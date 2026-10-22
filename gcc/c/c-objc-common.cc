/* Some code common to C and ObjC front ends.
   Copyright (C) 2001-2026 Free Software Foundation, Inc.

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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "system.h"
#অন্তর্ভাব "coretypes.h"
#অন্তর্ভাব "c-tree.h"
#অন্তর্ভাব "intl.h"
#অন্তর্ভাব "c-family/c-pretty-print.h"
#অন্তর্ভাব "tree-core.h"
#অন্তর্ভাব "tree-pretty-print.h"
#অন্তর্ভাব "tree-pretty-print-markup.h"
#অন্তর্ভাব "gimple-pretty-print.h"
#অন্তর্ভাব "langhooks.h"
#অন্তর্ভাব "c-objc-common.h"
#অন্তর্ভাব "c-family/c-type-mismatch.h"
#অন্তর্ভাব "stringpool.h"
#অন্তর্ভাব "attribs.h"
#অন্তর্ভাব "dwarf2.h"

স্থির যৌক্তিক c_বৃক্ষ_printer (pretty_printer *, text_info *, ধ্রুবক অক্ষর *,
			    পূর্ণসংখ্যা, যৌক্তিক, যৌক্তিক, যৌক্তিক, যৌক্তিক *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

কাঠামো c_feature_info
{
  ধ্রুবক অক্ষর *ident;
  ধ্রুবক পূর্ণসংখ্যা *enable_flag;
};

স্থির ধ্রুবক c_feature_info c_feature_table[] =
{
  { "c_alignas", &flag_isoc11 },
  { "c_alignof", &flag_isoc11 },
  { "c_atomic", &flag_isoc11 },
  { "c_generic_selections", &flag_isoc11 },
  { "c_static_assert", &flag_isoc11 },
  { "c_thread_local", &flag_isoc11 },
  { "cxx_binary_literals", &flag_isoc23 }
};

/* Register features specific to the C language.  */

শূন্য
c_register_features ()
{
  জন্য (unsigned i = 0; i < ARRAY_আকার (c_feature_table); i++)
    {
      ধ্রুবক c_feature_info *info = c_feature_table + i;
      ধ্রুবক যৌক্তিক feat_p = !info->enable_flag || *info->enable_flag;
      c_common_register_feature (info->ident, feat_p);
    }
}

যৌক্তিক
c_missing_noreturn_ok_p (বৃক্ষ decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  যদি (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    ফেরত মিথ্যা;

  ফেরত flag_hosted
    || TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (বৃক্ষ_TYPE (decl))) == integer_type_গ্রন্থি;
}

/* Called from check_global_declaration.  */

