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

#నిర్వచితం_కాకపోతే GCC_C_OBJC_COMMON
#నిర్వచించు GCC_C_OBJC_COMMON

/* Implemented in c-objc-common.cc.  */
బాహ్య శూన్య c_రిజిస్టరు_features ();

/* Lang hooks that are shared between C and ObjC are defined here.  Hooks
   specific to C or ObjC go in c-lang.cc and objc/objc-lang.cc, respectively.  */

#నిర్వచనం_రద్దు LANG_HOOKS_IDENTIFIER_కొలత
#నిర్వచించు LANG_HOOKS_IDENTIFIER_కొలత C_SIZEOF_STRUCT_LANG_IDENTIFIER
#నిర్వచనం_రద్దు LANG_HOOKS_వృక్షం_కొలత
#నిర్వచించు LANG_HOOKS_వృక్షం_కొలత c_వృక్షం_కొలత
#నిర్వచనం_రద్దు LANG_HOOKS_ముగింపు
#నిర్వచించు LANG_HOOKS_ముగింపు c_common_ముగింపు
#నిర్వచనం_రద్దు LANG_HOOKS_OPTION_LANG_ముసుగు
#నిర్వచించు LANG_HOOKS_OPTION_LANG_ముసుగు c_common_option_lang_ముసుగు
#నిర్వచనం_రద్దు LANG_HOOKS_COMPLAIN_WRONG_LANG_P
#నిర్వచించు LANG_HOOKS_COMPLAIN_WRONG_LANG_P c_common_complain_wrong_lang_p
#నిర్వచనం_రద్దు LANG_HOOKS_INIT_OPTIONS_STRUCT
#నిర్వచించు LANG_HOOKS_INIT_OPTIONS_STRUCT c_common_init_options_struct
#నిర్వచనం_రద్దు LANG_HOOKS_INIT_OPTIONS
#నిర్వచించు LANG_HOOKS_INIT_OPTIONS c_common_init_options
#నిర్వచనం_రద్దు LANG_HOOKS_INITIALIZE_DIAGNOSTICS
#నిర్వచించు LANG_HOOKS_INITIALIZE_DIAGNOSTICS c_initialize_diagnostics
#నిర్వచనం_రద్దు LANG_HOOKS_HANDLE_OPTION
#నిర్వచించు LANG_HOOKS_HANDLE_OPTION c_common_handle_option
#నిర్వచనం_రద్దు LANG_HOOKS_POST_OPTIONS
#నిర్వచించు LANG_HOOKS_POST_OPTIONS c_common_post_options
#నిర్వచనం_రద్దు LANG_HOOKS_GET_ALIAS_సమితి
#నిర్వచించు LANG_HOOKS_GET_ALIAS_సమితి c_get_alias_సమితి
#నిర్వచనం_రద్దు LANG_HOOKS_PARSE_FILE
#నిర్వచించు LANG_HOOKS_PARSE_FILE c_common_parse_file
#నిర్వచనం_రద్దు LANG_HOOKS_ముగింపు_INCOMPLETE_DECL
#నిర్వచించు LANG_HOOKS_ముగింపు_INCOMPLETE_DECL c_ముగింపు_incomplete_decl
#నిర్వచనం_రద్దు LANG_HOOKS_WARN_వాడని_GLOBAL_DECL
#నిర్వచించు LANG_HOOKS_WARN_వాడని_GLOBAL_DECL c_warn_వాడని_global_decl
#నిర్వచనం_రద్దు LANG_HOOKS_PRINT_IDENTIFIER
#నిర్వచించు LANG_HOOKS_PRINT_IDENTIFIER c_print_identifier
#నిర్వచనం_రద్దు LANG_HOOKS_TYPES_COMPATIBLE_P
#నిర్వచించు LANG_HOOKS_TYPES_COMPATIBLE_P c_types_compatible_p
#నిర్వచనం_రద్దు LANG_HOOKS_MISSING_NORETURN_OK_P
#నిర్వచించు LANG_HOOKS_MISSING_NORETURN_OK_P c_missing_noreturn_ok_p
#నిర్వచనం_రద్దు LANG_HOOKS_ఖండం_MAY_FALLTHRU
#నిర్వచించు LANG_HOOKS_ఖండం_MAY_FALLTHRU c_ఖండం_may_fallthru
#నిర్వచనం_రద్దు  LANG_HOOKS_BUILTIN_FUNCTION
#నిర్వచించు LANG_HOOKS_BUILTIN_FUNCTION c_builtin_function
#నిర్వచనం_రద్దు  LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE
#నిర్వచించు LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE c_builtin_function_ext_scope
#నిర్వచనం_రద్దు  LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL
#నిర్వచించు LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL \
  c_simulate_builtin_function_decl
#నిర్వచనం_రద్దు LANG_HOOKS_EMITS_BEGIN_STMT
#నిర్వచించు LANG_HOOKS_EMITS_BEGIN_STMT true
#నిర్వచనం_రద్దు LANG_HOOKS_FINALIZE_EARLY_DEBUG
#నిర్వచించు LANG_HOOKS_FINALIZE_EARLY_DEBUG c_common_finalize_early_debug
#నిర్వచనం_రద్దు LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE
#నిర్వచించు LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE c_reconstruct_complex_type

స్థిర స్థిరరాశి scoped_attribute_specs *స్థిరరాశి c_objc_attribute_పట్టిక[] =
{
  &std_attribute_పట్టిక,
  &c_common_gnu_attribute_పట్టిక,
  &c_common_clang_attribute_పట్టిక,
  &c_common_format_attribute_పట్టిక
};

