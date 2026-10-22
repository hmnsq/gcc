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


#अन्तर्भाव "config.h"
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "langhooks.h"
#अन्तर्भाव "langhooks-def.h"
#अन्तर्भाव "c-objc-common.h"
#अन्तर्भाव "c-family/c-pragma.h"
#अन्तर्भाव "c-parser.h"

गणना c_language_विधा c_language = clk_c;

/* Lang hooks common to C and ObjC are declared in c-objc-common.h;
   consequently, there should be very few hooks below.  */

#अपरिभाषय LANG_HOOKS_NAME
#परिभाषय LANG_HOOKS_NAME "GNU C"
#अपरिभाषय LANG_HOOKS_INIT
#परिभाषय LANG_HOOKS_INIT c_objc_common_init
#अपरिभाषय LANG_HOOKS_INIT_TS
#परिभाषय LANG_HOOKS_INIT_TS c_common_init_ts
#अपरिभाषय LANG_HOOKS_ENUM_UNDERLYING_आधारः_TYPE
#परिभाषय LANG_HOOKS_ENUM_UNDERLYING_आधारः_TYPE c_enum_underlying_आधारः_type

#यदि CHECKING_P
#अपरिभाषय LANG_HOOKS_सततम्_LANG_SELFTESTS
#परिभाषय LANG_HOOKS_सततम्_LANG_SELFTESTS selftest::सततम्_c_tests
#यदि_अन्तः /* #if CHECKING_P */

#अपरिभाषय LANG_HOOKS_GET_SUBSTRING_LOCATION
#परिभाषय LANG_HOOKS_GET_SUBSTRING_LOCATION c_get_substring_location

#अपरिभाषय LANG_HOOKS_GET_SARIF_SOURCE_LANGUAGE
#परिभाषय LANG_HOOKS_GET_SARIF_SOURCE_LANGUAGE c_get_sarif_source_language

/* Each front end provides its own lang hook initializer.  */
संरचना lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Get a value for the SARIF v2.1.0 "artifact.sourceLanguage" property,
   based on the list in SARIF v2.1.0 Appendix J.  */

ध्रुव वर्ण *
c_get_sarif_source_language (ध्रुव वर्ण *)
{
  प्रत्यागम "c";
}

/* Implement c-family hook to register language-specific features for
   __has_{feature,extension}.  */

शून्य
c_family_पञ्जिकाकोशः_lang_features ()
{
  c_पञ्जिकाकोशः_features ();
}

#यदि CHECKING_P

नामाकाश selftest {

/* Implementation of LANG_HOOKS_RUN_LANG_SELFTESTS for the C frontend.  */

शून्य
सततम्_c_tests (शून्य)
{
  /* Run selftests shared within the C family.  */
  c_family_tests ();

  /* Additional C-specific tests.  */
}

} // namespace selftest

#यदि_अन्तः /* #if CHECKING_P */


#अन्तर्भाव "gtype-c.h"
