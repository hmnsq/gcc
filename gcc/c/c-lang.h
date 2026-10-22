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

#اگر_غیر_تعریف_شدہ GCC_C_LANG_H
#تعریف_کرو GCC_C_LANG_H

#شامل "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
ساخت GTY(()) sorted_fields_type {
  صحیح len;
  درخت GTY((لمبائی ("%h.len"))) elts[1];
};

ساخت GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  ساخت sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  درخت enum_min;
  درخت enum_max;
  اتحاد maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    حرف GTY((لیبل ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    درخت GTY((لیبل ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

ساخت GTY(()) lang_decl {
  حرف dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

ساخت GTY(()) language_function {
  ساخت c_language_function بنیاد;
  غیرعلامتی حرف x_اندر_statement;
  ساخت c_switch * GTY((skip)) x_switch_ڈھیر;
  ساخت c_arg_info * GTY((skip)) arg_info;
  vec<درخت> GTY((skip)) loop_نام;
  decl_درخت_map * GTY((skip)) loop_نام_hash;
  صحیح returns_قدر;
  صحیح returns_null;
  صحیح returns_abnormally;
  صحیح warn_about_return_type;
};

ساخت GTY(()) c_omp_declare_ہدف_attr {
  bool attr_syntax;
  صحیح device_type;
  صحیح بالواسطہ;
};

ساخت GTY(()) c_omp_begin_assumes_ڈیٹا {
  bool attr_syntax;
};

ساخت GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  درخت selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
خارجی GTY(()) vec<c_omp_declare_ہدف_attr, va_gc>
  *current_omp_declare_ہدف_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
خارجی GTY(()) vec<c_omp_begin_assumes_ڈیٹا, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
خارجی GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#اگر_ختم /* ! GCC_C_LANG_H */
