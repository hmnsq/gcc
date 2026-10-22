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


#అన్తర్భావ "config.h"
#అన్తర్భావ "system.h"
#అన్తర్భావ "coretypes.h"
#అన్తర్భావ "c-tree.h"
#అన్తర్భావ "langhooks.h"
#అన్తర్భావ "langhooks-def.h"
#అన్తర్భావ "c-objc-common.h"
#అన్తర్భావ "c-family/c-pragma.h"
#అన్తర్భావ "c-parser.h"

గణన c_language_రకం c_language = clk_c;

/* Lang hooks common to C and ObjC are declared in c-objc-common.h;
   consequently, there should be very few hooks below.  */

#నిర్వచనం_రద్దు LANG_HOOKS_NAME
#నిర్వచించు LANG_HOOKS_NAME "GNU C"
#నిర్వచనం_రద్దు LANG_HOOKS_INIT
#నిర్వచించు LANG_HOOKS_INIT c_objc_common_init
#నిర్వచనం_రద్దు LANG_HOOKS_INIT_TS
#నిర్వచించు LANG_HOOKS_INIT_TS c_common_init_ts
#నిర్వచనం_రద్దు LANG_HOOKS_ENUM_UNDERLYING_పునాది_TYPE
#నిర్వచించు LANG_HOOKS_ENUM_UNDERLYING_పునాది_TYPE c_enum_underlying_పునాది_type

#ఒకవేళ CHECKING_P
#నిర్వచనం_రద్దు LANG_HOOKS_నిరంతరం_LANG_SELFTESTS
#నిర్వచించు LANG_HOOKS_నిరంతరం_LANG_SELFTESTS selftest::నిరంతరం_c_tests
#అయితే_ముగింపు /* #if CHECKING_P */

#నిర్వచనం_రద్దు LANG_HOOKS_GET_SUBSTRING_LOCATION
#నిర్వచించు LANG_HOOKS_GET_SUBSTRING_LOCATION c_get_substring_location

#నిర్వచనం_రద్దు LANG_HOOKS_GET_SARIF_ఆధారం_LANGUAGE
#నిర్వచించు LANG_HOOKS_GET_SARIF_ఆధారం_LANGUAGE c_get_sarif_ఆధారం_language

/* Each front end provides its own lang hook initializer.  */
నిర్మాణం lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Get a value for the SARIF v2.1.0 "artifact.sourceLanguage" property,
   based on the list in SARIF v2.1.0 Appendix J.  */

స్థిరరాశి అక్షరం *
c_get_sarif_ఆధారం_language (స్థిరరాశి అక్షరం *)
{
  తిరిగి "c";
}

/* Implement c-family hook to register language-specific features for
   __has_{feature,extension}.  */

శూన్య
c_family_రిజిస్టరు_lang_features ()
{
  c_రిజిస్టరు_features ();
}

#ఒకవేళ CHECKING_P

నామాకాశ selftest {

/* Implementation of LANG_HOOKS_RUN_LANG_SELFTESTS for the C frontend.  */

శూన్య
నిరంతరం_c_tests (శూన్య)
{
  /* Run selftests shared within the C family.  */
  c_family_tests ();

  /* Additional C-specific tests.  */
}

} // namespace selftest

#అయితే_ముగింపు /* #if CHECKING_P */


#అన్తర్భావ "gtype-c.h"
