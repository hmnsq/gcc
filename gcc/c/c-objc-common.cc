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

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "c-tree.h"
#ضمن "intl.h"
#ضمن "c-family/c-pretty-print.h"
#ضمن "tree-core.h"
#ضمن "tree-pretty-print.h"
#ضمن "tree-pretty-print-markup.h"
#ضمن "gimple-pretty-print.h"
#ضمن "langhooks.h"
#ضمن "c-objc-common.h"
#ضمن "c-family/c-type-mismatch.h"
#ضمن "stringpool.h"
#ضمن "attribs.h"
#ضمن "dwarf2.h"

ساكن منطقي c_tree_printer (pretty_printer *, text_info *, ثابت حرف *,
			    صحيح, منطقي, منطقي, منطقي, منطقي *, pp_token_list &);

/* Info for C language features which can be queried through
   __has_{feature,extension}.  */

بنية c_feature_info
{
  ثابت حرف *ident;
  ثابت صحيح *enable_flag;
};

ساكن ثابت c_feature_info c_feature_table[] =
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

فراغ
c_register_features ()
{
  لكل (unsigned i = 0; i < ARRAY_SIZE (c_feature_table); i++)
    {
      ثابت c_feature_info *info = c_feature_table + i;
      ثابت منطقي feat_p = !info->enable_flag || *info->enable_flag;
      c_common_register_feature (info->ident, feat_p);
    }
}

منطقي
c_missing_noreturn_ok_p (tree decl)
{
  /* A missing noreturn is ok for the `main' function.  */
  ܐܢ (!MAIN_NAME_P (DECL_ASSEMBLER_NAME (decl)))
    ܦܢܐ ܕܓܠܐ;

  ܦܢܐ flag_hosted
    || TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (decl))) == integer_type_node;
}

/* Called from check_global_declaration.  */

منطقي
c_warn_unused_global_decl (const_tree decl)
{
  ܐܢ (TREE_CODE (decl) == FUNCTION_DECL && DECL_DECLARED_INLINE_P (decl))
    ܦܢܐ ܕܓܠܐ;
  ܐܢ (DECL_IN_SYSTEM_HEADER (decl))
    ܦܢܐ ܕܓܠܐ;

  ܦܢܐ ܫܪܪܐ;
}

/* Initialization common to C and Objective-C front ends.  */
منطقي
c_objc_common_init (فراغ)
{
  c_init_decl_processing ();

  ܦܢܐ c_common_init ();
}

/* Decide whether it's worth saying that TYPE is also known as some other
   type.  Return the other type if so, otherwise return TYPE.  */

