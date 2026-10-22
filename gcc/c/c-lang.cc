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


#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "langhooks.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "langhooks-def.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-objc-common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-pragma.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-parser.h"

ਗਿਣਤੀ c_language_ਕਿਸਮ c_language = clk_c;

/* Lang hooks common to C and ObjC are declared in c-objc-common.h;
   consequently, there should be very few hooks below.  */

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_NAME
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_NAME "GNU C"
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_INIT
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_INIT c_objc_common_init
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_INIT_TS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_INIT_TS c_common_init_ts
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ENUM_UNDERLYING_ਅਧਾਰ_TYPE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ENUM_UNDERLYING_ਅਧਾਰ_TYPE c_enum_underlying_ਅਧਾਰ_type

#ਜੇ CHECKING_P
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_ਲੜੀਵਾਰ_LANG_SELFTESTS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_ਲੜੀਵਾਰ_LANG_SELFTESTS selftest::ਲੜੀਵਾਰ_c_tests
#ਜੇ_ਅੰਤ /* #if CHECKING_P */

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_GET_SUBSTRING_LOCATION
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_GET_SUBSTRING_LOCATION c_get_substring_location

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LANG_HOOKS_GET_SARIF_ਸਰੋਤ_LANGUAGE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LANG_HOOKS_GET_SARIF_ਸਰੋਤ_LANGUAGE c_get_sarif_ਸਰੋਤ_language

/* Each front end provides its own lang hook initializer.  */
ਬਣਤਰ lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Get a value for the SARIF v2.1.0 "artifact.sourceLanguage" property,
   based on the list in SARIF v2.1.0 Appendix J.  */

ਅਚਲ ਅੱਖਰ *
c_get_sarif_ਸਰੋਤ_language (ਅਚਲ ਅੱਖਰ *)
{
  ਵਾਪਸ "c";
}

/* Implement c-family hook to register language-specific features for
   __has_{feature,extension}.  */

ਖਾਲੀ
c_family_ਰਜਿਸਟਰ_lang_features ()
{
  c_ਰਜਿਸਟਰ_features ();
}

#ਜੇ CHECKING_P

ਨਾਮਾਕਾਸ਼ selftest {

/* Implementation of LANG_HOOKS_RUN_LANG_SELFTESTS for the C frontend.  */

ਖਾਲੀ
ਲੜੀਵਾਰ_c_tests (ਖਾਲੀ)
{
  /* Run selftests shared within the C family.  */
  c_family_tests ();

  /* Additional C-specific tests.  */
}

} // namespace selftest

#ਜੇ_ਅੰਤ /* #if CHECKING_P */


#ਅਨ੍ਤਰ੍ਭਾਵ "gtype-c.h"
