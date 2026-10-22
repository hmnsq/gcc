/* Generate information regarding function declarations and definitions based
   on information stored in GCC's tree structure.  This code implements the
   -aux-info option.
   Copyright (C) 1989-2026 Free Software Foundation, Inc.
   Contributed by Ron Guilmette (rfg@segfault.us.com).

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
#شامل "tm.h"
#شامل "c-tree.h"

شمار formals_style {
  ansi,
  k_and_r_نام,
  k_and_r_decls
};


ساکن ثابت حرف *ڈیٹا_type;

ساکن حرف *affix_ڈیٹا_type (ثابت حرف *) ATTRIBUTE_MALLOC;
ساکن ثابت حرف *gen_formal_list_for_type (درخت, formals_style);
ساکن ثابت حرف *gen_formal_list_for_func_def (درخت, formals_style);
ساکن ثابت حرف *gen_type (ثابت حرف *, درخت, formals_style);
ساکن ثابت حرف *gen_decl (درخت, صحیح, formals_style);

/* Given a string representing an entire type or an entire declaration
   which only lacks the actual "data-type" specifier (at its left end),
   affix the data-type specifier to the left end of the given type
   specification or object declaration.

   Because of C language weirdness, the data-type specifier (which normally
   goes in at the very left end) may have to be slipped in just to the
   right of any leading "const" or "volatile" qualifiers (there may be more
   than one).  Actually this may not be strictly necessary because it seems
   that GCC (at least) accepts `<data-type> const foo;' and treats it the
   same as `const <data-type> foo;' but people are accustomed to seeing
   `const char *foo;' and *not* `char const *foo;' so we try to create types
   that look as expected.  */

ساکن حرف *
affix_ڈیٹا_type (ثابت حرف *param)
{
  حرف *ثابت type_or_decl = ASTRDUP (param);
  حرف *p = type_or_decl;
  حرف *qualifiers_then_ڈیٹا_type;
  حرف saved;

  /* Skip as many leading const's or volatile's as there are.  */

  برائے (;;)
    {
      اگر (startswith (p, "volatile "))
	{
	  p += 9;
	  جاری;
	}
      اگر (startswith (p, "const "))
	{
	  p += 6;
	  جاری;
	}
      توڑو;
    }

  /* p now points to the place where we can insert the data type.  We have to
     add a blank after the data-type of course.  */

  اگر (p == type_or_decl)
    واپس concat (ڈیٹا_type, " ", type_or_decl, تہی);

  saved = *p;
  *p = '\0';
  qualifiers_then_ڈیٹا_type = concat (type_or_decl, ڈیٹا_type, تہی);
  *p = saved;
  واپس reconcat (qualifiers_then_ڈیٹا_type,
		   qualifiers_then_ڈیٹا_type, " ", p, تہی);
}

/* Given a tree node which represents some "function type", generate the
   source code version of a formal parameter list (of some given style) for
   this function type.  Return the whole formal parameter list (including
   a pair of surrounding parens) as a string.   Note that if the style
   we are currently aiming for is non-ansi, then we just return a pair
   of empty parens here.  */

ساکن ثابت حرف *
gen_formal_list_for_type (درخت fntype, formals_style style)
{
  ثابت حرف *formal_list = "";
  درخت formal_type;

  اگر (style != ansi)
    واپس "()";

  formal_type = TYPE_ARG_TYPES (fntype);
  جب (formal_type && درخت_قدر (formal_type) != void_type_گرہ)
    {
      ثابت حرف *this_type;

      اگر (*formal_list)
	formal_list = concat (formal_list, ", ", تہی);

      this_type = gen_type ("", درخت_قدر (formal_type), ansi);
      formal_list
	= ((لڑی_لمبائی (this_type))
	   ? concat (formal_list, affix_ڈیٹا_type (this_type), تہی)
	   : concat (formal_list, ڈیٹا_type, تہی));

      formal_type = درخت_CHAIN (formal_type);
    }

  /* If we got to here, then we are trying to generate an ANSI style formal
     parameters list.

     New style prototyped ANSI formal parameter lists should in theory always
     contain some stuff between the opening and closing parens, even if it is
     only "void".

     The brutal truth though is that there is lots of old K&R code out there
     which contains declarations of "pointer-to-function" parameters and
     these almost never have fully specified formal parameter lists associated
     with them.  That is, the pointer-to-function parameters are declared
     with just empty parameter lists.

     In cases such as these, protoize should really insert *something* into
     the vacant parameter lists, but what?  It has no basis on which to insert
     anything in particular.

     Here, we make life easy for protoize by trying to distinguish between
     K&R empty parameter lists and new-style prototyped parameter lists
     that actually contain "void".  In the latter case we (obviously) want
     to output the "void" verbatim, and that what we do.  In the former case,
     we do our best to give protoize something nice to insert.

     This "something nice" should be something that is still valid (when
     re-compiled) but something that can clearly indicate to the user that
     more typing information (for the parameter list) should be added (by
     hand) at some convenient moment.

     The string chosen here is a comment with question marks in it.  */

  اگر (!*formal_list)
    {
      اگر (prototype_p (fntype))
	/* assert (TREE_VALUE (TYPE_ARG_TYPES (fntype)) == void_type_node);  */
	formal_list = "void";
      ورنہ
	formal_list = "/* ??? */";
    }
  ورنہ
    {
      /* If there were at least some parameters, and if the formals-types-list
	 petered out to a NULL (i.e. without being terminated by a
	 void_type_node) then we need to tack on an ellipsis.  */
      اگر (!formal_type)
	formal_list = concat (formal_list, ", ...", تہی);
    }

  واپس concat (" (", formal_list, ")", تہی);
}

