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

#यदि_अपरिभाषितम् GCC_C_OBJC_COMMON
#परिभाषय GCC_C_OBJC_COMMON

/* Implemented in c-objc-common.cc.  */
बाह्य शून्य c_पञ्जिकाकोशः_features ();

/* Lang hooks that are shared between C and ObjC are defined here.  Hooks
   specific to C or ObjC go in c-lang.cc and objc/objc-lang.cc, respectively.  */

#अपरिभाषय LANG_HOOKS_IDENTIFIER_आकार
#परिभाषय LANG_HOOKS_IDENTIFIER_आकार C_SIZEOF_STRUCT_LANG_IDENTIFIER
#अपरिभाषय LANG_HOOKS_वृक्षः_आकार
#परिभाषय LANG_HOOKS_वृक्षः_आकार c_वृक्षः_आकार
#अपरिभाषय LANG_HOOKS_FINISH
#परिभाषय LANG_HOOKS_FINISH c_common_finish
#अपरिभाषय LANG_HOOKS_OPTION_LANG_आवरणम्
#परिभाषय LANG_HOOKS_OPTION_LANG_आवरणम् c_common_option_lang_आवरणम्
#अपरिभाषय LANG_HOOKS_COMPLAIN_WRONG_LANG_P
#परिभाषय LANG_HOOKS_COMPLAIN_WRONG_LANG_P c_common_complain_wrong_lang_p
#अपरिभाषय LANG_HOOKS_INIT_OPTIONS_STRUCT
#परिभाषय LANG_HOOKS_INIT_OPTIONS_STRUCT c_common_init_options_struct
#अपरिभाषय LANG_HOOKS_INIT_OPTIONS
#परिभाषय LANG_HOOKS_INIT_OPTIONS c_common_init_options
#अपरिभाषय LANG_HOOKS_INITIALIZE_DIAGNOSTICS
#परिभाषय LANG_HOOKS_INITIALIZE_DIAGNOSTICS c_initialize_diagnostics
#अपरिभाषय LANG_HOOKS_HANDLE_OPTION
#परिभाषय LANG_HOOKS_HANDLE_OPTION c_common_handle_option
#अपरिभाषय LANG_HOOKS_POST_OPTIONS
#परिभाषय LANG_HOOKS_POST_OPTIONS c_common_post_options
#अपरिभाषय LANG_HOOKS_GET_ALIAS_समुच्चयः
#परिभाषय LANG_HOOKS_GET_ALIAS_समुच्चयः c_get_alias_समुच्चयः
#अपरिभाषय LANG_HOOKS_PARSE_FILE
#परिभाषय LANG_HOOKS_PARSE_FILE c_common_parse_file
#अपरिभाषय LANG_HOOKS_FINISH_INCOMPLETE_DECL
#परिभाषय LANG_HOOKS_FINISH_INCOMPLETE_DECL c_finish_incomplete_decl
#अपरिभाषय LANG_HOOKS_WARN_अप्रयुक्तम्_GLOBAL_DECL
#परिभाषय LANG_HOOKS_WARN_अप्रयुक्तम्_GLOBAL_DECL c_warn_अप्रयुक्तम्_global_decl
#अपरिभाषय LANG_HOOKS_PRINT_IDENTIFIER
#परिभाषय LANG_HOOKS_PRINT_IDENTIFIER c_print_identifier
#अपरिभाषय LANG_HOOKS_TYPES_COMPATIBLE_P
#परिभाषय LANG_HOOKS_TYPES_COMPATIBLE_P c_types_compatible_p
#अपरिभाषय LANG_HOOKS_MISSING_NORETURN_OK_P
#परिभाषय LANG_HOOKS_MISSING_NORETURN_OK_P c_missing_noreturn_ok_p
#अपरिभाषय LANG_HOOKS_खण्डम्_MAY_FALLTHRU
#परिभाषय LANG_HOOKS_खण्डम्_MAY_FALLTHRU c_खण्डम्_may_fallthru
#अपरिभाषय  LANG_HOOKS_BUILTIN_FUNCTION
#परिभाषय LANG_HOOKS_BUILTIN_FUNCTION c_builtin_function
#अपरिभाषय  LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE
#परिभाषय LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE c_builtin_function_ext_scope
#अपरिभाषय  LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL
#परिभाषय LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL \
  c_simulate_builtin_function_decl
#अपरिभाषय LANG_HOOKS_EMITS_BEGIN_STMT
#परिभाषय LANG_HOOKS_EMITS_BEGIN_STMT true
#अपरिभाषय LANG_HOOKS_FINALIZE_EARLY_DEBUG
#परिभाषय LANG_HOOKS_FINALIZE_EARLY_DEBUG c_common_finalize_early_debug
#अपरिभाषय LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE
#परिभाषय LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE c_reconstruct_complex_type

स्थिर ध्रुव scoped_attribute_specs *ध्रुव c_objc_attribute_सारणी[] =
{
  &std_attribute_सारणी,
  &c_common_gnu_attribute_सारणी,
  &c_common_clang_attribute_सारणी,
  &c_common_format_attribute_सारणी
};

#अपरिभाषय LANG_HOOKS_ATTRIBUTE_सारणी
#परिभाषय LANG_HOOKS_ATTRIBUTE_सारणी c_objc_attribute_सारणी

