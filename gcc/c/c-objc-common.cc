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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "intl.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-pretty-print.h"
#ಅನ್ತರ್ಭಾವ "tree-core.h"
#ಅನ್ತರ್ಭಾವ "tree-pretty-print.h"
#ಅನ್ತರ್ಭಾವ "tree-pretty-print-markup.h"
#ಅನ್ತರ್ಭಾವ "gimple-pretty-print.h"
#ಅನ್ತರ್ಭಾವ "langhooks.h"
#ಅನ್ತರ್ಭಾವ "c-objc-common.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-type-mismatch.h"
#ಅನ್ತರ್ಭಾವ "stringpool.h"
#ಅನ್ತರ್ಭಾವ "attribs.h"
#ಅನ್ತರ್ಭಾವ "dwarf2.h"

ಸ್ಥಿರ ತಾರ್ಕಿಕ c_ವೃಕ್ಷ_printer (pretty_printer *, text_info *, ಧ್ರುವ ವರ್ಣ *,
			    ಪೂರ್ಣಾಙ್ಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

ಸಂರಚನಾ c_feature_info
{
  ಧ್ರುವ ವರ್ಣ *ident;
  ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *enable_flag;
};

ಸ್ಥಿರ ಧ್ರುವ c_feature_info c_feature_table[] =
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

ಶೂನ್ಯ
c_register_features ()
{
  ಪ್ರತಿ (unsigned i = 0; i < ARRAY_SIZE (c_feature_table); i++)
    {
      ಧ್ರುವ c_feature_info *info = c_feature_table + i;
      ಧ್ರುವ ತಾರ್ಕಿಕ feat_p = !info->enable_flag || *info->enable_flag;
      c_common_register_feature (info->ident, feat_p);
    }
}

ತಾರ್ಕಿಕ
c_missing_noreturn_ok_p (ವೃಕ್ಷ decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  ಯದಿ (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ flag_hosted
    || TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl))) == integer_type_ಗಂಟು;
}

/* Called from check_global_declaration.  */