/* Generate a parameter list for a function definition (in some given style).

   Note that this routine has to be separate (and different) from the code that
   generates the prototype parameter lists for function declarations, because
   in the case of a function declaration, all we have to go on is a tree node
   representing the function's own "function type".  This can tell us the types
   of all of the formal parameters for the function, but it cannot tell us the
   actual *names* of each of the formal parameters.  We need to output those
   parameter names for each function definition.

   This routine gets a pointer to a tree node which represents the actual
   declaration of the given function, and this DECL node has a list of formal
   parameter (variable) declarations attached to it.  These formal parameter
   (variable) declaration nodes give us the actual names of the formal
   parameters for the given function definition.

   This routine returns a string which is the source form for the entire
   function formal parameter list.  */

ساکن ثابت حرف *
gen_formal_list_for_func_def (درخت fndecl, formals_style style)
{
  ثابت حرف *formal_list = "";
  درخت formal_decl;

  formal_decl = DECL_ARGUMENTS (fndecl);
  جب (formal_decl)
    {
      ثابت حرف *this_formal;

      اگر (*formal_list && ((style == ansi) || (style == k_and_r_نام)))
	formal_list = concat (formal_list, ", ", تہی);
      this_formal = gen_decl (formal_decl, 0, style);
      اگر (style == k_and_r_decls)
	formal_list = concat (formal_list, this_formal, "; ", تہی);
      ورنہ
	formal_list = concat (formal_list, this_formal, تہی);
      formal_decl = درخت_CHAIN (formal_decl);
    }
  اگر (style == ansi)
    {
      اگر (!DECL_ARGUMENTS (fndecl))
	formal_list = concat (formal_list, "void", تہی);
      اگر (stdarg_p (درخت_TYPE (fndecl)))
	formal_list = concat (formal_list, ", ...", تہی);
    }
  اگر ((style == ansi) || (style == k_and_r_نام))
    formal_list = concat (" (", formal_list, ")", تہی);
  واپس formal_list;
}

/* Generate a string which is the source code form for a given type (t).  This
   routine is ugly and complex because the C syntax for declarations is ugly
   and complex.  This routine is straightforward so long as *no* pointer types,
   array types, or function types are involved.

   In the simple cases, this routine will return the (string) value which was
   passed in as the "ret_val" argument.  Usually, this starts out either as an
   empty string, or as the name of the declared item (i.e. the formal function
   parameter variable).

   This routine will also return with the global variable "data_type" set to
   some string value which is the "basic" data-type of the given complete type.
   This "data_type" string can be concatenated onto the front of the returned
   string after this routine returns to its caller.

   In complicated cases involving pointer types, array types, or function
   types, the C declaration syntax requires an "inside out" approach, i.e. if
   you have a type which is a "pointer-to-function" type, you need to handle
   the "pointer" part first, but it also has to be "innermost" (relative to
   the declaration stuff for the "function" type).  Thus, is this case, you
   must prepend a "(*" and append a ")" to the name of the item (i.e. formal
   variable).  Then you must append and prepend the other info for the
   "function type" part of the overall type.

   To handle the "innermost precedence" rules of complicated C declarators, we
   do the following (in this routine).  The input parameter called "ret_val"
   is treated as a "seed".  Each time gen_type is called (perhaps recursively)
   some additional strings may be appended or prepended (or both) to the "seed"
   string.  If yet another (lower) level of the GCC tree exists for the given
   type (as in the case of a pointer type, an array type, or a function type)
   then the (wrapped) seed is passed to a (recursive) invocation of gen_type()
   this recursive invocation may again "wrap" the (new) seed with yet more
   declarator stuff, by appending, prepending (or both).  By the time the
   recursion bottoms out, the "seed value" at that point will have a value
   which is (almost) the complete source version of the declarator (except
   for the data_type info).  Thus, this deepest "seed" value is simply passed
   back up through all of the recursive calls until it is given (as the return
   value) to the initial caller of the gen_type() routine.  All that remains
   to do at this point is for the initial caller to prepend the "data_type"
   string onto the returned "seed".  */

