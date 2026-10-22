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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-pretty-print.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-core.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-pretty-print.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-pretty-print-markup.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple-pretty-print.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "langhooks.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-objc-common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-type-mismatch.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stringpool.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attribs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "dwarf2.h"

ਸਥਿਰ ਤਾਰਕਿਕ c_ਰੁੱਖ_printer (pretty_printer *, ਪਾਠ_info *, ਅਚਲ ਅੱਖਰ *,
			    ਪੂਰਨ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

ਬਣਤਰ c_feature_info
{
  ਅਚਲ ਅੱਖਰ *ident;
  ਅਚਲ ਪੂਰਨ *enable_flag;
};

ਸਥਿਰ ਅਚਲ c_feature_info c_feature_ਸਾਰਣੀ[] =
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

ਖਾਲੀ
c_ਰਜਿਸਟਰ_features ()
{
  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < ARRAY_ਮਾਪ (c_feature_ਸਾਰਣੀ); i++)
    {
      ਅਚਲ c_feature_info *info = c_feature_ਸਾਰਣੀ + i;
      ਅਚਲ ਤਾਰਕਿਕ feat_p = !info->enable_flag || *info->enable_flag;
      c_common_ਰਜਿਸਟਰ_feature (info->ident, feat_p);
    }
}

ਤਾਰਕਿਕ
c_missing_noreturn_ok_p (ਰੁੱਖ decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  ਜੇ (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    ਵਾਪਸ ਝੂਠ;

  ਵਾਪਸ flag_hosted
    || TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (decl))) == integer_type_ਗੰਢ;
}

/* Called from check_global_declaration.  */

ਤਾਰਕਿਕ
c_warn_ਅਣਵਰਤਿਆ_global_decl (const_ਰੁੱਖ decl)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (DECL_ਵਿੱਚ_SYSTEM_ਸਿਰਲੇਖ (decl))
    ਵਾਪਸ ਝੂਠ;

  ਵਾਪਸ ਸੱਚ;
}

