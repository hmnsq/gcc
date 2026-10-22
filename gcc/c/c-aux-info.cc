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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "tm.h"
#அந்தர்பாவ "c-tree.h"

எண்ணிக்கை formals_style {
  ansi,
  k_and_r_names,
  k_and_r_decls
};


நிலையான மாறிலி எழுத்து *data_type;

நிலையான எழுத்து *affix_data_type (மாறிலி எழுத்து *) ATTRIBUTE_MALLOC;
நிலையான மாறிலி எழுத்து *gen_formal_list_for_type (மரம், formals_style);
நிலையான மாறிலி எழுத்து *gen_formal_list_for_func_def (மரம், formals_style);
நிலையான மாறிலி எழுத்து *gen_type (மாறிலி எழுத்து *, மரம், formals_style);
நிலையான மாறிலி எழுத்து *gen_decl (மரம், முழு, formals_style);

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

நிலையான எழுத்து *
affix_data_type (மாறிலி எழுத்து *param)
{
  எழுத்து *மாறிலி type_or_decl = ASTRDUP (param);
  எழுத்து *p = type_or_decl;
  எழுத்து *qualifiers_then_data_type;
  எழுத்து saved;

  /* Skip as many leading const's or volatile's as there are.  */

  க்கு (;;)
    {
      எனில் (startswith (p, "volatile "))
	{
	  p += 9;
	  தொடர்;
	}
      எனில் (startswith (p, "const "))
	{
	  p += 6;
	  தொடர்;
	}
      நிறுத்து;
    }

  /* p now points to the place where we can insert the data type.  We have to
     add a blank after the data-type of course.  */

  எனில் (p == type_or_decl)
    திரும்பு concat (data_type, " ", type_or_decl, வெற்று);

  saved = *p;
  *p = '\0';
  qualifiers_then_data_type = concat (type_or_decl, data_type, வெற்று);
  *p = saved;
  திரும்பு reconcat (qualifiers_then_data_type,
		   qualifiers_then_data_type, " ", p, வெற்று);
}

/* Given a tree node which represents some "function type", generate the
   source code version of a formal parameter list (of some given style) for
   this function type.  Return the whole formal parameter list (including
   a pair of surrounding parens) as a string.   Note that if the style
   we are currently aiming for is non-ansi, then we just return a pair
   of empty parens here.  */

