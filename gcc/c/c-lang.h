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

#অন্তর্ভাব "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
কাঠামো GTY(()) sorted_fields_type {
  পূর্ণসংখ্যা len;
  বৃক্ষ GTY((দৈর্ঘ্য ("%h.len"))) elts[1];
};

কাঠামো GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  কাঠামো sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  বৃক্ষ enum_min;
  বৃক্ষ enum_max;
  সংঘ maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    অক্ষর GTY((tag ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    বৃক্ষ GTY((tag ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

কাঠামো GTY(()) lang_decl {
  অক্ষর dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

কাঠামো GTY(()) language_function {
  কাঠামো c_language_function base;
  unsigned অক্ষর x_in_statement;
  কাঠামো c_switch * GTY((skip)) x_switch_স্তূপ;
  কাঠামো c_arg_info * GTY((skip)) arg_info;
  vec<বৃক্ষ> GTY((skip)) loop_names;
  decl_বৃক্ষ_map * GTY((skip)) loop_names_hash;
  পূর্ণসংখ্যা returns_মান;
  পূর্ণসংখ্যা returns_null;
  পূর্ণসংখ্যা returns_abnormally;
  পূর্ণসংখ্যা warn_about_return_type;
};

কাঠামো GTY(()) c_omp_declare_target_attr {
  bool attr_syntax;
  পূর্ণসংখ্যা device_type;
  পূর্ণসংখ্যা indirect;
};

কাঠামো GTY(()) c_omp_begin_assumes_তথ্য {
  bool attr_syntax;
};

কাঠামো GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  বৃক্ষ selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
বাহ্যিক GTY(()) vec<c_omp_declare_target_attr, va_gc>
  *current_omp_declare_target_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
বাহ্যিক GTY(()) vec<c_omp_begin_assumes_তথ্য, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
বাহ্যিক GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#endif /* ! GCC_C_LANG_H */
