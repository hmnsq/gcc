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

ಸ್ಥಿರ ತಾರ್ಕಿಕ c_ವೃಕ್ಷ_printer (pretty_printer *, ಪಠ್ಯ_info *, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *,
			    ಪೂರ್ಣಾಂಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

ರಚನೆ c_feature_info
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ident;
  ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *enable_flag;
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ c_feature_info c_feature_ಕೋಷ್ಟಕ[] =
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
c_ರಿಜಿಸ್ಟರ್_features ()
{
  ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < ARRAY_ಗಾತ್ರ (c_feature_ಕೋಷ್ಟಕ); i++)
    {
      ಸ್ಥಿರಾಂಕ c_feature_info *info = c_feature_ಕೋಷ್ಟಕ + i;
      ಸ್ಥಿರಾಂಕ ತಾರ್ಕಿಕ feat_p = !info->enable_flag || *info->enable_flag;
      c_common_ರಿಜಿಸ್ಟರ್_feature (info->ident, feat_p);
    }
}

ತಾರ್ಕಿಕ
c_missing_noreturn_ok_p (ವೃಕ್ಷ decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  ಆದರೆ (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಹಿಂತಿರುಗಿ flag_hosted
    || TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (decl))) == integer_type_ಗಂಟು;
}

/* Called from check_global_declaration.  */

