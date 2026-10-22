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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GCC_C_LANG_H
#ವ್ಯಾಖ್ಯಾನಿಸು GCC_C_LANG_H

#ಅನ್ತರ್ಭಾವ "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
ರಚನೆ GTY(()) sorted_fields_type {
  ಪೂರ್ಣಾಂಕ len;
  ವೃಕ್ಷ GTY((ಉದ್ದಳತೆ ("%h.len"))) elts[1];
};

ರಚನೆ GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  ರಚನೆ sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  ವೃಕ್ಷ enum_min;
  ವೃಕ್ಷ enum_max;
  ಒಕ್ಕೂಟ maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    ಅಕ್ಷರ GTY((ಟ್ಯಾಗ್ ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    ವೃಕ್ಷ GTY((ಟ್ಯಾಗ್ ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

ರಚನೆ GTY(()) lang_decl {
  ಅಕ್ಷರ dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

ರಚನೆ GTY(()) language_function {
  ರಚನೆ c_language_function ತಳ;
  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ x_ಒಳ_statement;
  ರಚನೆ c_switch * GTY((skip)) x_switch_ರಾಶಿ;
  ರಚನೆ c_arg_info * GTY((skip)) arg_info;
  vec<ವೃಕ್ಷ> GTY((skip)) loop_ಹೆಸರುಗಳು;
  decl_ವೃಕ್ಷ_map * GTY((skip)) loop_ಹೆಸರುಗಳು_hash;
  ಪೂರ್ಣಾಂಕ returns_ಮೌಲ್ಯ;
  ಪೂರ್ಣಾಂಕ returns_null;
  ಪೂರ್ಣಾಂಕ returns_abnormally;
  ಪೂರ್ಣಾಂಕ warn_about_return_type;
};

ರಚನೆ GTY(()) c_omp_declare_ಗುರಿ_attr {
  bool attr_syntax;
  ಪೂರ್ಣಾಂಕ device_type;
  ಪೂರ್ಣಾಂಕ ಪರೋಕ್ಷ;
};

ರಚನೆ GTY(()) c_omp_begin_assumes_ದತ್ತಾಂಶ {
  bool attr_syntax;
};

ರಚನೆ GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  ವೃಕ್ಷ selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
ಬಾಹ್ಯ GTY(()) vec<c_omp_declare_ಗುರಿ_attr, va_gc>
  *current_omp_declare_ಗುರಿ_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
ಬಾಹ್ಯ GTY(()) vec<c_omp_begin_assumes_ದತ್ತಾಂಶ, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
ಬಾಹ್ಯ GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#ಆದರೆ_ಅಂತ್ಯ /* ! GCC_C_LANG_H */
