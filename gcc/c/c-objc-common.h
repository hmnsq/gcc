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

#اگر_غیر_تعریف_شدہ GCC_C_OBJC_COMMON
#تعریف_کرو GCC_C_OBJC_COMMON

/* Implemented in c-objc-common.cc.  */
خارجی خالی c_رجسٹر_features ();

/* Lang hooks that are shared between C and ObjC are defined here.  Hooks
   specific to C or ObjC go in c-lang.cc and objc/objc-lang.cc, respectively.  */

#تعریف_منسوخ LANG_HOOKS_IDENTIFIER_سائز
#تعریف_کرو LANG_HOOKS_IDENTIFIER_سائز C_SIZEOF_STRUCT_LANG_IDENTIFIER
#تعریف_منسوخ LANG_HOOKS_درخت_سائز
#تعریف_کرو LANG_HOOKS_درخت_سائز c_درخت_سائز
#تعریف_منسوخ LANG_HOOKS_اختتام
#تعریف_کرو LANG_HOOKS_اختتام c_common_اختتام
#تعریف_منسوخ LANG_HOOKS_OPTION_LANG_نقاب
#تعریف_کرو LANG_HOOKS_OPTION_LANG_نقاب c_common_option_lang_نقاب
#تعریف_منسوخ LANG_HOOKS_COMPLAIN_WRONG_LANG_P
#تعریف_کرو LANG_HOOKS_COMPLAIN_WRONG_LANG_P c_common_complain_wrong_lang_p
#تعریف_منسوخ LANG_HOOKS_INIT_OPTIONS_STRUCT
#تعریف_کرو LANG_HOOKS_INIT_OPTIONS_STRUCT c_common_init_options_struct
#تعریف_منسوخ LANG_HOOKS_INIT_OPTIONS
#تعریف_کرو LANG_HOOKS_INIT_OPTIONS c_common_init_options
#تعریف_منسوخ LANG_HOOKS_INITIALIZE_DIAGNOSTICS
#تعریف_کرو LANG_HOOKS_INITIALIZE_DIAGNOSTICS c_initialize_diagnostics
#تعریف_منسوخ LANG_HOOKS_HANDLE_OPTION
#تعریف_کرو LANG_HOOKS_HANDLE_OPTION c_common_handle_option
#تعریف_منسوخ LANG_HOOKS_POST_OPTIONS
#تعریف_کرو LANG_HOOKS_POST_OPTIONS c_common_post_options
#تعریف_منسوخ LANG_HOOKS_GET_ALIAS_سیٹ
#تعریف_کرو LANG_HOOKS_GET_ALIAS_سیٹ c_get_alias_سیٹ
#تعریف_منسوخ LANG_HOOKS_PARSE_FILE
#تعریف_کرو LANG_HOOKS_PARSE_FILE c_common_parse_file
#تعریف_منسوخ LANG_HOOKS_اختتام_INCOMPLETE_DECL
#تعریف_کرو LANG_HOOKS_اختتام_INCOMPLETE_DECL c_اختتام_incomplete_decl
#تعریف_منسوخ LANG_HOOKS_WARN_غیر_مستعمل_GLOBAL_DECL
#تعریف_کرو LANG_HOOKS_WARN_غیر_مستعمل_GLOBAL_DECL c_warn_غیر_مستعمل_global_decl
#تعریف_منسوخ LANG_HOOKS_PRINT_IDENTIFIER
#تعریف_کرو LANG_HOOKS_PRINT_IDENTIFIER c_print_identifier
#تعریف_منسوخ LANG_HOOKS_TYPES_COMPATIBLE_P
#تعریف_کرو LANG_HOOKS_TYPES_COMPATIBLE_P c_types_compatible_p
#تعریف_منسوخ LANG_HOOKS_MISSING_NORETURN_OK_P
#تعریف_کرو LANG_HOOKS_MISSING_NORETURN_OK_P c_missing_noreturn_ok_p
#تعریف_منسوخ LANG_HOOKS_بلاک_MAY_FALLTHRU
#تعریف_کرو LANG_HOOKS_بلاک_MAY_FALLTHRU c_بلاک_may_fallthru
#تعریف_منسوخ  LANG_HOOKS_BUILTIN_FUNCTION
#تعریف_کرو LANG_HOOKS_BUILTIN_FUNCTION c_builtin_function
#تعریف_منسوخ  LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE
#تعریف_کرو LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE c_builtin_function_ext_scope
#تعریف_منسوخ  LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL
#تعریف_کرو LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL \
  c_simulate_builtin_function_decl
#تعریف_منسوخ LANG_HOOKS_EMITS_BEGIN_STMT
#تعریف_کرو LANG_HOOKS_EMITS_BEGIN_STMT true
#تعریف_منسوخ LANG_HOOKS_FINALIZE_EARLY_DEBUG
#تعریف_کرو LANG_HOOKS_FINALIZE_EARLY_DEBUG c_common_finalize_early_debug
#تعریف_منسوخ LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE
#تعریف_کرو LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE c_reconstruct_complex_type

ساکن ثابت scoped_attribute_specs *ثابت c_objc_attribute_جدول[] =
{
  &std_attribute_جدول,
  &c_common_gnu_attribute_جدول,
  &c_common_clang_attribute_جدول,
  &c_common_format_attribute_جدول
};