நிலையான மாறிலி எழுத்து *
gen_formal_list_for_type (மரம் fntype, formals_style style)
{
  மாறிலி எழுத்து *formal_list = "";
  மரம் formal_type;

  எனில் (style != ansi)
    திரும்பு "()";

  formal_type = TYPE_ARG_TYPES (fntype);
  போது (formal_type && மரம்_மதிப்பு (formal_type) != void_type_முனை)
    {
      மாறிலி எழுத்து *this_type;

      எனில் (*formal_list)
	formal_list = concat (formal_list, ", ", வெற்று);

      this_type = gen_type ("", மரம்_மதிப்பு (formal_type), ansi);
      formal_list
	= ((strlen (this_type))
	   ? concat (formal_list, affix_data_type (this_type), வெற்று)
	   : concat (formal_list, data_type, வெற்று));

      formal_type = மரம்_CHAIN (formal_type);
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

  எனில் (!*formal_list)
    {
      எனில் (prototype_p (fntype))
	/* assert (TREE_VALUE (TYPE_ARG_TYPES (fntype)) == void_type_node);  */
	formal_list = "void";
      இல்லையெனில்
	formal_list = "/* ??? */";
    }
  இல்லையெனில்
    {
      /* If there were at least some parameters, and if the formals-types-list
	 petered out to a NULL (i.e. without being terminated by a
	 void_type_node) then we need to tack on an ellipsis.  */
      எனில் (!formal_type)
	formal_list = concat (formal_list, ", ...", வெற்று);
    }

  திரும்பு concat (" (", formal_list, ")", வெற்று);
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

நிலையான மாறிலி எழுத்து *
gen_formal_list_for_func_def (மரம் fndecl, formals_style style)
{
  மாறிலி எழுத்து *formal_list = "";
  மரம் formal_decl;

  formal_decl = DECL_ARGUMENTS (fndecl);
  போது (formal_decl)
    {
      மாறிலி எழுத்து *this_formal;

      எனில் (*formal_list && ((style == ansi) || (style == k_and_r_names)))
	formal_list = concat (formal_list, ", ", வெற்று);
      this_formal = gen_decl (formal_decl, 0, style);
      எனில் (style == k_and_r_decls)
	formal_list = concat (formal_list, this_formal, "; ", வெற்று);
      இல்லையெனில்
	formal_list = concat (formal_list, this_formal, வெற்று);
      formal_decl = மரம்_CHAIN (formal_decl);
    }
  எனில் (style == ansi)
    {
      எனில் (!DECL_ARGUMENTS (fndecl))
	formal_list = concat (formal_list, "void", வெற்று);
      எனில் (stdarg_p (மரம்_TYPE (fndecl)))
	formal_list = concat (formal_list, ", ...", வெற்று);
    }
  எனில் ((style == ansi) || (style == k_and_r_names))
    formal_list = concat (" (", formal_list, ")", வெற்று);
  திரும்பு formal_list;
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

நிலையான மாறிலி எழுத்து *
gen_type (மாறிலி எழுத்து *ret_val, மரம் t, formals_style style)
{
  மரம் chain_p;

  /* If there is a typedef name for this type, use it.  */
  எனில் (TYPE_NAME (t) && மரம்_CODE (TYPE_NAME (t)) == TYPE_DECL)
    data_type = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (t)));
  இல்லையெனில்
    {
      தேர்வு (மரம்_CODE (t))
	{
	நிலை POINTER_TYPE:
	  எனில் (TYPE_ATOMIC (t))
	    ret_val = concat ("_Atomic ", ret_val, வெற்று);
	  எனில் (TYPE_READONLY (t))
	    ret_val = concat ("const ", ret_val, வெற்று);
	  எனில் (TYPE_VOLATILE (t))
	    ret_val = concat ("volatile ", ret_val, வெற்று);

	  ret_val = concat ("*", ret_val, வெற்று);

	  எனில் (மரம்_CODE (மரம்_TYPE (t)) == ARRAY_TYPE || மரம்_CODE (மரம்_TYPE (t)) == FUNCTION_TYPE)
	    ret_val = concat ("(", ret_val, ")", வெற்று);

	  ret_val = gen_type (ret_val, மரம்_TYPE (t), style);

	  திரும்பு ret_val;

	நிலை ARRAY_TYPE:
	  எனில் (!COMPLETE_TYPE_P (t) || மரம்_CODE (TYPE_SIZE (t)) != INTEGER_CST)
	    ret_val = gen_type (concat (ret_val, "[]", வெற்று),
				மரம்_TYPE (t), style);
	  இல்லையெனில் எனில் (int_size_in_bytes (t) == 0)
	    ret_val = gen_type (concat (ret_val, "[0]", வெற்று),
				மரம்_TYPE (t), style);
	  இல்லையெனில்
	    {
	      எழுத்து buff[23];
	      sprintf (buff, "[" HOST_WIDE_INT_PRINT_DEC"]",
		       int_size_in_bytes (t)
		       / int_size_in_bytes (மரம்_TYPE (t)));
	      ret_val = gen_type (concat (ret_val, buff, வெற்று),
				  மரம்_TYPE (t), style);
	    }
	  நிறுத்து;

	நிலை FUNCTION_TYPE:
	  ret_val = gen_type (concat (ret_val,
				      gen_formal_list_for_type (t, style),
				      வெற்று),
			      மரம்_TYPE (t), style);
	  நிறுத்து;

	நிலை IDENTIFIER_முனை:
	  data_type = IDENTIFIER_POINTER (t);
	  நிறுத்து;

	/* The following three cases are complicated by the fact that a
	   user may do something really stupid, like creating a brand new
	   "anonymous" type specification in a formal argument list (or as
	   part of a function return type specification).  For example:

		int f (enum { red, green, blue } color);

	   In such cases, we have no name that we can put into the prototype
	   to represent the (anonymous) type.  Thus, we have to generate the
	   whole darn type specification.  Yuck!  */

	நிலை RECORD_TYPE:
	  எனில் (TYPE_NAME (t))
	    data_type = IDENTIFIER_POINTER (TYPE_NAME (t));
	  இல்லையெனில்
	    {
	      data_type = "";
	      chain_p = TYPE_FIELDS (t);
	      போது (chain_p)
		{
		  data_type = concat (data_type, gen_decl (chain_p, 0, ansi),
				      வெற்று);
		  chain_p = மரம்_CHAIN (chain_p);
		  data_type = concat (data_type, "; ", வெற்று);
		}
	      data_type = concat ("{ ", data_type, "}", வெற்று);
	    }
	  data_type = concat ("struct ", data_type, வெற்று);
	  நிறுத்து;

	நிலை UNION_TYPE:
	  எனில் (TYPE_NAME (t))
	    data_type = IDENTIFIER_POINTER (TYPE_NAME (t));
	  இல்லையெனில்
	    {
	      data_type = "";
	      chain_p = TYPE_FIELDS (t);
	      போது (chain_p)
		{
		  data_type = concat (data_type, gen_decl (chain_p, 0, ansi),
				      வெற்று);
		  chain_p = மரம்_CHAIN (chain_p);
		  data_type = concat (data_type, "; ", வெற்று);
		}
	      data_type = concat ("{ ", data_type, "}", வெற்று);
	    }
	  data_type = concat ("union ", data_type, வெற்று);
	  நிறுத்து;

	நிலை ENUMERAL_TYPE:
	  எனில் (TYPE_NAME (t))
	    data_type = IDENTIFIER_POINTER (TYPE_NAME (t));
	  இல்லையெனில்
	    {
	      data_type = "";
	      chain_p = TYPE_மதிப்புகள் (t);
	      போது (chain_p)
		{
		  data_type = concat (data_type,
			IDENTIFIER_POINTER (மரம்_PURPOSE (chain_p)), வெற்று);
		  chain_p = மரம்_CHAIN (chain_p);
		  எனில் (chain_p)
		    data_type = concat (data_type, ", ", வெற்று);
		}
	      data_type = concat ("{ ", data_type, " }", வெற்று);
	    }
	  data_type = concat ("enum ", data_type, வெற்று);
	  நிறுத்து;

	நிலை TYPE_DECL:
	  data_type = IDENTIFIER_POINTER (DECL_NAME (t));
	  நிறுத்து;

	நிலை INTEGER_TYPE:
	நிலை FIXED_POINT_TYPE:
	  data_type = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (t)));
	  /* Normally, `unsigned' is part of the deal.  Not so if it comes
	     with a type qualifier.  */
	  எனில் (TYPE_UNSIGNED (t) && TYPE_QUALS (t))
	    data_type = concat ("unsigned ", data_type, வெற்று);
	  நிறுத்து;

	நிலை BITINT_TYPE:
	  {
	    எழுத்து buf[அளவு ("2147483647")];
	    sprintf (buf, "%d", TYPE_PRECISION (t));
	    எனில் (TYPE_UNSIGNED (t))
	      data_type = concat ("unsigned _BitInt(", buf, ")", வெற்று);
	    இல்லையெனில்
	      data_type = concat ("_BitInt(", buf, ")", வெற்று);
	    நிறுத்து;
	  }

	நிலை OPAQUE_TYPE:
	நிலை REAL_TYPE:
	  data_type = IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (t)));
	  நிறுத்து;

	நிலை VOID_TYPE:
	  data_type = "void";
	  நிறுத்து;

	நிலை ERROR_MARK:
	  data_type = "[ERROR]";
	  நிறுத்து;

	இயல்பு:
	  gcc_unreachable ();
	}
    }
  எனில் (TYPE_ATOMIC (t))
    ret_val = concat ("_Atomic ", ret_val, வெற்று);
  எனில் (TYPE_READONLY (t))
    ret_val = concat ("const ", ret_val, வெற்று);
  எனில் (TYPE_VOLATILE (t))
    ret_val = concat ("volatile ", ret_val, வெற்று);
  எனில் (TYPE_RESTRICT (t))
    ret_val = concat ("restrict ", ret_val, வெற்று);
  திரும்பு ret_val;
}

