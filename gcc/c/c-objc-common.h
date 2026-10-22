/* Language hooks common to C and ObjC front ends.
   Copyright (C) 2004-2026 Free Software Foundation, Inc.
   Contributed by Ziemowit Laski  <zlaski@apple.com>

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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GCC_C_OBJC_COMMON
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GCC_C_OBJC_COMMON

/* Implemented in c-objc-common.cc.  */
ਬਾਹਰੀ ਖਾਲੀ c_ਰਜਿਸਟਰ_features ();

/* Lang hooks that are shared between C and ObjC are defined here.  Hooks
   specific to C or ObjC go in c-lang.cc and objc/objc-lang.cc, respectively.  */

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_IDENTIFIER_ਮਾਪ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_IDENTIFIER_ਮਾਪ C_SIZEOF_STRUCT_LANG_IDENTIFIER
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਰੁੱਖ_ਮਾਪ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਰੁੱਖ_ਮਾਪ c_ਰੁੱਖ_ਮਾਪ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਅੰਤ c_common_ਅੰਤ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OPTION_LANG_ਨਕਾਬ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OPTION_LANG_ਨਕਾਬ c_common_option_lang_ਨਕਾਬ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_COMPLAIN_WRONG_LANG_P
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_COMPLAIN_WRONG_LANG_P c_common_complain_wrong_lang_p
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_INIT_OPTIONS_STRUCT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_INIT_OPTIONS_STRUCT c_common_init_options_struct
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_INIT_OPTIONS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_INIT_OPTIONS c_common_init_options
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_INITIALIZE_DIAGNOSTICS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_INITIALIZE_DIAGNOSTICS c_initialize_diagnostics
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_HANDLE_OPTION
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_HANDLE_OPTION c_common_handle_option
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_POST_OPTIONS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_POST_OPTIONS c_common_post_options
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_GET_ALIAS_ਸੈੱਟ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_GET_ALIAS_ਸੈੱਟ c_get_alias_ਸੈੱਟ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_PARSE_FILE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_PARSE_FILE c_common_parse_file
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਅੰਤ_INCOMPLETE_DECL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਅੰਤ_INCOMPLETE_DECL c_ਅੰਤ_incomplete_decl
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_WARN_ਅਣਵਰਤਿਆ_GLOBAL_DECL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_WARN_ਅਣਵਰਤਿਆ_GLOBAL_DECL c_warn_ਅਣਵਰਤਿਆ_global_decl
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_PRINT_IDENTIFIER
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_PRINT_IDENTIFIER c_print_identifier
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_TYPES_COMPATIBLE_P
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_TYPES_COMPATIBLE_P c_types_compatible_p
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_MISSING_NORETURN_OK_P
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_MISSING_NORETURN_OK_P c_missing_noreturn_ok_p
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਖੰਡ_MAY_FALLTHRU
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਖੰਡ_MAY_FALLTHRU c_ਖੰਡ_may_fallthru
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ  LANG_HOOKS_BUILTIN_FUNCTION
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_BUILTIN_FUNCTION c_builtin_function
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ  LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE c_builtin_function_ext_scope
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ  LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL \
  c_simulate_builtin_function_decl
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_EMITS_BEGIN_STMT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_EMITS_BEGIN_STMT true
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_FINALIZE_EARLY_DEBUG
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_FINALIZE_EARLY_DEBUG c_common_finalize_early_debug
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE c_reconstruct_complex_type

