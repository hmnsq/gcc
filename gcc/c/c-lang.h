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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GCC_C_LANG_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GCC_C_LANG_H

#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-common.h"

/* In a RECORD_TYPE, a sorted array of the fields of the type, not a
   tree for size reasons.  */
ਬਣਤਰ GTY(()) sorted_fields_type {
  ਪੂਰਨ len;
  ਰੁੱਖ GTY((ਲੰਮਾਈ ("%h.len"))) elts[1];
};

ਬਣਤਰ GTY(()) lang_type {
  /* In a RECORD_TYPE, a sorted array of the fields of the type.  */
  ਬਣਤਰ sorted_fields_type * GTY ((reorder ("resort_sorted_fields"))) s;
  /* In an ENUMERAL_TYPE, the min and max values.  */
  ਰੁੱਖ enum_min;
  ਰੁੱਖ enum_max;
  ਸੰਘ maybe_objc_info {
    /* If not c_dialect_objc, this part is not even allocated.  */
    ਅੱਖਰ GTY((ਟੈਗ ("0"))) non_objc;
    /* In a RECORD_TYPE, information specific to Objective-C, such
       as a list of adopted protocols or a pointer to a corresponding
       @interface.  See objc/objc-act.h for details.  */
    ਰੁੱਖ GTY((ਟੈਗ ("1"))) objc_info;
  } GTY ((desc ("c_dialect_objc ()"))) info;
};

ਬਣਤਰ GTY(()) lang_decl {
  ਅੱਖਰ dummy;
};

/* Save and restore the variables in this file and elsewhere
   that keep track of the progress of compilation of the current function.
   Used for nested functions.  */

ਬਣਤਰ GTY(()) language_function {
  ਬਣਤਰ c_language_function ਅਧਾਰ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ x_ਵਿੱਚ_statement;
  ਬਣਤਰ c_switch * GTY((skip)) x_switch_ਢੇਰ;
  ਬਣਤਰ c_arg_info * GTY((skip)) arg_info;
  vec<ਰੁੱਖ> GTY((skip)) loop_ਨਾਂ;
  decl_ਰੁੱਖ_map * GTY((skip)) loop_ਨਾਂ_hash;
  ਪੂਰਨ returns_ਮੁੱਲ;
  ਪੂਰਨ returns_null;
  ਪੂਰਨ returns_abnormally;
  ਪੂਰਨ warn_about_return_type;
};

ਬਣਤਰ GTY(()) c_omp_declare_ਨਿਸ਼ਾਨਾ_attr {
  bool attr_syntax;
  ਪੂਰਨ device_type;
  ਪੂਰਨ ਅਸਿੱਧਾ;
};

ਬਣਤਰ GTY(()) c_omp_begin_assumes_ਅੰਕੜੇ {
  bool attr_syntax;
};

ਬਣਤਰ GTY(()) c_omp_declare_variant_attr {
  bool attr_syntax;
  ਰੁੱਖ selector;
};

/* If non-empty, implicit "omp declare target" attribute is added into the
   attribute lists.  */
ਬਾਹਰੀ GTY(()) vec<c_omp_declare_ਨਿਸ਼ਾਨਾ_attr, va_gc>
  *current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute;
/* Similarly whether we are in between #pragma omp begin assumes and
   #pragma omp end assumes (and how many times when nested).  */
ਬਾਹਰੀ GTY(()) vec<c_omp_begin_assumes_ਅੰਕੜੇ, va_gc>
  *current_omp_begin_assumes;
/* And similarly for #pragma omp begin/end declare variant.  */
ਬਾਹਰੀ GTY(()) vec<c_omp_declare_variant_attr, va_gc>
  *current_omp_declare_variant_attribute;

#ਜੇ_ਅੰਤ /* ! GCC_C_LANG_H */
