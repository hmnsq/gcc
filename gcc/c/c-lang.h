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

#यदि_अपरिभाषितम् GCC_C_LANG_H
#परिभाषय GCC_C_LANG_H

#अन्तर्भाव "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
संरचना GTY(()) sorted_fields_type {
  पूर्णाङ्क len;
  वृक्षः GTY((दीर्घता ("%h.len"))) elts[1];
};

संरचना GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  संरचना sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  वृक्षः enum_min;
  वृक्षः enum_max;
  सङ्घ maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    वर्ण GTY((चिह्नकम् ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    वृक्षः GTY((चिह्नकम् ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

संरचना GTY(()) lang_decl {
  वर्ण dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

संरचना GTY(()) language_function {
  संरचना c_language_function आधारः;
  अचिह्नित वर्ण x_अन्तर्_statement;
  संरचना c_switch * GTY((skip)) x_switch_राशिः;
  संरचना c_arg_info * GTY((skip)) arg_info;
  vec<वृक्षः> GTY((skip)) loop_नामानि;
  decl_वृक्षः_map * GTY((skip)) loop_नामानि_hash;
  पूर्णाङ्क returns_मानम्;
  पूर्णाङ्क returns_null;
  पूर्णाङ्क returns_abnormally;
  पूर्णाङ्क warn_about_return_type;
};

संरचना GTY(()) c_omp_declare_target_attr {
  bool attr_syntax;
  पूर्णाङ्क device_type;
  पूर्णाङ्क परोक्षम्;
};

संरचना GTY(()) c_omp_begin_assumes_दत्त {
  bool attr_syntax;
};

संरचना GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  वृक्षः selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
बाह्य GTY(()) vec<c_omp_declare_target_attr, va_gc>
  *current_omp_declare_target_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
बाह्य GTY(()) vec<c_omp_begin_assumes_दत्त, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
बाह्य GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#यदि_अन्तः /* ! GCC_C_LANG_H */