ساکن ثابت حرف *
gen_type (ثابت حرف *ret_val, درخت t, formals_style style)
{
  درخت chain_p;

  /* If there is a typedef name for this type, use it.  */
  اگر (TYPE_NAME (t) && درخت_رمز (TYPE_NAME (t)) == TYPE_DECL)
    ڈیٹا_type = IDENTIFIER_اشارہ_گر (DECL_NAME (TYPE_NAME (t)));
  ورنہ
    {
      انتخاب (درخت_رمز (t))
	{
	حالت اشارہ_گر_TYPE:
	  اگر (TYPE_ATOMIC (t))
	    ret_val = concat ("_Atomic ", ret_val, تہی);
	  اگر (TYPE_READONLY (t))
	    ret_val = concat ("const ", ret_val, تہی);
	  اگر (TYPE_VOLATILE (t))
	    ret_val = concat ("volatile ", ret_val, تہی);

	  ret_val = concat ("*", ret_val, تہی);

	  اگر (درخت_رمز (درخت_TYPE (t)) == ARRAY_TYPE || درخت_رمز (درخت_TYPE (t)) == FUNCTION_TYPE)
	    ret_val = concat ("(", ret_val, ")", تہی);

	  ret_val = gen_type (ret_val, درخت_TYPE (t), style);

	  واپس ret_val;

	حالت ARRAY_TYPE:
	  اگر (!COMPLETE_TYPE_P (t) || درخت_رمز (TYPE_سائز (t)) != INTEGER_CST)
	    ret_val = gen_type (concat (ret_val, "[]", تہی),
				درخت_TYPE (t), style);
	  ورنہ اگر (int_سائز_اندر_بائٹیں (t) == 0)
	    ret_val = gen_type (concat (ret_val, "[0]", تہی),
				درخت_TYPE (t), style);
	  ورنہ
	    {
	      حرف buff[23];
	      sprintf (buff, "[" HOST_WIDE_INT_PRINT_DEC"]",
		       int_سائز_اندر_بائٹیں (t)
		       / int_سائز_اندر_بائٹیں (درخت_TYPE (t)));
	      ret_val = gen_type (concat (ret_val, buff, تہی),
				  درخت_TYPE (t), style);
	    }
	  توڑو;

	حالت FUNCTION_TYPE:
	  ret_val = gen_type (concat (ret_val,
				      gen_formal_list_for_type (t, style),
				      تہی),
			      درخت_TYPE (t), style);
	  توڑو;

	حالت IDENTIFIER_گرہ:
	  ڈیٹا_type = IDENTIFIER_اشارہ_گر (t);
	  توڑو;

	/* The following three cases are complicated by the fact that a
	   user may do something really stupid, like creating a brand new
	   "anonymous" type specification in a formal argument list (or as
	   part of a function return type specification).  For example:

		int f (enum { red, green, blue } color);

	   In such cases, we have no name that we can put into the prototype
	   to represent the (anonymous) type.  Thus, we have to generate the
	   whole darn type specification.  Yuck!  */

	حالت ریکارڈ_TYPE:
	  اگر (TYPE_NAME (t))
	    ڈیٹا_type = IDENTIFIER_اشارہ_گر (TYPE_NAME (t));
	  ورنہ
	    {
	      ڈیٹا_type = "";
	      chain_p = TYPE_FIELDS (t);
	      جب (chain_p)
		{
		  ڈیٹا_type = concat (ڈیٹا_type, gen_decl (chain_p, 0, ansi),
				      تہی);
		  chain_p = درخت_CHAIN (chain_p);
		  ڈیٹا_type = concat (ڈیٹا_type, "; ", تہی);
		}
	      ڈیٹا_type = concat ("{ ", ڈیٹا_type, "}", تہی);
	    }
	  ڈیٹا_type = concat ("struct ", ڈیٹا_type, تہی);
	  توڑو;

	حالت UNION_TYPE:
	  اگر (TYPE_NAME (t))
	    ڈیٹا_type = IDENTIFIER_اشارہ_گر (TYPE_NAME (t));
	  ورنہ
	    {
	      ڈیٹا_type = "";
	      chain_p = TYPE_FIELDS (t);
	      جب (chain_p)
		{
		  ڈیٹا_type = concat (ڈیٹا_type, gen_decl (chain_p, 0, ansi),
				      تہی);
		  chain_p = درخت_CHAIN (chain_p);
		  ڈیٹا_type = concat (ڈیٹا_type, "; ", تہی);
		}
	      ڈیٹا_type = concat ("{ ", ڈیٹا_type, "}", تہی);
	    }
	  ڈیٹا_type = concat ("union ", ڈیٹا_type, تہی);
	  توڑو;

	حالت ENUMERAL_TYPE:
	  اگر (TYPE_NAME (t))
	    ڈیٹا_type = IDENTIFIER_اشارہ_گر (TYPE_NAME (t));
	  ورنہ
	    {
	      ڈیٹا_type = "";
	      chain_p = TYPE_اقدار (t);
	      جب (chain_p)
		{
		  ڈیٹا_type = concat (ڈیٹا_type,
			IDENTIFIER_اشارہ_گر (درخت_PURPOSE (chain_p)), تہی);
		  chain_p = درخت_CHAIN (chain_p);
		  اگر (chain_p)
		    ڈیٹا_type = concat (ڈیٹا_type, ", ", تہی);
		}
	      ڈیٹا_type = concat ("{ ", ڈیٹا_type, " }", تہی);
	    }
	  ڈیٹا_type = concat ("enum ", ڈیٹا_type, تہی);
	  توڑو;

	حالت TYPE_DECL:
	  ڈیٹا_type = IDENTIFIER_اشارہ_گر (DECL_NAME (t));
	  توڑو;

	حالت INTEGER_TYPE:
	حالت FIXED_نقطہ_TYPE:
	  ڈیٹا_type = IDENTIFIER_اشارہ_گر (DECL_NAME (TYPE_NAME (t)));
	  /* Normally, `unsigned' is part of the deal.  Not so if it comes
	     with a type qualifier.  */
	  اگر (TYPE_UNSIGNED (t) && TYPE_QUALS (t))
	    ڈیٹا_type = concat ("unsigned ", ڈیٹا_type, تہی);
	  توڑو;

	حالت BITINT_TYPE:
	  {
	    حرف buf[حجم ("2147483647")];
	    sprintf (buf, "%d", TYPE_PRECISION (t));
	    اگر (TYPE_UNSIGNED (t))
	      ڈیٹا_type = concat ("unsigned _BitInt(", buf, ")", تہی);
	    ورنہ
	      ڈیٹا_type = concat ("_BitInt(", buf, ")", تہی);
	    توڑو;
	  }

	حالت OPAQUE_TYPE:
	حالت REAL_TYPE:
	  ڈیٹا_type = IDENTIFIER_اشارہ_گر (DECL_NAME (TYPE_NAME (t)));
	  توڑو;

	حالت VOID_TYPE:
	  ڈیٹا_type = "void";
	  توڑو;

	حالت ERROR_MARK:
	  ڈیٹا_type = "[ERROR]";
	  توڑو;

	طےشدہ:
	  gcc_unreachable ();
	}
    }
  اگر (TYPE_ATOMIC (t))
    ret_val = concat ("_Atomic ", ret_val, تہی);
  اگر (TYPE_READONLY (t))
    ret_val = concat ("const ", ret_val, تہی);
  اگر (TYPE_VOLATILE (t))
    ret_val = concat ("volatile ", ret_val, تہی);
  اگر (TYPE_RESTRICT (t))
    ret_val = concat ("restrict ", ret_val, تہی);
  واپس ret_val;
}

