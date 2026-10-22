/* Parser for C and Objective-C.

   Copyright (C) 1987-2026 Free Software Foundation, Inc.
   Parser actions based on the old Bison parser; structure somewhat
   influenced by and fragments based on the C++ parser.

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

/* TODO:

   Make sure all relevant comments, and all relevant code from all
   actions, brought over from old parser.  Verify exact correspondence
   of syntax accepted.

   Add testcases covering every input symbol in every state in old and
   new parsers.

   Include full syntax for GNU C, including erroneous cases accepted
   with error messages, in syntax productions in comments.

   Make more diagnostics in the front end generally take an explicit
   location rather than implicitly using input_location.  */

#ضمن "config.h"
#تعریف_کن INCLUDE_STRING
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "target.h"
#ضمن "function.h"
#ضمن "c-tree.h"
#ضمن "timevar.h"
#ضمن "stringpool.h"
#ضمن "cgraph.h"
#ضمن "attribs.h"
#ضمن "stor-layout.h"
#ضمن "varasm.h"
#ضمن "trans-mem.h"
#ضمن "c-family/c-pragma.h"
#ضمن "c-lang.h"
#ضمن "c-family/c-objc.h"
#ضمن "plugin.h"
#ضمن "omp-general.h"
#ضمن "omp-offload.h"
#ضمن "builtins.h"
#ضمن "gomp-constants.h"
#ضمن "c-family/c-indentation.h"
#ضمن "gimple-expr.h"
#ضمن "context.h"
#ضمن "gcc-rich-location.h"
#ضمن "c-parser.h"
#ضمن "gimple-parser.h"
#ضمن "read-rtl-function.h"
#ضمن "run-rtl-passes.h"
#ضمن "intl.h"
#ضمن "c-family/name-hint.h"
#ضمن "tree-iterator.h"
#ضمن "tree-pretty-print.h"
#ضمن "memmodel.h"
#ضمن "c-family/known-headers.h"
#ضمن "bitmap.h"
#ضمن "analyzer/analyzer-language.h"
#ضمن "toplev.h"
#ضمن "asan.h"
#ضمن "c-family/c-ubsan.h"
#ضمن "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<درخت> incomplete_رکورد_decls;

فراغ
مجموعه_c_عبارت_منبع_range (c_عبارت *عبارت,
			 location_t شروع, location_t پایان)
{
  عبارت->src_range.m_شروع = شروع;
  عبارت->src_range.m_پایان = پایان;
  إذا (عبارت->مقدار)
    مجموعه_منبع_range (عبارت->مقدار, شروع, پایان);
}

فراغ
مجموعه_c_عبارت_منبع_range (c_عبارت *عبارت,
			 منبع_range src_range)
{
  عبارت->src_range = src_range;
  إذا (عبارت->مقدار)
    مجموعه_منبع_range (عبارت->مقدار, src_range);
}


/* Initialization routine for this file.  */

فراغ
c_parse_init (فراغ)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  بیعلامت صحيح i;
  درخت id;
  صحيح ماسک = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  ماسک |= D_CXXONLY;
  إذا (!flag_isoc99)
    ماسک |= D_C99;
  إذا (!flag_isoc23)
    ماسک |= D_C23;
  إذا (flag_no_asm)
    {
      ماسک |= D_ASM | D_EXT;
      إذا (!flag_isoc99)
	ماسک |= D_EXT89;
      إذا (!flag_isoc23)
	ماسک |= D_EXT11;
    }
  إذا (!c_dialect_objc ())
    ماسک |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<درخت> ((صحيح) RID_MAX);
  لكل (i = 0; i < رقم_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      إذا (c_common_reswords[i].disable & ماسک)
	{
	  إذا (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].کلمه);
	      C_مجموعه_RID_کد (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_کلمه (id) = 1;
	    }
	  استمر;
	}

      id = get_identifier (c_common_reswords[i].کلمه);
      C_مجموعه_RID_کد (id, c_common_reswords[i].rid);
      C_IS_RESERVED_کلمه (id) = 1;
      ridpointers [(صحيح) c_common_reswords[i].rid] = id;
    }

  لكل (i = 0; i < رقم_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      حرف name[50];
      sprintf (name, "__int%d", int_n_داده[i].bitsize);
      id = get_identifier (name);
      C_مجموعه_RID_کد (id, RID_اولی_INT_N + i);
      C_IS_RESERVED_کلمه (id) = 1;

      sprintf (name, "__int%d__", int_n_داده[i].bitsize);
      id = get_identifier (name);
      C_مجموعه_RID_کد (id, RID_اولی_INT_N + i);
      C_IS_RESERVED_کلمه (id) = 1;
    }

  إذا (flag_openmp)
    {
      id = get_identifier ("omp_all_memory");
      C_مجموعه_RID_کد (id, RID_OMP_ALL_حافظه);
      C_IS_RESERVED_کلمه (id) = 1;
      ridpointers [RID_OMP_ALL_حافظه] = id;
    }
}

/* A parser structure recording information about the state and
   context of parsing.  Includes lexer information with up to two
   tokens of look-ahead; more are not needed for C.  */
بنية GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) نشانهها;
  /* Buffer for look-ahead tokens.  */
  c_token نشانهها_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  بیعلامت صحيح نشانهها_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_نشانهها;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  بیعلامت صحيح raw_نشانهها_استفاده_شده;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  منطقي error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  منطقي درون_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  منطقي درون_if_بلوک : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  منطقي lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  منطقي translate_رشتهها_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  منطقي objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  منطقي objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  منطقي objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  بیعلامت صحيح درون_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  منطقي objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  منطقي دیده_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  منطقي omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t آخرین_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  بنية omp_for_parse_داده * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  بنية omp_attribute_pragma_state *درون_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  درخت درون_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  بنية omp_metadirective_parse_داده * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
بنية GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_نشانهها;
  بیعلامت صحيح save_نشانهها_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
بنية GTY(()) omp_begin_declare_variant_map_مدخل {
  درخت variant;		/* The variant decl.  */
  درخت id;		/* Name of base function.  */
  درخت ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_مدخل, va_gc> *omp_begin_declare_variant_map;

ساكن درخت omp_شروع_variant_function (c_declarator *, درخت);
ساكن فراغ omp_پایان_variant_function (درخت, درخت, درخت);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_نشانهها_buf (c_parser *parser, بیعلامت n)
{
  أرجع &parser->نشانهها_buf[n];
}

/* Return the error state of PARSER.  */

منطقي
c_parser_error (c_parser *parser)
{
  أرجع parser->error;
}

/* Set the error state of PARSER to ERR.  */

فراغ
c_parser_مجموعه_error (c_parser *parser, منطقي err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

ساكن GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

ساكن فراغ
c_lex_one_token (c_parser *parser, c_token *token, منطقي raw = خطأ)
{
  timevar_افزودن (TV_LEX);

  إذا (raw || vec_امن_درازی (parser->raw_نشانهها) == 0)
    {
      token->type = c_lex_with_flags (&token->مقدار, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_نوع = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_نوع = PRAGMA_NONE;
    }
  وإلا
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_نشانهها)[parser->raw_نشانهها_استفاده_شده];
      ++parser->raw_نشانهها_استفاده_شده;
      إذا (parser->raw_نشانهها_استفاده_شده == vec_امن_درازی (parser->raw_نشانهها))
	{
	  vec_free (parser->raw_نشانهها);
	  parser->raw_نشانهها_استفاده_شده = 0;
	}
    }

  إذا (raw)
    اذهب بیرون;

  بدل (token->type)
    {
    حالة CPP_NAME:
      {
	درخت decl;

	منطقي objc_force_identifier = parser->objc_need_raw_identifier;
	إذا (c_dialect_objc ())
	  parser->objc_need_raw_identifier = خطأ;

	إذا (C_IS_RESERVED_کلمه (token->مقدار))
	  {
	    تعداد rid rid_کد = C_RID_کد (token->مقدار);

	    إذا (rid_کد == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->مقدار);
	      }
	    وإلا إذا (rid_کد >= RID_اولی_ADDR_SPACE
		     && rid_کد <= RID_آخرین_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_کد - RID_اولی_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_نوع = C_ID_ADDRSPACE;
		token->keyword = rid_کد;
		اكسر;
	      }
	    وإلا إذا (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_کد))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		إذا (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_کد;
		    اكسر;
		  }
		وإلا إذا (parser->objc_could_be_foreach_context
			 && rid_کد == RID_درون)
		  {
		    /* We are in Objective-C, inside a (potential)
		       foreach context (which means after having
		       parsed 'for (', but before having parsed ';'),
		       and we found 'in'.  We consider it the keyword
		       which terminates the declaration at the
		       beginning of a foreach-statement.  Note that
		       this means you can't use 'in' for anything else
		       in that context; in particular, in Objective-C
		       you can't use 'in' as the name of the running
		       variable in a C for loop.  We could potentially
		       try to add code here to disambiguate, but it
		       seems a reasonable limitation.  */
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_کد;
		    اكسر;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    وإلا إذا (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_کد))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		إذا (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_کد;
		    اكسر;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    وإلا إذا (c_dialect_objc ()
		     && (OBJC_IS_AT_KEYWORD (rid_کد)
			 || OBJC_IS_CXX_KEYWORD (rid_کد)))
	      {
		/* We found one of the Objective-C "@" keywords (defs,
		   selector, synchronized, etc) or one of the
		   Objective-C "cxx" keywords (class, private,
		   protected, public, try, catch, throw) without a
		   preceding '@' sign.  Do nothing and fall through to
		   the code for normal tokens (in C++ we would still
		   consider the CXX ones keywords, but not in C).  */
		;
	      }
	    وإلا
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_کد;
		اكسر;
	      }
	  }

	decl = lookup_name (token->مقدار);
	إذا (decl)
	  {
	    إذا (درخت_کد (decl) == TYPE_DECL)
	      {
		token->id_نوع = C_ID_TYPENAME;
		اكسر;
	      }
	  }
	وإلا إذا (c_dialect_objc ())
	  {
	    درخت objc_interface_decl = objc_is_class_name (token->مقدار);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    إذا (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->مقدار = objc_interface_decl;
		token->id_نوع = C_ID_CLASSNAME;
		اكسر;
	      }
	  }
        token->id_نوع = C_ID_ID;
      }
      اكسر;
    حالة CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      بدل (C_RID_کد (token->مقدار))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	حالة RID_CLASS:     token->keyword = RID_AT_CLASS; اكسر;
	حالة RID_خصوصی:   token->keyword = RID_AT_خصوصی; اكسر;
	حالة RID_PROTECTED: token->keyword = RID_AT_PROTECTED; اكسر;
	حالة RID_عمومی:    token->keyword = RID_AT_عمومی; اكسر;
	حالة RID_THROW:     token->keyword = RID_AT_THROW; اكسر;
	حالة RID_TRY:       token->keyword = RID_AT_TRY; اكسر;
	حالة RID_CATCH:     token->keyword = RID_AT_CATCH; اكسر;
	حالة RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; اكسر;
	افتراضي:            token->keyword = C_RID_کد (token->مقدار);
	}
      اكسر;
    حالة CPP_COLON:
    حالة CPP_COMMA:
    حالة CPP_CLOSE_PAREN:
    حالة CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      إذا (c_dialect_objc ())
	parser->objc_need_raw_identifier = خطأ;
      اكسر;
    حالة CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_نوع = (تعداد pragma_نوع) درخت_INT_CST_کم (token->مقدار);
      token->مقدار = عدم;
      اكسر;
    افتراضي:
      اكسر;
    }
 بیرون:
  timevar_برداشت (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  إذا (parser->نشانهها_avail == 0)
    {
      c_lex_one_token (parser, &parser->نشانهها[0]);
      parser->نشانهها_avail = 1;
    }
  أرجع &parser->نشانهها[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  إذا (parser->نشانهها_avail >= 2)
    أرجع &parser->نشانهها[1];
  gcc_assert (parser->نشانهها_avail == 1);
  gcc_assert (parser->نشانهها[0].type != CPP_EOF);
  gcc_assert (parser->نشانهها[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->نشانهها[1]);
  parser->نشانهها_avail = 2;
  أرجع &parser->نشانهها[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, بیعلامت صحيح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  إذا (parser->نشانهها_avail >= n)
    أرجع &parser->نشانهها[n - 1];
  gcc_assert (parser->نشانهها_avail == n - 1);
  c_lex_one_token (parser, &parser->نشانهها[n - 1]);
  parser->نشانهها_avail = n;
  أرجع &parser->نشانهها[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, بیعلامت صحيح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  إذا (parser->نشانهها_avail >= n)
    أرجع &parser->نشانهها[n - 1];
  بیعلامت صحيح raw_len = vec_امن_درازی (parser->raw_نشانهها);
  بیعلامت صحيح raw_avail
    = parser->نشانهها_avail + raw_len - parser->raw_نشانهها_استفاده_شده;
  gcc_assert (raw_avail >= n - 1);
  إذا (raw_avail >= n)
    أرجع &(*parser->raw_نشانهها)[parser->raw_نشانهها_استفاده_شده
				  + n - 1 - parser->نشانهها_avail];
  vec_امن_reserve (parser->raw_نشانهها, 1);
  parser->raw_نشانهها->سریع_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_نشانهها)[raw_len], درست);
  أرجع &(*parser->raw_نشانهها)[raw_len];
}

منطقي
c_keyword_starts_typename (تعداد rid keyword)
{
  بدل (keyword)
    {
    حالة RID_UNSIGNED:
    حالة RID_LONG:
    حالة RID_SHORT:
    حالة RID_SIGNED:
    حالة RID_COMPLEX:
    حالة RID_INT:
    حالة RID_CHAR:
    حالة RID_FLOAT:
    حالة RID_DOUBLE:
    حالة RID_VOID:
    حالة RID_DFLOAT32:
    حالة RID_DFLOAT64:
    حالة RID_DFLOAT128:
    حالة RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    حالة RID_BOOL:
    حالة RID_BITINT:
    حالة RID_ENUM:
    حالة RID_STRUCT:
    حالة RID_UNION:
    حالة RID_TYPEOF:
    حالة RID_TYPEOF_UNQUAL:
    حالة RID_CONST:
    حالة RID_ATOMIC:
    حالة RID_VOLATILE:
    حالة RID_RESTRICT:
    حالة RID_ATTRIBUTE:
    حالة RID_FRACT:
    حالة RID_ACCUM:
    حالة RID_SAT:
    حالة RID_AUTO_TYPE:
    حالة RID_ALIGNAS:
      أرجع درست;
    افتراضي:
      إذا (keyword >= RID_اولی_INT_N
	  && keyword < RID_اولی_INT_N + رقم_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_اولی_INT_N])
	أرجع درست;
      أرجع خطأ;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
منطقي
c_token_starts_typename (c_token *token)
{
  بدل (token->type)
    {
    حالة CPP_NAME:
      بدل (token->id_نوع)
	{
	حالة C_ID_ID:
	  أرجع خطأ;
	حالة C_ID_ADDRSPACE:
	  أرجع درست;
	حالة C_ID_TYPENAME:
	  أرجع درست;
	حالة C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  أرجع درست;
	افتراضي:
	  gcc_unreachable ();
	}
    حالة CPP_KEYWORD:
      أرجع c_keyword_starts_typename (token->keyword);
    حالة CPP_LESS:
      إذا (c_dialect_objc ())
	أرجع درست;
      أرجع خطأ;
    افتراضي:
      أرجع خطأ;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

ساكن مضمن منطقي
c_parser_بعدی_نشانهها_شروع_typename (c_parser *parser, تعداد c_lookahead_نوع la,
				     بیعلامت صحيح n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  إذا (c_token_starts_typename (token))
    أرجع درست;

  /* Try a bit harder to detect an unknown typename.  */
  إذا (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_نوع == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->مقدار))
    أرجع درست;

  أرجع خطأ;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
ساكن منطقي
c_token_starts_compound_literal (c_token *token)
{
  بدل (token->type)
    {
    حالة CPP_KEYWORD:
      بدل (token->keyword)
	{
	حالة RID_CONSTEXPR:
	حالة RID_ثبات:
	حالة RID_STATIC:
	حالة RID_THREAD:
	  أرجع درست;
	افتراضي:
	  اكسر;
	}
      /* Fall through.  */
    افتراضي:
      أرجع c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
ساكن منطقي
c_token_is_qualifier (c_token *token)
{
  بدل (token->type)
    {
    حالة CPP_NAME:
      بدل (token->id_نوع)
	{
	حالة C_ID_ADDRSPACE:
	  أرجع درست;
	افتراضي:
	  أرجع خطأ;
	}
    حالة CPP_KEYWORD:
      بدل (token->keyword)
	{
	حالة RID_CONST:
	حالة RID_VOLATILE:
	حالة RID_RESTRICT:
	حالة RID_ATTRIBUTE:
	حالة RID_ATOMIC:
	  أرجع درست;
	افتراضي:
	  أرجع خطأ;
	}
    حالة CPP_LESS:
      أرجع خطأ;
    افتراضي:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
ساكن مضمن منطقي
c_parser_بعدی_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  أرجع c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
ساكن منطقي
c_token_starts_declspecs (c_token *token)
{
  بدل (token->type)
    {
    حالة CPP_NAME:
      بدل (token->id_نوع)
	{
	حالة C_ID_ID:
	  أرجع خطأ;
	حالة C_ID_ADDRSPACE:
	  أرجع درست;
	حالة C_ID_TYPENAME:
	  أرجع درست;
	حالة C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  أرجع درست;
	افتراضي:
	  gcc_unreachable ();
	}
    حالة CPP_KEYWORD:
      بدل (token->keyword)
	{
	حالة RID_STATIC:
	حالة RID_EXTERN:
	حالة RID_ثبات:
	حالة RID_TYPEDEF:
	حالة RID_INLINE:
	حالة RID_NORETURN:
	حالة RID_AUTO:
	حالة RID_THREAD:
	حالة RID_UNSIGNED:
	حالة RID_LONG:
	حالة RID_SHORT:
	حالة RID_SIGNED:
	حالة RID_COMPLEX:
	حالة RID_INT:
	حالة RID_CHAR:
	حالة RID_FLOAT:
	حالة RID_DOUBLE:
	حالة RID_VOID:
	حالة RID_DFLOAT32:
	حالة RID_DFLOAT64:
	حالة RID_DFLOAT128:
	حالة RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالة RID_BOOL:
	حالة RID_BITINT:
	حالة RID_ENUM:
	حالة RID_STRUCT:
	حالة RID_UNION:
	حالة RID_TYPEOF:
	حالة RID_TYPEOF_UNQUAL:
	حالة RID_CONST:
	حالة RID_VOLATILE:
	حالة RID_RESTRICT:
	حالة RID_ATTRIBUTE:
	حالة RID_FRACT:
	حالة RID_ACCUM:
	حالة RID_SAT:
	حالة RID_ALIGNAS:
	حالة RID_ATOMIC:
	حالة RID_AUTO_TYPE:
	حالة RID_CONSTEXPR:
	  أرجع درست;
	افتراضي:
	  إذا (token->keyword >= RID_اولی_INT_N
	      && token->keyword < RID_اولی_INT_N + رقم_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_اولی_INT_N])
	    أرجع درست;
	  أرجع خطأ;
	}
    حالة CPP_LESS:
      إذا (c_dialect_objc ())
	أرجع درست;
      أرجع خطأ;
    افتراضي:
      أرجع خطأ;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
ساكن منطقي
c_token_starts_declaration (c_token *token)
{
  إذا (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    أرجع درست;
  وإلا
    أرجع خطأ;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
منطقي
c_parser_بعدی_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  إذا (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_نوع == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    أرجع خطأ;

  أرجع c_token_starts_declspecs (token);
}

ساكن منطقي c_parser_check_متوازن_raw_token_sequence (c_parser *,
							بیعلامت صحيح *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
منطقي
c_parser_بعدی_نشانهها_شروع_declaration (c_parser *parser, بیعلامت صحيح n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  إذا (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_نوع == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    أرجع خطأ;

  /* Labels do not start declarations.  */
  إذا (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    أرجع خطأ;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  إذا (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	أرجع درست;
      أرجع c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  إذا (c_token_starts_declaration (token))
    أرجع درست;

  إذا (c_parser_بعدی_نشانهها_شروع_typename (parser, cla_nonabstract_decl, n))
    أرجع درست;

  أرجع خطأ;
}

/* Consume the next token from PARSER.  */

فراغ
c_parser_consume_token (c_parser *parser)
{
  gcc_assert (parser->نشانهها_avail >= 1);
  gcc_assert (parser->نشانهها[0].type != CPP_EOF);
  gcc_assert (!parser->درون_pragma || parser->نشانهها[0].type != CPP_PRAGMA_EOL);
  /* CPP_PRAGMA should not show up here except if there was an error or inside
     another pragma.  */
  gcc_assert (parser->درون_pragma
	      || parser->error
	      || parser->نشانهها[0].type != CPP_PRAGMA);
  parser->آخرین_token_location = parser->نشانهها[0].location;
  إذا (parser->نشانهها != &parser->نشانهها_buf[0])
    parser->نشانهها++;
  وإلا إذا (parser->نشانهها_avail >= 2)
    {
      parser->نشانهها[0] = parser->نشانهها[1];
      إذا (parser->نشانهها_avail >= 3)
        {
          parser->نشانهها[1] = parser->نشانهها[2];
          إذا (parser->نشانهها_avail >= 4)
            parser->نشانهها[2] = parser->نشانهها[3];
        }
    }
  parser->نشانهها_avail--;
  parser->دیده_string_literal = خطأ;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

ساكن فراغ
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->درون_pragma);
  gcc_assert (parser->نشانهها_avail >= 1);
  gcc_assert (parser->نشانهها[0].type == CPP_PRAGMA);
  إذا (parser->نشانهها != &parser->نشانهها_buf[0])
    parser->نشانهها++;
  وإلا إذا (parser->نشانهها_avail >= 2)
    {
      parser->نشانهها[0] = parser->نشانهها[1];
      إذا (parser->نشانهها_avail >= 3)
	parser->نشانهها[1] = parser->نشانهها[2];
    }
  parser->نشانهها_avail--;
  parser->درون_pragma = درست;
}

/* Update the global input_location from TOKEN.  */
ساكن مضمن فراغ
c_parser_مجموعه_منبع_position_from_token (c_token *token)
{
  إذا (token->type != CPP_EOF)
    {
      درون_داد_location = token->location;
    }
}

/* Helper function for c_parser_error.
   Having peeked a token of kind TOK1_KIND that might signify
   a conflict marker, peek successor tokens to determine
   if we actually do have a conflict marker.
   Specifically, we consider a run of 7 '<', '=' or '>' characters
   at the start of a line as a conflict marker.
   These come through the lexer as three pairs and a single,
   e.g. three CPP_LSHIFT ("<<") and a CPP_LESS ('<').
   If it returns true, *OUT_LOC is written to with the location/range
   of the marker.  */

ساكن منطقي
c_parser_peek_conflict_marker (c_parser *parser, تعداد cpp_ttype tok1_نوع,
			       location_t *بیرون_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  إذا (token2->type != tok1_نوع)
    أرجع خطأ;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  إذا (token3->type != tok1_نوع)
    أرجع خطأ;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  إذا (token4->type != conflict_marker_get_final_tok_نوع (tok1_نوع))
    أرجع خطأ;

  /* It must be at the start of the line.  */
  location_t شروع_loc = c_parser_peek_token (parser)->location;
  إذا (LOCATION_ستونی (شروع_loc) != 1)
    أرجع خطأ;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t پایان_loc = get_پایان (token4->location);
  *بیرون_loc = make_location (شروع_loc, شروع_loc, پایان_loc);

  أرجع درست;
}

/* Issue a diagnostic of the form
      FILE:LINE: MESSAGE before TOKEN
   where TOKEN is the next token in the input stream of PARSER.
   MESSAGE (specified by the caller) is usually of the form "expected
   OTHER-TOKEN".

   Use RICHLOC as the location of the diagnostic.

   Do not issue a diagnostic if still recovering from an error.

   Return true iff an error was actually emitted.

   ??? This is taken from the C++ parser, but building up messages in
   this way is not i18n-friendly and some other approach should be
   used.  */

ساكن منطقي
c_parser_error_richloc (c_parser *parser, ثابت حرف *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  إذا (parser->error)
    أرجع خطأ;
  parser->error = درست;
  إذا (!gmsgid)
    أرجع خطأ;

  /* If this is actually a conflict marker, report it as such.  */
  إذا (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      إذا (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  أرجع درست;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_گروه d;
  name_hint h;
  إذا (parser->دیده_string_literal && token->type == CPP_NAME)
    {
      درخت name = token->مقدار;
      ثابت حرف *token_name = IDENTIFIER_اشاره_گر (name);
      ثابت حرف *سرآیند_hint
	= get_c_stdlib_سرآیند_for_string_macro_name (token_name);
      إذا (سرآیند_hint != عدم)
	h = name_hint (اشاره_تهی,
		       std::make_unique<suggest_missing_سرآیند>
			 (token->location,
			  token_name,
			  سرآیند_hint));
    }

  c_parse_error (gmsgid,
		 /* Because c_parse_error does not understand
		    CPP_KEYWORD, keywords are treated like
		    identifiers.  */
		 (token->type == CPP_KEYWORD ? CPP_NAME : token->type),
		 /* ??? The C parser does not save the cpp flags of a
		    token, we need to pass 0 here and we will not get
		    the source spelling of some tokens but rather the
		    canonical spelling.  */
		 token->مقدار, /*flags=*/0, richloc);
  أرجع درست;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

منطقي
c_parser_error (c_parser *parser, ثابت حرف *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_مجموعه_منبع_position_from_token (token);
  rich_location richloc (سطر_جدول, درون_داد_location);
  أرجع c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

قالب <نام_نوع traits_t>
صنف token_pair
{
 عام:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  منطقي require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    إذا (token)
      m_open_loc = token->location;

    أرجع c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  فراغ consume_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    gcc_assert (token->type == traits_t::open_token_type);
    m_open_loc = token->location;
    c_parser_consume_token (parser);
  }

  /* If the next token is the closing symbol for this pair, consume it
     and return true.
     Otherwise, issue an error, highlighting the location of the
     corresponding opening token, and return false.  */

  منطقي require_close (c_parser *parser) ثابت
  {
    أرجع c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  فراغ skip_until_یافت_close (c_parser *parser) ثابت
  {
    c_parser_skip_until_یافت (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 خاص:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

بنية matching_paren_traits
{
  ساكن ثابت تعداد cpp_ttype open_token_type = CPP_OPEN_PAREN;
  ساكن ثابت حرف * ثابت open_gmsgid;
  ساكن ثابت تعداد cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  ساكن ثابت حرف * ثابت close_gmsgid;
};

ثابت حرف * ثابت matching_paren_traits::open_gmsgid = "expected %<(%>";
ثابت حرف * ثابت matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

تعريفنوع token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

بنية matching_brace_traits
{
  ساكن ثابت تعداد cpp_ttype open_token_type = CPP_OPEN_BRACE;
  ساكن ثابت حرف * ثابت open_gmsgid;
  ساكن ثابت تعداد cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  ساكن ثابت حرف * ثابت close_gmsgid;
};

ثابت حرف * ثابت matching_brace_traits::open_gmsgid = "expected %<{%>";
ثابت حرف * ثابت matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

تعريفنوع token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

ساكن ثابت حرف *
get_matching_نماد (تعداد cpp_ttype type)
{
  بدل (type)
    {
    افتراضي:
      gcc_unreachable ();
    حالة CPP_CLOSE_PAREN:
      أرجع "(";
    حالة CPP_CLOSE_BRACE:
      أرجع "{";
    }
}

/* If the next token is of the indicated TYPE, consume it.  Otherwise,
   issue the error MSGID.  If MSGID is NULL then a message has already
   been produced and no message will be produced this time.  Returns
   true if found, false otherwise.

   If MATCHING_LOCATION is not UNKNOWN_LOCATION, then highlight it
   within any error as the location of an "opening" token matching
   the close token TYPE (e.g. the location of the '(' when TYPE is
   CPP_CLOSE_PAREN).

   If TYPE_IS_UNIQUE is true (the default) then msgid describes exactly
   one type (e.g. "expected %<)%>") and thus it may be reasonable to
   attempt to generate a fix-it hint for the problem.
   Otherwise msgid describes multiple token types (e.g.
   "expected %<;%>, %<,%> or %<)%>"), and thus we shouldn't attempt to
   generate a fix-it hint.  */

منطقي
c_parser_require (c_parser *parser,
		  تعداد cpp_ttype type,
		  ثابت حرف *msgid,
		  location_t matching_location,
		  منطقي type_is_unique)
{
  إذا (c_parser_بعدی_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      أرجع درست;
    }
  وإلا
    {
      location_t بعدی_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (بعدی_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      إذا (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->آخرین_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      منطقي added_matching_location = خطأ;
      إذا (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.جمع_کن_location_if_nearby (*global_dc, matching_location);

      إذا (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	إذا (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_نماد (type));

      أرجع خطأ;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

ساكن منطقي
c_parser_require_keyword (c_parser *parser,
			  تعداد rid keyword,
			  ثابت حرف *msgid)
{
  إذا (c_parser_بعدی_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      أرجع درست;
    }
  وإلا
    {
      c_parser_error (parser, msgid);
      أرجع خطأ;
    }
}

/* Like c_parser_require, except that tokens will be skipped until the
   desired token is found.  An error message is still produced if the
   next token is not as expected.  If MSGID is NULL then a message has
   already been produced and no message will be produced this
   time.

   If MATCHING_LOCATION is not UNKNOWN_LOCATION, then highlight it
   within any error as the location of an "opening" token matching
   the close token TYPE (e.g. the location of the '(' when TYPE is
   CPP_CLOSE_PAREN).  */

فراغ
c_parser_skip_until_یافت (c_parser *parser,
			   تعداد cpp_ttype type,
			   ثابت حرف *msgid,
			   location_t matching_location)
{
  بیعلامت nesting_عمق = 0;

  إذا (c_parser_require (parser, type, msgid, matching_location))
    {
      إذا (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->درون_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    {
	      parser->نشانهها = parser->درون_omp_attribute_pragma->save_نشانهها;
	      parser->نشانهها_avail
		= parser->درون_omp_attribute_pragma->save_نشانهها_avail;
	      parser->درون_omp_attribute_pragma = عدم;
	    }
	}
      أرجع;
    }

  /* Skip tokens until the desired token is found.  */
  طالما (درست)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      إذا (token->type == type && !nesting_عمق)
	{
	  c_parser_consume_token (parser);
	  إذا (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->درون_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      إذا (token->type == CPP_EOF)
		{
		  parser->نشانهها = parser->درون_omp_attribute_pragma->save_نشانهها;
		  parser->نشانهها_avail
		    = parser->درون_omp_attribute_pragma->save_نشانهها_avail;
		  parser->درون_omp_attribute_pragma = عدم;
		}
	    }
	  اكسر;
	}

      /* If we've run out of tokens, stop.  */
      إذا (token->type == CPP_EOF)
	أرجع;
      إذا (token->type == CPP_PRAGMA_EOL && parser->درون_pragma)
	أرجع;
      إذا (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_مربع)
	++nesting_عمق;
      وإلا إذا (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_مربع)
	{
	  إذا (nesting_عمق-- == 0)
	    اكسر;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = خطأ;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

ساكن فراغ
c_parser_skip_مقصد_انتها_از_parameter (c_parser *parser)
{
  بیعلامت nesting_عمق = 0;

  طالما (درست)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_عمق)
	اكسر;
      /* If we've run out of tokens, stop.  */
      إذا (token->type == CPP_EOF)
	أرجع;
      إذا (token->type == CPP_PRAGMA_EOL && parser->درون_pragma)
	أرجع;
      إذا (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_مربع)
	++nesting_عمق;
      وإلا إذا (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_مربع)
	{
	  إذا (nesting_عمق-- == 0)
	    اكسر;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = خطأ;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

ساكن منطقي
c_parser_skip_مقصد_closing_brace (c_parser *parser)
{
  بیعلامت nesting_عمق = 0;

  طالما (درست)
    {
      c_token *token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_PRAGMA_EOL:
	  إذا (!parser->درون_pragma)
	    اكسر;
	  /* FALLTHRU */
	حالة CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  أرجع خطأ;

	حالة CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  إذا (nesting_عمق-- == 0)
	    أرجع درست;
	  اكسر;

	حالة CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_عمق;
	  اكسر;

	افتراضي:
	  اكسر;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

ساكن فراغ
c_parser_skip_مقصد_pragma_eol (c_parser *parser, منطقي error_if_not_eol = درست)
{
  gcc_assert (parser->درون_pragma);
  parser->درون_pragma = خطأ;

  إذا (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  افعل
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      إذا (token_type == CPP_EOF)
	اكسر;
      c_parser_consume_token (parser);
    }
  طالما (token_type != CPP_PRAGMA_EOL);

  إذا (parser->درون_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_EOF)
	{
	  parser->نشانهها = parser->درون_omp_attribute_pragma->save_نشانهها;
	  parser->نشانهها_avail
	    = parser->درون_omp_attribute_pragma->save_نشانهها_avail;
	  parser->درون_omp_attribute_pragma = عدم;
	}
    }

  parser->error = خطأ;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
ساكن فراغ
c_parser_skip_مقصد_pragma_omp_انتها_declare_variant (c_parser *parser)
{
  لكل (صحيح عمق = 0; عمق >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_PRAGMA_EOL:
	  إذا (!parser->درون_pragma)
	    اكسر;
	  /* FALLTHRU */
	حالة CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  أرجع;

	حالة CPP_PRAGMA:
	  إذا ((token->pragma_نوع == PRAGMA_OMP_BEGIN
	       || token->pragma_نوع == PRAGMA_OMP_انتها)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      درخت id1 = c_parser_peek_nth_token (parser, 2)->مقدار;
	      درخت id2 = c_parser_peek_nth_token (parser, 3)->مقدار;
	      إذا (strcmp (IDENTIFIER_اشاره_گر (id1), "declare") == 0
		  && strcmp (IDENTIFIER_اشاره_گر (id2), "variant") == 0)
		{
		  إذا (token->pragma_نوع == PRAGMA_OMP_BEGIN)
		    عمق++;
		  وإلا
		    عمق--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  استمر;

	افتراضي:
	  اكسر;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

ساكن فراغ
c_parser_skip_مقصد_انتها_از_بلوک_or_statement (c_parser *parser,
					    منطقي metadirective_p = خطأ)
{
  بیعلامت nesting_عمق = 0;
  صحيح bracket_عمق = 0;
  منطقي save_error = parser->error;

  طالما (درست)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_EOF:
	  أرجع;

	حالة CPP_PRAGMA_EOL:
	  إذا (parser->درون_pragma)
	    أرجع;
	  اكسر;

	حالة CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  إذا (!nesting_عمق && (!metadirective_p || bracket_عمق <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      اذهب پایانیافته;
	    }
	  اكسر;

	حالة CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  إذا ((nesting_عمق == 0 || --nesting_عمق == 0)
	      && (!metadirective_p || bracket_عمق <= 0))
	    {
	      c_parser_consume_token (parser);
	      اذهب پایانیافته;
	    }
	  اكسر;

	حالة CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_عمق;
	  اكسر;

	حالة CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  إذا (metadirective_p && nesting_عمق == 0)
	    ++bracket_عمق;
	  اكسر;

	حالة CPP_CLOSE_PAREN:
	  إذا (metadirective_p && nesting_عمق == 0)
	    --bracket_عمق;
	  اكسر;

	حالة CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  parser->error = save_error;
	  استمر;

	افتراضي:
	  اكسر;
	}

      c_parser_consume_token (parser);
    }

 پایانیافته:
  parser->error = خطأ;
}

/* CPP's options (initialized by c-opts.cc).  */
خارجي cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

ساكن مضمن صحيح
disable_extension_diagnostics (فراغ)
{
  صحيح ret = (pedantic
	     | (warn_اشاره_گر_arith << 1)
	     | (warn_traditional << 2)
	     | (flag_iso << 3)
	     | (warn_long_long << 4)
	     | (warn_cxx_compat << 5)
	     | (warn_overlength_رشتهها << 6)
	     /* warn_c90_c99_compat has three states: -1/0/1, so we must
		play tricks to properly restore it.  */
	     | ((warn_c90_c99_compat == 1) << 7)
	     | ((warn_c90_c99_compat == -1) << 8)
	     /* Similarly for warn_c99_c11_compat.  */
	     | ((warn_c99_c11_compat == 1) << 9)
	     | ((warn_c99_c11_compat == -1) << 10)
	     /* Similarly for warn_c11_c23_compat.  */
	     | ((warn_c11_c23_compat == 1) << 11)
	     | ((warn_c11_c23_compat == -1) << 12)
	     /* Similarly for warn_c23_c2y_compat.  */
	     | ((warn_c23_c2y_compat == 1) << 13)
	     | ((warn_c23_c2y_compat == -1) << 14)
	     );
  cpp_opts->cpp_pedantic = pedantic = 0;
  warn_اشاره_گر_arith = 0;
  cpp_opts->cpp_warn_traditional = warn_traditional = 0;
  flag_iso = 0;
  cpp_opts->cpp_warn_long_long = warn_long_long = 0;
  warn_cxx_compat = 0;
  warn_overlength_رشتهها = 0;
  warn_c90_c99_compat = 0;
  warn_c99_c11_compat = 0;
  warn_c11_c23_compat = 0;
  warn_c23_c2y_compat = 0;
  أرجع ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

ساكن مضمن فراغ
restore_extension_diagnostics (صحيح flags)
{
  cpp_opts->cpp_pedantic = pedantic = flags & 1;
  warn_اشاره_گر_arith = (flags >> 1) & 1;
  cpp_opts->cpp_warn_traditional = warn_traditional = (flags >> 2) & 1;
  flag_iso = (flags >> 3) & 1;
  cpp_opts->cpp_warn_long_long = warn_long_long = (flags >> 4) & 1;
  warn_cxx_compat = (flags >> 5) & 1;
  warn_overlength_رشتهها = (flags >> 6) & 1;
  /* See above for why is this needed.  */
  warn_c90_c99_compat = (flags >> 7) & 1 ? 1 : ((flags >> 8) & 1 ? -1 : 0);
  warn_c99_c11_compat = (flags >> 9) & 1 ? 1 : ((flags >> 10) & 1 ? -1 : 0);
  warn_c11_c23_compat = (flags >> 11) & 1 ? 1 : ((flags >> 12) & 1 ? -1 : 0);
  warn_c23_c2y_compat = (flags >> 13) & 1 ? 1 : ((flags >> 14) & 1 ? -1 : 0);
}

/* Helper data structure for parsing #pragma acc routine.  */
بنية oacc_routine_داده {
  منطقي error_دیده; /* Set if error has been reported.  */
  منطقي fndecl_دیده; /* Set if one fn decl/definition has been seen already.  */
  درخت clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
ساكن درخت objc_foreach_break_label, objc_foreach_continue_label;

/* Used for parsing OMP for loops.

   Some notes on flags used for context:
   parser->omp_for_parse_state is non-null anywhere inside the OMP FOR
   construct, except for the final-loop-body.
   The want_nested_loop flag is true if inside a {} sequence where
   a loop-nest (or another {} sequence containing a loop-nest) is expected,
   but has not yet been seen.  It's false when parsing intervening code
   statements or their substatements that cannot contain a loop-nest.
   The in_intervening_code flag is true when parsing any intervening code,
   including substatements, and whether or not want_nested_loop is true.

   And, about error handling:
   The saw_intervening_code flag is set if the loop is not perfectly
   nested, even in the usual case where this is not an error.
   perfect_nesting_fail is set if an error has been diagnosed because an
   imperfectly-nested loop was found where a perfectly-nested one is
   required (we diagnose this only once).
   fail is set if any kind of structural error in the loop nest
   has been found and diagnosed.
  */
بنية omp_for_parse_داده {
  تعداد درخت_کد_2 کد;
  درخت declv, condv, incrv, initv;
  درخت pre_body;
  درخت bindings;
  صحيح شمار;	/* Expected nesting depth.  */
  صحيح عمق;	/* Current nesting depth.  */
  location_t for_loc;
  منطقي ordered : 1;
  منطقي inscan : 1;
  منطقي want_nested_loop : 1;
  منطقي درون_intervening_کد : 1;
  منطقي saw_intervening_کد: 1;
  منطقي perfect_nesting_fail : 1;
  منطقي fail : 1;
};

بنية attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  منطقي musttail_p;

  فراغ reset () { musttail_p = خطأ; }
};

ساكن منطقي c_parser_nth_token_starts_std_صفات (c_parser *,
						      بیعلامت صحيح);
ساكن درخت c_parser_std_attribute_specifier_sequence (c_parser *);
ساكن فراغ c_parser_external_declaration (c_parser *);
ساكن فراغ c_parser_asm_definition (c_parser *);
ساكن درخت c_parser_declaration_or_fndef (c_parser *, منطقي, منطقي, منطقي,
					   منطقي, منطقي, منطقي, درخت * = عدم,
					   vec<c_token> * = عدم,
					   منطقي have_attrs = خطأ,
					   درخت attrs = عدم,
					   بنية oacc_routine_داده * = عدم,
					   منطقي * = عدم);
ساكن منطقي c_parser_handle_statement_omp_صفات (c_parser *, درخت &,
						      منطقي *);
ساكن فراغ c_parser_static_assert_declaration_no_semi (c_parser *);
ساكن فراغ c_parser_static_assert_declaration (c_parser *);
ساكن بنية c_typespec c_parser_enum_specifier (c_parser *);
ساكن بنية c_typespec c_parser_struct_or_union_specifier (c_parser *);
ساكن درخت c_parser_struct_declaration (c_parser *, درخت *);
ساكن بنية c_typespec c_parser_typeof_specifier (c_parser *);
ساكن درخت c_parser_alignas_specifier (c_parser *);
ساكن بنية c_declarator *c_parser_مستقیم_declarator (c_parser *, منطقي,
							c_dtr_syn, منطقي *);
ساكن بنية c_declarator *c_parser_مستقیم_declarator_inner (c_parser *,
							      منطقي,
							      بنية c_declarator *);
ساكن بنية c_arg_info *c_parser_parms_declarator (c_parser *, منطقي, درخت,
						     منطقي);
ساكن بنية c_arg_info *c_parser_parms_list_declarator (c_parser *, درخت,
							  درخت, منطقي);
ساكن بنية c_parm *c_parser_parameter_declaration (c_parser *, درخت, منطقي);
ساكن درخت c_parser_asm_string_literal (c_parser *);
ساكن درخت c_parser_simple_asm_عبارت (c_parser *);
ساكن درخت c_parser_gnu_صفات (c_parser *);
ساكن بنية c_عبارت c_parser_initializer (c_parser *, درخت);
ساكن بنية c_عبارت c_parser_braced_init (c_parser *, درخت, منطقي,
					   بنية obstack *, منطقي);
ساكن فراغ c_parser_initelt (c_parser *, بنية obstack *);
ساكن فراغ c_parser_initval (c_parser *, بنية c_عبارت *,
			      بنية obstack *);
ساكن درخت c_parser_compound_statement (c_parser *, location_t * = عدم);
ساكن location_t c_parser_compound_statement_nostart (c_parser *);
ساكن فراغ c_parser_label (c_parser *, درخت);
ساكن فراغ c_parser_statement (c_parser *, منطقي *, location_t * = عدم);
ساكن فراغ c_parser_statement_after_labels (c_parser *, منطقي *, درخت,
					     vec<درخت> * = عدم,
					     attr_state = {});
ساكن درخت c_parser_c99_بلوک_statement (c_parser *, منطقي *,
					  location_t * = عدم);
ساكن فراغ c_parser_if_statement (c_parser *, منطقي *, vec<درخت> *);
ساكن فراغ c_parser_switch_statement (c_parser *, منطقي *, درخت);
ساكن فراغ c_parser_while_statement (c_parser *, منطقي, بیعلامت کوتاه, منطقي,
				      منطقي *, درخت);
ساكن فراغ c_parser_do_statement (c_parser *, منطقي, بیعلامت کوتاه, منطقي,
				   درخت);
ساكن فراغ c_parser_for_statement (c_parser *, منطقي, بیعلامت کوتاه, منطقي,
				    منطقي *, درخت);
ساكن درخت c_parser_asm_statement (c_parser *);
ساكن درخت c_parser_asm_operands (c_parser *);
ساكن درخت c_parser_asm_goto_operands (c_parser *);
ساكن درخت c_parser_asm_clobbers (c_parser *);
ساكن بنية c_عبارت c_parser_عبارت_no_commas (c_parser *, بنية c_عبارت *,
					      درخت = NULL_درخت);
ساكن بنية c_عبارت c_parser_conditional_عبارت (c_parser *,
						      بنية c_عبارت *, درخت);
ساكن بنية c_عبارت c_parser_دودویی_عبارت (c_parser *, بنية c_عبارت *,
						 درخت);
ساكن بنية c_عبارت c_parser_cast_عبارت (c_parser *, بنية c_عبارت *);
ساكن بنية c_عبارت c_parser_unary_عبارت (c_parser *);
ساكن بنية c_عبارت c_parser_sizeof_or_countof_عبارت (c_parser *,
							    تعداد rid);
ساكن بنية c_عبارت c_parser_alignof_عبارت (c_parser *);
ساكن بنية c_عبارت c_parser_maxof_or_minof_عبارت (c_parser *, تعداد rid);
ساكن بنية c_عبارت c_parser_postfix_عبارت (c_parser *);
ساكن بنية c_عبارت c_parser_postfix_عبارت_after_paren_type (c_parser *,
								   بنية c_declspecs *,
								   بنية c_type_name *,
								   location_t);
ساكن بنية c_عبارت c_parser_postfix_عبارت_after_primary (c_parser *,
								location_t loc,
								بنية c_عبارت);
ساكن درخت c_parser_transaction (c_parser *, تعداد rid);
ساكن بنية c_عبارت c_parser_transaction_عبارت (c_parser *, تعداد rid);
ساكن درخت c_parser_transaction_cancel (c_parser *);
ساكن بنية c_عبارت c_parser_عبارت (c_parser *);
ساكن بنية c_عبارت c_parser_عبارت_conv (c_parser *);
ساكن vec<درخت, va_gc> *c_parser_عبارت_list (c_parser *, منطقي, منطقي,
					     vec<درخت, va_gc> **, location_t *,
					     درخت *, vec<location_t> *,
					     بیعلامت صحيح * = عدم);
ساكن بنية c_عبارت c_parser_has_attribute_عبارت (c_parser *);

ساكن فراغ c_parser_oacc_declare (c_parser *);
ساكن فراغ c_parser_oacc_enter_exit_داده (c_parser *, منطقي);
ساكن فراغ c_parser_oacc_update (c_parser *);
ساكن فراغ c_parser_omp_construct (c_parser *, منطقي *);
ساكن فراغ c_parser_omp_groupprivate (c_parser *);
ساكن فراغ c_parser_omp_threadprivate (c_parser *);
ساكن فراغ c_parser_omp_barrier (c_parser *);
ساكن فراغ c_parser_omp_depobj (c_parser *);
ساكن فراغ c_parser_omp_flush (c_parser *);
ساكن منطقي c_parser_omp_بعدی_نشانهها_can_be_canon_loop (c_parser *,
							تعداد درخت_کد_2, منطقي);
ساكن درخت c_parser_omp_loop_nest (c_parser *, منطقي *);
ساكن درخت c_parser_omp_for_loop (location_t, c_parser *, تعداد درخت_کد_2,
				   درخت, درخت *, منطقي *);
ساكن فراغ c_parser_omp_taskwait (c_parser *);
ساكن فراغ c_parser_omp_taskyield (c_parser *);
ساكن فراغ c_parser_omp_cancel (c_parser *);
ساكن فراغ c_parser_omp_nothing (c_parser *);
ساكن فراغ c_parser_omp_metadirective (c_parser *, منطقي *);

تعداد pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
ساكن منطقي c_parser_pragma (c_parser *, تعداد pragma_context, منطقي *, درخت);
ساكن منطقي c_parser_omp_cancellation_نقطه (c_parser *, تعداد pragma_context);
ساكن منطقي c_parser_omp_هدف (c_parser *, تعداد pragma_context, منطقي *);
ساكن فراغ c_parser_omp_begin (c_parser *);
ساكن فراغ c_parser_omp_انتها (c_parser *);
ساكن منطقي c_parser_omp_declare (c_parser *, تعداد pragma_context);
ساكن فراغ c_parser_omp_requires (c_parser *);
ساكن منطقي c_parser_omp_error (c_parser *, تعداد pragma_context);
ساكن فراغ c_parser_omp_assumption_clauses (c_parser *, منطقي);
ساكن فراغ c_parser_omp_allocate (c_parser *);
ساكن فراغ c_parser_omp_assumes (c_parser *);
ساكن منطقي c_parser_omp_ordered (c_parser *, تعداد pragma_context, منطقي *);
ساكن درخت c_parser_omp_dispatch (location_t, c_parser *);
ساكن فراغ c_parser_omp_interop (c_parser *);
ساكن فراغ c_parser_oacc_routine (c_parser *, تعداد pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
ساكن فراغ c_parser_objc_class_definition (c_parser *, درخت);
ساكن فراغ c_parser_objc_class_instance_variables (c_parser *);
ساكن فراغ c_parser_objc_class_declaration (c_parser *);
ساكن فراغ c_parser_objc_alias_declaration (c_parser *);
ساكن فراغ c_parser_objc_protocol_definition (c_parser *, درخت);
ساكن منطقي c_parser_objc_روش_type (c_parser *);
ساكن فراغ c_parser_objc_روش_definition (c_parser *);
ساكن فراغ c_parser_objc_methodprotolist (c_parser *);
ساكن فراغ c_parser_objc_methodproto (c_parser *);
ساكن درخت c_parser_objc_روش_decl (c_parser *, منطقي, درخت *, درخت *);
ساكن درخت c_parser_objc_type_name (c_parser *);
ساكن درخت c_parser_objc_protocol_refs (c_parser *);
ساكن فراغ c_parser_objc_try_catch_finally_statement (c_parser *);
ساكن فراغ c_parser_objc_synchronized_statement (c_parser *);
ساكن درخت c_parser_objc_selector (c_parser *);
ساكن درخت c_parser_objc_selector_arg (c_parser *);
ساكن درخت c_parser_objc_receiver (c_parser *);
ساكن درخت c_parser_objc_پیام_آرگومانها (c_parser *);
ساكن درخت c_parser_objc_keywordexpr (c_parser *);
ساكن فراغ c_parser_objc_at_property_declaration (c_parser *);
ساكن فراغ c_parser_objc_at_synthesize_declaration (c_parser *);
ساكن فراغ c_parser_objc_at_dynamic_declaration (c_parser *);
ساكن منطقي c_parser_objc_diagnose_bad_element_پیشوند
  (c_parser *, بنية c_declspecs *);
ساكن location_t c_parser_parse_rtl_body (c_parser *, حرف *);
ساكن درخت c_parser_handle_musttail (c_parser *, درخت, attr_state &);

#إذا ENABLE_ANALYZER

نطاق ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

صنف c_translation_unit : عام translation_unit
{
عام:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  درخت lookup_constant_by_id (درخت id) ثابت final override
  {
    /* Consider decls.  */
    إذا (درخت decl = lookup_name (id))
      إذا (درخت_کد (decl) == CONST_DECL)
	إذا (درخت مقدار = DECL_INITIAL (decl))
	  إذا (درخت_کد (مقدار) == INTEGER_CST)
	    أرجع مقدار;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    إذا (cpp_macro_p (hashnode))
      إذا (درخت مقدار = consider_macro (hashnode->مقدار.macro))
	أرجع مقدار;

    أرجع NULL_درخت;
  }

  درخت
  lookup_type_by_id (درخت id) ثابت final override
  {
    إذا (درخت type_decl = lookup_name (id))
	إذا (درخت_کد (type_decl) == TYPE_DECL)
	  {
	    درخت رکورد_type = درخت_TYPE (type_decl);
	    إذا (درخت_کد (رکورد_type) == رکورد_TYPE)
	      أرجع رکورد_type;
	  }

    أرجع NULL_درخت;
  }

  درخت
  lookup_global_var_by_id (درخت id) ثابت final override
  {
    إذا (درخت var_decl = lookup_name (id))
      إذا (درخت_کد (var_decl) == VAR_DECL)
				أرجع var_decl;

    أرجع NULL_درخت;
  }

خاص:
  /* Attempt to get an INTEGER_CST from MACRO.
     Only handle the simplest cases: where MACRO's definition is a single
     token containing a number, by lexing the number again.
     This will handle e.g.
       #define NAME 42
     and other bases but not negative numbers, parentheses or e.g.
       #define NAME 1 << 7
     as doing so would require a parser.
     Also handle the case where MACRO's definition is a single identifier
     that is itself a macro name (e.g. "#define O_CREAT _FCREAT"), by
     following the chain of aliases.  */
  درخت consider_macro (cpp_macro *macro, صحيح عمق = 0) ثابت
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (عمق >= 0);

    إذا (macro->paramc > 0)
      أرجع NULL_درخت;
    إذا (macro->نوع != cmk_macro)
      أرجع NULL_درخت;
    إذا (macro->شمار != 1)
      أرجع NULL_درخت;
    ثابت cpp_token &tok = macro->نمایی_تابع.نشانهها[0];
    إذا (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	إذا (عمق >= param_analyzer_max_macro_alias_عمق)
	  أرجع NULL_درخت;

	cpp_hashnode *alias = tok.val.گره.گره;
	إذا (cpp_macro_p (alias))
	  أرجع consider_macro (alias->مقدار.macro, عمق + 1);

	/* Not a simple alias.  */
	أرجع NULL_درخت;
      }
    وإلا إذا (tok.type != CPP_عدد)
      أرجع NULL_درخت;

    cpp_reader *old_parse_درون = parse_درون;
    parse_درون = cpp_create_reader (CLK_GNUC89, عدم, سطر_جدول);

    pretty_printer pp;
    pp_string (&pp, (ثابت حرف *) tok.val.str.متن);
    pp_newline (&pp);
    cpp_افزودن_میانگیر (parse_درون,
		     (ثابت بیعلامت حرف *) pp_formatted_متن (&pp),
		     طول_رشته (pp_formatted_متن (&pp)),
		     0);

    درخت مقدار;
    location_t loc;
    بیعلامت حرف cpp_flags;
    c_lex_with_flags (&مقدار, &loc, &cpp_flags, 0);

    cpp_destroy (parse_درون);
    parse_درون = old_parse_درون;

    إذا (مقدار && درخت_کد (مقدار) == INTEGER_CST)
      أرجع مقدار;

    أرجع NULL_درخت;
  }
};

} // namespace ana

#پایان_اگر /* #if ENABLE_ANALYZER */

/* Parse a translation unit (C90 6.7, C99 6.9, C11 6.9).

   translation-unit:
     external-declarations

   external-declarations:
     external-declaration
     external-declarations external-declaration

   GNU extensions:

   translation-unit:
خالی
*/

ساكن فراغ
c_parser_translation_unit (c_parser *parser)
{
  إذا (c_parser_بعدی_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  وإلا
    {
      فراغ *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (خطأ);
      افعل
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      طالما (c_parser_بعدی_token_is_not (parser, CPP_EOF));
    }

  بیعلامت صحيح i;
  درخت decl;
  FOR_EACH_VEC_ELT (incomplete_رکورد_decls, i, decl)
    إذا (DECL_اندازه (decl) == NULL_درخت && درخت_TYPE (decl) != error_mark_گره)
      error ("storage size of %q+D isn%'t known", decl);

  إذا (vec_امن_درازی (current_omp_declare_هدف_attribute))
    {
      c_omp_declare_هدف_attr
	a = current_omp_declare_هدف_attribute->برداشت ();
      إذا (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_امن_truncate (current_omp_declare_هدف_attribute, 0);
    }
  إذا (vec_امن_درازی (current_omp_begin_assumes))
    {
      إذا (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_امن_truncate (current_omp_begin_assumes, 0);
    }
  إذا (vec_امن_درازی (current_omp_declare_variant_attribute))
    {
      إذا (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_امن_truncate (current_omp_declare_variant_attribute, 0);
    }
  إذا (vec_امن_درازی (omp_begin_declare_variant_map))
    {
      بیعلامت صحيح i;
      omp_begin_declare_variant_map_مدخل *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_پایان_variant_function (e->variant, e->id, e->ctx);
      vec_امن_truncate (omp_begin_declare_variant_map, 0);
    }

#إذا ENABLE_ANALYZER
  إذا (flag_analyzer)
    {
      ana::c_translation_unit tu;
      ana::on_پایان_translation_unit (tu);
    }
#پایان_اگر
}

/* Parse an external declaration (C90 6.7, C99 6.9, C11 6.9).

   external-declaration:
     function-definition
     declaration

   GNU extensions:

   external-declaration:
     asm-definition
     ;
     __extension__ external-declaration

   Objective-C:

   external-declaration:
     objc-class-definition
     objc-class-declaration
     objc-alias-declaration
     objc-protocol-definition
     objc-method-definition
     @end
*/

ساكن فراغ
c_parser_external_declaration (c_parser *parser)
{
  صحيح ext;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  اكسر;
	حالة RID_ASM:
	  c_parser_asm_definition (parser);
	  اكسر;
	حالة RID_AT_INTERFACE:
	حالة RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_درخت);
	  اكسر;
	حالة RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  اكسر;
	حالة RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  اكسر;
	حالة RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_درخت);
	  اكسر;
	حالة RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  اكسر;
	حالة RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  اكسر;
	حالة RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  اكسر;
	حالة RID_AT_انتها:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_پایان_implementation ();
	  اكسر;
	افتراضي:
	  اذهب decl_or_fndef;
	}
      اكسر;
    حالة CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (درست);
      c_parser_pragma (parser, pragma_external, عدم, NULL_درخت);
      mark_valid_location_for_stdc_pragma (خطأ);
      اكسر;
    حالة CPP_PLUS:
    حالة CPP_MINUS:
      إذا (c_dialect_objc ())
	{
	  c_parser_objc_روش_definition (parser);
	  اكسر;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    افتراضي:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, درست, درست, درست, خطأ, درست,
				     خطأ);
      اكسر;
    }
}

ساكن فراغ c_parser_handle_directive_omp_صفات (درخت &, vec<c_token> *&,
						      vec<c_token> *);
ساكن فراغ c_پایان_omp_declare_simd (c_parser *, درخت, درخت, vec<c_token> *);
ساكن فراغ c_پایان_oacc_routine (بنية oacc_routine_داده *, درخت, منطقي);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

ساكن فراغ
جمع_کن_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  إذا (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    أرجع;

  درخت stmt = build0 (DEBUG_BEGIN_STMT, void_type_گره);
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

ساكن درخت
handle_assume_attribute (location_t اینجا, درخت attrs, منطقي nested)
{
  إذا (nested)
    لكل (درخت attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", درخت_CHAIN (attr)))
      {
	درخت آرگومانها = درخت_مقدار (attr);
	صحيح nargs = list_درازی (آرگومانها);
	إذا (nargs != 1)
	  {
	    error_at (اینجا, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (اینجا, "expected %i, found %i", 1, nargs);
	  }
	وإلا
	  {
	    درخت arg = درخت_مقدار (آرگومانها);
	    arg = c_objc_common_truthvalue_conversion (اینجا, arg);
	    arg = c_fully_fold (arg, خطأ, عدم);
	    إذا (arg != error_mark_گره)
	      {
		درخت fn = build_call_عبارت_داخلی_loc (اینجا, IFN_ASSUME,
							void_type_گره, 1,
							arg);
		جمع_کن_stmt (fn);
	      }
	  }
      }
  وإلا
    pedwarn (اینجا, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  أرجع remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

ساكن فراغ
c_parser_maybe_reclassify_token (c_parser *parser)
{
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      إذا (token->id_نوع == C_ID_ID || token->id_نوع == C_ID_TYPENAME)
	{
	  درخت decl = lookup_name (token->مقدار);

	  token->id_نوع = C_ID_ID;
	  إذا (decl)
	    {
	      إذا (درخت_کد (decl) == TYPE_DECL)
		token->id_نوع = C_ID_TYPENAME;
	    }
	  وإلا إذا (c_dialect_objc ())
	    {
	      درخت objc_interface_decl = objc_is_class_name (token->مقدار);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      إذا (objc_interface_decl)
		{
		  token->مقدار = objc_interface_decl;
		  token->id_نوع = C_ID_CLASSNAME;
		}
	    }
	}
    }
}

/* Parse a declaration or function definition (C90 6.5, 6.7.1, C99
   6.7, 6.9.1, C11 6.7, 6.9.1).  If FNDEF_OK is true, a function definition
   is accepted; otherwise (old-style parameter declarations) only other
   declarations are accepted.  If STATIC_ASSERT_OK is true, a static
   assertion is accepted; otherwise (old-style parameter declarations)
   it is not.  If NESTED is true, we are inside a function or parsing
   old-style parameter declarations; any functions encountered are
   nested functions and declaration specifiers are required; otherwise
   we are at top level and functions are normal functions and
   declaration specifiers may be optional.  If EMPTY_OK is true, empty
   declarations are OK (subject to all other constraints); otherwise
   (old-style parameter declarations) they are diagnosed.  If
   START_ATTR_OK is true, the declaration specifiers may start with
   attributes (GNU or standard); otherwise they may not.
   OBJC_FOREACH_OBJECT_DECLARATION can be used to get back the parsed
   declaration when parsing an Objective-C foreach statement.
   FALLTHRU_ATTR_P is used to signal whether this function parsed
   "__attribute__((fallthrough));".  ATTRS are any standard attributes
   parsed in the caller (in contexts where such attributes had to be
   parsed to determine whether what follows is a declaration or a
   statement); HAVE_ATTRS says whether there were any such attributes
   (even empty).  If SIMPLE_OK, the construct can be a simple-declaration;
   in that case, the ';' is not consumed (left to the caller so that it
   can figure out if there was a simple-declaration or not), there must
   be an initializer, and only one object may be declared.  When SIMPLE_OK
   is true we are called from c_parser_selection_header.

   Returns the resulting declaration, if there was any with an initializer.

   declaration:
     declaration-specifiers init-declarator-list[opt] ;
     static_assert-declaration

   function-definition:
     declaration-specifiers[opt] declarator declaration-list[opt]
       compound-statement

   declaration-list:
     declaration
     declaration-list declaration

   init-declarator-list:
     init-declarator
     init-declarator-list , init-declarator

   init-declarator:
     declarator simple-asm-expr[opt] gnu-attributes[opt]
     declarator simple-asm-expr[opt] gnu-attributes[opt] = initializer

   simple-declaration:
     attribute-specifier-sequence[opt] declaration-specifiers declarator
       = initializer

   GNU extensions:

   nested-function-definition:
     declaration-specifiers declarator declaration-list[opt]
       compound-statement

   attribute ;

   Objective-C:
     gnu-attributes objc-class-definition
     gnu-attributes objc-category-definition
     gnu-attributes objc-protocol-definition

   The simple-asm-expr and gnu-attributes are GNU extensions.

   This function does not handle __extension__; that is handled in its
   callers.  ??? Following the old parser, __extension__ may start
   external declarations, declarations in functions and declarations
   at the start of "for" loops, but not old-style parameter
   declarations.

   C99 requires declaration specifiers in a function definition; the
   absence is diagnosed through the diagnosis of implicit int.  In GNU
   C we also allow but diagnose declarations without declaration
   specifiers, but only at top level (elsewhere they conflict with
   other syntax).

   In Objective-C, declarations of the looping variable in a foreach
   statement are exceptionally terminated by 'in' (for example, 'for
   (NSObject *object in array) { ... }').

   OpenMP:

   declaration:
     threadprivate-directive

   GIMPLE:

   gimple-function-definition:
     declaration-specifiers[opt] __GIMPLE (gimple-or-rtl-pass-list) declarator
       declaration-list[opt] compound-statement

   rtl-function-definition:
     declaration-specifiers[opt] __RTL (gimple-or-rtl-pass-list) declarator
       declaration-list[opt] compound-statement  */

ساكن درخت
c_parser_declaration_or_fndef (c_parser *parser, منطقي fndef_ok,
			       منطقي static_assert_ok, منطقي خالی_ok,
			       منطقي nested, منطقي شروع_attr_ok,
			       منطقي simple_ok,
			       درخت *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       منطقي have_attrs /* = false */,
			       درخت attrs /* = NULL_TREE */,
			       بنية oacc_routine_داده *oacc_routine_داده
			       /* = NULL */,
			       منطقي *fallthru_attr_p /* = NULL */)
{
  بنية c_declspecs *specs;
  درخت پیشوند_attrs;
  درخت all_پیشوند_attrs;
  منطقي diagnosed_no_specs = خطأ;
  location_t اینجا = c_parser_peek_token (parser)->location;
  درخت نتیجه = NULL_درخت;

  جمع_کن_debug_begin_stmt (c_parser_peek_token (parser)->location);

  إذا (static_assert_ok
      && c_parser_بعدی_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      أرجع نتیجه;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  إذا (have_attrs)
    {
      declspecs_جمع_کن_attrs (اینجا, specs, attrs);
      specs->non_std_attrs_دیده_p = خطأ;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  إذا (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_نوع == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->مقدار)))
    {
      درخت name = c_parser_peek_token (parser)->مقدار;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (اینجا);
      إذا (برچسب_exists_p (رکورد_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.جمع_کن_fixit_درج_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      وإلا إذا (برچسب_exists_p (UNION_TYPE, name))
	{
	  richloc.جمع_کن_fixit_درج_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      وإلا إذا (برچسب_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.جمع_کن_fixit_درج_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      وإلا
	{
	  auto_diagnostic_گروه d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      اینجا);
	  إذا (ثابت حرف *suggestion = hint.suggestion ())
	    {
	      richloc.جمع_کن_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  وإلا
	    error_at (اینجا, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->مقدار = error_mark_گره;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  إذا (c_parser_nth_token_starts_std_صفات (parser, 1))
    have_attrs = درست;

  c_parser_declspecs (parser, specs, درست, درست, شروع_attr_ok,
		      درست, درست, شروع_attr_ok, درست, cla_nonabstract_decl);
  إذا (parser->error)
    {
      c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
      أرجع نتیجه;
    }
  إذا (nested && !specs->declspecs_دیده_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
      أرجع نتیجه;
    }

  پایان_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  إذا (specs->typespec_نوع == ctsk_tagdef)
    verify_counted_by_for_بالاترین_anonymous_type (specs->type);

  منطقي gnu_auto_type_p = specs->typespec_کلمه == cts_auto_type;
  منطقي std_auto_type_p = specs->c23_auto_p;
  منطقي any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ثابت حرف *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  إذا (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      بدل (specs->typespec_نوع)
	{
	حالة ctsk_tagfirstref:
	حالة ctsk_tagfirstref_attrs:
	  error_at (اینجا, "%qT declared in underspecified object declaration",
		    specs->type);
	  اكسر;

	حالة ctsk_tagdef:
	  error_at (اینجا, "%qT defined in underspecified object declaration",
		    specs->type);
	  اكسر;

	افتراضي:
	  اكسر;
	}
    }

  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      منطقي handled_assume = خطأ;
      إذا (specs->attrs
	  && !nested
	  && specs->typespec_نوع == ctsk_none
	  && c_parser_handle_statement_omp_صفات (parser, specs->attrs,
						       عدم))
	{
	  إذا (specs->attrs)
	    c_warn_استفادهنشده_صفات (specs->attrs);
	  طالما (parser->درون_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_بعدی_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, عدم, NULL_درخت);
	    }
	  c_parser_consume_token (parser);
	  أرجع نتیجه;
	}
      إذا (specs->typespec_نوع == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = درست;
	  specs->attrs
	    = handle_assume_attribute (اینجا, specs->attrs, nested);
	}
      إذا (any_auto_type_p)
	error_at (اینجا, "%qs in empty declaration", auto_type_keyword);
      وإلا إذا (specs->typespec_نوع == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  إذا (fallthru_attr_p != عدم)
	    *fallthru_attr_p = درست;
	  إذا (nested)
	    {
	      درخت fn = build_call_عبارت_داخلی_loc (اینجا, IFN_FALLTHROUGH,
						      void_type_گره, 0);
	      جمع_کن_stmt (fn);
	    }
	  وإلا
	    pedwarn (اینجا, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      وإلا إذا (خالی_ok
	       && !(have_attrs && specs->non_std_attrs_دیده_p)
	       && !handled_assume)
	shadow_برچسب (specs);
      وإلا
	{
	  shadow_برچسب_warned (specs, 1);
	  إذا (!handled_assume)
	    pedwarn (اینجا, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      إذا (specs->عبارت)
	جمع_کن_stmt (fold_convert (void_type_گره, specs->عبارت));
      c_parser_consume_token (parser);
      إذا (oacc_routine_داده)
	c_پایان_oacc_routine (oacc_routine_داده, NULL_درخت, خطأ);
      أرجع نتیجه;
    }
  وإلا إذا (specs->typespec_نوع == ctsk_none
	   && nested
	   /* Only parse __attribute__((musttail)) when called from
	      c_parser_compound_statement_nostart.  This certainly isn't
	      a declaration in that case, but we don't do tentative parsing
	      of GNU attributes right now.  */
	   && fallthru_attr_p
	   && c_parser_بعدی_token_is_keyword (parser, RID_RETURN))
    {
      attr_state astate = {};
      specs->attrs = c_parser_handle_musttail (parser, specs->attrs, astate);
      إذا (astate.musttail_p)
	{
	  إذا (specs->attrs)
	    {
	      auto_urlify_صفات sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, عدم, NULL_درخت, عدم,
					   astate);
	  أرجع نتیجه;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  إذا (خالی_ok
      && specs->typespec_نوع == ctsk_tagdef
      && c_parser_بعدی_token_starts_declspecs (parser)
      && !c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = خطأ;
      shadow_برچسب_warned (specs, 1);
      أرجع نتیجه;
    }
  وإلا إذا (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      بدل (c_parser_peek_token (parser)->type)
	{
	  حالة CPP_PLUS:
	  حالة CPP_MINUS:
	    إذا (c_parser_objc_diagnose_bad_element_پیشوند (parser, specs))
	      أرجع نتیجه;
	    إذا (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_درخت;
	      }
	    إذا (fndef_ok)
	      c_parser_objc_روش_definition (parser);
	    وإلا
	      c_parser_objc_methodproto (parser);
	    أرجع نتیجه;
	    اكسر;
	  افتراضي:
	    اكسر;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_AT_INTERFACE:
	  {
	    إذا (c_parser_objc_diagnose_bad_element_پیشوند (parser, specs))
	      أرجع نتیجه;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    أرجع نتیجه;
	  }
	  اكسر;
	حالة RID_AT_IMPLEMENTATION:
	  {
	    إذا (c_parser_objc_diagnose_bad_element_پیشوند (parser, specs))
	      أرجع نتیجه;
	    إذا (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_درخت;
	      }
	    c_parser_objc_class_definition (parser, NULL_درخت);
	    أرجع نتیجه;
	  }
	  اكسر;
	حالة RID_AT_PROTOCOL:
	  {
	    إذا (c_parser_objc_diagnose_bad_element_پیشوند (parser, specs))
	      أرجع نتیجه;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    أرجع نتیجه;
	  }
	  اكسر;
	حالة RID_AT_ALIAS:
	حالة RID_AT_CLASS:
	حالة RID_AT_انتها:
	حالة RID_AT_PROPERTY:
	  إذا (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = عدم;
	    }
	  اكسر;
	افتراضي:
	  اكسر;
	}
    }
  وإلا إذا (attribute_fallthrough_p (specs->attrs))
    warning_at (اینجا, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  وإلا إذا (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (اینجا, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_صفات (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  پیشوند_attrs = specs->attrs;
  all_پیشوند_attrs = پیشوند_attrs;
  specs->attrs = NULL_درخت;
  منطقي بیشتر_than_one_decl = خطأ;
  طالما (درست)
    {
      بنية c_declarator *declarator;
      منطقي dummy = خطأ;
      timevar_id_t tv;
      درخت fnbody = NULL_درخت;
      درخت underspec_name = NULL_درخت;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_نوع != ctsk_none,
					C_DTR_نرمال, &dummy);
      إذا (declarator == عدم)
	{
	  إذا (omp_declare_simd_clauses)
	    c_پایان_omp_declare_simd (parser, NULL_درخت, NULL_درخت,
				       omp_declare_simd_clauses);
	  إذا (oacc_routine_داده)
	    c_پایان_oacc_routine (oacc_routine_داده, NULL_درخت, خطأ);
	  /* This check is here purely to improve the diagnostic.  */
	  إذا (!simple_ok)
	    c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
	  أرجع نتیجه;
	}
      إذا (flag_openmp || flag_openmp_simd)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->نوع != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = عدم;
	  c_parser_handle_directive_omp_صفات (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      إذا (gnu_auto_type_p && declarator->نوع != cdk_id)
	{
	  error_at (اینجا,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
	  أرجع نتیجه;
	}
      إذا (std_auto_type_p)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->نوع == cdk_attrs)
	    d = d->declarator;
	  إذا (d->نوع != cdk_id)
	    {
	      error_at (اینجا,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
	      أرجع نتیجه;
	    }
	  underspec_name = d->u.id.id;
	}
      وإلا إذا (specs->constexpr_p)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->نوع != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_EQ)
	  || c_parser_بعدی_token_is (parser, CPP_COMMA)
	  || c_parser_بعدی_token_is (parser, CPP_SEMICOLON)
	  || c_parser_بعدی_token_is_keyword (parser, RID_ASM)
	  || c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_بعدی_token_is_keyword (parser, RID_درون))
	{
	  درخت asm_name = NULL_درخت;
	  درخت postfix_attrs = NULL_درخت;
	  إذا (!diagnosed_no_specs && !specs->declspecs_دیده_p)
	    {
	      diagnosed_no_specs = درست;
	      pedwarn (اینجا, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = خطأ;
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_عبارت (parser);
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_صفات (parser);
	      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (اینجا, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
		  أرجع نتیجه;
		}
	    }
	  إذا (c_parser_بعدی_token_is (parser, CPP_EQ))
	    {
	      درخت d;
	      بنية c_عبارت init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      إذا (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_جدول, init_loc);
		  بیعلامت صحيح underspec_state = 0;
		  إذا (std_auto_type_p)
		    underspec_state =
		      شروع_underspecified_init (init_loc, underspec_name);
		  شروع_init (NULL_درخت, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_کد_type flag_sanitize_save = flag_sanitize;
		  إذا (nested && !خالی_ok)
		    flag_sanitize = 0;
		  init = c_parser_عبارت_no_commas (parser, عدم);
		  إذا (std_auto_type_p)
		    پایان_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  إذا (gnu_auto_type_p
		      && درخت_کد (init.مقدار) == COMPONENT_REF
		      && DECL_C_بیت_فیلد (درخت_عملوند (init.مقدار, 1)))
		    error_at (اینجا,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_مقصد_rvalue (init_loc, init, درست, درست,
						   درست);
		  درخت init_type = درخت_TYPE (init.مقدار);
		  منطقي vm_type = c_type_variably_modified_p (init_type);
		  إذا (vm_type)
		    init.مقدار = save_عبارت (init.مقدار);
		  پایان_init ();
		  specs->typespec_نوع = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = درست;
		  specs->type = init_type;
		  إذا (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_صفات (specs->type,
						  specs->postfix_attrs);
		      decl_صفات (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_درخت;
		    }
		  إذا (vm_type)
		    {
		      منطقي maybe_const = درست;
		      درخت type_عبارت = c_fully_fold (init.مقدار, خطأ,
						     &maybe_const);
		      specs->عبارت_const_operands &= maybe_const;
		      إذا (specs->عبارت)
			specs->عبارت = build2 (COMPOUND_عبارت,
					      درخت_TYPE (type_عبارت),
					      specs->عبارت, type_عبارت);
		      وإلا
			specs->عبارت = type_عبارت;
		    }
		  d = شروع_decl (declarator, specs, درست,
				  chainon (postfix_attrs, all_پیشوند_attrs));
		  إذا (!d)
		    d = error_mark_گره;
		  إذا (omp_declare_simd_clauses)
		    c_پایان_omp_declare_simd (parser, d, NULL_درخت,
					       omp_declare_simd_clauses);
		  إذا (!omp_dsimd_idattr_clauses.is_خالی ())
		    c_پایان_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		}
	      وإلا
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_جدول, init_loc);
		  بیعلامت صحيح underspec_state = 0;
		  إذا (specs->constexpr_p)
		    underspec_state =
		      شروع_underspecified_init (init_loc, underspec_name);
		  d = شروع_decl (declarator, specs, درست,
				  chainon (postfix_attrs,
					   all_پیشوند_attrs),
				  !specs->constexpr_p);
		  إذا (!d)
		    d = error_mark_گره;
		  إذا (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_پایان_omp_declare_simd (parser, d, NULL_درخت,
					       omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالی ())
		    c_پایان_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		  شروع_init (d, asm_name,
			      درخت_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_کد_type flag_sanitize_save = flag_sanitize;
		  إذا (درخت_کد (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  إذا (specs->constexpr_p)
		    {
		      پایان_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      إذا (omp_declare_simd_clauses)
			c_پایان_omp_declare_simd (parser, d, NULL_درخت,
						   omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالی ())
		    c_پایان_omp_declare_simd (parser, d, NULL_درخت,
					       &omp_dsimd_idattr_clauses);
		    }
		  پایان_init ();
		}
	      إذا (oacc_routine_داده)
		c_پایان_oacc_routine (oacc_routine_داده, d, خطأ);
	      إذا (d != error_mark_گره)
		{
		  maybe_warn_string_init (init_loc, درخت_TYPE (d), init);
		  پایان_decl (d, init_loc, init.مقدار,
			       init.original_type, asm_name);
		  نتیجه = d;
		}
	    }
	  وإلا
	    {
	      إذا (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (اینجا,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
		  أرجع نتیجه;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      درخت attrs = chainon (postfix_attrs, all_پیشوند_attrs);
	      درخت d = شروع_decl (declarator, specs, خطأ, attrs, درست,
				   &lastloc);
	      إذا (d && درخت_کد (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ثابت بنية c_declarator *decl = declarator;
		  ثابت بنية c_declarator *آخرین_non_id_attrs = عدم;

		  طالما (decl)
		    بدل (decl->نوع)
		      {
		      حالة cdk_array:
		      حالة cdk_function:
		      حالة cdk_اشاره_گر:
			آخرین_non_id_attrs = decl;
			decl = decl->declarator;
			اكسر;

		      حالة cdk_attrs:
			decl = decl->declarator;
			اكسر;

		      حالة cdk_id:
			decl = 0;
			اكسر;

		      افتراضي:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  إذا (آخرین_non_id_attrs
		      && آخرین_non_id_attrs->نوع == cdk_function)
		    {
		      درخت parms = آخرین_non_id_attrs->u.arg_info->parms;
		      إذا (DECL_ARGUMENTS (d) == NULL_درخت
			  && DECL_INITIAL (d) == NULL_درخت)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      إذا (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_خالی ())
		{
		  درخت parms = NULL_درخت;
		  إذا (d && درخت_کد (d) == FUNCTION_DECL)
		    {
		      بنية c_declarator *ce = declarator;
		      طالما (ce != عدم)
			إذا (ce->نوع == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    اكسر;
			  }
			وإلا
			  ce = ce->declarator;
		    }
		  إذا (parms)
		    موقت_store_parm_decls (d, parms);
		  إذا (omp_declare_simd_clauses)
		    c_پایان_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالی ())
		    c_پایان_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  إذا (parms)
		    موقت_برداشت_parm_decls ();
		}
	      إذا (oacc_routine_داده)
		c_پایان_oacc_routine (oacc_routine_داده, d, خطأ);
	      إذا (d)
		پایان_decl (d, UNKNOWN_LOCATION, NULL_درخت,
			     NULL_درخت, asm_name);

	      إذا (c_parser_بعدی_token_is_keyword (parser, RID_درون))
		{
		  إذا (d)
		    *objc_foreach_object_declaration = d;
		  وإلا
		    *objc_foreach_object_declaration = error_mark_گره;
		}
	    }
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    {
	      بیشتر_than_one_decl = درست;
	      إذا (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (اینجا,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
		  أرجع نتیجه;
		}
	      c_parser_consume_token (parser);
	      إذا (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
		all_پیشوند_attrs = chainon (c_parser_gnu_صفات (parser),
					    پیشوند_attrs);
	      وإلا
		all_پیشوند_attrs = پیشوند_attrs;
	      استمر;
	    }
	  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	    {
	      إذا (!simple_ok)
		c_parser_consume_token (parser);
	      أرجع نتیجه;
	    }
	  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_درون))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      أرجع نتیجه;
	    }
	  وإلا
	    {
	      إذا (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      وإلا إذا (بیشتر_than_one_decl)
		error_at (اینجا, "declaration in condition can only declare "
			  "a single object");
	      أرجع نتیجه;
	    }
	}
      وإلا إذا (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (اینجا,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
	  أرجع نتیجه;
	}
      وإلا إذا (!fndef_ok)
	{
	  إذا (simple_ok && c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  وإلا
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
	    }
	  أرجع نتیجه;
	}
      /* Function definition (nested or otherwise).  */
      إذا (nested)
	{
	  pedwarn (اینجا, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_افزودن_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      درخت dv_پایه = NULL_درخت;
      درخت dv_ctx = NULL_درخت;
      إذا (!vec_امن_is_خالی (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->آخرین ();
	  dv_ctx = copy_list (a.selector);
	  dv_پایه = omp_شروع_variant_function (declarator, dv_ctx);
	}

      إذا (!شروع_function (specs, declarator, all_پیشوند_attrs))
	{
	  /* At this point we've consumed:
	       declaration-specifiers declarator
	     and the next token isn't CPP_EQ, CPP_COMMA, CPP_SEMICOLON,
	     RID_ASM, RID_ATTRIBUTE, or RID_IN,
	     but the
	       declaration-specifiers declarator
	     aren't grokkable as a function definition, so we have
	     an error.  */
	  gcc_assert (!c_parser_بعدی_token_is (parser, CPP_SEMICOLON));
	  إذا (c_parser_بعدی_token_starts_declspecs (parser))
	    {
	      /* If we have
		   declaration-specifiers declarator decl-specs
		 then assume we have a missing semicolon, which would
		 give us:
		   declaration-specifiers declarator  decl-specs
						    ^
						    ;
		   <~~~~~~~~~ declaration ~~~~~~~~~~>
		 Use c_parser_require to get an error with a fix-it hint.  */
	      c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>");
	      parser->error = خطأ;
	    }
	  وإلا
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  إذا (nested)
	    c_برداشت_function_context ();
	  اكسر;
	}

      إذا (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      وإلا
        tv = TV_PARSE_FUNC;
      auto_timevar at (g_timer, tv);

      /* Parse old-style parameter declarations.  ??? Attributes are
	 not allowed to start declaration specifiers here because of a
	 syntax conflict between a function declaration with attribute
	 suffix and a function definition with an attribute prefix on
	 first old-style parameter declaration.  Following the old
	 parser, they are not accepted on subsequent old-style
	 parameter declarations either.  However, there is no
	 ambiguity after the first declaration, nor indeed on the
	 first as long as we don't allow postfix attributes after a
	 declarator with a nonempty identifier list in a definition;
	 and postfix attributes have never been accepted here in
	 function definitions either.  */
      صحيح save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      طالما (c_parser_بعدی_token_is_not (parser, CPP_EOF)
	     && c_parser_بعدی_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, خطأ, خطأ, خطأ,
				       درست, خطأ, خطأ);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      إذا (omp_declare_simd_clauses)
	c_پایان_omp_declare_simd (parser, current_function_decl, NULL_درخت,
				   omp_declare_simd_clauses);
      إذا (!omp_dsimd_idattr_clauses.is_خالی ())
	c_پایان_omp_declare_simd (parser, current_function_decl, NULL_درخت,
				   &omp_dsimd_idattr_clauses);
      إذا (oacc_routine_داده)
	c_پایان_oacc_routine (oacc_routine_داده, current_function_decl, درست);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_شروع_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      إذا (dv_پایه && current_function_decl != error_mark_گره)
	{
	  omp_begin_declare_variant_map_مدخل e
	    = { current_function_decl, dv_پایه, dv_ctx };
	  vec_امن_افزودن (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      إذا (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  افزودن_scope ();
	  برداشت_scope ();

	  پایان_function (endloc);
	  أرجع نتیجه;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      وإلا إذا (specs->declspec_il != cdil_none)
	{
	  منطقي saved = درون_late_دودویی_op;
	  درون_late_دودویی_op = درست;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->مدخل_bb_شمار);
	  درون_late_دودویی_op = saved;
	}
      وإلا
	fnbody = c_parser_compound_statement (parser, &endloc);
      درخت fndecl = current_function_decl;
      إذا (nested && specs->declspec_il == cdil_none)
	{
	  درخت decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  جمع_کن_stmt (fnbody);
	  پایان_function (endloc);
	  c_برداشت_function_context ();
	  جمع_کن_stmt (build_stmt (DECL_منبع_LOCATION (decl), DECL_عبارت, decl));
	}
      وإلا إذا (nested)
	{
	  إذا (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  وإلا
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  پایان_function (endloc);
	  c_برداشت_function_context ();
	}
      وإلا
	{
	  إذا (fnbody)
	    جمع_کن_stmt (fnbody);
	  پایان_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      إذا (specs->declspec_il != cdil_none)
	DECL_SAVED_درخت (fndecl) = NULL_درخت;

      اكسر;
    }

  أرجع نتیجه;
}

/* Parse an asm-definition (asm() outside a function body).  This is a
   GNU extension.

   asm-definition:
     simple-asm-expr ;
     asm ( toplevel-asm-argument ) ;

   toplevel-asm-argument:
     asm-string-literal
     asm-string-literal : asm-operands[opt]
     asm-string-literal : asm-operands[opt] : asm-operands[opt]

   The :: token is considered equivalent to two consecutive : tokens.  */

ساكن فراغ
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  درخت asm_str = NULL_درخت;
  درخت outputs = NULL_درخت, inputs = NULL_درخت;
  إذا (!parens.require_open (parser))
    اذهب انجامشده;
  asm_str = c_parser_asm_string_literal (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      اذهب انجامشده;
    }
  لكل (صحيح section = 0; section < 2; ++section)
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  إذا (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	      asm_str = NULL_درخت;
	      اذهب انجامشده;
	    }
	  c_parser_consume_token (parser);
	}
      وإلا إذا (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, خطأ))
	اذهب error_close_paren;
      إذا (!c_parser_بعدی_token_is (parser, CPP_COLON)
	  && !c_parser_بعدی_token_is (parser, CPP_SCOPE)
	  && !c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (section)
	    inputs = c_parser_asm_operands (parser);
	  وإلا
	    outputs = c_parser_asm_operands (parser);
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;
    }

  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
      asm_str = NULL_درخت;
    }

  إذا (asm_str)
    asm_str = build_asm_عبارت (asm_loc, asm_str, outputs, inputs,
			      NULL_درخت, NULL_درخت, خطأ, خطأ);
انجامشده:
  إذا (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

ساكن فراغ
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  إذا (parser->error
      || !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
}

/* Parse a static assertion (C11 6.7.10), without the trailing
   semicolon.

   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression , string-literal )

   C23:
   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression )
*/

ساكن فراغ
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, مقدار_loc;
  درخت مقدار;
  درخت string = NULL_درخت;

  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_STATIC_ASSERT));
  درخت spelling = c_parser_peek_token (parser)->مقدار;
  assert_loc = c_parser_peek_token (parser)->location;
  إذا (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  وإلا
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع;
  location_t مقدار_tok_loc = c_parser_peek_token (parser)->location;
  مقدار = convert_lvalue_مقصد_rvalue (مقدار_tok_loc,
				    c_parser_عبارت_no_commas (parser, عدم),
				    درست, درست).مقدار;
  مقدار_loc = عبارت_LOC_OR_LOC (مقدار, مقدار_tok_loc);
  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_STRING:
	حالة CPP_STRING16:
	حالة CPP_STRING32:
	حالة CPP_WSTRING:
	حالة CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, خطأ, درست).مقدار;
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected string literal");
	  أرجع;
	}
    }
  وإلا إذا (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (مقدار)))
    {
      error_at (مقدار_loc, "expression in static assertion is not an integer");
      أرجع;
    }
  إذا (درخت_کد (مقدار) != INTEGER_CST)
    {
      مقدار = c_fully_fold (مقدار, خطأ, عدم);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (مقدار);
      إذا (درخت_کد (مقدار) == INTEGER_CST)
	pedwarn (مقدار_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  إذا (درخت_کد (مقدار) != INTEGER_CST)
    {
      error_at (مقدار_loc, "expression in static assertion is not constant");
      أرجع;
    }
  constant_عبارت_warning (مقدار);
  إذا (integer_zerop (مقدار))
    {
      إذا (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      وإلا
	error_at (assert_loc, "static assertion failed");
    }
}

/* Parse some declaration specifiers (possibly none) (C90 6.5, C99
   6.7, C11 6.7), adding them to SPECS (which may already include some).
   Storage class specifiers are accepted iff SCSPEC_OK; type
   specifiers are accepted iff TYPESPEC_OK; alignment specifiers are
   accepted iff ALIGNSPEC_OK; gnu-attributes are accepted at the start
   iff START_ATTR_OK; __auto_type is accepted iff AUTO_TYPE_OK.  In
   addition to the syntax shown, standard attributes are accepted at
   the start iff START_STD_ATTR_OK and at the end iff END_STD_ATTR_OK;
   unlike gnu-attributes, they are not accepted in the middle of the
   list.  (This combines various different syntax productions in the C
   standard, and in some cases gnu-attributes and standard attributes
   at the start may already have been parsed before this function is
   called.)

   declaration-specifiers:
     storage-class-specifier declaration-specifiers[opt]
     type-specifier declaration-specifiers[opt]
     type-qualifier declaration-specifiers[opt]
     function-specifier declaration-specifiers[opt]
     alignment-specifier declaration-specifiers[opt]

   Function specifiers (inline) are from C99, and are currently
   handled as storage class specifiers, as is __thread.  Alignment
   specifiers are from C11.

   C90 6.5.1, C99 6.7.1, C11 6.7.1:
   storage-class-specifier:
     typedef
     extern
     static
     auto
ثبات
     _Thread_local

   (_Thread_local is new in C11.)

   C99 6.7.4, C11 6.7.4:
   function-specifier:
     inline
     _Noreturn

   (_Noreturn is new in C11.)

   C90 6.5.2, C99 6.7.2, C11 6.7.2:
   type-specifier:
     void
     char
     short
     int
     long
     float
     double
     signed
     unsigned
     _Bool
     _Complex
     [_Imaginary removed in C99 TC2]
     _BitInt ( constant-expression )
     struct-or-union-specifier
     enum-specifier
     typedef-name
     atomic-type-specifier

   (_Bool and _Complex are new in C99.)
   (atomic-type-specifier is new in C11.)
   (_BitInt is new in C23.)

   C90 6.5.3, C99 6.7.3, C11 6.7.3:

   type-qualifier:
     const
     restrict
     volatile
     address-space-qualifier
     _Atomic

   (restrict is new in C99.)
   (_Atomic is new in C11.)

   GNU extensions:

   declaration-specifiers:
     gnu-attributes declaration-specifiers[opt]

   type-qualifier:
     address-space

   address-space:
     identifier recognized by the target

   storage-class-specifier:
     __thread

   type-specifier:
     typeof-specifier
     __auto_type
     __intN
     _Decimal32
     _Decimal64
     _Decimal128
     _Fract
     _Accum
     _Sat

  (_Fract, _Accum, and _Sat are new from ISO/IEC DTR 18037:
   http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1169.pdf)

   atomic-type-specifier
    _Atomic ( type-name )

   Objective-C:

   type-specifier:
     class-name objc-protocol-refs[opt]
     typedef-name objc-protocol-refs
     objc-protocol-refs
*/

فراغ
c_parser_declspecs (c_parser *parser, بنية c_declspecs *specs,
		    منطقي scspec_ok, منطقي typespec_ok, منطقي شروع_attr_ok,
		    منطقي alignspec_ok, منطقي auto_type_ok,
		    منطقي شروع_std_attr_ok, منطقي انتها_std_attr_ok,
		    تعداد c_lookahead_نوع la)
{
  منطقي attrs_ok = شروع_attr_ok;
  منطقي دیده_type = specs->typespec_نوع != ctsk_none;

  إذا (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  إذا (شروع_std_attr_ok
      && c_parser_nth_token_starts_std_صفات (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_دیده_p);
      location_t loc = c_parser_peek_token (parser)->location;
      درخت attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_جمع_کن_attrs (loc, specs, attrs);
      specs->non_std_attrs_دیده_p = خطأ;
    }

  طالما (c_parser_بعدی_token_is (parser, CPP_NAME)
	 || c_parser_بعدی_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_بعدی_token_is (parser, CPP_LESS)))
    {
      بنية c_typespec t;
      درخت attrs;
      درخت align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      إذا ((!typespec_ok || specs->typespec_نوع == ctsk_tagdef)
	  && c_parser_بعدی_نشانهها_شروع_typename (parser, la)
	  && !c_parser_بعدی_token_is_qualifier (parser)
	  && !c_parser_بعدی_token_is_keyword (parser, RID_ALIGNAS))
	اكسر;

      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  درخت مقدار = name_token->مقدار;
	  c_id_نوع نوع = name_token->id_نوع;

	  إذا (نوع == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_اولی_ADDR_SPACE;
	      declspecs_جمع_کن_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = درست;
	      استمر;
	    }

	  gcc_assert (!c_parser_بعدی_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  إذا (دیده_type || !c_parser_بعدی_نشانهها_شروع_typename (parser, la))
	    اكسر;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  دیده_type = درست;
	  attrs_ok = درست;
	  إذا (نوع == C_ID_ID)
	    {
	      auto_diagnostic_گروه d;
	      name_hint hint = lookup_name_fuzzy (مقدار, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      إذا (ثابت حرف *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.جمع_کن_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    مقدار, suggestion);
		}
	      وإلا
		error_at (loc, "unknown type name %qE", مقدار);
	      t.نوع = ctsk_typedef;
	      t.spec = error_mark_گره;
	    }
	  وإلا إذا (نوع == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_بعدی_token_is_not (parser, CPP_LESS)))
	    {
	      t.نوع = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (مقدار);
	    }
	  وإلا
	    {
	      درخت proto = NULL_درخت;
	      gcc_assert (c_dialect_objc ());
	      t.نوع = ctsk_objc;
	      إذا (c_parser_بعدی_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (مقدار, proto);
	    }
	  t.عبارت = NULL_درخت;
	  t.عبارت_const_operands = درست;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_جمع_کن_type (name_token->location, specs, t);
	  استمر;
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  درخت proto;
	  gcc_assert (c_dialect_objc ());
	  إذا (!typespec_ok || دیده_type)
	    اكسر;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.نوع = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_درخت, proto);
	  t.عبارت = NULL_درخت;
	  t.عبارت_const_operands = درست;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_جمع_کن_type (loc, specs, t);
	  استمر;
	}
      gcc_assert (c_parser_بعدی_token_is (parser, CPP_KEYWORD));
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_STATIC:
	حالة RID_EXTERN:
	حالة RID_ثبات:
	حالة RID_TYPEDEF:
	حالة RID_INLINE:
	حالة RID_NORETURN:
	حالة RID_AUTO:
	حالة RID_THREAD:
	حالة RID_CONSTEXPR:
	  إذا (!scspec_ok)
	    اذهب بیرون;
	  attrs_ok = درست;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_جمع_کن_scspec (loc, specs,
				c_parser_peek_token (parser)->مقدار);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_AUTO_TYPE:
	  إذا (!auto_type_ok)
	    اذهب بیرون;
	  /* Fall through.  */
	حالة RID_UNSIGNED:
	حالة RID_LONG:
	حالة RID_SHORT:
	حالة RID_SIGNED:
	حالة RID_COMPLEX:
	حالة RID_INT:
	حالة RID_CHAR:
	حالة RID_FLOAT:
	حالة RID_DOUBLE:
	حالة RID_VOID:
	حالة RID_DFLOAT32:
	حالة RID_DFLOAT64:
	حالة RID_DFLOAT128:
	حالة RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالة RID_BOOL:
	حالة RID_FRACT:
	حالة RID_ACCUM:
	حالة RID_SAT:
	حالة RID_INT_N_0:
	حالة RID_INT_N_1:
	حالة RID_INT_N_2:
	حالة RID_INT_N_3:
	  إذا (!typespec_ok)
	    اذهب بیرون;
	  attrs_ok = درست;
	  دیده_type = درست;
	  إذا (c_dialect_objc ())
	    parser->objc_need_raw_identifier = درست;
	  t.نوع = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->مقدار;
	  t.عبارت = NULL_درخت;
	  t.عبارت_const_operands = درست;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_جمع_کن_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_ENUM:
	  إذا (!typespec_ok)
	    اذهب بیرون;
	  attrs_ok = درست;
	  دیده_type = درست;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_پایان_TYPE, t.spec);
	  declspecs_جمع_کن_type (loc, specs, t);
	  اكسر;
	حالة RID_STRUCT:
	حالة RID_UNION:
	  إذا (!typespec_ok)
	    اذهب بیرون;
	  attrs_ok = درست;
	  دیده_type = درست;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_پایان_TYPE, t.spec);
	  declspecs_جمع_کن_type (loc, specs, t);
	  اكسر;
	حالة RID_TYPEOF:
	حالة RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  إذا (!typespec_ok || دیده_type)
	    اذهب بیرون;
	  attrs_ok = درست;
	  دیده_type = درست;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_جمع_کن_type (loc, specs, t);
	  اكسر;
	حالة RID_BITINT:
	  إذا (!typespec_ok)
	    اذهب بیرون;
	  وإلا
	    {
	      attrs_ok = درست;
	      دیده_type = درست;
	      t.نوع = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->مقدار;
	      t.عبارت = error_mark_گره;
	      t.عبارت_const_operands = درست;
	      t.has_enum_type_specifier = خطأ;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      إذا (parens.require_open (parser))
		{
		  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
		  t.عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, درست,
						     درست).مقدار;
		  parens.skip_until_یافت_close (parser);
		}
	      declspecs_جمع_کن_type (loc, specs, t);
	    }
	  اكسر;
	حالة RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  إذا (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  إذا (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  وإلا
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = درست;
	  درخت مقدار;
	  مقدار = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	  إذا (typespec_ok && c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      دیده_type = درست;
	      c_parser_consume_token (parser);
	      بنية c_type_name *type = c_parser_type_name (parser);
	      t.نوع = ctsk_typeof;
	      t.spec = error_mark_گره;
	      t.عبارت = NULL_درخت;
	      t.عبارت_const_operands = درست;
	      t.has_enum_type_specifier = خطأ;
	      إذا (type != عدم)
		t.spec = groktypename (type, &t.عبارت,
				       &t.عبارت_const_operands);
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      إذا (t.spec != error_mark_گره)
		{
		  إذا (درخت_کد (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  وإلا إذا (درخت_کد (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  وإلا إذا (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  وإلا
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_جمع_کن_type (loc, specs, t);
	    }
	  وإلا
	    declspecs_جمع_کن_qual (loc, specs, مقدار);
	  اكسر;
	حالة RID_CONST:
	حالة RID_VOLATILE:
	حالة RID_RESTRICT:
	  attrs_ok = درست;
	  declspecs_جمع_کن_qual (loc, specs, c_parser_peek_token (parser)->مقدار);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_ATTRIBUTE:
	  إذا (!attrs_ok)
	    اذهب بیرون;
	  attrs = c_parser_gnu_صفات (parser);
	  declspecs_جمع_کن_attrs (loc, specs, attrs);
	  اكسر;
	حالة RID_ALIGNAS:
	  إذا (!alignspec_ok)
	    اذهب بیرون;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_جمع_کن_alignas (loc, specs, align);
	  اكسر;
	حالة RID_GIMPLE:
	  إذا (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  اكسر;
	حالة RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  اكسر;
	افتراضي:
	  اذهب بیرون;
	}
    }
 بیرون:
  إذا (انتها_std_attr_ok
      && c_parser_nth_token_starts_std_صفات (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

ساكن فراغ
report_bad_enum_name (c_parser *parser)
{
  إذا (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      بدل (token->type)
	{
	افتراضي:
	  اكسر;
	حالة CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = درست;
	  أرجع;
	حالة CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  إذا (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_گروه d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_اشاره_گر (token->مقدار));
	      جمع_کن_note_about_new_keyword (token->location,
					  token->مقدار);
	      parser->error = درست;
	      أرجع;
	    }
	  اكسر;
	}
    }

  /* Otherwise, a more generic error message.  */
  c_parser_error (parser, "expected identifier");
}

/* Parse an enum specifier (C90 6.5.2.2, C99 6.7.2.2, C11 6.7.2.2).

   enum-specifier:
     enum gnu-attributes[opt] identifier[opt] enum-type-specifier[opt]
       { enumerator-list } gnu-attributes[opt]
     enum gnu-attributes[opt] identifier[opt] enum-type-specifier[opt]
       { enumerator-list , } gnu-attributes[opt] enum-type-specifier[opt]
     enum gnu-attributes[opt] identifier

   The form with trailing comma is new in C99; enum-type-specifiers
   are new in C23.  The forms with gnu-attributes are GNU extensions.
   In GNU C, we accept any expression without commas in the syntax
   (assignment expressions, not just conditional expressions);
   assignment expressions will be diagnosed as non-constant.

   enum-type-specifier:
     : specifier-qualifier-list

   enumerator-list:
     enumerator
     enumerator-list , enumerator

   enumerator:
     enumeration-constant attribute-specifier-sequence[opt]
     enumeration-constant attribute-specifier-sequence[opt]
       = constant-expression

   GNU Extensions:

   enumerator:
     enumeration-constant attribute-specifier-sequence[opt] gnu-attributes[opt]
     enumeration-constant attribute-specifier-sequence[opt] gnu-attributes[opt]
       = constant-expression

*/

ساكن بنية c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  بنية c_typespec ret;
  منطقي have_std_attrs;
  منطقي potential_nesting_p = خطأ;
  درخت std_attrs = NULL_درخت;
  درخت attrs;
  درخت ident = NULL_درخت;
  درخت fixed_underlying_type = NULL_درخت;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_صفات (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_صفات (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_مجموعه_منبع_position_from_token (c_parser_peek_token (parser));
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->مقدار;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  إذا (c_parser_بعدی_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      إذا (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_برچسب (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, درست);
	  إذا (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_درخت == TYPE_مقادیر (ret.spec);
	}
      وإلا
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_درخت;
	  ret.نوع = ctsk_tagdef;
	  ret.عبارت = NULL_درخت;
	  ret.عبارت_const_operands = درست;
	  ret.has_enum_type_specifier = درست;
	}
      c_parser_consume_token (parser);
      بنية c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, خطأ, درست, خطأ, خطأ, خطأ,
			  خطأ, درست, cla_prefer_id);
      پایان_declspecs (specs);
      إذا (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      وإلا إذا (درخت_کد (specs->type) != INTEGER_TYPE
	       && درخت_کد (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || درخت_کد (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_گره;
	}
      وإلا إذا (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      إذا (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  إذا (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_درخت)
	    {
	      TYPE_MIN_مقدار (ret.spec) =
		TYPE_MIN_مقدار (fixed_underlying_type);
	      TYPE_MAX_مقدار (ret.spec) =
		TYPE_MAX_مقدار (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      مجموعه_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_اندازه (ret.spec) = NULL_درخت;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  وإلا إذا (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      بنية c_enum_contents the_enum;
      درخت type;
      درخت postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      درخت مقادیر;
      timevar_افزودن (TV_PARSE_ENUM);
      type = شروع_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      مقادیر = NULL_درخت;
      c_parser_consume_token (parser);
      طالما (درست)
	{
	  درخت enum_id;
	  درخت enum_مقدار;
	  درخت enum_decl;
	  منطقي دیده_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, مقدار_loc;
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE, عدم);
	      مقادیر = error_mark_گره;
	      اكسر;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->مقدار;
	  /* Set the location in case we create a decl now.  */
	  c_parser_مجموعه_منبع_position_from_token (token);
	  decl_loc = مقدار_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  درخت std_attrs = NULL_درخت;
	  إذا (c_parser_nth_token_starts_std_صفات (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  درخت enum_attrs = chainon (std_attrs,
				     c_parser_gnu_صفات (parser));
	  إذا (c_parser_بعدی_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      مقدار_loc = c_parser_peek_token (parser)->location;
	      enum_مقدار = convert_lvalue_مقصد_rvalue (مقدار_loc,
						     (c_parser_عبارت_no_commas
						      (parser, عدم)),
						     درست, درست).مقدار;
	    }
	  وإلا
	    enum_مقدار = NULL_درخت;
	  enum_decl = build_enumerator (decl_loc, مقدار_loc,
					&the_enum, enum_id, enum_مقدار);
	  إذا (enum_attrs)
	    decl_صفات (&درخت_PURPOSE (enum_decl), enum_attrs, 0);
	  درخت_CHAIN (enum_decl) = مقادیر;
	  مقادیر = enum_decl;
	  دیده_comma = خطأ;
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      دیده_comma = درست;
	      c_parser_consume_token (parser);
	    }
	  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      إذا (دیده_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  إذا (!دیده_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE, عدم);
	      مقادیر = error_mark_گره;
	      اكسر;
	    }
	}
      postfix_attrs = c_parser_gnu_صفات (parser);
      ret.spec = پایان_enum (type, nreverse (مقادیر),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.نوع = ctsk_tagdef;
      ret.عبارت = NULL_درخت;
      ret.عبارت_const_operands = درست;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_درخت;
      timevar_برداشت (TV_PARSE_ENUM);
      أرجع ret;
    }
  وإلا إذا (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_گره;
      ret.نوع = ctsk_tagref;
      ret.عبارت = NULL_درخت;
      ret.عبارت_const_operands = درست;
      ret.has_enum_type_specifier = خطأ;
      أرجع ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  إذا (have_std_attrs && c_parser_بعدی_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  إذا (fixed_underlying_type == NULL_درخت)
    {
      ret = parser_xref_برچسب (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, خطأ);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      إذا (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  أرجع ret;
}

/* Parse a struct or union specifier (C90 6.5.2.1, C99 6.7.2.1, C11 6.7.2.1).

   struct-or-union-specifier:
     struct-or-union attribute-specifier-sequence[opt] gnu-attributes[opt]
       identifier[opt] { struct-contents } gnu-attributes[opt]
     struct-or-union attribute-specifier-sequence[opt] gnu-attributes[opt]
       identifier

   struct-contents:
     struct-declaration-list

   struct-declaration-list:
     struct-declaration ;
     struct-declaration-list struct-declaration ;

   GNU extensions:

   struct-contents:
خالی
     struct-declaration
     struct-declaration-list struct-declaration

   struct-declaration-list:
     struct-declaration-list ;
     ;

   (Note that in the syntax here, unlike that in ISO C, the semicolons
   are included here rather than in struct-declaration, in order to
   describe the syntax with extra semicolons and missing semicolon at
   end.)

   Objective-C:

   struct-declaration-list:
     @defs ( class-name )

   (Note this does not include a trailing semicolon, but can be
   followed by further declarations, and gets a pedwarn-if-pedantic
   when followed by a semicolon.)  */

ساكن بنية c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  بنية c_typespec ret;
  منطقي have_std_attrs;
  درخت std_attrs = NULL_درخت;
  درخت attrs;
  درخت ident = NULL_درخت;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  تعداد درخت_کد_2 کد;
  بدل (c_parser_peek_token (parser)->keyword)
    {
    حالة RID_STRUCT:
      کد = رکورد_TYPE;
      اكسر;
    حالة RID_UNION:
      کد = UNION_TYPE;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_صفات (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_صفات (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_مجموعه_منبع_position_from_token (c_parser_peek_token (parser));

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->مقدار;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      صنف c_struct_parse_info *struct_info;
      درخت type = شروع_struct (struct_loc, کد, ident, &struct_info);
      درخت postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      درخت contents;
      درخت عبارت = عدم;
      timevar_افزودن (TV_PARSE_STRUCT);
      contents = NULL_درخت;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_DEFS))
	{
	  درخت name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  إذا (!parens.require_open (parser))
	    اذهب انتها_at_defs;
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_نوع == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->مقدار;
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	      اذهب انتها_at_defs;
	    }
	  parens.skip_until_یافت_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    انتها_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      طالما (درست)
	{
	  درخت decls;
	  /* Parse any stray semicolon.  */
	  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.جمع_کن_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  /* Accept #pragmas at struct scope.  */
	  إذا (c_parser_بعدی_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, عدم, NULL_درخت);
	      استمر;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &عبارت);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      وإلا إذا (parser->error
		       || !c_parser_بعدی_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE, عدم);
		  اكسر;
		}

	      /* If we come here, we have already emitted an error
		 for an expected `;', identifier or `(', and we also
	         recovered already.  Go on with the next field. */
	    }
	}
      postfix_attrs = c_parser_gnu_صفات (parser);
      ret.spec = پایان_struct (struct_loc, type, nreverse (contents),
				chainon (std_attrs,
					 chainon (attrs, postfix_attrs)),
				struct_info, &عبارت);
      ret.نوع = ctsk_tagdef;
      ret.عبارت = عبارت;
      ret.عبارت_const_operands = درست;
      ret.has_enum_type_specifier = خطأ;
      timevar_برداشت (TV_PARSE_STRUCT);
      أرجع ret;
    }
  وإلا إذا (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_گره;
      ret.نوع = ctsk_tagref;
      ret.عبارت = NULL_درخت;
      ret.عبارت_const_operands = درست;
      ret.has_enum_type_specifier = خطأ;
      أرجع ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  إذا (have_std_attrs && c_parser_بعدی_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_برچسب (ident_loc, کد, ident, have_std_attrs, std_attrs,
			 خطأ);
  أرجع ret;
}

/* Parse a struct-declaration (C90 6.5.2.1, C99 6.7.2.1, C11 6.7.2.1),
   *without* the trailing semicolon.

   struct-declaration:
     attribute-specifier-sequence[opt] specifier-qualifier-list
       attribute-specifier-sequence[opt] struct-declarator-list
     static_assert-declaration-no-semi

   specifier-qualifier-list:
     type-specifier specifier-qualifier-list[opt]
     type-qualifier specifier-qualifier-list[opt]
     alignment-specifier specifier-qualifier-list[opt]
     gnu-attributes specifier-qualifier-list[opt]

   struct-declarator-list:
     struct-declarator
     struct-declarator-list , gnu-attributes[opt] struct-declarator

   struct-declarator:
     declarator gnu-attributes[opt]
     declarator[opt] : constant-expression gnu-attributes[opt]

   GNU extensions:

   struct-declaration:
     __extension__ struct-declaration
     specifier-qualifier-list

   Unlike the ISO C syntax, semicolons are handled elsewhere.  The use
   of gnu-attributes where shown is a GNU extension.  In GNU C, we accept
   any expression without commas in the syntax (assignment
   expressions, not just conditional expressions); assignment
   expressions will be diagnosed as non-constant.  */

ساكن درخت
c_parser_struct_declaration (c_parser *parser, درخت *عبارت)
{
  بنية c_declspecs *specs;
  درخت پیشوند_attrs;
  درخت all_پیشوند_attrs;
  درخت decls;
  location_t decl_loc;
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_EXTENSION))
    {
      صحيح ext;
      درخت decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, عبارت);
      restore_extension_diagnostics (ext);
      أرجع decl;
    }
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      أرجع NULL_درخت;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, خطأ, درست, درست,
		      درست, خطأ, درست, درست, cla_nonabstract_decl);
  إذا (parser->error)
    أرجع NULL_درخت;
  إذا (!specs->declspecs_دیده_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      أرجع NULL_درخت;
    }
  پایان_declspecs (specs);
  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON)
      || c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
    {
      درخت ret;
      إذا (specs->typespec_نوع == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_برچسب_warned (specs, pedantic);
	  ret = NULL_درخت;
	}
      وإلا
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  درخت attrs = عدم;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_درخت), specs,
			   NULL_درخت, &attrs, عبارت);
	  إذا (ret)
	    decl_صفات (&ret, attrs, 0);
	}
      أرجع ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  إذا (specs->typespec_نوع == ctsk_tagdef
      && درخت_کد (specs->type) != ENUMERAL_TYPE
      && c_parser_بعدی_token_starts_declspecs (parser)
      && !c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = خطأ;
      أرجع NULL_درخت;
    }

  pending_xref_error ();
  پیشوند_attrs = specs->attrs;
  all_پیشوند_attrs = پیشوند_attrs;
  specs->attrs = NULL_درخت;
  decls = NULL_درخت;
  طالما (درست)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      بنية c_declarator *declarator;
      منطقي dummy = خطأ;
      إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_درخت);
      وإلا
	declarator = c_parser_declarator (parser,
					  specs->typespec_نوع != ctsk_none,
					  C_DTR_نرمال, &dummy);
      إذا (declarator == عدم)
	{
	  c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
	  اكسر;
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_COLON)
	  || c_parser_بعدی_token_is (parser, CPP_COMMA)
	  || c_parser_بعدی_token_is (parser, CPP_SEMICOLON)
	  || c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  درخت postfix_attrs = NULL_درخت;
	  درخت عرض = NULL_درخت;
	  درخت d;
	  إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      عرض = convert_lvalue_مقصد_rvalue (loc,
						(c_parser_عبارت_no_commas
						 (parser, عدم)),
						درست, درست).مقدار;
	    }
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_صفات (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, عرض, &all_پیشوند_attrs, عبارت);
	  decl_صفات (&d, chainon (postfix_attrs,
					all_پیشوند_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_پیشوند_attrs = chainon (c_parser_gnu_صفات (parser),
					پیشوند_attrs);
	  وإلا
	    all_پیشوند_attrs = پیشوند_attrs;
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON)
		   || c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      اكسر;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      اكسر;
	    }
	}
      وإلا
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  اكسر;
	}
    }
  أرجع decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

ساكن بنية c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  منطقي is_unqual;
  منطقي is_std;
  بنية c_typespec ret;
  ret.نوع = ctsk_typeof;
  ret.spec = error_mark_گره;
  ret.عبارت = NULL_درخت;
  ret.عبارت_const_operands = درست;
  ret.has_enum_type_specifier = خطأ;
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = خطأ;
      درخت spelling = c_parser_peek_token (parser)->مقدار;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_اشاره_گر (spelling), "typeof") == 0);
    }
  وإلا
    {
      gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = درست;
      درخت spelling = c_parser_peek_token (parser)->مقدار;
      is_std = strcmp (IDENTIFIER_اشاره_گر (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  درون_typeof++;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      درون_typeof--;
      أرجع ret;
    }
  إذا (c_parser_بعدی_نشانهها_شروع_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      درون_typeof--;
      إذا (type != عدم)
	{
	  ret.spec = groktypename (type, &ret.عبارت, &ret.عبارت_const_operands);
	  برداشت_maybe_استفاده_شده (c_type_variably_modified_p (ret.spec));
	}
    }
  وإلا
    {
      منطقي was_vm;
      location_t اینجا = c_parser_peek_token (parser)->location;
      بنية c_عبارت عبارت = c_parser_عبارت (parser);
      c_inhibit_evaluation_warnings--;
      درون_typeof--;
      إذا (درخت_کد (عبارت.مقدار) == COMPONENT_REF
	  && DECL_C_بیت_فیلد (درخت_عملوند (عبارت.مقدار, 1)))
	error_at (اینجا, "%<typeof%> applied to a bit-field");
      mark_exp_read (عبارت.مقدار);
      ret.spec = درخت_TYPE (عبارت.مقدار);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      إذا (was_vm)
	ret.عبارت = c_fully_fold (عبارت.مقدار, خطأ, &ret.عبارت_const_operands);
      برداشت_maybe_استفاده_شده (was_vm);
    }
  parens.skip_until_یافت_close (parser);
  إذا (ret.spec != error_mark_گره)
    {
      إذا (is_unqual)
	{
	  منطقي is_array = درخت_کد (ret.spec) == ARRAY_TYPE;
	  صحيح quals = TYPE_QUALS (strip_array_types (ret.spec));
	  إذا ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      إذا (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      إذا (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  إذا (درخت_کد (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  وإلا إذا (FUNCTION_اشاره_گر_TYPE_P (ret.spec)
		   && TYPE_QUALS (درخت_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_اشاره_گر_type (TYPE_MAIN_VARIANT (درخت_TYPE (ret.spec)));
	}
    }
  أرجع ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

ساكن درخت
c_parser_alignas_specifier (c_parser * parser)
{
  درخت ret = error_mark_گره;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_ALIGNAS));
  درخت spelling = c_parser_peek_token (parser)->مقدار;
  c_parser_consume_token (parser);
  إذا (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  وإلا
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع ret;
  إذا (c_parser_بعدی_نشانهها_شروع_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *type = c_parser_type_name (parser);
      إذا (type != عدم)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, عدم, عدم),
					خطأ, درست, 1);
    }
  وإلا
    ret = convert_lvalue_مقصد_rvalue (loc,
				    c_parser_عبارت_no_commas (parser, عدم),
				    درست, درست).مقدار;
  parens.skip_until_یافت_close (parser);
  أرجع ret;
}

/* Parse a declarator, possibly an abstract declarator (C90 6.5.4,
   6.5.5, C99 6.7.5, 6.7.6, C11 6.7.6, 6.7.7).  If TYPE_SEEN_P then
   a typedef name may be redeclared; otherwise it may not.  KIND
   indicates which kind of declarator is wanted.  Returns a valid
   declarator except in the case of a syntax error in which case NULL is
   returned.  *SEEN_ID is set to true if an identifier being declared is
   seen; this is used to diagnose bad forms of abstract array declarators
   and to determine whether an identifier list is syntactically permitted.

   declarator:
     pointer[opt] direct-declarator

   direct-declarator:
     identifier
     ( gnu-attributes[opt] declarator )
     direct-declarator array-declarator
     direct-declarator ( parameter-type-list )
     direct-declarator ( identifier-list[opt] )

   pointer:
     * type-qualifier-list[opt]
     * type-qualifier-list[opt] pointer

   type-qualifier-list:
     type-qualifier
     gnu-attributes
     type-qualifier-list type-qualifier
     type-qualifier-list gnu-attributes

   array-declarator:
     [ type-qualifier-list[opt] assignment-expression[opt] ]
     [ static type-qualifier-list[opt] assignment-expression ]
     [ type-qualifier-list static assignment-expression ]
     [ type-qualifier-list[opt] * ]

   parameter-type-list:
     parameter-list
     parameter-list , ...

   parameter-list:
     parameter-declaration
     parameter-list , parameter-declaration

   parameter-declaration:
     declaration-specifiers declarator gnu-attributes[opt]
     declaration-specifiers abstract-declarator[opt] gnu-attributes[opt]

   identifier-list:
     identifier
     identifier-list , identifier

   abstract-declarator:
اشاره_گر
     pointer[opt] direct-abstract-declarator

   direct-abstract-declarator:
     ( gnu-attributes[opt] abstract-declarator )
     direct-abstract-declarator[opt] array-declarator
     direct-abstract-declarator[opt] ( parameter-type-list[opt] )

   GNU extensions:

   direct-declarator:
     direct-declarator ( parameter-forward-declarations
			 parameter-type-list[opt] )

   direct-abstract-declarator:
     direct-abstract-declarator[opt] ( parameter-forward-declarations
				       parameter-type-list[opt] )

   parameter-forward-declarations:
     parameter-list ;
     parameter-forward-declarations parameter-list ;

   The uses of gnu-attributes shown above are GNU extensions.

   Some forms of array declarator are not included in C99 in the
   syntax for abstract declarators; these are disallowed elsewhere.
   This may be a defect (DR#289).

   This function also accepts an omitted abstract declarator as being
   an abstract declarator, although not part of the formal syntax.  */

بنية c_declarator *
c_parser_declarator (c_parser *parser, منطقي type_دیده_p, c_dtr_syn نوع,
		     منطقي *دیده_id)
{
  /* Parse any initial pointer part.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_MULT))
    {
      بنية c_declspecs *quals_attrs = build_null_declspecs ();
      بنية c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, درست,
			  خطأ, خطأ, درست, خطأ, cla_prefer_id);
      inner = c_parser_declarator (parser, type_دیده_p, نوع, دیده_id);
      إذا (inner == عدم)
	أرجع عدم;
      وإلا
	أرجع make_اشاره_گر_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  أرجع c_parser_مستقیم_declarator (parser, type_دیده_p, نوع, دیده_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

ساكن بنية c_declarator *
c_parser_مستقیم_declarator (c_parser *parser, منطقي type_دیده_p, c_dtr_syn نوع,
			    منطقي *دیده_id)
{
  /* The direct declarator must start with an identifier (possibly
     omitted) or a parenthesized declarator (possibly abstract).  In
     an ordinary declarator, initial parentheses must start a
     parenthesized declarator.  In an abstract declarator or parameter
     declarator, they could start a parenthesized declarator or a
     parameter list.  To tell which, the open parenthesis and any
     following gnu-attributes must be read.  If a declaration
     specifier or standard attributes follow, then it is a parameter
     list; if the specifier is a typedef name, there might be an
     ambiguity about redeclaring it, which is resolved in the
     direction of treating it as a typedef name.  If a close
     parenthesis follows, it is also an empty parameter list, as the
     syntax does not permit empty abstract declarators.  Otherwise, it
     is a parenthesized declarator (in which case the analysis may be
     repeated inside it, recursively).

     ??? There is an ambiguity in a parameter declaration "int
     (__attribute__((foo)) x)", where x is not a typedef name: it
     could be an abstract declarator for a function, or declare x with
     parentheses.  The proper resolution of this ambiguity needs
     documenting.  At present we follow an accident of the old
     parser's implementation, whereby the first parameter must have
     some declaration specifiers other than just gnu-attributes.  Thus as
     a parameter declaration it is treated as a parenthesized
     parameter named x, and as an abstract declarator it is
     rejected.

     ??? Also following the old parser, gnu-attributes inside an empty
     parameter list are ignored, making it a list not yielding a
     prototype, rather than giving an error or making it have one
     parameter with implicit type int.

     ??? Also following the old parser, typedef names may be
     redeclared in declarators, but not Objective-C class names.  */

  إذا (نوع != C_DTR_ABSTRACT
      && c_parser_بعدی_token_is (parser, CPP_NAME)
      && ((type_دیده_p
	   && (c_parser_peek_token (parser)->id_نوع == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_نوع == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_نوع == C_ID_ID))
    {
      بنية c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->مقدار);
      *دیده_id = درست;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (c_parser_nth_token_starts_std_صفات (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      أرجع c_parser_مستقیم_declarator_inner (parser, *دیده_id, inner);
    }

  إذا (نوع != C_DTR_نرمال
      && c_parser_بعدی_token_is (parser, CPP_OPEN_مربع)
      && !c_parser_nth_token_starts_std_صفات (parser, 1))
    {
      بنية c_declarator *inner = build_id_declarator (NULL_درخت);
      inner->id_loc = c_parser_peek_token (parser)->location;
      أرجع c_parser_مستقیم_declarator_inner (parser, *دیده_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      درخت attrs;
      بنية c_declarator *inner;
      c_parser_consume_token (parser);
      منطقي have_gnu_attrs = c_parser_بعدی_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_صفات (parser);
      إذا (نوع != C_DTR_نرمال
	  && (c_parser_بعدی_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_صفات (parser, 1)
		      || c_parser_بعدی_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  بنية c_arg_info *آرگومانها
	    = c_parser_parms_declarator (parser, نوع == C_DTR_نرمال,
					 attrs, have_gnu_attrs);
	  إذا (آرگومانها == عدم)
	    أرجع عدم;
	  وإلا
	    {
	      inner = build_id_declarator (NULL_درخت);
	      إذا (!(آرگومانها->types
		    && آرگومانها->types != error_mark_گره
		    && درخت_کد (درخت_مقدار (آرگومانها->types)) == IDENTIFIER_گره)
		  && c_parser_nth_token_starts_std_صفات (parser, 1))
		{
		  درخت std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  إذا (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (آرگومانها, inner);
	      أرجع c_parser_مستقیم_declarator_inner (parser, *دیده_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_دیده_p, نوع, دیده_id);
      إذا (inner != عدم && attrs != عدم)
	inner = build_attrs_declarator (attrs, inner);
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  إذا (inner == عدم)
	    أرجع عدم;
	  وإلا
	    أرجع c_parser_مستقیم_declarator_inner (parser, *دیده_id, inner);
	}
      وإلا
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع عدم;
	}
    }
  وإلا
    {
      إذا (نوع == C_DTR_نرمال)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  أرجع عدم;
	}
      وإلا
	أرجع build_id_declarator (NULL_درخت);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

ساكن بنية c_declarator *
c_parser_مستقیم_declarator_inner (c_parser *parser, منطقي id_present,
				  بنية c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_مربع)
      && !c_parser_nth_token_starts_std_صفات (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      بنية c_declarator *declarator;
      بنية c_declspecs *quals_attrs = build_null_declspecs ();
      بنية c_عبارت dimen;
      dimen.مقدار = NULL_درخت;
      dimen.original_کد = ERROR_MARK;
      dimen.original_type = NULL_درخت;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, درست,
			  خطأ, خطأ, خطأ, خطأ, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      إذا (c_parser_بعدی_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  إذا (!quals_attrs->declspecs_دیده_p)
	    c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, درست,
				خطأ, خطأ, خطأ, خطأ, cla_prefer_id);
	}
      إذا (!quals_attrs->declspecs_دیده_p)
	quals_attrs = عدم;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ثابت منطقي static_دیده = (static_loc != UNKNOWN_LOCATION);
      منطقي ستاره_دیده = خطأ;
      إذا (c_parser_بعدی_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_مربع)
	{
	  ستاره_دیده = درست;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (!c_parser_بعدی_token_is (parser, CPP_CLOSE_مربع))
	dimen = c_parser_عبارت_no_commas (parser, عدم);

      إذا (static_دیده)
	{
	  إذا (ستاره_دیده)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      ستاره_دیده = خطأ;
	      dimen.مقدار = error_mark_گره;
	    }
	  وإلا إذا (!dimen.مقدار)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_مربع))
	c_parser_consume_token (parser);
      وإلا
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع,
				     "expected %<]%>");
	  أرجع عدم;
	}
      إذا (dimen.مقدار)
	dimen = convert_lvalue_مقصد_rvalue (brace_loc, dimen, درست, درست);
      declarator = build_array_declarator (brace_loc, dimen.مقدار, quals_attrs,
					   static_دیده, ستاره_دیده);
      إذا (declarator == عدم)
	أرجع عدم;
      إذا (c_parser_nth_token_starts_std_صفات (parser, 1))
	{
	  درخت std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  إذا (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = مجموعه_array_declarator_inner (declarator, inner);
      أرجع c_parser_مستقیم_declarator_inner (parser, id_present, inner);
    }
  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      درخت attrs;
      بنية c_arg_info *آرگومانها;
      c_parser_consume_token (parser);
      منطقي have_gnu_attrs = c_parser_بعدی_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_صفات (parser);
      آرگومانها = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      إذا (آرگومانها == عدم)
	أرجع عدم;
      وإلا
	{
	  إذا (!(آرگومانها->types
		&& آرگومانها->types != error_mark_گره
		&& درخت_کد (درخت_مقدار (آرگومانها->types)) == IDENTIFIER_گره)
	      && c_parser_nth_token_starts_std_صفات (parser, 1))
	    {
	      درخت std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      إذا (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (آرگومانها, inner);
	  أرجع c_parser_مستقیم_declarator_inner (parser, id_present, inner);
	}
    }
  أرجع inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

ساكن بنية c_arg_info *
c_parser_parms_declarator (c_parser *parser, منطقي id_list_ok, درخت attrs,
			   منطقي have_gnu_attrs)
{
  افزودن_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  إذا (id_list_ok
      && !attrs
      && c_parser_بعدی_token_is (parser, CPP_NAME)
      && c_parser_peek_token (parser)->id_نوع == C_ID_ID

      /* Look ahead to detect typos in type names.  */
      && c_parser_peek_2nd_token (parser)->type != CPP_NAME
      && c_parser_peek_2nd_token (parser)->type != CPP_MULT
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_مربع
      && c_parser_peek_2nd_token (parser)->type != CPP_KEYWORD)
    {
      درخت list = NULL_درخت, *nextp = &list;
      طالما (c_parser_بعدی_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_نوع == C_ID_ID)
	{
	  *nextp = build_درخت_list (NULL_درخت,
				    c_parser_peek_token (parser)->مقدار);
	  nextp = & درخت_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      اكسر;
	    }
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	{
	  بنية c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  برداشت_scope ();
	  أرجع ret;
	}
      وإلا
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  برداشت_scope ();
	  أرجع عدم;
	}
    }
  وإلا
    {
      بنية c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, عدم, have_gnu_attrs);
      برداشت_scope ();
      أرجع ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

ساكن بنية c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, درخت attrs, درخت عبارت,
				منطقي have_gnu_attrs)
{
  منطقي bad_parm = خطأ;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
    {
      بنية c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      أرجع ret;
    }
  إذا (c_parser_بعدی_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      بنية c_arg_info *ret = build_arg_info ();

      ret->types = NULL_درخت;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_آرگومانها_stdarg_p = درست;
	  c_parser_consume_token (parser);
	  أرجع ret;
	}
      وإلا
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع عدم;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  طالما (درست)
    {
      /* Parse a parameter.  */
      بنية c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_درخت;
      have_gnu_attrs = خطأ;
      إذا (parm == عدم)
	bad_parm = درست;
      وإلا
	افزودن_parm_decl (parm, &عبارت);
      إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	{
	  درخت new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  منطقي new_have_gnu_attrs
	    = c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_صفات (parser);
	  أرجع c_parser_parms_list_declarator (parser, new_attrs, عبارت,
						 new_have_gnu_attrs);
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  إذا (bad_parm)
	    أرجع عدم;
	  وإلا
	    أرجع get_parm_info (خطأ, عبارت);
	}
      إذا (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, خطأ))
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع عدم;
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      إذا (bad_parm)
		أرجع عدم;
	      وإلا
		أرجع get_parm_info (درست, عبارت);
	    }
	  وإلا
	    {
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      أرجع عدم;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

ساكن بنية c_parm *
c_parser_parameter_declaration (c_parser *parser, درخت attrs,
				منطقي have_gnu_attrs)
{
  بنية c_declspecs *specs;
  بنية c_declarator *declarator;
  درخت پیشوند_attrs;
  درخت postfix_attrs = NULL_درخت;
  منطقي dummy = خطأ;

  /* Accept #pragmas between parameter declarations.  */
  طالما (c_parser_بعدی_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, عدم, NULL_درخت);

  إذا (!c_parser_بعدی_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_صفات (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (parser->error)
	أرجع عدم;
      c_parser_مجموعه_منبع_position_from_token (token);
      إذا (c_parser_بعدی_نشانهها_شروع_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_گروه d;
	  name_hint hint = lookup_name_fuzzy (token->مقدار,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  إذا (ثابت حرف *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.جمع_کن_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->مقدار, suggestion);
	    }
	  وإلا
	    error_at (token->location, "unknown type name %qE", token->مقدار);
	  parser->error = درست;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      وإلا
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_مقصد_انتها_از_parameter (parser);
      أرجع عدم;
    }

  location_t شروع_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  إذا (attrs)
    {
      declspecs_جمع_کن_attrs (درون_داد_location, specs, attrs);
      attrs = NULL_درخت;
    }
  c_parser_declspecs (parser, specs, درست, درست, درست, درست, خطأ,
		      !have_gnu_attrs, درست, cla_nonabstract_decl);
  پایان_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  إذا (specs->typespec_نوع == ctsk_tagdef)
    verify_counted_by_for_بالاترین_anonymous_type (specs->type);

  pending_xref_error ();
  پیشوند_attrs = specs->attrs;
  specs->attrs = NULL_درخت;
  declarator = c_parser_declarator (parser,
				    specs->typespec_نوع != ctsk_none,
				    C_DTR_PARM, &dummy);
  إذا (declarator == عدم)
    {
      c_parser_skip_until_یافت (parser, CPP_COMMA, عدم);
      أرجع عدم;
    }
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
    postfix_attrs = c_parser_gnu_صفات (parser);

  /* Generate a location for the parameter, ranging from the start of the
     initial token to the end of the final token.

     If we have a identifier, then use it for the caret location, e.g.

       extern int callee (int one, int (*two)(int, int), float three);
                                   ~~~~~~^~~~~~~~~~~~~~

     otherwise, reuse the start location for the caret location e.g.:

       extern int callee (int one, int (*)(int, int), float three);
                                   ^~~~~~~~~~~~~~~~~
  */
  location_t انتها_loc = parser->آخرین_token_location;

  /* Find any cdk_id declarator; determine if we have an identifier.  */
  c_declarator *id_declarator = declarator;
  طالما (id_declarator && id_declarator->نوع != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : شروع_loc);
  location_t param_loc = make_location (caret_loc, شروع_loc, انتها_loc);

  أرجع build_c_parm (specs, chainon (postfix_attrs, پیشوند_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

ساكن درخت
c_parser_asm_string_literal (c_parser *parser)
{
  درخت str;
  صحيح save_flag = warn_overlength_رشتهها;
  warn_overlength_رشتهها = 0;
  str = c_parser_string_literal (parser, خطأ, خطأ).مقدار;
  warn_overlength_رشتهها = save_flag;
  أرجع str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

ساكن درخت
c_parser_simple_asm_عبارت (c_parser *parser)
{
  درخت str;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع NULL_درخت;
  str = c_parser_asm_string_literal (parser);
  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
      أرجع NULL_درخت;
    }
  أرجع str;
}

ساكن درخت
c_parser_gnu_attribute_any_کلمه (c_parser *parser)
{
  درخت attr_name = NULL_درخت;

  إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      منطقي ok;
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_STATIC:
	حالة RID_UNSIGNED:
	حالة RID_LONG:
	حالة RID_CONST:
	حالة RID_EXTERN:
	حالة RID_ثبات:
	حالة RID_TYPEDEF:
	حالة RID_SHORT:
	حالة RID_INLINE:
	حالة RID_NORETURN:
	حالة RID_VOLATILE:
	حالة RID_SIGNED:
	حالة RID_AUTO:
	حالة RID_RESTRICT:
	حالة RID_COMPLEX:
	حالة RID_THREAD:
	حالة RID_INT:
	حالة RID_CHAR:
	حالة RID_FLOAT:
	حالة RID_DOUBLE:
	حالة RID_VOID:
	حالة RID_DFLOAT32:
	حالة RID_DFLOAT64:
	حالة RID_DFLOAT128:
	حالة RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	حالة RID_BOOL:
	حالة RID_BITINT:
	حالة RID_FRACT:
	حالة RID_ACCUM:
	حالة RID_SAT:
	حالة RID_TRANSACTION_ATOMIC:
	حالة RID_TRANSACTION_CANCEL:
	حالة RID_ATOMIC:
	حالة RID_AUTO_TYPE:
	حالة RID_CONSTEXPR:
	حالة RID_INT_N_0:
	حالة RID_INT_N_1:
	حالة RID_INT_N_2:
	حالة RID_INT_N_3:
	  ok = درست;
	  اكسر;
	افتراضي:
	  ok = خطأ;
	  اكسر;
	}
      إذا (!ok)
	أرجع NULL_درخت;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(صحيح) c_parser_peek_token (parser)->keyword];
    }
  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->مقدار;

  أرجع attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

ساكن درخت
c_parser_attribute_arguments (c_parser *parser, منطقي takes_identifier,
			      منطقي require_string, منطقي assume_attr,
			      منطقي allow_خالی_آرگومانها)
{
  vec<درخت, va_gc> *عبارت_list;
  درخت attr_آرگومانها;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      && (c_parser_peek_token (parser)->id_نوع == C_ID_ID
	  || (c_dialect_objc ()
	      && c_parser_peek_token (parser)->id_نوع
	      == C_ID_CLASSNAME))
      && ((c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	  || (c_parser_peek_2nd_token (parser)->type
	      == CPP_CLOSE_PAREN))
      && (takes_identifier
	  || (c_dialect_objc ()
	      && !assume_attr
	      && c_parser_peek_token (parser)->id_نوع
	      == C_ID_CLASSNAME)))
    {
      درخت arg1 = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	attr_آرگومانها = build_درخت_list (NULL_درخت, arg1);
      وإلا
	{
	  درخت درخت_list;
	  c_parser_consume_token (parser);
	  عبارت_list = c_parser_عبارت_list (parser, خطأ, درست,
					  عدم, عدم, عدم, عدم);
	  درخت_list = build_درخت_list_vec (عبارت_list);
	  attr_آرگومانها = درخت_cons (NULL_درخت, arg1, درخت_list);
	  release_درخت_وکتور (عبارت_list);
	}
    }
  وإلا
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (!allow_خالی_آرگومانها)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_آرگومانها = NULL_درخت;
	}
      وإلا إذا (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  درخت string = c_parser_string_literal (parser, خطأ, درست).مقدار;
	  attr_آرگومانها = build_درخت_list (NULL_درخت, string);
	}
      وإلا إذا (assume_attr)
	{
	  درخت cond
	    = c_parser_conditional_عبارت (parser, عدم, NULL_درخت).مقدار;
	  إذا (!c_parser_بعدی_token_is (parser, CPP_COMMA))
	    attr_آرگومانها = build_درخت_list (NULL_درخت, cond);
	  وإلا
	    {
	      درخت درخت_list;
	      c_parser_consume_token (parser);
	      عبارت_list = c_parser_عبارت_list (parser, خطأ, درست,
					      عدم, عدم, عدم, عدم);
	      درخت_list = build_درخت_list_vec (عبارت_list);
	      attr_آرگومانها = درخت_cons (NULL_درخت, cond, درخت_list);
	      release_درخت_وکتور (عبارت_list);
	    }
	}
      وإلا
	{
	  عبارت_list = c_parser_عبارت_list (parser, خطأ, درست,
					  عدم, عدم, عدم, عدم);
	  attr_آرگومانها = build_درخت_list_vec (عبارت_list);
	  release_درخت_وکتور (عبارت_list);
	}
    }
  أرجع attr_آرگومانها;
}

/* Parse (possibly empty) gnu-attributes.  This is a GNU extension.

   gnu-attributes:
خالی
     gnu-attributes gnu-attribute

   gnu-attribute:
     __attribute__ ( ( gnu-attribute-list ) )

   gnu-attribute-list:
     gnu-attrib
     gnu-attribute_list , gnu-attrib

   gnu-attrib:
خالی
     any-word
     any-word ( gnu-attribute-arguments )

   where "any-word" may be any identifier (including one declared as a
   type), a reserved word storage class specifier, type specifier or
   type qualifier.  ??? This still leaves out most reserved keywords
   (following the old parser), shouldn't we include them?
   When EXPECT_COMMA is true, expect the attribute to be preceded
   by a comma and fail if it isn't.
   When EMPTY_OK is true, allow and consume any number of consecutive
   commas with no attributes in between.  */

ساكن درخت
c_parser_gnu_attribute (c_parser *parser, درخت attrs,
			منطقي expect_comma = خطأ, منطقي خالی_ok = درست)
{
  منطقي comma_اولی = c_parser_بعدی_token_is (parser, CPP_COMMA);
  إذا (!comma_اولی
      && !c_parser_بعدی_token_is (parser, CPP_NAME)
      && !c_parser_بعدی_token_is (parser, CPP_KEYWORD))
    أرجع NULL_درخت;

  طالما (c_parser_بعدی_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (!خالی_ok)
	أرجع attrs;
    }

  درخت attr_name = c_parser_gnu_attribute_any_کلمه (parser);
  إذا (attr_name == NULL_درخت)
    أرجع NULL_درخت;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  درخت attr;
  إذا (c_parser_بعدی_token_is_not (parser, CPP_OPEN_PAREN))
    {
      إذا (expect_comma && !comma_اولی)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع error_mark_گره;
	}
      attr = build_درخت_list (attr_name, NULL_درخت);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      أرجع attrs;
    }
  c_parser_consume_token (parser);

  درخت attr_آرگومانها
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    خطأ,
				    is_attribute_p ("assume", attr_name),
				    درست);

  attr = build_درخت_list (attr_name, attr_آرگومانها);
  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع error_mark_گره;
    }

  إذا (expect_comma && !comma_اولی)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع error_mark_گره;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  أرجع attrs;
}

ساكن درخت
c_parser_gnu_صفات (c_parser *parser)
{
  درخت attrs = NULL_درخت;
  طالما (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      منطقي save_translate_رشتهها_p = parser->translate_رشتهها_p;
      parser->translate_رشتهها_p = خطأ;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_رشتهها_p = save_translate_رشتهها_p;
	  أرجع attrs;
	}
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_رشتهها_p = save_translate_رشتهها_p;
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      لكل (منطقي expect_comma = خطأ; ; expect_comma = درست)
	{
	  /* Parse a single attribute.  */
	  درخت attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  إذا (attr == error_mark_گره)
	    أرجع attrs;
	  إذا (!attr)
	    اكسر;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      وإلا
	{
	  parser->translate_رشتهها_p = save_translate_رشتهها_p;
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع attrs;
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      وإلا
	{
	  parser->translate_رشتهها_p = save_translate_رشتهها_p;
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع attrs;
	}
      parser->translate_رشتهها_p = save_translate_رشتهها_p;
    }

  أرجع attrs;
}

/* Parse an optional balanced token sequence.

   balanced-token-sequence:
     balanced-token
     balanced-token-sequence balanced-token

   balanced-token:
     ( balanced-token-sequence[opt] )
     [ balanced-token-sequence[opt] ]
     { balanced-token-sequence[opt] }
     any token other than ()[]{}
*/

ساكن فراغ
c_parser_متوازن_token_sequence (c_parser *parser)
{
  طالما (درست)
    {
      c_token *token = c_parser_peek_token (parser);
      بدل (token->type)
	{
	حالة CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_متوازن_token_sequence (parser);
	    braces.require_close (parser);
	    اكسر;
	  }

	حالة CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_متوازن_token_sequence (parser);
	    parens.require_close (parser);
	    اكسر;
	  }

	حالة CPP_OPEN_مربع:
	  c_parser_consume_token (parser);
	  c_parser_متوازن_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_مربع, "expected %<]%>");
	  اكسر;

	حالة CPP_CLOSE_BRACE:
	حالة CPP_CLOSE_PAREN:
	حالة CPP_CLOSE_مربع:
	حالة CPP_EOF:
	  أرجع;

	حالة CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  اكسر;

	افتراضي:
	  c_parser_consume_token (parser);
	  اكسر;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

ساكن فراغ
c_parser_omp_directive_آرگومانها (c_parser *parser, درخت attribute, منطقي decl_p)
{
  بیعلامت صحيح n = 1;
  c_token *اولی = c_parser_peek_token (parser);
  إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_متوازن_token_sequence (parser);
      درخت_مقدار (attribute) = NULL_درخت;
      أرجع;
    }
  إذا (n == 1)
    {
      error_at (اولی->location, "expected OpenMP directive name");
      درخت_مقدار (attribute) = NULL_درخت;
      أرجع;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  لكل (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->سریع_افزودن (*tok);
      c_parser_consume_token (parser);
    }
  درخت arg = make_گره (C_TOKEN_VEC);
  C_TOKEN_VEC_نشانهها (arg) = v;
  إذا (decl_p)
    درخت_عمومی (arg) = 1;
  درخت_مقدار (attribute) = درخت_cons (NULL_درخت, arg, درخت_مقدار (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

ساكن فراغ
c_parser_omp_sequence_آرگومانها (c_parser *parser, درخت attribute)
{
  افعل
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_اشاره_گر (token->مقدار), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      منطقي directive = خطأ;
      ثابت حرف *p;
      إذا (token->type != CPP_NAME)
	p = "";
      وإلا
	p = IDENTIFIER_اشاره_گر (token->مقدار);
      إذا (strcmp (p, "directive") == 0)
	directive = درست;
      وإلا إذا (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  بیعلامت nesting_عمق = 0;

	  طالما (درست)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      إذا ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_عمق)
		اكسر;
	      /* If we've run out of tokens, stop.  */
	      إذا (token->type == CPP_EOF)
		اكسر;
	      إذا (token->type == CPP_PRAGMA_EOL && parser->درون_pragma)
		اكسر;
	      إذا (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_مربع)
		++nesting_عمق;
	      وإلا إذا (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_مربع)
		{
		  إذا (nesting_عمق-- == 0)
		    اكسر;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	  استمر;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      إذا (parens.require_open (parser))
	{
	  إذا (directive)
	    c_parser_omp_directive_آرگومانها (parser, attribute, خطأ);
	  وإلا
	    c_parser_omp_sequence_آرگومانها (parser, attribute);
	  parens.skip_until_یافت_close (parser);
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (c_parser_بعدی_token_is_not (parser, CPP_COMMA))
	اكسر;
      وإلا
	c_parser_consume_token (parser);
    }
  طالما (1);
}

/* Parse standard (C23) attributes (including GNU attributes in the
   gnu:: namespace).

   attribute-specifier-sequence:
     attribute-specifier-sequence[opt] attribute-specifier

   attribute-specifier:
     [ [ attribute-list ] ]

   attribute-list:
     attribute[opt]
     attribute-list, attribute[opt]

   attribute:
     attribute-token attribute-argument-clause[opt]

   attribute-token:
     standard-attribute
     attribute-prefixed-token

   standard-attribute:
     identifier

   attribute-prefixed-token:
     attribute-prefix :: identifier

   attribute-prefix:
     identifier

   attribute-argument-clause:
     ( balanced-token-sequence[opt] )

   Keywords are accepted as identifiers for this purpose.

   As an extension, we permit an attribute-specifier to be:

     [ [ __extension__ attribute-list ] ]

   Two colons are then accepted as a synonym for ::.  No attempt is made
   to check whether the colons are immediately adjacent.  LOOSE_SCOPE_P
   indicates whether this relaxation is in effect.  */

ساكن درخت
c_parser_std_attribute (c_parser *parser, منطقي for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  درخت ns, name, attribute;

  /* Parse the attribute-token.  */
  إذا (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      أرجع error_mark_گره;
    }
  name = canonicalize_attr_name (token->مقدار);
  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_SCOPE)
      || (c_parser_بعدی_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      إذا (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع error_mark_گره;
	}
      name = canonicalize_attr_name (token->مقدار);
      c_parser_consume_token (parser);
    }
  وإلا
    ns = NULL_درخت;
  attribute = build_درخت_list (build_درخت_list (ns, name), NULL_درخت);

  /* Parse the arguments, if any.  */
  ثابت attribute_spec *as = lookup_attribute_spec (درخت_PURPOSE (attribute));
  إذا (c_parser_بعدی_token_is_not (parser, CPP_OPEN_PAREN))
    {
      إذا ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  أرجع error_mark_گره;
	}
      اذهب بیرون;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    إذا ((as && as->max_درازی == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_یافت_close (parser);
	أرجع error_mark_گره;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    إذا (as && !attribute_ignored_p (as))
      {
	منطقي takes_identifier
	  = (ns != NULL_درخت
	     && strcmp (IDENTIFIER_اشاره_گر (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	منطقي require_string
	  = (ns == NULL_درخت
	     && (strcmp (IDENTIFIER_اشاره_گر (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_اشاره_گر (name), "nodiscard") == 0));
	منطقي assume_attr
	  = (ns != NULL_درخت
	     && strcmp (IDENTIFIER_اشاره_گر (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_اشاره_گر (name), "assume") == 0);
	درخت_مقدار (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, خطأ);
      }
    وإلا
      {
	إذا ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    إذا (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_آرگومانها (parser, attribute, خطأ);
		parens.skip_until_یافت_close (parser);
		أرجع attribute;
	      }
	    وإلا إذا (is_attribute_p ("decl", name))
	      {
		درخت_مقدار (درخت_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_آرگومانها (parser, attribute, درست);
		parens.skip_until_یافت_close (parser);
		أرجع attribute;
	      }
	    وإلا إذا (is_attribute_p ("sequence", name))
	      {
		درخت_مقدار (درخت_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_آرگومانها (parser, attribute);
		parens.skip_until_یافت_close (parser);
		درخت_مقدار (attribute) = nreverse (درخت_مقدار (attribute));
		أرجع attribute;
	      }
	  }
	c_parser_متوازن_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 بیرون:
  إذا (ns == NULL_درخت && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (درون_داد_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      أرجع error_mark_گره;
    }
  أرجع attribute;
}

ساكن درخت
c_parser_std_attribute_list (c_parser *parser, منطقي for_tm)
{
  درخت صفات = NULL_درخت;
  طالما (درست)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_CLOSE_مربع)
	اكسر;
      إذا (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      درخت attribute = c_parser_std_attribute (parser, for_tm);
      إذا (attribute != error_mark_گره)
	{
	  درخت_CHAIN (attribute) = صفات;
	  صفات = attribute;
	}
      إذا (c_parser_بعدی_token_is_not (parser, CPP_COMMA))
	اكسر;
    }
  أرجع صفات;
}

ساكن درخت
c_parser_std_attribute_specifier (c_parser *parser, منطقي for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_مربع, "expected %<[%>"))
    أرجع NULL_درخت;
  إذا (!c_parser_require (parser, CPP_OPEN_مربع, "expected %<[%>"))
    {
      c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع, "expected %<]%>");
      أرجع NULL_درخت;
    }
  درخت صفات;
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_EXTENSION))
    {
      خودکار ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      صفات = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  وإلا
    {
      إذا (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      صفات = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع, "expected %<]%>");
  c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع, "expected %<]%>");
  أرجع nreverse (صفات);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

ساكن منطقي
c_parser_check_متوازن_raw_token_sequence (c_parser *parser, بیعلامت صحيح *n)
{
  طالما (درست)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      بدل (token->type)
	{
	حالة CPP_OPEN_BRACE:
	  {
	    ++*n;
	    إذا (c_parser_check_متوازن_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		إذا (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		وإلا
		  أرجع خطأ;
	      }
	    وإلا
	      أرجع خطأ;
	    اكسر;
	  }

	حالة CPP_OPEN_PAREN:
	  {
	    ++*n;
	    إذا (c_parser_check_متوازن_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		إذا (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		وإلا
		  أرجع خطأ;
	      }
	    وإلا
	      أرجع خطأ;
	    اكسر;
	  }

	حالة CPP_OPEN_مربع:
	  {
	    ++*n;
	    إذا (c_parser_check_متوازن_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		إذا (token->type == CPP_CLOSE_مربع)
		  ++*n;
		وإلا
		  أرجع خطأ;
	      }
	    وإلا
	      أرجع خطأ;
	    اكسر;
	  }

	حالة CPP_CLOSE_BRACE:
	حالة CPP_CLOSE_PAREN:
	حالة CPP_CLOSE_مربع:
	حالة CPP_EOF:
	  أرجع درست;

	افتراضي:
	  ++*n;
	  اكسر;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

ساكن منطقي
c_parser_nth_token_starts_std_صفات (c_parser *parser, بیعلامت صحيح n)
{
  إذا (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_مربع
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_مربع))
    أرجع خطأ;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  إذا (!c_dialect_objc ())
    أرجع درست;
  n += 2;
  إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &n))
    أرجع خطأ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  إذا (token->type != CPP_CLOSE_مربع)
    أرجع خطأ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  أرجع token->type == CPP_CLOSE_مربع;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

ساكن اندازه_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, اندازه_t n)
{
  اندازه_t orig_n = n;
  طالما (درست)
    {
      إذا (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_مربع
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_مربع))
	{
	  بیعلامت صحيح m = n + 2;
	  إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &m))
	    أرجع orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  إذا (token->type != CPP_CLOSE_مربع)
	    أرجع orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  إذا (token->type != CPP_CLOSE_مربع)
	    أرجع orig_n;
	  n = m + 2;
	}
      وإلا
	اكسر;
    }
  أرجع n;
}

ساكن درخت
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  درخت صفات = NULL_درخت;
  افعل
    {
      درخت attrs = c_parser_std_attribute_specifier (parser, خطأ);
      صفات = chainon (صفات, attrs);
    }
  طالما (c_parser_nth_token_starts_std_صفات (parser, 1));
  أرجع صفات;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

بنية c_type_name *
c_parser_type_name (c_parser *parser, منطقي alignas_ok)
{
  بنية c_declspecs *specs = build_null_declspecs ();
  بنية c_declarator *declarator;
  بنية c_type_name *ret;
  منطقي dummy = خطأ;
  c_parser_declspecs (parser, specs, خطأ, درست, درست, alignas_ok, خطأ,
		      خطأ, درست, cla_prefer_type);
  إذا (!specs->declspecs_دیده_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      أرجع عدم;
    }
  إذا (specs->type != error_mark_گره)
    {
      pending_xref_error ();
      پایان_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      إذا (specs->typespec_نوع == ctsk_tagdef)
	verify_counted_by_for_بالاترین_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_نوع != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  إذا (declarator == عدم)
    أرجع عدم;
  ret = XOBNEW (&parser_obstack, بنية c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  أرجع ret;
}

/* Parse an initializer (C90 6.5.7, C99 6.7.8, C11 6.7.9).

   initializer:
     assignment-expression
     { initializer-list }
     { initializer-list , }

   initializer-list:
     designation[opt] initializer
     initializer-list , designation[opt] initializer

   designation:
     designator-list =

   designator-list:
     designator
     designator-list designator

   designator:
     array-designator
     . identifier

   array-designator:
     [ constant-expression ]

   GNU extensions:

   initializer:
     { }

   designation:
     array-designator
     identifier :

   array-designator:
     [ constant-expression ... constant-expression ]

   Any expression without commas is accepted in the syntax for the
   constant-expressions, with non-constant expressions rejected later.

   DECL is the declaration we're parsing this initializer for.

   This function is only used for top-level initializers; for nested
   ones, see c_parser_initval.  */

ساكن بنية c_عبارت
c_parser_initializer (c_parser *parser, درخت decl)
{
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    أرجع c_parser_braced_init (parser, NULL_درخت, خطأ, عدم,
				 decl != error_mark_گره
				 && C_DECL_VARIABLE_اندازه (decl));
  وإلا
    {
      بنية c_عبارت ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_عبارت_no_commas (parser, عدم);
      إذا (decl != error_mark_گره && C_DECL_VARIABLE_اندازه (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.مجموعه_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      إذا (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !درخت_STATIC (decl)
	  && ret.مقدار == decl
	  && !warning_enabled_at (DECL_منبع_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      إذا (درخت_کد (ret.مقدار) != STRING_CST
	  && (درخت_کد (ret.مقدار) != COMPOUND_LITERAL_عبارت
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_عبارت_DECL
					    (ret.مقدار))))
	ret = convert_lvalue_مقصد_rvalue (loc, ret, درست, درست, درست);
      أرجع ret;
    }
}

/* The location of the last comma within the current initializer list,
   or UNKNOWN_LOCATION if not within one.  */

location_t آخرین_init_list_comma;

/* Parse a braced initializer list.  TYPE is the type specified for a
   compound literal, and NULL_TREE for other initializers and for
   nested braced lists.  NESTED_P is true for nested braced lists,
   false for the list of a compound literal or the list that is the
   top-level initializer in a declaration.  VARSIZE_P indicates
   whether the object to be initialized has a variable size.  */

ساكن بنية c_عبارت
c_parser_braced_init (c_parser *parser, درخت type, منطقي nested_p,
		      بنية obstack *outer_obstack, منطقي varsize_p)
{
  بنية c_عبارت ret;
  بنية obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE));
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = خطأ;
  منطقي zero_init_padding_بیتها = خطأ;
  matching_braces braces;
  braces.consume_open (parser);
  إذا (nested_p)
    {
      پایان_implicit_inits (brace_loc, outer_obstack);
      افزودن_init_level (brace_loc, 0, &braced_init_obstack);
    }
  وإلا
    really_شروع_incremental_init (type);
  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      إذا (flag_isoc23)
	zero_init_padding_بیتها = درست;
    }
  وإلا
    {
      إذا (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      طالما (درست)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  إذا (parser->error)
	    اكسر;
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    {
	      آخرین_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      طالما (c_parser_بعدی_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_عبارت embed_val;
		  embed_val.مقدار = embed->مقدار;
		  embed_val.original_کد = RAW_داده_CST;
		  embed_val.original_type = integer_type_گره;
		  مجموعه_c_عبارت_منبع_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, خطأ,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_بعدی_token_is (parser,
							       CPP_COMMA));
		  آخرین_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  وإلا
	    اكسر;
	  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	    اكسر;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *بعدی_tok = c_parser_peek_token (parser);
  إذا (بعدی_tok->type != CPP_CLOSE_BRACE)
    {
      ret.مجموعه_error ();
      ret.original_کد = ERROR_MARK;
      ret.original_type = عدم;
      braces.skip_until_یافت_close (parser);
      برداشت_init_level (brace_loc, 0, &braced_init_obstack, آخرین_init_list_comma);
      obstack_free (&braced_init_obstack, عدم);
      أرجع ret;
    }
  location_t close_loc = بعدی_tok->location;
  c_parser_consume_token (parser);
  ret = برداشت_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  إذا (zero_init_padding_بیتها
      && ret.مقدار
      && درخت_کد (ret.مقدار) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_بیتها (ret.مقدار) = 1;
  obstack_free (&braced_init_obstack, عدم);
  مجموعه_c_عبارت_منبع_range (&ret, brace_loc, close_loc);
  أرجع ret;
}

/* Parse a nested initializer, including designators.  */

ساكن فراغ
c_parser_initelt (c_parser *parser, بنية obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      مجموعه_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->مقدار,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  وإلا
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      صحيح des_دیده = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      طالما (c_parser_بعدی_token_is (parser, CPP_OPEN_مربع)
	     || c_parser_بعدی_token_is (parser, CPP_DOT))
	{
	  صحيح des_prev = des_دیده;
	  إذا (!des_دیده)
	    des_loc = c_parser_peek_token (parser)->location;
	  إذا (des_دیده < 2)
	    des_دیده++;
	  إذا (c_parser_بعدی_token_is (parser, CPP_DOT))
	    {
	      des_دیده = 2;
	      c_parser_consume_token (parser);
	      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		{
		  مجموعه_init_label (des_loc, c_parser_peek_token (parser)->مقدار,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      وإلا
		{
		  بنية c_عبارت init;
		  init.مجموعه_error ();
		  init.original_کد = ERROR_MARK;
		  init.original_type = عدم;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_یافت (parser, CPP_COMMA, عدم);
		  process_init_element (درون_داد_location, init, خطأ,
					braced_init_obstack);
		  أرجع;
		}
	    }
	  وإلا
	    {
	      بنية c_عبارت اولی_عبارت;
	      درخت اولی, دومی;
	      location_t ellipsis_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	      location_t array_شاخص_loc = UNKNOWN_LOCATION;
	      /* ??? Following the old parser, [ objc-receiver
		 objc-message-args ] is accepted as an initializer,
		 being distinguished from a designator by what follows
		 the first assignment expression inside the square
		 brackets, but after a first array designator a
		 subsequent square bracket is for Objective-C taken to
		 start an expression, using the obsolete form of
		 designated initializer without '=', rather than
		 possibly being a second level of designation: in LALR
		 terms, the '[' is shifted rather than reducing
		 designator to designator-list.  */
	      إذا (des_prev == 1 && c_dialect_objc ())
		{
		  des_دیده = des_prev;
		  اكسر;
		}
	      إذا (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  درخت rec, آرگومانها;
		  بنية c_عبارت mexpr;
		  c_parser_consume_token (parser);
		  إذا (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_نوع
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_نوع
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      درخت id = c_parser_peek_token (parser)->مقدار;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      اذهب parse_پیام_آرگومانها;
		    }
		  array_شاخص_loc = c_parser_peek_token (parser)->location;
		  اولی_عبارت = c_parser_عبارت_no_commas (parser, عدم);
		  mark_exp_read (اولی_عبارت.مقدار);
		  إذا (c_parser_بعدی_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_بعدی_token_is (parser, CPP_CLOSE_مربع))
		    اذهب array_desig_after_اولی;
		  اولی = اولی_عبارت.مقدار;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = اولی;
		  طالما (c_parser_بعدی_token_is (parser, CPP_COMMA))
		    {
		      بنية c_عبارت بعدی;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      بعدی = c_parser_عبارت_no_commas (parser, عدم);
		      بعدی = convert_lvalue_مقصد_rvalue (exp_loc, بعدی,
						       درست, درست);
		      rec = build_compound_عبارت (comma_loc, rec, بعدی.مقدار);
		    }
		parse_پیام_آرگومانها:
		  /* Now parse the objc-message-args.  */
		  آرگومانها = c_parser_objc_پیام_آرگومانها (parser);
		  c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع,
					     "expected %<]%>");
		  mexpr.مقدار
		    = objc_build_پیام_عبارت (rec, آرگومانها);
		  mexpr.original_کد = ERROR_MARK;
		  mexpr.original_type = عدم;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  أرجع;
		}
	      c_parser_consume_token (parser);
	      array_شاخص_loc = c_parser_peek_token (parser)->location;
	      اولی_عبارت = c_parser_عبارت_no_commas (parser, عدم);
	      mark_exp_read (اولی_عبارت.مقدار);
	    array_desig_after_اولی:
	      اولی_عبارت = convert_lvalue_مقصد_rvalue (array_شاخص_loc,
						     اولی_عبارت,
						     درست, درست);
	      اولی = اولی_عبارت.مقدار;
	      إذا (c_parser_بعدی_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  دومی = convert_lvalue_مقصد_rvalue (ellipsis_loc,
						     (c_parser_عبارت_no_commas
						      (parser, عدم)),
						     درست, درست).مقدار;
		  mark_exp_read (دومی);
		}
	      وإلا
		دومی = NULL_درخت;
	      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_مربع))
		{
		  c_parser_consume_token (parser);
		  مجموعه_init_شاخص (array_شاخص_loc, اولی, دومی,
				  braced_init_obstack);
		  إذا (دومی)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      وإلا
		c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع,
					   "expected %<]%>");
	    }
	}
      إذا (des_دیده >= 1)
	{
	  إذا (c_parser_بعدی_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      إذا (des_دیده == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      وإلا
		{
		  بنية c_عبارت init;
		  init.مجموعه_error ();
		  init.original_کد = ERROR_MARK;
		  init.original_type = عدم;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_یافت (parser, CPP_COMMA, عدم);
		  process_init_element (درون_داد_location, init, خطأ,
					braced_init_obstack);
		  أرجع;
		}
	    }
	}
    }
  c_parser_initval (parser, عدم, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

ساكن فراغ
c_parser_initval (c_parser *parser, بنية c_عبارت *after,
		  بنية obstack * braced_init_obstack)
{
  بنية c_عبارت init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_درخت, درست,
				 braced_init_obstack, خطأ);
  وإلا
    {
      init = c_parser_عبارت_no_commas (parser, after);
      إذا (init.مقدار != NULL_درخت
	  && درخت_کد (init.مقدار) != STRING_CST
	  && (درخت_کد (init.مقدار) != COMPOUND_LITERAL_عبارت
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_عبارت_DECL
					    (init.مقدار))))
	init = convert_lvalue_مقصد_rvalue (loc, init, درست, درست, درست);
    }
  درخت val = init.مقدار;
  process_init_element (loc, init, خطأ, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  ساكن بیعلامت vals_مقصد_ignore;
  إذا (vals_مقصد_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_مقصد_ignore;
  وإلا إذا (val
	   && درخت_کد (val) == INTEGER_CST
	   && درخت_TYPE (val) == integer_type_گره
	   && c_parser_بعدی_token_is (parser, CPP_COMMA))
    إذا (بیعلامت صحيح len = c_maybe_optimize_large_byte_initializer ())
      {
	حرف buf1[64];
	بیعلامت صحيح i;
	gcc_checking_assert (len >= 64);
	location_t آخرین_loc = UNKNOWN_LOCATION;
	لكل (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    إذا (tok->type != CPP_COMMA)
	      اكسر;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    إذا (tok->type != CPP_عدد
		|| درخت_کد (tok->مقدار) != INTEGER_CST
		|| درخت_TYPE (tok->مقدار) != integer_type_گره
		|| wi::neg_p (wi::مقصد_wide (tok->مقدار))
		|| wi::مقصد_widest (tok->مقدار) > UCHAR_MAX)
	      اكسر;
	    buf1[i] = (حرف) درخت_مقصد_uhwi (tok->مقدار);
	    إذا (i == 0)
	      loc = tok->location;
	    آخرین_loc = tok->location;
	  }
	إذا (i < 64)
	  {
	    vals_مقصد_ignore = i;
	    أرجع;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	إذا (tok->type == CPP_CLOSE_BRACE && len != بیشترین_صحیح)
	  len = i;
	وإلا إذا (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_عدد))
	  {
	    vals_مقصد_ignore = i;
	    أرجع;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	بیعلامت صحيح max_len = 131072 - offsetof (بنية درخت_string, str) - 1;
	بیعلامت صحيح orig_len = len;
	بیعلامت صحيح off = 0, آخرین = 0;
	إذا (!wi::neg_p (wi::مقصد_wide (val)) && wi::مقصد_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	حرف *buf2 = XNEWVEC (حرف, len + off);
	إذا (off)
	  buf2[0] = (حرف) درخت_مقصد_uhwi (val);
	کپی_حافظه (buf2 + off, buf1, i);
	لكل (بیعلامت صحيح j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	لكل (; i < len; ++i)
	  {
	    إذا (!c_parser_بعدی_token_is (parser, CPP_COMMA))
	      اكسر;
	    tok = c_parser_peek_2nd_token (parser);
	    إذا (tok->type != CPP_عدد
		|| درخت_کد (tok->مقدار) != INTEGER_CST
		|| درخت_TYPE (tok->مقدار) != integer_type_گره
		|| wi::neg_p (wi::مقصد_wide (tok->مقدار))
		|| wi::مقصد_widest (tok->مقدار) > UCHAR_MAX)
	      اكسر;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    إذا (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      اكسر;
	    buf2[i + off] = (حرف) درخت_مقصد_uhwi (tok->مقدار);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    إذا (orig_len == بیشترین_صحیح
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_عدد)))
	      {
		آخرین = 1;
		اكسر;
	      }
	    آخرین_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_گره (RAW_داده_CST);
	درخت_TYPE (val) = integer_type_گره;
	RAW_داده_درازی (val) = i;
	درخت owner = build_string (i + off + آخرین, buf2);
	XDELETEVEC (buf2);
	درخت_TYPE (owner) = build_array_type_nelts (unsigned_char_type_گره,
						    i + off + آخرین);
	RAW_داده_OWNER (val) = owner;
	RAW_داده_اشاره_گر (val) = درخت_STRING_اشاره_گر (owner) + off;
	init.مقدار = val;
	مجموعه_c_عبارت_منبع_range (&init, loc, آخرین_loc);
	init.original_کد = RAW_داده_CST;
	init.original_type = integer_type_گره;
	init.m_decimal = 0;
	process_init_element (loc, init, خطأ, braced_init_obstack);
      }
}

/* Parse a compound statement (possibly a function body) (C90 6.6.2,
   C99 6.8.2, C11 6.8.2, C23 6.8.2).

   compound-statement:
     { block-item-list[opt] }
     { label-declarations block-item-list }

   block-item-list:
     block-item
     block-item-list block-item

   block-item:
     label
     nested-declaration
     statement

   nested-declaration:
     declaration

   GNU extensions:

   compound-statement:
     { label-declarations block-item-list }

   nested-declaration:
     __extension__ nested-declaration
     nested-function-definition

   label-declarations:
     label-declaration
     label-declarations label-declaration

   label-declaration:
     __label__ identifier-list ;

   Allowing the mixing of declarations and code is new in C99.  The
   GNU syntax also permits (not shown above) labels at the end of
   compound statements, which yield an error.  We don't allow labels
   on declarations; this might seem like a natural extension, but
   there would be a conflict between gnu-attributes on the label and
   prefix gnu-attributes on the declaration.  ??? The syntax follows the
   old parser in requiring something after label declarations.
   Although they are erroneous if the labels declared aren't defined,
   is it useful for the syntax to be this way?

   OpenACC:

   block-item:
     openacc-directive

   openacc-directive:
     update-directive

   OpenMP:

   block-item:
     openmp-directive

   openmp-directive:
     barrier-directive
     flush-directive
     taskwait-directive
     taskyield-directive
     cancel-directive
     cancellation-point-directive  */

ساكن درخت
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  درخت stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (درست);
      c_انتها_compound_stmt (brace_loc, stmt, درست);
      أرجع error_mark_گره;
    }
  stmt = c_begin_compound_stmt (درست);
  location_t انتها_loc = c_parser_compound_statement_nostart (parser);
  إذا (endlocp)
    *endlocp = انتها_loc;

  أرجع c_انتها_compound_stmt (brace_loc, stmt, درست);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

ساكن فراغ
check_omp_intervening_کد (c_parser *parser)
{
  بنية omp_for_parse_داده *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  إذا (!omp_for_parse_state->درون_intervening_کد)
    أرجع;
  omp_for_parse_state->saw_intervening_کد = درست;

  /* Only diagnose errors related to perfect nesting once.  */
  إذا (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      إذا (omp_for_parse_state->کد == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = درست;
	}
      وإلا إذا (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = درست;
	}
      وإلا إذا (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = درست;
	}
      وإلا إذا (omp_for_parse_state->کد == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = درست;
	}
      إذا (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = درست;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
ساكن فراغ
جمع_کن_structured_بلوک_stmt (درخت sl)
{
  إذا (درخت_کد (sl) != STATEMENT_LIST
      || !tsi_انتها_p (tsi_شروع (sl)))
    جمع_کن_stmt (build1 (OMP_STRUCTURED_بلوک, void_type_گره, sl));
}

بنية c_omp_attribute_داده
{
  vec<c_token, va_gc> *نشانهها;
  ثابت c_omp_directive *dir;
  c_omp_directive_نوع نوع;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

ساكن منطقي
c_parser_handle_statement_omp_صفات (c_parser *parser, درخت &attrs,
					  منطقي *have_std_attrs)
{
  إذا (!flag_openmp && !flag_openmp_simd)
    أرجع خطأ;

  auto_vec<c_omp_attribute_داده, 16> vd;
  صحيح cnt = 0;
  صحيح نشانهها = 0;
  منطقي bad = خطأ;
  لكل (درخت *pa = &attrs; *pa; )
    إذا (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	لكل (درخت a = درخت_مقدار (*pa); a; a = درخت_CHAIN (a))
	  {
	    درخت d = درخت_مقدار (a);
	    gcc_assert (درخت_کد (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_نشانهها (d);
	    c_token *اولی = toks->آدرس ();
	    c_token *آخرین = اولی + toks->درازی ();
	    إذا (parser->omp_attrs_forbidden_p)
	      {
		error_at (اولی->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = خطأ;
		bad = درست;
	      }
	    وإلا إذا (درخت_عمومی (d))
	      {
		error_at (اولی->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = درست;
	      }
	    ثابت حرف *directive[3] = {};
	    لكل (صحيح i = 0; i < 3; i++)
	      {
		درخت id = NULL_درخت;
		إذا (اولی + i == آخرین)
		  اكسر;
		إذا (اولی[i].type == CPP_NAME)
		  id = اولی[i].مقدار;
		وإلا إذا (اولی[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحيح) اولی[i].keyword];
		وإلا
		  اكسر;
		directive[i] = IDENTIFIER_اشاره_گر (id);
	      }
	    ثابت c_omp_directive *dir = عدم;
	    إذا (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    إذا (dir == عدم)
	      {
		error_at (اولی->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  درخت_عمومی (d) ? "omp::decl" : "omp::directive");
		استمر;
	      }
	    c_omp_directive_نوع نوع = dir->نوع;
	    إذا (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		إذا (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  نوع = C_OMP_DIR_STANDALONE;
		وإلا إذا (اولی + 2 < آخرین
			 && اولی[1].type == CPP_COMMA
			 && اولی[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_اشاره_گر (اولی[2].مقدار),
				     "depend") == 0
			     || strcmp (IDENTIFIER_اشاره_گر (اولی[2].مقدار),
					"doacross") == 0))
		  نوع = C_OMP_DIR_STANDALONE;
	      }
	    وإلا إذا (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		صحيح paren_عمق = 0;
		لكل (صحيح i = 1; اولی + i < آخرین; i++)
		  إذا (اولی[i].type == CPP_OPEN_PAREN)
		    paren_عمق++;
		  وإلا إذا (اولی[i].type == CPP_CLOSE_PAREN)
		    paren_عمق--;
		  وإلا إذا (paren_عمق == 0
			   && اولی + i + 2 < آخرین
			   && اولی[i].type == CPP_NAME
			   && اولی[i + 1].type == CPP_OPEN_PAREN
			   && اولی[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_اشاره_گر (اولی[i].مقدار),
				       "at")
			   && !strcmp (IDENTIFIER_اشاره_گر (اولی[i
								 + 2].مقدار),
				       "execution"))
		    {
		      نوع = C_OMP_DIR_STANDALONE;
		      اكسر;
		    }
	      }
	    c_omp_attribute_داده v = { toks, dir, نوع };
	    vd.امن_افزودن (v);
	    إذا (flag_openmp || dir->simd)
	      نشانهها += (آخرین - اولی) + 1;
	  }
	c_omp_attribute_داده v = {};
	vd.امن_افزودن (v);
	*pa = درخت_CHAIN (*pa);
      }
    وإلا
      pa = &درخت_CHAIN (*pa);

  إذا (bad)
    {
    fail:
      إذا (have_std_attrs && attrs == عدم)
	*have_std_attrs = خطأ;
      أرجع خطأ;
    }

  بیعلامت صحيح i;
  c_omp_attribute_داده *v;
  c_omp_attribute_داده *construct_دیده = اشاره_تهی;
  c_omp_attribute_داده *standalone_دیده = اشاره_تهی;
  c_omp_attribute_داده *prev_standalone_دیده = اشاره_تهی;
  FOR_EACH_VEC_ELT (vd, i, v)
    إذا (v->نشانهها)
      {
	إذا (v->نوع == C_OMP_DIR_CONSTRUCT && !construct_دیده)
	  construct_دیده = v;
	وإلا إذا (v->نوع == C_OMP_DIR_STANDALONE && !standalone_دیده)
	  standalone_دیده = v;
      }
    وإلا
      {
	إذا (standalone_دیده && !prev_standalone_دیده)
	  {
	    prev_standalone_دیده = standalone_دیده;
	    standalone_دیده = اشاره_تهی;
	  }
      }

  إذا (cnt > 1 && construct_دیده)
    {
      error_at ((*construct_دیده->نشانهها)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      اذهب fail;
    }
  إذا (cnt > 1 && standalone_دیده && prev_standalone_دیده)
    {
      error_at ((*standalone_دیده->نشانهها)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      اذهب fail;
    }

  إذا (prev_standalone_دیده)
    standalone_دیده = prev_standalone_دیده;
  إذا (standalone_دیده
      && !c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_دیده->نشانهها->آدرس ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      اذهب fail;
    }
  إذا (cnt && c_parser_بعدی_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      تعداد pragma_نوع نوع = token->pragma_نوع;
      إذا (نوع >= PRAGMA_OMP_شروع && نوع <= PRAGMA_OMP_آخرین)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  اذهب fail;
	}
    }

  إذا (!نشانهها)
    أرجع خطأ;

  بیعلامت صحيح نشانهها_avail = parser->نشانهها_avail;

  نشانهها++;
  vec<c_token, va_gc> *toks = عدم;
  vec_امن_reserve (toks, نشانهها, درست);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      إذا (!v->نشانهها)
	استمر;
      إذا (!flag_openmp && !v->dir->simd)
	استمر;
      c_token *اولی = v->نشانهها->آدرس ();
      c_token *آخرین = اولی + v->نشانهها->درازی ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_نوع = pragma_نوع (v->dir->id);
      tok.location = اولی->location;
      toks->سریع_افزودن (tok);
      طالما (++اولی < آخرین)
	toks->سریع_افزودن (*اولی);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = آخرین[-1].location;
      toks->سریع_افزودن (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->آخرین ().location;
  toks->سریع_افزودن (tok);

  gcc_assert (!parser->درون_omp_attribute_pragma);
  parser->درون_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->درون_omp_attribute_pragma->token_vec = toks;
  parser->درون_omp_attribute_pragma->save_نشانهها = parser->نشانهها;
  parser->درون_omp_attribute_pragma->save_نشانهها_avail = نشانهها_avail;
  parser->نشانهها = toks->آدرس ();
  parser->نشانهها_avail = نشانهها;
  أرجع درست;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

ساكن فراغ
c_parser_handle_directive_omp_صفات (درخت &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  إذا (!flag_openmp && !flag_openmp_simd)
    أرجع;

  لكل (درخت *pa = &attrs; *pa; )
    إذا (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	صحيح cnt = 0;
	لكل (درخت *pa2 = &درخت_مقدار (*pa); *pa2; )
	  {
	    درخت a = *pa2;
	    درخت d = درخت_مقدار (a);
	    gcc_assert (درخت_کد (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_نشانهها (d);
	    c_token *اولی = toks->آدرس ();
	    c_token *آخرین = اولی + toks->درازی ();
	    ثابت حرف *directive[3] = {};
	    لكل (صحيح i = 0; i < 3; i++)
	      {
		درخت id = NULL_درخت;
		إذا (اولی + i == آخرین)
		  اكسر;
		إذا (اولی[i].type == CPP_NAME)
		  id = اولی[i].مقدار;
		وإلا إذا (اولی[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحيح) اولی[i].keyword];
		وإلا
		  اكسر;
		directive[i] = IDENTIFIER_اشاره_گر (id);
	      }
	    ثابت c_omp_directive *dir = عدم;
	    إذا (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    إذا (dir == عدم)
	      {
		error_at (اولی->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  درخت_عمومی (d) ? "omp::decl" : "omp::directive");
		*pa2 = درخت_CHAIN (a);
	      }
	    وإلا إذا (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		إذا (pragma_clauses)
		  {
		    error_at (اولی->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    لكل (pa = &attrs; *pa; )
		      إذا (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = درخت_CHAIN (*pa);
		      وإلا
			pa = &درخت_CHAIN (*pa);
		    أرجع;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->درازی ()
				       + toks->درازی () + 2);
		لكل (++اولی; اولی < آخرین; ++اولی)
		  attr_clauses->سریع_افزودن (*اولی);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = آخرین[-1].location;
		attr_clauses->سریع_افزودن (tok);
		*pa2 = درخت_CHAIN (a);
	      }
	    وإلا
	      pa2 = &درخت_CHAIN (a);
	  }
	إذا (cnt && درخت_مقدار (*pa) == NULL_درخت)
	  *pa = درخت_CHAIN (*pa);
	وإلا
	  pa = &درخت_CHAIN (*pa);
      }
    وإلا
      pa = &درخت_CHAIN (*pa);
  إذا (attr_clauses->درازی ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->آخرین ().location;
      attr_clauses->سریع_افزودن (tok);
      attr_clauses->سریع_افزودن (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

ساكن درخت
c_parser_handle_musttail (c_parser *parser, درخت std_attrs, attr_state &attr)
{
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_RETURN))
    {
      إذا (درخت a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  لكل (; a; a = lookup_attribute ("gnu", "musttail", درخت_CHAIN (a)))
	    إذا (درخت_مقدار (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = درست;
	}
      إذا (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = درست;
	}
    }
  أرجع std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

ساكن درخت
get_before_labels ()
{
  إذا (!building_stmt_list_p ())
    أرجع NULL_درخت;
  درخت_stmt_iterator tsi = tsi_آخرین (cur_stmt_list);
  إذا (tsi_انتها_p (tsi))
    أرجع NULL_درخت;
  أرجع tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

ساكن location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  منطقي آخرین_stmt = خطأ;
  منطقي آخرین_label = خطأ;
  منطقي save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  بنية omp_for_parse_داده *omp_for_parse_state
    = parser->omp_for_parse_state;
  منطقي درون_omp_loop_بلوک
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : خطأ;
  درخت sl = NULL_درخت;
  attr_state astate = {};

  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      جمع_کن_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      أرجع endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  إذا (درون_omp_loop_بلوک)
    sl = افزودن_stmt_list ();

  mark_valid_location_for_stdc_pragma (درست);
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (خطأ);
      إذا (درون_omp_loop_بلوک)
	check_omp_intervening_کد (parser);
      طالما (c_parser_بعدی_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  طالما (درست)
	    {
	      درخت label;
	      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  اكسر;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->مقدار);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      جمع_کن_stmt (build_stmt (label_loc, DECL_عبارت, label));
	      c_parser_consume_token (parser);
	      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      وإلا
		اكسر;
	    }
	  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      أرجع endloc;
    }
  درخت before_labels = get_before_labels ();
  طالما (c_parser_بعدی_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_نقطه_location_if_درون_system_سرآیند (loc);

      منطقي want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : خطأ);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      إذا (درون_omp_loop_بلوک && !آخرین_label)
	{
	  درخت_کد_2 کد = omp_for_parse_state->کد;
	  إذا (want_nested_loop
	      && c_parser_omp_بعدی_نشانهها_can_be_canon_loop (parser, کد,
							     خطأ))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      جمع_کن_structured_بلوک_stmt (برداشت_stmt_list (sl));
	      omp_for_parse_state->عمق++;
	      جمع_کن_stmt (c_parser_omp_loop_nest (parser, عدم));
	      omp_for_parse_state->عمق--;
	      sl = افزودن_stmt_list ();
	      parser->error = خطأ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      استمر;
	    }
	  وإلا إذا (want_nested_loop
		   && c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      درخت pre_sl = برداشت_stmt_list (sl);
	      درخت nested_sl = افزودن_stmt_list ();
	      mark_valid_location_for_stdc_pragma (خطأ);
	      c_parser_statement_after_labels (parser, عدم, NULL_درخت);
	      nested_sl = برداشت_stmt_list (nested_sl);
	      إذا (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_کد (parser);
		  sl = افزودن_stmt_list ();
		  جمع_کن_stmt (pre_sl);
		  جمع_کن_stmt (nested_sl);
		}
	      وإلا
		{
		  /* It contains the nested loop.  */
		  جمع_کن_structured_بلوک_stmt (pre_sl);
		  جمع_کن_stmt (nested_sl);
		  sl = افزودن_stmt_list ();
		}
	      parser->error = خطأ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      استمر;
	    }
	  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      استمر;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      منطقي have_std_attrs
	= c_parser_nth_token_starts_std_صفات (parser, 1);
      درخت std_attrs = NULL_درخت;
      إذا (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      إذا (c_parser_بعدی_token_is_keyword (parser, RID_CASE)
	  || c_parser_بعدی_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_بعدی_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  وإلا
	    label_loc = c_parser_peek_token (parser)->location;
	  آخرین_label = درست;
	  آخرین_stmt = خطأ;
	  mark_valid_location_for_stdc_pragma (خطأ);
	  إذا (درون_omp_loop_بلوک)
	    check_omp_intervening_کد (parser);
	  c_parser_label (parser, std_attrs);
	}
      وإلا إذا (c_parser_بعدی_نشانهها_شروع_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_صفات
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_بعدی_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = درست)))
	{
	  إذا (آخرین_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  إذا (درون_omp_loop_بلوک)
	    {
	      check_omp_intervening_کد (parser);
	      omp_for_parse_state->want_nested_loop = خطأ;
	    }
	  mark_valid_location_for_stdc_pragma (خطأ);
	  منطقي fallthru_attr_p = خطأ;
	  c_parser_declaration_or_fndef (parser, درست, !have_std_attrs,
					 درست, درست, درست, خطأ, عدم,
					 عدم, have_std_attrs, std_attrs,
					 عدم, &fallthru_attr_p);

	  إذا (درون_omp_loop_بلوک)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  إذا (آخرین_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  آخرین_stmt = fallthru_attr_p;
	  آخرین_label = خطأ;
	  before_labels = get_before_labels ();
	}
      وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  طالما (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  إذا (!have_std_attrs
	      && (c_parser_بعدی_نشانهها_شروع_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_صفات (parser, 2)))
	    {
	      صحيح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      آخرین_label = خطأ;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      إذا (درون_omp_loop_بلوک)
		{
		  check_omp_intervening_کد (parser);
		  omp_for_parse_state->want_nested_loop = خطأ;
		}
	      mark_valid_location_for_stdc_pragma (خطأ);
	      c_parser_declaration_or_fndef (parser, درست, درست, درست, درست,
					     درست, خطأ);
	      إذا (درون_omp_loop_بلوک)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      إذا (آخرین_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      آخرین_stmt = خطأ;
	      before_labels = get_before_labels ();
	    }
	  وإلا
	    اذهب statement;
	}
      وإلا إذا (c_parser_بعدی_token_is (parser, CPP_PRAGMA))
	{
	  إذا (have_std_attrs && !parser->درون_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  وإلا إذا (std_attrs)
	    c_warn_استفادهنشده_صفات (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  إذا (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = خطأ;
	  إذا (c_parser_pragma (parser,
			       آخرین_label ? pragma_stmt : pragma_compound,
			       عدم, before_labels))
	    {
	      آخرین_label = خطأ;
	      آخرین_stmt = درست;
	      إذا (omp_for_parse_state)
		check_omp_intervening_کد (parser);
	    }
	  إذا (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      وإلا إذا (c_parser_بعدی_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  أرجع c_parser_peek_token (parser)->location;
	}
      وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_ELSE))
        {
          إذا (parser->درون_if_بلوک)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      أرجع c_parser_peek_token (parser)->location;
            }
          وإلا
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              استمر;
            }
        }
      وإلا
	{
	statement:
	  c_warn_استفادهنشده_صفات (std_attrs);
	  آخرین_label = خطأ;
	  آخرین_stmt = درست;
	  mark_valid_location_for_stdc_pragma (خطأ);
	  إذا (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, عدم, before_labels,
					     عدم, astate);
	  وإلا
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = خطأ;
	      check_omp_intervening_کد (parser);
	      c_parser_statement_after_labels (parser, عدم, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = خطأ;
      astate.reset ();
    }
  إذا (آخرین_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  إذا (sl)
    {
      sl = برداشت_stmt_list (sl);
      إذا (omp_for_parse_state->want_nested_loop)
	جمع_کن_stmt (sl);
      وإلا
	جمع_کن_structured_بلوک_stmt (sl);
    }
  أرجع endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

ساكن attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  منطقي have_std_attrs;
  درخت std_attrs = عدم;
  إذا ((have_std_attrs = c_parser_nth_token_starts_std_صفات (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  طالما (c_parser_بعدی_token_is_keyword (parser, RID_CASE)
	 || c_parser_بعدی_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_بعدی_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = عدم;
      إذا ((have_std_attrs = c_parser_nth_token_starts_std_صفات (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  إذا (std_attrs
      && (!c_parser_handle_statement_omp_صفات (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      إذا (have_std_attrs && c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_استفادهنشده_صفات (std_attrs);
    }
  وإلا إذا (have_std_attrs && c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  أرجع attr;
}


/* Information used while parsing an OpenMP metadirective.  */
بنية omp_metadirective_parse_داده {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<درخت> * GTY((skip)) body_labels;
  بیعلامت صحيح region_رقم;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
ساكن درخت
mangle_metadirective_region_label (c_parser *parser, درخت name)
{
  إذا (parser->omp_metadirective_state->body_labels->شامل_است (name))
    {
      ثابت حرف *old_name = IDENTIFIER_اشاره_گر (name);
      حرف *new_name = (حرف *) XALLOCAVEC (حرف, طول_رشته (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_رقم);
      أرجع get_identifier (new_name);
    }
  أرجع name;
}

/* Parse a label (C90 6.6.1, C99 6.8.1, C11 6.8.1).

   label:
     identifier : gnu-attributes[opt]
     case constant-expression :
     default :

   GNU extensions:

   label:
     case constant-expression ... constant-expression :

   The use of gnu-attributes on labels is a GNU extension.  The syntax in
   GNU C accepts any expressions without commas, non-constant
   expressions being rejected later.  Any standard
   attribute-specifier-sequence before the first label has been parsed
   in the caller, to distinguish statements from declarations.  Any
   attribute-specifier-sequence after the label is parsed in this
   function.  */
ساكن فراغ
c_parser_label (c_parser *parser, درخت std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  درخت label = NULL_درخت;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  منطقي fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  إذا (c_parser_بعدی_token_is_keyword (parser, RID_CASE))
    {
      درخت exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_مقصد_rvalue (loc1,
				       c_parser_عبارت_no_commas (parser, عدم),
				       درست, درست).مقدار;
      إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_درخت, std_attrs);
	}
      وإلا إذا (c_parser_بعدی_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_مقصد_rvalue (loc1,
					   c_parser_عبارت_no_commas (parser,
								    عدم),
					   درست, درست).مقدار;
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      وإلا
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_درخت, NULL_درخت, std_attrs);
    }
  وإلا
    {
      درخت name = c_parser_peek_token (parser)->مقدار;
      درخت tlab;
      درخت attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_بعدی_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_بعدی_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_صفات (parser);
      إذا (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      إذا (tlab)
	{
	  decl_صفات (&tlab, attrs, 0);
	  decl_صفات (&tlab, std_attrs, 0);
	  label = جمع_کن_stmt (build_stmt (loc1, LABEL_عبارت, tlab));
	}
      إذا (attrs
	  && c_parser_بعدی_نشانهها_شروع_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  إذا (label)
    {
      إذا (درخت_کد (label) == LABEL_عبارت)
	FALLTHROUGH_LABEL_P (LABEL_عبارت_LABEL (label)) = fallthrough_p;
      وإلا
	FALLTHROUGH_LABEL_P (CASE_LABEL (label)) = fallthrough_p;
    }
}

/* Parse a statement (C90 6.6, C99 6.8, C11 6.8).

   statement:
     labeled-statement
     attribute-specifier-sequence[opt] compound-statement
     expression-statement
     attribute-specifier-sequence[opt] selection-statement
     attribute-specifier-sequence[opt] iteration-statement
     attribute-specifier-sequence[opt] jump-statement

   labeled-statement:
     attribute-specifier-sequence[opt] label statement

   expression-statement:
     expression[opt] ;
     attribute-specifier-sequence expression ;

   selection-statement:
     if-statement
     switch-statement

   iteration-statement:
     while-statement
     do-statement
     for-statement

   jump-statement:
     goto identifier ;
     continue ;
     break ;
     return expression[opt] ;

   GNU extensions:

   statement:
     attribute-specifier-sequence[opt] asm-statement

   jump-statement:
     goto * expression ;

   expression-statement:
     gnu-attributes ;

   Objective-C:

   statement:
     attribute-specifier-sequence[opt] objc-throw-statement
     attribute-specifier-sequence[opt] objc-try-catch-statement
     attribute-specifier-sequence[opt] objc-synchronized-statement

   objc-throw-statement:
     @throw expression ;
     @throw ;

   OpenACC:

   statement:
     attribute-specifier-sequence[opt] openacc-construct

   openacc-construct:
     parallel-construct
     kernels-construct
     data-construct
     loop-construct

   parallel-construct:
     parallel-directive structured-block

   kernels-construct:
     kernels-directive structured-block

   data-construct:
     data-directive structured-block

   loop-construct:
     loop-directive structured-block

   OpenMP:

   statement:
     attribute-specifier-sequence[opt] openmp-construct

   openmp-construct:
     parallel-construct
     for-construct
     simd-construct
     for-simd-construct
     sections-construct
     single-construct
     parallel-for-construct
     parallel-for-simd-construct
     parallel-sections-construct
     master-construct
     critical-construct
     atomic-construct
     ordered-construct

   parallel-construct:
     parallel-directive structured-block

   for-construct:
     for-directive iteration-statement

   simd-construct:
     simd-directive iteration-statements

   for-simd-construct:
     for-simd-directive iteration-statements

   sections-construct:
     sections-directive section-scope

   single-construct:
     single-directive structured-block

   parallel-for-construct:
     parallel-for-directive iteration-statement

   parallel-for-simd-construct:
     parallel-for-simd-directive iteration-statement

   parallel-sections-construct:
     parallel-sections-directive section-scope

   master-construct:
     master-directive structured-block

   critical-construct:
     critical-directive structured-block

   atomic-construct:
     atomic-directive expression-statement

   ordered-construct:
     ordered-directive structured-block

   Transactional Memory:

   statement:
     attribute-specifier-sequence[opt] transaction-statement
     attribute-specifier-sequence[opt] transaction-cancel-statement

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساكن فراغ
c_parser_statement (c_parser *parser, منطقي *if_p, location_t *loc_after_labels)
{
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  إذا (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = خطأ;
  c_parser_statement_after_labels (parser, if_p, before_labels, عدم, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

ساكن درخت
c_parser_bc_name (c_parser *parser, منطقي is_break)
{
  إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
    أرجع NULL_درخت;

  c_token *tok = c_parser_peek_token (parser);
  درخت label = c_پایان_bc_name (tok->location, tok->مقدار, is_break);
  c_parser_consume_token (parser);
  أرجع label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_statement_after_labels (c_parser *parser, منطقي *if_p,
				 درخت before_labels,
				 vec<درخت> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت stmt = NULL_درخت;
  منطقي درون_if_بلوک = parser->درون_if_بلوک;
  parser->درون_if_بلوک = خطأ;
  إذا (if_p != عدم)
    *if_p = خطأ;

  إذا (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    جمع_کن_debug_begin_stmt (loc);

 restart:
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_OPEN_BRACE:
      جمع_کن_stmt (c_parser_compound_statement (parser));
      اكسر;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  اكسر;
	حالة RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  اكسر;
	حالة RID_WHILE:
	  c_parser_while_statement (parser, خطأ, 0, خطأ, if_p, before_labels);
	  اكسر;
	حالة RID_DO:
	  c_parser_do_statement (parser, خطأ, 0, خطأ, before_labels);
	  اكسر;
	حالة RID_FOR:
	  c_parser_for_statement (parser, خطأ, 0, خطأ, if_p, before_labels);
	  اكسر;
	حالة RID_GOTO:
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	    {
	      درخت name = c_parser_peek_token (parser)->مقدار;
	      إذا (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_پایان_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_MULT))
	    {
	      بنية c_عبارت val;

	      c_parser_consume_token (parser);
	      val = c_parser_عبارت (parser);
	      val = convert_lvalue_مقصد_rvalue (loc, val, خطأ, درست);
	      stmt = c_پایان_goto_ptr (loc, val);
	    }
	  وإلا
	    c_parser_error (parser, "expected identifier or %<*%>");
	  اذهب expect_semicolon;
	حالة RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_پایان_bc_stmt (loc, objc_foreach_continue_label, خطأ,
				   c_parser_bc_name (parser, خطأ));
	  اذهب expect_semicolon;
	حالة RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_پایان_bc_stmt (loc, objc_foreach_break_label, درست,
				   c_parser_bc_name (parser, درست));
	  اذهب expect_semicolon;
	حالة RID_RETURN:
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_پایان_return (loc, NULL_درخت, NULL_درخت,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      بنية c_عبارت عبارت = c_parser_عبارت_conv (parser);
	      mark_exp_read (عبارت.مقدار);
	      stmt = c_پایان_return (عبارت_LOC_OR_LOC (عبارت.مقدار, xloc),
				      عبارت.مقدار, عبارت.original_type,
				      astate.musttail_p);
	      اذهب expect_semicolon;
	    }
	  اكسر;
	حالة RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  اكسر;
	حالة RID_TRANSACTION_ATOMIC:
	حالة RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  اكسر;
	حالة RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  اذهب expect_semicolon;
	حالة RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_درخت);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      بنية c_عبارت عبارت = c_parser_عبارت (parser);
	      عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, خطأ, خطأ);
	      عبارت.مقدار = c_fully_fold (عبارت.مقدار, خطأ, عدم);
	      stmt = objc_build_throw_stmt (loc, عبارت.مقدار);
	      اذهب expect_semicolon;
	    }
	  اكسر;
	حالة RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  اكسر;
	حالة RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  اكسر;
	حالة RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    درخت attrs = c_parser_gnu_صفات (parser);
	    منطقي has_assume = lookup_attribute ("assume", attrs);
	    إذا (has_assume)
	      {
		إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, درست);
		وإلا
		  {
		    auto_urlify_صفات sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = خطأ;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    إذا (astate.musttail_p)
	      {
		إذا (attrs)
		  {
		    auto_urlify_صفات sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		اذهب restart;
	      }
	    إذا (attribute_fallthrough_p (attrs))
	      {
		إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
		  {
		    درخت fn = build_call_عبارت_داخلی_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_گره, 0);
		    جمع_کن_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		وإلا
		  {
		    auto_urlify_صفات sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    وإلا إذا (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    وإلا إذا (attrs != NULL_درخت)
	      {
		auto_urlify_صفات sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    اكسر;
	  }
	افتراضي:
	  اذهب عبارت_stmt;
	}
      اكسر;
    حالة CPP_SEMICOLON:
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CLOSE_PAREN:
    حالة CPP_CLOSE_مربع:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_PRAGMA:
      إذا (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        اذهب restart;
      اكسر;
    افتراضي:
    عبارت_stmt:
      stmt = c_پایان_عبارت_stmt (loc, c_parser_عبارت_conv (parser).مقدار);
    expect_semicolon:
      c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
      اكسر;
    }
  /* Two cases cannot and do not have line numbers associated: If stmt
     is degenerate, such as "2;", then stmt is an INTEGER_CST, which
     cannot hold line numbers.  But that's OK because the statement
     will either be changed to a MODIFY_EXPR during gimplification of
     the statement expr, or discarded.  If stmt was compound, but
     without new variables, we will have skipped the creation of a
     BIND and will have a bare STATEMENT_LIST.  But that's OK because
     (recursively) all of the component statements should already have
     line numbers assigned.  ??? Can we discard no-op statements
     earlier?  */
  إذا (عبارت_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_مجموعه_عبارت_location (stmt, loc);

  parser->درون_if_بلوک = درون_if_بلوک;
}

/* Parse the condition from an if, do, while or for statements.  */

ساكن درخت
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت cond;
  cond = c_parser_عبارت_conv (parser).مقدار;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, خطأ, عدم);
  إذا (warn_sequence_نقطه)
    verify_sequence_points (cond);
  أرجع cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

ساكن درخت
c_parser_paren_condition (c_parser *parser)
{
  درخت cond;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_گره;
  cond = c_parser_condition (parser);
  parens.skip_until_یافت_close (parser);
  أرجع cond;
}

/* Parse a selection-header:

   selection-header:
عبارت
     declaration expression
     simple-declaration

   simple-declaration:
     attribute-specifier-sequence[opt] declaration-specifiers declarator
       = initializer

  SWITCH_P is true if we are called from c_parser_switch_statement; in
  that case, don't perform the truthvalue conversion.  */

ساكن c_عبارت
c_parser_selection_سرآیند (c_parser *parser, منطقي switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت;
  منطقي parse_عبارت = درست;
  درخت std_attrs;
  منطقي have_std_attrs = c_parser_nth_token_starts_std_صفات (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  وإلا
    std_attrs = NULL_درخت;
  إذا (c_parser_بعدی_نشانهها_شروع_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      عبارت.مقدار
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/خطأ,
					 /*static_assert_ok=*/خطأ,
					 /*empty_ok=*/خطأ,
					 /*nested=*/درست,
					 /*start_attr_ok=*/درست,
					 /*simple_ok=*/درست,
					 /*objc_foreach_object_decl=*/اشاره_تهی,
					 /*omp_declare_simd_clauses=*/اشاره_تهی,
					 have_std_attrs,
					 std_attrs);
      إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      وإلا
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  إذا (!عبارت.مقدار)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      عبارت.original_type = error_mark_گره;
	      عبارت.مجموعه_error ();
	      أرجع عبارت;
	    }
	  parse_عبارت = خطأ;
	}
      إذا (عبارت.مقدار)
	{
	  عبارت.original_type = درخت_TYPE (عبارت.مقدار);
	  عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, /*convert_p=*/درست,
					   /*read_p=*/درست);
	}
    }
  وإلا إذا (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      عبارت.original_type = error_mark_گره;
      عبارت.مجموعه_error ();
      أرجع عبارت;
    }

  إذا (parse_عبارت)
    عبارت = c_parser_عبارت_conv (parser);
  إذا (!switch_p)
    {
      عبارت.مقدار = c_objc_common_truthvalue_conversion (loc, عبارت.مقدار);
      عبارت.مقدار = c_fully_fold (عبارت.مقدار, خطأ, عدم);
      إذا (warn_sequence_نقطه)
	verify_sequence_points (عبارت.مقدار);
    }
  أرجع عبارت;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

ساكن درخت
c_parser_paren_selection_سرآیند (c_parser *parser)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_گره;
  درخت cond = c_parser_selection_سرآیند (parser, /*switch_p=*/خطأ).مقدار;
  parens.skip_until_یافت_close (parser);
  أرجع cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساكن درخت
c_parser_c99_بلوک_statement (c_parser *parser, منطقي *if_p,
			      location_t *loc_after_labels)
{
  درخت بلوک = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  أرجع c_انتها_compound_stmt (loc, بلوک, flag_isoc99);
}

/* Parse the body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we track whether the
   body is an if statement for the sake of -Wparentheses warnings, (c)
   we handle an empty body specially for the sake of -Wempty-body
   warnings, and (d) we call parser_compound_statement directly
   because c_parser_statement_after_labels resets
   parser->in_if_block.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساكن درخت
c_parser_if_body (c_parser *parser, منطقي *if_p,
		  ثابت token_indent_info &if_tinfo)
{
  درخت بلوک = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      جمع_کن_stmt (build_خالی_stmt (loc));
      c_parser_consume_token (parser);
      إذا (!c_parser_بعدی_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    جمع_کن_stmt (c_parser_compound_statement (parser));
  وإلا
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, عدم, a);
    }

  token_indent_info بعدی_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, بعدی_tinfo);
  إذا (body_loc_after_labels != UNKNOWN_LOCATION
      && بعدی_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, بعدی_tinfo.location,
				    if_tinfo.location, RID_IF);

  أرجع c_انتها_compound_stmt (body_loc, بلوک, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

ساكن درخت
c_parser_else_body (c_parser *parser, ثابت token_indent_info &else_tinfo,
		    vec<درخت> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  درخت بلوک = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  درخت before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      جمع_کن_stmt (build_خالی_stmt (loc));
      c_parser_consume_token (parser);
    }
  وإلا
    {
      إذا (!c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, عدم, before_labels, chain, a);
    }

  token_indent_info بعدی_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, بعدی_tinfo);
  إذا (body_loc_after_labels != UNKNOWN_LOCATION
      && بعدی_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, بعدی_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  أرجع c_انتها_compound_stmt (body_loc, بلوک, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساكن فراغ
c_parser_if_statement (c_parser *parser, منطقي *if_p, vec<درخت> *chain)
{
  درخت بلوک;
  location_t loc;
  درخت cond;
  منطقي nested_if = خطأ;
  درخت اولی_body, دومی_body;
  منطقي درون_if_بلوک;

  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  بلوک = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_سرآیند (parser);
  درون_if_بلوک = parser->درون_if_بلوک;
  parser->درون_if_بلوک = درست;
  اولی_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->درون_if_بلوک = درون_if_بلوک;

  إذا (warn_duplicated_cond)
    warn_duplicated_cond_جمع_کن_or_warn (عبارت_LOCATION (cond), cond, &chain);

  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      إذا (warn_duplicated_cond)
	{
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_IF)
	      && chain == عدم)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = جديد vec<درخت> ();
	      إذا (!CONSTANT_CLASS_P (cond) && !درخت_SIDE_EFFECTS (cond))
		chain->امن_افزودن (cond);
	    }
	  وإلا إذا (!c_parser_بعدی_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      دومی_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      إذا (if_p != عدم)
	*if_p = درست;
    }
  وإلا
    {
      دومی_body = NULL_درخت;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      إذا (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      إذا (warn_duplicated_cond)
	/* This if statement does not have an else clause.  We don't
	   need the condition chain anymore.  */
	vec_free (chain);
    }
  c_پایان_if_stmt (loc, cond, اولی_body, دومی_body);
  جمع_کن_stmt (c_انتها_compound_stmt (loc, بلوک, flag_isoc99));

  c_parser_maybe_reclassify_token (parser);
}

/* Parse a switch statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   switch-statement:
     switch (expression) statement

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_switch_statement (c_parser *parser, منطقي *if_p, درخت before_labels)
{
  بنية c_عبارت ce;
  درخت بلوک, عبارت, body;
  بیعلامت حرف save_درون_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  درخت switch_name;
  صحيح رقم_نامها = c_get_loop_نامها (before_labels, درست, &switch_name);
  بلوک = c_begin_compound_stmt (flag_isoc99);
  منطقي explicit_cast_p = خطأ;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = درست;
      ce = c_parser_selection_سرآیند (parser, /*switch_p=*/درست);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_مقصد_rvalue (switch_cond_loc, ce, درست, درست);
      عبارت = ce.مقدار;
      /* ??? expr has no valid location?  */
      parens.skip_until_یافت_close (parser);
    }
  وإلا
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      عبارت = error_mark_گره;
      ce.original_type = error_mark_گره;
    }
  درخت stmt
    = c_شروع_switch (switch_loc, switch_cond_loc, عبارت, explicit_cast_p,
		      switch_name);
  save_درون_statement = درون_statement;
  درون_statement |= درون_SWITCH_STMT;
  إذا (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      درون_statement |= درون_NAMED_STMT;
    }
  وإلا
    درون_statement &= ~درون_NAMED_STMT;
  location_t loc_after_labels;
  منطقي open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_بلوک_statement (parser, if_p, &loc_after_labels);
  location_t بعدی_loc = c_parser_peek_token (parser)->location;
  إذا (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, بعدی_loc, switch_loc,
				    RID_SWITCH);
  c_پایان_switch (body, ce.original_type);
  درون_statement = save_درون_statement;
  إذا (رقم_نامها)
    {
      إذا (!C_DECL_LOOP_SWITCH_NAME_استفاده_شده (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_درخت;
      وإلا
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_نامها (رقم_نامها);
    }
  جمع_کن_stmt (c_انتها_compound_stmt (switch_loc, بلوک, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
}

/* Parse a while statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   while-statement:
      while (expression) statement

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_while_statement (c_parser *parser, منطقي ivdep, بیعلامت کوتاه unroll,
			  منطقي novector, منطقي *if_p, درخت before_labels)
{
  درخت بلوک, cond, body;
  بیعلامت حرف save_درون_statement;
  location_t loc;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت loop_name;
  صحيح رقم_نامها = c_get_loop_نامها (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = درست;
    }

  c_parser_consume_token (parser);
  بلوک = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  إذا (ivdep && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_ivdep_نوع),
		   integer_zero_گره);
  إذا (unroll && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_unroll_نوع),
		   build_int_cst (integer_type_گره, unroll));
  إذا (novector && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_no_وکتور_نوع),
		   integer_zero_گره);
  save_درون_statement = درون_statement;
  درون_statement = درون_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      درون_statement |= درون_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقي open_brace = c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_بلوک_statement (parser, if_p, &loc_after_labels);
  إذا (loop_name && !C_DECL_LOOP_SWITCH_NAME_استفاده_شده (loop_name))
    loop_name = NULL_درخت;
  جمع_کن_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_درخت,
			NULL_درخت));
  جمع_کن_stmt (c_انتها_compound_stmt (loc, بلوک, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  إذا (رقم_نامها)
    c_release_loop_نامها (رقم_نامها);

  token_indent_info بعدی_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, بعدی_tinfo);

  إذا (بعدی_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, بعدی_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  درون_statement = save_درون_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_do_statement (c_parser *parser, منطقي ivdep, بیعلامت کوتاه unroll,
		       منطقي novector, درخت before_labels)
{
  درخت بلوک, cond, body;
  بیعلامت حرف save_درون_statement;
  location_t loc;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_DO));
  درخت loop_name;
  صحيح رقم_نامها = c_get_loop_نامها (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = درست;
    }

  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  بلوک = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_درون_statement = درون_statement;
  درون_statement = درون_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      درون_statement |= درون_NAMED_STMT;
    }
  body = c_parser_c99_بلوک_statement (parser, عدم);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  درون_statement = save_درون_statement;
  إذا (رقم_نامها)
    {
      إذا (!C_DECL_LOOP_SWITCH_NAME_استفاده_شده (loop_name))
	loop_name = NULL_درخت;
      c_release_loop_نامها (رقم_نامها);
    }
  cond = c_parser_paren_condition (parser);
  إذا (ivdep && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_ivdep_نوع),
		   integer_zero_گره);
  إذا (unroll && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_unroll_نوع),
 		   build_int_cst (integer_type_گره, unroll));
  إذا (novector && cond != error_mark_گره)
    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
		   build_int_cst (integer_type_گره,
				  annot_عبارت_no_وکتور_نوع),
		   integer_zero_گره);
  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);

  جمع_کن_stmt (build_stmt (loc, DO_STMT, cond, body, loop_name));
  جمع_کن_stmt (c_انتها_compound_stmt (loc, بلوک, flag_isoc99));
}

/* Parse a for statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   for-statement:
     for ( expression[opt] ; expression[opt] ; expression[opt] ) statement
     for ( nested-declaration expression[opt] ; expression[opt] ) statement

   The form with a declaration is new in C99.

   ??? In accordance with the old parser, the declaration may be a
   nested function, which is then rejected in check_for_loop_decls,
   but does it make any sense for this to be included in the grammar?
   Note in particular that the nested function does not include a
   trailing ';', whereas the "declaration" production includes one.
   Also, can we reject bad declarations earlier and cheaper than
   check_for_loop_decls?

   In Objective-C, there are two additional variants:

   foreach-statement:
     for ( expression in expression ) statement
     for ( declaration in expression ) statement

   This is inconsistent with C, because the second variant is allowed
   even if c99 is not enabled.

   The rest of the comment documents these Objective-C foreach-statement.

   Here is the canonical example of the first variant:
    for (object in array)    { do something with object }
   we call the first expression ("object") the "object_expression" and
   the second expression ("array") the "collection_expression".
   object_expression must be an lvalue of type "id" (a generic Objective-C
   object) because the loop works by assigning to object_expression the
   various objects from the collection_expression.  collection_expression
   must evaluate to something of type "id" which responds to the method
   countByEnumeratingWithState:objects:count:.

   The canonical example of the second variant is:
    for (id object in array)    { do something with object }
   which is completely equivalent to
    {
      id object;
      for (object in array) { do something with object }
    }
   Note that initizializing 'object' in some way (eg, "for ((object =
   xxx) in array) { do something with object }") is possibly
   technically valid, but completely pointless as 'object' will be
   assigned to something else as soon as the loop starts.  We should
   most likely reject it (TODO).

   The beginning of the Objective-C foreach-statement looks exactly
   like the beginning of the for-statement, and we can tell it is a
   foreach-statement only because the initial declaration or
   expression is terminated by 'in' instead of ';'.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_for_statement (c_parser *parser, منطقي ivdep, بیعلامت کوتاه unroll,
			منطقي novector, منطقي *if_p, درخت before_labels)
{
  درخت بلوک, cond, incr, body;
  بیعلامت حرف save_درون_statement;
  درخت save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  درخت object_عبارت;
  /* Silence the bogus uninitialized warning.  */
  درخت collection_عبارت = عدم;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  منطقي is_foreach_statement = خطأ;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  درخت loop_name;
  صحيح رقم_نامها = c_get_loop_نامها (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = درست;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  بلوک = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_گره;
  incr = error_mark_گره;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_عبارت = error_mark_گره;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = خطأ;
	  c_parser_consume_token (parser);
	  c_پایان_عبارت_stmt (loc, NULL_درخت);
	}
      وإلا إذا (c_parser_بعدی_نشانهها_شروع_declaration (parser)
	       || c_parser_nth_token_starts_std_صفات (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, درست, درست, درست, درست, درست,
					 خطأ, &object_عبارت);
	  parser->objc_could_be_foreach_context = خطأ;

	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_درون))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = درست;
	      إذا (check_for_loop_decls (for_loc, درست) == NULL_درخت)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  وإلا
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  طالما (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_نشانهها_شروع_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_صفات (parser, 2))
	    {
	      صحيح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, درست, درست, درست, درست,
					     درست, خطأ, &object_عبارت);
	      parser->objc_could_be_foreach_context = خطأ;

	      restore_extension_diagnostics (ext);
	      إذا (c_parser_بعدی_token_is_keyword (parser, RID_درون))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = درست;
		  إذا (check_for_loop_decls (for_loc, درست) == NULL_درخت)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      وإلا
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  وإلا
	    اذهب init_عبارت;
	}
      وإلا
	{
	init_عبارت:
	  {
	    بنية c_عبارت ce;
	    درخت init_عبارت_2;
	    ce = c_parser_عبارت (parser);
	    init_عبارت_2 = ce.مقدار;
	    parser->objc_could_be_foreach_context = خطأ;
	    إذا (c_parser_بعدی_token_is_keyword (parser, RID_درون))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = درست;
		إذا (! lvalue_p (init_عبارت_2))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_عبارت
		  = c_fully_fold (init_عبارت_2, خطأ, عدم);
	      }
	    وإلا
	      {
		ce = convert_lvalue_مقصد_rvalue (loc, ce, درست, خطأ);
		init_عبارت_2 = ce.مقدار;
		c_پایان_عبارت_stmt (loc, init_عبارت_2);
		c_parser_skip_until_یافت (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      إذا (!is_foreach_statement)
	{
	  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	    {
	      إذا (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_گره;
		}
	      وإلا إذا (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_گره;
		}
	      وإلا
		{
		  c_parser_consume_token (parser);
		  cond = NULL_درخت;
		}
	    }
	  وإلا
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_یافت (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  إذا (ivdep && cond != error_mark_گره)
	    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
			   build_int_cst (integer_type_گره,
					  annot_عبارت_ivdep_نوع),
			   integer_zero_گره);
	  إذا (unroll && cond != error_mark_گره)
	    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
 			   build_int_cst (integer_type_گره,
					  annot_عبارت_unroll_نوع),
			   build_int_cst (integer_type_گره, unroll));
	  إذا (novector && cond && cond != error_mark_گره)
	    cond = build3 (ANNOTATE_عبارت, درخت_TYPE (cond), cond,
			   build_int_cst (integer_type_گره,
					  annot_عبارت_no_وکتور_نوع),
			   integer_zero_گره);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_عبارت = error_mark_گره;
	    }
	  وإلا
	    incr = c_process_عبارت_stmt (loc, NULL_درخت);
	}
      وإلا
	{
	  إذا (is_foreach_statement)
	    collection_عبارت
	      = c_fully_fold (c_parser_عبارت (parser).مقدار, خطأ, عدم);
	  وإلا
	    {
	      بنية c_عبارت ce = c_parser_عبارت (parser);
	      ce = convert_lvalue_مقصد_rvalue (loc, ce, درست, خطأ);
	      incr = c_process_عبارت_stmt (loc, ce.مقدار);
	    }
	}
      parens.skip_until_یافت_close (parser);
    }
  save_درون_statement = درون_statement;
  إذا (is_foreach_statement)
    {
      درون_statement = درون_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      إذا (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  وإلا
    درون_statement = درون_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      درون_statement |= درون_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقي open_brace = c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_بلوک_statement (parser, if_p, &loc_after_labels);

  إذا (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_درخت;
      DECL_CHAIN (objc_foreach_break_label) = NULL_درخت;
    }

  إذا (is_foreach_statement)
    objc_پایان_foreach_loop (for_loc, object_عبارت,
			      collection_عبارت, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  وإلا
    جمع_کن_stmt (build_stmt (for_loc, FOR_STMT, NULL_درخت, cond, incr,
			  body, NULL_درخت,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_استفاده_شده (loop_name)
			  ? loop_name : NULL_درخت, NULL_درخت, NULL_درخت));
  جمع_کن_stmt (c_انتها_compound_stmt (for_loc, بلوک,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info بعدی_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, بعدی_tinfo);

  إذا (بعدی_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, بعدی_tinfo.location,
				    for_tinfo.location, RID_FOR);

  درون_statement = save_درون_statement;
  إذا (رقم_نامها)
    c_release_loop_نامها (رقم_نامها);
  إذا (is_foreach_statement)
    {
      objc_foreach_break_label = save_objc_foreach_break_label;
      objc_foreach_continue_label = save_objc_foreach_continue_label;
    }
}

/* Parse an asm statement, a GNU extension.  This is a full-blown asm
   statement with inputs, outputs, clobbers, and volatile, inline, and goto
   tags allowed.

   asm-qualifier:
     volatile
     inline
     goto

   asm-qualifier-list:
     asm-qualifier-list asm-qualifier
     asm-qualifier

   asm-statement:
     asm asm-qualifier-list[opt] ( asm-argument ) ;

   asm-argument:
     asm-string-literal
     asm-string-literal : asm-operands[opt]
     asm-string-literal : asm-operands[opt] : asm-operands[opt]
     asm-string-literal : asm-operands[opt] : asm-operands[opt] \
       : asm-clobbers[opt]
     asm-string-literal : : asm-operands[opt] : asm-clobbers[opt] \
       : asm-goto-operands

   The form with asm-goto-operands is valid if and only if the
   asm-qualifier-list contains goto, and is the only allowed form in that case.
   Duplicate asm-qualifiers are not allowed.

   The :: token is considered equivalent to two consecutive : tokens.  */

ساكن درخت
c_parser_asm_statement (c_parser *parser)
{
  درخت str, outputs, inputs, clobbers, labels, ret;
  منطقي simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  صحيح section, nsections;

  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  لكل (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      بدل (token->keyword)
	{
	حالة RID_VOLATILE:
	  إذا (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->مقدار);
	      inform (volatile_loc, "first seen here");
	    }
	  وإلا
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_INLINE:
	  إذا (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->مقدار);
	      inform (inline_loc, "first seen here");
	    }
	  وإلا
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_GOTO:
	  إذا (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->مقدار);
	      inform (goto_loc, "first seen here");
	    }
	  وإلا
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_CONST:
	حالة RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->مقدار);
	  c_parser_consume_token (parser);
	  استمر;

	افتراضي:
	  اكسر;
	}
      اكسر;
    }

  منطقي is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  منطقي is_inline = (inline_loc != UNKNOWN_LOCATION);
  منطقي is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = عدم;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    اذهب error;

  str = c_parser_asm_string_literal (parser);
  إذا (str == NULL_درخت)
    اذهب error_close_paren;

  simple = درست;
  outputs = NULL_درخت;
  inputs = NULL_درخت;
  clobbers = NULL_درخت;
  labels = NULL_درخت;

  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    اذهب انجامشده_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  لكل (section = 0; section < nsections; ++section)
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  إذا (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      اذهب error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      وإلا إذا (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	اذهب error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = خطأ;

      إذا ((!c_parser_بعدی_token_is (parser, CPP_COLON)
	   && !c_parser_بعدی_token_is (parser, CPP_SCOPE)
	   && !c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	بدل (section)
	  {
	  حالة 0:
	    outputs = c_parser_asm_operands (parser);
	    اكسر;
	  حالة 1:
	    inputs = c_parser_asm_operands (parser);
	    اكسر;
	  حالة 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    اكسر;
	  حالة 3:
	    labels = c_parser_asm_goto_operands (parser);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }

      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	اذهب انجامشده_asm;
    }

 انجامشده_asm:
  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
      اذهب error;
    }

  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_عبارت (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  أرجع ret;

 error_close_paren:
  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
  اذهب error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

ساكن درخت
c_parser_asm_operands (c_parser *parser)
{
  درخت list = NULL_درخت;
  طالما (درست)
    {
      درخت name, str;
      بنية c_عبارت عبارت;
      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_مربع))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	    {
	      درخت id = c_parser_peek_token (parser)->مقدار;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_درازی (id),
				   IDENTIFIER_اشاره_گر (id));
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع, عدم);
	      أرجع NULL_درخت;
	    }
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع,
				     "expected %<]%>");
	}
      وإلا
	name = NULL_درخت;
      str = c_parser_asm_string_literal (parser);
      إذا (str == NULL_درخت)
	أرجع NULL_درخت;
      matching_parens parens;
      إذا (!parens.require_open (parser))
	أرجع NULL_درخت;
      عبارت = c_parser_عبارت (parser);
      mark_exp_read (عبارت.مقدار);
      إذا (!parens.require_close (parser))
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع NULL_درخت;
	}
      list = chainon (list, build_درخت_list (build_درخت_list (name, str),
					     عبارت.مقدار));
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  أرجع list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

ساكن درخت
c_parser_asm_clobbers (c_parser *parser)
{
  درخت list = NULL_درخت;
  طالما (درست)
    {
      درخت str = c_parser_asm_string_literal (parser);
      إذا (str)
	list = درخت_cons (NULL_درخت, str, list);
      وإلا
	أرجع NULL_درخت;
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  أرجع list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

ساكن درخت
c_parser_asm_goto_operands (c_parser *parser)
{
  درخت list = NULL_درخت;
  طالما (درست)
    {
      درخت name, label;

      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->مقدار;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  درخت_استفاده_شده (label) = 1;
	}
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع NULL_درخت;
	}

      name = build_string (IDENTIFIER_درازی (name),
			   IDENTIFIER_اشاره_گر (name));
      list = درخت_cons (name, label, list);
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	أرجع nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

بنية c_عبارت
c_parser_string_literal (c_parser *parser, منطقي translate, منطقي wide_ok)
{
  بنية c_عبارت ret;
  اندازه_t شمار;
  بنية obstack str_ob;
  بنية obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, آخرین_tok_loc;
  تعداد cpp_ttype type;
  درخت مقدار, string_درخت;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  آخرین_tok_loc = linemap_resolve_location (سطر_جدول, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   عدم);
  type = tok->type;
  بدل (type)
    {
    حالة CPP_STRING:
    حالة CPP_WSTRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_UTF8STRING:
      string_درخت = tok->مقدار;
      اكسر;

    افتراضي:
      c_parser_error (parser, "expected string literal");
      ret.مجموعه_error ();
      ret.مقدار = NULL_درخت;
      ret.original_کد = ERROR_MARK;
      ret.original_type = NULL_درخت;
      أرجع ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  بدل (c_parser_peek_2nd_token (parser)->type)
    {
    افتراضي:
      c_parser_consume_token (parser);
      str.متن = (ثابت بیعلامت حرف *) درخت_STRING_اشاره_گر (string_درخت);
      str.len = درخت_STRING_درازی (string_درخت);
      شمار = 1;
      strs = &str;
      اكسر;

    حالة CPP_STRING:
    حالة CPP_WSTRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      شمار = 0;
      افعل
	{
	  c_parser_consume_token (parser);
	  شمار++;
	  str.متن = (ثابت بیعلامت حرف *) درخت_STRING_اشاره_گر (string_درخت);
	  str.len = درخت_STRING_درازی (string_درخت);
	  إذا (type != tok->type)
	    {
	      إذا (type == CPP_STRING)
		type = tok->type;
	      وإلا إذا (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, حجم (cpp_string));
	  obstack_grow (&loc_ob, &آخرین_tok_loc, حجم (location_t));
	  tok = c_parser_peek_token (parser);
	  string_درخت = tok->مقدار;
	  آخرین_tok_loc
	    = linemap_resolve_location (سطر_جدول, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, عدم);
	}
      طالما (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_پایان (&str_ob);
    }

  إذا (شمار > 1 && !درون_system_سرآیند_at (درون_داد_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  إذا ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_درون, strs, شمار, &istr, type)))
    {
      مقدار = build_string (istr.len, (ثابت حرف *) istr.متن);
      حرر (const_cast<بیعلامت حرف *> (istr.متن));
      إذا (شمار > 1)
	{
	  location_t *locs = (location_t *) obstack_پایان (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->رکورد_string_concatenation (شمار, locs);
	}
    }
  وإلا
    {
      إذا (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      بدل (type)
	{
	افتراضي:
	حالة CPP_STRING:
	حالة CPP_UTF8STRING:
	  إذا (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      مقدار = build_string (TYPE_PRECISION (char8_type_گره)
				    / TYPE_PRECISION (char_type_گره),
				    "");  /* char8_t is 8 bits */
	    }
	  وإلا
	    مقدار = build_string (1, "");
	  اكسر;
	حالة CPP_STRING16:
	  مقدار = build_string (TYPE_PRECISION (char16_type_گره)
				/ TYPE_PRECISION (char_type_گره),
				"\0");  /* char16_t is 16 bits */
	  اكسر;
	حالة CPP_STRING32:
	  مقدار = build_string (TYPE_PRECISION (char32_type_گره)
				/ TYPE_PRECISION (char_type_گره),
				"\0\0\0");  /* char32_t is 32 bits */
	  اكسر;
	حالة CPP_WSTRING:
	  مقدار = build_string (TYPE_PRECISION (wchar_type_گره)
				/ TYPE_PRECISION (char_type_گره),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  اكسر;
        }
    }

  بدل (type)
    {
    افتراضي:
    حالة CPP_STRING:
      درخت_TYPE (مقدار) = char_array_type_گره;
      اكسر;
    حالة CPP_UTF8STRING:
      إذا (flag_char8_t)
	درخت_TYPE (مقدار) = char8_array_type_گره;
      وإلا
	درخت_TYPE (مقدار) = char_array_type_گره;
      اكسر;
    حالة CPP_STRING16:
      درخت_TYPE (مقدار) = char16_array_type_گره;
      اكسر;
    حالة CPP_STRING32:
      درخت_TYPE (مقدار) = char32_array_type_گره;
      اكسر;
    حالة CPP_WSTRING:
      درخت_TYPE (مقدار) = wchar_array_type_گره;
    }
  مقدار = fix_string_type (مقدار);

  إذا (شمار > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.مقدار = مقدار;
  ret.original_کد = STRING_CST;
  ret.original_type = NULL_درخت;
  مجموعه_c_عبارت_منبع_range (&ret, get_range_from_loc (سطر_جدول, loc));
  ret.m_decimal = 0;
  parser->دیده_string_literal = درست;
  أرجع ret;
}

/* Parse an expression other than a compound expression; that is, an
   assignment expression (C90 6.3.16, C99 6.5.16, C11 6.5.16).  If
   AFTER is not NULL then it is an Objective-C message expression which
   is the primary-expression starting the expression as an initializer.

   assignment-expression:
     conditional-expression
     unary-expression assignment-operator assignment-expression

   assignment-operator: one of
     = *= /= %= += -= <<= >>= &= ^= |=

   In GNU C we accept any conditional expression on the LHS and
   diagnose the invalid lvalue rather than producing a syntax
   error.  */

ساكن بنية c_عبارت
c_parser_عبارت_no_commas (c_parser *parser, بنية c_عبارت *after,
			 درخت omp_atomic_lhs)
{
  بنية c_عبارت lhs, rhs, ret;
  تعداد درخت_کد_2 کد;
  location_t op_location, exp_location;
  منطقي save_درون_omp_for = c_درون_omp_for;
  c_درون_omp_for = خطأ;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_عبارت (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_EQ:
      کد = NOP_عبارت;
      اكسر;
    حالة CPP_MULT_EQ:
      کد = MULT_عبارت;
      اكسر;
    حالة CPP_DIV_EQ:
      کد = TRUNC_DIV_عبارت;
      اكسر;
    حالة CPP_MOD_EQ:
      کد = TRUNC_MOD_عبارت;
      اكسر;
    حالة CPP_PLUS_EQ:
      کد = PLUS_عبارت;
      اكسر;
    حالة CPP_MINUS_EQ:
      کد = MINUS_عبارت;
      اكسر;
    حالة CPP_LSHIFT_EQ:
      کد = LSHIFT_عبارت;
      اكسر;
    حالة CPP_RSHIFT_EQ:
      کد = RSHIFT_عبارت;
      اكسر;
    حالة CPP_AND_EQ:
      کد = بیت_AND_عبارت;
      اكسر;
    حالة CPP_XOR_EQ:
      کد = بیت_XOR_عبارت;
      اكسر;
    حالة CPP_OR_EQ:
      کد = بیت_IOR_عبارت;
      اكسر;
    افتراضي:
      c_درون_omp_for = save_درون_omp_for;
      أرجع lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_عبارت_no_commas (parser, عدم);
  rhs = convert_lvalue_مقصد_rvalue (exp_location, rhs, درست, درست);

  ret.مقدار = build_modify_عبارت (op_location, lhs.مقدار, lhs.original_type,
				 کد, exp_location, rhs.مقدار,
				 rhs.original_type);
  ret.m_decimal = 0;
  مجموعه_c_عبارت_منبع_range (&ret, lhs.get_شروع (), rhs.get_پایان ());
  إذا (کد == NOP_عبارت)
    ret.original_کد = MODIFY_عبارت;
  وإلا
    {
      suppress_warning (ret.مقدار, OPT_Wparentheses);
      ret.original_کد = ERROR_MARK;
    }
  ret.original_type = عدم;
  c_درون_omp_for = save_درون_omp_for;
  أرجع ret;
}

/* Parse a conditional expression (C90 6.3.15, C99 6.5.15, C11 6.5.15).  If
   AFTER is not NULL then it is an Objective-C message expression which is
   the primary-expression starting the expression as an initializer.

   conditional-expression:
     logical-OR-expression
     logical-OR-expression ? expression : conditional-expression

   GNU extensions:

   conditional-expression:
     logical-OR-expression ? : conditional-expression
*/

ساكن بنية c_عبارت
c_parser_conditional_عبارت (c_parser *parser, بنية c_عبارت *after,
				 درخت omp_atomic_lhs)
{
  بنية c_عبارت cond, exp1, exp2, ret;
  location_t شروع, cond_loc, colon_loc;
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_دودویی_عبارت (parser, after, omp_atomic_lhs);

  إذا (c_parser_بعدی_token_is_not (parser, CPP_QUERY))
    أرجع cond;
  c_omp_array_section_p = خطأ;
  إذا (cond.مقدار != error_mark_گره)
    شروع = cond.get_شروع ();
  وإلا
    شروع = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_مقصد_rvalue (cond_loc, cond, درست, درست);
  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
    {
      درخت eptype = NULL_درخت;

      location_t میانه_loc = c_parser_peek_token (parser)->location;
      pedwarn (میانه_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      إذا (درخت_کد (cond.مقدار) == EXCESS_PRECISION_عبارت)
	{
	  eptype = درخت_TYPE (cond.مقدار);
	  cond.مقدار = درخت_عملوند (cond.مقدار, 0);
	}
      درخت e = cond.مقدار;
      طالما (درخت_کد (e) == COMPOUND_عبارت)
	e = درخت_عملوند (e, 1);
      warn_for_omitted_condop (میانه_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.مقدار = save_عبارت (default_conversion (cond.مقدار));
      إذا (eptype)
	exp1.مقدار = build1 (EXCESS_PRECISION_عبارت, eptype, exp1.مقدار);
      exp1.original_type = عدم;
      exp1.src_range = cond.src_range;
      cond.مقدار = c_objc_common_truthvalue_conversion (cond_loc, exp1.مقدار);
      c_inhibit_evaluation_warnings += cond.مقدار == truthvalue_true_گره;
    }
  وإلا
    {
      cond.مقدار
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.مقدار));
      c_inhibit_evaluation_warnings += cond.مقدار == truthvalue_false_گره;
      exp1 = c_parser_عبارت_conv (parser);
      mark_exp_read (exp1.مقدار);
      c_inhibit_evaluation_warnings +=
	((cond.مقدار == truthvalue_true_گره)
	 - (cond.مقدار == truthvalue_false_گره));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.مقدار == truthvalue_true_گره;
      ret.مجموعه_error ();
      ret.original_کد = ERROR_MARK;
      ret.original_type = عدم;
      c_omp_array_section_p = save_c_omp_array_section_p;
      أرجع ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_عبارت (parser, عدم, NULL_درخت);
    exp2 = convert_lvalue_مقصد_rvalue (exp2_loc, exp2, درست, درست);
  }
  c_inhibit_evaluation_warnings -= cond.مقدار == truthvalue_true_گره;
  location_t loc1 = make_location (exp1.get_شروع (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_شروع (), exp2.src_range);
  إذا (UNLIKELY (omp_atomic_lhs != عدم)
      && (درخت_کد (cond.مقدار) == GT_عبارت
	  || درخت_کد (cond.مقدار) == LT_عبارت
	  || درخت_کد (cond.مقدار) == EQ_عبارت)
      && c_درخت_equal (exp2.مقدار, omp_atomic_lhs)
      && (c_درخت_equal (درخت_عملوند (cond.مقدار, 0), omp_atomic_lhs)
	  || c_درخت_equal (درخت_عملوند (cond.مقدار, 1), omp_atomic_lhs)))
    ret.مقدار = build3_loc (colon_loc, COND_عبارت, درخت_TYPE (omp_atomic_lhs),
			    cond.مقدار, exp1.مقدار, exp2.مقدار);
  وإلا
    ret.مقدار
      = build_conditional_عبارت (colon_loc, cond.مقدار,
				cond.original_کد == C_MAYBE_CONST_عبارت,
				exp1.مقدار, exp1.original_type, loc1,
				exp2.مقدار, exp2.original_type, loc2);
  ret.original_کد = ERROR_MARK;
  إذا (exp1.مقدار == error_mark_گره || exp2.مقدار == error_mark_گره)
    ret.original_type = عدم;
  وإلا
    {
      درخت t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : درخت_TYPE (exp1.مقدار);
      t2 = exp2.original_type ? exp2.original_type : درخت_TYPE (exp2.مقدار);
      ret.original_type = ((t1 != error_mark_گره
			    && t2 != error_mark_گره
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : عدم);
    }
  مجموعه_c_عبارت_منبع_range (&ret, شروع, exp2.get_پایان ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  أرجع ret;
}

/* Parse a binary expression; that is, a logical-OR-expression (C90
   6.3.5-6.3.14, C99 6.5.5-6.5.14, C11 6.5.5-6.5.14).  If AFTER is not
   NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   OMP_ATOMIC_LHS is NULL, unless parsing OpenMP #pragma omp atomic,
   when it should be the unfolded lhs.  In a valid OpenMP source,
   one of the operands of the toplevel binary expression must be equal
   to it.  In that case, just return a build2 created binary operation
   rather than result of parser_build_binary_op.

   multiplicative-expression:
     cast-expression
     multiplicative-expression * cast-expression
     multiplicative-expression / cast-expression
     multiplicative-expression % cast-expression

   additive-expression:
     multiplicative-expression
     additive-expression + multiplicative-expression
     additive-expression - multiplicative-expression

   shift-expression:
     additive-expression
     shift-expression << additive-expression
     shift-expression >> additive-expression

   relational-expression:
     shift-expression
     relational-expression < shift-expression
     relational-expression > shift-expression
     relational-expression <= shift-expression
     relational-expression >= shift-expression

   equality-expression:
     relational-expression
     equality-expression == relational-expression
     equality-expression != relational-expression

   AND-expression:
     equality-expression
     AND-expression & equality-expression

   exclusive-OR-expression:
     AND-expression
     exclusive-OR-expression ^ AND-expression

   inclusive-OR-expression:
     exclusive-OR-expression
     inclusive-OR-expression | exclusive-OR-expression

   logical-AND-expression:
     inclusive-OR-expression
     logical-AND-expression && inclusive-OR-expression

   logical-OR-expression:
     logical-AND-expression
     logical-OR-expression || logical-AND-expression
*/

ساكن بنية c_عبارت
c_parser_دودویی_عبارت (c_parser *parser, بنية c_عبارت *after,
			    درخت omp_atomic_lhs)
{
  /* A binary expression is parsed using operator-precedence parsing,
     with the operands being cast expressions.  All the binary
     operators are left-associative.  Thus a binary expression is of
     form:

     E0 op1 E1 op2 E2 ...

     which we represent on a stack.  On the stack, the precedence
     levels are strictly increasing.  When a new operator is
     encountered of higher precedence than that at the top of the
     stack, it is pushed; its LHS is the top expression, and its RHS
     is everything parsed until it is popped.  When a new operator is
     encountered with precedence less than or equal to that at the top
     of the stack, triples E[i-1] op[i] E[i] are popped and replaced
     by the result of the operation until the operator at the top of
     the stack has lower precedence than the new operator or there is
     only one element on the stack; then the top expression is the LHS
     of the new operator.  In the case of logical AND and OR
     expressions, we also need to adjust c_inhibit_evaluation_warnings
     as appropriate when the operators are pushed and popped.  */

  بنية {
    /* The expression at this stack level.  */
    بنية c_عبارت عبارت;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    تعداد c_parser_prec prec;
    /* The operation on its left.  */
    تعداد درخت_کد_2 op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    درخت sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    درخت orig_عبارت;
  } پشته[رقم_PRECS];
  صحيح sp;
  /* Location of the binary operator.  */
  location_t دودویی_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#تعریف_کن برداشت_2								      \
  افعل {									      \
    بدل (پشته[sp].op)						      \
      {									      \
      حالة TRUTH_ANDIF_عبارت:						      \
	c_inhibit_evaluation_warnings -= (پشته[sp - 1].عبارت.مقدار	      \
					  == truthvalue_false_گره);	      \
	اكسر;								      \
      حالة TRUTH_ORIF_عبارت:						      \
	c_inhibit_evaluation_warnings -= (پشته[sp - 1].عبارت.مقدار	      \
					  == truthvalue_true_گره);	      \
	اكسر;								      \
      حالة TRUNC_DIV_عبارت:						      \
	إذا ((پشته[sp - 1].عبارت.original_کد == SIZEOF_عبارت		      \
	     || پشته[sp - 1].عبارت.original_کد == PAREN_SIZEOF_عبارت)	      \
	    && (پشته[sp].عبارت.original_کد == SIZEOF_عبارت		      \
		|| پشته[sp].عبارت.original_کد == PAREN_SIZEOF_عبارت))	      \
	  {								      \
	    درخت type0 = پشته[sp - 1].sizeof_arg;			      \
	    درخت type1 = پشته[sp].sizeof_arg;				      \
	    درخت اولی_arg = type0;					      \
	    إذا (!TYPE_P (type0))					      \
	      type0 = درخت_TYPE (type0);				      \
	    إذا (!TYPE_P (type1))					      \
	      type1 = درخت_TYPE (type1);				      \
	    إذا (اشاره_گر_TYPE_P (type0)					      \
		&& comptypes (درخت_TYPE (type0), type1)			      \
		&& !(درخت_کد (اولی_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (اولی_arg)			      \
		     && warn_sizeof_array_آرگومان))			      \
	      {								      \
		auto_diagnostic_گروه d;				      \
		إذا (warning_at (پشته[sp].loc, OPT_Wsizeof_اشاره_گر_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  إذا (DECL_P (اولی_arg))				      \
		    inform (DECL_منبع_LOCATION (اولی_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    وإلا إذا (درخت_کد (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (درخت_TYPE (type0)))  \
		     && پشته[sp].عبارت.original_کد != PAREN_SIZEOF_عبارت)    \
	      maybe_warn_sizeof_array_div (پشته[sp].loc, اولی_arg, type0,   \
					   پشته[sp].sizeof_arg, type1);      \
	  }								      \
	اكسر;								      \
      افتراضي:								      \
	اكسر;								      \
      }									      \
    پشته[sp - 1].عبارت							      \
      = convert_lvalue_مقصد_rvalue (پشته[sp - 1].loc,			      \
				  پشته[sp - 1].عبارت, درست, درست);	      \
    پشته[sp].عبارت							      \
      = convert_lvalue_مقصد_rvalue (پشته[sp].loc,			      \
				  پشته[sp].عبارت, درست, درست);		      \
    إذا (UNLIKELY (omp_atomic_lhs != NULL_درخت) && sp == 1		      \
	&& ((c_parser_بعدی_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << پشته[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_لغزش)		      \
		     | (1 << PREC_جمع_کن) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_بعدی_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_گره			      \
		     && c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (پشته[sp].prec == PREC_REL || پشته[sp].prec == PREC_EQ)))\
	&& پشته[sp].op != TRUNC_MOD_عبارت				      \
	&& پشته[sp].op != GE_عبارت					      \
	&& پشته[sp].op != LE_عبارت					      \
	&& پشته[sp].op != NE_عبارت					      \
	&& پشته[0].عبارت.مقدار != error_mark_گره			      \
	&& پشته[1].عبارت.مقدار != error_mark_گره			      \
	&& (omp_atomic_lhs == void_list_گره				      \
	    || c_درخت_equal (پشته[0].عبارت.مقدار, omp_atomic_lhs)	      \
	    || c_درخت_equal (پشته[1].عبارت.مقدار, omp_atomic_lhs)	      \
	    || (پشته[sp].op == EQ_عبارت					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	درخت t = make_گره (پشته[1].op);				      \
	درخت_TYPE (t) = درخت_TYPE (پشته[0].عبارت.مقدار);		      \
	درخت_عملوند (t, 0) = پشته[0].عبارت.مقدار;			      \
	درخت_عملوند (t, 1) = پشته[1].عبارت.مقدار;			      \
	پشته[0].عبارت.مقدار = t;					      \
	پشته[0].عبارت.m_decimal = 0;					      \
      }									      \
    وإلا								      \
      پشته[sp - 1].عبارت = parser_build_دودویی_op (پشته[sp].loc,	      \
						   پشته[sp].op,	      \
						   پشته[sp - 1].عبارت,	      \
						   پشته[sp].عبارت,	      \
						   پشته[sp - 1].orig_عبارت);  \
    پشته[sp - 1].orig_عبارت = NULL_درخت;				      \
    sp--;								      \
  } طالما (0)
  gcc_assert (!after || c_dialect_objc ());
  پشته[0].loc = c_parser_peek_token (parser)->location;
  پشته[0].عبارت = c_parser_cast_عبارت (parser, after);
  پشته[0].prec = PREC_NONE;
  پشته[0].sizeof_arg = c_آخرین_sizeof_arg;
  پشته[0].orig_عبارت = NULL_درخت;
  sp = 0;
  طالما (درست)
    {
      تعداد c_parser_prec oprec;
      تعداد درخت_کد_2 ocode;
      منبع_range src_range;
      إذا (parser->error)
	اذهب بیرون;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_عبارت;
	  اكسر;
	حالة CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_عبارت;
	  اكسر;
	حالة CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_عبارت;
	  اكسر;
	حالة CPP_PLUS:
	  oprec = PREC_جمع_کن;
	  ocode = PLUS_عبارت;
	  اكسر;
	حالة CPP_MINUS:
	  oprec = PREC_جمع_کن;
	  ocode = MINUS_عبارت;
	  اكسر;
	حالة CPP_LSHIFT:
	  oprec = PREC_لغزش;
	  ocode = LSHIFT_عبارت;
	  اكسر;
	حالة CPP_RSHIFT:
	  oprec = PREC_لغزش;
	  ocode = RSHIFT_عبارت;
	  اكسر;
	حالة CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_عبارت;
	  اكسر;
	حالة CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_عبارت;
	  اكسر;
	حالة CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_عبارت;
	  اكسر;
	حالة CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_عبارت;
	  اكسر;
	حالة CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_عبارت;
	  اكسر;
	حالة CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_عبارت;
	  اكسر;
	حالة CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = بیت_AND_عبارت;
	  اكسر;
	حالة CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = بیت_XOR_عبارت;
	  اكسر;
	حالة CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = بیت_IOR_عبارت;
	  اكسر;
	حالة CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_عبارت;
	  اكسر;
	حالة CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_عبارت;
	  اكسر;
	افتراضي:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  اذهب بیرون;
	}
      دودویی_loc = c_parser_peek_token (parser)->location;
      طالما (oprec <= پشته[sp].prec)
	برداشت_2;
      c_parser_consume_token (parser);
      بدل (ocode)
	{
	حالة TRUTH_ANDIF_عبارت:
	  src_range = پشته[sp].عبارت.src_range;
	  پشته[sp].عبارت
	    = convert_lvalue_مقصد_rvalue (پشته[sp].loc,
					پشته[sp].عبارت, درست, درست);
	  پشته[sp].orig_عبارت = پشته[sp].عبارت.مقدار;
	  پشته[sp].عبارت.مقدار = c_objc_common_truthvalue_conversion
	    (پشته[sp].loc, default_conversion (پشته[sp].عبارت.مقدار));
	  c_inhibit_evaluation_warnings += (پشته[sp].عبارت.مقدار
					    == truthvalue_false_گره);
	  مجموعه_c_عبارت_منبع_range (&پشته[sp].عبارت, src_range);
	  اكسر;
	حالة TRUTH_ORIF_عبارت:
	  src_range = پشته[sp].عبارت.src_range;
	  پشته[sp].عبارت
	    = convert_lvalue_مقصد_rvalue (پشته[sp].loc,
					پشته[sp].عبارت, درست, درست);
	  پشته[sp].orig_عبارت = پشته[sp].عبارت.مقدار;
	  پشته[sp].عبارت.مقدار = c_objc_common_truthvalue_conversion
	    (پشته[sp].loc, default_conversion (پشته[sp].عبارت.مقدار));
	  c_inhibit_evaluation_warnings += (پشته[sp].عبارت.مقدار
					    == truthvalue_true_گره);
	  مجموعه_c_عبارت_منبع_range (&پشته[sp].عبارت, src_range);
	  اكسر;
	افتراضي:
	  اكسر;
	}
      sp++;
      پشته[sp].loc = دودویی_loc;
      پشته[sp].عبارت = c_parser_cast_عبارت (parser, عدم);
      پشته[sp].prec = oprec;
      پشته[sp].op = ocode;
      پشته[sp].sizeof_arg = c_آخرین_sizeof_arg;
      پشته[sp].orig_عبارت = NULL_درخت;
    }
 بیرون:
  طالما (sp > 0)
    برداشت_2;
  أرجع پشته[0].عبارت;
#لغو_تعریف برداشت_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

ساكن بنية c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  منطقي دیده_scspec = خطأ;
  بنية c_declspecs *specs = build_null_declspecs ();
  طالما (c_parser_بعدی_token_is (parser, CPP_KEYWORD))
    {
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CONSTEXPR:
	حالة RID_ثبات:
	حالة RID_STATIC:
	حالة RID_THREAD:
	  دیده_scspec = درست;
	  declspecs_جمع_کن_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->مقدار);
	  c_parser_consume_token (parser);
	  اكسر;
	افتراضي:
	  اذهب بیرون;
	}
    }
 بیرون:
  أرجع دیده_scspec ? specs : عدم;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

ساكن بنية c_عبارت
c_parser_cast_عبارت (c_parser *parser, بنية c_عبارت *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  إذا (after)
    أرجع c_parser_postfix_عبارت_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      بنية c_عبارت ret;
      بنية c_عبارت عبارت;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, درست);
      parens.skip_until_یافت_close (parser);
      إذا (type_name == عدم)
	{
	  ret.مجموعه_error ();
	  ret.original_کد = ERROR_MARK;
	  ret.original_type = عدم;
	  أرجع ret;
	}

      /* Save casted types in the function's used types hash table.  */
      استفاده_شده_types_درج (type_name->specs->type);

      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
	أرجع c_parser_postfix_عبارت_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      إذا (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t عبارت_loc = c_parser_peek_token (parser)->location;
	عبارت = c_parser_cast_عبارت (parser, عدم);
	عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, درست, درست);
      }
      ret.مقدار = c_cast_عبارت (cast_loc, type_name, عبارت.مقدار);
      إذا (ret.مقدار && عبارت.مقدار)
	مجموعه_c_عبارت_منبع_range (&ret, cast_loc, عبارت.get_پایان ());
      ret.original_کد = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      أرجع ret;
    }
  وإلا
    أرجع c_parser_unary_عبارت (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

ساكن فراغ
mark_exp_read_cond (درخت نمایی_تابع)
{
  إذا ((VAR_P (نمایی_تابع) || درخت_کد (نمایی_تابع) == PARM_DECL)
      && (VAR_P (نمایی_تابع) ? warn_استفادهنشده_but_مجموعه_variable
		      : warn_استفادهنشده_but_مجموعه_parameter) > 1)
    أرجع;

  mark_exp_read (نمایی_تابع);
}


/* Parse an unary expression (C90 6.3.3, C99 6.5.3, C11 6.5.3).

   unary-expression:
     postfix-expression
     ++ unary-expression
     -- unary-expression
     unary-operator cast-expression
     _Countof unary-expression
     _Countof ( type-name )
     sizeof unary-expression
     sizeof ( type-name )
     static-assert-declaration-no-semi

   (_Countof and the use of static assertions in expressions are new in C2y.)

   unary-operator: one of
     & * + - ~ !

   GNU extensions:

   unary-expression:
     __alignof__ unary-expression
     __alignof__ ( type-name )
     _Maxof ( type-name )
     _Minof ( type-name )
     && identifier

   (C11 permits _Alignof with type names only.)

   unary-operator: one of
     __extension__ __real__ __imag__

   Transactional Memory:

   unary-expression:
     transaction-expression

   In addition, the GNU syntax treats ++ and -- as unary operators, so
   they may be applied to cast expressions with errors for non-lvalues
   given later.  */

ساكن بنية c_عبارت
c_parser_unary_عبارت (c_parser *parser)
{
  صحيح ext;
  بنية c_عبارت ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t پایان;
  ret.original_کد = ERROR_MARK;
  ret.original_type = عدم;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, عدم);
      mark_exp_read_cond (op.مقدار);
      op = default_function_array_conversion (exp_loc, op);
      أرجع parser_build_unary_op (op_loc, PREINCREMENT_عبارت, op);
    حالة CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, عدم);
      mark_exp_read_cond (op.مقدار);
      op = default_function_array_conversion (exp_loc, op);
      أرجع parser_build_unary_op (op_loc, PREDECREMENT_عبارت, op);
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_عبارت (parser, عدم);
      mark_exp_read (op.مقدار);
      أرجع parser_build_unary_op (op_loc, ADDR_عبارت, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_عبارت (parser, عدم);
	پایان = op.get_پایان ();
	op = convert_lvalue_مقصد_rvalue (exp_loc, op, درست, درست);
	location_t combined_loc = make_location (op_loc, op_loc, پایان);
	ret.مقدار = build_غیرمستقیم_ref (combined_loc, op.مقدار, RO_UNARY_ستاره);
	ret.src_range.m_شروع = op_loc;
	ret.src_range.m_پایان = پایان;
	ret.m_decimal = 0;
	أرجع ret;
      }
    حالة CPP_PLUS:
      إذا (!c_dialect_objc () && !درون_system_سرآیند_at (درون_داد_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, عدم);
      op = convert_lvalue_مقصد_rvalue (exp_loc, op, درست, درست);
      أرجع parser_build_unary_op (op_loc, CONVERT_عبارت, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, عدم);
      op = convert_lvalue_مقصد_rvalue (exp_loc, op, درست, درست);
      أرجع parser_build_unary_op (op_loc, NEGATE_عبارت, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, عدم);
      op = convert_lvalue_مقصد_rvalue (exp_loc, op, درست, درست);
      أرجع parser_build_unary_op (op_loc, بیت_NOT_عبارت, op);
    حالة CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_عبارت (parser, عدم);
      op = convert_lvalue_مقصد_rvalue (exp_loc, op, درست, درست);
      أرجع parser_build_unary_op (op_loc, TRUTH_NOT_عبارت, op);
    حالة CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  ret.مقدار = پایان_label_آدرس_عبارت
	    (c_parser_peek_token (parser)->مقدار, op_loc);
	  مجموعه_c_عبارت_منبع_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_پایان ());
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  ret.مجموعه_error ();
	}
      أرجع ret;
    حالة CPP_KEYWORD:
      {
	تعداد rid rid = c_parser_peek_token (parser)->keyword;
	بدل (rid)
	  {
	  حالة RID_COUNTOF:
	  حالة RID_SIZEOF:
	    أرجع c_parser_sizeof_or_countof_عبارت (parser, rid);
	  حالة RID_ALIGNOF:
	    أرجع c_parser_alignof_عبارت (parser);
	  حالة RID_MAXOF:
	  حالة RID_MINOF:
	    أرجع c_parser_maxof_or_minof_عبارت (parser, rid);
	  حالة RID_BUILTIN_HAS_ATTRIBUTE:
	    أرجع c_parser_has_attribute_عبارت (parser);
	  حالة RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_عبارت (parser, عدم);
	    restore_extension_diagnostics (ext);
	    أرجع ret;
	  حالة RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_عبارت (parser, عدم);
	    op = default_function_array_conversion (exp_loc, op);
	    أرجع parser_build_unary_op (op_loc, REALPART_عبارت, op);
	  حالة RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_عبارت (parser, عدم);
	    op = default_function_array_conversion (exp_loc, op);
	    أرجع parser_build_unary_op (op_loc, IMAGPART_عبارت, op);
	  حالة RID_TRANSACTION_ATOMIC:
	  حالة RID_TRANSACTION_RELAXED:
	    أرجع c_parser_transaction_عبارت (parser, rid);
	  حالة RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.مقدار = void_گره;
	    مجموعه_c_عبارت_منبع_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    أرجع ret;
	  افتراضي:
	    أرجع c_parser_postfix_عبارت (parser);
	  }
      }
    افتراضي:
      أرجع c_parser_postfix_عبارت (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

ساكن بنية c_عبارت
c_parser_sizeof_or_countof_عبارت (c_parser *parser, تعداد rid rid)
{
  ثابت حرف *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  بنية c_عبارت عبارت;
  بنية c_عبارت نتیجه;
  location_t عبارت_loc;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, rid));

  location_t شروع;
  location_t پایان = UNKNOWN_LOCATION;

  شروع = c_parser_peek_token (parser)->location;

  إذا (rid == RID_COUNTOF)
    pedwarn_c23 (شروع, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  إذا (rid == RID_COUNTOF)
    درون_countof++;
  وإلا
    درون_sizeof++;
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      عبارت_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, درست);
      parens.skip_until_یافت_close (parser);
      پایان = parser->نشانهها_buf[0].location;
      إذا (type_name == عدم)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  عبارت.مجموعه_error ();
	  اذهب Xof_عبارت;
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
	{
	  عبارت = c_parser_postfix_عبارت_after_paren_type (parser, scspecs,
							       type_name,
							       عبارت_loc);
	  پایان = عبارت.get_پایان ();
	  اذهب Xof_عبارت;
	}
      /* sizeof ( type-name ).  */
      إذا (scspecs)
	error_at (عبارت_loc, "storage class specifier in %qs", op_name);
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      إذا (rid == RID_COUNTOF)
	{
	  درون_countof--;
	  نتیجه = c_عبارت_countof_type (عبارت_loc, type_name);
	}
      وإلا
	{
	  درون_sizeof--;
	  نتیجه = c_عبارت_sizeof_type (عبارت_loc, type_name);
	}
    }
  وإلا
    {
      عبارت_loc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_unary_عبارت (parser);
      پایان = عبارت.get_پایان ();
    Xof_عبارت:
      c_inhibit_evaluation_warnings--;
      إذا (rid == RID_COUNTOF)
	درون_countof--;
      وإلا
	درون_sizeof--;
      mark_exp_read (عبارت.مقدار);
      إذا (درخت_کد (عبارت.مقدار) == COMPONENT_REF
	  && DECL_C_بیت_فیلد (درخت_عملوند (عبارت.مقدار, 1)))
	error_at (عبارت_loc, "%qs applied to a bit-field", op_name);
      إذا (rid == RID_COUNTOF)
	نتیجه = c_عبارت_countof_عبارت (عبارت_loc, عبارت);
      وإلا
	نتیجه = c_عبارت_sizeof_عبارت (عبارت_loc, عبارت);
    }
  إذا (پایان == UNKNOWN_LOCATION)
    پایان = شروع;
  مجموعه_c_عبارت_منبع_range (&نتیجه, شروع, پایان);
  أرجع نتیجه;
}

/* Parse an alignof expression.  */

ساكن بنية c_عبارت
c_parser_alignof_عبارت (c_parser *parser)
{
  بنية c_عبارت عبارت;
  location_t شروع_loc = c_parser_peek_token (parser)->location;
  location_t انتها_loc;
  درخت alignof_spelling = c_parser_peek_token (parser)->مقدار;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_ALIGNOF));
  منطقي is_c11_alignof = (strcmp (IDENTIFIER_اشاره_گر (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_اشاره_گر (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  إذا (is_c11_alignof)
    {
      إذا (flag_isoc99)
	pedwarn_c99 (شروع_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      وإلا
	pedwarn_c99 (شروع_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  درون_alignof++;
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      بنية c_عبارت ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, درست);
      انتها_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_یافت_close (parser);
      إذا (type_name == عدم)
	{
	  بنية c_عبارت ret;
	  c_inhibit_evaluation_warnings--;
	  درون_alignof--;
	  ret.مجموعه_error ();
	  ret.original_کد = ERROR_MARK;
	  ret.original_type = عدم;
	  أرجع ret;
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
	{
	  عبارت = c_parser_postfix_عبارت_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  اذهب alignof_عبارت;
	}
      /* alignof ( type-name ).  */
      إذا (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      درون_alignof--;
      ret.مقدار = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       عدم, عدم),
					    خطأ, is_c11_alignof, 1);
      ret.original_کد = ERROR_MARK;
      ret.original_type = عدم;
      مجموعه_c_عبارت_منبع_range (&ret, شروع_loc, انتها_loc);
      ret.m_decimal = 0;
      أرجع ret;
    }
  وإلا
    {
      بنية c_عبارت ret;
      عبارت = c_parser_unary_عبارت (parser);
      انتها_loc = عبارت.src_range.m_پایان;
    alignof_عبارت:
      mark_exp_read (عبارت.مقدار);
      c_inhibit_evaluation_warnings--;
      درون_alignof--;
      إذا (is_c11_alignof)
	pedwarn (شروع_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.مقدار = c_alignof_عبارت (شروع_loc, عبارت.مقدار);
      ret.original_کد = ERROR_MARK;
      ret.original_type = عدم;
      مجموعه_c_عبارت_منبع_range (&ret, شروع_loc, انتها_loc);
      ret.m_decimal = 0;
      أرجع ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

ساكن بنية c_عبارت
c_parser_maxof_or_minof_عبارت (c_parser *parser, تعداد rid rid)
{
  ثابت حرف *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  بنية c_عبارت نتیجه;
  location_t عبارت_loc;
  بنية c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, rid));

  location_t شروع;
  location_t پایان = UNKNOWN_LOCATION;

  شروع = c_parser_peek_token (parser)->location;

  pedwarn (شروع, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  إذا (!c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      اذهب fail;
    }
  parens.consume_open (parser);
  عبارت_loc = c_parser_peek_token (parser)->location;
  إذا (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (عبارت_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_یافت_close (parser);
      اذهب fail;
    }
  type_name = c_parser_type_name (parser, درست);
  إذا (type_name == عدم)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_یافت_close (parser);
      اذهب fail;
    }
  parens.skip_until_یافت_close (parser);
  پایان = parser->نشانهها_buf[0].location;
  إذا (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  إذا (rid == RID_MAXOF)
    نتیجه = c_عبارت_maxof_type (عبارت_loc, type_name);
  وإلا
    نتیجه = c_عبارت_minof_type (عبارت_loc, type_name);
  مجموعه_c_عبارت_منبع_range (&نتیجه, شروع, پایان);
  أرجع نتیجه;
fail:
  c_inhibit_evaluation_warnings--;
  نتیجه.مجموعه_error ();
  نتیجه.original_کد = ERROR_MARK;
  نتیجه.original_type = عدم;
  أرجع نتیجه;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

ساكن بنية c_عبارت
c_parser_has_attribute_عبارت (c_parser *parser)
{
  gcc_assert (c_parser_بعدی_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t شروع = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      درون_typeof--;

      بنية c_عبارت نتیجه;
      نتیجه.مجموعه_error ();
      نتیجه.original_کد = ERROR_MARK;
      نتیجه.original_type = عدم;
      أرجع نتیجه;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  درون_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  درخت oper = NULL_درخت;
  إذا (c_parser_بعدی_نشانهها_شروع_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *tname = c_parser_type_name (parser);
      درون_typeof--;
      إذا (tname)
	{
	  oper = groktypename (tname, عدم, عدم);
	  برداشت_maybe_استفاده_شده (c_type_variably_modified_p (oper));
	}
    }
  وإلا
    {
      بنية c_عبارت cexpr = c_parser_عبارت_no_commas (parser, عدم);
      c_inhibit_evaluation_warnings--;
      درون_typeof--;
      إذا (cexpr.مقدار != error_mark_گره)
	{
	  mark_exp_read (cexpr.مقدار);
	  oper = cexpr.مقدار;
	  درخت etype = درخت_TYPE (oper);
	  منطقي was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  إذا (was_vm)
	    oper = c_fully_fold (oper, خطأ, عدم);
	  برداشت_maybe_استفاده_شده (was_vm);
	}
    }

  بنية c_عبارت نتیجه;
  نتیجه.original_کد = ERROR_MARK;
  نتیجه.original_type = عدم;

  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      نتیجه.مجموعه_error ();
      أرجع نتیجه;
    }

  منطقي save_translate_رشتهها_p = parser->translate_رشتهها_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  درخت attr = c_parser_gnu_attribute (parser, NULL_درخت, خطأ, خطأ);

  parser->translate_رشتهها_p = save_translate_رشتهها_p;

  location_t پایان = c_parser_peek_token (parser)->location;
  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);

      نتیجه.مجموعه_error ();
      أرجع نتیجه;
    }

  إذا (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      نتیجه.مجموعه_error ();
      أرجع نتیجه;
    }

  نتیجه.original_کد = INTEGER_CST;
  نتیجه.original_type = boolean_type_گره;

  إذا (has_attribute (atloc, oper, attr, default_conversion))
    نتیجه.مقدار = boolean_true_گره;
  وإلا
    نتیجه.مقدار =  boolean_false_گره;

  مجموعه_c_عبارت_منبع_range (&نتیجه, شروع, پایان);
  نتیجه.m_decimal = 0;
  أرجع نتیجه;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
ساكن منطقي
c_parser_get_builtin_آرگومانها (c_parser *parser, ثابت حرف *bname,
			   vec<c_عبارت_t, va_gc> **ret_cexpr_list,
			   منطقي انتخاب_عبارت_p,
			   location_t *بیرون_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_عبارت_t, va_gc> *cexpr_list;
  c_عبارت_t عبارت;
  منطقي saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = عدم;
  إذا (c_parser_بعدی_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      أرجع خطأ;
    }

  c_parser_consume_token (parser);

  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
    {
      *بیرون_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      أرجع درست;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= انتخاب_عبارت_p;
  عبارت = c_parser_عبارت_no_commas (parser, عدم);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_امن_افزودن (cexpr_list, عبارت);
  طالما (c_parser_بعدی_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  درخت مقدار = embed->مقدار;
	  عبارت.original_کد = INTEGER_CST;
	  عبارت.original_type = integer_type_گره;
	  عبارت.مقدار = NULL_درخت;
	  مجموعه_c_عبارت_منبع_range (&عبارت, embed->get_range ());
	  عبارت.m_decimal = 0;
	  لكل (بیعلامت صحيح i = 0; i < (بیعلامت) RAW_داده_درازی (مقدار); i++)
	    {
	      عبارت.مقدار = build_int_cst (integer_type_گره,
					  RAW_داده_UCHAR_ELT (مقدار, i));
	      vec_امن_افزودن (cexpr_list, عبارت);
	    }
	  c_parser_consume_token (parser);
	  استمر;
	}
      عبارت = c_parser_عبارت_no_commas (parser, عدم);
      vec_امن_افزودن (cexpr_list, عبارت);
    }

  *بیرون_close_paren_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع خطأ;

  *ret_cexpr_list = cexpr_list;
  أرجع درست;
}

/* This represents a single generic-association.  */

بنية c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  درخت type;
  /* The association's expression.  */
  بنية c_عبارت عبارت_2;
};

/* Parse a generic-selection.  (C11 6.5.1.1).

   generic-selection:
     _Generic ( generic-controlling-operand , generic-assoc-list )

  generic-controlling-operand:
    assignment-expression
    type-name

  (The use of a type-name is new in C2Y.)

   generic-assoc-list:
     generic-association
     generic-assoc-list , generic-association

   generic-association:
     type-name : assignment-expression
     default : assignment-expression
*/

ساكن بنية c_عبارت
c_parser_generic_selection (c_parser *parser)
{
  بنية c_عبارت selector, error_عبارت;
  درخت selector_type;
  بنية c_generic_association matched_assoc;
  صحيح تطابق_یافت = -1;
  location_t generic_loc, selector_loc;

  error_عبارت.original_کد = ERROR_MARK;
  error_عبارت.original_type = عدم;
  error_عبارت.مجموعه_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_درخت;
  matched_assoc.عبارت_2 = error_عبارت;

  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  إذا (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  وإلا
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_عبارت;

  selector_loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_بعدی_نشانهها_شروع_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      بنية c_type_name *type = c_parser_type_name (parser);
      إذا (type)
	selector_type = groktypename (type, عدم, عدم);
      c_inhibit_evaluation_warnings--;
      إذا (!type)
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_عبارت;
	}
    }
  وإلا
    {
      c_inhibit_evaluation_warnings++;
      درون_generic++;
      selector = c_parser_عبارت_no_commas (parser, عدم);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      درون_generic--;
      برداشت_maybe_استفاده_شده (!flag_isoc23);

      إذا (selector.مقدار == error_mark_گره)
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع selector;
	}
      mark_exp_read (selector.مقدار);
      selector_type = درخت_TYPE (selector.مقدار);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      إذا (درخت_کد (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      إذا (FUNCTION_اشاره_گر_TYPE_P (selector_type)
	  && TYPE_QUALS (درخت_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_اشاره_گر_type (TYPE_MAIN_VARIANT (درخت_TYPE (selector_type)));
    }

  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
      أرجع error_عبارت;
    }

  auto_vec<c_generic_association> associations;
  بنية maybe_استفاده_شده_decl *maybe_استفاده_شده_default = عدم;
  طالما (1)
    {
      بنية c_generic_association assoc, *iter;
      بیعلامت صحيح ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      إذا (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_درخت;
	}
      وإلا
	{
	  بنية c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  إذا (type_name == عدم)
	    {
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع error_عبارت;
	    }
	  assoc.type = grokgenassoc (type_name);
	  إذا (assoc.type == error_mark_گره)
	    {
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع error_عبارت;
	    }

	  إذا (درخت_کد (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  وإلا إذا (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  إذا (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_عبارت;
	}

      منطقي تطابق = assoc.type == NULL_درخت
		   || comptypes (assoc.type, selector_type);

      إذا (!تطابق || matched_assoc.type != NULL_درخت)
	c_inhibit_evaluation_warnings++;
      درون_generic++;

      assoc.عبارت_2 = c_parser_عبارت_no_commas (parser, عدم);

      إذا (!تطابق || matched_assoc.type != NULL_درخت)
	c_inhibit_evaluation_warnings--;
      درون_generic--;
      إذا (!تطابق)
	برداشت_maybe_استفاده_شده (!flag_isoc23);
      وإلا إذا (assoc.type == NULL_درخت)
	maybe_استفاده_شده_default = save_maybe_استفاده_شده ();
      وإلا
	برداشت_maybe_استفاده_شده (درست);

      إذا (assoc.عبارت_2.مقدار == error_mark_گره)
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_عبارت;
	}

      لكل (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  إذا (assoc.type == NULL_درخت)
	    {
	      إذا (iter->type == NULL_درخت)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  وإلا إذا (iter->type != NULL_درخت)
	    {
	      إذا (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      إذا (assoc.type == NULL_درخت)
	{
	  إذا (تطابق_یافت < 0)
	    {
	      matched_assoc = assoc;
	      تطابق_یافت = associations.درازی ();
	    }
	}
      وإلا إذا (تطابق)
	{
	  إذا (تطابق_یافت < 0 || matched_assoc.type == NULL_درخت)
	    {
	      matched_assoc = assoc;
	      تطابق_یافت = associations.درازی ();
	    }
	  وإلا
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.امن_افزودن (assoc);

      إذا (c_parser_peek_token (parser)->type != CPP_COMMA)
	اكسر;
      c_parser_consume_token (parser);
    }

  إذا (تطابق_یافت >= 0 && matched_assoc.type == NULL_درخت)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_استفاده_شده (maybe_استفاده_شده_default);
      برداشت_maybe_استفاده_شده (درست);
    }
  وإلا إذا (maybe_استفاده_شده_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_استفاده_شده (maybe_استفاده_شده_default);
      برداشت_maybe_استفاده_شده (!flag_isoc23);
    }

  بیعلامت صحيح ix;
  بنية c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    إذا (ix != (بیعلامت) تطابق_یافت)
      mark_exp_read (iter->عبارت_2.مقدار);

  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
      أرجع error_عبارت;
    }

  إذا (تطابق_یافت < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      أرجع error_عبارت;
    }

  أرجع matched_assoc.عبارت_2;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

ساكن بیعلامت صحيح
check_tgmath_function (c_عبارت *عبارت, بیعلامت صحيح pos)
{
  درخت type = درخت_TYPE (عبارت->مقدار);
  إذا (!FUNCTION_اشاره_گر_TYPE_P (type))
    {
      error_at (عبارت->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      أرجع 0;
    }
  type = درخت_TYPE (type);
  إذا (!prototype_p (type))
    {
      error_at (عبارت->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      أرجع 0;
    }
  إذا (stdarg_p (type))
    {
      error_at (عبارت->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      أرجع 0;
    }
  بیعلامت صحيح nargs = 0;
  function_آرگومانها_iterator iter;
  درخت t;
  FOREACH_FUNCTION_آرگومانها (type, t, iter)
    {
      إذا (t == void_type_گره)
	اكسر;
      nargs++;
    }
  إذا (nargs == 0)
    {
      error_at (عبارت->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      أرجع 0;
    }
  أرجع nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
تعداد tgmath_parm_نوع
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

ساكن بنية c_عبارت
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  بدل (c_parser_peek_token (parser)->keyword)
    {
    حالة RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      اكسر;
    حالة RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      اكسر;
    حالة RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  بنية c_عبارت عبارت;
  عبارت.original_کد = ERROR_MARK;
  عبارت.original_type = عدم;
  عبارت.مقدار = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->مقدار);
  مجموعه_c_عبارت_منبع_range (&عبارت, loc, loc);
  عبارت.m_decimal = 0;
  c_parser_consume_token (parser);
  أرجع عبارت;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

ساكن منطقي
has_counted_by_object (درخت ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  إذا ((درخت_کد (ref) == غیرمستقیم_REF
       && is_access_with_اندازه_p (درخت_عملوند (ref, 0)))
      || is_access_with_اندازه_p (ref))
    أرجع درست;
  أرجع خطأ;
}

/* Get the reference to the counted-by object associated with the REF.  */

ساكن درخت
get_counted_by_ref (درخت ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  إذا (درخت_کد (ref) == غیرمستقیم_REF
      && is_access_with_اندازه_p (درخت_عملوند (ref, 0)))
    أرجع CALL_عبارت_ARG (درخت_عملوند (ref, 0), 1);
  وإلا إذا (is_access_with_اندازه_p (ref))
    أرجع CALL_عبارت_ARG (ref, 1);

  أرجع NULL_درخت;
}

/* Parse a postfix expression (C90 6.3.1-6.3.2, C99 6.5.1-6.5.2,
   C11 6.5.1-6.5.2).  Compound literals aren't handled here; callers have to
   call c_parser_postfix_expression_after_paren_type on encountering them.

   postfix-expression:
     primary-expression
     postfix-expression [ expression ]
     postfix-expression ( argument-expression-list[opt] )
     postfix-expression . identifier
     postfix-expression -> identifier
     postfix-expression ++
     postfix-expression --
     ( storage-class-specifiers[opt] type-name ) { initializer-list[opt] }
     ( storage-class-specifiers[opt] type-name ) { initializer-list , }

   argument-expression-list:
     argument-expression
     argument-expression-list , argument-expression

   primary-expression:
     identifier
     constant
     string-literal
     ( expression )
     generic-selection

   GNU extensions:

   primary-expression:
     __func__
       (treated as a keyword in GNU C)
     __FUNCTION__
     __PRETTY_FUNCTION__
     ( compound-statement )
     __builtin_va_arg ( assignment-expression , type-name )
     __builtin_offsetof ( type-name , offsetof-member-designator )
     __builtin_choose_expr ( assignment-expression ,
			     assignment-expression ,
			     assignment-expression )
     __builtin_types_compatible_p ( type-name , type-name )
     __builtin_tgmath ( expr-list )
     __builtin_complex ( assignment-expression , assignment-expression )
     __builtin_shuffle ( assignment-expression , assignment-expression )
     __builtin_shuffle ( assignment-expression ,
			 assignment-expression ,
			 assignment-expression, )
     __builtin_convertvector ( assignment-expression , type-name )
     __builtin_assoc_barrier ( assignment-expression )

   offsetof-member-designator:
     identifier
     offsetof-member-designator . identifier
     offsetof-member-designator [ expression ]

   Objective-C:

   primary-expression:
     [ objc-receiver objc-message-args ]
     @selector ( objc-selector-arg )
     @protocol ( identifier )
     @encode ( type-name )
     objc-string-literal
     Classname . identifier
*/

ساكن بنية c_عبارت
c_parser_postfix_عبارت (c_parser *parser)
{
  بنية c_عبارت عبارت, e1;
  بنية c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  منبع_range tok_range = c_parser_peek_token (parser)->get_range ();
  عبارت.original_کد = ERROR_MARK;
  عبارت.original_type = عدم;
  عبارت.m_decimal = 0;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_عدد:
      عبارت.مقدار = c_parser_peek_token (parser)->مقدار;
      مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
      loc = c_parser_peek_token (parser)->location;
      عبارت.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      إذا (درخت_کد (عبارت.مقدار) == FIXED_CST
	  && !targetm.fixed_نقطه_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  عبارت.مجموعه_error ();
	}
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      عبارت.مقدار = c_parser_peek_token (parser)->مقدار;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      عبارت.original_type = char_type_گره;
      مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      عبارت = c_parser_string_literal (parser, parser->translate_رشتهها_p,
				      درست);
      اكسر;
    حالة CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      عبارت.مقدار
	= objc_build_string_object (c_parser_peek_token (parser)->مقدار);
      مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_NAME:
      بدل (c_parser_peek_token (parser)->id_نوع)
	{
	حالة C_ID_ID:
	  {
	    درخت id = c_parser_peek_token (parser)->مقدار;
	    c_parser_consume_token (parser);
	    عبارت.مقدار = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &عبارت.original_type);
	    مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
	    اكسر;
	  }
	حالة C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    درخت class_name = c_parser_peek_token (parser)->مقدار;
	    درخت component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    إذا (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->مقدار;
	    location_t انتها_loc = component_tok->get_پایان ();
	    c_parser_consume_token (parser);
	    عبارت.مقدار = objc_build_class_component_ref (class_name,
							 component);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, انتها_loc);
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser, "expected expression");
	  عبارت.مجموعه_error ();
	  اكسر;
	}
      اكسر;
    حالة CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      إذا (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  درخت stmt;
	  location_t brace_loc;
	  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  إذا (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = درست;
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE, عدم);
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	      عبارت.مجموعه_error ();
	      اكسر;
	    }
	  c_omp_array_section_p = خطأ;
	  stmt = c_begin_stmt_عبارت ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  عبارت.مقدار = c_پایان_stmt_عبارت (brace_loc, stmt);
	  مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_loc);
	  mark_exp_read (عبارت.مقدار);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      وإلا
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  عبارت = c_parser_عبارت (parser);
	  إذا (درخت_کد (عبارت.مقدار) == MODIFY_عبارت)
	    suppress_warning (عبارت.مقدار, OPT_Wparentheses);
	  إذا (عبارت.original_کد != C_MAYBE_CONST_عبارت
	      && عبارت.original_کد != SIZEOF_عبارت)
	    عبارت.original_کد = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  إذا (عبارت.original_کد == SIZEOF_عبارت)
	    عبارت.original_کد = PAREN_SIZEOF_عبارت;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  مجموعه_c_عبارت_منبع_range (&عبارت, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      اكسر;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_FUNCTION_NAME:
	حالة RID_PRETTY_FUNCTION_NAME:
	حالة RID_C99_FUNCTION_NAME:
	  عبارت = c_parser_predefined_identifier (parser);
	  اكسر;
	حالة RID_VA_ARG:
	  {
	    location_t شروع_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    e1 = c_parser_عبارت_no_commas (parser, عدم);
	    mark_exp_read (e1.مقدار);
	    e1.مقدار = c_fully_fold (e1.مقدار, خطأ, عدم);
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t انتها_loc = c_parser_peek_token (parser)->get_پایان ();
	    c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (t1 == عدم)
	      {
		عبارت.مجموعه_error ();
	      }
	    وإلا
	      {
		درخت type_عبارت = NULL_درخت;
		درخت type = groktypename (t1, &type_عبارت, عدم);
		عبارت.مقدار = c_build_va_arg (شروع_loc, e1.مقدار, loc,
					     type, type_عبارت);
		مجموعه_c_عبارت_منبع_range (&عبارت, شروع_loc, انتها_loc);
	      }
	  }
	  اكسر;
	حالة RID_C23_VA_شروع:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    e1 = c_parser_عبارت_no_commas (parser, عدم);
	    e1 = convert_lvalue_مقصد_rvalue (e1.get_location (), e1, درست, درست);
	    إذا (!c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
		    عبارت.مجموعه_error ();
		    اكسر;
		  }
		إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_نوع == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    درخت name = c_parser_peek_token (parser)->مقدار;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    درخت decl = lookup_name (name);
		    درخت آخرین_parm
		      = درخت_آخرین (DECL_ARGUMENTS (current_function_decl));
		    إذا (!آخرین_parm || decl != آخرین_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    وإلا إذا (DECL_ثبات (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		وإلا
		  {
		    بیعلامت nesting_عمق = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    طالما (درست)
		      {
			c_token *token = c_parser_peek_token (parser);
			إذا (token->type == CPP_CLOSE_PAREN && !nesting_عمق)
			  اكسر;

			إذا (token->type == CPP_EOF)
			  اكسر;
			إذا (token->type == CPP_OPEN_PAREN)
			  ++nesting_عمق;
			وإلا إذا (token->type == CPP_CLOSE_PAREN)
			  --nesting_عمق;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    إذا (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_یافت_close (parser);
	    درخت fndecl = builtin_decl_explicit (BUILT_درون_VA_شروع);
	    vec<درخت, va_gc> *params;
	    vec_alloc (params, 2);
	    params->سریع_افزودن (e1.مقدار);
	    params->سریع_افزودن (integer_zero_گره);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.سریع_افزودن (e1.get_location ());
	    arg_loc.سریع_افزودن (UNKNOWN_LOCATION);
	    عبارت.مقدار = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, عدم);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc,
				     parser->نشانهها_buf[0].get_پایان ());
	    عبارت.m_decimal = 0;
	    عبارت.original_کد = ERROR_MARK;
	    عبارت.original_type = عدم;
	    release_درخت_وکتور (params);
	    اكسر;
	  }
	حالة RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      parser->error = درست;
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    إذا (parser->error)
	      {
		c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    درخت type = groktypename (t1, عدم, عدم);
	    درخت offsetof_ref;
	    إذا (type == error_mark_گره)
	      offsetof_ref = error_mark_گره;
	    وإلا
	      {
		offsetof_ref = build1 (غیرمستقیم_REF, type, null_اشاره_گر_گره);
		مجموعه_عبارت_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->مقدار,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		طالما (c_parser_بعدی_token_is (parser, CPP_DOT)
		       || c_parser_بعدی_token_is (parser,
						  CPP_OPEN_مربع)
		       || c_parser_بعدی_token_is (parser,
						  CPP_DEREF))
		  {
		    إذا (c_parser_بعدی_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_گره);
			اذهب do_dot;
		      }
		    وإلا إذا (c_parser_بعدی_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			إذا (c_parser_بعدی_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    اكسر;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->مقدار,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    وإلا
		      {
			بنية c_عبارت ce;
			درخت idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_عبارت (parser);
			ce = convert_lvalue_مقصد_rvalue (loc, ce, خطأ, خطأ);
			idx = ce.مقدار;
			idx = c_fully_fold (idx, خطأ, عدم);
			c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    وإلا
	      c_parser_error (parser, "expected identifier");
	    location_t انتها_loc = c_parser_peek_token (parser)->get_پایان ();
	    c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    عبارت.مقدار = fold_offsetof (offsetof_ref);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, انتها_loc);
	  }
	  اكسر;
	حالة RID_انتخاب_عبارت:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *e1_p, *e2_p, *e3_p;
	    درخت c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, درست,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    إذا (vec_امن_درازی (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->مقدار;
	    mark_exp_read (e2_p->مقدار);
	    mark_exp_read (e3_p->مقدار);
	    إذا (درخت_کد (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (درخت_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_عبارت_warning (c);
	    عبارت = integer_zerop (c) ? *e3_p : *e2_p;
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    t2 = c_parser_type_name (parser);
	    إذا (t2 == عدم)
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_یافت_close (parser);
	    درخت e1, e2;
	    e1 = groktypename (t1, عدم, عدم);
	    e2 = groktypename (t2, عدم, عدم);
	    إذا (e1 == error_mark_گره || e2 == error_mark_گره)
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    عبارت.مقدار
	      = comptypes (e1, e2) ? integer_one_گره : integer_zero_گره;
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	  }
	  اكسر;
	حالة RID_BUILTIN_TGMATH:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser,
					    "__builtin_tgmath",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    إذا (vec_امن_درازی (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    بیعلامت صحيح i;
	    c_عبارت_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_مقصد_rvalue (loc, *p, درست, درست);
	    بیعلامت صحيح nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    إذا (nargs == 0)
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (vec_امن_درازی (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    بیعلامت صحيح رقم_functions = vec_امن_درازی (cexpr_list) - nargs;
	    إذا (رقم_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    لكل (بیعلامت صحيح j = 1; j < رقم_functions; j++)
	      {
		بیعلامت صحيح this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		إذا (this_nargs == 0)
		  {
		    عبارت.مجموعه_error ();
		    اذهب بیرون;
		  }
		إذا (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    عبارت.مجموعه_error ();
		    اذهب بیرون;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<تعداد tgmath_parm_نوع> parm_نوع (nargs + 1);
	    auto_vec<درخت> parm_اولی (nargs + 1);
	    auto_vec<منطقي> parm_complex (nargs + 1);
	    auto_vec<منطقي> parm_varies (nargs + 1);
	    درخت اولی_type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[0].مقدار));
	    درخت اولی_ret = TYPE_MAIN_VARIANT (درخت_TYPE (اولی_type));
	    parm_اولی.سریع_افزودن (اولی_ret);
	    parm_complex.سریع_افزودن (درخت_کد (اولی_ret) == COMPLEX_TYPE);
	    parm_varies.سریع_افزودن (خطأ);
	    function_آرگومانها_iterator iter;
	    درخت t;
	    بیعلامت صحيح argpos;
	    FOREACH_FUNCTION_آرگومانها (اولی_type, t, iter)
	      {
		إذا (t == void_type_گره)
		  اكسر;
		parm_اولی.سریع_افزودن (TYPE_MAIN_VARIANT (t));
		parm_complex.سریع_افزودن (درخت_کد (t) == COMPLEX_TYPE);
		parm_varies.سریع_افزودن (خطأ);
	      }
	    لكل (بیعلامت صحيح j = 1; j < رقم_functions; j++)
	      {
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].مقدار));
		درخت ret = TYPE_MAIN_VARIANT (درخت_TYPE (type));
		إذا (ret != parm_اولی[0])
		  {
		    parm_varies[0] = درست;
		    إذا (!SCALAR_FLOAT_TYPE_P (parm_اولی[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_اولی[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		    إذا (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		  }
		إذا (درخت_کد (ret) == COMPLEX_TYPE)
		  parm_complex[0] = درست;
		argpos = 1;
		FOREACH_FUNCTION_آرگومانها (type, t, iter)
		  {
		    إذا (t == void_type_گره)
		      اكسر;
		    t = TYPE_MAIN_VARIANT (t);
		    إذا (t != parm_اولی[argpos])
		      {
			parm_varies[argpos] = درست;
			إذا (!SCALAR_FLOAT_TYPE_P (parm_اولی[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_اولی[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    عبارت.مجموعه_error ();
			    اذهب بیرون;
			  }
			إذا (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    عبارت.مجموعه_error ();
			    اذهب بیرون;
			  }
		      }
		    إذا (درخت_کد (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = درست;
		    argpos++;
		  }
	      }
	    تعداد tgmath_parm_نوع max_variation = tgmath_fixed;
	    لكل (بیعلامت صحيح j = 0; j <= nargs; j++)
	      {
		تعداد tgmath_parm_نوع this_نوع;
		إذا (parm_varies[j])
		  {
		    إذا (parm_complex[j])
		      max_variation = this_نوع = tgmath_complex;
		    وإلا
		      {
			this_نوع = tgmath_real;
			إذا (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		وإلا
		  this_نوع = tgmath_fixed;
		parm_نوع.سریع_افزودن (this_نوع);
	      }
	    إذا (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    بیعلامت صحيح tgarg = 0;
	    لكل (بیعلامت صحيح j = 1; j <= nargs; j++)
	      إذا (parm_نوع[j] == max_variation)
		{
		  tgarg = j;
		  اكسر;
		}
	    إذا (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<درخت> tg_type (رقم_functions);
	    لكل (بیعلامت صحيح j = 0; j < رقم_functions; j++)
	      {
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].مقدار));
		argpos = 1;
		FOREACH_FUNCTION_آرگومانها (type, t, iter)
		  {
		    إذا (argpos == tgarg)
		      {
			tg_type.سریع_افزودن (TYPE_MAIN_VARIANT (t));
			اكسر;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    منطقي all_complex = درست;
	    منطقي all_دودویی = درست;
	    منطقي all_decimal = درست;
	    hash_مجموعه<درخت> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		إذا (درخت_کد (t) == COMPLEX_TYPE)
		  all_decimal = خطأ;
		وإلا
		  {
		    all_complex = خطأ;
		    إذا (DECIMAL_FLOAT_TYPE_P (t))
		      all_دودویی = خطأ;
		    وإلا
		      all_decimal = خطأ;
		  }
		إذا (tg_types.جمع_کن (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    عبارت.مجموعه_error ();
		    اذهب بیرون;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    لكل (بیعلامت صحيح j = 0; j < رقم_functions; j++)
	      {
		درخت exp_type = tg_type[j];
		درخت exp_real_type = exp_type;
		إذا (درخت_کد (exp_type) == COMPLEX_TYPE)
		  exp_real_type = درخت_TYPE (exp_type);
		درخت type = درخت_TYPE (درخت_TYPE ((*cexpr_list)[j].مقدار));
		درخت ret = TYPE_MAIN_VARIANT (درخت_TYPE (type));
		إذا ((parm_نوع[0] == tgmath_complex && ret != exp_type)
		    || (parm_نوع[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    عبارت.مجموعه_error ();
		    اذهب بیرون;
		  }
		argpos = 1;
		FOREACH_FUNCTION_آرگومانها (type, t, iter)
		  {
		    إذا (t == void_type_گره)
		      اكسر;
		    t = TYPE_MAIN_VARIANT (t);
		    إذا ((parm_نوع[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_نوع[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		    argpos++;
		  }
	      }

	    /* The functions listed are a valid set of functions for a
	       <tgmath.h> macro to select between.  Identify the
	       matching function, if any.  First, the argument types
	       must be combined following <tgmath.h> rules.  Integer
	       types are treated as _Decimal64 if any type-generic
	       argument is decimal, or if the only alternatives for
	       type-generic arguments are of decimal types, and are
	       otherwise treated as _Float32x (or _Complex _Float32x
	       for complex integer types) if any type-generic argument
	       has _FloatNx type, otherwise as double (or _Complex
	       double for complex integer types).  After that
	       adjustment, types are combined following the usual
	       arithmetic conversions.  If the function only accepts
	       complex arguments, a complex type is produced.  */
	    منطقي arg_complex = all_complex;
	    منطقي arg_دودویی = all_دودویی;
	    منطقي arg_int_decimal = all_decimal;
	    منطقي arg_int_floatnx = خطأ;
	    منطقي arg_int_decimalx = خطأ;
	    لكل (بیعلامت صحيح j = 1; j <= nargs; j++)
	      {
		إذا (parm_نوع[j] == tgmath_fixed)
		  استمر;
		c_عبارت_t *ce = &(*cexpr_list)[رقم_functions + j - 1];
		درخت type = درخت_TYPE (ce->مقدار);
		إذا (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && درخت_کد (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    عبارت.مجموعه_error ();
		    اذهب بیرون;
		  }
		إذا (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = درست;
		    إذا (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		    وإلا إذا (all_دودویی)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		    وإلا إذا (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		    وإلا إذا (arg_دودویی)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		  }
		وإلا إذا (درخت_کد (type) == COMPLEX_TYPE)
		  {
		    arg_complex = درست;
		    إذا (COMPLEX_FLOAT_TYPE_P (type))
		      arg_دودویی = درست;
		    إذا (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		    وإلا إذا (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		  }
		وإلا إذا (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_دودویی = درست;
		    إذا (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		    وإلا إذا (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			عبارت.مجموعه_error ();
			اذهب بیرون;
		      }
		  }
		درخت rtype = TYPE_MAIN_VARIANT (type);
		إذا (درخت_کد (rtype) == COMPLEX_TYPE)
		  rtype = درخت_TYPE (rtype);
		إذا (SCALAR_FLOAT_TYPE_P (rtype))
		  لكل (بیعلامت صحيح j = 0; j < رقم_FLOATNX_TYPES; j++)
		    إذا (rtype == FLOATNX_TYPE_گره (j))
		      {
			arg_int_floatnx = درست;
			اكسر;
		      }
		إذا (rtype == dfloat64x_type_گره)
		  arg_int_decimalx = درست;
	      }
	    درخت arg_real = NULL_درخت;
	    لكل (بیعلامت صحيح j = 1; j <= nargs; j++)
	      {
		إذا (parm_نوع[j] == tgmath_fixed)
		  استمر;
		c_عبارت_t *ce = &(*cexpr_list)[رقم_functions + j - 1];
		درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (ce->مقدار));
		إذا (درخت_کد (type) == COMPLEX_TYPE)
		  type = درخت_TYPE (type);
		إذا (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_گره
			  : arg_int_floatnx
			  ? float32x_type_گره
			  : arg_int_decimal
			  ? dfloat64_type_گره
			  : double_type_گره);
		إذا (arg_real == NULL_درخت)
		  arg_real = type;
		وإلا
		  arg_real = common_type (arg_real, type);
		إذا (arg_real == error_mark_گره)
		  {
		    عبارت.مجموعه_error ();
		    اذهب بیرون;
		  }
	      }
	    درخت arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_عبارت_t *fn = عدم;
	    لكل (بیعلامت صحيح j = 0; j < رقم_functions; j++)
	      {
		إذا (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    اكسر;
		  }
	      }
	    إذا (fn == عدم
		&& parm_نوع[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_اولی[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		لكل (بیعلامت صحيح j = 0; j < رقم_functions; j++)
		  {
		    إذا (arg_complex
			!= (درخت_کد (tg_type[j]) == COMPLEX_TYPE))
		      استمر;
		    درخت real_tg_type = (arg_complex
					 ? درخت_TYPE (tg_type[j])
					 : tg_type[j]);
		    إذا (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      استمر;
		    scalar_float_نما arg_نما
		      = SCALAR_FLOAT_TYPE_نما (arg_real);
		    scalar_float_نما tg_نما
		      = SCALAR_FLOAT_TYPE_نما (real_tg_type);
		    ثابت real_format *arg_fmt = REAL_نما_FORMAT (arg_نما);
		    ثابت real_format *tg_fmt = REAL_نما_FORMAT (tg_نما);
		    إذا (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			اكسر;
		      }
		  }
	      }
	    إذا (fn == عدم)
	      {
		error_at (loc, "no matching function for type-generic call");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    /* Construct a call to FN.  */
	    vec<درخت, va_gc> *آرگومانها;
	    vec_alloc (آرگومانها, nargs);
	    vec<درخت, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    لكل (بیعلامت صحيح j = 0; j < nargs; j++)
	      {
		c_عبارت_t *ce = &(*cexpr_list)[رقم_functions + j];
		آرگومانها->سریع_افزودن (ce->مقدار);
		arg_loc.سریع_افزودن (ce->get_location ());
		origtypes->سریع_افزودن (ce->original_type);
	      }
	    عبارت.مقدار = c_build_function_call_vec (loc, arg_loc, fn->مقدار,
						    آرگومانها, origtypes);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *e2_p;
	    درخت chain_مقدار;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (vec_امن_درازی (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    عبارت = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_مقصد_rvalue (loc, *e2_p, درست, درست);
	    chain_مقدار = e2_p->مقدار;
	    mark_exp_read (chain_مقدار);

	    إذا (درخت_کد (عبارت.مقدار) != CALL_عبارت)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    وإلا إذا (درخت_کد (درخت_TYPE (chain_مقدار)) != اشاره_گر_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    وإلا
	      CALL_عبارت_STATIC_CHAIN (عبارت.مقدار) = chain_مقدار;
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_COMPLEX:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser,
					    "__builtin_complex",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    إذا (vec_امن_درازی (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_مقصد_rvalue (loc, *e1_p, درست, درست);
	    إذا (درخت_کد (e1_p->مقدار) == EXCESS_PRECISION_عبارت)
	      e1_p->مقدار = convert (درخت_TYPE (e1_p->مقدار),
				     درخت_عملوند (e1_p->مقدار, 0));
	    *e2_p = convert_lvalue_مقصد_rvalue (loc, *e2_p, درست, درست);
	    إذا (درخت_کد (e2_p->مقدار) == EXCESS_PRECISION_عبارت)
	      e2_p->مقدار = convert (درخت_TYPE (e2_p->مقدار),
				     درخت_عملوند (e2_p->مقدار, 0));
	    إذا (!SCALAR_FLOAT_TYPE_P (درخت_TYPE (e1_p->مقدار))
		|| DECIMAL_FLOAT_TYPE_P (درخت_TYPE (e1_p->مقدار))
		|| !SCALAR_FLOAT_TYPE_P (درخت_TYPE (e2_p->مقدار))
		|| DECIMAL_FLOAT_TYPE_P (درخت_TYPE (e2_p->مقدار)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (TYPE_MAIN_VARIANT (درخت_TYPE (e1_p->مقدار))
		!= TYPE_MAIN_VARIANT (درخت_TYPE (e2_p->مقدار)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    عبارت.مقدار = build2_loc (loc, COMPLEX_عبارت,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (درخت_TYPE (e1_p->مقدار))),
				     e1_p->مقدار, e2_p->مقدار);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (vec_امن_درازی (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    e_p = &(*cexpr_list)[0];
	    درخت ref = e_p->مقدار;

	    إذا (درخت_کد (درخت_TYPE (ref)) != ARRAY_TYPE
		 && درخت_کد (درخت_TYPE (ref)) != اشاره_گر_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    إذا (درخت_کد (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    إذا (درخت_کد (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    إذا (has_counted_by_object (ref))
	      عبارت.مقدار = get_counted_by_ref (ref);
	    وإلا
	      عبارت.مقدار = null_اشاره_گر_گره;

	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    بیعلامت صحيح i;
	    c_عبارت_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser,
					    "__builtin_shuffle",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    FOR_EACH_VEC_امن_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_مقصد_rvalue (loc, *p, درست, درست);

	    إذا (vec_امن_درازی (cexpr_list) == 2)
	      عبارت.مقدار = c_build_vec_perm_عبارت (loc, (*cexpr_list)[0].مقدار,
						  NULL_درخت,
						  (*cexpr_list)[1].مقدار);

	    وإلا إذا (vec_امن_درازی (cexpr_list) == 3)
	      عبارت.مقدار = c_build_vec_perm_عبارت (loc, (*cexpr_list)[0].مقدار,
						  (*cexpr_list)[1].مقدار,
						  (*cexpr_list)[2].مقدار);
	    وإلا
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		عبارت.مجموعه_error ();
	      }
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    بیعلامت صحيح i;
	    c_عبارت_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    FOR_EACH_VEC_امن_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_مقصد_rvalue (loc, *p, درست, درست);

	    إذا (vec_امن_درازی (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		عبارت.مجموعه_error ();
	      }
	    وإلا
	      {
		auto_vec<درخت, 16> ماسک;
		لكل (i = 2; i < cexpr_list->درازی (); ++i)
		  ماسک.امن_افزودن ((*cexpr_list)[i].مقدار);
		عبارت.مقدار = c_build_shufflevector (loc, (*cexpr_list)[0].مقدار,
						    (*cexpr_list)[1].مقدار,
						    ماسک);
	      }
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t شروع_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    e1 = c_parser_عبارت_no_commas (parser, عدم);
	    mark_exp_read (e1.مقدار);
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t انتها_loc = c_parser_peek_token (parser)->get_پایان ();
	    c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (t1 == عدم)
	      عبارت.مجموعه_error ();
	    وإلا
	      {
		درخت type_عبارت = NULL_درخت;
		عبارت.مقدار = c_build_vec_convert (شروع_loc, e1.مقدار, loc,
						  groktypename (t1, &type_عبارت,
								عدم));
		مجموعه_c_عبارت_منبع_range (&عبارت, شروع_loc, انتها_loc);
	      }
	  }
	  اكسر;
	حالة RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t شروع_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    e1 = c_parser_عبارت_no_commas (parser, عدم);
	    mark_exp_read (e1.مقدار);
	    location_t انتها_loc = c_parser_peek_token (parser)->get_پایان ();
	    parens.skip_until_یافت_close (parser);
	    عبارت = parser_build_unary_op (loc, PAREN_عبارت, e1);
	    مجموعه_c_عبارت_منبع_range (&عبارت, شروع_loc, انتها_loc);
	  }
	  اكسر;
	حالة RID_BUILTIN_STDC:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    c_عبارت_t *arg_p;
	    location_t close_paren_loc;
	    تعداد c_builtin_stdc {
	      C_BUILTIN_STDC_بیت_CEIL,
	      C_BUILTIN_STDC_بیت_FLOOR,
	      C_BUILTIN_STDC_بیت_عرض,
	      C_BUILTIN_STDC_شمار_ONES,
	      C_BUILTIN_STDC_شمار_ZEROS,
	      C_BUILTIN_STDC_اولی_LEADING_ONE,
	      C_BUILTIN_STDC_اولی_LEADING_ZERO,
	      C_BUILTIN_STDC_اولی_TRAILING_ONE,
	      C_BUILTIN_STDC_اولی_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_بیت,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_چپ,
	      C_BUILTIN_STDC_ROTATE_راست,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ثابت حرف *name
	      = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	    بیعلامت رقم_آرگومانها = 1;
	    بدل (name[حجم ("__builtin_stdc_") - 1])
	      {
	      حالة 'b':
		بدل (name[حجم ("__builtin_stdc_bit_") - 1])
		  {
		  حالة 'c':
		    stdc_rid = C_BUILTIN_STDC_بیت_CEIL;
		    اكسر;
		  حالة 'f':
		    stdc_rid = C_BUILTIN_STDC_بیت_FLOOR;
		    اكسر;
		  افتراضي:
		    stdc_rid = C_BUILTIN_STDC_بیت_عرض;
		    اكسر;
		  }
		اكسر;
	      حالة 'c':
		إذا (name[حجم ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_شمار_ONES;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_شمار_ZEROS;
		اكسر;
	      حالة 'f':
		بدل (name[حجم ("__builtin_stdc_first_trailing_") - 1])
		  {
		  حالة 'n':
		    stdc_rid = C_BUILTIN_STDC_اولی_LEADING_ONE;
		    اكسر;
		  حالة 'e':
		    stdc_rid = C_BUILTIN_STDC_اولی_LEADING_ZERO;
		    اكسر;
		  حالة 'o':
		    stdc_rid = C_BUILTIN_STDC_اولی_TRAILING_ONE;
		    اكسر;
		  افتراضي:
		    stdc_rid = C_BUILTIN_STDC_اولی_TRAILING_ZERO;
		    اكسر;
		  }
		اكسر;
	      حالة 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_بیت;
		اكسر;
	      حالة 'l':
		إذا (name[حجم ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		اكسر;
	      حالة 'r':
		إذا (name[حجم ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_چپ;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_ROTATE_راست;
		رقم_آرگومانها = 2;
		اكسر;
	      حالة 't':
		إذا (name[حجم ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		اكسر;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser, name,
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    إذا (vec_امن_درازی (cexpr_list) != رقم_آرگومانها)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_مقصد_rvalue (loc, *arg_p, درست, درست);
	    إذا (!INTEGRAL_TYPE_P (درخت_TYPE (arg_p->مقدار)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (درخت_کد (درخت_TYPE (arg_p->مقدار)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (درخت_کد (درخت_TYPE (arg_p->مقدار)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (!TYPE_UNSIGNED (درخت_TYPE (arg_p->مقدار)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (TYPE_MAIN_VARIANT (درخت_TYPE (arg_p->مقدار))
		== char_type_گره)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    درخت arg = arg_p->مقدار;
	    درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (arg));
	    /* Expand:
	       __builtin_stdc_leading_zeros (arg) as
		 (unsigned int) __builtin_clzg (arg, prec)
	       __builtin_stdc_leading_ones (arg) as
		 (unsigned int) __builtin_clzg ((type) ~arg, prec)
	       __builtin_stdc_trailing_zeros (arg) as
		 (unsigned int) __builtin_ctzg (arg, prec)
	       __builtin_stdc_trailing_ones (arg) as
		 (unsigned int) __builtin_ctzg ((type) ~arg, prec)
	       __builtin_stdc_first_leading_zero (arg) as
		 __builtin_clzg ((type) ~arg, -1) + 1U
	       __builtin_stdc_first_leading_one (arg) as
		 __builtin_clzg (arg, -1) + 1U
	       __builtin_stdc_first_trailing_zero (arg) as
		 __builtin_ctzg ((type) ~arg, -1) + 1U
	       __builtin_stdc_first_trailing_one (arg) as
		 __builtin_ctzg (arg, -1) + 1U
	       __builtin_stdc_count_zeros (arg) as
		 (unsigned int) __builtin_popcountg ((type) ~arg)
	       __builtin_stdc_count_ones (arg) as
		 (unsigned int) __builtin_popcountg (arg)
	       __builtin_stdc_has_single_bit (arg) as
		 (_Bool) (__builtin_popcountg (arg) == 1)
	       __builtin_stdc_bit_width (arg) as
		 (unsigned int) (prec - __builtin_clzg (arg, prec))
	       __builtin_stdc_bit_floor (arg) as
		 arg == 0 ? (type) 0
			  : (type) 1 << (prec - 1 - __builtin_clzg (arg))
	       __builtin_stdc_bit_ceil (arg) as
		 arg <= 1 ? (type) 1
			  : (type) 2 << (prec - 1 - __builtin_clzg (arg - 1))
	       without evaluating arg multiple times, type being
	       __typeof (arg) and prec __builtin_popcountg ((type) ~0)).  */
	    صحيح prec = TYPE_PRECISION (type);
	    إذا (رقم_آرگومانها == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_مقصد_rvalue (loc, *arg_p, درست, درست);
		إذا (!INTEGRAL_TYPE_P (درخت_TYPE (arg_p->مقدار)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    عبارت.مجموعه_error ();
		    اكسر;
		  }
		إذا (درخت_کد (درخت_TYPE (arg_p->مقدار)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    عبارت.مجموعه_error ();
		    اكسر;
		  }
		درخت arg1 = save_عبارت (arg);
		درخت arg2 = save_عبارت (arg_p->مقدار);
		درخت_کد_2 کد;
		إذا (stdc_rid == C_BUILTIN_STDC_ROTATE_چپ)
		  کد = LROTATE_عبارت;
		وإلا
		  کد = RROTATE_عبارت;

		إذا (درخت_کد (arg2) == INTEGER_CST
		    && درخت_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_شمار_negative,
			      "rotate count is negative");

		درخت instrument_عبارت = NULL_درخت;
		إذا (sanitize_flags_p (SANITIZE_لغزش))
		  instrument_عبارت = ubsan_instrument_لغزش (loc, کد,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		إذا (TYPE_PRECISION (درخت_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_گره))
		  arg2 = fold_convert (unsigned_type_گره, arg2);

		إذا (TYPE_UNSIGNED (درخت_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_عبارت, درخت_TYPE (arg2),
				     arg2, build_int_cst (درخت_TYPE (arg2),
							  prec));
		وإلا
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    درخت utype = c_common_unsigned_type (درخت_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_عبارت, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		إذا (type_has_نما_precision_p (درخت_TYPE (arg1))
		    || (درخت_کد (درخت_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_نما_اندازه))
		  عبارت.مقدار = build2_loc (loc, کد, درخت_TYPE (arg1), arg1,
					   arg2);
		وإلا
		  {
		    arg2 = save_عبارت (arg2);
		    درخت t1 = build2_loc (loc, (کد == LROTATE_عبارت
						? LSHIFT_عبارت : RSHIFT_عبارت),
					  درخت_TYPE (arg1), arg1, arg2);
		    درخت t2 = build2_loc (loc, MINUS_عبارت,
					  درخت_TYPE (arg2),
					  build_int_cst (درخت_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (کد == LROTATE_عبارت
					   ? RSHIFT_عبارت : LSHIFT_عبارت),
				     درخت_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_شمار_سرریز);
		    درخت t3 = build2_loc (loc, بیت_IOR_عبارت,
					  درخت_TYPE (arg1), t1, t2);
		    درخت t4 = build2_loc (loc, NE_عبارت, boolean_type_گره,
					  arg2,
					  build_zero_cst (درخت_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_عبارت, boolean_type_گره,
				     arg1, t4);
		    عبارت.مقدار = build3_loc (loc, COND_عبارت,
					     درخت_TYPE (arg1), t4, t3, arg1);
		  }
		إذا (instrument_عبارت)
		  عبارت.مقدار = build2_loc (loc, COMPOUND_عبارت,
					   درخت_TYPE (عبارت.مقدار),
					   instrument_عبارت, عبارت.مقدار);
		مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
		اكسر;
	      }
	    درخت barg1 = arg;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_بیت_CEIL:
		arg = save_عبارت (arg);
		barg1 = build2_loc (loc, PLUS_عبارت, type, arg,
				    build_int_cst (type, -1));
		اكسر;
	      حالة C_BUILTIN_STDC_بیت_FLOOR:
		barg1 = arg = save_عبارت (arg);
		اكسر;
	      حالة C_BUILTIN_STDC_شمار_ZEROS:
	      حالة C_BUILTIN_STDC_اولی_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_اولی_TRAILING_ZERO:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, بیت_NOT_عبارت, type, arg);
		اكسر;
	      افتراضي:
		اكسر;
	      }
	    درخت barg2 = NULL_درخت;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_بیت_عرض:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_LEADING_ZEROS:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_گره, prec);
		اكسر;
	      حالة C_BUILTIN_STDC_اولی_LEADING_ONE:
	      حالة C_BUILTIN_STDC_اولی_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_اولی_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_اولی_TRAILING_ZERO:
		barg2 = integer_minus_one_گره;
		اكسر;
	      افتراضي:
		اكسر;
	      }
	    درخت fndecl = NULL_درخت;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_بیت_CEIL:
	      حالة C_BUILTIN_STDC_بیت_FLOOR:
	      حالة C_BUILTIN_STDC_بیت_عرض:
	      حالة C_BUILTIN_STDC_اولی_LEADING_ONE:
	      حالة C_BUILTIN_STDC_اولی_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_درون_CLZG);
		اكسر;
	      حالة C_BUILTIN_STDC_اولی_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_اولی_TRAILING_ZERO:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_درون_CTZG);
		اكسر;
	      حالة C_BUILTIN_STDC_شمار_ONES:
	      حالة C_BUILTIN_STDC_شمار_ZEROS:
	      حالة C_BUILTIN_STDC_HAS_SINGLE_بیت:
		fndecl = builtin_decl_explicit (BUILT_درون_POPCOUNTG);
		اكسر;
	      افتراضي:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    صحيح nargs = barg2 != NULL_درخت ? 2 : 1;
	    vec<درخت, va_gc> *آرگومانها;
	    vec_alloc (آرگومانها, nargs);
	    vec<درخت, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    آرگومانها->سریع_افزودن (barg1);
	    arg_loc.سریع_افزودن (arg_p->get_location ());
	    origtypes->سریع_افزودن (arg_p->original_type);
	    إذا (nargs == 2)
	      {
		آرگومانها->سریع_افزودن (barg2);
		arg_loc.سریع_افزودن (loc);
		origtypes->سریع_افزودن (integer_type_گره);
	      }
	    عبارت.مقدار = c_build_function_call_vec (loc, arg_loc, fndecl,
						    آرگومانها, origtypes);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    إذا (عبارت.مقدار == error_mark_گره)
	      اكسر;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_بیت_CEIL:
	      حالة C_BUILTIN_STDC_بیت_FLOOR:
		--prec;
		/* FALLTHRU */
	      حالة C_BUILTIN_STDC_بیت_عرض:
		عبارت.مقدار = build2_loc (loc, MINUS_عبارت, integer_type_گره,
					 build_int_cst (integer_type_گره,
							prec), عبارت.مقدار);
		اكسر;
	      حالة C_BUILTIN_STDC_اولی_LEADING_ONE:
	      حالة C_BUILTIN_STDC_اولی_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_اولی_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_اولی_TRAILING_ZERO:
		عبارت.مقدار = build2_loc (loc, PLUS_عبارت, integer_type_گره,
					 عبارت.مقدار, integer_one_گره);
		اكسر;
	      حالة C_BUILTIN_STDC_HAS_SINGLE_بیت:
		عبارت.مقدار = build2_loc (loc, EQ_عبارت, boolean_type_گره,
					 عبارت.مقدار, integer_one_گره);
		اكسر;
	      افتراضي:
		اكسر;
	      }

	    إذا (stdc_rid != C_BUILTIN_STDC_بیت_CEIL
		&& stdc_rid != C_BUILTIN_STDC_بیت_FLOOR)
	      {
		إذا (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_بیت)
		  عبارت.مقدار = fold_convert_loc (loc, unsigned_type_گره,
						 عبارت.مقدار);
		اكسر;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    إذا (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_بیت_CEIL && integer_onep (arg)))
	      عبارت.مقدار = build_int_cst (type, 0);
	    وإلا
	      عبارت.مقدار
		= build2_loc (loc, LSHIFT_عبارت, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_بیت_CEIL
					      ? 2 : 1)), عبارت.مقدار);
	    إذا (stdc_rid == C_BUILTIN_STDC_بیت_CEIL)
	      عبارت.مقدار = build3_loc (loc, COND_عبارت, type,
				       build2_loc (loc, LE_عبارت,
						   boolean_type_گره, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       عبارت.مقدار);
	    وإلا
	      عبارت.مقدار = build3_loc (loc, COND_عبارت, type,
				       build2_loc (loc, EQ_عبارت,
						   boolean_type_گره, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       عبارت.مقدار);
	    اكسر;
	  }
	حالة RID_BUILTIN_BSWAPG:
	حالة RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_عبارت_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    داخلی_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ثابت حرف *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_آرگومانها (parser, name, &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    إذا (vec_امن_درازی (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		عبارت.مجموعه_error ();
		اكسر;
	      }

	    c_عبارت_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_مقصد_rvalue (loc, *arg_p, درست, درست);
	    درخت arg = arg_p->مقدار;
	    إذا (error_عملوند_p (arg))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (arg));
	    إذا (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (درخت_کد (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (درخت_کد (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    arg = c_fully_fold (arg, خطأ, عدم);
	    عبارت.مقدار = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    درخت sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_یافت_close (parser);
	    عبارت.مقدار = objc_build_selector_عبارت (loc, sel);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_loc);
	  }
	  اكسر;
	حالة RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    درخت id = c_parser_peek_token (parser)->مقدار;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_یافت_close (parser);
	    عبارت.مقدار = objc_build_protocol_عبارت (id);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_loc);
	  }
	  اكسر;
	حالة RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      {
		عبارت.مجموعه_error ();
		c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
		اكسر;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_یافت_close (parser);
	    درخت type = groktypename (t1, عدم, عدم);
	    عبارت.مقدار = objc_build_encode_عبارت (type);
	    مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_loc);
	  }
	  اكسر;
	حالة RID_GENERIC:
	  عبارت = c_parser_generic_selection (parser);
	  اكسر;
	حالة RID_OMP_ALL_حافظه:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  عبارت.مجموعه_error ();
	  اكسر;
	/* C23 'nullptr' literal.  */
	حالة RID_NULLPTR:
	  c_parser_consume_token (parser);
	  عبارت.مقدار = nullptr_گره;
	  مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  اكسر;
	حالة RID_TRUE:
	  c_parser_consume_token (parser);
	  عبارت.مقدار = boolean_true_گره;
	  مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
	  اكسر;
	حالة RID_FALSE:
	  c_parser_consume_token (parser);
	  عبارت.مقدار = boolean_false_گره;
	  مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected expression");
	  عبارت.مجموعه_error ();
	  اكسر;
	}
      اكسر;
    حالة CPP_OPEN_مربع:
      إذا (c_dialect_objc ())
	{
	  درخت receiver, آرگومانها;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  آرگومانها = c_parser_objc_پیام_آرگومانها (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع,
				     "expected %<]%>");
	  عبارت.مقدار = objc_build_پیام_عبارت (receiver, آرگومانها);
	  مجموعه_c_عبارت_منبع_range (&عبارت, loc, close_loc);
	  اكسر;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    افتراضي:
      c_parser_error (parser, "expected expression");
      عبارت.مجموعه_error ();
      اكسر;
    }
 بیرون:
  أرجع c_parser_postfix_عبارت_after_primary
    (parser, عبارت_LOC_OR_LOC (عبارت.مقدار, loc), عبارت);
}

/* Parse a postfix expression after a parenthesized type name: the
   brace-enclosed initializer of a compound literal, possibly followed
   by some postfix operators.  This is separate because it is not
   possible to tell until after the type name whether a cast
   expression has a cast or a compound literal, or whether the operand
   of sizeof is a parenthesized type name or starts with a compound
   literal.  TYPE_LOC is the location where TYPE_NAME starts--the
   location of the first token after the parentheses around the type
   name.  */

ساكن بنية c_عبارت
c_parser_postfix_عبارت_after_paren_type (c_parser *parser,
					      بنية c_declspecs *scspecs,
					      بنية c_type_name *type_name,
					      location_t type_loc)
{
  درخت type;
  بنية c_عبارت init;
  منطقي non_const;
  بنية c_عبارت عبارت;
  location_t شروع_loc;
  درخت type_عبارت = NULL_درخت;
  منطقي type_عبارت_const = درست;
  منطقي constexpr_p = scspecs ? scspecs->constexpr_p : خطأ;
  بیعلامت صحيح underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (سطر_جدول, type_loc);
  شروع_loc = c_parser_peek_token (parser)->location;
  إذا (constexpr_p)
    {
      underspec_state = شروع_underspecified_init (شروع_loc, NULL_درخت);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      بدل (type_name->specs->typespec_نوع)
	{
	حالة ctsk_tagfirstref:
	حالة ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  اكسر;

	حالة ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  اكسر;

	افتراضي:
	  اكسر;
	}
    }
  شروع_init (NULL_درخت, عدم,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_عبارت, &type_عبارت_const);
  منطقي varsize_p = خطأ;
  إذا (type != error_mark_گره && C_TYPE_VARIABLE_اندازه (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = درست;
    }
  وإلا إذا (درخت_کد (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_گره;
    }
  إذا (constexpr_p && type != error_mark_گره)
    {
      درخت type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      إذا (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      وإلا إذا (رکورد_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, خطأ, عدم, varsize_p);
  إذا (constexpr_p)
    پایان_underspecified_init (NULL_درخت, underspec_state);
  پایان_init ();
  maybe_warn_string_init (type_loc, type, init);

  إذا (type != error_mark_گره
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_گره;
    }

  إذا (!pedwarn_c90 (شروع_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (شروع_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.مقدار && درخت_کد (init.مقدار) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.مقدار)
	       : init.original_کد == C_MAYBE_CONST_عبارت);
  non_const |= !type_عبارت_const;
  بیعلامت صحيح alignas_align = 0;
  إذا (type != error_mark_گره
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      إذا (alignas_align < min_align_از_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  عبارت.مقدار = build_compound_literal (شروع_loc, type, init.مقدار, non_const,
				       alignas_align, scspecs);
  مجموعه_c_عبارت_منبع_range (&عبارت, init.src_range);
  عبارت.m_decimal = 0;
  عبارت.original_کد = ERROR_MARK;
  عبارت.original_type = عدم;
  إذا (type != error_mark_گره
      && عبارت.مقدار != error_mark_گره
      && type_عبارت)
    {
      إذا (درخت_کد (عبارت.مقدار) == C_MAYBE_CONST_عبارت)
	{
	  gcc_assert (C_MAYBE_CONST_عبارت_PRE (عبارت.مقدار) == NULL_درخت);
	  C_MAYBE_CONST_عبارت_PRE (عبارت.مقدار) = type_عبارت;
	}
      وإلا
	{
	  gcc_assert (!non_const);
	  عبارت.مقدار = build2 (C_MAYBE_CONST_عبارت, type,
			       type_عبارت, عبارت.مقدار);
	}
    }
  أرجع c_parser_postfix_عبارت_after_primary (parser, شروع_loc, عبارت);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

ساكن منطقي
sizeof_ptr_memacc_comptypes (درخت type1, درخت type2)
{
  أرجع comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

ساكن فراغ
warn_for_abs (location_t loc, درخت fndecl, درخت arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  إذا (c_inhibit_evaluation_warnings)
    أرجع;

  درخت atype = درخت_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  إذا (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && درخت_کد (atype) != COMPLEX_TYPE)
    أرجع;

  تعداد built_درون_function fcode = DECL_FUNCTION_کد (fndecl);

  بدل (fcode)
    {
    حالة BUILT_درون_ABS:
    حالة BUILT_درون_LABS:
    حالة BUILT_درون_LLABS:
    حالة BUILT_درون_IMAXABS:
      إذا (!INTEGRAL_TYPE_P (atype))
	{
	  إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  وإلا إذا (درخت_کد (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  وإلا
	    gcc_unreachable ();
	  أرجع;
	}
      إذا (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_مقدار,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      اكسر;

    CASE_FLT_FN (BUILT_درون_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_درون_FABS):
      إذا (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_نما_P (TYPE_نما (atype)))
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  وإلا إذا (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  وإلا إذا (درخت_کد (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  وإلا
	    gcc_unreachable ();
	  أرجع;
	}
      اكسر;

    CASE_FLT_FN (BUILT_درون_CABS):
      إذا (درخت_کد (atype) != COMPLEX_TYPE)
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  وإلا إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  وإلا
	    gcc_unreachable ();

	  أرجع;
	}
      اكسر;

    حالة BUILT_درون_FABSD32:
    حالة BUILT_درون_FABSD64:
    حالة BUILT_درون_FABSD128:
    حالة BUILT_درون_FABSD64_X:
      إذا (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  وإلا إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  وإلا إذا (درخت_کد (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_مقدار,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  وإلا
	    gcc_unreachable ();
	  أرجع;
	}
      اكسر;

    افتراضي:
      أرجع;
    }

  إذا (!TYPE_ARG_TYPES (درخت_TYPE (fndecl)))
    أرجع;

  درخت ftype = درخت_مقدار (TYPE_ARG_TYPES (درخت_TYPE (fndecl)));
  إذا (درخت_کد (atype) == COMPLEX_TYPE)
    {
      gcc_assert (درخت_کد (ftype) == COMPLEX_TYPE);
      atype = درخت_TYPE (atype);
      ftype = درخت_TYPE (ftype);
    }

  إذا (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_مقدار,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

ساكن بنية c_عبارت
c_parser_postfix_عبارت_after_primary (c_parser *parser,
					   location_t عبارت_loc,
					   بنية c_عبارت عبارت)
{
  بنية c_عبارت orig_عبارت;
  درخت ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  درخت sizeof_arg[6];
  بیعلامت صحيح literal_zero_ماسک;
  بیعلامت صحيح i;
  vec<درخت, va_gc> *exprlist;
  vec<درخت, va_gc> *origtypes = عدم;
  vec<location_t> arg_loc = vNULL;
  location_t شروع;
  location_t پایان;

  طالما (درست)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_مربع:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_درخت;
	  إذا (!c_omp_array_section_p
	      || c_parser_بعدی_token_is_not (parser, CPP_COLON))
	    idx = c_parser_عبارت (parser).مقدار;

	  إذا (c_omp_array_section_p
	      && c_parser_بعدی_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      إذا (c_parser_بعدی_token_is_not (parser, CPP_CLOSE_مربع))
		len = c_parser_عبارت (parser).مقدار;

	      عبارت.مقدار = build_omp_array_section (op_loc, عبارت.مقدار, idx,
						    len);
	    }
	  وإلا
	    عبارت.مقدار = build_array_ref (op_loc, عبارت.مقدار, idx);

	  c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع,
				     "expected %<]%>");

	  شروع = عبارت.get_شروع ();
	  پایان = parser->نشانهها_buf[0].location;
	  مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	  عبارت.original_کد = ERROR_MARK;
	  عبارت.original_type = عدم;
	  عبارت.m_decimal = 0;
	  اكسر;
	حالة CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    لكل (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_درخت;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_ماسک = 0;
	    إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = عدم;
	    وإلا إذا (درخت_کد (عبارت.مقدار) == FUNCTION_DECL
		     && fndecl_built_درون_p (عبارت.مقدار, BUILT_درون_CLASSIFY_TYPE)
		     && c_parser_بعدی_نشانهها_شروع_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		درون_alignof++;
		بنية c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		درون_alignof--;
		بنية c_typespec ret;
		ret.عبارت = NULL_درخت;
		ret.spec = error_mark_گره;
		ret.عبارت_const_operands = خطأ;
		إذا (type != عدم)
		  ret.spec = groktypename (type, &ret.عبارت,
					   &ret.عبارت_const_operands);
		parens.skip_until_یافت_close (parser);
		عبارت.مقدار = build_int_cst (integer_type_گره,
					    type_مقصد_class (ret.spec));
		اكسر;
	      }
	    وإلا
	      exprlist = c_parser_عبارت_list (parser, درست, خطأ, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_ماسک);
	    parens.skip_until_یافت_close (parser);
	  }
	  orig_عبارت = عبارت;
	  mark_exp_read (عبارت.مقدار);
	  إذا (warn_sizeof_اشاره_گر_memaccess)
	    sizeof_اشاره_گر_memaccess_warning (sizeof_arg_loc,
					      عبارت.مقدار, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  إذا (درخت_کد (عبارت.مقدار) == FUNCTION_DECL)
	    {
	      إذا (fndecl_built_درون_p (عبارت.مقدار, BUILT_درون_MEMSET)
		  && vec_امن_درازی (exprlist) == 3)
		{
		  درخت arg0 = (*exprlist)[0];
		  درخت arg2 = (*exprlist)[2];
		  warn_for_memset (عبارت_loc, arg0, arg2, literal_zero_ماسک);
		}
	      إذا (warn_absolute_مقدار
		  && fndecl_built_درون_p (عبارت.مقدار, BUILT_درون_نرمال)
		  && vec_امن_درازی (exprlist) == 1)
		warn_for_abs (عبارت_loc, عبارت.مقدار, (*exprlist)[0]);
	      إذا (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->درون_intervening_کد
		  && omp_runtime_api_call (عبارت.مقدار))
		{
		  error_at (عبارت_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = درست;
		}
	      إذا (warn_calloc_transposed_آرگومانها)
		إذا (درخت attr = lookup_attribute ("alloc_size",
						  TYPE_صفات
						    (درخت_TYPE (عبارت.مقدار))))
		  إذا (درخت_مقدار (attr) && درخت_CHAIN (درخت_مقدار (attr)))
		    warn_for_calloc (sizeof_arg_loc, عبارت.مقدار, exprlist,
				     sizeof_arg, attr);
	    }

	  شروع = عبارت.get_شروع ();
	  پایان = parser->نشانهها_buf[0].get_پایان ();
	  عبارت.مقدار
	    = c_build_function_call_vec (عبارت_loc, arg_loc, عبارت.مقدار,
					 exprlist, origtypes);
	  مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	  عبارت.m_decimal = 0;

	  عبارت.original_کد = ERROR_MARK;
	  إذا (درخت_کد (عبارت.مقدار) == INTEGER_CST
	      && درخت_کد (orig_عبارت.مقدار) == FUNCTION_DECL
	      && fndecl_built_درون_p (orig_عبارت.مقدار, BUILT_درون_CONSTANT_P))
	    عبارت.original_کد = C_MAYBE_CONST_عبارت;
	  عبارت.original_type = عدم;
	  إذا (exprlist)
	    {
	      release_درخت_وکتور (exprlist);
	      release_درخت_وکتور (origtypes);
	    }
	  arg_loc.release ();
	  اكسر;
	حالة CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  عبارت = default_function_array_conversion (عبارت_loc, عبارت);
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->مقدار;
	      comp_loc = comp_tok->location;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      عبارت.مجموعه_error ();
	      عبارت.original_کد = ERROR_MARK;
              عبارت.original_type = عدم;
	      أرجع عبارت;
	    }
	  شروع = عبارت.get_شروع ();
	  پایان = c_parser_peek_token (parser)->get_پایان ();
	  c_parser_consume_token (parser);
	  عبارت.مقدار = build_component_ref (op_loc, عبارت.مقدار, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	  عبارت.original_کد = ERROR_MARK;
	  إذا (درخت_کد (عبارت.مقدار) != COMPONENT_REF)
	    عبارت.original_type = عدم;
	  وإلا
	    {
	      /* Remember the original type of a bitfield.  */
	      درخت فیلد_2 = درخت_عملوند (عبارت.مقدار, 1);
	      إذا (درخت_کد (فیلد_2) != فیلد_DECL)
		عبارت.original_type = عدم;
	      وإلا
		عبارت.original_type = DECL_بیت_فیلد_TYPE (فیلد_2);
	    }
	  عبارت.m_decimal = 0;
	  اكسر;
	حالة CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, درست, خطأ);
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->مقدار;
	      comp_loc = comp_tok->location;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      عبارت.مجموعه_error ();
	      عبارت.original_کد = ERROR_MARK;
	      عبارت.original_type = عدم;
	      أرجع عبارت;
	    }
	  شروع = عبارت.get_شروع ();
	  پایان = c_parser_peek_token (parser)->get_پایان ();
	  c_parser_consume_token (parser);
	  عبارت.مقدار = build_component_ref (op_loc,
					    build_غیرمستقیم_ref (op_loc,
								عبارت.مقدار,
								RO_ARROW),
					    ident, comp_loc,
					    عبارت.get_location ());
	  مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	  عبارت.original_کد = ERROR_MARK;
	  إذا (درخت_کد (عبارت.مقدار) != COMPONENT_REF)
	    عبارت.original_type = عدم;
	  وإلا
	    {
	      /* Remember the original type of a bitfield.  */
	      درخت فیلد_2 = درخت_عملوند (عبارت.مقدار, 1);
	      إذا (درخت_کد (فیلد_2) != فیلد_DECL)
		عبارت.original_type = عدم;
	      وإلا
		عبارت.original_type = DECL_بیت_فیلد_TYPE (فیلد_2);
	    }
	  عبارت.m_decimal = 0;
	  اكسر;
	حالة CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  شروع = عبارت.get_شروع ();
	  پایان = c_parser_peek_token (parser)->get_پایان ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (عبارت.مقدار);
	  عبارت = default_function_array_conversion (عبارت_loc, عبارت);
	  عبارت.مقدار = build_unary_op (op_loc, POSTINCREMENT_عبارت,
				       عبارت.مقدار, خطأ);
	  مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	  عبارت.original_کد = ERROR_MARK;
	  عبارت.original_type = عدم;
	  اكسر;
	حالة CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  شروع = عبارت.get_شروع ();
	  پایان = c_parser_peek_token (parser)->get_پایان ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (عبارت.مقدار);
	  عبارت = default_function_array_conversion (عبارت_loc, عبارت);
	  عبارت.مقدار = build_unary_op (op_loc, POSTDECREMENT_عبارت,
				       عبارت.مقدار, خطأ);
	  مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	  عبارت.original_کد = ERROR_MARK;
	  عبارت.original_type = عدم;
	  اكسر;
	افتراضي:
	  أرجع عبارت;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

ساكن بنية c_عبارت
c_parser_عبارت (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  بنية c_عبارت عبارت;
  عبارت = c_parser_عبارت_no_commas (parser, عدم);
  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
    عبارت = convert_lvalue_مقصد_rvalue (tloc, عبارت, درست, خطأ);
  طالما (c_parser_بعدی_token_is (parser, CPP_COMMA))
    {
      بنية c_عبارت بعدی;
      درخت lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t عبارت_loc;
      c_parser_consume_token (parser);
      عبارت_loc = c_parser_peek_token (parser)->location;
      lhsval = عبارت.مقدار;
      طالما (درخت_کد (lhsval) == COMPOUND_عبارت
	     || درخت_کد (lhsval) == NOP_عبارت)
	{
	  إذا (درخت_کد (lhsval) == COMPOUND_عبارت)
	    lhsval = درخت_عملوند (lhsval, 1);
	  وإلا
	    lhsval = درخت_عملوند (lhsval, 0);
	}
      إذا (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      إذا (c_parser_بعدی_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  درخت val = embed->مقدار;
	  بیعلامت آخرین = RAW_داده_درازی (val) - 1;
	  بعدی.مقدار = build_int_cst (درخت_TYPE (val),
				      RAW_داده_UCHAR_ELT (val, آخرین));
	  بعدی.original_type = integer_type_گره;
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  بعدی = c_parser_عبارت_no_commas (parser, عدم);
	  بعدی = convert_lvalue_مقصد_rvalue (عبارت_loc, بعدی, درست, خطأ);
	}
      عبارت.مقدار = build_compound_عبارت (loc, عبارت.مقدار, بعدی.مقدار);
      عبارت.original_کد = COMPOUND_عبارت;
      عبارت.original_type = بعدی.original_type;
      عبارت.m_decimal = 0;
    }
  أرجع عبارت;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

ساكن بنية c_عبارت
c_parser_عبارت_conv (c_parser *parser)
{
  بنية c_عبارت عبارت;
  location_t loc = c_parser_peek_token (parser)->location;
  عبارت = c_parser_عبارت (parser);
  عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, درست, خطأ);
  أرجع عبارت;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

ساكن مضمن فراغ
c_parser_check_literal_zero (c_parser *parser, بیعلامت *literal_zero_ماسک,
			     بیعلامت صحيح idx)
{
  إذا (idx >= HOST_بیتها_در_هر_INT)
    أرجع;

  c_token *tok = c_parser_peek_token (parser);
  بدل (tok->type)
    {
    حالة CPP_عدد:
    حالة CPP_CHAR:
    حالة CPP_WCHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      إذا (integer_zerop (tok->مقدار)
	  && !درخت_سرریز (tok->مقدار)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_ماسک |= 1U << idx;
    افتراضي:
      اكسر;
    }
}

/* Parse a non-empty list of expressions.  If CONVERT_P, convert
   functions and arrays to pointers and lvalues to rvalues.  If
   FOLD_P, fold the expressions.  If LOCATIONS is non-NULL, save the
   locations of function arguments into this vector.

   nonempty-expr-list:
     assignment-expression
     nonempty-expr-list , assignment-expression
*/

ساكن vec<درخت, va_gc> *
c_parser_عبارت_list (c_parser *parser, منطقي convert_p, منطقي fold_p,
		    vec<درخت, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, درخت *sizeof_arg,
		    vec<location_t> *locations,
		    بیعلامت صحيح *literal_zero_ماسک)
{
  vec<درخت, va_gc> *ret;
  vec<درخت, va_gc> *orig_types;
  بنية c_عبارت عبارت;
  بیعلامت صحيح idx = 0;
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = خطأ;

  ret = make_درخت_وکتور ();
  إذا (p_orig_types == عدم)
    orig_types = عدم;
  وإلا
    orig_types = make_درخت_وکتور ();

  إذا (literal_zero_ماسک)
    c_parser_check_literal_zero (parser, literal_zero_ماسک, 0);
  عبارت = c_parser_عبارت_no_commas (parser, عدم);
  إذا (convert_p)
    عبارت = convert_lvalue_مقصد_rvalue (عبارت.get_location (), عبارت, درست, درست);
  إذا (fold_p)
    عبارت.مقدار = c_fully_fold (عبارت.مقدار, خطأ, عدم);
  ret->سریع_افزودن (عبارت.مقدار);
  إذا (orig_types)
    orig_types->سریع_افزودن (عبارت.original_type);
  إذا (locations)
    locations->امن_افزودن (عبارت.get_location ());
  إذا (sizeof_arg != عدم
      && (عبارت.original_کد == SIZEOF_عبارت
	  || عبارت.original_کد == PAREN_SIZEOF_عبارت))
    {
      sizeof_arg[0] = c_آخرین_sizeof_arg;
      sizeof_arg_loc[0] = c_آخرین_sizeof_loc;
    }
  طالما (c_parser_بعدی_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  درخت مقدار = embed->مقدار;
	  عبارت.original_کد = INTEGER_CST;
	  عبارت.original_type = integer_type_گره;
	  عبارت.مقدار = NULL_درخت;
	  مجموعه_c_عبارت_منبع_range (&عبارت, embed->get_range ());
	  عبارت.m_decimal = 0;
	  لكل (بیعلامت صحيح i = 0; i < (بیعلامت) RAW_داده_درازی (مقدار); i++)
	    {
	      إذا (literal_zero_ماسک
		  && idx + 1 < HOST_بیتها_در_هر_INT
		  && RAW_داده_اشاره_گر (مقدار)[i] == 0)
		*literal_zero_ماسک |= 1U << (idx + 1);
	      عبارت.مقدار = build_int_cst (integer_type_گره,
					  RAW_داده_UCHAR_ELT (مقدار, i));
	      vec_امن_افزودن (ret, عبارت.مقدار);
	      إذا (orig_types)
		vec_امن_افزودن (orig_types, عبارت.original_type);
	      إذا (locations)
		locations->امن_افزودن (عبارت.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  استمر;
	}
      إذا (literal_zero_ماسک)
	c_parser_check_literal_zero (parser, literal_zero_ماسک, idx + 1);
      عبارت = c_parser_عبارت_no_commas (parser, عدم);
      إذا (convert_p)
	عبارت = convert_lvalue_مقصد_rvalue (عبارت.get_location (), عبارت, درست,
					 درست);
      إذا (fold_p)
	عبارت.مقدار = c_fully_fold (عبارت.مقدار, خطأ, عدم);
      vec_امن_افزودن (ret, عبارت.مقدار);
      إذا (orig_types)
	vec_امن_افزودن (orig_types, عبارت.original_type);
      إذا (locations)
	locations->امن_افزودن (عبارت.get_location ());
      إذا (++idx < 6
	  && sizeof_arg != عدم
	  && (عبارت.original_کد == SIZEOF_عبارت
	      || عبارت.original_کد == PAREN_SIZEOF_عبارت))
	{
	  sizeof_arg[idx] = c_آخرین_sizeof_arg;
	  sizeof_arg_loc[idx] = c_آخرین_sizeof_loc;
	}
    }
  إذا (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  أرجع ret;
}

/* Parse Objective-C-specific constructs.  */

/* Parse an objc-class-definition.

   objc-class-definition:
     @interface identifier objc-superclass[opt] objc-protocol-refs[opt]
       objc-class-instance-variables[opt] objc-methodprotolist @end
     @implementation identifier objc-superclass[opt]
       objc-class-instance-variables[opt]
     @interface identifier ( identifier ) objc-protocol-refs[opt]
       objc-methodprotolist @end
     @interface identifier ( ) objc-protocol-refs[opt]
       objc-methodprotolist @end
     @implementation identifier ( identifier )

   objc-superclass:
     : identifier

   "@interface identifier (" must start "@interface identifier (
   identifier ) ...": objc-methodprotolist in the first production may
   not start with a parenthesized identifier as a declarator of a data
   definition with no declaration specifiers if the objc-superclass,
   objc-protocol-refs and objc-class-instance-variables are omitted.  */

ساكن فراغ
c_parser_objc_class_definition (c_parser *parser, درخت صفات)
{
  منطقي iface_p;
  درخت id1;
  درخت superclass;
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = درست;
  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = خطأ;
  وإلا
    gcc_unreachable ();

  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      أرجع;
    }
  id1 = c_parser_peek_token (parser)->مقدار;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      درخت id2;
      درخت proto = NULL_درخت;
      matching_parens parens;
      parens.consume_open (parser);
      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	{
	  إذا (iface_p && c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_درخت;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع;
	    }
	}
      وإلا
	{
	  id2 = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_یافت_close (parser);
      إذا (!iface_p)
	{
	  objc_شروع_category_implementation (id1, id2);
	  أرجع;
	}
      إذا (c_parser_بعدی_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_شروع_category_interface (id1, id2, proto, صفات);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_انتها, "expected %<@end%>");
      objc_پایان_interface ();
      أرجع;
    }
  إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع;
	}
      superclass = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
    }
  وإلا
    superclass = NULL_درخت;
  إذا (iface_p)
    {
      درخت proto = NULL_درخت;
      إذا (c_parser_بعدی_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_شروع_class_interface (id1, loc1, superclass, proto, صفات);
    }
  وإلا
    objc_شروع_class_implementation (id1, superclass);
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  إذا (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_انتها, "expected %<@end%>");
      objc_پایان_interface ();
    }
  وإلا
    {
      objc_continue_implementation ();
      أرجع;
    }
}

/* Parse objc-class-instance-variables.

   objc-class-instance-variables:
     { objc-instance-variable-decl-list[opt] }

   objc-instance-variable-decl-list:
     objc-visibility-spec
     objc-instance-variable-decl ;
     ;
     objc-instance-variable-decl-list objc-visibility-spec
     objc-instance-variable-decl-list objc-instance-variable-decl ;
     objc-instance-variable-decl-list ;

   objc-visibility-spec:
     @private
     @protected
     @public

   objc-instance-variable-decl:
     struct-declaration
*/

ساكن فراغ
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  طالما (c_parser_بعدی_token_is_not (parser, CPP_EOF))
    {
      درخت decls;
      /* Parse any stray semicolon.  */
      إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  استمر;
	}
      /* Stop if at the end of the instance variables.  */
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  اكسر;
	}
      /* Parse any objc-visibility-spec.  */
      إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_خصوصی))
	{
	  c_parser_consume_token (parser);
	  objc_مجموعه_visibility (OBJC_IVAR_VIS_خصوصی);
	  استمر;
	}
      وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_مجموعه_visibility (OBJC_IVAR_VIS_PROTECTED);
	  استمر;
	}
      وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_عمومی))
	{
	  c_parser_consume_token (parser);
	  objc_مجموعه_visibility (OBJC_IVAR_VIS_عمومی);
	  استمر;
	}
      وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_مجموعه_visibility (OBJC_IVAR_VIS_PACKAGE);
	  استمر;
	}
      وإلا إذا (c_parser_بعدی_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, عدم, NULL_درخت);
	  استمر;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, عدم);
      إذا (decls == عدم)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_مربع)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = خطأ;
	  استمر;
	}
      وإلا
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  درخت ivar = nreverse (decls);
	  لكل (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_جمع_کن_instance_variable (copy_گره (ivar));
	}
      c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

ساكن فراغ
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  طالما (درست)
    {
      درخت id;
      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);
	  parser->error = خطأ;
	  أرجع;
	}
      id = c_parser_peek_token (parser)->مقدار;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

ساكن فراغ
c_parser_objc_alias_declaration (c_parser *parser)
{
  درخت id1, id2;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);
      أرجع;
    }
  id1 = c_parser_peek_token (parser)->مقدار;
  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);
      أرجع;
    }
  id2 = c_parser_peek_token (parser)->مقدار;
  c_parser_consume_token (parser);
  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_declare_alias (id1, id2);
}

/* Parse an objc-protocol-definition.

   objc-protocol-definition:
     @protocol identifier objc-protocol-refs[opt] objc-methodprotolist @end
     @protocol identifier-list ;

   "@protocol identifier ;" should be resolved as "@protocol
   identifier-list ;": objc-methodprotolist may not start with a
   semicolon in the first alternative if objc-protocol-refs are
   omitted.  */

ساكن فراغ
c_parser_objc_protocol_definition (c_parser *parser, درخت صفات)
{
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      أرجع;
    }
  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      طالما (درست)
	{
	  درخت id;
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      اكسر;
	    }
	  id = c_parser_peek_token (parser)->مقدار;
	  objc_declare_protocol (id, صفات);
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  وإلا
    {
      درخت id = c_parser_peek_token (parser)->مقدار;
      درخت proto = NULL_درخت;
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = درست;
      objc_شروع_protocol (id, proto, صفات);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_انتها, "expected %<@end%>");
      parser->objc_pq_context = خطأ;
      objc_پایان_interface ();
    }
}

/* Parse an objc-method-type.

   objc-method-type:
     +
     -

   Return true if it is a class method (+) and false if it is
   an instance method (-).
*/
ساكن مضمن منطقي
c_parser_objc_روش_type (c_parser *parser)
{
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      أرجع درست;
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      أرجع خطأ;
    افتراضي:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

ساكن فراغ
c_parser_objc_روش_definition (c_parser *parser)
{
  منطقي is_class_روش = c_parser_objc_روش_type (parser);
  درخت decl, صفات = NULL_درخت, عبارت = NULL_درخت;
  parser->objc_pq_context = درست;
  decl = c_parser_objc_روش_decl (parser, is_class_روش, &صفات,
				    &عبارت);
  إذا (decl == error_mark_گره)
    أرجع;  /* Bail here. */

  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  إذا (!c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      أرجع;
    }

  parser->objc_pq_context = خطأ;
  إذا (objc_شروع_روش_definition (is_class_روش, decl, صفات, عبارت))
    {
      جمع_کن_stmt (c_parser_compound_statement (parser));
      objc_پایان_روش_definition (current_function_decl);
    }
  وإلا
    {
      /* This code is executed when we find a method definition
	 outside of an @implementation context (or invalid for other
	 reasons).  Parse the method (to keep going) but do not emit
	 any code.
      */
      c_parser_compound_statement (parser);
    }
}

/* Parse an objc-methodprotolist.

   objc-methodprotolist:
خالی
     objc-methodprotolist objc-methodproto
     objc-methodprotolist declaration
     objc-methodprotolist ;
     @optional
     @required

   The declaration is a data definition, which may be missing
   declaration specifiers under the same rules and diagnostics as
   other data definitions outside functions, and the stray semicolon
   is diagnosed the same way as a stray semicolon outside a
   function.  */

ساكن فراغ
c_parser_objc_methodprotolist (c_parser *parser)
{
  طالما (درست)
    {
      /* The list is terminated by @end.  */
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  اكسر;
	حالة CPP_PLUS:
	حالة CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  اكسر;
	حالة CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, عدم, NULL_درخت);
	  اكسر;
	حالة CPP_EOF:
	  أرجع;
	افتراضي:
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_انتها))
	    أرجع;
	  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_مجموعه_روش_opt (درست);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_مجموعه_روش_opt (خطأ);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    c_parser_declaration_or_fndef (parser, خطأ, خطأ, درست,
					   خطأ, درست, خطأ);
	  اكسر;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

ساكن فراغ
c_parser_objc_methodproto (c_parser *parser)
{
  منطقي is_class_روش = c_parser_objc_روش_type (parser);
  درخت decl, صفات = NULL_درخت;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = درست;
  decl = c_parser_objc_روش_decl (parser, is_class_روش, &صفات,
				    عدم);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = خطأ;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  إذا (!c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      أرجع;
    }

  إذا (decl != error_mark_گره)
    objc_جمع_کن_روش_declaration (is_class_روش, decl, صفات);

  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

ساكن منطقي
c_parser_objc_maybe_روش_صفات (c_parser* parser, درخت* صفات)
{
  منطقي bad = خطأ;
  إذا (*صفات)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *صفات = NULL_درخت;
      bad = درست;
    }

  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
    *صفات = c_parser_gnu_صفات (parser);

  /* If there were no attributes here, just report any earlier error.  */
  إذا (*صفات == NULL_درخت || bad)
    أرجع bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON)
      || c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    أرجع bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  أرجع درست;
}

/* Parse an objc-method-decl.

   objc-method-decl:
     ( objc-type-name ) objc-selector
     objc-selector
     ( objc-type-name ) objc-keyword-selector objc-optparmlist
     objc-keyword-selector objc-optparmlist
     gnu-attributes

   objc-keyword-selector:
     objc-keyword-decl
     objc-keyword-selector objc-keyword-decl

   objc-keyword-decl:
     objc-selector : ( objc-type-name ) identifier
     objc-selector : identifier
     : ( objc-type-name ) identifier
     : identifier

   objc-optparmlist:
     objc-optparms objc-optellipsis

   objc-optparms:
خالی
     objc-opt-parms , parameter-declaration

   objc-optellipsis:
خالی
     , ...
*/

ساكن درخت
c_parser_objc_روش_decl (c_parser *parser, منطقي is_class_روش,
			   درخت *صفات, درخت *عبارت)
{
  درخت type = NULL_درخت;
  درخت sel;
  درخت parms = NULL_درخت;
  منطقي ellipsis = خطأ;
  منطقي attr_err = خطأ;

  *صفات = NULL_درخت;
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      type = c_parser_objc_type_name (parser);
      parens.skip_until_یافت_close (parser);
    }
  sel = c_parser_objc_selector (parser);
  /* If there is no selector, or a colon follows, we have an
     objc-keyword-selector.  If there is a selector, and a colon does
     not follow, that selector ends the objc-method-decl.  */
  إذا (!sel || c_parser_بعدی_token_is (parser, CPP_COLON))
    {
      درخت tsel = sel;
      درخت list = NULL_درخت;
      طالما (درست)
	{
	  درخت atype = NULL_درخت, id, keyworddecl;
	  درخت param_attr = NULL_درخت;
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    اكسر;
	  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_صفات (parser);
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      أرجع error_mark_گره;
	    }
	  id = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  إذا (!tsel && c_parser_بعدی_token_is_not (parser, CPP_COLON))
	    اكسر;
	}

      attr_err |= c_parser_objc_maybe_روش_صفات (parser, صفات) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_گره (درخت_LIST);
      طالما (c_parser_بعدی_token_is (parser, CPP_COMMA))
	{
	  بنية c_parm *parm;
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = درست;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_روش_صفات
						(parser, صفات) ;
	      اكسر;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_درخت, خطأ);
	  إذا (parm == عدم)
	    اكسر;
	  parms = chainon (parms,
			   build_درخت_list (NULL_درخت, grokparm (parm, عبارت)));
	}
      sel = list;
    }
  وإلا
    attr_err |= c_parser_objc_maybe_روش_صفات (parser, صفات) ;

  إذا (sel == عدم)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      أرجع error_mark_گره;
    }

  إذا (attr_err)
    أرجع error_mark_گره;

  أرجع objc_build_روش_signature (is_class_روش, type, sel, parms, ellipsis);
}

/* Parse an objc-type-name.

   objc-type-name:
     objc-type-qualifiers[opt] type-name
     objc-type-qualifiers[opt]

   objc-type-qualifiers:
     objc-type-qualifier
     objc-type-qualifiers objc-type-qualifier

   objc-type-qualifier: one of
     in out inout bycopy byref oneway
*/

ساكن درخت
c_parser_objc_type_name (c_parser *parser)
{
  درخت quals = NULL_درخت;
  بنية c_type_name *type_name = عدم;
  درخت type = NULL_درخت;
  طالما (درست)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_KEYWORD
	  && (token->keyword == RID_درون
	      || token->keyword == RID_بیرون
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_درخت_list (NULL_درخت, token->مقدار), quals);
	  c_parser_consume_token (parser);
	}
      وإلا
	اكسر;
    }
  إذا (c_parser_بعدی_نشانهها_شروع_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  إذا (type_name)
    type = groktypename (type_name, عدم, عدم);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  إذا (type == error_mark_گره)
    type = NULL_درخت;

  أرجع build_درخت_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

ساكن درخت
c_parser_objc_protocol_refs (c_parser *parser)
{
  درخت list = NULL_درخت;
  gcc_assert (c_parser_بعدی_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  طالما (درست)
    {
      درخت id;
      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}
      id = c_parser_peek_token (parser)->مقدار;
      list = chainon (list, build_درخت_list (NULL_درخت, id));
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  أرجع list;
}

/* Parse an objc-try-catch-finally-statement.

   objc-try-catch-finally-statement:
     @try compound-statement objc-catch-list[opt]
     @try compound-statement objc-catch-list[opt] @finally compound-statement

   objc-catch-list:
     @catch ( objc-catch-parameter-declaration ) compound-statement
     objc-catch-list @catch ( objc-catch-parameter-declaration ) compound-statement

   objc-catch-parameter-declaration:
     parameter-declaration
     '...'

   where '...' is to be interpreted literally, that is, it means CPP_ELLIPSIS.

   PS: This function is identical to cp_parser_objc_try_catch_finally_statement
   for C++.  Keep them in sync.  */

ساكن فراغ
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  درخت stmt;

  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  طالما (c_parser_بعدی_token_is_keyword (parser, RID_AT_CATCH))
    {
      بنية c_parm *parm;
      درخت parameter_declaration = error_mark_گره;
      منطقي دیده_open_paren = خطأ;

      c_parser_consume_token (parser);
      matching_parens parens;
      إذا (!parens.require_open (parser))
	دیده_open_paren = درست;
      إذا (c_parser_بعدی_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_درخت;
	}
      وإلا
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_درخت, خطأ);
	  إذا (parm == عدم)
	    parameter_declaration = error_mark_گره;
	  وإلا
	    parameter_declaration = grokparm (parm, عدم);
	}
      إذا (دیده_open_paren)
	parens.require_close (parser);
      وإلا
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      إذا (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_پایان_catch_clause ();
    }
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_AT_FINALLY))
    {
      c_parser_consume_token (parser);
      location = c_parser_peek_token (parser)->location;
      stmt = c_parser_compound_statement (parser);
      objc_build_finally_clause (location, stmt);
    }
  objc_پایان_try_stmt ();
}

/* Parse an objc-synchronized-statement.

   objc-synchronized-statement:
     @synchronized ( expression ) compound-statement
*/

ساكن فراغ
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  درخت عبارت, stmt;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      بنية c_عبارت ce = c_parser_عبارت (parser);
      ce = convert_lvalue_مقصد_rvalue (loc, ce, خطأ, خطأ);
      عبارت = ce.مقدار;
      عبارت = c_fully_fold (عبارت, خطأ, عدم);
      parens.skip_until_یافت_close (parser);
    }
  وإلا
    عبارت = error_mark_گره;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, عبارت, stmt);
}

/* Parse an objc-selector; return NULL_TREE without an error if the
   next token is not an objc-selector.

   objc-selector:
     identifier
     one of
       enum struct union if else while do for switch case default
       break continue return goto asm sizeof typeof typeof_unqual __alignof
       unsigned long const short volatile signed restrict _Complex
       in out inout bycopy byref oneway int char float double void _Bool
       _Atomic

   ??? Why this selection of keywords but not, for example, storage
   class specifiers?  */

ساكن درخت
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  درخت مقدار = token->مقدار;
  إذا (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      أرجع مقدار;
    }
  إذا (token->type != CPP_KEYWORD)
    أرجع NULL_درخت;
  بدل (token->keyword)
    {
    حالة RID_ENUM:
    حالة RID_STRUCT:
    حالة RID_UNION:
    حالة RID_IF:
    حالة RID_ELSE:
    حالة RID_WHILE:
    حالة RID_DO:
    حالة RID_FOR:
    حالة RID_SWITCH:
    حالة RID_CASE:
    حالة RID_DEFAULT:
    حالة RID_BREAK:
    حالة RID_CONTINUE:
    حالة RID_RETURN:
    حالة RID_GOTO:
    حالة RID_ASM:
    حالة RID_SIZEOF:
    حالة RID_TYPEOF:
    حالة RID_TYPEOF_UNQUAL:
    حالة RID_ALIGNOF:
    حالة RID_UNSIGNED:
    حالة RID_LONG:
    حالة RID_CONST:
    حالة RID_SHORT:
    حالة RID_VOLATILE:
    حالة RID_SIGNED:
    حالة RID_RESTRICT:
    حالة RID_COMPLEX:
    حالة RID_درون:
    حالة RID_بیرون:
    حالة RID_INOUT:
    حالة RID_BYCOPY:
    حالة RID_BYREF:
    حالة RID_ONEWAY:
    حالة RID_INT:
    حالة RID_CHAR:
    حالة RID_FLOAT:
    حالة RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    حالة RID_VOID:
    حالة RID_BOOL:
    حالة RID_ATOMIC:
    حالة RID_AUTO_TYPE:
    حالة RID_INT_N_0:
    حالة RID_INT_N_1:
    حالة RID_INT_N_2:
    حالة RID_INT_N_3:
      c_parser_consume_token (parser);
      أرجع مقدار;
    افتراضي:
      أرجع NULL_درخت;
    }
}

/* Parse an objc-selector-arg.

   objc-selector-arg:
     objc-selector
     objc-keywordname-list

   objc-keywordname-list:
     objc-keywordname
     objc-keywordname-list objc-keywordname

   objc-keywordname:
     objc-selector :
     :
*/

ساكن درخت
c_parser_objc_selector_arg (c_parser *parser)
{
  درخت sel = c_parser_objc_selector (parser);
  درخت list = NULL_درخت;
  إذا (sel
      && c_parser_بعدی_token_is_not (parser, CPP_COLON)
      && c_parser_بعدی_token_is_not (parser, CPP_SCOPE))
    أرجع sel;
  طالما (درست)
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_درخت_list (sel, NULL_درخت));
	  list = chainon (list, build_درخت_list (NULL_درخت, NULL_درخت));
	}
      وإلا
	{
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    أرجع list;
	  list = chainon (list, build_درخت_list (sel, NULL_درخت));
	}
      sel = c_parser_objc_selector (parser);
      إذا (!sel
	  && c_parser_بعدی_token_is_not (parser, CPP_COLON)
	  && c_parser_بعدی_token_is_not (parser, CPP_SCOPE))
	اكسر;
    }
  أرجع list;
}

/* Parse an objc-receiver.

   objc-receiver:
عبارت
     class-name
     type-name
*/

ساكن درخت
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_نوع == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_نوع == C_ID_CLASSNAME))
    {
      درخت id = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      أرجع objc_get_class_reference (id);
    }
  بنية c_عبارت ce = c_parser_عبارت (parser);
  ce = convert_lvalue_مقصد_rvalue (loc, ce, خطأ, خطأ);
  أرجع c_fully_fold (ce.مقدار, خطأ, عدم);
}

/* Parse objc-message-args.

   objc-message-args:
     objc-selector
     objc-keywordarg-list

   objc-keywordarg-list:
     objc-keywordarg
     objc-keywordarg-list objc-keywordarg

   objc-keywordarg:
     objc-selector : objc-keywordexpr
     : objc-keywordexpr
*/

ساكن درخت
c_parser_objc_پیام_آرگومانها (c_parser *parser)
{
  درخت sel = c_parser_objc_selector (parser);
  درخت list = NULL_درخت;
  إذا (sel && c_parser_بعدی_token_is_not (parser, CPP_COLON))
    أرجع sel;
  طالما (درست)
    {
      درخت keywordexpr;
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	أرجع error_mark_گره;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_درخت_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      إذا (!sel && c_parser_بعدی_token_is_not (parser, CPP_COLON))
	اكسر;
    }
  أرجع list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

ساكن درخت
c_parser_objc_keywordexpr (c_parser *parser)
{
  درخت ret;
  vec<درخت, va_gc> *عبارت_list = c_parser_عبارت_list (parser, درست, درست,
						عدم, عدم, عدم, عدم);
  إذا (vec_امن_درازی (عبارت_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*عبارت_list)[0];
    }
  وإلا
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_درخت_list_vec (عبارت_list);
    }
  release_درخت_وکتور (عبارت_list);
  أرجع ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
ساكن منطقي
c_parser_objc_diagnose_bad_element_پیشوند (c_parser *parser,
					   بنية c_declspecs *specs)
{
  إذا (!specs->declspecs_دیده_p || specs->non_sc_دیده_p
      || specs->typespec_نوع != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
      أرجع درست;
    }
  أرجع خطأ;
}

/* Parse an Objective-C @property declaration.  The syntax is:

   objc-property-declaration:
     '@property' objc-property-attributes[opt] struct-declaration ;

   objc-property-attributes:
    '(' objc-property-attribute-list ')'

   objc-property-attribute-list:
     objc-property-attribute
     objc-property-attribute-list, objc-property-attribute

   objc-property-attribute
     'getter' = identifier
     'setter' = identifier
     'readonly'
     'readwrite'
     'assign'
     'retain'
     'copy'
     'nonatomic'

  For example:
    @property NSString *name;
    @property (readonly) id object;
    @property (retain, nonatomic, getter=getTheName) id name;
    @property int a, b, c;

  PS: This function is identical to cp_parser_objc_at_propery_declaration
  for C++.  Keep them in sync.  */
ساكن فراغ
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  منطقي syntax_error = خطأ;
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_شروع = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = درست;

      /* Allow @property (), with a warning.  */
      location_t attr_انتها = c_parser_peek_token (parser)->location;

      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_انتها, attr_شروع, attr_انتها);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      وإلا
	طالما (درست)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_شروع = token->location;
	    attr_انتها = get_پایان (token->location);
	    location_t attr_comb = make_location (attr_شروع, attr_شروع,
						  attr_انتها);

	    إذا (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		إذا (token->type == CPP_CLOSE_PAREN)
		  اكسر;
		c_parser_consume_token (parser);
		استمر;
	      }

	    درخت attr_name = NULL_درخت;
	    تعداد rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    منطقي جمع_کن_at = خطأ;
	    إذا (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		إذا (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->مقدار;
		    جمع_کن_at = درست;
		  }
		وإلا
		  attr_name = ridpointers[(صحيح)keyword];
	      }
	    وإلا إذا (token->type == CPP_NAME)
	      attr_name = token->مقدار;
	    c_parser_consume_token (parser);

	    تعداد objc_property_attribute_نوع prop_نوع
	      = objc_prop_attr_نوع_for_rid (keyword);
	    property_attribute_info *prop
	      = جديد property_attribute_info (attr_name, attr_comb, prop_نوع);
	    prop_attr_list.امن_افزودن (prop);

	    درخت meth_name;
	    بدل (prop->prop_نوع)
	      {
	      افتراضي: اكسر;
	      حالة OBJC_PROPERTY_ATTR_UNKNOWN:
		إذا (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    جمع_کن_at ? "@" : "", IDENTIFIER_اشاره_گر (attr_name));
		وإلا
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = درست;
		اكسر;

	      حالة OBJC_PROPERTY_ATTR_GETTER:
	      حالة OBJC_PROPERTY_ATTR_SETTER:
		إذا (c_parser_بعدی_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_انتها, attr_شروع, attr_انتها);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = درست;
		    اكسر;
		  }
		token = c_parser_peek_token (parser);
		attr_انتها = token->location;
		c_parser_consume_token (parser); /* eat the = */
		إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_انتها, attr_شروع, attr_انتها);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = درست;
		    اكسر;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_انتها = get_پایان (token->location);
		meth_name = token->مقدار;
		c_parser_consume_token (parser);
		إذا (prop->prop_نوع == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    إذا (c_parser_بعدی_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_انتها, attr_شروع,
						   attr_انتها);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = درست;
		      }
		    وإلا
		      {
			attr_انتها = get_پایان (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_شروع, attr_شروع,
					       attr_انتها);
		  }
		وإلا
		  attr_comb = make_location (attr_شروع, attr_شروع,
					       attr_انتها);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		اكسر;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      parser->objc_property_attr_context = خطأ;

      إذا (syntax_error && c_parser_بعدی_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      وإلا
	syntax_error = خطأ, parens.skip_until_یافت_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  درخت properties = c_parser_struct_declaration (parser, عدم);

  إذا (properties == error_mark_گره)
    c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);
  وإلا
    {
      إذا (properties == NULL_درخت)
	c_parser_error (parser, "expected identifier");
      وإلا
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  لكل (; properties; properties = درخت_CHAIN (properties))
	    objc_جمع_کن_property_declaration (loc, copy_گره (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  طالما (!prop_attr_list.is_خالی())
    حذف prop_attr_list.برداشت ();
  prop_attr_list.release ();
  parser->error = خطأ;
}

/* Parse an Objective-C @synthesize declaration.  The syntax is:

   objc-synthesize-declaration:
     @synthesize objc-synthesize-identifier-list ;

   objc-synthesize-identifier-list:
     objc-synthesize-identifier
     objc-synthesize-identifier-list, objc-synthesize-identifier

   objc-synthesize-identifier
     identifier
     identifier = identifier

  For example:
    @synthesize MyProperty;
    @synthesize OneProperty, AnotherProperty=MyIvar, YetAnotherProperty;

  PS: This function is identical to cp_parser_objc_at_synthesize_declaration
  for C++.  Keep them in sync.
*/
ساكن فراغ
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  درخت list = NULL_درخت;
  location_t loc;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  طالما (درست)
    {
      درخت property, ivar;
      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = خطأ;
	  أرجع;
	}
      property = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);
	      parser->error = خطأ;
	      أرجع;
	    }
	  ivar = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	}
      وإلا
	ivar = NULL_درخت;
      list = chainon (list, build_درخت_list (ivar, property));
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_جمع_کن_synthesize_declaration (loc, list);
}

/* Parse an Objective-C @dynamic declaration.  The syntax is:

   objc-dynamic-declaration:
     @dynamic identifier-list ;

   For example:
     @dynamic MyProperty;
     @dynamic MyProperty, AnotherProperty;

  PS: This function is identical to cp_parser_objc_at_dynamic_declaration
  for C++.  Keep them in sync.
*/
ساكن فراغ
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  درخت list = NULL_درخت;
  location_t loc;
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  طالما (درست)
    {
      درخت property;
      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);
	  parser->error = خطأ;
	  أرجع;
	}
      property = c_parser_peek_token (parser)->مقدار;
      list = chainon (list, build_درخت_list (NULL_درخت, property));
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_جمع_کن_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

ساكن منطقي
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);
  أرجع درست;
}

/* Parse a pragma GCC novector.  */

ساكن منطقي
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);
  أرجع درست;
}

/* Parse a pragma GCC unroll.  */

ساكن بیعلامت کوتاه
c_parser_pragma_unroll (c_parser *parser)
{
  بیعلامت کوتاه unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  درخت عبارت = c_parser_عبارت_no_commas (parser, عدم).مقدار;
  mark_exp_read (عبارت);
  عبارت = c_fully_fold (عبارت, خطأ, عدم);
  HOST_WIDE_INT lunroll = 0;
  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (عبارت))
      || درخت_کد (عبارت) != INTEGER_CST
      || (lunroll = درخت_مقصد_shwi (عبارت)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  وإلا
    {
      unroll = (بیعلامت کوتاه)lunroll;
      إذا (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_مقصد_pragma_eol (parser);
  أرجع unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

ساكن منطقي
c_parser_pragma (c_parser *parser, تعداد pragma_context context, منطقي *if_p,
		 درخت before_labels)
{
  بیعلامت صحيح id;
  ثابت حرف *construct = عدم;

  درون_داد_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_نوع;
  gcc_assert (id != PRAGMA_NONE);
  إذا (parser->omp_for_parse_state
      && parser->omp_for_parse_state->درون_intervening_کد
      && id >= PRAGMA_OMP_شروع && id <= PRAGMA_OMP_آخرین
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	درون_داد_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = درست;
      c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;
    }

  بدل (id)
    {
    حالة PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      أرجع خطأ;

    حالة PRAGMA_OACC_ENTER_داده:
      إذا (context != pragma_compound)
	{
	  construct = "acc enter data";
	درون_compound:
	  إذا (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
	      أرجع درست;
	    }
	  اذهب bad_stmt;
	}
      c_parser_oacc_enter_exit_داده (parser, درست);
      أرجع خطأ;

    حالة PRAGMA_OACC_EXIT_داده:
      إذا (context != pragma_compound)
	{
	  construct = "acc exit data";
	  اذهب درون_compound;
	}
      c_parser_oacc_enter_exit_داده (parser, خطأ);
      أرجع خطأ;

    حالة PRAGMA_OACC_ROUTINE:
      إذا (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
	  أرجع خطأ;
	}
      c_parser_oacc_routine (parser, context);
      أرجع خطأ;

    حالة PRAGMA_OACC_UPDATE:
      إذا (context != pragma_compound)
	{
	  construct = "acc update";
	  اذهب درون_compound;
	}
      c_parser_oacc_update (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_BARRIER:
      إذا (context != pragma_compound)
	{
	  construct = "omp barrier";
	  اذهب درون_compound;
	}
      c_parser_omp_barrier (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_DEPOBJ:
      إذا (context != pragma_compound)
	{
	  construct = "omp depobj";
	  اذهب درون_compound;
	}
      c_parser_omp_depobj (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_FLUSH:
      إذا (context != pragma_compound)
	{
	  construct = "omp flush";
	  اذهب درون_compound;
	}
      c_parser_omp_flush (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_INTEROP:
      إذا (context != pragma_compound)
	{
	  construct = "omp interop";
	  اذهب درون_compound;
	}
      c_parser_omp_interop (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_TASKWAIT:
      إذا (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  اذهب درون_compound;
	}
      c_parser_omp_taskwait (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_TASKYIELD:
      إذا (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  اذهب درون_compound;
	}
      c_parser_omp_taskyield (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_CANCEL:
      إذا (context != pragma_compound)
	{
	  construct = "omp cancel";
	  اذهب درون_compound;
	}
      c_parser_omp_cancel (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_CANCELLATION_نقطه:
      أرجع c_parser_omp_cancellation_نقطه (parser, context);

    حالة PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_هدف:
      أرجع c_parser_omp_هدف (parser, context, if_p);

    حالة PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_انتها:
      c_parser_omp_انتها (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_پیمایش:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OMP_DECLARE:
      أرجع c_parser_omp_declare (parser, context);

    حالة PRAGMA_OMP_REQUIRES:
      إذا (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
	  أرجع خطأ;
	}
      c_parser_omp_requires (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_ASSUMES:
      إذا (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
	  أرجع خطأ;
	}
      c_parser_omp_assumes (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      أرجع درست;

    حالة PRAGMA_OMP_ERROR:
      أرجع c_parser_omp_error (parser, context);

    حالة PRAGMA_OMP_ORDERED:
      أرجع c_parser_omp_ordered (parser, context, if_p);

    حالة PRAGMA_NOVECTOR:
    حالة PRAGMA_UNROLL:
    حالة PRAGMA_IVDEP:
      {
	منطقي novector = خطأ;
	بیعلامت کوتاه unroll = 0;
	منطقي ivdep = خطأ;

	بدل (id)
	  {
	  حالة PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    اكسر;
	  حالة PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    اكسر;
	  حالة PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	منطقي has_بیشتر = tok->type == CPP_PRAGMA;
	طالما (has_بیشتر)
	  {
	    بدل (tok->pragma_نوع)
	      {
	      حالة PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		اكسر;
	      حالة PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		اكسر;
	      حالة PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		اكسر;
	      افتراضي:
		has_بیشتر = خطأ;
		اكسر;
	      }
	    tok = c_parser_peek_token (parser);
	    has_بیشتر = has_بیشتر && tok->type == CPP_PRAGMA;
	  }
	إذا (!c_parser_بعدی_token_is_keyword (parser, RID_FOR)
	    && !c_parser_بعدی_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_بعدی_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    أرجع خطأ;
	  }
	إذا (c_parser_بعدی_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	وإلا
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      أرجع درست;

    حالة PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OACC_WAIT:
      إذا (context != pragma_compound)
	{
	  construct = "acc wait";
	  اذهب درون_compound;
	}
	/* FALL THROUGH.  */

    افتراضي:
      إذا (id < PRAGMA_اولی_EXTERNAL)
	{
	  إذا (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_یافت (parser, CPP_PRAGMA_EOL, عدم);
	      أرجع خطأ;
	    }
	  c_parser_omp_construct (parser, if_p);
	  أرجع درست;
	}
      اكسر;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = درست;
  c_parser_skip_مقصد_pragma_eol (parser);

  أرجع خطأ;
}

/* The interface the pragma parsers have to the lexer.  */

تعداد cpp_ttype
pragma_lex (درخت *مقدار, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  تعداد cpp_ttype ret = tok->type;

  *مقدار = tok->مقدار;
  إذا (loc)
    *loc = tok->location;

  إذا (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  وإلا إذا (ret == CPP_STRING)
    *مقدار = c_parser_string_literal (the_parser, خطأ, خطأ).مقدار;
  وإلا
    {
      إذا (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  أرجع ret;
}

فراغ
pragma_lex_discard_مقصد_eol ()
{
  cpp_ttype type;
  افعل
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } طالما (type != CPP_PRAGMA_EOL);
}

ساكن فراغ
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  درخت name = عدم;

  parser->lex_joined_string = درست;
  c_parser_consume_pragma (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
    }
  وإلا
    c_parser_error (parser, "expected string literal");
  c_parser_skip_مقصد_pragma_eol (parser);
  parser->lex_joined_string = خطأ;

  إذا (name)
    c_common_pch_pragma (parse_درون, درخت_STRING_اشاره_گر (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

ساكن pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause نتیجه = PRAGMA_OMP_CLAUSE_NONE;

  إذا (c_parser_بعدی_token_is_keyword (parser, RID_AUTO))
    نتیجه = PRAGMA_OACC_CLAUSE_AUTO;
  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_IF))
    نتیجه = PRAGMA_OMP_CLAUSE_IF;
  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_DEFAULT))
    نتیجه = PRAGMA_OMP_CLAUSE_DEFAULT;
  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_FOR))
    نتیجه = PRAGMA_OMP_CLAUSE_FOR;
  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      بدل (p[0])
	{
	حالة 'a':
	  إذا (!strcmp ("affinity", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_AFFINITY;
	  وإلا إذا (!strcmp ("aligned", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_ALIGNED;
	  وإلا إذا (!strcmp ("allocate", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  وإلا إذا (!strcmp ("async", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_ASYNC;
	  وإلا إذا (!strcmp ("attach", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_ATTACH;
	  اكسر;
	حالة 'b':
	  إذا (!strcmp ("bind", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_BIND;
	  اكسر;
	حالة 'c':
	  إذا (!strcmp ("collapse", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  وإلا إذا (!strcmp ("copy", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_COPY;
	  وإلا إذا (!strcmp ("copyin", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_COPYIN;
	  وإلا إذا (!strcmp ("copyout", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_COPYOUT;
          وإلا إذا (!strcmp ("copyprivate", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  وإلا إذا (!strcmp ("create", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_CREATE;
	  اكسر;
	حالة 'd':
	  إذا (!strcmp ("defaultmap", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  وإلا إذا (!strcmp ("delete", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_DELETE;
	  وإلا إذا (!strcmp ("depend", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_DEPEND;
	  وإلا إذا (!strcmp ("destroy", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_DESTROY;
	  وإلا إذا (!strcmp ("detach", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_DETACH;
	  وإلا إذا (!strcmp ("device", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_DEVICE;
	  وإلا إذا (!strcmp ("deviceptr", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  وإلا إذا (!strcmp ("device_resident", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  وإلا إذا (!strcmp ("device_type", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  وإلا إذا (!strcmp ("dist_schedule", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_DIST_زمانبندی;
	  وإلا إذا (!strcmp ("doacross", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_DOACROSS;
	  وإلا إذا (!strcmp ("dyn_groupprivate", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  اكسر;
	حالة 'e':
	  إذا (!strcmp ("enter", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_ENTER;
	  اكسر;
	حالة 'f':
	  إذا (!strcmp ("filter", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_FILTER;
	  وإلا إذا (!strcmp ("final", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_FINAL;
	  وإلا إذا (!strcmp ("finalize", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_FINALIZE;
	  وإلا إذا (!strcmp ("firstprivate", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  وإلا إذا (!strcmp ("from", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_FROM;
	  وإلا إذا (!strcmp ("full", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_پر;
	  اكسر;
	حالة 'g':
	  إذا (!strcmp ("gang", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_GANG;
	  وإلا إذا (!strcmp ("grainsize", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  اكسر;
	حالة 'h':
	  إذا (!strcmp ("has_device_addr", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  وإلا إذا (!strcmp ("hint", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_HINT;
	  وإلا إذا (!strcmp ("host", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_HOST;
	  اكسر;
	حالة 'i':
	  إذا (!strcmp ("if_present", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  وإلا إذا (!strcmp ("in_reduction", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_درون_REDUCTION;
	  وإلا إذا (!strcmp ("inbranch", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_INBRANCH;
	  وإلا إذا (!strcmp ("independent", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  وإلا إذا (!strcmp ("indirect", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_غیرمستقیم;
	  وإلا إذا (!strcmp ("init", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_INIT;
	  وإلا إذا (!strcmp ("is_device_ptr", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  وإلا إذا (!strcmp ("interop", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_INTEROP;
	  اكسر;
	حالة 'l':
	  إذا (!strcmp ("lastprivate", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  وإلا إذا (!strcmp ("linear", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_خطی;
	  وإلا إذا (!strcmp ("link", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_LINK;
	  وإلا إذا (!strcmp ("local", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_LOCAL;
	  اكسر;
	حالة 'm':
	  إذا (!strcmp ("map", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_MAP;
	  وإلا إذا (!strcmp ("mergeable", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  اكسر;
	حالة 'n':
	  إذا (!strcmp ("no_create", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  وإلا إذا (!strcmp ("nocontext", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  وإلا إذا (!strcmp ("nogroup", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_NOGROUP;
	  وإلا إذا (!strcmp ("nohost", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_NOHOST;
	  وإلا إذا (!strcmp ("nontemporal", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  وإلا إذا (!strcmp ("notinbranch", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  وإلا إذا (!strcmp ("novariants", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  وإلا إذا (!strcmp ("nowait", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_NOWAIT;
	  وإلا إذا (!strcmp ("num_gangs", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_رقم_GANGS;
	  وإلا إذا (!strcmp ("num_tasks", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_رقم_TASKS;
	  وإلا إذا (!strcmp ("num_teams", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_رقم_TEAMS;
	  وإلا إذا (!strcmp ("num_threads", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_رقم_نخها;
	  وإلا إذا (!strcmp ("num_workers", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_رقم_WORKERS;
	  اكسر;
	حالة 'o':
	  إذا (!strcmp ("ordered", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_ORDERED;
	  وإلا إذا (!strcmp ("order", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_ترتیب;
	  اكسر;
	حالة 'p':
	  إذا (!strcmp ("parallel", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_PARALLEL;
	  وإلا إذا (!strcmp ("partial", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_PARTIAL;
	  وإلا إذا (!strcmp ("present", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  وإلا إذا (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_COPY;
	  وإلا إذا (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_COPYIN;
	  وإلا إذا (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_COPYOUT;
	  وإلا إذا (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_CREATE;
	  وإلا إذا (!strcmp ("priority", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_اولویت;
	  وإلا إذا (!strcmp ("private", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_خصوصی;
	  وإلا إذا (!strcmp ("proc_bind", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  اكسر;
	حالة 'r':
	  إذا (!strcmp ("reduction", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_REDUCTION;
	  اكسر;
	حالة 's':
	  إذا (!strcmp ("safelen", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_SAFELEN;
	  وإلا إذا (!strcmp ("schedule", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_زمانبندی;
	  وإلا إذا (!strcmp ("sections", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_SECTIONS;
	  وإلا إذا (!strcmp ("self", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_SELF;
	  وإلا إذا (!strcmp ("seq", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_SEQ;
	  وإلا إذا (!strcmp ("shared", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_SHARED;
	  وإلا إذا (!strcmp ("simd", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_SIMD;
	  وإلا إذا (!strcmp ("simdlen", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  اكسر;
	حالة 't':
	  إذا (!strcmp ("task_reduction", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  وإلا إذا (!strcmp ("taskgroup", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  وإلا إذا (!strcmp ("thread_limit", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_THREAD_حد;
	  وإلا إذا (!strcmp ("threads", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_نخها;
	  وإلا إذا (!strcmp ("tile", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_TILE;
	  وإلا إذا (!strcmp ("to", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_مقصد;
	  اكسر;
	حالة 'u':
	  إذا (!strcmp ("uniform", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_یکنواخت;
	  وإلا إذا (!strcmp ("untied", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_UNTIED;
	  وإلا إذا (!strcmp ("use", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_USE;
	  وإلا إذا (!strcmp ("use_device", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  وإلا إذا (!strcmp ("use_device_addr", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  وإلا إذا (!strcmp ("use_device_ptr", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  وإلا إذا (!strcmp ("uses_allocators", p))
	    نتیجه = PRAGMA_OMP_CLAUSE_استفاده_میکند_ALLOCATORS;
	  اكسر;
	حالة 'v':
	  إذا (!strcmp ("vector", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_وکتور;
	  وإلا إذا (!strcmp ("vector_length", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_وکتور_درازی;
	  اكسر;
	حالة 'w':
	  إذا (!strcmp ("wait", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_WAIT;
	  وإلا إذا (!strcmp ("worker", p))
	    نتیجه = PRAGMA_OACC_CLAUSE_کارگر;
	  اكسر;
	}
    }

  إذا (نتیجه != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  أرجع نتیجه;
}

/* Validate that a clause of the given type does not already exist.  */

ساكن فراغ
check_no_duplicate_clause (درخت clauses, تعداد omp_clause_کد کد,
			   ثابت حرف *name)
{
  إذا (درخت c = omp_پیدا_کن_clause (clauses, کد))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

ساكن درخت
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, درخت list)
{
  vec<درخت, va_gc> *آرگومانها;
  درخت t, آرگومانها_درخت;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  آرگومانها = c_parser_عبارت_list (parser, خطأ, درست, عدم, عدم, عدم, عدم);
  آرگومانها_درخت = build_درخت_list_vec (آرگومانها);

  لكل (t = آرگومانها_درخت; t; t = درخت_CHAIN (t))
    {
      درخت targ = درخت_مقدار (t);

      إذا (targ != error_mark_گره)
	{
	  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_گره;
	    }
	  وإلا
	    {
	      درخت c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_درخت_وکتور (آرگومانها);
  parens.require_close (parser);
  أرجع list;
}

/* OpenACC 2.0, OpenMP 2.5:
   variable-list:
     identifier
     variable-list , identifier

   If KIND is nonzero, create the appropriate node and install the
   decl in OMP_CLAUSE_DECL and add the node to the head of the list.
   If KIND is nonzero, CLAUSE_LOC is the location of the clause.

   If KIND is zero (= OMP_CLAUSE_ERROR), create a TREE_LIST with the decl
   in TREE_PURPOSE and the location in TREE_VALUE (accessible using
   EXPR_LOCATION); return the list created.

   The optional ALLOW_DEREF argument is true if list items can use the deref
   (->) operator.  */

بنية omp_dim
{
  درخت کم_bound, درازی;
  location_t loc;
  منطقي no_colon;
  omp_dim (درخت lb, درخت len, location_t lo, منطقي nc)
  : کم_bound (lb), درازی (len), loc (lo), no_colon (nc) {}
};

ساكن درخت
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    تعداد omp_clause_کد نوع, درخت list,
			    منطقي map_lvalue = خطأ)
{
  auto_vec<omp_dim> dims;
  منطقي array_section_p;
  auto_vec<c_token> نشانهها;
  بیعلامت صحيح نشانهها_avail = 0;
  c_token *saved_نشانهها = عدم;

  طالما (1)
    {
      درخت t = NULL_درخت;
      location_t tloc = c_parser_peek_token (parser)->location;

      إذا (نوع == OMP_CLAUSE_DEPEND || نوع == OMP_CLAUSE_AFFINITY)
	{
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_نوع != C_ID_ID)
	    {
	      بنية c_عبارت عبارت;
	      إذا (نوع == OMP_CLAUSE_DEPEND
		  && c_parser_بعدی_token_is_keyword (parser,
						     RID_OMP_ALL_حافظه)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  عبارت.مقدار = ridpointers[RID_OMP_ALL_حافظه];
		  c_parser_consume_token (parser);
		}
	      وإلا
		عبارت = c_parser_عبارت_no_commas (parser, عدم);
	      إذا (عبارت.مقدار != error_mark_گره)
		{
		  درخت u = build_omp_clause (clause_loc, نوع);
		  OMP_CLAUSE_DECL (u) = عبارت.مقدار;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      إذا (c_parser_بعدی_token_is_not (parser, CPP_COMMA))
		اكسر;

	      c_parser_consume_token (parser);
	      استمر;
	    }

	  نشانهها.truncate (0);
	  بیعلامت صحيح nesting_عمق = 0;
	  طالما (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      بدل (token->type)
		{
		حالة CPP_EOF:
		حالة CPP_PRAGMA_EOL:
		  اكسر;
		حالة CPP_OPEN_BRACE:
		حالة CPP_OPEN_PAREN:
		حالة CPP_OPEN_مربع:
		  ++nesting_عمق;
		  اذهب جمع_کن;
		حالة CPP_CLOSE_BRACE:
		حالة CPP_CLOSE_PAREN:
		حالة CPP_CLOSE_مربع:
		  إذا (nesting_عمق-- == 0)
		    اكسر;
		  اذهب جمع_کن;
		حالة CPP_COMMA:
		  إذا (nesting_عمق == 0)
		    اكسر;
		  اذهب جمع_کن;
		افتراضي:
		جمع_کن:
		  نشانهها.امن_افزودن (*token);
		  c_parser_consume_token (parser);
		  استمر;
		}
	      اكسر;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, حجم (eof_token));
	  eof_token.type = CPP_EOF;
	  نشانهها.امن_افزودن (eof_token);
	  نشانهها.امن_افزودن (eof_token);

	  saved_نشانهها = parser->نشانهها;
	  نشانهها_avail = parser->نشانهها_avail;
	  parser->نشانهها = نشانهها.آدرس ();
	  parser->نشانهها_avail = نشانهها.درازی ();
	}
      وإلا إذا (map_lvalue
	       && (نوع == OMP_CLAUSE_MAP
		   || نوع == OMP_CLAUSE_مقصد
		   || نوع == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = درست;
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  إذا (عبارت.مقدار != error_mark_گره)
	    mark_exp_read (عبارت.مقدار);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  درخت decl = عبارت.مقدار;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  إذا (درخت_کد (decl) == OMP_ARRAY_SECTION)
	    {
	      طالما (درخت_کد (decl) == OMP_ARRAY_SECTION)
		{
		  درخت کم_bound = درخت_عملوند (decl, 1);
		  درخت درازی = درخت_عملوند (decl, 2);
		  dims.امن_افزودن (omp_dim (کم_bound, درازی, loc, خطأ));
		  decl = درخت_عملوند (decl, 0);
		}

	      طالما (درخت_کد (decl) == ARRAY_REF
		     || درخت_کد (decl) == غیرمستقیم_REF
		     || درخت_کد (decl) == COMPOUND_عبارت)
		{
		  إذا (درخت_کد (decl) == COMPOUND_عبارت)
		    {
		      decl = درخت_عملوند (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  وإلا إذا (درخت_کد (decl) == غیرمستقیم_REF)
		    {
		      dims.امن_افزودن (omp_dim (integer_zero_گره,
					       integer_one_گره, loc, درست));
		      decl = درخت_عملوند (decl, 0);
		    }
		  وإلا  /* ARRAY_REF. */
		    {
		      درخت شاخص = درخت_عملوند (decl, 1);
		      dims.امن_افزودن (omp_dim (شاخص, integer_one_گره, loc,
					       درست));
		      decl = درخت_عملوند (decl, 0);
		    }
		}

	      لكل (صحيح i = dims.درازی () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].کم_bound,
						dims[i].درازی);
	    }
	  وإلا إذا (درخت_کد (decl) == غیرمستقیم_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = درخت_عملوند (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_گره,
					      integer_one_گره);
	    }
	  وإلا إذا (درخت_کد (decl) == ARRAY_REF)
	    {
	      درخت idx = درخت_عملوند (decl, 1);

	      decl = درخت_عملوند (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_گره);
	    }
	  وإلا إذا (درخت_کد (decl) == NON_LVALUE_عبارت
		   || CONVERT_عبارت_P (decl))
	    decl = درخت_عملوند (decl, 0);

	  درخت u = build_omp_clause (loc, نوع);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  اذهب بعدی_قلم;
	}

      إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_نوع == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->مقدار);

	  إذا (t == NULL_درخت)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->مقدار);
	      t = error_mark_گره;
	    }

	  c_parser_consume_token (parser);
	}
      وإلا إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).مقدار;
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}

      إذا (t == error_mark_گره)
	;
      وإلا إذا (نوع != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  بدل (نوع)
	    {
	    حالة OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      إذا (c_parser_peek_token (parser)->type != CPP_OPEN_مربع)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_گره;
		  اكسر;
		}
	      /* FALLTHROUGH  */
	    حالة OMP_CLAUSE_MAP:
	    حالة OMP_CLAUSE_FROM:
	    حالة OMP_CLAUSE_مقصد:
	    شروع_component_ref:
	      طالما (c_parser_بعدی_token_is (parser, CPP_DOT)
		     || c_parser_بعدی_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  إذا (c_parser_بعدی_token_is (parser, CPP_DEREF))
		    {
		      c_عبارت t_عبارت;
		      t_عبارت.مقدار = t;
		      t_عبارت.original_کد = ERROR_MARK;
		      t_عبارت.original_type = عدم;
		      مجموعه_c_عبارت_منبع_range (&t_عبارت, op_loc, op_loc);
		      t_عبارت.m_decimal = 0;
		      t_عبارت = convert_lvalue_مقصد_rvalue (op_loc, t_عبارت,
							 درست, خطأ);
		      t = build_غیرمستقیم_ref (op_loc, t_عبارت.مقدار, RO_ARROW);
		      arrow_loc = t_عبارت.get_location ();
		    }
		  c_parser_consume_token (parser);
		  إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_گره;
		      اكسر;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  درخت ident = comp_tok->مقدار;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    حالة OMP_CLAUSE_AFFINITY:
	    حالة OMP_CLAUSE_DEPEND:
	    حالة OMP_CLAUSE_REDUCTION:
	    حالة OMP_CLAUSE_درون_REDUCTION:
	    حالة OMP_CLAUSE_TASK_REDUCTION:
	    حالة OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = خطأ;
	      dims.truncate (0);
	      طالما (c_parser_بعدی_token_is (parser, CPP_OPEN_مربع))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  درخت کم_bound = NULL_درخت, درازی = NULL_درخت;
		  منطقي no_colon = خطأ;

		  c_parser_consume_token (parser);
		  إذا (!c_parser_بعدی_token_is (parser, CPP_COLON))
		    {
		      location_t عبارت_loc
			= c_parser_peek_token (parser)->location;
		      c_عبارت عبارت = c_parser_عبارت (parser);
		      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت,
						       خطأ, درست);
		      کم_bound = عبارت.مقدار;
		      loc = عبارت_loc;
		    }
		  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_مربع))
		    {
		      درازی = integer_one_گره;
		      no_colon = درست;
		    }
		  وإلا
		    {
		      /* Look for `:'.  */
		      إذا (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_گره;
			  اكسر;
			}
		      array_section_p = درست;
		      إذا (!c_parser_بعدی_token_is (parser, CPP_CLOSE_مربع))
			{
			  location_t عبارت_loc
			    = c_parser_peek_token (parser)->location;
			  c_عبارت عبارت = c_parser_عبارت (parser);
			  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت,
							   خطأ, درست);
			  درازی = عبارت.مقدار;
			}
		    }
		  /* Look for the closing `]'.  */
		  إذا (!c_parser_require (parser, CPP_CLOSE_مربع,
					 "expected %<]%>"))
		    {
		      t = error_mark_گره;
		      اكسر;
		    }

		  dims.امن_افزودن (omp_dim (کم_bound, درازی, loc, no_colon));
		}

	      إذا (t != error_mark_گره)
		{
		  إذا ((نوع == OMP_CLAUSE_MAP
		       || نوع == OMP_CLAUSE_FROM
		       || نوع == OMP_CLAUSE_مقصد)
		      && !array_section_p
		      && (c_parser_بعدی_token_is (parser, CPP_DOT)
			  || c_parser_بعدی_token_is (parser, CPP_DEREF)))
		    {
		      لكل (بیعلامت i = 0; i < dims.درازی (); i++)
			{
			  gcc_assert (dims[i].درازی == integer_one_گره);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].کم_bound);
			}
		      اذهب شروع_component_ref;
		    }
		  وإلا
		    لكل (بیعلامت i = 0; i < dims.درازی (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].کم_bound,
						   dims[i].درازی);
		}

	      إذا ((نوع == OMP_CLAUSE_DEPEND || نوع == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_گره
		  && parser->نشانهها_avail != 2)
		{
		  إذا (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_گره;
		    }
		  وإلا
		    {
		      parser->نشانهها = نشانهها.آدرس ();
		      parser->نشانهها_avail = نشانهها.درازی ();

		      t = c_parser_عبارت_no_commas (parser, عدم).مقدار;
		      إذا (t != error_mark_گره && parser->نشانهها_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_گره;
			}
		    }
		}
	      اكسر;
	    افتراضي:
	      اكسر;
	    }

	  إذا (t != error_mark_گره)
	    {
	      درخت u = build_omp_clause (clause_loc, نوع);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      وإلا  /* kind == OMP_CLAUSE_ERROR */
	list = درخت_cons (t, build_خالی_stmt (tloc), list);

      إذا (نوع == OMP_CLAUSE_DEPEND || نوع == OMP_CLAUSE_AFFINITY)
	{
	  parser->نشانهها = saved_نشانهها;
	  parser->نشانهها_avail = نشانهها_avail;
	}

    بعدی_قلم:
      إذا (c_parser_بعدی_token_is_not (parser, CPP_COMMA))
	اكسر;

      c_parser_consume_token (parser);
    }

  أرجع list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

ساكن درخت
c_parser_omp_var_list_parens (c_parser *parser, تعداد omp_clause_کد نوع,
			      درخت list, منطقي map_lvalue = خطأ)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (parser->درون_omp_decl_attribute)
    {
      إذا (نوع)
	{
	  درخت u = build_omp_clause (loc, نوع);
	  OMP_CLAUSE_DECL (u) = parser->درون_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  أرجع u;
	}
      وإلا
	أرجع درخت_cons (parser->درون_omp_decl_attribute, NULL_درخت, list);
    }

  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, نوع, list, map_lvalue);
      parens.skip_until_یافت_close (parser);
    }
  أرجع list;
}

/* OpenACC 2.0:
   copy ( variable-list )
   copyin ( variable-list )
   copyout ( variable-list )
   create ( variable-list )
   delete ( variable-list )
   present ( variable-list )

   OpenACC 2.6:
   no_create ( variable-list )
   attach ( variable-list )
   detach ( variable-list )

   OpenACC 2.7:
   copyin (readonly : variable-list )
 */

ساكن درخت
c_parser_oacc_داده_clause (c_parser *parser, pragma_omp_clause c_نوع,
			   درخت list)
{
  تعداد gomp_map_نوع نوع;
  بدل (c_نوع)
    {
    حالة PRAGMA_OACC_CLAUSE_ATTACH:
      نوع = GOMP_MAP_ATTACH;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPY:
      نوع = GOMP_MAP_TOFROM;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPYIN:
      نوع = GOMP_MAP_مقصد;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPYOUT:
      نوع = GOMP_MAP_FROM;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_CREATE:
      نوع = GOMP_MAP_ALLOC;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DELETE:
      نوع = GOMP_MAP_RELEASE;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DETACH:
      نوع = GOMP_MAP_DETACH;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DEVICE:
      نوع = GOMP_MAP_FORCE_مقصد;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      نوع = GOMP_MAP_DEVICE_RESIDENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_LINK:
      نوع = GOMP_MAP_LINK;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_NO_CREATE:
      نوع = GOMP_MAP_IF_PRESENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_PRESENT:
      نوع = GOMP_MAP_FORCE_PRESENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    حالة PRAGMA_OACC_CLAUSE_HOST:
      نوع = GOMP_MAP_FORCE_FROM;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  درخت nl = list;
  منطقي readonly = خطأ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      إذا (c_نوع == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_اشاره_گر (token->مقدار), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = درست;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       خطأ);
      parens.skip_until_یافت_close (parser);
    }

  لكل (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_مجموعه_MAP_نوع (c, نوع);
      إذا (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  أرجع nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

ساكن درخت
c_parser_oacc_داده_clause_deviceptr (c_parser *parser, درخت list)
{
  درخت vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
  لكل (t = vars; t && t; t = درخت_CHAIN (t))
    {
      درخت v = درخت_PURPOSE (t);
      location_t loc = عبارت_LOCATION (درخت_مقدار (t));

      إذا (!VAR_P (v) && درخت_کد (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      وإلا إذا (درخت_TYPE (v) == error_mark_گره)
	;
      وإلا إذا (!اشاره_گر_TYPE_P (درخت_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      درخت u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_مجموعه_MAP_نوع (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  أرجع list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

ساكن درخت
c_parser_omp_clause_collapse (c_parser *parser, درخت list)
{
  درخت c, رقم = error_mark_گره;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      رقم = c_parser_عبارت_no_commas (parser, عدم).مقدار;
      parens.skip_until_یافت_close (parser);
    }
  إذا (رقم == error_mark_گره)
    أرجع list;
  mark_exp_read (رقم);
  رقم = c_fully_fold (رقم, خطأ, عدم);
  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (رقم))
      || !درخت_میگنجد_shwi_p (رقم)
      || (n = درخت_مقصد_shwi (رقم)) <= 0
      || (صحيح) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      أرجع list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_عبارت (c) = رقم;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

ساكن درخت
c_parser_omp_clause_copyin (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

ساكن درخت
c_parser_omp_clause_copyprivate (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

ساكن درخت
c_parser_omp_clause_default (c_parser *parser, درخت list, منطقي is_oacc)
{
  تعداد omp_clause_default_نوع نوع = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      بدل (p[0])
	{
	حالة 'n':
	  إذا (strcmp ("none", p) != 0)
	    اذهب invalid_نوع;
	  نوع = OMP_CLAUSE_DEFAULT_NONE;
	  اكسر;

	حالة 'p':
	  إذا (is_oacc)
	    {
	      إذا (strcmp ("present", p) != 0)
		اذهب invalid_نوع;
	      نوع = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  وإلا
	    {
	      إذا (strcmp ("private", p) != 0)
		اذهب invalid_نوع;
	      نوع = OMP_CLAUSE_DEFAULT_خصوصی;
	    }
	  اكسر;

	حالة 'f':
	  إذا (strcmp ("firstprivate", p) != 0 || is_oacc)
	    اذهب invalid_نوع;
	  نوع = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  اكسر;

	حالة 's':
	  إذا (strcmp ("shared", p) != 0 || is_oacc)
	    اذهب invalid_نوع;
	  نوع = OMP_CLAUSE_DEFAULT_SHARED;
	  اكسر;

	افتراضي:
	  اذهب invalid_نوع;
	}

      c_parser_consume_token (parser);
    }
  وإلا
    {
    invalid_نوع:
      إذا (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      وإلا
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_یافت_close (parser);

  إذا (نوع == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_نوع (c) = نوع;

  أرجع c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

ساكن درخت
c_parser_omp_clause_firstprivate (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

ساكن درخت
c_parser_omp_clause_final (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      درخت t, c;
      إذا (!parens.require_open (parser))
	t = error_mark_گره;
      وإلا
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  t = convert_lvalue_مقصد_rvalue (eloc, عبارت, درست, درست).مقدار;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, خطأ, عدم);
	  parens.skip_until_یافت_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  وإلا
    c_parser_error (parser, "expected %<(%>");

  أرجع list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

ساكن درخت
c_parser_omp_clause_غیرمستقیم (c_parser *parser, درخت list)
{
  location_t location = c_parser_peek_token (parser)->location;
  درخت t;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      إذا (!parens.require_open (parser))
	أرجع list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, درست, درست);
      t = c_objc_common_truthvalue_conversion (loc, عبارت.مقدار);
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_کد (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  أرجع list;
	}
      parens.skip_until_یافت_close (parser);
    }
  وإلا
    t = integer_one_گره;

  check_no_duplicate_clause (list, OMP_CLAUSE_غیرمستقیم, "indirect");

  درخت c = build_omp_clause (location, OMP_CLAUSE_غیرمستقیم);
  OMP_CLAUSE_غیرمستقیم_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenACC, OpenMP 2.5:
   if ( expression )

   OpenMP 4.5:
   if ( directive-name-modifier : expression )

   directive-name-modifier:
     parallel | task | taskloop | target data | target | target update
     | target enter data | target exit data

   OpenMP 5.0:
   directive-name-modifier:
     ... | simd | cancel  */

ساكن درخت
c_parser_omp_clause_if (c_parser *parser, درخت list, منطقي is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  تعداد درخت_کد_2 if_modifier = ERROR_MARK;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (is_omp && c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      صحيح n = 2;
      إذا (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      وإلا إذا (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      وإلا إذا (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      وإلا إذا (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      وإلا إذا (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      وإلا إذا (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_هدف;
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_اشاره_گر (c_parser_peek_2nd_token (parser)->مقدار);
	      إذا (strcmp ("data", p) == 0)
		if_modifier = OMP_هدف_داده;
	      وإلا إذا (strcmp ("update", p) == 0)
		if_modifier = OMP_هدف_UPDATE;
	      وإلا إذا (strcmp ("enter", p) == 0)
		if_modifier = OMP_هدف_ENTER_داده;
	      وإلا إذا (strcmp ("exit", p) == 0)
		if_modifier = OMP_هدف_EXIT_داده;
	      إذا (if_modifier != OMP_هدف)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      وإلا
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      إذا (if_modifier == OMP_هدف_ENTER_داده
		  || if_modifier == OMP_هدف_EXIT_داده)
		{
		  إذا (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_اشاره_گر
				(c_parser_peek_2nd_token (parser)->مقدار);
		      إذا (strcmp ("data", p) == 0)
			n = 4;
		    }
		  إذا (n == 4)
		    c_parser_consume_token (parser);
		  وإلا
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      إذا (if_modifier != ERROR_MARK)
	{
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      إذا (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
  عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, درست, درست);
  درخت t = c_objc_common_truthvalue_conversion (loc, عبارت.مقدار), c;
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_یافت_close (parser);

  لكل (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_IF)
      {
	إذا (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ثابت حرف *p = عدم;
	    بدل (if_modifier)
	      {
	      حالة VOID_CST: p = "cancel"; اكسر;
	      حالة OMP_PARALLEL: p = "parallel"; اكسر;
	      حالة OMP_SIMD: p = "simd"; اكسر;
	      حالة OMP_TASK: p = "task"; اكسر;
	      حالة OMP_TASKLOOP: p = "taskloop"; اكسر;
	      حالة OMP_هدف_داده: p = "target data"; اكسر;
	      حالة OMP_هدف: p = "target"; اكسر;
	      حالة OMP_هدف_UPDATE: p = "target update"; اكسر;
	      حالة OMP_هدف_ENTER_داده: p = "target enter data"; اكسر;
	      حالة OMP_هدف_EXIT_داده: p = "target exit data"; اكسر;
	      افتراضي: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    أرجع list;
	  }
	وإلا إذا (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    إذا (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    وإلا
	      error_at (location, "too many %<if%> clauses without modifier");
	    أرجع list;
	  }
	وإلا إذا (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    أرجع list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

ساكن درخت
c_parser_omp_clause_lastprivate (c_parser *parser, درخت list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      منطقي conditional = خطأ;
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	  إذا (strcmp (p, "conditional") == 0)
	    {
	      conditional = درست;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      درخت nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (conditional)
	لكل (درخت c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      أرجع nlist;
    }
  أرجع list;
}

/* OpenMP 3.1:
   mergeable */

ساكن درخت
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_استفادهنشده, درخت list)
{
  درخت c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 2.5:
   nowait */

ساكن درخت
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_استفادهنشده, درخت list)
{
  درخت c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

ساكن درخت
c_parser_omp_clause_رقم_نخها (c_parser *parser, درخت list)
{
  location_t رقم_نخها_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_یافت_close (parser);

      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
		       build_int_cst (درخت_TYPE (t), 0));
      protected_مجموعه_عبارت_location (c, عبارت_loc);
      إذا (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_رقم_نخها, "num_threads");

      c = build_omp_clause (رقم_نخها_loc, OMP_CLAUSE_رقم_نخها);
      OMP_CLAUSE_رقم_نخها_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

ساكن درخت
c_parser_omp_clause_رقم_tasks (c_parser *parser, درخت list)
{
  location_t رقم_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي strict = خطأ;
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار),
		     "strict") == 0)
	{
	  strict = درست;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_یافت_close (parser);

      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
			   build_int_cst (درخت_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	مجموعه_عبارت_LOCATION (c, عبارت_loc);
      إذا (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_رقم_TASKS, "num_tasks");

      c = build_omp_clause (رقم_tasks_loc, OMP_CLAUSE_رقم_TASKS);
      OMP_CLAUSE_رقم_TASKS_عبارت (c) = t;
      OMP_CLAUSE_رقم_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

ساكن درخت
c_parser_omp_clause_grainsize (c_parser *parser, درخت list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي strict = خطأ;
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار),
		     "strict") == 0)
	{
	  strict = درست;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_یافت_close (parser);

      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
			   build_int_cst (درخت_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	مجموعه_عبارت_LOCATION (c, عبارت_loc);
      إذا (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_عبارت (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   priority ( expression ) */

ساكن درخت
c_parser_omp_clause_اولویت (c_parser *parser, درخت list)
{
  location_t اولویت_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_یافت_close (parser);

      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (عبارت_loc, LT_عبارت, boolean_type_گره, t,
			   build_int_cst (درخت_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	مجموعه_عبارت_LOCATION (c, عبارت_loc);
      إذا (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_اولویت, "priority");

      c = build_omp_clause (اولویت_loc, OMP_CLAUSE_اولویت);
      OMP_CLAUSE_اولویت_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   hint ( expression ) */

ساكن درخت
c_parser_omp_clause_hint (c_parser *parser, درخت list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_کد (t) != INTEGER_CST
	  || درخت_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  أرجع list;
	}
      parens.skip_until_یافت_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

ساكن درخت
c_parser_omp_clause_filter (c_parser *parser, درخت list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}
      parens.skip_until_یافت_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

ساكن درخت
c_parser_omp_clause_defaultmap (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت حرف *p;
  تعداد omp_clause_defaultmap_نوع behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  تعداد omp_clause_defaultmap_نوع category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  وإلا إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      اذهب بیرون_err;
    }
  وإلا
    p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

  بدل (p[0])
    {
    حالة 'a':
      إذا (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 'd':
      إذا (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 'f':
      إذا (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      وإلا إذا (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 'n':
      إذا (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 'p':
      إذا (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    حالة 't':
      إذا (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      وإلا إذا (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_مقصد;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    افتراضي:
      اذهب invalid_behavior;
    }
  c_parser_consume_token (parser);

  إذا (!c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
    {
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	اذهب بیرون_err;
      إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  اذهب بیرون_err;
	}
      p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      بدل (p[0])
	{
	حالة 'a':
	  إذا (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  وإلا إذا (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  وإلا
	    اذهب invalid_category;
	  اكسر;

	حالة 'p':
	  إذا (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_اشاره_گر;
	  وإلا
	    اذهب invalid_category;
	  اكسر;

	حالة 's':
	  إذا (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  وإلا
	    اذهب invalid_category;
	  اكسر;

	افتراضي:
	  اذهب invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_یافت_close (parser);

  لكل (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	تعداد omp_clause_defaultmap_نوع cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	إذا (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = عدم;
	بدل (cat)
	  {
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = عدم;
	    اكسر;
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    اكسر;
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    اكسر;
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_اشاره_گر:
	    p = "pointer";
	    اكسر;
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
	إذا (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	وإلا
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	اكسر;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_مجموعه_نوع (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 بیرون_err:
  parens.skip_until_یافت_close (parser);
  أرجع list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

ساكن درخت
c_parser_omp_clause_use_device_ptr (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

ساكن درخت
c_parser_omp_clause_use_device_addr (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

ساكن درخت
c_parser_omp_clause_has_device_addr (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

ساكن درخت
c_parser_omp_clause_is_device_ptr (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

ساكن درخت
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_کد کد,
				 درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t عبارت_loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت (parser);
  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
  درخت c, t = عبارت.مقدار;
  t = c_fully_fold (t, خطأ, عدم);

  parens.skip_until_یافت_close (parser);

  إذا (t == error_mark_گره)
    أرجع list;
  وإلا إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
    {
      error_at (عبارت_loc, "%qs expression must be integral",
		omp_clause_کد_name[کد]);
      أرجع list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
		       build_int_cst (درخت_TYPE (t), 0));
  protected_مجموعه_عبارت_location (c, عبارت_loc);
  إذا (c == boolean_true_گره)
    {
      warning_at (عبارت_loc, 0,
		  "%qs value must be positive",
		  omp_clause_کد_name[کد]);
      t = integer_one_گره;
    }

  check_no_duplicate_clause (list, کد, omp_clause_کد_name[کد]);

  c = build_omp_clause (loc, کد);
  OMP_CLAUSE_عملوند (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenACC:

    gang [( gang-arg-list )]
    worker [( [num:] int-expr )]
    vector [( [length:] int-expr )]

  where gang-arg is one of:

    [num:] int-expr
    static: size-expr

  and size-expr may be:

    *
    int-expr
*/

ساكن درخت
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_کد نوع,
			    ثابت حرف *str, درخت list)
{
  ثابت حرف *id = "num";
  درخت ops[2] = { NULL_درخت, NULL_درخت }, c;

  إذا (نوع == OMP_CLAUSE_وکتور)
    id = "length";

  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      افعل
	{
	  c_token *بعدی = c_parser_peek_token (parser);
	  صحيح idx = 0;

	  /* Gang static argument.  */
	  إذا (نوع == OMP_CLAUSE_GANG
	      && c_parser_بعدی_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		اذهب cleanup_error;

	      idx = 1;
	      إذا (ops[idx] != NULL_درخت)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  اذهب cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      إذا (c_parser_بعدی_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_گره;

		  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      استمر;
		    }
		  وإلا
		    اكسر;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_اشاره_گر (بعدی->مقدار)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  إذا (ops[idx] != NULL_درخت)
	    {
	      c_parser_error (parser, "unexpected argument");
	      اذهب cleanup_error;
	    }

	  location_t عبارت_loc = c_parser_peek_token (parser)->location;
	  c_عبارت cexpr = c_parser_عبارت_no_commas (parser, عدم);
	  cexpr = convert_lvalue_مقصد_rvalue (عبارت_loc, cexpr, خطأ, درست);
	  درخت عبارت = cexpr.مقدار;
	  إذا (عبارت == error_mark_گره)
	    اذهب cleanup_error;

	  عبارت = c_fully_fold (عبارت, خطأ, عدم);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (عبارت)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      أرجع list;
	    }

	  درخت c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, عبارت,
				    build_int_cst (درخت_TYPE (عبارت), 0));
	  إذا (c == boolean_true_گره)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      عبارت = integer_one_گره;
	    }

	  ops[idx] = عبارت;

	  إذا (نوع == OMP_CLAUSE_GANG
	      && c_parser_بعدی_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  اكسر;
	}
      طالما (1);

      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	اذهب cleanup_error;
    }

  check_no_duplicate_clause (list, نوع, str);

  c = build_omp_clause (loc, نوع);

  إذا (ops[1])
    OMP_CLAUSE_عملوند (c, 1) = ops[1];

  OMP_CLAUSE_عملوند (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;

 cleanup_error:
  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, 0);
  أرجع list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

ساكن درخت
c_parser_oacc_simple_clause (location_t loc, تعداد omp_clause_کد کد,
			     درخت list)
{
  check_no_duplicate_clause (list, کد, omp_clause_کد_name[کد]);

  درخت c = build_omp_clause (loc, کد);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenACC:
   async [( int-expr )] */

ساكن درخت
c_parser_oacc_clause_async (c_parser *parser, درخت list)
{
  درخت c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_گره, GOMP_ASYNC_NOVAL);

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_عبارت_no_commas (parser, عدم).مقدار;
      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      وإلا إذا (t == error_mark_گره
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	أرجع list;
    }
  وإلا
    t = c_fully_fold (t, خطأ, عدم);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

ساكن درخت
c_parser_oacc_clause_tile (c_parser *parser, درخت list)
{
  درخت c, عبارت = error_mark_گره;
  location_t loc;
  درخت tile = NULL_درخت;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع list;

  افعل
    {
      إذا (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	أرجع list;

      إذا (c_parser_بعدی_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  عبارت = integer_zero_گره;
	}
      وإلا
	{
	  location_t عبارت_loc = c_parser_peek_token (parser)->location;
	  c_عبارت cexpr = c_parser_عبارت_no_commas (parser, عدم);
	  cexpr = convert_lvalue_مقصد_rvalue (عبارت_loc, cexpr, خطأ, درست);
	  عبارت = cexpr.مقدار;

	  إذا (عبارت == error_mark_گره)
	    {
	      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      أرجع list;
	    }

	  عبارت = c_fully_fold (عبارت, خطأ, عدم);

	  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (عبارت))
	      || !درخت_میگنجد_shwi_p (عبارت)
	      || درخت_مقصد_shwi (عبارت) <= 0)
	    {
	      error_at (عبارت_loc, "%<tile%> argument needs positive"
			" integral constant");
	      عبارت = integer_zero_گره;
	    }
	}

      tile = درخت_cons (NULL_درخت, عبارت, tile);
    }
  طالما (c_parser_بعدی_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenACC:
   wait [( int-expr-list )] */

ساكن درخت
c_parser_oacc_clause_wait (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  وإلا
    {
      درخت c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_گره, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenACC 2.7:
   self [( expression )] */

ساكن درخت
c_parser_oacc_compute_clause_self (c_parser *parser, درخت list)
{
  درخت t;
  location_t location = c_parser_peek_token (parser)->location;
  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, درست, درست);
      t = c_objc_common_truthvalue_conversion (loc, عبارت.مقدار);
      t = c_fully_fold (t, خطأ, عدم);
      parens.skip_until_یافت_close (parser);
    }
  وإلا
    t = truthvalue_true_گره;

  لكل (درخت c = list; c; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	أرجع list;
      }

  درخت c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

ساكن درخت
c_parser_omp_clause_ترتیب (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت حرف *p;
  منطقي unconstrained = خطأ;
  منطقي reproducible = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "unconstrained") == 0)
	unconstrained = درست;
      وإلا إذا (strcmp (p, "reproducible") == 0)
	reproducible = درست;
      وإلا
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  اذهب بیرون_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      اذهب بیرون_err;
    }
  p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
  إذا (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      اذهب بیرون_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_یافت_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ترتیب, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ترتیب);
  OMP_CLAUSE_ترتیب_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ترتیب_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 بیرون_err:
  parens.skip_until_یافت_close (parser);
  أرجع list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

ساكن درخت
c_parser_omp_clause_bind (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت c;
  ثابت حرف *p;
  تعداد omp_clause_bind_نوع نوع = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_یافت_close (parser);
      أرجع list;
    }
  p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
  إذا (strcmp (p, "teams") == 0)
    نوع = OMP_CLAUSE_BIND_TEAMS;
  وإلا إذا (strcmp (p, "parallel") == 0)
    نوع = OMP_CLAUSE_BIND_PARALLEL;
  وإلا إذا (strcmp (p, "thread") != 0)
    اذهب invalid;
  c_parser_consume_token (parser);
  parens.skip_until_یافت_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_نوع (c) = نوع;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

ساكن درخت
c_parser_omp_clause_ordered (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  درخت c, رقم = NULL_درخت;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      رقم = c_parser_عبارت_no_commas (parser, عدم).مقدار;
      parens.skip_until_یافت_close (parser);
    }
  إذا (رقم == error_mark_گره)
    أرجع list;
  إذا (رقم)
    {
      mark_exp_read (رقم);
      رقم = c_fully_fold (رقم, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (رقم))
	  || !درخت_میگنجد_shwi_p (رقم)
	  || (n = درخت_مقصد_shwi (رقم)) <= 0
	  || (صحيح) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  أرجع list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_عبارت (c) = رقم;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

ساكن درخت
c_parser_omp_clause_خصوصی (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_خصوصی, list);
}

/* OpenMP 2.5:
   reduction ( reduction-operator : variable-list )

   reduction-operator:
     One of: + * - & ^ | && ||

   OpenMP 3.1:

   reduction-operator:
     One of: + * - & ^ | && || max min

   OpenMP 4.0:

   reduction-operator:
     One of: + * - & ^ | && ||
     identifier

   OpenMP 5.0:
   reduction ( reduction-modifier, reduction-operator : variable-list )
   in_reduction ( reduction-operator : variable-list )
   task_reduction ( reduction-operator : variable-list )  */

ساكن درخت
c_parser_omp_clause_reduction (c_parser *parser, تعداد omp_clause_کد نوع,
			       منطقي is_omp, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي task = خطأ;
      منطقي inscan = خطأ;
      تعداد درخت_کد_2 کد = ERROR_MARK;
      درخت reduc_id = NULL_درخت;

      إذا (نوع == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  إذا (c_parser_بعدی_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ثابت حرف *p
		= IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	      إذا (strcmp (p, "task") == 0)
		task = درست;
	      وإلا إذا (strcmp (p, "inscan") == 0)
		inscan = درست;
	      إذا (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_PLUS:
	  کد = PLUS_عبارت;
	  اكسر;
	حالة CPP_MULT:
	  کد = MULT_عبارت;
	  اكسر;
	حالة CPP_MINUS:
	  إذا (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.جمع_کن_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  کد = MINUS_عبارت;
	  اكسر;
	حالة CPP_AND:
	  کد = بیت_AND_عبارت;
	  اكسر;
	حالة CPP_XOR:
	  کد = بیت_XOR_عبارت;
	  اكسر;
	حالة CPP_OR:
	  کد = بیت_IOR_عبارت;
	  اكسر;
	حالة CPP_AND_AND:
	  کد = TRUTH_ANDIF_عبارت;
	  اكسر;
	حالة CPP_OR_OR:
	  کد = TRUTH_ORIF_عبارت;
	  اكسر;
        حالة CPP_NAME:
	  {
	    ثابت حرف *p
	      = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	    إذا (strcmp (p, "min") == 0)
	      {
		کد = MIN_عبارت;
		اكسر;
	      }
	    إذا (strcmp (p, "max") == 0)
	      {
		کد = MAX_عبارت;
		اكسر;
	      }
	    reduc_id = c_parser_peek_token (parser)->مقدار;
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, 0);
	  أرجع list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (کد, reduc_id);
      إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  درخت nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, نوع, list);
	  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      درخت d = OMP_CLAUSE_DECL (c), type;
	      إذا (درخت_کد (d) != OMP_ARRAY_SECTION)
		type = درخت_TYPE (d);
	      وإلا
		{
		  صحيح cnt = 0;
		  درخت t;
		  لكل (t = d;
		      درخت_کد (t) == OMP_ARRAY_SECTION;
		      t = درخت_عملوند (t, 0))
		    cnt++;
		  type = درخت_TYPE (t);
		  طالما (cnt > 0)
		    {
		      إذا (درخت_کد (type) != اشاره_گر_TYPE
			  && درخت_کد (type) != ARRAY_TYPE)
			اكسر;
		      type = درخت_TYPE (type);
		      cnt--;
		    }
		}
	      طالما (درخت_کد (type) == ARRAY_TYPE)
		type = درخت_TYPE (type);
	      OMP_CLAUSE_REDUCTION_کد (c) = کد;
	      إذا (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      وإلا إذا (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      إذا (کد == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || درخت_کد (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_یافت_close (parser);
    }
  أرجع list;
}

/* OpenMP 2.5:
   schedule ( schedule-kind )
   schedule ( schedule-kind , expression )

   schedule-kind:
     static | dynamic | guided | runtime | auto

   OpenMP 4.5:
   schedule ( schedule-modifier : schedule-kind )
   schedule ( schedule-modifier [ , schedule-modifier ] : schedule-kind , expression )

   schedule-modifier:
     simd
     monotonic
     nonmonotonic  */

ساكن درخت
c_parser_omp_clause_زمانبندی (c_parser *parser, درخت list)
{
  درخت c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  صحيح modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  c = build_omp_clause (loc, OMP_CLAUSE_زمانبندی);

  location_t comma = UNKNOWN_LOCATION;
  طالما (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      درخت نوع = c_parser_peek_token (parser)->مقدار;
      ثابت حرف *p = IDENTIFIER_اشاره_گر (نوع);
      إذا (strcmp ("simd", p) == 0)
	OMP_CLAUSE_زمانبندی_SIMD (c) = 1;
      وإلا إذا (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_زمانبندی_MONOTONIC;
      وإلا إذا (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_زمانبندی_NONMONOTONIC;
      وإلا
	اكسر;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      إذا (nmodifiers++ == 0
	  && c_parser_بعدی_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  اكسر;
	}
    }
  إذا (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  إذا ((modifiers & (OMP_CLAUSE_زمانبندی_MONOTONIC
		    | OMP_CLAUSE_زمانبندی_NONMONOTONIC))
      == (OMP_CLAUSE_زمانبندی_MONOTONIC
	  | OMP_CLAUSE_زمانبندی_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      درخت نوع = c_parser_peek_token (parser)->مقدار;
      ثابت حرف *p = IDENTIFIER_اشاره_گر (نوع);

      بدل (p[0])
	{
	حالة 'd':
	  إذا (strcmp ("dynamic", p) != 0)
	    اذهب invalid_نوع;
	  OMP_CLAUSE_زمانبندی_نوع (c) = OMP_CLAUSE_زمانبندی_DYNAMIC;
	  اكسر;

        حالة 'g':
	  إذا (strcmp ("guided", p) != 0)
	    اذهب invalid_نوع;
	  OMP_CLAUSE_زمانبندی_نوع (c) = OMP_CLAUSE_زمانبندی_GUIDED;
	  اكسر;

	حالة 'r':
	  إذا (strcmp ("runtime", p) != 0)
	    اذهب invalid_نوع;
	  OMP_CLAUSE_زمانبندی_نوع (c) = OMP_CLAUSE_زمانبندی_RUNTIME;
	  اكسر;

	افتراضي:
	  اذهب invalid_نوع;
	}
    }
  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_زمانبندی_نوع (c) = OMP_CLAUSE_زمانبندی_STATIC;
  وإلا إذا (c_parser_بعدی_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_زمانبندی_نوع (c) = OMP_CLAUSE_زمانبندی_AUTO;
  وإلا
    اذهب invalid_نوع;

  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
    {
      location_t اینجا;
      c_parser_consume_token (parser);

      اینجا = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (اینجا, عبارت, خطأ, درست);
      t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);

      إذا (OMP_CLAUSE_زمانبندی_نوع (c) == OMP_CLAUSE_زمانبندی_RUNTIME)
	error_at (اینجا, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      وإلا إذا (OMP_CLAUSE_زمانبندی_نوع (c) == OMP_CLAUSE_زمانبندی_AUTO)
	error_at (اینجا,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      وإلا إذا (درخت_کد (درخت_TYPE (t)) == INTEGER_TYPE
	       || درخت_کد (درخت_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  درخت s = fold_build2_loc (loc, LE_عبارت, boolean_type_گره, t,
				    build_int_cst (درخت_TYPE (t), 0));
	  protected_مجموعه_عبارت_location (s, loc);
	  إذا (s == boolean_true_گره)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_گره;
	    }
	  OMP_CLAUSE_زمانبندی_CHUNK_عبارت (c) = t;
	}
      وإلا
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_یافت_close (parser);
    }
  وإلا
    c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_زمانبندی_نوع (c)
    = (تعداد omp_clause_زمانبندی_نوع)
      (OMP_CLAUSE_زمانبندی_نوع (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_زمانبندی, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_نوع:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, 0);
  أرجع list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

ساكن درخت
c_parser_omp_clause_shared (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

ساكن درخت
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_استفادهنشده, درخت list)
{
  درخت c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

ساكن درخت
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_استفادهنشده,
			    تعداد omp_clause_کد کد, درخت list)
{
  check_no_duplicate_clause (list, کد, omp_clause_کد_name[کد]);

  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, کد);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

ساكن درخت
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_استفادهنشده,
				تعداد omp_clause_کد کد, درخت list)
{
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, کد);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 4.5:
   nogroup */

ساكن درخت
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_استفادهنشده, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.5:
   simd
نخها*/

ساكن درخت
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_استفادهنشده,
				 تعداد omp_clause_کد کد, درخت list)
{
  check_no_duplicate_clause (list, کد, omp_clause_کد_name[کد]);
  درخت c = build_omp_clause (c_parser_peek_token (parser)->location, کد);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

ساكن درخت
c_parser_omp_clause_رقم_teams (c_parser *parser, درخت list)
{
  location_t رقم_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t فوقانی_loc = c_parser_peek_token (parser)->location;
      location_t پایینی_loc = UNKNOWN_LOCATION;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (فوقانی_loc, عبارت, خطأ, درست);
      درخت c, فوقانی = عبارت.مقدار, پایینی = NULL_درخت;
      فوقانی = c_fully_fold (فوقانی, خطأ, عدم);

      إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  پایینی_loc = فوقانی_loc;
	  پایینی = فوقانی;
	  فوقانی_loc = c_parser_peek_token (parser)->location;
	  عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  عبارت = convert_lvalue_مقصد_rvalue (فوقانی_loc, عبارت, خطأ, درست);
	  فوقانی = عبارت.مقدار;
	  فوقانی = c_fully_fold (فوقانی, خطأ, عدم);
	}

      parens.skip_until_یافت_close (parser);

      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (فوقانی))
	  || (پایینی && !INTEGRAL_TYPE_P (درخت_TYPE (پایینی))))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (فوقانی_loc, LE_عبارت, boolean_type_گره, فوقانی,
			   build_int_cst (درخت_TYPE (فوقانی), 0));
      protected_مجموعه_عبارت_location (c, فوقانی_loc);
      إذا (c == boolean_true_گره)
	{
	  warning_at (فوقانی_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  فوقانی = integer_one_گره;
	}
      إذا (پایینی)
	{
	  c = fold_build2_loc (پایینی_loc, LE_عبارت, boolean_type_گره, پایینی,
			       build_int_cst (درخت_TYPE (پایینی), 0));
	  protected_مجموعه_عبارت_location (c, پایینی_loc);
	  إذا (c == boolean_true_گره)
	    {
	      warning_at (پایینی_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      پایینی = NULL_درخت;
	    }
	  وإلا إذا (درخت_کد (پایینی) == INTEGER_CST
		   && درخت_کد (فوقانی) == INTEGER_CST
		   && درخت_int_cst_lt (فوقانی, پایینی))
	    {
	      warning_at (پایینی_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", پایینی, فوقانی);
	      پایینی = NULL_درخت;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_رقم_TEAMS, "num_teams");

      c = build_omp_clause (رقم_teams_loc, OMP_CLAUSE_رقم_TEAMS);
      OMP_CLAUSE_رقم_TEAMS_فوقانی_عبارت (c) = فوقانی;
      OMP_CLAUSE_رقم_TEAMS_پایینی_عبارت (c) = پایینی;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

ساكن درخت
c_parser_omp_clause_thread_حد (c_parser *parser, درخت list)
{
  location_t رقم_thread_حد_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      درخت c, t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_یافت_close (parser);

      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (عبارت_loc, LE_عبارت, boolean_type_گره, t,
			   build_int_cst (درخت_TYPE (t), 0));
      protected_مجموعه_عبارت_location (c, عبارت_loc);
      إذا (c == boolean_true_گره)
	{
	  warning_at (عبارت_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_گره;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_حد,
				 "thread_limit");

      c = build_omp_clause (رقم_thread_حد_loc, OMP_CLAUSE_THREAD_حد);
      OMP_CLAUSE_THREAD_حد_عبارت (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

ساكن درخت
c_parser_omp_clause_aligned (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      درخت alignment = عبارت.مقدار;
      alignment = c_fully_fold (alignment, خطأ, عدم);
      إذا (درخت_کد (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (درخت_TYPE (alignment))
	  || درخت_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_درخت;
	}

      لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_یافت_close (parser);
  أرجع nl;
}

/* OpenMP 5.0:
   allocate ( variable-list )
   allocate ( expression : variable-list )

   OpenMP 5.1:
   allocate ( allocator-modifier : variable-list )
   allocate ( allocator-modifier , allocator-modifier : variable-list )

   allocator-modifier:
   allocator ( expression )
   align ( expression )  */

ساكن درخت
c_parser_omp_clause_allocate (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;
  درخت allocator = NULL_درخت;
  درخت align = NULL_درخت;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا ((c_parser_بعدی_token_is_not (parser, CPP_NAME)
       && c_parser_بعدی_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      منطقي has_modifiers = خطأ;
      درخت orig_type = NULL_درخت;
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  بیعلامت صحيح n = 3;
	  ثابت حرف *p
	    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	  إذا ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = درست;
	      وإلا إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ثابت حرف *q = IDENTIFIER_اشاره_گر (tok->مقدار);
		  n += 4;
		  إذا ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_متوازن_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = درست;
		}
	    }
	  إذا (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t عبارت_loc = c_parser_peek_token (parser)->location;
	      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
	      إذا (عبارت.مقدار == error_mark_گره)
		;
	      وإلا إذا (strcmp (p, "allocator") == 0)
		{
		  allocator = عبارت.مقدار;
		  allocator = c_fully_fold (allocator, خطأ, عدم);
		  orig_type = عبارت.original_type
			      ? عبارت.original_type : درخت_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      وإلا
		{
		  align = عبارت.مقدار;
		  align = c_fully_fold (align, خطأ, عدم);
		}
	      parens2.skip_until_یافت_close (parser);
	      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ثابت حرف *q = "";
		  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_اشاره_گر (tok->مقدار);
		  إذا (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_یافت_close (parser);
		      أرجع list;
		    }
		  وإلا إذا (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_یافت_close (parser);
		      أرجع list;
		    }
		  c_parser_consume_token (parser);
		  إذا (!parens2.require_open (parser))
		    {
		      parens.skip_until_یافت_close (parser);
		      أرجع list;
		    }
		  عبارت_loc = c_parser_peek_token (parser)->location;
		  عبارت = c_parser_عبارت_no_commas (parser, عدم);
		  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ,
						   درست);
		  إذا (strcmp (q, "allocator") == 0)
		    {
		      allocator = عبارت.مقدار;
		      allocator = c_fully_fold (allocator, خطأ, عدم);
		      orig_type = عبارت.original_type
				  ? عبارت.original_type : درخت_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  وإلا
		    {
		      align = عبارت.مقدار;
		      align = c_fully_fold (align, خطأ, عدم);
		    }
		  parens2.skip_until_یافت_close (parser);
		}
	    }
	}
      إذا (!has_modifiers)
	{
	  location_t عبارت_loc = c_parser_peek_token (parser)->location;
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
	  إذا (عبارت.مقدار != error_mark_گره)
	    {
	      allocator = عبارت.مقدار;
	      allocator = c_fully_fold (allocator, خطأ, عدم);
	      orig_type = عبارت.original_type
			  ? عبارت.original_type : درخت_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      إذا (allocator
	  && (!INTEGRAL_TYPE_P (درخت_TYPE (allocator))
	      || درخت_کد (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				درخت_TYPE (allocator));
          allocator = NULL_درخت;
        }
      إذا (align
	  && (!INTEGRAL_TYPE_P (درخت_TYPE (align))
	      || !درخت_میگنجد_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_درخت;
	}
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_یافت_close (parser);
	  أرجع list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  إذا (allocator || align)
    لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_یافت_close (parser);
  أرجع nl;
}

/* OpenMP 5.0:
   uses_allocators ( allocator-list )

   allocator-list:
   allocator
   allocator , allocator-list
   allocator ( traits-array )
   allocator ( traits-array ) , allocator-list

   Deprecated in 5.2, removed in 6.0: 'allocator(trait-array)' syntax.

   OpenMP 5.2:

   uses_allocators ( modifier : allocator-list )
   uses_allocators ( modifier , modifier : allocator-list )

   OpenMP 6.0:
   uses_allocators ( [modifier-list :] allocator-list [; ...] )

   modifier:
   traits ( traits-array )
   memspace ( mem-space-handle )  */

ساكن درخت
c_parser_omp_clause_استفاده_میکند_allocators (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl = list;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

parse_بعدی:

  منطقي has_modifiers = خطأ;
  منطقي دیده_allocators = خطأ;
  درخت memspace_عبارت = NULL_درخت;
  درخت traits_var = NULL_درخت;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      بیعلامت صحيح n = 3;
      ثابت حرف *p
	= IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = درست;
	  وإلا إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ثابت حرف *q = IDENTIFIER_اشاره_گر (tok->مقدار);
	      n += 4;
	      إذا ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_متوازن_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = درست;
		  إذا ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ثابت حرف *m = IDENTIFIER_اشاره_گر (tok->مقدار);
		      إذا (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  اذهب انتها;
			}
		    }
		}
	    }
	}
      إذا (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  إذا (عبارت.مقدار == error_mark_گره)
	    ;
	  وإلا إذا (strcmp (p, "traits") == 0)
	    {
	      traits_var = عبارت.مقدار;
	      traits_var = c_fully_fold (traits_var, خطأ, عدم);
	      mark_exp_read (traits_var);
	    }
	  وإلا
	    {
	      memspace_عبارت = عبارت.مقدار;
	      memspace_عبارت = c_fully_fold (memspace_عبارت, خطأ, عدم);
	    }
	  parens2.skip_until_یافت_close (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت حرف *q = "";
	      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		q = IDENTIFIER_اشاره_گر (tok->مقدار);
	      إذا (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_یافت_close (parser);
		  أرجع list;
		}
	      وإلا إذا (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_یافت_close (parser);
		  أرجع list;
		}
	      c_parser_consume_token (parser);
	      إذا (!parens2.require_open (parser))
		{
		  parens.skip_until_یافت_close (parser);
		  أرجع list;
		}
	      عبارت = c_parser_عبارت_no_commas (parser, عدم);
	      إذا (strcmp (q, "traits") == 0)
		{
		  traits_var = عبارت.مقدار;
		  traits_var = c_fully_fold (traits_var, خطأ, عدم);
		  mark_exp_read (traits_var);
		}
	      وإلا
		{
		  memspace_عبارت = عبارت.مقدار;
		  memspace_عبارت = c_fully_fold (memspace_عبارت, خطأ, عدم);
		}
	      parens2.skip_until_یافت_close (parser);
	    }
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    اذهب انتها;
	}
    }

  طالما (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *tok_s = IDENTIFIER_اشاره_گر (tok->مقدار);
      درخت t = lookup_name (tok->مقدار);
      إذا (t == NULL_درخت)
	{
	  undeclared_variable (tok->location, tok->مقدار);
	  t = error_mark_گره;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      درخت legacy_traits = NULL_درخت;
      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ثابت حرف *tok_a
	    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_یافت_close (parser);

	  إذا (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      اذهب انتها;
	    }
	  legacy_traits = c_fully_fold (عبارت.مقدار, خطأ, عدم);
	  إذا (legacy_traits == error_mark_گره)
	    اذهب انتها;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  إذا (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.جمع_کن_fixit_replace (alloc_loc, "traits");
	      richloc.جمع_کن_fixit_درج_after (close_loc, ": ");
	      richloc.جمع_کن_fixit_درج_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      إذا (دیده_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  اذهب انتها;
	}
      دیده_allocators = درست;

      درخت c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_استفاده_میکند_ALLOCATORS);
      OMP_CLAUSE_استفاده_میکند_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_استفاده_میکند_ALLOCATORS_MEMSPACE (c) = memspace_عبارت;
      OMP_CLAUSE_استفاده_میکند_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }

  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      اذهب parse_بعدی;
    }

 انتها:
  parens.skip_until_یافت_close (parser);
  أرجع nl;
}

/* OpenMP 4.0:
   linear ( variable-list )
   linear ( variable-list : expression )

   OpenMP 4.5:
   linear ( modifier ( variable-list ) )
   linear ( modifier ( variable-list ) : expression )

   modifier:
     val

   OpenMP 5.2:
   linear ( variable-list : modifiers-list )

   modifiers:
     val
     step ( expression )  */

ساكن درخت
c_parser_omp_clause_خطی (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  درخت nl, c, گام;
  تعداد omp_clause_خطی_نوع نوع = OMP_CLAUSE_خطی_DEFAULT;
  منطقي old_خطی_modifier = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *p = IDENTIFIER_اشاره_گر (tok->مقدار);
      إذا (strcmp ("val", p) == 0)
	نوع = OMP_CLAUSE_خطی_VAL;
      إذا (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	نوع = OMP_CLAUSE_خطی_DEFAULT;
      إذا (نوع != OMP_CLAUSE_خطی_DEFAULT)
	{
	  old_خطی_modifier = درست;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_خطی, list);

  إذا (نوع != OMP_CLAUSE_خطی_DEFAULT)
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_یافت_close (parser);
    }

  إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = عبارت_loc;
      منطقي has_modifiers = خطأ;
      إذا (نوع == OMP_CLAUSE_خطی_DEFAULT
	  && c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ثابت حرف *p = IDENTIFIER_اشاره_گر (tok->مقدار);
	  بیعلامت صحيح pos = 0;
	  إذا (strcmp ("val", p) == 0)
	    pos = 2;
	  وإلا إذا (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      إذا (c_parser_check_متوازن_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      وإلا
		pos = 0;
	    }
	  إذا (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      إذا (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = درست;
	    }
	}
      إذا (has_modifiers)
	{
	  گام = NULL_درخت;
	  طالما (c_parser_بعدی_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت حرف *p = IDENTIFIER_اشاره_گر (tok->مقدار);
	      إذا (strcmp ("val", p) == 0)
		{
		  إذا (نوع != OMP_CLAUSE_خطی_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  نوع = OMP_CLAUSE_خطی_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      وإلا إذا (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  إذا (parens2.require_open (parser))
		    {
		      إذا (گام)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      عبارت_loc = c_parser_peek_token (parser)->location;
		      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
		      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ,
						       درست);
		      گام = c_fully_fold (عبارت.مقدار, خطأ, عدم);
		      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (گام)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  گام = integer_one_گره;
			}
		      parens2.skip_until_یافت_close (parser);
		    }
		  وإلا
		    اكسر;
		}
	      وإلا
		اكسر;
	      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  استمر;
		}
	      اكسر;
	    }
	  إذا (!گام)
	    گام = integer_one_گره;
	}
      وإلا
	{
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
	  گام = c_fully_fold (عبارت.مقدار, خطأ, عدم);
	  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (گام)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      گام = integer_one_گره;
	    }
	}

    }
  وإلا
    گام = integer_one_گره;

  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_خطی_گام (c) = گام;
      OMP_CLAUSE_خطی_نوع (c) = نوع;
      OMP_CLAUSE_خطی_OLD_خطی_MODIFIER (c) = old_خطی_modifier;
    }

  إذا (old_خطی_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      إذا (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.جمع_کن_fixit_remove (rm1_loc);
	  إذا (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.جمع_کن_fixit_remove (rm2_loc);
	      richloc.جمع_کن_fixit_درج_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.جمع_کن_fixit_درج_before (close_loc, ")");
	    }
	  وإلا
	    richloc.جمع_کن_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_یافت_close (parser);
  أرجع nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

ساكن درخت
c_parser_omp_clause_nontemporal (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

ساكن درخت
c_parser_omp_clause_safelen (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت c, t;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t عبارت_loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
  t = عبارت.مقدار;
  t = c_fully_fold (t, خطأ, عدم);
  إذا (درخت_کد (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (درخت_TYPE (t))
      || درخت_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_درخت;
    }

  parens.skip_until_یافت_close (parser);
  إذا (t == NULL_درخت || t == error_mark_گره)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

ساكن درخت
c_parser_omp_clause_simdlen (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت c, t = NULL_درخت, type = NULL_درخت, مقسوم_علیه = NULL_درخت;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  بیعلامت pos = 3;
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار),
		 "scaled") == 0
      && c_parser_check_متوازن_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      بنية c_type_name *ctype = c_parser_type_name (parser);
      إذا (ctype == عدم
	  || (type = groktypename (ctype, عدم, عدم)) == عدم
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && درخت_کد (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_گره;
	}
      وإلا إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, خطأ, درست);
	  مقسوم_علیه = عبارت.مقدار;
	  مقسوم_علیه = c_fully_fold (مقسوم_علیه, خطأ, عدم);
	  إذا (درخت_کد (مقسوم_علیه) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (درخت_TYPE (مقسوم_علیه))
	      || درخت_int_cst_sgn (مقسوم_علیه) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_گره;
	    }
	}
      parens2.skip_until_یافت_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  إذا (type != error_mark_گره)
    {
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (درخت_کد (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (درخت_TYPE (t))
	  || درخت_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_درخت;
	}
    }

  parens.skip_until_یافت_close (parser);
  إذا (type == error_mark_گره || t == NULL_درخت || t == error_mark_گره)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_عبارت (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_مقسوم_علیه (c) = مقسوم_علیه;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

ساكن درخت
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   درخت list, منطقي depend_p)
{
  درخت vec = عدم;
  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_نوع != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      أرجع list;
    }

  إذا (!depend_p)
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_عدد
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  درخت val = c_parser_peek_nth_token (parser, 3)->مقدار;
	  إذا (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_نوع (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      أرجع u;
	    }
	}
    }



  طالما (c_parser_بعدی_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_نوع == C_ID_ID)
    {
      درخت t = lookup_name (c_parser_peek_token (parser)->مقدار);
      درخت addend = عدم;

      إذا (t == NULL_درخت)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->مقدار);
	  t = error_mark_گره;
	}

      c_parser_consume_token (parser);

      منطقي neg = خطأ;
      إذا (c_parser_بعدی_token_is (parser, CPP_MINUS))
	neg = درست;
      وإلا إذا (!c_parser_بعدی_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_گره;
	  neg = خطأ;
	  اذهب جمع_کن_مقصد_وکتور;
	}
      c_parser_consume_token (parser);

      إذا (c_parser_بعدی_token_is_not (parser, CPP_عدد))
	{
	  c_parser_error (parser, "expected integer");
	  أرجع list;
	}

      addend = c_parser_peek_token (parser)->مقدار;
      إذا (درخت_کد (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  أرجع list;
	}
      c_parser_consume_token (parser);

    جمع_کن_مقصد_وکتور:
      إذا (t != error_mark_گره)
	{
	  vec = درخت_cons (addend, t, vec);
	  إذا (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      إذا (c_parser_بعدی_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_نوع != C_ID_ID)
	اكسر;

      c_parser_consume_token (parser);
    }

  إذا (vec == NULL_درخت)
    أرجع list;

  درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_نوع (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  أرجع u;
}

/* OpenMP 5.0:
   iterators ( iterators-definition )

   iterators-definition:
     iterator-specifier
     iterator-specifier , iterators-definition

   iterator-specifier:
     identifier = range-specification
     iterator-type identifier = range-specification

   range-specification:
     begin : end
     begin : end : step  */

ساكن درخت
c_parser_omp_iterators (c_parser *parser)
{
  درخت ret = NULL_درخت, *آخرین = &ret;
  c_parser_consume_token (parser);

  افزودن_scope ();

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_گره;

  افعل
    {
      درخت iter_type = NULL_درخت, type_عبارت = NULL_درخت;
      إذا (c_parser_بعدی_نشانهها_شروع_typename (parser, cla_prefer_id))
	{
	  بنية c_type_name *type = c_parser_type_name (parser);
	  إذا (type != عدم)
	    iter_type = groktypename (type, &type_عبارت, عدم);
	}
      إذا (iter_type == NULL_درخت)
	iter_type = integer_type_گره;

      location_t loc = c_parser_peek_token (parser)->location;
      إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}

      درخت id = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);

      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اكسر;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (eloc, عبارت, درست, خطأ);
      درخت begin = عبارت.مقدار;

      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	اكسر;

      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (eloc, عبارت, درست, خطأ);
      درخت انتها = عبارت.مقدار;

      درخت گام = integer_one_گره;
      إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  عبارت = c_parser_عبارت_no_commas (parser, عدم);
	  عبارت = convert_lvalue_مقصد_rvalue (eloc, عبارت, درست, خطأ);
	  گام = عبارت.مقدار;
	}

      درخت iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *آخرین = make_omp_iterator ();
      OMP_ITERATOR_VAR (*آخرین) = iter_var;
      OMP_ITERATOR_BEGIN (*آخرین) = begin;
      OMP_ITERATOR_انتها (*آخرین) = انتها;
      OMP_ITERATOR_گام (*آخرین) = گام;
      آخرین = &درخت_CHAIN (*آخرین);

      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      اكسر;
    }
  طالما (1);

  parens.skip_until_یافت_close (parser);
  أرجع ret ? ret : error_mark_گره;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

ساكن درخت
c_parser_omp_clause_affinity (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, iterators = NULL_درخت;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      منطقي parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      إذا (parse_iter)
	{
	  بیعلامت n = 3;
	  parse_iter = (c_parser_check_متوازن_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      إذا (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      إذا (iterators)
		برداشت_scope ();
	      parens.skip_until_یافت_close (parser);
	      أرجع list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  إذا (iterators)
    {
      درخت بلوک = برداشت_scope ();
      إذا (iterators != error_mark_گره)
	{
	  OMP_ITERATOR_بلوک (iterators) = بلوک;
	  لكل (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_درخت_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_یافت_close (parser);
  أرجع nl;
}


/* OpenMP 4.0:
   depend ( depend-kind: variable-list )

   depend-kind:
     in | out | inout

   OpenMP 4.5:
   depend ( source )

   depend ( sink  : vec )

   OpenMP 5.0:
   depend ( depend-modifier , depend-kind: variable-list )

   depend-kind:
     in | out | inout | mutexinoutset | depobj | inoutset

   depend-modifier:
     iterator ( iterators-definition )  */

ساكن درخت
c_parser_omp_clause_depend (c_parser *parser, درخت list, location_t اینجا)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_depend_نوع نوع = OMP_CLAUSE_DEPEND_آخرین;
  تعداد omp_clause_doacross_نوع dkind = OMP_CLAUSE_DOACROSS_آخرین;
  درخت nl, c, iterators = NULL_درخت;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  افعل
    {
      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
	اذهب invalid_نوع;

      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp ("iterator", p) == 0 && iterators == NULL_درخت)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  استمر;
	}
      إذا (strcmp ("in", p) == 0)
	نوع = OMP_CLAUSE_DEPEND_درون;
      وإلا إذا (strcmp ("inout", p) == 0)
	نوع = OMP_CLAUSE_DEPEND_INOUT;
      وإلا إذا (strcmp ("inoutset", p) == 0)
	نوع = OMP_CLAUSE_DEPEND_INOUTSET;
      وإلا إذا (strcmp ("mutexinoutset", p) == 0)
	نوع = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      وإلا إذا (strcmp ("out", p) == 0)
	نوع = OMP_CLAUSE_DEPEND_بیرون;
      وإلا إذا (strcmp ("depobj", p) == 0)
	نوع = OMP_CLAUSE_DEPEND_DEPOBJ;
      وإلا إذا (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جمع_کن_fixit_replace (اینجا, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      وإلا إذا (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جمع_کن_fixit_replace (اینجا, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_منبع;
	}
      وإلا
	اذهب invalid_نوع;
      اكسر;
    }
  طالما (1);

  c_parser_consume_token (parser);

  إذا (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_منبع
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      برداشت_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_منبع ? "source" : "sink");
      iterators = NULL_درخت;
    }

  إذا (dkind == OMP_CLAUSE_DOACROSS_منبع)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_نوع (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_درخت;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_یافت_close (parser);
      أرجع c;
    }

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب resync_fail;

  إذا (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, درست);
  وإلا
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      إذا (iterators)
	{
	  درخت بلوک = برداشت_scope ();
	  إذا (iterators == error_mark_گره)
	    iterators = NULL_درخت;
	  وإلا
	    OMP_ITERATOR_بلوک (iterators) = بلوک;
	}

      لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_نوع (c) = نوع;
	  إذا (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_درخت_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_یافت_close (parser);
  أرجع nl;

 invalid_نوع:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_یافت_close (parser);
  إذا (iterators)
    برداشت_scope ();
  أرجع list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

ساكن درخت
c_parser_omp_clause_doacross (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_doacross_نوع نوع = OMP_CLAUSE_DOACROSS_آخرین;
  درخت nl;
  ثابت حرف *p;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME))
    اذهب invalid_نوع;

  p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
  إذا (strcmp ("sink", p) == 0)
    نوع = OMP_CLAUSE_DOACROSS_SINK;
  وإلا إذا (strcmp ("source", p) == 0)
    نوع = OMP_CLAUSE_DOACROSS_منبع;
  وإلا
    اذهب invalid_نوع;

  c_parser_consume_token (parser);

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب resync_fail;

  إذا (نوع == OMP_CLAUSE_DOACROSS_منبع)
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_نوع (nl) = OMP_CLAUSE_DOACROSS_منبع;
      OMP_CLAUSE_DECL (nl) = NULL_درخت;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  وإلا
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, خطأ);

  parens.skip_until_یافت_close (parser);
  أرجع nl;

 invalid_نوع:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_یافت_close (parser);
  أرجع list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

ساكن درخت
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  تعداد omp_clause_fallback_نوع نوع = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  بیعلامت n = 3;
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  أرجع list;
	}
      c_parser_consume_token (parser);
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	أرجع list;
      p = "";
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "abort") == 0)
	نوع = OMP_CLAUSE_FALLBACK_ABORT;
      وإلا إذا (strcmp (p, "default_mem") == 0)
	نوع = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      وإلا إذا (strcmp (p, "null") == 0)
	نوع = OMP_CLAUSE_FALLBACK_NULL;
      وإلا
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  أرجع list;
	}
      c_parser_consume_token (parser);
      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	أرجع list;
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	أرجع list;
    }
  location_t عبارت_loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
  درخت اندازه = c_fully_fold (عبارت.مقدار, خطأ, عدم);
  parens.skip_until_یافت_close (parser);

  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (اندازه)))
    {
      error_at (عبارت_loc, "expected integer expression");
      أرجع list;
    }

  /* Attempt to statically determine when the number is negative.  */
  درخت c = fold_build2_loc (عبارت_loc, LT_عبارت, boolean_type_گره, اندازه,
			    build_int_cst (درخت_TYPE (اندازه), 0));
  protected_مجموعه_عبارت_location (c, عبارت_loc);
  إذا (c == boolean_true_گره)
    {
      warning_at (عبارت_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      اندازه = integer_zero_گره;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_نوع (c) = نوع;
  OMP_CLAUSE_DYN_GROUPPRIVATE_عبارت (c) = اندازه;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenMP 4.0:
   map ( map-kind: variable-list )
   map ( variable-list )

   map-kind:
     alloc | to | from | tofrom

   OpenMP 4.5:
   map-kind:
     alloc | to | from | tofrom | release | delete

   map ( always [,] map-kind: variable-list )

   OpenMP 5.0:
   map ( [map-type-modifier[,] ...] map-kind: variable-list )

   map-type-modifier:
     always | close | present | iterator (iterators-definition)  */

ساكن درخت
c_parser_omp_clause_map (c_parser *parser, درخت list, منطقي declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  درخت nl, c;
  تعداد gomp_map_نوع نوع = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  صحيح pos = 1;
  صحيح map_نوع_pos = 0;
  صحيح iterator_درازی = 0;
  لكل (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      إذا (tok->type != CPP_NAME)
	اكسر;

      ثابت حرف *p = IDENTIFIER_اشاره_گر (tok->مقدار);
      c_token *بعدی_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      إذا (strcmp (p, "iterator") == 0 && بعدی_tok->type == CPP_OPEN_PAREN)
	{
	  بیعلامت n = pos + 2;
	  إذا (c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_درازی = n - pos + 1;
	      pos = n;
	      بعدی_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      إذا (بعدی_tok->type == CPP_COLON)
	{
	  map_نوع_pos = pos;
	  اكسر;
	}

      إذا (بعدی_tok->type == CPP_COMMA)
	pos++;
      وإلا إذا (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  بیعلامت صحيح npos = pos + 2;
	  إذا (c_parser_check_متوازن_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  صحيح always_modifier = 0;
  صحيح close_modifier = 0;
  صحيح present_modifier = 0;
  صحيح mapper_modifier = 0;
  صحيح رقم_commas = 0;
  صحيح رقم_identifiers = 0;
  درخت mapper_name = NULL_درخت;
  درخت iterators = NULL_درخت;
  لكل (صحيح pos = 1; pos < map_نوع_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      إذا (tok->type == CPP_COMMA)
	{
	  ++رقم_commas;
	  إذا (رقم_commas > رقم_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  استمر;
	}

      ثابت حرف *p = IDENTIFIER_اشاره_گر (tok->مقدار);
      إذا (strcmp ("always", p) == 0)
	{
	  إذا (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_یافت_close (parser);
	      أرجع list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("close", p) == 0)
	{
	  إذا (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_یافت_close (parser);
	      أرجع list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("iterator", p) == 0)
	{
	  إذا (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_یافت_close (parser);
	      أرجع list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_درازی - 1;
	}
      وإلا إذا (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  إذا (mparens.require_open (parser))
	    {
	      إذا (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_یافت_close (parser);
		  أرجع list;
		}

	      tok = c_parser_peek_token (parser);

	      بدل (tok->type)
		{
		حالة CPP_NAME:
		  {
		    mapper_name = tok->مقدار;
		    c_parser_consume_token (parser);
		    إذا (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  اكسر;

		حالة CPP_KEYWORD:
		  إذا (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      اكسر;
		    }
		  /* Fallthrough.  */

		افتراضي:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  أرجع list;
		}

	      إذا (!mparens.require_close (parser))
		{
		  parens.skip_until_یافت_close (parser);
		  أرجع list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      وإلا إذا (strcmp ("present", p) == 0)
	{
	  إذا (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_یافت_close (parser);
	      أرجع list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_یافت_close (parser);
	  أرجع list;
	}
      ++رقم_identifiers;
      إذا (رقم_identifiers - 1 > رقم_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جمع_کن_fixit_درج_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      رقم_commas = رقم_identifiers - 1;
    }

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      صحيح always_present_modifier = always_modifier && present_modifier;

      إذا (strcmp ("alloc", p) == 0)
	نوع = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      وإلا إذا (strcmp ("to", p) == 0)
	نوع = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_مقصد
		: present_modifier ? GOMP_MAP_PRESENT_مقصد
		: always_modifier ? GOMP_MAP_ALWAYS_مقصد
		: GOMP_MAP_مقصد);
      وإلا إذا (strcmp ("from", p) == 0)
	نوع = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      وإلا إذا (strcmp ("tofrom", p) == 0)
	نوع = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      وإلا إذا (strcmp ("release", p) == 0)
	نوع = GOMP_MAP_RELEASE;
      وإلا إذا (strcmp ("delete", p) == 0)
	نوع = GOMP_MAP_DELETE;
      وإلا
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   درست);

  درخت آخرین_new = NULL_درخت;

  إذا (iterators)
    {
      درخت بلوک = برداشت_scope ();
      إذا (iterators == error_mark_گره)
	iterators = NULL_درخت;
      وإلا
	OMP_ITERATOR_بلوک (iterators) = بلوک;
    }

  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_مجموعه_MAP_نوع (c, نوع);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      آخرین_new = c;
    }

  إذا (mapper_name)
    {
      درخت name = build_omp_clause (درون_داد_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_مجموعه_MAP_نوع (name, GOMP_MAP_افزودن_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (آخرین_new);

      name = build_omp_clause (درون_داد_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_مجموعه_MAP_نوع (name, GOMP_MAP_برداشت_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_اشاره_گر_گره;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (آخرین_new);
      OMP_CLAUSE_CHAIN (آخرین_new) = name;
    }

  parens.skip_until_یافت_close (parser);
  أرجع nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

ساكن درخت
c_parser_omp_clause_device (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t عبارت_loc;
  c_عبارت عبارت;
  درخت c, t;
  منطقي ancestor = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *p = IDENTIFIER_اشاره_گر (tok->مقدار);
      إذا (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  إذا ((omp_requires_ماسک & OMP_REQUIRES_معکوس_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_یافت_close (parser);
	      أرجع list;
	    }
	  ancestor = درست;
	}
      وإلا إذا (strcmp ("device_num", p) == 0)
	;
      وإلا
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_یافت_close (parser);
	  أرجع list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  عبارت_loc = c_parser_peek_token (parser)->location;
  عبارت = c_parser_عبارت_no_commas (parser, عدم);
  عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
  t = عبارت.مقدار;
  t = c_fully_fold (t, خطأ, عدم);

  parens.skip_until_یافت_close (parser);

  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      أرجع list;
    }
  إذا (ancestor && درخت_کد (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (عبارت_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      أرجع list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  أرجع list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

ساكن درخت
c_parser_omp_clause_dist_زمانبندی (c_parser *parser, درخت list)
{
  درخت c, t = NULL_درخت;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (!c_parser_بعدی_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع list;
    }

  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      t = عبارت.مقدار;
      t = c_fully_fold (t, خطأ, عدم);
      parens.skip_until_یافت_close (parser);
    }
  وإلا
    c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  إذا (omp_پیدا_کن_clause (list, OMP_CLAUSE_DIST_زمانبندی))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  إذا (t == error_mark_گره)
    أرجع list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_زمانبندی);
  OMP_CLAUSE_DIST_زمانبندی_CHUNK_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

ساكن درخت
c_parser_omp_clause_proc_bind (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_proc_bind_نوع نوع;
  درخت c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp ("primary", p) == 0)
	نوع = OMP_CLAUSE_PROC_BIND_PRIMARY;
      وإلا إذا (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جمع_کن_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  نوع = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      وإلا إذا (strcmp ("close", p) == 0)
	نوع = OMP_CLAUSE_PROC_BIND_CLOSE;
      وإلا إذا (strcmp ("spread", p) == 0)
	نوع = OMP_CLAUSE_PROC_BIND_پراکندگی;
      وإلا
	اذهب invalid_نوع;
    }
  وإلا
    اذهب invalid_نوع;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_یافت_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_نوع (c) = نوع;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_نوع:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_یافت_close (parser);
  أرجع list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

ساكن درخت
c_parser_omp_clause_device_type (c_parser *parser, درخت list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_device_type_نوع نوع;
  درخت c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp ("host", p) == 0)
	نوع = OMP_CLAUSE_DEVICE_TYPE_HOST;
      وإلا إذا (strcmp ("nohost", p) == 0)
	نوع = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      وإلا إذا (strcmp ("any", p) == 0)
	نوع = OMP_CLAUSE_DEVICE_TYPE_ANY;
      وإلا
	اذهب invalid_نوع;
    }
  وإلا
    اذهب invalid_نوع;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_یافت_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_نوع (c) = نوع;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_نوع:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_یافت_close (parser);
  أرجع list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

ساكن درخت
c_parser_omp_clause_from_مقصد (c_parser *parser, تعداد omp_clause_کد نوع,
			     درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  صحيح pos = 1, colon_pos = 0;
  صحيح iterator_درازی = 0;

  طالما (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ثابت حرف *identifier =
	IDENTIFIER_اشاره_گر (c_parser_peek_nth_token_raw (parser, pos)->مقدار);
      إذا (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  بیعلامت صحيح npos = pos + 2;
	  إذا (c_parser_check_متوازن_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      إذا (strcmp (identifier, "iterator") == 0)
		iterator_درازی = npos - pos + 1;
	      pos = npos;
	    }
	}
      إذا (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      وإلا
	pos++;
      إذا (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  اكسر;
	}
    }

  منطقي present = خطأ, mapper_modifier = خطأ;
  درخت iterators = NULL_درخت;
  درخت mapper_name = NULL_درخت;

  لكل (صحيح pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      ثابت حرف *p = IDENTIFIER_اشاره_گر (token->مقدار);
      إذا (strcmp ("present", p) == 0)
	{
	  إذا (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_یافت_close (parser);
	      أرجع list;
	    }
	  present = درست;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("iterator", p) == 0)
	{
	  إذا (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_یافت_close (parser);
	      أرجع list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_درازی - 1;
	}
      وإلا إذا (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  إذا (mparens.require_open (parser))
	    {
	      إذا (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_یافت_close (parser);
		  أرجع list;
		}

	      token = c_parser_peek_token (parser);
	      بدل (token->type)
		{
		حالة CPP_NAME:
		  {
		    mapper_name = token->مقدار;
		    c_parser_consume_token (parser);
		  }
		  اكسر;
		حالة CPP_KEYWORD:
		  إذا (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      اكسر;
		    }
		  /* FALLTHROUGH  */
		افتراضي:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  أرجع list;
		}
	      إذا (!mparens.require_close (parser))
		{
		  parens.skip_until_یافت_close (parser);
		  أرجع list;
		}
	      mapper_modifier = درست;
	      pos += 3;
	    }
	}
      وإلا
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    نوع == OMP_CLAUSE_مقصد ? "to" : "from");
	  parens.skip_until_یافت_close (parser);
	  أرجع list;
	}
    }

  إذا (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  درخت nl = c_parser_omp_variable_list (parser, loc, نوع, list);
  parens.skip_until_یافت_close (parser);

  إذا (present)
    لكل (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  إذا (iterators)
    {
      درخت بلوک = برداشت_scope ();
      إذا (iterators == error_mark_گره)
	iterators = NULL_درخت;
      وإلا
	OMP_ITERATOR_بلوک (iterators) = بلوک;
    }

  إذا (iterators)
    لكل (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  إذا (mapper_name)
    {
      درخت آخرین_new = NULL_درخت;
      لكل (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	آخرین_new = c;

      درخت name = build_omp_clause (درون_داد_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_مجموعه_MAP_نوع (name, GOMP_MAP_افزودن_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (آخرین_new);

      name = build_omp_clause (درون_داد_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_مجموعه_MAP_نوع (name, GOMP_MAP_برداشت_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_اشاره_گر_گره;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (آخرین_new);
      OMP_CLAUSE_CHAIN (آخرین_new) = name;
    }

  أرجع nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

ساكن درخت
c_parser_omp_clause_یکنواخت (c_parser *parser, درخت list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_یکنواخت,
					 list);
      parens.skip_until_یافت_close (parser);
    }
  أرجع list;
}

/* OpenMP 5.1
پر*/

ساكن درخت
c_parser_omp_clause_پر (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_پر, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  درخت c = build_omp_clause (loc, OMP_CLAUSE_پر);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

ساكن درخت
c_parser_omp_clause_partial (c_parser *parser, درخت list)
{
  درخت رقم = NULL_درخت;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      رقم = c_parser_عبارت_no_commas (parser, عدم).مقدار;
      parens.skip_until_یافت_close (parser);

      إذا (رقم == error_mark_گره)
	أرجع list;

      mark_exp_read (رقم);
      رقم = c_fully_fold (رقم, خطأ, عدم);
      HOST_WIDE_INT n;
      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (رقم))
	  || !درخت_میگنجد_shwi_p (رقم)
	  || (n = درخت_مقصد_shwi (رقم)) <= 0
	  || (صحيح) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  أرجع list;
	}
    }

  درخت c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_عبارت (c) = رقم;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

ساكن درخت
c_parser_omp_clause_novariants (c_parser *parser, درخت list)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
  درخت t = convert_lvalue_مقصد_rvalue (loc, عبارت, درست, درست).مقدار;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_یافت_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  درخت c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

ساكن درخت
c_parser_omp_clause_nocontext (c_parser *parser, درخت list)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
  درخت t = convert_lvalue_مقصد_rvalue (loc, عبارت, درست, درست).مقدار;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_یافت_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  درخت c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_عبارت (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

ساكن درخت
c_parser_omp_clause_detach (c_parser *parser, درخت list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_نوع != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_یافت_close (parser);
      أرجع list;
    }

  درخت t = lookup_name (c_parser_peek_token (parser)->مقدار);
  إذا (t == NULL_درخت)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->مقدار);
      parens.skip_until_یافت_close (parser);
      أرجع list;
    }
  c_parser_consume_token (parser);

  درخت type = TYPE_MAIN_VARIANT (درخت_TYPE (t));
  إذا (!INTEGRAL_TYPE_P (type)
      || درخت_کد (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_یافت_close (parser);
      أرجع list;
    }

  درخت u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_یافت_close (parser);
  أرجع u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

ساكن درخت
c_parser_omp_clause_destroy (c_parser *parser, درخت list)
{
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  لكل (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    درخت_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  أرجع nl;
}

/* OpenMP 5.1:
     prefer_type ( const-int-expr-or-string-literal-list )

   OpenMP 6.0:
     prefer_type ( { preference-selector-list }, { ... } )

   with preference-selector being:
     fr ( identifier-or-string-literal-list )
     attr ( string-list )

   Data format:
    For the foreign runtime identifiers, string values are converted to
    their integer value; unknown string or integer values are set to
    GOMP_INTEROP_IFR_KNOWN.

    Each item (a) GOMP_INTEROP_IFR_SEPARATOR
	      (b) for any 'fr', its integer value.
		  Note: Spec only permits 1 'fr' entry (6.0; changed after TR13)
	      (c) GOMP_INTEROP_IFR_SEPARATOR
	      (d) list of \0-terminated non-empty strings for 'attr'
	      (e) '\0'
    Tailing '\0'.  */

ساكن درخت
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع error_mark_گره;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  إذا (!c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    طالما (درست)
      {
	str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
	إذا (c_parser_بعدی_token_is (parser, CPP_STRING))
	  {
	    c_عبارت cval = c_parser_string_literal (parser, خطأ, خطأ);
	    إذا (cval.مقدار == error_mark_گره)
	      أرجع error_mark_گره;
	    إذا ((اندازه_t) درخت_STRING_درازی (cval.مقدار)
		!= طول_رشته (درخت_STRING_اشاره_گر (cval.مقدار)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = درست;
		أرجع error_mark_گره;
	      }

	    حرف c = omp_get_fr_id_from_name (درخت_STRING_اشاره_گر (cval.مقدار));
	    إذا (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  درخت_STRING_اشاره_گر (cval.مقدار));
	    str += c;
	  }
	وإلا
	  {
	    c_عبارت cval = c_parser_عبارت_no_commas (parser, عدم);
	    درخت مقدار = c_fully_fold (cval.مقدار, خطأ, عدم);
	    إذا (INTEGRAL_TYPE_P (درخت_TYPE (مقدار))
		&& درخت_کد (مقدار) != INTEGER_CST)
	      مقدار = convert_lvalue_مقصد_rvalue (cval.get_شروع (), cval,
						خطأ, درست).مقدار;
	    إذا (درخت_کد (مقدار) != INTEGER_CST
		|| !درخت_میگنجد_shwi_p (مقدار))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		أرجع error_mark_گره;
	      }
	    HOST_WIDE_INT n = درخت_مقصد_shwi (مقدار);
	    إذا (n < 1 || n > GOMP_INTEROP_IFR_آخرین)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (حرف) n;
	  }
	str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    استمر;
	  }
	إذا (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  أرجع error_mark_گره;
	str += '\0';
	درخت res = build_string (str.درازی (), str.داده ());
	درخت_TYPE (res) = build_array_type_nelts (unsigned_char_type_گره,
						  str.درازی ());
	أرجع res;
      }

  /* New format. */
  std::string str2;
  طالما (درست)
    {
      إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	أرجع error_mark_گره;
      str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      منطقي has_fr = خطأ;
      طالما (درست)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  إذا (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_اشاره_گر (tok->مقدار)) != 0
		  && strcmp("attr", IDENTIFIER_اشاره_گر (tok->مقدار)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      أرجع error_mark_گره;
	    }
	  c_parser_consume_token (parser);
	  منطقي is_fr = IDENTIFIER_اشاره_گر (tok->مقدار)[0] == 'f';
	  إذا (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      أرجع error_mark_گره;
	    }
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع error_mark_گره;
	  طالما (درست)
	    {
	      إذا (c_parser_بعدی_token_is (parser, CPP_STRING))
		{
		  c_عبارت cval = c_parser_string_literal (parser, خطأ, خطأ);
		  درخت مقدار = cval.مقدار;
		  إذا (مقدار == error_mark_گره)
		    أرجع error_mark_گره;
		  إذا ((اندازه_t) درخت_STRING_درازی (مقدار)
		      != طول_رشته (درخت_STRING_اشاره_گر (مقدار)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = درست;
		      أرجع error_mark_گره;
		    }
		  إذا (!is_fr)
		    {
		      إذا (!startswith (درخت_STRING_اشاره_گر (مقدار), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = درست;
			  أرجع error_mark_گره;
			}
		      إذا (strchr (درخت_STRING_اشاره_گر (مقدار), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = درست;
			  أرجع error_mark_گره;
			}
		      str2 += درخت_STRING_اشاره_گر (مقدار);
		      str2 += '\0';
		    }
		  وإلا
		    {
		      إذا (*درخت_STRING_اشاره_گر (مقدار) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  أرجع error_mark_گره;
			}
		      حرف c = omp_get_fr_id_from_name (درخت_STRING_اشاره_گر (مقدار));
		      إذا (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    درخت_STRING_اشاره_گر (مقدار));
		     str += c;
		     has_fr = درست;
		    }
		}
	      وإلا إذا (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  أرجع error_mark_گره;
		}
	      وإلا
		{
		  c_عبارت cval = c_parser_عبارت_no_commas (parser, عدم);
		  درخت مقدار = c_fully_fold (cval.مقدار, خطأ, عدم);
		  إذا (INTEGRAL_TYPE_P (درخت_TYPE (مقدار))
		      && درخت_کد (مقدار) != INTEGER_CST)
		    مقدار = convert_lvalue_مقصد_rvalue (cval.get_شروع (), cval,
						      خطأ, درست).مقدار;

		  إذا (درخت_کد (مقدار) != INTEGER_CST
		      || !درخت_میگنجد_shwi_p (مقدار))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      أرجع error_mark_گره;
		    }
		  HOST_WIDE_INT n = درخت_مقصد_shwi (مقدار);
		  إذا (n < 1 || n > GOMP_INTEROP_IFR_آخرین)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (حرف) n;
		  has_fr = درست;
		}
	      إذا (!is_fr
		  && c_parser_بعدی_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  استمر;
		}
	      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		أرجع error_mark_گره;
	      اكسر;
	    }
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	    اكسر;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  أرجع error_mark_گره;
	}
      str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;
      إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	أرجع error_mark_گره;
    }
  c_parser_consume_token (parser);
  str += '\0';
  درخت res = build_string (str.درازی (), str.داده ());
  درخت_TYPE (res) = build_array_type_nelts (unsigned_char_type_گره,
						  str.درازی ());
  أرجع res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
هدف
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

ساكن منطقي
c_parser_omp_clause_init_modifiers (c_parser *parser, منطقي *هدف,
				    منطقي *targetsync, درخت *prefer_type_درخت)
{
  *هدف = خطأ;
  *targetsync = خطأ;
  *prefer_type_درخت = NULL_درخت;

  افعل
    {
      c_token *tok = c_parser_peek_token (parser);
      إذا (tok->type != CPP_NAME)
	اذهب fail;
      ثابت حرف *p = IDENTIFIER_اشاره_گر (tok->مقدار);
      إذا (strcmp ("targetsync", p) == 0)
	{
	  إذا (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = درست;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("target", p) == 0)
	{
	  إذا (*هدف)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *هدف = درست;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("prefer_type", p) == 0)
	{
	  إذا (*prefer_type_درخت != NULL_درخت)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_درخت = c_parser_omp_modifier_prefer_type (parser);
	  إذا (*prefer_type_درخت == error_mark_گره)
	    أرجع خطأ;
	}
      وإلا
	اذهب fail;
      tok = c_parser_peek_token (parser);
      إذا (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      أرجع درست;
    }
  طالما (درست);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  أرجع خطأ;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
هدف
     targetsync
     prefer_type (preference-specification) */

ساكن درخت
c_parser_omp_clause_init (c_parser *parser, درخت list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  منطقي هدف = خطأ;
  منطقي targetsync = خطأ;
  درخت prefer_type_درخت = NULL_درخت;

  إذا (!c_parser_omp_clause_init_modifiers (parser, &هدف, &targetsync,
					   &prefer_type_درخت)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      إذا (prefer_type_درخت != error_mark_گره)
	parens.skip_until_یافت_close (parser);
      أرجع list;
    }

  إذا (!هدف && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  درخت nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					خطأ);
  parens.skip_until_یافت_close (parser);

  لكل (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      إذا (هدف)
	OMP_CLAUSE_INIT_هدف (c) = 1;
      إذا (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      إذا (prefer_type_درخت)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_درخت;
    }
  أرجع nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

ساكن درخت
c_parser_omp_clause_use (c_parser *parser, درخت list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

ساكن درخت
c_parser_omp_clause_interop (c_parser *parser, درخت list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  لكل (درخت c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت_استفاده_شده (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  أرجع nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

ساكن درخت
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_ماسک ماسک,
			   ثابت حرف *where, منطقي پایان_p = درست,
			   منطقي هدف_p = خطأ)
{
  درخت clauses = عدم;
  منطقي اولی = درست;

  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t اینجا;
      pragma_omp_clause c_نوع;
      ثابت حرف *c_name;
      درخت prev = clauses;

      إذا (!اولی && c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      اینجا = c_parser_peek_token (parser)->location;
      c_نوع = c_parser_omp_clause_name (parser);

      بدل (c_نوع)
	{
	حالة PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (اینجا, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "attach";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "copy";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "copyin";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "copyout";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "create";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "delete";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, درست);
	  c_name = "default";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "detach";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "device";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_داده_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "device_resident";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (اینجا, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, اینجا, OMP_CLAUSE_GANG,
						c_name, clauses);
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "host";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, خطأ);
	  c_name = "if";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (اینجا, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (اینجا, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "link";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "no_create";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (اینجا, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_رقم_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_رقم_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_رقم_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_رقم_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "present";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_خصوصی:
	  clauses = c_parser_omp_clause_خصوصی (parser, clauses);
	  c_name = "private";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     خطأ, clauses);
	  c_name = "reduction";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_SELF:
	  إذا ((ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  وإلا
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_داده_clause (parser, c_نوع, clauses);
	  c_name = "self";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (اینجا, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_وکتور:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, اینجا, OMP_CLAUSE_وکتور,
						c_name,	clauses);
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_وکتور_درازی:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_وکتور_درازی,
						     clauses);
	  c_name = "vector_length";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_کارگر:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, اینجا, OMP_CLAUSE_کارگر,
						c_name, clauses);
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected an OpenACC clause");
	  اذهب saw_error;
	}

      اولی = خطأ;

      إذا (((ماسک >> c_نوع) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (اینجا, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_مقصد_pragma_eol (parser);

  إذا (پایان_p)
    أرجع c_پایان_omp_clauses (clauses, هدف_p ? C_ORT_ACC_هدف
						   : C_ORT_ACC);

  أرجع clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

ساكن درخت
c_parser_omp_all_clauses (c_parser *parser, omp_clause_ماسک ماسک,
			  ثابت حرف *where, منطقي پایان_p = درست,
			  صحيح nested = 0)
{
  درخت clauses = عدم;
  منطقي اولی = درست;

  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t اینجا;
      pragma_omp_clause c_نوع;
      ثابت حرف *c_name;
      درخت prev = clauses;

      إذا (nested && c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;

      إذا (!اولی || nested != 2)
	{
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا إذا (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      اینجا = c_parser_peek_token (parser)->location;
      c_نوع = c_parser_omp_clause_name (parser);

      بدل (c_نوع)
	{
	حالة PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, خطأ);
	  c_name = "default";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, درست);
	  c_name = "if";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_درون_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_درون_REDUCTION,
					     درست, clauses);
	  c_name = "in_reduction";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_غیرمستقیم:
	  clauses = c_parser_omp_clause_غیرمستقیم (parser, clauses);
	  c_name = "indirect";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_رقم_TASKS:
	  clauses = c_parser_omp_clause_رقم_tasks (parser, clauses);
	  c_name = "num_tasks";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_رقم_نخها:
	  clauses = c_parser_omp_clause_رقم_نخها (parser, clauses);
	  c_name = "num_threads";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ترتیب:
	  clauses = c_parser_omp_clause_ترتیب (parser, clauses);
	  c_name = "order";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_اولویت:
	  clauses = c_parser_omp_clause_اولویت (parser, clauses);
	  c_name = "priority";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_خصوصی:
	  clauses = c_parser_omp_clause_خصوصی (parser, clauses);
	  c_name = "private";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     درست, clauses);
	  c_name = "reduction";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_زمانبندی:
	  clauses = c_parser_omp_clause_زمانبندی (parser, clauses);
	  c_name = "schedule";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     درست, clauses);
	  c_name = "task_reduction";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  إذا (!اولی)
	    {
	     clause_not_اولی:
	      error_at (اینجا, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  إذا (!اولی)
	    اذهب clause_not_اولی;
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  إذا (!اولی)
	    اذهب clause_not_اولی;
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  إذا (!اولی)
	    اذهب clause_not_اولی;
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_مقصد:
	  إذا ((ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (اینجا);
	      richloc.جمع_کن_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      لكل (درخت c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_مقصد (c) = 1;
	      clauses = nl;
	    }
	  وإلا
	    clauses = c_parser_omp_clause_from_مقصد (parser, OMP_CLAUSE_مقصد,
						   clauses);
	  c_name = "to";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_مقصد (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_یکنواخت:
	  clauses = c_parser_omp_clause_یکنواخت (parser, clauses);
	  c_name = "uniform";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_رقم_TEAMS:
	  clauses = c_parser_omp_clause_رقم_teams (parser, clauses);
	  c_name = "num_teams";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_THREAD_حد:
	  clauses = c_parser_omp_clause_thread_حد (parser, clauses);
	  c_name = "thread_limit";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_خطی:
	  clauses = c_parser_omp_clause_خطی (parser, clauses);
	  c_name = "linear";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_استفاده_میکند_ALLOCATORS:
	  clauses = c_parser_omp_clause_استفاده_میکند_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, اینجا);
	  c_name = "depend";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, خطأ);
	  c_name = "map";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DIST_زمانبندی:
	  clauses = c_parser_omp_clause_dist_زمانبندی (parser, clauses);
	  c_name = "dist_schedule";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_نخها:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_نخها,
					       clauses);
	  c_name = "threads";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_پر:
	  c_name = "full";
	  clauses = c_parser_omp_clause_پر (parser, clauses);
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected an OpenMP clause");
	  اذهب saw_error;
	}

      اولی = خطأ;

      إذا (((ماسک >> c_نوع) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (اینجا, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  إذا (!nested)
    c_parser_skip_مقصد_pragma_eol (parser);

  إذا (پایان_p)
    {
      إذا ((ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_یکنواخت)) != 0)
	أرجع c_پایان_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      إذا ((ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	أرجع c_پایان_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      أرجع c_پایان_omp_clauses (clauses, C_ORT_OMP);
    }

  أرجع clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

ساكن درخت
c_parser_omp_structured_بلوک (c_parser *parser, منطقي *if_p)
{
  درخت stmt = افزودن_stmt_list ();
  parser->omp_attrs_forbidden_p = درست;
  c_parser_statement (parser, if_p);
  أرجع برداشت_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

ساكن درخت
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  درخت stmt, clauses = NULL_درخت;
  منطقي readonly = خطأ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_اشاره_گر (token->مقدار), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = درست;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_درخت);
      parens.skip_until_یافت_close (parser);
    }

  إذا (readonly)
    لكل (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_پایان_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_مقصد_pragma_eol (parser);

  stmt = make_گره (OACC_CACHE);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);

  أرجع stmt;
}

/* OpenACC 2.0:
   # pragma acc data oacc-data-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#تعریف_کن OACC_داده_CLAUSE_ماسک						\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_PRESENT))

ساكن درخت
c_parser_oacc_داده (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت stmt, clauses, بلوک;

  clauses = c_parser_oacc_all_clauses (parser, OACC_داده_CLAUSE_ماسک,
				       "#pragma acc data");

  بلوک = c_begin_omp_parallel ();
  جمع_کن_stmt (c_parser_omp_structured_بلوک (parser, if_p));

  stmt = c_پایان_oacc_داده (loc, clauses, بلوک);

  أرجع stmt;
}

/* OpenACC 2.0:
   # pragma acc declare oacc-data-clause[optseq] new-line
*/

#تعریف_کن OACC_DECLARE_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_LINK)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_PRESENT))

ساكن فراغ
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  درخت clauses, stmt, t, decl;

  منطقي error = خطأ;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_ماسک,
				       "#pragma acc declare");
  إذا (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      أرجع;
    }

  لكل (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      إذا (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = درست;
	  استمر;
	}

      بدل (OMP_CLAUSE_MAP_نوع (t))
	{
	حالة GOMP_MAP_FIRSTPRIVATE_اشاره_گر:
	حالة GOMP_MAP_ALLOC:
	حالة GOMP_MAP_مقصد:
	حالة GOMP_MAP_FORCE_DEVICEPTR:
	حالة GOMP_MAP_DEVICE_RESIDENT:
	  اكسر;

	حالة GOMP_MAP_LINK:
	  إذا (!global_bindings_p ()
	      && (درخت_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = درست;
	      استمر;
	    }
	  اكسر;

	افتراضي:
	  إذا (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = درست;
	      استمر;
	    }
	  إذا (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = درست;
	      استمر;
	    }
	  وإلا إذا (درخت_عمومی (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = درست;
	      استمر;
	    }
	  اكسر;
	}

      إذا (!c_check_درون_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = درست;
	  استمر;
	}

      إذا (lookup_attribute ("omp declare target", DECL_صفات (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_صفات (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = درست;
	  استمر;
	}

      إذا (!error)
	{
	  درخت id;

	  إذا (OMP_CLAUSE_MAP_نوع (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  وإلا
	    id = get_identifier ("omp declare target");

	  DECL_صفات (decl)
			   = درخت_cons (id, NULL_درخت, DECL_صفات (decl));

	  إذا (global_bindings_p ())
	    {
	      symtab_گره *گره = symtab_گره::get (decl);
	      إذا (گره != عدم)
		{
		  گره->offloadable = 1;
		  إذا (ENABLE_OFFLOADING)
		    {
		      g->have_offload = درست;
		      إذا (is_a <varpool_گره *> (گره))
			vec_امن_افزودن (offload_vars, decl);
		    }
		}
	    }
	}
    }

  إذا (error || global_bindings_p ())
    أرجع;

  stmt = make_گره (OACC_DECLARE);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, pragma_loc);

  جمع_کن_stmt (stmt);

  أرجع;
}

/* OpenACC 2.0:
   # pragma acc enter data oacc-enter-data-clause[optseq] new-line

   or

   # pragma acc exit data oacc-exit-data-clause[optseq] new-line


   LOC is the location of the #pragma token.
*/

#تعریف_کن OACC_ENTER_داده_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#تعریف_کن OACC_EXIT_داده_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DELETE) 		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DETACH) 		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_FINALIZE) 		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساكن فراغ
c_parser_oacc_enter_exit_داده (c_parser *parser, منطقي enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت clauses, stmt;
  ثابت حرف *p = "";

  c_parser_consume_pragma (parser);

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      c_parser_consume_token (parser);
    }

  إذا (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = درست;
      c_parser_skip_مقصد_pragma_eol (parser);
      أرجع;
    }

  إذا (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_داده_CLAUSE_ماسک,
					 "#pragma acc enter data");
  وإلا
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_داده_CLAUSE_ماسک,
					 "#pragma acc exit data");

  إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_MAP) == NULL_درخت)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      أرجع;
    }

  stmt = enter ? make_گره (OACC_ENTER_داده) : make_گره (OACC_EXIT_داده);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);
}


/* OpenACC 2.0:
   # pragma acc host_data oacc-data-clause[optseq] new-line
     structured-block
*/

#تعریف_کن OACC_HOST_داده_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_USE_DEVICE)          \
	 | (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF)                  \
	 | (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT) )

ساكن درخت
c_parser_oacc_host_داده (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت stmt, clauses, بلوک;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_داده_CLAUSE_ماسک,
				       "#pragma acc host_data", خطأ);
  إذا (!omp_پیدا_کن_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      أرجع error_mark_گره;
    }
  clauses = c_پایان_omp_clauses (clauses, C_ORT_ACC);
  بلوک = c_begin_omp_parallel ();
  جمع_کن_stmt (c_parser_omp_structured_بلوک (parser, if_p));
  stmt = c_پایان_oacc_host_داده (loc, clauses, بلوک);
  أرجع stmt;
}


/* OpenACC 2.0:

   # pragma acc loop oacc-loop-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#تعریف_کن OACC_LOOP_CLAUSE_ماسک						\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COLLAPSE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_خصوصی)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_کارگر)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_وکتور)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_AUTO)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_INDEPENDENT) 	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_TILE) )
ساكن درخت
c_parser_oacc_loop (location_t loc, c_parser *parser, حرف *p_name,
		    omp_clause_ماسک ماسک, درخت *cclauses, منطقي *if_p)
{
  منطقي is_parallel = ((ماسک >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  ماسک |= OACC_LOOP_CLAUSE_ماسک;

  درخت clauses = c_parser_oacc_all_clauses (parser, ماسک, p_name,
					    /*finish_p=*/cclauses == عدم,
					    /*target=*/is_parallel);
  إذا (cclauses)
    {
      clauses = c_oacc_تقسیم_loop_clauses (clauses, cclauses, is_parallel);
      إذا (*cclauses)
	*cclauses = c_پایان_omp_clauses (*cclauses, C_ORT_ACC_هدف);
      إذا (clauses)
	clauses = c_پایان_omp_clauses (clauses, C_ORT_ACC);
    }

  درخت بلوک = c_begin_compound_stmt (درست);
  درخت stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, عدم,
				     if_p);
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع stmt;
}

/* OpenACC 2.0:
   # pragma acc kernels oacc-kernels-clause[optseq] new-line
     structured-block

   or

   # pragma acc parallel oacc-parallel-clause[optseq] new-line
     structured-block

   OpenACC 2.6:

   # pragma acc serial oacc-serial-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#تعریف_کن OACC_KERNELS_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_رقم_GANGS)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_رقم_WORKERS)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_وکتور_درازی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#تعریف_کن OACC_PARALLEL_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_خصوصی)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_رقم_GANGS)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_رقم_WORKERS)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_وکتور_درازی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#تعریف_کن OACC_SERIAL_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_خصوصی)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساكن درخت
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       تعداد pragma_نوع p_نوع, حرف *p_name, منطقي *if_p)
{
  omp_clause_ماسک ماسک;
  تعداد درخت_کد_2 کد;
  بدل (p_نوع)
    {
    حالة PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      ماسک = OACC_KERNELS_CLAUSE_ماسک;
      کد = OACC_KERNELS;
      اكسر;
    حالة PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      ماسک = OACC_PARALLEL_CLAUSE_ماسک;
      کد = OACC_PARALLEL;
      اكسر;
    حالة PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      ماسک = OACC_SERIAL_CLAUSE_ماسک;
      کد = OACC_SERIAL;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  درخت بلوک = c_begin_omp_parallel ();
	  درخت clauses;
	  c_parser_oacc_loop (loc, parser, p_name, ماسک, &clauses, if_p);
	  أرجع c_پایان_omp_construct (loc, کد, بلوک, clauses);
	}
    }

  درخت clauses = c_parser_oacc_all_clauses (parser, ماسک, p_name,
					    /*finish_p=*/درست,
					    /*target=*/درست);

  درخت بلوک = c_begin_omp_parallel ();
  جمع_کن_stmt (c_parser_omp_structured_بلوک (parser, if_p));

  أرجع c_پایان_omp_construct (loc, کد, بلوک, clauses);
}

/* OpenACC 2.0:
   # pragma acc routine oacc-routine-clause[optseq] new-line
     function-definition

   # pragma acc routine ( name ) oacc-routine-clause[optseq] new-line
*/

#تعریف_کن OACC_ROUTINE_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_کارگر)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_وکتور)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_NOHOST) )

/* Parse an OpenACC routine directive.  For named directives, we apply
   immediately to the named function.  For unnamed ones we then parse
   a declaration or definition, which must be for a function.  */

ساكن فراغ
c_parser_oacc_routine (c_parser *parser, تعداد pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_داده داده;
  داده.error_دیده = خطأ;
  داده.fndecl_دیده = خطأ;
  داده.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      درخت decl = NULL_درخت;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      إذا (name_token->type == CPP_NAME
	  && (name_token->id_نوع == C_ID_ID
	      || name_token->id_نوع == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->مقدار);
	  إذا (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->مقدار);
	  c_parser_consume_token (parser);
	}
      وإلا
	c_parser_error (parser, "expected function name");

      إذا (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  أرجع;
	}

      داده.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_ماسک,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      داده.clauses = nreverse (داده.clauses);

      إذا (درخت_کد (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  أرجع;
	}

      c_پایان_oacc_routine (&داده, decl, خطأ);
    }
  وإلا /* No optional '( name )'.  */
    {
      داده.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_ماسک,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      داده.clauses = nreverse (داده.clauses);

      /* Emit a helpful diagnostic if there's another pragma following this
	 one.  Also don't allow a static assertion declaration, as in the
	 following we'll just parse a *single* "declaration or function
	 definition", and the static assertion counts an one.  */
      إذا (c_parser_بعدی_token_is (parser, CPP_PRAGMA)
	  || c_parser_بعدی_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (داده.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  أرجع;
	}

      /* We only have to consider the pragma_external case here.  */
      إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, درست, درست, درست, خطأ, درست,
					 خطأ, عدم, عدم, خطأ, عدم, &داده);
	  restore_extension_diagnostics (ext);
	}
      وإلا
	c_parser_declaration_or_fndef (parser, درست, درست, درست, خطأ, درست,
				       خطأ, عدم, عدم, خطأ, عدم, &داده);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

ساكن فراغ
c_پایان_oacc_routine (بنية oacc_routine_داده *داده, درخت fndecl,
		       منطقي is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  إذا (داده->error_دیده
      || fndecl == error_mark_گره)
    أرجع;

  إذا (داده->fndecl_دیده)
    {
      error_at (داده->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      داده->error_دیده = درست;
      أرجع;
    }
  إذا (fndecl == NULL_درخت || درخت_کد (fndecl) != FUNCTION_DECL)
    {
      error_at (داده->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      داده->error_دیده = درست;
      أرجع;
    }

  صحيح compatible
    = oacc_verify_routine_clauses (fndecl, &داده->clauses, داده->loc,
				   "#pragma acc routine");
  إذا (compatible < 0)
    {
      داده->error_دیده = درست;
      أرجع;
    }
  إذا (compatible > 0)
    {
    }
  وإلا
    {
      إذا (درخت_استفاده_شده (fndecl) || (!is_defn && DECL_SAVED_درخت (fndecl)))
	{
	  error_at (داده->loc,
		    درخت_استفاده_شده (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  داده->error_دیده = درست;
	  أرجع;
	}

      /* Set the routine's level of parallelism.  */
      درخت dims = oacc_build_routine_dims (داده->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_صفات (fndecl)
	= درخت_cons (get_identifier ("omp declare target"),
		     داده->clauses, DECL_صفات (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  داده->fndecl_دیده = درست;
}

/* OpenACC 2.0:
   # pragma acc update oacc-update-clause[optseq] new-line
*/

#تعریف_کن OACC_UPDATE_CLAUSE_ماسک						\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_DEVICE)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_HOST)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساكن فراغ
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  درخت clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_ماسک,
					    "#pragma acc update");
  إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_MAP) == NULL_درخت)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      أرجع;
    }

  إذا (parser->error)
    أرجع;

  درخت stmt = make_گره (OACC_UPDATE);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#تعریف_کن OACC_WAIT_CLAUSE_ماسک						\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OACC_CLAUSE_IF) )

ساكن درخت
c_parser_oacc_wait (location_t loc, c_parser *parser, حرف *p_name)
{
  درخت clauses, list = NULL_درخت, stmt = NULL_درخت;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_ماسک, p_name);
  stmt = c_پایان_oacc_wait (loc, list, clauses);
  جمع_کن_stmt (stmt);

  أرجع stmt;
}

بنية c_omp_loc_درخت
{
  location_t loc;
  درخت var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
ساكن درخت
c_check_omp_allocate_allocator_r (درخت *tp, صحيح *, فراغ *داده)
{
  درخت var = ((بنية c_omp_loc_درخت *) داده)->var;
  location_t loc = ((بنية c_omp_loc_درخت *) داده)->loc;
  إذا (درخت_کد (*tp) == VAR_DECL && c_check_درون_current_scope (*tp))
    {
      إذا (linemap_location_before_p (سطر_جدول, DECL_منبع_LOCATION (var),
				     DECL_منبع_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_منبع_LOCATION (*tp), "declared here");
	  inform (DECL_منبع_LOCATION (var),
		  "to be allocated variable declared here");
	  أرجع *tp;
	}
      وإلا
	{
	  gcc_assert (cur_stmt_list
		      && درخت_کد (cur_stmt_list) == STATEMENT_LIST);

	  درخت_stmt_iterator l = tsi_آخرین (cur_stmt_list);
	  طالما (!tsi_انتها_p (l))
	    {
	      إذا (linemap_location_before_p (سطر_جدول, عبارت_LOCATION (*l),
					     DECL_منبع_LOCATION (var)))
		  اكسر;
	      إذا (درخت_کد (*l) == MODIFY_عبارت
		  && درخت_عملوند (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (عبارت_LOCATION (*l), "modified here");
		  inform (DECL_منبع_LOCATION (var),
			  "to be allocated variable declared here");
		  أرجع *tp;
		}
	      --l;
	    }
	}
    }
  أرجع NULL_درخت;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

ساكن فراغ
c_parser_omp_allocate (c_parser *parser)
{
  درخت alignment = NULL_درخت;
  درخت allocator = NULL_درخت;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  درخت nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_درخت);
  افعل
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
	اكسر;
      matching_parens parens;
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      c_parser_consume_token (parser);
      location_t عبارت_loc = c_parser_peek_token (parser)->location;
      إذا (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  اكسر;
	}
      إذا (!parens.require_open (parser))
	اكسر;

      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, خطأ, درست);
      عبارت_loc = c_parser_peek_token (parser)->location;
      إذا (عبارت.مقدار == error_mark_گره)
	;
      وإلا إذا (p[2] == 'i' && alignment)
	{
	  error_at (عبارت_loc, "too many %qs clauses", "align");
	  اكسر;
	}
      وإلا إذا (p[2] == 'i')
	{
	  alignment = c_fully_fold (عبارت.مقدار, خطأ, عدم);
	  إذا (درخت_کد (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (درخت_TYPE (alignment))
	      || درخت_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (عبارت_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_درخت;
	    }
	}
      وإلا إذا (allocator)
	{
	  error_at (عبارت_loc, "too many %qs clauses", "allocator");
	  اكسر;
	}
      وإلا
	{
	  allocator = c_fully_fold (عبارت.مقدار, خطأ, عدم);
	  allocator_loc = عبارت_loc;
	  درخت orig_type
	    = عبارت.original_type ? عبارت.original_type : درخت_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (allocator))
	      || درخت_کد (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (عبارت_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			درخت_TYPE (allocator));
	      allocator = NULL_درخت;
	    }
	}
      parens.skip_until_یافت_close (parser);
    } طالما (درست);
  c_parser_skip_مقصد_pragma_eol (parser);

  c_mark_decl_jump_unsafe_درون_current_scope ();
  لكل (درخت c = nl; c != NULL_درخت; c = OMP_CLAUSE_CHAIN (c))
    {
      درخت var = OMP_CLAUSE_DECL (c);
      إذا (درخت_کد (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  استمر;
	}
      إذا (!parser->درون_omp_decl_attribute && !c_check_درون_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_منبع_LOCATION (var), "declared here");
	  استمر;
	}
      إذا (lookup_attribute ("omp allocate", DECL_صفات (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  استمر;
	}
      إذا (درخت_STATIC (var))
	{
	  إذا (allocator == NULL_درخت && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      استمر;
	    }
	  وإلا إذا (allocator
		   && (wi::مقصد_widest (allocator) < 1
		       || wi::مقصد_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::مقصد_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::مقصد_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  وإلا إذا (allocator
		   && (wi::eq_p (wi::مقصد_widest (allocator),
				 GOMP_OMP_PREDEF_ALLOC_CGROUP)
		       || wi::eq_p (wi::مقصد_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_PTEAM)
		       || wi::eq_p (wi::مقصد_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_THREAD)))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause for static variable %qD must not "
			"be %<omp_cgroup_mem_alloc%>, %<omp_pteam_mem_alloc%>, "
			"or %<omp_thread_mem_alloc%>", var);
	    }
	}
      إذا (allocator)
	{
	  بنية c_omp_loc_درخت داده
	    = {عبارت_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_درخت (&allocator, c_check_omp_allocate_allocator_r, &داده, عدم);
	}
      DECL_صفات (var) = درخت_cons (get_identifier ("omp allocate"),
					 build_درخت_list (allocator, alignment),
					 DECL_صفات (var));
    }
}

/* OpenMP 2.5:
   # pragma omp atomic new-line
     expression-stmt

   expression-stmt:
     x binop= expr | x++ | ++x | x-- | --x
   binop:
     +, *, -, /, &, ^, |, <<, >>

  where x is an lvalue expression with scalar type.

   OpenMP 3.1:
   # pragma omp atomic new-line
     update-stmt

   # pragma omp atomic read new-line
     read-stmt

   # pragma omp atomic write new-line
     write-stmt

   # pragma omp atomic update new-line
     update-stmt

   # pragma omp atomic capture new-line
     capture-stmt

   # pragma omp atomic capture new-line
     capture-block

   read-stmt:
     v = x
   write-stmt:
     x = expr
   update-stmt:
     expression-stmt | x = x binop expr
   capture-stmt:
     v = expression-stmt
   capture-block:
     { v = x; update-stmt; } | { update-stmt; v = x; }

   OpenMP 4.0:
   update-stmt:
     expression-stmt | x = x binop expr | x = expr binop x
   capture-stmt:
     v = update-stmt
   capture-block:
     { v = x; update-stmt; } | { update-stmt; v = x; } | { v = x; x = expr; }

   OpenMP 5.1:
   # pragma omp atomic compare new-line
     conditional-update-atomic

   # pragma omp atomic compare capture new-line
     conditional-update-capture-atomic

   conditional-update-atomic:
     cond-expr-stmt | cond-update-stmt
   cond-expr-stmt:
     x = expr ordop x ? expr : x;
     x = x ordop expr ? expr : x;
     x = x == e ? d : x;
   cond-update-stmt:
     if (expr ordop x) { x = expr; }
     if (x ordop expr) { x = expr; }
     if (x == e) { x = d; }
   ordop:
     <, >
   conditional-update-capture-atomic:
     v = cond-expr-stmt
     { v = x; cond-expr-stmt }
     { cond-expr-stmt v = x; }
     { v = x; cond-update-stmt }
     { cond-update-stmt v = x; }
     if (x == e) { x = d; } else { v = x; }
     { r = x == e; if (r) { x = d; } }
     { r = x == e; if (r) { x = d; } else { v = x; } }

  where x, r and v are lvalue expressions with scalar type,
  expr, e and d are expressions with scalar type and e might be
  the same as v.

  LOC is the location of the #pragma token.  */

ساكن فراغ
c_parser_omp_atomic (location_t loc, c_parser *parser, منطقي openacc)
{
  درخت lhs = NULL_درخت, rhs = NULL_درخت, v = NULL_درخت, r = NULL_درخت;
  درخت lhs1 = NULL_درخت, rhs1 = NULL_درخت;
  درخت stmt, orig_lhs, unfolded_lhs = NULL_درخت, unfolded_lhs1 = NULL_درخت;
  تعداد درخت_کد_2 کد = ERROR_MARK, opcode = NOP_عبارت;
  تعداد omp_حافظه_ترتیب حافظه_ترتیب = OMP_حافظه_ترتیب_UNSPECIFIED;
  بنية c_عبارت عبارت;
  location_t eloc;
  منطقي structured_بلوک = خطأ;
  منطقي swapped = خطأ;
  منطقي non_lvalue_p;
  درخت clauses = NULL_درخت;
  منطقي capture = خطأ;
  منطقي compare = خطأ;
  منطقي weak = خطأ;
  تعداد omp_حافظه_ترتیب fail = OMP_حافظه_ترتیب_UNSPECIFIED;
  منطقي no_semicolon = خطأ;
  منطقي extra_scope = خطأ;

  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  تعداد درخت_کد_2 new_کد = ERROR_MARK;
	  تعداد omp_حافظه_ترتیب new_حافظه_ترتیب
	    = OMP_حافظه_ترتیب_UNSPECIFIED;
	  منطقي new_capture = خطأ;
	  منطقي new_compare = خطأ;
	  منطقي new_weak = خطأ;
	  تعداد omp_حافظه_ترتیب new_fail = OMP_حافظه_ترتیب_UNSPECIFIED;

	  إذا (!strcmp (p, "read"))
	    new_کد = OMP_ATOMIC_READ;
	  وإلا إذا (!strcmp (p, "write"))
	    new_کد = NOP_عبارت;
	  وإلا إذا (!strcmp (p, "update"))
	    new_کد = OMP_ATOMIC;
	  وإلا إذا (openacc && !strcmp (p, "capture"))
	    new_کد = OMP_ATOMIC_CAPTURE_NEW;
	  وإلا إذا (openacc)
	    {
	      p = عدم;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  وإلا إذا (!strcmp (p, "capture"))
	    new_capture = درست;
	  وإلا إذا (!strcmp (p, "compare"))
	    new_compare = درست;
	  وإلا إذا (!strcmp (p, "weak"))
	    new_weak = درست;
	  وإلا إذا (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      إذا (!parens.require_open (parser))
		استمر;

	      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		{
		  ثابت حرف *q
		    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

		  إذا (!strcmp (q, "seq_cst"))
		    new_fail = OMP_حافظه_ترتیب_SEQ_CST;
		  وإلا إذا (!strcmp (q, "acquire"))
		    new_fail = OMP_حافظه_ترتیب_ACQUIRE;
		  وإلا إذا (!strcmp (q, "relaxed"))
		    new_fail = OMP_حافظه_ترتیب_RELAXED;
		}

	      إذا (new_fail != OMP_حافظه_ترتیب_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  إذا (fail != OMP_حافظه_ترتیب_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  وإلا
		    fail = new_fail;
		}
	      وإلا
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_یافت_close (parser);
	      استمر;
	    }
	  وإلا إذا (!strcmp (p, "seq_cst"))
	    new_حافظه_ترتیب = OMP_حافظه_ترتیب_SEQ_CST;
	  وإلا إذا (!strcmp (p, "acq_rel"))
	    new_حافظه_ترتیب = OMP_حافظه_ترتیب_ACQ_REL;
	  وإلا إذا (!strcmp (p, "release"))
	    new_حافظه_ترتیب = OMP_حافظه_ترتیب_RELEASE;
	  وإلا إذا (!strcmp (p, "acquire"))
	    new_حافظه_ترتیب = OMP_حافظه_ترتیب_ACQUIRE;
	  وإلا إذا (!strcmp (p, "relaxed"))
	    new_حافظه_ترتیب = OMP_حافظه_ترتیب_RELAXED;
	  وإلا إذا (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      استمر;
	    }
	  وإلا
	    {
	      p = عدم;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  إذا (p)
	    {
	      إذا (new_کد != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  إذا (openacc
		      && کد == OMP_ATOMIC
		      && new_کد == OMP_ATOMIC_CAPTURE_NEW)
		    کد = new_کد;
		  وإلا إذا (کد != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  وإلا
		    کد = new_کد;
		}
	      وإلا إذا (new_حافظه_ترتیب != OMP_حافظه_ترتیب_UNSPECIFIED)
		{
		  إذا (حافظه_ترتیب != OMP_حافظه_ترتیب_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  وإلا
		    حافظه_ترتیب = new_حافظه_ترتیب;
		}
	      وإلا إذا (new_capture)
		{
		  إذا (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  وإلا
		    capture = درست;
		}
	      وإلا إذا (new_compare)
		{
		  إذا (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  وإلا
		    compare = درست;
		}
	      وإلا إذا (new_weak)
		{
		  إذا (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  وإلا
		    weak = درست;
		}
	      c_parser_consume_token (parser);
	      استمر;
	    }
	}
      اكسر;
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  إذا (کد == ERROR_MARK)
    کد = OMP_ATOMIC;
  إذا (capture)
    {
      إذا (کد != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      وإلا
	کد = OMP_ATOMIC_CAPTURE_NEW;
    }
  إذا (compare && کد != OMP_ATOMIC && کد != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = خطأ;
    }
  إذا (fail != OMP_حافظه_ترتیب_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_حافظه_ترتیب_UNSPECIFIED;
    }
  إذا (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = خطأ;
    }
  إذا (openacc)
    حافظه_ترتیب = OMP_حافظه_ترتیب_RELAXED;
  وإلا إذا (حافظه_ترتیب == OMP_حافظه_ترتیب_UNSPECIFIED)
    {
      omp_requires_ماسک
	= (تعداد omp_requires) (omp_requires_ماسک
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب_استفاده_شده);
      بدل ((تعداد omp_حافظه_ترتیب)
	      (omp_requires_ماسک & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب))
	{
	حالة OMP_حافظه_ترتیب_UNSPECIFIED:
	حالة OMP_حافظه_ترتیب_RELAXED:
	  حافظه_ترتیب = OMP_حافظه_ترتیب_RELAXED;
	  اكسر;
	حالة OMP_حافظه_ترتیب_SEQ_CST:
	  حافظه_ترتیب = OMP_حافظه_ترتیب_SEQ_CST;
	  اكسر;
	حالة OMP_حافظه_ترتیب_ACQUIRE:
	  إذا (کد == NOP_عبارت)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      حافظه_ترتیب = OMP_حافظه_ترتیب_SEQ_CST;
	    }
	  وإلا
	    حافظه_ترتیب = OMP_حافظه_ترتیب_ACQUIRE;
	  اكسر;
	حالة OMP_حافظه_ترتیب_RELEASE:
	  إذا (کد == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      حافظه_ترتیب = OMP_حافظه_ترتیب_SEQ_CST;
	    }
	  وإلا
	    حافظه_ترتیب = OMP_حافظه_ترتیب_RELEASE;
	  اكسر;
	حالة OMP_حافظه_ترتیب_ACQ_REL:
	  بدل (کد)
	    {
	    حالة OMP_ATOMIC_READ:
	      حافظه_ترتیب = OMP_حافظه_ترتیب_ACQUIRE;
	      اكسر;
	    حالة NOP_عبارت: /* atomic write */
	      حافظه_ترتیب = OMP_حافظه_ترتیب_RELEASE;
	      اكسر;
	    افتراضي:
	      حافظه_ترتیب = OMP_حافظه_ترتیب_ACQ_REL;
	      اكسر;
	    }
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}
    }
  وإلا
    بدل (کد)
      {
      حالة OMP_ATOMIC_READ:
	إذا (حافظه_ترتیب == OMP_حافظه_ترتیب_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    حافظه_ترتیب = OMP_حافظه_ترتیب_SEQ_CST;
	  }
	وإلا إذا (حافظه_ترتیب == OMP_حافظه_ترتیب_ACQ_REL)
	  حافظه_ترتیب = OMP_حافظه_ترتیب_ACQUIRE;
	اكسر;
      حالة NOP_عبارت: /* atomic write */
	إذا (حافظه_ترتیب == OMP_حافظه_ترتیب_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    حافظه_ترتیب = OMP_حافظه_ترتیب_SEQ_CST;
	  }
	وإلا إذا (حافظه_ترتیب == OMP_حافظه_ترتیب_ACQ_REL)
	  حافظه_ترتیب = OMP_حافظه_ترتیب_RELEASE;
	اكسر;
      افتراضي:
	اكسر;
      }
  إذا (fail != OMP_حافظه_ترتیب_UNSPECIFIED)
    حافظه_ترتیب
      = (تعداد omp_حافظه_ترتیب) (حافظه_ترتیب
				 | (fail << OMP_FAIL_حافظه_ترتیب_لغزش));

  بدل (کد)
    {
    حالة OMP_ATOMIC_READ:
    حالة NOP_عبارت: /* atomic write */
      v = c_parser_cast_عبارت (parser, عدم).مقدار;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, خطأ, عدم, درست);
      إذا (v == error_mark_گره)
	اذهب saw_error;
      إذا (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اذهب saw_error;
      إذا (کد == NOP_عبارت)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  عبارت = c_parser_عبارت (parser);
	  عبارت = default_function_array_read_conversion (eloc, عبارت);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  کد = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_درخت;
	  rhs = c_fully_fold (عبارت.مقدار, خطأ, عدم);
	  إذا (rhs == error_mark_گره)
	    اذهب saw_error;
	}
      وإلا
	{
	  lhs = c_parser_cast_عبارت (parser, عدم).مقدار;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, خطأ, عدم, درست);
	  إذا (lhs == error_mark_گره)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      اذهب انجامشده;
    حالة OMP_ATOMIC_CAPTURE_NEW:
      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_بلوک = درست;
	}
      وإلا إذا (compare
	       && c_parser_بعدی_token_is_keyword (parser, RID_IF))
	اكسر;
      وإلا
	{
	  v = c_parser_cast_عبارت (parser, عدم).مقدار;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, خطأ, عدم, درست);
	  إذا (v == error_mark_گره)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    v = non_lvalue (v);
	  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    اذهب saw_error;
	  إذا (compare && c_parser_بعدی_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      اذهب saw_error;
	    }
	}
      اكسر;
    افتراضي:
      اكسر;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  إذا (compare && c_parser_بعدی_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      إذا (!parens.require_open (parser))
	اذهب saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_عبارت cmp_عبارت;
      إذا (r)
	{
	  cmp_عبارت = c_parser_cast_عبارت (parser, عدم);
	  cmp_عبارت = default_function_array_conversion (eloc, cmp_عبارت);
	}
      وإلا
	cmp_عبارت = c_parser_دودویی_عبارت (parser, عدم, void_list_گره);
      parens.skip_until_یافت_close (parser);
      إذا (cmp_عبارت.مقدار == error_mark_گره)
	اذهب saw_error;
      إذا (r)
	{
	  إذا (!c_درخت_equal (cmp_عبارت.مقدار, unfolded_lhs))
	    اذهب bad_if;
	  cmp_عبارت.مقدار = rhs1;
	  rhs1 = NULL_درخت;
	  gcc_assert (درخت_کد (cmp_عبارت.مقدار) == EQ_عبارت);
	}
      إذا (درخت_کد (cmp_عبارت.مقدار) == EQ_عبارت)
	;
      وإلا إذا (!structured_بلوک && کد == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (عبارت_LOC_OR_LOC (cmp_عبارت.مقدار, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  اذهب saw_error;
	}
      وإلا إذا (درخت_کد (cmp_عبارت.مقدار) != GT_عبارت
	       && درخت_کد (cmp_عبارت.مقدار) != LT_عبارت)
	{
	  error_at (عبارت_LOC_OR_LOC (cmp_عبارت.مقدار, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  اذهب saw_error;
	}
      إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	اذهب saw_error;

      extra_scope = درست;
      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_cast_عبارت (parser, عدم);
      lhs = عبارت.مقدار;
      عبارت = default_function_array_conversion (eloc, عبارت);
      unfolded_lhs = عبارت.مقدار;
      lhs = c_fully_fold (lhs, خطأ, عدم, درست);
      orig_lhs = lhs;
      إذا (lhs == error_mark_گره)
	اذهب saw_error;
      إذا (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      إذا (!c_parser_بعدی_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  اذهب saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_عبارت_no_commas (parser, عدم);
      rhs1 = عبارت.مقدار;

      إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	اذهب saw_error;

      إذا (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	اذهب saw_error;

      extra_scope = خطأ;
      no_semicolon = درست;

      إذا (c_درخت_equal (درخت_عملوند (cmp_عبارت.مقدار, 0), unfolded_lhs))
	{
	  إذا (درخت_کد (cmp_عبارت.مقدار) == EQ_عبارت)
	    {
	      opcode = COND_عبارت;
	      rhs = c_fully_fold (درخت_عملوند (cmp_عبارت.مقدار, 1),
				  خطأ, عدم, درست);
	      rhs1 = c_fully_fold (rhs1, خطأ, عدم, درست);
	    }
	  وإلا إذا (c_درخت_equal (درخت_عملوند (cmp_عبارت.مقدار, 1), rhs1))
	    {
	      opcode = (درخت_کد (cmp_عبارت.مقدار) == GT_عبارت
			? MIN_عبارت : MAX_عبارت);
	      rhs = c_fully_fold (rhs1, خطأ, عدم, درست);
	      rhs1 = c_fully_fold (درخت_عملوند (cmp_عبارت.مقدار, 0),
				   خطأ, عدم, درست);
	    }
	  وإلا
	    اذهب bad_if;
	}
      وإلا إذا (درخت_کد (cmp_عبارت.مقدار) == EQ_عبارت)
	اذهب bad_if;
      وإلا إذا (c_درخت_equal (درخت_عملوند (cmp_عبارت.مقدار, 1), unfolded_lhs)
	       && c_درخت_equal (درخت_عملوند (cmp_عبارت.مقدار, 0), rhs1))
	{
	  opcode = (درخت_کد (cmp_عبارت.مقدار) == GT_عبارت
		    ? MAX_عبارت : MIN_عبارت);
	  rhs = c_fully_fold (rhs1, خطأ, عدم, درست);
	  rhs1 = c_fully_fold (درخت_عملوند (cmp_عبارت.مقدار, 1),
			       خطأ, عدم, درست);
	}
      وإلا
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  اذهب saw_error;
	}

      إذا (c_parser_بعدی_token_is_keyword (parser, RID_ELSE))
	{
	  إذا (کد != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_بلوک && r == NULL_درخت)
	      || درخت_کد (cmp_عبارت.مقدار) != EQ_عبارت)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      اذهب saw_error;
	    }

	  c_parser_consume_token (parser);

	  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    اذهب saw_error;

	  extra_scope = درست;
	  v = c_parser_cast_عبارت (parser, عدم).مقدار;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, خطأ, عدم, درست);
	  إذا (v == error_mark_گره)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    v = non_lvalue (v);
	  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    اذهب saw_error;

	  عبارت = c_parser_عبارت_no_commas (parser, عدم);

	  إذا (!c_درخت_equal (عبارت.مقدار, unfolded_lhs))
	    اذهب bad_if;

	  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    اذهب saw_error;

	  إذا (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    اذهب saw_error;

	  extra_scope = خطأ;
	  کد = OMP_ATOMIC_CAPTURE_OLD;
	  إذا (r == NULL_درخت)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_گره;
	}
      وإلا إذا (کد == OMP_ATOMIC_CAPTURE_NEW && !structured_بلوک)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  اذهب saw_error;
	}
      وإلا إذا (کد == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_درخت
	       && v == NULL_درخت)
	کد = OMP_ATOMIC;
      اذهب stmt_انجامشده;
    }
  eloc = c_parser_peek_token (parser)->location;
  عبارت = c_parser_cast_عبارت (parser, عدم);
  lhs = عبارت.مقدار;
  عبارت = default_function_array_conversion (eloc, عبارت);
  unfolded_lhs = عبارت.مقدار;
  lhs = c_fully_fold (lhs, خطأ, عدم, درست);
  orig_lhs = lhs;
  بدل (درخت_کد (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    حالة ERROR_MARK:
    saw_error:
      c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
      إذا (extra_scope && c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      إذا (structured_بلوک)
	{
	  إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  وإلا إذا (کد == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
	      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      أرجع;

    حالة POSTINCREMENT_عبارت:
      إذا (کد == OMP_ATOMIC_CAPTURE_NEW && !structured_بلوک)
	کد = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالة PREINCREMENT_عبارت:
      lhs = درخت_عملوند (lhs, 0);
      unfolded_lhs = NULL_درخت;
      opcode = PLUS_عبارت;
      rhs = integer_one_گره;
      إذا (compare)
	اذهب invalid_compare;
      اكسر;

    حالة POSTDECREMENT_عبارت:
      إذا (کد == OMP_ATOMIC_CAPTURE_NEW && !structured_بلوک)
	کد = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالة PREDECREMENT_عبارت:
      lhs = درخت_عملوند (lhs, 0);
      unfolded_lhs = NULL_درخت;
      opcode = MINUS_عبارت;
      rhs = integer_one_گره;
      إذا (compare)
	اذهب invalid_compare;
      اكسر;

    حالة COMPOUND_عبارت:
      إذا (درخت_کد (درخت_عملوند (lhs, 0)) == SAVE_عبارت
	  && درخت_کد (درخت_عملوند (lhs, 1)) == COMPOUND_عبارت
	  && درخت_کد (درخت_عملوند (درخت_عملوند (lhs, 1), 0)) == MODIFY_عبارت
	  && درخت_عملوند (درخت_عملوند (lhs, 1), 1) == درخت_عملوند (lhs, 0)
	  && C_BOOLEAN_TYPE_P (درخت_TYPE (درخت_عملوند (درخت_عملوند
					      (درخت_عملوند (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = درخت_عملوند (درخت_عملوند (lhs, 1), 0);
      /* FALLTHRU */
    حالة MODIFY_عبارت:
      إذا (درخت_کد (lhs) == MODIFY_عبارت
	  && C_BOOLEAN_TYPE_P (درخت_TYPE (درخت_عملوند (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  إذا (integer_onep (درخت_عملوند (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = درخت_عملوند (lhs, 1);
	      lhs = درخت_عملوند (lhs, 0);
	      unfolded_lhs = NULL_درخت;
	      opcode = NOP_عبارت;
	      إذا (کد == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_بلوک
		  && درخت_کد (orig_lhs) == COMPOUND_عبارت)
		کد = OMP_ATOMIC_CAPTURE_OLD;
	      إذا (compare)
		اذهب invalid_compare;
	      اكسر;
	    }
	  إذا (درخت_کد (درخت_عملوند (lhs, 1)) == TRUTH_NOT_عبارت
	      && درخت_عملوند (lhs, 0)
		 == درخت_عملوند (درخت_عملوند (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = درخت_عملوند (lhs, 1);
	      lhs = درخت_عملوند (lhs, 0);
	      unfolded_lhs = NULL_درخت;
	      opcode = NOP_عبارت;
	      إذا (کد == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_بلوک
		  && درخت_کد (orig_lhs) == COMPOUND_عبارت)
		کد = OMP_ATOMIC_CAPTURE_OLD;
	      إذا (compare)
		اذهب invalid_compare;
	      اكسر;
	    }
	}
      /* FALLTHRU */
    افتراضي:
      إذا (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      إذا (compare && !c_parser_بعدی_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  اذهب saw_error;
	}
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_MULT_EQ:
	  opcode = MULT_عبارت;
	  اكسر;
	حالة CPP_DIV_EQ:
	  opcode = TRUNC_DIV_عبارت;
	  اكسر;
	حالة CPP_PLUS_EQ:
	  opcode = PLUS_عبارت;
	  اكسر;
	حالة CPP_MINUS_EQ:
	  opcode = MINUS_عبارت;
	  اكسر;
	حالة CPP_LSHIFT_EQ:
	  opcode = LSHIFT_عبارت;
	  اكسر;
	حالة CPP_RSHIFT_EQ:
	  opcode = RSHIFT_عبارت;
	  اكسر;
	حالة CPP_AND_EQ:
	  opcode = بیت_AND_عبارت;
	  اكسر;
	حالة CPP_OR_EQ:
	  opcode = بیت_IOR_عبارت;
	  اكسر;
	حالة CPP_XOR_EQ:
	  opcode = بیت_XOR_عبارت;
	  اكسر;
	حالة CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  عبارت = c_parser_عبارت_no_commas (parser, عدم, unfolded_lhs);
	  rhs1 = عبارت.مقدار;
	  بدل (درخت_کد (rhs1))
	    {
	    حالة MULT_عبارت:
	    حالة TRUNC_DIV_عبارت:
	    حالة RDIV_عبارت:
	    حالة PLUS_عبارت:
	    حالة MINUS_عبارت:
	    حالة LSHIFT_عبارت:
	    حالة RSHIFT_عبارت:
	    حالة بیت_AND_عبارت:
	    حالة بیت_IOR_عبارت:
	    حالة بیت_XOR_عبارت:
	      إذا (compare)
		اكسر;
	      إذا (c_درخت_equal (درخت_عملوند (rhs1, 0), unfolded_lhs))
		{
		  opcode = درخت_کد (rhs1);
		  rhs = c_fully_fold (درخت_عملوند (rhs1, 1), خطأ, عدم,
				      درست);
		  rhs1 = c_fully_fold (درخت_عملوند (rhs1, 0), خطأ, عدم,
				       درست);
		  اذهب stmt_انجامشده;
		}
	      إذا (c_درخت_equal (درخت_عملوند (rhs1, 1), unfolded_lhs))
		{
		  opcode = درخت_کد (rhs1);
		  rhs = c_fully_fold (درخت_عملوند (rhs1, 0), خطأ, عدم,
				      درست);
		  rhs1 = c_fully_fold (درخت_عملوند (rhs1, 1), خطأ, عدم,
				       درست);
		  swapped = !commutative_درخت_کد (opcode);
		  اذهب stmt_انجامشده;
		}
	      اكسر;
	    حالة COND_عبارت:
	      إذا (!compare)
		اكسر;
	      إذا (درخت_کد (درخت_عملوند (rhs1, 0)) != GT_عبارت
		  && درخت_کد (درخت_عملوند (rhs1, 0)) != LT_عبارت
		  && درخت_کد (درخت_عملوند (rhs1, 0)) != EQ_عبارت)
		اكسر;
	      إذا (!درخت_عملوند (rhs1, 1))
		اكسر;
	      إذا (!c_درخت_equal (درخت_عملوند (rhs1, 2), unfolded_lhs))
		اكسر;
	      إذا (c_درخت_equal (درخت_عملوند (درخت_عملوند (rhs1, 0), 0),
				unfolded_lhs))
		{
		  إذا (درخت_کد (درخت_عملوند (rhs1, 0)) == EQ_عبارت)
		    {
		      opcode = COND_عبارت;
		      rhs = c_fully_fold (درخت_عملوند (درخت_عملوند (rhs1,
								      0), 1),
					  خطأ, عدم, درست);
		      rhs1 = c_fully_fold (درخت_عملوند (rhs1, 1), خطأ,
					   عدم, درست);
		      اذهب stmt_انجامشده;
		    }
		  إذا (c_درخت_equal (درخت_عملوند (درخت_عملوند (rhs1, 0), 1),
				    درخت_عملوند (rhs1, 1)))
		    {
		      opcode = (درخت_کد (درخت_عملوند (rhs1, 0)) == GT_عبارت
				? MIN_عبارت : MAX_عبارت);
		      rhs = c_fully_fold (درخت_عملوند (rhs1, 1), خطأ, عدم,
					  درست);
		      rhs1 = c_fully_fold (درخت_عملوند (درخت_عملوند (rhs1,
								       0), 0),
					   خطأ, عدم, درست);
		      اذهب stmt_انجامشده;
		    }
		}
	      وإلا إذا (درخت_کد (درخت_عملوند (rhs1, 0)) == EQ_عبارت)
		اكسر;
	      وإلا إذا (c_درخت_equal (درخت_عملوند (درخت_عملوند (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  إذا (c_درخت_equal (درخت_عملوند (درخت_عملوند (rhs1, 0), 0),
				    درخت_عملوند (rhs1, 1)))
		    {
		      opcode = (درخت_کد (درخت_عملوند (rhs1, 0)) == GT_عبارت
				? MAX_عبارت : MIN_عبارت);
		      rhs = c_fully_fold (درخت_عملوند (rhs1, 1), خطأ, عدم,
					  درست);
		      rhs1 = c_fully_fold (درخت_عملوند (درخت_عملوند (rhs1,
								       0), 1),
					   خطأ, عدم, درست);
		      اذهب stmt_انجامشده;
		    }
		}
	      اكسر;
	    حالة EQ_عبارت:
	      إذا (!compare
		  || کد != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_بلوک
		  || v
		  || r)
		اكسر;
	      إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_درخت;
		  c_parser_consume_token (parser);
		  اذهب restart;
		}
	      اكسر;
	    حالة ERROR_MARK:
	      اذهب saw_error;
	    افتراضي:
	      اكسر;
	    }
	  إذا (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      إذا (structured_بلوک && کد == OMP_ATOMIC_CAPTURE_NEW)
		{
		  کد = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_درخت;
		  عبارت = default_function_array_read_conversion (eloc, عبارت);
		  unfolded_lhs1 = عبارت.مقدار;
		  lhs1 = c_fully_fold (unfolded_lhs1, خطأ, عدم, درست);
		  rhs1 = NULL_درخت;
		  c_parser_consume_token (parser);
		  اذهب restart;
		}
	      إذا (structured_بلوک && !compare)
		{
		  opcode = NOP_عبارت;
		  عبارت = default_function_array_read_conversion (eloc, عبارت);
		  rhs = c_fully_fold (عبارت.مقدار, خطأ, عدم, درست);
		  rhs1 = NULL_درخت;
		  اذهب stmt_انجامشده;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  اذهب saw_error;
	افتراضي:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  اذهب saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_عبارت (parser);
      عبارت = default_function_array_read_conversion (eloc, عبارت);
      rhs = عبارت.مقدار;
      rhs = c_fully_fold (rhs, خطأ, عدم, درست);
      اكسر;
    }
stmt_انجامشده:
  إذا (structured_بلوک && کد == OMP_ATOMIC_CAPTURE_NEW && r == NULL_درخت)
    {
      إذا (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	اذهب saw_error;
      no_semicolon = خطأ;
      v = c_parser_cast_عبارت (parser, عدم).مقدار;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, خطأ, عدم, درست);
      إذا (v == error_mark_گره)
	اذهب saw_error;
      إذا (non_lvalue_p)
	v = non_lvalue (v);
      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اذهب saw_error;
      eloc = c_parser_peek_token (parser)->location;
      عبارت = c_parser_cast_عبارت (parser, عدم);
      lhs1 = عبارت.مقدار;
      عبارت = default_function_array_read_conversion (eloc, عبارت);
      unfolded_lhs1 = عبارت.مقدار;
      lhs1 = c_fully_fold (lhs1, خطأ, عدم, درست);
      إذا (lhs1 == error_mark_گره)
	اذهب saw_error;
      إذا (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  إذا (structured_بلوک)
    {
      إذا (!no_semicolon)
	c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
انجامشده:
  إذا (weak && opcode != COND_عبارت)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = خطأ;
    }
  إذا (unfolded_lhs && unfolded_lhs1
      && !c_درخت_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_گره;
    }
  وإلا
    stmt = c_پایان_omp_atomic (loc, کد, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, حافظه_ترتیب, weak);
  إذا (stmt != error_mark_گره)
    جمع_کن_stmt (stmt);

  إذا (!structured_بلوک && !no_semicolon)
    c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

ساكن فراغ
c_parser_omp_barrier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);

  c_پایان_omp_barrier (loc);
}

/* OpenMP 2.5:
   # pragma omp critical [(name)] new-line
     structured-block

   OpenMP 4.5:
   # pragma omp critical [(name) [hint(expression)]] new-line

  LOC is the location of the #pragma itself.  */

#تعریف_کن OMP_CRITICAL_CLAUSE_ماسک		\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_HINT) )

ساكن درخت
c_parser_omp_critical (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت stmt, name = NULL_درخت, clauses = NULL_درخت;

  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->مقدار;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      وإلا
	c_parser_error (parser, "expected identifier");

      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_ماسک,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_بلوک (parser, if_p);
  أرجع c_پایان_omp_critical (loc, stmt, name, clauses);
}

/* OpenMP 5.0:
   # pragma omp depobj ( depobj ) depobj-clause new-line

   depobj-clause:
     depend (dependence-type : locator)
     destroy
     update (dependence-type)

   OpenMP 5.2 additionally:
     destroy ( depobj )

   dependence-type:
درون
بیرون
     inout
     mutexinout  */

ساكن فراغ
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
      c_parser_skip_مقصد_pragma_eol (parser);
      أرجع;
    }

  درخت depobj = c_parser_عبارت_no_commas (parser, عدم).مقدار;
  إذا (depobj != error_mark_گره)
    {
      إذا (!lvalue_p (depobj))
	{
	  error_at (عبارت_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_گره;
	}
      وإلا
	{
	  درخت addr = build_unary_op (عبارت_LOC_OR_LOC (depobj, loc), ADDR_عبارت,
				      depobj, خطأ);
	  إذا (addr == error_mark_گره)
	    depobj = error_mark_گره;
	  وإلا
	    depobj = build_غیرمستقیم_ref (عبارت_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_ستاره);
	}
    }

  parens.skip_until_یافت_close (parser);
  درخت clause = NULL_درخت;
  تعداد omp_clause_depend_نوع نوع = OMP_CLAUSE_DEPEND_INVALID;
  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      c_parser_consume_token (parser);
      إذا (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_درخت, c_loc);
	  clause = c_پایان_omp_clauses (clause, C_ORT_OMP);
	  إذا (!clause)
	    clause = error_mark_گره;
	}
      وإلا إذا (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  نوع = OMP_CLAUSE_DEPEND_آخرین;
	  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      درخت destobj = c_parser_عبارت_no_commas (parser, عدم).مقدار;
	      إذا (!lvalue_p (destobj))
		error_at (عبارت_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      وإلا إذا (depobj != error_mark_گره
		       && !عملوند_equal_p (destobj, depobj,
					    OEP_تطابق_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (عبارت_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_یافت_close (parser);
	    }
	}
      وإلا إذا (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  إذا (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		{
		  ثابت حرف *p2
		    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

		  c_parser_consume_token (parser);
		  إذا (!strcmp ("in", p2))
		    نوع = OMP_CLAUSE_DEPEND_درون;
		  وإلا إذا (!strcmp ("out", p2))
		    نوع = OMP_CLAUSE_DEPEND_بیرون;
		  وإلا إذا (!strcmp ("inout", p2))
		    نوع = OMP_CLAUSE_DEPEND_INOUT;
		  وإلا إذا (!strcmp ("mutexinoutset", p2))
		    نوع = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  وإلا إذا (!strcmp ("inoutset", p2))
		    نوع = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      إذا (نوع == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_گره;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_یافت_close (parser);
	    }
	  وإلا
	    clause = error_mark_گره;
	}
    }
  إذا (!clause && نوع == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_گره;
      error_at (c_loc, "expected %<depend%>, %<destroy%> or %<update%> clause");
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  c_پایان_omp_depobj (loc, depobj, نوع, clause);
}


/* OpenMP 2.5:
   # pragma omp flush flush-vars[opt] new-line

   flush-vars:
     ( variable-list )

   OpenMP 5.0:
   # pragma omp flush memory-order-clause new-line  */

ساكن فراغ
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  تعداد memmodel mo = MEMMODEL_آخرین;
  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p
	= IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      إذا (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      وإلا إذا (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      وإلا إذا (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      وإلا إذا (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      وإلا
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      إذا (mo != MEMMODEL_آخرین)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
    }
  وإلا إذا (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_مقصد_pragma_eol (parser);

  c_پایان_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

ساكن منطقي
c_parser_omp_section_پیمایش (c_parser *parser, ثابت حرف *directive,
			   منطقي tentative)
{
  إذا (!c_parser_nth_token_starts_std_صفات (parser, 1))
    أرجع خطأ;
  بیعلامت صحيح n = 3;
  إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &n))
    أرجع خطأ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  إذا (token->type != CPP_CLOSE_مربع)
    أرجع خطأ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  إذا (token->type != CPP_CLOSE_مربع)
    أرجع خطأ;
  إذا (n < 9)
    أرجع خطأ;
  إذا (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      درخت اولی = c_parser_peek_nth_token_raw (parser, 3)->مقدار;
      درخت دومی = c_parser_peek_nth_token_raw (parser, 5)->مقدار;
      إذا (strcmp (IDENTIFIER_اشاره_گر (اولی), "directive")
	  && strcmp (IDENTIFIER_اشاره_گر (اولی), "__directive__"))
	أرجع خطأ;
      إذا (strcmp (IDENTIFIER_اشاره_گر (دومی), directive))
	أرجع خطأ;
    }
  إذا (tentative)
    أرجع درست;
  location_t اولی_loc = c_parser_peek_token (parser)->location;
  location_t آخرین_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t میانه_loc = UNKNOWN_LOCATION;
  درخت std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  منطقي دیده = خطأ;
  صحيح cnt = 0;
  لكل (درخت attr = std_attrs; attr; attr = درخت_CHAIN (attr))
    إذا (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	لكل (درخت a = درخت_مقدار (attr); a; a = درخت_CHAIN (a))
	  {
	    درخت d = درخت_مقدار (a);
	    gcc_assert (درخت_کد (d) == C_TOKEN_VEC);
	    c_token *اولی = C_TOKEN_VEC_نشانهها (d)->آدرس ();
	    cnt++;
	    إذا (اولی->type == CPP_NAME
		&& strcmp (IDENTIFIER_اشاره_گر (اولی->مقدار),
			   directive) == 0)
	      {
		دیده = درست;
		إذا (میانه_loc == UNKNOWN_LOCATION)
		  میانه_loc = اولی->location;
	      }
	  }
      }
  إذا (!دیده)
    أرجع خطأ;
  إذا (cnt != 1 || درخت_CHAIN (std_attrs))
    {
      error_at (make_location (اولی_loc, آخرین_loc, میانه_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      أرجع خطأ;
    }
  c_parser_handle_statement_omp_صفات (parser, std_attrs, عدم);
  أرجع درست;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

ساكن درخت
c_parser_omp_structured_بلوک_sequence (c_parser *parser,
					تعداد pragma_نوع نوع)
{
  درخت stmt = افزودن_stmt_list ();
  c_parser_statement (parser, عدم);
  افعل
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	اكسر;
      إذا (c_parser_بعدی_token_is (parser, CPP_EOF))
	اكسر;

      إذا (نوع != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_نوع == نوع)
	اكسر;

      إذا (نوع != PRAGMA_NONE
	  && c_parser_omp_section_پیمایش (parser,
					نوع == PRAGMA_OMP_پیمایش
					? "scan" : "section", خطأ))
	اكسر;

      c_parser_statement (parser, عدم);
    }
  طالما (1);
  أرجع برداشت_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

ساكن فراغ
c_parser_omp_پیمایش_loop_body (c_parser *parser, منطقي open_brace_parsed)
{
  درخت substmt;
  location_t loc;
  درخت clauses = NULL_درخت;
  منطقي یافت_پیمایش = خطأ;

  loc = c_parser_peek_token (parser)->location;
  إذا (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = خطأ;
      أرجع;
    }

  إذا (c_parser_peek_token (parser)->pragma_نوع != PRAGMA_OMP_پیمایش)
    substmt = c_parser_omp_structured_بلوک_sequence (parser, PRAGMA_OMP_پیمایش);
  وإلا
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_خالی_stmt (loc);
    }
  substmt = build2 (OMP_پیمایش, void_type_گره, substmt, NULL_درخت);
  مجموعه_عبارت_LOCATION (substmt, loc);
  جمع_کن_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_peek_token (parser)->pragma_نوع == PRAGMA_OMP_پیمایش)
    {
      تعداد omp_clause_کد clause = OMP_CLAUSE_ERROR;
      یافت_پیمایش = درست;

      c_parser_consume_pragma (parser);

      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	  إذا (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  وإلا إذا (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      إذا (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_درخت);
	}
      وإلا
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_مقصد_pragma_eol (parser);
    }
  وإلا
    error ("expected %<#pragma omp scan%>");

  clauses = c_پایان_omp_clauses (clauses, C_ORT_OMP);
  إذا (!c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_بلوک_sequence (parser, PRAGMA_NONE);
  وإلا
    {
      إذا (یافت_پیمایش)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_خالی_stmt (loc);
    }
  substmt = build2 (OMP_پیمایش, void_type_گره, substmt, clauses);
  مجموعه_عبارت_LOCATION (substmt, loc);
  جمع_کن_stmt (substmt);

  c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
ساكن منطقي
c_parser_omp_بعدی_نشانهها_can_be_canon_loop (c_parser *parser,
					    تعداد درخت_کد_2 کد,
					    منطقي error_p)
{
  إذا (کد == OACC_LOOP)
    {
      إذا (c_parser_بعدی_token_is_keyword (parser, RID_FOR))
	أرجع درست;
      إذا (error_p)
	c_parser_error (parser, "for statement expected");
    }
  وإلا
    {
      إذا (c_parser_بعدی_token_is_keyword (parser, RID_FOR))
	أرجع درست;

      إذا (c_parser_بعدی_token_is (parser, CPP_PRAGMA))
	بدل (c_parser_peek_token (parser)->pragma_نوع)
	  {
	  حالة PRAGMA_OMP_UNROLL:
	  حالة PRAGMA_OMP_TILE:
	    أرجع درست;
	  افتراضي:
	    اكسر;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      اندازه_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      إذا (token->type == CPP_NAME
	  && C_IS_RESERVED_کلمه (token->مقدار)
	  && C_RID_کد (token->مقدار) == RID_FOR)
	أرجع درست;
      إذا (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  أرجع خطأ;
}

ساكن درخت c_parser_omp_tile (location_t, c_parser *, منطقي *);
ساكن درخت c_parser_omp_unroll (location_t, c_parser *, منطقي *);

/* This function parses a single level of a loop nest, invoking itself
   recursively if necessary.

   loop-nest :: for (...) loop-body
   loop-body :: loop-nest
	     |  { [intervening-code] loop-body [intervening-code] }
	     |  final-loop-body
   intervening-code :: structured-block-sequence
   final-loop-body :: structured-block

   For a collapsed loop nest, only a single OMP_FOR is built, pulling out
   all the iterator information from the inner loops into the
   parser->omp_for_parse_state structure.

   The iterator decl, init, cond, and incr are stored in vectors.

   Initialization code for iterator variables is collected into
   parser->omp_for_parse_state->pre_body and ends up inserted directly
   into the OMP_FOR structure.  */

ساكن درخت
c_parser_omp_loop_nest (c_parser *parser, منطقي *if_p)
{
  درخت decl = NULL_درخت, cond = NULL_درخت, incr = NULL_درخت, init = NULL_درخت;
  درخت body = NULL_درخت;
  matching_parens parens;
  منطقي moreloops;
  بیعلامت حرف save_درون_statement;
  درخت loop_scope;
  location_t loc;
  بنية omp_for_parse_داده *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  صحيح عمق = omp_for_parse_state->عمق;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  إذا (c_parser_nth_token_starts_std_صفات (parser, 1))
    {
      درخت std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_صفات (parser, std_attrs, عدم);
      إذا (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_PRAGMA))
    {
      درخت transform = NULL_درخت, sizes, body = NULL_درخت;
      صحيح شمار = 0;
      بدل (c_parser_peek_token (parser)->pragma_نوع)
	{
	حالة PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = افزودن_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = برداشت_stmt_list (body);
	  إذا (transform == NULL_درخت || transform == error_mark_گره)
	    {
	      transform = error_mark_گره;
	      اكسر;
	    }
	  gcc_assert (درخت_کد (transform) == OMP_UNROLL);
	  إذا (omp_پیدا_کن_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      إذا (omp_for_parse_state->شمار - عمق > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->شمار - عمق);
		  transform = error_mark_گره;
		}
	      وإلا
		شمار = 1;
	    }
	  وإلا
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_گره;
	    }
	  اكسر;
	حالة PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = افزودن_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = برداشت_stmt_list (body);
	  إذا (transform == NULL_درخت || transform == error_mark_گره)
	    {
	      transform = error_mark_گره;
	      اكسر;
	    }
	  gcc_assert (درخت_کد (transform) == OMP_TILE);
	  sizes = omp_پیدا_کن_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  شمار = list_درازی (OMP_CLAUSE_SIZES_LIST (sizes));
	  إذا (عمق + شمار < omp_for_parse_state->شمار)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			شمار, omp_for_parse_state->شمار - عمق);
	      transform = error_mark_گره;
	    }
	  اكسر;
	افتراضي:
	  c_parser_pragma (parser, pragma_stmt, عدم, void_list_گره);
	  اكسر;
	}
      إذا (transform == NULL_درخت)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      إذا (transform == NULL_درخت || transform == error_mark_گره)
	{
	  omp_for_parse_state->fail = درست;
	  أرجع NULL_درخت;
	}
      لكل (شمار = omp_for_parse_state->شمار; عمق < شمار; ++عمق)
	{
	  درخت_VEC_ELT (omp_for_parse_state->declv, عمق) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->initv, عمق) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->condv, عمق) = NULL_درخت;
	  درخت_VEC_ELT (omp_for_parse_state->incrv, عمق) = NULL_درخت;
	}
      omp_for_parse_state->want_nested_loop = خطأ;
      أرجع body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_درون_statement = درون_statement;
  درون_statement = درون_OMP_بلوک;

  /* We are not in intervening code now.  */
  omp_for_parse_state->درون_intervening_کد = خطأ;

  إذا (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = درست;
      أرجع NULL_درخت;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (درست);

  /* Parse the initialization declaration or expression.  */
  إذا (c_parser_بعدی_نشانهها_شروع_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      درخت this_pre_body = افزودن_stmt_list ();
      c_درون_omp_for = درست;
      c_parser_declaration_or_fndef (parser, درست, درست, درست, درست, درست,
				     خطأ);
      c_درون_omp_for = خطأ;
      this_pre_body = برداشت_stmt_list (this_pre_body);
      append_مقصد_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      إذا (decl == عدم)
	اذهب error_init;
      إذا (DECL_INITIAL (decl) == error_mark_گره)
	decl = error_mark_گره;
      init = decl;
    }
  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      بنية c_عبارت decl_exp;
      بنية c_عبارت init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_عبارت (parser);
      decl = decl_exp.مقدار;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_عبارت_no_commas (parser, عدم);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_درون_omp_for = درست;
      init = build_modify_عبارت (init_loc, decl, decl_exp.original_type,
				NOP_عبارت, init_loc, init_exp.مقدار,
				init_exp.original_type);
      c_درون_omp_for = خطأ;
      init = c_process_عبارت_stmt (init_loc, init);

      c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  وإلا
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = درست;
      اذهب parse_بعدی;
    }

  /* Parse the loop condition.  */
  إذا (c_parser_بعدی_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_درون_omp_for = درست;
      بنية c_عبارت cond_عبارت
	= c_parser_دودویی_عبارت (parser, عدم, NULL_درخت);
      c_درون_omp_for = خطأ;

      cond = cond_عبارت.مقدار;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      بدل (cond_عبارت.original_کد)
	{
	حالة GT_عبارت:
	حالة GE_عبارت:
	حالة LT_عبارت:
	حالة LE_عبارت:
	  اكسر;
	حالة NE_عبارت:
	  إذا (omp_for_parse_state->کد != OACC_LOOP)
	    اكسر;
	  /* FALLTHRU.  */
	افتراضي:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_عبارت, boolean_type_گره, error_mark_گره);
	  اكسر;
	}
      protected_مجموعه_عبارت_location (cond, cond_loc);
    }
  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  إذا (c_parser_بعدی_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_عبارت_stmt (incr_loc,
				  c_parser_عبارت (parser).مقدار);
    }
  parens.skip_until_یافت_close (parser);

  إذا (decl == عدم || decl == error_mark_گره || init == error_mark_گره)
    omp_for_parse_state->fail = درست;
  وإلا
    {
      درخت_VEC_ELT (omp_for_parse_state->declv, عمق) = decl;
      درخت_VEC_ELT (omp_for_parse_state->initv, عمق) = init;
      درخت_VEC_ELT (omp_for_parse_state->condv, عمق) = cond;
      درخت_VEC_ELT (omp_for_parse_state->incrv, عمق) = incr;
    }

parse_بعدی:
  moreloops = عمق < omp_for_parse_state->شمار - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  إذا (moreloops
      && c_parser_omp_بعدی_نشانهها_can_be_canon_loop (parser,
						     omp_for_parse_state->کد,
						     خطأ))
    {
      omp_for_parse_state->عمق++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->عمق--;
    }
  وإلا إذا (moreloops && c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->درون_intervening_کد = درست;
      body = c_parser_compound_statement (parser, عدم);
      omp_for_parse_state->درون_intervening_کد = خطأ;
      إذا (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = درست;
	}
      if_p = عدم;
    }
  وإلا
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      إذا (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = درست;
	}
      درون_statement = درون_OMP_FOR;
      parser->omp_for_parse_state = عدم;
      body = افزودن_stmt_list ();
      إذا (omp_for_parse_state->inscan)
	c_parser_omp_پیمایش_loop_body (parser, خطأ);
      وإلا
	جمع_کن_stmt (c_parser_c99_بلوک_statement (parser, if_p));
      body = برداشت_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  درون_statement = save_درون_statement;
  omp_for_parse_state->want_nested_loop = خطأ;
  omp_for_parse_state->درون_intervening_کد = درست;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  إذا (body)
    جمع_کن_stmt (body);
  body = c_انتها_compound_stmt (loc, loop_scope, درست);
  إذا (decl && درخت_کد (body) == BIND_عبارت)
    {
      درخت t = BIND_عبارت_VARS (body);
      درخت prev = NULL_درخت, بعدی = NULL_درخت;
      طالما (t)
	{
	  بعدی = DECL_CHAIN (t);
	  إذا (t == decl)
	    {
	      إذا (prev)
		DECL_CHAIN (prev) = بعدی;
	      وإلا
		{
		  BIND_عبارت_VARS (body) = بعدی;
		  بلوک_VARS (BIND_عبارت_بلوک (body)) = بعدی;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      اكسر;
	    }
	  وإلا
	    {
	      prev = t;
	      t = بعدی;
	    }
	}
      إذا (BIND_عبارت_VARS (body) == NULL_درخت)
	body = BIND_عبارت_BODY (body);
    }

  أرجع body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

ساكن درخت
c_parser_omp_for_loop (location_t loc, c_parser *parser, تعداد درخت_کد_2 کد,
		       درخت clauses, درخت *cclauses, منطقي *if_p)
{
  درخت body, stmt, cl;
  درخت ret = NULL_درخت;
  درخت ordered_cl = NULL_درخت;
  صحيح i, collapse = 1, ordered = 0, شمار;
  منطقي oacc_tiling = خطأ;
  منطقي inscan = خطأ;
  بنية omp_for_parse_داده داده;
  بنية omp_for_parse_داده *save_داده = parser->omp_for_parse_state;

  لكل (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    إذا (OMP_CLAUSE_کد (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = درخت_مقصد_shwi (OMP_CLAUSE_COLLAPSE_عبارت (cl));
    وإلا إذا (OMP_CLAUSE_کد (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = درست;
	collapse = list_درازی (OMP_CLAUSE_TILE_LIST (cl));
      }
    وإلا إذا (OMP_CLAUSE_کد (cl) == OMP_CLAUSE_SIZES)
      collapse = list_درازی (OMP_CLAUSE_SIZES_LIST (cl));
    وإلا إذا (OMP_CLAUSE_کد (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_عبارت (cl))
      {
	ordered_cl = cl;
	ordered = درخت_مقصد_shwi (OMP_CLAUSE_ORDERED_عبارت (cl));
      }
    وإلا إذا (OMP_CLAUSE_کد (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (کد == OMP_SIMD || کد == OMP_FOR))
      inscan = درست;

  إذا (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_عبارت (ordered_cl)
	= build_int_cst (integer_type_گره, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  شمار = ordered ? ordered : collapse;

  إذا (!c_parser_omp_بعدی_نشانهها_can_be_canon_loop (parser, کد, درست))
    أرجع عدم;

  /* Initialize parse state for recursive descent.  */
  داده.declv = make_درخت_vec (شمار);
  داده.initv = make_درخت_vec (شمار);
  داده.condv = make_درخت_vec (شمار);
  داده.incrv = make_درخت_vec (شمار);
  داده.pre_body = NULL_درخت;
  داده.bindings = NULL_درخت;
  داده.for_loc = c_parser_peek_token (parser)->location;
  داده.شمار = شمار;
  داده.عمق = 0;
  داده.want_nested_loop = درست;
  داده.ordered = ordered > 0;
  داده.درون_intervening_کد = خطأ;
  داده.perfect_nesting_fail = خطأ;
  داده.fail = خطأ;
  داده.inscan = inscan;
  داده.saw_intervening_کد = خطأ;
  داده.کد = کد;
  parser->omp_for_parse_state = &داده;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  لكل (درخت t = داده.bindings; t; )
    {
      درخت n = درخت_CHAIN (t);
      درخت_CHAIN (t) = NULL_درخت;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  إذا (!داده.fail)
    {
      c_درون_omp_for = درست;
      stmt = c_پایان_omp_for (loc, کد, داده.declv, عدم, داده.initv,
			       داده.condv, داده.incrv,
			       body, داده.pre_body, درست);
      c_درون_omp_for = خطأ;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      إذا (stmt && !c_omp_check_loop_iv (stmt, داده.declv, عدم))
	stmt = NULL_درخت;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      إذا (داده.saw_intervening_کد
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, عدم))
	stmt = NULL_درخت;

      إذا (stmt)
	{
	  جمع_کن_stmt (stmt);

	  لكل (i = 0; i < درخت_VEC_درازی (OMP_FOR_INIT (stmt)); i++)
	    {
	      درخت init = درخت_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      إذا (init == NULL_درخت)
		اكسر;
	      gcc_assert (درخت_کد (init) == MODIFY_عبارت);
	      درخت decl = درخت_عملوند (init, 0);
	      درخت cond = درخت_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (درخت_عملوند (cond, 0) == decl);

	      درخت op0 = درخت_عملوند (init, 1);
	      إذا (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || درخت_کد (op0) != درخت_VEC)
		درخت_عملوند (init, 1) = c_fully_fold (op0, خطأ, عدم);
	      وإلا
		{
		  درخت_VEC_ELT (op0, 1)
		    = c_fully_fold (درخت_VEC_ELT (op0, 1), خطأ, عدم);
		  درخت_VEC_ELT (op0, 2)
		    = c_fully_fold (درخت_VEC_ELT (op0, 2), خطأ, عدم);
		}

	      درخت op1 = درخت_عملوند (cond, 1);
	      إذا (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || درخت_کد (op1) != درخت_VEC)
		درخت_عملوند (cond, 1) = c_fully_fold (op1, خطأ, عدم);
	      وإلا
		{
		  درخت_VEC_ELT (op1, 1)
		    = c_fully_fold (درخت_VEC_ELT (op1, 1), خطأ, عدم);
		  درخت_VEC_ELT (op1, 2)
		    = c_fully_fold (درخت_VEC_ELT (op1, 2), خطأ, عدم);
		}
	    }

	  إذا (cclauses != عدم
	      && cclauses[C_OMP_CLAUSE_تقسیم_PARALLEL] != عدم)
	    {
	      درخت *c;
	      لكل (c = &cclauses[C_OMP_CLAUSE_تقسیم_PARALLEL]; *c ; )
		إذا (OMP_CLAUSE_کد (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_کد (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		وإلا
		  {
		    لكل (i = 0; i < شمار; i++)
		      إذا (درخت_VEC_ELT (داده.declv, i) == OMP_CLAUSE_DECL (*c))
			اكسر;
		    إذا (i == شمار)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    وإلا إذا (OMP_CLAUSE_کد (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    وإلا
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			درخت l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			إذا (کد == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_تقسیم_FOR];
			    cclauses[C_OMP_CLAUSE_تقسیم_FOR] = l;
			  }
			وإلا
			  {
			    OMP_CLAUSE_CHAIN (l) = clauses;
			    clauses = l;
			  }
		      }
		  }
	    }
	  OMP_FOR_CLAUSES (stmt) = clauses;
	}
      ret = stmt;
    }

  parser->omp_for_parse_state = save_داده;
  أرجع ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

ساكن فراغ
omp_تقسیم_clauses (location_t loc, تعداد درخت_کد_2 کد,
		   omp_clause_ماسک ماسک, درخت clauses, درخت *cclauses)
{
  صحيح i;
  c_omp_تقسیم_clauses (loc, کد, ماسک, clauses, cclauses);
  لكل (i = 0; i < C_OMP_CLAUSE_تقسیم_شمار; i++)
    إذا (cclauses[i])
      cclauses[i] = c_پایان_omp_clauses (cclauses[i],
					  i == C_OMP_CLAUSE_تقسیم_هدف
					  ? C_ORT_OMP_هدف : C_ORT_OMP);
}

/* OpenMP 5.0:
   #pragma omp loop loop-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#تعریف_کن OMP_LOOP_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_BIND)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ترتیب))

ساكن درخت
c_parser_omp_loop (location_t loc, c_parser *parser,
		   حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
		   منطقي *if_p)
{
  درخت بلوک, clauses, ret;

  strcat (p_name, " loop");
  ماسک |= OMP_LOOP_CLAUSE_ماسک;

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_LOOP, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_LOOP];
    }

  بلوک = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع ret;
}

/* OpenMP 4.0:
   #pragma omp simd simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#تعریف_کن OMP_SIMD_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SAFELEN)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خطی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NONTEMPORAL)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ترتیب))

ساكن درخت
c_parser_omp_simd (location_t loc, c_parser *parser,
		   حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
		   منطقي *if_p)
{
  درخت بلوک, clauses, ret;

  strcat (p_name, " simd");
  ماسک |= OMP_SIMD_CLAUSE_ماسک;

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_SIMD, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_SIMD];
    }

  بلوک = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع ret;
}

/* OpenMP 2.5:
   #pragma omp for for-clause[optseq] new-line
     for-loop

   OpenMP 4.0:
   #pragma omp for simd for-simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#تعریف_کن OMP_FOR_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خطی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ORDERED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_زمانبندی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ترتیب))

ساكن درخت
c_parser_omp_for (location_t loc, c_parser *parser,
		  حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
		  منطقي *if_p)
{
  درخت بلوک, clauses, ret;

  strcat (p_name, " for");
  ماسک |= OMP_FOR_CLAUSE_ماسک;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  إذا (cclauses && (ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    ماسک &= ~(OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  إذا ((ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DIST_زمانبندی)) != 0)
    ماسک &= ~(OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      إذا (strcmp (p, "simd") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_simd (loc, parser, p_name, ماسک, cclauses,
				      if_p);
	  بلوک = c_begin_compound_stmt (درست);
	  ret = c_parser_omp_simd (loc, parser, p_name, ماسک, cclauses, if_p);
	  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
	  إذا (ret == NULL_درخت)
	    أرجع ret;
	  ret = make_گره (OMP_FOR);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_FOR_BODY (ret) = بلوک;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_تقسیم_FOR];
	  مجموعه_عبارت_LOCATION (ret, loc);
	  جمع_کن_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع NULL_درخت;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  إذا ((ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DIST_زمانبندی)) != 0)
    ماسک &= ~(OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خطی);

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_FOR, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_FOR];
    }

  بلوک = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع ret;
}

ساكن درخت c_parser_omp_taskloop (location_t, c_parser *, حرف *,
				   omp_clause_ماسک, درخت *, منطقي *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

ساكن درخت
c_parser_omp_master (location_t loc, c_parser *parser,
		     حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
		     منطقي *if_p, location_t master_loc)
{
  درخت بلوک, clauses, ret;
  gcc_rich_location richloc (loc);
  إذا (master_loc != UNKNOWN_LOCATION)
    richloc.جمع_کن_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      إذا (strcmp (p, "taskloop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_taskloop (loc, parser, p_name, ماسک, cclauses,
					  if_p);
	  بلوک = c_begin_compound_stmt (درست);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, ماسک, cclauses,
				       if_p);
	  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
	  إذا (ret == NULL_درخت)
	    أرجع ret;
	  ret = c_پایان_omp_master (loc, بلوک);
	  OMP_MASTER_COMBINED (ret) = 1;
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع NULL_درخت;
    }

  إذا (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, خطأ);
      omp_تقسیم_clauses (loc, OMP_MASTER, ماسک, clauses, cclauses);
    }
  وإلا
    c_parser_skip_مقصد_pragma_eol (parser);

  أرجع c_پایان_omp_master (loc, c_parser_omp_structured_بلوک (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#تعریف_کن OMP_MASKED_CLAUSE_ماسک					\
	(OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FILTER)

ساكن درخت
c_parser_omp_masked (location_t loc, c_parser *parser,
		     حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
		     منطقي *if_p)
{
  درخت بلوک, clauses, ret;

  strcat (p_name, " masked");
  ماسک |= OMP_MASKED_CLAUSE_ماسک;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      إذا (strcmp (p, "taskloop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_taskloop (loc, parser, p_name, ماسک, cclauses,
					  if_p);
	  بلوک = c_begin_compound_stmt (درست);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, ماسک, cclauses,
				       if_p);
	  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
	  إذا (ret == NULL_درخت)
	    أرجع ret;
	  ret = c_پایان_omp_masked (loc, بلوک,
				     cclauses[C_OMP_CLAUSE_تقسیم_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_MASKED, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_MASKED];
    }

  أرجع c_پایان_omp_masked (loc, c_parser_omp_structured_بلوک (parser,
								  if_p),
			      clauses);
}

/* OpenMP 5.1:
   # pragma omp interop clauses[opt] new-line */

#تعریف_کن OMP_INTEROP_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DESTROY)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_INIT)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_USE))

ساكن فراغ
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_ماسک,
					   "#pragma omp interop");
  درخت stmt = make_گره (OMP_INTEROP);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);
}

/* OpenMP 2.5:
   # pragma omp ordered new-line
     structured-block

   OpenMP 4.5:
   # pragma omp ordered ordered-clauses new-line
     structured-block

   # pragma omp ordered depend-clauses new-line

   OpenMP 5.2
   # pragma omp ordered doacross-clauses new-line  */

#تعریف_کن OMP_ORDERED_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_نخها)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SIMD))

#تعریف_کن OMP_ORDERED_DEPEND_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DOACROSS))

ساكن منطقي
c_parser_omp_ordered (c_parser *parser, تعداد pragma_context context,
		      منطقي *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  إذا (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع خطأ;
    }

  صحيح n = 1;
  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
    n = 2;

  إذا (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ثابت حرف *p
	= IDENTIFIER_اشاره_گر (c_parser_peek_nth_token (parser, n)->مقدار);

      إذا (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  إذا (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	      أرجع خطأ;
	    }
	  إذا (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	      أرجع درست;
	    }

	  درخت clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_ماسک,
					"#pragma omp ordered");
	  c_پایان_omp_ordered (loc, clauses, NULL_درخت);
	  أرجع خطأ;
	}
    }

  درخت clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_ماسک,
					   "#pragma omp ordered");

  إذا (!flag_openmp	/* flag_openmp_simd  */
      && omp_پیدا_کن_clause (clauses, OMP_CLAUSE_SIMD) == NULL_درخت)
    أرجع خطأ;

  c_پایان_omp_ordered (loc, clauses,
			c_parser_omp_structured_بلوک (parser, if_p));
  أرجع درست;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

ساكن درخت
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  درخت stmt, substmt;
  منطقي error_suppress = خطأ;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = خطأ;
      أرجع NULL_درخت;
    }

  stmt = افزودن_stmt_list ();

  إذا (c_parser_peek_token (parser)->pragma_نوع != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_پیمایش (parser, "section", درست))
    {
      substmt = c_parser_omp_structured_بلوک_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_گره, substmt);
      مجموعه_عبارت_LOCATION (substmt, loc);
      جمع_کن_stmt (substmt);
    }

  طالما (1)
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
	اكسر;
      إذا (c_parser_بعدی_token_is (parser, CPP_EOF))
	اكسر;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_پیمایش (parser, "section", خطأ);
      إذا (c_parser_peek_token (parser)->pragma_نوع == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_مقصد_pragma_eol (parser);
	  error_suppress = خطأ;
	}
      وإلا إذا (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = درست;
	}

      substmt = c_parser_omp_structured_بلوک_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_گره, substmt);
      مجموعه_عبارت_LOCATION (substmt, loc);
      جمع_کن_stmt (substmt);
    }
  c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = برداشت_stmt_list (stmt);

  stmt = make_گره (OMP_SECTIONS);
  مجموعه_عبارت_LOCATION (stmt, sections_loc);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_SECTIONS_BODY (stmt) = substmt;

  أرجع جمع_کن_stmt (stmt);
}

/* OpenMP 2.5:
   # pragma omp sections sections-clause[optseq] newline
     sections-scope

   LOC is the location of the #pragma token.
*/

#تعریف_کن OMP_SECTIONS_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن درخت
c_parser_omp_sections (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses)
{
  درخت بلوک, clauses, ret;

  strcat (p_name, " sections");
  ماسک |= OMP_SECTIONS_CLAUSE_ماسک;
  إذا (cclauses)
    ماسک &= ~(OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_SECTIONS, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_SECTIONS];
    }

  بلوک = c_begin_compound_stmt (درست);
  ret = c_parser_omp_sections_scope (loc, parser);
  إذا (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع ret;
}

/* OpenMP 2.5:
   # pragma omp parallel parallel-clause[optseq] new-line
     structured-block
   # pragma omp parallel for parallel-for-clause[optseq] new-line
     structured-block
   # pragma omp parallel sections parallel-sections-clause[optseq] new-line
     structured-block

   OpenMP 4.0:
   # pragma omp parallel for simd parallel-for-simd-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#تعریف_کن OMP_PARALLEL_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_COPYIN)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_رقم_نخها)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

ساكن درخت
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
		       منطقي *if_p)
{
  درخت stmt, clauses, بلوک;

  strcat (p_name, " parallel");
  ماسک |= OMP_PARALLEL_CLAUSE_ماسک;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  إذا ((ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DIST_زمانبندی)) == 0)
    ماسک &= ~(OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  إذا (c_parser_بعدی_token_is_keyword (parser, RID_FOR))
    {
      درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
      إذا (cclauses == عدم)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      إذا (!flag_openmp)  /* flag_openmp_simd  */
	أرجع c_parser_omp_for (loc, parser, p_name, ماسک, cclauses, if_p);
      بلوک = c_begin_omp_parallel ();
      درخت ret = c_parser_omp_for (loc, parser, p_name, ماسک, cclauses, if_p);
      stmt
	= c_پایان_omp_parallel (loc, cclauses[C_OMP_CLAUSE_تقسیم_PARALLEL],
				 بلوک);
      إذا (ret == NULL_درخت)
	أرجع ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      أرجع stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  وإلا إذا (cclauses
	   && (ماسک & (OMP_CLAUSE_ماسک_1
		       << PRAGMA_OMP_CLAUSE_DIST_زمانبندی)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_مقصد_pragma_eol (parser);
      أرجع NULL_درخت;
    }
  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      location_t ploc = c_parser_peek_token (parser)->location;
      إذا (cclauses == عدم && strcmp (p, "masked") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_masked (loc, parser, p_name, ماسک, cclauses,
					if_p);
	  بلوک = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_masked (loc, parser, p_name, ماسک, cclauses,
					  if_p);
	  stmt = c_پایان_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_تقسیم_PARALLEL],
					بلوک);
	  إذا (ret == عدم)
	    أرجع ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  إذا (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
      وإلا إذا (cclauses == عدم && strcmp (p, "master") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_master (loc, parser, p_name, ماسک, cclauses,
					if_p, ploc);
	  بلوک = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_master (loc, parser, p_name, ماسک, cclauses,
					  if_p, ploc);
	  stmt = c_پایان_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_تقسیم_PARALLEL],
					بلوک);
	  إذا (ret == عدم)
	    أرجع ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  إذا (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
      وإلا إذا (strcmp (p, "loop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_loop (loc, parser, p_name, ماسک, cclauses,
				      if_p);
	  بلوک = c_begin_omp_parallel ();
	  درخت ret = c_parser_omp_loop (loc, parser, p_name, ماسک, cclauses,
					if_p);
	  stmt
	    = c_پایان_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_تقسیم_PARALLEL],
				     بلوک);
	  إذا (ret == NULL_درخت)
	    أرجع ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
      وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  أرجع NULL_درخت;
	}
      وإلا إذا (cclauses == عدم && strcmp (p, "sections") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  بلوک = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, ماسک, cclauses);
	  stmt = c_پایان_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_تقسیم_PARALLEL],
					بلوک);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
    }
  وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_PARALLEL, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_PARALLEL];
    }

  بلوک = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = درست;
  c_parser_statement (parser, if_p);
  stmt = c_پایان_omp_parallel (loc, clauses, بلوک);

  أرجع stmt;
}

/* OpenMP 2.5:
   # pragma omp single single-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#تعریف_کن OMP_SINGLE_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_COPYPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن درخت
c_parser_omp_single (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت stmt = make_گره (OMP_SINGLE);
  مجموعه_عبارت_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گره;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_ماسک,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_بلوک (parser, if_p);

  أرجع جمع_کن_stmt (stmt);
}

/* OpenMP 5.1:
   # pragma omp scope scope-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#تعریف_کن OMP_SCOPE_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن درخت
c_parser_omp_scope (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت stmt = make_گره (OMP_SCOPE);
  مجموعه_عبارت_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گره;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_ماسک,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_بلوک (parser, if_p);

  أرجع جمع_کن_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
ساكن درخت
c_parser_omp_dispatch_body (c_parser *parser)
{
  بنية c_عبارت lhs, rhs, ret;
  location_t عبارت_loc = c_parser_peek_token (parser)->location;
  منبع_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_عبارت (parser, عدم, عدم);
  إذا (درخت_کد (lhs.مقدار) == CALL_عبارت)
    أرجع lhs.مقدار;

  location_t op_location = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    أرجع error_mark_گره;

  /* Parse function name.  */
  إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      أرجع error_mark_گره;
    }
  عبارت_loc = c_parser_peek_token (parser)->location;
  درخت id = c_parser_peek_token (parser)->مقدار;
  c_parser_consume_token (parser);
  إذا (!c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      أرجع error_mark_گره;
    }

  rhs.مقدار = build_external_ref (عبارت_loc, id, درست, &rhs.original_type);
  مجموعه_c_عبارت_منبع_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_عبارت_after_primary (
    parser, عبارت_LOC_OR_LOC (rhs.مقدار, عبارت_loc), rhs);
  إذا (درخت_کد (rhs.مقدار) != CALL_عبارت)
    {
      error_at (عبارت_LOC_OR_LOC (rhs.مقدار, عبارت_loc),
		"expected target-function call");
      أرجع error_mark_گره;
    }

  /* Build assignment. */
  rhs = convert_lvalue_مقصد_rvalue (عبارت_loc, rhs, درست, درست);
  ret.مقدار
    = build_modify_عبارت (op_location, lhs.مقدار, lhs.original_type, NOP_عبارت,
			 عبارت_loc, rhs.مقدار, rhs.original_type);
  ret.m_decimal = 0;
  مجموعه_c_عبارت_منبع_range (&ret, lhs.get_شروع (), rhs.get_پایان ());
  ret.original_کد = MODIFY_عبارت;
  ret.original_type = عدم;
  أرجع ret.مقدار;
}

/* OpenMP 5.1:
   # pragma omp dispatch dispatch-clause[optseq] new-line
     expression-stmt

   LOC is the location of the #pragma.
*/

#تعریف_کن OMP_DISPATCH_CLAUSE_ماسک                                               \
  ((OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE)                             \
   | (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)                           \
   | (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOVARIANTS)                       \
   | (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOCONTEXT)                        \
   | (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR)                  \
   | (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_INTEROP)                          \
   | (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)                    \
   | (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن درخت
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  درخت stmt = make_گره (OMP_DISPATCH);
  مجموعه_عبارت_LOCATION (stmt, loc);
  درخت_TYPE (stmt) = void_type_گره;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_ماسک,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  درخت depend_clauses = NULL_درخت;
  درخت *depend_clauses_ptr = &depend_clauses;
  لكل (درخت c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  إذا (depend_clauses != NULL_درخت)
    {
      درخت stmt = make_گره (OMP_TASK);
      درخت_TYPE (stmt) = void_گره;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_درخت;
      مجموعه_عبارت_LOCATION (stmt, loc);
      جمع_کن_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  درخت dispatch_body = c_parser_omp_dispatch_body (parser);
  إذا (dispatch_body == error_mark_گره)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser);
      أرجع NULL_درخت;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (درخت_کد (dispatch_body) == CALL_عبارت
	      || درخت_کد (dispatch_body) == MODIFY_عبارت);
  درخت *dispatch_call = درخت_کد (dispatch_body) == MODIFY_عبارت
			  ? &درخت_عملوند (dispatch_body, 1)
			  : &dispatch_body;
  طالما (درخت_کد (*dispatch_call) == FLOAT_عبارت
	 || درخت_کد (*dispatch_call) == CONVERT_عبارت
	 || درخت_کد (*dispatch_call) == NOP_عبارت)
    dispatch_call = &درخت_عملوند (*dispatch_call, 0);
  *dispatch_call = build_call_عبارت_داخلی_loc (
    loc, IFN_GOMP_DISPATCH,
    درخت_TYPE (درخت_TYPE (CALL_عبارت_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_یافت (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  أرجع جمع_کن_stmt (stmt);
}

/* OpenMP 3.0:
   # pragma omp task task-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#تعریف_کن OMP_TASK_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_اولویت)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_درون_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DETACH)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_AFFINITY))

ساكن درخت
c_parser_omp_task (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت clauses, بلوک;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_ماسک,
				      "#pragma omp task");

  بلوک = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = درست;
  c_parser_statement (parser, if_p);
  أرجع c_پایان_omp_task (loc, clauses, بلوک);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#تعریف_کن OMP_TASKWAIT_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن فراغ
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_ماسک,
				"#pragma omp taskwait");

  إذا (clauses)
    {
      درخت stmt = make_گره (OMP_TASK);
      درخت_TYPE (stmt) = void_گره;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_درخت;
      مجموعه_عبارت_LOCATION (stmt, loc);
      جمع_کن_stmt (stmt);
    }
  وإلا
    c_پایان_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

ساكن فراغ
c_parser_omp_taskyield (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);

  c_پایان_omp_taskyield (loc);
}

/* OpenMP 4.0:
   # pragma omp taskgroup new-line

   OpenMP 5.0:
   # pragma omp taskgroup taskgroup-clause[optseq] new-line
*/

#تعریف_کن OMP_TASKGROUP_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_TASK_REDUCTION))

ساكن درخت
c_parser_omp_taskgroup (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_ماسک,
					   "#pragma omp taskgroup");

  درخت body = c_parser_omp_structured_بلوک (parser, if_p);
  أرجع c_پایان_omp_taskgroup (loc, body, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancel cancel-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#تعریف_کن OMP_CANCEL_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_TASKGROUP)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF))

ساكن فراغ
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_ماسک,
					   "#pragma omp cancel");

  c_پایان_omp_cancel (loc, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancellation point cancelpt-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#تعریف_کن OMP_CANCELLATION_نقطه_CLAUSE_ماسک			\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_TASKGROUP))

ساكن منطقي
c_parser_omp_cancellation_نقطه (c_parser *parser, تعداد pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت clauses;
  منطقي نقطه_دیده = خطأ;

  c_parser_consume_pragma (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  نقطه_دیده = درست;
	}
    }
  إذا (!نقطه_دیده)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_مقصد_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (context != pragma_compound)
    {
      إذا (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      وإلا
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع درست;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_نقطه_CLAUSE_ماسک,
				"#pragma omp cancellation point");

  c_پایان_omp_cancellation_نقطه (loc, clauses);
  أرجع درست;
}

/* OpenMP 4.0:
   #pragma omp distribute distribute-clause[optseq] new-line
     for-loop  */

#تعریف_کن OMP_DISTRIBUTE_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DIST_زمانبندی)\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ترتیب))

ساكن درخت
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
			 منطقي *if_p)
{
  درخت clauses, بلوک, ret;

  strcat (p_name, " distribute");
  ماسک |= OMP_DISTRIBUTE_CLAUSE_ماسک;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      منطقي simd = خطأ;
      منطقي parallel = خطأ;

      إذا (strcmp (p, "simd") == 0)
	simd = درست;
      وإلا
	parallel = strcmp (p, "parallel") == 0;
      إذا (parallel || simd)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      إذا (simd)
		أرجع c_parser_omp_simd (loc, parser, p_name, ماسک, cclauses,
					  if_p);
	      وإلا
		أرجع c_parser_omp_parallel (loc, parser, p_name, ماسک,
					      cclauses, if_p);
	    }
	  بلوک = c_begin_compound_stmt (درست);
	  إذا (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, ماسک, cclauses,
				     if_p);
	  وإلا
	    ret = c_parser_omp_parallel (loc, parser, p_name, ماسک, cclauses,
					 if_p);
	  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
	  إذا (ret == عدم)
	    أرجع ret;
	  ret = make_گره (OMP_DISTRIBUTE);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_FOR_BODY (ret) = بلوک;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_تقسیم_DISTRIBUTE];
	  مجموعه_عبارت_LOCATION (ret, loc);
	  جمع_کن_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_DISTRIBUTE, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_DISTRIBUTE];
    }

  بلوک = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, عدم,
			       if_p);
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#تعریف_کن OMP_TEAMS_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_رقم_TEAMS)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_THREAD_حد)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

ساكن درخت
c_parser_omp_teams (location_t loc, c_parser *parser,
		    حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
		    منطقي *if_p)
{
  درخت clauses, بلوک, ret;

  strcat (p_name, " teams");
  ماسک |= OMP_TEAMS_CLAUSE_ماسک;

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "distribute") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_distribute (loc, parser, p_name, ماسک,
					    cclauses, if_p);
	  بلوک = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, ماسک, cclauses,
					 if_p);
	  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
	  إذا (ret == عدم)
	    أرجع ret;
	  clauses = cclauses[C_OMP_CLAUSE_تقسیم_TEAMS];
	  ret = make_گره (OMP_TEAMS);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = بلوک;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  مجموعه_عبارت_LOCATION (ret, loc);
	  أرجع جمع_کن_stmt (ret);
	}
      وإلا إذا (strcmp (p, "loop") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_loop (loc, parser, p_name, ماسک, cclauses,
				      if_p);
	  بلوک = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, ماسک, cclauses, if_p);
	  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
	  إذا (ret == عدم)
	    أرجع ret;
	  clauses = cclauses[C_OMP_CLAUSE_تقسیم_TEAMS];
	  ret = make_گره (OMP_TEAMS);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = بلوک;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  مجموعه_عبارت_LOCATION (ret, loc);
	  أرجع جمع_کن_stmt (ret);
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_TEAMS, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_TEAMS];
    }

  درخت stmt = make_گره (OMP_TEAMS);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  بلوک = c_begin_omp_parallel ();
  جمع_کن_stmt (c_parser_omp_structured_بلوک (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_انتها_compound_stmt (loc, بلوک, درست);
  مجموعه_عبارت_LOCATION (stmt, loc);

  أرجع جمع_کن_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target data target-data-clause[optseq] new-line
     structured-block  */

#تعریف_کن OMP_هدف_داده_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR) \
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR))

ساكن درخت
c_parser_omp_هدف_داده (location_t loc, c_parser *parser, منطقي *if_p)
{
  إذا (flag_openmp)
    omp_requires_ماسک
      = (تعداد omp_requires) (omp_requires_ماسک | OMP_REQUIRES_هدف_استفاده_شده);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_هدف_داده_CLAUSE_ماسک,
				"#pragma omp target data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_پایان_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_دیده = 0;
  لكل (درخت *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_کد (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_نوع (*pc))
	  {
	  حالة GOMP_MAP_مقصد:
	  حالة GOMP_MAP_ALWAYS_مقصد:
	  حالة GOMP_MAP_PRESENT_مقصد:
	  حالة GOMP_MAP_ALWAYS_PRESENT_مقصد:
	  حالة GOMP_MAP_FROM:
	  حالة GOMP_MAP_ALWAYS_FROM:
	  حالة GOMP_MAP_PRESENT_FROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالة GOMP_MAP_TOFROM:
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	  حالة GOMP_MAP_PRESENT_TOFROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  حالة GOMP_MAP_ALLOC:
	  حالة GOMP_MAP_PRESENT_ALLOC:
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_اشاره_گر:
	  حالة GOMP_MAP_ALWAYS_اشاره_گر:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_ATTACH:
	    اكسر;
	  افتراضي:
	    map_دیده |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      وإلا إذا (OMP_CLAUSE_کد (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_کد (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_دیده = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_دیده != 3)
    {
      إذا (map_دیده == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      أرجع NULL_درخت;
    }

  درخت stmt = make_گره (OMP_هدف_داده);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_هدف_داده_CLAUSES (stmt) = clauses;
  keep_بعدی_level ();
  درخت بلوک = c_begin_compound_stmt (درست);
  جمع_کن_stmt (c_parser_omp_structured_بلوک (parser, if_p));
  OMP_هدف_داده_BODY (stmt) = c_انتها_compound_stmt (loc, بلوک, درست);

  مجموعه_عبارت_LOCATION (stmt, loc);
  أرجع جمع_کن_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target update target-update-clause[optseq] new-line */

#تعریف_کن OMP_هدف_UPDATE_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FROM)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_مقصد)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن منطقي
c_parser_omp_هدف_update (location_t loc, c_parser *parser,
			    تعداد pragma_context context)
{
  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع درست;
    }

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_هدف_UPDATE_CLAUSE_ماسک,
				"#pragma omp target update",
				/* finish_p = */ خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_پایان_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_مقصد) == NULL_درخت
      && omp_پیدا_کن_clause (clauses, OMP_CLAUSE_FROM) == NULL_درخت)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      أرجع خطأ;
    }

  إذا (flag_openmp)
    omp_requires_ماسک
      = (تعداد omp_requires) (omp_requires_ماسک | OMP_REQUIRES_هدف_استفاده_شده);

  درخت stmt = make_گره (OMP_هدف_UPDATE);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_هدف_UPDATE_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);
  أرجع خطأ;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#تعریف_کن OMP_هدف_ENTER_داده_CLAUSE_ماسک			\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن منطقي
c_parser_omp_هدف_enter_داده (location_t loc, c_parser *parser,
				تعداد pragma_context context)
{
  منطقي داده_دیده = خطأ;
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  داده_دیده = درست;
	}
    }
  إذا (!داده_دیده)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_مقصد_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع درست;
    }

  إذا (flag_openmp)
    omp_requires_ماسک
      = (تعداد omp_requires) (omp_requires_ماسک | OMP_REQUIRES_هدف_استفاده_شده);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_هدف_ENTER_داده_CLAUSE_ماسک,
				"#pragma omp target enter data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_پایان_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_دیده = 0;
  لكل (درخت *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_کد (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_نوع (*pc))
	  {
	  حالة GOMP_MAP_مقصد:
	  حالة GOMP_MAP_ALWAYS_مقصد:
	  حالة GOMP_MAP_PRESENT_مقصد:
	  حالة GOMP_MAP_ALWAYS_PRESENT_مقصد:
	  حالة GOMP_MAP_ALLOC:
	  حالة GOMP_MAP_PRESENT_ALLOC:
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_TOFROM:
	    OMP_CLAUSE_مجموعه_MAP_نوع (*pc, GOMP_MAP_مقصد);
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_مجموعه_MAP_نوع (*pc, GOMP_MAP_ALWAYS_مقصد);
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_مجموعه_MAP_نوع (*pc, GOMP_MAP_PRESENT_مقصد);
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_مجموعه_MAP_نوع (*pc, GOMP_MAP_ALWAYS_PRESENT_مقصد);
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_اشاره_گر:
	  حالة GOMP_MAP_ALWAYS_اشاره_گر:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_ATTACH:
	    اكسر;
	  افتراضي:
	    map_دیده |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_دیده != 3)
    {
      إذا (map_دیده == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      أرجع درست;
    }

  درخت stmt = make_گره (OMP_هدف_ENTER_داده);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_هدف_ENTER_داده_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);
  أرجع درست;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#تعریف_کن OMP_هدف_EXIT_داده_CLAUSE_ماسک			\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن منطقي
c_parser_omp_هدف_exit_داده (location_t loc, c_parser *parser,
			       تعداد pragma_context context)
{
  منطقي داده_دیده = خطأ;
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  داده_دیده = درست;
	}
    }
  إذا (!داده_دیده)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_مقصد_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع درست;
    }

  إذا (flag_openmp)
    omp_requires_ماسک
      = (تعداد omp_requires) (omp_requires_ماسک | OMP_REQUIRES_هدف_استفاده_شده);

  درخت clauses
    = c_parser_omp_all_clauses (parser, OMP_هدف_EXIT_داده_CLAUSE_ماسک,
				"#pragma omp target exit data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_داده);
  clauses = c_پایان_omp_clauses (clauses, C_ORT_OMP_EXIT_داده);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_دیده = 0;
  لكل (درخت *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_کد (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_نوع (*pc))
	  {
	  حالة GOMP_MAP_FROM:
	  حالة GOMP_MAP_ALWAYS_FROM:
	  حالة GOMP_MAP_PRESENT_FROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالة GOMP_MAP_RELEASE:
	  حالة GOMP_MAP_DELETE:
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_TOFROM:
	    OMP_CLAUSE_مجموعه_MAP_نوع (*pc, GOMP_MAP_FROM);
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_مجموعه_MAP_نوع (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_مجموعه_MAP_نوع (*pc, GOMP_MAP_PRESENT_FROM);
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_مجموعه_MAP_نوع (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_دیده = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_اشاره_گر:
	  حالة GOMP_MAP_ALWAYS_اشاره_گر:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_DETACH:
	    اكسر;
	  افتراضي:
	    map_دیده |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_دیده != 3)
    {
      إذا (map_دیده == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      أرجع درست;
    }

  درخت stmt = make_گره (OMP_هدف_EXIT_داده);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_هدف_EXIT_داده_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);
  أرجع درست;
}

/* OpenMP 4.0:
   # pragma omp target target-clause[optseq] new-line
     structured-block  */

#تعریف_کن OMP_هدف_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEFAULTMAP)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE) \
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR) \
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_درون_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_THREAD_حد)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_استفاده_میکند_ALLOCATORS))

ساكن منطقي
c_parser_omp_هدف (c_parser *parser, تعداد pragma_context context, منطقي *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت *pc = عدم, stmt, بلوک, body, clauses;

  إذا (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_مقصد_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (flag_openmp)
    omp_requires_ماسک
      = (تعداد omp_requires) (omp_requires_ماسک | OMP_REQUIRES_هدف_استفاده_شده);

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      تعداد درخت_کد_2 ccode = ERROR_MARK;

      إذا (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      وإلا إذا (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      وإلا إذا (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      إذا (ccode != ERROR_MARK)
	{
	  درخت cclauses[C_OMP_CLAUSE_تقسیم_شمار];
	  حرف p_name[حجم ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      درخت stmt;
	      بدل (ccode)
		{
		حالة OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_هدف_CLAUSE_ماسک,
					     cclauses, if_p);
		  اكسر;
		حالة OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_هدف_CLAUSE_ماسک,
						cclauses, if_p);
		  اكسر;
		حالة OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_هدف_CLAUSE_ماسک,
					    cclauses, if_p);
		  اكسر;
		افتراضي:
		  gcc_unreachable ();
		}
	      أرجع stmt != NULL_درخت;
	    }
	  keep_بعدی_level ();
	  درخت بلوک = c_begin_compound_stmt (درست), ret;
	  بدل (ccode)
	    {
	    حالة OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_هدف_CLAUSE_ماسک, cclauses,
					if_p);
	      اكسر;
	    حالة OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_هدف_CLAUSE_ماسک, cclauses,
					   if_p);
	      اكسر;
	    حالة OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_هدف_CLAUSE_ماسک, cclauses,
				       if_p);
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
	  إذا (ret == NULL_درخت)
	    أرجع خطأ;
	  إذا (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    لكل (درخت c = cclauses[C_OMP_CLAUSE_تقسیم_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_رقم_TEAMS
		  || OMP_CLAUSE_کد (c) == OMP_CLAUSE_THREAD_حد)
		لكل (صحيح i = 0;
		     i <= (OMP_CLAUSE_کد (c) == OMP_CLAUSE_رقم_TEAMS); ++i)
		  إذا (OMP_CLAUSE_عملوند (c, i)
		      && درخت_کد (OMP_CLAUSE_عملوند (c, i)) != INTEGER_CST)
		    {
		      درخت عبارت = OMP_CLAUSE_عملوند (c, i);
		      درخت tmp = create_tmp_var_raw (درخت_TYPE (عبارت));
		      عبارت = build4 (هدف_عبارت, درخت_TYPE (عبارت), tmp,
				     عبارت, NULL_درخت, NULL_درخت);
		      جمع_کن_stmt (عبارت);
		      OMP_CLAUSE_عملوند (c, i) = عبارت;
		      درخت tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_تقسیم_هدف];
		      cclauses[C_OMP_CLAUSE_تقسیم_هدف] = tc;
		    }
	  درخت stmt = make_گره (OMP_هدف);
	  درخت_TYPE (stmt) = void_type_گره;
	  OMP_هدف_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_تقسیم_هدف];
	  c_omp_adjust_map_clauses (OMP_هدف_CLAUSES (stmt), درست);
	  OMP_هدف_BODY (stmt) = بلوک;
	  OMP_هدف_COMBINED (stmt) = 1;
	  مجموعه_عبارت_LOCATION (stmt, loc);
	  جمع_کن_stmt (stmt);
	  pc = &OMP_هدف_CLAUSES (stmt);
	  اذهب check_clauses;
	}
      وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  أرجع خطأ;
	}
      وإلا إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_هدف_داده (loc, parser, if_p);
	  أرجع درست;
	}
      وإلا إذا (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_هدف_enter_داده (loc, parser, context);
	}
      وإلا إذا (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_هدف_exit_داده (loc, parser, context);
	}
      وإلا إذا (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_هدف_update (loc, parser, context);
	}
    }
  إذا (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع خطأ;
    }

  stmt = make_گره (OMP_هدف);
  درخت_TYPE (stmt) = void_type_گره;

  clauses = c_parser_omp_all_clauses (parser, OMP_هدف_CLAUSE_ماسک,
				      "#pragma omp target", خطأ);
  لكل (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION)
      {
	درخت nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_مجموعه_MAP_نوع (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_هدف);
  clauses  = c_پایان_omp_clauses (clauses, C_ORT_OMP_هدف);
  c_omp_adjust_map_clauses (clauses, درست);

  keep_بعدی_level ();
  بلوک = c_begin_compound_stmt (درست);
  body = c_parser_omp_structured_بلوک (parser, if_p);

  c_omp_پیمایش_mapper_bindings (loc, &clauses, body);

  جمع_کن_stmt (body);
  OMP_هدف_CLAUSES (stmt) = clauses;
  pc = &OMP_هدف_CLAUSES (stmt);
  OMP_هدف_BODY (stmt) = c_انتها_compound_stmt (loc, بلوک, درست);

  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);

check_clauses:
  طالما (*pc)
    {
      إذا (OMP_CLAUSE_کد (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_نوع (*pc))
	  {
	  حالة GOMP_MAP_مقصد:
	  حالة GOMP_MAP_ALWAYS_مقصد:
	  حالة GOMP_MAP_PRESENT_مقصد:
	  حالة GOMP_MAP_ALWAYS_PRESENT_مقصد:
	  حالة GOMP_MAP_FROM:
	  حالة GOMP_MAP_ALWAYS_FROM:
	  حالة GOMP_MAP_PRESENT_FROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالة GOMP_MAP_TOFROM:
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	  حالة GOMP_MAP_PRESENT_TOFROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  حالة GOMP_MAP_ALLOC:
	  حالة GOMP_MAP_PRESENT_ALLOC:
	  حالة GOMP_MAP_FIRSTPRIVATE_اشاره_گر:
	  حالة GOMP_MAP_ALWAYS_اشاره_گر:
	  حالة GOMP_MAP_اشاره_گر:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_ATTACH:
	    اكسر;
	  افتراضي:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_هدف = درست;
  أرجع درست;
}

/* OpenMP 4.0:
   # pragma omp declare simd declare-simd-clauses[optseq] new-line

   OpenMP 5.0:
   # pragma omp declare variant (identifier) match(context-selector) new-line

   OpenMP 5.1
   # pragma omp declare variant (identifier) match(context-selector) \
      adjust_args(adjust-op:argument-list) append_args(interop-list) new-line
   */

#تعریف_کن OMP_DECLARE_SIMD_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خطی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_یکنواخت)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_INBRANCH)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOTINBRANCH))

ساكن فراغ
c_parser_omp_declare_simd (c_parser *parser, تعداد pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  درخت نوع = token->مقدار;
  gcc_assert (strcmp (IDENTIFIER_اشاره_گر (نوع), "simd") == 0
	      || strcmp (IDENTIFIER_اشاره_گر (نوع), "variant") == 0);

  auto_vec<c_token> clauses;
  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_EOF)
	{
	  c_parser_skip_مقصد_pragma_eol (parser);
	  أرجع;
	}
      clauses.امن_افزودن (*token);
      c_parser_consume_token (parser);
    }
  clauses.امن_افزودن (*c_parser_peek_token (parser));
  c_parser_skip_مقصد_pragma_eol (parser);

  طالما (c_parser_بعدی_token_is (parser, CPP_PRAGMA))
    {
      إذا (c_parser_peek_token (parser)->pragma_نوع != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->مقدار != نوع)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_اشاره_گر (نوع), IDENTIFIER_اشاره_گر (نوع));
	  أرجع;
	}
      c_parser_consume_pragma (parser);
      طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    {
	      c_parser_skip_مقصد_pragma_eol (parser);
	      أرجع;
	    }
	  clauses.امن_افزودن (*token);
	  c_parser_consume_token (parser);
	}
      clauses.امن_افزودن (*c_parser_peek_token (parser));
      c_parser_skip_مقصد_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, حجم (eof_token));
  eof_token.type = CPP_EOF;
  clauses.امن_افزودن (eof_token);
  clauses.امن_افزودن (eof_token);

  بدل (context)
    {
    حالة pragma_external:
      إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, درست, درست, درست, خطأ, درست,
					 خطأ, عدم, &clauses);
	  restore_extension_diagnostics (ext);
	}
      وإلا
	c_parser_declaration_or_fndef (parser, درست, درست, درست, خطأ, درست,
				       خطأ, عدم, &clauses);
      اكسر;
    حالة pragma_struct:
    حالة pragma_param:
    حالة pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_اشاره_گر (نوع));
      اكسر;
    حالة pragma_compound:
      منطقي have_std_attrs;
      درخت std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_صفات (parser, 1);
      إذا (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      وإلا
	std_attrs = NULL_درخت;
      إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  إذا (c_parser_بعدی_نشانهها_شروع_declaration (parser)
	      || c_parser_nth_token_starts_std_صفات (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, درست, درست, درست, درست,
					     درست, خطأ, عدم, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      اكسر;
	    }
	  restore_extension_diagnostics (ext);
	}
      وإلا إذا (c_parser_بعدی_نشانهها_شروع_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, درست, درست, درست, درست, درست,
					 خطأ, عدم, &clauses, have_std_attrs,
					 std_attrs);
	  اكسر;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_اشاره_گر (نوع));
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
}

/* OpenMP 5.0:

   trait-selector:
     trait-selector-name[([trait-score:]trait-property[,trait-property[,...]])]

   trait-score:
     score(score-expression)

   Note that this function returns a list of trait selectors for the
   trait-selector-set SET.  */

ساكن درخت
c_parser_omp_context_selector (c_parser *parser, تعداد omp_tss_کد مجموعه,
			       درخت parms)
{
  درخت ret = NULL_درخت;
  افعل
    {
      درخت selector;
      إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
	  || c_parser_بعدی_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->مقدار;
      وإلا
	{
	  c_parser_error (parser, "expected trait selector name");
	  أرجع error_mark_گره;
	}
      تعداد omp_ts_کد sel
	= omp_lookup_ts_کد (مجموعه, IDENTIFIER_اشاره_گر (selector));

      إذا (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_اشاره_گر (selector),  omp_tss_map[مجموعه]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_درخت, NULL_درخت, ret);
	  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_متوازن_token_sequence (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  وإلا
	    اكسر;
	}

      c_parser_consume_token (parser);

      درخت properties = NULL_درخت;
      درخت scoreval = NULL_درخت;
      تعداد omp_tp_type property_نوع = omp_ts_map[sel].tp_type;
      منطقي allow_score = omp_ts_map[sel].allow_score;
      درخت t;

      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
	{
	  إذا (property_نوع == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_اشاره_گر (selector));
	      أرجع error_mark_گره;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_اشاره_گر (token->مقدار), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      درخت score = c_parser_عبارت_no_commas (parser, عدم).مقدار;
	      parens2.skip_until_یافت_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      إذا (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[مجموعه]);
	      وإلا إذا (score != error_mark_گره)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, خطأ, عدم);
		  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (score))
		      || درخت_کد (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  وإلا إذا (درخت_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  وإلا
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  بدل (property_نوع)
	    {
	    حالة OMP_TRAIT_PROPERTY_ID:
	      إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
		  || c_parser_بعدی_token_is (parser, CPP_NAME))
		{
		  درخت prop = c_parser_peek_token (parser)->مقدار;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_درخت,
						    properties);
		}
	      وإلا
		{
		  c_parser_error (parser, "expected identifier");
		  أرجع error_mark_گره;
		}
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_NAME_LIST:
	      افعل
		{
		  درخت prop = OMP_TP_NAMELIST_گره;
		  درخت مقدار = NULL_درخت;
		  إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
		      || c_parser_بعدی_token_is (parser, CPP_NAME))
		    {
		      مقدار = c_parser_peek_token (parser)->مقدار;
		      c_parser_consume_token (parser);
		    }
		  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_STRING))
		    مقدار = c_parser_string_literal (parser, خطأ,
						     خطأ).مقدار;
		  وإلا
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      أرجع error_mark_گره;
		    }

		  properties = make_trait_property (prop, مقدار, properties);

		  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  وإلا
		    اكسر;
		}
	      طالما (1);
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_DEV_رقم_عبارت:
	    حالة OMP_TRAIT_PROPERTY_BOOL_عبارت:
	      {
		c_عبارت texpr = c_parser_عبارت_no_commas (parser, عدم);
		texpr = convert_lvalue_مقصد_rvalue (token->location, texpr,
						  درست, درست);
		t = texpr.مقدار;
	      }
	      إذا (t == error_mark_گره)
		أرجع error_mark_گره;
	      mark_exp_read (t);
	      إذا (property_نوع == OMP_TRAIT_PROPERTY_BOOL_عبارت)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_گره);
		  إذا (t == error_mark_گره)
		    أرجع error_mark_گره;
		}
	      وإلا إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  أرجع error_mark_گره;
		}
	      t = c_fully_fold (t, خطأ, عدم);
	      properties = make_trait_property (NULL_درخت, t, properties);
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      إذا (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  إذا (parms == NULL_درخت)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      أرجع error_mark_گره;
		    }
		  درخت c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_ماسک,
						"simd", درست, 2);
		  c = c_omp_declare_simd_clauses_مقصد_numbers (parms
							     == error_mark_گره
							     ? NULL_درخت : parms,
							     c);
		  properties = c;
		}
	      وإلا إذا (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  أرجع error_mark_گره;
		}
	      وإلا
		gcc_unreachable ();
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }

	  parens.skip_until_یافت_close (parser);
	  properties = nreverse (properties);
	}
      وإلا إذا (property_نوع != OMP_TRAIT_PROPERTY_NONE
	       && property_نوع != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_نوع != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  أرجع error_mark_گره;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  طالما (1);

  أرجع nreverse (ret);
}

/* OpenMP 5.0:

   trait-set-selector[,trait-set-selector[,...]]

   trait-set-selector:
     trait-set-selector-name = { trait-selector[, trait-selector[, ...]] }

   trait-set-selector-name:
     constructor
     device
     implementation
     user  */

ساكن درخت
c_parser_omp_context_selector_specification (c_parser *parser, درخت parms)
{
  درخت ret = NULL_درخت;
  افعل
    {
      ثابت حرف *setp = "";
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      تعداد omp_tss_کد مجموعه = omp_lookup_tss_کد (setp);

      إذا (مجموعه == OMP_TRAIT_مجموعه_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  أرجع error_mark_گره;
	}

      c_parser_consume_token (parser);

      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	أرجع error_mark_گره;

      matching_braces braces;
      إذا (!braces.require_open (parser))
	أرجع error_mark_گره;

      درخت selectors = c_parser_omp_context_selector (parser, مجموعه, parms);
      إذا (selectors == error_mark_گره)
	{
	  c_parser_skip_مقصد_closing_brace (parser);
	  ret = error_mark_گره;
	}
      وإلا إذا (ret != error_mark_گره)
	ret = make_trait_مجموعه_selector (مجموعه, selectors, ret);

      braces.require_close (parser);

      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  طالما (1);

  إذا (ret == error_mark_گره)
    أرجع ret;
  أرجع nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

ساكن فراغ
c_پایان_omp_declare_variant (c_parser *parser, درخت fndecl, درخت parms)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع;
    }

  إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_نوع != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      اذهب fail;
    }

  c_token *token = c_parser_peek_token (parser);
  درخت variant = lookup_name (token->مقدار);

  إذا (variant == NULL_درخت)
    {
      undeclared_variable (token->location, token->مقدار);
      variant = error_mark_گره;
    }
  وإلا إذا (درخت_کد (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_گره;
    }
  وإلا إذا (fndecl_built_درون_p (variant)
	   && (مقایسه_رشته (IDENTIFIER_اشاره_گر (DECL_NAME (variant)),
			"__builtin_", طول_رشته ("__builtin_")) == 0
	       || مقایسه_رشته (IDENTIFIER_اشاره_گر (DECL_NAME (variant)),
			   "__sync_", طول_رشته ("__sync_")) == 0
	       || مقایسه_رشته (IDENTIFIER_اشاره_گر (DECL_NAME (variant)),
			   "__atomic_", طول_رشته ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_گره;
    }
  وإلا إذا (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_گره;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  درخت append_آرگومانها_درخت = NULL_درخت;
  درخت append_آرگومانها_آخرین;
  vec<درخت> adjust_آرگومانها_list = vNULL;
  منطقي has_تطابق = خطأ, has_adjust_آرگومانها = خطأ;
  location_t adjust_آرگومانها_loc = UNKNOWN_LOCATION;
  location_t append_آرگومانها_loc = UNKNOWN_LOCATION;
  location_t تطابق_loc = UNKNOWN_LOCATION;
  درخت need_device_ptr_list = NULL_درخت;
  درخت ctx = error_mark_گره;

  افعل
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ثابت حرف *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      تعداد clause
      {
	تطابق,
	adjust_آرگومانها,
	append_آرگومانها
      } ccode;

      إذا (strcmp (clause, "match") == 0)
	{
	  ccode = تطابق;
	  تطابق_loc = loc;
	}
      وإلا إذا (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_آرگومانها;
	  adjust_آرگومانها_loc = loc;
	}
      وإلا إذا (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_آرگومانها;
	  append_آرگومانها_loc = loc;
	}
      وإلا
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  اذهب fail;
	}

      c_parser_consume_token (parser);

      إذا (!parens.require_open (parser))
	اذهب fail;

      إذا (parms == NULL_درخت)
	parms = error_mark_گره;

      إذا (ccode == تطابق)
	{
	  إذا (has_تطابق)
	    error_at (تطابق_loc, "too many %<match%> clauses");
	  has_تطابق = درست;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  إذا (ctx == error_mark_گره)
	    اذهب fail;
	  ctx = omp_check_context_selector (تطابق_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  إذا (ctx != error_mark_گره
	      && !vec_امن_is_خالی (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->آخرین ();
	      درخت outer_ctx = a.selector;
	      ctx = omp_ادغام_context_selectors (تطابق_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      وإلا إذا (ccode == adjust_آرگومانها)
	{
	  has_adjust_آرگومانها = درست;
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ثابت حرف *p
		= IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	      إذا (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  درخت list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_درخت);

		  درخت arg;
		  إذا (variant != error_mark_گره)
		    لكل (درخت c = list; c != NULL_درخت; c = درخت_CHAIN (c))
		      {
			درخت decl = درخت_PURPOSE (c);
			location_t arg_loc = عبارت_LOCATION (درخت_مقدار (c));
			صحيح idx;
			لكل (arg = parms, idx = 0; arg != عدم;
			     arg = درخت_CHAIN (arg), idx++)
			  إذا (arg == decl)
			    اكسر;
			إذا (arg == NULL_درخت)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    اذهب fail;
			  }
			إذا (adjust_آرگومانها_list.شامل_است (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    اذهب fail;
			  }
			إذا (strcmp (p, "need_device_ptr") == 0
			    && درخت_کد (درخت_TYPE (arg)) != اشاره_گر_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    اذهب fail;
			  }
			adjust_آرگومانها_list.امن_افزودن (arg);
			إذا (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_درخت_list (
				NULL_درخت,
				build_int_cst (
				  integer_type_گره,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      وإلا
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  إذا (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  اذهب fail;
		}
	    }
	  وإلا
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      اذهب fail;
	    }
	}
      وإلا إذا (ccode == append_آرگومانها)
	{
	  إذا (append_آرگومانها_درخت)
	    {
	      error_at (append_آرگومانها_loc, "too many %qs clauses", "append_args");
	      append_آرگومانها_درخت = NULL_درخت;
	    }
	  افعل
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      إذا (!c_parser_بعدی_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_اشاره_گر (
			       c_parser_peek_token (parser)->مقدار)))
		{
		  error_at (loc, "expected %<interop%>");
		  اذهب fail;
		}
	      c_parser_consume_token (parser);

	      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		اذهب fail;
	      منطقي هدف = خطأ;
	      منطقي targetsync = خطأ;
	      درخت prefer_type_درخت = NULL_درخت;
	      إذا (!c_parser_omp_clause_init_modifiers (parser, &هدف,
						       &targetsync,
						       &prefer_type_درخت)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		اذهب fail;
	      إذا (!هدف && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      درخت t = build_درخت_list (هدف ? boolean_true_گره
					       : boolean_false_گره,
					targetsync ? boolean_true_گره
						   : boolean_false_گره);
	      t = build1_loc (loc, NOP_عبارت, void_type_گره, t);
	      t = build_درخت_list (t, prefer_type_درخت);
	      إذا (append_آرگومانها_درخت)
		{
		  درخت_CHAIN (append_آرگومانها_آخرین) = t;
		  append_آرگومانها_آخرین = t;
		}
	      وإلا
		append_آرگومانها_درخت = append_آرگومانها_آخرین = t;
	      إذا (c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
		اكسر;
	      إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		اذهب fail;
	    }
	  طالما (درست);
	}

      parens.require_close (parser);
  } طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL));
  إذا (variant != error_mark_گره && !has_تطابق)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_گره;
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  إذا (variant == error_mark_گره || ctx == error_mark_گره)
    /* Previously diagnosed error.  */
    أرجع;

  إذا ((has_adjust_آرگومانها || append_آرگومانها_درخت)
      && !omp_get_context_selector (ctx, OMP_TRAIT_مجموعه_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_آرگومانها ? adjust_آرگومانها_loc : append_آرگومانها_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_آرگومانها ? "adjust_args" : "append_args");
      أرجع;
    }

  إذا (!omp_get_context_selector (ctx, OMP_TRAIT_مجموعه_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      درخت پایه_type = درخت_TYPE (fndecl);
      درخت variant_type = درخت_TYPE (variant);
      منطقي unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_درخت
	   && !TYPE_NO_NAMED_آرگومانها_STDARG_P (variant_type));

      إذا (append_آرگومانها_درخت
	  && TYPE_ARG_TYPES (پایه_type) == NULL_درخت
	  && !TYPE_NO_NAMED_آرگومانها_STDARG_P (پایه_type))
	{
	  /* The base function is a pre-C23 unprototyped function.  Without
	     a prototype, we don't know the offset where the append_args go.
	     That offset needs to be stored with the append_args in the
	     variant function attributes, so we cannot presently handle
	     this case.  */
	  sorry_at (append_آرگومانها_loc,
		    "%<append_args%> with unprototyped base function "
		    "is not supported yet");
	  inform (DECL_منبع_LOCATION (fndecl),
		  "base function %qD declared here", fndecl);
	  أرجع;
	}
      وإلا إذا (append_آرگومانها_درخت)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  صحيح nappend_آرگومانها = 0;
	  صحيح nbase_آرگومانها = 0;
	  لكل (درخت t = TYPE_ARG_TYPES (پایه_type);
	       t && درخت_مقدار (t) != void_type_گره; t = درخت_CHAIN (t))
	    nbase_آرگومانها++;
	  لكل (درخت t = append_آرگومانها_درخت; t; t = درخت_CHAIN (t))
	    nappend_آرگومانها++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_آرگومانها_درخت = build_درخت_list (build_int_cst (integer_type_گره,
							     nbase_آرگومانها),
					      append_آرگومانها_درخت);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  إذا (!unprototyped_variant)
	    {
	      درخت آرگومانها = TYPE_ARG_TYPES (variant_type);
	      لكل (صحيح i = 0; آرگومانها && i < nbase_آرگومانها;
		   i++, آرگومانها = درخت_CHAIN (آرگومانها))
		;
	      لكل (صحيح i = 0; i < nappend_آرگومانها; i++, آرگومانها = درخت_CHAIN (آرگومانها))
		إذا (!آرگومانها || !c_omp_interop_t_p (درخت_مقدار (آرگومانها)))
		  {
		    error_at (DECL_منبع_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_آرگومانها + i + 1, variant);
		    inform (append_آرگومانها_loc,
			    "%<append_args%> specified here");
		    أرجع;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  درخت آرگومانها = TYPE_ARG_TYPES (پایه_type);
	  درخت newargs = NULL_درخت;
	  درخت lastarg = NULL_درخت;
	  لكل (صحيح j = 0; j < nbase_آرگومانها; j++, آرگومانها = درخت_CHAIN (آرگومانها))
	    {
	      درخت t = درخت_cons (درخت_PURPOSE (آرگومانها),
				  درخت_مقدار (آرگومانها), NULL_درخت);
	      إذا (lastarg)
		درخت_CHAIN (lastarg) = t;
	      وإلا
		newargs = t;
	      lastarg = t;
	    }
	  درخت type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? درخت_TYPE (type) : اشاره_گر_sized_int_گره;
	  لكل (صحيح j = 0; j < nappend_آرگومانها; j++)
	    {
	      درخت t = درخت_cons (NULL_درخت, type, NULL_درخت);
	      إذا (lastarg)
		درخت_CHAIN (lastarg) = t;
	      وإلا
		newargs = t;
	      lastarg = t;
	    }
	  درخت_CHAIN (lastarg) = آرگومانها;

	  /* Temporarily stuff newargs into the original base_type.  */
	  درخت saveargs = TYPE_ARG_TYPES (پایه_type);
	  TYPE_ARG_TYPES (پایه_type) = newargs;
	  منطقي fail = !comptypes (پایه_type, variant_type);
	  TYPE_ARG_TYPES (پایه_type) = saveargs;

	  إذا (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_منبع_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      أرجع;
	    }
	  وإلا إذا (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      وإلا  /* No append_args present.  */
	{
	  إذا (!comptypes (پایه_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_منبع_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      أرجع;
	    }
	  وإلا إذا (TYPE_ARG_TYPES (variant_type) == NULL_درخت
		   && !TYPE_NO_NAMED_آرگومانها_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (پایه_type) != NULL_درخت)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (پایه_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_استفاده_شده (variant) = 1;
  درخت construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_مجموعه_CONSTRUCT);
  omp_mark_declare_variant (تطابق_loc, variant, construct);
  إذا (omp_context_selector_matches (ctx, NULL_درخت, خطأ))
    {
      درخت attr = درخت_cons (get_identifier ("omp declare variant base"),
			     build_درخت_list (variant, ctx),
			     DECL_صفات (fndecl));
      DECL_صفات (fndecl) = attr;
    }

  إذا (need_device_ptr_list || append_آرگومانها_درخت)
    {
      درخت variant_decl = درخت_strip_nop_conversions (variant);
      درخت t = build_درخت_list (need_device_ptr_list,
				NULL_درخت /* need_device_addr */);
      درخت_CHAIN (t) = append_آرگومانها_درخت;
      DECL_صفات (variant_decl)
	= درخت_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_صفات (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

ساكن فراغ
c_پایان_omp_declare_simd (c_parser *parser, درخت fndecl, درخت parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  إذا (clauses.exists () && clauses[0].type == CPP_EOF)
    أرجع;
  ثابت حرف *نوع = "simd";
  إذا (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    نوع = IDENTIFIER_اشاره_گر (clauses[0].مقدار);
  gcc_assert (strcmp (نوع, "simd") == 0 || strcmp (نوع, "variant") == 0);
  إذا (fndecl == NULL_درخت || درخت_کد (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", نوع);
      clauses[0].type = CPP_EOF;
      أرجع;
    }
  إذا (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_منبع_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", نوع);
      clauses[0].type = CPP_EOF;
      أرجع;
    }
  إذا (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_منبع_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", نوع);
      أرجع;
    }

  إذا (parms == NULL_درخت)
    parms = DECL_ARGUMENTS (fndecl);

  بیعلامت صحيح نشانهها_avail = parser->نشانهها_avail;
  gcc_assert (parser->نشانهها == &parser->نشانهها_buf[0]);

  parser->نشانهها = clauses.آدرس ();
  parser->نشانهها_avail = clauses.درازی ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  طالما (parser->نشانهها_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      نوع = IDENTIFIER_اشاره_گر (token->مقدار);
      c_parser_consume_token (parser);
      parser->درون_pragma = درست;

      إذا (strcmp (نوع, "simd") == 0)
	{
	  درخت c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_ماسک,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_مقصد_numbers (parms, c);
	  إذا (c != NULL_درخت)
	    c = درخت_cons (NULL_درخت, c, NULL_درخت);
	  c = build_درخت_list (get_identifier ("omp declare simd"), c);
	  درخت_CHAIN (c) = DECL_صفات (fndecl);
	  DECL_صفات (fndecl) = c;
	}
      وإلا
	{
	  gcc_assert (strcmp (نوع, "variant") == 0);
	  c_پایان_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->نشانهها = &parser->نشانهها_buf[0];
  parser->نشانهها_avail = نشانهها_avail;
  إذا (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#إذا !defined (NO_DOT_درون_LABEL)
#تعریف_کن JOIN_STR "."
#وإلاإذا !defined (NO_DOLLAR_درون_LABEL)
#تعریف_کن JOIN_STR "$"
#وإلا
#تعریف_کن JOIN_STR "_"
#پایان_اگر

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
ساكن درخت
omp_شروع_variant_function (c_declarator *declarator, درخت ctx)
{
  c_declarator *id = declarator;
  طالما (id->نوع != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  درخت name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  أرجع name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
ساكن فراغ
omp_پایان_variant_function (درخت decl, درخت پایه_name, درخت ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  درخت پایه_decl = lookup_name (پایه_name);
  إذا (پایه_decl == error_mark_گره)
    پایه_decl = NULL_درخت;
  إذا (!پایه_decl)
    {
      error_at (DECL_منبع_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_اشاره_گر (پایه_name));
      أرجع;
    }

  إذا (!comptypes (درخت_TYPE (decl), درخت_TYPE (پایه_decl)))
    {
      error_at (DECL_منبع_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", پایه_decl);
      inform (DECL_منبع_LOCATION (پایه_decl),
	      "%qE declared here", پایه_decl);
      أرجع;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_منبع_LOCATION (decl),
				   پایه_decl, ctx);
  درخت construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_مجموعه_CONSTRUCT);
  omp_mark_declare_variant (DECL_منبع_LOCATION (decl), decl, construct);
  درخت attrs = DECL_صفات (پایه_decl);
  درخت تطابق_loc_گره
    = maybe_wrap_with_location (integer_zero_گره,
				DECL_منبع_LOCATION (پایه_decl));
  درخت loc_گره = درخت_cons (تطابق_loc_گره, integer_zero_گره,
			     build_درخت_list (تطابق_loc_گره,
					      integer_zero_گره));
  attrs = درخت_cons (get_identifier ("omp declare variant base"),
		     درخت_cons (decl, ctx, loc_گره), attrs);
  DECL_صفات (پایه_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  درخت_عمومی (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

منطقي
c_maybe_parse_omp_decl (درخت decl, درخت d)
{
  gcc_assert (درخت_کد (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_نشانهها (d);
  c_token *اولی = toks->آدرس ();
  c_token *آخرین = اولی + toks->درازی ();
  ثابت حرف *directive[3] = {};
  لكل (صحيح j = 0; j < 3; j++)
    {
      درخت id = NULL_درخت;
      إذا (اولی + j == آخرین)
	اكسر;
      إذا (اولی[j].type == CPP_NAME)
	id = اولی[j].مقدار;
      وإلا إذا (اولی[j].type == CPP_KEYWORD)
	id = ridpointers[(صحيح) اولی[j].keyword];
      وإلا
	اكسر;
      directive[j] = IDENTIFIER_اشاره_گر (id);
    }
  ثابت c_omp_directive *dir = عدم;
  إذا (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  إذا (dir == عدم)
    {
      error_at (اولی->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      أرجع خطأ;
    }
  إذا (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    أرجع خطأ;

  إذا (!flag_openmp && !dir->simd)
    أرجع درست;

  c_parser *parser = the_parser;
  بیعلامت صحيح نشانهها_avail = parser->نشانهها_avail;
  gcc_assert (parser->نشانهها == &parser->نشانهها_buf[0]);
  toks = عدم;
  vec_امن_reserve (toks, آخرین - اولی + 2, درست);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_نوع = pragma_نوع (dir->id);
  tok.location = اولی->location;
  toks->سریع_افزودن (tok);
  طالما (++اولی < آخرین)
    toks->سریع_افزودن (*اولی);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = آخرین[-1].location;
  toks->سریع_افزودن (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = آخرین[-1].location;
  toks->سریع_افزودن (tok);
  parser->درون_omp_decl_attribute = decl;
  gcc_assert (!parser->درون_omp_attribute_pragma);
  parser->درون_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->درون_omp_attribute_pragma->token_vec = toks;
  parser->درون_omp_attribute_pragma->save_نشانهها = parser->نشانهها;
  parser->درون_omp_attribute_pragma->save_نشانهها_avail = نشانهها_avail;
  parser->نشانهها = toks->آدرس ();
  parser->نشانهها_avail = toks->درازی ();
  c_parser_pragma (parser, pragma_external, عدم, NULL_درخت);
  parser->درون_omp_decl_attribute = NULL_درخت;
  أرجع درست;
}

/* OpenMP 4.0:
   # pragma omp declare target new-line
   declarations and definitions
   # pragma omp end declare target new-line

   OpenMP 4.5:
   # pragma omp declare target ( extended-list ) new-line

   # pragma omp declare target declare-target-clauses[seq] new-line  */

#تعریف_کن OMP_DECLARE_هدف_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_مقصد)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ENTER)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LINK)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LOCAL)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_غیرمستقیم))

ساكن فراغ
c_parser_omp_declare_هدف (c_parser *parser)
{
  درخت clauses = NULL_درخت;
  صحيح device_type = 0;
  منطقي غیرمستقیم = خطأ;
  منطقي only_device_type_or_غیرمستقیم = درست;
  إذا (flag_openmp)
    omp_requires_ماسک
      = (تعداد omp_requires) (omp_requires_ماسک | OMP_REQUIRES_هدف_استفاده_شده);
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
      || (c_parser_بعدی_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_هدف_CLAUSE_ماسک,
					"#pragma omp declare target");
  وإلا إذا (parser->درون_omp_decl_attribute
	   || c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_پایان_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_مقصد_pragma_eol (parser);
    }
  وإلا
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      منطقي attr_syntax = parser->درون_omp_attribute_pragma != عدم;
      c_parser_skip_مقصد_pragma_eol (parser);
      c_omp_declare_هدف_attr attr = { attr_syntax, -1, 0 };
      vec_امن_افزودن (current_omp_declare_هدف_attribute, attr);
      أرجع;
    }
  لكل (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_نوع (c);
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_غیرمستقیم)
	غیرمستقیم |= !integer_zerop (OMP_CLAUSE_غیرمستقیم_عبارت (c));
    }
  لكل (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_کد (c) == OMP_CLAUSE_غیرمستقیم)
	استمر;
      درخت t = OMP_CLAUSE_DECL (c), id;
      درخت at1 = lookup_attribute ("omp declare target", DECL_صفات (t));
      درخت at2 = lookup_attribute ("omp declare target link",
				   DECL_صفات (t));
      only_device_type_or_غیرمستقیم = خطأ;
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::جابجا (at1, at2);
	}
      وإلا
	id = get_identifier ("omp declare target");
      إذا (at2)
	{
	  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_مقصد (c) ? "to" : "enter");
	  وإلا إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_LOCAL
		   || مقدار_member (get_identifier ("local"), درخت_مقدار (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  استمر;
	}
      إذا (!at1)
	{
	  DECL_صفات (t) = درخت_cons (id, NULL_درخت, DECL_صفات (t));
	  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_LOCAL)
	    درخت_مقدار (DECL_صفات (t))
	      = درخت_cons (NULL_درخت, get_identifier ("local"),
			   درخت_مقدار (DECL_صفات (t)));

	  إذا (درخت_کد (t) != FUNCTION_DECL && !is_global_var (t))
	    استمر;

	  symtab_گره *گره = symtab_گره::get (t);
	  إذا (گره != عدم)
	    {
	      گره->offloadable = 1;
	      إذا (ENABLE_OFFLOADING)
		{
		  g->have_offload = درست;
		  إذا (is_a <varpool_گره *> (گره)
		      && OMP_CLAUSE_کد (c) != OMP_CLAUSE_LOCAL)
		    vec_امن_افزودن (offload_vars, t);
		}
	    }
	}
      وإلا
	{
	  منطقي saw_local = مقدار_member (get_identifier ("local"),
					 درخت_مقدار (at1));
	  إذا (saw_local && OMP_CLAUSE_کد (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_مقصد (c) ? "to" : "enter");
	      استمر;
	    }
	  وإلا إذا (!saw_local && OMP_CLAUSE_کد (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      استمر;
	    }
	}
      إذا (درخت_کد (t) != FUNCTION_DECL)
	استمر;
      إذا ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  درخت at3 = lookup_attribute ("omp declare target host",
				       DECL_صفات (t));
	  إذا (at3 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_صفات (t)
		= درخت_cons (id, NULL_درخت, DECL_صفات (t));
	    }
	}
      إذا ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  درخت at3 = lookup_attribute ("omp declare target nohost",
				       DECL_صفات (t));
	  إذا (at3 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_صفات (t)
		= درخت_cons (id, NULL_درخت, DECL_صفات (t));
	    }
	}
      إذا (غیرمستقیم)
	{
	  درخت at4 = lookup_attribute ("omp declare target indirect",
				       DECL_صفات (t));
	  إذا (at4 == NULL_درخت)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_صفات (t)
		= درخت_cons (id, NULL_درخت, DECL_صفات (t));
	    }
	}
    }
  إذا ((device_type || غیرمستقیم) && only_device_type_or_غیرمستقیم)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  إذا (غیرمستقیم && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "%<device_type%> clause must specify 'any' when used with "
	      "an %<indirect%> clause");
}

/* OpenMP 5.1
   #pragma omp begin assumes clauses[optseq] new-line

   #pragma omp begin declare target clauses[optseq] new-line

   #pragma omp begin declare variant match (context-selector) new-line  */

#تعریف_کن OMP_BEGIN_DECLARE_هدف_CLAUSE_ماسک			\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_غیرمستقیم))

ساكن فراغ
c_parser_omp_begin (c_parser *parser)
{
  ثابت حرف *p = "";
  c_parser_consume_pragma (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
  إذا (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقي attr_syntax = parser->درون_omp_attribute_pragma != عدم;
	  درخت clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_هدف_CLAUSE_ماسک,
					"#pragma omp begin declare target");
	  صحيح device_type = 0;
	  صحيح غیرمستقیم = 0;
	  لكل (درخت c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_نوع (c);
	      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_غیرمستقیم)
		غیرمستقیم |= !integer_zerop (OMP_CLAUSE_غیرمستقیم_عبارت (c));
	    }
	  c_omp_declare_هدف_attr attr = { attr_syntax, device_type,
					     غیرمستقیم };
	  vec_امن_افزودن (current_omp_declare_هدف_attribute, attr);
	}
      وإلا إذا (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ثابت حرف *clause = "";
	  matching_parens parens;
	  location_t تطابق_loc = c_parser_peek_token (parser)->location;
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	    {
	      درخت id = c_parser_peek_token (parser)->مقدار;
	      clause = IDENTIFIER_اشاره_گر (id);
	    }
	  إذا (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_مقصد_pragma_eol (parser);
	      أرجع;
	    }

	  c_parser_consume_token (parser);

	  إذا (!parens.require_open (parser))
	    {
	      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	      أرجع;
	    }

	  درخت ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_درخت);
	  إذا (ctx != error_mark_گره)
	    ctx = omp_check_context_selector (تطابق_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  إذا (ctx != error_mark_گره
	      && !vec_امن_is_خالی (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->آخرین ();
	      درخت outer_ctx = a.selector;
	      ctx = omp_ادغام_context_selectors (تطابق_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  إذا (ctx == error_mark_گره
	      || !omp_context_selector_matches (ctx, NULL_درخت, خطأ, درست))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	      c_parser_skip_مقصد_pragma_omp_انتها_declare_variant (parser);
	      أرجع;
	    }
	  وإلا
	    {
	      منطقي attr_syntax = parser->درون_omp_attribute_pragma != عدم;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_امن_افزودن (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_مقصد_pragma_eol (parser);
	}
      وإلا
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	}
    }
  وإلا إذا (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقي attr_syntax = parser->درون_omp_attribute_pragma != عدم;
      c_parser_omp_assumption_clauses (parser, خطأ);
      بنية c_omp_begin_assumes_داده a = { attr_syntax };
      vec_امن_افزودن (current_omp_begin_assumes, a);
    }
  وإلا
    {
      c_parser_error (parser, "expected %<declare target%>, "
		      "%<declare variant%>, or %<assumes%>");
      c_parser_skip_مقصد_pragma_eol (parser);
    }
}

/* OpenMP 4.0
   #pragma omp end declare target

   OpenMP 5.1
   #pragma omp end assumes
   #pragma omp end declare variant  */

ساكن فراغ
c_parser_omp_انتها (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ثابت حرف *p = "";
  c_parser_consume_pragma (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
  إذا (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقي attr_syntax = parser->درون_omp_attribute_pragma != عدم;
	  c_parser_skip_مقصد_pragma_eol (parser);
	  إذا (!vec_امن_درازی (current_omp_declare_هدف_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  وإلا
	    {
	      c_omp_declare_هدف_attr
		a = current_omp_declare_هدف_attribute->برداشت ();
	      إذا (a.attr_syntax != attr_syntax)
		{
		  إذا (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  وإلا
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      وإلا إذا (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقي attr_syntax = parser->درون_omp_attribute_pragma != عدم;
	  c_parser_skip_مقصد_pragma_eol (parser);
	  إذا (!vec_امن_درازی (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  وإلا
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->برداشت ();
	      إذا (a.attr_syntax != attr_syntax)
		{
		  إذا (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  وإلا
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      وإلا
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_مقصد_pragma_eol (parser);
	  أرجع;
	}
    }
  وإلا إذا (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقي attr_syntax = parser->درون_omp_attribute_pragma != عدم;
      c_parser_skip_مقصد_pragma_eol (parser);
      إذا (!vec_امن_درازی (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      وإلا
	{
	  c_omp_begin_assumes_داده
	    a = current_omp_begin_assumes->برداشت ();
	  إذا (a.attr_syntax != attr_syntax)
	    {
	      إذا (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      وإلا
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  وإلا
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_مقصد_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

ساكن فراغ
c_parser_omp_declare_mapper (c_parser *parser, تعداد pragma_context context)
{
  درخت type, mapper_name = NULL_درخت, var = NULL_درخت, stmt, stmtlist;
  درخت maplist = NULL_درخت, mapper_id, mapper_decl, t;
  c_token *token;

  إذا (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      اذهب fail;
    }

  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    اذهب fail;

  token = c_parser_peek_token (parser);

  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      بدل (token->type)
	{
	حالة CPP_NAME:
	  mapper_name = token->مقدار;
	  c_parser_consume_token (parser);
	  اكسر;
	حالة CPP_KEYWORD:
	  إذا (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_درخت;
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  /* Fallthrough.  */
	افتراضي:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  أرجع;
	}

      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	اذهب fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    بنية c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, عدم, عدم);
    إذا (type == error_mark_گره)
      اذهب fail;
    إذا (!رکورد_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	أرجع;
      }
    لكل (درخت t = DECL_INITIAL (mapper_decl); t; t = درخت_CHAIN (t))
      إذا (comptypes (درخت_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_اشاره_گر (mapper_id)
		      + حجم ("omp declare mapper ") - 1,
		    type);
	  درخت prevmapper = درخت_مقدار (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_منبع_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  أرجع;
	}
  }

  token = c_parser_peek_token (parser);
  إذا (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->مقدار, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  وإلا
    {
      error_at (token->location, "expected identifier");
      اذهب fail;
    }

  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    اذهب fail;

  افزودن_scope ();
  stmtlist = افزودن_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t اینجا;
      pragma_omp_clause c_نوع;
      اینجا = c_parser_peek_token (parser)->location;
      c_نوع = c_parser_omp_clause_name (parser);
      إذا (c_نوع != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (اینجا, "unexpected clause");
	  اذهب fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, درست);
    }

  إذا (maplist == NULL_درخت)
    {
      error_at (درون_داد_location, "missing %<map%> clause");
      اذهب fail;
    }
  درخت list;
  لكل (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      درخت dvar = OMP_CLAUSE_DECL (list);
      طالما (!DECL_P (dvar) && درخت_عملوند_درازی (dvar))
	dvar = درخت_عملوند (dvar, 0);
      إذا (dvar == var)
	اكسر;
    }
  إذا (!list)
    error_at (درون_داد_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_گره (OMP_DECLARE_MAPPER);
  درخت_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  جمع_کن_stmt (stmt);

  برداشت_stmt_list (stmtlist);
  برداشت_scope ();

  c_parser_skip_مقصد_pragma_eol (parser);

  t = درخت_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  أرجع;

 fail:
  c_parser_skip_مقصد_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

ساكن فراغ
c_parser_omp_declare_reduction (c_parser *parser, تعداد pragma_context context)
{
  بیعلامت صحيح نشانهها_avail = 0, i;
  c_token *saved_نشانهها = عدم;
  vec<درخت> types = vNULL;
  vec<c_token> clauses = vNULL;
  تعداد درخت_کد_2 reduc_کد = ERROR_MARK;
  درخت reduc_id = NULL_درخت;
  درخت type;
  location_t rloc = c_parser_peek_token (parser)->location;

  إذا (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      اذهب fail;
    }

  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    اذهب fail;

  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_PLUS:
      reduc_کد = PLUS_عبارت;
      اكسر;
    حالة CPP_MULT:
      reduc_کد = MULT_عبارت;
      اكسر;
    حالة CPP_MINUS:
      reduc_کد = MINUS_عبارت;
      اكسر;
    حالة CPP_AND:
      reduc_کد = بیت_AND_عبارت;
      اكسر;
    حالة CPP_XOR:
      reduc_کد = بیت_XOR_عبارت;
      اكسر;
    حالة CPP_OR:
      reduc_کد = بیت_IOR_عبارت;
      اكسر;
    حالة CPP_AND_AND:
      reduc_کد = TRUTH_ANDIF_عبارت;
      اكسر;
    حالة CPP_OR_OR:
      reduc_کد = TRUTH_ORIF_عبارت;
      اكسر;
    حالة CPP_NAME:
      ثابت حرف *p;
      p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "min") == 0)
	{
	  reduc_کد = MIN_عبارت;
	  اكسر;
	}
      إذا (strcmp (p, "max") == 0)
	{
	  reduc_کد = MAX_عبارت;
	  اكسر;
	}
      reduc_id = c_parser_peek_token (parser)->مقدار;
      اكسر;
    افتراضي:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      اذهب fail;
    }

  درخت orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_کد, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب fail;

  طالما (درست)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      بنية c_type_name *ctype = c_parser_type_name (parser);
      إذا (ctype != عدم)
	{
	  type = groktypename (ctype, عدم, عدم);
	  إذا (type == error_mark_گره)
	    ;
	  وإلا إذا ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || درخت_کد (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_درخت)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  وإلا إذا (درخت_کد (type) == FUNCTION_TYPE
		   || درخت_کد (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  وإلا إذا (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  وإلا إذا (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  وإلا
	    {
	      درخت t;
	      لكل (t = DECL_INITIAL (reduc_decl); t; t = درخت_CHAIN (t))
		إذا (comptypes (درخت_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_اشاره_گر (reduc_id)
				   + حجم ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_منبع_LOCATION (درخت_VEC_ELT (درخت_مقدار (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    اكسر;
		  }
	      إذا (t == NULL_درخت)
		types.امن_افزودن (type);
	    }
	  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      وإلا
	اكسر;
    }

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_خالی ())
    {
     fail:
      clauses.release ();
      types.release ();
      طالما (درست)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    اكسر;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_مقصد_pragma_eol (parser);
      أرجع;
    }

  إذا (types.درازی () > 1)
    {
      طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    اذهب fail;
	  clauses.امن_افزودن (*token);
	  c_parser_consume_token (parser);
	}
      clauses.امن_افزودن (*c_parser_peek_token (parser));
      c_parser_skip_مقصد_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, حجم (eof_token));
      eof_token.type = CPP_EOF;
      clauses.امن_افزودن (eof_token);
      clauses.امن_افزودن (eof_token);
    }

  صحيح errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_نشانهها = parser->نشانهها;
      نشانهها_avail = parser->نشانهها_avail;
      إذا (!clauses.is_خالی ())
	{
	  parser->نشانهها = clauses.آدرس ();
	  parser->نشانهها_avail = clauses.درازی ();
	  parser->درون_pragma = درست;
	}

      منطقي nested = current_function_decl != NULL_درخت;
      إذا (nested)
	c_افزودن_function_context ();
      درخت fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, درست);
      افزودن_scope ();
      درخت stmt = افزودن_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      درخت omp_بیرون = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_بیرون) = 1;
      DECL_CONTEXT (omp_بیرون) = fndecl;
      pushdecl (omp_بیرون);
      درخت omp_درون = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_درون) = 1;
      DECL_CONTEXT (omp_درون) = fndecl;
      pushdecl (omp_درون);
      بنية c_عبارت combiner = c_parser_عبارت (parser);
      بنية c_عبارت initializer;
      درخت omp_priv = NULL_درخت, omp_orig = NULL_درخت;
      منطقي bad = خطأ;
      initializer.مجموعه_error ();
      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = درست;
      وإلا إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      إذا (!bad
	  && (c_parser_بعدی_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_اشاره_گر
				(c_parser_peek_token (parser)->مقدار),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  برداشت_scope ();
	  افزودن_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_گره;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = درست;
	  وإلا إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = درست;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر
				(c_parser_peek_token (parser)->مقدار),
			   "omp_priv") != 0)
	    {
	      إذا (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_نوع != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = درست;
		}
	      وإلا
		initializer = c_parser_postfix_عبارت (parser);
	      إذا (initializer.مقدار
		  && درخت_کد (initializer.مقدار) == CALL_عبارت)
		{
		  صحيح j;
		  درخت c = initializer.مقدار;
		  لكل (j = 0; j < call_عبارت_nargs (c); j++)
		    {
		      درخت a = CALL_عبارت_ARG (c, j);
		      STRIP_NOPS (a);
		      إذا (درخت_کد (a) == ADDR_عبارت
			  && درخت_عملوند (a, 0) == omp_priv)
			اكسر;
		    }
		  إذا (j == call_عبارت_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = درست;
	      وإلا
		{
		  درخت st = افزودن_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سطر_جدول, loc);
		  شروع_init (omp_priv, NULL_درخت, خطأ, خطأ, &richloc);
		  بنية c_عبارت init = c_parser_initializer (parser, omp_priv);
		  پایان_init ();
		  پایان_decl (omp_priv, loc, init.مقدار,
		      	       init.original_type, NULL_درخت);
		  برداشت_stmt_list (st);
		}
	    }
	  إذا (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = درست;
	}

      إذا (!bad)
	{
	  c_parser_skip_مقصد_pragma_eol (parser);

	  درخت t = درخت_cons (type, make_درخت_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_منبع_LOCATION (omp_بیرون) = rloc;
	  درخت_VEC_ELT (درخت_مقدار (t), 0) = omp_بیرون;
	  درخت_VEC_ELT (درخت_مقدار (t), 1) = omp_درون;
	  درخت_VEC_ELT (درخت_مقدار (t), 2) = combiner.مقدار;
	  walk_درخت (&combiner.مقدار, c_check_omp_declare_reduction_r,
		     &درخت_VEC_ELT (درخت_مقدار (t), 0), عدم);
	  إذا (omp_priv)
	    {
	      DECL_منبع_LOCATION (omp_priv) = rloc;
	      درخت_VEC_ELT (درخت_مقدار (t), 3) = omp_priv;
	      درخت_VEC_ELT (درخت_مقدار (t), 4) = omp_orig;
	      درخت_VEC_ELT (درخت_مقدار (t), 5) = initializer.مقدار;
	      walk_درخت (&initializer.مقدار, c_check_omp_declare_reduction_r,
			 &درخت_VEC_ELT (درخت_مقدار (t), 3), عدم);
	      walk_درخت (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &درخت_VEC_ELT (درخت_مقدار (t), 3), عدم);
	    }
	}

      برداشت_stmt_list (stmt);
      برداشت_scope ();
      إذا (cfun->language != عدم)
	{
	  ggc_free (cfun->language);
	  cfun->language = عدم;
	}
      مجموعه_cfun (عدم);
      current_function_decl = NULL_درخت;
      إذا (nested)
	c_برداشت_function_context ();

      إذا (!clauses.is_خالی ())
	{
	  parser->نشانهها = saved_نشانهها;
	  parser->نشانهها_avail = نشانهها_avail;
	}
      إذا (bad)
	اذهب fail;
      إذا (errs != errorcount)
	اكسر;
    }

  clauses.release ();
  types.release ();
}

/* OpenMP 4.0
   #pragma omp declare simd declare-simd-clauses[optseq] new-line
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line
   #pragma omp declare target new-line

   OpenMP 5.0
   #pragma omp declare variant (identifier) match (context-selector)

   OpenMP 5.1
   #pragma omp declare variant (identifier) match (context-selector) \
      adjust_args(adjust-op:argument-list)  */

ساكن منطقي
c_parser_omp_declare (c_parser *parser, تعداد pragma_context context)
{
  c_parser_consume_pragma (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  أرجع درست;
	}
      إذا (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  أرجع خطأ;
	}
      إذا (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  أرجع خطأ;
	}
      إذا (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  أرجع خطأ;
	}
      إذا (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_هدف (parser);
	  أرجع خطأ;
	}
      إذا (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  أرجع درست;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_مقصد_pragma_eol (parser);
  أرجع خطأ;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

ساكن فراغ
c_parser_omp_requires (c_parser *parser)
{
  تعداد omp_requires new_req = (تعداد omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  تعداد omp_requires this_req = (تعداد omp_requires) 0;

	  إذا (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_آدرس;
	  وإلا إذا (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_حافظه;
	  وإلا إذا (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  وإلا إذا (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  وإلا إذا (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_معکوس_OFFLOAD;
	  وإلا إذا (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      إذا (parens.require_open (parser))
		{
		  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		    {
		      درخت v = c_parser_peek_token (parser)->مقدار;
		      p = IDENTIFIER_اشاره_گر (v);

		      إذا (!strcmp (p, "seq_cst"))
			this_req
			  = (تعداد omp_requires) OMP_حافظه_ترتیب_SEQ_CST;
		      وإلا إذا (!strcmp (p, "relaxed"))
			this_req
			  = (تعداد omp_requires) OMP_حافظه_ترتیب_RELAXED;
		      وإلا إذا (!strcmp (p, "release"))
			this_req
			  = (تعداد omp_requires) OMP_حافظه_ترتیب_RELEASE;
		      وإلا إذا (!strcmp (p, "acq_rel"))
			this_req
			  = (تعداد omp_requires) OMP_حافظه_ترتیب_ACQ_REL;
		      وإلا إذا (!strcmp (p, "acquire"))
			this_req
			  = (تعداد omp_requires) OMP_حافظه_ترتیب_ACQUIRE;
		    }
		  إذا (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      بدل (c_parser_peek_token (parser)->type)
			{
			حالة CPP_EOF:
			حالة CPP_PRAGMA_EOL:
			حالة CPP_CLOSE_PAREN:
			  اكسر;
			افتراضي:
			  إذا (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  اكسر;
			}
		    }
		  وإلا
		    c_parser_consume_token (parser);

		  parens.skip_until_یافت_close (parser);
		  إذا (this_req == 0)
		    {
		      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
		      أرجع;
		    }
		}
	      p = عدم;
	    }
	  وإلا
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	      أرجع;
	    }
	  إذا (p)
	    c_parser_consume_token (parser);
	  إذا (this_req)
	    {
	      إذا ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب) != 0)
		{
		  إذا ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  إذا (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_ماسک & OMP_REQUIRES_هدف_استفاده_شده) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      وإلا إذا ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (تعداد omp_requires) 0;
		}
	      وإلا إذا ((omp_requires_ماسک
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (تعداد omp_requires)
		       (omp_requires_ماسک
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب);
		}
	      وإلا إذا ((omp_requires_ماسک
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتیب_استفاده_شده) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (تعداد omp_requires) (new_req | this_req);
	      omp_requires_ماسک
		= (تعداد omp_requires) (omp_requires_ماسک | this_req);
	      استمر;
	    }
	}
      اكسر;
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  إذا (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

ساكن درخت
c_پایان_taskloop_clauses (درخت clauses)
{
  درخت *pc = &clauses;
  لكل (درخت c = clauses; c; c = *pc)
    {
      منطقي remove = خطأ;
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION)
	{
	  درخت type = strip_array_types (درخت_TYPE (OMP_CLAUSE_DECL (c)));
	  إذا (integer_zerop (TYPE_اندازه_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = درست;
	    }
	  وإلا إذا (درخت_کد (TYPE_اندازه_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = درست;
	    }
	}
      إذا (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      وإلا
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  أرجع clauses;
}

/* OpenMP 4.5:
   #pragma omp taskloop taskloop-clause[optseq] new-line
     for-loop

   #pragma omp taskloop simd taskloop-simd-clause[optseq] new-line
     for-loop  */

#تعریف_کن OMP_TASKLOOP_CLAUSE_ماسک				\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_خصوصی)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_GRAINSIZE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_رقم_TASKS)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_NOGROUP)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_اولویت)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_درون_REDUCTION))

ساكن درخت
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_ماسک ماسک, درخت *cclauses,
		       منطقي *if_p)
{
  درخت clauses, بلوک, ret;

  strcat (p_name, " taskloop");
  ماسک |= OMP_TASKLOOP_CLAUSE_ماسک;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  إذا ((ماسک & (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_رقم_نخها)) != 0)
    ماسک &= ~(OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_درون_REDUCTION);

  إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);

      إذا (strcmp (p, "simd") == 0)
	{
	  درخت cclauses_buf[C_OMP_CLAUSE_تقسیم_شمار];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_simd (loc, parser, p_name, ماسک, cclauses,
				      if_p);
	  بلوک = c_begin_compound_stmt (درست);
	  ret = c_parser_omp_simd (loc, parser, p_name, ماسک, cclauses, if_p);
	  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
	  إذا (ret == عدم)
	    أرجع ret;
	  ret = make_گره (OMP_TASKLOOP);
	  درخت_TYPE (ret) = void_type_گره;
	  OMP_FOR_BODY (ret) = بلوک;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_تقسیم_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_پایان_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  مجموعه_عبارت_LOCATION (ret, loc);
	  جمع_کن_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_مقصد_pragma_eol (parser, خطأ);
      أرجع NULL_درخت;
    }

  clauses = c_parser_omp_all_clauses (parser, ماسک, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_تقسیم_clauses (loc, OMP_TASKLOOP, ماسک, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_تقسیم_TASKLOOP];
    }

  clauses = c_پایان_taskloop_clauses (clauses);
  بلوک = c_begin_compound_stmt (درست);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, عدم, if_p);
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
ساكن درخت
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  درخت sizes = NULL_درخت;

  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  إذا (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_اشاره_گر (tok->مقدار)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      أرجع error_mark_گره;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_گره;

  vec<درخت, va_gc> *sizes_vec
    = c_parser_عبارت_list (parser, درست, درست, عدم, عدم, عدم, عدم);
  sizes = build_درخت_list_vec (sizes_vec);
  release_درخت_وکتور (sizes_vec);

  لكل (درخت s = sizes; s; s = درخت_CHAIN (s))
    {
      درخت عبارت = درخت_مقدار (s);
      إذا (عبارت == error_mark_گره)
	{
	  parens.skip_until_یافت_close (parser);
	  أرجع error_mark_گره;
	}

      HOST_WIDE_INT n;
      إذا (!INTEGRAL_TYPE_P (درخت_TYPE (عبارت))
	  || !درخت_میگنجد_shwi_p (عبارت)
	  || (n = درخت_مقصد_shwi (عبارت)) <= 0
	  || (صحيح) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  درخت_مقدار (s) = integer_one_گره;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  درخت c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  أرجع c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

ساكن درخت
c_parser_omp_tile (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_مقصد_pragma_eol (parser);

  إذا (!clauses || clauses == error_mark_گره)
    أرجع error_mark_گره;

  درخت بلوک = c_begin_compound_stmt (درست);
  درخت ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    عدم, if_p);
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع ret;
}

#تعریف_کن OMP_UNROLL_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_پر))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

ساكن درخت
c_parser_omp_unroll (location_t loc, c_parser *parser, منطقي *if_p)
{
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_ماسک,
					   "#pragma omp unroll", درست);

  درخت بلوک = c_begin_compound_stmt (درست);
  درخت ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    عدم, if_p);
  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);
  جمع_کن_stmt (بلوک);

  أرجع ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

ساكن فراغ
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_مقصد_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

ساكن منطقي
c_parser_omp_error (c_parser *parser, تعداد pragma_context context)
{
  صحيح at_compilation = -1;
  صحيح severity_fatal = -1;
  درخت پیام = NULL_درخت;
  منطقي bad = خطأ;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
	اكسر;

      ثابت حرف *p
	= IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      location_t cloc = c_parser_peek_token (parser)->location;
      ساكن ثابت حرف *آرگومانها[] = {
	"execution", "compilation", "warning", "fatal"
      };
      صحيح *v = عدم;
      صحيح idx = 0, n = -1;
      درخت m = NULL_درخت;

      إذا (!strcmp (p, "at"))
	v = &at_compilation;
      وإلا إذا (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      وإلا إذا (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_مقصد_pragma_eol (parser, خطأ);
	  أرجع خطأ;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      إذا (parens.require_open (parser))
	{
	  إذا (v == عدم)
	    {
	      location_t عبارت_loc = c_parser_peek_token (parser)->location;
	      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	      عبارت = convert_lvalue_مقصد_rvalue (عبارت_loc, عبارت, درست, درست);
	      m = convert (const_string_type_گره, عبارت.مقدار);
	      m = c_fully_fold (m, خطأ, عدم);
	    }
	  وإلا
	    {
	      إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		{
		  درخت val = c_parser_peek_token (parser)->مقدار;
		  ثابت حرف *q = IDENTIFIER_اشاره_گر (val);

		  إذا (!strcmp (q, آرگومانها[idx]))
		    n = 0;
		  وإلا إذا (!strcmp (q, آرگومانها[idx + 1]))
		    n = 1;
		}
	      إذا (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", آرگومانها[idx], آرگومانها[idx + 1]);
		  bad = درست;
		  بدل (c_parser_peek_token (parser)->type)
		    {
		    حالة CPP_EOF:
		    حالة CPP_PRAGMA_EOL:
		    حالة CPP_CLOSE_PAREN:
		      اكسر;
		    افتراضي:
		      إذا (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      اكسر;
		    }
		}
	      وإلا
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_یافت_close (parser);

	  إذا (v == عدم)
	    {
	      إذا (پیام)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = درست;
		}
	      وإلا
		پیام = m;
	    }
	  وإلا إذا (n != -1)
	    {
	      إذا (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = درست;
		}
	      وإلا
		*v = n;
	    }
	}
      وإلا
	bad = درست;
    }
  c_parser_skip_مقصد_pragma_eol (parser);
  إذا (bad)
    أرجع درست;

  إذا (at_compilation == -1)
    at_compilation = 1;
  إذا (severity_fatal == -1)
    severity_fatal = 1;
  إذا (!at_compilation)
    {
      إذا (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  أرجع درست;
	}
      إذا (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->درون_intervening_کد)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = درست;
	  أرجع درست;
	}
      درخت fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_درون_GOMP_ERROR
						: BUILT_درون_GOMP_WARNING);
      إذا (!پیام)
	پیام = build_zero_cst (const_string_type_گره);
      درخت stmt = build_call_عبارت_loc (loc, fndecl, 2, پیام,
				       build_all_ones_cst (اندازه_type_گره));
      جمع_کن_stmt (stmt);
      أرجع درست;
    }
  ثابت حرف *پیام_2 = عدم;
  إذا (پیام)
    {
      پیام_2 = c_getstr (پیام);
      إذا (پیام_2 == عدم)
	پیام_2 = _("<message unknown at compile time>");
    }
  ثابت تعداد diagnostics::نوع diag_نوع = (severity_fatal
					    ? diagnostics::نوع::error
					    : diagnostics::نوع::warning);
  إذا (پیام_2)
    emit_diagnostic (diag_نوع, loc, 0,
		     "%<pragma omp error%> encountered: %s", پیام_2);
  وإلا
    emit_diagnostic (diag_نوع, loc, 0,
		     "%<pragma omp error%> encountered");
  أرجع خطأ;
}

/* Assumption clauses
   OpenMP 5.1:
   absent (directive-name-list)
   contains (directive-name-list)
   holds (expression)
   no_openmp
   no_openmp_routines
   no_parallelism

   OpenMP 6.0:
   no_openmp_constructs  */

ساكن فراغ
c_parser_omp_assumption_clauses (c_parser *parser, منطقي is_assume)
{
  منطقي no_openmp = خطأ;
  منطقي no_openmp_constructs = خطأ;
  منطقي no_openmp_routines = خطأ;
  منطقي no_parallelism = خطأ;
  bitmap_سر absent_سر, شامل_است_سر;

  bitmap_obstack_initialize (عدم);
  bitmap_initialize (&absent_سر, &bitmap_default_obstack);
  bitmap_initialize (&شامل_است_سر, &bitmap_default_obstack);

  إذا (c_parser_بعدی_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
	اكسر;

      ثابت حرف *p
	= IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      location_t cloc = c_parser_peek_token (parser)->location;

      إذا (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = درست;
	}
      وإلا إذا (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = درست;
	}
      وإلا إذا (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = درست;
	}
      وإلا إذا (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = درست;
	}
      وإلا إذا (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  إذا (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_عبارت عبارت = c_parser_عبارت_no_commas (parser, عدم);
	      درخت t = convert_lvalue_مقصد_rvalue (eloc, عبارت, درست, درست).مقدار;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, خطأ, عدم);
	      إذا (is_assume && t != error_mark_گره)
		{
		  درخت fn = build_call_عبارت_داخلی_loc (eloc, IFN_ASSUME,
							  void_type_گره, 1,
							  t);
		  جمع_کن_stmt (fn);
		}
	      parens.skip_until_یافت_close (parser);
	    }
	}
      وإلا إذا (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  إذا (parens.require_open (parser))
	    {
	      افعل
		{
		  ثابت حرف *directive[3] = {};
		  صحيح i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  لكل (i = 0; i < 3; i++)
		    {
		      درخت id;
		      إذا (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->مقدار;
		      وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  تعداد rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      وإلا
			اكسر;
		      directive[i] = IDENTIFIER_اشاره_گر (id);
		    }
		  إذا (i == 0)
		    error_at (dloc, "expected directive name");
		  وإلا
		    {
		      ثابت بنية c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      إذا (dir
			  && dir->id != PRAGMA_OMP_انتها
			  && (dir->نوع == C_OMP_DIR_DECLARATIVE
			      || dir->نوع == C_OMP_DIR_INFORMATIONAL
			      || dir->نوع == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      وإلا إذا (dir == عدم
			       || dir->id == PRAGMA_OMP_انتها
			       || (!dir->دومی && directive[1])
			       || (!dir->سوم && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      وإلا
			{
			  صحيح id = dir - c_omp_directives;
			  إذا (bitmap_بیت_p (p[0] == 'a' ? &شامل_است_سر
							: &absent_سر, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  وإلا إذا (!bitmap_مجموعه_بیت (p[0] == 'a'
						    ? &absent_سر
						    : &شامل_است_سر, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned multiple times in %qs "
					    "clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "", p);
			}
		      لكل (; i; --i)
			c_parser_consume_token (parser);
		    }
		  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  وإلا
		    اكسر;
		}
	      طالما (1);
	      parens.skip_until_یافت_close (parser);
	    }
	}
      وإلا إذا (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_متوازن_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      وإلا
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  اكسر;
	}
    }
  c_parser_skip_مقصد_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

ساكن فراغ
c_parser_omp_assume (c_parser *parser, منطقي *if_p)
{
  c_parser_omp_assumption_clauses (parser, درست);
  جمع_کن_stmt (c_parser_omp_structured_بلوک (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

ساكن فراغ
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, خطأ);
}

/* Helper function for c_parser_omp_metadirective.  */

ساكن فراغ
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &نشانهها,
			    vec<درخت> &labels)
{
  صحيح nesting_عمق = 0;
  صحيح bracket_عمق = 0;
  منطقي ignore_label = خطأ;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  طالما (1)
    {
      c_token *token = c_parser_peek_token (parser);
      منطقي stop = خطأ;

      إذا (c_parser_بعدی_token_is_keyword (parser, RID_CASE))
	ignore_label = درست;

      بدل (token->type)
	{
	حالة CPP_EOF:
	  اكسر;
	حالة CPP_NAME:
	  إذا (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.امن_افزودن (token->مقدار);
	  اذهب جمع_کن;
	حالة CPP_OPEN_BRACE:
	  ++nesting_عمق;
	  اذهب جمع_کن;
	حالة CPP_CLOSE_BRACE:
	  إذا (--nesting_عمق == 0 && bracket_عمق == 0)
	    stop = درست;
	  اذهب جمع_کن;
	حالة CPP_OPEN_PAREN:
	  ++bracket_عمق;
	  اذهب جمع_کن;
	حالة CPP_CLOSE_PAREN:
	  --bracket_عمق;
	  اذهب جمع_کن;
	حالة CPP_COLON:
	  ignore_label = خطأ;
	  اذهب جمع_کن;
	حالة CPP_SEMICOLON:
	  إذا (nesting_عمق == 0 && bracket_عمق == 0)
	    stop = درست;
	  اذهب جمع_کن;
	افتراضي:
	جمع_کن:
	  نشانهها.امن_افزودن (*token);
	  إذا (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  وإلا إذا (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_مقصد_pragma_eol (parser);
	  وإلا
	    c_parser_consume_token (parser);
	  إذا (stop)
	    اكسر;
	  استمر;
	}
      اكسر;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

ساكن فراغ
c_parser_omp_metadirective (c_parser *parser, منطقي *if_p)
{
  ساكن بیعلامت صحيح metadirective_region_شمار = 0;

  درخت ret;
  auto_vec<c_token> directive_نشانهها;
  auto_vec<c_token> body_نشانهها;
  auto_vec<درخت> body_labels;
  auto_vec<ثابت بنية c_omp_directive *> directives;
  auto_vec<درخت> ctxs;
  vec<بنية omp_variant> candidates;
  منطقي default_دیده = خطأ;
  صحيح directive_token_idx = 0;
  درخت standalone_body = NULL_درخت;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  منطقي requires_body = خطأ;

  ret = make_گره (OMP_METADIRECTIVE);
  مجموعه_عبارت_LOCATION (ret, pragma_loc);
  درخت_TYPE (ret) = void_type_گره;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_درخت;

  c_parser_consume_pragma (parser);
  طالما (c_parser_بعدی_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      إذا (c_parser_بعدی_token_is_not (parser, CPP_NAME)
	  && c_parser_بعدی_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  اذهب error;
	}

      location_t تطابق_loc = c_parser_peek_token (parser)->location;
      ثابت حرف *p = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      إذا (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.جمع_کن_fixit_replace (تطابق_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      منطقي default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      إذا (default_p)
	{
	  إذا (default_دیده)
	    {
	      error_at (تطابق_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      اذهب error;
	    }
	  default_دیده = درست;
	}
      وإلا إذا (default_دیده)
	{
	  error_at (تطابق_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  اذهب error;
	}
      إذا (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (تطابق_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  اذهب error;
	}

      matching_parens parens;
      درخت ctx = NULL_درخت;
      منطقي skip = خطأ;

      إذا (!parens.require_open (parser))
	اذهب error;

      إذا (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_درخت);
	  إذا (ctx == error_mark_گره)
	    اذهب error;
	  ctx = omp_check_context_selector (تطابق_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  إذا (ctx == error_mark_گره)
	    اذهب error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_درخت, خطأ) == 0);

	  إذا (c_parser_بعدی_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      اذهب error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ثابت حرف *directive[3] = {};
      صحيح i;
      لكل (i = 0; i < 3; i++)
	{
	  درخت id;
	  إذا (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      إذا (i == 0)
		directive[i++] = "nothing";
	      اكسر;
	    }
	  وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->مقدار;
	  وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      تعداد rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  وإلا
	    اكسر;

	  directive[i] = IDENTIFIER_اشاره_گر (id);
	}
      إذا (i == 0)
	{
	  error_at (loc, "expected directive name");
	  اذهب error;
	}

      ثابت بنية c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      إذا (omp_directive == عدم)
	{
	  لكل (صحيح j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  اذهب error;
	}
      وإلا
	{
	  صحيح token_شمار = 0;
	  إذا (omp_directive->اولی) token_شمار++;
	  إذا (omp_directive->دومی) token_شمار++;
	  إذا (omp_directive->سوم) token_شمار++;
	  لكل (صحيح j = 0; j < token_شمار; j++)
	    c_parser_consume_token (parser);
	}
      إذا (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  اذهب error;
	}
      إذا (omp_directive->نوع == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  اذهب error;
	}
      إذا (omp_directive->نوع == C_OMP_DIR_CONSTRUCT)
	requires_body = درست;

      إذا (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_نوع = (تعداد pragma_نوع) omp_directive->id;

	  directives.امن_افزودن (omp_directive);
	  directive_نشانهها.امن_افزودن (pragma_token);
	  ctxs.امن_افزودن (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      صحيح nesting_عمق = 0;
      طالما (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  بدل (token->type)
	    {
	    حالة CPP_EOF:
	    حالة CPP_PRAGMA_EOL:
	      اكسر;
	    حالة CPP_OPEN_PAREN:
	      ++nesting_عمق;
	      اذهب جمع_کن;
	    حالة CPP_CLOSE_PAREN:
	      إذا (nesting_عمق-- == 0)
		{
		  c_parser_consume_token (parser);
		  اكسر;
		}
	      اذهب جمع_کن;
	    افتراضي:
	    جمع_کن:
	      إذا (!skip)
		directive_نشانهها.امن_افزودن (*token);
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  اكسر;
	}

      إذا (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, حجم (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_نشانهها.امن_افزودن (eol_token);
	}
    }
  c_parser_skip_مقصد_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  إذا (ctxs.درازی () == 1)
    {
      درخت ctx = ctxs[0];
      إذا (ctx == NULL_درخت
	  || (omp_context_selector_matches (ctx, NULL_درخت, خطأ) == 1
	      && directive_نشانهها[0].pragma_نوع == PRAGMA_OMP_NOTHING))
	أرجع;
    }

  إذا (!default_دیده)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ثابت بنية c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", عدم, عدم);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_نوع = PRAGMA_OMP_NOTHING;

      directives.امن_افزودن (omp_directive);
      directive_نشانهها.امن_افزودن (pragma_token);
      ctxs.امن_افزودن (NULL_درخت);

      c_token eol_token;
      memset (&eol_token, 0, حجم (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_نشانهها.امن_افزودن (eol_token);
    }

  إذا (requires_body)
    analyze_metadirective_body (parser, body_نشانهها, body_labels);

  /* Process each candidate directive.  */
  بیعلامت i;
  درخت ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> نشانهها;

      /* Add the directive tokens.  */
      افعل
	نشانهها.امن_افزودن (directive_نشانهها [directive_token_idx++]);
      طالما (نشانهها.آخرین ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_نشانهها.is_خالی ());
      لكل (بیعلامت j = 0; j < body_نشانهها.درازی (); j++)
	نشانهها.امن_افزودن (body_نشانهها[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, حجم (eof_token));
      eof_token.type = CPP_EOF;
      نشانهها.امن_افزودن (eof_token);
      نشانهها.امن_افزودن (eof_token);

      بیعلامت صحيح old_نشانهها_avail = parser->نشانهها_avail;
      c_token *old_نشانهها = parser->نشانهها;
      بنية omp_attribute_pragma_state *old_درون_omp_attribute_pragma
	= parser->درون_omp_attribute_pragma;
      بنية omp_metadirective_parse_داده *old_state
	= parser->omp_metadirective_state;

      بنية omp_metadirective_parse_داده new_state;
      new_state.body_labels = &body_labels;
      new_state.region_رقم = ++metadirective_region_شمار;

      parser->نشانهها = نشانهها.آدرس ();
      parser->نشانهها_avail = نشانهها.درازی ();
      parser->درون_omp_attribute_pragma = عدم;
      parser->omp_metadirective_state = &new_state;

      صحيح prev_errorcount = errorcount;
      درخت directive = c_begin_compound_stmt (درست);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_درخت);
      directive = c_انتها_compound_stmt (pragma_loc, directive, درست);
      منطقي standalone_p
	= directives[i]->نوع == C_OMP_DIR_STANDALONE
	  || directives[i]->نوع == C_OMP_DIR_UTILITY;
      إذا (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  إذا (standalone_body == NULL_درخت)
	    {
	      standalone_body = افزودن_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = برداشت_stmt_list (standalone_body);
	    }
	  وإلا
	    c_parser_skip_مقصد_انتها_از_بلوک_or_statement (parser, درست);
	}

      درخت body = standalone_p ? standalone_body : NULL_درخت;
      درخت variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      إذا (errorcount == prev_errorcount)
	{
	  gcc_assert (parser->نشانهها_avail == 2);
	  gcc_assert (c_parser_بعدی_token_is (parser, CPP_EOF));
	  gcc_assert (c_parser_peek_2nd_token (parser)->type == CPP_EOF);
	}

      parser->نشانهها = old_نشانهها;
      parser->نشانهها_avail = old_نشانهها_avail;
      parser->درون_omp_attribute_pragma = old_درون_omp_attribute_pragma;
      parser->omp_metadirective_state = old_state;
    }

  /* Try to resolve the metadirective early.  */
  candidates = omp_early_resolve_metadirective (ret);
  إذا (!candidates.is_خالی ())
    ret = c_omp_expand_variant_construct (candidates);

  جمع_کن_stmt (ret);
  أرجع;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  إذا (parser->درون_pragma)
    c_parser_skip_مقصد_pragma_eol (parser, خطأ);
}

/* Main entry point to parsing most OpenMP pragmas.  */

ساكن فراغ
c_parser_omp_construct (c_parser *parser, منطقي *if_p)
{
  تعداد pragma_نوع p_نوع;
  location_t loc;
  درخت stmt;
  حرف p_name[حجم "#pragma omp teams distribute parallel for simd"];
  omp_clause_ماسک ماسک (0);

  loc = c_parser_peek_token (parser)->location;
  p_نوع = c_parser_peek_token (parser)->pragma_نوع;
  c_parser_consume_pragma (parser);

  بدل (p_نوع)
    {
    حالة PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, درست);
      أرجع;
    حالة PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      اكسر;
    حالة PRAGMA_OACC_داده:
      stmt = c_parser_oacc_داده (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OACC_HOST_داده:
      stmt = c_parser_oacc_host_داده (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OACC_KERNELS:
    حالة PRAGMA_OACC_PARALLEL:
    حالة PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_نوع, p_name, if_p);
      اكسر;
    حالة PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      اكسر;
    حالة PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, خطأ);
      أرجع;
    حالة PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, ماسک, عدم, if_p,
				  UNKNOWN_LOCATION);
      اكسر;
    حالة PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, ماسک, عدم);
      اكسر;
    حالة PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, ماسک, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      أرجع;
    حالة PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  إذا (stmt && stmt != error_mark_گره)
    gcc_assert (عبارت_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#تعریف_کن OMP_GROUPPRIVATE_CLAUSE_ماسک					\
	( (OMP_CLAUSE_ماسک_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

ساكن فراغ
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  درخت vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
  درخت clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_ماسک,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (فراغ) vars;
  (فراغ) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

ساكن فراغ
c_parser_omp_threadprivate (c_parser *parser)
{
  درخت vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  لكل (t = vars; t; t = درخت_CHAIN (t))
    {
      درخت v = درخت_PURPOSE (t);
      loc = عبارت_LOCATION (درخت_مقدار (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      إذا (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      وإلا إذا (درخت_استفاده_شده (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      وإلا إذا (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      وإلا إذا (درخت_TYPE (v) == error_mark_گره)
	;
      وإلا إذا (! COMPLETE_TYPE_P (درخت_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      وإلا
	{
	  إذا (! DECL_THREAD_LOCAL_P (v))
	    {
	      مجموعه_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      إذا (DECL_RTL_مجموعه_P (v))
		make_decl_rtl (v);
	    }
	  C_DECL_THREADPRIVATE_P (v) = 1;
	}
    }

  c_parser_skip_مقصد_pragma_eol (parser);
}

/* Parse a transaction attribute (GCC Extension).

   transaction-attribute:
     gnu-attributes
     attribute-specifier
*/

ساكن درخت
c_parser_transaction_صفات (c_parser *parser)
{
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ATTRIBUTE))
    أرجع c_parser_gnu_صفات (parser);

  إذا (!c_parser_بعدی_token_is (parser, CPP_OPEN_مربع))
    أرجع NULL_درخت;
  أرجع c_parser_std_attribute_specifier (parser, درست);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

ساكن درخت
c_parser_transaction (c_parser *parser, تعداد rid keyword)
{
  بیعلامت صحيح old_درون = parser->درون_transaction;
  بیعلامت صحيح this_درون = 1, new_درون;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_بعدی_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  إذا (keyword == RID_TRANSACTION_RELAXED)
    this_درون |= TM_STMT_ATTR_RELAXED;
  وإلا
    {
      attrs = c_parser_transaction_صفات (parser);
      إذا (attrs)
	this_درون |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_درون = this_درون | (old_درون & TM_STMT_ATTR_OUTER);

  parser->درون_transaction = new_درون;
  stmt = c_parser_compound_statement (parser);
  parser->درون_transaction = old_درون;

  إذا (flag_tm)
    stmt = c_پایان_transaction (loc, stmt, this_درون);
  وإلا
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  أرجع stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

ساكن بنية c_عبارت
c_parser_transaction_عبارت (c_parser *parser, تعداد rid keyword)
{
  بنية c_عبارت ret;
  بیعلامت صحيح old_درون = parser->درون_transaction;
  بیعلامت صحيح this_درون = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  درخت attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_بعدی_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  إذا (keyword == RID_TRANSACTION_RELAXED)
    this_درون |= TM_STMT_ATTR_RELAXED;
  وإلا
    {
      attrs = c_parser_transaction_صفات (parser);
      إذا (attrs)
	this_درون |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->درون_transaction = this_درون;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      درخت عبارت = c_parser_عبارت (parser).مقدار;
      ret.original_type = درخت_TYPE (عبارت);
      ret.مقدار = build1 (TRANSACTION_عبارت, ret.original_type, عبارت);
      إذا (this_درون & TM_STMT_ATTR_RELAXED)
	TRANSACTION_عبارت_RELAXED (ret.مقدار) = 1;
      مجموعه_عبارت_LOCATION (ret.مقدار, loc);
      ret.original_کد = TRANSACTION_عبارت;
      ret.m_decimal = 0;
      إذا (!parens.require_close (parser))
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, عدم);
	  اذهب error;
	}
    }
  وإلا
    {
     error:
      ret.مجموعه_error ();
      ret.original_کد = ERROR_MARK;
      ret.original_type = عدم;
    }
  parser->درون_transaction = old_درون;

  إذا (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  مجموعه_c_عبارت_منبع_range (&ret, loc, loc);

  أرجع ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

ساكن درخت
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  درخت attrs;
  منطقي is_outer = خطأ;

  gcc_assert (c_parser_بعدی_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_صفات (parser);
  إذا (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  إذا (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      اذهب ret_error;
    }
  وإلا إذا (parser->درون_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      اذهب ret_error;
    }
  وإلا إذا (is_outer)
    {
      إذا ((parser->درون_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  اذهب ret_error;
	}
    }
  وإلا إذا (parser->درون_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      اذهب ret_error;
    }

  أرجع جمع_کن_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  أرجع build1 (NOP_عبارت, void_type_گره, error_mark_گره);
}

/* Parse a single source file.  */

فراغ
c_parse_file (فراغ)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, حجم tparser);
  tparser.translate_رشتهها_p = درست;
  tparser.نشانهها = &tparser.نشانهها_buf[0];
  the_parser = &tparser;

  إذا (c_parser_peek_token (&tparser)->pragma_نوع == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  وإلا
    c_common_no_بیشتر_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  إذا (tparser.نشانهها == &tparser.نشانهها_buf[0])
    the_parser->نشانهها = &the_parser->نشانهها_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  إذا (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = عدم;
}

فراغ
c_init_preprocess (فراغ)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, حجم (c_parser));
  the_parser->نشانهها = &the_parser->نشانهها_buf[0];
}

/* Parse the body of a function declaration marked with "__RTL".

   The RTL parser works on the level of characters read from a
   FILE *, whereas c_parser works at the level of tokens.
   Square this circle by consuming all of the tokens up to and
   including the closing brace, recording the start/end of the RTL
   fragment, and reopening the file and re-reading the relevant
   lines within the RTL parser.

   This requires the opening and closing braces of the C function
   to be on separate lines from the RTL they wrap.

   Take ownership of START_WITH_PASS, if non-NULL.  */

location_t
c_parser_parse_rtl_body (c_parser *parser, حرف *شروع_with_pass)
{
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      حرر (شروع_with_pass);
      أرجع c_parser_peek_token (parser)->location;
    }

  location_t شروع_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  صحيح رقم_open_braces = 1;
  طالما (1)
    {
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_BRACE:
	  رقم_open_braces++;
	  اكسر;
	حالة CPP_CLOSE_BRACE:
	  إذا (--رقم_open_braces == 0)
	    اذهب یافت_closing_brace;
	  اكسر;
	حالة CPP_EOF:
	  error_at (شروع_loc, "no closing brace");
	  حرر (شروع_with_pass);
	  أرجع c_parser_peek_token (parser)->location;
	افتراضي:
	  اكسر;
	}
      c_parser_consume_token (parser);
    }

 یافت_closing_brace:
  /* At the closing brace; record its location.  */
  location_t انتها_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  إذا (!read_rtl_function_body_from_file_range (شروع_loc, انتها_loc))
    {
      حرر (شروع_with_pass);
      أرجع انتها_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  پیاپی_rtl_passes (شروع_with_pass);
  أرجع انتها_loc;
}

#ضمن "gt-c-c-parser.h"
