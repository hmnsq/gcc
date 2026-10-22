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

#جيڪڏهن_وصف_نه_ٿيل GCC_C_OBJC_COMMON
#وصف_ڪريو GCC_C_OBJC_COMMON

/* Implemented in c-objc-common.cc.  */
خارجي فراغ c_رجسٽر_features ();

/* Lang hooks that are shared between C and ObjC are defined here.  Hooks
   specific to C or ObjC go in c-lang.cc and objc/objc-lang.cc, respectively.  */

#وصف_رد LANG_HOOKS_IDENTIFIER_سائيز
#وصف_ڪريو LANG_HOOKS_IDENTIFIER_سائيز C_SIZEOF_STRUCT_LANG_IDENTIFIER
#وصف_رد LANG_HOOKS_وڻ_سائيز
#وصف_ڪريو LANG_HOOKS_وڻ_سائيز c_وڻ_سائيز
#وصف_رد LANG_HOOKS_پڄاڻي
#وصف_ڪريو LANG_HOOKS_پڄاڻي c_common_پڄاڻي
#وصف_رد LANG_HOOKS_OPTION_LANG_نقاب
#وصف_ڪريو LANG_HOOKS_OPTION_LANG_نقاب c_common_option_lang_نقاب
#وصف_رد LANG_HOOKS_COMPLAIN_WRONG_LANG_P
#وصف_ڪريو LANG_HOOKS_COMPLAIN_WRONG_LANG_P c_common_complain_wrong_lang_p
#وصف_رد LANG_HOOKS_INIT_OPTIONS_STRUCT
#وصف_ڪريو LANG_HOOKS_INIT_OPTIONS_STRUCT c_common_init_options_struct
#وصف_رد LANG_HOOKS_INIT_OPTIONS
#وصف_ڪريو LANG_HOOKS_INIT_OPTIONS c_common_init_options
#وصف_رد LANG_HOOKS_INITIALIZE_DIAGNOSTICS
#وصف_ڪريو LANG_HOOKS_INITIALIZE_DIAGNOSTICS c_initialize_diagnostics
#وصف_رد LANG_HOOKS_HANDLE_OPTION
#وصف_ڪريو LANG_HOOKS_HANDLE_OPTION c_common_handle_option
#وصف_رد LANG_HOOKS_POST_OPTIONS
#وصف_ڪريو LANG_HOOKS_POST_OPTIONS c_common_post_options
#وصف_رد LANG_HOOKS_GET_ALIAS_سيٽ
#وصف_ڪريو LANG_HOOKS_GET_ALIAS_سيٽ c_get_alias_سيٽ
#وصف_رد LANG_HOOKS_PARSE_FILE
#وصف_ڪريو LANG_HOOKS_PARSE_FILE c_common_parse_file
#وصف_رد LANG_HOOKS_پڄاڻي_INCOMPLETE_DECL
#وصف_ڪريو LANG_HOOKS_پڄاڻي_INCOMPLETE_DECL c_پڄاڻي_incomplete_decl
#وصف_رد LANG_HOOKS_WARN_اڻ_استعمال_ٿيل_GLOBAL_DECL
#وصف_ڪريو LANG_HOOKS_WARN_اڻ_استعمال_ٿيل_GLOBAL_DECL c_warn_اڻ_استعمال_ٿيل_global_decl
#وصف_رد LANG_HOOKS_PRINT_IDENTIFIER
#وصف_ڪريو LANG_HOOKS_PRINT_IDENTIFIER c_print_identifier
#وصف_رد LANG_HOOKS_TYPES_COMPATIBLE_P
#وصف_ڪريو LANG_HOOKS_TYPES_COMPATIBLE_P c_types_compatible_p
#وصف_رد LANG_HOOKS_MISSING_NORETURN_OK_P
#وصف_ڪريو LANG_HOOKS_MISSING_NORETURN_OK_P c_missing_noreturn_ok_p
#وصف_رد LANG_HOOKS_بلاڪ_MAY_FALLTHRU
#وصف_ڪريو LANG_HOOKS_بلاڪ_MAY_FALLTHRU c_بلاڪ_may_fallthru
#وصف_رد  LANG_HOOKS_BUILTIN_FUNCTION
#وصف_ڪريو LANG_HOOKS_BUILTIN_FUNCTION c_builtin_function
#وصف_رد  LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE
#وصف_ڪريو LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE c_builtin_function_ext_scope
#وصف_رد  LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL
#وصف_ڪريو LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL \
  c_simulate_builtin_function_decl
#وصف_رد LANG_HOOKS_EMITS_BEGIN_STMT
#وصف_ڪريو LANG_HOOKS_EMITS_BEGIN_STMT true
#وصف_رد LANG_HOOKS_FINALIZE_EARLY_DEBUG
#وصف_ڪريو LANG_HOOKS_FINALIZE_EARLY_DEBUG c_common_finalize_early_debug
#وصف_رد LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE
#وصف_ڪريو LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE c_reconstruct_complex_type

ساكن ثابت scoped_attribute_specs *ثابت c_objc_attribute_جدول[] =
{
  &std_attribute_جدول,
  &c_common_gnu_attribute_جدول,
  &c_common_clang_attribute_جدول,
  &c_common_format_attribute_جدول
};