/* Generate a string (source) representation of an entire entity declaration
   (using some particular style for function types).

   The given entity may be either a variable or a function.

   If the "is_func_definition" parameter is nonzero, assume that the thing
   we are generating a declaration for is a FUNCTION_DECL node which is
   associated with a function definition.  In this case, we can assume that
   an attached list of DECL nodes for function formal arguments is present.  */

ساکن ثابت حرف *
gen_decl (درخت decl, صحیح is_func_definition, formals_style style)
{
  ثابت حرف *ret_val;

  اگر (DECL_NAME (decl))
    ret_val = IDENTIFIER_اشارہ_گر (DECL_NAME (decl));
  ورنہ
    ret_val = "";

  /* If we are just generating a list of names of formal parameters, we can
     simply return the formal parameter name (with no typing information
     attached to it) now.  */

  اگر (style == k_and_r_نام)
    واپس ret_val;

  /* Note that for the declaration of some entity (either a function or a
     data object, like for instance a parameter) if the entity itself was
     declared as either const or volatile, then const and volatile properties
     are associated with just the declaration of the entity, and *not* with
     the `type' of the entity.  Thus, for such declared entities, we have to
     generate the qualifiers here.  */

  اگر (درخت_THIS_VOLATILE (decl))
    ret_val = concat ("volatile ", ret_val, تہی);
  اگر (درخت_READONLY (decl))
    ret_val = concat ("const ", ret_val, تہی);

  ڈیٹا_type = "";

  /* For FUNCTION_DECL nodes, there are two possible cases here.  First, if
     this FUNCTION_DECL node was generated from a function "definition", then
     we will have a list of DECL_NODE's, one for each of the function's formal
     parameters.  In this case, we can print out not only the types of each
     formal, but also each formal's name.  In the second case, this
     FUNCTION_DECL node came from an actual function declaration (and *not*
     a definition).  In this case, we do nothing here because the formal
     argument type-list will be output later, when the "type" of the function
     is added to the string we are building.  Note that the ANSI-style formal
     parameter list is considered to be a (suffix) part of the "type" of the
     function.  */

  اگر (درخت_رمز (decl) == FUNCTION_DECL && is_func_definition)
    {
      ret_val = concat (ret_val, gen_formal_list_for_func_def (decl, ansi),
			تہی);

      /* Since we have already added in the formals list stuff, here we don't
	 add the whole "type" of the function we are considering (which
	 would include its parameter-list info), rather, we only add in
	 the "type" of the "type" of the function, which is really just
	 the return-type of the function (and does not include the parameter
	 list info).  */

      ret_val = gen_type (ret_val, درخت_TYPE (درخت_TYPE (decl)), style);
    }
  ورنہ
    ret_val = gen_type (ret_val, درخت_TYPE (decl), style);

  ret_val = affix_ڈیٹا_type (ret_val);

  اگر (درخت_رمز (decl) != FUNCTION_DECL && C_DECL_رجسٹر (decl))
    ret_val = concat ("register ", ret_val, تہی);
  اگر (درخت_عوامی (decl))
    ret_val = concat ("extern ", ret_val, تہی);
  اگر (درخت_رمز (decl) == FUNCTION_DECL && !درخت_عوامی (decl))
    ret_val = concat ("static ", ret_val, تہی);

  واپس ret_val;
}

