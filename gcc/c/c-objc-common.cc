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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "system.h"
#അന്തര്ഭാവ "coretypes.h"
#അന്തര്ഭാവ "c-tree.h"
#അന്തര്ഭാവ "intl.h"
#അന്തര്ഭാവ "c-family/c-pretty-print.h"
#അന്തര്ഭാവ "tree-core.h"
#അന്തര്ഭാവ "tree-pretty-print.h"
#അന്തര്ഭാവ "tree-pretty-print-markup.h"
#അന്തര്ഭാവ "gimple-pretty-print.h"
#അന്തര്ഭാവ "langhooks.h"
#അന്തര്ഭാവ "c-objc-common.h"
#അന്തര്ഭാവ "c-family/c-type-mismatch.h"
#അന്തര്ഭാവ "stringpool.h"
#അന്തര്ഭാവ "attribs.h"
#അന്തര്ഭാവ "dwarf2.h"

സ്ഥിതം തർക്കം c_വൃക്ഷം_printer (pretty_printer *, text_info *, സ്ഥിരം അക്ഷരം *,
			    പൂർണ്ണസംഖ്യ, തർക്കം, തർക്കം, തർക്കം, തർക്കം *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

ഘടന c_feature_info
{
  സ്ഥിരം അക്ഷരം *ident;
  സ്ഥിരം പൂർണ്ണസംഖ്യ *enable_flag;
};

സ്ഥിതം സ്ഥിരം c_feature_info c_feature_table[] =
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

ശൂന്യം
c_register_features ()
{
  വേണ്ടി (unsigned i = 0; i < ARRAY_SIZE (c_feature_table); i++)
    {
      സ്ഥിരം c_feature_info *info = c_feature_table + i;
      സ്ഥിരം തർക്കം feat_p = !info->enable_flag || *info->enable_flag;
      c_common_register_feature (info->ident, feat_p);
    }
}

തർക്കം
c_missing_noreturn_ok_p (വൃക്ഷം decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  എങ്കിൽ (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    തിരികെ അസത്യം;

  തിരികെ flag_hosted
    || TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (decl))) == integer_type_കണ്ണി;
}

/* Called from check_global_declaration.  */

