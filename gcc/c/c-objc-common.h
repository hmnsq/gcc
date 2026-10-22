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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GCC_C_OBJC_COMMON
#ವ್ಯಾಖ್ಯಾನಿಸು GCC_C_OBJC_COMMON

/* Implemented in c-objc-common.cc.  */
ಬಾಹ್ಯ ಶೂನ್ಯ c_ರಿಜಿಸ್ಟರ್_features ();

/* Lang hooks that are shared between C and ObjC are defined here.  Hooks
   specific to C or ObjC go in c-lang.cc and objc/objc-lang.cc, respectively.  */

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_IDENTIFIER_ಗಾತ್ರ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_IDENTIFIER_ಗಾತ್ರ C_SIZEOF_STRUCT_LANG_IDENTIFIER
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ವೃಕ್ಷ_ಗಾತ್ರ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ವೃಕ್ಷ_ಗಾತ್ರ c_ವೃಕ್ಷ_ಗಾತ್ರ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ಮುಕ್ತಾಯ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ಮುಕ್ತಾಯ c_common_ಮುಕ್ತಾಯ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OPTION_LANG_ಮುಖವಾಡ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OPTION_LANG_ಮುಖವಾಡ c_common_option_lang_ಮುಖವಾಡ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_COMPLAIN_WRONG_LANG_P
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_COMPLAIN_WRONG_LANG_P c_common_complain_wrong_lang_p
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_INIT_OPTIONS_STRUCT
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_INIT_OPTIONS_STRUCT c_common_init_options_struct
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_INIT_OPTIONS
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_INIT_OPTIONS c_common_init_options
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_INITIALIZE_DIAGNOSTICS
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_INITIALIZE_DIAGNOSTICS c_initialize_diagnostics
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_HANDLE_OPTION
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_HANDLE_OPTION c_common_handle_option
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_POST_OPTIONS
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_POST_OPTIONS c_common_post_options
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_GET_ALIAS_ಗಣ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_GET_ALIAS_ಗಣ c_get_alias_ಗಣ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_PARSE_FILE
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_PARSE_FILE c_common_parse_file
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ಮುಕ್ತಾಯ_INCOMPLETE_DECL
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ಮುಕ್ತಾಯ_INCOMPLETE_DECL c_ಮುಕ್ತಾಯ_incomplete_decl
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_WARN_ಬಳಸದ_GLOBAL_DECL
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_WARN_ಬಳಸದ_GLOBAL_DECL c_warn_ಬಳಸದ_global_decl
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_PRINT_IDENTIFIER
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_PRINT_IDENTIFIER c_print_identifier
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_TYPES_COMPATIBLE_P
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_TYPES_COMPATIBLE_P c_types_compatible_p
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_MISSING_NORETURN_OK_P
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_MISSING_NORETURN_OK_P c_missing_noreturn_ok_p
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ಖಂಡ_MAY_FALLTHRU
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ಖಂಡ_MAY_FALLTHRU c_ಖಂಡ_may_fallthru
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು  LANG_HOOKS_BUILTIN_FUNCTION
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_BUILTIN_FUNCTION c_builtin_function
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು  LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_BUILTIN_FUNCTION_EXT_SCOPE c_builtin_function_ext_scope
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು  LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_SIMULATE_BUILTIN_FUNCTION_DECL \
  c_simulate_builtin_function_decl
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_EMITS_BEGIN_STMT
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_EMITS_BEGIN_STMT true
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_FINALIZE_EARLY_DEBUG
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_FINALIZE_EARLY_DEBUG c_common_finalize_early_debug
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_RECONSTRUCT_COMPLEX_TYPE c_reconstruct_complex_type

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ scoped_attribute_specs *ಸ್ಥಿರಾಂಕ c_objc_attribute_ಕೋಷ್ಟಕ[] =
{
  &std_attribute_ಕೋಷ್ಟಕ,
  &c_common_gnu_attribute_ಕೋಷ್ಟಕ,
  &c_common_clang_attribute_ಕೋಷ್ಟಕ,
  &c_common_format_attribute_ಕೋಷ್ಟಕ
};

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ATTRIBUTE_ಕೋಷ್ಟಕ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ATTRIBUTE_ಕೋಷ್ಟಕ c_objc_attribute_ಕೋಷ್ಟಕ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ವೃಕ್ಷ_DUMP_DUMP_ವೃಕ್ಷ_FN
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ವೃಕ್ಷ_DUMP_DUMP_ವೃಕ್ಷ_FN c_dump_ವೃಕ್ಷ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_SIMULATE_ENUM_DECL
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_SIMULATE_ENUM_DECL c_simulate_enum_decl
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_SIMULATE_ದಾಖಲೆ_DECL
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_SIMULATE_ದಾಖಲೆ_DECL c_simulate_ದಾಖಲೆ_decl
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_TYPE_FOR_ಬಹುಲಕ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_TYPE_FOR_ಬಹುಲಕ c_common_type_for_ಬಹುಲಕ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_TYPE_FOR_ಗಾತ್ರ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_TYPE_FOR_ಗಾತ್ರ c_common_type_for_ಗಾತ್ರ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_INCOMPLETE_TYPE_ERROR
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_INCOMPLETE_TYPE_ERROR c_incomplete_type_error
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_TYPE_PROMOTES_ಗಮ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_TYPE_PROMOTES_ಗಮ್ಯ c_type_promotes_ಗಮ್ಯ
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ರಿಜಿಸ್ಟರ್_BUILTIN_TYPE
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ರಿಜಿಸ್ಟರ್_BUILTIN_TYPE c_ರಿಜಿಸ್ಟರ್_builtin_type
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ಗಮ್ಯ_ಗುರಿ_CHARSET
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ಗಮ್ಯ_ಗುರಿ_CHARSET c_common_ಗಮ್ಯ_ಗುರಿ_charset
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ಅಭಿವ್ಯಕ್ತಿ_ಗಮ್ಯ_DECL
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ಅಭಿವ್ಯಕ್ತಿ_ಗಮ್ಯ_DECL c_ಅಭಿವ್ಯಕ್ತಿ_ಗಮ್ಯ_decl

