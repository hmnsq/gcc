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

#ಅನ್ತರ್ಭಾವ "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
ಸಂರಚನಾ GTY(()) sorted_fields_type {
  ಪೂರ್ಣಾಙ್ಕ len;
  ವೃಕ್ಷ GTY((length ("%h.len"))) elts[1];
};

ಸಂರಚನಾ GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  ಸಂರಚನಾ sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  ವೃಕ್ಷ enum_min;
  ವೃಕ್ಷ enum_max;
  ಸಙ್ಘ maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    ವರ್ಣ GTY((tag ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    ವೃಕ್ಷ GTY((tag ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

ಸಂರಚನಾ GTY(()) lang_decl {
  ವರ್ಣ dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

ಸಂರಚನಾ GTY(()) language_function {
  ಸಂರಚನಾ c_language_function base;
  unsigned ವರ್ಣ x_in_statement;
  ಸಂರಚನಾ c_switch * GTY((skip)) x_switch_ರಾಶಿ;
  ಸಂರಚನಾ c_arg_info * GTY((skip)) arg_info;
  vec<ವೃಕ್ಷ> GTY((skip)) loop_names;
  decl_ವೃಕ್ಷ_map * GTY((skip)) loop_names_hash;
  ಪೂರ್ಣಾಙ್ಕ returns_ಮೌಲ್ಯ;
  ಪೂರ್ಣಾಙ್ಕ returns_null;
  ಪೂರ್ಣಾಙ್ಕ returns_abnormally;
  ಪೂರ್ಣಾಙ್ಕ warn_about_return_type;
};

ಸಂರಚನಾ GTY(()) c_omp_declare_target_attr {
  bool attr_syntax;
  ಪೂರ್ಣಾಙ್ಕ device_type;
  ಪೂರ್ಣಾಙ್ಕ indirect;
};

ಸಂರಚನಾ GTY(()) c_omp_begin_assumes_data {
  bool attr_syntax;
};

ಸಂರಚನಾ GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  ವೃಕ್ಷ selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
ಬಾಹ್ಯ GTY(()) vec<c_omp_declare_target_attr, va_gc>
  *current_omp_declare_target_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
ಬಾಹ್ಯ GTY(()) vec<c_omp_begin_assumes_data, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
ಬಾಹ್ಯ GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#endif /* ! GCC_C_LANG_H */
