/* Definitions for C language specific types.
   Copyright (C) 2009-2026 Free Software Foundation, Inc.

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

#ifndef GCC_C_LANG_H
#define GCC_C_LANG_H

#ଅନ୍ତର୍ଭାଵ "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
ସଂରଚନା GTY(()) sorted_fields_type {
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା len;
  ବୃକ୍ଷ GTY((length ("%h.len"))) elts[1];
};

ସଂରଚନା GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  ସଂରଚନା sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  ବୃକ୍ଷ enum_min;
  ବୃକ୍ଷ enum_max;
  ସଂଘ maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    ଅକ୍ଷର GTY((tag ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    ବୃକ୍ଷ GTY((tag ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

ସଂରଚନା GTY(()) lang_decl {
  ଅକ୍ଷର dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

ସଂରଚନା GTY(()) language_function {
  ସଂରଚନା c_language_function base;
  unsigned ଅକ୍ଷର x_in_statement;
  ସଂରଚନା c_switch * GTY((skip)) x_switch_ଗଦା;
  ସଂରଚନା c_arg_info * GTY((skip)) arg_info;
  vec<ବୃକ୍ଷ> GTY((skip)) loop_names;
  decl_ବୃକ୍ଷ_map * GTY((skip)) loop_names_hash;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା returns_ମୂଲ୍ୟ;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା returns_null;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା returns_abnormally;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା warn_about_return_type;
};

ସଂରଚନା GTY(()) c_omp_declare_target_attr {
  bool attr_syntax;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା device_type;
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା indirect;
};

ସଂରଚନା GTY(()) c_omp_begin_assumes_data {
  bool attr_syntax;
};

ସଂରଚନା GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  ବୃକ୍ଷ selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
ବାହ୍ୟ GTY(()) vec<c_omp_declare_target_attr, va_gc>
  *current_omp_declare_target_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
ବାହ୍ୟ GTY(()) vec<c_omp_begin_assumes_data, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
ବାହ୍ୟ GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#endif /* ! GCC_C_LANG_H */