#अपरिभाषय LANG_HOOKS_वृक्षः_DUMP_DUMP_वृक्षः_FN
#परिभाषय LANG_HOOKS_वृक्षः_DUMP_DUMP_वृक्षः_FN c_dump_वृक्षः

#अपरिभाषय LANG_HOOKS_SIMULATE_ENUM_DECL
#परिभाषय LANG_HOOKS_SIMULATE_ENUM_DECL c_simulate_enum_decl
#अपरिभाषय LANG_HOOKS_SIMULATE_लेखः_DECL
#परिभाषय LANG_HOOKS_SIMULATE_लेखः_DECL c_simulate_लेखः_decl
#अपरिभाषय LANG_HOOKS_TYPE_FOR_बहुलकम्
#परिभाषय LANG_HOOKS_TYPE_FOR_बहुलकम् c_common_type_for_बहुलकम्
#अपरिभाषय LANG_HOOKS_TYPE_FOR_आकार
#परिभाषय LANG_HOOKS_TYPE_FOR_आकार c_common_type_for_आकार
#अपरिभाषय LANG_HOOKS_INCOMPLETE_TYPE_ERROR
#परिभाषय LANG_HOOKS_INCOMPLETE_TYPE_ERROR c_incomplete_type_error
#अपरिभाषय LANG_HOOKS_TYPE_PROMOTES_गन्तव्यम्
#परिभाषय LANG_HOOKS_TYPE_PROMOTES_गन्तव्यम् c_type_promotes_गन्तव्यम्
#अपरिभाषय LANG_HOOKS_पञ्जिकाकोशः_BUILTIN_TYPE
#परिभाषय LANG_HOOKS_पञ्जिकाकोशः_BUILTIN_TYPE c_पञ्जिकाकोशः_builtin_type
#अपरिभाषय LANG_HOOKS_गन्तव्यम्_TARGET_CHARSET
#परिभाषय LANG_HOOKS_गन्तव्यम्_TARGET_CHARSET c_common_गन्तव्यम्_target_charset
#अपरिभाषय LANG_HOOKS_व्यञ्जकम्_गन्तव्यम्_DECL
#परिभाषय LANG_HOOKS_व्यञ्जकम्_गन्तव्यम्_DECL c_व्यञ्जकम्_गन्तव्यम्_decl

/* The C front end's scoping structure is very different from
   that expected by the language-independent code; it is best
   to disable getdecls.
   This means it must also provide its own write_globals.  */

#अपरिभाषय LANG_HOOKS_GETDECLS
#परिभाषय LANG_HOOKS_GETDECLS hook_वृक्षः_void_null

/* Hooks for tree gimplification.  */
#अपरिभाषय LANG_HOOKS_GIMPLIFY_व्यञ्जकम्
#परिभाषय LANG_HOOKS_GIMPLIFY_व्यञ्जकम् c_gimplify_व्यञ्जकम्

#अपरिभाषय LANG_HOOKS_TYPE_DWARF_ATTRIBUTE
#परिभाषय LANG_HOOKS_TYPE_DWARF_ATTRIBUTE c_type_dwarf_attribute

#अपरिभाषय LANG_HOOKS_OMP_PREDETERMINED_SHARING
#परिभाषय LANG_HOOKS_OMP_PREDETERMINED_SHARING c_omp_predetermined_sharing

#अपरिभाषय LANG_HOOKS_OMP_PREDETERMINED_MAPPING
#परिभाषय LANG_HOOKS_OMP_PREDETERMINED_MAPPING c_omp_predetermined_mapping

#अपरिभाषय LANG_HOOKS_OMP_CLAUSE_COPY_CTOR
#परिभाषय LANG_HOOKS_OMP_CLAUSE_COPY_CTOR c_omp_clause_copy_ctor

#अपरिभाषय LANG_HOOKS_OMP_CLAUSE_नियोजय_OP
#परिभाषय LANG_HOOKS_OMP_CLAUSE_नियोजय_OP c_omp_clause_copy_ctor

#अपरिभाषय LANG_HOOKS_OMP_FINISH_MAPPER_CLAUSES
#परिभाषय LANG_HOOKS_OMP_FINISH_MAPPER_CLAUSES c_omp_finish_mapper_clauses

#अपरिभाषय LANG_HOOKS_OMP_MAPPER_LOOKUP
#परिभाषय LANG_HOOKS_OMP_MAPPER_LOOKUP c_omp_mapper_lookup

#अपरिभाषय LANG_HOOKS_OMP_EXTRACT_MAPPER_DIRECTIVE
#परिभाषय LANG_HOOKS_OMP_EXTRACT_MAPPER_DIRECTIVE c_omp_extract_mapper_directive

#अपरिभाषय LANG_HOOKS_OMP_MAP_ARRAY_SECTION
#परिभाषय LANG_HOOKS_OMP_MAP_ARRAY_SECTION c_omp_map_array_section

#अपरिभाषय LANG_HOOKS_वृक्षः_INLINING_VAR_MOD_TYPE_P
#परिभाषय LANG_HOOKS_वृक्षः_INLINING_VAR_MOD_TYPE_P c_var_mod_p
#यदि_अन्तः /* GCC_C_OBJC_COMMON */
