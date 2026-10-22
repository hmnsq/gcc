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

#اگر_تعریف_نشده GCC_C_OBJC_COMMON
#تعریف_کن GCC_C_OBJC_COMMON

/* Implemented in c-objc-common.cc.  */
خارجي فراغ c_ثبات_features ();

/* Lang hooks that are shared between C and ObjC are defined here.  Hooks
   specific to C or ObjC go in c-lang.cc and objc/objc-lang.cc, respectively.  */

#لغو_تعریف LANG_HOOKS_IDENTIFIER_اندازه
#تعریف_کن LANG_HOOKS_IDENTIFIER_اندازه C_SIZEOF_STRUCT_LANG_IDENTIFIER
#لغو_تعریف LANG_HOOKS_درخت_اندازه
#تعریف_کن LANG_HOOKS_درخت_اندازه c_درخت_اندازه
#لغو_تعریف LANG_HOOKS_پایان
#تعریف_کن LANG_HOOKS_پایان c_common_پایان
#لغو_تعریف LANG_HOOKS_OPTION_LANG_ماسک
#تعریف_کن LANG_HOOKS_OPTION_LANG_ماسک c_common_option_lang_ماسک
#لغو_تعریف LANG_HOOKS_COMPLAIN_WRONG_LANG_P
#تعریف_کن LANG_HOOKS_COMPLAIN_WRONG_LANG_P c_common_complain_wrong_lang_p
#لغو_تعریف LANG_HOOKS_INIT_OPTIONS_STRUCT
#تعریف_کن LANG_HOOKS_INIT_OPTIONS_STRUCT c_common_init_options_struct
#لغو_تعریف LANG_HOOKS_INIT_OPTIONS
#تعریف_کن LANG_HOOKS_INIT_OPTIONS c_common_init_options
#لغو_تعریف LANG_HOOKS_INITIALIZE_DIAGNOSTICS
#تعریف_کن LANG_HOOKS_INITIALIZE_DIAGNOSTICS c_initialize_diagnostics
#لغو_تعریف LANG_HOOKS_HANDLE_OPTION
#تعریف_کن LANG_HOOKS_HANDLE_OPTION c_common_handle_option
#لغو_تعریف LANG_HOOKS_POST_OPTIONS
#تعریف_کن LANG_HOOKS_POST_OPTIONS c_common_post_options
#لغو_تعریف LANG_HOOKS_GET_ALIAS_مجموعه
#تعریف_کن LANG_HOOKS_GET_ALIAS_مجموعه c_get_alias_مجموعه
#لغو_تعریف LANG_HOOKS_PARSE_FILE
#تعریف_کن LANG_HOOKS_PARSE_FILE c_common_parse_file
#لغو_تعریف LANG_HOOKS_پایان_INCOMPLETE_DECL
#تعریف_کن LANG_HOOKS_پایان_INCOMPLETE_DECL c_پایان_incomplete_decl
#لغو_تعریف LANG_HOOKS_WARN_استفادهنشده_GLOBAL_DECL
#تعریف_کن LANG_HOOKS_WARN_استفادهنشده_GLOBAL_DECL c_warn_استفادهنشده_global_decl
#لغو_تعریف LANG_HOOKS_PRINT_IDENTIFIER
#تعریف_کن LANG_HOOKS_PRINT_IDENTIFIER c_print_identifier
#لغو_تعریف LANG_HOOKS_TYPES_COMPATIBLE_P
#تعریف_کن LANG_HOOKS_TYPES_COMPATIBLE_P c_types_compatible_p
#لغو_تعریف LANG_HOOKS_MISSING_NORETURN_OK_P
#تعریف_کن LANG_HOOKS_MISSING_NORETURN_OK_P c_missing_noreturn_ok_p
#لغو_تعریف LANG_HOOKS_بلوک_MAY_FALLTHRU
#تعریف_کن LANG_HOOKS_بلوک_MAY_FALLTHRU c_بلوک_may_fallthru
#لغو_تعریف  LANG_HOOKS_BUILTIN_FUNCTION
#تعریف_کن LANG_HOOKS_BUILTIN_FUNCTION c_builtin_function
#لغو_تعریف  LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE
#تعریف_کن LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE c_builtin_function_ext_scope
#لغو_تعریف  LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL
#تعریف_کن LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL \
  c_simulate_builtin_function_decl
#لغو_تعریف LANG_HOOKS_EMITS_BEGIN_STMT
#تعریف_کن LANG_HOOKS_EMITS_BEGIN_STMT true
#لغو_تعریف LANG_HOOKS_FINALIZE_EARLY_DEBUG
#تعریف_کن LANG_HOOKS_FINALIZE_EARLY_DEBUG c_common_finalize_early_debug
#لغو_تعریف LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE
#تعریف_کن LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE c_reconstruct_complex_type

ساكن ثابت scoped_attribute_specs *ثابت c_objc_attribute_جدول[] =
{
  &std_attribute_جدول,
  &c_common_gnu_attribute_جدول,
  &c_common_clang_attribute_جدول,
  &c_common_format_attribute_جدول
};