ತಾರ್ಕಿಕ
c_warn_unused_global_decl (const_ವೃಕ್ಷ decl)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (DECL_IN_SYSTEM_HEADER (decl))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Initialization common to C and Objective-C front ends.  */
ತಾರ್ಕಿಕ
c_objc_common_init (ಶೂನ್ಯ)
{
  c_init_decl_processing ();

  ಪ್ರತ್ಯಾಗಮ c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

ಸ್ಥಿರ ವೃಕ್ಷ
get_aka_type (ವೃಕ್ಷ type)
{
  ಯದಿ (type == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ type;

  ವೃಕ್ಷ result;
  ಯದಿ (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      ವೃಕ್ಷ orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (orig_type);
      ವೃಕ್ಷ orig_id = TYPE_IDENTIFIER (orig_type);
      ಯದಿ ((code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	ಪ್ರತ್ಯಾಗಮ type;

      ಯದಿ (!user_facing_original_type_p (type))
	ಪ್ರತ್ಯಾಗಮ type;

      result = get_aka_type (orig_type);
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE)
    ಪ್ರತ್ಯಾಗಮ type;
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ canonical = TYPE_CANONICAL (type);
      ಯದಿ (canonical && ವೃಕ್ಷ_CODE (type) != ವೃಕ್ಷ_CODE (canonical))
	ಪ್ರತ್ಯಾಗಮ canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (type))
	{
	ಪಕ್ಷ POINTER_TYPE:
	ಪಕ್ಷ REFERENCE_TYPE:
	  {
	    ವೃಕ್ಷ target_type = get_aka_type (ವೃಕ್ಷ_TYPE (type));

	    ಯದಿ (target_type == ವೃಕ್ಷ_TYPE (type))
	      ಪ್ರತ್ಯಾಗಮ type;

	    ಯದಿ (canonical && target_type == ವೃಕ್ಷ_TYPE (canonical))
	      ಪ್ರತ್ಯಾಗಮ canonical;

	    result = (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
		      ? build_pointer_type (target_type)
		      : build_reference_type (target_type));
	    ಭಙ್ಗ;
	  }

	ಪಕ್ಷ ARRAY_TYPE:
	  {
	    ವೃಕ್ಷ element_type = get_aka_type (ವೃಕ್ಷ_TYPE (type));
	    ವೃಕ್ಷ index_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_ವೃಕ್ಷ);

	    ಯದಿ (element_type == ವೃಕ್ಷ_TYPE (type)
		&& index_type == TYPE_DOMAIN (type))
	      ಪ್ರತ್ಯಾಗಮ type;

	    ಯದಿ (canonical
		&& element_type == ವೃಕ್ಷ_TYPE (canonical)
		&& index_type == TYPE_DOMAIN (canonical))
	      ಪ್ರತ್ಯಾಗಮ canonical;

	    result = build_array_type (element_type, index_type,
				       TYPE_TYPELESS_STORAGE (type));
	    ಭಙ್ಗ;
	  }

	ಪಕ್ಷ FUNCTION_TYPE:
	  {
	    ವೃಕ್ಷ return_type = get_aka_type (ವೃಕ್ಷ_TYPE (type));

	    ವೃಕ್ಷ args = TYPE_ARG_TYPES (type);
	    ಯದಿ (args == error_mark_ಗಂಟು)
	      ಪ್ರತ್ಯಾಗಮ type;

	    auto_vec<ವೃಕ್ಷ, 32> arg_types;
	    ತಾರ್ಕಿಕ type_ok_p = ಸತ್ಯ;
	    ಯಾವತ್ (args && args != void_list_ಗಂಟು)
	      {
		ವೃಕ್ಷ arg_type = get_aka_type (ವೃಕ್ಷ_ಮೌಲ್ಯ (args));
		arg_types.safe_ತಳ್ಳು (arg_type);
		type_ok_p &= (arg_type == ವೃಕ್ಷ_ಮೌಲ್ಯ (args));
		args = ವೃಕ್ಷ_CHAIN (args);
	      }

	    ಯದಿ (type_ok_p && return_type == ವೃಕ್ಷ_TYPE (type))
	      ಪ್ರತ್ಯಾಗಮ type;

	    unsigned ಪೂರ್ಣಾಙ್ಕ i;
	    ವೃಕ್ಷ arg_type;
	    FOR_EACH_VEC_ELT_REVERSE (arg_types, i, arg_type)
	      args = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, arg_type, args);
	    result = build_function_type (return_type, args);
	    ಭಙ್ಗ;
	  }

	ಸ್ವಭಾವ:
	  ಪ್ರತ್ಯಾಗಮ canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  ಯದಿ (RECORD_OR_UNION_TYPE_P (type) || ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE)
    ಪ್ರತ್ಯಾಗಮ build_qualified_type (result, TYPE_QUALS (type));
  ಪ್ರತ್ಯಾಗಮ build_type_attribute_qual_variant (result, TYPE_ATTRIBUTES (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

ಸ್ಥಿರ ಶೂನ್ಯ
print_type (c_pretty_printer *cpp, ವೃಕ್ಷ t, ತಾರ್ಕಿಕ *quoted,
	    ಧ್ರುವ ವರ್ಣ *highlight_color = nullptr)
{
  ಯದಿ (t == error_mark_ಗಂಟು)
    {
      pp_string (cpp, _("{erroneous}"));
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (!pp_show_highlight_colors (cpp))
    highlight_color = nullptr;

  gcc_assert (TYPE_P (t));
  ಸಂರಚನಾ obstack *ob = pp_buffer (cpp)->m_obstack;
  ವರ್ಣ *p = (ವರ್ಣ *) obstack_base (ob);
  /* Remember the end of the initial dump.  */
  ಪೂರ್ಣಾಙ್ಕ len = obstack_object_size (ob);

  ವೃಕ್ಷ name = TYPE_NAME (t);
  ಯದಿ (name && ವೃಕ್ಷ_CODE (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  ಅನ್ಯಥಾ
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  ವೃಕ್ಷ aka_type = get_aka_type (t);
  ಯದಿ (aka_type != t)
    {
      ಧ್ರುವ ತಾರ್ಕಿಕ show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      ಸಂರಚನಾ obstack *ob2 = pp_buffer (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      ಧ್ರುವ ವರ್ಣ *aka = (ವರ್ಣ *) obstack_base (ob2);
      ಪೂರ್ಣಾಙ್ಕ aka_len = obstack_object_size (ob2);
      ಪೂರ್ಣಾಙ್ಕ type1_len = obstack_object_size (ob) - len;

      /* If they are identical, bail out.  */
      ಯದಿ (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	ಪ್ರತ್ಯಾಗಮ;

      /* They're not, print the stripped version now.  */
      ಯದಿ (*quoted)
	pp_end_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_ಎಡ_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      ಯದಿ (*quoted)
	pp_begin_quote (cpp, show_color);
      ಯದಿ (highlight_color)
	pp_string (cpp, colorize_start (show_color, highlight_color));
      cpp->type_id (aka_type);
      ಯದಿ (*quoted)
	pp_end_quote (cpp, show_color);
      pp_ಬಲ_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = ಅಸತ್ಯ;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

ಶೂನ್ಯ
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
ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_ವೃಕ್ಷ_printer (pretty_printer *pp, text_info *text, ಧ್ರುವ ವರ್ಣ *spec,
		ಪೂರ್ಣಾಙ್ಕ precision, ತಾರ್ಕಿಕ wide, ತಾರ್ಕಿಕ set_locus, ತಾರ್ಕಿಕ hash,
		ತಾರ್ಕಿಕ *quoted, pp_token_list &)
{
  ವೃಕ್ಷ t = NULL_ವೃಕ್ಷ;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->set_padding (pp_none);

  ಯದಿ (precision != 0 || wide)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಯದಿ (*spec != 'v')
    {
      t = va_arg (*text->m_args_ptr, ವೃಕ್ಷ);
      ಯದಿ (set_locus)
	text->set_location (0, DECL_SOURCE_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  ವಿಕಲ್ಪ (*spec)
    {
    ಪಕ್ಷ 'D':
      ಯದಿ (VAR_P (t) && DECL_HAS_DEBUG_ಅಭಿವ್ಯಕ್ತಿ_P (t))
	{
	  t = DECL_DEBUG_ಅಭಿವ್ಯಕ್ತಿ (t);
	  ಯದಿ (!DECL_P (t))
	    {
	      cpp->expression (t);
	      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	    }
	}
      /* FALLTHRU */

    ಪಕ್ಷ 'F':
      ಯದಿ (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == FUNCTION_DECL)
	    {
	      pp_c_function_target_version (cpp, t);
	      pp_c_function_target_clones (cpp, t);
	    }
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ 'T':
      print_type (cpp, t, quoted);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಪಕ್ಷ 'E':
      ಯದಿ (ವೃಕ್ಷ_CODE (t) == IDENTIFIER_ಗಂಟು)
	pp_identifier (cpp, IDENTIFIER_POINTER (t));
      ಅನ್ಯಥಾ
	cpp->expression (t);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಪಕ್ಷ 'V':
      pp_c_type_qualifier_list (cpp, t);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಪಕ್ಷ 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*text->m_args_ptr, ಪೂರ್ಣಾಙ್ಕ), hash);
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  pp_string (cpp, _("({anonymous})"));
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_text
range_label_for_type_mismatch::get_text (unsigned /*range_idx*/) ಧ್ರುವ
{
  ಯದಿ (m_labelled_type == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ label_text::borrow (ರಿಕ್ತ);

  c_pretty_printer cpp;
  ತಾರ್ಕಿಕ quoted = ಅಸತ್ಯ;
  print_type (&cpp, m_labelled_type, &quoted);
  ಪ್ರತ್ಯಾಗಮ label_text::take (xstrdup (pp_formatted_text (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
ತಾರ್ಕಿಕ
has_c_linkage (const_ವೃಕ್ಷ decl ATTRIBUTE_UNUSED)
{
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಶೂನ್ಯ
c_initialize_diagnostics (diagnostics::context *context)
{
  context->set_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_set_defaults (context);
  context->set_format_decoder (&c_ವೃಕ್ಷ_printer);
}

ಪೂರ್ಣಾಙ್ಕ
c_types_compatible_p (ವೃಕ್ಷ x, ವೃಕ್ಷ y)
{
  ಪ್ರತ್ಯಾಗಮ comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

ತಾರ್ಕಿಕ
c_var_mod_p (ವೃಕ್ಷ x, ವೃಕ್ಷ fn ATTRIBUTE_UNUSED)
{
  ಪ್ರತ್ಯಾಗಮ c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_set_type
c_get_alias_set (ವೃಕ್ಷ t)
{
  ಪ್ರತ್ಯಾಗಮ c_common_get_alias_set (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

ಪೂರ್ಣಾಙ್ಕ
maybe_adjust_arg_pos_for_attribute (const_ವೃಕ್ಷ)
{
  ಪ್ರತ್ಯಾಗಮ 0;
}

/* In C, no expression is dependent.  */

ತಾರ್ಕಿಕ
instantiation_dependent_expression_p (ವೃಕ್ಷ)
{
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
ಪೂರ್ಣಾಙ್ಕ
c_type_dwarf_attribute (const_ವೃಕ್ಷ type, ಪೂರ್ಣಾಙ್ಕ attr)
{
  ಯದಿ (type == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ -1;

  ವಿಕಲ್ಪ (attr)
    {
    ಪಕ್ಷ DW_AT_export_symbols:
      ಯದಿ (RECORD_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_ವೃಕ್ಷ)
	ಪ್ರತ್ಯಾಗಮ 1;
      ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }

  ಪ್ರತ್ಯಾಗಮ -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

ವೃಕ್ಷ
c_enum_underlying_base_type (const_ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ underlying_type = ENUM_UNDERLYING_TYPE (type);

  ಯದಿ (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_mode (TYPE_MODE (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  ಪ್ರತ್ಯಾಗಮ underlying_type;
}
