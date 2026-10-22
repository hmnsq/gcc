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


#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "c-tree.h"
#ضمن "langhooks.h"
#ضمن "langhooks-def.h"
#ضمن "c-objc-common.h"
#ضمن "c-family/c-pragma.h"
#ضمن "c-parser.h"

تعداد c_language_قسم c_language = clk_c;

/* Lang hooks common to C and ObjC are declared in c-objc-common.h;
   consequently, there should be very few hooks below.  */

#تعریف_رد LANG_HOOKS_NAME
#تعریف_کرو LANG_HOOKS_NAME "GNU C"
#تعریف_رد LANG_HOOKS_INIT
#تعریف_کرو LANG_HOOKS_INIT c_objc_common_init
#تعریف_رد LANG_HOOKS_INIT_TS
#تعریف_کرو LANG_HOOKS_INIT_TS c_common_init_ts
#تعریف_رد LANG_HOOKS_ENUM_UNDERLYING_ادھار_TYPE
#تعریف_کرو LANG_HOOKS_ENUM_UNDERLYING_ادھار_TYPE c_enum_underlying_ادھار_type

#إذا CHECKING_P
#تعریف_رد LANG_HOOKS_لگاتار_LANG_SELFTESTS
#تعریف_کرو LANG_HOOKS_لگاتار_LANG_SELFTESTS selftest::لگاتار_c_tests
#جے_انت /* #if CHECKING_P */

#تعریف_رد LANG_HOOKS_GET_SUBSTRING_LOCATION
#تعریف_کرو LANG_HOOKS_GET_SUBSTRING_LOCATION c_get_substring_location

#تعریف_رد LANG_HOOKS_GET_SARIF_سروت_LANGUAGE
#تعریف_کرو LANG_HOOKS_GET_SARIF_سروت_LANGUAGE c_get_sarif_سروت_language

/* Each front end provides its own lang hook initializer.  */
بنية lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Get a value for the SARIF v2.1.0 "artifact.sourceLanguage" property,
   based on the list in SARIF v2.1.0 Appendix J.  */

ثابت حرف *
c_get_sarif_سروت_language (ثابت حرف *)
{
  أرجع "c";
}

/* Implement c-family hook to register language-specific features for
   __has_{feature,extension}.  */

فراغ
c_family_رجسٹر_lang_features ()
{
  c_رجسٹر_features ();
}

#إذا CHECKING_P

نطاق selftest {

/* Implementation of LANG_HOOKS_RUN_LANG_SELFTESTS for the C frontend.  */

فراغ
لگاتار_c_tests (فراغ)
{
  /* Run selftests shared within the C family.  */
  c_family_tests ();

  /* Additional C-specific tests.  */
}

} // namespace selftest

#جے_انت /* #if CHECKING_P */


#ضمن "gtype-c.h"
