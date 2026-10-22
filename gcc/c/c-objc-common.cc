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

#అన్తర్భావ "config.h"
#అన్తర్భావ "system.h"
#అన్తర్భావ "coretypes.h"
#అన్తర్భావ "c-tree.h"
#అన్తర్భావ "intl.h"
#అన్తర్భావ "c-family/c-pretty-print.h"
#అన్తర్భావ "tree-core.h"
#అన్తర్భావ "tree-pretty-print.h"
#అన్తర్భావ "tree-pretty-print-markup.h"
#అన్తర్భావ "gimple-pretty-print.h"
#అన్తర్భావ "langhooks.h"
#అన్తర్భావ "c-objc-common.h"
#అన్తర్భావ "c-family/c-type-mismatch.h"
#అన్తర్భావ "stringpool.h"
#అన్తర్భావ "attribs.h"
#అన్తర్భావ "dwarf2.h"

స్థిర తార్కిక c_వృక్షం_printer (pretty_printer *, పాఠ్యం_info *, స్థిరరాశి అక్షరం *,
			    పూర్ణాంకం, తార్కిక, తార్కిక, తార్కిక, తార్కిక *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

నిర్మాణం c_feature_info
{
  స్థిరరాశి అక్షరం *ident;
  స్థిరరాశి పూర్ణాంకం *enable_flag;
};

స్థిర స్థిరరాశి c_feature_info c_feature_పట్టిక[] =
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

శూన్య
c_రిజిస్టరు_features ()
{
  కొరకు (గుర్తులేని i = 0; i < ARRAY_కొలత (c_feature_పట్టిక); i++)
    {
      స్థిరరాశి c_feature_info *info = c_feature_పట్టిక + i;
      స్థిరరాశి తార్కిక feat_p = !info->enable_flag || *info->enable_flag;
      c_common_రిజిస్టరు_feature (info->ident, feat_p);
    }
}

తార్కిక
c_missing_noreturn_ok_p (వృక్షం decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  ఒకవేళ (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    తిరిగి అబద్ధం;

  తిరిగి flag_hosted
    || TYPE_MAIN_VARIANT (వృక్షం_TYPE (వృక్షం_TYPE (decl))) == integer_type_కణుపు;
}

/* Called from check_global_declaration.  */

తార్కిక
c_warn_వాడని_global_decl (const_వృక్షం decl)
{
  ఒకవేళ (వృక్షం_సంకేతం (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    తిరిగి అబద్ధం;
  ఒకవేళ (DECL_లోపల_SYSTEM_శీర్షిక (decl))
    తిరిగి అబద్ధం;

  తిరిగి నిజం;
}

/* Initialization common to C and Objective-C front ends.  */
తార్కిక
c_objc_common_init (శూన్య)
{
  c_init_decl_processing ();

  తిరిగి c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

స్థిర వృక్షం
get_aka_type (వృక్షం type)
{
  ఒకవేళ (type == error_mark_కణుపు)
    తిరిగి type;

  వృక్షం ఫలితం;
  ఒకవేళ (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      వృక్షం orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (orig_type);
      వృక్షం orig_id = TYPE_IDENTIFIER (orig_type);
      ఒకవేళ ((సంకేతం_2 == రికార్డు_TYPE || సంకేతం_2 == UNION_TYPE || సంకేతం_2 == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	తిరిగి type;

      ఒకవేళ (!user_facing_original_type_p (type))
	తిరిగి type;

      ఫలితం = get_aka_type (orig_type);
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (type) == ENUMERAL_TYPE)
    తిరిగి type;
  లేకపోతే
    {
      వృక్షం canonical = TYPE_CANONICAL (type);
      ఒకవేళ (canonical && వృక్షం_సంకేతం (type) != వృక్షం_సంకేతం (canonical))
	తిరిగి canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      ఎంపిక (వృక్షం_సంకేతం (type))
	{
	స్థితి సూచిక_TYPE:
	స్థితి REFERENCE_TYPE:
	  {
	    వృక్షం లక్ష్యం_type = get_aka_type (వృక్షం_TYPE (type));

	    ఒకవేళ (లక్ష్యం_type == వృక్షం_TYPE (type))
	      తిరిగి type;

	    ఒకవేళ (canonical && లక్ష్యం_type == వృక్షం_TYPE (canonical))
	      తిరిగి canonical;

	    ఫలితం = (వృక్షం_సంకేతం (type) == సూచిక_TYPE
		      ? build_సూచిక_type (లక్ష్యం_type)
		      : build_reference_type (లక్ష్యం_type));
	    ఆపు;
	  }

	స్థితి ARRAY_TYPE:
	  {
	    వృక్షం element_type = get_aka_type (వృక్షం_TYPE (type));
	    వృక్షం సూచీ_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_వృక్షం);

	    ఒకవేళ (element_type == వృక్షం_TYPE (type)
		&& సూచీ_type == TYPE_DOMAIN (type))
	      తిరిగి type;

	    ఒకవేళ (canonical
		&& element_type == వృక్షం_TYPE (canonical)
		&& సూచీ_type == TYPE_DOMAIN (canonical))
	      తిరిగి canonical;

	    ఫలితం = build_array_type (element_type, సూచీ_type,
				       TYPE_TYPELESS_STORAGE (type));
	    ఆపు;
	  }

	స్థితి FUNCTION_TYPE:
	  {
	    వృక్షం return_type = get_aka_type (వృక్షం_TYPE (type));

	    వృక్షం వాదనలు = TYPE_ARG_TYPES (type);
	    ఒకవేళ (వాదనలు == error_mark_కణుపు)
	      తిరిగి type;

	    auto_vec<వృక్షం, 32> arg_types;
	    తార్కిక type_ok_p = నిజం;
	    అయితే (వాదనలు && వాదనలు != void_list_కణుపు)
	      {
		వృక్షం arg_type = get_aka_type (వృక్షం_విలువ (వాదనలు));
		arg_types.సురక్షిత_నెట్టు (arg_type);
		type_ok_p &= (arg_type == వృక్షం_విలువ (వాదనలు));
		వాదనలు = వృక్షం_CHAIN (వాదనలు);
	      }

	    ఒకవేళ (type_ok_p && return_type == వృక్షం_TYPE (type))
	      తిరిగి type;

	    గుర్తులేని పూర్ణాంకం i;
	    వృక్షం arg_type;
	    FOR_EACH_VEC_ELT_తిరగేయి (arg_types, i, arg_type)
	      వాదనలు = వృక్షం_cons (NULL_వృక్షం, arg_type, వాదనలు);
	    ఫలితం = build_function_type (return_type, వాదనలు);
	    ఆపు;
	  }

	అప్రమేయ:
	  తిరిగి canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type) || వృక్షం_సంకేతం (type) == ENUMERAL_TYPE)
    తిరిగి build_qualified_type (ఫలితం, TYPE_QUALS (type));
  తిరిగి build_type_attribute_qual_variant (ఫలితం, TYPE_లక్షణాలు (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

స్థిర శూన్య
print_type (c_pretty_printer *cpp, వృక్షం t, తార్కిక *quoted,
	    స్థిరరాశి అక్షరం *highlight_color = శూన్యసూచిక)
{
  ఒకవేళ (t == error_mark_కణుపు)
    {
      pp_string (cpp, _("{erroneous}"));
      తిరిగి;
    }

  ఒకవేళ (!pp_show_highlight_colors (cpp))
    highlight_color = శూన్యసూచిక;

  gcc_assert (TYPE_P (t));
  నిర్మాణం obstack *ob = pp_బఫరు (cpp)->m_obstack;
  అక్షరం *p = (అక్షరం *) obstack_పునాది (ob);
  /* Remember the end of the initial dump.  */
  పూర్ణాంకం len = obstack_object_కొలత (ob);

  వృక్షం name = TYPE_NAME (t);
  ఒకవేళ (name && వృక్షం_సంకేతం (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  లేకపోతే
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  వృక్షం aka_type = get_aka_type (t);
  ఒకవేళ (aka_type != t)
    {
      స్థిరరాశి తార్కిక show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      నిర్మాణం obstack *ob2 = pp_బఫరు (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      స్థిరరాశి అక్షరం *aka = (అక్షరం *) obstack_పునాది (ob2);
      పూర్ణాంకం aka_len = obstack_object_కొలత (ob2);
      పూర్ణాంకం type1_len = obstack_object_కొలత (ob) - len;

      /* If they are identical, bail out.  */
      ఒకవేళ (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	తిరిగి;

      /* They're not, print the stripped version now.  */
      ఒకవేళ (*quoted)
	pp_చివర_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_ఎడమ_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      ఒకవేళ (*quoted)
	pp_begin_quote (cpp, show_color);
      ఒకవేళ (highlight_color)
	pp_string (cpp, colorize_ప్రారంభం (show_color, highlight_color));
      cpp->type_id (aka_type);
      ఒకవేళ (*quoted)
	pp_చివర_quote (cpp, show_color);
      pp_కుడి_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = అబద్ధం;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

శూన్య
pp_markup::element_quoted_type::print_type (pp_markup::context &ctxt)
{
  స్వయంచాలక pp = ctxt.m_pp.clone ();
  c_pretty_printer *cpp = (c_pretty_printer *)pp.get ();
  cpp->సమితి_padding (pp_none);
  ::print_type (cpp, m_type, &ctxt.m_quoted, m_highlight_color);
  pp_string (&ctxt.m_pp, pp_formatted_పాఠ్యం (cpp));
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
స్థిర తార్కిక
c_వృక్షం_printer (pretty_printer *pp, పాఠ్యం_info *పాఠ్యం, స్థిరరాశి అక్షరం *spec,
		పూర్ణాంకం precision, తార్కిక wide, తార్కిక సమితి_locus, తార్కిక hash,
		తార్కిక *quoted, pp_token_list &)
{
  వృక్షం t = NULL_వృక్షం;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->సమితి_padding (pp_none);

  ఒకవేళ (precision != 0 || wide)
    తిరిగి అబద్ధం;

  ఒకవేళ (*spec != 'v')
    {
      t = va_arg (*పాఠ్యం->m_వాదనలు_ptr, వృక్షం);
      ఒకవేళ (సమితి_locus)
	పాఠ్యం->సమితి_location (0, DECL_ఆధారం_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  ఎంపిక (*spec)
    {
    స్థితి 'D':
      ఒకవేళ (VAR_P (t) && DECL_HAS_DEBUG_సమాసం_P (t))
	{
	  t = DECL_DEBUG_సమాసం (t);
	  ఒకవేళ (!DECL_P (t))
	    {
	      cpp->వ్యక్తీకరణ (t);
	      తిరిగి నిజం;
	    }
	}
      /* FALLTHRU */

    స్థితి 'F':
      ఒకవేళ (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  ఒకవేళ (వృక్షం_సంకేతం (t) == FUNCTION_DECL)
	    {
	      pp_c_function_లక్ష్యం_సంస్కరణ (cpp, t);
	      pp_c_function_లక్ష్యం_clones (cpp, t);
	    }
	  తిరిగి నిజం;
	}
      ఆపు;

    స్థితి 'T':
      print_type (cpp, t, quoted);
      తిరిగి నిజం;

    స్థితి 'E':
      ఒకవేళ (వృక్షం_సంకేతం (t) == IDENTIFIER_కణుపు)
	pp_identifier (cpp, IDENTIFIER_సూచిక (t));
      లేకపోతే
	cpp->వ్యక్తీకరణ (t);
      తిరిగి నిజం;

    స్థితి 'V':
      pp_c_type_qualifier_list (cpp, t);
      తిరిగి నిజం;

    స్థితి 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*పాఠ్యం->m_వాదనలు_ptr, పూర్ణాంకం), hash);
      తిరిగి నిజం;

    అప్రమేయ:
      తిరిగి అబద్ధం;
    }

  pp_string (cpp, _("({anonymous})"));
  తిరిగి నిజం;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_పాఠ్యం
range_label_for_type_mismatch::get_పాఠ్యం (గుర్తులేని /*range_idx*/) స్థిరరాశి
{
  ఒకవేళ (m_labelled_type == NULL_వృక్షం)
    తిరిగి label_పాఠ్యం::borrow (ఖాళీ);

  c_pretty_printer cpp;
  తార్కిక quoted = అబద్ధం;
  print_type (&cpp, m_labelled_type, &quoted);
  తిరిగి label_పాఠ్యం::take (xstrdup (pp_formatted_పాఠ్యం (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
తార్కిక
has_c_linkage (const_వృక్షం decl ATTRIBUTE_వాడని)
{
  తిరిగి నిజం;
}

శూన్య
c_initialize_diagnostics (diagnostics::context *context)
{
  context->సమితి_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_సమితి_defaults (context);
  context->సమితి_format_decoder (&c_వృక్షం_printer);
}

పూర్ణాంకం
c_types_compatible_p (వృక్షం x, వృక్షం y)
{
  తిరిగి comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

తార్కిక
c_var_mod_p (వృక్షం x, వృక్షం fn ATTRIBUTE_వాడని)
{
  తిరిగి c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_సమితి_type
c_get_alias_సమితి (వృక్షం t)
{
  తిరిగి c_common_get_alias_సమితి (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

పూర్ణాంకం
maybe_adjust_arg_pos_for_attribute (const_వృక్షం)
{
  తిరిగి 0;
}

/* In C, no expression is dependent.  */

తార్కిక
instantiation_dependent_వ్యక్తీకరణ_p (వృక్షం)
{
  తిరిగి అబద్ధం;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
పూర్ణాంకం
c_type_dwarf_attribute (const_వృక్షం type, పూర్ణాంకం attr)
{
  ఒకవేళ (type == NULL_వృక్షం)
    తిరిగి -1;

  ఎంపిక (attr)
    {
    స్థితి DW_AT_export_symbols:
      ఒకవేళ (రికార్డు_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_వృక్షం)
	తిరిగి 1;
      ఆపు;

    అప్రమేయ:
      ఆపు;
    }

  తిరిగి -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

వృక్షం
c_enum_underlying_పునాది_type (const_వృక్షం type)
{
  వృక్షం underlying_type = ENUM_UNDERLYING_TYPE (type);

  ఒకవేళ (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_బహుళకం (TYPE_బహుళకం (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  తిరిగి underlying_type;
}