/* The C front end's scoping structure is very different from
   that expected by the language-independent code; it is best
   to disable getdecls.
   This means it must also provide its own write_globals.  */

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_GETDECLS
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_GETDECLS hook_ವೃಕ್ಷ_void_null

/* Hooks for tree gimplification.  */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_GIMPLIFY_ಅಭಿವ್ಯಕ್ತಿ
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_GIMPLIFY_ಅಭಿವ್ಯಕ್ತಿ c_gimplify_ಅಭಿವ್ಯಕ್ತಿ

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_TYPE_DWARF_ATTRIBUTE
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_TYPE_DWARF_ATTRIBUTE c_type_dwarf_attribute

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OMP_PREDETERMINED_SHARING
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OMP_PREDETERMINED_SHARING c_omp_predetermined_sharing

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OMP_PREDETERMINED_MAPPING
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OMP_PREDETERMINED_MAPPING c_omp_predetermined_mapping

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OMP_CLAUSE_COPY_CTOR
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OMP_CLAUSE_COPY_CTOR c_omp_clause_copy_ctor

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OMP_CLAUSE_ನಿಯೋಜಿಸು_OP
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OMP_CLAUSE_ನಿಯೋಜಿಸು_OP c_omp_clause_copy_ctor

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OMP_ಮುಕ್ತಾಯ_MAPPER_CLAUSES
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OMP_ಮುಕ್ತಾಯ_MAPPER_CLAUSES c_omp_ಮುಕ್ತಾಯ_mapper_clauses

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OMP_MAPPER_LOOKUP
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OMP_MAPPER_LOOKUP c_omp_mapper_lookup

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OMP_ಹೊರತೆಗೆ_MAPPER_DIRECTIVE
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OMP_ಹೊರತೆಗೆ_MAPPER_DIRECTIVE c_omp_ಹೊರತೆಗೆ_mapper_directive

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_OMP_MAP_ARRAY_SECTION
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_OMP_MAP_ARRAY_SECTION c_omp_map_array_section

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ವೃಕ್ಷ_INLINING_VAR_MOD_TYPE_P
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ವೃಕ್ಷ_INLINING_VAR_MOD_TYPE_P c_var_mod_p
#ಆದರೆ_ಅಂತ್ಯ /* GCC_C_OBJC_COMMON */
