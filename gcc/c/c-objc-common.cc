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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "system.h"
#અન્તર્ભાવ "coretypes.h"
#અન્તર્ભાવ "c-tree.h"
#અન્તર્ભાવ "intl.h"
#અન્તર્ભાવ "c-family/c-pretty-print.h"
#અન્તર્ભાવ "tree-core.h"
#અન્તર્ભાવ "tree-pretty-print.h"
#અન્તર્ભાવ "tree-pretty-print-markup.h"
#અન્તર્ભાવ "gimple-pretty-print.h"
#અન્તર્ભાવ "langhooks.h"
#અન્તર્ભાવ "c-objc-common.h"
#અન્તર્ભાવ "c-family/c-type-mismatch.h"
#અન્તર્ભાવ "stringpool.h"
#અન્તર્ભાવ "attribs.h"
#અન્તર્ભાવ "dwarf2.h"

સ્થિર તાર્કિક c_વૃક્ષ_printer (pretty_printer *, text_info *, અચલ અક્ષર *,
			    પૂર્ણાંક, તાર્કિક, તાર્કિક, તાર્કિક, તાર્કિક *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

સંરચના c_feature_info
{
  અચલ અક્ષર *ident;
  અચલ પૂર્ણાંક *enable_flag;
};

સ્થિર અચલ c_feature_info c_feature_table[] =
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

શૂન્ય
c_register_features ()
{
  માટે (unsigned i = 0; i < ARRAY_SIZE (c_feature_table); i++)
    {
      અચલ c_feature_info *info = c_feature_table + i;
      અચલ તાર્કિક feat_p = !info->enable_flag || *info->enable_flag;
      c_common_register_feature (info->ident, feat_p);
    }
}

તાર્કિક
c_missing_noreturn_ok_p (વૃક્ષ decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  જો (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    પાછા ખોટું;

  પાછા flag_hosted
    || TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (વૃક્ષ_TYPE (decl))) == integer_type_ગાંઠ;
}

/* Called from check_global_declaration.  */

તાર્કિક
c_warn_unused_global_decl (const_વૃક્ષ decl)
{
  જો (વૃક્ષ_CODE (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    પાછા ખોટું;
  જો (DECL_IN_SYSTEM_HEADER (decl))
    પાછા ખોટું;

  પાછા સાચું;
}

/* Initialization common to C and Objective-C front ends.  */
તાર્કિક
c_objc_common_init (શૂન્ય)
{
  c_init_decl_processing ();

  પાછા c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

સ્થિર વૃક્ષ
get_aka_type (વૃક્ષ type)
{
  જો (type == error_mark_ગાંઠ)
    પાછા type;

  વૃક્ષ result;
  જો (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      વૃક્ષ orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      વૃક્ષ_code code = વૃક્ષ_CODE (orig_type);
      વૃક્ષ orig_id = TYPE_IDENTIFIER (orig_type);
      જો ((code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	પાછા type;

      જો (!user_facing_original_type_p (type))
	પાછા type;

      result = get_aka_type (orig_type);
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == ENUMERAL_TYPE)
    પાછા type;
  નહીંતર
    {
      વૃક્ષ canonical = TYPE_CANONICAL (type);
      જો (canonical && વૃક્ષ_CODE (type) != વૃક્ષ_CODE (canonical))
	પાછા canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      પસંદગી (વૃક્ષ_CODE (type))
	{
	સ્થિતિ POINTER_TYPE:
	સ્થિતિ REFERENCE_TYPE:
	  {
	    વૃક્ષ target_type = get_aka_type (વૃક્ષ_TYPE (type));

	    જો (target_type == વૃક્ષ_TYPE (type))
	      પાછા type;

	    જો (canonical && target_type == વૃક્ષ_TYPE (canonical))
	      પાછા canonical;

	    result = (વૃક્ષ_CODE (type) == POINTER_TYPE
		      ? build_pointer_type (target_type)
		      : build_reference_type (target_type));
	    તોડો;
	  }

	સ્થિતિ ARRAY_TYPE:
	  {
	    વૃક્ષ element_type = get_aka_type (વૃક્ષ_TYPE (type));
	    વૃક્ષ index_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_વૃક્ષ);

	    જો (element_type == વૃક્ષ_TYPE (type)
		&& index_type == TYPE_DOMAIN (type))
	      પાછા type;

	    જો (canonical
		&& element_type == વૃક્ષ_TYPE (canonical)
		&& index_type == TYPE_DOMAIN (canonical))
	      પાછા canonical;

	    result = build_array_type (element_type, index_type,
				       TYPE_TYPELESS_STORAGE (type));
	    તોડો;
	  }

	સ્થિતિ FUNCTION_TYPE:
	  {
	    વૃક્ષ return_type = get_aka_type (વૃક્ષ_TYPE (type));

	    વૃક્ષ args = TYPE_ARG_TYPES (type);
	    જો (args == error_mark_ગાંઠ)
	      પાછા type;

	    auto_vec<વૃક્ષ, 32> arg_types;
	    તાર્કિક type_ok_p = સાચું;
	    જ્યારે (args && args != void_list_ગાંઠ)
	      {
		વૃક્ષ arg_type = get_aka_type (વૃક્ષ_કિંમત (args));
		arg_types.safe_ધકેલો (arg_type);
		type_ok_p &= (arg_type == વૃક્ષ_કિંમત (args));
		args = વૃક્ષ_CHAIN (args);
	      }

	    જો (type_ok_p && return_type == વૃક્ષ_TYPE (type))
	      પાછા type;

	    unsigned પૂર્ણાંક i;
	    વૃક્ષ arg_type;
	    FOR_EACH_VEC_ELT_REVERSE (arg_types, i, arg_type)
	      args = વૃક્ષ_cons (NULL_વૃક્ષ, arg_type, args);
	    result = build_function_type (return_type, args);
	    તોડો;
	  }

	મૂળભૂત:
	  પાછા canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  જો (RECORD_OR_UNION_TYPE_P (type) || વૃક્ષ_CODE (type) == ENUMERAL_TYPE)
    પાછા build_qualified_type (result, TYPE_QUALS (type));
  પાછા build_type_attribute_qual_variant (result, TYPE_ATTRIBUTES (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

સ્થિર શૂન્ય
print_type (c_pretty_printer *cpp, વૃક્ષ t, તાર્કિક *quoted,
	    અચલ અક્ષર *highlight_color = nullptr)
{
  જો (t == error_mark_ગાંઠ)
    {
      pp_string (cpp, _("{erroneous}"));
      પાછા;
    }

  જો (!pp_show_highlight_colors (cpp))
    highlight_color = nullptr;

  gcc_assert (TYPE_P (t));
  સંરચના obstack *ob = pp_buffer (cpp)->m_obstack;
  અક્ષર *p = (અક્ષર *) obstack_base (ob);
  /* Remember the end of the initial dump.  */
  પૂર્ણાંક len = obstack_object_size (ob);

  વૃક્ષ name = TYPE_NAME (t);
  જો (name && વૃક્ષ_CODE (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  નહીંતર
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  વૃક્ષ aka_type = get_aka_type (t);
  જો (aka_type != t)
    {
      અચલ તાર્કિક show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      સંરચના obstack *ob2 = pp_buffer (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      અચલ અક્ષર *aka = (અક્ષર *) obstack_base (ob2);
      પૂર્ણાંક aka_len = obstack_object_size (ob2);
      પૂર્ણાંક type1_len = obstack_object_size (ob) - len;

      /* If they are identical, bail out.  */
      જો (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	પાછા;

      /* They're not, print the stripped version now.  */
      જો (*quoted)
	pp_end_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_ડાબું_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      જો (*quoted)
	pp_begin_quote (cpp, show_color);
      જો (highlight_color)
	pp_string (cpp, colorize_start (show_color, highlight_color));
      cpp->type_id (aka_type);
      જો (*quoted)
	pp_end_quote (cpp, show_color);
      pp_જમણું_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = ખોટું;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

શૂન્ય
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
સ્થિર તાર્કિક
c_વૃક્ષ_printer (pretty_printer *pp, text_info *text, અચલ અક્ષર *spec,
		પૂર્ણાંક precision, તાર્કિક wide, તાર્કિક set_locus, તાર્કિક hash,
		તાર્કિક *quoted, pp_token_list &)
{
  વૃક્ષ t = NULL_વૃક્ષ;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->set_padding (pp_none);

  જો (precision != 0 || wide)
    પાછા ખોટું;

  જો (*spec != 'v')
    {
      t = va_arg (*text->m_args_ptr, વૃક્ષ);
      જો (set_locus)
	text->set_location (0, DECL_SOURCE_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  પસંદગી (*spec)
    {
    સ્થિતિ 'D':
      જો (VAR_P (t) && DECL_HAS_DEBUG_પદાવલિ_P (t))
	{
	  t = DECL_DEBUG_પદાવલિ (t);
	  જો (!DECL_P (t))
	    {
	      cpp->expression (t);
	      પાછા સાચું;
	    }
	}
      /* FALLTHRU */

    સ્થિતિ 'F':
      જો (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  જો (વૃક્ષ_CODE (t) == FUNCTION_DECL)
	    {
	      pp_c_function_target_version (cpp, t);
	      pp_c_function_target_clones (cpp, t);
	    }
	  પાછા સાચું;
	}
      તોડો;

    સ્થિતિ 'T':
      print_type (cpp, t, quoted);
      પાછા સાચું;

    સ્થિતિ 'E':
      જો (વૃક્ષ_CODE (t) == IDENTIFIER_ગાંઠ)
	pp_identifier (cpp, IDENTIFIER_POINTER (t));
      નહીંતર
	cpp->expression (t);
      પાછા સાચું;

    સ્થિતિ 'V':
      pp_c_type_qualifier_list (cpp, t);
      પાછા સાચું;

    સ્થિતિ 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*text->m_args_ptr, પૂર્ણાંક), hash);
      પાછા સાચું;

    મૂળભૂત:
      પાછા ખોટું;
    }

  pp_string (cpp, _("({anonymous})"));
  પાછા સાચું;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_text
range_label_for_type_mismatch::get_text (unsigned /*range_idx*/) અચલ
{
  જો (m_labelled_type == NULL_વૃક્ષ)
    પાછા label_text::borrow (ખાલી);

  c_pretty_printer cpp;
  તાર્કિક quoted = ખોટું;
  print_type (&cpp, m_labelled_type, &quoted);
  પાછા label_text::take (xstrdup (pp_formatted_text (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
તાર્કિક
has_c_linkage (const_વૃક્ષ decl ATTRIBUTE_UNUSED)
{
  પાછા સાચું;
}

શૂન્ય
c_initialize_diagnostics (diagnostics::context *context)
{
  context->set_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_set_defaults (context);
  context->set_format_decoder (&c_વૃક્ષ_printer);
}

પૂર્ણાંક
c_types_compatible_p (વૃક્ષ x, વૃક્ષ y)
{
  પાછા comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

તાર્કિક
c_var_mod_p (વૃક્ષ x, વૃક્ષ fn ATTRIBUTE_UNUSED)
{
  પાછા c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_set_type
c_get_alias_set (વૃક્ષ t)
{
  પાછા c_common_get_alias_set (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

પૂર્ણાંક
maybe_adjust_arg_pos_for_attribute (const_વૃક્ષ)
{
  પાછા 0;
}

/* In C, no expression is dependent.  */

તાર્કિક
instantiation_dependent_expression_p (વૃક્ષ)
{
  પાછા ખોટું;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
પૂર્ણાંક
c_type_dwarf_attribute (const_વૃક્ષ type, પૂર્ણાંક attr)
{
  જો (type == NULL_વૃક્ષ)
    પાછા -1;

  પસંદગી (attr)
    {
    સ્થિતિ DW_AT_export_symbols:
      જો (RECORD_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_વૃક્ષ)
	પાછા 1;
      તોડો;

    મૂળભૂત:
      તોડો;
    }

  પાછા -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

વૃક્ષ
c_enum_underlying_base_type (const_વૃક્ષ type)
{
  વૃક્ષ underlying_type = ENUM_UNDERLYING_TYPE (type);

  જો (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_mode (TYPE_MODE (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  પાછા underlying_type;
}
