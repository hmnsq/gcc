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

#నిర్వచితం_కాకపోతే GCC_C_LANG_H
#నిర్వచించు GCC_C_LANG_H

#అన్తర్భావ "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
నిర్మాణం GTY(()) sorted_fields_type {
  పూర్ణాంకం len;
  వృక్షం GTY((నిడివి ("%h.len"))) elts[1];
};

నిర్మాణం GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  నిర్మాణం sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  వృక్షం enum_min;
  వృక్షం enum_max;
  సంఘం maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    అక్షరం GTY((ట్యాగ్ ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    వృక్షం GTY((ట్యాగ్ ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

నిర్మాణం GTY(()) lang_decl {
  అక్షరం dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

నిర్మాణం GTY(()) language_function {
  నిర్మాణం c_language_function పునాది;
  గుర్తులేని అక్షరం x_లోపల_statement;
  నిర్మాణం c_switch * GTY((skip)) x_switch_దొంతర;
  నిర్మాణం c_arg_info * GTY((skip)) arg_info;
  vec<వృక్షం> GTY((skip)) loop_పేర్లు;
  decl_వృక్షం_map * GTY((skip)) loop_పేర్లు_hash;
  పూర్ణాంకం returns_విలువ;
  పూర్ణాంకం returns_null;
  పూర్ణాంకం returns_abnormally;
  పూర్ణాంకం warn_about_return_type;
};

నిర్మాణం GTY(()) c_omp_declare_లక్ష్యం_attr {
  bool attr_syntax;
  పూర్ణాంకం device_type;
  పూర్ణాంకం పరోక్ష;
};

నిర్మాణం GTY(()) c_omp_begin_assumes_దత్తాంశం {
  bool attr_syntax;
};

నిర్మాణం GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  వృక్షం selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
బాహ్య GTY(()) vec<c_omp_declare_లక్ష్యం_attr, va_gc>
  *current_omp_declare_లక్ష్యం_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
బాహ్య GTY(()) vec<c_omp_begin_assumes_దత్తాంశం, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
బాహ్య GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#అయితే_ముగింపు /* ! GCC_C_LANG_H */
