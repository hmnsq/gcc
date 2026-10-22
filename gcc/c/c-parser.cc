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

#अन्तर्भाव "config.h"
#define INCLUDE_STRING
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "target.h"
#अन्तर्भाव "function.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "timevar.h"
#अन्तर्भाव "stringpool.h"
#अन्तर्भाव "cgraph.h"
#अन्तर्भाव "attribs.h"
#अन्तर्भाव "stor-layout.h"
#अन्तर्भाव "varasm.h"
#अन्तर्भाव "trans-mem.h"
#अन्तर्भाव "c-family/c-pragma.h"
#अन्तर्भाव "c-lang.h"
#अन्तर्भाव "c-family/c-objc.h"
#अन्तर्भाव "plugin.h"
#अन्तर्भाव "omp-general.h"
#अन्तर्भाव "omp-offload.h"
#अन्तर्भाव "builtins.h"
#अन्तर्भाव "gomp-constants.h"
#अन्तर्भाव "c-family/c-indentation.h"
#अन्तर्भाव "gimple-expr.h"
#अन्तर्भाव "context.h"
#अन्तर्भाव "gcc-rich-location.h"
#अन्तर्भाव "c-parser.h"
#अन्तर्भाव "gimple-parser.h"
#अन्तर्भाव "read-rtl-function.h"
#अन्तर्भाव "run-rtl-passes.h"
#अन्तर्भाव "intl.h"
#अन्तर्भाव "c-family/name-hint.h"
#अन्तर्भाव "tree-iterator.h"
#अन्तर्भाव "tree-pretty-print.h"
#अन्तर्भाव "memmodel.h"
#अन्तर्भाव "c-family/known-headers.h"
#अन्तर्भाव "bitmap.h"
#अन्तर्भाव "analyzer/analyzer-language.h"
#अन्तर्भाव "toplev.h"
#अन्तर्भाव "asan.h"
#अन्तर्भाव "c-family/c-ubsan.h"
#अन्तर्भाव "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<वृक्षः> incomplete_record_decls;

शून्य
set_c_व्यञ्जकम्_source_range (c_व्यञ्जकम् *व्यञ्जकम्,
			 location_t start, location_t finish)
{
  व्यञ्जकम्->src_range.m_start = start;
  व्यञ्जकम्->src_range.m_finish = finish;
  जइ (व्यञ्जकम्->मानम्)
    set_source_range (व्यञ्जकम्->मानम्, start, finish);
}

शून्य
set_c_व्यञ्जकम्_source_range (c_व्यञ्जकम् *व्यञ्जकम्,
			 source_range src_range)
{
  व्यञ्जकम्->src_range = src_range;
  जइ (व्यञ्जकम्->मानम्)
    set_source_range (व्यञ्जकम्->मानम्, src_range);
}


/* Initialization routine for this file.  */

शून्य
c_parse_init (शून्य)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  unsigned पूर्णाङ्क i;
  वृक्षः id;
  पूर्णाङ्क mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  जइ (!flag_isoc99)
    mask |= D_C99;
  जइ (!flag_isoc23)
    mask |= D_C23;
  जइ (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      जइ (!flag_isoc99)
	mask |= D_EXT89;
      जइ (!flag_isoc23)
	mask |= D_EXT11;
    }
  जइ (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<वृक्षः> ((पूर्णाङ्क) RID_MAX);
  प्रति (i = 0; i < अङ्कः_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      जइ (c_common_reswords[i].disable & mask)
	{
	  जइ (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  अनुवर्त;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(पूर्णाङ्क) c_common_reswords[i].rid] = id;
    }

  प्रति (i = 0; i < अङ्कः_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      वर्ण name[50];
      sprintf (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      sprintf (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  जइ (flag_openmp)
    {
      id = get_identifier ("omp_all_memory");
      C_SET_RID_CODE (id, RID_OMP_ALL_MEMORY);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [RID_OMP_ALL_MEMORY] = id;
    }
}

/* A parser structure recording information about the state and
   context of parsing.  Includes lexer information with up to two
   tokens of look-ahead; more are not needed for C.  */
संरचना GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  unsigned पूर्णाङ्क tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  unsigned पूर्णाङ्क raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  तार्किक error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  तार्किक in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  तार्किक in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  तार्किक lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  तार्किक translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  तार्किक objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  तार्किक objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  तार्किक objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  unsigned पूर्णाङ्क in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  तार्किक objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  तार्किक seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  तार्किक omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  संरचना omp_for_parse_data * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  संरचना omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  वृक्षः in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  संरचना omp_metadirective_parse_data * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
संरचना GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  unsigned पूर्णाङ्क save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
संरचना GTY(()) omp_begin_declare_variant_map_entry {
  वृक्षः variant;		/* The variant decl.  */
  वृक्षः id;		/* Name of base function.  */
  वृक्षः ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

स्थिर वृक्षः omp_start_variant_function (c_declarator *, वृक्षः);
स्थिर शून्य omp_finish_variant_function (वृक्षः, वृक्षः, वृक्षः);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, unsigned n)
{
  प्रत्यागम &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

तार्किक
c_parser_error (c_parser *parser)
{
  प्रत्यागम parser->error;
}

/* Set the error state of PARSER to ERR.  */

शून्य
c_parser_set_error (c_parser *parser, तार्किक err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

स्थिर GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

स्थिर शून्य
c_lex_one_token (c_parser *parser, c_token *token, तार्किक raw = मिच्छ)
{
  timevar_प्रक्षिप (TV_LEX);

  जइ (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->मानम्, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  अण्णहा
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      जइ (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  जइ (raw)
    गच्छ out;

  विकल्प (token->type)
    {
    पक्ष CPP_NAME:
      {
	वृक्षः decl;

	तार्किक objc_force_identifier = parser->objc_need_raw_identifier;
	जइ (c_dialect_objc ())
	  parser->objc_need_raw_identifier = मिच्छ;

	जइ (C_IS_RESERVED_WORD (token->मानम्))
	  {
	    गणना rid rid_code = C_RID_CODE (token->मानम्);

	    जइ (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->मानम्);
	      }
	    अण्णहा जइ (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		भङ्ग;
	      }
	    अण्णहा जइ (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		जइ (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    भङ्ग;
		  }
		अण्णहा जइ (parser->objc_could_be_foreach_context
			 && rid_code == RID_IN)
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
		    token->keyword = rid_code;
		    भङ्ग;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    अण्णहा जइ (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		जइ (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    भङ्ग;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    अण्णहा जइ (c_dialect_objc ()
		     && (OBJC_IS_AT_KEYWORD (rid_code)
			 || OBJC_IS_CXX_KEYWORD (rid_code)))
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
	    अण्णहा
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		भङ्ग;
	      }
	  }

	decl = lookup_name (token->मानम्);
	जइ (decl)
	  {
	    जइ (वृक्षः_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		भङ्ग;
	      }
	  }
	अण्णहा जइ (c_dialect_objc ())
	  {
	    वृक्षः objc_interface_decl = objc_is_class_name (token->मानम्);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    जइ (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->मानम् = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		भङ्ग;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      भङ्ग;
    पक्ष CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      विकल्प (C_RID_CODE (token->मानम्))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	पक्ष RID_CLASS:     token->keyword = RID_AT_CLASS; भङ्ग;
	पक्ष RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; भङ्ग;
	पक्ष RID_PROTECTED: token->keyword = RID_AT_PROTECTED; भङ्ग;
	पक्ष RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; भङ्ग;
	पक्ष RID_THROW:     token->keyword = RID_AT_THROW; भङ्ग;
	पक्ष RID_TRY:       token->keyword = RID_AT_TRY; भङ्ग;
	पक्ष RID_CATCH:     token->keyword = RID_AT_CATCH; भङ्ग;
	पक्ष RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; भङ्ग;
	स्वभाव:            token->keyword = C_RID_CODE (token->मानम्);
	}
      भङ्ग;
    पक्ष CPP_COLON:
    पक्ष CPP_COMMA:
    पक्ष CPP_CLOSE_PAREN:
    पक्ष CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      जइ (c_dialect_objc ())
	parser->objc_need_raw_identifier = मिच्छ;
      भङ्ग;
    पक्ष CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (गणना pragma_kind) वृक्षः_INT_CST_नीचः (token->मानम्);
      token->मानम् = रिक्त;
      भङ्ग;
    स्वभाव:
      भङ्ग;
    }
 out:
  timevar_निष्कासय (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  जइ (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  प्रत्यागम &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  जइ (parser->tokens_avail >= 2)
    प्रत्यागम &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  प्रत्यागम &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, unsigned पूर्णाङ्क n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  जइ (parser->tokens_avail >= n)
    प्रत्यागम &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  प्रत्यागम &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, unsigned पूर्णाङ्क n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  जइ (parser->tokens_avail >= n)
    प्रत्यागम &parser->tokens[n - 1];
  unsigned पूर्णाङ्क raw_len = vec_safe_length (parser->raw_tokens);
  unsigned पूर्णाङ्क raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  जइ (raw_avail >= n)
    प्रत्यागम &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], सच्च);
  प्रत्यागम &(*parser->raw_tokens)[raw_len];
}

तार्किक
c_keyword_starts_typename (गणना rid keyword)
{
  विकल्प (keyword)
    {
    पक्ष RID_UNSIGNED:
    पक्ष RID_LONG:
    पक्ष RID_SHORT:
    पक्ष RID_SIGNED:
    पक्ष RID_COMPLEX:
    पक्ष RID_INT:
    पक्ष RID_CHAR:
    पक्ष RID_FLOAT:
    पक्ष RID_DOUBLE:
    पक्ष RID_VOID:
    पक्ष RID_DFLOAT32:
    पक्ष RID_DFLOAT64:
    पक्ष RID_DFLOAT128:
    पक्ष RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    पक्ष RID_BOOL:
    पक्ष RID_BITINT:
    पक्ष RID_ENUM:
    पक्ष RID_STRUCT:
    पक्ष RID_UNION:
    पक्ष RID_TYPEOF:
    पक्ष RID_TYPEOF_UNQUAL:
    पक्ष RID_CONST:
    पक्ष RID_ATOMIC:
    पक्ष RID_VOLATILE:
    पक्ष RID_RESTRICT:
    पक्ष RID_ATTRIBUTE:
    पक्ष RID_FRACT:
    पक्ष RID_ACCUM:
    पक्ष RID_SAT:
    पक्ष RID_AUTO_TYPE:
    पक्ष RID_ALIGNAS:
      प्रत्यागम सच्च;
    स्वभाव:
      जइ (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + अङ्कः_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	प्रत्यागम सच्च;
      प्रत्यागम मिच्छ;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
तार्किक
c_token_starts_typename (c_token *token)
{
  विकल्प (token->type)
    {
    पक्ष CPP_NAME:
      विकल्प (token->id_kind)
	{
	पक्ष C_ID_ID:
	  प्रत्यागम मिच्छ;
	पक्ष C_ID_ADDRSPACE:
	  प्रत्यागम सच्च;
	पक्ष C_ID_TYPENAME:
	  प्रत्यागम सच्च;
	पक्ष C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  प्रत्यागम सच्च;
	स्वभाव:
	  gcc_unreachable ();
	}
    पक्ष CPP_KEYWORD:
      प्रत्यागम c_keyword_starts_typename (token->keyword);
    पक्ष CPP_LESS:
      जइ (c_dialect_objc ())
	प्रत्यागम सच्च;
      प्रत्यागम मिच्छ;
    स्वभाव:
      प्रत्यागम मिच्छ;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

स्थिर अन्तःस्थ तार्किक
c_parser_next_tokens_start_typename (c_parser *parser, गणना c_lookahead_kind la,
				     unsigned पूर्णाङ्क n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  जइ (c_token_starts_typename (token))
    प्रत्यागम सच्च;

  /* Try a bit harder to detect an unknown typename.  */
  जइ (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->मानम्))
    प्रत्यागम सच्च;

  प्रत्यागम मिच्छ;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
स्थिर तार्किक
c_token_starts_compound_literal (c_token *token)
{
  विकल्प (token->type)
    {
    पक्ष CPP_KEYWORD:
      विकल्प (token->keyword)
	{
	पक्ष RID_CONSTEXPR:
	पक्ष RID_REGISTER:
	पक्ष RID_STATIC:
	पक्ष RID_THREAD:
	  प्रत्यागम सच्च;
	स्वभाव:
	  भङ्ग;
	}
      /* Fall through.  */
    स्वभाव:
      प्रत्यागम c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
स्थिर तार्किक
c_token_is_qualifier (c_token *token)
{
  विकल्प (token->type)
    {
    पक्ष CPP_NAME:
      विकल्प (token->id_kind)
	{
	पक्ष C_ID_ADDRSPACE:
	  प्रत्यागम सच्च;
	स्वभाव:
	  प्रत्यागम मिच्छ;
	}
    पक्ष CPP_KEYWORD:
      विकल्प (token->keyword)
	{
	पक्ष RID_CONST:
	पक्ष RID_VOLATILE:
	पक्ष RID_RESTRICT:
	पक्ष RID_ATTRIBUTE:
	पक्ष RID_ATOMIC:
	  प्रत्यागम सच्च;
	स्वभाव:
	  प्रत्यागम मिच्छ;
	}
    पक्ष CPP_LESS:
      प्रत्यागम मिच्छ;
    स्वभाव:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
स्थिर अन्तःस्थ तार्किक
c_parser_next_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  प्रत्यागम c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
स्थिर तार्किक
c_token_starts_declspecs (c_token *token)
{
  विकल्प (token->type)
    {
    पक्ष CPP_NAME:
      विकल्प (token->id_kind)
	{
	पक्ष C_ID_ID:
	  प्रत्यागम मिच्छ;
	पक्ष C_ID_ADDRSPACE:
	  प्रत्यागम सच्च;
	पक्ष C_ID_TYPENAME:
	  प्रत्यागम सच्च;
	पक्ष C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  प्रत्यागम सच्च;
	स्वभाव:
	  gcc_unreachable ();
	}
    पक्ष CPP_KEYWORD:
      विकल्प (token->keyword)
	{
	पक्ष RID_STATIC:
	पक्ष RID_EXTERN:
	पक्ष RID_REGISTER:
	पक्ष RID_TYPEDEF:
	पक्ष RID_INLINE:
	पक्ष RID_NORETURN:
	पक्ष RID_AUTO:
	पक्ष RID_THREAD:
	पक्ष RID_UNSIGNED:
	पक्ष RID_LONG:
	पक्ष RID_SHORT:
	पक्ष RID_SIGNED:
	पक्ष RID_COMPLEX:
	पक्ष RID_INT:
	पक्ष RID_CHAR:
	पक्ष RID_FLOAT:
	पक्ष RID_DOUBLE:
	पक्ष RID_VOID:
	पक्ष RID_DFLOAT32:
	पक्ष RID_DFLOAT64:
	पक्ष RID_DFLOAT128:
	पक्ष RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	पक्ष RID_BOOL:
	पक्ष RID_BITINT:
	पक्ष RID_ENUM:
	पक्ष RID_STRUCT:
	पक्ष RID_UNION:
	पक्ष RID_TYPEOF:
	पक्ष RID_TYPEOF_UNQUAL:
	पक्ष RID_CONST:
	पक्ष RID_VOLATILE:
	पक्ष RID_RESTRICT:
	पक्ष RID_ATTRIBUTE:
	पक्ष RID_FRACT:
	पक्ष RID_ACCUM:
	पक्ष RID_SAT:
	पक्ष RID_ALIGNAS:
	पक्ष RID_ATOMIC:
	पक्ष RID_AUTO_TYPE:
	पक्ष RID_CONSTEXPR:
	  प्रत्यागम सच्च;
	स्वभाव:
	  जइ (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + अङ्कः_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    प्रत्यागम सच्च;
	  प्रत्यागम मिच्छ;
	}
    पक्ष CPP_LESS:
      जइ (c_dialect_objc ())
	प्रत्यागम सच्च;
      प्रत्यागम मिच्छ;
    स्वभाव:
      प्रत्यागम मिच्छ;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
स्थिर तार्किक
c_token_starts_declaration (c_token *token)
{
  जइ (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    प्रत्यागम सच्च;
  अण्णहा
    प्रत्यागम मिच्छ;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
तार्किक
c_parser_next_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  जइ (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    प्रत्यागम मिच्छ;

  प्रत्यागम c_token_starts_declspecs (token);
}

स्थिर तार्किक c_parser_check_balanced_raw_token_sequence (c_parser *,
							unsigned पूर्णाङ्क *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
तार्किक
c_parser_next_tokens_start_declaration (c_parser *parser, unsigned पूर्णाङ्क n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  जइ (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    प्रत्यागम मिच्छ;

  /* Labels do not start declarations.  */
  जइ (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    प्रत्यागम मिच्छ;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  जइ (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      जइ (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	प्रत्यागम सच्च;
      प्रत्यागम c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  जइ (c_token_starts_declaration (token))
    प्रत्यागम सच्च;

  जइ (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    प्रत्यागम सच्च;

  प्रत्यागम मिच्छ;
}

/* Consume the next token from PARSER.  */

शून्य
c_parser_consume_token (c_parser *parser)
{
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (!parser->in_pragma || parser->tokens[0].type != CPP_PRAGMA_EOL);
  /* CPP_PRAGMA should not show up here except if there was an error or inside
     another pragma.  */
  gcc_assert (parser->in_pragma
	      || parser->error
	      || parser->tokens[0].type != CPP_PRAGMA);
  parser->last_token_location = parser->tokens[0].location;
  जइ (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  अण्णहा जइ (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      जइ (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          जइ (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = मिच्छ;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

स्थिर शून्य
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  जइ (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  अण्णहा जइ (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      जइ (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = सच्च;
}

/* Update the global input_location from TOKEN.  */
स्थिर अन्तःस्थ शून्य
c_parser_set_source_position_from_token (c_token *token)
{
  जइ (token->type != CPP_EOF)
    {
      निवेशः_location = token->location;
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

स्थिर तार्किक
c_parser_peek_conflict_marker (c_parser *parser, गणना cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  जइ (token2->type != tok1_kind)
    प्रत्यागम मिच्छ;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  जइ (token3->type != tok1_kind)
    प्रत्यागम मिच्छ;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  जइ (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    प्रत्यागम मिच्छ;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  जइ (LOCATION_COLUMN (start_loc) != 1)
    प्रत्यागम मिच्छ;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  प्रत्यागम सच्च;
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

स्थिर तार्किक
c_parser_error_richloc (c_parser *parser, ध्रुव वर्ण *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  जइ (parser->error)
    प्रत्यागम मिच्छ;
  parser->error = सच्च;
  जइ (!gmsgid)
    प्रत्यागम मिच्छ;

  /* If this is actually a conflict marker, report it as such.  */
  जइ (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      जइ (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  प्रत्यागम सच्च;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  जइ (parser->seen_string_literal && token->type == CPP_NAME)
    {
      वृक्षः name = token->मानम्;
      ध्रुव वर्ण *token_name = IDENTIFIER_POINTER (name);
      ध्रुव वर्ण *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      जइ (header_hint != रिक्त)
	h = name_hint (nullptr,
		       std::make_unique<suggest_missing_header>
			 (token->location,
			  token_name,
			  header_hint));
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
		 token->मानम्, /*flags=*/0, richloc);
  प्रत्यागम सच्च;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

तार्किक
c_parser_error (c_parser *parser, ध्रुव वर्ण *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (पङ्क्तिः_table, निवेशः_location);
  प्रत्यागम c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

template <typename traits_t>
वर्ग token_pair
{
 सार्वजनिक:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  तार्किक require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    जइ (token)
      m_open_loc = token->location;

    प्रत्यागम c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  शून्य consume_open (c_parser *parser)
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

  तार्किक require_close (c_parser *parser) ध्रुव
  {
    प्रत्यागम c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  शून्य skip_until_found_close (c_parser *parser) ध्रुव
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 गुप्त:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

संरचना matching_paren_traits
{
  स्थिर ध्रुव गणना cpp_ttype open_token_type = CPP_OPEN_PAREN;
  स्थिर ध्रुव वर्ण * ध्रुव open_gmsgid;
  स्थिर ध्रुव गणना cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  स्थिर ध्रुव वर्ण * ध्रुव close_gmsgid;
};

ध्रुव वर्ण * ध्रुव matching_paren_traits::open_gmsgid = "expected %<(%>";
ध्रुव वर्ण * ध्रुव matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

प्रकारनिर्देश token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

संरचना matching_brace_traits
{
  स्थिर ध्रुव गणना cpp_ttype open_token_type = CPP_OPEN_BRACE;
  स्थिर ध्रुव वर्ण * ध्रुव open_gmsgid;
  स्थिर ध्रुव गणना cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  स्थिर ध्रुव वर्ण * ध्रुव close_gmsgid;
};

ध्रुव वर्ण * ध्रुव matching_brace_traits::open_gmsgid = "expected %<{%>";
ध्रुव वर्ण * ध्रुव matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

प्रकारनिर्देश token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

स्थिर ध्रुव वर्ण *
get_matching_चिह्नम् (गणना cpp_ttype type)
{
  विकल्प (type)
    {
    स्वभाव:
      gcc_unreachable ();
    पक्ष CPP_CLOSE_PAREN:
      प्रत्यागम "(";
    पक्ष CPP_CLOSE_BRACE:
      प्रत्यागम "{";
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

तार्किक
c_parser_require (c_parser *parser,
		  गणना cpp_ttype type,
		  ध्रुव वर्ण *msgid,
		  location_t matching_location,
		  तार्किक type_is_unique)
{
  जइ (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      प्रत्यागम सच्च;
    }
  अण्णहा
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      जइ (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      तार्किक added_matching_location = मिच्छ;
      जइ (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      जइ (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	जइ (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_चिह्नम् (type));

      प्रत्यागम मिच्छ;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

स्थिर तार्किक
c_parser_require_keyword (c_parser *parser,
			  गणना rid keyword,
			  ध्रुव वर्ण *msgid)
{
  जइ (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      प्रत्यागम सच्च;
    }
  अण्णहा
    {
      c_parser_error (parser, msgid);
      प्रत्यागम मिच्छ;
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

शून्य
c_parser_skip_until_found (c_parser *parser,
			   गणना cpp_ttype type,
			   ध्रुव वर्ण *msgid,
			   location_t matching_location)
{
  unsigned nesting_depth = 0;

  जइ (c_parser_require (parser, type, msgid, matching_location))
    {
      जइ (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  जइ (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = रिक्त;
	    }
	}
      प्रत्यागम;
    }

  /* Skip tokens until the desired token is found.  */
  जाव (सच्च)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      जइ (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  जइ (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      जइ (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = रिक्त;
		}
	    }
	  भङ्ग;
	}

      /* If we've run out of tokens, stop.  */
      जइ (token->type == CPP_EOF)
	प्रत्यागम;
      जइ (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	प्रत्यागम;
      जइ (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      अण्णहा जइ (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  जइ (nesting_depth-- == 0)
	    भङ्ग;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = मिच्छ;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

स्थिर शून्य
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  जाव (सच्च)
    {
      c_token *token = c_parser_peek_token (parser);
      जइ ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	भङ्ग;
      /* If we've run out of tokens, stop.  */
      जइ (token->type == CPP_EOF)
	प्रत्यागम;
      जइ (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	प्रत्यागम;
      जइ (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      अण्णहा जइ (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  जइ (nesting_depth-- == 0)
	    भङ्ग;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = मिच्छ;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

स्थिर तार्किक
c_parser_skip_to_closing_brace (c_parser *parser)
{
  unsigned nesting_depth = 0;

  जाव (सच्च)
    {
      c_token *token = c_parser_peek_token (parser);

      विकल्प (token->type)
	{
	पक्ष CPP_PRAGMA_EOL:
	  जइ (!parser->in_pragma)
	    भङ्ग;
	  /* FALLTHRU */
	पक्ष CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  प्रत्यागम मिच्छ;

	पक्ष CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  जइ (nesting_depth-- == 0)
	    प्रत्यागम सच्च;
	  भङ्ग;

	पक्ष CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  भङ्ग;

	स्वभाव:
	  भङ्ग;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

स्थिर शून्य
c_parser_skip_to_pragma_eol (c_parser *parser, तार्किक error_if_not_eol = सच्च)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = मिच्छ;

  जइ (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  करेहि
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      जइ (token_type == CPP_EOF)
	भङ्ग;
      c_parser_consume_token (parser);
    }
  जाव (token_type != CPP_PRAGMA_EOL);

  जइ (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      जइ (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = रिक्त;
	}
    }

  parser->error = मिच्छ;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
स्थिर शून्य
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  प्रति (पूर्णाङ्क depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      विकल्प (token->type)
	{
	पक्ष CPP_PRAGMA_EOL:
	  जइ (!parser->in_pragma)
	    भङ्ग;
	  /* FALLTHRU */
	पक्ष CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  प्रत्यागम;

	पक्ष CPP_PRAGMA:
	  जइ ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      वृक्षः id1 = c_parser_peek_nth_token (parser, 2)->मानम्;
	      वृक्षः id2 = c_parser_peek_nth_token (parser, 3)->मानम्;
	      जइ (strcmp (IDENTIFIER_POINTER (id1), "declare") == 0
		  && strcmp (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  जइ (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  अण्णहा
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  अनुवर्त;

	स्वभाव:
	  भङ्ग;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

स्थिर शून्य
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    तार्किक metadirective_p = मिच्छ)
{
  unsigned nesting_depth = 0;
  पूर्णाङ्क bracket_depth = 0;
  तार्किक save_error = parser->error;

  जाव (सच्च)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      विकल्प (token->type)
	{
	पक्ष CPP_EOF:
	  प्रत्यागम;

	पक्ष CPP_PRAGMA_EOL:
	  जइ (parser->in_pragma)
	    प्रत्यागम;
	  भङ्ग;

	पक्ष CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  जइ (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      गच्छ finished;
	    }
	  भङ्ग;

	पक्ष CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  जइ ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      गच्छ finished;
	    }
	  भङ्ग;

	पक्ष CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  भङ्ग;

	पक्ष CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  जइ (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  भङ्ग;

	पक्ष CPP_CLOSE_PAREN:
	  जइ (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  भङ्ग;

	पक्ष CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  parser->error = save_error;
	  अनुवर्त;

	स्वभाव:
	  भङ्ग;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = मिच्छ;
}

/* CPP's options (initialized by c-opts.cc).  */
बाह्य cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

स्थिर अन्तःस्थ पूर्णाङ्क
disable_extension_diagnostics (शून्य)
{
  पूर्णाङ्क ret = (pedantic
	     | (warn_pointer_arith << 1)
	     | (warn_traditional << 2)
	     | (flag_iso << 3)
	     | (warn_long_long << 4)
	     | (warn_cxx_compat << 5)
	     | (warn_overlength_strings << 6)
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
  warn_pointer_arith = 0;
  cpp_opts->cpp_warn_traditional = warn_traditional = 0;
  flag_iso = 0;
  cpp_opts->cpp_warn_long_long = warn_long_long = 0;
  warn_cxx_compat = 0;
  warn_overlength_strings = 0;
  warn_c90_c99_compat = 0;
  warn_c99_c11_compat = 0;
  warn_c11_c23_compat = 0;
  warn_c23_c2y_compat = 0;
  प्रत्यागम ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

स्थिर अन्तःस्थ शून्य
restore_extension_diagnostics (पूर्णाङ्क flags)
{
  cpp_opts->cpp_pedantic = pedantic = flags & 1;
  warn_pointer_arith = (flags >> 1) & 1;
  cpp_opts->cpp_warn_traditional = warn_traditional = (flags >> 2) & 1;
  flag_iso = (flags >> 3) & 1;
  cpp_opts->cpp_warn_long_long = warn_long_long = (flags >> 4) & 1;
  warn_cxx_compat = (flags >> 5) & 1;
  warn_overlength_strings = (flags >> 6) & 1;
  /* See above for why is this needed.  */
  warn_c90_c99_compat = (flags >> 7) & 1 ? 1 : ((flags >> 8) & 1 ? -1 : 0);
  warn_c99_c11_compat = (flags >> 9) & 1 ? 1 : ((flags >> 10) & 1 ? -1 : 0);
  warn_c11_c23_compat = (flags >> 11) & 1 ? 1 : ((flags >> 12) & 1 ? -1 : 0);
  warn_c23_c2y_compat = (flags >> 13) & 1 ? 1 : ((flags >> 14) & 1 ? -1 : 0);
}

/* Helper data structure for parsing #pragma acc routine.  */
संरचना oacc_routine_data {
  तार्किक error_seen; /* Set if error has been reported.  */
  तार्किक fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  वृक्षः clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
स्थिर वृक्षः objc_foreach_break_label, objc_foreach_continue_label;

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
संरचना omp_for_parse_data {
  गणना वृक्षः_code code;
  वृक्षः declv, condv, incrv, initv;
  वृक्षः pre_body;
  वृक्षः bindings;
  पूर्णाङ्क गणनम्;	/* Expected nesting depth.  */
  पूर्णाङ्क depth;	/* Current nesting depth.  */
  location_t for_loc;
  तार्किक ordered : 1;
  तार्किक inscan : 1;
  तार्किक want_nested_loop : 1;
  तार्किक in_intervening_code : 1;
  तार्किक saw_intervening_code: 1;
  तार्किक perfect_nesting_fail : 1;
  तार्किक fail : 1;
};

संरचना attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  तार्किक musttail_p;

  शून्य reset () { musttail_p = मिच्छ; }
};

स्थिर तार्किक c_parser_nth_token_starts_std_attributes (c_parser *,
						      unsigned पूर्णाङ्क);
स्थिर वृक्षः c_parser_std_attribute_specifier_sequence (c_parser *);
स्थिर शून्य c_parser_external_declaration (c_parser *);
स्थिर शून्य c_parser_asm_definition (c_parser *);
स्थिर वृक्षः c_parser_declaration_or_fndef (c_parser *, तार्किक, तार्किक, तार्किक,
					   तार्किक, तार्किक, तार्किक, वृक्षः * = रिक्त,
					   vec<c_token> * = रिक्त,
					   तार्किक have_attrs = मिच्छ,
					   वृक्षः attrs = रिक्त,
					   संरचना oacc_routine_data * = रिक्त,
					   तार्किक * = रिक्त);
स्थिर तार्किक c_parser_handle_statement_omp_attributes (c_parser *, वृक्षः &,
						      तार्किक *);
स्थिर शून्य c_parser_static_assert_declaration_no_semi (c_parser *);
स्थिर शून्य c_parser_static_assert_declaration (c_parser *);
स्थिर संरचना c_typespec c_parser_enum_specifier (c_parser *);
स्थिर संरचना c_typespec c_parser_struct_or_union_specifier (c_parser *);
स्थिर वृक्षः c_parser_struct_declaration (c_parser *, वृक्षः *);
स्थिर संरचना c_typespec c_parser_typeof_specifier (c_parser *);
स्थिर वृक्षः c_parser_alignas_specifier (c_parser *);
स्थिर संरचना c_declarator *c_parser_direct_declarator (c_parser *, तार्किक,
							c_dtr_syn, तार्किक *);
स्थिर संरचना c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      तार्किक,
							      संरचना c_declarator *);
स्थिर संरचना c_arg_info *c_parser_parms_declarator (c_parser *, तार्किक, वृक्षः,
						     तार्किक);
स्थिर संरचना c_arg_info *c_parser_parms_list_declarator (c_parser *, वृक्षः,
							  वृक्षः, तार्किक);
स्थिर संरचना c_parm *c_parser_parameter_declaration (c_parser *, वृक्षः, तार्किक);
स्थिर वृक्षः c_parser_asm_string_literal (c_parser *);
स्थिर वृक्षः c_parser_simple_asm_व्यञ्जकम् (c_parser *);
स्थिर वृक्षः c_parser_gnu_attributes (c_parser *);
स्थिर संरचना c_व्यञ्जकम् c_parser_initializer (c_parser *, वृक्षः);
स्थिर संरचना c_व्यञ्जकम् c_parser_braced_init (c_parser *, वृक्षः, तार्किक,
					   संरचना obstack *, तार्किक);
स्थिर शून्य c_parser_initelt (c_parser *, संरचना obstack *);
स्थिर शून्य c_parser_initval (c_parser *, संरचना c_व्यञ्जकम् *,
			      संरचना obstack *);
स्थिर वृक्षः c_parser_compound_statement (c_parser *, location_t * = रिक्त);
स्थिर location_t c_parser_compound_statement_nostart (c_parser *);
स्थिर शून्य c_parser_label (c_parser *, वृक्षः);
स्थिर शून्य c_parser_statement (c_parser *, तार्किक *, location_t * = रिक्त);
स्थिर शून्य c_parser_statement_after_labels (c_parser *, तार्किक *, वृक्षः,
					     vec<वृक्षः> * = रिक्त,
					     attr_state = {});
स्थिर वृक्षः c_parser_c99_block_statement (c_parser *, तार्किक *,
					  location_t * = रिक्त);
स्थिर शून्य c_parser_if_statement (c_parser *, तार्किक *, vec<वृक्षः> *);
स्थिर शून्य c_parser_switch_statement (c_parser *, तार्किक *, वृक्षः);
स्थिर शून्य c_parser_while_statement (c_parser *, तार्किक, unsigned short, तार्किक,
				      तार्किक *, वृक्षः);
स्थिर शून्य c_parser_do_statement (c_parser *, तार्किक, unsigned short, तार्किक,
				   वृक्षः);
स्थिर शून्य c_parser_for_statement (c_parser *, तार्किक, unsigned short, तार्किक,
				    तार्किक *, वृक्षः);
स्थिर वृक्षः c_parser_asm_statement (c_parser *);
स्थिर वृक्षः c_parser_asm_operands (c_parser *);
स्थिर वृक्षः c_parser_asm_goto_operands (c_parser *);
स्थिर वृक्षः c_parser_asm_clobbers (c_parser *);
स्थिर संरचना c_व्यञ्जकम् c_parser_व्यञ्जकम्_no_commas (c_parser *, संरचना c_व्यञ्जकम् *,
					      वृक्षः = NULL_वृक्षः);
स्थिर संरचना c_व्यञ्जकम् c_parser_conditional_expression (c_parser *,
						      संरचना c_व्यञ्जकम् *, वृक्षः);
स्थिर संरचना c_व्यञ्जकम् c_parser_द्विमान_expression (c_parser *, संरचना c_व्यञ्जकम् *,
						 वृक्षः);
स्थिर संरचना c_व्यञ्जकम् c_parser_cast_expression (c_parser *, संरचना c_व्यञ्जकम् *);
स्थिर संरचना c_व्यञ्जकम् c_parser_unary_expression (c_parser *);
स्थिर संरचना c_व्यञ्जकम् c_parser_sizeof_or_countof_expression (c_parser *,
							    गणना rid);
स्थिर संरचना c_व्यञ्जकम् c_parser_alignof_expression (c_parser *);
स्थिर संरचना c_व्यञ्जकम् c_parser_maxof_or_minof_expression (c_parser *, गणना rid);
स्थिर संरचना c_व्यञ्जकम् c_parser_postfix_expression (c_parser *);
स्थिर संरचना c_व्यञ्जकम् c_parser_postfix_expression_after_paren_type (c_parser *,
								   संरचना c_declspecs *,
								   संरचना c_type_name *,
								   location_t);
स्थिर संरचना c_व्यञ्जकम् c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								संरचना c_व्यञ्जकम्);
स्थिर वृक्षः c_parser_transaction (c_parser *, गणना rid);
स्थिर संरचना c_व्यञ्जकम् c_parser_transaction_expression (c_parser *, गणना rid);
स्थिर वृक्षः c_parser_transaction_cancel (c_parser *);
स्थिर संरचना c_व्यञ्जकम् c_parser_expression (c_parser *);
स्थिर संरचना c_व्यञ्जकम् c_parser_expression_conv (c_parser *);
स्थिर vec<वृक्षः, va_gc> *c_parser_व्यञ्जकम्_list (c_parser *, तार्किक, तार्किक,
					     vec<वृक्षः, va_gc> **, location_t *,
					     वृक्षः *, vec<location_t> *,
					     unsigned पूर्णाङ्क * = रिक्त);
स्थिर संरचना c_व्यञ्जकम् c_parser_has_attribute_expression (c_parser *);

स्थिर शून्य c_parser_oacc_declare (c_parser *);
स्थिर शून्य c_parser_oacc_enter_exit_data (c_parser *, तार्किक);
स्थिर शून्य c_parser_oacc_update (c_parser *);
स्थिर शून्य c_parser_omp_construct (c_parser *, तार्किक *);
स्थिर शून्य c_parser_omp_groupprivate (c_parser *);
स्थिर शून्य c_parser_omp_threadprivate (c_parser *);
स्थिर शून्य c_parser_omp_barrier (c_parser *);
स्थिर शून्य c_parser_omp_depobj (c_parser *);
स्थिर शून्य c_parser_omp_flush (c_parser *);
स्थिर तार्किक c_parser_omp_next_tokens_can_be_canon_loop (c_parser *,
							गणना वृक्षः_code, तार्किक);
स्थिर वृक्षः c_parser_omp_loop_nest (c_parser *, तार्किक *);
स्थिर वृक्षः c_parser_omp_for_loop (location_t, c_parser *, गणना वृक्षः_code,
				   वृक्षः, वृक्षः *, तार्किक *);
स्थिर शून्य c_parser_omp_taskwait (c_parser *);
स्थिर शून्य c_parser_omp_taskyield (c_parser *);
स्थिर शून्य c_parser_omp_cancel (c_parser *);
स्थिर शून्य c_parser_omp_nothing (c_parser *);
स्थिर शून्य c_parser_omp_metadirective (c_parser *, तार्किक *);

गणना pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
स्थिर तार्किक c_parser_pragma (c_parser *, गणना pragma_context, तार्किक *, वृक्षः);
स्थिर तार्किक c_parser_omp_cancellation_point (c_parser *, गणना pragma_context);
स्थिर तार्किक c_parser_omp_target (c_parser *, गणना pragma_context, तार्किक *);
स्थिर शून्य c_parser_omp_begin (c_parser *);
स्थिर शून्य c_parser_omp_end (c_parser *);
स्थिर तार्किक c_parser_omp_declare (c_parser *, गणना pragma_context);
स्थिर शून्य c_parser_omp_requires (c_parser *);
स्थिर तार्किक c_parser_omp_error (c_parser *, गणना pragma_context);
स्थिर शून्य c_parser_omp_assumption_clauses (c_parser *, तार्किक);
स्थिर शून्य c_parser_omp_allocate (c_parser *);
स्थिर शून्य c_parser_omp_assumes (c_parser *);
स्थिर तार्किक c_parser_omp_ordered (c_parser *, गणना pragma_context, तार्किक *);
स्थिर वृक्षः c_parser_omp_dispatch (location_t, c_parser *);
स्थिर शून्य c_parser_omp_interop (c_parser *);
स्थिर शून्य c_parser_oacc_routine (c_parser *, गणना pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
स्थिर शून्य c_parser_objc_class_definition (c_parser *, वृक्षः);
स्थिर शून्य c_parser_objc_class_instance_variables (c_parser *);
स्थिर शून्य c_parser_objc_class_declaration (c_parser *);
स्थिर शून्य c_parser_objc_alias_declaration (c_parser *);
स्थिर शून्य c_parser_objc_protocol_definition (c_parser *, वृक्षः);
स्थिर तार्किक c_parser_objc_method_type (c_parser *);
स्थिर शून्य c_parser_objc_method_definition (c_parser *);
स्थिर शून्य c_parser_objc_methodprotolist (c_parser *);
स्थिर शून्य c_parser_objc_methodproto (c_parser *);
स्थिर वृक्षः c_parser_objc_method_decl (c_parser *, तार्किक, वृक्षः *, वृक्षः *);
स्थिर वृक्षः c_parser_objc_type_name (c_parser *);
स्थिर वृक्षः c_parser_objc_protocol_refs (c_parser *);
स्थिर शून्य c_parser_objc_try_catch_finally_statement (c_parser *);
स्थिर शून्य c_parser_objc_synchronized_statement (c_parser *);
स्थिर वृक्षः c_parser_objc_selector (c_parser *);
स्थिर वृक्षः c_parser_objc_selector_arg (c_parser *);
स्थिर वृक्षः c_parser_objc_receiver (c_parser *);
स्थिर वृक्षः c_parser_objc_message_args (c_parser *);
स्थिर वृक्षः c_parser_objc_keywordexpr (c_parser *);
स्थिर शून्य c_parser_objc_at_property_declaration (c_parser *);
स्थिर शून्य c_parser_objc_at_synthesize_declaration (c_parser *);
स्थिर शून्य c_parser_objc_at_dynamic_declaration (c_parser *);
स्थिर तार्किक c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, संरचना c_declspecs *);
स्थिर location_t c_parser_parse_rtl_body (c_parser *, वर्ण *);
स्थिर वृक्षः c_parser_handle_musttail (c_parser *, वृक्षः, attr_state &);

#जइ ENABLE_ANALYZER

नामाकाश ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

वर्ग c_translation_unit : सार्वजनिक translation_unit
{
सार्वजनिक:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  वृक्षः lookup_constant_by_id (वृक्षः id) ध्रुव final override
  {
    /* Consider decls.  */
    जइ (वृक्षः decl = lookup_name (id))
      जइ (वृक्षः_CODE (decl) == CONST_DECL)
	जइ (वृक्षः मानम् = DECL_INITIAL (decl))
	  जइ (वृक्षः_CODE (मानम्) == INTEGER_CST)
	    प्रत्यागम मानम्;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    जइ (cpp_macro_p (hashnode))
      जइ (वृक्षः मानम् = consider_macro (hashnode->मानम्.macro))
	प्रत्यागम मानम्;

    प्रत्यागम NULL_वृक्षः;
  }

  वृक्षः
  lookup_type_by_id (वृक्षः id) ध्रुव final override
  {
    जइ (वृक्षः type_decl = lookup_name (id))
	जइ (वृक्षः_CODE (type_decl) == TYPE_DECL)
	  {
	    वृक्षः record_type = वृक्षः_TYPE (type_decl);
	    जइ (वृक्षः_CODE (record_type) == RECORD_TYPE)
	      प्रत्यागम record_type;
	  }

    प्रत्यागम NULL_वृक्षः;
  }

  वृक्षः
  lookup_global_var_by_id (वृक्षः id) ध्रुव final override
  {
    जइ (वृक्षः var_decl = lookup_name (id))
      जइ (वृक्षः_CODE (var_decl) == VAR_DECL)
				प्रत्यागम var_decl;

    प्रत्यागम NULL_वृक्षः;
  }

गुप्त:
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
  वृक्षः consider_macro (cpp_macro *macro, पूर्णाङ्क depth = 0) ध्रुव
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    जइ (macro->paramc > 0)
      प्रत्यागम NULL_वृक्षः;
    जइ (macro->kind != cmk_macro)
      प्रत्यागम NULL_वृक्षः;
    जइ (macro->गणनम् != 1)
      प्रत्यागम NULL_वृक्षः;
    ध्रुव cpp_token &tok = macro->exp.tokens[0];
    जइ (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	जइ (depth >= param_analyzer_max_macro_alias_depth)
	  प्रत्यागम NULL_वृक्षः;

	cpp_hashnode *alias = tok.val.ग्रन्थिः.ग्रन्थिः;
	जइ (cpp_macro_p (alias))
	  प्रत्यागम consider_macro (alias->मानम्.macro, depth + 1);

	/* Not a simple alias.  */
	प्रत्यागम NULL_वृक्षः;
      }
    अण्णहा जइ (tok.type != CPP_सङ्ख्या)
      प्रत्यागम NULL_वृक्षः;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, रिक्त, पङ्क्तिः_table);

    pretty_printer pp;
    pp_string (&pp, (ध्रुव वर्ण *) tok.val.str.text);
    pp_newline (&pp);
    cpp_प्रक्षिप_buffer (parse_in,
		     (ध्रुव unsigned वर्ण *) pp_formatted_text (&pp),
		     strlen (pp_formatted_text (&pp)),
		     0);

    वृक्षः मानम्;
    location_t loc;
    unsigned वर्ण cpp_flags;
    c_lex_with_flags (&मानम्, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    जइ (मानम् && वृक्षः_CODE (मानम्) == INTEGER_CST)
      प्रत्यागम मानम्;

    प्रत्यागम NULL_वृक्षः;
  }
};

} // namespace ana

#endif /* #if ENABLE_ANALYZER */

/* Parse a translation unit (C90 6.7, C99 6.9, C11 6.9).

   translation-unit:
     external-declarations

   external-declarations:
     external-declaration
     external-declarations external-declaration

   GNU extensions:

   translation-unit:
     empty
*/

स्थिर शून्य
c_parser_translation_unit (c_parser *parser)
{
  जइ (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  अण्णहा
    {
      शून्य *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (मिच्छ);
      करेहि
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      जाव (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  unsigned पूर्णाङ्क i;
  वृक्षः decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    जइ (DECL_SIZE (decl) == NULL_वृक्षः && वृक्षः_TYPE (decl) != error_mark_ग्रन्थिः)
      error ("storage size of %q+D isn%'t known", decl);

  जइ (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->निष्कासय ();
      जइ (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  जइ (vec_safe_length (current_omp_begin_assumes))
    {
      जइ (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  जइ (vec_safe_length (current_omp_declare_variant_attribute))
    {
      जइ (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  जइ (vec_safe_length (omp_begin_declare_variant_map))
    {
      unsigned पूर्णाङ्क i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#जइ ENABLE_ANALYZER
  जइ (flag_analyzer)
    {
      ana::c_translation_unit tu;
      ana::on_finish_translation_unit (tu);
    }
#endif
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

स्थिर शून्य
c_parser_external_declaration (c_parser *parser)
{
  पूर्णाङ्क ext;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  भङ्ग;
	पक्ष RID_ASM:
	  c_parser_asm_definition (parser);
	  भङ्ग;
	पक्ष RID_AT_INTERFACE:
	पक्ष RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_वृक्षः);
	  भङ्ग;
	पक्ष RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  भङ्ग;
	पक्ष RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  भङ्ग;
	पक्ष RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_वृक्षः);
	  भङ्ग;
	पक्ष RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  भङ्ग;
	पक्ष RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  भङ्ग;
	पक्ष RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  भङ्ग;
	पक्ष RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  भङ्ग;
	स्वभाव:
	  गच्छ decl_or_fndef;
	}
      भङ्ग;
    पक्ष CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (सच्च);
      c_parser_pragma (parser, pragma_external, रिक्त, NULL_वृक्षः);
      mark_valid_location_for_stdc_pragma (मिच्छ);
      भङ्ग;
    पक्ष CPP_PLUS:
    पक्ष CPP_MINUS:
      जइ (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  भङ्ग;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    स्वभाव:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, मिच्छ, सच्च,
				     मिच्छ);
      भङ्ग;
    }
}

स्थिर शून्य c_parser_handle_directive_omp_attributes (वृक्षः &, vec<c_token> *&,
						      vec<c_token> *);
स्थिर शून्य c_finish_omp_declare_simd (c_parser *, वृक्षः, वृक्षः, vec<c_token> *);
स्थिर शून्य c_finish_oacc_routine (संरचना oacc_routine_data *, वृक्षः, तार्किक);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

स्थिर शून्य
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  जइ (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    प्रत्यागम;

  वृक्षः stmt = build0 (DEBUG_BEGIN_STMT, void_type_ग्रन्थिः);
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

स्थिर वृक्षः
handle_assume_attribute (location_t here, वृक्षः attrs, तार्किक nested)
{
  जइ (nested)
    प्रति (वृक्षः attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", वृक्षः_CHAIN (attr)))
      {
	वृक्षः args = वृक्षः_मानम् (attr);
	पूर्णाङ्क nargs = list_length (args);
	जइ (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	अण्णहा
	  {
	    वृक्षः arg = वृक्षः_मानम् (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, मिच्छ, रिक्त);
	    जइ (arg != error_mark_ग्रन्थिः)
	      {
		वृक्षः fn = build_call_व्यञ्जकम्_internal_loc (here, IFN_ASSUME,
							void_type_ग्रन्थिः, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  अण्णहा
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  प्रत्यागम remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

स्थिर शून्य
c_parser_maybe_reclassify_token (c_parser *parser)
{
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      जइ (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  वृक्षः decl = lookup_name (token->मानम्);

	  token->id_kind = C_ID_ID;
	  जइ (decl)
	    {
	      जइ (वृक्षः_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  अण्णहा जइ (c_dialect_objc ())
	    {
	      वृक्षः objc_interface_decl = objc_is_class_name (token->मानम्);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      जइ (objc_interface_decl)
		{
		  token->मानम् = objc_interface_decl;
		  token->id_kind = C_ID_CLASSNAME;
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

स्थिर वृक्षः
c_parser_declaration_or_fndef (c_parser *parser, तार्किक fndef_ok,
			       तार्किक static_assert_ok, तार्किक empty_ok,
			       तार्किक nested, तार्किक start_attr_ok,
			       तार्किक simple_ok,
			       वृक्षः *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       तार्किक have_attrs /* = false */,
			       वृक्षः attrs /* = NULL_TREE */,
			       संरचना oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       तार्किक *fallthru_attr_p /* = NULL */)
{
  संरचना c_declspecs *specs;
  वृक्षः prefix_attrs;
  वृक्षः all_prefix_attrs;
  तार्किक diagnosed_no_specs = मिच्छ;
  location_t here = c_parser_peek_token (parser)->location;
  वृक्षः result = NULL_वृक्षः;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  जइ (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      प्रत्यागम result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  जइ (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = मिच्छ;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  जइ (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->मानम्)))
    {
      वृक्षः name = c_parser_peek_token (parser)->मानम्;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      जइ (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_निवेशय_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      अण्णहा जइ (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_निवेशय_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      अण्णहा जइ (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_निवेशय_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      अण्णहा
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  जइ (ध्रुव वर्ण *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  अण्णहा
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->मानम् = error_mark_ग्रन्थिः;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  जइ (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = सच्च;

  c_parser_declspecs (parser, specs, सच्च, सच्च, start_attr_ok,
		      सच्च, सच्च, start_attr_ok, सच्च, cla_nonabstract_decl);
  जइ (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      प्रत्यागम result;
    }
  जइ (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      प्रत्यागम result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  जइ (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_शिखरम्_anonymous_type (specs->type);

  तार्किक gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  तार्किक std_auto_type_p = specs->c23_auto_p;
  तार्किक any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ध्रुव वर्ण *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  जइ (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      विकल्प (specs->typespec_kind)
	{
	पक्ष ctsk_tagfirstref:
	पक्ष ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  भङ्ग;

	पक्ष ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  भङ्ग;

	स्वभाव:
	  भङ्ग;
	}
    }

  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      तार्किक handled_assume = मिच्छ;
      जइ (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       रिक्त))
	{
	  जइ (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  जाव (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, रिक्त, NULL_वृक्षः);
	    }
	  c_parser_consume_token (parser);
	  प्रत्यागम result;
	}
      जइ (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = सच्च;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      जइ (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      अण्णहा जइ (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  जइ (fallthru_attr_p != रिक्त)
	    *fallthru_attr_p = सच्च;
	  जइ (nested)
	    {
	      वृक्षः fn = build_call_व्यञ्जकम्_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_ग्रन्थिः, 0);
	      add_stmt (fn);
	    }
	  अण्णहा
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      अण्णहा जइ (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      अण्णहा
	{
	  shadow_tag_warned (specs, 1);
	  जइ (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      जइ (specs->व्यञ्जकम्)
	add_stmt (fold_convert (void_type_ग्रन्थिः, specs->व्यञ्जकम्));
      c_parser_consume_token (parser);
      जइ (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_वृक्षः, मिच्छ);
      प्रत्यागम result;
    }
  अण्णहा जइ (specs->typespec_kind == ctsk_none
	   && nested
	   /* Only parse __attribute__((musttail)) when called from
	      c_parser_compound_statement_nostart.  This certainly isn't
	      a declaration in that case, but we don't do tentative parsing
	      of GNU attributes right now.  */
	   && fallthru_attr_p
	   && c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      attr_state astate = {};
      specs->attrs = c_parser_handle_musttail (parser, specs->attrs, astate);
      जइ (astate.musttail_p)
	{
	  जइ (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, रिक्त, NULL_वृक्षः, रिक्त,
					   astate);
	  प्रत्यागम result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  जइ (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = मिच्छ;
      shadow_tag_warned (specs, 1);
      प्रत्यागम result;
    }
  अण्णहा जइ (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      विकल्प (c_parser_peek_token (parser)->type)
	{
	  पक्ष CPP_PLUS:
	  पक्ष CPP_MINUS:
	    जइ (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      प्रत्यागम result;
	    जइ (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_वृक्षः;
	      }
	    जइ (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    अण्णहा
	      c_parser_objc_methodproto (parser);
	    प्रत्यागम result;
	    भङ्ग;
	  स्वभाव:
	    भङ्ग;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_AT_INTERFACE:
	  {
	    जइ (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      प्रत्यागम result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    प्रत्यागम result;
	  }
	  भङ्ग;
	पक्ष RID_AT_IMPLEMENTATION:
	  {
	    जइ (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      प्रत्यागम result;
	    जइ (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_वृक्षः;
	      }
	    c_parser_objc_class_definition (parser, NULL_वृक्षः);
	    प्रत्यागम result;
	  }
	  भङ्ग;
	पक्ष RID_AT_PROTOCOL:
	  {
	    जइ (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      प्रत्यागम result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    प्रत्यागम result;
	  }
	  भङ्ग;
	पक्ष RID_AT_ALIAS:
	पक्ष RID_AT_CLASS:
	पक्ष RID_AT_END:
	पक्ष RID_AT_PROPERTY:
	  जइ (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = रिक्त;
	    }
	  भङ्ग;
	स्वभाव:
	  भङ्ग;
	}
    }
  अण्णहा जइ (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  अण्णहा जइ (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_वृक्षः;
  तार्किक more_than_one_decl = मिच्छ;
  जाव (सच्च)
    {
      संरचना c_declarator *declarator;
      तार्किक dummy = मिच्छ;
      timevar_id_t tv;
      वृक्षः fnbody = NULL_वृक्षः;
      वृक्षः underspec_name = NULL_वृक्षः;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      जइ (declarator == रिक्त)
	{
	  जइ (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_वृक्षः, NULL_वृक्षः,
				       omp_declare_simd_clauses);
	  जइ (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_वृक्षः, मिच्छ);
	  /* This check is here purely to improve the diagnostic.  */
	  जइ (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  प्रत्यागम result;
	}
      जइ (flag_openmp || flag_openmp_simd)
	{
	  संरचना c_declarator *d = declarator;
	  जाव (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = रिक्त;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      जइ (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  प्रत्यागम result;
	}
      जइ (std_auto_type_p)
	{
	  संरचना c_declarator *d = declarator;
	  जाव (d->kind == cdk_attrs)
	    d = d->declarator;
	  जइ (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      प्रत्यागम result;
	    }
	  underspec_name = d->u.id.id;
	}
      अण्णहा जइ (specs->constexpr_p)
	{
	  संरचना c_declarator *d = declarator;
	  जाव (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      जइ (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  वृक्षः asm_name = NULL_वृक्षः;
	  वृक्षः postfix_attrs = NULL_वृक्षः;
	  जइ (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = सच्च;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = मिच्छ;
	  जइ (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_व्यञ्जकम् (parser);
	  जइ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  प्रत्यागम result;
		}
	    }
	  जइ (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      वृक्षः d;
	      संरचना c_व्यञ्जकम् init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      जइ (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पङ्क्तिः_table, init_loc);
		  unsigned पूर्णाङ्क underspec_state = 0;
		  जइ (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_वृक्षः, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  जइ (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
		  जइ (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  जइ (gnu_auto_type_p
		      && वृक्षः_CODE (init.मानम्) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (वृक्षः_OPERAND (init.मानम्, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, सच्च, सच्च,
						   सच्च);
		  वृक्षः init_type = वृक्षः_TYPE (init.मानम्);
		  तार्किक vm_type = c_type_variably_modified_p (init_type);
		  जइ (vm_type)
		    init.मानम् = save_व्यञ्जकम् (init.मानम्);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = सच्च;
		  specs->type = init_type;
		  जइ (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_वृक्षः;
		    }
		  जइ (vm_type)
		    {
		      तार्किक maybe_const = सच्च;
		      वृक्षः type_व्यञ्जकम् = c_fully_fold (init.मानम्, मिच्छ,
						     &maybe_const);
		      specs->व्यञ्जकम्_const_operands &= maybe_const;
		      जइ (specs->व्यञ्जकम्)
			specs->व्यञ्जकम् = build2 (COMPOUND_व्यञ्जकम्,
					      वृक्षः_TYPE (type_व्यञ्जकम्),
					      specs->व्यञ्जकम्, type_व्यञ्जकम्);
		      अण्णहा
			specs->व्यञ्जकम् = type_व्यञ्जकम्;
		    }
		  d = start_decl (declarator, specs, सच्च,
				  chainon (postfix_attrs, all_prefix_attrs));
		  जइ (!d)
		    d = error_mark_ग्रन्थिः;
		  जइ (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्षः,
					       omp_declare_simd_clauses);
		  जइ (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्षः,
					       &omp_dsimd_idattr_clauses);
		}
	      अण्णहा
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पङ्क्तिः_table, init_loc);
		  unsigned पूर्णाङ्क underspec_state = 0;
		  जइ (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, सच्च,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  जइ (!d)
		    d = error_mark_ग्रन्थिः;
		  जइ (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्षः,
					       omp_declare_simd_clauses);
		  जइ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्षः,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      वृक्षः_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  जइ (वृक्षः_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  जइ (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      जइ (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_वृक्षः,
						   omp_declare_simd_clauses);
		  जइ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्षः,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      जइ (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, मिच्छ);
	      जइ (d != error_mark_ग्रन्थिः)
		{
		  maybe_warn_string_init (init_loc, वृक्षः_TYPE (d), init);
		  finish_decl (d, init_loc, init.मानम्,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  अण्णहा
	    {
	      जइ (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  प्रत्यागम result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      वृक्षः attrs = chainon (postfix_attrs, all_prefix_attrs);
	      वृक्षः d = start_decl (declarator, specs, मिच्छ, attrs, सच्च,
				   &lastloc);
	      जइ (d && वृक्षः_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ध्रुव संरचना c_declarator *decl = declarator;
		  ध्रुव संरचना c_declarator *last_non_id_attrs = रिक्त;

		  जाव (decl)
		    विकल्प (decl->kind)
		      {
		      पक्ष cdk_array:
		      पक्ष cdk_function:
		      पक्ष cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			भङ्ग;

		      पक्ष cdk_attrs:
			decl = decl->declarator;
			भङ्ग;

		      पक्ष cdk_id:
			decl = 0;
			भङ्ग;

		      स्वभाव:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  जइ (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      वृक्षः parms = last_non_id_attrs->u.arg_info->parms;
		      जइ (DECL_ARGUMENTS (d) == NULL_वृक्षः
			  && DECL_INITIAL (d) == NULL_वृक्षः)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      जइ (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  वृक्षः parms = NULL_वृक्षः;
		  जइ (d && वृक्षः_CODE (d) == FUNCTION_DECL)
		    {
		      संरचना c_declarator *ce = declarator;
		      जाव (ce != रिक्त)
			जइ (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    भङ्ग;
			  }
			अण्णहा
			  ce = ce->declarator;
		    }
		  जइ (parms)
		    temp_store_parm_decls (d, parms);
		  जइ (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  जइ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  जइ (parms)
		    temp_निष्कासय_parm_decls ();
		}
	      जइ (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, मिच्छ);
	      जइ (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_वृक्षः,
			     NULL_वृक्षः, asm_name);

	      जइ (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  जइ (d)
		    *objc_foreach_object_declaration = d;
		  अण्णहा
		    *objc_foreach_object_declaration = error_mark_ग्रन्थिः;
		}
	    }
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = सच्च;
	      जइ (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  प्रत्यागम result;
		}
	      c_parser_consume_token (parser);
	      जइ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      अण्णहा
		all_prefix_attrs = prefix_attrs;
	      अनुवर्त;
	    }
	  अण्णहा जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      जइ (!simple_ok)
		c_parser_consume_token (parser);
	      प्रत्यागम result;
	    }
	  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      प्रत्यागम result;
	    }
	  अण्णहा
	    {
	      जइ (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      अण्णहा जइ (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      प्रत्यागम result;
	    }
	}
      अण्णहा जइ (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  प्रत्यागम result;
	}
      अण्णहा जइ (!fndef_ok)
	{
	  जइ (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  अण्णहा
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  प्रत्यागम result;
	}
      /* Function definition (nested or otherwise).  */
      जइ (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_प्रक्षिप_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      वृक्षः dv_base = NULL_वृक्षः;
      वृक्षः dv_ctx = NULL_वृक्षः;
      जइ (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      जइ (!start_function (specs, declarator, all_prefix_attrs))
	{
	  /* At this point we've consumed:
	       declaration-specifiers declarator
	     and the next token isn't CPP_EQ, CPP_COMMA, CPP_SEMICOLON,
	     RID_ASM, RID_ATTRIBUTE, or RID_IN,
	     but the
	       declaration-specifiers declarator
	     aren't grokkable as a function definition, so we have
	     an error.  */
	  gcc_assert (!c_parser_next_token_is (parser, CPP_SEMICOLON));
	  जइ (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = मिच्छ;
	    }
	  अण्णहा
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  जइ (nested)
	    c_निष्कासय_function_context ();
	  भङ्ग;
	}

      जइ (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      अण्णहा
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
      पूर्णाङ्क save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      जाव (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, मिच्छ, मिच्छ, मिच्छ,
				       सच्च, मिच्छ, मिच्छ);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      जइ (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_वृक्षः,
				   omp_declare_simd_clauses);
      जइ (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_वृक्षः,
				   &omp_dsimd_idattr_clauses);
      जइ (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, सच्च);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      जइ (dv_base && current_function_decl != error_mark_ग्रन्थिः)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_प्रक्षिप (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      जइ (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  प्रक्षिप_scope ();
	  निष्कासय_scope ();

	  finish_function (endloc);
	  प्रत्यागम result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      अण्णहा जइ (specs->declspec_il != cdil_none)
	{
	  तार्किक saved = in_late_द्विमान_op;
	  in_late_द्विमान_op = सच्च;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_गणनम्);
	  in_late_द्विमान_op = saved;
	}
      अण्णहा
	fnbody = c_parser_compound_statement (parser, &endloc);
      वृक्षः fndecl = current_function_decl;
      जइ (nested && specs->declspec_il == cdil_none)
	{
	  वृक्षः decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_निष्कासय_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_व्यञ्जकम्, decl));
	}
      अण्णहा जइ (nested)
	{
	  जइ (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  अण्णहा
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_निष्कासय_function_context ();
	}
      अण्णहा
	{
	  जइ (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      जइ (specs->declspec_il != cdil_none)
	DECL_SAVED_वृक्षः (fndecl) = NULL_वृक्षः;

      भङ्ग;
    }

  प्रत्यागम result;
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

स्थिर शून्य
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  वृक्षः asm_str = NULL_वृक्षः;
  वृक्षः outputs = NULL_वृक्षः, inputs = NULL_वृक्षः;
  जइ (!parens.require_open (parser))
    गच्छ done;
  asm_str = c_parser_asm_string_literal (parser);
  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      गच्छ done;
    }
  प्रति (पूर्णाङ्क section = 0; section < 2; ++section)
    {
      जइ (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  जइ (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      asm_str = NULL_वृक्षः;
	      गच्छ done;
	    }
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, मिच्छ))
	गच्छ error_close_paren;
      जइ (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  जइ (section)
	    inputs = c_parser_asm_operands (parser);
	  अण्णहा
	    outputs = c_parser_asm_operands (parser);
	}
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	भङ्ग;
    }

  जइ (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      asm_str = NULL_वृक्षः;
    }

  जइ (asm_str)
    asm_str = build_asm_व्यञ्जकम् (asm_loc, asm_str, outputs, inputs,
			      NULL_वृक्षः, NULL_वृक्षः, मिच्छ, मिच्छ);
done:
  जइ (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

स्थिर शून्य
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  जइ (parser->error
      || !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);
}

/* Parse a static assertion (C11 6.7.10), without the trailing
   semicolon.

   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression , string-literal )

   C23:
   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression )
*/

स्थिर शून्य
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, मानम्_loc;
  वृक्षः मानम्;
  वृक्षः string = NULL_वृक्षः;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  वृक्षः spelling = c_parser_peek_token (parser)->मानम्;
  assert_loc = c_parser_peek_token (parser)->location;
  जइ (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  अण्णहा
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम;
  location_t मानम्_tok_loc = c_parser_peek_token (parser)->location;
  मानम् = convert_lvalue_to_rvalue (मानम्_tok_loc,
				    c_parser_व्यञ्जकम्_no_commas (parser, रिक्त),
				    सच्च, सच्च).मानम्;
  मानम्_loc = व्यञ्जकम्_LOC_OR_LOC (मानम्, मानम्_tok_loc);
  जइ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_STRING:
	पक्ष CPP_STRING16:
	पक्ष CPP_STRING32:
	पक्ष CPP_WSTRING:
	पक्ष CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, मिच्छ, सच्च).मानम्;
	  भङ्ग;
	स्वभाव:
	  c_parser_error (parser, "expected string literal");
	  प्रत्यागम;
	}
    }
  अण्णहा जइ (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (मानम्)))
    {
      error_at (मानम्_loc, "expression in static assertion is not an integer");
      प्रत्यागम;
    }
  जइ (वृक्षः_CODE (मानम्) != INTEGER_CST)
    {
      मानम् = c_fully_fold (मानम्, मिच्छ, रिक्त);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (मानम्);
      जइ (वृक्षः_CODE (मानम्) == INTEGER_CST)
	pedwarn (मानम्_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  जइ (वृक्षः_CODE (मानम्) != INTEGER_CST)
    {
      error_at (मानम्_loc, "expression in static assertion is not constant");
      प्रत्यागम;
    }
  constant_expression_warning (मानम्);
  जइ (integer_zerop (मानम्))
    {
      जइ (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      अण्णहा
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
     register
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

शून्य
c_parser_declspecs (c_parser *parser, संरचना c_declspecs *specs,
		    तार्किक scspec_ok, तार्किक typespec_ok, तार्किक start_attr_ok,
		    तार्किक alignspec_ok, तार्किक auto_type_ok,
		    तार्किक start_std_attr_ok, तार्किक end_std_attr_ok,
		    गणना c_lookahead_kind la)
{
  तार्किक attrs_ok = start_attr_ok;
  तार्किक seen_type = specs->typespec_kind != ctsk_none;

  जइ (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  जइ (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      वृक्षः attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = मिच्छ;
    }

  जाव (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      संरचना c_typespec t;
      वृक्षः attrs;
      वृक्षः align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      जइ ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	भङ्ग;

      जइ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  वृक्षः मानम् = name_token->मानम्;
	  c_id_kind kind = name_token->id_kind;

	  जइ (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = सच्च;
	      अनुवर्त;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  जइ (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    भङ्ग;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = सच्च;
	  attrs_ok = सच्च;
	  जइ (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (मानम्, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      जइ (ध्रुव वर्ण *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    मानम्, suggestion);
		}
	      अण्णहा
		error_at (loc, "unknown type name %qE", मानम्);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_ग्रन्थिः;
	    }
	  अण्णहा जइ (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (मानम्);
	    }
	  अण्णहा
	    {
	      वृक्षः proto = NULL_वृक्षः;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      जइ (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (मानम्, proto);
	    }
	  t.व्यञ्जकम् = NULL_वृक्षः;
	  t.व्यञ्जकम्_const_operands = सच्च;
	  t.has_enum_type_specifier = मिच्छ;
	  declspecs_add_type (name_token->location, specs, t);
	  अनुवर्त;
	}
      जइ (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  वृक्षः proto;
	  gcc_assert (c_dialect_objc ());
	  जइ (!typespec_ok || seen_type)
	    भङ्ग;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_वृक्षः, proto);
	  t.व्यञ्जकम् = NULL_वृक्षः;
	  t.व्यञ्जकम्_const_operands = सच्च;
	  t.has_enum_type_specifier = मिच्छ;
	  declspecs_add_type (loc, specs, t);
	  अनुवर्त;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_STATIC:
	पक्ष RID_EXTERN:
	पक्ष RID_REGISTER:
	पक्ष RID_TYPEDEF:
	पक्ष RID_INLINE:
	पक्ष RID_NORETURN:
	पक्ष RID_AUTO:
	पक्ष RID_THREAD:
	पक्ष RID_CONSTEXPR:
	  जइ (!scspec_ok)
	    गच्छ out;
	  attrs_ok = सच्च;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->मानम्);
	  c_parser_consume_token (parser);
	  भङ्ग;
	पक्ष RID_AUTO_TYPE:
	  जइ (!auto_type_ok)
	    गच्छ out;
	  /* Fall through.  */
	पक्ष RID_UNSIGNED:
	पक्ष RID_LONG:
	पक्ष RID_SHORT:
	पक्ष RID_SIGNED:
	पक्ष RID_COMPLEX:
	पक्ष RID_INT:
	पक्ष RID_CHAR:
	पक्ष RID_FLOAT:
	पक्ष RID_DOUBLE:
	पक्ष RID_VOID:
	पक्ष RID_DFLOAT32:
	पक्ष RID_DFLOAT64:
	पक्ष RID_DFLOAT128:
	पक्ष RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	पक्ष RID_BOOL:
	पक्ष RID_FRACT:
	पक्ष RID_ACCUM:
	पक्ष RID_SAT:
	पक्ष RID_INT_N_0:
	पक्ष RID_INT_N_1:
	पक्ष RID_INT_N_2:
	पक्ष RID_INT_N_3:
	  जइ (!typespec_ok)
	    गच्छ out;
	  attrs_ok = सच्च;
	  seen_type = सच्च;
	  जइ (c_dialect_objc ())
	    parser->objc_need_raw_identifier = सच्च;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->मानम्;
	  t.व्यञ्जकम् = NULL_वृक्षः;
	  t.व्यञ्जकम्_const_operands = सच्च;
	  t.has_enum_type_specifier = मिच्छ;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  भङ्ग;
	पक्ष RID_ENUM:
	  जइ (!typespec_ok)
	    गच्छ out;
	  attrs_ok = सच्च;
	  seen_type = सच्च;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  भङ्ग;
	पक्ष RID_STRUCT:
	पक्ष RID_UNION:
	  जइ (!typespec_ok)
	    गच्छ out;
	  attrs_ok = सच्च;
	  seen_type = सच्च;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  भङ्ग;
	पक्ष RID_TYPEOF:
	पक्ष RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  जइ (!typespec_ok || seen_type)
	    गच्छ out;
	  attrs_ok = सच्च;
	  seen_type = सच्च;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  भङ्ग;
	पक्ष RID_BITINT:
	  जइ (!typespec_ok)
	    गच्छ out;
	  अण्णहा
	    {
	      attrs_ok = सच्च;
	      seen_type = सच्च;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->मानम्;
	      t.व्यञ्जकम् = error_mark_ग्रन्थिः;
	      t.व्यञ्जकम्_const_operands = सच्च;
	      t.has_enum_type_specifier = मिच्छ;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      जइ (parens.require_open (parser))
		{
		  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
		  t.व्यञ्जकम् = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, सच्च,
						     सच्च).मानम्;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  भङ्ग;
	पक्ष RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  जइ (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  जइ (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  अण्णहा
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = सच्च;
	  वृक्षः मानम्;
	  मानम् = c_parser_peek_token (parser)->मानम्;
	  c_parser_consume_token (parser);
	  जइ (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = सच्च;
	      c_parser_consume_token (parser);
	      संरचना c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_ग्रन्थिः;
	      t.व्यञ्जकम् = NULL_वृक्षः;
	      t.व्यञ्जकम्_const_operands = सच्च;
	      t.has_enum_type_specifier = मिच्छ;
	      जइ (type != रिक्त)
		t.spec = groktypename (type, &t.व्यञ्जकम्,
				       &t.व्यञ्जकम्_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      जइ (t.spec != error_mark_ग्रन्थिः)
		{
		  जइ (वृक्षः_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  अण्णहा जइ (वृक्षः_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  अण्णहा जइ (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  अण्णहा
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  अण्णहा
	    declspecs_add_qual (loc, specs, मानम्);
	  भङ्ग;
	पक्ष RID_CONST:
	पक्ष RID_VOLATILE:
	पक्ष RID_RESTRICT:
	  attrs_ok = सच्च;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->मानम्);
	  c_parser_consume_token (parser);
	  भङ्ग;
	पक्ष RID_ATTRIBUTE:
	  जइ (!attrs_ok)
	    गच्छ out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  भङ्ग;
	पक्ष RID_ALIGNAS:
	  जइ (!alignspec_ok)
	    गच्छ out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  भङ्ग;
	पक्ष RID_GIMPLE:
	  जइ (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  भङ्ग;
	पक्ष RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  भङ्ग;
	स्वभाव:
	  गच्छ out;
	}
    }
 out:
  जइ (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

स्थिर शून्य
report_bad_enum_name (c_parser *parser)
{
  जइ (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      विकल्प (token->type)
	{
	स्वभाव:
	  भङ्ग;
	पक्ष CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = सच्च;
	  प्रत्यागम;
	पक्ष CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  जइ (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->मानम्));
	      add_note_about_new_keyword (token->location,
					  token->मानम्);
	      parser->error = सच्च;
	      प्रत्यागम;
	    }
	  भङ्ग;
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

स्थिर संरचना c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  संरचना c_typespec ret;
  तार्किक have_std_attrs;
  तार्किक potential_nesting_p = मिच्छ;
  वृक्षः std_attrs = NULL_वृक्षः;
  वृक्षः attrs;
  वृक्षः ident = NULL_वृक्षः;
  वृक्षः fixed_underlying_type = NULL_वृक्षः;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  जइ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->मानम्;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  जइ (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      जइ (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, सच्च);
	  जइ (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_वृक्षः == TYPE_मानानि (ret.spec);
	}
      अण्णहा
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_वृक्षः;
	  ret.kind = ctsk_tagdef;
	  ret.व्यञ्जकम् = NULL_वृक्षः;
	  ret.व्यञ्जकम्_const_operands = सच्च;
	  ret.has_enum_type_specifier = सच्च;
	}
      c_parser_consume_token (parser);
      संरचना c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, मिच्छ, सच्च, मिच्छ, मिच्छ, मिच्छ,
			  मिच्छ, सच्च, cla_prefer_id);
      finish_declspecs (specs);
      जइ (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      अण्णहा जइ (वृक्षः_CODE (specs->type) != INTEGER_TYPE
	       && वृक्षः_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || वृक्षः_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_ग्रन्थिः;
	}
      अण्णहा जइ (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      जइ (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  जइ (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_वृक्षः)
	    {
	      TYPE_MIN_मानम् (ret.spec) =
		TYPE_MIN_मानम् (fixed_underlying_type);
	      TYPE_MAX_मानम् (ret.spec) =
		TYPE_MAX_मानम् (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_वृक्षः;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  अण्णहा जइ (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      संरचना c_enum_contents the_enum;
      वृक्षः type;
      वृक्षः postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      वृक्षः मानानि;
      timevar_प्रक्षिप (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      मानानि = NULL_वृक्षः;
      c_parser_consume_token (parser);
      जाव (सच्च)
	{
	  वृक्षः enum_id;
	  वृक्षः enum_मानम्;
	  वृक्षः enum_decl;
	  तार्किक seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, मानम्_loc;
	  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	      मानानि = error_mark_ग्रन्थिः;
	      भङ्ग;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->मानम्;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = मानम्_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  वृक्षः std_attrs = NULL_वृक्षः;
	  जइ (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  वृक्षः enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  जइ (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      मानम्_loc = c_parser_peek_token (parser)->location;
	      enum_मानम् = convert_lvalue_to_rvalue (मानम्_loc,
						     (c_parser_व्यञ्जकम्_no_commas
						      (parser, रिक्त)),
						     सच्च, सच्च).मानम्;
	    }
	  अण्णहा
	    enum_मानम् = NULL_वृक्षः;
	  enum_decl = build_enumerator (decl_loc, मानम्_loc,
					&the_enum, enum_id, enum_मानम्);
	  जइ (enum_attrs)
	    decl_attributes (&वृक्षः_PURPOSE (enum_decl), enum_attrs, 0);
	  वृक्षः_CHAIN (enum_decl) = मानानि;
	  मानानि = enum_decl;
	  seen_comma = मिच्छ;
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = सच्च;
	      c_parser_consume_token (parser);
	    }
	  जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      जइ (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      भङ्ग;
	    }
	  जइ (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	      मानानि = error_mark_ग्रन्थिः;
	      भङ्ग;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (मानानि),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.व्यञ्जकम् = NULL_वृक्षः;
      ret.व्यञ्जकम्_const_operands = सच्च;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_वृक्षः;
      timevar_निष्कासय (TV_PARSE_ENUM);
      प्रत्यागम ret;
    }
  अण्णहा जइ (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ग्रन्थिः;
      ret.kind = ctsk_tagref;
      ret.व्यञ्जकम् = NULL_वृक्षः;
      ret.व्यञ्जकम्_const_operands = सच्च;
      ret.has_enum_type_specifier = मिच्छ;
      प्रत्यागम ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  जइ (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  जइ (fixed_underlying_type == NULL_वृक्षः)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, मिच्छ);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      जइ (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  प्रत्यागम ret;
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
     empty
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

स्थिर संरचना c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  संरचना c_typespec ret;
  तार्किक have_std_attrs;
  वृक्षः std_attrs = NULL_वृक्षः;
  वृक्षः attrs;
  वृक्षः ident = NULL_वृक्षः;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  गणना वृक्षः_code code;
  विकल्प (c_parser_peek_token (parser)->keyword)
    {
    पक्ष RID_STRUCT:
      code = RECORD_TYPE;
      भङ्ग;
    पक्ष RID_UNION:
      code = UNION_TYPE;
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  जइ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->मानम्;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      वर्ग c_struct_parse_info *struct_info;
      वृक्षः type = start_struct (struct_loc, code, ident, &struct_info);
      वृक्षः postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      वृक्षः contents;
      वृक्षः व्यञ्जकम् = रिक्त;
      timevar_प्रक्षिप (TV_PARSE_STRUCT);
      contents = NULL_वृक्षः;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      जइ (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  वृक्षः name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  जइ (!parens.require_open (parser))
	    गच्छ end_at_defs;
	  जइ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->मानम्;
	      c_parser_consume_token (parser);
	    }
	  अण्णहा
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      गच्छ end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      जाव (सच्च)
	{
	  वृक्षः decls;
	  /* Parse any stray semicolon.  */
	  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      अनुवर्त;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      भङ्ग;
	    }
	  /* Accept #pragmas at struct scope.  */
	  जइ (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, रिक्त, NULL_वृक्षः);
	      अनुवर्त;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &व्यञ्जकम्);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  अण्णहा
	    {
	      जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      अण्णहा जइ (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
		  भङ्ग;
		}

	      /* If we come here, we have already emitted an error
		 for an expected `;', identifier or `(', and we also
	         recovered already.  Go on with the next field. */
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_struct (struct_loc, type, nreverse (contents),
				chainon (std_attrs,
					 chainon (attrs, postfix_attrs)),
				struct_info, &व्यञ्जकम्);
      ret.kind = ctsk_tagdef;
      ret.व्यञ्जकम् = व्यञ्जकम्;
      ret.व्यञ्जकम्_const_operands = सच्च;
      ret.has_enum_type_specifier = मिच्छ;
      timevar_निष्कासय (TV_PARSE_STRUCT);
      प्रत्यागम ret;
    }
  अण्णहा जइ (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ग्रन्थिः;
      ret.kind = ctsk_tagref;
      ret.व्यञ्जकम् = NULL_वृक्षः;
      ret.व्यञ्जकम्_const_operands = सच्च;
      ret.has_enum_type_specifier = मिच्छ;
      प्रत्यागम ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  जइ (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 मिच्छ);
  प्रत्यागम ret;
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

स्थिर वृक्षः
c_parser_struct_declaration (c_parser *parser, वृक्षः *व्यञ्जकम्)
{
  संरचना c_declspecs *specs;
  वृक्षः prefix_attrs;
  वृक्षः all_prefix_attrs;
  वृक्षः decls;
  location_t decl_loc;
  जइ (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      पूर्णाङ्क ext;
      वृक्षः decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, व्यञ्जकम्);
      restore_extension_diagnostics (ext);
      प्रत्यागम decl;
    }
  जइ (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      प्रत्यागम NULL_वृक्षः;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, मिच्छ, सच्च, सच्च,
		      सच्च, मिच्छ, सच्च, सच्च, cla_nonabstract_decl);
  जइ (parser->error)
    प्रत्यागम NULL_वृक्षः;
  जइ (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      प्रत्यागम NULL_वृक्षः;
    }
  finish_declspecs (specs);
  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      वृक्षः ret;
      जइ (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_वृक्षः;
	}
      अण्णहा
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  वृक्षः attrs = रिक्त;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_वृक्षः), specs,
			   NULL_वृक्षः, &attrs, व्यञ्जकम्);
	  जइ (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      प्रत्यागम ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  जइ (specs->typespec_kind == ctsk_tagdef
      && वृक्षः_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = मिच्छ;
      प्रत्यागम NULL_वृक्षः;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_वृक्षः;
  decls = NULL_वृक्षः;
  जाव (सच्च)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      संरचना c_declarator *declarator;
      तार्किक dummy = मिच्छ;
      जइ (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_वृक्षः);
      अण्णहा
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      जइ (declarator == रिक्त)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  भङ्ग;
	}
      जइ (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  वृक्षः postfix_attrs = NULL_वृक्षः;
	  वृक्षः width = NULL_वृक्षः;
	  वृक्षः d;
	  जइ (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_व्यञ्जकम्_no_commas
						 (parser, रिक्त)),
						सच्च, सच्च).मानम्;
	    }
	  जइ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, व्यञ्जकम्);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  जइ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  अण्णहा
	    all_prefix_attrs = prefix_attrs;
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अण्णहा जइ (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      भङ्ग;
	    }
	  अण्णहा
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      भङ्ग;
	    }
	}
      अण्णहा
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  भङ्ग;
	}
    }
  प्रत्यागम decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

स्थिर संरचना c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  तार्किक is_unqual;
  तार्किक is_std;
  संरचना c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_ग्रन्थिः;
  ret.व्यञ्जकम् = NULL_वृक्षः;
  ret.व्यञ्जकम्_const_operands = सच्च;
  ret.has_enum_type_specifier = मिच्छ;
  जइ (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = मिच्छ;
      वृक्षः spelling = c_parser_peek_token (parser)->मानम्;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  अण्णहा
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = सच्च;
      वृक्षः spelling = c_parser_peek_token (parser)->मानम्;
      is_std = strcmp (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  जइ (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      प्रत्यागम ret;
    }
  जइ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      संरचना c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      जइ (type != रिक्त)
	{
	  ret.spec = groktypename (type, &ret.व्यञ्जकम्, &ret.व्यञ्जकम्_const_operands);
	  निष्कासय_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  अण्णहा
    {
      तार्किक was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      संरचना c_व्यञ्जकम् व्यञ्जकम् = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्षः_OPERAND (व्यञ्जकम्.मानम्, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (व्यञ्जकम्.मानम्);
      ret.spec = वृक्षः_TYPE (व्यञ्जकम्.मानम्);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      जइ (was_vm)
	ret.व्यञ्जकम् = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, &ret.व्यञ्जकम्_const_operands);
      निष्कासय_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  जइ (ret.spec != error_mark_ग्रन्थिः)
    {
      जइ (is_unqual)
	{
	  तार्किक is_array = वृक्षः_CODE (ret.spec) == ARRAY_TYPE;
	  पूर्णाङ्क quals = TYPE_QUALS (strip_array_types (ret.spec));
	  जइ ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      जइ (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      जइ (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  जइ (वृक्षः_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  अण्णहा जइ (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (वृक्षः_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (वृक्षः_TYPE (ret.spec)));
	}
    }
  प्रत्यागम ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

स्थिर वृक्षः
c_parser_alignas_specifier (c_parser * parser)
{
  वृक्षः ret = error_mark_ग्रन्थिः;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  वृक्षः spelling = c_parser_peek_token (parser)->मानम्;
  c_parser_consume_token (parser);
  जइ (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  अण्णहा
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम ret;
  जइ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      संरचना c_type_name *type = c_parser_type_name (parser);
      जइ (type != रिक्त)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, रिक्त, रिक्त),
					मिच्छ, सच्च, 1);
    }
  अण्णहा
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_व्यञ्जकम्_no_commas (parser, रिक्त),
				    सच्च, सच्च).मानम्;
  parens.skip_until_found_close (parser);
  प्रत्यागम ret;
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
     pointer
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

संरचना c_declarator *
c_parser_declarator (c_parser *parser, तार्किक type_seen_p, c_dtr_syn kind,
		     तार्किक *seen_id)
{
  /* Parse any initial pointer part.  */
  जइ (c_parser_next_token_is (parser, CPP_MULT))
    {
      संरचना c_declspecs *quals_attrs = build_null_declspecs ();
      संरचना c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, मिच्छ, मिच्छ, सच्च,
			  मिच्छ, मिच्छ, सच्च, मिच्छ, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      जइ (inner == रिक्त)
	प्रत्यागम रिक्त;
      अण्णहा
	प्रत्यागम make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  प्रत्यागम c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

स्थिर संरचना c_declarator *
c_parser_direct_declarator (c_parser *parser, तार्किक type_seen_p, c_dtr_syn kind,
			    तार्किक *seen_id)
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

  जइ (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      संरचना c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->मानम्);
      *seen_id = सच्च;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      जइ (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      प्रत्यागम c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  जइ (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      संरचना c_declarator *inner = build_id_declarator (NULL_वृक्षः);
      inner->id_loc = c_parser_peek_token (parser)->location;
      प्रत्यागम c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      वृक्षः attrs;
      संरचना c_declarator *inner;
      c_parser_consume_token (parser);
      तार्किक have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      जइ (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  संरचना c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  जइ (args == रिक्त)
	    प्रत्यागम रिक्त;
	  अण्णहा
	    {
	      inner = build_id_declarator (NULL_वृक्षः);
	      जइ (!(args->types
		    && args->types != error_mark_ग्रन्थिः
		    && वृक्षः_CODE (वृक्षः_मानम् (args->types)) == IDENTIFIER_ग्रन्थिः)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  वृक्षः std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  जइ (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      प्रत्यागम c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      जइ (inner != रिक्त && attrs != रिक्त)
	inner = build_attrs_declarator (attrs, inner);
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  जइ (inner == रिक्त)
	    प्रत्यागम रिक्त;
	  अण्णहा
	    प्रत्यागम c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      अण्णहा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  प्रत्यागम रिक्त;
	}
    }
  अण्णहा
    {
      जइ (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  प्रत्यागम रिक्त;
	}
      अण्णहा
	प्रत्यागम build_id_declarator (NULL_वृक्षः);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

स्थिर संरचना c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, तार्किक id_present,
				  संरचना c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  जइ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      संरचना c_declarator *declarator;
      संरचना c_declspecs *quals_attrs = build_null_declspecs ();
      संरचना c_व्यञ्जकम् dimen;
      dimen.मानम् = NULL_वृक्षः;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_वृक्षः;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, मिच्छ, मिच्छ, सच्च,
			  मिच्छ, मिच्छ, मिच्छ, मिच्छ, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      जइ (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  जइ (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, मिच्छ, मिच्छ, सच्च,
				मिच्छ, मिच्छ, मिच्छ, मिच्छ, cla_prefer_id);
	}
      जइ (!quals_attrs->declspecs_seen_p)
	quals_attrs = रिक्त;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ध्रुव तार्किक static_seen = (static_loc != UNKNOWN_LOCATION);
      तार्किक star_seen = मिच्छ;
      जइ (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = सच्च;
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);

      जइ (static_seen)
	{
	  जइ (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = मिच्छ;
	      dimen.मानम् = error_mark_ग्रन्थिः;
	    }
	  अण्णहा जइ (!dimen.मानम्)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      जइ (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      अण्णहा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  प्रत्यागम रिक्त;
	}
      जइ (dimen.मानम्)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, सच्च, सच्च);
      declarator = build_array_declarator (brace_loc, dimen.मानम्, quals_attrs,
					   static_seen, star_seen);
      जइ (declarator == रिक्त)
	प्रत्यागम रिक्त;
      जइ (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  वृक्षः std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  जइ (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      प्रत्यागम c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  अण्णहा जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      वृक्षः attrs;
      संरचना c_arg_info *args;
      c_parser_consume_token (parser);
      तार्किक have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      जइ (args == रिक्त)
	प्रत्यागम रिक्त;
      अण्णहा
	{
	  जइ (!(args->types
		&& args->types != error_mark_ग्रन्थिः
		&& वृक्षः_CODE (वृक्षः_मानम् (args->types)) == IDENTIFIER_ग्रन्थिः)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      वृक्षः std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      जइ (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  प्रत्यागम c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  प्रत्यागम inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

स्थिर संरचना c_arg_info *
c_parser_parms_declarator (c_parser *parser, तार्किक id_list_ok, वृक्षः attrs,
			   तार्किक have_gnu_attrs)
{
  प्रक्षिप_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  जइ (id_list_ok
      && !attrs
      && c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_token (parser)->id_kind == C_ID_ID

      /* Look ahead to detect typos in type names.  */
      && c_parser_peek_2nd_token (parser)->type != CPP_NAME
      && c_parser_peek_2nd_token (parser)->type != CPP_MULT
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_SQUARE
      && c_parser_peek_2nd_token (parser)->type != CPP_KEYWORD)
    {
      वृक्षः list = NULL_वृक्षः, *nextp = &list;
      जाव (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_वृक्षः_list (NULL_वृक्षः,
				    c_parser_peek_token (parser)->मानम्);
	  nextp = & वृक्षः_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is_not (parser, CPP_COMMA))
	    भङ्ग;
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      भङ्ग;
	    }
	}
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  संरचना c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  निष्कासय_scope ();
	  प्रत्यागम ret;
	}
      अण्णहा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  निष्कासय_scope ();
	  प्रत्यागम रिक्त;
	}
    }
  अण्णहा
    {
      संरचना c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, रिक्त, have_gnu_attrs);
      निष्कासय_scope ();
      प्रत्यागम ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

स्थिर संरचना c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, वृक्षः attrs, वृक्षः व्यञ्जकम्,
				तार्किक have_gnu_attrs)
{
  तार्किक bad_parm = मिच्छ;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      संरचना c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      प्रत्यागम ret;
    }
  जइ (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      संरचना c_arg_info *ret = build_arg_info ();

      ret->types = NULL_वृक्षः;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = सच्च;
	  c_parser_consume_token (parser);
	  प्रत्यागम ret;
	}
      अण्णहा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  प्रत्यागम रिक्त;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  जाव (सच्च)
    {
      /* Parse a parameter.  */
      संरचना c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_वृक्षः;
      have_gnu_attrs = मिच्छ;
      जइ (parm == रिक्त)
	bad_parm = सच्च;
      अण्णहा
	प्रक्षिप_parm_decl (parm, &व्यञ्जकम्);
      जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  वृक्षः new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  तार्किक new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  प्रत्यागम c_parser_parms_list_declarator (parser, new_attrs, व्यञ्जकम्,
						 new_have_gnu_attrs);
	}
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  जइ (bad_parm)
	    प्रत्यागम रिक्त;
	  अण्णहा
	    प्रत्यागम get_parm_info (मिच्छ, व्यञ्जकम्);
	}
      जइ (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, मिच्छ))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  प्रत्यागम रिक्त;
	}
      जइ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      जइ (bad_parm)
		प्रत्यागम रिक्त;
	      अण्णहा
		प्रत्यागम get_parm_info (सच्च, व्यञ्जकम्);
	    }
	  अण्णहा
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      प्रत्यागम रिक्त;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

स्थिर संरचना c_parm *
c_parser_parameter_declaration (c_parser *parser, वृक्षः attrs,
				तार्किक have_gnu_attrs)
{
  संरचना c_declspecs *specs;
  संरचना c_declarator *declarator;
  वृक्षः prefix_attrs;
  वृक्षः postfix_attrs = NULL_वृक्षः;
  तार्किक dummy = मिच्छ;

  /* Accept #pragmas between parameter declarations.  */
  जाव (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, रिक्त, NULL_वृक्षः);

  जइ (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      जइ (parser->error)
	प्रत्यागम रिक्त;
      c_parser_set_source_position_from_token (token);
      जइ (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->मानम्,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  जइ (ध्रुव वर्ण *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->मानम्, suggestion);
	    }
	  अण्णहा
	    error_at (token->location, "unknown type name %qE", token->मानम्);
	  parser->error = सच्च;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      अण्णहा
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      प्रत्यागम रिक्त;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  जइ (attrs)
    {
      declspecs_add_attrs (निवेशः_location, specs, attrs);
      attrs = NULL_वृक्षः;
    }
  c_parser_declspecs (parser, specs, सच्च, सच्च, सच्च, सच्च, मिच्छ,
		      !have_gnu_attrs, सच्च, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  जइ (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_शिखरम्_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_वृक्षः;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  जइ (declarator == रिक्त)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, रिक्त);
      प्रत्यागम रिक्त;
    }
  जइ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    postfix_attrs = c_parser_gnu_attributes (parser);

  /* Generate a location for the parameter, ranging from the start of the
     initial token to the end of the final token.

     If we have a identifier, then use it for the caret location, e.g.

       extern int callee (int one, int (*two)(int, int), float three);
                                   ~~~~~~^~~~~~~~~~~~~~

     otherwise, reuse the start location for the caret location e.g.:

       extern int callee (int one, int (*)(int, int), float three);
                                   ^~~~~~~~~~~~~~~~~
  */
  location_t end_loc = parser->last_token_location;

  /* Find any cdk_id declarator; determine if we have an identifier.  */
  c_declarator *id_declarator = declarator;
  जाव (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  प्रत्यागम build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

स्थिर वृक्षः
c_parser_asm_string_literal (c_parser *parser)
{
  वृक्षः str;
  पूर्णाङ्क save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, मिच्छ, मिच्छ).मानम्;
  warn_overlength_strings = save_flag;
  प्रत्यागम str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

स्थिर वृक्षः
c_parser_simple_asm_व्यञ्जकम् (c_parser *parser)
{
  वृक्षः str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम NULL_वृक्षः;
  str = c_parser_asm_string_literal (parser);
  जइ (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      प्रत्यागम NULL_वृक्षः;
    }
  प्रत्यागम str;
}

स्थिर वृक्षः
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  वृक्षः attr_name = NULL_वृक्षः;

  जइ (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      तार्किक ok;
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_STATIC:
	पक्ष RID_UNSIGNED:
	पक्ष RID_LONG:
	पक्ष RID_CONST:
	पक्ष RID_EXTERN:
	पक्ष RID_REGISTER:
	पक्ष RID_TYPEDEF:
	पक्ष RID_SHORT:
	पक्ष RID_INLINE:
	पक्ष RID_NORETURN:
	पक्ष RID_VOLATILE:
	पक्ष RID_SIGNED:
	पक्ष RID_AUTO:
	पक्ष RID_RESTRICT:
	पक्ष RID_COMPLEX:
	पक्ष RID_THREAD:
	पक्ष RID_INT:
	पक्ष RID_CHAR:
	पक्ष RID_FLOAT:
	पक्ष RID_DOUBLE:
	पक्ष RID_VOID:
	पक्ष RID_DFLOAT32:
	पक्ष RID_DFLOAT64:
	पक्ष RID_DFLOAT128:
	पक्ष RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	पक्ष RID_BOOL:
	पक्ष RID_BITINT:
	पक्ष RID_FRACT:
	पक्ष RID_ACCUM:
	पक्ष RID_SAT:
	पक्ष RID_TRANSACTION_ATOMIC:
	पक्ष RID_TRANSACTION_CANCEL:
	पक्ष RID_ATOMIC:
	पक्ष RID_AUTO_TYPE:
	पक्ष RID_CONSTEXPR:
	पक्ष RID_INT_N_0:
	पक्ष RID_INT_N_1:
	पक्ष RID_INT_N_2:
	पक्ष RID_INT_N_3:
	  ok = सच्च;
	  भङ्ग;
	स्वभाव:
	  ok = मिच्छ;
	  भङ्ग;
	}
      जइ (!ok)
	प्रत्यागम NULL_वृक्षः;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(पूर्णाङ्क) c_parser_peek_token (parser)->keyword];
    }
  अण्णहा जइ (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->मानम्;

  प्रत्यागम attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

स्थिर वृक्षः
c_parser_attribute_arguments (c_parser *parser, तार्किक takes_identifier,
			      तार्किक require_string, तार्किक assume_attr,
			      तार्किक allow_empty_args)
{
  vec<वृक्षः, va_gc> *व्यञ्जकम्_list;
  वृक्षः attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  जइ (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_token (parser)->id_kind == C_ID_ID
	  || (c_dialect_objc ()
	      && c_parser_peek_token (parser)->id_kind
	      == C_ID_CLASSNAME))
      && ((c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	  || (c_parser_peek_2nd_token (parser)->type
	      == CPP_CLOSE_PAREN))
      && (takes_identifier
	  || (c_dialect_objc ()
	      && !assume_attr
	      && c_parser_peek_token (parser)->id_kind
	      == C_ID_CLASSNAME)))
    {
      वृक्षः arg1 = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_वृक्षः_list (NULL_वृक्षः, arg1);
      अण्णहा
	{
	  वृक्षः वृक्षः_list;
	  c_parser_consume_token (parser);
	  व्यञ्जकम्_list = c_parser_व्यञ्जकम्_list (parser, मिच्छ, सच्च,
					  रिक्त, रिक्त, रिक्त, रिक्त);
	  वृक्षः_list = build_वृक्षः_list_vec (व्यञ्जकम्_list);
	  attr_args = वृक्षः_cons (NULL_वृक्षः, arg1, वृक्षः_list);
	  release_वृक्षः_vector (व्यञ्जकम्_list);
	}
    }
  अण्णहा
    {
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  जइ (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_वृक्षः;
	}
      अण्णहा जइ (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  वृक्षः string = c_parser_string_literal (parser, मिच्छ, सच्च).मानम्;
	  attr_args = build_वृक्षः_list (NULL_वृक्षः, string);
	}
      अण्णहा जइ (assume_attr)
	{
	  वृक्षः cond
	    = c_parser_conditional_expression (parser, रिक्त, NULL_वृक्षः).मानम्;
	  जइ (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_args = build_वृक्षः_list (NULL_वृक्षः, cond);
	  अण्णहा
	    {
	      वृक्षः वृक्षः_list;
	      c_parser_consume_token (parser);
	      व्यञ्जकम्_list = c_parser_व्यञ्जकम्_list (parser, मिच्छ, सच्च,
					      रिक्त, रिक्त, रिक्त, रिक्त);
	      वृक्षः_list = build_वृक्षः_list_vec (व्यञ्जकम्_list);
	      attr_args = वृक्षः_cons (NULL_वृक्षः, cond, वृक्षः_list);
	      release_वृक्षः_vector (व्यञ्जकम्_list);
	    }
	}
      अण्णहा
	{
	  व्यञ्जकम्_list = c_parser_व्यञ्जकम्_list (parser, मिच्छ, सच्च,
					  रिक्त, रिक्त, रिक्त, रिक्त);
	  attr_args = build_वृक्षः_list_vec (व्यञ्जकम्_list);
	  release_वृक्षः_vector (व्यञ्जकम्_list);
	}
    }
  प्रत्यागम attr_args;
}

/* Parse (possibly empty) gnu-attributes.  This is a GNU extension.

   gnu-attributes:
     empty
     gnu-attributes gnu-attribute

   gnu-attribute:
     __attribute__ ( ( gnu-attribute-list ) )

   gnu-attribute-list:
     gnu-attrib
     gnu-attribute_list , gnu-attrib

   gnu-attrib:
     empty
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

स्थिर वृक्षः
c_parser_gnu_attribute (c_parser *parser, वृक्षः attrs,
			तार्किक expect_comma = मिच्छ, तार्किक empty_ok = सच्च)
{
  तार्किक comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  जइ (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    प्रत्यागम NULL_वृक्षः;

  जाव (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      जइ (!empty_ok)
	प्रत्यागम attrs;
    }

  वृक्षः attr_name = c_parser_gnu_attribute_any_word (parser);
  जइ (attr_name == NULL_वृक्षः)
    प्रत्यागम NULL_वृक्षः;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  वृक्षः attr;
  जइ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      जइ (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  प्रत्यागम error_mark_ग्रन्थिः;
	}
      attr = build_वृक्षः_list (attr_name, NULL_वृक्षः);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      प्रत्यागम attrs;
    }
  c_parser_consume_token (parser);

  वृक्षः attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    मिच्छ,
				    is_attribute_p ("assume", attr_name),
				    सच्च);

  attr = build_वृक्षः_list (attr_name, attr_args);
  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  अण्णहा
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      प्रत्यागम error_mark_ग्रन्थिः;
    }

  जइ (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      प्रत्यागम error_mark_ग्रन्थिः;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  प्रत्यागम attrs;
}

स्थिर वृक्षः
c_parser_gnu_attributes (c_parser *parser)
{
  वृक्षः attrs = NULL_वृक्षः;
  जाव (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      तार्किक save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = मिच्छ;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  प्रत्यागम attrs;
	}
      जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  प्रत्यागम attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      प्रति (तार्किक expect_comma = मिच्छ; ; expect_comma = सच्च)
	{
	  /* Parse a single attribute.  */
	  वृक्षः attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  जइ (attr == error_mark_ग्रन्थिः)
	    प्रत्यागम attrs;
	  जइ (!attr)
	    भङ्ग;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      अण्णहा
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  प्रत्यागम attrs;
	}
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      अण्णहा
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  प्रत्यागम attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  प्रत्यागम attrs;
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

स्थिर शून्य
c_parser_balanced_token_sequence (c_parser *parser)
{
  जाव (सच्च)
    {
      c_token *token = c_parser_peek_token (parser);
      विकल्प (token->type)
	{
	पक्ष CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    भङ्ग;
	  }

	पक्ष CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    भङ्ग;
	  }

	पक्ष CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  भङ्ग;

	पक्ष CPP_CLOSE_BRACE:
	पक्ष CPP_CLOSE_PAREN:
	पक्ष CPP_CLOSE_SQUARE:
	पक्ष CPP_EOF:
	  प्रत्यागम;

	पक्ष CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  भङ्ग;

	स्वभाव:
	  c_parser_consume_token (parser);
	  भङ्ग;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

स्थिर शून्य
c_parser_omp_directive_args (c_parser *parser, वृक्षः attribute, तार्किक decl_p)
{
  unsigned पूर्णाङ्क n = 1;
  c_token *first = c_parser_peek_token (parser);
  जइ (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      वृक्षः_मानम् (attribute) = NULL_वृक्षः;
      प्रत्यागम;
    }
  जइ (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      वृक्षः_मानम् (attribute) = NULL_वृक्षः;
      प्रत्यागम;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  प्रति (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_प्रक्षिप (*tok);
      c_parser_consume_token (parser);
    }
  वृक्षः arg = make_ग्रन्थिः (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  जइ (decl_p)
    वृक्षः_PUBLIC (arg) = 1;
  वृक्षः_मानम् (attribute) = वृक्षः_cons (NULL_वृक्षः, arg, वृक्षः_मानम् (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

स्थिर शून्य
c_parser_omp_sequence_args (c_parser *parser, वृक्षः attribute)
{
  करेहि
    {
      c_token *token = c_parser_peek_token (parser);
      जइ (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_POINTER (token->मानम्), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      तार्किक directive = मिच्छ;
      ध्रुव वर्ण *p;
      जइ (token->type != CPP_NAME)
	p = "";
      अण्णहा
	p = IDENTIFIER_POINTER (token->मानम्);
      जइ (strcmp (p, "directive") == 0)
	directive = सच्च;
      अण्णहा जइ (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  unsigned nesting_depth = 0;

	  जाव (सच्च)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      जइ ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		भङ्ग;
	      /* If we've run out of tokens, stop.  */
	      जइ (token->type == CPP_EOF)
		भङ्ग;
	      जइ (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		भङ्ग;
	      जइ (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      अण्णहा जइ (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  जइ (nesting_depth-- == 0)
		    भङ्ग;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  जइ (c_parser_next_token_is_not (parser, CPP_COMMA))
	    भङ्ग;
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      जइ (parens.require_open (parser))
	{
	  जइ (directive)
	    c_parser_omp_directive_args (parser, attribute, मिच्छ);
	  अण्णहा
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  जइ (c_parser_next_token_is_not (parser, CPP_COMMA))
	    भङ्ग;
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (c_parser_next_token_is_not (parser, CPP_COMMA))
	भङ्ग;
      अण्णहा
	c_parser_consume_token (parser);
    }
  जाव (1);
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

स्थिर वृक्षः
c_parser_std_attribute (c_parser *parser, तार्किक for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  वृक्षः ns, name, attribute;

  /* Parse the attribute-token.  */
  जइ (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      प्रत्यागम error_mark_ग्रन्थिः;
    }
  name = canonicalize_attr_name (token->मानम्);
  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      जइ (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      जइ (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  प्रत्यागम error_mark_ग्रन्थिः;
	}
      name = canonicalize_attr_name (token->मानम्);
      c_parser_consume_token (parser);
    }
  अण्णहा
    ns = NULL_वृक्षः;
  attribute = build_वृक्षः_list (build_वृक्षः_list (ns, name), NULL_वृक्षः);

  /* Parse the arguments, if any.  */
  ध्रुव attribute_spec *as = lookup_attribute_spec (वृक्षः_PURPOSE (attribute));
  जइ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      जइ ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  प्रत्यागम error_mark_ग्रन्थिः;
	}
      गच्छ out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    जइ ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	प्रत्यागम error_mark_ग्रन्थिः;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    जइ (as && !attribute_ignored_p (as))
      {
	तार्किक takes_identifier
	  = (ns != NULL_वृक्षः
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	तार्किक require_string
	  = (ns == NULL_वृक्षः
	     && (strcmp (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	तार्किक assume_attr
	  = (ns != NULL_वृक्षः
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_POINTER (name), "assume") == 0);
	वृक्षः_मानम् (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, मिच्छ);
      }
    अण्णहा
      {
	जइ ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    जइ (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, मिच्छ);
		parens.skip_until_found_close (parser);
		प्रत्यागम attribute;
	      }
	    अण्णहा जइ (is_attribute_p ("decl", name))
	      {
		वृक्षः_मानम् (वृक्षः_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, सच्च);
		parens.skip_until_found_close (parser);
		प्रत्यागम attribute;
	      }
	    अण्णहा जइ (is_attribute_p ("sequence", name))
	      {
		वृक्षः_मानम् (वृक्षः_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		वृक्षः_मानम् (attribute) = nreverse (वृक्षः_मानम् (attribute));
		प्रत्यागम attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  जइ (ns == NULL_वृक्षः && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (निवेशः_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      प्रत्यागम error_mark_ग्रन्थिः;
    }
  प्रत्यागम attribute;
}

स्थिर वृक्षः
c_parser_std_attribute_list (c_parser *parser, तार्किक for_tm)
{
  वृक्षः attributes = NULL_वृक्षः;
  जाव (सच्च)
    {
      c_token *token = c_parser_peek_token (parser);
      जइ (token->type == CPP_CLOSE_SQUARE)
	भङ्ग;
      जइ (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}
      वृक्षः attribute = c_parser_std_attribute (parser, for_tm);
      जइ (attribute != error_mark_ग्रन्थिः)
	{
	  वृक्षः_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      जइ (c_parser_next_token_is_not (parser, CPP_COMMA))
	भङ्ग;
    }
  प्रत्यागम attributes;
}

स्थिर वृक्षः
c_parser_std_attribute_specifier (c_parser *parser, तार्किक for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  जइ (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    प्रत्यागम NULL_वृक्षः;
  जइ (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      प्रत्यागम NULL_वृक्षः;
    }
  वृक्षः attributes;
  जइ (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      auto ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  अण्णहा
    {
      जइ (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  प्रत्यागम nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

स्थिर तार्किक
c_parser_check_balanced_raw_token_sequence (c_parser *parser, unsigned पूर्णाङ्क *n)
{
  जाव (सच्च)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      विकल्प (token->type)
	{
	पक्ष CPP_OPEN_BRACE:
	  {
	    ++*n;
	    जइ (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		जइ (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		अण्णहा
		  प्रत्यागम मिच्छ;
	      }
	    अण्णहा
	      प्रत्यागम मिच्छ;
	    भङ्ग;
	  }

	पक्ष CPP_OPEN_PAREN:
	  {
	    ++*n;
	    जइ (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		जइ (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		अण्णहा
		  प्रत्यागम मिच्छ;
	      }
	    अण्णहा
	      प्रत्यागम मिच्छ;
	    भङ्ग;
	  }

	पक्ष CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    जइ (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		जइ (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		अण्णहा
		  प्रत्यागम मिच्छ;
	      }
	    अण्णहा
	      प्रत्यागम मिच्छ;
	    भङ्ग;
	  }

	पक्ष CPP_CLOSE_BRACE:
	पक्ष CPP_CLOSE_PAREN:
	पक्ष CPP_CLOSE_SQUARE:
	पक्ष CPP_EOF:
	  प्रत्यागम सच्च;

	स्वभाव:
	  ++*n;
	  भङ्ग;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

स्थिर तार्किक
c_parser_nth_token_starts_std_attributes (c_parser *parser, unsigned पूर्णाङ्क n)
{
  जइ (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    प्रत्यागम मिच्छ;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  जइ (!c_dialect_objc ())
    प्रत्यागम सच्च;
  n += 2;
  जइ (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    प्रत्यागम मिच्छ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  जइ (token->type != CPP_CLOSE_SQUARE)
    प्रत्यागम मिच्छ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  प्रत्यागम token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

स्थिर size_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, size_t n)
{
  size_t orig_n = n;
  जाव (सच्च)
    {
      जइ (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  unsigned पूर्णाङ्क m = n + 2;
	  जइ (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    प्रत्यागम orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  जइ (token->type != CPP_CLOSE_SQUARE)
	    प्रत्यागम orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  जइ (token->type != CPP_CLOSE_SQUARE)
	    प्रत्यागम orig_n;
	  n = m + 2;
	}
      अण्णहा
	भङ्ग;
    }
  प्रत्यागम n;
}

स्थिर वृक्षः
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  वृक्षः attributes = NULL_वृक्षः;
  करेहि
    {
      वृक्षः attrs = c_parser_std_attribute_specifier (parser, मिच्छ);
      attributes = chainon (attributes, attrs);
    }
  जाव (c_parser_nth_token_starts_std_attributes (parser, 1));
  प्रत्यागम attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

संरचना c_type_name *
c_parser_type_name (c_parser *parser, तार्किक alignas_ok)
{
  संरचना c_declspecs *specs = build_null_declspecs ();
  संरचना c_declarator *declarator;
  संरचना c_type_name *ret;
  तार्किक dummy = मिच्छ;
  c_parser_declspecs (parser, specs, मिच्छ, सच्च, सच्च, alignas_ok, मिच्छ,
		      मिच्छ, सच्च, cla_prefer_type);
  जइ (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      प्रत्यागम रिक्त;
    }
  जइ (specs->type != error_mark_ग्रन्थिः)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      जइ (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_शिखरम्_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  जइ (declarator == रिक्त)
    प्रत्यागम रिक्त;
  ret = XOBNEW (&parser_obstack, संरचना c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  प्रत्यागम ret;
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_initializer (c_parser *parser, वृक्षः decl)
{
  जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    प्रत्यागम c_parser_braced_init (parser, NULL_वृक्षः, मिच्छ, रिक्त,
				 decl != error_mark_ग्रन्थिः
				 && C_DECL_VARIABLE_SIZE (decl));
  अण्णहा
    {
      संरचना c_व्यञ्जकम् ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      जइ (decl != error_mark_ग्रन्थिः && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      जइ (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !वृक्षः_STATIC (decl)
	  && ret.मानम् == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      जइ (वृक्षः_CODE (ret.मानम्) != STRING_CST
	  && (वृक्षः_CODE (ret.मानम्) != COMPOUND_LITERAL_व्यञ्जकम्
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_व्यञ्जकम्_DECL
					    (ret.मानम्))))
	ret = convert_lvalue_to_rvalue (loc, ret, सच्च, सच्च, सच्च);
      प्रत्यागम ret;
    }
}

/* The location of the last comma within the current initializer list,
   or UNKNOWN_LOCATION if not within one.  */

location_t last_init_list_comma;

/* Parse a braced initializer list.  TYPE is the type specified for a
   compound literal, and NULL_TREE for other initializers and for
   nested braced lists.  NESTED_P is true for nested braced lists,
   false for the list of a compound literal or the list that is the
   top-level initializer in a declaration.  VARSIZE_P indicates
   whether the object to be initialized has a variable size.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_braced_init (c_parser *parser, वृक्षः type, तार्किक nested_p,
		      संरचना obstack *outer_obstack, तार्किक varsize_p)
{
  संरचना c_व्यञ्जकम् ret;
  संरचना obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = मिच्छ;
  तार्किक zero_init_padding_bits = मिच्छ;
  matching_braces braces;
  braces.consume_open (parser);
  जइ (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      प्रक्षिप_init_level (brace_loc, 0, &braced_init_obstack);
    }
  अण्णहा
    really_start_incremental_init (type);
  जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      जइ (flag_isoc23)
	zero_init_padding_bits = सच्च;
    }
  अण्णहा
    {
      जइ (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      जाव (सच्च)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  जइ (parser->error)
	    भङ्ग;
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      जाव (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_व्यञ्जकम् embed_val;
		  embed_val.मानम् = embed->मानम्;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_ग्रन्थिः;
		  set_c_व्यञ्जकम्_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, मिच्छ,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  अण्णहा
	    भङ्ग;
	  जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    भङ्ग;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  जइ (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      braces.skip_until_found_close (parser);
      निष्कासय_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, रिक्त);
      प्रत्यागम ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = निष्कासय_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  जइ (zero_init_padding_bits
      && ret.मानम्
      && वृक्षः_CODE (ret.मानम्) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.मानम्) = 1;
  obstack_free (&braced_init_obstack, रिक्त);
  set_c_व्यञ्जकम्_source_range (&ret, brace_loc, close_loc);
  प्रत्यागम ret;
}

/* Parse a nested initializer, including designators.  */

स्थिर शून्य
c_parser_initelt (c_parser *parser, संरचना obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  जइ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->मानम्,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  अण्णहा
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      पूर्णाङ्क des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      जाव (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  पूर्णाङ्क des_prev = des_seen;
	  जइ (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  जइ (des_seen < 2)
	    des_seen++;
	  जइ (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      जइ (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->मानम्,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      अण्णहा
		{
		  संरचना c_व्यञ्जकम् init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = रिक्त;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, रिक्त);
		  process_init_element (निवेशः_location, init, मिच्छ,
					braced_init_obstack);
		  प्रत्यागम;
		}
	    }
	  अण्णहा
	    {
	      संरचना c_व्यञ्जकम् first_व्यञ्जकम्;
	      वृक्षः first, second;
	      location_t ellipsis_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	      location_t array_index_loc = UNKNOWN_LOCATION;
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
	      जइ (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  भङ्ग;
		}
	      जइ (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  वृक्षः rec, args;
		  संरचना c_व्यञ्जकम् mexpr;
		  c_parser_consume_token (parser);
		  जइ (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      वृक्षः id = c_parser_peek_token (parser)->मानम्;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      गच्छ parse_message_args;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
		  mark_exp_read (first_व्यञ्जकम्.मानम्);
		  जइ (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    गच्छ array_desig_after_first;
		  first = first_व्यञ्जकम्.मानम्;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  जाव (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      संरचना c_व्यञ्जकम् next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       सच्च, सच्च);
		      rec = build_compound_व्यञ्जकम् (comma_loc, rec, next.मानम्);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.मानम्
		    = objc_build_message_व्यञ्जकम् (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = रिक्त;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  प्रत्यागम;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	      mark_exp_read (first_व्यञ्जकम्.मानम्);
	    array_desig_after_first:
	      first_व्यञ्जकम् = convert_lvalue_to_rvalue (array_index_loc,
						     first_व्यञ्जकम्,
						     सच्च, सच्च);
	      first = first_व्यञ्जकम्.मानम्;
	      जइ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_व्यञ्जकम्_no_commas
						      (parser, रिक्त)),
						     सच्च, सच्च).मानम्;
		  mark_exp_read (second);
		}
	      अण्णहा
		second = NULL_वृक्षः;
	      जइ (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  जइ (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      अण्णहा
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      जइ (des_seen >= 1)
	{
	  जइ (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  अण्णहा
	    {
	      जइ (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      अण्णहा
		{
		  संरचना c_व्यञ्जकम् init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = रिक्त;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, रिक्त);
		  process_init_element (निवेशः_location, init, मिच्छ,
					braced_init_obstack);
		  प्रत्यागम;
		}
	    }
	}
    }
  c_parser_initval (parser, रिक्त, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

स्थिर शून्य
c_parser_initval (c_parser *parser, संरचना c_व्यञ्जकम् *after,
		  संरचना obstack * braced_init_obstack)
{
  संरचना c_व्यञ्जकम् init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_वृक्षः, सच्च,
				 braced_init_obstack, मिच्छ);
  अण्णहा
    {
      init = c_parser_व्यञ्जकम्_no_commas (parser, after);
      जइ (init.मानम् != NULL_वृक्षः
	  && वृक्षः_CODE (init.मानम्) != STRING_CST
	  && (वृक्षः_CODE (init.मानम्) != COMPOUND_LITERAL_व्यञ्जकम्
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_व्यञ्जकम्_DECL
					    (init.मानम्))))
	init = convert_lvalue_to_rvalue (loc, init, सच्च, सच्च, सच्च);
    }
  वृक्षः val = init.मानम्;
  process_init_element (loc, init, मिच्छ, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  स्थिर unsigned vals_to_ignore;
  जइ (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  अण्णहा जइ (val
	   && वृक्षः_CODE (val) == INTEGER_CST
	   && वृक्षः_TYPE (val) == integer_type_ग्रन्थिः
	   && c_parser_next_token_is (parser, CPP_COMMA))
    जइ (unsigned पूर्णाङ्क len = c_maybe_optimize_large_byte_initializer ())
      {
	वर्ण buf1[64];
	unsigned पूर्णाङ्क i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	प्रति (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    जइ (tok->type != CPP_COMMA)
	      भङ्ग;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    जइ (tok->type != CPP_सङ्ख्या
		|| वृक्षः_CODE (tok->मानम्) != INTEGER_CST
		|| वृक्षः_TYPE (tok->मानम्) != integer_type_ग्रन्थिः
		|| wi::neg_p (wi::to_wide (tok->मानम्))
		|| wi::to_widest (tok->मानम्) > UCHAR_MAX)
	      भङ्ग;
	    buf1[i] = (वर्ण) वृक्षः_to_uhwi (tok->मानम्);
	    जइ (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	जइ (i < 64)
	  {
	    vals_to_ignore = i;
	    प्रत्यागम;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	जइ (tok->type == CPP_CLOSE_BRACE && len != INT_MAX)
	  len = i;
	अण्णहा जइ (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_सङ्ख्या))
	  {
	    vals_to_ignore = i;
	    प्रत्यागम;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	unsigned पूर्णाङ्क max_len = 131072 - offsetof (संरचना वृक्षः_string, str) - 1;
	unsigned पूर्णाङ्क orig_len = len;
	unsigned पूर्णाङ्क off = 0, last = 0;
	जइ (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	वर्ण *buf2 = XNEWVEC (वर्ण, len + off);
	जइ (off)
	  buf2[0] = (वर्ण) वृक्षः_to_uhwi (val);
	memcpy (buf2 + off, buf1, i);
	प्रति (unsigned पूर्णाङ्क j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	प्रति (; i < len; ++i)
	  {
	    जइ (!c_parser_next_token_is (parser, CPP_COMMA))
	      भङ्ग;
	    tok = c_parser_peek_2nd_token (parser);
	    जइ (tok->type != CPP_सङ्ख्या
		|| वृक्षः_CODE (tok->मानम्) != INTEGER_CST
		|| वृक्षः_TYPE (tok->मानम्) != integer_type_ग्रन्थिः
		|| wi::neg_p (wi::to_wide (tok->मानम्))
		|| wi::to_widest (tok->मानम्) > UCHAR_MAX)
	      भङ्ग;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    जइ (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      भङ्ग;
	    buf2[i + off] = (वर्ण) वृक्षः_to_uhwi (tok->मानम्);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    जइ (orig_len == INT_MAX
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_सङ्ख्या)))
	      {
		last = 1;
		भङ्ग;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_ग्रन्थिः (RAW_DATA_CST);
	वृक्षः_TYPE (val) = integer_type_ग्रन्थिः;
	RAW_DATA_LENGTH (val) = i;
	वृक्षः owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	वृक्षः_TYPE (owner) = build_array_type_nelts (unsigned_char_type_ग्रन्थिः,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = वृक्षः_STRING_POINTER (owner) + off;
	init.मानम् = val;
	set_c_व्यञ्जकम्_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_ग्रन्थिः;
	init.m_decimal = 0;
	process_init_element (loc, init, मिच्छ, braced_init_obstack);
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

स्थिर वृक्षः
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  वृक्षः stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  जइ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (सच्च);
      c_end_compound_stmt (brace_loc, stmt, सच्च);
      प्रत्यागम error_mark_ग्रन्थिः;
    }
  stmt = c_begin_compound_stmt (सच्च);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  जइ (endlocp)
    *endlocp = end_loc;

  प्रत्यागम c_end_compound_stmt (brace_loc, stmt, सच्च);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

स्थिर शून्य
check_omp_intervening_code (c_parser *parser)
{
  संरचना omp_for_parse_data *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  जइ (!omp_for_parse_state->in_intervening_code)
    प्रत्यागम;
  omp_for_parse_state->saw_intervening_code = सच्च;

  /* Only diagnose errors related to perfect nesting once.  */
  जइ (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      जइ (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = सच्च;
	}
      अण्णहा जइ (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = सच्च;
	}
      अण्णहा जइ (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = सच्च;
	}
      अण्णहा जइ (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = सच्च;
	}
      जइ (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = सच्च;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
स्थिर शून्य
add_structured_block_stmt (वृक्षः sl)
{
  जइ (वृक्षः_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_ग्रन्थिः, sl));
}

संरचना c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  ध्रुव c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

स्थिर तार्किक
c_parser_handle_statement_omp_attributes (c_parser *parser, वृक्षः &attrs,
					  तार्किक *have_std_attrs)
{
  जइ (!flag_openmp && !flag_openmp_simd)
    प्रत्यागम मिच्छ;

  auto_vec<c_omp_attribute_data, 16> vd;
  पूर्णाङ्क cnt = 0;
  पूर्णाङ्क tokens = 0;
  तार्किक bad = मिच्छ;
  प्रति (वृक्षः *pa = &attrs; *pa; )
    जइ (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	प्रति (वृक्षः a = वृक्षः_मानम् (*pa); a; a = वृक्षः_CHAIN (a))
	  {
	    वृक्षः d = वृक्षः_मानम् (a);
	    gcc_assert (वृक्षः_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    जइ (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = मिच्छ;
		bad = सच्च;
	      }
	    अण्णहा जइ (वृक्षः_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = सच्च;
	      }
	    ध्रुव वर्ण *directive[3] = {};
	    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
	      {
		वृक्षः id = NULL_वृक्षः;
		जइ (first + i == last)
		  भङ्ग;
		जइ (first[i].type == CPP_NAME)
		  id = first[i].मानम्;
		अण्णहा जइ (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(पूर्णाङ्क) first[i].keyword];
		अण्णहा
		  भङ्ग;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ध्रुव c_omp_directive *dir = रिक्त;
	    जइ (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    जइ (dir == रिक्त)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  वृक्षः_PUBLIC (d) ? "omp::decl" : "omp::directive");
		अनुवर्त;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    जइ (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		जइ (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		अण्णहा जइ (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_POINTER (first[2].मानम्),
				     "depend") == 0
			     || strcmp (IDENTIFIER_POINTER (first[2].मानम्),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    अण्णहा जइ (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		पूर्णाङ्क paren_depth = 0;
		प्रति (पूर्णाङ्क i = 1; first + i < last; i++)
		  जइ (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  अण्णहा जइ (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  अण्णहा जइ (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_POINTER (first[i].मानम्),
				       "at")
			   && !strcmp (IDENTIFIER_POINTER (first[i
								 + 2].मानम्),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      भङ्ग;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_प्रक्षिप (v);
	    जइ (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_प्रक्षिप (v);
	*pa = वृक्षः_CHAIN (*pa);
      }
    अण्णहा
      pa = &वृक्षः_CHAIN (*pa);

  जइ (bad)
    {
    fail:
      जइ (have_std_attrs && attrs == रिक्त)
	*have_std_attrs = मिच्छ;
      प्रत्यागम मिच्छ;
    }

  unsigned पूर्णाङ्क i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    जइ (v->tokens)
      {
	जइ (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	अण्णहा जइ (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    अण्णहा
      {
	जइ (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  जइ (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      गच्छ fail;
    }
  जइ (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      गच्छ fail;
    }

  जइ (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  जइ (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      गच्छ fail;
    }
  जइ (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      गणना pragma_kind kind = token->pragma_kind;
      जइ (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  गच्छ fail;
	}
    }

  जइ (!tokens)
    प्रत्यागम मिच्छ;

  unsigned पूर्णाङ्क tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = रिक्त;
  vec_safe_reserve (toks, tokens, सच्च);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      जइ (!v->tokens)
	अनुवर्त;
      जइ (!flag_openmp && !v->dir->simd)
	अनुवर्त;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_प्रक्षिप (tok);
      जाव (++first < last)
	toks->quick_प्रक्षिप (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_प्रक्षिप (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_प्रक्षिप (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  प्रत्यागम सच्च;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

स्थिर शून्य
c_parser_handle_directive_omp_attributes (वृक्षः &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  जइ (!flag_openmp && !flag_openmp_simd)
    प्रत्यागम;

  प्रति (वृक्षः *pa = &attrs; *pa; )
    जइ (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	पूर्णाङ्क cnt = 0;
	प्रति (वृक्षः *pa2 = &वृक्षः_मानम् (*pa); *pa2; )
	  {
	    वृक्षः a = *pa2;
	    वृक्षः d = वृक्षः_मानम् (a);
	    gcc_assert (वृक्षः_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    ध्रुव वर्ण *directive[3] = {};
	    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
	      {
		वृक्षः id = NULL_वृक्षः;
		जइ (first + i == last)
		  भङ्ग;
		जइ (first[i].type == CPP_NAME)
		  id = first[i].मानम्;
		अण्णहा जइ (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(पूर्णाङ्क) first[i].keyword];
		अण्णहा
		  भङ्ग;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    ध्रुव c_omp_directive *dir = रिक्त;
	    जइ (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    जइ (dir == रिक्त)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  वृक्षः_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = वृक्षः_CHAIN (a);
	      }
	    अण्णहा जइ (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		जइ (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    प्रति (pa = &attrs; *pa; )
		      जइ (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = वृक्षः_CHAIN (*pa);
		      अण्णहा
			pa = &वृक्षः_CHAIN (*pa);
		    प्रत्यागम;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		प्रति (++first; first < last; ++first)
		  attr_clauses->quick_प्रक्षिप (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_प्रक्षिप (tok);
		*pa2 = वृक्षः_CHAIN (a);
	      }
	    अण्णहा
	      pa2 = &वृक्षः_CHAIN (a);
	  }
	जइ (cnt && वृक्षः_मानम् (*pa) == NULL_वृक्षः)
	  *pa = वृक्षः_CHAIN (*pa);
	अण्णहा
	  pa = &वृक्षः_CHAIN (*pa);
      }
    अण्णहा
      pa = &वृक्षः_CHAIN (*pa);
  जइ (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_प्रक्षिप (tok);
      attr_clauses->quick_प्रक्षिप (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

स्थिर वृक्षः
c_parser_handle_musttail (c_parser *parser, वृक्षः std_attrs, attr_state &attr)
{
  जइ (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      जइ (वृक्षः a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  प्रति (; a; a = lookup_attribute ("gnu", "musttail", वृक्षः_CHAIN (a)))
	    जइ (वृक्षः_मानम् (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = सच्च;
	}
      जइ (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = सच्च;
	}
    }
  प्रत्यागम std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

स्थिर वृक्षः
get_before_labels ()
{
  जइ (!building_stmt_list_p ())
    प्रत्यागम NULL_वृक्षः;
  वृक्षः_stmt_iterator tsi = tsi_last (cur_stmt_list);
  जइ (tsi_end_p (tsi))
    प्रत्यागम NULL_वृक्षः;
  प्रत्यागम tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

स्थिर location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  तार्किक last_stmt = मिच्छ;
  तार्किक last_label = मिच्छ;
  तार्किक save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  संरचना omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  तार्किक in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : मिच्छ;
  वृक्षः sl = NULL_वृक्षः;
  attr_state astate = {};

  जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      प्रत्यागम endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  जइ (in_omp_loop_block)
    sl = प्रक्षिप_stmt_list ();

  mark_valid_location_for_stdc_pragma (सच्च);
  जइ (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (मिच्छ);
      जइ (in_omp_loop_block)
	check_omp_intervening_code (parser);
      जाव (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  जाव (सच्च)
	    {
	      वृक्षः label;
	      जइ (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  भङ्ग;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->मानम्);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_व्यञ्जकम्, label));
	      c_parser_consume_token (parser);
	      जइ (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      अण्णहा
		भङ्ग;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      प्रत्यागम endloc;
    }
  वृक्षः before_labels = get_before_labels ();
  जाव (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      तार्किक want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : मिच्छ);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      जइ (in_omp_loop_block && !last_label)
	{
	  वृक्षः_code code = omp_for_parse_state->code;
	  जइ (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     मिच्छ))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (निष्कासय_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, रिक्त));
	      omp_for_parse_state->depth--;
	      sl = प्रक्षिप_stmt_list ();
	      parser->error = मिच्छ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      अनुवर्त;
	    }
	  अण्णहा जइ (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      वृक्षः pre_sl = निष्कासय_stmt_list (sl);
	      वृक्षः nested_sl = प्रक्षिप_stmt_list ();
	      mark_valid_location_for_stdc_pragma (मिच्छ);
	      c_parser_statement_after_labels (parser, रिक्त, NULL_वृक्षः);
	      nested_sl = निष्कासय_stmt_list (nested_sl);
	      जइ (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = प्रक्षिप_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      अण्णहा
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = प्रक्षिप_stmt_list ();
		}
	      parser->error = मिच्छ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      अनुवर्त;
	    }
	  अण्णहा जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      अनुवर्त;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      तार्किक have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      वृक्षः std_attrs = NULL_वृक्षः;
      जइ (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      जइ (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  जइ (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  अण्णहा
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = सच्च;
	  last_stmt = मिच्छ;
	  mark_valid_location_for_stdc_pragma (मिच्छ);
	  जइ (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      अण्णहा जइ (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = सच्च)))
	{
	  जइ (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  जइ (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = मिच्छ;
	    }
	  mark_valid_location_for_stdc_pragma (मिच्छ);
	  तार्किक fallthru_attr_p = मिच्छ;
	  c_parser_declaration_or_fndef (parser, सच्च, !have_std_attrs,
					 सच्च, सच्च, सच्च, मिच्छ, रिक्त,
					 रिक्त, have_std_attrs, std_attrs,
					 रिक्त, &fallthru_attr_p);

	  जइ (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  जइ (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = मिच्छ;
	  before_labels = get_before_labels ();
	}
      अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  जाव (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  जइ (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      पूर्णाङ्क ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = मिच्छ;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      जइ (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = मिच्छ;
		}
	      mark_valid_location_for_stdc_pragma (मिच्छ);
	      c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, सच्च,
					     सच्च, मिच्छ);
	      जइ (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      जइ (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = मिच्छ;
	      before_labels = get_before_labels ();
	    }
	  अण्णहा
	    गच्छ statement;
	}
      अण्णहा जइ (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  जइ (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  अण्णहा जइ (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  जइ (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = मिच्छ;
	  जइ (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       रिक्त, before_labels))
	    {
	      last_label = मिच्छ;
	      last_stmt = सच्च;
	      जइ (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  जइ (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      अण्णहा जइ (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  प्रत्यागम c_parser_peek_token (parser)->location;
	}
      अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          जइ (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      प्रत्यागम c_parser_peek_token (parser)->location;
            }
          अण्णहा
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              अनुवर्त;
            }
        }
      अण्णहा
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = मिच्छ;
	  last_stmt = सच्च;
	  mark_valid_location_for_stdc_pragma (मिच्छ);
	  जइ (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, रिक्त, before_labels,
					     रिक्त, astate);
	  अण्णहा
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = मिच्छ;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, रिक्त, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = मिच्छ;
      astate.reset ();
    }
  जइ (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  जइ (sl)
    {
      sl = निष्कासय_stmt_list (sl);
      जइ (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      अण्णहा
	add_structured_block_stmt (sl);
    }
  प्रत्यागम endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

स्थिर attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  तार्किक have_std_attrs;
  वृक्षः std_attrs = रिक्त;
  जइ ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  जाव (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = रिक्त;
      जइ ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  जइ (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      जइ (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  अण्णहा जइ (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  प्रत्यागम attr;
}


/* Information used while parsing an OpenMP metadirective.  */
संरचना omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<वृक्षः> * GTY((skip)) body_labels;
  unsigned पूर्णाङ्क region_अङ्कः;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
स्थिर वृक्षः
mangle_metadirective_region_label (c_parser *parser, वृक्षः name)
{
  जइ (parser->omp_metadirective_state->body_labels->contains (name))
    {
      ध्रुव वर्ण *old_name = IDENTIFIER_POINTER (name);
      वर्ण *new_name = (वर्ण *) XALLOCAVEC (वर्ण, strlen (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_अङ्कः);
      प्रत्यागम get_identifier (new_name);
    }
  प्रत्यागम name;
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
स्थिर शून्य
c_parser_label (c_parser *parser, वृक्षः std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  वृक्षः label = NULL_वृक्षः;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  तार्किक fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  जइ (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      वृक्षः exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_व्यञ्जकम्_no_commas (parser, रिक्त),
				       सच्च, सच्च).मानम्;
      जइ (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_वृक्षः, std_attrs);
	}
      अण्णहा जइ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_व्यञ्जकम्_no_commas (parser,
								    रिक्त),
					   सच्च, सच्च).मानम्;
	  जइ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      अण्णहा
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      जइ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_वृक्षः, NULL_वृक्षः, std_attrs);
    }
  अण्णहा
    {
      वृक्षः name = c_parser_peek_token (parser)->मानम्;
      वृक्षः tlab;
      वृक्षः attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      जइ (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      जइ (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_व्यञ्जकम्, tlab));
	}
      जइ (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  जइ (label)
    {
      जइ (वृक्षः_CODE (label) == LABEL_व्यञ्जकम्)
	FALLTHROUGH_LABEL_P (LABEL_व्यञ्जकम्_LABEL (label)) = fallthrough_p;
      अण्णहा
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

स्थिर शून्य
c_parser_statement (c_parser *parser, तार्किक *if_p, location_t *loc_after_labels)
{
  वृक्षः before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  जइ (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = मिच्छ;
  c_parser_statement_after_labels (parser, if_p, before_labels, रिक्त, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

स्थिर वृक्षः
c_parser_bc_name (c_parser *parser, तार्किक is_break)
{
  जइ (!c_parser_next_token_is (parser, CPP_NAME))
    प्रत्यागम NULL_वृक्षः;

  c_token *tok = c_parser_peek_token (parser);
  वृक्षः label = c_finish_bc_name (tok->location, tok->मानम्, is_break);
  c_parser_consume_token (parser);
  प्रत्यागम label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

स्थिर शून्य
c_parser_statement_after_labels (c_parser *parser, तार्किक *if_p,
				 वृक्षः before_labels,
				 vec<वृक्षः> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः stmt = NULL_वृक्षः;
  तार्किक in_if_block = parser->in_if_block;
  parser->in_if_block = मिच्छ;
  जइ (if_p != रिक्त)
    *if_p = मिच्छ;

  जइ (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      भङ्ग;
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  भङ्ग;
	पक्ष RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  भङ्ग;
	पक्ष RID_WHILE:
	  c_parser_while_statement (parser, मिच्छ, 0, मिच्छ, if_p, before_labels);
	  भङ्ग;
	पक्ष RID_DO:
	  c_parser_do_statement (parser, मिच्छ, 0, मिच्छ, before_labels);
	  भङ्ग;
	पक्ष RID_FOR:
	  c_parser_for_statement (parser, मिच्छ, 0, मिच्छ, if_p, before_labels);
	  भङ्ग;
	पक्ष RID_GOTO:
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      वृक्षः name = c_parser_peek_token (parser)->मानम्;
	      जइ (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  अण्णहा जइ (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      संरचना c_व्यञ्जकम् val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, मिच्छ, सच्च);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  अण्णहा
	    c_parser_error (parser, "expected identifier or %<*%>");
	  गच्छ expect_semicolon;
	पक्ष RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, मिच्छ,
				   c_parser_bc_name (parser, मिच्छ));
	  गच्छ expect_semicolon;
	पक्ष RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, सच्च,
				   c_parser_bc_name (parser, सच्च));
	  गच्छ expect_semicolon;
	पक्ष RID_RETURN:
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_वृक्षः, NULL_वृक्षः,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  अण्णहा
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      संरचना c_व्यञ्जकम् व्यञ्जकम् = c_parser_expression_conv (parser);
	      mark_exp_read (व्यञ्जकम्.मानम्);
	      stmt = c_finish_return (व्यञ्जकम्_LOC_OR_LOC (व्यञ्जकम्.मानम्, xloc),
				      व्यञ्जकम्.मानम्, व्यञ्जकम्.original_type,
				      astate.musttail_p);
	      गच्छ expect_semicolon;
	    }
	  भङ्ग;
	पक्ष RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  भङ्ग;
	पक्ष RID_TRANSACTION_ATOMIC:
	पक्ष RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  भङ्ग;
	पक्ष RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  गच्छ expect_semicolon;
	पक्ष RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_वृक्षः);
	      c_parser_consume_token (parser);
	    }
	  अण्णहा
	    {
	      संरचना c_व्यञ्जकम् व्यञ्जकम् = c_parser_expression (parser);
	      व्यञ्जकम् = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, मिच्छ, मिच्छ);
	      व्यञ्जकम्.मानम् = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
	      stmt = objc_build_throw_stmt (loc, व्यञ्जकम्.मानम्);
	      गच्छ expect_semicolon;
	    }
	  भङ्ग;
	पक्ष RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  भङ्ग;
	पक्ष RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  भङ्ग;
	पक्ष RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    वृक्षः attrs = c_parser_gnu_attributes (parser);
	    तार्किक has_assume = lookup_attribute ("assume", attrs);
	    जइ (has_assume)
	      {
		जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, सच्च);
		अण्णहा
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = मिच्छ;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    जइ (astate.musttail_p)
	      {
		जइ (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		गच्छ restart;
	      }
	    जइ (attribute_fallthrough_p (attrs))
	      {
		जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    वृक्षः fn = build_call_व्यञ्जकम्_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_ग्रन्थिः, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		अण्णहा
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    अण्णहा जइ (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    अण्णहा जइ (attrs != NULL_वृक्षः)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    भङ्ग;
	  }
	स्वभाव:
	  गच्छ व्यञ्जकम्_stmt;
	}
      भङ्ग;
    पक्ष CPP_SEMICOLON:
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_CLOSE_PAREN:
    पक्ष CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_PRAGMA:
      जइ (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        गच्छ restart;
      भङ्ग;
    स्वभाव:
    व्यञ्जकम्_stmt:
      stmt = c_finish_व्यञ्जकम्_stmt (loc, c_parser_expression_conv (parser).मानम्);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      भङ्ग;
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
  जइ (व्यञ्जकम्_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_व्यञ्जकम्_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

स्थिर वृक्षः
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः cond;
  cond = c_parser_expression_conv (parser).मानम्;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, मिच्छ, रिक्त);
  जइ (warn_sequence_point)
    verify_sequence_points (cond);
  प्रत्यागम cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

स्थिर वृक्षः
c_parser_paren_condition (c_parser *parser)
{
  वृक्षः cond;
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम error_mark_ग्रन्थिः;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  प्रत्यागम cond;
}

/* Parse a selection-header:

   selection-header:
     expression
     declaration expression
     simple-declaration

   simple-declaration:
     attribute-specifier-sequence[opt] declaration-specifiers declarator
       = initializer

  SWITCH_P is true if we are called from c_parser_switch_statement; in
  that case, don't perform the truthvalue conversion.  */

स्थिर c_व्यञ्जकम्
c_parser_selection_header (c_parser *parser, तार्किक switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_व्यञ्जकम् व्यञ्जकम्;
  तार्किक parse_व्यञ्जकम् = सच्च;
  वृक्षः std_attrs;
  तार्किक have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  जइ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  अण्णहा
    std_attrs = NULL_वृक्षः;
  जइ (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      व्यञ्जकम्.मानम्
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/मिच्छ,
					 /*static_assert_ok=*/मिच्छ,
					 /*empty_ok=*/मिच्छ,
					 /*nested=*/सच्च,
					 /*start_attr_ok=*/सच्च,
					 /*simple_ok=*/सच्च,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      अण्णहा
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  जइ (!व्यञ्जकम्.मानम्)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      व्यञ्जकम्.original_type = error_mark_ग्रन्थिः;
	      व्यञ्जकम्.set_error ();
	      प्रत्यागम व्यञ्जकम्;
	    }
	  parse_व्यञ्जकम् = मिच्छ;
	}
      जइ (व्यञ्जकम्.मानम्)
	{
	  व्यञ्जकम्.original_type = वृक्षः_TYPE (व्यञ्जकम्.मानम्);
	  व्यञ्जकम् = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, /*convert_p=*/सच्च,
					   /*read_p=*/सच्च);
	}
    }
  अण्णहा जइ (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      व्यञ्जकम्.original_type = error_mark_ग्रन्थिः;
      व्यञ्जकम्.set_error ();
      प्रत्यागम व्यञ्जकम्;
    }

  जइ (parse_व्यञ्जकम्)
    व्यञ्जकम् = c_parser_expression_conv (parser);
  जइ (!switch_p)
    {
      व्यञ्जकम्.मानम् = c_objc_common_truthvalue_conversion (loc, व्यञ्जकम्.मानम्);
      व्यञ्जकम्.मानम् = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
      जइ (warn_sequence_point)
	verify_sequence_points (व्यञ्जकम्.मानम्);
    }
  प्रत्यागम व्यञ्जकम्;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

स्थिर वृक्षः
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम error_mark_ग्रन्थिः;
  वृक्षः cond = c_parser_selection_header (parser, /*switch_p=*/मिच्छ).मानम्;
  parens.skip_until_found_close (parser);
  प्रत्यागम cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

स्थिर वृक्षः
c_parser_c99_block_statement (c_parser *parser, तार्किक *if_p,
			      location_t *loc_after_labels)
{
  वृक्षः block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  प्रत्यागम c_end_compound_stmt (loc, block, flag_isoc99);
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

स्थिर वृक्षः
c_parser_if_body (c_parser *parser, तार्किक *if_p,
		  ध्रुव token_indent_info &if_tinfo)
{
  वृक्षः block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  वृक्षः before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      जइ (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  अण्णहा जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  अण्णहा
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, रिक्त, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  जइ (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  प्रत्यागम c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

स्थिर वृक्षः
c_parser_else_body (c_parser *parser, ध्रुव token_indent_info &else_tinfo,
		    vec<वृक्षः> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  वृक्षः block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  वृक्षः before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  अण्णहा
    {
      जइ (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, रिक्त, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  जइ (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  प्रत्यागम c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

स्थिर शून्य
c_parser_if_statement (c_parser *parser, तार्किक *if_p, vec<वृक्षः> *chain)
{
  वृक्षः block;
  location_t loc;
  वृक्षः cond;
  तार्किक nested_if = मिच्छ;
  वृक्षः first_body, second_body;
  तार्किक in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = सच्च;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  जइ (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (व्यञ्जकम्_LOCATION (cond), cond, &chain);

  जइ (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      जइ (warn_duplicated_cond)
	{
	  जइ (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == रिक्त)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = नूतन vec<वृक्षः> ();
	      जइ (!CONSTANT_CLASS_P (cond) && !वृक्षः_SIDE_EFFECTS (cond))
		chain->safe_प्रक्षिप (cond);
	    }
	  अण्णहा जइ (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      जइ (if_p != रिक्त)
	*if_p = सच्च;
    }
  अण्णहा
    {
      second_body = NULL_वृक्षः;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      जइ (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      जइ (warn_duplicated_cond)
	/* This if statement does not have an else clause.  We don't
	   need the condition chain anymore.  */
	vec_free (chain);
    }
  c_finish_if_stmt (loc, cond, first_body, second_body);
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));

  c_parser_maybe_reclassify_token (parser);
}

/* Parse a switch statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   switch-statement:
     switch (expression) statement

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

स्थिर शून्य
c_parser_switch_statement (c_parser *parser, तार्किक *if_p, वृक्षः before_labels)
{
  संरचना c_व्यञ्जकम् ce;
  वृक्षः block, व्यञ्जकम्, body;
  unsigned वर्ण save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  वृक्षः switch_name;
  पूर्णाङ्क अङ्कः_names = c_get_loop_names (before_labels, सच्च, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  तार्किक explicit_cast_p = मिच्छ;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = सच्च;
      ce = c_parser_selection_header (parser, /*switch_p=*/सच्च);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, सच्च, सच्च);
      व्यञ्जकम् = ce.मानम्;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  अण्णहा
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      व्यञ्जकम् = error_mark_ग्रन्थिः;
      ce.original_type = error_mark_ग्रन्थिः;
    }
  वृक्षः stmt
    = c_start_switch (switch_loc, switch_cond_loc, व्यञ्जकम्, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  जइ (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  अण्णहा
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  तार्किक open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  जइ (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  जइ (अङ्कः_names)
    {
      जइ (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_वृक्षः;
      अण्णहा
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (अङ्कः_names);
    }
  add_stmt (c_end_compound_stmt (switch_loc, block, flag_isoc99));
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

स्थिर शून्य
c_parser_while_statement (c_parser *parser, तार्किक ivdep, unsigned short unroll,
			  तार्किक novector, तार्किक *if_p, वृक्षः before_labels)
{
  वृक्षः block, cond, body;
  unsigned वर्ण save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  वृक्षः loop_name;
  पूर्णाङ्क अङ्कः_names = c_get_loop_names (before_labels, मिच्छ, &loop_name);

  जइ (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = सच्च;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  जइ (ivdep && cond != error_mark_ग्रन्थिः)
    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
		   build_int_cst (integer_type_ग्रन्थिः,
				  annot_व्यञ्जकम्_ivdep_kind),
		   integer_zero_ग्रन्थिः);
  जइ (unroll && cond != error_mark_ग्रन्थिः)
    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
		   build_int_cst (integer_type_ग्रन्थिः,
				  annot_व्यञ्जकम्_unroll_kind),
		   build_int_cst (integer_type_ग्रन्थिः, unroll));
  जइ (novector && cond != error_mark_ग्रन्थिः)
    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
		   build_int_cst (integer_type_ग्रन्थिः,
				  annot_व्यञ्जकम्_no_vector_kind),
		   integer_zero_ग्रन्थिः);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  जइ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  तार्किक open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  जइ (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_वृक्षः;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_वृक्षः,
			NULL_वृक्षः));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  जइ (अङ्कः_names)
    c_release_loop_names (अङ्कः_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  जइ (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

स्थिर शून्य
c_parser_do_statement (c_parser *parser, तार्किक ivdep, unsigned short unroll,
		       तार्किक novector, वृक्षः before_labels)
{
  वृक्षः block, cond, body;
  unsigned वर्ण save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  वृक्षः loop_name;
  पूर्णाङ्क अङ्कः_names = c_get_loop_names (before_labels, मिच्छ, &loop_name);

  जइ (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = सच्च;
    }

  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  जइ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, रिक्त);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  जइ (अङ्कः_names)
    {
      जइ (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_वृक्षः;
      c_release_loop_names (अङ्कः_names);
    }
  cond = c_parser_paren_condition (parser);
  जइ (ivdep && cond != error_mark_ग्रन्थिः)
    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
		   build_int_cst (integer_type_ग्रन्थिः,
				  annot_व्यञ्जकम्_ivdep_kind),
		   integer_zero_ग्रन्थिः);
  जइ (unroll && cond != error_mark_ग्रन्थिः)
    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
		   build_int_cst (integer_type_ग्रन्थिः,
				  annot_व्यञ्जकम्_unroll_kind),
 		   build_int_cst (integer_type_ग्रन्थिः, unroll));
  जइ (novector && cond != error_mark_ग्रन्थिः)
    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
		   build_int_cst (integer_type_ग्रन्थिः,
				  annot_व्यञ्जकम्_no_vector_kind),
		   integer_zero_ग्रन्थिः);
  जइ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  add_stmt (build_stmt (loc, DO_STMT, cond, body, loop_name));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
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

स्थिर शून्य
c_parser_for_statement (c_parser *parser, तार्किक ivdep, unsigned short unroll,
			तार्किक novector, तार्किक *if_p, वृक्षः before_labels)
{
  वृक्षः block, cond, incr, body;
  unsigned वर्ण save_in_statement;
  वृक्षः save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  वृक्षः object_expression;
  /* Silence the bogus uninitialized warning.  */
  वृक्षः collection_expression = रिक्त;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  तार्किक is_foreach_statement = मिच्छ;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  वृक्षः loop_name;
  पूर्णाङ्क अङ्कः_names = c_get_loop_names (before_labels, मिच्छ, &loop_name);

  जइ (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = सच्च;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_ग्रन्थिः;
  incr = error_mark_ग्रन्थिः;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_ग्रन्थिः;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = मिच्छ;
	  c_parser_consume_token (parser);
	  c_finish_व्यञ्जकम्_stmt (loc, NULL_वृक्षः);
	}
      अण्णहा जइ (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, सच्च, सच्च,
					 मिच्छ, &object_expression);
	  parser->objc_could_be_foreach_context = मिच्छ;

	  जइ (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = सच्च;
	      जइ (check_for_loop_decls (for_loc, सच्च) == NULL_वृक्षः)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  अण्णहा
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  जाव (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  जइ (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      पूर्णाङ्क ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, सच्च,
					     सच्च, मिच्छ, &object_expression);
	      parser->objc_could_be_foreach_context = मिच्छ;

	      restore_extension_diagnostics (ext);
	      जइ (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = सच्च;
		  जइ (check_for_loop_decls (for_loc, सच्च) == NULL_वृक्षः)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      अण्णहा
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  अण्णहा
	    गच्छ init_व्यञ्जकम्;
	}
      अण्णहा
	{
	init_व्यञ्जकम्:
	  {
	    संरचना c_व्यञ्जकम् ce;
	    वृक्षः init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.मानम्;
	    parser->objc_could_be_foreach_context = मिच्छ;
	    जइ (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = सच्च;
		जइ (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, मिच्छ, रिक्त);
	      }
	    अण्णहा
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, सच्च, मिच्छ);
		init_expression = ce.मानम्;
		c_finish_व्यञ्जकम्_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      जइ (!is_foreach_statement)
	{
	  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      जइ (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_ग्रन्थिः;
		}
	      अण्णहा जइ (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_ग्रन्थिः;
		}
	      अण्णहा
		{
		  c_parser_consume_token (parser);
		  cond = NULL_वृक्षः;
		}
	    }
	  अण्णहा
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  जइ (ivdep && cond != error_mark_ग्रन्थिः)
	    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
			   build_int_cst (integer_type_ग्रन्थिः,
					  annot_व्यञ्जकम्_ivdep_kind),
			   integer_zero_ग्रन्थिः);
	  जइ (unroll && cond != error_mark_ग्रन्थिः)
	    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
 			   build_int_cst (integer_type_ग्रन्थिः,
					  annot_व्यञ्जकम्_unroll_kind),
			   build_int_cst (integer_type_ग्रन्थिः, unroll));
	  जइ (novector && cond && cond != error_mark_ग्रन्थिः)
	    cond = build3 (ANNOTATE_व्यञ्जकम्, वृक्षः_TYPE (cond), cond,
			   build_int_cst (integer_type_ग्रन्थिः,
					  annot_व्यञ्जकम्_no_vector_kind),
			   integer_zero_ग्रन्थिः);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  जइ (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_ग्रन्थिः;
	    }
	  अण्णहा
	    incr = c_process_व्यञ्जकम्_stmt (loc, NULL_वृक्षः);
	}
      अण्णहा
	{
	  जइ (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).मानम्, मिच्छ, रिक्त);
	  अण्णहा
	    {
	      संरचना c_व्यञ्जकम् ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, सच्च, मिच्छ);
	      incr = c_process_व्यञ्जकम्_stmt (loc, ce.मानम्);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  जइ (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      जइ (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  अण्णहा
    in_statement = IN_ITERATION_STMT;
  जइ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  तार्किक open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  जइ (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_वृक्षः;
      DECL_CHAIN (objc_foreach_break_label) = NULL_वृक्षः;
    }

  जइ (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  अण्णहा
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_वृक्षः, cond, incr,
			  body, NULL_वृक्षः,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_वृक्षः, NULL_वृक्षः, NULL_वृक्षः));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  जइ (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  जइ (अङ्कः_names)
    c_release_loop_names (अङ्कः_names);
  जइ (is_foreach_statement)
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

स्थिर वृक्षः
c_parser_asm_statement (c_parser *parser)
{
  वृक्षः str, outputs, inputs, clobbers, labels, ret;
  तार्किक simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  पूर्णाङ्क section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  प्रति (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      विकल्प (token->keyword)
	{
	पक्ष RID_VOLATILE:
	  जइ (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मानम्);
	      inform (volatile_loc, "first seen here");
	    }
	  अण्णहा
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  अनुवर्त;

	पक्ष RID_INLINE:
	  जइ (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मानम्);
	      inform (inline_loc, "first seen here");
	    }
	  अण्णहा
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  अनुवर्त;

	पक्ष RID_GOTO:
	  जइ (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मानम्);
	      inform (goto_loc, "first seen here");
	    }
	  अण्णहा
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  अनुवर्त;

	पक्ष RID_CONST:
	पक्ष RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->मानम्);
	  c_parser_consume_token (parser);
	  अनुवर्त;

	स्वभाव:
	  भङ्ग;
	}
      भङ्ग;
    }

  तार्किक is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  तार्किक is_inline = (inline_loc != UNKNOWN_LOCATION);
  तार्किक is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = रिक्त;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    गच्छ error;

  str = c_parser_asm_string_literal (parser);
  जइ (str == NULL_वृक्षः)
    गच्छ error_close_paren;

  simple = सच्च;
  outputs = NULL_वृक्षः;
  inputs = NULL_वृक्षः;
  clobbers = NULL_वृक्षः;
  labels = NULL_वृक्षः;

  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    गच्छ done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  प्रति (section = 0; section < nsections; ++section)
    {
      जइ (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  जइ (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      गच्छ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	गच्छ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = मिच्छ;

      जइ ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	विकल्प (section)
	  {
	  पक्ष 0:
	    outputs = c_parser_asm_operands (parser);
	    भङ्ग;
	  पक्ष 1:
	    inputs = c_parser_asm_operands (parser);
	    भङ्ग;
	  पक्ष 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    भङ्ग;
	  पक्ष 3:
	    labels = c_parser_asm_goto_operands (parser);
	    भङ्ग;
	  स्वभाव:
	    gcc_unreachable ();
	  }

      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	गच्छ done_asm;
    }

 done_asm:
  जइ (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      गच्छ error;
    }

  जइ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_व्यञ्जकम् (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  प्रत्यागम ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
  गच्छ error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

स्थिर वृक्षः
c_parser_asm_operands (c_parser *parser)
{
  वृक्षः list = NULL_वृक्षः;
  जाव (सच्च)
    {
      वृक्षः name, str;
      संरचना c_व्यञ्जकम् व्यञ्जकम्;
      जइ (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      वृक्षः id = c_parser_peek_token (parser)->मानम्;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  अण्णहा
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, रिक्त);
	      प्रत्यागम NULL_वृक्षः;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      अण्णहा
	name = NULL_वृक्षः;
      str = c_parser_asm_string_literal (parser);
      जइ (str == NULL_वृक्षः)
	प्रत्यागम NULL_वृक्षः;
      matching_parens parens;
      जइ (!parens.require_open (parser))
	प्रत्यागम NULL_वृक्षः;
      व्यञ्जकम् = c_parser_expression (parser);
      mark_exp_read (व्यञ्जकम्.मानम्);
      जइ (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  प्रत्यागम NULL_वृक्षः;
	}
      list = chainon (list, build_वृक्षः_list (build_वृक्षः_list (name, str),
					     व्यञ्जकम्.मानम्));
      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }
  प्रत्यागम list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

स्थिर वृक्षः
c_parser_asm_clobbers (c_parser *parser)
{
  वृक्षः list = NULL_वृक्षः;
  जाव (सच्च)
    {
      वृक्षः str = c_parser_asm_string_literal (parser);
      जइ (str)
	list = वृक्षः_cons (NULL_वृक्षः, str, list);
      अण्णहा
	प्रत्यागम NULL_वृक्षः;
      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }
  प्रत्यागम list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

स्थिर वृक्षः
c_parser_asm_goto_operands (c_parser *parser)
{
  वृक्षः list = NULL_वृक्षः;
  जाव (सच्च)
    {
      वृक्षः name, label;

      जइ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->मानम्;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  वृक्षः_USED (label) = 1;
	}
      अण्णहा
	{
	  c_parser_error (parser, "expected identifier");
	  प्रत्यागम NULL_वृक्षः;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = वृक्षः_cons (name, label, list);
      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	प्रत्यागम nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

संरचना c_व्यञ्जकम्
c_parser_string_literal (c_parser *parser, तार्किक translate, तार्किक wide_ok)
{
  संरचना c_व्यञ्जकम् ret;
  size_t गणनम्;
  संरचना obstack str_ob;
  संरचना obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  गणना cpp_ttype type;
  वृक्षः मानम्, string_वृक्षः;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (पङ्क्तिः_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   रिक्त);
  type = tok->type;
  विकल्प (type)
    {
    पक्ष CPP_STRING:
    पक्ष CPP_WSTRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_UTF8STRING:
      string_वृक्षः = tok->मानम्;
      भङ्ग;

    स्वभाव:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.मानम् = NULL_वृक्षः;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_वृक्षः;
      प्रत्यागम ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  विकल्प (c_parser_peek_2nd_token (parser)->type)
    {
    स्वभाव:
      c_parser_consume_token (parser);
      str.text = (ध्रुव unsigned वर्ण *) वृक्षः_STRING_POINTER (string_वृक्षः);
      str.len = वृक्षः_STRING_LENGTH (string_वृक्षः);
      गणनम् = 1;
      strs = &str;
      भङ्ग;

    पक्ष CPP_STRING:
    पक्ष CPP_WSTRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      गणनम् = 0;
      करेहि
	{
	  c_parser_consume_token (parser);
	  गणनम्++;
	  str.text = (ध्रुव unsigned वर्ण *) वृक्षः_STRING_POINTER (string_वृक्षः);
	  str.len = वृक्षः_STRING_LENGTH (string_वृक्षः);
	  जइ (type != tok->type)
	    {
	      जइ (type == CPP_STRING)
		type = tok->type;
	      अण्णहा जइ (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, परिमाण (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, परिमाण (location_t));
	  tok = c_parser_peek_token (parser);
	  string_वृक्षः = tok->मानम्;
	  last_tok_loc
	    = linemap_resolve_location (पङ्क्तिः_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, रिक्त);
	}
      जाव (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  जइ (गणनम् > 1 && !in_system_header_at (निवेशः_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  जइ ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, गणनम्, &istr, type)))
    {
      मानम् = build_string (istr.len, (ध्रुव वर्ण *) istr.text);
      मुक्त (const_cast<unsigned वर्ण *> (istr.text));
      जइ (गणनम् > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (गणनम्, locs);
	}
    }
  अण्णहा
    {
      जइ (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      विकल्प (type)
	{
	स्वभाव:
	पक्ष CPP_STRING:
	पक्ष CPP_UTF8STRING:
	  जइ (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      मानम् = build_string (TYPE_PRECISION (char8_type_ग्रन्थिः)
				    / TYPE_PRECISION (char_type_ग्रन्थिः),
				    "");  /* char8_t is 8 bits */
	    }
	  अण्णहा
	    मानम् = build_string (1, "");
	  भङ्ग;
	पक्ष CPP_STRING16:
	  मानम् = build_string (TYPE_PRECISION (char16_type_ग्रन्थिः)
				/ TYPE_PRECISION (char_type_ग्रन्थिः),
				"\0");  /* char16_t is 16 bits */
	  भङ्ग;
	पक्ष CPP_STRING32:
	  मानम् = build_string (TYPE_PRECISION (char32_type_ग्रन्थिः)
				/ TYPE_PRECISION (char_type_ग्रन्थिः),
				"\0\0\0");  /* char32_t is 32 bits */
	  भङ्ग;
	पक्ष CPP_WSTRING:
	  मानम् = build_string (TYPE_PRECISION (wchar_type_ग्रन्थिः)
				/ TYPE_PRECISION (char_type_ग्रन्थिः),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  भङ्ग;
        }
    }

  विकल्प (type)
    {
    स्वभाव:
    पक्ष CPP_STRING:
      वृक्षः_TYPE (मानम्) = char_array_type_ग्रन्थिः;
      भङ्ग;
    पक्ष CPP_UTF8STRING:
      जइ (flag_char8_t)
	वृक्षः_TYPE (मानम्) = char8_array_type_ग्रन्थिः;
      अण्णहा
	वृक्षः_TYPE (मानम्) = char_array_type_ग्रन्थिः;
      भङ्ग;
    पक्ष CPP_STRING16:
      वृक्षः_TYPE (मानम्) = char16_array_type_ग्रन्थिः;
      भङ्ग;
    पक्ष CPP_STRING32:
      वृक्षः_TYPE (मानम्) = char32_array_type_ग्रन्थिः;
      भङ्ग;
    पक्ष CPP_WSTRING:
      वृक्षः_TYPE (मानम्) = wchar_array_type_ग्रन्थिः;
    }
  मानम् = fix_string_type (मानम्);

  जइ (गणनम् > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.मानम् = मानम्;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_वृक्षः;
  set_c_व्यञ्जकम्_source_range (&ret, get_range_from_loc (पङ्क्तिः_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = सच्च;
  प्रत्यागम ret;
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_व्यञ्जकम्_no_commas (c_parser *parser, संरचना c_व्यञ्जकम् *after,
			 वृक्षः omp_atomic_lhs)
{
  संरचना c_व्यञ्जकम् lhs, rhs, ret;
  गणना वृक्षः_code code;
  location_t op_location, exp_location;
  तार्किक save_in_omp_for = c_in_omp_for;
  c_in_omp_for = मिच्छ;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_EQ:
      code = NOP_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MULT_EQ:
      code = MULT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_DIV_EQ:
      code = TRUNC_DIV_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MOD_EQ:
      code = TRUNC_MOD_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_PLUS_EQ:
      code = PLUS_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MINUS_EQ:
      code = MINUS_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_LSHIFT_EQ:
      code = LSHIFT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_RSHIFT_EQ:
      code = RSHIFT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_AND_EQ:
      code = BIT_AND_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_XOR_EQ:
      code = BIT_XOR_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_OR_EQ:
      code = BIT_IOR_व्यञ्जकम्;
      भङ्ग;
    स्वभाव:
      c_in_omp_for = save_in_omp_for;
      प्रत्यागम lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, सच्च, सच्च);

  ret.मानम् = build_modify_व्यञ्जकम् (op_location, lhs.मानम्, lhs.original_type,
				 code, exp_location, rhs.मानम्,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_व्यञ्जकम्_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  जइ (code == NOP_व्यञ्जकम्)
    ret.original_code = MODIFY_व्यञ्जकम्;
  अण्णहा
    {
      suppress_warning (ret.मानम्, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = रिक्त;
  c_in_omp_for = save_in_omp_for;
  प्रत्यागम ret;
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_conditional_expression (c_parser *parser, संरचना c_व्यञ्जकम् *after,
				 वृक्षः omp_atomic_lhs)
{
  संरचना c_व्यञ्जकम् cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_द्विमान_expression (parser, after, omp_atomic_lhs);

  जइ (c_parser_next_token_is_not (parser, CPP_QUERY))
    प्रत्यागम cond;
  c_omp_array_section_p = मिच्छ;
  जइ (cond.मानम् != error_mark_ग्रन्थिः)
    start = cond.get_start ();
  अण्णहा
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, सच्च, सच्च);
  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is (parser, CPP_COLON))
    {
      वृक्षः eptype = NULL_वृक्षः;

      location_t मध्यः_loc = c_parser_peek_token (parser)->location;
      pedwarn (मध्यः_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      जइ (वृक्षः_CODE (cond.मानम्) == EXCESS_PRECISION_व्यञ्जकम्)
	{
	  eptype = वृक्षः_TYPE (cond.मानम्);
	  cond.मानम् = वृक्षः_OPERAND (cond.मानम्, 0);
	}
      वृक्षः e = cond.मानम्;
      जाव (वृक्षः_CODE (e) == COMPOUND_व्यञ्जकम्)
	e = वृक्षः_OPERAND (e, 1);
      warn_for_omitted_condop (मध्यः_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.मानम् = save_व्यञ्जकम् (default_conversion (cond.मानम्));
      जइ (eptype)
	exp1.मानम् = build1 (EXCESS_PRECISION_व्यञ्जकम्, eptype, exp1.मानम्);
      exp1.original_type = रिक्त;
      exp1.src_range = cond.src_range;
      cond.मानम् = c_objc_common_truthvalue_conversion (cond_loc, exp1.मानम्);
      c_inhibit_evaluation_warnings += cond.मानम् == truthvalue_true_ग्रन्थिः;
    }
  अण्णहा
    {
      cond.मानम्
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.मानम्));
      c_inhibit_evaluation_warnings += cond.मानम् == truthvalue_false_ग्रन्थिः;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.मानम्);
      c_inhibit_evaluation_warnings +=
	((cond.मानम् == truthvalue_true_ग्रन्थिः)
	 - (cond.मानम् == truthvalue_false_ग्रन्थिः));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.मानम् == truthvalue_true_ग्रन्थिः;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      c_omp_array_section_p = save_c_omp_array_section_p;
      प्रत्यागम ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, रिक्त, NULL_वृक्षः);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, सच्च, सच्च);
  }
  c_inhibit_evaluation_warnings -= cond.मानम् == truthvalue_true_ग्रन्थिः;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  जइ (UNLIKELY (omp_atomic_lhs != रिक्त)
      && (वृक्षः_CODE (cond.मानम्) == GT_व्यञ्जकम्
	  || वृक्षः_CODE (cond.मानम्) == LT_व्यञ्जकम्
	  || वृक्षः_CODE (cond.मानम्) == EQ_व्यञ्जकम्)
      && c_वृक्षः_equal (exp2.मानम्, omp_atomic_lhs)
      && (c_वृक्षः_equal (वृक्षः_OPERAND (cond.मानम्, 0), omp_atomic_lhs)
	  || c_वृक्षः_equal (वृक्षः_OPERAND (cond.मानम्, 1), omp_atomic_lhs)))
    ret.मानम् = build3_loc (colon_loc, COND_व्यञ्जकम्, वृक्षः_TYPE (omp_atomic_lhs),
			    cond.मानम्, exp1.मानम्, exp2.मानम्);
  अण्णहा
    ret.मानम्
      = build_conditional_व्यञ्जकम् (colon_loc, cond.मानम्,
				cond.original_code == C_MAYBE_CONST_व्यञ्जकम्,
				exp1.मानम्, exp1.original_type, loc1,
				exp2.मानम्, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  जइ (exp1.मानम् == error_mark_ग्रन्थिः || exp2.मानम् == error_mark_ग्रन्थिः)
    ret.original_type = रिक्त;
  अण्णहा
    {
      वृक्षः t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : वृक्षः_TYPE (exp1.मानम्);
      t2 = exp2.original_type ? exp2.original_type : वृक्षः_TYPE (exp2.मानम्);
      ret.original_type = ((t1 != error_mark_ग्रन्थिः
			    && t2 != error_mark_ग्रन्थिः
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : रिक्त);
    }
  set_c_व्यञ्जकम्_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  प्रत्यागम ret;
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_द्विमान_expression (c_parser *parser, संरचना c_व्यञ्जकम् *after,
			    वृक्षः omp_atomic_lhs)
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

  संरचना {
    /* The expression at this stack level.  */
    संरचना c_व्यञ्जकम् व्यञ्जकम्;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    गणना c_parser_prec prec;
    /* The operation on its left.  */
    गणना वृक्षः_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    वृक्षः sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    वृक्षः orig_व्यञ्जकम्;
  } राशिः[अङ्कः_PRECS];
  पूर्णाङ्क sp;
  /* Location of the binary operator.  */
  location_t द्विमान_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define निष्कासय_2								      \
  करेहि {									      \
    विकल्प (राशिः[sp].op)						      \
      {									      \
      पक्ष TRUTH_ANDIF_व्यञ्जकम्:						      \
	c_inhibit_evaluation_warnings -= (राशिः[sp - 1].व्यञ्जकम्.मानम्	      \
					  == truthvalue_false_ग्रन्थिः);	      \
	भङ्ग;								      \
      पक्ष TRUTH_ORIF_व्यञ्जकम्:						      \
	c_inhibit_evaluation_warnings -= (राशिः[sp - 1].व्यञ्जकम्.मानम्	      \
					  == truthvalue_true_ग्रन्थिः);	      \
	भङ्ग;								      \
      पक्ष TRUNC_DIV_व्यञ्जकम्:						      \
	जइ ((राशिः[sp - 1].व्यञ्जकम्.original_code == SIZEOF_व्यञ्जकम्		      \
	     || राशिः[sp - 1].व्यञ्जकम्.original_code == PAREN_SIZEOF_व्यञ्जकम्)	      \
	    && (राशिः[sp].व्यञ्जकम्.original_code == SIZEOF_व्यञ्जकम्		      \
		|| राशिः[sp].व्यञ्जकम्.original_code == PAREN_SIZEOF_व्यञ्जकम्))	      \
	  {								      \
	    वृक्षः type0 = राशिः[sp - 1].sizeof_arg;			      \
	    वृक्षः type1 = राशिः[sp].sizeof_arg;				      \
	    वृक्षः first_arg = type0;					      \
	    जइ (!TYPE_P (type0))					      \
	      type0 = वृक्षः_TYPE (type0);				      \
	    जइ (!TYPE_P (type1))					      \
	      type1 = वृक्षः_TYPE (type1);				      \
	    जइ (POINTER_TYPE_P (type0)					      \
		&& comptypes (वृक्षः_TYPE (type0), type1)			      \
		&& !(वृक्षः_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		जइ (warning_at (राशिः[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  जइ (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    अण्णहा जइ (वृक्षः_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (वृक्षः_TYPE (type0)))  \
		     && राशिः[sp].व्यञ्जकम्.original_code != PAREN_SIZEOF_व्यञ्जकम्)    \
	      maybe_warn_sizeof_array_div (राशिः[sp].loc, first_arg, type0,   \
					   राशिः[sp].sizeof_arg, type1);      \
	  }								      \
	भङ्ग;								      \
      स्वभाव:								      \
	भङ्ग;								      \
      }									      \
    राशिः[sp - 1].व्यञ्जकम्							      \
      = convert_lvalue_to_rvalue (राशिः[sp - 1].loc,			      \
				  राशिः[sp - 1].व्यञ्जकम्, सच्च, सच्च);	      \
    राशिः[sp].व्यञ्जकम्							      \
      = convert_lvalue_to_rvalue (राशिः[sp].loc,			      \
				  राशिः[sp].व्यञ्जकम्, सच्च, सच्च);		      \
    जइ (UNLIKELY (omp_atomic_lhs != NULL_वृक्षः) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << राशिः[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_ग्रन्थिः			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (राशिः[sp].prec == PREC_REL || राशिः[sp].prec == PREC_EQ)))\
	&& राशिः[sp].op != TRUNC_MOD_व्यञ्जकम्				      \
	&& राशिः[sp].op != GE_व्यञ्जकम्					      \
	&& राशिः[sp].op != LE_व्यञ्जकम्					      \
	&& राशिः[sp].op != NE_व्यञ्जकम्					      \
	&& राशिः[0].व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः			      \
	&& राशिः[1].व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः			      \
	&& (omp_atomic_lhs == void_list_ग्रन्थिः				      \
	    || c_वृक्षः_equal (राशिः[0].व्यञ्जकम्.मानम्, omp_atomic_lhs)	      \
	    || c_वृक्षः_equal (राशिः[1].व्यञ्जकम्.मानम्, omp_atomic_lhs)	      \
	    || (राशिः[sp].op == EQ_व्यञ्जकम्					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	वृक्षः t = make_ग्रन्थिः (राशिः[1].op);				      \
	वृक्षः_TYPE (t) = वृक्षः_TYPE (राशिः[0].व्यञ्जकम्.मानम्);		      \
	वृक्षः_OPERAND (t, 0) = राशिः[0].व्यञ्जकम्.मानम्;			      \
	वृक्षः_OPERAND (t, 1) = राशिः[1].व्यञ्जकम्.मानम्;			      \
	राशिः[0].व्यञ्जकम्.मानम् = t;					      \
	राशिः[0].व्यञ्जकम्.m_decimal = 0;					      \
      }									      \
    अण्णहा								      \
      राशिः[sp - 1].व्यञ्जकम् = parser_build_द्विमान_op (राशिः[sp].loc,	      \
						   राशिः[sp].op,	      \
						   राशिः[sp - 1].व्यञ्जकम्,	      \
						   राशिः[sp].व्यञ्जकम्,	      \
						   राशिः[sp - 1].orig_व्यञ्जकम्);  \
    राशिः[sp - 1].orig_व्यञ्जकम् = NULL_वृक्षः;				      \
    sp--;								      \
  } जाव (0)
  gcc_assert (!after || c_dialect_objc ());
  राशिः[0].loc = c_parser_peek_token (parser)->location;
  राशिः[0].व्यञ्जकम् = c_parser_cast_expression (parser, after);
  राशिः[0].prec = PREC_NONE;
  राशिः[0].sizeof_arg = c_last_sizeof_arg;
  राशिः[0].orig_व्यञ्जकम् = NULL_वृक्षः;
  sp = 0;
  जाव (सच्च)
    {
      गणना c_parser_prec oprec;
      गणना वृक्षः_code ocode;
      source_range src_range;
      जइ (parser->error)
	गच्छ out;
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_व्यञ्जकम्;
	  भङ्ग;
	स्वभाव:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  गच्छ out;
	}
      द्विमान_loc = c_parser_peek_token (parser)->location;
      जाव (oprec <= राशिः[sp].prec)
	निष्कासय_2;
      c_parser_consume_token (parser);
      विकल्प (ocode)
	{
	पक्ष TRUTH_ANDIF_व्यञ्जकम्:
	  src_range = राशिः[sp].व्यञ्जकम्.src_range;
	  राशिः[sp].व्यञ्जकम्
	    = convert_lvalue_to_rvalue (राशिः[sp].loc,
					राशिः[sp].व्यञ्जकम्, सच्च, सच्च);
	  राशिः[sp].orig_व्यञ्जकम् = राशिः[sp].व्यञ्जकम्.मानम्;
	  राशिः[sp].व्यञ्जकम्.मानम् = c_objc_common_truthvalue_conversion
	    (राशिः[sp].loc, default_conversion (राशिः[sp].व्यञ्जकम्.मानम्));
	  c_inhibit_evaluation_warnings += (राशिः[sp].व्यञ्जकम्.मानम्
					    == truthvalue_false_ग्रन्थिः);
	  set_c_व्यञ्जकम्_source_range (&राशिः[sp].व्यञ्जकम्, src_range);
	  भङ्ग;
	पक्ष TRUTH_ORIF_व्यञ्जकम्:
	  src_range = राशिः[sp].व्यञ्जकम्.src_range;
	  राशिः[sp].व्यञ्जकम्
	    = convert_lvalue_to_rvalue (राशिः[sp].loc,
					राशिः[sp].व्यञ्जकम्, सच्च, सच्च);
	  राशिः[sp].orig_व्यञ्जकम् = राशिः[sp].व्यञ्जकम्.मानम्;
	  राशिः[sp].व्यञ्जकम्.मानम् = c_objc_common_truthvalue_conversion
	    (राशिः[sp].loc, default_conversion (राशिः[sp].व्यञ्जकम्.मानम्));
	  c_inhibit_evaluation_warnings += (राशिः[sp].व्यञ्जकम्.मानम्
					    == truthvalue_true_ग्रन्थिः);
	  set_c_व्यञ्जकम्_source_range (&राशिः[sp].व्यञ्जकम्, src_range);
	  भङ्ग;
	स्वभाव:
	  भङ्ग;
	}
      sp++;
      राशिः[sp].loc = द्विमान_loc;
      राशिः[sp].व्यञ्जकम् = c_parser_cast_expression (parser, रिक्त);
      राशिः[sp].prec = oprec;
      राशिः[sp].op = ocode;
      राशिः[sp].sizeof_arg = c_last_sizeof_arg;
      राशिः[sp].orig_व्यञ्जकम् = NULL_वृक्षः;
    }
 out:
  जाव (sp > 0)
    निष्कासय_2;
  प्रत्यागम राशिः[0].व्यञ्जकम्;
#undef निष्कासय_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

स्थिर संरचना c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  तार्किक seen_scspec = मिच्छ;
  संरचना c_declspecs *specs = build_null_declspecs ();
  जाव (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_CONSTEXPR:
	पक्ष RID_REGISTER:
	पक्ष RID_STATIC:
	पक्ष RID_THREAD:
	  seen_scspec = सच्च;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->मानम्);
	  c_parser_consume_token (parser);
	  भङ्ग;
	स्वभाव:
	  गच्छ out;
	}
    }
 out:
  प्रत्यागम seen_scspec ? specs : रिक्त;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

स्थिर संरचना c_व्यञ्जकम्
c_parser_cast_expression (c_parser *parser, संरचना c_व्यञ्जकम् *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  जइ (after)
    प्रत्यागम c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      संरचना c_declspecs *scspecs;
      संरचना c_type_name *type_name;
      संरचना c_व्यञ्जकम् ret;
      संरचना c_व्यञ्जकम् व्यञ्जकम्;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, सच्च);
      parens.skip_until_found_close (parser);
      जइ (type_name == रिक्त)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = रिक्त;
	  प्रत्यागम ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_निवेशय (type_name->specs->type);

      जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	प्रत्यागम c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      जइ (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      जइ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
	व्यञ्जकम् = c_parser_cast_expression (parser, रिक्त);
	व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, सच्च, सच्च);
      }
      ret.मानम् = c_cast_व्यञ्जकम् (cast_loc, type_name, व्यञ्जकम्.मानम्);
      जइ (ret.मानम् && व्यञ्जकम्.मानम्)
	set_c_व्यञ्जकम्_source_range (&ret, cast_loc, व्यञ्जकम्.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      प्रत्यागम ret;
    }
  अण्णहा
    प्रत्यागम c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

स्थिर शून्य
mark_exp_read_cond (वृक्षः exp)
{
  जइ ((VAR_P (exp) || वृक्षः_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    प्रत्यागम;

  mark_exp_read (exp);
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_unary_expression (c_parser *parser)
{
  पूर्णाङ्क ext;
  संरचना c_व्यञ्जकम् ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = रिक्त;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      mark_exp_read_cond (op.मानम्);
      op = default_function_array_conversion (exp_loc, op);
      प्रत्यागम parser_build_unary_op (op_loc, PREINCREMENT_व्यञ्जकम्, op);
    पक्ष CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      mark_exp_read_cond (op.मानम्);
      op = default_function_array_conversion (exp_loc, op);
      प्रत्यागम parser_build_unary_op (op_loc, PREDECREMENT_व्यञ्जकम्, op);
    पक्ष CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, रिक्त);
      mark_exp_read (op.मानम्);
      प्रत्यागम parser_build_unary_op (op_loc, ADDR_व्यञ्जकम्, op);
    पक्ष CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, रिक्त);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, सच्च, सच्च);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.मानम् = build_indirect_ref (combined_loc, op.मानम्, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	प्रत्यागम ret;
      }
    पक्ष CPP_PLUS:
      जइ (!c_dialect_objc () && !in_system_header_at (निवेशः_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      op = convert_lvalue_to_rvalue (exp_loc, op, सच्च, सच्च);
      प्रत्यागम parser_build_unary_op (op_loc, CONVERT_व्यञ्जकम्, op);
    पक्ष CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      op = convert_lvalue_to_rvalue (exp_loc, op, सच्च, सच्च);
      प्रत्यागम parser_build_unary_op (op_loc, NEGATE_व्यञ्जकम्, op);
    पक्ष CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      op = convert_lvalue_to_rvalue (exp_loc, op, सच्च, सच्च);
      प्रत्यागम parser_build_unary_op (op_loc, BIT_NOT_व्यञ्जकम्, op);
    पक्ष CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      op = convert_lvalue_to_rvalue (exp_loc, op, सच्च, सच्च);
      प्रत्यागम parser_build_unary_op (op_loc, TRUTH_NOT_व्यञ्जकम्, op);
    पक्ष CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.मानम् = finish_label_address_व्यञ्जकम्
	    (c_parser_peek_token (parser)->मानम्, op_loc);
	  set_c_व्यञ्जकम्_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      अण्णहा
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      प्रत्यागम ret;
    पक्ष CPP_KEYWORD:
      {
	गणना rid rid = c_parser_peek_token (parser)->keyword;
	विकल्प (rid)
	  {
	  पक्ष RID_COUNTOF:
	  पक्ष RID_SIZEOF:
	    प्रत्यागम c_parser_sizeof_or_countof_expression (parser, rid);
	  पक्ष RID_ALIGNOF:
	    प्रत्यागम c_parser_alignof_expression (parser);
	  पक्ष RID_MAXOF:
	  पक्ष RID_MINOF:
	    प्रत्यागम c_parser_maxof_or_minof_expression (parser, rid);
	  पक्ष RID_BUILTIN_HAS_ATTRIBUTE:
	    प्रत्यागम c_parser_has_attribute_expression (parser);
	  पक्ष RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, रिक्त);
	    restore_extension_diagnostics (ext);
	    प्रत्यागम ret;
	  पक्ष RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, रिक्त);
	    op = default_function_array_conversion (exp_loc, op);
	    प्रत्यागम parser_build_unary_op (op_loc, REALPART_व्यञ्जकम्, op);
	  पक्ष RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, रिक्त);
	    op = default_function_array_conversion (exp_loc, op);
	    प्रत्यागम parser_build_unary_op (op_loc, IMAGPART_व्यञ्जकम्, op);
	  पक्ष RID_TRANSACTION_ATOMIC:
	  पक्ष RID_TRANSACTION_RELAXED:
	    प्रत्यागम c_parser_transaction_expression (parser, rid);
	  पक्ष RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.मानम् = void_ग्रन्थिः;
	    set_c_व्यञ्जकम्_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    प्रत्यागम ret;
	  स्वभाव:
	    प्रत्यागम c_parser_postfix_expression (parser);
	  }
      }
    स्वभाव:
      प्रत्यागम c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_sizeof_or_countof_expression (c_parser *parser, गणना rid rid)
{
  ध्रुव वर्ण *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  संरचना c_व्यञ्जकम् result;
  location_t व्यञ्जकम्_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  जइ (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  जइ (rid == RID_COUNTOF)
    in_countof++;
  अण्णहा
    in_sizeof++;
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      संरचना c_declspecs *scspecs;
      संरचना c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, सच्च);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      जइ (type_name == रिक्त)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  व्यञ्जकम्.set_error ();
	  गच्छ Xof_व्यञ्जकम्;
	}
      जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  व्यञ्जकम् = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       व्यञ्जकम्_loc);
	  finish = व्यञ्जकम्.get_finish ();
	  गच्छ Xof_व्यञ्जकम्;
	}
      /* sizeof ( type-name ).  */
      जइ (scspecs)
	error_at (व्यञ्जकम्_loc, "storage class specifier in %qs", op_name);
      जइ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      जइ (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_व्यञ्जकम्_countof_type (व्यञ्जकम्_loc, type_name);
	}
      अण्णहा
	{
	  in_sizeof--;
	  result = c_व्यञ्जकम्_sizeof_type (व्यञ्जकम्_loc, type_name);
	}
    }
  अण्णहा
    {
      व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      व्यञ्जकम् = c_parser_unary_expression (parser);
      finish = व्यञ्जकम्.get_finish ();
    Xof_व्यञ्जकम्:
      c_inhibit_evaluation_warnings--;
      जइ (rid == RID_COUNTOF)
	in_countof--;
      अण्णहा
	in_sizeof--;
      mark_exp_read (व्यञ्जकम्.मानम्);
      जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्षः_OPERAND (व्यञ्जकम्.मानम्, 1)))
	error_at (व्यञ्जकम्_loc, "%qs applied to a bit-field", op_name);
      जइ (rid == RID_COUNTOF)
	result = c_व्यञ्जकम्_countof_व्यञ्जकम् (व्यञ्जकम्_loc, व्यञ्जकम्);
      अण्णहा
	result = c_व्यञ्जकम्_sizeof_व्यञ्जकम् (व्यञ्जकम्_loc, व्यञ्जकम्);
    }
  जइ (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_व्यञ्जकम्_source_range (&result, start, finish);
  प्रत्यागम result;
}

/* Parse an alignof expression.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_alignof_expression (c_parser *parser)
{
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  वृक्षः alignof_spelling = c_parser_peek_token (parser)->मानम्;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  तार्किक is_c11_alignof = (strcmp (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  जइ (is_c11_alignof)
    {
      जइ (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      अण्णहा
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      संरचना c_declspecs *scspecs;
      संरचना c_type_name *type_name;
      संरचना c_व्यञ्जकम् ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, सच्च);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      जइ (type_name == रिक्त)
	{
	  संरचना c_व्यञ्जकम् ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = रिक्त;
	  प्रत्यागम ret;
	}
      जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  व्यञ्जकम् = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  गच्छ alignof_व्यञ्जकम्;
	}
      /* alignof ( type-name ).  */
      जइ (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      जइ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.मानम् = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       रिक्त, रिक्त),
					    मिच्छ, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      set_c_व्यञ्जकम्_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      प्रत्यागम ret;
    }
  अण्णहा
    {
      संरचना c_व्यञ्जकम् ret;
      व्यञ्जकम् = c_parser_unary_expression (parser);
      end_loc = व्यञ्जकम्.src_range.m_finish;
    alignof_व्यञ्जकम्:
      mark_exp_read (व्यञ्जकम्.मानम्);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      जइ (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.मानम् = c_alignof_व्यञ्जकम् (start_loc, व्यञ्जकम्.मानम्);
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      set_c_व्यञ्जकम्_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      प्रत्यागम ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_maxof_or_minof_expression (c_parser *parser, गणना rid rid)
{
  ध्रुव वर्ण *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  संरचना c_व्यञ्जकम् result;
  location_t व्यञ्जकम्_loc;
  संरचना c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  जइ (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      गच्छ fail;
    }
  parens.consume_open (parser);
  व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
  जइ (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (व्यञ्जकम्_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      गच्छ fail;
    }
  type_name = c_parser_type_name (parser, सच्च);
  जइ (type_name == रिक्त)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      गच्छ fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  जइ (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  जइ (rid == RID_MAXOF)
    result = c_व्यञ्जकम्_maxof_type (व्यञ्जकम्_loc, type_name);
  अण्णहा
    result = c_व्यञ्जकम्_minof_type (व्यञ्जकम्_loc, type_name);
  set_c_व्यञ्जकम्_source_range (&result, start, finish);
  प्रत्यागम result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = रिक्त;
  प्रत्यागम result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      संरचना c_व्यञ्जकम् result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = रिक्त;
      प्रत्यागम result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  वृक्षः oper = NULL_वृक्षः;
  जइ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      संरचना c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      जइ (tname)
	{
	  oper = groktypename (tname, रिक्त, रिक्त);
	  निष्कासय_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  अण्णहा
    {
      संरचना c_व्यञ्जकम् cexpr = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      जइ (cexpr.मानम् != error_mark_ग्रन्थिः)
	{
	  mark_exp_read (cexpr.मानम्);
	  oper = cexpr.मानम्;
	  वृक्षः etype = वृक्षः_TYPE (oper);
	  तार्किक was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  जइ (was_vm)
	    oper = c_fully_fold (oper, मिच्छ, रिक्त);
	  निष्कासय_maybe_used (was_vm);
	}
    }

  संरचना c_व्यञ्जकम् result;
  result.original_code = ERROR_MARK;
  result.original_type = रिक्त;

  जइ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      प्रत्यागम result;
    }

  तार्किक save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  वृक्षः attr = c_parser_gnu_attribute (parser, NULL_वृक्षः, मिच्छ, मिच्छ);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  अण्णहा
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);

      result.set_error ();
      प्रत्यागम result;
    }

  जइ (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      प्रत्यागम result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_ग्रन्थिः;

  जइ (has_attribute (atloc, oper, attr, default_conversion))
    result.मानम् = boolean_true_ग्रन्थिः;
  अण्णहा
    result.मानम् =  boolean_false_ग्रन्थिः;

  set_c_व्यञ्जकम्_source_range (&result, start, finish);
  result.m_decimal = 0;
  प्रत्यागम result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
स्थिर तार्किक
c_parser_get_builtin_args (c_parser *parser, ध्रुव वर्ण *bname,
			   vec<c_व्यञ्जकम्_t, va_gc> **ret_cexpr_list,
			   तार्किक choose_व्यञ्जकम्_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
  c_व्यञ्जकम्_t व्यञ्जकम्;
  तार्किक saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = रिक्त;
  जइ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      प्रत्यागम मिच्छ;
    }

  c_parser_consume_token (parser);

  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      प्रत्यागम सच्च;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_व्यञ्जकम्_p;
  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_प्रक्षिप (cexpr_list, व्यञ्जकम्);
  जाव (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  वृक्षः मानम् = embed->मानम्;
	  व्यञ्जकम्.original_code = INTEGER_CST;
	  व्यञ्जकम्.original_type = integer_type_ग्रन्थिः;
	  व्यञ्जकम्.मानम् = NULL_वृक्षः;
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, embed->get_range ());
	  व्यञ्जकम्.m_decimal = 0;
	  प्रति (unsigned पूर्णाङ्क i = 0; i < (unsigned) RAW_DATA_LENGTH (मानम्); i++)
	    {
	      व्यञ्जकम्.मानम् = build_int_cst (integer_type_ग्रन्थिः,
					  RAW_DATA_UCHAR_ELT (मानम्, i));
	      vec_safe_प्रक्षिप (cexpr_list, व्यञ्जकम्);
	    }
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}
      व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      vec_safe_प्रक्षिप (cexpr_list, व्यञ्जकम्);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  जइ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम मिच्छ;

  *ret_cexpr_list = cexpr_list;
  प्रत्यागम सच्च;
}

/* This represents a single generic-association.  */

संरचना c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  वृक्षः type;
  /* The association's expression.  */
  संरचना c_व्यञ्जकम् expression;
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_generic_selection (c_parser *parser)
{
  संरचना c_व्यञ्जकम् selector, error_व्यञ्जकम्;
  वृक्षः selector_type;
  संरचना c_generic_association matched_assoc;
  पूर्णाङ्क match_found = -1;
  location_t generic_loc, selector_loc;

  error_व्यञ्जकम्.original_code = ERROR_MARK;
  error_व्यञ्जकम्.original_type = रिक्त;
  error_व्यञ्जकम्.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_वृक्षः;
  matched_assoc.expression = error_व्यञ्जकम्;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  जइ (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  अण्णहा
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम error_व्यञ्जकम्;

  selector_loc = c_parser_peek_token (parser)->location;
  जइ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      संरचना c_type_name *type = c_parser_type_name (parser);
      जइ (type)
	selector_type = groktypename (type, रिक्त, रिक्त);
      c_inhibit_evaluation_warnings--;
      जइ (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  प्रत्यागम error_व्यञ्जकम्;
	}
    }
  अण्णहा
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      निष्कासय_maybe_used (!flag_isoc23);

      जइ (selector.मानम् == error_mark_ग्रन्थिः)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  प्रत्यागम selector;
	}
      mark_exp_read (selector.मानम्);
      selector_type = वृक्षः_TYPE (selector.मानम्);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      जइ (वृक्षः_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      जइ (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (वृक्षः_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (वृक्षः_TYPE (selector_type)));
    }

  जइ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      प्रत्यागम error_व्यञ्जकम्;
    }

  auto_vec<c_generic_association> associations;
  संरचना maybe_used_decl *maybe_used_default = रिक्त;
  जाव (1)
    {
      संरचना c_generic_association assoc, *iter;
      unsigned पूर्णाङ्क ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      जइ (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_वृक्षः;
	}
      अण्णहा
	{
	  संरचना c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  जइ (type_name == रिक्त)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      प्रत्यागम error_व्यञ्जकम्;
	    }
	  assoc.type = grokgenassoc (type_name);
	  जइ (assoc.type == error_mark_ग्रन्थिः)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      प्रत्यागम error_व्यञ्जकम्;
	    }

	  जइ (वृक्षः_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  अण्णहा जइ (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  जइ (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  प्रत्यागम error_व्यञ्जकम्;
	}

      तार्किक match = assoc.type == NULL_वृक्षः
		   || comptypes (assoc.type, selector_type);

      जइ (!match || matched_assoc.type != NULL_वृक्षः)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);

      जइ (!match || matched_assoc.type != NULL_वृक्षः)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      जइ (!match)
	निष्कासय_maybe_used (!flag_isoc23);
      अण्णहा जइ (assoc.type == NULL_वृक्षः)
	maybe_used_default = save_maybe_used ();
      अण्णहा
	निष्कासय_maybe_used (सच्च);

      जइ (assoc.expression.मानम् == error_mark_ग्रन्थिः)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  प्रत्यागम error_व्यञ्जकम्;
	}

      प्रति (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  जइ (assoc.type == NULL_वृक्षः)
	    {
	      जइ (iter->type == NULL_वृक्षः)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  अण्णहा जइ (iter->type != NULL_वृक्षः)
	    {
	      जइ (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      जइ (assoc.type == NULL_वृक्षः)
	{
	  जइ (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      अण्णहा जइ (match)
	{
	  जइ (match_found < 0 || matched_assoc.type == NULL_वृक्षः)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  अण्णहा
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_प्रक्षिप (assoc);

      जइ (c_parser_peek_token (parser)->type != CPP_COMMA)
	भङ्ग;
      c_parser_consume_token (parser);
    }

  जइ (match_found >= 0 && matched_assoc.type == NULL_वृक्षः)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      निष्कासय_maybe_used (सच्च);
    }
  अण्णहा जइ (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      निष्कासय_maybe_used (!flag_isoc23);
    }

  unsigned पूर्णाङ्क ix;
  संरचना c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    जइ (ix != (unsigned) match_found)
      mark_exp_read (iter->expression.मानम्);

  जइ (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      प्रत्यागम error_व्यञ्जकम्;
    }

  जइ (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      प्रत्यागम error_व्यञ्जकम्;
    }

  प्रत्यागम matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

स्थिर unsigned पूर्णाङ्क
check_tgmath_function (c_व्यञ्जकम् *व्यञ्जकम्, unsigned पूर्णाङ्क pos)
{
  वृक्षः type = वृक्षः_TYPE (व्यञ्जकम्->मानम्);
  जइ (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (व्यञ्जकम्->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      प्रत्यागम 0;
    }
  type = वृक्षः_TYPE (type);
  जइ (!prototype_p (type))
    {
      error_at (व्यञ्जकम्->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      प्रत्यागम 0;
    }
  जइ (stdarg_p (type))
    {
      error_at (व्यञ्जकम्->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      प्रत्यागम 0;
    }
  unsigned पूर्णाङ्क nargs = 0;
  function_args_iterator iter;
  वृक्षः t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      जइ (t == void_type_ग्रन्थिः)
	भङ्ग;
      nargs++;
    }
  जइ (nargs == 0)
    {
      error_at (व्यञ्जकम्->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      प्रत्यागम 0;
    }
  प्रत्यागम nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
गणना tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  विकल्प (c_parser_peek_token (parser)->keyword)
    {
    पक्ष RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      भङ्ग;
    पक्ष RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      भङ्ग;
    पक्ष RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }

  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  व्यञ्जकम्.original_code = ERROR_MARK;
  व्यञ्जकम्.original_type = रिक्त;
  व्यञ्जकम्.मानम् = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->मानम्);
  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, loc);
  व्यञ्जकम्.m_decimal = 0;
  c_parser_consume_token (parser);
  प्रत्यागम व्यञ्जकम्;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

स्थिर तार्किक
has_counted_by_object (वृक्षः ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  जइ ((वृक्षः_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (वृक्षः_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    प्रत्यागम सच्च;
  प्रत्यागम मिच्छ;
}

/* Get the reference to the counted-by object associated with the REF.  */

स्थिर वृक्षः
get_counted_by_ref (वृक्षः ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  जइ (वृक्षः_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (वृक्षः_OPERAND (ref, 0)))
    प्रत्यागम CALL_व्यञ्जकम्_ARG (वृक्षः_OPERAND (ref, 0), 1);
  अण्णहा जइ (is_access_with_size_p (ref))
    प्रत्यागम CALL_व्यञ्जकम्_ARG (ref, 1);

  प्रत्यागम NULL_वृक्षः;
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_postfix_expression (c_parser *parser)
{
  संरचना c_व्यञ्जकम् व्यञ्जकम्, e1;
  संरचना c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  व्यञ्जकम्.original_code = ERROR_MARK;
  व्यञ्जकम्.original_type = रिक्त;
  व्यञ्जकम्.m_decimal = 0;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_सङ्ख्या:
      व्यञ्जकम्.मानम् = c_parser_peek_token (parser)->मानम्;
      set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
      loc = c_parser_peek_token (parser)->location;
      व्यञ्जकम्.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  व्यञ्जकम्.set_error ();
	}
      भङ्ग;
    पक्ष CPP_CHAR:
    पक्ष CPP_CHAR16:
    पक्ष CPP_CHAR32:
    पक्ष CPP_UTF8CHAR:
    पक्ष CPP_WCHAR:
      व्यञ्जकम्.मानम् = c_parser_peek_token (parser)->मानम्;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      व्यञ्जकम्.original_type = char_type_ग्रन्थिः;
      set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_STRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_WSTRING:
    पक्ष CPP_UTF8STRING:
      व्यञ्जकम् = c_parser_string_literal (parser, parser->translate_strings_p,
				      सच्च);
      भङ्ग;
    पक्ष CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      व्यञ्जकम्.मानम्
	= objc_build_string_object (c_parser_peek_token (parser)->मानम्);
      set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_NAME:
      विकल्प (c_parser_peek_token (parser)->id_kind)
	{
	पक्ष C_ID_ID:
	  {
	    वृक्षः id = c_parser_peek_token (parser)->मानम्;
	    c_parser_consume_token (parser);
	    व्यञ्जकम्.मानम् = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &व्यञ्जकम्.original_type);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
	    भङ्ग;
	  }
	पक्ष C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    वृक्षः class_name = c_parser_peek_token (parser)->मानम्;
	    वृक्षः component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    जइ (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->मानम्;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    व्यञ्जकम्.मानम् = objc_build_class_component_ref (class_name,
							 component);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, end_loc);
	    भङ्ग;
	  }
	स्वभाव:
	  c_parser_error (parser, "expected expression");
	  व्यञ्जकम्.set_error ();
	  भङ्ग;
	}
      भङ्ग;
    पक्ष CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      जइ (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  वृक्षः stmt;
	  location_t brace_loc;
	  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  जइ (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = सच्च;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      व्यञ्जकम्.set_error ();
	      भङ्ग;
	    }
	  c_omp_array_section_p = मिच्छ;
	  stmt = c_begin_stmt_व्यञ्जकम् ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  व्यञ्जकम्.मानम् = c_finish_stmt_व्यञ्जकम् (brace_loc, stmt);
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_loc);
	  mark_exp_read (व्यञ्जकम्.मानम्);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      अण्णहा
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  व्यञ्जकम् = c_parser_expression (parser);
	  जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) == MODIFY_व्यञ्जकम्)
	    suppress_warning (व्यञ्जकम्.मानम्, OPT_Wparentheses);
	  जइ (व्यञ्जकम्.original_code != C_MAYBE_CONST_व्यञ्जकम्
	      && व्यञ्जकम्.original_code != SIZEOF_व्यञ्जकम्)
	    व्यञ्जकम्.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  जइ (व्यञ्जकम्.original_code == SIZEOF_व्यञ्जकम्)
	    व्यञ्जकम्.original_code = PAREN_SIZEOF_व्यञ्जकम्;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      भङ्ग;
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_FUNCTION_NAME:
	पक्ष RID_PRETTY_FUNCTION_NAME:
	पक्ष RID_C99_FUNCTION_NAME:
	  व्यञ्जकम् = c_parser_predefined_identifier (parser);
	  भङ्ग;
	पक्ष RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    e1 = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	    mark_exp_read (e1.मानम्);
	    e1.मानम् = c_fully_fold (e1.मानम्, मिच्छ, रिक्त);
	    जइ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    जइ (t1 == रिक्त)
	      {
		व्यञ्जकम्.set_error ();
	      }
	    अण्णहा
	      {
		वृक्षः type_व्यञ्जकम् = NULL_वृक्षः;
		वृक्षः type = groktypename (t1, &type_व्यञ्जकम्, रिक्त);
		व्यञ्जकम्.मानम् = c_build_va_arg (start_loc, e1.मानम्, loc,
					     type, type_व्यञ्जकम्);
		set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start_loc, end_loc);
	      }
	  }
	  भङ्ग;
	पक्ष RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    e1 = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, सच्च, सच्च);
	    जइ (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		जइ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		    व्यञ्जकम्.set_error ();
		    भङ्ग;
		  }
		जइ (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    वृक्षः name = c_parser_peek_token (parser)->मानम्;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    वृक्षः decl = lookup_name (name);
		    वृक्षः last_parm
		      = वृक्षः_last (DECL_ARGUMENTS (current_function_decl));
		    जइ (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    अण्णहा जइ (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		अण्णहा
		  {
		    unsigned nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    जाव (सच्च)
		      {
			c_token *token = c_parser_peek_token (parser);
			जइ (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  भङ्ग;

			जइ (token->type == CPP_EOF)
			  भङ्ग;
			जइ (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			अण्णहा जइ (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    जइ (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    वृक्षः fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<वृक्षः, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_प्रक्षिप (e1.मानम्);
	    params->quick_प्रक्षिप (integer_zero_ग्रन्थिः);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_प्रक्षिप (e1.get_location ());
	    arg_loc.quick_प्रक्षिप (UNKNOWN_LOCATION);
	    व्यञ्जकम्.मानम् = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, रिक्त);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc,
				     parser->tokens_buf[0].get_finish ());
	    व्यञ्जकम्.m_decimal = 0;
	    व्यञ्जकम्.original_code = ERROR_MARK;
	    व्यञ्जकम्.original_type = रिक्त;
	    release_वृक्षः_vector (params);
	    भङ्ग;
	  }
	पक्ष RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    t1 = c_parser_type_name (parser);
	    जइ (t1 == रिक्त)
	      parser->error = सच्च;
	    जइ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    जइ (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    वृक्षः type = groktypename (t1, रिक्त, रिक्त);
	    वृक्षः offsetof_ref;
	    जइ (type == error_mark_ग्रन्थिः)
	      offsetof_ref = error_mark_ग्रन्थिः;
	    अण्णहा
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_ग्रन्थिः);
		SET_व्यञ्जकम्_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    जइ (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->मानम्,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		जाव (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    जइ (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_ग्रन्थिः);
			गच्छ do_dot;
		      }
		    अण्णहा जइ (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			जइ (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    भङ्ग;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->मानम्,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    अण्णहा
		      {
			संरचना c_व्यञ्जकम् ce;
			वृक्षः idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, मिच्छ, मिच्छ);
			idx = ce.मानम्;
			idx = c_fully_fold (idx, मिच्छ, रिक्त);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    अण्णहा
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    व्यञ्जकम्.मानम् = fold_offsetof (offsetof_ref);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, end_loc);
	  }
	  भङ्ग;
	पक्ष RID_CHOOSE_व्यञ्जकम्:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    c_व्यञ्जकम्_t *e1_p, *e2_p, *e3_p;
	    वृक्षः c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, सच्च,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    जइ (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->मानम्;
	    mark_exp_read (e2_p->मानम्);
	    mark_exp_read (e3_p->मानम्);
	    जइ (वृक्षः_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (वृक्षः_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    व्यञ्जकम् = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    भङ्ग;
	  }
	पक्ष RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    t1 = c_parser_type_name (parser);
	    जइ (t1 == रिक्त)
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    t2 = c_parser_type_name (parser);
	    जइ (t2 == रिक्त)
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    वृक्षः e1, e2;
	    e1 = groktypename (t1, रिक्त, रिक्त);
	    e2 = groktypename (t2, रिक्त, रिक्त);
	    जइ (e1 == error_mark_ग्रन्थिः || e2 == error_mark_ग्रन्थिः)
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    व्यञ्जकम्.मानम्
	      = comptypes (e1, e2) ? integer_one_ग्रन्थिः : integer_zero_ग्रन्थिः;
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	  }
	  भङ्ग;
	पक्ष RID_BUILTIN_TGMATH:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, मिच्छ,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    जइ (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    unsigned पूर्णाङ्क i;
	    c_व्यञ्जकम्_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, सच्च, सच्च);
	    unsigned पूर्णाङ्क nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    जइ (nargs == 0)
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    unsigned पूर्णाङ्क अङ्कः_functions = vec_safe_length (cexpr_list) - nargs;
	    जइ (अङ्कः_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    प्रति (unsigned पूर्णाङ्क j = 1; j < अङ्कः_functions; j++)
	      {
		unsigned पूर्णाङ्क this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		जइ (this_nargs == 0)
		  {
		    व्यञ्जकम्.set_error ();
		    गच्छ out;
		  }
		जइ (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    व्यञ्जकम्.set_error ();
		    गच्छ out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<गणना tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<वृक्षः> parm_first (nargs + 1);
	    auto_vec<तार्किक> parm_complex (nargs + 1);
	    auto_vec<तार्किक> parm_varies (nargs + 1);
	    वृक्षः first_type = वृक्षः_TYPE (वृक्षः_TYPE ((*cexpr_list)[0].मानम्));
	    वृक्षः first_ret = TYPE_MAIN_VARIANT (वृक्षः_TYPE (first_type));
	    parm_first.quick_प्रक्षिप (first_ret);
	    parm_complex.quick_प्रक्षिप (वृक्षः_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_प्रक्षिप (मिच्छ);
	    function_args_iterator iter;
	    वृक्षः t;
	    unsigned पूर्णाङ्क argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		जइ (t == void_type_ग्रन्थिः)
		  भङ्ग;
		parm_first.quick_प्रक्षिप (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_प्रक्षिप (वृक्षः_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_प्रक्षिप (मिच्छ);
	      }
	    प्रति (unsigned पूर्णाङ्क j = 1; j < अङ्कः_functions; j++)
	      {
		वृक्षः type = वृक्षः_TYPE (वृक्षः_TYPE ((*cexpr_list)[j].मानम्));
		वृक्षः ret = TYPE_MAIN_VARIANT (वृक्षः_TYPE (type));
		जइ (ret != parm_first[0])
		  {
		    parm_varies[0] = सच्च;
		    जइ (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		    जइ (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		  }
		जइ (वृक्षः_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = सच्च;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    जइ (t == void_type_ग्रन्थिः)
		      भङ्ग;
		    t = TYPE_MAIN_VARIANT (t);
		    जइ (t != parm_first[argpos])
		      {
			parm_varies[argpos] = सच्च;
			जइ (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    व्यञ्जकम्.set_error ();
			    गच्छ out;
			  }
			जइ (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    व्यञ्जकम्.set_error ();
			    गच्छ out;
			  }
		      }
		    जइ (वृक्षः_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = सच्च;
		    argpos++;
		  }
	      }
	    गणना tgmath_parm_kind max_variation = tgmath_fixed;
	    प्रति (unsigned पूर्णाङ्क j = 0; j <= nargs; j++)
	      {
		गणना tgmath_parm_kind this_kind;
		जइ (parm_varies[j])
		  {
		    जइ (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    अण्णहा
		      {
			this_kind = tgmath_real;
			जइ (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		अण्णहा
		  this_kind = tgmath_fixed;
		parm_kind.quick_प्रक्षिप (this_kind);
	      }
	    जइ (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    unsigned पूर्णाङ्क tgarg = 0;
	    प्रति (unsigned पूर्णाङ्क j = 1; j <= nargs; j++)
	      जइ (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  भङ्ग;
		}
	    जइ (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<वृक्षः> tg_type (अङ्कः_functions);
	    प्रति (unsigned पूर्णाङ्क j = 0; j < अङ्कः_functions; j++)
	      {
		वृक्षः type = वृक्षः_TYPE (वृक्षः_TYPE ((*cexpr_list)[j].मानम्));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    जइ (argpos == tgarg)
		      {
			tg_type.quick_प्रक्षिप (TYPE_MAIN_VARIANT (t));
			भङ्ग;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    तार्किक all_complex = सच्च;
	    तार्किक all_द्विमान = सच्च;
	    तार्किक all_decimal = सच्च;
	    hash_set<वृक्षः> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		जइ (वृक्षः_CODE (t) == COMPLEX_TYPE)
		  all_decimal = मिच्छ;
		अण्णहा
		  {
		    all_complex = मिच्छ;
		    जइ (DECIMAL_FLOAT_TYPE_P (t))
		      all_द्विमान = मिच्छ;
		    अण्णहा
		      all_decimal = मिच्छ;
		  }
		जइ (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    व्यञ्जकम्.set_error ();
		    गच्छ out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    प्रति (unsigned पूर्णाङ्क j = 0; j < अङ्कः_functions; j++)
	      {
		वृक्षः exp_type = tg_type[j];
		वृक्षः exp_real_type = exp_type;
		जइ (वृक्षः_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = वृक्षः_TYPE (exp_type);
		वृक्षः type = वृक्षः_TYPE (वृक्षः_TYPE ((*cexpr_list)[j].मानम्));
		वृक्षः ret = TYPE_MAIN_VARIANT (वृक्षः_TYPE (type));
		जइ ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    व्यञ्जकम्.set_error ();
		    गच्छ out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    जइ (t == void_type_ग्रन्थिः)
		      भङ्ग;
		    t = TYPE_MAIN_VARIANT (t);
		    जइ ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			व्यञ्जकम्.set_error ();
			गच्छ out;
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
	    तार्किक arg_complex = all_complex;
	    तार्किक arg_द्विमान = all_द्विमान;
	    तार्किक arg_int_decimal = all_decimal;
	    तार्किक arg_int_floatnx = मिच्छ;
	    तार्किक arg_int_decimalx = मिच्छ;
	    प्रति (unsigned पूर्णाङ्क j = 1; j <= nargs; j++)
	      {
		जइ (parm_kind[j] == tgmath_fixed)
		  अनुवर्त;
		c_व्यञ्जकम्_t *ce = &(*cexpr_list)[अङ्कः_functions + j - 1];
		वृक्षः type = वृक्षः_TYPE (ce->मानम्);
		जइ (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && वृक्षः_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    व्यञ्जकम्.set_error ();
		    गच्छ out;
		  }
		जइ (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = सच्च;
		    जइ (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		    अण्णहा जइ (all_द्विमान)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		    अण्णहा जइ (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		    अण्णहा जइ (arg_द्विमान)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		  }
		अण्णहा जइ (वृक्षः_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = सच्च;
		    जइ (COMPLEX_FLOAT_TYPE_P (type))
		      arg_द्विमान = सच्च;
		    जइ (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		    अण्णहा जइ (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		  }
		अण्णहा जइ (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_द्विमान = सच्च;
		    जइ (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		    अण्णहा जइ (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			व्यञ्जकम्.set_error ();
			गच्छ out;
		      }
		  }
		वृक्षः rtype = TYPE_MAIN_VARIANT (type);
		जइ (वृक्षः_CODE (rtype) == COMPLEX_TYPE)
		  rtype = वृक्षः_TYPE (rtype);
		जइ (SCALAR_FLOAT_TYPE_P (rtype))
		  प्रति (unsigned पूर्णाङ्क j = 0; j < अङ्कः_FLOATNX_TYPES; j++)
		    जइ (rtype == FLOATNX_TYPE_ग्रन्थिः (j))
		      {
			arg_int_floatnx = सच्च;
			भङ्ग;
		      }
		जइ (rtype == dfloat64x_type_ग्रन्थिः)
		  arg_int_decimalx = सच्च;
	      }
	    वृक्षः arg_real = NULL_वृक्षः;
	    प्रति (unsigned पूर्णाङ्क j = 1; j <= nargs; j++)
	      {
		जइ (parm_kind[j] == tgmath_fixed)
		  अनुवर्त;
		c_व्यञ्जकम्_t *ce = &(*cexpr_list)[अङ्कः_functions + j - 1];
		वृक्षः type = TYPE_MAIN_VARIANT (वृक्षः_TYPE (ce->मानम्));
		जइ (वृक्षः_CODE (type) == COMPLEX_TYPE)
		  type = वृक्षः_TYPE (type);
		जइ (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_ग्रन्थिः
			  : arg_int_floatnx
			  ? float32x_type_ग्रन्थिः
			  : arg_int_decimal
			  ? dfloat64_type_ग्रन्थिः
			  : double_type_ग्रन्थिः);
		जइ (arg_real == NULL_वृक्षः)
		  arg_real = type;
		अण्णहा
		  arg_real = common_type (arg_real, type);
		जइ (arg_real == error_mark_ग्रन्थिः)
		  {
		    व्यञ्जकम्.set_error ();
		    गच्छ out;
		  }
	      }
	    वृक्षः arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_व्यञ्जकम्_t *fn = रिक्त;
	    प्रति (unsigned पूर्णाङ्क j = 0; j < अङ्कः_functions; j++)
	      {
		जइ (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    भङ्ग;
		  }
	      }
	    जइ (fn == रिक्त
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		प्रति (unsigned पूर्णाङ्क j = 0; j < अङ्कः_functions; j++)
		  {
		    जइ (arg_complex
			!= (वृक्षः_CODE (tg_type[j]) == COMPLEX_TYPE))
		      अनुवर्त;
		    वृक्षः real_tg_type = (arg_complex
					 ? वृक्षः_TYPE (tg_type[j])
					 : tg_type[j]);
		    जइ (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      अनुवर्त;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    ध्रुव real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    ध्रुव real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    जइ (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			भङ्ग;
		      }
		  }
	      }
	    जइ (fn == रिक्त)
	      {
		error_at (loc, "no matching function for type-generic call");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    /* Construct a call to FN.  */
	    vec<वृक्षः, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<वृक्षः, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    प्रति (unsigned पूर्णाङ्क j = 0; j < nargs; j++)
	      {
		c_व्यञ्जकम्_t *ce = &(*cexpr_list)[अङ्कः_functions + j];
		args->quick_प्रक्षिप (ce->मानम्);
		arg_loc.quick_प्रक्षिप (ce->get_location ());
		origtypes->quick_प्रक्षिप (ce->original_type);
	      }
	    व्यञ्जकम्.मानम् = c_build_function_call_vec (loc, arg_loc, fn->मानम्,
						    args, origtypes);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    भङ्ग;
	  }
	पक्ष RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    c_व्यञ्जकम्_t *e2_p;
	    वृक्षः chain_मानम्;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, मिच्छ,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    व्यञ्जकम् = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, सच्च, सच्च);
	    chain_मानम् = e2_p->मानम्;
	    mark_exp_read (chain_मानम्);

	    जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) != CALL_व्यञ्जकम्)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    अण्णहा जइ (वृक्षः_CODE (वृक्षः_TYPE (chain_मानम्)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    अण्णहा
	      CALL_व्यञ्जकम्_STATIC_CHAIN (व्यञ्जकम्.मानम्) = chain_मानम्;
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    भङ्ग;
	  }
	पक्ष RID_BUILTIN_COMPLEX:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    c_व्यञ्जकम्_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, मिच्छ,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    जइ (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, सच्च, सच्च);
	    जइ (वृक्षः_CODE (e1_p->मानम्) == EXCESS_PRECISION_व्यञ्जकम्)
	      e1_p->मानम् = convert (वृक्षः_TYPE (e1_p->मानम्),
				     वृक्षः_OPERAND (e1_p->मानम्, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, सच्च, सच्च);
	    जइ (वृक्षः_CODE (e2_p->मानम्) == EXCESS_PRECISION_व्यञ्जकम्)
	      e2_p->मानम् = convert (वृक्षः_TYPE (e2_p->मानम्),
				     वृक्षः_OPERAND (e2_p->मानम्, 0));
	    जइ (!SCALAR_FLOAT_TYPE_P (वृक्षः_TYPE (e1_p->मानम्))
		|| DECIMAL_FLOAT_TYPE_P (वृक्षः_TYPE (e1_p->मानम्))
		|| !SCALAR_FLOAT_TYPE_P (वृक्षः_TYPE (e2_p->मानम्))
		|| DECIMAL_FLOAT_TYPE_P (वृक्षः_TYPE (e2_p->मानम्)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (TYPE_MAIN_VARIANT (वृक्षः_TYPE (e1_p->मानम्))
		!= TYPE_MAIN_VARIANT (वृक्षः_TYPE (e2_p->मानम्)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    व्यञ्जकम्.मानम् = build2_loc (loc, COMPLEX_व्यञ्जकम्,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (वृक्षः_TYPE (e1_p->मानम्))),
				     e1_p->मानम्, e2_p->मानम्);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    भङ्ग;
	  }
	पक्ष RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    c_व्यञ्जकम्_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, मिच्छ,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    e_p = &(*cexpr_list)[0];
	    वृक्षः ref = e_p->मानम्;

	    जइ (वृक्षः_CODE (वृक्षः_TYPE (ref)) != ARRAY_TYPE
		 && वृक्षः_CODE (वृक्षः_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    जइ (वृक्षः_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    जइ (वृक्षः_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    जइ (has_counted_by_object (ref))
	      व्यञ्जकम्.मानम् = get_counted_by_ref (ref);
	    अण्णहा
	      व्यञ्जकम्.मानम् = null_pointer_ग्रन्थिः;

	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    भङ्ग;
	  }
	पक्ष RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    unsigned पूर्णाङ्क i;
	    c_व्यञ्जकम्_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, मिच्छ,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, सच्च, सच्च);

	    जइ (vec_safe_length (cexpr_list) == 2)
	      व्यञ्जकम्.मानम् = c_build_vec_perm_व्यञ्जकम् (loc, (*cexpr_list)[0].मानम्,
						  NULL_वृक्षः,
						  (*cexpr_list)[1].मानम्);

	    अण्णहा जइ (vec_safe_length (cexpr_list) == 3)
	      व्यञ्जकम्.मानम् = c_build_vec_perm_व्यञ्जकम् (loc, (*cexpr_list)[0].मानम्,
						  (*cexpr_list)[1].मानम्,
						  (*cexpr_list)[2].मानम्);
	    अण्णहा
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		व्यञ्जकम्.set_error ();
	      }
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    भङ्ग;
	  }
	पक्ष RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    unsigned पूर्णाङ्क i;
	    c_व्यञ्जकम्_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, मिच्छ,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, सच्च, सच्च);

	    जइ (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		व्यञ्जकम्.set_error ();
	      }
	    अण्णहा
	      {
		auto_vec<वृक्षः, 16> mask;
		प्रति (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_प्रक्षिप ((*cexpr_list)[i].मानम्);
		व्यञ्जकम्.मानम् = c_build_shufflevector (loc, (*cexpr_list)[0].मानम्,
						    (*cexpr_list)[1].मानम्,
						    mask);
	      }
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    भङ्ग;
	  }
	पक्ष RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    e1 = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	    mark_exp_read (e1.मानम्);
	    जइ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    जइ (t1 == रिक्त)
	      व्यञ्जकम्.set_error ();
	    अण्णहा
	      {
		वृक्षः type_व्यञ्जकम् = NULL_वृक्षः;
		व्यञ्जकम्.मानम् = c_build_vec_convert (start_loc, e1.मानम्, loc,
						  groktypename (t1, &type_व्यञ्जकम्,
								रिक्त));
		set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start_loc, end_loc);
	      }
	  }
	  भङ्ग;
	पक्ष RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    e1 = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	    mark_exp_read (e1.मानम्);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    व्यञ्जकम् = parser_build_unary_op (loc, PAREN_व्यञ्जकम्, e1);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start_loc, end_loc);
	  }
	  भङ्ग;
	पक्ष RID_BUILTIN_STDC:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    c_व्यञ्जकम्_t *arg_p;
	    location_t close_paren_loc;
	    गणना c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_गणनम्_ONES,
	      C_BUILTIN_STDC_गणनम्_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_वामः,
	      C_BUILTIN_STDC_ROTATE_दक्षिणः,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ध्रुव वर्ण *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	    unsigned अङ्कः_args = 1;
	    विकल्प (name[परिमाण ("__builtin_stdc_") - 1])
	      {
	      पक्ष 'b':
		विकल्प (name[परिमाण ("__builtin_stdc_bit_") - 1])
		  {
		  पक्ष 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    भङ्ग;
		  पक्ष 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    भङ्ग;
		  स्वभाव:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    भङ्ग;
		  }
		भङ्ग;
	      पक्ष 'c':
		जइ (name[परिमाण ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_गणनम्_ONES;
		अण्णहा
		  stdc_rid = C_BUILTIN_STDC_गणनम्_ZEROS;
		भङ्ग;
	      पक्ष 'f':
		विकल्प (name[परिमाण ("__builtin_stdc_first_trailing_") - 1])
		  {
		  पक्ष 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    भङ्ग;
		  पक्ष 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    भङ्ग;
		  पक्ष 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    भङ्ग;
		  स्वभाव:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    भङ्ग;
		  }
		भङ्ग;
	      पक्ष 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		भङ्ग;
	      पक्ष 'l':
		जइ (name[परिमाण ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		अण्णहा
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		भङ्ग;
	      पक्ष 'r':
		जइ (name[परिमाण ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_वामः;
		अण्णहा
		  stdc_rid = C_BUILTIN_STDC_ROTATE_दक्षिणः;
		अङ्कः_args = 2;
		भङ्ग;
	      पक्ष 't':
		जइ (name[परिमाण ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		अण्णहा
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		भङ्ग;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, मिच्छ,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    जइ (vec_safe_length (cexpr_list) != अङ्कः_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, सच्च, सच्च);
	    जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (arg_p->मानम्)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (वृक्षः_CODE (वृक्षः_TYPE (arg_p->मानम्)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (वृक्षः_CODE (वृक्षः_TYPE (arg_p->मानम्)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (!TYPE_UNSIGNED (वृक्षः_TYPE (arg_p->मानम्)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (TYPE_MAIN_VARIANT (वृक्षः_TYPE (arg_p->मानम्))
		== char_type_ग्रन्थिः)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    वृक्षः arg = arg_p->मानम्;
	    वृक्षः type = TYPE_MAIN_VARIANT (वृक्षः_TYPE (arg));
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
	    पूर्णाङ्क prec = TYPE_PRECISION (type);
	    जइ (अङ्कः_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, सच्च, सच्च);
		जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (arg_p->मानम्)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    व्यञ्जकम्.set_error ();
		    भङ्ग;
		  }
		जइ (वृक्षः_CODE (वृक्षः_TYPE (arg_p->मानम्)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    व्यञ्जकम्.set_error ();
		    भङ्ग;
		  }
		वृक्षः arg1 = save_व्यञ्जकम् (arg);
		वृक्षः arg2 = save_व्यञ्जकम् (arg_p->मानम्);
		वृक्षः_code code;
		जइ (stdc_rid == C_BUILTIN_STDC_ROTATE_वामः)
		  code = LROTATE_व्यञ्जकम्;
		अण्णहा
		  code = RROTATE_व्यञ्जकम्;

		जइ (वृक्षः_CODE (arg2) == INTEGER_CST
		    && वृक्षः_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_गणनम्_negative,
			      "rotate count is negative");

		वृक्षः instrument_व्यञ्जकम् = NULL_वृक्षः;
		जइ (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_व्यञ्जकम् = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		जइ (TYPE_PRECISION (वृक्षः_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_ग्रन्थिः))
		  arg2 = fold_convert (unsigned_type_ग्रन्थिः, arg2);

		जइ (TYPE_UNSIGNED (वृक्षः_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_व्यञ्जकम्, वृक्षः_TYPE (arg2),
				     arg2, build_int_cst (वृक्षः_TYPE (arg2),
							  prec));
		अण्णहा
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    वृक्षः utype = c_common_unsigned_type (वृक्षः_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_व्यञ्जकम्, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		जइ (type_has_mode_precision_p (वृक्षः_TYPE (arg1))
		    || (वृक्षः_CODE (वृक्षः_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  व्यञ्जकम्.मानम् = build2_loc (loc, code, वृक्षः_TYPE (arg1), arg1,
					   arg2);
		अण्णहा
		  {
		    arg2 = save_व्यञ्जकम् (arg2);
		    वृक्षः t1 = build2_loc (loc, (code == LROTATE_व्यञ्जकम्
						? LSHIFT_व्यञ्जकम् : RSHIFT_व्यञ्जकम्),
					  वृक्षः_TYPE (arg1), arg1, arg2);
		    वृक्षः t2 = build2_loc (loc, MINUS_व्यञ्जकम्,
					  वृक्षः_TYPE (arg2),
					  build_int_cst (वृक्षः_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_व्यञ्जकम्
					   ? RSHIFT_व्यञ्जकम् : LSHIFT_व्यञ्जकम्),
				     वृक्षः_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_गणनम्_overflow);
		    वृक्षः t3 = build2_loc (loc, BIT_IOR_व्यञ्जकम्,
					  वृक्षः_TYPE (arg1), t1, t2);
		    वृक्षः t4 = build2_loc (loc, NE_व्यञ्जकम्, boolean_type_ग्रन्थिः,
					  arg2,
					  build_zero_cst (वृक्षः_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_व्यञ्जकम्, boolean_type_ग्रन्थिः,
				     arg1, t4);
		    व्यञ्जकम्.मानम् = build3_loc (loc, COND_व्यञ्जकम्,
					     वृक्षः_TYPE (arg1), t4, t3, arg1);
		  }
		जइ (instrument_व्यञ्जकम्)
		  व्यञ्जकम्.मानम् = build2_loc (loc, COMPOUND_व्यञ्जकम्,
					   वृक्षः_TYPE (व्यञ्जकम्.मानम्),
					   instrument_व्यञ्जकम्, व्यञ्जकम्.मानम्);
		set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
		भङ्ग;
	      }
	    वृक्षः barg1 = arg;
	    विकल्प (stdc_rid)
	      {
	      पक्ष C_BUILTIN_STDC_BIT_CEIL:
		arg = save_व्यञ्जकम् (arg);
		barg1 = build2_loc (loc, PLUS_व्यञ्जकम्, type, arg,
				    build_int_cst (type, -1));
		भङ्ग;
	      पक्ष C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_व्यञ्जकम् (arg);
		भङ्ग;
	      पक्ष C_BUILTIN_STDC_गणनम्_ZEROS:
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      पक्ष C_BUILTIN_STDC_LEADING_ONES:
	      पक्ष C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_व्यञ्जकम्, type, arg);
		भङ्ग;
	      स्वभाव:
		भङ्ग;
	      }
	    वृक्षः barg2 = NULL_वृक्षः;
	    विकल्प (stdc_rid)
	      {
	      पक्ष C_BUILTIN_STDC_BIT_WIDTH:
	      पक्ष C_BUILTIN_STDC_LEADING_ONES:
	      पक्ष C_BUILTIN_STDC_LEADING_ZEROS:
	      पक्ष C_BUILTIN_STDC_TRAILING_ONES:
	      पक्ष C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_ग्रन्थिः, prec);
		भङ्ग;
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_ग्रन्थिः;
		भङ्ग;
	      स्वभाव:
		भङ्ग;
	      }
	    वृक्षः fndecl = NULL_वृक्षः;
	    विकल्प (stdc_rid)
	      {
	      पक्ष C_BUILTIN_STDC_BIT_CEIL:
	      पक्ष C_BUILTIN_STDC_BIT_FLOOR:
	      पक्ष C_BUILTIN_STDC_BIT_WIDTH:
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      पक्ष C_BUILTIN_STDC_LEADING_ONES:
	      पक्ष C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		भङ्ग;
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      पक्ष C_BUILTIN_STDC_TRAILING_ONES:
	      पक्ष C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		भङ्ग;
	      पक्ष C_BUILTIN_STDC_गणनम्_ONES:
	      पक्ष C_BUILTIN_STDC_गणनम्_ZEROS:
	      पक्ष C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		भङ्ग;
	      स्वभाव:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    पूर्णाङ्क nargs = barg2 != NULL_वृक्षः ? 2 : 1;
	    vec<वृक्षः, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<वृक्षः, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_प्रक्षिप (barg1);
	    arg_loc.quick_प्रक्षिप (arg_p->get_location ());
	    origtypes->quick_प्रक्षिप (arg_p->original_type);
	    जइ (nargs == 2)
	      {
		args->quick_प्रक्षिप (barg2);
		arg_loc.quick_प्रक्षिप (loc);
		origtypes->quick_प्रक्षिप (integer_type_ग्रन्थिः);
	      }
	    व्यञ्जकम्.मानम् = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    जइ (व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
	      भङ्ग;
	    विकल्प (stdc_rid)
	      {
	      पक्ष C_BUILTIN_STDC_BIT_CEIL:
	      पक्ष C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      पक्ष C_BUILTIN_STDC_BIT_WIDTH:
		व्यञ्जकम्.मानम् = build2_loc (loc, MINUS_व्यञ्जकम्, integer_type_ग्रन्थिः,
					 build_int_cst (integer_type_ग्रन्थिः,
							prec), व्यञ्जकम्.मानम्);
		भङ्ग;
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		व्यञ्जकम्.मानम् = build2_loc (loc, PLUS_व्यञ्जकम्, integer_type_ग्रन्थिः,
					 व्यञ्जकम्.मानम्, integer_one_ग्रन्थिः);
		भङ्ग;
	      पक्ष C_BUILTIN_STDC_HAS_SINGLE_BIT:
		व्यञ्जकम्.मानम् = build2_loc (loc, EQ_व्यञ्जकम्, boolean_type_ग्रन्थिः,
					 व्यञ्जकम्.मानम्, integer_one_ग्रन्थिः);
		भङ्ग;
	      स्वभाव:
		भङ्ग;
	      }

	    जइ (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		जइ (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  व्यञ्जकम्.मानम् = fold_convert_loc (loc, unsigned_type_ग्रन्थिः,
						 व्यञ्जकम्.मानम्);
		भङ्ग;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    जइ (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      व्यञ्जकम्.मानम् = build_int_cst (type, 0);
	    अण्णहा
	      व्यञ्जकम्.मानम्
		= build2_loc (loc, LSHIFT_व्यञ्जकम्, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), व्यञ्जकम्.मानम्);
	    जइ (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      व्यञ्जकम्.मानम् = build3_loc (loc, COND_व्यञ्जकम्, type,
				       build2_loc (loc, LE_व्यञ्जकम्,
						   boolean_type_ग्रन्थिः, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       व्यञ्जकम्.मानम्);
	    अण्णहा
	      व्यञ्जकम्.मानम् = build3_loc (loc, COND_व्यञ्जकम्, type,
				       build2_loc (loc, EQ_व्यञ्जकम्,
						   boolean_type_ग्रन्थिः, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       व्यञ्जकम्.मानम्);
	    भङ्ग;
	  }
	पक्ष RID_BUILTIN_BSWAPG:
	पक्ष RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_व्यञ्जकम्_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ध्रुव वर्ण *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    जइ (!c_parser_get_builtin_args (parser, name, &cexpr_list, मिच्छ,
					    &close_paren_loc))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    जइ (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }

	    c_व्यञ्जकम्_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, सच्च, सच्च);
	    वृक्षः arg = arg_p->मानम्;
	    जइ (error_operand_p (arg))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    वृक्षः type = TYPE_MAIN_VARIANT (वृक्षः_TYPE (arg));
	    जइ (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (वृक्षः_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (वृक्षः_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    arg = c_fully_fold (arg, मिच्छ, रिक्त);
	    व्यञ्जकम्.मानम् = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_paren_loc);
	    भङ्ग;
	  }
	पक्ष RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    वृक्षः sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    व्यञ्जकम्.मानम् = objc_build_selector_व्यञ्जकम् (loc, sel);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_loc);
	  }
	  भङ्ग;
	पक्ष RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    वृक्षः id = c_parser_peek_token (parser)->मानम्;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    व्यञ्जकम्.मानम् = objc_build_protocol_व्यञ्जकम् (id);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_loc);
	  }
	  भङ्ग;
	पक्ष RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    जइ (!parens.require_open (parser))
	      {
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    t1 = c_parser_type_name (parser);
	    जइ (t1 == रिक्त)
	      {
		व्यञ्जकम्.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		भङ्ग;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    वृक्षः type = groktypename (t1, रिक्त, रिक्त);
	    व्यञ्जकम्.मानम् = objc_build_encode_व्यञ्जकम् (type);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_loc);
	  }
	  भङ्ग;
	पक्ष RID_GENERIC:
	  व्यञ्जकम् = c_parser_generic_selection (parser);
	  भङ्ग;
	पक्ष RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  व्यञ्जकम्.set_error ();
	  भङ्ग;
	/* C23 'nullptr' literal.  */
	पक्ष RID_NULLPTR:
	  c_parser_consume_token (parser);
	  व्यञ्जकम्.मानम् = nullptr_ग्रन्थिः;
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  भङ्ग;
	पक्ष RID_TRUE:
	  c_parser_consume_token (parser);
	  व्यञ्जकम्.मानम् = boolean_true_ग्रन्थिः;
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
	  भङ्ग;
	पक्ष RID_FALSE:
	  c_parser_consume_token (parser);
	  व्यञ्जकम्.मानम् = boolean_false_ग्रन्थिः;
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
	  भङ्ग;
	स्वभाव:
	  c_parser_error (parser, "expected expression");
	  व्यञ्जकम्.set_error ();
	  भङ्ग;
	}
      भङ्ग;
    पक्ष CPP_OPEN_SQUARE:
      जइ (c_dialect_objc ())
	{
	  वृक्षः receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  व्यञ्जकम्.मानम् = objc_build_message_व्यञ्जकम् (receiver, args);
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, loc, close_loc);
	  भङ्ग;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    स्वभाव:
      c_parser_error (parser, "expected expression");
      व्यञ्जकम्.set_error ();
      भङ्ग;
    }
 out:
  प्रत्यागम c_parser_postfix_expression_after_primary
    (parser, व्यञ्जकम्_LOC_OR_LOC (व्यञ्जकम्.मानम्, loc), व्यञ्जकम्);
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      संरचना c_declspecs *scspecs,
					      संरचना c_type_name *type_name,
					      location_t type_loc)
{
  वृक्षः type;
  संरचना c_व्यञ्जकम् init;
  तार्किक non_const;
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  location_t start_loc;
  वृक्षः type_व्यञ्जकम् = NULL_वृक्षः;
  तार्किक type_व्यञ्जकम्_const = सच्च;
  तार्किक constexpr_p = scspecs ? scspecs->constexpr_p : मिच्छ;
  unsigned पूर्णाङ्क underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (पङ्क्तिः_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  जइ (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_वृक्षः);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      विकल्प (type_name->specs->typespec_kind)
	{
	पक्ष ctsk_tagfirstref:
	पक्ष ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  भङ्ग;

	पक्ष ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  भङ्ग;

	स्वभाव:
	  भङ्ग;
	}
    }
  start_init (NULL_वृक्षः, रिक्त,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_व्यञ्जकम्, &type_व्यञ्जकम्_const);
  तार्किक varsize_p = मिच्छ;
  जइ (type != error_mark_ग्रन्थिः && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = सच्च;
    }
  अण्णहा जइ (वृक्षः_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_ग्रन्थिः;
    }
  जइ (constexpr_p && type != error_mark_ग्रन्थिः)
    {
      वृक्षः type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      जइ (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      अण्णहा जइ (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, मिच्छ, रिक्त, varsize_p);
  जइ (constexpr_p)
    finish_underspecified_init (NULL_वृक्षः, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  जइ (type != error_mark_ग्रन्थिः
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_ग्रन्थिः;
    }

  जइ (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.मानम् && वृक्षः_CODE (init.मानम्) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.मानम्)
	       : init.original_code == C_MAYBE_CONST_व्यञ्जकम्);
  non_const |= !type_व्यञ्जकम्_const;
  unsigned पूर्णाङ्क alignas_align = 0;
  जइ (type != error_mark_ग्रन्थिः
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      जइ (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  व्यञ्जकम्.मानम् = build_compound_literal (start_loc, type, init.मानम्, non_const,
				       alignas_align, scspecs);
  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, init.src_range);
  व्यञ्जकम्.m_decimal = 0;
  व्यञ्जकम्.original_code = ERROR_MARK;
  व्यञ्जकम्.original_type = रिक्त;
  जइ (type != error_mark_ग्रन्थिः
      && व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः
      && type_व्यञ्जकम्)
    {
      जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) == C_MAYBE_CONST_व्यञ्जकम्)
	{
	  gcc_assert (C_MAYBE_CONST_व्यञ्जकम्_PRE (व्यञ्जकम्.मानम्) == NULL_वृक्षः);
	  C_MAYBE_CONST_व्यञ्जकम्_PRE (व्यञ्जकम्.मानम्) = type_व्यञ्जकम्;
	}
      अण्णहा
	{
	  gcc_assert (!non_const);
	  व्यञ्जकम्.मानम् = build2 (C_MAYBE_CONST_व्यञ्जकम्, type,
			       type_व्यञ्जकम्, व्यञ्जकम्.मानम्);
	}
    }
  प्रत्यागम c_parser_postfix_expression_after_primary (parser, start_loc, व्यञ्जकम्);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

स्थिर तार्किक
sizeof_ptr_memacc_comptypes (वृक्षः type1, वृक्षः type2)
{
  प्रत्यागम comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

स्थिर शून्य
warn_for_abs (location_t loc, वृक्षः fndecl, वृक्षः arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  जइ (c_inhibit_evaluation_warnings)
    प्रत्यागम;

  वृक्षः atype = वृक्षः_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  जइ (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && वृक्षः_CODE (atype) != COMPLEX_TYPE)
    प्रत्यागम;

  गणना built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  विकल्प (fcode)
    {
    पक्ष BUILT_IN_ABS:
    पक्ष BUILT_IN_LABS:
    पक्ष BUILT_IN_LLABS:
    पक्ष BUILT_IN_IMAXABS:
      जइ (!INTEGRAL_TYPE_P (atype))
	{
	  जइ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  अण्णहा जइ (वृक्षः_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  अण्णहा
	    gcc_unreachable ();
	  प्रत्यागम;
	}
      जइ (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_मानम्,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      भङ्ग;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      जइ (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  जइ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  अण्णहा जइ (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  अण्णहा जइ (वृक्षः_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  अण्णहा
	    gcc_unreachable ();
	  प्रत्यागम;
	}
      भङ्ग;

    CASE_FLT_FN (BUILT_IN_CABS):
      जइ (वृक्षः_CODE (atype) != COMPLEX_TYPE)
	{
	  जइ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  अण्णहा जइ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  अण्णहा
	    gcc_unreachable ();

	  प्रत्यागम;
	}
      भङ्ग;

    पक्ष BUILT_IN_FABSD32:
    पक्ष BUILT_IN_FABSD64:
    पक्ष BUILT_IN_FABSD128:
    पक्ष BUILT_IN_FABSD64X:
      जइ (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  जइ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  अण्णहा जइ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  अण्णहा जइ (वृक्षः_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मानम्,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  अण्णहा
	    gcc_unreachable ();
	  प्रत्यागम;
	}
      भङ्ग;

    स्वभाव:
      प्रत्यागम;
    }

  जइ (!TYPE_ARG_TYPES (वृक्षः_TYPE (fndecl)))
    प्रत्यागम;

  वृक्षः ftype = वृक्षः_मानम् (TYPE_ARG_TYPES (वृक्षः_TYPE (fndecl)));
  जइ (वृक्षः_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (वृक्षः_CODE (ftype) == COMPLEX_TYPE);
      atype = वृक्षः_TYPE (atype);
      ftype = वृक्षः_TYPE (ftype);
    }

  जइ (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_मानम्,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t व्यञ्जकम्_loc,
					   संरचना c_व्यञ्जकम् व्यञ्जकम्)
{
  संरचना c_व्यञ्जकम् orig_व्यञ्जकम्;
  वृक्षः ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  वृक्षः sizeof_arg[6];
  unsigned पूर्णाङ्क literal_zero_mask;
  unsigned पूर्णाङ्क i;
  vec<वृक्षः, va_gc> *exprlist;
  vec<वृक्षः, va_gc> *origtypes = रिक्त;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  जाव (सच्च)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_वृक्षः;
	  जइ (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).मानम्;

	  जइ (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      जइ (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).मानम्;

	      व्यञ्जकम्.मानम् = build_omp_array_section (op_loc, व्यञ्जकम्.मानम्, idx,
						    len);
	    }
	  अण्णहा
	    व्यञ्जकम्.मानम् = build_array_ref (op_loc, व्यञ्जकम्.मानम्, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = व्यञ्जकम्.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	  व्यञ्जकम्.original_code = ERROR_MARK;
	  व्यञ्जकम्.original_type = रिक्त;
	  व्यञ्जकम्.m_decimal = 0;
	  भङ्ग;
	पक्ष CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    प्रति (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_वृक्षः;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = रिक्त;
	    अण्णहा जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) == FUNCTION_DECL
		     && fndecl_built_in_p (व्यञ्जकम्.मानम्, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_next_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		संरचना c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		संरचना c_typespec ret;
		ret.व्यञ्जकम् = NULL_वृक्षः;
		ret.spec = error_mark_ग्रन्थिः;
		ret.व्यञ्जकम्_const_operands = मिच्छ;
		जइ (type != रिक्त)
		  ret.spec = groktypename (type, &ret.व्यञ्जकम्,
					   &ret.व्यञ्जकम्_const_operands);
		parens.skip_until_found_close (parser);
		व्यञ्जकम्.मानम् = build_int_cst (integer_type_ग्रन्थिः,
					    type_to_class (ret.spec));
		भङ्ग;
	      }
	    अण्णहा
	      exprlist = c_parser_व्यञ्जकम्_list (parser, सच्च, मिच्छ, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_व्यञ्जकम् = व्यञ्जकम्;
	  mark_exp_read (व्यञ्जकम्.मानम्);
	  जइ (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      व्यञ्जकम्.मानम्, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) == FUNCTION_DECL)
	    {
	      जइ (fndecl_built_in_p (व्यञ्जकम्.मानम्, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  वृक्षः arg0 = (*exprlist)[0];
		  वृक्षः arg2 = (*exprlist)[2];
		  warn_for_memset (व्यञ्जकम्_loc, arg0, arg2, literal_zero_mask);
		}
	      जइ (warn_absolute_मानम्
		  && fndecl_built_in_p (व्यञ्जकम्.मानम्, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (व्यञ्जकम्_loc, व्यञ्जकम्.मानम्, (*exprlist)[0]);
	      जइ (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (व्यञ्जकम्.मानम्))
		{
		  error_at (व्यञ्जकम्_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = सच्च;
		}
	      जइ (warn_calloc_transposed_args)
		जइ (वृक्षः attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (वृक्षः_TYPE (व्यञ्जकम्.मानम्))))
		  जइ (वृक्षः_मानम् (attr) && वृक्षः_CHAIN (वृक्षः_मानम् (attr)))
		    warn_for_calloc (sizeof_arg_loc, व्यञ्जकम्.मानम्, exprlist,
				     sizeof_arg, attr);
	    }

	  start = व्यञ्जकम्.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  व्यञ्जकम्.मानम्
	    = c_build_function_call_vec (व्यञ्जकम्_loc, arg_loc, व्यञ्जकम्.मानम्,
					 exprlist, origtypes);
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	  व्यञ्जकम्.m_decimal = 0;

	  व्यञ्जकम्.original_code = ERROR_MARK;
	  जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) == INTEGER_CST
	      && वृक्षः_CODE (orig_व्यञ्जकम्.मानम्) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_व्यञ्जकम्.मानम्, BUILT_IN_CONSTANT_P))
	    व्यञ्जकम्.original_code = C_MAYBE_CONST_व्यञ्जकम्;
	  व्यञ्जकम्.original_type = रिक्त;
	  जइ (exprlist)
	    {
	      release_वृक्षः_vector (exprlist);
	      release_वृक्षः_vector (origtypes);
	    }
	  arg_loc.release ();
	  भङ्ग;
	पक्ष CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  व्यञ्जकम् = default_function_array_conversion (व्यञ्जकम्_loc, व्यञ्जकम्);
	  जइ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->मानम्;
	      comp_loc = comp_tok->location;
	    }
	  अण्णहा
	    {
	      c_parser_error (parser, "expected identifier");
	      व्यञ्जकम्.set_error ();
	      व्यञ्जकम्.original_code = ERROR_MARK;
              व्यञ्जकम्.original_type = रिक्त;
	      प्रत्यागम व्यञ्जकम्;
	    }
	  start = व्यञ्जकम्.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  व्यञ्जकम्.मानम् = build_component_ref (op_loc, व्यञ्जकम्.मानम्, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	  व्यञ्जकम्.original_code = ERROR_MARK;
	  जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) != COMPONENT_REF)
	    व्यञ्जकम्.original_type = रिक्त;
	  अण्णहा
	    {
	      /* Remember the original type of a bitfield.  */
	      वृक्षः field = वृक्षः_OPERAND (व्यञ्जकम्.मानम्, 1);
	      जइ (वृक्षः_CODE (field) != FIELD_DECL)
		व्यञ्जकम्.original_type = रिक्त;
	      अण्णहा
		व्यञ्जकम्.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  व्यञ्जकम्.m_decimal = 0;
	  भङ्ग;
	पक्ष CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, सच्च, मिच्छ);
	  जइ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->मानम्;
	      comp_loc = comp_tok->location;
	    }
	  अण्णहा
	    {
	      c_parser_error (parser, "expected identifier");
	      व्यञ्जकम्.set_error ();
	      व्यञ्जकम्.original_code = ERROR_MARK;
	      व्यञ्जकम्.original_type = रिक्त;
	      प्रत्यागम व्यञ्जकम्;
	    }
	  start = व्यञ्जकम्.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  व्यञ्जकम्.मानम् = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								व्यञ्जकम्.मानम्,
								RO_ARROW),
					    ident, comp_loc,
					    व्यञ्जकम्.get_location ());
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	  व्यञ्जकम्.original_code = ERROR_MARK;
	  जइ (वृक्षः_CODE (व्यञ्जकम्.मानम्) != COMPONENT_REF)
	    व्यञ्जकम्.original_type = रिक्त;
	  अण्णहा
	    {
	      /* Remember the original type of a bitfield.  */
	      वृक्षः field = वृक्षः_OPERAND (व्यञ्जकम्.मानम्, 1);
	      जइ (वृक्षः_CODE (field) != FIELD_DECL)
		व्यञ्जकम्.original_type = रिक्त;
	      अण्णहा
		व्यञ्जकम्.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  व्यञ्जकम्.m_decimal = 0;
	  भङ्ग;
	पक्ष CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = व्यञ्जकम्.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (व्यञ्जकम्.मानम्);
	  व्यञ्जकम् = default_function_array_conversion (व्यञ्जकम्_loc, व्यञ्जकम्);
	  व्यञ्जकम्.मानम् = build_unary_op (op_loc, POSTINCREMENT_व्यञ्जकम्,
				       व्यञ्जकम्.मानम्, मिच्छ);
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	  व्यञ्जकम्.original_code = ERROR_MARK;
	  व्यञ्जकम्.original_type = रिक्त;
	  भङ्ग;
	पक्ष CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = व्यञ्जकम्.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (व्यञ्जकम्.मानम्);
	  व्यञ्जकम् = default_function_array_conversion (व्यञ्जकम्_loc, व्यञ्जकम्);
	  व्यञ्जकम्.मानम् = build_unary_op (op_loc, POSTDECREMENT_व्यञ्जकम्,
				       व्यञ्जकम्.मानम्, मिच्छ);
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	  व्यञ्जकम्.original_code = ERROR_MARK;
	  व्यञ्जकम्.original_type = रिक्त;
	  भङ्ग;
	स्वभाव:
	  प्रत्यागम व्यञ्जकम्;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

स्थिर संरचना c_व्यञ्जकम्
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  जइ (c_parser_next_token_is (parser, CPP_COMMA))
    व्यञ्जकम् = convert_lvalue_to_rvalue (tloc, व्यञ्जकम्, सच्च, मिच्छ);
  जाव (c_parser_next_token_is (parser, CPP_COMMA))
    {
      संरचना c_व्यञ्जकम् next;
      वृक्षः lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t व्यञ्जकम्_loc;
      c_parser_consume_token (parser);
      व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      lhsval = व्यञ्जकम्.मानम्;
      जाव (वृक्षः_CODE (lhsval) == COMPOUND_व्यञ्जकम्
	     || वृक्षः_CODE (lhsval) == NOP_व्यञ्जकम्)
	{
	  जइ (वृक्षः_CODE (lhsval) == COMPOUND_व्यञ्जकम्)
	    lhsval = वृक्षः_OPERAND (lhsval, 1);
	  अण्णहा
	    lhsval = वृक्षः_OPERAND (lhsval, 0);
	}
      जइ (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      जइ (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  वृक्षः val = embed->मानम्;
	  unsigned last = RAW_DATA_LENGTH (val) - 1;
	  next.मानम् = build_int_cst (वृक्षः_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_ग्रन्थिः;
	  c_parser_consume_token (parser);
	}
      अण्णहा
	{
	  next = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  next = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, next, सच्च, मिच्छ);
	}
      व्यञ्जकम्.मानम् = build_compound_व्यञ्जकम् (loc, व्यञ्जकम्.मानम्, next.मानम्);
      व्यञ्जकम्.original_code = COMPOUND_व्यञ्जकम्;
      व्यञ्जकम्.original_type = next.original_type;
      व्यञ्जकम्.m_decimal = 0;
    }
  प्रत्यागम व्यञ्जकम्;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_expression_conv (c_parser *parser)
{
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  location_t loc = c_parser_peek_token (parser)->location;
  व्यञ्जकम् = c_parser_expression (parser);
  व्यञ्जकम् = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, सच्च, मिच्छ);
  प्रत्यागम व्यञ्जकम्;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

स्थिर अन्तःस्थ शून्य
c_parser_check_literal_zero (c_parser *parser, unsigned *literal_zero_mask,
			     unsigned पूर्णाङ्क idx)
{
  जइ (idx >= HOST_BITS_PER_INT)
    प्रत्यागम;

  c_token *tok = c_parser_peek_token (parser);
  विकल्प (tok->type)
    {
    पक्ष CPP_सङ्ख्या:
    पक्ष CPP_CHAR:
    पक्ष CPP_WCHAR:
    पक्ष CPP_CHAR16:
    पक्ष CPP_CHAR32:
    पक्ष CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      जइ (integer_zerop (tok->मानम्)
	  && !वृक्षः_OVERFLOW (tok->मानम्)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    स्वभाव:
      भङ्ग;
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

स्थिर vec<वृक्षः, va_gc> *
c_parser_व्यञ्जकम्_list (c_parser *parser, तार्किक convert_p, तार्किक fold_p,
		    vec<वृक्षः, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, वृक्षः *sizeof_arg,
		    vec<location_t> *locations,
		    unsigned पूर्णाङ्क *literal_zero_mask)
{
  vec<वृक्षः, va_gc> *ret;
  vec<वृक्षः, va_gc> *orig_types;
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  unsigned पूर्णाङ्क idx = 0;
  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = मिच्छ;

  ret = make_वृक्षः_vector ();
  जइ (p_orig_types == रिक्त)
    orig_types = रिक्त;
  अण्णहा
    orig_types = make_वृक्षः_vector ();

  जइ (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  जइ (convert_p)
    व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्.get_location (), व्यञ्जकम्, सच्च, सच्च);
  जइ (fold_p)
    व्यञ्जकम्.मानम् = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
  ret->quick_प्रक्षिप (व्यञ्जकम्.मानम्);
  जइ (orig_types)
    orig_types->quick_प्रक्षिप (व्यञ्जकम्.original_type);
  जइ (locations)
    locations->safe_प्रक्षिप (व्यञ्जकम्.get_location ());
  जइ (sizeof_arg != रिक्त
      && (व्यञ्जकम्.original_code == SIZEOF_व्यञ्जकम्
	  || व्यञ्जकम्.original_code == PAREN_SIZEOF_व्यञ्जकम्))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  जाव (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  वृक्षः मानम् = embed->मानम्;
	  व्यञ्जकम्.original_code = INTEGER_CST;
	  व्यञ्जकम्.original_type = integer_type_ग्रन्थिः;
	  व्यञ्जकम्.मानम् = NULL_वृक्षः;
	  set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, embed->get_range ());
	  व्यञ्जकम्.m_decimal = 0;
	  प्रति (unsigned पूर्णाङ्क i = 0; i < (unsigned) RAW_DATA_LENGTH (मानम्); i++)
	    {
	      जइ (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (मानम्)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      व्यञ्जकम्.मानम् = build_int_cst (integer_type_ग्रन्थिः,
					  RAW_DATA_UCHAR_ELT (मानम्, i));
	      vec_safe_प्रक्षिप (ret, व्यञ्जकम्.मानम्);
	      जइ (orig_types)
		vec_safe_प्रक्षिप (orig_types, व्यञ्जकम्.original_type);
	      जइ (locations)
		locations->safe_प्रक्षिप (व्यञ्जकम्.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}
      जइ (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      जइ (convert_p)
	व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्.get_location (), व्यञ्जकम्, सच्च,
					 सच्च);
      जइ (fold_p)
	व्यञ्जकम्.मानम् = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
      vec_safe_प्रक्षिप (ret, व्यञ्जकम्.मानम्);
      जइ (orig_types)
	vec_safe_प्रक्षिप (orig_types, व्यञ्जकम्.original_type);
      जइ (locations)
	locations->safe_प्रक्षिप (व्यञ्जकम्.get_location ());
      जइ (++idx < 6
	  && sizeof_arg != रिक्त
	  && (व्यञ्जकम्.original_code == SIZEOF_व्यञ्जकम्
	      || व्यञ्जकम्.original_code == PAREN_SIZEOF_व्यञ्जकम्))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  जइ (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  प्रत्यागम ret;
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

स्थिर शून्य
c_parser_objc_class_definition (c_parser *parser, वृक्षः attributes)
{
  तार्किक iface_p;
  वृक्षः id1;
  वृक्षः superclass;
  जइ (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = सच्च;
  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = मिच्छ;
  अण्णहा
    gcc_unreachable ();

  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      प्रत्यागम;
    }
  id1 = c_parser_peek_token (parser)->मानम्;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      वृक्षः id2;
      वृक्षः proto = NULL_वृक्षः;
      matching_parens parens;
      parens.consume_open (parser);
      जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  जइ (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_वृक्षः;
	    }
	  अण्णहा
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      प्रत्यागम;
	    }
	}
      अण्णहा
	{
	  id2 = c_parser_peek_token (parser)->मानम्;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      जइ (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  प्रत्यागम;
	}
      जइ (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      प्रत्यागम;
    }
  जइ (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  प्रत्यागम;
	}
      superclass = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
    }
  अण्णहा
    superclass = NULL_वृक्षः;
  जइ (iface_p)
    {
      वृक्षः proto = NULL_वृक्षः;
      जइ (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  अण्णहा
    objc_start_class_implementation (id1, superclass);
  जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  जइ (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  अण्णहा
    {
      objc_continue_implementation ();
      प्रत्यागम;
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

स्थिर शून्य
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  जाव (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      वृक्षः decls;
      /* Parse any stray semicolon.  */
      जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}
      /* Stop if at the end of the instance variables.  */
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  भङ्ग;
	}
      /* Parse any objc-visibility-spec.  */
      जइ (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  अनुवर्त;
	}
      अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  अनुवर्त;
	}
      अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  अनुवर्त;
	}
      अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  अनुवर्त;
	}
      अण्णहा जइ (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, रिक्त, NULL_वृक्षः);
	  अनुवर्त;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, रिक्त);
      जइ (decls == रिक्त)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  जइ (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = मिच्छ;
	  अनुवर्त;
	}
      अण्णहा
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  वृक्षः ivar = nreverse (decls);
	  प्रति (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_ग्रन्थिः (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

स्थिर शून्य
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  जाव (सच्च)
    {
      वृक्षः id;
      जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	  parser->error = मिच्छ;
	  प्रत्यागम;
	}
      id = c_parser_peek_token (parser)->मानम्;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

स्थिर शून्य
c_parser_objc_alias_declaration (c_parser *parser)
{
  वृक्षः id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
      प्रत्यागम;
    }
  id1 = c_parser_peek_token (parser)->मानम्;
  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
      प्रत्यागम;
    }
  id2 = c_parser_peek_token (parser)->मानम्;
  c_parser_consume_token (parser);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
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

स्थिर शून्य
c_parser_objc_protocol_definition (c_parser *parser, वृक्षः attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      प्रत्यागम;
    }
  जइ (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      जाव (सच्च)
	{
	  वृक्षः id;
	  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      भङ्ग;
	    }
	  id = c_parser_peek_token (parser)->मानम्;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अण्णहा
	    भङ्ग;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  अण्णहा
    {
      वृक्षः id = c_parser_peek_token (parser)->मानम्;
      वृक्षः proto = NULL_वृक्षः;
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = सच्च;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = मिच्छ;
      objc_finish_interface ();
    }
}

/* Parse an objc-method-type.

   objc-method-type:
     +
     -

   Return true if it is a class method (+) and false if it is
   an instance method (-).
*/
स्थिर अन्तःस्थ तार्किक
c_parser_objc_method_type (c_parser *parser)
{
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_PLUS:
      c_parser_consume_token (parser);
      प्रत्यागम सच्च;
    पक्ष CPP_MINUS:
      c_parser_consume_token (parser);
      प्रत्यागम मिच्छ;
    स्वभाव:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

स्थिर शून्य
c_parser_objc_method_definition (c_parser *parser)
{
  तार्किक is_class_method = c_parser_objc_method_type (parser);
  वृक्षः decl, attributes = NULL_वृक्षः, व्यञ्जकम् = NULL_वृक्षः;
  parser->objc_pq_context = सच्च;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &व्यञ्जकम्);
  जइ (decl == error_mark_ग्रन्थिः)
    प्रत्यागम;  /* Bail here. */

  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  जइ (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      प्रत्यागम;
    }

  parser->objc_pq_context = मिच्छ;
  जइ (objc_start_method_definition (is_class_method, decl, attributes, व्यञ्जकम्))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  अण्णहा
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
     empty
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

स्थिर शून्य
c_parser_objc_methodprotolist (c_parser *parser)
{
  जाव (सच्च)
    {
      /* The list is terminated by @end.  */
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  भङ्ग;
	पक्ष CPP_PLUS:
	पक्ष CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  भङ्ग;
	पक्ष CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, रिक्त, NULL_वृक्षः);
	  भङ्ग;
	पक्ष CPP_EOF:
	  प्रत्यागम;
	स्वभाव:
	  जइ (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    प्रत्यागम;
	  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (सच्च);
	      c_parser_consume_token (parser);
	    }
	  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (मिच्छ);
	      c_parser_consume_token (parser);
	    }
	  अण्णहा
	    c_parser_declaration_or_fndef (parser, मिच्छ, मिच्छ, सच्च,
					   मिच्छ, सच्च, मिच्छ);
	  भङ्ग;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

स्थिर शून्य
c_parser_objc_methodproto (c_parser *parser)
{
  तार्किक is_class_method = c_parser_objc_method_type (parser);
  वृक्षः decl, attributes = NULL_वृक्षः;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = सच्च;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    रिक्त);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = मिच्छ;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  जइ (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      प्रत्यागम;
    }

  जइ (decl != error_mark_ग्रन्थिः)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

स्थिर तार्किक
c_parser_objc_maybe_method_attributes (c_parser* parser, वृक्षः* attributes)
{
  तार्किक bad = मिच्छ;
  जइ (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_वृक्षः;
      bad = सच्च;
    }

  जइ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  जइ (*attributes == NULL_वृक्षः || bad)
    प्रत्यागम bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    प्रत्यागम bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  प्रत्यागम सच्च;
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
     empty
     objc-opt-parms , parameter-declaration

   objc-optellipsis:
     empty
     , ...
*/

स्थिर वृक्षः
c_parser_objc_method_decl (c_parser *parser, तार्किक is_class_method,
			   वृक्षः *attributes, वृक्षः *व्यञ्जकम्)
{
  वृक्षः type = NULL_वृक्षः;
  वृक्षः sel;
  वृक्षः parms = NULL_वृक्षः;
  तार्किक ellipsis = मिच्छ;
  तार्किक attr_err = मिच्छ;

  *attributes = NULL_वृक्षः;
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      type = c_parser_objc_type_name (parser);
      parens.skip_until_found_close (parser);
    }
  sel = c_parser_objc_selector (parser);
  /* If there is no selector, or a colon follows, we have an
     objc-keyword-selector.  If there is a selector, and a colon does
     not follow, that selector ends the objc-method-decl.  */
  जइ (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      वृक्षः tsel = sel;
      वृक्षः list = NULL_वृक्षः;
      जाव (सच्च)
	{
	  वृक्षः atype = NULL_वृक्षः, id, keyworddecl;
	  वृक्षः param_attr = NULL_वृक्षः;
	  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    भङ्ग;
	  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  जइ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      प्रत्यागम error_mark_ग्रन्थिः;
	    }
	  id = c_parser_peek_token (parser)->मानम्;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  जइ (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    भङ्ग;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_ग्रन्थिः (वृक्षः_LIST);
      जाव (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  संरचना c_parm *parm;
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = सच्च;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      भङ्ग;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_वृक्षः, मिच्छ);
	  जइ (parm == रिक्त)
	    भङ्ग;
	  parms = chainon (parms,
			   build_वृक्षः_list (NULL_वृक्षः, grokparm (parm, व्यञ्जकम्)));
	}
      sel = list;
    }
  अण्णहा
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  जइ (sel == रिक्त)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      प्रत्यागम error_mark_ग्रन्थिः;
    }

  जइ (attr_err)
    प्रत्यागम error_mark_ग्रन्थिः;

  प्रत्यागम objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

स्थिर वृक्षः
c_parser_objc_type_name (c_parser *parser)
{
  वृक्षः quals = NULL_वृक्षः;
  संरचना c_type_name *type_name = रिक्त;
  वृक्षः type = NULL_वृक्षः;
  जाव (सच्च)
    {
      c_token *token = c_parser_peek_token (parser);
      जइ (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_वृक्षः_list (NULL_वृक्षः, token->मानम्), quals);
	  c_parser_consume_token (parser);
	}
      अण्णहा
	भङ्ग;
    }
  जइ (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  जइ (type_name)
    type = groktypename (type_name, रिक्त, रिक्त);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  जइ (type == error_mark_ग्रन्थिः)
    type = NULL_वृक्षः;

  प्रत्यागम build_वृक्षः_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

स्थिर वृक्षः
c_parser_objc_protocol_refs (c_parser *parser)
{
  वृक्षः list = NULL_वृक्षः;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  जाव (सच्च)
    {
      वृक्षः id;
      जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  भङ्ग;
	}
      id = c_parser_peek_token (parser)->मानम्;
      list = chainon (list, build_वृक्षः_list (NULL_वृक्षः, id));
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  प्रत्यागम list;
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

स्थिर शून्य
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  वृक्षः stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  जाव (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      संरचना c_parm *parm;
      वृक्षः parameter_declaration = error_mark_ग्रन्थिः;
      तार्किक seen_open_paren = मिच्छ;

      c_parser_consume_token (parser);
      matching_parens parens;
      जइ (!parens.require_open (parser))
	seen_open_paren = सच्च;
      जइ (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_वृक्षः;
	}
      अण्णहा
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_वृक्षः, मिच्छ);
	  जइ (parm == रिक्त)
	    parameter_declaration = error_mark_ग्रन्थिः;
	  अण्णहा
	    parameter_declaration = grokparm (parm, रिक्त);
	}
      जइ (seen_open_paren)
	parens.require_close (parser);
      अण्णहा
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      जइ (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  जइ (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
    {
      c_parser_consume_token (parser);
      location = c_parser_peek_token (parser)->location;
      stmt = c_parser_compound_statement (parser);
      objc_build_finally_clause (location, stmt);
    }
  objc_finish_try_stmt ();
}

/* Parse an objc-synchronized-statement.

   objc-synchronized-statement:
     @synchronized ( expression ) compound-statement
*/

स्थिर शून्य
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  वृक्षः व्यञ्जकम्, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      संरचना c_व्यञ्जकम् ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, मिच्छ, मिच्छ);
      व्यञ्जकम् = ce.मानम्;
      व्यञ्जकम् = c_fully_fold (व्यञ्जकम्, मिच्छ, रिक्त);
      parens.skip_until_found_close (parser);
    }
  अण्णहा
    व्यञ्जकम् = error_mark_ग्रन्थिः;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, व्यञ्जकम्, stmt);
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

स्थिर वृक्षः
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  वृक्षः मानम् = token->मानम्;
  जइ (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      प्रत्यागम मानम्;
    }
  जइ (token->type != CPP_KEYWORD)
    प्रत्यागम NULL_वृक्षः;
  विकल्प (token->keyword)
    {
    पक्ष RID_ENUM:
    पक्ष RID_STRUCT:
    पक्ष RID_UNION:
    पक्ष RID_IF:
    पक्ष RID_ELSE:
    पक्ष RID_WHILE:
    पक्ष RID_DO:
    पक्ष RID_FOR:
    पक्ष RID_SWITCH:
    पक्ष RID_CASE:
    पक्ष RID_DEFAULT:
    पक्ष RID_BREAK:
    पक्ष RID_CONTINUE:
    पक्ष RID_RETURN:
    पक्ष RID_GOTO:
    पक्ष RID_ASM:
    पक्ष RID_SIZEOF:
    पक्ष RID_TYPEOF:
    पक्ष RID_TYPEOF_UNQUAL:
    पक्ष RID_ALIGNOF:
    पक्ष RID_UNSIGNED:
    पक्ष RID_LONG:
    पक्ष RID_CONST:
    पक्ष RID_SHORT:
    पक्ष RID_VOLATILE:
    पक्ष RID_SIGNED:
    पक्ष RID_RESTRICT:
    पक्ष RID_COMPLEX:
    पक्ष RID_IN:
    पक्ष RID_OUT:
    पक्ष RID_INOUT:
    पक्ष RID_BYCOPY:
    पक्ष RID_BYREF:
    पक्ष RID_ONEWAY:
    पक्ष RID_INT:
    पक्ष RID_CHAR:
    पक्ष RID_FLOAT:
    पक्ष RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    पक्ष RID_VOID:
    पक्ष RID_BOOL:
    पक्ष RID_ATOMIC:
    पक्ष RID_AUTO_TYPE:
    पक्ष RID_INT_N_0:
    पक्ष RID_INT_N_1:
    पक्ष RID_INT_N_2:
    पक्ष RID_INT_N_3:
      c_parser_consume_token (parser);
      प्रत्यागम मानम्;
    स्वभाव:
      प्रत्यागम NULL_वृक्षः;
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

स्थिर वृक्षः
c_parser_objc_selector_arg (c_parser *parser)
{
  वृक्षः sel = c_parser_objc_selector (parser);
  वृक्षः list = NULL_वृक्षः;
  जइ (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    प्रत्यागम sel;
  जाव (सच्च)
    {
      जइ (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_वृक्षः_list (sel, NULL_वृक्षः));
	  list = chainon (list, build_वृक्षः_list (NULL_वृक्षः, NULL_वृक्षः));
	}
      अण्णहा
	{
	  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    प्रत्यागम list;
	  list = chainon (list, build_वृक्षः_list (sel, NULL_वृक्षः));
	}
      sel = c_parser_objc_selector (parser);
      जइ (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	भङ्ग;
    }
  प्रत्यागम list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

स्थिर वृक्षः
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  जइ (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      वृक्षः id = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
      प्रत्यागम objc_get_class_reference (id);
    }
  संरचना c_व्यञ्जकम् ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, मिच्छ, मिच्छ);
  प्रत्यागम c_fully_fold (ce.मानम्, मिच्छ, रिक्त);
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

स्थिर वृक्षः
c_parser_objc_message_args (c_parser *parser)
{
  वृक्षः sel = c_parser_objc_selector (parser);
  वृक्षः list = NULL_वृक्षः;
  जइ (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    प्रत्यागम sel;
  जाव (सच्च)
    {
      वृक्षः keywordexpr;
      जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	प्रत्यागम error_mark_ग्रन्थिः;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_वृक्षः_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      जइ (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	भङ्ग;
    }
  प्रत्यागम list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

स्थिर वृक्षः
c_parser_objc_keywordexpr (c_parser *parser)
{
  वृक्षः ret;
  vec<वृक्षः, va_gc> *व्यञ्जकम्_list = c_parser_व्यञ्जकम्_list (parser, सच्च, सच्च,
						रिक्त, रिक्त, रिक्त, रिक्त);
  जइ (vec_safe_length (व्यञ्जकम्_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*व्यञ्जकम्_list)[0];
    }
  अण्णहा
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_वृक्षः_list_vec (व्यञ्जकम्_list);
    }
  release_वृक्षः_vector (व्यञ्जकम्_list);
  प्रत्यागम ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
स्थिर तार्किक
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   संरचना c_declspecs *specs)
{
  जइ (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      प्रत्यागम सच्च;
    }
  प्रत्यागम मिच्छ;
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
स्थिर शून्य
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  तार्किक syntax_error = मिच्छ;
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = सच्च;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      अण्णहा
	जाव (सच्च)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    जइ (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		जइ (token->type == CPP_CLOSE_PAREN)
		  भङ्ग;
		c_parser_consume_token (parser);
		अनुवर्त;
	      }

	    वृक्षः attr_name = NULL_वृक्षः;
	    गणना rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    तार्किक add_at = मिच्छ;
	    जइ (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		जइ (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->मानम्;
		    add_at = सच्च;
		  }
		अण्णहा
		  attr_name = ridpointers[(पूर्णाङ्क)keyword];
	      }
	    अण्णहा जइ (token->type == CPP_NAME)
	      attr_name = token->मानम्;
	    c_parser_consume_token (parser);

	    गणना objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = नूतन property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_प्रक्षिप (prop);

	    वृक्षः meth_name;
	    विकल्प (prop->prop_kind)
	      {
	      स्वभाव: भङ्ग;
	      पक्ष OBJC_PROPERTY_ATTR_UNKNOWN:
		जइ (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		अण्णहा
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = सच्च;
		भङ्ग;

	      पक्ष OBJC_PROPERTY_ATTR_GETTER:
	      पक्ष OBJC_PROPERTY_ATTR_SETTER:
		जइ (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = सच्च;
		    भङ्ग;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		जइ (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = सच्च;
		    भङ्ग;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->मानम्;
		c_parser_consume_token (parser);
		जइ (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    जइ (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = सच्च;
		      }
		    अण्णहा
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		अण्णहा
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		भङ्ग;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अण्णहा
	    भङ्ग;
	}
      parser->objc_property_attr_context = मिच्छ;

      जइ (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      अण्णहा
	syntax_error = मिच्छ, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  वृक्षः properties = c_parser_struct_declaration (parser, रिक्त);

  जइ (properties == error_mark_ग्रन्थिः)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
  अण्णहा
    {
      जइ (properties == NULL_वृक्षः)
	c_parser_error (parser, "expected identifier");
      अण्णहा
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  प्रति (; properties; properties = वृक्षः_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_ग्रन्थिः (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  जाव (!prop_attr_list.is_empty())
    delete prop_attr_list.निष्कासय ();
  prop_attr_list.release ();
  parser->error = मिच्छ;
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
स्थिर शून्य
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  वृक्षः list = NULL_वृक्षः;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  जाव (सच्च)
    {
      वृक्षः property, ivar;
      जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = मिच्छ;
	  प्रत्यागम;
	}
      property = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	      parser->error = मिच्छ;
	      प्रत्यागम;
	    }
	  ivar = c_parser_peek_token (parser)->मानम्;
	  c_parser_consume_token (parser);
	}
      अण्णहा
	ivar = NULL_वृक्षः;
      list = chainon (list, build_वृक्षः_list (ivar, property));
      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_synthesize_declaration (loc, list);
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
स्थिर शून्य
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  वृक्षः list = NULL_वृक्षः;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  जाव (सच्च)
    {
      वृक्षः property;
      जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	  parser->error = मिच्छ;
	  प्रत्यागम;
	}
      property = c_parser_peek_token (parser)->मानम्;
      list = chainon (list, build_वृक्षः_list (NULL_वृक्षः, property));
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

स्थिर तार्किक
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  प्रत्यागम सच्च;
}

/* Parse a pragma GCC novector.  */

स्थिर तार्किक
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  प्रत्यागम सच्च;
}

/* Parse a pragma GCC unroll.  */

स्थिर unsigned short
c_parser_pragma_unroll (c_parser *parser)
{
  unsigned short unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  वृक्षः व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
  mark_exp_read (व्यञ्जकम्);
  व्यञ्जकम् = c_fully_fold (व्यञ्जकम्, मिच्छ, रिक्त);
  HOST_WIDE_INT lunroll = 0;
  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्))
      || वृक्षः_CODE (व्यञ्जकम्) != INTEGER_CST
      || (lunroll = वृक्षः_to_shwi (व्यञ्जकम्)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  अण्णहा
    {
      unroll = (unsigned short)lunroll;
      जइ (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  प्रत्यागम unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

स्थिर तार्किक
c_parser_pragma (c_parser *parser, गणना pragma_context context, तार्किक *if_p,
		 वृक्षः before_labels)
{
  unsigned पूर्णाङ्क id;
  ध्रुव वर्ण *construct = रिक्त;

  निवेशः_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  जइ (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	निवेशः_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = सच्च;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
      प्रत्यागम मिच्छ;
    }

  विकल्प (id)
    {
    पक्ष PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OACC_ENTER_DATA:
      जइ (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  जइ (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	      प्रत्यागम सच्च;
	    }
	  गच्छ bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, सच्च);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OACC_EXIT_DATA:
      जइ (context != pragma_compound)
	{
	  construct = "acc exit data";
	  गच्छ in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, मिच्छ);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OACC_ROUTINE:
      जइ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	  प्रत्यागम मिच्छ;
	}
      c_parser_oacc_routine (parser, context);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OACC_UPDATE:
      जइ (context != pragma_compound)
	{
	  construct = "acc update";
	  गच्छ in_compound;
	}
      c_parser_oacc_update (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_BARRIER:
      जइ (context != pragma_compound)
	{
	  construct = "omp barrier";
	  गच्छ in_compound;
	}
      c_parser_omp_barrier (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_DEPOBJ:
      जइ (context != pragma_compound)
	{
	  construct = "omp depobj";
	  गच्छ in_compound;
	}
      c_parser_omp_depobj (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_FLUSH:
      जइ (context != pragma_compound)
	{
	  construct = "omp flush";
	  गच्छ in_compound;
	}
      c_parser_omp_flush (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_INTEROP:
      जइ (context != pragma_compound)
	{
	  construct = "omp interop";
	  गच्छ in_compound;
	}
      c_parser_omp_interop (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_TASKWAIT:
      जइ (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  गच्छ in_compound;
	}
      c_parser_omp_taskwait (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_TASKYIELD:
      जइ (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  गच्छ in_compound;
	}
      c_parser_omp_taskyield (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_CANCEL:
      जइ (context != pragma_compound)
	{
	  construct = "omp cancel";
	  गच्छ in_compound;
	}
      c_parser_omp_cancel (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_CANCELLATION_POINT:
      प्रत्यागम c_parser_omp_cancellation_point (parser, context);

    पक्ष PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_TARGET:
      प्रत्यागम c_parser_omp_target (parser, context, if_p);

    पक्ष PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_DECLARE:
      प्रत्यागम c_parser_omp_declare (parser, context);

    पक्ष PRAGMA_OMP_REQUIRES:
      जइ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	  प्रत्यागम मिच्छ;
	}
      c_parser_omp_requires (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_ASSUMES:
      जइ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	  प्रत्यागम मिच्छ;
	}
      c_parser_omp_assumes (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      प्रत्यागम सच्च;

    पक्ष PRAGMA_OMP_ERROR:
      प्रत्यागम c_parser_omp_error (parser, context);

    पक्ष PRAGMA_OMP_ORDERED:
      प्रत्यागम c_parser_omp_ordered (parser, context, if_p);

    पक्ष PRAGMA_NOVECTOR:
    पक्ष PRAGMA_UNROLL:
    पक्ष PRAGMA_IVDEP:
      {
	तार्किक novector = मिच्छ;
	unsigned short unroll = 0;
	तार्किक ivdep = मिच्छ;

	विकल्प (id)
	  {
	  पक्ष PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    भङ्ग;
	  पक्ष PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    भङ्ग;
	  पक्ष PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    भङ्ग;
	  स्वभाव:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	तार्किक has_more = tok->type == CPP_PRAGMA;
	जाव (has_more)
	  {
	    विकल्प (tok->pragma_kind)
	      {
	      पक्ष PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		भङ्ग;
	      पक्ष PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		भङ्ग;
	      पक्ष PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		भङ्ग;
	      स्वभाव:
		has_more = मिच्छ;
		भङ्ग;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	जइ (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    प्रत्यागम मिच्छ;
	  }
	जइ (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	अण्णहा
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      प्रत्यागम सच्च;

    पक्ष PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
      प्रत्यागम मिच्छ;

    पक्ष PRAGMA_OACC_WAIT:
      जइ (context != pragma_compound)
	{
	  construct = "acc wait";
	  गच्छ in_compound;
	}
	/* FALL THROUGH.  */

    स्वभाव:
      जइ (id < PRAGMA_FIRST_EXTERNAL)
	{
	  जइ (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	      प्रत्यागम मिच्छ;
	    }
	  c_parser_omp_construct (parser, if_p);
	  प्रत्यागम सच्च;
	}
      भङ्ग;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = सच्च;
  c_parser_skip_to_pragma_eol (parser);

  प्रत्यागम मिच्छ;
}

/* The interface the pragma parsers have to the lexer.  */

गणना cpp_ttype
pragma_lex (वृक्षः *मानम्, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  गणना cpp_ttype ret = tok->type;

  *मानम् = tok->मानम्;
  जइ (loc)
    *loc = tok->location;

  जइ (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  अण्णहा जइ (ret == CPP_STRING)
    *मानम् = c_parser_string_literal (the_parser, मिच्छ, मिच्छ).मानम्;
  अण्णहा
    {
      जइ (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  प्रत्यागम ret;
}

शून्य
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  करेहि
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } जाव (type != CPP_PRAGMA_EOL);
}

स्थिर शून्य
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  वृक्षः name = रिक्त;

  parser->lex_joined_string = सच्च;
  c_parser_consume_pragma (parser);
  जइ (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
    }
  अण्णहा
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = मिच्छ;

  जइ (name)
    c_common_pch_pragma (parse_in, वृक्षः_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

स्थिर pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  जइ (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  अण्णहा जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      विकल्प (p[0])
	{
	पक्ष 'a':
	  जइ (!strcmp ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  अण्णहा जइ (!strcmp ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  अण्णहा जइ (!strcmp ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  अण्णहा जइ (!strcmp ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  अण्णहा जइ (!strcmp ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  भङ्ग;
	पक्ष 'b':
	  जइ (!strcmp ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  भङ्ग;
	पक्ष 'c':
	  जइ (!strcmp ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  अण्णहा जइ (!strcmp ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  अण्णहा जइ (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  अण्णहा जइ (!strcmp ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          अण्णहा जइ (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  अण्णहा जइ (!strcmp ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  भङ्ग;
	पक्ष 'd':
	  जइ (!strcmp ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  अण्णहा जइ (!strcmp ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  अण्णहा जइ (!strcmp ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  अण्णहा जइ (!strcmp ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  अण्णहा जइ (!strcmp ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  अण्णहा जइ (!strcmp ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  अण्णहा जइ (!strcmp ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  अण्णहा जइ (!strcmp ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  अण्णहा जइ (!strcmp ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  अण्णहा जइ (!strcmp ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  अण्णहा जइ (!strcmp ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  अण्णहा जइ (!strcmp ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  भङ्ग;
	पक्ष 'e':
	  जइ (!strcmp ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  भङ्ग;
	पक्ष 'f':
	  जइ (!strcmp ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  अण्णहा जइ (!strcmp ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  अण्णहा जइ (!strcmp ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  अण्णहा जइ (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  अण्णहा जइ (!strcmp ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  अण्णहा जइ (!strcmp ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  भङ्ग;
	पक्ष 'g':
	  जइ (!strcmp ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  अण्णहा जइ (!strcmp ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  भङ्ग;
	पक्ष 'h':
	  जइ (!strcmp ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  अण्णहा जइ (!strcmp ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  अण्णहा जइ (!strcmp ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  भङ्ग;
	पक्ष 'i':
	  जइ (!strcmp ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  अण्णहा जइ (!strcmp ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  अण्णहा जइ (!strcmp ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  अण्णहा जइ (!strcmp ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  अण्णहा जइ (!strcmp ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  अण्णहा जइ (!strcmp ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  अण्णहा जइ (!strcmp ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  अण्णहा जइ (!strcmp ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  भङ्ग;
	पक्ष 'l':
	  जइ (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  अण्णहा जइ (!strcmp ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  अण्णहा जइ (!strcmp ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  अण्णहा जइ (!strcmp ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  भङ्ग;
	पक्ष 'm':
	  जइ (!strcmp ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  अण्णहा जइ (!strcmp ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  भङ्ग;
	पक्ष 'n':
	  जइ (!strcmp ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  अण्णहा जइ (!strcmp ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  अण्णहा जइ (!strcmp ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  अण्णहा जइ (!strcmp ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  अण्णहा जइ (!strcmp ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  अण्णहा जइ (!strcmp ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  अण्णहा जइ (!strcmp ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  अण्णहा जइ (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  अण्णहा जइ (!strcmp ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_अङ्कः_GANGS;
	  अण्णहा जइ (!strcmp ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_अङ्कः_TASKS;
	  अण्णहा जइ (!strcmp ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_अङ्कः_TEAMS;
	  अण्णहा जइ (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_अङ्कः_THREADS;
	  अण्णहा जइ (!strcmp ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_अङ्कः_WORKERS;
	  भङ्ग;
	पक्ष 'o':
	  जइ (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  अण्णहा जइ (!strcmp ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  भङ्ग;
	पक्ष 'p':
	  जइ (!strcmp ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  अण्णहा जइ (!strcmp ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  अण्णहा जइ (!strcmp ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  अण्णहा जइ (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  अण्णहा जइ (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  अण्णहा जइ (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  अण्णहा जइ (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  अण्णहा जइ (!strcmp ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  अण्णहा जइ (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  अण्णहा जइ (!strcmp ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  भङ्ग;
	पक्ष 'r':
	  जइ (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  भङ्ग;
	पक्ष 's':
	  जइ (!strcmp ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  अण्णहा जइ (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  अण्णहा जइ (!strcmp ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  अण्णहा जइ (!strcmp ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  अण्णहा जइ (!strcmp ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  अण्णहा जइ (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  अण्णहा जइ (!strcmp ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  अण्णहा जइ (!strcmp ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  भङ्ग;
	पक्ष 't':
	  जइ (!strcmp ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  अण्णहा जइ (!strcmp ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  अण्णहा जइ (!strcmp ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  अण्णहा जइ (!strcmp ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  अण्णहा जइ (!strcmp ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  अण्णहा जइ (!strcmp ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  भङ्ग;
	पक्ष 'u':
	  जइ (!strcmp ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  अण्णहा जइ (!strcmp ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  अण्णहा जइ (!strcmp ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  अण्णहा जइ (!strcmp ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  अण्णहा जइ (!strcmp ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  अण्णहा जइ (!strcmp ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  अण्णहा जइ (!strcmp ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  भङ्ग;
	पक्ष 'v':
	  जइ (!strcmp ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  अण्णहा जइ (!strcmp ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  भङ्ग;
	पक्ष 'w':
	  जइ (!strcmp ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  अण्णहा जइ (!strcmp ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  भङ्ग;
	}
    }

  जइ (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  प्रत्यागम result;
}

/* Validate that a clause of the given type does not already exist.  */

स्थिर शून्य
check_no_duplicate_clause (वृक्षः clauses, गणना omp_clause_code code,
			   ध्रुव वर्ण *name)
{
  जइ (वृक्षः c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

स्थिर वृक्षः
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, वृक्षः list)
{
  vec<वृक्षः, va_gc> *args;
  वृक्षः t, args_वृक्षः;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  args = c_parser_व्यञ्जकम्_list (parser, मिच्छ, सच्च, रिक्त, रिक्त, रिक्त, रिक्त);
  args_वृक्षः = build_वृक्षः_list_vec (args);

  प्रति (t = args_वृक्षः; t; t = वृक्षः_CHAIN (t))
    {
      वृक्षः targ = वृक्षः_मानम् (t);

      जइ (targ != error_mark_ग्रन्थिः)
	{
	  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_ग्रन्थिः;
	    }
	  अण्णहा
	    {
	      वृक्षः c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_वृक्षः_vector (args);
  parens.require_close (parser);
  प्रत्यागम list;
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

संरचना omp_dim
{
  वृक्षः नीचः_bound, length;
  location_t loc;
  तार्किक no_colon;
  omp_dim (वृक्षः lb, वृक्षः len, location_t lo, तार्किक nc)
  : नीचः_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

स्थिर वृक्षः
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    गणना omp_clause_code kind, वृक्षः list,
			    तार्किक map_lvalue = मिच्छ)
{
  auto_vec<omp_dim> dims;
  तार्किक array_section_p;
  auto_vec<c_token> tokens;
  unsigned पूर्णाङ्क tokens_avail = 0;
  c_token *saved_tokens = रिक्त;

  जाव (1)
    {
      वृक्षः t = NULL_वृक्षः;
      location_t tloc = c_parser_peek_token (parser)->location;

      जइ (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  जइ (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      संरचना c_व्यञ्जकम् व्यञ्जकम्;
	      जइ (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  व्यञ्जकम्.मानम् = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      अण्णहा
		व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	      जइ (व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः)
		{
		  वृक्षः u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = व्यञ्जकम्.मानम्;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      जइ (c_parser_next_token_is_not (parser, CPP_COMMA))
		भङ्ग;

	      c_parser_consume_token (parser);
	      अनुवर्त;
	    }

	  tokens.truncate (0);
	  unsigned पूर्णाङ्क nesting_depth = 0;
	  जाव (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      विकल्प (token->type)
		{
		पक्ष CPP_EOF:
		पक्ष CPP_PRAGMA_EOL:
		  भङ्ग;
		पक्ष CPP_OPEN_BRACE:
		पक्ष CPP_OPEN_PAREN:
		पक्ष CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  गच्छ add;
		पक्ष CPP_CLOSE_BRACE:
		पक्ष CPP_CLOSE_PAREN:
		पक्ष CPP_CLOSE_SQUARE:
		  जइ (nesting_depth-- == 0)
		    भङ्ग;
		  गच्छ add;
		पक्ष CPP_COMMA:
		  जइ (nesting_depth == 0)
		    भङ्ग;
		  गच्छ add;
		स्वभाव:
		add:
		  tokens.safe_प्रक्षिप (*token);
		  c_parser_consume_token (parser);
		  अनुवर्त;
		}
	      भङ्ग;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, परिमाण (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_प्रक्षिप (eof_token);
	  tokens.safe_प्रक्षिप (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      अण्णहा जइ (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = सच्च;
	  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  जइ (व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः)
	    mark_exp_read (व्यञ्जकम्.मानम्);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  वृक्षः decl = व्यञ्जकम्.मानम्;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  जइ (वृक्षः_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      जाव (वृक्षः_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  वृक्षः नीचः_bound = वृक्षः_OPERAND (decl, 1);
		  वृक्षः length = वृक्षः_OPERAND (decl, 2);
		  dims.safe_प्रक्षिप (omp_dim (नीचः_bound, length, loc, मिच्छ));
		  decl = वृक्षः_OPERAND (decl, 0);
		}

	      जाव (वृक्षः_CODE (decl) == ARRAY_REF
		     || वृक्षः_CODE (decl) == INDIRECT_REF
		     || वृक्षः_CODE (decl) == COMPOUND_व्यञ्जकम्)
		{
		  जइ (वृक्षः_CODE (decl) == COMPOUND_व्यञ्जकम्)
		    {
		      decl = वृक्षः_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  अण्णहा जइ (वृक्षः_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_प्रक्षिप (omp_dim (integer_zero_ग्रन्थिः,
					       integer_one_ग्रन्थिः, loc, सच्च));
		      decl = वृक्षः_OPERAND (decl, 0);
		    }
		  अण्णहा  /* ARRAY_REF. */
		    {
		      वृक्षः index = वृक्षः_OPERAND (decl, 1);
		      dims.safe_प्रक्षिप (omp_dim (index, integer_one_ग्रन्थिः, loc,
					       सच्च));
		      decl = वृक्षः_OPERAND (decl, 0);
		    }
		}

	      प्रति (पूर्णाङ्क i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].नीचः_bound,
						dims[i].length);
	    }
	  अण्णहा जइ (वृक्षः_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = वृक्षः_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_ग्रन्थिः,
					      integer_one_ग्रन्थिः);
	    }
	  अण्णहा जइ (वृक्षः_CODE (decl) == ARRAY_REF)
	    {
	      वृक्षः idx = वृक्षः_OPERAND (decl, 1);

	      decl = वृक्षः_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_ग्रन्थिः);
	    }
	  अण्णहा जइ (वृक्षः_CODE (decl) == NON_LVALUE_व्यञ्जकम्
		   || CONVERT_व्यञ्जकम्_P (decl))
	    decl = वृक्षः_OPERAND (decl, 0);

	  वृक्षः u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  गच्छ next_item;
	}

      जइ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->मानम्);

	  जइ (t == NULL_वृक्षः)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->मानम्);
	      t = error_mark_ग्रन्थिः;
	    }

	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).मानम्;
      अण्णहा
	{
	  c_parser_error (parser, "expected identifier");
	  भङ्ग;
	}

      जइ (t == error_mark_ग्रन्थिः)
	;
      अण्णहा जइ (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  विकल्प (kind)
	    {
	    पक्ष OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      जइ (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_ग्रन्थिः;
		  भङ्ग;
		}
	      /* FALLTHROUGH  */
	    पक्ष OMP_CLAUSE_MAP:
	    पक्ष OMP_CLAUSE_FROM:
	    पक्ष OMP_CLAUSE_TO:
	    start_component_ref:
	      जाव (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  जइ (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_व्यञ्जकम् t_व्यञ्जकम्;
		      t_व्यञ्जकम्.मानम् = t;
		      t_व्यञ्जकम्.original_code = ERROR_MARK;
		      t_व्यञ्जकम्.original_type = रिक्त;
		      set_c_व्यञ्जकम्_source_range (&t_व्यञ्जकम्, op_loc, op_loc);
		      t_व्यञ्जकम्.m_decimal = 0;
		      t_व्यञ्जकम् = convert_lvalue_to_rvalue (op_loc, t_व्यञ्जकम्,
							 सच्च, मिच्छ);
		      t = build_indirect_ref (op_loc, t_व्यञ्जकम्.मानम्, RO_ARROW);
		      arrow_loc = t_व्यञ्जकम्.get_location ();
		    }
		  c_parser_consume_token (parser);
		  जइ (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_ग्रन्थिः;
		      भङ्ग;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  वृक्षः ident = comp_tok->मानम्;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    पक्ष OMP_CLAUSE_AFFINITY:
	    पक्ष OMP_CLAUSE_DEPEND:
	    पक्ष OMP_CLAUSE_REDUCTION:
	    पक्ष OMP_CLAUSE_IN_REDUCTION:
	    पक्ष OMP_CLAUSE_TASK_REDUCTION:
	    पक्ष OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = मिच्छ;
	      dims.truncate (0);
	      जाव (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  वृक्षः नीचः_bound = NULL_वृक्षः, length = NULL_वृक्षः;
		  तार्किक no_colon = मिच्छ;

		  c_parser_consume_token (parser);
		  जइ (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t व्यञ्जकम्_loc
			= c_parser_peek_token (parser)->location;
		      c_व्यञ्जकम् व्यञ्जकम् = c_parser_expression (parser);
		      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्,
						       मिच्छ, सच्च);
		      नीचः_bound = व्यञ्जकम्.मानम्;
		      loc = व्यञ्जकम्_loc;
		    }
		  जइ (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_ग्रन्थिः;
		      no_colon = सच्च;
		    }
		  अण्णहा
		    {
		      /* Look for `:'.  */
		      जइ (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_ग्रन्थिः;
			  भङ्ग;
			}
		      array_section_p = सच्च;
		      जइ (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t व्यञ्जकम्_loc
			    = c_parser_peek_token (parser)->location;
			  c_व्यञ्जकम् व्यञ्जकम् = c_parser_expression (parser);
			  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्,
							   मिच्छ, सच्च);
			  length = व्यञ्जकम्.मानम्;
			}
		    }
		  /* Look for the closing `]'.  */
		  जइ (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_ग्रन्थिः;
		      भङ्ग;
		    }

		  dims.safe_प्रक्षिप (omp_dim (नीचः_bound, length, loc, no_colon));
		}

	      जइ (t != error_mark_ग्रन्थिः)
		{
		  जइ ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      प्रति (unsigned i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_ग्रन्थिः);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].नीचः_bound);
			}
		      गच्छ start_component_ref;
		    }
		  अण्णहा
		    प्रति (unsigned i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].नीचः_bound,
						   dims[i].length);
		}

	      जइ ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_ग्रन्थिः
		  && parser->tokens_avail != 2)
		{
		  जइ (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_ग्रन्थिः;
		    }
		  अण्णहा
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
		      जइ (t != error_mark_ग्रन्थिः && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_ग्रन्थिः;
			}
		    }
		}
	      भङ्ग;
	    स्वभाव:
	      भङ्ग;
	    }

	  जइ (t != error_mark_ग्रन्थिः)
	    {
	      वृक्षः u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      अण्णहा  /* kind == OMP_CLAUSE_ERROR */
	list = वृक्षः_cons (t, build_empty_stmt (tloc), list);

      जइ (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      जइ (c_parser_next_token_is_not (parser, CPP_COMMA))
	भङ्ग;

      c_parser_consume_token (parser);
    }

  प्रत्यागम list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

स्थिर वृक्षः
c_parser_omp_var_list_parens (c_parser *parser, गणना omp_clause_code kind,
			      वृक्षः list, तार्किक map_lvalue = मिच्छ)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  जइ (parser->in_omp_decl_attribute)
    {
      जइ (kind)
	{
	  वृक्षः u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  प्रत्यागम u;
	}
      अण्णहा
	प्रत्यागम वृक्षः_cons (parser->in_omp_decl_attribute, NULL_वृक्षः, list);
    }

  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  प्रत्यागम list;
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

स्थिर वृक्षः
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   वृक्षः list)
{
  गणना gomp_map_kind kind;
  विकल्प (c_kind)
    {
    पक्ष PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      भङ्ग;
    पक्ष PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    पक्ष PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }

  वृक्षः nl = list;
  तार्किक readonly = मिच्छ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      जइ (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  जइ (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_POINTER (token->मानम्), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = सच्च;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       मिच्छ);
      parens.skip_until_found_close (parser);
    }

  प्रति (वृक्षः c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      जइ (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  प्रत्यागम nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

स्थिर वृक्षः
c_parser_oacc_data_clause_deviceptr (c_parser *parser, वृक्षः list)
{
  वृक्षः vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, रिक्त);
  प्रति (t = vars; t && t; t = वृक्षः_CHAIN (t))
    {
      वृक्षः v = वृक्षः_PURPOSE (t);
      location_t loc = व्यञ्जकम्_LOCATION (वृक्षः_मानम् (t));

      जइ (!VAR_P (v) && वृक्षः_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      अण्णहा जइ (वृक्षः_TYPE (v) == error_mark_ग्रन्थिः)
	;
      अण्णहा जइ (!POINTER_TYPE_P (वृक्षः_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      वृक्षः u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  प्रत्यागम list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

स्थिर वृक्षः
c_parser_omp_clause_collapse (c_parser *parser, वृक्षः list)
{
  वृक्षः c, अङ्कः = error_mark_ग्रन्थिः;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      अङ्कः = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
      parens.skip_until_found_close (parser);
    }
  जइ (अङ्कः == error_mark_ग्रन्थिः)
    प्रत्यागम list;
  mark_exp_read (अङ्कः);
  अङ्कः = c_fully_fold (अङ्कः, मिच्छ, रिक्त);
  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (अङ्कः))
      || !वृक्षः_fits_shwi_p (अङ्कः)
      || (n = वृक्षः_to_shwi (अङ्कः)) <= 0
      || (पूर्णाङ्क) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      प्रत्यागम list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_व्यञ्जकम् (c) = अङ्कः;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_copyin (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_copyprivate (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

स्थिर वृक्षः
c_parser_omp_clause_default (c_parser *parser, वृक्षः list, तार्किक is_oacc)
{
  गणना omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः c;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      विकल्प (p[0])
	{
	पक्ष 'n':
	  जइ (strcmp ("none", p) != 0)
	    गच्छ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  भङ्ग;

	पक्ष 'p':
	  जइ (is_oacc)
	    {
	      जइ (strcmp ("present", p) != 0)
		गच्छ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  अण्णहा
	    {
	      जइ (strcmp ("private", p) != 0)
		गच्छ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  भङ्ग;

	पक्ष 'f':
	  जइ (strcmp ("firstprivate", p) != 0 || is_oacc)
	    गच्छ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  भङ्ग;

	पक्ष 's':
	  जइ (strcmp ("shared", p) != 0 || is_oacc)
	    गच्छ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  भङ्ग;

	स्वभाव:
	  गच्छ invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  अण्णहा
    {
    invalid_kind:
      जइ (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      अण्णहा
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  जइ (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    प्रत्यागम list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  प्रत्यागम c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_firstprivate (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

स्थिर वृक्षः
c_parser_omp_clause_final (c_parser *parser, वृक्षः list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      वृक्षः t, c;
      जइ (!parens.require_open (parser))
	t = error_mark_ग्रन्थिः;
      अण्णहा
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  t = convert_lvalue_to_rvalue (eloc, व्यञ्जकम्, सच्च, सच्च).मानम्;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, मिच्छ, रिक्त);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_व्यञ्जकम् (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  अण्णहा
    c_parser_error (parser, "expected %<(%>");

  प्रत्यागम list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

स्थिर वृक्षः
c_parser_omp_clause_indirect (c_parser *parser, वृक्षः list)
{
  location_t location = c_parser_peek_token (parser)->location;
  वृक्षः t;

  जइ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      जइ (!parens.require_open (parser))
	प्रत्यागम list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, सच्च, सच्च);
      t = c_objc_common_truthvalue_conversion (loc, व्यञ्जकम्.मानम्);
      t = c_fully_fold (t, मिच्छ, रिक्त);
      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t))
	  || वृक्षः_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  प्रत्यागम list;
	}
      parens.skip_until_found_close (parser);
    }
  अण्णहा
    t = integer_one_ग्रन्थिः;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  वृक्षः c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  प्रत्यागम c;
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

स्थिर वृक्षः
c_parser_omp_clause_if (c_parser *parser, वृक्षः list, तार्किक is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  गणना वृक्षः_code if_modifier = ERROR_MARK;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      पूर्णाङ्क n = 2;
      जइ (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      अण्णहा जइ (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      अण्णहा जइ (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      अण्णहा जइ (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      अण्णहा जइ (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      अण्णहा जइ (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  जइ (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->मानम्);
	      जइ (strcmp ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      अण्णहा जइ (strcmp ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      अण्णहा जइ (strcmp ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      अण्णहा जइ (strcmp ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      जइ (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      अण्णहा
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      जइ (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  जइ (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->मानम्);
		      जइ (strcmp ("data", p) == 0)
			n = 4;
		    }
		  जइ (n == 4)
		    c_parser_consume_token (parser);
		  अण्णहा
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      जइ (if_modifier != ERROR_MARK)
	{
	  जइ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  अण्णहा
	    {
	      जइ (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  व्यञ्जकम् = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, सच्च, सच्च);
  वृक्षः t = c_objc_common_truthvalue_conversion (loc, व्यञ्जकम्.मानम्), c;
  t = c_fully_fold (t, मिच्छ, रिक्त);
  parens.skip_until_found_close (parser);

  प्रति (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	जइ (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ध्रुव वर्ण *p = रिक्त;
	    विकल्प (if_modifier)
	      {
	      पक्ष VOID_CST: p = "cancel"; भङ्ग;
	      पक्ष OMP_PARALLEL: p = "parallel"; भङ्ग;
	      पक्ष OMP_SIMD: p = "simd"; भङ्ग;
	      पक्ष OMP_TASK: p = "task"; भङ्ग;
	      पक्ष OMP_TASKLOOP: p = "taskloop"; भङ्ग;
	      पक्ष OMP_TARGET_DATA: p = "target data"; भङ्ग;
	      पक्ष OMP_TARGET: p = "target"; भङ्ग;
	      पक्ष OMP_TARGET_UPDATE: p = "target update"; भङ्ग;
	      पक्ष OMP_TARGET_ENTER_DATA: p = "target enter data"; भङ्ग;
	      पक्ष OMP_TARGET_EXIT_DATA: p = "target exit data"; भङ्ग;
	      स्वभाव: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    प्रत्यागम list;
	  }
	अण्णहा जइ (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    जइ (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    अण्णहा
	      error_at (location, "too many %<if%> clauses without modifier");
	    प्रत्यागम list;
	  }
	अण्णहा जइ (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    प्रत्यागम list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_lastprivate (c_parser *parser, वृक्षः list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  जइ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      तार्किक conditional = मिच्छ;
      जइ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ध्रुव वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	  जइ (strcmp (p, "conditional") == 0)
	    {
	      conditional = सच्च;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      वृक्षः nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      जइ (conditional)
	प्रति (वृक्षः c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      प्रत्यागम nlist;
    }
  प्रत्यागम list;
}

/* OpenMP 3.1:
   mergeable */

स्थिर वृक्षः
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, वृक्षः list)
{
  वृक्षः c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  प्रत्यागम c;
}

/* OpenMP 2.5:
   nowait */

स्थिर वृक्षः
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, वृक्षः list)
{
  वृक्षः c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

स्थिर वृक्षः
c_parser_omp_clause_अङ्कः_threads (c_parser *parser, वृक्षः list)
{
  location_t अङ्कः_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः c, t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);

      parens.skip_until_found_close (parser);

      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  प्रत्यागम list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (व्यञ्जकम्_loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, t,
		       build_int_cst (वृक्षः_TYPE (t), 0));
      protected_set_व्यञ्जकम्_location (c, व्यञ्जकम्_loc);
      जइ (c == boolean_true_ग्रन्थिः)
	{
	  warning_at (व्यञ्जकम्_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_ग्रन्थिः;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अङ्कः_THREADS, "num_threads");

      c = build_omp_clause (अङ्कः_threads_loc, OMP_CLAUSE_अङ्कः_THREADS);
      OMP_CLAUSE_अङ्कः_THREADS_व्यञ्जकम् (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

स्थिर वृक्षः
c_parser_omp_clause_अङ्कः_tasks (c_parser *parser, वृक्षः list)
{
  location_t अङ्कः_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      तार्किक strict = मिच्छ;
      जइ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्),
		     "strict") == 0)
	{
	  strict = सच्च;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः c, t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);

      parens.skip_until_found_close (parser);

      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  प्रत्यागम list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (व्यञ्जकम्_loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, t,
			   build_int_cst (वृक्षः_TYPE (t), 0));
      जइ (CAN_HAVE_LOCATION_P (c))
	SET_व्यञ्जकम्_LOCATION (c, व्यञ्जकम्_loc);
      जइ (c == boolean_true_ग्रन्थिः)
	{
	  warning_at (व्यञ्जकम्_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_ग्रन्थिः;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अङ्कः_TASKS, "num_tasks");

      c = build_omp_clause (अङ्कः_tasks_loc, OMP_CLAUSE_अङ्कः_TASKS);
      OMP_CLAUSE_अङ्कः_TASKS_व्यञ्जकम् (c) = t;
      OMP_CLAUSE_अङ्कः_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

स्थिर वृक्षः
c_parser_omp_clause_grainsize (c_parser *parser, वृक्षः list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      तार्किक strict = मिच्छ;
      जइ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्),
		     "strict") == 0)
	{
	  strict = सच्च;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः c, t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);

      parens.skip_until_found_close (parser);

      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  प्रत्यागम list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (व्यञ्जकम्_loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, t,
			   build_int_cst (वृक्षः_TYPE (t), 0));
      जइ (CAN_HAVE_LOCATION_P (c))
	SET_व्यञ्जकम्_LOCATION (c, व्यञ्जकम्_loc);
      जइ (c == boolean_true_ग्रन्थिः)
	{
	  warning_at (व्यञ्जकम्_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_ग्रन्थिः;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_व्यञ्जकम् (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenMP 4.5:
   priority ( expression ) */

स्थिर वृक्षः
c_parser_omp_clause_priority (c_parser *parser, वृक्षः list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः c, t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);

      parens.skip_until_found_close (parser);

      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  प्रत्यागम list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (व्यञ्जकम्_loc, LT_व्यञ्जकम्, boolean_type_ग्रन्थिः, t,
			   build_int_cst (वृक्षः_TYPE (t), 0));
      जइ (CAN_HAVE_LOCATION_P (c))
	SET_व्यञ्जकम्_LOCATION (c, व्यञ्जकम्_loc);
      जइ (c == boolean_true_ग्रन्थिः)
	{
	  warning_at (व्यञ्जकम्_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_ग्रन्थिः;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_व्यञ्जकम् (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenMP 4.5:
   hint ( expression ) */

स्थिर वृक्षः
c_parser_omp_clause_hint (c_parser *parser, वृक्षः list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः c, t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);
      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t))
	  || वृक्षः_CODE (t) != INTEGER_CST
	  || वृक्षः_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  प्रत्यागम list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_व्यञ्जकम् (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

स्थिर वृक्षः
c_parser_omp_clause_filter (c_parser *parser, वृक्षः list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः c, t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);
      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  प्रत्यागम list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_व्यञ्जकम् (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

स्थिर वृक्षः
c_parser_omp_clause_defaultmap (c_parser *parser, वृक्षः list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः c;
  ध्रुव वर्ण *p;
  गणना omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  गणना omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;
  जइ (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  अण्णहा जइ (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      गच्छ out_err;
    }
  अण्णहा
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

  विकल्प (p[0])
    {
    पक्ष 'a':
      जइ (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      अण्णहा
	गच्छ invalid_behavior;
      भङ्ग;

    पक्ष 'd':
      जइ (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      अण्णहा
	गच्छ invalid_behavior;
      भङ्ग;

    पक्ष 'f':
      जइ (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      अण्णहा जइ (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      अण्णहा
	गच्छ invalid_behavior;
      भङ्ग;

    पक्ष 'n':
      जइ (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      अण्णहा
	गच्छ invalid_behavior;
      भङ्ग;

    पक्ष 'p':
      जइ (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      अण्णहा
	गच्छ invalid_behavior;
      भङ्ग;

    पक्ष 't':
      जइ (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      अण्णहा जइ (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      अण्णहा
	गच्छ invalid_behavior;
      भङ्ग;

    स्वभाव:
      गच्छ invalid_behavior;
    }
  c_parser_consume_token (parser);

  जइ (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	गच्छ out_err;
      जइ (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  गच्छ out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      विकल्प (p[0])
	{
	पक्ष 'a':
	  जइ (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  अण्णहा जइ (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  अण्णहा
	    गच्छ invalid_category;
	  भङ्ग;

	पक्ष 'p':
	  जइ (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  अण्णहा
	    गच्छ invalid_category;
	  भङ्ग;

	पक्ष 's':
	  जइ (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  अण्णहा
	    गच्छ invalid_category;
	  भङ्ग;

	स्वभाव:
	  गच्छ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  प्रति (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	गणना omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	जइ (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = रिक्त;
	विकल्प (cat)
	  {
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = रिक्त;
	    भङ्ग;
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    भङ्ग;
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    भङ्ग;
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    भङ्ग;
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    भङ्ग;
	  स्वभाव:
	    gcc_unreachable ();
	  }
	जइ (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	अण्णहा
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	भङ्ग;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;

 out_err:
  parens.skip_until_found_close (parser);
  प्रत्यागम list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_use_device_ptr (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_use_device_addr (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_has_device_addr (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_is_device_ptr (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

स्थिर वृक्षः
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 वृक्षः list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
  c_व्यञ्जकम् व्यञ्जकम् = c_parser_expression (parser);
  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
  वृक्षः c, t = व्यञ्जकम्.मानम्;
  t = c_fully_fold (t, मिच्छ, रिक्त);

  parens.skip_until_found_close (parser);

  जइ (t == error_mark_ग्रन्थिः)
    प्रत्यागम list;
  अण्णहा जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
    {
      error_at (व्यञ्जकम्_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      प्रत्यागम list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (व्यञ्जकम्_loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, t,
		       build_int_cst (वृक्षः_TYPE (t), 0));
  protected_set_व्यञ्जकम्_location (c, व्यञ्जकम्_loc);
  जइ (c == boolean_true_ग्रन्थिः)
    {
      warning_at (व्यञ्जकम्_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_ग्रन्थिः;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
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

स्थिर वृक्षः
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    ध्रुव वर्ण *str, वृक्षः list)
{
  ध्रुव वर्ण *id = "num";
  वृक्षः ops[2] = { NULL_वृक्षः, NULL_वृक्षः }, c;

  जइ (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      करेहि
	{
	  c_token *next = c_parser_peek_token (parser);
	  पूर्णाङ्क idx = 0;

	  /* Gang static argument.  */
	  जइ (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		गच्छ cleanup_error;

	      idx = 1;
	      जइ (ops[idx] != NULL_वृक्षः)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  गच्छ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      जइ (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_ग्रन्थिः;

		  जइ (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      अनुवर्त;
		    }
		  अण्णहा
		    भङ्ग;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  अण्णहा जइ (c_parser_next_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_POINTER (next->मानम्)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  जइ (ops[idx] != NULL_वृक्षः)
	    {
	      c_parser_error (parser, "unexpected argument");
	      गच्छ cleanup_error;
	    }

	  location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
	  c_व्यञ्जकम् cexpr = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  cexpr = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, cexpr, मिच्छ, सच्च);
	  वृक्षः व्यञ्जकम् = cexpr.मानम्;
	  जइ (व्यञ्जकम् == error_mark_ग्रन्थिः)
	    गच्छ cleanup_error;

	  व्यञ्जकम् = c_fully_fold (व्यञ्जकम्, मिच्छ, रिक्त);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      प्रत्यागम list;
	    }

	  वृक्षः c = fold_build2_loc (व्यञ्जकम्_loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, व्यञ्जकम्,
				    build_int_cst (वृक्षः_TYPE (व्यञ्जकम्), 0));
	  जइ (c == boolean_true_ग्रन्थिः)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      व्यञ्जकम् = integer_one_ग्रन्थिः;
	    }

	  ops[idx] = व्यञ्जकम्;

	  जइ (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      अनुवर्त;
	    }
	  भङ्ग;
	}
      जाव (1);

      जइ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	गच्छ cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  जइ (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  प्रत्यागम c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  प्रत्यागम list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

स्थिर वृक्षः
c_parser_oacc_simple_clause (location_t loc, गणना omp_clause_code code,
			     वृक्षः list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  वृक्षः c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  प्रत्यागम c;
}

/* OpenACC:
   async [( int-expr )] */

स्थिर वृक्षः
c_parser_oacc_clause_async (c_parser *parser, वृक्षः list)
{
  वृक्षः c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_ग्रन्थिः, GOMP_ASYNC_NOVAL);

  जइ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      अण्णहा जइ (t == error_mark_ग्रन्थिः
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	प्रत्यागम list;
    }
  अण्णहा
    t = c_fully_fold (t, मिच्छ, रिक्त);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  प्रत्यागम list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

स्थिर वृक्षः
c_parser_oacc_clause_tile (c_parser *parser, वृक्षः list)
{
  वृक्षः c, व्यञ्जकम् = error_mark_ग्रन्थिः;
  location_t loc;
  वृक्षः tile = NULL_वृक्षः;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम list;

  करेहि
    {
      जइ (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	प्रत्यागम list;

      जइ (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  व्यञ्जकम् = integer_zero_ग्रन्थिः;
	}
      अण्णहा
	{
	  location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
	  c_व्यञ्जकम् cexpr = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  cexpr = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, cexpr, मिच्छ, सच्च);
	  व्यञ्जकम् = cexpr.मानम्;

	  जइ (व्यञ्जकम् == error_mark_ग्रन्थिः)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      प्रत्यागम list;
	    }

	  व्यञ्जकम् = c_fully_fold (व्यञ्जकम्, मिच्छ, रिक्त);

	  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्))
	      || !वृक्षः_fits_shwi_p (व्यञ्जकम्)
	      || वृक्षः_to_shwi (व्यञ्जकम्) <= 0)
	    {
	      error_at (व्यञ्जकम्_loc, "%<tile%> argument needs positive"
			" integral constant");
	      व्यञ्जकम् = integer_zero_ग्रन्थिः;
	    }
	}

      tile = वृक्षः_cons (NULL_वृक्षः, व्यञ्जकम्, tile);
    }
  जाव (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenACC:
   wait [( int-expr-list )] */

स्थिर वृक्षः
c_parser_oacc_clause_wait (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  जइ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  अण्णहा
    {
      वृक्षः c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_ग्रन्थिः, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenACC 2.7:
   self [( expression )] */

स्थिर वृक्षः
c_parser_oacc_compute_clause_self (c_parser *parser, वृक्षः list)
{
  वृक्षः t;
  location_t location = c_parser_peek_token (parser)->location;
  जइ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, सच्च, सच्च);
      t = c_objc_common_truthvalue_conversion (loc, व्यञ्जकम्.मानम्);
      t = c_fully_fold (t, मिच्छ, रिक्त);
      parens.skip_until_found_close (parser);
    }
  अण्णहा
    t = truthvalue_true_ग्रन्थिः;

  प्रति (वृक्षः c = list; c; c = OMP_CLAUSE_CHAIN (c))
    जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	प्रत्यागम list;
      }

  वृक्षः c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

स्थिर वृक्षः
c_parser_omp_clause_order (c_parser *parser, वृक्षः list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः c;
  ध्रुव वर्ण *p;
  तार्किक unconstrained = मिच्छ;
  तार्किक reproducible = मिच्छ;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;
  जइ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "unconstrained") == 0)
	unconstrained = सच्च;
      अण्णहा जइ (strcmp (p, "reproducible") == 0)
	reproducible = सच्च;
      अण्णहा
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  गच्छ out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  जइ (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      गच्छ out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
  जइ (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      गच्छ out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;

 out_err:
  parens.skip_until_found_close (parser);
  प्रत्यागम list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

स्थिर वृक्षः
c_parser_omp_clause_bind (c_parser *parser, वृक्षः list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः c;
  ध्रुव वर्ण *p;
  गणना omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;
  जइ (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      प्रत्यागम list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
  जइ (strcmp (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  अण्णहा जइ (strcmp (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  अण्णहा जइ (strcmp (p, "thread") != 0)
    गच्छ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

स्थिर वृक्षः
c_parser_omp_clause_ordered (c_parser *parser, वृक्षः list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  वृक्षः c, अङ्कः = NULL_वृक्षः;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      अङ्कः = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
      parens.skip_until_found_close (parser);
    }
  जइ (अङ्कः == error_mark_ग्रन्थिः)
    प्रत्यागम list;
  जइ (अङ्कः)
    {
      mark_exp_read (अङ्कः);
      अङ्कः = c_fully_fold (अङ्कः, मिच्छ, रिक्त);
      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (अङ्कः))
	  || !वृक्षः_fits_shwi_p (अङ्कः)
	  || (n = वृक्षः_to_shwi (अङ्कः)) <= 0
	  || (पूर्णाङ्क) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  प्रत्यागम list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_व्यञ्जकम् (c) = अङ्कः;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_private (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

स्थिर वृक्षः
c_parser_omp_clause_reduction (c_parser *parser, गणना omp_clause_code kind,
			       तार्किक is_omp, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      तार्किक task = मिच्छ;
      तार्किक inscan = मिच्छ;
      गणना वृक्षः_code code = ERROR_MARK;
      वृक्षः reduc_id = NULL_वृक्षः;

      जइ (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  जइ (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  अण्णहा जइ (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ध्रुव वर्ण *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	      जइ (strcmp (p, "task") == 0)
		task = सच्च;
	      अण्णहा जइ (strcmp (p, "inscan") == 0)
		inscan = सच्च;
	      जइ (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_PLUS:
	  code = PLUS_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_MULT:
	  code = MULT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_MINUS:
	  जइ (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_AND:
	  code = BIT_AND_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_XOR:
	  code = BIT_XOR_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_OR:
	  code = BIT_IOR_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_AND_AND:
	  code = TRUTH_ANDIF_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_OR_OR:
	  code = TRUTH_ORIF_व्यञ्जकम्;
	  भङ्ग;
        पक्ष CPP_NAME:
	  {
	    ध्रुव वर्ण *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	    जइ (strcmp (p, "min") == 0)
	      {
		code = MIN_व्यञ्जकम्;
		भङ्ग;
	      }
	    जइ (strcmp (p, "max") == 0)
	      {
		code = MAX_व्यञ्जकम्;
		भङ्ग;
	      }
	    reduc_id = c_parser_peek_token (parser)->मानम्;
	    भङ्ग;
	  }
	स्वभाव:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  प्रत्यागम list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      जइ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  वृक्षः nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  प्रति (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      वृक्षः d = OMP_CLAUSE_DECL (c), type;
	      जइ (वृक्षः_CODE (d) != OMP_ARRAY_SECTION)
		type = वृक्षः_TYPE (d);
	      अण्णहा
		{
		  पूर्णाङ्क cnt = 0;
		  वृक्षः t;
		  प्रति (t = d;
		      वृक्षः_CODE (t) == OMP_ARRAY_SECTION;
		      t = वृक्षः_OPERAND (t, 0))
		    cnt++;
		  type = वृक्षः_TYPE (t);
		  जाव (cnt > 0)
		    {
		      जइ (वृक्षः_CODE (type) != POINTER_TYPE
			  && वृक्षः_CODE (type) != ARRAY_TYPE)
			भङ्ग;
		      type = वृक्षः_TYPE (type);
		      cnt--;
		    }
		}
	      जाव (वृक्षः_CODE (type) == ARRAY_TYPE)
		type = वृक्षः_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      जइ (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      अण्णहा जइ (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      जइ (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || वृक्षः_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  प्रत्यागम list;
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

स्थिर वृक्षः
c_parser_omp_clause_schedule (c_parser *parser, वृक्षः list)
{
  वृक्षः c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  पूर्णाङ्क modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  जाव (c_parser_next_token_is (parser, CPP_NAME))
    {
      वृक्षः kind = c_parser_peek_token (parser)->मानम्;
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (kind);
      जइ (strcmp ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      अण्णहा जइ (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      अण्णहा जइ (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      अण्णहा
	भङ्ग;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      जइ (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      अण्णहा
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  भङ्ग;
	}
    }
  जइ (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  जइ ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      वृक्षः kind = c_parser_peek_token (parser)->मानम्;
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (kind);

      विकल्प (p[0])
	{
	पक्ष 'd':
	  जइ (strcmp ("dynamic", p) != 0)
	    गच्छ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  भङ्ग;

        पक्ष 'g':
	  जइ (strcmp ("guided", p) != 0)
	    गच्छ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  भङ्ग;

	पक्ष 'r':
	  जइ (strcmp ("runtime", p) != 0)
	    गच्छ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  भङ्ग;

	स्वभाव:
	  गच्छ invalid_kind;
	}
    }
  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  अण्णहा जइ (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  अण्णहा
    गच्छ invalid_kind;

  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (here, व्यञ्जकम्, मिच्छ, सच्च);
      t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);

      जइ (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      अण्णहा जइ (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      अण्णहा जइ (वृक्षः_CODE (वृक्षः_TYPE (t)) == INTEGER_TYPE
	       || वृक्षः_CODE (वृक्षः_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  वृक्षः s = fold_build2_loc (loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, t,
				    build_int_cst (वृक्षः_TYPE (t), 0));
	  protected_set_व्यञ्जकम्_location (s, loc);
	  जइ (s == boolean_true_ग्रन्थिः)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_ग्रन्थिः;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_व्यञ्जकम् (c) = t;
	}
      अण्णहा
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  अण्णहा
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (गणना omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  प्रत्यागम list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_shared (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

स्थिर वृक्षः
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, वृक्षः list)
{
  वृक्षः c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  प्रत्यागम c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

स्थिर वृक्षः
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    गणना omp_clause_code code, वृक्षः list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  वृक्षः c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  प्रत्यागम c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

स्थिर वृक्षः
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				गणना omp_clause_code code, वृक्षः list)
{
  वृक्षः c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  प्रत्यागम c;
}

/* OpenMP 4.5:
   nogroup */

स्थिर वृक्षः
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, वृक्षः list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  वृक्षः c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 4.5:
   simd
   threads */

स्थिर वृक्षः
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 गणना omp_clause_code code, वृक्षः list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  वृक्षः c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

स्थिर वृक्षः
c_parser_omp_clause_अङ्कः_teams (c_parser *parser, वृक्षः list)
{
  location_t अङ्कः_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (upper_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः c, upper = व्यञ्जकम्.मानम्, lower = NULL_वृक्षः;
      upper = c_fully_fold (upper, मिच्छ, रिक्त);

      जइ (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  व्यञ्जकम् = convert_lvalue_to_rvalue (upper_loc, व्यञ्जकम्, मिच्छ, सच्च);
	  upper = व्यञ्जकम्.मानम्;
	  upper = c_fully_fold (upper, मिच्छ, रिक्त);
	}

      parens.skip_until_found_close (parser);

      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (वृक्षः_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  प्रत्यागम list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, upper,
			   build_int_cst (वृक्षः_TYPE (upper), 0));
      protected_set_व्यञ्जकम्_location (c, upper_loc);
      जइ (c == boolean_true_ग्रन्थिः)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_ग्रन्थिः;
	}
      जइ (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, lower,
			       build_int_cst (वृक्षः_TYPE (lower), 0));
	  protected_set_व्यञ्जकम्_location (c, lower_loc);
	  जइ (c == boolean_true_ग्रन्थिः)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_वृक्षः;
	    }
	  अण्णहा जइ (वृक्षः_CODE (lower) == INTEGER_CST
		   && वृक्षः_CODE (upper) == INTEGER_CST
		   && वृक्षः_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_वृक्षः;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अङ्कः_TEAMS, "num_teams");

      c = build_omp_clause (अङ्कः_teams_loc, OMP_CLAUSE_अङ्कः_TEAMS);
      OMP_CLAUSE_अङ्कः_TEAMS_UPPER_व्यञ्जकम् (c) = upper;
      OMP_CLAUSE_अङ्कः_TEAMS_LOWER_व्यञ्जकम् (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

स्थिर वृक्षः
c_parser_omp_clause_thread_limit (c_parser *parser, वृक्षः list)
{
  location_t अङ्कः_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः c, t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);

      parens.skip_until_found_close (parser);

      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  प्रत्यागम list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (व्यञ्जकम्_loc, LE_व्यञ्जकम्, boolean_type_ग्रन्थिः, t,
			   build_int_cst (वृक्षः_TYPE (t), 0));
      protected_set_व्यञ्जकम्_location (c, व्यञ्जकम्_loc);
      जइ (c == boolean_true_ग्रन्थिः)
	{
	  warning_at (व्यञ्जकम्_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_ग्रन्थिः;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (अङ्कः_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_व्यञ्जकम् (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  प्रत्यागम list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

स्थिर वृक्षः
c_parser_omp_clause_aligned (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्षः nl, c;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  जइ (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      वृक्षः alignment = व्यञ्जकम्.मानम्;
      alignment = c_fully_fold (alignment, मिच्छ, रिक्त);
      जइ (वृक्षः_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (वृक्षः_TYPE (alignment))
	  || वृक्षः_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_वृक्षः;
	}

      प्रति (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  प्रत्यागम nl;
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

स्थिर वृक्षः
c_parser_omp_clause_allocate (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्षः nl, c;
  वृक्षः allocator = NULL_वृक्षः;
  वृक्षः align = NULL_वृक्षः;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      तार्किक has_modifiers = मिच्छ;
      वृक्षः orig_type = NULL_वृक्षः;
      जइ (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  unsigned पूर्णाङ्क n = 3;
	  ध्रुव वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	  जइ ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      जइ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = सच्च;
	      अण्णहा जइ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ध्रुव वर्ण *q = IDENTIFIER_POINTER (tok->मानम्);
		  n += 4;
		  जइ ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = सच्च;
		}
	    }
	  जइ (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
	      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
	      जइ (व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
		;
	      अण्णहा जइ (strcmp (p, "allocator") == 0)
		{
		  allocator = व्यञ्जकम्.मानम्;
		  allocator = c_fully_fold (allocator, मिच्छ, रिक्त);
		  orig_type = व्यञ्जकम्.original_type
			      ? व्यञ्जकम्.original_type : वृक्षः_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      अण्णहा
		{
		  align = व्यञ्जकम्.मानम्;
		  align = c_fully_fold (align, मिच्छ, रिक्त);
		}
	      parens2.skip_until_found_close (parser);
	      जइ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ध्रुव वर्ण *q = "";
		  जइ (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->मानम्);
		  जइ (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      प्रत्यागम list;
		    }
		  अण्णहा जइ (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      प्रत्यागम list;
		    }
		  c_parser_consume_token (parser);
		  जइ (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      प्रत्यागम list;
		    }
		  व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
		  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
		  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ,
						   सच्च);
		  जइ (strcmp (q, "allocator") == 0)
		    {
		      allocator = व्यञ्जकम्.मानम्;
		      allocator = c_fully_fold (allocator, मिच्छ, रिक्त);
		      orig_type = व्यञ्जकम्.original_type
				  ? व्यञ्जकम्.original_type : वृक्षः_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  अण्णहा
		    {
		      align = व्यञ्जकम्.मानम्;
		      align = c_fully_fold (align, मिच्छ, रिक्त);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      जइ (!has_modifiers)
	{
	  location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
	  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
	  जइ (व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः)
	    {
	      allocator = व्यञ्जकम्.मानम्;
	      allocator = c_fully_fold (allocator, मिच्छ, रिक्त);
	      orig_type = व्यञ्जकम्.original_type
			  ? व्यञ्जकम्.original_type : वृक्षः_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      जइ (allocator
	  && (!INTEGRAL_TYPE_P (वृक्षः_TYPE (allocator))
	      || वृक्षः_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				वृक्षः_TYPE (allocator));
          allocator = NULL_वृक्षः;
        }
      जइ (align
	  && (!INTEGRAL_TYPE_P (वृक्षः_TYPE (align))
	      || !वृक्षः_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_वृक्षः;
	}
      जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  प्रत्यागम list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  जइ (allocator || align)
    प्रति (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  प्रत्यागम nl;
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

स्थिर वृक्षः
c_parser_omp_clause_uses_allocators (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्षः nl = list;
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

parse_next:

  तार्किक has_modifiers = मिच्छ;
  तार्किक seen_allocators = मिच्छ;
  वृक्षः memspace_व्यञ्जकम् = NULL_वृक्षः;
  वृक्षः traits_var = NULL_वृक्षः;

  जइ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      unsigned पूर्णाङ्क n = 3;
      ध्रुव वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  जइ (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = सच्च;
	  अण्णहा जइ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ध्रुव वर्ण *q = IDENTIFIER_POINTER (tok->मानम्);
	      n += 4;
	      जइ ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  जइ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = सच्च;
		  जइ ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ध्रुव वर्ण *m = IDENTIFIER_POINTER (tok->मानम्);
		      जइ (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  गच्छ end;
			}
		    }
		}
	    }
	}
      जइ (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  जइ (व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
	    ;
	  अण्णहा जइ (strcmp (p, "traits") == 0)
	    {
	      traits_var = व्यञ्जकम्.मानम्;
	      traits_var = c_fully_fold (traits_var, मिच्छ, रिक्त);
	      mark_exp_read (traits_var);
	    }
	  अण्णहा
	    {
	      memspace_व्यञ्जकम् = व्यञ्जकम्.मानम्;
	      memspace_व्यञ्जकम् = c_fully_fold (memspace_व्यञ्जकम्, मिच्छ, रिक्त);
	    }
	  parens2.skip_until_found_close (parser);
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ध्रुव वर्ण *q = "";
	      जइ (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->मानम्);
	      जइ (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  प्रत्यागम list;
		}
	      अण्णहा जइ (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  प्रत्यागम list;
		}
	      c_parser_consume_token (parser);
	      जइ (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  प्रत्यागम list;
		}
	      व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	      जइ (strcmp (q, "traits") == 0)
		{
		  traits_var = व्यञ्जकम्.मानम्;
		  traits_var = c_fully_fold (traits_var, मिच्छ, रिक्त);
		  mark_exp_read (traits_var);
		}
	      अण्णहा
		{
		  memspace_व्यञ्जकम् = व्यञ्जकम्.मानम्;
		  memspace_व्यञ्जकम् = c_fully_fold (memspace_व्यञ्जकम्, मिच्छ, रिक्त);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    गच्छ end;
	}
    }

  जाव (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ध्रुव वर्ण *tok_s = IDENTIFIER_POINTER (tok->मानम्);
      वृक्षः t = lookup_name (tok->मानम्);
      जइ (t == NULL_वृक्षः)
	{
	  undeclared_variable (tok->location, tok->मानम्);
	  t = error_mark_ग्रन्थिः;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      वृक्षः legacy_traits = NULL_वृक्षः;
      जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ध्रुव वर्ण *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  जइ (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      गच्छ end;
	    }
	  legacy_traits = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
	  जइ (legacy_traits == error_mark_ग्रन्थिः)
	    गच्छ end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  जइ (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_निवेशय_after (close_loc, ": ");
	      richloc.add_fixit_निवेशय_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      जइ (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  गच्छ end;
	}
      seen_allocators = सच्च;

      वृक्षः c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_व्यञ्जकम्;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }

  जइ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      गच्छ parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  प्रत्यागम nl;
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

स्थिर वृक्षः
c_parser_omp_clause_linear (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  वृक्षः nl, c, step;
  गणना omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  तार्किक old_linear_modifier = मिच्छ;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (tok->मानम्);
      जइ (strcmp ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      जइ (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      जइ (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = सच्च;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  जइ (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  जइ (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = व्यञ्जकम्_loc;
      तार्किक has_modifiers = मिच्छ;
      जइ (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ध्रुव वर्ण *p = IDENTIFIER_POINTER (tok->मानम्);
	  unsigned पूर्णाङ्क pos = 0;
	  जइ (strcmp ("val", p) == 0)
	    pos = 2;
	  अण्णहा जइ (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      जइ (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      अण्णहा
		pos = 0;
	    }
	  जइ (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      जइ (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = सच्च;
	    }
	}
      जइ (has_modifiers)
	{
	  step = NULL_वृक्षः;
	  जाव (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ध्रुव वर्ण *p = IDENTIFIER_POINTER (tok->मानम्);
	      जइ (strcmp ("val", p) == 0)
		{
		  जइ (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      अण्णहा जइ (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  जइ (parens2.require_open (parser))
		    {
		      जइ (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
		      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
		      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ,
						       सच्च);
		      step = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
		      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_ग्रन्थिः;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  अण्णहा
		    भङ्ग;
		}
	      अण्णहा
		भङ्ग;
	      जइ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  अनुवर्त;
		}
	      भङ्ग;
	    }
	  जइ (!step)
	    step = integer_one_ग्रन्थिः;
	}
      अण्णहा
	{
	  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
	  step = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
	  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_ग्रन्थिः;
	    }
	}

    }
  अण्णहा
    step = integer_one_ग्रन्थिः;

  प्रति (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  जइ (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      जइ (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  जइ (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_निवेशय_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_निवेशय_before (close_loc, ")");
	    }
	  अण्णहा
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  प्रत्यागम nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_nontemporal (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

स्थिर वृक्षः
c_parser_omp_clause_safelen (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्षः c, t;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
  t = व्यञ्जकम्.मानम्;
  t = c_fully_fold (t, मिच्छ, रिक्त);
  जइ (वृक्षः_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (वृक्षः_TYPE (t))
      || वृक्षः_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_वृक्षः;
    }

  parens.skip_until_found_close (parser);
  जइ (t == NULL_वृक्षः || t == error_mark_ग्रन्थिः)
    प्रत्यागम list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

स्थिर वृक्षः
c_parser_omp_clause_simdlen (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्षः c, t = NULL_वृक्षः, type = NULL_वृक्षः, भाजकः = NULL_वृक्षः;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  unsigned pos = 3;
  जइ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      संरचना c_type_name *ctype = c_parser_type_name (parser);
      जइ (ctype == रिक्त
	  || (type = groktypename (ctype, रिक्त, रिक्त)) == रिक्त
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && वृक्षः_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_ग्रन्थिः;
	}
      अण्णहा जइ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  व्यञ्जकम् = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, मिच्छ, सच्च);
	  भाजकः = व्यञ्जकम्.मानम्;
	  भाजकः = c_fully_fold (भाजकः, मिच्छ, रिक्त);
	  जइ (वृक्षः_CODE (भाजकः) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (वृक्षः_TYPE (भाजकः))
	      || वृक्षः_int_cst_sgn (भाजकः) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_ग्रन्थिः;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  जइ (type != error_mark_ग्रन्थिः)
    {
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);
      जइ (वृक्षः_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (वृक्षः_TYPE (t))
	  || वृक्षः_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_वृक्षः;
	}
    }

  parens.skip_until_found_close (parser);
  जइ (type == error_mark_ग्रन्थिः || t == NULL_वृक्षः || t == error_mark_ग्रन्थिः)
    प्रत्यागम list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_भाजकः (c) = भाजकः;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

स्थिर वृक्षः
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   वृक्षः list, तार्किक depend_p)
{
  वृक्षः vec = रिक्त;
  जइ (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      प्रत्यागम list;
    }

  जइ (!depend_p)
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_सङ्ख्या
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  वृक्षः val = c_parser_peek_nth_token (parser, 3)->मानम्;
	  जइ (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      वृक्षः u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      प्रत्यागम u;
	    }
	}
    }



  जाव (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      वृक्षः t = lookup_name (c_parser_peek_token (parser)->मानम्);
      वृक्षः addend = रिक्त;

      जइ (t == NULL_वृक्षः)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->मानम्);
	  t = error_mark_ग्रन्थिः;
	}

      c_parser_consume_token (parser);

      तार्किक neg = मिच्छ;
      जइ (c_parser_next_token_is (parser, CPP_MINUS))
	neg = सच्च;
      अण्णहा जइ (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_ग्रन्थिः;
	  neg = मिच्छ;
	  गच्छ add_to_vector;
	}
      c_parser_consume_token (parser);

      जइ (c_parser_next_token_is_not (parser, CPP_सङ्ख्या))
	{
	  c_parser_error (parser, "expected integer");
	  प्रत्यागम list;
	}

      addend = c_parser_peek_token (parser)->मानम्;
      जइ (वृक्षः_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  प्रत्यागम list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      जइ (t != error_mark_ग्रन्थिः)
	{
	  vec = वृक्षः_cons (addend, t, vec);
	  जइ (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      जइ (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	भङ्ग;

      c_parser_consume_token (parser);
    }

  जइ (vec == NULL_वृक्षः)
    प्रत्यागम list;

  वृक्षः u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  प्रत्यागम u;
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

स्थिर वृक्षः
c_parser_omp_iterators (c_parser *parser)
{
  वृक्षः ret = NULL_वृक्षः, *last = &ret;
  c_parser_consume_token (parser);

  प्रक्षिप_scope ();

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम error_mark_ग्रन्थिः;

  करेहि
    {
      वृक्षः iter_type = NULL_वृक्षः, type_व्यञ्जकम् = NULL_वृक्षः;
      जइ (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  संरचना c_type_name *type = c_parser_type_name (parser);
	  जइ (type != रिक्त)
	    iter_type = groktypename (type, &type_व्यञ्जकम्, रिक्त);
	}
      जइ (iter_type == NULL_वृक्षः)
	iter_type = integer_type_ग्रन्थिः;

      location_t loc = c_parser_peek_token (parser)->location;
      जइ (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  भङ्ग;
	}

      वृक्षः id = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);

      जइ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	भङ्ग;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (eloc, व्यञ्जकम्, सच्च, मिच्छ);
      वृक्षः begin = व्यञ्जकम्.मानम्;

      जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	भङ्ग;

      eloc = c_parser_peek_token (parser)->location;
      व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (eloc, व्यञ्जकम्, सच्च, मिच्छ);
      वृक्षः end = व्यञ्जकम्.मानम्;

      वृक्षः step = integer_one_ग्रन्थिः;
      जइ (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	  व्यञ्जकम् = convert_lvalue_to_rvalue (eloc, व्यञ्जकम्, सच्च, मिच्छ);
	  step = व्यञ्जकम्.मानम्;
	}

      वृक्षः iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &वृक्षः_CHAIN (*last);

      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}
      भङ्ग;
    }
  जाव (1);

  parens.skip_until_found_close (parser);
  प्रत्यागम ret ? ret : error_mark_ग्रन्थिः;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

स्थिर वृक्षः
c_parser_omp_clause_affinity (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्षः nl, iterators = NULL_वृक्षः;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      तार्किक parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      जइ (parse_iter)
	{
	  unsigned n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      जइ (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      जइ (iterators)
		निष्कासय_scope ();
	      parens.skip_until_found_close (parser);
	      प्रत्यागम list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  जइ (iterators)
    {
      वृक्षः block = निष्कासय_scope ();
      जइ (iterators != error_mark_ग्रन्थिः)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  प्रति (वृक्षः c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_वृक्षः_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  प्रत्यागम nl;
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

स्थिर वृक्षः
c_parser_omp_clause_depend (c_parser *parser, वृक्षः list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  गणना omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  गणना omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  वृक्षः nl, c, iterators = NULL_वृक्षः;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  करेहि
    {
      जइ (c_parser_next_token_is_not (parser, CPP_NAME))
	गच्छ invalid_kind;

      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp ("iterator", p) == 0 && iterators == NULL_वृक्षः)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  अनुवर्त;
	}
      जइ (strcmp ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      अण्णहा जइ (strcmp ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      अण्णहा जइ (strcmp ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      अण्णहा जइ (strcmp ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      अण्णहा जइ (strcmp ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      अण्णहा जइ (strcmp ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      अण्णहा जइ (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      अण्णहा जइ (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      अण्णहा
	गच्छ invalid_kind;
      भङ्ग;
    }
  जाव (1);

  c_parser_consume_token (parser);

  जइ (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      निष्कासय_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_वृक्षः;
    }

  जइ (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_वृक्षः;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      प्रत्यागम c;
    }

  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    गच्छ resync_fail;

  जइ (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, सच्च);
  अण्णहा
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      जइ (iterators)
	{
	  वृक्षः block = निष्कासय_scope ();
	  जइ (iterators == error_mark_ग्रन्थिः)
	    iterators = NULL_वृक्षः;
	  अण्णहा
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      प्रति (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  जइ (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_वृक्षः_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  प्रत्यागम nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  जइ (iterators)
    निष्कासय_scope ();
  प्रत्यागम list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

स्थिर वृक्षः
c_parser_omp_clause_doacross (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  गणना omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  वृक्षः nl;
  ध्रुव वर्ण *p;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (c_parser_next_token_is_not (parser, CPP_NAME))
    गच्छ invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
  जइ (strcmp ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  अण्णहा जइ (strcmp ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  अण्णहा
    गच्छ invalid_kind;

  c_parser_consume_token (parser);

  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    गच्छ resync_fail;

  जइ (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      जइ (c_parser_next_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_वृक्षः;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  अण्णहा
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, मिच्छ);

  parens.skip_until_found_close (parser);
  प्रत्यागम nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  प्रत्यागम list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

स्थिर वृक्षः
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  गणना omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  unsigned n = 3;
  जइ (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  प्रत्यागम list;
	}
      c_parser_consume_token (parser);
      जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	प्रत्यागम list;
      p = "";
      जइ (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      अण्णहा जइ (strcmp (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      अण्णहा जइ (strcmp (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      अण्णहा
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  प्रत्यागम list;
	}
      c_parser_consume_token (parser);
      जइ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	प्रत्यागम list;
      जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	प्रत्यागम list;
    }
  location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
  वृक्षः size = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
  parens.skip_until_found_close (parser);

  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (size)))
    {
      error_at (व्यञ्जकम्_loc, "expected integer expression");
      प्रत्यागम list;
    }

  /* Attempt to statically determine when the number is negative.  */
  वृक्षः c = fold_build2_loc (व्यञ्जकम्_loc, LT_व्यञ्जकम्, boolean_type_ग्रन्थिः, size,
			    build_int_cst (वृक्षः_TYPE (size), 0));
  protected_set_व्यञ्जकम्_location (c, व्यञ्जकम्_loc);
  जइ (c == boolean_true_ग्रन्थिः)
    {
      warning_at (व्यञ्जकम्_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_ग्रन्थिः;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_व्यञ्जकम् (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  प्रत्यागम list;
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

स्थिर वृक्षः
c_parser_omp_clause_map (c_parser *parser, वृक्षः list, तार्किक declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्षः nl, c;
  गणना gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  पूर्णाङ्क pos = 1;
  पूर्णाङ्क map_kind_pos = 0;
  पूर्णाङ्क iterator_length = 0;
  प्रति (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      जइ (tok->type != CPP_NAME)
	भङ्ग;

      ध्रुव वर्ण *p = IDENTIFIER_POINTER (tok->मानम्);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      जइ (strcmp (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  unsigned n = pos + 2;
	  जइ (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      जइ (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  भङ्ग;
	}

      जइ (next_tok->type == CPP_COMMA)
	pos++;
      अण्णहा जइ (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  unsigned पूर्णाङ्क npos = pos + 2;
	  जइ (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  पूर्णाङ्क always_modifier = 0;
  पूर्णाङ्क close_modifier = 0;
  पूर्णाङ्क present_modifier = 0;
  पूर्णाङ्क mapper_modifier = 0;
  पूर्णाङ्क अङ्कः_commas = 0;
  पूर्णाङ्क अङ्कः_identifiers = 0;
  वृक्षः mapper_name = NULL_वृक्षः;
  वृक्षः iterators = NULL_वृक्षः;
  प्रति (पूर्णाङ्क pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      जइ (tok->type == CPP_COMMA)
	{
	  ++अङ्कः_commas;
	  जइ (अङ्कः_commas > अङ्कः_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}

      ध्रुव वर्ण *p = IDENTIFIER_POINTER (tok->मानम्);
      जइ (strcmp ("always", p) == 0)
	{
	  जइ (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      प्रत्यागम list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (strcmp ("close", p) == 0)
	{
	  जइ (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      प्रत्यागम list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (strcmp ("iterator", p) == 0)
	{
	  जइ (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      प्रत्यागम list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      अण्णहा जइ (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  जइ (mparens.require_open (parser))
	    {
	      जइ (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  प्रत्यागम list;
		}

	      tok = c_parser_peek_token (parser);

	      विकल्प (tok->type)
		{
		पक्ष CPP_NAME:
		  {
		    mapper_name = tok->मानम्;
		    c_parser_consume_token (parser);
		    जइ (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  भङ्ग;

		पक्ष CPP_KEYWORD:
		  जइ (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      भङ्ग;
		    }
		  /* Fallthrough.  */

		स्वभाव:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  प्रत्यागम list;
		}

	      जइ (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  प्रत्यागम list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      अण्णहा जइ (strcmp ("present", p) == 0)
	{
	  जइ (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      प्रत्यागम list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      अण्णहा
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  प्रत्यागम list;
	}
      ++अङ्कः_identifiers;
      जइ (अङ्कः_identifiers - 1 > अङ्कः_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_निवेशय_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      अङ्कः_commas = अङ्कः_identifiers - 1;
    }

  जइ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      पूर्णाङ्क always_present_modifier = always_modifier && present_modifier;

      जइ (strcmp ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      अण्णहा जइ (strcmp ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      अण्णहा जइ (strcmp ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      अण्णहा जइ (strcmp ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      अण्णहा जइ (strcmp ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      अण्णहा जइ (strcmp ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      अण्णहा
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  प्रत्यागम list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   सच्च);

  वृक्षः last_new = NULL_वृक्षः;

  जइ (iterators)
    {
      वृक्षः block = निष्कासय_scope ();
      जइ (iterators == error_mark_ग्रन्थिः)
	iterators = NULL_वृक्षः;
      अण्णहा
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  प्रति (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  जइ (mapper_name)
    {
      वृक्षः name = build_omp_clause (निवेशः_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_प्रक्षिप_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (निवेशः_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_निष्कासय_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_ग्रन्थिः;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  प्रत्यागम nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

स्थिर वृक्षः
c_parser_omp_clause_device (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t व्यञ्जकम्_loc;
  c_व्यञ्जकम् व्यञ्जकम्;
  वृक्षः c, t;
  तार्किक ancestor = मिच्छ;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (tok->मानम्);
      जइ (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  जइ ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      प्रत्यागम list;
	    }
	  ancestor = सच्च;
	}
      अण्णहा जइ (strcmp ("device_num", p) == 0)
	;
      अण्णहा
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  प्रत्यागम list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
  t = व्यञ्जकम्.मानम्;
  t = c_fully_fold (t, मिच्छ, रिक्त);

  parens.skip_until_found_close (parser);

  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      प्रत्यागम list;
    }
  जइ (ancestor && वृक्षः_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (व्यञ्जकम्_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      प्रत्यागम list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  प्रत्यागम list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

स्थिर वृक्षः
c_parser_omp_clause_dist_schedule (c_parser *parser, वृक्षः list)
{
  वृक्षः c, t = NULL_वृक्षः;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      प्रत्यागम list;
    }

  c_parser_consume_token (parser);
  जइ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      t = व्यञ्जकम्.मानम्;
      t = c_fully_fold (t, मिच्छ, रिक्त);
      parens.skip_until_found_close (parser);
    }
  अण्णहा
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  जइ (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  जइ (t == error_mark_ग्रन्थिः)
    प्रत्यागम list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

स्थिर वृक्षः
c_parser_omp_clause_proc_bind (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  गणना omp_clause_proc_bind_kind kind;
  वृक्षः c;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      अण्णहा जइ (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      अण्णहा जइ (strcmp ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      अण्णहा जइ (strcmp ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      अण्णहा
	गच्छ invalid_kind;
    }
  अण्णहा
    गच्छ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  प्रत्यागम list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

स्थिर वृक्षः
c_parser_omp_clause_device_type (c_parser *parser, वृक्षः list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  गणना omp_clause_device_type_kind kind;
  वृक्षः c;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      अण्णहा जइ (strcmp ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      अण्णहा जइ (strcmp ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      अण्णहा
	गच्छ invalid_kind;
    }
  अण्णहा
    गच्छ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  प्रत्यागम list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

स्थिर वृक्षः
c_parser_omp_clause_from_to (c_parser *parser, गणना omp_clause_code kind,
			     वृक्षः list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  पूर्णाङ्क pos = 1, colon_pos = 0;
  पूर्णाङ्क iterator_length = 0;

  जाव (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ध्रुव वर्ण *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->मानम्);
      जइ (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  unsigned पूर्णाङ्क npos = pos + 2;
	  जइ (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      जइ (strcmp (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      जइ (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      अण्णहा
	pos++;
      जइ (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  भङ्ग;
	}
    }

  तार्किक present = मिच्छ, mapper_modifier = मिच्छ;
  वृक्षः iterators = NULL_वृक्षः;
  वृक्षः mapper_name = NULL_वृक्षः;

  प्रति (पूर्णाङ्क pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      जइ (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (token->मानम्);
      जइ (strcmp ("present", p) == 0)
	{
	  जइ (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      प्रत्यागम list;
	    }
	  present = सच्च;
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (strcmp ("iterator", p) == 0)
	{
	  जइ (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      प्रत्यागम list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      अण्णहा जइ (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  जइ (mparens.require_open (parser))
	    {
	      जइ (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  प्रत्यागम list;
		}

	      token = c_parser_peek_token (parser);
	      विकल्प (token->type)
		{
		पक्ष CPP_NAME:
		  {
		    mapper_name = token->मानम्;
		    c_parser_consume_token (parser);
		  }
		  भङ्ग;
		पक्ष CPP_KEYWORD:
		  जइ (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      भङ्ग;
		    }
		  /* FALLTHROUGH  */
		स्वभाव:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  प्रत्यागम list;
		}
	      जइ (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  प्रत्यागम list;
		}
	      mapper_modifier = सच्च;
	      pos += 3;
	    }
	}
      अण्णहा
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  प्रत्यागम list;
	}
    }

  जइ (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  वृक्षः nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  जइ (present)
    प्रति (वृक्षः c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  जइ (iterators)
    {
      वृक्षः block = निष्कासय_scope ();
      जइ (iterators == error_mark_ग्रन्थिः)
	iterators = NULL_वृक्षः;
      अण्णहा
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  जइ (iterators)
    प्रति (वृक्षः c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  जइ (mapper_name)
    {
      वृक्षः last_new = NULL_वृक्षः;
      प्रति (वृक्षः c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      वृक्षः name = build_omp_clause (निवेशः_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_प्रक्षिप_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (निवेशः_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_निष्कासय_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_ग्रन्थिः;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  प्रत्यागम nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_uniform (c_parser *parser, वृक्षः list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  प्रत्यागम list;
}

/* OpenMP 5.1
   full */

स्थिर वृक्षः
c_parser_omp_clause_full (c_parser *parser, वृक्षः list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

स्थिर वृक्षः
c_parser_omp_clause_partial (c_parser *parser, वृक्षः list)
{
  वृक्षः अङ्कः = NULL_वृक्षः;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      अङ्कः = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
      parens.skip_until_found_close (parser);

      जइ (अङ्कः == error_mark_ग्रन्थिः)
	प्रत्यागम list;

      mark_exp_read (अङ्कः);
      अङ्कः = c_fully_fold (अङ्कः, मिच्छ, रिक्त);
      HOST_WIDE_INT n;
      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (अङ्कः))
	  || !वृक्षः_fits_shwi_p (अङ्कः)
	  || (n = वृक्षः_to_shwi (अङ्कः)) <= 0
	  || (पूर्णाङ्क) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  प्रत्यागम list;
	}
    }

  वृक्षः c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_व्यञ्जकम् (c) = अङ्कः;
  OMP_CLAUSE_CHAIN (c) = list;
  प्रत्यागम c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

स्थिर वृक्षः
c_parser_omp_clause_novariants (c_parser *parser, वृक्षः list)
{
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  वृक्षः t = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, सच्च, सच्च).मानम्;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, मिच्छ, रिक्त);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  वृक्षः c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  प्रत्यागम list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

स्थिर वृक्षः
c_parser_omp_clause_nocontext (c_parser *parser, वृक्षः list)
{
  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
  वृक्षः t = convert_lvalue_to_rvalue (loc, व्यञ्जकम्, सच्च, सच्च).मानम्;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, मिच्छ, रिक्त);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  वृक्षः c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_व्यञ्जकम् (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  प्रत्यागम list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

स्थिर वृक्षः
c_parser_omp_clause_detach (c_parser *parser, वृक्षः list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  जइ (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      प्रत्यागम list;
    }

  वृक्षः t = lookup_name (c_parser_peek_token (parser)->मानम्);
  जइ (t == NULL_वृक्षः)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->मानम्);
      parens.skip_until_found_close (parser);
      प्रत्यागम list;
    }
  c_parser_consume_token (parser);

  वृक्षः type = TYPE_MAIN_VARIANT (वृक्षः_TYPE (t));
  जइ (!INTEGRAL_TYPE_P (type)
      || वृक्षः_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      प्रत्यागम list;
    }

  वृक्षः u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  प्रत्यागम u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_destroy (c_parser *parser, वृक्षः list)
{
  वृक्षः nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  प्रति (वृक्षः c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    वृक्षः_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  प्रत्यागम nl;
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

स्थिर वृक्षः
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम error_mark_ग्रन्थिः;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  जइ (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    जाव (सच्च)
      {
	str += (वर्ण) GOMP_INTEROP_IFR_SEPARATOR;
	जइ (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_व्यञ्जकम् cval = c_parser_string_literal (parser, मिच्छ, मिच्छ);
	    जइ (cval.मानम् == error_mark_ग्रन्थिः)
	      प्रत्यागम error_mark_ग्रन्थिः;
	    जइ ((size_t) वृक्षः_STRING_LENGTH (cval.मानम्)
		!= strlen (वृक्षः_STRING_POINTER (cval.मानम्)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = सच्च;
		प्रत्यागम error_mark_ग्रन्थिः;
	      }

	    वर्ण c = omp_get_fr_id_from_name (वृक्षः_STRING_POINTER (cval.मानम्));
	    जइ (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  वृक्षः_STRING_POINTER (cval.मानम्));
	    str += c;
	  }
	अण्णहा
	  {
	    c_व्यञ्जकम् cval = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	    वृक्षः मानम् = c_fully_fold (cval.मानम्, मिच्छ, रिक्त);
	    जइ (INTEGRAL_TYPE_P (वृक्षः_TYPE (मानम्))
		&& वृक्षः_CODE (मानम्) != INTEGER_CST)
	      मानम् = convert_lvalue_to_rvalue (cval.get_start (), cval,
						मिच्छ, सच्च).मानम्;
	    जइ (वृक्षः_CODE (मानम्) != INTEGER_CST
		|| !वृक्षः_fits_shwi_p (मानम्))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		प्रत्यागम error_mark_ग्रन्थिः;
	      }
	    HOST_WIDE_INT n = वृक्षः_to_shwi (मानम्);
	    जइ (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (वर्ण) n;
	  }
	str += (वर्ण) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	जइ (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    अनुवर्त;
	  }
	जइ (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  प्रत्यागम error_mark_ग्रन्थिः;
	str += '\0';
	वृक्षः res = build_string (str.length (), str.data ());
	वृक्षः_TYPE (res) = build_array_type_nelts (unsigned_char_type_ग्रन्थिः,
						  str.length ());
	प्रत्यागम res;
      }

  /* New format. */
  std::string str2;
  जाव (सच्च)
    {
      जइ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	प्रत्यागम error_mark_ग्रन्थिः;
      str += (वर्ण) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      तार्किक has_fr = मिच्छ;
      जाव (सच्च)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  जइ (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_POINTER (tok->मानम्)) != 0
		  && strcmp("attr", IDENTIFIER_POINTER (tok->मानम्)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      प्रत्यागम error_mark_ग्रन्थिः;
	    }
	  c_parser_consume_token (parser);
	  तार्किक is_fr = IDENTIFIER_POINTER (tok->मानम्)[0] == 'f';
	  जइ (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      प्रत्यागम error_mark_ग्रन्थिः;
	    }
	  जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    प्रत्यागम error_mark_ग्रन्थिः;
	  जाव (सच्च)
	    {
	      जइ (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_व्यञ्जकम् cval = c_parser_string_literal (parser, मिच्छ, मिच्छ);
		  वृक्षः मानम् = cval.मानम्;
		  जइ (मानम् == error_mark_ग्रन्थिः)
		    प्रत्यागम error_mark_ग्रन्थिः;
		  जइ ((size_t) वृक्षः_STRING_LENGTH (मानम्)
		      != strlen (वृक्षः_STRING_POINTER (मानम्)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = सच्च;
		      प्रत्यागम error_mark_ग्रन्थिः;
		    }
		  जइ (!is_fr)
		    {
		      जइ (!startswith (वृक्षः_STRING_POINTER (मानम्), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = सच्च;
			  प्रत्यागम error_mark_ग्रन्थिः;
			}
		      जइ (strchr (वृक्षः_STRING_POINTER (मानम्), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = सच्च;
			  प्रत्यागम error_mark_ग्रन्थिः;
			}
		      str2 += वृक्षः_STRING_POINTER (मानम्);
		      str2 += '\0';
		    }
		  अण्णहा
		    {
		      जइ (*वृक्षः_STRING_POINTER (मानम्) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  प्रत्यागम error_mark_ग्रन्थिः;
			}
		      वर्ण c = omp_get_fr_id_from_name (वृक्षः_STRING_POINTER (मानम्));
		      जइ (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    वृक्षः_STRING_POINTER (मानम्));
		     str += c;
		     has_fr = सच्च;
		    }
		}
	      अण्णहा जइ (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  प्रत्यागम error_mark_ग्रन्थिः;
		}
	      अण्णहा
		{
		  c_व्यञ्जकम् cval = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
		  वृक्षः मानम् = c_fully_fold (cval.मानम्, मिच्छ, रिक्त);
		  जइ (INTEGRAL_TYPE_P (वृक्षः_TYPE (मानम्))
		      && वृक्षः_CODE (मानम्) != INTEGER_CST)
		    मानम् = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      मिच्छ, सच्च).मानम्;

		  जइ (वृक्षः_CODE (मानम्) != INTEGER_CST
		      || !वृक्षः_fits_shwi_p (मानम्))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      प्रत्यागम error_mark_ग्रन्थिः;
		    }
		  HOST_WIDE_INT n = वृक्षः_to_shwi (मानम्);
		  जइ (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (वर्ण) n;
		  has_fr = सच्च;
		}
	      जइ (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  अनुवर्त;
		}
	      जइ (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		प्रत्यागम error_mark_ग्रन्थिः;
	      भङ्ग;
	    }
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      अनुवर्त;
	    }
	  जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    भङ्ग;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  प्रत्यागम error_mark_ग्रन्थिः;
	}
      str += (वर्ण) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	भङ्ग;
      जइ (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	प्रत्यागम error_mark_ग्रन्थिः;
    }
  c_parser_consume_token (parser);
  str += '\0';
  वृक्षः res = build_string (str.length (), str.data ());
  वृक्षः_TYPE (res) = build_array_type_nelts (unsigned_char_type_ग्रन्थिः,
						  str.length ());
  प्रत्यागम res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

स्थिर तार्किक
c_parser_omp_clause_init_modifiers (c_parser *parser, तार्किक *target,
				    तार्किक *targetsync, वृक्षः *prefer_type_वृक्षः)
{
  *target = मिच्छ;
  *targetsync = मिच्छ;
  *prefer_type_वृक्षः = NULL_वृक्षः;

  करेहि
    {
      c_token *tok = c_parser_peek_token (parser);
      जइ (tok->type != CPP_NAME)
	गच्छ fail;
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (tok->मानम्);
      जइ (strcmp ("targetsync", p) == 0)
	{
	  जइ (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = सच्च;
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (strcmp ("target", p) == 0)
	{
	  जइ (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = सच्च;
	  c_parser_consume_token (parser);
	}
      अण्णहा जइ (strcmp ("prefer_type", p) == 0)
	{
	  जइ (*prefer_type_वृक्षः != NULL_वृक्षः)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_वृक्षः = c_parser_omp_modifier_prefer_type (parser);
	  जइ (*prefer_type_वृक्षः == error_mark_ग्रन्थिः)
	    प्रत्यागम मिच्छ;
	}
      अण्णहा
	गच्छ fail;
      tok = c_parser_peek_token (parser);
      जइ (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  अनुवर्त;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      प्रत्यागम सच्च;
    }
  जाव (सच्च);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  प्रत्यागम मिच्छ;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

स्थिर वृक्षः
c_parser_omp_clause_init (c_parser *parser, वृक्षः list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम list;

  तार्किक target = मिच्छ;
  तार्किक targetsync = मिच्छ;
  वृक्षः prefer_type_वृक्षः = NULL_वृक्षः;

  जइ (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_वृक्षः)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      जइ (prefer_type_वृक्षः != error_mark_ग्रन्थिः)
	parens.skip_until_found_close (parser);
      प्रत्यागम list;
    }

  जइ (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  वृक्षः nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					मिच्छ);
  parens.skip_until_found_close (parser);

  प्रति (वृक्षः c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      वृक्षः_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      जइ (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      जइ (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      जइ (prefer_type_वृक्षः)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_वृक्षः;
    }
  प्रत्यागम nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_use (c_parser *parser, वृक्षः list)
{
  प्रत्यागम c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

स्थिर वृक्षः
c_parser_omp_clause_interop (c_parser *parser, वृक्षः list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  वृक्षः nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  प्रति (वृक्षः c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      वृक्षः_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  प्रत्यागम nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

स्थिर वृक्षः
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   ध्रुव वर्ण *where, तार्किक finish_p = सच्च,
			   तार्किक target_p = मिच्छ)
{
  वृक्षः clauses = रिक्त;
  तार्किक first = सच्च;

  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ध्रुव वर्ण *c_name;
      वृक्षः prev = clauses;

      जइ (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      विकल्प (c_kind)
	{
	पक्ष PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, सच्च);
	  c_name = "default";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, मिच्छ);
	  c_name = "if";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_अङ्कः_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_अङ्कः_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_अङ्कः_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_अङ्कः_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     मिच्छ, clauses);
	  c_name = "reduction";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_SELF:
	  जइ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  अण्णहा
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  भङ्ग;
	पक्ष PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  भङ्ग;
	स्वभाव:
	  c_parser_error (parser, "expected an OpenACC clause");
	  गच्छ saw_error;
	}

      first = मिच्छ;

      जइ (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  जइ (finish_p)
    प्रत्यागम c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  प्रत्यागम clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

स्थिर वृक्षः
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  ध्रुव वर्ण *where, तार्किक finish_p = सच्च,
			  पूर्णाङ्क nested = 0)
{
  वृक्षः clauses = रिक्त;
  तार्किक first = सच्च;

  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      ध्रुव वर्ण *c_name;
      वृक्षः prev = clauses;

      जइ (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	भङ्ग;

      जइ (!first || nested != 2)
	{
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अण्णहा जइ (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      विकल्प (c_kind)
	{
	पक्ष PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, मिच्छ);
	  c_name = "default";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, सच्च);
	  c_name = "if";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     सच्च, clauses);
	  c_name = "in_reduction";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_अङ्कः_TASKS:
	  clauses = c_parser_omp_clause_अङ्कः_tasks (parser, clauses);
	  c_name = "num_tasks";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_अङ्कः_THREADS:
	  clauses = c_parser_omp_clause_अङ्कः_threads (parser, clauses);
	  c_name = "num_threads";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     सच्च, clauses);
	  c_name = "reduction";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     सच्च, clauses);
	  c_name = "task_reduction";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  जइ (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  जइ (!first)
	    गच्छ clause_not_first;
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  जइ (!first)
	    गच्छ clause_not_first;
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  जइ (!first)
	    गच्छ clause_not_first;
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_TO:
	  जइ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      वृक्षः nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      प्रति (वृक्षः c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  अण्णहा
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_अङ्कः_TEAMS:
	  clauses = c_parser_omp_clause_अङ्कः_teams (parser, clauses);
	  c_name = "num_teams";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, मिच्छ);
	  c_name = "map";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  भङ्ग;
	पक्ष PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  भङ्ग;
	स्वभाव:
	  c_parser_error (parser, "expected an OpenMP clause");
	  गच्छ saw_error;
	}

      first = मिच्छ;

      जइ (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  जइ (!nested)
    c_parser_skip_to_pragma_eol (parser);

  जइ (finish_p)
    {
      जइ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	प्रत्यागम c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      जइ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	प्रत्यागम c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      प्रत्यागम c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  प्रत्यागम clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

स्थिर वृक्षः
c_parser_omp_structured_block (c_parser *parser, तार्किक *if_p)
{
  वृक्षः stmt = प्रक्षिप_stmt_list ();
  parser->omp_attrs_forbidden_p = सच्च;
  c_parser_statement (parser, if_p);
  प्रत्यागम निष्कासय_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

स्थिर वृक्षः
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  वृक्षः stmt, clauses = NULL_वृक्षः;
  तार्किक readonly = मिच्छ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      जइ (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_POINTER (token->मानम्), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = सच्च;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_वृक्षः);
      parens.skip_until_found_close (parser);
    }

  जइ (readonly)
    प्रति (वृक्षः c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_ग्रन्थिः (OACC_CACHE);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);

  प्रत्यागम stmt;
}

/* OpenACC 2.0:
   # pragma acc data oacc-data-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OACC_DATA_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRESENT))

स्थिर वृक्षः
c_parser_oacc_data (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  प्रत्यागम stmt;
}

/* OpenACC 2.0:
   # pragma acc declare oacc-data-clause[optseq] new-line
*/

#define OACC_DECLARE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_LINK)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRESENT))

स्थिर शून्य
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  वृक्षः clauses, stmt, t, decl;

  तार्किक error = मिच्छ;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  जइ (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      प्रत्यागम;
    }

  प्रति (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      जइ (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = सच्च;
	  अनुवर्त;
	}

      विकल्प (OMP_CLAUSE_MAP_KIND (t))
	{
	पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	पक्ष GOMP_MAP_ALLOC:
	पक्ष GOMP_MAP_TO:
	पक्ष GOMP_MAP_FORCE_DEVICEPTR:
	पक्ष GOMP_MAP_DEVICE_RESIDENT:
	  भङ्ग;

	पक्ष GOMP_MAP_LINK:
	  जइ (!global_bindings_p ()
	      && (वृक्षः_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = सच्च;
	      अनुवर्त;
	    }
	  भङ्ग;

	स्वभाव:
	  जइ (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = सच्च;
	      अनुवर्त;
	    }
	  जइ (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = सच्च;
	      अनुवर्त;
	    }
	  अण्णहा जइ (वृक्षः_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = सच्च;
	      अनुवर्त;
	    }
	  भङ्ग;
	}

      जइ (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = सच्च;
	  अनुवर्त;
	}

      जइ (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = सच्च;
	  अनुवर्त;
	}

      जइ (!error)
	{
	  वृक्षः id;

	  जइ (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  अण्णहा
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = वृक्षः_cons (id, NULL_वृक्षः, DECL_ATTRIBUTES (decl));

	  जइ (global_bindings_p ())
	    {
	      symtab_ग्रन्थिः *ग्रन्थिः = symtab_ग्रन्थिः::get (decl);
	      जइ (ग्रन्थिः != रिक्त)
		{
		  ग्रन्थिः->offloadable = 1;
		  जइ (ENABLE_OFFLOADING)
		    {
		      g->have_offload = सच्च;
		      जइ (is_a <varpool_ग्रन्थिः *> (ग्रन्थिः))
			vec_safe_प्रक्षिप (offload_vars, decl);
		    }
		}
	    }
	}
    }

  जइ (error || global_bindings_p ())
    प्रत्यागम;

  stmt = make_ग्रन्थिः (OACC_DECLARE);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_व्यञ्जकम्_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  प्रत्यागम;
}

/* OpenACC 2.0:
   # pragma acc enter data oacc-enter-data-clause[optseq] new-line

   or

   # pragma acc exit data oacc-exit-data-clause[optseq] new-line


   LOC is the location of the #pragma token.
*/

#define OACC_ENTER_DATA_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#define OACC_EXIT_DATA_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DELETE) 		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DETACH) 		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_FINALIZE) 		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

स्थिर शून्य
c_parser_oacc_enter_exit_data (c_parser *parser, तार्किक enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः clauses, stmt;
  ध्रुव वर्ण *p = "";

  c_parser_consume_pragma (parser);

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      c_parser_consume_token (parser);
    }

  जइ (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = सच्च;
      c_parser_skip_to_pragma_eol (parser);
      प्रत्यागम;
    }

  जइ (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  अण्णहा
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  जइ (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_वृक्षः)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      प्रत्यागम;
    }

  stmt = enter ? make_ग्रन्थिः (OACC_ENTER_DATA) : make_ग्रन्थिः (OACC_EXIT_DATA);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);
}


/* OpenACC 2.0:
   # pragma acc host_data oacc-data-clause[optseq] new-line
     structured-block
*/

#define OACC_HOST_DATA_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_USE_DEVICE)          \
	 | (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)                  \
	 | (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT) )

स्थिर वृक्षः
c_parser_oacc_host_data (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", मिच्छ);
  जइ (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      प्रत्यागम error_mark_ग्रन्थिः;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  प्रत्यागम stmt;
}


/* OpenACC 2.0:

   # pragma acc loop oacc-loop-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OACC_LOOP_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COLLAPSE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRIVATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WORKER)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_VECTOR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_AUTO)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_INDEPENDENT) 	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_TILE) )
स्थिर वृक्षः
c_parser_oacc_loop (location_t loc, c_parser *parser, वर्ण *p_name,
		    omp_clause_mask mask, वृक्षः *cclauses, तार्किक *if_p)
{
  तार्किक is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  वृक्षः clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == रिक्त,
					    /*target=*/is_parallel);
  जइ (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      जइ (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      जइ (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  वृक्षः block = c_begin_compound_stmt (सच्च);
  वृक्षः stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, रिक्त,
				     if_p);
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम stmt;
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

#define OACC_KERNELS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अङ्कः_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अङ्कः_WORKERS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_VECTOR_LENGTH)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#define OACC_PARALLEL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRIVATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अङ्कः_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अङ्कः_WORKERS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_VECTOR_LENGTH)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#define OACC_SERIAL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRIVATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

स्थिर वृक्षः
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       गणना pragma_kind p_kind, वर्ण *p_name, तार्किक *if_p)
{
  omp_clause_mask mask;
  गणना वृक्षः_code code;
  विकल्प (p_kind)
    {
    पक्ष PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      भङ्ग;
    पक्ष PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      भङ्ग;
    पक्ष PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  वृक्षः block = c_begin_omp_parallel ();
	  वृक्षः clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  प्रत्यागम c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  वृक्षः clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/सच्च,
					    /*target=*/सच्च);

  वृक्षः block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  प्रत्यागम c_finish_omp_construct (loc, code, block, clauses);
}

/* OpenACC 2.0:
   # pragma acc routine oacc-routine-clause[optseq] new-line
     function-definition

   # pragma acc routine ( name ) oacc-routine-clause[optseq] new-line
*/

#define OACC_ROUTINE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WORKER)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_VECTOR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_NOHOST) )

/* Parse an OpenACC routine directive.  For named directives, we apply
   immediately to the named function.  For unnamed ones we then parse
   a declaration or definition, which must be for a function.  */

स्थिर शून्य
c_parser_oacc_routine (c_parser *parser, गणना pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_data data;
  data.error_seen = मिच्छ;
  data.fndecl_seen = मिच्छ;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      वृक्षः decl = NULL_वृक्षः;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      जइ (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->मानम्);
	  जइ (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->मानम्);
	  c_parser_consume_token (parser);
	}
      अण्णहा
	c_parser_error (parser, "expected function name");

      जइ (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  प्रत्यागम;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      जइ (वृक्षः_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  प्रत्यागम;
	}

      c_finish_oacc_routine (&data, decl, मिच्छ);
    }
  अण्णहा /* No optional '( name )'.  */
    {
      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      /* Emit a helpful diagnostic if there's another pragma following this
	 one.  Also don't allow a static assertion declaration, as in the
	 following we'll just parse a *single* "declaration or function
	 definition", and the static assertion counts an one.  */
      जइ (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  प्रत्यागम;
	}

      /* We only have to consider the pragma_external case here.  */
      जइ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णाङ्क ext = disable_extension_diagnostics ();
	  करेहि
	    c_parser_consume_token (parser);
	  जाव (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, मिच्छ, सच्च,
					 मिच्छ, रिक्त, रिक्त, मिच्छ, रिक्त, &data);
	  restore_extension_diagnostics (ext);
	}
      अण्णहा
	c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, मिच्छ, सच्च,
				       मिच्छ, रिक्त, रिक्त, मिच्छ, रिक्त, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

स्थिर शून्य
c_finish_oacc_routine (संरचना oacc_routine_data *data, वृक्षः fndecl,
		       तार्किक is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  जइ (data->error_seen
      || fndecl == error_mark_ग्रन्थिः)
    प्रत्यागम;

  जइ (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = सच्च;
      प्रत्यागम;
    }
  जइ (fndecl == NULL_वृक्षः || वृक्षः_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = सच्च;
      प्रत्यागम;
    }

  पूर्णाङ्क compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  जइ (compatible < 0)
    {
      data->error_seen = सच्च;
      प्रत्यागम;
    }
  जइ (compatible > 0)
    {
    }
  अण्णहा
    {
      जइ (वृक्षः_USED (fndecl) || (!is_defn && DECL_SAVED_वृक्षः (fndecl)))
	{
	  error_at (data->loc,
		    वृक्षः_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = सच्च;
	  प्रत्यागम;
	}

      /* Set the routine's level of parallelism.  */
      वृक्षः dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= वृक्षः_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = सच्च;
}

/* OpenACC 2.0:
   # pragma acc update oacc-update-clause[optseq] new-line
*/

#define OACC_UPDATE_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

स्थिर शून्य
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  वृक्षः clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  जइ (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_वृक्षः)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      प्रत्यागम;
    }

  जइ (parser->error)
    प्रत्यागम;

  वृक्षः stmt = make_ग्रन्थिः (OACC_UPDATE);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

स्थिर वृक्षः
c_parser_oacc_wait (location_t loc, c_parser *parser, वर्ण *p_name)
{
  वृक्षः clauses, list = NULL_वृक्षः, stmt = NULL_वृक्षः;

  जइ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  प्रत्यागम stmt;
}

संरचना c_omp_loc_वृक्षः
{
  location_t loc;
  वृक्षः var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
स्थिर वृक्षः
c_check_omp_allocate_allocator_r (वृक्षः *tp, पूर्णाङ्क *, शून्य *data)
{
  वृक्षः var = ((संरचना c_omp_loc_वृक्षः *) data)->var;
  location_t loc = ((संरचना c_omp_loc_वृक्षः *) data)->loc;
  जइ (वृक्षः_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      जइ (linemap_location_before_p (पङ्क्तिः_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  प्रत्यागम *tp;
	}
      अण्णहा
	{
	  gcc_assert (cur_stmt_list
		      && वृक्षः_CODE (cur_stmt_list) == STATEMENT_LIST);

	  वृक्षः_stmt_iterator l = tsi_last (cur_stmt_list);
	  जाव (!tsi_end_p (l))
	    {
	      जइ (linemap_location_before_p (पङ्क्तिः_table, व्यञ्जकम्_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  भङ्ग;
	      जइ (वृक्षः_CODE (*l) == MODIFY_व्यञ्जकम्
		  && वृक्षः_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (व्यञ्जकम्_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  प्रत्यागम *tp;
		}
	      --l;
	    }
	}
    }
  प्रत्यागम NULL_वृक्षः;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

स्थिर शून्य
c_parser_omp_allocate (c_parser *parser)
{
  वृक्षः alignment = NULL_वृक्षः;
  वृक्षः allocator = NULL_वृक्षः;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  वृक्षः nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_वृक्षः);
  करेहि
    {
      जइ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      जइ (!c_parser_next_token_is (parser, CPP_NAME))
	भङ्ग;
      matching_parens parens;
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      c_parser_consume_token (parser);
      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      जइ (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  भङ्ग;
	}
      जइ (!parens.require_open (parser))
	भङ्ग;

      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, मिच्छ, सच्च);
      व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
      जइ (व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
	;
      अण्णहा जइ (p[2] == 'i' && alignment)
	{
	  error_at (व्यञ्जकम्_loc, "too many %qs clauses", "align");
	  भङ्ग;
	}
      अण्णहा जइ (p[2] == 'i')
	{
	  alignment = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
	  जइ (वृक्षः_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (वृक्षः_TYPE (alignment))
	      || वृक्षः_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (व्यञ्जकम्_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_वृक्षः;
	    }
	}
      अण्णहा जइ (allocator)
	{
	  error_at (व्यञ्जकम्_loc, "too many %qs clauses", "allocator");
	  भङ्ग;
	}
      अण्णहा
	{
	  allocator = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
	  allocator_loc = व्यञ्जकम्_loc;
	  वृक्षः orig_type
	    = व्यञ्जकम्.original_type ? व्यञ्जकम्.original_type : वृक्षः_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (allocator))
	      || वृक्षः_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (व्यञ्जकम्_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			वृक्षः_TYPE (allocator));
	      allocator = NULL_वृक्षः;
	    }
	}
      parens.skip_until_found_close (parser);
    } जाव (सच्च);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  प्रति (वृक्षः c = nl; c != NULL_वृक्षः; c = OMP_CLAUSE_CHAIN (c))
    {
      वृक्षः var = OMP_CLAUSE_DECL (c);
      जइ (वृक्षः_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  अनुवर्त;
	}
      जइ (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  अनुवर्त;
	}
      जइ (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  अनुवर्त;
	}
      जइ (वृक्षः_STATIC (var))
	{
	  जइ (allocator == NULL_वृक्षः && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      अनुवर्त;
	    }
	  अण्णहा जइ (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  अण्णहा जइ (allocator
		   && (wi::eq_p (wi::to_widest (allocator),
				 GOMP_OMP_PREDEF_ALLOC_CGROUP)
		       || wi::eq_p (wi::to_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_PTEAM)
		       || wi::eq_p (wi::to_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_THREAD)))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause for static variable %qD must not "
			"be %<omp_cgroup_mem_alloc%>, %<omp_pteam_mem_alloc%>, "
			"or %<omp_thread_mem_alloc%>", var);
	    }
	}
      जइ (allocator)
	{
	  संरचना c_omp_loc_वृक्षः data
	    = {व्यञ्जकम्_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_वृक्षः (&allocator, c_check_omp_allocate_allocator_r, &data, रिक्त);
	}
      DECL_ATTRIBUTES (var) = वृक्षः_cons (get_identifier ("omp allocate"),
					 build_वृक्षः_list (allocator, alignment),
					 DECL_ATTRIBUTES (var));
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

स्थिर शून्य
c_parser_omp_atomic (location_t loc, c_parser *parser, तार्किक openacc)
{
  वृक्षः lhs = NULL_वृक्षः, rhs = NULL_वृक्षः, v = NULL_वृक्षः, r = NULL_वृक्षः;
  वृक्षः lhs1 = NULL_वृक्षः, rhs1 = NULL_वृक्षः;
  वृक्षः stmt, orig_lhs, unfolded_lhs = NULL_वृक्षः, unfolded_lhs1 = NULL_वृक्षः;
  गणना वृक्षः_code code = ERROR_MARK, opcode = NOP_व्यञ्जकम्;
  गणना omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  location_t eloc;
  तार्किक structured_block = मिच्छ;
  तार्किक swapped = मिच्छ;
  तार्किक non_lvalue_p;
  वृक्षः clauses = NULL_वृक्षः;
  तार्किक capture = मिच्छ;
  तार्किक compare = मिच्छ;
  तार्किक weak = मिच्छ;
  गणना omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  तार्किक no_semicolon = मिच्छ;
  तार्किक extra_scope = मिच्छ;

  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      जइ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      जइ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ध्रुव वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  गणना वृक्षः_code new_code = ERROR_MARK;
	  गणना omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  तार्किक new_capture = मिच्छ;
	  तार्किक new_compare = मिच्छ;
	  तार्किक new_weak = मिच्छ;
	  गणना omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  जइ (!strcmp (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  अण्णहा जइ (!strcmp (p, "write"))
	    new_code = NOP_व्यञ्जकम्;
	  अण्णहा जइ (!strcmp (p, "update"))
	    new_code = OMP_ATOMIC;
	  अण्णहा जइ (openacc && !strcmp (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  अण्णहा जइ (openacc)
	    {
	      p = रिक्त;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  अण्णहा जइ (!strcmp (p, "capture"))
	    new_capture = सच्च;
	  अण्णहा जइ (!strcmp (p, "compare"))
	    new_compare = सच्च;
	  अण्णहा जइ (!strcmp (p, "weak"))
	    new_weak = सच्च;
	  अण्णहा जइ (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      जइ (!parens.require_open (parser))
		अनुवर्त;

	      जइ (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ध्रुव वर्ण *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

		  जइ (!strcmp (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  अण्णहा जइ (!strcmp (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  अण्णहा जइ (!strcmp (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      जइ (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  जइ (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  अण्णहा
		    fail = new_fail;
		}
	      अण्णहा
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      अनुवर्त;
	    }
	  अण्णहा जइ (!strcmp (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  अण्णहा जइ (!strcmp (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  अण्णहा जइ (!strcmp (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  अण्णहा जइ (!strcmp (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  अण्णहा जइ (!strcmp (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  अण्णहा जइ (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      अनुवर्त;
	    }
	  अण्णहा
	    {
	      p = रिक्त;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  जइ (p)
	    {
	      जइ (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  जइ (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  अण्णहा जइ (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  अण्णहा
		    code = new_code;
		}
	      अण्णहा जइ (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  जइ (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  अण्णहा
		    memory_order = new_memory_order;
		}
	      अण्णहा जइ (new_capture)
		{
		  जइ (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  अण्णहा
		    capture = सच्च;
		}
	      अण्णहा जइ (new_compare)
		{
		  जइ (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  अण्णहा
		    compare = सच्च;
		}
	      अण्णहा जइ (new_weak)
		{
		  जइ (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  अण्णहा
		    weak = सच्च;
		}
	      c_parser_consume_token (parser);
	      अनुवर्त;
	    }
	}
      भङ्ग;
    }
  c_parser_skip_to_pragma_eol (parser);

  जइ (code == ERROR_MARK)
    code = OMP_ATOMIC;
  जइ (capture)
    {
      जइ (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      अण्णहा
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  जइ (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = मिच्छ;
    }
  जइ (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  जइ (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = मिच्छ;
    }
  जइ (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  अण्णहा जइ (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (गणना omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      विकल्प ((गणना omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	पक्ष OMP_MEMORY_ORDER_UNSPECIFIED:
	पक्ष OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  भङ्ग;
	पक्ष OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  भङ्ग;
	पक्ष OMP_MEMORY_ORDER_ACQUIRE:
	  जइ (code == NOP_व्यञ्जकम्)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  अण्णहा
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  भङ्ग;
	पक्ष OMP_MEMORY_ORDER_RELEASE:
	  जइ (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  अण्णहा
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  भङ्ग;
	पक्ष OMP_MEMORY_ORDER_ACQ_REL:
	  विकल्प (code)
	    {
	    पक्ष OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      भङ्ग;
	    पक्ष NOP_व्यञ्जकम्: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      भङ्ग;
	    स्वभाव:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      भङ्ग;
	    }
	  भङ्ग;
	स्वभाव:
	  gcc_unreachable ();
	}
    }
  अण्णहा
    विकल्प (code)
      {
      पक्ष OMP_ATOMIC_READ:
	जइ (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	अण्णहा जइ (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	भङ्ग;
      पक्ष NOP_व्यञ्जकम्: /* atomic write */
	जइ (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	अण्णहा जइ (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	भङ्ग;
      स्वभाव:
	भङ्ग;
      }
  जइ (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (गणना omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  विकल्प (code)
    {
    पक्ष OMP_ATOMIC_READ:
    पक्ष NOP_व्यञ्जकम्: /* atomic write */
      v = c_parser_cast_expression (parser, रिक्त).मानम्;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, मिच्छ, रिक्त, सच्च);
      जइ (v == error_mark_ग्रन्थिः)
	गच्छ saw_error;
      जइ (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      जइ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	गच्छ saw_error;
      जइ (code == NOP_व्यञ्जकम्)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  व्यञ्जकम् = c_parser_expression (parser);
	  व्यञ्जकम् = default_function_array_read_conversion (eloc, व्यञ्जकम्);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_वृक्षः;
	  rhs = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त);
	  जइ (rhs == error_mark_ग्रन्थिः)
	    गच्छ saw_error;
	}
      अण्णहा
	{
	  lhs = c_parser_cast_expression (parser, रिक्त).मानम्;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, मिच्छ, रिक्त, सच्च);
	  जइ (lhs == error_mark_ग्रन्थिः)
	    गच्छ saw_error;
	  जइ (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      गच्छ done;
    पक्ष OMP_ATOMIC_CAPTURE_NEW:
      जइ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = सच्च;
	}
      अण्णहा जइ (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	भङ्ग;
      अण्णहा
	{
	  v = c_parser_cast_expression (parser, रिक्त).मानम्;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, मिच्छ, रिक्त, सच्च);
	  जइ (v == error_mark_ग्रन्थिः)
	    गच्छ saw_error;
	  जइ (non_lvalue_p)
	    v = non_lvalue (v);
	  जइ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    गच्छ saw_error;
	  जइ (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      गच्छ saw_error;
	    }
	}
      भङ्ग;
    स्वभाव:
      भङ्ग;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  जइ (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      जइ (!parens.require_open (parser))
	गच्छ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् cmp_व्यञ्जकम्;
      जइ (r)
	{
	  cmp_व्यञ्जकम् = c_parser_cast_expression (parser, रिक्त);
	  cmp_व्यञ्जकम् = default_function_array_conversion (eloc, cmp_व्यञ्जकम्);
	}
      अण्णहा
	cmp_व्यञ्जकम् = c_parser_द्विमान_expression (parser, रिक्त, void_list_ग्रन्थिः);
      parens.skip_until_found_close (parser);
      जइ (cmp_व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
	गच्छ saw_error;
      जइ (r)
	{
	  जइ (!c_वृक्षः_equal (cmp_व्यञ्जकम्.मानम्, unfolded_lhs))
	    गच्छ bad_if;
	  cmp_व्यञ्जकम्.मानम् = rhs1;
	  rhs1 = NULL_वृक्षः;
	  gcc_assert (वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) == EQ_व्यञ्जकम्);
	}
      जइ (वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) == EQ_व्यञ्जकम्)
	;
      अण्णहा जइ (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (व्यञ्जकम्_LOC_OR_LOC (cmp_व्यञ्जकम्.मानम्, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  गच्छ saw_error;
	}
      अण्णहा जइ (वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) != GT_व्यञ्जकम्
	       && वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) != LT_व्यञ्जकम्)
	{
	  error_at (व्यञ्जकम्_LOC_OR_LOC (cmp_व्यञ्जकम्.मानम्, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  गच्छ saw_error;
	}
      जइ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	गच्छ saw_error;

      extra_scope = सच्च;
      eloc = c_parser_peek_token (parser)->location;
      व्यञ्जकम् = c_parser_cast_expression (parser, रिक्त);
      lhs = व्यञ्जकम्.मानम्;
      व्यञ्जकम् = default_function_array_conversion (eloc, व्यञ्जकम्);
      unfolded_lhs = व्यञ्जकम्.मानम्;
      lhs = c_fully_fold (lhs, मिच्छ, रिक्त, सच्च);
      orig_lhs = lhs;
      जइ (lhs == error_mark_ग्रन्थिः)
	गच्छ saw_error;
      जइ (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      जइ (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  गच्छ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      rhs1 = व्यञ्जकम्.मानम्;

      जइ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	गच्छ saw_error;

      जइ (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	गच्छ saw_error;

      extra_scope = मिच्छ;
      no_semicolon = सच्च;

      जइ (c_वृक्षः_equal (वृक्षः_OPERAND (cmp_व्यञ्जकम्.मानम्, 0), unfolded_lhs))
	{
	  जइ (वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) == EQ_व्यञ्जकम्)
	    {
	      opcode = COND_व्यञ्जकम्;
	      rhs = c_fully_fold (वृक्षः_OPERAND (cmp_व्यञ्जकम्.मानम्, 1),
				  मिच्छ, रिक्त, सच्च);
	      rhs1 = c_fully_fold (rhs1, मिच्छ, रिक्त, सच्च);
	    }
	  अण्णहा जइ (c_वृक्षः_equal (वृक्षः_OPERAND (cmp_व्यञ्जकम्.मानम्, 1), rhs1))
	    {
	      opcode = (वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) == GT_व्यञ्जकम्
			? MIN_व्यञ्जकम् : MAX_व्यञ्जकम्);
	      rhs = c_fully_fold (rhs1, मिच्छ, रिक्त, सच्च);
	      rhs1 = c_fully_fold (वृक्षः_OPERAND (cmp_व्यञ्जकम्.मानम्, 0),
				   मिच्छ, रिक्त, सच्च);
	    }
	  अण्णहा
	    गच्छ bad_if;
	}
      अण्णहा जइ (वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) == EQ_व्यञ्जकम्)
	गच्छ bad_if;
      अण्णहा जइ (c_वृक्षः_equal (वृक्षः_OPERAND (cmp_व्यञ्जकम्.मानम्, 1), unfolded_lhs)
	       && c_वृक्षः_equal (वृक्षः_OPERAND (cmp_व्यञ्जकम्.मानम्, 0), rhs1))
	{
	  opcode = (वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) == GT_व्यञ्जकम्
		    ? MAX_व्यञ्जकम् : MIN_व्यञ्जकम्);
	  rhs = c_fully_fold (rhs1, मिच्छ, रिक्त, सच्च);
	  rhs1 = c_fully_fold (वृक्षः_OPERAND (cmp_व्यञ्जकम्.मानम्, 1),
			       मिच्छ, रिक्त, सच्च);
	}
      अण्णहा
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  गच्छ saw_error;
	}

      जइ (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  जइ (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_वृक्षः)
	      || वृक्षः_CODE (cmp_व्यञ्जकम्.मानम्) != EQ_व्यञ्जकम्)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      गच्छ saw_error;
	    }

	  c_parser_consume_token (parser);

	  जइ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    गच्छ saw_error;

	  extra_scope = सच्च;
	  v = c_parser_cast_expression (parser, रिक्त).मानम्;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, मिच्छ, रिक्त, सच्च);
	  जइ (v == error_mark_ग्रन्थिः)
	    गच्छ saw_error;
	  जइ (non_lvalue_p)
	    v = non_lvalue (v);
	  जइ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    गच्छ saw_error;

	  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);

	  जइ (!c_वृक्षः_equal (व्यञ्जकम्.मानम्, unfolded_lhs))
	    गच्छ bad_if;

	  जइ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    गच्छ saw_error;

	  जइ (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    गच्छ saw_error;

	  extra_scope = मिच्छ;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  जइ (r == NULL_वृक्षः)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_ग्रन्थिः;
	}
      अण्णहा जइ (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  गच्छ saw_error;
	}
      अण्णहा जइ (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_वृक्षः
	       && v == NULL_वृक्षः)
	code = OMP_ATOMIC;
      गच्छ stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  व्यञ्जकम् = c_parser_cast_expression (parser, रिक्त);
  lhs = व्यञ्जकम्.मानम्;
  व्यञ्जकम् = default_function_array_conversion (eloc, व्यञ्जकम्);
  unfolded_lhs = व्यञ्जकम्.मानम्;
  lhs = c_fully_fold (lhs, मिच्छ, रिक्त, सच्च);
  orig_lhs = lhs;
  विकल्प (वृक्षः_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    पक्ष ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      जइ (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      जइ (structured_block)
	{
	  जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  अण्णहा जइ (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      प्रत्यागम;

    पक्ष POSTINCREMENT_व्यञ्जकम्:
      जइ (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    पक्ष PREINCREMENT_व्यञ्जकम्:
      lhs = वृक्षः_OPERAND (lhs, 0);
      unfolded_lhs = NULL_वृक्षः;
      opcode = PLUS_व्यञ्जकम्;
      rhs = integer_one_ग्रन्थिः;
      जइ (compare)
	गच्छ invalid_compare;
      भङ्ग;

    पक्ष POSTDECREMENT_व्यञ्जकम्:
      जइ (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    पक्ष PREDECREMENT_व्यञ्जकम्:
      lhs = वृक्षः_OPERAND (lhs, 0);
      unfolded_lhs = NULL_वृक्षः;
      opcode = MINUS_व्यञ्जकम्;
      rhs = integer_one_ग्रन्थिः;
      जइ (compare)
	गच्छ invalid_compare;
      भङ्ग;

    पक्ष COMPOUND_व्यञ्जकम्:
      जइ (वृक्षः_CODE (वृक्षः_OPERAND (lhs, 0)) == SAVE_व्यञ्जकम्
	  && वृक्षः_CODE (वृक्षः_OPERAND (lhs, 1)) == COMPOUND_व्यञ्जकम्
	  && वृक्षः_CODE (वृक्षः_OPERAND (वृक्षः_OPERAND (lhs, 1), 0)) == MODIFY_व्यञ्जकम्
	  && वृक्षः_OPERAND (वृक्षः_OPERAND (lhs, 1), 1) == वृक्षः_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (वृक्षः_TYPE (वृक्षः_OPERAND (वृक्षः_OPERAND
					      (वृक्षः_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = वृक्षः_OPERAND (वृक्षः_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    पक्ष MODIFY_व्यञ्जकम्:
      जइ (वृक्षः_CODE (lhs) == MODIFY_व्यञ्जकम्
	  && C_BOOLEAN_TYPE_P (वृक्षः_TYPE (वृक्षः_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  जइ (integer_onep (वृक्षः_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = वृक्षः_OPERAND (lhs, 1);
	      lhs = वृक्षः_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_वृक्षः;
	      opcode = NOP_व्यञ्जकम्;
	      जइ (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && वृक्षः_CODE (orig_lhs) == COMPOUND_व्यञ्जकम्)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      जइ (compare)
		गच्छ invalid_compare;
	      भङ्ग;
	    }
	  जइ (वृक्षः_CODE (वृक्षः_OPERAND (lhs, 1)) == TRUTH_NOT_व्यञ्जकम्
	      && वृक्षः_OPERAND (lhs, 0)
		 == वृक्षः_OPERAND (वृक्षः_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = वृक्षः_OPERAND (lhs, 1);
	      lhs = वृक्षः_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_वृक्षः;
	      opcode = NOP_व्यञ्जकम्;
	      जइ (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && वृक्षः_CODE (orig_lhs) == COMPOUND_व्यञ्जकम्)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      जइ (compare)
		गच्छ invalid_compare;
	      भङ्ग;
	    }
	}
      /* FALLTHRU */
    स्वभाव:
      जइ (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      जइ (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  गच्छ saw_error;
	}
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_MULT_EQ:
	  opcode = MULT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_DIV_EQ:
	  opcode = TRUNC_DIV_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_PLUS_EQ:
	  opcode = PLUS_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_MINUS_EQ:
	  opcode = MINUS_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_LSHIFT_EQ:
	  opcode = LSHIFT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_RSHIFT_EQ:
	  opcode = RSHIFT_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_AND_EQ:
	  opcode = BIT_AND_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_OR_EQ:
	  opcode = BIT_IOR_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_XOR_EQ:
	  opcode = BIT_XOR_व्यञ्जकम्;
	  भङ्ग;
	पक्ष CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त, unfolded_lhs);
	  rhs1 = व्यञ्जकम्.मानम्;
	  विकल्प (वृक्षः_CODE (rhs1))
	    {
	    पक्ष MULT_व्यञ्जकम्:
	    पक्ष TRUNC_DIV_व्यञ्जकम्:
	    पक्ष RDIV_व्यञ्जकम्:
	    पक्ष PLUS_व्यञ्जकम्:
	    पक्ष MINUS_व्यञ्जकम्:
	    पक्ष LSHIFT_व्यञ्जकम्:
	    पक्ष RSHIFT_व्यञ्जकम्:
	    पक्ष BIT_AND_व्यञ्जकम्:
	    पक्ष BIT_IOR_व्यञ्जकम्:
	    पक्ष BIT_XOR_व्यञ्जकम्:
	      जइ (compare)
		भङ्ग;
	      जइ (c_वृक्षः_equal (वृक्षः_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = वृक्षः_CODE (rhs1);
		  rhs = c_fully_fold (वृक्षः_OPERAND (rhs1, 1), मिच्छ, रिक्त,
				      सच्च);
		  rhs1 = c_fully_fold (वृक्षः_OPERAND (rhs1, 0), मिच्छ, रिक्त,
				       सच्च);
		  गच्छ stmt_done;
		}
	      जइ (c_वृक्षः_equal (वृक्षः_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = वृक्षः_CODE (rhs1);
		  rhs = c_fully_fold (वृक्षः_OPERAND (rhs1, 0), मिच्छ, रिक्त,
				      सच्च);
		  rhs1 = c_fully_fold (वृक्षः_OPERAND (rhs1, 1), मिच्छ, रिक्त,
				       सच्च);
		  swapped = !commutative_वृक्षः_code (opcode);
		  गच्छ stmt_done;
		}
	      भङ्ग;
	    पक्ष COND_व्यञ्जकम्:
	      जइ (!compare)
		भङ्ग;
	      जइ (वृक्षः_CODE (वृक्षः_OPERAND (rhs1, 0)) != GT_व्यञ्जकम्
		  && वृक्षः_CODE (वृक्षः_OPERAND (rhs1, 0)) != LT_व्यञ्जकम्
		  && वृक्षः_CODE (वृक्षः_OPERAND (rhs1, 0)) != EQ_व्यञ्जकम्)
		भङ्ग;
	      जइ (!वृक्षः_OPERAND (rhs1, 1))
		भङ्ग;
	      जइ (!c_वृक्षः_equal (वृक्षः_OPERAND (rhs1, 2), unfolded_lhs))
		भङ्ग;
	      जइ (c_वृक्षः_equal (वृक्षः_OPERAND (वृक्षः_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  जइ (वृक्षः_CODE (वृक्षः_OPERAND (rhs1, 0)) == EQ_व्यञ्जकम्)
		    {
		      opcode = COND_व्यञ्जकम्;
		      rhs = c_fully_fold (वृक्षः_OPERAND (वृक्षः_OPERAND (rhs1,
								      0), 1),
					  मिच्छ, रिक्त, सच्च);
		      rhs1 = c_fully_fold (वृक्षः_OPERAND (rhs1, 1), मिच्छ,
					   रिक्त, सच्च);
		      गच्छ stmt_done;
		    }
		  जइ (c_वृक्षः_equal (वृक्षः_OPERAND (वृक्षः_OPERAND (rhs1, 0), 1),
				    वृक्षः_OPERAND (rhs1, 1)))
		    {
		      opcode = (वृक्षः_CODE (वृक्षः_OPERAND (rhs1, 0)) == GT_व्यञ्जकम्
				? MIN_व्यञ्जकम् : MAX_व्यञ्जकम्);
		      rhs = c_fully_fold (वृक्षः_OPERAND (rhs1, 1), मिच्छ, रिक्त,
					  सच्च);
		      rhs1 = c_fully_fold (वृक्षः_OPERAND (वृक्षः_OPERAND (rhs1,
								       0), 0),
					   मिच्छ, रिक्त, सच्च);
		      गच्छ stmt_done;
		    }
		}
	      अण्णहा जइ (वृक्षः_CODE (वृक्षः_OPERAND (rhs1, 0)) == EQ_व्यञ्जकम्)
		भङ्ग;
	      अण्णहा जइ (c_वृक्षः_equal (वृक्षः_OPERAND (वृक्षः_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  जइ (c_वृक्षः_equal (वृक्षः_OPERAND (वृक्षः_OPERAND (rhs1, 0), 0),
				    वृक्षः_OPERAND (rhs1, 1)))
		    {
		      opcode = (वृक्षः_CODE (वृक्षः_OPERAND (rhs1, 0)) == GT_व्यञ्जकम्
				? MAX_व्यञ्जकम् : MIN_व्यञ्जकम्);
		      rhs = c_fully_fold (वृक्षः_OPERAND (rhs1, 1), मिच्छ, रिक्त,
					  सच्च);
		      rhs1 = c_fully_fold (वृक्षः_OPERAND (वृक्षः_OPERAND (rhs1,
								       0), 1),
					   मिच्छ, रिक्त, सच्च);
		      गच्छ stmt_done;
		    }
		}
	      भङ्ग;
	    पक्ष EQ_व्यञ्जकम्:
	      जइ (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		भङ्ग;
	      जइ (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_वृक्षः;
		  c_parser_consume_token (parser);
		  गच्छ restart;
		}
	      भङ्ग;
	    पक्ष ERROR_MARK:
	      गच्छ saw_error;
	    स्वभाव:
	      भङ्ग;
	    }
	  जइ (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      जइ (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_वृक्षः;
		  व्यञ्जकम् = default_function_array_read_conversion (eloc, व्यञ्जकम्);
		  unfolded_lhs1 = व्यञ्जकम्.मानम्;
		  lhs1 = c_fully_fold (unfolded_lhs1, मिच्छ, रिक्त, सच्च);
		  rhs1 = NULL_वृक्षः;
		  c_parser_consume_token (parser);
		  गच्छ restart;
		}
	      जइ (structured_block && !compare)
		{
		  opcode = NOP_व्यञ्जकम्;
		  व्यञ्जकम् = default_function_array_read_conversion (eloc, व्यञ्जकम्);
		  rhs = c_fully_fold (व्यञ्जकम्.मानम्, मिच्छ, रिक्त, सच्च);
		  rhs1 = NULL_वृक्षः;
		  गच्छ stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  गच्छ saw_error;
	स्वभाव:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  गच्छ saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      व्यञ्जकम् = c_parser_expression (parser);
      व्यञ्जकम् = default_function_array_read_conversion (eloc, व्यञ्जकम्);
      rhs = व्यञ्जकम्.मानम्;
      rhs = c_fully_fold (rhs, मिच्छ, रिक्त, सच्च);
      भङ्ग;
    }
stmt_done:
  जइ (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_वृक्षः)
    {
      जइ (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	गच्छ saw_error;
      no_semicolon = मिच्छ;
      v = c_parser_cast_expression (parser, रिक्त).मानम्;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, मिच्छ, रिक्त, सच्च);
      जइ (v == error_mark_ग्रन्थिः)
	गच्छ saw_error;
      जइ (non_lvalue_p)
	v = non_lvalue (v);
      जइ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	गच्छ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      व्यञ्जकम् = c_parser_cast_expression (parser, रिक्त);
      lhs1 = व्यञ्जकम्.मानम्;
      व्यञ्जकम् = default_function_array_read_conversion (eloc, व्यञ्जकम्);
      unfolded_lhs1 = व्यञ्जकम्.मानम्;
      lhs1 = c_fully_fold (lhs1, मिच्छ, रिक्त, सच्च);
      जइ (lhs1 == error_mark_ग्रन्थिः)
	गच्छ saw_error;
      जइ (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  जइ (structured_block)
    {
      जइ (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  जइ (weak && opcode != COND_व्यञ्जकम्)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = मिच्छ;
    }
  जइ (unfolded_lhs && unfolded_lhs1
      && !c_वृक्षः_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_ग्रन्थिः;
    }
  अण्णहा
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  जइ (stmt != error_mark_ग्रन्थिः)
    add_stmt (stmt);

  जइ (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

स्थिर शून्य
c_parser_omp_barrier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_barrier (loc);
}

/* OpenMP 2.5:
   # pragma omp critical [(name)] new-line
     structured-block

   OpenMP 4.5:
   # pragma omp critical [(name) [hint(expression)]] new-line

  LOC is the location of the #pragma itself.  */

#define OMP_CRITICAL_CLAUSE_MASK		\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_HINT) )

स्थिर वृक्षः
c_parser_omp_critical (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः stmt, name = NULL_वृक्षः, clauses = NULL_वृक्षः;

  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      जइ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->मानम्;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      अण्णहा
	c_parser_error (parser, "expected identifier");

      जइ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  प्रत्यागम c_finish_omp_critical (loc, stmt, name, clauses);
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
     in
     out
     inout
     mutexinout  */

स्थिर शून्य
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  जइ (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      प्रत्यागम;
    }

  वृक्षः depobj = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
  जइ (depobj != error_mark_ग्रन्थिः)
    {
      जइ (!lvalue_p (depobj))
	{
	  error_at (व्यञ्जकम्_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_ग्रन्थिः;
	}
      अण्णहा
	{
	  वृक्षः addr = build_unary_op (व्यञ्जकम्_LOC_OR_LOC (depobj, loc), ADDR_व्यञ्जकम्,
				      depobj, मिच्छ);
	  जइ (addr == error_mark_ग्रन्थिः)
	    depobj = error_mark_ग्रन्थिः;
	  अण्णहा
	    depobj = build_indirect_ref (व्यञ्जकम्_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  वृक्षः clause = NULL_वृक्षः;
  गणना omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  जइ (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      c_parser_consume_token (parser);
      जइ (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_वृक्षः, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  जइ (!clause)
	    clause = error_mark_ग्रन्थिः;
	}
      अण्णहा जइ (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      वृक्षः destobj = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
	      जइ (!lvalue_p (destobj))
		error_at (व्यञ्जकम्_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      अण्णहा जइ (depobj != error_mark_ग्रन्थिः
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (व्यञ्जकम्_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      अण्णहा जइ (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  जइ (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      जइ (c_parser_next_token_is (parser, CPP_NAME))
		{
		  ध्रुव वर्ण *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

		  c_parser_consume_token (parser);
		  जइ (!strcmp ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  अण्णहा जइ (!strcmp ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  अण्णहा जइ (!strcmp ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  अण्णहा जइ (!strcmp ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  अण्णहा जइ (!strcmp ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      जइ (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_ग्रन्थिः;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  अण्णहा
	    clause = error_mark_ग्रन्थिः;
	}
    }
  जइ (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_ग्रन्थिः;
      error_at (c_loc, "expected %<depend%>, %<destroy%> or %<update%> clause");
    }
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_depobj (loc, depobj, kind, clause);
}


/* OpenMP 2.5:
   # pragma omp flush flush-vars[opt] new-line

   flush-vars:
     ( variable-list )

   OpenMP 5.0:
   # pragma omp flush memory-order-clause new-line  */

स्थिर शून्य
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  गणना memmodel mo = MEMMODEL_LAST;
  जइ (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      जइ (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      अण्णहा जइ (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      अण्णहा जइ (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      अण्णहा जइ (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      अण्णहा
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      जइ (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, रिक्त);
    }
  अण्णहा जइ (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

स्थिर तार्किक
c_parser_omp_section_scan (c_parser *parser, ध्रुव वर्ण *directive,
			   तार्किक tentative)
{
  जइ (!c_parser_nth_token_starts_std_attributes (parser, 1))
    प्रत्यागम मिच्छ;
  unsigned पूर्णाङ्क n = 3;
  जइ (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    प्रत्यागम मिच्छ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  जइ (token->type != CPP_CLOSE_SQUARE)
    प्रत्यागम मिच्छ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  जइ (token->type != CPP_CLOSE_SQUARE)
    प्रत्यागम मिच्छ;
  जइ (n < 9)
    प्रत्यागम मिच्छ;
  जइ (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      वृक्षः first = c_parser_peek_nth_token_raw (parser, 3)->मानम्;
      वृक्षः second = c_parser_peek_nth_token_raw (parser, 5)->मानम्;
      जइ (strcmp (IDENTIFIER_POINTER (first), "directive")
	  && strcmp (IDENTIFIER_POINTER (first), "__directive__"))
	प्रत्यागम मिच्छ;
      जइ (strcmp (IDENTIFIER_POINTER (second), directive))
	प्रत्यागम मिच्छ;
    }
  जइ (tentative)
    प्रत्यागम सच्च;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t मध्यः_loc = UNKNOWN_LOCATION;
  वृक्षः std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  तार्किक seen = मिच्छ;
  पूर्णाङ्क cnt = 0;
  प्रति (वृक्षः attr = std_attrs; attr; attr = वृक्षः_CHAIN (attr))
    जइ (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	प्रति (वृक्षः a = वृक्षः_मानम् (attr); a; a = वृक्षः_CHAIN (a))
	  {
	    वृक्षः d = वृक्षः_मानम् (a);
	    gcc_assert (वृक्षः_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    जइ (first->type == CPP_NAME
		&& strcmp (IDENTIFIER_POINTER (first->मानम्),
			   directive) == 0)
	      {
		seen = सच्च;
		जइ (मध्यः_loc == UNKNOWN_LOCATION)
		  मध्यः_loc = first->location;
	      }
	  }
      }
  जइ (!seen)
    प्रत्यागम मिच्छ;
  जइ (cnt != 1 || वृक्षः_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, मध्यः_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      प्रत्यागम मिच्छ;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, रिक्त);
  प्रत्यागम सच्च;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

स्थिर वृक्षः
c_parser_omp_structured_block_sequence (c_parser *parser,
					गणना pragma_kind kind)
{
  वृक्षः stmt = प्रक्षिप_stmt_list ();
  c_parser_statement (parser, रिक्त);
  करेहि
    {
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	भङ्ग;
      जइ (c_parser_next_token_is (parser, CPP_EOF))
	भङ्ग;

      जइ (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	भङ्ग;

      जइ (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", मिच्छ))
	भङ्ग;

      c_parser_statement (parser, रिक्त);
    }
  जाव (1);
  प्रत्यागम निष्कासय_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

स्थिर शून्य
c_parser_omp_scan_loop_body (c_parser *parser, तार्किक open_brace_parsed)
{
  वृक्षः substmt;
  location_t loc;
  वृक्षः clauses = NULL_वृक्षः;
  तार्किक found_scan = मिच्छ;

  loc = c_parser_peek_token (parser)->location;
  जइ (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = मिच्छ;
      प्रत्यागम;
    }

  जइ (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  अण्णहा
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_ग्रन्थिः, substmt, NULL_वृक्षः);
  SET_व्यञ्जकम्_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  जइ (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      गणना omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = सच्च;

      c_parser_consume_pragma (parser);

      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      जइ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ध्रुव वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	  जइ (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  अण्णहा जइ (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      जइ (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_वृक्षः);
	}
      अण्णहा
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  अण्णहा
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  जइ (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  अण्णहा
    {
      जइ (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_ग्रन्थिः, substmt, clauses);
  SET_व्यञ्जकम्_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
स्थिर तार्किक
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    गणना वृक्षः_code code,
					    तार्किक error_p)
{
  जइ (code == OACC_LOOP)
    {
      जइ (c_parser_next_token_is_keyword (parser, RID_FOR))
	प्रत्यागम सच्च;
      जइ (error_p)
	c_parser_error (parser, "for statement expected");
    }
  अण्णहा
    {
      जइ (c_parser_next_token_is_keyword (parser, RID_FOR))
	प्रत्यागम सच्च;

      जइ (c_parser_next_token_is (parser, CPP_PRAGMA))
	विकल्प (c_parser_peek_token (parser)->pragma_kind)
	  {
	  पक्ष PRAGMA_OMP_UNROLL:
	  पक्ष PRAGMA_OMP_TILE:
	    प्रत्यागम सच्च;
	  स्वभाव:
	    भङ्ग;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      size_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      जइ (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->मानम्)
	  && C_RID_CODE (token->मानम्) == RID_FOR)
	प्रत्यागम सच्च;
      जइ (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  प्रत्यागम मिच्छ;
}

स्थिर वृक्षः c_parser_omp_tile (location_t, c_parser *, तार्किक *);
स्थिर वृक्षः c_parser_omp_unroll (location_t, c_parser *, तार्किक *);

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

स्थिर वृक्षः
c_parser_omp_loop_nest (c_parser *parser, तार्किक *if_p)
{
  वृक्षः decl = NULL_वृक्षः, cond = NULL_वृक्षः, incr = NULL_वृक्षः, init = NULL_वृक्षः;
  वृक्षः body = NULL_वृक्षः;
  matching_parens parens;
  तार्किक moreloops;
  unsigned वर्ण save_in_statement;
  वृक्षः loop_scope;
  location_t loc;
  संरचना omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  पूर्णाङ्क depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  जइ (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      वृक्षः std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, रिक्त);
      जइ (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  जइ (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      वृक्षः transform = NULL_वृक्षः, sizes, body = NULL_वृक्षः;
      पूर्णाङ्क गणनम् = 0;
      विकल्प (c_parser_peek_token (parser)->pragma_kind)
	{
	पक्ष PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = प्रक्षिप_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = निष्कासय_stmt_list (body);
	  जइ (transform == NULL_वृक्षः || transform == error_mark_ग्रन्थिः)
	    {
	      transform = error_mark_ग्रन्थिः;
	      भङ्ग;
	    }
	  gcc_assert (वृक्षः_CODE (transform) == OMP_UNROLL);
	  जइ (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      जइ (omp_for_parse_state->गणनम् - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->गणनम् - depth);
		  transform = error_mark_ग्रन्थिः;
		}
	      अण्णहा
		गणनम् = 1;
	    }
	  अण्णहा
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_ग्रन्थिः;
	    }
	  भङ्ग;
	पक्ष PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = प्रक्षिप_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = निष्कासय_stmt_list (body);
	  जइ (transform == NULL_वृक्षः || transform == error_mark_ग्रन्थिः)
	    {
	      transform = error_mark_ग्रन्थिः;
	      भङ्ग;
	    }
	  gcc_assert (वृक्षः_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  गणनम् = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  जइ (depth + गणनम् < omp_for_parse_state->गणनम्)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			गणनम्, omp_for_parse_state->गणनम् - depth);
	      transform = error_mark_ग्रन्थिः;
	    }
	  भङ्ग;
	स्वभाव:
	  c_parser_pragma (parser, pragma_stmt, रिक्त, void_list_ग्रन्थिः);
	  भङ्ग;
	}
      जइ (transform == NULL_वृक्षः)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      जइ (transform == NULL_वृक्षः || transform == error_mark_ग्रन्थिः)
	{
	  omp_for_parse_state->fail = सच्च;
	  प्रत्यागम NULL_वृक्षः;
	}
      प्रति (गणनम् = omp_for_parse_state->गणनम्; depth < गणनम्; ++depth)
	{
	  वृक्षः_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_वृक्षः;
	  वृक्षः_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_वृक्षः;
	  वृक्षः_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_वृक्षः;
	  वृक्षः_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_वृक्षः;
	}
      omp_for_parse_state->want_nested_loop = मिच्छ;
      प्रत्यागम body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = मिच्छ;

  जइ (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = सच्च;
      प्रत्यागम NULL_वृक्षः;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (सच्च);

  /* Parse the initialization declaration or expression.  */
  जइ (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      वृक्षः this_pre_body = प्रक्षिप_stmt_list ();
      c_in_omp_for = सच्च;
      c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, सच्च, सच्च,
				     मिच्छ);
      c_in_omp_for = मिच्छ;
      this_pre_body = निष्कासय_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      जइ (decl == रिक्त)
	गच्छ error_init;
      जइ (DECL_INITIAL (decl) == error_mark_ग्रन्थिः)
	decl = error_mark_ग्रन्थिः;
      init = decl;
    }
  अण्णहा जइ (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      संरचना c_व्यञ्जकम् decl_exp;
      संरचना c_व्यञ्जकम् init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.मानम्;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = सच्च;
      init = build_modify_व्यञ्जकम् (init_loc, decl, decl_exp.original_type,
				NOP_व्यञ्जकम्, init_loc, init_exp.मानम्,
				init_exp.original_type);
      c_in_omp_for = मिच्छ;
      init = c_process_व्यञ्जकम्_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  अण्णहा
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = सच्च;
      गच्छ parse_next;
    }

  /* Parse the loop condition.  */
  जइ (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = सच्च;
      संरचना c_व्यञ्जकम् cond_व्यञ्जकम्
	= c_parser_द्विमान_expression (parser, रिक्त, NULL_वृक्षः);
      c_in_omp_for = मिच्छ;

      cond = cond_व्यञ्जकम्.मानम्;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      विकल्प (cond_व्यञ्जकम्.original_code)
	{
	पक्ष GT_व्यञ्जकम्:
	पक्ष GE_व्यञ्जकम्:
	पक्ष LT_व्यञ्जकम्:
	पक्ष LE_व्यञ्जकम्:
	  भङ्ग;
	पक्ष NE_व्यञ्जकम्:
	  जइ (omp_for_parse_state->code != OACC_LOOP)
	    भङ्ग;
	  /* FALLTHRU.  */
	स्वभाव:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_व्यञ्जकम्, boolean_type_ग्रन्थिः, error_mark_ग्रन्थिः);
	  भङ्ग;
	}
      protected_set_व्यञ्जकम्_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  जइ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_व्यञ्जकम्_stmt (incr_loc,
				  c_parser_expression (parser).मानम्);
    }
  parens.skip_until_found_close (parser);

  जइ (decl == रिक्त || decl == error_mark_ग्रन्थिः || init == error_mark_ग्रन्थिः)
    omp_for_parse_state->fail = सच्च;
  अण्णहा
    {
      वृक्षः_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      वृक्षः_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      वृक्षः_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      वृक्षः_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->गणनम् - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  जइ (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     मिच्छ))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  अण्णहा जइ (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = सच्च;
      body = c_parser_compound_statement (parser, रिक्त);
      omp_for_parse_state->in_intervening_code = मिच्छ;
      जइ (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = सच्च;
	}
      if_p = रिक्त;
    }
  अण्णहा
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      जइ (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = सच्च;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = रिक्त;
      body = प्रक्षिप_stmt_list ();
      जइ (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, मिच्छ);
      अण्णहा
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = निष्कासय_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = मिच्छ;
  omp_for_parse_state->in_intervening_code = सच्च;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  जइ (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, सच्च);
  जइ (decl && वृक्षः_CODE (body) == BIND_व्यञ्जकम्)
    {
      वृक्षः t = BIND_व्यञ्जकम्_VARS (body);
      वृक्षः prev = NULL_वृक्षः, next = NULL_वृक्षः;
      जाव (t)
	{
	  next = DECL_CHAIN (t);
	  जइ (t == decl)
	    {
	      जइ (prev)
		DECL_CHAIN (prev) = next;
	      अण्णहा
		{
		  BIND_व्यञ्जकम्_VARS (body) = next;
		  BLOCK_VARS (BIND_व्यञ्जकम्_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      भङ्ग;
	    }
	  अण्णहा
	    {
	      prev = t;
	      t = next;
	    }
	}
      जइ (BIND_व्यञ्जकम्_VARS (body) == NULL_वृक्षः)
	body = BIND_व्यञ्जकम्_BODY (body);
    }

  प्रत्यागम body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

स्थिर वृक्षः
c_parser_omp_for_loop (location_t loc, c_parser *parser, गणना वृक्षः_code code,
		       वृक्षः clauses, वृक्षः *cclauses, तार्किक *if_p)
{
  वृक्षः body, stmt, cl;
  वृक्षः ret = NULL_वृक्षः;
  वृक्षः ordered_cl = NULL_वृक्षः;
  पूर्णाङ्क i, collapse = 1, ordered = 0, गणनम्;
  तार्किक oacc_tiling = मिच्छ;
  तार्किक inscan = मिच्छ;
  संरचना omp_for_parse_data data;
  संरचना omp_for_parse_data *save_data = parser->omp_for_parse_state;

  प्रति (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    जइ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = वृक्षः_to_shwi (OMP_CLAUSE_COLLAPSE_व्यञ्जकम् (cl));
    अण्णहा जइ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = सच्च;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    अण्णहा जइ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    अण्णहा जइ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_व्यञ्जकम् (cl))
      {
	ordered_cl = cl;
	ordered = वृक्षः_to_shwi (OMP_CLAUSE_ORDERED_व्यञ्जकम् (cl));
      }
    अण्णहा जइ (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = सच्च;

  जइ (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_व्यञ्जकम् (ordered_cl)
	= build_int_cst (integer_type_ग्रन्थिः, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  गणनम् = ordered ? ordered : collapse;

  जइ (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, सच्च))
    प्रत्यागम रिक्त;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_वृक्षः_vec (गणनम्);
  data.initv = make_वृक्षः_vec (गणनम्);
  data.condv = make_वृक्षः_vec (गणनम्);
  data.incrv = make_वृक्षः_vec (गणनम्);
  data.pre_body = NULL_वृक्षः;
  data.bindings = NULL_वृक्षः;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.गणनम् = गणनम्;
  data.depth = 0;
  data.want_nested_loop = सच्च;
  data.ordered = ordered > 0;
  data.in_intervening_code = मिच्छ;
  data.perfect_nesting_fail = मिच्छ;
  data.fail = मिच्छ;
  data.inscan = inscan;
  data.saw_intervening_code = मिच्छ;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  प्रति (वृक्षः t = data.bindings; t; )
    {
      वृक्षः n = वृक्षः_CHAIN (t);
      वृक्षः_CHAIN (t) = NULL_वृक्षः;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  जइ (!data.fail)
    {
      c_in_omp_for = सच्च;
      stmt = c_finish_omp_for (loc, code, data.declv, रिक्त, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, सच्च);
      c_in_omp_for = मिच्छ;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      जइ (stmt && !c_omp_check_loop_iv (stmt, data.declv, रिक्त))
	stmt = NULL_वृक्षः;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      जइ (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, रिक्त))
	stmt = NULL_वृक्षः;

      जइ (stmt)
	{
	  add_stmt (stmt);

	  प्रति (i = 0; i < वृक्षः_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      वृक्षः init = वृक्षः_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      जइ (init == NULL_वृक्षः)
		भङ्ग;
	      gcc_assert (वृक्षः_CODE (init) == MODIFY_व्यञ्जकम्);
	      वृक्षः decl = वृक्षः_OPERAND (init, 0);
	      वृक्षः cond = वृक्षः_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (वृक्षः_OPERAND (cond, 0) == decl);

	      वृक्षः op0 = वृक्षः_OPERAND (init, 1);
	      जइ (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || वृक्षः_CODE (op0) != वृक्षः_VEC)
		वृक्षः_OPERAND (init, 1) = c_fully_fold (op0, मिच्छ, रिक्त);
	      अण्णहा
		{
		  वृक्षः_VEC_ELT (op0, 1)
		    = c_fully_fold (वृक्षः_VEC_ELT (op0, 1), मिच्छ, रिक्त);
		  वृक्षः_VEC_ELT (op0, 2)
		    = c_fully_fold (वृक्षः_VEC_ELT (op0, 2), मिच्छ, रिक्त);
		}

	      वृक्षः op1 = वृक्षः_OPERAND (cond, 1);
	      जइ (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || वृक्षः_CODE (op1) != वृक्षः_VEC)
		वृक्षः_OPERAND (cond, 1) = c_fully_fold (op1, मिच्छ, रिक्त);
	      अण्णहा
		{
		  वृक्षः_VEC_ELT (op1, 1)
		    = c_fully_fold (वृक्षः_VEC_ELT (op1, 1), मिच्छ, रिक्त);
		  वृक्षः_VEC_ELT (op1, 2)
		    = c_fully_fold (वृक्षः_VEC_ELT (op1, 2), मिच्छ, रिक्त);
		}
	    }

	  जइ (cclauses != रिक्त
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != रिक्त)
	    {
	      वृक्षः *c;
	      प्रति (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		जइ (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		अण्णहा
		  {
		    प्रति (i = 0; i < गणनम्; i++)
		      जइ (वृक्षः_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			भङ्ग;
		    जइ (i == गणनम्)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    अण्णहा जइ (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    अण्णहा
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			वृक्षः l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			जइ (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			अण्णहा
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

  parser->omp_for_parse_state = save_data;
  प्रत्यागम ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

स्थिर शून्य
omp_split_clauses (location_t loc, गणना वृक्षः_code code,
		   omp_clause_mask mask, वृक्षः clauses, वृक्षः *cclauses)
{
  पूर्णाङ्क i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  प्रति (i = 0; i < C_OMP_CLAUSE_SPLIT_गणनम्; i++)
    जइ (cclauses[i])
      cclauses[i] = c_finish_omp_clauses (cclauses[i],
					  i == C_OMP_CLAUSE_SPLIT_TARGET
					  ? C_ORT_OMP_TARGET : C_ORT_OMP);
}

/* OpenMP 5.0:
   #pragma omp loop loop-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#define OMP_LOOP_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_BIND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDER))

स्थिर वृक्षः
c_parser_omp_loop (location_t loc, c_parser *parser,
		   वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
		   तार्किक *if_p)
{
  वृक्षः block, clauses, ret;

  strcat (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (सच्च);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम ret;
}

/* OpenMP 4.0:
   #pragma omp simd simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#define OMP_SIMD_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SAFELEN)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NONTEMPORAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDER))

स्थिर वृक्षः
c_parser_omp_simd (location_t loc, c_parser *parser,
		   वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
		   तार्किक *if_p)
{
  वृक्षः block, clauses, ret;

  strcat (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (सच्च);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम ret;
}

/* OpenMP 2.5:
   #pragma omp for for-clause[optseq] new-line
     for-loop

   OpenMP 4.0:
   #pragma omp for simd for-simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#define OMP_FOR_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SCHEDULE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDER))

स्थिर वृक्षः
c_parser_omp_for (location_t loc, c_parser *parser,
		  वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
		  तार्किक *if_p)
{
  वृक्षः block, clauses, ret;

  strcat (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  जइ (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  जइ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      जइ (strcmp (p, "simd") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  जइ (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (सच्च);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, सच्च);
	  जइ (ret == NULL_वृक्षः)
	    प्रत्यागम ret;
	  ret = make_ग्रन्थिः (OMP_FOR);
	  वृक्षः_TYPE (ret) = void_type_ग्रन्थिः;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_व्यञ्जकम्_LOCATION (ret, loc);
	  add_stmt (ret);
	  प्रत्यागम ret;
	}
    }
  जइ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम NULL_वृक्षः;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  जइ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (सच्च);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम ret;
}

स्थिर वृक्षः c_parser_omp_taskloop (location_t, c_parser *, वर्ण *,
				   omp_clause_mask, वृक्षः *, तार्किक *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

स्थिर वृक्षः
c_parser_omp_master (location_t loc, c_parser *parser,
		     वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
		     तार्किक *if_p, location_t master_loc)
{
  वृक्षः block, clauses, ret;
  gcc_rich_location richloc (loc);
  जइ (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      जइ (strcmp (p, "taskloop") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  जइ (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (सच्च);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, सच्च);
	  जइ (ret == NULL_वृक्षः)
	    प्रत्यागम ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  प्रत्यागम ret;
	}
    }
  जइ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम NULL_वृक्षः;
    }

  जइ (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, मिच्छ);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  अण्णहा
    c_parser_skip_to_pragma_eol (parser);

  प्रत्यागम c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

स्थिर वृक्षः
c_parser_omp_masked (location_t loc, c_parser *parser,
		     वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
		     तार्किक *if_p)
{
  वृक्षः block, clauses, ret;

  strcat (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      जइ (strcmp (p, "taskloop") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  जइ (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (सच्च);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, सच्च);
	  जइ (ret == NULL_वृक्षः)
	    प्रत्यागम ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  प्रत्यागम ret;
	}
    }
  जइ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम NULL_वृक्षः;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  प्रत्यागम c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
								  if_p),
			      clauses);
}

/* OpenMP 5.1:
   # pragma omp interop clauses[opt] new-line */

#define OMP_INTEROP_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DESTROY)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INIT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE))

स्थिर शून्य
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  वृक्षः clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  वृक्षः stmt = make_ग्रन्थिः (OMP_INTEROP);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);
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

#define OMP_ORDERED_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SIMD))

#define OMP_ORDERED_DEPEND_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DOACROSS))

स्थिर तार्किक
c_parser_omp_ordered (c_parser *parser, गणना pragma_context context,
		      तार्किक *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  जइ (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम मिच्छ;
    }

  पूर्णाङ्क n = 1;
  जइ (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  जइ (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ध्रुव वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->मानम्);

      जइ (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  जइ (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, मिच्छ);
	      प्रत्यागम मिच्छ;
	    }
	  जइ (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, मिच्छ);
	      प्रत्यागम सच्च;
	    }

	  वृक्षः clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_वृक्षः);
	  प्रत्यागम मिच्छ;
	}
    }

  वृक्षः clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  जइ (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_वृक्षः)
    प्रत्यागम मिच्छ;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  प्रत्यागम सच्च;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

स्थिर वृक्षः
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  वृक्षः stmt, substmt;
  तार्किक error_suppress = मिच्छ;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  जइ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = मिच्छ;
      प्रत्यागम NULL_वृक्षः;
    }

  stmt = प्रक्षिप_stmt_list ();

  जइ (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", सच्च))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ग्रन्थिः, substmt);
      SET_व्यञ्जकम्_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  जाव (1)
    {
      जइ (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	भङ्ग;
      जइ (c_parser_next_token_is (parser, CPP_EOF))
	भङ्ग;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", मिच्छ);
      जइ (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = मिच्छ;
	}
      अण्णहा जइ (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = सच्च;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ग्रन्थिः, substmt);
      SET_व्यञ्जकम्_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = निष्कासय_stmt_list (stmt);

  stmt = make_ग्रन्थिः (OMP_SECTIONS);
  SET_व्यञ्जकम्_LOCATION (stmt, sections_loc);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OMP_SECTIONS_BODY (stmt) = substmt;

  प्रत्यागम add_stmt (stmt);
}

/* OpenMP 2.5:
   # pragma omp sections sections-clause[optseq] newline
     sections-scope

   LOC is the location of the #pragma token.
*/

#define OMP_SECTIONS_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

स्थिर वृक्षः
c_parser_omp_sections (location_t loc, c_parser *parser,
		       वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses)
{
  वृक्षः block, clauses, ret;

  strcat (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  जइ (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (सच्च);
  ret = c_parser_omp_sections_scope (loc, parser);
  जइ (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम ret;
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

#define OMP_PARALLEL_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अङ्कः_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

स्थिर वृक्षः
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
		       तार्किक *if_p)
{
  वृक्षः stmt, clauses, block;

  strcat (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  जइ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  जइ (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
      जइ (cclauses == रिक्त)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      जइ (!flag_openmp)  /* flag_openmp_simd  */
	प्रत्यागम c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      वृक्षः ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      जइ (ret == NULL_वृक्षः)
	प्रत्यागम ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      प्रत्यागम stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  अण्णहा जइ (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      प्रत्यागम NULL_वृक्षः;
    }
  अण्णहा जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      location_t ploc = c_parser_peek_token (parser)->location;
      जइ (cclauses == रिक्त && strcmp (p, "masked") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  वृक्षः ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  जइ (ret == रिक्त)
	    प्रत्यागम ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  जइ (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  प्रत्यागम stmt;
	}
      अण्णहा जइ (cclauses == रिक्त && strcmp (p, "master") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  वृक्षः ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  जइ (ret == रिक्त)
	    प्रत्यागम ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  जइ (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  प्रत्यागम stmt;
	}
      अण्णहा जइ (strcmp (p, "loop") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  जइ (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  वृक्षः ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  जइ (ret == NULL_वृक्षः)
	    प्रत्यागम ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  प्रत्यागम stmt;
	}
      अण्णहा जइ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  प्रत्यागम NULL_वृक्षः;
	}
      अण्णहा जइ (cclauses == रिक्त && strcmp (p, "sections") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  प्रत्यागम stmt;
	}
    }
  अण्णहा जइ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम NULL_वृक्षः;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = सच्च;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  प्रत्यागम stmt;
}

/* OpenMP 2.5:
   # pragma omp single single-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#define OMP_SINGLE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

स्थिर वृक्षः
c_parser_omp_single (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः stmt = make_ग्रन्थिः (OMP_SINGLE);
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  प्रत्यागम add_stmt (stmt);
}

/* OpenMP 5.1:
   # pragma omp scope scope-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#define OMP_SCOPE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

स्थिर वृक्षः
c_parser_omp_scope (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः stmt = make_ग्रन्थिः (OMP_SCOPE);
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  प्रत्यागम add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
स्थिर वृक्षः
c_parser_omp_dispatch_body (c_parser *parser)
{
  संरचना c_व्यञ्जकम् lhs, rhs, ret;
  location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, रिक्त, रिक्त);
  जइ (वृक्षः_CODE (lhs.मानम्) == CALL_व्यञ्जकम्)
    प्रत्यागम lhs.मानम्;

  location_t op_location = c_parser_peek_token (parser)->location;
  जइ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    प्रत्यागम error_mark_ग्रन्थिः;

  /* Parse function name.  */
  जइ (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      प्रत्यागम error_mark_ग्रन्थिः;
    }
  व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
  वृक्षः id = c_parser_peek_token (parser)->मानम्;
  c_parser_consume_token (parser);
  जइ (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      प्रत्यागम error_mark_ग्रन्थिः;
    }

  rhs.मानम् = build_external_ref (व्यञ्जकम्_loc, id, सच्च, &rhs.original_type);
  set_c_व्यञ्जकम्_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, व्यञ्जकम्_LOC_OR_LOC (rhs.मानम्, व्यञ्जकम्_loc), rhs);
  जइ (वृक्षः_CODE (rhs.मानम्) != CALL_व्यञ्जकम्)
    {
      error_at (व्यञ्जकम्_LOC_OR_LOC (rhs.मानम्, व्यञ्जकम्_loc),
		"expected target-function call");
      प्रत्यागम error_mark_ग्रन्थिः;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, rhs, सच्च, सच्च);
  ret.मानम्
    = build_modify_व्यञ्जकम् (op_location, lhs.मानम्, lhs.original_type, NOP_व्यञ्जकम्,
			 व्यञ्जकम्_loc, rhs.मानम्, rhs.original_type);
  ret.m_decimal = 0;
  set_c_व्यञ्जकम्_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_व्यञ्जकम्;
  ret.original_type = रिक्त;
  प्रत्यागम ret.मानम्;
}

/* OpenMP 5.1:
   # pragma omp dispatch dispatch-clause[optseq] new-line
     expression-stmt

   LOC is the location of the #pragma.
*/

#define OMP_DISPATCH_CLAUSE_MASK                                               \
  ((OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)                             \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)                           \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOVARIANTS)                       \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOCONTEXT)                        \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR)                  \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INTEROP)                          \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)                    \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

स्थिर वृक्षः
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  वृक्षः stmt = make_ग्रन्थिः (OMP_DISPATCH);
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  वृक्षः depend_clauses = NULL_वृक्षः;
  वृक्षः *depend_clauses_ptr = &depend_clauses;
  प्रति (वृक्षः c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  जइ (depend_clauses != NULL_वृक्षः)
    {
      वृक्षः stmt = make_ग्रन्थिः (OMP_TASK);
      वृक्षः_TYPE (stmt) = void_ग्रन्थिः;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_वृक्षः;
      SET_व्यञ्जकम्_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  वृक्षः dispatch_body = c_parser_omp_dispatch_body (parser);
  जइ (dispatch_body == error_mark_ग्रन्थिः)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      प्रत्यागम NULL_वृक्षः;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (वृक्षः_CODE (dispatch_body) == CALL_व्यञ्जकम्
	      || वृक्षः_CODE (dispatch_body) == MODIFY_व्यञ्जकम्);
  वृक्षः *dispatch_call = वृक्षः_CODE (dispatch_body) == MODIFY_व्यञ्जकम्
			  ? &वृक्षः_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  जाव (वृक्षः_CODE (*dispatch_call) == FLOAT_व्यञ्जकम्
	 || वृक्षः_CODE (*dispatch_call) == CONVERT_व्यञ्जकम्
	 || वृक्षः_CODE (*dispatch_call) == NOP_व्यञ्जकम्)
    dispatch_call = &वृक्षः_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_व्यञ्जकम्_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    वृक्षः_TYPE (वृक्षः_TYPE (CALL_व्यञ्जकम्_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  प्रत्यागम add_stmt (stmt);
}

/* OpenMP 3.0:
   # pragma omp task task-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#define OMP_TASK_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIORITY)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DETACH)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_AFFINITY))

स्थिर वृक्षः
c_parser_omp_task (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = सच्च;
  c_parser_statement (parser, if_p);
  प्रत्यागम c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#define OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

स्थिर शून्य
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  वृक्षः clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  जइ (clauses)
    {
      वृक्षः stmt = make_ग्रन्थिः (OMP_TASK);
      वृक्षः_TYPE (stmt) = void_ग्रन्थिः;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_वृक्षः;
      SET_व्यञ्जकम्_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  अण्णहा
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

स्थिर शून्य
c_parser_omp_taskyield (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_taskyield (loc);
}

/* OpenMP 4.0:
   # pragma omp taskgroup new-line

   OpenMP 5.0:
   # pragma omp taskgroup taskgroup-clause[optseq] new-line
*/

#define OMP_TASKGROUP_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TASK_REDUCTION))

स्थिर वृक्षः
c_parser_omp_taskgroup (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  वृक्षः body = c_parser_omp_structured_block (parser, if_p);
  प्रत्यागम c_finish_omp_taskgroup (loc, body, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancel cancel-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#define OMP_CANCEL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TASKGROUP)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF))

स्थिर शून्य
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  वृक्षः clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
					   "#pragma omp cancel");

  c_finish_omp_cancel (loc, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancellation point cancelpt-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#define OMP_CANCELLATION_POINT_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TASKGROUP))

स्थिर तार्किक
c_parser_omp_cancellation_point (c_parser *parser, गणना pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः clauses;
  तार्किक point_seen = मिच्छ;

  c_parser_consume_pragma (parser);
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = सच्च;
	}
    }
  जइ (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      प्रत्यागम मिच्छ;
    }

  जइ (context != pragma_compound)
    {
      जइ (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      अण्णहा
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम सच्च;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  प्रत्यागम सच्च;
}

/* OpenMP 4.0:
   #pragma omp distribute distribute-clause[optseq] new-line
     for-loop  */

#define OMP_DISTRIBUTE_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDER))

स्थिर वृक्षः
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
			 तार्किक *if_p)
{
  वृक्षः clauses, block, ret;

  strcat (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      तार्किक simd = मिच्छ;
      तार्किक parallel = मिच्छ;

      जइ (strcmp (p, "simd") == 0)
	simd = सच्च;
      अण्णहा
	parallel = strcmp (p, "parallel") == 0;
      जइ (parallel || simd)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  जइ (cclauses == रिक्त)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      जइ (simd)
		प्रत्यागम c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      अण्णहा
		प्रत्यागम c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (सच्च);
	  जइ (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  अण्णहा
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, सच्च);
	  जइ (ret == रिक्त)
	    प्रत्यागम ret;
	  ret = make_ग्रन्थिः (OMP_DISTRIBUTE);
	  वृक्षः_TYPE (ret) = void_type_ग्रन्थिः;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_व्यञ्जकम्_LOCATION (ret, loc);
	  add_stmt (ret);
	  प्रत्यागम ret;
	}
    }
  जइ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम NULL_वृक्षः;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (सच्च);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, रिक्त,
			       if_p);
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अङ्कः_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

स्थिर वृक्षः
c_parser_omp_teams (location_t loc, c_parser *parser,
		    वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
		    तार्किक *if_p)
{
  वृक्षः clauses, block, ret;

  strcat (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "distribute") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  जइ (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, सच्च);
	  जइ (ret == रिक्त)
	    प्रत्यागम ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_ग्रन्थिः (OMP_TEAMS);
	  वृक्षः_TYPE (ret) = void_type_ग्रन्थिः;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_व्यञ्जकम्_LOCATION (ret, loc);
	  प्रत्यागम add_stmt (ret);
	}
      अण्णहा जइ (strcmp (p, "loop") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  जइ (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, सच्च);
	  जइ (ret == रिक्त)
	    प्रत्यागम ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_ग्रन्थिः (OMP_TEAMS);
	  वृक्षः_TYPE (ret) = void_type_ग्रन्थिः;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_व्यञ्जकम्_LOCATION (ret, loc);
	  प्रत्यागम add_stmt (ret);
	}
    }
  जइ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम NULL_वृक्षः;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  वृक्षः stmt = make_ग्रन्थिः (OMP_TEAMS);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, सच्च);
  SET_व्यञ्जकम्_LOCATION (stmt, loc);

  प्रत्यागम add_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target data target-data-clause[optseq] new-line
     structured-block  */

#define OMP_TARGET_DATA_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR) \
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR))

स्थिर वृक्षः
c_parser_omp_target_data (location_t loc, c_parser *parser, तार्किक *if_p)
{
  जइ (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  वृक्षः clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", मिच्छ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, मिच्छ);
  पूर्णाङ्क map_seen = 0;
  प्रति (वृक्षः *pc = &clauses; *pc;)
    {
      जइ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	विकल्प (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  पक्ष GOMP_MAP_TO:
	  पक्ष GOMP_MAP_ALWAYS_TO:
	  पक्ष GOMP_MAP_PRESENT_TO:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TO:
	  पक्ष GOMP_MAP_FROM:
	  पक्ष GOMP_MAP_ALWAYS_FROM:
	  पक्ष GOMP_MAP_PRESENT_FROM:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_FROM:
	  पक्ष GOMP_MAP_TOFROM:
	  पक्ष GOMP_MAP_ALWAYS_TOFROM:
	  पक्ष GOMP_MAP_PRESENT_TOFROM:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  पक्ष GOMP_MAP_ALLOC:
	  पक्ष GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	  पक्ष GOMP_MAP_ALWAYS_POINTER:
	  पक्ष GOMP_MAP_ATTACH_DETACH:
	  पक्ष GOMP_MAP_ATTACH:
	    भङ्ग;
	  स्वभाव:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    अनुवर्त;
	  }
      अण्णहा जइ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  जइ (map_seen != 3)
    {
      जइ (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      प्रत्यागम NULL_वृक्षः;
    }

  वृक्षः stmt = make_ग्रन्थिः (OMP_TARGET_DATA);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  वृक्षः block = c_begin_compound_stmt (सच्च);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, सच्च);

  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  प्रत्यागम add_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target update target-update-clause[optseq] new-line */

#define OMP_TARGET_UPDATE_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FROM)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TO)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

स्थिर तार्किक
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    गणना pragma_context context)
{
  जइ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम सच्च;
    }

  वृक्षः clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ मिच्छ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  जइ (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_वृक्षः
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_वृक्षः)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      प्रत्यागम मिच्छ;
    }

  जइ (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  वृक्षः stmt = make_ग्रन्थिः (OMP_TARGET_UPDATE);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);
  प्रत्यागम मिच्छ;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#define OMP_TARGET_ENTER_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

स्थिर तार्किक
c_parser_omp_target_enter_data (location_t loc, c_parser *parser,
				गणना pragma_context context)
{
  तार्किक data_seen = मिच्छ;
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = सच्च;
	}
    }
  जइ (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      प्रत्यागम मिच्छ;
    }

  जइ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम सच्च;
    }

  जइ (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  वृक्षः clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", मिच्छ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, मिच्छ);
  पूर्णाङ्क map_seen = 0;
  प्रति (वृक्षः *pc = &clauses; *pc;)
    {
      जइ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	विकल्प (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  पक्ष GOMP_MAP_TO:
	  पक्ष GOMP_MAP_ALWAYS_TO:
	  पक्ष GOMP_MAP_PRESENT_TO:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TO:
	  पक्ष GOMP_MAP_ALLOC:
	  पक्ष GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	  पक्ष GOMP_MAP_ALWAYS_POINTER:
	  पक्ष GOMP_MAP_ATTACH_DETACH:
	  पक्ष GOMP_MAP_ATTACH:
	    भङ्ग;
	  स्वभाव:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    अनुवर्त;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  जइ (map_seen != 3)
    {
      जइ (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      प्रत्यागम सच्च;
    }

  वृक्षः stmt = make_ग्रन्थिः (OMP_TARGET_ENTER_DATA);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);
  प्रत्यागम सच्च;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#define OMP_TARGET_EXIT_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

स्थिर तार्किक
c_parser_omp_target_exit_data (location_t loc, c_parser *parser,
			       गणना pragma_context context)
{
  तार्किक data_seen = मिच्छ;
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = सच्च;
	}
    }
  जइ (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      प्रत्यागम मिच्छ;
    }

  जइ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम सच्च;
    }

  जइ (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  वृक्षः clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", मिच्छ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, मिच्छ);
  पूर्णाङ्क map_seen = 0;
  प्रति (वृक्षः *pc = &clauses; *pc;)
    {
      जइ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	विकल्प (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  पक्ष GOMP_MAP_FROM:
	  पक्ष GOMP_MAP_ALWAYS_FROM:
	  पक्ष GOMP_MAP_PRESENT_FROM:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_FROM:
	  पक्ष GOMP_MAP_RELEASE:
	  पक्ष GOMP_MAP_DELETE:
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    भङ्ग;
	  पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	  पक्ष GOMP_MAP_ALWAYS_POINTER:
	  पक्ष GOMP_MAP_ATTACH_DETACH:
	  पक्ष GOMP_MAP_DETACH:
	    भङ्ग;
	  स्वभाव:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    अनुवर्त;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  जइ (map_seen != 3)
    {
      जइ (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      प्रत्यागम सच्च;
    }

  वृक्षः stmt = make_ग्रन्थिः (OMP_TARGET_EXIT_DATA);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);
  प्रत्यागम सच्च;
}

/* OpenMP 4.0:
   # pragma omp target target-clause[optseq] new-line
     structured-block  */

#define OMP_TARGET_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULTMAP)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE) \
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR) \
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USES_ALLOCATORS))

स्थिर तार्किक
c_parser_omp_target (c_parser *parser, गणना pragma_context context, तार्किक *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  वृक्षः *pc = रिक्त, stmt, block, body, clauses;

  जइ (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      प्रत्यागम मिच्छ;
    }

  जइ (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      गणना वृक्षः_code ccode = ERROR_MARK;

      जइ (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      अण्णहा जइ (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      अण्णहा जइ (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      जइ (ccode != ERROR_MARK)
	{
	  वृक्षः cclauses[C_OMP_CLAUSE_SPLIT_गणनम्];
	  वर्ण p_name[परिमाण ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      वृक्षः stmt;
	      विकल्प (ccode)
		{
		पक्ष OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  भङ्ग;
		पक्ष OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  भङ्ग;
		पक्ष OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  भङ्ग;
		स्वभाव:
		  gcc_unreachable ();
		}
	      प्रत्यागम stmt != NULL_वृक्षः;
	    }
	  keep_next_level ();
	  वृक्षः block = c_begin_compound_stmt (सच्च), ret;
	  विकल्प (ccode)
	    {
	    पक्ष OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      भङ्ग;
	    पक्ष OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      भङ्ग;
	    पक्ष OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, सच्च);
	  जइ (ret == NULL_वृक्षः)
	    प्रत्यागम मिच्छ;
	  जइ (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    प्रति (वृक्षः c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_अङ्कः_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		प्रति (पूर्णाङ्क i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_अङ्कः_TEAMS); ++i)
		  जइ (OMP_CLAUSE_OPERAND (c, i)
		      && वृक्षः_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      वृक्षः व्यञ्जकम् = OMP_CLAUSE_OPERAND (c, i);
		      वृक्षः tmp = create_tmp_var_raw (वृक्षः_TYPE (व्यञ्जकम्));
		      व्यञ्जकम् = build4 (TARGET_व्यञ्जकम्, वृक्षः_TYPE (व्यञ्जकम्), tmp,
				     व्यञ्जकम्, NULL_वृक्षः, NULL_वृक्षः);
		      add_stmt (व्यञ्जकम्);
		      OMP_CLAUSE_OPERAND (c, i) = व्यञ्जकम्;
		      वृक्षः tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  वृक्षः stmt = make_ग्रन्थिः (OMP_TARGET);
	  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), सच्च);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_व्यञ्जकम्_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  गच्छ check_clauses;
	}
      अण्णहा जइ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  प्रत्यागम मिच्छ;
	}
      अण्णहा जइ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  प्रत्यागम सच्च;
	}
      अण्णहा जइ (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  प्रत्यागम c_parser_omp_target_enter_data (loc, parser, context);
	}
      अण्णहा जइ (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  प्रत्यागम c_parser_omp_target_exit_data (loc, parser, context);
	}
      अण्णहा जइ (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  प्रत्यागम c_parser_omp_target_update (loc, parser, context);
	}
    }
  जइ (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम मिच्छ;
    }

  stmt = make_ग्रन्थिः (OMP_TARGET);
  वृक्षः_TYPE (stmt) = void_type_ग्रन्थिः;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", मिच्छ);
  प्रति (वृक्षः c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	वृक्षः nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, सच्च);

  keep_next_level ();
  block = c_begin_compound_stmt (सच्च);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, सच्च);

  SET_व्यञ्जकम्_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  जाव (*pc)
    {
      जइ (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	विकल्प (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  पक्ष GOMP_MAP_TO:
	  पक्ष GOMP_MAP_ALWAYS_TO:
	  पक्ष GOMP_MAP_PRESENT_TO:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TO:
	  पक्ष GOMP_MAP_FROM:
	  पक्ष GOMP_MAP_ALWAYS_FROM:
	  पक्ष GOMP_MAP_PRESENT_FROM:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_FROM:
	  पक्ष GOMP_MAP_TOFROM:
	  पक्ष GOMP_MAP_ALWAYS_TOFROM:
	  पक्ष GOMP_MAP_PRESENT_TOFROM:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  पक्ष GOMP_MAP_ALLOC:
	  पक्ष GOMP_MAP_PRESENT_ALLOC:
	  पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	  पक्ष GOMP_MAP_ALWAYS_POINTER:
	  पक्ष GOMP_MAP_POINTER:
	  पक्ष GOMP_MAP_ATTACH_DETACH:
	  पक्ष GOMP_MAP_ATTACH:
	    भङ्ग;
	  स्वभाव:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    अनुवर्त;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = सच्च;
  प्रत्यागम सच्च;
}

/* OpenMP 4.0:
   # pragma omp declare simd declare-simd-clauses[optseq] new-line

   OpenMP 5.0:
   # pragma omp declare variant (identifier) match(context-selector) new-line

   OpenMP 5.1
   # pragma omp declare variant (identifier) match(context-selector) \
      adjust_args(adjust-op:argument-list) append_args(interop-list) new-line
   */

#define OMP_DECLARE_SIMD_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INBRANCH)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOTINBRANCH))

स्थिर शून्य
c_parser_omp_declare_simd (c_parser *parser, गणना pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  वृक्षः kind = token->मानम्;
  gcc_assert (strcmp (IDENTIFIER_POINTER (kind), "simd") == 0
	      || strcmp (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      जइ (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  प्रत्यागम;
	}
      clauses.safe_प्रक्षिप (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_प्रक्षिप (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  जाव (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      जइ (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->मानम् != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  प्रत्यागम;
	}
      c_parser_consume_pragma (parser);
      जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  जइ (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      प्रत्यागम;
	    }
	  clauses.safe_प्रक्षिप (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_प्रक्षिप (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, परिमाण (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_प्रक्षिप (eof_token);
  clauses.safe_प्रक्षिप (eof_token);

  विकल्प (context)
    {
    पक्ष pragma_external:
      जइ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णाङ्क ext = disable_extension_diagnostics ();
	  करेहि
	    c_parser_consume_token (parser);
	  जाव (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, मिच्छ, सच्च,
					 मिच्छ, रिक्त, &clauses);
	  restore_extension_diagnostics (ext);
	}
      अण्णहा
	c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, मिच्छ, सच्च,
				       मिच्छ, रिक्त, &clauses);
      भङ्ग;
    पक्ष pragma_struct:
    पक्ष pragma_param:
    पक्ष pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      भङ्ग;
    पक्ष pragma_compound:
      तार्किक have_std_attrs;
      वृक्षः std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      जइ (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      अण्णहा
	std_attrs = NULL_वृक्षः;
      जइ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णाङ्क ext = disable_extension_diagnostics ();
	  करेहि
	    c_parser_consume_token (parser);
	  जाव (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  जइ (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, सच्च,
					     सच्च, मिच्छ, रिक्त, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      भङ्ग;
	    }
	  restore_extension_diagnostics (ext);
	}
      अण्णहा जइ (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, सच्च, सच्च, सच्च, सच्च, सच्च,
					 मिच्छ, रिक्त, &clauses, have_std_attrs,
					 std_attrs);
	  भङ्ग;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      भङ्ग;
    स्वभाव:
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

स्थिर वृक्षः
c_parser_omp_context_selector (c_parser *parser, गणना omp_tss_code set,
			       वृक्षः parms)
{
  वृक्षः ret = NULL_वृक्षः;
  करेहि
    {
      वृक्षः selector;
      जइ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->मानम्;
      अण्णहा
	{
	  c_parser_error (parser, "expected trait selector name");
	  प्रत्यागम error_mark_ग्रन्थिः;
	}
      गणना omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      जइ (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_वृक्षः, NULL_वृक्षः, ret);
	  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      अनुवर्त;
	    }
	  अण्णहा
	    भङ्ग;
	}

      c_parser_consume_token (parser);

      वृक्षः properties = NULL_वृक्षः;
      वृक्षः scoreval = NULL_वृक्षः;
      गणना omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      तार्किक allow_score = omp_ts_map[sel].allow_score;
      वृक्षः t;

      जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  जइ (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      प्रत्यागम error_mark_ग्रन्थिः;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER (token->मानम्), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      वृक्षः score = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त).मानम्;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      जइ (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      अण्णहा जइ (score != error_mark_ग्रन्थिः)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, मिच्छ, रिक्त);
		  जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (score))
		      || वृक्षः_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  अण्णहा जइ (वृक्षः_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  अण्णहा
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  विकल्प (property_kind)
	    {
	    पक्ष OMP_TRAIT_PROPERTY_ID:
	      जइ (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  वृक्षः prop = c_parser_peek_token (parser)->मानम्;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_वृक्षः,
						    properties);
		}
	      अण्णहा
		{
		  c_parser_error (parser, "expected identifier");
		  प्रत्यागम error_mark_ग्रन्थिः;
		}
	      भङ्ग;
	    पक्ष OMP_TRAIT_PROPERTY_NAME_LIST:
	      करेहि
		{
		  वृक्षः prop = OMP_TP_NAMELIST_ग्रन्थिः;
		  वृक्षः मानम् = NULL_वृक्षः;
		  जइ (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      मानम् = c_parser_peek_token (parser)->मानम्;
		      c_parser_consume_token (parser);
		    }
		  अण्णहा जइ (c_parser_next_token_is (parser, CPP_STRING))
		    मानम् = c_parser_string_literal (parser, मिच्छ,
						     मिच्छ).मानम्;
		  अण्णहा
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      प्रत्यागम error_mark_ग्रन्थिः;
		    }

		  properties = make_trait_property (prop, मानम्, properties);

		  जइ (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  अण्णहा
		    भङ्ग;
		}
	      जाव (1);
	      भङ्ग;
	    पक्ष OMP_TRAIT_PROPERTY_DEV_अङ्कः_व्यञ्जकम्:
	    पक्ष OMP_TRAIT_PROPERTY_BOOL_व्यञ्जकम्:
	      {
		c_व्यञ्जकम् texpr = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  सच्च, सच्च);
		t = texpr.मानम्;
	      }
	      जइ (t == error_mark_ग्रन्थिः)
		प्रत्यागम error_mark_ग्रन्थिः;
	      mark_exp_read (t);
	      जइ (property_kind == OMP_TRAIT_PROPERTY_BOOL_व्यञ्जकम्)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_ग्रन्थिः);
		  जइ (t == error_mark_ग्रन्थिः)
		    प्रत्यागम error_mark_ग्रन्थिः;
		}
	      अण्णहा जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  प्रत्यागम error_mark_ग्रन्थिः;
		}
	      t = c_fully_fold (t, मिच्छ, रिक्त);
	      properties = make_trait_property (NULL_वृक्षः, t, properties);
	      भङ्ग;
	    पक्ष OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      जइ (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  जइ (parms == NULL_वृक्षः)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      प्रत्यागम error_mark_ग्रन्थिः;
		    }
		  वृक्षः c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", सच्च, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_ग्रन्थिः
							     ? NULL_वृक्षः : parms,
							     c);
		  properties = c;
		}
	      अण्णहा जइ (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  प्रत्यागम error_mark_ग्रन्थिः;
		}
	      अण्णहा
		gcc_unreachable ();
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      अण्णहा जइ (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  प्रत्यागम error_mark_ग्रन्थिः;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }
  जाव (1);

  प्रत्यागम nreverse (ret);
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

स्थिर वृक्षः
c_parser_omp_context_selector_specification (c_parser *parser, वृक्षः parms)
{
  वृक्षः ret = NULL_वृक्षः;
  करेहि
    {
      ध्रुव वर्ण *setp = "";
      जइ (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      गणना omp_tss_code set = omp_lookup_tss_code (setp);

      जइ (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  प्रत्यागम error_mark_ग्रन्थिः;
	}

      c_parser_consume_token (parser);

      जइ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	प्रत्यागम error_mark_ग्रन्थिः;

      matching_braces braces;
      जइ (!braces.require_open (parser))
	प्रत्यागम error_mark_ग्रन्थिः;

      वृक्षः selectors = c_parser_omp_context_selector (parser, set, parms);
      जइ (selectors == error_mark_ग्रन्थिः)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_ग्रन्थिः;
	}
      अण्णहा जइ (ret != error_mark_ग्रन्थिः)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अण्णहा
	भङ्ग;
    }
  जाव (1);

  जइ (ret == error_mark_ग्रन्थिः)
    प्रत्यागम ret;
  प्रत्यागम nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

स्थिर शून्य
c_finish_omp_declare_variant (c_parser *parser, वृक्षः fndecl, वृक्षः parms)
{
  matching_parens parens;
  जइ (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम;
    }

  जइ (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      गच्छ fail;
    }

  c_token *token = c_parser_peek_token (parser);
  वृक्षः variant = lookup_name (token->मानम्);

  जइ (variant == NULL_वृक्षः)
    {
      undeclared_variable (token->location, token->मानम्);
      variant = error_mark_ग्रन्थिः;
    }
  अण्णहा जइ (वृक्षः_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_ग्रन्थिः;
    }
  अण्णहा जइ (fndecl_built_in_p (variant)
	   && (strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", strlen ("__builtin_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", strlen ("__sync_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", strlen ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_ग्रन्थिः;
    }
  अण्णहा जइ (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_ग्रन्थिः;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  वृक्षः append_args_वृक्षः = NULL_वृक्षः;
  वृक्षः append_args_last;
  vec<वृक्षः> adjust_args_list = vNULL;
  तार्किक has_match = मिच्छ, has_adjust_args = मिच्छ;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  वृक्षः need_device_ptr_list = NULL_वृक्षः;
  वृक्षः ctx = error_mark_ग्रन्थिः;

  करेहि
    {
      जइ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ध्रुव वर्ण *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      जइ (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      गणना clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      जइ (strcmp (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      अण्णहा जइ (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      अण्णहा जइ (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      अण्णहा
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  गच्छ fail;
	}

      c_parser_consume_token (parser);

      जइ (!parens.require_open (parser))
	गच्छ fail;

      जइ (parms == NULL_वृक्षः)
	parms = error_mark_ग्रन्थिः;

      जइ (ccode == match)
	{
	  जइ (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = सच्च;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  जइ (ctx == error_mark_ग्रन्थिः)
	    गच्छ fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  जइ (ctx != error_mark_ग्रन्थिः
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      वृक्षः outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      अण्णहा जइ (ccode == adjust_args)
	{
	  has_adjust_args = सच्च;
	  जइ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ध्रुव वर्ण *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	      जइ (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  वृक्षः list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_वृक्षः);

		  वृक्षः arg;
		  जइ (variant != error_mark_ग्रन्थिः)
		    प्रति (वृक्षः c = list; c != NULL_वृक्षः; c = वृक्षः_CHAIN (c))
		      {
			वृक्षः decl = वृक्षः_PURPOSE (c);
			location_t arg_loc = व्यञ्जकम्_LOCATION (वृक्षः_मानम् (c));
			पूर्णाङ्क idx;
			प्रति (arg = parms, idx = 0; arg != रिक्त;
			     arg = वृक्षः_CHAIN (arg), idx++)
			  जइ (arg == decl)
			    भङ्ग;
			जइ (arg == NULL_वृक्षः)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    गच्छ fail;
			  }
			जइ (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    गच्छ fail;
			  }
			जइ (strcmp (p, "need_device_ptr") == 0
			    && वृक्षः_CODE (वृक्षः_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    गच्छ fail;
			  }
			adjust_args_list.safe_प्रक्षिप (arg);
			जइ (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_वृक्षः_list (
				NULL_वृक्षः,
				build_int_cst (
				  integer_type_ग्रन्थिः,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      अण्णहा
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  जइ (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  गच्छ fail;
		}
	    }
	  अण्णहा
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      गच्छ fail;
	    }
	}
      अण्णहा जइ (ccode == append_args)
	{
	  जइ (append_args_वृक्षः)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_वृक्षः = NULL_वृक्षः;
	    }
	  करेहि
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      जइ (!c_parser_next_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->मानम्)))
		{
		  error_at (loc, "expected %<interop%>");
		  गच्छ fail;
		}
	      c_parser_consume_token (parser);

	      जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		गच्छ fail;
	      तार्किक target = मिच्छ;
	      तार्किक targetsync = मिच्छ;
	      वृक्षः prefer_type_वृक्षः = NULL_वृक्षः;
	      जइ (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_वृक्षः)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		गच्छ fail;
	      जइ (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      वृक्षः t = build_वृक्षः_list (target ? boolean_true_ग्रन्थिः
					       : boolean_false_ग्रन्थिः,
					targetsync ? boolean_true_ग्रन्थिः
						   : boolean_false_ग्रन्थिः);
	      t = build1_loc (loc, NOP_व्यञ्जकम्, void_type_ग्रन्थिः, t);
	      t = build_वृक्षः_list (t, prefer_type_वृक्षः);
	      जइ (append_args_वृक्षः)
		{
		  वृक्षः_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      अण्णहा
		append_args_वृक्षः = append_args_last = t;
	      जइ (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		भङ्ग;
	      जइ (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		गच्छ fail;
	    }
	  जाव (सच्च);
	}

      parens.require_close (parser);
  } जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  जइ (variant != error_mark_ग्रन्थिः && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_ग्रन्थिः;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  जइ (variant == error_mark_ग्रन्थिः || ctx == error_mark_ग्रन्थिः)
    /* Previously diagnosed error.  */
    प्रत्यागम;

  जइ ((has_adjust_args || append_args_वृक्षः)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      प्रत्यागम;
    }

  जइ (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      वृक्षः base_type = वृक्षः_TYPE (fndecl);
      वृक्षः variant_type = वृक्षः_TYPE (variant);
      तार्किक unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_वृक्षः
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      जइ (append_args_वृक्षः
	  && TYPE_ARG_TYPES (base_type) == NULL_वृक्षः
	  && !TYPE_NO_NAMED_ARGS_STDARG_P (base_type))
	{
	  /* The base function is a pre-C23 unprototyped function.  Without
	     a prototype, we don't know the offset where the append_args go.
	     That offset needs to be stored with the append_args in the
	     variant function attributes, so we cannot presently handle
	     this case.  */
	  sorry_at (append_args_loc,
		    "%<append_args%> with unprototyped base function "
		    "is not supported yet");
	  inform (DECL_SOURCE_LOCATION (fndecl),
		  "base function %qD declared here", fndecl);
	  प्रत्यागम;
	}
      अण्णहा जइ (append_args_वृक्षः)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  पूर्णाङ्क nappend_args = 0;
	  पूर्णाङ्क nbase_args = 0;
	  प्रति (वृक्षः t = TYPE_ARG_TYPES (base_type);
	       t && वृक्षः_मानम् (t) != void_type_ग्रन्थिः; t = वृक्षः_CHAIN (t))
	    nbase_args++;
	  प्रति (वृक्षः t = append_args_वृक्षः; t; t = वृक्षः_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_वृक्षः = build_वृक्षः_list (build_int_cst (integer_type_ग्रन्थिः,
							     nbase_args),
					      append_args_वृक्षः);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  जइ (!unprototyped_variant)
	    {
	      वृक्षः args = TYPE_ARG_TYPES (variant_type);
	      प्रति (पूर्णाङ्क i = 0; args && i < nbase_args;
		   i++, args = वृक्षः_CHAIN (args))
		;
	      प्रति (पूर्णाङ्क i = 0; i < nappend_args; i++, args = वृक्षः_CHAIN (args))
		जइ (!args || !c_omp_interop_t_p (वृक्षः_मानम् (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    प्रत्यागम;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  वृक्षः args = TYPE_ARG_TYPES (base_type);
	  वृक्षः newargs = NULL_वृक्षः;
	  वृक्षः lastarg = NULL_वृक्षः;
	  प्रति (पूर्णाङ्क j = 0; j < nbase_args; j++, args = वृक्षः_CHAIN (args))
	    {
	      वृक्षः t = वृक्षः_cons (वृक्षः_PURPOSE (args),
				  वृक्षः_मानम् (args), NULL_वृक्षः);
	      जइ (lastarg)
		वृक्षः_CHAIN (lastarg) = t;
	      अण्णहा
		newargs = t;
	      lastarg = t;
	    }
	  वृक्षः type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? वृक्षः_TYPE (type) : pointer_sized_int_ग्रन्थिः;
	  प्रति (पूर्णाङ्क j = 0; j < nappend_args; j++)
	    {
	      वृक्षः t = वृक्षः_cons (NULL_वृक्षः, type, NULL_वृक्षः);
	      जइ (lastarg)
		वृक्षः_CHAIN (lastarg) = t;
	      अण्णहा
		newargs = t;
	      lastarg = t;
	    }
	  वृक्षः_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  वृक्षः saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  तार्किक fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  जइ (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      प्रत्यागम;
	    }
	  अण्णहा जइ (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      अण्णहा  /* No append_args present.  */
	{
	  जइ (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      प्रत्यागम;
	    }
	  अण्णहा जइ (TYPE_ARG_TYPES (variant_type) == NULL_वृक्षः
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_वृक्षः)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  वृक्षः construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  जइ (omp_context_selector_matches (ctx, NULL_वृक्षः, मिच्छ))
    {
      वृक्षः attr = वृक्षः_cons (get_identifier ("omp declare variant base"),
			     build_वृक्षः_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  जइ (need_device_ptr_list || append_args_वृक्षः)
    {
      वृक्षः variant_decl = वृक्षः_strip_nop_conversions (variant);
      वृक्षः t = build_वृक्षः_list (need_device_ptr_list,
				NULL_वृक्षः /* need_device_addr */);
      वृक्षः_CHAIN (t) = append_args_वृक्षः;
      DECL_ATTRIBUTES (variant_decl)
	= वृक्षः_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

स्थिर शून्य
c_finish_omp_declare_simd (c_parser *parser, वृक्षः fndecl, वृक्षः parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  जइ (clauses.exists () && clauses[0].type == CPP_EOF)
    प्रत्यागम;
  ध्रुव वर्ण *kind = "simd";
  जइ (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].मानम्);
  gcc_assert (strcmp (kind, "simd") == 0 || strcmp (kind, "variant") == 0);
  जइ (fndecl == NULL_वृक्षः || वृक्षः_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      प्रत्यागम;
    }
  जइ (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      प्रत्यागम;
    }
  जइ (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      प्रत्यागम;
    }

  जइ (parms == NULL_वृक्षः)
    parms = DECL_ARGUMENTS (fndecl);

  unsigned पूर्णाङ्क tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  जाव (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->मानम्);
      c_parser_consume_token (parser);
      parser->in_pragma = सच्च;

      जइ (strcmp (kind, "simd") == 0)
	{
	  वृक्षः c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  जइ (c != NULL_वृक्षः)
	    c = वृक्षः_cons (NULL_वृक्षः, c, NULL_वृक्षः);
	  c = build_वृक्षः_list (get_identifier ("omp declare simd"), c);
	  वृक्षः_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      अण्णहा
	{
	  gcc_assert (strcmp (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  जइ (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#जइ !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#नोचेद्यदि !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#अण्णहा
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
स्थिर वृक्षः
omp_start_variant_function (c_declarator *declarator, वृक्षः ctx)
{
  c_declarator *id = declarator;
  जाव (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  वृक्षः name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  प्रत्यागम name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
स्थिर शून्य
omp_finish_variant_function (वृक्षः decl, वृक्षः base_name, वृक्षः ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  वृक्षः base_decl = lookup_name (base_name);
  जइ (base_decl == error_mark_ग्रन्थिः)
    base_decl = NULL_वृक्षः;
  जइ (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      प्रत्यागम;
    }

  जइ (!comptypes (वृक्षः_TYPE (decl), वृक्षः_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      प्रत्यागम;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  वृक्षः construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  वृक्षः attrs = DECL_ATTRIBUTES (base_decl);
  वृक्षः match_loc_ग्रन्थिः
    = maybe_wrap_with_location (integer_zero_ग्रन्थिः,
				DECL_SOURCE_LOCATION (base_decl));
  वृक्षः loc_ग्रन्थिः = वृक्षः_cons (match_loc_ग्रन्थिः, integer_zero_ग्रन्थिः,
			     build_वृक्षः_list (match_loc_ग्रन्थिः,
					      integer_zero_ग्रन्थिः));
  attrs = वृक्षः_cons (get_identifier ("omp declare variant base"),
		     वृक्षः_cons (decl, ctx, loc_ग्रन्थिः), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  वृक्षः_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

तार्किक
c_maybe_parse_omp_decl (वृक्षः decl, वृक्षः d)
{
  gcc_assert (वृक्षः_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  ध्रुव वर्ण *directive[3] = {};
  प्रति (पूर्णाङ्क j = 0; j < 3; j++)
    {
      वृक्षः id = NULL_वृक्षः;
      जइ (first + j == last)
	भङ्ग;
      जइ (first[j].type == CPP_NAME)
	id = first[j].मानम्;
      अण्णहा जइ (first[j].type == CPP_KEYWORD)
	id = ridpointers[(पूर्णाङ्क) first[j].keyword];
      अण्णहा
	भङ्ग;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  ध्रुव c_omp_directive *dir = रिक्त;
  जइ (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  जइ (dir == रिक्त)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      प्रत्यागम मिच्छ;
    }
  जइ (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    प्रत्यागम मिच्छ;

  जइ (!flag_openmp && !dir->simd)
    प्रत्यागम सच्च;

  c_parser *parser = the_parser;
  unsigned पूर्णाङ्क tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = रिक्त;
  vec_safe_reserve (toks, last - first + 2, सच्च);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_प्रक्षिप (tok);
  जाव (++first < last)
    toks->quick_प्रक्षिप (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_प्रक्षिप (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_प्रक्षिप (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, रिक्त, NULL_वृक्षः);
  parser->in_omp_decl_attribute = NULL_वृक्षः;
  प्रत्यागम सच्च;
}

/* OpenMP 4.0:
   # pragma omp declare target new-line
   declarations and definitions
   # pragma omp end declare target new-line

   OpenMP 4.5:
   # pragma omp declare target ( extended-list ) new-line

   # pragma omp declare target declare-target-clauses[seq] new-line  */

#define OMP_DECLARE_TARGET_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TO)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ENTER)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LOCAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INDIRECT))

स्थिर शून्य
c_parser_omp_declare_target (c_parser *parser)
{
  वृक्षः clauses = NULL_वृक्षः;
  पूर्णाङ्क device_type = 0;
  तार्किक indirect = मिच्छ;
  तार्किक only_device_type_or_indirect = सच्च;
  जइ (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  जइ (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  अण्णहा जइ (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  अण्णहा
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_प्रक्षिप (current_omp_declare_target_attribute, attr);
      प्रत्यागम;
    }
  प्रति (वृक्षः c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_व्यञ्जकम् (c));
    }
  प्रति (वृक्षः c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	अनुवर्त;
      वृक्षः t = OMP_CLAUSE_DECL (c), id;
      वृक्षः at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      वृक्षः at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = मिच्छ;
      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      अण्णहा
	id = get_identifier ("omp declare target");
      जइ (at2)
	{
	  जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  अण्णहा जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || मानम्_member (get_identifier ("local"), वृक्षः_मानम् (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  अण्णहा
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  अनुवर्त;
	}
      जइ (!at1)
	{
	  DECL_ATTRIBUTES (t) = वृक्षः_cons (id, NULL_वृक्षः, DECL_ATTRIBUTES (t));
	  जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    वृक्षः_मानम् (DECL_ATTRIBUTES (t))
	      = वृक्षः_cons (NULL_वृक्षः, get_identifier ("local"),
			   वृक्षः_मानम् (DECL_ATTRIBUTES (t)));

	  जइ (वृक्षः_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    अनुवर्त;

	  symtab_ग्रन्थिः *ग्रन्थिः = symtab_ग्रन्थिः::get (t);
	  जइ (ग्रन्थिः != रिक्त)
	    {
	      ग्रन्थिः->offloadable = 1;
	      जइ (ENABLE_OFFLOADING)
		{
		  g->have_offload = सच्च;
		  जइ (is_a <varpool_ग्रन्थिः *> (ग्रन्थिः)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_प्रक्षिप (offload_vars, t);
		}
	    }
	}
      अण्णहा
	{
	  तार्किक saw_local = मानम्_member (get_identifier ("local"),
					 वृक्षः_मानम् (at1));
	  जइ (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      अनुवर्त;
	    }
	  अण्णहा जइ (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      अनुवर्त;
	    }
	}
      जइ (वृक्षः_CODE (t) != FUNCTION_DECL)
	अनुवर्त;
      जइ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  वृक्षः at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  जइ (at3 == NULL_वृक्षः)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= वृक्षः_cons (id, NULL_वृक्षः, DECL_ATTRIBUTES (t));
	    }
	}
      जइ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  वृक्षः at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  जइ (at3 == NULL_वृक्षः)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= वृक्षः_cons (id, NULL_वृक्षः, DECL_ATTRIBUTES (t));
	    }
	}
      जइ (indirect)
	{
	  वृक्षः at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  जइ (at4 == NULL_वृक्षः)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= वृक्षः_cons (id, NULL_वृक्षः, DECL_ATTRIBUTES (t));
	    }
	}
    }
  जइ ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  जइ (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "%<device_type%> clause must specify 'any' when used with "
	      "an %<indirect%> clause");
}

/* OpenMP 5.1
   #pragma omp begin assumes clauses[optseq] new-line

   #pragma omp begin declare target clauses[optseq] new-line

   #pragma omp begin declare variant match (context-selector) new-line  */

#define OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INDIRECT))

स्थिर शून्य
c_parser_omp_begin (c_parser *parser)
{
  ध्रुव वर्ण *p = "";
  c_parser_consume_pragma (parser);
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
  जइ (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      जइ (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
	  वृक्षः clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  पूर्णाङ्क device_type = 0;
	  पूर्णाङ्क indirect = 0;
	  प्रति (वृक्षः c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_व्यञ्जकम् (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_प्रक्षिप (current_omp_declare_target_attribute, attr);
	}
      अण्णहा जइ (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ध्रुव वर्ण *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      वृक्षः id = c_parser_peek_token (parser)->मानम्;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  जइ (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      प्रत्यागम;
	    }

	  c_parser_consume_token (parser);

	  जइ (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, मिच्छ);
	      प्रत्यागम;
	    }

	  वृक्षः ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_वृक्षः);
	  जइ (ctx != error_mark_ग्रन्थिः)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  जइ (ctx != error_mark_ग्रन्थिः
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      वृक्षः outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  जइ (ctx == error_mark_ग्रन्थिः
	      || !omp_context_selector_matches (ctx, NULL_वृक्षः, मिच्छ, सच्च))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, मिच्छ);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      प्रत्यागम;
	    }
	  अण्णहा
	    {
	      तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_प्रक्षिप (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      अण्णहा
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	}
    }
  अण्णहा जइ (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
      c_parser_omp_assumption_clauses (parser, मिच्छ);
      संरचना c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_प्रक्षिप (current_omp_begin_assumes, a);
    }
  अण्णहा
    {
      c_parser_error (parser, "expected %<declare target%>, "
		      "%<declare variant%>, or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 4.0
   #pragma omp end declare target

   OpenMP 5.1
   #pragma omp end assumes
   #pragma omp end declare variant  */

स्थिर शून्य
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ध्रुव वर्ण *p = "";
  c_parser_consume_pragma (parser);
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
  जइ (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      जइ (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
	  c_parser_skip_to_pragma_eol (parser);
	  जइ (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  अण्णहा
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->निष्कासय ();
	      जइ (a.attr_syntax != attr_syntax)
		{
		  जइ (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  अण्णहा
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      अण्णहा जइ (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
	  c_parser_skip_to_pragma_eol (parser);
	  जइ (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  अण्णहा
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->निष्कासय ();
	      जइ (a.attr_syntax != attr_syntax)
		{
		  जइ (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  अण्णहा
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      अण्णहा
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  प्रत्यागम;
	}
    }
  अण्णहा जइ (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
      c_parser_skip_to_pragma_eol (parser);
      जइ (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      अण्णहा
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->निष्कासय ();
	  जइ (a.attr_syntax != attr_syntax)
	    {
	      जइ (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      अण्णहा
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  अण्णहा
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

स्थिर शून्य
c_parser_omp_declare_mapper (c_parser *parser, गणना pragma_context context)
{
  वृक्षः type, mapper_name = NULL_वृक्षः, var = NULL_वृक्षः, stmt, stmtlist;
  वृक्षः maplist = NULL_वृक्षः, mapper_id, mapper_decl, t;
  c_token *token;

  जइ (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      गच्छ fail;
    }

  जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    गच्छ fail;

  token = c_parser_peek_token (parser);

  जइ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      विकल्प (token->type)
	{
	पक्ष CPP_NAME:
	  mapper_name = token->मानम्;
	  c_parser_consume_token (parser);
	  भङ्ग;
	पक्ष CPP_KEYWORD:
	  जइ (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_वृक्षः;
	      c_parser_consume_token (parser);
	      भङ्ग;
	    }
	  /* Fallthrough.  */
	स्वभाव:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  प्रत्यागम;
	}

      जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	गच्छ fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    संरचना c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, रिक्त, रिक्त);
    जइ (type == error_mark_ग्रन्थिः)
      गच्छ fail;
    जइ (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, मिच्छ);
	प्रत्यागम;
      }
    प्रति (वृक्षः t = DECL_INITIAL (mapper_decl); t; t = वृक्षः_CHAIN (t))
      जइ (comptypes (वृक्षः_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + परिमाण ("omp declare mapper ") - 1,
		    type);
	  वृक्षः prevmapper = वृक्षः_मानम् (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  प्रत्यागम;
	}
  }

  token = c_parser_peek_token (parser);
  जइ (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->मानम्, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  अण्णहा
    {
      error_at (token->location, "expected identifier");
      गच्छ fail;
    }

  जइ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    गच्छ fail;

  प्रक्षिप_scope ();
  stmtlist = प्रक्षिप_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      जइ (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  गच्छ fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, सच्च);
    }

  जइ (maplist == NULL_वृक्षः)
    {
      error_at (निवेशः_location, "missing %<map%> clause");
      गच्छ fail;
    }
  वृक्षः list;
  प्रति (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      वृक्षः dvar = OMP_CLAUSE_DECL (list);
      जाव (!DECL_P (dvar) && वृक्षः_OPERAND_LENGTH (dvar))
	dvar = वृक्षः_OPERAND (dvar, 0);
      जइ (dvar == var)
	भङ्ग;
    }
  जइ (!list)
    error_at (निवेशः_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_ग्रन्थिः (OMP_DECLARE_MAPPER);
  वृक्षः_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  निष्कासय_stmt_list (stmtlist);
  निष्कासय_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = वृक्षः_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  प्रत्यागम;

 fail:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

स्थिर शून्य
c_parser_omp_declare_reduction (c_parser *parser, गणना pragma_context context)
{
  unsigned पूर्णाङ्क tokens_avail = 0, i;
  c_token *saved_tokens = रिक्त;
  vec<वृक्षः> types = vNULL;
  vec<c_token> clauses = vNULL;
  गणना वृक्षः_code reduc_code = ERROR_MARK;
  वृक्षः reduc_id = NULL_वृक्षः;
  वृक्षः type;
  location_t rloc = c_parser_peek_token (parser)->location;

  जइ (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      गच्छ fail;
    }

  जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    गच्छ fail;

  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_PLUS:
      reduc_code = PLUS_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MULT:
      reduc_code = MULT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MINUS:
      reduc_code = MINUS_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_AND:
      reduc_code = BIT_AND_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_XOR:
      reduc_code = BIT_XOR_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_OR:
      reduc_code = BIT_IOR_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_OR_OR:
      reduc_code = TRUTH_ORIF_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_NAME:
      ध्रुव वर्ण *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "min") == 0)
	{
	  reduc_code = MIN_व्यञ्जकम्;
	  भङ्ग;
	}
      जइ (strcmp (p, "max") == 0)
	{
	  reduc_code = MAX_व्यञ्जकम्;
	  भङ्ग;
	}
      reduc_id = c_parser_peek_token (parser)->मानम्;
      भङ्ग;
    स्वभाव:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      गच्छ fail;
    }

  वृक्षः orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    गच्छ fail;

  जाव (सच्च)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      संरचना c_type_name *ctype = c_parser_type_name (parser);
      जइ (ctype != रिक्त)
	{
	  type = groktypename (ctype, रिक्त, रिक्त);
	  जइ (type == error_mark_ग्रन्थिः)
	    ;
	  अण्णहा जइ ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || वृक्षः_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_वृक्षः)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  अण्णहा जइ (वृक्षः_CODE (type) == FUNCTION_TYPE
		   || वृक्षः_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  अण्णहा जइ (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  अण्णहा जइ (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  अण्णहा
	    {
	      वृक्षः t;
	      प्रति (t = DECL_INITIAL (reduc_decl); t; t = वृक्षः_CHAIN (t))
		जइ (comptypes (वृक्षः_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + परिमाण ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (वृक्षः_VEC_ELT (वृक्षः_मानम् (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    भङ्ग;
		  }
	      जइ (t == NULL_वृक्षः)
		types.safe_प्रक्षिप (type);
	    }
	  जइ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अण्णहा
	    भङ्ग;
	}
      अण्णहा
	भङ्ग;
    }

  जइ (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      जाव (सच्च)
	{
	  c_token *token = c_parser_peek_token (parser);
	  जइ (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    भङ्ग;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      प्रत्यागम;
    }

  जइ (types.length () > 1)
    {
      जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  जइ (token->type == CPP_EOF)
	    गच्छ fail;
	  clauses.safe_प्रक्षिप (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_प्रक्षिप (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, परिमाण (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_प्रक्षिप (eof_token);
      clauses.safe_प्रक्षिप (eof_token);
    }

  पूर्णाङ्क errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      जइ (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = सच्च;
	}

      तार्किक nested = current_function_decl != NULL_वृक्षः;
      जइ (nested)
	c_प्रक्षिप_function_context ();
      वृक्षः fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, सच्च);
      प्रक्षिप_scope ();
      वृक्षः stmt = प्रक्षिप_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      वृक्षः omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      वृक्षः omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      संरचना c_व्यञ्जकम् combiner = c_parser_expression (parser);
      संरचना c_व्यञ्जकम् initializer;
      वृक्षः omp_priv = NULL_वृक्षः, omp_orig = NULL_वृक्षः;
      तार्किक bad = मिच्छ;
      initializer.set_error ();
      जइ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = सच्च;
      अण्णहा जइ (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      जइ (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->मानम्),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  निष्कासय_scope ();
	  प्रक्षिप_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_ग्रन्थिः;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  जइ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = सच्च;
	  अण्णहा जइ (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = सच्च;
	    }
	  अण्णहा जइ (strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->मानम्),
			   "omp_priv") != 0)
	    {
	      जइ (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = सच्च;
		}
	      अण्णहा
		initializer = c_parser_postfix_expression (parser);
	      जइ (initializer.मानम्
		  && वृक्षः_CODE (initializer.मानम्) == CALL_व्यञ्जकम्)
		{
		  पूर्णाङ्क j;
		  वृक्षः c = initializer.मानम्;
		  प्रति (j = 0; j < call_व्यञ्जकम्_nargs (c); j++)
		    {
		      वृक्षः a = CALL_व्यञ्जकम्_ARG (c, j);
		      STRIP_NOPS (a);
		      जइ (वृक्षः_CODE (a) == ADDR_व्यञ्जकम्
			  && वृक्षः_OPERAND (a, 0) == omp_priv)
			भङ्ग;
		    }
		  जइ (j == call_व्यञ्जकम्_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  अण्णहा
	    {
	      c_parser_consume_token (parser);
	      जइ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = सच्च;
	      अण्णहा
		{
		  वृक्षः st = प्रक्षिप_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पङ्क्तिः_table, loc);
		  start_init (omp_priv, NULL_वृक्षः, मिच्छ, मिच्छ, &richloc);
		  संरचना c_व्यञ्जकम् init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.मानम्,
		      	       init.original_type, NULL_वृक्षः);
		  निष्कासय_stmt_list (st);
		}
	    }
	  जइ (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = सच्च;
	}

      जइ (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  वृक्षः t = वृक्षः_cons (type, make_वृक्षः_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 0) = omp_out;
	  वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 1) = omp_in;
	  वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 2) = combiner.मानम्;
	  walk_वृक्षः (&combiner.मानम्, c_check_omp_declare_reduction_r,
		     &वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 0), रिक्त);
	  जइ (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 3) = omp_priv;
	      वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 4) = omp_orig;
	      वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 5) = initializer.मानम्;
	      walk_वृक्षः (&initializer.मानम्, c_check_omp_declare_reduction_r,
			 &वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 3), रिक्त);
	      walk_वृक्षः (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &वृक्षः_VEC_ELT (वृक्षः_मानम् (t), 3), रिक्त);
	    }
	}

      निष्कासय_stmt_list (stmt);
      निष्कासय_scope ();
      जइ (cfun->language != रिक्त)
	{
	  ggc_free (cfun->language);
	  cfun->language = रिक्त;
	}
      set_cfun (रिक्त);
      current_function_decl = NULL_वृक्षः;
      जइ (nested)
	c_निष्कासय_function_context ();

      जइ (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      जइ (bad)
	गच्छ fail;
      जइ (errs != errorcount)
	भङ्ग;
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

स्थिर तार्किक
c_parser_omp_declare (c_parser *parser, गणना pragma_context context)
{
  c_parser_consume_pragma (parser);
  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  प्रत्यागम सच्च;
	}
      जइ (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  प्रत्यागम मिच्छ;
	}
      जइ (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  प्रत्यागम मिच्छ;
	}
      जइ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  प्रत्यागम मिच्छ;
	}
      जइ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  प्रत्यागम मिच्छ;
	}
      जइ (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  प्रत्यागम सच्च;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  प्रत्यागम मिच्छ;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

स्थिर शून्य
c_parser_omp_requires (c_parser *parser)
{
  गणना omp_requires new_req = (गणना omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      जइ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      जइ (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ध्रुव वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  गणना omp_requires this_req = (गणना omp_requires) 0;

	  जइ (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  अण्णहा जइ (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  अण्णहा जइ (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  अण्णहा जइ (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  अण्णहा जइ (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  अण्णहा जइ (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      जइ (parens.require_open (parser))
		{
		  जइ (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      वृक्षः v = c_parser_peek_token (parser)->मानम्;
		      p = IDENTIFIER_POINTER (v);

		      जइ (!strcmp (p, "seq_cst"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      अण्णहा जइ (!strcmp (p, "relaxed"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      अण्णहा जइ (!strcmp (p, "release"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      अण्णहा जइ (!strcmp (p, "acq_rel"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      अण्णहा जइ (!strcmp (p, "acquire"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  जइ (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      विकल्प (c_parser_peek_token (parser)->type)
			{
			पक्ष CPP_EOF:
			पक्ष CPP_PRAGMA_EOL:
			पक्ष CPP_CLOSE_PAREN:
			  भङ्ग;
			स्वभाव:
			  जइ (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  भङ्ग;
			}
		    }
		  अण्णहा
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  जइ (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, मिच्छ);
		      प्रत्यागम;
		    }
		}
	      p = रिक्त;
	    }
	  अण्णहा
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, मिच्छ);
	      प्रत्यागम;
	    }
	  जइ (p)
	    c_parser_consume_token (parser);
	  जइ (this_req)
	    {
	      जइ ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  जइ ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  जइ (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      अण्णहा जइ ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (गणना omp_requires) 0;
		}
	      अण्णहा जइ ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (गणना omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      अण्णहा जइ ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (गणना omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (गणना omp_requires) (omp_requires_mask | this_req);
	      अनुवर्त;
	    }
	}
      भङ्ग;
    }
  c_parser_skip_to_pragma_eol (parser);

  जइ (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

स्थिर वृक्षः
c_finish_taskloop_clauses (वृक्षः clauses)
{
  वृक्षः *pc = &clauses;
  प्रति (वृक्षः c = clauses; c; c = *pc)
    {
      तार्किक remove = मिच्छ;
      जइ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  वृक्षः type = strip_array_types (वृक्षः_TYPE (OMP_CLAUSE_DECL (c)));
	  जइ (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = सच्च;
	    }
	  अण्णहा जइ (वृक्षः_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = सच्च;
	    }
	}
      जइ (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      अण्णहा
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  प्रत्यागम clauses;
}

/* OpenMP 4.5:
   #pragma omp taskloop taskloop-clause[optseq] new-line
     for-loop

   #pragma omp taskloop simd taskloop-simd-clause[optseq] new-line
     for-loop  */

#define OMP_TASKLOOP_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_GRAINSIZE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अङ्कः_TASKS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOGROUP)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIORITY)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION))

स्थिर वृक्षः
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       वर्ण *p_name, omp_clause_mask mask, वृक्षः *cclauses,
		       तार्किक *if_p)
{
  वृक्षः clauses, block, ret;

  strcat (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  जइ ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अङ्कः_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  जइ (c_parser_next_token_is (parser, CPP_NAME))
    {
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);

      जइ (strcmp (p, "simd") == 0)
	{
	  वृक्षः cclauses_buf[C_OMP_CLAUSE_SPLIT_गणनम्];
	  जइ (cclauses == रिक्त)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  जइ (!flag_openmp)  /* flag_openmp_simd  */
	    प्रत्यागम c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (सच्च);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, सच्च);
	  जइ (ret == रिक्त)
	    प्रत्यागम ret;
	  ret = make_ग्रन्थिः (OMP_TASKLOOP);
	  वृक्षः_TYPE (ret) = void_type_ग्रन्थिः;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_व्यञ्जकम्_LOCATION (ret, loc);
	  add_stmt (ret);
	  प्रत्यागम ret;
	}
    }
  जइ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, मिच्छ);
      प्रत्यागम NULL_वृक्षः;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  जइ (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (सच्च);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, रिक्त, if_p);
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
स्थिर वृक्षः
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  वृक्षः sizes = NULL_वृक्षः;

  जइ (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  जइ (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_POINTER (tok->मानम्)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      प्रत्यागम error_mark_ग्रन्थिः;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  जइ (!parens.require_open (parser))
    प्रत्यागम error_mark_ग्रन्थिः;

  vec<वृक्षः, va_gc> *sizes_vec
    = c_parser_व्यञ्जकम्_list (parser, सच्च, सच्च, रिक्त, रिक्त, रिक्त, रिक्त);
  sizes = build_वृक्षः_list_vec (sizes_vec);
  release_वृक्षः_vector (sizes_vec);

  प्रति (वृक्षः s = sizes; s; s = वृक्षः_CHAIN (s))
    {
      वृक्षः व्यञ्जकम् = वृक्षः_मानम् (s);
      जइ (व्यञ्जकम् == error_mark_ग्रन्थिः)
	{
	  parens.skip_until_found_close (parser);
	  प्रत्यागम error_mark_ग्रन्थिः;
	}

      HOST_WIDE_INT n;
      जइ (!INTEGRAL_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्))
	  || !वृक्षः_fits_shwi_p (व्यञ्जकम्)
	  || (n = वृक्षः_to_shwi (व्यञ्जकम्)) <= 0
	  || (पूर्णाङ्क) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  वृक्षः_मानम् (s) = integer_one_ग्रन्थिः;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  वृक्षः c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  प्रत्यागम c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

स्थिर वृक्षः
c_parser_omp_tile (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  जइ (!clauses || clauses == error_mark_ग्रन्थिः)
    प्रत्यागम error_mark_ग्रन्थिः;

  वृक्षः block = c_begin_compound_stmt (सच्च);
  वृक्षः ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    रिक्त, if_p);
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

स्थिर वृक्षः
c_parser_omp_unroll (location_t loc, c_parser *parser, तार्किक *if_p)
{
  वृक्षः clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", सच्च);

  वृक्षः block = c_begin_compound_stmt (सच्च);
  वृक्षः ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    रिक्त, if_p);
  block = c_end_compound_stmt (loc, block, सच्च);
  add_stmt (block);

  प्रत्यागम ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

स्थिर शून्य
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

स्थिर तार्किक
c_parser_omp_error (c_parser *parser, गणना pragma_context context)
{
  पूर्णाङ्क at_compilation = -1;
  पूर्णाङ्क severity_fatal = -1;
  वृक्षः message = NULL_वृक्षः;
  तार्किक bad = मिच्छ;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      जइ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      जइ (!c_parser_next_token_is (parser, CPP_NAME))
	भङ्ग;

      ध्रुव वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      location_t cloc = c_parser_peek_token (parser)->location;
      स्थिर ध्रुव वर्ण *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      पूर्णाङ्क *v = रिक्त;
      पूर्णाङ्क idx = 0, n = -1;
      वृक्षः m = NULL_वृक्षः;

      जइ (!strcmp (p, "at"))
	v = &at_compilation;
      अण्णहा जइ (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      अण्णहा जइ (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, मिच्छ);
	  प्रत्यागम मिच्छ;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      जइ (parens.require_open (parser))
	{
	  जइ (v == रिक्त)
	    {
	      location_t व्यञ्जकम्_loc = c_parser_peek_token (parser)->location;
	      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	      व्यञ्जकम् = convert_lvalue_to_rvalue (व्यञ्जकम्_loc, व्यञ्जकम्, सच्च, सच्च);
	      m = convert (const_string_type_ग्रन्थिः, व्यञ्जकम्.मानम्);
	      m = c_fully_fold (m, मिच्छ, रिक्त);
	    }
	  अण्णहा
	    {
	      जइ (c_parser_next_token_is (parser, CPP_NAME))
		{
		  वृक्षः val = c_parser_peek_token (parser)->मानम्;
		  ध्रुव वर्ण *q = IDENTIFIER_POINTER (val);

		  जइ (!strcmp (q, args[idx]))
		    n = 0;
		  अण्णहा जइ (!strcmp (q, args[idx + 1]))
		    n = 1;
		}
	      जइ (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  bad = सच्च;
		  विकल्प (c_parser_peek_token (parser)->type)
		    {
		    पक्ष CPP_EOF:
		    पक्ष CPP_PRAGMA_EOL:
		    पक्ष CPP_CLOSE_PAREN:
		      भङ्ग;
		    स्वभाव:
		      जइ (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      भङ्ग;
		    }
		}
	      अण्णहा
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  जइ (v == रिक्त)
	    {
	      जइ (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = सच्च;
		}
	      अण्णहा
		message = m;
	    }
	  अण्णहा जइ (n != -1)
	    {
	      जइ (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = सच्च;
		}
	      अण्णहा
		*v = n;
	    }
	}
      अण्णहा
	bad = सच्च;
    }
  c_parser_skip_to_pragma_eol (parser);
  जइ (bad)
    प्रत्यागम सच्च;

  जइ (at_compilation == -1)
    at_compilation = 1;
  जइ (severity_fatal == -1)
    severity_fatal = 1;
  जइ (!at_compilation)
    {
      जइ (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  प्रत्यागम सच्च;
	}
      जइ (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = सच्च;
	  प्रत्यागम सच्च;
	}
      वृक्षः fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      जइ (!message)
	message = build_zero_cst (const_string_type_ग्रन्थिः);
      वृक्षः stmt = build_call_व्यञ्जकम्_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_ग्रन्थिः));
      add_stmt (stmt);
      प्रत्यागम सच्च;
    }
  ध्रुव वर्ण *सन्देशः = रिक्त;
  जइ (message)
    {
      सन्देशः = c_getstr (message);
      जइ (सन्देशः == रिक्त)
	सन्देशः = _("<message unknown at compile time>");
    }
  ध्रुव गणना diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  जइ (सन्देशः)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", सन्देशः);
  अण्णहा
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  प्रत्यागम मिच्छ;
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

स्थिर शून्य
c_parser_omp_assumption_clauses (c_parser *parser, तार्किक is_assume)
{
  तार्किक no_openmp = मिच्छ;
  तार्किक no_openmp_constructs = मिच्छ;
  तार्किक no_openmp_routines = मिच्छ;
  तार्किक no_parallelism = मिच्छ;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (रिक्त);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  जइ (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      जइ (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      जइ (!c_parser_next_token_is (parser, CPP_NAME))
	भङ्ग;

      ध्रुव वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      location_t cloc = c_parser_peek_token (parser)->location;

      जइ (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  जइ (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = सच्च;
	}
      अण्णहा जइ (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  जइ (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = सच्च;
	}
      अण्णहा जइ (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  जइ (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = सच्च;
	}
      अण्णहा जइ (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  जइ (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = सच्च;
	}
      अण्णहा जइ (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  जइ (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_व्यञ्जकम् व्यञ्जकम् = c_parser_व्यञ्जकम्_no_commas (parser, रिक्त);
	      वृक्षः t = convert_lvalue_to_rvalue (eloc, व्यञ्जकम्, सच्च, सच्च).मानम्;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, मिच्छ, रिक्त);
	      जइ (is_assume && t != error_mark_ग्रन्थिः)
		{
		  वृक्षः fn = build_call_व्यञ्जकम्_internal_loc (eloc, IFN_ASSUME,
							  void_type_ग्रन्थिः, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      अण्णहा जइ (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  जइ (parens.require_open (parser))
	    {
	      करेहि
		{
		  ध्रुव वर्ण *directive[3] = {};
		  पूर्णाङ्क i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  प्रति (i = 0; i < 3; i++)
		    {
		      वृक्षः id;
		      जइ (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->मानम्;
		      अण्णहा जइ (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  गणना rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      अण्णहा
			भङ्ग;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  जइ (i == 0)
		    error_at (dloc, "expected directive name");
		  अण्णहा
		    {
		      ध्रुव संरचना c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      जइ (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      अण्णहा जइ (dir == रिक्त
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      अण्णहा
			{
			  पूर्णाङ्क id = dir - c_omp_directives;
			  जइ (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  अण्णहा जइ (!bitmap_set_bit (p[0] == 'a'
						    ? &absent_head
						    : &contains_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned multiple times in %qs "
					    "clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "", p);
			}
		      प्रति (; i; --i)
			c_parser_consume_token (parser);
		    }
		  जइ (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  अण्णहा
		    भङ्ग;
		}
	      जाव (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      अण्णहा जइ (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  जइ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      अण्णहा
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  भङ्ग;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

स्थिर शून्य
c_parser_omp_assume (c_parser *parser, तार्किक *if_p)
{
  c_parser_omp_assumption_clauses (parser, सच्च);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

स्थिर शून्य
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, मिच्छ);
}

/* Helper function for c_parser_omp_metadirective.  */

स्थिर शून्य
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<वृक्षः> &labels)
{
  पूर्णाङ्क nesting_depth = 0;
  पूर्णाङ्क bracket_depth = 0;
  तार्किक ignore_label = मिच्छ;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  जाव (1)
    {
      c_token *token = c_parser_peek_token (parser);
      तार्किक stop = मिच्छ;

      जइ (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = सच्च;

      विकल्प (token->type)
	{
	पक्ष CPP_EOF:
	  भङ्ग;
	पक्ष CPP_NAME:
	  जइ (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_प्रक्षिप (token->मानम्);
	  गच्छ add;
	पक्ष CPP_OPEN_BRACE:
	  ++nesting_depth;
	  गच्छ add;
	पक्ष CPP_CLOSE_BRACE:
	  जइ (--nesting_depth == 0 && bracket_depth == 0)
	    stop = सच्च;
	  गच्छ add;
	पक्ष CPP_OPEN_PAREN:
	  ++bracket_depth;
	  गच्छ add;
	पक्ष CPP_CLOSE_PAREN:
	  --bracket_depth;
	  गच्छ add;
	पक्ष CPP_COLON:
	  ignore_label = मिच्छ;
	  गच्छ add;
	पक्ष CPP_SEMICOLON:
	  जइ (nesting_depth == 0 && bracket_depth == 0)
	    stop = सच्च;
	  गच्छ add;
	स्वभाव:
	add:
	  tokens.safe_प्रक्षिप (*token);
	  जइ (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  अण्णहा जइ (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  अण्णहा
	    c_parser_consume_token (parser);
	  जइ (stop)
	    भङ्ग;
	  अनुवर्त;
	}
      भङ्ग;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

स्थिर शून्य
c_parser_omp_metadirective (c_parser *parser, तार्किक *if_p)
{
  स्थिर unsigned पूर्णाङ्क metadirective_region_गणनम् = 0;

  वृक्षः ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<वृक्षः> body_labels;
  auto_vec<ध्रुव संरचना c_omp_directive *> directives;
  auto_vec<वृक्षः> ctxs;
  vec<संरचना omp_variant> candidates;
  तार्किक default_seen = मिच्छ;
  पूर्णाङ्क directive_token_idx = 0;
  वृक्षः standalone_body = NULL_वृक्षः;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  तार्किक requires_body = मिच्छ;

  ret = make_ग्रन्थिः (OMP_METADIRECTIVE);
  SET_व्यञ्जकम्_LOCATION (ret, pragma_loc);
  वृक्षः_TYPE (ret) = void_type_ग्रन्थिः;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_वृक्षः;

  c_parser_consume_pragma (parser);
  जाव (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      जइ (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      जइ (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  गच्छ error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      ध्रुव वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      जइ (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      तार्किक default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      जइ (default_p)
	{
	  जइ (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      गच्छ error;
	    }
	  default_seen = सच्च;
	}
      अण्णहा जइ (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  गच्छ error;
	}
      जइ (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  गच्छ error;
	}

      matching_parens parens;
      वृक्षः ctx = NULL_वृक्षः;
      तार्किक skip = मिच्छ;

      जइ (!parens.require_open (parser))
	गच्छ error;

      जइ (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_वृक्षः);
	  जइ (ctx == error_mark_ग्रन्थिः)
	    गच्छ error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  जइ (ctx == error_mark_ग्रन्थिः)
	    गच्छ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_वृक्षः, मिच्छ) == 0);

	  जइ (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      गच्छ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ध्रुव वर्ण *directive[3] = {};
      पूर्णाङ्क i;
      प्रति (i = 0; i < 3; i++)
	{
	  वृक्षः id;
	  जइ (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      जइ (i == 0)
		directive[i++] = "nothing";
	      भङ्ग;
	    }
	  अण्णहा जइ (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->मानम्;
	  अण्णहा जइ (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      गणना rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  अण्णहा
	    भङ्ग;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      जइ (i == 0)
	{
	  error_at (loc, "expected directive name");
	  गच्छ error;
	}

      ध्रुव संरचना c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      जइ (omp_directive == रिक्त)
	{
	  प्रति (पूर्णाङ्क j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  गच्छ error;
	}
      अण्णहा
	{
	  पूर्णाङ्क token_गणनम् = 0;
	  जइ (omp_directive->first) token_गणनम्++;
	  जइ (omp_directive->second) token_गणनम्++;
	  जइ (omp_directive->third) token_गणनम्++;
	  प्रति (पूर्णाङ्क j = 0; j < token_गणनम्; j++)
	    c_parser_consume_token (parser);
	}
      जइ (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  गच्छ error;
	}
      जइ (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  गच्छ error;
	}
      जइ (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = सच्च;

      जइ (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (गणना pragma_kind) omp_directive->id;

	  directives.safe_प्रक्षिप (omp_directive);
	  directive_tokens.safe_प्रक्षिप (pragma_token);
	  ctxs.safe_प्रक्षिप (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      पूर्णाङ्क nesting_depth = 0;
      जाव (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  विकल्प (token->type)
	    {
	    पक्ष CPP_EOF:
	    पक्ष CPP_PRAGMA_EOL:
	      भङ्ग;
	    पक्ष CPP_OPEN_PAREN:
	      ++nesting_depth;
	      गच्छ add;
	    पक्ष CPP_CLOSE_PAREN:
	      जइ (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  भङ्ग;
		}
	      गच्छ add;
	    स्वभाव:
	    add:
	      जइ (!skip)
		directive_tokens.safe_प्रक्षिप (*token);
	      c_parser_consume_token (parser);
	      अनुवर्त;
	    }
	  भङ्ग;
	}

      जइ (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, परिमाण (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_प्रक्षिप (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  जइ (ctxs.length () == 1)
    {
      वृक्षः ctx = ctxs[0];
      जइ (ctx == NULL_वृक्षः
	  || (omp_context_selector_matches (ctx, NULL_वृक्षः, मिच्छ) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	प्रत्यागम;
    }

  जइ (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ध्रुव संरचना c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", रिक्त, रिक्त);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_प्रक्षिप (omp_directive);
      directive_tokens.safe_प्रक्षिप (pragma_token);
      ctxs.safe_प्रक्षिप (NULL_वृक्षः);

      c_token eol_token;
      memset (&eol_token, 0, परिमाण (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_प्रक्षिप (eol_token);
    }

  जइ (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  unsigned i;
  वृक्षः ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      करेहि
	tokens.safe_प्रक्षिप (directive_tokens [directive_token_idx++]);
      जाव (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      प्रति (unsigned j = 0; j < body_tokens.length (); j++)
	tokens.safe_प्रक्षिप (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, परिमाण (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_प्रक्षिप (eof_token);
      tokens.safe_प्रक्षिप (eof_token);

      unsigned पूर्णाङ्क old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      संरचना omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      संरचना omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      संरचना omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_अङ्कः = ++metadirective_region_गणनम्;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = रिक्त;
      parser->omp_metadirective_state = &new_state;

      पूर्णाङ्क prev_errorcount = errorcount;
      वृक्षः directive = c_begin_compound_stmt (सच्च);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_वृक्षः);
      directive = c_end_compound_stmt (pragma_loc, directive, सच्च);
      तार्किक standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      जइ (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  जइ (standalone_body == NULL_वृक्षः)
	    {
	      standalone_body = प्रक्षिप_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = निष्कासय_stmt_list (standalone_body);
	    }
	  अण्णहा
	    c_parser_skip_to_end_of_block_or_statement (parser, सच्च);
	}

      वृक्षः body = standalone_p ? standalone_body : NULL_वृक्षः;
      वृक्षः variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      जइ (errorcount == prev_errorcount)
	{
	  gcc_assert (parser->tokens_avail == 2);
	  gcc_assert (c_parser_next_token_is (parser, CPP_EOF));
	  gcc_assert (c_parser_peek_2nd_token (parser)->type == CPP_EOF);
	}

      parser->tokens = old_tokens;
      parser->tokens_avail = old_tokens_avail;
      parser->in_omp_attribute_pragma = old_in_omp_attribute_pragma;
      parser->omp_metadirective_state = old_state;
    }

  /* Try to resolve the metadirective early.  */
  candidates = omp_early_resolve_metadirective (ret);
  जइ (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  प्रत्यागम;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  जइ (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, मिच्छ);
}

/* Main entry point to parsing most OpenMP pragmas.  */

स्थिर शून्य
c_parser_omp_construct (c_parser *parser, तार्किक *if_p)
{
  गणना pragma_kind p_kind;
  location_t loc;
  वृक्षः stmt;
  वर्ण p_name[परिमाण "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  विकल्प (p_kind)
    {
    पक्ष PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, सच्च);
      प्रत्यागम;
    पक्ष PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      भङ्ग;
    पक्ष PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OACC_KERNELS:
    पक्ष PRAGMA_OACC_PARALLEL:
    पक्ष PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      भङ्ग;
    पक्ष PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      भङ्ग;
    पक्ष PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, मिच्छ);
      प्रत्यागम;
    पक्ष PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, रिक्त, if_p,
				  UNKNOWN_LOCATION);
      भङ्ग;
    पक्ष PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, रिक्त);
      भङ्ग;
    पक्ष PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, रिक्त, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      प्रत्यागम;
    पक्ष PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      भङ्ग;
    पक्ष PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }

  जइ (stmt && stmt != error_mark_ग्रन्थिः)
    gcc_assert (व्यञ्जकम्_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#define OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

स्थिर शून्य
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  वृक्षः vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, रिक्त);
  वृक्षः clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (शून्य) vars;
  (शून्य) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

स्थिर शून्य
c_parser_omp_threadprivate (c_parser *parser)
{
  वृक्षः vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, रिक्त);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  प्रति (t = vars; t; t = वृक्षः_CHAIN (t))
    {
      वृक्षः v = वृक्षः_PURPOSE (t);
      loc = व्यञ्जकम्_LOCATION (वृक्षः_मानम् (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      जइ (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      अण्णहा जइ (वृक्षः_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      अण्णहा जइ (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      अण्णहा जइ (वृक्षः_TYPE (v) == error_mark_ग्रन्थिः)
	;
      अण्णहा जइ (! COMPLETE_TYPE_P (वृक्षः_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      अण्णहा
	{
	  जइ (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      जइ (DECL_RTL_SET_P (v))
		make_decl_rtl (v);
	    }
	  C_DECL_THREADPRIVATE_P (v) = 1;
	}
    }

  c_parser_skip_to_pragma_eol (parser);
}

/* Parse a transaction attribute (GCC Extension).

   transaction-attribute:
     gnu-attributes
     attribute-specifier
*/

स्थिर वृक्षः
c_parser_transaction_attributes (c_parser *parser)
{
  जइ (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    प्रत्यागम c_parser_gnu_attributes (parser);

  जइ (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    प्रत्यागम NULL_वृक्षः;
  प्रत्यागम c_parser_std_attribute_specifier (parser, सच्च);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

स्थिर वृक्षः
c_parser_transaction (c_parser *parser, गणना rid keyword)
{
  unsigned पूर्णाङ्क old_in = parser->in_transaction;
  unsigned पूर्णाङ्क this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  जइ (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  अण्णहा
    {
      attrs = c_parser_transaction_attributes (parser);
      जइ (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  जइ (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  अण्णहा
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  प्रत्यागम stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

स्थिर संरचना c_व्यञ्जकम्
c_parser_transaction_expression (c_parser *parser, गणना rid keyword)
{
  संरचना c_व्यञ्जकम् ret;
  unsigned पूर्णाङ्क old_in = parser->in_transaction;
  unsigned पूर्णाङ्क this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  जइ (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  अण्णहा
    {
      attrs = c_parser_transaction_attributes (parser);
      जइ (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  जइ (parens.require_open (parser))
    {
      वृक्षः व्यञ्जकम् = c_parser_expression (parser).मानम्;
      ret.original_type = वृक्षः_TYPE (व्यञ्जकम्);
      ret.मानम् = build1 (TRANSACTION_व्यञ्जकम्, ret.original_type, व्यञ्जकम्);
      जइ (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_व्यञ्जकम्_RELAXED (ret.मानम्) = 1;
      SET_व्यञ्जकम्_LOCATION (ret.मानम्, loc);
      ret.original_code = TRANSACTION_व्यञ्जकम्;
      ret.m_decimal = 0;
      जइ (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  गच्छ error;
	}
    }
  अण्णहा
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
    }
  parser->in_transaction = old_in;

  जइ (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_व्यञ्जकम्_source_range (&ret, loc, loc);

  प्रत्यागम ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

स्थिर वृक्षः
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्षः attrs;
  तार्किक is_outer = मिच्छ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  जइ (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  जइ (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      गच्छ ret_error;
    }
  अण्णहा जइ (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      गच्छ ret_error;
    }
  अण्णहा जइ (is_outer)
    {
      जइ ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  गच्छ ret_error;
	}
    }
  अण्णहा जइ (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      गच्छ ret_error;
    }

  प्रत्यागम add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  प्रत्यागम build1 (NOP_व्यञ्जकम्, void_type_ग्रन्थिः, error_mark_ग्रन्थिः);
}

/* Parse a single source file.  */

शून्य
c_parse_file (शून्य)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, परिमाण tparser);
  tparser.translate_strings_p = सच्च;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  जइ (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  अण्णहा
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  जइ (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  जइ (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = रिक्त;
}

शून्य
c_init_preprocess (शून्य)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, परिमाण (c_parser));
  the_parser->tokens = &the_parser->tokens_buf[0];
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
c_parser_parse_rtl_body (c_parser *parser, वर्ण *start_with_pass)
{
  जइ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      मुक्त (start_with_pass);
      प्रत्यागम c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  पूर्णाङ्क अङ्कः_open_braces = 1;
  जाव (1)
    {
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_OPEN_BRACE:
	  अङ्कः_open_braces++;
	  भङ्ग;
	पक्ष CPP_CLOSE_BRACE:
	  जइ (--अङ्कः_open_braces == 0)
	    गच्छ found_closing_brace;
	  भङ्ग;
	पक्ष CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  मुक्त (start_with_pass);
	  प्रत्यागम c_parser_peek_token (parser)->location;
	स्वभाव:
	  भङ्ग;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  जइ (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      मुक्त (start_with_pass);
      प्रत्यागम end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  प्रत्यागम end_loc;
}

#अन्तर्भाव "gt-c-c-parser.h"