#تعریف_منسوخ LANG_HOOKS_ATTRIBUTE_جدول
#تعریف_کرو LANG_HOOKS_ATTRIBUTE_جدول c_objc_attribute_جدول

#تعریف_منسوخ LANG_HOOKS_درخت_DUMP_DUMP_درخت_FN
#تعریف_کرو LANG_HOOKS_درخت_DUMP_DUMP_درخت_FN c_dump_درخت

#تعریف_منسوخ LANG_HOOKS_SIMULATE_ENUM_DECL
#تعریف_کرو LANG_HOOKS_SIMULATE_ENUM_DECL c_simulate_enum_decl
#تعریف_منسوخ LANG_HOOKS_SIMULATE_ریکارڈ_DECL
#تعریف_کرو LANG_HOOKS_SIMULATE_ریکارڈ_DECL c_simulate_ریکارڈ_decl
#تعریف_منسوخ LANG_HOOKS_TYPE_FOR_منوال
#تعریف_کرو LANG_HOOKS_TYPE_FOR_منوال c_common_type_for_منوال
#تعریف_منسوخ LANG_HOOKS_TYPE_FOR_سائز
#تعریف_کرو LANG_HOOKS_TYPE_FOR_سائز c_common_type_for_سائز
#تعریف_منسوخ LANG_HOOKS_INCOMPLETE_TYPE_ERROR
#تعریف_کرو LANG_HOOKS_INCOMPLETE_TYPE_ERROR c_incomplete_type_error
#تعریف_منسوخ LANG_HOOKS_TYPE_PROMOTES_مقصد
#تعریف_کرو LANG_HOOKS_TYPE_PROMOTES_مقصد c_type_promotes_مقصد
#تعریف_منسوخ LANG_HOOKS_رجسٹر_BUILTIN_TYPE
#تعریف_کرو LANG_HOOKS_رجسٹر_BUILTIN_TYPE c_رجسٹر_builtin_type
#تعریف_منسوخ LANG_HOOKS_مقصد_ہدف_CHARSET
#تعریف_کرو LANG_HOOKS_مقصد_ہدف_CHARSET c_common_مقصد_ہدف_charset
#تعریف_منسوخ LANG_HOOKS_اظہاریہ_مقصد_DECL
#تعریف_کرو LANG_HOOKS_اظہاریہ_مقصد_DECL c_اظہاریہ_مقصد_decl

/* The C front end's scoping structure is very different from
   that expected by the language-independent code; it is best
   to disable getdecls.
   This means it must also provide its own write_globals.  */

#تعریف_منسوخ LANG_HOOKS_GETDECLS
#تعریف_کرو LANG_HOOKS_GETDECLS hook_درخت_void_null

/* Hooks for tree gimplification.  */
#تعریف_منسوخ LANG_HOOKS_GIMPLIFY_اظہاریہ
#تعریف_کرو LANG_HOOKS_GIMPLIFY_اظہاریہ c_gimplify_اظہاریہ

#تعریف_منسوخ LANG_HOOKS_TYPE_DWARF_ATTRIBUTE
#تعریف_کرو LANG_HOOKS_TYPE_DWARF_ATTRIBUTE c_type_dwarf_attribute

#تعریف_منسوخ LANG_HOOKS_OMP_PREDETERMINED_SHARING
#تعریف_کرو LANG_HOOKS_OMP_PREDETERMINED_SHARING c_omp_predetermined_sharing

#تعریف_منسوخ LANG_HOOKS_OMP_PREDETERMINED_MAPPING
#تعریف_کرو LANG_HOOKS_OMP_PREDETERMINED_MAPPING c_omp_predetermined_mapping

#تعریف_منسوخ LANG_HOOKS_OMP_CLAUSE_COPY_CTOR
#تعریف_کرو LANG_HOOKS_OMP_CLAUSE_COPY_CTOR c_omp_clause_copy_ctor

#تعریف_منسوخ LANG_HOOKS_OMP_CLAUSE_تفویض_OP
#تعریف_کرو LANG_HOOKS_OMP_CLAUSE_تفویض_OP c_omp_clause_copy_ctor

#تعریف_منسوخ LANG_HOOKS_OMP_اختتام_MAPPER_CLAUSES
#تعریف_کرو LANG_HOOKS_OMP_اختتام_MAPPER_CLAUSES c_omp_اختتام_mapper_clauses

#تعریف_منسوخ LANG_HOOKS_OMP_MAPPER_LOOKUP
#تعریف_کرو LANG_HOOKS_OMP_MAPPER_LOOKUP c_omp_mapper_lookup

#تعریف_منسوخ LANG_HOOKS_OMP_نکالو_MAPPER_DIRECTIVE
#تعریف_کرو LANG_HOOKS_OMP_نکالو_MAPPER_DIRECTIVE c_omp_نکالو_mapper_directive

#تعریف_منسوخ LANG_HOOKS_OMP_MAP_ARRAY_SECTION
#تعریف_کرو LANG_HOOKS_OMP_MAP_ARRAY_SECTION c_omp_map_array_section

#تعریف_منسوخ LANG_HOOKS_درخت_INLINING_VAR_MOD_TYPE_P
#تعریف_کرو LANG_HOOKS_درخت_INLINING_VAR_MOD_TYPE_P c_var_mod_p
#اگر_ختم /* GCC_C_OBJC_COMMON */