തർക്കം
c_warn_unused_global_decl (const_വൃക്ഷം decl)
{
  എങ്കിൽ (വൃക്ഷം_CODE (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    തിരികെ അസത്യം;
  എങ്കിൽ (DECL_IN_SYSTEM_HEADER (decl))
    തിരികെ അസത്യം;

  തിരികെ സത്യം;
}

/* Initialization common to C and Objective-C front ends.  */
തർക്കം
c_objc_common_init (ശൂന്യം)
{
  c_init_decl_processing ();

  തിരികെ c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

സ്ഥിതം വൃക്ഷം
get_aka_type (വൃക്ഷം type)
{
  എങ്കിൽ (type == error_mark_കണ്ണി)
    തിരികെ type;

  വൃക്ഷം result;
  എങ്കിൽ (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      വൃക്ഷം orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      വൃക്ഷം_code code = വൃക്ഷം_CODE (orig_type);
      വൃക്ഷം orig_id = TYPE_IDENTIFIER (orig_type);
      എങ്കിൽ ((code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	തിരികെ type;

      എങ്കിൽ (!user_facing_original_type_p (type))
	തിരികെ type;

      result = get_aka_type (orig_type);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (type) == ENUMERAL_TYPE)
    തിരികെ type;
  അല്ലെങ്കിൽ
    {
      വൃക്ഷം canonical = TYPE_CANONICAL (type);
      എങ്കിൽ (canonical && വൃക്ഷം_CODE (type) != വൃക്ഷം_CODE (canonical))
	തിരികെ canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      തിരഞ്ഞെടുപ്പ് (വൃക്ഷം_CODE (type))
	{
	അവസ്ഥ POINTER_TYPE:
	അവസ്ഥ REFERENCE_TYPE:
	  {
	    വൃക്ഷം target_type = get_aka_type (വൃക്ഷം_TYPE (type));

	    എങ്കിൽ (target_type == വൃക്ഷം_TYPE (type))
	      തിരികെ type;

	    എങ്കിൽ (canonical && target_type == വൃക്ഷം_TYPE (canonical))
	      തിരികെ canonical;

	    result = (വൃക്ഷം_CODE (type) == POINTER_TYPE
		      ? build_pointer_type (target_type)
		      : build_reference_type (target_type));
	    നിർത്തുക;
	  }

	അവസ്ഥ ARRAY_TYPE:
	  {
	    വൃക്ഷം element_type = get_aka_type (വൃക്ഷം_TYPE (type));
	    വൃക്ഷം index_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_വൃക്ഷം);

	    എങ്കിൽ (element_type == വൃക്ഷം_TYPE (type)
		&& index_type == TYPE_DOMAIN (type))
	      തിരികെ type;

	    എങ്കിൽ (canonical
		&& element_type == വൃക്ഷം_TYPE (canonical)
		&& index_type == TYPE_DOMAIN (canonical))
	      തിരികെ canonical;

	    result = build_array_type (element_type, index_type,
				       TYPE_TYPELESS_STORAGE (type));
	    നിർത്തുക;
	  }

	അവസ്ഥ FUNCTION_TYPE:
	  {
	    വൃക്ഷം return_type = get_aka_type (വൃക്ഷം_TYPE (type));

	    വൃക്ഷം args = TYPE_ARG_TYPES (type);
	    എങ്കിൽ (args == error_mark_കണ്ണി)
	      തിരികെ type;

	    auto_vec<വൃക്ഷം, 32> arg_types;
	    തർക്കം type_ok_p = സത്യം;
	    ആകുമ്പോൾ (args && args != void_list_കണ്ണി)
	      {
		വൃക്ഷം arg_type = get_aka_type (വൃക്ഷം_മൂല്യം (args));
		arg_types.safe_തള്ളുക (arg_type);
		type_ok_p &= (arg_type == വൃക്ഷം_മൂല്യം (args));
		args = വൃക്ഷം_CHAIN (args);
	      }

	    എങ്കിൽ (type_ok_p && return_type == വൃക്ഷം_TYPE (type))
	      തിരികെ type;

	    unsigned പൂർണ്ണസംഖ്യ i;
	    വൃക്ഷം arg_type;
	    FOR_EACH_VEC_ELT_REVERSE (arg_types, i, arg_type)
	      args = വൃക്ഷം_cons (NULL_വൃക്ഷം, arg_type, args);
	    result = build_function_type (return_type, args);
	    നിർത്തുക;
	  }

	സ്ഥിരസ്ഥിതി:
	  തിരികെ canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  എങ്കിൽ (RECORD_OR_UNION_TYPE_P (type) || വൃക്ഷം_CODE (type) == ENUMERAL_TYPE)
    തിരികെ build_qualified_type (result, TYPE_QUALS (type));
  തിരികെ build_type_attribute_qual_variant (result, TYPE_ATTRIBUTES (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

സ്ഥിതം ശൂന്യം
print_type (c_pretty_printer *cpp, വൃക്ഷം t, തർക്കം *quoted,
	    സ്ഥിരം അക്ഷരം *highlight_color = nullptr)
{
  എങ്കിൽ (t == error_mark_കണ്ണി)
    {
      pp_string (cpp, _("{erroneous}"));
      തിരികെ;
    }

  എങ്കിൽ (!pp_show_highlight_colors (cpp))
    highlight_color = nullptr;

  gcc_assert (TYPE_P (t));
  ഘടന obstack *ob = pp_buffer (cpp)->m_obstack;
  അക്ഷരം *p = (അക്ഷരം *) obstack_base (ob);
  /* Remember the end of the initial dump.  */
  പൂർണ്ണസംഖ്യ len = obstack_object_size (ob);

  വൃക്ഷം name = TYPE_NAME (t);
  എങ്കിൽ (name && വൃക്ഷം_CODE (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  അല്ലെങ്കിൽ
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  വൃക്ഷം aka_type = get_aka_type (t);
  എങ്കിൽ (aka_type != t)
    {
      സ്ഥിരം തർക്കം show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      ഘടന obstack *ob2 = pp_buffer (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      സ്ഥിരം അക്ഷരം *aka = (അക്ഷരം *) obstack_base (ob2);
      പൂർണ്ണസംഖ്യ aka_len = obstack_object_size (ob2);
      പൂർണ്ണസംഖ്യ type1_len = obstack_object_size (ob) - len;

      /* If they are identical, bail out.  */
      എങ്കിൽ (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	തിരികെ;

      /* They're not, print the stripped version now.  */
      എങ്കിൽ (*quoted)
	pp_end_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_ഇടത്_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      എങ്കിൽ (*quoted)
	pp_begin_quote (cpp, show_color);
      എങ്കിൽ (highlight_color)
	pp_string (cpp, colorize_start (show_color, highlight_color));
      cpp->type_id (aka_type);
      എങ്കിൽ (*quoted)
	pp_end_quote (cpp, show_color);
      pp_വലത്_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = അസത്യം;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

ശൂന്യം
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
സ്ഥിതം തർക്കം
c_വൃക്ഷം_printer (pretty_printer *pp, text_info *text, സ്ഥിരം അക്ഷരം *spec,
		പൂർണ്ണസംഖ്യ precision, തർക്കം wide, തർക്കം set_locus, തർക്കം hash,
		തർക്കം *quoted, pp_token_list &)
{
  വൃക്ഷം t = NULL_വൃക്ഷം;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->set_padding (pp_none);

  എങ്കിൽ (precision != 0 || wide)
    തിരികെ അസത്യം;

  എങ്കിൽ (*spec != 'v')
    {
      t = va_arg (*text->m_args_ptr, വൃക്ഷം);
      എങ്കിൽ (set_locus)
	text->set_location (0, DECL_SOURCE_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  തിരഞ്ഞെടുപ്പ് (*spec)
    {
    അവസ്ഥ 'D':
      എങ്കിൽ (VAR_P (t) && DECL_HAS_DEBUG_വ്യഞ്ജകം_P (t))
	{
	  t = DECL_DEBUG_വ്യഞ്ജകം (t);
	  എങ്കിൽ (!DECL_P (t))
	    {
	      cpp->expression (t);
	      തിരികെ സത്യം;
	    }
	}
      /* FALLTHRU */

    അവസ്ഥ 'F':
      എങ്കിൽ (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  എങ്കിൽ (വൃക്ഷം_CODE (t) == FUNCTION_DECL)
	    {
	      pp_c_function_target_version (cpp, t);
	      pp_c_function_target_clones (cpp, t);
	    }
	  തിരികെ സത്യം;
	}
      നിർത്തുക;

    അവസ്ഥ 'T':
      print_type (cpp, t, quoted);
      തിരികെ സത്യം;

    അവസ്ഥ 'E':
      എങ്കിൽ (വൃക്ഷം_CODE (t) == IDENTIFIER_കണ്ണി)
	pp_identifier (cpp, IDENTIFIER_POINTER (t));
      അല്ലെങ്കിൽ
	cpp->expression (t);
      തിരികെ സത്യം;

    അവസ്ഥ 'V':
      pp_c_type_qualifier_list (cpp, t);
      തിരികെ സത്യം;

    അവസ്ഥ 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*text->m_args_ptr, പൂർണ്ണസംഖ്യ), hash);
      തിരികെ സത്യം;

    സ്ഥിരസ്ഥിതി:
      തിരികെ അസത്യം;
    }

  pp_string (cpp, _("({anonymous})"));
  തിരികെ സത്യം;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_text
range_label_for_type_mismatch::get_text (unsigned /*range_idx*/) സ്ഥിരം
{
  എങ്കിൽ (m_labelled_type == NULL_വൃക്ഷം)
    തിരികെ label_text::borrow (ശൂന്യ);

  c_pretty_printer cpp;
  തർക്കം quoted = അസത്യം;
  print_type (&cpp, m_labelled_type, &quoted);
  തിരികെ label_text::take (xstrdup (pp_formatted_text (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
തർക്കം
has_c_linkage (const_വൃക്ഷം decl ATTRIBUTE_UNUSED)
{
  തിരികെ സത്യം;
}

ശൂന്യം
c_initialize_diagnostics (diagnostics::context *context)
{
  context->set_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_set_defaults (context);
  context->set_format_decoder (&c_വൃക്ഷം_printer);
}

പൂർണ്ണസംഖ്യ
c_types_compatible_p (വൃക്ഷം x, വൃക്ഷം y)
{
  തിരികെ comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

തർക്കം
c_var_mod_p (വൃക്ഷം x, വൃക്ഷം fn ATTRIBUTE_UNUSED)
{
  തിരികെ c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_set_type
c_get_alias_set (വൃക്ഷം t)
{
  തിരികെ c_common_get_alias_set (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

പൂർണ്ണസംഖ്യ
maybe_adjust_arg_pos_for_attribute (const_വൃക്ഷം)
{
  തിരികെ 0;
}

/* In C, no expression is dependent.  */

തർക്കം
instantiation_dependent_expression_p (വൃക്ഷം)
{
  തിരികെ അസത്യം;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
പൂർണ്ണസംഖ്യ
c_type_dwarf_attribute (const_വൃക്ഷം type, പൂർണ്ണസംഖ്യ attr)
{
  എങ്കിൽ (type == NULL_വൃക്ഷം)
    തിരികെ -1;

  തിരഞ്ഞെടുപ്പ് (attr)
    {
    അവസ്ഥ DW_AT_export_symbols:
      എങ്കിൽ (RECORD_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_വൃക്ഷം)
	തിരികെ 1;
      നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
      നിർത്തുക;
    }

  തിരികെ -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

വൃക്ഷം
c_enum_underlying_base_type (const_വൃക്ഷം type)
{
  വൃക്ഷം underlying_type = ENUM_UNDERLYING_TYPE (type);

  എങ്കിൽ (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_mode (TYPE_MODE (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  തിരികെ underlying_type;
}