/* Generate a string (source) representation of an entire entity declaration
   (using some particular style for function types).

   The given entity may be either a variable or a function.

   If the "is_func_definition" parameter is nonzero, assume that the thing
   we are generating a declaration for is a FUNCTION_DECL node which is
   associated with a function definition.  In this case, we can assume that
   an attached list of DECL nodes for function formal arguments is present.  */

நிலையான மாறிலி எழுத்து *
gen_decl (மரம் decl, முழு is_func_definition, formals_style style)
{
  மாறிலி எழுத்து *ret_val;

  எனில் (DECL_NAME (decl))
    ret_val = IDENTIFIER_POINTER (DECL_NAME (decl));
  இல்லையெனில்
    ret_val = "";

  /* If we are just generating a list of names of formal parameters, we can
     simply return the formal parameter name (with no typing information
     attached to it) now.  */

  எனில் (style == k_and_r_names)
    திரும்பு ret_val;

  /* Note that for the declaration of some entity (either a function or a
     data object, like for instance a parameter) if the entity itself was
     declared as either const or volatile, then const and volatile properties
     are associated with just the declaration of the entity, and *not* with
     the `type' of the entity.  Thus, for such declared entities, we have to
     generate the qualifiers here.  */

  எனில் (மரம்_THIS_VOLATILE (decl))
    ret_val = concat ("volatile ", ret_val, வெற்று);
  எனில் (மரம்_READONLY (decl))
    ret_val = concat ("const ", ret_val, வெற்று);

  data_type = "";

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

  எனில் (மரம்_CODE (decl) == FUNCTION_DECL && is_func_definition)
    {
      ret_val = concat (ret_val, gen_formal_list_for_func_def (decl, ansi),
			வெற்று);

      /* Since we have already added in the formals list stuff, here we don't
	 add the whole "type" of the function we are considering (which
	 would include its parameter-list info), rather, we only add in
	 the "type" of the "type" of the function, which is really just
	 the return-type of the function (and does not include the parameter
	 list info).  */

      ret_val = gen_type (ret_val, மரம்_TYPE (மரம்_TYPE (decl)), style);
    }
  இல்லையெனில்
    ret_val = gen_type (ret_val, மரம்_TYPE (decl), style);

  ret_val = affix_data_type (ret_val);

  எனில் (மரம்_CODE (decl) != FUNCTION_DECL && C_DECL_REGISTER (decl))
    ret_val = concat ("register ", ret_val, வெற்று);
  எனில் (மரம்_PUBLIC (decl))
    ret_val = concat ("extern ", ret_val, வெற்று);
  எனில் (மரம்_CODE (decl) == FUNCTION_DECL && !மரம்_PUBLIC (decl))
    ret_val = concat ("static ", ret_val, வெற்று);

  திரும்பு ret_val;
}

