/* Language-specific hook definitions for C front end.
   Copyright (C) 1991-2026 Free Software Foundation, Inc.

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


#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "langhooks.h"
#ಅನ್ತರ್ಭಾವ "langhooks-def.h"
#ಅನ್ತರ್ಭಾವ "c-objc-common.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-pragma.h"
#ಅನ್ತರ್ಭಾವ "c-parser.h"

ಗಣನಾ c_language_kind c_language = clk_c;

/* Lang hooks common to C and ObjC are declared in c-objc-common.h;
   consequently, there should be very few hooks below.  */

#undef LANG_HOOKS_NAME
#define LANG_HOOKS_NAME "GNU C"
#undef LANG_HOOKS_INIT
#define LANG_HOOKS_INIT c_objc_common_init
#undef LANG_HOOKS_INIT_TS
#define LANG_HOOKS_INIT_TS c_common_init_ts
#undef LANG_HOOKS_ENUM_UNDERLYING_BASE_TYPE
#define LANG_HOOKS_ENUM_UNDERLYING_BASE_TYPE c_enum_underlying_base_type

#ಯದಿ CHECKING_P
#undef LANG_HOOKS_RUN_LANG_SELFTESTS
#define LANG_HOOKS_RUN_LANG_SELFTESTS selftest::run_c_tests
#endif /* #if CHECKING_P */

#undef LANG_HOOKS_GET_SUBSTRING_LOCATION
#define LANG_HOOKS_GET_SUBSTRING_LOCATION c_get_substring_location

#undef LANG_HOOKS_GET_SARIF_SOURCE_LANGUAGE
#define LANG_HOOKS_GET_SARIF_SOURCE_LANGUAGE c_get_sarif_source_language

/* Each front end provides its own lang hook initializer.  */
ಸಂರಚನಾ lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Get a value for the SARIF v2.1.0 "artifact.sourceLanguage" property,
   based on the list in SARIF v2.1.0 Appendix J.  */

ಧ್ರುವ ವರ್ಣ *
c_get_sarif_source_language (ಧ್ರುವ ವರ್ಣ *)
{
  ಪ್ರತ್ಯಾಗಮ "c";
}

/* Implement c-family hook to register language-specific features for
   __has_{feature,extension}.  */

ಶೂನ್ಯ
c_family_register_lang_features ()
{
  c_register_features ();
}

#ಯದಿ CHECKING_P

ನಾಮಾಕಾಶ selftest {

/* Implementation of LANG_HOOKS_RUN_LANG_SELFTESTS for the C frontend.  */

ಶೂನ್ಯ
run_c_tests (ಶೂನ್ಯ)
{
  /* Run selftests shared within the C family.  */
  c_family_tests ();

  /* Additional C-specific tests.  */
}

} // namespace selftest

#endif /* #if CHECKING_P */


#ಅನ್ತರ್ಭಾವ "gtype-c.h"
