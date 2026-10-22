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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "system.h"
#ଅନ୍ତର୍ଭାଵ "coretypes.h"
#ଅନ୍ତର୍ଭାଵ "c-tree.h"
#ଅନ୍ତର୍ଭାଵ "intl.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-pretty-print.h"
#ଅନ୍ତର୍ଭାଵ "tree-core.h"
#ଅନ୍ତର୍ଭାଵ "tree-pretty-print.h"
#ଅନ୍ତର୍ଭାଵ "tree-pretty-print-markup.h"
#ଅନ୍ତର୍ଭାଵ "gimple-pretty-print.h"
#ଅନ୍ତର୍ଭାଵ "langhooks.h"
#ଅନ୍ତର୍ଭାଵ "c-objc-common.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-type-mismatch.h"
#ଅନ୍ତର୍ଭାଵ "stringpool.h"
#ଅନ୍ତର୍ଭାଵ "attribs.h"
#ଅନ୍ତର୍ଭାଵ "dwarf2.h"

ସ୍ଥିର ତାର୍କିକ c_ବୃକ୍ଷ_printer (pretty_printer *, text_info *, ଅଚଳ ଅକ୍ଷର *,
			    ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ତାର୍କିକ, ତାର୍କିକ, ତାର୍କିକ, ତାର୍କିକ *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

ସଂରଚନା c_feature_info
{
  ଅଚଳ ଅକ୍ଷର *ident;
  ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *enable_flag;
};

ସ୍ଥିର ଅଚଳ c_feature_info c_feature_table[] =
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

ଶୂନ୍ୟ
c_register_features ()
{
  ପାଇଁ (unsigned i = 0; i < ARRAY_SIZE (c_feature_table); i++)
    {
      ଅଚଳ c_feature_info *info = c_feature_table + i;
      ଅଚଳ ତାର୍କିକ feat_p = !info->enable_flag || *info->enable_flag;
      c_common_register_feature (info->ident, feat_p);
    }
}

ତାର୍କିକ
c_missing_noreturn_ok_p (ବୃକ୍ଷ decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  ଯଦି (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଫେରନ୍ତୁ flag_hosted
    || TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (decl))) == integer_type_ଗଣ୍ଠି;
}

/* Called from check_global_declaration.  */

