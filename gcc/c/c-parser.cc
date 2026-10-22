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

vec<रूख> incomplete_record_decls;

शून्य
set_c_अभिव्यक्ति_source_range (c_अभिव्यक्ति *अभिव्यक्ति,
			 location_t start, location_t finish)
{
  अभिव्यक्ति->src_range.m_start = start;
  अभिव्यक्ति->src_range.m_finish = finish;
  यदि (अभिव्यक्ति->मान)
    set_source_range (अभिव्यक्ति->मान, start, finish);
}

शून्य
set_c_अभिव्यक्ति_source_range (c_अभिव्यक्ति *अभिव्यक्ति,
			 source_range src_range)
{
  अभिव्यक्ति->src_range = src_range;
  यदि (अभिव्यक्ति->मान)
    set_source_range (अभिव्यक्ति->मान, src_range);
}


/* Initialization routine for this file.  */

शून्य
c_parse_init (शून्य)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  अचिन्हित पूर्णाङ्क i;
  रूख id;
  पूर्णाङ्क mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  यदि (!flag_isoc99)
    mask |= D_C99;
  यदि (!flag_isoc23)
    mask |= D_C23;
  यदि (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      यदि (!flag_isoc99)
	mask |= D_EXT89;
      यदि (!flag_isoc23)
	mask |= D_EXT11;
    }
  यदि (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<रूख> ((पूर्णाङ्क) RID_MAX);
  लागि (i = 0; i < अङ्क_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      यदि (c_common_reswords[i].disable & mask)
	{
	  यदि (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  जारी;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(पूर्णाङ्क) c_common_reswords[i].rid] = id;
    }

  लागि (i = 0; i < अङ्क_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      वर्ण name[50];
      प्र_लिखो (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      प्र_लिखो (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  यदि (flag_openmp)
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
  अचिन्हित पूर्णाङ्क tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  अचिन्हित पूर्णाङ्क raw_tokens_used;
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
  अचिन्हित पूर्णाङ्क in_transaction : 4;
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
  रूख in_omp_decl_attribute;

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
  अचिन्हित पूर्णाङ्क save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
संरचना GTY(()) omp_begin_declare_variant_map_entry {
  रूख variant;		/* The variant decl.  */
  रूख id;		/* Name of base function.  */
  रूख ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

स्थिर रूख omp_start_variant_function (c_declarator *, रूख);
स्थिर शून्य omp_finish_variant_function (रूख, रूख, रूख);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, अचिन्हित n)
{
  फर्काऊ &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

तार्किक
c_parser_error (c_parser *parser)
{
  फर्काऊ parser->error;
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
c_lex_one_token (c_parser *parser, c_token *token, तार्किक raw = असत्य)
{
  timevar_थप (TV_LEX);

  यदि (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->मान, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  अन्यथा
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      यदि (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  यदि (raw)
    गच्छ out;

  विकल्प (token->type)
    {
    पक्ष CPP_NAME:
      {
	रूख decl;

	तार्किक objc_force_identifier = parser->objc_need_raw_identifier;
	यदि (c_dialect_objc ())
	  parser->objc_need_raw_identifier = असत्य;

	यदि (C_IS_RESERVED_WORD (token->मान))
	  {
	    गणना rid rid_code = C_RID_CODE (token->मान);

	    यदि (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->मान);
	      }
	    अन्यथा यदि (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		रोक;
	      }
	    अन्यथा यदि (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		यदि (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    रोक;
		  }
		अन्यथा यदि (parser->objc_could_be_foreach_context
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
		    रोक;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    अन्यथा यदि (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		यदि (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    रोक;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    अन्यथा यदि (c_dialect_objc ()
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
	    अन्यथा
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		रोक;
	      }
	  }

	decl = lookup_name (token->मान);
	यदि (decl)
	  {
	    यदि (रूख_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		रोक;
	      }
	  }
	अन्यथा यदि (c_dialect_objc ())
	  {
	    रूख objc_interface_decl = objc_is_class_name (token->मान);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    यदि (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->मान = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		रोक;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      रोक;
    पक्ष CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      विकल्प (C_RID_CODE (token->मान))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	पक्ष RID_CLASS:     token->keyword = RID_AT_CLASS; रोक;
	पक्ष RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; रोक;
	पक्ष RID_PROTECTED: token->keyword = RID_AT_PROTECTED; रोक;
	पक्ष RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; रोक;
	पक्ष RID_THROW:     token->keyword = RID_AT_THROW; रोक;
	पक्ष RID_TRY:       token->keyword = RID_AT_TRY; रोक;
	पक्ष RID_CATCH:     token->keyword = RID_AT_CATCH; रोक;
	पक्ष RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; रोक;
	स्वभाव:            token->keyword = C_RID_CODE (token->मान);
	}
      रोक;
    पक्ष CPP_COLON:
    पक्ष CPP_COMMA:
    पक्ष CPP_CLOSE_PAREN:
    पक्ष CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      यदि (c_dialect_objc ())
	parser->objc_need_raw_identifier = असत्य;
      रोक;
    पक्ष CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (गणना pragma_kind) रूख_INT_CST_तल्लो (token->मान);
      token->मान = रिक्त;
      रोक;
    स्वभाव:
      रोक;
    }
 out:
  timevar_झिक (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  यदि (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  फर्काऊ &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  यदि (parser->tokens_avail >= 2)
    फर्काऊ &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  फर्काऊ &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, अचिन्हित पूर्णाङ्क n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  यदि (parser->tokens_avail >= n)
    फर्काऊ &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  फर्काऊ &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, अचिन्हित पूर्णाङ्क n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  यदि (parser->tokens_avail >= n)
    फर्काऊ &parser->tokens[n - 1];
  अचिन्हित पूर्णाङ्क raw_len = vec_safe_length (parser->raw_tokens);
  अचिन्हित पूर्णाङ्क raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  यदि (raw_avail >= n)
    फर्काऊ &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], सत्य);
  फर्काऊ &(*parser->raw_tokens)[raw_len];
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
      फर्काऊ सत्य;
    स्वभाव:
      यदि (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + अङ्क_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	फर्काऊ सत्य;
      फर्काऊ असत्य;
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
	  फर्काऊ असत्य;
	पक्ष C_ID_ADDRSPACE:
	  फर्काऊ सत्य;
	पक्ष C_ID_TYPENAME:
	  फर्काऊ सत्य;
	पक्ष C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  फर्काऊ सत्य;
	स्वभाव:
	  gcc_unreachable ();
	}
    पक्ष CPP_KEYWORD:
      फर्काऊ c_keyword_starts_typename (token->keyword);
    पक्ष CPP_LESS:
      यदि (c_dialect_objc ())
	फर्काऊ सत्य;
      फर्काऊ असत्य;
    स्वभाव:
      फर्काऊ असत्य;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

स्थिर अन्तःस्थ तार्किक
c_parser_next_tokens_start_typename (c_parser *parser, गणना c_lookahead_kind la,
				     अचिन्हित पूर्णाङ्क n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  यदि (c_token_starts_typename (token))
    फर्काऊ सत्य;

  /* Try a bit harder to detect an unknown typename.  */
  यदि (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->मान))
    फर्काऊ सत्य;

  फर्काऊ असत्य;
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
	  फर्काऊ सत्य;
	स्वभाव:
	  रोक;
	}
      /* Fall through.  */
    स्वभाव:
      फर्काऊ c_token_starts_typename (token);
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
	  फर्काऊ सत्य;
	स्वभाव:
	  फर्काऊ असत्य;
	}
    पक्ष CPP_KEYWORD:
      विकल्प (token->keyword)
	{
	पक्ष RID_CONST:
	पक्ष RID_VOLATILE:
	पक्ष RID_RESTRICT:
	पक्ष RID_ATTRIBUTE:
	पक्ष RID_ATOMIC:
	  फर्काऊ सत्य;
	स्वभाव:
	  फर्काऊ असत्य;
	}
    पक्ष CPP_LESS:
      फर्काऊ असत्य;
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
  फर्काऊ c_token_is_qualifier (token);
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
	  फर्काऊ असत्य;
	पक्ष C_ID_ADDRSPACE:
	  फर्काऊ सत्य;
	पक्ष C_ID_TYPENAME:
	  फर्काऊ सत्य;
	पक्ष C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  फर्काऊ सत्य;
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
	  फर्काऊ सत्य;
	स्वभाव:
	  यदि (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + अङ्क_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    फर्काऊ सत्य;
	  फर्काऊ असत्य;
	}
    पक्ष CPP_LESS:
      यदि (c_dialect_objc ())
	फर्काऊ सत्य;
      फर्काऊ असत्य;
    स्वभाव:
      फर्काऊ असत्य;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
स्थिर तार्किक
c_token_starts_declaration (c_token *token)
{
  यदि (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    फर्काऊ सत्य;
  अन्यथा
    फर्काऊ असत्य;
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
  यदि (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    फर्काऊ असत्य;

  फर्काऊ c_token_starts_declspecs (token);
}

स्थिर तार्किक c_parser_check_balanced_raw_token_sequence (c_parser *,
							अचिन्हित पूर्णाङ्क *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
तार्किक
c_parser_next_tokens_start_declaration (c_parser *parser, अचिन्हित पूर्णाङ्क n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  यदि (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    फर्काऊ असत्य;

  /* Labels do not start declarations.  */
  यदि (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    फर्काऊ असत्य;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  यदि (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      यदि (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	फर्काऊ सत्य;
      फर्काऊ c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  यदि (c_token_starts_declaration (token))
    फर्काऊ सत्य;

  यदि (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    फर्काऊ सत्य;

  फर्काऊ असत्य;
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
  यदि (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  अन्यथा यदि (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      यदि (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          यदि (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = असत्य;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

स्थिर शून्य
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  यदि (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  अन्यथा यदि (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      यदि (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = सत्य;
}

/* Update the global input_location from TOKEN.  */
स्थिर अन्तःस्थ शून्य
c_parser_set_source_position_from_token (c_token *token)
{
  यदि (token->type != CPP_EOF)
    {
      आगत_location = token->location;
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
  यदि (token2->type != tok1_kind)
    फर्काऊ असत्य;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  यदि (token3->type != tok1_kind)
    फर्काऊ असत्य;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  यदि (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    फर्काऊ असत्य;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  यदि (LOCATION_COLUMN (start_loc) != 1)
    फर्काऊ असत्य;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  फर्काऊ सत्य;
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
c_parser_error_richloc (c_parser *parser, अचर वर्ण *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  यदि (parser->error)
    फर्काऊ असत्य;
  parser->error = सत्य;
  यदि (!gmsgid)
    फर्काऊ असत्य;

  /* If this is actually a conflict marker, report it as such.  */
  यदि (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      यदि (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  फर्काऊ सत्य;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  यदि (parser->seen_string_literal && token->type == CPP_NAME)
    {
      रूख name = token->मान;
      अचर वर्ण *token_name = IDENTIFIER_POINTER (name);
      अचर वर्ण *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      यदि (header_hint != रिक्त)
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
		 token->मान, /*flags=*/0, richloc);
  फर्काऊ सत्य;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

तार्किक
c_parser_error (c_parser *parser, अचर वर्ण *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (पङ्क्ति_table, आगत_location);
  फर्काऊ c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

ढाँचा <typename traits_t>
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
    यदि (token)
      m_open_loc = token->location;

    फर्काऊ c_parser_require (parser, traits_t::open_token_type,
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

  तार्किक require_close (c_parser *parser) अचर
  {
    फर्काऊ c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  शून्य skip_until_found_close (c_parser *parser) अचर
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
  स्थिर अचर गणना cpp_ttype open_token_type = CPP_OPEN_PAREN;
  स्थिर अचर वर्ण * अचर open_gmsgid;
  स्थिर अचर गणना cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  स्थिर अचर वर्ण * अचर close_gmsgid;
};

अचर वर्ण * अचर matching_paren_traits::open_gmsgid = "expected %<(%>";
अचर वर्ण * अचर matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

प्रकारनिर्देश token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

संरचना matching_brace_traits
{
  स्थिर अचर गणना cpp_ttype open_token_type = CPP_OPEN_BRACE;
  स्थिर अचर वर्ण * अचर open_gmsgid;
  स्थिर अचर गणना cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  स्थिर अचर वर्ण * अचर close_gmsgid;
};

अचर वर्ण * अचर matching_brace_traits::open_gmsgid = "expected %<{%>";
अचर वर्ण * अचर matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

प्रकारनिर्देश token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

स्थिर अचर वर्ण *
get_matching_चिह्न (गणना cpp_ttype type)
{
  विकल्प (type)
    {
    स्वभाव:
      gcc_unreachable ();
    पक्ष CPP_CLOSE_PAREN:
      फर्काऊ "(";
    पक्ष CPP_CLOSE_BRACE:
      फर्काऊ "{";
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
		  अचर वर्ण *msgid,
		  location_t matching_location,
		  तार्किक type_is_unique)
{
  यदि (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      फर्काऊ सत्य;
    }
  अन्यथा
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      यदि (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      तार्किक added_matching_location = असत्य;
      यदि (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      यदि (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	यदि (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_चिह्न (type));

      फर्काऊ असत्य;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

स्थिर तार्किक
c_parser_require_keyword (c_parser *parser,
			  गणना rid keyword,
			  अचर वर्ण *msgid)
{
  यदि (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      फर्काऊ सत्य;
    }
  अन्यथा
    {
      c_parser_error (parser, msgid);
      फर्काऊ असत्य;
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
			   अचर वर्ण *msgid,
			   location_t matching_location)
{
  अचिन्हित nesting_depth = 0;

  यदि (c_parser_require (parser, type, msgid, matching_location))
    {
      यदि (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  यदि (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = रिक्त;
	    }
	}
      फर्काऊ;
    }

  /* Skip tokens until the desired token is found.  */
  जबसम्म (सत्य)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      यदि (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  यदि (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      यदि (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = रिक्त;
		}
	    }
	  रोक;
	}

      /* If we've run out of tokens, stop.  */
      यदि (token->type == CPP_EOF)
	फर्काऊ;
      यदि (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	फर्काऊ;
      यदि (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      अन्यथा यदि (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  यदि (nesting_depth-- == 0)
	    रोक;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = असत्य;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

स्थिर शून्य
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  अचिन्हित nesting_depth = 0;

  जबसम्म (सत्य)
    {
      c_token *token = c_parser_peek_token (parser);
      यदि ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	रोक;
      /* If we've run out of tokens, stop.  */
      यदि (token->type == CPP_EOF)
	फर्काऊ;
      यदि (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	फर्काऊ;
      यदि (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      अन्यथा यदि (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  यदि (nesting_depth-- == 0)
	    रोक;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = असत्य;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

स्थिर तार्किक
c_parser_skip_to_closing_brace (c_parser *parser)
{
  अचिन्हित nesting_depth = 0;

  जबसम्म (सत्य)
    {
      c_token *token = c_parser_peek_token (parser);

      विकल्प (token->type)
	{
	पक्ष CPP_PRAGMA_EOL:
	  यदि (!parser->in_pragma)
	    रोक;
	  /* FALLTHRU */
	पक्ष CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  फर्काऊ असत्य;

	पक्ष CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  यदि (nesting_depth-- == 0)
	    फर्काऊ सत्य;
	  रोक;

	पक्ष CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  रोक;

	स्वभाव:
	  रोक;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

स्थिर शून्य
c_parser_skip_to_pragma_eol (c_parser *parser, तार्किक error_if_not_eol = सत्य)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = असत्य;

  यदि (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  गर
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      यदि (token_type == CPP_EOF)
	रोक;
      c_parser_consume_token (parser);
    }
  जबसम्म (token_type != CPP_PRAGMA_EOL);

  यदि (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      यदि (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = रिक्त;
	}
    }

  parser->error = असत्य;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
स्थिर शून्य
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  लागि (पूर्णाङ्क depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      विकल्प (token->type)
	{
	पक्ष CPP_PRAGMA_EOL:
	  यदि (!parser->in_pragma)
	    रोक;
	  /* FALLTHRU */
	पक्ष CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  फर्काऊ;

	पक्ष CPP_PRAGMA:
	  यदि ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      रूख id1 = c_parser_peek_nth_token (parser, 2)->मान;
	      रूख id2 = c_parser_peek_nth_token (parser, 3)->मान;
	      यदि (म_भेद (IDENTIFIER_POINTER (id1), "declare") == 0
		  && म_भेद (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  यदि (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  अन्यथा
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  जारी;

	स्वभाव:
	  रोक;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

स्थिर शून्य
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    तार्किक metadirective_p = असत्य)
{
  अचिन्हित nesting_depth = 0;
  पूर्णाङ्क bracket_depth = 0;
  तार्किक save_error = parser->error;

  जबसम्म (सत्य)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      विकल्प (token->type)
	{
	पक्ष CPP_EOF:
	  फर्काऊ;

	पक्ष CPP_PRAGMA_EOL:
	  यदि (parser->in_pragma)
	    फर्काऊ;
	  रोक;

	पक्ष CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  यदि (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      गच्छ finished;
	    }
	  रोक;

	पक्ष CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  यदि ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      गच्छ finished;
	    }
	  रोक;

	पक्ष CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  रोक;

	पक्ष CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  यदि (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  रोक;

	पक्ष CPP_CLOSE_PAREN:
	  यदि (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  रोक;

	पक्ष CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  parser->error = save_error;
	  जारी;

	स्वभाव:
	  रोक;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = असत्य;
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
  फर्काऊ ret;
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
  रूख clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
स्थिर रूख objc_foreach_break_label, objc_foreach_continue_label;

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
  गणना रूख_code code;
  रूख declv, condv, incrv, initv;
  रूख pre_body;
  रूख bindings;
  पूर्णाङ्क गन्ती;	/* Expected nesting depth.  */
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

  शून्य reset () { musttail_p = असत्य; }
};

स्थिर तार्किक c_parser_nth_token_starts_std_attributes (c_parser *,
						      अचिन्हित पूर्णाङ्क);
स्थिर रूख c_parser_std_attribute_specifier_sequence (c_parser *);
स्थिर शून्य c_parser_external_declaration (c_parser *);
स्थिर शून्य c_parser_asm_definition (c_parser *);
स्थिर रूख c_parser_declaration_or_fndef (c_parser *, तार्किक, तार्किक, तार्किक,
					   तार्किक, तार्किक, तार्किक, रूख * = रिक्त,
					   vec<c_token> * = रिक्त,
					   तार्किक have_attrs = असत्य,
					   रूख attrs = रिक्त,
					   संरचना oacc_routine_data * = रिक्त,
					   तार्किक * = रिक्त);
स्थिर तार्किक c_parser_handle_statement_omp_attributes (c_parser *, रूख &,
						      तार्किक *);
स्थिर शून्य c_parser_static_assert_declaration_no_semi (c_parser *);
स्थिर शून्य c_parser_static_assert_declaration (c_parser *);
स्थिर संरचना c_typespec c_parser_enum_specifier (c_parser *);
स्थिर संरचना c_typespec c_parser_struct_or_union_specifier (c_parser *);
स्थिर रूख c_parser_struct_declaration (c_parser *, रूख *);
स्थिर संरचना c_typespec c_parser_typeof_specifier (c_parser *);
स्थिर रूख c_parser_alignas_specifier (c_parser *);
स्थिर संरचना c_declarator *c_parser_direct_declarator (c_parser *, तार्किक,
							c_dtr_syn, तार्किक *);
स्थिर संरचना c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      तार्किक,
							      संरचना c_declarator *);
स्थिर संरचना c_arg_info *c_parser_parms_declarator (c_parser *, तार्किक, रूख,
						     तार्किक);
स्थिर संरचना c_arg_info *c_parser_parms_list_declarator (c_parser *, रूख,
							  रूख, तार्किक);
स्थिर संरचना c_parm *c_parser_parameter_declaration (c_parser *, रूख, तार्किक);
स्थिर रूख c_parser_asm_string_literal (c_parser *);
स्थिर रूख c_parser_simple_asm_अभिव्यक्ति (c_parser *);
स्थिर रूख c_parser_gnu_attributes (c_parser *);
स्थिर संरचना c_अभिव्यक्ति c_parser_initializer (c_parser *, रूख);
स्थिर संरचना c_अभिव्यक्ति c_parser_braced_init (c_parser *, रूख, तार्किक,
					   संरचना obstack *, तार्किक);
स्थिर शून्य c_parser_initelt (c_parser *, संरचना obstack *);
स्थिर शून्य c_parser_initval (c_parser *, संरचना c_अभिव्यक्ति *,
			      संरचना obstack *);
स्थिर रूख c_parser_compound_statement (c_parser *, location_t * = रिक्त);
स्थिर location_t c_parser_compound_statement_nostart (c_parser *);
स्थिर शून्य c_parser_label (c_parser *, रूख);
स्थिर शून्य c_parser_statement (c_parser *, तार्किक *, location_t * = रिक्त);
स्थिर शून्य c_parser_statement_after_labels (c_parser *, तार्किक *, रूख,
					     vec<रूख> * = रिक्त,
					     attr_state = {});
स्थिर रूख c_parser_c99_block_statement (c_parser *, तार्किक *,
					  location_t * = रिक्त);
स्थिर शून्य c_parser_if_statement (c_parser *, तार्किक *, vec<रूख> *);
स्थिर शून्य c_parser_switch_statement (c_parser *, तार्किक *, रूख);
स्थिर शून्य c_parser_while_statement (c_parser *, तार्किक, अचिन्हित लघु, तार्किक,
				      तार्किक *, रूख);
स्थिर शून्य c_parser_do_statement (c_parser *, तार्किक, अचिन्हित लघु, तार्किक,
				   रूख);
स्थिर शून्य c_parser_for_statement (c_parser *, तार्किक, अचिन्हित लघु, तार्किक,
				    तार्किक *, रूख);
स्थिर रूख c_parser_asm_statement (c_parser *);
स्थिर रूख c_parser_asm_operands (c_parser *);
स्थिर रूख c_parser_asm_goto_operands (c_parser *);
स्थिर रूख c_parser_asm_clobbers (c_parser *);
स्थिर संरचना c_अभिव्यक्ति c_parser_अभिव्यक्ति_no_commas (c_parser *, संरचना c_अभिव्यक्ति *,
					      रूख = NULL_रूख);
स्थिर संरचना c_अभिव्यक्ति c_parser_conditional_expression (c_parser *,
						      संरचना c_अभिव्यक्ति *, रूख);
स्थिर संरचना c_अभिव्यक्ति c_parser_द्विआधारी_expression (c_parser *, संरचना c_अभिव्यक्ति *,
						 रूख);
स्थिर संरचना c_अभिव्यक्ति c_parser_cast_expression (c_parser *, संरचना c_अभिव्यक्ति *);
स्थिर संरचना c_अभिव्यक्ति c_parser_unary_expression (c_parser *);
स्थिर संरचना c_अभिव्यक्ति c_parser_sizeof_or_countof_expression (c_parser *,
							    गणना rid);
स्थिर संरचना c_अभिव्यक्ति c_parser_alignof_expression (c_parser *);
स्थिर संरचना c_अभिव्यक्ति c_parser_maxof_or_minof_expression (c_parser *, गणना rid);
स्थिर संरचना c_अभिव्यक्ति c_parser_postfix_expression (c_parser *);
स्थिर संरचना c_अभिव्यक्ति c_parser_postfix_expression_after_paren_type (c_parser *,
								   संरचना c_declspecs *,
								   संरचना c_type_name *,
								   location_t);
स्थिर संरचना c_अभिव्यक्ति c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								संरचना c_अभिव्यक्ति);
स्थिर रूख c_parser_transaction (c_parser *, गणना rid);
स्थिर संरचना c_अभिव्यक्ति c_parser_transaction_expression (c_parser *, गणना rid);
स्थिर रूख c_parser_transaction_cancel (c_parser *);
स्थिर संरचना c_अभिव्यक्ति c_parser_expression (c_parser *);
स्थिर संरचना c_अभिव्यक्ति c_parser_expression_conv (c_parser *);
स्थिर vec<रूख, va_gc> *c_parser_अभिव्यक्ति_list (c_parser *, तार्किक, तार्किक,
					     vec<रूख, va_gc> **, location_t *,
					     रूख *, vec<location_t> *,
					     अचिन्हित पूर्णाङ्क * = रिक्त);
स्थिर संरचना c_अभिव्यक्ति c_parser_has_attribute_expression (c_parser *);

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
							गणना रूख_code, तार्किक);
स्थिर रूख c_parser_omp_loop_nest (c_parser *, तार्किक *);
स्थिर रूख c_parser_omp_for_loop (location_t, c_parser *, गणना रूख_code,
				   रूख, रूख *, तार्किक *);
स्थिर शून्य c_parser_omp_taskwait (c_parser *);
स्थिर शून्य c_parser_omp_taskyield (c_parser *);
स्थिर शून्य c_parser_omp_cancel (c_parser *);
स्थिर शून्य c_parser_omp_nothing (c_parser *);
स्थिर शून्य c_parser_omp_metadirective (c_parser *, तार्किक *);

गणना pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
स्थिर तार्किक c_parser_pragma (c_parser *, गणना pragma_context, तार्किक *, रूख);
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
स्थिर रूख c_parser_omp_dispatch (location_t, c_parser *);
स्थिर शून्य c_parser_omp_interop (c_parser *);
स्थिर शून्य c_parser_oacc_routine (c_parser *, गणना pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
स्थिर शून्य c_parser_objc_class_definition (c_parser *, रूख);
स्थिर शून्य c_parser_objc_class_instance_variables (c_parser *);
स्थिर शून्य c_parser_objc_class_declaration (c_parser *);
स्थिर शून्य c_parser_objc_alias_declaration (c_parser *);
स्थिर शून्य c_parser_objc_protocol_definition (c_parser *, रूख);
स्थिर तार्किक c_parser_objc_method_type (c_parser *);
स्थिर शून्य c_parser_objc_method_definition (c_parser *);
स्थिर शून्य c_parser_objc_methodprotolist (c_parser *);
स्थिर शून्य c_parser_objc_methodproto (c_parser *);
स्थिर रूख c_parser_objc_method_decl (c_parser *, तार्किक, रूख *, रूख *);
स्थिर रूख c_parser_objc_type_name (c_parser *);
स्थिर रूख c_parser_objc_protocol_refs (c_parser *);
स्थिर शून्य c_parser_objc_try_catch_finally_statement (c_parser *);
स्थिर शून्य c_parser_objc_synchronized_statement (c_parser *);
स्थिर रूख c_parser_objc_selector (c_parser *);
स्थिर रूख c_parser_objc_selector_arg (c_parser *);
स्थिर रूख c_parser_objc_receiver (c_parser *);
स्थिर रूख c_parser_objc_message_args (c_parser *);
स्थिर रूख c_parser_objc_keywordexpr (c_parser *);
स्थिर शून्य c_parser_objc_at_property_declaration (c_parser *);
स्थिर शून्य c_parser_objc_at_synthesize_declaration (c_parser *);
स्थिर शून्य c_parser_objc_at_dynamic_declaration (c_parser *);
स्थिर तार्किक c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, संरचना c_declspecs *);
स्थिर location_t c_parser_parse_rtl_body (c_parser *, वर्ण *);
स्थिर रूख c_parser_handle_musttail (c_parser *, रूख, attr_state &);

#यदि ENABLE_ANALYZER

नामाकाश ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

वर्ग c_translation_unit : सार्वजनिक translation_unit
{
सार्वजनिक:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  रूख lookup_constant_by_id (रूख id) अचर final override
  {
    /* Consider decls.  */
    यदि (रूख decl = lookup_name (id))
      यदि (रूख_CODE (decl) == CONST_DECL)
	यदि (रूख मान = DECL_INITIAL (decl))
	  यदि (रूख_CODE (मान) == INTEGER_CST)
	    फर्काऊ मान;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    यदि (cpp_macro_p (hashnode))
      यदि (रूख मान = consider_macro (hashnode->मान.macro))
	फर्काऊ मान;

    फर्काऊ NULL_रूख;
  }

  रूख
  lookup_type_by_id (रूख id) अचर final override
  {
    यदि (रूख type_decl = lookup_name (id))
	यदि (रूख_CODE (type_decl) == TYPE_DECL)
	  {
	    रूख record_type = रूख_TYPE (type_decl);
	    यदि (रूख_CODE (record_type) == RECORD_TYPE)
	      फर्काऊ record_type;
	  }

    फर्काऊ NULL_रूख;
  }

  रूख
  lookup_global_var_by_id (रूख id) अचर final override
  {
    यदि (रूख var_decl = lookup_name (id))
      यदि (रूख_CODE (var_decl) == VAR_DECL)
				फर्काऊ var_decl;

    फर्काऊ NULL_रूख;
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
  रूख consider_macro (cpp_macro *macro, पूर्णाङ्क depth = 0) अचर
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    यदि (macro->paramc > 0)
      फर्काऊ NULL_रूख;
    यदि (macro->kind != cmk_macro)
      फर्काऊ NULL_रूख;
    यदि (macro->गन्ती != 1)
      फर्काऊ NULL_रूख;
    अचर cpp_token &tok = macro->exp.tokens[0];
    यदि (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	यदि (depth >= param_analyzer_max_macro_alias_depth)
	  फर्काऊ NULL_रूख;

	cpp_hashnode *alias = tok.val.गाँठो.गाँठो;
	यदि (cpp_macro_p (alias))
	  फर्काऊ consider_macro (alias->मान.macro, depth + 1);

	/* Not a simple alias.  */
	फर्काऊ NULL_रूख;
      }
    अन्यथा यदि (tok.type != CPP_सङ्ख्या)
      फर्काऊ NULL_रूख;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, रिक्त, पङ्क्ति_table);

    pretty_printer pp;
    pp_string (&pp, (अचर वर्ण *) tok.val.str.text);
    pp_newline (&pp);
    cpp_थप_buffer (parse_in,
		     (अचर अचिन्हित वर्ण *) pp_formatted_text (&pp),
		     म_माप (pp_formatted_text (&pp)),
		     0);

    रूख मान;
    location_t loc;
    अचिन्हित वर्ण cpp_flags;
    c_lex_with_flags (&मान, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    यदि (मान && रूख_CODE (मान) == INTEGER_CST)
      फर्काऊ मान;

    फर्काऊ NULL_रूख;
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
  यदि (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  अन्यथा
    {
      शून्य *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (असत्य);
      गर
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      जबसम्म (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  अचिन्हित पूर्णाङ्क i;
  रूख decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    यदि (DECL_SIZE (decl) == NULL_रूख && रूख_TYPE (decl) != error_mark_गाँठो)
      error ("storage size of %q+D isn%'t known", decl);

  यदि (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->झिक ();
      यदि (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  यदि (vec_safe_length (current_omp_begin_assumes))
    {
      यदि (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  यदि (vec_safe_length (current_omp_declare_variant_attribute))
    {
      यदि (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  यदि (vec_safe_length (omp_begin_declare_variant_map))
    {
      अचिन्हित पूर्णाङ्क i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#यदि ENABLE_ANALYZER
  यदि (flag_analyzer)
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
	  रोक;
	पक्ष RID_ASM:
	  c_parser_asm_definition (parser);
	  रोक;
	पक्ष RID_AT_INTERFACE:
	पक्ष RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_रूख);
	  रोक;
	पक्ष RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  रोक;
	पक्ष RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  रोक;
	पक्ष RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_रूख);
	  रोक;
	पक्ष RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  रोक;
	पक्ष RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  रोक;
	पक्ष RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  रोक;
	पक्ष RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  रोक;
	स्वभाव:
	  गच्छ decl_or_fndef;
	}
      रोक;
    पक्ष CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      रोक;
    पक्ष CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (सत्य);
      c_parser_pragma (parser, pragma_external, रिक्त, NULL_रूख);
      mark_valid_location_for_stdc_pragma (असत्य);
      रोक;
    पक्ष CPP_PLUS:
    पक्ष CPP_MINUS:
      यदि (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  रोक;
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
      c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, असत्य, सत्य,
				     असत्य);
      रोक;
    }
}

स्थिर शून्य c_parser_handle_directive_omp_attributes (रूख &, vec<c_token> *&,
						      vec<c_token> *);
स्थिर शून्य c_finish_omp_declare_simd (c_parser *, रूख, रूख, vec<c_token> *);
स्थिर शून्य c_finish_oacc_routine (संरचना oacc_routine_data *, रूख, तार्किक);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

स्थिर शून्य
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  यदि (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    फर्काऊ;

  रूख stmt = build0 (DEBUG_BEGIN_STMT, void_type_गाँठो);
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

स्थिर रूख
handle_assume_attribute (location_t here, रूख attrs, तार्किक nested)
{
  यदि (nested)
    लागि (रूख attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", रूख_CHAIN (attr)))
      {
	रूख args = रूख_मान (attr);
	पूर्णाङ्क nargs = list_length (args);
	यदि (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	अन्यथा
	  {
	    रूख arg = रूख_मान (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, असत्य, रिक्त);
	    यदि (arg != error_mark_गाँठो)
	      {
		रूख fn = build_call_अभिव्यक्ति_internal_loc (here, IFN_ASSUME,
							void_type_गाँठो, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  अन्यथा
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  फर्काऊ remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

स्थिर शून्य
c_parser_maybe_reclassify_token (c_parser *parser)
{
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      यदि (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  रूख decl = lookup_name (token->मान);

	  token->id_kind = C_ID_ID;
	  यदि (decl)
	    {
	      यदि (रूख_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  अन्यथा यदि (c_dialect_objc ())
	    {
	      रूख objc_interface_decl = objc_is_class_name (token->मान);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      यदि (objc_interface_decl)
		{
		  token->मान = objc_interface_decl;
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

स्थिर रूख
c_parser_declaration_or_fndef (c_parser *parser, तार्किक fndef_ok,
			       तार्किक static_assert_ok, तार्किक empty_ok,
			       तार्किक nested, तार्किक start_attr_ok,
			       तार्किक simple_ok,
			       रूख *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       तार्किक have_attrs /* = false */,
			       रूख attrs /* = NULL_TREE */,
			       संरचना oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       तार्किक *fallthru_attr_p /* = NULL */)
{
  संरचना c_declspecs *specs;
  रूख prefix_attrs;
  रूख all_prefix_attrs;
  तार्किक diagnosed_no_specs = असत्य;
  location_t here = c_parser_peek_token (parser)->location;
  रूख result = NULL_रूख;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  यदि (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      फर्काऊ result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  यदि (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = असत्य;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  यदि (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->मान)))
    {
      रूख name = c_parser_peek_token (parser)->मान;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      यदि (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_घुसाउ_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      अन्यथा यदि (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_घुसाउ_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      अन्यथा यदि (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_घुसाउ_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      अन्यथा
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  यदि (अचर वर्ण *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  अन्यथा
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->मान = error_mark_गाँठो;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  यदि (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = सत्य;

  c_parser_declspecs (parser, specs, सत्य, सत्य, start_attr_ok,
		      सत्य, सत्य, start_attr_ok, सत्य, cla_nonabstract_decl);
  यदि (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      फर्काऊ result;
    }
  यदि (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      फर्काऊ result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  यदि (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_शीर्ष_anonymous_type (specs->type);

  तार्किक gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  तार्किक std_auto_type_p = specs->c23_auto_p;
  तार्किक any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  अचर वर्ण *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  यदि (specs->constexpr_p)
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
	  रोक;

	पक्ष ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  रोक;

	स्वभाव:
	  रोक;
	}
    }

  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      तार्किक handled_assume = असत्य;
      यदि (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       रिक्त))
	{
	  यदि (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  जबसम्म (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, रिक्त, NULL_रूख);
	    }
	  c_parser_consume_token (parser);
	  फर्काऊ result;
	}
      यदि (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = सत्य;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      यदि (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      अन्यथा यदि (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  यदि (fallthru_attr_p != रिक्त)
	    *fallthru_attr_p = सत्य;
	  यदि (nested)
	    {
	      रूख fn = build_call_अभिव्यक्ति_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_गाँठो, 0);
	      add_stmt (fn);
	    }
	  अन्यथा
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      अन्यथा यदि (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      अन्यथा
	{
	  shadow_tag_warned (specs, 1);
	  यदि (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      यदि (specs->अभिव्यक्ति)
	add_stmt (fold_convert (void_type_गाँठो, specs->अभिव्यक्ति));
      c_parser_consume_token (parser);
      यदि (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_रूख, असत्य);
      फर्काऊ result;
    }
  अन्यथा यदि (specs->typespec_kind == ctsk_none
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
      यदि (astate.musttail_p)
	{
	  यदि (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, रिक्त, NULL_रूख, रिक्त,
					   astate);
	  फर्काऊ result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  यदि (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = असत्य;
      shadow_tag_warned (specs, 1);
      फर्काऊ result;
    }
  अन्यथा यदि (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      विकल्प (c_parser_peek_token (parser)->type)
	{
	  पक्ष CPP_PLUS:
	  पक्ष CPP_MINUS:
	    यदि (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      फर्काऊ result;
	    यदि (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_रूख;
	      }
	    यदि (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    अन्यथा
	      c_parser_objc_methodproto (parser);
	    फर्काऊ result;
	    रोक;
	  स्वभाव:
	    रोक;
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
	    यदि (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      फर्काऊ result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    फर्काऊ result;
	  }
	  रोक;
	पक्ष RID_AT_IMPLEMENTATION:
	  {
	    यदि (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      फर्काऊ result;
	    यदि (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_रूख;
	      }
	    c_parser_objc_class_definition (parser, NULL_रूख);
	    फर्काऊ result;
	  }
	  रोक;
	पक्ष RID_AT_PROTOCOL:
	  {
	    यदि (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      फर्काऊ result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    फर्काऊ result;
	  }
	  रोक;
	पक्ष RID_AT_ALIAS:
	पक्ष RID_AT_CLASS:
	पक्ष RID_AT_END:
	पक्ष RID_AT_PROPERTY:
	  यदि (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = रिक्त;
	    }
	  रोक;
	स्वभाव:
	  रोक;
	}
    }
  अन्यथा यदि (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  अन्यथा यदि (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_रूख;
  तार्किक more_than_one_decl = असत्य;
  जबसम्म (सत्य)
    {
      संरचना c_declarator *declarator;
      तार्किक dummy = असत्य;
      timevar_id_t tv;
      रूख fnbody = NULL_रूख;
      रूख underspec_name = NULL_रूख;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      यदि (declarator == रिक्त)
	{
	  यदि (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_रूख, NULL_रूख,
				       omp_declare_simd_clauses);
	  यदि (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_रूख, असत्य);
	  /* This check is here purely to improve the diagnostic.  */
	  यदि (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  फर्काऊ result;
	}
      यदि (flag_openmp || flag_openmp_simd)
	{
	  संरचना c_declarator *d = declarator;
	  जबसम्म (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = रिक्त;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      यदि (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  फर्काऊ result;
	}
      यदि (std_auto_type_p)
	{
	  संरचना c_declarator *d = declarator;
	  जबसम्म (d->kind == cdk_attrs)
	    d = d->declarator;
	  यदि (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      फर्काऊ result;
	    }
	  underspec_name = d->u.id.id;
	}
      अन्यथा यदि (specs->constexpr_p)
	{
	  संरचना c_declarator *d = declarator;
	  जबसम्म (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      यदि (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  रूख asm_name = NULL_रूख;
	  रूख postfix_attrs = NULL_रूख;
	  यदि (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = सत्य;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = असत्य;
	  यदि (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_अभिव्यक्ति (parser);
	  यदि (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  फर्काऊ result;
		}
	    }
	  यदि (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      रूख d;
	      संरचना c_अभिव्यक्ति init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      यदि (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पङ्क्ति_table, init_loc);
		  अचिन्हित पूर्णाङ्क underspec_state = 0;
		  यदि (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_रूख, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  यदि (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
		  यदि (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  यदि (gnu_auto_type_p
		      && रूख_CODE (init.मान) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (रूख_OPERAND (init.मान, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, सत्य, सत्य,
						   सत्य);
		  रूख init_type = रूख_TYPE (init.मान);
		  तार्किक vm_type = c_type_variably_modified_p (init_type);
		  यदि (vm_type)
		    init.मान = save_अभिव्यक्ति (init.मान);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = सत्य;
		  specs->type = init_type;
		  यदि (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_रूख;
		    }
		  यदि (vm_type)
		    {
		      तार्किक maybe_const = सत्य;
		      रूख type_अभिव्यक्ति = c_fully_fold (init.मान, असत्य,
						     &maybe_const);
		      specs->अभिव्यक्ति_const_operands &= maybe_const;
		      यदि (specs->अभिव्यक्ति)
			specs->अभिव्यक्ति = build2 (COMPOUND_अभिव्यक्ति,
					      रूख_TYPE (type_अभिव्यक्ति),
					      specs->अभिव्यक्ति, type_अभिव्यक्ति);
		      अन्यथा
			specs->अभिव्यक्ति = type_अभिव्यक्ति;
		    }
		  d = start_decl (declarator, specs, सत्य,
				  chainon (postfix_attrs, all_prefix_attrs));
		  यदि (!d)
		    d = error_mark_गाँठो;
		  यदि (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_रूख,
					       omp_declare_simd_clauses);
		  यदि (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_रूख,
					       &omp_dsimd_idattr_clauses);
		}
	      अन्यथा
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पङ्क्ति_table, init_loc);
		  अचिन्हित पूर्णाङ्क underspec_state = 0;
		  यदि (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, सत्य,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  यदि (!d)
		    d = error_mark_गाँठो;
		  यदि (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_रूख,
					       omp_declare_simd_clauses);
		  यदि (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_रूख,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      रूख_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  यदि (रूख_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  यदि (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      यदि (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_रूख,
						   omp_declare_simd_clauses);
		  यदि (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_रूख,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      यदि (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, असत्य);
	      यदि (d != error_mark_गाँठो)
		{
		  maybe_warn_string_init (init_loc, रूख_TYPE (d), init);
		  finish_decl (d, init_loc, init.मान,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  अन्यथा
	    {
	      यदि (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  फर्काऊ result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      रूख attrs = chainon (postfix_attrs, all_prefix_attrs);
	      रूख d = start_decl (declarator, specs, असत्य, attrs, सत्य,
				   &lastloc);
	      यदि (d && रूख_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  अचर संरचना c_declarator *decl = declarator;
		  अचर संरचना c_declarator *last_non_id_attrs = रिक्त;

		  जबसम्म (decl)
		    विकल्प (decl->kind)
		      {
		      पक्ष cdk_array:
		      पक्ष cdk_function:
		      पक्ष cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			रोक;

		      पक्ष cdk_attrs:
			decl = decl->declarator;
			रोक;

		      पक्ष cdk_id:
			decl = 0;
			रोक;

		      स्वभाव:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  यदि (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      रूख parms = last_non_id_attrs->u.arg_info->parms;
		      यदि (DECL_ARGUMENTS (d) == NULL_रूख
			  && DECL_INITIAL (d) == NULL_रूख)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      यदि (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  रूख parms = NULL_रूख;
		  यदि (d && रूख_CODE (d) == FUNCTION_DECL)
		    {
		      संरचना c_declarator *ce = declarator;
		      जबसम्म (ce != रिक्त)
			यदि (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    रोक;
			  }
			अन्यथा
			  ce = ce->declarator;
		    }
		  यदि (parms)
		    temp_store_parm_decls (d, parms);
		  यदि (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  यदि (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  यदि (parms)
		    temp_झिक_parm_decls ();
		}
	      यदि (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, असत्य);
	      यदि (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_रूख,
			     NULL_रूख, asm_name);

	      यदि (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  यदि (d)
		    *objc_foreach_object_declaration = d;
		  अन्यथा
		    *objc_foreach_object_declaration = error_mark_गाँठो;
		}
	    }
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = सत्य;
	      यदि (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  फर्काऊ result;
		}
	      c_parser_consume_token (parser);
	      यदि (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      अन्यथा
		all_prefix_attrs = prefix_attrs;
	      जारी;
	    }
	  अन्यथा यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      यदि (!simple_ok)
		c_parser_consume_token (parser);
	      फर्काऊ result;
	    }
	  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      फर्काऊ result;
	    }
	  अन्यथा
	    {
	      यदि (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      अन्यथा यदि (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      फर्काऊ result;
	    }
	}
      अन्यथा यदि (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  फर्काऊ result;
	}
      अन्यथा यदि (!fndef_ok)
	{
	  यदि (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  अन्यथा
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  फर्काऊ result;
	}
      /* Function definition (nested or otherwise).  */
      यदि (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_थप_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      रूख dv_base = NULL_रूख;
      रूख dv_ctx = NULL_रूख;
      यदि (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      यदि (!start_function (specs, declarator, all_prefix_attrs))
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
	  यदि (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = असत्य;
	    }
	  अन्यथा
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  यदि (nested)
	    c_झिक_function_context ();
	  रोक;
	}

      यदि (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      अन्यथा
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
      जबसम्म (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, असत्य, असत्य, असत्य,
				       सत्य, असत्य, असत्य);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      यदि (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_रूख,
				   omp_declare_simd_clauses);
      यदि (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_रूख,
				   &omp_dsimd_idattr_clauses);
      यदि (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, सत्य);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      यदि (dv_base && current_function_decl != error_mark_गाँठो)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_थप (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      यदि (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  थप_scope ();
	  झिक_scope ();

	  finish_function (endloc);
	  फर्काऊ result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      अन्यथा यदि (specs->declspec_il != cdil_none)
	{
	  तार्किक saved = in_late_द्विआधारी_op;
	  in_late_द्विआधारी_op = सत्य;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_गन्ती);
	  in_late_द्विआधारी_op = saved;
	}
      अन्यथा
	fnbody = c_parser_compound_statement (parser, &endloc);
      रूख fndecl = current_function_decl;
      यदि (nested && specs->declspec_il == cdil_none)
	{
	  रूख decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_झिक_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_अभिव्यक्ति, decl));
	}
      अन्यथा यदि (nested)
	{
	  यदि (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  अन्यथा
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_झिक_function_context ();
	}
      अन्यथा
	{
	  यदि (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      यदि (specs->declspec_il != cdil_none)
	DECL_SAVED_रूख (fndecl) = NULL_रूख;

      रोक;
    }

  फर्काऊ result;
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
  रूख asm_str = NULL_रूख;
  रूख outputs = NULL_रूख, inputs = NULL_रूख;
  यदि (!parens.require_open (parser))
    गच्छ done;
  asm_str = c_parser_asm_string_literal (parser);
  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      गच्छ done;
    }
  लागि (पूर्णाङ्क section = 0; section < 2; ++section)
    {
      यदि (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  यदि (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      asm_str = NULL_रूख;
	      गच्छ done;
	    }
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, असत्य))
	गच्छ error_close_paren;
      यदि (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  यदि (section)
	    inputs = c_parser_asm_operands (parser);
	  अन्यथा
	    outputs = c_parser_asm_operands (parser);
	}
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	रोक;
    }

  यदि (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      asm_str = NULL_रूख;
    }

  यदि (asm_str)
    asm_str = build_asm_अभिव्यक्ति (asm_loc, asm_str, outputs, inputs,
			      NULL_रूख, NULL_रूख, असत्य, असत्य);
done:
  यदि (asm_str)
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
  यदि (parser->error
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
  location_t assert_loc, मान_loc;
  रूख मान;
  रूख string = NULL_रूख;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  रूख spelling = c_parser_peek_token (parser)->मान;
  assert_loc = c_parser_peek_token (parser)->location;
  यदि (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  अन्यथा
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ;
  location_t मान_tok_loc = c_parser_peek_token (parser)->location;
  मान = convert_lvalue_to_rvalue (मान_tok_loc,
				    c_parser_अभिव्यक्ति_no_commas (parser, रिक्त),
				    सत्य, सत्य).मान;
  मान_loc = अभिव्यक्ति_LOC_OR_LOC (मान, मान_tok_loc);
  यदि (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_STRING:
	पक्ष CPP_STRING16:
	पक्ष CPP_STRING32:
	पक्ष CPP_WSTRING:
	पक्ष CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, असत्य, सत्य).मान;
	  रोक;
	स्वभाव:
	  c_parser_error (parser, "expected string literal");
	  फर्काऊ;
	}
    }
  अन्यथा यदि (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (मान)))
    {
      error_at (मान_loc, "expression in static assertion is not an integer");
      फर्काऊ;
    }
  यदि (रूख_CODE (मान) != INTEGER_CST)
    {
      मान = c_fully_fold (मान, असत्य, रिक्त);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (मान);
      यदि (रूख_CODE (मान) == INTEGER_CST)
	pedwarn (मान_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  यदि (रूख_CODE (मान) != INTEGER_CST)
    {
      error_at (मान_loc, "expression in static assertion is not constant");
      फर्काऊ;
    }
  constant_expression_warning (मान);
  यदि (integer_zerop (मान))
    {
      यदि (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      अन्यथा
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

  यदि (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  यदि (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      रूख attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = असत्य;
    }

  जबसम्म (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      संरचना c_typespec t;
      रूख attrs;
      रूख align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      यदि ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	रोक;

      यदि (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  रूख मान = name_token->मान;
	  c_id_kind kind = name_token->id_kind;

	  यदि (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = सत्य;
	      जारी;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  यदि (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    रोक;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = सत्य;
	  attrs_ok = सत्य;
	  यदि (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (मान, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      यदि (अचर वर्ण *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    मान, suggestion);
		}
	      अन्यथा
		error_at (loc, "unknown type name %qE", मान);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_गाँठो;
	    }
	  अन्यथा यदि (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (मान);
	    }
	  अन्यथा
	    {
	      रूख proto = NULL_रूख;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      यदि (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (मान, proto);
	    }
	  t.अभिव्यक्ति = NULL_रूख;
	  t.अभिव्यक्ति_const_operands = सत्य;
	  t.has_enum_type_specifier = असत्य;
	  declspecs_add_type (name_token->location, specs, t);
	  जारी;
	}
      यदि (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  रूख proto;
	  gcc_assert (c_dialect_objc ());
	  यदि (!typespec_ok || seen_type)
	    रोक;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_रूख, proto);
	  t.अभिव्यक्ति = NULL_रूख;
	  t.अभिव्यक्ति_const_operands = सत्य;
	  t.has_enum_type_specifier = असत्य;
	  declspecs_add_type (loc, specs, t);
	  जारी;
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
	  यदि (!scspec_ok)
	    गच्छ out;
	  attrs_ok = सत्य;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->मान);
	  c_parser_consume_token (parser);
	  रोक;
	पक्ष RID_AUTO_TYPE:
	  यदि (!auto_type_ok)
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
	  यदि (!typespec_ok)
	    गच्छ out;
	  attrs_ok = सत्य;
	  seen_type = सत्य;
	  यदि (c_dialect_objc ())
	    parser->objc_need_raw_identifier = सत्य;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->मान;
	  t.अभिव्यक्ति = NULL_रूख;
	  t.अभिव्यक्ति_const_operands = सत्य;
	  t.has_enum_type_specifier = असत्य;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  रोक;
	पक्ष RID_ENUM:
	  यदि (!typespec_ok)
	    गच्छ out;
	  attrs_ok = सत्य;
	  seen_type = सत्य;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  रोक;
	पक्ष RID_STRUCT:
	पक्ष RID_UNION:
	  यदि (!typespec_ok)
	    गच्छ out;
	  attrs_ok = सत्य;
	  seen_type = सत्य;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  रोक;
	पक्ष RID_TYPEOF:
	पक्ष RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  यदि (!typespec_ok || seen_type)
	    गच्छ out;
	  attrs_ok = सत्य;
	  seen_type = सत्य;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  रोक;
	पक्ष RID_BITINT:
	  यदि (!typespec_ok)
	    गच्छ out;
	  अन्यथा
	    {
	      attrs_ok = सत्य;
	      seen_type = सत्य;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->मान;
	      t.अभिव्यक्ति = error_mark_गाँठो;
	      t.अभिव्यक्ति_const_operands = सत्य;
	      t.has_enum_type_specifier = असत्य;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      यदि (parens.require_open (parser))
		{
		  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
		  t.अभिव्यक्ति = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, सत्य,
						     सत्य).मान;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  रोक;
	पक्ष RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  यदि (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  यदि (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  अन्यथा
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = सत्य;
	  रूख मान;
	  मान = c_parser_peek_token (parser)->मान;
	  c_parser_consume_token (parser);
	  यदि (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = सत्य;
	      c_parser_consume_token (parser);
	      संरचना c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_गाँठो;
	      t.अभिव्यक्ति = NULL_रूख;
	      t.अभिव्यक्ति_const_operands = सत्य;
	      t.has_enum_type_specifier = असत्य;
	      यदि (type != रिक्त)
		t.spec = groktypename (type, &t.अभिव्यक्ति,
				       &t.अभिव्यक्ति_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      यदि (t.spec != error_mark_गाँठो)
		{
		  यदि (रूख_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  अन्यथा यदि (रूख_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  अन्यथा यदि (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  अन्यथा
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  अन्यथा
	    declspecs_add_qual (loc, specs, मान);
	  रोक;
	पक्ष RID_CONST:
	पक्ष RID_VOLATILE:
	पक्ष RID_RESTRICT:
	  attrs_ok = सत्य;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->मान);
	  c_parser_consume_token (parser);
	  रोक;
	पक्ष RID_ATTRIBUTE:
	  यदि (!attrs_ok)
	    गच्छ out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  रोक;
	पक्ष RID_ALIGNAS:
	  यदि (!alignspec_ok)
	    गच्छ out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  रोक;
	पक्ष RID_GIMPLE:
	  यदि (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  रोक;
	पक्ष RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  रोक;
	स्वभाव:
	  गच्छ out;
	}
    }
 out:
  यदि (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

स्थिर शून्य
report_bad_enum_name (c_parser *parser)
{
  यदि (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      विकल्प (token->type)
	{
	स्वभाव:
	  रोक;
	पक्ष CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = सत्य;
	  फर्काऊ;
	पक्ष CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  यदि (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->मान));
	      add_note_about_new_keyword (token->location,
					  token->मान);
	      parser->error = सत्य;
	      फर्काऊ;
	    }
	  रोक;
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
  तार्किक potential_nesting_p = असत्य;
  रूख std_attrs = NULL_रूख;
  रूख attrs;
  रूख ident = NULL_रूख;
  रूख fixed_underlying_type = NULL_रूख;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  यदि (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->मान;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  यदि (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      यदि (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, सत्य);
	  यदि (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_रूख == TYPE_मानहरू (ret.spec);
	}
      अन्यथा
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_रूख;
	  ret.kind = ctsk_tagdef;
	  ret.अभिव्यक्ति = NULL_रूख;
	  ret.अभिव्यक्ति_const_operands = सत्य;
	  ret.has_enum_type_specifier = सत्य;
	}
      c_parser_consume_token (parser);
      संरचना c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, असत्य, सत्य, असत्य, असत्य, असत्य,
			  असत्य, सत्य, cla_prefer_id);
      finish_declspecs (specs);
      यदि (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      अन्यथा यदि (रूख_CODE (specs->type) != INTEGER_TYPE
	       && रूख_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || रूख_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_गाँठो;
	}
      अन्यथा यदि (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      यदि (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  यदि (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_रूख)
	    {
	      TYPE_MIN_मान (ret.spec) =
		TYPE_MIN_मान (fixed_underlying_type);
	      TYPE_MAX_मान (ret.spec) =
		TYPE_MAX_मान (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_रूख;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  अन्यथा यदि (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      संरचना c_enum_contents the_enum;
      रूख type;
      रूख postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      रूख मानहरू;
      timevar_थप (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      मानहरू = NULL_रूख;
      c_parser_consume_token (parser);
      जबसम्म (सत्य)
	{
	  रूख enum_id;
	  रूख enum_मान;
	  रूख enum_decl;
	  तार्किक seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, मान_loc;
	  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	      मानहरू = error_mark_गाँठो;
	      रोक;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->मान;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = मान_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  रूख std_attrs = NULL_रूख;
	  यदि (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  रूख enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  यदि (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      मान_loc = c_parser_peek_token (parser)->location;
	      enum_मान = convert_lvalue_to_rvalue (मान_loc,
						     (c_parser_अभिव्यक्ति_no_commas
						      (parser, रिक्त)),
						     सत्य, सत्य).मान;
	    }
	  अन्यथा
	    enum_मान = NULL_रूख;
	  enum_decl = build_enumerator (decl_loc, मान_loc,
					&the_enum, enum_id, enum_मान);
	  यदि (enum_attrs)
	    decl_attributes (&रूख_PURPOSE (enum_decl), enum_attrs, 0);
	  रूख_CHAIN (enum_decl) = मानहरू;
	  मानहरू = enum_decl;
	  seen_comma = असत्य;
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = सत्य;
	      c_parser_consume_token (parser);
	    }
	  यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      यदि (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      रोक;
	    }
	  यदि (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	      मानहरू = error_mark_गाँठो;
	      रोक;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (मानहरू),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.अभिव्यक्ति = NULL_रूख;
      ret.अभिव्यक्ति_const_operands = सत्य;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_रूख;
      timevar_झिक (TV_PARSE_ENUM);
      फर्काऊ ret;
    }
  अन्यथा यदि (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_गाँठो;
      ret.kind = ctsk_tagref;
      ret.अभिव्यक्ति = NULL_रूख;
      ret.अभिव्यक्ति_const_operands = सत्य;
      ret.has_enum_type_specifier = असत्य;
      फर्काऊ ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  यदि (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  यदि (fixed_underlying_type == NULL_रूख)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, असत्य);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      यदि (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  फर्काऊ ret;
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
  रूख std_attrs = NULL_रूख;
  रूख attrs;
  रूख ident = NULL_रूख;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  गणना रूख_code code;
  विकल्प (c_parser_peek_token (parser)->keyword)
    {
    पक्ष RID_STRUCT:
      code = RECORD_TYPE;
      रोक;
    पक्ष RID_UNION:
      code = UNION_TYPE;
      रोक;
    स्वभाव:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  यदि (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->मान;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      वर्ग c_struct_parse_info *struct_info;
      रूख type = start_struct (struct_loc, code, ident, &struct_info);
      रूख postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      रूख contents;
      रूख अभिव्यक्ति = रिक्त;
      timevar_थप (TV_PARSE_STRUCT);
      contents = NULL_रूख;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      यदि (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  रूख name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  यदि (!parens.require_open (parser))
	    गच्छ end_at_defs;
	  यदि (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->मान;
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
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
      जबसम्म (सत्य)
	{
	  रूख decls;
	  /* Parse any stray semicolon.  */
	  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      रोक;
	    }
	  /* Accept #pragmas at struct scope.  */
	  यदि (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, रिक्त, NULL_रूख);
	      जारी;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &अभिव्यक्ति);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  अन्यथा
	    {
	      यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      अन्यथा यदि (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
		  रोक;
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
				struct_info, &अभिव्यक्ति);
      ret.kind = ctsk_tagdef;
      ret.अभिव्यक्ति = अभिव्यक्ति;
      ret.अभिव्यक्ति_const_operands = सत्य;
      ret.has_enum_type_specifier = असत्य;
      timevar_झिक (TV_PARSE_STRUCT);
      फर्काऊ ret;
    }
  अन्यथा यदि (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_गाँठो;
      ret.kind = ctsk_tagref;
      ret.अभिव्यक्ति = NULL_रूख;
      ret.अभिव्यक्ति_const_operands = सत्य;
      ret.has_enum_type_specifier = असत्य;
      फर्काऊ ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  यदि (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 असत्य);
  फर्काऊ ret;
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

स्थिर रूख
c_parser_struct_declaration (c_parser *parser, रूख *अभिव्यक्ति)
{
  संरचना c_declspecs *specs;
  रूख prefix_attrs;
  रूख all_prefix_attrs;
  रूख decls;
  location_t decl_loc;
  यदि (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      पूर्णाङ्क ext;
      रूख decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, अभिव्यक्ति);
      restore_extension_diagnostics (ext);
      फर्काऊ decl;
    }
  यदि (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      फर्काऊ NULL_रूख;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, असत्य, सत्य, सत्य,
		      सत्य, असत्य, सत्य, सत्य, cla_nonabstract_decl);
  यदि (parser->error)
    फर्काऊ NULL_रूख;
  यदि (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      फर्काऊ NULL_रूख;
    }
  finish_declspecs (specs);
  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      रूख ret;
      यदि (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_रूख;
	}
      अन्यथा
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  रूख attrs = रिक्त;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_रूख), specs,
			   NULL_रूख, &attrs, अभिव्यक्ति);
	  यदि (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      फर्काऊ ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  यदि (specs->typespec_kind == ctsk_tagdef
      && रूख_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = असत्य;
      फर्काऊ NULL_रूख;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_रूख;
  decls = NULL_रूख;
  जबसम्म (सत्य)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      संरचना c_declarator *declarator;
      तार्किक dummy = असत्य;
      यदि (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_रूख);
      अन्यथा
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      यदि (declarator == रिक्त)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  रोक;
	}
      यदि (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  रूख postfix_attrs = NULL_रूख;
	  रूख width = NULL_रूख;
	  रूख d;
	  यदि (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_अभिव्यक्ति_no_commas
						 (parser, रिक्त)),
						सत्य, सत्य).मान;
	    }
	  यदि (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, अभिव्यक्ति);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  यदि (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  अन्यथा
	    all_prefix_attrs = prefix_attrs;
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा यदि (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      रोक;
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      रोक;
	    }
	}
      अन्यथा
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  रोक;
	}
    }
  फर्काऊ decls;
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
  ret.spec = error_mark_गाँठो;
  ret.अभिव्यक्ति = NULL_रूख;
  ret.अभिव्यक्ति_const_operands = सत्य;
  ret.has_enum_type_specifier = असत्य;
  यदि (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = असत्य;
      रूख spelling = c_parser_peek_token (parser)->मान;
      is_std = (flag_isoc23
		&& म_भेद (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  अन्यथा
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = सत्य;
      रूख spelling = c_parser_peek_token (parser)->मान;
      is_std = म_भेद (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  यदि (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      फर्काऊ ret;
    }
  यदि (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      संरचना c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      यदि (type != रिक्त)
	{
	  ret.spec = groktypename (type, &ret.अभिव्यक्ति, &ret.अभिव्यक्ति_const_operands);
	  झिक_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  अन्यथा
    {
      तार्किक was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      संरचना c_अभिव्यक्ति अभिव्यक्ति = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      यदि (रूख_CODE (अभिव्यक्ति.मान) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (रूख_OPERAND (अभिव्यक्ति.मान, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (अभिव्यक्ति.मान);
      ret.spec = रूख_TYPE (अभिव्यक्ति.मान);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      यदि (was_vm)
	ret.अभिव्यक्ति = c_fully_fold (अभिव्यक्ति.मान, असत्य, &ret.अभिव्यक्ति_const_operands);
      झिक_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  यदि (ret.spec != error_mark_गाँठो)
    {
      यदि (is_unqual)
	{
	  तार्किक is_array = रूख_CODE (ret.spec) == ARRAY_TYPE;
	  पूर्णाङ्क quals = TYPE_QUALS (strip_array_types (ret.spec));
	  यदि ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      यदि (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      यदि (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  यदि (रूख_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  अन्यथा यदि (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (रूख_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (रूख_TYPE (ret.spec)));
	}
    }
  फर्काऊ ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

स्थिर रूख
c_parser_alignas_specifier (c_parser * parser)
{
  रूख ret = error_mark_गाँठो;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  रूख spelling = c_parser_peek_token (parser)->मान;
  c_parser_consume_token (parser);
  यदि (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  अन्यथा
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ ret;
  यदि (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      संरचना c_type_name *type = c_parser_type_name (parser);
      यदि (type != रिक्त)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, रिक्त, रिक्त),
					असत्य, सत्य, 1);
    }
  अन्यथा
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_अभिव्यक्ति_no_commas (parser, रिक्त),
				    सत्य, सत्य).मान;
  parens.skip_until_found_close (parser);
  फर्काऊ ret;
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
  यदि (c_parser_next_token_is (parser, CPP_MULT))
    {
      संरचना c_declspecs *quals_attrs = build_null_declspecs ();
      संरचना c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, असत्य, असत्य, सत्य,
			  असत्य, असत्य, सत्य, असत्य, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      यदि (inner == रिक्त)
	फर्काऊ रिक्त;
      अन्यथा
	फर्काऊ make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  फर्काऊ c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
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

  यदि (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      संरचना c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->मान);
      *seen_id = सत्य;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      यदि (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      फर्काऊ c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  यदि (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      संरचना c_declarator *inner = build_id_declarator (NULL_रूख);
      inner->id_loc = c_parser_peek_token (parser)->location;
      फर्काऊ c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      रूख attrs;
      संरचना c_declarator *inner;
      c_parser_consume_token (parser);
      तार्किक have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      यदि (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  संरचना c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  यदि (args == रिक्त)
	    फर्काऊ रिक्त;
	  अन्यथा
	    {
	      inner = build_id_declarator (NULL_रूख);
	      यदि (!(args->types
		    && args->types != error_mark_गाँठो
		    && रूख_CODE (रूख_मान (args->types)) == IDENTIFIER_गाँठो)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  रूख std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  यदि (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      फर्काऊ c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      यदि (inner != रिक्त && attrs != रिक्त)
	inner = build_attrs_declarator (attrs, inner);
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  यदि (inner == रिक्त)
	    फर्काऊ रिक्त;
	  अन्यथा
	    फर्काऊ c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      अन्यथा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  फर्काऊ रिक्त;
	}
    }
  अन्यथा
    {
      यदि (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  फर्काऊ रिक्त;
	}
      अन्यथा
	फर्काऊ build_id_declarator (NULL_रूख);
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
  यदि (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      संरचना c_declarator *declarator;
      संरचना c_declspecs *quals_attrs = build_null_declspecs ();
      संरचना c_अभिव्यक्ति dimen;
      dimen.मान = NULL_रूख;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_रूख;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, असत्य, असत्य, सत्य,
			  असत्य, असत्य, असत्य, असत्य, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      यदि (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  यदि (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, असत्य, असत्य, सत्य,
				असत्य, असत्य, असत्य, असत्य, cla_prefer_id);
	}
      यदि (!quals_attrs->declspecs_seen_p)
	quals_attrs = रिक्त;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      अचर तार्किक static_seen = (static_loc != UNKNOWN_LOCATION);
      तार्किक star_seen = असत्य;
      यदि (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = सत्य;
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);

      यदि (static_seen)
	{
	  यदि (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = असत्य;
	      dimen.मान = error_mark_गाँठो;
	    }
	  अन्यथा यदि (!dimen.मान)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      यदि (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      अन्यथा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  फर्काऊ रिक्त;
	}
      यदि (dimen.मान)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, सत्य, सत्य);
      declarator = build_array_declarator (brace_loc, dimen.मान, quals_attrs,
					   static_seen, star_seen);
      यदि (declarator == रिक्त)
	फर्काऊ रिक्त;
      यदि (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  रूख std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  यदि (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      फर्काऊ c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  अन्यथा यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      रूख attrs;
      संरचना c_arg_info *args;
      c_parser_consume_token (parser);
      तार्किक have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      यदि (args == रिक्त)
	फर्काऊ रिक्त;
      अन्यथा
	{
	  यदि (!(args->types
		&& args->types != error_mark_गाँठो
		&& रूख_CODE (रूख_मान (args->types)) == IDENTIFIER_गाँठो)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      रूख std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      यदि (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  फर्काऊ c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  फर्काऊ inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

स्थिर संरचना c_arg_info *
c_parser_parms_declarator (c_parser *parser, तार्किक id_list_ok, रूख attrs,
			   तार्किक have_gnu_attrs)
{
  थप_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  यदि (id_list_ok
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
      रूख list = NULL_रूख, *nextp = &list;
      जबसम्म (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_रूख_list (NULL_रूख,
				    c_parser_peek_token (parser)->मान);
	  nextp = & रूख_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is_not (parser, CPP_COMMA))
	    रोक;
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      रोक;
	    }
	}
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  संरचना c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  झिक_scope ();
	  फर्काऊ ret;
	}
      अन्यथा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  झिक_scope ();
	  फर्काऊ रिक्त;
	}
    }
  अन्यथा
    {
      संरचना c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, रिक्त, have_gnu_attrs);
      झिक_scope ();
      फर्काऊ ret;
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
c_parser_parms_list_declarator (c_parser *parser, रूख attrs, रूख अभिव्यक्ति,
				तार्किक have_gnu_attrs)
{
  तार्किक bad_parm = असत्य;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      संरचना c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      फर्काऊ ret;
    }
  यदि (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      संरचना c_arg_info *ret = build_arg_info ();

      ret->types = NULL_रूख;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = सत्य;
	  c_parser_consume_token (parser);
	  फर्काऊ ret;
	}
      अन्यथा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  फर्काऊ रिक्त;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  जबसम्म (सत्य)
    {
      /* Parse a parameter.  */
      संरचना c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_रूख;
      have_gnu_attrs = असत्य;
      यदि (parm == रिक्त)
	bad_parm = सत्य;
      अन्यथा
	थप_parm_decl (parm, &अभिव्यक्ति);
      यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  रूख new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  तार्किक new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  फर्काऊ c_parser_parms_list_declarator (parser, new_attrs, अभिव्यक्ति,
						 new_have_gnu_attrs);
	}
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  यदि (bad_parm)
	    फर्काऊ रिक्त;
	  अन्यथा
	    फर्काऊ get_parm_info (असत्य, अभिव्यक्ति);
	}
      यदि (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, असत्य))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  फर्काऊ रिक्त;
	}
      यदि (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      यदि (bad_parm)
		फर्काऊ रिक्त;
	      अन्यथा
		फर्काऊ get_parm_info (सत्य, अभिव्यक्ति);
	    }
	  अन्यथा
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      फर्काऊ रिक्त;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

स्थिर संरचना c_parm *
c_parser_parameter_declaration (c_parser *parser, रूख attrs,
				तार्किक have_gnu_attrs)
{
  संरचना c_declspecs *specs;
  संरचना c_declarator *declarator;
  रूख prefix_attrs;
  रूख postfix_attrs = NULL_रूख;
  तार्किक dummy = असत्य;

  /* Accept #pragmas between parameter declarations.  */
  जबसम्म (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, रिक्त, NULL_रूख);

  यदि (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      यदि (parser->error)
	फर्काऊ रिक्त;
      c_parser_set_source_position_from_token (token);
      यदि (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->मान,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  यदि (अचर वर्ण *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->मान, suggestion);
	    }
	  अन्यथा
	    error_at (token->location, "unknown type name %qE", token->मान);
	  parser->error = सत्य;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      अन्यथा
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      फर्काऊ रिक्त;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  यदि (attrs)
    {
      declspecs_add_attrs (आगत_location, specs, attrs);
      attrs = NULL_रूख;
    }
  c_parser_declspecs (parser, specs, सत्य, सत्य, सत्य, सत्य, असत्य,
		      !have_gnu_attrs, सत्य, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  यदि (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_शीर्ष_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_रूख;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  यदि (declarator == रिक्त)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, रिक्त);
      फर्काऊ रिक्त;
    }
  यदि (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
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
  जबसम्म (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  फर्काऊ build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

स्थिर रूख
c_parser_asm_string_literal (c_parser *parser)
{
  रूख str;
  पूर्णाङ्क save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, असत्य, असत्य).मान;
  warn_overlength_strings = save_flag;
  फर्काऊ str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

स्थिर रूख
c_parser_simple_asm_अभिव्यक्ति (c_parser *parser)
{
  रूख str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ NULL_रूख;
  str = c_parser_asm_string_literal (parser);
  यदि (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      फर्काऊ NULL_रूख;
    }
  फर्काऊ str;
}

स्थिर रूख
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  रूख attr_name = NULL_रूख;

  यदि (c_parser_next_token_is (parser, CPP_KEYWORD))
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
	  ok = सत्य;
	  रोक;
	स्वभाव:
	  ok = असत्य;
	  रोक;
	}
      यदि (!ok)
	फर्काऊ NULL_रूख;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(पूर्णाङ्क) c_parser_peek_token (parser)->keyword];
    }
  अन्यथा यदि (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->मान;

  फर्काऊ attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

स्थिर रूख
c_parser_attribute_arguments (c_parser *parser, तार्किक takes_identifier,
			      तार्किक require_string, तार्किक assume_attr,
			      तार्किक allow_empty_args)
{
  vec<रूख, va_gc> *अभिव्यक्ति_list;
  रूख attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  यदि (c_parser_next_token_is (parser, CPP_NAME)
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
      रूख arg1 = c_parser_peek_token (parser)->मान;
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_रूख_list (NULL_रूख, arg1);
      अन्यथा
	{
	  रूख रूख_list;
	  c_parser_consume_token (parser);
	  अभिव्यक्ति_list = c_parser_अभिव्यक्ति_list (parser, असत्य, सत्य,
					  रिक्त, रिक्त, रिक्त, रिक्त);
	  रूख_list = build_रूख_list_vec (अभिव्यक्ति_list);
	  attr_args = रूख_cons (NULL_रूख, arg1, रूख_list);
	  release_रूख_vector (अभिव्यक्ति_list);
	}
    }
  अन्यथा
    {
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  यदि (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_रूख;
	}
      अन्यथा यदि (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  रूख string = c_parser_string_literal (parser, असत्य, सत्य).मान;
	  attr_args = build_रूख_list (NULL_रूख, string);
	}
      अन्यथा यदि (assume_attr)
	{
	  रूख cond
	    = c_parser_conditional_expression (parser, रिक्त, NULL_रूख).मान;
	  यदि (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_args = build_रूख_list (NULL_रूख, cond);
	  अन्यथा
	    {
	      रूख रूख_list;
	      c_parser_consume_token (parser);
	      अभिव्यक्ति_list = c_parser_अभिव्यक्ति_list (parser, असत्य, सत्य,
					      रिक्त, रिक्त, रिक्त, रिक्त);
	      रूख_list = build_रूख_list_vec (अभिव्यक्ति_list);
	      attr_args = रूख_cons (NULL_रूख, cond, रूख_list);
	      release_रूख_vector (अभिव्यक्ति_list);
	    }
	}
      अन्यथा
	{
	  अभिव्यक्ति_list = c_parser_अभिव्यक्ति_list (parser, असत्य, सत्य,
					  रिक्त, रिक्त, रिक्त, रिक्त);
	  attr_args = build_रूख_list_vec (अभिव्यक्ति_list);
	  release_रूख_vector (अभिव्यक्ति_list);
	}
    }
  फर्काऊ attr_args;
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

स्थिर रूख
c_parser_gnu_attribute (c_parser *parser, रूख attrs,
			तार्किक expect_comma = असत्य, तार्किक empty_ok = सत्य)
{
  तार्किक comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  यदि (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    फर्काऊ NULL_रूख;

  जबसम्म (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      यदि (!empty_ok)
	फर्काऊ attrs;
    }

  रूख attr_name = c_parser_gnu_attribute_any_word (parser);
  यदि (attr_name == NULL_रूख)
    फर्काऊ NULL_रूख;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  रूख attr;
  यदि (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      यदि (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  फर्काऊ error_mark_गाँठो;
	}
      attr = build_रूख_list (attr_name, NULL_रूख);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      फर्काऊ attrs;
    }
  c_parser_consume_token (parser);

  रूख attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    असत्य,
				    is_attribute_p ("assume", attr_name),
				    सत्य);

  attr = build_रूख_list (attr_name, attr_args);
  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  अन्यथा
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      फर्काऊ error_mark_गाँठो;
    }

  यदि (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      फर्काऊ error_mark_गाँठो;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  फर्काऊ attrs;
}

स्थिर रूख
c_parser_gnu_attributes (c_parser *parser)
{
  रूख attrs = NULL_रूख;
  जबसम्म (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      तार्किक save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = असत्य;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  फर्काऊ attrs;
	}
      यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  फर्काऊ attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      लागि (तार्किक expect_comma = असत्य; ; expect_comma = सत्य)
	{
	  /* Parse a single attribute.  */
	  रूख attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  यदि (attr == error_mark_गाँठो)
	    फर्काऊ attrs;
	  यदि (!attr)
	    रोक;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      अन्यथा
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  फर्काऊ attrs;
	}
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      अन्यथा
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  फर्काऊ attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  फर्काऊ attrs;
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
  जबसम्म (सत्य)
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
	    रोक;
	  }

	पक्ष CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    रोक;
	  }

	पक्ष CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  रोक;

	पक्ष CPP_CLOSE_BRACE:
	पक्ष CPP_CLOSE_PAREN:
	पक्ष CPP_CLOSE_SQUARE:
	पक्ष CPP_EOF:
	  फर्काऊ;

	पक्ष CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  रोक;

	स्वभाव:
	  c_parser_consume_token (parser);
	  रोक;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

स्थिर शून्य
c_parser_omp_directive_args (c_parser *parser, रूख attribute, तार्किक decl_p)
{
  अचिन्हित पूर्णाङ्क n = 1;
  c_token *first = c_parser_peek_token (parser);
  यदि (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      रूख_मान (attribute) = NULL_रूख;
      फर्काऊ;
    }
  यदि (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      रूख_मान (attribute) = NULL_रूख;
      फर्काऊ;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  लागि (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_थप (*tok);
      c_parser_consume_token (parser);
    }
  रूख arg = make_गाँठो (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  यदि (decl_p)
    रूख_PUBLIC (arg) = 1;
  रूख_मान (attribute) = रूख_cons (NULL_रूख, arg, रूख_मान (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

स्थिर शून्य
c_parser_omp_sequence_args (c_parser *parser, रूख attribute)
{
  गर
    {
      c_token *token = c_parser_peek_token (parser);
      यदि (token->type == CPP_NAME
	  && म_भेद (IDENTIFIER_POINTER (token->मान), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      तार्किक directive = असत्य;
      अचर वर्ण *p;
      यदि (token->type != CPP_NAME)
	p = "";
      अन्यथा
	p = IDENTIFIER_POINTER (token->मान);
      यदि (म_भेद (p, "directive") == 0)
	directive = सत्य;
      अन्यथा यदि (म_भेद (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  अचिन्हित nesting_depth = 0;

	  जबसम्म (सत्य)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      यदि ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		रोक;
	      /* If we've run out of tokens, stop.  */
	      यदि (token->type == CPP_EOF)
		रोक;
	      यदि (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		रोक;
	      यदि (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      अन्यथा यदि (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  यदि (nesting_depth-- == 0)
		    रोक;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  यदि (c_parser_next_token_is_not (parser, CPP_COMMA))
	    रोक;
	  c_parser_consume_token (parser);
	  जारी;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      यदि (parens.require_open (parser))
	{
	  यदि (directive)
	    c_parser_omp_directive_args (parser, attribute, असत्य);
	  अन्यथा
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  यदि (c_parser_next_token_is_not (parser, CPP_COMMA))
	    रोक;
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (c_parser_next_token_is_not (parser, CPP_COMMA))
	रोक;
      अन्यथा
	c_parser_consume_token (parser);
    }
  जबसम्म (1);
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

स्थिर रूख
c_parser_std_attribute (c_parser *parser, तार्किक for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  रूख ns, name, attribute;

  /* Parse the attribute-token.  */
  यदि (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      फर्काऊ error_mark_गाँठो;
    }
  name = canonicalize_attr_name (token->मान);
  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      यदि (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      यदि (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  फर्काऊ error_mark_गाँठो;
	}
      name = canonicalize_attr_name (token->मान);
      c_parser_consume_token (parser);
    }
  अन्यथा
    ns = NULL_रूख;
  attribute = build_रूख_list (build_रूख_list (ns, name), NULL_रूख);

  /* Parse the arguments, if any.  */
  अचर attribute_spec *as = lookup_attribute_spec (रूख_PURPOSE (attribute));
  यदि (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      यदि ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  फर्काऊ error_mark_गाँठो;
	}
      गच्छ out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    यदि ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	फर्काऊ error_mark_गाँठो;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    यदि (as && !attribute_ignored_p (as))
      {
	तार्किक takes_identifier
	  = (ns != NULL_रूख
	     && म_भेद (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	तार्किक require_string
	  = (ns == NULL_रूख
	     && (म_भेद (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || म_भेद (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	तार्किक assume_attr
	  = (ns != NULL_रूख
	     && म_भेद (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && म_भेद (IDENTIFIER_POINTER (name), "assume") == 0);
	रूख_मान (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, असत्य);
      }
    अन्यथा
      {
	यदि ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    यदि (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, असत्य);
		parens.skip_until_found_close (parser);
		फर्काऊ attribute;
	      }
	    अन्यथा यदि (is_attribute_p ("decl", name))
	      {
		रूख_मान (रूख_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, सत्य);
		parens.skip_until_found_close (parser);
		फर्काऊ attribute;
	      }
	    अन्यथा यदि (is_attribute_p ("sequence", name))
	      {
		रूख_मान (रूख_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		रूख_मान (attribute) = nreverse (रूख_मान (attribute));
		फर्काऊ attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  यदि (ns == NULL_रूख && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (आगत_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      फर्काऊ error_mark_गाँठो;
    }
  फर्काऊ attribute;
}

स्थिर रूख
c_parser_std_attribute_list (c_parser *parser, तार्किक for_tm)
{
  रूख attributes = NULL_रूख;
  जबसम्म (सत्य)
    {
      c_token *token = c_parser_peek_token (parser);
      यदि (token->type == CPP_CLOSE_SQUARE)
	रोक;
      यदि (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  जारी;
	}
      रूख attribute = c_parser_std_attribute (parser, for_tm);
      यदि (attribute != error_mark_गाँठो)
	{
	  रूख_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      यदि (c_parser_next_token_is_not (parser, CPP_COMMA))
	रोक;
    }
  फर्काऊ attributes;
}

स्थिर रूख
c_parser_std_attribute_specifier (c_parser *parser, तार्किक for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    फर्काऊ NULL_रूख;
  यदि (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      फर्काऊ NULL_रूख;
    }
  रूख attributes;
  यदि (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      स्वतः ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  अन्यथा
    {
      यदि (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  फर्काऊ nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

स्थिर तार्किक
c_parser_check_balanced_raw_token_sequence (c_parser *parser, अचिन्हित पूर्णाङ्क *n)
{
  जबसम्म (सत्य)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      विकल्प (token->type)
	{
	पक्ष CPP_OPEN_BRACE:
	  {
	    ++*n;
	    यदि (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		यदि (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		अन्यथा
		  फर्काऊ असत्य;
	      }
	    अन्यथा
	      फर्काऊ असत्य;
	    रोक;
	  }

	पक्ष CPP_OPEN_PAREN:
	  {
	    ++*n;
	    यदि (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		यदि (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		अन्यथा
		  फर्काऊ असत्य;
	      }
	    अन्यथा
	      फर्काऊ असत्य;
	    रोक;
	  }

	पक्ष CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    यदि (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		यदि (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		अन्यथा
		  फर्काऊ असत्य;
	      }
	    अन्यथा
	      फर्काऊ असत्य;
	    रोक;
	  }

	पक्ष CPP_CLOSE_BRACE:
	पक्ष CPP_CLOSE_PAREN:
	पक्ष CPP_CLOSE_SQUARE:
	पक्ष CPP_EOF:
	  फर्काऊ सत्य;

	स्वभाव:
	  ++*n;
	  रोक;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

स्थिर तार्किक
c_parser_nth_token_starts_std_attributes (c_parser *parser, अचिन्हित पूर्णाङ्क n)
{
  यदि (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    फर्काऊ असत्य;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  यदि (!c_dialect_objc ())
    फर्काऊ सत्य;
  n += 2;
  यदि (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    फर्काऊ असत्य;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  यदि (token->type != CPP_CLOSE_SQUARE)
    फर्काऊ असत्य;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  फर्काऊ token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

स्थिर माप_प्रकार
c_parser_skip_std_attribute_spec_seq (c_parser *parser, माप_प्रकार n)
{
  माप_प्रकार orig_n = n;
  जबसम्म (सत्य)
    {
      यदि (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  अचिन्हित पूर्णाङ्क m = n + 2;
	  यदि (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    फर्काऊ orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  यदि (token->type != CPP_CLOSE_SQUARE)
	    फर्काऊ orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  यदि (token->type != CPP_CLOSE_SQUARE)
	    फर्काऊ orig_n;
	  n = m + 2;
	}
      अन्यथा
	रोक;
    }
  फर्काऊ n;
}

स्थिर रूख
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  रूख attributes = NULL_रूख;
  गर
    {
      रूख attrs = c_parser_std_attribute_specifier (parser, असत्य);
      attributes = chainon (attributes, attrs);
    }
  जबसम्म (c_parser_nth_token_starts_std_attributes (parser, 1));
  फर्काऊ attributes;
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
  तार्किक dummy = असत्य;
  c_parser_declspecs (parser, specs, असत्य, सत्य, सत्य, alignas_ok, असत्य,
		      असत्य, सत्य, cla_prefer_type);
  यदि (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      फर्काऊ रिक्त;
    }
  यदि (specs->type != error_mark_गाँठो)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      यदि (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_शीर्ष_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  यदि (declarator == रिक्त)
    फर्काऊ रिक्त;
  ret = XOBNEW (&parser_obstack, संरचना c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  फर्काऊ ret;
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_initializer (c_parser *parser, रूख decl)
{
  यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    फर्काऊ c_parser_braced_init (parser, NULL_रूख, असत्य, रिक्त,
				 decl != error_mark_गाँठो
				 && C_DECL_VARIABLE_SIZE (decl));
  अन्यथा
    {
      संरचना c_अभिव्यक्ति ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      यदि (decl != error_mark_गाँठो && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      यदि (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !रूख_STATIC (decl)
	  && ret.मान == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      यदि (रूख_CODE (ret.मान) != STRING_CST
	  && (रूख_CODE (ret.मान) != COMPOUND_LITERAL_अभिव्यक्ति
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_अभिव्यक्ति_DECL
					    (ret.मान))))
	ret = convert_lvalue_to_rvalue (loc, ret, सत्य, सत्य, सत्य);
      फर्काऊ ret;
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_braced_init (c_parser *parser, रूख type, तार्किक nested_p,
		      संरचना obstack *outer_obstack, तार्किक varsize_p)
{
  संरचना c_अभिव्यक्ति ret;
  संरचना obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = असत्य;
  तार्किक zero_init_padding_bits = असत्य;
  matching_braces braces;
  braces.consume_open (parser);
  यदि (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      थप_init_level (brace_loc, 0, &braced_init_obstack);
    }
  अन्यथा
    really_start_incremental_init (type);
  यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      यदि (flag_isoc23)
	zero_init_padding_bits = सत्य;
    }
  अन्यथा
    {
      यदि (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      जबसम्म (सत्य)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  यदि (parser->error)
	    रोक;
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      जबसम्म (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_अभिव्यक्ति embed_val;
		  embed_val.मान = embed->मान;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_गाँठो;
		  set_c_अभिव्यक्ति_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, असत्य,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  अन्यथा
	    रोक;
	  यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    रोक;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  यदि (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      braces.skip_until_found_close (parser);
      झिक_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, रिक्त);
      फर्काऊ ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = झिक_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  यदि (zero_init_padding_bits
      && ret.मान
      && रूख_CODE (ret.मान) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.मान) = 1;
  obstack_free (&braced_init_obstack, रिक्त);
  set_c_अभिव्यक्ति_source_range (&ret, brace_loc, close_loc);
  फर्काऊ ret;
}

/* Parse a nested initializer, including designators.  */

स्थिर शून्य
c_parser_initelt (c_parser *parser, संरचना obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  यदि (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->मान,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  अन्यथा
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      पूर्णाङ्क des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      जबसम्म (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  पूर्णाङ्क des_prev = des_seen;
	  यदि (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  यदि (des_seen < 2)
	    des_seen++;
	  यदि (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      यदि (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->मान,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      अन्यथा
		{
		  संरचना c_अभिव्यक्ति init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = रिक्त;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, रिक्त);
		  process_init_element (आगत_location, init, असत्य,
					braced_init_obstack);
		  फर्काऊ;
		}
	    }
	  अन्यथा
	    {
	      संरचना c_अभिव्यक्ति first_अभिव्यक्ति;
	      रूख first, second;
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
	      यदि (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  रोक;
		}
	      यदि (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  रूख rec, args;
		  संरचना c_अभिव्यक्ति mexpr;
		  c_parser_consume_token (parser);
		  यदि (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      रूख id = c_parser_peek_token (parser)->मान;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      गच्छ parse_message_args;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
		  mark_exp_read (first_अभिव्यक्ति.मान);
		  यदि (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    गच्छ array_desig_after_first;
		  first = first_अभिव्यक्ति.मान;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  जबसम्म (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      संरचना c_अभिव्यक्ति next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       सत्य, सत्य);
		      rec = build_compound_अभिव्यक्ति (comma_loc, rec, next.मान);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.मान
		    = objc_build_message_अभिव्यक्ति (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = रिक्त;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  फर्काऊ;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	      mark_exp_read (first_अभिव्यक्ति.मान);
	    array_desig_after_first:
	      first_अभिव्यक्ति = convert_lvalue_to_rvalue (array_index_loc,
						     first_अभिव्यक्ति,
						     सत्य, सत्य);
	      first = first_अभिव्यक्ति.मान;
	      यदि (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_अभिव्यक्ति_no_commas
						      (parser, रिक्त)),
						     सत्य, सत्य).मान;
		  mark_exp_read (second);
		}
	      अन्यथा
		second = NULL_रूख;
	      यदि (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  यदि (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      अन्यथा
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      यदि (des_seen >= 1)
	{
	  यदि (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      यदि (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      अन्यथा
		{
		  संरचना c_अभिव्यक्ति init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = रिक्त;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, रिक्त);
		  process_init_element (आगत_location, init, असत्य,
					braced_init_obstack);
		  फर्काऊ;
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
c_parser_initval (c_parser *parser, संरचना c_अभिव्यक्ति *after,
		  संरचना obstack * braced_init_obstack)
{
  संरचना c_अभिव्यक्ति init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_रूख, सत्य,
				 braced_init_obstack, असत्य);
  अन्यथा
    {
      init = c_parser_अभिव्यक्ति_no_commas (parser, after);
      यदि (init.मान != NULL_रूख
	  && रूख_CODE (init.मान) != STRING_CST
	  && (रूख_CODE (init.मान) != COMPOUND_LITERAL_अभिव्यक्ति
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_अभिव्यक्ति_DECL
					    (init.मान))))
	init = convert_lvalue_to_rvalue (loc, init, सत्य, सत्य, सत्य);
    }
  रूख val = init.मान;
  process_init_element (loc, init, असत्य, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  स्थिर अचिन्हित vals_to_ignore;
  यदि (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  अन्यथा यदि (val
	   && रूख_CODE (val) == INTEGER_CST
	   && रूख_TYPE (val) == integer_type_गाँठो
	   && c_parser_next_token_is (parser, CPP_COMMA))
    यदि (अचिन्हित पूर्णाङ्क len = c_maybe_optimize_large_byte_initializer ())
      {
	वर्ण buf1[64];
	अचिन्हित पूर्णाङ्क i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	लागि (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    यदि (tok->type != CPP_COMMA)
	      रोक;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    यदि (tok->type != CPP_सङ्ख्या
		|| रूख_CODE (tok->मान) != INTEGER_CST
		|| रूख_TYPE (tok->मान) != integer_type_गाँठो
		|| wi::neg_p (wi::to_wide (tok->मान))
		|| wi::to_widest (tok->मान) > अच_अक्षर_उच्च)
	      रोक;
	    buf1[i] = (वर्ण) रूख_to_uhwi (tok->मान);
	    यदि (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	यदि (i < 64)
	  {
	    vals_to_ignore = i;
	    फर्काऊ;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	यदि (tok->type == CPP_CLOSE_BRACE && len != पूर्णांक_उच्च)
	  len = i;
	अन्यथा यदि (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_सङ्ख्या))
	  {
	    vals_to_ignore = i;
	    फर्काऊ;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	अचिन्हित पूर्णाङ्क max_len = 131072 - दुरत्व (संरचना रूख_string, str) - 1;
	अचिन्हित पूर्णाङ्क orig_len = len;
	अचिन्हित पूर्णाङ्क off = 0, last = 0;
	यदि (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= अच_अक्षर_उच्च)
	  off = 1;
	len = MIN (len, max_len - off);
	वर्ण *buf2 = XNEWVEC (वर्ण, len + off);
	यदि (off)
	  buf2[0] = (वर्ण) रूख_to_uhwi (val);
	स_नकल (buf2 + off, buf1, i);
	लागि (अचिन्हित पूर्णाङ्क j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	लागि (; i < len; ++i)
	  {
	    यदि (!c_parser_next_token_is (parser, CPP_COMMA))
	      रोक;
	    tok = c_parser_peek_2nd_token (parser);
	    यदि (tok->type != CPP_सङ्ख्या
		|| रूख_CODE (tok->मान) != INTEGER_CST
		|| रूख_TYPE (tok->मान) != integer_type_गाँठो
		|| wi::neg_p (wi::to_wide (tok->मान))
		|| wi::to_widest (tok->मान) > अच_अक्षर_उच्च)
	      रोक;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    यदि (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      रोक;
	    buf2[i + off] = (वर्ण) रूख_to_uhwi (tok->मान);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    यदि (orig_len == पूर्णांक_उच्च
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_सङ्ख्या)))
	      {
		last = 1;
		रोक;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_गाँठो (RAW_DATA_CST);
	रूख_TYPE (val) = integer_type_गाँठो;
	RAW_DATA_LENGTH (val) = i;
	रूख owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	रूख_TYPE (owner) = build_array_type_nelts (unsigned_char_type_गाँठो,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = रूख_STRING_POINTER (owner) + off;
	init.मान = val;
	set_c_अभिव्यक्ति_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_गाँठो;
	init.m_decimal = 0;
	process_init_element (loc, init, असत्य, braced_init_obstack);
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

स्थिर रूख
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  रूख stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (सत्य);
      c_end_compound_stmt (brace_loc, stmt, सत्य);
      फर्काऊ error_mark_गाँठो;
    }
  stmt = c_begin_compound_stmt (सत्य);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  यदि (endlocp)
    *endlocp = end_loc;

  फर्काऊ c_end_compound_stmt (brace_loc, stmt, सत्य);
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

  यदि (!omp_for_parse_state->in_intervening_code)
    फर्काऊ;
  omp_for_parse_state->saw_intervening_code = सत्य;

  /* Only diagnose errors related to perfect nesting once.  */
  यदि (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      यदि (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = सत्य;
	}
      अन्यथा यदि (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = सत्य;
	}
      अन्यथा यदि (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = सत्य;
	}
      अन्यथा यदि (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = सत्य;
	}
      यदि (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = सत्य;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
स्थिर शून्य
add_structured_block_stmt (रूख sl)
{
  यदि (रूख_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_गाँठो, sl));
}

संरचना c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  अचर c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

स्थिर तार्किक
c_parser_handle_statement_omp_attributes (c_parser *parser, रूख &attrs,
					  तार्किक *have_std_attrs)
{
  यदि (!flag_openmp && !flag_openmp_simd)
    फर्काऊ असत्य;

  auto_vec<c_omp_attribute_data, 16> vd;
  पूर्णाङ्क cnt = 0;
  पूर्णाङ्क tokens = 0;
  तार्किक bad = असत्य;
  लागि (रूख *pa = &attrs; *pa; )
    यदि (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	लागि (रूख a = रूख_मान (*pa); a; a = रूख_CHAIN (a))
	  {
	    रूख d = रूख_मान (a);
	    gcc_assert (रूख_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    यदि (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = असत्य;
		bad = सत्य;
	      }
	    अन्यथा यदि (रूख_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = सत्य;
	      }
	    अचर वर्ण *directive[3] = {};
	    लागि (पूर्णाङ्क i = 0; i < 3; i++)
	      {
		रूख id = NULL_रूख;
		यदि (first + i == last)
		  रोक;
		यदि (first[i].type == CPP_NAME)
		  id = first[i].मान;
		अन्यथा यदि (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(पूर्णाङ्क) first[i].keyword];
		अन्यथा
		  रोक;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    अचर c_omp_directive *dir = रिक्त;
	    यदि (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    यदि (dir == रिक्त)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  रूख_PUBLIC (d) ? "omp::decl" : "omp::directive");
		जारी;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    यदि (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		यदि (directive[1]
		    && (म_भेद (directive[1], "depend") == 0
			|| म_भेद (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		अन्यथा यदि (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (म_भेद (IDENTIFIER_POINTER (first[2].मान),
				     "depend") == 0
			     || म_भेद (IDENTIFIER_POINTER (first[2].मान),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    अन्यथा यदि (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		पूर्णाङ्क paren_depth = 0;
		लागि (पूर्णाङ्क i = 1; first + i < last; i++)
		  यदि (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  अन्यथा यदि (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  अन्यथा यदि (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !म_भेद (IDENTIFIER_POINTER (first[i].मान),
				       "at")
			   && !म_भेद (IDENTIFIER_POINTER (first[i
								 + 2].मान),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      रोक;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_थप (v);
	    यदि (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_थप (v);
	*pa = रूख_CHAIN (*pa);
      }
    अन्यथा
      pa = &रूख_CHAIN (*pa);

  यदि (bad)
    {
    fail:
      यदि (have_std_attrs && attrs == रिक्त)
	*have_std_attrs = असत्य;
      फर्काऊ असत्य;
    }

  अचिन्हित पूर्णाङ्क i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    यदि (v->tokens)
      {
	यदि (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	अन्यथा यदि (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    अन्यथा
      {
	यदि (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  यदि (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      गच्छ fail;
    }
  यदि (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      गच्छ fail;
    }

  यदि (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  यदि (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      गच्छ fail;
    }
  यदि (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      गणना pragma_kind kind = token->pragma_kind;
      यदि (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  गच्छ fail;
	}
    }

  यदि (!tokens)
    फर्काऊ असत्य;

  अचिन्हित पूर्णाङ्क tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = रिक्त;
  vec_safe_reserve (toks, tokens, सत्य);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      यदि (!v->tokens)
	जारी;
      यदि (!flag_openmp && !v->dir->simd)
	जारी;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_थप (tok);
      जबसम्म (++first < last)
	toks->quick_थप (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_थप (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_थप (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  फर्काऊ सत्य;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

स्थिर शून्य
c_parser_handle_directive_omp_attributes (रूख &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  यदि (!flag_openmp && !flag_openmp_simd)
    फर्काऊ;

  लागि (रूख *pa = &attrs; *pa; )
    यदि (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	पूर्णाङ्क cnt = 0;
	लागि (रूख *pa2 = &रूख_मान (*pa); *pa2; )
	  {
	    रूख a = *pa2;
	    रूख d = रूख_मान (a);
	    gcc_assert (रूख_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    अचर वर्ण *directive[3] = {};
	    लागि (पूर्णाङ्क i = 0; i < 3; i++)
	      {
		रूख id = NULL_रूख;
		यदि (first + i == last)
		  रोक;
		यदि (first[i].type == CPP_NAME)
		  id = first[i].मान;
		अन्यथा यदि (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(पूर्णाङ्क) first[i].keyword];
		अन्यथा
		  रोक;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    अचर c_omp_directive *dir = रिक्त;
	    यदि (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    यदि (dir == रिक्त)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  रूख_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = रूख_CHAIN (a);
	      }
	    अन्यथा यदि (dir->id == PRAGMA_OMP_DECLARE
		     && (म_भेद (directive[1], "simd") == 0
			 || म_भेद (directive[1], "variant") == 0))
	      {
		यदि (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    लागि (pa = &attrs; *pa; )
		      यदि (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = रूख_CHAIN (*pa);
		      अन्यथा
			pa = &रूख_CHAIN (*pa);
		    फर्काऊ;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		लागि (++first; first < last; ++first)
		  attr_clauses->quick_थप (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_थप (tok);
		*pa2 = रूख_CHAIN (a);
	      }
	    अन्यथा
	      pa2 = &रूख_CHAIN (a);
	  }
	यदि (cnt && रूख_मान (*pa) == NULL_रूख)
	  *pa = रूख_CHAIN (*pa);
	अन्यथा
	  pa = &रूख_CHAIN (*pa);
      }
    अन्यथा
      pa = &रूख_CHAIN (*pa);
  यदि (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_थप (tok);
      attr_clauses->quick_थप (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

स्थिर रूख
c_parser_handle_musttail (c_parser *parser, रूख std_attrs, attr_state &attr)
{
  यदि (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      यदि (रूख a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  लागि (; a; a = lookup_attribute ("gnu", "musttail", रूख_CHAIN (a)))
	    यदि (रूख_मान (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = सत्य;
	}
      यदि (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = सत्य;
	}
    }
  फर्काऊ std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

स्थिर रूख
get_before_labels ()
{
  यदि (!building_stmt_list_p ())
    फर्काऊ NULL_रूख;
  रूख_stmt_iterator tsi = tsi_last (cur_stmt_list);
  यदि (tsi_end_p (tsi))
    फर्काऊ NULL_रूख;
  फर्काऊ tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

स्थिर location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  तार्किक last_stmt = असत्य;
  तार्किक last_label = असत्य;
  तार्किक save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  संरचना omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  तार्किक in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : असत्य;
  रूख sl = NULL_रूख;
  attr_state astate = {};

  यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      फर्काऊ endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  यदि (in_omp_loop_block)
    sl = थप_stmt_list ();

  mark_valid_location_for_stdc_pragma (सत्य);
  यदि (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (असत्य);
      यदि (in_omp_loop_block)
	check_omp_intervening_code (parser);
      जबसम्म (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  जबसम्म (सत्य)
	    {
	      रूख label;
	      यदि (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  रोक;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->मान);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_अभिव्यक्ति, label));
	      c_parser_consume_token (parser);
	      यदि (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      अन्यथा
		रोक;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      फर्काऊ endloc;
    }
  रूख before_labels = get_before_labels ();
  जबसम्म (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      तार्किक want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : असत्य);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      यदि (in_omp_loop_block && !last_label)
	{
	  रूख_code code = omp_for_parse_state->code;
	  यदि (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     असत्य))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (झिक_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, रिक्त));
	      omp_for_parse_state->depth--;
	      sl = थप_stmt_list ();
	      parser->error = असत्य;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      जारी;
	    }
	  अन्यथा यदि (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      रूख pre_sl = झिक_stmt_list (sl);
	      रूख nested_sl = थप_stmt_list ();
	      mark_valid_location_for_stdc_pragma (असत्य);
	      c_parser_statement_after_labels (parser, रिक्त, NULL_रूख);
	      nested_sl = झिक_stmt_list (nested_sl);
	      यदि (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = थप_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      अन्यथा
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = थप_stmt_list ();
		}
	      parser->error = असत्य;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      जारी;
	    }
	  अन्यथा यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      जारी;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      तार्किक have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      रूख std_attrs = NULL_रूख;
      यदि (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      यदि (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  यदि (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  अन्यथा
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = सत्य;
	  last_stmt = असत्य;
	  mark_valid_location_for_stdc_pragma (असत्य);
	  यदि (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      अन्यथा यदि (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = सत्य)))
	{
	  यदि (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  यदि (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = असत्य;
	    }
	  mark_valid_location_for_stdc_pragma (असत्य);
	  तार्किक fallthru_attr_p = असत्य;
	  c_parser_declaration_or_fndef (parser, सत्य, !have_std_attrs,
					 सत्य, सत्य, सत्य, असत्य, रिक्त,
					 रिक्त, have_std_attrs, std_attrs,
					 रिक्त, &fallthru_attr_p);

	  यदि (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  यदि (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = असत्य;
	  before_labels = get_before_labels ();
	}
      अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  जबसम्म (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  यदि (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      पूर्णाङ्क ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = असत्य;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      यदि (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = असत्य;
		}
	      mark_valid_location_for_stdc_pragma (असत्य);
	      c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, सत्य,
					     सत्य, असत्य);
	      यदि (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      यदि (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = असत्य;
	      before_labels = get_before_labels ();
	    }
	  अन्यथा
	    गच्छ statement;
	}
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  यदि (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  अन्यथा यदि (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  यदि (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = असत्य;
	  यदि (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       रिक्त, before_labels))
	    {
	      last_label = असत्य;
	      last_stmt = सत्य;
	      यदि (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  यदि (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  फर्काऊ c_parser_peek_token (parser)->location;
	}
      अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          यदि (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      फर्काऊ c_parser_peek_token (parser)->location;
            }
          अन्यथा
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              जारी;
            }
        }
      अन्यथा
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = असत्य;
	  last_stmt = सत्य;
	  mark_valid_location_for_stdc_pragma (असत्य);
	  यदि (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, रिक्त, before_labels,
					     रिक्त, astate);
	  अन्यथा
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = असत्य;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, रिक्त, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = असत्य;
      astate.reset ();
    }
  यदि (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  यदि (sl)
    {
      sl = झिक_stmt_list (sl);
      यदि (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      अन्यथा
	add_structured_block_stmt (sl);
    }
  फर्काऊ endloc;
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
  रूख std_attrs = रिक्त;
  यदि ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  जबसम्म (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = रिक्त;
      यदि ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  यदि (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      यदि (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  अन्यथा यदि (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  फर्काऊ attr;
}


/* Information used while parsing an OpenMP metadirective.  */
संरचना omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<रूख> * GTY((skip)) body_labels;
  अचिन्हित पूर्णाङ्क region_अङ्क;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
स्थिर रूख
mangle_metadirective_region_label (c_parser *parser, रूख name)
{
  यदि (parser->omp_metadirective_state->body_labels->contains (name))
    {
      अचर वर्ण *old_name = IDENTIFIER_POINTER (name);
      वर्ण *new_name = (वर्ण *) XALLOCAVEC (वर्ण, म_माप (old_name) + 32);
      प्र_लिखो (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_अङ्क);
      फर्काऊ get_identifier (new_name);
    }
  फर्काऊ name;
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
c_parser_label (c_parser *parser, रूख std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  रूख label = NULL_रूख;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  तार्किक fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  यदि (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      रूख exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_अभिव्यक्ति_no_commas (parser, रिक्त),
				       सत्य, सत्य).मान;
      यदि (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_रूख, std_attrs);
	}
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_अभिव्यक्ति_no_commas (parser,
								    रिक्त),
					   सत्य, सत्य).मान;
	  यदि (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      अन्यथा
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      यदि (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_रूख, NULL_रूख, std_attrs);
    }
  अन्यथा
    {
      रूख name = c_parser_peek_token (parser)->मान;
      रूख tlab;
      रूख attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      यदि (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      यदि (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_अभिव्यक्ति, tlab));
	}
      यदि (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  यदि (label)
    {
      यदि (रूख_CODE (label) == LABEL_अभिव्यक्ति)
	FALLTHROUGH_LABEL_P (LABEL_अभिव्यक्ति_LABEL (label)) = fallthrough_p;
      अन्यथा
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
  रूख before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  यदि (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = असत्य;
  c_parser_statement_after_labels (parser, if_p, before_labels, रिक्त, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

स्थिर रूख
c_parser_bc_name (c_parser *parser, तार्किक is_break)
{
  यदि (!c_parser_next_token_is (parser, CPP_NAME))
    फर्काऊ NULL_रूख;

  c_token *tok = c_parser_peek_token (parser);
  रूख label = c_finish_bc_name (tok->location, tok->मान, is_break);
  c_parser_consume_token (parser);
  फर्काऊ label;
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
				 रूख before_labels,
				 vec<रूख> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  रूख stmt = NULL_रूख;
  तार्किक in_if_block = parser->in_if_block;
  parser->in_if_block = असत्य;
  यदि (if_p != रिक्त)
    *if_p = असत्य;

  यदि (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      रोक;
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  रोक;
	पक्ष RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  रोक;
	पक्ष RID_WHILE:
	  c_parser_while_statement (parser, असत्य, 0, असत्य, if_p, before_labels);
	  रोक;
	पक्ष RID_DO:
	  c_parser_do_statement (parser, असत्य, 0, असत्य, before_labels);
	  रोक;
	पक्ष RID_FOR:
	  c_parser_for_statement (parser, असत्य, 0, असत्य, if_p, before_labels);
	  रोक;
	पक्ष RID_GOTO:
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      रूख name = c_parser_peek_token (parser)->मान;
	      यदि (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा यदि (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      संरचना c_अभिव्यक्ति val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, असत्य, सत्य);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  अन्यथा
	    c_parser_error (parser, "expected identifier or %<*%>");
	  गच्छ expect_semicolon;
	पक्ष RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, असत्य,
				   c_parser_bc_name (parser, असत्य));
	  गच्छ expect_semicolon;
	पक्ष RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, सत्य,
				   c_parser_bc_name (parser, सत्य));
	  गच्छ expect_semicolon;
	पक्ष RID_RETURN:
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_रूख, NULL_रूख,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      संरचना c_अभिव्यक्ति अभिव्यक्ति = c_parser_expression_conv (parser);
	      mark_exp_read (अभिव्यक्ति.मान);
	      stmt = c_finish_return (अभिव्यक्ति_LOC_OR_LOC (अभिव्यक्ति.मान, xloc),
				      अभिव्यक्ति.मान, अभिव्यक्ति.original_type,
				      astate.musttail_p);
	      गच्छ expect_semicolon;
	    }
	  रोक;
	पक्ष RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  रोक;
	पक्ष RID_TRANSACTION_ATOMIC:
	पक्ष RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  रोक;
	पक्ष RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  गच्छ expect_semicolon;
	पक्ष RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_रूख);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      संरचना c_अभिव्यक्ति अभिव्यक्ति = c_parser_expression (parser);
	      अभिव्यक्ति = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, असत्य, असत्य);
	      अभिव्यक्ति.मान = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
	      stmt = objc_build_throw_stmt (loc, अभिव्यक्ति.मान);
	      गच्छ expect_semicolon;
	    }
	  रोक;
	पक्ष RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  रोक;
	पक्ष RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  रोक;
	पक्ष RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    रूख attrs = c_parser_gnu_attributes (parser);
	    तार्किक has_assume = lookup_attribute ("assume", attrs);
	    यदि (has_assume)
	      {
		यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, सत्य);
		अन्यथा
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = असत्य;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    यदि (astate.musttail_p)
	      {
		यदि (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		गच्छ restart;
	      }
	    यदि (attribute_fallthrough_p (attrs))
	      {
		यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    रूख fn = build_call_अभिव्यक्ति_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_गाँठो, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		अन्यथा
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    अन्यथा यदि (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    अन्यथा यदि (attrs != NULL_रूख)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    रोक;
	  }
	स्वभाव:
	  गच्छ अभिव्यक्ति_stmt;
	}
      रोक;
    पक्ष CPP_SEMICOLON:
      c_parser_consume_token (parser);
      रोक;
    पक्ष CPP_CLOSE_PAREN:
    पक्ष CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      रोक;
    पक्ष CPP_PRAGMA:
      यदि (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        गच्छ restart;
      रोक;
    स्वभाव:
    अभिव्यक्ति_stmt:
      stmt = c_finish_अभिव्यक्ति_stmt (loc, c_parser_expression_conv (parser).मान);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      रोक;
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
  यदि (अभिव्यक्ति_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_अभिव्यक्ति_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

स्थिर रूख
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  रूख cond;
  cond = c_parser_expression_conv (parser).मान;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, असत्य, रिक्त);
  यदि (warn_sequence_point)
    verify_sequence_points (cond);
  फर्काऊ cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

स्थिर रूख
c_parser_paren_condition (c_parser *parser)
{
  रूख cond;
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ error_mark_गाँठो;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  फर्काऊ cond;
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

स्थिर c_अभिव्यक्ति
c_parser_selection_header (c_parser *parser, तार्किक switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_अभिव्यक्ति अभिव्यक्ति;
  तार्किक parse_अभिव्यक्ति = सत्य;
  रूख std_attrs;
  तार्किक have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  यदि (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  अन्यथा
    std_attrs = NULL_रूख;
  यदि (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      अभिव्यक्ति.मान
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/असत्य,
					 /*static_assert_ok=*/असत्य,
					 /*empty_ok=*/असत्य,
					 /*nested=*/सत्य,
					 /*start_attr_ok=*/सत्य,
					 /*simple_ok=*/सत्य,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      अन्यथा
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  यदि (!अभिव्यक्ति.मान)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      अभिव्यक्ति.original_type = error_mark_गाँठो;
	      अभिव्यक्ति.set_error ();
	      फर्काऊ अभिव्यक्ति;
	    }
	  parse_अभिव्यक्ति = असत्य;
	}
      यदि (अभिव्यक्ति.मान)
	{
	  अभिव्यक्ति.original_type = रूख_TYPE (अभिव्यक्ति.मान);
	  अभिव्यक्ति = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, /*convert_p=*/सत्य,
					   /*read_p=*/सत्य);
	}
    }
  अन्यथा यदि (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      अभिव्यक्ति.original_type = error_mark_गाँठो;
      अभिव्यक्ति.set_error ();
      फर्काऊ अभिव्यक्ति;
    }

  यदि (parse_अभिव्यक्ति)
    अभिव्यक्ति = c_parser_expression_conv (parser);
  यदि (!switch_p)
    {
      अभिव्यक्ति.मान = c_objc_common_truthvalue_conversion (loc, अभिव्यक्ति.मान);
      अभिव्यक्ति.मान = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
      यदि (warn_sequence_point)
	verify_sequence_points (अभिव्यक्ति.मान);
    }
  फर्काऊ अभिव्यक्ति;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

स्थिर रूख
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ error_mark_गाँठो;
  रूख cond = c_parser_selection_header (parser, /*switch_p=*/असत्य).मान;
  parens.skip_until_found_close (parser);
  फर्काऊ cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

स्थिर रूख
c_parser_c99_block_statement (c_parser *parser, तार्किक *if_p,
			      location_t *loc_after_labels)
{
  रूख block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  फर्काऊ c_end_compound_stmt (loc, block, flag_isoc99);
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

स्थिर रूख
c_parser_if_body (c_parser *parser, तार्किक *if_p,
		  अचर token_indent_info &if_tinfo)
{
  रूख block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  रूख before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      यदि (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  अन्यथा यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  अन्यथा
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, रिक्त, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  यदि (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  फर्काऊ c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

स्थिर रूख
c_parser_else_body (c_parser *parser, अचर token_indent_info &else_tinfo,
		    vec<रूख> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  रूख block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  रूख before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  अन्यथा
    {
      यदि (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, रिक्त, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  यदि (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  फर्काऊ c_end_compound_stmt (body_loc, block, flag_isoc99);
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
c_parser_if_statement (c_parser *parser, तार्किक *if_p, vec<रूख> *chain)
{
  रूख block;
  location_t loc;
  रूख cond;
  तार्किक nested_if = असत्य;
  रूख first_body, second_body;
  तार्किक in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = सत्य;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  यदि (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (अभिव्यक्ति_LOCATION (cond), cond, &chain);

  यदि (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      यदि (warn_duplicated_cond)
	{
	  यदि (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == रिक्त)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = नूतन vec<रूख> ();
	      यदि (!CONSTANT_CLASS_P (cond) && !रूख_SIDE_EFFECTS (cond))
		chain->safe_थप (cond);
	    }
	  अन्यथा यदि (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      यदि (if_p != रिक्त)
	*if_p = सत्य;
    }
  अन्यथा
    {
      second_body = NULL_रूख;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      यदि (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      यदि (warn_duplicated_cond)
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
c_parser_switch_statement (c_parser *parser, तार्किक *if_p, रूख before_labels)
{
  संरचना c_अभिव्यक्ति ce;
  रूख block, अभिव्यक्ति, body;
  अचिन्हित वर्ण save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  रूख switch_name;
  पूर्णाङ्क अङ्क_names = c_get_loop_names (before_labels, सत्य, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  तार्किक explicit_cast_p = असत्य;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = सत्य;
      ce = c_parser_selection_header (parser, /*switch_p=*/सत्य);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, सत्य, सत्य);
      अभिव्यक्ति = ce.मान;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      अभिव्यक्ति = error_mark_गाँठो;
      ce.original_type = error_mark_गाँठो;
    }
  रूख stmt
    = c_start_switch (switch_loc, switch_cond_loc, अभिव्यक्ति, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  यदि (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  अन्यथा
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  तार्किक open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  यदि (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  यदि (अङ्क_names)
    {
      यदि (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_रूख;
      अन्यथा
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (अङ्क_names);
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
c_parser_while_statement (c_parser *parser, तार्किक ivdep, अचिन्हित लघु unroll,
			  तार्किक novector, तार्किक *if_p, रूख before_labels)
{
  रूख block, cond, body;
  अचिन्हित वर्ण save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  रूख loop_name;
  पूर्णाङ्क अङ्क_names = c_get_loop_names (before_labels, असत्य, &loop_name);

  यदि (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = सत्य;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  यदि (ivdep && cond != error_mark_गाँठो)
    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठो,
				  annot_अभिव्यक्ति_ivdep_kind),
		   integer_zero_गाँठो);
  यदि (unroll && cond != error_mark_गाँठो)
    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठो,
				  annot_अभिव्यक्ति_unroll_kind),
		   build_int_cst (integer_type_गाँठो, unroll));
  यदि (novector && cond != error_mark_गाँठो)
    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठो,
				  annot_अभिव्यक्ति_no_vector_kind),
		   integer_zero_गाँठो);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  यदि (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  तार्किक open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  यदि (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_रूख;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_रूख,
			NULL_रूख));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  यदि (अङ्क_names)
    c_release_loop_names (अङ्क_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  यदि (next_tinfo.type != CPP_SEMICOLON && !open_brace)
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
c_parser_do_statement (c_parser *parser, तार्किक ivdep, अचिन्हित लघु unroll,
		       तार्किक novector, रूख before_labels)
{
  रूख block, cond, body;
  अचिन्हित वर्ण save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  रूख loop_name;
  पूर्णाङ्क अङ्क_names = c_get_loop_names (before_labels, असत्य, &loop_name);

  यदि (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = सत्य;
    }

  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  यदि (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, रिक्त);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  यदि (अङ्क_names)
    {
      यदि (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_रूख;
      c_release_loop_names (अङ्क_names);
    }
  cond = c_parser_paren_condition (parser);
  यदि (ivdep && cond != error_mark_गाँठो)
    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठो,
				  annot_अभिव्यक्ति_ivdep_kind),
		   integer_zero_गाँठो);
  यदि (unroll && cond != error_mark_गाँठो)
    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठो,
				  annot_अभिव्यक्ति_unroll_kind),
 		   build_int_cst (integer_type_गाँठो, unroll));
  यदि (novector && cond != error_mark_गाँठो)
    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठो,
				  annot_अभिव्यक्ति_no_vector_kind),
		   integer_zero_गाँठो);
  यदि (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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
c_parser_for_statement (c_parser *parser, तार्किक ivdep, अचिन्हित लघु unroll,
			तार्किक novector, तार्किक *if_p, रूख before_labels)
{
  रूख block, cond, incr, body;
  अचिन्हित वर्ण save_in_statement;
  रूख save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  रूख object_expression;
  /* Silence the bogus uninitialized warning.  */
  रूख collection_expression = रिक्त;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  तार्किक is_foreach_statement = असत्य;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  रूख loop_name;
  पूर्णाङ्क अङ्क_names = c_get_loop_names (before_labels, असत्य, &loop_name);

  यदि (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = सत्य;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_गाँठो;
  incr = error_mark_गाँठो;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_गाँठो;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = असत्य;
	  c_parser_consume_token (parser);
	  c_finish_अभिव्यक्ति_stmt (loc, NULL_रूख);
	}
      अन्यथा यदि (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, सत्य, सत्य,
					 असत्य, &object_expression);
	  parser->objc_could_be_foreach_context = असत्य;

	  यदि (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = सत्य;
	      यदि (check_for_loop_decls (for_loc, सत्य) == NULL_रूख)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  अन्यथा
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  जबसम्म (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  यदि (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      पूर्णाङ्क ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, सत्य,
					     सत्य, असत्य, &object_expression);
	      parser->objc_could_be_foreach_context = असत्य;

	      restore_extension_diagnostics (ext);
	      यदि (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = सत्य;
		  यदि (check_for_loop_decls (for_loc, सत्य) == NULL_रूख)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      अन्यथा
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  अन्यथा
	    गच्छ init_अभिव्यक्ति;
	}
      अन्यथा
	{
	init_अभिव्यक्ति:
	  {
	    संरचना c_अभिव्यक्ति ce;
	    रूख init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.मान;
	    parser->objc_could_be_foreach_context = असत्य;
	    यदि (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = सत्य;
		यदि (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, असत्य, रिक्त);
	      }
	    अन्यथा
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, सत्य, असत्य);
		init_expression = ce.मान;
		c_finish_अभिव्यक्ति_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      यदि (!is_foreach_statement)
	{
	  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      यदि (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_गाँठो;
		}
	      अन्यथा यदि (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_गाँठो;
		}
	      अन्यथा
		{
		  c_parser_consume_token (parser);
		  cond = NULL_रूख;
		}
	    }
	  अन्यथा
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  यदि (ivdep && cond != error_mark_गाँठो)
	    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
			   build_int_cst (integer_type_गाँठो,
					  annot_अभिव्यक्ति_ivdep_kind),
			   integer_zero_गाँठो);
	  यदि (unroll && cond != error_mark_गाँठो)
	    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
 			   build_int_cst (integer_type_गाँठो,
					  annot_अभिव्यक्ति_unroll_kind),
			   build_int_cst (integer_type_गाँठो, unroll));
	  यदि (novector && cond && cond != error_mark_गाँठो)
	    cond = build3 (ANNOTATE_अभिव्यक्ति, रूख_TYPE (cond), cond,
			   build_int_cst (integer_type_गाँठो,
					  annot_अभिव्यक्ति_no_vector_kind),
			   integer_zero_गाँठो);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  यदि (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_गाँठो;
	    }
	  अन्यथा
	    incr = c_process_अभिव्यक्ति_stmt (loc, NULL_रूख);
	}
      अन्यथा
	{
	  यदि (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).मान, असत्य, रिक्त);
	  अन्यथा
	    {
	      संरचना c_अभिव्यक्ति ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, सत्य, असत्य);
	      incr = c_process_अभिव्यक्ति_stmt (loc, ce.मान);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  यदि (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      यदि (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  अन्यथा
    in_statement = IN_ITERATION_STMT;
  यदि (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  तार्किक open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  यदि (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_रूख;
      DECL_CHAIN (objc_foreach_break_label) = NULL_रूख;
    }

  यदि (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  अन्यथा
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_रूख, cond, incr,
			  body, NULL_रूख,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_रूख, NULL_रूख, NULL_रूख));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  यदि (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  यदि (अङ्क_names)
    c_release_loop_names (अङ्क_names);
  यदि (is_foreach_statement)
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

स्थिर रूख
c_parser_asm_statement (c_parser *parser)
{
  रूख str, outputs, inputs, clobbers, labels, ret;
  तार्किक simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  पूर्णाङ्क section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  लागि (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      विकल्प (token->keyword)
	{
	पक्ष RID_VOLATILE:
	  यदि (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मान);
	      inform (volatile_loc, "first seen here");
	    }
	  अन्यथा
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  जारी;

	पक्ष RID_INLINE:
	  यदि (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मान);
	      inform (inline_loc, "first seen here");
	    }
	  अन्यथा
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  जारी;

	पक्ष RID_GOTO:
	  यदि (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मान);
	      inform (goto_loc, "first seen here");
	    }
	  अन्यथा
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  जारी;

	पक्ष RID_CONST:
	पक्ष RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->मान);
	  c_parser_consume_token (parser);
	  जारी;

	स्वभाव:
	  रोक;
	}
      रोक;
    }

  तार्किक is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  तार्किक is_inline = (inline_loc != UNKNOWN_LOCATION);
  तार्किक is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = रिक्त;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    गच्छ error;

  str = c_parser_asm_string_literal (parser);
  यदि (str == NULL_रूख)
    गच्छ error_close_paren;

  simple = सत्य;
  outputs = NULL_रूख;
  inputs = NULL_रूख;
  clobbers = NULL_रूख;
  labels = NULL_रूख;

  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    गच्छ done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  लागि (section = 0; section < nsections; ++section)
    {
      यदि (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  यदि (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      गच्छ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	गच्छ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = असत्य;

      यदि ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	विकल्प (section)
	  {
	  पक्ष 0:
	    outputs = c_parser_asm_operands (parser);
	    रोक;
	  पक्ष 1:
	    inputs = c_parser_asm_operands (parser);
	    रोक;
	  पक्ष 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    रोक;
	  पक्ष 3:
	    labels = c_parser_asm_goto_operands (parser);
	    रोक;
	  स्वभाव:
	    gcc_unreachable ();
	  }

      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	गच्छ done_asm;
    }

 done_asm:
  यदि (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      गच्छ error;
    }

  यदि (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_अभिव्यक्ति (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  फर्काऊ ret;

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

स्थिर रूख
c_parser_asm_operands (c_parser *parser)
{
  रूख list = NULL_रूख;
  जबसम्म (सत्य)
    {
      रूख name, str;
      संरचना c_अभिव्यक्ति अभिव्यक्ति;
      यदि (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      रूख id = c_parser_peek_token (parser)->मान;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, रिक्त);
	      फर्काऊ NULL_रूख;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      अन्यथा
	name = NULL_रूख;
      str = c_parser_asm_string_literal (parser);
      यदि (str == NULL_रूख)
	फर्काऊ NULL_रूख;
      matching_parens parens;
      यदि (!parens.require_open (parser))
	फर्काऊ NULL_रूख;
      अभिव्यक्ति = c_parser_expression (parser);
      mark_exp_read (अभिव्यक्ति.मान);
      यदि (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  फर्काऊ NULL_रूख;
	}
      list = chainon (list, build_रूख_list (build_रूख_list (name, str),
					     अभिव्यक्ति.मान));
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
    }
  फर्काऊ list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

स्थिर रूख
c_parser_asm_clobbers (c_parser *parser)
{
  रूख list = NULL_रूख;
  जबसम्म (सत्य)
    {
      रूख str = c_parser_asm_string_literal (parser);
      यदि (str)
	list = रूख_cons (NULL_रूख, str, list);
      अन्यथा
	फर्काऊ NULL_रूख;
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
    }
  फर्काऊ list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

स्थिर रूख
c_parser_asm_goto_operands (c_parser *parser)
{
  रूख list = NULL_रूख;
  जबसम्म (सत्य)
    {
      रूख name, label;

      यदि (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->मान;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  रूख_USED (label) = 1;
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected identifier");
	  फर्काऊ NULL_रूख;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = रूख_cons (name, label, list);
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	फर्काऊ nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

संरचना c_अभिव्यक्ति
c_parser_string_literal (c_parser *parser, तार्किक translate, तार्किक wide_ok)
{
  संरचना c_अभिव्यक्ति ret;
  माप_प्रकार गन्ती;
  संरचना obstack str_ob;
  संरचना obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  गणना cpp_ttype type;
  रूख मान, string_रूख;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (पङ्क्ति_table, loc,
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
      string_रूख = tok->मान;
      रोक;

    स्वभाव:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.मान = NULL_रूख;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_रूख;
      फर्काऊ ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  विकल्प (c_parser_peek_2nd_token (parser)->type)
    {
    स्वभाव:
      c_parser_consume_token (parser);
      str.text = (अचर अचिन्हित वर्ण *) रूख_STRING_POINTER (string_रूख);
      str.len = रूख_STRING_LENGTH (string_रूख);
      गन्ती = 1;
      strs = &str;
      रोक;

    पक्ष CPP_STRING:
    पक्ष CPP_WSTRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      गन्ती = 0;
      गर
	{
	  c_parser_consume_token (parser);
	  गन्ती++;
	  str.text = (अचर अचिन्हित वर्ण *) रूख_STRING_POINTER (string_रूख);
	  str.len = रूख_STRING_LENGTH (string_रूख);
	  यदि (type != tok->type)
	    {
	      यदि (type == CPP_STRING)
		type = tok->type;
	      अन्यथा यदि (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, परिमाण (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, परिमाण (location_t));
	  tok = c_parser_peek_token (parser);
	  string_रूख = tok->मान;
	  last_tok_loc
	    = linemap_resolve_location (पङ्क्ति_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, रिक्त);
	}
      जबसम्म (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  यदि (गन्ती > 1 && !in_system_header_at (आगत_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  यदि ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, गन्ती, &istr, type)))
    {
      मान = build_string (istr.len, (अचर वर्ण *) istr.text);
      मुक्त (const_cast<अचिन्हित वर्ण *> (istr.text));
      यदि (गन्ती > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (गन्ती, locs);
	}
    }
  अन्यथा
    {
      यदि (type != CPP_STRING && !wide_ok)
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
	  यदि (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      मान = build_string (TYPE_PRECISION (char8_type_गाँठो)
				    / TYPE_PRECISION (char_type_गाँठो),
				    "");  /* char8_t is 8 bits */
	    }
	  अन्यथा
	    मान = build_string (1, "");
	  रोक;
	पक्ष CPP_STRING16:
	  मान = build_string (TYPE_PRECISION (char16_type_गाँठो)
				/ TYPE_PRECISION (char_type_गाँठो),
				"\0");  /* char16_t is 16 bits */
	  रोक;
	पक्ष CPP_STRING32:
	  मान = build_string (TYPE_PRECISION (char32_type_गाँठो)
				/ TYPE_PRECISION (char_type_गाँठो),
				"\0\0\0");  /* char32_t is 32 bits */
	  रोक;
	पक्ष CPP_WSTRING:
	  मान = build_string (TYPE_PRECISION (wchar_type_गाँठो)
				/ TYPE_PRECISION (char_type_गाँठो),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  रोक;
        }
    }

  विकल्प (type)
    {
    स्वभाव:
    पक्ष CPP_STRING:
      रूख_TYPE (मान) = char_array_type_गाँठो;
      रोक;
    पक्ष CPP_UTF8STRING:
      यदि (flag_char8_t)
	रूख_TYPE (मान) = char8_array_type_गाँठो;
      अन्यथा
	रूख_TYPE (मान) = char_array_type_गाँठो;
      रोक;
    पक्ष CPP_STRING16:
      रूख_TYPE (मान) = char16_array_type_गाँठो;
      रोक;
    पक्ष CPP_STRING32:
      रूख_TYPE (मान) = char32_array_type_गाँठो;
      रोक;
    पक्ष CPP_WSTRING:
      रूख_TYPE (मान) = wchar_array_type_गाँठो;
    }
  मान = fix_string_type (मान);

  यदि (गन्ती > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.मान = मान;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_रूख;
  set_c_अभिव्यक्ति_source_range (&ret, get_range_from_loc (पङ्क्ति_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = सत्य;
  फर्काऊ ret;
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_अभिव्यक्ति_no_commas (c_parser *parser, संरचना c_अभिव्यक्ति *after,
			 रूख omp_atomic_lhs)
{
  संरचना c_अभिव्यक्ति lhs, rhs, ret;
  गणना रूख_code code;
  location_t op_location, exp_location;
  तार्किक save_in_omp_for = c_in_omp_for;
  c_in_omp_for = असत्य;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_EQ:
      code = NOP_अभिव्यक्ति;
      रोक;
    पक्ष CPP_MULT_EQ:
      code = MULT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_DIV_EQ:
      code = TRUNC_DIV_अभिव्यक्ति;
      रोक;
    पक्ष CPP_MOD_EQ:
      code = TRUNC_MOD_अभिव्यक्ति;
      रोक;
    पक्ष CPP_PLUS_EQ:
      code = PLUS_अभिव्यक्ति;
      रोक;
    पक्ष CPP_MINUS_EQ:
      code = MINUS_अभिव्यक्ति;
      रोक;
    पक्ष CPP_LSHIFT_EQ:
      code = LSHIFT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_RSHIFT_EQ:
      code = RSHIFT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_AND_EQ:
      code = BIT_AND_अभिव्यक्ति;
      रोक;
    पक्ष CPP_XOR_EQ:
      code = BIT_XOR_अभिव्यक्ति;
      रोक;
    पक्ष CPP_OR_EQ:
      code = BIT_IOR_अभिव्यक्ति;
      रोक;
    स्वभाव:
      c_in_omp_for = save_in_omp_for;
      फर्काऊ lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, सत्य, सत्य);

  ret.मान = build_modify_अभिव्यक्ति (op_location, lhs.मान, lhs.original_type,
				 code, exp_location, rhs.मान,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_अभिव्यक्ति_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  यदि (code == NOP_अभिव्यक्ति)
    ret.original_code = MODIFY_अभिव्यक्ति;
  अन्यथा
    {
      suppress_warning (ret.मान, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = रिक्त;
  c_in_omp_for = save_in_omp_for;
  फर्काऊ ret;
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_conditional_expression (c_parser *parser, संरचना c_अभिव्यक्ति *after,
				 रूख omp_atomic_lhs)
{
  संरचना c_अभिव्यक्ति cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_द्विआधारी_expression (parser, after, omp_atomic_lhs);

  यदि (c_parser_next_token_is_not (parser, CPP_QUERY))
    फर्काऊ cond;
  c_omp_array_section_p = असत्य;
  यदि (cond.मान != error_mark_गाँठो)
    start = cond.get_start ();
  अन्यथा
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, सत्य, सत्य);
  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is (parser, CPP_COLON))
    {
      रूख eptype = NULL_रूख;

      location_t बीच_loc = c_parser_peek_token (parser)->location;
      pedwarn (बीच_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      यदि (रूख_CODE (cond.मान) == EXCESS_PRECISION_अभिव्यक्ति)
	{
	  eptype = रूख_TYPE (cond.मान);
	  cond.मान = रूख_OPERAND (cond.मान, 0);
	}
      रूख e = cond.मान;
      जबसम्म (रूख_CODE (e) == COMPOUND_अभिव्यक्ति)
	e = रूख_OPERAND (e, 1);
      warn_for_omitted_condop (बीच_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.मान = save_अभिव्यक्ति (default_conversion (cond.मान));
      यदि (eptype)
	exp1.मान = build1 (EXCESS_PRECISION_अभिव्यक्ति, eptype, exp1.मान);
      exp1.original_type = रिक्त;
      exp1.src_range = cond.src_range;
      cond.मान = c_objc_common_truthvalue_conversion (cond_loc, exp1.मान);
      c_inhibit_evaluation_warnings += cond.मान == truthvalue_true_गाँठो;
    }
  अन्यथा
    {
      cond.मान
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.मान));
      c_inhibit_evaluation_warnings += cond.मान == truthvalue_false_गाँठो;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.मान);
      c_inhibit_evaluation_warnings +=
	((cond.मान == truthvalue_true_गाँठो)
	 - (cond.मान == truthvalue_false_गाँठो));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.मान == truthvalue_true_गाँठो;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      c_omp_array_section_p = save_c_omp_array_section_p;
      फर्काऊ ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, रिक्त, NULL_रूख);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, सत्य, सत्य);
  }
  c_inhibit_evaluation_warnings -= cond.मान == truthvalue_true_गाँठो;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  यदि (UNLIKELY (omp_atomic_lhs != रिक्त)
      && (रूख_CODE (cond.मान) == GT_अभिव्यक्ति
	  || रूख_CODE (cond.मान) == LT_अभिव्यक्ति
	  || रूख_CODE (cond.मान) == EQ_अभिव्यक्ति)
      && c_रूख_equal (exp2.मान, omp_atomic_lhs)
      && (c_रूख_equal (रूख_OPERAND (cond.मान, 0), omp_atomic_lhs)
	  || c_रूख_equal (रूख_OPERAND (cond.मान, 1), omp_atomic_lhs)))
    ret.मान = build3_loc (colon_loc, COND_अभिव्यक्ति, रूख_TYPE (omp_atomic_lhs),
			    cond.मान, exp1.मान, exp2.मान);
  अन्यथा
    ret.मान
      = build_conditional_अभिव्यक्ति (colon_loc, cond.मान,
				cond.original_code == C_MAYBE_CONST_अभिव्यक्ति,
				exp1.मान, exp1.original_type, loc1,
				exp2.मान, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  यदि (exp1.मान == error_mark_गाँठो || exp2.मान == error_mark_गाँठो)
    ret.original_type = रिक्त;
  अन्यथा
    {
      रूख t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : रूख_TYPE (exp1.मान);
      t2 = exp2.original_type ? exp2.original_type : रूख_TYPE (exp2.मान);
      ret.original_type = ((t1 != error_mark_गाँठो
			    && t2 != error_mark_गाँठो
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : रिक्त);
    }
  set_c_अभिव्यक्ति_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  फर्काऊ ret;
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_द्विआधारी_expression (c_parser *parser, संरचना c_अभिव्यक्ति *after,
			    रूख omp_atomic_lhs)
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
    संरचना c_अभिव्यक्ति अभिव्यक्ति;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    गणना c_parser_prec prec;
    /* The operation on its left.  */
    गणना रूख_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    रूख sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    रूख orig_अभिव्यक्ति;
  } थाक[अङ्क_PRECS];
  पूर्णाङ्क sp;
  /* Location of the binary operator.  */
  location_t द्विआधारी_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define झिक_2								      \
  गर {									      \
    विकल्प (थाक[sp].op)						      \
      {									      \
      पक्ष TRUTH_ANDIF_अभिव्यक्ति:						      \
	c_inhibit_evaluation_warnings -= (थाक[sp - 1].अभिव्यक्ति.मान	      \
					  == truthvalue_false_गाँठो);	      \
	रोक;								      \
      पक्ष TRUTH_ORIF_अभिव्यक्ति:						      \
	c_inhibit_evaluation_warnings -= (थाक[sp - 1].अभिव्यक्ति.मान	      \
					  == truthvalue_true_गाँठो);	      \
	रोक;								      \
      पक्ष TRUNC_DIV_अभिव्यक्ति:						      \
	यदि ((थाक[sp - 1].अभिव्यक्ति.original_code == SIZEOF_अभिव्यक्ति		      \
	     || थाक[sp - 1].अभिव्यक्ति.original_code == PAREN_SIZEOF_अभिव्यक्ति)	      \
	    && (थाक[sp].अभिव्यक्ति.original_code == SIZEOF_अभिव्यक्ति		      \
		|| थाक[sp].अभिव्यक्ति.original_code == PAREN_SIZEOF_अभिव्यक्ति))	      \
	  {								      \
	    रूख type0 = थाक[sp - 1].sizeof_arg;			      \
	    रूख type1 = थाक[sp].sizeof_arg;				      \
	    रूख first_arg = type0;					      \
	    यदि (!TYPE_P (type0))					      \
	      type0 = रूख_TYPE (type0);				      \
	    यदि (!TYPE_P (type1))					      \
	      type1 = रूख_TYPE (type1);				      \
	    यदि (POINTER_TYPE_P (type0)					      \
		&& comptypes (रूख_TYPE (type0), type1)			      \
		&& !(रूख_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		यदि (warning_at (थाक[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  यदि (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    अन्यथा यदि (रूख_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (रूख_TYPE (type0)))  \
		     && थाक[sp].अभिव्यक्ति.original_code != PAREN_SIZEOF_अभिव्यक्ति)    \
	      maybe_warn_sizeof_array_div (थाक[sp].loc, first_arg, type0,   \
					   थाक[sp].sizeof_arg, type1);      \
	  }								      \
	रोक;								      \
      स्वभाव:								      \
	रोक;								      \
      }									      \
    थाक[sp - 1].अभिव्यक्ति							      \
      = convert_lvalue_to_rvalue (थाक[sp - 1].loc,			      \
				  थाक[sp - 1].अभिव्यक्ति, सत्य, सत्य);	      \
    थाक[sp].अभिव्यक्ति							      \
      = convert_lvalue_to_rvalue (थाक[sp].loc,			      \
				  थाक[sp].अभिव्यक्ति, सत्य, सत्य);		      \
    यदि (UNLIKELY (omp_atomic_lhs != NULL_रूख) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << थाक[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_गाँठो			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (थाक[sp].prec == PREC_REL || थाक[sp].prec == PREC_EQ)))\
	&& थाक[sp].op != TRUNC_MOD_अभिव्यक्ति				      \
	&& थाक[sp].op != GE_अभिव्यक्ति					      \
	&& थाक[sp].op != LE_अभिव्यक्ति					      \
	&& थाक[sp].op != NE_अभिव्यक्ति					      \
	&& थाक[0].अभिव्यक्ति.मान != error_mark_गाँठो			      \
	&& थाक[1].अभिव्यक्ति.मान != error_mark_गाँठो			      \
	&& (omp_atomic_lhs == void_list_गाँठो				      \
	    || c_रूख_equal (थाक[0].अभिव्यक्ति.मान, omp_atomic_lhs)	      \
	    || c_रूख_equal (थाक[1].अभिव्यक्ति.मान, omp_atomic_lhs)	      \
	    || (थाक[sp].op == EQ_अभिव्यक्ति					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	रूख t = make_गाँठो (थाक[1].op);				      \
	रूख_TYPE (t) = रूख_TYPE (थाक[0].अभिव्यक्ति.मान);		      \
	रूख_OPERAND (t, 0) = थाक[0].अभिव्यक्ति.मान;			      \
	रूख_OPERAND (t, 1) = थाक[1].अभिव्यक्ति.मान;			      \
	थाक[0].अभिव्यक्ति.मान = t;					      \
	थाक[0].अभिव्यक्ति.m_decimal = 0;					      \
      }									      \
    अन्यथा								      \
      थाक[sp - 1].अभिव्यक्ति = parser_build_द्विआधारी_op (थाक[sp].loc,	      \
						   थाक[sp].op,	      \
						   थाक[sp - 1].अभिव्यक्ति,	      \
						   थाक[sp].अभिव्यक्ति,	      \
						   थाक[sp - 1].orig_अभिव्यक्ति);  \
    थाक[sp - 1].orig_अभिव्यक्ति = NULL_रूख;				      \
    sp--;								      \
  } जबसम्म (0)
  gcc_assert (!after || c_dialect_objc ());
  थाक[0].loc = c_parser_peek_token (parser)->location;
  थाक[0].अभिव्यक्ति = c_parser_cast_expression (parser, after);
  थाक[0].prec = PREC_NONE;
  थाक[0].sizeof_arg = c_last_sizeof_arg;
  थाक[0].orig_अभिव्यक्ति = NULL_रूख;
  sp = 0;
  जबसम्म (सत्य)
    {
      गणना c_parser_prec oprec;
      गणना रूख_code ocode;
      source_range src_range;
      यदि (parser->error)
	गच्छ out;
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_अभिव्यक्ति;
	  रोक;
	स्वभाव:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  गच्छ out;
	}
      द्विआधारी_loc = c_parser_peek_token (parser)->location;
      जबसम्म (oprec <= थाक[sp].prec)
	झिक_2;
      c_parser_consume_token (parser);
      विकल्प (ocode)
	{
	पक्ष TRUTH_ANDIF_अभिव्यक्ति:
	  src_range = थाक[sp].अभिव्यक्ति.src_range;
	  थाक[sp].अभिव्यक्ति
	    = convert_lvalue_to_rvalue (थाक[sp].loc,
					थाक[sp].अभिव्यक्ति, सत्य, सत्य);
	  थाक[sp].orig_अभिव्यक्ति = थाक[sp].अभिव्यक्ति.मान;
	  थाक[sp].अभिव्यक्ति.मान = c_objc_common_truthvalue_conversion
	    (थाक[sp].loc, default_conversion (थाक[sp].अभिव्यक्ति.मान));
	  c_inhibit_evaluation_warnings += (थाक[sp].अभिव्यक्ति.मान
					    == truthvalue_false_गाँठो);
	  set_c_अभिव्यक्ति_source_range (&थाक[sp].अभिव्यक्ति, src_range);
	  रोक;
	पक्ष TRUTH_ORIF_अभिव्यक्ति:
	  src_range = थाक[sp].अभिव्यक्ति.src_range;
	  थाक[sp].अभिव्यक्ति
	    = convert_lvalue_to_rvalue (थाक[sp].loc,
					थाक[sp].अभिव्यक्ति, सत्य, सत्य);
	  थाक[sp].orig_अभिव्यक्ति = थाक[sp].अभिव्यक्ति.मान;
	  थाक[sp].अभिव्यक्ति.मान = c_objc_common_truthvalue_conversion
	    (थाक[sp].loc, default_conversion (थाक[sp].अभिव्यक्ति.मान));
	  c_inhibit_evaluation_warnings += (थाक[sp].अभिव्यक्ति.मान
					    == truthvalue_true_गाँठो);
	  set_c_अभिव्यक्ति_source_range (&थाक[sp].अभिव्यक्ति, src_range);
	  रोक;
	स्वभाव:
	  रोक;
	}
      sp++;
      थाक[sp].loc = द्विआधारी_loc;
      थाक[sp].अभिव्यक्ति = c_parser_cast_expression (parser, रिक्त);
      थाक[sp].prec = oprec;
      थाक[sp].op = ocode;
      थाक[sp].sizeof_arg = c_last_sizeof_arg;
      थाक[sp].orig_अभिव्यक्ति = NULL_रूख;
    }
 out:
  जबसम्म (sp > 0)
    झिक_2;
  फर्काऊ थाक[0].अभिव्यक्ति;
#undef झिक_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

स्थिर संरचना c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  तार्किक seen_scspec = असत्य;
  संरचना c_declspecs *specs = build_null_declspecs ();
  जबसम्म (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_CONSTEXPR:
	पक्ष RID_REGISTER:
	पक्ष RID_STATIC:
	पक्ष RID_THREAD:
	  seen_scspec = सत्य;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->मान);
	  c_parser_consume_token (parser);
	  रोक;
	स्वभाव:
	  गच्छ out;
	}
    }
 out:
  फर्काऊ seen_scspec ? specs : रिक्त;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

स्थिर संरचना c_अभिव्यक्ति
c_parser_cast_expression (c_parser *parser, संरचना c_अभिव्यक्ति *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  यदि (after)
    फर्काऊ c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      संरचना c_declspecs *scspecs;
      संरचना c_type_name *type_name;
      संरचना c_अभिव्यक्ति ret;
      संरचना c_अभिव्यक्ति अभिव्यक्ति;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, सत्य);
      parens.skip_until_found_close (parser);
      यदि (type_name == रिक्त)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = रिक्त;
	  फर्काऊ ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_घुसाउ (type_name->specs->type);

      यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	फर्काऊ c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      यदि (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      यदि (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
	अभिव्यक्ति = c_parser_cast_expression (parser, रिक्त);
	अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, सत्य, सत्य);
      }
      ret.मान = c_cast_अभिव्यक्ति (cast_loc, type_name, अभिव्यक्ति.मान);
      यदि (ret.मान && अभिव्यक्ति.मान)
	set_c_अभिव्यक्ति_source_range (&ret, cast_loc, अभिव्यक्ति.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      फर्काऊ ret;
    }
  अन्यथा
    फर्काऊ c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

स्थिर शून्य
mark_exp_read_cond (रूख exp)
{
  यदि ((VAR_P (exp) || रूख_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    फर्काऊ;

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

स्थिर संरचना c_अभिव्यक्ति
c_parser_unary_expression (c_parser *parser)
{
  पूर्णाङ्क ext;
  संरचना c_अभिव्यक्ति ret, op;
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
      mark_exp_read_cond (op.मान);
      op = default_function_array_conversion (exp_loc, op);
      फर्काऊ parser_build_unary_op (op_loc, PREINCREMENT_अभिव्यक्ति, op);
    पक्ष CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      mark_exp_read_cond (op.मान);
      op = default_function_array_conversion (exp_loc, op);
      फर्काऊ parser_build_unary_op (op_loc, PREDECREMENT_अभिव्यक्ति, op);
    पक्ष CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, रिक्त);
      mark_exp_read (op.मान);
      फर्काऊ parser_build_unary_op (op_loc, ADDR_अभिव्यक्ति, op);
    पक्ष CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, रिक्त);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, सत्य, सत्य);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.मान = build_indirect_ref (combined_loc, op.मान, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	फर्काऊ ret;
      }
    पक्ष CPP_PLUS:
      यदि (!c_dialect_objc () && !in_system_header_at (आगत_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      op = convert_lvalue_to_rvalue (exp_loc, op, सत्य, सत्य);
      फर्काऊ parser_build_unary_op (op_loc, CONVERT_अभिव्यक्ति, op);
    पक्ष CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      op = convert_lvalue_to_rvalue (exp_loc, op, सत्य, सत्य);
      फर्काऊ parser_build_unary_op (op_loc, NEGATE_अभिव्यक्ति, op);
    पक्ष CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      op = convert_lvalue_to_rvalue (exp_loc, op, सत्य, सत्य);
      फर्काऊ parser_build_unary_op (op_loc, BIT_NOT_अभिव्यक्ति, op);
    पक्ष CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, रिक्त);
      op = convert_lvalue_to_rvalue (exp_loc, op, सत्य, सत्य);
      फर्काऊ parser_build_unary_op (op_loc, TRUTH_NOT_अभिव्यक्ति, op);
    पक्ष CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.मान = finish_label_address_अभिव्यक्ति
	    (c_parser_peek_token (parser)->मान, op_loc);
	  set_c_अभिव्यक्ति_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      फर्काऊ ret;
    पक्ष CPP_KEYWORD:
      {
	गणना rid rid = c_parser_peek_token (parser)->keyword;
	विकल्प (rid)
	  {
	  पक्ष RID_COUNTOF:
	  पक्ष RID_SIZEOF:
	    फर्काऊ c_parser_sizeof_or_countof_expression (parser, rid);
	  पक्ष RID_ALIGNOF:
	    फर्काऊ c_parser_alignof_expression (parser);
	  पक्ष RID_MAXOF:
	  पक्ष RID_MINOF:
	    फर्काऊ c_parser_maxof_or_minof_expression (parser, rid);
	  पक्ष RID_BUILTIN_HAS_ATTRIBUTE:
	    फर्काऊ c_parser_has_attribute_expression (parser);
	  पक्ष RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, रिक्त);
	    restore_extension_diagnostics (ext);
	    फर्काऊ ret;
	  पक्ष RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, रिक्त);
	    op = default_function_array_conversion (exp_loc, op);
	    फर्काऊ parser_build_unary_op (op_loc, REALPART_अभिव्यक्ति, op);
	  पक्ष RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, रिक्त);
	    op = default_function_array_conversion (exp_loc, op);
	    फर्काऊ parser_build_unary_op (op_loc, IMAGPART_अभिव्यक्ति, op);
	  पक्ष RID_TRANSACTION_ATOMIC:
	  पक्ष RID_TRANSACTION_RELAXED:
	    फर्काऊ c_parser_transaction_expression (parser, rid);
	  पक्ष RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.मान = void_गाँठो;
	    set_c_अभिव्यक्ति_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    फर्काऊ ret;
	  स्वभाव:
	    फर्काऊ c_parser_postfix_expression (parser);
	  }
      }
    स्वभाव:
      फर्काऊ c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_sizeof_or_countof_expression (c_parser *parser, गणना rid rid)
{
  अचर वर्ण *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  संरचना c_अभिव्यक्ति result;
  location_t अभिव्यक्ति_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  यदि (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  यदि (rid == RID_COUNTOF)
    in_countof++;
  अन्यथा
    in_sizeof++;
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      संरचना c_declspecs *scspecs;
      संरचना c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, सत्य);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      यदि (type_name == रिक्त)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  अभिव्यक्ति.set_error ();
	  गच्छ Xof_अभिव्यक्ति;
	}
      यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  अभिव्यक्ति = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       अभिव्यक्ति_loc);
	  finish = अभिव्यक्ति.get_finish ();
	  गच्छ Xof_अभिव्यक्ति;
	}
      /* sizeof ( type-name ).  */
      यदि (scspecs)
	error_at (अभिव्यक्ति_loc, "storage class specifier in %qs", op_name);
      यदि (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      यदि (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_अभिव्यक्ति_countof_type (अभिव्यक्ति_loc, type_name);
	}
      अन्यथा
	{
	  in_sizeof--;
	  result = c_अभिव्यक्ति_sizeof_type (अभिव्यक्ति_loc, type_name);
	}
    }
  अन्यथा
    {
      अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      अभिव्यक्ति = c_parser_unary_expression (parser);
      finish = अभिव्यक्ति.get_finish ();
    Xof_अभिव्यक्ति:
      c_inhibit_evaluation_warnings--;
      यदि (rid == RID_COUNTOF)
	in_countof--;
      अन्यथा
	in_sizeof--;
      mark_exp_read (अभिव्यक्ति.मान);
      यदि (रूख_CODE (अभिव्यक्ति.मान) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (रूख_OPERAND (अभिव्यक्ति.मान, 1)))
	error_at (अभिव्यक्ति_loc, "%qs applied to a bit-field", op_name);
      यदि (rid == RID_COUNTOF)
	result = c_अभिव्यक्ति_countof_अभिव्यक्ति (अभिव्यक्ति_loc, अभिव्यक्ति);
      अन्यथा
	result = c_अभिव्यक्ति_sizeof_अभिव्यक्ति (अभिव्यक्ति_loc, अभिव्यक्ति);
    }
  यदि (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_अभिव्यक्ति_source_range (&result, start, finish);
  फर्काऊ result;
}

/* Parse an alignof expression.  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_alignof_expression (c_parser *parser)
{
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  रूख alignof_spelling = c_parser_peek_token (parser)->मान;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  तार्किक is_c11_alignof = (म_भेद (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || म_भेद (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  यदि (is_c11_alignof)
    {
      यदि (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      अन्यथा
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      संरचना c_declspecs *scspecs;
      संरचना c_type_name *type_name;
      संरचना c_अभिव्यक्ति ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, सत्य);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      यदि (type_name == रिक्त)
	{
	  संरचना c_अभिव्यक्ति ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = रिक्त;
	  फर्काऊ ret;
	}
      यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  अभिव्यक्ति = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  गच्छ alignof_अभिव्यक्ति;
	}
      /* alignof ( type-name ).  */
      यदि (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      यदि (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.मान = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       रिक्त, रिक्त),
					    असत्य, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      set_c_अभिव्यक्ति_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      फर्काऊ ret;
    }
  अन्यथा
    {
      संरचना c_अभिव्यक्ति ret;
      अभिव्यक्ति = c_parser_unary_expression (parser);
      end_loc = अभिव्यक्ति.src_range.m_finish;
    alignof_अभिव्यक्ति:
      mark_exp_read (अभिव्यक्ति.मान);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      यदि (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.मान = c_alignof_अभिव्यक्ति (start_loc, अभिव्यक्ति.मान);
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      set_c_अभिव्यक्ति_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      फर्काऊ ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_maxof_or_minof_expression (c_parser *parser, गणना rid rid)
{
  अचर वर्ण *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  संरचना c_अभिव्यक्ति result;
  location_t अभिव्यक्ति_loc;
  संरचना c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  यदि (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      गच्छ fail;
    }
  parens.consume_open (parser);
  अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
  यदि (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (अभिव्यक्ति_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      गच्छ fail;
    }
  type_name = c_parser_type_name (parser, सत्य);
  यदि (type_name == रिक्त)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      गच्छ fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  यदि (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  यदि (rid == RID_MAXOF)
    result = c_अभिव्यक्ति_maxof_type (अभिव्यक्ति_loc, type_name);
  अन्यथा
    result = c_अभिव्यक्ति_minof_type (अभिव्यक्ति_loc, type_name);
  set_c_अभिव्यक्ति_source_range (&result, start, finish);
  फर्काऊ result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = रिक्त;
  फर्काऊ result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      संरचना c_अभिव्यक्ति result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = रिक्त;
      फर्काऊ result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  रूख oper = NULL_रूख;
  यदि (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      संरचना c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      यदि (tname)
	{
	  oper = groktypename (tname, रिक्त, रिक्त);
	  झिक_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  अन्यथा
    {
      संरचना c_अभिव्यक्ति cexpr = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      यदि (cexpr.मान != error_mark_गाँठो)
	{
	  mark_exp_read (cexpr.मान);
	  oper = cexpr.मान;
	  रूख etype = रूख_TYPE (oper);
	  तार्किक was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  यदि (was_vm)
	    oper = c_fully_fold (oper, असत्य, रिक्त);
	  झिक_maybe_used (was_vm);
	}
    }

  संरचना c_अभिव्यक्ति result;
  result.original_code = ERROR_MARK;
  result.original_type = रिक्त;

  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      फर्काऊ result;
    }

  तार्किक save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  रूख attr = c_parser_gnu_attribute (parser, NULL_रूख, असत्य, असत्य);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  अन्यथा
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);

      result.set_error ();
      फर्काऊ result;
    }

  यदि (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      फर्काऊ result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_गाँठो;

  यदि (has_attribute (atloc, oper, attr, default_conversion))
    result.मान = boolean_true_गाँठो;
  अन्यथा
    result.मान =  boolean_false_गाँठो;

  set_c_अभिव्यक्ति_source_range (&result, start, finish);
  result.m_decimal = 0;
  फर्काऊ result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
स्थिर तार्किक
c_parser_get_builtin_args (c_parser *parser, अचर वर्ण *bname,
			   vec<c_अभिव्यक्ति_t, va_gc> **ret_cexpr_list,
			   तार्किक choose_अभिव्यक्ति_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
  c_अभिव्यक्ति_t अभिव्यक्ति;
  तार्किक saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = रिक्त;
  यदि (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      फर्काऊ असत्य;
    }

  c_parser_consume_token (parser);

  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      फर्काऊ सत्य;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_अभिव्यक्ति_p;
  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_थप (cexpr_list, अभिव्यक्ति);
  जबसम्म (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  रूख मान = embed->मान;
	  अभिव्यक्ति.original_code = INTEGER_CST;
	  अभिव्यक्ति.original_type = integer_type_गाँठो;
	  अभिव्यक्ति.मान = NULL_रूख;
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, embed->get_range ());
	  अभिव्यक्ति.m_decimal = 0;
	  लागि (अचिन्हित पूर्णाङ्क i = 0; i < (अचिन्हित) RAW_DATA_LENGTH (मान); i++)
	    {
	      अभिव्यक्ति.मान = build_int_cst (integer_type_गाँठो,
					  RAW_DATA_UCHAR_ELT (मान, i));
	      vec_safe_थप (cexpr_list, अभिव्यक्ति);
	    }
	  c_parser_consume_token (parser);
	  जारी;
	}
      अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      vec_safe_थप (cexpr_list, अभिव्यक्ति);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    फर्काऊ असत्य;

  *ret_cexpr_list = cexpr_list;
  फर्काऊ सत्य;
}

/* This represents a single generic-association.  */

संरचना c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  रूख type;
  /* The association's expression.  */
  संरचना c_अभिव्यक्ति expression;
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_generic_selection (c_parser *parser)
{
  संरचना c_अभिव्यक्ति selector, error_अभिव्यक्ति;
  रूख selector_type;
  संरचना c_generic_association matched_assoc;
  पूर्णाङ्क match_found = -1;
  location_t generic_loc, selector_loc;

  error_अभिव्यक्ति.original_code = ERROR_MARK;
  error_अभिव्यक्ति.original_type = रिक्त;
  error_अभिव्यक्ति.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_रूख;
  matched_assoc.expression = error_अभिव्यक्ति;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  यदि (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  अन्यथा
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ error_अभिव्यक्ति;

  selector_loc = c_parser_peek_token (parser)->location;
  यदि (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      संरचना c_type_name *type = c_parser_type_name (parser);
      यदि (type)
	selector_type = groktypename (type, रिक्त, रिक्त);
      c_inhibit_evaluation_warnings--;
      यदि (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  फर्काऊ error_अभिव्यक्ति;
	}
    }
  अन्यथा
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      झिक_maybe_used (!flag_isoc23);

      यदि (selector.मान == error_mark_गाँठो)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  फर्काऊ selector;
	}
      mark_exp_read (selector.मान);
      selector_type = रूख_TYPE (selector.मान);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      यदि (रूख_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      यदि (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (रूख_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (रूख_TYPE (selector_type)));
    }

  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      फर्काऊ error_अभिव्यक्ति;
    }

  auto_vec<c_generic_association> associations;
  संरचना maybe_used_decl *maybe_used_default = रिक्त;
  जबसम्म (1)
    {
      संरचना c_generic_association assoc, *iter;
      अचिन्हित पूर्णाङ्क ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      यदि (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_रूख;
	}
      अन्यथा
	{
	  संरचना c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  यदि (type_name == रिक्त)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      फर्काऊ error_अभिव्यक्ति;
	    }
	  assoc.type = grokgenassoc (type_name);
	  यदि (assoc.type == error_mark_गाँठो)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      फर्काऊ error_अभिव्यक्ति;
	    }

	  यदि (रूख_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  अन्यथा यदि (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  यदि (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  फर्काऊ error_अभिव्यक्ति;
	}

      तार्किक match = assoc.type == NULL_रूख
		   || comptypes (assoc.type, selector_type);

      यदि (!match || matched_assoc.type != NULL_रूख)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);

      यदि (!match || matched_assoc.type != NULL_रूख)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      यदि (!match)
	झिक_maybe_used (!flag_isoc23);
      अन्यथा यदि (assoc.type == NULL_रूख)
	maybe_used_default = save_maybe_used ();
      अन्यथा
	झिक_maybe_used (सत्य);

      यदि (assoc.expression.मान == error_mark_गाँठो)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  फर्काऊ error_अभिव्यक्ति;
	}

      लागि (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  यदि (assoc.type == NULL_रूख)
	    {
	      यदि (iter->type == NULL_रूख)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  अन्यथा यदि (iter->type != NULL_रूख)
	    {
	      यदि (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      यदि (assoc.type == NULL_रूख)
	{
	  यदि (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      अन्यथा यदि (match)
	{
	  यदि (match_found < 0 || matched_assoc.type == NULL_रूख)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  अन्यथा
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_थप (assoc);

      यदि (c_parser_peek_token (parser)->type != CPP_COMMA)
	रोक;
      c_parser_consume_token (parser);
    }

  यदि (match_found >= 0 && matched_assoc.type == NULL_रूख)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      झिक_maybe_used (सत्य);
    }
  अन्यथा यदि (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      झिक_maybe_used (!flag_isoc23);
    }

  अचिन्हित पूर्णाङ्क ix;
  संरचना c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    यदि (ix != (अचिन्हित) match_found)
      mark_exp_read (iter->expression.मान);

  यदि (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
      फर्काऊ error_अभिव्यक्ति;
    }

  यदि (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      फर्काऊ error_अभिव्यक्ति;
    }

  फर्काऊ matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

स्थिर अचिन्हित पूर्णाङ्क
check_tgmath_function (c_अभिव्यक्ति *अभिव्यक्ति, अचिन्हित पूर्णाङ्क pos)
{
  रूख type = रूख_TYPE (अभिव्यक्ति->मान);
  यदि (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (अभिव्यक्ति->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      फर्काऊ 0;
    }
  type = रूख_TYPE (type);
  यदि (!prototype_p (type))
    {
      error_at (अभिव्यक्ति->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      फर्काऊ 0;
    }
  यदि (stdarg_p (type))
    {
      error_at (अभिव्यक्ति->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      फर्काऊ 0;
    }
  अचिन्हित पूर्णाङ्क nargs = 0;
  function_args_iterator iter;
  रूख t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      यदि (t == void_type_गाँठो)
	रोक;
      nargs++;
    }
  यदि (nargs == 0)
    {
      error_at (अभिव्यक्ति->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      फर्काऊ 0;
    }
  फर्काऊ nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
गणना tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  विकल्प (c_parser_peek_token (parser)->keyword)
    {
    पक्ष RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      रोक;
    पक्ष RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      रोक;
    पक्ष RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      रोक;
    स्वभाव:
      gcc_unreachable ();
    }

  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  अभिव्यक्ति.original_code = ERROR_MARK;
  अभिव्यक्ति.original_type = रिक्त;
  अभिव्यक्ति.मान = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->मान);
  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, loc);
  अभिव्यक्ति.m_decimal = 0;
  c_parser_consume_token (parser);
  फर्काऊ अभिव्यक्ति;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

स्थिर तार्किक
has_counted_by_object (रूख ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  यदि ((रूख_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (रूख_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    फर्काऊ सत्य;
  फर्काऊ असत्य;
}

/* Get the reference to the counted-by object associated with the REF.  */

स्थिर रूख
get_counted_by_ref (रूख ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  यदि (रूख_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (रूख_OPERAND (ref, 0)))
    फर्काऊ CALL_अभिव्यक्ति_ARG (रूख_OPERAND (ref, 0), 1);
  अन्यथा यदि (is_access_with_size_p (ref))
    फर्काऊ CALL_अभिव्यक्ति_ARG (ref, 1);

  फर्काऊ NULL_रूख;
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_postfix_expression (c_parser *parser)
{
  संरचना c_अभिव्यक्ति अभिव्यक्ति, e1;
  संरचना c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  अभिव्यक्ति.original_code = ERROR_MARK;
  अभिव्यक्ति.original_type = रिक्त;
  अभिव्यक्ति.m_decimal = 0;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_सङ्ख्या:
      अभिव्यक्ति.मान = c_parser_peek_token (parser)->मान;
      set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
      loc = c_parser_peek_token (parser)->location;
      अभिव्यक्ति.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      यदि (रूख_CODE (अभिव्यक्ति.मान) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  अभिव्यक्ति.set_error ();
	}
      रोक;
    पक्ष CPP_CHAR:
    पक्ष CPP_CHAR16:
    पक्ष CPP_CHAR32:
    पक्ष CPP_UTF8CHAR:
    पक्ष CPP_WCHAR:
      अभिव्यक्ति.मान = c_parser_peek_token (parser)->मान;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      अभिव्यक्ति.original_type = char_type_गाँठो;
      set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
      c_parser_consume_token (parser);
      रोक;
    पक्ष CPP_STRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_WSTRING:
    पक्ष CPP_UTF8STRING:
      अभिव्यक्ति = c_parser_string_literal (parser, parser->translate_strings_p,
				      सत्य);
      रोक;
    पक्ष CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      अभिव्यक्ति.मान
	= objc_build_string_object (c_parser_peek_token (parser)->मान);
      set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
      c_parser_consume_token (parser);
      रोक;
    पक्ष CPP_NAME:
      विकल्प (c_parser_peek_token (parser)->id_kind)
	{
	पक्ष C_ID_ID:
	  {
	    रूख id = c_parser_peek_token (parser)->मान;
	    c_parser_consume_token (parser);
	    अभिव्यक्ति.मान = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &अभिव्यक्ति.original_type);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
	    रोक;
	  }
	पक्ष C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    रूख class_name = c_parser_peek_token (parser)->मान;
	    रूख component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    यदि (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->मान;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    अभिव्यक्ति.मान = objc_build_class_component_ref (class_name,
							 component);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, end_loc);
	    रोक;
	  }
	स्वभाव:
	  c_parser_error (parser, "expected expression");
	  अभिव्यक्ति.set_error ();
	  रोक;
	}
      रोक;
    पक्ष CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      यदि (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  रूख stmt;
	  location_t brace_loc;
	  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  यदि (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = सत्य;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      अभिव्यक्ति.set_error ();
	      रोक;
	    }
	  c_omp_array_section_p = असत्य;
	  stmt = c_begin_stmt_अभिव्यक्ति ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  अभिव्यक्ति.मान = c_finish_stmt_अभिव्यक्ति (brace_loc, stmt);
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_loc);
	  mark_exp_read (अभिव्यक्ति.मान);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      अन्यथा
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  अभिव्यक्ति = c_parser_expression (parser);
	  यदि (रूख_CODE (अभिव्यक्ति.मान) == MODIFY_अभिव्यक्ति)
	    suppress_warning (अभिव्यक्ति.मान, OPT_Wparentheses);
	  यदि (अभिव्यक्ति.original_code != C_MAYBE_CONST_अभिव्यक्ति
	      && अभिव्यक्ति.original_code != SIZEOF_अभिव्यक्ति)
	    अभिव्यक्ति.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  यदि (अभिव्यक्ति.original_code == SIZEOF_अभिव्यक्ति)
	    अभिव्यक्ति.original_code = PAREN_SIZEOF_अभिव्यक्ति;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      रोक;
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_FUNCTION_NAME:
	पक्ष RID_PRETTY_FUNCTION_NAME:
	पक्ष RID_C99_FUNCTION_NAME:
	  अभिव्यक्ति = c_parser_predefined_identifier (parser);
	  रोक;
	पक्ष RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    e1 = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	    mark_exp_read (e1.मान);
	    e1.मान = c_fully_fold (e1.मान, असत्य, रिक्त);
	    यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    यदि (t1 == रिक्त)
	      {
		अभिव्यक्ति.set_error ();
	      }
	    अन्यथा
	      {
		रूख type_अभिव्यक्ति = NULL_रूख;
		रूख type = groktypename (t1, &type_अभिव्यक्ति, रिक्त);
		अभिव्यक्ति.मान = c_build_va_arg (start_loc, e1.मान, loc,
					     type, type_अभिव्यक्ति);
		set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start_loc, end_loc);
	      }
	  }
	  रोक;
	पक्ष RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    e1 = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, सत्य, सत्य);
	    यदि (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		    अभिव्यक्ति.set_error ();
		    रोक;
		  }
		यदि (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    रूख name = c_parser_peek_token (parser)->मान;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    रूख decl = lookup_name (name);
		    रूख last_parm
		      = रूख_last (DECL_ARGUMENTS (current_function_decl));
		    यदि (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    अन्यथा यदि (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		अन्यथा
		  {
		    अचिन्हित nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    जबसम्म (सत्य)
		      {
			c_token *token = c_parser_peek_token (parser);
			यदि (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  रोक;

			यदि (token->type == CPP_EOF)
			  रोक;
			यदि (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			अन्यथा यदि (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    यदि (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    रूख fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<रूख, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_थप (e1.मान);
	    params->quick_थप (integer_zero_गाँठो);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_थप (e1.get_location ());
	    arg_loc.quick_थप (UNKNOWN_LOCATION);
	    अभिव्यक्ति.मान = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, रिक्त);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc,
				     parser->tokens_buf[0].get_finish ());
	    अभिव्यक्ति.m_decimal = 0;
	    अभिव्यक्ति.original_code = ERROR_MARK;
	    अभिव्यक्ति.original_type = रिक्त;
	    release_रूख_vector (params);
	    रोक;
	  }
	पक्ष RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    t1 = c_parser_type_name (parser);
	    यदि (t1 == रिक्त)
	      parser->error = सत्य;
	    यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    यदि (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    रूख type = groktypename (t1, रिक्त, रिक्त);
	    रूख offsetof_ref;
	    यदि (type == error_mark_गाँठो)
	      offsetof_ref = error_mark_गाँठो;
	    अन्यथा
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_गाँठो);
		SET_अभिव्यक्ति_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    यदि (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->मान,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		जबसम्म (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    यदि (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_गाँठो);
			गच्छ do_dot;
		      }
		    अन्यथा यदि (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			यदि (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    रोक;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->मान,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    अन्यथा
		      {
			संरचना c_अभिव्यक्ति ce;
			रूख idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, असत्य, असत्य);
			idx = ce.मान;
			idx = c_fully_fold (idx, असत्य, रिक्त);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    अन्यथा
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    अभिव्यक्ति.मान = fold_offsetof (offsetof_ref);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, end_loc);
	  }
	  रोक;
	पक्ष RID_CHOOSE_अभिव्यक्ति:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    c_अभिव्यक्ति_t *e1_p, *e2_p, *e3_p;
	    रूख c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, सत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    यदि (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->मान;
	    mark_exp_read (e2_p->मान);
	    mark_exp_read (e3_p->मान);
	    यदि (रूख_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (रूख_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    अभिव्यक्ति = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    रोक;
	  }
	पक्ष RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    t1 = c_parser_type_name (parser);
	    यदि (t1 == रिक्त)
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    t2 = c_parser_type_name (parser);
	    यदि (t2 == रिक्त)
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    रूख e1, e2;
	    e1 = groktypename (t1, रिक्त, रिक्त);
	    e2 = groktypename (t2, रिक्त, रिक्त);
	    यदि (e1 == error_mark_गाँठो || e2 == error_mark_गाँठो)
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    अभिव्यक्ति.मान
	      = comptypes (e1, e2) ? integer_one_गाँठो : integer_zero_गाँठो;
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	  }
	  रोक;
	पक्ष RID_BUILTIN_TGMATH:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, असत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    यदि (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    अचिन्हित पूर्णाङ्क i;
	    c_अभिव्यक्ति_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, सत्य, सत्य);
	    अचिन्हित पूर्णाङ्क nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    यदि (nargs == 0)
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    अचिन्हित पूर्णाङ्क अङ्क_functions = vec_safe_length (cexpr_list) - nargs;
	    यदि (अङ्क_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    लागि (अचिन्हित पूर्णाङ्क j = 1; j < अङ्क_functions; j++)
	      {
		अचिन्हित पूर्णाङ्क this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		यदि (this_nargs == 0)
		  {
		    अभिव्यक्ति.set_error ();
		    गच्छ out;
		  }
		यदि (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    अभिव्यक्ति.set_error ();
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
	    auto_vec<रूख> parm_first (nargs + 1);
	    auto_vec<तार्किक> parm_complex (nargs + 1);
	    auto_vec<तार्किक> parm_varies (nargs + 1);
	    रूख first_type = रूख_TYPE (रूख_TYPE ((*cexpr_list)[0].मान));
	    रूख first_ret = TYPE_MAIN_VARIANT (रूख_TYPE (first_type));
	    parm_first.quick_थप (first_ret);
	    parm_complex.quick_थप (रूख_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_थप (असत्य);
	    function_args_iterator iter;
	    रूख t;
	    अचिन्हित पूर्णाङ्क argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		यदि (t == void_type_गाँठो)
		  रोक;
		parm_first.quick_थप (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_थप (रूख_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_थप (असत्य);
	      }
	    लागि (अचिन्हित पूर्णाङ्क j = 1; j < अङ्क_functions; j++)
	      {
		रूख type = रूख_TYPE (रूख_TYPE ((*cexpr_list)[j].मान));
		रूख ret = TYPE_MAIN_VARIANT (रूख_TYPE (type));
		यदि (ret != parm_first[0])
		  {
		    parm_varies[0] = सत्य;
		    यदि (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		    यदि (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		  }
		यदि (रूख_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = सत्य;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    यदि (t == void_type_गाँठो)
		      रोक;
		    t = TYPE_MAIN_VARIANT (t);
		    यदि (t != parm_first[argpos])
		      {
			parm_varies[argpos] = सत्य;
			यदि (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    अभिव्यक्ति.set_error ();
			    गच्छ out;
			  }
			यदि (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    अभिव्यक्ति.set_error ();
			    गच्छ out;
			  }
		      }
		    यदि (रूख_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = सत्य;
		    argpos++;
		  }
	      }
	    गणना tgmath_parm_kind max_variation = tgmath_fixed;
	    लागि (अचिन्हित पूर्णाङ्क j = 0; j <= nargs; j++)
	      {
		गणना tgmath_parm_kind this_kind;
		यदि (parm_varies[j])
		  {
		    यदि (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    अन्यथा
		      {
			this_kind = tgmath_real;
			यदि (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		अन्यथा
		  this_kind = tgmath_fixed;
		parm_kind.quick_थप (this_kind);
	      }
	    यदि (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    अचिन्हित पूर्णाङ्क tgarg = 0;
	    लागि (अचिन्हित पूर्णाङ्क j = 1; j <= nargs; j++)
	      यदि (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  रोक;
		}
	    यदि (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<रूख> tg_type (अङ्क_functions);
	    लागि (अचिन्हित पूर्णाङ्क j = 0; j < अङ्क_functions; j++)
	      {
		रूख type = रूख_TYPE (रूख_TYPE ((*cexpr_list)[j].मान));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    यदि (argpos == tgarg)
		      {
			tg_type.quick_थप (TYPE_MAIN_VARIANT (t));
			रोक;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    तार्किक all_complex = सत्य;
	    तार्किक all_द्विआधारी = सत्य;
	    तार्किक all_decimal = सत्य;
	    hash_set<रूख> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		यदि (रूख_CODE (t) == COMPLEX_TYPE)
		  all_decimal = असत्य;
		अन्यथा
		  {
		    all_complex = असत्य;
		    यदि (DECIMAL_FLOAT_TYPE_P (t))
		      all_द्विआधारी = असत्य;
		    अन्यथा
		      all_decimal = असत्य;
		  }
		यदि (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    अभिव्यक्ति.set_error ();
		    गच्छ out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    लागि (अचिन्हित पूर्णाङ्क j = 0; j < अङ्क_functions; j++)
	      {
		रूख exp_type = tg_type[j];
		रूख exp_real_type = exp_type;
		यदि (रूख_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = रूख_TYPE (exp_type);
		रूख type = रूख_TYPE (रूख_TYPE ((*cexpr_list)[j].मान));
		रूख ret = TYPE_MAIN_VARIANT (रूख_TYPE (type));
		यदि ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    अभिव्यक्ति.set_error ();
		    गच्छ out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    यदि (t == void_type_गाँठो)
		      रोक;
		    t = TYPE_MAIN_VARIANT (t);
		    यदि ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			अभिव्यक्ति.set_error ();
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
	    तार्किक arg_द्विआधारी = all_द्विआधारी;
	    तार्किक arg_int_decimal = all_decimal;
	    तार्किक arg_int_floatnx = असत्य;
	    तार्किक arg_int_decimalx = असत्य;
	    लागि (अचिन्हित पूर्णाङ्क j = 1; j <= nargs; j++)
	      {
		यदि (parm_kind[j] == tgmath_fixed)
		  जारी;
		c_अभिव्यक्ति_t *ce = &(*cexpr_list)[अङ्क_functions + j - 1];
		रूख type = रूख_TYPE (ce->मान);
		यदि (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && रूख_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    अभिव्यक्ति.set_error ();
		    गच्छ out;
		  }
		यदि (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = सत्य;
		    यदि (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		    अन्यथा यदि (all_द्विआधारी)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		    अन्यथा यदि (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		    अन्यथा यदि (arg_द्विआधारी)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		  }
		अन्यथा यदि (रूख_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = सत्य;
		    यदि (COMPLEX_FLOAT_TYPE_P (type))
		      arg_द्विआधारी = सत्य;
		    यदि (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		    अन्यथा यदि (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		  }
		अन्यथा यदि (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_द्विआधारी = सत्य;
		    यदि (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		    अन्यथा यदि (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			अभिव्यक्ति.set_error ();
			गच्छ out;
		      }
		  }
		रूख rtype = TYPE_MAIN_VARIANT (type);
		यदि (रूख_CODE (rtype) == COMPLEX_TYPE)
		  rtype = रूख_TYPE (rtype);
		यदि (SCALAR_FLOAT_TYPE_P (rtype))
		  लागि (अचिन्हित पूर्णाङ्क j = 0; j < अङ्क_FLOATNX_TYPES; j++)
		    यदि (rtype == FLOATNX_TYPE_गाँठो (j))
		      {
			arg_int_floatnx = सत्य;
			रोक;
		      }
		यदि (rtype == dfloat64x_type_गाँठो)
		  arg_int_decimalx = सत्य;
	      }
	    रूख arg_real = NULL_रूख;
	    लागि (अचिन्हित पूर्णाङ्क j = 1; j <= nargs; j++)
	      {
		यदि (parm_kind[j] == tgmath_fixed)
		  जारी;
		c_अभिव्यक्ति_t *ce = &(*cexpr_list)[अङ्क_functions + j - 1];
		रूख type = TYPE_MAIN_VARIANT (रूख_TYPE (ce->मान));
		यदि (रूख_CODE (type) == COMPLEX_TYPE)
		  type = रूख_TYPE (type);
		यदि (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_गाँठो
			  : arg_int_floatnx
			  ? float32x_type_गाँठो
			  : arg_int_decimal
			  ? dfloat64_type_गाँठो
			  : double_type_गाँठो);
		यदि (arg_real == NULL_रूख)
		  arg_real = type;
		अन्यथा
		  arg_real = common_type (arg_real, type);
		यदि (arg_real == error_mark_गाँठो)
		  {
		    अभिव्यक्ति.set_error ();
		    गच्छ out;
		  }
	      }
	    रूख arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_अभिव्यक्ति_t *fn = रिक्त;
	    लागि (अचिन्हित पूर्णाङ्क j = 0; j < अङ्क_functions; j++)
	      {
		यदि (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    रोक;
		  }
	      }
	    यदि (fn == रिक्त
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		लागि (अचिन्हित पूर्णाङ्क j = 0; j < अङ्क_functions; j++)
		  {
		    यदि (arg_complex
			!= (रूख_CODE (tg_type[j]) == COMPLEX_TYPE))
		      जारी;
		    रूख real_tg_type = (arg_complex
					 ? रूख_TYPE (tg_type[j])
					 : tg_type[j]);
		    यदि (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      जारी;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    अचर real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    अचर real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    यदि (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			रोक;
		      }
		  }
	      }
	    यदि (fn == रिक्त)
	      {
		error_at (loc, "no matching function for type-generic call");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    /* Construct a call to FN.  */
	    vec<रूख, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<रूख, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    लागि (अचिन्हित पूर्णाङ्क j = 0; j < nargs; j++)
	      {
		c_अभिव्यक्ति_t *ce = &(*cexpr_list)[अङ्क_functions + j];
		args->quick_थप (ce->मान);
		arg_loc.quick_थप (ce->get_location ());
		origtypes->quick_थप (ce->original_type);
	      }
	    अभिव्यक्ति.मान = c_build_function_call_vec (loc, arg_loc, fn->मान,
						    args, origtypes);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    रोक;
	  }
	पक्ष RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    c_अभिव्यक्ति_t *e2_p;
	    रूख chain_मान;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, असत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    अभिव्यक्ति = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, सत्य, सत्य);
	    chain_मान = e2_p->मान;
	    mark_exp_read (chain_मान);

	    यदि (रूख_CODE (अभिव्यक्ति.मान) != CALL_अभिव्यक्ति)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    अन्यथा यदि (रूख_CODE (रूख_TYPE (chain_मान)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    अन्यथा
	      CALL_अभिव्यक्ति_STATIC_CHAIN (अभिव्यक्ति.मान) = chain_मान;
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    रोक;
	  }
	पक्ष RID_BUILTIN_COMPLEX:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    c_अभिव्यक्ति_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, असत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    यदि (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, सत्य, सत्य);
	    यदि (रूख_CODE (e1_p->मान) == EXCESS_PRECISION_अभिव्यक्ति)
	      e1_p->मान = convert (रूख_TYPE (e1_p->मान),
				     रूख_OPERAND (e1_p->मान, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, सत्य, सत्य);
	    यदि (रूख_CODE (e2_p->मान) == EXCESS_PRECISION_अभिव्यक्ति)
	      e2_p->मान = convert (रूख_TYPE (e2_p->मान),
				     रूख_OPERAND (e2_p->मान, 0));
	    यदि (!SCALAR_FLOAT_TYPE_P (रूख_TYPE (e1_p->मान))
		|| DECIMAL_FLOAT_TYPE_P (रूख_TYPE (e1_p->मान))
		|| !SCALAR_FLOAT_TYPE_P (रूख_TYPE (e2_p->मान))
		|| DECIMAL_FLOAT_TYPE_P (रूख_TYPE (e2_p->मान)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (TYPE_MAIN_VARIANT (रूख_TYPE (e1_p->मान))
		!= TYPE_MAIN_VARIANT (रूख_TYPE (e2_p->मान)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    अभिव्यक्ति.मान = build2_loc (loc, COMPLEX_अभिव्यक्ति,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (रूख_TYPE (e1_p->मान))),
				     e1_p->मान, e2_p->मान);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    रोक;
	  }
	पक्ष RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    c_अभिव्यक्ति_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, असत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    e_p = &(*cexpr_list)[0];
	    रूख ref = e_p->मान;

	    यदि (रूख_CODE (रूख_TYPE (ref)) != ARRAY_TYPE
		 && रूख_CODE (रूख_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    यदि (रूख_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    यदि (रूख_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    यदि (has_counted_by_object (ref))
	      अभिव्यक्ति.मान = get_counted_by_ref (ref);
	    अन्यथा
	      अभिव्यक्ति.मान = null_pointer_गाँठो;

	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    रोक;
	  }
	पक्ष RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    अचिन्हित पूर्णाङ्क i;
	    c_अभिव्यक्ति_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, असत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, सत्य, सत्य);

	    यदि (vec_safe_length (cexpr_list) == 2)
	      अभिव्यक्ति.मान = c_build_vec_perm_अभिव्यक्ति (loc, (*cexpr_list)[0].मान,
						  NULL_रूख,
						  (*cexpr_list)[1].मान);

	    अन्यथा यदि (vec_safe_length (cexpr_list) == 3)
	      अभिव्यक्ति.मान = c_build_vec_perm_अभिव्यक्ति (loc, (*cexpr_list)[0].मान,
						  (*cexpr_list)[1].मान,
						  (*cexpr_list)[2].मान);
	    अन्यथा
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		अभिव्यक्ति.set_error ();
	      }
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    रोक;
	  }
	पक्ष RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    अचिन्हित पूर्णाङ्क i;
	    c_अभिव्यक्ति_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, असत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, सत्य, सत्य);

	    यदि (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		अभिव्यक्ति.set_error ();
	      }
	    अन्यथा
	      {
		auto_vec<रूख, 16> mask;
		लागि (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_थप ((*cexpr_list)[i].मान);
		अभिव्यक्ति.मान = c_build_shufflevector (loc, (*cexpr_list)[0].मान,
						    (*cexpr_list)[1].मान,
						    mask);
	      }
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    रोक;
	  }
	पक्ष RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    e1 = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	    mark_exp_read (e1.मान);
	    यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    यदि (t1 == रिक्त)
	      अभिव्यक्ति.set_error ();
	    अन्यथा
	      {
		रूख type_अभिव्यक्ति = NULL_रूख;
		अभिव्यक्ति.मान = c_build_vec_convert (start_loc, e1.मान, loc,
						  groktypename (t1, &type_अभिव्यक्ति,
								रिक्त));
		set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start_loc, end_loc);
	      }
	  }
	  रोक;
	पक्ष RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    e1 = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	    mark_exp_read (e1.मान);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    अभिव्यक्ति = parser_build_unary_op (loc, PAREN_अभिव्यक्ति, e1);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start_loc, end_loc);
	  }
	  रोक;
	पक्ष RID_BUILTIN_STDC:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    c_अभिव्यक्ति_t *arg_p;
	    location_t close_paren_loc;
	    गणना c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_गन्ती_ONES,
	      C_BUILTIN_STDC_गन्ती_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_बायाँ,
	      C_BUILTIN_STDC_ROTATE_दायाँ,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    अचर वर्ण *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	    अचिन्हित अङ्क_args = 1;
	    विकल्प (name[परिमाण ("__builtin_stdc_") - 1])
	      {
	      पक्ष 'b':
		विकल्प (name[परिमाण ("__builtin_stdc_bit_") - 1])
		  {
		  पक्ष 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    रोक;
		  पक्ष 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    रोक;
		  स्वभाव:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    रोक;
		  }
		रोक;
	      पक्ष 'c':
		यदि (name[परिमाण ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_गन्ती_ONES;
		अन्यथा
		  stdc_rid = C_BUILTIN_STDC_गन्ती_ZEROS;
		रोक;
	      पक्ष 'f':
		विकल्प (name[परिमाण ("__builtin_stdc_first_trailing_") - 1])
		  {
		  पक्ष 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    रोक;
		  पक्ष 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    रोक;
		  पक्ष 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    रोक;
		  स्वभाव:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    रोक;
		  }
		रोक;
	      पक्ष 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		रोक;
	      पक्ष 'l':
		यदि (name[परिमाण ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		अन्यथा
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		रोक;
	      पक्ष 'r':
		यदि (name[परिमाण ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_बायाँ;
		अन्यथा
		  stdc_rid = C_BUILTIN_STDC_ROTATE_दायाँ;
		अङ्क_args = 2;
		रोक;
	      पक्ष 't':
		यदि (name[परिमाण ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		अन्यथा
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		रोक;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, असत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    यदि (vec_safe_length (cexpr_list) != अङ्क_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, सत्य, सत्य);
	    यदि (!INTEGRAL_TYPE_P (रूख_TYPE (arg_p->मान)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (रूख_CODE (रूख_TYPE (arg_p->मान)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (रूख_CODE (रूख_TYPE (arg_p->मान)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (!TYPE_UNSIGNED (रूख_TYPE (arg_p->मान)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (TYPE_MAIN_VARIANT (रूख_TYPE (arg_p->मान))
		== char_type_गाँठो)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    रूख arg = arg_p->मान;
	    रूख type = TYPE_MAIN_VARIANT (रूख_TYPE (arg));
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
	    यदि (अङ्क_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, सत्य, सत्य);
		यदि (!INTEGRAL_TYPE_P (रूख_TYPE (arg_p->मान)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    अभिव्यक्ति.set_error ();
		    रोक;
		  }
		यदि (रूख_CODE (रूख_TYPE (arg_p->मान)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    अभिव्यक्ति.set_error ();
		    रोक;
		  }
		रूख arg1 = save_अभिव्यक्ति (arg);
		रूख arg2 = save_अभिव्यक्ति (arg_p->मान);
		रूख_code code;
		यदि (stdc_rid == C_BUILTIN_STDC_ROTATE_बायाँ)
		  code = LROTATE_अभिव्यक्ति;
		अन्यथा
		  code = RROTATE_अभिव्यक्ति;

		यदि (रूख_CODE (arg2) == INTEGER_CST
		    && रूख_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_गन्ती_negative,
			      "rotate count is negative");

		रूख instrument_अभिव्यक्ति = NULL_रूख;
		यदि (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_अभिव्यक्ति = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		यदि (TYPE_PRECISION (रूख_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_गाँठो))
		  arg2 = fold_convert (unsigned_type_गाँठो, arg2);

		यदि (TYPE_UNSIGNED (रूख_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_अभिव्यक्ति, रूख_TYPE (arg2),
				     arg2, build_int_cst (रूख_TYPE (arg2),
							  prec));
		अन्यथा
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    रूख utype = c_common_unsigned_type (रूख_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_अभिव्यक्ति, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		यदि (type_has_mode_precision_p (रूख_TYPE (arg1))
		    || (रूख_CODE (रूख_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  अभिव्यक्ति.मान = build2_loc (loc, code, रूख_TYPE (arg1), arg1,
					   arg2);
		अन्यथा
		  {
		    arg2 = save_अभिव्यक्ति (arg2);
		    रूख t1 = build2_loc (loc, (code == LROTATE_अभिव्यक्ति
						? LSHIFT_अभिव्यक्ति : RSHIFT_अभिव्यक्ति),
					  रूख_TYPE (arg1), arg1, arg2);
		    रूख t2 = build2_loc (loc, MINUS_अभिव्यक्ति,
					  रूख_TYPE (arg2),
					  build_int_cst (रूख_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_अभिव्यक्ति
					   ? RSHIFT_अभिव्यक्ति : LSHIFT_अभिव्यक्ति),
				     रूख_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_गन्ती_overflow);
		    रूख t3 = build2_loc (loc, BIT_IOR_अभिव्यक्ति,
					  रूख_TYPE (arg1), t1, t2);
		    रूख t4 = build2_loc (loc, NE_अभिव्यक्ति, boolean_type_गाँठो,
					  arg2,
					  build_zero_cst (रूख_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_अभिव्यक्ति, boolean_type_गाँठो,
				     arg1, t4);
		    अभिव्यक्ति.मान = build3_loc (loc, COND_अभिव्यक्ति,
					     रूख_TYPE (arg1), t4, t3, arg1);
		  }
		यदि (instrument_अभिव्यक्ति)
		  अभिव्यक्ति.मान = build2_loc (loc, COMPOUND_अभिव्यक्ति,
					   रूख_TYPE (अभिव्यक्ति.मान),
					   instrument_अभिव्यक्ति, अभिव्यक्ति.मान);
		set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
		रोक;
	      }
	    रूख barg1 = arg;
	    विकल्प (stdc_rid)
	      {
	      पक्ष C_BUILTIN_STDC_BIT_CEIL:
		arg = save_अभिव्यक्ति (arg);
		barg1 = build2_loc (loc, PLUS_अभिव्यक्ति, type, arg,
				    build_int_cst (type, -1));
		रोक;
	      पक्ष C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_अभिव्यक्ति (arg);
		रोक;
	      पक्ष C_BUILTIN_STDC_गन्ती_ZEROS:
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      पक्ष C_BUILTIN_STDC_LEADING_ONES:
	      पक्ष C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_अभिव्यक्ति, type, arg);
		रोक;
	      स्वभाव:
		रोक;
	      }
	    रूख barg2 = NULL_रूख;
	    विकल्प (stdc_rid)
	      {
	      पक्ष C_BUILTIN_STDC_BIT_WIDTH:
	      पक्ष C_BUILTIN_STDC_LEADING_ONES:
	      पक्ष C_BUILTIN_STDC_LEADING_ZEROS:
	      पक्ष C_BUILTIN_STDC_TRAILING_ONES:
	      पक्ष C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_गाँठो, prec);
		रोक;
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_गाँठो;
		रोक;
	      स्वभाव:
		रोक;
	      }
	    रूख fndecl = NULL_रूख;
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
		रोक;
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      पक्ष C_BUILTIN_STDC_TRAILING_ONES:
	      पक्ष C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		रोक;
	      पक्ष C_BUILTIN_STDC_गन्ती_ONES:
	      पक्ष C_BUILTIN_STDC_गन्ती_ZEROS:
	      पक्ष C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		रोक;
	      स्वभाव:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    पूर्णाङ्क nargs = barg2 != NULL_रूख ? 2 : 1;
	    vec<रूख, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<रूख, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_थप (barg1);
	    arg_loc.quick_थप (arg_p->get_location ());
	    origtypes->quick_थप (arg_p->original_type);
	    यदि (nargs == 2)
	      {
		args->quick_थप (barg2);
		arg_loc.quick_थप (loc);
		origtypes->quick_थप (integer_type_गाँठो);
	      }
	    अभिव्यक्ति.मान = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    यदि (अभिव्यक्ति.मान == error_mark_गाँठो)
	      रोक;
	    विकल्प (stdc_rid)
	      {
	      पक्ष C_BUILTIN_STDC_BIT_CEIL:
	      पक्ष C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      पक्ष C_BUILTIN_STDC_BIT_WIDTH:
		अभिव्यक्ति.मान = build2_loc (loc, MINUS_अभिव्यक्ति, integer_type_गाँठो,
					 build_int_cst (integer_type_गाँठो,
							prec), अभिव्यक्ति.मान);
		रोक;
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      पक्ष C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		अभिव्यक्ति.मान = build2_loc (loc, PLUS_अभिव्यक्ति, integer_type_गाँठो,
					 अभिव्यक्ति.मान, integer_one_गाँठो);
		रोक;
	      पक्ष C_BUILTIN_STDC_HAS_SINGLE_BIT:
		अभिव्यक्ति.मान = build2_loc (loc, EQ_अभिव्यक्ति, boolean_type_गाँठो,
					 अभिव्यक्ति.मान, integer_one_गाँठो);
		रोक;
	      स्वभाव:
		रोक;
	      }

	    यदि (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		यदि (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  अभिव्यक्ति.मान = fold_convert_loc (loc, unsigned_type_गाँठो,
						 अभिव्यक्ति.मान);
		रोक;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    यदि (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      अभिव्यक्ति.मान = build_int_cst (type, 0);
	    अन्यथा
	      अभिव्यक्ति.मान
		= build2_loc (loc, LSHIFT_अभिव्यक्ति, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), अभिव्यक्ति.मान);
	    यदि (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      अभिव्यक्ति.मान = build3_loc (loc, COND_अभिव्यक्ति, type,
				       build2_loc (loc, LE_अभिव्यक्ति,
						   boolean_type_गाँठो, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       अभिव्यक्ति.मान);
	    अन्यथा
	      अभिव्यक्ति.मान = build3_loc (loc, COND_अभिव्यक्ति, type,
				       build2_loc (loc, EQ_अभिव्यक्ति,
						   boolean_type_गाँठो, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       अभिव्यक्ति.मान);
	    रोक;
	  }
	पक्ष RID_BUILTIN_BSWAPG:
	पक्ष RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_अभिव्यक्ति_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    अचर वर्ण *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    यदि (!c_parser_get_builtin_args (parser, name, &cexpr_list, असत्य,
					    &close_paren_loc))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    यदि (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }

	    c_अभिव्यक्ति_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, सत्य, सत्य);
	    रूख arg = arg_p->मान;
	    यदि (error_operand_p (arg))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    रूख type = TYPE_MAIN_VARIANT (रूख_TYPE (arg));
	    यदि (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (रूख_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (रूख_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    arg = c_fully_fold (arg, असत्य, रिक्त);
	    अभिव्यक्ति.मान = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_paren_loc);
	    रोक;
	  }
	पक्ष RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    रूख sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    अभिव्यक्ति.मान = objc_build_selector_अभिव्यक्ति (loc, sel);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_loc);
	  }
	  रोक;
	पक्ष RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    रूख id = c_parser_peek_token (parser)->मान;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    अभिव्यक्ति.मान = objc_build_protocol_अभिव्यक्ति (id);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_loc);
	  }
	  रोक;
	पक्ष RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    यदि (!parens.require_open (parser))
	      {
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    t1 = c_parser_type_name (parser);
	    यदि (t1 == रिक्त)
	      {
		अभिव्यक्ति.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
		रोक;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    रूख type = groktypename (t1, रिक्त, रिक्त);
	    अभिव्यक्ति.मान = objc_build_encode_अभिव्यक्ति (type);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_loc);
	  }
	  रोक;
	पक्ष RID_GENERIC:
	  अभिव्यक्ति = c_parser_generic_selection (parser);
	  रोक;
	पक्ष RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  अभिव्यक्ति.set_error ();
	  रोक;
	/* C23 'nullptr' literal.  */
	पक्ष RID_NULLPTR:
	  c_parser_consume_token (parser);
	  अभिव्यक्ति.मान = nullptr_गाँठो;
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  रोक;
	पक्ष RID_TRUE:
	  c_parser_consume_token (parser);
	  अभिव्यक्ति.मान = boolean_true_गाँठो;
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
	  रोक;
	पक्ष RID_FALSE:
	  c_parser_consume_token (parser);
	  अभिव्यक्ति.मान = boolean_false_गाँठो;
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
	  रोक;
	स्वभाव:
	  c_parser_error (parser, "expected expression");
	  अभिव्यक्ति.set_error ();
	  रोक;
	}
      रोक;
    पक्ष CPP_OPEN_SQUARE:
      यदि (c_dialect_objc ())
	{
	  रूख receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  अभिव्यक्ति.मान = objc_build_message_अभिव्यक्ति (receiver, args);
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, loc, close_loc);
	  रोक;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    स्वभाव:
      c_parser_error (parser, "expected expression");
      अभिव्यक्ति.set_error ();
      रोक;
    }
 out:
  फर्काऊ c_parser_postfix_expression_after_primary
    (parser, अभिव्यक्ति_LOC_OR_LOC (अभिव्यक्ति.मान, loc), अभिव्यक्ति);
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      संरचना c_declspecs *scspecs,
					      संरचना c_type_name *type_name,
					      location_t type_loc)
{
  रूख type;
  संरचना c_अभिव्यक्ति init;
  तार्किक non_const;
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  location_t start_loc;
  रूख type_अभिव्यक्ति = NULL_रूख;
  तार्किक type_अभिव्यक्ति_const = सत्य;
  तार्किक constexpr_p = scspecs ? scspecs->constexpr_p : असत्य;
  अचिन्हित पूर्णाङ्क underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (पङ्क्ति_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  यदि (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_रूख);
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
	  रोक;

	पक्ष ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  रोक;

	स्वभाव:
	  रोक;
	}
    }
  start_init (NULL_रूख, रिक्त,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_अभिव्यक्ति, &type_अभिव्यक्ति_const);
  तार्किक varsize_p = असत्य;
  यदि (type != error_mark_गाँठो && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = सत्य;
    }
  अन्यथा यदि (रूख_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_गाँठो;
    }
  यदि (constexpr_p && type != error_mark_गाँठो)
    {
      रूख type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      यदि (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      अन्यथा यदि (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, असत्य, रिक्त, varsize_p);
  यदि (constexpr_p)
    finish_underspecified_init (NULL_रूख, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  यदि (type != error_mark_गाँठो
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_गाँठो;
    }

  यदि (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.मान && रूख_CODE (init.मान) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.मान)
	       : init.original_code == C_MAYBE_CONST_अभिव्यक्ति);
  non_const |= !type_अभिव्यक्ति_const;
  अचिन्हित पूर्णाङ्क alignas_align = 0;
  यदि (type != error_mark_गाँठो
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      यदि (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  अभिव्यक्ति.मान = build_compound_literal (start_loc, type, init.मान, non_const,
				       alignas_align, scspecs);
  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, init.src_range);
  अभिव्यक्ति.m_decimal = 0;
  अभिव्यक्ति.original_code = ERROR_MARK;
  अभिव्यक्ति.original_type = रिक्त;
  यदि (type != error_mark_गाँठो
      && अभिव्यक्ति.मान != error_mark_गाँठो
      && type_अभिव्यक्ति)
    {
      यदि (रूख_CODE (अभिव्यक्ति.मान) == C_MAYBE_CONST_अभिव्यक्ति)
	{
	  gcc_assert (C_MAYBE_CONST_अभिव्यक्ति_PRE (अभिव्यक्ति.मान) == NULL_रूख);
	  C_MAYBE_CONST_अभिव्यक्ति_PRE (अभिव्यक्ति.मान) = type_अभिव्यक्ति;
	}
      अन्यथा
	{
	  gcc_assert (!non_const);
	  अभिव्यक्ति.मान = build2 (C_MAYBE_CONST_अभिव्यक्ति, type,
			       type_अभिव्यक्ति, अभिव्यक्ति.मान);
	}
    }
  फर्काऊ c_parser_postfix_expression_after_primary (parser, start_loc, अभिव्यक्ति);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

स्थिर तार्किक
sizeof_ptr_memacc_comptypes (रूख type1, रूख type2)
{
  फर्काऊ comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

स्थिर शून्य
warn_for_abs (location_t loc, रूख fndecl, रूख arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  यदि (c_inhibit_evaluation_warnings)
    फर्काऊ;

  रूख atype = रूख_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  यदि (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && रूख_CODE (atype) != COMPLEX_TYPE)
    फर्काऊ;

  गणना built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  विकल्प (fcode)
    {
    पक्ष BUILT_IN_ABS:
    पक्ष BUILT_IN_LABS:
    पक्ष BUILT_IN_LLABS:
    पक्ष BUILT_IN_IMAXABS:
      यदि (!INTEGRAL_TYPE_P (atype))
	{
	  यदि (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मान,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  अन्यथा यदि (रूख_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मान,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  अन्यथा
	    gcc_unreachable ();
	  फर्काऊ;
	}
      यदि (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_मान,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      रोक;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      यदि (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  यदि (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मान,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  अन्यथा यदि (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मान,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  अन्यथा यदि (रूख_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मान,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  अन्यथा
	    gcc_unreachable ();
	  फर्काऊ;
	}
      रोक;

    CASE_FLT_FN (BUILT_IN_CABS):
      यदि (रूख_CODE (atype) != COMPLEX_TYPE)
	{
	  यदि (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मान,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  अन्यथा यदि (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मान,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  अन्यथा
	    gcc_unreachable ();

	  फर्काऊ;
	}
      रोक;

    पक्ष BUILT_IN_FABSD32:
    पक्ष BUILT_IN_FABSD64:
    पक्ष BUILT_IN_FABSD128:
    पक्ष BUILT_IN_FABSD64X:
      यदि (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  यदि (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मान,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  अन्यथा यदि (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मान,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  अन्यथा यदि (रूख_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मान,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  अन्यथा
	    gcc_unreachable ();
	  फर्काऊ;
	}
      रोक;

    स्वभाव:
      फर्काऊ;
    }

  यदि (!TYPE_ARG_TYPES (रूख_TYPE (fndecl)))
    फर्काऊ;

  रूख ftype = रूख_मान (TYPE_ARG_TYPES (रूख_TYPE (fndecl)));
  यदि (रूख_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (रूख_CODE (ftype) == COMPLEX_TYPE);
      atype = रूख_TYPE (atype);
      ftype = रूख_TYPE (ftype);
    }

  यदि (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_मान,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t अभिव्यक्ति_loc,
					   संरचना c_अभिव्यक्ति अभिव्यक्ति)
{
  संरचना c_अभिव्यक्ति orig_अभिव्यक्ति;
  रूख ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  रूख sizeof_arg[6];
  अचिन्हित पूर्णाङ्क literal_zero_mask;
  अचिन्हित पूर्णाङ्क i;
  vec<रूख, va_gc> *exprlist;
  vec<रूख, va_gc> *origtypes = रिक्त;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  जबसम्म (सत्य)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_रूख;
	  यदि (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).मान;

	  यदि (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      यदि (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).मान;

	      अभिव्यक्ति.मान = build_omp_array_section (op_loc, अभिव्यक्ति.मान, idx,
						    len);
	    }
	  अन्यथा
	    अभिव्यक्ति.मान = build_array_ref (op_loc, अभिव्यक्ति.मान, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = अभिव्यक्ति.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	  अभिव्यक्ति.original_code = ERROR_MARK;
	  अभिव्यक्ति.original_type = रिक्त;
	  अभिव्यक्ति.m_decimal = 0;
	  रोक;
	पक्ष CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    लागि (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_रूख;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = रिक्त;
	    अन्यथा यदि (रूख_CODE (अभिव्यक्ति.मान) == FUNCTION_DECL
		     && fndecl_built_in_p (अभिव्यक्ति.मान, BUILT_IN_CLASSIFY_TYPE)
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
		ret.अभिव्यक्ति = NULL_रूख;
		ret.spec = error_mark_गाँठो;
		ret.अभिव्यक्ति_const_operands = असत्य;
		यदि (type != रिक्त)
		  ret.spec = groktypename (type, &ret.अभिव्यक्ति,
					   &ret.अभिव्यक्ति_const_operands);
		parens.skip_until_found_close (parser);
		अभिव्यक्ति.मान = build_int_cst (integer_type_गाँठो,
					    type_to_class (ret.spec));
		रोक;
	      }
	    अन्यथा
	      exprlist = c_parser_अभिव्यक्ति_list (parser, सत्य, असत्य, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_अभिव्यक्ति = अभिव्यक्ति;
	  mark_exp_read (अभिव्यक्ति.मान);
	  यदि (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      अभिव्यक्ति.मान, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  यदि (रूख_CODE (अभिव्यक्ति.मान) == FUNCTION_DECL)
	    {
	      यदि (fndecl_built_in_p (अभिव्यक्ति.मान, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  रूख arg0 = (*exprlist)[0];
		  रूख arg2 = (*exprlist)[2];
		  warn_for_memset (अभिव्यक्ति_loc, arg0, arg2, literal_zero_mask);
		}
	      यदि (warn_absolute_मान
		  && fndecl_built_in_p (अभिव्यक्ति.मान, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (अभिव्यक्ति_loc, अभिव्यक्ति.मान, (*exprlist)[0]);
	      यदि (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (अभिव्यक्ति.मान))
		{
		  error_at (अभिव्यक्ति_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = सत्य;
		}
	      यदि (warn_calloc_transposed_args)
		यदि (रूख attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (रूख_TYPE (अभिव्यक्ति.मान))))
		  यदि (रूख_मान (attr) && रूख_CHAIN (रूख_मान (attr)))
		    warn_for_calloc (sizeof_arg_loc, अभिव्यक्ति.मान, exprlist,
				     sizeof_arg, attr);
	    }

	  start = अभिव्यक्ति.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  अभिव्यक्ति.मान
	    = c_build_function_call_vec (अभिव्यक्ति_loc, arg_loc, अभिव्यक्ति.मान,
					 exprlist, origtypes);
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	  अभिव्यक्ति.m_decimal = 0;

	  अभिव्यक्ति.original_code = ERROR_MARK;
	  यदि (रूख_CODE (अभिव्यक्ति.मान) == INTEGER_CST
	      && रूख_CODE (orig_अभिव्यक्ति.मान) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_अभिव्यक्ति.मान, BUILT_IN_CONSTANT_P))
	    अभिव्यक्ति.original_code = C_MAYBE_CONST_अभिव्यक्ति;
	  अभिव्यक्ति.original_type = रिक्त;
	  यदि (exprlist)
	    {
	      release_रूख_vector (exprlist);
	      release_रूख_vector (origtypes);
	    }
	  arg_loc.release ();
	  रोक;
	पक्ष CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  अभिव्यक्ति = default_function_array_conversion (अभिव्यक्ति_loc, अभिव्यक्ति);
	  यदि (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->मान;
	      comp_loc = comp_tok->location;
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected identifier");
	      अभिव्यक्ति.set_error ();
	      अभिव्यक्ति.original_code = ERROR_MARK;
              अभिव्यक्ति.original_type = रिक्त;
	      फर्काऊ अभिव्यक्ति;
	    }
	  start = अभिव्यक्ति.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  अभिव्यक्ति.मान = build_component_ref (op_loc, अभिव्यक्ति.मान, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	  अभिव्यक्ति.original_code = ERROR_MARK;
	  यदि (रूख_CODE (अभिव्यक्ति.मान) != COMPONENT_REF)
	    अभिव्यक्ति.original_type = रिक्त;
	  अन्यथा
	    {
	      /* Remember the original type of a bitfield.  */
	      रूख field = रूख_OPERAND (अभिव्यक्ति.मान, 1);
	      यदि (रूख_CODE (field) != FIELD_DECL)
		अभिव्यक्ति.original_type = रिक्त;
	      अन्यथा
		अभिव्यक्ति.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  अभिव्यक्ति.m_decimal = 0;
	  रोक;
	पक्ष CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, सत्य, असत्य);
	  यदि (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->मान;
	      comp_loc = comp_tok->location;
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected identifier");
	      अभिव्यक्ति.set_error ();
	      अभिव्यक्ति.original_code = ERROR_MARK;
	      अभिव्यक्ति.original_type = रिक्त;
	      फर्काऊ अभिव्यक्ति;
	    }
	  start = अभिव्यक्ति.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  अभिव्यक्ति.मान = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								अभिव्यक्ति.मान,
								RO_ARROW),
					    ident, comp_loc,
					    अभिव्यक्ति.get_location ());
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	  अभिव्यक्ति.original_code = ERROR_MARK;
	  यदि (रूख_CODE (अभिव्यक्ति.मान) != COMPONENT_REF)
	    अभिव्यक्ति.original_type = रिक्त;
	  अन्यथा
	    {
	      /* Remember the original type of a bitfield.  */
	      रूख field = रूख_OPERAND (अभिव्यक्ति.मान, 1);
	      यदि (रूख_CODE (field) != FIELD_DECL)
		अभिव्यक्ति.original_type = रिक्त;
	      अन्यथा
		अभिव्यक्ति.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  अभिव्यक्ति.m_decimal = 0;
	  रोक;
	पक्ष CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = अभिव्यक्ति.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (अभिव्यक्ति.मान);
	  अभिव्यक्ति = default_function_array_conversion (अभिव्यक्ति_loc, अभिव्यक्ति);
	  अभिव्यक्ति.मान = build_unary_op (op_loc, POSTINCREMENT_अभिव्यक्ति,
				       अभिव्यक्ति.मान, असत्य);
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	  अभिव्यक्ति.original_code = ERROR_MARK;
	  अभिव्यक्ति.original_type = रिक्त;
	  रोक;
	पक्ष CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = अभिव्यक्ति.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (अभिव्यक्ति.मान);
	  अभिव्यक्ति = default_function_array_conversion (अभिव्यक्ति_loc, अभिव्यक्ति);
	  अभिव्यक्ति.मान = build_unary_op (op_loc, POSTDECREMENT_अभिव्यक्ति,
				       अभिव्यक्ति.मान, असत्य);
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	  अभिव्यक्ति.original_code = ERROR_MARK;
	  अभिव्यक्ति.original_type = रिक्त;
	  रोक;
	स्वभाव:
	  फर्काऊ अभिव्यक्ति;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

स्थिर संरचना c_अभिव्यक्ति
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  यदि (c_parser_next_token_is (parser, CPP_COMMA))
    अभिव्यक्ति = convert_lvalue_to_rvalue (tloc, अभिव्यक्ति, सत्य, असत्य);
  जबसम्म (c_parser_next_token_is (parser, CPP_COMMA))
    {
      संरचना c_अभिव्यक्ति next;
      रूख lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t अभिव्यक्ति_loc;
      c_parser_consume_token (parser);
      अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      lhsval = अभिव्यक्ति.मान;
      जबसम्म (रूख_CODE (lhsval) == COMPOUND_अभिव्यक्ति
	     || रूख_CODE (lhsval) == NOP_अभिव्यक्ति)
	{
	  यदि (रूख_CODE (lhsval) == COMPOUND_अभिव्यक्ति)
	    lhsval = रूख_OPERAND (lhsval, 1);
	  अन्यथा
	    lhsval = रूख_OPERAND (lhsval, 0);
	}
      यदि (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      यदि (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  रूख val = embed->मान;
	  अचिन्हित last = RAW_DATA_LENGTH (val) - 1;
	  next.मान = build_int_cst (रूख_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_गाँठो;
	  c_parser_consume_token (parser);
	}
      अन्यथा
	{
	  next = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  next = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, next, सत्य, असत्य);
	}
      अभिव्यक्ति.मान = build_compound_अभिव्यक्ति (loc, अभिव्यक्ति.मान, next.मान);
      अभिव्यक्ति.original_code = COMPOUND_अभिव्यक्ति;
      अभिव्यक्ति.original_type = next.original_type;
      अभिव्यक्ति.m_decimal = 0;
    }
  फर्काऊ अभिव्यक्ति;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_expression_conv (c_parser *parser)
{
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  location_t loc = c_parser_peek_token (parser)->location;
  अभिव्यक्ति = c_parser_expression (parser);
  अभिव्यक्ति = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, सत्य, असत्य);
  फर्काऊ अभिव्यक्ति;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

स्थिर अन्तःस्थ शून्य
c_parser_check_literal_zero (c_parser *parser, अचिन्हित *literal_zero_mask,
			     अचिन्हित पूर्णाङ्क idx)
{
  यदि (idx >= HOST_BITS_PER_INT)
    फर्काऊ;

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
      यदि (integer_zerop (tok->मान)
	  && !रूख_OVERFLOW (tok->मान)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    स्वभाव:
      रोक;
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

स्थिर vec<रूख, va_gc> *
c_parser_अभिव्यक्ति_list (c_parser *parser, तार्किक convert_p, तार्किक fold_p,
		    vec<रूख, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, रूख *sizeof_arg,
		    vec<location_t> *locations,
		    अचिन्हित पूर्णाङ्क *literal_zero_mask)
{
  vec<रूख, va_gc> *ret;
  vec<रूख, va_gc> *orig_types;
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  अचिन्हित पूर्णाङ्क idx = 0;
  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = असत्य;

  ret = make_रूख_vector ();
  यदि (p_orig_types == रिक्त)
    orig_types = रिक्त;
  अन्यथा
    orig_types = make_रूख_vector ();

  यदि (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  यदि (convert_p)
    अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति.get_location (), अभिव्यक्ति, सत्य, सत्य);
  यदि (fold_p)
    अभिव्यक्ति.मान = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
  ret->quick_थप (अभिव्यक्ति.मान);
  यदि (orig_types)
    orig_types->quick_थप (अभिव्यक्ति.original_type);
  यदि (locations)
    locations->safe_थप (अभिव्यक्ति.get_location ());
  यदि (sizeof_arg != रिक्त
      && (अभिव्यक्ति.original_code == SIZEOF_अभिव्यक्ति
	  || अभिव्यक्ति.original_code == PAREN_SIZEOF_अभिव्यक्ति))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  जबसम्म (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  रूख मान = embed->मान;
	  अभिव्यक्ति.original_code = INTEGER_CST;
	  अभिव्यक्ति.original_type = integer_type_गाँठो;
	  अभिव्यक्ति.मान = NULL_रूख;
	  set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, embed->get_range ());
	  अभिव्यक्ति.m_decimal = 0;
	  लागि (अचिन्हित पूर्णाङ्क i = 0; i < (अचिन्हित) RAW_DATA_LENGTH (मान); i++)
	    {
	      यदि (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (मान)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      अभिव्यक्ति.मान = build_int_cst (integer_type_गाँठो,
					  RAW_DATA_UCHAR_ELT (मान, i));
	      vec_safe_थप (ret, अभिव्यक्ति.मान);
	      यदि (orig_types)
		vec_safe_थप (orig_types, अभिव्यक्ति.original_type);
	      यदि (locations)
		locations->safe_थप (अभिव्यक्ति.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  जारी;
	}
      यदि (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      यदि (convert_p)
	अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति.get_location (), अभिव्यक्ति, सत्य,
					 सत्य);
      यदि (fold_p)
	अभिव्यक्ति.मान = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
      vec_safe_थप (ret, अभिव्यक्ति.मान);
      यदि (orig_types)
	vec_safe_थप (orig_types, अभिव्यक्ति.original_type);
      यदि (locations)
	locations->safe_थप (अभिव्यक्ति.get_location ());
      यदि (++idx < 6
	  && sizeof_arg != रिक्त
	  && (अभिव्यक्ति.original_code == SIZEOF_अभिव्यक्ति
	      || अभिव्यक्ति.original_code == PAREN_SIZEOF_अभिव्यक्ति))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  यदि (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  फर्काऊ ret;
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
c_parser_objc_class_definition (c_parser *parser, रूख attributes)
{
  तार्किक iface_p;
  रूख id1;
  रूख superclass;
  यदि (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = सत्य;
  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = असत्य;
  अन्यथा
    gcc_unreachable ();

  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      फर्काऊ;
    }
  id1 = c_parser_peek_token (parser)->मान;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      रूख id2;
      रूख proto = NULL_रूख;
      matching_parens parens;
      parens.consume_open (parser);
      यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  यदि (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_रूख;
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	      फर्काऊ;
	    }
	}
      अन्यथा
	{
	  id2 = c_parser_peek_token (parser)->मान;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      यदि (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  फर्काऊ;
	}
      यदि (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      फर्काऊ;
    }
  यदि (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  फर्काऊ;
	}
      superclass = c_parser_peek_token (parser)->मान;
      c_parser_consume_token (parser);
    }
  अन्यथा
    superclass = NULL_रूख;
  यदि (iface_p)
    {
      रूख proto = NULL_रूख;
      यदि (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  अन्यथा
    objc_start_class_implementation (id1, superclass);
  यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  यदि (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  अन्यथा
    {
      objc_continue_implementation ();
      फर्काऊ;
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
  जबसम्म (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      रूख decls;
      /* Parse any stray semicolon.  */
      यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  जारी;
	}
      /* Stop if at the end of the instance variables.  */
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  रोक;
	}
      /* Parse any objc-visibility-spec.  */
      यदि (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  जारी;
	}
      अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  जारी;
	}
      अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  जारी;
	}
      अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  जारी;
	}
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, रिक्त, NULL_रूख);
	  जारी;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, रिक्त);
      यदि (decls == रिक्त)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  यदि (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = असत्य;
	  जारी;
	}
      अन्यथा
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  रूख ivar = nreverse (decls);
	  लागि (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_गाँठो (ivar));
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
  जबसम्म (सत्य)
    {
      रूख id;
      यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	  parser->error = असत्य;
	  फर्काऊ;
	}
      id = c_parser_peek_token (parser)->मान;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
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
  रूख id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
      फर्काऊ;
    }
  id1 = c_parser_peek_token (parser)->मान;
  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
      फर्काऊ;
    }
  id2 = c_parser_peek_token (parser)->मान;
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
c_parser_objc_protocol_definition (c_parser *parser, रूख attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      फर्काऊ;
    }
  यदि (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      जबसम्म (सत्य)
	{
	  रूख id;
	  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      रोक;
	    }
	  id = c_parser_peek_token (parser)->मान;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    रोक;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  अन्यथा
    {
      रूख id = c_parser_peek_token (parser)->मान;
      रूख proto = NULL_रूख;
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = सत्य;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = असत्य;
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
      फर्काऊ सत्य;
    पक्ष CPP_MINUS:
      c_parser_consume_token (parser);
      फर्काऊ असत्य;
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
  रूख decl, attributes = NULL_रूख, अभिव्यक्ति = NULL_रूख;
  parser->objc_pq_context = सत्य;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &अभिव्यक्ति);
  यदि (decl == error_mark_गाँठो)
    फर्काऊ;  /* Bail here. */

  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  यदि (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      फर्काऊ;
    }

  parser->objc_pq_context = असत्य;
  यदि (objc_start_method_definition (is_class_method, decl, attributes, अभिव्यक्ति))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  अन्यथा
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
  जबसम्म (सत्य)
    {
      /* The list is terminated by @end.  */
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  रोक;
	पक्ष CPP_PLUS:
	पक्ष CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  रोक;
	पक्ष CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, रिक्त, NULL_रूख);
	  रोक;
	पक्ष CPP_EOF:
	  फर्काऊ;
	स्वभाव:
	  यदि (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    फर्काऊ;
	  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (सत्य);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (असत्य);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    c_parser_declaration_or_fndef (parser, असत्य, असत्य, सत्य,
					   असत्य, सत्य, असत्य);
	  रोक;
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
  रूख decl, attributes = NULL_रूख;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = सत्य;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    रिक्त);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = असत्य;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  यदि (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      फर्काऊ;
    }

  यदि (decl != error_mark_गाँठो)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

स्थिर तार्किक
c_parser_objc_maybe_method_attributes (c_parser* parser, रूख* attributes)
{
  तार्किक bad = असत्य;
  यदि (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_रूख;
      bad = सत्य;
    }

  यदि (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  यदि (*attributes == NULL_रूख || bad)
    फर्काऊ bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    फर्काऊ bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  फर्काऊ सत्य;
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

स्थिर रूख
c_parser_objc_method_decl (c_parser *parser, तार्किक is_class_method,
			   रूख *attributes, रूख *अभिव्यक्ति)
{
  रूख type = NULL_रूख;
  रूख sel;
  रूख parms = NULL_रूख;
  तार्किक ellipsis = असत्य;
  तार्किक attr_err = असत्य;

  *attributes = NULL_रूख;
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
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
  यदि (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      रूख tsel = sel;
      रूख list = NULL_रूख;
      जबसम्म (सत्य)
	{
	  रूख atype = NULL_रूख, id, keyworddecl;
	  रूख param_attr = NULL_रूख;
	  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    रोक;
	  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  यदि (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      फर्काऊ error_mark_गाँठो;
	    }
	  id = c_parser_peek_token (parser)->मान;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  यदि (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    रोक;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_गाँठो (रूख_LIST);
      जबसम्म (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  संरचना c_parm *parm;
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = सत्य;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      रोक;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_रूख, असत्य);
	  यदि (parm == रिक्त)
	    रोक;
	  parms = chainon (parms,
			   build_रूख_list (NULL_रूख, grokparm (parm, अभिव्यक्ति)));
	}
      sel = list;
    }
  अन्यथा
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  यदि (sel == रिक्त)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      फर्काऊ error_mark_गाँठो;
    }

  यदि (attr_err)
    फर्काऊ error_mark_गाँठो;

  फर्काऊ objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

स्थिर रूख
c_parser_objc_type_name (c_parser *parser)
{
  रूख quals = NULL_रूख;
  संरचना c_type_name *type_name = रिक्त;
  रूख type = NULL_रूख;
  जबसम्म (सत्य)
    {
      c_token *token = c_parser_peek_token (parser);
      यदि (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_रूख_list (NULL_रूख, token->मान), quals);
	  c_parser_consume_token (parser);
	}
      अन्यथा
	रोक;
    }
  यदि (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  यदि (type_name)
    type = groktypename (type_name, रिक्त, रिक्त);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  यदि (type == error_mark_गाँठो)
    type = NULL_रूख;

  फर्काऊ build_रूख_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

स्थिर रूख
c_parser_objc_protocol_refs (c_parser *parser)
{
  रूख list = NULL_रूख;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  जबसम्म (सत्य)
    {
      रूख id;
      यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  रोक;
	}
      id = c_parser_peek_token (parser)->मान;
      list = chainon (list, build_रूख_list (NULL_रूख, id));
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  फर्काऊ list;
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
  रूख stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  जबसम्म (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      संरचना c_parm *parm;
      रूख parameter_declaration = error_mark_गाँठो;
      तार्किक seen_open_paren = असत्य;

      c_parser_consume_token (parser);
      matching_parens parens;
      यदि (!parens.require_open (parser))
	seen_open_paren = सत्य;
      यदि (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_रूख;
	}
      अन्यथा
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_रूख, असत्य);
	  यदि (parm == रिक्त)
	    parameter_declaration = error_mark_गाँठो;
	  अन्यथा
	    parameter_declaration = grokparm (parm, रिक्त);
	}
      यदि (seen_open_paren)
	parens.require_close (parser);
      अन्यथा
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      यदि (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  यदि (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
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
  रूख अभिव्यक्ति, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      संरचना c_अभिव्यक्ति ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, असत्य, असत्य);
      अभिव्यक्ति = ce.मान;
      अभिव्यक्ति = c_fully_fold (अभिव्यक्ति, असत्य, रिक्त);
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    अभिव्यक्ति = error_mark_गाँठो;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, अभिव्यक्ति, stmt);
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

स्थिर रूख
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  रूख मान = token->मान;
  यदि (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      फर्काऊ मान;
    }
  यदि (token->type != CPP_KEYWORD)
    फर्काऊ NULL_रूख;
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
      फर्काऊ मान;
    स्वभाव:
      फर्काऊ NULL_रूख;
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

स्थिर रूख
c_parser_objc_selector_arg (c_parser *parser)
{
  रूख sel = c_parser_objc_selector (parser);
  रूख list = NULL_रूख;
  यदि (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    फर्काऊ sel;
  जबसम्म (सत्य)
    {
      यदि (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_रूख_list (sel, NULL_रूख));
	  list = chainon (list, build_रूख_list (NULL_रूख, NULL_रूख));
	}
      अन्यथा
	{
	  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    फर्काऊ list;
	  list = chainon (list, build_रूख_list (sel, NULL_रूख));
	}
      sel = c_parser_objc_selector (parser);
      यदि (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	रोक;
    }
  फर्काऊ list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

स्थिर रूख
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  यदि (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      रूख id = c_parser_peek_token (parser)->मान;
      c_parser_consume_token (parser);
      फर्काऊ objc_get_class_reference (id);
    }
  संरचना c_अभिव्यक्ति ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, असत्य, असत्य);
  फर्काऊ c_fully_fold (ce.मान, असत्य, रिक्त);
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

स्थिर रूख
c_parser_objc_message_args (c_parser *parser)
{
  रूख sel = c_parser_objc_selector (parser);
  रूख list = NULL_रूख;
  यदि (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    फर्काऊ sel;
  जबसम्म (सत्य)
    {
      रूख keywordexpr;
      यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	फर्काऊ error_mark_गाँठो;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_रूख_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      यदि (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	रोक;
    }
  फर्काऊ list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

स्थिर रूख
c_parser_objc_keywordexpr (c_parser *parser)
{
  रूख ret;
  vec<रूख, va_gc> *अभिव्यक्ति_list = c_parser_अभिव्यक्ति_list (parser, सत्य, सत्य,
						रिक्त, रिक्त, रिक्त, रिक्त);
  यदि (vec_safe_length (अभिव्यक्ति_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*अभिव्यक्ति_list)[0];
    }
  अन्यथा
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_रूख_list_vec (अभिव्यक्ति_list);
    }
  release_रूख_vector (अभिव्यक्ति_list);
  फर्काऊ ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
स्थिर तार्किक
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   संरचना c_declspecs *specs)
{
  यदि (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      फर्काऊ सत्य;
    }
  फर्काऊ असत्य;
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

  तार्किक syntax_error = असत्य;
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = सत्य;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      अन्यथा
	जबसम्म (सत्य)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    यदि (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		यदि (token->type == CPP_CLOSE_PAREN)
		  रोक;
		c_parser_consume_token (parser);
		जारी;
	      }

	    रूख attr_name = NULL_रूख;
	    गणना rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    तार्किक add_at = असत्य;
	    यदि (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		यदि (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->मान;
		    add_at = सत्य;
		  }
		अन्यथा
		  attr_name = ridpointers[(पूर्णाङ्क)keyword];
	      }
	    अन्यथा यदि (token->type == CPP_NAME)
	      attr_name = token->मान;
	    c_parser_consume_token (parser);

	    गणना objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = नूतन property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_थप (prop);

	    रूख meth_name;
	    विकल्प (prop->prop_kind)
	      {
	      स्वभाव: रोक;
	      पक्ष OBJC_PROPERTY_ATTR_UNKNOWN:
		यदि (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		अन्यथा
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = सत्य;
		रोक;

	      पक्ष OBJC_PROPERTY_ATTR_GETTER:
	      पक्ष OBJC_PROPERTY_ATTR_SETTER:
		यदि (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = सत्य;
		    रोक;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		यदि (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = सत्य;
		    रोक;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->मान;
		c_parser_consume_token (parser);
		यदि (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    यदि (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = सत्य;
		      }
		    अन्यथा
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		अन्यथा
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		रोक;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    रोक;
	}
      parser->objc_property_attr_context = असत्य;

      यदि (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      अन्यथा
	syntax_error = असत्य, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  रूख properties = c_parser_struct_declaration (parser, रिक्त);

  यदि (properties == error_mark_गाँठो)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
  अन्यथा
    {
      यदि (properties == NULL_रूख)
	c_parser_error (parser, "expected identifier");
      अन्यथा
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  लागि (; properties; properties = रूख_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_गाँठो (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  जबसम्म (!prop_attr_list.is_empty())
    delete prop_attr_list.झिक ();
  prop_attr_list.release ();
  parser->error = असत्य;
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
  रूख list = NULL_रूख;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  जबसम्म (सत्य)
    {
      रूख property, ivar;
      यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = असत्य;
	  फर्काऊ;
	}
      property = c_parser_peek_token (parser)->मान;
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	      parser->error = असत्य;
	      फर्काऊ;
	    }
	  ivar = c_parser_peek_token (parser)->मान;
	  c_parser_consume_token (parser);
	}
      अन्यथा
	ivar = NULL_रूख;
      list = chainon (list, build_रूख_list (ivar, property));
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
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
  रूख list = NULL_रूख;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  जबसम्म (सत्य)
    {
      रूख property;
      यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	  parser->error = असत्य;
	  फर्काऊ;
	}
      property = c_parser_peek_token (parser)->मान;
      list = chainon (list, build_रूख_list (NULL_रूख, property));
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
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
  फर्काऊ सत्य;
}

/* Parse a pragma GCC novector.  */

स्थिर तार्किक
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  फर्काऊ सत्य;
}

/* Parse a pragma GCC unroll.  */

स्थिर अचिन्हित लघु
c_parser_pragma_unroll (c_parser *parser)
{
  अचिन्हित लघु unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  रूख अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
  mark_exp_read (अभिव्यक्ति);
  अभिव्यक्ति = c_fully_fold (अभिव्यक्ति, असत्य, रिक्त);
  HOST_WIDE_INT lunroll = 0;
  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (अभिव्यक्ति))
      || रूख_CODE (अभिव्यक्ति) != INTEGER_CST
      || (lunroll = रूख_to_shwi (अभिव्यक्ति)) < 0
      || lunroll >= अच_लघु_उच्च)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", अच_लघु_उच्च);
      unroll = 0;
    }
  अन्यथा
    {
      unroll = (अचिन्हित लघु)lunroll;
      यदि (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  फर्काऊ unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

स्थिर तार्किक
c_parser_pragma (c_parser *parser, गणना pragma_context context, तार्किक *if_p,
		 रूख before_labels)
{
  अचिन्हित पूर्णाङ्क id;
  अचर वर्ण *construct = रिक्त;

  आगत_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  यदि (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	आगत_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = सत्य;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
      फर्काऊ असत्य;
    }

  विकल्प (id)
    {
    पक्ष PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OACC_ENTER_DATA:
      यदि (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  यदि (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	      फर्काऊ सत्य;
	    }
	  गच्छ bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, सत्य);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OACC_EXIT_DATA:
      यदि (context != pragma_compound)
	{
	  construct = "acc exit data";
	  गच्छ in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, असत्य);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OACC_ROUTINE:
      यदि (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	  फर्काऊ असत्य;
	}
      c_parser_oacc_routine (parser, context);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OACC_UPDATE:
      यदि (context != pragma_compound)
	{
	  construct = "acc update";
	  गच्छ in_compound;
	}
      c_parser_oacc_update (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_BARRIER:
      यदि (context != pragma_compound)
	{
	  construct = "omp barrier";
	  गच्छ in_compound;
	}
      c_parser_omp_barrier (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_DEPOBJ:
      यदि (context != pragma_compound)
	{
	  construct = "omp depobj";
	  गच्छ in_compound;
	}
      c_parser_omp_depobj (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_FLUSH:
      यदि (context != pragma_compound)
	{
	  construct = "omp flush";
	  गच्छ in_compound;
	}
      c_parser_omp_flush (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_INTEROP:
      यदि (context != pragma_compound)
	{
	  construct = "omp interop";
	  गच्छ in_compound;
	}
      c_parser_omp_interop (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_TASKWAIT:
      यदि (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  गच्छ in_compound;
	}
      c_parser_omp_taskwait (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_TASKYIELD:
      यदि (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  गच्छ in_compound;
	}
      c_parser_omp_taskyield (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_CANCEL:
      यदि (context != pragma_compound)
	{
	  construct = "omp cancel";
	  गच्छ in_compound;
	}
      c_parser_omp_cancel (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_CANCELLATION_POINT:
      फर्काऊ c_parser_omp_cancellation_point (parser, context);

    पक्ष PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_TARGET:
      फर्काऊ c_parser_omp_target (parser, context, if_p);

    पक्ष PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_DECLARE:
      फर्काऊ c_parser_omp_declare (parser, context);

    पक्ष PRAGMA_OMP_REQUIRES:
      यदि (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	  फर्काऊ असत्य;
	}
      c_parser_omp_requires (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_ASSUMES:
      यदि (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	  फर्काऊ असत्य;
	}
      c_parser_omp_assumes (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      फर्काऊ सत्य;

    पक्ष PRAGMA_OMP_ERROR:
      फर्काऊ c_parser_omp_error (parser, context);

    पक्ष PRAGMA_OMP_ORDERED:
      फर्काऊ c_parser_omp_ordered (parser, context, if_p);

    पक्ष PRAGMA_NOVECTOR:
    पक्ष PRAGMA_UNROLL:
    पक्ष PRAGMA_IVDEP:
      {
	तार्किक novector = असत्य;
	अचिन्हित लघु unroll = 0;
	तार्किक ivdep = असत्य;

	विकल्प (id)
	  {
	  पक्ष PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    रोक;
	  पक्ष PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    रोक;
	  पक्ष PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    रोक;
	  स्वभाव:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	तार्किक has_more = tok->type == CPP_PRAGMA;
	जबसम्म (has_more)
	  {
	    विकल्प (tok->pragma_kind)
	      {
	      पक्ष PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		रोक;
	      पक्ष PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		रोक;
	      पक्ष PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		रोक;
	      स्वभाव:
		has_more = असत्य;
		रोक;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	यदि (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    फर्काऊ असत्य;
	  }
	यदि (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	अन्यथा
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      फर्काऊ सत्य;

    पक्ष PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
      फर्काऊ असत्य;

    पक्ष PRAGMA_OACC_WAIT:
      यदि (context != pragma_compound)
	{
	  construct = "acc wait";
	  गच्छ in_compound;
	}
	/* FALL THROUGH.  */

    स्वभाव:
      यदि (id < PRAGMA_FIRST_EXTERNAL)
	{
	  यदि (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, रिक्त);
	      फर्काऊ असत्य;
	    }
	  c_parser_omp_construct (parser, if_p);
	  फर्काऊ सत्य;
	}
      रोक;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = सत्य;
  c_parser_skip_to_pragma_eol (parser);

  फर्काऊ असत्य;
}

/* The interface the pragma parsers have to the lexer.  */

गणना cpp_ttype
pragma_lex (रूख *मान, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  गणना cpp_ttype ret = tok->type;

  *मान = tok->मान;
  यदि (loc)
    *loc = tok->location;

  यदि (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  अन्यथा यदि (ret == CPP_STRING)
    *मान = c_parser_string_literal (the_parser, असत्य, असत्य).मान;
  अन्यथा
    {
      यदि (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  फर्काऊ ret;
}

शून्य
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  गर
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } जबसम्म (type != CPP_PRAGMA_EOL);
}

स्थिर शून्य
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  रूख name = रिक्त;

  parser->lex_joined_string = सत्य;
  c_parser_consume_pragma (parser);
  यदि (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->मान;
      c_parser_consume_token (parser);
    }
  अन्यथा
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = असत्य;

  यदि (name)
    c_common_pch_pragma (parse_in, रूख_STRING_POINTER (name));
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

  यदि (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  अन्यथा यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      विकल्प (p[0])
	{
	पक्ष 'a':
	  यदि (!म_भेद ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  अन्यथा यदि (!म_भेद ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  अन्यथा यदि (!म_भेद ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  अन्यथा यदि (!म_भेद ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  अन्यथा यदि (!म_भेद ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  रोक;
	पक्ष 'b':
	  यदि (!म_भेद ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  रोक;
	पक्ष 'c':
	  यदि (!म_भेद ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  अन्यथा यदि (!म_भेद ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  अन्यथा यदि (!म_भेद ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  अन्यथा यदि (!म_भेद ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          अन्यथा यदि (!म_भेद ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  अन्यथा यदि (!म_भेद ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  रोक;
	पक्ष 'd':
	  यदि (!म_भेद ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  अन्यथा यदि (!म_भेद ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  अन्यथा यदि (!म_भेद ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  अन्यथा यदि (!म_भेद ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  अन्यथा यदि (!म_भेद ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  अन्यथा यदि (!म_भेद ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  अन्यथा यदि (!म_भेद ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  अन्यथा यदि (!म_भेद ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  अन्यथा यदि (!म_भेद ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  अन्यथा यदि (!म_भेद ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  अन्यथा यदि (!म_भेद ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  अन्यथा यदि (!म_भेद ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  रोक;
	पक्ष 'e':
	  यदि (!म_भेद ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  रोक;
	पक्ष 'f':
	  यदि (!म_भेद ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  अन्यथा यदि (!म_भेद ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  अन्यथा यदि (!म_भेद ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  अन्यथा यदि (!म_भेद ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  अन्यथा यदि (!म_भेद ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  अन्यथा यदि (!म_भेद ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  रोक;
	पक्ष 'g':
	  यदि (!म_भेद ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  अन्यथा यदि (!म_भेद ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  रोक;
	पक्ष 'h':
	  यदि (!म_भेद ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  अन्यथा यदि (!म_भेद ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  अन्यथा यदि (!म_भेद ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  रोक;
	पक्ष 'i':
	  यदि (!म_भेद ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  अन्यथा यदि (!म_भेद ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  अन्यथा यदि (!म_भेद ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  अन्यथा यदि (!म_भेद ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  अन्यथा यदि (!म_भेद ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  अन्यथा यदि (!म_भेद ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  अन्यथा यदि (!म_भेद ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  अन्यथा यदि (!म_भेद ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  रोक;
	पक्ष 'l':
	  यदि (!म_भेद ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  अन्यथा यदि (!म_भेद ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  अन्यथा यदि (!म_भेद ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  अन्यथा यदि (!म_भेद ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  रोक;
	पक्ष 'm':
	  यदि (!म_भेद ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  अन्यथा यदि (!म_भेद ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  रोक;
	पक्ष 'n':
	  यदि (!म_भेद ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  अन्यथा यदि (!म_भेद ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  अन्यथा यदि (!म_भेद ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  अन्यथा यदि (!म_भेद ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  अन्यथा यदि (!म_भेद ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  अन्यथा यदि (!म_भेद ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  अन्यथा यदि (!म_भेद ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  अन्यथा यदि (!म_भेद ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  अन्यथा यदि (!म_भेद ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_अङ्क_GANGS;
	  अन्यथा यदि (!म_भेद ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_अङ्क_TASKS;
	  अन्यथा यदि (!म_भेद ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_अङ्क_TEAMS;
	  अन्यथा यदि (!म_भेद ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_अङ्क_THREADS;
	  अन्यथा यदि (!म_भेद ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_अङ्क_WORKERS;
	  रोक;
	पक्ष 'o':
	  यदि (!म_भेद ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  अन्यथा यदि (!म_भेद ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  रोक;
	पक्ष 'p':
	  यदि (!म_भेद ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  अन्यथा यदि (!म_भेद ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  अन्यथा यदि (!म_भेद ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  अन्यथा यदि (!म_भेद ("present_or_copy", p)
		   || !म_भेद ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  अन्यथा यदि (!म_भेद ("present_or_copyin", p)
		   || !म_भेद ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  अन्यथा यदि (!म_भेद ("present_or_copyout", p)
		   || !म_भेद ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  अन्यथा यदि (!म_भेद ("present_or_create", p)
		   || !म_भेद ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  अन्यथा यदि (!म_भेद ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  अन्यथा यदि (!म_भेद ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  अन्यथा यदि (!म_भेद ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  रोक;
	पक्ष 'r':
	  यदि (!म_भेद ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  रोक;
	पक्ष 's':
	  यदि (!म_भेद ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  अन्यथा यदि (!म_भेद ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  अन्यथा यदि (!म_भेद ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  अन्यथा यदि (!म_भेद ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  अन्यथा यदि (!म_भेद ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  अन्यथा यदि (!म_भेद ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  अन्यथा यदि (!म_भेद ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  अन्यथा यदि (!म_भेद ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  रोक;
	पक्ष 't':
	  यदि (!म_भेद ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  अन्यथा यदि (!म_भेद ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  अन्यथा यदि (!म_भेद ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  अन्यथा यदि (!म_भेद ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  अन्यथा यदि (!म_भेद ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  अन्यथा यदि (!म_भेद ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  रोक;
	पक्ष 'u':
	  यदि (!म_भेद ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  अन्यथा यदि (!म_भेद ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  अन्यथा यदि (!म_भेद ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  अन्यथा यदि (!म_भेद ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  अन्यथा यदि (!म_भेद ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  अन्यथा यदि (!म_भेद ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  अन्यथा यदि (!म_भेद ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  रोक;
	पक्ष 'v':
	  यदि (!म_भेद ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  अन्यथा यदि (!म_भेद ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  रोक;
	पक्ष 'w':
	  यदि (!म_भेद ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  अन्यथा यदि (!म_भेद ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  रोक;
	}
    }

  यदि (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  फर्काऊ result;
}

/* Validate that a clause of the given type does not already exist.  */

स्थिर शून्य
check_no_duplicate_clause (रूख clauses, गणना omp_clause_code code,
			   अचर वर्ण *name)
{
  यदि (रूख c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

स्थिर रूख
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, रूख list)
{
  vec<रूख, va_gc> *args;
  रूख t, args_रूख;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  args = c_parser_अभिव्यक्ति_list (parser, असत्य, सत्य, रिक्त, रिक्त, रिक्त, रिक्त);
  args_रूख = build_रूख_list_vec (args);

  लागि (t = args_रूख; t; t = रूख_CHAIN (t))
    {
      रूख targ = रूख_मान (t);

      यदि (targ != error_mark_गाँठो)
	{
	  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_गाँठो;
	    }
	  अन्यथा
	    {
	      रूख c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_रूख_vector (args);
  parens.require_close (parser);
  फर्काऊ list;
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
  रूख तल्लो_bound, length;
  location_t loc;
  तार्किक no_colon;
  omp_dim (रूख lb, रूख len, location_t lo, तार्किक nc)
  : तल्लो_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

स्थिर रूख
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    गणना omp_clause_code kind, रूख list,
			    तार्किक map_lvalue = असत्य)
{
  auto_vec<omp_dim> dims;
  तार्किक array_section_p;
  auto_vec<c_token> tokens;
  अचिन्हित पूर्णाङ्क tokens_avail = 0;
  c_token *saved_tokens = रिक्त;

  जबसम्म (1)
    {
      रूख t = NULL_रूख;
      location_t tloc = c_parser_peek_token (parser)->location;

      यदि (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  यदि (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      संरचना c_अभिव्यक्ति अभिव्यक्ति;
	      यदि (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  अभिव्यक्ति.मान = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      अन्यथा
		अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	      यदि (अभिव्यक्ति.मान != error_mark_गाँठो)
		{
		  रूख u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = अभिव्यक्ति.मान;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      यदि (c_parser_next_token_is_not (parser, CPP_COMMA))
		रोक;

	      c_parser_consume_token (parser);
	      जारी;
	    }

	  tokens.truncate (0);
	  अचिन्हित पूर्णाङ्क nesting_depth = 0;
	  जबसम्म (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      विकल्प (token->type)
		{
		पक्ष CPP_EOF:
		पक्ष CPP_PRAGMA_EOL:
		  रोक;
		पक्ष CPP_OPEN_BRACE:
		पक्ष CPP_OPEN_PAREN:
		पक्ष CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  गच्छ add;
		पक्ष CPP_CLOSE_BRACE:
		पक्ष CPP_CLOSE_PAREN:
		पक्ष CPP_CLOSE_SQUARE:
		  यदि (nesting_depth-- == 0)
		    रोक;
		  गच्छ add;
		पक्ष CPP_COMMA:
		  यदि (nesting_depth == 0)
		    रोक;
		  गच्छ add;
		स्वभाव:
		add:
		  tokens.safe_थप (*token);
		  c_parser_consume_token (parser);
		  जारी;
		}
	      रोक;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  स_रखो (&eof_token, 0, परिमाण (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_थप (eof_token);
	  tokens.safe_थप (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      अन्यथा यदि (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  तार्किक save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = सत्य;
	  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  यदि (अभिव्यक्ति.मान != error_mark_गाँठो)
	    mark_exp_read (अभिव्यक्ति.मान);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  रूख decl = अभिव्यक्ति.मान;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  यदि (रूख_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      जबसम्म (रूख_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  रूख तल्लो_bound = रूख_OPERAND (decl, 1);
		  रूख length = रूख_OPERAND (decl, 2);
		  dims.safe_थप (omp_dim (तल्लो_bound, length, loc, असत्य));
		  decl = रूख_OPERAND (decl, 0);
		}

	      जबसम्म (रूख_CODE (decl) == ARRAY_REF
		     || रूख_CODE (decl) == INDIRECT_REF
		     || रूख_CODE (decl) == COMPOUND_अभिव्यक्ति)
		{
		  यदि (रूख_CODE (decl) == COMPOUND_अभिव्यक्ति)
		    {
		      decl = रूख_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  अन्यथा यदि (रूख_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_थप (omp_dim (integer_zero_गाँठो,
					       integer_one_गाँठो, loc, सत्य));
		      decl = रूख_OPERAND (decl, 0);
		    }
		  अन्यथा  /* ARRAY_REF. */
		    {
		      रूख index = रूख_OPERAND (decl, 1);
		      dims.safe_थप (omp_dim (index, integer_one_गाँठो, loc,
					       सत्य));
		      decl = रूख_OPERAND (decl, 0);
		    }
		}

	      लागि (पूर्णाङ्क i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].तल्लो_bound,
						dims[i].length);
	    }
	  अन्यथा यदि (रूख_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = रूख_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_गाँठो,
					      integer_one_गाँठो);
	    }
	  अन्यथा यदि (रूख_CODE (decl) == ARRAY_REF)
	    {
	      रूख idx = रूख_OPERAND (decl, 1);

	      decl = रूख_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_गाँठो);
	    }
	  अन्यथा यदि (रूख_CODE (decl) == NON_LVALUE_अभिव्यक्ति
		   || CONVERT_अभिव्यक्ति_P (decl))
	    decl = रूख_OPERAND (decl, 0);

	  रूख u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  गच्छ next_item;
	}

      यदि (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->मान);

	  यदि (t == NULL_रूख)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->मान);
	      t = error_mark_गाँठो;
	    }

	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).मान;
      अन्यथा
	{
	  c_parser_error (parser, "expected identifier");
	  रोक;
	}

      यदि (t == error_mark_गाँठो)
	;
      अन्यथा यदि (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  विकल्प (kind)
	    {
	    पक्ष OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      यदि (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_गाँठो;
		  रोक;
		}
	      /* FALLTHROUGH  */
	    पक्ष OMP_CLAUSE_MAP:
	    पक्ष OMP_CLAUSE_FROM:
	    पक्ष OMP_CLAUSE_TO:
	    start_component_ref:
	      जबसम्म (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  यदि (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_अभिव्यक्ति t_अभिव्यक्ति;
		      t_अभिव्यक्ति.मान = t;
		      t_अभिव्यक्ति.original_code = ERROR_MARK;
		      t_अभिव्यक्ति.original_type = रिक्त;
		      set_c_अभिव्यक्ति_source_range (&t_अभिव्यक्ति, op_loc, op_loc);
		      t_अभिव्यक्ति.m_decimal = 0;
		      t_अभिव्यक्ति = convert_lvalue_to_rvalue (op_loc, t_अभिव्यक्ति,
							 सत्य, असत्य);
		      t = build_indirect_ref (op_loc, t_अभिव्यक्ति.मान, RO_ARROW);
		      arrow_loc = t_अभिव्यक्ति.get_location ();
		    }
		  c_parser_consume_token (parser);
		  यदि (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_गाँठो;
		      रोक;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  रूख ident = comp_tok->मान;
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
	      array_section_p = असत्य;
	      dims.truncate (0);
	      जबसम्म (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  रूख तल्लो_bound = NULL_रूख, length = NULL_रूख;
		  तार्किक no_colon = असत्य;

		  c_parser_consume_token (parser);
		  यदि (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t अभिव्यक्ति_loc
			= c_parser_peek_token (parser)->location;
		      c_अभिव्यक्ति अभिव्यक्ति = c_parser_expression (parser);
		      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति,
						       असत्य, सत्य);
		      तल्लो_bound = अभिव्यक्ति.मान;
		      loc = अभिव्यक्ति_loc;
		    }
		  यदि (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_गाँठो;
		      no_colon = सत्य;
		    }
		  अन्यथा
		    {
		      /* Look for `:'.  */
		      यदि (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_गाँठो;
			  रोक;
			}
		      array_section_p = सत्य;
		      यदि (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t अभिव्यक्ति_loc
			    = c_parser_peek_token (parser)->location;
			  c_अभिव्यक्ति अभिव्यक्ति = c_parser_expression (parser);
			  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति,
							   असत्य, सत्य);
			  length = अभिव्यक्ति.मान;
			}
		    }
		  /* Look for the closing `]'.  */
		  यदि (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_गाँठो;
		      रोक;
		    }

		  dims.safe_थप (omp_dim (तल्लो_bound, length, loc, no_colon));
		}

	      यदि (t != error_mark_गाँठो)
		{
		  यदि ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      लागि (अचिन्हित i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_गाँठो);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].तल्लो_bound);
			}
		      गच्छ start_component_ref;
		    }
		  अन्यथा
		    लागि (अचिन्हित i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].तल्लो_bound,
						   dims[i].length);
		}

	      यदि ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_गाँठो
		  && parser->tokens_avail != 2)
		{
		  यदि (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_गाँठो;
		    }
		  अन्यथा
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
		      यदि (t != error_mark_गाँठो && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_गाँठो;
			}
		    }
		}
	      रोक;
	    स्वभाव:
	      रोक;
	    }

	  यदि (t != error_mark_गाँठो)
	    {
	      रूख u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      अन्यथा  /* kind == OMP_CLAUSE_ERROR */
	list = रूख_cons (t, build_empty_stmt (tloc), list);

      यदि (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      यदि (c_parser_next_token_is_not (parser, CPP_COMMA))
	रोक;

      c_parser_consume_token (parser);
    }

  फर्काऊ list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

स्थिर रूख
c_parser_omp_var_list_parens (c_parser *parser, गणना omp_clause_code kind,
			      रूख list, तार्किक map_lvalue = असत्य)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  यदि (parser->in_omp_decl_attribute)
    {
      यदि (kind)
	{
	  रूख u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  फर्काऊ u;
	}
      अन्यथा
	फर्काऊ रूख_cons (parser->in_omp_decl_attribute, NULL_रूख, list);
    }

  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  फर्काऊ list;
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

स्थिर रूख
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   रूख list)
{
  गणना gomp_map_kind kind;
  विकल्प (c_kind)
    {
    पक्ष PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      रोक;
    पक्ष PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    पक्ष PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      रोक;
    स्वभाव:
      gcc_unreachable ();
    }

  रूख nl = list;
  तार्किक readonly = असत्य;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      यदि (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  यदि (token->type == CPP_NAME
	      && !म_भेद (IDENTIFIER_POINTER (token->मान), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = सत्य;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       असत्य);
      parens.skip_until_found_close (parser);
    }

  लागि (रूख c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      यदि (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  फर्काऊ nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

स्थिर रूख
c_parser_oacc_data_clause_deviceptr (c_parser *parser, रूख list)
{
  रूख vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, रिक्त);
  लागि (t = vars; t && t; t = रूख_CHAIN (t))
    {
      रूख v = रूख_PURPOSE (t);
      location_t loc = अभिव्यक्ति_LOCATION (रूख_मान (t));

      यदि (!VAR_P (v) && रूख_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      अन्यथा यदि (रूख_TYPE (v) == error_mark_गाँठो)
	;
      अन्यथा यदि (!POINTER_TYPE_P (रूख_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      रूख u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  फर्काऊ list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

स्थिर रूख
c_parser_omp_clause_collapse (c_parser *parser, रूख list)
{
  रूख c, अङ्क = error_mark_गाँठो;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      अङ्क = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
      parens.skip_until_found_close (parser);
    }
  यदि (अङ्क == error_mark_गाँठो)
    फर्काऊ list;
  mark_exp_read (अङ्क);
  अङ्क = c_fully_fold (अङ्क, असत्य, रिक्त);
  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (अङ्क))
      || !रूख_fits_shwi_p (अङ्क)
      || (n = रूख_to_shwi (अङ्क)) <= 0
      || (पूर्णाङ्क) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      फर्काऊ list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_अभिव्यक्ति (c) = अङ्क;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_copyin (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_copyprivate (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

स्थिर रूख
c_parser_omp_clause_default (c_parser *parser, रूख list, तार्किक is_oacc)
{
  गणना omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  रूख c;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      विकल्प (p[0])
	{
	पक्ष 'n':
	  यदि (म_भेद ("none", p) != 0)
	    गच्छ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  रोक;

	पक्ष 'p':
	  यदि (is_oacc)
	    {
	      यदि (म_भेद ("present", p) != 0)
		गच्छ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  अन्यथा
	    {
	      यदि (म_भेद ("private", p) != 0)
		गच्छ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  रोक;

	पक्ष 'f':
	  यदि (म_भेद ("firstprivate", p) != 0 || is_oacc)
	    गच्छ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  रोक;

	पक्ष 's':
	  यदि (म_भेद ("shared", p) != 0 || is_oacc)
	    गच्छ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  रोक;

	स्वभाव:
	  गच्छ invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  अन्यथा
    {
    invalid_kind:
      यदि (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      अन्यथा
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  यदि (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    फर्काऊ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  फर्काऊ c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_firstprivate (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

स्थिर रूख
c_parser_omp_clause_final (c_parser *parser, रूख list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      रूख t, c;
      यदि (!parens.require_open (parser))
	t = error_mark_गाँठो;
      अन्यथा
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  t = convert_lvalue_to_rvalue (eloc, अभिव्यक्ति, सत्य, सत्य).मान;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, असत्य, रिक्त);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_अभिव्यक्ति (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  अन्यथा
    c_parser_error (parser, "expected %<(%>");

  फर्काऊ list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

स्थिर रूख
c_parser_omp_clause_indirect (c_parser *parser, रूख list)
{
  location_t location = c_parser_peek_token (parser)->location;
  रूख t;

  यदि (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      यदि (!parens.require_open (parser))
	फर्काऊ list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, सत्य, सत्य);
      t = c_objc_common_truthvalue_conversion (loc, अभिव्यक्ति.मान);
      t = c_fully_fold (t, असत्य, रिक्त);
      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t))
	  || रूख_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  फर्काऊ list;
	}
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    t = integer_one_गाँठो;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  रूख c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  फर्काऊ c;
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

स्थिर रूख
c_parser_omp_clause_if (c_parser *parser, रूख list, तार्किक is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  गणना रूख_code if_modifier = ERROR_MARK;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      पूर्णाङ्क n = 2;
      यदि (म_भेद (p, "cancel") == 0)
	if_modifier = VOID_CST;
      अन्यथा यदि (म_भेद (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      अन्यथा यदि (म_भेद (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      अन्यथा यदि (म_भेद (p, "task") == 0)
	if_modifier = OMP_TASK;
      अन्यथा यदि (म_भेद (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      अन्यथा यदि (म_भेद (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  यदि (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->मान);
	      यदि (म_भेद ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      अन्यथा यदि (म_भेद ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      अन्यथा यदि (म_भेद ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      अन्यथा यदि (म_भेद ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      यदि (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      अन्यथा
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      यदि (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  यदि (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->मान);
		      यदि (म_भेद ("data", p) == 0)
			n = 4;
		    }
		  यदि (n == 4)
		    c_parser_consume_token (parser);
		  अन्यथा
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      यदि (if_modifier != ERROR_MARK)
	{
	  यदि (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      यदि (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  अभिव्यक्ति = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, सत्य, सत्य);
  रूख t = c_objc_common_truthvalue_conversion (loc, अभिव्यक्ति.मान), c;
  t = c_fully_fold (t, असत्य, रिक्त);
  parens.skip_until_found_close (parser);

  लागि (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	यदि (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    अचर वर्ण *p = रिक्त;
	    विकल्प (if_modifier)
	      {
	      पक्ष VOID_CST: p = "cancel"; रोक;
	      पक्ष OMP_PARALLEL: p = "parallel"; रोक;
	      पक्ष OMP_SIMD: p = "simd"; रोक;
	      पक्ष OMP_TASK: p = "task"; रोक;
	      पक्ष OMP_TASKLOOP: p = "taskloop"; रोक;
	      पक्ष OMP_TARGET_DATA: p = "target data"; रोक;
	      पक्ष OMP_TARGET: p = "target"; रोक;
	      पक्ष OMP_TARGET_UPDATE: p = "target update"; रोक;
	      पक्ष OMP_TARGET_ENTER_DATA: p = "target enter data"; रोक;
	      पक्ष OMP_TARGET_EXIT_DATA: p = "target exit data"; रोक;
	      स्वभाव: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    फर्काऊ list;
	  }
	अन्यथा यदि (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    यदि (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    अन्यथा
	      error_at (location, "too many %<if%> clauses without modifier");
	    फर्काऊ list;
	  }
	अन्यथा यदि (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    फर्काऊ list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

स्थिर रूख
c_parser_omp_clause_lastprivate (c_parser *parser, रूख list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      तार्किक conditional = असत्य;
      यदि (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  अचर वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	  यदि (म_भेद (p, "conditional") == 0)
	    {
	      conditional = सत्य;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      रूख nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      यदि (conditional)
	लागि (रूख c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      फर्काऊ nlist;
    }
  फर्काऊ list;
}

/* OpenMP 3.1:
   mergeable */

स्थिर रूख
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, रूख list)
{
  रूख c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  फर्काऊ c;
}

/* OpenMP 2.5:
   nowait */

स्थिर रूख
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, रूख list)
{
  रूख c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

स्थिर रूख
c_parser_omp_clause_अङ्क_threads (c_parser *parser, रूख list)
{
  location_t अङ्क_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख c, t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);

      parens.skip_until_found_close (parser);

      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  फर्काऊ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (अभिव्यक्ति_loc, LE_अभिव्यक्ति, boolean_type_गाँठो, t,
		       build_int_cst (रूख_TYPE (t), 0));
      protected_set_अभिव्यक्ति_location (c, अभिव्यक्ति_loc);
      यदि (c == boolean_true_गाँठो)
	{
	  warning_at (अभिव्यक्ति_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_गाँठो;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अङ्क_THREADS, "num_threads");

      c = build_omp_clause (अङ्क_threads_loc, OMP_CLAUSE_अङ्क_THREADS);
      OMP_CLAUSE_अङ्क_THREADS_अभिव्यक्ति (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

स्थिर रूख
c_parser_omp_clause_अङ्क_tasks (c_parser *parser, रूख list)
{
  location_t अङ्क_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      तार्किक strict = असत्य;
      यदि (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान),
		     "strict") == 0)
	{
	  strict = सत्य;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख c, t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);

      parens.skip_until_found_close (parser);

      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  फर्काऊ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (अभिव्यक्ति_loc, LE_अभिव्यक्ति, boolean_type_गाँठो, t,
			   build_int_cst (रूख_TYPE (t), 0));
      यदि (CAN_HAVE_LOCATION_P (c))
	SET_अभिव्यक्ति_LOCATION (c, अभिव्यक्ति_loc);
      यदि (c == boolean_true_गाँठो)
	{
	  warning_at (अभिव्यक्ति_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_गाँठो;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अङ्क_TASKS, "num_tasks");

      c = build_omp_clause (अङ्क_tasks_loc, OMP_CLAUSE_अङ्क_TASKS);
      OMP_CLAUSE_अङ्क_TASKS_अभिव्यक्ति (c) = t;
      OMP_CLAUSE_अङ्क_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

स्थिर रूख
c_parser_omp_clause_grainsize (c_parser *parser, रूख list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      तार्किक strict = असत्य;
      यदि (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान),
		     "strict") == 0)
	{
	  strict = सत्य;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख c, t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);

      parens.skip_until_found_close (parser);

      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  फर्काऊ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (अभिव्यक्ति_loc, LE_अभिव्यक्ति, boolean_type_गाँठो, t,
			   build_int_cst (रूख_TYPE (t), 0));
      यदि (CAN_HAVE_LOCATION_P (c))
	SET_अभिव्यक्ति_LOCATION (c, अभिव्यक्ति_loc);
      यदि (c == boolean_true_गाँठो)
	{
	  warning_at (अभिव्यक्ति_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_गाँठो;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_अभिव्यक्ति (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenMP 4.5:
   priority ( expression ) */

स्थिर रूख
c_parser_omp_clause_priority (c_parser *parser, रूख list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख c, t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);

      parens.skip_until_found_close (parser);

      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  फर्काऊ list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (अभिव्यक्ति_loc, LT_अभिव्यक्ति, boolean_type_गाँठो, t,
			   build_int_cst (रूख_TYPE (t), 0));
      यदि (CAN_HAVE_LOCATION_P (c))
	SET_अभिव्यक्ति_LOCATION (c, अभिव्यक्ति_loc);
      यदि (c == boolean_true_गाँठो)
	{
	  warning_at (अभिव्यक्ति_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_गाँठो;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_अभिव्यक्ति (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenMP 4.5:
   hint ( expression ) */

स्थिर रूख
c_parser_omp_clause_hint (c_parser *parser, रूख list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख c, t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);
      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t))
	  || रूख_CODE (t) != INTEGER_CST
	  || रूख_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  फर्काऊ list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_अभिव्यक्ति (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

स्थिर रूख
c_parser_omp_clause_filter (c_parser *parser, रूख list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख c, t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);
      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  फर्काऊ list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_अभिव्यक्ति (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

स्थिर रूख
c_parser_omp_clause_defaultmap (c_parser *parser, रूख list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  रूख c;
  अचर वर्ण *p;
  गणना omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  गणना omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;
  यदि (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  अन्यथा यदि (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      गच्छ out_err;
    }
  अन्यथा
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

  विकल्प (p[0])
    {
    पक्ष 'a':
      यदि (म_भेद ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      अन्यथा
	गच्छ invalid_behavior;
      रोक;

    पक्ष 'd':
      यदि (म_भेद ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      अन्यथा
	गच्छ invalid_behavior;
      रोक;

    पक्ष 'f':
      यदि (म_भेद ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      अन्यथा यदि (म_भेद ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      अन्यथा
	गच्छ invalid_behavior;
      रोक;

    पक्ष 'n':
      यदि (म_भेद ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      अन्यथा
	गच्छ invalid_behavior;
      रोक;

    पक्ष 'p':
      यदि (म_भेद ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      अन्यथा
	गच्छ invalid_behavior;
      रोक;

    पक्ष 't':
      यदि (म_भेद ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      अन्यथा यदि (म_भेद ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      अन्यथा
	गच्छ invalid_behavior;
      रोक;

    स्वभाव:
      गच्छ invalid_behavior;
    }
  c_parser_consume_token (parser);

  यदि (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	गच्छ out_err;
      यदि (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  गच्छ out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      विकल्प (p[0])
	{
	पक्ष 'a':
	  यदि (म_भेद ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  अन्यथा यदि (म_भेद ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  अन्यथा
	    गच्छ invalid_category;
	  रोक;

	पक्ष 'p':
	  यदि (म_भेद ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  अन्यथा
	    गच्छ invalid_category;
	  रोक;

	पक्ष 's':
	  यदि (म_भेद ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  अन्यथा
	    गच्छ invalid_category;
	  रोक;

	स्वभाव:
	  गच्छ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  लागि (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
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
	यदि (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = रिक्त;
	विकल्प (cat)
	  {
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = रिक्त;
	    रोक;
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    रोक;
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    रोक;
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    रोक;
	  पक्ष OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    रोक;
	  स्वभाव:
	    gcc_unreachable ();
	  }
	यदि (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	अन्यथा
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	रोक;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;

 out_err:
  parens.skip_until_found_close (parser);
  फर्काऊ list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_use_device_ptr (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_use_device_addr (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_has_device_addr (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_is_device_ptr (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

स्थिर रूख
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 रूख list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
  c_अभिव्यक्ति अभिव्यक्ति = c_parser_expression (parser);
  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
  रूख c, t = अभिव्यक्ति.मान;
  t = c_fully_fold (t, असत्य, रिक्त);

  parens.skip_until_found_close (parser);

  यदि (t == error_mark_गाँठो)
    फर्काऊ list;
  अन्यथा यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
    {
      error_at (अभिव्यक्ति_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      फर्काऊ list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (अभिव्यक्ति_loc, LE_अभिव्यक्ति, boolean_type_गाँठो, t,
		       build_int_cst (रूख_TYPE (t), 0));
  protected_set_अभिव्यक्ति_location (c, अभिव्यक्ति_loc);
  यदि (c == boolean_true_गाँठो)
    {
      warning_at (अभिव्यक्ति_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_गाँठो;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
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

स्थिर रूख
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    अचर वर्ण *str, रूख list)
{
  अचर वर्ण *id = "num";
  रूख ops[2] = { NULL_रूख, NULL_रूख }, c;

  यदि (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      गर
	{
	  c_token *next = c_parser_peek_token (parser);
	  पूर्णाङ्क idx = 0;

	  /* Gang static argument.  */
	  यदि (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		गच्छ cleanup_error;

	      idx = 1;
	      यदि (ops[idx] != NULL_रूख)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  गच्छ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      यदि (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_गाँठो;

		  यदि (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      जारी;
		    }
		  अन्यथा
		    रोक;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  अन्यथा यदि (c_parser_next_token_is (parser, CPP_NAME)
		   && म_भेद (id, IDENTIFIER_POINTER (next->मान)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  यदि (ops[idx] != NULL_रूख)
	    {
	      c_parser_error (parser, "unexpected argument");
	      गच्छ cleanup_error;
	    }

	  location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
	  c_अभिव्यक्ति cexpr = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  cexpr = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, cexpr, असत्य, सत्य);
	  रूख अभिव्यक्ति = cexpr.मान;
	  यदि (अभिव्यक्ति == error_mark_गाँठो)
	    गच्छ cleanup_error;

	  अभिव्यक्ति = c_fully_fold (अभिव्यक्ति, असत्य, रिक्त);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (अभिव्यक्ति)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      फर्काऊ list;
	    }

	  रूख c = fold_build2_loc (अभिव्यक्ति_loc, LE_अभिव्यक्ति, boolean_type_गाँठो, अभिव्यक्ति,
				    build_int_cst (रूख_TYPE (अभिव्यक्ति), 0));
	  यदि (c == boolean_true_गाँठो)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      अभिव्यक्ति = integer_one_गाँठो;
	    }

	  ops[idx] = अभिव्यक्ति;

	  यदि (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  रोक;
	}
      जबसम्म (1);

      यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	गच्छ cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  यदि (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  फर्काऊ c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  फर्काऊ list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

स्थिर रूख
c_parser_oacc_simple_clause (location_t loc, गणना omp_clause_code code,
			     रूख list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  रूख c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  फर्काऊ c;
}

/* OpenACC:
   async [( int-expr )] */

स्थिर रूख
c_parser_oacc_clause_async (c_parser *parser, रूख list)
{
  रूख c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_गाँठो, GOMP_ASYNC_NOVAL);

  यदि (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      अन्यथा यदि (t == error_mark_गाँठो
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	फर्काऊ list;
    }
  अन्यथा
    t = c_fully_fold (t, असत्य, रिक्त);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  फर्काऊ list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

स्थिर रूख
c_parser_oacc_clause_tile (c_parser *parser, रूख list)
{
  रूख c, अभिव्यक्ति = error_mark_गाँठो;
  location_t loc;
  रूख tile = NULL_रूख;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    फर्काऊ list;

  गर
    {
      यदि (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	फर्काऊ list;

      यदि (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  अभिव्यक्ति = integer_zero_गाँठो;
	}
      अन्यथा
	{
	  location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
	  c_अभिव्यक्ति cexpr = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  cexpr = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, cexpr, असत्य, सत्य);
	  अभिव्यक्ति = cexpr.मान;

	  यदि (अभिव्यक्ति == error_mark_गाँठो)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      फर्काऊ list;
	    }

	  अभिव्यक्ति = c_fully_fold (अभिव्यक्ति, असत्य, रिक्त);

	  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (अभिव्यक्ति))
	      || !रूख_fits_shwi_p (अभिव्यक्ति)
	      || रूख_to_shwi (अभिव्यक्ति) <= 0)
	    {
	      error_at (अभिव्यक्ति_loc, "%<tile%> argument needs positive"
			" integral constant");
	      अभिव्यक्ति = integer_zero_गाँठो;
	    }
	}

      tile = रूख_cons (NULL_रूख, अभिव्यक्ति, tile);
    }
  जबसम्म (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenACC:
   wait [( int-expr-list )] */

स्थिर रूख
c_parser_oacc_clause_wait (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  यदि (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  अन्यथा
    {
      रूख c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_गाँठो, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenACC 2.7:
   self [( expression )] */

स्थिर रूख
c_parser_oacc_compute_clause_self (c_parser *parser, रूख list)
{
  रूख t;
  location_t location = c_parser_peek_token (parser)->location;
  यदि (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, सत्य, सत्य);
      t = c_objc_common_truthvalue_conversion (loc, अभिव्यक्ति.मान);
      t = c_fully_fold (t, असत्य, रिक्त);
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    t = truthvalue_true_गाँठो;

  लागि (रूख c = list; c; c = OMP_CLAUSE_CHAIN (c))
    यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	फर्काऊ list;
      }

  रूख c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

स्थिर रूख
c_parser_omp_clause_order (c_parser *parser, रूख list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  रूख c;
  अचर वर्ण *p;
  तार्किक unconstrained = असत्य;
  तार्किक reproducible = असत्य;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;
  यदि (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "unconstrained") == 0)
	unconstrained = सत्य;
      अन्यथा यदि (म_भेद (p, "reproducible") == 0)
	reproducible = सत्य;
      अन्यथा
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  गच्छ out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  यदि (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      गच्छ out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
  यदि (म_भेद (p, "concurrent") != 0)
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
  फर्काऊ c;

 out_err:
  parens.skip_until_found_close (parser);
  फर्काऊ list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

स्थिर रूख
c_parser_omp_clause_bind (c_parser *parser, रूख list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  रूख c;
  अचर वर्ण *p;
  गणना omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;
  यदि (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      फर्काऊ list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
  यदि (म_भेद (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  अन्यथा यदि (म_भेद (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  अन्यथा यदि (म_भेद (p, "thread") != 0)
    गच्छ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

स्थिर रूख
c_parser_omp_clause_ordered (c_parser *parser, रूख list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  रूख c, अङ्क = NULL_रूख;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      अङ्क = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
      parens.skip_until_found_close (parser);
    }
  यदि (अङ्क == error_mark_गाँठो)
    फर्काऊ list;
  यदि (अङ्क)
    {
      mark_exp_read (अङ्क);
      अङ्क = c_fully_fold (अङ्क, असत्य, रिक्त);
      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (अङ्क))
	  || !रूख_fits_shwi_p (अङ्क)
	  || (n = रूख_to_shwi (अङ्क)) <= 0
	  || (पूर्णाङ्क) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  फर्काऊ list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_अभिव्यक्ति (c) = अङ्क;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_private (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

स्थिर रूख
c_parser_omp_clause_reduction (c_parser *parser, गणना omp_clause_code kind,
			       तार्किक is_omp, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      तार्किक task = असत्य;
      तार्किक inscan = असत्य;
      गणना रूख_code code = ERROR_MARK;
      रूख reduc_id = NULL_रूख;

      यदि (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  यदि (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा यदि (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      अचर वर्ण *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	      यदि (म_भेद (p, "task") == 0)
		task = सत्य;
	      अन्यथा यदि (म_भेद (p, "inscan") == 0)
		inscan = सत्य;
	      यदि (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_PLUS:
	  code = PLUS_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_MULT:
	  code = MULT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_MINUS:
	  यदि (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_AND:
	  code = BIT_AND_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_XOR:
	  code = BIT_XOR_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_OR:
	  code = BIT_IOR_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_AND_AND:
	  code = TRUTH_ANDIF_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_OR_OR:
	  code = TRUTH_ORIF_अभिव्यक्ति;
	  रोक;
        पक्ष CPP_NAME:
	  {
	    अचर वर्ण *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	    यदि (म_भेद (p, "min") == 0)
	      {
		code = MIN_अभिव्यक्ति;
		रोक;
	      }
	    यदि (म_भेद (p, "max") == 0)
	      {
		code = MAX_अभिव्यक्ति;
		रोक;
	      }
	    reduc_id = c_parser_peek_token (parser)->मान;
	    रोक;
	  }
	स्वभाव:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  फर्काऊ list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      यदि (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  रूख nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  लागि (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      रूख d = OMP_CLAUSE_DECL (c), type;
	      यदि (रूख_CODE (d) != OMP_ARRAY_SECTION)
		type = रूख_TYPE (d);
	      अन्यथा
		{
		  पूर्णाङ्क cnt = 0;
		  रूख t;
		  लागि (t = d;
		      रूख_CODE (t) == OMP_ARRAY_SECTION;
		      t = रूख_OPERAND (t, 0))
		    cnt++;
		  type = रूख_TYPE (t);
		  जबसम्म (cnt > 0)
		    {
		      यदि (रूख_CODE (type) != POINTER_TYPE
			  && रूख_CODE (type) != ARRAY_TYPE)
			रोक;
		      type = रूख_TYPE (type);
		      cnt--;
		    }
		}
	      जबसम्म (रूख_CODE (type) == ARRAY_TYPE)
		type = रूख_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      यदि (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      अन्यथा यदि (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      यदि (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || रूख_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  फर्काऊ list;
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

स्थिर रूख
c_parser_omp_clause_schedule (c_parser *parser, रूख list)
{
  रूख c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  पूर्णाङ्क modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  जबसम्म (c_parser_next_token_is (parser, CPP_NAME))
    {
      रूख kind = c_parser_peek_token (parser)->मान;
      अचर वर्ण *p = IDENTIFIER_POINTER (kind);
      यदि (म_भेद ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      अन्यथा यदि (म_भेद ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      अन्यथा यदि (म_भेद ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      अन्यथा
	रोक;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      यदि (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      अन्यथा
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  रोक;
	}
    }
  यदि (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  यदि ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      रूख kind = c_parser_peek_token (parser)->मान;
      अचर वर्ण *p = IDENTIFIER_POINTER (kind);

      विकल्प (p[0])
	{
	पक्ष 'd':
	  यदि (म_भेद ("dynamic", p) != 0)
	    गच्छ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  रोक;

        पक्ष 'g':
	  यदि (म_भेद ("guided", p) != 0)
	    गच्छ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  रोक;

	पक्ष 'r':
	  यदि (म_भेद ("runtime", p) != 0)
	    गच्छ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  रोक;

	स्वभाव:
	  गच्छ invalid_kind;
	}
    }
  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  अन्यथा यदि (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  अन्यथा
    गच्छ invalid_kind;

  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (here, अभिव्यक्ति, असत्य, सत्य);
      t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);

      यदि (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      अन्यथा यदि (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      अन्यथा यदि (रूख_CODE (रूख_TYPE (t)) == INTEGER_TYPE
	       || रूख_CODE (रूख_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  रूख s = fold_build2_loc (loc, LE_अभिव्यक्ति, boolean_type_गाँठो, t,
				    build_int_cst (रूख_TYPE (t), 0));
	  protected_set_अभिव्यक्ति_location (s, loc);
	  यदि (s == boolean_true_गाँठो)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_गाँठो;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_अभिव्यक्ति (c) = t;
	}
      अन्यथा
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  अन्यथा
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (गणना omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  फर्काऊ list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_shared (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

स्थिर रूख
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, रूख list)
{
  रूख c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  फर्काऊ c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

स्थिर रूख
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    गणना omp_clause_code code, रूख list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  रूख c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  फर्काऊ c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

स्थिर रूख
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				गणना omp_clause_code code, रूख list)
{
  रूख c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  फर्काऊ c;
}

/* OpenMP 4.5:
   nogroup */

स्थिर रूख
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, रूख list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  रूख c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 4.5:
   simd
   threads */

स्थिर रूख
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 गणना omp_clause_code code, रूख list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  रूख c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

स्थिर रूख
c_parser_omp_clause_अङ्क_teams (c_parser *parser, रूख list)
{
  location_t अङ्क_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (upper_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख c, upper = अभिव्यक्ति.मान, lower = NULL_रूख;
      upper = c_fully_fold (upper, असत्य, रिक्त);

      यदि (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  अभिव्यक्ति = convert_lvalue_to_rvalue (upper_loc, अभिव्यक्ति, असत्य, सत्य);
	  upper = अभिव्यक्ति.मान;
	  upper = c_fully_fold (upper, असत्य, रिक्त);
	}

      parens.skip_until_found_close (parser);

      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (रूख_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  फर्काऊ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_अभिव्यक्ति, boolean_type_गाँठो, upper,
			   build_int_cst (रूख_TYPE (upper), 0));
      protected_set_अभिव्यक्ति_location (c, upper_loc);
      यदि (c == boolean_true_गाँठो)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_गाँठो;
	}
      यदि (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_अभिव्यक्ति, boolean_type_गाँठो, lower,
			       build_int_cst (रूख_TYPE (lower), 0));
	  protected_set_अभिव्यक्ति_location (c, lower_loc);
	  यदि (c == boolean_true_गाँठो)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_रूख;
	    }
	  अन्यथा यदि (रूख_CODE (lower) == INTEGER_CST
		   && रूख_CODE (upper) == INTEGER_CST
		   && रूख_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_रूख;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अङ्क_TEAMS, "num_teams");

      c = build_omp_clause (अङ्क_teams_loc, OMP_CLAUSE_अङ्क_TEAMS);
      OMP_CLAUSE_अङ्क_TEAMS_UPPER_अभिव्यक्ति (c) = upper;
      OMP_CLAUSE_अङ्क_TEAMS_LOWER_अभिव्यक्ति (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

स्थिर रूख
c_parser_omp_clause_thread_limit (c_parser *parser, रूख list)
{
  location_t अङ्क_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख c, t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);

      parens.skip_until_found_close (parser);

      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  फर्काऊ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (अभिव्यक्ति_loc, LE_अभिव्यक्ति, boolean_type_गाँठो, t,
			   build_int_cst (रूख_TYPE (t), 0));
      protected_set_अभिव्यक्ति_location (c, अभिव्यक्ति_loc);
      यदि (c == boolean_true_गाँठो)
	{
	  warning_at (अभिव्यक्ति_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_गाँठो;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (अङ्क_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_अभिव्यक्ति (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  फर्काऊ list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

स्थिर रूख
c_parser_omp_clause_aligned (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  रूख nl, c;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  यदि (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      रूख alignment = अभिव्यक्ति.मान;
      alignment = c_fully_fold (alignment, असत्य, रिक्त);
      यदि (रूख_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (रूख_TYPE (alignment))
	  || रूख_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_रूख;
	}

      लागि (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  फर्काऊ nl;
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

स्थिर रूख
c_parser_omp_clause_allocate (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  रूख nl, c;
  रूख allocator = NULL_रूख;
  रूख align = NULL_रूख;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      तार्किक has_modifiers = असत्य;
      रूख orig_type = NULL_रूख;
      यदि (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  अचिन्हित पूर्णाङ्क n = 3;
	  अचर वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	  यदि ((म_भेद (p, "allocator") == 0 || म_भेद (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      यदि (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = सत्य;
	      अन्यथा यदि (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  अचर वर्ण *q = IDENTIFIER_POINTER (tok->मान);
		  n += 4;
		  यदि ((म_भेद (q, "allocator") == 0
		       || म_भेद (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = सत्य;
		}
	    }
	  यदि (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
	      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
	      यदि (अभिव्यक्ति.मान == error_mark_गाँठो)
		;
	      अन्यथा यदि (म_भेद (p, "allocator") == 0)
		{
		  allocator = अभिव्यक्ति.मान;
		  allocator = c_fully_fold (allocator, असत्य, रिक्त);
		  orig_type = अभिव्यक्ति.original_type
			      ? अभिव्यक्ति.original_type : रूख_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      अन्यथा
		{
		  align = अभिव्यक्ति.मान;
		  align = c_fully_fold (align, असत्य, रिक्त);
		}
	      parens2.skip_until_found_close (parser);
	      यदि (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  अचर वर्ण *q = "";
		  यदि (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->मान);
		  यदि (म_भेद (q, "allocator") != 0 && म_भेद (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      फर्काऊ list;
		    }
		  अन्यथा यदि (म_भेद (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      फर्काऊ list;
		    }
		  c_parser_consume_token (parser);
		  यदि (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      फर्काऊ list;
		    }
		  अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
		  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
		  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य,
						   सत्य);
		  यदि (म_भेद (q, "allocator") == 0)
		    {
		      allocator = अभिव्यक्ति.मान;
		      allocator = c_fully_fold (allocator, असत्य, रिक्त);
		      orig_type = अभिव्यक्ति.original_type
				  ? अभिव्यक्ति.original_type : रूख_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  अन्यथा
		    {
		      align = अभिव्यक्ति.मान;
		      align = c_fully_fold (align, असत्य, रिक्त);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      यदि (!has_modifiers)
	{
	  location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
	  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
	  यदि (अभिव्यक्ति.मान != error_mark_गाँठो)
	    {
	      allocator = अभिव्यक्ति.मान;
	      allocator = c_fully_fold (allocator, असत्य, रिक्त);
	      orig_type = अभिव्यक्ति.original_type
			  ? अभिव्यक्ति.original_type : रूख_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      यदि (allocator
	  && (!INTEGRAL_TYPE_P (रूख_TYPE (allocator))
	      || रूख_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				रूख_TYPE (allocator));
          allocator = NULL_रूख;
        }
      यदि (align
	  && (!INTEGRAL_TYPE_P (रूख_TYPE (align))
	      || !रूख_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_रूख;
	}
      यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  फर्काऊ list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  यदि (allocator || align)
    लागि (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  फर्काऊ nl;
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

स्थिर रूख
c_parser_omp_clause_uses_allocators (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  रूख nl = list;
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

parse_next:

  तार्किक has_modifiers = असत्य;
  तार्किक seen_allocators = असत्य;
  रूख memspace_अभिव्यक्ति = NULL_रूख;
  रूख traits_var = NULL_रूख;

  यदि (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      अचिन्हित पूर्णाङ्क n = 3;
      अचर वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि ((म_भेद (p, "traits") == 0 || म_भेद (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  यदि (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = सत्य;
	  अन्यथा यदि (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      अचर वर्ण *q = IDENTIFIER_POINTER (tok->मान);
	      n += 4;
	      यदि ((म_भेद (q, "traits") == 0
		   || म_भेद (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  यदि (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = सत्य;
		  यदि ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      अचर वर्ण *m = IDENTIFIER_POINTER (tok->मान);
		      यदि (म_भेद (p, m) == 0 || म_भेद (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  गच्छ end;
			}
		    }
		}
	    }
	}
      यदि (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  यदि (अभिव्यक्ति.मान == error_mark_गाँठो)
	    ;
	  अन्यथा यदि (म_भेद (p, "traits") == 0)
	    {
	      traits_var = अभिव्यक्ति.मान;
	      traits_var = c_fully_fold (traits_var, असत्य, रिक्त);
	      mark_exp_read (traits_var);
	    }
	  अन्यथा
	    {
	      memspace_अभिव्यक्ति = अभिव्यक्ति.मान;
	      memspace_अभिव्यक्ति = c_fully_fold (memspace_अभिव्यक्ति, असत्य, रिक्त);
	    }
	  parens2.skip_until_found_close (parser);
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      अचर वर्ण *q = "";
	      यदि (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->मान);
	      यदि (म_भेद (q, "traits") != 0 && म_भेद (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  फर्काऊ list;
		}
	      अन्यथा यदि (म_भेद (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  फर्काऊ list;
		}
	      c_parser_consume_token (parser);
	      यदि (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  फर्काऊ list;
		}
	      अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	      यदि (म_भेद (q, "traits") == 0)
		{
		  traits_var = अभिव्यक्ति.मान;
		  traits_var = c_fully_fold (traits_var, असत्य, रिक्त);
		  mark_exp_read (traits_var);
		}
	      अन्यथा
		{
		  memspace_अभिव्यक्ति = अभिव्यक्ति.मान;
		  memspace_अभिव्यक्ति = c_fully_fold (memspace_अभिव्यक्ति, असत्य, रिक्त);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    गच्छ end;
	}
    }

  जबसम्म (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      अचर वर्ण *tok_s = IDENTIFIER_POINTER (tok->मान);
      रूख t = lookup_name (tok->मान);
      यदि (t == NULL_रूख)
	{
	  undeclared_variable (tok->location, tok->मान);
	  t = error_mark_गाँठो;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      रूख legacy_traits = NULL_रूख;
      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  अचर वर्ण *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  यदि (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      गच्छ end;
	    }
	  legacy_traits = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
	  यदि (legacy_traits == error_mark_गाँठो)
	    गच्छ end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  यदि (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_घुसाउ_after (close_loc, ": ");
	      richloc.add_fixit_घुसाउ_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      यदि (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  गच्छ end;
	}
      seen_allocators = सत्य;

      रूख c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_अभिव्यक्ति;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
    }

  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      गच्छ parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  फर्काऊ nl;
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

स्थिर रूख
c_parser_omp_clause_linear (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  रूख nl, c, step;
  गणना omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  तार्किक old_linear_modifier = असत्य;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      अचर वर्ण *p = IDENTIFIER_POINTER (tok->मान);
      यदि (म_भेद ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      यदि (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      यदि (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = सत्य;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  यदि (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  यदि (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = अभिव्यक्ति_loc;
      तार्किक has_modifiers = असत्य;
      यदि (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  अचर वर्ण *p = IDENTIFIER_POINTER (tok->मान);
	  अचिन्हित पूर्णाङ्क pos = 0;
	  यदि (म_भेद ("val", p) == 0)
	    pos = 2;
	  अन्यथा यदि (म_भेद ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      यदि (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      अन्यथा
		pos = 0;
	    }
	  यदि (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      यदि (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = सत्य;
	    }
	}
      यदि (has_modifiers)
	{
	  step = NULL_रूख;
	  जबसम्म (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      अचर वर्ण *p = IDENTIFIER_POINTER (tok->मान);
	      यदि (म_भेद ("val", p) == 0)
		{
		  यदि (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      अन्यथा यदि (म_भेद ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  यदि (parens2.require_open (parser))
		    {
		      यदि (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
		      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
		      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य,
						       सत्य);
		      step = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
		      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_गाँठो;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  अन्यथा
		    रोक;
		}
	      अन्यथा
		रोक;
	      यदि (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  जारी;
		}
	      रोक;
	    }
	  यदि (!step)
	    step = integer_one_गाँठो;
	}
      अन्यथा
	{
	  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
	  step = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
	  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_गाँठो;
	    }
	}

    }
  अन्यथा
    step = integer_one_गाँठो;

  लागि (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  यदि (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      यदि (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  यदि (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_घुसाउ_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_घुसाउ_before (close_loc, ")");
	    }
	  अन्यथा
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  फर्काऊ nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_nontemporal (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

स्थिर रूख
c_parser_omp_clause_safelen (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  रूख c, t;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
  t = अभिव्यक्ति.मान;
  t = c_fully_fold (t, असत्य, रिक्त);
  यदि (रूख_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (रूख_TYPE (t))
      || रूख_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_रूख;
    }

  parens.skip_until_found_close (parser);
  यदि (t == NULL_रूख || t == error_mark_गाँठो)
    फर्काऊ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

स्थिर रूख
c_parser_omp_clause_simdlen (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  रूख c, t = NULL_रूख, type = NULL_रूख, भाजक = NULL_रूख;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  अचिन्हित pos = 3;
  यदि (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      संरचना c_type_name *ctype = c_parser_type_name (parser);
      यदि (ctype == रिक्त
	  || (type = groktypename (ctype, रिक्त, रिक्त)) == रिक्त
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && रूख_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_गाँठो;
	}
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  अभिव्यक्ति = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, असत्य, सत्य);
	  भाजक = अभिव्यक्ति.मान;
	  भाजक = c_fully_fold (भाजक, असत्य, रिक्त);
	  यदि (रूख_CODE (भाजक) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (रूख_TYPE (भाजक))
	      || रूख_int_cst_sgn (भाजक) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_गाँठो;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  यदि (type != error_mark_गाँठो)
    {
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);
      यदि (रूख_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (रूख_TYPE (t))
	  || रूख_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_रूख;
	}
    }

  parens.skip_until_found_close (parser);
  यदि (type == error_mark_गाँठो || t == NULL_रूख || t == error_mark_गाँठो)
    फर्काऊ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_भाजक (c) = भाजक;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

स्थिर रूख
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   रूख list, तार्किक depend_p)
{
  रूख vec = रिक्त;
  यदि (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      फर्काऊ list;
    }

  यदि (!depend_p)
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_सङ्ख्या
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  रूख val = c_parser_peek_nth_token (parser, 3)->मान;
	  यदि (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      रूख u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      फर्काऊ u;
	    }
	}
    }



  जबसम्म (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      रूख t = lookup_name (c_parser_peek_token (parser)->मान);
      रूख addend = रिक्त;

      यदि (t == NULL_रूख)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->मान);
	  t = error_mark_गाँठो;
	}

      c_parser_consume_token (parser);

      तार्किक neg = असत्य;
      यदि (c_parser_next_token_is (parser, CPP_MINUS))
	neg = सत्य;
      अन्यथा यदि (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_गाँठो;
	  neg = असत्य;
	  गच्छ add_to_vector;
	}
      c_parser_consume_token (parser);

      यदि (c_parser_next_token_is_not (parser, CPP_सङ्ख्या))
	{
	  c_parser_error (parser, "expected integer");
	  फर्काऊ list;
	}

      addend = c_parser_peek_token (parser)->मान;
      यदि (रूख_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  फर्काऊ list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      यदि (t != error_mark_गाँठो)
	{
	  vec = रूख_cons (addend, t, vec);
	  यदि (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      यदि (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	रोक;

      c_parser_consume_token (parser);
    }

  यदि (vec == NULL_रूख)
    फर्काऊ list;

  रूख u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  फर्काऊ u;
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

स्थिर रूख
c_parser_omp_iterators (c_parser *parser)
{
  रूख ret = NULL_रूख, *last = &ret;
  c_parser_consume_token (parser);

  थप_scope ();

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ error_mark_गाँठो;

  गर
    {
      रूख iter_type = NULL_रूख, type_अभिव्यक्ति = NULL_रूख;
      यदि (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  संरचना c_type_name *type = c_parser_type_name (parser);
	  यदि (type != रिक्त)
	    iter_type = groktypename (type, &type_अभिव्यक्ति, रिक्त);
	}
      यदि (iter_type == NULL_रूख)
	iter_type = integer_type_गाँठो;

      location_t loc = c_parser_peek_token (parser)->location;
      यदि (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  रोक;
	}

      रूख id = c_parser_peek_token (parser)->मान;
      c_parser_consume_token (parser);

      यदि (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	रोक;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (eloc, अभिव्यक्ति, सत्य, असत्य);
      रूख begin = अभिव्यक्ति.मान;

      यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	रोक;

      eloc = c_parser_peek_token (parser)->location;
      अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (eloc, अभिव्यक्ति, सत्य, असत्य);
      रूख end = अभिव्यक्ति.मान;

      रूख step = integer_one_गाँठो;
      यदि (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	  अभिव्यक्ति = convert_lvalue_to_rvalue (eloc, अभिव्यक्ति, सत्य, असत्य);
	  step = अभिव्यक्ति.मान;
	}

      रूख iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &रूख_CHAIN (*last);

      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  जारी;
	}
      रोक;
    }
  जबसम्म (1);

  parens.skip_until_found_close (parser);
  फर्काऊ ret ? ret : error_mark_गाँठो;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

स्थिर रूख
c_parser_omp_clause_affinity (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  रूख nl, iterators = NULL_रूख;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      तार्किक parse_iter = ((म_भेद ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      यदि (parse_iter)
	{
	  अचिन्हित n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      यदि (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      यदि (iterators)
		झिक_scope ();
	      parens.skip_until_found_close (parser);
	      फर्काऊ list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  यदि (iterators)
    {
      रूख block = झिक_scope ();
      यदि (iterators != error_mark_गाँठो)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  लागि (रूख c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_रूख_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  फर्काऊ nl;
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

स्थिर रूख
c_parser_omp_clause_depend (c_parser *parser, रूख list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  गणना omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  गणना omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  रूख nl, c, iterators = NULL_रूख;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  गर
    {
      यदि (c_parser_next_token_is_not (parser, CPP_NAME))
	गच्छ invalid_kind;

      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद ("iterator", p) == 0 && iterators == NULL_रूख)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  जारी;
	}
      यदि (म_भेद ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      अन्यथा यदि (म_भेद ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      अन्यथा यदि (म_भेद ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      अन्यथा यदि (म_भेद ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      अन्यथा यदि (म_भेद ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      अन्यथा यदि (म_भेद ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      अन्यथा यदि (म_भेद ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      अन्यथा यदि (म_भेद ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      अन्यथा
	गच्छ invalid_kind;
      रोक;
    }
  जबसम्म (1);

  c_parser_consume_token (parser);

  यदि (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      झिक_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_रूख;
    }

  यदि (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_रूख;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      फर्काऊ c;
    }

  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    गच्छ resync_fail;

  यदि (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, सत्य);
  अन्यथा
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      यदि (iterators)
	{
	  रूख block = झिक_scope ();
	  यदि (iterators == error_mark_गाँठो)
	    iterators = NULL_रूख;
	  अन्यथा
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      लागि (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  यदि (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_रूख_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  फर्काऊ nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  यदि (iterators)
    झिक_scope ();
  फर्काऊ list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

स्थिर रूख
c_parser_omp_clause_doacross (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  गणना omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  रूख nl;
  अचर वर्ण *p;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (c_parser_next_token_is_not (parser, CPP_NAME))
    गच्छ invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
  यदि (म_भेद ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  अन्यथा यदि (म_भेद ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  अन्यथा
    गच्छ invalid_kind;

  c_parser_consume_token (parser);

  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    गच्छ resync_fail;

  यदि (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      यदि (c_parser_next_token_is (parser, CPP_NAME)
	  && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_रूख;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  अन्यथा
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, असत्य);

  parens.skip_until_found_close (parser);
  फर्काऊ nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  फर्काऊ list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

स्थिर रूख
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  गणना omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  अचिन्हित n = 3;
  यदि (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  फर्काऊ list;
	}
      c_parser_consume_token (parser);
      यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	फर्काऊ list;
      p = "";
      यदि (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      अन्यथा यदि (म_भेद (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      अन्यथा यदि (म_भेद (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      अन्यथा
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  फर्काऊ list;
	}
      c_parser_consume_token (parser);
      यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	फर्काऊ list;
      यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	फर्काऊ list;
    }
  location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
  रूख size = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
  parens.skip_until_found_close (parser);

  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (size)))
    {
      error_at (अभिव्यक्ति_loc, "expected integer expression");
      फर्काऊ list;
    }

  /* Attempt to statically determine when the number is negative.  */
  रूख c = fold_build2_loc (अभिव्यक्ति_loc, LT_अभिव्यक्ति, boolean_type_गाँठो, size,
			    build_int_cst (रूख_TYPE (size), 0));
  protected_set_अभिव्यक्ति_location (c, अभिव्यक्ति_loc);
  यदि (c == boolean_true_गाँठो)
    {
      warning_at (अभिव्यक्ति_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_गाँठो;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_अभिव्यक्ति (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  फर्काऊ list;
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

स्थिर रूख
c_parser_omp_clause_map (c_parser *parser, रूख list, तार्किक declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  रूख nl, c;
  गणना gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  पूर्णाङ्क pos = 1;
  पूर्णाङ्क map_kind_pos = 0;
  पूर्णाङ्क iterator_length = 0;
  लागि (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      यदि (tok->type != CPP_NAME)
	रोक;

      अचर वर्ण *p = IDENTIFIER_POINTER (tok->मान);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      यदि (म_भेद (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  अचिन्हित n = pos + 2;
	  यदि (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      यदि (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  रोक;
	}

      यदि (next_tok->type == CPP_COMMA)
	pos++;
      अन्यथा यदि (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  अचिन्हित पूर्णाङ्क npos = pos + 2;
	  यदि (c_parser_check_balanced_raw_token_sequence (parser, &npos)
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
  पूर्णाङ्क अङ्क_commas = 0;
  पूर्णाङ्क अङ्क_identifiers = 0;
  रूख mapper_name = NULL_रूख;
  रूख iterators = NULL_रूख;
  लागि (पूर्णाङ्क pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      यदि (tok->type == CPP_COMMA)
	{
	  ++अङ्क_commas;
	  यदि (अङ्क_commas > अङ्क_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  जारी;
	}

      अचर वर्ण *p = IDENTIFIER_POINTER (tok->मान);
      यदि (म_भेद ("always", p) == 0)
	{
	  यदि (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      फर्काऊ list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (म_भेद ("close", p) == 0)
	{
	  यदि (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      फर्काऊ list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (म_भेद ("iterator", p) == 0)
	{
	  यदि (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      फर्काऊ list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      अन्यथा यदि (म_भेद ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  यदि (mparens.require_open (parser))
	    {
	      यदि (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  फर्काऊ list;
		}

	      tok = c_parser_peek_token (parser);

	      विकल्प (tok->type)
		{
		पक्ष CPP_NAME:
		  {
		    mapper_name = tok->मान;
		    c_parser_consume_token (parser);
		    यदि (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  रोक;

		पक्ष CPP_KEYWORD:
		  यदि (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      रोक;
		    }
		  /* Fallthrough.  */

		स्वभाव:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  फर्काऊ list;
		}

	      यदि (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  फर्काऊ list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      अन्यथा यदि (म_भेद ("present", p) == 0)
	{
	  यदि (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      फर्काऊ list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      अन्यथा
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  फर्काऊ list;
	}
      ++अङ्क_identifiers;
      यदि (अङ्क_identifiers - 1 > अङ्क_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_घुसाउ_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      अङ्क_commas = अङ्क_identifiers - 1;
    }

  यदि (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      पूर्णाङ्क always_present_modifier = always_modifier && present_modifier;

      यदि (म_भेद ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      अन्यथा यदि (म_भेद ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      अन्यथा यदि (म_भेद ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      अन्यथा यदि (म_भेद ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      अन्यथा यदि (म_भेद ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      अन्यथा यदि (म_भेद ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      अन्यथा
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  फर्काऊ list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   सत्य);

  रूख last_new = NULL_रूख;

  यदि (iterators)
    {
      रूख block = झिक_scope ();
      यदि (iterators == error_mark_गाँठो)
	iterators = NULL_रूख;
      अन्यथा
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  लागि (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  यदि (mapper_name)
    {
      रूख name = build_omp_clause (आगत_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_थप_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (आगत_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_झिक_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_गाँठो;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  फर्काऊ nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

स्थिर रूख
c_parser_omp_clause_device (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t अभिव्यक्ति_loc;
  c_अभिव्यक्ति अभिव्यक्ति;
  रूख c, t;
  तार्किक ancestor = असत्य;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      अचर वर्ण *p = IDENTIFIER_POINTER (tok->मान);
      यदि (म_भेद ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  यदि ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      फर्काऊ list;
	    }
	  ancestor = सत्य;
	}
      अन्यथा यदि (म_भेद ("device_num", p) == 0)
	;
      अन्यथा
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  फर्काऊ list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
  t = अभिव्यक्ति.मान;
  t = c_fully_fold (t, असत्य, रिक्त);

  parens.skip_until_found_close (parser);

  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      फर्काऊ list;
    }
  यदि (ancestor && रूख_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (अभिव्यक्ति_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      फर्काऊ list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  फर्काऊ list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

स्थिर रूख
c_parser_omp_clause_dist_schedule (c_parser *parser, रूख list)
{
  रूख c, t = NULL_रूख;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      फर्काऊ list;
    }

  c_parser_consume_token (parser);
  यदि (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      t = अभिव्यक्ति.मान;
      t = c_fully_fold (t, असत्य, रिक्त);
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  यदि (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  यदि (t == error_mark_गाँठो)
    फर्काऊ list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

स्थिर रूख
c_parser_omp_clause_proc_bind (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  गणना omp_clause_proc_bind_kind kind;
  रूख c;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      अन्यथा यदि (म_भेद ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      अन्यथा यदि (म_भेद ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      अन्यथा यदि (म_भेद ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      अन्यथा
	गच्छ invalid_kind;
    }
  अन्यथा
    गच्छ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  फर्काऊ list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

स्थिर रूख
c_parser_omp_clause_device_type (c_parser *parser, रूख list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  गणना omp_clause_device_type_kind kind;
  रूख c;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      अन्यथा यदि (म_भेद ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      अन्यथा यदि (म_भेद ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      अन्यथा
	गच्छ invalid_kind;
    }
  अन्यथा
    गच्छ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  फर्काऊ list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

स्थिर रूख
c_parser_omp_clause_from_to (c_parser *parser, गणना omp_clause_code kind,
			     रूख list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  पूर्णाङ्क pos = 1, colon_pos = 0;
  पूर्णाङ्क iterator_length = 0;

  जबसम्म (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      अचर वर्ण *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->मान);
      यदि (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  अचिन्हित पूर्णाङ्क npos = pos + 2;
	  यदि (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      यदि (म_भेद (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      यदि (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      अन्यथा
	pos++;
      यदि (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  रोक;
	}
    }

  तार्किक present = असत्य, mapper_modifier = असत्य;
  रूख iterators = NULL_रूख;
  रूख mapper_name = NULL_रूख;

  लागि (पूर्णाङ्क pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      यदि (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  जारी;
	}
      अचर वर्ण *p = IDENTIFIER_POINTER (token->मान);
      यदि (म_भेद ("present", p) == 0)
	{
	  यदि (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      फर्काऊ list;
	    }
	  present = सत्य;
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (म_भेद ("iterator", p) == 0)
	{
	  यदि (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      फर्काऊ list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      अन्यथा यदि (म_भेद ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  यदि (mparens.require_open (parser))
	    {
	      यदि (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  फर्काऊ list;
		}

	      token = c_parser_peek_token (parser);
	      विकल्प (token->type)
		{
		पक्ष CPP_NAME:
		  {
		    mapper_name = token->मान;
		    c_parser_consume_token (parser);
		  }
		  रोक;
		पक्ष CPP_KEYWORD:
		  यदि (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      रोक;
		    }
		  /* FALLTHROUGH  */
		स्वभाव:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  फर्काऊ list;
		}
	      यदि (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  फर्काऊ list;
		}
	      mapper_modifier = सत्य;
	      pos += 3;
	    }
	}
      अन्यथा
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  फर्काऊ list;
	}
    }

  यदि (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  रूख nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  यदि (present)
    लागि (रूख c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  यदि (iterators)
    {
      रूख block = झिक_scope ();
      यदि (iterators == error_mark_गाँठो)
	iterators = NULL_रूख;
      अन्यथा
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  यदि (iterators)
    लागि (रूख c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  यदि (mapper_name)
    {
      रूख last_new = NULL_रूख;
      लागि (रूख c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      रूख name = build_omp_clause (आगत_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_थप_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (आगत_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_झिक_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_गाँठो;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  फर्काऊ nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_uniform (c_parser *parser, रूख list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  फर्काऊ list;
}

/* OpenMP 5.1
   full */

स्थिर रूख
c_parser_omp_clause_full (c_parser *parser, रूख list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  रूख c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

स्थिर रूख
c_parser_omp_clause_partial (c_parser *parser, रूख list)
{
  रूख अङ्क = NULL_रूख;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      अङ्क = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
      parens.skip_until_found_close (parser);

      यदि (अङ्क == error_mark_गाँठो)
	फर्काऊ list;

      mark_exp_read (अङ्क);
      अङ्क = c_fully_fold (अङ्क, असत्य, रिक्त);
      HOST_WIDE_INT n;
      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (अङ्क))
	  || !रूख_fits_shwi_p (अङ्क)
	  || (n = रूख_to_shwi (अङ्क)) <= 0
	  || (पूर्णाङ्क) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  फर्काऊ list;
	}
    }

  रूख c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_अभिव्यक्ति (c) = अङ्क;
  OMP_CLAUSE_CHAIN (c) = list;
  फर्काऊ c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

स्थिर रूख
c_parser_omp_clause_novariants (c_parser *parser, रूख list)
{
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  रूख t = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, सत्य, सत्य).मान;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, असत्य, रिक्त);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  रूख c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  फर्काऊ list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

स्थिर रूख
c_parser_omp_clause_nocontext (c_parser *parser, रूख list)
{
  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
  रूख t = convert_lvalue_to_rvalue (loc, अभिव्यक्ति, सत्य, सत्य).मान;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, असत्य, रिक्त);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  रूख c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_अभिव्यक्ति (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  फर्काऊ list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

स्थिर रूख
c_parser_omp_clause_detach (c_parser *parser, रूख list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  यदि (!parens.require_open (parser))
    फर्काऊ list;

  यदि (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      फर्काऊ list;
    }

  रूख t = lookup_name (c_parser_peek_token (parser)->मान);
  यदि (t == NULL_रूख)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->मान);
      parens.skip_until_found_close (parser);
      फर्काऊ list;
    }
  c_parser_consume_token (parser);

  रूख type = TYPE_MAIN_VARIANT (रूख_TYPE (t));
  यदि (!INTEGRAL_TYPE_P (type)
      || रूख_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      फर्काऊ list;
    }

  रूख u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  फर्काऊ u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_destroy (c_parser *parser, रूख list)
{
  रूख nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  लागि (रूख c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    रूख_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  फर्काऊ nl;
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

स्थिर रूख
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    फर्काऊ error_mark_गाँठो;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  यदि (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    जबसम्म (सत्य)
      {
	str += (वर्ण) GOMP_INTEROP_IFR_SEPARATOR;
	यदि (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_अभिव्यक्ति cval = c_parser_string_literal (parser, असत्य, असत्य);
	    यदि (cval.मान == error_mark_गाँठो)
	      फर्काऊ error_mark_गाँठो;
	    यदि ((माप_प्रकार) रूख_STRING_LENGTH (cval.मान)
		!= म_माप (रूख_STRING_POINTER (cval.मान)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = सत्य;
		फर्काऊ error_mark_गाँठो;
	      }

	    वर्ण c = omp_get_fr_id_from_name (रूख_STRING_POINTER (cval.मान));
	    यदि (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  रूख_STRING_POINTER (cval.मान));
	    str += c;
	  }
	अन्यथा
	  {
	    c_अभिव्यक्ति cval = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	    रूख मान = c_fully_fold (cval.मान, असत्य, रिक्त);
	    यदि (INTEGRAL_TYPE_P (रूख_TYPE (मान))
		&& रूख_CODE (मान) != INTEGER_CST)
	      मान = convert_lvalue_to_rvalue (cval.get_start (), cval,
						असत्य, सत्य).मान;
	    यदि (रूख_CODE (मान) != INTEGER_CST
		|| !रूख_fits_shwi_p (मान))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		फर्काऊ error_mark_गाँठो;
	      }
	    HOST_WIDE_INT n = रूख_to_shwi (मान);
	    यदि (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (वर्ण) n;
	  }
	str += (वर्ण) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	यदि (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    जारी;
	  }
	यदि (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  फर्काऊ error_mark_गाँठो;
	str += '\0';
	रूख res = build_string (str.length (), str.data ());
	रूख_TYPE (res) = build_array_type_nelts (unsigned_char_type_गाँठो,
						  str.length ());
	फर्काऊ res;
      }

  /* New format. */
  std::string str2;
  जबसम्म (सत्य)
    {
      यदि (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	फर्काऊ error_mark_गाँठो;
      str += (वर्ण) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      तार्किक has_fr = असत्य;
      जबसम्म (सत्य)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  यदि (tok->type != CPP_NAME
	      || (म_भेद("fr", IDENTIFIER_POINTER (tok->मान)) != 0
		  && म_भेद("attr", IDENTIFIER_POINTER (tok->मान)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      फर्काऊ error_mark_गाँठो;
	    }
	  c_parser_consume_token (parser);
	  तार्किक is_fr = IDENTIFIER_POINTER (tok->मान)[0] == 'f';
	  यदि (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      फर्काऊ error_mark_गाँठो;
	    }
	  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    फर्काऊ error_mark_गाँठो;
	  जबसम्म (सत्य)
	    {
	      यदि (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_अभिव्यक्ति cval = c_parser_string_literal (parser, असत्य, असत्य);
		  रूख मान = cval.मान;
		  यदि (मान == error_mark_गाँठो)
		    फर्काऊ error_mark_गाँठो;
		  यदि ((माप_प्रकार) रूख_STRING_LENGTH (मान)
		      != म_माप (रूख_STRING_POINTER (मान)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = सत्य;
		      फर्काऊ error_mark_गाँठो;
		    }
		  यदि (!is_fr)
		    {
		      यदि (!startswith (रूख_STRING_POINTER (मान), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = सत्य;
			  फर्काऊ error_mark_गाँठो;
			}
		      यदि (म_अक्षर (रूख_STRING_POINTER (मान), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = सत्य;
			  फर्काऊ error_mark_गाँठो;
			}
		      str2 += रूख_STRING_POINTER (मान);
		      str2 += '\0';
		    }
		  अन्यथा
		    {
		      यदि (*रूख_STRING_POINTER (मान) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  फर्काऊ error_mark_गाँठो;
			}
		      वर्ण c = omp_get_fr_id_from_name (रूख_STRING_POINTER (मान));
		      यदि (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    रूख_STRING_POINTER (मान));
		     str += c;
		     has_fr = सत्य;
		    }
		}
	      अन्यथा यदि (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  फर्काऊ error_mark_गाँठो;
		}
	      अन्यथा
		{
		  c_अभिव्यक्ति cval = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
		  रूख मान = c_fully_fold (cval.मान, असत्य, रिक्त);
		  यदि (INTEGRAL_TYPE_P (रूख_TYPE (मान))
		      && रूख_CODE (मान) != INTEGER_CST)
		    मान = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      असत्य, सत्य).मान;

		  यदि (रूख_CODE (मान) != INTEGER_CST
		      || !रूख_fits_shwi_p (मान))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      फर्काऊ error_mark_गाँठो;
		    }
		  HOST_WIDE_INT n = रूख_to_shwi (मान);
		  यदि (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (वर्ण) n;
		  has_fr = सत्य;
		}
	      यदि (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  जारी;
		}
	      यदि (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		फर्काऊ error_mark_गाँठो;
	      रोक;
	    }
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    रोक;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  फर्काऊ error_mark_गाँठो;
	}
      str += (वर्ण) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	रोक;
      यदि (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	फर्काऊ error_mark_गाँठो;
    }
  c_parser_consume_token (parser);
  str += '\0';
  रूख res = build_string (str.length (), str.data ());
  रूख_TYPE (res) = build_array_type_nelts (unsigned_char_type_गाँठो,
						  str.length ());
  फर्काऊ res;
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
				    तार्किक *targetsync, रूख *prefer_type_रूख)
{
  *target = असत्य;
  *targetsync = असत्य;
  *prefer_type_रूख = NULL_रूख;

  गर
    {
      c_token *tok = c_parser_peek_token (parser);
      यदि (tok->type != CPP_NAME)
	गच्छ fail;
      अचर वर्ण *p = IDENTIFIER_POINTER (tok->मान);
      यदि (म_भेद ("targetsync", p) == 0)
	{
	  यदि (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = सत्य;
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (म_भेद ("target", p) == 0)
	{
	  यदि (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = सत्य;
	  c_parser_consume_token (parser);
	}
      अन्यथा यदि (म_भेद ("prefer_type", p) == 0)
	{
	  यदि (*prefer_type_रूख != NULL_रूख)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_रूख = c_parser_omp_modifier_prefer_type (parser);
	  यदि (*prefer_type_रूख == error_mark_गाँठो)
	    फर्काऊ असत्य;
	}
      अन्यथा
	गच्छ fail;
      tok = c_parser_peek_token (parser);
      यदि (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  जारी;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      फर्काऊ सत्य;
    }
  जबसम्म (सत्य);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  फर्काऊ असत्य;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

स्थिर रूख
c_parser_omp_clause_init (c_parser *parser, रूख list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ list;

  तार्किक target = असत्य;
  तार्किक targetsync = असत्य;
  रूख prefer_type_रूख = NULL_रूख;

  यदि (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_रूख)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      यदि (prefer_type_रूख != error_mark_गाँठो)
	parens.skip_until_found_close (parser);
      फर्काऊ list;
    }

  यदि (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  रूख nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					असत्य);
  parens.skip_until_found_close (parser);

  लागि (रूख c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      रूख_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      यदि (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      यदि (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      यदि (prefer_type_रूख)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_रूख;
    }
  फर्काऊ nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_use (c_parser *parser, रूख list)
{
  फर्काऊ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

स्थिर रूख
c_parser_omp_clause_interop (c_parser *parser, रूख list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  रूख nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  लागि (रूख c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      रूख_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  फर्काऊ nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

स्थिर रूख
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   अचर वर्ण *where, तार्किक finish_p = सत्य,
			   तार्किक target_p = असत्य)
{
  रूख clauses = रिक्त;
  तार्किक first = सत्य;

  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      अचर वर्ण *c_name;
      रूख prev = clauses;

      यदि (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      विकल्प (c_kind)
	{
	पक्ष PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, सत्य);
	  c_name = "default";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, असत्य);
	  c_name = "if";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_अङ्क_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_अङ्क_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_अङ्क_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_अङ्क_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     असत्य, clauses);
	  c_name = "reduction";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_SELF:
	  यदि ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  अन्यथा
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  रोक;
	पक्ष PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  रोक;
	स्वभाव:
	  c_parser_error (parser, "expected an OpenACC clause");
	  गच्छ saw_error;
	}

      first = असत्य;

      यदि (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  यदि (finish_p)
    फर्काऊ c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  फर्काऊ clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

स्थिर रूख
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  अचर वर्ण *where, तार्किक finish_p = सत्य,
			  पूर्णाङ्क nested = 0)
{
  रूख clauses = रिक्त;
  तार्किक first = सत्य;

  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      अचर वर्ण *c_name;
      रूख prev = clauses;

      यदि (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	रोक;

      यदि (!first || nested != 2)
	{
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा यदि (nested == 2)
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
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, असत्य);
	  c_name = "default";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, सत्य);
	  c_name = "if";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     सत्य, clauses);
	  c_name = "in_reduction";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_अङ्क_TASKS:
	  clauses = c_parser_omp_clause_अङ्क_tasks (parser, clauses);
	  c_name = "num_tasks";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_अङ्क_THREADS:
	  clauses = c_parser_omp_clause_अङ्क_threads (parser, clauses);
	  c_name = "num_threads";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     सत्य, clauses);
	  c_name = "reduction";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     सत्य, clauses);
	  c_name = "task_reduction";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  यदि (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  यदि (!first)
	    गच्छ clause_not_first;
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  यदि (!first)
	    गच्छ clause_not_first;
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  यदि (!first)
	    गच्छ clause_not_first;
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_TO:
	  यदि ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      रूख nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      लागि (रूख c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  अन्यथा
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_अङ्क_TEAMS:
	  clauses = c_parser_omp_clause_अङ्क_teams (parser, clauses);
	  c_name = "num_teams";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, असत्य);
	  c_name = "map";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  रोक;
	पक्ष PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  रोक;
	स्वभाव:
	  c_parser_error (parser, "expected an OpenMP clause");
	  गच्छ saw_error;
	}

      first = असत्य;

      यदि (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  यदि (!nested)
    c_parser_skip_to_pragma_eol (parser);

  यदि (finish_p)
    {
      यदि ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	फर्काऊ c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      यदि ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	फर्काऊ c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      फर्काऊ c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  फर्काऊ clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

स्थिर रूख
c_parser_omp_structured_block (c_parser *parser, तार्किक *if_p)
{
  रूख stmt = थप_stmt_list ();
  parser->omp_attrs_forbidden_p = सत्य;
  c_parser_statement (parser, if_p);
  फर्काऊ झिक_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

स्थिर रूख
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  रूख stmt, clauses = NULL_रूख;
  तार्किक readonly = असत्य;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      यदि (token->type == CPP_NAME
	  && !म_भेद (IDENTIFIER_POINTER (token->मान), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = सत्य;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_रूख);
      parens.skip_until_found_close (parser);
    }

  यदि (readonly)
    लागि (रूख c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_गाँठो (OACC_CACHE);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  add_stmt (stmt);

  फर्काऊ stmt;
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

स्थिर रूख
c_parser_oacc_data (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  फर्काऊ stmt;
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
  रूख clauses, stmt, t, decl;

  तार्किक error = असत्य;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  यदि (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      फर्काऊ;
    }

  लागि (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      यदि (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = सत्य;
	  जारी;
	}

      विकल्प (OMP_CLAUSE_MAP_KIND (t))
	{
	पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	पक्ष GOMP_MAP_ALLOC:
	पक्ष GOMP_MAP_TO:
	पक्ष GOMP_MAP_FORCE_DEVICEPTR:
	पक्ष GOMP_MAP_DEVICE_RESIDENT:
	  रोक;

	पक्ष GOMP_MAP_LINK:
	  यदि (!global_bindings_p ()
	      && (रूख_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = सत्य;
	      जारी;
	    }
	  रोक;

	स्वभाव:
	  यदि (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = सत्य;
	      जारी;
	    }
	  यदि (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = सत्य;
	      जारी;
	    }
	  अन्यथा यदि (रूख_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = सत्य;
	      जारी;
	    }
	  रोक;
	}

      यदि (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = सत्य;
	  जारी;
	}

      यदि (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = सत्य;
	  जारी;
	}

      यदि (!error)
	{
	  रूख id;

	  यदि (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  अन्यथा
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = रूख_cons (id, NULL_रूख, DECL_ATTRIBUTES (decl));

	  यदि (global_bindings_p ())
	    {
	      symtab_गाँठो *गाँठो = symtab_गाँठो::get (decl);
	      यदि (गाँठो != रिक्त)
		{
		  गाँठो->offloadable = 1;
		  यदि (ENABLE_OFFLOADING)
		    {
		      g->have_offload = सत्य;
		      यदि (is_a <varpool_गाँठो *> (गाँठो))
			vec_safe_थप (offload_vars, decl);
		    }
		}
	    }
	}
    }

  यदि (error || global_bindings_p ())
    फर्काऊ;

  stmt = make_गाँठो (OACC_DECLARE);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ति_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  फर्काऊ;
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
  रूख clauses, stmt;
  अचर वर्ण *p = "";

  c_parser_consume_pragma (parser);

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      c_parser_consume_token (parser);
    }

  यदि (म_भेद (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = सत्य;
      c_parser_skip_to_pragma_eol (parser);
      फर्काऊ;
    }

  यदि (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  अन्यथा
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  यदि (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_रूख)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      फर्काऊ;
    }

  stmt = enter ? make_गाँठो (OACC_ENTER_DATA) : make_गाँठो (OACC_EXIT_DATA);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
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

स्थिर रूख
c_parser_oacc_host_data (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", असत्य);
  यदि (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      फर्काऊ error_mark_गाँठो;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  फर्काऊ stmt;
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
स्थिर रूख
c_parser_oacc_loop (location_t loc, c_parser *parser, वर्ण *p_name,
		    omp_clause_mask mask, रूख *cclauses, तार्किक *if_p)
{
  तार्किक is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  म_जोड़ो (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  रूख clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == रिक्त,
					    /*target=*/is_parallel);
  यदि (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      यदि (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      यदि (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  रूख block = c_begin_compound_stmt (सत्य);
  रूख stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, रिक्त,
				     if_p);
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ stmt;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अङ्क_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अङ्क_WORKERS)		\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अङ्क_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अङ्क_WORKERS)		\
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

स्थिर रूख
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       गणना pragma_kind p_kind, वर्ण *p_name, तार्किक *if_p)
{
  omp_clause_mask mask;
  गणना रूख_code code;
  विकल्प (p_kind)
    {
    पक्ष PRAGMA_OACC_KERNELS:
      म_जोड़ो (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      रोक;
    पक्ष PRAGMA_OACC_PARALLEL:
      म_जोड़ो (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      रोक;
    पक्ष PRAGMA_OACC_SERIAL:
      म_जोड़ो (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      रोक;
    स्वभाव:
      gcc_unreachable ();
    }

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  रूख block = c_begin_omp_parallel ();
	  रूख clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  फर्काऊ c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  रूख clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/सत्य,
					    /*target=*/सत्य);

  रूख block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  फर्काऊ c_finish_omp_construct (loc, code, block, clauses);
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
  data.error_seen = असत्य;
  data.fndecl_seen = असत्य;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      रूख decl = NULL_रूख;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      यदि (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->मान);
	  यदि (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->मान);
	  c_parser_consume_token (parser);
	}
      अन्यथा
	c_parser_error (parser, "expected function name");

      यदि (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  फर्काऊ;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      यदि (रूख_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  फर्काऊ;
	}

      c_finish_oacc_routine (&data, decl, असत्य);
    }
  अन्यथा /* No optional '( name )'.  */
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
      यदि (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  फर्काऊ;
	}

      /* We only have to consider the pragma_external case here.  */
      यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णाङ्क ext = disable_extension_diagnostics ();
	  गर
	    c_parser_consume_token (parser);
	  जबसम्म (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, असत्य, सत्य,
					 असत्य, रिक्त, रिक्त, असत्य, रिक्त, &data);
	  restore_extension_diagnostics (ext);
	}
      अन्यथा
	c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, असत्य, सत्य,
				       असत्य, रिक्त, रिक्त, असत्य, रिक्त, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

स्थिर शून्य
c_finish_oacc_routine (संरचना oacc_routine_data *data, रूख fndecl,
		       तार्किक is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  यदि (data->error_seen
      || fndecl == error_mark_गाँठो)
    फर्काऊ;

  यदि (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = सत्य;
      फर्काऊ;
    }
  यदि (fndecl == NULL_रूख || रूख_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = सत्य;
      फर्काऊ;
    }

  पूर्णाङ्क compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  यदि (compatible < 0)
    {
      data->error_seen = सत्य;
      फर्काऊ;
    }
  यदि (compatible > 0)
    {
    }
  अन्यथा
    {
      यदि (रूख_USED (fndecl) || (!is_defn && DECL_SAVED_रूख (fndecl)))
	{
	  error_at (data->loc,
		    रूख_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = सत्य;
	  फर्काऊ;
	}

      /* Set the routine's level of parallelism.  */
      रूख dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= रूख_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = सत्य;
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

  रूख clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  यदि (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_रूख)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      फर्काऊ;
    }

  यदि (parser->error)
    फर्काऊ;

  रूख stmt = make_गाँठो (OACC_UPDATE);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

स्थिर रूख
c_parser_oacc_wait (location_t loc, c_parser *parser, वर्ण *p_name)
{
  रूख clauses, list = NULL_रूख, stmt = NULL_रूख;

  यदि (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  म_नकल (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  फर्काऊ stmt;
}

संरचना c_omp_loc_रूख
{
  location_t loc;
  रूख var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
स्थिर रूख
c_check_omp_allocate_allocator_r (रूख *tp, पूर्णाङ्क *, शून्य *data)
{
  रूख var = ((संरचना c_omp_loc_रूख *) data)->var;
  location_t loc = ((संरचना c_omp_loc_रूख *) data)->loc;
  यदि (रूख_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      यदि (linemap_location_before_p (पङ्क्ति_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  फर्काऊ *tp;
	}
      अन्यथा
	{
	  gcc_assert (cur_stmt_list
		      && रूख_CODE (cur_stmt_list) == STATEMENT_LIST);

	  रूख_stmt_iterator l = tsi_last (cur_stmt_list);
	  जबसम्म (!tsi_end_p (l))
	    {
	      यदि (linemap_location_before_p (पङ्क्ति_table, अभिव्यक्ति_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  रोक;
	      यदि (रूख_CODE (*l) == MODIFY_अभिव्यक्ति
		  && रूख_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (अभिव्यक्ति_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  फर्काऊ *tp;
		}
	      --l;
	    }
	}
    }
  फर्काऊ NULL_रूख;
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
  रूख alignment = NULL_रूख;
  रूख allocator = NULL_रूख;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  रूख nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_रूख);
  गर
    {
      यदि (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      यदि (!c_parser_next_token_is (parser, CPP_NAME))
	रोक;
      matching_parens parens;
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      c_parser_consume_token (parser);
      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      यदि (म_भेद ("align", p) != 0 && म_भेद ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  रोक;
	}
      यदि (!parens.require_open (parser))
	रोक;

      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, असत्य, सत्य);
      अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
      यदि (अभिव्यक्ति.मान == error_mark_गाँठो)
	;
      अन्यथा यदि (p[2] == 'i' && alignment)
	{
	  error_at (अभिव्यक्ति_loc, "too many %qs clauses", "align");
	  रोक;
	}
      अन्यथा यदि (p[2] == 'i')
	{
	  alignment = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
	  यदि (रूख_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (रूख_TYPE (alignment))
	      || रूख_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (अभिव्यक्ति_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_रूख;
	    }
	}
      अन्यथा यदि (allocator)
	{
	  error_at (अभिव्यक्ति_loc, "too many %qs clauses", "allocator");
	  रोक;
	}
      अन्यथा
	{
	  allocator = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
	  allocator_loc = अभिव्यक्ति_loc;
	  रूख orig_type
	    = अभिव्यक्ति.original_type ? अभिव्यक्ति.original_type : रूख_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (allocator))
	      || रूख_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (अभिव्यक्ति_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			रूख_TYPE (allocator));
	      allocator = NULL_रूख;
	    }
	}
      parens.skip_until_found_close (parser);
    } जबसम्म (सत्य);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  लागि (रूख c = nl; c != NULL_रूख; c = OMP_CLAUSE_CHAIN (c))
    {
      रूख var = OMP_CLAUSE_DECL (c);
      यदि (रूख_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  जारी;
	}
      यदि (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  जारी;
	}
      यदि (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  जारी;
	}
      यदि (रूख_STATIC (var))
	{
	  यदि (allocator == NULL_रूख && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      जारी;
	    }
	  अन्यथा यदि (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  अन्यथा यदि (allocator
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
      यदि (allocator)
	{
	  संरचना c_omp_loc_रूख data
	    = {अभिव्यक्ति_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_रूख (&allocator, c_check_omp_allocate_allocator_r, &data, रिक्त);
	}
      DECL_ATTRIBUTES (var) = रूख_cons (get_identifier ("omp allocate"),
					 build_रूख_list (allocator, alignment),
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
  रूख lhs = NULL_रूख, rhs = NULL_रूख, v = NULL_रूख, r = NULL_रूख;
  रूख lhs1 = NULL_रूख, rhs1 = NULL_रूख;
  रूख stmt, orig_lhs, unfolded_lhs = NULL_रूख, unfolded_lhs1 = NULL_रूख;
  गणना रूख_code code = ERROR_MARK, opcode = NOP_अभिव्यक्ति;
  गणना omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  location_t eloc;
  तार्किक structured_block = असत्य;
  तार्किक swapped = असत्य;
  तार्किक non_lvalue_p;
  रूख clauses = NULL_रूख;
  तार्किक capture = असत्य;
  तार्किक compare = असत्य;
  तार्किक weak = असत्य;
  गणना omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  तार्किक no_semicolon = असत्य;
  तार्किक extra_scope = असत्य;

  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      यदि (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      यदि (c_parser_next_token_is (parser, CPP_NAME))
	{
	  अचर वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  गणना रूख_code new_code = ERROR_MARK;
	  गणना omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  तार्किक new_capture = असत्य;
	  तार्किक new_compare = असत्य;
	  तार्किक new_weak = असत्य;
	  गणना omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  यदि (!म_भेद (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  अन्यथा यदि (!म_भेद (p, "write"))
	    new_code = NOP_अभिव्यक्ति;
	  अन्यथा यदि (!म_भेद (p, "update"))
	    new_code = OMP_ATOMIC;
	  अन्यथा यदि (openacc && !म_भेद (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  अन्यथा यदि (openacc)
	    {
	      p = रिक्त;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  अन्यथा यदि (!म_भेद (p, "capture"))
	    new_capture = सत्य;
	  अन्यथा यदि (!म_भेद (p, "compare"))
	    new_compare = सत्य;
	  अन्यथा यदि (!म_भेद (p, "weak"))
	    new_weak = सत्य;
	  अन्यथा यदि (!म_भेद (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      यदि (!parens.require_open (parser))
		जारी;

	      यदि (c_parser_next_token_is (parser, CPP_NAME))
		{
		  अचर वर्ण *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

		  यदि (!म_भेद (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  अन्यथा यदि (!म_भेद (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  अन्यथा यदि (!म_भेद (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      यदि (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  यदि (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  अन्यथा
		    fail = new_fail;
		}
	      अन्यथा
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      जारी;
	    }
	  अन्यथा यदि (!म_भेद (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  अन्यथा यदि (!म_भेद (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  अन्यथा यदि (!म_भेद (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  अन्यथा यदि (!म_भेद (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  अन्यथा यदि (!म_भेद (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  अन्यथा यदि (!म_भेद (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      जारी;
	    }
	  अन्यथा
	    {
	      p = रिक्त;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  यदि (p)
	    {
	      यदि (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  यदि (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  अन्यथा यदि (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  अन्यथा
		    code = new_code;
		}
	      अन्यथा यदि (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  यदि (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  अन्यथा
		    memory_order = new_memory_order;
		}
	      अन्यथा यदि (new_capture)
		{
		  यदि (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  अन्यथा
		    capture = सत्य;
		}
	      अन्यथा यदि (new_compare)
		{
		  यदि (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  अन्यथा
		    compare = सत्य;
		}
	      अन्यथा यदि (new_weak)
		{
		  यदि (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  अन्यथा
		    weak = सत्य;
		}
	      c_parser_consume_token (parser);
	      जारी;
	    }
	}
      रोक;
    }
  c_parser_skip_to_pragma_eol (parser);

  यदि (code == ERROR_MARK)
    code = OMP_ATOMIC;
  यदि (capture)
    {
      यदि (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      अन्यथा
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  यदि (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = असत्य;
    }
  यदि (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  यदि (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = असत्य;
    }
  यदि (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  अन्यथा यदि (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
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
	  रोक;
	पक्ष OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  रोक;
	पक्ष OMP_MEMORY_ORDER_ACQUIRE:
	  यदि (code == NOP_अभिव्यक्ति)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  अन्यथा
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  रोक;
	पक्ष OMP_MEMORY_ORDER_RELEASE:
	  यदि (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  अन्यथा
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  रोक;
	पक्ष OMP_MEMORY_ORDER_ACQ_REL:
	  विकल्प (code)
	    {
	    पक्ष OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      रोक;
	    पक्ष NOP_अभिव्यक्ति: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      रोक;
	    स्वभाव:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      रोक;
	    }
	  रोक;
	स्वभाव:
	  gcc_unreachable ();
	}
    }
  अन्यथा
    विकल्प (code)
      {
      पक्ष OMP_ATOMIC_READ:
	यदि (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	अन्यथा यदि (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	रोक;
      पक्ष NOP_अभिव्यक्ति: /* atomic write */
	यदि (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	अन्यथा यदि (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	रोक;
      स्वभाव:
	रोक;
      }
  यदि (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (गणना omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  विकल्प (code)
    {
    पक्ष OMP_ATOMIC_READ:
    पक्ष NOP_अभिव्यक्ति: /* atomic write */
      v = c_parser_cast_expression (parser, रिक्त).मान;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, असत्य, रिक्त, सत्य);
      यदि (v == error_mark_गाँठो)
	गच्छ saw_error;
      यदि (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      यदि (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	गच्छ saw_error;
      यदि (code == NOP_अभिव्यक्ति)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  अभिव्यक्ति = c_parser_expression (parser);
	  अभिव्यक्ति = default_function_array_read_conversion (eloc, अभिव्यक्ति);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_रूख;
	  rhs = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त);
	  यदि (rhs == error_mark_गाँठो)
	    गच्छ saw_error;
	}
      अन्यथा
	{
	  lhs = c_parser_cast_expression (parser, रिक्त).मान;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, असत्य, रिक्त, सत्य);
	  यदि (lhs == error_mark_गाँठो)
	    गच्छ saw_error;
	  यदि (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      गच्छ done;
    पक्ष OMP_ATOMIC_CAPTURE_NEW:
      यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = सत्य;
	}
      अन्यथा यदि (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	रोक;
      अन्यथा
	{
	  v = c_parser_cast_expression (parser, रिक्त).मान;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, असत्य, रिक्त, सत्य);
	  यदि (v == error_mark_गाँठो)
	    गच्छ saw_error;
	  यदि (non_lvalue_p)
	    v = non_lvalue (v);
	  यदि (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    गच्छ saw_error;
	  यदि (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      गच्छ saw_error;
	    }
	}
      रोक;
    स्वभाव:
      रोक;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  यदि (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      यदि (!parens.require_open (parser))
	गच्छ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति cmp_अभिव्यक्ति;
      यदि (r)
	{
	  cmp_अभिव्यक्ति = c_parser_cast_expression (parser, रिक्त);
	  cmp_अभिव्यक्ति = default_function_array_conversion (eloc, cmp_अभिव्यक्ति);
	}
      अन्यथा
	cmp_अभिव्यक्ति = c_parser_द्विआधारी_expression (parser, रिक्त, void_list_गाँठो);
      parens.skip_until_found_close (parser);
      यदि (cmp_अभिव्यक्ति.मान == error_mark_गाँठो)
	गच्छ saw_error;
      यदि (r)
	{
	  यदि (!c_रूख_equal (cmp_अभिव्यक्ति.मान, unfolded_lhs))
	    गच्छ bad_if;
	  cmp_अभिव्यक्ति.मान = rhs1;
	  rhs1 = NULL_रूख;
	  gcc_assert (रूख_CODE (cmp_अभिव्यक्ति.मान) == EQ_अभिव्यक्ति);
	}
      यदि (रूख_CODE (cmp_अभिव्यक्ति.मान) == EQ_अभिव्यक्ति)
	;
      अन्यथा यदि (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (अभिव्यक्ति_LOC_OR_LOC (cmp_अभिव्यक्ति.मान, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  गच्छ saw_error;
	}
      अन्यथा यदि (रूख_CODE (cmp_अभिव्यक्ति.मान) != GT_अभिव्यक्ति
	       && रूख_CODE (cmp_अभिव्यक्ति.मान) != LT_अभिव्यक्ति)
	{
	  error_at (अभिव्यक्ति_LOC_OR_LOC (cmp_अभिव्यक्ति.मान, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  गच्छ saw_error;
	}
      यदि (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	गच्छ saw_error;

      extra_scope = सत्य;
      eloc = c_parser_peek_token (parser)->location;
      अभिव्यक्ति = c_parser_cast_expression (parser, रिक्त);
      lhs = अभिव्यक्ति.मान;
      अभिव्यक्ति = default_function_array_conversion (eloc, अभिव्यक्ति);
      unfolded_lhs = अभिव्यक्ति.मान;
      lhs = c_fully_fold (lhs, असत्य, रिक्त, सत्य);
      orig_lhs = lhs;
      यदि (lhs == error_mark_गाँठो)
	गच्छ saw_error;
      यदि (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      यदि (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  गच्छ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      rhs1 = अभिव्यक्ति.मान;

      यदि (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	गच्छ saw_error;

      यदि (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	गच्छ saw_error;

      extra_scope = असत्य;
      no_semicolon = सत्य;

      यदि (c_रूख_equal (रूख_OPERAND (cmp_अभिव्यक्ति.मान, 0), unfolded_lhs))
	{
	  यदि (रूख_CODE (cmp_अभिव्यक्ति.मान) == EQ_अभिव्यक्ति)
	    {
	      opcode = COND_अभिव्यक्ति;
	      rhs = c_fully_fold (रूख_OPERAND (cmp_अभिव्यक्ति.मान, 1),
				  असत्य, रिक्त, सत्य);
	      rhs1 = c_fully_fold (rhs1, असत्य, रिक्त, सत्य);
	    }
	  अन्यथा यदि (c_रूख_equal (रूख_OPERAND (cmp_अभिव्यक्ति.मान, 1), rhs1))
	    {
	      opcode = (रूख_CODE (cmp_अभिव्यक्ति.मान) == GT_अभिव्यक्ति
			? MIN_अभिव्यक्ति : MAX_अभिव्यक्ति);
	      rhs = c_fully_fold (rhs1, असत्य, रिक्त, सत्य);
	      rhs1 = c_fully_fold (रूख_OPERAND (cmp_अभिव्यक्ति.मान, 0),
				   असत्य, रिक्त, सत्य);
	    }
	  अन्यथा
	    गच्छ bad_if;
	}
      अन्यथा यदि (रूख_CODE (cmp_अभिव्यक्ति.मान) == EQ_अभिव्यक्ति)
	गच्छ bad_if;
      अन्यथा यदि (c_रूख_equal (रूख_OPERAND (cmp_अभिव्यक्ति.मान, 1), unfolded_lhs)
	       && c_रूख_equal (रूख_OPERAND (cmp_अभिव्यक्ति.मान, 0), rhs1))
	{
	  opcode = (रूख_CODE (cmp_अभिव्यक्ति.मान) == GT_अभिव्यक्ति
		    ? MAX_अभिव्यक्ति : MIN_अभिव्यक्ति);
	  rhs = c_fully_fold (rhs1, असत्य, रिक्त, सत्य);
	  rhs1 = c_fully_fold (रूख_OPERAND (cmp_अभिव्यक्ति.मान, 1),
			       असत्य, रिक्त, सत्य);
	}
      अन्यथा
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  गच्छ saw_error;
	}

      यदि (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  यदि (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_रूख)
	      || रूख_CODE (cmp_अभिव्यक्ति.मान) != EQ_अभिव्यक्ति)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      गच्छ saw_error;
	    }

	  c_parser_consume_token (parser);

	  यदि (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    गच्छ saw_error;

	  extra_scope = सत्य;
	  v = c_parser_cast_expression (parser, रिक्त).मान;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, असत्य, रिक्त, सत्य);
	  यदि (v == error_mark_गाँठो)
	    गच्छ saw_error;
	  यदि (non_lvalue_p)
	    v = non_lvalue (v);
	  यदि (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    गच्छ saw_error;

	  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);

	  यदि (!c_रूख_equal (अभिव्यक्ति.मान, unfolded_lhs))
	    गच्छ bad_if;

	  यदि (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    गच्छ saw_error;

	  यदि (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    गच्छ saw_error;

	  extra_scope = असत्य;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  यदि (r == NULL_रूख)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_गाँठो;
	}
      अन्यथा यदि (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  गच्छ saw_error;
	}
      अन्यथा यदि (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_रूख
	       && v == NULL_रूख)
	code = OMP_ATOMIC;
      गच्छ stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  अभिव्यक्ति = c_parser_cast_expression (parser, रिक्त);
  lhs = अभिव्यक्ति.मान;
  अभिव्यक्ति = default_function_array_conversion (eloc, अभिव्यक्ति);
  unfolded_lhs = अभिव्यक्ति.मान;
  lhs = c_fully_fold (lhs, असत्य, रिक्त, सत्य);
  orig_lhs = lhs;
  विकल्प (रूख_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    पक्ष ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      यदि (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      यदि (structured_block)
	{
	  यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  अन्यथा यदि (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      फर्काऊ;

    पक्ष POSTINCREMENT_अभिव्यक्ति:
      यदि (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    पक्ष PREINCREMENT_अभिव्यक्ति:
      lhs = रूख_OPERAND (lhs, 0);
      unfolded_lhs = NULL_रूख;
      opcode = PLUS_अभिव्यक्ति;
      rhs = integer_one_गाँठो;
      यदि (compare)
	गच्छ invalid_compare;
      रोक;

    पक्ष POSTDECREMENT_अभिव्यक्ति:
      यदि (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    पक्ष PREDECREMENT_अभिव्यक्ति:
      lhs = रूख_OPERAND (lhs, 0);
      unfolded_lhs = NULL_रूख;
      opcode = MINUS_अभिव्यक्ति;
      rhs = integer_one_गाँठो;
      यदि (compare)
	गच्छ invalid_compare;
      रोक;

    पक्ष COMPOUND_अभिव्यक्ति:
      यदि (रूख_CODE (रूख_OPERAND (lhs, 0)) == SAVE_अभिव्यक्ति
	  && रूख_CODE (रूख_OPERAND (lhs, 1)) == COMPOUND_अभिव्यक्ति
	  && रूख_CODE (रूख_OPERAND (रूख_OPERAND (lhs, 1), 0)) == MODIFY_अभिव्यक्ति
	  && रूख_OPERAND (रूख_OPERAND (lhs, 1), 1) == रूख_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (रूख_TYPE (रूख_OPERAND (रूख_OPERAND
					      (रूख_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = रूख_OPERAND (रूख_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    पक्ष MODIFY_अभिव्यक्ति:
      यदि (रूख_CODE (lhs) == MODIFY_अभिव्यक्ति
	  && C_BOOLEAN_TYPE_P (रूख_TYPE (रूख_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  यदि (integer_onep (रूख_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = रूख_OPERAND (lhs, 1);
	      lhs = रूख_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_रूख;
	      opcode = NOP_अभिव्यक्ति;
	      यदि (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && रूख_CODE (orig_lhs) == COMPOUND_अभिव्यक्ति)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      यदि (compare)
		गच्छ invalid_compare;
	      रोक;
	    }
	  यदि (रूख_CODE (रूख_OPERAND (lhs, 1)) == TRUTH_NOT_अभिव्यक्ति
	      && रूख_OPERAND (lhs, 0)
		 == रूख_OPERAND (रूख_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = रूख_OPERAND (lhs, 1);
	      lhs = रूख_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_रूख;
	      opcode = NOP_अभिव्यक्ति;
	      यदि (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && रूख_CODE (orig_lhs) == COMPOUND_अभिव्यक्ति)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      यदि (compare)
		गच्छ invalid_compare;
	      रोक;
	    }
	}
      /* FALLTHRU */
    स्वभाव:
      यदि (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      यदि (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  गच्छ saw_error;
	}
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_MULT_EQ:
	  opcode = MULT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_DIV_EQ:
	  opcode = TRUNC_DIV_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_PLUS_EQ:
	  opcode = PLUS_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_MINUS_EQ:
	  opcode = MINUS_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_LSHIFT_EQ:
	  opcode = LSHIFT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_RSHIFT_EQ:
	  opcode = RSHIFT_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_AND_EQ:
	  opcode = BIT_AND_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_OR_EQ:
	  opcode = BIT_IOR_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_XOR_EQ:
	  opcode = BIT_XOR_अभिव्यक्ति;
	  रोक;
	पक्ष CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त, unfolded_lhs);
	  rhs1 = अभिव्यक्ति.मान;
	  विकल्प (रूख_CODE (rhs1))
	    {
	    पक्ष MULT_अभिव्यक्ति:
	    पक्ष TRUNC_DIV_अभिव्यक्ति:
	    पक्ष RDIV_अभिव्यक्ति:
	    पक्ष PLUS_अभिव्यक्ति:
	    पक्ष MINUS_अभिव्यक्ति:
	    पक्ष LSHIFT_अभिव्यक्ति:
	    पक्ष RSHIFT_अभिव्यक्ति:
	    पक्ष BIT_AND_अभिव्यक्ति:
	    पक्ष BIT_IOR_अभिव्यक्ति:
	    पक्ष BIT_XOR_अभिव्यक्ति:
	      यदि (compare)
		रोक;
	      यदि (c_रूख_equal (रूख_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = रूख_CODE (rhs1);
		  rhs = c_fully_fold (रूख_OPERAND (rhs1, 1), असत्य, रिक्त,
				      सत्य);
		  rhs1 = c_fully_fold (रूख_OPERAND (rhs1, 0), असत्य, रिक्त,
				       सत्य);
		  गच्छ stmt_done;
		}
	      यदि (c_रूख_equal (रूख_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = रूख_CODE (rhs1);
		  rhs = c_fully_fold (रूख_OPERAND (rhs1, 0), असत्य, रिक्त,
				      सत्य);
		  rhs1 = c_fully_fold (रूख_OPERAND (rhs1, 1), असत्य, रिक्त,
				       सत्य);
		  swapped = !commutative_रूख_code (opcode);
		  गच्छ stmt_done;
		}
	      रोक;
	    पक्ष COND_अभिव्यक्ति:
	      यदि (!compare)
		रोक;
	      यदि (रूख_CODE (रूख_OPERAND (rhs1, 0)) != GT_अभिव्यक्ति
		  && रूख_CODE (रूख_OPERAND (rhs1, 0)) != LT_अभिव्यक्ति
		  && रूख_CODE (रूख_OPERAND (rhs1, 0)) != EQ_अभिव्यक्ति)
		रोक;
	      यदि (!रूख_OPERAND (rhs1, 1))
		रोक;
	      यदि (!c_रूख_equal (रूख_OPERAND (rhs1, 2), unfolded_lhs))
		रोक;
	      यदि (c_रूख_equal (रूख_OPERAND (रूख_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  यदि (रूख_CODE (रूख_OPERAND (rhs1, 0)) == EQ_अभिव्यक्ति)
		    {
		      opcode = COND_अभिव्यक्ति;
		      rhs = c_fully_fold (रूख_OPERAND (रूख_OPERAND (rhs1,
								      0), 1),
					  असत्य, रिक्त, सत्य);
		      rhs1 = c_fully_fold (रूख_OPERAND (rhs1, 1), असत्य,
					   रिक्त, सत्य);
		      गच्छ stmt_done;
		    }
		  यदि (c_रूख_equal (रूख_OPERAND (रूख_OPERAND (rhs1, 0), 1),
				    रूख_OPERAND (rhs1, 1)))
		    {
		      opcode = (रूख_CODE (रूख_OPERAND (rhs1, 0)) == GT_अभिव्यक्ति
				? MIN_अभिव्यक्ति : MAX_अभिव्यक्ति);
		      rhs = c_fully_fold (रूख_OPERAND (rhs1, 1), असत्य, रिक्त,
					  सत्य);
		      rhs1 = c_fully_fold (रूख_OPERAND (रूख_OPERAND (rhs1,
								       0), 0),
					   असत्य, रिक्त, सत्य);
		      गच्छ stmt_done;
		    }
		}
	      अन्यथा यदि (रूख_CODE (रूख_OPERAND (rhs1, 0)) == EQ_अभिव्यक्ति)
		रोक;
	      अन्यथा यदि (c_रूख_equal (रूख_OPERAND (रूख_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  यदि (c_रूख_equal (रूख_OPERAND (रूख_OPERAND (rhs1, 0), 0),
				    रूख_OPERAND (rhs1, 1)))
		    {
		      opcode = (रूख_CODE (रूख_OPERAND (rhs1, 0)) == GT_अभिव्यक्ति
				? MAX_अभिव्यक्ति : MIN_अभिव्यक्ति);
		      rhs = c_fully_fold (रूख_OPERAND (rhs1, 1), असत्य, रिक्त,
					  सत्य);
		      rhs1 = c_fully_fold (रूख_OPERAND (रूख_OPERAND (rhs1,
								       0), 1),
					   असत्य, रिक्त, सत्य);
		      गच्छ stmt_done;
		    }
		}
	      रोक;
	    पक्ष EQ_अभिव्यक्ति:
	      यदि (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		रोक;
	      यदि (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_रूख;
		  c_parser_consume_token (parser);
		  गच्छ restart;
		}
	      रोक;
	    पक्ष ERROR_MARK:
	      गच्छ saw_error;
	    स्वभाव:
	      रोक;
	    }
	  यदि (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      यदि (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_रूख;
		  अभिव्यक्ति = default_function_array_read_conversion (eloc, अभिव्यक्ति);
		  unfolded_lhs1 = अभिव्यक्ति.मान;
		  lhs1 = c_fully_fold (unfolded_lhs1, असत्य, रिक्त, सत्य);
		  rhs1 = NULL_रूख;
		  c_parser_consume_token (parser);
		  गच्छ restart;
		}
	      यदि (structured_block && !compare)
		{
		  opcode = NOP_अभिव्यक्ति;
		  अभिव्यक्ति = default_function_array_read_conversion (eloc, अभिव्यक्ति);
		  rhs = c_fully_fold (अभिव्यक्ति.मान, असत्य, रिक्त, सत्य);
		  rhs1 = NULL_रूख;
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
      अभिव्यक्ति = c_parser_expression (parser);
      अभिव्यक्ति = default_function_array_read_conversion (eloc, अभिव्यक्ति);
      rhs = अभिव्यक्ति.मान;
      rhs = c_fully_fold (rhs, असत्य, रिक्त, सत्य);
      रोक;
    }
stmt_done:
  यदि (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_रूख)
    {
      यदि (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	गच्छ saw_error;
      no_semicolon = असत्य;
      v = c_parser_cast_expression (parser, रिक्त).मान;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, असत्य, रिक्त, सत्य);
      यदि (v == error_mark_गाँठो)
	गच्छ saw_error;
      यदि (non_lvalue_p)
	v = non_lvalue (v);
      यदि (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	गच्छ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      अभिव्यक्ति = c_parser_cast_expression (parser, रिक्त);
      lhs1 = अभिव्यक्ति.मान;
      अभिव्यक्ति = default_function_array_read_conversion (eloc, अभिव्यक्ति);
      unfolded_lhs1 = अभिव्यक्ति.मान;
      lhs1 = c_fully_fold (lhs1, असत्य, रिक्त, सत्य);
      यदि (lhs1 == error_mark_गाँठो)
	गच्छ saw_error;
      यदि (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  यदि (structured_block)
    {
      यदि (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  यदि (weak && opcode != COND_अभिव्यक्ति)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = असत्य;
    }
  यदि (unfolded_lhs && unfolded_lhs1
      && !c_रूख_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_गाँठो;
    }
  अन्यथा
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  यदि (stmt != error_mark_गाँठो)
    add_stmt (stmt);

  यदि (!structured_block && !no_semicolon)
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

स्थिर रूख
c_parser_omp_critical (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख stmt, name = NULL_रूख, clauses = NULL_रूख;

  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      यदि (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->मान;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      अन्यथा
	c_parser_error (parser, "expected identifier");

      यदि (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  फर्काऊ c_finish_omp_critical (loc, stmt, name, clauses);
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
  यदि (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      फर्काऊ;
    }

  रूख depobj = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
  यदि (depobj != error_mark_गाँठो)
    {
      यदि (!lvalue_p (depobj))
	{
	  error_at (अभिव्यक्ति_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_गाँठो;
	}
      अन्यथा
	{
	  रूख addr = build_unary_op (अभिव्यक्ति_LOC_OR_LOC (depobj, loc), ADDR_अभिव्यक्ति,
				      depobj, असत्य);
	  यदि (addr == error_mark_गाँठो)
	    depobj = error_mark_गाँठो;
	  अन्यथा
	    depobj = build_indirect_ref (अभिव्यक्ति_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  रूख clause = NULL_रूख;
  गणना omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  यदि (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      c_parser_consume_token (parser);
      यदि (!म_भेद ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_रूख, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  यदि (!clause)
	    clause = error_mark_गाँठो;
	}
      अन्यथा यदि (!म_भेद ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      रूख destobj = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
	      यदि (!lvalue_p (destobj))
		error_at (अभिव्यक्ति_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      अन्यथा यदि (depobj != error_mark_गाँठो
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (अभिव्यक्ति_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      अन्यथा यदि (!म_भेद ("update", p))
	{
	  matching_parens c_parens;
	  यदि (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      यदि (c_parser_next_token_is (parser, CPP_NAME))
		{
		  अचर वर्ण *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

		  c_parser_consume_token (parser);
		  यदि (!म_भेद ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  अन्यथा यदि (!म_भेद ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  अन्यथा यदि (!म_भेद ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  अन्यथा यदि (!म_भेद ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  अन्यथा यदि (!म_भेद ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      यदि (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_गाँठो;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  अन्यथा
	    clause = error_mark_गाँठो;
	}
    }
  यदि (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_गाँठो;
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
  यदि (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      यदि (!म_भेद (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      अन्यथा यदि (!म_भेद (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      अन्यथा यदि (!म_भेद (p, "release"))
	mo = MEMMODEL_RELEASE;
      अन्यथा यदि (!म_भेद (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      अन्यथा
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      यदि (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, रिक्त);
    }
  अन्यथा यदि (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

स्थिर तार्किक
c_parser_omp_section_scan (c_parser *parser, अचर वर्ण *directive,
			   तार्किक tentative)
{
  यदि (!c_parser_nth_token_starts_std_attributes (parser, 1))
    फर्काऊ असत्य;
  अचिन्हित पूर्णाङ्क n = 3;
  यदि (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    फर्काऊ असत्य;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  यदि (token->type != CPP_CLOSE_SQUARE)
    फर्काऊ असत्य;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  यदि (token->type != CPP_CLOSE_SQUARE)
    फर्काऊ असत्य;
  यदि (n < 9)
    फर्काऊ असत्य;
  यदि (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      रूख first = c_parser_peek_nth_token_raw (parser, 3)->मान;
      रूख second = c_parser_peek_nth_token_raw (parser, 5)->मान;
      यदि (म_भेद (IDENTIFIER_POINTER (first), "directive")
	  && म_भेद (IDENTIFIER_POINTER (first), "__directive__"))
	फर्काऊ असत्य;
      यदि (म_भेद (IDENTIFIER_POINTER (second), directive))
	फर्काऊ असत्य;
    }
  यदि (tentative)
    फर्काऊ सत्य;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t बीच_loc = UNKNOWN_LOCATION;
  रूख std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  तार्किक seen = असत्य;
  पूर्णाङ्क cnt = 0;
  लागि (रूख attr = std_attrs; attr; attr = रूख_CHAIN (attr))
    यदि (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	लागि (रूख a = रूख_मान (attr); a; a = रूख_CHAIN (a))
	  {
	    रूख d = रूख_मान (a);
	    gcc_assert (रूख_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    यदि (first->type == CPP_NAME
		&& म_भेद (IDENTIFIER_POINTER (first->मान),
			   directive) == 0)
	      {
		seen = सत्य;
		यदि (बीच_loc == UNKNOWN_LOCATION)
		  बीच_loc = first->location;
	      }
	  }
      }
  यदि (!seen)
    फर्काऊ असत्य;
  यदि (cnt != 1 || रूख_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, बीच_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      फर्काऊ असत्य;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, रिक्त);
  फर्काऊ सत्य;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

स्थिर रूख
c_parser_omp_structured_block_sequence (c_parser *parser,
					गणना pragma_kind kind)
{
  रूख stmt = थप_stmt_list ();
  c_parser_statement (parser, रिक्त);
  गर
    {
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	रोक;
      यदि (c_parser_next_token_is (parser, CPP_EOF))
	रोक;

      यदि (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	रोक;

      यदि (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", असत्य))
	रोक;

      c_parser_statement (parser, रिक्त);
    }
  जबसम्म (1);
  फर्काऊ झिक_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

स्थिर शून्य
c_parser_omp_scan_loop_body (c_parser *parser, तार्किक open_brace_parsed)
{
  रूख substmt;
  location_t loc;
  रूख clauses = NULL_रूख;
  तार्किक found_scan = असत्य;

  loc = c_parser_peek_token (parser)->location;
  यदि (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = असत्य;
      फर्काऊ;
    }

  यदि (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  अन्यथा
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_गाँठो, substmt, NULL_रूख);
  SET_अभिव्यक्ति_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  यदि (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      गणना omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = सत्य;

      c_parser_consume_pragma (parser);

      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      यदि (c_parser_next_token_is (parser, CPP_NAME))
	{
	  अचर वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	  यदि (म_भेद (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  अन्यथा यदि (म_भेद (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      यदि (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_रूख);
	}
      अन्यथा
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  अन्यथा
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  यदि (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  अन्यथा
    {
      यदि (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_गाँठो, substmt, clauses);
  SET_अभिव्यक्ति_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
स्थिर तार्किक
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    गणना रूख_code code,
					    तार्किक error_p)
{
  यदि (code == OACC_LOOP)
    {
      यदि (c_parser_next_token_is_keyword (parser, RID_FOR))
	फर्काऊ सत्य;
      यदि (error_p)
	c_parser_error (parser, "for statement expected");
    }
  अन्यथा
    {
      यदि (c_parser_next_token_is_keyword (parser, RID_FOR))
	फर्काऊ सत्य;

      यदि (c_parser_next_token_is (parser, CPP_PRAGMA))
	विकल्प (c_parser_peek_token (parser)->pragma_kind)
	  {
	  पक्ष PRAGMA_OMP_UNROLL:
	  पक्ष PRAGMA_OMP_TILE:
	    फर्काऊ सत्य;
	  स्वभाव:
	    रोक;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      माप_प्रकार n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      यदि (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->मान)
	  && C_RID_CODE (token->मान) == RID_FOR)
	फर्काऊ सत्य;
      यदि (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  फर्काऊ असत्य;
}

स्थिर रूख c_parser_omp_tile (location_t, c_parser *, तार्किक *);
स्थिर रूख c_parser_omp_unroll (location_t, c_parser *, तार्किक *);

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

स्थिर रूख
c_parser_omp_loop_nest (c_parser *parser, तार्किक *if_p)
{
  रूख decl = NULL_रूख, cond = NULL_रूख, incr = NULL_रूख, init = NULL_रूख;
  रूख body = NULL_रूख;
  matching_parens parens;
  तार्किक moreloops;
  अचिन्हित वर्ण save_in_statement;
  रूख loop_scope;
  location_t loc;
  संरचना omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  पूर्णाङ्क depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  यदि (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      रूख std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, रिक्त);
      यदि (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  यदि (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      रूख transform = NULL_रूख, sizes, body = NULL_रूख;
      पूर्णाङ्क गन्ती = 0;
      विकल्प (c_parser_peek_token (parser)->pragma_kind)
	{
	पक्ष PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = थप_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = झिक_stmt_list (body);
	  यदि (transform == NULL_रूख || transform == error_mark_गाँठो)
	    {
	      transform = error_mark_गाँठो;
	      रोक;
	    }
	  gcc_assert (रूख_CODE (transform) == OMP_UNROLL);
	  यदि (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      यदि (omp_for_parse_state->गन्ती - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->गन्ती - depth);
		  transform = error_mark_गाँठो;
		}
	      अन्यथा
		गन्ती = 1;
	    }
	  अन्यथा
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_गाँठो;
	    }
	  रोक;
	पक्ष PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = थप_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = झिक_stmt_list (body);
	  यदि (transform == NULL_रूख || transform == error_mark_गाँठो)
	    {
	      transform = error_mark_गाँठो;
	      रोक;
	    }
	  gcc_assert (रूख_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  गन्ती = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  यदि (depth + गन्ती < omp_for_parse_state->गन्ती)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			गन्ती, omp_for_parse_state->गन्ती - depth);
	      transform = error_mark_गाँठो;
	    }
	  रोक;
	स्वभाव:
	  c_parser_pragma (parser, pragma_stmt, रिक्त, void_list_गाँठो);
	  रोक;
	}
      यदि (transform == NULL_रूख)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      यदि (transform == NULL_रूख || transform == error_mark_गाँठो)
	{
	  omp_for_parse_state->fail = सत्य;
	  फर्काऊ NULL_रूख;
	}
      लागि (गन्ती = omp_for_parse_state->गन्ती; depth < गन्ती; ++depth)
	{
	  रूख_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_रूख;
	  रूख_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_रूख;
	  रूख_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_रूख;
	  रूख_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_रूख;
	}
      omp_for_parse_state->want_nested_loop = असत्य;
      फर्काऊ body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = असत्य;

  यदि (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = सत्य;
      फर्काऊ NULL_रूख;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (सत्य);

  /* Parse the initialization declaration or expression.  */
  यदि (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      रूख this_pre_body = थप_stmt_list ();
      c_in_omp_for = सत्य;
      c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, सत्य, सत्य,
				     असत्य);
      c_in_omp_for = असत्य;
      this_pre_body = झिक_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      यदि (decl == रिक्त)
	गच्छ error_init;
      यदि (DECL_INITIAL (decl) == error_mark_गाँठो)
	decl = error_mark_गाँठो;
      init = decl;
    }
  अन्यथा यदि (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      संरचना c_अभिव्यक्ति decl_exp;
      संरचना c_अभिव्यक्ति init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.मान;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = सत्य;
      init = build_modify_अभिव्यक्ति (init_loc, decl, decl_exp.original_type,
				NOP_अभिव्यक्ति, init_loc, init_exp.मान,
				init_exp.original_type);
      c_in_omp_for = असत्य;
      init = c_process_अभिव्यक्ति_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  अन्यथा
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = सत्य;
      गच्छ parse_next;
    }

  /* Parse the loop condition.  */
  यदि (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = सत्य;
      संरचना c_अभिव्यक्ति cond_अभिव्यक्ति
	= c_parser_द्विआधारी_expression (parser, रिक्त, NULL_रूख);
      c_in_omp_for = असत्य;

      cond = cond_अभिव्यक्ति.मान;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      विकल्प (cond_अभिव्यक्ति.original_code)
	{
	पक्ष GT_अभिव्यक्ति:
	पक्ष GE_अभिव्यक्ति:
	पक्ष LT_अभिव्यक्ति:
	पक्ष LE_अभिव्यक्ति:
	  रोक;
	पक्ष NE_अभिव्यक्ति:
	  यदि (omp_for_parse_state->code != OACC_LOOP)
	    रोक;
	  /* FALLTHRU.  */
	स्वभाव:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_अभिव्यक्ति, boolean_type_गाँठो, error_mark_गाँठो);
	  रोक;
	}
      protected_set_अभिव्यक्ति_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  यदि (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_अभिव्यक्ति_stmt (incr_loc,
				  c_parser_expression (parser).मान);
    }
  parens.skip_until_found_close (parser);

  यदि (decl == रिक्त || decl == error_mark_गाँठो || init == error_mark_गाँठो)
    omp_for_parse_state->fail = सत्य;
  अन्यथा
    {
      रूख_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      रूख_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      रूख_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      रूख_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->गन्ती - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  यदि (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     असत्य))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  अन्यथा यदि (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = सत्य;
      body = c_parser_compound_statement (parser, रिक्त);
      omp_for_parse_state->in_intervening_code = असत्य;
      यदि (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = सत्य;
	}
      if_p = रिक्त;
    }
  अन्यथा
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      यदि (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = सत्य;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = रिक्त;
      body = थप_stmt_list ();
      यदि (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, असत्य);
      अन्यथा
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = झिक_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = असत्य;
  omp_for_parse_state->in_intervening_code = सत्य;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  यदि (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, सत्य);
  यदि (decl && रूख_CODE (body) == BIND_अभिव्यक्ति)
    {
      रूख t = BIND_अभिव्यक्ति_VARS (body);
      रूख prev = NULL_रूख, next = NULL_रूख;
      जबसम्म (t)
	{
	  next = DECL_CHAIN (t);
	  यदि (t == decl)
	    {
	      यदि (prev)
		DECL_CHAIN (prev) = next;
	      अन्यथा
		{
		  BIND_अभिव्यक्ति_VARS (body) = next;
		  BLOCK_VARS (BIND_अभिव्यक्ति_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      रोक;
	    }
	  अन्यथा
	    {
	      prev = t;
	      t = next;
	    }
	}
      यदि (BIND_अभिव्यक्ति_VARS (body) == NULL_रूख)
	body = BIND_अभिव्यक्ति_BODY (body);
    }

  फर्काऊ body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

स्थिर रूख
c_parser_omp_for_loop (location_t loc, c_parser *parser, गणना रूख_code code,
		       रूख clauses, रूख *cclauses, तार्किक *if_p)
{
  रूख body, stmt, cl;
  रूख ret = NULL_रूख;
  रूख ordered_cl = NULL_रूख;
  पूर्णाङ्क i, collapse = 1, ordered = 0, गन्ती;
  तार्किक oacc_tiling = असत्य;
  तार्किक inscan = असत्य;
  संरचना omp_for_parse_data data;
  संरचना omp_for_parse_data *save_data = parser->omp_for_parse_state;

  लागि (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    यदि (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = रूख_to_shwi (OMP_CLAUSE_COLLAPSE_अभिव्यक्ति (cl));
    अन्यथा यदि (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = सत्य;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    अन्यथा यदि (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    अन्यथा यदि (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_अभिव्यक्ति (cl))
      {
	ordered_cl = cl;
	ordered = रूख_to_shwi (OMP_CLAUSE_ORDERED_अभिव्यक्ति (cl));
      }
    अन्यथा यदि (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = सत्य;

  यदि (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_अभिव्यक्ति (ordered_cl)
	= build_int_cst (integer_type_गाँठो, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  गन्ती = ordered ? ordered : collapse;

  यदि (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, सत्य))
    फर्काऊ रिक्त;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_रूख_vec (गन्ती);
  data.initv = make_रूख_vec (गन्ती);
  data.condv = make_रूख_vec (गन्ती);
  data.incrv = make_रूख_vec (गन्ती);
  data.pre_body = NULL_रूख;
  data.bindings = NULL_रूख;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.गन्ती = गन्ती;
  data.depth = 0;
  data.want_nested_loop = सत्य;
  data.ordered = ordered > 0;
  data.in_intervening_code = असत्य;
  data.perfect_nesting_fail = असत्य;
  data.fail = असत्य;
  data.inscan = inscan;
  data.saw_intervening_code = असत्य;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  लागि (रूख t = data.bindings; t; )
    {
      रूख n = रूख_CHAIN (t);
      रूख_CHAIN (t) = NULL_रूख;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  यदि (!data.fail)
    {
      c_in_omp_for = सत्य;
      stmt = c_finish_omp_for (loc, code, data.declv, रिक्त, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, सत्य);
      c_in_omp_for = असत्य;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      यदि (stmt && !c_omp_check_loop_iv (stmt, data.declv, रिक्त))
	stmt = NULL_रूख;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      यदि (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, रिक्त))
	stmt = NULL_रूख;

      यदि (stmt)
	{
	  add_stmt (stmt);

	  लागि (i = 0; i < रूख_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      रूख init = रूख_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      यदि (init == NULL_रूख)
		रोक;
	      gcc_assert (रूख_CODE (init) == MODIFY_अभिव्यक्ति);
	      रूख decl = रूख_OPERAND (init, 0);
	      रूख cond = रूख_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (रूख_OPERAND (cond, 0) == decl);

	      रूख op0 = रूख_OPERAND (init, 1);
	      यदि (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || रूख_CODE (op0) != रूख_VEC)
		रूख_OPERAND (init, 1) = c_fully_fold (op0, असत्य, रिक्त);
	      अन्यथा
		{
		  रूख_VEC_ELT (op0, 1)
		    = c_fully_fold (रूख_VEC_ELT (op0, 1), असत्य, रिक्त);
		  रूख_VEC_ELT (op0, 2)
		    = c_fully_fold (रूख_VEC_ELT (op0, 2), असत्य, रिक्त);
		}

	      रूख op1 = रूख_OPERAND (cond, 1);
	      यदि (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || रूख_CODE (op1) != रूख_VEC)
		रूख_OPERAND (cond, 1) = c_fully_fold (op1, असत्य, रिक्त);
	      अन्यथा
		{
		  रूख_VEC_ELT (op1, 1)
		    = c_fully_fold (रूख_VEC_ELT (op1, 1), असत्य, रिक्त);
		  रूख_VEC_ELT (op1, 2)
		    = c_fully_fold (रूख_VEC_ELT (op1, 2), असत्य, रिक्त);
		}
	    }

	  यदि (cclauses != रिक्त
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != रिक्त)
	    {
	      रूख *c;
	      लागि (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		यदि (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		अन्यथा
		  {
		    लागि (i = 0; i < गन्ती; i++)
		      यदि (रूख_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			रोक;
		    यदि (i == गन्ती)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    अन्यथा यदि (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    अन्यथा
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			रूख l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			यदि (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			अन्यथा
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
  फर्काऊ ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

स्थिर शून्य
omp_split_clauses (location_t loc, गणना रूख_code code,
		   omp_clause_mask mask, रूख clauses, रूख *cclauses)
{
  पूर्णाङ्क i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  लागि (i = 0; i < C_OMP_CLAUSE_SPLIT_गन्ती; i++)
    यदि (cclauses[i])
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

स्थिर रूख
c_parser_omp_loop (location_t loc, c_parser *parser,
		   वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
		   तार्किक *if_p)
{
  रूख block, clauses, ret;

  म_जोड़ो (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (सत्य);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ ret;
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

स्थिर रूख
c_parser_omp_simd (location_t loc, c_parser *parser,
		   वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
		   तार्किक *if_p)
{
  रूख block, clauses, ret;

  म_जोड़ो (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (सत्य);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ ret;
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

स्थिर रूख
c_parser_omp_for (location_t loc, c_parser *parser,
		  वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
		  तार्किक *if_p)
{
  रूख block, clauses, ret;

  म_जोड़ो (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  यदि (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  यदि ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      यदि (म_भेद (p, "simd") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  यदि (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (सत्य);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, सत्य);
	  यदि (ret == NULL_रूख)
	    फर्काऊ ret;
	  ret = make_गाँठो (OMP_FOR);
	  रूख_TYPE (ret) = void_type_गाँठो;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_अभिव्यक्ति_LOCATION (ret, loc);
	  add_stmt (ret);
	  फर्काऊ ret;
	}
    }
  यदि (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ NULL_रूख;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  यदि ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (सत्य);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ ret;
}

स्थिर रूख c_parser_omp_taskloop (location_t, c_parser *, वर्ण *,
				   omp_clause_mask, रूख *, तार्किक *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

स्थिर रूख
c_parser_omp_master (location_t loc, c_parser *parser,
		     वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
		     तार्किक *if_p, location_t master_loc)
{
  रूख block, clauses, ret;
  gcc_rich_location richloc (loc);
  यदि (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  म_जोड़ो (p_name, " master");

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      यदि (म_भेद (p, "taskloop") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  यदि (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (सत्य);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, सत्य);
	  यदि (ret == NULL_रूख)
	    फर्काऊ ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  फर्काऊ ret;
	}
    }
  यदि (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ NULL_रूख;
    }

  यदि (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, असत्य);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  अन्यथा
    c_parser_skip_to_pragma_eol (parser);

  फर्काऊ c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

स्थिर रूख
c_parser_omp_masked (location_t loc, c_parser *parser,
		     वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
		     तार्किक *if_p)
{
  रूख block, clauses, ret;

  म_जोड़ो (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      यदि (म_भेद (p, "taskloop") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  यदि (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (सत्य);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, सत्य);
	  यदि (ret == NULL_रूख)
	    फर्काऊ ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  फर्काऊ ret;
	}
    }
  यदि (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ NULL_रूख;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  फर्काऊ c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
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
  रूख clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  रूख stmt = make_गाँठो (OMP_INTEROP);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
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

  यदि (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ असत्य;
    }

  पूर्णाङ्क n = 1;
  यदि (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  यदि (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      अचर वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->मान);

      यदि (!म_भेद ("depend", p) || !म_भेद ("doacross", p))
	{
	  यदि (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, असत्य);
	      फर्काऊ असत्य;
	    }
	  यदि (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, असत्य);
	      फर्काऊ सत्य;
	    }

	  रूख clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_रूख);
	  फर्काऊ असत्य;
	}
    }

  रूख clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  यदि (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_रूख)
    फर्काऊ असत्य;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  फर्काऊ सत्य;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

स्थिर रूख
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  रूख stmt, substmt;
  तार्किक error_suppress = असत्य;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = असत्य;
      फर्काऊ NULL_रूख;
    }

  stmt = थप_stmt_list ();

  यदि (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", सत्य))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_गाँठो, substmt);
      SET_अभिव्यक्ति_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  जबसम्म (1)
    {
      यदि (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	रोक;
      यदि (c_parser_next_token_is (parser, CPP_EOF))
	रोक;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", असत्य);
      यदि (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = असत्य;
	}
      अन्यथा यदि (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = सत्य;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_गाँठो, substmt);
      SET_अभिव्यक्ति_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = झिक_stmt_list (stmt);

  stmt = make_गाँठो (OMP_SECTIONS);
  SET_अभिव्यक्ति_LOCATION (stmt, sections_loc);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OMP_SECTIONS_BODY (stmt) = substmt;

  फर्काऊ add_stmt (stmt);
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

स्थिर रूख
c_parser_omp_sections (location_t loc, c_parser *parser,
		       वर्ण *p_name, omp_clause_mask mask, रूख *cclauses)
{
  रूख block, clauses, ret;

  म_जोड़ो (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  यदि (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (सत्य);
  ret = c_parser_omp_sections_scope (loc, parser);
  यदि (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ ret;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अङ्क_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

स्थिर रूख
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
		       तार्किक *if_p)
{
  रूख stmt, clauses, block;

  म_जोड़ो (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  यदि ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  यदि (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
      यदि (cclauses == रिक्त)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      यदि (!flag_openmp)  /* flag_openmp_simd  */
	फर्काऊ c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      रूख ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      यदि (ret == NULL_रूख)
	फर्काऊ ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      फर्काऊ stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  अन्यथा यदि (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      फर्काऊ NULL_रूख;
    }
  अन्यथा यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      location_t ploc = c_parser_peek_token (parser)->location;
      यदि (cclauses == रिक्त && म_भेद (p, "masked") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  रूख ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  यदि (ret == रिक्त)
	    फर्काऊ ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  यदि (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  फर्काऊ stmt;
	}
      अन्यथा यदि (cclauses == रिक्त && म_भेद (p, "master") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  रूख ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  यदि (ret == रिक्त)
	    फर्काऊ ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  यदि (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  फर्काऊ stmt;
	}
      अन्यथा यदि (म_भेद (p, "loop") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  यदि (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  रूख ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  यदि (ret == NULL_रूख)
	    फर्काऊ ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  फर्काऊ stmt;
	}
      अन्यथा यदि (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  फर्काऊ NULL_रूख;
	}
      अन्यथा यदि (cclauses == रिक्त && म_भेद (p, "sections") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  फर्काऊ stmt;
	}
    }
  अन्यथा यदि (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ NULL_रूख;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = सत्य;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  फर्काऊ stmt;
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

स्थिर रूख
c_parser_omp_single (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख stmt = make_गाँठो (OMP_SINGLE);
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  रूख_TYPE (stmt) = void_type_गाँठो;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  फर्काऊ add_stmt (stmt);
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

स्थिर रूख
c_parser_omp_scope (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख stmt = make_गाँठो (OMP_SCOPE);
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  रूख_TYPE (stmt) = void_type_गाँठो;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  फर्काऊ add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
स्थिर रूख
c_parser_omp_dispatch_body (c_parser *parser)
{
  संरचना c_अभिव्यक्ति lhs, rhs, ret;
  location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, रिक्त, रिक्त);
  यदि (रूख_CODE (lhs.मान) == CALL_अभिव्यक्ति)
    फर्काऊ lhs.मान;

  location_t op_location = c_parser_peek_token (parser)->location;
  यदि (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    फर्काऊ error_mark_गाँठो;

  /* Parse function name.  */
  यदि (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      फर्काऊ error_mark_गाँठो;
    }
  अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
  रूख id = c_parser_peek_token (parser)->मान;
  c_parser_consume_token (parser);
  यदि (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      फर्काऊ error_mark_गाँठो;
    }

  rhs.मान = build_external_ref (अभिव्यक्ति_loc, id, सत्य, &rhs.original_type);
  set_c_अभिव्यक्ति_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, अभिव्यक्ति_LOC_OR_LOC (rhs.मान, अभिव्यक्ति_loc), rhs);
  यदि (रूख_CODE (rhs.मान) != CALL_अभिव्यक्ति)
    {
      error_at (अभिव्यक्ति_LOC_OR_LOC (rhs.मान, अभिव्यक्ति_loc),
		"expected target-function call");
      फर्काऊ error_mark_गाँठो;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, rhs, सत्य, सत्य);
  ret.मान
    = build_modify_अभिव्यक्ति (op_location, lhs.मान, lhs.original_type, NOP_अभिव्यक्ति,
			 अभिव्यक्ति_loc, rhs.मान, rhs.original_type);
  ret.m_decimal = 0;
  set_c_अभिव्यक्ति_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_अभिव्यक्ति;
  ret.original_type = रिक्त;
  फर्काऊ ret.मान;
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

स्थिर रूख
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  रूख stmt = make_गाँठो (OMP_DISPATCH);
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  रूख_TYPE (stmt) = void_type_गाँठो;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  रूख depend_clauses = NULL_रूख;
  रूख *depend_clauses_ptr = &depend_clauses;
  लागि (रूख c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  यदि (depend_clauses != NULL_रूख)
    {
      रूख stmt = make_गाँठो (OMP_TASK);
      रूख_TYPE (stmt) = void_गाँठो;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_रूख;
      SET_अभिव्यक्ति_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  रूख dispatch_body = c_parser_omp_dispatch_body (parser);
  यदि (dispatch_body == error_mark_गाँठो)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      फर्काऊ NULL_रूख;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (रूख_CODE (dispatch_body) == CALL_अभिव्यक्ति
	      || रूख_CODE (dispatch_body) == MODIFY_अभिव्यक्ति);
  रूख *dispatch_call = रूख_CODE (dispatch_body) == MODIFY_अभिव्यक्ति
			  ? &रूख_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  जबसम्म (रूख_CODE (*dispatch_call) == FLOAT_अभिव्यक्ति
	 || रूख_CODE (*dispatch_call) == CONVERT_अभिव्यक्ति
	 || रूख_CODE (*dispatch_call) == NOP_अभिव्यक्ति)
    dispatch_call = &रूख_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_अभिव्यक्ति_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    रूख_TYPE (रूख_TYPE (CALL_अभिव्यक्ति_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  फर्काऊ add_stmt (stmt);
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

स्थिर रूख
c_parser_omp_task (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = सत्य;
  c_parser_statement (parser, if_p);
  फर्काऊ c_finish_omp_task (loc, clauses, block);
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

  रूख clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  यदि (clauses)
    {
      रूख stmt = make_गाँठो (OMP_TASK);
      रूख_TYPE (stmt) = void_गाँठो;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_रूख;
      SET_अभिव्यक्ति_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  अन्यथा
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

स्थिर रूख
c_parser_omp_taskgroup (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  रूख body = c_parser_omp_structured_block (parser, if_p);
  फर्काऊ c_finish_omp_taskgroup (loc, body, clauses);
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
  रूख clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
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
  रूख clauses;
  तार्किक point_seen = असत्य;

  c_parser_consume_pragma (parser);
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = सत्य;
	}
    }
  यदि (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      फर्काऊ असत्य;
    }

  यदि (context != pragma_compound)
    {
      यदि (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      अन्यथा
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ सत्य;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  फर्काऊ सत्य;
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

स्थिर रूख
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
			 तार्किक *if_p)
{
  रूख clauses, block, ret;

  म_जोड़ो (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      तार्किक simd = असत्य;
      तार्किक parallel = असत्य;

      यदि (म_भेद (p, "simd") == 0)
	simd = सत्य;
      अन्यथा
	parallel = म_भेद (p, "parallel") == 0;
      यदि (parallel || simd)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  यदि (cclauses == रिक्त)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      यदि (simd)
		फर्काऊ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      अन्यथा
		फर्काऊ c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (सत्य);
	  यदि (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  अन्यथा
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, सत्य);
	  यदि (ret == रिक्त)
	    फर्काऊ ret;
	  ret = make_गाँठो (OMP_DISTRIBUTE);
	  रूख_TYPE (ret) = void_type_गाँठो;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_अभिव्यक्ति_LOCATION (ret, loc);
	  add_stmt (ret);
	  फर्काऊ ret;
	}
    }
  यदि (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ NULL_रूख;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (सत्य);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, रिक्त,
			       if_p);
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अङ्क_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

स्थिर रूख
c_parser_omp_teams (location_t loc, c_parser *parser,
		    वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
		    तार्किक *if_p)
{
  रूख clauses, block, ret;

  म_जोड़ो (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "distribute") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  यदि (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, सत्य);
	  यदि (ret == रिक्त)
	    फर्काऊ ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_गाँठो (OMP_TEAMS);
	  रूख_TYPE (ret) = void_type_गाँठो;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_अभिव्यक्ति_LOCATION (ret, loc);
	  फर्काऊ add_stmt (ret);
	}
      अन्यथा यदि (म_भेद (p, "loop") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  यदि (cclauses == रिक्त)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, सत्य);
	  यदि (ret == रिक्त)
	    फर्काऊ ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_गाँठो (OMP_TEAMS);
	  रूख_TYPE (ret) = void_type_गाँठो;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_अभिव्यक्ति_LOCATION (ret, loc);
	  फर्काऊ add_stmt (ret);
	}
    }
  यदि (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ NULL_रूख;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  रूख stmt = make_गाँठो (OMP_TEAMS);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, सत्य);
  SET_अभिव्यक्ति_LOCATION (stmt, loc);

  फर्काऊ add_stmt (stmt);
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

स्थिर रूख
c_parser_omp_target_data (location_t loc, c_parser *parser, तार्किक *if_p)
{
  यदि (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  रूख clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", असत्य);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, असत्य);
  पूर्णाङ्क map_seen = 0;
  लागि (रूख *pc = &clauses; *pc;)
    {
      यदि (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
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
	    रोक;
	  पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	  पक्ष GOMP_MAP_ALWAYS_POINTER:
	  पक्ष GOMP_MAP_ATTACH_DETACH:
	  पक्ष GOMP_MAP_ATTACH:
	    रोक;
	  स्वभाव:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    जारी;
	  }
      अन्यथा यदि (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  यदि (map_seen != 3)
    {
      यदि (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      फर्काऊ NULL_रूख;
    }

  रूख stmt = make_गाँठो (OMP_TARGET_DATA);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  रूख block = c_begin_compound_stmt (सत्य);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, सत्य);

  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  फर्काऊ add_stmt (stmt);
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
  यदि (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ सत्य;
    }

  रूख clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ असत्य);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  यदि (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_रूख
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_रूख)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      फर्काऊ असत्य;
    }

  यदि (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  रूख stmt = make_गाँठो (OMP_TARGET_UPDATE);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  add_stmt (stmt);
  फर्काऊ असत्य;
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
  तार्किक data_seen = असत्य;
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = सत्य;
	}
    }
  यदि (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      फर्काऊ असत्य;
    }

  यदि (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ सत्य;
    }

  यदि (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  रूख clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", असत्य);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, असत्य);
  पूर्णाङ्क map_seen = 0;
  लागि (रूख *pc = &clauses; *pc;)
    {
      यदि (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	विकल्प (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  पक्ष GOMP_MAP_TO:
	  पक्ष GOMP_MAP_ALWAYS_TO:
	  पक्ष GOMP_MAP_PRESENT_TO:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TO:
	  पक्ष GOMP_MAP_ALLOC:
	  पक्ष GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	  पक्ष GOMP_MAP_ALWAYS_POINTER:
	  पक्ष GOMP_MAP_ATTACH_DETACH:
	  पक्ष GOMP_MAP_ATTACH:
	    रोक;
	  स्वभाव:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    जारी;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  यदि (map_seen != 3)
    {
      यदि (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      फर्काऊ सत्य;
    }

  रूख stmt = make_गाँठो (OMP_TARGET_ENTER_DATA);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  add_stmt (stmt);
  फर्काऊ सत्य;
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
  तार्किक data_seen = असत्य;
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = सत्य;
	}
    }
  यदि (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      फर्काऊ असत्य;
    }

  यदि (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ सत्य;
    }

  यदि (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  रूख clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", असत्य);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, असत्य);
  पूर्णाङ्क map_seen = 0;
  लागि (रूख *pc = &clauses; *pc;)
    {
      यदि (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	विकल्प (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  पक्ष GOMP_MAP_FROM:
	  पक्ष GOMP_MAP_ALWAYS_FROM:
	  पक्ष GOMP_MAP_PRESENT_FROM:
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_FROM:
	  पक्ष GOMP_MAP_RELEASE:
	  पक्ष GOMP_MAP_DELETE:
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    रोक;
	  पक्ष GOMP_MAP_FIRSTPRIVATE_POINTER:
	  पक्ष GOMP_MAP_ALWAYS_POINTER:
	  पक्ष GOMP_MAP_ATTACH_DETACH:
	  पक्ष GOMP_MAP_DETACH:
	    रोक;
	  स्वभाव:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    जारी;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  यदि (map_seen != 3)
    {
      यदि (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      फर्काऊ सत्य;
    }

  रूख stmt = make_गाँठो (OMP_TARGET_EXIT_DATA);
  रूख_TYPE (stmt) = void_type_गाँठो;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  add_stmt (stmt);
  फर्काऊ सत्य;
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
  रूख *pc = रिक्त, stmt, block, body, clauses;

  यदि (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      फर्काऊ असत्य;
    }

  यदि (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      गणना रूख_code ccode = ERROR_MARK;

      यदि (म_भेद (p, "teams") == 0)
	ccode = OMP_TEAMS;
      अन्यथा यदि (म_भेद (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      अन्यथा यदि (म_भेद (p, "simd") == 0)
	ccode = OMP_SIMD;
      यदि (ccode != ERROR_MARK)
	{
	  रूख cclauses[C_OMP_CLAUSE_SPLIT_गन्ती];
	  वर्ण p_name[परिमाण ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  म_नकल (p_name, "#pragma omp target");
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      रूख stmt;
	      विकल्प (ccode)
		{
		पक्ष OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  रोक;
		पक्ष OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  रोक;
		पक्ष OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  रोक;
		स्वभाव:
		  gcc_unreachable ();
		}
	      फर्काऊ stmt != NULL_रूख;
	    }
	  keep_next_level ();
	  रूख block = c_begin_compound_stmt (सत्य), ret;
	  विकल्प (ccode)
	    {
	    पक्ष OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      रोक;
	    पक्ष OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      रोक;
	    पक्ष OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      रोक;
	    स्वभाव:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, सत्य);
	  यदि (ret == NULL_रूख)
	    फर्काऊ असत्य;
	  यदि (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    लागि (रूख c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_अङ्क_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		लागि (पूर्णाङ्क i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_अङ्क_TEAMS); ++i)
		  यदि (OMP_CLAUSE_OPERAND (c, i)
		      && रूख_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      रूख अभिव्यक्ति = OMP_CLAUSE_OPERAND (c, i);
		      रूख tmp = create_tmp_var_raw (रूख_TYPE (अभिव्यक्ति));
		      अभिव्यक्ति = build4 (TARGET_अभिव्यक्ति, रूख_TYPE (अभिव्यक्ति), tmp,
				     अभिव्यक्ति, NULL_रूख, NULL_रूख);
		      add_stmt (अभिव्यक्ति);
		      OMP_CLAUSE_OPERAND (c, i) = अभिव्यक्ति;
		      रूख tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  रूख stmt = make_गाँठो (OMP_TARGET);
	  रूख_TYPE (stmt) = void_type_गाँठो;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), सत्य);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_अभिव्यक्ति_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  गच्छ check_clauses;
	}
      अन्यथा यदि (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  फर्काऊ असत्य;
	}
      अन्यथा यदि (म_भेद (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  फर्काऊ सत्य;
	}
      अन्यथा यदि (म_भेद (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  फर्काऊ c_parser_omp_target_enter_data (loc, parser, context);
	}
      अन्यथा यदि (म_भेद (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  फर्काऊ c_parser_omp_target_exit_data (loc, parser, context);
	}
      अन्यथा यदि (म_भेद (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  फर्काऊ c_parser_omp_target_update (loc, parser, context);
	}
    }
  यदि (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ असत्य;
    }

  stmt = make_गाँठो (OMP_TARGET);
  रूख_TYPE (stmt) = void_type_गाँठो;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", असत्य);
  लागि (रूख c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	रूख nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, सत्य);

  keep_next_level ();
  block = c_begin_compound_stmt (सत्य);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, सत्य);

  SET_अभिव्यक्ति_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  जबसम्म (*pc)
    {
      यदि (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
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
	    रोक;
	  स्वभाव:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    जारी;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = सत्य;
  फर्काऊ सत्य;
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
  रूख kind = token->मान;
  gcc_assert (म_भेद (IDENTIFIER_POINTER (kind), "simd") == 0
	      || म_भेद (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      यदि (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  फर्काऊ;
	}
      clauses.safe_थप (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_थप (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  जबसम्म (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      यदि (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->मान != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  फर्काऊ;
	}
      c_parser_consume_pragma (parser);
      जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  यदि (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      फर्काऊ;
	    }
	  clauses.safe_थप (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_थप (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  स_रखो (&eof_token, 0, परिमाण (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_थप (eof_token);
  clauses.safe_थप (eof_token);

  विकल्प (context)
    {
    पक्ष pragma_external:
      यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णाङ्क ext = disable_extension_diagnostics ();
	  गर
	    c_parser_consume_token (parser);
	  जबसम्म (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, असत्य, सत्य,
					 असत्य, रिक्त, &clauses);
	  restore_extension_diagnostics (ext);
	}
      अन्यथा
	c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, असत्य, सत्य,
				       असत्य, रिक्त, &clauses);
      रोक;
    पक्ष pragma_struct:
    पक्ष pragma_param:
    पक्ष pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      रोक;
    पक्ष pragma_compound:
      तार्किक have_std_attrs;
      रूख std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      यदि (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      अन्यथा
	std_attrs = NULL_रूख;
      यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णाङ्क ext = disable_extension_diagnostics ();
	  गर
	    c_parser_consume_token (parser);
	  जबसम्म (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  यदि (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, सत्य,
					     सत्य, असत्य, रिक्त, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      रोक;
	    }
	  restore_extension_diagnostics (ext);
	}
      अन्यथा यदि (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, सत्य, सत्य, सत्य, सत्य, सत्य,
					 असत्य, रिक्त, &clauses, have_std_attrs,
					 std_attrs);
	  रोक;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      रोक;
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

स्थिर रूख
c_parser_omp_context_selector (c_parser *parser, गणना omp_tss_code set,
			       रूख parms)
{
  रूख ret = NULL_रूख;
  गर
    {
      रूख selector;
      यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->मान;
      अन्यथा
	{
	  c_parser_error (parser, "expected trait selector name");
	  फर्काऊ error_mark_गाँठो;
	}
      गणना omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      यदि (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_रूख, NULL_रूख, ret);
	  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  अन्यथा
	    रोक;
	}

      c_parser_consume_token (parser);

      रूख properties = NULL_रूख;
      रूख scoreval = NULL_रूख;
      गणना omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      तार्किक allow_score = omp_ts_map[sel].allow_score;
      रूख t;

      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  यदि (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      फर्काऊ error_mark_गाँठो;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_NAME)
	      && म_भेद (IDENTIFIER_POINTER (token->मान), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      रूख score = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त).मान;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      यदि (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      अन्यथा यदि (score != error_mark_गाँठो)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, असत्य, रिक्त);
		  यदि (!INTEGRAL_TYPE_P (रूख_TYPE (score))
		      || रूख_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  अन्यथा यदि (रूख_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  अन्यथा
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  विकल्प (property_kind)
	    {
	    पक्ष OMP_TRAIT_PROPERTY_ID:
	      यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  रूख prop = c_parser_peek_token (parser)->मान;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_रूख,
						    properties);
		}
	      अन्यथा
		{
		  c_parser_error (parser, "expected identifier");
		  फर्काऊ error_mark_गाँठो;
		}
	      रोक;
	    पक्ष OMP_TRAIT_PROPERTY_NAME_LIST:
	      गर
		{
		  रूख prop = OMP_TP_NAMELIST_गाँठो;
		  रूख मान = NULL_रूख;
		  यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      मान = c_parser_peek_token (parser)->मान;
		      c_parser_consume_token (parser);
		    }
		  अन्यथा यदि (c_parser_next_token_is (parser, CPP_STRING))
		    मान = c_parser_string_literal (parser, असत्य,
						     असत्य).मान;
		  अन्यथा
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      फर्काऊ error_mark_गाँठो;
		    }

		  properties = make_trait_property (prop, मान, properties);

		  यदि (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  अन्यथा
		    रोक;
		}
	      जबसम्म (1);
	      रोक;
	    पक्ष OMP_TRAIT_PROPERTY_DEV_अङ्क_अभिव्यक्ति:
	    पक्ष OMP_TRAIT_PROPERTY_BOOL_अभिव्यक्ति:
	      {
		c_अभिव्यक्ति texpr = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  सत्य, सत्य);
		t = texpr.मान;
	      }
	      यदि (t == error_mark_गाँठो)
		फर्काऊ error_mark_गाँठो;
	      mark_exp_read (t);
	      यदि (property_kind == OMP_TRAIT_PROPERTY_BOOL_अभिव्यक्ति)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_गाँठो);
		  यदि (t == error_mark_गाँठो)
		    फर्काऊ error_mark_गाँठो;
		}
	      अन्यथा यदि (!INTEGRAL_TYPE_P (रूख_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  फर्काऊ error_mark_गाँठो;
		}
	      t = c_fully_fold (t, असत्य, रिक्त);
	      properties = make_trait_property (NULL_रूख, t, properties);
	      रोक;
	    पक्ष OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      यदि (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  यदि (parms == NULL_रूख)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      फर्काऊ error_mark_गाँठो;
		    }
		  रूख c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", सत्य, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_गाँठो
							     ? NULL_रूख : parms,
							     c);
		  properties = c;
		}
	      अन्यथा यदि (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  फर्काऊ error_mark_गाँठो;
		}
	      अन्यथा
		gcc_unreachable ();
	      रोक;
	    स्वभाव:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      अन्यथा यदि (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  फर्काऊ error_mark_गाँठो;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
    }
  जबसम्म (1);

  फर्काऊ nreverse (ret);
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

स्थिर रूख
c_parser_omp_context_selector_specification (c_parser *parser, रूख parms)
{
  रूख ret = NULL_रूख;
  गर
    {
      अचर वर्ण *setp = "";
      यदि (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      गणना omp_tss_code set = omp_lookup_tss_code (setp);

      यदि (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  फर्काऊ error_mark_गाँठो;
	}

      c_parser_consume_token (parser);

      यदि (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	फर्काऊ error_mark_गाँठो;

      matching_braces braces;
      यदि (!braces.require_open (parser))
	फर्काऊ error_mark_गाँठो;

      रूख selectors = c_parser_omp_context_selector (parser, set, parms);
      यदि (selectors == error_mark_गाँठो)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_गाँठो;
	}
      अन्यथा यदि (ret != error_mark_गाँठो)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	रोक;
    }
  जबसम्म (1);

  यदि (ret == error_mark_गाँठो)
    फर्काऊ ret;
  फर्काऊ nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

स्थिर शून्य
c_finish_omp_declare_variant (c_parser *parser, रूख fndecl, रूख parms)
{
  matching_parens parens;
  यदि (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ;
    }

  यदि (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      गच्छ fail;
    }

  c_token *token = c_parser_peek_token (parser);
  रूख variant = lookup_name (token->मान);

  यदि (variant == NULL_रूख)
    {
      undeclared_variable (token->location, token->मान);
      variant = error_mark_गाँठो;
    }
  अन्यथा यदि (रूख_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_गाँठो;
    }
  अन्यथा यदि (fndecl_built_in_p (variant)
	   && (म_भेदन (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", म_माप ("__builtin_")) == 0
	       || म_भेदन (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", म_माप ("__sync_")) == 0
	       || म_भेदन (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", म_माप ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_गाँठो;
    }
  अन्यथा यदि (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_गाँठो;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  रूख append_args_रूख = NULL_रूख;
  रूख append_args_last;
  vec<रूख> adjust_args_list = vNULL;
  तार्किक has_match = असत्य, has_adjust_args = असत्य;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  रूख need_device_ptr_list = NULL_रूख;
  रूख ctx = error_mark_गाँठो;

  गर
    {
      यदि (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      अचर वर्ण *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      यदि (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      गणना clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      यदि (म_भेद (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      अन्यथा यदि (म_भेद (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      अन्यथा यदि (म_भेद (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  गच्छ fail;
	}

      c_parser_consume_token (parser);

      यदि (!parens.require_open (parser))
	गच्छ fail;

      यदि (parms == NULL_रूख)
	parms = error_mark_गाँठो;

      यदि (ccode == match)
	{
	  यदि (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = सत्य;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  यदि (ctx == error_mark_गाँठो)
	    गच्छ fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  यदि (ctx != error_mark_गाँठो
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      रूख outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      अन्यथा यदि (ccode == adjust_args)
	{
	  has_adjust_args = सत्य;
	  यदि (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      अचर वर्ण *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	      यदि (म_भेद (p, "need_device_ptr") == 0
		  || म_भेद (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  रूख list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_रूख);

		  रूख arg;
		  यदि (variant != error_mark_गाँठो)
		    लागि (रूख c = list; c != NULL_रूख; c = रूख_CHAIN (c))
		      {
			रूख decl = रूख_PURPOSE (c);
			location_t arg_loc = अभिव्यक्ति_LOCATION (रूख_मान (c));
			पूर्णाङ्क idx;
			लागि (arg = parms, idx = 0; arg != रिक्त;
			     arg = रूख_CHAIN (arg), idx++)
			  यदि (arg == decl)
			    रोक;
			यदि (arg == NULL_रूख)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    गच्छ fail;
			  }
			यदि (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    गच्छ fail;
			  }
			यदि (म_भेद (p, "need_device_ptr") == 0
			    && रूख_CODE (रूख_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    गच्छ fail;
			  }
			adjust_args_list.safe_थप (arg);
			यदि (म_भेद (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_रूख_list (
				NULL_रूख,
				build_int_cst (
				  integer_type_गाँठो,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      अन्यथा
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  यदि (म_भेद (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  गच्छ fail;
		}
	    }
	  अन्यथा
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      गच्छ fail;
	    }
	}
      अन्यथा यदि (ccode == append_args)
	{
	  यदि (append_args_रूख)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_रूख = NULL_रूख;
	    }
	  गर
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      यदि (!c_parser_next_token_is (parser, CPP_NAME)
		  || म_भेद ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->मान)))
		{
		  error_at (loc, "expected %<interop%>");
		  गच्छ fail;
		}
	      c_parser_consume_token (parser);

	      यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		गच्छ fail;
	      तार्किक target = असत्य;
	      तार्किक targetsync = असत्य;
	      रूख prefer_type_रूख = NULL_रूख;
	      यदि (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_रूख)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		गच्छ fail;
	      यदि (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      रूख t = build_रूख_list (target ? boolean_true_गाँठो
					       : boolean_false_गाँठो,
					targetsync ? boolean_true_गाँठो
						   : boolean_false_गाँठो);
	      t = build1_loc (loc, NOP_अभिव्यक्ति, void_type_गाँठो, t);
	      t = build_रूख_list (t, prefer_type_रूख);
	      यदि (append_args_रूख)
		{
		  रूख_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      अन्यथा
		append_args_रूख = append_args_last = t;
	      यदि (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		रोक;
	      यदि (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		गच्छ fail;
	    }
	  जबसम्म (सत्य);
	}

      parens.require_close (parser);
  } जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  यदि (variant != error_mark_गाँठो && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_गाँठो;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  यदि (variant == error_mark_गाँठो || ctx == error_mark_गाँठो)
    /* Previously diagnosed error.  */
    फर्काऊ;

  यदि ((has_adjust_args || append_args_रूख)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      फर्काऊ;
    }

  यदि (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      रूख base_type = रूख_TYPE (fndecl);
      रूख variant_type = रूख_TYPE (variant);
      तार्किक unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_रूख
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      यदि (append_args_रूख
	  && TYPE_ARG_TYPES (base_type) == NULL_रूख
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
	  फर्काऊ;
	}
      अन्यथा यदि (append_args_रूख)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  पूर्णाङ्क nappend_args = 0;
	  पूर्णाङ्क nbase_args = 0;
	  लागि (रूख t = TYPE_ARG_TYPES (base_type);
	       t && रूख_मान (t) != void_type_गाँठो; t = रूख_CHAIN (t))
	    nbase_args++;
	  लागि (रूख t = append_args_रूख; t; t = रूख_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_रूख = build_रूख_list (build_int_cst (integer_type_गाँठो,
							     nbase_args),
					      append_args_रूख);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  यदि (!unprototyped_variant)
	    {
	      रूख args = TYPE_ARG_TYPES (variant_type);
	      लागि (पूर्णाङ्क i = 0; args && i < nbase_args;
		   i++, args = रूख_CHAIN (args))
		;
	      लागि (पूर्णाङ्क i = 0; i < nappend_args; i++, args = रूख_CHAIN (args))
		यदि (!args || !c_omp_interop_t_p (रूख_मान (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    फर्काऊ;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  रूख args = TYPE_ARG_TYPES (base_type);
	  रूख newargs = NULL_रूख;
	  रूख lastarg = NULL_रूख;
	  लागि (पूर्णाङ्क j = 0; j < nbase_args; j++, args = रूख_CHAIN (args))
	    {
	      रूख t = रूख_cons (रूख_PURPOSE (args),
				  रूख_मान (args), NULL_रूख);
	      यदि (lastarg)
		रूख_CHAIN (lastarg) = t;
	      अन्यथा
		newargs = t;
	      lastarg = t;
	    }
	  रूख type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? रूख_TYPE (type) : pointer_sized_int_गाँठो;
	  लागि (पूर्णाङ्क j = 0; j < nappend_args; j++)
	    {
	      रूख t = रूख_cons (NULL_रूख, type, NULL_रूख);
	      यदि (lastarg)
		रूख_CHAIN (lastarg) = t;
	      अन्यथा
		newargs = t;
	      lastarg = t;
	    }
	  रूख_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  रूख saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  तार्किक fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  यदि (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      फर्काऊ;
	    }
	  अन्यथा यदि (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      अन्यथा  /* No append_args present.  */
	{
	  यदि (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      फर्काऊ;
	    }
	  अन्यथा यदि (TYPE_ARG_TYPES (variant_type) == NULL_रूख
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_रूख)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  रूख construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  यदि (omp_context_selector_matches (ctx, NULL_रूख, असत्य))
    {
      रूख attr = रूख_cons (get_identifier ("omp declare variant base"),
			     build_रूख_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  यदि (need_device_ptr_list || append_args_रूख)
    {
      रूख variant_decl = रूख_strip_nop_conversions (variant);
      रूख t = build_रूख_list (need_device_ptr_list,
				NULL_रूख /* need_device_addr */);
      रूख_CHAIN (t) = append_args_रूख;
      DECL_ATTRIBUTES (variant_decl)
	= रूख_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

स्थिर शून्य
c_finish_omp_declare_simd (c_parser *parser, रूख fndecl, रूख parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  यदि (clauses.exists () && clauses[0].type == CPP_EOF)
    फर्काऊ;
  अचर वर्ण *kind = "simd";
  यदि (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].मान);
  gcc_assert (म_भेद (kind, "simd") == 0 || म_भेद (kind, "variant") == 0);
  यदि (fndecl == NULL_रूख || रूख_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      फर्काऊ;
    }
  यदि (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      फर्काऊ;
    }
  यदि (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      फर्काऊ;
    }

  यदि (parms == NULL_रूख)
    parms = DECL_ARGUMENTS (fndecl);

  अचिन्हित पूर्णाङ्क tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  जबसम्म (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->मान);
      c_parser_consume_token (parser);
      parser->in_pragma = सत्य;

      यदि (म_भेद (kind, "simd") == 0)
	{
	  रूख c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  यदि (c != NULL_रूख)
	    c = रूख_cons (NULL_रूख, c, NULL_रूख);
	  c = build_रूख_list (get_identifier ("omp declare simd"), c);
	  रूख_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      अन्यथा
	{
	  gcc_assert (म_भेद (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  यदि (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#यदि !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#अथवायदि !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#अन्यथा
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
स्थिर रूख
omp_start_variant_function (c_declarator *declarator, रूख ctx)
{
  c_declarator *id = declarator;
  जबसम्म (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  रूख name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  फर्काऊ name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
स्थिर शून्य
omp_finish_variant_function (रूख decl, रूख base_name, रूख ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  रूख base_decl = lookup_name (base_name);
  यदि (base_decl == error_mark_गाँठो)
    base_decl = NULL_रूख;
  यदि (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      फर्काऊ;
    }

  यदि (!comptypes (रूख_TYPE (decl), रूख_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      फर्काऊ;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  रूख construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  रूख attrs = DECL_ATTRIBUTES (base_decl);
  रूख match_loc_गाँठो
    = maybe_wrap_with_location (integer_zero_गाँठो,
				DECL_SOURCE_LOCATION (base_decl));
  रूख loc_गाँठो = रूख_cons (match_loc_गाँठो, integer_zero_गाँठो,
			     build_रूख_list (match_loc_गाँठो,
					      integer_zero_गाँठो));
  attrs = रूख_cons (get_identifier ("omp declare variant base"),
		     रूख_cons (decl, ctx, loc_गाँठो), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  रूख_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

तार्किक
c_maybe_parse_omp_decl (रूख decl, रूख d)
{
  gcc_assert (रूख_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  अचर वर्ण *directive[3] = {};
  लागि (पूर्णाङ्क j = 0; j < 3; j++)
    {
      रूख id = NULL_रूख;
      यदि (first + j == last)
	रोक;
      यदि (first[j].type == CPP_NAME)
	id = first[j].मान;
      अन्यथा यदि (first[j].type == CPP_KEYWORD)
	id = ridpointers[(पूर्णाङ्क) first[j].keyword];
      अन्यथा
	रोक;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  अचर c_omp_directive *dir = रिक्त;
  यदि (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  यदि (dir == रिक्त)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      फर्काऊ असत्य;
    }
  यदि (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || म_भेद (directive[1], "target") != 0))
    फर्काऊ असत्य;

  यदि (!flag_openmp && !dir->simd)
    फर्काऊ सत्य;

  c_parser *parser = the_parser;
  अचिन्हित पूर्णाङ्क tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = रिक्त;
  vec_safe_reserve (toks, last - first + 2, सत्य);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_थप (tok);
  जबसम्म (++first < last)
    toks->quick_थप (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_थप (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_थप (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, रिक्त, NULL_रूख);
  parser->in_omp_decl_attribute = NULL_रूख;
  फर्काऊ सत्य;
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
  रूख clauses = NULL_रूख;
  पूर्णाङ्क device_type = 0;
  तार्किक indirect = असत्य;
  तार्किक only_device_type_or_indirect = सत्य;
  यदि (flag_openmp)
    omp_requires_mask
      = (गणना omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  यदि (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  अन्यथा यदि (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  अन्यथा
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_थप (current_omp_declare_target_attribute, attr);
      फर्काऊ;
    }
  लागि (रूख c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_अभिव्यक्ति (c));
    }
  लागि (रूख c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	जारी;
      रूख t = OMP_CLAUSE_DECL (c), id;
      रूख at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      रूख at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = असत्य;
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      अन्यथा
	id = get_identifier ("omp declare target");
      यदि (at2)
	{
	  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  अन्यथा यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || मान_member (get_identifier ("local"), रूख_मान (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  अन्यथा
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  जारी;
	}
      यदि (!at1)
	{
	  DECL_ATTRIBUTES (t) = रूख_cons (id, NULL_रूख, DECL_ATTRIBUTES (t));
	  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    रूख_मान (DECL_ATTRIBUTES (t))
	      = रूख_cons (NULL_रूख, get_identifier ("local"),
			   रूख_मान (DECL_ATTRIBUTES (t)));

	  यदि (रूख_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    जारी;

	  symtab_गाँठो *गाँठो = symtab_गाँठो::get (t);
	  यदि (गाँठो != रिक्त)
	    {
	      गाँठो->offloadable = 1;
	      यदि (ENABLE_OFFLOADING)
		{
		  g->have_offload = सत्य;
		  यदि (is_a <varpool_गाँठो *> (गाँठो)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_थप (offload_vars, t);
		}
	    }
	}
      अन्यथा
	{
	  तार्किक saw_local = मान_member (get_identifier ("local"),
					 रूख_मान (at1));
	  यदि (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      जारी;
	    }
	  अन्यथा यदि (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      जारी;
	    }
	}
      यदि (रूख_CODE (t) != FUNCTION_DECL)
	जारी;
      यदि ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  रूख at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  यदि (at3 == NULL_रूख)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= रूख_cons (id, NULL_रूख, DECL_ATTRIBUTES (t));
	    }
	}
      यदि ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  रूख at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  यदि (at3 == NULL_रूख)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= रूख_cons (id, NULL_रूख, DECL_ATTRIBUTES (t));
	    }
	}
      यदि (indirect)
	{
	  रूख at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  यदि (at4 == NULL_रूख)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= रूख_cons (id, NULL_रूख, DECL_ATTRIBUTES (t));
	    }
	}
    }
  यदि ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  यदि (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
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
  अचर वर्ण *p = "";
  c_parser_consume_pragma (parser);
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
  यदि (म_भेद (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      यदि (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
	  रूख clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  पूर्णाङ्क device_type = 0;
	  पूर्णाङ्क indirect = 0;
	  लागि (रूख c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_अभिव्यक्ति (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_थप (current_omp_declare_target_attribute, attr);
	}
      अन्यथा यदि (म_भेद (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  अचर वर्ण *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      रूख id = c_parser_peek_token (parser)->मान;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  यदि (म_भेद (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      फर्काऊ;
	    }

	  c_parser_consume_token (parser);

	  यदि (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, असत्य);
	      फर्काऊ;
	    }

	  रूख ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_रूख);
	  यदि (ctx != error_mark_गाँठो)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  यदि (ctx != error_mark_गाँठो
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      रूख outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  यदि (ctx == error_mark_गाँठो
	      || !omp_context_selector_matches (ctx, NULL_रूख, असत्य, सत्य))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, असत्य);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      फर्काऊ;
	    }
	  अन्यथा
	    {
	      तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_थप (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	}
    }
  अन्यथा यदि (म_भेद (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
      c_parser_omp_assumption_clauses (parser, असत्य);
      संरचना c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_थप (current_omp_begin_assumes, a);
    }
  अन्यथा
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
  अचर वर्ण *p = "";
  c_parser_consume_pragma (parser);
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
  यदि (म_भेद (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      यदि (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
	  c_parser_skip_to_pragma_eol (parser);
	  यदि (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  अन्यथा
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->झिक ();
	      यदि (a.attr_syntax != attr_syntax)
		{
		  यदि (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  अन्यथा
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      अन्यथा यदि (म_भेद (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
	  c_parser_skip_to_pragma_eol (parser);
	  यदि (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  अन्यथा
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->झिक ();
	      यदि (a.attr_syntax != attr_syntax)
		{
		  यदि (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  अन्यथा
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  फर्काऊ;
	}
    }
  अन्यथा यदि (म_भेद (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      तार्किक attr_syntax = parser->in_omp_attribute_pragma != रिक्त;
      c_parser_skip_to_pragma_eol (parser);
      यदि (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      अन्यथा
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->झिक ();
	  यदि (a.attr_syntax != attr_syntax)
	    {
	      यदि (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      अन्यथा
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  अन्यथा
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
  रूख type, mapper_name = NULL_रूख, var = NULL_रूख, stmt, stmtlist;
  रूख maplist = NULL_रूख, mapper_id, mapper_decl, t;
  c_token *token;

  यदि (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      गच्छ fail;
    }

  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    गच्छ fail;

  token = c_parser_peek_token (parser);

  यदि (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      विकल्प (token->type)
	{
	पक्ष CPP_NAME:
	  mapper_name = token->मान;
	  c_parser_consume_token (parser);
	  रोक;
	पक्ष CPP_KEYWORD:
	  यदि (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_रूख;
	      c_parser_consume_token (parser);
	      रोक;
	    }
	  /* Fallthrough.  */
	स्वभाव:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  फर्काऊ;
	}

      यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	गच्छ fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    संरचना c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, रिक्त, रिक्त);
    यदि (type == error_mark_गाँठो)
      गच्छ fail;
    यदि (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, असत्य);
	फर्काऊ;
      }
    लागि (रूख t = DECL_INITIAL (mapper_decl); t; t = रूख_CHAIN (t))
      यदि (comptypes (रूख_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + परिमाण ("omp declare mapper ") - 1,
		    type);
	  रूख prevmapper = रूख_मान (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  फर्काऊ;
	}
  }

  token = c_parser_peek_token (parser);
  यदि (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->मान, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  अन्यथा
    {
      error_at (token->location, "expected identifier");
      गच्छ fail;
    }

  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    गच्छ fail;

  थप_scope ();
  stmtlist = थप_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      यदि (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  गच्छ fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, सत्य);
    }

  यदि (maplist == NULL_रूख)
    {
      error_at (आगत_location, "missing %<map%> clause");
      गच्छ fail;
    }
  रूख list;
  लागि (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      रूख dvar = OMP_CLAUSE_DECL (list);
      जबसम्म (!DECL_P (dvar) && रूख_OPERAND_LENGTH (dvar))
	dvar = रूख_OPERAND (dvar, 0);
      यदि (dvar == var)
	रोक;
    }
  यदि (!list)
    error_at (आगत_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_गाँठो (OMP_DECLARE_MAPPER);
  रूख_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  झिक_stmt_list (stmtlist);
  झिक_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = रूख_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  फर्काऊ;

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
  अचिन्हित पूर्णाङ्क tokens_avail = 0, i;
  c_token *saved_tokens = रिक्त;
  vec<रूख> types = vNULL;
  vec<c_token> clauses = vNULL;
  गणना रूख_code reduc_code = ERROR_MARK;
  रूख reduc_id = NULL_रूख;
  रूख type;
  location_t rloc = c_parser_peek_token (parser)->location;

  यदि (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      गच्छ fail;
    }

  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    गच्छ fail;

  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_PLUS:
      reduc_code = PLUS_अभिव्यक्ति;
      रोक;
    पक्ष CPP_MULT:
      reduc_code = MULT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_MINUS:
      reduc_code = MINUS_अभिव्यक्ति;
      रोक;
    पक्ष CPP_AND:
      reduc_code = BIT_AND_अभिव्यक्ति;
      रोक;
    पक्ष CPP_XOR:
      reduc_code = BIT_XOR_अभिव्यक्ति;
      रोक;
    पक्ष CPP_OR:
      reduc_code = BIT_IOR_अभिव्यक्ति;
      रोक;
    पक्ष CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_अभिव्यक्ति;
      रोक;
    पक्ष CPP_OR_OR:
      reduc_code = TRUTH_ORIF_अभिव्यक्ति;
      रोक;
    पक्ष CPP_NAME:
      अचर वर्ण *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "min") == 0)
	{
	  reduc_code = MIN_अभिव्यक्ति;
	  रोक;
	}
      यदि (म_भेद (p, "max") == 0)
	{
	  reduc_code = MAX_अभिव्यक्ति;
	  रोक;
	}
      reduc_id = c_parser_peek_token (parser)->मान;
      रोक;
    स्वभाव:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      गच्छ fail;
    }

  रूख orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    गच्छ fail;

  जबसम्म (सत्य)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      संरचना c_type_name *ctype = c_parser_type_name (parser);
      यदि (ctype != रिक्त)
	{
	  type = groktypename (ctype, रिक्त, रिक्त);
	  यदि (type == error_mark_गाँठो)
	    ;
	  अन्यथा यदि ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || रूख_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_रूख)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  अन्यथा यदि (रूख_CODE (type) == FUNCTION_TYPE
		   || रूख_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  अन्यथा यदि (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  अन्यथा यदि (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  अन्यथा
	    {
	      रूख t;
	      लागि (t = DECL_INITIAL (reduc_decl); t; t = रूख_CHAIN (t))
		यदि (comptypes (रूख_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + परिमाण ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (रूख_VEC_ELT (रूख_मान (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    रोक;
		  }
	      यदि (t == NULL_रूख)
		types.safe_थप (type);
	    }
	  यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    रोक;
	}
      अन्यथा
	रोक;
    }

  यदि (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      जबसम्म (सत्य)
	{
	  c_token *token = c_parser_peek_token (parser);
	  यदि (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    रोक;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      फर्काऊ;
    }

  यदि (types.length () > 1)
    {
      जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  यदि (token->type == CPP_EOF)
	    गच्छ fail;
	  clauses.safe_थप (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_थप (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      स_रखो (&eof_token, 0, परिमाण (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_थप (eof_token);
      clauses.safe_थप (eof_token);
    }

  पूर्णाङ्क errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      यदि (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = सत्य;
	}

      तार्किक nested = current_function_decl != NULL_रूख;
      यदि (nested)
	c_थप_function_context ();
      रूख fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, सत्य);
      थप_scope ();
      रूख stmt = थप_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      रूख omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      रूख omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      संरचना c_अभिव्यक्ति combiner = c_parser_expression (parser);
      संरचना c_अभिव्यक्ति initializer;
      रूख omp_priv = NULL_रूख, omp_orig = NULL_रूख;
      तार्किक bad = असत्य;
      initializer.set_error ();
      यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = सत्य;
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      यदि (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && म_भेद (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->मान),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  झिक_scope ();
	  थप_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_गाँठो;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = सत्य;
	  अन्यथा यदि (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = सत्य;
	    }
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->मान),
			   "omp_priv") != 0)
	    {
	      यदि (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = सत्य;
		}
	      अन्यथा
		initializer = c_parser_postfix_expression (parser);
	      यदि (initializer.मान
		  && रूख_CODE (initializer.मान) == CALL_अभिव्यक्ति)
		{
		  पूर्णाङ्क j;
		  रूख c = initializer.मान;
		  लागि (j = 0; j < call_अभिव्यक्ति_nargs (c); j++)
		    {
		      रूख a = CALL_अभिव्यक्ति_ARG (c, j);
		      STRIP_NOPS (a);
		      यदि (रूख_CODE (a) == ADDR_अभिव्यक्ति
			  && रूख_OPERAND (a, 0) == omp_priv)
			रोक;
		    }
		  यदि (j == call_अभिव्यक्ति_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  अन्यथा
	    {
	      c_parser_consume_token (parser);
	      यदि (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = सत्य;
	      अन्यथा
		{
		  रूख st = थप_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पङ्क्ति_table, loc);
		  start_init (omp_priv, NULL_रूख, असत्य, असत्य, &richloc);
		  संरचना c_अभिव्यक्ति init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.मान,
		      	       init.original_type, NULL_रूख);
		  झिक_stmt_list (st);
		}
	    }
	  यदि (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = सत्य;
	}

      यदि (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  रूख t = रूख_cons (type, make_रूख_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  रूख_VEC_ELT (रूख_मान (t), 0) = omp_out;
	  रूख_VEC_ELT (रूख_मान (t), 1) = omp_in;
	  रूख_VEC_ELT (रूख_मान (t), 2) = combiner.मान;
	  walk_रूख (&combiner.मान, c_check_omp_declare_reduction_r,
		     &रूख_VEC_ELT (रूख_मान (t), 0), रिक्त);
	  यदि (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      रूख_VEC_ELT (रूख_मान (t), 3) = omp_priv;
	      रूख_VEC_ELT (रूख_मान (t), 4) = omp_orig;
	      रूख_VEC_ELT (रूख_मान (t), 5) = initializer.मान;
	      walk_रूख (&initializer.मान, c_check_omp_declare_reduction_r,
			 &रूख_VEC_ELT (रूख_मान (t), 3), रिक्त);
	      walk_रूख (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &रूख_VEC_ELT (रूख_मान (t), 3), रिक्त);
	    }
	}

      झिक_stmt_list (stmt);
      झिक_scope ();
      यदि (cfun->language != रिक्त)
	{
	  ggc_free (cfun->language);
	  cfun->language = रिक्त;
	}
      set_cfun (रिक्त);
      current_function_decl = NULL_रूख;
      यदि (nested)
	c_झिक_function_context ();

      यदि (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      यदि (bad)
	गच्छ fail;
      यदि (errs != errorcount)
	रोक;
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
  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  फर्काऊ सत्य;
	}
      यदि (म_भेद (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  फर्काऊ असत्य;
	}
      यदि (म_भेद (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  फर्काऊ असत्य;
	}
      यदि (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  फर्काऊ असत्य;
	}
      यदि (म_भेद (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  फर्काऊ असत्य;
	}
      यदि (म_भेद (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  फर्काऊ सत्य;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  फर्काऊ असत्य;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

स्थिर शून्य
c_parser_omp_requires (c_parser *parser)
{
  गणना omp_requires new_req = (गणना omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      यदि (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      यदि (c_parser_next_token_is (parser, CPP_NAME))
	{
	  अचर वर्ण *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  गणना omp_requires this_req = (गणना omp_requires) 0;

	  यदि (!म_भेद (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  अन्यथा यदि (!म_भेद (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  अन्यथा यदि (!म_भेद (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  अन्यथा यदि (!म_भेद (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  अन्यथा यदि (!म_भेद (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  अन्यथा यदि (!म_भेद (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      यदि (parens.require_open (parser))
		{
		  यदि (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      रूख v = c_parser_peek_token (parser)->मान;
		      p = IDENTIFIER_POINTER (v);

		      यदि (!म_भेद (p, "seq_cst"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      अन्यथा यदि (!म_भेद (p, "relaxed"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      अन्यथा यदि (!म_भेद (p, "release"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      अन्यथा यदि (!म_भेद (p, "acq_rel"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      अन्यथा यदि (!म_भेद (p, "acquire"))
			this_req
			  = (गणना omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  यदि (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      विकल्प (c_parser_peek_token (parser)->type)
			{
			पक्ष CPP_EOF:
			पक्ष CPP_PRAGMA_EOL:
			पक्ष CPP_CLOSE_PAREN:
			  रोक;
			स्वभाव:
			  यदि (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  रोक;
			}
		    }
		  अन्यथा
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  यदि (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, असत्य);
		      फर्काऊ;
		    }
		}
	      p = रिक्त;
	    }
	  अन्यथा
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, असत्य);
	      फर्काऊ;
	    }
	  यदि (p)
	    c_parser_consume_token (parser);
	  यदि (this_req)
	    {
	      यदि ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  यदि ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  यदि (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      अन्यथा यदि ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (गणना omp_requires) 0;
		}
	      अन्यथा यदि ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (गणना omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      अन्यथा यदि ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (गणना omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (गणना omp_requires) (omp_requires_mask | this_req);
	      जारी;
	    }
	}
      रोक;
    }
  c_parser_skip_to_pragma_eol (parser);

  यदि (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

स्थिर रूख
c_finish_taskloop_clauses (रूख clauses)
{
  रूख *pc = &clauses;
  लागि (रूख c = clauses; c; c = *pc)
    {
      तार्किक हटाओ = असत्य;
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  रूख type = strip_array_types (रूख_TYPE (OMP_CLAUSE_DECL (c)));
	  यदि (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (रूख_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      हटाओ = सत्य;
	    }
	}
      यदि (हटाओ)
	*pc = OMP_CLAUSE_CHAIN (c);
      अन्यथा
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  फर्काऊ clauses;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अङ्क_TASKS)	\
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

स्थिर रूख
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       वर्ण *p_name, omp_clause_mask mask, रूख *cclauses,
		       तार्किक *if_p)
{
  रूख clauses, block, ret;

  म_जोड़ो (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  यदि ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अङ्क_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  यदि (c_parser_next_token_is (parser, CPP_NAME))
    {
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);

      यदि (म_भेद (p, "simd") == 0)
	{
	  रूख cclauses_buf[C_OMP_CLAUSE_SPLIT_गन्ती];
	  यदि (cclauses == रिक्त)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  यदि (!flag_openmp)  /* flag_openmp_simd  */
	    फर्काऊ c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (सत्य);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, सत्य);
	  यदि (ret == रिक्त)
	    फर्काऊ ret;
	  ret = make_गाँठो (OMP_TASKLOOP);
	  रूख_TYPE (ret) = void_type_गाँठो;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_अभिव्यक्ति_LOCATION (ret, loc);
	  add_stmt (ret);
	  फर्काऊ ret;
	}
    }
  यदि (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, असत्य);
      फर्काऊ NULL_रूख;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == रिक्त);
  यदि (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (सत्य);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, रिक्त, if_p);
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
स्थिर रूख
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  रूख sizes = NULL_रूख;

  यदि (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  यदि (tok->type != CPP_NAME
      || म_भेद ("sizes", IDENTIFIER_POINTER (tok->मान)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      फर्काऊ error_mark_गाँठो;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  यदि (!parens.require_open (parser))
    फर्काऊ error_mark_गाँठो;

  vec<रूख, va_gc> *sizes_vec
    = c_parser_अभिव्यक्ति_list (parser, सत्य, सत्य, रिक्त, रिक्त, रिक्त, रिक्त);
  sizes = build_रूख_list_vec (sizes_vec);
  release_रूख_vector (sizes_vec);

  लागि (रूख s = sizes; s; s = रूख_CHAIN (s))
    {
      रूख अभिव्यक्ति = रूख_मान (s);
      यदि (अभिव्यक्ति == error_mark_गाँठो)
	{
	  parens.skip_until_found_close (parser);
	  फर्काऊ error_mark_गाँठो;
	}

      HOST_WIDE_INT n;
      यदि (!INTEGRAL_TYPE_P (रूख_TYPE (अभिव्यक्ति))
	  || !रूख_fits_shwi_p (अभिव्यक्ति)
	  || (n = रूख_to_shwi (अभिव्यक्ति)) <= 0
	  || (पूर्णाङ्क) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  रूख_मान (s) = integer_one_गाँठो;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  रूख c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  फर्काऊ c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

स्थिर रूख
c_parser_omp_tile (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  यदि (!clauses || clauses == error_mark_गाँठो)
    फर्काऊ error_mark_गाँठो;

  रूख block = c_begin_compound_stmt (सत्य);
  रूख ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    रिक्त, if_p);
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

स्थिर रूख
c_parser_omp_unroll (location_t loc, c_parser *parser, तार्किक *if_p)
{
  रूख clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", सत्य);

  रूख block = c_begin_compound_stmt (सत्य);
  रूख ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    रिक्त, if_p);
  block = c_end_compound_stmt (loc, block, सत्य);
  add_stmt (block);

  फर्काऊ ret;
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
  रूख message = NULL_रूख;
  तार्किक bad = असत्य;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      यदि (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      यदि (!c_parser_next_token_is (parser, CPP_NAME))
	रोक;

      अचर वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      location_t cloc = c_parser_peek_token (parser)->location;
      स्थिर अचर वर्ण *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      पूर्णाङ्क *v = रिक्त;
      पूर्णाङ्क idx = 0, n = -1;
      रूख m = NULL_रूख;

      यदि (!म_भेद (p, "at"))
	v = &at_compilation;
      अन्यथा यदि (!म_भेद (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      अन्यथा यदि (म_भेद (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, असत्य);
	  फर्काऊ असत्य;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      यदि (parens.require_open (parser))
	{
	  यदि (v == रिक्त)
	    {
	      location_t अभिव्यक्ति_loc = c_parser_peek_token (parser)->location;
	      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	      अभिव्यक्ति = convert_lvalue_to_rvalue (अभिव्यक्ति_loc, अभिव्यक्ति, सत्य, सत्य);
	      m = convert (const_string_type_गाँठो, अभिव्यक्ति.मान);
	      m = c_fully_fold (m, असत्य, रिक्त);
	    }
	  अन्यथा
	    {
	      यदि (c_parser_next_token_is (parser, CPP_NAME))
		{
		  रूख val = c_parser_peek_token (parser)->मान;
		  अचर वर्ण *q = IDENTIFIER_POINTER (val);

		  यदि (!म_भेद (q, args[idx]))
		    n = 0;
		  अन्यथा यदि (!म_भेद (q, args[idx + 1]))
		    n = 1;
		}
	      यदि (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  bad = सत्य;
		  विकल्प (c_parser_peek_token (parser)->type)
		    {
		    पक्ष CPP_EOF:
		    पक्ष CPP_PRAGMA_EOL:
		    पक्ष CPP_CLOSE_PAREN:
		      रोक;
		    स्वभाव:
		      यदि (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      रोक;
		    }
		}
	      अन्यथा
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  यदि (v == रिक्त)
	    {
	      यदि (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = सत्य;
		}
	      अन्यथा
		message = m;
	    }
	  अन्यथा यदि (n != -1)
	    {
	      यदि (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = सत्य;
		}
	      अन्यथा
		*v = n;
	    }
	}
      अन्यथा
	bad = सत्य;
    }
  c_parser_skip_to_pragma_eol (parser);
  यदि (bad)
    फर्काऊ सत्य;

  यदि (at_compilation == -1)
    at_compilation = 1;
  यदि (severity_fatal == -1)
    severity_fatal = 1;
  यदि (!at_compilation)
    {
      यदि (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  फर्काऊ सत्य;
	}
      यदि (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = सत्य;
	  फर्काऊ सत्य;
	}
      रूख fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      यदि (!message)
	message = build_zero_cst (const_string_type_गाँठो);
      रूख stmt = build_call_अभिव्यक्ति_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_गाँठो));
      add_stmt (stmt);
      फर्काऊ सत्य;
    }
  अचर वर्ण *सन्देश = रिक्त;
  यदि (message)
    {
      सन्देश = c_getstr (message);
      यदि (सन्देश == रिक्त)
	सन्देश = _("<message unknown at compile time>");
    }
  अचर गणना diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  यदि (सन्देश)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", सन्देश);
  अन्यथा
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  फर्काऊ असत्य;
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
  तार्किक no_openmp = असत्य;
  तार्किक no_openmp_constructs = असत्य;
  तार्किक no_openmp_routines = असत्य;
  तार्किक no_parallelism = असत्य;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (रिक्त);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  यदि (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      यदि (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      यदि (!c_parser_next_token_is (parser, CPP_NAME))
	रोक;

      अचर वर्ण *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      location_t cloc = c_parser_peek_token (parser)->location;

      यदि (!म_भेद (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  यदि (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = सत्य;
	}
      अन्यथा यदि (!म_भेद (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  यदि (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = सत्य;
	}
      अन्यथा यदि (!म_भेद (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  यदि (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = सत्य;
	}
      अन्यथा यदि (!म_भेद (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  यदि (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = सत्य;
	}
      अन्यथा यदि (!म_भेद (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  यदि (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_अभिव्यक्ति अभिव्यक्ति = c_parser_अभिव्यक्ति_no_commas (parser, रिक्त);
	      रूख t = convert_lvalue_to_rvalue (eloc, अभिव्यक्ति, सत्य, सत्य).मान;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, असत्य, रिक्त);
	      यदि (is_assume && t != error_mark_गाँठो)
		{
		  रूख fn = build_call_अभिव्यक्ति_internal_loc (eloc, IFN_ASSUME,
							  void_type_गाँठो, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      अन्यथा यदि (!म_भेद (p, "absent") || !म_भेद (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  यदि (parens.require_open (parser))
	    {
	      गर
		{
		  अचर वर्ण *directive[3] = {};
		  पूर्णाङ्क i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  लागि (i = 0; i < 3; i++)
		    {
		      रूख id;
		      यदि (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->मान;
		      अन्यथा यदि (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  गणना rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      अन्यथा
			रोक;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  यदि (i == 0)
		    error_at (dloc, "expected directive name");
		  अन्यथा
		    {
		      अचर संरचना c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      यदि (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      अन्यथा यदि (dir == रिक्त
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      अन्यथा
			{
			  पूर्णाङ्क id = dir - c_omp_directives;
			  यदि (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  अन्यथा यदि (!bitmap_set_bit (p[0] == 'a'
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
		      लागि (; i; --i)
			c_parser_consume_token (parser);
		    }
		  यदि (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  अन्यथा
		    रोक;
		}
	      जबसम्म (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      अन्यथा यदि (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      अन्यथा
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  रोक;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

स्थिर शून्य
c_parser_omp_assume (c_parser *parser, तार्किक *if_p)
{
  c_parser_omp_assumption_clauses (parser, सत्य);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

स्थिर शून्य
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, असत्य);
}

/* Helper function for c_parser_omp_metadirective.  */

स्थिर शून्य
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<रूख> &labels)
{
  पूर्णाङ्क nesting_depth = 0;
  पूर्णाङ्क bracket_depth = 0;
  तार्किक ignore_label = असत्य;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  जबसम्म (1)
    {
      c_token *token = c_parser_peek_token (parser);
      तार्किक stop = असत्य;

      यदि (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = सत्य;

      विकल्प (token->type)
	{
	पक्ष CPP_EOF:
	  रोक;
	पक्ष CPP_NAME:
	  यदि (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_थप (token->मान);
	  गच्छ add;
	पक्ष CPP_OPEN_BRACE:
	  ++nesting_depth;
	  गच्छ add;
	पक्ष CPP_CLOSE_BRACE:
	  यदि (--nesting_depth == 0 && bracket_depth == 0)
	    stop = सत्य;
	  गच्छ add;
	पक्ष CPP_OPEN_PAREN:
	  ++bracket_depth;
	  गच्छ add;
	पक्ष CPP_CLOSE_PAREN:
	  --bracket_depth;
	  गच्छ add;
	पक्ष CPP_COLON:
	  ignore_label = असत्य;
	  गच्छ add;
	पक्ष CPP_SEMICOLON:
	  यदि (nesting_depth == 0 && bracket_depth == 0)
	    stop = सत्य;
	  गच्छ add;
	स्वभाव:
	add:
	  tokens.safe_थप (*token);
	  यदि (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  अन्यथा यदि (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  अन्यथा
	    c_parser_consume_token (parser);
	  यदि (stop)
	    रोक;
	  जारी;
	}
      रोक;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

स्थिर शून्य
c_parser_omp_metadirective (c_parser *parser, तार्किक *if_p)
{
  स्थिर अचिन्हित पूर्णाङ्क metadirective_region_गन्ती = 0;

  रूख ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<रूख> body_labels;
  auto_vec<अचर संरचना c_omp_directive *> directives;
  auto_vec<रूख> ctxs;
  vec<संरचना omp_variant> candidates;
  तार्किक default_seen = असत्य;
  पूर्णाङ्क directive_token_idx = 0;
  रूख standalone_body = NULL_रूख;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  तार्किक requires_body = असत्य;

  ret = make_गाँठो (OMP_METADIRECTIVE);
  SET_अभिव्यक्ति_LOCATION (ret, pragma_loc);
  रूख_TYPE (ret) = void_type_गाँठो;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_रूख;

  c_parser_consume_pragma (parser);
  जबसम्म (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      यदि (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  गच्छ error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      अचर वर्ण *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      यदि (म_भेद (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      तार्किक default_p
	= म_भेद (p, "default") == 0 || म_भेद (p, "otherwise") == 0;
      यदि (default_p)
	{
	  यदि (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      गच्छ error;
	    }
	  default_seen = सत्य;
	}
      अन्यथा यदि (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  गच्छ error;
	}
      यदि (!default_p && म_भेद (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  गच्छ error;
	}

      matching_parens parens;
      रूख ctx = NULL_रूख;
      तार्किक skip = असत्य;

      यदि (!parens.require_open (parser))
	गच्छ error;

      यदि (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_रूख);
	  यदि (ctx == error_mark_गाँठो)
	    गच्छ error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  यदि (ctx == error_mark_गाँठो)
	    गच्छ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_रूख, असत्य) == 0);

	  यदि (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      गच्छ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      अचर वर्ण *directive[3] = {};
      पूर्णाङ्क i;
      लागि (i = 0; i < 3; i++)
	{
	  रूख id;
	  यदि (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      यदि (i == 0)
		directive[i++] = "nothing";
	      रोक;
	    }
	  अन्यथा यदि (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->मान;
	  अन्यथा यदि (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      गणना rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  अन्यथा
	    रोक;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      यदि (i == 0)
	{
	  error_at (loc, "expected directive name");
	  गच्छ error;
	}

      अचर संरचना c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      यदि (omp_directive == रिक्त)
	{
	  लागि (पूर्णाङ्क j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  गच्छ error;
	}
      अन्यथा
	{
	  पूर्णाङ्क token_गन्ती = 0;
	  यदि (omp_directive->first) token_गन्ती++;
	  यदि (omp_directive->second) token_गन्ती++;
	  यदि (omp_directive->third) token_गन्ती++;
	  लागि (पूर्णाङ्क j = 0; j < token_गन्ती; j++)
	    c_parser_consume_token (parser);
	}
      यदि (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  गच्छ error;
	}
      यदि (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  गच्छ error;
	}
      यदि (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = सत्य;

      यदि (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (गणना pragma_kind) omp_directive->id;

	  directives.safe_थप (omp_directive);
	  directive_tokens.safe_थप (pragma_token);
	  ctxs.safe_थप (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      पूर्णाङ्क nesting_depth = 0;
      जबसम्म (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  विकल्प (token->type)
	    {
	    पक्ष CPP_EOF:
	    पक्ष CPP_PRAGMA_EOL:
	      रोक;
	    पक्ष CPP_OPEN_PAREN:
	      ++nesting_depth;
	      गच्छ add;
	    पक्ष CPP_CLOSE_PAREN:
	      यदि (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  रोक;
		}
	      गच्छ add;
	    स्वभाव:
	    add:
	      यदि (!skip)
		directive_tokens.safe_थप (*token);
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  रोक;
	}

      यदि (!skip)
	{
	  c_token eol_token;
	  स_रखो (&eol_token, 0, परिमाण (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_थप (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  यदि (ctxs.length () == 1)
    {
      रूख ctx = ctxs[0];
      यदि (ctx == NULL_रूख
	  || (omp_context_selector_matches (ctx, NULL_रूख, असत्य) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	फर्काऊ;
    }

  यदि (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      अचर संरचना c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", रिक्त, रिक्त);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_थप (omp_directive);
      directive_tokens.safe_थप (pragma_token);
      ctxs.safe_थप (NULL_रूख);

      c_token eol_token;
      स_रखो (&eol_token, 0, परिमाण (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_थप (eol_token);
    }

  यदि (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  अचिन्हित i;
  रूख ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      गर
	tokens.safe_थप (directive_tokens [directive_token_idx++]);
      जबसम्म (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      लागि (अचिन्हित j = 0; j < body_tokens.length (); j++)
	tokens.safe_थप (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      स_रखो (&eof_token, 0, परिमाण (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_थप (eof_token);
      tokens.safe_थप (eof_token);

      अचिन्हित पूर्णाङ्क old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      संरचना omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      संरचना omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      संरचना omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_अङ्क = ++metadirective_region_गन्ती;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = रिक्त;
      parser->omp_metadirective_state = &new_state;

      पूर्णाङ्क prev_errorcount = errorcount;
      रूख directive = c_begin_compound_stmt (सत्य);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_रूख);
      directive = c_end_compound_stmt (pragma_loc, directive, सत्य);
      तार्किक standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      यदि (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  यदि (standalone_body == NULL_रूख)
	    {
	      standalone_body = थप_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = झिक_stmt_list (standalone_body);
	    }
	  अन्यथा
	    c_parser_skip_to_end_of_block_or_statement (parser, सत्य);
	}

      रूख body = standalone_p ? standalone_body : NULL_रूख;
      रूख variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      यदि (errorcount == prev_errorcount)
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
  यदि (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  फर्काऊ;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  यदि (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, असत्य);
}

/* Main entry point to parsing most OpenMP pragmas.  */

स्थिर शून्य
c_parser_omp_construct (c_parser *parser, तार्किक *if_p)
{
  गणना pragma_kind p_kind;
  location_t loc;
  रूख stmt;
  वर्ण p_name[परिमाण "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  विकल्प (p_kind)
    {
    पक्ष PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, सत्य);
      फर्काऊ;
    पक्ष PRAGMA_OACC_CACHE:
      म_नकल (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      रोक;
    पक्ष PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OACC_KERNELS:
    पक्ष PRAGMA_OACC_PARALLEL:
    पक्ष PRAGMA_OACC_SERIAL:
      म_नकल (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      रोक;
    पक्ष PRAGMA_OACC_LOOP:
      म_नकल (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OACC_WAIT:
      म_नकल (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      रोक;
    पक्ष PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, असत्य);
      फर्काऊ;
    पक्ष PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OMP_DISTRIBUTE:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OMP_FOR:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OMP_LOOP:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OMP_MASKED:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OMP_MASTER:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, रिक्त, if_p,
				  UNKNOWN_LOCATION);
      रोक;
    पक्ष PRAGMA_OMP_PARALLEL:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OMP_SECTIONS:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, रिक्त);
      रोक;
    पक्ष PRAGMA_OMP_SIMD:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OMP_TASKLOOP:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OMP_TEAMS:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, रिक्त, if_p);
      रोक;
    पक्ष PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      फर्काऊ;
    पक्ष PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      रोक;
    पक्ष PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      रोक;
    स्वभाव:
      gcc_unreachable ();
    }

  यदि (stmt && stmt != error_mark_गाँठो)
    gcc_assert (अभिव्यक्ति_LOCATION (stmt) != UNKNOWN_LOCATION);
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
  रूख vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, रिक्त);
  रूख clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
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
  रूख vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, रिक्त);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  लागि (t = vars; t; t = रूख_CHAIN (t))
    {
      रूख v = रूख_PURPOSE (t);
      loc = अभिव्यक्ति_LOCATION (रूख_मान (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      यदि (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      अन्यथा यदि (रूख_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      अन्यथा यदि (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      अन्यथा यदि (रूख_TYPE (v) == error_mark_गाँठो)
	;
      अन्यथा यदि (! COMPLETE_TYPE_P (रूख_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      अन्यथा
	{
	  यदि (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      यदि (DECL_RTL_SET_P (v))
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

स्थिर रूख
c_parser_transaction_attributes (c_parser *parser)
{
  यदि (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    फर्काऊ c_parser_gnu_attributes (parser);

  यदि (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    फर्काऊ NULL_रूख;
  फर्काऊ c_parser_std_attribute_specifier (parser, सत्य);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

स्थिर रूख
c_parser_transaction (c_parser *parser, गणना rid keyword)
{
  अचिन्हित पूर्णाङ्क old_in = parser->in_transaction;
  अचिन्हित पूर्णाङ्क this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  रूख stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  यदि (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  अन्यथा
    {
      attrs = c_parser_transaction_attributes (parser);
      यदि (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  यदि (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  अन्यथा
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  फर्काऊ stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

स्थिर संरचना c_अभिव्यक्ति
c_parser_transaction_expression (c_parser *parser, गणना rid keyword)
{
  संरचना c_अभिव्यक्ति ret;
  अचिन्हित पूर्णाङ्क old_in = parser->in_transaction;
  अचिन्हित पूर्णाङ्क this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  रूख attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  यदि (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  अन्यथा
    {
      attrs = c_parser_transaction_attributes (parser);
      यदि (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  यदि (parens.require_open (parser))
    {
      रूख अभिव्यक्ति = c_parser_expression (parser).मान;
      ret.original_type = रूख_TYPE (अभिव्यक्ति);
      ret.मान = build1 (TRANSACTION_अभिव्यक्ति, ret.original_type, अभिव्यक्ति);
      यदि (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_अभिव्यक्ति_RELAXED (ret.मान) = 1;
      SET_अभिव्यक्ति_LOCATION (ret.मान, loc);
      ret.original_code = TRANSACTION_अभिव्यक्ति;
      ret.m_decimal = 0;
      यदि (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, रिक्त);
	  गच्छ error;
	}
    }
  अन्यथा
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
    }
  parser->in_transaction = old_in;

  यदि (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_अभिव्यक्ति_source_range (&ret, loc, loc);

  फर्काऊ ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

स्थिर रूख
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  रूख attrs;
  तार्किक is_outer = असत्य;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  यदि (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  यदि (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      गच्छ ret_error;
    }
  अन्यथा यदि (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      गच्छ ret_error;
    }
  अन्यथा यदि (is_outer)
    {
      यदि ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  गच्छ ret_error;
	}
    }
  अन्यथा यदि (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      गच्छ ret_error;
    }

  फर्काऊ add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  फर्काऊ build1 (NOP_अभिव्यक्ति, void_type_गाँठो, error_mark_गाँठो);
}

/* Parse a single source file.  */

शून्य
c_parse_file (शून्य)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  स_रखो (&tparser, 0, परिमाण tparser);
  tparser.translate_strings_p = सत्य;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  यदि (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  अन्यथा
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  यदि (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  यदि (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = रिक्त;
}

शून्य
c_init_preprocess (शून्य)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  स_रखो (the_parser, 0, परिमाण (c_parser));
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
  यदि (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      मुक्त (start_with_pass);
      फर्काऊ c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  पूर्णाङ्क अङ्क_open_braces = 1;
  जबसम्म (1)
    {
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_OPEN_BRACE:
	  अङ्क_open_braces++;
	  रोक;
	पक्ष CPP_CLOSE_BRACE:
	  यदि (--अङ्क_open_braces == 0)
	    गच्छ found_closing_brace;
	  रोक;
	पक्ष CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  मुक्त (start_with_pass);
	  फर्काऊ c_parser_peek_token (parser)->location;
	स्वभाव:
	  रोक;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  यदि (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      मुक्त (start_with_pass);
      फर्काऊ end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  फर्काऊ end_loc;
}

#अन्तर्भाव "gt-c-c-parser.h"
