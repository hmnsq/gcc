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

#अन्तर्भाव "config.h"
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "intl.h"
#अन्तर्भाव "c-family/c-pretty-print.h"
#अन्तर्भाव "tree-core.h"
#अन्तर्भाव "tree-pretty-print.h"
#अन्तर्भाव "tree-pretty-print-markup.h"
#अन्तर्भाव "gimple-pretty-print.h"
#अन्तर्भाव "langhooks.h"
#अन्तर्भाव "c-objc-common.h"
#अन्तर्भाव "c-family/c-type-mismatch.h"
#अन्तर्भाव "stringpool.h"
#अन्तर्भाव "attribs.h"
#अन्तर्भाव "dwarf2.h"

स्थिर तार्किक c_वृक्षः_printer (pretty_printer *, text_info *, ध्रुव वर्ण *,
			    पूर्णाङ्क, तार्किक, तार्किक, तार्किक, तार्किक *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

संरचना c_feature_info
{
  ध्रुव वर्ण *ident;
  ध्रुव पूर्णाङ्क *enable_flag;
};

स्थिर ध्रुव c_feature_info c_feature_table[] =
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

शून्य
c_register_features ()
{
  अत्थाय (unsigned i = 0; i < ARRAY_SIZE (c_feature_table); i++)
    {
      ध्रुव c_feature_info *info = c_feature_table + i;
      ध्रुव तार्किक feat_p = !info->enable_flag || *info->enable_flag;
      c_common_register_feature (info->ident, feat_p);
    }
}

तार्किक
c_missing_noreturn_ok_p (वृक्षः decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  सचे (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    पटिनिवत्त मिच्छा;

  पटिनिवत्त flag_hosted
    || TYPE_MAIN_VARIANT (वृक्षः_TYPE (वृक्षः_TYPE (decl))) == integer_type_ग्रन्थिः;
}

/* Called from check_global_declaration.  */

तार्किक
c_warn_unused_global_decl (const_वृक्षः decl)
{
  सचे (वृक्षः_CODE (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    पटिनिवत्त मिच्छा;
  सचे (DECL_IN_SYSTEM_HEADER (decl))
    पटिनिवत्त मिच्छा;

  पटिनिवत्त सच्च;
}

/* Initialization common to C and Objective-C front ends.  */
तार्किक
c_objc_common_init (शून्य)
{
  c_init_decl_processing ();

  पटिनिवत्त c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

स्थिर वृक्षः
get_aka_type (वृक्षः type)
{
  सचे (type == error_mark_ग्रन्थिः)
    पटिनिवत्त type;

  वृक्षः result;
  सचे (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      वृक्षः orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      वृक्षः_code code = वृक्षः_CODE (orig_type);
      वृक्षः orig_id = TYPE_IDENTIFIER (orig_type);
      सचे ((code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	पटिनिवत्त type;

      सचे (!user_facing_original_type_p (type))
	पटिनिवत्त type;

      result = get_aka_type (orig_type);
    }
  अञ्ञथा सचे (वृक्षः_CODE (type) == ENUMERAL_TYPE)
    पटिनिवत्त type;
  अञ्ञथा
    {
      वृक्षः canonical = TYPE_CANONICAL (type);
      सचे (canonical && वृक्षः_CODE (type) != वृक्षः_CODE (canonical))
	पटिनिवत्त canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      विकल्प (वृक्षः_CODE (type))
	{
	पक्ष POINTER_TYPE:
	पक्ष REFERENCE_TYPE:
	  {
	    वृक्षः target_type = get_aka_type (वृक्षः_TYPE (type));

	    सचे (target_type == वृक्षः_TYPE (type))
	      पटिनिवत्त type;

	    सचे (canonical && target_type == वृक्षः_TYPE (canonical))
	      पटिनिवत्त canonical;

	    result = (वृक्षः_CODE (type) == POINTER_TYPE
		      ? build_pointer_type (target_type)
		      : build_reference_type (target_type));
	    भङ्ग;
	  }

	पक्ष ARRAY_TYPE:
	  {
	    वृक्षः element_type = get_aka_type (वृक्षः_TYPE (type));
	    वृक्षः index_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_वृक्षः);

	    सचे (element_type == वृक्षः_TYPE (type)
		&& index_type == TYPE_DOMAIN (type))
	      पटिनिवत्त type;

	    सचे (canonical
		&& element_type == वृक्षः_TYPE (canonical)
		&& index_type == TYPE_DOMAIN (canonical))
	      पटिनिवत्त canonical;

	    result = build_array_type (element_type, index_type,
				       TYPE_TYPELESS_STORAGE (type));
	    भङ्ग;
	  }

	पक्ष FUNCTION_TYPE:
	  {
	    वृक्षः return_type = get_aka_type (वृक्षः_TYPE (type));

	    वृक्षः args = TYPE_ARG_TYPES (type);
	    सचे (args == error_mark_ग्रन्थिः)
	      पटिनिवत्त type;

	    auto_vec<वृक्षः, 32> arg_types;
	    तार्किक type_ok_p = सच्च;
	    याव (args && args != void_list_ग्रन्थिः)
	      {
		वृक्षः arg_type = get_aka_type (वृक्षः_मानम् (args));
		arg_types.safe_प्रक्षिप (arg_type);
		type_ok_p &= (arg_type == वृक्षः_मानम् (args));
		args = वृक्षः_CHAIN (args);
	      }

	    सचे (type_ok_p && return_type == वृक्षः_TYPE (type))
	      पटिनिवत्त type;

	    unsigned पूर्णाङ्क i;
	    वृक्षः arg_type;
	    FOR_EACH_VEC_ELT_REVERSE (arg_types, i, arg_type)
	      args = वृक्षः_cons (NULL_वृक्षः, arg_type, args);
	    result = build_function_type (return_type, args);
	    भङ्ग;
	  }

	स्वभाव:
	  पटिनिवत्त canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  सचे (RECORD_OR_UNION_TYPE_P (type) || वृक्षः_CODE (type) == ENUMERAL_TYPE)
    पटिनिवत्त build_qualified_type (result, TYPE_QUALS (type));
  पटिनिवत्त build_type_attribute_qual_variant (result, TYPE_ATTRIBUTES (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

स्थिर शून्य
print_type (c_pretty_printer *cpp, वृक्षः t, तार्किक *quoted,
	    ध्रुव वर्ण *highlight_color = nullptr)
{
  सचे (t == error_mark_ग्रन्थिः)
    {
      pp_string (cpp, _("{erroneous}"));
      पटिनिवत्त;
    }

  सचे (!pp_show_highlight_colors (cpp))
    highlight_color = nullptr;

  gcc_assert (TYPE_P (t));
  संरचना obstack *ob = pp_buffer (cpp)->m_obstack;
  वर्ण *p = (वर्ण *) obstack_base (ob);
  /* Remember the end of the initial dump.  */
  पूर्णाङ्क len = obstack_object_size (ob);

  वृक्षः name = TYPE_NAME (t);
  सचे (name && वृक्षः_CODE (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  अञ्ञथा
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  वृक्षः aka_type = get_aka_type (t);
  सचे (aka_type != t)
    {
      ध्रुव तार्किक show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      संरचना obstack *ob2 = pp_buffer (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      ध्रुव वर्ण *aka = (वर्ण *) obstack_base (ob2);
      पूर्णाङ्क aka_len = obstack_object_size (ob2);
      पूर्णाङ्क type1_len = obstack_object_size (ob) - len;

      /* If they are identical, bail out.  */
      सचे (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	पटिनिवत्त;

      /* They're not, print the stripped version now.  */
      सचे (*quoted)
	pp_end_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_वामः_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      सचे (*quoted)
	pp_begin_quote (cpp, show_color);
      सचे (highlight_color)
	pp_string (cpp, colorize_start (show_color, highlight_color));
      cpp->type_id (aka_type);
      सचे (*quoted)
	pp_end_quote (cpp, show_color);
      pp_दक्षिणः_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = मिच्छा;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

शून्य
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
स्थिर तार्किक
c_वृक्षः_printer (pretty_printer *pp, text_info *text, ध्रुव वर्ण *spec,
		पूर्णाङ्क precision, तार्किक wide, तार्किक set_locus, तार्किक hash,
		तार्किक *quoted, pp_token_list &)
{
  वृक्षः t = NULL_वृक्षः;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->set_padding (pp_none);

  सचे (precision != 0 || wide)
    पटिनिवत्त मिच्छा;

  सचे (*spec != 'v')
    {
      t = va_arg (*text->m_args_ptr, वृक्षः);
      सचे (set_locus)
	text->set_location (0, DECL_SOURCE_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  विकल्प (*spec)
    {
    पक्ष 'D':
      सचे (VAR_P (t) && DECL_HAS_DEBUG_व्यञ्जकम्_P (t))
	{
	  t = DECL_DEBUG_व्यञ्जकम् (t);
	  सचे (!DECL_P (t))
	    {
	      cpp->expression (t);
	      पटिनिवत्त सच्च;
	    }
	}
      /* FALLTHRU */

    पक्ष 'F':
      सचे (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  सचे (वृक्षः_CODE (t) == FUNCTION_DECL)
	    {
	      pp_c_function_target_version (cpp, t);
	      pp_c_function_target_clones (cpp, t);
	    }
	  पटिनिवत्त सच्च;
	}
      भङ्ग;

    पक्ष 'T':
      print_type (cpp, t, quoted);
      पटिनिवत्त सच्च;

    पक्ष 'E':
      सचे (वृक्षः_CODE (t) == IDENTIFIER_ग्रन्थिः)
	pp_identifier (cpp, IDENTIFIER_POINTER (t));
      अञ्ञथा
	cpp->expression (t);
      पटिनिवत्त सच्च;

    पक्ष 'V':
      pp_c_type_qualifier_list (cpp, t);
      पटिनिवत्त सच्च;

    पक्ष 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*text->m_args_ptr, पूर्णाङ्क), hash);
      पटिनिवत्त सच्च;

    स्वभाव:
      पटिनिवत्त मिच्छा;
    }

  pp_string (cpp, _("({anonymous})"));
  पटिनिवत्त सच्च;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_text
range_label_for_type_mismatch::get_text (unsigned /*range_idx*/) ध्रुव
{
  सचे (m_labelled_type == NULL_वृक्षः)
    पटिनिवत्त label_text::borrow (रिक्त);

  c_pretty_printer cpp;
  तार्किक quoted = मिच्छा;
  print_type (&cpp, m_labelled_type, &quoted);
  पटिनिवत्त label_text::take (xstrdup (pp_formatted_text (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
तार्किक
has_c_linkage (const_वृक्षः decl ATTRIBUTE_UNUSED)
{
  पटिनिवत्त सच्च;
}

शून्य
c_initialize_diagnostics (diagnostics::context *context)
{
  context->set_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_set_defaults (context);
  context->set_format_decoder (&c_वृक्षः_printer);
}

पूर्णाङ्क
c_types_compatible_p (वृक्षः x, वृक्षः y)
{
  पटिनिवत्त comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

तार्किक
c_var_mod_p (वृक्षः x, वृक्षः fn ATTRIBUTE_UNUSED)
{
  पटिनिवत्त c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_set_type
c_get_alias_set (वृक्षः t)
{
  पटिनिवत्त c_common_get_alias_set (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

पूर्णाङ्क
maybe_adjust_arg_pos_for_attribute (const_वृक्षः)
{
  पटिनिवत्त 0;
}

/* In C, no expression is dependent.  */

तार्किक
instantiation_dependent_expression_p (वृक्षः)
{
  पटिनिवत्त मिच्छा;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
पूर्णाङ्क
c_type_dwarf_attribute (const_वृक्षः type, पूर्णाङ्क attr)
{
  सचे (type == NULL_वृक्षः)
    पटिनिवत्त -1;

  विकल्प (attr)
    {
    पक्ष DW_AT_export_symbols:
      सचे (RECORD_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_वृक्षः)
	पटिनिवत्त 1;
      भङ्ग;

    स्वभाव:
      भङ्ग;
    }

  पटिनिवत्त -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

वृक्षः
c_enum_underlying_base_type (const_वृक्षः type)
{
  वृक्षः underlying_type = ENUM_UNDERLYING_TYPE (type);

  सचे (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_mode (TYPE_MODE (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  पटिनिवत्त underlying_type;
}