যৌক্তিক
c_warn_unused_global_decl (const_বৃক্ষ decl)
{
  যদি (বৃক্ষ_CODE (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    ফেরত মিথ্যা;
  যদি (DECL_IN_SYSTEM_HEADER (decl))
    ফেরত মিথ্যা;

  ফেরত সত্য;
}

/* Initialization common to C and Objective-C front ends.  */
যৌক্তিক
c_objc_common_init (শূন্য)
{
  c_init_decl_processing ();

  ফেরত c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

স্থির বৃক্ষ
get_aka_type (বৃক্ষ type)
{
  যদি (type == error_mark_গ্রন্থি)
    ফেরত type;

  বৃক্ষ ফলাফল;
  যদি (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      বৃক্ষ orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      বৃক্ষ_code code = বৃক্ষ_CODE (orig_type);
      বৃক্ষ orig_id = TYPE_IDENTIFIER (orig_type);
      যদি ((code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	ফেরত type;

      যদি (!user_facing_original_type_p (type))
	ফেরত type;

      ফলাফল = get_aka_type (orig_type);
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == ENUMERAL_TYPE)
    ফেরত type;
  অন্যথা
    {
      বৃক্ষ canonical = TYPE_CANONICAL (type);
      যদি (canonical && বৃক্ষ_CODE (type) != বৃক্ষ_CODE (canonical))
	ফেরত canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      নির্বাচন (বৃক্ষ_CODE (type))
	{
	ক্ষেত্র POINTER_TYPE:
	ক্ষেত্র REFERENCE_TYPE:
	  {
	    বৃক্ষ target_type = get_aka_type (বৃক্ষ_TYPE (type));

	    যদি (target_type == বৃক্ষ_TYPE (type))
	      ফেরত type;

	    যদি (canonical && target_type == বৃক্ষ_TYPE (canonical))
	      ফেরত canonical;

	    ফলাফল = (বৃক্ষ_CODE (type) == POINTER_TYPE
		      ? build_pointer_type (target_type)
		      : build_reference_type (target_type));
	    বিরতি;
	  }

	ক্ষেত্র ARRAY_TYPE:
	  {
	    বৃক্ষ element_type = get_aka_type (বৃক্ষ_TYPE (type));
	    বৃক্ষ সূচক_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_বৃক্ষ);

	    যদি (element_type == বৃক্ষ_TYPE (type)
		&& সূচক_type == TYPE_DOMAIN (type))
	      ফেরত type;

	    যদি (canonical
		&& element_type == বৃক্ষ_TYPE (canonical)
		&& সূচক_type == TYPE_DOMAIN (canonical))
	      ফেরত canonical;

	    ফলাফল = build_array_type (element_type, সূচক_type,
				       TYPE_TYPELESS_STORAGE (type));
	    বিরতি;
	  }

	ক্ষেত্র FUNCTION_TYPE:
	  {
	    বৃক্ষ return_type = get_aka_type (বৃক্ষ_TYPE (type));

	    বৃক্ষ args = TYPE_ARG_TYPES (type);
	    যদি (args == error_mark_গ্রন্থি)
	      ফেরত type;

	    auto_vec<বৃক্ষ, 32> arg_types;
	    যৌক্তিক type_ok_p = সত্য;
	    যখন (args && args != void_list_গ্রন্থি)
	      {
		বৃক্ষ arg_type = get_aka_type (বৃক্ষ_মান (args));
		arg_types.safe_ঠেলো (arg_type);
		type_ok_p &= (arg_type == বৃক্ষ_মান (args));
		args = বৃক্ষ_CHAIN (args);
	      }

	    যদি (type_ok_p && return_type == বৃক্ষ_TYPE (type))
	      ফেরত type;

	    unsigned পূর্ণসংখ্যা i;
	    বৃক্ষ arg_type;
	    FOR_EACH_VEC_ELT_REVERSE (arg_types, i, arg_type)
	      args = বৃক্ষ_cons (NULL_বৃক্ষ, arg_type, args);
	    ফলাফল = build_function_type (return_type, args);
	    বিরতি;
	  }

	পূর্বনির্ধারিত:
	  ফেরত canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  যদি (RECORD_OR_UNION_TYPE_P (type) || বৃক্ষ_CODE (type) == ENUMERAL_TYPE)
    ফেরত build_qualified_type (ফলাফল, TYPE_QUALS (type));
  ফেরত build_type_attribute_qual_variant (ফলাফল, TYPE_ATTRIBUTES (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

স্থির শূন্য
print_type (c_pretty_printer *cpp, বৃক্ষ t, যৌক্তিক *quoted,
	    ধ্রুবক অক্ষর *highlight_color = nullptr)
{
  যদি (t == error_mark_গ্রন্থি)
    {
      pp_string (cpp, _("{erroneous}"));
      ফেরত;
    }

  যদি (!pp_show_highlight_colors (cpp))
    highlight_color = nullptr;

  gcc_assert (TYPE_P (t));
  কাঠামো obstack *ob = pp_বাফার (cpp)->m_obstack;
  অক্ষর *p = (অক্ষর *) obstack_base (ob);
  /* Remember the end of the initial dump.  */
  পূর্ণসংখ্যা len = obstack_object_আকার (ob);

  বৃক্ষ name = TYPE_NAME (t);
  যদি (name && বৃক্ষ_CODE (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  অন্যথা
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  বৃক্ষ aka_type = get_aka_type (t);
  যদি (aka_type != t)
    {
      ধ্রুবক যৌক্তিক show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      কাঠামো obstack *ob2 = pp_বাফার (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      ধ্রুবক অক্ষর *aka = (অক্ষর *) obstack_base (ob2);
      পূর্ণসংখ্যা aka_len = obstack_object_আকার (ob2);
      পূর্ণসংখ্যা type1_len = obstack_object_আকার (ob) - len;

      /* If they are identical, bail out.  */
      যদি (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	ফেরত;

      /* They're not, print the stripped version now.  */
      যদি (*quoted)
	pp_end_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_বাম_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      যদি (*quoted)
	pp_begin_quote (cpp, show_color);
      যদি (highlight_color)
	pp_string (cpp, colorize_start (show_color, highlight_color));
      cpp->type_id (aka_type);
      যদি (*quoted)
	pp_end_quote (cpp, show_color);
      pp_ডান_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = মিথ্যা;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

শূন্য
pp_markup::element_quoted_type::print_type (pp_markup::context &ctxt)
{
  auto pp = ctxt.m_pp.clone ();
  c_pretty_printer *cpp = (c_pretty_printer *)pp.get ();
  cpp->set_padding (pp_none);
  ::print_type (cpp, m_type, &ctxt.m_quoted, m_highlight_color);
  pp_string (&ctxt.m_pp, pp_formatted_text (cpp));
}

/* Called during diagnostic message formatting process to print a
   source-level entity onto BUFFER.  The meaning of the format specifiers
   is as follows:
   %D: a general decl,
   %E: an identifier or expression,
   %F: a function declaration,
   %T: a type.
   %V: a list of type qualifiers from a tree.
   %v: an explicit list of type qualifiers
   %#v: an explicit list of type qualifiers of a function type.

   Please notice when called, the `%' part was already skipped by the
   diagnostic machinery.  */
স্থির যৌক্তিক
c_বৃক্ষ_printer (pretty_printer *pp, text_info *text, ধ্রুবক অক্ষর *spec,
		পূর্ণসংখ্যা precision, যৌক্তিক wide, যৌক্তিক set_locus, যৌক্তিক hash,
		যৌক্তিক *quoted, pp_token_list &)
{
  বৃক্ষ t = NULL_বৃক্ষ;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->set_padding (pp_none);

  যদি (precision != 0 || wide)
    ফেরত মিথ্যা;

  যদি (*spec != 'v')
    {
      t = va_arg (*text->m_args_ptr, বৃক্ষ);
      যদি (set_locus)
	text->set_location (0, DECL_SOURCE_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  নির্বাচন (*spec)
    {
    ক্ষেত্র 'D':
      যদি (VAR_P (t) && DECL_HAS_DEBUG_রাশিমালা_P (t))
	{
	  t = DECL_DEBUG_রাশিমালা (t);
	  যদি (!DECL_P (t))
	    {
	      cpp->expression (t);
	      ফেরত সত্য;
	    }
	}
      /* FALLTHRU */

    ক্ষেত্র 'F':
      যদি (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  যদি (বৃক্ষ_CODE (t) == FUNCTION_DECL)
	    {
	      pp_c_function_target_version (cpp, t);
	      pp_c_function_target_clones (cpp, t);
	    }
	  ফেরত সত্য;
	}
      বিরতি;

    ক্ষেত্র 'T':
      print_type (cpp, t, quoted);
      ফেরত সত্য;

    ক্ষেত্র 'E':
      যদি (বৃক্ষ_CODE (t) == IDENTIFIER_গ্রন্থি)
	pp_identifier (cpp, IDENTIFIER_POINTER (t));
      অন্যথা
	cpp->expression (t);
      ফেরত সত্য;

    ক্ষেত্র 'V':
      pp_c_type_qualifier_list (cpp, t);
      ফেরত সত্য;

    ক্ষেত্র 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*text->m_args_ptr, পূর্ণসংখ্যা), hash);
      ফেরত সত্য;

    পূর্বনির্ধারিত:
      ফেরত মিথ্যা;
    }

  pp_string (cpp, _("({anonymous})"));
  ফেরত সত্য;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_text
range_label_for_type_mismatch::get_text (unsigned /*range_idx*/) ধ্রুবক
{
  যদি (m_labelled_type == NULL_বৃক্ষ)
    ফেরত label_text::borrow (ফাঁকা);

  c_pretty_printer cpp;
  যৌক্তিক quoted = মিথ্যা;
  print_type (&cpp, m_labelled_type, &quoted);
  ফেরত label_text::take (xstrdup (pp_formatted_text (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
যৌক্তিক
has_c_linkage (const_বৃক্ষ decl ATTRIBUTE_UNUSED)
{
  ফেরত সত্য;
}

শূন্য
c_initialize_diagnostics (diagnostics::context *context)
{
  context->set_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_set_defaults (context);
  context->set_format_decoder (&c_বৃক্ষ_printer);
}

পূর্ণসংখ্যা
c_types_compatible_p (বৃক্ষ x, বৃক্ষ y)
{
  ফেরত comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

যৌক্তিক
c_var_mod_p (বৃক্ষ x, বৃক্ষ fn ATTRIBUTE_UNUSED)
{
  ফেরত c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_set_type
c_get_alias_set (বৃক্ষ t)
{
  ফেরত c_common_get_alias_set (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

পূর্ণসংখ্যা
maybe_adjust_arg_pos_for_attribute (const_বৃক্ষ)
{
  ফেরত 0;
}

/* In C, no expression is dependent.  */

যৌক্তিক
instantiation_dependent_expression_p (বৃক্ষ)
{
  ফেরত মিথ্যা;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
পূর্ণসংখ্যা
c_type_dwarf_attribute (const_বৃক্ষ type, পূর্ণসংখ্যা attr)
{
  যদি (type == NULL_বৃক্ষ)
    ফেরত -1;

  নির্বাচন (attr)
    {
    ক্ষেত্র DW_AT_export_symbols:
      যদি (RECORD_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_বৃক্ষ)
	ফেরত 1;
      বিরতি;

    পূর্বনির্ধারিত:
      বিরতি;
    }

  ফেরত -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

বৃক্ষ
c_enum_underlying_base_type (const_বৃক্ষ type)
{
  বৃক্ষ underlying_type = ENUM_UNDERLYING_TYPE (type);

  যদি (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_mode (TYPE_MODE (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  ফেরত underlying_type;
}