/* Initialization common to C and Objective-C front ends.  */
ਤਾਰਕਿਕ
c_objc_common_init (ਖਾਲੀ)
{
  c_init_decl_processing ();

  ਵਾਪਸ c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

ਸਥਿਰ ਰੁੱਖ
get_aka_type (ਰੁੱਖ type)
{
  ਜੇ (type == error_mark_ਗੰਢ)
    ਵਾਪਸ type;

  ਰੁੱਖ ਨਤੀਜਾ;
  ਜੇ (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      ਰੁੱਖ orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (orig_type);
      ਰੁੱਖ orig_id = TYPE_IDENTIFIER (orig_type);
      ਜੇ ((ਕੋਡ == ਰਿਕਾਰਡ_TYPE || ਕੋਡ == UNION_TYPE || ਕੋਡ == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	ਵਾਪਸ type;

      ਜੇ (!user_facing_original_type_p (type))
	ਵਾਪਸ type;

      ਨਤੀਜਾ = get_aka_type (orig_type);
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE)
    ਵਾਪਸ type;
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ canonical = TYPE_CANONICAL (type);
      ਜੇ (canonical && ਰੁੱਖ_ਕੋਡ (type) != ਰੁੱਖ_ਕੋਡ (canonical))
	ਵਾਪਸ canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      ਚੋਣ (ਰੁੱਖ_ਕੋਡ (type))
	{
	ਹਾਲਤ ਸੂਚਕ_TYPE:
	ਹਾਲਤ REFERENCE_TYPE:
	  {
	    ਰੁੱਖ ਨਿਸ਼ਾਨਾ_type = get_aka_type (ਰੁੱਖ_TYPE (type));

	    ਜੇ (ਨਿਸ਼ਾਨਾ_type == ਰੁੱਖ_TYPE (type))
	      ਵਾਪਸ type;

	    ਜੇ (canonical && ਨਿਸ਼ਾਨਾ_type == ਰੁੱਖ_TYPE (canonical))
	      ਵਾਪਸ canonical;

	    ਨਤੀਜਾ = (ਰੁੱਖ_ਕੋਡ (type) == ਸੂਚਕ_TYPE
		      ? build_ਸੂਚਕ_type (ਨਿਸ਼ਾਨਾ_type)
		      : build_reference_type (ਨਿਸ਼ਾਨਾ_type));
	    ਰੋਕੋ;
	  }

	ਹਾਲਤ ARRAY_TYPE:
	  {
	    ਰੁੱਖ element_type = get_aka_type (ਰੁੱਖ_TYPE (type));
	    ਰੁੱਖ ਸੂਚਕਾਂਕ_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_ਰੁੱਖ);

	    ਜੇ (element_type == ਰੁੱਖ_TYPE (type)
		&& ਸੂਚਕਾਂਕ_type == TYPE_DOMAIN (type))
	      ਵਾਪਸ type;

	    ਜੇ (canonical
		&& element_type == ਰੁੱਖ_TYPE (canonical)
		&& ਸੂਚਕਾਂਕ_type == TYPE_DOMAIN (canonical))
	      ਵਾਪਸ canonical;

	    ਨਤੀਜਾ = build_array_type (element_type, ਸੂਚਕਾਂਕ_type,
				       TYPE_TYPELESS_STORAGE (type));
	    ਰੋਕੋ;
	  }

	ਹਾਲਤ FUNCTION_TYPE:
	  {
	    ਰੁੱਖ return_type = get_aka_type (ਰੁੱਖ_TYPE (type));

	    ਰੁੱਖ ਦਲੀਲਾਂ = TYPE_ARG_TYPES (type);
	    ਜੇ (ਦਲੀਲਾਂ == error_mark_ਗੰਢ)
	      ਵਾਪਸ type;

	    auto_vec<ਰੁੱਖ, 32> arg_types;
	    ਤਾਰਕਿਕ type_ok_p = ਸੱਚ;
	    ਜਦੋਂ (ਦਲੀਲਾਂ && ਦਲੀਲਾਂ != void_list_ਗੰਢ)
	      {
		ਰੁੱਖ arg_type = get_aka_type (ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ));
		arg_types.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (arg_type);
		type_ok_p &= (arg_type == ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ));
		ਦਲੀਲਾਂ = ਰੁੱਖ_CHAIN (ਦਲੀਲਾਂ);
	      }

	    ਜੇ (type_ok_p && return_type == ਰੁੱਖ_TYPE (type))
	      ਵਾਪਸ type;

	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
	    ਰੁੱਖ arg_type;
	    FOR_EACH_VEC_ELT_ਉਲਟ (arg_types, i, arg_type)
	      ਦਲੀਲਾਂ = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, arg_type, ਦਲੀਲਾਂ);
	    ਨਤੀਜਾ = build_function_type (return_type, ਦਲੀਲਾਂ);
	    ਰੋਕੋ;
	  }

	ਮੂਲ:
	  ਵਾਪਸ canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type) || ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE)
    ਵਾਪਸ build_qualified_type (ਨਤੀਜਾ, TYPE_QUALS (type));
  ਵਾਪਸ build_type_attribute_qual_variant (ਨਤੀਜਾ, TYPE_ਗੁਣ (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

ਸਥਿਰ ਖਾਲੀ
print_type (c_pretty_printer *cpp, ਰੁੱਖ t, ਤਾਰਕਿਕ *quoted,
	    ਅਚਲ ਅੱਖਰ *highlight_color = ਖਾਲੀ_ਸੂਚਕ)
{
  ਜੇ (t == error_mark_ਗੰਢ)
    {
      pp_string (cpp, _("{erroneous}"));
      ਵਾਪਸ;
    }

  ਜੇ (!pp_show_highlight_colors (cpp))
    highlight_color = ਖਾਲੀ_ਸੂਚਕ;

  gcc_assert (TYPE_P (t));
  ਬਣਤਰ obstack *ob = pp_ਬਫਰ (cpp)->m_obstack;
  ਅੱਖਰ *p = (ਅੱਖਰ *) obstack_ਅਧਾਰ (ob);
  /* Remember the end of the initial dump.  */
  ਪੂਰਨ len = obstack_object_ਮਾਪ (ob);

  ਰੁੱਖ name = TYPE_NAME (t);
  ਜੇ (name && ਰੁੱਖ_ਕੋਡ (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  ਨਹੀਂਤਾਂ
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  ਰੁੱਖ aka_type = get_aka_type (t);
  ਜੇ (aka_type != t)
    {
      ਅਚਲ ਤਾਰਕਿਕ show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      ਬਣਤਰ obstack *ob2 = pp_ਬਫਰ (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      ਅਚਲ ਅੱਖਰ *aka = (ਅੱਖਰ *) obstack_ਅਧਾਰ (ob2);
      ਪੂਰਨ aka_len = obstack_object_ਮਾਪ (ob2);
      ਪੂਰਨ type1_len = obstack_object_ਮਾਪ (ob) - len;

      /* If they are identical, bail out.  */
      ਜੇ (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	ਵਾਪਸ;

      /* They're not, print the stripped version now.  */
      ਜੇ (*quoted)
	pp_ਸਿਰਾ_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_ਖੱਬਾ_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      ਜੇ (*quoted)
	pp_begin_quote (cpp, show_color);
      ਜੇ (highlight_color)
	pp_string (cpp, colorize_ਸ਼ੁਰੂ (show_color, highlight_color));
      cpp->type_id (aka_type);
      ਜੇ (*quoted)
	pp_ਸਿਰਾ_quote (cpp, show_color);
      pp_ਸੱਜਾ_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = ਝੂਠ;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

ਖਾਲੀ
pp_markup::element_quoted_type::print_type (pp_markup::context &ctxt)
{
  ਸਵੈਚਾਲਿਤ pp = ctxt.m_pp.clone ();
  c_pretty_printer *cpp = (c_pretty_printer *)pp.get ();
  cpp->ਸੈੱਟ_padding (pp_none);
  ::print_type (cpp, m_type, &ctxt.m_quoted, m_highlight_color);
  pp_string (&ctxt.m_pp, pp_formatted_ਪਾਠ (cpp));
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
ਸਥਿਰ ਤਾਰਕਿਕ
c_ਰੁੱਖ_printer (pretty_printer *pp, ਪਾਠ_info *ਪਾਠ, ਅਚਲ ਅੱਖਰ *spec,
		ਪੂਰਨ precision, ਤਾਰਕਿਕ wide, ਤਾਰਕਿਕ ਸੈੱਟ_locus, ਤਾਰਕਿਕ hash,
		ਤਾਰਕਿਕ *quoted, pp_token_list &)
{
  ਰੁੱਖ t = NULL_ਰੁੱਖ;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->ਸੈੱਟ_padding (pp_none);

  ਜੇ (precision != 0 || wide)
    ਵਾਪਸ ਝੂਠ;

  ਜੇ (*spec != 'v')
    {
      t = va_arg (*ਪਾਠ->m_ਦਲੀਲਾਂ_ptr, ਰੁੱਖ);
      ਜੇ (ਸੈੱਟ_locus)
	ਪਾਠ->ਸੈੱਟ_location (0, DECL_ਸਰੋਤ_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  ਚੋਣ (*spec)
    {
    ਹਾਲਤ 'D':
      ਜੇ (VAR_P (t) && DECL_HAS_DEBUG_ਵਿਅੰਜਕ_P (t))
	{
	  t = DECL_DEBUG_ਵਿਅੰਜਕ (t);
	  ਜੇ (!DECL_P (t))
	    {
	      cpp->ਵਿਅੰਜਕ_2 (t);
	      ਵਾਪਸ ਸੱਚ;
	    }
	}
      /* FALLTHRU */

    ਹਾਲਤ 'F':
      ਜੇ (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == FUNCTION_DECL)
	    {
	      pp_c_function_ਨਿਸ਼ਾਨਾ_ਸੰਸਕਰਣ (cpp, t);
	      pp_c_function_ਨਿਸ਼ਾਨਾ_clones (cpp, t);
	    }
	  ਵਾਪਸ ਸੱਚ;
	}
      ਰੋਕੋ;

    ਹਾਲਤ 'T':
      print_type (cpp, t, quoted);
      ਵਾਪਸ ਸੱਚ;

    ਹਾਲਤ 'E':
      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == IDENTIFIER_ਗੰਢ)
	pp_identifier (cpp, IDENTIFIER_ਸੂਚਕ (t));
      ਨਹੀਂਤਾਂ
	cpp->ਵਿਅੰਜਕ_2 (t);
      ਵਾਪਸ ਸੱਚ;

    ਹਾਲਤ 'V':
      pp_c_type_qualifier_list (cpp, t);
      ਵਾਪਸ ਸੱਚ;

    ਹਾਲਤ 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*ਪਾਠ->m_ਦਲੀਲਾਂ_ptr, ਪੂਰਨ), hash);
      ਵਾਪਸ ਸੱਚ;

    ਮੂਲ:
      ਵਾਪਸ ਝੂਠ;
    }

  pp_string (cpp, _("({anonymous})"));
  ਵਾਪਸ ਸੱਚ;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_ਪਾਠ
range_label_for_type_mismatch::get_ਪਾਠ (ਬਿਨਾਨਿਸ਼ਾਨੀ /*range_idx*/) ਅਚਲ
{
  ਜੇ (m_labelled_type == NULL_ਰੁੱਖ)
    ਵਾਪਸ label_ਪਾਠ::borrow (ਨਿਰਾ);

  c_pretty_printer cpp;
  ਤਾਰਕਿਕ quoted = ਝੂਠ;
  print_type (&cpp, m_labelled_type, &quoted);
  ਵਾਪਸ label_ਪਾਠ::take (xstrdup (pp_formatted_ਪਾਠ (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
ਤਾਰਕਿਕ
has_c_linkage (const_ਰੁੱਖ decl ATTRIBUTE_ਅਣਵਰਤਿਆ)
{
  ਵਾਪਸ ਸੱਚ;
}

ਖਾਲੀ
c_initialize_diagnostics (diagnostics::context *context)
{
  context->ਸੈੱਟ_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_ਸੈੱਟ_defaults (context);
  context->ਸੈੱਟ_format_decoder (&c_ਰੁੱਖ_printer);
}

ਪੂਰਨ
c_types_compatible_p (ਰੁੱਖ x, ਰੁੱਖ y)
{
  ਵਾਪਸ comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

ਤਾਰਕਿਕ
c_var_mod_p (ਰੁੱਖ x, ਰੁੱਖ fn ATTRIBUTE_ਅਣਵਰਤਿਆ)
{
  ਵਾਪਸ c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_ਸੈੱਟ_type
c_get_alias_ਸੈੱਟ (ਰੁੱਖ t)
{
  ਵਾਪਸ c_common_get_alias_ਸੈੱਟ (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

ਪੂਰਨ
maybe_adjust_arg_pos_for_attribute (const_ਰੁੱਖ)
{
  ਵਾਪਸ 0;
}

/* In C, no expression is dependent.  */

ਤਾਰਕਿਕ
instantiation_dependent_ਵਿਅੰਜਕ_p (ਰੁੱਖ)
{
  ਵਾਪਸ ਝੂਠ;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
ਪੂਰਨ
c_type_dwarf_attribute (const_ਰੁੱਖ type, ਪੂਰਨ attr)
{
  ਜੇ (type == NULL_ਰੁੱਖ)
    ਵਾਪਸ -1;

  ਚੋਣ (attr)
    {
    ਹਾਲਤ DW_AT_export_symbols:
      ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_ਰੁੱਖ)
	ਵਾਪਸ 1;
      ਰੋਕੋ;

    ਮੂਲ:
      ਰੋਕੋ;
    }

  ਵਾਪਸ -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

ਰੁੱਖ
c_enum_underlying_ਅਧਾਰ_type (const_ਰੁੱਖ type)
{
  ਰੁੱਖ underlying_type = ENUM_UNDERLYING_TYPE (type);

  ਜੇ (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_ਬਹੁਲਕ (TYPE_ਬਹੁਲਕ (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  ਵਾਪਸ underlying_type;
}
