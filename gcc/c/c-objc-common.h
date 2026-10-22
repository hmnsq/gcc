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

#अगर_अघोषित GCC_C_OBJC_COMMON
#घोषणा GCC_C_OBJC_COMMON

/* Implemented in c-objc-common.cc.  */
बाह्य व्योम c_register_features ();

/* Lang hooks that are shared between C and ObjC are defined here.  Hooks
   specific to C or ObjC go in c-lang.cc and objc/objc-lang.cc, respectively.  */

#अघोषित LANG_HOOKS_IDENTIFIER_आकार
#घोषणा LANG_HOOKS_IDENTIFIER_आकार C_SIZEOF_STRUCT_LANG_IDENTIFIER
#अघोषित LANG_HOOKS_वृक्ष_आकार
#घोषणा LANG_HOOKS_वृक्ष_आकार c_वृक्ष_आकार
#अघोषित LANG_HOOKS_FINISH
#घोषणा LANG_HOOKS_FINISH c_common_finish
#अघोषित LANG_HOOKS_OPTION_LANG_MASK
#घोषणा LANG_HOOKS_OPTION_LANG_MASK c_common_option_lang_mask
#अघोषित LANG_HOOKS_COMPLAIN_WRONG_LANG_P
#घोषणा LANG_HOOKS_COMPLAIN_WRONG_LANG_P c_common_complain_wrong_lang_p
#अघोषित LANG_HOOKS_INIT_OPTIONS_STRUCT
#घोषणा LANG_HOOKS_INIT_OPTIONS_STRUCT c_common_init_options_struct
#अघोषित LANG_HOOKS_INIT_OPTIONS
#घोषणा LANG_HOOKS_INIT_OPTIONS c_common_init_options
#अघोषित LANG_HOOKS_INITIALIZE_DIAGNOSTICS
#घोषणा LANG_HOOKS_INITIALIZE_DIAGNOSTICS c_initialize_diagnostics
#अघोषित LANG_HOOKS_HANDLE_OPTION
#घोषणा LANG_HOOKS_HANDLE_OPTION c_common_handle_option
#अघोषित LANG_HOOKS_POST_OPTIONS
#घोषणा LANG_HOOKS_POST_OPTIONS c_common_post_options
#अघोषित LANG_HOOKS_GET_ALIAS_SET
#घोषणा LANG_HOOKS_GET_ALIAS_SET c_get_alias_set
#अघोषित LANG_HOOKS_PARSE_FILE
#घोषणा LANG_HOOKS_PARSE_FILE c_common_parse_file
#अघोषित LANG_HOOKS_FINISH_INCOMPLETE_DECL
#घोषणा LANG_HOOKS_FINISH_INCOMPLETE_DECL c_finish_incomplete_decl
#अघोषित LANG_HOOKS_WARN_UNUSED_GLOBAL_DECL
#घोषणा LANG_HOOKS_WARN_UNUSED_GLOBAL_DECL c_warn_unused_global_decl
#अघोषित LANG_HOOKS_PRINT_IDENTIFIER
#घोषणा LANG_HOOKS_PRINT_IDENTIFIER c_print_identifier
#अघोषित LANG_HOOKS_TYPES_COMPATIBLE_P
#घोषणा LANG_HOOKS_TYPES_COMPATIBLE_P c_types_compatible_p
#अघोषित LANG_HOOKS_MISSING_NORETURN_OK_P
#घोषणा LANG_HOOKS_MISSING_NORETURN_OK_P c_missing_noreturn_ok_p
#अघोषित LANG_HOOKS_BLOCK_MAY_FALLTHRU
#घोषणा LANG_HOOKS_BLOCK_MAY_FALLTHRU c_block_may_fallthru
#अघोषित  LANG_HOOKS_BUILTIN_FUNCTION
#घोषणा LANG_HOOKS_BUILTIN_FUNCTION c_builtin_function
#अघोषित  LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE
#घोषणा LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE c_builtin_function_ext_scope
#अघोषित  LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL
#घोषणा LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL \
  c_simulate_builtin_function_decl
#अघोषित LANG_HOOKS_EMITS_BEGIN_STMT
#घोषणा LANG_HOOKS_EMITS_BEGIN_STMT true
#अघोषित LANG_HOOKS_FINALIZE_EARLY_DEBUG
#घोषणा LANG_HOOKS_FINALIZE_EARLY_DEBUG c_common_finalize_early_debug
#अघोषित LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE
#घोषणा LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE c_reconstruct_complex_type

अटल स्थिर scoped_attribute_specs *स्थिर c_objc_attribute_table[] =
{
  &std_attribute_table,
  &c_common_gnu_attribute_table,
  &c_common_clang_attribute_table,
  &c_common_format_attribute_table
};

