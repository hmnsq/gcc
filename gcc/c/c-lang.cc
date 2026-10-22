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

ಎಣಿಕೆ c_language_ಬಗೆ c_language = clk_c;

/* Lang hooks common to C and ObjC are declared in c-objc-common.h;
   consequently, there should be very few hooks below.  */

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_NAME
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_NAME "GNU C"
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_INIT
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_INIT c_objc_common_init
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_INIT_TS
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_INIT_TS c_common_init_ts
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ENUM_UNDERLYING_ತಳ_TYPE
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ENUM_UNDERLYING_ತಳ_TYPE c_enum_underlying_ತಳ_type

#ಆದರೆ CHECKING_P
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_ಸತತ_LANG_SELFTESTS
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_ಸತತ_LANG_SELFTESTS selftest::ಸತತ_c_tests
#ಆದರೆ_ಅಂತ್ಯ /* #if CHECKING_P */

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_GET_SUBSTRING_LOCATION
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_GET_SUBSTRING_LOCATION c_get_substring_location

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LANG_HOOKS_GET_SARIF_ಮೂಲ_LANGUAGE
#ವ್ಯಾಖ್ಯಾನಿಸು LANG_HOOKS_GET_SARIF_ಮೂಲ_LANGUAGE c_get_sarif_ಮೂಲ_language

/* Each front end provides its own lang hook initializer.  */
ರಚನೆ lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Get a value for the SARIF v2.1.0 "artifact.sourceLanguage" property,
   based on the list in SARIF v2.1.0 Appendix J.  */

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *
c_get_sarif_ಮೂಲ_language (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)
{
  ಹಿಂತಿರುಗಿ "c";
}

/* Implement c-family hook to register language-specific features for
   __has_{feature,extension}.  */

ಶೂನ್ಯ
c_family_ರಿಜಿಸ್ಟರ್_lang_features ()
{
  c_ರಿಜಿಸ್ಟರ್_features ();
}

#ಆದರೆ CHECKING_P

ನಾಮಾಕಾಶ selftest {

/* Implementation of LANG_HOOKS_RUN_LANG_SELFTESTS for the C frontend.  */

ಶೂನ್ಯ
ಸತತ_c_tests (ಶೂನ್ಯ)
{
  /* Run selftests shared within the C family.  */
  c_family_tests ();

  /* Additional C-specific tests.  */
}

} // namespace selftest

#ಆದರೆ_ಅಂತ್ಯ /* #if CHECKING_P */


#ಅನ್ತರ್ಭಾವ "gtype-c.h"
