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
#وصف_ڪريو INCLUDE_STRING
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

vec<وڻ> incomplete_رڪارڊ_decls;

فراغ
سيٽ_c_اظهار_ذريعو_range (c_اظهار *اظهار,
			 location_t شروعات, location_t پڄاڻي)
{
  اظهار->src_range.m_شروعات = شروعات;
  اظهار->src_range.m_پڄاڻي = پڄاڻي;
  إذا (اظهار->قدر)
    سيٽ_ذريعو_range (اظهار->قدر, شروعات, پڄاڻي);
}

فراغ
سيٽ_c_اظهار_ذريعو_range (c_اظهار *اظهار,
			 ذريعو_range src_range)
{
  اظهار->src_range = src_range;
  إذا (اظهار->قدر)
    سيٽ_ذريعو_range (اظهار->قدر, src_range);
}


/* Initialization routine for this file.  */

فراغ
c_parse_init (فراغ)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  بنانشان صحيح i;
  وڻ id;
  صحيح نقاب = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  نقاب |= D_CXXONLY;
  إذا (!flag_isoc99)
    نقاب |= D_C99;
  إذا (!flag_isoc23)
    نقاب |= D_C23;
  إذا (flag_no_asm)
    {
      نقاب |= D_ASM | D_EXT;
      إذا (!flag_isoc99)
	نقاب |= D_EXT89;
      إذا (!flag_isoc23)
	نقاب |= D_EXT11;
    }
  إذا (!c_dialect_objc ())
    نقاب |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<وڻ> ((صحيح) RID_MAX);
  لكل (i = 0; i < انگ_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      إذا (c_common_reswords[i].disable & نقاب)
	{
	  إذا (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].لفظ);
	      C_سيٽ_RID_ڪوڊ (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_لفظ (id) = 1;
	    }
	  استمر;
	}

      id = get_identifier (c_common_reswords[i].لفظ);
      C_سيٽ_RID_ڪوڊ (id, c_common_reswords[i].rid);
      C_IS_RESERVED_لفظ (id) = 1;
      ridpointers [(صحيح) c_common_reswords[i].rid] = id;
    }

  لكل (i = 0; i < انگ_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      حرف name[50];
      sprintf (name, "__int%d", int_n_معلومات[i].bitsize);
      id = get_identifier (name);
      C_سيٽ_RID_ڪوڊ (id, RID_پهريون_INT_N + i);
      C_IS_RESERVED_لفظ (id) = 1;

      sprintf (name, "__int%d__", int_n_معلومات[i].bitsize);
      id = get_identifier (name);
      C_سيٽ_RID_ڪوڊ (id, RID_پهريون_INT_N + i);
      C_IS_RESERVED_لفظ (id) = 1;
    }

  إذا (flag_openmp)
    {
      id = get_identifier ("omp_all_memory");
      C_سيٽ_RID_ڪوڊ (id, RID_OMP_ALL_يادگيري);
      C_IS_RESERVED_لفظ (id) = 1;
      ridpointers [RID_OMP_ALL_يادگيري] = id;
    }
}

/* A parser structure recording information about the state and
   context of parsing.  Includes lexer information with up to two
   tokens of look-ahead; more are not needed for C.  */
بنية GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) ٽوڪن;
  /* Buffer for look-ahead tokens.  */
  c_token ٽوڪن_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  بنانشان صحيح ٽوڪن_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_ٽوڪن;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  بنانشان صحيح raw_ٽوڪن_استعمال_ٿيل;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  منطقي error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  منطقي اندريون_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  منطقي اندريون_if_بلاڪ : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  منطقي lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  منطقي translate_لڙيون_p : 1;

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
  بنانشان صحيح اندريون_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  منطقي objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  منطقي ڏٺل_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  منطقي omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t آخري_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  بنية omp_for_parse_معلومات * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  بنية omp_attribute_pragma_state *اندريون_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  وڻ اندريون_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  بنية omp_metadirective_parse_معلومات * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
بنية GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_ٽوڪن;
  بنانشان صحيح save_ٽوڪن_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
بنية GTY(()) omp_begin_declare_variant_map_داخلا {
  وڻ variant;		/* The variant decl.  */
  وڻ id;		/* Name of base function.  */
  وڻ ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_داخلا, va_gc> *omp_begin_declare_variant_map;

ساكن وڻ omp_شروعات_variant_function (c_declarator *, وڻ);
ساكن فراغ omp_پڄاڻي_variant_function (وڻ, وڻ, وڻ);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_ٽوڪن_buf (c_parser *parser, بنانشان n)
{
  أرجع &parser->ٽوڪن_buf[n];
}

/* Return the error state of PARSER.  */

منطقي
c_parser_error (c_parser *parser)
{
  أرجع parser->error;
}

/* Set the error state of PARSER to ERR.  */

فراغ
c_parser_سيٽ_error (c_parser *parser, منطقي err)
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
  timevar_ڌڪو (TV_LEX);

  إذا (raw || vec_محفوظ_ڊيگهائي (parser->raw_ٽوڪن) == 0)
    {
      token->type = c_lex_with_flags (&token->قدر, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_قسم = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_قسم = PRAGMA_NONE;
    }
  وإلا
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_ٽوڪن)[parser->raw_ٽوڪن_استعمال_ٿيل];
      ++parser->raw_ٽوڪن_استعمال_ٿيل;
      إذا (parser->raw_ٽوڪن_استعمال_ٿيل == vec_محفوظ_ڊيگهائي (parser->raw_ٽوڪن))
	{
	  vec_free (parser->raw_ٽوڪن);
	  parser->raw_ٽوڪن_استعمال_ٿيل = 0;
	}
    }

  إذا (raw)
    اذهب ٻاهريون;

  بدل (token->type)
    {
    حالة CPP_NAME:
      {
	وڻ decl;

	منطقي objc_force_identifier = parser->objc_need_raw_identifier;
	إذا (c_dialect_objc ())
	  parser->objc_need_raw_identifier = خطأ;

	إذا (C_IS_RESERVED_لفظ (token->قدر))
	  {
	    تعداد rid rid_ڪوڊ = C_RID_ڪوڊ (token->قدر);

	    إذا (rid_ڪوڊ == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->قدر);
	      }
	    وإلا إذا (rid_ڪوڊ >= RID_پهريون_ADDR_SPACE
		     && rid_ڪوڊ <= RID_آخري_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_ڪوڊ - RID_پهريون_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_قسم = C_ID_ADDRSPACE;
		token->keyword = rid_ڪوڊ;
		اكسر;
	      }
	    وإلا إذا (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_ڪوڊ))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		إذا (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_ڪوڊ;
		    اكسر;
		  }
		وإلا إذا (parser->objc_could_be_foreach_context
			 && rid_ڪوڊ == RID_اندريون)
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
		    token->keyword = rid_ڪوڊ;
		    اكسر;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    وإلا إذا (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_ڪوڊ))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		إذا (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_ڪوڊ;
		    اكسر;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    وإلا إذا (c_dialect_objc ()
		     && (OBJC_IS_AT_KEYWORD (rid_ڪوڊ)
			 || OBJC_IS_CXX_KEYWORD (rid_ڪوڊ)))
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
		token->keyword = rid_ڪوڊ;
		اكسر;
	      }
	  }

	decl = lookup_name (token->قدر);
	إذا (decl)
	  {
	    إذا (وڻ_ڪوڊ (decl) == TYPE_DECL)
	      {
		token->id_قسم = C_ID_TYPENAME;
		اكسر;
	      }
	  }
	وإلا إذا (c_dialect_objc ())
	  {
	    وڻ objc_interface_decl = objc_is_class_name (token->قدر);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    إذا (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->قدر = objc_interface_decl;
		token->id_قسم = C_ID_CLASSNAME;
		اكسر;
	      }
	  }
        token->id_قسم = C_ID_ID;
      }
      اكسر;
    حالة CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      بدل (C_RID_ڪوڊ (token->قدر))
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
	حالة RID_ذاتي:   token->keyword = RID_AT_ذاتي; اكسر;
	حالة RID_PROTECTED: token->keyword = RID_AT_PROTECTED; اكسر;
	حالة RID_عوامي:    token->keyword = RID_AT_عوامي; اكسر;
	حالة RID_THROW:     token->keyword = RID_AT_THROW; اكسر;
	حالة RID_TRY:       token->keyword = RID_AT_TRY; اكسر;
	حالة RID_CATCH:     token->keyword = RID_AT_CATCH; اكسر;
	حالة RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; اكسر;
	افتراضي:            token->keyword = C_RID_ڪوڊ (token->قدر);
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
      token->pragma_قسم = (تعداد pragma_قسم) وڻ_INT_CST_هيٺيون (token->قدر);
      token->قدر = عدم;
      اكسر;
    افتراضي:
      اكسر;
    }
 ٻاهريون:
  timevar_ڪڍو (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  إذا (parser->ٽوڪن_avail == 0)
    {
      c_lex_one_token (parser, &parser->ٽوڪن[0]);
      parser->ٽوڪن_avail = 1;
    }
  أرجع &parser->ٽوڪن[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  إذا (parser->ٽوڪن_avail >= 2)
    أرجع &parser->ٽوڪن[1];
  gcc_assert (parser->ٽوڪن_avail == 1);
  gcc_assert (parser->ٽوڪن[0].type != CPP_EOF);
  gcc_assert (parser->ٽوڪن[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->ٽوڪن[1]);
  parser->ٽوڪن_avail = 2;
  أرجع &parser->ٽوڪن[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, بنانشان صحيح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  إذا (parser->ٽوڪن_avail >= n)
    أرجع &parser->ٽوڪن[n - 1];
  gcc_assert (parser->ٽوڪن_avail == n - 1);
  c_lex_one_token (parser, &parser->ٽوڪن[n - 1]);
  parser->ٽوڪن_avail = n;
  أرجع &parser->ٽوڪن[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, بنانشان صحيح n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  إذا (parser->ٽوڪن_avail >= n)
    أرجع &parser->ٽوڪن[n - 1];
  بنانشان صحيح raw_len = vec_محفوظ_ڊيگهائي (parser->raw_ٽوڪن);
  بنانشان صحيح raw_avail
    = parser->ٽوڪن_avail + raw_len - parser->raw_ٽوڪن_استعمال_ٿيل;
  gcc_assert (raw_avail >= n - 1);
  إذا (raw_avail >= n)
    أرجع &(*parser->raw_ٽوڪن)[parser->raw_ٽوڪن_استعمال_ٿيل
				  + n - 1 - parser->ٽوڪن_avail];
  vec_محفوظ_reserve (parser->raw_ٽوڪن, 1);
  parser->raw_ٽوڪن->تيز_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_ٽوڪن)[raw_len], سچ);
  أرجع &(*parser->raw_ٽوڪن)[raw_len];
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
      أرجع سچ;
    افتراضي:
      إذا (keyword >= RID_پهريون_INT_N
	  && keyword < RID_پهريون_INT_N + انگ_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_پهريون_INT_N])
	أرجع سچ;
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
      بدل (token->id_قسم)
	{
	حالة C_ID_ID:
	  أرجع خطأ;
	حالة C_ID_ADDRSPACE:
	  أرجع سچ;
	حالة C_ID_TYPENAME:
	  أرجع سچ;
	حالة C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  أرجع سچ;
	افتراضي:
	  gcc_unreachable ();
	}
    حالة CPP_KEYWORD:
      أرجع c_keyword_starts_typename (token->keyword);
    حالة CPP_LESS:
      إذا (c_dialect_objc ())
	أرجع سچ;
      أرجع خطأ;
    افتراضي:
      أرجع خطأ;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

ساكن مضمن منطقي
c_parser_ايندڙ_ٽوڪن_شروعات_typename (c_parser *parser, تعداد c_lookahead_قسم la,
				     بنانشان صحيح n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  إذا (c_token_starts_typename (token))
    أرجع سچ;

  /* Try a bit harder to detect an unknown typename.  */
  إذا (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_قسم == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->قدر))
    أرجع سچ;

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
	حالة RID_رجسٽر:
	حالة RID_STATIC:
	حالة RID_THREAD:
	  أرجع سچ;
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
      بدل (token->id_قسم)
	{
	حالة C_ID_ADDRSPACE:
	  أرجع سچ;
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
	  أرجع سچ;
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
c_parser_ايندڙ_token_is_qualifier (c_parser *parser)
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
      بدل (token->id_قسم)
	{
	حالة C_ID_ID:
	  أرجع خطأ;
	حالة C_ID_ADDRSPACE:
	  أرجع سچ;
	حالة C_ID_TYPENAME:
	  أرجع سچ;
	حالة C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  أرجع سچ;
	افتراضي:
	  gcc_unreachable ();
	}
    حالة CPP_KEYWORD:
      بدل (token->keyword)
	{
	حالة RID_STATIC:
	حالة RID_EXTERN:
	حالة RID_رجسٽر:
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
	  أرجع سچ;
	افتراضي:
	  إذا (token->keyword >= RID_پهريون_INT_N
	      && token->keyword < RID_پهريون_INT_N + انگ_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_پهريون_INT_N])
	    أرجع سچ;
	  أرجع خطأ;
	}
    حالة CPP_LESS:
      إذا (c_dialect_objc ())
	أرجع سچ;
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
    أرجع سچ;
  وإلا
    أرجع خطأ;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
منطقي
c_parser_ايندڙ_token_starts_declspecs (c_parser *parser)
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
      && token->id_قسم == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    أرجع خطأ;

  أرجع c_token_starts_declspecs (token);
}

ساكن منطقي c_parser_check_متوازن_raw_token_sequence (c_parser *,
							بنانشان صحيح *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
منطقي
c_parser_ايندڙ_ٽوڪن_شروعات_declaration (c_parser *parser, بنانشان صحيح n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  إذا (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_قسم == C_ID_CLASSNAME
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
	أرجع سچ;
      أرجع c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  إذا (c_token_starts_declaration (token))
    أرجع سچ;

  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, cla_nonabstract_decl, n))
    أرجع سچ;

  أرجع خطأ;
}

/* Consume the next token from PARSER.  */

فراغ
c_parser_consume_token (c_parser *parser)
{
  gcc_assert (parser->ٽوڪن_avail >= 1);
  gcc_assert (parser->ٽوڪن[0].type != CPP_EOF);
  gcc_assert (!parser->اندريون_pragma || parser->ٽوڪن[0].type != CPP_PRAGMA_EOL);
  /* CPP_PRAGMA should not show up here except if there was an error or inside
     another pragma.  */
  gcc_assert (parser->اندريون_pragma
	      || parser->error
	      || parser->ٽوڪن[0].type != CPP_PRAGMA);
  parser->آخري_token_location = parser->ٽوڪن[0].location;
  إذا (parser->ٽوڪن != &parser->ٽوڪن_buf[0])
    parser->ٽوڪن++;
  وإلا إذا (parser->ٽوڪن_avail >= 2)
    {
      parser->ٽوڪن[0] = parser->ٽوڪن[1];
      إذا (parser->ٽوڪن_avail >= 3)
        {
          parser->ٽوڪن[1] = parser->ٽوڪن[2];
          إذا (parser->ٽوڪن_avail >= 4)
            parser->ٽوڪن[2] = parser->ٽوڪن[3];
        }
    }
  parser->ٽوڪن_avail--;
  parser->ڏٺل_string_literal = خطأ;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

ساكن فراغ
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->اندريون_pragma);
  gcc_assert (parser->ٽوڪن_avail >= 1);
  gcc_assert (parser->ٽوڪن[0].type == CPP_PRAGMA);
  إذا (parser->ٽوڪن != &parser->ٽوڪن_buf[0])
    parser->ٽوڪن++;
  وإلا إذا (parser->ٽوڪن_avail >= 2)
    {
      parser->ٽوڪن[0] = parser->ٽوڪن[1];
      إذا (parser->ٽوڪن_avail >= 3)
	parser->ٽوڪن[1] = parser->ٽوڪن[2];
    }
  parser->ٽوڪن_avail--;
  parser->اندريون_pragma = سچ;
}

/* Update the global input_location from TOKEN.  */
ساكن مضمن فراغ
c_parser_سيٽ_ذريعو_position_from_token (c_token *token)
{
  إذا (token->type != CPP_EOF)
    {
      داخلا_location = token->location;
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
c_parser_peek_conflict_marker (c_parser *parser, تعداد cpp_ttype tok1_قسم,
			       location_t *ٻاهريون_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  إذا (token2->type != tok1_قسم)
    أرجع خطأ;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  إذا (token3->type != tok1_قسم)
    أرجع خطأ;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  إذا (token4->type != conflict_marker_get_final_tok_قسم (tok1_قسم))
    أرجع خطأ;

  /* It must be at the start of the line.  */
  location_t شروعات_loc = c_parser_peek_token (parser)->location;
  إذا (LOCATION_ڪالم (شروعات_loc) != 1)
    أرجع خطأ;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t پڄاڻي_loc = get_پڄاڻي (token4->location);
  *ٻاهريون_loc = make_location (شروعات_loc, شروعات_loc, پڄاڻي_loc);

  أرجع سچ;
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
  parser->error = سچ;
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
	  أرجع سچ;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_گروهه d;
  name_hint h;
  إذا (parser->ڏٺل_string_literal && token->type == CPP_NAME)
    {
      وڻ name = token->قدر;
      ثابت حرف *token_name = IDENTIFIER_اشارو (name);
      ثابت حرف *سرو_hint
	= get_c_stdlib_سرو_for_string_macro_name (token_name);
      إذا (سرو_hint != عدم)
	h = name_hint (خالي_اشارو,
		       std::make_unique<suggest_missing_سرو>
			 (token->location,
			  token_name,
			  سرو_hint));
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
		 token->قدر, /*flags=*/0, richloc);
  أرجع سچ;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

منطقي
c_parser_error (c_parser *parser, ثابت حرف *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_سيٽ_ذريعو_position_from_token (token);
  rich_location richloc (سٽ_جدول, داخلا_location);
  أرجع c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

سانچو <قسم_نالو traits_t>
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

  فراغ skip_until_مليو_close (c_parser *parser) ثابت
  {
    c_parser_skip_until_مليو (parser, traits_t::close_token_type,
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
get_matching_نشان (تعداد cpp_ttype type)
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
  إذا (c_parser_ايندڙ_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      أرجع سچ;
    }
  وإلا
    {
      location_t ايندڙ_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (ايندڙ_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      إذا (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->آخري_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      منطقي added_matching_location = خطأ;
      إذا (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.جوڙيو_location_if_nearby (*global_dc, matching_location);

      إذا (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	إذا (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_نشان (type));

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
  إذا (c_parser_ايندڙ_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      أرجع سچ;
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
c_parser_skip_until_مليو (c_parser *parser,
			   تعداد cpp_ttype type,
			   ثابت حرف *msgid,
			   location_t matching_location)
{
  بنانشان nesting_اونهائي = 0;

  إذا (c_parser_require (parser, type, msgid, matching_location))
    {
      إذا (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->اندريون_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    {
	      parser->ٽوڪن = parser->اندريون_omp_attribute_pragma->save_ٽوڪن;
	      parser->ٽوڪن_avail
		= parser->اندريون_omp_attribute_pragma->save_ٽوڪن_avail;
	      parser->اندريون_omp_attribute_pragma = عدم;
	    }
	}
      أرجع;
    }

  /* Skip tokens until the desired token is found.  */
  طالما (سچ)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      إذا (token->type == type && !nesting_اونهائي)
	{
	  c_parser_consume_token (parser);
	  إذا (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->اندريون_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      إذا (token->type == CPP_EOF)
		{
		  parser->ٽوڪن = parser->اندريون_omp_attribute_pragma->save_ٽوڪن;
		  parser->ٽوڪن_avail
		    = parser->اندريون_omp_attribute_pragma->save_ٽوڪن_avail;
		  parser->اندريون_omp_attribute_pragma = عدم;
		}
	    }
	  اكسر;
	}

      /* If we've run out of tokens, stop.  */
      إذا (token->type == CPP_EOF)
	أرجع;
      إذا (token->type == CPP_PRAGMA_EOL && parser->اندريون_pragma)
	أرجع;
      إذا (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_چورس)
	++nesting_اونهائي;
      وإلا إذا (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_چورس)
	{
	  إذا (nesting_اونهائي-- == 0)
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
c_parser_skip_منزل_پڇاڙي_جو_parameter (c_parser *parser)
{
  بنانشان nesting_اونهائي = 0;

  طالما (سچ)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_اونهائي)
	اكسر;
      /* If we've run out of tokens, stop.  */
      إذا (token->type == CPP_EOF)
	أرجع;
      إذا (token->type == CPP_PRAGMA_EOL && parser->اندريون_pragma)
	أرجع;
      إذا (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_چورس)
	++nesting_اونهائي;
      وإلا إذا (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_چورس)
	{
	  إذا (nesting_اونهائي-- == 0)
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
c_parser_skip_منزل_closing_brace (c_parser *parser)
{
  بنانشان nesting_اونهائي = 0;

  طالما (سچ)
    {
      c_token *token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_PRAGMA_EOL:
	  إذا (!parser->اندريون_pragma)
	    اكسر;
	  /* FALLTHRU */
	حالة CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  أرجع خطأ;

	حالة CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  إذا (nesting_اونهائي-- == 0)
	    أرجع سچ;
	  اكسر;

	حالة CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_اونهائي;
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
c_parser_skip_منزل_pragma_eol (c_parser *parser, منطقي error_if_not_eol = سچ)
{
  gcc_assert (parser->اندريون_pragma);
  parser->اندريون_pragma = خطأ;

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

  إذا (parser->اندريون_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_EOF)
	{
	  parser->ٽوڪن = parser->اندريون_omp_attribute_pragma->save_ٽوڪن;
	  parser->ٽوڪن_avail
	    = parser->اندريون_omp_attribute_pragma->save_ٽوڪن_avail;
	  parser->اندريون_omp_attribute_pragma = عدم;
	}
    }

  parser->error = خطأ;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
ساكن فراغ
c_parser_skip_منزل_pragma_omp_پڇاڙي_declare_variant (c_parser *parser)
{
  لكل (صحيح اونهائي = 0; اونهائي >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_PRAGMA_EOL:
	  إذا (!parser->اندريون_pragma)
	    اكسر;
	  /* FALLTHRU */
	حالة CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  أرجع;

	حالة CPP_PRAGMA:
	  إذا ((token->pragma_قسم == PRAGMA_OMP_BEGIN
	       || token->pragma_قسم == PRAGMA_OMP_پڇاڙي)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      وڻ id1 = c_parser_peek_nth_token (parser, 2)->قدر;
	      وڻ id2 = c_parser_peek_nth_token (parser, 3)->قدر;
	      إذا (strcmp (IDENTIFIER_اشارو (id1), "declare") == 0
		  && strcmp (IDENTIFIER_اشارو (id2), "variant") == 0)
		{
		  إذا (token->pragma_قسم == PRAGMA_OMP_BEGIN)
		    اونهائي++;
		  وإلا
		    اونهائي--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
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
c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (c_parser *parser,
					    منطقي metadirective_p = خطأ)
{
  بنانشان nesting_اونهائي = 0;
  صحيح bracket_اونهائي = 0;
  منطقي save_error = parser->error;

  طالما (سچ)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      بدل (token->type)
	{
	حالة CPP_EOF:
	  أرجع;

	حالة CPP_PRAGMA_EOL:
	  إذا (parser->اندريون_pragma)
	    أرجع;
	  اكسر;

	حالة CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  إذا (!nesting_اونهائي && (!metadirective_p || bracket_اونهائي <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      اذهب ختم;
	    }
	  اكسر;

	حالة CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  إذا ((nesting_اونهائي == 0 || --nesting_اونهائي == 0)
	      && (!metadirective_p || bracket_اونهائي <= 0))
	    {
	      c_parser_consume_token (parser);
	      اذهب ختم;
	    }
	  اكسر;

	حالة CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_اونهائي;
	  اكسر;

	حالة CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  إذا (metadirective_p && nesting_اونهائي == 0)
	    ++bracket_اونهائي;
	  اكسر;

	حالة CPP_CLOSE_PAREN:
	  إذا (metadirective_p && nesting_اونهائي == 0)
	    --bracket_اونهائي;
	  اكسر;

	حالة CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
	  parser->error = save_error;
	  استمر;

	افتراضي:
	  اكسر;
	}

      c_parser_consume_token (parser);
    }

 ختم:
  parser->error = خطأ;
}

/* CPP's options (initialized by c-opts.cc).  */
خارجي cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

ساكن مضمن صحيح
disable_extension_diagnostics (فراغ)
{
  صحيح ret = (pedantic
	     | (warn_اشارو_arith << 1)
	     | (warn_traditional << 2)
	     | (flag_iso << 3)
	     | (warn_long_long << 4)
	     | (warn_cxx_compat << 5)
	     | (warn_overlength_لڙيون << 6)
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
  warn_اشارو_arith = 0;
  cpp_opts->cpp_warn_traditional = warn_traditional = 0;
  flag_iso = 0;
  cpp_opts->cpp_warn_long_long = warn_long_long = 0;
  warn_cxx_compat = 0;
  warn_overlength_لڙيون = 0;
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
  warn_اشارو_arith = (flags >> 1) & 1;
  cpp_opts->cpp_warn_traditional = warn_traditional = (flags >> 2) & 1;
  flag_iso = (flags >> 3) & 1;
  cpp_opts->cpp_warn_long_long = warn_long_long = (flags >> 4) & 1;
  warn_cxx_compat = (flags >> 5) & 1;
  warn_overlength_لڙيون = (flags >> 6) & 1;
  /* See above for why is this needed.  */
  warn_c90_c99_compat = (flags >> 7) & 1 ? 1 : ((flags >> 8) & 1 ? -1 : 0);
  warn_c99_c11_compat = (flags >> 9) & 1 ? 1 : ((flags >> 10) & 1 ? -1 : 0);
  warn_c11_c23_compat = (flags >> 11) & 1 ? 1 : ((flags >> 12) & 1 ? -1 : 0);
  warn_c23_c2y_compat = (flags >> 13) & 1 ? 1 : ((flags >> 14) & 1 ? -1 : 0);
}

/* Helper data structure for parsing #pragma acc routine.  */
بنية oacc_routine_معلومات {
  منطقي error_ڏٺل; /* Set if error has been reported.  */
  منطقي fndecl_ڏٺل; /* Set if one fn decl/definition has been seen already.  */
  وڻ clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
ساكن وڻ objc_foreach_break_label, objc_foreach_continue_label;

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
بنية omp_for_parse_معلومات {
  تعداد وڻ_ڪوڊ_2 ڪوڊ;
  وڻ declv, condv, incrv, initv;
  وڻ pre_body;
  وڻ bindings;
  صحيح ڳڻپ;	/* Expected nesting depth.  */
  صحيح اونهائي;	/* Current nesting depth.  */
  location_t for_loc;
  منطقي ordered : 1;
  منطقي inscan : 1;
  منطقي want_nested_loop : 1;
  منطقي اندريون_intervening_ڪوڊ : 1;
  منطقي saw_intervening_ڪوڊ: 1;
  منطقي perfect_nesting_fail : 1;
  منطقي fail : 1;
};

بنية attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  منطقي musttail_p;

  فراغ reset () { musttail_p = خطأ; }
};

ساكن منطقي c_parser_nth_token_starts_std_خاصيتون (c_parser *,
						      بنانشان صحيح);
ساكن وڻ c_parser_std_attribute_specifier_sequence (c_parser *);
ساكن فراغ c_parser_external_declaration (c_parser *);
ساكن فراغ c_parser_asm_definition (c_parser *);
ساكن وڻ c_parser_declaration_or_fndef (c_parser *, منطقي, منطقي, منطقي,
					   منطقي, منطقي, منطقي, وڻ * = عدم,
					   vec<c_token> * = عدم,
					   منطقي have_attrs = خطأ,
					   وڻ attrs = عدم,
					   بنية oacc_routine_معلومات * = عدم,
					   منطقي * = عدم);
ساكن منطقي c_parser_handle_statement_omp_خاصيتون (c_parser *, وڻ &,
						      منطقي *);
ساكن فراغ c_parser_static_assert_declaration_no_semi (c_parser *);
ساكن فراغ c_parser_static_assert_declaration (c_parser *);
ساكن بنية c_typespec c_parser_enum_specifier (c_parser *);
ساكن بنية c_typespec c_parser_struct_or_union_specifier (c_parser *);
ساكن وڻ c_parser_struct_declaration (c_parser *, وڻ *);
ساكن بنية c_typespec c_parser_typeof_specifier (c_parser *);
ساكن وڻ c_parser_alignas_specifier (c_parser *);
ساكن بنية c_declarator *c_parser_سڌو_declarator (c_parser *, منطقي,
							c_dtr_syn, منطقي *);
ساكن بنية c_declarator *c_parser_سڌو_declarator_inner (c_parser *,
							      منطقي,
							      بنية c_declarator *);
ساكن بنية c_arg_info *c_parser_parms_declarator (c_parser *, منطقي, وڻ,
						     منطقي);
ساكن بنية c_arg_info *c_parser_parms_list_declarator (c_parser *, وڻ,
							  وڻ, منطقي);
ساكن بنية c_parm *c_parser_parameter_declaration (c_parser *, وڻ, منطقي);
ساكن وڻ c_parser_asm_string_literal (c_parser *);
ساكن وڻ c_parser_simple_asm_اظهار (c_parser *);
ساكن وڻ c_parser_gnu_خاصيتون (c_parser *);
ساكن بنية c_اظهار c_parser_initializer (c_parser *, وڻ);
ساكن بنية c_اظهار c_parser_braced_init (c_parser *, وڻ, منطقي,
					   بنية obstack *, منطقي);
ساكن فراغ c_parser_initelt (c_parser *, بنية obstack *);
ساكن فراغ c_parser_initval (c_parser *, بنية c_اظهار *,
			      بنية obstack *);
ساكن وڻ c_parser_compound_statement (c_parser *, location_t * = عدم);
ساكن location_t c_parser_compound_statement_nostart (c_parser *);
ساكن فراغ c_parser_label (c_parser *, وڻ);
ساكن فراغ c_parser_statement (c_parser *, منطقي *, location_t * = عدم);
ساكن فراغ c_parser_statement_after_labels (c_parser *, منطقي *, وڻ,
					     vec<وڻ> * = عدم,
					     attr_state = {});
ساكن وڻ c_parser_c99_بلاڪ_statement (c_parser *, منطقي *,
					  location_t * = عدم);
ساكن فراغ c_parser_if_statement (c_parser *, منطقي *, vec<وڻ> *);
ساكن فراغ c_parser_switch_statement (c_parser *, منطقي *, وڻ);
ساكن فراغ c_parser_while_statement (c_parser *, منطقي, بنانشان ننڍو, منطقي,
				      منطقي *, وڻ);
ساكن فراغ c_parser_do_statement (c_parser *, منطقي, بنانشان ننڍو, منطقي,
				   وڻ);
ساكن فراغ c_parser_for_statement (c_parser *, منطقي, بنانشان ننڍو, منطقي,
				    منطقي *, وڻ);
ساكن وڻ c_parser_asm_statement (c_parser *);
ساكن وڻ c_parser_asm_operands (c_parser *);
ساكن وڻ c_parser_asm_goto_operands (c_parser *);
ساكن وڻ c_parser_asm_clobbers (c_parser *);
ساكن بنية c_اظهار c_parser_اظهار_no_commas (c_parser *, بنية c_اظهار *,
					      وڻ = NULL_وڻ);
ساكن بنية c_اظهار c_parser_conditional_اظهار (c_parser *,
						      بنية c_اظهار *, وڻ);
ساكن بنية c_اظهار c_parser_ٻٽو_اظهار (c_parser *, بنية c_اظهار *,
						 وڻ);
ساكن بنية c_اظهار c_parser_cast_اظهار (c_parser *, بنية c_اظهار *);
ساكن بنية c_اظهار c_parser_unary_اظهار (c_parser *);
ساكن بنية c_اظهار c_parser_sizeof_or_countof_اظهار (c_parser *,
							    تعداد rid);
ساكن بنية c_اظهار c_parser_alignof_اظهار (c_parser *);
ساكن بنية c_اظهار c_parser_maxof_or_minof_اظهار (c_parser *, تعداد rid);
ساكن بنية c_اظهار c_parser_postfix_اظهار (c_parser *);
ساكن بنية c_اظهار c_parser_postfix_اظهار_after_paren_type (c_parser *,
								   بنية c_declspecs *,
								   بنية c_type_name *,
								   location_t);
ساكن بنية c_اظهار c_parser_postfix_اظهار_after_primary (c_parser *,
								location_t loc,
								بنية c_اظهار);
ساكن وڻ c_parser_transaction (c_parser *, تعداد rid);
ساكن بنية c_اظهار c_parser_transaction_اظهار (c_parser *, تعداد rid);
ساكن وڻ c_parser_transaction_cancel (c_parser *);
ساكن بنية c_اظهار c_parser_اظهار (c_parser *);
ساكن بنية c_اظهار c_parser_اظهار_conv (c_parser *);
ساكن vec<وڻ, va_gc> *c_parser_اظهار_list (c_parser *, منطقي, منطقي,
					     vec<وڻ, va_gc> **, location_t *,
					     وڻ *, vec<location_t> *,
					     بنانشان صحيح * = عدم);
ساكن بنية c_اظهار c_parser_has_attribute_اظهار (c_parser *);

ساكن فراغ c_parser_oacc_declare (c_parser *);
ساكن فراغ c_parser_oacc_enter_exit_معلومات (c_parser *, منطقي);
ساكن فراغ c_parser_oacc_update (c_parser *);
ساكن فراغ c_parser_omp_construct (c_parser *, منطقي *);
ساكن فراغ c_parser_omp_groupprivate (c_parser *);
ساكن فراغ c_parser_omp_threadprivate (c_parser *);
ساكن فراغ c_parser_omp_barrier (c_parser *);
ساكن فراغ c_parser_omp_depobj (c_parser *);
ساكن فراغ c_parser_omp_flush (c_parser *);
ساكن منطقي c_parser_omp_ايندڙ_ٽوڪن_can_be_canon_loop (c_parser *,
							تعداد وڻ_ڪوڊ_2, منطقي);
ساكن وڻ c_parser_omp_loop_nest (c_parser *, منطقي *);
ساكن وڻ c_parser_omp_for_loop (location_t, c_parser *, تعداد وڻ_ڪوڊ_2,
				   وڻ, وڻ *, منطقي *);
ساكن فراغ c_parser_omp_taskwait (c_parser *);
ساكن فراغ c_parser_omp_taskyield (c_parser *);
ساكن فراغ c_parser_omp_cancel (c_parser *);
ساكن فراغ c_parser_omp_nothing (c_parser *);
ساكن فراغ c_parser_omp_metadirective (c_parser *, منطقي *);

تعداد pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
ساكن منطقي c_parser_pragma (c_parser *, تعداد pragma_context, منطقي *, وڻ);
ساكن منطقي c_parser_omp_cancellation_نقطو (c_parser *, تعداد pragma_context);
ساكن منطقي c_parser_omp_هدف (c_parser *, تعداد pragma_context, منطقي *);
ساكن فراغ c_parser_omp_begin (c_parser *);
ساكن فراغ c_parser_omp_پڇاڙي (c_parser *);
ساكن منطقي c_parser_omp_declare (c_parser *, تعداد pragma_context);
ساكن فراغ c_parser_omp_requires (c_parser *);
ساكن منطقي c_parser_omp_error (c_parser *, تعداد pragma_context);
ساكن فراغ c_parser_omp_assumption_clauses (c_parser *, منطقي);
ساكن فراغ c_parser_omp_allocate (c_parser *);
ساكن فراغ c_parser_omp_assumes (c_parser *);
ساكن منطقي c_parser_omp_ordered (c_parser *, تعداد pragma_context, منطقي *);
ساكن وڻ c_parser_omp_dispatch (location_t, c_parser *);
ساكن فراغ c_parser_omp_interop (c_parser *);
ساكن فراغ c_parser_oacc_routine (c_parser *, تعداد pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
ساكن فراغ c_parser_objc_class_definition (c_parser *, وڻ);
ساكن فراغ c_parser_objc_class_instance_variables (c_parser *);
ساكن فراغ c_parser_objc_class_declaration (c_parser *);
ساكن فراغ c_parser_objc_alias_declaration (c_parser *);
ساكن فراغ c_parser_objc_protocol_definition (c_parser *, وڻ);
ساكن منطقي c_parser_objc_طريقو_type (c_parser *);
ساكن فراغ c_parser_objc_طريقو_definition (c_parser *);
ساكن فراغ c_parser_objc_methodprotolist (c_parser *);
ساكن فراغ c_parser_objc_methodproto (c_parser *);
ساكن وڻ c_parser_objc_طريقو_decl (c_parser *, منطقي, وڻ *, وڻ *);
ساكن وڻ c_parser_objc_type_name (c_parser *);
ساكن وڻ c_parser_objc_protocol_refs (c_parser *);
ساكن فراغ c_parser_objc_try_catch_finally_statement (c_parser *);
ساكن فراغ c_parser_objc_synchronized_statement (c_parser *);
ساكن وڻ c_parser_objc_selector (c_parser *);
ساكن وڻ c_parser_objc_selector_arg (c_parser *);
ساكن وڻ c_parser_objc_receiver (c_parser *);
ساكن وڻ c_parser_objc_پيغام_دليلون (c_parser *);
ساكن وڻ c_parser_objc_keywordexpr (c_parser *);
ساكن فراغ c_parser_objc_at_property_declaration (c_parser *);
ساكن فراغ c_parser_objc_at_synthesize_declaration (c_parser *);
ساكن فراغ c_parser_objc_at_dynamic_declaration (c_parser *);
ساكن منطقي c_parser_objc_diagnose_bad_element_اڳياڙي
  (c_parser *, بنية c_declspecs *);
ساكن location_t c_parser_parse_rtl_body (c_parser *, حرف *);
ساكن وڻ c_parser_handle_musttail (c_parser *, وڻ, attr_state &);

#إذا ENABLE_ANALYZER

نطاق ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

صنف c_translation_unit : عام translation_unit
{
عام:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  وڻ lookup_constant_by_id (وڻ id) ثابت final override
  {
    /* Consider decls.  */
    إذا (وڻ decl = lookup_name (id))
      إذا (وڻ_ڪوڊ (decl) == CONST_DECL)
	إذا (وڻ قدر = DECL_INITIAL (decl))
	  إذا (وڻ_ڪوڊ (قدر) == INTEGER_CST)
	    أرجع قدر;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    إذا (cpp_macro_p (hashnode))
      إذا (وڻ قدر = consider_macro (hashnode->قدر.macro))
	أرجع قدر;

    أرجع NULL_وڻ;
  }

  وڻ
  lookup_type_by_id (وڻ id) ثابت final override
  {
    إذا (وڻ type_decl = lookup_name (id))
	إذا (وڻ_ڪوڊ (type_decl) == TYPE_DECL)
	  {
	    وڻ رڪارڊ_type = وڻ_TYPE (type_decl);
	    إذا (وڻ_ڪوڊ (رڪارڊ_type) == رڪارڊ_TYPE)
	      أرجع رڪارڊ_type;
	  }

    أرجع NULL_وڻ;
  }

  وڻ
  lookup_global_var_by_id (وڻ id) ثابت final override
  {
    إذا (وڻ var_decl = lookup_name (id))
      إذا (وڻ_ڪوڊ (var_decl) == VAR_DECL)
				أرجع var_decl;

    أرجع NULL_وڻ;
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
  وڻ consider_macro (cpp_macro *macro, صحيح اونهائي = 0) ثابت
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (اونهائي >= 0);

    إذا (macro->paramc > 0)
      أرجع NULL_وڻ;
    إذا (macro->قسم != cmk_macro)
      أرجع NULL_وڻ;
    إذا (macro->ڳڻپ != 1)
      أرجع NULL_وڻ;
    ثابت cpp_token &tok = macro->قوت_نما.ٽوڪن[0];
    إذا (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	إذا (اونهائي >= param_analyzer_max_macro_alias_اونهائي)
	  أرجع NULL_وڻ;

	cpp_hashnode *alias = tok.val.ڳنڍ.ڳنڍ;
	إذا (cpp_macro_p (alias))
	  أرجع consider_macro (alias->قدر.macro, اونهائي + 1);

	/* Not a simple alias.  */
	أرجع NULL_وڻ;
      }
    وإلا إذا (tok.type != CPP_عدد)
      أرجع NULL_وڻ;

    cpp_reader *old_parse_اندريون = parse_اندريون;
    parse_اندريون = cpp_create_reader (CLK_GNUC89, عدم, سٽ_جدول);

    pretty_printer pp;
    pp_string (&pp, (ثابت حرف *) tok.val.str.متن);
    pp_newline (&pp);
    cpp_ڌڪو_بفر (parse_اندريون,
		     (ثابت بنانشان حرف *) pp_formatted_متن (&pp),
		     لڙي_ڊيگهه (pp_formatted_متن (&pp)),
		     0);

    وڻ قدر;
    location_t loc;
    بنانشان حرف cpp_flags;
    c_lex_with_flags (&قدر, &loc, &cpp_flags, 0);

    cpp_destroy (parse_اندريون);
    parse_اندريون = old_parse_اندريون;

    إذا (قدر && وڻ_ڪوڊ (قدر) == INTEGER_CST)
      أرجع قدر;

    أرجع NULL_وڻ;
  }
};

} // namespace ana

#جيڪڏهن_پورو /* #if ENABLE_ANALYZER */

/* Parse a translation unit (C90 6.7, C99 6.9, C11 6.9).

   translation-unit:
     external-declarations

   external-declarations:
     external-declaration
     external-declarations external-declaration

   GNU extensions:

   translation-unit:
خالي_جايون
*/

ساكن فراغ
c_parser_translation_unit (c_parser *parser)
{
  إذا (c_parser_ايندڙ_token_is (parser, CPP_EOF))
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
      طالما (c_parser_ايندڙ_token_is_not (parser, CPP_EOF));
    }

  بنانشان صحيح i;
  وڻ decl;
  FOR_EACH_VEC_ELT (incomplete_رڪارڊ_decls, i, decl)
    إذا (DECL_سائيز (decl) == NULL_وڻ && وڻ_TYPE (decl) != error_mark_ڳنڍ)
      error ("storage size of %q+D isn%'t known", decl);

  إذا (vec_محفوظ_ڊيگهائي (current_omp_declare_هدف_attribute))
    {
      c_omp_declare_هدف_attr
	a = current_omp_declare_هدف_attribute->ڪڍو ();
      إذا (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_محفوظ_truncate (current_omp_declare_هدف_attribute, 0);
    }
  إذا (vec_محفوظ_ڊيگهائي (current_omp_begin_assumes))
    {
      إذا (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_محفوظ_truncate (current_omp_begin_assumes, 0);
    }
  إذا (vec_محفوظ_ڊيگهائي (current_omp_declare_variant_attribute))
    {
      إذا (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_محفوظ_truncate (current_omp_declare_variant_attribute, 0);
    }
  إذا (vec_محفوظ_ڊيگهائي (omp_begin_declare_variant_map))
    {
      بنانشان صحيح i;
      omp_begin_declare_variant_map_داخلا *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_پڄاڻي_variant_function (e->variant, e->id, e->ctx);
      vec_محفوظ_truncate (omp_begin_declare_variant_map, 0);
    }

#إذا ENABLE_ANALYZER
  إذا (flag_analyzer)
    {
      ana::c_translation_unit tu;
      ana::on_پڄاڻي_translation_unit (tu);
    }
#جيڪڏهن_پورو
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
	  c_parser_objc_class_definition (parser, NULL_وڻ);
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
	  c_parser_objc_protocol_definition (parser, NULL_وڻ);
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
	حالة RID_AT_پڇاڙي:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_پڄاڻي_implementation ();
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
      mark_valid_location_for_stdc_pragma (سچ);
      c_parser_pragma (parser, pragma_external, عدم, NULL_وڻ);
      mark_valid_location_for_stdc_pragma (خطأ);
      اكسر;
    حالة CPP_PLUS:
    حالة CPP_MINUS:
      إذا (c_dialect_objc ())
	{
	  c_parser_objc_طريقو_definition (parser);
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
      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, خطأ, سچ,
				     خطأ);
      اكسر;
    }
}

ساكن فراغ c_parser_handle_directive_omp_خاصيتون (وڻ &, vec<c_token> *&,
						      vec<c_token> *);
ساكن فراغ c_پڄاڻي_omp_declare_simd (c_parser *, وڻ, وڻ, vec<c_token> *);
ساكن فراغ c_پڄاڻي_oacc_routine (بنية oacc_routine_معلومات *, وڻ, منطقي);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

ساكن فراغ
جوڙيو_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  إذا (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    أرجع;

  وڻ stmt = build0 (DEBUG_BEGIN_STMT, void_type_ڳنڍ);
  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

ساكن وڻ
handle_assume_attribute (location_t هتي, وڻ attrs, منطقي nested)
{
  إذا (nested)
    لكل (وڻ attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", وڻ_CHAIN (attr)))
      {
	وڻ دليلون = وڻ_قدر (attr);
	صحيح nargs = list_ڊيگهائي (دليلون);
	إذا (nargs != 1)
	  {
	    error_at (هتي, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (هتي, "expected %i, found %i", 1, nargs);
	  }
	وإلا
	  {
	    وڻ arg = وڻ_قدر (دليلون);
	    arg = c_objc_common_truthvalue_conversion (هتي, arg);
	    arg = c_fully_fold (arg, خطأ, عدم);
	    إذا (arg != error_mark_ڳنڍ)
	      {
		وڻ fn = build_call_اظهار_اندروني_loc (هتي, IFN_ASSUME,
							void_type_ڳنڍ, 1,
							arg);
		جوڙيو_stmt (fn);
	      }
	  }
      }
  وإلا
    pedwarn (هتي, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  أرجع remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

ساكن فراغ
c_parser_maybe_reclassify_token (c_parser *parser)
{
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      إذا (token->id_قسم == C_ID_ID || token->id_قسم == C_ID_TYPENAME)
	{
	  وڻ decl = lookup_name (token->قدر);

	  token->id_قسم = C_ID_ID;
	  إذا (decl)
	    {
	      إذا (وڻ_ڪوڊ (decl) == TYPE_DECL)
		token->id_قسم = C_ID_TYPENAME;
	    }
	  وإلا إذا (c_dialect_objc ())
	    {
	      وڻ objc_interface_decl = objc_is_class_name (token->قدر);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      إذا (objc_interface_decl)
		{
		  token->قدر = objc_interface_decl;
		  token->id_قسم = C_ID_CLASSNAME;
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

ساكن وڻ
c_parser_declaration_or_fndef (c_parser *parser, منطقي fndef_ok,
			       منطقي static_assert_ok, منطقي خالي_جايون_ok,
			       منطقي nested, منطقي شروعات_attr_ok,
			       منطقي simple_ok,
			       وڻ *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       منطقي have_attrs /* = false */,
			       وڻ attrs /* = NULL_TREE */,
			       بنية oacc_routine_معلومات *oacc_routine_معلومات
			       /* = NULL */,
			       منطقي *fallthru_attr_p /* = NULL */)
{
  بنية c_declspecs *specs;
  وڻ اڳياڙي_attrs;
  وڻ all_اڳياڙي_attrs;
  منطقي diagnosed_no_specs = خطأ;
  location_t هتي = c_parser_peek_token (parser)->location;
  وڻ نتيجو = NULL_وڻ;

  جوڙيو_debug_begin_stmt (c_parser_peek_token (parser)->location);

  إذا (static_assert_ok
      && c_parser_ايندڙ_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      أرجع نتيجو;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  إذا (have_attrs)
    {
      declspecs_جوڙيو_attrs (هتي, specs, attrs);
      specs->non_std_attrs_ڏٺل_p = خطأ;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  إذا (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_قسم == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->قدر)))
    {
      وڻ name = c_parser_peek_token (parser)->قدر;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (هتي);
      إذا (ٽيگ_exists_p (رڪارڊ_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.جوڙيو_fixit_وجهو_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      وإلا إذا (ٽيگ_exists_p (UNION_TYPE, name))
	{
	  richloc.جوڙيو_fixit_وجهو_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      وإلا إذا (ٽيگ_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.جوڙيو_fixit_وجهو_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      وإلا
	{
	  auto_diagnostic_گروهه d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      هتي);
	  إذا (ثابت حرف *suggestion = hint.suggestion ())
	    {
	      richloc.جوڙيو_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  وإلا
	    error_at (هتي, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->قدر = error_mark_ڳنڍ;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  إذا (c_parser_nth_token_starts_std_خاصيتون (parser, 1))
    have_attrs = سچ;

  c_parser_declspecs (parser, specs, سچ, سچ, شروعات_attr_ok,
		      سچ, سچ, شروعات_attr_ok, سچ, cla_nonabstract_decl);
  إذا (parser->error)
    {
      c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
      أرجع نتيجو;
    }
  إذا (nested && !specs->declspecs_ڏٺل_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
      أرجع نتيجو;
    }

  پڄاڻي_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  إذا (specs->typespec_قسم == ctsk_tagdef)
    verify_counted_by_for_چوٽي_anonymous_type (specs->type);

  منطقي gnu_auto_type_p = specs->typespec_لفظ == cts_auto_type;
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
      بدل (specs->typespec_قسم)
	{
	حالة ctsk_tagfirstref:
	حالة ctsk_tagfirstref_attrs:
	  error_at (هتي, "%qT declared in underspecified object declaration",
		    specs->type);
	  اكسر;

	حالة ctsk_tagdef:
	  error_at (هتي, "%qT defined in underspecified object declaration",
		    specs->type);
	  اكسر;

	افتراضي:
	  اكسر;
	}
    }

  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      منطقي handled_assume = خطأ;
      إذا (specs->attrs
	  && !nested
	  && specs->typespec_قسم == ctsk_none
	  && c_parser_handle_statement_omp_خاصيتون (parser, specs->attrs,
						       عدم))
	{
	  إذا (specs->attrs)
	    c_warn_اڻ_استعمال_ٿيل_خاصيتون (specs->attrs);
	  طالما (parser->اندريون_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, عدم, NULL_وڻ);
	    }
	  c_parser_consume_token (parser);
	  أرجع نتيجو;
	}
      إذا (specs->typespec_قسم == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = سچ;
	  specs->attrs
	    = handle_assume_attribute (هتي, specs->attrs, nested);
	}
      إذا (any_auto_type_p)
	error_at (هتي, "%qs in empty declaration", auto_type_keyword);
      وإلا إذا (specs->typespec_قسم == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  إذا (fallthru_attr_p != عدم)
	    *fallthru_attr_p = سچ;
	  إذا (nested)
	    {
	      وڻ fn = build_call_اظهار_اندروني_loc (هتي, IFN_FALLTHROUGH,
						      void_type_ڳنڍ, 0);
	      جوڙيو_stmt (fn);
	    }
	  وإلا
	    pedwarn (هتي, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      وإلا إذا (خالي_جايون_ok
	       && !(have_attrs && specs->non_std_attrs_ڏٺل_p)
	       && !handled_assume)
	shadow_ٽيگ (specs);
      وإلا
	{
	  shadow_ٽيگ_warned (specs, 1);
	  إذا (!handled_assume)
	    pedwarn (هتي, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      إذا (specs->اظهار)
	جوڙيو_stmt (fold_convert (void_type_ڳنڍ, specs->اظهار));
      c_parser_consume_token (parser);
      إذا (oacc_routine_معلومات)
	c_پڄاڻي_oacc_routine (oacc_routine_معلومات, NULL_وڻ, خطأ);
      أرجع نتيجو;
    }
  وإلا إذا (specs->typespec_قسم == ctsk_none
	   && nested
	   /* Only parse __attribute__((musttail)) when called from
	      c_parser_compound_statement_nostart.  This certainly isn't
	      a declaration in that case, but we don't do tentative parsing
	      of GNU attributes right now.  */
	   && fallthru_attr_p
	   && c_parser_ايندڙ_token_is_keyword (parser, RID_RETURN))
    {
      attr_state astate = {};
      specs->attrs = c_parser_handle_musttail (parser, specs->attrs, astate);
      إذا (astate.musttail_p)
	{
	  إذا (specs->attrs)
	    {
	      auto_urlify_خاصيتون sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, عدم, NULL_وڻ, عدم,
					   astate);
	  أرجع نتيجو;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  إذا (خالي_جايون_ok
      && specs->typespec_قسم == ctsk_tagdef
      && c_parser_ايندڙ_token_starts_declspecs (parser)
      && !c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = خطأ;
      shadow_ٽيگ_warned (specs, 1);
      أرجع نتيجو;
    }
  وإلا إذا (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      بدل (c_parser_peek_token (parser)->type)
	{
	  حالة CPP_PLUS:
	  حالة CPP_MINUS:
	    إذا (c_parser_objc_diagnose_bad_element_اڳياڙي (parser, specs))
	      أرجع نتيجو;
	    إذا (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_وڻ;
	      }
	    إذا (fndef_ok)
	      c_parser_objc_طريقو_definition (parser);
	    وإلا
	      c_parser_objc_methodproto (parser);
	    أرجع نتيجو;
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
	    إذا (c_parser_objc_diagnose_bad_element_اڳياڙي (parser, specs))
	      أرجع نتيجو;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    أرجع نتيجو;
	  }
	  اكسر;
	حالة RID_AT_IMPLEMENTATION:
	  {
	    إذا (c_parser_objc_diagnose_bad_element_اڳياڙي (parser, specs))
	      أرجع نتيجو;
	    إذا (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_وڻ;
	      }
	    c_parser_objc_class_definition (parser, NULL_وڻ);
	    أرجع نتيجو;
	  }
	  اكسر;
	حالة RID_AT_PROTOCOL:
	  {
	    إذا (c_parser_objc_diagnose_bad_element_اڳياڙي (parser, specs))
	      أرجع نتيجو;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    أرجع نتيجو;
	  }
	  اكسر;
	حالة RID_AT_ALIAS:
	حالة RID_AT_CLASS:
	حالة RID_AT_پڇاڙي:
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
    warning_at (هتي, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  وإلا إذا (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (هتي, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_خاصيتون (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  اڳياڙي_attrs = specs->attrs;
  all_اڳياڙي_attrs = اڳياڙي_attrs;
  specs->attrs = NULL_وڻ;
  منطقي وڌيڪ_than_one_decl = خطأ;
  طالما (سچ)
    {
      بنية c_declarator *declarator;
      منطقي dummy = خطأ;
      timevar_id_t tv;
      وڻ fnbody = NULL_وڻ;
      وڻ underspec_name = NULL_وڻ;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_قسم != ctsk_none,
					C_DTR_عام, &dummy);
      إذا (declarator == عدم)
	{
	  إذا (omp_declare_simd_clauses)
	    c_پڄاڻي_omp_declare_simd (parser, NULL_وڻ, NULL_وڻ,
				       omp_declare_simd_clauses);
	  إذا (oacc_routine_معلومات)
	    c_پڄاڻي_oacc_routine (oacc_routine_معلومات, NULL_وڻ, خطأ);
	  /* This check is here purely to improve the diagnostic.  */
	  إذا (!simple_ok)
	    c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
	  أرجع نتيجو;
	}
      إذا (flag_openmp || flag_openmp_simd)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->قسم != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = عدم;
	  c_parser_handle_directive_omp_خاصيتون (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      إذا (gnu_auto_type_p && declarator->قسم != cdk_id)
	{
	  error_at (هتي,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
	  أرجع نتيجو;
	}
      إذا (std_auto_type_p)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->قسم == cdk_attrs)
	    d = d->declarator;
	  إذا (d->قسم != cdk_id)
	    {
	      error_at (هتي,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
	      أرجع نتيجو;
	    }
	  underspec_name = d->u.id.id;
	}
      وإلا إذا (specs->constexpr_p)
	{
	  بنية c_declarator *d = declarator;
	  طالما (d->قسم != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_EQ)
	  || c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  || c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)
	  || c_parser_ايندڙ_token_is_keyword (parser, RID_ASM)
	  || c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_ايندڙ_token_is_keyword (parser, RID_اندريون))
	{
	  وڻ asm_name = NULL_وڻ;
	  وڻ postfix_attrs = NULL_وڻ;
	  إذا (!diagnosed_no_specs && !specs->declspecs_ڏٺل_p)
	    {
	      diagnosed_no_specs = سچ;
	      pedwarn (هتي, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = خطأ;
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_اظهار (parser);
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_خاصيتون (parser);
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (هتي, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
		  أرجع نتيجو;
		}
	    }
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_EQ))
	    {
	      وڻ d;
	      بنية c_اظهار init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      إذا (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سٽ_جدول, init_loc);
		  بنانشان صحيح underspec_state = 0;
		  إذا (std_auto_type_p)
		    underspec_state =
		      شروعات_underspecified_init (init_loc, underspec_name);
		  شروعات_init (NULL_وڻ, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_ڪوڊ_type flag_sanitize_save = flag_sanitize;
		  إذا (nested && !خالي_جايون_ok)
		    flag_sanitize = 0;
		  init = c_parser_اظهار_no_commas (parser, عدم);
		  إذا (std_auto_type_p)
		    پڄاڻي_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  إذا (gnu_auto_type_p
		      && وڻ_ڪوڊ (init.قدر) == COMPONENT_REF
		      && DECL_C_ٻٽو_انگ_ميدان (وڻ_عمليو (init.قدر, 1)))
		    error_at (هتي,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_منزل_rvalue (init_loc, init, سچ, سچ,
						   سچ);
		  وڻ init_type = وڻ_TYPE (init.قدر);
		  منطقي vm_type = c_type_variably_modified_p (init_type);
		  إذا (vm_type)
		    init.قدر = save_اظهار (init.قدر);
		  پڄاڻي_init ();
		  specs->typespec_قسم = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = سچ;
		  specs->type = init_type;
		  إذا (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_خاصيتون (specs->type,
						  specs->postfix_attrs);
		      decl_خاصيتون (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_وڻ;
		    }
		  إذا (vm_type)
		    {
		      منطقي maybe_const = سچ;
		      وڻ type_اظهار = c_fully_fold (init.قدر, خطأ,
						     &maybe_const);
		      specs->اظهار_const_operands &= maybe_const;
		      إذا (specs->اظهار)
			specs->اظهار = build2 (COMPOUND_اظهار,
					      وڻ_TYPE (type_اظهار),
					      specs->اظهار, type_اظهار);
		      وإلا
			specs->اظهار = type_اظهار;
		    }
		  d = شروعات_decl (declarator, specs, سچ,
				  chainon (postfix_attrs, all_اڳياڙي_attrs));
		  إذا (!d)
		    d = error_mark_ڳنڍ;
		  إذا (omp_declare_simd_clauses)
		    c_پڄاڻي_omp_declare_simd (parser, d, NULL_وڻ,
					       omp_declare_simd_clauses);
		  إذا (!omp_dsimd_idattr_clauses.is_خالي_جايون ())
		    c_پڄاڻي_omp_declare_simd (parser, d, NULL_وڻ,
					       &omp_dsimd_idattr_clauses);
		}
	      وإلا
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سٽ_جدول, init_loc);
		  بنانشان صحيح underspec_state = 0;
		  إذا (specs->constexpr_p)
		    underspec_state =
		      شروعات_underspecified_init (init_loc, underspec_name);
		  d = شروعات_decl (declarator, specs, سچ,
				  chainon (postfix_attrs,
					   all_اڳياڙي_attrs),
				  !specs->constexpr_p);
		  إذا (!d)
		    d = error_mark_ڳنڍ;
		  إذا (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_پڄاڻي_omp_declare_simd (parser, d, NULL_وڻ,
					       omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالي_جايون ())
		    c_پڄاڻي_omp_declare_simd (parser, d, NULL_وڻ,
					       &omp_dsimd_idattr_clauses);
		  شروعات_init (d, asm_name,
			      وڻ_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_ڪوڊ_type flag_sanitize_save = flag_sanitize;
		  إذا (وڻ_ڪوڊ (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  إذا (specs->constexpr_p)
		    {
		      پڄاڻي_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      إذا (omp_declare_simd_clauses)
			c_پڄاڻي_omp_declare_simd (parser, d, NULL_وڻ,
						   omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالي_جايون ())
		    c_پڄاڻي_omp_declare_simd (parser, d, NULL_وڻ,
					       &omp_dsimd_idattr_clauses);
		    }
		  پڄاڻي_init ();
		}
	      إذا (oacc_routine_معلومات)
		c_پڄاڻي_oacc_routine (oacc_routine_معلومات, d, خطأ);
	      إذا (d != error_mark_ڳنڍ)
		{
		  maybe_warn_string_init (init_loc, وڻ_TYPE (d), init);
		  پڄاڻي_decl (d, init_loc, init.قدر,
			       init.original_type, asm_name);
		  نتيجو = d;
		}
	    }
	  وإلا
	    {
	      إذا (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (هتي,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
		  أرجع نتيجو;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      وڻ attrs = chainon (postfix_attrs, all_اڳياڙي_attrs);
	      وڻ d = شروعات_decl (declarator, specs, خطأ, attrs, سچ,
				   &lastloc);
	      إذا (d && وڻ_ڪوڊ (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ثابت بنية c_declarator *decl = declarator;
		  ثابت بنية c_declarator *آخري_non_id_attrs = عدم;

		  طالما (decl)
		    بدل (decl->قسم)
		      {
		      حالة cdk_array:
		      حالة cdk_function:
		      حالة cdk_اشارو:
			آخري_non_id_attrs = decl;
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
		  إذا (آخري_non_id_attrs
		      && آخري_non_id_attrs->قسم == cdk_function)
		    {
		      وڻ parms = آخري_non_id_attrs->u.arg_info->parms;
		      إذا (DECL_ARGUMENTS (d) == NULL_وڻ
			  && DECL_INITIAL (d) == NULL_وڻ)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      إذا (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_خالي_جايون ())
		{
		  وڻ parms = NULL_وڻ;
		  إذا (d && وڻ_ڪوڊ (d) == FUNCTION_DECL)
		    {
		      بنية c_declarator *ce = declarator;
		      طالما (ce != عدم)
			إذا (ce->قسم == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    اكسر;
			  }
			وإلا
			  ce = ce->declarator;
		    }
		  إذا (parms)
		    عارضي_store_parm_decls (d, parms);
		  إذا (omp_declare_simd_clauses)
		    c_پڄاڻي_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  إذا (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_خالي_جايون ())
		    c_پڄاڻي_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  إذا (parms)
		    عارضي_ڪڍو_parm_decls ();
		}
	      إذا (oacc_routine_معلومات)
		c_پڄاڻي_oacc_routine (oacc_routine_معلومات, d, خطأ);
	      إذا (d)
		پڄاڻي_decl (d, UNKNOWN_LOCATION, NULL_وڻ,
			     NULL_وڻ, asm_name);

	      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_اندريون))
		{
		  إذا (d)
		    *objc_foreach_object_declaration = d;
		  وإلا
		    *objc_foreach_object_declaration = error_mark_ڳنڍ;
		}
	    }
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    {
	      وڌيڪ_than_one_decl = سچ;
	      إذا (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (هتي,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
		  أرجع نتيجو;
		}
	      c_parser_consume_token (parser);
	      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
		all_اڳياڙي_attrs = chainon (c_parser_gnu_خاصيتون (parser),
					    اڳياڙي_attrs);
	      وإلا
		all_اڳياڙي_attrs = اڳياڙي_attrs;
	      استمر;
	    }
	  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	    {
	      إذا (!simple_ok)
		c_parser_consume_token (parser);
	      أرجع نتيجو;
	    }
	  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_اندريون))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      أرجع نتيجو;
	    }
	  وإلا
	    {
	      إذا (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      وإلا إذا (وڌيڪ_than_one_decl)
		error_at (هتي, "declaration in condition can only declare "
			  "a single object");
	      أرجع نتيجو;
	    }
	}
      وإلا إذا (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (هتي,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
	  أرجع نتيجو;
	}
      وإلا إذا (!fndef_ok)
	{
	  إذا (simple_ok && c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  وإلا
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
	    }
	  أرجع نتيجو;
	}
      /* Function definition (nested or otherwise).  */
      إذا (nested)
	{
	  pedwarn (هتي, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_ڌڪو_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      وڻ dv_بنياد = NULL_وڻ;
      وڻ dv_ctx = NULL_وڻ;
      إذا (!vec_محفوظ_is_خالي_جايون (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->آخري ();
	  dv_ctx = copy_list (a.selector);
	  dv_بنياد = omp_شروعات_variant_function (declarator, dv_ctx);
	}

      إذا (!شروعات_function (specs, declarator, all_اڳياڙي_attrs))
	{
	  /* At this point we've consumed:
	       declaration-specifiers declarator
	     and the next token isn't CPP_EQ, CPP_COMMA, CPP_SEMICOLON,
	     RID_ASM, RID_ATTRIBUTE, or RID_IN,
	     but the
	       declaration-specifiers declarator
	     aren't grokkable as a function definition, so we have
	     an error.  */
	  gcc_assert (!c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON));
	  إذا (c_parser_ايندڙ_token_starts_declspecs (parser))
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
	    c_ڪڍو_function_context ();
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
      طالما (c_parser_ايندڙ_token_is_not (parser, CPP_EOF)
	     && c_parser_ايندڙ_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, خطأ, خطأ, خطأ,
				       سچ, خطأ, خطأ);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      إذا (omp_declare_simd_clauses)
	c_پڄاڻي_omp_declare_simd (parser, current_function_decl, NULL_وڻ,
				   omp_declare_simd_clauses);
      إذا (!omp_dsimd_idattr_clauses.is_خالي_جايون ())
	c_پڄاڻي_omp_declare_simd (parser, current_function_decl, NULL_وڻ,
				   &omp_dsimd_idattr_clauses);
      إذا (oacc_routine_معلومات)
	c_پڄاڻي_oacc_routine (oacc_routine_معلومات, current_function_decl, سچ);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_شروعات_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      إذا (dv_بنياد && current_function_decl != error_mark_ڳنڍ)
	{
	  omp_begin_declare_variant_map_داخلا e
	    = { current_function_decl, dv_بنياد, dv_ctx };
	  vec_محفوظ_ڌڪو (omp_begin_declare_variant_map, e);
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
	  ڌڪو_scope ();
	  ڪڍو_scope ();

	  پڄاڻي_function (endloc);
	  أرجع نتيجو;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      وإلا إذا (specs->declspec_il != cdil_none)
	{
	  منطقي saved = اندريون_late_ٻٽو_op;
	  اندريون_late_ٻٽو_op = سچ;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->داخلا_bb_ڳڻپ);
	  اندريون_late_ٻٽو_op = saved;
	}
      وإلا
	fnbody = c_parser_compound_statement (parser, &endloc);
      وڻ fndecl = current_function_decl;
      إذا (nested && specs->declspec_il == cdil_none)
	{
	  وڻ decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  جوڙيو_stmt (fnbody);
	  پڄاڻي_function (endloc);
	  c_ڪڍو_function_context ();
	  جوڙيو_stmt (build_stmt (DECL_ذريعو_LOCATION (decl), DECL_اظهار, decl));
	}
      وإلا إذا (nested)
	{
	  إذا (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  وإلا
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  پڄاڻي_function (endloc);
	  c_ڪڍو_function_context ();
	}
      وإلا
	{
	  إذا (fnbody)
	    جوڙيو_stmt (fnbody);
	  پڄاڻي_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      إذا (specs->declspec_il != cdil_none)
	DECL_SAVED_وڻ (fndecl) = NULL_وڻ;

      اكسر;
    }

  أرجع نتيجو;
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
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  وڻ asm_str = NULL_وڻ;
  وڻ outputs = NULL_وڻ, inputs = NULL_وڻ;
  إذا (!parens.require_open (parser))
    اذهب پورو;
  asm_str = c_parser_asm_string_literal (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      اذهب پورو;
    }
  لكل (صحيح section = 0; section < 2; ++section)
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  إذا (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	      asm_str = NULL_وڻ;
	      اذهب پورو;
	    }
	  c_parser_consume_token (parser);
	}
      وإلا إذا (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, خطأ))
	اذهب error_close_paren;
      إذا (!c_parser_ايندڙ_token_is (parser, CPP_COLON)
	  && !c_parser_ايندڙ_token_is (parser, CPP_SCOPE)
	  && !c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (section)
	    inputs = c_parser_asm_operands (parser);
	  وإلا
	    outputs = c_parser_asm_operands (parser);
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;
    }

  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
      asm_str = NULL_وڻ;
    }

  إذا (asm_str)
    asm_str = build_asm_اظهار (asm_loc, asm_str, outputs, inputs,
			      NULL_وڻ, NULL_وڻ, خطأ, خطأ);
پورو:
  إذا (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
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
    c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
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
  location_t assert_loc, قدر_loc;
  وڻ قدر;
  وڻ string = NULL_وڻ;

  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_STATIC_ASSERT));
  وڻ spelling = c_parser_peek_token (parser)->قدر;
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
  location_t قدر_tok_loc = c_parser_peek_token (parser)->location;
  قدر = convert_lvalue_منزل_rvalue (قدر_tok_loc,
				    c_parser_اظهار_no_commas (parser, عدم),
				    سچ, سچ).قدر;
  قدر_loc = اظهار_LOC_OR_LOC (قدر, قدر_tok_loc);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_STRING:
	حالة CPP_STRING16:
	حالة CPP_STRING32:
	حالة CPP_WSTRING:
	حالة CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, خطأ, سچ).قدر;
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

  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (قدر)))
    {
      error_at (قدر_loc, "expression in static assertion is not an integer");
      أرجع;
    }
  إذا (وڻ_ڪوڊ (قدر) != INTEGER_CST)
    {
      قدر = c_fully_fold (قدر, خطأ, عدم);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (قدر);
      إذا (وڻ_ڪوڊ (قدر) == INTEGER_CST)
	pedwarn (قدر_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  إذا (وڻ_ڪوڊ (قدر) != INTEGER_CST)
    {
      error_at (قدر_loc, "expression in static assertion is not constant");
      أرجع;
    }
  constant_اظهار_warning (قدر);
  إذا (integer_zerop (قدر))
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
رجسٽر
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
		    منطقي scspec_ok, منطقي typespec_ok, منطقي شروعات_attr_ok,
		    منطقي alignspec_ok, منطقي auto_type_ok,
		    منطقي شروعات_std_attr_ok, منطقي پڇاڙي_std_attr_ok,
		    تعداد c_lookahead_قسم la)
{
  منطقي attrs_ok = شروعات_attr_ok;
  منطقي ڏٺل_type = specs->typespec_قسم != ctsk_none;

  إذا (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  إذا (شروعات_std_attr_ok
      && c_parser_nth_token_starts_std_خاصيتون (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_ڏٺل_p);
      location_t loc = c_parser_peek_token (parser)->location;
      وڻ attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_جوڙيو_attrs (loc, specs, attrs);
      specs->non_std_attrs_ڏٺل_p = خطأ;
    }

  طالما (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	 || c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_ايندڙ_token_is (parser, CPP_LESS)))
    {
      بنية c_typespec t;
      وڻ attrs;
      وڻ align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      إذا ((!typespec_ok || specs->typespec_قسم == ctsk_tagdef)
	  && c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, la)
	  && !c_parser_ايندڙ_token_is_qualifier (parser)
	  && !c_parser_ايندڙ_token_is_keyword (parser, RID_ALIGNAS))
	اكسر;

      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  وڻ قدر = name_token->قدر;
	  c_id_قسم قسم = name_token->id_قسم;

	  إذا (قسم == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_پهريون_ADDR_SPACE;
	      declspecs_جوڙيو_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = سچ;
	      استمر;
	    }

	  gcc_assert (!c_parser_ايندڙ_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  إذا (ڏٺل_type || !c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, la))
	    اكسر;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  ڏٺل_type = سچ;
	  attrs_ok = سچ;
	  إذا (قسم == C_ID_ID)
	    {
	      auto_diagnostic_گروهه d;
	      name_hint hint = lookup_name_fuzzy (قدر, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      إذا (ثابت حرف *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.جوڙيو_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    قدر, suggestion);
		}
	      وإلا
		error_at (loc, "unknown type name %qE", قدر);
	      t.قسم = ctsk_typedef;
	      t.spec = error_mark_ڳنڍ;
	    }
	  وإلا إذا (قسم == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_ايندڙ_token_is_not (parser, CPP_LESS)))
	    {
	      t.قسم = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (قدر);
	    }
	  وإلا
	    {
	      وڻ proto = NULL_وڻ;
	      gcc_assert (c_dialect_objc ());
	      t.قسم = ctsk_objc;
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (قدر, proto);
	    }
	  t.اظهار = NULL_وڻ;
	  t.اظهار_const_operands = سچ;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_جوڙيو_type (name_token->location, specs, t);
	  استمر;
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  وڻ proto;
	  gcc_assert (c_dialect_objc ());
	  إذا (!typespec_ok || ڏٺل_type)
	    اكسر;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.قسم = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_وڻ, proto);
	  t.اظهار = NULL_وڻ;
	  t.اظهار_const_operands = سچ;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_جوڙيو_type (loc, specs, t);
	  استمر;
	}
      gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD));
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_STATIC:
	حالة RID_EXTERN:
	حالة RID_رجسٽر:
	حالة RID_TYPEDEF:
	حالة RID_INLINE:
	حالة RID_NORETURN:
	حالة RID_AUTO:
	حالة RID_THREAD:
	حالة RID_CONSTEXPR:
	  إذا (!scspec_ok)
	    اذهب ٻاهريون;
	  attrs_ok = سچ;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_جوڙيو_scspec (loc, specs,
				c_parser_peek_token (parser)->قدر);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_AUTO_TYPE:
	  إذا (!auto_type_ok)
	    اذهب ٻاهريون;
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
	    اذهب ٻاهريون;
	  attrs_ok = سچ;
	  ڏٺل_type = سچ;
	  إذا (c_dialect_objc ())
	    parser->objc_need_raw_identifier = سچ;
	  t.قسم = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->قدر;
	  t.اظهار = NULL_وڻ;
	  t.اظهار_const_operands = سچ;
	  t.has_enum_type_specifier = خطأ;
	  declspecs_جوڙيو_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_ENUM:
	  إذا (!typespec_ok)
	    اذهب ٻاهريون;
	  attrs_ok = سچ;
	  ڏٺل_type = سچ;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_پڄاڻي_TYPE, t.spec);
	  declspecs_جوڙيو_type (loc, specs, t);
	  اكسر;
	حالة RID_STRUCT:
	حالة RID_UNION:
	  إذا (!typespec_ok)
	    اذهب ٻاهريون;
	  attrs_ok = سچ;
	  ڏٺل_type = سچ;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_پڄاڻي_TYPE, t.spec);
	  declspecs_جوڙيو_type (loc, specs, t);
	  اكسر;
	حالة RID_TYPEOF:
	حالة RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  إذا (!typespec_ok || ڏٺل_type)
	    اذهب ٻاهريون;
	  attrs_ok = سچ;
	  ڏٺل_type = سچ;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_جوڙيو_type (loc, specs, t);
	  اكسر;
	حالة RID_BITINT:
	  إذا (!typespec_ok)
	    اذهب ٻاهريون;
	  وإلا
	    {
	      attrs_ok = سچ;
	      ڏٺل_type = سچ;
	      t.قسم = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->قدر;
	      t.اظهار = error_mark_ڳنڍ;
	      t.اظهار_const_operands = سچ;
	      t.has_enum_type_specifier = خطأ;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      إذا (parens.require_open (parser))
		{
		  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
		  t.اظهار = convert_lvalue_منزل_rvalue (loc, اظهار, سچ,
						     سچ).قدر;
		  parens.skip_until_مليو_close (parser);
		}
	      declspecs_جوڙيو_type (loc, specs, t);
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
	  attrs_ok = سچ;
	  وڻ قدر;
	  قدر = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	  إذا (typespec_ok && c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      ڏٺل_type = سچ;
	      c_parser_consume_token (parser);
	      بنية c_type_name *type = c_parser_type_name (parser);
	      t.قسم = ctsk_typeof;
	      t.spec = error_mark_ڳنڍ;
	      t.اظهار = NULL_وڻ;
	      t.اظهار_const_operands = سچ;
	      t.has_enum_type_specifier = خطأ;
	      إذا (type != عدم)
		t.spec = groktypename (type, &t.اظهار,
				       &t.اظهار_const_operands);
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      إذا (t.spec != error_mark_ڳنڍ)
		{
		  إذا (وڻ_ڪوڊ (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  وإلا إذا (وڻ_ڪوڊ (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  وإلا إذا (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  وإلا
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_جوڙيو_type (loc, specs, t);
	    }
	  وإلا
	    declspecs_جوڙيو_qual (loc, specs, قدر);
	  اكسر;
	حالة RID_CONST:
	حالة RID_VOLATILE:
	حالة RID_RESTRICT:
	  attrs_ok = سچ;
	  declspecs_جوڙيو_qual (loc, specs, c_parser_peek_token (parser)->قدر);
	  c_parser_consume_token (parser);
	  اكسر;
	حالة RID_ATTRIBUTE:
	  إذا (!attrs_ok)
	    اذهب ٻاهريون;
	  attrs = c_parser_gnu_خاصيتون (parser);
	  declspecs_جوڙيو_attrs (loc, specs, attrs);
	  اكسر;
	حالة RID_ALIGNAS:
	  إذا (!alignspec_ok)
	    اذهب ٻاهريون;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_جوڙيو_alignas (loc, specs, align);
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
	  اذهب ٻاهريون;
	}
    }
 ٻاهريون:
  إذا (پڇاڙي_std_attr_ok
      && c_parser_nth_token_starts_std_خاصيتون (parser, 1))
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
	  parser->error = سچ;
	  أرجع;
	حالة CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  إذا (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_گروهه d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_اشارو (token->قدر));
	      جوڙيو_note_about_new_keyword (token->location,
					  token->قدر);
	      parser->error = سچ;
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
  وڻ std_attrs = NULL_وڻ;
  وڻ attrs;
  وڻ ident = NULL_وڻ;
  وڻ fixed_underlying_type = NULL_وڻ;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_خاصيتون (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_خاصيتون (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_سيٽ_ذريعو_position_from_token (c_parser_peek_token (parser));
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->قدر;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON)
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
	  ret = parser_xref_ٽيگ (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, سچ);
	  إذا (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_وڻ == TYPE_قدرون (ret.spec);
	}
      وإلا
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_وڻ;
	  ret.قسم = ctsk_tagdef;
	  ret.اظهار = NULL_وڻ;
	  ret.اظهار_const_operands = سچ;
	  ret.has_enum_type_specifier = سچ;
	}
      c_parser_consume_token (parser);
      بنية c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, خطأ, سچ, خطأ, خطأ, خطأ,
			  خطأ, سچ, cla_prefer_id);
      پڄاڻي_declspecs (specs);
      إذا (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      وإلا إذا (وڻ_ڪوڊ (specs->type) != INTEGER_TYPE
	       && وڻ_ڪوڊ (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || وڻ_ڪوڊ (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_ڳنڍ;
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
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_وڻ)
	    {
	      TYPE_MIN_قدر (ret.spec) =
		TYPE_MIN_قدر (fixed_underlying_type);
	      TYPE_MAX_قدر (ret.spec) =
		TYPE_MAX_قدر (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      سيٽ_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_سائيز (ret.spec) = NULL_وڻ;
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
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      بنية c_enum_contents the_enum;
      وڻ type;
      وڻ postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      وڻ قدرون;
      timevar_ڌڪو (TV_PARSE_ENUM);
      type = شروعات_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      قدرون = NULL_وڻ;
      c_parser_consume_token (parser);
      طالما (سچ)
	{
	  وڻ enum_id;
	  وڻ enum_قدر;
	  وڻ enum_decl;
	  منطقي ڏٺل_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, قدر_loc;
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE, عدم);
	      قدرون = error_mark_ڳنڍ;
	      اكسر;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->قدر;
	  /* Set the location in case we create a decl now.  */
	  c_parser_سيٽ_ذريعو_position_from_token (token);
	  decl_loc = قدر_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  وڻ std_attrs = NULL_وڻ;
	  إذا (c_parser_nth_token_starts_std_خاصيتون (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  وڻ enum_attrs = chainon (std_attrs,
				     c_parser_gnu_خاصيتون (parser));
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      قدر_loc = c_parser_peek_token (parser)->location;
	      enum_قدر = convert_lvalue_منزل_rvalue (قدر_loc,
						     (c_parser_اظهار_no_commas
						      (parser, عدم)),
						     سچ, سچ).قدر;
	    }
	  وإلا
	    enum_قدر = NULL_وڻ;
	  enum_decl = build_enumerator (decl_loc, قدر_loc,
					&the_enum, enum_id, enum_قدر);
	  إذا (enum_attrs)
	    decl_خاصيتون (&وڻ_PURPOSE (enum_decl), enum_attrs, 0);
	  وڻ_CHAIN (enum_decl) = قدرون;
	  قدرون = enum_decl;
	  ڏٺل_comma = خطأ;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      ڏٺل_comma = سچ;
	      c_parser_consume_token (parser);
	    }
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      إذا (ڏٺل_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  إذا (!ڏٺل_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE, عدم);
	      قدرون = error_mark_ڳنڍ;
	      اكسر;
	    }
	}
      postfix_attrs = c_parser_gnu_خاصيتون (parser);
      ret.spec = پڄاڻي_enum (type, nreverse (قدرون),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.قسم = ctsk_tagdef;
      ret.اظهار = NULL_وڻ;
      ret.اظهار_const_operands = سچ;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_وڻ;
      timevar_ڪڍو (TV_PARSE_ENUM);
      أرجع ret;
    }
  وإلا إذا (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ڳنڍ;
      ret.قسم = ctsk_tagref;
      ret.اظهار = NULL_وڻ;
      ret.اظهار_const_operands = سچ;
      ret.has_enum_type_specifier = خطأ;
      أرجع ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  إذا (have_std_attrs && c_parser_ايندڙ_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  إذا (fixed_underlying_type == NULL_وڻ)
    {
      ret = parser_xref_ٽيگ (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
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
خالي_جايون
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
  وڻ std_attrs = NULL_وڻ;
  وڻ attrs;
  وڻ ident = NULL_وڻ;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  تعداد وڻ_ڪوڊ_2 ڪوڊ;
  بدل (c_parser_peek_token (parser)->keyword)
    {
    حالة RID_STRUCT:
      ڪوڊ = رڪارڊ_TYPE;
      اكسر;
    حالة RID_UNION:
      ڪوڊ = UNION_TYPE;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_خاصيتون (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_خاصيتون (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_سيٽ_ذريعو_position_from_token (c_parser_peek_token (parser));

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->قدر;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      صنف c_struct_parse_info *struct_info;
      وڻ type = شروعات_struct (struct_loc, ڪوڊ, ident, &struct_info);
      وڻ postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      وڻ contents;
      وڻ اظهار = عدم;
      timevar_ڌڪو (TV_PARSE_STRUCT);
      contents = NULL_وڻ;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_DEFS))
	{
	  وڻ name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  إذا (!parens.require_open (parser))
	    اذهب پڇاڙي_at_defs;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_قسم == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->قدر;
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	      اذهب پڇاڙي_at_defs;
	    }
	  parens.skip_until_مليو_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    پڇاڙي_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      طالما (سچ)
	{
	  وڻ decls;
	  /* Parse any stray semicolon.  */
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.جوڙيو_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  /* Accept #pragmas at struct scope.  */
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, عدم, NULL_وڻ);
	      استمر;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &اظهار);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      وإلا إذا (parser->error
		       || !c_parser_ايندڙ_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE, عدم);
		  اكسر;
		}

	      /* If we come here, we have already emitted an error
		 for an expected `;', identifier or `(', and we also
	         recovered already.  Go on with the next field. */
	    }
	}
      postfix_attrs = c_parser_gnu_خاصيتون (parser);
      ret.spec = پڄاڻي_struct (struct_loc, type, nreverse (contents),
				chainon (std_attrs,
					 chainon (attrs, postfix_attrs)),
				struct_info, &اظهار);
      ret.قسم = ctsk_tagdef;
      ret.اظهار = اظهار;
      ret.اظهار_const_operands = سچ;
      ret.has_enum_type_specifier = خطأ;
      timevar_ڪڍو (TV_PARSE_STRUCT);
      أرجع ret;
    }
  وإلا إذا (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ڳنڍ;
      ret.قسم = ctsk_tagref;
      ret.اظهار = NULL_وڻ;
      ret.اظهار_const_operands = سچ;
      ret.has_enum_type_specifier = خطأ;
      أرجع ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  إذا (have_std_attrs && c_parser_ايندڙ_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_ٽيگ (ident_loc, ڪوڊ, ident, have_std_attrs, std_attrs,
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

ساكن وڻ
c_parser_struct_declaration (c_parser *parser, وڻ *اظهار)
{
  بنية c_declspecs *specs;
  وڻ اڳياڙي_attrs;
  وڻ all_اڳياڙي_attrs;
  وڻ decls;
  location_t decl_loc;
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_EXTENSION))
    {
      صحيح ext;
      وڻ decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, اظهار);
      restore_extension_diagnostics (ext);
      أرجع decl;
    }
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      أرجع NULL_وڻ;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, خطأ, سچ, سچ,
		      سچ, خطأ, سچ, سچ, cla_nonabstract_decl);
  إذا (parser->error)
    أرجع NULL_وڻ;
  إذا (!specs->declspecs_ڏٺل_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      أرجع NULL_وڻ;
    }
  پڄاڻي_declspecs (specs);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)
      || c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
    {
      وڻ ret;
      إذا (specs->typespec_قسم == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_ٽيگ_warned (specs, pedantic);
	  ret = NULL_وڻ;
	}
      وإلا
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  وڻ attrs = عدم;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_وڻ), specs,
			   NULL_وڻ, &attrs, اظهار);
	  إذا (ret)
	    decl_خاصيتون (&ret, attrs, 0);
	}
      أرجع ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  إذا (specs->typespec_قسم == ctsk_tagdef
      && وڻ_ڪوڊ (specs->type) != ENUMERAL_TYPE
      && c_parser_ايندڙ_token_starts_declspecs (parser)
      && !c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = خطأ;
      أرجع NULL_وڻ;
    }

  pending_xref_error ();
  اڳياڙي_attrs = specs->attrs;
  all_اڳياڙي_attrs = اڳياڙي_attrs;
  specs->attrs = NULL_وڻ;
  decls = NULL_وڻ;
  طالما (سچ)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      بنية c_declarator *declarator;
      منطقي dummy = خطأ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_وڻ);
      وإلا
	declarator = c_parser_declarator (parser,
					  specs->typespec_قسم != ctsk_none,
					  C_DTR_عام, &dummy);
      إذا (declarator == عدم)
	{
	  c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
	  اكسر;
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON)
	  || c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  || c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)
	  || c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  وڻ postfix_attrs = NULL_وڻ;
	  وڻ ويڪر = NULL_وڻ;
	  وڻ d;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      ويڪر = convert_lvalue_منزل_rvalue (loc,
						(c_parser_اظهار_no_commas
						 (parser, عدم)),
						سچ, سچ).قدر;
	    }
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_خاصيتون (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, ويڪر, &all_اڳياڙي_attrs, اظهار);
	  decl_خاصيتون (&d, chainon (postfix_attrs,
					all_اڳياڙي_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_اڳياڙي_attrs = chainon (c_parser_gnu_خاصيتون (parser),
					اڳياڙي_attrs);
	  وإلا
	    all_اڳياڙي_attrs = اڳياڙي_attrs;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)
		   || c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
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
  ret.قسم = ctsk_typeof;
  ret.spec = error_mark_ڳنڍ;
  ret.اظهار = NULL_وڻ;
  ret.اظهار_const_operands = سچ;
  ret.has_enum_type_specifier = خطأ;
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = خطأ;
      وڻ spelling = c_parser_peek_token (parser)->قدر;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_اشارو (spelling), "typeof") == 0);
    }
  وإلا
    {
      gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = سچ;
      وڻ spelling = c_parser_peek_token (parser)->قدر;
      is_std = strcmp (IDENTIFIER_اشارو (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  اندريون_typeof++;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      اندريون_typeof--;
      أرجع ret;
    }
  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      اندريون_typeof--;
      إذا (type != عدم)
	{
	  ret.spec = groktypename (type, &ret.اظهار, &ret.اظهار_const_operands);
	  ڪڍو_maybe_استعمال_ٿيل (c_type_variably_modified_p (ret.spec));
	}
    }
  وإلا
    {
      منطقي was_vm;
      location_t هتي = c_parser_peek_token (parser)->location;
      بنية c_اظهار اظهار = c_parser_اظهار (parser);
      c_inhibit_evaluation_warnings--;
      اندريون_typeof--;
      إذا (وڻ_ڪوڊ (اظهار.قدر) == COMPONENT_REF
	  && DECL_C_ٻٽو_انگ_ميدان (وڻ_عمليو (اظهار.قدر, 1)))
	error_at (هتي, "%<typeof%> applied to a bit-field");
      mark_exp_read (اظهار.قدر);
      ret.spec = وڻ_TYPE (اظهار.قدر);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      إذا (was_vm)
	ret.اظهار = c_fully_fold (اظهار.قدر, خطأ, &ret.اظهار_const_operands);
      ڪڍو_maybe_استعمال_ٿيل (was_vm);
    }
  parens.skip_until_مليو_close (parser);
  إذا (ret.spec != error_mark_ڳنڍ)
    {
      إذا (is_unqual)
	{
	  منطقي is_array = وڻ_ڪوڊ (ret.spec) == ARRAY_TYPE;
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
	  إذا (وڻ_ڪوڊ (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  وإلا إذا (FUNCTION_اشارو_TYPE_P (ret.spec)
		   && TYPE_QUALS (وڻ_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_اشارو_type (TYPE_MAIN_VARIANT (وڻ_TYPE (ret.spec)));
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

ساكن وڻ
c_parser_alignas_specifier (c_parser * parser)
{
  وڻ ret = error_mark_ڳنڍ;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_ALIGNAS));
  وڻ spelling = c_parser_peek_token (parser)->قدر;
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
  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *type = c_parser_type_name (parser);
      إذا (type != عدم)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, عدم, عدم),
					خطأ, سچ, 1);
    }
  وإلا
    ret = convert_lvalue_منزل_rvalue (loc,
				    c_parser_اظهار_no_commas (parser, عدم),
				    سچ, سچ).قدر;
  parens.skip_until_مليو_close (parser);
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
اشارو
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
c_parser_declarator (c_parser *parser, منطقي type_ڏٺل_p, c_dtr_syn قسم,
		     منطقي *ڏٺل_id)
{
  /* Parse any initial pointer part.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_MULT))
    {
      بنية c_declspecs *quals_attrs = build_null_declspecs ();
      بنية c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, سچ,
			  خطأ, خطأ, سچ, خطأ, cla_prefer_id);
      inner = c_parser_declarator (parser, type_ڏٺل_p, قسم, ڏٺل_id);
      إذا (inner == عدم)
	أرجع عدم;
      وإلا
	أرجع make_اشارو_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  أرجع c_parser_سڌو_declarator (parser, type_ڏٺل_p, قسم, ڏٺل_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

ساكن بنية c_declarator *
c_parser_سڌو_declarator (c_parser *parser, منطقي type_ڏٺل_p, c_dtr_syn قسم,
			    منطقي *ڏٺل_id)
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

  إذا (قسم != C_DTR_ABSTRACT
      && c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && ((type_ڏٺل_p
	   && (c_parser_peek_token (parser)->id_قسم == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_قسم == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_قسم == C_ID_ID))
    {
      بنية c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->قدر);
      *ڏٺل_id = سچ;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (c_parser_nth_token_starts_std_خاصيتون (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      أرجع c_parser_سڌو_declarator_inner (parser, *ڏٺل_id, inner);
    }

  إذا (قسم != C_DTR_عام
      && c_parser_ايندڙ_token_is (parser, CPP_OPEN_چورس)
      && !c_parser_nth_token_starts_std_خاصيتون (parser, 1))
    {
      بنية c_declarator *inner = build_id_declarator (NULL_وڻ);
      inner->id_loc = c_parser_peek_token (parser)->location;
      أرجع c_parser_سڌو_declarator_inner (parser, *ڏٺل_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      وڻ attrs;
      بنية c_declarator *inner;
      c_parser_consume_token (parser);
      منطقي have_gnu_attrs = c_parser_ايندڙ_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_خاصيتون (parser);
      إذا (قسم != C_DTR_عام
	  && (c_parser_ايندڙ_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_خاصيتون (parser, 1)
		      || c_parser_ايندڙ_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  بنية c_arg_info *دليلون
	    = c_parser_parms_declarator (parser, قسم == C_DTR_عام,
					 attrs, have_gnu_attrs);
	  إذا (دليلون == عدم)
	    أرجع عدم;
	  وإلا
	    {
	      inner = build_id_declarator (NULL_وڻ);
	      إذا (!(دليلون->types
		    && دليلون->types != error_mark_ڳنڍ
		    && وڻ_ڪوڊ (وڻ_قدر (دليلون->types)) == IDENTIFIER_ڳنڍ)
		  && c_parser_nth_token_starts_std_خاصيتون (parser, 1))
		{
		  وڻ std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  إذا (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (دليلون, inner);
	      أرجع c_parser_سڌو_declarator_inner (parser, *ڏٺل_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_ڏٺل_p, قسم, ڏٺل_id);
      إذا (inner != عدم && attrs != عدم)
	inner = build_attrs_declarator (attrs, inner);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  إذا (inner == عدم)
	    أرجع عدم;
	  وإلا
	    أرجع c_parser_سڌو_declarator_inner (parser, *ڏٺل_id, inner);
	}
      وإلا
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع عدم;
	}
    }
  وإلا
    {
      إذا (قسم == C_DTR_عام)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  أرجع عدم;
	}
      وإلا
	أرجع build_id_declarator (NULL_وڻ);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

ساكن بنية c_declarator *
c_parser_سڌو_declarator_inner (c_parser *parser, منطقي id_present,
				  بنية c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_چورس)
      && !c_parser_nth_token_starts_std_خاصيتون (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      بنية c_declarator *declarator;
      بنية c_declspecs *quals_attrs = build_null_declspecs ();
      بنية c_اظهار dimen;
      dimen.قدر = NULL_وڻ;
      dimen.original_ڪوڊ = ERROR_MARK;
      dimen.original_type = NULL_وڻ;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, سچ,
			  خطأ, خطأ, خطأ, خطأ, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  إذا (!quals_attrs->declspecs_ڏٺل_p)
	    c_parser_declspecs (parser, quals_attrs, خطأ, خطأ, سچ,
				خطأ, خطأ, خطأ, خطأ, cla_prefer_id);
	}
      إذا (!quals_attrs->declspecs_ڏٺل_p)
	quals_attrs = عدم;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ثابت منطقي static_ڏٺل = (static_loc != UNKNOWN_LOCATION);
      منطقي تارو_ڏٺل = خطأ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_چورس)
	{
	  تارو_ڏٺل = سچ;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (!c_parser_ايندڙ_token_is (parser, CPP_CLOSE_چورس))
	dimen = c_parser_اظهار_no_commas (parser, عدم);

      إذا (static_ڏٺل)
	{
	  إذا (تارو_ڏٺل)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      تارو_ڏٺل = خطأ;
	      dimen.قدر = error_mark_ڳنڍ;
	    }
	  وإلا إذا (!dimen.قدر)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_چورس))
	c_parser_consume_token (parser);
      وإلا
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس,
				     "expected %<]%>");
	  أرجع عدم;
	}
      إذا (dimen.قدر)
	dimen = convert_lvalue_منزل_rvalue (brace_loc, dimen, سچ, سچ);
      declarator = build_array_declarator (brace_loc, dimen.قدر, quals_attrs,
					   static_ڏٺل, تارو_ڏٺل);
      إذا (declarator == عدم)
	أرجع عدم;
      إذا (c_parser_nth_token_starts_std_خاصيتون (parser, 1))
	{
	  وڻ std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  إذا (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = سيٽ_array_declarator_inner (declarator, inner);
      أرجع c_parser_سڌو_declarator_inner (parser, id_present, inner);
    }
  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      وڻ attrs;
      بنية c_arg_info *دليلون;
      c_parser_consume_token (parser);
      منطقي have_gnu_attrs = c_parser_ايندڙ_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_خاصيتون (parser);
      دليلون = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      إذا (دليلون == عدم)
	أرجع عدم;
      وإلا
	{
	  إذا (!(دليلون->types
		&& دليلون->types != error_mark_ڳنڍ
		&& وڻ_ڪوڊ (وڻ_قدر (دليلون->types)) == IDENTIFIER_ڳنڍ)
	      && c_parser_nth_token_starts_std_خاصيتون (parser, 1))
	    {
	      وڻ std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      إذا (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (دليلون, inner);
	  أرجع c_parser_سڌو_declarator_inner (parser, id_present, inner);
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
c_parser_parms_declarator (c_parser *parser, منطقي id_list_ok, وڻ attrs,
			   منطقي have_gnu_attrs)
{
  ڌڪو_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  إذا (id_list_ok
      && !attrs
      && c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && c_parser_peek_token (parser)->id_قسم == C_ID_ID

      /* Look ahead to detect typos in type names.  */
      && c_parser_peek_2nd_token (parser)->type != CPP_NAME
      && c_parser_peek_2nd_token (parser)->type != CPP_MULT
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_چورس
      && c_parser_peek_2nd_token (parser)->type != CPP_KEYWORD)
    {
      وڻ list = NULL_وڻ, *nextp = &list;
      طالما (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_قسم == C_ID_ID)
	{
	  *nextp = build_وڻ_list (NULL_وڻ,
				    c_parser_peek_token (parser)->قدر);
	  nextp = & وڻ_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      اكسر;
	    }
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  بنية c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  ڪڍو_scope ();
	  أرجع ret;
	}
      وإلا
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ڪڍو_scope ();
	  أرجع عدم;
	}
    }
  وإلا
    {
      بنية c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, عدم, have_gnu_attrs);
      ڪڍو_scope ();
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
c_parser_parms_list_declarator (c_parser *parser, وڻ attrs, وڻ اظهار,
				منطقي have_gnu_attrs)
{
  منطقي bad_parm = خطأ;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
    {
      بنية c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      أرجع ret;
    }
  إذا (c_parser_ايندڙ_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      بنية c_arg_info *ret = build_arg_info ();

      ret->types = NULL_وڻ;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_دليلون_stdarg_p = سچ;
	  c_parser_consume_token (parser);
	  أرجع ret;
	}
      وإلا
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع عدم;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  طالما (سچ)
    {
      /* Parse a parameter.  */
      بنية c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_وڻ;
      have_gnu_attrs = خطأ;
      إذا (parm == عدم)
	bad_parm = سچ;
      وإلا
	ڌڪو_parm_decl (parm, &اظهار);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	{
	  وڻ new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  منطقي new_have_gnu_attrs
	    = c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_خاصيتون (parser);
	  أرجع c_parser_parms_list_declarator (parser, new_attrs, اظهار,
						 new_have_gnu_attrs);
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  إذا (bad_parm)
	    أرجع عدم;
	  وإلا
	    أرجع get_parm_info (خطأ, اظهار);
	}
      إذا (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, خطأ))
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع عدم;
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      إذا (bad_parm)
		أرجع عدم;
	      وإلا
		أرجع get_parm_info (سچ, اظهار);
	    }
	  وإلا
	    {
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
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
c_parser_parameter_declaration (c_parser *parser, وڻ attrs,
				منطقي have_gnu_attrs)
{
  بنية c_declspecs *specs;
  بنية c_declarator *declarator;
  وڻ اڳياڙي_attrs;
  وڻ postfix_attrs = NULL_وڻ;
  منطقي dummy = خطأ;

  /* Accept #pragmas between parameter declarations.  */
  طالما (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, عدم, NULL_وڻ);

  إذا (!c_parser_ايندڙ_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_خاصيتون (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (parser->error)
	أرجع عدم;
      c_parser_سيٽ_ذريعو_position_from_token (token);
      إذا (c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_گروهه d;
	  name_hint hint = lookup_name_fuzzy (token->قدر,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  إذا (ثابت حرف *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.جوڙيو_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->قدر, suggestion);
	    }
	  وإلا
	    error_at (token->location, "unknown type name %qE", token->قدر);
	  parser->error = سچ;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      وإلا
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_منزل_پڇاڙي_جو_parameter (parser);
      أرجع عدم;
    }

  location_t شروعات_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  إذا (attrs)
    {
      declspecs_جوڙيو_attrs (داخلا_location, specs, attrs);
      attrs = NULL_وڻ;
    }
  c_parser_declspecs (parser, specs, سچ, سچ, سچ, سچ, خطأ,
		      !have_gnu_attrs, سچ, cla_nonabstract_decl);
  پڄاڻي_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  إذا (specs->typespec_قسم == ctsk_tagdef)
    verify_counted_by_for_چوٽي_anonymous_type (specs->type);

  pending_xref_error ();
  اڳياڙي_attrs = specs->attrs;
  specs->attrs = NULL_وڻ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_قسم != ctsk_none,
				    C_DTR_PARM, &dummy);
  إذا (declarator == عدم)
    {
      c_parser_skip_until_مليو (parser, CPP_COMMA, عدم);
      أرجع عدم;
    }
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
    postfix_attrs = c_parser_gnu_خاصيتون (parser);

  /* Generate a location for the parameter, ranging from the start of the
     initial token to the end of the final token.

     If we have a identifier, then use it for the caret location, e.g.

       extern int callee (int one, int (*two)(int, int), float three);
                                   ~~~~~~^~~~~~~~~~~~~~

     otherwise, reuse the start location for the caret location e.g.:

       extern int callee (int one, int (*)(int, int), float three);
                                   ^~~~~~~~~~~~~~~~~
  */
  location_t پڇاڙي_loc = parser->آخري_token_location;

  /* Find any cdk_id declarator; determine if we have an identifier.  */
  c_declarator *id_declarator = declarator;
  طالما (id_declarator && id_declarator->قسم != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : شروعات_loc);
  location_t param_loc = make_location (caret_loc, شروعات_loc, پڇاڙي_loc);

  أرجع build_c_parm (specs, chainon (postfix_attrs, اڳياڙي_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

ساكن وڻ
c_parser_asm_string_literal (c_parser *parser)
{
  وڻ str;
  صحيح save_flag = warn_overlength_لڙيون;
  warn_overlength_لڙيون = 0;
  str = c_parser_string_literal (parser, خطأ, خطأ).قدر;
  warn_overlength_لڙيون = save_flag;
  أرجع str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

ساكن وڻ
c_parser_simple_asm_اظهار (c_parser *parser)
{
  وڻ str;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع NULL_وڻ;
  str = c_parser_asm_string_literal (parser);
  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
      أرجع NULL_وڻ;
    }
  أرجع str;
}

ساكن وڻ
c_parser_gnu_attribute_any_لفظ (c_parser *parser)
{
  وڻ attr_name = NULL_وڻ;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD))
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
	حالة RID_رجسٽر:
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
	  ok = سچ;
	  اكسر;
	افتراضي:
	  ok = خطأ;
	  اكسر;
	}
      إذا (!ok)
	أرجع NULL_وڻ;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(صحيح) c_parser_peek_token (parser)->keyword];
    }
  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->قدر;

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

ساكن وڻ
c_parser_attribute_arguments (c_parser *parser, منطقي takes_identifier,
			      منطقي require_string, منطقي assume_attr,
			      منطقي allow_خالي_جايون_دليلون)
{
  vec<وڻ, va_gc> *اظهار_list;
  وڻ attr_دليلون;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && (c_parser_peek_token (parser)->id_قسم == C_ID_ID
	  || (c_dialect_objc ()
	      && c_parser_peek_token (parser)->id_قسم
	      == C_ID_CLASSNAME))
      && ((c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	  || (c_parser_peek_2nd_token (parser)->type
	      == CPP_CLOSE_PAREN))
      && (takes_identifier
	  || (c_dialect_objc ()
	      && !assume_attr
	      && c_parser_peek_token (parser)->id_قسم
	      == C_ID_CLASSNAME)))
    {
      وڻ arg1 = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	attr_دليلون = build_وڻ_list (NULL_وڻ, arg1);
      وإلا
	{
	  وڻ وڻ_list;
	  c_parser_consume_token (parser);
	  اظهار_list = c_parser_اظهار_list (parser, خطأ, سچ,
					  عدم, عدم, عدم, عدم);
	  وڻ_list = build_وڻ_list_vec (اظهار_list);
	  attr_دليلون = وڻ_cons (NULL_وڻ, arg1, وڻ_list);
	  release_وڻ_ويڪٽر (اظهار_list);
	}
    }
  وإلا
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (!allow_خالي_جايون_دليلون)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_دليلون = NULL_وڻ;
	}
      وإلا إذا (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  وڻ string = c_parser_string_literal (parser, خطأ, سچ).قدر;
	  attr_دليلون = build_وڻ_list (NULL_وڻ, string);
	}
      وإلا إذا (assume_attr)
	{
	  وڻ cond
	    = c_parser_conditional_اظهار (parser, عدم, NULL_وڻ).قدر;
	  إذا (!c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    attr_دليلون = build_وڻ_list (NULL_وڻ, cond);
	  وإلا
	    {
	      وڻ وڻ_list;
	      c_parser_consume_token (parser);
	      اظهار_list = c_parser_اظهار_list (parser, خطأ, سچ,
					      عدم, عدم, عدم, عدم);
	      وڻ_list = build_وڻ_list_vec (اظهار_list);
	      attr_دليلون = وڻ_cons (NULL_وڻ, cond, وڻ_list);
	      release_وڻ_ويڪٽر (اظهار_list);
	    }
	}
      وإلا
	{
	  اظهار_list = c_parser_اظهار_list (parser, خطأ, سچ,
					  عدم, عدم, عدم, عدم);
	  attr_دليلون = build_وڻ_list_vec (اظهار_list);
	  release_وڻ_ويڪٽر (اظهار_list);
	}
    }
  أرجع attr_دليلون;
}

/* Parse (possibly empty) gnu-attributes.  This is a GNU extension.

   gnu-attributes:
خالي_جايون
     gnu-attributes gnu-attribute

   gnu-attribute:
     __attribute__ ( ( gnu-attribute-list ) )

   gnu-attribute-list:
     gnu-attrib
     gnu-attribute_list , gnu-attrib

   gnu-attrib:
خالي_جايون
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

ساكن وڻ
c_parser_gnu_attribute (c_parser *parser, وڻ attrs,
			منطقي expect_comma = خطأ, منطقي خالي_جايون_ok = سچ)
{
  منطقي comma_پهريون = c_parser_ايندڙ_token_is (parser, CPP_COMMA);
  إذا (!comma_پهريون
      && !c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && !c_parser_ايندڙ_token_is (parser, CPP_KEYWORD))
    أرجع NULL_وڻ;

  طالما (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (!خالي_جايون_ok)
	أرجع attrs;
    }

  وڻ attr_name = c_parser_gnu_attribute_any_لفظ (parser);
  إذا (attr_name == NULL_وڻ)
    أرجع NULL_وڻ;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  وڻ attr;
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_OPEN_PAREN))
    {
      إذا (expect_comma && !comma_پهريون)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع error_mark_ڳنڍ;
	}
      attr = build_وڻ_list (attr_name, NULL_وڻ);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      أرجع attrs;
    }
  c_parser_consume_token (parser);

  وڻ attr_دليلون
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    خطأ,
				    is_attribute_p ("assume", attr_name),
				    سچ);

  attr = build_وڻ_list (attr_name, attr_دليلون);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع error_mark_ڳنڍ;
    }

  إذا (expect_comma && !comma_پهريون)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع error_mark_ڳنڍ;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  أرجع attrs;
}

ساكن وڻ
c_parser_gnu_خاصيتون (c_parser *parser)
{
  وڻ attrs = NULL_وڻ;
  طالما (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      منطقي save_translate_لڙيون_p = parser->translate_لڙيون_p;
      parser->translate_لڙيون_p = خطأ;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_لڙيون_p = save_translate_لڙيون_p;
	  أرجع attrs;
	}
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_لڙيون_p = save_translate_لڙيون_p;
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      لكل (منطقي expect_comma = خطأ; ; expect_comma = سچ)
	{
	  /* Parse a single attribute.  */
	  وڻ attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  إذا (attr == error_mark_ڳنڍ)
	    أرجع attrs;
	  إذا (!attr)
	    اكسر;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      وإلا
	{
	  parser->translate_لڙيون_p = save_translate_لڙيون_p;
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع attrs;
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      وإلا
	{
	  parser->translate_لڙيون_p = save_translate_لڙيون_p;
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع attrs;
	}
      parser->translate_لڙيون_p = save_translate_لڙيون_p;
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
  طالما (سچ)
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

	حالة CPP_OPEN_چورس:
	  c_parser_consume_token (parser);
	  c_parser_متوازن_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_چورس, "expected %<]%>");
	  اكسر;

	حالة CPP_CLOSE_BRACE:
	حالة CPP_CLOSE_PAREN:
	حالة CPP_CLOSE_چورس:
	حالة CPP_EOF:
	  أرجع;

	حالة CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
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
c_parser_omp_directive_دليلون (c_parser *parser, وڻ attribute, منطقي decl_p)
{
  بنانشان صحيح n = 1;
  c_token *پهريون = c_parser_peek_token (parser);
  إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_متوازن_token_sequence (parser);
      وڻ_قدر (attribute) = NULL_وڻ;
      أرجع;
    }
  إذا (n == 1)
    {
      error_at (پهريون->location, "expected OpenMP directive name");
      وڻ_قدر (attribute) = NULL_وڻ;
      أرجع;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  لكل (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->تيز_ڌڪو (*tok);
      c_parser_consume_token (parser);
    }
  وڻ arg = make_ڳنڍ (C_TOKEN_VEC);
  C_TOKEN_VEC_ٽوڪن (arg) = v;
  إذا (decl_p)
    وڻ_عوامي (arg) = 1;
  وڻ_قدر (attribute) = وڻ_cons (NULL_وڻ, arg, وڻ_قدر (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

ساكن فراغ
c_parser_omp_sequence_دليلون (c_parser *parser, وڻ attribute)
{
  افعل
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_اشارو (token->قدر), "omp") == 0
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
	p = IDENTIFIER_اشارو (token->قدر);
      إذا (strcmp (p, "directive") == 0)
	directive = سچ;
      وإلا إذا (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  بنانشان nesting_اونهائي = 0;

	  طالما (سچ)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      إذا ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_اونهائي)
		اكسر;
	      /* If we've run out of tokens, stop.  */
	      إذا (token->type == CPP_EOF)
		اكسر;
	      إذا (token->type == CPP_PRAGMA_EOL && parser->اندريون_pragma)
		اكسر;
	      إذا (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_چورس)
		++nesting_اونهائي;
	      وإلا إذا (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_چورس)
		{
		  إذا (nesting_اونهائي-- == 0)
		    اكسر;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	  استمر;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      إذا (parens.require_open (parser))
	{
	  إذا (directive)
	    c_parser_omp_directive_دليلون (parser, attribute, خطأ);
	  وإلا
	    c_parser_omp_sequence_دليلون (parser, attribute);
	  parens.skip_until_مليو_close (parser);
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COMMA))
	    اكسر;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COMMA))
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

ساكن وڻ
c_parser_std_attribute (c_parser *parser, منطقي for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  وڻ ns, name, attribute;

  /* Parse the attribute-token.  */
  إذا (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      أرجع error_mark_ڳنڍ;
    }
  name = canonicalize_attr_name (token->قدر);
  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_SCOPE)
      || (c_parser_ايندڙ_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      إذا (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع error_mark_ڳنڍ;
	}
      name = canonicalize_attr_name (token->قدر);
      c_parser_consume_token (parser);
    }
  وإلا
    ns = NULL_وڻ;
  attribute = build_وڻ_list (build_وڻ_list (ns, name), NULL_وڻ);

  /* Parse the arguments, if any.  */
  ثابت attribute_spec *as = lookup_attribute_spec (وڻ_PURPOSE (attribute));
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_OPEN_PAREN))
    {
      إذا ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  أرجع error_mark_ڳنڍ;
	}
      اذهب ٻاهريون;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    إذا ((as && as->max_ڊيگهائي == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_مليو_close (parser);
	أرجع error_mark_ڳنڍ;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    إذا (as && !attribute_ignored_p (as))
      {
	منطقي takes_identifier
	  = (ns != NULL_وڻ
	     && strcmp (IDENTIFIER_اشارو (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	منطقي require_string
	  = (ns == NULL_وڻ
	     && (strcmp (IDENTIFIER_اشارو (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_اشارو (name), "nodiscard") == 0));
	منطقي assume_attr
	  = (ns != NULL_وڻ
	     && strcmp (IDENTIFIER_اشارو (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_اشارو (name), "assume") == 0);
	وڻ_قدر (attribute)
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
		c_parser_omp_directive_دليلون (parser, attribute, خطأ);
		parens.skip_until_مليو_close (parser);
		أرجع attribute;
	      }
	    وإلا إذا (is_attribute_p ("decl", name))
	      {
		وڻ_قدر (وڻ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_دليلون (parser, attribute, سچ);
		parens.skip_until_مليو_close (parser);
		أرجع attribute;
	      }
	    وإلا إذا (is_attribute_p ("sequence", name))
	      {
		وڻ_قدر (وڻ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_دليلون (parser, attribute);
		parens.skip_until_مليو_close (parser);
		وڻ_قدر (attribute) = nreverse (وڻ_قدر (attribute));
		أرجع attribute;
	      }
	  }
	c_parser_متوازن_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 ٻاهريون:
  إذا (ns == NULL_وڻ && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (داخلا_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      أرجع error_mark_ڳنڍ;
    }
  أرجع attribute;
}

ساكن وڻ
c_parser_std_attribute_list (c_parser *parser, منطقي for_tm)
{
  وڻ خاصيتون = NULL_وڻ;
  طالما (سچ)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_CLOSE_چورس)
	اكسر;
      إذا (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      وڻ attribute = c_parser_std_attribute (parser, for_tm);
      إذا (attribute != error_mark_ڳنڍ)
	{
	  وڻ_CHAIN (attribute) = خاصيتون;
	  خاصيتون = attribute;
	}
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COMMA))
	اكسر;
    }
  أرجع خاصيتون;
}

ساكن وڻ
c_parser_std_attribute_specifier (c_parser *parser, منطقي for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_چورس, "expected %<[%>"))
    أرجع NULL_وڻ;
  إذا (!c_parser_require (parser, CPP_OPEN_چورس, "expected %<[%>"))
    {
      c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس, "expected %<]%>");
      أرجع NULL_وڻ;
    }
  وڻ خاصيتون;
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_EXTENSION))
    {
      خودڪار ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      خاصيتون = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  وإلا
    {
      إذا (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      خاصيتون = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس, "expected %<]%>");
  c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس, "expected %<]%>");
  أرجع nreverse (خاصيتون);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

ساكن منطقي
c_parser_check_متوازن_raw_token_sequence (c_parser *parser, بنانشان صحيح *n)
{
  طالما (سچ)
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

	حالة CPP_OPEN_چورس:
	  {
	    ++*n;
	    إذا (c_parser_check_متوازن_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		إذا (token->type == CPP_CLOSE_چورس)
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
	حالة CPP_CLOSE_چورس:
	حالة CPP_EOF:
	  أرجع سچ;

	افتراضي:
	  ++*n;
	  اكسر;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

ساكن منطقي
c_parser_nth_token_starts_std_خاصيتون (c_parser *parser, بنانشان صحيح n)
{
  إذا (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_چورس
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_چورس))
    أرجع خطأ;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  إذا (!c_dialect_objc ())
    أرجع سچ;
  n += 2;
  إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &n))
    أرجع خطأ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  إذا (token->type != CPP_CLOSE_چورس)
    أرجع خطأ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  أرجع token->type == CPP_CLOSE_چورس;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

ساكن سائيز_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, سائيز_t n)
{
  سائيز_t orig_n = n;
  طالما (سچ)
    {
      إذا (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_چورس
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_چورس))
	{
	  بنانشان صحيح m = n + 2;
	  إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &m))
	    أرجع orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  إذا (token->type != CPP_CLOSE_چورس)
	    أرجع orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  إذا (token->type != CPP_CLOSE_چورس)
	    أرجع orig_n;
	  n = m + 2;
	}
      وإلا
	اكسر;
    }
  أرجع n;
}

ساكن وڻ
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  وڻ خاصيتون = NULL_وڻ;
  افعل
    {
      وڻ attrs = c_parser_std_attribute_specifier (parser, خطأ);
      خاصيتون = chainon (خاصيتون, attrs);
    }
  طالما (c_parser_nth_token_starts_std_خاصيتون (parser, 1));
  أرجع خاصيتون;
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
  c_parser_declspecs (parser, specs, خطأ, سچ, سچ, alignas_ok, خطأ,
		      خطأ, سچ, cla_prefer_type);
  إذا (!specs->declspecs_ڏٺل_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      أرجع عدم;
    }
  إذا (specs->type != error_mark_ڳنڍ)
    {
      pending_xref_error ();
      پڄاڻي_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      إذا (specs->typespec_قسم == ctsk_tagdef)
	verify_counted_by_for_چوٽي_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_قسم != ctsk_none,
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

ساكن بنية c_اظهار
c_parser_initializer (c_parser *parser, وڻ decl)
{
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    أرجع c_parser_braced_init (parser, NULL_وڻ, خطأ, عدم,
				 decl != error_mark_ڳنڍ
				 && C_DECL_VARIABLE_سائيز (decl));
  وإلا
    {
      بنية c_اظهار ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_اظهار_no_commas (parser, عدم);
      إذا (decl != error_mark_ڳنڍ && C_DECL_VARIABLE_سائيز (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.سيٽ_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      إذا (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !وڻ_STATIC (decl)
	  && ret.قدر == decl
	  && !warning_enabled_at (DECL_ذريعو_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      إذا (وڻ_ڪوڊ (ret.قدر) != STRING_CST
	  && (وڻ_ڪوڊ (ret.قدر) != COMPOUND_LITERAL_اظهار
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_اظهار_DECL
					    (ret.قدر))))
	ret = convert_lvalue_منزل_rvalue (loc, ret, سچ, سچ, سچ);
      أرجع ret;
    }
}

/* The location of the last comma within the current initializer list,
   or UNKNOWN_LOCATION if not within one.  */

location_t آخري_init_list_comma;

/* Parse a braced initializer list.  TYPE is the type specified for a
   compound literal, and NULL_TREE for other initializers and for
   nested braced lists.  NESTED_P is true for nested braced lists,
   false for the list of a compound literal or the list that is the
   top-level initializer in a declaration.  VARSIZE_P indicates
   whether the object to be initialized has a variable size.  */

ساكن بنية c_اظهار
c_parser_braced_init (c_parser *parser, وڻ type, منطقي nested_p,
		      بنية obstack *outer_obstack, منطقي varsize_p)
{
  بنية c_اظهار ret;
  بنية obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE));
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = خطأ;
  منطقي zero_init_padding_بٽ = خطأ;
  matching_braces braces;
  braces.consume_open (parser);
  إذا (nested_p)
    {
      پڄاڻي_implicit_inits (brace_loc, outer_obstack);
      ڌڪو_init_level (brace_loc, 0, &braced_init_obstack);
    }
  وإلا
    really_شروعات_incremental_init (type);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      إذا (flag_isoc23)
	zero_init_padding_بٽ = سچ;
    }
  وإلا
    {
      إذا (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      طالما (سچ)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  إذا (parser->error)
	    اكسر;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    {
	      آخري_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      طالما (c_parser_ايندڙ_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_اظهار embed_val;
		  embed_val.قدر = embed->قدر;
		  embed_val.original_ڪوڊ = RAW_معلومات_CST;
		  embed_val.original_type = integer_type_ڳنڍ;
		  سيٽ_c_اظهار_ذريعو_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, خطأ,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_ايندڙ_token_is (parser,
							       CPP_COMMA));
		  آخري_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  وإلا
	    اكسر;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	    اكسر;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *ايندڙ_tok = c_parser_peek_token (parser);
  إذا (ايندڙ_tok->type != CPP_CLOSE_BRACE)
    {
      ret.سيٽ_error ();
      ret.original_ڪوڊ = ERROR_MARK;
      ret.original_type = عدم;
      braces.skip_until_مليو_close (parser);
      ڪڍو_init_level (brace_loc, 0, &braced_init_obstack, آخري_init_list_comma);
      obstack_free (&braced_init_obstack, عدم);
      أرجع ret;
    }
  location_t close_loc = ايندڙ_tok->location;
  c_parser_consume_token (parser);
  ret = ڪڍو_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  إذا (zero_init_padding_بٽ
      && ret.قدر
      && وڻ_ڪوڊ (ret.قدر) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_بٽ (ret.قدر) = 1;
  obstack_free (&braced_init_obstack, عدم);
  سيٽ_c_اظهار_ذريعو_range (&ret, brace_loc, close_loc);
  أرجع ret;
}

/* Parse a nested initializer, including designators.  */

ساكن فراغ
c_parser_initelt (c_parser *parser, بنية obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      سيٽ_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->قدر,
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
      صحيح des_ڏٺل = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      طالما (c_parser_ايندڙ_token_is (parser, CPP_OPEN_چورس)
	     || c_parser_ايندڙ_token_is (parser, CPP_DOT))
	{
	  صحيح des_prev = des_ڏٺل;
	  إذا (!des_ڏٺل)
	    des_loc = c_parser_peek_token (parser)->location;
	  إذا (des_ڏٺل < 2)
	    des_ڏٺل++;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_DOT))
	    {
	      des_ڏٺل = 2;
	      c_parser_consume_token (parser);
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		{
		  سيٽ_init_label (des_loc, c_parser_peek_token (parser)->قدر,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      وإلا
		{
		  بنية c_اظهار init;
		  init.سيٽ_error ();
		  init.original_ڪوڊ = ERROR_MARK;
		  init.original_type = عدم;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_مليو (parser, CPP_COMMA, عدم);
		  process_init_element (داخلا_location, init, خطأ,
					braced_init_obstack);
		  أرجع;
		}
	    }
	  وإلا
	    {
	      بنية c_اظهار پهريون_اظهار;
	      وڻ پهريون, ٻيو;
	      location_t ellipsis_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	      location_t array_اشاريو_loc = UNKNOWN_LOCATION;
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
		  des_ڏٺل = des_prev;
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
		  وڻ rec, دليلون;
		  بنية c_اظهار mexpr;
		  c_parser_consume_token (parser);
		  إذا (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_قسم
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_قسم
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      وڻ id = c_parser_peek_token (parser)->قدر;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      اذهب parse_پيغام_دليلون;
		    }
		  array_اشاريو_loc = c_parser_peek_token (parser)->location;
		  پهريون_اظهار = c_parser_اظهار_no_commas (parser, عدم);
		  mark_exp_read (پهريون_اظهار.قدر);
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_ايندڙ_token_is (parser, CPP_CLOSE_چورس))
		    اذهب array_desig_after_پهريون;
		  پهريون = پهريون_اظهار.قدر;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = پهريون;
		  طالما (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		    {
		      بنية c_اظهار ايندڙ;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      ايندڙ = c_parser_اظهار_no_commas (parser, عدم);
		      ايندڙ = convert_lvalue_منزل_rvalue (exp_loc, ايندڙ,
						       سچ, سچ);
		      rec = build_compound_اظهار (comma_loc, rec, ايندڙ.قدر);
		    }
		parse_پيغام_دليلون:
		  /* Now parse the objc-message-args.  */
		  دليلون = c_parser_objc_پيغام_دليلون (parser);
		  c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس,
					     "expected %<]%>");
		  mexpr.قدر
		    = objc_build_پيغام_اظهار (rec, دليلون);
		  mexpr.original_ڪوڊ = ERROR_MARK;
		  mexpr.original_type = عدم;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  أرجع;
		}
	      c_parser_consume_token (parser);
	      array_اشاريو_loc = c_parser_peek_token (parser)->location;
	      پهريون_اظهار = c_parser_اظهار_no_commas (parser, عدم);
	      mark_exp_read (پهريون_اظهار.قدر);
	    array_desig_after_پهريون:
	      پهريون_اظهار = convert_lvalue_منزل_rvalue (array_اشاريو_loc,
						     پهريون_اظهار,
						     سچ, سچ);
	      پهريون = پهريون_اظهار.قدر;
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  ٻيو = convert_lvalue_منزل_rvalue (ellipsis_loc,
						     (c_parser_اظهار_no_commas
						      (parser, عدم)),
						     سچ, سچ).قدر;
		  mark_exp_read (ٻيو);
		}
	      وإلا
		ٻيو = NULL_وڻ;
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_چورس))
		{
		  c_parser_consume_token (parser);
		  سيٽ_init_اشاريو (array_اشاريو_loc, پهريون, ٻيو,
				  braced_init_obstack);
		  إذا (ٻيو)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      وإلا
		c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس,
					   "expected %<]%>");
	    }
	}
      إذا (des_ڏٺل >= 1)
	{
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      إذا (des_ڏٺل == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      وإلا
		{
		  بنية c_اظهار init;
		  init.سيٽ_error ();
		  init.original_ڪوڊ = ERROR_MARK;
		  init.original_type = عدم;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_مليو (parser, CPP_COMMA, عدم);
		  process_init_element (داخلا_location, init, خطأ,
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
c_parser_initval (c_parser *parser, بنية c_اظهار *after,
		  بنية obstack * braced_init_obstack)
{
  بنية c_اظهار init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_وڻ, سچ,
				 braced_init_obstack, خطأ);
  وإلا
    {
      init = c_parser_اظهار_no_commas (parser, after);
      إذا (init.قدر != NULL_وڻ
	  && وڻ_ڪوڊ (init.قدر) != STRING_CST
	  && (وڻ_ڪوڊ (init.قدر) != COMPOUND_LITERAL_اظهار
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_اظهار_DECL
					    (init.قدر))))
	init = convert_lvalue_منزل_rvalue (loc, init, سچ, سچ, سچ);
    }
  وڻ val = init.قدر;
  process_init_element (loc, init, خطأ, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  ساكن بنانشان vals_منزل_ignore;
  إذا (vals_منزل_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_منزل_ignore;
  وإلا إذا (val
	   && وڻ_ڪوڊ (val) == INTEGER_CST
	   && وڻ_TYPE (val) == integer_type_ڳنڍ
	   && c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    إذا (بنانشان صحيح len = c_maybe_optimize_large_byte_initializer ())
      {
	حرف buf1[64];
	بنانشان صحيح i;
	gcc_checking_assert (len >= 64);
	location_t آخري_loc = UNKNOWN_LOCATION;
	لكل (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    إذا (tok->type != CPP_COMMA)
	      اكسر;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    إذا (tok->type != CPP_عدد
		|| وڻ_ڪوڊ (tok->قدر) != INTEGER_CST
		|| وڻ_TYPE (tok->قدر) != integer_type_ڳنڍ
		|| wi::neg_p (wi::منزل_wide (tok->قدر))
		|| wi::منزل_widest (tok->قدر) > UCHAR_MAX)
	      اكسر;
	    buf1[i] = (حرف) وڻ_منزل_uhwi (tok->قدر);
	    إذا (i == 0)
	      loc = tok->location;
	    آخري_loc = tok->location;
	  }
	إذا (i < 64)
	  {
	    vals_منزل_ignore = i;
	    أرجع;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	إذا (tok->type == CPP_CLOSE_BRACE && len != وڌ_کان_وڌ_عدد)
	  len = i;
	وإلا إذا (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_عدد))
	  {
	    vals_منزل_ignore = i;
	    أرجع;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	بنانشان صحيح max_len = 131072 - offsetof (بنية وڻ_string, str) - 1;
	بنانشان صحيح orig_len = len;
	بنانشان صحيح off = 0, آخري = 0;
	إذا (!wi::neg_p (wi::منزل_wide (val)) && wi::منزل_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	حرف *buf2 = XNEWVEC (حرف, len + off);
	إذا (off)
	  buf2[0] = (حرف) وڻ_منزل_uhwi (val);
	يادگيري_نقل (buf2 + off, buf1, i);
	لكل (بنانشان صحيح j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	لكل (; i < len; ++i)
	  {
	    إذا (!c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	      اكسر;
	    tok = c_parser_peek_2nd_token (parser);
	    إذا (tok->type != CPP_عدد
		|| وڻ_ڪوڊ (tok->قدر) != INTEGER_CST
		|| وڻ_TYPE (tok->قدر) != integer_type_ڳنڍ
		|| wi::neg_p (wi::منزل_wide (tok->قدر))
		|| wi::منزل_widest (tok->قدر) > UCHAR_MAX)
	      اكسر;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    إذا (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      اكسر;
	    buf2[i + off] = (حرف) وڻ_منزل_uhwi (tok->قدر);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    إذا (orig_len == وڌ_کان_وڌ_عدد
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_عدد)))
	      {
		آخري = 1;
		اكسر;
	      }
	    آخري_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_ڳنڍ (RAW_معلومات_CST);
	وڻ_TYPE (val) = integer_type_ڳنڍ;
	RAW_معلومات_ڊيگهائي (val) = i;
	وڻ owner = build_string (i + off + آخري, buf2);
	XDELETEVEC (buf2);
	وڻ_TYPE (owner) = build_array_type_nelts (unsigned_char_type_ڳنڍ,
						    i + off + آخري);
	RAW_معلومات_OWNER (val) = owner;
	RAW_معلومات_اشارو (val) = وڻ_STRING_اشارو (owner) + off;
	init.قدر = val;
	سيٽ_c_اظهار_ذريعو_range (&init, loc, آخري_loc);
	init.original_ڪوڊ = RAW_معلومات_CST;
	init.original_type = integer_type_ڳنڍ;
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

ساكن وڻ
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  وڻ stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (سچ);
      c_پڇاڙي_compound_stmt (brace_loc, stmt, سچ);
      أرجع error_mark_ڳنڍ;
    }
  stmt = c_begin_compound_stmt (سچ);
  location_t پڇاڙي_loc = c_parser_compound_statement_nostart (parser);
  إذا (endlocp)
    *endlocp = پڇاڙي_loc;

  أرجع c_پڇاڙي_compound_stmt (brace_loc, stmt, سچ);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

ساكن فراغ
check_omp_intervening_ڪوڊ (c_parser *parser)
{
  بنية omp_for_parse_معلومات *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  إذا (!omp_for_parse_state->اندريون_intervening_ڪوڊ)
    أرجع;
  omp_for_parse_state->saw_intervening_ڪوڊ = سچ;

  /* Only diagnose errors related to perfect nesting once.  */
  إذا (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      إذا (omp_for_parse_state->ڪوڊ == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = سچ;
	}
      وإلا إذا (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = سچ;
	}
      وإلا إذا (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = سچ;
	}
      وإلا إذا (omp_for_parse_state->ڪوڊ == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = سچ;
	}
      إذا (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = سچ;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
ساكن فراغ
جوڙيو_structured_بلاڪ_stmt (وڻ sl)
{
  إذا (وڻ_ڪوڊ (sl) != STATEMENT_LIST
      || !tsi_پڇاڙي_p (tsi_شروعات (sl)))
    جوڙيو_stmt (build1 (OMP_STRUCTURED_بلاڪ, void_type_ڳنڍ, sl));
}

بنية c_omp_attribute_معلومات
{
  vec<c_token, va_gc> *ٽوڪن;
  ثابت c_omp_directive *dir;
  c_omp_directive_قسم قسم;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

ساكن منطقي
c_parser_handle_statement_omp_خاصيتون (c_parser *parser, وڻ &attrs,
					  منطقي *have_std_attrs)
{
  إذا (!flag_openmp && !flag_openmp_simd)
    أرجع خطأ;

  auto_vec<c_omp_attribute_معلومات, 16> vd;
  صحيح cnt = 0;
  صحيح ٽوڪن = 0;
  منطقي bad = خطأ;
  لكل (وڻ *pa = &attrs; *pa; )
    إذا (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	لكل (وڻ a = وڻ_قدر (*pa); a; a = وڻ_CHAIN (a))
	  {
	    وڻ d = وڻ_قدر (a);
	    gcc_assert (وڻ_ڪوڊ (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_ٽوڪن (d);
	    c_token *پهريون = toks->پتو ();
	    c_token *آخري = پهريون + toks->ڊيگهائي ();
	    إذا (parser->omp_attrs_forbidden_p)
	      {
		error_at (پهريون->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = خطأ;
		bad = سچ;
	      }
	    وإلا إذا (وڻ_عوامي (d))
	      {
		error_at (پهريون->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = سچ;
	      }
	    ثابت حرف *directive[3] = {};
	    لكل (صحيح i = 0; i < 3; i++)
	      {
		وڻ id = NULL_وڻ;
		إذا (پهريون + i == آخري)
		  اكسر;
		إذا (پهريون[i].type == CPP_NAME)
		  id = پهريون[i].قدر;
		وإلا إذا (پهريون[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحيح) پهريون[i].keyword];
		وإلا
		  اكسر;
		directive[i] = IDENTIFIER_اشارو (id);
	      }
	    ثابت c_omp_directive *dir = عدم;
	    إذا (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    إذا (dir == عدم)
	      {
		error_at (پهريون->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  وڻ_عوامي (d) ? "omp::decl" : "omp::directive");
		استمر;
	      }
	    c_omp_directive_قسم قسم = dir->قسم;
	    إذا (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		إذا (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  قسم = C_OMP_DIR_STANDALONE;
		وإلا إذا (پهريون + 2 < آخري
			 && پهريون[1].type == CPP_COMMA
			 && پهريون[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_اشارو (پهريون[2].قدر),
				     "depend") == 0
			     || strcmp (IDENTIFIER_اشارو (پهريون[2].قدر),
					"doacross") == 0))
		  قسم = C_OMP_DIR_STANDALONE;
	      }
	    وإلا إذا (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		صحيح paren_اونهائي = 0;
		لكل (صحيح i = 1; پهريون + i < آخري; i++)
		  إذا (پهريون[i].type == CPP_OPEN_PAREN)
		    paren_اونهائي++;
		  وإلا إذا (پهريون[i].type == CPP_CLOSE_PAREN)
		    paren_اونهائي--;
		  وإلا إذا (paren_اونهائي == 0
			   && پهريون + i + 2 < آخري
			   && پهريون[i].type == CPP_NAME
			   && پهريون[i + 1].type == CPP_OPEN_PAREN
			   && پهريون[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_اشارو (پهريون[i].قدر),
				       "at")
			   && !strcmp (IDENTIFIER_اشارو (پهريون[i
								 + 2].قدر),
				       "execution"))
		    {
		      قسم = C_OMP_DIR_STANDALONE;
		      اكسر;
		    }
	      }
	    c_omp_attribute_معلومات v = { toks, dir, قسم };
	    vd.محفوظ_ڌڪو (v);
	    إذا (flag_openmp || dir->simd)
	      ٽوڪن += (آخري - پهريون) + 1;
	  }
	c_omp_attribute_معلومات v = {};
	vd.محفوظ_ڌڪو (v);
	*pa = وڻ_CHAIN (*pa);
      }
    وإلا
      pa = &وڻ_CHAIN (*pa);

  إذا (bad)
    {
    fail:
      إذا (have_std_attrs && attrs == عدم)
	*have_std_attrs = خطأ;
      أرجع خطأ;
    }

  بنانشان صحيح i;
  c_omp_attribute_معلومات *v;
  c_omp_attribute_معلومات *construct_ڏٺل = خالي_اشارو;
  c_omp_attribute_معلومات *standalone_ڏٺل = خالي_اشارو;
  c_omp_attribute_معلومات *prev_standalone_ڏٺل = خالي_اشارو;
  FOR_EACH_VEC_ELT (vd, i, v)
    إذا (v->ٽوڪن)
      {
	إذا (v->قسم == C_OMP_DIR_CONSTRUCT && !construct_ڏٺل)
	  construct_ڏٺل = v;
	وإلا إذا (v->قسم == C_OMP_DIR_STANDALONE && !standalone_ڏٺل)
	  standalone_ڏٺل = v;
      }
    وإلا
      {
	إذا (standalone_ڏٺل && !prev_standalone_ڏٺل)
	  {
	    prev_standalone_ڏٺل = standalone_ڏٺل;
	    standalone_ڏٺل = خالي_اشارو;
	  }
      }

  إذا (cnt > 1 && construct_ڏٺل)
    {
      error_at ((*construct_ڏٺل->ٽوڪن)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      اذهب fail;
    }
  إذا (cnt > 1 && standalone_ڏٺل && prev_standalone_ڏٺل)
    {
      error_at ((*standalone_ڏٺل->ٽوڪن)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      اذهب fail;
    }

  إذا (prev_standalone_ڏٺل)
    standalone_ڏٺل = prev_standalone_ڏٺل;
  إذا (standalone_ڏٺل
      && !c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_ڏٺل->ٽوڪن->پتو ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      اذهب fail;
    }
  إذا (cnt && c_parser_ايندڙ_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      تعداد pragma_قسم قسم = token->pragma_قسم;
      إذا (قسم >= PRAGMA_OMP_شروعات && قسم <= PRAGMA_OMP_آخري)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  اذهب fail;
	}
    }

  إذا (!ٽوڪن)
    أرجع خطأ;

  بنانشان صحيح ٽوڪن_avail = parser->ٽوڪن_avail;

  ٽوڪن++;
  vec<c_token, va_gc> *toks = عدم;
  vec_محفوظ_reserve (toks, ٽوڪن, سچ);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      إذا (!v->ٽوڪن)
	استمر;
      إذا (!flag_openmp && !v->dir->simd)
	استمر;
      c_token *پهريون = v->ٽوڪن->پتو ();
      c_token *آخري = پهريون + v->ٽوڪن->ڊيگهائي ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_قسم = pragma_قسم (v->dir->id);
      tok.location = پهريون->location;
      toks->تيز_ڌڪو (tok);
      طالما (++پهريون < آخري)
	toks->تيز_ڌڪو (*پهريون);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = آخري[-1].location;
      toks->تيز_ڌڪو (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->آخري ().location;
  toks->تيز_ڌڪو (tok);

  gcc_assert (!parser->اندريون_omp_attribute_pragma);
  parser->اندريون_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->اندريون_omp_attribute_pragma->token_vec = toks;
  parser->اندريون_omp_attribute_pragma->save_ٽوڪن = parser->ٽوڪن;
  parser->اندريون_omp_attribute_pragma->save_ٽوڪن_avail = ٽوڪن_avail;
  parser->ٽوڪن = toks->پتو ();
  parser->ٽوڪن_avail = ٽوڪن;
  أرجع سچ;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

ساكن فراغ
c_parser_handle_directive_omp_خاصيتون (وڻ &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  إذا (!flag_openmp && !flag_openmp_simd)
    أرجع;

  لكل (وڻ *pa = &attrs; *pa; )
    إذا (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	صحيح cnt = 0;
	لكل (وڻ *pa2 = &وڻ_قدر (*pa); *pa2; )
	  {
	    وڻ a = *pa2;
	    وڻ d = وڻ_قدر (a);
	    gcc_assert (وڻ_ڪوڊ (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_ٽوڪن (d);
	    c_token *پهريون = toks->پتو ();
	    c_token *آخري = پهريون + toks->ڊيگهائي ();
	    ثابت حرف *directive[3] = {};
	    لكل (صحيح i = 0; i < 3; i++)
	      {
		وڻ id = NULL_وڻ;
		إذا (پهريون + i == آخري)
		  اكسر;
		إذا (پهريون[i].type == CPP_NAME)
		  id = پهريون[i].قدر;
		وإلا إذا (پهريون[i].type == CPP_KEYWORD)
		  id = ridpointers[(صحيح) پهريون[i].keyword];
		وإلا
		  اكسر;
		directive[i] = IDENTIFIER_اشارو (id);
	      }
	    ثابت c_omp_directive *dir = عدم;
	    إذا (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    إذا (dir == عدم)
	      {
		error_at (پهريون->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  وڻ_عوامي (d) ? "omp::decl" : "omp::directive");
		*pa2 = وڻ_CHAIN (a);
	      }
	    وإلا إذا (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		إذا (pragma_clauses)
		  {
		    error_at (پهريون->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    لكل (pa = &attrs; *pa; )
		      إذا (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = وڻ_CHAIN (*pa);
		      وإلا
			pa = &وڻ_CHAIN (*pa);
		    أرجع;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->ڊيگهائي ()
				       + toks->ڊيگهائي () + 2);
		لكل (++پهريون; پهريون < آخري; ++پهريون)
		  attr_clauses->تيز_ڌڪو (*پهريون);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = آخري[-1].location;
		attr_clauses->تيز_ڌڪو (tok);
		*pa2 = وڻ_CHAIN (a);
	      }
	    وإلا
	      pa2 = &وڻ_CHAIN (a);
	  }
	إذا (cnt && وڻ_قدر (*pa) == NULL_وڻ)
	  *pa = وڻ_CHAIN (*pa);
	وإلا
	  pa = &وڻ_CHAIN (*pa);
      }
    وإلا
      pa = &وڻ_CHAIN (*pa);
  إذا (attr_clauses->ڊيگهائي ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->آخري ().location;
      attr_clauses->تيز_ڌڪو (tok);
      attr_clauses->تيز_ڌڪو (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

ساكن وڻ
c_parser_handle_musttail (c_parser *parser, وڻ std_attrs, attr_state &attr)
{
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_RETURN))
    {
      إذا (وڻ a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  لكل (; a; a = lookup_attribute ("gnu", "musttail", وڻ_CHAIN (a)))
	    إذا (وڻ_قدر (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = سچ;
	}
      إذا (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = سچ;
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

ساكن وڻ
get_before_labels ()
{
  إذا (!building_stmt_list_p ())
    أرجع NULL_وڻ;
  وڻ_stmt_iterator tsi = tsi_آخري (cur_stmt_list);
  إذا (tsi_پڇاڙي_p (tsi))
    أرجع NULL_وڻ;
  أرجع tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

ساكن location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  منطقي آخري_stmt = خطأ;
  منطقي آخري_label = خطأ;
  منطقي save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  بنية omp_for_parse_معلومات *omp_for_parse_state
    = parser->omp_for_parse_state;
  منطقي اندريون_omp_loop_بلاڪ
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : خطأ;
  وڻ sl = NULL_وڻ;
  attr_state astate = {};

  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      جوڙيو_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      أرجع endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  إذا (اندريون_omp_loop_بلاڪ)
    sl = ڌڪو_stmt_list ();

  mark_valid_location_for_stdc_pragma (سچ);
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (خطأ);
      إذا (اندريون_omp_loop_بلاڪ)
	check_omp_intervening_ڪوڊ (parser);
      طالما (c_parser_ايندڙ_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  طالما (سچ)
	    {
	      وڻ label;
	      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  اكسر;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->قدر);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      جوڙيو_stmt (build_stmt (label_loc, DECL_اظهار, label));
	      c_parser_consume_token (parser);
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      وإلا
		اكسر;
	    }
	  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      أرجع endloc;
    }
  وڻ before_labels = get_before_labels ();
  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_نقطو_location_if_اندريون_system_سرو (loc);

      منطقي want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : خطأ);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      إذا (اندريون_omp_loop_بلاڪ && !آخري_label)
	{
	  وڻ_ڪوڊ_2 ڪوڊ = omp_for_parse_state->ڪوڊ;
	  إذا (want_nested_loop
	      && c_parser_omp_ايندڙ_ٽوڪن_can_be_canon_loop (parser, ڪوڊ,
							     خطأ))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      جوڙيو_structured_بلاڪ_stmt (ڪڍو_stmt_list (sl));
	      omp_for_parse_state->اونهائي++;
	      جوڙيو_stmt (c_parser_omp_loop_nest (parser, عدم));
	      omp_for_parse_state->اونهائي--;
	      sl = ڌڪو_stmt_list ();
	      parser->error = خطأ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      استمر;
	    }
	  وإلا إذا (want_nested_loop
		   && c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      وڻ pre_sl = ڪڍو_stmt_list (sl);
	      وڻ nested_sl = ڌڪو_stmt_list ();
	      mark_valid_location_for_stdc_pragma (خطأ);
	      c_parser_statement_after_labels (parser, عدم, NULL_وڻ);
	      nested_sl = ڪڍو_stmt_list (nested_sl);
	      إذا (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_ڪوڊ (parser);
		  sl = ڌڪو_stmt_list ();
		  جوڙيو_stmt (pre_sl);
		  جوڙيو_stmt (nested_sl);
		}
	      وإلا
		{
		  /* It contains the nested loop.  */
		  جوڙيو_structured_بلاڪ_stmt (pre_sl);
		  جوڙيو_stmt (nested_sl);
		  sl = ڌڪو_stmt_list ();
		}
	      parser->error = خطأ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      استمر;
	    }
	  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
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
	= c_parser_nth_token_starts_std_خاصيتون (parser, 1);
      وڻ std_attrs = NULL_وڻ;
      إذا (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_CASE)
	  || c_parser_ايندڙ_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  وإلا
	    label_loc = c_parser_peek_token (parser)->location;
	  آخري_label = سچ;
	  آخري_stmt = خطأ;
	  mark_valid_location_for_stdc_pragma (خطأ);
	  إذا (اندريون_omp_loop_بلاڪ)
	    check_omp_intervening_ڪوڊ (parser);
	  c_parser_label (parser, std_attrs);
	}
      وإلا إذا (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_خاصيتون
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = سچ)))
	{
	  إذا (آخري_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  إذا (اندريون_omp_loop_بلاڪ)
	    {
	      check_omp_intervening_ڪوڊ (parser);
	      omp_for_parse_state->want_nested_loop = خطأ;
	    }
	  mark_valid_location_for_stdc_pragma (خطأ);
	  منطقي fallthru_attr_p = خطأ;
	  c_parser_declaration_or_fndef (parser, سچ, !have_std_attrs,
					 سچ, سچ, سچ, خطأ, عدم,
					 عدم, have_std_attrs, std_attrs,
					 عدم, &fallthru_attr_p);

	  إذا (اندريون_omp_loop_بلاڪ)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  إذا (آخري_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  آخري_stmt = fallthru_attr_p;
	  آخري_label = خطأ;
	  before_labels = get_before_labels ();
	}
      وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_EXTENSION))
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
	      && (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_خاصيتون (parser, 2)))
	    {
	      صحيح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      آخري_label = خطأ;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      إذا (اندريون_omp_loop_بلاڪ)
		{
		  check_omp_intervening_ڪوڊ (parser);
		  omp_for_parse_state->want_nested_loop = خطأ;
		}
	      mark_valid_location_for_stdc_pragma (خطأ);
	      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ,
					     سچ, خطأ);
	      إذا (اندريون_omp_loop_بلاڪ)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      إذا (آخري_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      آخري_stmt = خطأ;
	      before_labels = get_before_labels ();
	    }
	  وإلا
	    اذهب statement;
	}
      وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA))
	{
	  إذا (have_std_attrs && !parser->اندريون_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  وإلا إذا (std_attrs)
	    c_warn_اڻ_استعمال_ٿيل_خاصيتون (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  إذا (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = خطأ;
	  إذا (c_parser_pragma (parser,
			       آخري_label ? pragma_stmt : pragma_compound,
			       عدم, before_labels))
	    {
	      آخري_label = خطأ;
	      آخري_stmt = سچ;
	      إذا (omp_for_parse_state)
		check_omp_intervening_ڪوڊ (parser);
	    }
	  إذا (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  أرجع c_parser_peek_token (parser)->location;
	}
      وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ELSE))
        {
          إذا (parser->اندريون_if_بلاڪ)
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
	  c_warn_اڻ_استعمال_ٿيل_خاصيتون (std_attrs);
	  آخري_label = خطأ;
	  آخري_stmt = سچ;
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
	      check_omp_intervening_ڪوڊ (parser);
	      c_parser_statement_after_labels (parser, عدم, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = خطأ;
      astate.reset ();
    }
  إذا (آخري_label)
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
      sl = ڪڍو_stmt_list (sl);
      إذا (omp_for_parse_state->want_nested_loop)
	جوڙيو_stmt (sl);
      وإلا
	جوڙيو_structured_بلاڪ_stmt (sl);
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
  وڻ std_attrs = عدم;
  إذا ((have_std_attrs = c_parser_nth_token_starts_std_خاصيتون (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  طالما (c_parser_ايندڙ_token_is_keyword (parser, RID_CASE)
	 || c_parser_ايندڙ_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = عدم;
      إذا ((have_std_attrs = c_parser_nth_token_starts_std_خاصيتون (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  إذا (std_attrs
      && (!c_parser_handle_statement_omp_خاصيتون (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      إذا (have_std_attrs && c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_اڻ_استعمال_ٿيل_خاصيتون (std_attrs);
    }
  وإلا إذا (have_std_attrs && c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  أرجع attr;
}


/* Information used while parsing an OpenMP metadirective.  */
بنية omp_metadirective_parse_معلومات {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<وڻ> * GTY((skip)) body_labels;
  بنانشان صحيح region_انگ;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
ساكن وڻ
mangle_metadirective_region_label (c_parser *parser, وڻ name)
{
  إذا (parser->omp_metadirective_state->body_labels->شامل_آهي (name))
    {
      ثابت حرف *old_name = IDENTIFIER_اشارو (name);
      حرف *new_name = (حرف *) XALLOCAVEC (حرف, لڙي_ڊيگهه (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_انگ);
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
c_parser_label (c_parser *parser, وڻ std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  وڻ label = NULL_وڻ;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  منطقي fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_CASE))
    {
      وڻ exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_منزل_rvalue (loc1,
				       c_parser_اظهار_no_commas (parser, عدم),
				       سچ, سچ).قدر;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_وڻ, std_attrs);
	}
      وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_منزل_rvalue (loc1,
					   c_parser_اظهار_no_commas (parser,
								    عدم),
					   سچ, سچ).قدر;
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      وإلا
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_وڻ, NULL_وڻ, std_attrs);
    }
  وإلا
    {
      وڻ name = c_parser_peek_token (parser)->قدر;
      وڻ tlab;
      وڻ attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_خاصيتون (parser);
      إذا (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      إذا (tlab)
	{
	  decl_خاصيتون (&tlab, attrs, 0);
	  decl_خاصيتون (&tlab, std_attrs, 0);
	  label = جوڙيو_stmt (build_stmt (loc1, LABEL_اظهار, tlab));
	}
      إذا (attrs
	  && c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  إذا (label)
    {
      إذا (وڻ_ڪوڊ (label) == LABEL_اظهار)
	FALLTHROUGH_LABEL_P (LABEL_اظهار_LABEL (label)) = fallthrough_p;
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
  وڻ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  إذا (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = خطأ;
  c_parser_statement_after_labels (parser, if_p, before_labels, عدم, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

ساكن وڻ
c_parser_bc_name (c_parser *parser, منطقي is_break)
{
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
    أرجع NULL_وڻ;

  c_token *tok = c_parser_peek_token (parser);
  وڻ label = c_پڄاڻي_bc_name (tok->location, tok->قدر, is_break);
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
				 وڻ before_labels,
				 vec<وڻ> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ stmt = NULL_وڻ;
  منطقي اندريون_if_بلاڪ = parser->اندريون_if_بلاڪ;
  parser->اندريون_if_بلاڪ = خطأ;
  إذا (if_p != عدم)
    *if_p = خطأ;

  إذا (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    جوڙيو_debug_begin_stmt (loc);

 restart:
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_OPEN_BRACE:
      جوڙيو_stmt (c_parser_compound_statement (parser));
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
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	    {
	      وڻ name = c_parser_peek_token (parser)->قدر;
	      إذا (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_پڄاڻي_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_MULT))
	    {
	      بنية c_اظهار val;

	      c_parser_consume_token (parser);
	      val = c_parser_اظهار (parser);
	      val = convert_lvalue_منزل_rvalue (loc, val, خطأ, سچ);
	      stmt = c_پڄاڻي_goto_ptr (loc, val);
	    }
	  وإلا
	    c_parser_error (parser, "expected identifier or %<*%>");
	  اذهب expect_semicolon;
	حالة RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_پڄاڻي_bc_stmt (loc, objc_foreach_continue_label, خطأ,
				   c_parser_bc_name (parser, خطأ));
	  اذهب expect_semicolon;
	حالة RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_پڄاڻي_bc_stmt (loc, objc_foreach_break_label, سچ,
				   c_parser_bc_name (parser, سچ));
	  اذهب expect_semicolon;
	حالة RID_RETURN:
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_پڄاڻي_return (loc, NULL_وڻ, NULL_وڻ,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      بنية c_اظهار اظهار = c_parser_اظهار_conv (parser);
	      mark_exp_read (اظهار.قدر);
	      stmt = c_پڄاڻي_return (اظهار_LOC_OR_LOC (اظهار.قدر, xloc),
				      اظهار.قدر, اظهار.original_type,
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
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_وڻ);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    {
	      بنية c_اظهار اظهار = c_parser_اظهار (parser);
	      اظهار = convert_lvalue_منزل_rvalue (loc, اظهار, خطأ, خطأ);
	      اظهار.قدر = c_fully_fold (اظهار.قدر, خطأ, عدم);
	      stmt = objc_build_throw_stmt (loc, اظهار.قدر);
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
	    وڻ attrs = c_parser_gnu_خاصيتون (parser);
	    منطقي has_assume = lookup_attribute ("assume", attrs);
	    إذا (has_assume)
	      {
		إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, سچ);
		وإلا
		  {
		    auto_urlify_خاصيتون sentinel;
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
		    auto_urlify_خاصيتون sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		اذهب restart;
	      }
	    إذا (attribute_fallthrough_p (attrs))
	      {
		إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
		  {
		    وڻ fn = build_call_اظهار_اندروني_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_ڳنڍ, 0);
		    جوڙيو_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		وإلا
		  {
		    auto_urlify_خاصيتون sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    وإلا إذا (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    وإلا إذا (attrs != NULL_وڻ)
	      {
		auto_urlify_خاصيتون sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    اكسر;
	  }
	افتراضي:
	  اذهب اظهار_stmt;
	}
      اكسر;
    حالة CPP_SEMICOLON:
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CLOSE_PAREN:
    حالة CPP_CLOSE_چورس:
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
    اظهار_stmt:
      stmt = c_پڄاڻي_اظهار_stmt (loc, c_parser_اظهار_conv (parser).قدر);
    expect_semicolon:
      c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
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
  إذا (اظهار_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_سيٽ_اظهار_location (stmt, loc);

  parser->اندريون_if_بلاڪ = اندريون_if_بلاڪ;
}

/* Parse the condition from an if, do, while or for statements.  */

ساكن وڻ
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ cond;
  cond = c_parser_اظهار_conv (parser).قدر;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, خطأ, عدم);
  إذا (warn_sequence_نقطو)
    verify_sequence_points (cond);
  أرجع cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

ساكن وڻ
c_parser_paren_condition (c_parser *parser)
{
  وڻ cond;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_ڳنڍ;
  cond = c_parser_condition (parser);
  parens.skip_until_مليو_close (parser);
  أرجع cond;
}

/* Parse a selection-header:

   selection-header:
اظهار
     declaration expression
     simple-declaration

   simple-declaration:
     attribute-specifier-sequence[opt] declaration-specifiers declarator
       = initializer

  SWITCH_P is true if we are called from c_parser_switch_statement; in
  that case, don't perform the truthvalue conversion.  */

ساكن c_اظهار
c_parser_selection_سرو (c_parser *parser, منطقي switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_اظهار اظهار;
  منطقي parse_اظهار = سچ;
  وڻ std_attrs;
  منطقي have_std_attrs = c_parser_nth_token_starts_std_خاصيتون (parser, 1);
  إذا (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  وإلا
    std_attrs = NULL_وڻ;
  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      اظهار.قدر
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/خطأ,
					 /*static_assert_ok=*/خطأ,
					 /*empty_ok=*/خطأ,
					 /*nested=*/سچ,
					 /*start_attr_ok=*/سچ,
					 /*simple_ok=*/سچ,
					 /*objc_foreach_object_decl=*/خالي_اشارو,
					 /*omp_declare_simd_clauses=*/خالي_اشارو,
					 have_std_attrs,
					 std_attrs);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      وإلا
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  إذا (!اظهار.قدر)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      اظهار.original_type = error_mark_ڳنڍ;
	      اظهار.سيٽ_error ();
	      أرجع اظهار;
	    }
	  parse_اظهار = خطأ;
	}
      إذا (اظهار.قدر)
	{
	  اظهار.original_type = وڻ_TYPE (اظهار.قدر);
	  اظهار = convert_lvalue_منزل_rvalue (loc, اظهار, /*convert_p=*/سچ,
					   /*read_p=*/سچ);
	}
    }
  وإلا إذا (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      اظهار.original_type = error_mark_ڳنڍ;
      اظهار.سيٽ_error ();
      أرجع اظهار;
    }

  إذا (parse_اظهار)
    اظهار = c_parser_اظهار_conv (parser);
  إذا (!switch_p)
    {
      اظهار.قدر = c_objc_common_truthvalue_conversion (loc, اظهار.قدر);
      اظهار.قدر = c_fully_fold (اظهار.قدر, خطأ, عدم);
      إذا (warn_sequence_نقطو)
	verify_sequence_points (اظهار.قدر);
    }
  أرجع اظهار;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

ساكن وڻ
c_parser_paren_selection_سرو (c_parser *parser)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_ڳنڍ;
  وڻ cond = c_parser_selection_سرو (parser, /*switch_p=*/خطأ).قدر;
  parens.skip_until_مليو_close (parser);
  أرجع cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ساكن وڻ
c_parser_c99_بلاڪ_statement (c_parser *parser, منطقي *if_p,
			      location_t *loc_after_labels)
{
  وڻ بلاڪ = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  أرجع c_پڇاڙي_compound_stmt (loc, بلاڪ, flag_isoc99);
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

ساكن وڻ
c_parser_if_body (c_parser *parser, منطقي *if_p,
		  ثابت token_indent_info &if_tinfo)
{
  وڻ بلاڪ = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  وڻ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      جوڙيو_stmt (build_خالي_جايون_stmt (loc));
      c_parser_consume_token (parser);
      إذا (!c_parser_ايندڙ_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    جوڙيو_stmt (c_parser_compound_statement (parser));
  وإلا
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, عدم, a);
    }

  token_indent_info ايندڙ_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, ايندڙ_tinfo);
  إذا (body_loc_after_labels != UNKNOWN_LOCATION
      && ايندڙ_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, ايندڙ_tinfo.location,
				    if_tinfo.location, RID_IF);

  أرجع c_پڇاڙي_compound_stmt (body_loc, بلاڪ, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

ساكن وڻ
c_parser_else_body (c_parser *parser, ثابت token_indent_info &else_tinfo,
		    vec<وڻ> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  وڻ بلاڪ = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  وڻ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      جوڙيو_stmt (build_خالي_جايون_stmt (loc));
      c_parser_consume_token (parser);
    }
  وإلا
    {
      إذا (!c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, عدم, before_labels, chain, a);
    }

  token_indent_info ايندڙ_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, ايندڙ_tinfo);
  إذا (body_loc_after_labels != UNKNOWN_LOCATION
      && ايندڙ_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, ايندڙ_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  أرجع c_پڇاڙي_compound_stmt (body_loc, بلاڪ, flag_isoc99);
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
c_parser_if_statement (c_parser *parser, منطقي *if_p, vec<وڻ> *chain)
{
  وڻ بلاڪ;
  location_t loc;
  وڻ cond;
  منطقي nested_if = خطأ;
  وڻ پهريون_body, ٻيو_body;
  منطقي اندريون_if_بلاڪ;

  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  بلاڪ = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_سرو (parser);
  اندريون_if_بلاڪ = parser->اندريون_if_بلاڪ;
  parser->اندريون_if_بلاڪ = سچ;
  پهريون_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->اندريون_if_بلاڪ = اندريون_if_بلاڪ;

  إذا (warn_duplicated_cond)
    warn_duplicated_cond_جوڙيو_or_warn (اظهار_LOCATION (cond), cond, &chain);

  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      إذا (warn_duplicated_cond)
	{
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_IF)
	      && chain == عدم)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = جديد vec<وڻ> ();
	      إذا (!CONSTANT_CLASS_P (cond) && !وڻ_SIDE_EFFECTS (cond))
		chain->محفوظ_ڌڪو (cond);
	    }
	  وإلا إذا (!c_parser_ايندڙ_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      ٻيو_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      إذا (if_p != عدم)
	*if_p = سچ;
    }
  وإلا
    {
      ٻيو_body = NULL_وڻ;

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
  c_پڄاڻي_if_stmt (loc, cond, پهريون_body, ٻيو_body);
  جوڙيو_stmt (c_پڇاڙي_compound_stmt (loc, بلاڪ, flag_isoc99));

  c_parser_maybe_reclassify_token (parser);
}

/* Parse a switch statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   switch-statement:
     switch (expression) statement

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_switch_statement (c_parser *parser, منطقي *if_p, وڻ before_labels)
{
  بنية c_اظهار ce;
  وڻ بلاڪ, اظهار, body;
  بنانشان حرف save_اندريون_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  وڻ switch_name;
  صحيح انگ_نالا = c_get_loop_نالا (before_labels, سچ, &switch_name);
  بلاڪ = c_begin_compound_stmt (flag_isoc99);
  منطقي explicit_cast_p = خطأ;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = سچ;
      ce = c_parser_selection_سرو (parser, /*switch_p=*/سچ);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_منزل_rvalue (switch_cond_loc, ce, سچ, سچ);
      اظهار = ce.قدر;
      /* ??? expr has no valid location?  */
      parens.skip_until_مليو_close (parser);
    }
  وإلا
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      اظهار = error_mark_ڳنڍ;
      ce.original_type = error_mark_ڳنڍ;
    }
  وڻ stmt
    = c_شروعات_switch (switch_loc, switch_cond_loc, اظهار, explicit_cast_p,
		      switch_name);
  save_اندريون_statement = اندريون_statement;
  اندريون_statement |= اندريون_SWITCH_STMT;
  إذا (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      اندريون_statement |= اندريون_NAMED_STMT;
    }
  وإلا
    اندريون_statement &= ~اندريون_NAMED_STMT;
  location_t loc_after_labels;
  منطقي open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_بلاڪ_statement (parser, if_p, &loc_after_labels);
  location_t ايندڙ_loc = c_parser_peek_token (parser)->location;
  إذا (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, ايندڙ_loc, switch_loc,
				    RID_SWITCH);
  c_پڄاڻي_switch (body, ce.original_type);
  اندريون_statement = save_اندريون_statement;
  إذا (انگ_نالا)
    {
      إذا (!C_DECL_LOOP_SWITCH_NAME_استعمال_ٿيل (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_وڻ;
      وإلا
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_نالا (انگ_نالا);
    }
  جوڙيو_stmt (c_پڇاڙي_compound_stmt (switch_loc, بلاڪ, flag_isoc99));
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
c_parser_while_statement (c_parser *parser, منطقي ivdep, بنانشان ننڍو unroll,
			  منطقي novector, منطقي *if_p, وڻ before_labels)
{
  وڻ بلاڪ, cond, body;
  بنانشان حرف save_اندريون_statement;
  location_t loc;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  وڻ loop_name;
  صحيح انگ_نالا = c_get_loop_نالا (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = سچ;
    }

  c_parser_consume_token (parser);
  بلاڪ = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  إذا (ivdep && cond != error_mark_ڳنڍ)
    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
		   build_int_cst (integer_type_ڳنڍ,
				  annot_اظهار_ivdep_قسم),
		   integer_zero_ڳنڍ);
  إذا (unroll && cond != error_mark_ڳنڍ)
    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
		   build_int_cst (integer_type_ڳنڍ,
				  annot_اظهار_unroll_قسم),
		   build_int_cst (integer_type_ڳنڍ, unroll));
  إذا (novector && cond != error_mark_ڳنڍ)
    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
		   build_int_cst (integer_type_ڳنڍ,
				  annot_اظهار_no_ويڪٽر_قسم),
		   integer_zero_ڳنڍ);
  save_اندريون_statement = اندريون_statement;
  اندريون_statement = اندريون_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      اندريون_statement |= اندريون_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقي open_brace = c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_بلاڪ_statement (parser, if_p, &loc_after_labels);
  إذا (loop_name && !C_DECL_LOOP_SWITCH_NAME_استعمال_ٿيل (loop_name))
    loop_name = NULL_وڻ;
  جوڙيو_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_وڻ,
			NULL_وڻ));
  جوڙيو_stmt (c_پڇاڙي_compound_stmt (loc, بلاڪ, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  إذا (انگ_نالا)
    c_release_loop_نالا (انگ_نالا);

  token_indent_info ايندڙ_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, ايندڙ_tinfo);

  إذا (ايندڙ_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, ايندڙ_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  اندريون_statement = save_اندريون_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ساكن فراغ
c_parser_do_statement (c_parser *parser, منطقي ivdep, بنانشان ننڍو unroll,
		       منطقي novector, وڻ before_labels)
{
  وڻ بلاڪ, cond, body;
  بنانشان حرف save_اندريون_statement;
  location_t loc;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_DO));
  وڻ loop_name;
  صحيح انگ_نالا = c_get_loop_نالا (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = سچ;
    }

  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  بلاڪ = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_اندريون_statement = اندريون_statement;
  اندريون_statement = اندريون_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      اندريون_statement |= اندريون_NAMED_STMT;
    }
  body = c_parser_c99_بلاڪ_statement (parser, عدم);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  اندريون_statement = save_اندريون_statement;
  إذا (انگ_نالا)
    {
      إذا (!C_DECL_LOOP_SWITCH_NAME_استعمال_ٿيل (loop_name))
	loop_name = NULL_وڻ;
      c_release_loop_نالا (انگ_نالا);
    }
  cond = c_parser_paren_condition (parser);
  إذا (ivdep && cond != error_mark_ڳنڍ)
    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
		   build_int_cst (integer_type_ڳنڍ,
				  annot_اظهار_ivdep_قسم),
		   integer_zero_ڳنڍ);
  إذا (unroll && cond != error_mark_ڳنڍ)
    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
		   build_int_cst (integer_type_ڳنڍ,
				  annot_اظهار_unroll_قسم),
 		   build_int_cst (integer_type_ڳنڍ, unroll));
  إذا (novector && cond != error_mark_ڳنڍ)
    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
		   build_int_cst (integer_type_ڳنڍ,
				  annot_اظهار_no_ويڪٽر_قسم),
		   integer_zero_ڳنڍ);
  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);

  جوڙيو_stmt (build_stmt (loc, DO_STMT, cond, body, loop_name));
  جوڙيو_stmt (c_پڇاڙي_compound_stmt (loc, بلاڪ, flag_isoc99));
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
c_parser_for_statement (c_parser *parser, منطقي ivdep, بنانشان ننڍو unroll,
			منطقي novector, منطقي *if_p, وڻ before_labels)
{
  وڻ بلاڪ, cond, incr, body;
  بنانشان حرف save_اندريون_statement;
  وڻ save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  وڻ object_اظهار;
  /* Silence the bogus uninitialized warning.  */
  وڻ collection_اظهار = عدم;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  منطقي is_foreach_statement = خطأ;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  وڻ loop_name;
  صحيح انگ_نالا = c_get_loop_نالا (before_labels, خطأ, &loop_name);

  إذا (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = سچ;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  بلاڪ = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_ڳنڍ;
  incr = error_mark_ڳنڍ;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_اظهار = error_mark_ڳنڍ;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = خطأ;
	  c_parser_consume_token (parser);
	  c_پڄاڻي_اظهار_stmt (loc, NULL_وڻ);
	}
      وإلا إذا (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser)
	       || c_parser_nth_token_starts_std_خاصيتون (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ, سچ,
					 خطأ, &object_اظهار);
	  parser->objc_could_be_foreach_context = خطأ;

	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_اندريون))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = سچ;
	      إذا (check_for_loop_decls (for_loc, سچ) == NULL_وڻ)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  وإلا
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  طالما (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_خاصيتون (parser, 2))
	    {
	      صحيح ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ,
					     سچ, خطأ, &object_اظهار);
	      parser->objc_could_be_foreach_context = خطأ;

	      restore_extension_diagnostics (ext);
	      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_اندريون))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = سچ;
		  إذا (check_for_loop_decls (for_loc, سچ) == NULL_وڻ)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      وإلا
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  وإلا
	    اذهب init_اظهار;
	}
      وإلا
	{
	init_اظهار:
	  {
	    بنية c_اظهار ce;
	    وڻ init_اظهار_2;
	    ce = c_parser_اظهار (parser);
	    init_اظهار_2 = ce.قدر;
	    parser->objc_could_be_foreach_context = خطأ;
	    إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_اندريون))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = سچ;
		إذا (! lvalue_p (init_اظهار_2))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_اظهار
		  = c_fully_fold (init_اظهار_2, خطأ, عدم);
	      }
	    وإلا
	      {
		ce = convert_lvalue_منزل_rvalue (loc, ce, سچ, خطأ);
		init_اظهار_2 = ce.قدر;
		c_پڄاڻي_اظهار_stmt (loc, init_اظهار_2);
		c_parser_skip_until_مليو (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      إذا (!is_foreach_statement)
	{
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	    {
	      إذا (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_ڳنڍ;
		}
	      وإلا إذا (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_ڳنڍ;
		}
	      وإلا
		{
		  c_parser_consume_token (parser);
		  cond = NULL_وڻ;
		}
	    }
	  وإلا
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_مليو (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  إذا (ivdep && cond != error_mark_ڳنڍ)
	    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
			   build_int_cst (integer_type_ڳنڍ,
					  annot_اظهار_ivdep_قسم),
			   integer_zero_ڳنڍ);
	  إذا (unroll && cond != error_mark_ڳنڍ)
	    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
 			   build_int_cst (integer_type_ڳنڍ,
					  annot_اظهار_unroll_قسم),
			   build_int_cst (integer_type_ڳنڍ, unroll));
	  إذا (novector && cond && cond != error_mark_ڳنڍ)
	    cond = build3 (ANNOTATE_اظهار, وڻ_TYPE (cond), cond,
			   build_int_cst (integer_type_ڳنڍ,
					  annot_اظهار_no_ويڪٽر_قسم),
			   integer_zero_ڳنڍ);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  إذا (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_اظهار = error_mark_ڳنڍ;
	    }
	  وإلا
	    incr = c_process_اظهار_stmt (loc, NULL_وڻ);
	}
      وإلا
	{
	  إذا (is_foreach_statement)
	    collection_اظهار
	      = c_fully_fold (c_parser_اظهار (parser).قدر, خطأ, عدم);
	  وإلا
	    {
	      بنية c_اظهار ce = c_parser_اظهار (parser);
	      ce = convert_lvalue_منزل_rvalue (loc, ce, سچ, خطأ);
	      incr = c_process_اظهار_stmt (loc, ce.قدر);
	    }
	}
      parens.skip_until_مليو_close (parser);
    }
  save_اندريون_statement = اندريون_statement;
  إذا (is_foreach_statement)
    {
      اندريون_statement = اندريون_OBJC_FOREACH;
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
    اندريون_statement = اندريون_ITERATION_STMT;
  إذا (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      اندريون_statement |= اندريون_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  منطقي open_brace = c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_بلاڪ_statement (parser, if_p, &loc_after_labels);

  إذا (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_وڻ;
      DECL_CHAIN (objc_foreach_break_label) = NULL_وڻ;
    }

  إذا (is_foreach_statement)
    objc_پڄاڻي_foreach_loop (for_loc, object_اظهار,
			      collection_اظهار, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  وإلا
    جوڙيو_stmt (build_stmt (for_loc, FOR_STMT, NULL_وڻ, cond, incr,
			  body, NULL_وڻ,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_استعمال_ٿيل (loop_name)
			  ? loop_name : NULL_وڻ, NULL_وڻ, NULL_وڻ));
  جوڙيو_stmt (c_پڇاڙي_compound_stmt (for_loc, بلاڪ,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info ايندڙ_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, ايندڙ_tinfo);

  إذا (ايندڙ_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, ايندڙ_tinfo.location,
				    for_tinfo.location, RID_FOR);

  اندريون_statement = save_اندريون_statement;
  إذا (انگ_نالا)
    c_release_loop_نالا (انگ_نالا);
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

ساكن وڻ
c_parser_asm_statement (c_parser *parser)
{
  وڻ str, outputs, inputs, clobbers, labels, ret;
  منطقي simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  صحيح section, nsections;

  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_ASM));
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
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->قدر);
	      inform (volatile_loc, "first seen here");
	    }
	  وإلا
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_INLINE:
	  إذا (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->قدر);
	      inform (inline_loc, "first seen here");
	    }
	  وإلا
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_GOTO:
	  إذا (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->قدر);
	      inform (goto_loc, "first seen here");
	    }
	  وإلا
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  استمر;

	حالة RID_CONST:
	حالة RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->قدر);
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
  إذا (str == NULL_وڻ)
    اذهب error_close_paren;

  simple = سچ;
  outputs = NULL_وڻ;
  inputs = NULL_وڻ;
  clobbers = NULL_وڻ;
  labels = NULL_وڻ;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    اذهب پورو_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  لكل (section = 0; section < nsections; ++section)
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_SCOPE))
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

      إذا ((!c_parser_ايندڙ_token_is (parser, CPP_COLON)
	   && !c_parser_ايندڙ_token_is (parser, CPP_SCOPE)
	   && !c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
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

      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	اذهب پورو_asm;
    }

 پورو_asm:
  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
      اذهب error;
    }

  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_اظهار (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  أرجع ret;

 error_close_paren:
  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
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

ساكن وڻ
c_parser_asm_operands (c_parser *parser)
{
  وڻ list = NULL_وڻ;
  طالما (سچ)
    {
      وڻ name, str;
      بنية c_اظهار اظهار;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_چورس))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	    {
	      وڻ id = c_parser_peek_token (parser)->قدر;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_ڊيگهائي (id),
				   IDENTIFIER_اشارو (id));
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس, عدم);
	      أرجع NULL_وڻ;
	    }
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس,
				     "expected %<]%>");
	}
      وإلا
	name = NULL_وڻ;
      str = c_parser_asm_string_literal (parser);
      إذا (str == NULL_وڻ)
	أرجع NULL_وڻ;
      matching_parens parens;
      إذا (!parens.require_open (parser))
	أرجع NULL_وڻ;
      اظهار = c_parser_اظهار (parser);
      mark_exp_read (اظهار.قدر);
      إذا (!parens.require_close (parser))
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع NULL_وڻ;
	}
      list = chainon (list, build_وڻ_list (build_وڻ_list (name, str),
					     اظهار.قدر));
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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

ساكن وڻ
c_parser_asm_clobbers (c_parser *parser)
{
  وڻ list = NULL_وڻ;
  طالما (سچ)
    {
      وڻ str = c_parser_asm_string_literal (parser);
      إذا (str)
	list = وڻ_cons (NULL_وڻ, str, list);
      وإلا
	أرجع NULL_وڻ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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

ساكن وڻ
c_parser_asm_goto_operands (c_parser *parser)
{
  وڻ list = NULL_وڻ;
  طالما (سچ)
    {
      وڻ name, label;

      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->قدر;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  وڻ_استعمال_ٿيل (label) = 1;
	}
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع NULL_وڻ;
	}

      name = build_string (IDENTIFIER_ڊيگهائي (name),
			   IDENTIFIER_اشارو (name));
      list = وڻ_cons (name, label, list);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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

بنية c_اظهار
c_parser_string_literal (c_parser *parser, منطقي translate, منطقي wide_ok)
{
  بنية c_اظهار ret;
  سائيز_t ڳڻپ;
  بنية obstack str_ob;
  بنية obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, آخري_tok_loc;
  تعداد cpp_ttype type;
  وڻ قدر, string_وڻ;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  آخري_tok_loc = linemap_resolve_location (سٽ_جدول, loc,
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
      string_وڻ = tok->قدر;
      اكسر;

    افتراضي:
      c_parser_error (parser, "expected string literal");
      ret.سيٽ_error ();
      ret.قدر = NULL_وڻ;
      ret.original_ڪوڊ = ERROR_MARK;
      ret.original_type = NULL_وڻ;
      أرجع ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  بدل (c_parser_peek_2nd_token (parser)->type)
    {
    افتراضي:
      c_parser_consume_token (parser);
      str.متن = (ثابت بنانشان حرف *) وڻ_STRING_اشارو (string_وڻ);
      str.len = وڻ_STRING_ڊيگهائي (string_وڻ);
      ڳڻپ = 1;
      strs = &str;
      اكسر;

    حالة CPP_STRING:
    حالة CPP_WSTRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      ڳڻپ = 0;
      افعل
	{
	  c_parser_consume_token (parser);
	  ڳڻپ++;
	  str.متن = (ثابت بنانشان حرف *) وڻ_STRING_اشارو (string_وڻ);
	  str.len = وڻ_STRING_ڊيگهائي (string_وڻ);
	  إذا (type != tok->type)
	    {
	      إذا (type == CPP_STRING)
		type = tok->type;
	      وإلا إذا (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, حجم (cpp_string));
	  obstack_grow (&loc_ob, &آخري_tok_loc, حجم (location_t));
	  tok = c_parser_peek_token (parser);
	  string_وڻ = tok->قدر;
	  آخري_tok_loc
	    = linemap_resolve_location (سٽ_جدول, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, عدم);
	}
      طالما (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_پڄاڻي (&str_ob);
    }

  إذا (ڳڻپ > 1 && !اندريون_system_سرو_at (داخلا_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  إذا ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_اندريون, strs, ڳڻپ, &istr, type)))
    {
      قدر = build_string (istr.len, (ثابت حرف *) istr.متن);
      حرر (const_cast<بنانشان حرف *> (istr.متن));
      إذا (ڳڻپ > 1)
	{
	  location_t *locs = (location_t *) obstack_پڄاڻي (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->رڪارڊ_string_concatenation (ڳڻپ, locs);
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
	      قدر = build_string (TYPE_PRECISION (char8_type_ڳنڍ)
				    / TYPE_PRECISION (char_type_ڳنڍ),
				    "");  /* char8_t is 8 bits */
	    }
	  وإلا
	    قدر = build_string (1, "");
	  اكسر;
	حالة CPP_STRING16:
	  قدر = build_string (TYPE_PRECISION (char16_type_ڳنڍ)
				/ TYPE_PRECISION (char_type_ڳنڍ),
				"\0");  /* char16_t is 16 bits */
	  اكسر;
	حالة CPP_STRING32:
	  قدر = build_string (TYPE_PRECISION (char32_type_ڳنڍ)
				/ TYPE_PRECISION (char_type_ڳنڍ),
				"\0\0\0");  /* char32_t is 32 bits */
	  اكسر;
	حالة CPP_WSTRING:
	  قدر = build_string (TYPE_PRECISION (wchar_type_ڳنڍ)
				/ TYPE_PRECISION (char_type_ڳنڍ),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  اكسر;
        }
    }

  بدل (type)
    {
    افتراضي:
    حالة CPP_STRING:
      وڻ_TYPE (قدر) = char_array_type_ڳنڍ;
      اكسر;
    حالة CPP_UTF8STRING:
      إذا (flag_char8_t)
	وڻ_TYPE (قدر) = char8_array_type_ڳنڍ;
      وإلا
	وڻ_TYPE (قدر) = char_array_type_ڳنڍ;
      اكسر;
    حالة CPP_STRING16:
      وڻ_TYPE (قدر) = char16_array_type_ڳنڍ;
      اكسر;
    حالة CPP_STRING32:
      وڻ_TYPE (قدر) = char32_array_type_ڳنڍ;
      اكسر;
    حالة CPP_WSTRING:
      وڻ_TYPE (قدر) = wchar_array_type_ڳنڍ;
    }
  قدر = fix_string_type (قدر);

  إذا (ڳڻپ > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.قدر = قدر;
  ret.original_ڪوڊ = STRING_CST;
  ret.original_type = NULL_وڻ;
  سيٽ_c_اظهار_ذريعو_range (&ret, get_range_from_loc (سٽ_جدول, loc));
  ret.m_decimal = 0;
  parser->ڏٺل_string_literal = سچ;
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

ساكن بنية c_اظهار
c_parser_اظهار_no_commas (c_parser *parser, بنية c_اظهار *after,
			 وڻ omp_atomic_lhs)
{
  بنية c_اظهار lhs, rhs, ret;
  تعداد وڻ_ڪوڊ_2 ڪوڊ;
  location_t op_location, exp_location;
  منطقي save_اندريون_omp_for = c_اندريون_omp_for;
  c_اندريون_omp_for = خطأ;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_اظهار (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_EQ:
      ڪوڊ = NOP_اظهار;
      اكسر;
    حالة CPP_MULT_EQ:
      ڪوڊ = MULT_اظهار;
      اكسر;
    حالة CPP_DIV_EQ:
      ڪوڊ = TRUNC_DIV_اظهار;
      اكسر;
    حالة CPP_MOD_EQ:
      ڪوڊ = TRUNC_MOD_اظهار;
      اكسر;
    حالة CPP_PLUS_EQ:
      ڪوڊ = PLUS_اظهار;
      اكسر;
    حالة CPP_MINUS_EQ:
      ڪوڊ = MINUS_اظهار;
      اكسر;
    حالة CPP_LSHIFT_EQ:
      ڪوڊ = LSHIFT_اظهار;
      اكسر;
    حالة CPP_RSHIFT_EQ:
      ڪوڊ = RSHIFT_اظهار;
      اكسر;
    حالة CPP_AND_EQ:
      ڪوڊ = ٻٽو_انگ_AND_اظهار;
      اكسر;
    حالة CPP_XOR_EQ:
      ڪوڊ = ٻٽو_انگ_XOR_اظهار;
      اكسر;
    حالة CPP_OR_EQ:
      ڪوڊ = ٻٽو_انگ_IOR_اظهار;
      اكسر;
    افتراضي:
      c_اندريون_omp_for = save_اندريون_omp_for;
      أرجع lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_اظهار_no_commas (parser, عدم);
  rhs = convert_lvalue_منزل_rvalue (exp_location, rhs, سچ, سچ);

  ret.قدر = build_modify_اظهار (op_location, lhs.قدر, lhs.original_type,
				 ڪوڊ, exp_location, rhs.قدر,
				 rhs.original_type);
  ret.m_decimal = 0;
  سيٽ_c_اظهار_ذريعو_range (&ret, lhs.get_شروعات (), rhs.get_پڄاڻي ());
  إذا (ڪوڊ == NOP_اظهار)
    ret.original_ڪوڊ = MODIFY_اظهار;
  وإلا
    {
      suppress_warning (ret.قدر, OPT_Wparentheses);
      ret.original_ڪوڊ = ERROR_MARK;
    }
  ret.original_type = عدم;
  c_اندريون_omp_for = save_اندريون_omp_for;
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

ساكن بنية c_اظهار
c_parser_conditional_اظهار (c_parser *parser, بنية c_اظهار *after,
				 وڻ omp_atomic_lhs)
{
  بنية c_اظهار cond, exp1, exp2, ret;
  location_t شروعات, cond_loc, colon_loc;
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_ٻٽو_اظهار (parser, after, omp_atomic_lhs);

  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_QUERY))
    أرجع cond;
  c_omp_array_section_p = خطأ;
  إذا (cond.قدر != error_mark_ڳنڍ)
    شروعات = cond.get_شروعات ();
  وإلا
    شروعات = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_منزل_rvalue (cond_loc, cond, سچ, سچ);
  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
    {
      وڻ eptype = NULL_وڻ;

      location_t وچ_loc = c_parser_peek_token (parser)->location;
      pedwarn (وچ_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      إذا (وڻ_ڪوڊ (cond.قدر) == EXCESS_PRECISION_اظهار)
	{
	  eptype = وڻ_TYPE (cond.قدر);
	  cond.قدر = وڻ_عمليو (cond.قدر, 0);
	}
      وڻ e = cond.قدر;
      طالما (وڻ_ڪوڊ (e) == COMPOUND_اظهار)
	e = وڻ_عمليو (e, 1);
      warn_for_omitted_condop (وچ_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.قدر = save_اظهار (default_conversion (cond.قدر));
      إذا (eptype)
	exp1.قدر = build1 (EXCESS_PRECISION_اظهار, eptype, exp1.قدر);
      exp1.original_type = عدم;
      exp1.src_range = cond.src_range;
      cond.قدر = c_objc_common_truthvalue_conversion (cond_loc, exp1.قدر);
      c_inhibit_evaluation_warnings += cond.قدر == truthvalue_true_ڳنڍ;
    }
  وإلا
    {
      cond.قدر
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.قدر));
      c_inhibit_evaluation_warnings += cond.قدر == truthvalue_false_ڳنڍ;
      exp1 = c_parser_اظهار_conv (parser);
      mark_exp_read (exp1.قدر);
      c_inhibit_evaluation_warnings +=
	((cond.قدر == truthvalue_true_ڳنڍ)
	 - (cond.قدر == truthvalue_false_ڳنڍ));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.قدر == truthvalue_true_ڳنڍ;
      ret.سيٽ_error ();
      ret.original_ڪوڊ = ERROR_MARK;
      ret.original_type = عدم;
      c_omp_array_section_p = save_c_omp_array_section_p;
      أرجع ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_اظهار (parser, عدم, NULL_وڻ);
    exp2 = convert_lvalue_منزل_rvalue (exp2_loc, exp2, سچ, سچ);
  }
  c_inhibit_evaluation_warnings -= cond.قدر == truthvalue_true_ڳنڍ;
  location_t loc1 = make_location (exp1.get_شروعات (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_شروعات (), exp2.src_range);
  إذا (UNLIKELY (omp_atomic_lhs != عدم)
      && (وڻ_ڪوڊ (cond.قدر) == GT_اظهار
	  || وڻ_ڪوڊ (cond.قدر) == LT_اظهار
	  || وڻ_ڪوڊ (cond.قدر) == EQ_اظهار)
      && c_وڻ_equal (exp2.قدر, omp_atomic_lhs)
      && (c_وڻ_equal (وڻ_عمليو (cond.قدر, 0), omp_atomic_lhs)
	  || c_وڻ_equal (وڻ_عمليو (cond.قدر, 1), omp_atomic_lhs)))
    ret.قدر = build3_loc (colon_loc, COND_اظهار, وڻ_TYPE (omp_atomic_lhs),
			    cond.قدر, exp1.قدر, exp2.قدر);
  وإلا
    ret.قدر
      = build_conditional_اظهار (colon_loc, cond.قدر,
				cond.original_ڪوڊ == C_MAYBE_CONST_اظهار,
				exp1.قدر, exp1.original_type, loc1,
				exp2.قدر, exp2.original_type, loc2);
  ret.original_ڪوڊ = ERROR_MARK;
  إذا (exp1.قدر == error_mark_ڳنڍ || exp2.قدر == error_mark_ڳنڍ)
    ret.original_type = عدم;
  وإلا
    {
      وڻ t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : وڻ_TYPE (exp1.قدر);
      t2 = exp2.original_type ? exp2.original_type : وڻ_TYPE (exp2.قدر);
      ret.original_type = ((t1 != error_mark_ڳنڍ
			    && t2 != error_mark_ڳنڍ
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : عدم);
    }
  سيٽ_c_اظهار_ذريعو_range (&ret, شروعات, exp2.get_پڄاڻي ());
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

ساكن بنية c_اظهار
c_parser_ٻٽو_اظهار (c_parser *parser, بنية c_اظهار *after,
			    وڻ omp_atomic_lhs)
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
    بنية c_اظهار اظهار;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    تعداد c_parser_prec prec;
    /* The operation on its left.  */
    تعداد وڻ_ڪوڊ_2 op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    وڻ sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    وڻ orig_اظهار;
  } ڍير[انگ_PRECS];
  صحيح sp;
  /* Location of the binary operator.  */
  location_t ٻٽو_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#وصف_ڪريو ڪڍو_2								      \
  افعل {									      \
    بدل (ڍير[sp].op)						      \
      {									      \
      حالة TRUTH_ANDIF_اظهار:						      \
	c_inhibit_evaluation_warnings -= (ڍير[sp - 1].اظهار.قدر	      \
					  == truthvalue_false_ڳنڍ);	      \
	اكسر;								      \
      حالة TRUTH_ORIF_اظهار:						      \
	c_inhibit_evaluation_warnings -= (ڍير[sp - 1].اظهار.قدر	      \
					  == truthvalue_true_ڳنڍ);	      \
	اكسر;								      \
      حالة TRUNC_DIV_اظهار:						      \
	إذا ((ڍير[sp - 1].اظهار.original_ڪوڊ == SIZEOF_اظهار		      \
	     || ڍير[sp - 1].اظهار.original_ڪوڊ == PAREN_SIZEOF_اظهار)	      \
	    && (ڍير[sp].اظهار.original_ڪوڊ == SIZEOF_اظهار		      \
		|| ڍير[sp].اظهار.original_ڪوڊ == PAREN_SIZEOF_اظهار))	      \
	  {								      \
	    وڻ type0 = ڍير[sp - 1].sizeof_arg;			      \
	    وڻ type1 = ڍير[sp].sizeof_arg;				      \
	    وڻ پهريون_arg = type0;					      \
	    إذا (!TYPE_P (type0))					      \
	      type0 = وڻ_TYPE (type0);				      \
	    إذا (!TYPE_P (type1))					      \
	      type1 = وڻ_TYPE (type1);				      \
	    إذا (اشارو_TYPE_P (type0)					      \
		&& comptypes (وڻ_TYPE (type0), type1)			      \
		&& !(وڻ_ڪوڊ (پهريون_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (پهريون_arg)			      \
		     && warn_sizeof_array_دليل))			      \
	      {								      \
		auto_diagnostic_گروهه d;				      \
		إذا (warning_at (ڍير[sp].loc, OPT_Wsizeof_اشارو_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  إذا (DECL_P (پهريون_arg))				      \
		    inform (DECL_ذريعو_LOCATION (پهريون_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    وإلا إذا (وڻ_ڪوڊ (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (وڻ_TYPE (type0)))  \
		     && ڍير[sp].اظهار.original_ڪوڊ != PAREN_SIZEOF_اظهار)    \
	      maybe_warn_sizeof_array_div (ڍير[sp].loc, پهريون_arg, type0,   \
					   ڍير[sp].sizeof_arg, type1);      \
	  }								      \
	اكسر;								      \
      افتراضي:								      \
	اكسر;								      \
      }									      \
    ڍير[sp - 1].اظهار							      \
      = convert_lvalue_منزل_rvalue (ڍير[sp - 1].loc,			      \
				  ڍير[sp - 1].اظهار, سچ, سچ);	      \
    ڍير[sp].اظهار							      \
      = convert_lvalue_منزل_rvalue (ڍير[sp].loc,			      \
				  ڍير[sp].اظهار, سچ, سچ);		      \
    إذا (UNLIKELY (omp_atomic_lhs != NULL_وڻ) && sp == 1		      \
	&& ((c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << ڍير[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_سرڪايو)		      \
		     | (1 << PREC_جوڙيو) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_ايندڙ_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_ڳنڍ			      \
		     && c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (ڍير[sp].prec == PREC_REL || ڍير[sp].prec == PREC_EQ)))\
	&& ڍير[sp].op != TRUNC_MOD_اظهار				      \
	&& ڍير[sp].op != GE_اظهار					      \
	&& ڍير[sp].op != LE_اظهار					      \
	&& ڍير[sp].op != NE_اظهار					      \
	&& ڍير[0].اظهار.قدر != error_mark_ڳنڍ			      \
	&& ڍير[1].اظهار.قدر != error_mark_ڳنڍ			      \
	&& (omp_atomic_lhs == void_list_ڳنڍ				      \
	    || c_وڻ_equal (ڍير[0].اظهار.قدر, omp_atomic_lhs)	      \
	    || c_وڻ_equal (ڍير[1].اظهار.قدر, omp_atomic_lhs)	      \
	    || (ڍير[sp].op == EQ_اظهار					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	وڻ t = make_ڳنڍ (ڍير[1].op);				      \
	وڻ_TYPE (t) = وڻ_TYPE (ڍير[0].اظهار.قدر);		      \
	وڻ_عمليو (t, 0) = ڍير[0].اظهار.قدر;			      \
	وڻ_عمليو (t, 1) = ڍير[1].اظهار.قدر;			      \
	ڍير[0].اظهار.قدر = t;					      \
	ڍير[0].اظهار.m_decimal = 0;					      \
      }									      \
    وإلا								      \
      ڍير[sp - 1].اظهار = parser_build_ٻٽو_op (ڍير[sp].loc,	      \
						   ڍير[sp].op,	      \
						   ڍير[sp - 1].اظهار,	      \
						   ڍير[sp].اظهار,	      \
						   ڍير[sp - 1].orig_اظهار);  \
    ڍير[sp - 1].orig_اظهار = NULL_وڻ;				      \
    sp--;								      \
  } طالما (0)
  gcc_assert (!after || c_dialect_objc ());
  ڍير[0].loc = c_parser_peek_token (parser)->location;
  ڍير[0].اظهار = c_parser_cast_اظهار (parser, after);
  ڍير[0].prec = PREC_NONE;
  ڍير[0].sizeof_arg = c_آخري_sizeof_arg;
  ڍير[0].orig_اظهار = NULL_وڻ;
  sp = 0;
  طالما (سچ)
    {
      تعداد c_parser_prec oprec;
      تعداد وڻ_ڪوڊ_2 ocode;
      ذريعو_range src_range;
      إذا (parser->error)
	اذهب ٻاهريون;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_اظهار;
	  اكسر;
	حالة CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_اظهار;
	  اكسر;
	حالة CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_اظهار;
	  اكسر;
	حالة CPP_PLUS:
	  oprec = PREC_جوڙيو;
	  ocode = PLUS_اظهار;
	  اكسر;
	حالة CPP_MINUS:
	  oprec = PREC_جوڙيو;
	  ocode = MINUS_اظهار;
	  اكسر;
	حالة CPP_LSHIFT:
	  oprec = PREC_سرڪايو;
	  ocode = LSHIFT_اظهار;
	  اكسر;
	حالة CPP_RSHIFT:
	  oprec = PREC_سرڪايو;
	  ocode = RSHIFT_اظهار;
	  اكسر;
	حالة CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_اظهار;
	  اكسر;
	حالة CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_اظهار;
	  اكسر;
	حالة CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_اظهار;
	  اكسر;
	حالة CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_اظهار;
	  اكسر;
	حالة CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_اظهار;
	  اكسر;
	حالة CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_اظهار;
	  اكسر;
	حالة CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = ٻٽو_انگ_AND_اظهار;
	  اكسر;
	حالة CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = ٻٽو_انگ_XOR_اظهار;
	  اكسر;
	حالة CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = ٻٽو_انگ_IOR_اظهار;
	  اكسر;
	حالة CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_اظهار;
	  اكسر;
	حالة CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_اظهار;
	  اكسر;
	افتراضي:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  اذهب ٻاهريون;
	}
      ٻٽو_loc = c_parser_peek_token (parser)->location;
      طالما (oprec <= ڍير[sp].prec)
	ڪڍو_2;
      c_parser_consume_token (parser);
      بدل (ocode)
	{
	حالة TRUTH_ANDIF_اظهار:
	  src_range = ڍير[sp].اظهار.src_range;
	  ڍير[sp].اظهار
	    = convert_lvalue_منزل_rvalue (ڍير[sp].loc,
					ڍير[sp].اظهار, سچ, سچ);
	  ڍير[sp].orig_اظهار = ڍير[sp].اظهار.قدر;
	  ڍير[sp].اظهار.قدر = c_objc_common_truthvalue_conversion
	    (ڍير[sp].loc, default_conversion (ڍير[sp].اظهار.قدر));
	  c_inhibit_evaluation_warnings += (ڍير[sp].اظهار.قدر
					    == truthvalue_false_ڳنڍ);
	  سيٽ_c_اظهار_ذريعو_range (&ڍير[sp].اظهار, src_range);
	  اكسر;
	حالة TRUTH_ORIF_اظهار:
	  src_range = ڍير[sp].اظهار.src_range;
	  ڍير[sp].اظهار
	    = convert_lvalue_منزل_rvalue (ڍير[sp].loc,
					ڍير[sp].اظهار, سچ, سچ);
	  ڍير[sp].orig_اظهار = ڍير[sp].اظهار.قدر;
	  ڍير[sp].اظهار.قدر = c_objc_common_truthvalue_conversion
	    (ڍير[sp].loc, default_conversion (ڍير[sp].اظهار.قدر));
	  c_inhibit_evaluation_warnings += (ڍير[sp].اظهار.قدر
					    == truthvalue_true_ڳنڍ);
	  سيٽ_c_اظهار_ذريعو_range (&ڍير[sp].اظهار, src_range);
	  اكسر;
	افتراضي:
	  اكسر;
	}
      sp++;
      ڍير[sp].loc = ٻٽو_loc;
      ڍير[sp].اظهار = c_parser_cast_اظهار (parser, عدم);
      ڍير[sp].prec = oprec;
      ڍير[sp].op = ocode;
      ڍير[sp].sizeof_arg = c_آخري_sizeof_arg;
      ڍير[sp].orig_اظهار = NULL_وڻ;
    }
 ٻاهريون:
  طالما (sp > 0)
    ڪڍو_2;
  أرجع ڍير[0].اظهار;
#وصف_رد ڪڍو_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

ساكن بنية c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  منطقي ڏٺل_scspec = خطأ;
  بنية c_declspecs *specs = build_null_declspecs ();
  طالما (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD))
    {
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CONSTEXPR:
	حالة RID_رجسٽر:
	حالة RID_STATIC:
	حالة RID_THREAD:
	  ڏٺل_scspec = سچ;
	  declspecs_جوڙيو_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->قدر);
	  c_parser_consume_token (parser);
	  اكسر;
	افتراضي:
	  اذهب ٻاهريون;
	}
    }
 ٻاهريون:
  أرجع ڏٺل_scspec ? specs : عدم;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

ساكن بنية c_اظهار
c_parser_cast_اظهار (c_parser *parser, بنية c_اظهار *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  إذا (after)
    أرجع c_parser_postfix_اظهار_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      بنية c_اظهار ret;
      بنية c_اظهار اظهار;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, سچ);
      parens.skip_until_مليو_close (parser);
      إذا (type_name == عدم)
	{
	  ret.سيٽ_error ();
	  ret.original_ڪوڊ = ERROR_MARK;
	  ret.original_type = عدم;
	  أرجع ret;
	}

      /* Save casted types in the function's used types hash table.  */
      استعمال_ٿيل_types_وجهو (type_name->specs->type);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
	أرجع c_parser_postfix_اظهار_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      إذا (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t اظهار_loc = c_parser_peek_token (parser)->location;
	اظهار = c_parser_cast_اظهار (parser, عدم);
	اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, سچ, سچ);
      }
      ret.قدر = c_cast_اظهار (cast_loc, type_name, اظهار.قدر);
      إذا (ret.قدر && اظهار.قدر)
	سيٽ_c_اظهار_ذريعو_range (&ret, cast_loc, اظهار.get_پڄاڻي ());
      ret.original_ڪوڊ = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      أرجع ret;
    }
  وإلا
    أرجع c_parser_unary_اظهار (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

ساكن فراغ
mark_exp_read_cond (وڻ قوت_نما)
{
  إذا ((VAR_P (قوت_نما) || وڻ_ڪوڊ (قوت_نما) == PARM_DECL)
      && (VAR_P (قوت_نما) ? warn_اڻ_استعمال_ٿيل_but_سيٽ_variable
		      : warn_اڻ_استعمال_ٿيل_but_سيٽ_parameter) > 1)
    أرجع;

  mark_exp_read (قوت_نما);
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

ساكن بنية c_اظهار
c_parser_unary_اظهار (c_parser *parser)
{
  صحيح ext;
  بنية c_اظهار ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t پڄاڻي;
  ret.original_ڪوڊ = ERROR_MARK;
  ret.original_type = عدم;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_اظهار (parser, عدم);
      mark_exp_read_cond (op.قدر);
      op = default_function_array_conversion (exp_loc, op);
      أرجع parser_build_unary_op (op_loc, PREINCREMENT_اظهار, op);
    حالة CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_اظهار (parser, عدم);
      mark_exp_read_cond (op.قدر);
      op = default_function_array_conversion (exp_loc, op);
      أرجع parser_build_unary_op (op_loc, PREDECREMENT_اظهار, op);
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_اظهار (parser, عدم);
      mark_exp_read (op.قدر);
      أرجع parser_build_unary_op (op_loc, ADDR_اظهار, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_اظهار (parser, عدم);
	پڄاڻي = op.get_پڄاڻي ();
	op = convert_lvalue_منزل_rvalue (exp_loc, op, سچ, سچ);
	location_t combined_loc = make_location (op_loc, op_loc, پڄاڻي);
	ret.قدر = build_اڻسڌو_ref (combined_loc, op.قدر, RO_UNARY_تارو);
	ret.src_range.m_شروعات = op_loc;
	ret.src_range.m_پڄاڻي = پڄاڻي;
	ret.m_decimal = 0;
	أرجع ret;
      }
    حالة CPP_PLUS:
      إذا (!c_dialect_objc () && !اندريون_system_سرو_at (داخلا_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_اظهار (parser, عدم);
      op = convert_lvalue_منزل_rvalue (exp_loc, op, سچ, سچ);
      أرجع parser_build_unary_op (op_loc, CONVERT_اظهار, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_اظهار (parser, عدم);
      op = convert_lvalue_منزل_rvalue (exp_loc, op, سچ, سچ);
      أرجع parser_build_unary_op (op_loc, NEGATE_اظهار, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_اظهار (parser, عدم);
      op = convert_lvalue_منزل_rvalue (exp_loc, op, سچ, سچ);
      أرجع parser_build_unary_op (op_loc, ٻٽو_انگ_NOT_اظهار, op);
    حالة CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_اظهار (parser, عدم);
      op = convert_lvalue_منزل_rvalue (exp_loc, op, سچ, سچ);
      أرجع parser_build_unary_op (op_loc, TRUTH_NOT_اظهار, op);
    حالة CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  ret.قدر = پڄاڻي_label_پتو_اظهار
	    (c_parser_peek_token (parser)->قدر, op_loc);
	  سيٽ_c_اظهار_ذريعو_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_پڄاڻي ());
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  ret.سيٽ_error ();
	}
      أرجع ret;
    حالة CPP_KEYWORD:
      {
	تعداد rid rid = c_parser_peek_token (parser)->keyword;
	بدل (rid)
	  {
	  حالة RID_COUNTOF:
	  حالة RID_SIZEOF:
	    أرجع c_parser_sizeof_or_countof_اظهار (parser, rid);
	  حالة RID_ALIGNOF:
	    أرجع c_parser_alignof_اظهار (parser);
	  حالة RID_MAXOF:
	  حالة RID_MINOF:
	    أرجع c_parser_maxof_or_minof_اظهار (parser, rid);
	  حالة RID_BUILTIN_HAS_ATTRIBUTE:
	    أرجع c_parser_has_attribute_اظهار (parser);
	  حالة RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_اظهار (parser, عدم);
	    restore_extension_diagnostics (ext);
	    أرجع ret;
	  حالة RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_اظهار (parser, عدم);
	    op = default_function_array_conversion (exp_loc, op);
	    أرجع parser_build_unary_op (op_loc, REALPART_اظهار, op);
	  حالة RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_اظهار (parser, عدم);
	    op = default_function_array_conversion (exp_loc, op);
	    أرجع parser_build_unary_op (op_loc, IMAGPART_اظهار, op);
	  حالة RID_TRANSACTION_ATOMIC:
	  حالة RID_TRANSACTION_RELAXED:
	    أرجع c_parser_transaction_اظهار (parser, rid);
	  حالة RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.قدر = void_ڳنڍ;
	    سيٽ_c_اظهار_ذريعو_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    أرجع ret;
	  افتراضي:
	    أرجع c_parser_postfix_اظهار (parser);
	  }
      }
    افتراضي:
      أرجع c_parser_postfix_اظهار (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

ساكن بنية c_اظهار
c_parser_sizeof_or_countof_اظهار (c_parser *parser, تعداد rid rid)
{
  ثابت حرف *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  بنية c_اظهار اظهار;
  بنية c_اظهار نتيجو;
  location_t اظهار_loc;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, rid));

  location_t شروعات;
  location_t پڄاڻي = UNKNOWN_LOCATION;

  شروعات = c_parser_peek_token (parser)->location;

  إذا (rid == RID_COUNTOF)
    pedwarn_c23 (شروعات, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  إذا (rid == RID_COUNTOF)
    اندريون_countof++;
  وإلا
    اندريون_sizeof++;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      اظهار_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, سچ);
      parens.skip_until_مليو_close (parser);
      پڄاڻي = parser->ٽوڪن_buf[0].location;
      إذا (type_name == عدم)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  اظهار.سيٽ_error ();
	  اذهب Xof_اظهار;
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
	{
	  اظهار = c_parser_postfix_اظهار_after_paren_type (parser, scspecs,
							       type_name,
							       اظهار_loc);
	  پڄاڻي = اظهار.get_پڄاڻي ();
	  اذهب Xof_اظهار;
	}
      /* sizeof ( type-name ).  */
      إذا (scspecs)
	error_at (اظهار_loc, "storage class specifier in %qs", op_name);
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      إذا (rid == RID_COUNTOF)
	{
	  اندريون_countof--;
	  نتيجو = c_اظهار_countof_type (اظهار_loc, type_name);
	}
      وإلا
	{
	  اندريون_sizeof--;
	  نتيجو = c_اظهار_sizeof_type (اظهار_loc, type_name);
	}
    }
  وإلا
    {
      اظهار_loc = c_parser_peek_token (parser)->location;
      اظهار = c_parser_unary_اظهار (parser);
      پڄاڻي = اظهار.get_پڄاڻي ();
    Xof_اظهار:
      c_inhibit_evaluation_warnings--;
      إذا (rid == RID_COUNTOF)
	اندريون_countof--;
      وإلا
	اندريون_sizeof--;
      mark_exp_read (اظهار.قدر);
      إذا (وڻ_ڪوڊ (اظهار.قدر) == COMPONENT_REF
	  && DECL_C_ٻٽو_انگ_ميدان (وڻ_عمليو (اظهار.قدر, 1)))
	error_at (اظهار_loc, "%qs applied to a bit-field", op_name);
      إذا (rid == RID_COUNTOF)
	نتيجو = c_اظهار_countof_اظهار (اظهار_loc, اظهار);
      وإلا
	نتيجو = c_اظهار_sizeof_اظهار (اظهار_loc, اظهار);
    }
  إذا (پڄاڻي == UNKNOWN_LOCATION)
    پڄاڻي = شروعات;
  سيٽ_c_اظهار_ذريعو_range (&نتيجو, شروعات, پڄاڻي);
  أرجع نتيجو;
}

/* Parse an alignof expression.  */

ساكن بنية c_اظهار
c_parser_alignof_اظهار (c_parser *parser)
{
  بنية c_اظهار اظهار;
  location_t شروعات_loc = c_parser_peek_token (parser)->location;
  location_t پڇاڙي_loc;
  وڻ alignof_spelling = c_parser_peek_token (parser)->قدر;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_ALIGNOF));
  منطقي is_c11_alignof = (strcmp (IDENTIFIER_اشارو (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_اشارو (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  إذا (is_c11_alignof)
    {
      إذا (flag_isoc99)
	pedwarn_c99 (شروعات_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      وإلا
	pedwarn_c99 (شروعات_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  اندريون_alignof++;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      بنية c_declspecs *scspecs;
      بنية c_type_name *type_name;
      بنية c_اظهار ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, سچ);
      پڇاڙي_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_مليو_close (parser);
      إذا (type_name == عدم)
	{
	  بنية c_اظهار ret;
	  c_inhibit_evaluation_warnings--;
	  اندريون_alignof--;
	  ret.سيٽ_error ();
	  ret.original_ڪوڊ = ERROR_MARK;
	  ret.original_type = عدم;
	  أرجع ret;
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
	{
	  اظهار = c_parser_postfix_اظهار_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  اذهب alignof_اظهار;
	}
      /* alignof ( type-name ).  */
      إذا (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      إذا (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      اندريون_alignof--;
      ret.قدر = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       عدم, عدم),
					    خطأ, is_c11_alignof, 1);
      ret.original_ڪوڊ = ERROR_MARK;
      ret.original_type = عدم;
      سيٽ_c_اظهار_ذريعو_range (&ret, شروعات_loc, پڇاڙي_loc);
      ret.m_decimal = 0;
      أرجع ret;
    }
  وإلا
    {
      بنية c_اظهار ret;
      اظهار = c_parser_unary_اظهار (parser);
      پڇاڙي_loc = اظهار.src_range.m_پڄاڻي;
    alignof_اظهار:
      mark_exp_read (اظهار.قدر);
      c_inhibit_evaluation_warnings--;
      اندريون_alignof--;
      إذا (is_c11_alignof)
	pedwarn (شروعات_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.قدر = c_alignof_اظهار (شروعات_loc, اظهار.قدر);
      ret.original_ڪوڊ = ERROR_MARK;
      ret.original_type = عدم;
      سيٽ_c_اظهار_ذريعو_range (&ret, شروعات_loc, پڇاڙي_loc);
      ret.m_decimal = 0;
      أرجع ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

ساكن بنية c_اظهار
c_parser_maxof_or_minof_اظهار (c_parser *parser, تعداد rid rid)
{
  ثابت حرف *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  بنية c_اظهار نتيجو;
  location_t اظهار_loc;
  بنية c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, rid));

  location_t شروعات;
  location_t پڄاڻي = UNKNOWN_LOCATION;

  شروعات = c_parser_peek_token (parser)->location;

  pedwarn (شروعات, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      اذهب fail;
    }
  parens.consume_open (parser);
  اظهار_loc = c_parser_peek_token (parser)->location;
  إذا (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (اظهار_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_مليو_close (parser);
      اذهب fail;
    }
  type_name = c_parser_type_name (parser, سچ);
  إذا (type_name == عدم)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_مليو_close (parser);
      اذهب fail;
    }
  parens.skip_until_مليو_close (parser);
  پڄاڻي = parser->ٽوڪن_buf[0].location;
  إذا (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  إذا (rid == RID_MAXOF)
    نتيجو = c_اظهار_maxof_type (اظهار_loc, type_name);
  وإلا
    نتيجو = c_اظهار_minof_type (اظهار_loc, type_name);
  سيٽ_c_اظهار_ذريعو_range (&نتيجو, شروعات, پڄاڻي);
  أرجع نتيجو;
fail:
  c_inhibit_evaluation_warnings--;
  نتيجو.سيٽ_error ();
  نتيجو.original_ڪوڊ = ERROR_MARK;
  نتيجو.original_type = عدم;
  أرجع نتيجو;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

ساكن بنية c_اظهار
c_parser_has_attribute_اظهار (c_parser *parser)
{
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t شروعات = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      اندريون_typeof--;

      بنية c_اظهار نتيجو;
      نتيجو.سيٽ_error ();
      نتيجو.original_ڪوڊ = ERROR_MARK;
      نتيجو.original_type = عدم;
      أرجع نتيجو;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  اندريون_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  وڻ oper = NULL_وڻ;
  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, cla_prefer_id))
    {
      بنية c_type_name *tname = c_parser_type_name (parser);
      اندريون_typeof--;
      إذا (tname)
	{
	  oper = groktypename (tname, عدم, عدم);
	  ڪڍو_maybe_استعمال_ٿيل (c_type_variably_modified_p (oper));
	}
    }
  وإلا
    {
      بنية c_اظهار cexpr = c_parser_اظهار_no_commas (parser, عدم);
      c_inhibit_evaluation_warnings--;
      اندريون_typeof--;
      إذا (cexpr.قدر != error_mark_ڳنڍ)
	{
	  mark_exp_read (cexpr.قدر);
	  oper = cexpr.قدر;
	  وڻ etype = وڻ_TYPE (oper);
	  منطقي was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  إذا (was_vm)
	    oper = c_fully_fold (oper, خطأ, عدم);
	  ڪڍو_maybe_استعمال_ٿيل (was_vm);
	}
    }

  بنية c_اظهار نتيجو;
  نتيجو.original_ڪوڊ = ERROR_MARK;
  نتيجو.original_type = عدم;

  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      نتيجو.سيٽ_error ();
      أرجع نتيجو;
    }

  منطقي save_translate_لڙيون_p = parser->translate_لڙيون_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  وڻ attr = c_parser_gnu_attribute (parser, NULL_وڻ, خطأ, خطأ);

  parser->translate_لڙيون_p = save_translate_لڙيون_p;

  location_t پڄاڻي = c_parser_peek_token (parser)->location;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);

      نتيجو.سيٽ_error ();
      أرجع نتيجو;
    }

  إذا (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      نتيجو.سيٽ_error ();
      أرجع نتيجو;
    }

  نتيجو.original_ڪوڊ = INTEGER_CST;
  نتيجو.original_type = boolean_type_ڳنڍ;

  إذا (has_attribute (atloc, oper, attr, default_conversion))
    نتيجو.قدر = boolean_true_ڳنڍ;
  وإلا
    نتيجو.قدر =  boolean_false_ڳنڍ;

  سيٽ_c_اظهار_ذريعو_range (&نتيجو, شروعات, پڄاڻي);
  نتيجو.m_decimal = 0;
  أرجع نتيجو;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
ساكن منطقي
c_parser_get_builtin_دليلون (c_parser *parser, ثابت حرف *bname,
			   vec<c_اظهار_t, va_gc> **ret_cexpr_list,
			   منطقي چونڊيو_اظهار_p,
			   location_t *ٻاهريون_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_اظهار_t, va_gc> *cexpr_list;
  c_اظهار_t اظهار;
  منطقي saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = عدم;
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      أرجع خطأ;
    }

  c_parser_consume_token (parser);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
    {
      *ٻاهريون_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      أرجع سچ;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= چونڊيو_اظهار_p;
  اظهار = c_parser_اظهار_no_commas (parser, عدم);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_محفوظ_ڌڪو (cexpr_list, اظهار);
  طالما (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  وڻ قدر = embed->قدر;
	  اظهار.original_ڪوڊ = INTEGER_CST;
	  اظهار.original_type = integer_type_ڳنڍ;
	  اظهار.قدر = NULL_وڻ;
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, embed->get_range ());
	  اظهار.m_decimal = 0;
	  لكل (بنانشان صحيح i = 0; i < (بنانشان) RAW_معلومات_ڊيگهائي (قدر); i++)
	    {
	      اظهار.قدر = build_int_cst (integer_type_ڳنڍ,
					  RAW_معلومات_UCHAR_ELT (قدر, i));
	      vec_محفوظ_ڌڪو (cexpr_list, اظهار);
	    }
	  c_parser_consume_token (parser);
	  استمر;
	}
      اظهار = c_parser_اظهار_no_commas (parser, عدم);
      vec_محفوظ_ڌڪو (cexpr_list, اظهار);
    }

  *ٻاهريون_close_paren_loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع خطأ;

  *ret_cexpr_list = cexpr_list;
  أرجع سچ;
}

/* This represents a single generic-association.  */

بنية c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  وڻ type;
  /* The association's expression.  */
  بنية c_اظهار اظهار_2;
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

ساكن بنية c_اظهار
c_parser_generic_selection (c_parser *parser)
{
  بنية c_اظهار selector, error_اظهار;
  وڻ selector_type;
  بنية c_generic_association matched_assoc;
  صحيح ميلاپ_مليو = -1;
  location_t generic_loc, selector_loc;

  error_اظهار.original_ڪوڊ = ERROR_MARK;
  error_اظهار.original_type = عدم;
  error_اظهار.سيٽ_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_وڻ;
  matched_assoc.اظهار_2 = error_اظهار;

  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_GENERIC));
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
    أرجع error_اظهار;

  selector_loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, cla_prefer_id))
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
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_اظهار;
	}
    }
  وإلا
    {
      c_inhibit_evaluation_warnings++;
      اندريون_generic++;
      selector = c_parser_اظهار_no_commas (parser, عدم);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      اندريون_generic--;
      ڪڍو_maybe_استعمال_ٿيل (!flag_isoc23);

      إذا (selector.قدر == error_mark_ڳنڍ)
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع selector;
	}
      mark_exp_read (selector.قدر);
      selector_type = وڻ_TYPE (selector.قدر);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      إذا (وڻ_ڪوڊ (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      إذا (FUNCTION_اشارو_TYPE_P (selector_type)
	  && TYPE_QUALS (وڻ_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_اشارو_type (TYPE_MAIN_VARIANT (وڻ_TYPE (selector_type)));
    }

  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
      أرجع error_اظهار;
    }

  auto_vec<c_generic_association> associations;
  بنية maybe_استعمال_ٿيل_decl *maybe_استعمال_ٿيل_default = عدم;
  طالما (1)
    {
      بنية c_generic_association assoc, *iter;
      بنانشان صحيح ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      إذا (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_وڻ;
	}
      وإلا
	{
	  بنية c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  إذا (type_name == عدم)
	    {
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع error_اظهار;
	    }
	  assoc.type = grokgenassoc (type_name);
	  إذا (assoc.type == error_mark_ڳنڍ)
	    {
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع error_اظهار;
	    }

	  إذا (وڻ_ڪوڊ (assoc.type) == FUNCTION_TYPE)
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
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_اظهار;
	}

      منطقي ميلاپ = assoc.type == NULL_وڻ
		   || comptypes (assoc.type, selector_type);

      إذا (!ميلاپ || matched_assoc.type != NULL_وڻ)
	c_inhibit_evaluation_warnings++;
      اندريون_generic++;

      assoc.اظهار_2 = c_parser_اظهار_no_commas (parser, عدم);

      إذا (!ميلاپ || matched_assoc.type != NULL_وڻ)
	c_inhibit_evaluation_warnings--;
      اندريون_generic--;
      إذا (!ميلاپ)
	ڪڍو_maybe_استعمال_ٿيل (!flag_isoc23);
      وإلا إذا (assoc.type == NULL_وڻ)
	maybe_استعمال_ٿيل_default = save_maybe_استعمال_ٿيل ();
      وإلا
	ڪڍو_maybe_استعمال_ٿيل (سچ);

      إذا (assoc.اظهار_2.قدر == error_mark_ڳنڍ)
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	  أرجع error_اظهار;
	}

      لكل (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  إذا (assoc.type == NULL_وڻ)
	    {
	      إذا (iter->type == NULL_وڻ)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  وإلا إذا (iter->type != NULL_وڻ)
	    {
	      إذا (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      إذا (assoc.type == NULL_وڻ)
	{
	  إذا (ميلاپ_مليو < 0)
	    {
	      matched_assoc = assoc;
	      ميلاپ_مليو = associations.ڊيگهائي ();
	    }
	}
      وإلا إذا (ميلاپ)
	{
	  إذا (ميلاپ_مليو < 0 || matched_assoc.type == NULL_وڻ)
	    {
	      matched_assoc = assoc;
	      ميلاپ_مليو = associations.ڊيگهائي ();
	    }
	  وإلا
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.محفوظ_ڌڪو (assoc);

      إذا (c_parser_peek_token (parser)->type != CPP_COMMA)
	اكسر;
      c_parser_consume_token (parser);
    }

  إذا (ميلاپ_مليو >= 0 && matched_assoc.type == NULL_وڻ)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_استعمال_ٿيل (maybe_استعمال_ٿيل_default);
      ڪڍو_maybe_استعمال_ٿيل (سچ);
    }
  وإلا إذا (maybe_استعمال_ٿيل_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_استعمال_ٿيل (maybe_استعمال_ٿيل_default);
      ڪڍو_maybe_استعمال_ٿيل (!flag_isoc23);
    }

  بنانشان صحيح ix;
  بنية c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    إذا (ix != (بنانشان) ميلاپ_مليو)
      mark_exp_read (iter->اظهار_2.قدر);

  إذا (!parens.require_close (parser))
    {
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
      أرجع error_اظهار;
    }

  إذا (ميلاپ_مليو < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      أرجع error_اظهار;
    }

  أرجع matched_assoc.اظهار_2;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

ساكن بنانشان صحيح
check_tgmath_function (c_اظهار *اظهار, بنانشان صحيح pos)
{
  وڻ type = وڻ_TYPE (اظهار->قدر);
  إذا (!FUNCTION_اشارو_TYPE_P (type))
    {
      error_at (اظهار->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      أرجع 0;
    }
  type = وڻ_TYPE (type);
  إذا (!prototype_p (type))
    {
      error_at (اظهار->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      أرجع 0;
    }
  إذا (stdarg_p (type))
    {
      error_at (اظهار->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      أرجع 0;
    }
  بنانشان صحيح nargs = 0;
  function_دليلون_iterator iter;
  وڻ t;
  FOREACH_FUNCTION_دليلون (type, t, iter)
    {
      إذا (t == void_type_ڳنڍ)
	اكسر;
      nargs++;
    }
  إذا (nargs == 0)
    {
      error_at (اظهار->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      أرجع 0;
    }
  أرجع nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
تعداد tgmath_parm_قسم
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

ساكن بنية c_اظهار
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

  بنية c_اظهار اظهار;
  اظهار.original_ڪوڊ = ERROR_MARK;
  اظهار.original_type = عدم;
  اظهار.قدر = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->قدر);
  سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, loc);
  اظهار.m_decimal = 0;
  c_parser_consume_token (parser);
  أرجع اظهار;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

ساكن منطقي
has_counted_by_object (وڻ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  إذا ((وڻ_ڪوڊ (ref) == اڻسڌو_REF
       && is_access_with_سائيز_p (وڻ_عمليو (ref, 0)))
      || is_access_with_سائيز_p (ref))
    أرجع سچ;
  أرجع خطأ;
}

/* Get the reference to the counted-by object associated with the REF.  */

ساكن وڻ
get_counted_by_ref (وڻ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  إذا (وڻ_ڪوڊ (ref) == اڻسڌو_REF
      && is_access_with_سائيز_p (وڻ_عمليو (ref, 0)))
    أرجع CALL_اظهار_ARG (وڻ_عمليو (ref, 0), 1);
  وإلا إذا (is_access_with_سائيز_p (ref))
    أرجع CALL_اظهار_ARG (ref, 1);

  أرجع NULL_وڻ;
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

ساكن بنية c_اظهار
c_parser_postfix_اظهار (c_parser *parser)
{
  بنية c_اظهار اظهار, e1;
  بنية c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  ذريعو_range tok_range = c_parser_peek_token (parser)->get_range ();
  اظهار.original_ڪوڊ = ERROR_MARK;
  اظهار.original_type = عدم;
  اظهار.m_decimal = 0;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_عدد:
      اظهار.قدر = c_parser_peek_token (parser)->قدر;
      سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
      loc = c_parser_peek_token (parser)->location;
      اظهار.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      إذا (وڻ_ڪوڊ (اظهار.قدر) == FIXED_CST
	  && !targetm.fixed_نقطو_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  اظهار.سيٽ_error ();
	}
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      اظهار.قدر = c_parser_peek_token (parser)->قدر;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      اظهار.original_type = char_type_ڳنڍ;
      سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      اظهار = c_parser_string_literal (parser, parser->translate_لڙيون_p,
				      سچ);
      اكسر;
    حالة CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      اظهار.قدر
	= objc_build_string_object (c_parser_peek_token (parser)->قدر);
      سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_NAME:
      بدل (c_parser_peek_token (parser)->id_قسم)
	{
	حالة C_ID_ID:
	  {
	    وڻ id = c_parser_peek_token (parser)->قدر;
	    c_parser_consume_token (parser);
	    اظهار.قدر = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &اظهار.original_type);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
	    اكسر;
	  }
	حالة C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    وڻ class_name = c_parser_peek_token (parser)->قدر;
	    وڻ component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    إذا (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->قدر;
	    location_t پڇاڙي_loc = component_tok->get_پڄاڻي ();
	    c_parser_consume_token (parser);
	    اظهار.قدر = objc_build_class_component_ref (class_name,
							 component);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, پڇاڙي_loc);
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser, "expected expression");
	  اظهار.سيٽ_error ();
	  اكسر;
	}
      اكسر;
    حالة CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      إذا (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  وڻ stmt;
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
	      parser->error = سچ;
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE, عدم);
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	      اظهار.سيٽ_error ();
	      اكسر;
	    }
	  c_omp_array_section_p = خطأ;
	  stmt = c_begin_stmt_اظهار ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  اظهار.قدر = c_پڄاڻي_stmt_اظهار (brace_loc, stmt);
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_loc);
	  mark_exp_read (اظهار.قدر);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      وإلا
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  اظهار = c_parser_اظهار (parser);
	  إذا (وڻ_ڪوڊ (اظهار.قدر) == MODIFY_اظهار)
	    suppress_warning (اظهار.قدر, OPT_Wparentheses);
	  إذا (اظهار.original_ڪوڊ != C_MAYBE_CONST_اظهار
	      && اظهار.original_ڪوڊ != SIZEOF_اظهار)
	    اظهار.original_ڪوڊ = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  إذا (اظهار.original_ڪوڊ == SIZEOF_اظهار)
	    اظهار.original_ڪوڊ = PAREN_SIZEOF_اظهار;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      اكسر;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_FUNCTION_NAME:
	حالة RID_PRETTY_FUNCTION_NAME:
	حالة RID_C99_FUNCTION_NAME:
	  اظهار = c_parser_predefined_identifier (parser);
	  اكسر;
	حالة RID_VA_ARG:
	  {
	    location_t شروعات_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    e1 = c_parser_اظهار_no_commas (parser, عدم);
	    mark_exp_read (e1.قدر);
	    e1.قدر = c_fully_fold (e1.قدر, خطأ, عدم);
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t پڇاڙي_loc = c_parser_peek_token (parser)->get_پڄاڻي ();
	    c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (t1 == عدم)
	      {
		اظهار.سيٽ_error ();
	      }
	    وإلا
	      {
		وڻ type_اظهار = NULL_وڻ;
		وڻ type = groktypename (t1, &type_اظهار, عدم);
		اظهار.قدر = c_build_va_arg (شروعات_loc, e1.قدر, loc,
					     type, type_اظهار);
		سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات_loc, پڇاڙي_loc);
	      }
	  }
	  اكسر;
	حالة RID_C23_VA_شروعات:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    e1 = c_parser_اظهار_no_commas (parser, عدم);
	    e1 = convert_lvalue_منزل_rvalue (e1.get_location (), e1, سچ, سچ);
	    إذا (!c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
		    اظهار.سيٽ_error ();
		    اكسر;
		  }
		إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_قسم == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    وڻ name = c_parser_peek_token (parser)->قدر;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    وڻ decl = lookup_name (name);
		    وڻ آخري_parm
		      = وڻ_آخري (DECL_ARGUMENTS (current_function_decl));
		    إذا (!آخري_parm || decl != آخري_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    وإلا إذا (DECL_رجسٽر (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		وإلا
		  {
		    بنانشان nesting_اونهائي = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    طالما (سچ)
		      {
			c_token *token = c_parser_peek_token (parser);
			إذا (token->type == CPP_CLOSE_PAREN && !nesting_اونهائي)
			  اكسر;

			إذا (token->type == CPP_EOF)
			  اكسر;
			إذا (token->type == CPP_OPEN_PAREN)
			  ++nesting_اونهائي;
			وإلا إذا (token->type == CPP_CLOSE_PAREN)
			  --nesting_اونهائي;
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
	    parens.skip_until_مليو_close (parser);
	    وڻ fndecl = builtin_decl_explicit (BUILT_اندريون_VA_شروعات);
	    vec<وڻ, va_gc> *params;
	    vec_alloc (params, 2);
	    params->تيز_ڌڪو (e1.قدر);
	    params->تيز_ڌڪو (integer_zero_ڳنڍ);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.تيز_ڌڪو (e1.get_location ());
	    arg_loc.تيز_ڌڪو (UNKNOWN_LOCATION);
	    اظهار.قدر = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, عدم);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc,
				     parser->ٽوڪن_buf[0].get_پڄاڻي ());
	    اظهار.m_decimal = 0;
	    اظهار.original_ڪوڊ = ERROR_MARK;
	    اظهار.original_type = عدم;
	    release_وڻ_ويڪٽر (params);
	    اكسر;
	  }
	حالة RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      parser->error = سچ;
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    إذا (parser->error)
	      {
		c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    وڻ type = groktypename (t1, عدم, عدم);
	    وڻ offsetof_ref;
	    إذا (type == error_mark_ڳنڍ)
	      offsetof_ref = error_mark_ڳنڍ;
	    وإلا
	      {
		offsetof_ref = build1 (اڻسڌو_REF, type, null_اشارو_ڳنڍ);
		سيٽ_اظهار_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->قدر,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		طالما (c_parser_ايندڙ_token_is (parser, CPP_DOT)
		       || c_parser_ايندڙ_token_is (parser,
						  CPP_OPEN_چورس)
		       || c_parser_ايندڙ_token_is (parser,
						  CPP_DEREF))
		  {
		    إذا (c_parser_ايندڙ_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_ڳنڍ);
			اذهب do_dot;
		      }
		    وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			إذا (c_parser_ايندڙ_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    اكسر;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->قدر,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    وإلا
		      {
			بنية c_اظهار ce;
			وڻ idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_اظهار (parser);
			ce = convert_lvalue_منزل_rvalue (loc, ce, خطأ, خطأ);
			idx = ce.قدر;
			idx = c_fully_fold (idx, خطأ, عدم);
			c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    وإلا
	      c_parser_error (parser, "expected identifier");
	    location_t پڇاڙي_loc = c_parser_peek_token (parser)->get_پڄاڻي ();
	    c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    اظهار.قدر = fold_offsetof (offsetof_ref);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, پڇاڙي_loc);
	  }
	  اكسر;
	حالة RID_چونڊيو_اظهار:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    c_اظهار_t *e1_p, *e2_p, *e3_p;
	    وڻ c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_دليلون (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, سچ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->قدر;
	    mark_exp_read (e2_p->قدر);
	    mark_exp_read (e3_p->قدر);
	    إذا (وڻ_ڪوڊ (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (وڻ_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_اظهار_warning (c);
	    اظهار = integer_zerop (c) ? *e3_p : *e2_p;
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    t2 = c_parser_type_name (parser);
	    إذا (t2 == عدم)
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_مليو_close (parser);
	    وڻ e1, e2;
	    e1 = groktypename (t1, عدم, عدم);
	    e2 = groktypename (t2, عدم, عدم);
	    إذا (e1 == error_mark_ڳنڍ || e2 == error_mark_ڳنڍ)
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    اظهار.قدر
	      = comptypes (e1, e2) ? integer_one_ڳنڍ : integer_zero_ڳنڍ;
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	  }
	  اكسر;
	حالة RID_BUILTIN_TGMATH:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_دليلون (parser,
					    "__builtin_tgmath",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    بنانشان صحيح i;
	    c_اظهار_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_منزل_rvalue (loc, *p, سچ, سچ);
	    بنانشان صحيح nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    إذا (nargs == 0)
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    بنانشان صحيح انگ_functions = vec_محفوظ_ڊيگهائي (cexpr_list) - nargs;
	    إذا (انگ_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    لكل (بنانشان صحيح j = 1; j < انگ_functions; j++)
	      {
		بنانشان صحيح this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		إذا (this_nargs == 0)
		  {
		    اظهار.سيٽ_error ();
		    اذهب ٻاهريون;
		  }
		إذا (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    اظهار.سيٽ_error ();
		    اذهب ٻاهريون;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<تعداد tgmath_parm_قسم> parm_قسم (nargs + 1);
	    auto_vec<وڻ> parm_پهريون (nargs + 1);
	    auto_vec<منطقي> parm_complex (nargs + 1);
	    auto_vec<منطقي> parm_varies (nargs + 1);
	    وڻ پهريون_type = وڻ_TYPE (وڻ_TYPE ((*cexpr_list)[0].قدر));
	    وڻ پهريون_ret = TYPE_MAIN_VARIANT (وڻ_TYPE (پهريون_type));
	    parm_پهريون.تيز_ڌڪو (پهريون_ret);
	    parm_complex.تيز_ڌڪو (وڻ_ڪوڊ (پهريون_ret) == COMPLEX_TYPE);
	    parm_varies.تيز_ڌڪو (خطأ);
	    function_دليلون_iterator iter;
	    وڻ t;
	    بنانشان صحيح argpos;
	    FOREACH_FUNCTION_دليلون (پهريون_type, t, iter)
	      {
		إذا (t == void_type_ڳنڍ)
		  اكسر;
		parm_پهريون.تيز_ڌڪو (TYPE_MAIN_VARIANT (t));
		parm_complex.تيز_ڌڪو (وڻ_ڪوڊ (t) == COMPLEX_TYPE);
		parm_varies.تيز_ڌڪو (خطأ);
	      }
	    لكل (بنانشان صحيح j = 1; j < انگ_functions; j++)
	      {
		وڻ type = وڻ_TYPE (وڻ_TYPE ((*cexpr_list)[j].قدر));
		وڻ ret = TYPE_MAIN_VARIANT (وڻ_TYPE (type));
		إذا (ret != parm_پهريون[0])
		  {
		    parm_varies[0] = سچ;
		    إذا (!SCALAR_FLOAT_TYPE_P (parm_پهريون[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_پهريون[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		    إذا (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		  }
		إذا (وڻ_ڪوڊ (ret) == COMPLEX_TYPE)
		  parm_complex[0] = سچ;
		argpos = 1;
		FOREACH_FUNCTION_دليلون (type, t, iter)
		  {
		    إذا (t == void_type_ڳنڍ)
		      اكسر;
		    t = TYPE_MAIN_VARIANT (t);
		    إذا (t != parm_پهريون[argpos])
		      {
			parm_varies[argpos] = سچ;
			إذا (!SCALAR_FLOAT_TYPE_P (parm_پهريون[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_پهريون[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    اظهار.سيٽ_error ();
			    اذهب ٻاهريون;
			  }
			إذا (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    اظهار.سيٽ_error ();
			    اذهب ٻاهريون;
			  }
		      }
		    إذا (وڻ_ڪوڊ (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = سچ;
		    argpos++;
		  }
	      }
	    تعداد tgmath_parm_قسم max_variation = tgmath_fixed;
	    لكل (بنانشان صحيح j = 0; j <= nargs; j++)
	      {
		تعداد tgmath_parm_قسم this_قسم;
		إذا (parm_varies[j])
		  {
		    إذا (parm_complex[j])
		      max_variation = this_قسم = tgmath_complex;
		    وإلا
		      {
			this_قسم = tgmath_real;
			إذا (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		وإلا
		  this_قسم = tgmath_fixed;
		parm_قسم.تيز_ڌڪو (this_قسم);
	      }
	    إذا (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    بنانشان صحيح tgarg = 0;
	    لكل (بنانشان صحيح j = 1; j <= nargs; j++)
	      إذا (parm_قسم[j] == max_variation)
		{
		  tgarg = j;
		  اكسر;
		}
	    إذا (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<وڻ> tg_type (انگ_functions);
	    لكل (بنانشان صحيح j = 0; j < انگ_functions; j++)
	      {
		وڻ type = وڻ_TYPE (وڻ_TYPE ((*cexpr_list)[j].قدر));
		argpos = 1;
		FOREACH_FUNCTION_دليلون (type, t, iter)
		  {
		    إذا (argpos == tgarg)
		      {
			tg_type.تيز_ڌڪو (TYPE_MAIN_VARIANT (t));
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
	    منطقي all_complex = سچ;
	    منطقي all_ٻٽو = سچ;
	    منطقي all_decimal = سچ;
	    hash_سيٽ<وڻ> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		إذا (وڻ_ڪوڊ (t) == COMPLEX_TYPE)
		  all_decimal = خطأ;
		وإلا
		  {
		    all_complex = خطأ;
		    إذا (DECIMAL_FLOAT_TYPE_P (t))
		      all_ٻٽو = خطأ;
		    وإلا
		      all_decimal = خطأ;
		  }
		إذا (tg_types.جوڙيو (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    اظهار.سيٽ_error ();
		    اذهب ٻاهريون;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    لكل (بنانشان صحيح j = 0; j < انگ_functions; j++)
	      {
		وڻ exp_type = tg_type[j];
		وڻ exp_real_type = exp_type;
		إذا (وڻ_ڪوڊ (exp_type) == COMPLEX_TYPE)
		  exp_real_type = وڻ_TYPE (exp_type);
		وڻ type = وڻ_TYPE (وڻ_TYPE ((*cexpr_list)[j].قدر));
		وڻ ret = TYPE_MAIN_VARIANT (وڻ_TYPE (type));
		إذا ((parm_قسم[0] == tgmath_complex && ret != exp_type)
		    || (parm_قسم[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    اظهار.سيٽ_error ();
		    اذهب ٻاهريون;
		  }
		argpos = 1;
		FOREACH_FUNCTION_دليلون (type, t, iter)
		  {
		    إذا (t == void_type_ڳنڍ)
		      اكسر;
		    t = TYPE_MAIN_VARIANT (t);
		    إذا ((parm_قسم[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_قسم[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
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
	    منطقي arg_ٻٽو = all_ٻٽو;
	    منطقي arg_int_decimal = all_decimal;
	    منطقي arg_int_floatnx = خطأ;
	    منطقي arg_int_decimalx = خطأ;
	    لكل (بنانشان صحيح j = 1; j <= nargs; j++)
	      {
		إذا (parm_قسم[j] == tgmath_fixed)
		  استمر;
		c_اظهار_t *ce = &(*cexpr_list)[انگ_functions + j - 1];
		وڻ type = وڻ_TYPE (ce->قدر);
		إذا (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && وڻ_ڪوڊ (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    اظهار.سيٽ_error ();
		    اذهب ٻاهريون;
		  }
		إذا (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = سچ;
		    إذا (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		    وإلا إذا (all_ٻٽو)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		    وإلا إذا (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		    وإلا إذا (arg_ٻٽو)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		  }
		وإلا إذا (وڻ_ڪوڊ (type) == COMPLEX_TYPE)
		  {
		    arg_complex = سچ;
		    إذا (COMPLEX_FLOAT_TYPE_P (type))
		      arg_ٻٽو = سچ;
		    إذا (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		    وإلا إذا (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		  }
		وإلا إذا (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_ٻٽو = سچ;
		    إذا (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		    وإلا إذا (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			اظهار.سيٽ_error ();
			اذهب ٻاهريون;
		      }
		  }
		وڻ rtype = TYPE_MAIN_VARIANT (type);
		إذا (وڻ_ڪوڊ (rtype) == COMPLEX_TYPE)
		  rtype = وڻ_TYPE (rtype);
		إذا (SCALAR_FLOAT_TYPE_P (rtype))
		  لكل (بنانشان صحيح j = 0; j < انگ_FLOATNX_TYPES; j++)
		    إذا (rtype == FLOATNX_TYPE_ڳنڍ (j))
		      {
			arg_int_floatnx = سچ;
			اكسر;
		      }
		إذا (rtype == dfloat64x_type_ڳنڍ)
		  arg_int_decimalx = سچ;
	      }
	    وڻ arg_real = NULL_وڻ;
	    لكل (بنانشان صحيح j = 1; j <= nargs; j++)
	      {
		إذا (parm_قسم[j] == tgmath_fixed)
		  استمر;
		c_اظهار_t *ce = &(*cexpr_list)[انگ_functions + j - 1];
		وڻ type = TYPE_MAIN_VARIANT (وڻ_TYPE (ce->قدر));
		إذا (وڻ_ڪوڊ (type) == COMPLEX_TYPE)
		  type = وڻ_TYPE (type);
		إذا (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_ڳنڍ
			  : arg_int_floatnx
			  ? float32x_type_ڳنڍ
			  : arg_int_decimal
			  ? dfloat64_type_ڳنڍ
			  : double_type_ڳنڍ);
		إذا (arg_real == NULL_وڻ)
		  arg_real = type;
		وإلا
		  arg_real = common_type (arg_real, type);
		إذا (arg_real == error_mark_ڳنڍ)
		  {
		    اظهار.سيٽ_error ();
		    اذهب ٻاهريون;
		  }
	      }
	    وڻ arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_اظهار_t *fn = عدم;
	    لكل (بنانشان صحيح j = 0; j < انگ_functions; j++)
	      {
		إذا (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    اكسر;
		  }
	      }
	    إذا (fn == عدم
		&& parm_قسم[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_پهريون[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		لكل (بنانشان صحيح j = 0; j < انگ_functions; j++)
		  {
		    إذا (arg_complex
			!= (وڻ_ڪوڊ (tg_type[j]) == COMPLEX_TYPE))
		      استمر;
		    وڻ real_tg_type = (arg_complex
					 ? وڻ_TYPE (tg_type[j])
					 : tg_type[j]);
		    إذا (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      استمر;
		    scalar_float_گهڻائي arg_گهڻائي
		      = SCALAR_FLOAT_TYPE_گهڻائي (arg_real);
		    scalar_float_گهڻائي tg_گهڻائي
		      = SCALAR_FLOAT_TYPE_گهڻائي (real_tg_type);
		    ثابت real_format *arg_fmt = REAL_گهڻائي_FORMAT (arg_گهڻائي);
		    ثابت real_format *tg_fmt = REAL_گهڻائي_FORMAT (tg_گهڻائي);
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
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    /* Construct a call to FN.  */
	    vec<وڻ, va_gc> *دليلون;
	    vec_alloc (دليلون, nargs);
	    vec<وڻ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    لكل (بنانشان صحيح j = 0; j < nargs; j++)
	      {
		c_اظهار_t *ce = &(*cexpr_list)[انگ_functions + j];
		دليلون->تيز_ڌڪو (ce->قدر);
		arg_loc.تيز_ڌڪو (ce->get_location ());
		origtypes->تيز_ڌڪو (ce->original_type);
	      }
	    اظهار.قدر = c_build_function_call_vec (loc, arg_loc, fn->قدر,
						    دليلون, origtypes);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    c_اظهار_t *e2_p;
	    وڻ chain_قدر;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_دليلون (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    اظهار = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_منزل_rvalue (loc, *e2_p, سچ, سچ);
	    chain_قدر = e2_p->قدر;
	    mark_exp_read (chain_قدر);

	    إذا (وڻ_ڪوڊ (اظهار.قدر) != CALL_اظهار)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    وإلا إذا (وڻ_ڪوڊ (وڻ_TYPE (chain_قدر)) != اشارو_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    وإلا
	      CALL_اظهار_STATIC_CHAIN (اظهار.قدر) = chain_قدر;
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_COMPLEX:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    c_اظهار_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_دليلون (parser,
					    "__builtin_complex",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_منزل_rvalue (loc, *e1_p, سچ, سچ);
	    إذا (وڻ_ڪوڊ (e1_p->قدر) == EXCESS_PRECISION_اظهار)
	      e1_p->قدر = convert (وڻ_TYPE (e1_p->قدر),
				     وڻ_عمليو (e1_p->قدر, 0));
	    *e2_p = convert_lvalue_منزل_rvalue (loc, *e2_p, سچ, سچ);
	    إذا (وڻ_ڪوڊ (e2_p->قدر) == EXCESS_PRECISION_اظهار)
	      e2_p->قدر = convert (وڻ_TYPE (e2_p->قدر),
				     وڻ_عمليو (e2_p->قدر, 0));
	    إذا (!SCALAR_FLOAT_TYPE_P (وڻ_TYPE (e1_p->قدر))
		|| DECIMAL_FLOAT_TYPE_P (وڻ_TYPE (e1_p->قدر))
		|| !SCALAR_FLOAT_TYPE_P (وڻ_TYPE (e2_p->قدر))
		|| DECIMAL_FLOAT_TYPE_P (وڻ_TYPE (e2_p->قدر)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (TYPE_MAIN_VARIANT (وڻ_TYPE (e1_p->قدر))
		!= TYPE_MAIN_VARIANT (وڻ_TYPE (e2_p->قدر)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    اظهار.قدر = build2_loc (loc, COMPLEX_اظهار,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (وڻ_TYPE (e1_p->قدر))),
				     e1_p->قدر, e2_p->قدر);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    c_اظهار_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_دليلون (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    e_p = &(*cexpr_list)[0];
	    وڻ ref = e_p->قدر;

	    إذا (وڻ_ڪوڊ (وڻ_TYPE (ref)) != ARRAY_TYPE
		 && وڻ_ڪوڊ (وڻ_TYPE (ref)) != اشارو_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    إذا (وڻ_ڪوڊ (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    إذا (وڻ_ڪوڊ (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    إذا (has_counted_by_object (ref))
	      اظهار.قدر = get_counted_by_ref (ref);
	    وإلا
	      اظهار.قدر = null_اشارو_ڳنڍ;

	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    بنانشان صحيح i;
	    c_اظهار_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_دليلون (parser,
					    "__builtin_shuffle",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    FOR_EACH_VEC_محفوظ_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_منزل_rvalue (loc, *p, سچ, سچ);

	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) == 2)
	      اظهار.قدر = c_build_vec_perm_اظهار (loc, (*cexpr_list)[0].قدر,
						  NULL_وڻ,
						  (*cexpr_list)[1].قدر);

	    وإلا إذا (vec_محفوظ_ڊيگهائي (cexpr_list) == 3)
	      اظهار.قدر = c_build_vec_perm_اظهار (loc, (*cexpr_list)[0].قدر,
						  (*cexpr_list)[1].قدر,
						  (*cexpr_list)[2].قدر);
	    وإلا
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		اظهار.سيٽ_error ();
	      }
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    بنانشان صحيح i;
	    c_اظهار_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_دليلون (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    FOR_EACH_VEC_محفوظ_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_منزل_rvalue (loc, *p, سچ, سچ);

	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		اظهار.سيٽ_error ();
	      }
	    وإلا
	      {
		auto_vec<وڻ, 16> نقاب;
		لكل (i = 2; i < cexpr_list->ڊيگهائي (); ++i)
		  نقاب.محفوظ_ڌڪو ((*cexpr_list)[i].قدر);
		اظهار.قدر = c_build_shufflevector (loc, (*cexpr_list)[0].قدر,
						    (*cexpr_list)[1].قدر,
						    نقاب);
	      }
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t شروعات_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    e1 = c_parser_اظهار_no_commas (parser, عدم);
	    mark_exp_read (e1.قدر);
	    إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t پڇاڙي_loc = c_parser_peek_token (parser)->get_پڄاڻي ();
	    c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (t1 == عدم)
	      اظهار.سيٽ_error ();
	    وإلا
	      {
		وڻ type_اظهار = NULL_وڻ;
		اظهار.قدر = c_build_vec_convert (شروعات_loc, e1.قدر, loc,
						  groktypename (t1, &type_اظهار,
								عدم));
		سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات_loc, پڇاڙي_loc);
	      }
	  }
	  اكسر;
	حالة RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t شروعات_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    e1 = c_parser_اظهار_no_commas (parser, عدم);
	    mark_exp_read (e1.قدر);
	    location_t پڇاڙي_loc = c_parser_peek_token (parser)->get_پڄاڻي ();
	    parens.skip_until_مليو_close (parser);
	    اظهار = parser_build_unary_op (loc, PAREN_اظهار, e1);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات_loc, پڇاڙي_loc);
	  }
	  اكسر;
	حالة RID_BUILTIN_STDC:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    c_اظهار_t *arg_p;
	    location_t close_paren_loc;
	    تعداد c_builtin_stdc {
	      C_BUILTIN_STDC_ٻٽو_انگ_CEIL,
	      C_BUILTIN_STDC_ٻٽو_انگ_FLOOR,
	      C_BUILTIN_STDC_ٻٽو_انگ_ويڪر,
	      C_BUILTIN_STDC_ڳڻپ_ONES,
	      C_BUILTIN_STDC_ڳڻپ_ZEROS,
	      C_BUILTIN_STDC_پهريون_LEADING_ONE,
	      C_BUILTIN_STDC_پهريون_LEADING_ZERO,
	      C_BUILTIN_STDC_پهريون_TRAILING_ONE,
	      C_BUILTIN_STDC_پهريون_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_ٻٽو_انگ,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_کاٻو,
	      C_BUILTIN_STDC_ROTATE_ساڄو,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ثابت حرف *name
	      = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	    بنانشان انگ_دليلون = 1;
	    بدل (name[حجم ("__builtin_stdc_") - 1])
	      {
	      حالة 'b':
		بدل (name[حجم ("__builtin_stdc_bit_") - 1])
		  {
		  حالة 'c':
		    stdc_rid = C_BUILTIN_STDC_ٻٽو_انگ_CEIL;
		    اكسر;
		  حالة 'f':
		    stdc_rid = C_BUILTIN_STDC_ٻٽو_انگ_FLOOR;
		    اكسر;
		  افتراضي:
		    stdc_rid = C_BUILTIN_STDC_ٻٽو_انگ_ويڪر;
		    اكسر;
		  }
		اكسر;
	      حالة 'c':
		إذا (name[حجم ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_ڳڻپ_ONES;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_ڳڻپ_ZEROS;
		اكسر;
	      حالة 'f':
		بدل (name[حجم ("__builtin_stdc_first_trailing_") - 1])
		  {
		  حالة 'n':
		    stdc_rid = C_BUILTIN_STDC_پهريون_LEADING_ONE;
		    اكسر;
		  حالة 'e':
		    stdc_rid = C_BUILTIN_STDC_پهريون_LEADING_ZERO;
		    اكسر;
		  حالة 'o':
		    stdc_rid = C_BUILTIN_STDC_پهريون_TRAILING_ONE;
		    اكسر;
		  افتراضي:
		    stdc_rid = C_BUILTIN_STDC_پهريون_TRAILING_ZERO;
		    اكسر;
		  }
		اكسر;
	      حالة 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_ٻٽو_انگ;
		اكسر;
	      حالة 'l':
		إذا (name[حجم ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		اكسر;
	      حالة 'r':
		إذا (name[حجم ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_کاٻو;
		وإلا
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ساڄو;
		انگ_دليلون = 2;
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
	    إذا (!c_parser_get_builtin_دليلون (parser, name,
					    &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) != انگ_دليلون)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_منزل_rvalue (loc, *arg_p, سچ, سچ);
	    إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (arg_p->قدر)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (وڻ_ڪوڊ (وڻ_TYPE (arg_p->قدر)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (وڻ_ڪوڊ (وڻ_TYPE (arg_p->قدر)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (!TYPE_UNSIGNED (وڻ_TYPE (arg_p->قدر)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (TYPE_MAIN_VARIANT (وڻ_TYPE (arg_p->قدر))
		== char_type_ڳنڍ)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    وڻ arg = arg_p->قدر;
	    وڻ type = TYPE_MAIN_VARIANT (وڻ_TYPE (arg));
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
	    إذا (انگ_دليلون == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_منزل_rvalue (loc, *arg_p, سچ, سچ);
		إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (arg_p->قدر)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    اظهار.سيٽ_error ();
		    اكسر;
		  }
		إذا (وڻ_ڪوڊ (وڻ_TYPE (arg_p->قدر)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    اظهار.سيٽ_error ();
		    اكسر;
		  }
		وڻ arg1 = save_اظهار (arg);
		وڻ arg2 = save_اظهار (arg_p->قدر);
		وڻ_ڪوڊ_2 ڪوڊ;
		إذا (stdc_rid == C_BUILTIN_STDC_ROTATE_کاٻو)
		  ڪوڊ = LROTATE_اظهار;
		وإلا
		  ڪوڊ = RROTATE_اظهار;

		إذا (وڻ_ڪوڊ (arg2) == INTEGER_CST
		    && وڻ_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_ڳڻپ_negative,
			      "rotate count is negative");

		وڻ instrument_اظهار = NULL_وڻ;
		إذا (sanitize_flags_p (SANITIZE_سرڪايو))
		  instrument_اظهار = ubsan_instrument_سرڪايو (loc, ڪوڊ,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		إذا (TYPE_PRECISION (وڻ_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_ڳنڍ))
		  arg2 = fold_convert (unsigned_type_ڳنڍ, arg2);

		إذا (TYPE_UNSIGNED (وڻ_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_اظهار, وڻ_TYPE (arg2),
				     arg2, build_int_cst (وڻ_TYPE (arg2),
							  prec));
		وإلا
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    وڻ utype = c_common_unsigned_type (وڻ_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_اظهار, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		إذا (type_has_گهڻائي_precision_p (وڻ_TYPE (arg1))
		    || (وڻ_ڪوڊ (وڻ_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_گهڻائي_سائيز))
		  اظهار.قدر = build2_loc (loc, ڪوڊ, وڻ_TYPE (arg1), arg1,
					   arg2);
		وإلا
		  {
		    arg2 = save_اظهار (arg2);
		    وڻ t1 = build2_loc (loc, (ڪوڊ == LROTATE_اظهار
						? LSHIFT_اظهار : RSHIFT_اظهار),
					  وڻ_TYPE (arg1), arg1, arg2);
		    وڻ t2 = build2_loc (loc, MINUS_اظهار,
					  وڻ_TYPE (arg2),
					  build_int_cst (وڻ_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (ڪوڊ == LROTATE_اظهار
					   ? RSHIFT_اظهار : LSHIFT_اظهار),
				     وڻ_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_ڳڻپ_حد_کان_مٿي);
		    وڻ t3 = build2_loc (loc, ٻٽو_انگ_IOR_اظهار,
					  وڻ_TYPE (arg1), t1, t2);
		    وڻ t4 = build2_loc (loc, NE_اظهار, boolean_type_ڳنڍ,
					  arg2,
					  build_zero_cst (وڻ_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_اظهار, boolean_type_ڳنڍ,
				     arg1, t4);
		    اظهار.قدر = build3_loc (loc, COND_اظهار,
					     وڻ_TYPE (arg1), t4, t3, arg1);
		  }
		إذا (instrument_اظهار)
		  اظهار.قدر = build2_loc (loc, COMPOUND_اظهار,
					   وڻ_TYPE (اظهار.قدر),
					   instrument_اظهار, اظهار.قدر);
		سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
		اكسر;
	      }
	    وڻ barg1 = arg;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_CEIL:
		arg = save_اظهار (arg);
		barg1 = build2_loc (loc, PLUS_اظهار, type, arg,
				    build_int_cst (type, -1));
		اكسر;
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_FLOOR:
		barg1 = arg = save_اظهار (arg);
		اكسر;
	      حالة C_BUILTIN_STDC_ڳڻپ_ZEROS:
	      حالة C_BUILTIN_STDC_پهريون_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_پهريون_TRAILING_ZERO:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, ٻٽو_انگ_NOT_اظهار, type, arg);
		اكسر;
	      افتراضي:
		اكسر;
	      }
	    وڻ barg2 = NULL_وڻ;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_ويڪر:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_LEADING_ZEROS:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_ڳنڍ, prec);
		اكسر;
	      حالة C_BUILTIN_STDC_پهريون_LEADING_ONE:
	      حالة C_BUILTIN_STDC_پهريون_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_پهريون_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_پهريون_TRAILING_ZERO:
		barg2 = integer_minus_one_ڳنڍ;
		اكسر;
	      افتراضي:
		اكسر;
	      }
	    وڻ fndecl = NULL_وڻ;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_CEIL:
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_FLOOR:
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_ويڪر:
	      حالة C_BUILTIN_STDC_پهريون_LEADING_ONE:
	      حالة C_BUILTIN_STDC_پهريون_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_LEADING_ONES:
	      حالة C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_اندريون_CLZG);
		اكسر;
	      حالة C_BUILTIN_STDC_پهريون_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_پهريون_TRAILING_ZERO:
	      حالة C_BUILTIN_STDC_TRAILING_ONES:
	      حالة C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_اندريون_CTZG);
		اكسر;
	      حالة C_BUILTIN_STDC_ڳڻپ_ONES:
	      حالة C_BUILTIN_STDC_ڳڻپ_ZEROS:
	      حالة C_BUILTIN_STDC_HAS_SINGLE_ٻٽو_انگ:
		fndecl = builtin_decl_explicit (BUILT_اندريون_POPCOUNTG);
		اكسر;
	      افتراضي:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    صحيح nargs = barg2 != NULL_وڻ ? 2 : 1;
	    vec<وڻ, va_gc> *دليلون;
	    vec_alloc (دليلون, nargs);
	    vec<وڻ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    دليلون->تيز_ڌڪو (barg1);
	    arg_loc.تيز_ڌڪو (arg_p->get_location ());
	    origtypes->تيز_ڌڪو (arg_p->original_type);
	    إذا (nargs == 2)
	      {
		دليلون->تيز_ڌڪو (barg2);
		arg_loc.تيز_ڌڪو (loc);
		origtypes->تيز_ڌڪو (integer_type_ڳنڍ);
	      }
	    اظهار.قدر = c_build_function_call_vec (loc, arg_loc, fndecl,
						    دليلون, origtypes);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    إذا (اظهار.قدر == error_mark_ڳنڍ)
	      اكسر;
	    بدل (stdc_rid)
	      {
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_CEIL:
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_FLOOR:
		--prec;
		/* FALLTHRU */
	      حالة C_BUILTIN_STDC_ٻٽو_انگ_ويڪر:
		اظهار.قدر = build2_loc (loc, MINUS_اظهار, integer_type_ڳنڍ,
					 build_int_cst (integer_type_ڳنڍ,
							prec), اظهار.قدر);
		اكسر;
	      حالة C_BUILTIN_STDC_پهريون_LEADING_ONE:
	      حالة C_BUILTIN_STDC_پهريون_LEADING_ZERO:
	      حالة C_BUILTIN_STDC_پهريون_TRAILING_ONE:
	      حالة C_BUILTIN_STDC_پهريون_TRAILING_ZERO:
		اظهار.قدر = build2_loc (loc, PLUS_اظهار, integer_type_ڳنڍ,
					 اظهار.قدر, integer_one_ڳنڍ);
		اكسر;
	      حالة C_BUILTIN_STDC_HAS_SINGLE_ٻٽو_انگ:
		اظهار.قدر = build2_loc (loc, EQ_اظهار, boolean_type_ڳنڍ,
					 اظهار.قدر, integer_one_ڳنڍ);
		اكسر;
	      افتراضي:
		اكسر;
	      }

	    إذا (stdc_rid != C_BUILTIN_STDC_ٻٽو_انگ_CEIL
		&& stdc_rid != C_BUILTIN_STDC_ٻٽو_انگ_FLOOR)
	      {
		إذا (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_ٻٽو_انگ)
		  اظهار.قدر = fold_convert_loc (loc, unsigned_type_ڳنڍ,
						 اظهار.قدر);
		اكسر;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    إذا (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_ٻٽو_انگ_CEIL && integer_onep (arg)))
	      اظهار.قدر = build_int_cst (type, 0);
	    وإلا
	      اظهار.قدر
		= build2_loc (loc, LSHIFT_اظهار, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_ٻٽو_انگ_CEIL
					      ? 2 : 1)), اظهار.قدر);
	    إذا (stdc_rid == C_BUILTIN_STDC_ٻٽو_انگ_CEIL)
	      اظهار.قدر = build3_loc (loc, COND_اظهار, type,
				       build2_loc (loc, LE_اظهار,
						   boolean_type_ڳنڍ, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       اظهار.قدر);
	    وإلا
	      اظهار.قدر = build3_loc (loc, COND_اظهار, type,
				       build2_loc (loc, EQ_اظهار,
						   boolean_type_ڳنڍ, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       اظهار.قدر);
	    اكسر;
	  }
	حالة RID_BUILTIN_BSWAPG:
	حالة RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_اظهار_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    اندروني_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ثابت حرف *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    إذا (!c_parser_get_builtin_دليلون (parser, name, &cexpr_list, خطأ,
					    &close_paren_loc))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    إذا (vec_محفوظ_ڊيگهائي (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		اظهار.سيٽ_error ();
		اكسر;
	      }

	    c_اظهار_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_منزل_rvalue (loc, *arg_p, سچ, سچ);
	    وڻ arg = arg_p->قدر;
	    إذا (error_عمليو_p (arg))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    وڻ type = TYPE_MAIN_VARIANT (وڻ_TYPE (arg));
	    إذا (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (وڻ_ڪوڊ (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (وڻ_ڪوڊ (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    arg = c_fully_fold (arg, خطأ, عدم);
	    اظهار.قدر = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_paren_loc);
	    اكسر;
	  }
	حالة RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    وڻ sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_مليو_close (parser);
	    اظهار.قدر = objc_build_selector_اظهار (loc, sel);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_loc);
	  }
	  اكسر;
	حالة RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    إذا (!parens.require_open (parser))
	      {
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    وڻ id = c_parser_peek_token (parser)->قدر;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_مليو_close (parser);
	    اظهار.قدر = objc_build_protocol_اظهار (id);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_loc);
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
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    t1 = c_parser_type_name (parser);
	    إذا (t1 == عدم)
	      {
		اظهار.سيٽ_error ();
		c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
		اكسر;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_مليو_close (parser);
	    وڻ type = groktypename (t1, عدم, عدم);
	    اظهار.قدر = objc_build_encode_اظهار (type);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_loc);
	  }
	  اكسر;
	حالة RID_GENERIC:
	  اظهار = c_parser_generic_selection (parser);
	  اكسر;
	حالة RID_OMP_ALL_يادگيري:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  اظهار.سيٽ_error ();
	  اكسر;
	/* C23 'nullptr' literal.  */
	حالة RID_NULLPTR:
	  c_parser_consume_token (parser);
	  اظهار.قدر = nullptr_ڳنڍ;
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  اكسر;
	حالة RID_TRUE:
	  c_parser_consume_token (parser);
	  اظهار.قدر = boolean_true_ڳنڍ;
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
	  اكسر;
	حالة RID_FALSE:
	  c_parser_consume_token (parser);
	  اظهار.قدر = boolean_false_ڳنڍ;
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected expression");
	  اظهار.سيٽ_error ();
	  اكسر;
	}
      اكسر;
    حالة CPP_OPEN_چورس:
      إذا (c_dialect_objc ())
	{
	  وڻ receiver, دليلون;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  دليلون = c_parser_objc_پيغام_دليلون (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس,
				     "expected %<]%>");
	  اظهار.قدر = objc_build_پيغام_اظهار (receiver, دليلون);
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, loc, close_loc);
	  اكسر;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    افتراضي:
      c_parser_error (parser, "expected expression");
      اظهار.سيٽ_error ();
      اكسر;
    }
 ٻاهريون:
  أرجع c_parser_postfix_اظهار_after_primary
    (parser, اظهار_LOC_OR_LOC (اظهار.قدر, loc), اظهار);
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

ساكن بنية c_اظهار
c_parser_postfix_اظهار_after_paren_type (c_parser *parser,
					      بنية c_declspecs *scspecs,
					      بنية c_type_name *type_name,
					      location_t type_loc)
{
  وڻ type;
  بنية c_اظهار init;
  منطقي non_const;
  بنية c_اظهار اظهار;
  location_t شروعات_loc;
  وڻ type_اظهار = NULL_وڻ;
  منطقي type_اظهار_const = سچ;
  منطقي constexpr_p = scspecs ? scspecs->constexpr_p : خطأ;
  بنانشان صحيح underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (سٽ_جدول, type_loc);
  شروعات_loc = c_parser_peek_token (parser)->location;
  إذا (constexpr_p)
    {
      underspec_state = شروعات_underspecified_init (شروعات_loc, NULL_وڻ);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      بدل (type_name->specs->typespec_قسم)
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
  شروعات_init (NULL_وڻ, عدم,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_اظهار, &type_اظهار_const);
  منطقي varsize_p = خطأ;
  إذا (type != error_mark_ڳنڍ && C_TYPE_VARIABLE_سائيز (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = سچ;
    }
  وإلا إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_ڳنڍ;
    }
  إذا (constexpr_p && type != error_mark_ڳنڍ)
    {
      وڻ type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      إذا (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      وإلا إذا (رڪارڊ_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, خطأ, عدم, varsize_p);
  إذا (constexpr_p)
    پڄاڻي_underspecified_init (NULL_وڻ, underspec_state);
  پڄاڻي_init ();
  maybe_warn_string_init (type_loc, type, init);

  إذا (type != error_mark_ڳنڍ
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_ڳنڍ;
    }

  إذا (!pedwarn_c90 (شروعات_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (شروعات_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.قدر && وڻ_ڪوڊ (init.قدر) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.قدر)
	       : init.original_ڪوڊ == C_MAYBE_CONST_اظهار);
  non_const |= !type_اظهار_const;
  بنانشان صحيح alignas_align = 0;
  إذا (type != error_mark_ڳنڍ
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      إذا (alignas_align < min_align_جو_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  اظهار.قدر = build_compound_literal (شروعات_loc, type, init.قدر, non_const,
				       alignas_align, scspecs);
  سيٽ_c_اظهار_ذريعو_range (&اظهار, init.src_range);
  اظهار.m_decimal = 0;
  اظهار.original_ڪوڊ = ERROR_MARK;
  اظهار.original_type = عدم;
  إذا (type != error_mark_ڳنڍ
      && اظهار.قدر != error_mark_ڳنڍ
      && type_اظهار)
    {
      إذا (وڻ_ڪوڊ (اظهار.قدر) == C_MAYBE_CONST_اظهار)
	{
	  gcc_assert (C_MAYBE_CONST_اظهار_PRE (اظهار.قدر) == NULL_وڻ);
	  C_MAYBE_CONST_اظهار_PRE (اظهار.قدر) = type_اظهار;
	}
      وإلا
	{
	  gcc_assert (!non_const);
	  اظهار.قدر = build2 (C_MAYBE_CONST_اظهار, type,
			       type_اظهار, اظهار.قدر);
	}
    }
  أرجع c_parser_postfix_اظهار_after_primary (parser, شروعات_loc, اظهار);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

ساكن منطقي
sizeof_ptr_memacc_comptypes (وڻ type1, وڻ type2)
{
  أرجع comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

ساكن فراغ
warn_for_abs (location_t loc, وڻ fndecl, وڻ arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  إذا (c_inhibit_evaluation_warnings)
    أرجع;

  وڻ atype = وڻ_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  إذا (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && وڻ_ڪوڊ (atype) != COMPLEX_TYPE)
    أرجع;

  تعداد built_اندريون_function fcode = DECL_FUNCTION_ڪوڊ (fndecl);

  بدل (fcode)
    {
    حالة BUILT_اندريون_ABS:
    حالة BUILT_اندريون_LABS:
    حالة BUILT_اندريون_LLABS:
    حالة BUILT_اندريون_IMAXABS:
      إذا (!INTEGRAL_TYPE_P (atype))
	{
	  إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  وإلا إذا (وڻ_ڪوڊ (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  وإلا
	    gcc_unreachable ();
	  أرجع;
	}
      إذا (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_قدر,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      اكسر;

    CASE_FLT_FN (BUILT_اندريون_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_اندريون_FABS):
      إذا (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_گهڻائي_P (TYPE_گهڻائي (atype)))
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  وإلا إذا (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  وإلا إذا (وڻ_ڪوڊ (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  وإلا
	    gcc_unreachable ();
	  أرجع;
	}
      اكسر;

    CASE_FLT_FN (BUILT_اندريون_CABS):
      إذا (وڻ_ڪوڊ (atype) != COMPLEX_TYPE)
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  وإلا إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  وإلا
	    gcc_unreachable ();

	  أرجع;
	}
      اكسر;

    حالة BUILT_اندريون_FABSD32:
    حالة BUILT_اندريون_FABSD64:
    حالة BUILT_اندريون_FABSD128:
    حالة BUILT_اندريون_FABSD64_X:
      إذا (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  إذا (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  وإلا إذا (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_قدر,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  وإلا إذا (وڻ_ڪوڊ (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_قدر,
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

  إذا (!TYPE_ARG_TYPES (وڻ_TYPE (fndecl)))
    أرجع;

  وڻ ftype = وڻ_قدر (TYPE_ARG_TYPES (وڻ_TYPE (fndecl)));
  إذا (وڻ_ڪوڊ (atype) == COMPLEX_TYPE)
    {
      gcc_assert (وڻ_ڪوڊ (ftype) == COMPLEX_TYPE);
      atype = وڻ_TYPE (atype);
      ftype = وڻ_TYPE (ftype);
    }

  إذا (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_قدر,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

ساكن بنية c_اظهار
c_parser_postfix_اظهار_after_primary (c_parser *parser,
					   location_t اظهار_loc,
					   بنية c_اظهار اظهار)
{
  بنية c_اظهار orig_اظهار;
  وڻ ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  وڻ sizeof_arg[6];
  بنانشان صحيح literal_zero_نقاب;
  بنانشان صحيح i;
  vec<وڻ, va_gc> *exprlist;
  vec<وڻ, va_gc> *origtypes = عدم;
  vec<location_t> arg_loc = vNULL;
  location_t شروعات;
  location_t پڄاڻي;

  طالما (سچ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_چورس:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_وڻ;
	  إذا (!c_omp_array_section_p
	      || c_parser_ايندڙ_token_is_not (parser, CPP_COLON))
	    idx = c_parser_اظهار (parser).قدر;

	  إذا (c_omp_array_section_p
	      && c_parser_ايندڙ_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_CLOSE_چورس))
		len = c_parser_اظهار (parser).قدر;

	      اظهار.قدر = build_omp_array_section (op_loc, اظهار.قدر, idx,
						    len);
	    }
	  وإلا
	    اظهار.قدر = build_array_ref (op_loc, اظهار.قدر, idx);

	  c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس,
				     "expected %<]%>");

	  شروعات = اظهار.get_شروعات ();
	  پڄاڻي = parser->ٽوڪن_buf[0].location;
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	  اظهار.original_ڪوڊ = ERROR_MARK;
	  اظهار.original_type = عدم;
	  اظهار.m_decimal = 0;
	  اكسر;
	حالة CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    لكل (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_وڻ;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_نقاب = 0;
	    إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = عدم;
	    وإلا إذا (وڻ_ڪوڊ (اظهار.قدر) == FUNCTION_DECL
		     && fndecl_built_اندريون_p (اظهار.قدر, BUILT_اندريون_CLASSIFY_TYPE)
		     && c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		اندريون_alignof++;
		بنية c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		اندريون_alignof--;
		بنية c_typespec ret;
		ret.اظهار = NULL_وڻ;
		ret.spec = error_mark_ڳنڍ;
		ret.اظهار_const_operands = خطأ;
		إذا (type != عدم)
		  ret.spec = groktypename (type, &ret.اظهار,
					   &ret.اظهار_const_operands);
		parens.skip_until_مليو_close (parser);
		اظهار.قدر = build_int_cst (integer_type_ڳنڍ,
					    type_منزل_class (ret.spec));
		اكسر;
	      }
	    وإلا
	      exprlist = c_parser_اظهار_list (parser, سچ, خطأ, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_نقاب);
	    parens.skip_until_مليو_close (parser);
	  }
	  orig_اظهار = اظهار;
	  mark_exp_read (اظهار.قدر);
	  إذا (warn_sizeof_اشارو_memaccess)
	    sizeof_اشارو_memaccess_warning (sizeof_arg_loc,
					      اظهار.قدر, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  إذا (وڻ_ڪوڊ (اظهار.قدر) == FUNCTION_DECL)
	    {
	      إذا (fndecl_built_اندريون_p (اظهار.قدر, BUILT_اندريون_MEMSET)
		  && vec_محفوظ_ڊيگهائي (exprlist) == 3)
		{
		  وڻ arg0 = (*exprlist)[0];
		  وڻ arg2 = (*exprlist)[2];
		  warn_for_memset (اظهار_loc, arg0, arg2, literal_zero_نقاب);
		}
	      إذا (warn_absolute_قدر
		  && fndecl_built_اندريون_p (اظهار.قدر, BUILT_اندريون_عام)
		  && vec_محفوظ_ڊيگهائي (exprlist) == 1)
		warn_for_abs (اظهار_loc, اظهار.قدر, (*exprlist)[0]);
	      إذا (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->اندريون_intervening_ڪوڊ
		  && omp_runtime_api_call (اظهار.قدر))
		{
		  error_at (اظهار_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = سچ;
		}
	      إذا (warn_calloc_transposed_دليلون)
		إذا (وڻ attr = lookup_attribute ("alloc_size",
						  TYPE_خاصيتون
						    (وڻ_TYPE (اظهار.قدر))))
		  إذا (وڻ_قدر (attr) && وڻ_CHAIN (وڻ_قدر (attr)))
		    warn_for_calloc (sizeof_arg_loc, اظهار.قدر, exprlist,
				     sizeof_arg, attr);
	    }

	  شروعات = اظهار.get_شروعات ();
	  پڄاڻي = parser->ٽوڪن_buf[0].get_پڄاڻي ();
	  اظهار.قدر
	    = c_build_function_call_vec (اظهار_loc, arg_loc, اظهار.قدر,
					 exprlist, origtypes);
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	  اظهار.m_decimal = 0;

	  اظهار.original_ڪوڊ = ERROR_MARK;
	  إذا (وڻ_ڪوڊ (اظهار.قدر) == INTEGER_CST
	      && وڻ_ڪوڊ (orig_اظهار.قدر) == FUNCTION_DECL
	      && fndecl_built_اندريون_p (orig_اظهار.قدر, BUILT_اندريون_CONSTANT_P))
	    اظهار.original_ڪوڊ = C_MAYBE_CONST_اظهار;
	  اظهار.original_type = عدم;
	  إذا (exprlist)
	    {
	      release_وڻ_ويڪٽر (exprlist);
	      release_وڻ_ويڪٽر (origtypes);
	    }
	  arg_loc.release ();
	  اكسر;
	حالة CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  اظهار = default_function_array_conversion (اظهار_loc, اظهار);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->قدر;
	      comp_loc = comp_tok->location;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      اظهار.سيٽ_error ();
	      اظهار.original_ڪوڊ = ERROR_MARK;
              اظهار.original_type = عدم;
	      أرجع اظهار;
	    }
	  شروعات = اظهار.get_شروعات ();
	  پڄاڻي = c_parser_peek_token (parser)->get_پڄاڻي ();
	  c_parser_consume_token (parser);
	  اظهار.قدر = build_component_ref (op_loc, اظهار.قدر, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	  اظهار.original_ڪوڊ = ERROR_MARK;
	  إذا (وڻ_ڪوڊ (اظهار.قدر) != COMPONENT_REF)
	    اظهار.original_type = عدم;
	  وإلا
	    {
	      /* Remember the original type of a bitfield.  */
	      وڻ ميدان_2 = وڻ_عمليو (اظهار.قدر, 1);
	      إذا (وڻ_ڪوڊ (ميدان_2) != ميدان_DECL)
		اظهار.original_type = عدم;
	      وإلا
		اظهار.original_type = DECL_ٻٽو_انگ_ميدان_TYPE (ميدان_2);
	    }
	  اظهار.m_decimal = 0;
	  اكسر;
	حالة CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, سچ, خطأ);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->قدر;
	      comp_loc = comp_tok->location;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier");
	      اظهار.سيٽ_error ();
	      اظهار.original_ڪوڊ = ERROR_MARK;
	      اظهار.original_type = عدم;
	      أرجع اظهار;
	    }
	  شروعات = اظهار.get_شروعات ();
	  پڄاڻي = c_parser_peek_token (parser)->get_پڄاڻي ();
	  c_parser_consume_token (parser);
	  اظهار.قدر = build_component_ref (op_loc,
					    build_اڻسڌو_ref (op_loc,
								اظهار.قدر,
								RO_ARROW),
					    ident, comp_loc,
					    اظهار.get_location ());
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	  اظهار.original_ڪوڊ = ERROR_MARK;
	  إذا (وڻ_ڪوڊ (اظهار.قدر) != COMPONENT_REF)
	    اظهار.original_type = عدم;
	  وإلا
	    {
	      /* Remember the original type of a bitfield.  */
	      وڻ ميدان_2 = وڻ_عمليو (اظهار.قدر, 1);
	      إذا (وڻ_ڪوڊ (ميدان_2) != ميدان_DECL)
		اظهار.original_type = عدم;
	      وإلا
		اظهار.original_type = DECL_ٻٽو_انگ_ميدان_TYPE (ميدان_2);
	    }
	  اظهار.m_decimal = 0;
	  اكسر;
	حالة CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  شروعات = اظهار.get_شروعات ();
	  پڄاڻي = c_parser_peek_token (parser)->get_پڄاڻي ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (اظهار.قدر);
	  اظهار = default_function_array_conversion (اظهار_loc, اظهار);
	  اظهار.قدر = build_unary_op (op_loc, POSTINCREMENT_اظهار,
				       اظهار.قدر, خطأ);
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	  اظهار.original_ڪوڊ = ERROR_MARK;
	  اظهار.original_type = عدم;
	  اكسر;
	حالة CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  شروعات = اظهار.get_شروعات ();
	  پڄاڻي = c_parser_peek_token (parser)->get_پڄاڻي ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (اظهار.قدر);
	  اظهار = default_function_array_conversion (اظهار_loc, اظهار);
	  اظهار.قدر = build_unary_op (op_loc, POSTDECREMENT_اظهار,
				       اظهار.قدر, خطأ);
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	  اظهار.original_ڪوڊ = ERROR_MARK;
	  اظهار.original_type = عدم;
	  اكسر;
	افتراضي:
	  أرجع اظهار;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

ساكن بنية c_اظهار
c_parser_اظهار (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  بنية c_اظهار اظهار;
  اظهار = c_parser_اظهار_no_commas (parser, عدم);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    اظهار = convert_lvalue_منزل_rvalue (tloc, اظهار, سچ, خطأ);
  طالما (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    {
      بنية c_اظهار ايندڙ;
      وڻ lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t اظهار_loc;
      c_parser_consume_token (parser);
      اظهار_loc = c_parser_peek_token (parser)->location;
      lhsval = اظهار.قدر;
      طالما (وڻ_ڪوڊ (lhsval) == COMPOUND_اظهار
	     || وڻ_ڪوڊ (lhsval) == NOP_اظهار)
	{
	  إذا (وڻ_ڪوڊ (lhsval) == COMPOUND_اظهار)
	    lhsval = وڻ_عمليو (lhsval, 1);
	  وإلا
	    lhsval = وڻ_عمليو (lhsval, 0);
	}
      إذا (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  وڻ val = embed->قدر;
	  بنانشان آخري = RAW_معلومات_ڊيگهائي (val) - 1;
	  ايندڙ.قدر = build_int_cst (وڻ_TYPE (val),
				      RAW_معلومات_UCHAR_ELT (val, آخري));
	  ايندڙ.original_type = integer_type_ڳنڍ;
	  c_parser_consume_token (parser);
	}
      وإلا
	{
	  ايندڙ = c_parser_اظهار_no_commas (parser, عدم);
	  ايندڙ = convert_lvalue_منزل_rvalue (اظهار_loc, ايندڙ, سچ, خطأ);
	}
      اظهار.قدر = build_compound_اظهار (loc, اظهار.قدر, ايندڙ.قدر);
      اظهار.original_ڪوڊ = COMPOUND_اظهار;
      اظهار.original_type = ايندڙ.original_type;
      اظهار.m_decimal = 0;
    }
  أرجع اظهار;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

ساكن بنية c_اظهار
c_parser_اظهار_conv (c_parser *parser)
{
  بنية c_اظهار اظهار;
  location_t loc = c_parser_peek_token (parser)->location;
  اظهار = c_parser_اظهار (parser);
  اظهار = convert_lvalue_منزل_rvalue (loc, اظهار, سچ, خطأ);
  أرجع اظهار;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

ساكن مضمن فراغ
c_parser_check_literal_zero (c_parser *parser, بنانشان *literal_zero_نقاب,
			     بنانشان صحيح idx)
{
  إذا (idx >= HOST_بٽ_في_INT)
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
      إذا (integer_zerop (tok->قدر)
	  && !وڻ_حد_کان_مٿي (tok->قدر)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_نقاب |= 1U << idx;
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

ساكن vec<وڻ, va_gc> *
c_parser_اظهار_list (c_parser *parser, منطقي convert_p, منطقي fold_p,
		    vec<وڻ, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, وڻ *sizeof_arg,
		    vec<location_t> *locations,
		    بنانشان صحيح *literal_zero_نقاب)
{
  vec<وڻ, va_gc> *ret;
  vec<وڻ, va_gc> *orig_types;
  بنية c_اظهار اظهار;
  بنانشان صحيح idx = 0;
  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = خطأ;

  ret = make_وڻ_ويڪٽر ();
  إذا (p_orig_types == عدم)
    orig_types = عدم;
  وإلا
    orig_types = make_وڻ_ويڪٽر ();

  إذا (literal_zero_نقاب)
    c_parser_check_literal_zero (parser, literal_zero_نقاب, 0);
  اظهار = c_parser_اظهار_no_commas (parser, عدم);
  إذا (convert_p)
    اظهار = convert_lvalue_منزل_rvalue (اظهار.get_location (), اظهار, سچ, سچ);
  إذا (fold_p)
    اظهار.قدر = c_fully_fold (اظهار.قدر, خطأ, عدم);
  ret->تيز_ڌڪو (اظهار.قدر);
  إذا (orig_types)
    orig_types->تيز_ڌڪو (اظهار.original_type);
  إذا (locations)
    locations->محفوظ_ڌڪو (اظهار.get_location ());
  إذا (sizeof_arg != عدم
      && (اظهار.original_ڪوڊ == SIZEOF_اظهار
	  || اظهار.original_ڪوڊ == PAREN_SIZEOF_اظهار))
    {
      sizeof_arg[0] = c_آخري_sizeof_arg;
      sizeof_arg_loc[0] = c_آخري_sizeof_loc;
    }
  طالما (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  وڻ قدر = embed->قدر;
	  اظهار.original_ڪوڊ = INTEGER_CST;
	  اظهار.original_type = integer_type_ڳنڍ;
	  اظهار.قدر = NULL_وڻ;
	  سيٽ_c_اظهار_ذريعو_range (&اظهار, embed->get_range ());
	  اظهار.m_decimal = 0;
	  لكل (بنانشان صحيح i = 0; i < (بنانشان) RAW_معلومات_ڊيگهائي (قدر); i++)
	    {
	      إذا (literal_zero_نقاب
		  && idx + 1 < HOST_بٽ_في_INT
		  && RAW_معلومات_اشارو (قدر)[i] == 0)
		*literal_zero_نقاب |= 1U << (idx + 1);
	      اظهار.قدر = build_int_cst (integer_type_ڳنڍ,
					  RAW_معلومات_UCHAR_ELT (قدر, i));
	      vec_محفوظ_ڌڪو (ret, اظهار.قدر);
	      إذا (orig_types)
		vec_محفوظ_ڌڪو (orig_types, اظهار.original_type);
	      إذا (locations)
		locations->محفوظ_ڌڪو (اظهار.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  استمر;
	}
      إذا (literal_zero_نقاب)
	c_parser_check_literal_zero (parser, literal_zero_نقاب, idx + 1);
      اظهار = c_parser_اظهار_no_commas (parser, عدم);
      إذا (convert_p)
	اظهار = convert_lvalue_منزل_rvalue (اظهار.get_location (), اظهار, سچ,
					 سچ);
      إذا (fold_p)
	اظهار.قدر = c_fully_fold (اظهار.قدر, خطأ, عدم);
      vec_محفوظ_ڌڪو (ret, اظهار.قدر);
      إذا (orig_types)
	vec_محفوظ_ڌڪو (orig_types, اظهار.original_type);
      إذا (locations)
	locations->محفوظ_ڌڪو (اظهار.get_location ());
      إذا (++idx < 6
	  && sizeof_arg != عدم
	  && (اظهار.original_ڪوڊ == SIZEOF_اظهار
	      || اظهار.original_ڪوڊ == PAREN_SIZEOF_اظهار))
	{
	  sizeof_arg[idx] = c_آخري_sizeof_arg;
	  sizeof_arg_loc[idx] = c_آخري_sizeof_loc;
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
c_parser_objc_class_definition (c_parser *parser, وڻ خاصيتون)
{
  منطقي iface_p;
  وڻ id1;
  وڻ superclass;
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = سچ;
  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = خطأ;
  وإلا
    gcc_unreachable ();

  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      أرجع;
    }
  id1 = c_parser_peek_token (parser)->قدر;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      وڻ id2;
      وڻ proto = NULL_وڻ;
      matching_parens parens;
      parens.consume_open (parser);
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	{
	  إذا (iface_p && c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_وڻ;
	    }
	  وإلا
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	      أرجع;
	    }
	}
      وإلا
	{
	  id2 = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_مليو_close (parser);
      إذا (!iface_p)
	{
	  objc_شروعات_category_implementation (id1, id2);
	  أرجع;
	}
      إذا (c_parser_ايندڙ_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_شروعات_category_interface (id1, id2, proto, خاصيتون);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_پڇاڙي, "expected %<@end%>");
      objc_پڄاڻي_interface ();
      أرجع;
    }
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  أرجع;
	}
      superclass = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
    }
  وإلا
    superclass = NULL_وڻ;
  إذا (iface_p)
    {
      وڻ proto = NULL_وڻ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_شروعات_class_interface (id1, loc1, superclass, proto, خاصيتون);
    }
  وإلا
    objc_شروعات_class_implementation (id1, superclass);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  إذا (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_پڇاڙي, "expected %<@end%>");
      objc_پڄاڻي_interface ();
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
  gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_EOF))
    {
      وڻ decls;
      /* Parse any stray semicolon.  */
      إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  استمر;
	}
      /* Stop if at the end of the instance variables.  */
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  اكسر;
	}
      /* Parse any objc-visibility-spec.  */
      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_ذاتي))
	{
	  c_parser_consume_token (parser);
	  objc_سيٽ_visibility (OBJC_IVAR_VIS_ذاتي);
	  استمر;
	}
      وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_سيٽ_visibility (OBJC_IVAR_VIS_PROTECTED);
	  استمر;
	}
      وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_عوامي))
	{
	  c_parser_consume_token (parser);
	  objc_سيٽ_visibility (OBJC_IVAR_VIS_عوامي);
	  استمر;
	}
      وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_سيٽ_visibility (OBJC_IVAR_VIS_PACKAGE);
	  استمر;
	}
      وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, عدم, NULL_وڻ);
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
	  إذا (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_چورس)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = خطأ;
	  استمر;
	}
      وإلا
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  وڻ ivar = nreverse (decls);
	  لكل (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_جوڙيو_instance_variable (copy_ڳنڍ (ivar));
	}
      c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

ساكن فراغ
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  طالما (سچ)
    {
      وڻ id;
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);
	  parser->error = خطأ;
	  أرجع;
	}
      id = c_parser_peek_token (parser)->قدر;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

ساكن فراغ
c_parser_objc_alias_declaration (c_parser *parser)
{
  وڻ id1, id2;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);
      أرجع;
    }
  id1 = c_parser_peek_token (parser)->قدر;
  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);
      أرجع;
    }
  id2 = c_parser_peek_token (parser)->قدر;
  c_parser_consume_token (parser);
  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
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
c_parser_objc_protocol_definition (c_parser *parser, وڻ خاصيتون)
{
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      أرجع;
    }
  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      طالما (سچ)
	{
	  وڻ id;
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      اكسر;
	    }
	  id = c_parser_peek_token (parser)->قدر;
	  objc_declare_protocol (id, خاصيتون);
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  وإلا
    {
      وڻ id = c_parser_peek_token (parser)->قدر;
      وڻ proto = NULL_وڻ;
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = سچ;
      objc_شروعات_protocol (id, proto, خاصيتون);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_پڇاڙي, "expected %<@end%>");
      parser->objc_pq_context = خطأ;
      objc_پڄاڻي_interface ();
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
c_parser_objc_طريقو_type (c_parser *parser)
{
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      أرجع سچ;
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
c_parser_objc_طريقو_definition (c_parser *parser)
{
  منطقي is_class_طريقو = c_parser_objc_طريقو_type (parser);
  وڻ decl, خاصيتون = NULL_وڻ, اظهار = NULL_وڻ;
  parser->objc_pq_context = سچ;
  decl = c_parser_objc_طريقو_decl (parser, is_class_طريقو, &خاصيتون,
				    &اظهار);
  إذا (decl == error_mark_ڳنڍ)
    أرجع;  /* Bail here. */

  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  إذا (!c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      أرجع;
    }

  parser->objc_pq_context = خطأ;
  إذا (objc_شروعات_طريقو_definition (is_class_طريقو, decl, خاصيتون, اظهار))
    {
      جوڙيو_stmt (c_parser_compound_statement (parser));
      objc_پڄاڻي_طريقو_definition (current_function_decl);
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
خالي_جايون
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
  طالما (سچ)
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
	  c_parser_pragma (parser, pragma_external, عدم, NULL_وڻ);
	  اكسر;
	حالة CPP_EOF:
	  أرجع;
	افتراضي:
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_پڇاڙي))
	    أرجع;
	  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_سيٽ_طريقو_opt (سچ);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_سيٽ_طريقو_opt (خطأ);
	      c_parser_consume_token (parser);
	    }
	  وإلا
	    c_parser_declaration_or_fndef (parser, خطأ, خطأ, سچ,
					   خطأ, سچ, خطأ);
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
  منطقي is_class_طريقو = c_parser_objc_طريقو_type (parser);
  وڻ decl, خاصيتون = NULL_وڻ;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = سچ;
  decl = c_parser_objc_طريقو_decl (parser, is_class_طريقو, &خاصيتون,
				    عدم);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = خطأ;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      أرجع;
    }

  إذا (decl != error_mark_ڳنڍ)
    objc_جوڙيو_طريقو_declaration (is_class_طريقو, decl, خاصيتون);

  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

ساكن منطقي
c_parser_objc_maybe_طريقو_خاصيتون (c_parser* parser, وڻ* خاصيتون)
{
  منطقي bad = خطأ;
  إذا (*خاصيتون)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *خاصيتون = NULL_وڻ;
      bad = سچ;
    }

  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
    *خاصيتون = c_parser_gnu_خاصيتون (parser);

  /* If there were no attributes here, just report any earlier error.  */
  إذا (*خاصيتون == NULL_وڻ || bad)
    أرجع bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)
      || c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    أرجع bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  أرجع سچ;
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
خالي_جايون
     objc-opt-parms , parameter-declaration

   objc-optellipsis:
خالي_جايون
     , ...
*/

ساكن وڻ
c_parser_objc_طريقو_decl (c_parser *parser, منطقي is_class_طريقو,
			   وڻ *خاصيتون, وڻ *اظهار)
{
  وڻ type = NULL_وڻ;
  وڻ sel;
  وڻ parms = NULL_وڻ;
  منطقي ellipsis = خطأ;
  منطقي attr_err = خطأ;

  *خاصيتون = NULL_وڻ;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      type = c_parser_objc_type_name (parser);
      parens.skip_until_مليو_close (parser);
    }
  sel = c_parser_objc_selector (parser);
  /* If there is no selector, or a colon follows, we have an
     objc-keyword-selector.  If there is a selector, and a colon does
     not follow, that selector ends the objc-method-decl.  */
  إذا (!sel || c_parser_ايندڙ_token_is (parser, CPP_COLON))
    {
      وڻ tsel = sel;
      وڻ list = NULL_وڻ;
      طالما (سچ)
	{
	  وڻ atype = NULL_وڻ, id, keyworddecl;
	  وڻ param_attr = NULL_وڻ;
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    اكسر;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_خاصيتون (parser);
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      أرجع error_mark_ڳنڍ;
	    }
	  id = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  إذا (!tsel && c_parser_ايندڙ_token_is_not (parser, CPP_COLON))
	    اكسر;
	}

      attr_err |= c_parser_objc_maybe_طريقو_خاصيتون (parser, خاصيتون) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_ڳنڍ (وڻ_LIST);
      طالما (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	{
	  بنية c_parm *parm;
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = سچ;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_طريقو_خاصيتون
						(parser, خاصيتون) ;
	      اكسر;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_وڻ, خطأ);
	  إذا (parm == عدم)
	    اكسر;
	  parms = chainon (parms,
			   build_وڻ_list (NULL_وڻ, grokparm (parm, اظهار)));
	}
      sel = list;
    }
  وإلا
    attr_err |= c_parser_objc_maybe_طريقو_خاصيتون (parser, خاصيتون) ;

  إذا (sel == عدم)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      أرجع error_mark_ڳنڍ;
    }

  إذا (attr_err)
    أرجع error_mark_ڳنڍ;

  أرجع objc_build_طريقو_signature (is_class_طريقو, type, sel, parms, ellipsis);
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

ساكن وڻ
c_parser_objc_type_name (c_parser *parser)
{
  وڻ quals = NULL_وڻ;
  بنية c_type_name *type_name = عدم;
  وڻ type = NULL_وڻ;
  طالما (سچ)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_KEYWORD
	  && (token->keyword == RID_اندريون
	      || token->keyword == RID_ٻاهريون
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_وڻ_list (NULL_وڻ, token->قدر), quals);
	  c_parser_consume_token (parser);
	}
      وإلا
	اكسر;
    }
  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  إذا (type_name)
    type = groktypename (type_name, عدم, عدم);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  إذا (type == error_mark_ڳنڍ)
    type = NULL_وڻ;

  أرجع build_وڻ_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

ساكن وڻ
c_parser_objc_protocol_refs (c_parser *parser)
{
  وڻ list = NULL_وڻ;
  gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  طالما (سچ)
    {
      وڻ id;
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}
      id = c_parser_peek_token (parser)->قدر;
      list = chainon (list, build_وڻ_list (NULL_وڻ, id));
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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
  وڻ stmt;

  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  طالما (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_CATCH))
    {
      بنية c_parm *parm;
      وڻ parameter_declaration = error_mark_ڳنڍ;
      منطقي ڏٺل_open_paren = خطأ;

      c_parser_consume_token (parser);
      matching_parens parens;
      إذا (!parens.require_open (parser))
	ڏٺل_open_paren = سچ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_وڻ;
	}
      وإلا
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_وڻ, خطأ);
	  إذا (parm == عدم)
	    parameter_declaration = error_mark_ڳنڍ;
	  وإلا
	    parameter_declaration = grokparm (parm, عدم);
	}
      إذا (ڏٺل_open_paren)
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
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      إذا (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_پڄاڻي_catch_clause ();
    }
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_FINALLY))
    {
      c_parser_consume_token (parser);
      location = c_parser_peek_token (parser)->location;
      stmt = c_parser_compound_statement (parser);
      objc_build_finally_clause (location, stmt);
    }
  objc_پڄاڻي_try_stmt ();
}

/* Parse an objc-synchronized-statement.

   objc-synchronized-statement:
     @synchronized ( expression ) compound-statement
*/

ساكن فراغ
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  وڻ اظهار, stmt;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      بنية c_اظهار ce = c_parser_اظهار (parser);
      ce = convert_lvalue_منزل_rvalue (loc, ce, خطأ, خطأ);
      اظهار = ce.قدر;
      اظهار = c_fully_fold (اظهار, خطأ, عدم);
      parens.skip_until_مليو_close (parser);
    }
  وإلا
    اظهار = error_mark_ڳنڍ;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, اظهار, stmt);
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

ساكن وڻ
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  وڻ قدر = token->قدر;
  إذا (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      أرجع قدر;
    }
  إذا (token->type != CPP_KEYWORD)
    أرجع NULL_وڻ;
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
    حالة RID_اندريون:
    حالة RID_ٻاهريون:
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
      أرجع قدر;
    افتراضي:
      أرجع NULL_وڻ;
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

ساكن وڻ
c_parser_objc_selector_arg (c_parser *parser)
{
  وڻ sel = c_parser_objc_selector (parser);
  وڻ list = NULL_وڻ;
  إذا (sel
      && c_parser_ايندڙ_token_is_not (parser, CPP_COLON)
      && c_parser_ايندڙ_token_is_not (parser, CPP_SCOPE))
    أرجع sel;
  طالما (سچ)
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_وڻ_list (sel, NULL_وڻ));
	  list = chainon (list, build_وڻ_list (NULL_وڻ, NULL_وڻ));
	}
      وإلا
	{
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    أرجع list;
	  list = chainon (list, build_وڻ_list (sel, NULL_وڻ));
	}
      sel = c_parser_objc_selector (parser);
      إذا (!sel
	  && c_parser_ايندڙ_token_is_not (parser, CPP_COLON)
	  && c_parser_ايندڙ_token_is_not (parser, CPP_SCOPE))
	اكسر;
    }
  أرجع list;
}

/* Parse an objc-receiver.

   objc-receiver:
اظهار
     class-name
     type-name
*/

ساكن وڻ
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_قسم == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_قسم == C_ID_CLASSNAME))
    {
      وڻ id = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      أرجع objc_get_class_reference (id);
    }
  بنية c_اظهار ce = c_parser_اظهار (parser);
  ce = convert_lvalue_منزل_rvalue (loc, ce, خطأ, خطأ);
  أرجع c_fully_fold (ce.قدر, خطأ, عدم);
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

ساكن وڻ
c_parser_objc_پيغام_دليلون (c_parser *parser)
{
  وڻ sel = c_parser_objc_selector (parser);
  وڻ list = NULL_وڻ;
  إذا (sel && c_parser_ايندڙ_token_is_not (parser, CPP_COLON))
    أرجع sel;
  طالما (سچ)
    {
      وڻ keywordexpr;
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	أرجع error_mark_ڳنڍ;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_وڻ_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      إذا (!sel && c_parser_ايندڙ_token_is_not (parser, CPP_COLON))
	اكسر;
    }
  أرجع list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

ساكن وڻ
c_parser_objc_keywordexpr (c_parser *parser)
{
  وڻ ret;
  vec<وڻ, va_gc> *اظهار_list = c_parser_اظهار_list (parser, سچ, سچ,
						عدم, عدم, عدم, عدم);
  إذا (vec_محفوظ_ڊيگهائي (اظهار_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*اظهار_list)[0];
    }
  وإلا
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_وڻ_list_vec (اظهار_list);
    }
  release_وڻ_ويڪٽر (اظهار_list);
  أرجع ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
ساكن منطقي
c_parser_objc_diagnose_bad_element_اڳياڙي (c_parser *parser,
					   بنية c_declspecs *specs)
{
  إذا (!specs->declspecs_ڏٺل_p || specs->non_sc_ڏٺل_p
      || specs->typespec_قسم != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
      أرجع سچ;
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
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  منطقي syntax_error = خطأ;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_شروعات = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = سچ;

      /* Allow @property (), with a warning.  */
      location_t attr_پڇاڙي = c_parser_peek_token (parser)->location;

      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_پڇاڙي, attr_شروعات, attr_پڇاڙي);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      وإلا
	طالما (سچ)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_شروعات = token->location;
	    attr_پڇاڙي = get_پڄاڻي (token->location);
	    location_t attr_comb = make_location (attr_شروعات, attr_شروعات,
						  attr_پڇاڙي);

	    إذا (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		إذا (token->type == CPP_CLOSE_PAREN)
		  اكسر;
		c_parser_consume_token (parser);
		استمر;
	      }

	    وڻ attr_name = NULL_وڻ;
	    تعداد rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    منطقي جوڙيو_at = خطأ;
	    إذا (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		إذا (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->قدر;
		    جوڙيو_at = سچ;
		  }
		وإلا
		  attr_name = ridpointers[(صحيح)keyword];
	      }
	    وإلا إذا (token->type == CPP_NAME)
	      attr_name = token->قدر;
	    c_parser_consume_token (parser);

	    تعداد objc_property_attribute_قسم prop_قسم
	      = objc_prop_attr_قسم_for_rid (keyword);
	    property_attribute_info *prop
	      = جديد property_attribute_info (attr_name, attr_comb, prop_قسم);
	    prop_attr_list.محفوظ_ڌڪو (prop);

	    وڻ meth_name;
	    بدل (prop->prop_قسم)
	      {
	      افتراضي: اكسر;
	      حالة OBJC_PROPERTY_ATTR_UNKNOWN:
		إذا (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    جوڙيو_at ? "@" : "", IDENTIFIER_اشارو (attr_name));
		وإلا
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = سچ;
		اكسر;

	      حالة OBJC_PROPERTY_ATTR_GETTER:
	      حالة OBJC_PROPERTY_ATTR_SETTER:
		إذا (c_parser_ايندڙ_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_پڇاڙي, attr_شروعات, attr_پڇاڙي);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = سچ;
		    اكسر;
		  }
		token = c_parser_peek_token (parser);
		attr_پڇاڙي = token->location;
		c_parser_consume_token (parser); /* eat the = */
		إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_پڇاڙي, attr_شروعات, attr_پڇاڙي);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = سچ;
		    اكسر;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_پڇاڙي = get_پڄاڻي (token->location);
		meth_name = token->قدر;
		c_parser_consume_token (parser);
		إذا (prop->prop_قسم == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_پڇاڙي, attr_شروعات,
						   attr_پڇاڙي);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = سچ;
		      }
		    وإلا
		      {
			attr_پڇاڙي = get_پڄاڻي (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_شروعات, attr_شروعات,
					       attr_پڇاڙي);
		  }
		وإلا
		  attr_comb = make_location (attr_شروعات, attr_شروعات,
					       attr_پڇاڙي);
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
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      parser->objc_property_attr_context = خطأ;

      إذا (syntax_error && c_parser_ايندڙ_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      وإلا
	syntax_error = خطأ, parens.skip_until_مليو_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  وڻ properties = c_parser_struct_declaration (parser, عدم);

  إذا (properties == error_mark_ڳنڍ)
    c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);
  وإلا
    {
      إذا (properties == NULL_وڻ)
	c_parser_error (parser, "expected identifier");
      وإلا
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  لكل (; properties; properties = وڻ_CHAIN (properties))
	    objc_جوڙيو_property_declaration (loc, copy_ڳنڍ (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  طالما (!prop_attr_list.is_خالي_جايون())
    ميٽيو prop_attr_list.ڪڍو ();
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
  وڻ list = NULL_وڻ;
  location_t loc;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  طالما (سچ)
    {
      وڻ property, ivar;
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = خطأ;
	  أرجع;
	}
      property = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);
	      parser->error = خطأ;
	      أرجع;
	    }
	  ivar = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	}
      وإلا
	ivar = NULL_وڻ;
      list = chainon (list, build_وڻ_list (ivar, property));
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_جوڙيو_synthesize_declaration (loc, list);
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
  وڻ list = NULL_وڻ;
  location_t loc;
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  طالما (سچ)
    {
      وڻ property;
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);
	  parser->error = خطأ;
	  أرجع;
	}
      property = c_parser_peek_token (parser)->قدر;
      list = chainon (list, build_وڻ_list (NULL_وڻ, property));
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_جوڙيو_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

ساكن منطقي
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_منزل_pragma_eol (parser);
  أرجع سچ;
}

/* Parse a pragma GCC novector.  */

ساكن منطقي
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_منزل_pragma_eol (parser);
  أرجع سچ;
}

/* Parse a pragma GCC unroll.  */

ساكن بنانشان ننڍو
c_parser_pragma_unroll (c_parser *parser)
{
  بنانشان ننڍو unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  وڻ اظهار = c_parser_اظهار_no_commas (parser, عدم).قدر;
  mark_exp_read (اظهار);
  اظهار = c_fully_fold (اظهار, خطأ, عدم);
  HOST_WIDE_INT lunroll = 0;
  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (اظهار))
      || وڻ_ڪوڊ (اظهار) != INTEGER_CST
      || (lunroll = وڻ_منزل_shwi (اظهار)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  وإلا
    {
      unroll = (بنانشان ننڍو)lunroll;
      إذا (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_منزل_pragma_eol (parser);
  أرجع unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

ساكن منطقي
c_parser_pragma (c_parser *parser, تعداد pragma_context context, منطقي *if_p,
		 وڻ before_labels)
{
  بنانشان صحيح id;
  ثابت حرف *construct = عدم;

  داخلا_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_قسم;
  gcc_assert (id != PRAGMA_NONE);
  إذا (parser->omp_for_parse_state
      && parser->omp_for_parse_state->اندريون_intervening_ڪوڊ
      && id >= PRAGMA_OMP_شروعات && id <= PRAGMA_OMP_آخري
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	داخلا_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = سچ;
      c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;
    }

  بدل (id)
    {
    حالة PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      أرجع خطأ;

    حالة PRAGMA_OACC_ENTER_معلومات:
      إذا (context != pragma_compound)
	{
	  construct = "acc enter data";
	اندريون_compound:
	  إذا (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
	      أرجع سچ;
	    }
	  اذهب bad_stmt;
	}
      c_parser_oacc_enter_exit_معلومات (parser, سچ);
      أرجع خطأ;

    حالة PRAGMA_OACC_EXIT_معلومات:
      إذا (context != pragma_compound)
	{
	  construct = "acc exit data";
	  اذهب اندريون_compound;
	}
      c_parser_oacc_enter_exit_معلومات (parser, خطأ);
      أرجع خطأ;

    حالة PRAGMA_OACC_ROUTINE:
      إذا (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
	  أرجع خطأ;
	}
      c_parser_oacc_routine (parser, context);
      أرجع خطأ;

    حالة PRAGMA_OACC_UPDATE:
      إذا (context != pragma_compound)
	{
	  construct = "acc update";
	  اذهب اندريون_compound;
	}
      c_parser_oacc_update (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_BARRIER:
      إذا (context != pragma_compound)
	{
	  construct = "omp barrier";
	  اذهب اندريون_compound;
	}
      c_parser_omp_barrier (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_DEPOBJ:
      إذا (context != pragma_compound)
	{
	  construct = "omp depobj";
	  اذهب اندريون_compound;
	}
      c_parser_omp_depobj (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_FLUSH:
      إذا (context != pragma_compound)
	{
	  construct = "omp flush";
	  اذهب اندريون_compound;
	}
      c_parser_omp_flush (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_INTEROP:
      إذا (context != pragma_compound)
	{
	  construct = "omp interop";
	  اذهب اندريون_compound;
	}
      c_parser_omp_interop (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_TASKWAIT:
      إذا (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  اذهب اندريون_compound;
	}
      c_parser_omp_taskwait (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_TASKYIELD:
      إذا (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  اذهب اندريون_compound;
	}
      c_parser_omp_taskyield (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_CANCEL:
      إذا (context != pragma_compound)
	{
	  construct = "omp cancel";
	  اذهب اندريون_compound;
	}
      c_parser_omp_cancel (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_CANCELLATION_نقطو:
      أرجع c_parser_omp_cancellation_نقطو (parser, context);

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

    حالة PRAGMA_OMP_پڇاڙي:
      c_parser_omp_پڇاڙي (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_جاچ:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OMP_DECLARE:
      أرجع c_parser_omp_declare (parser, context);

    حالة PRAGMA_OMP_REQUIRES:
      إذا (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
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
	  c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
	  أرجع خطأ;
	}
      c_parser_omp_assumes (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      أرجع خطأ;

    حالة PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      أرجع سچ;

    حالة PRAGMA_OMP_ERROR:
      أرجع c_parser_omp_error (parser, context);

    حالة PRAGMA_OMP_ORDERED:
      أرجع c_parser_omp_ordered (parser, context, if_p);

    حالة PRAGMA_NOVECTOR:
    حالة PRAGMA_UNROLL:
    حالة PRAGMA_IVDEP:
      {
	منطقي novector = خطأ;
	بنانشان ننڍو unroll = 0;
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
	منطقي has_وڌيڪ = tok->type == CPP_PRAGMA;
	طالما (has_وڌيڪ)
	  {
	    بدل (tok->pragma_قسم)
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
		has_وڌيڪ = خطأ;
		اكسر;
	      }
	    tok = c_parser_peek_token (parser);
	    has_وڌيڪ = has_وڌيڪ && tok->type == CPP_PRAGMA;
	  }
	إذا (!c_parser_ايندڙ_token_is_keyword (parser, RID_FOR)
	    && !c_parser_ايندڙ_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_ايندڙ_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    أرجع خطأ;
	  }
	إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	وإلا
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      أرجع سچ;

    حالة PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
      أرجع خطأ;

    حالة PRAGMA_OACC_WAIT:
      إذا (context != pragma_compound)
	{
	  construct = "acc wait";
	  اذهب اندريون_compound;
	}
	/* FALL THROUGH.  */

    افتراضي:
      إذا (id < PRAGMA_پهريون_EXTERNAL)
	{
	  إذا (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_مليو (parser, CPP_PRAGMA_EOL, عدم);
	      أرجع خطأ;
	    }
	  c_parser_omp_construct (parser, if_p);
	  أرجع سچ;
	}
      اكسر;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = سچ;
  c_parser_skip_منزل_pragma_eol (parser);

  أرجع خطأ;
}

/* The interface the pragma parsers have to the lexer.  */

تعداد cpp_ttype
pragma_lex (وڻ *قدر, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  تعداد cpp_ttype ret = tok->type;

  *قدر = tok->قدر;
  إذا (loc)
    *loc = tok->location;

  إذا (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  وإلا إذا (ret == CPP_STRING)
    *قدر = c_parser_string_literal (the_parser, خطأ, خطأ).قدر;
  وإلا
    {
      إذا (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  أرجع ret;
}

فراغ
pragma_lex_discard_منزل_eol ()
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
  وڻ name = عدم;

  parser->lex_joined_string = سچ;
  c_parser_consume_pragma (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
    }
  وإلا
    c_parser_error (parser, "expected string literal");
  c_parser_skip_منزل_pragma_eol (parser);
  parser->lex_joined_string = خطأ;

  إذا (name)
    c_common_pch_pragma (parse_اندريون, وڻ_STRING_اشارو (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

ساكن pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause نتيجو = PRAGMA_OMP_CLAUSE_NONE;

  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AUTO))
    نتيجو = PRAGMA_OACC_CLAUSE_AUTO;
  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_IF))
    نتيجو = PRAGMA_OMP_CLAUSE_IF;
  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_DEFAULT))
    نتيجو = PRAGMA_OMP_CLAUSE_DEFAULT;
  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_FOR))
    نتيجو = PRAGMA_OMP_CLAUSE_FOR;
  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

      بدل (p[0])
	{
	حالة 'a':
	  إذا (!strcmp ("affinity", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_AFFINITY;
	  وإلا إذا (!strcmp ("aligned", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ALIGNED;
	  وإلا إذا (!strcmp ("allocate", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  وإلا إذا (!strcmp ("async", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_ASYNC;
	  وإلا إذا (!strcmp ("attach", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_ATTACH;
	  اكسر;
	حالة 'b':
	  إذا (!strcmp ("bind", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_BIND;
	  اكسر;
	حالة 'c':
	  إذا (!strcmp ("collapse", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  وإلا إذا (!strcmp ("copy", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_COPY;
	  وإلا إذا (!strcmp ("copyin", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_COPYIN;
	  وإلا إذا (!strcmp ("copyout", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_COPYOUT;
          وإلا إذا (!strcmp ("copyprivate", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  وإلا إذا (!strcmp ("create", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_CREATE;
	  اكسر;
	حالة 'd':
	  إذا (!strcmp ("defaultmap", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  وإلا إذا (!strcmp ("delete", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_DELETE;
	  وإلا إذا (!strcmp ("depend", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_DEPEND;
	  وإلا إذا (!strcmp ("destroy", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_DESTROY;
	  وإلا إذا (!strcmp ("detach", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_DETACH;
	  وإلا إذا (!strcmp ("device", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_DEVICE;
	  وإلا إذا (!strcmp ("deviceptr", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  وإلا إذا (!strcmp ("device_resident", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  وإلا إذا (!strcmp ("device_type", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  وإلا إذا (!strcmp ("dist_schedule", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_DIST_وقت_جدول;
	  وإلا إذا (!strcmp ("doacross", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_DOACROSS;
	  وإلا إذا (!strcmp ("dyn_groupprivate", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  اكسر;
	حالة 'e':
	  إذا (!strcmp ("enter", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ENTER;
	  اكسر;
	حالة 'f':
	  إذا (!strcmp ("filter", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_FILTER;
	  وإلا إذا (!strcmp ("final", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_FINAL;
	  وإلا إذا (!strcmp ("finalize", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_FINALIZE;
	  وإلا إذا (!strcmp ("firstprivate", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  وإلا إذا (!strcmp ("from", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_FROM;
	  وإلا إذا (!strcmp ("full", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ڀريل;
	  اكسر;
	حالة 'g':
	  إذا (!strcmp ("gang", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_GANG;
	  وإلا إذا (!strcmp ("grainsize", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  اكسر;
	حالة 'h':
	  إذا (!strcmp ("has_device_addr", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  وإلا إذا (!strcmp ("hint", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_HINT;
	  وإلا إذا (!strcmp ("host", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_HOST;
	  اكسر;
	حالة 'i':
	  إذا (!strcmp ("if_present", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  وإلا إذا (!strcmp ("in_reduction", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_اندريون_REDUCTION;
	  وإلا إذا (!strcmp ("inbranch", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_INBRANCH;
	  وإلا إذا (!strcmp ("independent", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  وإلا إذا (!strcmp ("indirect", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_اڻسڌو;
	  وإلا إذا (!strcmp ("init", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_INIT;
	  وإلا إذا (!strcmp ("is_device_ptr", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  وإلا إذا (!strcmp ("interop", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_INTEROP;
	  اكسر;
	حالة 'l':
	  إذا (!strcmp ("lastprivate", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  وإلا إذا (!strcmp ("linear", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_لڪيري;
	  وإلا إذا (!strcmp ("link", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_LINK;
	  وإلا إذا (!strcmp ("local", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_LOCAL;
	  اكسر;
	حالة 'm':
	  إذا (!strcmp ("map", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_MAP;
	  وإلا إذا (!strcmp ("mergeable", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  اكسر;
	حالة 'n':
	  إذا (!strcmp ("no_create", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  وإلا إذا (!strcmp ("nocontext", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  وإلا إذا (!strcmp ("nogroup", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_NOGROUP;
	  وإلا إذا (!strcmp ("nohost", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_NOHOST;
	  وإلا إذا (!strcmp ("nontemporal", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  وإلا إذا (!strcmp ("notinbranch", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  وإلا إذا (!strcmp ("novariants", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  وإلا إذا (!strcmp ("nowait", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_NOWAIT;
	  وإلا إذا (!strcmp ("num_gangs", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_انگ_GANGS;
	  وإلا إذا (!strcmp ("num_tasks", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_انگ_TASKS;
	  وإلا إذا (!strcmp ("num_teams", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_انگ_TEAMS;
	  وإلا إذا (!strcmp ("num_threads", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_انگ_ڌاڳا;
	  وإلا إذا (!strcmp ("num_workers", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_انگ_WORKERS;
	  اكسر;
	حالة 'o':
	  إذا (!strcmp ("ordered", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ORDERED;
	  وإلا إذا (!strcmp ("order", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ترتيب;
	  اكسر;
	حالة 'p':
	  إذا (!strcmp ("parallel", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_PARALLEL;
	  وإلا إذا (!strcmp ("partial", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_PARTIAL;
	  وإلا إذا (!strcmp ("present", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  وإلا إذا (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_COPY;
	  وإلا إذا (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_COPYIN;
	  وإلا إذا (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_COPYOUT;
	  وإلا إذا (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_CREATE;
	  وإلا إذا (!strcmp ("priority", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ترجيح;
	  وإلا إذا (!strcmp ("private", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ذاتي;
	  وإلا إذا (!strcmp ("proc_bind", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  اكسر;
	حالة 'r':
	  إذا (!strcmp ("reduction", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_REDUCTION;
	  اكسر;
	حالة 's':
	  إذا (!strcmp ("safelen", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_SAFELEN;
	  وإلا إذا (!strcmp ("schedule", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_وقت_جدول;
	  وإلا إذا (!strcmp ("sections", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_SECTIONS;
	  وإلا إذا (!strcmp ("self", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_SELF;
	  وإلا إذا (!strcmp ("seq", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_SEQ;
	  وإلا إذا (!strcmp ("shared", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_SHARED;
	  وإلا إذا (!strcmp ("simd", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_SIMD;
	  وإلا إذا (!strcmp ("simdlen", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  اكسر;
	حالة 't':
	  إذا (!strcmp ("task_reduction", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  وإلا إذا (!strcmp ("taskgroup", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  وإلا إذا (!strcmp ("thread_limit", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_THREAD_حد_بندي;
	  وإلا إذا (!strcmp ("threads", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_ڌاڳا;
	  وإلا إذا (!strcmp ("tile", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_TILE;
	  وإلا إذا (!strcmp ("to", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_منزل;
	  اكسر;
	حالة 'u':
	  إذا (!strcmp ("uniform", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_هڪجهڙو;
	  وإلا إذا (!strcmp ("untied", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_UNTIED;
	  وإلا إذا (!strcmp ("use", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_USE;
	  وإلا إذا (!strcmp ("use_device", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  وإلا إذا (!strcmp ("use_device_addr", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  وإلا إذا (!strcmp ("use_device_ptr", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  وإلا إذا (!strcmp ("uses_allocators", p))
	    نتيجو = PRAGMA_OMP_CLAUSE_استعمال_ڪري_ALLOCATORS;
	  اكسر;
	حالة 'v':
	  إذا (!strcmp ("vector", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_ويڪٽر;
	  وإلا إذا (!strcmp ("vector_length", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_ويڪٽر_ڊيگهائي;
	  اكسر;
	حالة 'w':
	  إذا (!strcmp ("wait", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_WAIT;
	  وإلا إذا (!strcmp ("worker", p))
	    نتيجو = PRAGMA_OACC_CLAUSE_ڪم_ڪندڙ;
	  اكسر;
	}
    }

  إذا (نتيجو != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  أرجع نتيجو;
}

/* Validate that a clause of the given type does not already exist.  */

ساكن فراغ
check_no_duplicate_clause (وڻ clauses, تعداد omp_clause_ڪوڊ ڪوڊ,
			   ثابت حرف *name)
{
  إذا (وڻ c = omp_ڳوليو_clause (clauses, ڪوڊ))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

ساكن وڻ
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, وڻ list)
{
  vec<وڻ, va_gc> *دليلون;
  وڻ t, دليلون_وڻ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  دليلون = c_parser_اظهار_list (parser, خطأ, سچ, عدم, عدم, عدم, عدم);
  دليلون_وڻ = build_وڻ_list_vec (دليلون);

  لكل (t = دليلون_وڻ; t; t = وڻ_CHAIN (t))
    {
      وڻ targ = وڻ_قدر (t);

      إذا (targ != error_mark_ڳنڍ)
	{
	  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_ڳنڍ;
	    }
	  وإلا
	    {
	      وڻ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_وڻ_ويڪٽر (دليلون);
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
  وڻ هيٺيون_bound, ڊيگهائي;
  location_t loc;
  منطقي no_colon;
  omp_dim (وڻ lb, وڻ len, location_t lo, منطقي nc)
  : هيٺيون_bound (lb), ڊيگهائي (len), loc (lo), no_colon (nc) {}
};

ساكن وڻ
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    تعداد omp_clause_ڪوڊ قسم, وڻ list,
			    منطقي map_lvalue = خطأ)
{
  auto_vec<omp_dim> dims;
  منطقي array_section_p;
  auto_vec<c_token> ٽوڪن;
  بنانشان صحيح ٽوڪن_avail = 0;
  c_token *saved_ٽوڪن = عدم;

  طالما (1)
    {
      وڻ t = NULL_وڻ;
      location_t tloc = c_parser_peek_token (parser)->location;

      إذا (قسم == OMP_CLAUSE_DEPEND || قسم == OMP_CLAUSE_AFFINITY)
	{
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
	    {
	      بنية c_اظهار اظهار;
	      إذا (قسم == OMP_CLAUSE_DEPEND
		  && c_parser_ايندڙ_token_is_keyword (parser,
						     RID_OMP_ALL_يادگيري)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  اظهار.قدر = ridpointers[RID_OMP_ALL_يادگيري];
		  c_parser_consume_token (parser);
		}
	      وإلا
		اظهار = c_parser_اظهار_no_commas (parser, عدم);
	      إذا (اظهار.قدر != error_mark_ڳنڍ)
		{
		  وڻ u = build_omp_clause (clause_loc, قسم);
		  OMP_CLAUSE_DECL (u) = اظهار.قدر;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COMMA))
		اكسر;

	      c_parser_consume_token (parser);
	      استمر;
	    }

	  ٽوڪن.truncate (0);
	  بنانشان صحيح nesting_اونهائي = 0;
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
		حالة CPP_OPEN_چورس:
		  ++nesting_اونهائي;
		  اذهب جوڙيو;
		حالة CPP_CLOSE_BRACE:
		حالة CPP_CLOSE_PAREN:
		حالة CPP_CLOSE_چورس:
		  إذا (nesting_اونهائي-- == 0)
		    اكسر;
		  اذهب جوڙيو;
		حالة CPP_COMMA:
		  إذا (nesting_اونهائي == 0)
		    اكسر;
		  اذهب جوڙيو;
		افتراضي:
		جوڙيو:
		  ٽوڪن.محفوظ_ڌڪو (*token);
		  c_parser_consume_token (parser);
		  استمر;
		}
	      اكسر;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, حجم (eof_token));
	  eof_token.type = CPP_EOF;
	  ٽوڪن.محفوظ_ڌڪو (eof_token);
	  ٽوڪن.محفوظ_ڌڪو (eof_token);

	  saved_ٽوڪن = parser->ٽوڪن;
	  ٽوڪن_avail = parser->ٽوڪن_avail;
	  parser->ٽوڪن = ٽوڪن.پتو ();
	  parser->ٽوڪن_avail = ٽوڪن.ڊيگهائي ();
	}
      وإلا إذا (map_lvalue
	       && (قسم == OMP_CLAUSE_MAP
		   || قسم == OMP_CLAUSE_منزل
		   || قسم == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  منطقي save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = سچ;
	  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  إذا (اظهار.قدر != error_mark_ڳنڍ)
	    mark_exp_read (اظهار.قدر);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  وڻ decl = اظهار.قدر;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  إذا (وڻ_ڪوڊ (decl) == OMP_ARRAY_SECTION)
	    {
	      طالما (وڻ_ڪوڊ (decl) == OMP_ARRAY_SECTION)
		{
		  وڻ هيٺيون_bound = وڻ_عمليو (decl, 1);
		  وڻ ڊيگهائي = وڻ_عمليو (decl, 2);
		  dims.محفوظ_ڌڪو (omp_dim (هيٺيون_bound, ڊيگهائي, loc, خطأ));
		  decl = وڻ_عمليو (decl, 0);
		}

	      طالما (وڻ_ڪوڊ (decl) == ARRAY_REF
		     || وڻ_ڪوڊ (decl) == اڻسڌو_REF
		     || وڻ_ڪوڊ (decl) == COMPOUND_اظهار)
		{
		  إذا (وڻ_ڪوڊ (decl) == COMPOUND_اظهار)
		    {
		      decl = وڻ_عمليو (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  وإلا إذا (وڻ_ڪوڊ (decl) == اڻسڌو_REF)
		    {
		      dims.محفوظ_ڌڪو (omp_dim (integer_zero_ڳنڍ,
					       integer_one_ڳنڍ, loc, سچ));
		      decl = وڻ_عمليو (decl, 0);
		    }
		  وإلا  /* ARRAY_REF. */
		    {
		      وڻ اشاريو = وڻ_عمليو (decl, 1);
		      dims.محفوظ_ڌڪو (omp_dim (اشاريو, integer_one_ڳنڍ, loc,
					       سچ));
		      decl = وڻ_عمليو (decl, 0);
		    }
		}

	      لكل (صحيح i = dims.ڊيگهائي () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].هيٺيون_bound,
						dims[i].ڊيگهائي);
	    }
	  وإلا إذا (وڻ_ڪوڊ (decl) == اڻسڌو_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = وڻ_عمليو (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_ڳنڍ,
					      integer_one_ڳنڍ);
	    }
	  وإلا إذا (وڻ_ڪوڊ (decl) == ARRAY_REF)
	    {
	      وڻ idx = وڻ_عمليو (decl, 1);

	      decl = وڻ_عمليو (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_ڳنڍ);
	    }
	  وإلا إذا (وڻ_ڪوڊ (decl) == NON_LVALUE_اظهار
		   || CONVERT_اظهار_P (decl))
	    decl = وڻ_عمليو (decl, 0);

	  وڻ u = build_omp_clause (loc, قسم);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  اذهب ايندڙ_شي;
	}

      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_قسم == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->قدر);

	  إذا (t == NULL_وڻ)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->قدر);
	      t = error_mark_ڳنڍ;
	    }

	  c_parser_consume_token (parser);
	}
      وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).قدر;
      وإلا
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}

      إذا (t == error_mark_ڳنڍ)
	;
      وإلا إذا (قسم != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  بدل (قسم)
	    {
	    حالة OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      إذا (c_parser_peek_token (parser)->type != CPP_OPEN_چورس)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_ڳنڍ;
		  اكسر;
		}
	      /* FALLTHROUGH  */
	    حالة OMP_CLAUSE_MAP:
	    حالة OMP_CLAUSE_FROM:
	    حالة OMP_CLAUSE_منزل:
	    شروعات_component_ref:
	      طالما (c_parser_ايندڙ_token_is (parser, CPP_DOT)
		     || c_parser_ايندڙ_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_DEREF))
		    {
		      c_اظهار t_اظهار;
		      t_اظهار.قدر = t;
		      t_اظهار.original_ڪوڊ = ERROR_MARK;
		      t_اظهار.original_type = عدم;
		      سيٽ_c_اظهار_ذريعو_range (&t_اظهار, op_loc, op_loc);
		      t_اظهار.m_decimal = 0;
		      t_اظهار = convert_lvalue_منزل_rvalue (op_loc, t_اظهار,
							 سچ, خطأ);
		      t = build_اڻسڌو_ref (op_loc, t_اظهار.قدر, RO_ARROW);
		      arrow_loc = t_اظهار.get_location ();
		    }
		  c_parser_consume_token (parser);
		  إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_ڳنڍ;
		      اكسر;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  وڻ ident = comp_tok->قدر;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    حالة OMP_CLAUSE_AFFINITY:
	    حالة OMP_CLAUSE_DEPEND:
	    حالة OMP_CLAUSE_REDUCTION:
	    حالة OMP_CLAUSE_اندريون_REDUCTION:
	    حالة OMP_CLAUSE_TASK_REDUCTION:
	    حالة OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = خطأ;
	      dims.truncate (0);
	      طالما (c_parser_ايندڙ_token_is (parser, CPP_OPEN_چورس))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  وڻ هيٺيون_bound = NULL_وڻ, ڊيگهائي = NULL_وڻ;
		  منطقي no_colon = خطأ;

		  c_parser_consume_token (parser);
		  إذا (!c_parser_ايندڙ_token_is (parser, CPP_COLON))
		    {
		      location_t اظهار_loc
			= c_parser_peek_token (parser)->location;
		      c_اظهار اظهار = c_parser_اظهار (parser);
		      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار,
						       خطأ, سچ);
		      هيٺيون_bound = اظهار.قدر;
		      loc = اظهار_loc;
		    }
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_چورس))
		    {
		      ڊيگهائي = integer_one_ڳنڍ;
		      no_colon = سچ;
		    }
		  وإلا
		    {
		      /* Look for `:'.  */
		      إذا (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_ڳنڍ;
			  اكسر;
			}
		      array_section_p = سچ;
		      إذا (!c_parser_ايندڙ_token_is (parser, CPP_CLOSE_چورس))
			{
			  location_t اظهار_loc
			    = c_parser_peek_token (parser)->location;
			  c_اظهار اظهار = c_parser_اظهار (parser);
			  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار,
							   خطأ, سچ);
			  ڊيگهائي = اظهار.قدر;
			}
		    }
		  /* Look for the closing `]'.  */
		  إذا (!c_parser_require (parser, CPP_CLOSE_چورس,
					 "expected %<]%>"))
		    {
		      t = error_mark_ڳنڍ;
		      اكسر;
		    }

		  dims.محفوظ_ڌڪو (omp_dim (هيٺيون_bound, ڊيگهائي, loc, no_colon));
		}

	      إذا (t != error_mark_ڳنڍ)
		{
		  إذا ((قسم == OMP_CLAUSE_MAP
		       || قسم == OMP_CLAUSE_FROM
		       || قسم == OMP_CLAUSE_منزل)
		      && !array_section_p
		      && (c_parser_ايندڙ_token_is (parser, CPP_DOT)
			  || c_parser_ايندڙ_token_is (parser, CPP_DEREF)))
		    {
		      لكل (بنانشان i = 0; i < dims.ڊيگهائي (); i++)
			{
			  gcc_assert (dims[i].ڊيگهائي == integer_one_ڳنڍ);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].هيٺيون_bound);
			}
		      اذهب شروعات_component_ref;
		    }
		  وإلا
		    لكل (بنانشان i = 0; i < dims.ڊيگهائي (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].هيٺيون_bound,
						   dims[i].ڊيگهائي);
		}

	      إذا ((قسم == OMP_CLAUSE_DEPEND || قسم == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_ڳنڍ
		  && parser->ٽوڪن_avail != 2)
		{
		  إذا (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_ڳنڍ;
		    }
		  وإلا
		    {
		      parser->ٽوڪن = ٽوڪن.پتو ();
		      parser->ٽوڪن_avail = ٽوڪن.ڊيگهائي ();

		      t = c_parser_اظهار_no_commas (parser, عدم).قدر;
		      إذا (t != error_mark_ڳنڍ && parser->ٽوڪن_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_ڳنڍ;
			}
		    }
		}
	      اكسر;
	    افتراضي:
	      اكسر;
	    }

	  إذا (t != error_mark_ڳنڍ)
	    {
	      وڻ u = build_omp_clause (clause_loc, قسم);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      وإلا  /* kind == OMP_CLAUSE_ERROR */
	list = وڻ_cons (t, build_خالي_جايون_stmt (tloc), list);

      إذا (قسم == OMP_CLAUSE_DEPEND || قسم == OMP_CLAUSE_AFFINITY)
	{
	  parser->ٽوڪن = saved_ٽوڪن;
	  parser->ٽوڪن_avail = ٽوڪن_avail;
	}

    ايندڙ_شي:
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COMMA))
	اكسر;

      c_parser_consume_token (parser);
    }

  أرجع list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

ساكن وڻ
c_parser_omp_var_list_parens (c_parser *parser, تعداد omp_clause_ڪوڊ قسم,
			      وڻ list, منطقي map_lvalue = خطأ)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (parser->اندريون_omp_decl_attribute)
    {
      إذا (قسم)
	{
	  وڻ u = build_omp_clause (loc, قسم);
	  OMP_CLAUSE_DECL (u) = parser->اندريون_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  أرجع u;
	}
      وإلا
	أرجع وڻ_cons (parser->اندريون_omp_decl_attribute, NULL_وڻ, list);
    }

  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, قسم, list, map_lvalue);
      parens.skip_until_مليو_close (parser);
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

ساكن وڻ
c_parser_oacc_معلومات_clause (c_parser *parser, pragma_omp_clause c_قسم,
			   وڻ list)
{
  تعداد gomp_map_قسم قسم;
  بدل (c_قسم)
    {
    حالة PRAGMA_OACC_CLAUSE_ATTACH:
      قسم = GOMP_MAP_ATTACH;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPY:
      قسم = GOMP_MAP_TOFROM;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPYIN:
      قسم = GOMP_MAP_منزل;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_COPYOUT:
      قسم = GOMP_MAP_FROM;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_CREATE:
      قسم = GOMP_MAP_ALLOC;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DELETE:
      قسم = GOMP_MAP_RELEASE;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DETACH:
      قسم = GOMP_MAP_DETACH;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DEVICE:
      قسم = GOMP_MAP_FORCE_منزل;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      قسم = GOMP_MAP_DEVICE_RESIDENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_LINK:
      قسم = GOMP_MAP_LINK;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_NO_CREATE:
      قسم = GOMP_MAP_IF_PRESENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_PRESENT:
      قسم = GOMP_MAP_FORCE_PRESENT;
      اكسر;
    حالة PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    حالة PRAGMA_OACC_CLAUSE_HOST:
      قسم = GOMP_MAP_FORCE_FROM;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  وڻ nl = list;
  منطقي readonly = خطأ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      إذا (c_قسم == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_اشارو (token->قدر), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = سچ;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       خطأ);
      parens.skip_until_مليو_close (parser);
    }

  لكل (وڻ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_سيٽ_MAP_قسم (c, قسم);
      إذا (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  أرجع nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

ساكن وڻ
c_parser_oacc_معلومات_clause_deviceptr (c_parser *parser, وڻ list)
{
  وڻ vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
  لكل (t = vars; t && t; t = وڻ_CHAIN (t))
    {
      وڻ v = وڻ_PURPOSE (t);
      location_t loc = اظهار_LOCATION (وڻ_قدر (t));

      إذا (!VAR_P (v) && وڻ_ڪوڊ (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      وإلا إذا (وڻ_TYPE (v) == error_mark_ڳنڍ)
	;
      وإلا إذا (!اشارو_TYPE_P (وڻ_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      وڻ u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سيٽ_MAP_قسم (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  أرجع list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

ساكن وڻ
c_parser_omp_clause_collapse (c_parser *parser, وڻ list)
{
  وڻ c, انگ = error_mark_ڳنڍ;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      انگ = c_parser_اظهار_no_commas (parser, عدم).قدر;
      parens.skip_until_مليو_close (parser);
    }
  إذا (انگ == error_mark_ڳنڍ)
    أرجع list;
  mark_exp_read (انگ);
  انگ = c_fully_fold (انگ, خطأ, عدم);
  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (انگ))
      || !وڻ_سمائي_shwi_p (انگ)
      || (n = وڻ_منزل_shwi (انگ)) <= 0
      || (صحيح) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      أرجع list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_اظهار (c) = انگ;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_copyin (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_copyprivate (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

ساكن وڻ
c_parser_omp_clause_default (c_parser *parser, وڻ list, منطقي is_oacc)
{
  تعداد omp_clause_default_قسم قسم = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

      بدل (p[0])
	{
	حالة 'n':
	  إذا (strcmp ("none", p) != 0)
	    اذهب invalid_قسم;
	  قسم = OMP_CLAUSE_DEFAULT_NONE;
	  اكسر;

	حالة 'p':
	  إذا (is_oacc)
	    {
	      إذا (strcmp ("present", p) != 0)
		اذهب invalid_قسم;
	      قسم = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  وإلا
	    {
	      إذا (strcmp ("private", p) != 0)
		اذهب invalid_قسم;
	      قسم = OMP_CLAUSE_DEFAULT_ذاتي;
	    }
	  اكسر;

	حالة 'f':
	  إذا (strcmp ("firstprivate", p) != 0 || is_oacc)
	    اذهب invalid_قسم;
	  قسم = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  اكسر;

	حالة 's':
	  إذا (strcmp ("shared", p) != 0 || is_oacc)
	    اذهب invalid_قسم;
	  قسم = OMP_CLAUSE_DEFAULT_SHARED;
	  اكسر;

	افتراضي:
	  اذهب invalid_قسم;
	}

      c_parser_consume_token (parser);
    }
  وإلا
    {
    invalid_قسم:
      إذا (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      وإلا
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_مليو_close (parser);

  إذا (قسم == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_قسم (c) = قسم;

  أرجع c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_firstprivate (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

ساكن وڻ
c_parser_omp_clause_final (c_parser *parser, وڻ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      وڻ t, c;
      إذا (!parens.require_open (parser))
	t = error_mark_ڳنڍ;
      وإلا
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  t = convert_lvalue_منزل_rvalue (eloc, اظهار, سچ, سچ).قدر;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, خطأ, عدم);
	  parens.skip_until_مليو_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_اظهار (c) = t;
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

ساكن وڻ
c_parser_omp_clause_اڻسڌو (c_parser *parser, وڻ list)
{
  location_t location = c_parser_peek_token (parser)->location;
  وڻ t;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      إذا (!parens.require_open (parser))
	أرجع list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (loc, اظهار, سچ, سچ);
      t = c_objc_common_truthvalue_conversion (loc, اظهار.قدر);
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t))
	  || وڻ_ڪوڊ (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  أرجع list;
	}
      parens.skip_until_مليو_close (parser);
    }
  وإلا
    t = integer_one_ڳنڍ;

  check_no_duplicate_clause (list, OMP_CLAUSE_اڻسڌو, "indirect");

  وڻ c = build_omp_clause (location, OMP_CLAUSE_اڻسڌو);
  OMP_CLAUSE_اڻسڌو_اظهار (c) = t;
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

ساكن وڻ
c_parser_omp_clause_if (c_parser *parser, وڻ list, منطقي is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  تعداد وڻ_ڪوڊ_2 if_modifier = ERROR_MARK;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (is_omp && c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
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
	      p = IDENTIFIER_اشارو (c_parser_peek_2nd_token (parser)->قدر);
	      إذا (strcmp ("data", p) == 0)
		if_modifier = OMP_هدف_معلومات;
	      وإلا إذا (strcmp ("update", p) == 0)
		if_modifier = OMP_هدف_UPDATE;
	      وإلا إذا (strcmp ("enter", p) == 0)
		if_modifier = OMP_هدف_ENTER_معلومات;
	      وإلا إذا (strcmp ("exit", p) == 0)
		if_modifier = OMP_هدف_EXIT_معلومات;
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
	      إذا (if_modifier == OMP_هدف_ENTER_معلومات
		  || if_modifier == OMP_هدف_EXIT_معلومات)
		{
		  إذا (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_اشارو
				(c_parser_peek_2nd_token (parser)->قدر);
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
  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
  اظهار = convert_lvalue_منزل_rvalue (loc, اظهار, سچ, سچ);
  وڻ t = c_objc_common_truthvalue_conversion (loc, اظهار.قدر), c;
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_مليو_close (parser);

  لكل (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_IF)
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
	      حالة OMP_هدف_معلومات: p = "target data"; اكسر;
	      حالة OMP_هدف: p = "target"; اكسر;
	      حالة OMP_هدف_UPDATE: p = "target update"; اكسر;
	      حالة OMP_هدف_ENTER_معلومات: p = "target enter data"; اكسر;
	      حالة OMP_هدف_EXIT_معلومات: p = "target exit data"; اكسر;
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
  OMP_CLAUSE_IF_اظهار (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

ساكن وڻ
c_parser_omp_clause_lastprivate (c_parser *parser, وڻ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      منطقي conditional = خطأ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	  إذا (strcmp (p, "conditional") == 0)
	    {
	      conditional = سچ;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      وڻ nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (conditional)
	لكل (وڻ c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      أرجع nlist;
    }
  أرجع list;
}

/* OpenMP 3.1:
   mergeable */

ساكن وڻ
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_اڻ_استعمال_ٿيل, وڻ list)
{
  وڻ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 2.5:
   nowait */

ساكن وڻ
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_اڻ_استعمال_ٿيل, وڻ list)
{
  وڻ c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

ساكن وڻ
c_parser_omp_clause_انگ_ڌاڳا (c_parser *parser, وڻ list)
{
  location_t انگ_ڌاڳا_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      وڻ c, t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_مليو_close (parser);

      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (اظهار_loc, LE_اظهار, boolean_type_ڳنڍ, t,
		       build_int_cst (وڻ_TYPE (t), 0));
      protected_سيٽ_اظهار_location (c, اظهار_loc);
      إذا (c == boolean_true_ڳنڍ)
	{
	  warning_at (اظهار_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_ڳنڍ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_انگ_ڌاڳا, "num_threads");

      c = build_omp_clause (انگ_ڌاڳا_loc, OMP_CLAUSE_انگ_ڌاڳا);
      OMP_CLAUSE_انگ_ڌاڳا_اظهار (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

ساكن وڻ
c_parser_omp_clause_انگ_tasks (c_parser *parser, وڻ list)
{
  location_t انگ_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي strict = خطأ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر),
		     "strict") == 0)
	{
	  strict = سچ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      وڻ c, t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_مليو_close (parser);

      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (اظهار_loc, LE_اظهار, boolean_type_ڳنڍ, t,
			   build_int_cst (وڻ_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	سيٽ_اظهار_LOCATION (c, اظهار_loc);
      إذا (c == boolean_true_ڳنڍ)
	{
	  warning_at (اظهار_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_ڳنڍ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_انگ_TASKS, "num_tasks");

      c = build_omp_clause (انگ_tasks_loc, OMP_CLAUSE_انگ_TASKS);
      OMP_CLAUSE_انگ_TASKS_اظهار (c) = t;
      OMP_CLAUSE_انگ_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

ساكن وڻ
c_parser_omp_clause_grainsize (c_parser *parser, وڻ list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي strict = خطأ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر),
		     "strict") == 0)
	{
	  strict = سچ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      وڻ c, t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_مليو_close (parser);

      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (اظهار_loc, LE_اظهار, boolean_type_ڳنڍ, t,
			   build_int_cst (وڻ_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	سيٽ_اظهار_LOCATION (c, اظهار_loc);
      إذا (c == boolean_true_ڳنڍ)
	{
	  warning_at (اظهار_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_ڳنڍ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_اظهار (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   priority ( expression ) */

ساكن وڻ
c_parser_omp_clause_ترجيح (c_parser *parser, وڻ list)
{
  location_t ترجيح_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      وڻ c, t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_مليو_close (parser);

      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (اظهار_loc, LT_اظهار, boolean_type_ڳنڍ, t,
			   build_int_cst (وڻ_TYPE (t), 0));
      إذا (CAN_HAVE_LOCATION_P (c))
	سيٽ_اظهار_LOCATION (c, اظهار_loc);
      إذا (c == boolean_true_ڳنڍ)
	{
	  warning_at (اظهار_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_ڳنڍ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ترجيح, "priority");

      c = build_omp_clause (ترجيح_loc, OMP_CLAUSE_ترجيح);
      OMP_CLAUSE_ترجيح_اظهار (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   hint ( expression ) */

ساكن وڻ
c_parser_omp_clause_hint (c_parser *parser, وڻ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      وڻ c, t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t))
	  || وڻ_ڪوڊ (t) != INTEGER_CST
	  || وڻ_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  أرجع list;
	}
      parens.skip_until_مليو_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_اظهار (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

ساكن وڻ
c_parser_omp_clause_filter (c_parser *parser, وڻ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      وڻ c, t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}
      parens.skip_until_مليو_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_اظهار (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

ساكن وڻ
c_parser_omp_clause_defaultmap (c_parser *parser, وڻ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ c;
  ثابت حرف *p;
  تعداد omp_clause_defaultmap_قسم behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  تعداد omp_clause_defaultmap_قسم category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  وإلا إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      اذهب ٻاهريون_err;
    }
  وإلا
    p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

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
	behavior = OMP_CLAUSE_DEFAULTMAP_منزل;
      وإلا
	اذهب invalid_behavior;
      اكسر;

    افتراضي:
      اذهب invalid_behavior;
    }
  c_parser_consume_token (parser);

  إذا (!c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
    {
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	اذهب ٻاهريون_err;
      إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  اذهب ٻاهريون_err;
	}
      p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
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
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_اشارو;
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
  parens.skip_until_مليو_close (parser);

  لكل (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	تعداد omp_clause_defaultmap_قسم cat = category;
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
	  حالة OMP_CLAUSE_DEFAULTMAP_CATEGORY_اشارو:
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
  OMP_CLAUSE_DEFAULTMAP_سيٽ_قسم (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 ٻاهريون_err:
  parens.skip_until_مليو_close (parser);
  أرجع list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_use_device_ptr (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_use_device_addr (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_has_device_addr (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_is_device_ptr (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

ساكن وڻ
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_ڪوڊ ڪوڊ,
				 وڻ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t اظهار_loc = c_parser_peek_token (parser)->location;
  c_اظهار اظهار = c_parser_اظهار (parser);
  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
  وڻ c, t = اظهار.قدر;
  t = c_fully_fold (t, خطأ, عدم);

  parens.skip_until_مليو_close (parser);

  إذا (t == error_mark_ڳنڍ)
    أرجع list;
  وإلا إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
    {
      error_at (اظهار_loc, "%qs expression must be integral",
		omp_clause_ڪوڊ_name[ڪوڊ]);
      أرجع list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (اظهار_loc, LE_اظهار, boolean_type_ڳنڍ, t,
		       build_int_cst (وڻ_TYPE (t), 0));
  protected_سيٽ_اظهار_location (c, اظهار_loc);
  إذا (c == boolean_true_ڳنڍ)
    {
      warning_at (اظهار_loc, 0,
		  "%qs value must be positive",
		  omp_clause_ڪوڊ_name[ڪوڊ]);
      t = integer_one_ڳنڍ;
    }

  check_no_duplicate_clause (list, ڪوڊ, omp_clause_ڪوڊ_name[ڪوڊ]);

  c = build_omp_clause (loc, ڪوڊ);
  OMP_CLAUSE_عمليو (c, 0) = t;
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

ساكن وڻ
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_ڪوڊ قسم,
			    ثابت حرف *str, وڻ list)
{
  ثابت حرف *id = "num";
  وڻ ops[2] = { NULL_وڻ, NULL_وڻ }, c;

  إذا (قسم == OMP_CLAUSE_ويڪٽر)
    id = "length";

  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      افعل
	{
	  c_token *ايندڙ = c_parser_peek_token (parser);
	  صحيح idx = 0;

	  /* Gang static argument.  */
	  إذا (قسم == OMP_CLAUSE_GANG
	      && c_parser_ايندڙ_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		اذهب cleanup_error;

	      idx = 1;
	      إذا (ops[idx] != NULL_وڻ)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  اذهب cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_ڳنڍ;

		  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      استمر;
		    }
		  وإلا
		    اكسر;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_اشارو (ايندڙ->قدر)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  إذا (ops[idx] != NULL_وڻ)
	    {
	      c_parser_error (parser, "unexpected argument");
	      اذهب cleanup_error;
	    }

	  location_t اظهار_loc = c_parser_peek_token (parser)->location;
	  c_اظهار cexpr = c_parser_اظهار_no_commas (parser, عدم);
	  cexpr = convert_lvalue_منزل_rvalue (اظهار_loc, cexpr, خطأ, سچ);
	  وڻ اظهار = cexpr.قدر;
	  إذا (اظهار == error_mark_ڳنڍ)
	    اذهب cleanup_error;

	  اظهار = c_fully_fold (اظهار, خطأ, عدم);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (اظهار)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      أرجع list;
	    }

	  وڻ c = fold_build2_loc (اظهار_loc, LE_اظهار, boolean_type_ڳنڍ, اظهار,
				    build_int_cst (وڻ_TYPE (اظهار), 0));
	  إذا (c == boolean_true_ڳنڍ)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      اظهار = integer_one_ڳنڍ;
	    }

	  ops[idx] = اظهار;

	  إذا (قسم == OMP_CLAUSE_GANG
	      && c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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

  check_no_duplicate_clause (list, قسم, str);

  c = build_omp_clause (loc, قسم);

  إذا (ops[1])
    OMP_CLAUSE_عمليو (c, 1) = ops[1];

  OMP_CLAUSE_عمليو (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;

 cleanup_error:
  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, 0);
  أرجع list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

ساكن وڻ
c_parser_oacc_simple_clause (location_t loc, تعداد omp_clause_ڪوڊ ڪوڊ,
			     وڻ list)
{
  check_no_duplicate_clause (list, ڪوڊ, omp_clause_ڪوڊ_name[ڪوڊ]);

  وڻ c = build_omp_clause (loc, ڪوڊ);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenACC:
   async [( int-expr )] */

ساكن وڻ
c_parser_oacc_clause_async (c_parser *parser, وڻ list)
{
  وڻ c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_ڳنڍ, GOMP_ASYNC_NOVAL);

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_اظهار_no_commas (parser, عدم).قدر;
      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      وإلا إذا (t == error_mark_ڳنڍ
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	أرجع list;
    }
  وإلا
    t = c_fully_fold (t, خطأ, عدم);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_اظهار (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

ساكن وڻ
c_parser_oacc_clause_tile (c_parser *parser, وڻ list)
{
  وڻ c, اظهار = error_mark_ڳنڍ;
  location_t loc;
  وڻ tile = NULL_وڻ;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع list;

  افعل
    {
      إذا (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	أرجع list;

      إذا (c_parser_ايندڙ_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  اظهار = integer_zero_ڳنڍ;
	}
      وإلا
	{
	  location_t اظهار_loc = c_parser_peek_token (parser)->location;
	  c_اظهار cexpr = c_parser_اظهار_no_commas (parser, عدم);
	  cexpr = convert_lvalue_منزل_rvalue (اظهار_loc, cexpr, خطأ, سچ);
	  اظهار = cexpr.قدر;

	  إذا (اظهار == error_mark_ڳنڍ)
	    {
	      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      أرجع list;
	    }

	  اظهار = c_fully_fold (اظهار, خطأ, عدم);

	  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (اظهار))
	      || !وڻ_سمائي_shwi_p (اظهار)
	      || وڻ_منزل_shwi (اظهار) <= 0)
	    {
	      error_at (اظهار_loc, "%<tile%> argument needs positive"
			" integral constant");
	      اظهار = integer_zero_ڳنڍ;
	    }
	}

      tile = وڻ_cons (NULL_وڻ, اظهار, tile);
    }
  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_CLOSE_PAREN));

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

ساكن وڻ
c_parser_oacc_clause_wait (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  وإلا
    {
      وڻ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_ڳنڍ, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenACC 2.7:
   self [( expression )] */

ساكن وڻ
c_parser_oacc_compute_clause_self (c_parser *parser, وڻ list)
{
  وڻ t;
  location_t location = c_parser_peek_token (parser)->location;
  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (loc, اظهار, سچ, سچ);
      t = c_objc_common_truthvalue_conversion (loc, اظهار.قدر);
      t = c_fully_fold (t, خطأ, عدم);
      parens.skip_until_مليو_close (parser);
    }
  وإلا
    t = truthvalue_true_ڳنڍ;

  لكل (وڻ c = list; c; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	أرجع list;
      }

  وڻ c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_اظهار (c) = t;
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

ساكن وڻ
c_parser_omp_clause_ترتيب (c_parser *parser, وڻ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ c;
  ثابت حرف *p;
  منطقي unconstrained = خطأ;
  منطقي reproducible = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "unconstrained") == 0)
	unconstrained = سچ;
      وإلا إذا (strcmp (p, "reproducible") == 0)
	reproducible = سچ;
      وإلا
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  اذهب ٻاهريون_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      اذهب ٻاهريون_err;
    }
  p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
  إذا (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      اذهب ٻاهريون_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_مليو_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ترتيب, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ترتيب);
  OMP_CLAUSE_ترتيب_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ترتيب_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 ٻاهريون_err:
  parens.skip_until_مليو_close (parser);
  أرجع list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

ساكن وڻ
c_parser_omp_clause_bind (c_parser *parser, وڻ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ c;
  ثابت حرف *p;
  تعداد omp_clause_bind_قسم قسم = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_مليو_close (parser);
      أرجع list;
    }
  p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
  إذا (strcmp (p, "teams") == 0)
    قسم = OMP_CLAUSE_BIND_TEAMS;
  وإلا إذا (strcmp (p, "parallel") == 0)
    قسم = OMP_CLAUSE_BIND_PARALLEL;
  وإلا إذا (strcmp (p, "thread") != 0)
    اذهب invalid;
  c_parser_consume_token (parser);
  parens.skip_until_مليو_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_قسم (c) = قسم;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

ساكن وڻ
c_parser_omp_clause_ordered (c_parser *parser, وڻ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  وڻ c, انگ = NULL_وڻ;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      انگ = c_parser_اظهار_no_commas (parser, عدم).قدر;
      parens.skip_until_مليو_close (parser);
    }
  إذا (انگ == error_mark_ڳنڍ)
    أرجع list;
  إذا (انگ)
    {
      mark_exp_read (انگ);
      انگ = c_fully_fold (انگ, خطأ, عدم);
      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (انگ))
	  || !وڻ_سمائي_shwi_p (انگ)
	  || (n = وڻ_منزل_shwi (انگ)) <= 0
	  || (صحيح) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  أرجع list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_اظهار (c) = انگ;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_ذاتي (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ذاتي, list);
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

ساكن وڻ
c_parser_omp_clause_reduction (c_parser *parser, تعداد omp_clause_ڪوڊ قسم,
			       منطقي is_omp, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      منطقي task = خطأ;
      منطقي inscan = خطأ;
      تعداد وڻ_ڪوڊ_2 ڪوڊ = ERROR_MARK;
      وڻ reduc_id = NULL_وڻ;

      إذا (قسم == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ثابت حرف *p
		= IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	      إذا (strcmp (p, "task") == 0)
		task = سچ;
	      وإلا إذا (strcmp (p, "inscan") == 0)
		inscan = سچ;
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
	  ڪوڊ = PLUS_اظهار;
	  اكسر;
	حالة CPP_MULT:
	  ڪوڊ = MULT_اظهار;
	  اكسر;
	حالة CPP_MINUS:
	  إذا (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.جوڙيو_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  ڪوڊ = MINUS_اظهار;
	  اكسر;
	حالة CPP_AND:
	  ڪوڊ = ٻٽو_انگ_AND_اظهار;
	  اكسر;
	حالة CPP_XOR:
	  ڪوڊ = ٻٽو_انگ_XOR_اظهار;
	  اكسر;
	حالة CPP_OR:
	  ڪوڊ = ٻٽو_انگ_IOR_اظهار;
	  اكسر;
	حالة CPP_AND_AND:
	  ڪوڊ = TRUTH_ANDIF_اظهار;
	  اكسر;
	حالة CPP_OR_OR:
	  ڪوڊ = TRUTH_ORIF_اظهار;
	  اكسر;
        حالة CPP_NAME:
	  {
	    ثابت حرف *p
	      = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	    إذا (strcmp (p, "min") == 0)
	      {
		ڪوڊ = MIN_اظهار;
		اكسر;
	      }
	    إذا (strcmp (p, "max") == 0)
	      {
		ڪوڊ = MAX_اظهار;
		اكسر;
	      }
	    reduc_id = c_parser_peek_token (parser)->قدر;
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, 0);
	  أرجع list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (ڪوڊ, reduc_id);
      إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  وڻ nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, قسم, list);
	  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      وڻ d = OMP_CLAUSE_DECL (c), type;
	      إذا (وڻ_ڪوڊ (d) != OMP_ARRAY_SECTION)
		type = وڻ_TYPE (d);
	      وإلا
		{
		  صحيح cnt = 0;
		  وڻ t;
		  لكل (t = d;
		      وڻ_ڪوڊ (t) == OMP_ARRAY_SECTION;
		      t = وڻ_عمليو (t, 0))
		    cnt++;
		  type = وڻ_TYPE (t);
		  طالما (cnt > 0)
		    {
		      إذا (وڻ_ڪوڊ (type) != اشارو_TYPE
			  && وڻ_ڪوڊ (type) != ARRAY_TYPE)
			اكسر;
		      type = وڻ_TYPE (type);
		      cnt--;
		    }
		}
	      طالما (وڻ_ڪوڊ (type) == ARRAY_TYPE)
		type = وڻ_TYPE (type);
	      OMP_CLAUSE_REDUCTION_ڪوڊ (c) = ڪوڊ;
	      إذا (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      وإلا إذا (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      إذا (ڪوڊ == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || وڻ_ڪوڊ (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_مليو_close (parser);
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

ساكن وڻ
c_parser_omp_clause_وقت_جدول (c_parser *parser, وڻ list)
{
  وڻ c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  صحيح modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  c = build_omp_clause (loc, OMP_CLAUSE_وقت_جدول);

  location_t comma = UNKNOWN_LOCATION;
  طالما (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      وڻ قسم = c_parser_peek_token (parser)->قدر;
      ثابت حرف *p = IDENTIFIER_اشارو (قسم);
      إذا (strcmp ("simd", p) == 0)
	OMP_CLAUSE_وقت_جدول_SIMD (c) = 1;
      وإلا إذا (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_وقت_جدول_MONOTONIC;
      وإلا إذا (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_وقت_جدول_NONMONOTONIC;
      وإلا
	اكسر;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      إذا (nmodifiers++ == 0
	  && c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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

  إذا ((modifiers & (OMP_CLAUSE_وقت_جدول_MONOTONIC
		    | OMP_CLAUSE_وقت_جدول_NONMONOTONIC))
      == (OMP_CLAUSE_وقت_جدول_MONOTONIC
	  | OMP_CLAUSE_وقت_جدول_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      وڻ قسم = c_parser_peek_token (parser)->قدر;
      ثابت حرف *p = IDENTIFIER_اشارو (قسم);

      بدل (p[0])
	{
	حالة 'd':
	  إذا (strcmp ("dynamic", p) != 0)
	    اذهب invalid_قسم;
	  OMP_CLAUSE_وقت_جدول_قسم (c) = OMP_CLAUSE_وقت_جدول_DYNAMIC;
	  اكسر;

        حالة 'g':
	  إذا (strcmp ("guided", p) != 0)
	    اذهب invalid_قسم;
	  OMP_CLAUSE_وقت_جدول_قسم (c) = OMP_CLAUSE_وقت_جدول_GUIDED;
	  اكسر;

	حالة 'r':
	  إذا (strcmp ("runtime", p) != 0)
	    اذهب invalid_قسم;
	  OMP_CLAUSE_وقت_جدول_قسم (c) = OMP_CLAUSE_وقت_جدول_RUNTIME;
	  اكسر;

	افتراضي:
	  اذهب invalid_قسم;
	}
    }
  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_وقت_جدول_قسم (c) = OMP_CLAUSE_وقت_جدول_STATIC;
  وإلا إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_وقت_جدول_قسم (c) = OMP_CLAUSE_وقت_جدول_AUTO;
  وإلا
    اذهب invalid_قسم;

  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    {
      location_t هتي;
      c_parser_consume_token (parser);

      هتي = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (هتي, اظهار, خطأ, سچ);
      t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);

      إذا (OMP_CLAUSE_وقت_جدول_قسم (c) == OMP_CLAUSE_وقت_جدول_RUNTIME)
	error_at (هتي, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      وإلا إذا (OMP_CLAUSE_وقت_جدول_قسم (c) == OMP_CLAUSE_وقت_جدول_AUTO)
	error_at (هتي,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      وإلا إذا (وڻ_ڪوڊ (وڻ_TYPE (t)) == INTEGER_TYPE
	       || وڻ_ڪوڊ (وڻ_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  وڻ s = fold_build2_loc (loc, LE_اظهار, boolean_type_ڳنڍ, t,
				    build_int_cst (وڻ_TYPE (t), 0));
	  protected_سيٽ_اظهار_location (s, loc);
	  إذا (s == boolean_true_ڳنڍ)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_ڳنڍ;
	    }
	  OMP_CLAUSE_وقت_جدول_CHUNK_اظهار (c) = t;
	}
      وإلا
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_مليو_close (parser);
    }
  وإلا
    c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_وقت_جدول_قسم (c)
    = (تعداد omp_clause_وقت_جدول_قسم)
      (OMP_CLAUSE_وقت_جدول_قسم (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_وقت_جدول, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_قسم:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, 0);
  أرجع list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_shared (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

ساكن وڻ
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_اڻ_استعمال_ٿيل, وڻ list)
{
  وڻ c;

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

ساكن وڻ
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_اڻ_استعمال_ٿيل,
			    تعداد omp_clause_ڪوڊ ڪوڊ, وڻ list)
{
  check_no_duplicate_clause (list, ڪوڊ, omp_clause_ڪوڊ_name[ڪوڊ]);

  وڻ c = build_omp_clause (c_parser_peek_token (parser)->location, ڪوڊ);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

ساكن وڻ
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_اڻ_استعمال_ٿيل,
				تعداد omp_clause_ڪوڊ ڪوڊ, وڻ list)
{
  وڻ c = build_omp_clause (c_parser_peek_token (parser)->location, ڪوڊ);
  OMP_CLAUSE_CHAIN (c) = list;

  أرجع c;
}

/* OpenMP 4.5:
   nogroup */

ساكن وڻ
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_اڻ_استعمال_ٿيل, وڻ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  وڻ c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.5:
   simd
ڌاڳا*/

ساكن وڻ
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_اڻ_استعمال_ٿيل,
				 تعداد omp_clause_ڪوڊ ڪوڊ, وڻ list)
{
  check_no_duplicate_clause (list, ڪوڊ, omp_clause_ڪوڊ_name[ڪوڊ]);
  وڻ c = build_omp_clause (c_parser_peek_token (parser)->location, ڪوڊ);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

ساكن وڻ
c_parser_omp_clause_انگ_teams (c_parser *parser, وڻ list)
{
  location_t انگ_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t مٿانهون_loc = c_parser_peek_token (parser)->location;
      location_t هيٺاهون_loc = UNKNOWN_LOCATION;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (مٿانهون_loc, اظهار, خطأ, سچ);
      وڻ c, مٿانهون = اظهار.قدر, هيٺاهون = NULL_وڻ;
      مٿانهون = c_fully_fold (مٿانهون, خطأ, عدم);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  هيٺاهون_loc = مٿانهون_loc;
	  هيٺاهون = مٿانهون;
	  مٿانهون_loc = c_parser_peek_token (parser)->location;
	  اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  اظهار = convert_lvalue_منزل_rvalue (مٿانهون_loc, اظهار, خطأ, سچ);
	  مٿانهون = اظهار.قدر;
	  مٿانهون = c_fully_fold (مٿانهون, خطأ, عدم);
	}

      parens.skip_until_مليو_close (parser);

      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (مٿانهون))
	  || (هيٺاهون && !INTEGRAL_TYPE_P (وڻ_TYPE (هيٺاهون))))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (مٿانهون_loc, LE_اظهار, boolean_type_ڳنڍ, مٿانهون,
			   build_int_cst (وڻ_TYPE (مٿانهون), 0));
      protected_سيٽ_اظهار_location (c, مٿانهون_loc);
      إذا (c == boolean_true_ڳنڍ)
	{
	  warning_at (مٿانهون_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  مٿانهون = integer_one_ڳنڍ;
	}
      إذا (هيٺاهون)
	{
	  c = fold_build2_loc (هيٺاهون_loc, LE_اظهار, boolean_type_ڳنڍ, هيٺاهون,
			       build_int_cst (وڻ_TYPE (هيٺاهون), 0));
	  protected_سيٽ_اظهار_location (c, هيٺاهون_loc);
	  إذا (c == boolean_true_ڳنڍ)
	    {
	      warning_at (هيٺاهون_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      هيٺاهون = NULL_وڻ;
	    }
	  وإلا إذا (وڻ_ڪوڊ (هيٺاهون) == INTEGER_CST
		   && وڻ_ڪوڊ (مٿانهون) == INTEGER_CST
		   && وڻ_int_cst_lt (مٿانهون, هيٺاهون))
	    {
	      warning_at (هيٺاهون_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", هيٺاهون, مٿانهون);
	      هيٺاهون = NULL_وڻ;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_انگ_TEAMS, "num_teams");

      c = build_omp_clause (انگ_teams_loc, OMP_CLAUSE_انگ_TEAMS);
      OMP_CLAUSE_انگ_TEAMS_مٿانهون_اظهار (c) = مٿانهون;
      OMP_CLAUSE_انگ_TEAMS_هيٺاهون_اظهار (c) = هيٺاهون;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

ساكن وڻ
c_parser_omp_clause_thread_حد_بندي (c_parser *parser, وڻ list)
{
  location_t انگ_thread_حد_بندي_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      وڻ c, t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);

      parens.skip_until_مليو_close (parser);

      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  أرجع list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (اظهار_loc, LE_اظهار, boolean_type_ڳنڍ, t,
			   build_int_cst (وڻ_TYPE (t), 0));
      protected_سيٽ_اظهار_location (c, اظهار_loc);
      إذا (c == boolean_true_ڳنڍ)
	{
	  warning_at (اظهار_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_ڳنڍ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_حد_بندي,
				 "thread_limit");

      c = build_omp_clause (انگ_thread_حد_بندي_loc, OMP_CLAUSE_THREAD_حد_بندي);
      OMP_CLAUSE_THREAD_حد_بندي_اظهار (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  أرجع list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

ساكن وڻ
c_parser_omp_clause_aligned (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  وڻ nl, c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      وڻ alignment = اظهار.قدر;
      alignment = c_fully_fold (alignment, خطأ, عدم);
      إذا (وڻ_ڪوڊ (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (وڻ_TYPE (alignment))
	  || وڻ_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_وڻ;
	}

      لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_مليو_close (parser);
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

ساكن وڻ
c_parser_omp_clause_allocate (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  وڻ nl, c;
  وڻ allocator = NULL_وڻ;
  وڻ align = NULL_وڻ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا ((c_parser_ايندڙ_token_is_not (parser, CPP_NAME)
       && c_parser_ايندڙ_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      منطقي has_modifiers = خطأ;
      وڻ orig_type = NULL_وڻ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  بنانشان صحيح n = 3;
	  ثابت حرف *p
	    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	  إذا ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = سچ;
	      وإلا إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ثابت حرف *q = IDENTIFIER_اشارو (tok->قدر);
		  n += 4;
		  إذا ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_متوازن_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = سچ;
		}
	    }
	  إذا (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t اظهار_loc = c_parser_peek_token (parser)->location;
	      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
	      إذا (اظهار.قدر == error_mark_ڳنڍ)
		;
	      وإلا إذا (strcmp (p, "allocator") == 0)
		{
		  allocator = اظهار.قدر;
		  allocator = c_fully_fold (allocator, خطأ, عدم);
		  orig_type = اظهار.original_type
			      ? اظهار.original_type : وڻ_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      وإلا
		{
		  align = اظهار.قدر;
		  align = c_fully_fold (align, خطأ, عدم);
		}
	      parens2.skip_until_مليو_close (parser);
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ثابت حرف *q = "";
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_اشارو (tok->قدر);
		  إذا (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_مليو_close (parser);
		      أرجع list;
		    }
		  وإلا إذا (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_مليو_close (parser);
		      أرجع list;
		    }
		  c_parser_consume_token (parser);
		  إذا (!parens2.require_open (parser))
		    {
		      parens.skip_until_مليو_close (parser);
		      أرجع list;
		    }
		  اظهار_loc = c_parser_peek_token (parser)->location;
		  اظهار = c_parser_اظهار_no_commas (parser, عدم);
		  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ,
						   سچ);
		  إذا (strcmp (q, "allocator") == 0)
		    {
		      allocator = اظهار.قدر;
		      allocator = c_fully_fold (allocator, خطأ, عدم);
		      orig_type = اظهار.original_type
				  ? اظهار.original_type : وڻ_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  وإلا
		    {
		      align = اظهار.قدر;
		      align = c_fully_fold (align, خطأ, عدم);
		    }
		  parens2.skip_until_مليو_close (parser);
		}
	    }
	}
      إذا (!has_modifiers)
	{
	  location_t اظهار_loc = c_parser_peek_token (parser)->location;
	  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
	  إذا (اظهار.قدر != error_mark_ڳنڍ)
	    {
	      allocator = اظهار.قدر;
	      allocator = c_fully_fold (allocator, خطأ, عدم);
	      orig_type = اظهار.original_type
			  ? اظهار.original_type : وڻ_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      إذا (allocator
	  && (!INTEGRAL_TYPE_P (وڻ_TYPE (allocator))
	      || وڻ_ڪوڊ (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				وڻ_TYPE (allocator));
          allocator = NULL_وڻ;
        }
      إذا (align
	  && (!INTEGRAL_TYPE_P (وڻ_TYPE (align))
	      || !وڻ_سمائي_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_وڻ;
	}
      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_مليو_close (parser);
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

  parens.skip_until_مليو_close (parser);
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

ساكن وڻ
c_parser_omp_clause_استعمال_ڪري_allocators (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  وڻ nl = list;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

parse_ايندڙ:

  منطقي has_modifiers = خطأ;
  منطقي ڏٺل_allocators = خطأ;
  وڻ memspace_اظهار = NULL_وڻ;
  وڻ traits_var = NULL_وڻ;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      بنانشان صحيح n = 3;
      ثابت حرف *p
	= IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = سچ;
	  وإلا إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ثابت حرف *q = IDENTIFIER_اشارو (tok->قدر);
	      n += 4;
	      إذا ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_متوازن_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  إذا (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = سچ;
		  إذا ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ثابت حرف *m = IDENTIFIER_اشارو (tok->قدر);
		      إذا (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  اذهب پڇاڙي;
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
	  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  إذا (اظهار.قدر == error_mark_ڳنڍ)
	    ;
	  وإلا إذا (strcmp (p, "traits") == 0)
	    {
	      traits_var = اظهار.قدر;
	      traits_var = c_fully_fold (traits_var, خطأ, عدم);
	      mark_exp_read (traits_var);
	    }
	  وإلا
	    {
	      memspace_اظهار = اظهار.قدر;
	      memspace_اظهار = c_fully_fold (memspace_اظهار, خطأ, عدم);
	    }
	  parens2.skip_until_مليو_close (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت حرف *q = "";
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		q = IDENTIFIER_اشارو (tok->قدر);
	      إذا (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_مليو_close (parser);
		  أرجع list;
		}
	      وإلا إذا (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_مليو_close (parser);
		  أرجع list;
		}
	      c_parser_consume_token (parser);
	      إذا (!parens2.require_open (parser))
		{
		  parens.skip_until_مليو_close (parser);
		  أرجع list;
		}
	      اظهار = c_parser_اظهار_no_commas (parser, عدم);
	      إذا (strcmp (q, "traits") == 0)
		{
		  traits_var = اظهار.قدر;
		  traits_var = c_fully_fold (traits_var, خطأ, عدم);
		  mark_exp_read (traits_var);
		}
	      وإلا
		{
		  memspace_اظهار = اظهار.قدر;
		  memspace_اظهار = c_fully_fold (memspace_اظهار, خطأ, عدم);
		}
	      parens2.skip_until_مليو_close (parser);
	    }
	  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    اذهب پڇاڙي;
	}
    }

  طالما (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *tok_s = IDENTIFIER_اشارو (tok->قدر);
      وڻ t = lookup_name (tok->قدر);
      إذا (t == NULL_وڻ)
	{
	  undeclared_variable (tok->location, tok->قدر);
	  t = error_mark_ڳنڍ;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      وڻ legacy_traits = NULL_وڻ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ثابت حرف *tok_a
	    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_مليو_close (parser);

	  إذا (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      اذهب پڇاڙي;
	    }
	  legacy_traits = c_fully_fold (اظهار.قدر, خطأ, عدم);
	  إذا (legacy_traits == error_mark_ڳنڍ)
	    اذهب پڇاڙي;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  إذا (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.جوڙيو_fixit_replace (alloc_loc, "traits");
	      richloc.جوڙيو_fixit_وجهو_after (close_loc, ": ");
	      richloc.جوڙيو_fixit_وجهو_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      إذا (ڏٺل_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  اذهب پڇاڙي;
	}
      ڏٺل_allocators = سچ;

      وڻ c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_استعمال_ڪري_ALLOCATORS);
      OMP_CLAUSE_استعمال_ڪري_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_استعمال_ڪري_ALLOCATORS_MEMSPACE (c) = memspace_اظهار;
      OMP_CLAUSE_استعمال_ڪري_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }

  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      اذهب parse_ايندڙ;
    }

 پڇاڙي:
  parens.skip_until_مليو_close (parser);
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

ساكن وڻ
c_parser_omp_clause_لڪيري (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  وڻ nl, c, قدم;
  تعداد omp_clause_لڪيري_قسم قسم = OMP_CLAUSE_لڪيري_DEFAULT;
  منطقي old_لڪيري_modifier = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *p = IDENTIFIER_اشارو (tok->قدر);
      إذا (strcmp ("val", p) == 0)
	قسم = OMP_CLAUSE_لڪيري_VAL;
      إذا (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	قسم = OMP_CLAUSE_لڪيري_DEFAULT;
      إذا (قسم != OMP_CLAUSE_لڪيري_DEFAULT)
	{
	  old_لڪيري_modifier = سچ;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_لڪيري, list);

  إذا (قسم != OMP_CLAUSE_لڪيري_DEFAULT)
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_مليو_close (parser);
    }

  إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = اظهار_loc;
      منطقي has_modifiers = خطأ;
      إذا (قسم == OMP_CLAUSE_لڪيري_DEFAULT
	  && c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ثابت حرف *p = IDENTIFIER_اشارو (tok->قدر);
	  بنانشان صحيح pos = 0;
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
		has_modifiers = سچ;
	    }
	}
      إذا (has_modifiers)
	{
	  قدم = NULL_وڻ;
	  طالما (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ثابت حرف *p = IDENTIFIER_اشارو (tok->قدر);
	      إذا (strcmp ("val", p) == 0)
		{
		  إذا (قسم != OMP_CLAUSE_لڪيري_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  قسم = OMP_CLAUSE_لڪيري_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      وإلا إذا (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  إذا (parens2.require_open (parser))
		    {
		      إذا (قدم)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      اظهار_loc = c_parser_peek_token (parser)->location;
		      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
		      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ,
						       سچ);
		      قدم = c_fully_fold (اظهار.قدر, خطأ, عدم);
		      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (قدم)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  قدم = integer_one_ڳنڍ;
			}
		      parens2.skip_until_مليو_close (parser);
		    }
		  وإلا
		    اكسر;
		}
	      وإلا
		اكسر;
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  استمر;
		}
	      اكسر;
	    }
	  إذا (!قدم)
	    قدم = integer_one_ڳنڍ;
	}
      وإلا
	{
	  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
	  قدم = c_fully_fold (اظهار.قدر, خطأ, عدم);
	  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (قدم)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      قدم = integer_one_ڳنڍ;
	    }
	}

    }
  وإلا
    قدم = integer_one_ڳنڍ;

  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_لڪيري_قدم (c) = قدم;
      OMP_CLAUSE_لڪيري_قسم (c) = قسم;
      OMP_CLAUSE_لڪيري_OLD_لڪيري_MODIFIER (c) = old_لڪيري_modifier;
    }

  إذا (old_لڪيري_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      إذا (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.جوڙيو_fixit_remove (rm1_loc);
	  إذا (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.جوڙيو_fixit_remove (rm2_loc);
	      richloc.جوڙيو_fixit_وجهو_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.جوڙيو_fixit_وجهو_before (close_loc, ")");
	    }
	  وإلا
	    richloc.جوڙيو_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_مليو_close (parser);
  أرجع nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_nontemporal (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

ساكن وڻ
c_parser_omp_clause_safelen (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  وڻ c, t;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t اظهار_loc = c_parser_peek_token (parser)->location;
  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
  t = اظهار.قدر;
  t = c_fully_fold (t, خطأ, عدم);
  إذا (وڻ_ڪوڊ (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (وڻ_TYPE (t))
      || وڻ_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_وڻ;
    }

  parens.skip_until_مليو_close (parser);
  إذا (t == NULL_وڻ || t == error_mark_ڳنڍ)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_اظهار (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

ساكن وڻ
c_parser_omp_clause_simdlen (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  وڻ c, t = NULL_وڻ, type = NULL_وڻ, ورهائيندڙ = NULL_وڻ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  بنانشان pos = 3;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر),
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
	      && وڻ_ڪوڊ (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_ڳنڍ;
	}
      وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  اظهار = convert_lvalue_منزل_rvalue (loc, اظهار, خطأ, سچ);
	  ورهائيندڙ = اظهار.قدر;
	  ورهائيندڙ = c_fully_fold (ورهائيندڙ, خطأ, عدم);
	  إذا (وڻ_ڪوڊ (ورهائيندڙ) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (وڻ_TYPE (ورهائيندڙ))
	      || وڻ_int_cst_sgn (ورهائيندڙ) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_ڳنڍ;
	    }
	}
      parens2.skip_until_مليو_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  إذا (type != error_mark_ڳنڍ)
    {
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);
      إذا (وڻ_ڪوڊ (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (وڻ_TYPE (t))
	  || وڻ_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_وڻ;
	}
    }

  parens.skip_until_مليو_close (parser);
  إذا (type == error_mark_ڳنڍ || t == NULL_وڻ || t == error_mark_ڳنڍ)
    أرجع list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_اظهار (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_ورهائيندڙ (c) = ورهائيندڙ;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

ساكن وڻ
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   وڻ list, منطقي depend_p)
{
  وڻ vec = عدم;
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      أرجع list;
    }

  إذا (!depend_p)
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_عدد
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  وڻ val = c_parser_peek_nth_token (parser, 3)->قدر;
	  إذا (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      وڻ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_قسم (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      أرجع u;
	    }
	}
    }



  طالما (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_قسم == C_ID_ID)
    {
      وڻ t = lookup_name (c_parser_peek_token (parser)->قدر);
      وڻ addend = عدم;

      إذا (t == NULL_وڻ)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->قدر);
	  t = error_mark_ڳنڍ;
	}

      c_parser_consume_token (parser);

      منطقي neg = خطأ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_MINUS))
	neg = سچ;
      وإلا إذا (!c_parser_ايندڙ_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_ڳنڍ;
	  neg = خطأ;
	  اذهب جوڙيو_منزل_ويڪٽر;
	}
      c_parser_consume_token (parser);

      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_عدد))
	{
	  c_parser_error (parser, "expected integer");
	  أرجع list;
	}

      addend = c_parser_peek_token (parser)->قدر;
      إذا (وڻ_ڪوڊ (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  أرجع list;
	}
      c_parser_consume_token (parser);

    جوڙيو_منزل_ويڪٽر:
      إذا (t != error_mark_ڳنڍ)
	{
	  vec = وڻ_cons (addend, t, vec);
	  إذا (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_قسم != C_ID_ID)
	اكسر;

      c_parser_consume_token (parser);
    }

  إذا (vec == NULL_وڻ)
    أرجع list;

  وڻ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_قسم (u) = OMP_CLAUSE_DOACROSS_SINK;
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

ساكن وڻ
c_parser_omp_iterators (c_parser *parser)
{
  وڻ ret = NULL_وڻ, *آخري = &ret;
  c_parser_consume_token (parser);

  ڌڪو_scope ();

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_ڳنڍ;

  افعل
    {
      وڻ iter_type = NULL_وڻ, type_اظهار = NULL_وڻ;
      إذا (c_parser_ايندڙ_ٽوڪن_شروعات_typename (parser, cla_prefer_id))
	{
	  بنية c_type_name *type = c_parser_type_name (parser);
	  إذا (type != عدم)
	    iter_type = groktypename (type, &type_اظهار, عدم);
	}
      إذا (iter_type == NULL_وڻ)
	iter_type = integer_type_ڳنڍ;

      location_t loc = c_parser_peek_token (parser)->location;
      إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  اكسر;
	}

      وڻ id = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);

      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اكسر;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (eloc, اظهار, سچ, خطأ);
      وڻ begin = اظهار.قدر;

      إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	اكسر;

      eloc = c_parser_peek_token (parser)->location;
      اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (eloc, اظهار, سچ, خطأ);
      وڻ پڇاڙي = اظهار.قدر;

      وڻ قدم = integer_one_ڳنڍ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  اظهار = c_parser_اظهار_no_commas (parser, عدم);
	  اظهار = convert_lvalue_منزل_rvalue (eloc, اظهار, سچ, خطأ);
	  قدم = اظهار.قدر;
	}

      وڻ iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *آخري = make_omp_iterator ();
      OMP_ITERATOR_VAR (*آخري) = iter_var;
      OMP_ITERATOR_BEGIN (*آخري) = begin;
      OMP_ITERATOR_پڇاڙي (*آخري) = پڇاڙي;
      OMP_ITERATOR_قدم (*آخري) = قدم;
      آخري = &وڻ_CHAIN (*آخري);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      اكسر;
    }
  طالما (1);

  parens.skip_until_مليو_close (parser);
  أرجع ret ? ret : error_mark_ڳنڍ;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

ساكن وڻ
c_parser_omp_clause_affinity (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  وڻ nl, iterators = NULL_وڻ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      منطقي parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      إذا (parse_iter)
	{
	  بنانشان n = 3;
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
		ڪڍو_scope ();
	      parens.skip_until_مليو_close (parser);
	      أرجع list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  إذا (iterators)
    {
      وڻ بلاڪ = ڪڍو_scope ();
      إذا (iterators != error_mark_ڳنڍ)
	{
	  OMP_ITERATOR_بلاڪ (iterators) = بلاڪ;
	  لكل (وڻ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_وڻ_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_مليو_close (parser);
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

ساكن وڻ
c_parser_omp_clause_depend (c_parser *parser, وڻ list, location_t هتي)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_depend_قسم قسم = OMP_CLAUSE_DEPEND_آخري;
  تعداد omp_clause_doacross_قسم dkind = OMP_CLAUSE_DOACROSS_آخري;
  وڻ nl, c, iterators = NULL_وڻ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  افعل
    {
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
	اذهب invalid_قسم;

      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp ("iterator", p) == 0 && iterators == NULL_وڻ)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  استمر;
	}
      إذا (strcmp ("in", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_اندريون;
      وإلا إذا (strcmp ("inout", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_INOUT;
      وإلا إذا (strcmp ("inoutset", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_INOUTSET;
      وإلا إذا (strcmp ("mutexinoutset", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      وإلا إذا (strcmp ("out", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_ٻاهريون;
      وإلا إذا (strcmp ("depobj", p) == 0)
	قسم = OMP_CLAUSE_DEPEND_DEPOBJ;
      وإلا إذا (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جوڙيو_fixit_replace (هتي, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      وإلا إذا (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جوڙيو_fixit_replace (هتي, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_ذريعو;
	}
      وإلا
	اذهب invalid_قسم;
      اكسر;
    }
  طالما (1);

  c_parser_consume_token (parser);

  إذا (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_ذريعو
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      ڪڍو_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_ذريعو ? "source" : "sink");
      iterators = NULL_وڻ;
    }

  إذا (dkind == OMP_CLAUSE_DOACROSS_ذريعو)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_قسم (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_وڻ;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_مليو_close (parser);
      أرجع c;
    }

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب resync_fail;

  إذا (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, سچ);
  وإلا
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      إذا (iterators)
	{
	  وڻ بلاڪ = ڪڍو_scope ();
	  إذا (iterators == error_mark_ڳنڍ)
	    iterators = NULL_وڻ;
	  وإلا
	    OMP_ITERATOR_بلاڪ (iterators) = بلاڪ;
	}

      لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_قسم (c) = قسم;
	  إذا (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_وڻ_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_مليو_close (parser);
  أرجع nl;

 invalid_قسم:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_مليو_close (parser);
  إذا (iterators)
    ڪڍو_scope ();
  أرجع list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

ساكن وڻ
c_parser_omp_clause_doacross (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_doacross_قسم قسم = OMP_CLAUSE_DOACROSS_آخري;
  وڻ nl;
  ثابت حرف *p;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME))
    اذهب invalid_قسم;

  p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
  إذا (strcmp ("sink", p) == 0)
    قسم = OMP_CLAUSE_DOACROSS_SINK;
  وإلا إذا (strcmp ("source", p) == 0)
    قسم = OMP_CLAUSE_DOACROSS_ذريعو;
  وإلا
    اذهب invalid_قسم;

  c_parser_consume_token (parser);

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب resync_fail;

  إذا (قسم == OMP_CLAUSE_DOACROSS_ذريعو)
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_قسم (nl) = OMP_CLAUSE_DOACROSS_ذريعو;
      OMP_CLAUSE_DECL (nl) = NULL_وڻ;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  وإلا
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, خطأ);

  parens.skip_until_مليو_close (parser);
  أرجع nl;

 invalid_قسم:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_مليو_close (parser);
  أرجع list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

ساكن وڻ
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  تعداد omp_clause_fallback_قسم قسم = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  بنانشان n = 3;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  أرجع list;
	}
      c_parser_consume_token (parser);
      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	أرجع list;
      p = "";
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "abort") == 0)
	قسم = OMP_CLAUSE_FALLBACK_ABORT;
      وإلا إذا (strcmp (p, "default_mem") == 0)
	قسم = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      وإلا إذا (strcmp (p, "null") == 0)
	قسم = OMP_CLAUSE_FALLBACK_NULL;
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
  location_t اظهار_loc = c_parser_peek_token (parser)->location;
  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
  وڻ سائيز = c_fully_fold (اظهار.قدر, خطأ, عدم);
  parens.skip_until_مليو_close (parser);

  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (سائيز)))
    {
      error_at (اظهار_loc, "expected integer expression");
      أرجع list;
    }

  /* Attempt to statically determine when the number is negative.  */
  وڻ c = fold_build2_loc (اظهار_loc, LT_اظهار, boolean_type_ڳنڍ, سائيز,
			    build_int_cst (وڻ_TYPE (سائيز), 0));
  protected_سيٽ_اظهار_location (c, اظهار_loc);
  إذا (c == boolean_true_ڳنڍ)
    {
      warning_at (اظهار_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      سائيز = integer_zero_ڳنڍ;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_قسم (c) = قسم;
  OMP_CLAUSE_DYN_GROUPPRIVATE_اظهار (c) = سائيز;
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

ساكن وڻ
c_parser_omp_clause_map (c_parser *parser, وڻ list, منطقي declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  وڻ nl, c;
  تعداد gomp_map_قسم قسم = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  صحيح pos = 1;
  صحيح map_قسم_pos = 0;
  صحيح iterator_ڊيگهائي = 0;
  لكل (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      إذا (tok->type != CPP_NAME)
	اكسر;

      ثابت حرف *p = IDENTIFIER_اشارو (tok->قدر);
      c_token *ايندڙ_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      إذا (strcmp (p, "iterator") == 0 && ايندڙ_tok->type == CPP_OPEN_PAREN)
	{
	  بنانشان n = pos + 2;
	  إذا (c_parser_check_متوازن_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_ڊيگهائي = n - pos + 1;
	      pos = n;
	      ايندڙ_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      إذا (ايندڙ_tok->type == CPP_COLON)
	{
	  map_قسم_pos = pos;
	  اكسر;
	}

      إذا (ايندڙ_tok->type == CPP_COMMA)
	pos++;
      وإلا إذا (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  بنانشان صحيح npos = pos + 2;
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
  صحيح انگ_commas = 0;
  صحيح انگ_identifiers = 0;
  وڻ mapper_name = NULL_وڻ;
  وڻ iterators = NULL_وڻ;
  لكل (صحيح pos = 1; pos < map_قسم_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      إذا (tok->type == CPP_COMMA)
	{
	  ++انگ_commas;
	  إذا (انگ_commas > انگ_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  استمر;
	}

      ثابت حرف *p = IDENTIFIER_اشارو (tok->قدر);
      إذا (strcmp ("always", p) == 0)
	{
	  إذا (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_مليو_close (parser);
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
	      parens.skip_until_مليو_close (parser);
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
	      parens.skip_until_مليو_close (parser);
	      أرجع list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_ڊيگهائي - 1;
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
		  parens.skip_until_مليو_close (parser);
		  أرجع list;
		}

	      tok = c_parser_peek_token (parser);

	      بدل (tok->type)
		{
		حالة CPP_NAME:
		  {
		    mapper_name = tok->قدر;
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
		  parens.skip_until_مليو_close (parser);
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
	      parens.skip_until_مليو_close (parser);
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
	  parens.skip_until_مليو_close (parser);
	  أرجع list;
	}
      ++انگ_identifiers;
      إذا (انگ_identifiers - 1 > انگ_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جوڙيو_fixit_وجهو_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      انگ_commas = انگ_identifiers - 1;
    }

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      صحيح always_present_modifier = always_modifier && present_modifier;

      إذا (strcmp ("alloc", p) == 0)
	قسم = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      وإلا إذا (strcmp ("to", p) == 0)
	قسم = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_منزل
		: present_modifier ? GOMP_MAP_PRESENT_منزل
		: always_modifier ? GOMP_MAP_ALWAYS_منزل
		: GOMP_MAP_منزل);
      وإلا إذا (strcmp ("from", p) == 0)
	قسم = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      وإلا إذا (strcmp ("tofrom", p) == 0)
	قسم = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      وإلا إذا (strcmp ("release", p) == 0)
	قسم = GOMP_MAP_RELEASE;
      وإلا إذا (strcmp ("delete", p) == 0)
	قسم = GOMP_MAP_DELETE;
      وإلا
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  أرجع list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   سچ);

  وڻ آخري_new = NULL_وڻ;

  إذا (iterators)
    {
      وڻ بلاڪ = ڪڍو_scope ();
      إذا (iterators == error_mark_ڳنڍ)
	iterators = NULL_وڻ;
      وإلا
	OMP_ITERATOR_بلاڪ (iterators) = بلاڪ;
    }

  لكل (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_سيٽ_MAP_قسم (c, قسم);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      آخري_new = c;
    }

  إذا (mapper_name)
    {
      وڻ name = build_omp_clause (داخلا_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سيٽ_MAP_قسم (name, GOMP_MAP_ڌڪو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (آخري_new);

      name = build_omp_clause (داخلا_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سيٽ_MAP_قسم (name, GOMP_MAP_ڪڍو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_اشارو_ڳنڍ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (آخري_new);
      OMP_CLAUSE_CHAIN (آخري_new) = name;
    }

  parens.skip_until_مليو_close (parser);
  أرجع nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

ساكن وڻ
c_parser_omp_clause_device (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t اظهار_loc;
  c_اظهار اظهار;
  وڻ c, t;
  منطقي ancestor = خطأ;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ثابت حرف *p = IDENTIFIER_اشارو (tok->قدر);
      إذا (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  إذا ((omp_requires_نقاب & OMP_REQUIRES_ابتو_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_مليو_close (parser);
	      أرجع list;
	    }
	  ancestor = سچ;
	}
      وإلا إذا (strcmp ("device_num", p) == 0)
	;
      وإلا
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_مليو_close (parser);
	  أرجع list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  اظهار_loc = c_parser_peek_token (parser)->location;
  اظهار = c_parser_اظهار_no_commas (parser, عدم);
  اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
  t = اظهار.قدر;
  t = c_fully_fold (t, خطأ, عدم);

  parens.skip_until_مليو_close (parser);

  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      أرجع list;
    }
  إذا (ancestor && وڻ_ڪوڊ (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (اظهار_loc, "the %<device%> clause expression must evaluate to "
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

ساكن وڻ
c_parser_omp_clause_dist_وقت_جدول (c_parser *parser, وڻ list)
{
  وڻ c, t = NULL_وڻ;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (!c_parser_ايندڙ_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      أرجع list;
    }

  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      t = اظهار.قدر;
      t = c_fully_fold (t, خطأ, عدم);
      parens.skip_until_مليو_close (parser);
    }
  وإلا
    c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  إذا (omp_ڳوليو_clause (list, OMP_CLAUSE_DIST_وقت_جدول))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  إذا (t == error_mark_ڳنڍ)
    أرجع list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_وقت_جدول);
  OMP_CLAUSE_DIST_وقت_جدول_CHUNK_اظهار (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

ساكن وڻ
c_parser_omp_clause_proc_bind (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_proc_bind_قسم قسم;
  وڻ c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp ("primary", p) == 0)
	قسم = OMP_CLAUSE_PROC_BIND_PRIMARY;
      وإلا إذا (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.جوڙيو_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  قسم = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      وإلا إذا (strcmp ("close", p) == 0)
	قسم = OMP_CLAUSE_PROC_BIND_CLOSE;
      وإلا إذا (strcmp ("spread", p) == 0)
	قسم = OMP_CLAUSE_PROC_BIND_پکيڙ;
      وإلا
	اذهب invalid_قسم;
    }
  وإلا
    اذهب invalid_قسم;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_مليو_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_قسم (c) = قسم;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_قسم:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_مليو_close (parser);
  أرجع list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

ساكن وڻ
c_parser_omp_clause_device_type (c_parser *parser, وڻ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  تعداد omp_clause_device_type_قسم قسم;
  وڻ c;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp ("host", p) == 0)
	قسم = OMP_CLAUSE_DEVICE_TYPE_HOST;
      وإلا إذا (strcmp ("nohost", p) == 0)
	قسم = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      وإلا إذا (strcmp ("any", p) == 0)
	قسم = OMP_CLAUSE_DEVICE_TYPE_ANY;
      وإلا
	اذهب invalid_قسم;
    }
  وإلا
    اذهب invalid_قسم;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_مليو_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_قسم (c) = قسم;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;

 invalid_قسم:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_مليو_close (parser);
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

ساكن وڻ
c_parser_omp_clause_from_منزل (c_parser *parser, تعداد omp_clause_ڪوڊ قسم,
			     وڻ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  صحيح pos = 1, colon_pos = 0;
  صحيح iterator_ڊيگهائي = 0;

  طالما (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ثابت حرف *identifier =
	IDENTIFIER_اشارو (c_parser_peek_nth_token_raw (parser, pos)->قدر);
      إذا (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  بنانشان صحيح npos = pos + 2;
	  إذا (c_parser_check_متوازن_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      إذا (strcmp (identifier, "iterator") == 0)
		iterator_ڊيگهائي = npos - pos + 1;
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
  وڻ iterators = NULL_وڻ;
  وڻ mapper_name = NULL_وڻ;

  لكل (صحيح pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  استمر;
	}
      ثابت حرف *p = IDENTIFIER_اشارو (token->قدر);
      إذا (strcmp ("present", p) == 0)
	{
	  إذا (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_مليو_close (parser);
	      أرجع list;
	    }
	  present = سچ;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("iterator", p) == 0)
	{
	  إذا (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_مليو_close (parser);
	      أرجع list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_ڊيگهائي - 1;
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
		  parens.skip_until_مليو_close (parser);
		  أرجع list;
		}

	      token = c_parser_peek_token (parser);
	      بدل (token->type)
		{
		حالة CPP_NAME:
		  {
		    mapper_name = token->قدر;
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
		  parens.skip_until_مليو_close (parser);
		  أرجع list;
		}
	      mapper_modifier = سچ;
	      pos += 3;
	    }
	}
      وإلا
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    قسم == OMP_CLAUSE_منزل ? "to" : "from");
	  parens.skip_until_مليو_close (parser);
	  أرجع list;
	}
    }

  إذا (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  وڻ nl = c_parser_omp_variable_list (parser, loc, قسم, list);
  parens.skip_until_مليو_close (parser);

  إذا (present)
    لكل (وڻ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  إذا (iterators)
    {
      وڻ بلاڪ = ڪڍو_scope ();
      إذا (iterators == error_mark_ڳنڍ)
	iterators = NULL_وڻ;
      وإلا
	OMP_ITERATOR_بلاڪ (iterators) = بلاڪ;
    }

  إذا (iterators)
    لكل (وڻ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  إذا (mapper_name)
    {
      وڻ آخري_new = NULL_وڻ;
      لكل (وڻ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	آخري_new = c;

      وڻ name = build_omp_clause (داخلا_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سيٽ_MAP_قسم (name, GOMP_MAP_ڌڪو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (آخري_new);

      name = build_omp_clause (داخلا_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_سيٽ_MAP_قسم (name, GOMP_MAP_ڪڍو_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_اشارو_ڳنڍ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (آخري_new);
      OMP_CLAUSE_CHAIN (آخري_new) = name;
    }

  أرجع nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_هڪجهڙو (c_parser *parser, وڻ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_هڪجهڙو,
					 list);
      parens.skip_until_مليو_close (parser);
    }
  أرجع list;
}

/* OpenMP 5.1
ڀريل*/

ساكن وڻ
c_parser_omp_clause_ڀريل (c_parser *parser, وڻ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ڀريل, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  وڻ c = build_omp_clause (loc, OMP_CLAUSE_ڀريل);
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

ساكن وڻ
c_parser_omp_clause_partial (c_parser *parser, وڻ list)
{
  وڻ انگ = NULL_وڻ;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      انگ = c_parser_اظهار_no_commas (parser, عدم).قدر;
      parens.skip_until_مليو_close (parser);

      إذا (انگ == error_mark_ڳنڍ)
	أرجع list;

      mark_exp_read (انگ);
      انگ = c_fully_fold (انگ, خطأ, عدم);
      HOST_WIDE_INT n;
      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (انگ))
	  || !وڻ_سمائي_shwi_p (انگ)
	  || (n = وڻ_منزل_shwi (انگ)) <= 0
	  || (صحيح) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  أرجع list;
	}
    }

  وڻ c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_اظهار (c) = انگ;
  OMP_CLAUSE_CHAIN (c) = list;
  أرجع c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

ساكن وڻ
c_parser_omp_clause_novariants (c_parser *parser, وڻ list)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
  وڻ t = convert_lvalue_منزل_rvalue (loc, اظهار, سچ, سچ).قدر;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_مليو_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  وڻ c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_اظهار (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

ساكن وڻ
c_parser_omp_clause_nocontext (c_parser *parser, وڻ list)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
  وڻ t = convert_lvalue_منزل_rvalue (loc, اظهار, سچ, سچ).قدر;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, خطأ, عدم);
  parens.skip_until_مليو_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  وڻ c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_اظهار (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  أرجع list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

ساكن وڻ
c_parser_omp_clause_detach (c_parser *parser, وڻ list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  إذا (!parens.require_open (parser))
    أرجع list;

  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_مليو_close (parser);
      أرجع list;
    }

  وڻ t = lookup_name (c_parser_peek_token (parser)->قدر);
  إذا (t == NULL_وڻ)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->قدر);
      parens.skip_until_مليو_close (parser);
      أرجع list;
    }
  c_parser_consume_token (parser);

  وڻ type = TYPE_MAIN_VARIANT (وڻ_TYPE (t));
  إذا (!INTEGRAL_TYPE_P (type)
      || وڻ_ڪوڊ (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_مليو_close (parser);
      أرجع list;
    }

  وڻ u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_مليو_close (parser);
  أرجع u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_destroy (c_parser *parser, وڻ list)
{
  وڻ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  لكل (وڻ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    وڻ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
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

ساكن وڻ
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع error_mark_ڳنڍ;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    طالما (سچ)
      {
	str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
	إذا (c_parser_ايندڙ_token_is (parser, CPP_STRING))
	  {
	    c_اظهار cval = c_parser_string_literal (parser, خطأ, خطأ);
	    إذا (cval.قدر == error_mark_ڳنڍ)
	      أرجع error_mark_ڳنڍ;
	    إذا ((سائيز_t) وڻ_STRING_ڊيگهائي (cval.قدر)
		!= لڙي_ڊيگهه (وڻ_STRING_اشارو (cval.قدر)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = سچ;
		أرجع error_mark_ڳنڍ;
	      }

	    حرف c = omp_get_fr_id_from_name (وڻ_STRING_اشارو (cval.قدر));
	    إذا (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  وڻ_STRING_اشارو (cval.قدر));
	    str += c;
	  }
	وإلا
	  {
	    c_اظهار cval = c_parser_اظهار_no_commas (parser, عدم);
	    وڻ قدر = c_fully_fold (cval.قدر, خطأ, عدم);
	    إذا (INTEGRAL_TYPE_P (وڻ_TYPE (قدر))
		&& وڻ_ڪوڊ (قدر) != INTEGER_CST)
	      قدر = convert_lvalue_منزل_rvalue (cval.get_شروعات (), cval,
						خطأ, سچ).قدر;
	    إذا (وڻ_ڪوڊ (قدر) != INTEGER_CST
		|| !وڻ_سمائي_shwi_p (قدر))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		أرجع error_mark_ڳنڍ;
	      }
	    HOST_WIDE_INT n = وڻ_منزل_shwi (قدر);
	    إذا (n < 1 || n > GOMP_INTEROP_IFR_آخري)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (حرف) n;
	  }
	str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    استمر;
	  }
	إذا (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  أرجع error_mark_ڳنڍ;
	str += '\0';
	وڻ res = build_string (str.ڊيگهائي (), str.معلومات ());
	وڻ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ڳنڍ,
						  str.ڊيگهائي ());
	أرجع res;
      }

  /* New format. */
  std::string str2;
  طالما (سچ)
    {
      إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	أرجع error_mark_ڳنڍ;
      str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      منطقي has_fr = خطأ;
      طالما (سچ)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  إذا (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_اشارو (tok->قدر)) != 0
		  && strcmp("attr", IDENTIFIER_اشارو (tok->قدر)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      أرجع error_mark_ڳنڍ;
	    }
	  c_parser_consume_token (parser);
	  منطقي is_fr = IDENTIFIER_اشارو (tok->قدر)[0] == 'f';
	  إذا (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      أرجع error_mark_ڳنڍ;
	    }
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع error_mark_ڳنڍ;
	  طالما (سچ)
	    {
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_STRING))
		{
		  c_اظهار cval = c_parser_string_literal (parser, خطأ, خطأ);
		  وڻ قدر = cval.قدر;
		  إذا (قدر == error_mark_ڳنڍ)
		    أرجع error_mark_ڳنڍ;
		  إذا ((سائيز_t) وڻ_STRING_ڊيگهائي (قدر)
		      != لڙي_ڊيگهه (وڻ_STRING_اشارو (قدر)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = سچ;
		      أرجع error_mark_ڳنڍ;
		    }
		  إذا (!is_fr)
		    {
		      إذا (!startswith (وڻ_STRING_اشارو (قدر), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = سچ;
			  أرجع error_mark_ڳنڍ;
			}
		      إذا (strchr (وڻ_STRING_اشارو (قدر), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = سچ;
			  أرجع error_mark_ڳنڍ;
			}
		      str2 += وڻ_STRING_اشارو (قدر);
		      str2 += '\0';
		    }
		  وإلا
		    {
		      إذا (*وڻ_STRING_اشارو (قدر) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  أرجع error_mark_ڳنڍ;
			}
		      حرف c = omp_get_fr_id_from_name (وڻ_STRING_اشارو (قدر));
		      إذا (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    وڻ_STRING_اشارو (قدر));
		     str += c;
		     has_fr = سچ;
		    }
		}
	      وإلا إذا (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  أرجع error_mark_ڳنڍ;
		}
	      وإلا
		{
		  c_اظهار cval = c_parser_اظهار_no_commas (parser, عدم);
		  وڻ قدر = c_fully_fold (cval.قدر, خطأ, عدم);
		  إذا (INTEGRAL_TYPE_P (وڻ_TYPE (قدر))
		      && وڻ_ڪوڊ (قدر) != INTEGER_CST)
		    قدر = convert_lvalue_منزل_rvalue (cval.get_شروعات (), cval,
						      خطأ, سچ).قدر;

		  إذا (وڻ_ڪوڊ (قدر) != INTEGER_CST
		      || !وڻ_سمائي_shwi_p (قدر))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      أرجع error_mark_ڳنڍ;
		    }
		  HOST_WIDE_INT n = وڻ_منزل_shwi (قدر);
		  إذا (n < 1 || n > GOMP_INTEROP_IFR_آخري)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (حرف) n;
		  has_fr = سچ;
		}
	      إذا (!is_fr
		  && c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  استمر;
		}
	      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		أرجع error_mark_ڳنڍ;
	      اكسر;
	    }
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	    اكسر;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  أرجع error_mark_ڳنڍ;
	}
      str += (حرف) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;
      إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	أرجع error_mark_ڳنڍ;
    }
  c_parser_consume_token (parser);
  str += '\0';
  وڻ res = build_string (str.ڊيگهائي (), str.معلومات ());
  وڻ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ڳنڍ,
						  str.ڊيگهائي ());
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
				    منطقي *targetsync, وڻ *prefer_type_وڻ)
{
  *هدف = خطأ;
  *targetsync = خطأ;
  *prefer_type_وڻ = NULL_وڻ;

  افعل
    {
      c_token *tok = c_parser_peek_token (parser);
      إذا (tok->type != CPP_NAME)
	اذهب fail;
      ثابت حرف *p = IDENTIFIER_اشارو (tok->قدر);
      إذا (strcmp ("targetsync", p) == 0)
	{
	  إذا (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = سچ;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("target", p) == 0)
	{
	  إذا (*هدف)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *هدف = سچ;
	  c_parser_consume_token (parser);
	}
      وإلا إذا (strcmp ("prefer_type", p) == 0)
	{
	  إذا (*prefer_type_وڻ != NULL_وڻ)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_وڻ = c_parser_omp_modifier_prefer_type (parser);
	  إذا (*prefer_type_وڻ == error_mark_ڳنڍ)
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
      أرجع سچ;
    }
  طالما (سچ);

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

ساكن وڻ
c_parser_omp_clause_init (c_parser *parser, وڻ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع list;

  منطقي هدف = خطأ;
  منطقي targetsync = خطأ;
  وڻ prefer_type_وڻ = NULL_وڻ;

  إذا (!c_parser_omp_clause_init_modifiers (parser, &هدف, &targetsync,
					   &prefer_type_وڻ)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      إذا (prefer_type_وڻ != error_mark_ڳنڍ)
	parens.skip_until_مليو_close (parser);
      أرجع list;
    }

  إذا (!هدف && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  وڻ nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					خطأ);
  parens.skip_until_مليو_close (parser);

  لكل (وڻ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      وڻ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      إذا (هدف)
	OMP_CLAUSE_INIT_هدف (c) = 1;
      إذا (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      إذا (prefer_type_وڻ)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_وڻ;
    }
  أرجع nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_use (c_parser *parser, وڻ list)
{
  أرجع c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

ساكن وڻ
c_parser_omp_clause_interop (c_parser *parser, وڻ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  وڻ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  لكل (وڻ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      وڻ_استعمال_ٿيل (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  أرجع nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

ساكن وڻ
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_نقاب نقاب,
			   ثابت حرف *where, منطقي پڄاڻي_p = سچ,
			   منطقي هدف_p = خطأ)
{
  وڻ clauses = عدم;
  منطقي پهريون = سچ;

  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t هتي;
      pragma_omp_clause c_قسم;
      ثابت حرف *c_name;
      وڻ prev = clauses;

      إذا (!پهريون && c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      هتي = c_parser_peek_token (parser)->location;
      c_قسم = c_parser_omp_clause_name (parser);

      بدل (c_قسم)
	{
	حالة PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (هتي, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "attach";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "copy";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "copyin";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "copyout";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "create";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "delete";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, سچ);
	  c_name = "default";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "detach";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "device";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_معلومات_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "device_resident";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (هتي, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, هتي, OMP_CLAUSE_GANG,
						c_name, clauses);
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "host";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, خطأ);
	  c_name = "if";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (هتي, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (هتي, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "link";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "no_create";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (هتي, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_انگ_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_انگ_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_انگ_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_انگ_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "present";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_ذاتي:
	  clauses = c_parser_omp_clause_ذاتي (parser, clauses);
	  c_name = "private";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     خطأ, clauses);
	  c_name = "reduction";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_SELF:
	  إذا ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  وإلا
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_معلومات_clause (parser, c_قسم, clauses);
	  c_name = "self";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (هتي, OMP_CLAUSE_SEQ,
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
	حالة PRAGMA_OACC_CLAUSE_ويڪٽر:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, هتي, OMP_CLAUSE_ويڪٽر,
						c_name,	clauses);
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_ويڪٽر_ڊيگهائي:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_ويڪٽر_ڊيگهائي,
						     clauses);
	  c_name = "vector_length";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  اكسر;
	حالة PRAGMA_OACC_CLAUSE_ڪم_ڪندڙ:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, هتي, OMP_CLAUSE_ڪم_ڪندڙ,
						c_name, clauses);
	  اكسر;
	افتراضي:
	  c_parser_error (parser, "expected an OpenACC clause");
	  اذهب saw_error;
	}

      پهريون = خطأ;

      إذا (((نقاب >> c_قسم) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (هتي, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_منزل_pragma_eol (parser);

  إذا (پڄاڻي_p)
    أرجع c_پڄاڻي_omp_clauses (clauses, هدف_p ? C_ORT_ACC_هدف
						   : C_ORT_ACC);

  أرجع clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

ساكن وڻ
c_parser_omp_all_clauses (c_parser *parser, omp_clause_نقاب نقاب,
			  ثابت حرف *where, منطقي پڄاڻي_p = سچ,
			  صحيح nested = 0)
{
  وڻ clauses = عدم;
  منطقي پهريون = سچ;

  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t هتي;
      pragma_omp_clause c_قسم;
      ثابت حرف *c_name;
      وڻ prev = clauses;

      إذا (nested && c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	اكسر;

      إذا (!پهريون || nested != 2)
	{
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا إذا (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      هتي = c_parser_peek_token (parser)->location;
      c_قسم = c_parser_omp_clause_name (parser);

      بدل (c_قسم)
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
	  clauses = c_parser_omp_clause_if (parser, clauses, سچ);
	  c_name = "if";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_اندريون_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_اندريون_REDUCTION,
					     سچ, clauses);
	  c_name = "in_reduction";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_اڻسڌو:
	  clauses = c_parser_omp_clause_اڻسڌو (parser, clauses);
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
	حالة PRAGMA_OMP_CLAUSE_انگ_TASKS:
	  clauses = c_parser_omp_clause_انگ_tasks (parser, clauses);
	  c_name = "num_tasks";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_انگ_ڌاڳا:
	  clauses = c_parser_omp_clause_انگ_ڌاڳا (parser, clauses);
	  c_name = "num_threads";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ترتيب:
	  clauses = c_parser_omp_clause_ترتيب (parser, clauses);
	  c_name = "order";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ترجيح:
	  clauses = c_parser_omp_clause_ترجيح (parser, clauses);
	  c_name = "priority";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_ذاتي:
	  clauses = c_parser_omp_clause_ذاتي (parser, clauses);
	  c_name = "private";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     سچ, clauses);
	  c_name = "reduction";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_وقت_جدول:
	  clauses = c_parser_omp_clause_وقت_جدول (parser, clauses);
	  c_name = "schedule";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     سچ, clauses);
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
	  إذا (!پهريون)
	    {
	     clause_not_پهريون:
	      error_at (هتي, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  إذا (!پهريون)
	    اذهب clause_not_پهريون;
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  إذا (!پهريون)
	    اذهب clause_not_پهريون;
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  إذا (!پهريون)
	    اذهب clause_not_پهريون;
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
	حالة PRAGMA_OMP_CLAUSE_منزل:
	  إذا ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (هتي);
	      richloc.جوڙيو_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      وڻ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      لكل (وڻ c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_منزل (c) = 1;
	      clauses = nl;
	    }
	  وإلا
	    clauses = c_parser_omp_clause_from_منزل (parser, OMP_CLAUSE_منزل,
						   clauses);
	  c_name = "to";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_منزل (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_هڪجهڙو:
	  clauses = c_parser_omp_clause_هڪجهڙو (parser, clauses);
	  c_name = "uniform";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_انگ_TEAMS:
	  clauses = c_parser_omp_clause_انگ_teams (parser, clauses);
	  c_name = "num_teams";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_THREAD_حد_بندي:
	  clauses = c_parser_omp_clause_thread_حد_بندي (parser, clauses);
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
	حالة PRAGMA_OMP_CLAUSE_لڪيري:
	  clauses = c_parser_omp_clause_لڪيري (parser, clauses);
	  c_name = "linear";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_استعمال_ڪري_ALLOCATORS:
	  clauses = c_parser_omp_clause_استعمال_ڪري_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  اكسر;
	حالة PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, هتي);
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
	حالة PRAGMA_OMP_CLAUSE_DIST_وقت_جدول:
	  clauses = c_parser_omp_clause_dist_وقت_جدول (parser, clauses);
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
	حالة PRAGMA_OMP_CLAUSE_ڌاڳا:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_ڌاڳا,
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
	حالة PRAGMA_OMP_CLAUSE_ڀريل:
	  c_name = "full";
	  clauses = c_parser_omp_clause_ڀريل (parser, clauses);
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

      پهريون = خطأ;

      إذا (((نقاب >> c_قسم) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (هتي, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  إذا (!nested)
    c_parser_skip_منزل_pragma_eol (parser);

  إذا (پڄاڻي_p)
    {
      إذا ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_هڪجهڙو)) != 0)
	أرجع c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      إذا ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	أرجع c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      أرجع c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP);
    }

  أرجع clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

ساكن وڻ
c_parser_omp_structured_بلاڪ (c_parser *parser, منطقي *if_p)
{
  وڻ stmt = ڌڪو_stmt_list ();
  parser->omp_attrs_forbidden_p = سچ;
  c_parser_statement (parser, if_p);
  أرجع ڪڍو_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

ساكن وڻ
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  وڻ stmt, clauses = NULL_وڻ;
  منطقي readonly = خطأ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_اشارو (token->قدر), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = سچ;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_وڻ);
      parens.skip_until_مليو_close (parser);
    }

  إذا (readonly)
    لكل (وڻ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_منزل_pragma_eol (parser);

  stmt = make_ڳنڍ (OACC_CACHE);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);

  أرجع stmt;
}

/* OpenACC 2.0:
   # pragma acc data oacc-data-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#وصف_ڪريو OACC_معلومات_CLAUSE_نقاب						\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT))

ساكن وڻ
c_parser_oacc_معلومات (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ stmt, clauses, بلاڪ;

  clauses = c_parser_oacc_all_clauses (parser, OACC_معلومات_CLAUSE_نقاب,
				       "#pragma acc data");

  بلاڪ = c_begin_omp_parallel ();
  جوڙيو_stmt (c_parser_omp_structured_بلاڪ (parser, if_p));

  stmt = c_پڄاڻي_oacc_معلومات (loc, clauses, بلاڪ);

  أرجع stmt;
}

/* OpenACC 2.0:
   # pragma acc declare oacc-data-clause[optseq] new-line
*/

#وصف_ڪريو OACC_DECLARE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_LINK)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT))

ساكن فراغ
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  وڻ clauses, stmt, t, decl;

  منطقي error = خطأ;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_نقاب,
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
	  error = سچ;
	  استمر;
	}

      بدل (OMP_CLAUSE_MAP_قسم (t))
	{
	حالة GOMP_MAP_FIRSTPRIVATE_اشارو:
	حالة GOMP_MAP_ALLOC:
	حالة GOMP_MAP_منزل:
	حالة GOMP_MAP_FORCE_DEVICEPTR:
	حالة GOMP_MAP_DEVICE_RESIDENT:
	  اكسر;

	حالة GOMP_MAP_LINK:
	  إذا (!global_bindings_p ()
	      && (وڻ_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = سچ;
	      استمر;
	    }
	  اكسر;

	افتراضي:
	  إذا (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = سچ;
	      استمر;
	    }
	  إذا (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = سچ;
	      استمر;
	    }
	  وإلا إذا (وڻ_عوامي (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = سچ;
	      استمر;
	    }
	  اكسر;
	}

      إذا (!c_check_اندريون_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = سچ;
	  استمر;
	}

      إذا (lookup_attribute ("omp declare target", DECL_خاصيتون (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_خاصيتون (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = سچ;
	  استمر;
	}

      إذا (!error)
	{
	  وڻ id;

	  إذا (OMP_CLAUSE_MAP_قسم (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  وإلا
	    id = get_identifier ("omp declare target");

	  DECL_خاصيتون (decl)
			   = وڻ_cons (id, NULL_وڻ, DECL_خاصيتون (decl));

	  إذا (global_bindings_p ())
	    {
	      symtab_ڳنڍ *ڳنڍ = symtab_ڳنڍ::get (decl);
	      إذا (ڳنڍ != عدم)
		{
		  ڳنڍ->offloadable = 1;
		  إذا (ENABLE_OFFLOADING)
		    {
		      g->have_offload = سچ;
		      إذا (is_a <varpool_ڳنڍ *> (ڳنڍ))
			vec_محفوظ_ڌڪو (offload_vars, decl);
		    }
		}
	    }
	}
    }

  إذا (error || global_bindings_p ())
    أرجع;

  stmt = make_ڳنڍ (OACC_DECLARE);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  سيٽ_اظهار_LOCATION (stmt, pragma_loc);

  جوڙيو_stmt (stmt);

  أرجع;
}

/* OpenACC 2.0:
   # pragma acc enter data oacc-enter-data-clause[optseq] new-line

   or

   # pragma acc exit data oacc-exit-data-clause[optseq] new-line


   LOC is the location of the #pragma token.
*/

#وصف_ڪريو OACC_ENTER_معلومات_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#وصف_ڪريو OACC_EXIT_معلومات_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DELETE) 		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DETACH) 		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_FINALIZE) 		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساكن فراغ
c_parser_oacc_enter_exit_معلومات (c_parser *parser, منطقي enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ clauses, stmt;
  ثابت حرف *p = "";

  c_parser_consume_pragma (parser);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      c_parser_consume_token (parser);
    }

  إذا (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = سچ;
      c_parser_skip_منزل_pragma_eol (parser);
      أرجع;
    }

  إذا (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_معلومات_CLAUSE_نقاب,
					 "#pragma acc enter data");
  وإلا
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_معلومات_CLAUSE_نقاب,
					 "#pragma acc exit data");

  إذا (omp_ڳوليو_clause (clauses, OMP_CLAUSE_MAP) == NULL_وڻ)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      أرجع;
    }

  stmt = enter ? make_ڳنڍ (OACC_ENTER_معلومات) : make_ڳنڍ (OACC_EXIT_معلومات);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);
}


/* OpenACC 2.0:
   # pragma acc host_data oacc-data-clause[optseq] new-line
     structured-block
*/

#وصف_ڪريو OACC_HOST_معلومات_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_USE_DEVICE)          \
	 | (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)                  \
	 | (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT) )

ساكن وڻ
c_parser_oacc_host_معلومات (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ stmt, clauses, بلاڪ;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_معلومات_CLAUSE_نقاب,
				       "#pragma acc host_data", خطأ);
  إذا (!omp_ڳوليو_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      أرجع error_mark_ڳنڍ;
    }
  clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_ACC);
  بلاڪ = c_begin_omp_parallel ();
  جوڙيو_stmt (c_parser_omp_structured_بلاڪ (parser, if_p));
  stmt = c_پڄاڻي_oacc_host_معلومات (loc, clauses, بلاڪ);
  أرجع stmt;
}


/* OpenACC 2.0:

   # pragma acc loop oacc-loop-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#وصف_ڪريو OACC_LOOP_CLAUSE_نقاب						\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COLLAPSE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ذاتي)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ڪم_ڪندڙ)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ويڪٽر)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_AUTO)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_INDEPENDENT) 	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_TILE) )
ساكن وڻ
c_parser_oacc_loop (location_t loc, c_parser *parser, حرف *p_name,
		    omp_clause_نقاب نقاب, وڻ *cclauses, منطقي *if_p)
{
  منطقي is_parallel = ((نقاب >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  نقاب |= OACC_LOOP_CLAUSE_نقاب;

  وڻ clauses = c_parser_oacc_all_clauses (parser, نقاب, p_name,
					    /*finish_p=*/cclauses == عدم,
					    /*target=*/is_parallel);
  إذا (cclauses)
    {
      clauses = c_oacc_ورهايو_loop_clauses (clauses, cclauses, is_parallel);
      إذا (*cclauses)
	*cclauses = c_پڄاڻي_omp_clauses (*cclauses, C_ORT_ACC_هدف);
      إذا (clauses)
	clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_ACC);
    }

  وڻ بلاڪ = c_begin_compound_stmt (سچ);
  وڻ stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, عدم,
				     if_p);
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

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

#وصف_ڪريو OACC_KERNELS_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_انگ_GANGS)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_انگ_WORKERS)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ويڪٽر_ڊيگهائي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#وصف_ڪريو OACC_PARALLEL_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ذاتي)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_انگ_GANGS)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_انگ_WORKERS)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ويڪٽر_ڊيگهائي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#وصف_ڪريو OACC_SERIAL_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ذاتي)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساكن وڻ
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       تعداد pragma_قسم p_قسم, حرف *p_name, منطقي *if_p)
{
  omp_clause_نقاب نقاب;
  تعداد وڻ_ڪوڊ_2 ڪوڊ;
  بدل (p_قسم)
    {
    حالة PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      نقاب = OACC_KERNELS_CLAUSE_نقاب;
      ڪوڊ = OACC_KERNELS;
      اكسر;
    حالة PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      نقاب = OACC_PARALLEL_CLAUSE_نقاب;
      ڪوڊ = OACC_PARALLEL;
      اكسر;
    حالة PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      نقاب = OACC_SERIAL_CLAUSE_نقاب;
      ڪوڊ = OACC_SERIAL;
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  وڻ بلاڪ = c_begin_omp_parallel ();
	  وڻ clauses;
	  c_parser_oacc_loop (loc, parser, p_name, نقاب, &clauses, if_p);
	  أرجع c_پڄاڻي_omp_construct (loc, ڪوڊ, بلاڪ, clauses);
	}
    }

  وڻ clauses = c_parser_oacc_all_clauses (parser, نقاب, p_name,
					    /*finish_p=*/سچ,
					    /*target=*/سچ);

  وڻ بلاڪ = c_begin_omp_parallel ();
  جوڙيو_stmt (c_parser_omp_structured_بلاڪ (parser, if_p));

  أرجع c_پڄاڻي_omp_construct (loc, ڪوڊ, بلاڪ, clauses);
}

/* OpenACC 2.0:
   # pragma acc routine oacc-routine-clause[optseq] new-line
     function-definition

   # pragma acc routine ( name ) oacc-routine-clause[optseq] new-line
*/

#وصف_ڪريو OACC_ROUTINE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ڪم_ڪندڙ)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ويڪٽر)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_NOHOST) )

/* Parse an OpenACC routine directive.  For named directives, we apply
   immediately to the named function.  For unnamed ones we then parse
   a declaration or definition, which must be for a function.  */

ساكن فراغ
c_parser_oacc_routine (c_parser *parser, تعداد pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_معلومات معلومات;
  معلومات.error_ڏٺل = خطأ;
  معلومات.fndecl_ڏٺل = خطأ;
  معلومات.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      وڻ decl = NULL_وڻ;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      إذا (name_token->type == CPP_NAME
	  && (name_token->id_قسم == C_ID_ID
	      || name_token->id_قسم == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->قدر);
	  إذا (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->قدر);
	  c_parser_consume_token (parser);
	}
      وإلا
	c_parser_error (parser, "expected function name");

      إذا (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
	  أرجع;
	}

      معلومات.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_نقاب,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      معلومات.clauses = nreverse (معلومات.clauses);

      إذا (وڻ_ڪوڊ (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  أرجع;
	}

      c_پڄاڻي_oacc_routine (&معلومات, decl, خطأ);
    }
  وإلا /* No optional '( name )'.  */
    {
      معلومات.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_نقاب,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      معلومات.clauses = nreverse (معلومات.clauses);

      /* Emit a helpful diagnostic if there's another pragma following this
	 one.  Also don't allow a static assertion declaration, as in the
	 following we'll just parse a *single* "declaration or function
	 definition", and the static assertion counts an one.  */
      إذا (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA)
	  || c_parser_ايندڙ_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (معلومات.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  أرجع;
	}

      /* We only have to consider the pragma_external case here.  */
      إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, خطأ, سچ,
					 خطأ, عدم, عدم, خطأ, عدم, &معلومات);
	  restore_extension_diagnostics (ext);
	}
      وإلا
	c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, خطأ, سچ,
				       خطأ, عدم, عدم, خطأ, عدم, &معلومات);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

ساكن فراغ
c_پڄاڻي_oacc_routine (بنية oacc_routine_معلومات *معلومات, وڻ fndecl,
		       منطقي is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  إذا (معلومات->error_ڏٺل
      || fndecl == error_mark_ڳنڍ)
    أرجع;

  إذا (معلومات->fndecl_ڏٺل)
    {
      error_at (معلومات->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      معلومات->error_ڏٺل = سچ;
      أرجع;
    }
  إذا (fndecl == NULL_وڻ || وڻ_ڪوڊ (fndecl) != FUNCTION_DECL)
    {
      error_at (معلومات->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      معلومات->error_ڏٺل = سچ;
      أرجع;
    }

  صحيح compatible
    = oacc_verify_routine_clauses (fndecl, &معلومات->clauses, معلومات->loc,
				   "#pragma acc routine");
  إذا (compatible < 0)
    {
      معلومات->error_ڏٺل = سچ;
      أرجع;
    }
  إذا (compatible > 0)
    {
    }
  وإلا
    {
      إذا (وڻ_استعمال_ٿيل (fndecl) || (!is_defn && DECL_SAVED_وڻ (fndecl)))
	{
	  error_at (معلومات->loc,
		    وڻ_استعمال_ٿيل (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  معلومات->error_ڏٺل = سچ;
	  أرجع;
	}

      /* Set the routine's level of parallelism.  */
      وڻ dims = oacc_build_routine_dims (معلومات->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_خاصيتون (fndecl)
	= وڻ_cons (get_identifier ("omp declare target"),
		     معلومات->clauses, DECL_خاصيتون (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  معلومات->fndecl_ڏٺل = سچ;
}

/* OpenACC 2.0:
   # pragma acc update oacc-update-clause[optseq] new-line
*/

#وصف_ڪريو OACC_UPDATE_CLAUSE_نقاب						\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_DEVICE)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_HOST)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ساكن فراغ
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  وڻ clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_نقاب,
					    "#pragma acc update");
  إذا (omp_ڳوليو_clause (clauses, OMP_CLAUSE_MAP) == NULL_وڻ)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      أرجع;
    }

  إذا (parser->error)
    أرجع;

  وڻ stmt = make_ڳنڍ (OACC_UPDATE);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#وصف_ڪريو OACC_WAIT_CLAUSE_نقاب						\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OACC_CLAUSE_IF) )

ساكن وڻ
c_parser_oacc_wait (location_t loc, c_parser *parser, حرف *p_name)
{
  وڻ clauses, list = NULL_وڻ, stmt = NULL_وڻ;

  إذا (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_نقاب, p_name);
  stmt = c_پڄاڻي_oacc_wait (loc, list, clauses);
  جوڙيو_stmt (stmt);

  أرجع stmt;
}

بنية c_omp_loc_وڻ
{
  location_t loc;
  وڻ var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
ساكن وڻ
c_check_omp_allocate_allocator_r (وڻ *tp, صحيح *, فراغ *معلومات)
{
  وڻ var = ((بنية c_omp_loc_وڻ *) معلومات)->var;
  location_t loc = ((بنية c_omp_loc_وڻ *) معلومات)->loc;
  إذا (وڻ_ڪوڊ (*tp) == VAR_DECL && c_check_اندريون_current_scope (*tp))
    {
      إذا (linemap_location_before_p (سٽ_جدول, DECL_ذريعو_LOCATION (var),
				     DECL_ذريعو_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_ذريعو_LOCATION (*tp), "declared here");
	  inform (DECL_ذريعو_LOCATION (var),
		  "to be allocated variable declared here");
	  أرجع *tp;
	}
      وإلا
	{
	  gcc_assert (cur_stmt_list
		      && وڻ_ڪوڊ (cur_stmt_list) == STATEMENT_LIST);

	  وڻ_stmt_iterator l = tsi_آخري (cur_stmt_list);
	  طالما (!tsi_پڇاڙي_p (l))
	    {
	      إذا (linemap_location_before_p (سٽ_جدول, اظهار_LOCATION (*l),
					     DECL_ذريعو_LOCATION (var)))
		  اكسر;
	      إذا (وڻ_ڪوڊ (*l) == MODIFY_اظهار
		  && وڻ_عمليو (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (اظهار_LOCATION (*l), "modified here");
		  inform (DECL_ذريعو_LOCATION (var),
			  "to be allocated variable declared here");
		  أرجع *tp;
		}
	      --l;
	    }
	}
    }
  أرجع NULL_وڻ;
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
  وڻ alignment = NULL_وڻ;
  وڻ allocator = NULL_وڻ;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  وڻ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_وڻ);
  افعل
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
	اكسر;
      matching_parens parens;
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      c_parser_consume_token (parser);
      location_t اظهار_loc = c_parser_peek_token (parser)->location;
      إذا (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  اكسر;
	}
      إذا (!parens.require_open (parser))
	اكسر;

      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, خطأ, سچ);
      اظهار_loc = c_parser_peek_token (parser)->location;
      إذا (اظهار.قدر == error_mark_ڳنڍ)
	;
      وإلا إذا (p[2] == 'i' && alignment)
	{
	  error_at (اظهار_loc, "too many %qs clauses", "align");
	  اكسر;
	}
      وإلا إذا (p[2] == 'i')
	{
	  alignment = c_fully_fold (اظهار.قدر, خطأ, عدم);
	  إذا (وڻ_ڪوڊ (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (وڻ_TYPE (alignment))
	      || وڻ_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (اظهار_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_وڻ;
	    }
	}
      وإلا إذا (allocator)
	{
	  error_at (اظهار_loc, "too many %qs clauses", "allocator");
	  اكسر;
	}
      وإلا
	{
	  allocator = c_fully_fold (اظهار.قدر, خطأ, عدم);
	  allocator_loc = اظهار_loc;
	  وڻ orig_type
	    = اظهار.original_type ? اظهار.original_type : وڻ_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (allocator))
	      || وڻ_ڪوڊ (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (اظهار_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			وڻ_TYPE (allocator));
	      allocator = NULL_وڻ;
	    }
	}
      parens.skip_until_مليو_close (parser);
    } طالما (سچ);
  c_parser_skip_منزل_pragma_eol (parser);

  c_mark_decl_jump_unsafe_اندريون_current_scope ();
  لكل (وڻ c = nl; c != NULL_وڻ; c = OMP_CLAUSE_CHAIN (c))
    {
      وڻ var = OMP_CLAUSE_DECL (c);
      إذا (وڻ_ڪوڊ (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  استمر;
	}
      إذا (!parser->اندريون_omp_decl_attribute && !c_check_اندريون_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_ذريعو_LOCATION (var), "declared here");
	  استمر;
	}
      إذا (lookup_attribute ("omp allocate", DECL_خاصيتون (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  استمر;
	}
      إذا (وڻ_STATIC (var))
	{
	  إذا (allocator == NULL_وڻ && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      استمر;
	    }
	  وإلا إذا (allocator
		   && (wi::منزل_widest (allocator) < 1
		       || wi::منزل_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::منزل_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::منزل_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  وإلا إذا (allocator
		   && (wi::eq_p (wi::منزل_widest (allocator),
				 GOMP_OMP_PREDEF_ALLOC_CGROUP)
		       || wi::eq_p (wi::منزل_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_PTEAM)
		       || wi::eq_p (wi::منزل_widest (allocator),
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
	  بنية c_omp_loc_وڻ معلومات
	    = {اظهار_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_وڻ (&allocator, c_check_omp_allocate_allocator_r, &معلومات, عدم);
	}
      DECL_خاصيتون (var) = وڻ_cons (get_identifier ("omp allocate"),
					 build_وڻ_list (allocator, alignment),
					 DECL_خاصيتون (var));
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
  وڻ lhs = NULL_وڻ, rhs = NULL_وڻ, v = NULL_وڻ, r = NULL_وڻ;
  وڻ lhs1 = NULL_وڻ, rhs1 = NULL_وڻ;
  وڻ stmt, orig_lhs, unfolded_lhs = NULL_وڻ, unfolded_lhs1 = NULL_وڻ;
  تعداد وڻ_ڪوڊ_2 ڪوڊ = ERROR_MARK, opcode = NOP_اظهار;
  تعداد omp_يادگيري_ترتيب يادگيري_ترتيب = OMP_يادگيري_ترتيب_UNSPECIFIED;
  بنية c_اظهار اظهار;
  location_t eloc;
  منطقي structured_بلاڪ = خطأ;
  منطقي swapped = خطأ;
  منطقي non_lvalue_p;
  وڻ clauses = NULL_وڻ;
  منطقي capture = خطأ;
  منطقي compare = خطأ;
  منطقي weak = خطأ;
  تعداد omp_يادگيري_ترتيب fail = OMP_يادگيري_ترتيب_UNSPECIFIED;
  منطقي no_semicolon = خطأ;
  منطقي extra_scope = خطأ;

  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  تعداد وڻ_ڪوڊ_2 new_ڪوڊ = ERROR_MARK;
	  تعداد omp_يادگيري_ترتيب new_يادگيري_ترتيب
	    = OMP_يادگيري_ترتيب_UNSPECIFIED;
	  منطقي new_capture = خطأ;
	  منطقي new_compare = خطأ;
	  منطقي new_weak = خطأ;
	  تعداد omp_يادگيري_ترتيب new_fail = OMP_يادگيري_ترتيب_UNSPECIFIED;

	  إذا (!strcmp (p, "read"))
	    new_ڪوڊ = OMP_ATOMIC_READ;
	  وإلا إذا (!strcmp (p, "write"))
	    new_ڪوڊ = NOP_اظهار;
	  وإلا إذا (!strcmp (p, "update"))
	    new_ڪوڊ = OMP_ATOMIC;
	  وإلا إذا (openacc && !strcmp (p, "capture"))
	    new_ڪوڊ = OMP_ATOMIC_CAPTURE_NEW;
	  وإلا إذا (openacc)
	    {
	      p = عدم;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  وإلا إذا (!strcmp (p, "capture"))
	    new_capture = سچ;
	  وإلا إذا (!strcmp (p, "compare"))
	    new_compare = سچ;
	  وإلا إذا (!strcmp (p, "weak"))
	    new_weak = سچ;
	  وإلا إذا (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      إذا (!parens.require_open (parser))
		استمر;

	      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		{
		  ثابت حرف *q
		    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

		  إذا (!strcmp (q, "seq_cst"))
		    new_fail = OMP_يادگيري_ترتيب_SEQ_CST;
		  وإلا إذا (!strcmp (q, "acquire"))
		    new_fail = OMP_يادگيري_ترتيب_ACQUIRE;
		  وإلا إذا (!strcmp (q, "relaxed"))
		    new_fail = OMP_يادگيري_ترتيب_RELAXED;
		}

	      إذا (new_fail != OMP_يادگيري_ترتيب_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  إذا (fail != OMP_يادگيري_ترتيب_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  وإلا
		    fail = new_fail;
		}
	      وإلا
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_مليو_close (parser);
	      استمر;
	    }
	  وإلا إذا (!strcmp (p, "seq_cst"))
	    new_يادگيري_ترتيب = OMP_يادگيري_ترتيب_SEQ_CST;
	  وإلا إذا (!strcmp (p, "acq_rel"))
	    new_يادگيري_ترتيب = OMP_يادگيري_ترتيب_ACQ_REL;
	  وإلا إذا (!strcmp (p, "release"))
	    new_يادگيري_ترتيب = OMP_يادگيري_ترتيب_RELEASE;
	  وإلا إذا (!strcmp (p, "acquire"))
	    new_يادگيري_ترتيب = OMP_يادگيري_ترتيب_ACQUIRE;
	  وإلا إذا (!strcmp (p, "relaxed"))
	    new_يادگيري_ترتيب = OMP_يادگيري_ترتيب_RELAXED;
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
	      إذا (new_ڪوڊ != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  إذا (openacc
		      && ڪوڊ == OMP_ATOMIC
		      && new_ڪوڊ == OMP_ATOMIC_CAPTURE_NEW)
		    ڪوڊ = new_ڪوڊ;
		  وإلا إذا (ڪوڊ != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  وإلا
		    ڪوڊ = new_ڪوڊ;
		}
	      وإلا إذا (new_يادگيري_ترتيب != OMP_يادگيري_ترتيب_UNSPECIFIED)
		{
		  إذا (يادگيري_ترتيب != OMP_يادگيري_ترتيب_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  وإلا
		    يادگيري_ترتيب = new_يادگيري_ترتيب;
		}
	      وإلا إذا (new_capture)
		{
		  إذا (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  وإلا
		    capture = سچ;
		}
	      وإلا إذا (new_compare)
		{
		  إذا (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  وإلا
		    compare = سچ;
		}
	      وإلا إذا (new_weak)
		{
		  إذا (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  وإلا
		    weak = سچ;
		}
	      c_parser_consume_token (parser);
	      استمر;
	    }
	}
      اكسر;
    }
  c_parser_skip_منزل_pragma_eol (parser);

  إذا (ڪوڊ == ERROR_MARK)
    ڪوڊ = OMP_ATOMIC;
  إذا (capture)
    {
      إذا (ڪوڊ != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      وإلا
	ڪوڊ = OMP_ATOMIC_CAPTURE_NEW;
    }
  إذا (compare && ڪوڊ != OMP_ATOMIC && ڪوڊ != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = خطأ;
    }
  إذا (fail != OMP_يادگيري_ترتيب_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_يادگيري_ترتيب_UNSPECIFIED;
    }
  إذا (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = خطأ;
    }
  إذا (openacc)
    يادگيري_ترتيب = OMP_يادگيري_ترتيب_RELAXED;
  وإلا إذا (يادگيري_ترتيب == OMP_يادگيري_ترتيب_UNSPECIFIED)
    {
      omp_requires_نقاب
	= (تعداد omp_requires) (omp_requires_نقاب
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتيب_استعمال_ٿيل);
      بدل ((تعداد omp_يادگيري_ترتيب)
	      (omp_requires_نقاب & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتيب))
	{
	حالة OMP_يادگيري_ترتيب_UNSPECIFIED:
	حالة OMP_يادگيري_ترتيب_RELAXED:
	  يادگيري_ترتيب = OMP_يادگيري_ترتيب_RELAXED;
	  اكسر;
	حالة OMP_يادگيري_ترتيب_SEQ_CST:
	  يادگيري_ترتيب = OMP_يادگيري_ترتيب_SEQ_CST;
	  اكسر;
	حالة OMP_يادگيري_ترتيب_ACQUIRE:
	  إذا (ڪوڊ == NOP_اظهار)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      يادگيري_ترتيب = OMP_يادگيري_ترتيب_SEQ_CST;
	    }
	  وإلا
	    يادگيري_ترتيب = OMP_يادگيري_ترتيب_ACQUIRE;
	  اكسر;
	حالة OMP_يادگيري_ترتيب_RELEASE:
	  إذا (ڪوڊ == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      يادگيري_ترتيب = OMP_يادگيري_ترتيب_SEQ_CST;
	    }
	  وإلا
	    يادگيري_ترتيب = OMP_يادگيري_ترتيب_RELEASE;
	  اكسر;
	حالة OMP_يادگيري_ترتيب_ACQ_REL:
	  بدل (ڪوڊ)
	    {
	    حالة OMP_ATOMIC_READ:
	      يادگيري_ترتيب = OMP_يادگيري_ترتيب_ACQUIRE;
	      اكسر;
	    حالة NOP_اظهار: /* atomic write */
	      يادگيري_ترتيب = OMP_يادگيري_ترتيب_RELEASE;
	      اكسر;
	    افتراضي:
	      يادگيري_ترتيب = OMP_يادگيري_ترتيب_ACQ_REL;
	      اكسر;
	    }
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}
    }
  وإلا
    بدل (ڪوڊ)
      {
      حالة OMP_ATOMIC_READ:
	إذا (يادگيري_ترتيب == OMP_يادگيري_ترتيب_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    يادگيري_ترتيب = OMP_يادگيري_ترتيب_SEQ_CST;
	  }
	وإلا إذا (يادگيري_ترتيب == OMP_يادگيري_ترتيب_ACQ_REL)
	  يادگيري_ترتيب = OMP_يادگيري_ترتيب_ACQUIRE;
	اكسر;
      حالة NOP_اظهار: /* atomic write */
	إذا (يادگيري_ترتيب == OMP_يادگيري_ترتيب_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    يادگيري_ترتيب = OMP_يادگيري_ترتيب_SEQ_CST;
	  }
	وإلا إذا (يادگيري_ترتيب == OMP_يادگيري_ترتيب_ACQ_REL)
	  يادگيري_ترتيب = OMP_يادگيري_ترتيب_RELEASE;
	اكسر;
      افتراضي:
	اكسر;
      }
  إذا (fail != OMP_يادگيري_ترتيب_UNSPECIFIED)
    يادگيري_ترتيب
      = (تعداد omp_يادگيري_ترتيب) (يادگيري_ترتيب
				 | (fail << OMP_FAIL_يادگيري_ترتيب_سرڪايو));

  بدل (ڪوڊ)
    {
    حالة OMP_ATOMIC_READ:
    حالة NOP_اظهار: /* atomic write */
      v = c_parser_cast_اظهار (parser, عدم).قدر;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, خطأ, عدم, سچ);
      إذا (v == error_mark_ڳنڍ)
	اذهب saw_error;
      إذا (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اذهب saw_error;
      إذا (ڪوڊ == NOP_اظهار)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  اظهار = c_parser_اظهار (parser);
	  اظهار = default_function_array_read_conversion (eloc, اظهار);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  ڪوڊ = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_وڻ;
	  rhs = c_fully_fold (اظهار.قدر, خطأ, عدم);
	  إذا (rhs == error_mark_ڳنڍ)
	    اذهب saw_error;
	}
      وإلا
	{
	  lhs = c_parser_cast_اظهار (parser, عدم).قدر;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, خطأ, عدم, سچ);
	  إذا (lhs == error_mark_ڳنڍ)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      اذهب پورو;
    حالة OMP_ATOMIC_CAPTURE_NEW:
      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_بلاڪ = سچ;
	}
      وإلا إذا (compare
	       && c_parser_ايندڙ_token_is_keyword (parser, RID_IF))
	اكسر;
      وإلا
	{
	  v = c_parser_cast_اظهار (parser, عدم).قدر;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, خطأ, عدم, سچ);
	  إذا (v == error_mark_ڳنڍ)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    v = non_lvalue (v);
	  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    اذهب saw_error;
	  إذا (compare && c_parser_ايندڙ_token_is_keyword (parser, RID_IF))
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
  إذا (compare && c_parser_ايندڙ_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      إذا (!parens.require_open (parser))
	اذهب saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_اظهار cmp_اظهار;
      إذا (r)
	{
	  cmp_اظهار = c_parser_cast_اظهار (parser, عدم);
	  cmp_اظهار = default_function_array_conversion (eloc, cmp_اظهار);
	}
      وإلا
	cmp_اظهار = c_parser_ٻٽو_اظهار (parser, عدم, void_list_ڳنڍ);
      parens.skip_until_مليو_close (parser);
      إذا (cmp_اظهار.قدر == error_mark_ڳنڍ)
	اذهب saw_error;
      إذا (r)
	{
	  إذا (!c_وڻ_equal (cmp_اظهار.قدر, unfolded_lhs))
	    اذهب bad_if;
	  cmp_اظهار.قدر = rhs1;
	  rhs1 = NULL_وڻ;
	  gcc_assert (وڻ_ڪوڊ (cmp_اظهار.قدر) == EQ_اظهار);
	}
      إذا (وڻ_ڪوڊ (cmp_اظهار.قدر) == EQ_اظهار)
	;
      وإلا إذا (!structured_بلاڪ && ڪوڊ == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (اظهار_LOC_OR_LOC (cmp_اظهار.قدر, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  اذهب saw_error;
	}
      وإلا إذا (وڻ_ڪوڊ (cmp_اظهار.قدر) != GT_اظهار
	       && وڻ_ڪوڊ (cmp_اظهار.قدر) != LT_اظهار)
	{
	  error_at (اظهار_LOC_OR_LOC (cmp_اظهار.قدر, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  اذهب saw_error;
	}
      إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	اذهب saw_error;

      extra_scope = سچ;
      eloc = c_parser_peek_token (parser)->location;
      اظهار = c_parser_cast_اظهار (parser, عدم);
      lhs = اظهار.قدر;
      اظهار = default_function_array_conversion (eloc, اظهار);
      unfolded_lhs = اظهار.قدر;
      lhs = c_fully_fold (lhs, خطأ, عدم, سچ);
      orig_lhs = lhs;
      إذا (lhs == error_mark_ڳنڍ)
	اذهب saw_error;
      إذا (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      إذا (!c_parser_ايندڙ_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  اذهب saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      اظهار = c_parser_اظهار_no_commas (parser, عدم);
      rhs1 = اظهار.قدر;

      إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	اذهب saw_error;

      إذا (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	اذهب saw_error;

      extra_scope = خطأ;
      no_semicolon = سچ;

      إذا (c_وڻ_equal (وڻ_عمليو (cmp_اظهار.قدر, 0), unfolded_lhs))
	{
	  إذا (وڻ_ڪوڊ (cmp_اظهار.قدر) == EQ_اظهار)
	    {
	      opcode = COND_اظهار;
	      rhs = c_fully_fold (وڻ_عمليو (cmp_اظهار.قدر, 1),
				  خطأ, عدم, سچ);
	      rhs1 = c_fully_fold (rhs1, خطأ, عدم, سچ);
	    }
	  وإلا إذا (c_وڻ_equal (وڻ_عمليو (cmp_اظهار.قدر, 1), rhs1))
	    {
	      opcode = (وڻ_ڪوڊ (cmp_اظهار.قدر) == GT_اظهار
			? MIN_اظهار : MAX_اظهار);
	      rhs = c_fully_fold (rhs1, خطأ, عدم, سچ);
	      rhs1 = c_fully_fold (وڻ_عمليو (cmp_اظهار.قدر, 0),
				   خطأ, عدم, سچ);
	    }
	  وإلا
	    اذهب bad_if;
	}
      وإلا إذا (وڻ_ڪوڊ (cmp_اظهار.قدر) == EQ_اظهار)
	اذهب bad_if;
      وإلا إذا (c_وڻ_equal (وڻ_عمليو (cmp_اظهار.قدر, 1), unfolded_lhs)
	       && c_وڻ_equal (وڻ_عمليو (cmp_اظهار.قدر, 0), rhs1))
	{
	  opcode = (وڻ_ڪوڊ (cmp_اظهار.قدر) == GT_اظهار
		    ? MAX_اظهار : MIN_اظهار);
	  rhs = c_fully_fold (rhs1, خطأ, عدم, سچ);
	  rhs1 = c_fully_fold (وڻ_عمليو (cmp_اظهار.قدر, 1),
			       خطأ, عدم, سچ);
	}
      وإلا
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  اذهب saw_error;
	}

      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ELSE))
	{
	  إذا (ڪوڊ != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_بلاڪ && r == NULL_وڻ)
	      || وڻ_ڪوڊ (cmp_اظهار.قدر) != EQ_اظهار)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      اذهب saw_error;
	    }

	  c_parser_consume_token (parser);

	  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    اذهب saw_error;

	  extra_scope = سچ;
	  v = c_parser_cast_اظهار (parser, عدم).قدر;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, خطأ, عدم, سچ);
	  إذا (v == error_mark_ڳنڍ)
	    اذهب saw_error;
	  إذا (non_lvalue_p)
	    v = non_lvalue (v);
	  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    اذهب saw_error;

	  اظهار = c_parser_اظهار_no_commas (parser, عدم);

	  إذا (!c_وڻ_equal (اظهار.قدر, unfolded_lhs))
	    اذهب bad_if;

	  إذا (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    اذهب saw_error;

	  إذا (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    اذهب saw_error;

	  extra_scope = خطأ;
	  ڪوڊ = OMP_ATOMIC_CAPTURE_OLD;
	  إذا (r == NULL_وڻ)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_ڳنڍ;
	}
      وإلا إذا (ڪوڊ == OMP_ATOMIC_CAPTURE_NEW && !structured_بلاڪ)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  اذهب saw_error;
	}
      وإلا إذا (ڪوڊ == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_وڻ
	       && v == NULL_وڻ)
	ڪوڊ = OMP_ATOMIC;
      اذهب stmt_پورو;
    }
  eloc = c_parser_peek_token (parser)->location;
  اظهار = c_parser_cast_اظهار (parser, عدم);
  lhs = اظهار.قدر;
  اظهار = default_function_array_conversion (eloc, اظهار);
  unfolded_lhs = اظهار.قدر;
  lhs = c_fully_fold (lhs, خطأ, عدم, سچ);
  orig_lhs = lhs;
  بدل (وڻ_ڪوڊ (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    حالة ERROR_MARK:
    saw_error:
      c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
      إذا (extra_scope && c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      إذا (structured_بلاڪ)
	{
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  وإلا إذا (ڪوڊ == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      أرجع;

    حالة POSTINCREMENT_اظهار:
      إذا (ڪوڊ == OMP_ATOMIC_CAPTURE_NEW && !structured_بلاڪ)
	ڪوڊ = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالة PREINCREMENT_اظهار:
      lhs = وڻ_عمليو (lhs, 0);
      unfolded_lhs = NULL_وڻ;
      opcode = PLUS_اظهار;
      rhs = integer_one_ڳنڍ;
      إذا (compare)
	اذهب invalid_compare;
      اكسر;

    حالة POSTDECREMENT_اظهار:
      إذا (ڪوڊ == OMP_ATOMIC_CAPTURE_NEW && !structured_بلاڪ)
	ڪوڊ = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    حالة PREDECREMENT_اظهار:
      lhs = وڻ_عمليو (lhs, 0);
      unfolded_lhs = NULL_وڻ;
      opcode = MINUS_اظهار;
      rhs = integer_one_ڳنڍ;
      إذا (compare)
	اذهب invalid_compare;
      اكسر;

    حالة COMPOUND_اظهار:
      إذا (وڻ_ڪوڊ (وڻ_عمليو (lhs, 0)) == SAVE_اظهار
	  && وڻ_ڪوڊ (وڻ_عمليو (lhs, 1)) == COMPOUND_اظهار
	  && وڻ_ڪوڊ (وڻ_عمليو (وڻ_عمليو (lhs, 1), 0)) == MODIFY_اظهار
	  && وڻ_عمليو (وڻ_عمليو (lhs, 1), 1) == وڻ_عمليو (lhs, 0)
	  && C_BOOLEAN_TYPE_P (وڻ_TYPE (وڻ_عمليو (وڻ_عمليو
					      (وڻ_عمليو (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = وڻ_عمليو (وڻ_عمليو (lhs, 1), 0);
      /* FALLTHRU */
    حالة MODIFY_اظهار:
      إذا (وڻ_ڪوڊ (lhs) == MODIFY_اظهار
	  && C_BOOLEAN_TYPE_P (وڻ_TYPE (وڻ_عمليو (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  إذا (integer_onep (وڻ_عمليو (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = وڻ_عمليو (lhs, 1);
	      lhs = وڻ_عمليو (lhs, 0);
	      unfolded_lhs = NULL_وڻ;
	      opcode = NOP_اظهار;
	      إذا (ڪوڊ == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_بلاڪ
		  && وڻ_ڪوڊ (orig_lhs) == COMPOUND_اظهار)
		ڪوڊ = OMP_ATOMIC_CAPTURE_OLD;
	      إذا (compare)
		اذهب invalid_compare;
	      اكسر;
	    }
	  إذا (وڻ_ڪوڊ (وڻ_عمليو (lhs, 1)) == TRUTH_NOT_اظهار
	      && وڻ_عمليو (lhs, 0)
		 == وڻ_عمليو (وڻ_عمليو (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = وڻ_عمليو (lhs, 1);
	      lhs = وڻ_عمليو (lhs, 0);
	      unfolded_lhs = NULL_وڻ;
	      opcode = NOP_اظهار;
	      إذا (ڪوڊ == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_بلاڪ
		  && وڻ_ڪوڊ (orig_lhs) == COMPOUND_اظهار)
		ڪوڊ = OMP_ATOMIC_CAPTURE_OLD;
	      إذا (compare)
		اذهب invalid_compare;
	      اكسر;
	    }
	}
      /* FALLTHRU */
    افتراضي:
      إذا (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      إذا (compare && !c_parser_ايندڙ_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  اذهب saw_error;
	}
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_MULT_EQ:
	  opcode = MULT_اظهار;
	  اكسر;
	حالة CPP_DIV_EQ:
	  opcode = TRUNC_DIV_اظهار;
	  اكسر;
	حالة CPP_PLUS_EQ:
	  opcode = PLUS_اظهار;
	  اكسر;
	حالة CPP_MINUS_EQ:
	  opcode = MINUS_اظهار;
	  اكسر;
	حالة CPP_LSHIFT_EQ:
	  opcode = LSHIFT_اظهار;
	  اكسر;
	حالة CPP_RSHIFT_EQ:
	  opcode = RSHIFT_اظهار;
	  اكسر;
	حالة CPP_AND_EQ:
	  opcode = ٻٽو_انگ_AND_اظهار;
	  اكسر;
	حالة CPP_OR_EQ:
	  opcode = ٻٽو_انگ_IOR_اظهار;
	  اكسر;
	حالة CPP_XOR_EQ:
	  opcode = ٻٽو_انگ_XOR_اظهار;
	  اكسر;
	حالة CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  اظهار = c_parser_اظهار_no_commas (parser, عدم, unfolded_lhs);
	  rhs1 = اظهار.قدر;
	  بدل (وڻ_ڪوڊ (rhs1))
	    {
	    حالة MULT_اظهار:
	    حالة TRUNC_DIV_اظهار:
	    حالة RDIV_اظهار:
	    حالة PLUS_اظهار:
	    حالة MINUS_اظهار:
	    حالة LSHIFT_اظهار:
	    حالة RSHIFT_اظهار:
	    حالة ٻٽو_انگ_AND_اظهار:
	    حالة ٻٽو_انگ_IOR_اظهار:
	    حالة ٻٽو_انگ_XOR_اظهار:
	      إذا (compare)
		اكسر;
	      إذا (c_وڻ_equal (وڻ_عمليو (rhs1, 0), unfolded_lhs))
		{
		  opcode = وڻ_ڪوڊ (rhs1);
		  rhs = c_fully_fold (وڻ_عمليو (rhs1, 1), خطأ, عدم,
				      سچ);
		  rhs1 = c_fully_fold (وڻ_عمليو (rhs1, 0), خطأ, عدم,
				       سچ);
		  اذهب stmt_پورو;
		}
	      إذا (c_وڻ_equal (وڻ_عمليو (rhs1, 1), unfolded_lhs))
		{
		  opcode = وڻ_ڪوڊ (rhs1);
		  rhs = c_fully_fold (وڻ_عمليو (rhs1, 0), خطأ, عدم,
				      سچ);
		  rhs1 = c_fully_fold (وڻ_عمليو (rhs1, 1), خطأ, عدم,
				       سچ);
		  swapped = !commutative_وڻ_ڪوڊ (opcode);
		  اذهب stmt_پورو;
		}
	      اكسر;
	    حالة COND_اظهار:
	      إذا (!compare)
		اكسر;
	      إذا (وڻ_ڪوڊ (وڻ_عمليو (rhs1, 0)) != GT_اظهار
		  && وڻ_ڪوڊ (وڻ_عمليو (rhs1, 0)) != LT_اظهار
		  && وڻ_ڪوڊ (وڻ_عمليو (rhs1, 0)) != EQ_اظهار)
		اكسر;
	      إذا (!وڻ_عمليو (rhs1, 1))
		اكسر;
	      إذا (!c_وڻ_equal (وڻ_عمليو (rhs1, 2), unfolded_lhs))
		اكسر;
	      إذا (c_وڻ_equal (وڻ_عمليو (وڻ_عمليو (rhs1, 0), 0),
				unfolded_lhs))
		{
		  إذا (وڻ_ڪوڊ (وڻ_عمليو (rhs1, 0)) == EQ_اظهار)
		    {
		      opcode = COND_اظهار;
		      rhs = c_fully_fold (وڻ_عمليو (وڻ_عمليو (rhs1,
								      0), 1),
					  خطأ, عدم, سچ);
		      rhs1 = c_fully_fold (وڻ_عمليو (rhs1, 1), خطأ,
					   عدم, سچ);
		      اذهب stmt_پورو;
		    }
		  إذا (c_وڻ_equal (وڻ_عمليو (وڻ_عمليو (rhs1, 0), 1),
				    وڻ_عمليو (rhs1, 1)))
		    {
		      opcode = (وڻ_ڪوڊ (وڻ_عمليو (rhs1, 0)) == GT_اظهار
				? MIN_اظهار : MAX_اظهار);
		      rhs = c_fully_fold (وڻ_عمليو (rhs1, 1), خطأ, عدم,
					  سچ);
		      rhs1 = c_fully_fold (وڻ_عمليو (وڻ_عمليو (rhs1,
								       0), 0),
					   خطأ, عدم, سچ);
		      اذهب stmt_پورو;
		    }
		}
	      وإلا إذا (وڻ_ڪوڊ (وڻ_عمليو (rhs1, 0)) == EQ_اظهار)
		اكسر;
	      وإلا إذا (c_وڻ_equal (وڻ_عمليو (وڻ_عمليو (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  إذا (c_وڻ_equal (وڻ_عمليو (وڻ_عمليو (rhs1, 0), 0),
				    وڻ_عمليو (rhs1, 1)))
		    {
		      opcode = (وڻ_ڪوڊ (وڻ_عمليو (rhs1, 0)) == GT_اظهار
				? MAX_اظهار : MIN_اظهار);
		      rhs = c_fully_fold (وڻ_عمليو (rhs1, 1), خطأ, عدم,
					  سچ);
		      rhs1 = c_fully_fold (وڻ_عمليو (وڻ_عمليو (rhs1,
								       0), 1),
					   خطأ, عدم, سچ);
		      اذهب stmt_پورو;
		    }
		}
	      اكسر;
	    حالة EQ_اظهار:
	      إذا (!compare
		  || ڪوڊ != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_بلاڪ
		  || v
		  || r)
		اكسر;
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_وڻ;
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
	      إذا (structured_بلاڪ && ڪوڊ == OMP_ATOMIC_CAPTURE_NEW)
		{
		  ڪوڊ = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_وڻ;
		  اظهار = default_function_array_read_conversion (eloc, اظهار);
		  unfolded_lhs1 = اظهار.قدر;
		  lhs1 = c_fully_fold (unfolded_lhs1, خطأ, عدم, سچ);
		  rhs1 = NULL_وڻ;
		  c_parser_consume_token (parser);
		  اذهب restart;
		}
	      إذا (structured_بلاڪ && !compare)
		{
		  opcode = NOP_اظهار;
		  اظهار = default_function_array_read_conversion (eloc, اظهار);
		  rhs = c_fully_fold (اظهار.قدر, خطأ, عدم, سچ);
		  rhs1 = NULL_وڻ;
		  اذهب stmt_پورو;
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
      اظهار = c_parser_اظهار (parser);
      اظهار = default_function_array_read_conversion (eloc, اظهار);
      rhs = اظهار.قدر;
      rhs = c_fully_fold (rhs, خطأ, عدم, سچ);
      اكسر;
    }
stmt_پورو:
  إذا (structured_بلاڪ && ڪوڊ == OMP_ATOMIC_CAPTURE_NEW && r == NULL_وڻ)
    {
      إذا (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	اذهب saw_error;
      no_semicolon = خطأ;
      v = c_parser_cast_اظهار (parser, عدم).قدر;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, خطأ, عدم, سچ);
      إذا (v == error_mark_ڳنڍ)
	اذهب saw_error;
      إذا (non_lvalue_p)
	v = non_lvalue (v);
      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	اذهب saw_error;
      eloc = c_parser_peek_token (parser)->location;
      اظهار = c_parser_cast_اظهار (parser, عدم);
      lhs1 = اظهار.قدر;
      اظهار = default_function_array_read_conversion (eloc, اظهار);
      unfolded_lhs1 = اظهار.قدر;
      lhs1 = c_fully_fold (lhs1, خطأ, عدم, سچ);
      إذا (lhs1 == error_mark_ڳنڍ)
	اذهب saw_error;
      إذا (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  إذا (structured_بلاڪ)
    {
      إذا (!no_semicolon)
	c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
پورو:
  إذا (weak && opcode != COND_اظهار)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = خطأ;
    }
  إذا (unfolded_lhs && unfolded_lhs1
      && !c_وڻ_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_ڳنڍ;
    }
  وإلا
    stmt = c_پڄاڻي_omp_atomic (loc, ڪوڊ, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, يادگيري_ترتيب, weak);
  إذا (stmt != error_mark_ڳنڍ)
    جوڙيو_stmt (stmt);

  إذا (!structured_بلاڪ && !no_semicolon)
    c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

ساكن فراغ
c_parser_omp_barrier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_منزل_pragma_eol (parser);

  c_پڄاڻي_omp_barrier (loc);
}

/* OpenMP 2.5:
   # pragma omp critical [(name)] new-line
     structured-block

   OpenMP 4.5:
   # pragma omp critical [(name) [hint(expression)]] new-line

  LOC is the location of the #pragma itself.  */

#وصف_ڪريو OMP_CRITICAL_CLAUSE_نقاب		\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_HINT) )

ساكن وڻ
c_parser_omp_critical (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ stmt, name = NULL_وڻ, clauses = NULL_وڻ;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->قدر;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      وإلا
	c_parser_error (parser, "expected identifier");

      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_نقاب,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_بلاڪ (parser, if_p);
  أرجع c_پڄاڻي_omp_critical (loc, stmt, name, clauses);
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
اندريون
ٻاهريون
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
      c_parser_skip_منزل_pragma_eol (parser);
      أرجع;
    }

  وڻ depobj = c_parser_اظهار_no_commas (parser, عدم).قدر;
  إذا (depobj != error_mark_ڳنڍ)
    {
      إذا (!lvalue_p (depobj))
	{
	  error_at (اظهار_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_ڳنڍ;
	}
      وإلا
	{
	  وڻ addr = build_unary_op (اظهار_LOC_OR_LOC (depobj, loc), ADDR_اظهار,
				      depobj, خطأ);
	  إذا (addr == error_mark_ڳنڍ)
	    depobj = error_mark_ڳنڍ;
	  وإلا
	    depobj = build_اڻسڌو_ref (اظهار_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_تارو);
	}
    }

  parens.skip_until_مليو_close (parser);
  وڻ clause = NULL_وڻ;
  تعداد omp_clause_depend_قسم قسم = OMP_CLAUSE_DEPEND_INVALID;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

      c_parser_consume_token (parser);
      إذا (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_وڻ, c_loc);
	  clause = c_پڄاڻي_omp_clauses (clause, C_ORT_OMP);
	  إذا (!clause)
	    clause = error_mark_ڳنڍ;
	}
      وإلا إذا (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  قسم = OMP_CLAUSE_DEPEND_آخري;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      وڻ destobj = c_parser_اظهار_no_commas (parser, عدم).قدر;
	      إذا (!lvalue_p (destobj))
		error_at (اظهار_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      وإلا إذا (depobj != error_mark_ڳنڍ
		       && !عمليو_equal_p (destobj, depobj,
					    OEP_ميلاپ_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (اظهار_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_مليو_close (parser);
	    }
	}
      وإلا إذا (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  إذا (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		{
		  ثابت حرف *p2
		    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

		  c_parser_consume_token (parser);
		  إذا (!strcmp ("in", p2))
		    قسم = OMP_CLAUSE_DEPEND_اندريون;
		  وإلا إذا (!strcmp ("out", p2))
		    قسم = OMP_CLAUSE_DEPEND_ٻاهريون;
		  وإلا إذا (!strcmp ("inout", p2))
		    قسم = OMP_CLAUSE_DEPEND_INOUT;
		  وإلا إذا (!strcmp ("mutexinoutset", p2))
		    قسم = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  وإلا إذا (!strcmp ("inoutset", p2))
		    قسم = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      إذا (قسم == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_ڳنڍ;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_مليو_close (parser);
	    }
	  وإلا
	    clause = error_mark_ڳنڍ;
	}
    }
  إذا (!clause && قسم == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_ڳنڍ;
      error_at (c_loc, "expected %<depend%>, %<destroy%> or %<update%> clause");
    }
  c_parser_skip_منزل_pragma_eol (parser);

  c_پڄاڻي_omp_depobj (loc, depobj, قسم, clause);
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
  تعداد memmodel mo = MEMMODEL_آخري;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p
	= IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

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
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      إذا (mo != MEMMODEL_آخري)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
    }
  وإلا إذا (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_منزل_pragma_eol (parser);

  c_پڄاڻي_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

ساكن منطقي
c_parser_omp_section_جاچ (c_parser *parser, ثابت حرف *directive,
			   منطقي tentative)
{
  إذا (!c_parser_nth_token_starts_std_خاصيتون (parser, 1))
    أرجع خطأ;
  بنانشان صحيح n = 3;
  إذا (!c_parser_check_متوازن_raw_token_sequence (parser, &n))
    أرجع خطأ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  إذا (token->type != CPP_CLOSE_چورس)
    أرجع خطأ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  إذا (token->type != CPP_CLOSE_چورس)
    أرجع خطأ;
  إذا (n < 9)
    أرجع خطأ;
  إذا (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      وڻ پهريون = c_parser_peek_nth_token_raw (parser, 3)->قدر;
      وڻ ٻيو = c_parser_peek_nth_token_raw (parser, 5)->قدر;
      إذا (strcmp (IDENTIFIER_اشارو (پهريون), "directive")
	  && strcmp (IDENTIFIER_اشارو (پهريون), "__directive__"))
	أرجع خطأ;
      إذا (strcmp (IDENTIFIER_اشارو (ٻيو), directive))
	أرجع خطأ;
    }
  إذا (tentative)
    أرجع سچ;
  location_t پهريون_loc = c_parser_peek_token (parser)->location;
  location_t آخري_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t وچ_loc = UNKNOWN_LOCATION;
  وڻ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  منطقي ڏٺل = خطأ;
  صحيح cnt = 0;
  لكل (وڻ attr = std_attrs; attr; attr = وڻ_CHAIN (attr))
    إذا (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	لكل (وڻ a = وڻ_قدر (attr); a; a = وڻ_CHAIN (a))
	  {
	    وڻ d = وڻ_قدر (a);
	    gcc_assert (وڻ_ڪوڊ (d) == C_TOKEN_VEC);
	    c_token *پهريون = C_TOKEN_VEC_ٽوڪن (d)->پتو ();
	    cnt++;
	    إذا (پهريون->type == CPP_NAME
		&& strcmp (IDENTIFIER_اشارو (پهريون->قدر),
			   directive) == 0)
	      {
		ڏٺل = سچ;
		إذا (وچ_loc == UNKNOWN_LOCATION)
		  وچ_loc = پهريون->location;
	      }
	  }
      }
  إذا (!ڏٺل)
    أرجع خطأ;
  إذا (cnt != 1 || وڻ_CHAIN (std_attrs))
    {
      error_at (make_location (پهريون_loc, آخري_loc, وچ_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      أرجع خطأ;
    }
  c_parser_handle_statement_omp_خاصيتون (parser, std_attrs, عدم);
  أرجع سچ;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

ساكن وڻ
c_parser_omp_structured_بلاڪ_sequence (c_parser *parser,
					تعداد pragma_قسم قسم)
{
  وڻ stmt = ڌڪو_stmt_list ();
  c_parser_statement (parser, عدم);
  افعل
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	اكسر;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_EOF))
	اكسر;

      إذا (قسم != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_قسم == قسم)
	اكسر;

      إذا (قسم != PRAGMA_NONE
	  && c_parser_omp_section_جاچ (parser,
					قسم == PRAGMA_OMP_جاچ
					? "scan" : "section", خطأ))
	اكسر;

      c_parser_statement (parser, عدم);
    }
  طالما (1);
  أرجع ڪڍو_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

ساكن فراغ
c_parser_omp_جاچ_loop_body (c_parser *parser, منطقي open_brace_parsed)
{
  وڻ substmt;
  location_t loc;
  وڻ clauses = NULL_وڻ;
  منطقي مليو_جاچ = خطأ;

  loc = c_parser_peek_token (parser)->location;
  إذا (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = خطأ;
      أرجع;
    }

  إذا (c_parser_peek_token (parser)->pragma_قسم != PRAGMA_OMP_جاچ)
    substmt = c_parser_omp_structured_بلاڪ_sequence (parser, PRAGMA_OMP_جاچ);
  وإلا
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_خالي_جايون_stmt (loc);
    }
  substmt = build2 (OMP_جاچ, void_type_ڳنڍ, substmt, NULL_وڻ);
  سيٽ_اظهار_LOCATION (substmt, loc);
  جوڙيو_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  إذا (c_parser_peek_token (parser)->pragma_قسم == PRAGMA_OMP_جاچ)
    {
      تعداد omp_clause_ڪوڊ clause = OMP_CLAUSE_ERROR;
      مليو_جاچ = سچ;

      c_parser_consume_pragma (parser);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	  إذا (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  وإلا إذا (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      إذا (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_وڻ);
	}
      وإلا
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_منزل_pragma_eol (parser);
    }
  وإلا
    error ("expected %<#pragma omp scan%>");

  clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP);
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_بلاڪ_sequence (parser, PRAGMA_NONE);
  وإلا
    {
      إذا (مليو_جاچ)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_خالي_جايون_stmt (loc);
    }
  substmt = build2 (OMP_جاچ, void_type_ڳنڍ, substmt, clauses);
  سيٽ_اظهار_LOCATION (substmt, loc);
  جوڙيو_stmt (substmt);

  c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
ساكن منطقي
c_parser_omp_ايندڙ_ٽوڪن_can_be_canon_loop (c_parser *parser,
					    تعداد وڻ_ڪوڊ_2 ڪوڊ,
					    منطقي error_p)
{
  إذا (ڪوڊ == OACC_LOOP)
    {
      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_FOR))
	أرجع سچ;
      إذا (error_p)
	c_parser_error (parser, "for statement expected");
    }
  وإلا
    {
      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_FOR))
	أرجع سچ;

      إذا (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA))
	بدل (c_parser_peek_token (parser)->pragma_قسم)
	  {
	  حالة PRAGMA_OMP_UNROLL:
	  حالة PRAGMA_OMP_TILE:
	    أرجع سچ;
	  افتراضي:
	    اكسر;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      سائيز_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      إذا (token->type == CPP_NAME
	  && C_IS_RESERVED_لفظ (token->قدر)
	  && C_RID_ڪوڊ (token->قدر) == RID_FOR)
	أرجع سچ;
      إذا (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  أرجع خطأ;
}

ساكن وڻ c_parser_omp_tile (location_t, c_parser *, منطقي *);
ساكن وڻ c_parser_omp_unroll (location_t, c_parser *, منطقي *);

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

ساكن وڻ
c_parser_omp_loop_nest (c_parser *parser, منطقي *if_p)
{
  وڻ decl = NULL_وڻ, cond = NULL_وڻ, incr = NULL_وڻ, init = NULL_وڻ;
  وڻ body = NULL_وڻ;
  matching_parens parens;
  منطقي moreloops;
  بنانشان حرف save_اندريون_statement;
  وڻ loop_scope;
  location_t loc;
  بنية omp_for_parse_معلومات *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  صحيح اونهائي = omp_for_parse_state->اونهائي;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  إذا (c_parser_nth_token_starts_std_خاصيتون (parser, 1))
    {
      وڻ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_خاصيتون (parser, std_attrs, عدم);
      إذا (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA))
    {
      وڻ transform = NULL_وڻ, sizes, body = NULL_وڻ;
      صحيح ڳڻپ = 0;
      بدل (c_parser_peek_token (parser)->pragma_قسم)
	{
	حالة PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = ڌڪو_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = ڪڍو_stmt_list (body);
	  إذا (transform == NULL_وڻ || transform == error_mark_ڳنڍ)
	    {
	      transform = error_mark_ڳنڍ;
	      اكسر;
	    }
	  gcc_assert (وڻ_ڪوڊ (transform) == OMP_UNROLL);
	  إذا (omp_ڳوليو_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      إذا (omp_for_parse_state->ڳڻپ - اونهائي > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->ڳڻپ - اونهائي);
		  transform = error_mark_ڳنڍ;
		}
	      وإلا
		ڳڻپ = 1;
	    }
	  وإلا
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_ڳنڍ;
	    }
	  اكسر;
	حالة PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = ڌڪو_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = ڪڍو_stmt_list (body);
	  إذا (transform == NULL_وڻ || transform == error_mark_ڳنڍ)
	    {
	      transform = error_mark_ڳنڍ;
	      اكسر;
	    }
	  gcc_assert (وڻ_ڪوڊ (transform) == OMP_TILE);
	  sizes = omp_ڳوليو_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  ڳڻپ = list_ڊيگهائي (OMP_CLAUSE_SIZES_LIST (sizes));
	  إذا (اونهائي + ڳڻپ < omp_for_parse_state->ڳڻپ)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			ڳڻپ, omp_for_parse_state->ڳڻپ - اونهائي);
	      transform = error_mark_ڳنڍ;
	    }
	  اكسر;
	افتراضي:
	  c_parser_pragma (parser, pragma_stmt, عدم, void_list_ڳنڍ);
	  اكسر;
	}
      إذا (transform == NULL_وڻ)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      إذا (transform == NULL_وڻ || transform == error_mark_ڳنڍ)
	{
	  omp_for_parse_state->fail = سچ;
	  أرجع NULL_وڻ;
	}
      لكل (ڳڻپ = omp_for_parse_state->ڳڻپ; اونهائي < ڳڻپ; ++اونهائي)
	{
	  وڻ_VEC_ELT (omp_for_parse_state->declv, اونهائي) = NULL_وڻ;
	  وڻ_VEC_ELT (omp_for_parse_state->initv, اونهائي) = NULL_وڻ;
	  وڻ_VEC_ELT (omp_for_parse_state->condv, اونهائي) = NULL_وڻ;
	  وڻ_VEC_ELT (omp_for_parse_state->incrv, اونهائي) = NULL_وڻ;
	}
      omp_for_parse_state->want_nested_loop = خطأ;
      أرجع body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_اندريون_statement = اندريون_statement;
  اندريون_statement = اندريون_OMP_بلاڪ;

  /* We are not in intervening code now.  */
  omp_for_parse_state->اندريون_intervening_ڪوڊ = خطأ;

  إذا (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = سچ;
      أرجع NULL_وڻ;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (سچ);

  /* Parse the initialization declaration or expression.  */
  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      وڻ this_pre_body = ڌڪو_stmt_list ();
      c_اندريون_omp_for = سچ;
      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ, سچ,
				     خطأ);
      c_اندريون_omp_for = خطأ;
      this_pre_body = ڪڍو_stmt_list (this_pre_body);
      append_منزل_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      إذا (decl == عدم)
	اذهب error_init;
      إذا (DECL_INITIAL (decl) == error_mark_ڳنڍ)
	decl = error_mark_ڳنڍ;
      init = decl;
    }
  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      بنية c_اظهار decl_exp;
      بنية c_اظهار init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_اظهار (parser);
      decl = decl_exp.قدر;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_اظهار_no_commas (parser, عدم);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_اندريون_omp_for = سچ;
      init = build_modify_اظهار (init_loc, decl, decl_exp.original_type,
				NOP_اظهار, init_loc, init_exp.قدر,
				init_exp.original_type);
      c_اندريون_omp_for = خطأ;
      init = c_process_اظهار_stmt (init_loc, init);

      c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  وإلا
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = سچ;
      اذهب parse_ايندڙ;
    }

  /* Parse the loop condition.  */
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_اندريون_omp_for = سچ;
      بنية c_اظهار cond_اظهار
	= c_parser_ٻٽو_اظهار (parser, عدم, NULL_وڻ);
      c_اندريون_omp_for = خطأ;

      cond = cond_اظهار.قدر;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      بدل (cond_اظهار.original_ڪوڊ)
	{
	حالة GT_اظهار:
	حالة GE_اظهار:
	حالة LT_اظهار:
	حالة LE_اظهار:
	  اكسر;
	حالة NE_اظهار:
	  إذا (omp_for_parse_state->ڪوڊ != OACC_LOOP)
	    اكسر;
	  /* FALLTHRU.  */
	افتراضي:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_اظهار, boolean_type_ڳنڍ, error_mark_ڳنڍ);
	  اكسر;
	}
      protected_سيٽ_اظهار_location (cond, cond_loc);
    }
  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_اظهار_stmt (incr_loc,
				  c_parser_اظهار (parser).قدر);
    }
  parens.skip_until_مليو_close (parser);

  إذا (decl == عدم || decl == error_mark_ڳنڍ || init == error_mark_ڳنڍ)
    omp_for_parse_state->fail = سچ;
  وإلا
    {
      وڻ_VEC_ELT (omp_for_parse_state->declv, اونهائي) = decl;
      وڻ_VEC_ELT (omp_for_parse_state->initv, اونهائي) = init;
      وڻ_VEC_ELT (omp_for_parse_state->condv, اونهائي) = cond;
      وڻ_VEC_ELT (omp_for_parse_state->incrv, اونهائي) = incr;
    }

parse_ايندڙ:
  moreloops = اونهائي < omp_for_parse_state->ڳڻپ - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  إذا (moreloops
      && c_parser_omp_ايندڙ_ٽوڪن_can_be_canon_loop (parser,
						     omp_for_parse_state->ڪوڊ,
						     خطأ))
    {
      omp_for_parse_state->اونهائي++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->اونهائي--;
    }
  وإلا إذا (moreloops && c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->اندريون_intervening_ڪوڊ = سچ;
      body = c_parser_compound_statement (parser, عدم);
      omp_for_parse_state->اندريون_intervening_ڪوڊ = خطأ;
      إذا (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = سچ;
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
	  omp_for_parse_state->fail = سچ;
	}
      اندريون_statement = اندريون_OMP_FOR;
      parser->omp_for_parse_state = عدم;
      body = ڌڪو_stmt_list ();
      إذا (omp_for_parse_state->inscan)
	c_parser_omp_جاچ_loop_body (parser, خطأ);
      وإلا
	جوڙيو_stmt (c_parser_c99_بلاڪ_statement (parser, if_p));
      body = ڪڍو_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  اندريون_statement = save_اندريون_statement;
  omp_for_parse_state->want_nested_loop = خطأ;
  omp_for_parse_state->اندريون_intervening_ڪوڊ = سچ;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  إذا (body)
    جوڙيو_stmt (body);
  body = c_پڇاڙي_compound_stmt (loc, loop_scope, سچ);
  إذا (decl && وڻ_ڪوڊ (body) == BIND_اظهار)
    {
      وڻ t = BIND_اظهار_VARS (body);
      وڻ prev = NULL_وڻ, ايندڙ = NULL_وڻ;
      طالما (t)
	{
	  ايندڙ = DECL_CHAIN (t);
	  إذا (t == decl)
	    {
	      إذا (prev)
		DECL_CHAIN (prev) = ايندڙ;
	      وإلا
		{
		  BIND_اظهار_VARS (body) = ايندڙ;
		  بلاڪ_VARS (BIND_اظهار_بلاڪ (body)) = ايندڙ;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      اكسر;
	    }
	  وإلا
	    {
	      prev = t;
	      t = ايندڙ;
	    }
	}
      إذا (BIND_اظهار_VARS (body) == NULL_وڻ)
	body = BIND_اظهار_BODY (body);
    }

  أرجع body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

ساكن وڻ
c_parser_omp_for_loop (location_t loc, c_parser *parser, تعداد وڻ_ڪوڊ_2 ڪوڊ,
		       وڻ clauses, وڻ *cclauses, منطقي *if_p)
{
  وڻ body, stmt, cl;
  وڻ ret = NULL_وڻ;
  وڻ ordered_cl = NULL_وڻ;
  صحيح i, collapse = 1, ordered = 0, ڳڻپ;
  منطقي oacc_tiling = خطأ;
  منطقي inscan = خطأ;
  بنية omp_for_parse_معلومات معلومات;
  بنية omp_for_parse_معلومات *save_معلومات = parser->omp_for_parse_state;

  لكل (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    إذا (OMP_CLAUSE_ڪوڊ (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = وڻ_منزل_shwi (OMP_CLAUSE_COLLAPSE_اظهار (cl));
    وإلا إذا (OMP_CLAUSE_ڪوڊ (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = سچ;
	collapse = list_ڊيگهائي (OMP_CLAUSE_TILE_LIST (cl));
      }
    وإلا إذا (OMP_CLAUSE_ڪوڊ (cl) == OMP_CLAUSE_SIZES)
      collapse = list_ڊيگهائي (OMP_CLAUSE_SIZES_LIST (cl));
    وإلا إذا (OMP_CLAUSE_ڪوڊ (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_اظهار (cl))
      {
	ordered_cl = cl;
	ordered = وڻ_منزل_shwi (OMP_CLAUSE_ORDERED_اظهار (cl));
      }
    وإلا إذا (OMP_CLAUSE_ڪوڊ (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (ڪوڊ == OMP_SIMD || ڪوڊ == OMP_FOR))
      inscan = سچ;

  إذا (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_اظهار (ordered_cl)
	= build_int_cst (integer_type_ڳنڍ, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  ڳڻپ = ordered ? ordered : collapse;

  إذا (!c_parser_omp_ايندڙ_ٽوڪن_can_be_canon_loop (parser, ڪوڊ, سچ))
    أرجع عدم;

  /* Initialize parse state for recursive descent.  */
  معلومات.declv = make_وڻ_vec (ڳڻپ);
  معلومات.initv = make_وڻ_vec (ڳڻپ);
  معلومات.condv = make_وڻ_vec (ڳڻپ);
  معلومات.incrv = make_وڻ_vec (ڳڻپ);
  معلومات.pre_body = NULL_وڻ;
  معلومات.bindings = NULL_وڻ;
  معلومات.for_loc = c_parser_peek_token (parser)->location;
  معلومات.ڳڻپ = ڳڻپ;
  معلومات.اونهائي = 0;
  معلومات.want_nested_loop = سچ;
  معلومات.ordered = ordered > 0;
  معلومات.اندريون_intervening_ڪوڊ = خطأ;
  معلومات.perfect_nesting_fail = خطأ;
  معلومات.fail = خطأ;
  معلومات.inscan = inscan;
  معلومات.saw_intervening_ڪوڊ = خطأ;
  معلومات.ڪوڊ = ڪوڊ;
  parser->omp_for_parse_state = &معلومات;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  لكل (وڻ t = معلومات.bindings; t; )
    {
      وڻ n = وڻ_CHAIN (t);
      وڻ_CHAIN (t) = NULL_وڻ;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  إذا (!معلومات.fail)
    {
      c_اندريون_omp_for = سچ;
      stmt = c_پڄاڻي_omp_for (loc, ڪوڊ, معلومات.declv, عدم, معلومات.initv,
			       معلومات.condv, معلومات.incrv,
			       body, معلومات.pre_body, سچ);
      c_اندريون_omp_for = خطأ;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      إذا (stmt && !c_omp_check_loop_iv (stmt, معلومات.declv, عدم))
	stmt = NULL_وڻ;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      إذا (معلومات.saw_intervening_ڪوڊ
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, عدم))
	stmt = NULL_وڻ;

      إذا (stmt)
	{
	  جوڙيو_stmt (stmt);

	  لكل (i = 0; i < وڻ_VEC_ڊيگهائي (OMP_FOR_INIT (stmt)); i++)
	    {
	      وڻ init = وڻ_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      إذا (init == NULL_وڻ)
		اكسر;
	      gcc_assert (وڻ_ڪوڊ (init) == MODIFY_اظهار);
	      وڻ decl = وڻ_عمليو (init, 0);
	      وڻ cond = وڻ_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (وڻ_عمليو (cond, 0) == decl);

	      وڻ op0 = وڻ_عمليو (init, 1);
	      إذا (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || وڻ_ڪوڊ (op0) != وڻ_VEC)
		وڻ_عمليو (init, 1) = c_fully_fold (op0, خطأ, عدم);
	      وإلا
		{
		  وڻ_VEC_ELT (op0, 1)
		    = c_fully_fold (وڻ_VEC_ELT (op0, 1), خطأ, عدم);
		  وڻ_VEC_ELT (op0, 2)
		    = c_fully_fold (وڻ_VEC_ELT (op0, 2), خطأ, عدم);
		}

	      وڻ op1 = وڻ_عمليو (cond, 1);
	      إذا (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || وڻ_ڪوڊ (op1) != وڻ_VEC)
		وڻ_عمليو (cond, 1) = c_fully_fold (op1, خطأ, عدم);
	      وإلا
		{
		  وڻ_VEC_ELT (op1, 1)
		    = c_fully_fold (وڻ_VEC_ELT (op1, 1), خطأ, عدم);
		  وڻ_VEC_ELT (op1, 2)
		    = c_fully_fold (وڻ_VEC_ELT (op1, 2), خطأ, عدم);
		}
	    }

	  إذا (cclauses != عدم
	      && cclauses[C_OMP_CLAUSE_ورهايو_PARALLEL] != عدم)
	    {
	      وڻ *c;
	      لكل (c = &cclauses[C_OMP_CLAUSE_ورهايو_PARALLEL]; *c ; )
		إذا (OMP_CLAUSE_ڪوڊ (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_ڪوڊ (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		وإلا
		  {
		    لكل (i = 0; i < ڳڻپ; i++)
		      إذا (وڻ_VEC_ELT (معلومات.declv, i) == OMP_CLAUSE_DECL (*c))
			اكسر;
		    إذا (i == ڳڻپ)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    وإلا إذا (OMP_CLAUSE_ڪوڊ (*c) == OMP_CLAUSE_FIRSTPRIVATE)
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
			وڻ l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			إذا (ڪوڊ == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_ورهايو_FOR];
			    cclauses[C_OMP_CLAUSE_ورهايو_FOR] = l;
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

  parser->omp_for_parse_state = save_معلومات;
  أرجع ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

ساكن فراغ
omp_ورهايو_clauses (location_t loc, تعداد وڻ_ڪوڊ_2 ڪوڊ,
		   omp_clause_نقاب نقاب, وڻ clauses, وڻ *cclauses)
{
  صحيح i;
  c_omp_ورهايو_clauses (loc, ڪوڊ, نقاب, clauses, cclauses);
  لكل (i = 0; i < C_OMP_CLAUSE_ورهايو_ڳڻپ; i++)
    إذا (cclauses[i])
      cclauses[i] = c_پڄاڻي_omp_clauses (cclauses[i],
					  i == C_OMP_CLAUSE_ورهايو_هدف
					  ? C_ORT_OMP_هدف : C_ORT_OMP);
}

/* OpenMP 5.0:
   #pragma omp loop loop-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#وصف_ڪريو OMP_LOOP_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_BIND)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترتيب))

ساكن وڻ
c_parser_omp_loop (location_t loc, c_parser *parser,
		   حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
		   منطقي *if_p)
{
  وڻ بلاڪ, clauses, ret;

  strcat (p_name, " loop");
  نقاب |= OMP_LOOP_CLAUSE_نقاب;

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_LOOP, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_LOOP];
    }

  بلاڪ = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

  أرجع ret;
}

/* OpenMP 4.0:
   #pragma omp simd simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#وصف_ڪريو OMP_SIMD_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SAFELEN)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_لڪيري)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NONTEMPORAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترتيب))

ساكن وڻ
c_parser_omp_simd (location_t loc, c_parser *parser,
		   حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
		   منطقي *if_p)
{
  وڻ بلاڪ, clauses, ret;

  strcat (p_name, " simd");
  نقاب |= OMP_SIMD_CLAUSE_نقاب;

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_SIMD, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_SIMD];
    }

  بلاڪ = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

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

#وصف_ڪريو OMP_FOR_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_لڪيري)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ORDERED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_وقت_جدول)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترتيب))

ساكن وڻ
c_parser_omp_for (location_t loc, c_parser *parser,
		  حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
		  منطقي *if_p)
{
  وڻ بلاڪ, clauses, ret;

  strcat (p_name, " for");
  نقاب |= OMP_FOR_CLAUSE_نقاب;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  إذا (cclauses && (نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  إذا ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DIST_وقت_جدول)) != 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

      إذا (strcmp (p, "simd") == 0)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses,
				      if_p);
	  بلاڪ = c_begin_compound_stmt (سچ);
	  ret = c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses, if_p);
	  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
	  إذا (ret == NULL_وڻ)
	    أرجع ret;
	  ret = make_ڳنڍ (OMP_FOR);
	  وڻ_TYPE (ret) = void_type_ڳنڍ;
	  OMP_FOR_BODY (ret) = بلاڪ;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_ورهايو_FOR];
	  سيٽ_اظهار_LOCATION (ret, loc);
	  جوڙيو_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع NULL_وڻ;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  إذا ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DIST_وقت_جدول)) != 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_لڪيري);

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_FOR, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_FOR];
    }

  بلاڪ = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

  أرجع ret;
}

ساكن وڻ c_parser_omp_taskloop (location_t, c_parser *, حرف *,
				   omp_clause_نقاب, وڻ *, منطقي *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

ساكن وڻ
c_parser_omp_master (location_t loc, c_parser *parser,
		     حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
		     منطقي *if_p, location_t master_loc)
{
  وڻ بلاڪ, clauses, ret;
  gcc_rich_location richloc (loc);
  إذا (master_loc != UNKNOWN_LOCATION)
    richloc.جوڙيو_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

      إذا (strcmp (p, "taskloop") == 0)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_taskloop (loc, parser, p_name, نقاب, cclauses,
					  if_p);
	  بلاڪ = c_begin_compound_stmt (سچ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, نقاب, cclauses,
				       if_p);
	  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
	  إذا (ret == NULL_وڻ)
	    أرجع ret;
	  ret = c_پڄاڻي_omp_master (loc, بلاڪ);
	  OMP_MASTER_COMBINED (ret) = 1;
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع NULL_وڻ;
    }

  إذا (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, خطأ);
      omp_ورهايو_clauses (loc, OMP_MASTER, نقاب, clauses, cclauses);
    }
  وإلا
    c_parser_skip_منزل_pragma_eol (parser);

  أرجع c_پڄاڻي_omp_master (loc, c_parser_omp_structured_بلاڪ (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#وصف_ڪريو OMP_MASKED_CLAUSE_نقاب					\
	(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FILTER)

ساكن وڻ
c_parser_omp_masked (location_t loc, c_parser *parser,
		     حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
		     منطقي *if_p)
{
  وڻ بلاڪ, clauses, ret;

  strcat (p_name, " masked");
  نقاب |= OMP_MASKED_CLAUSE_نقاب;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

      إذا (strcmp (p, "taskloop") == 0)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_taskloop (loc, parser, p_name, نقاب, cclauses,
					  if_p);
	  بلاڪ = c_begin_compound_stmt (سچ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, نقاب, cclauses,
				       if_p);
	  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
	  إذا (ret == NULL_وڻ)
	    أرجع ret;
	  ret = c_پڄاڻي_omp_masked (loc, بلاڪ,
				     cclauses[C_OMP_CLAUSE_ورهايو_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع NULL_وڻ;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_MASKED, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_MASKED];
    }

  أرجع c_پڄاڻي_omp_masked (loc, c_parser_omp_structured_بلاڪ (parser,
								  if_p),
			      clauses);
}

/* OpenMP 5.1:
   # pragma omp interop clauses[opt] new-line */

#وصف_ڪريو OMP_INTEROP_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DESTROY)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_INIT)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_USE))

ساكن فراغ
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  وڻ clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_نقاب,
					   "#pragma omp interop");
  وڻ stmt = make_ڳنڍ (OMP_INTEROP);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);
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

#وصف_ڪريو OMP_ORDERED_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ڌاڳا)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SIMD))

#وصف_ڪريو OMP_ORDERED_DEPEND_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DOACROSS))

ساكن منطقي
c_parser_omp_ordered (c_parser *parser, تعداد pragma_context context,
		      منطقي *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  إذا (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع خطأ;
    }

  صحيح n = 1;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    n = 2;

  إذا (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ثابت حرف *p
	= IDENTIFIER_اشارو (c_parser_peek_nth_token (parser, n)->قدر);

      إذا (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  إذا (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_منزل_pragma_eol (parser, خطأ);
	      أرجع خطأ;
	    }
	  إذا (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_منزل_pragma_eol (parser, خطأ);
	      أرجع سچ;
	    }

	  وڻ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_نقاب,
					"#pragma omp ordered");
	  c_پڄاڻي_omp_ordered (loc, clauses, NULL_وڻ);
	  أرجع خطأ;
	}
    }

  وڻ clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_نقاب,
					   "#pragma omp ordered");

  إذا (!flag_openmp	/* flag_openmp_simd  */
      && omp_ڳوليو_clause (clauses, OMP_CLAUSE_SIMD) == NULL_وڻ)
    أرجع خطأ;

  c_پڄاڻي_omp_ordered (loc, clauses,
			c_parser_omp_structured_بلاڪ (parser, if_p));
  أرجع سچ;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

ساكن وڻ
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  وڻ stmt, substmt;
  منطقي error_suppress = خطأ;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = خطأ;
      أرجع NULL_وڻ;
    }

  stmt = ڌڪو_stmt_list ();

  إذا (c_parser_peek_token (parser)->pragma_قسم != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_جاچ (parser, "section", سچ))
    {
      substmt = c_parser_omp_structured_بلاڪ_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ڳنڍ, substmt);
      سيٽ_اظهار_LOCATION (substmt, loc);
      جوڙيو_stmt (substmt);
    }

  طالما (1)
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
	اكسر;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_EOF))
	اكسر;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_جاچ (parser, "section", خطأ);
      إذا (c_parser_peek_token (parser)->pragma_قسم == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_منزل_pragma_eol (parser);
	  error_suppress = خطأ;
	}
      وإلا إذا (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = سچ;
	}

      substmt = c_parser_omp_structured_بلاڪ_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ڳنڍ, substmt);
      سيٽ_اظهار_LOCATION (substmt, loc);
      جوڙيو_stmt (substmt);
    }
  c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = ڪڍو_stmt_list (stmt);

  stmt = make_ڳنڍ (OMP_SECTIONS);
  سيٽ_اظهار_LOCATION (stmt, sections_loc);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OMP_SECTIONS_BODY (stmt) = substmt;

  أرجع جوڙيو_stmt (stmt);
}

/* OpenMP 2.5:
   # pragma omp sections sections-clause[optseq] newline
     sections-scope

   LOC is the location of the #pragma token.
*/

#وصف_ڪريو OMP_SECTIONS_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن وڻ
c_parser_omp_sections (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses)
{
  وڻ بلاڪ, clauses, ret;

  strcat (p_name, " sections");
  نقاب |= OMP_SECTIONS_CLAUSE_نقاب;
  إذا (cclauses)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_SECTIONS, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_SECTIONS];
    }

  بلاڪ = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_sections_scope (loc, parser);
  إذا (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

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

#وصف_ڪريو OMP_PARALLEL_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COPYIN)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_انگ_ڌاڳا)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

ساكن وڻ
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
		       منطقي *if_p)
{
  وڻ stmt, clauses, بلاڪ;

  strcat (p_name, " parallel");
  نقاب |= OMP_PARALLEL_CLAUSE_نقاب;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  إذا ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DIST_وقت_جدول)) == 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_FOR))
    {
      وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
      إذا (cclauses == عدم)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      إذا (!flag_openmp)  /* flag_openmp_simd  */
	أرجع c_parser_omp_for (loc, parser, p_name, نقاب, cclauses, if_p);
      بلاڪ = c_begin_omp_parallel ();
      وڻ ret = c_parser_omp_for (loc, parser, p_name, نقاب, cclauses, if_p);
      stmt
	= c_پڄاڻي_omp_parallel (loc, cclauses[C_OMP_CLAUSE_ورهايو_PARALLEL],
				 بلاڪ);
      إذا (ret == NULL_وڻ)
	أرجع ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      أرجع stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  وإلا إذا (cclauses
	   && (نقاب & (OMP_CLAUSE_نقاب_1
		       << PRAGMA_OMP_CLAUSE_DIST_وقت_جدول)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_منزل_pragma_eol (parser);
      أرجع NULL_وڻ;
    }
  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      location_t ploc = c_parser_peek_token (parser)->location;
      إذا (cclauses == عدم && strcmp (p, "masked") == 0)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_masked (loc, parser, p_name, نقاب, cclauses,
					if_p);
	  بلاڪ = c_begin_omp_parallel ();
	  وڻ ret = c_parser_omp_masked (loc, parser, p_name, نقاب, cclauses,
					  if_p);
	  stmt = c_پڄاڻي_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_ورهايو_PARALLEL],
					بلاڪ);
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
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_master (loc, parser, p_name, نقاب, cclauses,
					if_p, ploc);
	  بلاڪ = c_begin_omp_parallel ();
	  وڻ ret = c_parser_omp_master (loc, parser, p_name, نقاب, cclauses,
					  if_p, ploc);
	  stmt = c_پڄاڻي_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_ورهايو_PARALLEL],
					بلاڪ);
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
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_loop (loc, parser, p_name, نقاب, cclauses,
				      if_p);
	  بلاڪ = c_begin_omp_parallel ();
	  وڻ ret = c_parser_omp_loop (loc, parser, p_name, نقاب, cclauses,
					if_p);
	  stmt
	    = c_پڄاڻي_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_ورهايو_PARALLEL],
				     بلاڪ);
	  إذا (ret == NULL_وڻ)
	    أرجع ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
      وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
	  أرجع NULL_وڻ;
	}
      وإلا إذا (cclauses == عدم && strcmp (p, "sections") == 0)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  بلاڪ = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, نقاب, cclauses);
	  stmt = c_پڄاڻي_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_ورهايو_PARALLEL],
					بلاڪ);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  أرجع stmt;
	}
    }
  وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع NULL_وڻ;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_PARALLEL, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_PARALLEL];
    }

  بلاڪ = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = سچ;
  c_parser_statement (parser, if_p);
  stmt = c_پڄاڻي_omp_parallel (loc, clauses, بلاڪ);

  أرجع stmt;
}

/* OpenMP 2.5:
   # pragma omp single single-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#وصف_ڪريو OMP_SINGLE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COPYPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن وڻ
c_parser_omp_single (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ stmt = make_ڳنڍ (OMP_SINGLE);
  سيٽ_اظهار_LOCATION (stmt, loc);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_نقاب,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_بلاڪ (parser, if_p);

  أرجع جوڙيو_stmt (stmt);
}

/* OpenMP 5.1:
   # pragma omp scope scope-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#وصف_ڪريو OMP_SCOPE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن وڻ
c_parser_omp_scope (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ stmt = make_ڳنڍ (OMP_SCOPE);
  سيٽ_اظهار_LOCATION (stmt, loc);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_نقاب,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_بلاڪ (parser, if_p);

  أرجع جوڙيو_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
ساكن وڻ
c_parser_omp_dispatch_body (c_parser *parser)
{
  بنية c_اظهار lhs, rhs, ret;
  location_t اظهار_loc = c_parser_peek_token (parser)->location;
  ذريعو_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_اظهار (parser, عدم, عدم);
  إذا (وڻ_ڪوڊ (lhs.قدر) == CALL_اظهار)
    أرجع lhs.قدر;

  location_t op_location = c_parser_peek_token (parser)->location;
  إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    أرجع error_mark_ڳنڍ;

  /* Parse function name.  */
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      أرجع error_mark_ڳنڍ;
    }
  اظهار_loc = c_parser_peek_token (parser)->location;
  وڻ id = c_parser_peek_token (parser)->قدر;
  c_parser_consume_token (parser);
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      أرجع error_mark_ڳنڍ;
    }

  rhs.قدر = build_external_ref (اظهار_loc, id, سچ, &rhs.original_type);
  سيٽ_c_اظهار_ذريعو_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_اظهار_after_primary (
    parser, اظهار_LOC_OR_LOC (rhs.قدر, اظهار_loc), rhs);
  إذا (وڻ_ڪوڊ (rhs.قدر) != CALL_اظهار)
    {
      error_at (اظهار_LOC_OR_LOC (rhs.قدر, اظهار_loc),
		"expected target-function call");
      أرجع error_mark_ڳنڍ;
    }

  /* Build assignment. */
  rhs = convert_lvalue_منزل_rvalue (اظهار_loc, rhs, سچ, سچ);
  ret.قدر
    = build_modify_اظهار (op_location, lhs.قدر, lhs.original_type, NOP_اظهار,
			 اظهار_loc, rhs.قدر, rhs.original_type);
  ret.m_decimal = 0;
  سيٽ_c_اظهار_ذريعو_range (&ret, lhs.get_شروعات (), rhs.get_پڄاڻي ());
  ret.original_ڪوڊ = MODIFY_اظهار;
  ret.original_type = عدم;
  أرجع ret.قدر;
}

/* OpenMP 5.1:
   # pragma omp dispatch dispatch-clause[optseq] new-line
     expression-stmt

   LOC is the location of the #pragma.
*/

#وصف_ڪريو OMP_DISPATCH_CLAUSE_نقاب                                               \
  ((OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)                             \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)                           \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOVARIANTS)                       \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOCONTEXT)                        \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR)                  \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_INTEROP)                          \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)                    \
   | (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن وڻ
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  وڻ stmt = make_ڳنڍ (OMP_DISPATCH);
  سيٽ_اظهار_LOCATION (stmt, loc);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_نقاب,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  وڻ depend_clauses = NULL_وڻ;
  وڻ *depend_clauses_ptr = &depend_clauses;
  لكل (وڻ c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  إذا (depend_clauses != NULL_وڻ)
    {
      وڻ stmt = make_ڳنڍ (OMP_TASK);
      وڻ_TYPE (stmt) = void_ڳنڍ;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_وڻ;
      سيٽ_اظهار_LOCATION (stmt, loc);
      جوڙيو_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  وڻ dispatch_body = c_parser_omp_dispatch_body (parser);
  إذا (dispatch_body == error_mark_ڳنڍ)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser);
      أرجع NULL_وڻ;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (وڻ_ڪوڊ (dispatch_body) == CALL_اظهار
	      || وڻ_ڪوڊ (dispatch_body) == MODIFY_اظهار);
  وڻ *dispatch_call = وڻ_ڪوڊ (dispatch_body) == MODIFY_اظهار
			  ? &وڻ_عمليو (dispatch_body, 1)
			  : &dispatch_body;
  طالما (وڻ_ڪوڊ (*dispatch_call) == FLOAT_اظهار
	 || وڻ_ڪوڊ (*dispatch_call) == CONVERT_اظهار
	 || وڻ_ڪوڊ (*dispatch_call) == NOP_اظهار)
    dispatch_call = &وڻ_عمليو (*dispatch_call, 0);
  *dispatch_call = build_call_اظهار_اندروني_loc (
    loc, IFN_GOMP_DISPATCH,
    وڻ_TYPE (وڻ_TYPE (CALL_اظهار_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_مليو (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  أرجع جوڙيو_stmt (stmt);
}

/* OpenMP 3.0:
   # pragma omp task task-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#وصف_ڪريو OMP_TASK_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترجيح)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اندريون_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DETACH)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_AFFINITY))

ساكن وڻ
c_parser_omp_task (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ clauses, بلاڪ;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_نقاب,
				      "#pragma omp task");

  بلاڪ = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = سچ;
  c_parser_statement (parser, if_p);
  أرجع c_پڄاڻي_omp_task (loc, clauses, بلاڪ);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#وصف_ڪريو OMP_TASKWAIT_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن فراغ
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  وڻ clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_نقاب,
				"#pragma omp taskwait");

  إذا (clauses)
    {
      وڻ stmt = make_ڳنڍ (OMP_TASK);
      وڻ_TYPE (stmt) = void_ڳنڍ;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_وڻ;
      سيٽ_اظهار_LOCATION (stmt, loc);
      جوڙيو_stmt (stmt);
    }
  وإلا
    c_پڄاڻي_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

ساكن فراغ
c_parser_omp_taskyield (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_منزل_pragma_eol (parser);

  c_پڄاڻي_omp_taskyield (loc);
}

/* OpenMP 4.0:
   # pragma omp taskgroup new-line

   OpenMP 5.0:
   # pragma omp taskgroup taskgroup-clause[optseq] new-line
*/

#وصف_ڪريو OMP_TASKGROUP_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_TASK_REDUCTION))

ساكن وڻ
c_parser_omp_taskgroup (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_نقاب,
					   "#pragma omp taskgroup");

  وڻ body = c_parser_omp_structured_بلاڪ (parser, if_p);
  أرجع c_پڄاڻي_omp_taskgroup (loc, body, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancel cancel-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#وصف_ڪريو OMP_CANCEL_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_TASKGROUP)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF))

ساكن فراغ
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  وڻ clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_نقاب,
					   "#pragma omp cancel");

  c_پڄاڻي_omp_cancel (loc, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancellation point cancelpt-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#وصف_ڪريو OMP_CANCELLATION_نقطو_CLAUSE_نقاب			\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_TASKGROUP))

ساكن منطقي
c_parser_omp_cancellation_نقطو (c_parser *parser, تعداد pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ clauses;
  منطقي نقطو_ڏٺل = خطأ;

  c_parser_consume_pragma (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  نقطو_ڏٺل = سچ;
	}
    }
  إذا (!نقطو_ڏٺل)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_منزل_pragma_eol (parser);
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
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع سچ;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_نقطو_CLAUSE_نقاب,
				"#pragma omp cancellation point");

  c_پڄاڻي_omp_cancellation_نقطو (loc, clauses);
  أرجع سچ;
}

/* OpenMP 4.0:
   #pragma omp distribute distribute-clause[optseq] new-line
     for-loop  */

#وصف_ڪريو OMP_DISTRIBUTE_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DIST_وقت_جدول)\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترتيب))

ساكن وڻ
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
			 منطقي *if_p)
{
  وڻ clauses, بلاڪ, ret;

  strcat (p_name, " distribute");
  نقاب |= OMP_DISTRIBUTE_CLAUSE_نقاب;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      منطقي simd = خطأ;
      منطقي parallel = خطأ;

      إذا (strcmp (p, "simd") == 0)
	simd = سچ;
      وإلا
	parallel = strcmp (p, "parallel") == 0;
      إذا (parallel || simd)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      إذا (simd)
		أرجع c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses,
					  if_p);
	      وإلا
		أرجع c_parser_omp_parallel (loc, parser, p_name, نقاب,
					      cclauses, if_p);
	    }
	  بلاڪ = c_begin_compound_stmt (سچ);
	  إذا (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses,
				     if_p);
	  وإلا
	    ret = c_parser_omp_parallel (loc, parser, p_name, نقاب, cclauses,
					 if_p);
	  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
	  إذا (ret == عدم)
	    أرجع ret;
	  ret = make_ڳنڍ (OMP_DISTRIBUTE);
	  وڻ_TYPE (ret) = void_type_ڳنڍ;
	  OMP_FOR_BODY (ret) = بلاڪ;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_ورهايو_DISTRIBUTE];
	  سيٽ_اظهار_LOCATION (ret, loc);
	  جوڙيو_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع NULL_وڻ;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_DISTRIBUTE, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_DISTRIBUTE];
    }

  بلاڪ = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, عدم,
			       if_p);
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

  أرجع ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#وصف_ڪريو OMP_TEAMS_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_انگ_TEAMS)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_THREAD_حد_بندي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

ساكن وڻ
c_parser_omp_teams (location_t loc, c_parser *parser,
		    حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
		    منطقي *if_p)
{
  وڻ clauses, بلاڪ, ret;

  strcat (p_name, " teams");
  نقاب |= OMP_TEAMS_CLAUSE_نقاب;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "distribute") == 0)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_distribute (loc, parser, p_name, نقاب,
					    cclauses, if_p);
	  بلاڪ = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, نقاب, cclauses,
					 if_p);
	  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
	  إذا (ret == عدم)
	    أرجع ret;
	  clauses = cclauses[C_OMP_CLAUSE_ورهايو_TEAMS];
	  ret = make_ڳنڍ (OMP_TEAMS);
	  وڻ_TYPE (ret) = void_type_ڳنڍ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = بلاڪ;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  سيٽ_اظهار_LOCATION (ret, loc);
	  أرجع جوڙيو_stmt (ret);
	}
      وإلا إذا (strcmp (p, "loop") == 0)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_loop (loc, parser, p_name, نقاب, cclauses,
				      if_p);
	  بلاڪ = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, نقاب, cclauses, if_p);
	  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
	  إذا (ret == عدم)
	    أرجع ret;
	  clauses = cclauses[C_OMP_CLAUSE_ورهايو_TEAMS];
	  ret = make_ڳنڍ (OMP_TEAMS);
	  وڻ_TYPE (ret) = void_type_ڳنڍ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = بلاڪ;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  سيٽ_اظهار_LOCATION (ret, loc);
	  أرجع جوڙيو_stmt (ret);
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع NULL_وڻ;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_TEAMS, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_TEAMS];
    }

  وڻ stmt = make_ڳنڍ (OMP_TEAMS);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  بلاڪ = c_begin_omp_parallel ();
  جوڙيو_stmt (c_parser_omp_structured_بلاڪ (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  سيٽ_اظهار_LOCATION (stmt, loc);

  أرجع جوڙيو_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target data target-data-clause[optseq] new-line
     structured-block  */

#وصف_ڪريو OMP_هدف_معلومات_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR) \
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR))

ساكن وڻ
c_parser_omp_هدف_معلومات (location_t loc, c_parser *parser, منطقي *if_p)
{
  إذا (flag_openmp)
    omp_requires_نقاب
      = (تعداد omp_requires) (omp_requires_نقاب | OMP_REQUIRES_هدف_استعمال_ٿيل);

  وڻ clauses
    = c_parser_omp_all_clauses (parser, OMP_هدف_معلومات_CLAUSE_نقاب,
				"#pragma omp target data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_ڏٺل = 0;
  لكل (وڻ *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_ڪوڊ (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_قسم (*pc))
	  {
	  حالة GOMP_MAP_منزل:
	  حالة GOMP_MAP_ALWAYS_منزل:
	  حالة GOMP_MAP_PRESENT_منزل:
	  حالة GOMP_MAP_ALWAYS_PRESENT_منزل:
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
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_اشارو:
	  حالة GOMP_MAP_ALWAYS_اشارو:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_ATTACH:
	    اكسر;
	  افتراضي:
	    map_ڏٺل |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      وإلا إذا (OMP_CLAUSE_ڪوڊ (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_ڪوڊ (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_ڏٺل = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_ڏٺل != 3)
    {
      إذا (map_ڏٺل == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      أرجع NULL_وڻ;
    }

  وڻ stmt = make_ڳنڍ (OMP_هدف_معلومات);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OMP_هدف_معلومات_CLAUSES (stmt) = clauses;
  keep_ايندڙ_level ();
  وڻ بلاڪ = c_begin_compound_stmt (سچ);
  جوڙيو_stmt (c_parser_omp_structured_بلاڪ (parser, if_p));
  OMP_هدف_معلومات_BODY (stmt) = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);

  سيٽ_اظهار_LOCATION (stmt, loc);
  أرجع جوڙيو_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target update target-update-clause[optseq] new-line */

#وصف_ڪريو OMP_هدف_UPDATE_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FROM)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_منزل)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن منطقي
c_parser_omp_هدف_update (location_t loc, c_parser *parser,
			    تعداد pragma_context context)
{
  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع سچ;
    }

  وڻ clauses
    = c_parser_omp_all_clauses (parser, OMP_هدف_UPDATE_CLAUSE_نقاب,
				"#pragma omp target update",
				/* finish_p = */ خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  إذا (omp_ڳوليو_clause (clauses, OMP_CLAUSE_منزل) == NULL_وڻ
      && omp_ڳوليو_clause (clauses, OMP_CLAUSE_FROM) == NULL_وڻ)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      أرجع خطأ;
    }

  إذا (flag_openmp)
    omp_requires_نقاب
      = (تعداد omp_requires) (omp_requires_نقاب | OMP_REQUIRES_هدف_استعمال_ٿيل);

  وڻ stmt = make_ڳنڍ (OMP_هدف_UPDATE);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OMP_هدف_UPDATE_CLAUSES (stmt) = clauses;
  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);
  أرجع خطأ;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#وصف_ڪريو OMP_هدف_ENTER_معلومات_CLAUSE_نقاب			\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن منطقي
c_parser_omp_هدف_enter_معلومات (location_t loc, c_parser *parser,
				تعداد pragma_context context)
{
  منطقي معلومات_ڏٺل = خطأ;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  معلومات_ڏٺل = سچ;
	}
    }
  إذا (!معلومات_ڏٺل)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_منزل_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع سچ;
    }

  إذا (flag_openmp)
    omp_requires_نقاب
      = (تعداد omp_requires) (omp_requires_نقاب | OMP_REQUIRES_هدف_استعمال_ٿيل);

  وڻ clauses
    = c_parser_omp_all_clauses (parser, OMP_هدف_ENTER_معلومات_CLAUSE_نقاب,
				"#pragma omp target enter data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_ڏٺل = 0;
  لكل (وڻ *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_ڪوڊ (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_قسم (*pc))
	  {
	  حالة GOMP_MAP_منزل:
	  حالة GOMP_MAP_ALWAYS_منزل:
	  حالة GOMP_MAP_PRESENT_منزل:
	  حالة GOMP_MAP_ALWAYS_PRESENT_منزل:
	  حالة GOMP_MAP_ALLOC:
	  حالة GOMP_MAP_PRESENT_ALLOC:
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_TOFROM:
	    OMP_CLAUSE_سيٽ_MAP_قسم (*pc, GOMP_MAP_منزل);
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_سيٽ_MAP_قسم (*pc, GOMP_MAP_ALWAYS_منزل);
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_سيٽ_MAP_قسم (*pc, GOMP_MAP_PRESENT_منزل);
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_سيٽ_MAP_قسم (*pc, GOMP_MAP_ALWAYS_PRESENT_منزل);
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_اشارو:
	  حالة GOMP_MAP_ALWAYS_اشارو:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_ATTACH:
	    اكسر;
	  افتراضي:
	    map_ڏٺل |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_ڏٺل != 3)
    {
      إذا (map_ڏٺل == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      أرجع سچ;
    }

  وڻ stmt = make_ڳنڍ (OMP_هدف_ENTER_معلومات);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OMP_هدف_ENTER_معلومات_CLAUSES (stmt) = clauses;
  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);
  أرجع سچ;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#وصف_ڪريو OMP_هدف_EXIT_معلومات_CLAUSE_نقاب			\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ساكن منطقي
c_parser_omp_هدف_exit_معلومات (location_t loc, c_parser *parser,
			       تعداد pragma_context context)
{
  منطقي معلومات_ڏٺل = خطأ;
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  معلومات_ڏٺل = سچ;
	}
    }
  إذا (!معلومات_ڏٺل)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_منزل_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع سچ;
    }

  إذا (flag_openmp)
    omp_requires_نقاب
      = (تعداد omp_requires) (omp_requires_نقاب | OMP_REQUIRES_هدف_استعمال_ٿيل);

  وڻ clauses
    = c_parser_omp_all_clauses (parser, OMP_هدف_EXIT_معلومات_CLAUSE_نقاب,
				"#pragma omp target exit data", خطأ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_معلومات);
  clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP_EXIT_معلومات);
  c_omp_adjust_map_clauses (clauses, خطأ);
  صحيح map_ڏٺل = 0;
  لكل (وڻ *pc = &clauses; *pc;)
    {
      إذا (OMP_CLAUSE_ڪوڊ (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_قسم (*pc))
	  {
	  حالة GOMP_MAP_FROM:
	  حالة GOMP_MAP_ALWAYS_FROM:
	  حالة GOMP_MAP_PRESENT_FROM:
	  حالة GOMP_MAP_ALWAYS_PRESENT_FROM:
	  حالة GOMP_MAP_RELEASE:
	  حالة GOMP_MAP_DELETE:
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_TOFROM:
	    OMP_CLAUSE_سيٽ_MAP_قسم (*pc, GOMP_MAP_FROM);
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_سيٽ_MAP_قسم (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_سيٽ_MAP_قسم (*pc, GOMP_MAP_PRESENT_FROM);
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_سيٽ_MAP_قسم (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_ڏٺل = 3;
	    اكسر;
	  حالة GOMP_MAP_FIRSTPRIVATE_اشارو:
	  حالة GOMP_MAP_ALWAYS_اشارو:
	  حالة GOMP_MAP_ATTACH_DETACH:
	  حالة GOMP_MAP_DETACH:
	    اكسر;
	  افتراضي:
	    map_ڏٺل |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    استمر;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  إذا (map_ڏٺل != 3)
    {
      إذا (map_ڏٺل == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      أرجع سچ;
    }

  وڻ stmt = make_ڳنڍ (OMP_هدف_EXIT_معلومات);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;
  OMP_هدف_EXIT_معلومات_CLAUSES (stmt) = clauses;
  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);
  أرجع سچ;
}

/* OpenMP 4.0:
   # pragma omp target target-clause[optseq] new-line
     structured-block  */

#وصف_ڪريو OMP_هدف_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULTMAP)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE) \
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR) \
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اندريون_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_THREAD_حد_بندي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_استعمال_ڪري_ALLOCATORS))

ساكن منطقي
c_parser_omp_هدف (c_parser *parser, تعداد pragma_context context, منطقي *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  وڻ *pc = عدم, stmt, بلاڪ, body, clauses;

  إذا (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_منزل_pragma_eol (parser);
      أرجع خطأ;
    }

  إذا (flag_openmp)
    omp_requires_نقاب
      = (تعداد omp_requires) (omp_requires_نقاب | OMP_REQUIRES_هدف_استعمال_ٿيل);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      تعداد وڻ_ڪوڊ_2 ccode = ERROR_MARK;

      إذا (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      وإلا إذا (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      وإلا إذا (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      إذا (ccode != ERROR_MARK)
	{
	  وڻ cclauses[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  حرف p_name[حجم ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      وڻ stmt;
	      بدل (ccode)
		{
		حالة OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_هدف_CLAUSE_نقاب,
					     cclauses, if_p);
		  اكسر;
		حالة OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_هدف_CLAUSE_نقاب,
						cclauses, if_p);
		  اكسر;
		حالة OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_هدف_CLAUSE_نقاب,
					    cclauses, if_p);
		  اكسر;
		افتراضي:
		  gcc_unreachable ();
		}
	      أرجع stmt != NULL_وڻ;
	    }
	  keep_ايندڙ_level ();
	  وڻ بلاڪ = c_begin_compound_stmt (سچ), ret;
	  بدل (ccode)
	    {
	    حالة OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_هدف_CLAUSE_نقاب, cclauses,
					if_p);
	      اكسر;
	    حالة OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_هدف_CLAUSE_نقاب, cclauses,
					   if_p);
	      اكسر;
	    حالة OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_هدف_CLAUSE_نقاب, cclauses,
				       if_p);
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
	  إذا (ret == NULL_وڻ)
	    أرجع خطأ;
	  إذا (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    لكل (وڻ c = cclauses[C_OMP_CLAUSE_ورهايو_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_انگ_TEAMS
		  || OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_THREAD_حد_بندي)
		لكل (صحيح i = 0;
		     i <= (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_انگ_TEAMS); ++i)
		  إذا (OMP_CLAUSE_عمليو (c, i)
		      && وڻ_ڪوڊ (OMP_CLAUSE_عمليو (c, i)) != INTEGER_CST)
		    {
		      وڻ اظهار = OMP_CLAUSE_عمليو (c, i);
		      وڻ tmp = create_tmp_var_raw (وڻ_TYPE (اظهار));
		      اظهار = build4 (هدف_اظهار, وڻ_TYPE (اظهار), tmp,
				     اظهار, NULL_وڻ, NULL_وڻ);
		      جوڙيو_stmt (اظهار);
		      OMP_CLAUSE_عمليو (c, i) = اظهار;
		      وڻ tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_ورهايو_هدف];
		      cclauses[C_OMP_CLAUSE_ورهايو_هدف] = tc;
		    }
	  وڻ stmt = make_ڳنڍ (OMP_هدف);
	  وڻ_TYPE (stmt) = void_type_ڳنڍ;
	  OMP_هدف_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_ورهايو_هدف];
	  c_omp_adjust_map_clauses (OMP_هدف_CLAUSES (stmt), سچ);
	  OMP_هدف_BODY (stmt) = بلاڪ;
	  OMP_هدف_COMBINED (stmt) = 1;
	  سيٽ_اظهار_LOCATION (stmt, loc);
	  جوڙيو_stmt (stmt);
	  pc = &OMP_هدف_CLAUSES (stmt);
	  اذهب check_clauses;
	}
      وإلا إذا (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
	  أرجع خطأ;
	}
      وإلا إذا (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_هدف_معلومات (loc, parser, if_p);
	  أرجع سچ;
	}
      وإلا إذا (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_هدف_enter_معلومات (loc, parser, context);
	}
      وإلا إذا (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_هدف_exit_معلومات (loc, parser, context);
	}
      وإلا إذا (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  أرجع c_parser_omp_هدف_update (loc, parser, context);
	}
    }
  إذا (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع خطأ;
    }

  stmt = make_ڳنڍ (OMP_هدف);
  وڻ_TYPE (stmt) = void_type_ڳنڍ;

  clauses = c_parser_omp_all_clauses (parser, OMP_هدف_CLAUSE_نقاب,
				      "#pragma omp target", خطأ);
  لكل (وڻ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_اندريون_REDUCTION)
      {
	وڻ nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_سيٽ_MAP_قسم (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_هدف);
  clauses  = c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP_هدف);
  c_omp_adjust_map_clauses (clauses, سچ);

  keep_ايندڙ_level ();
  بلاڪ = c_begin_compound_stmt (سچ);
  body = c_parser_omp_structured_بلاڪ (parser, if_p);

  c_omp_جاچ_mapper_bindings (loc, &clauses, body);

  جوڙيو_stmt (body);
  OMP_هدف_CLAUSES (stmt) = clauses;
  pc = &OMP_هدف_CLAUSES (stmt);
  OMP_هدف_BODY (stmt) = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);

  سيٽ_اظهار_LOCATION (stmt, loc);
  جوڙيو_stmt (stmt);

check_clauses:
  طالما (*pc)
    {
      إذا (OMP_CLAUSE_ڪوڊ (*pc) == OMP_CLAUSE_MAP)
	بدل (OMP_CLAUSE_MAP_قسم (*pc))
	  {
	  حالة GOMP_MAP_منزل:
	  حالة GOMP_MAP_ALWAYS_منزل:
	  حالة GOMP_MAP_PRESENT_منزل:
	  حالة GOMP_MAP_ALWAYS_PRESENT_منزل:
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
	  حالة GOMP_MAP_FIRSTPRIVATE_اشارو:
	  حالة GOMP_MAP_ALWAYS_اشارو:
	  حالة GOMP_MAP_اشارو:
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
  cfun->has_omp_هدف = سچ;
  أرجع سچ;
}

/* OpenMP 4.0:
   # pragma omp declare simd declare-simd-clauses[optseq] new-line

   OpenMP 5.0:
   # pragma omp declare variant (identifier) match(context-selector) new-line

   OpenMP 5.1
   # pragma omp declare variant (identifier) match(context-selector) \
      adjust_args(adjust-op:argument-list) append_args(interop-list) new-line
   */

#وصف_ڪريو OMP_DECLARE_SIMD_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_لڪيري)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_هڪجهڙو)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_INBRANCH)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOTINBRANCH))

ساكن فراغ
c_parser_omp_declare_simd (c_parser *parser, تعداد pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  وڻ قسم = token->قدر;
  gcc_assert (strcmp (IDENTIFIER_اشارو (قسم), "simd") == 0
	      || strcmp (IDENTIFIER_اشارو (قسم), "variant") == 0);

  auto_vec<c_token> clauses;
  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      إذا (token->type == CPP_EOF)
	{
	  c_parser_skip_منزل_pragma_eol (parser);
	  أرجع;
	}
      clauses.محفوظ_ڌڪو (*token);
      c_parser_consume_token (parser);
    }
  clauses.محفوظ_ڌڪو (*c_parser_peek_token (parser));
  c_parser_skip_منزل_pragma_eol (parser);

  طالما (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA))
    {
      إذا (c_parser_peek_token (parser)->pragma_قسم != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->قدر != قسم)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_اشارو (قسم), IDENTIFIER_اشارو (قسم));
	  أرجع;
	}
      c_parser_consume_pragma (parser);
      طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    {
	      c_parser_skip_منزل_pragma_eol (parser);
	      أرجع;
	    }
	  clauses.محفوظ_ڌڪو (*token);
	  c_parser_consume_token (parser);
	}
      clauses.محفوظ_ڌڪو (*c_parser_peek_token (parser));
      c_parser_skip_منزل_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, حجم (eof_token));
  eof_token.type = CPP_EOF;
  clauses.محفوظ_ڌڪو (eof_token);
  clauses.محفوظ_ڌڪو (eof_token);

  بدل (context)
    {
    حالة pragma_external:
      إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, خطأ, سچ,
					 خطأ, عدم, &clauses);
	  restore_extension_diagnostics (ext);
	}
      وإلا
	c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, خطأ, سچ,
				       خطأ, عدم, &clauses);
      اكسر;
    حالة pragma_struct:
    حالة pragma_param:
    حالة pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_اشارو (قسم));
      اكسر;
    حالة pragma_compound:
      منطقي have_std_attrs;
      وڻ std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_خاصيتون (parser, 1);
      إذا (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      وإلا
	std_attrs = NULL_وڻ;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  صحيح ext = disable_extension_diagnostics ();
	  افعل
	    c_parser_consume_token (parser);
	  طالما (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  إذا (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser)
	      || c_parser_nth_token_starts_std_خاصيتون (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ,
					     سچ, خطأ, عدم, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      اكسر;
	    }
	  restore_extension_diagnostics (ext);
	}
      وإلا إذا (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, سچ, سچ, سچ, سچ, سچ,
					 خطأ, عدم, &clauses, have_std_attrs,
					 std_attrs);
	  اكسر;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_اشارو (قسم));
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

ساكن وڻ
c_parser_omp_context_selector (c_parser *parser, تعداد omp_tss_ڪوڊ سيٽ,
			       وڻ parms)
{
  وڻ ret = NULL_وڻ;
  افعل
    {
      وڻ selector;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
	  || c_parser_ايندڙ_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->قدر;
      وإلا
	{
	  c_parser_error (parser, "expected trait selector name");
	  أرجع error_mark_ڳنڍ;
	}
      تعداد omp_ts_ڪوڊ sel
	= omp_lookup_ts_ڪوڊ (سيٽ, IDENTIFIER_اشارو (selector));

      إذا (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_اشارو (selector),  omp_tss_map[سيٽ]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_وڻ, NULL_وڻ, ret);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_متوازن_token_sequence (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      استمر;
	    }
	  وإلا
	    اكسر;
	}

      c_parser_consume_token (parser);

      وڻ properties = NULL_وڻ;
      وڻ scoreval = NULL_وڻ;
      تعداد omp_tp_type property_قسم = omp_ts_map[sel].tp_type;
      منطقي allow_score = omp_ts_map[sel].allow_score;
      وڻ t;

      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
	{
	  إذا (property_قسم == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_اشارو (selector));
	      أرجع error_mark_ڳنڍ;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_اشارو (token->قدر), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      وڻ score = c_parser_اظهار_no_commas (parser, عدم).قدر;
	      parens2.skip_until_مليو_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      إذا (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[سيٽ]);
	      وإلا إذا (score != error_mark_ڳنڍ)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, خطأ, عدم);
		  إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (score))
		      || وڻ_ڪوڊ (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  وإلا إذا (وڻ_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  وإلا
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  بدل (property_قسم)
	    {
	    حالة OMP_TRAIT_PROPERTY_ID:
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
		  || c_parser_ايندڙ_token_is (parser, CPP_NAME))
		{
		  وڻ prop = c_parser_peek_token (parser)->قدر;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_وڻ,
						    properties);
		}
	      وإلا
		{
		  c_parser_error (parser, "expected identifier");
		  أرجع error_mark_ڳنڍ;
		}
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_NAME_LIST:
	      افعل
		{
		  وڻ prop = OMP_TP_NAMELIST_ڳنڍ;
		  وڻ قدر = NULL_وڻ;
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
		      || c_parser_ايندڙ_token_is (parser, CPP_NAME))
		    {
		      قدر = c_parser_peek_token (parser)->قدر;
		      c_parser_consume_token (parser);
		    }
		  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_STRING))
		    قدر = c_parser_string_literal (parser, خطأ,
						     خطأ).قدر;
		  وإلا
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      أرجع error_mark_ڳنڍ;
		    }

		  properties = make_trait_property (prop, قدر, properties);

		  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  وإلا
		    اكسر;
		}
	      طالما (1);
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_DEV_انگ_اظهار:
	    حالة OMP_TRAIT_PROPERTY_BOOL_اظهار:
	      {
		c_اظهار texpr = c_parser_اظهار_no_commas (parser, عدم);
		texpr = convert_lvalue_منزل_rvalue (token->location, texpr,
						  سچ, سچ);
		t = texpr.قدر;
	      }
	      إذا (t == error_mark_ڳنڍ)
		أرجع error_mark_ڳنڍ;
	      mark_exp_read (t);
	      إذا (property_قسم == OMP_TRAIT_PROPERTY_BOOL_اظهار)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_ڳنڍ);
		  إذا (t == error_mark_ڳنڍ)
		    أرجع error_mark_ڳنڍ;
		}
	      وإلا إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  أرجع error_mark_ڳنڍ;
		}
	      t = c_fully_fold (t, خطأ, عدم);
	      properties = make_trait_property (NULL_وڻ, t, properties);
	      اكسر;
	    حالة OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      إذا (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  إذا (parms == NULL_وڻ)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      أرجع error_mark_ڳنڍ;
		    }
		  وڻ c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_نقاب,
						"simd", سچ, 2);
		  c = c_omp_declare_simd_clauses_منزل_numbers (parms
							     == error_mark_ڳنڍ
							     ? NULL_وڻ : parms,
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
		  أرجع error_mark_ڳنڍ;
		}
	      وإلا
		gcc_unreachable ();
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }

	  parens.skip_until_مليو_close (parser);
	  properties = nreverse (properties);
	}
      وإلا إذا (property_قسم != OMP_TRAIT_PROPERTY_NONE
	       && property_قسم != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_قسم != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  أرجع error_mark_ڳنڍ;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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

ساكن وڻ
c_parser_omp_context_selector_specification (c_parser *parser, وڻ parms)
{
  وڻ ret = NULL_وڻ;
  افعل
    {
      ثابت حرف *setp = "";
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      تعداد omp_tss_ڪوڊ سيٽ = omp_lookup_tss_ڪوڊ (setp);

      إذا (سيٽ == OMP_TRAIT_سيٽ_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  أرجع error_mark_ڳنڍ;
	}

      c_parser_consume_token (parser);

      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	أرجع error_mark_ڳنڍ;

      matching_braces braces;
      إذا (!braces.require_open (parser))
	أرجع error_mark_ڳنڍ;

      وڻ selectors = c_parser_omp_context_selector (parser, سيٽ, parms);
      إذا (selectors == error_mark_ڳنڍ)
	{
	  c_parser_skip_منزل_closing_brace (parser);
	  ret = error_mark_ڳنڍ;
	}
      وإلا إذا (ret != error_mark_ڳنڍ)
	ret = make_trait_سيٽ_selector (سيٽ, selectors, ret);

      braces.require_close (parser);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      وإلا
	اكسر;
    }
  طالما (1);

  إذا (ret == error_mark_ڳنڍ)
    أرجع ret;
  أرجع nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

ساكن فراغ
c_پڄاڻي_omp_declare_variant (c_parser *parser, وڻ fndecl, وڻ parms)
{
  matching_parens parens;
  إذا (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع;
    }

  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      اذهب fail;
    }

  c_token *token = c_parser_peek_token (parser);
  وڻ variant = lookup_name (token->قدر);

  إذا (variant == NULL_وڻ)
    {
      undeclared_variable (token->location, token->قدر);
      variant = error_mark_ڳنڍ;
    }
  وإلا إذا (وڻ_ڪوڊ (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_ڳنڍ;
    }
  وإلا إذا (fndecl_built_اندريون_p (variant)
	   && (لڙي_ڀيٽ (IDENTIFIER_اشارو (DECL_NAME (variant)),
			"__builtin_", لڙي_ڊيگهه ("__builtin_")) == 0
	       || لڙي_ڀيٽ (IDENTIFIER_اشارو (DECL_NAME (variant)),
			   "__sync_", لڙي_ڊيگهه ("__sync_")) == 0
	       || لڙي_ڀيٽ (IDENTIFIER_اشارو (DECL_NAME (variant)),
			   "__atomic_", لڙي_ڊيگهه ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_ڳنڍ;
    }
  وإلا إذا (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_ڳنڍ;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  وڻ append_دليلون_وڻ = NULL_وڻ;
  وڻ append_دليلون_آخري;
  vec<وڻ> adjust_دليلون_list = vNULL;
  منطقي has_ميلاپ = خطأ, has_adjust_دليلون = خطأ;
  location_t adjust_دليلون_loc = UNKNOWN_LOCATION;
  location_t append_دليلون_loc = UNKNOWN_LOCATION;
  location_t ميلاپ_loc = UNKNOWN_LOCATION;
  وڻ need_device_ptr_list = NULL_وڻ;
  وڻ ctx = error_mark_ڳنڍ;

  افعل
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ثابت حرف *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

      تعداد clause
      {
	ميلاپ,
	adjust_دليلون,
	append_دليلون
      } ccode;

      إذا (strcmp (clause, "match") == 0)
	{
	  ccode = ميلاپ;
	  ميلاپ_loc = loc;
	}
      وإلا إذا (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_دليلون;
	  adjust_دليلون_loc = loc;
	}
      وإلا إذا (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_دليلون;
	  append_دليلون_loc = loc;
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

      إذا (parms == NULL_وڻ)
	parms = error_mark_ڳنڍ;

      إذا (ccode == ميلاپ)
	{
	  إذا (has_ميلاپ)
	    error_at (ميلاپ_loc, "too many %<match%> clauses");
	  has_ميلاپ = سچ;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  إذا (ctx == error_mark_ڳنڍ)
	    اذهب fail;
	  ctx = omp_check_context_selector (ميلاپ_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  إذا (ctx != error_mark_ڳنڍ
	      && !vec_محفوظ_is_خالي_جايون (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->آخري ();
	      وڻ outer_ctx = a.selector;
	      ctx = omp_ملايو_context_selectors (ميلاپ_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      وإلا إذا (ccode == adjust_دليلون)
	{
	  has_adjust_دليلون = سچ;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ثابت حرف *p
		= IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	      إذا (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  وڻ list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_وڻ);

		  وڻ arg;
		  إذا (variant != error_mark_ڳنڍ)
		    لكل (وڻ c = list; c != NULL_وڻ; c = وڻ_CHAIN (c))
		      {
			وڻ decl = وڻ_PURPOSE (c);
			location_t arg_loc = اظهار_LOCATION (وڻ_قدر (c));
			صحيح idx;
			لكل (arg = parms, idx = 0; arg != عدم;
			     arg = وڻ_CHAIN (arg), idx++)
			  إذا (arg == decl)
			    اكسر;
			إذا (arg == NULL_وڻ)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    اذهب fail;
			  }
			إذا (adjust_دليلون_list.شامل_آهي (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    اذهب fail;
			  }
			إذا (strcmp (p, "need_device_ptr") == 0
			    && وڻ_ڪوڊ (وڻ_TYPE (arg)) != اشارو_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    اذهب fail;
			  }
			adjust_دليلون_list.محفوظ_ڌڪو (arg);
			إذا (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_وڻ_list (
				NULL_وڻ,
				build_int_cst (
				  integer_type_ڳنڍ,
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
      وإلا إذا (ccode == append_دليلون)
	{
	  إذا (append_دليلون_وڻ)
	    {
	      error_at (append_دليلون_loc, "too many %qs clauses", "append_args");
	      append_دليلون_وڻ = NULL_وڻ;
	    }
	  افعل
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_اشارو (
			       c_parser_peek_token (parser)->قدر)))
		{
		  error_at (loc, "expected %<interop%>");
		  اذهب fail;
		}
	      c_parser_consume_token (parser);

	      إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		اذهب fail;
	      منطقي هدف = خطأ;
	      منطقي targetsync = خطأ;
	      وڻ prefer_type_وڻ = NULL_وڻ;
	      إذا (!c_parser_omp_clause_init_modifiers (parser, &هدف,
						       &targetsync,
						       &prefer_type_وڻ)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		اذهب fail;
	      إذا (!هدف && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      وڻ t = build_وڻ_list (هدف ? boolean_true_ڳنڍ
					       : boolean_false_ڳنڍ,
					targetsync ? boolean_true_ڳنڍ
						   : boolean_false_ڳنڍ);
	      t = build1_loc (loc, NOP_اظهار, void_type_ڳنڍ, t);
	      t = build_وڻ_list (t, prefer_type_وڻ);
	      إذا (append_دليلون_وڻ)
		{
		  وڻ_CHAIN (append_دليلون_آخري) = t;
		  append_دليلون_آخري = t;
		}
	      وإلا
		append_دليلون_وڻ = append_دليلون_آخري = t;
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
		اكسر;
	      إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		اذهب fail;
	    }
	  طالما (سچ);
	}

      parens.require_close (parser);
  } طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL));
  إذا (variant != error_mark_ڳنڍ && !has_ميلاپ)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_ڳنڍ;
    }
  c_parser_skip_منزل_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  إذا (variant == error_mark_ڳنڍ || ctx == error_mark_ڳنڍ)
    /* Previously diagnosed error.  */
    أرجع;

  إذا ((has_adjust_دليلون || append_دليلون_وڻ)
      && !omp_get_context_selector (ctx, OMP_TRAIT_سيٽ_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_دليلون ? adjust_دليلون_loc : append_دليلون_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_دليلون ? "adjust_args" : "append_args");
      أرجع;
    }

  إذا (!omp_get_context_selector (ctx, OMP_TRAIT_سيٽ_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      وڻ بنياد_type = وڻ_TYPE (fndecl);
      وڻ variant_type = وڻ_TYPE (variant);
      منطقي unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_وڻ
	   && !TYPE_NO_NAMED_دليلون_STDARG_P (variant_type));

      إذا (append_دليلون_وڻ
	  && TYPE_ARG_TYPES (بنياد_type) == NULL_وڻ
	  && !TYPE_NO_NAMED_دليلون_STDARG_P (بنياد_type))
	{
	  /* The base function is a pre-C23 unprototyped function.  Without
	     a prototype, we don't know the offset where the append_args go.
	     That offset needs to be stored with the append_args in the
	     variant function attributes, so we cannot presently handle
	     this case.  */
	  sorry_at (append_دليلون_loc,
		    "%<append_args%> with unprototyped base function "
		    "is not supported yet");
	  inform (DECL_ذريعو_LOCATION (fndecl),
		  "base function %qD declared here", fndecl);
	  أرجع;
	}
      وإلا إذا (append_دليلون_وڻ)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  صحيح nappend_دليلون = 0;
	  صحيح nbase_دليلون = 0;
	  لكل (وڻ t = TYPE_ARG_TYPES (بنياد_type);
	       t && وڻ_قدر (t) != void_type_ڳنڍ; t = وڻ_CHAIN (t))
	    nbase_دليلون++;
	  لكل (وڻ t = append_دليلون_وڻ; t; t = وڻ_CHAIN (t))
	    nappend_دليلون++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_دليلون_وڻ = build_وڻ_list (build_int_cst (integer_type_ڳنڍ,
							     nbase_دليلون),
					      append_دليلون_وڻ);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  إذا (!unprototyped_variant)
	    {
	      وڻ دليلون = TYPE_ARG_TYPES (variant_type);
	      لكل (صحيح i = 0; دليلون && i < nbase_دليلون;
		   i++, دليلون = وڻ_CHAIN (دليلون))
		;
	      لكل (صحيح i = 0; i < nappend_دليلون; i++, دليلون = وڻ_CHAIN (دليلون))
		إذا (!دليلون || !c_omp_interop_t_p (وڻ_قدر (دليلون)))
		  {
		    error_at (DECL_ذريعو_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_دليلون + i + 1, variant);
		    inform (append_دليلون_loc,
			    "%<append_args%> specified here");
		    أرجع;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  وڻ دليلون = TYPE_ARG_TYPES (بنياد_type);
	  وڻ newargs = NULL_وڻ;
	  وڻ lastarg = NULL_وڻ;
	  لكل (صحيح j = 0; j < nbase_دليلون; j++, دليلون = وڻ_CHAIN (دليلون))
	    {
	      وڻ t = وڻ_cons (وڻ_PURPOSE (دليلون),
				  وڻ_قدر (دليلون), NULL_وڻ);
	      إذا (lastarg)
		وڻ_CHAIN (lastarg) = t;
	      وإلا
		newargs = t;
	      lastarg = t;
	    }
	  وڻ type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? وڻ_TYPE (type) : اشارو_sized_int_ڳنڍ;
	  لكل (صحيح j = 0; j < nappend_دليلون; j++)
	    {
	      وڻ t = وڻ_cons (NULL_وڻ, type, NULL_وڻ);
	      إذا (lastarg)
		وڻ_CHAIN (lastarg) = t;
	      وإلا
		newargs = t;
	      lastarg = t;
	    }
	  وڻ_CHAIN (lastarg) = دليلون;

	  /* Temporarily stuff newargs into the original base_type.  */
	  وڻ saveargs = TYPE_ARG_TYPES (بنياد_type);
	  TYPE_ARG_TYPES (بنياد_type) = newargs;
	  منطقي fail = !comptypes (بنياد_type, variant_type);
	  TYPE_ARG_TYPES (بنياد_type) = saveargs;

	  إذا (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_ذريعو_LOCATION (variant),
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
	  إذا (!comptypes (بنياد_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_ذريعو_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      أرجع;
	    }
	  وإلا إذا (TYPE_ARG_TYPES (variant_type) == NULL_وڻ
		   && !TYPE_NO_NAMED_دليلون_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (بنياد_type) != NULL_وڻ)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (بنياد_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_استعمال_ٿيل (variant) = 1;
  وڻ construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_سيٽ_CONSTRUCT);
  omp_mark_declare_variant (ميلاپ_loc, variant, construct);
  إذا (omp_context_selector_matches (ctx, NULL_وڻ, خطأ))
    {
      وڻ attr = وڻ_cons (get_identifier ("omp declare variant base"),
			     build_وڻ_list (variant, ctx),
			     DECL_خاصيتون (fndecl));
      DECL_خاصيتون (fndecl) = attr;
    }

  إذا (need_device_ptr_list || append_دليلون_وڻ)
    {
      وڻ variant_decl = وڻ_strip_nop_conversions (variant);
      وڻ t = build_وڻ_list (need_device_ptr_list,
				NULL_وڻ /* need_device_addr */);
      وڻ_CHAIN (t) = append_دليلون_وڻ;
      DECL_خاصيتون (variant_decl)
	= وڻ_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_خاصيتون (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

ساكن فراغ
c_پڄاڻي_omp_declare_simd (c_parser *parser, وڻ fndecl, وڻ parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  إذا (clauses.exists () && clauses[0].type == CPP_EOF)
    أرجع;
  ثابت حرف *قسم = "simd";
  إذا (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    قسم = IDENTIFIER_اشارو (clauses[0].قدر);
  gcc_assert (strcmp (قسم, "simd") == 0 || strcmp (قسم, "variant") == 0);
  إذا (fndecl == NULL_وڻ || وڻ_ڪوڊ (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", قسم);
      clauses[0].type = CPP_EOF;
      أرجع;
    }
  إذا (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_ذريعو_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", قسم);
      clauses[0].type = CPP_EOF;
      أرجع;
    }
  إذا (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_ذريعو_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", قسم);
      أرجع;
    }

  إذا (parms == NULL_وڻ)
    parms = DECL_ARGUMENTS (fndecl);

  بنانشان صحيح ٽوڪن_avail = parser->ٽوڪن_avail;
  gcc_assert (parser->ٽوڪن == &parser->ٽوڪن_buf[0]);

  parser->ٽوڪن = clauses.پتو ();
  parser->ٽوڪن_avail = clauses.ڊيگهائي ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  طالما (parser->ٽوڪن_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      قسم = IDENTIFIER_اشارو (token->قدر);
      c_parser_consume_token (parser);
      parser->اندريون_pragma = سچ;

      إذا (strcmp (قسم, "simd") == 0)
	{
	  وڻ c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_نقاب,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_منزل_numbers (parms, c);
	  إذا (c != NULL_وڻ)
	    c = وڻ_cons (NULL_وڻ, c, NULL_وڻ);
	  c = build_وڻ_list (get_identifier ("omp declare simd"), c);
	  وڻ_CHAIN (c) = DECL_خاصيتون (fndecl);
	  DECL_خاصيتون (fndecl) = c;
	}
      وإلا
	{
	  gcc_assert (strcmp (قسم, "variant") == 0);
	  c_پڄاڻي_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->ٽوڪن = &parser->ٽوڪن_buf[0];
  parser->ٽوڪن_avail = ٽوڪن_avail;
  إذا (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#إذا !defined (NO_DOT_اندريون_LABEL)
#وصف_ڪريو JOIN_STR "."
#وإلاإذا !defined (NO_DOLLAR_اندريون_LABEL)
#وصف_ڪريو JOIN_STR "$"
#وإلا
#وصف_ڪريو JOIN_STR "_"
#جيڪڏهن_پورو

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
ساكن وڻ
omp_شروعات_variant_function (c_declarator *declarator, وڻ ctx)
{
  c_declarator *id = declarator;
  طالما (id->قسم != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  وڻ name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  أرجع name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
ساكن فراغ
omp_پڄاڻي_variant_function (وڻ decl, وڻ بنياد_name, وڻ ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  وڻ بنياد_decl = lookup_name (بنياد_name);
  إذا (بنياد_decl == error_mark_ڳنڍ)
    بنياد_decl = NULL_وڻ;
  إذا (!بنياد_decl)
    {
      error_at (DECL_ذريعو_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_اشارو (بنياد_name));
      أرجع;
    }

  إذا (!comptypes (وڻ_TYPE (decl), وڻ_TYPE (بنياد_decl)))
    {
      error_at (DECL_ذريعو_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", بنياد_decl);
      inform (DECL_ذريعو_LOCATION (بنياد_decl),
	      "%qE declared here", بنياد_decl);
      أرجع;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_ذريعو_LOCATION (decl),
				   بنياد_decl, ctx);
  وڻ construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_سيٽ_CONSTRUCT);
  omp_mark_declare_variant (DECL_ذريعو_LOCATION (decl), decl, construct);
  وڻ attrs = DECL_خاصيتون (بنياد_decl);
  وڻ ميلاپ_loc_ڳنڍ
    = maybe_wrap_with_location (integer_zero_ڳنڍ,
				DECL_ذريعو_LOCATION (بنياد_decl));
  وڻ loc_ڳنڍ = وڻ_cons (ميلاپ_loc_ڳنڍ, integer_zero_ڳنڍ,
			     build_وڻ_list (ميلاپ_loc_ڳنڍ,
					      integer_zero_ڳنڍ));
  attrs = وڻ_cons (get_identifier ("omp declare variant base"),
		     وڻ_cons (decl, ctx, loc_ڳنڍ), attrs);
  DECL_خاصيتون (بنياد_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  وڻ_عوامي (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

منطقي
c_maybe_parse_omp_decl (وڻ decl, وڻ d)
{
  gcc_assert (وڻ_ڪوڊ (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_ٽوڪن (d);
  c_token *پهريون = toks->پتو ();
  c_token *آخري = پهريون + toks->ڊيگهائي ();
  ثابت حرف *directive[3] = {};
  لكل (صحيح j = 0; j < 3; j++)
    {
      وڻ id = NULL_وڻ;
      إذا (پهريون + j == آخري)
	اكسر;
      إذا (پهريون[j].type == CPP_NAME)
	id = پهريون[j].قدر;
      وإلا إذا (پهريون[j].type == CPP_KEYWORD)
	id = ridpointers[(صحيح) پهريون[j].keyword];
      وإلا
	اكسر;
      directive[j] = IDENTIFIER_اشارو (id);
    }
  ثابت c_omp_directive *dir = عدم;
  إذا (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  إذا (dir == عدم)
    {
      error_at (پهريون->location,
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
    أرجع سچ;

  c_parser *parser = the_parser;
  بنانشان صحيح ٽوڪن_avail = parser->ٽوڪن_avail;
  gcc_assert (parser->ٽوڪن == &parser->ٽوڪن_buf[0]);
  toks = عدم;
  vec_محفوظ_reserve (toks, آخري - پهريون + 2, سچ);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_قسم = pragma_قسم (dir->id);
  tok.location = پهريون->location;
  toks->تيز_ڌڪو (tok);
  طالما (++پهريون < آخري)
    toks->تيز_ڌڪو (*پهريون);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = آخري[-1].location;
  toks->تيز_ڌڪو (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = آخري[-1].location;
  toks->تيز_ڌڪو (tok);
  parser->اندريون_omp_decl_attribute = decl;
  gcc_assert (!parser->اندريون_omp_attribute_pragma);
  parser->اندريون_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->اندريون_omp_attribute_pragma->token_vec = toks;
  parser->اندريون_omp_attribute_pragma->save_ٽوڪن = parser->ٽوڪن;
  parser->اندريون_omp_attribute_pragma->save_ٽوڪن_avail = ٽوڪن_avail;
  parser->ٽوڪن = toks->پتو ();
  parser->ٽوڪن_avail = toks->ڊيگهائي ();
  c_parser_pragma (parser, pragma_external, عدم, NULL_وڻ);
  parser->اندريون_omp_decl_attribute = NULL_وڻ;
  أرجع سچ;
}

/* OpenMP 4.0:
   # pragma omp declare target new-line
   declarations and definitions
   # pragma omp end declare target new-line

   OpenMP 4.5:
   # pragma omp declare target ( extended-list ) new-line

   # pragma omp declare target declare-target-clauses[seq] new-line  */

#وصف_ڪريو OMP_DECLARE_هدف_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_منزل)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ENTER)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LINK)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LOCAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اڻسڌو))

ساكن فراغ
c_parser_omp_declare_هدف (c_parser *parser)
{
  وڻ clauses = NULL_وڻ;
  صحيح device_type = 0;
  منطقي اڻسڌو = خطأ;
  منطقي only_device_type_or_اڻسڌو = سچ;
  إذا (flag_openmp)
    omp_requires_نقاب
      = (تعداد omp_requires) (omp_requires_نقاب | OMP_REQUIRES_هدف_استعمال_ٿيل);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
      || (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_هدف_CLAUSE_نقاب,
					"#pragma omp declare target");
  وإلا إذا (parser->اندريون_omp_decl_attribute
	   || c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_پڄاڻي_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_منزل_pragma_eol (parser);
    }
  وإلا
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      منطقي attr_syntax = parser->اندريون_omp_attribute_pragma != عدم;
      c_parser_skip_منزل_pragma_eol (parser);
      c_omp_declare_هدف_attr attr = { attr_syntax, -1, 0 };
      vec_محفوظ_ڌڪو (current_omp_declare_هدف_attribute, attr);
      أرجع;
    }
  لكل (وڻ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_قسم (c);
      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_اڻسڌو)
	اڻسڌو |= !integer_zerop (OMP_CLAUSE_اڻسڌو_اظهار (c));
    }
  لكل (وڻ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_اڻسڌو)
	استمر;
      وڻ t = OMP_CLAUSE_DECL (c), id;
      وڻ at1 = lookup_attribute ("omp declare target", DECL_خاصيتون (t));
      وڻ at2 = lookup_attribute ("omp declare target link",
				   DECL_خاصيتون (t));
      only_device_type_or_اڻسڌو = خطأ;
      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::مٽا_سٽا (at1, at2);
	}
      وإلا
	id = get_identifier ("omp declare target");
      إذا (at2)
	{
	  إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_منزل (c) ? "to" : "enter");
	  وإلا إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_LOCAL
		   || قدر_member (get_identifier ("local"), وڻ_قدر (at2)))
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
	  DECL_خاصيتون (t) = وڻ_cons (id, NULL_وڻ, DECL_خاصيتون (t));
	  إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_LOCAL)
	    وڻ_قدر (DECL_خاصيتون (t))
	      = وڻ_cons (NULL_وڻ, get_identifier ("local"),
			   وڻ_قدر (DECL_خاصيتون (t)));

	  إذا (وڻ_ڪوڊ (t) != FUNCTION_DECL && !is_global_var (t))
	    استمر;

	  symtab_ڳنڍ *ڳنڍ = symtab_ڳنڍ::get (t);
	  إذا (ڳنڍ != عدم)
	    {
	      ڳنڍ->offloadable = 1;
	      إذا (ENABLE_OFFLOADING)
		{
		  g->have_offload = سچ;
		  إذا (is_a <varpool_ڳنڍ *> (ڳنڍ)
		      && OMP_CLAUSE_ڪوڊ (c) != OMP_CLAUSE_LOCAL)
		    vec_محفوظ_ڌڪو (offload_vars, t);
		}
	    }
	}
      وإلا
	{
	  منطقي saw_local = قدر_member (get_identifier ("local"),
					 وڻ_قدر (at1));
	  إذا (saw_local && OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_منزل (c) ? "to" : "enter");
	      استمر;
	    }
	  وإلا إذا (!saw_local && OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      استمر;
	    }
	}
      إذا (وڻ_ڪوڊ (t) != FUNCTION_DECL)
	استمر;
      إذا ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  وڻ at3 = lookup_attribute ("omp declare target host",
				       DECL_خاصيتون (t));
	  إذا (at3 == NULL_وڻ)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_خاصيتون (t)
		= وڻ_cons (id, NULL_وڻ, DECL_خاصيتون (t));
	    }
	}
      إذا ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  وڻ at3 = lookup_attribute ("omp declare target nohost",
				       DECL_خاصيتون (t));
	  إذا (at3 == NULL_وڻ)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_خاصيتون (t)
		= وڻ_cons (id, NULL_وڻ, DECL_خاصيتون (t));
	    }
	}
      إذا (اڻسڌو)
	{
	  وڻ at4 = lookup_attribute ("omp declare target indirect",
				       DECL_خاصيتون (t));
	  إذا (at4 == NULL_وڻ)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_خاصيتون (t)
		= وڻ_cons (id, NULL_وڻ, DECL_خاصيتون (t));
	    }
	}
    }
  إذا ((device_type || اڻسڌو) && only_device_type_or_اڻسڌو)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  إذا (اڻسڌو && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "%<device_type%> clause must specify 'any' when used with "
	      "an %<indirect%> clause");
}

/* OpenMP 5.1
   #pragma omp begin assumes clauses[optseq] new-line

   #pragma omp begin declare target clauses[optseq] new-line

   #pragma omp begin declare variant match (context-selector) new-line  */

#وصف_ڪريو OMP_BEGIN_DECLARE_هدف_CLAUSE_نقاب			\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اڻسڌو))

ساكن فراغ
c_parser_omp_begin (c_parser *parser)
{
  ثابت حرف *p = "";
  c_parser_consume_pragma (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
  إذا (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقي attr_syntax = parser->اندريون_omp_attribute_pragma != عدم;
	  وڻ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_هدف_CLAUSE_نقاب,
					"#pragma omp begin declare target");
	  صحيح device_type = 0;
	  صحيح اڻسڌو = 0;
	  لكل (وڻ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_قسم (c);
	      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_اڻسڌو)
		اڻسڌو |= !integer_zerop (OMP_CLAUSE_اڻسڌو_اظهار (c));
	    }
	  c_omp_declare_هدف_attr attr = { attr_syntax, device_type,
					     اڻسڌو };
	  vec_محفوظ_ڌڪو (current_omp_declare_هدف_attribute, attr);
	}
      وإلا إذا (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ثابت حرف *clause = "";
	  matching_parens parens;
	  location_t ميلاپ_loc = c_parser_peek_token (parser)->location;
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	    {
	      وڻ id = c_parser_peek_token (parser)->قدر;
	      clause = IDENTIFIER_اشارو (id);
	    }
	  إذا (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_منزل_pragma_eol (parser);
	      أرجع;
	    }

	  c_parser_consume_token (parser);

	  إذا (!parens.require_open (parser))
	    {
	      c_parser_skip_منزل_pragma_eol (parser, خطأ);
	      أرجع;
	    }

	  وڻ ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_وڻ);
	  إذا (ctx != error_mark_ڳنڍ)
	    ctx = omp_check_context_selector (ميلاپ_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  إذا (ctx != error_mark_ڳنڍ
	      && !vec_محفوظ_is_خالي_جايون (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->آخري ();
	      وڻ outer_ctx = a.selector;
	      ctx = omp_ملايو_context_selectors (ميلاپ_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  إذا (ctx == error_mark_ڳنڍ
	      || !omp_context_selector_matches (ctx, NULL_وڻ, خطأ, سچ))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_منزل_pragma_eol (parser, خطأ);
	      c_parser_skip_منزل_pragma_omp_پڇاڙي_declare_variant (parser);
	      أرجع;
	    }
	  وإلا
	    {
	      منطقي attr_syntax = parser->اندريون_omp_attribute_pragma != عدم;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_محفوظ_ڌڪو (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_منزل_pragma_eol (parser);
	}
      وإلا
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
	}
    }
  وإلا إذا (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقي attr_syntax = parser->اندريون_omp_attribute_pragma != عدم;
      c_parser_omp_assumption_clauses (parser, خطأ);
      بنية c_omp_begin_assumes_معلومات a = { attr_syntax };
      vec_محفوظ_ڌڪو (current_omp_begin_assumes, a);
    }
  وإلا
    {
      c_parser_error (parser, "expected %<declare target%>, "
		      "%<declare variant%>, or %<assumes%>");
      c_parser_skip_منزل_pragma_eol (parser);
    }
}

/* OpenMP 4.0
   #pragma omp end declare target

   OpenMP 5.1
   #pragma omp end assumes
   #pragma omp end declare variant  */

ساكن فراغ
c_parser_omp_پڇاڙي (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ثابت حرف *p = "";
  c_parser_consume_pragma (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
  إذا (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  منطقي attr_syntax = parser->اندريون_omp_attribute_pragma != عدم;
	  c_parser_skip_منزل_pragma_eol (parser);
	  إذا (!vec_محفوظ_ڊيگهائي (current_omp_declare_هدف_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  وإلا
	    {
	      c_omp_declare_هدف_attr
		a = current_omp_declare_هدف_attribute->ڪڍو ();
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
	  منطقي attr_syntax = parser->اندريون_omp_attribute_pragma != عدم;
	  c_parser_skip_منزل_pragma_eol (parser);
	  إذا (!vec_محفوظ_ڊيگهائي (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  وإلا
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->ڪڍو ();
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
	  c_parser_skip_منزل_pragma_eol (parser);
	  أرجع;
	}
    }
  وإلا إذا (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      منطقي attr_syntax = parser->اندريون_omp_attribute_pragma != عدم;
      c_parser_skip_منزل_pragma_eol (parser);
      إذا (!vec_محفوظ_ڊيگهائي (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      وإلا
	{
	  c_omp_begin_assumes_معلومات
	    a = current_omp_begin_assumes->ڪڍو ();
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
      c_parser_skip_منزل_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

ساكن فراغ
c_parser_omp_declare_mapper (c_parser *parser, تعداد pragma_context context)
{
  وڻ type, mapper_name = NULL_وڻ, var = NULL_وڻ, stmt, stmtlist;
  وڻ maplist = NULL_وڻ, mapper_id, mapper_decl, t;
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
	  mapper_name = token->قدر;
	  c_parser_consume_token (parser);
	  اكسر;
	حالة CPP_KEYWORD:
	  إذا (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_وڻ;
	      c_parser_consume_token (parser);
	      اكسر;
	    }
	  /* Fallthrough.  */
	افتراضي:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
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
    إذا (type == error_mark_ڳنڍ)
      اذهب fail;
    إذا (!رڪارڊ_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_منزل_pragma_eol (parser, خطأ);
	أرجع;
      }
    لكل (وڻ t = DECL_INITIAL (mapper_decl); t; t = وڻ_CHAIN (t))
      إذا (comptypes (وڻ_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_اشارو (mapper_id)
		      + حجم ("omp declare mapper ") - 1,
		    type);
	  وڻ prevmapper = وڻ_قدر (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_ذريعو_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
	  أرجع;
	}
  }

  token = c_parser_peek_token (parser);
  إذا (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->قدر, type);
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

  ڌڪو_scope ();
  stmtlist = ڌڪو_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t هتي;
      pragma_omp_clause c_قسم;
      هتي = c_parser_peek_token (parser)->location;
      c_قسم = c_parser_omp_clause_name (parser);
      إذا (c_قسم != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (هتي, "unexpected clause");
	  اذهب fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, سچ);
    }

  إذا (maplist == NULL_وڻ)
    {
      error_at (داخلا_location, "missing %<map%> clause");
      اذهب fail;
    }
  وڻ list;
  لكل (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      وڻ dvar = OMP_CLAUSE_DECL (list);
      طالما (!DECL_P (dvar) && وڻ_عمليو_ڊيگهائي (dvar))
	dvar = وڻ_عمليو (dvar, 0);
      إذا (dvar == var)
	اكسر;
    }
  إذا (!list)
    error_at (داخلا_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_ڳنڍ (OMP_DECLARE_MAPPER);
  وڻ_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  جوڙيو_stmt (stmt);

  ڪڍو_stmt_list (stmtlist);
  ڪڍو_scope ();

  c_parser_skip_منزل_pragma_eol (parser);

  t = وڻ_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  أرجع;

 fail:
  c_parser_skip_منزل_pragma_eol (parser);
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
  بنانشان صحيح ٽوڪن_avail = 0, i;
  c_token *saved_ٽوڪن = عدم;
  vec<وڻ> types = vNULL;
  vec<c_token> clauses = vNULL;
  تعداد وڻ_ڪوڊ_2 reduc_ڪوڊ = ERROR_MARK;
  وڻ reduc_id = NULL_وڻ;
  وڻ type;
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
      reduc_ڪوڊ = PLUS_اظهار;
      اكسر;
    حالة CPP_MULT:
      reduc_ڪوڊ = MULT_اظهار;
      اكسر;
    حالة CPP_MINUS:
      reduc_ڪوڊ = MINUS_اظهار;
      اكسر;
    حالة CPP_AND:
      reduc_ڪوڊ = ٻٽو_انگ_AND_اظهار;
      اكسر;
    حالة CPP_XOR:
      reduc_ڪوڊ = ٻٽو_انگ_XOR_اظهار;
      اكسر;
    حالة CPP_OR:
      reduc_ڪوڊ = ٻٽو_انگ_IOR_اظهار;
      اكسر;
    حالة CPP_AND_AND:
      reduc_ڪوڊ = TRUTH_ANDIF_اظهار;
      اكسر;
    حالة CPP_OR_OR:
      reduc_ڪوڊ = TRUTH_ORIF_اظهار;
      اكسر;
    حالة CPP_NAME:
      ثابت حرف *p;
      p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "min") == 0)
	{
	  reduc_ڪوڊ = MIN_اظهار;
	  اكسر;
	}
      إذا (strcmp (p, "max") == 0)
	{
	  reduc_ڪوڊ = MAX_اظهار;
	  اكسر;
	}
      reduc_id = c_parser_peek_token (parser)->قدر;
      اكسر;
    افتراضي:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      اذهب fail;
    }

  وڻ orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_ڪوڊ, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    اذهب fail;

  طالما (سچ)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      بنية c_type_name *ctype = c_parser_type_name (parser);
      إذا (ctype != عدم)
	{
	  type = groktypename (ctype, عدم, عدم);
	  إذا (type == error_mark_ڳنڍ)
	    ;
	  وإلا إذا ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || وڻ_ڪوڊ (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_وڻ)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  وإلا إذا (وڻ_ڪوڊ (type) == FUNCTION_TYPE
		   || وڻ_ڪوڊ (type) == ARRAY_TYPE)
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
	      وڻ t;
	      لكل (t = DECL_INITIAL (reduc_decl); t; t = وڻ_CHAIN (t))
		إذا (comptypes (وڻ_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_اشارو (reduc_id)
				   + حجم ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_ذريعو_LOCATION (وڻ_VEC_ELT (وڻ_قدر (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    اكسر;
		  }
	      إذا (t == NULL_وڻ)
		types.محفوظ_ڌڪو (type);
	    }
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    اكسر;
	}
      وإلا
	اكسر;
    }

  إذا (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_خالي_جايون ())
    {
     fail:
      clauses.release ();
      types.release ();
      طالما (سچ)
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    اكسر;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_منزل_pragma_eol (parser);
      أرجع;
    }

  إذا (types.ڊيگهائي () > 1)
    {
      طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  إذا (token->type == CPP_EOF)
	    اذهب fail;
	  clauses.محفوظ_ڌڪو (*token);
	  c_parser_consume_token (parser);
	}
      clauses.محفوظ_ڌڪو (*c_parser_peek_token (parser));
      c_parser_skip_منزل_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, حجم (eof_token));
      eof_token.type = CPP_EOF;
      clauses.محفوظ_ڌڪو (eof_token);
      clauses.محفوظ_ڌڪو (eof_token);
    }

  صحيح errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_ٽوڪن = parser->ٽوڪن;
      ٽوڪن_avail = parser->ٽوڪن_avail;
      إذا (!clauses.is_خالي_جايون ())
	{
	  parser->ٽوڪن = clauses.پتو ();
	  parser->ٽوڪن_avail = clauses.ڊيگهائي ();
	  parser->اندريون_pragma = سچ;
	}

      منطقي nested = current_function_decl != NULL_وڻ;
      إذا (nested)
	c_ڌڪو_function_context ();
      وڻ fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, سچ);
      ڌڪو_scope ();
      وڻ stmt = ڌڪو_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      وڻ omp_ٻاهريون = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_ٻاهريون) = 1;
      DECL_CONTEXT (omp_ٻاهريون) = fndecl;
      pushdecl (omp_ٻاهريون);
      وڻ omp_اندريون = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_اندريون) = 1;
      DECL_CONTEXT (omp_اندريون) = fndecl;
      pushdecl (omp_اندريون);
      بنية c_اظهار combiner = c_parser_اظهار (parser);
      بنية c_اظهار initializer;
      وڻ omp_priv = NULL_وڻ, omp_orig = NULL_وڻ;
      منطقي bad = خطأ;
      initializer.سيٽ_error ();
      إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = سچ;
      وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      إذا (!bad
	  && (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_اشارو
				(c_parser_peek_token (parser)->قدر),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  ڪڍو_scope ();
	  ڌڪو_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_ڳنڍ;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = سچ;
	  وإلا إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = سچ;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارو
				(c_parser_peek_token (parser)->قدر),
			   "omp_priv") != 0)
	    {
	      إذا (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = سچ;
		}
	      وإلا
		initializer = c_parser_postfix_اظهار (parser);
	      إذا (initializer.قدر
		  && وڻ_ڪوڊ (initializer.قدر) == CALL_اظهار)
		{
		  صحيح j;
		  وڻ c = initializer.قدر;
		  لكل (j = 0; j < call_اظهار_nargs (c); j++)
		    {
		      وڻ a = CALL_اظهار_ARG (c, j);
		      STRIP_NOPS (a);
		      إذا (وڻ_ڪوڊ (a) == ADDR_اظهار
			  && وڻ_عمليو (a, 0) == omp_priv)
			اكسر;
		    }
		  إذا (j == call_اظهار_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      إذا (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = سچ;
	      وإلا
		{
		  وڻ st = ڌڪو_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (سٽ_جدول, loc);
		  شروعات_init (omp_priv, NULL_وڻ, خطأ, خطأ, &richloc);
		  بنية c_اظهار init = c_parser_initializer (parser, omp_priv);
		  پڄاڻي_init ();
		  پڄاڻي_decl (omp_priv, loc, init.قدر,
		      	       init.original_type, NULL_وڻ);
		  ڪڍو_stmt_list (st);
		}
	    }
	  إذا (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = سچ;
	}

      إذا (!bad)
	{
	  c_parser_skip_منزل_pragma_eol (parser);

	  وڻ t = وڻ_cons (type, make_وڻ_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_ذريعو_LOCATION (omp_ٻاهريون) = rloc;
	  وڻ_VEC_ELT (وڻ_قدر (t), 0) = omp_ٻاهريون;
	  وڻ_VEC_ELT (وڻ_قدر (t), 1) = omp_اندريون;
	  وڻ_VEC_ELT (وڻ_قدر (t), 2) = combiner.قدر;
	  walk_وڻ (&combiner.قدر, c_check_omp_declare_reduction_r,
		     &وڻ_VEC_ELT (وڻ_قدر (t), 0), عدم);
	  إذا (omp_priv)
	    {
	      DECL_ذريعو_LOCATION (omp_priv) = rloc;
	      وڻ_VEC_ELT (وڻ_قدر (t), 3) = omp_priv;
	      وڻ_VEC_ELT (وڻ_قدر (t), 4) = omp_orig;
	      وڻ_VEC_ELT (وڻ_قدر (t), 5) = initializer.قدر;
	      walk_وڻ (&initializer.قدر, c_check_omp_declare_reduction_r,
			 &وڻ_VEC_ELT (وڻ_قدر (t), 3), عدم);
	      walk_وڻ (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &وڻ_VEC_ELT (وڻ_قدر (t), 3), عدم);
	    }
	}

      ڪڍو_stmt_list (stmt);
      ڪڍو_scope ();
      إذا (cfun->language != عدم)
	{
	  ggc_free (cfun->language);
	  cfun->language = عدم;
	}
      سيٽ_cfun (عدم);
      current_function_decl = NULL_وڻ;
      إذا (nested)
	c_ڪڍو_function_context ();

      إذا (!clauses.is_خالي_جايون ())
	{
	  parser->ٽوڪن = saved_ٽوڪن;
	  parser->ٽوڪن_avail = ٽوڪن_avail;
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
  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  أرجع سچ;
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
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
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
	  أرجع سچ;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_منزل_pragma_eol (parser);
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
  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  ثابت حرف *p
	    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  تعداد omp_requires this_req = (تعداد omp_requires) 0;

	  إذا (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_پتو;
	  وإلا إذا (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_يادگيري;
	  وإلا إذا (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  وإلا إذا (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  وإلا إذا (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_ابتو_OFFLOAD;
	  وإلا إذا (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      إذا (parens.require_open (parser))
		{
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		    {
		      وڻ v = c_parser_peek_token (parser)->قدر;
		      p = IDENTIFIER_اشارو (v);

		      إذا (!strcmp (p, "seq_cst"))
			this_req
			  = (تعداد omp_requires) OMP_يادگيري_ترتيب_SEQ_CST;
		      وإلا إذا (!strcmp (p, "relaxed"))
			this_req
			  = (تعداد omp_requires) OMP_يادگيري_ترتيب_RELAXED;
		      وإلا إذا (!strcmp (p, "release"))
			this_req
			  = (تعداد omp_requires) OMP_يادگيري_ترتيب_RELEASE;
		      وإلا إذا (!strcmp (p, "acq_rel"))
			this_req
			  = (تعداد omp_requires) OMP_يادگيري_ترتيب_ACQ_REL;
		      وإلا إذا (!strcmp (p, "acquire"))
			this_req
			  = (تعداد omp_requires) OMP_يادگيري_ترتيب_ACQUIRE;
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

		  parens.skip_until_مليو_close (parser);
		  إذا (this_req == 0)
		    {
		      c_parser_skip_منزل_pragma_eol (parser, خطأ);
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
	      c_parser_skip_منزل_pragma_eol (parser, خطأ);
	      أرجع;
	    }
	  إذا (p)
	    c_parser_consume_token (parser);
	  إذا (this_req)
	    {
	      إذا ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتيب) != 0)
		{
		  إذا ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  إذا (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_نقاب & OMP_REQUIRES_هدف_استعمال_ٿيل) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      وإلا إذا ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتيب) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (تعداد omp_requires) 0;
		}
	      وإلا إذا ((omp_requires_نقاب
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتيب) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (تعداد omp_requires)
		       (omp_requires_نقاب
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتيب);
		}
	      وإلا إذا ((omp_requires_نقاب
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ترتيب_استعمال_ٿيل) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (تعداد omp_requires) (new_req | this_req);
	      omp_requires_نقاب
		= (تعداد omp_requires) (omp_requires_نقاب | this_req);
	      استمر;
	    }
	}
      اكسر;
    }
  c_parser_skip_منزل_pragma_eol (parser);

  إذا (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

ساكن وڻ
c_پڄاڻي_taskloop_clauses (وڻ clauses)
{
  وڻ *pc = &clauses;
  لكل (وڻ c = clauses; c; c = *pc)
    {
      منطقي remove = خطأ;
      إذا (OMP_CLAUSE_ڪوڊ (c) == OMP_CLAUSE_REDUCTION)
	{
	  وڻ type = strip_array_types (وڻ_TYPE (OMP_CLAUSE_DECL (c)));
	  إذا (integer_zerop (TYPE_سائيز_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = سچ;
	    }
	  وإلا إذا (وڻ_ڪوڊ (TYPE_سائيز_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = سچ;
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

#وصف_ڪريو OMP_TASKLOOP_CLAUSE_نقاب				\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ذاتي)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_GRAINSIZE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_انگ_TASKS)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_NOGROUP)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ترجيح)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اندريون_REDUCTION))

ساكن وڻ
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       حرف *p_name, omp_clause_نقاب نقاب, وڻ *cclauses,
		       منطقي *if_p)
{
  وڻ clauses, بلاڪ, ret;

  strcat (p_name, " taskloop");
  نقاب |= OMP_TASKLOOP_CLAUSE_نقاب;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  إذا ((نقاب & (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_انگ_ڌاڳا)) != 0)
    نقاب &= ~(OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_اندريون_REDUCTION);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);

      إذا (strcmp (p, "simd") == 0)
	{
	  وڻ cclauses_buf[C_OMP_CLAUSE_ورهايو_ڳڻپ];
	  إذا (cclauses == عدم)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  إذا (!flag_openmp)  /* flag_openmp_simd  */
	    أرجع c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses,
				      if_p);
	  بلاڪ = c_begin_compound_stmt (سچ);
	  ret = c_parser_omp_simd (loc, parser, p_name, نقاب, cclauses, if_p);
	  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
	  إذا (ret == عدم)
	    أرجع ret;
	  ret = make_ڳنڍ (OMP_TASKLOOP);
	  وڻ_TYPE (ret) = void_type_ڳنڍ;
	  OMP_FOR_BODY (ret) = بلاڪ;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_ورهايو_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_پڄاڻي_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  سيٽ_اظهار_LOCATION (ret, loc);
	  جوڙيو_stmt (ret);
	  أرجع ret;
	}
    }
  إذا (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_منزل_pragma_eol (parser, خطأ);
      أرجع NULL_وڻ;
    }

  clauses = c_parser_omp_all_clauses (parser, نقاب, p_name, cclauses == عدم);
  إذا (cclauses)
    {
      omp_ورهايو_clauses (loc, OMP_TASKLOOP, نقاب, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ورهايو_TASKLOOP];
    }

  clauses = c_پڄاڻي_taskloop_clauses (clauses);
  بلاڪ = c_begin_compound_stmt (سچ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, عدم, if_p);
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

  أرجع ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
ساكن وڻ
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  وڻ sizes = NULL_وڻ;

  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  إذا (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_اشارو (tok->قدر)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      أرجع error_mark_ڳنڍ;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  إذا (!parens.require_open (parser))
    أرجع error_mark_ڳنڍ;

  vec<وڻ, va_gc> *sizes_vec
    = c_parser_اظهار_list (parser, سچ, سچ, عدم, عدم, عدم, عدم);
  sizes = build_وڻ_list_vec (sizes_vec);
  release_وڻ_ويڪٽر (sizes_vec);

  لكل (وڻ s = sizes; s; s = وڻ_CHAIN (s))
    {
      وڻ اظهار = وڻ_قدر (s);
      إذا (اظهار == error_mark_ڳنڍ)
	{
	  parens.skip_until_مليو_close (parser);
	  أرجع error_mark_ڳنڍ;
	}

      HOST_WIDE_INT n;
      إذا (!INTEGRAL_TYPE_P (وڻ_TYPE (اظهار))
	  || !وڻ_سمائي_shwi_p (اظهار)
	  || (n = وڻ_منزل_shwi (اظهار)) <= 0
	  || (صحيح) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  وڻ_قدر (s) = integer_one_ڳنڍ;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  وڻ c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  أرجع c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

ساكن وڻ
c_parser_omp_tile (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_منزل_pragma_eol (parser);

  إذا (!clauses || clauses == error_mark_ڳنڍ)
    أرجع error_mark_ڳنڍ;

  وڻ بلاڪ = c_begin_compound_stmt (سچ);
  وڻ ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    عدم, if_p);
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

  أرجع ret;
}

#وصف_ڪريو OMP_UNROLL_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_ڀريل))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

ساكن وڻ
c_parser_omp_unroll (location_t loc, c_parser *parser, منطقي *if_p)
{
  وڻ clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_نقاب,
					   "#pragma omp unroll", سچ);

  وڻ بلاڪ = c_begin_compound_stmt (سچ);
  وڻ ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    عدم, if_p);
  بلاڪ = c_پڇاڙي_compound_stmt (loc, بلاڪ, سچ);
  جوڙيو_stmt (بلاڪ);

  أرجع ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

ساكن فراغ
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_منزل_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

ساكن منطقي
c_parser_omp_error (c_parser *parser, تعداد pragma_context context)
{
  صحيح at_compilation = -1;
  صحيح severity_fatal = -1;
  وڻ پيغام = NULL_وڻ;
  منطقي bad = خطأ;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
	اكسر;

      ثابت حرف *p
	= IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      location_t cloc = c_parser_peek_token (parser)->location;
      ساكن ثابت حرف *دليلون[] = {
	"execution", "compilation", "warning", "fatal"
      };
      صحيح *v = عدم;
      صحيح idx = 0, n = -1;
      وڻ m = NULL_وڻ;

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
	  c_parser_skip_منزل_pragma_eol (parser, خطأ);
	  أرجع خطأ;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      إذا (parens.require_open (parser))
	{
	  إذا (v == عدم)
	    {
	      location_t اظهار_loc = c_parser_peek_token (parser)->location;
	      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	      اظهار = convert_lvalue_منزل_rvalue (اظهار_loc, اظهار, سچ, سچ);
	      m = convert (const_string_type_ڳنڍ, اظهار.قدر);
	      m = c_fully_fold (m, خطأ, عدم);
	    }
	  وإلا
	    {
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		{
		  وڻ val = c_parser_peek_token (parser)->قدر;
		  ثابت حرف *q = IDENTIFIER_اشارو (val);

		  إذا (!strcmp (q, دليلون[idx]))
		    n = 0;
		  وإلا إذا (!strcmp (q, دليلون[idx + 1]))
		    n = 1;
		}
	      إذا (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", دليلون[idx], دليلون[idx + 1]);
		  bad = سچ;
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

	  parens.skip_until_مليو_close (parser);

	  إذا (v == عدم)
	    {
	      إذا (پيغام)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = سچ;
		}
	      وإلا
		پيغام = m;
	    }
	  وإلا إذا (n != -1)
	    {
	      إذا (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = سچ;
		}
	      وإلا
		*v = n;
	    }
	}
      وإلا
	bad = سچ;
    }
  c_parser_skip_منزل_pragma_eol (parser);
  إذا (bad)
    أرجع سچ;

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
	  أرجع سچ;
	}
      إذا (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->اندريون_intervening_ڪوڊ)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = سچ;
	  أرجع سچ;
	}
      وڻ fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_اندريون_GOMP_ERROR
						: BUILT_اندريون_GOMP_WARNING);
      إذا (!پيغام)
	پيغام = build_zero_cst (const_string_type_ڳنڍ);
      وڻ stmt = build_call_اظهار_loc (loc, fndecl, 2, پيغام,
				       build_all_ones_cst (سائيز_type_ڳنڍ));
      جوڙيو_stmt (stmt);
      أرجع سچ;
    }
  ثابت حرف *نياپو = عدم;
  إذا (پيغام)
    {
      نياپو = c_getstr (پيغام);
      إذا (نياپو == عدم)
	نياپو = _("<message unknown at compile time>");
    }
  ثابت تعداد diagnostics::قسم diag_قسم = (severity_fatal
					    ? diagnostics::قسم::error
					    : diagnostics::قسم::warning);
  إذا (نياپو)
    emit_diagnostic (diag_قسم, loc, 0,
		     "%<pragma omp error%> encountered: %s", نياپو);
  وإلا
    emit_diagnostic (diag_قسم, loc, 0,
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
  bitmap_سر absent_سر, شامل_آهي_سر;

  bitmap_obstack_initialize (عدم);
  bitmap_initialize (&absent_سر, &bitmap_default_obstack);
  bitmap_initialize (&شامل_آهي_سر, &bitmap_default_obstack);

  إذا (c_parser_ايندڙ_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
	اكسر;

      ثابت حرف *p
	= IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      location_t cloc = c_parser_peek_token (parser)->location;

      إذا (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = سچ;
	}
      وإلا إذا (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = سچ;
	}
      وإلا إذا (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = سچ;
	}
      وإلا إذا (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  إذا (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = سچ;
	}
      وإلا إذا (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  إذا (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_اظهار اظهار = c_parser_اظهار_no_commas (parser, عدم);
	      وڻ t = convert_lvalue_منزل_rvalue (eloc, اظهار, سچ, سچ).قدر;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, خطأ, عدم);
	      إذا (is_assume && t != error_mark_ڳنڍ)
		{
		  وڻ fn = build_call_اظهار_اندروني_loc (eloc, IFN_ASSUME,
							  void_type_ڳنڍ, 1,
							  t);
		  جوڙيو_stmt (fn);
		}
	      parens.skip_until_مليو_close (parser);
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
		      وڻ id;
		      إذا (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->قدر;
		      وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  تعداد rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      وإلا
			اكسر;
		      directive[i] = IDENTIFIER_اشارو (id);
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
			  && dir->id != PRAGMA_OMP_پڇاڙي
			  && (dir->قسم == C_OMP_DIR_DECLARATIVE
			      || dir->قسم == C_OMP_DIR_INFORMATIONAL
			      || dir->قسم == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      وإلا إذا (dir == عدم
			       || dir->id == PRAGMA_OMP_پڇاڙي
			       || (!dir->ٻيو && directive[1])
			       || (!dir->ٽيون && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      وإلا
			{
			  صحيح id = dir - c_omp_directives;
			  إذا (bitmap_ٻٽو_انگ_p (p[0] == 'a' ? &شامل_آهي_سر
							: &absent_سر, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  وإلا إذا (!bitmap_سيٽ_ٻٽو_انگ (p[0] == 'a'
						    ? &absent_سر
						    : &شامل_آهي_سر, id))
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
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  وإلا
		    اكسر;
		}
	      طالما (1);
	      parens.skip_until_مليو_close (parser);
	    }
	}
      وإلا إذا (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
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
  c_parser_skip_منزل_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

ساكن فراغ
c_parser_omp_assume (c_parser *parser, منطقي *if_p)
{
  c_parser_omp_assumption_clauses (parser, سچ);
  جوڙيو_stmt (c_parser_omp_structured_بلاڪ (parser, if_p));
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
			    vec<c_token> &ٽوڪن,
			    vec<وڻ> &labels)
{
  صحيح nesting_اونهائي = 0;
  صحيح bracket_اونهائي = 0;
  منطقي ignore_label = خطأ;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  طالما (1)
    {
      c_token *token = c_parser_peek_token (parser);
      منطقي stop = خطأ;

      إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_CASE))
	ignore_label = سچ;

      بدل (token->type)
	{
	حالة CPP_EOF:
	  اكسر;
	حالة CPP_NAME:
	  إذا (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.محفوظ_ڌڪو (token->قدر);
	  اذهب جوڙيو;
	حالة CPP_OPEN_BRACE:
	  ++nesting_اونهائي;
	  اذهب جوڙيو;
	حالة CPP_CLOSE_BRACE:
	  إذا (--nesting_اونهائي == 0 && bracket_اونهائي == 0)
	    stop = سچ;
	  اذهب جوڙيو;
	حالة CPP_OPEN_PAREN:
	  ++bracket_اونهائي;
	  اذهب جوڙيو;
	حالة CPP_CLOSE_PAREN:
	  --bracket_اونهائي;
	  اذهب جوڙيو;
	حالة CPP_COLON:
	  ignore_label = خطأ;
	  اذهب جوڙيو;
	حالة CPP_SEMICOLON:
	  إذا (nesting_اونهائي == 0 && bracket_اونهائي == 0)
	    stop = سچ;
	  اذهب جوڙيو;
	افتراضي:
	جوڙيو:
	  ٽوڪن.محفوظ_ڌڪو (*token);
	  إذا (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  وإلا إذا (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_منزل_pragma_eol (parser);
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
  ساكن بنانشان صحيح metadirective_region_ڳڻپ = 0;

  وڻ ret;
  auto_vec<c_token> directive_ٽوڪن;
  auto_vec<c_token> body_ٽوڪن;
  auto_vec<وڻ> body_labels;
  auto_vec<ثابت بنية c_omp_directive *> directives;
  auto_vec<وڻ> ctxs;
  vec<بنية omp_variant> candidates;
  منطقي default_ڏٺل = خطأ;
  صحيح directive_token_idx = 0;
  وڻ standalone_body = NULL_وڻ;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  منطقي requires_body = خطأ;

  ret = make_ڳنڍ (OMP_METADIRECTIVE);
  سيٽ_اظهار_LOCATION (ret, pragma_loc);
  وڻ_TYPE (ret) = void_type_ڳنڍ;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_وڻ;

  c_parser_consume_pragma (parser);
  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_NAME)
	  && c_parser_ايندڙ_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  اذهب error;
	}

      location_t ميلاپ_loc = c_parser_peek_token (parser)->location;
      ثابت حرف *p = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      إذا (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.جوڙيو_fixit_replace (ميلاپ_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      منطقي default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      إذا (default_p)
	{
	  إذا (default_ڏٺل)
	    {
	      error_at (ميلاپ_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      اذهب error;
	    }
	  default_ڏٺل = سچ;
	}
      وإلا إذا (default_ڏٺل)
	{
	  error_at (ميلاپ_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  اذهب error;
	}
      إذا (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (ميلاپ_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  اذهب error;
	}

      matching_parens parens;
      وڻ ctx = NULL_وڻ;
      منطقي skip = خطأ;

      إذا (!parens.require_open (parser))
	اذهب error;

      إذا (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_وڻ);
	  إذا (ctx == error_mark_ڳنڍ)
	    اذهب error;
	  ctx = omp_check_context_selector (ميلاپ_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  إذا (ctx == error_mark_ڳنڍ)
	    اذهب error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_وڻ, خطأ) == 0);

	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_COLON))
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
	  وڻ id;
	  إذا (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      إذا (i == 0)
		directive[i++] = "nothing";
	      اكسر;
	    }
	  وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->قدر;
	  وإلا إذا (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      تعداد rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  وإلا
	    اكسر;

	  directive[i] = IDENTIFIER_اشارو (id);
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
	  صحيح token_ڳڻپ = 0;
	  إذا (omp_directive->پهريون) token_ڳڻپ++;
	  إذا (omp_directive->ٻيو) token_ڳڻپ++;
	  إذا (omp_directive->ٽيون) token_ڳڻپ++;
	  لكل (صحيح j = 0; j < token_ڳڻپ; j++)
	    c_parser_consume_token (parser);
	}
      إذا (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  اذهب error;
	}
      إذا (omp_directive->قسم == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  اذهب error;
	}
      إذا (omp_directive->قسم == C_OMP_DIR_CONSTRUCT)
	requires_body = سچ;

      إذا (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_قسم = (تعداد pragma_قسم) omp_directive->id;

	  directives.محفوظ_ڌڪو (omp_directive);
	  directive_ٽوڪن.محفوظ_ڌڪو (pragma_token);
	  ctxs.محفوظ_ڌڪو (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      صحيح nesting_اونهائي = 0;
      طالما (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  بدل (token->type)
	    {
	    حالة CPP_EOF:
	    حالة CPP_PRAGMA_EOL:
	      اكسر;
	    حالة CPP_OPEN_PAREN:
	      ++nesting_اونهائي;
	      اذهب جوڙيو;
	    حالة CPP_CLOSE_PAREN:
	      إذا (nesting_اونهائي-- == 0)
		{
		  c_parser_consume_token (parser);
		  اكسر;
		}
	      اذهب جوڙيو;
	    افتراضي:
	    جوڙيو:
	      إذا (!skip)
		directive_ٽوڪن.محفوظ_ڌڪو (*token);
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
	  directive_ٽوڪن.محفوظ_ڌڪو (eol_token);
	}
    }
  c_parser_skip_منزل_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  إذا (ctxs.ڊيگهائي () == 1)
    {
      وڻ ctx = ctxs[0];
      إذا (ctx == NULL_وڻ
	  || (omp_context_selector_matches (ctx, NULL_وڻ, خطأ) == 1
	      && directive_ٽوڪن[0].pragma_قسم == PRAGMA_OMP_NOTHING))
	أرجع;
    }

  إذا (!default_ڏٺل)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ثابت بنية c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", عدم, عدم);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_قسم = PRAGMA_OMP_NOTHING;

      directives.محفوظ_ڌڪو (omp_directive);
      directive_ٽوڪن.محفوظ_ڌڪو (pragma_token);
      ctxs.محفوظ_ڌڪو (NULL_وڻ);

      c_token eol_token;
      memset (&eol_token, 0, حجم (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_ٽوڪن.محفوظ_ڌڪو (eol_token);
    }

  إذا (requires_body)
    analyze_metadirective_body (parser, body_ٽوڪن, body_labels);

  /* Process each candidate directive.  */
  بنانشان i;
  وڻ ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> ٽوڪن;

      /* Add the directive tokens.  */
      افعل
	ٽوڪن.محفوظ_ڌڪو (directive_ٽوڪن [directive_token_idx++]);
      طالما (ٽوڪن.آخري ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_ٽوڪن.is_خالي_جايون ());
      لكل (بنانشان j = 0; j < body_ٽوڪن.ڊيگهائي (); j++)
	ٽوڪن.محفوظ_ڌڪو (body_ٽوڪن[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, حجم (eof_token));
      eof_token.type = CPP_EOF;
      ٽوڪن.محفوظ_ڌڪو (eof_token);
      ٽوڪن.محفوظ_ڌڪو (eof_token);

      بنانشان صحيح old_ٽوڪن_avail = parser->ٽوڪن_avail;
      c_token *old_ٽوڪن = parser->ٽوڪن;
      بنية omp_attribute_pragma_state *old_اندريون_omp_attribute_pragma
	= parser->اندريون_omp_attribute_pragma;
      بنية omp_metadirective_parse_معلومات *old_state
	= parser->omp_metadirective_state;

      بنية omp_metadirective_parse_معلومات new_state;
      new_state.body_labels = &body_labels;
      new_state.region_انگ = ++metadirective_region_ڳڻپ;

      parser->ٽوڪن = ٽوڪن.پتو ();
      parser->ٽوڪن_avail = ٽوڪن.ڊيگهائي ();
      parser->اندريون_omp_attribute_pragma = عدم;
      parser->omp_metadirective_state = &new_state;

      صحيح prev_errorcount = errorcount;
      وڻ directive = c_begin_compound_stmt (سچ);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_وڻ);
      directive = c_پڇاڙي_compound_stmt (pragma_loc, directive, سچ);
      منطقي standalone_p
	= directives[i]->قسم == C_OMP_DIR_STANDALONE
	  || directives[i]->قسم == C_OMP_DIR_UTILITY;
      إذا (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  إذا (standalone_body == NULL_وڻ)
	    {
	      standalone_body = ڌڪو_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = ڪڍو_stmt_list (standalone_body);
	    }
	  وإلا
	    c_parser_skip_منزل_پڇاڙي_جو_بلاڪ_or_statement (parser, سچ);
	}

      وڻ body = standalone_p ? standalone_body : NULL_وڻ;
      وڻ variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      إذا (errorcount == prev_errorcount)
	{
	  gcc_assert (parser->ٽوڪن_avail == 2);
	  gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_EOF));
	  gcc_assert (c_parser_peek_2nd_token (parser)->type == CPP_EOF);
	}

      parser->ٽوڪن = old_ٽوڪن;
      parser->ٽوڪن_avail = old_ٽوڪن_avail;
      parser->اندريون_omp_attribute_pragma = old_اندريون_omp_attribute_pragma;
      parser->omp_metadirective_state = old_state;
    }

  /* Try to resolve the metadirective early.  */
  candidates = omp_early_resolve_metadirective (ret);
  إذا (!candidates.is_خالي_جايون ())
    ret = c_omp_expand_variant_construct (candidates);

  جوڙيو_stmt (ret);
  أرجع;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  إذا (parser->اندريون_pragma)
    c_parser_skip_منزل_pragma_eol (parser, خطأ);
}

/* Main entry point to parsing most OpenMP pragmas.  */

ساكن فراغ
c_parser_omp_construct (c_parser *parser, منطقي *if_p)
{
  تعداد pragma_قسم p_قسم;
  location_t loc;
  وڻ stmt;
  حرف p_name[حجم "#pragma omp teams distribute parallel for simd"];
  omp_clause_نقاب نقاب (0);

  loc = c_parser_peek_token (parser)->location;
  p_قسم = c_parser_peek_token (parser)->pragma_قسم;
  c_parser_consume_pragma (parser);

  بدل (p_قسم)
    {
    حالة PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, سچ);
      أرجع;
    حالة PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      اكسر;
    حالة PRAGMA_OACC_معلومات:
      stmt = c_parser_oacc_معلومات (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OACC_HOST_معلومات:
      stmt = c_parser_oacc_host_معلومات (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OACC_KERNELS:
    حالة PRAGMA_OACC_PARALLEL:
    حالة PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_قسم, p_name, if_p);
      اكسر;
    حالة PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, نقاب, عدم, if_p);
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
      stmt = c_parser_omp_distribute (loc, parser, p_name, نقاب, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, نقاب, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, نقاب, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, نقاب, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, نقاب, عدم, if_p,
				  UNKNOWN_LOCATION);
      اكسر;
    حالة PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, نقاب, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      اكسر;
    حالة PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, نقاب, عدم);
      اكسر;
    حالة PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, نقاب, عدم, if_p);
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
      stmt = c_parser_omp_taskloop (loc, parser, p_name, نقاب, عدم, if_p);
      اكسر;
    حالة PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, نقاب, عدم, if_p);
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

  إذا (stmt && stmt != error_mark_ڳنڍ)
    gcc_assert (اظهار_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#وصف_ڪريو OMP_GROUPPRIVATE_CLAUSE_نقاب					\
	( (OMP_CLAUSE_نقاب_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

ساكن فراغ
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  وڻ vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);
  وڻ clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_نقاب,
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
  وڻ vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, عدم);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  لكل (t = vars; t; t = وڻ_CHAIN (t))
    {
      وڻ v = وڻ_PURPOSE (t);
      loc = اظهار_LOCATION (وڻ_قدر (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      إذا (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      وإلا إذا (وڻ_استعمال_ٿيل (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      وإلا إذا (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      وإلا إذا (وڻ_TYPE (v) == error_mark_ڳنڍ)
	;
      وإلا إذا (! COMPLETE_TYPE_P (وڻ_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      وإلا
	{
	  إذا (! DECL_THREAD_LOCAL_P (v))
	    {
	      سيٽ_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      إذا (DECL_RTL_سيٽ_P (v))
		make_decl_rtl (v);
	    }
	  C_DECL_THREADPRIVATE_P (v) = 1;
	}
    }

  c_parser_skip_منزل_pragma_eol (parser);
}

/* Parse a transaction attribute (GCC Extension).

   transaction-attribute:
     gnu-attributes
     attribute-specifier
*/

ساكن وڻ
c_parser_transaction_خاصيتون (c_parser *parser)
{
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ATTRIBUTE))
    أرجع c_parser_gnu_خاصيتون (parser);

  إذا (!c_parser_ايندڙ_token_is (parser, CPP_OPEN_چورس))
    أرجع NULL_وڻ;
  أرجع c_parser_std_attribute_specifier (parser, سچ);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

ساكن وڻ
c_parser_transaction (c_parser *parser, تعداد rid keyword)
{
  بنانشان صحيح old_اندريون = parser->اندريون_transaction;
  بنانشان صحيح this_اندريون = 1, new_اندريون;
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_ايندڙ_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  إذا (keyword == RID_TRANSACTION_RELAXED)
    this_اندريون |= TM_STMT_ATTR_RELAXED;
  وإلا
    {
      attrs = c_parser_transaction_خاصيتون (parser);
      إذا (attrs)
	this_اندريون |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_اندريون = this_اندريون | (old_اندريون & TM_STMT_ATTR_OUTER);

  parser->اندريون_transaction = new_اندريون;
  stmt = c_parser_compound_statement (parser);
  parser->اندريون_transaction = old_اندريون;

  إذا (flag_tm)
    stmt = c_پڄاڻي_transaction (loc, stmt, this_اندريون);
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

ساكن بنية c_اظهار
c_parser_transaction_اظهار (c_parser *parser, تعداد rid keyword)
{
  بنية c_اظهار ret;
  بنانشان صحيح old_اندريون = parser->اندريون_transaction;
  بنانشان صحيح this_اندريون = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_ايندڙ_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  إذا (keyword == RID_TRANSACTION_RELAXED)
    this_اندريون |= TM_STMT_ATTR_RELAXED;
  وإلا
    {
      attrs = c_parser_transaction_خاصيتون (parser);
      إذا (attrs)
	this_اندريون |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->اندريون_transaction = this_اندريون;
  matching_parens parens;
  إذا (parens.require_open (parser))
    {
      وڻ اظهار = c_parser_اظهار (parser).قدر;
      ret.original_type = وڻ_TYPE (اظهار);
      ret.قدر = build1 (TRANSACTION_اظهار, ret.original_type, اظهار);
      إذا (this_اندريون & TM_STMT_ATTR_RELAXED)
	TRANSACTION_اظهار_RELAXED (ret.قدر) = 1;
      سيٽ_اظهار_LOCATION (ret.قدر, loc);
      ret.original_ڪوڊ = TRANSACTION_اظهار;
      ret.m_decimal = 0;
      إذا (!parens.require_close (parser))
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, عدم);
	  اذهب error;
	}
    }
  وإلا
    {
     error:
      ret.سيٽ_error ();
      ret.original_ڪوڊ = ERROR_MARK;
      ret.original_type = عدم;
    }
  parser->اندريون_transaction = old_اندريون;

  إذا (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  سيٽ_c_اظهار_ذريعو_range (&ret, loc, loc);

  أرجع ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

ساكن وڻ
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  وڻ attrs;
  منطقي is_outer = خطأ;

  gcc_assert (c_parser_ايندڙ_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_خاصيتون (parser);
  إذا (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  إذا (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      اذهب ret_error;
    }
  وإلا إذا (parser->اندريون_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      اذهب ret_error;
    }
  وإلا إذا (is_outer)
    {
      إذا ((parser->اندريون_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  اذهب ret_error;
	}
    }
  وإلا إذا (parser->اندريون_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      اذهب ret_error;
    }

  أرجع جوڙيو_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  أرجع build1 (NOP_اظهار, void_type_ڳنڍ, error_mark_ڳنڍ);
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
  tparser.translate_لڙيون_p = سچ;
  tparser.ٽوڪن = &tparser.ٽوڪن_buf[0];
  the_parser = &tparser;

  إذا (c_parser_peek_token (&tparser)->pragma_قسم == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  وإلا
    c_common_no_وڌيڪ_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  إذا (tparser.ٽوڪن == &tparser.ٽوڪن_buf[0])
    the_parser->ٽوڪن = &the_parser->ٽوڪن_buf[0];

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
  the_parser->ٽوڪن = &the_parser->ٽوڪن_buf[0];
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
c_parser_parse_rtl_body (c_parser *parser, حرف *شروعات_with_pass)
{
  إذا (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      حرر (شروعات_with_pass);
      أرجع c_parser_peek_token (parser)->location;
    }

  location_t شروعات_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  صحيح انگ_open_braces = 1;
  طالما (1)
    {
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_BRACE:
	  انگ_open_braces++;
	  اكسر;
	حالة CPP_CLOSE_BRACE:
	  إذا (--انگ_open_braces == 0)
	    اذهب مليو_closing_brace;
	  اكسر;
	حالة CPP_EOF:
	  error_at (شروعات_loc, "no closing brace");
	  حرر (شروعات_with_pass);
	  أرجع c_parser_peek_token (parser)->location;
	افتراضي:
	  اكسر;
	}
      c_parser_consume_token (parser);
    }

 مليو_closing_brace:
  /* At the closing brace; record its location.  */
  location_t پڇاڙي_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  إذا (!read_rtl_function_body_from_file_range (شروعات_loc, پڇاڙي_loc))
    {
      حرر (شروعات_with_pass);
      أرجع پڇاڙي_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  لاڳيتو_rtl_passes (شروعات_with_pass);
  أرجع پڇاڙي_loc;
}

#ضمن "gt-c-c-parser.h"