#وصف_رد LANG_HOOKS_ATTRIBUTE_جدول
#وصف_ڪريو LANG_HOOKS_ATTRIBUTE_جدول c_objc_attribute_جدول

#وصف_رد LANG_HOOKS_وڻ_DUMP_DUMP_وڻ_FN
#وصف_ڪريو LANG_HOOKS_وڻ_DUMP_DUMP_وڻ_FN c_dump_وڻ

#وصف_رد LANG_HOOKS_SIMULATE_ENUM_DECL
#وصف_ڪريو LANG_HOOKS_SIMULATE_ENUM_DECL c_simulate_enum_decl
#وصف_رد LANG_HOOKS_SIMULATE_رڪارڊ_DECL
#وصف_ڪريو LANG_HOOKS_SIMULATE_رڪارڊ_DECL c_simulate_رڪارڊ_decl
#وصف_رد LANG_HOOKS_TYPE_FOR_گهڻائي
#وصف_ڪريو LANG_HOOKS_TYPE_FOR_گهڻائي c_common_type_for_گهڻائي
#وصف_رد LANG_HOOKS_TYPE_FOR_سائيز
#وصف_ڪريو LANG_HOOKS_TYPE_FOR_سائيز c_common_type_for_سائيز
#وصف_رد LANG_HOOKS_INCOMPLETE_TYPE_ERROR
#وصف_ڪريو LANG_HOOKS_INCOMPLETE_TYPE_ERROR c_incomplete_type_error
#وصف_رد LANG_HOOKS_TYPE_PROMOTES_منزل
#وصف_ڪريو LANG_HOOKS_TYPE_PROMOTES_منزل c_type_promotes_منزل
#وصف_رد LANG_HOOKS_رجسٽر_BUILTIN_TYPE
#وصف_ڪريو LANG_HOOKS_رجسٽر_BUILTIN_TYPE c_رجسٽر_builtin_type
#وصف_رد LANG_HOOKS_منزل_هدف_CHARSET
#وصف_ڪريو LANG_HOOKS_منزل_هدف_CHARSET c_common_منزل_هدف_charset
#وصف_رد LANG_HOOKS_اظهار_منزل_DECL
#وصف_ڪريو LANG_HOOKS_اظهار_منزل_DECL c_اظهار_منزل_decl

/* The C front end's scoping structure is very different from
   that expected by the language-independent code; it is best
   to disable getdecls.
   This means it must also provide its own write_globals.  */

#وصف_رد LANG_HOOKS_GETDECLS
#وصف_ڪريو LANG_HOOKS_GETDECLS hook_وڻ_void_null

/* Hooks for tree gimplification.  */
#وصف_رد LANG_HOOKS_GIMPLIFY_اظهار
#وصف_ڪريو LANG_HOOKS_GIMPLIFY_اظهار c_gimplify_اظهار

#وصف_رد LANG_HOOKS_TYPE_DWARF_ATTRIBUTE
#وصف_ڪريو LANG_HOOKS_TYPE_DWARF_ATTRIBUTE c_type_dwarf_attribute

#وصف_رد LANG_HOOKS_OMP_PREDETERMINED_SHARING
#وصف_ڪريو LANG_HOOKS_OMP_PREDETERMINED_SHARING c_omp_predetermined_sharing

#وصف_رد LANG_HOOKS_OMP_PREDETERMINED_MAPPING
#وصف_ڪريو LANG_HOOKS_OMP_PREDETERMINED_MAPPING c_omp_predetermined_mapping

#وصف_رد LANG_HOOKS_OMP_CLAUSE_COPY_CTOR
#وصف_ڪريو LANG_HOOKS_OMP_CLAUSE_COPY_CTOR c_omp_clause_copy_ctor

#وصف_رد LANG_HOOKS_OMP_CLAUSE_سونپيو_OP
#وصف_ڪريو LANG_HOOKS_OMP_CLAUSE_سونپيو_OP c_omp_clause_copy_ctor

#وصف_رد LANG_HOOKS_OMP_پڄاڻي_MAPPER_CLAUSES
#وصف_ڪريو LANG_HOOKS_OMP_پڄاڻي_MAPPER_CLAUSES c_omp_پڄاڻي_mapper_clauses

#وصف_رد LANG_HOOKS_OMP_MAPPER_LOOKUP
#وصف_ڪريو LANG_HOOKS_OMP_MAPPER_LOOKUP c_omp_mapper_lookup

#وصف_رد LANG_HOOKS_OMP_ڪڍو_MAPPER_DIRECTIVE
#وصف_ڪريو LANG_HOOKS_OMP_ڪڍو_MAPPER_DIRECTIVE c_omp_ڪڍو_mapper_directive

#وصف_رد LANG_HOOKS_OMP_MAP_ARRAY_SECTION
#وصف_ڪريو LANG_HOOKS_OMP_MAP_ARRAY_SECTION c_omp_map_array_section

#وصف_رد LANG_HOOKS_وڻ_INLINING_VAR_MOD_TYPE_P
#وصف_ڪريو LANG_HOOKS_وڻ_INLINING_VAR_MOD_TYPE_P c_var_mod_p
#جيڪڏهن_پورو /* GCC_C_OBJC_COMMON */
