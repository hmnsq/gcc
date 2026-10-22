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

#ضمن "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
بنية GTY(()) sorted_fields_type {
  صحيح len;
  ڤوکوق GTY((length ("%h.len"))) elts[1];
};

بنية GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  بنية sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  ڤوکوق enum_min;
  ڤوکوق enum_max;
  اتحاد maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    حرف GTY((tag ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    ڤوکوق GTY((tag ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

بنية GTY(()) lang_decl {
  حرف dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

بنية GTY(()) language_function {
  بنية c_language_function base;
  unsigned حرف x_in_statement;
  بنية c_switch * GTY((skip)) x_switch_تيندنن;
  بنية c_arg_info * GTY((skip)) arg_info;
  vec<ڤوکوق> GTY((skip)) loop_names;
  decl_ڤوکوق_map * GTY((skip)) loop_names_hash;
  صحيح returns_نيلاي;
  صحيح returns_null;
  صحيح returns_abnormally;
  صحيح warn_about_return_type;
};

بنية GTY(()) c_omp_declare_target_attr {
  bool attr_syntax;
  صحيح device_type;
  صحيح indirect;
};

بنية GTY(()) c_omp_begin_assumes_data {
  bool attr_syntax;
};

بنية GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  ڤوکوق selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
خارجي GTY(()) vec<c_omp_declare_target_attr, va_gc>
  *current_omp_declare_target_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
خارجي GTY(()) vec<c_omp_begin_assumes_data, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
خارجي GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#endif /* ! GCC_C_LANG_H */
