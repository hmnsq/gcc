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


#شامل "config.h"
#شامل "system.h"
#شامل "coretypes.h"
#شامل "c-tree.h"
#شامل "langhooks.h"
#شامل "langhooks-def.h"
#شامل "c-objc-common.h"
#شامل "c-family/c-pragma.h"
#شامل "c-parser.h"

شمار c_language_قسم c_language = clk_c;

/* Lang hooks common to C and ObjC are declared in c-objc-common.h;
   consequently, there should be very few hooks below.  */

#تعریف_منسوخ LANG_HOOKS_NAME
#تعریف_کرو LANG_HOOKS_NAME "GNU C"
#تعریف_منسوخ LANG_HOOKS_INIT
#تعریف_کرو LANG_HOOKS_INIT c_objc_common_init
#تعریف_منسوخ LANG_HOOKS_INIT_TS
#تعریف_کرو LANG_HOOKS_INIT_TS c_common_init_ts
#تعریف_منسوخ LANG_HOOKS_ENUM_UNDERLYING_بنیاد_TYPE
#تعریف_کرو LANG_HOOKS_ENUM_UNDERLYING_بنیاد_TYPE c_enum_underlying_بنیاد_type

#اگر CHECKING_P
#تعریف_منسوخ LANG_HOOKS_تسلسل_LANG_SELFTESTS
#تعریف_کرو LANG_HOOKS_تسلسل_LANG_SELFTESTS selftest::تسلسل_c_tests
#اگر_ختم /* #if CHECKING_P */

#تعریف_منسوخ LANG_HOOKS_GET_SUBSTRING_LOCATION
#تعریف_کرو LANG_HOOKS_GET_SUBSTRING_LOCATION c_get_substring_location

#تعریف_منسوخ LANG_HOOKS_GET_SARIF_ماخذ_LANGUAGE
#تعریف_کرو LANG_HOOKS_GET_SARIF_ماخذ_LANGUAGE c_get_sarif_ماخذ_language

/* Each front end provides its own lang hook initializer.  */
ساخت lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Get a value for the SARIF v2.1.0 "artifact.sourceLanguage" property,
   based on the list in SARIF v2.1.0 Appendix J.  */

ثابت حرف *
c_get_sarif_ماخذ_language (ثابت حرف *)
{
  واپس "c";
}

/* Implement c-family hook to register language-specific features for
   __has_{feature,extension}.  */

خالی
c_family_رجسٹر_lang_features ()
{
  c_رجسٹر_features ();
}

#اگر CHECKING_P

نامخلا selftest {

/* Implementation of LANG_HOOKS_RUN_LANG_SELFTESTS for the C frontend.  */

خالی
تسلسل_c_tests (خالی)
{
  /* Run selftests shared within the C family.  */
  c_family_tests ();

  /* Additional C-specific tests.  */
}

} // namespace selftest

#اگر_ختم /* #if CHECKING_P */


#شامل "gtype-c.h"