ತಾರ್ಕಿಕ
c_warn_ಬಳಸದ_global_decl (const_ವೃಕ್ಷ decl)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  ಆದರೆ (DECL_ಒಳ_SYSTEM_ಶೀರ್ಷಿಕೆ (decl))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* Initialization common to C and Objective-C front ends.  */
ತಾರ್ಕಿಕ
c_objc_common_init (ಶೂನ್ಯ)
{
  c_init_decl_processing ();

  ಹಿಂತಿರುಗಿ c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

ಸ್ಥಿರ ವೃಕ್ಷ
get_aka_type (ವೃಕ್ಷ type)
{
  ಆದರೆ (type == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ type;

  ವೃಕ್ಷ ಫಲಿತಾಂಶ;
  ಆದರೆ (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      ವೃಕ್ಷ orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (orig_type);
      ವೃಕ್ಷ orig_id = TYPE_IDENTIFIER (orig_type);
      ಆದರೆ ((ಸಂಕೇತ_2 == ದಾಖಲೆ_TYPE || ಸಂಕೇತ_2 == UNION_TYPE || ಸಂಕೇತ_2 == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	ಹಿಂತಿರುಗಿ type;

      ಆದರೆ (!user_facing_original_type_p (type))
	ಹಿಂತಿರುಗಿ type;

      ಫಲಿತಾಂಶ = get_aka_type (orig_type);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE)
    ಹಿಂತಿರುಗಿ type;
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ವೃಕ್ಷ canonical = TYPE_CANONICAL (type);
      ಆದರೆ (canonical && ವೃಕ್ಷ_ಸಂಕೇತ (type) != ವೃಕ್ಷ_ಸಂಕೇತ (canonical))
	ಹಿಂತಿರುಗಿ canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      ಆಯ್ಕೆ (ವೃಕ್ಷ_ಸಂಕೇತ (type))
	{
	ಸ್ಥಿತಿ ಸೂಚಕ_TYPE:
	ಸ್ಥಿತಿ REFERENCE_TYPE:
	  {
	    ವೃಕ್ಷ ಗುರಿ_type = get_aka_type (ವೃಕ್ಷ_TYPE (type));

	    ಆದರೆ (ಗುರಿ_type == ವೃಕ್ಷ_TYPE (type))
	      ಹಿಂತಿರುಗಿ type;

	    ಆದರೆ (canonical && ಗುರಿ_type == ವೃಕ್ಷ_TYPE (canonical))
	      ಹಿಂತಿರುಗಿ canonical;

	    ಫಲಿತಾಂಶ = (ವೃಕ್ಷ_ಸಂಕೇತ (type) == ಸೂಚಕ_TYPE
		      ? build_ಸೂಚಕ_type (ಗುರಿ_type)
		      : build_reference_type (ಗುರಿ_type));
	    ನಿಲ್ಲಿಸು;
	  }

	ಸ್ಥಿತಿ ARRAY_TYPE:
	  {
	    ವೃಕ್ಷ element_type = get_aka_type (ವೃಕ್ಷ_TYPE (type));
	    ವೃಕ್ಷ ಸೂಚ್ಯಂಕ_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_ವೃಕ್ಷ);

	    ಆದರೆ (element_type == ವೃಕ್ಷ_TYPE (type)
		&& ಸೂಚ್ಯಂಕ_type == TYPE_DOMAIN (type))
	      ಹಿಂತಿರುಗಿ type;

	    ಆದರೆ (canonical
		&& element_type == ವೃಕ್ಷ_TYPE (canonical)
		&& ಸೂಚ್ಯಂಕ_type == TYPE_DOMAIN (canonical))
	      ಹಿಂತಿರುಗಿ canonical;

	    ಫಲಿತಾಂಶ = build_array_type (element_type, ಸೂಚ್ಯಂಕ_type,
				       TYPE_TYPELESS_STORAGE (type));
	    ನಿಲ್ಲಿಸು;
	  }

	ಸ್ಥಿತಿ FUNCTION_TYPE:
	  {
	    ವೃಕ್ಷ return_type = get_aka_type (ವೃಕ್ಷ_TYPE (type));

	    ವೃಕ್ಷ ವಾದಗಳು = TYPE_ARG_TYPES (type);
	    ಆದರೆ (ವಾದಗಳು == error_mark_ಗಂಟು)
	      ಹಿಂತಿರುಗಿ type;

	    auto_vec<ವೃಕ್ಷ, 32> arg_types;
	    ತಾರ್ಕಿಕ type_ok_p = ನಿಜ;
	    ಆಗ (ವಾದಗಳು && ವಾದಗಳು != void_list_ಗಂಟು)
	      {
		ವೃಕ್ಷ arg_type = get_aka_type (ವೃಕ್ಷ_ಮೌಲ್ಯ (ವಾದಗಳು));
		arg_types.ಸುರಕ್ಷಿತ_ತಳ್ಳು (arg_type);
		type_ok_p &= (arg_type == ವೃಕ್ಷ_ಮೌಲ್ಯ (ವಾದಗಳು));
		ವಾದಗಳು = ವೃಕ್ಷ_CHAIN (ವಾದಗಳು);
	      }

	    ಆದರೆ (type_ok_p && return_type == ವೃಕ್ಷ_TYPE (type))
	      ಹಿಂತಿರುಗಿ type;

	    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ i;
	    ವೃಕ್ಷ arg_type;
	    FOR_EACH_VEC_ELT_ಹಿಮ್ಮುಖ (arg_types, i, arg_type)
	      ವಾದಗಳು = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, arg_type, ವಾದಗಳು);
	    ಫಲಿತಾಂಶ = build_function_type (return_type, ವಾದಗಳು);
	    ನಿಲ್ಲಿಸು;
	  }

	ಪೂರ್ವನಿಯೋಜಿತ:
	  ಹಿಂತಿರುಗಿ canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (type) || ವೃಕ್ಷ_ಸಂಕೇತ (type) == ENUMERAL_TYPE)
    ಹಿಂತಿರುಗಿ build_qualified_type (ಫಲಿತಾಂಶ, TYPE_QUALS (type));
  ಹಿಂತಿರುಗಿ build_type_attribute_qual_variant (ಫಲಿತಾಂಶ, TYPE_ಗುಣಲಕ್ಷಣಗಳು (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

ಸ್ಥಿರ ಶೂನ್ಯ
print_type (c_pretty_printer *cpp, ವೃಕ್ಷ t, ತಾರ್ಕಿಕ *quoted,
	    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *highlight_color = ಶೂನ್ಯಸೂಚಕ)
{
  ಆದರೆ (t == error_mark_ಗಂಟು)
    {
      pp_string (cpp, _("{erroneous}"));
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (!pp_show_highlight_colors (cpp))
    highlight_color = ಶೂನ್ಯಸೂಚಕ;

  gcc_assert (TYPE_P (t));
  ರಚನೆ obstack *ob = pp_ಬಫರ್ (cpp)->m_obstack;
  ಅಕ್ಷರ *p = (ಅಕ್ಷರ *) obstack_ತಳ (ob);
  /* Remember the end of the initial dump.  */
  ಪೂರ್ಣಾಂಕ len = obstack_object_ಗಾತ್ರ (ob);

  ವೃಕ್ಷ name = TYPE_NAME (t);
  ಆದರೆ (name && ವೃಕ್ಷ_ಸಂಕೇತ (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  ಇಲ್ಲದಿದ್ದರೆ
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  ವೃಕ್ಷ aka_type = get_aka_type (t);
  ಆದರೆ (aka_type != t)
    {
      ಸ್ಥಿರಾಂಕ ತಾರ್ಕಿಕ show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      ರಚನೆ obstack *ob2 = pp_ಬಫರ್ (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *aka = (ಅಕ್ಷರ *) obstack_ತಳ (ob2);
      ಪೂರ್ಣಾಂಕ aka_len = obstack_object_ಗಾತ್ರ (ob2);
      ಪೂರ್ಣಾಂಕ type1_len = obstack_object_ಗಾತ್ರ (ob) - len;

      /* If they are identical, bail out.  */
      ಆದರೆ (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	ಹಿಂತಿರುಗಿ;

      /* They're not, print the stripped version now.  */
      ಆದರೆ (*quoted)
	pp_ಕೊನೆ_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_ಎಡ_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      ಆದರೆ (*quoted)
	pp_begin_quote (cpp, show_color);
      ಆದರೆ (highlight_color)
	pp_string (cpp, colorize_ಆರಂಭ (show_color, highlight_color));
      cpp->type_id (aka_type);
      ಆದರೆ (*quoted)
	pp_ಕೊನೆ_quote (cpp, show_color);
      pp_ಬಲ_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = ಸುಳ್ಳು;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

ಶೂನ್ಯ
pp_markup::element_quoted_type::print_type (pp_markup::context &ctxt)
{
  ಸ್ವಯಂಚಾಲಿತ pp = ctxt.m_pp.clone ();
  c_pretty_printer *cpp = (c_pretty_printer *)pp.get ();
  cpp->ಗಣ_padding (pp_none);
  ::print_type (cpp, m_type, &ctxt.m_quoted, m_highlight_color);
  pp_string (&ctxt.m_pp, pp_formatted_ಪಠ್ಯ (cpp));
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
c_ವೃಕ್ಷ_printer (pretty_printer *pp, ಪಠ್ಯ_info *ಪಠ್ಯ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *spec,
		ಪೂರ್ಣಾಂಕ precision, ತಾರ್ಕಿಕ wide, ತಾರ್ಕಿಕ ಗಣ_locus, ತಾರ್ಕಿಕ hash,
		ತಾರ್ಕಿಕ *quoted, pp_token_list &)
{
  ವೃಕ್ಷ t = NULL_ವೃಕ್ಷ;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->ಗಣ_padding (pp_none);

  ಆದರೆ (precision != 0 || wide)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಆದರೆ (*spec != 'v')
    {
      t = va_arg (*ಪಠ್ಯ->m_ವಾದಗಳು_ptr, ವೃಕ್ಷ);
      ಆದರೆ (ಗಣ_locus)
	ಪಠ್ಯ->ಗಣ_location (0, DECL_ಮೂಲ_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  ಆಯ್ಕೆ (*spec)
    {
    ಸ್ಥಿತಿ 'D':
      ಆದರೆ (VAR_P (t) && DECL_HAS_DEBUG_ಅಭಿವ್ಯಕ್ತಿ_P (t))
	{
	  t = DECL_DEBUG_ಅಭಿವ್ಯಕ್ತಿ (t);
	  ಆದರೆ (!DECL_P (t))
	    {
	      cpp->ಅಭಿವ್ಯಕ್ತಿ_2 (t);
	      ಹಿಂತಿರುಗಿ ನಿಜ;
	    }
	}
      /* FALLTHRU */

    ಸ್ಥಿತಿ 'F':
      ಆದರೆ (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == FUNCTION_DECL)
	    {
	      pp_c_function_ಗುರಿ_ಆವೃತ್ತಿ (cpp, t);
	      pp_c_function_ಗುರಿ_clones (cpp, t);
	    }
	  ಹಿಂತಿರುಗಿ ನಿಜ;
	}
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ 'T':
      print_type (cpp, t, quoted);
      ಹಿಂತಿರುಗಿ ನಿಜ;

    ಸ್ಥಿತಿ 'E':
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (t) == IDENTIFIER_ಗಂಟು)
	pp_identifier (cpp, IDENTIFIER_ಸೂಚಕ (t));
      ಇಲ್ಲದಿದ್ದರೆ
	cpp->ಅಭಿವ್ಯಕ್ತಿ_2 (t);
      ಹಿಂತಿರುಗಿ ನಿಜ;

    ಸ್ಥಿತಿ 'V':
      pp_c_type_qualifier_list (cpp, t);
      ಹಿಂತಿರುಗಿ ನಿಜ;

    ಸ್ಥಿತಿ 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*ಪಠ್ಯ->m_ವಾದಗಳು_ptr, ಪೂರ್ಣಾಂಕ), hash);
      ಹಿಂತಿರುಗಿ ನಿಜ;

    ಪೂರ್ವನಿಯೋಜಿತ:
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

  pp_string (cpp, _("({anonymous})"));
  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_ಪಠ್ಯ
range_label_for_type_mismatch::get_ಪಠ್ಯ (ಚಿಹ್ನೆರಹಿತ /*range_idx*/) ಸ್ಥಿರಾಂಕ
{
  ಆದರೆ (m_labelled_type == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ label_ಪಠ್ಯ::borrow (ಖಾಲಿ);

  c_pretty_printer cpp;
  ತಾರ್ಕಿಕ quoted = ಸುಳ್ಳು;
  print_type (&cpp, m_labelled_type, &quoted);
  ಹಿಂತಿರುಗಿ label_ಪಠ್ಯ::take (xstrdup (pp_formatted_ಪಠ್ಯ (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
ತಾರ್ಕಿಕ
has_c_linkage (const_ವೃಕ್ಷ decl ATTRIBUTE_ಬಳಸದ)
{
  ಹಿಂತಿರುಗಿ ನಿಜ;
}

ಶೂನ್ಯ
c_initialize_diagnostics (diagnostics::context *context)
{
  context->ಗಣ_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_ಗಣ_defaults (context);
  context->ಗಣ_format_decoder (&c_ವೃಕ್ಷ_printer);
}

ಪೂರ್ಣಾಂಕ
c_types_compatible_p (ವೃಕ್ಷ x, ವೃಕ್ಷ y)
{
  ಹಿಂತಿರುಗಿ comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

ತಾರ್ಕಿಕ
c_var_mod_p (ವೃಕ್ಷ x, ವೃಕ್ಷ fn ATTRIBUTE_ಬಳಸದ)
{
  ಹಿಂತಿರುಗಿ c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_ಗಣ_type
c_get_alias_ಗಣ (ವೃಕ್ಷ t)
{
  ಹಿಂತಿರುಗಿ c_common_get_alias_ಗಣ (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

ಪೂರ್ಣಾಂಕ
maybe_adjust_arg_pos_for_attribute (const_ವೃಕ್ಷ)
{
  ಹಿಂತಿರುಗಿ 0;
}

/* In C, no expression is dependent.  */

ತಾರ್ಕಿಕ
instantiation_dependent_ಅಭಿವ್ಯಕ್ತಿ_p (ವೃಕ್ಷ)
{
  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
ಪೂರ್ಣಾಂಕ
c_type_dwarf_attribute (const_ವೃಕ್ಷ type, ಪೂರ್ಣಾಂಕ attr)
{
  ಆದರೆ (type == NULL_ವೃಕ್ಷ)
    ಹಿಂತಿರುಗಿ -1;

  ಆಯ್ಕೆ (attr)
    {
    ಸ್ಥಿತಿ DW_AT_export_symbols:
      ಆದರೆ (ದಾಖಲೆ_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_ವೃಕ್ಷ)
	ಹಿಂತಿರುಗಿ 1;
      ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }

  ಹಿಂತಿರುಗಿ -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

ವೃಕ್ಷ
c_enum_underlying_ತಳ_type (const_ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ underlying_type = ENUM_UNDERLYING_TYPE (type);

  ಆದರೆ (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_ಬಹುಲಕ (TYPE_ಬಹುಲಕ (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  ಹಿಂತಿರುಗಿ underlying_type;
}