ساكن tree
get_aka_type (tree type)
{
  ܐܢ (type == error_mark_node)
    ܦܢܐ type;

  tree result;
  ܐܢ (typedef_variant_p (type))
    {
      /* Saying that "foo" is also known as "struct foo" or
	 "struct <anonymous>" is unlikely to be useful, since users of
	 structure-like types would already know that they're structures.
	 The same applies to unions and enums; in general, printing the
	 tag is only useful if it has a different name.  */
      tree orig_type = DECL_ORIGINAL_TYPE (TYPE_NAME (type));
      tree_code code = TREE_CODE (orig_type);
      tree orig_id = TYPE_IDENTIFIER (orig_type);
      ܐܢ ((code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	  && (!orig_id || TYPE_IDENTIFIER (type) == orig_id))
	ܦܢܐ type;

      ܐܢ (!user_facing_original_type_p (type))
	ܦܢܐ type;

      result = get_aka_type (orig_type);
    }
  ܐܚܪܢܐ ܐܢ (TREE_CODE (type) == ENUMERAL_TYPE)
    ܦܢܐ type;
  ܐܚܪܢܐ
    {
      tree canonical = TYPE_CANONICAL (type);
      ܐܢ (canonical && TREE_CODE (type) != TREE_CODE (canonical))
	ܦܢܐ canonical;

      /* Recursive calls might choose a middle ground between TYPE
	 (which has no typedefs stripped) and CANONICAL (which has
	 all typedefs stripped).  So try to reuse TYPE or CANONICAL if
	 convenient, but be prepared to create a new type if necessary.  */
      بدل (TREE_CODE (type))
	{
	حالة POINTER_TYPE:
	حالة REFERENCE_TYPE:
	  {
	    tree target_type = get_aka_type (TREE_TYPE (type));

	    ܐܢ (target_type == TREE_TYPE (type))
	      ܦܢܐ type;

	    ܐܢ (canonical && target_type == TREE_TYPE (canonical))
	      ܦܢܐ canonical;

	    result = (TREE_CODE (type) == POINTER_TYPE
		      ? build_pointer_type (target_type)
		      : build_reference_type (target_type));
	    اكسر;
	  }

	حالة ARRAY_TYPE:
	  {
	    tree element_type = get_aka_type (TREE_TYPE (type));
	    tree index_type = (TYPE_DOMAIN (type)
			       ? get_aka_type (TYPE_DOMAIN (type))
			       : NULL_TREE);

	    ܐܢ (element_type == TREE_TYPE (type)
		&& index_type == TYPE_DOMAIN (type))
	      ܦܢܐ type;

	    ܐܢ (canonical
		&& element_type == TREE_TYPE (canonical)
		&& index_type == TYPE_DOMAIN (canonical))
	      ܦܢܐ canonical;

	    result = build_array_type (element_type, index_type,
				       TYPE_TYPELESS_STORAGE (type));
	    اكسر;
	  }

	حالة FUNCTION_TYPE:
	  {
	    tree return_type = get_aka_type (TREE_TYPE (type));

	    tree args = TYPE_ARG_TYPES (type);
	    ܐܢ (args == error_mark_node)
	      ܦܢܐ type;

	    auto_vec<tree, 32> arg_types;
	    منطقي type_ok_p = ܫܪܪܐ;
	    ܟܡܐ (args && args != void_list_node)
	      {
		tree arg_type = get_aka_type (TREE_VALUE (args));
		arg_types.safe_push (arg_type);
		type_ok_p &= (arg_type == TREE_VALUE (args));
		args = TREE_CHAIN (args);
	      }

	    ܐܢ (type_ok_p && return_type == TREE_TYPE (type))
	      ܦܢܐ type;

	    unsigned صحيح i;
	    tree arg_type;
	    FOR_EACH_VEC_ELT_REVERSE (arg_types, i, arg_type)
	      args = tree_cons (NULL_TREE, arg_type, args);
	    result = build_function_type (return_type, args);
	    اكسر;
	  }

	افتراضي:
	  ܦܢܐ canonical ? canonical : type;
	}
    }
  /* For tagged types ignore attributes because they will otherwise
     be ignored later causing a warning inside diagnostics which leads
     to an ICE.  */
  ܐܢ (RECORD_OR_UNION_TYPE_P (type) || TREE_CODE (type) == ENUMERAL_TYPE)
    ܦܢܐ build_qualified_type (result, TYPE_QUALS (type));
  ܦܢܐ build_type_attribute_qual_variant (result, TYPE_ATTRIBUTES (type),
					    TYPE_QUALS (type));
}

/* Print T to CPP.  */

ساكن فراغ
print_type (c_pretty_printer *cpp, tree t, منطقي *quoted,
	    ثابت حرف *highlight_color = nullptr)
{
  ܐܢ (t == error_mark_node)
    {
      pp_string (cpp, _("{erroneous}"));
      ܦܢܐ;
    }

  ܐܢ (!pp_show_highlight_colors (cpp))
    highlight_color = nullptr;

  gcc_assert (TYPE_P (t));
  بنية obstack *ob = pp_buffer (cpp)->m_obstack;
  حرف *p = (حرف *) obstack_base (ob);
  /* Remember the end of the initial dump.  */
  صحيح len = obstack_object_size (ob);

  tree name = TYPE_NAME (t);
  ܐܢ (name && TREE_CODE (name) == TYPE_DECL && DECL_NAME (name))
    pp_identifier (cpp, lang_hooks.decl_printable_name (name, 2));
  ܐܚܪܢܐ
    cpp->type_id (t);

  /* If we're printing a type that involves typedefs, also print the
     stripped version.  But sometimes the stripped version looks
     exactly the same, so we don't want it after all.  To avoid
     printing it in that case, we play ugly obstack games.  */
  tree aka_type = get_aka_type (t);
  ܐܢ (aka_type != t)
    {
      ثابت منطقي show_color = pp_show_color (cpp);
      c_pretty_printer cpp2;
      /* Print the stripped version into a temporary printer.  */
      cpp2.type_id (aka_type);
      بنية obstack *ob2 = pp_buffer (&cpp2)->m_obstack;
      /* Get the stripped version from the temporary printer.  */
      ثابت حرف *aka = (حرف *) obstack_base (ob2);
      صحيح aka_len = obstack_object_size (ob2);
      صحيح type1_len = obstack_object_size (ob) - len;

      /* If they are identical, bail out.  */
      ܐܢ (aka_len == type1_len && memcmp (p + len, aka, aka_len) == 0)
	ܦܢܐ;

      /* They're not, print the stripped version now.  */
      ܐܢ (*quoted)
	pp_end_quote (cpp, show_color);
      pp_c_whitespace (cpp);
      pp_left_brace (cpp);
      pp_c_ws_string (cpp, _("aka"));
      pp_c_whitespace (cpp);
      pp_string (cpp, colorize_stop (show_color));
      ܐܢ (*quoted)
	pp_begin_quote (cpp, show_color);
      ܐܢ (highlight_color)
	pp_string (cpp, colorize_start (show_color, highlight_color));
      cpp->type_id (aka_type);
      ܐܢ (*quoted)
	pp_end_quote (cpp, show_color);
      pp_right_brace (cpp);
      /* No further closing quotes are needed.  */
      *quoted = ܕܓܠܐ;
    }
}

/* Implementation of pp_markup::element_quoted_type::print_type
   for C/ObjC.  */

فراغ
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
ساكن منطقي
c_tree_printer (pretty_printer *pp, text_info *text, ثابت حرف *spec,
		صحيح precision, منطقي wide, منطقي set_locus, منطقي hash,
		منطقي *quoted, pp_token_list &)
{
  tree t = NULL_TREE;
  // FIXME: the next cast should be a dynamic_cast, when it is permitted.
  c_pretty_printer *cpp = (c_pretty_printer *) pp;
  pp->set_padding (pp_none);

  ܐܢ (precision != 0 || wide)
    ܦܢܐ ܕܓܠܐ;

  ܐܢ (*spec != 'v')
    {
      t = va_arg (*text->m_args_ptr, tree);
      ܐܢ (set_locus)
	text->set_location (0, DECL_SOURCE_LOCATION (t),
			    SHOW_RANGE_WITH_CARET);
    }

  بدل (*spec)
    {
    حالة 'D':
      ܐܢ (VAR_P (t) && DECL_HAS_DEBUG_EXPR_P (t))
	{
	  t = DECL_DEBUG_EXPR (t);
	  ܐܢ (!DECL_P (t))
	    {
	      cpp->expression (t);
	      ܦܢܐ ܫܪܪܐ;
	    }
	}
      /* FALLTHRU */

    حالة 'F':
      ܐܢ (DECL_NAME (t))
	{
	  pp_identifier (cpp, lang_hooks.decl_printable_name (t, 2));
	  ܐܢ (TREE_CODE (t) == FUNCTION_DECL)
	    {
	      pp_c_function_target_version (cpp, t);
	      pp_c_function_target_clones (cpp, t);
	    }
	  ܦܢܐ ܫܪܪܐ;
	}
      اكسر;

    حالة 'T':
      print_type (cpp, t, quoted);
      ܦܢܐ ܫܪܪܐ;

    حالة 'E':
      ܐܢ (TREE_CODE (t) == IDENTIFIER_NODE)
	pp_identifier (cpp, IDENTIFIER_POINTER (t));
      ܐܚܪܢܐ
	cpp->expression (t);
      ܦܢܐ ܫܪܪܐ;

    حالة 'V':
      pp_c_type_qualifier_list (cpp, t);
      ܦܢܐ ܫܪܪܐ;

    حالة 'v':
      pp_c_cv_qualifiers (cpp, va_arg (*text->m_args_ptr, صحيح), hash);
      ܦܢܐ ܫܪܪܐ;

    افتراضي:
      ܦܢܐ ܕܓܠܐ;
    }

  pp_string (cpp, _("({anonymous})"));
  ܦܢܐ ܫܪܪܐ;
}

/* C-specific implementation of range_label::get_text () vfunc for
   range_label_for_type_mismatch.  */

label_text
range_label_for_type_mismatch::get_text (unsigned /*range_idx*/) ثابت
{
  ܐܢ (m_labelled_type == NULL_TREE)
    ܦܢܐ label_text::borrow (عدم);

  c_pretty_printer cpp;
  منطقي quoted = ܕܓܠܐ;
  print_type (&cpp, m_labelled_type, &quoted);
  ܦܢܐ label_text::take (xstrdup (pp_formatted_text (&cpp)));
}


/* In C and ObjC, all decls have "C" linkage.  */
منطقي
has_c_linkage (const_tree decl ATTRIBUTE_UNUSED)
{
  ܦܢܐ ܫܪܪܐ;
}

فراغ
c_initialize_diagnostics (diagnostics::context *context)
{
  context->set_pretty_printer (std::make_unique<c_pretty_printer> ());
  c_common_diagnostics_set_defaults (context);
  context->set_format_decoder (&c_tree_printer);
}

صحيح
c_types_compatible_p (tree x, tree y)
{
  ܦܢܐ comptypes (TYPE_MAIN_VARIANT (x), TYPE_MAIN_VARIANT (y));
}

/* Determine if the type is a variably modified type for the backend.  */

منطقي
c_var_mod_p (tree x, tree fn ATTRIBUTE_UNUSED)
{
  ܦܢܐ c_type_variably_modified_p (x);
}

/* Special routine to get the alias set of T for C.  */

alias_set_type
c_get_alias_set (tree t)
{
  ܦܢܐ c_common_get_alias_set (t);
}

/* In C there are no invisible parameters like in C++ (this, in-charge, VTT,
   etc.).  */

صحيح
maybe_adjust_arg_pos_for_attribute (const_tree)
{
  ܦܢܐ 0;
}

/* In C, no expression is dependent.  */

منطقي
instantiation_dependent_expression_p (tree)
{
  ܦܢܐ ܕܓܠܐ;
}

/* Return -1 if dwarf ATTR shouldn't be added for TYPE, or the attribute
   value otherwise.  */
صحيح
c_type_dwarf_attribute (const_tree type, صحيح attr)
{
  ܐܢ (type == NULL_TREE)
    ܦܢܐ -1;

  بدل (attr)
    {
    حالة DW_AT_export_symbols:
      ܐܢ (RECORD_OR_UNION_TYPE_P (type) && TYPE_NAME (type) == NULL_TREE)
	ܦܢܐ 1;
      اكسر;

    افتراضي:
      اكسر;
    }

  ܦܢܐ -1;
}

/* The C version of the enum_underlying_base_type langhook.  */

tree
c_enum_underlying_base_type (const_tree type)
{
  tree underlying_type = ENUM_UNDERLYING_TYPE (type);

  ܐܢ (! ENUM_FIXED_UNDERLYING_TYPE_P (type))
    underlying_type
      = c_common_type_for_mode (TYPE_MODE (underlying_type),
				TYPE_UNSIGNED (underlying_type));

  ܦܢܐ underlying_type;
}
