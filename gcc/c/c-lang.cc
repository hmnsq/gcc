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

تعداد c_language_نوع c_language = clk_c;

/* Lang hooks common to C and ObjC are declared in c-objc-common.h;
   consequently, there should be very few hooks below.  */

#لغو_تعریف LANG_HOOKS_NAME
#تعریف_کن LANG_HOOKS_NAME "GNU C"
#لغو_تعریف LANG_HOOKS_INIT
#تعریف_کن LANG_HOOKS_INIT c_objc_common_init
#لغو_تعریف LANG_HOOKS_INIT_TS
#تعریف_کن LANG_HOOKS_INIT_TS c_common_init_ts
#لغو_تعریف LANG_HOOKS_ENUM_UNDERLYING_پایه_TYPE
#تعریف_کن LANG_HOOKS_ENUM_UNDERLYING_پایه_TYPE c_enum_underlying_پایه_type

#إذا CHECKING_P
#لغو_تعریف LANG_HOOKS_پیاپی_LANG_SELFTESTS
#تعریف_کن LANG_HOOKS_پیاپی_LANG_SELFTESTS selftest::پیاپی_c_tests
#پایان_اگر /* #if CHECKING_P */

#لغو_تعریف LANG_HOOKS_GET_SUBSTRING_LOCATION
#تعریف_کن LANG_HOOKS_GET_SUBSTRING_LOCATION c_get_substring_location

#لغو_تعریف LANG_HOOKS_GET_SARIF_منبع_LANGUAGE
#تعریف_کن LANG_HOOKS_GET_SARIF_منبع_LANGUAGE c_get_sarif_منبع_language

/* Each front end provides its own lang hook initializer.  */
بنية lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Get a value for the SARIF v2.1.0 "artifact.sourceLanguage" property,
   based on the list in SARIF v2.1.0 Appendix J.  */

ثابت حرف *
c_get_sarif_منبع_language (ثابت حرف *)
{
  أرجع "c";
}

/* Implement c-family hook to register language-specific features for
   __has_{feature,extension}.  */

فراغ
c_family_ثبات_lang_features ()
{
  c_ثبات_features ();
}

#إذا CHECKING_P

نطاق selftest {

/* Implementation of LANG_HOOKS_RUN_LANG_SELFTESTS for the C frontend.  */

فراغ
پیاپی_c_tests (فراغ)
{
  /* Run selftests shared within the C family.  */
  c_family_tests ();

  /* Additional C-specific tests.  */
}

} // namespace selftest

#پایان_اگر /* #if CHECKING_P */


#ضمن "gtype-c.h"