வெளி FILE *aux_info_file;

/* Generate and write a new line of info to the aux-info (.X) file.  This
   routine is called once for each function declaration, and once for each
   function definition (even the implicit ones).  */

வெறுமை
gen_aux_info_record (மரம் fndecl, முழு is_definition, முழு is_implicit,
		     முழு is_prototyped)
{
  எனில் (flag_gen_aux_info)
    {
      நிலையான முழு compiled_from_record = 0;
      expanded_location xloc = expand_location (DECL_SOURCE_LOCATION (fndecl));

      /* Each output .X file must have a header line.  Write one now if we
	 have not yet done so.  */

      எனில் (!compiled_from_record++)
	{
	  /* The first line tells which directory file names are relative to.
	     Currently, -aux-info works only for files in the working
	     directory, so just use a `.' as a placeholder for now.  */
	  fprintf (aux_info_file, "/* compiled from: . */\n");
	}

      /* Write the actual line of auxiliary info.  */

      fprintf (aux_info_file, "/* %s:%d:%c%c */ %s;",
	       xloc.file, xloc.வரி,
	       (is_implicit) ? 'I' : (is_prototyped) ? 'N' : 'O',
	       (is_definition) ? 'F' : 'C',
	       gen_decl (fndecl, is_definition, ansi));

      /* If this is an explicit function declaration, we need to also write
	 out an old-style (i.e. K&R) function header, just in case the user
	 wants to run unprotoize.  */

      எனில் (is_definition)
	{
	  fprintf (aux_info_file, " /*%s %s*/",
		   gen_formal_list_for_func_def (fndecl, k_and_r_names),
		   gen_formal_list_for_func_def (fndecl, k_and_r_decls));
	}

      fprintf (aux_info_file, "\n");
    }
}