#لغو_تعریف LANG_HOOKS_ATTRIBUTE_جدول
#تعریف_کن LANG_HOOKS_ATTRIBUTE_جدول c_objc_attribute_جدول

#لغو_تعریف LANG_HOOKS_درخت_DUMP_DUMP_درخت_FN
#تعریف_کن LANG_HOOKS_درخت_DUMP_DUMP_درخت_FN c_dump_درخت

#لغو_تعریف LANG_HOOKS_SIMULATE_ENUM_DECL
#تعریف_کن LANG_HOOKS_SIMULATE_ENUM_DECL c_simulate_enum_decl
#لغو_تعریف LANG_HOOKS_SIMULATE_رکورد_DECL
#تعریف_کن LANG_HOOKS_SIMULATE_رکورد_DECL c_simulate_رکورد_decl
#لغو_تعریف LANG_HOOKS_TYPE_FOR_نما
#تعریف_کن LANG_HOOKS_TYPE_FOR_نما c_common_type_for_نما
#لغو_تعریف LANG_HOOKS_TYPE_FOR_اندازه
#تعریف_کن LANG_HOOKS_TYPE_FOR_اندازه c_common_type_for_اندازه
#لغو_تعریف LANG_HOOKS_INCOMPLETE_TYPE_ERROR
#تعریف_کن LANG_HOOKS_INCOMPLETE_TYPE_ERROR c_incomplete_type_error
#لغو_تعریف LANG_HOOKS_TYPE_PROMOTES_مقصد
#تعریف_کن LANG_HOOKS_TYPE_PROMOTES_مقصد c_type_promotes_مقصد
#لغو_تعریف LANG_HOOKS_ثبات_BUILTIN_TYPE
#تعریف_کن LANG_HOOKS_ثبات_BUILTIN_TYPE c_ثبات_builtin_type
#لغو_تعریف LANG_HOOKS_مقصد_هدف_CHARSET
#تعریف_کن LANG_HOOKS_مقصد_هدف_CHARSET c_common_مقصد_هدف_charset
#لغو_تعریف LANG_HOOKS_عبارت_مقصد_DECL
#تعریف_کن LANG_HOOKS_عبارت_مقصد_DECL c_عبارت_مقصد_decl

/* The C front end's scoping structure is very different from
   that expected by the language-independent code; it is best
   to disable getdecls.
   This means it must also provide its own write_globals.  */

#لغو_تعریف LANG_HOOKS_GETDECLS
#تعریف_کن LANG_HOOKS_GETDECLS hook_درخت_void_null

/* Hooks for tree gimplification.  */
#لغو_تعریف LANG_HOOKS_GIMPLIFY_عبارت
#تعریف_کن LANG_HOOKS_GIMPLIFY_عبارت c_gimplify_عبارت

#لغو_تعریف LANG_HOOKS_TYPE_DWARF_ATTRIBUTE
#تعریف_کن LANG_HOOKS_TYPE_DWARF_ATTRIBUTE c_type_dwarf_attribute

#لغو_تعریف LANG_HOOKS_OMP_PREDETERMINED_SHARING
#تعریف_کن LANG_HOOKS_OMP_PREDETERMINED_SHARING c_omp_predetermined_sharing

#لغو_تعریف LANG_HOOKS_OMP_PREDETERMINED_MAPPING
#تعریف_کن LANG_HOOKS_OMP_PREDETERMINED_MAPPING c_omp_predetermined_mapping

#لغو_تعریف LANG_HOOKS_OMP_CLAUSE_COPY_CTOR
#تعریف_کن LANG_HOOKS_OMP_CLAUSE_COPY_CTOR c_omp_clause_copy_ctor

#لغو_تعریف LANG_HOOKS_OMP_CLAUSE_تخصیص_بده_OP
#تعریف_کن LANG_HOOKS_OMP_CLAUSE_تخصیص_بده_OP c_omp_clause_copy_ctor

#لغو_تعریف LANG_HOOKS_OMP_پایان_MAPPER_CLAUSES
#تعریف_کن LANG_HOOKS_OMP_پایان_MAPPER_CLAUSES c_omp_پایان_mapper_clauses

#لغو_تعریف LANG_HOOKS_OMP_MAPPER_LOOKUP
#تعریف_کن LANG_HOOKS_OMP_MAPPER_LOOKUP c_omp_mapper_lookup

#لغو_تعریف LANG_HOOKS_OMP_استخراج_MAPPER_DIRECTIVE
#تعریف_کن LANG_HOOKS_OMP_استخراج_MAPPER_DIRECTIVE c_omp_استخراج_mapper_directive

#لغو_تعریف LANG_HOOKS_OMP_MAP_ARRAY_SECTION
#تعریف_کن LANG_HOOKS_OMP_MAP_ARRAY_SECTION c_omp_map_array_section

#لغو_تعریف LANG_HOOKS_درخت_INLINING_VAR_MOD_TYPE_P
#تعریف_کن LANG_HOOKS_درخت_INLINING_VAR_MOD_TYPE_P c_var_mod_p
#پایان_اگر /* GCC_C_OBJC_COMMON */
