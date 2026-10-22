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

#अगर_अघोषित GCC_C_LANG_H
#घोषणा GCC_C_LANG_H

#समावेश "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
काष्ठा GTY(()) sorted_fields_type {
  पूर्णांक len;
  वृक्ष GTY((लंबाई ("%h.len"))) elts[1];
};

काष्ठा GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  काष्ठा sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  वृक्ष enum_min;
  वृक्ष enum_max;
  जोड़ maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    अक्षर GTY((tag ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    वृक्ष GTY((tag ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

काष्ठा GTY(()) lang_decl {
  अक्षर dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

काष्ठा GTY(()) language_function {
  काष्ठा c_language_function base;
  अचिन्हित अक्षर x_in_statement;
  काष्ठा c_switch * GTY((skip)) x_switch_ढेर;
  काष्ठा c_arg_info * GTY((skip)) arg_info;
  vec<वृक्ष> GTY((skip)) loop_names;
  decl_वृक्ष_map * GTY((skip)) loop_names_hash;
  पूर्णांक returns_मूल्य;
  पूर्णांक returns_null;
  पूर्णांक returns_abnormally;
  पूर्णांक warn_about_return_type;
};

काष्ठा GTY(()) c_omp_declare_target_attr {
  bool attr_syntax;
  पूर्णांक device_type;
  पूर्णांक indirect;
};

काष्ठा GTY(()) c_omp_begin_assumes_तथ्य {
  bool attr_syntax;
};

काष्ठा GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  वृक्ष selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
बाह्य GTY(()) vec<c_omp_declare_target_attr, va_gc>
  *current_omp_declare_target_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
बाह्य GTY(()) vec<c_omp_begin_assumes_तथ्य, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
बाह्य GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#पूर्ण_अगर /* ! GCC_C_LANG_H */
