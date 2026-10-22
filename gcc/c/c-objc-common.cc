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

#شامل "config.h"
#شامل "system.h"
#شامل "coretypes.h"
#شامل "c-tree.h"
#شامل "intl.h"
#شامل "c-family/c-pretty-print.h"
#شامل "tree-core.h"
#شامل "tree-pretty-print.h"
#شامل "tree-pretty-print-markup.h"
#شامل "gimple-pretty-print.h"
#شامل "langhooks.h"
#شامل "c-objc-common.h"
#شامل "c-family/c-type-mismatch.h"
#شامل "stringpool.h"
#شامل "attribs.h"
#شامل "dwarf2.h"

ساکن منطقی c_درخت_printer (pretty_printer *, متن_info *, ثابت حرف *,
			    صحیح, منطقی, منطقی, منطقی, منطقی *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

ساخت c_feature_info
{
  ثابت حرف *ident;
  ثابت صحیح *enable_flag;
};

ساکن ثابت c_feature_info c_feature_جدول[] =
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

خالی
c_رجسٹر_features ()
{
  برائے (غیرعلامتی i = 0; i < ARRAY_سائز (c_feature_جدول); i++)
    {
      ثابت c_feature_info *info = c_feature_جدول + i;
      ثابت منطقی feat_p = !info->enable_flag || *info->enable_flag;
      c_common_رجسٹر_feature (info->ident, feat_p);
    }
}

منطقی
c_missing_noreturn_ok_p (درخت decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  اگر (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    واپس جھوٹ;

  واپس flag_hosted
    || TYPE_MAIN_VARIANT (درخت_TYPE (درخت_TYPE (decl))) == integer_type_گرہ;
}

/* Called from check_global_declaration.  */

منطقی
c_warn_غیر_مستعمل_global_decl (const_درخت decl)
{
  اگر (درخت_رمز (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    واپس جھوٹ;
  اگر (DECL_اندر_SYSTEM_سرخی (decl))
    واپس جھوٹ;

  واپس سچ;
}

/* Initialization common to C and Objective-C front ends.  */
منطقی
c_objc_common_init (خالی)
{
  c_init_decl_processing ();

  واپس c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

ساکن درخت
get_aka_type (درخت type)
{
  اگر (type == error_mark_گرہ)
    واپس type;

  درخت نتیجہ;
  اگر (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      درخت orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      درخت_رمز_2 رمز = درخت_رمز (orig_type);
      درخت orig_id = TYPE_IDENTIFIER (orig_type);
      اگر ((رمز == ریکارڈ_TYPE || رمز == UNION_TYPE || رمز == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	واپس type;

      اگر (!user_facing_original_type_p (type))
	واپس type;

      نتیجہ = get_aka_type (orig_type);
    }
  ورنہ اگر (درخت_رمز (type) == ENUMERAL_TYPE)
    واپس type;
  ورنہ
    {
      درخت canonical = TYPE_CANONICAL (type);
      اگر (canonical && درخت_رمز (type) != درخت_رمز (canonical))
	واپس canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      انتخاب (درخت_رمز (type))
	{
	حالت اشارہ_گر_TYPE:
	حالت REFERENCE_TYPE:
	  {
	    درخت ہدف_type = get_aka_type (درخت_TYPE (type));

	    اگر (ہدف_type == درخت_TYPE (type))
	      واپس type;

	    اگر (canonical && ہدف_type == درخت_TYPE (canonical))
	      واپس canonical;

	    نتیجہ = (درخت_رمز (type) == اشارہ_گر_TYPE
		      ? build_اشارہ_گر_type (ہدف_type)
		      : build_reference_type (ہدف_type));
	    توڑو;
	  }

	حالت ARRAY_TYPE:
	  {
	    درخت element_type = get_aka_type (درخت_TYPE (type));
	    درخت اشاریہ_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_درخت);

	    اگر (element_type == درخت_TYPE (type)
		&& اشاریہ_type == TYPE_DOMAIN (type))
	      واپس type;

	    اگر (canonical
		&& element_type == درخت_TYPE (canonical)
		&& اشاریہ_type == TYPE_DOMAIN (canonical))
	      واپس canonical;

	    نتیجہ = build_array_type (element_type, اشاریہ_type,
				       TYPE_TYPELESS_STORAGE (type));
	    توڑو;
	  }

	حالت FUNCTION_TYPE:
	  {
	    درخت return_type = get_aka_type (درخت_TYPE (type));

	    درخت دلائل = TYPE_ARG_TYPES (type);
	    اگر (دلائل == error_mark_گرہ)
	      واپس type;

	    auto_vec<درخت, 32> arg_types;
	    منطقی type_ok_p = سچ;
	    جب (دلائل && دلائل != void_list_گرہ)
	      {
		درخت arg_type = get_aka_type (درخت_قدر (دلائل));
		arg_types.محفوظ_ڈالو (arg_type);
		type_ok_p &= (arg_type == درخت_قدر (دلائل));
		دلائل = درخت_CHAIN (دلائل);
	      }

	    اگر (type_ok_p && return_type == درخت_TYPE (type))
	      واپس type;

	    غیرعلامتی صحیح i;
	    درخت arg_type;
	    FOR_EACH_VEC_ELT_الٹ (arg_types, i, arg_type)
	      دلائل = درخت_cons (NULL_درخت, arg_type, دلائل);
	    نتیجہ = build_function_type (return_type, دلائل);
	    توڑو;
	  }

	طےشدہ:
	  واپس canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  اگر (ریکارڈ_OR_UNION_TYPE_P (type) || درخت_رمز (type) == ENUMERAL_TYPE)
    واپس build_qualified_type (نتیجہ, TYPE_QUALS (type));
  واپس build_type_attribute_qual_variant (نتیجہ, TYPE_اوصاف (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

ساکن خالی
print_type (c_pretty_printer *cpp, درخت t, منطقی *quoted,
	    ثابت حرف *highlight_color = خالی_اشاریہ)
{
  اگر (t == error_mark_گرہ)
    {
      pp_string (cpp, _("{erroneous}"));
      واپس;
    }

  اگر (!pp_show_highlight_colors (cpp))
    highlight_color = خالی_اشاریہ;

  gcc_assert (TYPE_P (t));
  ساخت obstack *ob = pp_بفر (cpp)->m_obstack;
  حرف *p = (حرف *) obstack_بنیاد (ob);
  /* Remember the end of the initial dump.  */
  صحیح len = obstack_object_سائز (ob);

  درخت name = TYPE_NAME (t);
  اگر (name && درخت_رمز (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  ورنہ
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  درخت aka_type = get_aka_type (t);
  اگر (aka_type != t)
    {
      ثابت منطقی show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      ساخت obstack *ob2 = pp_بفر (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      ثابت حرف *aka = (حرف *) obstack_بنیاد (ob2);
      صحیح aka_len = obstack_object_سائز (ob2);
      صحیح type1_len = obstack_object_سائز (ob) - len;

      /* If they are identical, bail out.  */
      اگر (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	واپس;

      /* They're not, print the stripped version now.  */
      اگر (*quoted)
	pp_انتہا_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_بایاں_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      اگر (*quoted)
	pp_begin_quote (cpp, show_color);
      اگر (highlight_color)
	pp_string (cpp, colorize_آغاز (show_color, highlight_color));
      cpp->type_id (aka_type);
      اگر (*quoted)
	pp_انتہا_quote (cpp, show_color);
      pp_دایاں_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = جھوٹ;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

خالی
pp_markup::element_quoted_type::print_type (pp_markup::context &ctxt)
{
  خودکار pp = ctxt.m_pp.clone ();
  c_pretty_printer *cpp = (c_pretty_printer *)pp.get ();
  cpp->سیٹ_padding (pp_none);
  ::print_type (cpp, m_type, &ctxt.m_quoted, m_highlight_color);
  pp_string (&ctxt.m_pp, pp_formatted_متن (cpp));
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
ساکن منطقی
c_درخت_printer (pretty_printer *pp, متن_info *متن, ثابت حرف *spec,
		صحیح precision, منطقی wide, منطقی سیٹ_locus, منطقی hash,
		منطقی *quoted, pp_token_list &)
{
  درخت t = NULL_درخت;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->سیٹ_padding (pp_none);

  اگر (precision != 0 || wide)
    واپس جھوٹ;

  اگر (*spec != 'v')
    {
      t = va_arg (*متن->m_دلائل_ptr, درخت);
      اگر (سیٹ_locus)
	متن->سیٹ_location (0, DECL_ماخذ_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  انتخاب (*spec)
    {
    حالت 'D':
      اگر (VAR_P (t) && DECL_HAS_DEBUG_اظہاریہ_P (t))
	{
	  t = DECL_DEBUG_اظہاریہ (t);
	  اگر (!DECL_P (t))
	    {
	      cpp->عبارت (t);
	      واپس سچ;
	    }
	}
      /* FALLTHRU */

    حالت 'F':
      اگر (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  اگر (درخت_رمز (t) == FUNCTION_DECL)
	    {
	      pp_c_function_ہدف_نسخہ (cpp, t);
	      pp_c_function_ہدف_clones (cpp, t);
	    }
	  واپس سچ;
	}
      توڑو;

    حالت 'T':
      print_type (cpp, t, quoted);
      واپس سچ;

    حالت 'E':
      اگر (درخت_رمز (t) == IDENTIFIER_گرہ)
	pp_identifier (cpp, IDENTIFIER_اشارہ_گر (t));
      ورنہ
	cpp->عبارت (t);
      واپس سچ;

    حالت 'V':
      pp_c_type_qualifier_list (cpp, t);
      واپس سچ;

    حالت 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*متن->m_دلائل_ptr, صحیح), hash);
      واپس سچ;

    طےشدہ:
      واپس جھوٹ;
    }

  pp_string (cpp, _("({anonymous})"));
  واپس سچ;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_متن
range_label_for_type_mismatch::get_متن (غیرعلامتی /*range_idx*/) ثابت
{
  اگر (m_labelled_type == NULL_درخت)
    واپس label_متن::borrow (تہی);

  c_pretty_printer cpp;
  منطقی quoted = جھوٹ;
  print_type (&cpp, m_labelled_type, &quoted);
  واپس label_متن::take (xstrdup (pp_formatted_متن (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
منطقی
has_c_linkage (const_درخت decl ATTRIBUTE_غیر_مستعمل)
{
  واپس سچ;
}

خالی
c_initialize_diagnostics (diagnostics::context *context)
{
  context->سیٹ_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_سیٹ_defaults (context);
  context->سیٹ_format_decoder (&c_درخت_printer);
}

صحیح
c_types_compatible_p (درخت x, درخت y)
{
  واپس comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

منطقی
c_var_mod_p (درخت x, درخت fn ATTRIBUTE_غیر_مستعمل)
{
  واپس c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_سیٹ_type
c_get_alias_سیٹ (درخت t)
{
  واپس c_common_get_alias_سیٹ (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

صحیح
maybe_adjust_arg_pos_for_attribute (const_درخت)
{
  واپس 0;
}

/* In C, no expression is dependent.  */

منطقی
instantiation_dependent_عبارت_p (درخت)
{
  واپس جھوٹ;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
صحیح
c_type_dwarf_attribute (const_درخت type, صحیح attr)
{
  اگر (type == NULL_درخت)
    واپس -1;

  انتخاب (attr)
    {
    حالت DW_AT_export_symbols:
      اگر (ریکارڈ_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_درخت)
	واپس 1;
      توڑو;

    طےشدہ:
      توڑو;
    }

  واپس -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

درخت
c_enum_underlying_بنیاد_type (const_درخت type)
{
  درخت underlying_type = ENUM_UNDERLYING_TYPE (type);

  اگر (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_منوال (TYPE_منوال (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  واپس underlying_type;
}
