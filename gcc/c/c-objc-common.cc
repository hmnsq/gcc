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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "c-tree.h"
#அந்தர்பாவ "intl.h"
#அந்தர்பாவ "c-family/c-pretty-print.h"
#அந்தர்பாவ "tree-core.h"
#அந்தர்பாவ "tree-pretty-print.h"
#அந்தர்பாவ "tree-pretty-print-markup.h"
#அந்தர்பாவ "gimple-pretty-print.h"
#அந்தர்பாவ "langhooks.h"
#அந்தர்பாவ "c-objc-common.h"
#அந்தர்பாவ "c-family/c-type-mismatch.h"
#அந்தர்பாவ "stringpool.h"
#அந்தர்பாவ "attribs.h"
#அந்தர்பாவ "dwarf2.h"

நிலையான தருக்க c_மரம்_printer (pretty_printer *, text_info *, மாறிலி எழுத்து *,
			    முழு, தருக்க, தருக்க, தருக்க, தருக்க *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

கட்டமைப்பு c_feature_info
{
  மாறிலி எழுத்து *ident;
  மாறிலி முழு *enable_flag;
};

நிலையான மாறிலி c_feature_info c_feature_table[] =
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

வெறுமை
c_register_features ()
{
  க்கு (unsigned i = 0; i < ARRAY_SIZE (c_feature_table); i++)
    {
      மாறிலி c_feature_info *info = c_feature_table + i;
      மாறிலி தருக்க feat_p = !info->enable_flag || *info->enable_flag;
      c_common_register_feature (info->ident, feat_p);
    }
}

தருக்க
c_missing_noreturn_ok_p (மரம் decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  எனில் (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    திரும்பு பொய்;

  திரும்பு flag_hosted
    || TYPE_MAIN_VARIANT (மரம்_TYPE (மரம்_TYPE (decl))) == integer_type_முனை;
}

/* Called from check_global_declaration.  */

தருக்க
c_warn_unused_global_decl (const_மரம் decl)
{
  எனில் (மரம்_CODE (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    திரும்பு பொய்;
  எனில் (DECL_IN_SYSTEM_HEADER (decl))
    திரும்பு பொய்;

  திரும்பு உண்மை;
}

/* Initialization common to C and Objective-C front ends.  */
தருக்க
c_objc_common_init (வெறுமை)
{
  c_init_decl_processing ();

  திரும்பு c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

நிலையான மரம்
get_aka_type (மரம் type)
{
  எனில் (type == error_mark_முனை)
    திரும்பு type;

  மரம் result;
  எனில் (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      மரம் orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      மரம்_code code = மரம்_CODE (orig_type);
      மரம் orig_id = TYPE_IDENTIFIER (orig_type);
      எனில் ((code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	திரும்பு type;

      எனில் (!user_facing_original_type_p (type))
	திரும்பு type;

      result = get_aka_type (orig_type);
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == ENUMERAL_TYPE)
    திரும்பு type;
  இல்லையெனில்
    {
      மரம் canonical = TYPE_CANONICAL (type);
      எனில் (canonical && மரம்_CODE (type) != மரம்_CODE (canonical))
	திரும்பு canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      தேர்வு (மரம்_CODE (type))
	{
	நிலை POINTER_TYPE:
	நிலை REFERENCE_TYPE:
	  {
	    மரம் target_type = get_aka_type (மரம்_TYPE (type));

	    எனில் (target_type == மரம்_TYPE (type))
	      திரும்பு type;

	    எனில் (canonical && target_type == மரம்_TYPE (canonical))
	      திரும்பு canonical;

	    result = (மரம்_CODE (type) == POINTER_TYPE
		      ? build_pointer_type (target_type)
		      : build_reference_type (target_type));
	    நிறுத்து;
	  }

	நிலை ARRAY_TYPE:
	  {
	    மரம் element_type = get_aka_type (மரம்_TYPE (type));
	    மரம் index_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_மரம்);

	    எனில் (element_type == மரம்_TYPE (type)
		&& index_type == TYPE_DOMAIN (type))
	      திரும்பு type;

	    எனில் (canonical
		&& element_type == மரம்_TYPE (canonical)
		&& index_type == TYPE_DOMAIN (canonical))
	      திரும்பு canonical;

	    result = build_array_type (element_type, index_type,
				       TYPE_TYPELESS_STORAGE (type));
	    நிறுத்து;
	  }

	நிலை FUNCTION_TYPE:
	  {
	    மரம் return_type = get_aka_type (மரம்_TYPE (type));

	    மரம் args = TYPE_ARG_TYPES (type);
	    எனில் (args == error_mark_முனை)
	      திரும்பு type;

	    auto_vec<மரம், 32> arg_types;
	    தருக்க type_ok_p = உண்மை;
	    போது (args && args != void_list_முனை)
	      {
		மரம் arg_type = get_aka_type (மரம்_மதிப்பு (args));
		arg_types.safe_தள்ளு (arg_type);
		type_ok_p &= (arg_type == மரம்_மதிப்பு (args));
		args = மரம்_CHAIN (args);
	      }

	    எனில் (type_ok_p && return_type == மரம்_TYPE (type))
	      திரும்பு type;

	    unsigned முழு i;
	    மரம் arg_type;
	    FOR_EACH_VEC_ELT_REVERSE (arg_types, i, arg_type)
	      args = மரம்_cons (NULL_மரம், arg_type, args);
	    result = build_function_type (return_type, args);
	    நிறுத்து;
	  }

	இயல்பு:
	  திரும்பு canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  எனில் (RECORD_OR_UNION_TYPE_P (type) || மரம்_CODE (type) == ENUMERAL_TYPE)
    திரும்பு build_qualified_type (result, TYPE_QUALS (type));
  திரும்பு build_type_attribute_qual_variant (result, TYPE_ATTRIBUTES (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

நிலையான வெறுமை
print_type (c_pretty_printer *cpp, மரம் t, தருக்க *quoted,
	    மாறிலி எழுத்து *highlight_color = nullptr)
{
  எனில் (t == error_mark_முனை)
    {
      pp_string (cpp, _("{erroneous}"));
      திரும்பு;
    }

  எனில் (!pp_show_highlight_colors (cpp))
    highlight_color = nullptr;

  gcc_assert (TYPE_P (t));
  கட்டமைப்பு obstack *ob = pp_buffer (cpp)->m_obstack;
  எழுத்து *p = (எழுத்து *) obstack_base (ob);
  /* Remember the end of the initial dump.  */
  முழு len = obstack_object_size (ob);

  மரம் name = TYPE_NAME (t);
  எனில் (name && மரம்_CODE (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  இல்லையெனில்
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  மரம் aka_type = get_aka_type (t);
  எனில் (aka_type != t)
    {
      மாறிலி தருக்க show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      கட்டமைப்பு obstack *ob2 = pp_buffer (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      மாறிலி எழுத்து *aka = (எழுத்து *) obstack_base (ob2);
      முழு aka_len = obstack_object_size (ob2);
      முழு type1_len = obstack_object_size (ob) - len;

      /* If they are identical, bail out.  */
      எனில் (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	திரும்பு;

      /* They're not, print the stripped version now.  */
      எனில் (*quoted)
	pp_end_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_இடது_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      எனில் (*quoted)
	pp_begin_quote (cpp, show_color);
      எனில் (highlight_color)
	pp_string (cpp, colorize_start (show_color, highlight_color));
      cpp->type_id (aka_type);
      எனில் (*quoted)
	pp_end_quote (cpp, show_color);
      pp_வலது_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = பொய்;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

வெறுமை
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
நிலையான தருக்க
c_மரம்_printer (pretty_printer *pp, text_info *text, மாறிலி எழுத்து *spec,
		முழு precision, தருக்க wide, தருக்க set_locus, தருக்க hash,
		தருக்க *quoted, pp_token_list &)
{
  மரம் t = NULL_மரம்;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->set_padding (pp_none);

  எனில் (precision != 0 || wide)
    திரும்பு பொய்;

  எனில் (*spec != 'v')
    {
      t = va_arg (*text->m_args_ptr, மரம்);
      எனில் (set_locus)
	text->set_location (0, DECL_SOURCE_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  தேர்வு (*spec)
    {
    நிலை 'D':
      எனில் (VAR_P (t) && DECL_HAS_DEBUG_கோவை_P (t))
	{
	  t = DECL_DEBUG_கோவை (t);
	  எனில் (!DECL_P (t))
	    {
	      cpp->expression (t);
	      திரும்பு உண்மை;
	    }
	}
      /* FALLTHRU */

    நிலை 'F':
      எனில் (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  எனில் (மரம்_CODE (t) == FUNCTION_DECL)
	    {
	      pp_c_function_target_version (cpp, t);
	      pp_c_function_target_clones (cpp, t);
	    }
	  திரும்பு உண்மை;
	}
      நிறுத்து;

    நிலை 'T':
      print_type (cpp, t, quoted);
      திரும்பு உண்மை;

    நிலை 'E':
      எனில் (மரம்_CODE (t) == IDENTIFIER_முனை)
	pp_identifier (cpp, IDENTIFIER_POINTER (t));
      இல்லையெனில்
	cpp->expression (t);
      திரும்பு உண்மை;

    நிலை 'V':
      pp_c_type_qualifier_list (cpp, t);
      திரும்பு உண்மை;

    நிலை 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*text->m_args_ptr, முழு), hash);
      திரும்பு உண்மை;

    இயல்பு:
      திரும்பு பொய்;
    }

  pp_string (cpp, _("({anonymous})"));
  திரும்பு உண்மை;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_text
range_label_for_type_mismatch::get_text (unsigned /*range_idx*/) மாறிலி
{
  எனில் (m_labelled_type == NULL_மரம்)
    திரும்பு label_text::borrow (வெற்று);

  c_pretty_printer cpp;
  தருக்க quoted = பொய்;
  print_type (&cpp, m_labelled_type, &quoted);
  திரும்பு label_text::take (xstrdup (pp_formatted_text (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
தருக்க
has_c_linkage (const_மரம் decl ATTRIBUTE_UNUSED)
{
  திரும்பு உண்மை;
}

வெறுமை
c_initialize_diagnostics (diagnostics::context *context)
{
  context->set_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_set_defaults (context);
  context->set_format_decoder (&c_மரம்_printer);
}

முழு
c_types_compatible_p (மரம் x, மரம் y)
{
  திரும்பு comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

தருக்க
c_var_mod_p (மரம் x, மரம் fn ATTRIBUTE_UNUSED)
{
  திரும்பு c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_set_type
c_get_alias_set (மரம் t)
{
  திரும்பு c_common_get_alias_set (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

முழு
maybe_adjust_arg_pos_for_attribute (const_மரம்)
{
  திரும்பு 0;
}

/* In C, no expression is dependent.  */

தருக்க
instantiation_dependent_expression_p (மரம்)
{
  திரும்பு பொய்;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
முழு
c_type_dwarf_attribute (const_மரம் type, முழு attr)
{
  எனில் (type == NULL_மரம்)
    திரும்பு -1;

  தேர்வு (attr)
    {
    நிலை DW_AT_export_symbols:
      எனில் (RECORD_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_மரம்)
	திரும்பு 1;
      நிறுத்து;

    இயல்பு:
      நிறுத்து;
    }

  திரும்பு -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

மரம்
c_enum_underlying_base_type (const_மரம் type)
{
  மரம் underlying_type = ENUM_UNDERLYING_TYPE (type);

  எனில் (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_mode (TYPE_MODE (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  திரும்பு underlying_type;
}