#अघोषित LANG_HOOKS_ATTRIBUTE_TABLE
#घोषणा LANG_HOOKS_ATTRIBUTE_TABLE c_objc_attribute_table

#अघोषित LANG_HOOKS_वृक्ष_DUMP_DUMP_वृक्ष_FN
#घोषणा LANG_HOOKS_वृक्ष_DUMP_DUMP_वृक्ष_FN c_dump_वृक्ष

#अघोषित LANG_HOOKS_SIMULATE_ENUM_DECL
#घोषणा LANG_HOOKS_SIMULATE_ENUM_DECL c_simulate_enum_decl
#अघोषित LANG_HOOKS_SIMULATE_RECORD_DECL
#घोषणा LANG_HOOKS_SIMULATE_RECORD_DECL c_simulate_record_decl
#अघोषित LANG_HOOKS_TYPE_FOR_MODE
#घोषणा LANG_HOOKS_TYPE_FOR_MODE c_common_type_for_mode
#अघोषित LANG_HOOKS_TYPE_FOR_आकार
#घोषणा LANG_HOOKS_TYPE_FOR_आकार c_common_type_for_आकार
#अघोषित LANG_HOOKS_INCOMPLETE_TYPE_ERROR
#घोषणा LANG_HOOKS_INCOMPLETE_TYPE_ERROR c_incomplete_type_error
#अघोषित LANG_HOOKS_TYPE_PROMOTES_TO
#घोषणा LANG_HOOKS_TYPE_PROMOTES_TO c_type_promotes_to
#अघोषित LANG_HOOKS_REGISTER_BUILTIN_TYPE
#घोषणा LANG_HOOKS_REGISTER_BUILTIN_TYPE c_register_builtin_type
#अघोषित LANG_HOOKS_TO_TARGET_CHARSET
#घोषणा LANG_HOOKS_TO_TARGET_CHARSET c_common_to_target_charset
#अघोषित LANG_HOOKS_व्यंजक_TO_DECL
#घोषणा LANG_HOOKS_व्यंजक_TO_DECL c_व्यंजक_to_decl

/* The C front end's scoping structure is very different from
   that expected by the language-independent code; it is best
   to disable getdecls.
   This means it must also provide its own write_globals.  */

#अघोषित LANG_HOOKS_GETDECLS
#घोषणा LANG_HOOKS_GETDECLS hook_वृक्ष_void_null

/* Hooks for tree gimplification.  */
#अघोषित LANG_HOOKS_GIMPLIFY_व्यंजक
#घोषणा LANG_HOOKS_GIMPLIFY_व्यंजक c_gimplify_व्यंजक

#अघोषित LANG_HOOKS_TYPE_DWARF_ATTRIBUTE
#घोषणा LANG_HOOKS_TYPE_DWARF_ATTRIBUTE c_type_dwarf_attribute

#अघोषित LANG_HOOKS_OMP_PREDETERMINED_SHARING
#घोषणा LANG_HOOKS_OMP_PREDETERMINED_SHARING c_omp_predetermined_sharing

#अघोषित LANG_HOOKS_OMP_PREDETERMINED_MAPPING
#घोषणा LANG_HOOKS_OMP_PREDETERMINED_MAPPING c_omp_predetermined_mapping

#अघोषित LANG_HOOKS_OMP_CLAUSE_COPY_CTOR
#घोषणा LANG_HOOKS_OMP_CLAUSE_COPY_CTOR c_omp_clause_copy_ctor

#अघोषित LANG_HOOKS_OMP_CLAUSE_ASSIGN_OP
#घोषणा LANG_HOOKS_OMP_CLAUSE_ASSIGN_OP c_omp_clause_copy_ctor

#अघोषित LANG_HOOKS_OMP_FINISH_MAPPER_CLAUSES
#घोषणा LANG_HOOKS_OMP_FINISH_MAPPER_CLAUSES c_omp_finish_mapper_clauses

#अघोषित LANG_HOOKS_OMP_MAPPER_LOOKUP
#घोषणा LANG_HOOKS_OMP_MAPPER_LOOKUP c_omp_mapper_lookup

#अघोषित LANG_HOOKS_OMP_EXTRACT_MAPPER_DIRECTIVE
#घोषणा LANG_HOOKS_OMP_EXTRACT_MAPPER_DIRECTIVE c_omp_extract_mapper_directive

#अघोषित LANG_HOOKS_OMP_MAP_ARRAY_SECTION
#घोषणा LANG_HOOKS_OMP_MAP_ARRAY_SECTION c_omp_map_array_section

#अघोषित LANG_HOOKS_वृक्ष_INLINING_VAR_MOD_TYPE_P
#घोषणा LANG_HOOKS_वृक्ष_INLINING_VAR_MOD_TYPE_P c_var_mod_p
#पूर्ण_अगर /* GCC_C_OBJC_COMMON */