#నిర్వచనం_రద్దు LANG_HOOKS_ATTRIBUTE_పట్టిక
#నిర్వచించు LANG_HOOKS_ATTRIBUTE_పట్టిక c_objc_attribute_పట్టిక

#నిర్వచనం_రద్దు LANG_HOOKS_వృక్షం_DUMP_DUMP_వృక్షం_FN
#నిర్వచించు LANG_HOOKS_వృక్షం_DUMP_DUMP_వృక్షం_FN c_dump_వృక్షం

#నిర్వచనం_రద్దు LANG_HOOKS_SIMULATE_ENUM_DECL
#నిర్వచించు LANG_HOOKS_SIMULATE_ENUM_DECL c_simulate_enum_decl
#నిర్వచనం_రద్దు LANG_HOOKS_SIMULATE_రికార్డు_DECL
#నిర్వచించు LANG_HOOKS_SIMULATE_రికార్డు_DECL c_simulate_రికార్డు_decl
#నిర్వచనం_రద్దు LANG_HOOKS_TYPE_FOR_బహుళకం
#నిర్వచించు LANG_HOOKS_TYPE_FOR_బహుళకం c_common_type_for_బహుళకం
#నిర్వచనం_రద్దు LANG_HOOKS_TYPE_FOR_కొలత
#నిర్వచించు LANG_HOOKS_TYPE_FOR_కొలత c_common_type_for_కొలత
#నిర్వచనం_రద్దు LANG_HOOKS_INCOMPLETE_TYPE_ERROR
#నిర్వచించు LANG_HOOKS_INCOMPLETE_TYPE_ERROR c_incomplete_type_error
#నిర్వచనం_రద్దు LANG_HOOKS_TYPE_PROMOTES_గమ్యం
#నిర్వచించు LANG_HOOKS_TYPE_PROMOTES_గమ్యం c_type_promotes_గమ్యం
#నిర్వచనం_రద్దు LANG_HOOKS_రిజిస్టరు_BUILTIN_TYPE
#నిర్వచించు LANG_HOOKS_రిజిస్టరు_BUILTIN_TYPE c_రిజిస్టరు_builtin_type
#నిర్వచనం_రద్దు LANG_HOOKS_గమ్యం_లక్ష్యం_CHARSET
#నిర్వచించు LANG_HOOKS_గమ్యం_లక్ష్యం_CHARSET c_common_గమ్యం_లక్ష్యం_charset
#నిర్వచనం_రద్దు LANG_HOOKS_సమాసం_గమ్యం_DECL
#నిర్వచించు LANG_HOOKS_సమాసం_గమ్యం_DECL c_సమాసం_గమ్యం_decl

/* The C front end's scoping structure is very different from
   that expected by the language-independent code; it is best
   to disable getdecls.
   This means it must also provide its own write_globals.  */

#నిర్వచనం_రద్దు LANG_HOOKS_GETDECLS
#నిర్వచించు LANG_HOOKS_GETDECLS hook_వృక్షం_void_null

/* Hooks for tree gimplification.  */
#నిర్వచనం_రద్దు LANG_HOOKS_GIMPLIFY_సమాసం
#నిర్వచించు LANG_HOOKS_GIMPLIFY_సమాసం c_gimplify_సమాసం

#నిర్వచనం_రద్దు LANG_HOOKS_TYPE_DWARF_ATTRIBUTE
#నిర్వచించు LANG_HOOKS_TYPE_DWARF_ATTRIBUTE c_type_dwarf_attribute

#నిర్వచనం_రద్దు LANG_HOOKS_OMP_PREDETERMINED_SHARING
#నిర్వచించు LANG_HOOKS_OMP_PREDETERMINED_SHARING c_omp_predetermined_sharing

#నిర్వచనం_రద్దు LANG_HOOKS_OMP_PREDETERMINED_MAPPING
#నిర్వచించు LANG_HOOKS_OMP_PREDETERMINED_MAPPING c_omp_predetermined_mapping

#నిర్వచనం_రద్దు LANG_HOOKS_OMP_CLAUSE_COPY_CTOR
#నిర్వచించు LANG_HOOKS_OMP_CLAUSE_COPY_CTOR c_omp_clause_copy_ctor

#నిర్వచనం_రద్దు LANG_HOOKS_OMP_CLAUSE_కేటాయించు_OP
#నిర్వచించు LANG_HOOKS_OMP_CLAUSE_కేటాయించు_OP c_omp_clause_copy_ctor

#నిర్వచనం_రద్దు LANG_HOOKS_OMP_ముగింపు_MAPPER_CLAUSES
#నిర్వచించు LANG_HOOKS_OMP_ముగింపు_MAPPER_CLAUSES c_omp_ముగింపు_mapper_clauses

#నిర్వచనం_రద్దు LANG_HOOKS_OMP_MAPPER_LOOKUP
#నిర్వచించు LANG_HOOKS_OMP_MAPPER_LOOKUP c_omp_mapper_lookup

#నిర్వచనం_రద్దు LANG_HOOKS_OMP_వెలికితీయి_MAPPER_DIRECTIVE
#నిర్వచించు LANG_HOOKS_OMP_వెలికితీయి_MAPPER_DIRECTIVE c_omp_వెలికితీయి_mapper_directive

#నిర్వచనం_రద్దు LANG_HOOKS_OMP_MAP_ARRAY_SECTION
#నిర్వచించు LANG_HOOKS_OMP_MAP_ARRAY_SECTION c_omp_map_array_section

#నిర్వచనం_రద్దు LANG_HOOKS_వృక్షం_INLINING_VAR_MOD_TYPE_P
#నిర్వచించు LANG_HOOKS_వృక్షం_INLINING_VAR_MOD_TYPE_P c_var_mod_p
#అయితే_ముగింపు /* GCC_C_OBJC_COMMON */