ਸਥਿਰ ਅਚਲ scoped_attribute_specs *ਅਚਲ c_objc_attribute_ਸਾਰਣੀ[] =
{
  &std_attribute_ਸਾਰਣੀ,
  &c_common_gnu_attribute_ਸਾਰਣੀ,
  &c_common_clang_attribute_ਸਾਰਣੀ,
  &c_common_format_attribute_ਸਾਰਣੀ
};

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ATTRIBUTE_ਸਾਰਣੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ATTRIBUTE_ਸਾਰਣੀ c_objc_attribute_ਸਾਰਣੀ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਰੁੱਖ_DUMP_DUMP_ਰੁੱਖ_FN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਰੁੱਖ_DUMP_DUMP_ਰੁੱਖ_FN c_dump_ਰੁੱਖ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_SIMULATE_ENUM_DECL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_SIMULATE_ENUM_DECL c_simulate_enum_decl
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_SIMULATE_ਰਿਕਾਰਡ_DECL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_SIMULATE_ਰਿਕਾਰਡ_DECL c_simulate_ਰਿਕਾਰਡ_decl
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_TYPE_FOR_ਬਹੁਲਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_TYPE_FOR_ਬਹੁਲਕ c_common_type_for_ਬਹੁਲਕ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_TYPE_FOR_ਮਾਪ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_TYPE_FOR_ਮਾਪ c_common_type_for_ਮਾਪ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_INCOMPLETE_TYPE_ERROR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_INCOMPLETE_TYPE_ERROR c_incomplete_type_error
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_TYPE_PROMOTES_ਮੰਜ਼ਿਲ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_TYPE_PROMOTES_ਮੰਜ਼ਿਲ c_type_promotes_ਮੰਜ਼ਿਲ
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਰਜਿਸਟਰ_BUILTIN_TYPE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਰਜਿਸਟਰ_BUILTIN_TYPE c_ਰਜਿਸਟਰ_builtin_type
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਮੰਜ਼ਿਲ_ਨਿਸ਼ਾਨਾ_CHARSET
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਮੰਜ਼ਿਲ_ਨਿਸ਼ਾਨਾ_CHARSET c_common_ਮੰਜ਼ਿਲ_ਨਿਸ਼ਾਨਾ_charset
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਵਿਅੰਜਕ_ਮੰਜ਼ਿਲ_DECL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਵਿਅੰਜਕ_ਮੰਜ਼ਿਲ_DECL c_ਵਿਅੰਜਕ_ਮੰਜ਼ਿਲ_decl

/* The C front end's scoping structure is very different from
   that expected by the language-independent code; it is best
   to disable getdecls.
   This means it must also provide its own write_globals.  */

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_GETDECLS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_GETDECLS hook_ਰੁੱਖ_void_null

/* Hooks for tree gimplification.  */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_GIMPLIFY_ਵਿਅੰਜਕ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_GIMPLIFY_ਵਿਅੰਜਕ c_gimplify_ਵਿਅੰਜਕ

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_TYPE_DWARF_ATTRIBUTE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_TYPE_DWARF_ATTRIBUTE c_type_dwarf_attribute

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OMP_PREDETERMINED_SHARING
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OMP_PREDETERMINED_SHARING c_omp_predetermined_sharing

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OMP_PREDETERMINED_MAPPING
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OMP_PREDETERMINED_MAPPING c_omp_predetermined_mapping

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OMP_CLAUSE_COPY_CTOR
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OMP_CLAUSE_COPY_CTOR c_omp_clause_copy_ctor

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OMP_CLAUSE_ਸੌਂਪੋ_OP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OMP_CLAUSE_ਸੌਂਪੋ_OP c_omp_clause_copy_ctor

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OMP_ਅੰਤ_MAPPER_CLAUSES
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OMP_ਅੰਤ_MAPPER_CLAUSES c_omp_ਅੰਤ_mapper_clauses

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OMP_MAPPER_LOOKUP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OMP_MAPPER_LOOKUP c_omp_mapper_lookup

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OMP_ਕੱਢੋ_MAPPER_DIRECTIVE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OMP_ਕੱਢੋ_MAPPER_DIRECTIVE c_omp_ਕੱਢੋ_mapper_directive

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_OMP_MAP_ARRAY_SECTION
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_OMP_MAP_ARRAY_SECTION c_omp_map_array_section

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਰੁੱਖ_INLINING_VAR_MOD_TYPE_P
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਰੁੱਖ_INLINING_VAR_MOD_TYPE_P c_var_mod_p
#ਜੇ_ਅੰਤ /* GCC_C_OBJC_COMMON */