خارجی FILE *aux_info_file;

/* Generate and write a new line of info to the aux-info (.X) file.  This
   routine is called once for each function declaration, and once for each
   function definition (even the implicit ones).  */

خالی
gen_aux_info_ریکارڈ (درخت fndecl, صحیح is_definition, صحیح is_implicit,
		     صحیح is_prototyped)
{
  اگر (flag_gen_aux_info)
    {
      ساکن صحیح compiled_from_ریکارڈ = 0;
      expanded_location xloc = expand_location (DECL_ماخذ_LOCATION (fndecl));

      /* Each output .X file must have a header line.  Write one now if we
	 have not yet done so.  */

      اگر (!compiled_from_ریکارڈ++)
	{
	  /* The first line tells which directory file names are relative to.
	     Currently, -aux-info works only for files in the working
	     directory, so just use a `.' as a placeholder for now.  */
	  fprintf (aux_info_file, "/* compiled from: . */\n");
	}

      /* Write the actual line of auxiliary info.  */

      fprintf (aux_info_file, "/* %s:%d:%c%c */ %s;",
	       xloc.file, xloc.سطر,
	       (is_implicit) ? 'I' : (is_prototyped) ? 'N' : 'O',
	       (is_definition) ? 'F' : 'C',
	       gen_decl (fndecl, is_definition, ansi));

      /* If this is an explicit function declaration, we need to also write
	 out an old-style (i.e. K&R) function header, just in case the user
	 wants to run unprotoize.  */

      اگر (is_definition)
	{
	  fprintf (aux_info_file, " /*%s %s*/",
		   gen_formal_list_for_func_def (fndecl, k_and_r_نام),
		   gen_formal_list_for_func_def (fndecl, k_and_r_decls));
	}

      fprintf (aux_info_file, "\n");
    }
}