ତାର୍କିକ
c_warn_unused_global_decl (const_ବୃକ୍ଷ decl)
{
  ଯଦି (ବୃକ୍ଷ_CODE (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;
  ଯଦି (DECL_IN_SYSTEM_HEADER (decl))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* Initialization common to C and Objective-C front ends.  */
ତାର୍କିକ
c_objc_common_init (ଶୂନ୍ୟ)
{
  c_init_decl_processing ();

  ଫେରନ୍ତୁ c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

ସ୍ଥିର ବୃକ୍ଷ
get_aka_type (ବୃକ୍ଷ type)
{
  ଯଦି (type == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ type;

  ବୃକ୍ଷ result;
  ଯଦି (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      ବୃକ୍ଷ orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (orig_type);
      ବୃକ୍ଷ orig_id = TYPE_IDENTIFIER (orig_type);
      ଯଦି ((code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	ଫେରନ୍ତୁ type;

      ଯଦି (!user_facing_original_type_p (type))
	ଫେରନ୍ତୁ type;

      result = get_aka_type (orig_type);
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE)
    ଫେରନ୍ତୁ type;
  ଅନ୍ୟଥା
    {
      ବୃକ୍ଷ canonical = TYPE_CANONICAL (type);
      ଯଦି (canonical && ବୃକ୍ଷ_CODE (type) != ବୃକ୍ଷ_CODE (canonical))
	ଫେରନ୍ତୁ canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      ବାଛ (ବୃକ୍ଷ_CODE (type))
	{
	ସ୍ଥିତି POINTER_TYPE:
	ସ୍ଥିତି REFERENCE_TYPE:
	  {
	    ବୃକ୍ଷ target_type = get_aka_type (ବୃକ୍ଷ_TYPE (type));

	    ଯଦି (target_type == ବୃକ୍ଷ_TYPE (type))
	      ଫେରନ୍ତୁ type;

	    ଯଦି (canonical && target_type == ବୃକ୍ଷ_TYPE (canonical))
	      ଫେରନ୍ତୁ canonical;

	    result = (ବୃକ୍ଷ_CODE (type) == POINTER_TYPE
		      ? build_pointer_type (target_type)
		      : build_reference_type (target_type));
	    ଭାଙ୍ଗ;
	  }

	ସ୍ଥିତି ARRAY_TYPE:
	  {
	    ବୃକ୍ଷ element_type = get_aka_type (ବୃକ୍ଷ_TYPE (type));
	    ବୃକ୍ଷ index_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_ବୃକ୍ଷ);

	    ଯଦି (element_type == ବୃକ୍ଷ_TYPE (type)
		&& index_type == TYPE_DOMAIN (type))
	      ଫେରନ୍ତୁ type;

	    ଯଦି (canonical
		&& element_type == ବୃକ୍ଷ_TYPE (canonical)
		&& index_type == TYPE_DOMAIN (canonical))
	      ଫେରନ୍ତୁ canonical;

	    result = build_array_type (element_type, index_type,
				       TYPE_TYPELESS_STORAGE (type));
	    ଭାଙ୍ଗ;
	  }

	ସ୍ଥିତି FUNCTION_TYPE:
	  {
	    ବୃକ୍ଷ return_type = get_aka_type (ବୃକ୍ଷ_TYPE (type));

	    ବୃକ୍ଷ args = TYPE_ARG_TYPES (type);
	    ଯଦି (args == error_mark_ଗଣ୍ଠି)
	      ଫେରନ୍ତୁ type;

	    auto_vec<ବୃକ୍ଷ, 32> arg_types;
	    ତାର୍କିକ type_ok_p = ସତ୍ୟ;
	    ଯେତେବେଳେ (args && args != void_list_ଗଣ୍ଠି)
	      {
		ବୃକ୍ଷ arg_type = get_aka_type (ବୃକ୍ଷ_ମୂଲ୍ୟ (args));
		arg_types.safe_ଠେଲ (arg_type);
		type_ok_p &= (arg_type == ବୃକ୍ଷ_ମୂଲ୍ୟ (args));
		args = ବୃକ୍ଷ_CHAIN (args);
	      }

	    ଯଦି (type_ok_p && return_type == ବୃକ୍ଷ_TYPE (type))
	      ଫେରନ୍ତୁ type;

	    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
	    ବୃକ୍ଷ arg_type;
	    FOR_EACH_VEC_ELT_REVERSE (arg_types, i, arg_type)
	      args = ବୃକ୍ଷ_cons (NULL_ବୃକ୍ଷ, arg_type, args);
	    result = build_function_type (return_type, args);
	    ଭାଙ୍ଗ;
	  }

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଫେରନ୍ତୁ canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  ଯଦି (RECORD_OR_UNION_TYPE_P (type) || ବୃକ୍ଷ_CODE (type) == ENUMERAL_TYPE)
    ଫେରନ୍ତୁ build_qualified_type (result, TYPE_QUALS (type));
  ଫେରନ୍ତୁ build_type_attribute_qual_variant (result, TYPE_ATTRIBUTES (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

ସ୍ଥିର ଶୂନ୍ୟ
print_type (c_pretty_printer *cpp, ବୃକ୍ଷ t, ତାର୍କିକ *quoted,
	    ଅଚଳ ଅକ୍ଷର *highlight_color = nullptr)
{
  ଯଦି (t == error_mark_ଗଣ୍ଠି)
    {
      pp_string (cpp, _("{erroneous}"));
      ଫେରନ୍ତୁ;
    }

  ଯଦି (!pp_show_highlight_colors (cpp))
    highlight_color = nullptr;

  gcc_assert (TYPE_P (t));
  ସଂରଚନା obstack *ob = pp_buffer (cpp)->m_obstack;
  ଅକ୍ଷର *p = (ଅକ୍ଷର *) obstack_base (ob);
  /* Remember the end of the initial dump.  */
  ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = obstack_object_size (ob);

  ବୃକ୍ଷ name = TYPE_NAME (t);
  ଯଦି (name && ବୃକ୍ଷ_CODE (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  ଅନ୍ୟଥା
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  ବୃକ୍ଷ aka_type = get_aka_type (t);
  ଯଦି (aka_type != t)
    {
      ଅଚଳ ତାର୍କିକ show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      ସଂରଚନା obstack *ob2 = pp_buffer (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      ଅଚଳ ଅକ୍ଷର *aka = (ଅକ୍ଷର *) obstack_base (ob2);
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା aka_len = obstack_object_size (ob2);
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା type1_len = obstack_object_size (ob) - len;

      /* If they are identical, bail out.  */
      ଯଦି (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	ଫେରନ୍ତୁ;

      /* They're not, print the stripped version now.  */
      ଯଦି (*quoted)
	pp_end_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_ବାମ_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      ଯଦି (*quoted)
	pp_begin_quote (cpp, show_color);
      ଯଦି (highlight_color)
	pp_string (cpp, colorize_start (show_color, highlight_color));
      cpp->type_id (aka_type);
      ଯଦି (*quoted)
	pp_end_quote (cpp, show_color);
      pp_ଡାହାଣ_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = ମିଥ୍ୟା;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

ଶୂନ୍ୟ
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
ସ୍ଥିର ତାର୍କିକ
c_ବୃକ୍ଷ_printer (pretty_printer *pp, text_info *text, ଅଚଳ ଅକ୍ଷର *spec,
		ପୂର୍ଣ୍ଣସଂଖ୍ୟା precision, ତାର୍କିକ wide, ତାର୍କିକ set_locus, ତାର୍କିକ hash,
		ତାର୍କିକ *quoted, pp_token_list &)
{
  ବୃକ୍ଷ t = NULL_ବୃକ୍ଷ;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->set_padding (pp_none);

  ଯଦି (precision != 0 || wide)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଯଦି (*spec != 'v')
    {
      t = va_arg (*text->m_args_ptr, ବୃକ୍ଷ);
      ଯଦି (set_locus)
	text->set_location (0, DECL_SOURCE_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  ବାଛ (*spec)
    {
    ସ୍ଥିତି 'D':
      ଯଦି (VAR_P (t) && DECL_HAS_DEBUG_ପଦସମଷ୍ଟି_P (t))
	{
	  t = DECL_DEBUG_ପଦସମଷ୍ଟି (t);
	  ଯଦି (!DECL_P (t))
	    {
	      cpp->expression (t);
	      ଫେରନ୍ତୁ ସତ୍ୟ;
	    }
	}
      /* FALLTHRU */

    ସ୍ଥିତି 'F':
      ଯଦି (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  ଯଦି (ବୃକ୍ଷ_CODE (t) == FUNCTION_DECL)
	    {
	      pp_c_function_target_version (cpp, t);
	      pp_c_function_target_clones (cpp, t);
	    }
	  ଫେରନ୍ତୁ ସତ୍ୟ;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି 'T':
      print_type (cpp, t, quoted);
      ଫେରନ୍ତୁ ସତ୍ୟ;

    ସ୍ଥିତି 'E':
      ଯଦି (ବୃକ୍ଷ_CODE (t) == IDENTIFIER_ଗଣ୍ଠି)
	pp_identifier (cpp, IDENTIFIER_POINTER (t));
      ଅନ୍ୟଥା
	cpp->expression (t);
      ଫେରନ୍ତୁ ସତ୍ୟ;

    ସ୍ଥିତି 'V':
      pp_c_type_qualifier_list (cpp, t);
      ଫେରନ୍ତୁ ସତ୍ୟ;

    ସ୍ଥିତି 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*text->m_args_ptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା), hash);
      ଫେରନ୍ତୁ ସତ୍ୟ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  pp_string (cpp, _("({anonymous})"));
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_text
range_label_for_type_mismatch::get_text (unsigned /*range_idx*/) ଅଚଳ
{
  ଯଦି (m_labelled_type == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ label_text::borrow (ଖାଲି);

  c_pretty_printer cpp;
  ତାର୍କିକ quoted = ମିଥ୍ୟା;
  print_type (&cpp, m_labelled_type, &quoted);
  ଫେରନ୍ତୁ label_text::take (xstrdup (pp_formatted_text (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
ତାର୍କିକ
has_c_linkage (const_ବୃକ୍ଷ decl ATTRIBUTE_UNUSED)
{
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

ଶୂନ୍ୟ
c_initialize_diagnostics (diagnostics::context *context)
{
  context->set_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_set_defaults (context);
  context->set_format_decoder (&c_ବୃକ୍ଷ_printer);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
c_types_compatible_p (ବୃକ୍ଷ x, ବୃକ୍ଷ y)
{
  ଫେରନ୍ତୁ comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

ତାର୍କିକ
c_var_mod_p (ବୃକ୍ଷ x, ବୃକ୍ଷ fn ATTRIBUTE_UNUSED)
{
  ଫେରନ୍ତୁ c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_set_type
c_get_alias_set (ବୃକ୍ଷ t)
{
  ଫେରନ୍ତୁ c_common_get_alias_set (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

ପୂର୍ଣ୍ଣସଂଖ୍ୟା
maybe_adjust_arg_pos_for_attribute (const_ବୃକ୍ଷ)
{
  ଫେରନ୍ତୁ 0;
}

/* In C, no expression is dependent.  */

ତାର୍କିକ
instantiation_dependent_expression_p (ବୃକ୍ଷ)
{
  ଫେରନ୍ତୁ ମିଥ୍ୟା;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା
c_type_dwarf_attribute (const_ବୃକ୍ଷ type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା attr)
{
  ଯଦି (type == NULL_ବୃକ୍ଷ)
    ଫେରନ୍ତୁ -1;

  ବାଛ (attr)
    {
    ସ୍ଥିତି DW_AT_export_symbols:
      ଯଦି (RECORD_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_ବୃକ୍ଷ)
	ଫେରନ୍ତୁ 1;
      ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }

  ଫେରନ୍ତୁ -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

ବୃକ୍ଷ
c_enum_underlying_base_type (const_ବୃକ୍ଷ type)
{
  ବୃକ୍ଷ underlying_type = ENUM_UNDERLYING_TYPE (type);

  ଯଦି (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_mode (TYPE_MODE (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  ଫେରନ୍ତୁ underlying_type;
}
