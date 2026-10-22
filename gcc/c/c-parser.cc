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

#समावेश "config.h"
#घोषणा INCLUDE_STRING
#समावेश "system.h"
#समावेश "coretypes.h"
#समावेश "target.h"
#समावेश "function.h"
#समावेश "c-tree.h"
#समावेश "timevar.h"
#समावेश "stringpool.h"
#समावेश "cgraph.h"
#समावेश "attribs.h"
#समावेश "stor-layout.h"
#समावेश "varasm.h"
#समावेश "trans-mem.h"
#समावेश "c-family/c-pragma.h"
#समावेश "c-lang.h"
#समावेश "c-family/c-objc.h"
#समावेश "plugin.h"
#समावेश "omp-general.h"
#समावेश "omp-offload.h"
#समावेश "builtins.h"
#समावेश "gomp-constants.h"
#समावेश "c-family/c-indentation.h"
#समावेश "gimple-expr.h"
#समावेश "context.h"
#समावेश "gcc-rich-location.h"
#समावेश "c-parser.h"
#समावेश "gimple-parser.h"
#समावेश "read-rtl-function.h"
#समावेश "run-rtl-passes.h"
#समावेश "intl.h"
#समावेश "c-family/name-hint.h"
#समावेश "tree-iterator.h"
#समावेश "tree-pretty-print.h"
#समावेश "memmodel.h"
#समावेश "c-family/known-headers.h"
#समावेश "bitmap.h"
#समावेश "analyzer/analyzer-language.h"
#समावेश "toplev.h"
#समावेश "asan.h"
#समावेश "c-family/c-ubsan.h"
#समावेश "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<वृक्ष> incomplete_record_decls;

व्योम
set_c_व्यंजक_source_range (c_व्यंजक *व्यंजक,
			 location_t start, location_t finish)
{
  व्यंजक->src_range.m_start = start;
  व्यंजक->src_range.m_finish = finish;
  अगर (व्यंजक->मूल्य)
    set_source_range (व्यंजक->मूल्य, start, finish);
}

व्योम
set_c_व्यंजक_source_range (c_व्यंजक *व्यंजक,
			 source_range src_range)
{
  व्यंजक->src_range = src_range;
  अगर (व्यंजक->मूल्य)
    set_source_range (व्यंजक->मूल्य, src_range);
}


/* Initialization routine for this file.  */

व्योम
c_parse_init (व्योम)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  अचिन्हित पूर्णांक i;
  वृक्ष id;
  पूर्णांक mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  अगर (!flag_isoc99)
    mask |= D_C99;
  अगर (!flag_isoc23)
    mask |= D_C23;
  अगर (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      अगर (!flag_isoc99)
	mask |= D_EXT89;
      अगर (!flag_isoc23)
	mask |= D_EXT11;
    }
  अगर (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<वृक्ष> ((पूर्णांक) RID_MAX);
  क्रम (i = 0; i < अंक_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      अगर (c_common_reswords[i].disable & mask)
	{
	  अगर (warn_cxx_compat
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
      ridpointers [(पूर्णांक) c_common_reswords[i].rid] = id;
    }

  क्रम (i = 0; i < अंक_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      अक्षर name[50];
      प्र_लिखो (name, "__int%d", int_n_तथ्य[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      प्र_लिखो (name, "__int%d__", int_n_तथ्य[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  अगर (flag_openmp)
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
काष्ठा GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  अचिन्हित पूर्णांक tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  अचिन्हित पूर्णांक raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  bool error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  bool in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  bool in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  bool lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  bool translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  bool objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  bool objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  bool objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  अचिन्हित पूर्णांक in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  bool objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  bool seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  bool omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  काष्ठा omp_for_parse_तथ्य * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  काष्ठा omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  वृक्ष in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  काष्ठा omp_metadirective_parse_तथ्य * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
काष्ठा GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  अचिन्हित पूर्णांक save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
काष्ठा GTY(()) omp_begin_declare_variant_map_entry {
  वृक्ष variant;		/* The variant decl.  */
  वृक्ष id;		/* Name of base function.  */
  वृक्ष ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

अटल वृक्ष omp_start_variant_function (c_declarator *, वृक्ष);
अटल व्योम omp_finish_variant_function (वृक्ष, वृक्ष, वृक्ष);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, अचिन्हित n)
{
  वापस &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

bool
c_parser_error (c_parser *parser)
{
  वापस parser->error;
}

/* Set the error state of PARSER to ERR.  */

व्योम
c_parser_set_error (c_parser *parser, bool err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

अटल GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

अटल व्योम
c_lex_one_token (c_parser *parser, c_token *token, bool raw = false)
{
  timevar_धकेलो (TV_LEX);

  अगर (raw || vec_safe_लंबाई (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->मूल्य, &token->location,
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
      अगर (parser->raw_tokens_used == vec_safe_लंबाई (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  अगर (raw)
    जाओ out;

  चयन (token->type)
    {
    हाल CPP_NAME:
      {
	वृक्ष decl;

	bool objc_force_identifier = parser->objc_need_raw_identifier;
	अगर (c_dialect_objc ())
	  parser->objc_need_raw_identifier = false;

	अगर (C_IS_RESERVED_WORD (token->मूल्य))
	  {
	    क्रमागत rid rid_code = C_RID_CODE (token->मूल्य);

	    अगर (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->मूल्य);
	      }
	    अन्यथा अगर (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		अवरोध;
	      }
	    अन्यथा अगर (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		अगर (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    अवरोध;
		  }
		अन्यथा अगर (parser->objc_could_be_foreach_context
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
		    अवरोध;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    अन्यथा अगर (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		अगर (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    अवरोध;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    अन्यथा अगर (c_dialect_objc ()
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
		अवरोध;
	      }
	  }

	decl = lookup_name (token->मूल्य);
	अगर (decl)
	  {
	    अगर (वृक्ष_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		अवरोध;
	      }
	  }
	अन्यथा अगर (c_dialect_objc ())
	  {
	    वृक्ष objc_interface_decl = objc_is_class_name (token->मूल्य);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    अगर (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->मूल्य = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		अवरोध;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      अवरोध;
    हाल CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      चयन (C_RID_CODE (token->मूल्य))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	हाल RID_CLASS:     token->keyword = RID_AT_CLASS; अवरोध;
	हाल RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; अवरोध;
	हाल RID_PROTECTED: token->keyword = RID_AT_PROTECTED; अवरोध;
	हाल RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; अवरोध;
	हाल RID_THROW:     token->keyword = RID_AT_THROW; अवरोध;
	हाल RID_TRY:       token->keyword = RID_AT_TRY; अवरोध;
	हाल RID_CATCH:     token->keyword = RID_AT_CATCH; अवरोध;
	हाल RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; अवरोध;
	शेष:            token->keyword = C_RID_CODE (token->मूल्य);
	}
      अवरोध;
    हाल CPP_COLON:
    हाल CPP_COMMA:
    हाल CPP_CLOSE_PAREN:
    हाल CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      अगर (c_dialect_objc ())
	parser->objc_need_raw_identifier = false;
      अवरोध;
    हाल CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (क्रमागत pragma_kind) वृक्ष_INT_CST_निचला (token->मूल्य);
      token->मूल्य = शून्य;
      अवरोध;
    शेष:
      अवरोध;
    }
 out:
  timevar_निकालो (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  अगर (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  वापस &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  अगर (parser->tokens_avail >= 2)
    वापस &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  वापस &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, अचिन्हित पूर्णांक n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  अगर (parser->tokens_avail >= n)
    वापस &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  वापस &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, अचिन्हित पूर्णांक n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  अगर (parser->tokens_avail >= n)
    वापस &parser->tokens[n - 1];
  अचिन्हित पूर्णांक raw_len = vec_safe_लंबाई (parser->raw_tokens);
  अचिन्हित पूर्णांक raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  अगर (raw_avail >= n)
    वापस &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], true);
  वापस &(*parser->raw_tokens)[raw_len];
}

bool
c_keyword_starts_typename (क्रमागत rid keyword)
{
  चयन (keyword)
    {
    हाल RID_UNSIGNED:
    हाल RID_LONG:
    हाल RID_SHORT:
    हाल RID_SIGNED:
    हाल RID_COMPLEX:
    हाल RID_INT:
    हाल RID_CHAR:
    हाल RID_FLOAT:
    हाल RID_DOUBLE:
    हाल RID_VOID:
    हाल RID_DFLOAT32:
    हाल RID_DFLOAT64:
    हाल RID_DFLOAT128:
    हाल RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    हाल RID_BOOL:
    हाल RID_BITINT:
    हाल RID_ENUM:
    हाल RID_STRUCT:
    हाल RID_UNION:
    हाल RID_TYPEOF:
    हाल RID_TYPEOF_UNQUAL:
    हाल RID_CONST:
    हाल RID_ATOMIC:
    हाल RID_VOLATILE:
    हाल RID_RESTRICT:
    हाल RID_ATTRIBUTE:
    हाल RID_FRACT:
    हाल RID_ACCUM:
    हाल RID_SAT:
    हाल RID_AUTO_TYPE:
    हाल RID_ALIGNAS:
      वापस true;
    शेष:
      अगर (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + अंक_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	वापस true;
      वापस false;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
bool
c_token_starts_typename (c_token *token)
{
  चयन (token->type)
    {
    हाल CPP_NAME:
      चयन (token->id_kind)
	{
	हाल C_ID_ID:
	  वापस false;
	हाल C_ID_ADDRSPACE:
	  वापस true;
	हाल C_ID_TYPENAME:
	  वापस true;
	हाल C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  वापस true;
	शेष:
	  gcc_unreachable ();
	}
    हाल CPP_KEYWORD:
      वापस c_keyword_starts_typename (token->keyword);
    हाल CPP_LESS:
      अगर (c_dialect_objc ())
	वापस true;
      वापस false;
    शेष:
      वापस false;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

अटल अंतरभूत bool
c_parser_अग्र_tokens_start_typename (c_parser *parser, क्रमागत c_lookahead_kind la,
				     अचिन्हित पूर्णांक n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  अगर (c_token_starts_typename (token))
    वापस true;

  /* Try a bit harder to detect an unknown typename.  */
  अगर (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->मूल्य))
    वापस true;

  वापस false;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
अटल bool
c_token_starts_compound_literal (c_token *token)
{
  चयन (token->type)
    {
    हाल CPP_KEYWORD:
      चयन (token->keyword)
	{
	हाल RID_CONSTEXPR:
	हाल RID_REGISTER:
	हाल RID_STATIC:
	हाल RID_THREAD:
	  वापस true;
	शेष:
	  अवरोध;
	}
      /* Fall through.  */
    शेष:
      वापस c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
अटल bool
c_token_is_qualifier (c_token *token)
{
  चयन (token->type)
    {
    हाल CPP_NAME:
      चयन (token->id_kind)
	{
	हाल C_ID_ADDRSPACE:
	  वापस true;
	शेष:
	  वापस false;
	}
    हाल CPP_KEYWORD:
      चयन (token->keyword)
	{
	हाल RID_CONST:
	हाल RID_VOLATILE:
	हाल RID_RESTRICT:
	हाल RID_ATTRIBUTE:
	हाल RID_ATOMIC:
	  वापस true;
	शेष:
	  वापस false;
	}
    हाल CPP_LESS:
      वापस false;
    शेष:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
अटल अंतरभूत bool
c_parser_अग्र_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  वापस c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
अटल bool
c_token_starts_declspecs (c_token *token)
{
  चयन (token->type)
    {
    हाल CPP_NAME:
      चयन (token->id_kind)
	{
	हाल C_ID_ID:
	  वापस false;
	हाल C_ID_ADDRSPACE:
	  वापस true;
	हाल C_ID_TYPENAME:
	  वापस true;
	हाल C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  वापस true;
	शेष:
	  gcc_unreachable ();
	}
    हाल CPP_KEYWORD:
      चयन (token->keyword)
	{
	हाल RID_STATIC:
	हाल RID_EXTERN:
	हाल RID_REGISTER:
	हाल RID_TYPEDEF:
	हाल RID_INLINE:
	हाल RID_NORETURN:
	हाल RID_AUTO:
	हाल RID_THREAD:
	हाल RID_UNSIGNED:
	हाल RID_LONG:
	हाल RID_SHORT:
	हाल RID_SIGNED:
	हाल RID_COMPLEX:
	हाल RID_INT:
	हाल RID_CHAR:
	हाल RID_FLOAT:
	हाल RID_DOUBLE:
	हाल RID_VOID:
	हाल RID_DFLOAT32:
	हाल RID_DFLOAT64:
	हाल RID_DFLOAT128:
	हाल RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	हाल RID_BOOL:
	हाल RID_BITINT:
	हाल RID_ENUM:
	हाल RID_STRUCT:
	हाल RID_UNION:
	हाल RID_TYPEOF:
	हाल RID_TYPEOF_UNQUAL:
	हाल RID_CONST:
	हाल RID_VOLATILE:
	हाल RID_RESTRICT:
	हाल RID_ATTRIBUTE:
	हाल RID_FRACT:
	हाल RID_ACCUM:
	हाल RID_SAT:
	हाल RID_ALIGNAS:
	हाल RID_ATOMIC:
	हाल RID_AUTO_TYPE:
	हाल RID_CONSTEXPR:
	  वापस true;
	शेष:
	  अगर (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + अंक_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    वापस true;
	  वापस false;
	}
    हाल CPP_LESS:
      अगर (c_dialect_objc ())
	वापस true;
      वापस false;
    शेष:
      वापस false;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
अटल bool
c_token_starts_declaration (c_token *token)
{
  अगर (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    वापस true;
  अन्यथा
    वापस false;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
bool
c_parser_अग्र_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  अगर (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    वापस false;

  वापस c_token_starts_declspecs (token);
}

अटल bool c_parser_check_balanced_raw_token_sequence (c_parser *,
							अचिन्हित पूर्णांक *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
bool
c_parser_अग्र_tokens_start_declaration (c_parser *parser, अचिन्हित पूर्णांक n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  अगर (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    वापस false;

  /* Labels do not start declarations.  */
  अगर (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    वापस false;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  अगर (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      अगर (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	वापस true;
      वापस c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  अगर (c_token_starts_declaration (token))
    वापस true;

  अगर (c_parser_अग्र_tokens_start_typename (parser, cla_nonabstract_decl, n))
    वापस true;

  वापस false;
}

/* Consume the next token from PARSER.  */

व्योम
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
  अगर (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  अन्यथा अगर (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      अगर (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          अगर (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = false;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

अटल व्योम
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  अगर (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  अन्यथा अगर (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      अगर (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = true;
}

/* Update the global input_location from TOKEN.  */
अटल अंतरभूत व्योम
c_parser_set_source_position_from_token (c_token *token)
{
  अगर (token->type != CPP_EOF)
    {
      निवेश_location = token->location;
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

अटल bool
c_parser_peek_conflict_marker (c_parser *parser, क्रमागत cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  अगर (token2->type != tok1_kind)
    वापस false;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  अगर (token3->type != tok1_kind)
    वापस false;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  अगर (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    वापस false;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  अगर (LOCATION_COLUMN (start_loc) != 1)
    वापस false;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  वापस true;
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

अटल bool
c_parser_error_richloc (c_parser *parser, स्थिर अक्षर *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  अगर (parser->error)
    वापस false;
  parser->error = true;
  अगर (!gmsgid)
    वापस false;

  /* If this is actually a conflict marker, report it as such.  */
  अगर (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      अगर (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  वापस true;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  अगर (parser->seen_string_literal && token->type == CPP_NAME)
    {
      वृक्ष name = token->मूल्य;
      स्थिर अक्षर *token_name = IDENTIFIER_POINTER (name);
      स्थिर अक्षर *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      अगर (header_hint != शून्य)
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
		 token->मूल्य, /*flags=*/0, richloc);
  वापस true;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

bool
c_parser_error (c_parser *parser, स्थिर अक्षर *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (पंक्ति_table, निवेश_location);
  वापस c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

ढाँचा <typename traits_t>
श्रेणी token_pair
{
 खुला:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  bool require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    अगर (token)
      m_open_loc = token->location;

    वापस c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  व्योम consume_open (c_parser *parser)
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

  bool require_close (c_parser *parser) स्थिर
  {
    वापस c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  व्योम skip_until_found_close (c_parser *parser) स्थिर
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 निजी:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

काष्ठा matching_paren_traits
{
  अटल स्थिर क्रमागत cpp_ttype open_token_type = CPP_OPEN_PAREN;
  अटल स्थिर अक्षर * स्थिर open_gmsgid;
  अटल स्थिर क्रमागत cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  अटल स्थिर अक्षर * स्थिर close_gmsgid;
};

स्थिर अक्षर * स्थिर matching_paren_traits::open_gmsgid = "expected %<(%>";
स्थिर अक्षर * स्थिर matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

प्रकार token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

काष्ठा matching_brace_traits
{
  अटल स्थिर क्रमागत cpp_ttype open_token_type = CPP_OPEN_BRACE;
  अटल स्थिर अक्षर * स्थिर open_gmsgid;
  अटल स्थिर क्रमागत cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  अटल स्थिर अक्षर * स्थिर close_gmsgid;
};

स्थिर अक्षर * स्थिर matching_brace_traits::open_gmsgid = "expected %<{%>";
स्थिर अक्षर * स्थिर matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

प्रकार token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

अटल स्थिर अक्षर *
get_matching_प्रतीक (क्रमागत cpp_ttype type)
{
  चयन (type)
    {
    शेष:
      gcc_unreachable ();
    हाल CPP_CLOSE_PAREN:
      वापस "(";
    हाल CPP_CLOSE_BRACE:
      वापस "{";
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

bool
c_parser_require (c_parser *parser,
		  क्रमागत cpp_ttype type,
		  स्थिर अक्षर *msgid,
		  location_t matching_location,
		  bool type_is_unique)
{
  अगर (c_parser_अग्र_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      वापस true;
    }
  अन्यथा
    {
      location_t अग्र_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (अग्र_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      अगर (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      bool added_matching_location = false;
      अगर (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      अगर (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	अगर (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_प्रतीक (type));

      वापस false;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

अटल bool
c_parser_require_keyword (c_parser *parser,
			  क्रमागत rid keyword,
			  स्थिर अक्षर *msgid)
{
  अगर (c_parser_अग्र_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      वापस true;
    }
  अन्यथा
    {
      c_parser_error (parser, msgid);
      वापस false;
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

व्योम
c_parser_skip_until_found (c_parser *parser,
			   क्रमागत cpp_ttype type,
			   स्थिर अक्षर *msgid,
			   location_t matching_location)
{
  अचिन्हित nesting_depth = 0;

  अगर (c_parser_require (parser, type, msgid, matching_location))
    {
      अगर (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  अगर (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = शून्य;
	    }
	}
      वापस;
    }

  /* Skip tokens until the desired token is found.  */
  जबतक (true)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      अगर (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  अगर (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      अगर (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = शून्य;
		}
	    }
	  अवरोध;
	}

      /* If we've run out of tokens, stop.  */
      अगर (token->type == CPP_EOF)
	वापस;
      अगर (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	वापस;
      अगर (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      अन्यथा अगर (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  अगर (nesting_depth-- == 0)
	    अवरोध;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = false;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

अटल व्योम
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  अचिन्हित nesting_depth = 0;

  जबतक (true)
    {
      c_token *token = c_parser_peek_token (parser);
      अगर ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	अवरोध;
      /* If we've run out of tokens, stop.  */
      अगर (token->type == CPP_EOF)
	वापस;
      अगर (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	वापस;
      अगर (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      अन्यथा अगर (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  अगर (nesting_depth-- == 0)
	    अवरोध;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = false;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

अटल bool
c_parser_skip_to_closing_brace (c_parser *parser)
{
  अचिन्हित nesting_depth = 0;

  जबतक (true)
    {
      c_token *token = c_parser_peek_token (parser);

      चयन (token->type)
	{
	हाल CPP_PRAGMA_EOL:
	  अगर (!parser->in_pragma)
	    अवरोध;
	  /* FALLTHRU */
	हाल CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  वापस false;

	हाल CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  अगर (nesting_depth-- == 0)
	    वापस true;
	  अवरोध;

	हाल CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  अवरोध;

	शेष:
	  अवरोध;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

अटल व्योम
c_parser_skip_to_pragma_eol (c_parser *parser, bool error_if_not_eol = true)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = false;

  अगर (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  करो
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      अगर (token_type == CPP_EOF)
	अवरोध;
      c_parser_consume_token (parser);
    }
  जबतक (token_type != CPP_PRAGMA_EOL);

  अगर (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      अगर (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = शून्य;
	}
    }

  parser->error = false;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
अटल व्योम
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  क्रम (पूर्णांक depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      चयन (token->type)
	{
	हाल CPP_PRAGMA_EOL:
	  अगर (!parser->in_pragma)
	    अवरोध;
	  /* FALLTHRU */
	हाल CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  वापस;

	हाल CPP_PRAGMA:
	  अगर ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      वृक्ष id1 = c_parser_peek_nth_token (parser, 2)->मूल्य;
	      वृक्ष id2 = c_parser_peek_nth_token (parser, 3)->मूल्य;
	      अगर (म_भेद (IDENTIFIER_POINTER (id1), "declare") == 0
		  && म_भेद (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  अगर (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  अन्यथा
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, false);
	  जारी;

	शेष:
	  अवरोध;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

अटल व्योम
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    bool metadirective_p = false)
{
  अचिन्हित nesting_depth = 0;
  पूर्णांक bracket_depth = 0;
  bool save_error = parser->error;

  जबतक (true)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      चयन (token->type)
	{
	हाल CPP_EOF:
	  वापस;

	हाल CPP_PRAGMA_EOL:
	  अगर (parser->in_pragma)
	    वापस;
	  अवरोध;

	हाल CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  अगर (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      जाओ finished;
	    }
	  अवरोध;

	हाल CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  अगर ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      जाओ finished;
	    }
	  अवरोध;

	हाल CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  अवरोध;

	हाल CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  अगर (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  अवरोध;

	हाल CPP_CLOSE_PAREN:
	  अगर (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  अवरोध;

	हाल CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, false);
	  parser->error = save_error;
	  जारी;

	शेष:
	  अवरोध;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = false;
}

/* CPP's options (initialized by c-opts.cc).  */
बाह्य cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

अटल अंतरभूत पूर्णांक
disable_extension_diagnostics (व्योम)
{
  पूर्णांक ret = (pedantic
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
  वापस ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

अटल अंतरभूत व्योम
restore_extension_diagnostics (पूर्णांक flags)
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
काष्ठा oacc_routine_तथ्य {
  bool error_seen; /* Set if error has been reported.  */
  bool fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  वृक्ष clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
अटल वृक्ष objc_foreach_break_label, objc_foreach_continue_label;

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
काष्ठा omp_for_parse_तथ्य {
  क्रमागत वृक्ष_code code;
  वृक्ष declv, condv, incrv, initv;
  वृक्ष pre_body;
  वृक्ष bindings;
  पूर्णांक गिनती;	/* Expected nesting depth.  */
  पूर्णांक depth;	/* Current nesting depth.  */
  location_t for_loc;
  bool ordered : 1;
  bool inscan : 1;
  bool want_nested_loop : 1;
  bool in_intervening_code : 1;
  bool saw_intervening_code: 1;
  bool perfect_nesting_fail : 1;
  bool हार : 1;
};

काष्ठा attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  bool musttail_p;

  व्योम reset () { musttail_p = false; }
};

अटल bool c_parser_nth_token_starts_std_attributes (c_parser *,
						      अचिन्हित पूर्णांक);
अटल वृक्ष c_parser_std_attribute_specifier_sequence (c_parser *);
अटल व्योम c_parser_external_declaration (c_parser *);
अटल व्योम c_parser_asm_definition (c_parser *);
अटल वृक्ष c_parser_declaration_or_fndef (c_parser *, bool, bool, bool,
					   bool, bool, bool, वृक्ष * = शून्य,
					   vec<c_token> * = शून्य,
					   bool have_attrs = false,
					   वृक्ष attrs = शून्य,
					   काष्ठा oacc_routine_तथ्य * = शून्य,
					   bool * = शून्य);
अटल bool c_parser_handle_statement_omp_attributes (c_parser *, वृक्ष &,
						      bool *);
अटल व्योम c_parser_static_assert_declaration_no_semi (c_parser *);
अटल व्योम c_parser_static_assert_declaration (c_parser *);
अटल काष्ठा c_typespec c_parser_enum_specifier (c_parser *);
अटल काष्ठा c_typespec c_parser_struct_or_union_specifier (c_parser *);
अटल वृक्ष c_parser_struct_declaration (c_parser *, वृक्ष *);
अटल काष्ठा c_typespec c_parser_typeof_specifier (c_parser *);
अटल वृक्ष c_parser_alignas_specifier (c_parser *);
अटल काष्ठा c_declarator *c_parser_direct_declarator (c_parser *, bool,
							c_dtr_syn, bool *);
अटल काष्ठा c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      bool,
							      काष्ठा c_declarator *);
अटल काष्ठा c_arg_info *c_parser_parms_declarator (c_parser *, bool, वृक्ष,
						     bool);
अटल काष्ठा c_arg_info *c_parser_parms_list_declarator (c_parser *, वृक्ष,
							  वृक्ष, bool);
अटल काष्ठा c_parm *c_parser_parameter_declaration (c_parser *, वृक्ष, bool);
अटल वृक्ष c_parser_asm_string_literal (c_parser *);
अटल वृक्ष c_parser_simple_asm_व्यंजक (c_parser *);
अटल वृक्ष c_parser_gnu_attributes (c_parser *);
अटल काष्ठा c_व्यंजक c_parser_initializer (c_parser *, वृक्ष);
अटल काष्ठा c_व्यंजक c_parser_braced_init (c_parser *, वृक्ष, bool,
					   काष्ठा obstack *, bool);
अटल व्योम c_parser_initelt (c_parser *, काष्ठा obstack *);
अटल व्योम c_parser_initval (c_parser *, काष्ठा c_व्यंजक *,
			      काष्ठा obstack *);
अटल वृक्ष c_parser_compound_statement (c_parser *, location_t * = शून्य);
अटल location_t c_parser_compound_statement_nostart (c_parser *);
अटल व्योम c_parser_label (c_parser *, वृक्ष);
अटल व्योम c_parser_statement (c_parser *, bool *, location_t * = शून्य);
अटल व्योम c_parser_statement_after_labels (c_parser *, bool *, वृक्ष,
					     vec<वृक्ष> * = शून्य,
					     attr_state = {});
अटल वृक्ष c_parser_c99_block_statement (c_parser *, bool *,
					  location_t * = शून्य);
अटल व्योम c_parser_if_statement (c_parser *, bool *, vec<वृक्ष> *);
अटल व्योम c_parser_switch_statement (c_parser *, bool *, वृक्ष);
अटल व्योम c_parser_while_statement (c_parser *, bool, अचिन्हित लघु, bool,
				      bool *, वृक्ष);
अटल व्योम c_parser_do_statement (c_parser *, bool, अचिन्हित लघु, bool,
				   वृक्ष);
अटल व्योम c_parser_for_statement (c_parser *, bool, अचिन्हित लघु, bool,
				    bool *, वृक्ष);
अटल वृक्ष c_parser_asm_statement (c_parser *);
अटल वृक्ष c_parser_asm_operands (c_parser *);
अटल वृक्ष c_parser_asm_goto_operands (c_parser *);
अटल वृक्ष c_parser_asm_clobbers (c_parser *);
अटल काष्ठा c_व्यंजक c_parser_व्यंजक_no_commas (c_parser *, काष्ठा c_व्यंजक *,
					      वृक्ष = NULL_वृक्ष);
अटल काष्ठा c_व्यंजक c_parser_conditional_expression (c_parser *,
						      काष्ठा c_व्यंजक *, वृक्ष);
अटल काष्ठा c_व्यंजक c_parser_द्विआधारी_expression (c_parser *, काष्ठा c_व्यंजक *,
						 वृक्ष);
अटल काष्ठा c_व्यंजक c_parser_cast_expression (c_parser *, काष्ठा c_व्यंजक *);
अटल काष्ठा c_व्यंजक c_parser_unary_expression (c_parser *);
अटल काष्ठा c_व्यंजक c_parser_sizeof_or_countof_expression (c_parser *,
							    क्रमागत rid);
अटल काष्ठा c_व्यंजक c_parser_alignof_expression (c_parser *);
अटल काष्ठा c_व्यंजक c_parser_maxof_or_minof_expression (c_parser *, क्रमागत rid);
अटल काष्ठा c_व्यंजक c_parser_postfix_expression (c_parser *);
अटल काष्ठा c_व्यंजक c_parser_postfix_expression_after_paren_type (c_parser *,
								   काष्ठा c_declspecs *,
								   काष्ठा c_type_name *,
								   location_t);
अटल काष्ठा c_व्यंजक c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								काष्ठा c_व्यंजक);
अटल वृक्ष c_parser_transaction (c_parser *, क्रमागत rid);
अटल काष्ठा c_व्यंजक c_parser_transaction_expression (c_parser *, क्रमागत rid);
अटल वृक्ष c_parser_transaction_cancel (c_parser *);
अटल काष्ठा c_व्यंजक c_parser_expression (c_parser *);
अटल काष्ठा c_व्यंजक c_parser_expression_conv (c_parser *);
अटल vec<वृक्ष, va_gc> *c_parser_व्यंजक_list (c_parser *, bool, bool,
					     vec<वृक्ष, va_gc> **, location_t *,
					     वृक्ष *, vec<location_t> *,
					     अचिन्हित पूर्णांक * = शून्य);
अटल काष्ठा c_व्यंजक c_parser_has_attribute_expression (c_parser *);

अटल व्योम c_parser_oacc_declare (c_parser *);
अटल व्योम c_parser_oacc_enter_exit_तथ्य (c_parser *, bool);
अटल व्योम c_parser_oacc_update (c_parser *);
अटल व्योम c_parser_omp_construct (c_parser *, bool *);
अटल व्योम c_parser_omp_groupprivate (c_parser *);
अटल व्योम c_parser_omp_threadprivate (c_parser *);
अटल व्योम c_parser_omp_barrier (c_parser *);
अटल व्योम c_parser_omp_depobj (c_parser *);
अटल व्योम c_parser_omp_flush (c_parser *);
अटल bool c_parser_omp_अग्र_tokens_can_be_canon_loop (c_parser *,
							क्रमागत वृक्ष_code, bool);
अटल वृक्ष c_parser_omp_loop_nest (c_parser *, bool *);
अटल वृक्ष c_parser_omp_for_loop (location_t, c_parser *, क्रमागत वृक्ष_code,
				   वृक्ष, वृक्ष *, bool *);
अटल व्योम c_parser_omp_taskwait (c_parser *);
अटल व्योम c_parser_omp_taskyield (c_parser *);
अटल व्योम c_parser_omp_cancel (c_parser *);
अटल व्योम c_parser_omp_nothing (c_parser *);
अटल व्योम c_parser_omp_metadirective (c_parser *, bool *);

क्रमागत pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
अटल bool c_parser_pragma (c_parser *, क्रमागत pragma_context, bool *, वृक्ष);
अटल bool c_parser_omp_cancellation_point (c_parser *, क्रमागत pragma_context);
अटल bool c_parser_omp_target (c_parser *, क्रमागत pragma_context, bool *);
अटल व्योम c_parser_omp_begin (c_parser *);
अटल व्योम c_parser_omp_end (c_parser *);
अटल bool c_parser_omp_declare (c_parser *, क्रमागत pragma_context);
अटल व्योम c_parser_omp_requires (c_parser *);
अटल bool c_parser_omp_error (c_parser *, क्रमागत pragma_context);
अटल व्योम c_parser_omp_assumption_clauses (c_parser *, bool);
अटल व्योम c_parser_omp_allocate (c_parser *);
अटल व्योम c_parser_omp_assumes (c_parser *);
अटल bool c_parser_omp_ordered (c_parser *, क्रमागत pragma_context, bool *);
अटल वृक्ष c_parser_omp_dispatch (location_t, c_parser *);
अटल व्योम c_parser_omp_interop (c_parser *);
अटल व्योम c_parser_oacc_routine (c_parser *, क्रमागत pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
अटल व्योम c_parser_objc_class_definition (c_parser *, वृक्ष);
अटल व्योम c_parser_objc_class_instance_variables (c_parser *);
अटल व्योम c_parser_objc_class_declaration (c_parser *);
अटल व्योम c_parser_objc_alias_declaration (c_parser *);
अटल व्योम c_parser_objc_protocol_definition (c_parser *, वृक्ष);
अटल bool c_parser_objc_method_type (c_parser *);
अटल व्योम c_parser_objc_method_definition (c_parser *);
अटल व्योम c_parser_objc_methodprotolist (c_parser *);
अटल व्योम c_parser_objc_methodproto (c_parser *);
अटल वृक्ष c_parser_objc_method_decl (c_parser *, bool, वृक्ष *, वृक्ष *);
अटल वृक्ष c_parser_objc_type_name (c_parser *);
अटल वृक्ष c_parser_objc_protocol_refs (c_parser *);
अटल व्योम c_parser_objc_try_catch_finally_statement (c_parser *);
अटल व्योम c_parser_objc_synchronized_statement (c_parser *);
अटल वृक्ष c_parser_objc_selector (c_parser *);
अटल वृक्ष c_parser_objc_selector_arg (c_parser *);
अटल वृक्ष c_parser_objc_receiver (c_parser *);
अटल वृक्ष c_parser_objc_message_args (c_parser *);
अटल वृक्ष c_parser_objc_keywordexpr (c_parser *);
अटल व्योम c_parser_objc_at_property_declaration (c_parser *);
अटल व्योम c_parser_objc_at_synthesize_declaration (c_parser *);
अटल व्योम c_parser_objc_at_dynamic_declaration (c_parser *);
अटल bool c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, काष्ठा c_declspecs *);
अटल location_t c_parser_parse_rtl_body (c_parser *, अक्षर *);
अटल वृक्ष c_parser_handle_musttail (c_parser *, वृक्ष, attr_state &);

#अगर ENABLE_ANALYZER

namespace ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

श्रेणी c_translation_unit : खुला translation_unit
{
खुला:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  वृक्ष lookup_constant_by_id (वृक्ष id) स्थिर final override
  {
    /* Consider decls.  */
    अगर (वृक्ष decl = lookup_name (id))
      अगर (वृक्ष_CODE (decl) == CONST_DECL)
	अगर (वृक्ष मूल्य = DECL_INITIAL (decl))
	  अगर (वृक्ष_CODE (मूल्य) == INTEGER_CST)
	    वापस मूल्य;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    अगर (cpp_macro_p (hashnode))
      अगर (वृक्ष मूल्य = consider_macro (hashnode->मूल्य.macro))
	वापस मूल्य;

    वापस NULL_वृक्ष;
  }

  वृक्ष
  lookup_type_by_id (वृक्ष id) स्थिर final override
  {
    अगर (वृक्ष type_decl = lookup_name (id))
	अगर (वृक्ष_CODE (type_decl) == TYPE_DECL)
	  {
	    वृक्ष record_type = वृक्ष_TYPE (type_decl);
	    अगर (वृक्ष_CODE (record_type) == RECORD_TYPE)
	      वापस record_type;
	  }

    वापस NULL_वृक्ष;
  }

  वृक्ष
  lookup_global_var_by_id (वृक्ष id) स्थिर final override
  {
    अगर (वृक्ष var_decl = lookup_name (id))
      अगर (वृक्ष_CODE (var_decl) == VAR_DECL)
				वापस var_decl;

    वापस NULL_वृक्ष;
  }

निजी:
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
  वृक्ष consider_macro (cpp_macro *macro, पूर्णांक depth = 0) स्थिर
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    अगर (macro->paramc > 0)
      वापस NULL_वृक्ष;
    अगर (macro->kind != cmk_macro)
      वापस NULL_वृक्ष;
    अगर (macro->गिनती != 1)
      वापस NULL_वृक्ष;
    स्थिर cpp_token &tok = macro->exp.tokens[0];
    अगर (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	अगर (depth >= param_analyzer_max_macro_alias_depth)
	  वापस NULL_वृक्ष;

	cpp_hashnode *alias = tok.val.गाँठ.गाँठ;
	अगर (cpp_macro_p (alias))
	  वापस consider_macro (alias->मूल्य.macro, depth + 1);

	/* Not a simple alias.  */
	वापस NULL_वृक्ष;
      }
    अन्यथा अगर (tok.type != CPP_संख्या)
      वापस NULL_वृक्ष;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, शून्य, पंक्ति_table);

    pretty_printer pp;
    pp_string (&pp, (स्थिर अक्षर *) tok.val.str.text);
    pp_newline (&pp);
    cpp_धकेलो_बफर (parse_in,
		     (स्थिर अचिन्हित अक्षर *) pp_formatted_text (&pp),
		     म_माप (pp_formatted_text (&pp)),
		     0);

    वृक्ष मूल्य;
    location_t loc;
    अचिन्हित अक्षर cpp_flags;
    c_lex_with_flags (&मूल्य, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    अगर (मूल्य && वृक्ष_CODE (मूल्य) == INTEGER_CST)
      वापस मूल्य;

    वापस NULL_वृक्ष;
  }
};

} // namespace ana

#पूर्ण_अगर /* #if ENABLE_ANALYZER */

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

अटल व्योम
c_parser_translation_unit (c_parser *parser)
{
  अगर (c_parser_अग्र_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  अन्यथा
    {
      व्योम *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (false);
      करो
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      जबतक (c_parser_अग्र_token_is_not (parser, CPP_EOF));
    }

  अचिन्हित पूर्णांक i;
  वृक्ष decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    अगर (DECL_आकार (decl) == NULL_वृक्ष && वृक्ष_TYPE (decl) != error_mark_गाँठ)
      error ("storage size of %q+D isn%'t known", decl);

  अगर (vec_safe_लंबाई (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->निकालो ();
      अगर (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  अगर (vec_safe_लंबाई (current_omp_begin_assumes))
    {
      अगर (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  अगर (vec_safe_लंबाई (current_omp_declare_variant_attribute))
    {
      अगर (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  अगर (vec_safe_लंबाई (omp_begin_declare_variant_map))
    {
      अचिन्हित पूर्णांक i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#अगर ENABLE_ANALYZER
  अगर (flag_analyzer)
    {
      ana::c_translation_unit tu;
      ana::on_finish_translation_unit (tu);
    }
#पूर्ण_अगर
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

अटल व्योम
c_parser_external_declaration (c_parser *parser)
{
  पूर्णांक ext;
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_KEYWORD:
      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  अवरोध;
	हाल RID_ASM:
	  c_parser_asm_definition (parser);
	  अवरोध;
	हाल RID_AT_INTERFACE:
	हाल RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_वृक्ष);
	  अवरोध;
	हाल RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  अवरोध;
	हाल RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  अवरोध;
	हाल RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_वृक्ष);
	  अवरोध;
	हाल RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  अवरोध;
	हाल RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  अवरोध;
	हाल RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  अवरोध;
	हाल RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  अवरोध;
	शेष:
	  जाओ decl_or_fndef;
	}
      अवरोध;
    हाल CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      अवरोध;
    हाल CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (true);
      c_parser_pragma (parser, pragma_external, शून्य, NULL_वृक्ष);
      mark_valid_location_for_stdc_pragma (false);
      अवरोध;
    हाल CPP_PLUS:
    हाल CPP_MINUS:
      अगर (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  अवरोध;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    शेष:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, true, true, true, false, true,
				     false);
      अवरोध;
    }
}

अटल व्योम c_parser_handle_directive_omp_attributes (वृक्ष &, vec<c_token> *&,
						      vec<c_token> *);
अटल व्योम c_finish_omp_declare_simd (c_parser *, वृक्ष, वृक्ष, vec<c_token> *);
अटल व्योम c_finish_oacc_routine (काष्ठा oacc_routine_तथ्य *, वृक्ष, bool);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

अटल व्योम
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  अगर (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    वापस;

  वृक्ष stmt = build0 (DEBUG_BEGIN_STMT, void_type_गाँठ);
  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

अटल वृक्ष
handle_assume_attribute (location_t here, वृक्ष attrs, bool nested)
{
  अगर (nested)
    क्रम (वृक्ष attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", वृक्ष_CHAIN (attr)))
      {
	वृक्ष args = वृक्ष_मूल्य (attr);
	पूर्णांक nargs = list_लंबाई (args);
	अगर (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	अन्यथा
	  {
	    वृक्ष arg = वृक्ष_मूल्य (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, false, शून्य);
	    अगर (arg != error_mark_गाँठ)
	      {
		वृक्ष fn = build_call_व्यंजक_internal_loc (here, IFN_ASSUME,
							void_type_गाँठ, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  अन्यथा
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  वापस remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

अटल व्योम
c_parser_maybe_reclassify_token (c_parser *parser)
{
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      अगर (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  वृक्ष decl = lookup_name (token->मूल्य);

	  token->id_kind = C_ID_ID;
	  अगर (decl)
	    {
	      अगर (वृक्ष_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  अन्यथा अगर (c_dialect_objc ())
	    {
	      वृक्ष objc_interface_decl = objc_is_class_name (token->मूल्य);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      अगर (objc_interface_decl)
		{
		  token->मूल्य = objc_interface_decl;
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

अटल वृक्ष
c_parser_declaration_or_fndef (c_parser *parser, bool fndef_ok,
			       bool static_assert_ok, bool empty_ok,
			       bool nested, bool start_attr_ok,
			       bool simple_ok,
			       वृक्ष *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       bool have_attrs /* = false */,
			       वृक्ष attrs /* = NULL_TREE */,
			       काष्ठा oacc_routine_तथ्य *oacc_routine_तथ्य
			       /* = NULL */,
			       bool *fallthru_attr_p /* = NULL */)
{
  काष्ठा c_declspecs *specs;
  वृक्ष prefix_attrs;
  वृक्ष all_prefix_attrs;
  bool diagnosed_no_specs = false;
  location_t here = c_parser_peek_token (parser)->location;
  वृक्ष परिणाम = NULL_वृक्ष;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  अगर (static_assert_ok
      && c_parser_अग्र_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      वापस परिणाम;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  अगर (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = false;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  अगर (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->मूल्य)))
    {
      वृक्ष name = c_parser_peek_token (parser)->मूल्य;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      अगर (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_जोड़ो_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      अन्यथा अगर (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_जोड़ो_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      अन्यथा अगर (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_जोड़ो_before ("enum ");
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
	  अगर (स्थिर अक्षर *suggestion = hint.suggestion ())
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
      c_parser_peek_token (parser)->मूल्य = error_mark_गाँठ;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  अगर (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = true;

  c_parser_declspecs (parser, specs, true, true, start_attr_ok,
		      true, true, start_attr_ok, true, cla_nonabstract_decl);
  अगर (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      वापस परिणाम;
    }
  अगर (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      वापस परिणाम;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  अगर (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_शीर्ष_anonymous_type (specs->type);

  bool gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  bool std_auto_type_p = specs->c23_auto_p;
  bool any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  स्थिर अक्षर *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  अगर (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      चयन (specs->typespec_kind)
	{
	हाल ctsk_tagfirstref:
	हाल ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  अवरोध;

	हाल ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  अवरोध;

	शेष:
	  अवरोध;
	}
    }

  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      bool handled_assume = false;
      अगर (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       शून्य))
	{
	  अगर (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  जबतक (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_अग्र_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, शून्य, NULL_वृक्ष);
	    }
	  c_parser_consume_token (parser);
	  वापस परिणाम;
	}
      अगर (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = true;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      अगर (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      अन्यथा अगर (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  अगर (fallthru_attr_p != शून्य)
	    *fallthru_attr_p = true;
	  अगर (nested)
	    {
	      वृक्ष fn = build_call_व्यंजक_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_गाँठ, 0);
	      add_stmt (fn);
	    }
	  अन्यथा
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      अन्यथा अगर (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      अन्यथा
	{
	  shadow_tag_warned (specs, 1);
	  अगर (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      अगर (specs->व्यंजक)
	add_stmt (fold_convert (void_type_गाँठ, specs->व्यंजक));
      c_parser_consume_token (parser);
      अगर (oacc_routine_तथ्य)
	c_finish_oacc_routine (oacc_routine_तथ्य, NULL_वृक्ष, false);
      वापस परिणाम;
    }
  अन्यथा अगर (specs->typespec_kind == ctsk_none
	   && nested
	   /* Only parse __attribute__((musttail)) when called from
	      c_parser_compound_statement_nostart.  This certainly isn't
	      a declaration in that case, but we don't do tentative parsing
	      of GNU attributes right now.  */
	   && fallthru_attr_p
	   && c_parser_अग्र_token_is_keyword (parser, RID_RETURN))
    {
      attr_state astate = {};
      specs->attrs = c_parser_handle_musttail (parser, specs->attrs, astate);
      अगर (astate.musttail_p)
	{
	  अगर (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, शून्य, NULL_वृक्ष, शून्य,
					   astate);
	  वापस परिणाम;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  अगर (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_अग्र_token_starts_declspecs (parser)
      && !c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = false;
      shadow_tag_warned (specs, 1);
      वापस परिणाम;
    }
  अन्यथा अगर (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      चयन (c_parser_peek_token (parser)->type)
	{
	  हाल CPP_PLUS:
	  हाल CPP_MINUS:
	    अगर (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      वापस परिणाम;
	    अगर (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_वृक्ष;
	      }
	    अगर (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    अन्यथा
	      c_parser_objc_methodproto (parser);
	    वापस परिणाम;
	    अवरोध;
	  शेष:
	    अवरोध;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_AT_INTERFACE:
	  {
	    अगर (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      वापस परिणाम;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    वापस परिणाम;
	  }
	  अवरोध;
	हाल RID_AT_IMPLEMENTATION:
	  {
	    अगर (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      वापस परिणाम;
	    अगर (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_वृक्ष;
	      }
	    c_parser_objc_class_definition (parser, NULL_वृक्ष);
	    वापस परिणाम;
	  }
	  अवरोध;
	हाल RID_AT_PROTOCOL:
	  {
	    अगर (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      वापस परिणाम;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    वापस परिणाम;
	  }
	  अवरोध;
	हाल RID_AT_ALIAS:
	हाल RID_AT_CLASS:
	हाल RID_AT_END:
	हाल RID_AT_PROPERTY:
	  अगर (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = शून्य;
	    }
	  अवरोध;
	शेष:
	  अवरोध;
	}
    }
  अन्यथा अगर (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  अन्यथा अगर (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_वृक्ष;
  bool more_than_one_decl = false;
  जबतक (true)
    {
      काष्ठा c_declarator *declarator;
      bool dummy = false;
      timevar_id_t tv;
      वृक्ष fnbody = NULL_वृक्ष;
      वृक्ष underspec_name = NULL_वृक्ष;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      अगर (declarator == शून्य)
	{
	  अगर (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_वृक्ष, NULL_वृक्ष,
				       omp_declare_simd_clauses);
	  अगर (oacc_routine_तथ्य)
	    c_finish_oacc_routine (oacc_routine_तथ्य, NULL_वृक्ष, false);
	  /* This check is here purely to improve the diagnostic.  */
	  अगर (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  वापस परिणाम;
	}
      अगर (flag_openmp || flag_openmp_simd)
	{
	  काष्ठा c_declarator *d = declarator;
	  जबतक (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = शून्य;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      अगर (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  वापस परिणाम;
	}
      अगर (std_auto_type_p)
	{
	  काष्ठा c_declarator *d = declarator;
	  जबतक (d->kind == cdk_attrs)
	    d = d->declarator;
	  अगर (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      वापस परिणाम;
	    }
	  underspec_name = d->u.id.id;
	}
      अन्यथा अगर (specs->constexpr_p)
	{
	  काष्ठा c_declarator *d = declarator;
	  जबतक (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_EQ)
	  || c_parser_अग्र_token_is (parser, CPP_COMMA)
	  || c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
	  || c_parser_अग्र_token_is_keyword (parser, RID_ASM)
	  || c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_अग्र_token_is_keyword (parser, RID_IN))
	{
	  वृक्ष asm_name = NULL_वृक्ष;
	  वृक्ष postfix_attrs = NULL_वृक्ष;
	  अगर (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = true;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = false;
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_व्यंजक (parser);
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  वापस परिणाम;
		}
	    }
	  अगर (c_parser_अग्र_token_is (parser, CPP_EQ))
	    {
	      वृक्ष d;
	      काष्ठा c_व्यंजक init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      अगर (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पंक्ति_table, init_loc);
		  अचिन्हित पूर्णांक underspec_state = 0;
		  अगर (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_वृक्ष, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  अगर (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_व्यंजक_no_commas (parser, शून्य);
		  अगर (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  अगर (gnu_auto_type_p
		      && वृक्ष_CODE (init.मूल्य) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (वृक्ष_OPERAND (init.मूल्य, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, true, true,
						   true);
		  वृक्ष init_type = वृक्ष_TYPE (init.मूल्य);
		  bool vm_type = c_type_variably_modified_p (init_type);
		  अगर (vm_type)
		    init.मूल्य = save_व्यंजक (init.मूल्य);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = true;
		  specs->type = init_type;
		  अगर (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_वृक्ष;
		    }
		  अगर (vm_type)
		    {
		      bool maybe_const = true;
		      वृक्ष type_व्यंजक = c_fully_fold (init.मूल्य, false,
						     &maybe_const);
		      specs->व्यंजक_const_operands &= maybe_const;
		      अगर (specs->व्यंजक)
			specs->व्यंजक = build2 (COMPOUND_व्यंजक,
					      वृक्ष_TYPE (type_व्यंजक),
					      specs->व्यंजक, type_व्यंजक);
		      अन्यथा
			specs->व्यंजक = type_व्यंजक;
		    }
		  d = start_decl (declarator, specs, true,
				  chainon (postfix_attrs, all_prefix_attrs));
		  अगर (!d)
		    d = error_mark_गाँठ;
		  अगर (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्ष,
					       omp_declare_simd_clauses);
		  अगर (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्ष,
					       &omp_dsimd_idattr_clauses);
		}
	      अन्यथा
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पंक्ति_table, init_loc);
		  अचिन्हित पूर्णांक underspec_state = 0;
		  अगर (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, true,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  अगर (!d)
		    d = error_mark_गाँठ;
		  अगर (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्ष,
					       omp_declare_simd_clauses);
		  अगर (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्ष,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      वृक्ष_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  अगर (वृक्ष_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  अगर (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      अगर (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_वृक्ष,
						   omp_declare_simd_clauses);
		  अगर (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_वृक्ष,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      अगर (oacc_routine_तथ्य)
		c_finish_oacc_routine (oacc_routine_तथ्य, d, false);
	      अगर (d != error_mark_गाँठ)
		{
		  maybe_warn_string_init (init_loc, वृक्ष_TYPE (d), init);
		  finish_decl (d, init_loc, init.मूल्य,
			       init.original_type, asm_name);
		  परिणाम = d;
		}
	    }
	  अन्यथा
	    {
	      अगर (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  वापस परिणाम;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      वृक्ष attrs = chainon (postfix_attrs, all_prefix_attrs);
	      वृक्ष d = start_decl (declarator, specs, false, attrs, true,
				   &lastloc);
	      अगर (d && वृक्ष_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  स्थिर काष्ठा c_declarator *decl = declarator;
		  स्थिर काष्ठा c_declarator *last_non_id_attrs = शून्य;

		  जबतक (decl)
		    चयन (decl->kind)
		      {
		      हाल cdk_array:
		      हाल cdk_function:
		      हाल cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			अवरोध;

		      हाल cdk_attrs:
			decl = decl->declarator;
			अवरोध;

		      हाल cdk_id:
			decl = 0;
			अवरोध;

		      शेष:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  अगर (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      वृक्ष parms = last_non_id_attrs->u.arg_info->parms;
		      अगर (DECL_ARGUMENTS (d) == NULL_वृक्ष
			  && DECL_INITIAL (d) == NULL_वृक्ष)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      अगर (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  वृक्ष parms = NULL_वृक्ष;
		  अगर (d && वृक्ष_CODE (d) == FUNCTION_DECL)
		    {
		      काष्ठा c_declarator *ce = declarator;
		      जबतक (ce != शून्य)
			अगर (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    अवरोध;
			  }
			अन्यथा
			  ce = ce->declarator;
		    }
		  अगर (parms)
		    अस्थायी_store_parm_decls (d, parms);
		  अगर (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  अगर (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  अगर (parms)
		    अस्थायी_निकालो_parm_decls ();
		}
	      अगर (oacc_routine_तथ्य)
		c_finish_oacc_routine (oacc_routine_तथ्य, d, false);
	      अगर (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_वृक्ष,
			     NULL_वृक्ष, asm_name);

	      अगर (c_parser_अग्र_token_is_keyword (parser, RID_IN))
		{
		  अगर (d)
		    *objc_foreach_object_declaration = d;
		  अन्यथा
		    *objc_foreach_object_declaration = error_mark_गाँठ;
		}
	    }
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = true;
	      अगर (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  वापस परिणाम;
		}
	      c_parser_consume_token (parser);
	      अगर (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      अन्यथा
		all_prefix_attrs = prefix_attrs;
	      जारी;
	    }
	  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	    {
	      अगर (!simple_ok)
		c_parser_consume_token (parser);
	      वापस परिणाम;
	    }
	  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      वापस परिणाम;
	    }
	  अन्यथा
	    {
	      अगर (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      अन्यथा अगर (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      वापस परिणाम;
	    }
	}
      अन्यथा अगर (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  वापस परिणाम;
	}
      अन्यथा अगर (!fndef_ok)
	{
	  अगर (simple_ok && c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  अन्यथा
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  वापस परिणाम;
	}
      /* Function definition (nested or otherwise).  */
      अगर (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_धकेलो_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      वृक्ष dv_base = NULL_वृक्ष;
      वृक्ष dv_ctx = NULL_वृक्ष;
      अगर (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      अगर (!start_function (specs, declarator, all_prefix_attrs))
	{
	  /* At this point we've consumed:
	       declaration-specifiers declarator
	     and the next token isn't CPP_EQ, CPP_COMMA, CPP_SEMICOLON,
	     RID_ASM, RID_ATTRIBUTE, or RID_IN,
	     but the
	       declaration-specifiers declarator
	     aren't grokkable as a function definition, so we have
	     an error.  */
	  gcc_assert (!c_parser_अग्र_token_is (parser, CPP_SEMICOLON));
	  अगर (c_parser_अग्र_token_starts_declspecs (parser))
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
	      parser->error = false;
	    }
	  अन्यथा
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  अगर (nested)
	    c_निकालो_function_context ();
	  अवरोध;
	}

      अगर (DECL_DECLARED_INLINE_P (current_function_decl))
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
      पूर्णांक save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      जबतक (c_parser_अग्र_token_is_not (parser, CPP_EOF)
	     && c_parser_अग्र_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, false, false, false,
				       true, false, false);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      अगर (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_वृक्ष,
				   omp_declare_simd_clauses);
      अगर (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_वृक्ष,
				   &omp_dsimd_idattr_clauses);
      अगर (oacc_routine_तथ्य)
	c_finish_oacc_routine (oacc_routine_तथ्य, current_function_decl, true);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      अगर (dv_base && current_function_decl != error_mark_गाँठ)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_धकेलो (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      अगर (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  धकेलो_scope ();
	  निकालो_scope ();

	  finish_function (endloc);
	  वापस परिणाम;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      अन्यथा अगर (specs->declspec_il != cdil_none)
	{
	  bool saved = in_late_द्विआधारी_op;
	  in_late_द्विआधारी_op = true;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_गिनती);
	  in_late_द्विआधारी_op = saved;
	}
      अन्यथा
	fnbody = c_parser_compound_statement (parser, &endloc);
      वृक्ष fndecl = current_function_decl;
      अगर (nested && specs->declspec_il == cdil_none)
	{
	  वृक्ष decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_निकालो_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_व्यंजक, decl));
	}
      अन्यथा अगर (nested)
	{
	  अगर (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  अन्यथा
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_निकालो_function_context ();
	}
      अन्यथा
	{
	  अगर (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      अगर (specs->declspec_il != cdil_none)
	DECL_SAVED_वृक्ष (fndecl) = NULL_वृक्ष;

      अवरोध;
    }

  वापस परिणाम;
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

अटल व्योम
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  वृक्ष asm_str = NULL_वृक्ष;
  वृक्ष outputs = NULL_वृक्ष, inputs = NULL_वृक्ष;
  अगर (!parens.require_open (parser))
    जाओ done;
  asm_str = c_parser_asm_string_literal (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      जाओ done;
    }
  क्रम (पूर्णांक section = 0; section < 2; ++section)
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  अगर (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	      asm_str = NULL_वृक्ष;
	      जाओ done;
	    }
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, false))
	जाओ error_close_paren;
      अगर (!c_parser_अग्र_token_is (parser, CPP_COLON)
	  && !c_parser_अग्र_token_is (parser, CPP_SCOPE)
	  && !c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	{
	  अगर (section)
	    inputs = c_parser_asm_operands (parser);
	  अन्यथा
	    outputs = c_parser_asm_operands (parser);
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	अवरोध;
    }

  अगर (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
      asm_str = NULL_वृक्ष;
    }

  अगर (asm_str)
    asm_str = build_asm_व्यंजक (asm_loc, asm_str, outputs, inputs,
			      NULL_वृक्ष, NULL_वृक्ष, false, false);
done:
  अगर (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

अटल व्योम
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  अगर (parser->error
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

अटल व्योम
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, मूल्य_loc;
  वृक्ष मूल्य;
  वृक्ष string = NULL_वृक्ष;

  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_STATIC_ASSERT));
  वृक्ष spelling = c_parser_peek_token (parser)->मूल्य;
  assert_loc = c_parser_peek_token (parser)->location;
  अगर (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  अन्यथा
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस;
  location_t मूल्य_tok_loc = c_parser_peek_token (parser)->location;
  मूल्य = convert_lvalue_to_rvalue (मूल्य_tok_loc,
				    c_parser_व्यंजक_no_commas (parser, शून्य),
				    true, true).मूल्य;
  मूल्य_loc = व्यंजक_LOC_OR_LOC (मूल्य, मूल्य_tok_loc);
  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_STRING:
	हाल CPP_STRING16:
	हाल CPP_STRING32:
	हाल CPP_WSTRING:
	हाल CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, false, true).मूल्य;
	  अवरोध;
	शेष:
	  c_parser_error (parser, "expected string literal");
	  वापस;
	}
    }
  अन्यथा अगर (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (मूल्य)))
    {
      error_at (मूल्य_loc, "expression in static assertion is not an integer");
      वापस;
    }
  अगर (वृक्ष_CODE (मूल्य) != INTEGER_CST)
    {
      मूल्य = c_fully_fold (मूल्य, false, शून्य);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (मूल्य);
      अगर (वृक्ष_CODE (मूल्य) == INTEGER_CST)
	pedwarn (मूल्य_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  अगर (वृक्ष_CODE (मूल्य) != INTEGER_CST)
    {
      error_at (मूल्य_loc, "expression in static assertion is not constant");
      वापस;
    }
  constant_expression_warning (मूल्य);
  अगर (integer_zerop (मूल्य))
    {
      अगर (string)
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

व्योम
c_parser_declspecs (c_parser *parser, काष्ठा c_declspecs *specs,
		    bool scspec_ok, bool typespec_ok, bool start_attr_ok,
		    bool alignspec_ok, bool auto_type_ok,
		    bool start_std_attr_ok, bool end_std_attr_ok,
		    क्रमागत c_lookahead_kind la)
{
  bool attrs_ok = start_attr_ok;
  bool seen_type = specs->typespec_kind != ctsk_none;

  अगर (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  अगर (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      वृक्ष attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = false;
    }

  जबतक (c_parser_अग्र_token_is (parser, CPP_NAME)
	 || c_parser_अग्र_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_अग्र_token_is (parser, CPP_LESS)))
    {
      काष्ठा c_typespec t;
      वृक्ष attrs;
      वृक्ष align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      अगर ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_अग्र_tokens_start_typename (parser, la)
	  && !c_parser_अग्र_token_is_qualifier (parser)
	  && !c_parser_अग्र_token_is_keyword (parser, RID_ALIGNAS))
	अवरोध;

      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  वृक्ष मूल्य = name_token->मूल्य;
	  c_id_kind kind = name_token->id_kind;

	  अगर (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = true;
	      जारी;
	    }

	  gcc_assert (!c_parser_अग्र_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  अगर (seen_type || !c_parser_अग्र_tokens_start_typename (parser, la))
	    अवरोध;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = true;
	  attrs_ok = true;
	  अगर (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (मूल्य, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      अगर (स्थिर अक्षर *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    मूल्य, suggestion);
		}
	      अन्यथा
		error_at (loc, "unknown type name %qE", मूल्य);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_गाँठ;
	    }
	  अन्यथा अगर (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_अग्र_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (मूल्य);
	    }
	  अन्यथा
	    {
	      वृक्ष proto = NULL_वृक्ष;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      अगर (c_parser_अग्र_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (मूल्य, proto);
	    }
	  t.व्यंजक = NULL_वृक्ष;
	  t.व्यंजक_const_operands = true;
	  t.has_enum_type_specifier = false;
	  declspecs_add_type (name_token->location, specs, t);
	  जारी;
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  वृक्ष proto;
	  gcc_assert (c_dialect_objc ());
	  अगर (!typespec_ok || seen_type)
	    अवरोध;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_वृक्ष, proto);
	  t.व्यंजक = NULL_वृक्ष;
	  t.व्यंजक_const_operands = true;
	  t.has_enum_type_specifier = false;
	  declspecs_add_type (loc, specs, t);
	  जारी;
	}
      gcc_assert (c_parser_अग्र_token_is (parser, CPP_KEYWORD));
      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_STATIC:
	हाल RID_EXTERN:
	हाल RID_REGISTER:
	हाल RID_TYPEDEF:
	हाल RID_INLINE:
	हाल RID_NORETURN:
	हाल RID_AUTO:
	हाल RID_THREAD:
	हाल RID_CONSTEXPR:
	  अगर (!scspec_ok)
	    जाओ out;
	  attrs_ok = true;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->मूल्य);
	  c_parser_consume_token (parser);
	  अवरोध;
	हाल RID_AUTO_TYPE:
	  अगर (!auto_type_ok)
	    जाओ out;
	  /* Fall through.  */
	हाल RID_UNSIGNED:
	हाल RID_LONG:
	हाल RID_SHORT:
	हाल RID_SIGNED:
	हाल RID_COMPLEX:
	हाल RID_INT:
	हाल RID_CHAR:
	हाल RID_FLOAT:
	हाल RID_DOUBLE:
	हाल RID_VOID:
	हाल RID_DFLOAT32:
	हाल RID_DFLOAT64:
	हाल RID_DFLOAT128:
	हाल RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	हाल RID_BOOL:
	हाल RID_FRACT:
	हाल RID_ACCUM:
	हाल RID_SAT:
	हाल RID_INT_N_0:
	हाल RID_INT_N_1:
	हाल RID_INT_N_2:
	हाल RID_INT_N_3:
	  अगर (!typespec_ok)
	    जाओ out;
	  attrs_ok = true;
	  seen_type = true;
	  अगर (c_dialect_objc ())
	    parser->objc_need_raw_identifier = true;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->मूल्य;
	  t.व्यंजक = NULL_वृक्ष;
	  t.व्यंजक_const_operands = true;
	  t.has_enum_type_specifier = false;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  अवरोध;
	हाल RID_ENUM:
	  अगर (!typespec_ok)
	    जाओ out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  अवरोध;
	हाल RID_STRUCT:
	हाल RID_UNION:
	  अगर (!typespec_ok)
	    जाओ out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  अवरोध;
	हाल RID_TYPEOF:
	हाल RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  अगर (!typespec_ok || seen_type)
	    जाओ out;
	  attrs_ok = true;
	  seen_type = true;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  अवरोध;
	हाल RID_BITINT:
	  अगर (!typespec_ok)
	    जाओ out;
	  अन्यथा
	    {
	      attrs_ok = true;
	      seen_type = true;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->मूल्य;
	      t.व्यंजक = error_mark_गाँठ;
	      t.व्यंजक_const_operands = true;
	      t.has_enum_type_specifier = false;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      अगर (parens.require_open (parser))
		{
		  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
		  t.व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, true,
						     true).मूल्य;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  अवरोध;
	हाल RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  अगर (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  अगर (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  अन्यथा
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = true;
	  वृक्ष मूल्य;
	  मूल्य = c_parser_peek_token (parser)->मूल्य;
	  c_parser_consume_token (parser);
	  अगर (typespec_ok && c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = true;
	      c_parser_consume_token (parser);
	      काष्ठा c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_गाँठ;
	      t.व्यंजक = NULL_वृक्ष;
	      t.व्यंजक_const_operands = true;
	      t.has_enum_type_specifier = false;
	      अगर (type != शून्य)
		t.spec = groktypename (type, &t.व्यंजक,
				       &t.व्यंजक_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      अगर (t.spec != error_mark_गाँठ)
		{
		  अगर (वृक्ष_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  अन्यथा अगर (वृक्ष_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  अन्यथा अगर (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  अन्यथा
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  अन्यथा
	    declspecs_add_qual (loc, specs, मूल्य);
	  अवरोध;
	हाल RID_CONST:
	हाल RID_VOLATILE:
	हाल RID_RESTRICT:
	  attrs_ok = true;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->मूल्य);
	  c_parser_consume_token (parser);
	  अवरोध;
	हाल RID_ATTRIBUTE:
	  अगर (!attrs_ok)
	    जाओ out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  अवरोध;
	हाल RID_ALIGNAS:
	  अगर (!alignspec_ok)
	    जाओ out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  अवरोध;
	हाल RID_GIMPLE:
	  अगर (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  अवरोध;
	हाल RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  अवरोध;
	शेष:
	  जाओ out;
	}
    }
 out:
  अगर (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

अटल व्योम
report_bad_enum_name (c_parser *parser)
{
  अगर (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      चयन (token->type)
	{
	शेष:
	  अवरोध;
	हाल CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = true;
	  वापस;
	हाल CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  अगर (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->मूल्य));
	      add_note_about_new_keyword (token->location,
					  token->मूल्य);
	      parser->error = true;
	      वापस;
	    }
	  अवरोध;
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

अटल काष्ठा c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  काष्ठा c_typespec ret;
  bool have_std_attrs;
  bool potential_nesting_p = false;
  वृक्ष std_attrs = NULL_वृक्ष;
  वृक्ष attrs;
  वृक्ष ident = NULL_वृक्ष;
  वृक्ष fixed_underlying_type = NULL_वृक्ष;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  अगर (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->मूल्य;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  अगर (c_parser_अग्र_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      अगर (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, true);
	  अगर (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_वृक्ष == TYPE_मूल्यावली (ret.spec);
	}
      अन्यथा
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_वृक्ष;
	  ret.kind = ctsk_tagdef;
	  ret.व्यंजक = NULL_वृक्ष;
	  ret.व्यंजक_const_operands = true;
	  ret.has_enum_type_specifier = true;
	}
      c_parser_consume_token (parser);
      काष्ठा c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, false, true, false, false, false,
			  false, true, cla_prefer_id);
      finish_declspecs (specs);
      अगर (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      अन्यथा अगर (वृक्ष_CODE (specs->type) != INTEGER_TYPE
	       && वृक्ष_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || वृक्ष_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_गाँठ;
	}
      अन्यथा अगर (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      अगर (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  अगर (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_वृक्ष)
	    {
	      TYPE_MIN_मूल्य (ret.spec) =
		TYPE_MIN_मूल्य (fixed_underlying_type);
	      TYPE_MAX_मूल्य (ret.spec) =
		TYPE_MAX_मूल्य (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_आकार (ret.spec) = NULL_वृक्ष;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  अन्यथा अगर (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      काष्ठा c_enum_contents the_enum;
      वृक्ष type;
      वृक्ष postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      वृक्ष मूल्यावली;
      timevar_धकेलो (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      मूल्यावली = NULL_वृक्ष;
      c_parser_consume_token (parser);
      जबतक (true)
	{
	  वृक्ष enum_id;
	  वृक्ष enum_मूल्य;
	  वृक्ष enum_decl;
	  bool seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, मूल्य_loc;
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, शून्य);
	      मूल्यावली = error_mark_गाँठ;
	      अवरोध;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->मूल्य;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = मूल्य_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  वृक्ष std_attrs = NULL_वृक्ष;
	  अगर (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  वृक्ष enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  अगर (c_parser_अग्र_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      मूल्य_loc = c_parser_peek_token (parser)->location;
	      enum_मूल्य = convert_lvalue_to_rvalue (मूल्य_loc,
						     (c_parser_व्यंजक_no_commas
						      (parser, शून्य)),
						     true, true).मूल्य;
	    }
	  अन्यथा
	    enum_मूल्य = NULL_वृक्ष;
	  enum_decl = build_enumerator (decl_loc, मूल्य_loc,
					&the_enum, enum_id, enum_मूल्य);
	  अगर (enum_attrs)
	    decl_attributes (&वृक्ष_PURPOSE (enum_decl), enum_attrs, 0);
	  वृक्ष_CHAIN (enum_decl) = मूल्यावली;
	  मूल्यावली = enum_decl;
	  seen_comma = false;
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = true;
	      c_parser_consume_token (parser);
	    }
	  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      अगर (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      अवरोध;
	    }
	  अगर (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, शून्य);
	      मूल्यावली = error_mark_गाँठ;
	      अवरोध;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (मूल्यावली),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.व्यंजक = NULL_वृक्ष;
      ret.व्यंजक_const_operands = true;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_वृक्ष;
      timevar_निकालो (TV_PARSE_ENUM);
      वापस ret;
    }
  अन्यथा अगर (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_गाँठ;
      ret.kind = ctsk_tagref;
      ret.व्यंजक = NULL_वृक्ष;
      ret.व्यंजक_const_operands = true;
      ret.has_enum_type_specifier = false;
      वापस ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  अगर (have_std_attrs && c_parser_अग्र_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  अगर (fixed_underlying_type == NULL_वृक्ष)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, false);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      अगर (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  वापस ret;
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

अटल काष्ठा c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  काष्ठा c_typespec ret;
  bool have_std_attrs;
  वृक्ष std_attrs = NULL_वृक्ष;
  वृक्ष attrs;
  वृक्ष ident = NULL_वृक्ष;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  क्रमागत वृक्ष_code code;
  चयन (c_parser_peek_token (parser)->keyword)
    {
    हाल RID_STRUCT:
      code = RECORD_TYPE;
      अवरोध;
    हाल RID_UNION:
      code = UNION_TYPE;
      अवरोध;
    शेष:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  अगर (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->मूल्य;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      श्रेणी c_struct_parse_info *struct_info;
      वृक्ष type = start_struct (struct_loc, code, ident, &struct_info);
      वृक्ष postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      वृक्ष contents;
      वृक्ष व्यंजक = शून्य;
      timevar_धकेलो (TV_PARSE_STRUCT);
      contents = NULL_वृक्ष;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_DEFS))
	{
	  वृक्ष name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  अगर (!parens.require_open (parser))
	    जाओ end_at_defs;
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->मूल्य;
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	      जाओ end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      जबतक (true)
	{
	  वृक्ष decls;
	  /* Parse any stray semicolon.  */
	  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
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
	  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      अवरोध;
	    }
	  /* Accept #pragmas at struct scope.  */
	  अगर (c_parser_अग्र_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, शून्य, NULL_वृक्ष);
	      जारी;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &व्यंजक);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  अन्यथा
	    {
	      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      अन्यथा अगर (parser->error
		       || !c_parser_अग्र_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, शून्य);
		  अवरोध;
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
				struct_info, &व्यंजक);
      ret.kind = ctsk_tagdef;
      ret.व्यंजक = व्यंजक;
      ret.व्यंजक_const_operands = true;
      ret.has_enum_type_specifier = false;
      timevar_निकालो (TV_PARSE_STRUCT);
      वापस ret;
    }
  अन्यथा अगर (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_गाँठ;
      ret.kind = ctsk_tagref;
      ret.व्यंजक = NULL_वृक्ष;
      ret.व्यंजक_const_operands = true;
      ret.has_enum_type_specifier = false;
      वापस ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  अगर (have_std_attrs && c_parser_अग्र_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 false);
  वापस ret;
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

अटल वृक्ष
c_parser_struct_declaration (c_parser *parser, वृक्ष *व्यंजक)
{
  काष्ठा c_declspecs *specs;
  वृक्ष prefix_attrs;
  वृक्ष all_prefix_attrs;
  वृक्ष decls;
  location_t decl_loc;
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_EXTENSION))
    {
      पूर्णांक ext;
      वृक्ष decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, व्यंजक);
      restore_extension_diagnostics (ext);
      वापस decl;
    }
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      वापस NULL_वृक्ष;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, false, true, true,
		      true, false, true, true, cla_nonabstract_decl);
  अगर (parser->error)
    वापस NULL_वृक्ष;
  अगर (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      वापस NULL_वृक्ष;
    }
  finish_declspecs (specs);
  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
      || c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
    {
      वृक्ष ret;
      अगर (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_वृक्ष;
	}
      अन्यथा
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  वृक्ष attrs = शून्य;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_वृक्ष), specs,
			   NULL_वृक्ष, &attrs, व्यंजक);
	  अगर (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      वापस ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  अगर (specs->typespec_kind == ctsk_tagdef
      && वृक्ष_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_अग्र_token_starts_declspecs (parser)
      && !c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = false;
      वापस NULL_वृक्ष;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_वृक्ष;
  decls = NULL_वृक्ष;
  जबतक (true)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      काष्ठा c_declarator *declarator;
      bool dummy = false;
      अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_वृक्ष);
      अन्यथा
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      अगर (declarator == शून्य)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  अवरोध;
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_COLON)
	  || c_parser_अग्र_token_is (parser, CPP_COMMA)
	  || c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
	  || c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  वृक्ष postfix_attrs = NULL_वृक्ष;
	  वृक्ष width = NULL_वृक्ष;
	  वृक्ष d;
	  अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_व्यंजक_no_commas
						 (parser, शून्य)),
						true, true).मूल्य;
	    }
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, व्यंजक);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  अन्यथा
	    all_prefix_attrs = prefix_attrs;
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
		   || c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      अवरोध;
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      अवरोध;
	    }
	}
      अन्यथा
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  अवरोध;
	}
    }
  वापस decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

अटल काष्ठा c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  bool is_unqual;
  bool is_std;
  काष्ठा c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_गाँठ;
  ret.व्यंजक = NULL_वृक्ष;
  ret.व्यंजक_const_operands = true;
  ret.has_enum_type_specifier = false;
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = false;
      वृक्ष spelling = c_parser_peek_token (parser)->मूल्य;
      is_std = (flag_isoc23
		&& म_भेद (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  अन्यथा
    {
      gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = true;
      वृक्ष spelling = c_parser_peek_token (parser)->मूल्य;
      is_std = म_भेद (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  अगर (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      वापस ret;
    }
  अगर (c_parser_अग्र_tokens_start_typename (parser, cla_prefer_id))
    {
      काष्ठा c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      अगर (type != शून्य)
	{
	  ret.spec = groktypename (type, &ret.व्यंजक, &ret.व्यंजक_const_operands);
	  निकालो_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  अन्यथा
    {
      bool was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      काष्ठा c_व्यंजक व्यंजक = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      अगर (वृक्ष_CODE (व्यंजक.मूल्य) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्ष_OPERAND (व्यंजक.मूल्य, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (व्यंजक.मूल्य);
      ret.spec = वृक्ष_TYPE (व्यंजक.मूल्य);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      अगर (was_vm)
	ret.व्यंजक = c_fully_fold (व्यंजक.मूल्य, false, &ret.व्यंजक_const_operands);
      निकालो_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  अगर (ret.spec != error_mark_गाँठ)
    {
      अगर (is_unqual)
	{
	  bool is_array = वृक्ष_CODE (ret.spec) == ARRAY_TYPE;
	  पूर्णांक quals = TYPE_QUALS (strip_array_types (ret.spec));
	  अगर ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      अगर (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      अगर (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  अगर (वृक्ष_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  अन्यथा अगर (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (वृक्ष_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (वृक्ष_TYPE (ret.spec)));
	}
    }
  वापस ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

अटल वृक्ष
c_parser_alignas_specifier (c_parser * parser)
{
  वृक्ष ret = error_mark_गाँठ;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_ALIGNAS));
  वृक्ष spelling = c_parser_peek_token (parser)->मूल्य;
  c_parser_consume_token (parser);
  अगर (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  अन्यथा
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस ret;
  अगर (c_parser_अग्र_tokens_start_typename (parser, cla_prefer_id))
    {
      काष्ठा c_type_name *type = c_parser_type_name (parser);
      अगर (type != शून्य)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, शून्य, शून्य),
					false, true, 1);
    }
  अन्यथा
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_व्यंजक_no_commas (parser, शून्य),
				    true, true).मूल्य;
  parens.skip_until_found_close (parser);
  वापस ret;
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

काष्ठा c_declarator *
c_parser_declarator (c_parser *parser, bool type_seen_p, c_dtr_syn kind,
		     bool *seen_id)
{
  /* Parse any initial pointer part.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_MULT))
    {
      काष्ठा c_declspecs *quals_attrs = build_null_declspecs ();
      काष्ठा c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, false, false, true,
			  false, false, true, false, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      अगर (inner == शून्य)
	वापस शून्य;
      अन्यथा
	वापस make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  वापस c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

अटल काष्ठा c_declarator *
c_parser_direct_declarator (c_parser *parser, bool type_seen_p, c_dtr_syn kind,
			    bool *seen_id)
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

  अगर (kind != C_DTR_ABSTRACT
      && c_parser_अग्र_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      काष्ठा c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->मूल्य);
      *seen_id = true;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      अगर (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      वापस c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  अगर (kind != C_DTR_NORMAL
      && c_parser_अग्र_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      काष्ठा c_declarator *inner = build_id_declarator (NULL_वृक्ष);
      inner->id_loc = c_parser_peek_token (parser)->location;
      वापस c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      वृक्ष attrs;
      काष्ठा c_declarator *inner;
      c_parser_consume_token (parser);
      bool have_gnu_attrs = c_parser_अग्र_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      अगर (kind != C_DTR_NORMAL
	  && (c_parser_अग्र_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_अग्र_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  काष्ठा c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  अगर (args == शून्य)
	    वापस शून्य;
	  अन्यथा
	    {
	      inner = build_id_declarator (NULL_वृक्ष);
	      अगर (!(args->types
		    && args->types != error_mark_गाँठ
		    && वृक्ष_CODE (वृक्ष_मूल्य (args->types)) == IDENTIFIER_गाँठ)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  वृक्ष std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  अगर (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      वापस c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      अगर (inner != शून्य && attrs != शून्य)
	inner = build_attrs_declarator (attrs, inner);
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  अगर (inner == शून्य)
	    वापस शून्य;
	  अन्यथा
	    वापस c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      अन्यथा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  वापस शून्य;
	}
    }
  अन्यथा
    {
      अगर (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  वापस शून्य;
	}
      अन्यथा
	वापस build_id_declarator (NULL_वृक्ष);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

अटल काष्ठा c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, bool id_present,
				  काष्ठा c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      काष्ठा c_declarator *declarator;
      काष्ठा c_declspecs *quals_attrs = build_null_declspecs ();
      काष्ठा c_व्यंजक dimen;
      dimen.मूल्य = NULL_वृक्ष;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_वृक्ष;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, false, false, true,
			  false, false, false, false, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      अगर (c_parser_अग्र_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  अगर (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, false, false, true,
				false, false, false, false, cla_prefer_id);
	}
      अगर (!quals_attrs->declspecs_seen_p)
	quals_attrs = शून्य;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      स्थिर bool static_seen = (static_loc != UNKNOWN_LOCATION);
      bool star_seen = false;
      अगर (c_parser_अग्र_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = true;
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (!c_parser_अग्र_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_व्यंजक_no_commas (parser, शून्य);

      अगर (static_seen)
	{
	  अगर (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = false;
	      dimen.मूल्य = error_mark_गाँठ;
	    }
	  अन्यथा अगर (!dimen.मूल्य)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      अन्यथा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  वापस शून्य;
	}
      अगर (dimen.मूल्य)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, true, true);
      declarator = build_array_declarator (brace_loc, dimen.मूल्य, quals_attrs,
					   static_seen, star_seen);
      अगर (declarator == शून्य)
	वापस शून्य;
      अगर (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  वृक्ष std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  अगर (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      वापस c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      वृक्ष attrs;
      काष्ठा c_arg_info *args;
      c_parser_consume_token (parser);
      bool have_gnu_attrs = c_parser_अग्र_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      अगर (args == शून्य)
	वापस शून्य;
      अन्यथा
	{
	  अगर (!(args->types
		&& args->types != error_mark_गाँठ
		&& वृक्ष_CODE (वृक्ष_मूल्य (args->types)) == IDENTIFIER_गाँठ)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      वृक्ष std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      अगर (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  वापस c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  वापस inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

अटल काष्ठा c_arg_info *
c_parser_parms_declarator (c_parser *parser, bool id_list_ok, वृक्ष attrs,
			   bool have_gnu_attrs)
{
  धकेलो_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  अगर (id_list_ok
      && !attrs
      && c_parser_अग्र_token_is (parser, CPP_NAME)
      && c_parser_peek_token (parser)->id_kind == C_ID_ID

      /* Look ahead to detect typos in type names.  */
      && c_parser_peek_2nd_token (parser)->type != CPP_NAME
      && c_parser_peek_2nd_token (parser)->type != CPP_MULT
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_SQUARE
      && c_parser_peek_2nd_token (parser)->type != CPP_KEYWORD)
    {
      वृक्ष list = NULL_वृक्ष, *nextp = &list;
      जबतक (c_parser_अग्र_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_वृक्ष_list (NULL_वृक्ष,
				    c_parser_peek_token (parser)->मूल्य);
	  nextp = & वृक्ष_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_COMMA))
	    अवरोध;
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      अवरोध;
	    }
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	{
	  काष्ठा c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  निकालो_scope ();
	  वापस ret;
	}
      अन्यथा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  निकालो_scope ();
	  वापस शून्य;
	}
    }
  अन्यथा
    {
      काष्ठा c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, शून्य, have_gnu_attrs);
      निकालो_scope ();
      वापस ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

अटल काष्ठा c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, वृक्ष attrs, वृक्ष व्यंजक,
				bool have_gnu_attrs)
{
  bool bad_parm = false;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
    {
      काष्ठा c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      वापस ret;
    }
  अगर (c_parser_अग्र_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      काष्ठा c_arg_info *ret = build_arg_info ();

      ret->types = NULL_वृक्ष;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = true;
	  c_parser_consume_token (parser);
	  वापस ret;
	}
      अन्यथा
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  वापस शून्य;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  जबतक (true)
    {
      /* Parse a parameter.  */
      काष्ठा c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_वृक्ष;
      have_gnu_attrs = false;
      अगर (parm == शून्य)
	bad_parm = true;
      अन्यथा
	धकेलो_parm_decl (parm, &व्यंजक);
      अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	{
	  वृक्ष new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  bool new_have_gnu_attrs
	    = c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  वापस c_parser_parms_list_declarator (parser, new_attrs, व्यंजक,
						 new_have_gnu_attrs);
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  अगर (bad_parm)
	    वापस शून्य;
	  अन्यथा
	    वापस get_parm_info (false, व्यंजक);
	}
      अगर (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, false))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	  वापस शून्य;
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      अगर (bad_parm)
		वापस शून्य;
	      अन्यथा
		वापस get_parm_info (true, व्यंजक);
	    }
	  अन्यथा
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      वापस शून्य;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

अटल काष्ठा c_parm *
c_parser_parameter_declaration (c_parser *parser, वृक्ष attrs,
				bool have_gnu_attrs)
{
  काष्ठा c_declspecs *specs;
  काष्ठा c_declarator *declarator;
  वृक्ष prefix_attrs;
  वृक्ष postfix_attrs = NULL_वृक्ष;
  bool dummy = false;

  /* Accept #pragmas between parameter declarations.  */
  जबतक (c_parser_अग्र_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, शून्य, NULL_वृक्ष);

  अगर (!c_parser_अग्र_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      अगर (parser->error)
	वापस शून्य;
      c_parser_set_source_position_from_token (token);
      अगर (c_parser_अग्र_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->मूल्य,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  अगर (स्थिर अक्षर *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->मूल्य, suggestion);
	    }
	  अन्यथा
	    error_at (token->location, "unknown type name %qE", token->मूल्य);
	  parser->error = true;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      अन्यथा
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      वापस शून्य;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  अगर (attrs)
    {
      declspecs_add_attrs (निवेश_location, specs, attrs);
      attrs = NULL_वृक्ष;
    }
  c_parser_declspecs (parser, specs, true, true, true, true, false,
		      !have_gnu_attrs, true, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  अगर (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_शीर्ष_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_वृक्ष;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  अगर (declarator == शून्य)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, शून्य);
      वापस शून्य;
    }
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
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
  जबतक (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  वापस build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

अटल वृक्ष
c_parser_asm_string_literal (c_parser *parser)
{
  वृक्ष str;
  पूर्णांक save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, false, false).मूल्य;
  warn_overlength_strings = save_flag;
  वापस str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

अटल वृक्ष
c_parser_simple_asm_व्यंजक (c_parser *parser)
{
  वृक्ष str;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस NULL_वृक्ष;
  str = c_parser_asm_string_literal (parser);
  अगर (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
      वापस NULL_वृक्ष;
    }
  वापस str;
}

अटल वृक्ष
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  वृक्ष attr_name = NULL_वृक्ष;

  अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      bool ok;
      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_STATIC:
	हाल RID_UNSIGNED:
	हाल RID_LONG:
	हाल RID_CONST:
	हाल RID_EXTERN:
	हाल RID_REGISTER:
	हाल RID_TYPEDEF:
	हाल RID_SHORT:
	हाल RID_INLINE:
	हाल RID_NORETURN:
	हाल RID_VOLATILE:
	हाल RID_SIGNED:
	हाल RID_AUTO:
	हाल RID_RESTRICT:
	हाल RID_COMPLEX:
	हाल RID_THREAD:
	हाल RID_INT:
	हाल RID_CHAR:
	हाल RID_FLOAT:
	हाल RID_DOUBLE:
	हाल RID_VOID:
	हाल RID_DFLOAT32:
	हाल RID_DFLOAT64:
	हाल RID_DFLOAT128:
	हाल RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	हाल RID_BOOL:
	हाल RID_BITINT:
	हाल RID_FRACT:
	हाल RID_ACCUM:
	हाल RID_SAT:
	हाल RID_TRANSACTION_ATOMIC:
	हाल RID_TRANSACTION_CANCEL:
	हाल RID_ATOMIC:
	हाल RID_AUTO_TYPE:
	हाल RID_CONSTEXPR:
	हाल RID_INT_N_0:
	हाल RID_INT_N_1:
	हाल RID_INT_N_2:
	हाल RID_INT_N_3:
	  ok = true;
	  अवरोध;
	शेष:
	  ok = false;
	  अवरोध;
	}
      अगर (!ok)
	वापस NULL_वृक्ष;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(पूर्णांक) c_parser_peek_token (parser)->keyword];
    }
  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->मूल्य;

  वापस attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

अटल वृक्ष
c_parser_attribute_arguments (c_parser *parser, bool takes_identifier,
			      bool require_string, bool assume_attr,
			      bool allow_empty_args)
{
  vec<वृक्ष, va_gc> *व्यंजक_list;
  वृक्ष attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
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
      वृक्ष arg1 = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_वृक्ष_list (NULL_वृक्ष, arg1);
      अन्यथा
	{
	  वृक्ष वृक्ष_list;
	  c_parser_consume_token (parser);
	  व्यंजक_list = c_parser_व्यंजक_list (parser, false, true,
					  शून्य, शून्य, शून्य, शून्य);
	  वृक्ष_list = build_वृक्ष_list_vec (व्यंजक_list);
	  attr_args = वृक्ष_cons (NULL_वृक्ष, arg1, वृक्ष_list);
	  release_वृक्ष_vector (व्यंजक_list);
	}
    }
  अन्यथा
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	{
	  अगर (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_वृक्ष;
	}
      अन्यथा अगर (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  वृक्ष string = c_parser_string_literal (parser, false, true).मूल्य;
	  attr_args = build_वृक्ष_list (NULL_वृक्ष, string);
	}
      अन्यथा अगर (assume_attr)
	{
	  वृक्ष cond
	    = c_parser_conditional_expression (parser, शून्य, NULL_वृक्ष).मूल्य;
	  अगर (!c_parser_अग्र_token_is (parser, CPP_COMMA))
	    attr_args = build_वृक्ष_list (NULL_वृक्ष, cond);
	  अन्यथा
	    {
	      वृक्ष वृक्ष_list;
	      c_parser_consume_token (parser);
	      व्यंजक_list = c_parser_व्यंजक_list (parser, false, true,
					      शून्य, शून्य, शून्य, शून्य);
	      वृक्ष_list = build_वृक्ष_list_vec (व्यंजक_list);
	      attr_args = वृक्ष_cons (NULL_वृक्ष, cond, वृक्ष_list);
	      release_वृक्ष_vector (व्यंजक_list);
	    }
	}
      अन्यथा
	{
	  व्यंजक_list = c_parser_व्यंजक_list (parser, false, true,
					  शून्य, शून्य, शून्य, शून्य);
	  attr_args = build_वृक्ष_list_vec (व्यंजक_list);
	  release_वृक्ष_vector (व्यंजक_list);
	}
    }
  वापस attr_args;
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

अटल वृक्ष
c_parser_gnu_attribute (c_parser *parser, वृक्ष attrs,
			bool expect_comma = false, bool empty_ok = true)
{
  bool comma_first = c_parser_अग्र_token_is (parser, CPP_COMMA);
  अगर (!comma_first
      && !c_parser_अग्र_token_is (parser, CPP_NAME)
      && !c_parser_अग्र_token_is (parser, CPP_KEYWORD))
    वापस NULL_वृक्ष;

  जबतक (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      अगर (!empty_ok)
	वापस attrs;
    }

  वृक्ष attr_name = c_parser_gnu_attribute_any_word (parser);
  अगर (attr_name == NULL_वृक्ष)
    वापस NULL_वृक्ष;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  वृक्ष attr;
  अगर (c_parser_अग्र_token_is_not (parser, CPP_OPEN_PAREN))
    {
      अगर (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  वापस error_mark_गाँठ;
	}
      attr = build_वृक्ष_list (attr_name, NULL_वृक्ष);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      वापस attrs;
    }
  c_parser_consume_token (parser);

  वृक्ष attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    false,
				    is_attribute_p ("assume", attr_name),
				    true);

  attr = build_वृक्ष_list (attr_name, attr_args);
  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  अन्यथा
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      वापस error_mark_गाँठ;
    }

  अगर (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      वापस error_mark_गाँठ;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  वापस attrs;
}

अटल वृक्ष
c_parser_gnu_attributes (c_parser *parser)
{
  वृक्ष attrs = NULL_वृक्ष;
  जबतक (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      bool save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = false;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  वापस attrs;
	}
      अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	  वापस attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      क्रम (bool expect_comma = false; ; expect_comma = true)
	{
	  /* Parse a single attribute.  */
	  वृक्ष attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  अगर (attr == error_mark_गाँठ)
	    वापस attrs;
	  अगर (!attr)
	    अवरोध;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      अन्यथा
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  वापस attrs;
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      अन्यथा
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  वापस attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  वापस attrs;
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

अटल व्योम
c_parser_balanced_token_sequence (c_parser *parser)
{
  जबतक (true)
    {
      c_token *token = c_parser_peek_token (parser);
      चयन (token->type)
	{
	हाल CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    अवरोध;
	  }

	हाल CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    अवरोध;
	  }

	हाल CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  अवरोध;

	हाल CPP_CLOSE_BRACE:
	हाल CPP_CLOSE_PAREN:
	हाल CPP_CLOSE_SQUARE:
	हाल CPP_EOF:
	  वापस;

	हाल CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, false);
	  अवरोध;

	शेष:
	  c_parser_consume_token (parser);
	  अवरोध;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

अटल व्योम
c_parser_omp_directive_args (c_parser *parser, वृक्ष attribute, bool decl_p)
{
  अचिन्हित पूर्णांक n = 1;
  c_token *first = c_parser_peek_token (parser);
  अगर (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      वृक्ष_मूल्य (attribute) = NULL_वृक्ष;
      वापस;
    }
  अगर (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      वृक्ष_मूल्य (attribute) = NULL_वृक्ष;
      वापस;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  क्रम (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_धकेलो (*tok);
      c_parser_consume_token (parser);
    }
  वृक्ष arg = make_गाँठ (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  अगर (decl_p)
    वृक्ष_PUBLIC (arg) = 1;
  वृक्ष_मूल्य (attribute) = वृक्ष_cons (NULL_वृक्ष, arg, वृक्ष_मूल्य (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

अटल व्योम
c_parser_omp_sequence_args (c_parser *parser, वृक्ष attribute)
{
  करो
    {
      c_token *token = c_parser_peek_token (parser);
      अगर (token->type == CPP_NAME
	  && म_भेद (IDENTIFIER_POINTER (token->मूल्य), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      bool directive = false;
      स्थिर अक्षर *p;
      अगर (token->type != CPP_NAME)
	p = "";
      अन्यथा
	p = IDENTIFIER_POINTER (token->मूल्य);
      अगर (म_भेद (p, "directive") == 0)
	directive = true;
      अन्यथा अगर (म_भेद (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  अचिन्हित nesting_depth = 0;

	  जबतक (true)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      अगर ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		अवरोध;
	      /* If we've run out of tokens, stop.  */
	      अगर (token->type == CPP_EOF)
		अवरोध;
	      अगर (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		अवरोध;
	      अगर (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      अन्यथा अगर (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  अगर (nesting_depth-- == 0)
		    अवरोध;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_COMMA))
	    अवरोध;
	  c_parser_consume_token (parser);
	  जारी;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      अगर (parens.require_open (parser))
	{
	  अगर (directive)
	    c_parser_omp_directive_args (parser, attribute, false);
	  अन्यथा
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_COMMA))
	    अवरोध;
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (c_parser_अग्र_token_is_not (parser, CPP_COMMA))
	अवरोध;
      अन्यथा
	c_parser_consume_token (parser);
    }
  जबतक (1);
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

अटल वृक्ष
c_parser_std_attribute (c_parser *parser, bool for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  वृक्ष ns, name, attribute;

  /* Parse the attribute-token.  */
  अगर (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      वापस error_mark_गाँठ;
    }
  name = canonicalize_attr_name (token->मूल्य);
  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_SCOPE)
      || (c_parser_अग्र_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      अगर (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  वापस error_mark_गाँठ;
	}
      name = canonicalize_attr_name (token->मूल्य);
      c_parser_consume_token (parser);
    }
  अन्यथा
    ns = NULL_वृक्ष;
  attribute = build_वृक्ष_list (build_वृक्ष_list (ns, name), NULL_वृक्ष);

  /* Parse the arguments, if any.  */
  स्थिर attribute_spec *as = lookup_attribute_spec (वृक्ष_PURPOSE (attribute));
  अगर (c_parser_अग्र_token_is_not (parser, CPP_OPEN_PAREN))
    {
      अगर ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  वापस error_mark_गाँठ;
	}
      जाओ out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    अगर ((as && as->max_लंबाई == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	वापस error_mark_गाँठ;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    अगर (as && !attribute_ignored_p (as))
      {
	bool takes_identifier
	  = (ns != NULL_वृक्ष
	     && म_भेद (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	bool require_string
	  = (ns == NULL_वृक्ष
	     && (म_भेद (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || म_भेद (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	bool assume_attr
	  = (ns != NULL_वृक्ष
	     && म_भेद (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && म_भेद (IDENTIFIER_POINTER (name), "assume") == 0);
	वृक्ष_मूल्य (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, false);
      }
    अन्यथा
      {
	अगर ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    अगर (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, false);
		parens.skip_until_found_close (parser);
		वापस attribute;
	      }
	    अन्यथा अगर (is_attribute_p ("decl", name))
	      {
		वृक्ष_मूल्य (वृक्ष_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, true);
		parens.skip_until_found_close (parser);
		वापस attribute;
	      }
	    अन्यथा अगर (is_attribute_p ("sequence", name))
	      {
		वृक्ष_मूल्य (वृक्ष_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		वृक्ष_मूल्य (attribute) = nreverse (वृक्ष_मूल्य (attribute));
		वापस attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  अगर (ns == NULL_वृक्ष && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (निवेश_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      वापस error_mark_गाँठ;
    }
  वापस attribute;
}

अटल वृक्ष
c_parser_std_attribute_list (c_parser *parser, bool for_tm)
{
  वृक्ष attributes = NULL_वृक्ष;
  जबतक (true)
    {
      c_token *token = c_parser_peek_token (parser);
      अगर (token->type == CPP_CLOSE_SQUARE)
	अवरोध;
      अगर (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  जारी;
	}
      वृक्ष attribute = c_parser_std_attribute (parser, for_tm);
      अगर (attribute != error_mark_गाँठ)
	{
	  वृक्ष_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      अगर (c_parser_अग्र_token_is_not (parser, CPP_COMMA))
	अवरोध;
    }
  वापस attributes;
}

अटल वृक्ष
c_parser_std_attribute_specifier (c_parser *parser, bool for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  अगर (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    वापस NULL_वृक्ष;
  अगर (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      वापस NULL_वृक्ष;
    }
  वृक्ष attributes;
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_EXTENSION))
    {
      स्वतः ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  अन्यथा
    {
      अगर (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  वापस nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

अटल bool
c_parser_check_balanced_raw_token_sequence (c_parser *parser, अचिन्हित पूर्णांक *n)
{
  जबतक (true)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      चयन (token->type)
	{
	हाल CPP_OPEN_BRACE:
	  {
	    ++*n;
	    अगर (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		अगर (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		अन्यथा
		  वापस false;
	      }
	    अन्यथा
	      वापस false;
	    अवरोध;
	  }

	हाल CPP_OPEN_PAREN:
	  {
	    ++*n;
	    अगर (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		अगर (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		अन्यथा
		  वापस false;
	      }
	    अन्यथा
	      वापस false;
	    अवरोध;
	  }

	हाल CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    अगर (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		अगर (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		अन्यथा
		  वापस false;
	      }
	    अन्यथा
	      वापस false;
	    अवरोध;
	  }

	हाल CPP_CLOSE_BRACE:
	हाल CPP_CLOSE_PAREN:
	हाल CPP_CLOSE_SQUARE:
	हाल CPP_EOF:
	  वापस true;

	शेष:
	  ++*n;
	  अवरोध;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

अटल bool
c_parser_nth_token_starts_std_attributes (c_parser *parser, अचिन्हित पूर्णांक n)
{
  अगर (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    वापस false;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  अगर (!c_dialect_objc ())
    वापस true;
  n += 2;
  अगर (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    वापस false;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  अगर (token->type != CPP_CLOSE_SQUARE)
    वापस false;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  वापस token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

अटल माप_प्रकार
c_parser_skip_std_attribute_spec_seq (c_parser *parser, माप_प्रकार n)
{
  माप_प्रकार orig_n = n;
  जबतक (true)
    {
      अगर (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  अचिन्हित पूर्णांक m = n + 2;
	  अगर (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    वापस orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  अगर (token->type != CPP_CLOSE_SQUARE)
	    वापस orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  अगर (token->type != CPP_CLOSE_SQUARE)
	    वापस orig_n;
	  n = m + 2;
	}
      अन्यथा
	अवरोध;
    }
  वापस n;
}

अटल वृक्ष
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  वृक्ष attributes = NULL_वृक्ष;
  करो
    {
      वृक्ष attrs = c_parser_std_attribute_specifier (parser, false);
      attributes = chainon (attributes, attrs);
    }
  जबतक (c_parser_nth_token_starts_std_attributes (parser, 1));
  वापस attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

काष्ठा c_type_name *
c_parser_type_name (c_parser *parser, bool alignas_ok)
{
  काष्ठा c_declspecs *specs = build_null_declspecs ();
  काष्ठा c_declarator *declarator;
  काष्ठा c_type_name *ret;
  bool dummy = false;
  c_parser_declspecs (parser, specs, false, true, true, alignas_ok, false,
		      false, true, cla_prefer_type);
  अगर (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      वापस शून्य;
    }
  अगर (specs->type != error_mark_गाँठ)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      अगर (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_शीर्ष_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  अगर (declarator == शून्य)
    वापस शून्य;
  ret = XOBNEW (&parser_obstack, काष्ठा c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  वापस ret;
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

अटल काष्ठा c_व्यंजक
c_parser_initializer (c_parser *parser, वृक्ष decl)
{
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    वापस c_parser_braced_init (parser, NULL_वृक्ष, false, शून्य,
				 decl != error_mark_गाँठ
				 && C_DECL_VARIABLE_आकार (decl));
  अन्यथा
    {
      काष्ठा c_व्यंजक ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_व्यंजक_no_commas (parser, शून्य);
      अगर (decl != error_mark_गाँठ && C_DECL_VARIABLE_आकार (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      अगर (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !वृक्ष_STATIC (decl)
	  && ret.मूल्य == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      अगर (वृक्ष_CODE (ret.मूल्य) != STRING_CST
	  && (वृक्ष_CODE (ret.मूल्य) != COMPOUND_LITERAL_व्यंजक
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_व्यंजक_DECL
					    (ret.मूल्य))))
	ret = convert_lvalue_to_rvalue (loc, ret, true, true, true);
      वापस ret;
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

अटल काष्ठा c_व्यंजक
c_parser_braced_init (c_parser *parser, वृक्ष type, bool nested_p,
		      काष्ठा obstack *outer_obstack, bool varsize_p)
{
  काष्ठा c_व्यंजक ret;
  काष्ठा obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE));
  bool save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = false;
  bool zero_init_padding_bits = false;
  matching_braces braces;
  braces.consume_open (parser);
  अगर (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      धकेलो_init_level (brace_loc, 0, &braced_init_obstack);
    }
  अन्यथा
    really_start_incremental_init (type);
  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      अगर (flag_isoc23)
	zero_init_padding_bits = true;
    }
  अन्यथा
    {
      अगर (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      जबतक (true)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  अगर (parser->error)
	    अवरोध;
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      जबतक (c_parser_अग्र_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_व्यंजक embed_val;
		  embed_val.मूल्य = embed->मूल्य;
		  embed_val.original_code = RAW_तथ्य_CST;
		  embed_val.original_type = integer_type_गाँठ;
		  set_c_व्यंजक_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, false,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_अग्र_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  अन्यथा
	    अवरोध;
	  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	    अवरोध;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *अग्र_tok = c_parser_peek_token (parser);
  अगर (अग्र_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = शून्य;
      braces.skip_until_found_close (parser);
      निकालो_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, शून्य);
      वापस ret;
    }
  location_t close_loc = अग्र_tok->location;
  c_parser_consume_token (parser);
  ret = निकालो_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  अगर (zero_init_padding_bits
      && ret.मूल्य
      && वृक्ष_CODE (ret.मूल्य) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.मूल्य) = 1;
  obstack_free (&braced_init_obstack, शून्य);
  set_c_व्यंजक_source_range (&ret, brace_loc, close_loc);
  वापस ret;
}

/* Parse a nested initializer, including designators.  */

अटल व्योम
c_parser_initelt (c_parser *parser, काष्ठा obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->मूल्य,
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
      पूर्णांक des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      जबतक (c_parser_अग्र_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_अग्र_token_is (parser, CPP_DOT))
	{
	  पूर्णांक des_पूर्व = des_seen;
	  अगर (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  अगर (des_seen < 2)
	    des_seen++;
	  अगर (c_parser_अग्र_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->मूल्य,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      अन्यथा
		{
		  काष्ठा c_व्यंजक init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = शून्य;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, शून्य);
		  process_init_element (निवेश_location, init, false,
					braced_init_obstack);
		  वापस;
		}
	    }
	  अन्यथा
	    {
	      काष्ठा c_व्यंजक first_व्यंजक;
	      वृक्ष first, second;
	      location_t ellipsis_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	      location_t array_सूचकांक_loc = UNKNOWN_LOCATION;
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
	      अगर (des_पूर्व == 1 && c_dialect_objc ())
		{
		  des_seen = des_पूर्व;
		  अवरोध;
		}
	      अगर (des_पूर्व == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  वृक्ष rec, args;
		  काष्ठा c_व्यंजक mexpr;
		  c_parser_consume_token (parser);
		  अगर (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      वृक्ष id = c_parser_peek_token (parser)->मूल्य;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      जाओ parse_message_args;
		    }
		  array_सूचकांक_loc = c_parser_peek_token (parser)->location;
		  first_व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
		  mark_exp_read (first_व्यंजक.मूल्य);
		  अगर (c_parser_अग्र_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_अग्र_token_is (parser, CPP_CLOSE_SQUARE))
		    जाओ array_desig_after_first;
		  first = first_व्यंजक.मूल्य;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  जबतक (c_parser_अग्र_token_is (parser, CPP_COMMA))
		    {
		      काष्ठा c_व्यंजक अग्र;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      अग्र = c_parser_व्यंजक_no_commas (parser, शून्य);
		      अग्र = convert_lvalue_to_rvalue (exp_loc, अग्र,
						       true, true);
		      rec = build_compound_व्यंजक (comma_loc, rec, अग्र.मूल्य);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.मूल्य
		    = objc_build_message_व्यंजक (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = शून्य;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  वापस;
		}
	      c_parser_consume_token (parser);
	      array_सूचकांक_loc = c_parser_peek_token (parser)->location;
	      first_व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	      mark_exp_read (first_व्यंजक.मूल्य);
	    array_desig_after_first:
	      first_व्यंजक = convert_lvalue_to_rvalue (array_सूचकांक_loc,
						     first_व्यंजक,
						     true, true);
	      first = first_व्यंजक.मूल्य;
	      अगर (c_parser_अग्र_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_व्यंजक_no_commas
						      (parser, शून्य)),
						     true, true).मूल्य;
		  mark_exp_read (second);
		}
	      अन्यथा
		second = NULL_वृक्ष;
	      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_सूचकांक (array_सूचकांक_loc, first, second,
				  braced_init_obstack);
		  अगर (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      अन्यथा
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      अगर (des_seen >= 1)
	{
	  अगर (c_parser_अग्र_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      अगर (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      अन्यथा
		{
		  काष्ठा c_व्यंजक init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = शून्य;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, शून्य);
		  process_init_element (निवेश_location, init, false,
					braced_init_obstack);
		  वापस;
		}
	    }
	}
    }
  c_parser_initval (parser, शून्य, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

अटल व्योम
c_parser_initval (c_parser *parser, काष्ठा c_व्यंजक *after,
		  काष्ठा obstack * braced_init_obstack)
{
  काष्ठा c_व्यंजक init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_वृक्ष, true,
				 braced_init_obstack, false);
  अन्यथा
    {
      init = c_parser_व्यंजक_no_commas (parser, after);
      अगर (init.मूल्य != NULL_वृक्ष
	  && वृक्ष_CODE (init.मूल्य) != STRING_CST
	  && (वृक्ष_CODE (init.मूल्य) != COMPOUND_LITERAL_व्यंजक
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_व्यंजक_DECL
					    (init.मूल्य))))
	init = convert_lvalue_to_rvalue (loc, init, true, true, true);
    }
  वृक्ष val = init.मूल्य;
  process_init_element (loc, init, false, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  अटल अचिन्हित vals_to_ignore;
  अगर (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  अन्यथा अगर (val
	   && वृक्ष_CODE (val) == INTEGER_CST
	   && वृक्ष_TYPE (val) == integer_type_गाँठ
	   && c_parser_अग्र_token_is (parser, CPP_COMMA))
    अगर (अचिन्हित पूर्णांक len = c_maybe_optimize_large_byte_initializer ())
      {
	अक्षर buf1[64];
	अचिन्हित पूर्णांक i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	क्रम (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    अगर (tok->type != CPP_COMMA)
	      अवरोध;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    अगर (tok->type != CPP_संख्या
		|| वृक्ष_CODE (tok->मूल्य) != INTEGER_CST
		|| वृक्ष_TYPE (tok->मूल्य) != integer_type_गाँठ
		|| wi::neg_p (wi::to_wide (tok->मूल्य))
		|| wi::to_widest (tok->मूल्य) > अच_अक्षर_उच्च)
	      अवरोध;
	    buf1[i] = (अक्षर) वृक्ष_to_uhwi (tok->मूल्य);
	    अगर (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	अगर (i < 64)
	  {
	    vals_to_ignore = i;
	    वापस;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	अगर (tok->type == CPP_CLOSE_BRACE && len != पूर्णांक_उच्च)
	  len = i;
	अन्यथा अगर (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_संख्या))
	  {
	    vals_to_ignore = i;
	    वापस;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	अचिन्हित पूर्णांक max_len = 131072 - दुरत्व (काष्ठा वृक्ष_string, str) - 1;
	अचिन्हित पूर्णांक orig_len = len;
	अचिन्हित पूर्णांक off = 0, last = 0;
	अगर (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= अच_अक्षर_उच्च)
	  off = 1;
	len = MIN (len, max_len - off);
	अक्षर *buf2 = XNEWVEC (अक्षर, len + off);
	अगर (off)
	  buf2[0] = (अक्षर) वृक्ष_to_uhwi (val);
	स_नकल (buf2 + off, buf1, i);
	क्रम (अचिन्हित पूर्णांक j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	क्रम (; i < len; ++i)
	  {
	    अगर (!c_parser_अग्र_token_is (parser, CPP_COMMA))
	      अवरोध;
	    tok = c_parser_peek_2nd_token (parser);
	    अगर (tok->type != CPP_संख्या
		|| वृक्ष_CODE (tok->मूल्य) != INTEGER_CST
		|| वृक्ष_TYPE (tok->मूल्य) != integer_type_गाँठ
		|| wi::neg_p (wi::to_wide (tok->मूल्य))
		|| wi::to_widest (tok->मूल्य) > अच_अक्षर_उच्च)
	      अवरोध;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    अगर (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      अवरोध;
	    buf2[i + off] = (अक्षर) वृक्ष_to_uhwi (tok->मूल्य);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    अगर (orig_len == पूर्णांक_उच्च
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_संख्या)))
	      {
		last = 1;
		अवरोध;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_गाँठ (RAW_तथ्य_CST);
	वृक्ष_TYPE (val) = integer_type_गाँठ;
	RAW_तथ्य_लंबाई (val) = i;
	वृक्ष owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	वृक्ष_TYPE (owner) = build_array_type_nelts (unsigned_char_type_गाँठ,
						    i + off + last);
	RAW_तथ्य_OWNER (val) = owner;
	RAW_तथ्य_POINTER (val) = वृक्ष_STRING_POINTER (owner) + off;
	init.मूल्य = val;
	set_c_व्यंजक_source_range (&init, loc, last_loc);
	init.original_code = RAW_तथ्य_CST;
	init.original_type = integer_type_गाँठ;
	init.m_decimal = 0;
	process_init_element (loc, init, false, braced_init_obstack);
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

अटल वृक्ष
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  वृक्ष stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  अगर (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (true);
      c_end_compound_stmt (brace_loc, stmt, true);
      वापस error_mark_गाँठ;
    }
  stmt = c_begin_compound_stmt (true);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  अगर (endlocp)
    *endlocp = end_loc;

  वापस c_end_compound_stmt (brace_loc, stmt, true);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

अटल व्योम
check_omp_intervening_code (c_parser *parser)
{
  काष्ठा omp_for_parse_तथ्य *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  अगर (!omp_for_parse_state->in_intervening_code)
    वापस;
  omp_for_parse_state->saw_intervening_code = true;

  /* Only diagnose errors related to perfect nesting once.  */
  अगर (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      अगर (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = true;
	}
      अन्यथा अगर (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = true;
	}
      अन्यथा अगर (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = true;
	}
      अन्यथा अगर (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = true;
	}
      अगर (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->हार = true;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
अटल व्योम
add_structured_block_stmt (वृक्ष sl)
{
  अगर (वृक्ष_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_गाँठ, sl));
}

काष्ठा c_omp_attribute_तथ्य
{
  vec<c_token, va_gc> *tokens;
  स्थिर c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

अटल bool
c_parser_handle_statement_omp_attributes (c_parser *parser, वृक्ष &attrs,
					  bool *have_std_attrs)
{
  अगर (!flag_openmp && !flag_openmp_simd)
    वापस false;

  auto_vec<c_omp_attribute_तथ्य, 16> vd;
  पूर्णांक cnt = 0;
  पूर्णांक tokens = 0;
  bool बुरा = false;
  क्रम (वृक्ष *pa = &attrs; *pa; )
    अगर (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	क्रम (वृक्ष a = वृक्ष_मूल्य (*pa); a; a = वृक्ष_CHAIN (a))
	  {
	    वृक्ष d = वृक्ष_मूल्य (a);
	    gcc_assert (वृक्ष_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->लंबाई ();
	    अगर (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = false;
		बुरा = true;
	      }
	    अन्यथा अगर (वृक्ष_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		बुरा = true;
	      }
	    स्थिर अक्षर *directive[3] = {};
	    क्रम (पूर्णांक i = 0; i < 3; i++)
	      {
		वृक्ष id = NULL_वृक्ष;
		अगर (first + i == last)
		  अवरोध;
		अगर (first[i].type == CPP_NAME)
		  id = first[i].मूल्य;
		अन्यथा अगर (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(पूर्णांक) first[i].keyword];
		अन्यथा
		  अवरोध;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    स्थिर c_omp_directive *dir = शून्य;
	    अगर (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    अगर (dir == शून्य)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  वृक्ष_PUBLIC (d) ? "omp::decl" : "omp::directive");
		जारी;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    अगर (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		अगर (directive[1]
		    && (म_भेद (directive[1], "depend") == 0
			|| म_भेद (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		अन्यथा अगर (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (म_भेद (IDENTIFIER_POINTER (first[2].मूल्य),
				     "depend") == 0
			     || म_भेद (IDENTIFIER_POINTER (first[2].मूल्य),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    अन्यथा अगर (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		पूर्णांक paren_depth = 0;
		क्रम (पूर्णांक i = 1; first + i < last; i++)
		  अगर (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  अन्यथा अगर (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  अन्यथा अगर (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !म_भेद (IDENTIFIER_POINTER (first[i].मूल्य),
				       "at")
			   && !म_भेद (IDENTIFIER_POINTER (first[i
								 + 2].मूल्य),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      अवरोध;
		    }
	      }
	    c_omp_attribute_तथ्य v = { toks, dir, kind };
	    vd.safe_धकेलो (v);
	    अगर (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_तथ्य v = {};
	vd.safe_धकेलो (v);
	*pa = वृक्ष_CHAIN (*pa);
      }
    अन्यथा
      pa = &वृक्ष_CHAIN (*pa);

  अगर (बुरा)
    {
    हार:
      अगर (have_std_attrs && attrs == शून्य)
	*have_std_attrs = false;
      वापस false;
    }

  अचिन्हित पूर्णांक i;
  c_omp_attribute_तथ्य *v;
  c_omp_attribute_तथ्य *construct_seen = nullptr;
  c_omp_attribute_तथ्य *standalone_seen = nullptr;
  c_omp_attribute_तथ्य *पूर्व_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    अगर (v->tokens)
      {
	अगर (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	अन्यथा अगर (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    अन्यथा
      {
	अगर (standalone_seen && !पूर्व_standalone_seen)
	  {
	    पूर्व_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  अगर (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      जाओ हार;
    }
  अगर (cnt > 1 && standalone_seen && पूर्व_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      जाओ हार;
    }

  अगर (पूर्व_standalone_seen)
    standalone_seen = पूर्व_standalone_seen;
  अगर (standalone_seen
      && !c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      जाओ हार;
    }
  अगर (cnt && c_parser_अग्र_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      क्रमागत pragma_kind kind = token->pragma_kind;
      अगर (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  जाओ हार;
	}
    }

  अगर (!tokens)
    वापस false;

  अचिन्हित पूर्णांक tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = शून्य;
  vec_safe_reserve (toks, tokens, true);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      अगर (!v->tokens)
	जारी;
      अगर (!flag_openmp && !v->dir->simd)
	जारी;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->लंबाई ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_धकेलो (tok);
      जबतक (++first < last)
	toks->quick_धकेलो (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_धकेलो (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_धकेलो (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  वापस true;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

अटल व्योम
c_parser_handle_directive_omp_attributes (वृक्ष &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  अगर (!flag_openmp && !flag_openmp_simd)
    वापस;

  क्रम (वृक्ष *pa = &attrs; *pa; )
    अगर (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	पूर्णांक cnt = 0;
	क्रम (वृक्ष *pa2 = &वृक्ष_मूल्य (*pa); *pa2; )
	  {
	    वृक्ष a = *pa2;
	    वृक्ष d = वृक्ष_मूल्य (a);
	    gcc_assert (वृक्ष_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->लंबाई ();
	    स्थिर अक्षर *directive[3] = {};
	    क्रम (पूर्णांक i = 0; i < 3; i++)
	      {
		वृक्ष id = NULL_वृक्ष;
		अगर (first + i == last)
		  अवरोध;
		अगर (first[i].type == CPP_NAME)
		  id = first[i].मूल्य;
		अन्यथा अगर (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(पूर्णांक) first[i].keyword];
		अन्यथा
		  अवरोध;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    स्थिर c_omp_directive *dir = शून्य;
	    अगर (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    अगर (dir == शून्य)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  वृक्ष_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = वृक्ष_CHAIN (a);
	      }
	    अन्यथा अगर (dir->id == PRAGMA_OMP_DECLARE
		     && (म_भेद (directive[1], "simd") == 0
			 || म_भेद (directive[1], "variant") == 0))
	      {
		अगर (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    क्रम (pa = &attrs; *pa; )
		      अगर (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = वृक्ष_CHAIN (*pa);
		      अन्यथा
			pa = &वृक्ष_CHAIN (*pa);
		    वापस;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->लंबाई ()
				       + toks->लंबाई () + 2);
		क्रम (++first; first < last; ++first)
		  attr_clauses->quick_धकेलो (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_धकेलो (tok);
		*pa2 = वृक्ष_CHAIN (a);
	      }
	    अन्यथा
	      pa2 = &वृक्ष_CHAIN (a);
	  }
	अगर (cnt && वृक्ष_मूल्य (*pa) == NULL_वृक्ष)
	  *pa = वृक्ष_CHAIN (*pa);
	अन्यथा
	  pa = &वृक्ष_CHAIN (*pa);
      }
    अन्यथा
      pa = &वृक्ष_CHAIN (*pa);
  अगर (attr_clauses->लंबाई ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_धकेलो (tok);
      attr_clauses->quick_धकेलो (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

अटल वृक्ष
c_parser_handle_musttail (c_parser *parser, वृक्ष std_attrs, attr_state &attr)
{
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_RETURN))
    {
      अगर (वृक्ष a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  क्रम (; a; a = lookup_attribute ("gnu", "musttail", वृक्ष_CHAIN (a)))
	    अगर (वृक्ष_मूल्य (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = true;
	}
      अगर (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = true;
	}
    }
  वापस std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

अटल वृक्ष
get_before_labels ()
{
  अगर (!building_stmt_list_p ())
    वापस NULL_वृक्ष;
  वृक्ष_stmt_iterator tsi = tsi_last (cur_stmt_list);
  अगर (tsi_end_p (tsi))
    वापस NULL_वृक्ष;
  वापस tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

अटल location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  bool last_stmt = false;
  bool last_label = false;
  bool save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  काष्ठा omp_for_parse_तथ्य *omp_for_parse_state
    = parser->omp_for_parse_state;
  bool in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : false;
  वृक्ष sl = NULL_वृक्ष;
  attr_state astate = {};

  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      वापस endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  अगर (in_omp_loop_block)
    sl = धकेलो_stmt_list ();

  mark_valid_location_for_stdc_pragma (true);
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (false);
      अगर (in_omp_loop_block)
	check_omp_intervening_code (parser);
      जबतक (c_parser_अग्र_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  जबतक (true)
	    {
	      वृक्ष label;
	      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  अवरोध;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->मूल्य);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_व्यंजक, label));
	      c_parser_consume_token (parser);
	      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      अन्यथा
		अवरोध;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      वापस endloc;
    }
  वृक्ष before_labels = get_before_labels ();
  जबतक (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      bool want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : false);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      अगर (in_omp_loop_block && !last_label)
	{
	  वृक्ष_code code = omp_for_parse_state->code;
	  अगर (want_nested_loop
	      && c_parser_omp_अग्र_tokens_can_be_canon_loop (parser, code,
							     false))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (निकालो_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, शून्य));
	      omp_for_parse_state->depth--;
	      sl = धकेलो_stmt_list ();
	      parser->error = false;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      जारी;
	    }
	  अन्यथा अगर (want_nested_loop
		   && c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      वृक्ष pre_sl = निकालो_stmt_list (sl);
	      वृक्ष nested_sl = धकेलो_stmt_list ();
	      mark_valid_location_for_stdc_pragma (false);
	      c_parser_statement_after_labels (parser, शून्य, NULL_वृक्ष);
	      nested_sl = निकालो_stmt_list (nested_sl);
	      अगर (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = धकेलो_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      अन्यथा
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = धकेलो_stmt_list ();
		}
	      parser->error = false;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      जारी;
	    }
	  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
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
      bool have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      वृक्ष std_attrs = NULL_वृक्ष;
      अगर (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      अगर (c_parser_अग्र_token_is_keyword (parser, RID_CASE)
	  || c_parser_अग्र_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  अन्यथा
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = true;
	  last_stmt = false;
	  mark_valid_location_for_stdc_pragma (false);
	  अगर (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      अन्यथा अगर (c_parser_अग्र_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = true)))
	{
	  अगर (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  अगर (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = false;
	    }
	  mark_valid_location_for_stdc_pragma (false);
	  bool fallthru_attr_p = false;
	  c_parser_declaration_or_fndef (parser, true, !have_std_attrs,
					 true, true, true, false, शून्य,
					 शून्य, have_std_attrs, std_attrs,
					 शून्य, &fallthru_attr_p);

	  अगर (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  अगर (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = false;
	  before_labels = get_before_labels ();
	}
      अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  जबतक (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  अगर (!have_std_attrs
	      && (c_parser_अग्र_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      पूर्णांक ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = false;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      अगर (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = false;
		}
	      mark_valid_location_for_stdc_pragma (false);
	      c_parser_declaration_or_fndef (parser, true, true, true, true,
					     true, false);
	      अगर (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      अगर (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = false;
	      before_labels = get_before_labels ();
	    }
	  अन्यथा
	    जाओ statement;
	}
      अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_PRAGMA))
	{
	  अगर (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  अन्यथा अगर (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  अगर (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = false;
	  अगर (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       शून्य, before_labels))
	    {
	      last_label = false;
	      last_stmt = true;
	      अगर (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  अगर (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  वापस c_parser_peek_token (parser)->location;
	}
      अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_ELSE))
        {
          अगर (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      वापस c_parser_peek_token (parser)->location;
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
	  last_label = false;
	  last_stmt = true;
	  mark_valid_location_for_stdc_pragma (false);
	  अगर (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, शून्य, before_labels,
					     शून्य, astate);
	  अन्यथा
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = false;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, शून्य, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = false;
      astate.reset ();
    }
  अगर (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  अगर (sl)
    {
      sl = निकालो_stmt_list (sl);
      अगर (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      अन्यथा
	add_structured_block_stmt (sl);
    }
  वापस endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

अटल attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  bool have_std_attrs;
  वृक्ष std_attrs = शून्य;
  अगर ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  जबतक (c_parser_अग्र_token_is_keyword (parser, RID_CASE)
	 || c_parser_अग्र_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_अग्र_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = शून्य;
      अगर ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  अगर (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      अगर (have_std_attrs && c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  अन्यथा अगर (have_std_attrs && c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  वापस attr;
}


/* Information used while parsing an OpenMP metadirective.  */
काष्ठा omp_metadirective_parse_तथ्य {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<वृक्ष> * GTY((skip)) body_labels;
  अचिन्हित पूर्णांक region_अंक;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
अटल वृक्ष
mangle_metadirective_region_label (c_parser *parser, वृक्ष name)
{
  अगर (parser->omp_metadirective_state->body_labels->contains (name))
    {
      स्थिर अक्षर *old_name = IDENTIFIER_POINTER (name);
      अक्षर *new_name = (अक्षर *) XALLOCAVEC (अक्षर, म_माप (old_name) + 32);
      प्र_लिखो (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_अंक);
      वापस get_identifier (new_name);
    }
  वापस name;
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
अटल व्योम
c_parser_label (c_parser *parser, वृक्ष std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  वृक्ष label = NULL_वृक्ष;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  bool fallthrough_p = c_parser_peek_token (parser)->flags & पूर्व_FALLTHROUGH;

  अगर (c_parser_अग्र_token_is_keyword (parser, RID_CASE))
    {
      वृक्ष exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_व्यंजक_no_commas (parser, शून्य),
				       true, true).मूल्य;
      अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_वृक्ष, std_attrs);
	}
      अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_व्यंजक_no_commas (parser,
								    शून्य),
					   true, true).मूल्य;
	  अगर (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      अन्यथा
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      अगर (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_वृक्ष, NULL_वृक्ष, std_attrs);
    }
  अन्यथा
    {
      वृक्ष name = c_parser_peek_token (parser)->मूल्य;
      वृक्ष tlab;
      वृक्ष attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_अग्र_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_अग्र_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      अगर (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      अगर (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_व्यंजक, tlab));
	}
      अगर (attrs
	  && c_parser_अग्र_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  अगर (label)
    {
      अगर (वृक्ष_CODE (label) == LABEL_व्यंजक)
	FALLTHROUGH_LABEL_P (LABEL_व्यंजक_LABEL (label)) = fallthrough_p;
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

अटल व्योम
c_parser_statement (c_parser *parser, bool *if_p, location_t *loc_after_labels)
{
  वृक्ष before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  अगर (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = false;
  c_parser_statement_after_labels (parser, if_p, before_labels, शून्य, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

अटल वृक्ष
c_parser_bc_name (c_parser *parser, bool is_break)
{
  अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
    वापस NULL_वृक्ष;

  c_token *tok = c_parser_peek_token (parser);
  वृक्ष label = c_finish_bc_name (tok->location, tok->मूल्य, is_break);
  c_parser_consume_token (parser);
  वापस label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

अटल व्योम
c_parser_statement_after_labels (c_parser *parser, bool *if_p,
				 वृक्ष before_labels,
				 vec<वृक्ष> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष stmt = NULL_वृक्ष;
  bool in_if_block = parser->in_if_block;
  parser->in_if_block = false;
  अगर (if_p != शून्य)
    *if_p = false;

  अगर (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      अवरोध;
    हाल CPP_KEYWORD:
      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  अवरोध;
	हाल RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  अवरोध;
	हाल RID_WHILE:
	  c_parser_while_statement (parser, false, 0, false, if_p, before_labels);
	  अवरोध;
	हाल RID_DO:
	  c_parser_do_statement (parser, false, 0, false, before_labels);
	  अवरोध;
	हाल RID_FOR:
	  c_parser_for_statement (parser, false, 0, false, if_p, before_labels);
	  अवरोध;
	हाल RID_GOTO:
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      वृक्ष name = c_parser_peek_token (parser)->मूल्य;
	      अगर (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_MULT))
	    {
	      काष्ठा c_व्यंजक val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, false, true);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  अन्यथा
	    c_parser_error (parser, "expected identifier or %<*%>");
	  जाओ expect_semicolon;
	हाल RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, false,
				   c_parser_bc_name (parser, false));
	  जाओ expect_semicolon;
	हाल RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, true,
				   c_parser_bc_name (parser, true));
	  जाओ expect_semicolon;
	हाल RID_RETURN:
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_वृक्ष, NULL_वृक्ष,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      काष्ठा c_व्यंजक व्यंजक = c_parser_expression_conv (parser);
	      mark_exp_read (व्यंजक.मूल्य);
	      stmt = c_finish_return (व्यंजक_LOC_OR_LOC (व्यंजक.मूल्य, xloc),
				      व्यंजक.मूल्य, व्यंजक.original_type,
				      astate.musttail_p);
	      जाओ expect_semicolon;
	    }
	  अवरोध;
	हाल RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  अवरोध;
	हाल RID_TRANSACTION_ATOMIC:
	हाल RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  अवरोध;
	हाल RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  जाओ expect_semicolon;
	हाल RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_वृक्ष);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      काष्ठा c_व्यंजक व्यंजक = c_parser_expression (parser);
	      व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, false, false);
	      व्यंजक.मूल्य = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
	      stmt = objc_build_throw_stmt (loc, व्यंजक.मूल्य);
	      जाओ expect_semicolon;
	    }
	  अवरोध;
	हाल RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  अवरोध;
	हाल RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  अवरोध;
	हाल RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    वृक्ष attrs = c_parser_gnu_attributes (parser);
	    bool has_assume = lookup_attribute ("assume", attrs);
	    अगर (has_assume)
	      {
		अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, true);
		अन्यथा
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = false;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    अगर (astate.musttail_p)
	      {
		अगर (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		जाओ restart;
	      }
	    अगर (attribute_fallthrough_p (attrs))
	      {
		अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
		  {
		    वृक्ष fn = build_call_व्यंजक_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_गाँठ, 0);
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
	    अन्यथा अगर (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    अन्यथा अगर (attrs != NULL_वृक्ष)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    अवरोध;
	  }
	शेष:
	  जाओ व्यंजक_stmt;
	}
      अवरोध;
    हाल CPP_SEMICOLON:
      c_parser_consume_token (parser);
      अवरोध;
    हाल CPP_CLOSE_PAREN:
    हाल CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      अवरोध;
    हाल CPP_PRAGMA:
      अगर (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        जाओ restart;
      अवरोध;
    शेष:
    व्यंजक_stmt:
      stmt = c_finish_व्यंजक_stmt (loc, c_parser_expression_conv (parser).मूल्य);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      अवरोध;
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
  अगर (व्यंजक_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_व्यंजक_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

अटल वृक्ष
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष cond;
  cond = c_parser_expression_conv (parser).मूल्य;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, false, शून्य);
  अगर (warn_sequence_point)
    verify_sequence_points (cond);
  वापस cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

अटल वृक्ष
c_parser_paren_condition (c_parser *parser)
{
  वृक्ष cond;
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस error_mark_गाँठ;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  वापस cond;
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

अटल c_व्यंजक
c_parser_selection_header (c_parser *parser, bool switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_व्यंजक व्यंजक;
  bool parse_व्यंजक = true;
  वृक्ष std_attrs;
  bool have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  अगर (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  अन्यथा
    std_attrs = NULL_वृक्ष;
  अगर (c_parser_अग्र_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      व्यंजक.मूल्य
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/false,
					 /*static_assert_ok=*/false,
					 /*empty_ok=*/false,
					 /*nested=*/true,
					 /*start_attr_ok=*/true,
					 /*simple_ok=*/true,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      अन्यथा
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  अगर (!व्यंजक.मूल्य)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      व्यंजक.original_type = error_mark_गाँठ;
	      व्यंजक.set_error ();
	      वापस व्यंजक;
	    }
	  parse_व्यंजक = false;
	}
      अगर (व्यंजक.मूल्य)
	{
	  व्यंजक.original_type = वृक्ष_TYPE (व्यंजक.मूल्य);
	  व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, /*convert_p=*/true,
					   /*read_p=*/true);
	}
    }
  अन्यथा अगर (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      व्यंजक.original_type = error_mark_गाँठ;
      व्यंजक.set_error ();
      वापस व्यंजक;
    }

  अगर (parse_व्यंजक)
    व्यंजक = c_parser_expression_conv (parser);
  अगर (!switch_p)
    {
      व्यंजक.मूल्य = c_objc_common_truthvalue_conversion (loc, व्यंजक.मूल्य);
      व्यंजक.मूल्य = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
      अगर (warn_sequence_point)
	verify_sequence_points (व्यंजक.मूल्य);
    }
  वापस व्यंजक;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

अटल वृक्ष
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस error_mark_गाँठ;
  वृक्ष cond = c_parser_selection_header (parser, /*switch_p=*/false).मूल्य;
  parens.skip_until_found_close (parser);
  वापस cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

अटल वृक्ष
c_parser_c99_block_statement (c_parser *parser, bool *if_p,
			      location_t *loc_after_labels)
{
  वृक्ष block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  वापस c_end_compound_stmt (loc, block, flag_isoc99);
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

अटल वृक्ष
c_parser_if_body (c_parser *parser, bool *if_p,
		  स्थिर token_indent_info &if_tinfo)
{
  वृक्ष block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  वृक्ष before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      अगर (!c_parser_अग्र_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  अन्यथा
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, शून्य, a);
    }

  token_indent_info अग्र_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, अग्र_tinfo);
  अगर (body_loc_after_labels != UNKNOWN_LOCATION
      && अग्र_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, अग्र_tinfo.location,
				    if_tinfo.location, RID_IF);

  वापस c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

अटल वृक्ष
c_parser_else_body (c_parser *parser, स्थिर token_indent_info &else_tinfo,
		    vec<वृक्ष> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  वृक्ष block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  वृक्ष before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
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
      अगर (!c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, शून्य, before_labels, chain, a);
    }

  token_indent_info अग्र_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, अग्र_tinfo);
  अगर (body_loc_after_labels != UNKNOWN_LOCATION
      && अग्र_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, अग्र_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  वापस c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

अटल व्योम
c_parser_if_statement (c_parser *parser, bool *if_p, vec<वृक्ष> *chain)
{
  वृक्ष block;
  location_t loc;
  वृक्ष cond;
  bool nested_if = false;
  वृक्ष first_body, second_body;
  bool in_if_block;

  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = true;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  अगर (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (व्यंजक_LOCATION (cond), cond, &chain);

  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      अगर (warn_duplicated_cond)
	{
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_IF)
	      && chain == शून्य)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = नया vec<वृक्ष> ();
	      अगर (!CONSTANT_CLASS_P (cond) && !वृक्ष_SIDE_EFFECTS (cond))
		chain->safe_धकेलो (cond);
	    }
	  अन्यथा अगर (!c_parser_अग्र_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      अगर (if_p != शून्य)
	*if_p = true;
    }
  अन्यथा
    {
      second_body = NULL_वृक्ष;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      अगर (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      अगर (warn_duplicated_cond)
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

अटल व्योम
c_parser_switch_statement (c_parser *parser, bool *if_p, वृक्ष before_labels)
{
  काष्ठा c_व्यंजक ce;
  वृक्ष block, व्यंजक, body;
  अचिन्हित अक्षर save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  वृक्ष switch_name;
  पूर्णांक अंक_names = c_get_loop_names (before_labels, true, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  bool explicit_cast_p = false;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = true;
      ce = c_parser_selection_header (parser, /*switch_p=*/true);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, true, true);
      व्यंजक = ce.मूल्य;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      व्यंजक = error_mark_गाँठ;
      ce.original_type = error_mark_गाँठ;
    }
  वृक्ष stmt
    = c_start_switch (switch_loc, switch_cond_loc, व्यंजक, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  अगर (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  अन्यथा
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  bool open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t अग्र_loc = c_parser_peek_token (parser)->location;
  अगर (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, अग्र_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  अगर (अंक_names)
    {
      अगर (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_वृक्ष;
      अन्यथा
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (अंक_names);
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

अटल व्योम
c_parser_while_statement (c_parser *parser, bool ivdep, अचिन्हित लघु unroll,
			  bool novector, bool *if_p, वृक्ष before_labels)
{
  वृक्ष block, cond, body;
  अचिन्हित अक्षर save_in_statement;
  location_t loc;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  वृक्ष loop_name;
  पूर्णांक अंक_names = c_get_loop_names (before_labels, false, &loop_name);

  अगर (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->हार = true;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  अगर (ivdep && cond != error_mark_गाँठ)
    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठ,
				  annot_व्यंजक_ivdep_kind),
		   integer_zero_गाँठ);
  अगर (unroll && cond != error_mark_गाँठ)
    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठ,
				  annot_व्यंजक_unroll_kind),
		   build_int_cst (integer_type_गाँठ, unroll));
  अगर (novector && cond != error_mark_गाँठ)
    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठ,
				  annot_व्यंजक_no_vector_kind),
		   integer_zero_गाँठ);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  अगर (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  bool open_brace = c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  अगर (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_वृक्ष;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_वृक्ष,
			NULL_वृक्ष));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  अगर (अंक_names)
    c_release_loop_names (अंक_names);

  token_indent_info अग्र_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, अग्र_tinfo);

  अगर (अग्र_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, अग्र_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

अटल व्योम
c_parser_do_statement (c_parser *parser, bool ivdep, अचिन्हित लघु unroll,
		       bool novector, वृक्ष before_labels)
{
  वृक्ष block, cond, body;
  अचिन्हित अक्षर save_in_statement;
  location_t loc;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_DO));
  वृक्ष loop_name;
  पूर्णांक अंक_names = c_get_loop_names (before_labels, false, &loop_name);

  अगर (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->हार = true;
    }

  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  अगर (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, शून्य);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  अगर (अंक_names)
    {
      अगर (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_वृक्ष;
      c_release_loop_names (अंक_names);
    }
  cond = c_parser_paren_condition (parser);
  अगर (ivdep && cond != error_mark_गाँठ)
    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठ,
				  annot_व्यंजक_ivdep_kind),
		   integer_zero_गाँठ);
  अगर (unroll && cond != error_mark_गाँठ)
    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठ,
				  annot_व्यंजक_unroll_kind),
 		   build_int_cst (integer_type_गाँठ, unroll));
  अगर (novector && cond != error_mark_गाँठ)
    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
		   build_int_cst (integer_type_गाँठ,
				  annot_व्यंजक_no_vector_kind),
		   integer_zero_गाँठ);
  अगर (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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

अटल व्योम
c_parser_for_statement (c_parser *parser, bool ivdep, अचिन्हित लघु unroll,
			bool novector, bool *if_p, वृक्ष before_labels)
{
  वृक्ष block, cond, incr, body;
  अचिन्हित अक्षर save_in_statement;
  वृक्ष save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  वृक्ष object_expression;
  /* Silence the bogus uninitialized warning.  */
  वृक्ष collection_expression = शून्य;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  bool is_foreach_statement = false;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  वृक्ष loop_name;
  पूर्णांक अंक_names = c_get_loop_names (before_labels, false, &loop_name);

  अगर (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->हार = true;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_गाँठ;
  incr = error_mark_गाँठ;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_गाँठ;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = false;
	  c_parser_consume_token (parser);
	  c_finish_व्यंजक_stmt (loc, NULL_वृक्ष);
	}
      अन्यथा अगर (c_parser_अग्र_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, true, true, true, true, true,
					 false, &object_expression);
	  parser->objc_could_be_foreach_context = false;

	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = true;
	      अगर (check_for_loop_decls (for_loc, true) == NULL_वृक्ष)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  अन्यथा
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  जबतक (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      पूर्णांक ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, true, true, true, true,
					     true, false, &object_expression);
	      parser->objc_could_be_foreach_context = false;

	      restore_extension_diagnostics (ext);
	      अगर (c_parser_अग्र_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = true;
		  अगर (check_for_loop_decls (for_loc, true) == NULL_वृक्ष)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      अन्यथा
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  अन्यथा
	    जाओ init_व्यंजक;
	}
      अन्यथा
	{
	init_व्यंजक:
	  {
	    काष्ठा c_व्यंजक ce;
	    वृक्ष init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.मूल्य;
	    parser->objc_could_be_foreach_context = false;
	    अगर (c_parser_अग्र_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = true;
		अगर (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, false, शून्य);
	      }
	    अन्यथा
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, true, false);
		init_expression = ce.मूल्य;
		c_finish_व्यंजक_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      अगर (!is_foreach_statement)
	{
	  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	    {
	      अगर (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_गाँठ;
		}
	      अन्यथा अगर (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_गाँठ;
		}
	      अन्यथा
		{
		  c_parser_consume_token (parser);
		  cond = NULL_वृक्ष;
		}
	    }
	  अन्यथा
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  अगर (ivdep && cond != error_mark_गाँठ)
	    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
			   build_int_cst (integer_type_गाँठ,
					  annot_व्यंजक_ivdep_kind),
			   integer_zero_गाँठ);
	  अगर (unroll && cond != error_mark_गाँठ)
	    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
 			   build_int_cst (integer_type_गाँठ,
					  annot_व्यंजक_unroll_kind),
			   build_int_cst (integer_type_गाँठ, unroll));
	  अगर (novector && cond && cond != error_mark_गाँठ)
	    cond = build3 (ANNOTATE_व्यंजक, वृक्ष_TYPE (cond), cond,
			   build_int_cst (integer_type_गाँठ,
					  annot_व्यंजक_no_vector_kind),
			   integer_zero_गाँठ);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	{
	  अगर (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_गाँठ;
	    }
	  अन्यथा
	    incr = c_process_व्यंजक_stmt (loc, NULL_वृक्ष);
	}
      अन्यथा
	{
	  अगर (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).मूल्य, false, शून्य);
	  अन्यथा
	    {
	      काष्ठा c_व्यंजक ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, true, false);
	      incr = c_process_व्यंजक_stmt (loc, ce.मूल्य);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  अगर (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      अगर (loop_name)
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
  अगर (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  bool open_brace = c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  अगर (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_वृक्ष;
      DECL_CHAIN (objc_foreach_break_label) = NULL_वृक्ष;
    }

  अगर (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  अन्यथा
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_वृक्ष, cond, incr,
			  body, NULL_वृक्ष,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_वृक्ष, NULL_वृक्ष, NULL_वृक्ष));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info अग्र_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, अग्र_tinfo);

  अगर (अग्र_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, अग्र_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  अगर (अंक_names)
    c_release_loop_names (अंक_names);
  अगर (is_foreach_statement)
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

अटल वृक्ष
c_parser_asm_statement (c_parser *parser)
{
  वृक्ष str, outputs, inputs, clobbers, labels, ret;
  bool simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  पूर्णांक section, nsections;

  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  क्रम (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      चयन (token->keyword)
	{
	हाल RID_VOLATILE:
	  अगर (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मूल्य);
	      inform (volatile_loc, "first seen here");
	    }
	  अन्यथा
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  जारी;

	हाल RID_INLINE:
	  अगर (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मूल्य);
	      inform (inline_loc, "first seen here");
	    }
	  अन्यथा
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  जारी;

	हाल RID_GOTO:
	  अगर (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->मूल्य);
	      inform (goto_loc, "first seen here");
	    }
	  अन्यथा
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  जारी;

	हाल RID_CONST:
	हाल RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->मूल्य);
	  c_parser_consume_token (parser);
	  जारी;

	शेष:
	  अवरोध;
	}
      अवरोध;
    }

  bool is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  bool is_inline = (inline_loc != UNKNOWN_LOCATION);
  bool is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = शून्य;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    जाओ error;

  str = c_parser_asm_string_literal (parser);
  अगर (str == NULL_वृक्ष)
    जाओ error_close_paren;

  simple = true;
  outputs = NULL_वृक्ष;
  inputs = NULL_वृक्ष;
  clobbers = NULL_वृक्ष;
  labels = NULL_वृक्ष;

  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    जाओ done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  क्रम (section = 0; section < nsections; ++section)
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  अगर (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      जाओ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	जाओ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = false;

      अगर ((!c_parser_अग्र_token_is (parser, CPP_COLON)
	   && !c_parser_अग्र_token_is (parser, CPP_SCOPE)
	   && !c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	चयन (section)
	  {
	  हाल 0:
	    outputs = c_parser_asm_operands (parser);
	    अवरोध;
	  हाल 1:
	    inputs = c_parser_asm_operands (parser);
	    अवरोध;
	  हाल 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    अवरोध;
	  हाल 3:
	    labels = c_parser_asm_goto_operands (parser);
	    अवरोध;
	  शेष:
	    gcc_unreachable ();
	  }

      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	जाओ done_asm;
    }

 done_asm:
  अगर (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
      जाओ error;
    }

  अगर (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_व्यंजक (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  वापस ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
  जाओ error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

अटल वृक्ष
c_parser_asm_operands (c_parser *parser)
{
  वृक्ष list = NULL_वृक्ष;
  जबतक (true)
    {
      वृक्ष name, str;
      काष्ठा c_व्यंजक व्यंजक;
      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_लंबाई (id),
				   IDENTIFIER_POINTER (id));
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, शून्य);
	      वापस NULL_वृक्ष;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      अन्यथा
	name = NULL_वृक्ष;
      str = c_parser_asm_string_literal (parser);
      अगर (str == NULL_वृक्ष)
	वापस NULL_वृक्ष;
      matching_parens parens;
      अगर (!parens.require_open (parser))
	वापस NULL_वृक्ष;
      व्यंजक = c_parser_expression (parser);
      mark_exp_read (व्यंजक.मूल्य);
      अगर (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	  वापस NULL_वृक्ष;
	}
      list = chainon (list, build_वृक्ष_list (build_वृक्ष_list (name, str),
					     व्यंजक.मूल्य));
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
    }
  वापस list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

अटल वृक्ष
c_parser_asm_clobbers (c_parser *parser)
{
  वृक्ष list = NULL_वृक्ष;
  जबतक (true)
    {
      वृक्ष str = c_parser_asm_string_literal (parser);
      अगर (str)
	list = वृक्ष_cons (NULL_वृक्ष, str, list);
      अन्यथा
	वापस NULL_वृक्ष;
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
    }
  वापस list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

अटल वृक्ष
c_parser_asm_goto_operands (c_parser *parser)
{
  वृक्ष list = NULL_वृक्ष;
  जबतक (true)
    {
      वृक्ष name, label;

      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->मूल्य;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  वृक्ष_USED (label) = 1;
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected identifier");
	  वापस NULL_वृक्ष;
	}

      name = build_string (IDENTIFIER_लंबाई (name),
			   IDENTIFIER_POINTER (name));
      list = वृक्ष_cons (name, label, list);
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	वापस nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

काष्ठा c_व्यंजक
c_parser_string_literal (c_parser *parser, bool translate, bool wide_ok)
{
  काष्ठा c_व्यंजक ret;
  माप_प्रकार गिनती;
  काष्ठा obstack str_ob;
  काष्ठा obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  क्रमागत cpp_ttype type;
  वृक्ष मूल्य, string_वृक्ष;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (पंक्ति_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   शून्य);
  type = tok->type;
  चयन (type)
    {
    हाल CPP_STRING:
    हाल CPP_WSTRING:
    हाल CPP_STRING16:
    हाल CPP_STRING32:
    हाल CPP_UTF8STRING:
      string_वृक्ष = tok->मूल्य;
      अवरोध;

    शेष:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.मूल्य = NULL_वृक्ष;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_वृक्ष;
      वापस ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  चयन (c_parser_peek_2nd_token (parser)->type)
    {
    शेष:
      c_parser_consume_token (parser);
      str.text = (स्थिर अचिन्हित अक्षर *) वृक्ष_STRING_POINTER (string_वृक्ष);
      str.len = वृक्ष_STRING_लंबाई (string_वृक्ष);
      गिनती = 1;
      strs = &str;
      अवरोध;

    हाल CPP_STRING:
    हाल CPP_WSTRING:
    हाल CPP_STRING16:
    हाल CPP_STRING32:
    हाल CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      गिनती = 0;
      करो
	{
	  c_parser_consume_token (parser);
	  गिनती++;
	  str.text = (स्थिर अचिन्हित अक्षर *) वृक्ष_STRING_POINTER (string_वृक्ष);
	  str.len = वृक्ष_STRING_लंबाई (string_वृक्ष);
	  अगर (type != tok->type)
	    {
	      अगर (type == CPP_STRING)
		type = tok->type;
	      अन्यथा अगर (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, माप (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, माप (location_t));
	  tok = c_parser_peek_token (parser);
	  string_वृक्ष = tok->मूल्य;
	  last_tok_loc
	    = linemap_resolve_location (पंक्ति_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, शून्य);
	}
      जबतक (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  अगर (गिनती > 1 && !in_system_header_at (निवेश_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  अगर ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, गिनती, &istr, type)))
    {
      मूल्य = build_string (istr.len, (स्थिर अक्षर *) istr.text);
      मुक्त (const_cast<अचिन्हित अक्षर *> (istr.text));
      अगर (गिनती > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (गिनती, locs);
	}
    }
  अन्यथा
    {
      अगर (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      चयन (type)
	{
	शेष:
	हाल CPP_STRING:
	हाल CPP_UTF8STRING:
	  अगर (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      मूल्य = build_string (TYPE_PRECISION (char8_type_गाँठ)
				    / TYPE_PRECISION (char_type_गाँठ),
				    "");  /* char8_t is 8 bits */
	    }
	  अन्यथा
	    मूल्य = build_string (1, "");
	  अवरोध;
	हाल CPP_STRING16:
	  मूल्य = build_string (TYPE_PRECISION (char16_type_गाँठ)
				/ TYPE_PRECISION (char_type_गाँठ),
				"\0");  /* char16_t is 16 bits */
	  अवरोध;
	हाल CPP_STRING32:
	  मूल्य = build_string (TYPE_PRECISION (char32_type_गाँठ)
				/ TYPE_PRECISION (char_type_गाँठ),
				"\0\0\0");  /* char32_t is 32 bits */
	  अवरोध;
	हाल CPP_WSTRING:
	  मूल्य = build_string (TYPE_PRECISION (wchar_type_गाँठ)
				/ TYPE_PRECISION (char_type_गाँठ),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  अवरोध;
        }
    }

  चयन (type)
    {
    शेष:
    हाल CPP_STRING:
      वृक्ष_TYPE (मूल्य) = char_array_type_गाँठ;
      अवरोध;
    हाल CPP_UTF8STRING:
      अगर (flag_char8_t)
	वृक्ष_TYPE (मूल्य) = char8_array_type_गाँठ;
      अन्यथा
	वृक्ष_TYPE (मूल्य) = char_array_type_गाँठ;
      अवरोध;
    हाल CPP_STRING16:
      वृक्ष_TYPE (मूल्य) = char16_array_type_गाँठ;
      अवरोध;
    हाल CPP_STRING32:
      वृक्ष_TYPE (मूल्य) = char32_array_type_गाँठ;
      अवरोध;
    हाल CPP_WSTRING:
      वृक्ष_TYPE (मूल्य) = wchar_array_type_गाँठ;
    }
  मूल्य = fix_string_type (मूल्य);

  अगर (गिनती > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.मूल्य = मूल्य;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_वृक्ष;
  set_c_व्यंजक_source_range (&ret, get_range_from_loc (पंक्ति_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = true;
  वापस ret;
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

अटल काष्ठा c_व्यंजक
c_parser_व्यंजक_no_commas (c_parser *parser, काष्ठा c_व्यंजक *after,
			 वृक्ष omp_atomic_lhs)
{
  काष्ठा c_व्यंजक lhs, rhs, ret;
  क्रमागत वृक्ष_code code;
  location_t op_location, exp_location;
  bool save_in_omp_for = c_in_omp_for;
  c_in_omp_for = false;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_EQ:
      code = NOP_व्यंजक;
      अवरोध;
    हाल CPP_MULT_EQ:
      code = MULT_व्यंजक;
      अवरोध;
    हाल CPP_DIV_EQ:
      code = TRUNC_DIV_व्यंजक;
      अवरोध;
    हाल CPP_MOD_EQ:
      code = TRUNC_MOD_व्यंजक;
      अवरोध;
    हाल CPP_PLUS_EQ:
      code = PLUS_व्यंजक;
      अवरोध;
    हाल CPP_MINUS_EQ:
      code = MINUS_व्यंजक;
      अवरोध;
    हाल CPP_LSHIFT_EQ:
      code = LSHIFT_व्यंजक;
      अवरोध;
    हाल CPP_RSHIFT_EQ:
      code = RSHIFT_व्यंजक;
      अवरोध;
    हाल CPP_AND_EQ:
      code = BIT_AND_व्यंजक;
      अवरोध;
    हाल CPP_XOR_EQ:
      code = BIT_XOR_व्यंजक;
      अवरोध;
    हाल CPP_OR_EQ:
      code = BIT_IOR_व्यंजक;
      अवरोध;
    शेष:
      c_in_omp_for = save_in_omp_for;
      वापस lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_व्यंजक_no_commas (parser, शून्य);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, true, true);

  ret.मूल्य = build_modify_व्यंजक (op_location, lhs.मूल्य, lhs.original_type,
				 code, exp_location, rhs.मूल्य,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_व्यंजक_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  अगर (code == NOP_व्यंजक)
    ret.original_code = MODIFY_व्यंजक;
  अन्यथा
    {
      suppress_warning (ret.मूल्य, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = शून्य;
  c_in_omp_for = save_in_omp_for;
  वापस ret;
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

अटल काष्ठा c_व्यंजक
c_parser_conditional_expression (c_parser *parser, काष्ठा c_व्यंजक *after,
				 वृक्ष omp_atomic_lhs)
{
  काष्ठा c_व्यंजक cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  bool save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_द्विआधारी_expression (parser, after, omp_atomic_lhs);

  अगर (c_parser_अग्र_token_is_not (parser, CPP_QUERY))
    वापस cond;
  c_omp_array_section_p = false;
  अगर (cond.मूल्य != error_mark_गाँठ)
    start = cond.get_start ();
  अन्यथा
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, true, true);
  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
    {
      वृक्ष eptype = NULL_वृक्ष;

      location_t मध्य_loc = c_parser_peek_token (parser)->location;
      pedwarn (मध्य_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      अगर (वृक्ष_CODE (cond.मूल्य) == EXCESS_PRECISION_व्यंजक)
	{
	  eptype = वृक्ष_TYPE (cond.मूल्य);
	  cond.मूल्य = वृक्ष_OPERAND (cond.मूल्य, 0);
	}
      वृक्ष e = cond.मूल्य;
      जबतक (वृक्ष_CODE (e) == COMPOUND_व्यंजक)
	e = वृक्ष_OPERAND (e, 1);
      warn_for_omitted_condop (मध्य_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.मूल्य = save_व्यंजक (default_conversion (cond.मूल्य));
      अगर (eptype)
	exp1.मूल्य = build1 (EXCESS_PRECISION_व्यंजक, eptype, exp1.मूल्य);
      exp1.original_type = शून्य;
      exp1.src_range = cond.src_range;
      cond.मूल्य = c_objc_common_truthvalue_conversion (cond_loc, exp1.मूल्य);
      c_inhibit_evaluation_warnings += cond.मूल्य == truthvalue_true_गाँठ;
    }
  अन्यथा
    {
      cond.मूल्य
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.मूल्य));
      c_inhibit_evaluation_warnings += cond.मूल्य == truthvalue_false_गाँठ;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.मूल्य);
      c_inhibit_evaluation_warnings +=
	((cond.मूल्य == truthvalue_true_गाँठ)
	 - (cond.मूल्य == truthvalue_false_गाँठ));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.मूल्य == truthvalue_true_गाँठ;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = शून्य;
      c_omp_array_section_p = save_c_omp_array_section_p;
      वापस ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, शून्य, NULL_वृक्ष);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, true, true);
  }
  c_inhibit_evaluation_warnings -= cond.मूल्य == truthvalue_true_गाँठ;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  अगर (UNLIKELY (omp_atomic_lhs != शून्य)
      && (वृक्ष_CODE (cond.मूल्य) == GT_व्यंजक
	  || वृक्ष_CODE (cond.मूल्य) == LT_व्यंजक
	  || वृक्ष_CODE (cond.मूल्य) == EQ_व्यंजक)
      && c_वृक्ष_equal (exp2.मूल्य, omp_atomic_lhs)
      && (c_वृक्ष_equal (वृक्ष_OPERAND (cond.मूल्य, 0), omp_atomic_lhs)
	  || c_वृक्ष_equal (वृक्ष_OPERAND (cond.मूल्य, 1), omp_atomic_lhs)))
    ret.मूल्य = build3_loc (colon_loc, COND_व्यंजक, वृक्ष_TYPE (omp_atomic_lhs),
			    cond.मूल्य, exp1.मूल्य, exp2.मूल्य);
  अन्यथा
    ret.मूल्य
      = build_conditional_व्यंजक (colon_loc, cond.मूल्य,
				cond.original_code == C_MAYBE_CONST_व्यंजक,
				exp1.मूल्य, exp1.original_type, loc1,
				exp2.मूल्य, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  अगर (exp1.मूल्य == error_mark_गाँठ || exp2.मूल्य == error_mark_गाँठ)
    ret.original_type = शून्य;
  अन्यथा
    {
      वृक्ष t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : वृक्ष_TYPE (exp1.मूल्य);
      t2 = exp2.original_type ? exp2.original_type : वृक्ष_TYPE (exp2.मूल्य);
      ret.original_type = ((t1 != error_mark_गाँठ
			    && t2 != error_mark_गाँठ
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : शून्य);
    }
  set_c_व्यंजक_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  वापस ret;
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

अटल काष्ठा c_व्यंजक
c_parser_द्विआधारी_expression (c_parser *parser, काष्ठा c_व्यंजक *after,
			    वृक्ष omp_atomic_lhs)
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

  काष्ठा {
    /* The expression at this stack level.  */
    काष्ठा c_व्यंजक व्यंजक;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    क्रमागत c_parser_prec prec;
    /* The operation on its left.  */
    क्रमागत वृक्ष_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    वृक्ष sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    वृक्ष orig_व्यंजक;
  } ढेर[अंक_PRECS];
  पूर्णांक sp;
  /* Location of the binary operator.  */
  location_t द्विआधारी_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#घोषणा निकालो_2								      \
  करो {									      \
    चयन (ढेर[sp].op)						      \
      {									      \
      हाल TRUTH_ANDIF_व्यंजक:						      \
	c_inhibit_evaluation_warnings -= (ढेर[sp - 1].व्यंजक.मूल्य	      \
					  == truthvalue_false_गाँठ);	      \
	अवरोध;								      \
      हाल TRUTH_ORIF_व्यंजक:						      \
	c_inhibit_evaluation_warnings -= (ढेर[sp - 1].व्यंजक.मूल्य	      \
					  == truthvalue_true_गाँठ);	      \
	अवरोध;								      \
      हाल TRUNC_DIV_व्यंजक:						      \
	अगर ((ढेर[sp - 1].व्यंजक.original_code == SIZEOF_व्यंजक		      \
	     || ढेर[sp - 1].व्यंजक.original_code == PAREN_SIZEOF_व्यंजक)	      \
	    && (ढेर[sp].व्यंजक.original_code == SIZEOF_व्यंजक		      \
		|| ढेर[sp].व्यंजक.original_code == PAREN_SIZEOF_व्यंजक))	      \
	  {								      \
	    वृक्ष type0 = ढेर[sp - 1].sizeof_arg;			      \
	    वृक्ष type1 = ढेर[sp].sizeof_arg;				      \
	    वृक्ष first_arg = type0;					      \
	    अगर (!TYPE_P (type0))					      \
	      type0 = वृक्ष_TYPE (type0);				      \
	    अगर (!TYPE_P (type1))					      \
	      type1 = वृक्ष_TYPE (type1);				      \
	    अगर (POINTER_TYPE_P (type0)					      \
		&& comptypes (वृक्ष_TYPE (type0), type1)			      \
		&& !(वृक्ष_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		अगर (warning_at (ढेर[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  अगर (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    अन्यथा अगर (वृक्ष_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (वृक्ष_TYPE (type0)))  \
		     && ढेर[sp].व्यंजक.original_code != PAREN_SIZEOF_व्यंजक)    \
	      maybe_warn_sizeof_array_div (ढेर[sp].loc, first_arg, type0,   \
					   ढेर[sp].sizeof_arg, type1);      \
	  }								      \
	अवरोध;								      \
      शेष:								      \
	अवरोध;								      \
      }									      \
    ढेर[sp - 1].व्यंजक							      \
      = convert_lvalue_to_rvalue (ढेर[sp - 1].loc,			      \
				  ढेर[sp - 1].व्यंजक, true, true);	      \
    ढेर[sp].व्यंजक							      \
      = convert_lvalue_to_rvalue (ढेर[sp].loc,			      \
				  ढेर[sp].व्यंजक, true, true);		      \
    अगर (UNLIKELY (omp_atomic_lhs != NULL_वृक्ष) && sp == 1		      \
	&& ((c_parser_अग्र_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << ढेर[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_अग्र_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_गाँठ			      \
		     && c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (ढेर[sp].prec == PREC_REL || ढेर[sp].prec == PREC_EQ)))\
	&& ढेर[sp].op != TRUNC_MOD_व्यंजक				      \
	&& ढेर[sp].op != GE_व्यंजक					      \
	&& ढेर[sp].op != LE_व्यंजक					      \
	&& ढेर[sp].op != NE_व्यंजक					      \
	&& ढेर[0].व्यंजक.मूल्य != error_mark_गाँठ			      \
	&& ढेर[1].व्यंजक.मूल्य != error_mark_गाँठ			      \
	&& (omp_atomic_lhs == void_list_गाँठ				      \
	    || c_वृक्ष_equal (ढेर[0].व्यंजक.मूल्य, omp_atomic_lhs)	      \
	    || c_वृक्ष_equal (ढेर[1].व्यंजक.मूल्य, omp_atomic_lhs)	      \
	    || (ढेर[sp].op == EQ_व्यंजक					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	वृक्ष t = make_गाँठ (ढेर[1].op);				      \
	वृक्ष_TYPE (t) = वृक्ष_TYPE (ढेर[0].व्यंजक.मूल्य);		      \
	वृक्ष_OPERAND (t, 0) = ढेर[0].व्यंजक.मूल्य;			      \
	वृक्ष_OPERAND (t, 1) = ढेर[1].व्यंजक.मूल्य;			      \
	ढेर[0].व्यंजक.मूल्य = t;					      \
	ढेर[0].व्यंजक.m_decimal = 0;					      \
      }									      \
    अन्यथा								      \
      ढेर[sp - 1].व्यंजक = parser_build_द्विआधारी_op (ढेर[sp].loc,	      \
						   ढेर[sp].op,	      \
						   ढेर[sp - 1].व्यंजक,	      \
						   ढेर[sp].व्यंजक,	      \
						   ढेर[sp - 1].orig_व्यंजक);  \
    ढेर[sp - 1].orig_व्यंजक = NULL_वृक्ष;				      \
    sp--;								      \
  } जबतक (0)
  gcc_assert (!after || c_dialect_objc ());
  ढेर[0].loc = c_parser_peek_token (parser)->location;
  ढेर[0].व्यंजक = c_parser_cast_expression (parser, after);
  ढेर[0].prec = PREC_NONE;
  ढेर[0].sizeof_arg = c_last_sizeof_arg;
  ढेर[0].orig_व्यंजक = NULL_वृक्ष;
  sp = 0;
  जबतक (true)
    {
      क्रमागत c_parser_prec oprec;
      क्रमागत वृक्ष_code ocode;
      source_range src_range;
      अगर (parser->error)
	जाओ out;
      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_व्यंजक;
	  अवरोध;
	हाल CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_व्यंजक;
	  अवरोध;
	हाल CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_व्यंजक;
	  अवरोध;
	हाल CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_व्यंजक;
	  अवरोध;
	हाल CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_व्यंजक;
	  अवरोध;
	हाल CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_व्यंजक;
	  अवरोध;
	हाल CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_व्यंजक;
	  अवरोध;
	हाल CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_व्यंजक;
	  अवरोध;
	हाल CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_व्यंजक;
	  अवरोध;
	हाल CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_व्यंजक;
	  अवरोध;
	हाल CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_व्यंजक;
	  अवरोध;
	हाल CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_व्यंजक;
	  अवरोध;
	हाल CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_व्यंजक;
	  अवरोध;
	हाल CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_व्यंजक;
	  अवरोध;
	हाल CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_व्यंजक;
	  अवरोध;
	हाल CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_व्यंजक;
	  अवरोध;
	हाल CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_व्यंजक;
	  अवरोध;
	हाल CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_व्यंजक;
	  अवरोध;
	शेष:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  जाओ out;
	}
      द्विआधारी_loc = c_parser_peek_token (parser)->location;
      जबतक (oprec <= ढेर[sp].prec)
	निकालो_2;
      c_parser_consume_token (parser);
      चयन (ocode)
	{
	हाल TRUTH_ANDIF_व्यंजक:
	  src_range = ढेर[sp].व्यंजक.src_range;
	  ढेर[sp].व्यंजक
	    = convert_lvalue_to_rvalue (ढेर[sp].loc,
					ढेर[sp].व्यंजक, true, true);
	  ढेर[sp].orig_व्यंजक = ढेर[sp].व्यंजक.मूल्य;
	  ढेर[sp].व्यंजक.मूल्य = c_objc_common_truthvalue_conversion
	    (ढेर[sp].loc, default_conversion (ढेर[sp].व्यंजक.मूल्य));
	  c_inhibit_evaluation_warnings += (ढेर[sp].व्यंजक.मूल्य
					    == truthvalue_false_गाँठ);
	  set_c_व्यंजक_source_range (&ढेर[sp].व्यंजक, src_range);
	  अवरोध;
	हाल TRUTH_ORIF_व्यंजक:
	  src_range = ढेर[sp].व्यंजक.src_range;
	  ढेर[sp].व्यंजक
	    = convert_lvalue_to_rvalue (ढेर[sp].loc,
					ढेर[sp].व्यंजक, true, true);
	  ढेर[sp].orig_व्यंजक = ढेर[sp].व्यंजक.मूल्य;
	  ढेर[sp].व्यंजक.मूल्य = c_objc_common_truthvalue_conversion
	    (ढेर[sp].loc, default_conversion (ढेर[sp].व्यंजक.मूल्य));
	  c_inhibit_evaluation_warnings += (ढेर[sp].व्यंजक.मूल्य
					    == truthvalue_true_गाँठ);
	  set_c_व्यंजक_source_range (&ढेर[sp].व्यंजक, src_range);
	  अवरोध;
	शेष:
	  अवरोध;
	}
      sp++;
      ढेर[sp].loc = द्विआधारी_loc;
      ढेर[sp].व्यंजक = c_parser_cast_expression (parser, शून्य);
      ढेर[sp].prec = oprec;
      ढेर[sp].op = ocode;
      ढेर[sp].sizeof_arg = c_last_sizeof_arg;
      ढेर[sp].orig_व्यंजक = NULL_वृक्ष;
    }
 out:
  जबतक (sp > 0)
    निकालो_2;
  वापस ढेर[0].व्यंजक;
#अघोषित निकालो_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

अटल काष्ठा c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  bool seen_scspec = false;
  काष्ठा c_declspecs *specs = build_null_declspecs ();
  जबतक (c_parser_अग्र_token_is (parser, CPP_KEYWORD))
    {
      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_CONSTEXPR:
	हाल RID_REGISTER:
	हाल RID_STATIC:
	हाल RID_THREAD:
	  seen_scspec = true;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->मूल्य);
	  c_parser_consume_token (parser);
	  अवरोध;
	शेष:
	  जाओ out;
	}
    }
 out:
  वापस seen_scspec ? specs : शून्य;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

अटल काष्ठा c_व्यंजक
c_parser_cast_expression (c_parser *parser, काष्ठा c_व्यंजक *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  अगर (after)
    वापस c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      काष्ठा c_declspecs *scspecs;
      काष्ठा c_type_name *type_name;
      काष्ठा c_व्यंजक ret;
      काष्ठा c_व्यंजक व्यंजक;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, true);
      parens.skip_until_found_close (parser);
      अगर (type_name == शून्य)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = शून्य;
	  वापस ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_जोड़ो (type_name->specs->type);

      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
	वापस c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      अगर (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      अगर (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
	व्यंजक = c_parser_cast_expression (parser, शून्य);
	व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, true, true);
      }
      ret.मूल्य = c_cast_व्यंजक (cast_loc, type_name, व्यंजक.मूल्य);
      अगर (ret.मूल्य && व्यंजक.मूल्य)
	set_c_व्यंजक_source_range (&ret, cast_loc, व्यंजक.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = शून्य;
      ret.m_decimal = 0;
      वापस ret;
    }
  अन्यथा
    वापस c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

अटल व्योम
mark_exp_read_cond (वृक्ष exp)
{
  अगर ((VAR_P (exp) || वृक्ष_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    वापस;

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

अटल काष्ठा c_व्यंजक
c_parser_unary_expression (c_parser *parser)
{
  पूर्णांक ext;
  काष्ठा c_व्यंजक ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = शून्य;
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, शून्य);
      mark_exp_read_cond (op.मूल्य);
      op = default_function_array_conversion (exp_loc, op);
      वापस parser_build_unary_op (op_loc, PREINCREMENT_व्यंजक, op);
    हाल CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, शून्य);
      mark_exp_read_cond (op.मूल्य);
      op = default_function_array_conversion (exp_loc, op);
      वापस parser_build_unary_op (op_loc, PREDECREMENT_व्यंजक, op);
    हाल CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, शून्य);
      mark_exp_read (op.मूल्य);
      वापस parser_build_unary_op (op_loc, ADDR_व्यंजक, op);
    हाल CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, शून्य);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.मूल्य = build_indirect_ref (combined_loc, op.मूल्य, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	वापस ret;
      }
    हाल CPP_PLUS:
      अगर (!c_dialect_objc () && !in_system_header_at (निवेश_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, शून्य);
      op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
      वापस parser_build_unary_op (op_loc, CONVERT_व्यंजक, op);
    हाल CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, शून्य);
      op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
      वापस parser_build_unary_op (op_loc, NEGATE_व्यंजक, op);
    हाल CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, शून्य);
      op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
      वापस parser_build_unary_op (op_loc, BIT_NOT_व्यंजक, op);
    हाल CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, शून्य);
      op = convert_lvalue_to_rvalue (exp_loc, op, true, true);
      वापस parser_build_unary_op (op_loc, TRUTH_NOT_व्यंजक, op);
    हाल CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  ret.मूल्य = finish_label_address_व्यंजक
	    (c_parser_peek_token (parser)->मूल्य, op_loc);
	  set_c_व्यंजक_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      वापस ret;
    हाल CPP_KEYWORD:
      {
	क्रमागत rid rid = c_parser_peek_token (parser)->keyword;
	चयन (rid)
	  {
	  हाल RID_COUNTOF:
	  हाल RID_SIZEOF:
	    वापस c_parser_sizeof_or_countof_expression (parser, rid);
	  हाल RID_ALIGNOF:
	    वापस c_parser_alignof_expression (parser);
	  हाल RID_MAXOF:
	  हाल RID_MINOF:
	    वापस c_parser_maxof_or_minof_expression (parser, rid);
	  हाल RID_BUILTIN_HAS_ATTRIBUTE:
	    वापस c_parser_has_attribute_expression (parser);
	  हाल RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, शून्य);
	    restore_extension_diagnostics (ext);
	    वापस ret;
	  हाल RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, शून्य);
	    op = default_function_array_conversion (exp_loc, op);
	    वापस parser_build_unary_op (op_loc, REALPART_व्यंजक, op);
	  हाल RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, शून्य);
	    op = default_function_array_conversion (exp_loc, op);
	    वापस parser_build_unary_op (op_loc, IMAGPART_व्यंजक, op);
	  हाल RID_TRANSACTION_ATOMIC:
	  हाल RID_TRANSACTION_RELAXED:
	    वापस c_parser_transaction_expression (parser, rid);
	  हाल RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.मूल्य = void_गाँठ;
	    set_c_व्यंजक_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    वापस ret;
	  शेष:
	    वापस c_parser_postfix_expression (parser);
	  }
      }
    शेष:
      वापस c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

अटल काष्ठा c_व्यंजक
c_parser_sizeof_or_countof_expression (c_parser *parser, क्रमागत rid rid)
{
  स्थिर अक्षर *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  काष्ठा c_व्यंजक व्यंजक;
  काष्ठा c_व्यंजक परिणाम;
  location_t व्यंजक_loc;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  अगर (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  अगर (rid == RID_COUNTOF)
    in_countof++;
  अन्यथा
    in_sizeof++;
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      काष्ठा c_declspecs *scspecs;
      काष्ठा c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      व्यंजक_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, true);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      अगर (type_name == शून्य)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  व्यंजक.set_error ();
	  जाओ Xof_व्यंजक;
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
	{
	  व्यंजक = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       व्यंजक_loc);
	  finish = व्यंजक.get_finish ();
	  जाओ Xof_व्यंजक;
	}
      /* sizeof ( type-name ).  */
      अगर (scspecs)
	error_at (व्यंजक_loc, "storage class specifier in %qs", op_name);
      अगर (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      अगर (rid == RID_COUNTOF)
	{
	  in_countof--;
	  परिणाम = c_व्यंजक_countof_type (व्यंजक_loc, type_name);
	}
      अन्यथा
	{
	  in_sizeof--;
	  परिणाम = c_व्यंजक_sizeof_type (व्यंजक_loc, type_name);
	}
    }
  अन्यथा
    {
      व्यंजक_loc = c_parser_peek_token (parser)->location;
      व्यंजक = c_parser_unary_expression (parser);
      finish = व्यंजक.get_finish ();
    Xof_व्यंजक:
      c_inhibit_evaluation_warnings--;
      अगर (rid == RID_COUNTOF)
	in_countof--;
      अन्यथा
	in_sizeof--;
      mark_exp_read (व्यंजक.मूल्य);
      अगर (वृक्ष_CODE (व्यंजक.मूल्य) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्ष_OPERAND (व्यंजक.मूल्य, 1)))
	error_at (व्यंजक_loc, "%qs applied to a bit-field", op_name);
      अगर (rid == RID_COUNTOF)
	परिणाम = c_व्यंजक_countof_व्यंजक (व्यंजक_loc, व्यंजक);
      अन्यथा
	परिणाम = c_व्यंजक_sizeof_व्यंजक (व्यंजक_loc, व्यंजक);
    }
  अगर (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_व्यंजक_source_range (&परिणाम, start, finish);
  वापस परिणाम;
}

/* Parse an alignof expression.  */

अटल काष्ठा c_व्यंजक
c_parser_alignof_expression (c_parser *parser)
{
  काष्ठा c_व्यंजक व्यंजक;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  वृक्ष alignof_spelling = c_parser_peek_token (parser)->मूल्य;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_ALIGNOF));
  bool is_c11_alignof = (म_भेद (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || म_भेद (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  अगर (is_c11_alignof)
    {
      अगर (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      अन्यथा
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      काष्ठा c_declspecs *scspecs;
      काष्ठा c_type_name *type_name;
      काष्ठा c_व्यंजक ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, true);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      अगर (type_name == शून्य)
	{
	  काष्ठा c_व्यंजक ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = शून्य;
	  वापस ret;
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
	{
	  व्यंजक = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  जाओ alignof_व्यंजक;
	}
      /* alignof ( type-name ).  */
      अगर (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      अगर (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.मूल्य = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       शून्य, शून्य),
					    false, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = शून्य;
      set_c_व्यंजक_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      वापस ret;
    }
  अन्यथा
    {
      काष्ठा c_व्यंजक ret;
      व्यंजक = c_parser_unary_expression (parser);
      end_loc = व्यंजक.src_range.m_finish;
    alignof_व्यंजक:
      mark_exp_read (व्यंजक.मूल्य);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      अगर (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.मूल्य = c_alignof_व्यंजक (start_loc, व्यंजक.मूल्य);
      ret.original_code = ERROR_MARK;
      ret.original_type = शून्य;
      set_c_व्यंजक_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      वापस ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

अटल काष्ठा c_व्यंजक
c_parser_maxof_or_minof_expression (c_parser *parser, क्रमागत rid rid)
{
  स्थिर अक्षर *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  काष्ठा c_व्यंजक परिणाम;
  location_t व्यंजक_loc;
  काष्ठा c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  अगर (!c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      जाओ हार;
    }
  parens.consume_open (parser);
  व्यंजक_loc = c_parser_peek_token (parser)->location;
  अगर (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (व्यंजक_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      जाओ हार;
    }
  type_name = c_parser_type_name (parser, true);
  अगर (type_name == शून्य)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      जाओ हार;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  अगर (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  अगर (rid == RID_MAXOF)
    परिणाम = c_व्यंजक_maxof_type (व्यंजक_loc, type_name);
  अन्यथा
    परिणाम = c_व्यंजक_minof_type (व्यंजक_loc, type_name);
  set_c_व्यंजक_source_range (&परिणाम, start, finish);
  वापस परिणाम;
हार:
  c_inhibit_evaluation_warnings--;
  परिणाम.set_error ();
  परिणाम.original_code = ERROR_MARK;
  परिणाम.original_type = शून्य;
  वापस परिणाम;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

अटल काष्ठा c_व्यंजक
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_अग्र_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      काष्ठा c_व्यंजक परिणाम;
      परिणाम.set_error ();
      परिणाम.original_code = ERROR_MARK;
      परिणाम.original_type = शून्य;
      वापस परिणाम;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  वृक्ष oper = NULL_वृक्ष;
  अगर (c_parser_अग्र_tokens_start_typename (parser, cla_prefer_id))
    {
      काष्ठा c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      अगर (tname)
	{
	  oper = groktypename (tname, शून्य, शून्य);
	  निकालो_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  अन्यथा
    {
      काष्ठा c_व्यंजक cexpr = c_parser_व्यंजक_no_commas (parser, शून्य);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      अगर (cexpr.मूल्य != error_mark_गाँठ)
	{
	  mark_exp_read (cexpr.मूल्य);
	  oper = cexpr.मूल्य;
	  वृक्ष etype = वृक्ष_TYPE (oper);
	  bool was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  अगर (was_vm)
	    oper = c_fully_fold (oper, false, शून्य);
	  निकालो_maybe_used (was_vm);
	}
    }

  काष्ठा c_व्यंजक परिणाम;
  परिणाम.original_code = ERROR_MARK;
  परिणाम.original_type = शून्य;

  अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      परिणाम.set_error ();
      वापस परिणाम;
    }

  bool save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  वृक्ष attr = c_parser_gnu_attribute (parser, NULL_वृक्ष, false, false);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  अन्यथा
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);

      परिणाम.set_error ();
      वापस परिणाम;
    }

  अगर (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      परिणाम.set_error ();
      वापस परिणाम;
    }

  परिणाम.original_code = INTEGER_CST;
  परिणाम.original_type = boolean_type_गाँठ;

  अगर (has_attribute (atloc, oper, attr, default_conversion))
    परिणाम.मूल्य = boolean_true_गाँठ;
  अन्यथा
    परिणाम.मूल्य =  boolean_false_गाँठ;

  set_c_व्यंजक_source_range (&परिणाम, start, finish);
  परिणाम.m_decimal = 0;
  वापस परिणाम;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
अटल bool
c_parser_get_builtin_args (c_parser *parser, स्थिर अक्षर *bname,
			   vec<c_व्यंजक_t, va_gc> **ret_cexpr_list,
			   bool choose_व्यंजक_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_व्यंजक_t, va_gc> *cexpr_list;
  c_व्यंजक_t व्यंजक;
  bool saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = शून्य;
  अगर (c_parser_अग्र_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      वापस false;
    }

  c_parser_consume_token (parser);

  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      वापस true;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_व्यंजक_p;
  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_धकेलो (cexpr_list, व्यंजक);
  जबतक (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  वृक्ष मूल्य = embed->मूल्य;
	  व्यंजक.original_code = INTEGER_CST;
	  व्यंजक.original_type = integer_type_गाँठ;
	  व्यंजक.मूल्य = NULL_वृक्ष;
	  set_c_व्यंजक_source_range (&व्यंजक, embed->get_range ());
	  व्यंजक.m_decimal = 0;
	  क्रम (अचिन्हित पूर्णांक i = 0; i < (अचिन्हित) RAW_तथ्य_लंबाई (मूल्य); i++)
	    {
	      व्यंजक.मूल्य = build_int_cst (integer_type_गाँठ,
					  RAW_तथ्य_UCHAR_ELT (मूल्य, i));
	      vec_safe_धकेलो (cexpr_list, व्यंजक);
	    }
	  c_parser_consume_token (parser);
	  जारी;
	}
      व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      vec_safe_धकेलो (cexpr_list, व्यंजक);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    वापस false;

  *ret_cexpr_list = cexpr_list;
  वापस true;
}

/* This represents a single generic-association.  */

काष्ठा c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  वृक्ष type;
  /* The association's expression.  */
  काष्ठा c_व्यंजक expression;
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

अटल काष्ठा c_व्यंजक
c_parser_generic_selection (c_parser *parser)
{
  काष्ठा c_व्यंजक selector, error_व्यंजक;
  वृक्ष selector_type;
  काष्ठा c_generic_association matched_assoc;
  पूर्णांक match_found = -1;
  location_t generic_loc, selector_loc;

  error_व्यंजक.original_code = ERROR_MARK;
  error_व्यंजक.original_type = शून्य;
  error_व्यंजक.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_वृक्ष;
  matched_assoc.expression = error_व्यंजक;

  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  अगर (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  अन्यथा
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस error_व्यंजक;

  selector_loc = c_parser_peek_token (parser)->location;
  अगर (c_parser_अग्र_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      काष्ठा c_type_name *type = c_parser_type_name (parser);
      अगर (type)
	selector_type = groktypename (type, शून्य, शून्य);
      c_inhibit_evaluation_warnings--;
      अगर (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	  वापस error_व्यंजक;
	}
    }
  अन्यथा
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_व्यंजक_no_commas (parser, शून्य);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      निकालो_maybe_used (!flag_isoc23);

      अगर (selector.मूल्य == error_mark_गाँठ)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	  वापस selector;
	}
      mark_exp_read (selector.मूल्य);
      selector_type = वृक्ष_TYPE (selector.मूल्य);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      अगर (वृक्ष_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      अगर (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (वृक्ष_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (वृक्ष_TYPE (selector_type)));
    }

  अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
      वापस error_व्यंजक;
    }

  auto_vec<c_generic_association> associations;
  काष्ठा maybe_used_decl *maybe_used_default = शून्य;
  जबतक (1)
    {
      काष्ठा c_generic_association assoc, *iter;
      अचिन्हित पूर्णांक ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      अगर (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_वृक्ष;
	}
      अन्यथा
	{
	  काष्ठा c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  अगर (type_name == शून्य)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	      वापस error_व्यंजक;
	    }
	  assoc.type = grokgenassoc (type_name);
	  अगर (assoc.type == error_mark_गाँठ)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	      वापस error_व्यंजक;
	    }

	  अगर (वृक्ष_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  अन्यथा अगर (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  अगर (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	  वापस error_व्यंजक;
	}

      bool match = assoc.type == NULL_वृक्ष
		   || comptypes (assoc.type, selector_type);

      अगर (!match || matched_assoc.type != NULL_वृक्ष)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_व्यंजक_no_commas (parser, शून्य);

      अगर (!match || matched_assoc.type != NULL_वृक्ष)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      अगर (!match)
	निकालो_maybe_used (!flag_isoc23);
      अन्यथा अगर (assoc.type == NULL_वृक्ष)
	maybe_used_default = save_maybe_used ();
      अन्यथा
	निकालो_maybe_used (true);

      अगर (assoc.expression.मूल्य == error_mark_गाँठ)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	  वापस error_व्यंजक;
	}

      क्रम (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  अगर (assoc.type == NULL_वृक्ष)
	    {
	      अगर (iter->type == NULL_वृक्ष)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  अन्यथा अगर (iter->type != NULL_वृक्ष)
	    {
	      अगर (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      अगर (assoc.type == NULL_वृक्ष)
	{
	  अगर (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.लंबाई ();
	    }
	}
      अन्यथा अगर (match)
	{
	  अगर (match_found < 0 || matched_assoc.type == NULL_वृक्ष)
	    {
	      matched_assoc = assoc;
	      match_found = associations.लंबाई ();
	    }
	  अन्यथा
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_धकेलो (assoc);

      अगर (c_parser_peek_token (parser)->type != CPP_COMMA)
	अवरोध;
      c_parser_consume_token (parser);
    }

  अगर (match_found >= 0 && matched_assoc.type == NULL_वृक्ष)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      निकालो_maybe_used (true);
    }
  अन्यथा अगर (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      निकालो_maybe_used (!flag_isoc23);
    }

  अचिन्हित पूर्णांक ix;
  काष्ठा c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    अगर (ix != (अचिन्हित) match_found)
      mark_exp_read (iter->expression.मूल्य);

  अगर (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
      वापस error_व्यंजक;
    }

  अगर (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      वापस error_व्यंजक;
    }

  वापस matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

अटल अचिन्हित पूर्णांक
check_tgmath_function (c_व्यंजक *व्यंजक, अचिन्हित पूर्णांक pos)
{
  वृक्ष type = वृक्ष_TYPE (व्यंजक->मूल्य);
  अगर (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (व्यंजक->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      वापस 0;
    }
  type = वृक्ष_TYPE (type);
  अगर (!prototype_p (type))
    {
      error_at (व्यंजक->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      वापस 0;
    }
  अगर (stdarg_p (type))
    {
      error_at (व्यंजक->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      वापस 0;
    }
  अचिन्हित पूर्णांक nargs = 0;
  function_args_iterator iter;
  वृक्ष t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      अगर (t == void_type_गाँठ)
	अवरोध;
      nargs++;
    }
  अगर (nargs == 0)
    {
      error_at (व्यंजक->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      वापस 0;
    }
  वापस nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
क्रमागत tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

अटल काष्ठा c_व्यंजक
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  चयन (c_parser_peek_token (parser)->keyword)
    {
    हाल RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      अवरोध;
    हाल RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      अवरोध;
    हाल RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      अवरोध;
    शेष:
      gcc_unreachable ();
    }

  काष्ठा c_व्यंजक व्यंजक;
  व्यंजक.original_code = ERROR_MARK;
  व्यंजक.original_type = शून्य;
  व्यंजक.मूल्य = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->मूल्य);
  set_c_व्यंजक_source_range (&व्यंजक, loc, loc);
  व्यंजक.m_decimal = 0;
  c_parser_consume_token (parser);
  वापस व्यंजक;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

अटल bool
has_counted_by_object (वृक्ष ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  अगर ((वृक्ष_CODE (ref) == INDIRECT_REF
       && is_access_with_आकार_p (वृक्ष_OPERAND (ref, 0)))
      || is_access_with_आकार_p (ref))
    वापस true;
  वापस false;
}

/* Get the reference to the counted-by object associated with the REF.  */

अटल वृक्ष
get_counted_by_ref (वृक्ष ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  अगर (वृक्ष_CODE (ref) == INDIRECT_REF
      && is_access_with_आकार_p (वृक्ष_OPERAND (ref, 0)))
    वापस CALL_व्यंजक_ARG (वृक्ष_OPERAND (ref, 0), 1);
  अन्यथा अगर (is_access_with_आकार_p (ref))
    वापस CALL_व्यंजक_ARG (ref, 1);

  वापस NULL_वृक्ष;
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

अटल काष्ठा c_व्यंजक
c_parser_postfix_expression (c_parser *parser)
{
  काष्ठा c_व्यंजक व्यंजक, e1;
  काष्ठा c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  व्यंजक.original_code = ERROR_MARK;
  व्यंजक.original_type = शून्य;
  व्यंजक.m_decimal = 0;
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_संख्या:
      व्यंजक.मूल्य = c_parser_peek_token (parser)->मूल्य;
      set_c_व्यंजक_source_range (&व्यंजक, tok_range);
      loc = c_parser_peek_token (parser)->location;
      व्यंजक.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      अगर (वृक्ष_CODE (व्यंजक.मूल्य) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  व्यंजक.set_error ();
	}
      अवरोध;
    हाल CPP_CHAR:
    हाल CPP_CHAR16:
    हाल CPP_CHAR32:
    हाल CPP_UTF8CHAR:
    हाल CPP_WCHAR:
      व्यंजक.मूल्य = c_parser_peek_token (parser)->मूल्य;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      व्यंजक.original_type = char_type_गाँठ;
      set_c_व्यंजक_source_range (&व्यंजक, tok_range);
      c_parser_consume_token (parser);
      अवरोध;
    हाल CPP_STRING:
    हाल CPP_STRING16:
    हाल CPP_STRING32:
    हाल CPP_WSTRING:
    हाल CPP_UTF8STRING:
      व्यंजक = c_parser_string_literal (parser, parser->translate_strings_p,
				      true);
      अवरोध;
    हाल CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      व्यंजक.मूल्य
	= objc_build_string_object (c_parser_peek_token (parser)->मूल्य);
      set_c_व्यंजक_source_range (&व्यंजक, tok_range);
      c_parser_consume_token (parser);
      अवरोध;
    हाल CPP_NAME:
      चयन (c_parser_peek_token (parser)->id_kind)
	{
	हाल C_ID_ID:
	  {
	    वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	    c_parser_consume_token (parser);
	    व्यंजक.मूल्य = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &व्यंजक.original_type);
	    set_c_व्यंजक_source_range (&व्यंजक, tok_range);
	    अवरोध;
	  }
	हाल C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    वृक्ष class_name = c_parser_peek_token (parser)->मूल्य;
	    वृक्ष component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    अगर (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		व्यंजक.set_error ();
		अवरोध;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->मूल्य;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    व्यंजक.मूल्य = objc_build_class_component_ref (class_name,
							 component);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, end_loc);
	    अवरोध;
	  }
	शेष:
	  c_parser_error (parser, "expected expression");
	  व्यंजक.set_error ();
	  अवरोध;
	}
      अवरोध;
    हाल CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      अगर (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  वृक्ष stmt;
	  location_t brace_loc;
	  bool save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  अगर (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = true;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, शून्य);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	      व्यंजक.set_error ();
	      अवरोध;
	    }
	  c_omp_array_section_p = false;
	  stmt = c_begin_stmt_व्यंजक ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  व्यंजक.मूल्य = c_finish_stmt_व्यंजक (brace_loc, stmt);
	  set_c_व्यंजक_source_range (&व्यंजक, loc, close_loc);
	  mark_exp_read (व्यंजक.मूल्य);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      अन्यथा
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  व्यंजक = c_parser_expression (parser);
	  अगर (वृक्ष_CODE (व्यंजक.मूल्य) == MODIFY_व्यंजक)
	    suppress_warning (व्यंजक.मूल्य, OPT_Wparentheses);
	  अगर (व्यंजक.original_code != C_MAYBE_CONST_व्यंजक
	      && व्यंजक.original_code != SIZEOF_व्यंजक)
	    व्यंजक.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  अगर (व्यंजक.original_code == SIZEOF_व्यंजक)
	    व्यंजक.original_code = PAREN_SIZEOF_व्यंजक;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_व्यंजक_source_range (&व्यंजक, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      अवरोध;
    हाल CPP_KEYWORD:
      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_FUNCTION_NAME:
	हाल RID_PRETTY_FUNCTION_NAME:
	हाल RID_C99_FUNCTION_NAME:
	  व्यंजक = c_parser_predefined_identifier (parser);
	  अवरोध;
	हाल RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    e1 = c_parser_व्यंजक_no_commas (parser, शून्य);
	    mark_exp_read (e1.मूल्य);
	    e1.मूल्य = c_fully_fold (e1.मूल्य, false, शून्य);
	    अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    अगर (t1 == शून्य)
	      {
		व्यंजक.set_error ();
	      }
	    अन्यथा
	      {
		वृक्ष type_व्यंजक = NULL_वृक्ष;
		वृक्ष type = groktypename (t1, &type_व्यंजक, शून्य);
		व्यंजक.मूल्य = c_build_va_arg (start_loc, e1.मूल्य, loc,
					     type, type_व्यंजक);
		set_c_व्यंजक_source_range (&व्यंजक, start_loc, end_loc);
	      }
	  }
	  अवरोध;
	हाल RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    e1 = c_parser_व्यंजक_no_commas (parser, शून्य);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, true, true);
	    अगर (!c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
		    व्यंजक.set_error ();
		    अवरोध;
		  }
		अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    वृक्ष name = c_parser_peek_token (parser)->मूल्य;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    वृक्ष decl = lookup_name (name);
		    वृक्ष last_parm
		      = वृक्ष_last (DECL_ARGUMENTS (current_function_decl));
		    अगर (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    अन्यथा अगर (DECL_REGISTER (decl))
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
		    अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    जबतक (true)
		      {
			c_token *token = c_parser_peek_token (parser);
			अगर (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  अवरोध;

			अगर (token->type == CPP_EOF)
			  अवरोध;
			अगर (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			अन्यथा अगर (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    अगर (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    वृक्ष fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<वृक्ष, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_धकेलो (e1.मूल्य);
	    params->quick_धकेलो (integer_zero_गाँठ);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_धकेलो (e1.get_location ());
	    arg_loc.quick_धकेलो (UNKNOWN_LOCATION);
	    व्यंजक.मूल्य = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, शून्य);
	    set_c_व्यंजक_source_range (&व्यंजक, loc,
				     parser->tokens_buf[0].get_finish ());
	    व्यंजक.m_decimal = 0;
	    व्यंजक.original_code = ERROR_MARK;
	    व्यंजक.original_type = शून्य;
	    release_वृक्ष_vector (params);
	    अवरोध;
	  }
	हाल RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    t1 = c_parser_type_name (parser);
	    अगर (t1 == शून्य)
	      parser->error = true;
	    अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    अगर (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    वृक्ष type = groktypename (t1, शून्य, शून्य);
	    वृक्ष offsetof_ref;
	    अगर (type == error_mark_गाँठ)
	      offsetof_ref = error_mark_गाँठ;
	    अन्यथा
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_गाँठ);
		SET_व्यंजक_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->मूल्य,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		जबतक (c_parser_अग्र_token_is (parser, CPP_DOT)
		       || c_parser_अग्र_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_अग्र_token_is (parser,
						  CPP_DEREF))
		  {
		    अगर (c_parser_अग्र_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_गाँठ);
			जाओ do_dot;
		      }
		    अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			अगर (c_parser_अग्र_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    अवरोध;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->मूल्य,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    अन्यथा
		      {
			काष्ठा c_व्यंजक ce;
			वृक्ष idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, false, false);
			idx = ce.मूल्य;
			idx = c_fully_fold (idx, false, शून्य);
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
	    व्यंजक.मूल्य = fold_offsetof (offsetof_ref);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, end_loc);
	  }
	  अवरोध;
	हाल RID_CHOOSE_व्यंजक:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    c_व्यंजक_t *e1_p, *e2_p, *e3_p;
	    वृक्ष c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, true,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }

	    अगर (vec_safe_लंबाई (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->मूल्य;
	    mark_exp_read (e2_p->मूल्य);
	    mark_exp_read (e3_p->मूल्य);
	    अगर (वृक्ष_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (वृक्ष_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    व्यंजक = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अवरोध;
	  }
	हाल RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    t1 = c_parser_type_name (parser);
	    अगर (t1 == शून्य)
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    t2 = c_parser_type_name (parser);
	    अगर (t2 == शून्य)
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    वृक्ष e1, e2;
	    e1 = groktypename (t1, शून्य, शून्य);
	    e2 = groktypename (t2, शून्य, शून्य);
	    अगर (e1 == error_mark_गाँठ || e2 == error_mark_गाँठ)
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    व्यंजक.मूल्य
	      = comptypes (e1, e2) ? integer_one_गाँठ : integer_zero_गाँठ;
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	  }
	  अवरोध;
	हाल RID_BUILTIN_TGMATH:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, false,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }

	    अगर (vec_safe_लंबाई (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    अचिन्हित पूर्णांक i;
	    c_व्यंजक_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, true, true);
	    अचिन्हित पूर्णांक nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    अगर (nargs == 0)
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (vec_safe_लंबाई (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अचिन्हित पूर्णांक अंक_functions = vec_safe_लंबाई (cexpr_list) - nargs;
	    अगर (अंक_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    क्रम (अचिन्हित पूर्णांक j = 1; j < अंक_functions; j++)
	      {
		अचिन्हित पूर्णांक this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		अगर (this_nargs == 0)
		  {
		    व्यंजक.set_error ();
		    जाओ out;
		  }
		अगर (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    व्यंजक.set_error ();
		    जाओ out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<क्रमागत tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<वृक्ष> parm_first (nargs + 1);
	    auto_vec<bool> parm_complex (nargs + 1);
	    auto_vec<bool> parm_varies (nargs + 1);
	    वृक्ष first_type = वृक्ष_TYPE (वृक्ष_TYPE ((*cexpr_list)[0].मूल्य));
	    वृक्ष first_ret = TYPE_MAIN_VARIANT (वृक्ष_TYPE (first_type));
	    parm_first.quick_धकेलो (first_ret);
	    parm_complex.quick_धकेलो (वृक्ष_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_धकेलो (false);
	    function_args_iterator iter;
	    वृक्ष t;
	    अचिन्हित पूर्णांक argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		अगर (t == void_type_गाँठ)
		  अवरोध;
		parm_first.quick_धकेलो (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_धकेलो (वृक्ष_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_धकेलो (false);
	      }
	    क्रम (अचिन्हित पूर्णांक j = 1; j < अंक_functions; j++)
	      {
		वृक्ष type = वृक्ष_TYPE (वृक्ष_TYPE ((*cexpr_list)[j].मूल्य));
		वृक्ष ret = TYPE_MAIN_VARIANT (वृक्ष_TYPE (type));
		अगर (ret != parm_first[0])
		  {
		    parm_varies[0] = true;
		    अगर (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			व्यंजक.set_error ();
			जाओ out;
		      }
		    अगर (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			व्यंजक.set_error ();
			जाओ out;
		      }
		  }
		अगर (वृक्ष_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = true;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    अगर (t == void_type_गाँठ)
		      अवरोध;
		    t = TYPE_MAIN_VARIANT (t);
		    अगर (t != parm_first[argpos])
		      {
			parm_varies[argpos] = true;
			अगर (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    व्यंजक.set_error ();
			    जाओ out;
			  }
			अगर (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    व्यंजक.set_error ();
			    जाओ out;
			  }
		      }
		    अगर (वृक्ष_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = true;
		    argpos++;
		  }
	      }
	    क्रमागत tgmath_parm_kind max_variation = tgmath_fixed;
	    क्रम (अचिन्हित पूर्णांक j = 0; j <= nargs; j++)
	      {
		क्रमागत tgmath_parm_kind this_kind;
		अगर (parm_varies[j])
		  {
		    अगर (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    अन्यथा
		      {
			this_kind = tgmath_real;
			अगर (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		अन्यथा
		  this_kind = tgmath_fixed;
		parm_kind.quick_धकेलो (this_kind);
	      }
	    अगर (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    अचिन्हित पूर्णांक tgarg = 0;
	    क्रम (अचिन्हित पूर्णांक j = 1; j <= nargs; j++)
	      अगर (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  अवरोध;
		}
	    अगर (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<वृक्ष> tg_type (अंक_functions);
	    क्रम (अचिन्हित पूर्णांक j = 0; j < अंक_functions; j++)
	      {
		वृक्ष type = वृक्ष_TYPE (वृक्ष_TYPE ((*cexpr_list)[j].मूल्य));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    अगर (argpos == tgarg)
		      {
			tg_type.quick_धकेलो (TYPE_MAIN_VARIANT (t));
			अवरोध;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    bool all_complex = true;
	    bool all_द्विआधारी = true;
	    bool all_decimal = true;
	    hash_set<वृक्ष> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		अगर (वृक्ष_CODE (t) == COMPLEX_TYPE)
		  all_decimal = false;
		अन्यथा
		  {
		    all_complex = false;
		    अगर (DECIMAL_FLOAT_TYPE_P (t))
		      all_द्विआधारी = false;
		    अन्यथा
		      all_decimal = false;
		  }
		अगर (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    व्यंजक.set_error ();
		    जाओ out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    क्रम (अचिन्हित पूर्णांक j = 0; j < अंक_functions; j++)
	      {
		वृक्ष exp_type = tg_type[j];
		वृक्ष exp_real_type = exp_type;
		अगर (वृक्ष_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = वृक्ष_TYPE (exp_type);
		वृक्ष type = वृक्ष_TYPE (वृक्ष_TYPE ((*cexpr_list)[j].मूल्य));
		वृक्ष ret = TYPE_MAIN_VARIANT (वृक्ष_TYPE (type));
		अगर ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    व्यंजक.set_error ();
		    जाओ out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    अगर (t == void_type_गाँठ)
		      अवरोध;
		    t = TYPE_MAIN_VARIANT (t);
		    अगर ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			व्यंजक.set_error ();
			जाओ out;
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
	    bool arg_complex = all_complex;
	    bool arg_द्विआधारी = all_द्विआधारी;
	    bool arg_int_decimal = all_decimal;
	    bool arg_int_floatnx = false;
	    bool arg_int_decimalx = false;
	    क्रम (अचिन्हित पूर्णांक j = 1; j <= nargs; j++)
	      {
		अगर (parm_kind[j] == tgmath_fixed)
		  जारी;
		c_व्यंजक_t *ce = &(*cexpr_list)[अंक_functions + j - 1];
		वृक्ष type = वृक्ष_TYPE (ce->मूल्य);
		अगर (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && वृक्ष_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    व्यंजक.set_error ();
		    जाओ out;
		  }
		अगर (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = true;
		    अगर (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			व्यंजक.set_error ();
			जाओ out;
		      }
		    अन्यथा अगर (all_द्विआधारी)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			व्यंजक.set_error ();
			जाओ out;
		      }
		    अन्यथा अगर (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			व्यंजक.set_error ();
			जाओ out;
		      }
		    अन्यथा अगर (arg_द्विआधारी)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			व्यंजक.set_error ();
			जाओ out;
		      }
		  }
		अन्यथा अगर (वृक्ष_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = true;
		    अगर (COMPLEX_FLOAT_TYPE_P (type))
		      arg_द्विआधारी = true;
		    अगर (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			व्यंजक.set_error ();
			जाओ out;
		      }
		    अन्यथा अगर (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			व्यंजक.set_error ();
			जाओ out;
		      }
		  }
		अन्यथा अगर (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_द्विआधारी = true;
		    अगर (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			व्यंजक.set_error ();
			जाओ out;
		      }
		    अन्यथा अगर (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			व्यंजक.set_error ();
			जाओ out;
		      }
		  }
		वृक्ष rtype = TYPE_MAIN_VARIANT (type);
		अगर (वृक्ष_CODE (rtype) == COMPLEX_TYPE)
		  rtype = वृक्ष_TYPE (rtype);
		अगर (SCALAR_FLOAT_TYPE_P (rtype))
		  क्रम (अचिन्हित पूर्णांक j = 0; j < अंक_FLOATNX_TYPES; j++)
		    अगर (rtype == FLOATNX_TYPE_गाँठ (j))
		      {
			arg_int_floatnx = true;
			अवरोध;
		      }
		अगर (rtype == dfloat64x_type_गाँठ)
		  arg_int_decimalx = true;
	      }
	    वृक्ष arg_real = NULL_वृक्ष;
	    क्रम (अचिन्हित पूर्णांक j = 1; j <= nargs; j++)
	      {
		अगर (parm_kind[j] == tgmath_fixed)
		  जारी;
		c_व्यंजक_t *ce = &(*cexpr_list)[अंक_functions + j - 1];
		वृक्ष type = TYPE_MAIN_VARIANT (वृक्ष_TYPE (ce->मूल्य));
		अगर (वृक्ष_CODE (type) == COMPLEX_TYPE)
		  type = वृक्ष_TYPE (type);
		अगर (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_गाँठ
			  : arg_int_floatnx
			  ? float32x_type_गाँठ
			  : arg_int_decimal
			  ? dfloat64_type_गाँठ
			  : double_type_गाँठ);
		अगर (arg_real == NULL_वृक्ष)
		  arg_real = type;
		अन्यथा
		  arg_real = common_type (arg_real, type);
		अगर (arg_real == error_mark_गाँठ)
		  {
		    व्यंजक.set_error ();
		    जाओ out;
		  }
	      }
	    वृक्ष arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_व्यंजक_t *fn = शून्य;
	    क्रम (अचिन्हित पूर्णांक j = 0; j < अंक_functions; j++)
	      {
		अगर (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    अवरोध;
		  }
	      }
	    अगर (fn == शून्य
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		क्रम (अचिन्हित पूर्णांक j = 0; j < अंक_functions; j++)
		  {
		    अगर (arg_complex
			!= (वृक्ष_CODE (tg_type[j]) == COMPLEX_TYPE))
		      जारी;
		    वृक्ष real_tg_type = (arg_complex
					 ? वृक्ष_TYPE (tg_type[j])
					 : tg_type[j]);
		    अगर (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      जारी;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    स्थिर real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    स्थिर real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    अगर (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			अवरोध;
		      }
		  }
	      }
	    अगर (fn == शून्य)
	      {
		error_at (loc, "no matching function for type-generic call");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    /* Construct a call to FN.  */
	    vec<वृक्ष, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<वृक्ष, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    क्रम (अचिन्हित पूर्णांक j = 0; j < nargs; j++)
	      {
		c_व्यंजक_t *ce = &(*cexpr_list)[अंक_functions + j];
		args->quick_धकेलो (ce->मूल्य);
		arg_loc.quick_धकेलो (ce->get_location ());
		origtypes->quick_धकेलो (ce->original_type);
	      }
	    व्यंजक.मूल्य = c_build_function_call_vec (loc, arg_loc, fn->मूल्य,
						    args, origtypes);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अवरोध;
	  }
	हाल RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    c_व्यंजक_t *e2_p;
	    वृक्ष chain_मूल्य;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, false,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (vec_safe_लंबाई (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    व्यंजक = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, true, true);
	    chain_मूल्य = e2_p->मूल्य;
	    mark_exp_read (chain_मूल्य);

	    अगर (वृक्ष_CODE (व्यंजक.मूल्य) != CALL_व्यंजक)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    अन्यथा अगर (वृक्ष_CODE (वृक्ष_TYPE (chain_मूल्य)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    अन्यथा
	      CALL_व्यंजक_STATIC_CHAIN (व्यंजक.मूल्य) = chain_मूल्य;
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अवरोध;
	  }
	हाल RID_BUILTIN_COMPLEX:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    c_व्यंजक_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, false,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }

	    अगर (vec_safe_लंबाई (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, true, true);
	    अगर (वृक्ष_CODE (e1_p->मूल्य) == EXCESS_PRECISION_व्यंजक)
	      e1_p->मूल्य = convert (वृक्ष_TYPE (e1_p->मूल्य),
				     वृक्ष_OPERAND (e1_p->मूल्य, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, true, true);
	    अगर (वृक्ष_CODE (e2_p->मूल्य) == EXCESS_PRECISION_व्यंजक)
	      e2_p->मूल्य = convert (वृक्ष_TYPE (e2_p->मूल्य),
				     वृक्ष_OPERAND (e2_p->मूल्य, 0));
	    अगर (!SCALAR_FLOAT_TYPE_P (वृक्ष_TYPE (e1_p->मूल्य))
		|| DECIMAL_FLOAT_TYPE_P (वृक्ष_TYPE (e1_p->मूल्य))
		|| !SCALAR_FLOAT_TYPE_P (वृक्ष_TYPE (e2_p->मूल्य))
		|| DECIMAL_FLOAT_TYPE_P (वृक्ष_TYPE (e2_p->मूल्य)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (TYPE_MAIN_VARIANT (वृक्ष_TYPE (e1_p->मूल्य))
		!= TYPE_MAIN_VARIANT (वृक्ष_TYPE (e2_p->मूल्य)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		व्यंजक.set_error ();
		अवरोध;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    व्यंजक.मूल्य = build2_loc (loc, COMPLEX_व्यंजक,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (वृक्ष_TYPE (e1_p->मूल्य))),
				     e1_p->मूल्य, e2_p->मूल्य);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अवरोध;
	  }
	हाल RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    c_व्यंजक_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, false,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (vec_safe_लंबाई (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    e_p = &(*cexpr_list)[0];
	    वृक्ष ref = e_p->मूल्य;

	    अगर (वृक्ष_CODE (वृक्ष_TYPE (ref)) != ARRAY_TYPE
		 && वृक्ष_CODE (वृक्ष_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    अगर (वृक्ष_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		व्यंजक.set_error ();
		अवरोध;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    अगर (वृक्ष_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    अगर (has_counted_by_object (ref))
	      व्यंजक.मूल्य = get_counted_by_ref (ref);
	    अन्यथा
	      व्यंजक.मूल्य = null_pointer_गाँठ;

	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अवरोध;
	  }
	हाल RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    अचिन्हित पूर्णांक i;
	    c_व्यंजक_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, false,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, true, true);

	    अगर (vec_safe_लंबाई (cexpr_list) == 2)
	      व्यंजक.मूल्य = c_build_vec_perm_व्यंजक (loc, (*cexpr_list)[0].मूल्य,
						  NULL_वृक्ष,
						  (*cexpr_list)[1].मूल्य);

	    अन्यथा अगर (vec_safe_लंबाई (cexpr_list) == 3)
	      व्यंजक.मूल्य = c_build_vec_perm_व्यंजक (loc, (*cexpr_list)[0].मूल्य,
						  (*cexpr_list)[1].मूल्य,
						  (*cexpr_list)[2].मूल्य);
	    अन्यथा
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		व्यंजक.set_error ();
	      }
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अवरोध;
	  }
	हाल RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    अचिन्हित पूर्णांक i;
	    c_व्यंजक_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, false,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, true, true);

	    अगर (vec_safe_लंबाई (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		व्यंजक.set_error ();
	      }
	    अन्यथा
	      {
		auto_vec<वृक्ष, 16> mask;
		क्रम (i = 2; i < cexpr_list->लंबाई (); ++i)
		  mask.safe_धकेलो ((*cexpr_list)[i].मूल्य);
		व्यंजक.मूल्य = c_build_shufflevector (loc, (*cexpr_list)[0].मूल्य,
						    (*cexpr_list)[1].मूल्य,
						    mask);
	      }
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अवरोध;
	  }
	हाल RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    e1 = c_parser_व्यंजक_no_commas (parser, शून्य);
	    mark_exp_read (e1.मूल्य);
	    अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    अगर (t1 == शून्य)
	      व्यंजक.set_error ();
	    अन्यथा
	      {
		वृक्ष type_व्यंजक = NULL_वृक्ष;
		व्यंजक.मूल्य = c_build_vec_convert (start_loc, e1.मूल्य, loc,
						  groktypename (t1, &type_व्यंजक,
								शून्य));
		set_c_व्यंजक_source_range (&व्यंजक, start_loc, end_loc);
	      }
	  }
	  अवरोध;
	हाल RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    e1 = c_parser_व्यंजक_no_commas (parser, शून्य);
	    mark_exp_read (e1.मूल्य);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    व्यंजक = parser_build_unary_op (loc, PAREN_व्यंजक, e1);
	    set_c_व्यंजक_source_range (&व्यंजक, start_loc, end_loc);
	  }
	  अवरोध;
	हाल RID_BUILTIN_STDC:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    c_व्यंजक_t *arg_p;
	    location_t close_paren_loc;
	    क्रमागत c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_गिनती_ONES,
	      C_BUILTIN_STDC_गिनती_ZEROS,
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
	    स्थिर अक्षर *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	    अचिन्हित अंक_args = 1;
	    चयन (name[माप ("__builtin_stdc_") - 1])
	      {
	      हाल 'b':
		चयन (name[माप ("__builtin_stdc_bit_") - 1])
		  {
		  हाल 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    अवरोध;
		  हाल 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    अवरोध;
		  शेष:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    अवरोध;
		  }
		अवरोध;
	      हाल 'c':
		अगर (name[माप ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_गिनती_ONES;
		अन्यथा
		  stdc_rid = C_BUILTIN_STDC_गिनती_ZEROS;
		अवरोध;
	      हाल 'f':
		चयन (name[माप ("__builtin_stdc_first_trailing_") - 1])
		  {
		  हाल 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    अवरोध;
		  हाल 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    अवरोध;
		  हाल 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    अवरोध;
		  शेष:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    अवरोध;
		  }
		अवरोध;
	      हाल 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		अवरोध;
	      हाल 'l':
		अगर (name[माप ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		अन्यथा
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		अवरोध;
	      हाल 'r':
		अगर (name[माप ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_बायाँ;
		अन्यथा
		  stdc_rid = C_BUILTIN_STDC_ROTATE_दायाँ;
		अंक_args = 2;
		अवरोध;
	      हाल 't':
		अगर (name[माप ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		अन्यथा
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		अवरोध;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, false,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }

	    अगर (vec_safe_लंबाई (cexpr_list) != अंक_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		व्यंजक.set_error ();
		अवरोध;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, true, true);
	    अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (arg_p->मूल्य)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (वृक्ष_CODE (वृक्ष_TYPE (arg_p->मूल्य)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (वृक्ष_CODE (वृक्ष_TYPE (arg_p->मूल्य)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (!TYPE_UNSIGNED (वृक्ष_TYPE (arg_p->मूल्य)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (TYPE_MAIN_VARIANT (वृक्ष_TYPE (arg_p->मूल्य))
		== char_type_गाँठ)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    वृक्ष arg = arg_p->मूल्य;
	    वृक्ष type = TYPE_MAIN_VARIANT (वृक्ष_TYPE (arg));
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
	    पूर्णांक prec = TYPE_PRECISION (type);
	    अगर (अंक_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, true, true);
		अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (arg_p->मूल्य)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    व्यंजक.set_error ();
		    अवरोध;
		  }
		अगर (वृक्ष_CODE (वृक्ष_TYPE (arg_p->मूल्य)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    व्यंजक.set_error ();
		    अवरोध;
		  }
		वृक्ष arg1 = save_व्यंजक (arg);
		वृक्ष arg2 = save_व्यंजक (arg_p->मूल्य);
		वृक्ष_code code;
		अगर (stdc_rid == C_BUILTIN_STDC_ROTATE_बायाँ)
		  code = LROTATE_व्यंजक;
		अन्यथा
		  code = RROTATE_व्यंजक;

		अगर (वृक्ष_CODE (arg2) == INTEGER_CST
		    && वृक्ष_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_गिनती_negative,
			      "rotate count is negative");

		वृक्ष instrument_व्यंजक = NULL_वृक्ष;
		अगर (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_व्यंजक = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		अगर (TYPE_PRECISION (वृक्ष_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_गाँठ))
		  arg2 = fold_convert (unsigned_type_गाँठ, arg2);

		अगर (TYPE_UNSIGNED (वृक्ष_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_व्यंजक, वृक्ष_TYPE (arg2),
				     arg2, build_int_cst (वृक्ष_TYPE (arg2),
							  prec));
		अन्यथा
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    वृक्ष utype = c_common_unsigned_type (वृक्ष_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_व्यंजक, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		अगर (type_has_mode_precision_p (वृक्ष_TYPE (arg1))
		    || (वृक्ष_CODE (वृक्ष_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_आकार))
		  व्यंजक.मूल्य = build2_loc (loc, code, वृक्ष_TYPE (arg1), arg1,
					   arg2);
		अन्यथा
		  {
		    arg2 = save_व्यंजक (arg2);
		    वृक्ष t1 = build2_loc (loc, (code == LROTATE_व्यंजक
						? LSHIFT_व्यंजक : RSHIFT_व्यंजक),
					  वृक्ष_TYPE (arg1), arg1, arg2);
		    वृक्ष t2 = build2_loc (loc, MINUS_व्यंजक,
					  वृक्ष_TYPE (arg2),
					  build_int_cst (वृक्ष_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_व्यंजक
					   ? RSHIFT_व्यंजक : LSHIFT_व्यंजक),
				     वृक्ष_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_गिनती_overflow);
		    वृक्ष t3 = build2_loc (loc, BIT_IOR_व्यंजक,
					  वृक्ष_TYPE (arg1), t1, t2);
		    वृक्ष t4 = build2_loc (loc, NE_व्यंजक, boolean_type_गाँठ,
					  arg2,
					  build_zero_cst (वृक्ष_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_व्यंजक, boolean_type_गाँठ,
				     arg1, t4);
		    व्यंजक.मूल्य = build3_loc (loc, COND_व्यंजक,
					     वृक्ष_TYPE (arg1), t4, t3, arg1);
		  }
		अगर (instrument_व्यंजक)
		  व्यंजक.मूल्य = build2_loc (loc, COMPOUND_व्यंजक,
					   वृक्ष_TYPE (व्यंजक.मूल्य),
					   instrument_व्यंजक, व्यंजक.मूल्य);
		set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
		अवरोध;
	      }
	    वृक्ष barg1 = arg;
	    चयन (stdc_rid)
	      {
	      हाल C_BUILTIN_STDC_BIT_CEIL:
		arg = save_व्यंजक (arg);
		barg1 = build2_loc (loc, PLUS_व्यंजक, type, arg,
				    build_int_cst (type, -1));
		अवरोध;
	      हाल C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_व्यंजक (arg);
		अवरोध;
	      हाल C_BUILTIN_STDC_गिनती_ZEROS:
	      हाल C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      हाल C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      हाल C_BUILTIN_STDC_LEADING_ONES:
	      हाल C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_व्यंजक, type, arg);
		अवरोध;
	      शेष:
		अवरोध;
	      }
	    वृक्ष barg2 = NULL_वृक्ष;
	    चयन (stdc_rid)
	      {
	      हाल C_BUILTIN_STDC_BIT_WIDTH:
	      हाल C_BUILTIN_STDC_LEADING_ONES:
	      हाल C_BUILTIN_STDC_LEADING_ZEROS:
	      हाल C_BUILTIN_STDC_TRAILING_ONES:
	      हाल C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_गाँठ, prec);
		अवरोध;
	      हाल C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      हाल C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      हाल C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      हाल C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_गाँठ;
		अवरोध;
	      शेष:
		अवरोध;
	      }
	    वृक्ष fndecl = NULL_वृक्ष;
	    चयन (stdc_rid)
	      {
	      हाल C_BUILTIN_STDC_BIT_CEIL:
	      हाल C_BUILTIN_STDC_BIT_FLOOR:
	      हाल C_BUILTIN_STDC_BIT_WIDTH:
	      हाल C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      हाल C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      हाल C_BUILTIN_STDC_LEADING_ONES:
	      हाल C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		अवरोध;
	      हाल C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      हाल C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      हाल C_BUILTIN_STDC_TRAILING_ONES:
	      हाल C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		अवरोध;
	      हाल C_BUILTIN_STDC_गिनती_ONES:
	      हाल C_BUILTIN_STDC_गिनती_ZEROS:
	      हाल C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		अवरोध;
	      शेष:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    पूर्णांक nargs = barg2 != NULL_वृक्ष ? 2 : 1;
	    vec<वृक्ष, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<वृक्ष, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_धकेलो (barg1);
	    arg_loc.quick_धकेलो (arg_p->get_location ());
	    origtypes->quick_धकेलो (arg_p->original_type);
	    अगर (nargs == 2)
	      {
		args->quick_धकेलो (barg2);
		arg_loc.quick_धकेलो (loc);
		origtypes->quick_धकेलो (integer_type_गाँठ);
	      }
	    व्यंजक.मूल्य = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अगर (व्यंजक.मूल्य == error_mark_गाँठ)
	      अवरोध;
	    चयन (stdc_rid)
	      {
	      हाल C_BUILTIN_STDC_BIT_CEIL:
	      हाल C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      हाल C_BUILTIN_STDC_BIT_WIDTH:
		व्यंजक.मूल्य = build2_loc (loc, MINUS_व्यंजक, integer_type_गाँठ,
					 build_int_cst (integer_type_गाँठ,
							prec), व्यंजक.मूल्य);
		अवरोध;
	      हाल C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      हाल C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      हाल C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      हाल C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		व्यंजक.मूल्य = build2_loc (loc, PLUS_व्यंजक, integer_type_गाँठ,
					 व्यंजक.मूल्य, integer_one_गाँठ);
		अवरोध;
	      हाल C_BUILTIN_STDC_HAS_SINGLE_BIT:
		व्यंजक.मूल्य = build2_loc (loc, EQ_व्यंजक, boolean_type_गाँठ,
					 व्यंजक.मूल्य, integer_one_गाँठ);
		अवरोध;
	      शेष:
		अवरोध;
	      }

	    अगर (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		अगर (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  व्यंजक.मूल्य = fold_convert_loc (loc, unsigned_type_गाँठ,
						 व्यंजक.मूल्य);
		अवरोध;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    अगर (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      व्यंजक.मूल्य = build_int_cst (type, 0);
	    अन्यथा
	      व्यंजक.मूल्य
		= build2_loc (loc, LSHIFT_व्यंजक, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), व्यंजक.मूल्य);
	    अगर (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      व्यंजक.मूल्य = build3_loc (loc, COND_व्यंजक, type,
				       build2_loc (loc, LE_व्यंजक,
						   boolean_type_गाँठ, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       व्यंजक.मूल्य);
	    अन्यथा
	      व्यंजक.मूल्य = build3_loc (loc, COND_व्यंजक, type,
				       build2_loc (loc, EQ_व्यंजक,
						   boolean_type_गाँठ, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       व्यंजक.मूल्य);
	    अवरोध;
	  }
	हाल RID_BUILTIN_BSWAPG:
	हाल RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_व्यंजक_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    स्थिर अक्षर *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    अगर (!c_parser_get_builtin_args (parser, name, &cexpr_list, false,
					    &close_paren_loc))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }

	    अगर (vec_safe_लंबाई (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		व्यंजक.set_error ();
		अवरोध;
	      }

	    c_व्यंजक_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, true, true);
	    वृक्ष arg = arg_p->मूल्य;
	    अगर (error_operand_p (arg))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    वृक्ष type = TYPE_MAIN_VARIANT (वृक्ष_TYPE (arg));
	    अगर (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (वृक्ष_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (वृक्ष_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    arg = c_fully_fold (arg, false, शून्य);
	    व्यंजक.मूल्य = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_paren_loc);
	    अवरोध;
	  }
	हाल RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    वृक्ष sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    व्यंजक.मूल्य = objc_build_selector_व्यंजक (loc, sel);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_loc);
	  }
	  अवरोध;
	हाल RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
		व्यंजक.set_error ();
		अवरोध;
	      }
	    वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    व्यंजक.मूल्य = objc_build_protocol_व्यंजक (id);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_loc);
	  }
	  अवरोध;
	हाल RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    अगर (!parens.require_open (parser))
	      {
		व्यंजक.set_error ();
		अवरोध;
	      }
	    t1 = c_parser_type_name (parser);
	    अगर (t1 == शून्य)
	      {
		व्यंजक.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
		अवरोध;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    वृक्ष type = groktypename (t1, शून्य, शून्य);
	    व्यंजक.मूल्य = objc_build_encode_व्यंजक (type);
	    set_c_व्यंजक_source_range (&व्यंजक, loc, close_loc);
	  }
	  अवरोध;
	हाल RID_GENERIC:
	  व्यंजक = c_parser_generic_selection (parser);
	  अवरोध;
	हाल RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  व्यंजक.set_error ();
	  अवरोध;
	/* C23 'nullptr' literal.  */
	हाल RID_NULLPTR:
	  c_parser_consume_token (parser);
	  व्यंजक.मूल्य = nullptr_गाँठ;
	  set_c_व्यंजक_source_range (&व्यंजक, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  अवरोध;
	हाल RID_TRUE:
	  c_parser_consume_token (parser);
	  व्यंजक.मूल्य = boolean_true_गाँठ;
	  set_c_व्यंजक_source_range (&व्यंजक, tok_range);
	  अवरोध;
	हाल RID_FALSE:
	  c_parser_consume_token (parser);
	  व्यंजक.मूल्य = boolean_false_गाँठ;
	  set_c_व्यंजक_source_range (&व्यंजक, tok_range);
	  अवरोध;
	शेष:
	  c_parser_error (parser, "expected expression");
	  व्यंजक.set_error ();
	  अवरोध;
	}
      अवरोध;
    हाल CPP_OPEN_SQUARE:
      अगर (c_dialect_objc ())
	{
	  वृक्ष receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  व्यंजक.मूल्य = objc_build_message_व्यंजक (receiver, args);
	  set_c_व्यंजक_source_range (&व्यंजक, loc, close_loc);
	  अवरोध;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    शेष:
      c_parser_error (parser, "expected expression");
      व्यंजक.set_error ();
      अवरोध;
    }
 out:
  वापस c_parser_postfix_expression_after_primary
    (parser, व्यंजक_LOC_OR_LOC (व्यंजक.मूल्य, loc), व्यंजक);
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

अटल काष्ठा c_व्यंजक
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      काष्ठा c_declspecs *scspecs,
					      काष्ठा c_type_name *type_name,
					      location_t type_loc)
{
  वृक्ष type;
  काष्ठा c_व्यंजक init;
  bool non_const;
  काष्ठा c_व्यंजक व्यंजक;
  location_t start_loc;
  वृक्ष type_व्यंजक = NULL_वृक्ष;
  bool type_व्यंजक_const = true;
  bool constexpr_p = scspecs ? scspecs->constexpr_p : false;
  अचिन्हित पूर्णांक underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (पंक्ति_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  अगर (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_वृक्ष);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      चयन (type_name->specs->typespec_kind)
	{
	हाल ctsk_tagfirstref:
	हाल ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  अवरोध;

	हाल ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  अवरोध;

	शेष:
	  अवरोध;
	}
    }
  start_init (NULL_वृक्ष, शून्य,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_व्यंजक, &type_व्यंजक_const);
  bool varsize_p = false;
  अगर (type != error_mark_गाँठ && C_TYPE_VARIABLE_आकार (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = true;
    }
  अन्यथा अगर (वृक्ष_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_गाँठ;
    }
  अगर (constexpr_p && type != error_mark_गाँठ)
    {
      वृक्ष type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      अगर (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      अन्यथा अगर (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, false, शून्य, varsize_p);
  अगर (constexpr_p)
    finish_underspecified_init (NULL_वृक्ष, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  अगर (type != error_mark_गाँठ
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_गाँठ;
    }

  अगर (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.मूल्य && वृक्ष_CODE (init.मूल्य) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.मूल्य)
	       : init.original_code == C_MAYBE_CONST_व्यंजक);
  non_const |= !type_व्यंजक_const;
  अचिन्हित पूर्णांक alignas_align = 0;
  अगर (type != error_mark_गाँठ
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      अगर (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  व्यंजक.मूल्य = build_compound_literal (start_loc, type, init.मूल्य, non_const,
				       alignas_align, scspecs);
  set_c_व्यंजक_source_range (&व्यंजक, init.src_range);
  व्यंजक.m_decimal = 0;
  व्यंजक.original_code = ERROR_MARK;
  व्यंजक.original_type = शून्य;
  अगर (type != error_mark_गाँठ
      && व्यंजक.मूल्य != error_mark_गाँठ
      && type_व्यंजक)
    {
      अगर (वृक्ष_CODE (व्यंजक.मूल्य) == C_MAYBE_CONST_व्यंजक)
	{
	  gcc_assert (C_MAYBE_CONST_व्यंजक_PRE (व्यंजक.मूल्य) == NULL_वृक्ष);
	  C_MAYBE_CONST_व्यंजक_PRE (व्यंजक.मूल्य) = type_व्यंजक;
	}
      अन्यथा
	{
	  gcc_assert (!non_const);
	  व्यंजक.मूल्य = build2 (C_MAYBE_CONST_व्यंजक, type,
			       type_व्यंजक, व्यंजक.मूल्य);
	}
    }
  वापस c_parser_postfix_expression_after_primary (parser, start_loc, व्यंजक);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

अटल bool
sizeof_ptr_memacc_comptypes (वृक्ष type1, वृक्ष type2)
{
  वापस comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

अटल व्योम
warn_for_abs (location_t loc, वृक्ष fndecl, वृक्ष arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  अगर (c_inhibit_evaluation_warnings)
    वापस;

  वृक्ष atype = वृक्ष_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  अगर (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && वृक्ष_CODE (atype) != COMPLEX_TYPE)
    वापस;

  क्रमागत built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  चयन (fcode)
    {
    हाल BUILT_IN_ABS:
    हाल BUILT_IN_LABS:
    हाल BUILT_IN_LLABS:
    हाल BUILT_IN_IMAXABS:
      अगर (!INTEGRAL_TYPE_P (atype))
	{
	  अगर (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  अन्यथा अगर (वृक्ष_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  अन्यथा
	    gcc_unreachable ();
	  वापस;
	}
      अगर (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_मूल्य,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      अवरोध;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      अगर (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  अगर (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  अन्यथा अगर (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  अन्यथा अगर (वृक्ष_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  अन्यथा
	    gcc_unreachable ();
	  वापस;
	}
      अवरोध;

    CASE_FLT_FN (BUILT_IN_CABS):
      अगर (वृक्ष_CODE (atype) != COMPLEX_TYPE)
	{
	  अगर (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  अन्यथा अगर (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  अन्यथा
	    gcc_unreachable ();

	  वापस;
	}
      अवरोध;

    हाल BUILT_IN_FABSD32:
    हाल BUILT_IN_FABSD64:
    हाल BUILT_IN_FABSD128:
    हाल BUILT_IN_FABSD64X:
      अगर (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  अगर (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  अन्यथा अगर (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  अन्यथा अगर (वृक्ष_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_मूल्य,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  अन्यथा
	    gcc_unreachable ();
	  वापस;
	}
      अवरोध;

    शेष:
      वापस;
    }

  अगर (!TYPE_ARG_TYPES (वृक्ष_TYPE (fndecl)))
    वापस;

  वृक्ष ftype = वृक्ष_मूल्य (TYPE_ARG_TYPES (वृक्ष_TYPE (fndecl)));
  अगर (वृक्ष_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (वृक्ष_CODE (ftype) == COMPLEX_TYPE);
      atype = वृक्ष_TYPE (atype);
      ftype = वृक्ष_TYPE (ftype);
    }

  अगर (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_मूल्य,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

अटल काष्ठा c_व्यंजक
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t व्यंजक_loc,
					   काष्ठा c_व्यंजक व्यंजक)
{
  काष्ठा c_व्यंजक orig_व्यंजक;
  वृक्ष ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  वृक्ष sizeof_arg[6];
  अचिन्हित पूर्णांक literal_zero_mask;
  अचिन्हित पूर्णांक i;
  vec<वृक्ष, va_gc> *exprlist;
  vec<वृक्ष, va_gc> *origtypes = शून्य;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  जबतक (true)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_वृक्ष;
	  अगर (!c_omp_array_section_p
	      || c_parser_अग्र_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).मूल्य;

	  अगर (c_omp_array_section_p
	      && c_parser_अग्र_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      अगर (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).मूल्य;

	      व्यंजक.मूल्य = build_omp_array_section (op_loc, व्यंजक.मूल्य, idx,
						    len);
	    }
	  अन्यथा
	    व्यंजक.मूल्य = build_array_ref (op_loc, व्यंजक.मूल्य, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = व्यंजक.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	  व्यंजक.original_code = ERROR_MARK;
	  व्यंजक.original_type = शून्य;
	  व्यंजक.m_decimal = 0;
	  अवरोध;
	हाल CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    क्रम (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_वृक्ष;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = शून्य;
	    अन्यथा अगर (वृक्ष_CODE (व्यंजक.मूल्य) == FUNCTION_DECL
		     && fndecl_built_in_p (व्यंजक.मूल्य, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_अग्र_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		काष्ठा c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		काष्ठा c_typespec ret;
		ret.व्यंजक = NULL_वृक्ष;
		ret.spec = error_mark_गाँठ;
		ret.व्यंजक_const_operands = false;
		अगर (type != शून्य)
		  ret.spec = groktypename (type, &ret.व्यंजक,
					   &ret.व्यंजक_const_operands);
		parens.skip_until_found_close (parser);
		व्यंजक.मूल्य = build_int_cst (integer_type_गाँठ,
					    type_to_class (ret.spec));
		अवरोध;
	      }
	    अन्यथा
	      exprlist = c_parser_व्यंजक_list (parser, true, false, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_व्यंजक = व्यंजक;
	  mark_exp_read (व्यंजक.मूल्य);
	  अगर (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      व्यंजक.मूल्य, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  अगर (वृक्ष_CODE (व्यंजक.मूल्य) == FUNCTION_DECL)
	    {
	      अगर (fndecl_built_in_p (व्यंजक.मूल्य, BUILT_IN_MEMSET)
		  && vec_safe_लंबाई (exprlist) == 3)
		{
		  वृक्ष arg0 = (*exprlist)[0];
		  वृक्ष arg2 = (*exprlist)[2];
		  warn_for_memset (व्यंजक_loc, arg0, arg2, literal_zero_mask);
		}
	      अगर (warn_absolute_मूल्य
		  && fndecl_built_in_p (व्यंजक.मूल्य, BUILT_IN_NORMAL)
		  && vec_safe_लंबाई (exprlist) == 1)
		warn_for_abs (व्यंजक_loc, व्यंजक.मूल्य, (*exprlist)[0]);
	      अगर (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (व्यंजक.मूल्य))
		{
		  error_at (व्यंजक_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->हार = true;
		}
	      अगर (warn_calloc_transposed_args)
		अगर (वृक्ष attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (वृक्ष_TYPE (व्यंजक.मूल्य))))
		  अगर (वृक्ष_मूल्य (attr) && वृक्ष_CHAIN (वृक्ष_मूल्य (attr)))
		    warn_for_calloc (sizeof_arg_loc, व्यंजक.मूल्य, exprlist,
				     sizeof_arg, attr);
	    }

	  start = व्यंजक.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  व्यंजक.मूल्य
	    = c_build_function_call_vec (व्यंजक_loc, arg_loc, व्यंजक.मूल्य,
					 exprlist, origtypes);
	  set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	  व्यंजक.m_decimal = 0;

	  व्यंजक.original_code = ERROR_MARK;
	  अगर (वृक्ष_CODE (व्यंजक.मूल्य) == INTEGER_CST
	      && वृक्ष_CODE (orig_व्यंजक.मूल्य) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_व्यंजक.मूल्य, BUILT_IN_CONSTANT_P))
	    व्यंजक.original_code = C_MAYBE_CONST_व्यंजक;
	  व्यंजक.original_type = शून्य;
	  अगर (exprlist)
	    {
	      release_वृक्ष_vector (exprlist);
	      release_वृक्ष_vector (origtypes);
	    }
	  arg_loc.release ();
	  अवरोध;
	हाल CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  व्यंजक = default_function_array_conversion (व्यंजक_loc, व्यंजक);
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->मूल्य;
	      comp_loc = comp_tok->location;
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected identifier");
	      व्यंजक.set_error ();
	      व्यंजक.original_code = ERROR_MARK;
              व्यंजक.original_type = शून्य;
	      वापस व्यंजक;
	    }
	  start = व्यंजक.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  व्यंजक.मूल्य = build_component_ref (op_loc, व्यंजक.मूल्य, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	  व्यंजक.original_code = ERROR_MARK;
	  अगर (वृक्ष_CODE (व्यंजक.मूल्य) != COMPONENT_REF)
	    व्यंजक.original_type = शून्य;
	  अन्यथा
	    {
	      /* Remember the original type of a bitfield.  */
	      वृक्ष field = वृक्ष_OPERAND (व्यंजक.मूल्य, 1);
	      अगर (वृक्ष_CODE (field) != FIELD_DECL)
		व्यंजक.original_type = शून्य;
	      अन्यथा
		व्यंजक.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  व्यंजक.m_decimal = 0;
	  अवरोध;
	हाल CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, true, false);
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->मूल्य;
	      comp_loc = comp_tok->location;
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected identifier");
	      व्यंजक.set_error ();
	      व्यंजक.original_code = ERROR_MARK;
	      व्यंजक.original_type = शून्य;
	      वापस व्यंजक;
	    }
	  start = व्यंजक.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  व्यंजक.मूल्य = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								व्यंजक.मूल्य,
								RO_ARROW),
					    ident, comp_loc,
					    व्यंजक.get_location ());
	  set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	  व्यंजक.original_code = ERROR_MARK;
	  अगर (वृक्ष_CODE (व्यंजक.मूल्य) != COMPONENT_REF)
	    व्यंजक.original_type = शून्य;
	  अन्यथा
	    {
	      /* Remember the original type of a bitfield.  */
	      वृक्ष field = वृक्ष_OPERAND (व्यंजक.मूल्य, 1);
	      अगर (वृक्ष_CODE (field) != FIELD_DECL)
		व्यंजक.original_type = शून्य;
	      अन्यथा
		व्यंजक.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  व्यंजक.m_decimal = 0;
	  अवरोध;
	हाल CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = व्यंजक.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (व्यंजक.मूल्य);
	  व्यंजक = default_function_array_conversion (व्यंजक_loc, व्यंजक);
	  व्यंजक.मूल्य = build_unary_op (op_loc, POSTINCREMENT_व्यंजक,
				       व्यंजक.मूल्य, false);
	  set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	  व्यंजक.original_code = ERROR_MARK;
	  व्यंजक.original_type = शून्य;
	  अवरोध;
	हाल CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = व्यंजक.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (व्यंजक.मूल्य);
	  व्यंजक = default_function_array_conversion (व्यंजक_loc, व्यंजक);
	  व्यंजक.मूल्य = build_unary_op (op_loc, POSTDECREMENT_व्यंजक,
				       व्यंजक.मूल्य, false);
	  set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	  व्यंजक.original_code = ERROR_MARK;
	  व्यंजक.original_type = शून्य;
	  अवरोध;
	शेष:
	  वापस व्यंजक;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

अटल काष्ठा c_व्यंजक
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  काष्ठा c_व्यंजक व्यंजक;
  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
    व्यंजक = convert_lvalue_to_rvalue (tloc, व्यंजक, true, false);
  जबतक (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      काष्ठा c_व्यंजक अग्र;
      वृक्ष lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t व्यंजक_loc;
      c_parser_consume_token (parser);
      व्यंजक_loc = c_parser_peek_token (parser)->location;
      lhsval = व्यंजक.मूल्य;
      जबतक (वृक्ष_CODE (lhsval) == COMPOUND_व्यंजक
	     || वृक्ष_CODE (lhsval) == NOP_व्यंजक)
	{
	  अगर (वृक्ष_CODE (lhsval) == COMPOUND_व्यंजक)
	    lhsval = वृक्ष_OPERAND (lhsval, 1);
	  अन्यथा
	    lhsval = वृक्ष_OPERAND (lhsval, 0);
	}
      अगर (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      अगर (c_parser_अग्र_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  वृक्ष val = embed->मूल्य;
	  अचिन्हित last = RAW_तथ्य_लंबाई (val) - 1;
	  अग्र.मूल्य = build_int_cst (वृक्ष_TYPE (val),
				      RAW_तथ्य_UCHAR_ELT (val, last));
	  अग्र.original_type = integer_type_गाँठ;
	  c_parser_consume_token (parser);
	}
      अन्यथा
	{
	  अग्र = c_parser_व्यंजक_no_commas (parser, शून्य);
	  अग्र = convert_lvalue_to_rvalue (व्यंजक_loc, अग्र, true, false);
	}
      व्यंजक.मूल्य = build_compound_व्यंजक (loc, व्यंजक.मूल्य, अग्र.मूल्य);
      व्यंजक.original_code = COMPOUND_व्यंजक;
      व्यंजक.original_type = अग्र.original_type;
      व्यंजक.m_decimal = 0;
    }
  वापस व्यंजक;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

अटल काष्ठा c_व्यंजक
c_parser_expression_conv (c_parser *parser)
{
  काष्ठा c_व्यंजक व्यंजक;
  location_t loc = c_parser_peek_token (parser)->location;
  व्यंजक = c_parser_expression (parser);
  व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, true, false);
  वापस व्यंजक;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

अटल अंतरभूत व्योम
c_parser_check_literal_zero (c_parser *parser, अचिन्हित *literal_zero_mask,
			     अचिन्हित पूर्णांक idx)
{
  अगर (idx >= HOST_BITS_PER_INT)
    वापस;

  c_token *tok = c_parser_peek_token (parser);
  चयन (tok->type)
    {
    हाल CPP_संख्या:
    हाल CPP_CHAR:
    हाल CPP_WCHAR:
    हाल CPP_CHAR16:
    हाल CPP_CHAR32:
    हाल CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      अगर (integer_zerop (tok->मूल्य)
	  && !वृक्ष_OVERFLOW (tok->मूल्य)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    शेष:
      अवरोध;
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

अटल vec<वृक्ष, va_gc> *
c_parser_व्यंजक_list (c_parser *parser, bool convert_p, bool fold_p,
		    vec<वृक्ष, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, वृक्ष *sizeof_arg,
		    vec<location_t> *locations,
		    अचिन्हित पूर्णांक *literal_zero_mask)
{
  vec<वृक्ष, va_gc> *ret;
  vec<वृक्ष, va_gc> *orig_types;
  काष्ठा c_व्यंजक व्यंजक;
  अचिन्हित पूर्णांक idx = 0;
  bool save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = false;

  ret = make_वृक्ष_vector ();
  अगर (p_orig_types == शून्य)
    orig_types = शून्य;
  अन्यथा
    orig_types = make_वृक्ष_vector ();

  अगर (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  अगर (convert_p)
    व्यंजक = convert_lvalue_to_rvalue (व्यंजक.get_location (), व्यंजक, true, true);
  अगर (fold_p)
    व्यंजक.मूल्य = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
  ret->quick_धकेलो (व्यंजक.मूल्य);
  अगर (orig_types)
    orig_types->quick_धकेलो (व्यंजक.original_type);
  अगर (locations)
    locations->safe_धकेलो (व्यंजक.get_location ());
  अगर (sizeof_arg != शून्य
      && (व्यंजक.original_code == SIZEOF_व्यंजक
	  || व्यंजक.original_code == PAREN_SIZEOF_व्यंजक))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  जबतक (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  वृक्ष मूल्य = embed->मूल्य;
	  व्यंजक.original_code = INTEGER_CST;
	  व्यंजक.original_type = integer_type_गाँठ;
	  व्यंजक.मूल्य = NULL_वृक्ष;
	  set_c_व्यंजक_source_range (&व्यंजक, embed->get_range ());
	  व्यंजक.m_decimal = 0;
	  क्रम (अचिन्हित पूर्णांक i = 0; i < (अचिन्हित) RAW_तथ्य_लंबाई (मूल्य); i++)
	    {
	      अगर (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_तथ्य_POINTER (मूल्य)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      व्यंजक.मूल्य = build_int_cst (integer_type_गाँठ,
					  RAW_तथ्य_UCHAR_ELT (मूल्य, i));
	      vec_safe_धकेलो (ret, व्यंजक.मूल्य);
	      अगर (orig_types)
		vec_safe_धकेलो (orig_types, व्यंजक.original_type);
	      अगर (locations)
		locations->safe_धकेलो (व्यंजक.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  जारी;
	}
      अगर (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      अगर (convert_p)
	व्यंजक = convert_lvalue_to_rvalue (व्यंजक.get_location (), व्यंजक, true,
					 true);
      अगर (fold_p)
	व्यंजक.मूल्य = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
      vec_safe_धकेलो (ret, व्यंजक.मूल्य);
      अगर (orig_types)
	vec_safe_धकेलो (orig_types, व्यंजक.original_type);
      अगर (locations)
	locations->safe_धकेलो (व्यंजक.get_location ());
      अगर (++idx < 6
	  && sizeof_arg != शून्य
	  && (व्यंजक.original_code == SIZEOF_व्यंजक
	      || व्यंजक.original_code == PAREN_SIZEOF_व्यंजक))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  अगर (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  वापस ret;
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

अटल व्योम
c_parser_objc_class_definition (c_parser *parser, वृक्ष attributes)
{
  bool iface_p;
  वृक्ष id1;
  वृक्ष superclass;
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = true;
  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = false;
  अन्यथा
    gcc_unreachable ();

  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      वापस;
    }
  id1 = c_parser_peek_token (parser)->मूल्य;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      वृक्ष id2;
      वृक्ष proto = NULL_वृक्ष;
      matching_parens parens;
      parens.consume_open (parser);
      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	{
	  अगर (iface_p && c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_वृक्ष;
	    }
	  अन्यथा
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	      वापस;
	    }
	}
      अन्यथा
	{
	  id2 = c_parser_peek_token (parser)->मूल्य;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      अगर (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  वापस;
	}
      अगर (c_parser_अग्र_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      वापस;
    }
  अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  वापस;
	}
      superclass = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
    }
  अन्यथा
    superclass = NULL_वृक्ष;
  अगर (iface_p)
    {
      वृक्ष proto = NULL_वृक्ष;
      अगर (c_parser_अग्र_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  अन्यथा
    objc_start_class_implementation (id1, superclass);
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  अगर (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  अन्यथा
    {
      objc_continue_implementation ();
      वापस;
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

अटल व्योम
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  जबतक (c_parser_अग्र_token_is_not (parser, CPP_EOF))
    {
      वृक्ष decls;
      /* Parse any stray semicolon.  */
      अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  जारी;
	}
      /* Stop if at the end of the instance variables.  */
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  अवरोध;
	}
      /* Parse any objc-visibility-spec.  */
      अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  जारी;
	}
      अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  जारी;
	}
      अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  जारी;
	}
      अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  जारी;
	}
      अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, शून्य, NULL_वृक्ष);
	  जारी;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, शून्य);
      अगर (decls == शून्य)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  अगर (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = false;
	  जारी;
	}
      अन्यथा
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  वृक्ष ivar = nreverse (decls);
	  क्रम (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_गाँठ (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

अटल व्योम
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  जबतक (true)
    {
      वृक्ष id;
      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);
	  parser->error = false;
	  वापस;
	}
      id = c_parser_peek_token (parser)->मूल्य;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

अटल व्योम
c_parser_objc_alias_declaration (c_parser *parser)
{
  वृक्ष id1, id2;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);
      वापस;
    }
  id1 = c_parser_peek_token (parser)->मूल्य;
  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);
      वापस;
    }
  id2 = c_parser_peek_token (parser)->मूल्य;
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

अटल व्योम
c_parser_objc_protocol_definition (c_parser *parser, वृक्ष attributes)
{
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      वापस;
    }
  अगर (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      जबतक (true)
	{
	  वृक्ष id;
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      अवरोध;
	    }
	  id = c_parser_peek_token (parser)->मूल्य;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    अवरोध;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  अन्यथा
    {
      वृक्ष id = c_parser_peek_token (parser)->मूल्य;
      वृक्ष proto = NULL_वृक्ष;
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = true;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = false;
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
अटल अंतरभूत bool
c_parser_objc_method_type (c_parser *parser)
{
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_PLUS:
      c_parser_consume_token (parser);
      वापस true;
    हाल CPP_MINUS:
      c_parser_consume_token (parser);
      वापस false;
    शेष:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

अटल व्योम
c_parser_objc_method_definition (c_parser *parser)
{
  bool is_class_method = c_parser_objc_method_type (parser);
  वृक्ष decl, attributes = NULL_वृक्ष, व्यंजक = NULL_वृक्ष;
  parser->objc_pq_context = true;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &व्यंजक);
  अगर (decl == error_mark_गाँठ)
    वापस;  /* Bail here. */

  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  अगर (!c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      वापस;
    }

  parser->objc_pq_context = false;
  अगर (objc_start_method_definition (is_class_method, decl, attributes, व्यंजक))
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

अटल व्योम
c_parser_objc_methodprotolist (c_parser *parser)
{
  जबतक (true)
    {
      /* The list is terminated by @end.  */
      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  अवरोध;
	हाल CPP_PLUS:
	हाल CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  अवरोध;
	हाल CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, शून्य, NULL_वृक्ष);
	  अवरोध;
	हाल CPP_EOF:
	  वापस;
	शेष:
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_END))
	    वापस;
	  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (true);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (false);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    c_parser_declaration_or_fndef (parser, false, false, true,
					   false, true, false);
	  अवरोध;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

अटल व्योम
c_parser_objc_methodproto (c_parser *parser)
{
  bool is_class_method = c_parser_objc_method_type (parser);
  वृक्ष decl, attributes = NULL_वृक्ष;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = true;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    शून्य);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = false;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  अगर (!c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      वापस;
    }

  अगर (decl != error_mark_गाँठ)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

अटल bool
c_parser_objc_maybe_method_attributes (c_parser* parser, वृक्ष* attributes)
{
  bool बुरा = false;
  अगर (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_वृक्ष;
      बुरा = true;
    }

  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  अगर (*attributes == NULL_वृक्ष || बुरा)
    वापस बुरा;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
      || c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    वापस बुरा;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  वापस true;
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

अटल वृक्ष
c_parser_objc_method_decl (c_parser *parser, bool is_class_method,
			   वृक्ष *attributes, वृक्ष *व्यंजक)
{
  वृक्ष type = NULL_वृक्ष;
  वृक्ष sel;
  वृक्ष parms = NULL_वृक्ष;
  bool ellipsis = false;
  bool attr_err = false;

  *attributes = NULL_वृक्ष;
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
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
  अगर (!sel || c_parser_अग्र_token_is (parser, CPP_COLON))
    {
      वृक्ष tsel = sel;
      वृक्ष list = NULL_वृक्ष;
      जबतक (true)
	{
	  वृक्ष atype = NULL_वृक्ष, id, keyworddecl;
	  वृक्ष param_attr = NULL_वृक्ष;
	  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    अवरोध;
	  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      वापस error_mark_गाँठ;
	    }
	  id = c_parser_peek_token (parser)->मूल्य;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  अगर (!tsel && c_parser_अग्र_token_is_not (parser, CPP_COLON))
	    अवरोध;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_गाँठ (वृक्ष_LIST);
      जबतक (c_parser_अग्र_token_is (parser, CPP_COMMA))
	{
	  काष्ठा c_parm *parm;
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = true;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      अवरोध;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_वृक्ष, false);
	  अगर (parm == शून्य)
	    अवरोध;
	  parms = chainon (parms,
			   build_वृक्ष_list (NULL_वृक्ष, grokparm (parm, व्यंजक)));
	}
      sel = list;
    }
  अन्यथा
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  अगर (sel == शून्य)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      वापस error_mark_गाँठ;
    }

  अगर (attr_err)
    वापस error_mark_गाँठ;

  वापस objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

अटल वृक्ष
c_parser_objc_type_name (c_parser *parser)
{
  वृक्ष quals = NULL_वृक्ष;
  काष्ठा c_type_name *type_name = शून्य;
  वृक्ष type = NULL_वृक्ष;
  जबतक (true)
    {
      c_token *token = c_parser_peek_token (parser);
      अगर (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_वृक्ष_list (NULL_वृक्ष, token->मूल्य), quals);
	  c_parser_consume_token (parser);
	}
      अन्यथा
	अवरोध;
    }
  अगर (c_parser_अग्र_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  अगर (type_name)
    type = groktypename (type_name, शून्य, शून्य);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  अगर (type == error_mark_गाँठ)
    type = NULL_वृक्ष;

  वापस build_वृक्ष_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

अटल वृक्ष
c_parser_objc_protocol_refs (c_parser *parser)
{
  वृक्ष list = NULL_वृक्ष;
  gcc_assert (c_parser_अग्र_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  जबतक (true)
    {
      वृक्ष id;
      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  अवरोध;
	}
      id = c_parser_peek_token (parser)->मूल्य;
      list = chainon (list, build_वृक्ष_list (NULL_वृक्ष, id));
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  वापस list;
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

अटल व्योम
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  वृक्ष stmt;

  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  जबतक (c_parser_अग्र_token_is_keyword (parser, RID_AT_CATCH))
    {
      काष्ठा c_parm *parm;
      वृक्ष parameter_declaration = error_mark_गाँठ;
      bool seen_open_paren = false;

      c_parser_consume_token (parser);
      matching_parens parens;
      अगर (!parens.require_open (parser))
	seen_open_paren = true;
      अगर (c_parser_अग्र_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_वृक्ष;
	}
      अन्यथा
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_वृक्ष, false);
	  अगर (parm == शून्य)
	    parameter_declaration = error_mark_गाँठ;
	  अन्यथा
	    parameter_declaration = grokparm (parm, शून्य);
	}
      अगर (seen_open_paren)
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
	  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      अगर (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_AT_FINALLY))
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

अटल व्योम
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  वृक्ष व्यंजक, stmt;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      काष्ठा c_व्यंजक ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, false, false);
      व्यंजक = ce.मूल्य;
      व्यंजक = c_fully_fold (व्यंजक, false, शून्य);
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    व्यंजक = error_mark_गाँठ;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, व्यंजक, stmt);
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

अटल वृक्ष
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  वृक्ष मूल्य = token->मूल्य;
  अगर (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      वापस मूल्य;
    }
  अगर (token->type != CPP_KEYWORD)
    वापस NULL_वृक्ष;
  चयन (token->keyword)
    {
    हाल RID_ENUM:
    हाल RID_STRUCT:
    हाल RID_UNION:
    हाल RID_IF:
    हाल RID_ELSE:
    हाल RID_WHILE:
    हाल RID_DO:
    हाल RID_FOR:
    हाल RID_SWITCH:
    हाल RID_CASE:
    हाल RID_DEFAULT:
    हाल RID_BREAK:
    हाल RID_CONTINUE:
    हाल RID_RETURN:
    हाल RID_GOTO:
    हाल RID_ASM:
    हाल RID_SIZEOF:
    हाल RID_TYPEOF:
    हाल RID_TYPEOF_UNQUAL:
    हाल RID_ALIGNOF:
    हाल RID_UNSIGNED:
    हाल RID_LONG:
    हाल RID_CONST:
    हाल RID_SHORT:
    हाल RID_VOLATILE:
    हाल RID_SIGNED:
    हाल RID_RESTRICT:
    हाल RID_COMPLEX:
    हाल RID_IN:
    हाल RID_OUT:
    हाल RID_INOUT:
    हाल RID_BYCOPY:
    हाल RID_BYREF:
    हाल RID_ONEWAY:
    हाल RID_INT:
    हाल RID_CHAR:
    हाल RID_FLOAT:
    हाल RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    हाल RID_VOID:
    हाल RID_BOOL:
    हाल RID_ATOMIC:
    हाल RID_AUTO_TYPE:
    हाल RID_INT_N_0:
    हाल RID_INT_N_1:
    हाल RID_INT_N_2:
    हाल RID_INT_N_3:
      c_parser_consume_token (parser);
      वापस मूल्य;
    शेष:
      वापस NULL_वृक्ष;
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

अटल वृक्ष
c_parser_objc_selector_arg (c_parser *parser)
{
  वृक्ष sel = c_parser_objc_selector (parser);
  वृक्ष list = NULL_वृक्ष;
  अगर (sel
      && c_parser_अग्र_token_is_not (parser, CPP_COLON)
      && c_parser_अग्र_token_is_not (parser, CPP_SCOPE))
    वापस sel;
  जबतक (true)
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_वृक्ष_list (sel, NULL_वृक्ष));
	  list = chainon (list, build_वृक्ष_list (NULL_वृक्ष, NULL_वृक्ष));
	}
      अन्यथा
	{
	  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    वापस list;
	  list = chainon (list, build_वृक्ष_list (sel, NULL_वृक्ष));
	}
      sel = c_parser_objc_selector (parser);
      अगर (!sel
	  && c_parser_अग्र_token_is_not (parser, CPP_COLON)
	  && c_parser_अग्र_token_is_not (parser, CPP_SCOPE))
	अवरोध;
    }
  वापस list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

अटल वृक्ष
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  अगर (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      वृक्ष id = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
      वापस objc_get_class_reference (id);
    }
  काष्ठा c_व्यंजक ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, false, false);
  वापस c_fully_fold (ce.मूल्य, false, शून्य);
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

अटल वृक्ष
c_parser_objc_message_args (c_parser *parser)
{
  वृक्ष sel = c_parser_objc_selector (parser);
  वृक्ष list = NULL_वृक्ष;
  अगर (sel && c_parser_अग्र_token_is_not (parser, CPP_COLON))
    वापस sel;
  जबतक (true)
    {
      वृक्ष keywordexpr;
      अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	वापस error_mark_गाँठ;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_वृक्ष_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      अगर (!sel && c_parser_अग्र_token_is_not (parser, CPP_COLON))
	अवरोध;
    }
  वापस list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

अटल वृक्ष
c_parser_objc_keywordexpr (c_parser *parser)
{
  वृक्ष ret;
  vec<वृक्ष, va_gc> *व्यंजक_list = c_parser_व्यंजक_list (parser, true, true,
						शून्य, शून्य, शून्य, शून्य);
  अगर (vec_safe_लंबाई (व्यंजक_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*व्यंजक_list)[0];
    }
  अन्यथा
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_वृक्ष_list_vec (व्यंजक_list);
    }
  release_वृक्ष_vector (व्यंजक_list);
  वापस ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
अटल bool
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   काष्ठा c_declspecs *specs)
{
  अगर (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      वापस true;
    }
  वापस false;
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
अटल व्योम
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  bool syntax_error = false;
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = true;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      अन्यथा
	जबतक (true)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    अगर (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		अगर (token->type == CPP_CLOSE_PAREN)
		  अवरोध;
		c_parser_consume_token (parser);
		जारी;
	      }

	    वृक्ष attr_name = NULL_वृक्ष;
	    क्रमागत rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    bool add_at = false;
	    अगर (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		अगर (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->मूल्य;
		    add_at = true;
		  }
		अन्यथा
		  attr_name = ridpointers[(पूर्णांक)keyword];
	      }
	    अन्यथा अगर (token->type == CPP_NAME)
	      attr_name = token->मूल्य;
	    c_parser_consume_token (parser);

	    क्रमागत objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = नया property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_धकेलो (prop);

	    वृक्ष meth_name;
	    चयन (prop->prop_kind)
	      {
	      शेष: अवरोध;
	      हाल OBJC_PROPERTY_ATTR_UNKNOWN:
		अगर (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		अन्यथा
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = true;
		अवरोध;

	      हाल OBJC_PROPERTY_ATTR_GETTER:
	      हाल OBJC_PROPERTY_ATTR_SETTER:
		अगर (c_parser_अग्र_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = true;
		    अवरोध;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = true;
		    अवरोध;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->मूल्य;
		c_parser_consume_token (parser);
		अगर (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    अगर (c_parser_अग्र_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = true;
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
		अवरोध;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    अवरोध;
	}
      parser->objc_property_attr_context = false;

      अगर (syntax_error && c_parser_अग्र_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      अन्यथा
	syntax_error = false, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  वृक्ष properties = c_parser_struct_declaration (parser, शून्य);

  अगर (properties == error_mark_गाँठ)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);
  अन्यथा
    {
      अगर (properties == NULL_वृक्ष)
	c_parser_error (parser, "expected identifier");
      अन्यथा
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  क्रम (; properties; properties = वृक्ष_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_गाँठ (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  जबतक (!prop_attr_list.is_empty())
    मिटाओ prop_attr_list.निकालो ();
  prop_attr_list.release ();
  parser->error = false;
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
अटल व्योम
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  वृक्ष list = NULL_वृक्ष;
  location_t loc;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  जबतक (true)
    {
      वृक्ष property, ivar;
      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = false;
	  वापस;
	}
      property = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);
	      parser->error = false;
	      वापस;
	    }
	  ivar = c_parser_peek_token (parser)->मूल्य;
	  c_parser_consume_token (parser);
	}
      अन्यथा
	ivar = NULL_वृक्ष;
      list = chainon (list, build_वृक्ष_list (ivar, property));
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
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
अटल व्योम
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  वृक्ष list = NULL_वृक्ष;
  location_t loc;
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  जबतक (true)
    {
      वृक्ष property;
      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);
	  parser->error = false;
	  वापस;
	}
      property = c_parser_peek_token (parser)->मूल्य;
      list = chainon (list, build_वृक्ष_list (NULL_वृक्ष, property));
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

अटल bool
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  वापस true;
}

/* Parse a pragma GCC novector.  */

अटल bool
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  वापस true;
}

/* Parse a pragma GCC unroll.  */

अटल अचिन्हित लघु
c_parser_pragma_unroll (c_parser *parser)
{
  अचिन्हित लघु unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  वृक्ष व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
  mark_exp_read (व्यंजक);
  व्यंजक = c_fully_fold (व्यंजक, false, शून्य);
  HOST_WIDE_INT lunroll = 0;
  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (व्यंजक))
      || वृक्ष_CODE (व्यंजक) != INTEGER_CST
      || (lunroll = वृक्ष_to_shwi (व्यंजक)) < 0
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
      अगर (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  वापस unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

अटल bool
c_parser_pragma (c_parser *parser, क्रमागत pragma_context context, bool *if_p,
		 वृक्ष before_labels)
{
  अचिन्हित पूर्णांक id;
  स्थिर अक्षर *construct = शून्य;

  निवेश_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  अगर (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	निवेश_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->हार = true;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
      वापस false;
    }

  चयन (id)
    {
    हाल PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      वापस false;

    हाल PRAGMA_OACC_ENTER_तथ्य:
      अगर (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  अगर (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
	      वापस true;
	    }
	  जाओ bad_stmt;
	}
      c_parser_oacc_enter_exit_तथ्य (parser, true);
      वापस false;

    हाल PRAGMA_OACC_EXIT_तथ्य:
      अगर (context != pragma_compound)
	{
	  construct = "acc exit data";
	  जाओ in_compound;
	}
      c_parser_oacc_enter_exit_तथ्य (parser, false);
      वापस false;

    हाल PRAGMA_OACC_ROUTINE:
      अगर (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
	  वापस false;
	}
      c_parser_oacc_routine (parser, context);
      वापस false;

    हाल PRAGMA_OACC_UPDATE:
      अगर (context != pragma_compound)
	{
	  construct = "acc update";
	  जाओ in_compound;
	}
      c_parser_oacc_update (parser);
      वापस false;

    हाल PRAGMA_OMP_BARRIER:
      अगर (context != pragma_compound)
	{
	  construct = "omp barrier";
	  जाओ in_compound;
	}
      c_parser_omp_barrier (parser);
      वापस false;

    हाल PRAGMA_OMP_DEPOBJ:
      अगर (context != pragma_compound)
	{
	  construct = "omp depobj";
	  जाओ in_compound;
	}
      c_parser_omp_depobj (parser);
      वापस false;

    हाल PRAGMA_OMP_FLUSH:
      अगर (context != pragma_compound)
	{
	  construct = "omp flush";
	  जाओ in_compound;
	}
      c_parser_omp_flush (parser);
      वापस false;

    हाल PRAGMA_OMP_INTEROP:
      अगर (context != pragma_compound)
	{
	  construct = "omp interop";
	  जाओ in_compound;
	}
      c_parser_omp_interop (parser);
      वापस false;

    हाल PRAGMA_OMP_TASKWAIT:
      अगर (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  जाओ in_compound;
	}
      c_parser_omp_taskwait (parser);
      वापस false;

    हाल PRAGMA_OMP_TASKYIELD:
      अगर (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  जाओ in_compound;
	}
      c_parser_omp_taskyield (parser);
      वापस false;

    हाल PRAGMA_OMP_CANCEL:
      अगर (context != pragma_compound)
	{
	  construct = "omp cancel";
	  जाओ in_compound;
	}
      c_parser_omp_cancel (parser);
      वापस false;

    हाल PRAGMA_OMP_CANCELLATION_POINT:
      वापस c_parser_omp_cancellation_point (parser, context);

    हाल PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      वापस false;

    हाल PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      वापस false;

    हाल PRAGMA_OMP_TARGET:
      वापस c_parser_omp_target (parser, context, if_p);

    हाल PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      वापस false;

    हाल PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      वापस false;

    हाल PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
      वापस false;

    हाल PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
      वापस false;

    हाल PRAGMA_OMP_DECLARE:
      वापस c_parser_omp_declare (parser, context);

    हाल PRAGMA_OMP_REQUIRES:
      अगर (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
	  वापस false;
	}
      c_parser_omp_requires (parser);
      वापस false;

    हाल PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      वापस false;

    हाल PRAGMA_OMP_ASSUMES:
      अगर (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
	  वापस false;
	}
      c_parser_omp_assumes (parser);
      वापस false;

    हाल PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      वापस false;

    हाल PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      वापस true;

    हाल PRAGMA_OMP_ERROR:
      वापस c_parser_omp_error (parser, context);

    हाल PRAGMA_OMP_ORDERED:
      वापस c_parser_omp_ordered (parser, context, if_p);

    हाल PRAGMA_NOVECTOR:
    हाल PRAGMA_UNROLL:
    हाल PRAGMA_IVDEP:
      {
	bool novector = false;
	अचिन्हित लघु unroll = 0;
	bool ivdep = false;

	चयन (id)
	  {
	  हाल PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    अवरोध;
	  हाल PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    अवरोध;
	  हाल PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    अवरोध;
	  शेष:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	bool has_more = tok->type == CPP_PRAGMA;
	जबतक (has_more)
	  {
	    चयन (tok->pragma_kind)
	      {
	      हाल PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		अवरोध;
	      हाल PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		अवरोध;
	      हाल PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		अवरोध;
	      शेष:
		has_more = false;
		अवरोध;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	अगर (!c_parser_अग्र_token_is_keyword (parser, RID_FOR)
	    && !c_parser_अग्र_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_अग्र_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    वापस false;
	  }
	अगर (c_parser_अग्र_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	अन्यथा
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      वापस true;

    हाल PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
      वापस false;

    हाल PRAGMA_OACC_WAIT:
      अगर (context != pragma_compound)
	{
	  construct = "acc wait";
	  जाओ in_compound;
	}
	/* FALL THROUGH.  */

    शेष:
      अगर (id < PRAGMA_FIRST_EXTERNAL)
	{
	  अगर (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, शून्य);
	      वापस false;
	    }
	  c_parser_omp_construct (parser, if_p);
	  वापस true;
	}
      अवरोध;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = true;
  c_parser_skip_to_pragma_eol (parser);

  वापस false;
}

/* The interface the pragma parsers have to the lexer.  */

क्रमागत cpp_ttype
pragma_lex (वृक्ष *मूल्य, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  क्रमागत cpp_ttype ret = tok->type;

  *मूल्य = tok->मूल्य;
  अगर (loc)
    *loc = tok->location;

  अगर (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  अन्यथा अगर (ret == CPP_STRING)
    *मूल्य = c_parser_string_literal (the_parser, false, false).मूल्य;
  अन्यथा
    {
      अगर (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  वापस ret;
}

व्योम
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  करो
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } जबतक (type != CPP_PRAGMA_EOL);
}

अटल व्योम
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  वृक्ष name = शून्य;

  parser->lex_joined_string = true;
  c_parser_consume_pragma (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
    }
  अन्यथा
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = false;

  अगर (name)
    c_common_pch_pragma (parse_in, वृक्ष_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

अटल pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause परिणाम = PRAGMA_OMP_CLAUSE_NONE;

  अगर (c_parser_अग्र_token_is_keyword (parser, RID_AUTO))
    परिणाम = PRAGMA_OACC_CLAUSE_AUTO;
  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_IF))
    परिणाम = PRAGMA_OMP_CLAUSE_IF;
  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_DEFAULT))
    परिणाम = PRAGMA_OMP_CLAUSE_DEFAULT;
  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_FOR))
    परिणाम = PRAGMA_OMP_CLAUSE_FOR;
  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      चयन (p[0])
	{
	हाल 'a':
	  अगर (!म_भेद ("affinity", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_AFFINITY;
	  अन्यथा अगर (!म_भेद ("aligned", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_ALIGNED;
	  अन्यथा अगर (!म_भेद ("allocate", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  अन्यथा अगर (!म_भेद ("async", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_ASYNC;
	  अन्यथा अगर (!म_भेद ("attach", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_ATTACH;
	  अवरोध;
	हाल 'b':
	  अगर (!म_भेद ("bind", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_BIND;
	  अवरोध;
	हाल 'c':
	  अगर (!म_भेद ("collapse", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  अन्यथा अगर (!म_भेद ("copy", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_COPY;
	  अन्यथा अगर (!म_भेद ("copyin", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_COPYIN;
	  अन्यथा अगर (!म_भेद ("copyout", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_COPYOUT;
          अन्यथा अगर (!म_भेद ("copyprivate", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  अन्यथा अगर (!म_भेद ("create", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_CREATE;
	  अवरोध;
	हाल 'd':
	  अगर (!म_भेद ("defaultmap", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  अन्यथा अगर (!म_भेद ("delete", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_DELETE;
	  अन्यथा अगर (!म_भेद ("depend", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_DEPEND;
	  अन्यथा अगर (!म_भेद ("destroy", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_DESTROY;
	  अन्यथा अगर (!म_भेद ("detach", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_DETACH;
	  अन्यथा अगर (!म_भेद ("device", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_DEVICE;
	  अन्यथा अगर (!म_भेद ("deviceptr", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  अन्यथा अगर (!म_भेद ("device_resident", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  अन्यथा अगर (!म_भेद ("device_type", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  अन्यथा अगर (!म_भेद ("dist_schedule", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  अन्यथा अगर (!म_भेद ("doacross", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_DOACROSS;
	  अन्यथा अगर (!म_भेद ("dyn_groupprivate", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  अवरोध;
	हाल 'e':
	  अगर (!म_भेद ("enter", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_ENTER;
	  अवरोध;
	हाल 'f':
	  अगर (!म_भेद ("filter", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_FILTER;
	  अन्यथा अगर (!म_भेद ("final", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_FINAL;
	  अन्यथा अगर (!म_भेद ("finalize", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_FINALIZE;
	  अन्यथा अगर (!म_भेद ("firstprivate", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  अन्यथा अगर (!म_भेद ("from", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_FROM;
	  अन्यथा अगर (!म_भेद ("full", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_FULL;
	  अवरोध;
	हाल 'g':
	  अगर (!म_भेद ("gang", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_GANG;
	  अन्यथा अगर (!म_भेद ("grainsize", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  अवरोध;
	हाल 'h':
	  अगर (!म_भेद ("has_device_addr", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  अन्यथा अगर (!म_भेद ("hint", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_HINT;
	  अन्यथा अगर (!म_भेद ("host", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_HOST;
	  अवरोध;
	हाल 'i':
	  अगर (!म_भेद ("if_present", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  अन्यथा अगर (!म_भेद ("in_reduction", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  अन्यथा अगर (!म_भेद ("inbranch", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_INBRANCH;
	  अन्यथा अगर (!म_भेद ("independent", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  अन्यथा अगर (!म_भेद ("indirect", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_INDIRECT;
	  अन्यथा अगर (!म_भेद ("init", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_INIT;
	  अन्यथा अगर (!म_भेद ("is_device_ptr", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  अन्यथा अगर (!म_भेद ("interop", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_INTEROP;
	  अवरोध;
	हाल 'l':
	  अगर (!म_भेद ("lastprivate", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  अन्यथा अगर (!म_भेद ("linear", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_LINEAR;
	  अन्यथा अगर (!म_भेद ("link", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_LINK;
	  अन्यथा अगर (!म_भेद ("local", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_LOCAL;
	  अवरोध;
	हाल 'm':
	  अगर (!म_भेद ("map", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_MAP;
	  अन्यथा अगर (!म_भेद ("mergeable", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  अवरोध;
	हाल 'n':
	  अगर (!म_भेद ("no_create", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  अन्यथा अगर (!म_भेद ("nocontext", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  अन्यथा अगर (!म_भेद ("nogroup", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_NOGROUP;
	  अन्यथा अगर (!म_भेद ("nohost", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_NOHOST;
	  अन्यथा अगर (!म_भेद ("nontemporal", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  अन्यथा अगर (!म_भेद ("notinbranch", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  अन्यथा अगर (!म_भेद ("novariants", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  अन्यथा अगर (!म_भेद ("nowait", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_NOWAIT;
	  अन्यथा अगर (!म_भेद ("num_gangs", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_अंक_GANGS;
	  अन्यथा अगर (!म_भेद ("num_tasks", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_अंक_TASKS;
	  अन्यथा अगर (!म_भेद ("num_teams", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_अंक_TEAMS;
	  अन्यथा अगर (!म_भेद ("num_threads", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_अंक_THREADS;
	  अन्यथा अगर (!म_भेद ("num_workers", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_अंक_WORKERS;
	  अवरोध;
	हाल 'o':
	  अगर (!म_भेद ("ordered", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_ORDERED;
	  अन्यथा अगर (!म_भेद ("order", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_ORDER;
	  अवरोध;
	हाल 'p':
	  अगर (!म_भेद ("parallel", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_PARALLEL;
	  अन्यथा अगर (!म_भेद ("partial", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_PARTIAL;
	  अन्यथा अगर (!म_भेद ("present", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  अन्यथा अगर (!म_भेद ("present_or_copy", p)
		   || !म_भेद ("pcopy", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_COPY;
	  अन्यथा अगर (!म_भेद ("present_or_copyin", p)
		   || !म_भेद ("pcopyin", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_COPYIN;
	  अन्यथा अगर (!म_भेद ("present_or_copyout", p)
		   || !म_भेद ("pcopyout", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_COPYOUT;
	  अन्यथा अगर (!म_भेद ("present_or_create", p)
		   || !म_भेद ("pcreate", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_CREATE;
	  अन्यथा अगर (!म_भेद ("priority", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_PRIORITY;
	  अन्यथा अगर (!म_भेद ("private", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_PRIVATE;
	  अन्यथा अगर (!म_भेद ("proc_bind", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  अवरोध;
	हाल 'r':
	  अगर (!म_भेद ("reduction", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_REDUCTION;
	  अवरोध;
	हाल 's':
	  अगर (!म_भेद ("safelen", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_SAFELEN;
	  अन्यथा अगर (!म_भेद ("schedule", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  अन्यथा अगर (!म_भेद ("sections", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_SECTIONS;
	  अन्यथा अगर (!म_भेद ("self", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_SELF;
	  अन्यथा अगर (!म_भेद ("seq", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_SEQ;
	  अन्यथा अगर (!म_भेद ("shared", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_SHARED;
	  अन्यथा अगर (!म_भेद ("simd", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_SIMD;
	  अन्यथा अगर (!म_भेद ("simdlen", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  अवरोध;
	हाल 't':
	  अगर (!म_भेद ("task_reduction", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  अन्यथा अगर (!म_भेद ("taskgroup", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  अन्यथा अगर (!म_भेद ("thread_limit", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  अन्यथा अगर (!म_भेद ("threads", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_THREADS;
	  अन्यथा अगर (!म_भेद ("tile", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_TILE;
	  अन्यथा अगर (!म_भेद ("to", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_TO;
	  अवरोध;
	हाल 'u':
	  अगर (!म_भेद ("uniform", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_UNIFORM;
	  अन्यथा अगर (!म_भेद ("untied", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_UNTIED;
	  अन्यथा अगर (!म_भेद ("use", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_USE;
	  अन्यथा अगर (!म_भेद ("use_device", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  अन्यथा अगर (!म_भेद ("use_device_addr", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  अन्यथा अगर (!म_भेद ("use_device_ptr", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  अन्यथा अगर (!म_भेद ("uses_allocators", p))
	    परिणाम = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  अवरोध;
	हाल 'v':
	  अगर (!म_भेद ("vector", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_VECTOR;
	  अन्यथा अगर (!म_भेद ("vector_length", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_VECTOR_लंबाई;
	  अवरोध;
	हाल 'w':
	  अगर (!म_भेद ("wait", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_WAIT;
	  अन्यथा अगर (!म_भेद ("worker", p))
	    परिणाम = PRAGMA_OACC_CLAUSE_WORKER;
	  अवरोध;
	}
    }

  अगर (परिणाम != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  वापस परिणाम;
}

/* Validate that a clause of the given type does not already exist.  */

अटल व्योम
check_no_duplicate_clause (वृक्ष clauses, क्रमागत omp_clause_code code,
			   स्थिर अक्षर *name)
{
  अगर (वृक्ष c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

अटल वृक्ष
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, वृक्ष list)
{
  vec<वृक्ष, va_gc> *args;
  वृक्ष t, args_वृक्ष;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  args = c_parser_व्यंजक_list (parser, false, true, शून्य, शून्य, शून्य, शून्य);
  args_वृक्ष = build_वृक्ष_list_vec (args);

  क्रम (t = args_वृक्ष; t; t = वृक्ष_CHAIN (t))
    {
      वृक्ष targ = वृक्ष_मूल्य (t);

      अगर (targ != error_mark_गाँठ)
	{
	  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_गाँठ;
	    }
	  अन्यथा
	    {
	      वृक्ष c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_वृक्ष_vector (args);
  parens.require_close (parser);
  वापस list;
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

काष्ठा omp_dim
{
  वृक्ष निचला_bound, लंबाई;
  location_t loc;
  bool no_colon;
  omp_dim (वृक्ष lb, वृक्ष len, location_t lo, bool nc)
  : निचला_bound (lb), लंबाई (len), loc (lo), no_colon (nc) {}
};

अटल वृक्ष
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    क्रमागत omp_clause_code kind, वृक्ष list,
			    bool map_lvalue = false)
{
  auto_vec<omp_dim> dims;
  bool array_section_p;
  auto_vec<c_token> tokens;
  अचिन्हित पूर्णांक tokens_avail = 0;
  c_token *saved_tokens = शून्य;

  जबतक (1)
    {
      वृक्ष t = NULL_वृक्ष;
      location_t tloc = c_parser_peek_token (parser)->location;

      अगर (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      काष्ठा c_व्यंजक व्यंजक;
	      अगर (kind == OMP_CLAUSE_DEPEND
		  && c_parser_अग्र_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  व्यंजक.मूल्य = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      अन्यथा
		व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	      अगर (व्यंजक.मूल्य != error_mark_गाँठ)
		{
		  वृक्ष u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = व्यंजक.मूल्य;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      अगर (c_parser_अग्र_token_is_not (parser, CPP_COMMA))
		अवरोध;

	      c_parser_consume_token (parser);
	      जारी;
	    }

	  tokens.truncate (0);
	  अचिन्हित पूर्णांक nesting_depth = 0;
	  जबतक (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      चयन (token->type)
		{
		हाल CPP_EOF:
		हाल CPP_PRAGMA_EOL:
		  अवरोध;
		हाल CPP_OPEN_BRACE:
		हाल CPP_OPEN_PAREN:
		हाल CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  जाओ add;
		हाल CPP_CLOSE_BRACE:
		हाल CPP_CLOSE_PAREN:
		हाल CPP_CLOSE_SQUARE:
		  अगर (nesting_depth-- == 0)
		    अवरोध;
		  जाओ add;
		हाल CPP_COMMA:
		  अगर (nesting_depth == 0)
		    अवरोध;
		  जाओ add;
		शेष:
		add:
		  tokens.safe_धकेलो (*token);
		  c_parser_consume_token (parser);
		  जारी;
		}
	      अवरोध;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  स_रखो (&eof_token, 0, माप (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_धकेलो (eof_token);
	  tokens.safe_धकेलो (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.लंबाई ();
	}
      अन्यथा अगर (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  bool save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = true;
	  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  अगर (व्यंजक.मूल्य != error_mark_गाँठ)
	    mark_exp_read (व्यंजक.मूल्य);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  वृक्ष decl = व्यंजक.मूल्य;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  अगर (वृक्ष_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      जबतक (वृक्ष_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  वृक्ष निचला_bound = वृक्ष_OPERAND (decl, 1);
		  वृक्ष लंबाई = वृक्ष_OPERAND (decl, 2);
		  dims.safe_धकेलो (omp_dim (निचला_bound, लंबाई, loc, false));
		  decl = वृक्ष_OPERAND (decl, 0);
		}

	      जबतक (वृक्ष_CODE (decl) == ARRAY_REF
		     || वृक्ष_CODE (decl) == INDIRECT_REF
		     || वृक्ष_CODE (decl) == COMPOUND_व्यंजक)
		{
		  अगर (वृक्ष_CODE (decl) == COMPOUND_व्यंजक)
		    {
		      decl = वृक्ष_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  अन्यथा अगर (वृक्ष_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_धकेलो (omp_dim (integer_zero_गाँठ,
					       integer_one_गाँठ, loc, true));
		      decl = वृक्ष_OPERAND (decl, 0);
		    }
		  अन्यथा  /* ARRAY_REF. */
		    {
		      वृक्ष सूचकांक = वृक्ष_OPERAND (decl, 1);
		      dims.safe_धकेलो (omp_dim (सूचकांक, integer_one_गाँठ, loc,
					       true));
		      decl = वृक्ष_OPERAND (decl, 0);
		    }
		}

	      क्रम (पूर्णांक i = dims.लंबाई () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].निचला_bound,
						dims[i].लंबाई);
	    }
	  अन्यथा अगर (वृक्ष_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = वृक्ष_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_गाँठ,
					      integer_one_गाँठ);
	    }
	  अन्यथा अगर (वृक्ष_CODE (decl) == ARRAY_REF)
	    {
	      वृक्ष idx = वृक्ष_OPERAND (decl, 1);

	      decl = वृक्ष_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_गाँठ);
	    }
	  अन्यथा अगर (वृक्ष_CODE (decl) == NON_LVALUE_व्यंजक
		   || CONVERT_व्यंजक_P (decl))
	    decl = वृक्ष_OPERAND (decl, 0);

	  वृक्ष u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  जाओ अग्र_item;
	}

      अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->मूल्य);

	  अगर (t == NULL_वृक्ष)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->मूल्य);
	      t = error_mark_गाँठ;
	    }

	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).मूल्य;
      अन्यथा
	{
	  c_parser_error (parser, "expected identifier");
	  अवरोध;
	}

      अगर (t == error_mark_गाँठ)
	;
      अन्यथा अगर (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  चयन (kind)
	    {
	    हाल OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      अगर (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_गाँठ;
		  अवरोध;
		}
	      /* FALLTHROUGH  */
	    हाल OMP_CLAUSE_MAP:
	    हाल OMP_CLAUSE_FROM:
	    हाल OMP_CLAUSE_TO:
	    start_component_ref:
	      जबतक (c_parser_अग्र_token_is (parser, CPP_DOT)
		     || c_parser_अग्र_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  अगर (c_parser_अग्र_token_is (parser, CPP_DEREF))
		    {
		      c_व्यंजक t_व्यंजक;
		      t_व्यंजक.मूल्य = t;
		      t_व्यंजक.original_code = ERROR_MARK;
		      t_व्यंजक.original_type = शून्य;
		      set_c_व्यंजक_source_range (&t_व्यंजक, op_loc, op_loc);
		      t_व्यंजक.m_decimal = 0;
		      t_व्यंजक = convert_lvalue_to_rvalue (op_loc, t_व्यंजक,
							 true, false);
		      t = build_indirect_ref (op_loc, t_व्यंजक.मूल्य, RO_ARROW);
		      arrow_loc = t_व्यंजक.get_location ();
		    }
		  c_parser_consume_token (parser);
		  अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_गाँठ;
		      अवरोध;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  वृक्ष ident = comp_tok->मूल्य;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    हाल OMP_CLAUSE_AFFINITY:
	    हाल OMP_CLAUSE_DEPEND:
	    हाल OMP_CLAUSE_REDUCTION:
	    हाल OMP_CLAUSE_IN_REDUCTION:
	    हाल OMP_CLAUSE_TASK_REDUCTION:
	    हाल OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = false;
	      dims.truncate (0);
	      जबतक (c_parser_अग्र_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  वृक्ष निचला_bound = NULL_वृक्ष, लंबाई = NULL_वृक्ष;
		  bool no_colon = false;

		  c_parser_consume_token (parser);
		  अगर (!c_parser_अग्र_token_is (parser, CPP_COLON))
		    {
		      location_t व्यंजक_loc
			= c_parser_peek_token (parser)->location;
		      c_व्यंजक व्यंजक = c_parser_expression (parser);
		      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक,
						       false, true);
		      निचला_bound = व्यंजक.मूल्य;
		      loc = व्यंजक_loc;
		    }
		  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      लंबाई = integer_one_गाँठ;
		      no_colon = true;
		    }
		  अन्यथा
		    {
		      /* Look for `:'.  */
		      अगर (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_गाँठ;
			  अवरोध;
			}
		      array_section_p = true;
		      अगर (!c_parser_अग्र_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t व्यंजक_loc
			    = c_parser_peek_token (parser)->location;
			  c_व्यंजक व्यंजक = c_parser_expression (parser);
			  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक,
							   false, true);
			  लंबाई = व्यंजक.मूल्य;
			}
		    }
		  /* Look for the closing `]'.  */
		  अगर (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_गाँठ;
		      अवरोध;
		    }

		  dims.safe_धकेलो (omp_dim (निचला_bound, लंबाई, loc, no_colon));
		}

	      अगर (t != error_mark_गाँठ)
		{
		  अगर ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_अग्र_token_is (parser, CPP_DOT)
			  || c_parser_अग्र_token_is (parser, CPP_DEREF)))
		    {
		      क्रम (अचिन्हित i = 0; i < dims.लंबाई (); i++)
			{
			  gcc_assert (dims[i].लंबाई == integer_one_गाँठ);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].निचला_bound);
			}
		      जाओ start_component_ref;
		    }
		  अन्यथा
		    क्रम (अचिन्हित i = 0; i < dims.लंबाई (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].निचला_bound,
						   dims[i].लंबाई);
		}

	      अगर ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_गाँठ
		  && parser->tokens_avail != 2)
		{
		  अगर (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_गाँठ;
		    }
		  अन्यथा
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.लंबाई ();

		      t = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
		      अगर (t != error_mark_गाँठ && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_गाँठ;
			}
		    }
		}
	      अवरोध;
	    शेष:
	      अवरोध;
	    }

	  अगर (t != error_mark_गाँठ)
	    {
	      वृक्ष u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      अन्यथा  /* kind == OMP_CLAUSE_ERROR */
	list = वृक्ष_cons (t, build_empty_stmt (tloc), list);

      अगर (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    अग्र_item:
      अगर (c_parser_अग्र_token_is_not (parser, CPP_COMMA))
	अवरोध;

      c_parser_consume_token (parser);
    }

  वापस list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

अटल वृक्ष
c_parser_omp_var_list_parens (c_parser *parser, क्रमागत omp_clause_code kind,
			      वृक्ष list, bool map_lvalue = false)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  अगर (parser->in_omp_decl_attribute)
    {
      अगर (kind)
	{
	  वृक्ष u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  वापस u;
	}
      अन्यथा
	वापस वृक्ष_cons (parser->in_omp_decl_attribute, NULL_वृक्ष, list);
    }

  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  वापस list;
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

अटल वृक्ष
c_parser_oacc_तथ्य_clause (c_parser *parser, pragma_omp_clause c_kind,
			   वृक्ष list)
{
  क्रमागत gomp_map_kind kind;
  चयन (c_kind)
    {
    हाल PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      अवरोध;
    हाल PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    हाल PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      अवरोध;
    शेष:
      gcc_unreachable ();
    }

  वृक्ष nl = list;
  bool readonly = false;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      अगर (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  अगर (token->type == CPP_NAME
	      && !म_भेद (IDENTIFIER_POINTER (token->मूल्य), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = true;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       false);
      parens.skip_until_found_close (parser);
    }

  क्रम (वृक्ष c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      अगर (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  वापस nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

अटल वृक्ष
c_parser_oacc_तथ्य_clause_deviceptr (c_parser *parser, वृक्ष list)
{
  वृक्ष vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, शून्य);
  क्रम (t = vars; t && t; t = वृक्ष_CHAIN (t))
    {
      वृक्ष v = वृक्ष_PURPOSE (t);
      location_t loc = व्यंजक_LOCATION (वृक्ष_मूल्य (t));

      अगर (!VAR_P (v) && वृक्ष_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      अन्यथा अगर (वृक्ष_TYPE (v) == error_mark_गाँठ)
	;
      अन्यथा अगर (!POINTER_TYPE_P (वृक्ष_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      वृक्ष u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  वापस list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

अटल वृक्ष
c_parser_omp_clause_collapse (c_parser *parser, वृक्ष list)
{
  वृक्ष c, अंक = error_mark_गाँठ;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      अंक = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
      parens.skip_until_found_close (parser);
    }
  अगर (अंक == error_mark_गाँठ)
    वापस list;
  mark_exp_read (अंक);
  अंक = c_fully_fold (अंक, false, शून्य);
  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (अंक))
      || !वृक्ष_fits_shwi_p (अंक)
      || (n = वृक्ष_to_shwi (अंक)) <= 0
      || (पूर्णांक) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      वापस list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_व्यंजक (c) = अंक;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_copyin (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_copyprivate (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

अटल वृक्ष
c_parser_omp_clause_default (c_parser *parser, वृक्ष list, bool is_oacc)
{
  क्रमागत omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष c;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      चयन (p[0])
	{
	हाल 'n':
	  अगर (म_भेद ("none", p) != 0)
	    जाओ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  अवरोध;

	हाल 'p':
	  अगर (is_oacc)
	    {
	      अगर (म_भेद ("present", p) != 0)
		जाओ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  अन्यथा
	    {
	      अगर (म_भेद ("private", p) != 0)
		जाओ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  अवरोध;

	हाल 'f':
	  अगर (म_भेद ("firstprivate", p) != 0 || is_oacc)
	    जाओ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  अवरोध;

	हाल 's':
	  अगर (म_भेद ("shared", p) != 0 || is_oacc)
	    जाओ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  अवरोध;

	शेष:
	  जाओ invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  अन्यथा
    {
    invalid_kind:
      अगर (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      अन्यथा
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  अगर (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    वापस list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  वापस c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_firstprivate (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

अटल वृक्ष
c_parser_omp_clause_final (c_parser *parser, वृक्ष list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      वृक्ष t, c;
      अगर (!parens.require_open (parser))
	t = error_mark_गाँठ;
      अन्यथा
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  t = convert_lvalue_to_rvalue (eloc, व्यंजक, true, true).मूल्य;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, false, शून्य);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_व्यंजक (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  अन्यथा
    c_parser_error (parser, "expected %<(%>");

  वापस list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

अटल वृक्ष
c_parser_omp_clause_indirect (c_parser *parser, वृक्ष list)
{
  location_t location = c_parser_peek_token (parser)->location;
  वृक्ष t;

  अगर (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      अगर (!parens.require_open (parser))
	वापस list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, true, true);
      t = c_objc_common_truthvalue_conversion (loc, व्यंजक.मूल्य);
      t = c_fully_fold (t, false, शून्य);
      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t))
	  || वृक्ष_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  वापस list;
	}
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    t = integer_one_गाँठ;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  वृक्ष c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_व्यंजक (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  वापस c;
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

अटल वृक्ष
c_parser_omp_clause_if (c_parser *parser, वृक्ष list, bool is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  क्रमागत वृक्ष_code if_modifier = ERROR_MARK;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर (is_omp && c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      पूर्णांक n = 2;
      अगर (म_भेद (p, "cancel") == 0)
	if_modifier = VOID_CST;
      अन्यथा अगर (म_भेद (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      अन्यथा अगर (म_भेद (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      अन्यथा अगर (म_भेद (p, "task") == 0)
	if_modifier = OMP_TASK;
      अन्यथा अगर (म_भेद (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      अन्यथा अगर (म_भेद (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  अगर (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->मूल्य);
	      अगर (म_भेद ("data", p) == 0)
		if_modifier = OMP_TARGET_तथ्य;
	      अन्यथा अगर (म_भेद ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      अन्यथा अगर (म_भेद ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_तथ्य;
	      अन्यथा अगर (म_भेद ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_तथ्य;
	      अगर (if_modifier != OMP_TARGET)
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
	      अगर (if_modifier == OMP_TARGET_ENTER_तथ्य
		  || if_modifier == OMP_TARGET_EXIT_तथ्य)
		{
		  अगर (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->मूल्य);
		      अगर (म_भेद ("data", p) == 0)
			n = 4;
		    }
		  अगर (n == 4)
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
      अगर (if_modifier != ERROR_MARK)
	{
	  अगर (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा
	    {
	      अगर (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, true, true);
  वृक्ष t = c_objc_common_truthvalue_conversion (loc, व्यंजक.मूल्य), c;
  t = c_fully_fold (t, false, शून्य);
  parens.skip_until_found_close (parser);

  क्रम (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	अगर (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    स्थिर अक्षर *p = शून्य;
	    चयन (if_modifier)
	      {
	      हाल VOID_CST: p = "cancel"; अवरोध;
	      हाल OMP_PARALLEL: p = "parallel"; अवरोध;
	      हाल OMP_SIMD: p = "simd"; अवरोध;
	      हाल OMP_TASK: p = "task"; अवरोध;
	      हाल OMP_TASKLOOP: p = "taskloop"; अवरोध;
	      हाल OMP_TARGET_तथ्य: p = "target data"; अवरोध;
	      हाल OMP_TARGET: p = "target"; अवरोध;
	      हाल OMP_TARGET_UPDATE: p = "target update"; अवरोध;
	      हाल OMP_TARGET_ENTER_तथ्य: p = "target enter data"; अवरोध;
	      हाल OMP_TARGET_EXIT_तथ्य: p = "target exit data"; अवरोध;
	      शेष: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    वापस list;
	  }
	अन्यथा अगर (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    अगर (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    अन्यथा
	      error_at (location, "too many %<if%> clauses without modifier");
	    वापस list;
	  }
	अन्यथा अगर (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    वापस list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_व्यंजक (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

अटल वृक्ष
c_parser_omp_clause_lastprivate (c_parser *parser, वृक्ष list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  अगर (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      bool conditional = false;
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  स्थिर अक्षर *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	  अगर (म_भेद (p, "conditional") == 0)
	    {
	      conditional = true;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      वृक्ष nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      अगर (conditional)
	क्रम (वृक्ष c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      वापस nlist;
    }
  वापस list;
}

/* OpenMP 3.1:
   mergeable */

अटल वृक्ष
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, वृक्ष list)
{
  वृक्ष c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  वापस c;
}

/* OpenMP 2.5:
   nowait */

अटल वृक्ष
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, वृक्ष list)
{
  वृक्ष c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

अटल वृक्ष
c_parser_omp_clause_अंक_threads (c_parser *parser, वृक्ष list)
{
  location_t अंक_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      वृक्ष c, t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);

      parens.skip_until_found_close (parser);

      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  वापस list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (व्यंजक_loc, LE_व्यंजक, boolean_type_गाँठ, t,
		       build_int_cst (वृक्ष_TYPE (t), 0));
      protected_set_व्यंजक_location (c, व्यंजक_loc);
      अगर (c == boolean_true_गाँठ)
	{
	  warning_at (व्यंजक_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_गाँठ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अंक_THREADS, "num_threads");

      c = build_omp_clause (अंक_threads_loc, OMP_CLAUSE_अंक_THREADS);
      OMP_CLAUSE_अंक_THREADS_व्यंजक (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

अटल वृक्ष
c_parser_omp_clause_अंक_tasks (c_parser *parser, वृक्ष list)
{
  location_t अंक_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      bool strict = false;
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य),
		     "strict") == 0)
	{
	  strict = true;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      वृक्ष c, t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);

      parens.skip_until_found_close (parser);

      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  वापस list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (व्यंजक_loc, LE_व्यंजक, boolean_type_गाँठ, t,
			   build_int_cst (वृक्ष_TYPE (t), 0));
      अगर (CAN_HAVE_LOCATION_P (c))
	SET_व्यंजक_LOCATION (c, व्यंजक_loc);
      अगर (c == boolean_true_गाँठ)
	{
	  warning_at (व्यंजक_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_गाँठ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अंक_TASKS, "num_tasks");

      c = build_omp_clause (अंक_tasks_loc, OMP_CLAUSE_अंक_TASKS);
      OMP_CLAUSE_अंक_TASKS_व्यंजक (c) = t;
      OMP_CLAUSE_अंक_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

अटल वृक्ष
c_parser_omp_clause_grainsize (c_parser *parser, वृक्ष list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      bool strict = false;
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य),
		     "strict") == 0)
	{
	  strict = true;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      वृक्ष c, t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);

      parens.skip_until_found_close (parser);

      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  वापस list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (व्यंजक_loc, LE_व्यंजक, boolean_type_गाँठ, t,
			   build_int_cst (वृक्ष_TYPE (t), 0));
      अगर (CAN_HAVE_LOCATION_P (c))
	SET_व्यंजक_LOCATION (c, व्यंजक_loc);
      अगर (c == boolean_true_गाँठ)
	{
	  warning_at (व्यंजक_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_गाँठ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_व्यंजक (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenMP 4.5:
   priority ( expression ) */

अटल वृक्ष
c_parser_omp_clause_priority (c_parser *parser, वृक्ष list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      वृक्ष c, t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);

      parens.skip_until_found_close (parser);

      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  वापस list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (व्यंजक_loc, LT_व्यंजक, boolean_type_गाँठ, t,
			   build_int_cst (वृक्ष_TYPE (t), 0));
      अगर (CAN_HAVE_LOCATION_P (c))
	SET_व्यंजक_LOCATION (c, व्यंजक_loc);
      अगर (c == boolean_true_गाँठ)
	{
	  warning_at (व्यंजक_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_गाँठ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_व्यंजक (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenMP 4.5:
   hint ( expression ) */

अटल वृक्ष
c_parser_omp_clause_hint (c_parser *parser, वृक्ष list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      वृक्ष c, t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);
      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t))
	  || वृक्ष_CODE (t) != INTEGER_CST
	  || वृक्ष_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  वापस list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_व्यंजक (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

अटल वृक्ष
c_parser_omp_clause_filter (c_parser *parser, वृक्ष list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      वृक्ष c, t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);
      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  वापस list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_व्यंजक (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

अटल वृक्ष
c_parser_omp_clause_defaultmap (c_parser *parser, वृक्ष list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष c;
  स्थिर अक्षर *p;
  क्रमागत omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  क्रमागत omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  अन्यथा अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      जाओ out_err;
    }
  अन्यथा
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

  चयन (p[0])
    {
    हाल 'a':
      अगर (म_भेद ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      अन्यथा
	जाओ invalid_behavior;
      अवरोध;

    हाल 'd':
      अगर (म_भेद ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      अन्यथा
	जाओ invalid_behavior;
      अवरोध;

    हाल 'f':
      अगर (म_भेद ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      अन्यथा अगर (म_भेद ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      अन्यथा
	जाओ invalid_behavior;
      अवरोध;

    हाल 'n':
      अगर (म_भेद ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      अन्यथा
	जाओ invalid_behavior;
      अवरोध;

    हाल 'p':
      अगर (म_भेद ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      अन्यथा
	जाओ invalid_behavior;
      अवरोध;

    हाल 't':
      अगर (म_भेद ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      अन्यथा अगर (म_भेद ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      अन्यथा
	जाओ invalid_behavior;
      अवरोध;

    शेष:
      जाओ invalid_behavior;
    }
  c_parser_consume_token (parser);

  अगर (!c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
    {
      अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	जाओ out_err;
      अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  जाओ out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      चयन (p[0])
	{
	हाल 'a':
	  अगर (म_भेद ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  अन्यथा अगर (म_भेद ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  अन्यथा
	    जाओ invalid_category;
	  अवरोध;

	हाल 'p':
	  अगर (म_भेद ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  अन्यथा
	    जाओ invalid_category;
	  अवरोध;

	हाल 's':
	  अगर (म_भेद ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  अन्यथा
	    जाओ invalid_category;
	  अवरोध;

	शेष:
	  जाओ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  क्रम (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	क्रमागत omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	अगर (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = शून्य;
	चयन (cat)
	  {
	  हाल OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = शून्य;
	    अवरोध;
	  हाल OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    अवरोध;
	  हाल OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    अवरोध;
	  हाल OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    अवरोध;
	  हाल OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    अवरोध;
	  शेष:
	    gcc_unreachable ();
	  }
	अगर (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	अन्यथा
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	अवरोध;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;

 out_err:
  parens.skip_until_found_close (parser);
  वापस list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_use_device_ptr (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_use_device_addr (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_has_device_addr (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_is_device_ptr (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

अटल वृक्ष
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 वृक्ष list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
  c_व्यंजक व्यंजक = c_parser_expression (parser);
  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
  वृक्ष c, t = व्यंजक.मूल्य;
  t = c_fully_fold (t, false, शून्य);

  parens.skip_until_found_close (parser);

  अगर (t == error_mark_गाँठ)
    वापस list;
  अन्यथा अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
    {
      error_at (व्यंजक_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      वापस list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (व्यंजक_loc, LE_व्यंजक, boolean_type_गाँठ, t,
		       build_int_cst (वृक्ष_TYPE (t), 0));
  protected_set_व्यंजक_location (c, व्यंजक_loc);
  अगर (c == boolean_true_गाँठ)
    {
      warning_at (व्यंजक_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_गाँठ;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
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

अटल वृक्ष
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    स्थिर अक्षर *str, वृक्ष list)
{
  स्थिर अक्षर *id = "num";
  वृक्ष ops[2] = { NULL_वृक्ष, NULL_वृक्ष }, c;

  अगर (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      करो
	{
	  c_token *अग्र = c_parser_peek_token (parser);
	  पूर्णांक idx = 0;

	  /* Gang static argument.  */
	  अगर (kind == OMP_CLAUSE_GANG
	      && c_parser_अग्र_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		जाओ cleanup_error;

	      idx = 1;
	      अगर (ops[idx] != NULL_वृक्ष)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  जाओ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      अगर (c_parser_अग्र_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_गाँठ;

		  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      जारी;
		    }
		  अन्यथा
		    अवरोध;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
		   && म_भेद (id, IDENTIFIER_POINTER (अग्र->मूल्य)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  अगर (ops[idx] != NULL_वृक्ष)
	    {
	      c_parser_error (parser, "unexpected argument");
	      जाओ cleanup_error;
	    }

	  location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
	  c_व्यंजक cexpr = c_parser_व्यंजक_no_commas (parser, शून्य);
	  cexpr = convert_lvalue_to_rvalue (व्यंजक_loc, cexpr, false, true);
	  वृक्ष व्यंजक = cexpr.मूल्य;
	  अगर (व्यंजक == error_mark_गाँठ)
	    जाओ cleanup_error;

	  व्यंजक = c_fully_fold (व्यंजक, false, शून्य);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (व्यंजक)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      वापस list;
	    }

	  वृक्ष c = fold_build2_loc (व्यंजक_loc, LE_व्यंजक, boolean_type_गाँठ, व्यंजक,
				    build_int_cst (वृक्ष_TYPE (व्यंजक), 0));
	  अगर (c == boolean_true_गाँठ)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      व्यंजक = integer_one_गाँठ;
	    }

	  ops[idx] = व्यंजक;

	  अगर (kind == OMP_CLAUSE_GANG
	      && c_parser_अग्र_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  अवरोध;
	}
      जबतक (1);

      अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	जाओ cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  अगर (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  वापस c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  वापस list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

अटल वृक्ष
c_parser_oacc_simple_clause (location_t loc, क्रमागत omp_clause_code code,
			     वृक्ष list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  वृक्ष c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  वापस c;
}

/* OpenACC:
   async [( int-expr )] */

अटल वृक्ष
c_parser_oacc_clause_async (c_parser *parser, वृक्ष list)
{
  वृक्ष c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_गाँठ, GOMP_ASYNC_NOVAL);

  अगर (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      अन्यथा अगर (t == error_mark_गाँठ
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	वापस list;
    }
  अन्यथा
    t = c_fully_fold (t, false, शून्य);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_व्यंजक (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  वापस list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

अटल वृक्ष
c_parser_oacc_clause_tile (c_parser *parser, वृक्ष list)
{
  वृक्ष c, व्यंजक = error_mark_गाँठ;
  location_t loc;
  वृक्ष tile = NULL_वृक्ष;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    वापस list;

  करो
    {
      अगर (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	वापस list;

      अगर (c_parser_अग्र_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  व्यंजक = integer_zero_गाँठ;
	}
      अन्यथा
	{
	  location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
	  c_व्यंजक cexpr = c_parser_व्यंजक_no_commas (parser, शून्य);
	  cexpr = convert_lvalue_to_rvalue (व्यंजक_loc, cexpr, false, true);
	  व्यंजक = cexpr.मूल्य;

	  अगर (व्यंजक == error_mark_गाँठ)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      वापस list;
	    }

	  व्यंजक = c_fully_fold (व्यंजक, false, शून्य);

	  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (व्यंजक))
	      || !वृक्ष_fits_shwi_p (व्यंजक)
	      || वृक्ष_to_shwi (व्यंजक) <= 0)
	    {
	      error_at (व्यंजक_loc, "%<tile%> argument needs positive"
			" integral constant");
	      व्यंजक = integer_zero_गाँठ;
	    }
	}

      tile = वृक्ष_cons (NULL_वृक्ष, व्यंजक, tile);
    }
  जबतक (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenACC:
   wait [( int-expr-list )] */

अटल वृक्ष
c_parser_oacc_clause_wait (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  अगर (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  अन्यथा
    {
      वृक्ष c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_गाँठ, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenACC 2.7:
   self [( expression )] */

अटल वृक्ष
c_parser_oacc_compute_clause_self (c_parser *parser, वृक्ष list)
{
  वृक्ष t;
  location_t location = c_parser_peek_token (parser)->location;
  अगर (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, true, true);
      t = c_objc_common_truthvalue_conversion (loc, व्यंजक.मूल्य);
      t = c_fully_fold (t, false, शून्य);
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    t = truthvalue_true_गाँठ;

  क्रम (वृक्ष c = list; c; c = OMP_CLAUSE_CHAIN (c))
    अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	वापस list;
      }

  वृक्ष c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_व्यंजक (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

अटल वृक्ष
c_parser_omp_clause_order (c_parser *parser, वृक्ष list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष c;
  स्थिर अक्षर *p;
  bool unconstrained = false;
  bool reproducible = false;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "unconstrained") == 0)
	unconstrained = true;
      अन्यथा अगर (म_भेद (p, "reproducible") == 0)
	reproducible = true;
      अन्यथा
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  जाओ out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      जाओ out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
  अगर (म_भेद (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      जाओ out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;

 out_err:
  parens.skip_until_found_close (parser);
  वापस list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

अटल वृक्ष
c_parser_omp_clause_bind (c_parser *parser, वृक्ष list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष c;
  स्थिर अक्षर *p;
  क्रमागत omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;
  अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      वापस list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
  अगर (म_भेद (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  अन्यथा अगर (म_भेद (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  अन्यथा अगर (म_भेद (p, "thread") != 0)
    जाओ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

अटल वृक्ष
c_parser_omp_clause_ordered (c_parser *parser, वृक्ष list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  वृक्ष c, अंक = NULL_वृक्ष;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      अंक = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
      parens.skip_until_found_close (parser);
    }
  अगर (अंक == error_mark_गाँठ)
    वापस list;
  अगर (अंक)
    {
      mark_exp_read (अंक);
      अंक = c_fully_fold (अंक, false, शून्य);
      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (अंक))
	  || !वृक्ष_fits_shwi_p (अंक)
	  || (n = वृक्ष_to_shwi (अंक)) <= 0
	  || (पूर्णांक) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  वापस list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_व्यंजक (c) = अंक;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_private (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

अटल वृक्ष
c_parser_omp_clause_reduction (c_parser *parser, क्रमागत omp_clause_code kind,
			       bool is_omp, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      bool task = false;
      bool inscan = false;
      क्रमागत वृक्ष_code code = ERROR_MARK;
      वृक्ष reduc_id = NULL_वृक्ष;

      अगर (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  अगर (c_parser_अग्र_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      स्थिर अक्षर *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	      अगर (म_भेद (p, "task") == 0)
		task = true;
	      अन्यथा अगर (म_भेद (p, "inscan") == 0)
		inscan = true;
	      अगर (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_PLUS:
	  code = PLUS_व्यंजक;
	  अवरोध;
	हाल CPP_MULT:
	  code = MULT_व्यंजक;
	  अवरोध;
	हाल CPP_MINUS:
	  अगर (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_व्यंजक;
	  अवरोध;
	हाल CPP_AND:
	  code = BIT_AND_व्यंजक;
	  अवरोध;
	हाल CPP_XOR:
	  code = BIT_XOR_व्यंजक;
	  अवरोध;
	हाल CPP_OR:
	  code = BIT_IOR_व्यंजक;
	  अवरोध;
	हाल CPP_AND_AND:
	  code = TRUTH_ANDIF_व्यंजक;
	  अवरोध;
	हाल CPP_OR_OR:
	  code = TRUTH_ORIF_व्यंजक;
	  अवरोध;
        हाल CPP_NAME:
	  {
	    स्थिर अक्षर *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	    अगर (म_भेद (p, "min") == 0)
	      {
		code = MIN_व्यंजक;
		अवरोध;
	      }
	    अगर (म_भेद (p, "max") == 0)
	      {
		code = MAX_व्यंजक;
		अवरोध;
	      }
	    reduc_id = c_parser_peek_token (parser)->मूल्य;
	    अवरोध;
	  }
	शेष:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  वापस list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      अगर (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  वृक्ष nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  क्रम (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      वृक्ष d = OMP_CLAUSE_DECL (c), type;
	      अगर (वृक्ष_CODE (d) != OMP_ARRAY_SECTION)
		type = वृक्ष_TYPE (d);
	      अन्यथा
		{
		  पूर्णांक cnt = 0;
		  वृक्ष t;
		  क्रम (t = d;
		      वृक्ष_CODE (t) == OMP_ARRAY_SECTION;
		      t = वृक्ष_OPERAND (t, 0))
		    cnt++;
		  type = वृक्ष_TYPE (t);
		  जबतक (cnt > 0)
		    {
		      अगर (वृक्ष_CODE (type) != POINTER_TYPE
			  && वृक्ष_CODE (type) != ARRAY_TYPE)
			अवरोध;
		      type = वृक्ष_TYPE (type);
		      cnt--;
		    }
		}
	      जबतक (वृक्ष_CODE (type) == ARRAY_TYPE)
		type = वृक्ष_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      अगर (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      अन्यथा अगर (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      अगर (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || वृक्ष_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  वापस list;
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

अटल वृक्ष
c_parser_omp_clause_schedule (c_parser *parser, वृक्ष list)
{
  वृक्ष c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  पूर्णांक modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  जबतक (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      वृक्ष kind = c_parser_peek_token (parser)->मूल्य;
      स्थिर अक्षर *p = IDENTIFIER_POINTER (kind);
      अगर (म_भेद ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      अन्यथा अगर (म_भेद ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      अन्यथा अगर (म_भेद ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      अन्यथा
	अवरोध;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      अगर (nmodifiers++ == 0
	  && c_parser_अग्र_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      अन्यथा
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  अवरोध;
	}
    }
  अगर (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  अगर ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      वृक्ष kind = c_parser_peek_token (parser)->मूल्य;
      स्थिर अक्षर *p = IDENTIFIER_POINTER (kind);

      चयन (p[0])
	{
	हाल 'd':
	  अगर (म_भेद ("dynamic", p) != 0)
	    जाओ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  अवरोध;

        हाल 'g':
	  अगर (म_भेद ("guided", p) != 0)
	    जाओ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  अवरोध;

	हाल 'r':
	  अगर (म_भेद ("runtime", p) != 0)
	    जाओ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  अवरोध;

	शेष:
	  जाओ invalid_kind;
	}
    }
  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  अन्यथा अगर (c_parser_अग्र_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  अन्यथा
    जाओ invalid_kind;

  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (here, व्यंजक, false, true);
      t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);

      अगर (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      अन्यथा अगर (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      अन्यथा अगर (वृक्ष_CODE (वृक्ष_TYPE (t)) == INTEGER_TYPE
	       || वृक्ष_CODE (वृक्ष_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  वृक्ष s = fold_build2_loc (loc, LE_व्यंजक, boolean_type_गाँठ, t,
				    build_int_cst (वृक्ष_TYPE (t), 0));
	  protected_set_व्यंजक_location (s, loc);
	  अगर (s == boolean_true_गाँठ)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_गाँठ;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_व्यंजक (c) = t;
	}
      अन्यथा
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  अन्यथा
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (क्रमागत omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  वापस list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_shared (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

अटल वृक्ष
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, वृक्ष list)
{
  वृक्ष c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  वापस c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

अटल वृक्ष
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    क्रमागत omp_clause_code code, वृक्ष list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  वृक्ष c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  वापस c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

अटल वृक्ष
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				क्रमागत omp_clause_code code, वृक्ष list)
{
  वृक्ष c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  वापस c;
}

/* OpenMP 4.5:
   nogroup */

अटल वृक्ष
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, वृक्ष list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  वृक्ष c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 4.5:
   simd
   threads */

अटल वृक्ष
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 क्रमागत omp_clause_code code, वृक्ष list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  वृक्ष c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

अटल वृक्ष
c_parser_omp_clause_अंक_teams (c_parser *parser, वृक्ष list)
{
  location_t अंक_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (upper_loc, व्यंजक, false, true);
      वृक्ष c, upper = व्यंजक.मूल्य, lower = NULL_वृक्ष;
      upper = c_fully_fold (upper, false, शून्य);

      अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  व्यंजक = convert_lvalue_to_rvalue (upper_loc, व्यंजक, false, true);
	  upper = व्यंजक.मूल्य;
	  upper = c_fully_fold (upper, false, शून्य);
	}

      parens.skip_until_found_close (parser);

      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (वृक्ष_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  वापस list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_व्यंजक, boolean_type_गाँठ, upper,
			   build_int_cst (वृक्ष_TYPE (upper), 0));
      protected_set_व्यंजक_location (c, upper_loc);
      अगर (c == boolean_true_गाँठ)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_गाँठ;
	}
      अगर (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_व्यंजक, boolean_type_गाँठ, lower,
			       build_int_cst (वृक्ष_TYPE (lower), 0));
	  protected_set_व्यंजक_location (c, lower_loc);
	  अगर (c == boolean_true_गाँठ)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_वृक्ष;
	    }
	  अन्यथा अगर (वृक्ष_CODE (lower) == INTEGER_CST
		   && वृक्ष_CODE (upper) == INTEGER_CST
		   && वृक्ष_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_वृक्ष;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_अंक_TEAMS, "num_teams");

      c = build_omp_clause (अंक_teams_loc, OMP_CLAUSE_अंक_TEAMS);
      OMP_CLAUSE_अंक_TEAMS_UPPER_व्यंजक (c) = upper;
      OMP_CLAUSE_अंक_TEAMS_LOWER_व्यंजक (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

अटल वृक्ष
c_parser_omp_clause_thread_limit (c_parser *parser, वृक्ष list)
{
  location_t अंक_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      वृक्ष c, t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);

      parens.skip_until_found_close (parser);

      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  वापस list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (व्यंजक_loc, LE_व्यंजक, boolean_type_गाँठ, t,
			   build_int_cst (वृक्ष_TYPE (t), 0));
      protected_set_व्यंजक_location (c, व्यंजक_loc);
      अगर (c == boolean_true_गाँठ)
	{
	  warning_at (व्यंजक_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_गाँठ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (अंक_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_व्यंजक (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  वापस list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

अटल वृक्ष
c_parser_omp_clause_aligned (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्ष nl, c;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      वृक्ष alignment = व्यंजक.मूल्य;
      alignment = c_fully_fold (alignment, false, शून्य);
      अगर (वृक्ष_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (वृक्ष_TYPE (alignment))
	  || वृक्ष_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_वृक्ष;
	}

      क्रम (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  वापस nl;
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

अटल वृक्ष
c_parser_omp_clause_allocate (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्ष nl, c;
  वृक्ष allocator = NULL_वृक्ष;
  वृक्ष align = NULL_वृक्ष;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर ((c_parser_अग्र_token_is_not (parser, CPP_NAME)
       && c_parser_अग्र_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      bool has_modifiers = false;
      वृक्ष orig_type = NULL_वृक्ष;
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  अचिन्हित पूर्णांक n = 3;
	  स्थिर अक्षर *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	  अगर ((म_भेद (p, "allocator") == 0 || म_भेद (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      अगर (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = true;
	      अन्यथा अगर (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  स्थिर अक्षर *q = IDENTIFIER_POINTER (tok->मूल्य);
		  n += 4;
		  अगर ((म_भेद (q, "allocator") == 0
		       || म_भेद (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = true;
		}
	    }
	  अगर (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
	      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
	      अगर (व्यंजक.मूल्य == error_mark_गाँठ)
		;
	      अन्यथा अगर (म_भेद (p, "allocator") == 0)
		{
		  allocator = व्यंजक.मूल्य;
		  allocator = c_fully_fold (allocator, false, शून्य);
		  orig_type = व्यंजक.original_type
			      ? व्यंजक.original_type : वृक्ष_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      अन्यथा
		{
		  align = व्यंजक.मूल्य;
		  align = c_fully_fold (align, false, शून्य);
		}
	      parens2.skip_until_found_close (parser);
	      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  स्थिर अक्षर *q = "";
		  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->मूल्य);
		  अगर (म_भेद (q, "allocator") != 0 && म_भेद (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      वापस list;
		    }
		  अन्यथा अगर (म_भेद (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      वापस list;
		    }
		  c_parser_consume_token (parser);
		  अगर (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      वापस list;
		    }
		  व्यंजक_loc = c_parser_peek_token (parser)->location;
		  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
		  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false,
						   true);
		  अगर (म_भेद (q, "allocator") == 0)
		    {
		      allocator = व्यंजक.मूल्य;
		      allocator = c_fully_fold (allocator, false, शून्य);
		      orig_type = व्यंजक.original_type
				  ? व्यंजक.original_type : वृक्ष_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  अन्यथा
		    {
		      align = व्यंजक.मूल्य;
		      align = c_fully_fold (align, false, शून्य);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      अगर (!has_modifiers)
	{
	  location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
	  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
	  अगर (व्यंजक.मूल्य != error_mark_गाँठ)
	    {
	      allocator = व्यंजक.मूल्य;
	      allocator = c_fully_fold (allocator, false, शून्य);
	      orig_type = व्यंजक.original_type
			  ? व्यंजक.original_type : वृक्ष_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      अगर (allocator
	  && (!INTEGRAL_TYPE_P (वृक्ष_TYPE (allocator))
	      || वृक्ष_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				वृक्ष_TYPE (allocator));
          allocator = NULL_वृक्ष;
        }
      अगर (align
	  && (!INTEGRAL_TYPE_P (वृक्ष_TYPE (align))
	      || !वृक्ष_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_वृक्ष;
	}
      अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  वापस list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  अगर (allocator || align)
    क्रम (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  वापस nl;
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

अटल वृक्ष
c_parser_omp_clause_uses_allocators (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्ष nl = list;
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

parse_अग्र:

  bool has_modifiers = false;
  bool seen_allocators = false;
  वृक्ष memspace_व्यंजक = NULL_वृक्ष;
  वृक्ष traits_var = NULL_वृक्ष;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      अचिन्हित पूर्णांक n = 3;
      स्थिर अक्षर *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर ((म_भेद (p, "traits") == 0 || म_भेद (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  अगर (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = true;
	  अन्यथा अगर (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      स्थिर अक्षर *q = IDENTIFIER_POINTER (tok->मूल्य);
	      n += 4;
	      अगर ((म_भेद (q, "traits") == 0
		   || म_भेद (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  अगर (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = true;
		  अगर ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      स्थिर अक्षर *m = IDENTIFIER_POINTER (tok->मूल्य);
		      अगर (म_भेद (p, m) == 0 || म_भेद (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  जाओ end;
			}
		    }
		}
	    }
	}
      अगर (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  अगर (व्यंजक.मूल्य == error_mark_गाँठ)
	    ;
	  अन्यथा अगर (म_भेद (p, "traits") == 0)
	    {
	      traits_var = व्यंजक.मूल्य;
	      traits_var = c_fully_fold (traits_var, false, शून्य);
	      mark_exp_read (traits_var);
	    }
	  अन्यथा
	    {
	      memspace_व्यंजक = व्यंजक.मूल्य;
	      memspace_व्यंजक = c_fully_fold (memspace_व्यंजक, false, शून्य);
	    }
	  parens2.skip_until_found_close (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      स्थिर अक्षर *q = "";
	      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->मूल्य);
	      अगर (म_भेद (q, "traits") != 0 && म_भेद (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  वापस list;
		}
	      अन्यथा अगर (म_भेद (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  वापस list;
		}
	      c_parser_consume_token (parser);
	      अगर (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  वापस list;
		}
	      व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	      अगर (म_भेद (q, "traits") == 0)
		{
		  traits_var = व्यंजक.मूल्य;
		  traits_var = c_fully_fold (traits_var, false, शून्य);
		  mark_exp_read (traits_var);
		}
	      अन्यथा
		{
		  memspace_व्यंजक = व्यंजक.मूल्य;
		  memspace_व्यंजक = c_fully_fold (memspace_व्यंजक, false, शून्य);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    जाओ end;
	}
    }

  जबतक (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      स्थिर अक्षर *tok_s = IDENTIFIER_POINTER (tok->मूल्य);
      वृक्ष t = lookup_name (tok->मूल्य);
      अगर (t == NULL_वृक्ष)
	{
	  undeclared_variable (tok->location, tok->मूल्य);
	  t = error_mark_गाँठ;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      वृक्ष legacy_traits = NULL_वृक्ष;
      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  स्थिर अक्षर *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  अगर (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      जाओ end;
	    }
	  legacy_traits = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
	  अगर (legacy_traits == error_mark_गाँठ)
	    जाओ end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  अगर (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_जोड़ो_after (close_loc, ": ");
	      richloc.add_fixit_जोड़ो_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      अगर (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  जाओ end;
	}
      seen_allocators = true;

      वृक्ष c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_व्यंजक;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
    }

  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      जाओ parse_अग्र;
    }

 end:
  parens.skip_until_found_close (parser);
  वापस nl;
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

अटल वृक्ष
c_parser_omp_clause_linear (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  वृक्ष nl, c, step;
  क्रमागत omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  bool old_linear_modifier = false;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      स्थिर अक्षर *p = IDENTIFIER_POINTER (tok->मूल्य);
      अगर (म_भेद ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      अगर (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      अगर (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = true;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  अगर (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = व्यंजक_loc;
      bool has_modifiers = false;
      अगर (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  स्थिर अक्षर *p = IDENTIFIER_POINTER (tok->मूल्य);
	  अचिन्हित पूर्णांक pos = 0;
	  अगर (म_भेद ("val", p) == 0)
	    pos = 2;
	  अन्यथा अगर (म_भेद ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      अगर (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      अन्यथा
		pos = 0;
	    }
	  अगर (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      अगर (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = true;
	    }
	}
      अगर (has_modifiers)
	{
	  step = NULL_वृक्ष;
	  जबतक (c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      स्थिर अक्षर *p = IDENTIFIER_POINTER (tok->मूल्य);
	      अगर (म_भेद ("val", p) == 0)
		{
		  अगर (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      अन्यथा अगर (म_भेद ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  अगर (parens2.require_open (parser))
		    {
		      अगर (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      व्यंजक_loc = c_parser_peek_token (parser)->location;
		      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
		      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false,
						       true);
		      step = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
		      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_गाँठ;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  अन्यथा
		    अवरोध;
		}
	      अन्यथा
		अवरोध;
	      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  जारी;
		}
	      अवरोध;
	    }
	  अगर (!step)
	    step = integer_one_गाँठ;
	}
      अन्यथा
	{
	  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
	  step = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
	  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_गाँठ;
	    }
	}

    }
  अन्यथा
    step = integer_one_गाँठ;

  क्रम (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  अगर (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      अगर (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  अगर (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_जोड़ो_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_जोड़ो_before (close_loc, ")");
	    }
	  अन्यथा
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  वापस nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_nontemporal (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

अटल वृक्ष
c_parser_omp_clause_safelen (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्ष c, t;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
  t = व्यंजक.मूल्य;
  t = c_fully_fold (t, false, शून्य);
  अगर (वृक्ष_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (वृक्ष_TYPE (t))
      || वृक्ष_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_वृक्ष;
    }

  parens.skip_until_found_close (parser);
  अगर (t == NULL_वृक्ष || t == error_mark_गाँठ)
    वापस list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_व्यंजक (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

अटल वृक्ष
c_parser_omp_clause_simdlen (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्ष c, t = NULL_वृक्ष, type = NULL_वृक्ष, भाजक = NULL_वृक्ष;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अचिन्हित pos = 3;
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      काष्ठा c_type_name *ctype = c_parser_type_name (parser);
      अगर (ctype == शून्य
	  || (type = groktypename (ctype, शून्य, शून्य)) == शून्य
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && वृक्ष_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_गाँठ;
	}
      अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, false, true);
	  भाजक = व्यंजक.मूल्य;
	  भाजक = c_fully_fold (भाजक, false, शून्य);
	  अगर (वृक्ष_CODE (भाजक) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (वृक्ष_TYPE (भाजक))
	      || वृक्ष_int_cst_sgn (भाजक) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_गाँठ;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  अगर (type != error_mark_गाँठ)
    {
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);
      अगर (वृक्ष_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (वृक्ष_TYPE (t))
	  || वृक्ष_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_वृक्ष;
	}
    }

  parens.skip_until_found_close (parser);
  अगर (type == error_mark_गाँठ || t == NULL_वृक्ष || t == error_mark_गाँठ)
    वापस list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_व्यंजक (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_भाजक (c) = भाजक;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

अटल वृक्ष
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   वृक्ष list, bool depend_p)
{
  वृक्ष vec = शून्य;
  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      वापस list;
    }

  अगर (!depend_p)
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_संख्या
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  वृक्ष val = c_parser_peek_nth_token (parser, 3)->मूल्य;
	  अगर (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      वृक्ष u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      वापस u;
	    }
	}
    }



  जबतक (c_parser_अग्र_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      वृक्ष t = lookup_name (c_parser_peek_token (parser)->मूल्य);
      वृक्ष addend = शून्य;

      अगर (t == NULL_वृक्ष)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->मूल्य);
	  t = error_mark_गाँठ;
	}

      c_parser_consume_token (parser);

      bool neg = false;
      अगर (c_parser_अग्र_token_is (parser, CPP_MINUS))
	neg = true;
      अन्यथा अगर (!c_parser_अग्र_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_गाँठ;
	  neg = false;
	  जाओ add_to_vector;
	}
      c_parser_consume_token (parser);

      अगर (c_parser_अग्र_token_is_not (parser, CPP_संख्या))
	{
	  c_parser_error (parser, "expected integer");
	  वापस list;
	}

      addend = c_parser_peek_token (parser)->मूल्य;
      अगर (वृक्ष_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  वापस list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      अगर (t != error_mark_गाँठ)
	{
	  vec = वृक्ष_cons (addend, t, vec);
	  अगर (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      अगर (c_parser_अग्र_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	अवरोध;

      c_parser_consume_token (parser);
    }

  अगर (vec == NULL_वृक्ष)
    वापस list;

  वृक्ष u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  वापस u;
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

अटल वृक्ष
c_parser_omp_iterators (c_parser *parser)
{
  वृक्ष ret = NULL_वृक्ष, *last = &ret;
  c_parser_consume_token (parser);

  धकेलो_scope ();

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस error_mark_गाँठ;

  करो
    {
      वृक्ष iter_type = NULL_वृक्ष, type_व्यंजक = NULL_वृक्ष;
      अगर (c_parser_अग्र_tokens_start_typename (parser, cla_prefer_id))
	{
	  काष्ठा c_type_name *type = c_parser_type_name (parser);
	  अगर (type != शून्य)
	    iter_type = groktypename (type, &type_व्यंजक, शून्य);
	}
      अगर (iter_type == NULL_वृक्ष)
	iter_type = integer_type_गाँठ;

      location_t loc = c_parser_peek_token (parser)->location;
      अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  अवरोध;
	}

      वृक्ष id = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);

      अगर (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	अवरोध;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (eloc, व्यंजक, true, false);
      वृक्ष begin = व्यंजक.मूल्य;

      अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	अवरोध;

      eloc = c_parser_peek_token (parser)->location;
      व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (eloc, व्यंजक, true, false);
      वृक्ष end = व्यंजक.मूल्य;

      वृक्ष step = integer_one_गाँठ;
      अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	  व्यंजक = convert_lvalue_to_rvalue (eloc, व्यंजक, true, false);
	  step = व्यंजक.मूल्य;
	}

      वृक्ष iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &वृक्ष_CHAIN (*last);

      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  जारी;
	}
      अवरोध;
    }
  जबतक (1);

  parens.skip_until_found_close (parser);
  वापस ret ? ret : error_mark_गाँठ;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

अटल वृक्ष
c_parser_omp_clause_affinity (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्ष nl, iterators = NULL_वृक्ष;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      bool parse_iter = ((म_भेद ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      अगर (parse_iter)
	{
	  अचिन्हित n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      अगर (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      अगर (iterators)
		निकालो_scope ();
	      parens.skip_until_found_close (parser);
	      वापस list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  अगर (iterators)
    {
      वृक्ष block = निकालो_scope ();
      अगर (iterators != error_mark_गाँठ)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  क्रम (वृक्ष c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_वृक्ष_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  वापस nl;
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

अटल वृक्ष
c_parser_omp_clause_depend (c_parser *parser, वृक्ष list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  क्रमागत omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  क्रमागत omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  वृक्ष nl, c, iterators = NULL_वृक्ष;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  करो
    {
      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
	जाओ invalid_kind;

      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद ("iterator", p) == 0 && iterators == NULL_वृक्ष)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  जारी;
	}
      अगर (म_भेद ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      अन्यथा अगर (म_भेद ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      अन्यथा अगर (म_भेद ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      अन्यथा अगर (म_भेद ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      अन्यथा अगर (म_भेद ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      अन्यथा अगर (म_भेद ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      अन्यथा अगर (म_भेद ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      अन्यथा अगर (म_भेद ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      अन्यथा
	जाओ invalid_kind;
      अवरोध;
    }
  जबतक (1);

  c_parser_consume_token (parser);

  अगर (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      निकालो_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_वृक्ष;
    }

  अगर (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_वृक्ष;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      वापस c;
    }

  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    जाओ resync_fail;

  अगर (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, true);
  अन्यथा
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      अगर (iterators)
	{
	  वृक्ष block = निकालो_scope ();
	  अगर (iterators == error_mark_गाँठ)
	    iterators = NULL_वृक्ष;
	  अन्यथा
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      क्रम (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  अगर (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_वृक्ष_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  वापस nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  अगर (iterators)
    निकालो_scope ();
  वापस list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

अटल वृक्ष
c_parser_omp_clause_doacross (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  क्रमागत omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  वृक्ष nl;
  स्थिर अक्षर *p;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME))
    जाओ invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
  अगर (म_भेद ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  अन्यथा अगर (म_भेद ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  अन्यथा
    जाओ invalid_kind;

  c_parser_consume_token (parser);

  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    जाओ resync_fail;

  अगर (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_वृक्ष;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  अन्यथा
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, false);

  parens.skip_until_found_close (parser);
  वापस nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  वापस list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

अटल वृक्ष
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  क्रमागत omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  अचिन्हित n = 3;
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  वापस list;
	}
      c_parser_consume_token (parser);
      अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	वापस list;
      p = "";
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      अन्यथा अगर (म_भेद (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      अन्यथा अगर (म_भेद (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      अन्यथा
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  वापस list;
	}
      c_parser_consume_token (parser);
      अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	वापस list;
      अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	वापस list;
    }
  location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
  वृक्ष आकार = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
  parens.skip_until_found_close (parser);

  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (आकार)))
    {
      error_at (व्यंजक_loc, "expected integer expression");
      वापस list;
    }

  /* Attempt to statically determine when the number is negative.  */
  वृक्ष c = fold_build2_loc (व्यंजक_loc, LT_व्यंजक, boolean_type_गाँठ, आकार,
			    build_int_cst (वृक्ष_TYPE (आकार), 0));
  protected_set_व्यंजक_location (c, व्यंजक_loc);
  अगर (c == boolean_true_गाँठ)
    {
      warning_at (व्यंजक_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      आकार = integer_zero_गाँठ;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_व्यंजक (c) = आकार;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  वापस list;
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

अटल वृक्ष
c_parser_omp_clause_map (c_parser *parser, वृक्ष list, bool declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  वृक्ष nl, c;
  क्रमागत gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  पूर्णांक pos = 1;
  पूर्णांक map_kind_pos = 0;
  पूर्णांक iterator_लंबाई = 0;
  क्रम (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      अगर (tok->type != CPP_NAME)
	अवरोध;

      स्थिर अक्षर *p = IDENTIFIER_POINTER (tok->मूल्य);
      c_token *अग्र_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      अगर (म_भेद (p, "iterator") == 0 && अग्र_tok->type == CPP_OPEN_PAREN)
	{
	  अचिन्हित n = pos + 2;
	  अगर (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_लंबाई = n - pos + 1;
	      pos = n;
	      अग्र_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      अगर (अग्र_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  अवरोध;
	}

      अगर (अग्र_tok->type == CPP_COMMA)
	pos++;
      अन्यथा अगर (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  अचिन्हित पूर्णांक npos = pos + 2;
	  अगर (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  पूर्णांक always_modifier = 0;
  पूर्णांक close_modifier = 0;
  पूर्णांक present_modifier = 0;
  पूर्णांक mapper_modifier = 0;
  पूर्णांक अंक_commas = 0;
  पूर्णांक अंक_identifiers = 0;
  वृक्ष mapper_name = NULL_वृक्ष;
  वृक्ष iterators = NULL_वृक्ष;
  क्रम (पूर्णांक pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      अगर (tok->type == CPP_COMMA)
	{
	  ++अंक_commas;
	  अगर (अंक_commas > अंक_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  जारी;
	}

      स्थिर अक्षर *p = IDENTIFIER_POINTER (tok->मूल्य);
      अगर (म_भेद ("always", p) == 0)
	{
	  अगर (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      वापस list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (म_भेद ("close", p) == 0)
	{
	  अगर (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      वापस list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (म_भेद ("iterator", p) == 0)
	{
	  अगर (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      वापस list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_लंबाई - 1;
	}
      अन्यथा अगर (म_भेद ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  अगर (mparens.require_open (parser))
	    {
	      अगर (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  वापस list;
		}

	      tok = c_parser_peek_token (parser);

	      चयन (tok->type)
		{
		हाल CPP_NAME:
		  {
		    mapper_name = tok->मूल्य;
		    c_parser_consume_token (parser);
		    अगर (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  अवरोध;

		हाल CPP_KEYWORD:
		  अगर (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      अवरोध;
		    }
		  /* Fallthrough.  */

		शेष:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  वापस list;
		}

	      अगर (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  वापस list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      अन्यथा अगर (म_भेद ("present", p) == 0)
	{
	  अगर (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      वापस list;
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
	  वापस list;
	}
      ++अंक_identifiers;
      अगर (अंक_identifiers - 1 > अंक_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_जोड़ो_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      अंक_commas = अंक_identifiers - 1;
    }

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      पूर्णांक always_present_modifier = always_modifier && present_modifier;

      अगर (म_भेद ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      अन्यथा अगर (म_भेद ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      अन्यथा अगर (म_भेद ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      अन्यथा अगर (म_भेद ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      अन्यथा अगर (म_भेद ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      अन्यथा अगर (म_भेद ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      अन्यथा
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  वापस list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   true);

  वृक्ष last_new = NULL_वृक्ष;

  अगर (iterators)
    {
      वृक्ष block = निकालो_scope ();
      अगर (iterators == error_mark_गाँठ)
	iterators = NULL_वृक्ष;
      अन्यथा
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  क्रम (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  अगर (mapper_name)
    {
      वृक्ष name = build_omp_clause (निवेश_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_धकेलो_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (निवेश_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_निकालो_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_गाँठ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  वापस nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

अटल वृक्ष
c_parser_omp_clause_device (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t व्यंजक_loc;
  c_व्यंजक व्यंजक;
  वृक्ष c, t;
  bool ancestor = false;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      स्थिर अक्षर *p = IDENTIFIER_POINTER (tok->मूल्य);
      अगर (म_भेद ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  अगर ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      वापस list;
	    }
	  ancestor = true;
	}
      अन्यथा अगर (म_भेद ("device_num", p) == 0)
	;
      अन्यथा
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  वापस list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  व्यंजक_loc = c_parser_peek_token (parser)->location;
  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
  t = व्यंजक.मूल्य;
  t = c_fully_fold (t, false, शून्य);

  parens.skip_until_found_close (parser);

  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      वापस list;
    }
  अगर (ancestor && वृक्ष_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (व्यंजक_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      वापस list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  वापस list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

अटल वृक्ष
c_parser_omp_clause_dist_schedule (c_parser *parser, वृक्ष list)
{
  वृक्ष c, t = NULL_वृक्ष;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर (!c_parser_अग्र_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      वापस list;
    }

  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      t = व्यंजक.मूल्य;
      t = c_fully_fold (t, false, शून्य);
      parens.skip_until_found_close (parser);
    }
  अन्यथा
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  अगर (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  अगर (t == error_mark_गाँठ)
    वापस list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_व्यंजक (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

अटल वृक्ष
c_parser_omp_clause_proc_bind (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  क्रमागत omp_clause_proc_bind_kind kind;
  वृक्ष c;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      अन्यथा अगर (म_भेद ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      अन्यथा अगर (म_भेद ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      अन्यथा अगर (म_भेद ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      अन्यथा
	जाओ invalid_kind;
    }
  अन्यथा
    जाओ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  वापस list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

अटल वृक्ष
c_parser_omp_clause_device_type (c_parser *parser, वृक्ष list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  क्रमागत omp_clause_device_type_kind kind;
  वृक्ष c;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      अन्यथा अगर (म_भेद ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      अन्यथा अगर (म_भेद ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      अन्यथा
	जाओ invalid_kind;
    }
  अन्यथा
    जाओ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  वापस list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

अटल वृक्ष
c_parser_omp_clause_from_to (c_parser *parser, क्रमागत omp_clause_code kind,
			     वृक्ष list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  पूर्णांक pos = 1, colon_pos = 0;
  पूर्णांक iterator_लंबाई = 0;

  जबतक (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      स्थिर अक्षर *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->मूल्य);
      अगर (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  अचिन्हित पूर्णांक npos = pos + 2;
	  अगर (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      अगर (म_भेद (identifier, "iterator") == 0)
		iterator_लंबाई = npos - pos + 1;
	      pos = npos;
	    }
	}
      अगर (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      अन्यथा
	pos++;
      अगर (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  अवरोध;
	}
    }

  bool present = false, mapper_modifier = false;
  वृक्ष iterators = NULL_वृक्ष;
  वृक्ष mapper_name = NULL_वृक्ष;

  क्रम (पूर्णांक pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      अगर (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  जारी;
	}
      स्थिर अक्षर *p = IDENTIFIER_POINTER (token->मूल्य);
      अगर (म_भेद ("present", p) == 0)
	{
	  अगर (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      वापस list;
	    }
	  present = true;
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (म_भेद ("iterator", p) == 0)
	{
	  अगर (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      वापस list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_लंबाई - 1;
	}
      अन्यथा अगर (म_भेद ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  अगर (mparens.require_open (parser))
	    {
	      अगर (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  वापस list;
		}

	      token = c_parser_peek_token (parser);
	      चयन (token->type)
		{
		हाल CPP_NAME:
		  {
		    mapper_name = token->मूल्य;
		    c_parser_consume_token (parser);
		  }
		  अवरोध;
		हाल CPP_KEYWORD:
		  अगर (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      अवरोध;
		    }
		  /* FALLTHROUGH  */
		शेष:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  वापस list;
		}
	      अगर (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  वापस list;
		}
	      mapper_modifier = true;
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
	  वापस list;
	}
    }

  अगर (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  वृक्ष nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  अगर (present)
    क्रम (वृक्ष c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  अगर (iterators)
    {
      वृक्ष block = निकालो_scope ();
      अगर (iterators == error_mark_गाँठ)
	iterators = NULL_वृक्ष;
      अन्यथा
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  अगर (iterators)
    क्रम (वृक्ष c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  अगर (mapper_name)
    {
      वृक्ष last_new = NULL_वृक्ष;
      क्रम (वृक्ष c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      वृक्ष name = build_omp_clause (निवेश_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_धकेलो_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (निवेश_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_निकालो_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_गाँठ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  वापस nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_uniform (c_parser *parser, वृक्ष list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  वापस list;
}

/* OpenMP 5.1
   full */

अटल वृक्ष
c_parser_omp_clause_full (c_parser *parser, वृक्ष list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

अटल वृक्ष
c_parser_omp_clause_partial (c_parser *parser, वृक्ष list)
{
  वृक्ष अंक = NULL_वृक्ष;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      अंक = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
      parens.skip_until_found_close (parser);

      अगर (अंक == error_mark_गाँठ)
	वापस list;

      mark_exp_read (अंक);
      अंक = c_fully_fold (अंक, false, शून्य);
      HOST_WIDE_INT n;
      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (अंक))
	  || !वृक्ष_fits_shwi_p (अंक)
	  || (n = वृक्ष_to_shwi (अंक)) <= 0
	  || (पूर्णांक) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  वापस list;
	}
    }

  वृक्ष c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_व्यंजक (c) = अंक;
  OMP_CLAUSE_CHAIN (c) = list;
  वापस c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

अटल वृक्ष
c_parser_omp_clause_novariants (c_parser *parser, वृक्ष list)
{
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  वृक्ष t = convert_lvalue_to_rvalue (loc, व्यंजक, true, true).मूल्य;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, false, शून्य);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  वृक्ष c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_व्यंजक (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  वापस list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

अटल वृक्ष
c_parser_omp_clause_nocontext (c_parser *parser, वृक्ष list)
{
  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
  वृक्ष t = convert_lvalue_to_rvalue (loc, व्यंजक, true, true).मूल्य;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, false, शून्य);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  वृक्ष c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_व्यंजक (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  वापस list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

अटल वृक्ष
c_parser_omp_clause_detach (c_parser *parser, वृक्ष list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  अगर (!parens.require_open (parser))
    वापस list;

  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      वापस list;
    }

  वृक्ष t = lookup_name (c_parser_peek_token (parser)->मूल्य);
  अगर (t == NULL_वृक्ष)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->मूल्य);
      parens.skip_until_found_close (parser);
      वापस list;
    }
  c_parser_consume_token (parser);

  वृक्ष type = TYPE_MAIN_VARIANT (वृक्ष_TYPE (t));
  अगर (!INTEGRAL_TYPE_P (type)
      || वृक्ष_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      वापस list;
    }

  वृक्ष u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  वापस u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_destroy (c_parser *parser, वृक्ष list)
{
  वृक्ष nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  क्रम (वृक्ष c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    वृक्ष_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  वापस nl;
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

अटल वृक्ष
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    वापस error_mark_गाँठ;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  अगर (!c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    जबतक (true)
      {
	str += (अक्षर) GOMP_INTEROP_IFR_SEPARATOR;
	अगर (c_parser_अग्र_token_is (parser, CPP_STRING))
	  {
	    c_व्यंजक cval = c_parser_string_literal (parser, false, false);
	    अगर (cval.मूल्य == error_mark_गाँठ)
	      वापस error_mark_गाँठ;
	    अगर ((माप_प्रकार) वृक्ष_STRING_लंबाई (cval.मूल्य)
		!= म_माप (वृक्ष_STRING_POINTER (cval.मूल्य)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = true;
		वापस error_mark_गाँठ;
	      }

	    अक्षर c = omp_get_fr_id_from_name (वृक्ष_STRING_POINTER (cval.मूल्य));
	    अगर (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  वृक्ष_STRING_POINTER (cval.मूल्य));
	    str += c;
	  }
	अन्यथा
	  {
	    c_व्यंजक cval = c_parser_व्यंजक_no_commas (parser, शून्य);
	    वृक्ष मूल्य = c_fully_fold (cval.मूल्य, false, शून्य);
	    अगर (INTEGRAL_TYPE_P (वृक्ष_TYPE (मूल्य))
		&& वृक्ष_CODE (मूल्य) != INTEGER_CST)
	      मूल्य = convert_lvalue_to_rvalue (cval.get_start (), cval,
						false, true).मूल्य;
	    अगर (वृक्ष_CODE (मूल्य) != INTEGER_CST
		|| !वृक्ष_fits_shwi_p (मूल्य))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		वापस error_mark_गाँठ;
	      }
	    HOST_WIDE_INT n = वृक्ष_to_shwi (मूल्य);
	    अगर (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (अक्षर) n;
	  }
	str += (अक्षर) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    जारी;
	  }
	अगर (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  वापस error_mark_गाँठ;
	str += '\0';
	वृक्ष res = build_string (str.लंबाई (), str.तथ्य ());
	वृक्ष_TYPE (res) = build_array_type_nelts (unsigned_char_type_गाँठ,
						  str.लंबाई ());
	वापस res;
      }

  /* New format. */
  std::string str2;
  जबतक (true)
    {
      अगर (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	वापस error_mark_गाँठ;
      str += (अक्षर) GOMP_INTEROP_IFR_SEPARATOR;
      str2.सफा ();
      bool has_fr = false;
      जबतक (true)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  अगर (tok->type != CPP_NAME
	      || (म_भेद("fr", IDENTIFIER_POINTER (tok->मूल्य)) != 0
		  && म_भेद("attr", IDENTIFIER_POINTER (tok->मूल्य)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      वापस error_mark_गाँठ;
	    }
	  c_parser_consume_token (parser);
	  bool is_fr = IDENTIFIER_POINTER (tok->मूल्य)[0] == 'f';
	  अगर (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      वापस error_mark_गाँठ;
	    }
	  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    वापस error_mark_गाँठ;
	  जबतक (true)
	    {
	      अगर (c_parser_अग्र_token_is (parser, CPP_STRING))
		{
		  c_व्यंजक cval = c_parser_string_literal (parser, false, false);
		  वृक्ष मूल्य = cval.मूल्य;
		  अगर (मूल्य == error_mark_गाँठ)
		    वापस error_mark_गाँठ;
		  अगर ((माप_प्रकार) वृक्ष_STRING_लंबाई (मूल्य)
		      != म_माप (वृक्ष_STRING_POINTER (मूल्य)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = true;
		      वापस error_mark_गाँठ;
		    }
		  अगर (!is_fr)
		    {
		      अगर (!startswith (वृक्ष_STRING_POINTER (मूल्य), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = true;
			  वापस error_mark_गाँठ;
			}
		      अगर (म_अक्षर (वृक्ष_STRING_POINTER (मूल्य), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = true;
			  वापस error_mark_गाँठ;
			}
		      str2 += वृक्ष_STRING_POINTER (मूल्य);
		      str2 += '\0';
		    }
		  अन्यथा
		    {
		      अगर (*वृक्ष_STRING_POINTER (मूल्य) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  वापस error_mark_गाँठ;
			}
		      अक्षर c = omp_get_fr_id_from_name (वृक्ष_STRING_POINTER (मूल्य));
		      अगर (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    वृक्ष_STRING_POINTER (मूल्य));
		     str += c;
		     has_fr = true;
		    }
		}
	      अन्यथा अगर (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  वापस error_mark_गाँठ;
		}
	      अन्यथा
		{
		  c_व्यंजक cval = c_parser_व्यंजक_no_commas (parser, शून्य);
		  वृक्ष मूल्य = c_fully_fold (cval.मूल्य, false, शून्य);
		  अगर (INTEGRAL_TYPE_P (वृक्ष_TYPE (मूल्य))
		      && वृक्ष_CODE (मूल्य) != INTEGER_CST)
		    मूल्य = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      false, true).मूल्य;

		  अगर (वृक्ष_CODE (मूल्य) != INTEGER_CST
		      || !वृक्ष_fits_shwi_p (मूल्य))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      वापस error_mark_गाँठ;
		    }
		  HOST_WIDE_INT n = वृक्ष_to_shwi (मूल्य);
		  अगर (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (अक्षर) n;
		  has_fr = true;
		}
	      अगर (!is_fr
		  && c_parser_अग्र_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  जारी;
		}
	      अगर (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		वापस error_mark_गाँठ;
	      अवरोध;
	    }
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	    अवरोध;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  वापस error_mark_गाँठ;
	}
      str += (अक्षर) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	अवरोध;
      अगर (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	वापस error_mark_गाँठ;
    }
  c_parser_consume_token (parser);
  str += '\0';
  वृक्ष res = build_string (str.लंबाई (), str.तथ्य ());
  वृक्ष_TYPE (res) = build_array_type_nelts (unsigned_char_type_गाँठ,
						  str.लंबाई ());
  वापस res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

अटल bool
c_parser_omp_clause_init_modifiers (c_parser *parser, bool *target,
				    bool *targetsync, वृक्ष *prefer_type_वृक्ष)
{
  *target = false;
  *targetsync = false;
  *prefer_type_वृक्ष = NULL_वृक्ष;

  करो
    {
      c_token *tok = c_parser_peek_token (parser);
      अगर (tok->type != CPP_NAME)
	जाओ हार;
      स्थिर अक्षर *p = IDENTIFIER_POINTER (tok->मूल्य);
      अगर (म_भेद ("targetsync", p) == 0)
	{
	  अगर (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = true;
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (म_भेद ("target", p) == 0)
	{
	  अगर (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = true;
	  c_parser_consume_token (parser);
	}
      अन्यथा अगर (म_भेद ("prefer_type", p) == 0)
	{
	  अगर (*prefer_type_वृक्ष != NULL_वृक्ष)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_वृक्ष = c_parser_omp_modifier_prefer_type (parser);
	  अगर (*prefer_type_वृक्ष == error_mark_गाँठ)
	    वापस false;
	}
      अन्यथा
	जाओ हार;
      tok = c_parser_peek_token (parser);
      अगर (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  जारी;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      वापस true;
    }
  जबतक (true);

हार:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  वापस false;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

अटल वृक्ष
c_parser_omp_clause_init (c_parser *parser, वृक्ष list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस list;

  bool target = false;
  bool targetsync = false;
  वृक्ष prefer_type_वृक्ष = NULL_वृक्ष;

  अगर (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_वृक्ष)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      अगर (prefer_type_वृक्ष != error_mark_गाँठ)
	parens.skip_until_found_close (parser);
      वापस list;
    }

  अगर (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  वृक्ष nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					false);
  parens.skip_until_found_close (parser);

  क्रम (वृक्ष c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      वृक्ष_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      अगर (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      अगर (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      अगर (prefer_type_वृक्ष)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_वृक्ष;
    }
  वापस nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_use (c_parser *parser, वृक्ष list)
{
  वापस c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

अटल वृक्ष
c_parser_omp_clause_interop (c_parser *parser, वृक्ष list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  वृक्ष nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  क्रम (वृक्ष c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      वृक्ष_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  वापस nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

अटल वृक्ष
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   स्थिर अक्षर *where, bool finish_p = true,
			   bool target_p = false)
{
  वृक्ष clauses = शून्य;
  bool first = true;

  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      स्थिर अक्षर *c_name;
      वृक्ष पूर्व = clauses;

      अगर (!first && c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      चयन (c_kind)
	{
	हाल PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "create";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, true);
	  c_name = "default";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "device";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_तथ्य_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "host";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, false);
	  c_name = "if";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "link";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_अंक_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_अंक_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_अंक_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_अंक_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "present";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     false, clauses);
	  c_name = "reduction";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_SELF:
	  अगर ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  अन्यथा
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_तथ्य_clause (parser, c_kind, clauses);
	  c_name = "self";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_VECTOR_लंबाई:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_लंबाई,
						     clauses);
	  c_name = "vector_length";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  अवरोध;
	हाल PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  अवरोध;
	शेष:
	  c_parser_error (parser, "expected an OpenACC clause");
	  जाओ saw_error;
	}

      first = false;

      अगर (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = पूर्व;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  अगर (finish_p)
    वापस c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  वापस clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

अटल वृक्ष
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  स्थिर अक्षर *where, bool finish_p = true,
			  पूर्णांक nested = 0)
{
  वृक्ष clauses = शून्य;
  bool first = true;

  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      स्थिर अक्षर *c_name;
      वृक्ष पूर्व = clauses;

      अगर (nested && c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	अवरोध;

      अगर (!first || nested != 2)
	{
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा अगर (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      चयन (c_kind)
	{
	हाल PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, false);
	  c_name = "default";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, true);
	  c_name = "if";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     true, clauses);
	  c_name = "in_reduction";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_अंक_TASKS:
	  clauses = c_parser_omp_clause_अंक_tasks (parser, clauses);
	  c_name = "num_tasks";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_अंक_THREADS:
	  clauses = c_parser_omp_clause_अंक_threads (parser, clauses);
	  c_name = "num_threads";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     true, clauses);
	  c_name = "reduction";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     true, clauses);
	  c_name = "task_reduction";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  अगर (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = पूर्व;
	    }
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  अगर (!first)
	    जाओ clause_not_first;
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  अगर (!first)
	    जाओ clause_not_first;
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  अगर (!first)
	    जाओ clause_not_first;
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_TO:
	  अगर ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      वृक्ष nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      क्रम (वृक्ष c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  अन्यथा
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_अंक_TEAMS:
	  clauses = c_parser_omp_clause_अंक_teams (parser, clauses);
	  c_name = "num_teams";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, false);
	  c_name = "map";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  अवरोध;
	हाल PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  अवरोध;
	शेष:
	  c_parser_error (parser, "expected an OpenMP clause");
	  जाओ saw_error;
	}

      first = false;

      अगर (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = पूर्व;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  अगर (!nested)
    c_parser_skip_to_pragma_eol (parser);

  अगर (finish_p)
    {
      अगर ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	वापस c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      अगर ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	वापस c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      वापस c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  वापस clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

अटल वृक्ष
c_parser_omp_structured_block (c_parser *parser, bool *if_p)
{
  वृक्ष stmt = धकेलो_stmt_list ();
  parser->omp_attrs_forbidden_p = true;
  c_parser_statement (parser, if_p);
  वापस निकालो_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

अटल वृक्ष
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  वृक्ष stmt, clauses = NULL_वृक्ष;
  bool readonly = false;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      अगर (token->type == CPP_NAME
	  && !म_भेद (IDENTIFIER_POINTER (token->मूल्य), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = true;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_वृक्ष);
      parens.skip_until_found_close (parser);
    }

  अगर (readonly)
    क्रम (वृक्ष c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_गाँठ (OACC_CACHE);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);

  वापस stmt;
}

/* OpenACC 2.0:
   # pragma acc data oacc-data-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#घोषणा OACC_तथ्य_CLAUSE_MASK						\
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

अटल वृक्ष
c_parser_oacc_तथ्य (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_तथ्य_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_तथ्य (loc, clauses, block);

  वापस stmt;
}

/* OpenACC 2.0:
   # pragma acc declare oacc-data-clause[optseq] new-line
*/

#घोषणा OACC_DECLARE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_LINK)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRESENT))

अटल व्योम
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  वृक्ष clauses, stmt, t, decl;

  bool error = false;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  अगर (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      वापस;
    }

  क्रम (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      अगर (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = true;
	  जारी;
	}

      चयन (OMP_CLAUSE_MAP_KIND (t))
	{
	हाल GOMP_MAP_FIRSTPRIVATE_POINTER:
	हाल GOMP_MAP_ALLOC:
	हाल GOMP_MAP_TO:
	हाल GOMP_MAP_FORCE_DEVICEPTR:
	हाल GOMP_MAP_DEVICE_RESIDENT:
	  अवरोध;

	हाल GOMP_MAP_LINK:
	  अगर (!global_bindings_p ()
	      && (वृक्ष_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = true;
	      जारी;
	    }
	  अवरोध;

	शेष:
	  अगर (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = true;
	      जारी;
	    }
	  अगर (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = true;
	      जारी;
	    }
	  अन्यथा अगर (वृक्ष_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = true;
	      जारी;
	    }
	  अवरोध;
	}

      अगर (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = true;
	  जारी;
	}

      अगर (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = true;
	  जारी;
	}

      अगर (!error)
	{
	  वृक्ष id;

	  अगर (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  अन्यथा
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = वृक्ष_cons (id, NULL_वृक्ष, DECL_ATTRIBUTES (decl));

	  अगर (global_bindings_p ())
	    {
	      symtab_गाँठ *गाँठ = symtab_गाँठ::लो (decl);
	      अगर (गाँठ != शून्य)
		{
		  गाँठ->offloadable = 1;
		  अगर (ENABLE_OFFLOADING)
		    {
		      g->have_offload = true;
		      अगर (is_a <varpool_गाँठ *> (गाँठ))
			vec_safe_धकेलो (offload_vars, decl);
		    }
		}
	    }
	}
    }

  अगर (error || global_bindings_p ())
    वापस;

  stmt = make_गाँठ (OACC_DECLARE);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  वापस;
}

/* OpenACC 2.0:
   # pragma acc enter data oacc-enter-data-clause[optseq] new-line

   or

   # pragma acc exit data oacc-exit-data-clause[optseq] new-line


   LOC is the location of the #pragma token.
*/

#घोषणा OACC_ENTER_तथ्य_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#घोषणा OACC_EXIT_तथ्य_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DELETE) 		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DETACH) 		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_FINALIZE) 		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

अटल व्योम
c_parser_oacc_enter_exit_तथ्य (c_parser *parser, bool enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष clauses, stmt;
  स्थिर अक्षर *p = "";

  c_parser_consume_pragma (parser);

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      c_parser_consume_token (parser);
    }

  अगर (म_भेद (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = true;
      c_parser_skip_to_pragma_eol (parser);
      वापस;
    }

  अगर (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_तथ्य_CLAUSE_MASK,
					 "#pragma acc enter data");
  अन्यथा
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_तथ्य_CLAUSE_MASK,
					 "#pragma acc exit data");

  अगर (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_वृक्ष)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      वापस;
    }

  stmt = enter ? make_गाँठ (OACC_ENTER_तथ्य) : make_गाँठ (OACC_EXIT_तथ्य);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);
}


/* OpenACC 2.0:
   # pragma acc host_data oacc-data-clause[optseq] new-line
     structured-block
*/

#घोषणा OACC_HOST_तथ्य_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_USE_DEVICE)          \
	 | (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)                  \
	 | (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT) )

अटल वृक्ष
c_parser_oacc_host_तथ्य (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_तथ्य_CLAUSE_MASK,
				       "#pragma acc host_data", false);
  अगर (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      वापस error_mark_गाँठ;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_तथ्य (loc, clauses, block);
  वापस stmt;
}


/* OpenACC 2.0:

   # pragma acc loop oacc-loop-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#घोषणा OACC_LOOP_CLAUSE_MASK						\
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
अटल वृक्ष
c_parser_oacc_loop (location_t loc, c_parser *parser, अक्षर *p_name,
		    omp_clause_mask mask, वृक्ष *cclauses, bool *if_p)
{
  bool is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  म_जोड़ो (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  वृक्ष clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == शून्य,
					    /*target=*/is_parallel);
  अगर (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      अगर (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      अगर (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  वृक्ष block = c_begin_compound_stmt (true);
  वृक्ष stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, शून्य,
				     if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस stmt;
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

#घोषणा OACC_KERNELS_CLAUSE_MASK					\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अंक_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अंक_WORKERS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_VECTOR_लंबाई)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#घोषणा OACC_PARALLEL_CLAUSE_MASK					\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अंक_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_अंक_WORKERS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_VECTOR_लंबाई)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#घोषणा OACC_SERIAL_CLAUSE_MASK					\
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

अटल वृक्ष
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       क्रमागत pragma_kind p_kind, अक्षर *p_name, bool *if_p)
{
  omp_clause_mask mask;
  क्रमागत वृक्ष_code code;
  चयन (p_kind)
    {
    हाल PRAGMA_OACC_KERNELS:
      म_जोड़ो (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      अवरोध;
    हाल PRAGMA_OACC_PARALLEL:
      म_जोड़ो (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      अवरोध;
    हाल PRAGMA_OACC_SERIAL:
      म_जोड़ो (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      अवरोध;
    शेष:
      gcc_unreachable ();
    }

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  वृक्ष block = c_begin_omp_parallel ();
	  वृक्ष clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  वापस c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  वृक्ष clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/true,
					    /*target=*/true);

  वृक्ष block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  वापस c_finish_omp_construct (loc, code, block, clauses);
}

/* OpenACC 2.0:
   # pragma acc routine oacc-routine-clause[optseq] new-line
     function-definition

   # pragma acc routine ( name ) oacc-routine-clause[optseq] new-line
*/

#घोषणा OACC_ROUTINE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WORKER)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_VECTOR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_NOHOST) )

/* Parse an OpenACC routine directive.  For named directives, we apply
   immediately to the named function.  For unnamed ones we then parse
   a declaration or definition, which must be for a function.  */

अटल व्योम
c_parser_oacc_routine (c_parser *parser, क्रमागत pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_तथ्य तथ्य;
  तथ्य.error_seen = false;
  तथ्य.fndecl_seen = false;
  तथ्य.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      वृक्ष decl = NULL_वृक्ष;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      अगर (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->मूल्य);
	  अगर (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->मूल्य);
	  c_parser_consume_token (parser);
	}
      अन्यथा
	c_parser_error (parser, "expected function name");

      अगर (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, false);
	  वापस;
	}

      तथ्य.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      तथ्य.clauses = nreverse (तथ्य.clauses);

      अगर (वृक्ष_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  वापस;
	}

      c_finish_oacc_routine (&तथ्य, decl, false);
    }
  अन्यथा /* No optional '( name )'.  */
    {
      तथ्य.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      तथ्य.clauses = nreverse (तथ्य.clauses);

      /* Emit a helpful diagnostic if there's another pragma following this
	 one.  Also don't allow a static assertion declaration, as in the
	 following we'll just parse a *single* "declaration or function
	 definition", and the static assertion counts an one.  */
      अगर (c_parser_अग्र_token_is (parser, CPP_PRAGMA)
	  || c_parser_अग्र_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (तथ्य.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  वापस;
	}

      /* We only have to consider the pragma_external case here.  */
      अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णांक ext = disable_extension_diagnostics ();
	  करो
	    c_parser_consume_token (parser);
	  जबतक (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, true, true, true, false, true,
					 false, शून्य, शून्य, false, शून्य, &तथ्य);
	  restore_extension_diagnostics (ext);
	}
      अन्यथा
	c_parser_declaration_or_fndef (parser, true, true, true, false, true,
				       false, शून्य, शून्य, false, शून्य, &तथ्य);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

अटल व्योम
c_finish_oacc_routine (काष्ठा oacc_routine_तथ्य *तथ्य, वृक्ष fndecl,
		       bool is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  अगर (तथ्य->error_seen
      || fndecl == error_mark_गाँठ)
    वापस;

  अगर (तथ्य->fndecl_seen)
    {
      error_at (तथ्य->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      तथ्य->error_seen = true;
      वापस;
    }
  अगर (fndecl == NULL_वृक्ष || वृक्ष_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (तथ्य->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      तथ्य->error_seen = true;
      वापस;
    }

  पूर्णांक compatible
    = oacc_verify_routine_clauses (fndecl, &तथ्य->clauses, तथ्य->loc,
				   "#pragma acc routine");
  अगर (compatible < 0)
    {
      तथ्य->error_seen = true;
      वापस;
    }
  अगर (compatible > 0)
    {
    }
  अन्यथा
    {
      अगर (वृक्ष_USED (fndecl) || (!is_defn && DECL_SAVED_वृक्ष (fndecl)))
	{
	  error_at (तथ्य->loc,
		    वृक्ष_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  तथ्य->error_seen = true;
	  वापस;
	}

      /* Set the routine's level of parallelism.  */
      वृक्ष dims = oacc_build_routine_dims (तथ्य->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= वृक्ष_cons (get_identifier ("omp declare target"),
		     तथ्य->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  तथ्य->fndecl_seen = true;
}

/* OpenACC 2.0:
   # pragma acc update oacc-update-clause[optseq] new-line
*/

#घोषणा OACC_UPDATE_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_DEVICE)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_WAIT) )

अटल व्योम
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  वृक्ष clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  अगर (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_वृक्ष)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      वापस;
    }

  अगर (parser->error)
    वापस;

  वृक्ष stmt = make_गाँठ (OACC_UPDATE);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#घोषणा OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

अटल वृक्ष
c_parser_oacc_wait (location_t loc, c_parser *parser, अक्षर *p_name)
{
  वृक्ष clauses, list = NULL_वृक्ष, stmt = NULL_वृक्ष;

  अगर (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  म_नकल (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  वापस stmt;
}

काष्ठा c_omp_loc_वृक्ष
{
  location_t loc;
  वृक्ष var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
अटल वृक्ष
c_check_omp_allocate_allocator_r (वृक्ष *tp, पूर्णांक *, व्योम *तथ्य)
{
  वृक्ष var = ((काष्ठा c_omp_loc_वृक्ष *) तथ्य)->var;
  location_t loc = ((काष्ठा c_omp_loc_वृक्ष *) तथ्य)->loc;
  अगर (वृक्ष_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      अगर (linemap_location_before_p (पंक्ति_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  वापस *tp;
	}
      अन्यथा
	{
	  gcc_assert (cur_stmt_list
		      && वृक्ष_CODE (cur_stmt_list) == STATEMENT_LIST);

	  वृक्ष_stmt_iterator l = tsi_last (cur_stmt_list);
	  जबतक (!tsi_end_p (l))
	    {
	      अगर (linemap_location_before_p (पंक्ति_table, व्यंजक_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  अवरोध;
	      अगर (वृक्ष_CODE (*l) == MODIFY_व्यंजक
		  && वृक्ष_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (व्यंजक_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  वापस *tp;
		}
	      --l;
	    }
	}
    }
  वापस NULL_वृक्ष;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

अटल व्योम
c_parser_omp_allocate (c_parser *parser)
{
  वृक्ष alignment = NULL_वृक्ष;
  वृक्ष allocator = NULL_वृक्ष;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  वृक्ष nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_वृक्ष);
  करो
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
	अवरोध;
      matching_parens parens;
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      c_parser_consume_token (parser);
      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
      अगर (म_भेद ("align", p) != 0 && म_भेद ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  अवरोध;
	}
      अगर (!parens.require_open (parser))
	अवरोध;

      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, false, true);
      व्यंजक_loc = c_parser_peek_token (parser)->location;
      अगर (व्यंजक.मूल्य == error_mark_गाँठ)
	;
      अन्यथा अगर (p[2] == 'i' && alignment)
	{
	  error_at (व्यंजक_loc, "too many %qs clauses", "align");
	  अवरोध;
	}
      अन्यथा अगर (p[2] == 'i')
	{
	  alignment = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
	  अगर (वृक्ष_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (वृक्ष_TYPE (alignment))
	      || वृक्ष_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (व्यंजक_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_वृक्ष;
	    }
	}
      अन्यथा अगर (allocator)
	{
	  error_at (व्यंजक_loc, "too many %qs clauses", "allocator");
	  अवरोध;
	}
      अन्यथा
	{
	  allocator = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
	  allocator_loc = व्यंजक_loc;
	  वृक्ष orig_type
	    = व्यंजक.original_type ? व्यंजक.original_type : वृक्ष_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (allocator))
	      || वृक्ष_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (व्यंजक_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			वृक्ष_TYPE (allocator));
	      allocator = NULL_वृक्ष;
	    }
	}
      parens.skip_until_found_close (parser);
    } जबतक (true);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  क्रम (वृक्ष c = nl; c != NULL_वृक्ष; c = OMP_CLAUSE_CHAIN (c))
    {
      वृक्ष var = OMP_CLAUSE_DECL (c);
      अगर (वृक्ष_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  जारी;
	}
      अगर (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  जारी;
	}
      अगर (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  जारी;
	}
      अगर (वृक्ष_STATIC (var))
	{
	  अगर (allocator == NULL_वृक्ष && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      जारी;
	    }
	  अन्यथा अगर (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  अन्यथा अगर (allocator
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
      अगर (allocator)
	{
	  काष्ठा c_omp_loc_वृक्ष तथ्य
	    = {व्यंजक_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_वृक्ष (&allocator, c_check_omp_allocate_allocator_r, &तथ्य, शून्य);
	}
      DECL_ATTRIBUTES (var) = वृक्ष_cons (get_identifier ("omp allocate"),
					 build_वृक्ष_list (allocator, alignment),
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

अटल व्योम
c_parser_omp_atomic (location_t loc, c_parser *parser, bool openacc)
{
  वृक्ष lhs = NULL_वृक्ष, rhs = NULL_वृक्ष, v = NULL_वृक्ष, r = NULL_वृक्ष;
  वृक्ष lhs1 = NULL_वृक्ष, rhs1 = NULL_वृक्ष;
  वृक्ष stmt, orig_lhs, unfolded_lhs = NULL_वृक्ष, unfolded_lhs1 = NULL_वृक्ष;
  क्रमागत वृक्ष_code code = ERROR_MARK, opcode = NOP_व्यंजक;
  क्रमागत omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  काष्ठा c_व्यंजक व्यंजक;
  location_t eloc;
  bool structured_block = false;
  bool swapped = false;
  bool non_lvalue_p;
  वृक्ष clauses = NULL_वृक्ष;
  bool capture = false;
  bool compare = false;
  bool weak = false;
  क्रमागत omp_memory_order हार = OMP_MEMORY_ORDER_UNSPECIFIED;
  bool no_semicolon = false;
  bool extra_scope = false;

  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  स्थिर अक्षर *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  क्रमागत वृक्ष_code new_code = ERROR_MARK;
	  क्रमागत omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  bool new_capture = false;
	  bool new_compare = false;
	  bool new_weak = false;
	  क्रमागत omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  अगर (!म_भेद (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  अन्यथा अगर (!म_भेद (p, "write"))
	    new_code = NOP_व्यंजक;
	  अन्यथा अगर (!म_भेद (p, "update"))
	    new_code = OMP_ATOMIC;
	  अन्यथा अगर (openacc && !म_भेद (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  अन्यथा अगर (openacc)
	    {
	      p = शून्य;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  अन्यथा अगर (!म_भेद (p, "capture"))
	    new_capture = true;
	  अन्यथा अगर (!म_भेद (p, "compare"))
	    new_compare = true;
	  अन्यथा अगर (!म_भेद (p, "weak"))
	    new_weak = true;
	  अन्यथा अगर (!म_भेद (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      अगर (!parens.require_open (parser))
		जारी;

	      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		{
		  स्थिर अक्षर *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

		  अगर (!म_भेद (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  अन्यथा अगर (!म_भेद (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  अन्यथा अगर (!म_भेद (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      अगर (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  अगर (हार != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  अन्यथा
		    हार = new_fail;
		}
	      अन्यथा
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      जारी;
	    }
	  अन्यथा अगर (!म_भेद (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  अन्यथा अगर (!म_भेद (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  अन्यथा अगर (!म_भेद (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  अन्यथा अगर (!म_भेद (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  अन्यथा अगर (!म_भेद (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  अन्यथा अगर (!म_भेद (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      जारी;
	    }
	  अन्यथा
	    {
	      p = शून्य;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  अगर (p)
	    {
	      अगर (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  अगर (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  अन्यथा अगर (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  अन्यथा
		    code = new_code;
		}
	      अन्यथा अगर (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  अगर (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  अन्यथा
		    memory_order = new_memory_order;
		}
	      अन्यथा अगर (new_capture)
		{
		  अगर (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  अन्यथा
		    capture = true;
		}
	      अन्यथा अगर (new_compare)
		{
		  अगर (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  अन्यथा
		    compare = true;
		}
	      अन्यथा अगर (new_weak)
		{
		  अगर (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  अन्यथा
		    weak = true;
		}
	      c_parser_consume_token (parser);
	      जारी;
	    }
	}
      अवरोध;
    }
  c_parser_skip_to_pragma_eol (parser);

  अगर (code == ERROR_MARK)
    code = OMP_ATOMIC;
  अगर (capture)
    {
      अगर (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      अन्यथा
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  अगर (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = false;
    }
  अगर (हार != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      हार = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  अगर (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = false;
    }
  अगर (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  अन्यथा अगर (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (क्रमागत omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      चयन ((क्रमागत omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	हाल OMP_MEMORY_ORDER_UNSPECIFIED:
	हाल OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  अवरोध;
	हाल OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  अवरोध;
	हाल OMP_MEMORY_ORDER_ACQUIRE:
	  अगर (code == NOP_व्यंजक)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  अन्यथा
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  अवरोध;
	हाल OMP_MEMORY_ORDER_RELEASE:
	  अगर (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  अन्यथा
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  अवरोध;
	हाल OMP_MEMORY_ORDER_ACQ_REL:
	  चयन (code)
	    {
	    हाल OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      अवरोध;
	    हाल NOP_व्यंजक: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      अवरोध;
	    शेष:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      अवरोध;
	    }
	  अवरोध;
	शेष:
	  gcc_unreachable ();
	}
    }
  अन्यथा
    चयन (code)
      {
      हाल OMP_ATOMIC_READ:
	अगर (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	अन्यथा अगर (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	अवरोध;
      हाल NOP_व्यंजक: /* atomic write */
	अगर (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	अन्यथा अगर (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	अवरोध;
      शेष:
	अवरोध;
      }
  अगर (हार != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (क्रमागत omp_memory_order) (memory_order
				 | (हार << OMP_FAIL_MEMORY_ORDER_SHIFT));

  चयन (code)
    {
    हाल OMP_ATOMIC_READ:
    हाल NOP_व्यंजक: /* atomic write */
      v = c_parser_cast_expression (parser, शून्य).मूल्य;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, false, शून्य, true);
      अगर (v == error_mark_गाँठ)
	जाओ saw_error;
      अगर (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      अगर (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	जाओ saw_error;
      अगर (code == NOP_व्यंजक)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  व्यंजक = c_parser_expression (parser);
	  व्यंजक = default_function_array_read_conversion (eloc, व्यंजक);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_वृक्ष;
	  rhs = c_fully_fold (व्यंजक.मूल्य, false, शून्य);
	  अगर (rhs == error_mark_गाँठ)
	    जाओ saw_error;
	}
      अन्यथा
	{
	  lhs = c_parser_cast_expression (parser, शून्य).मूल्य;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, false, शून्य, true);
	  अगर (lhs == error_mark_गाँठ)
	    जाओ saw_error;
	  अगर (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      जाओ done;
    हाल OMP_ATOMIC_CAPTURE_NEW:
      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = true;
	}
      अन्यथा अगर (compare
	       && c_parser_अग्र_token_is_keyword (parser, RID_IF))
	अवरोध;
      अन्यथा
	{
	  v = c_parser_cast_expression (parser, शून्य).मूल्य;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, false, शून्य, true);
	  अगर (v == error_mark_गाँठ)
	    जाओ saw_error;
	  अगर (non_lvalue_p)
	    v = non_lvalue (v);
	  अगर (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    जाओ saw_error;
	  अगर (compare && c_parser_अग्र_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      जाओ saw_error;
	    }
	}
      अवरोध;
    शेष:
      अवरोध;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  अगर (compare && c_parser_अग्र_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      अगर (!parens.require_open (parser))
	जाओ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_व्यंजक cmp_व्यंजक;
      अगर (r)
	{
	  cmp_व्यंजक = c_parser_cast_expression (parser, शून्य);
	  cmp_व्यंजक = default_function_array_conversion (eloc, cmp_व्यंजक);
	}
      अन्यथा
	cmp_व्यंजक = c_parser_द्विआधारी_expression (parser, शून्य, void_list_गाँठ);
      parens.skip_until_found_close (parser);
      अगर (cmp_व्यंजक.मूल्य == error_mark_गाँठ)
	जाओ saw_error;
      अगर (r)
	{
	  अगर (!c_वृक्ष_equal (cmp_व्यंजक.मूल्य, unfolded_lhs))
	    जाओ bad_if;
	  cmp_व्यंजक.मूल्य = rhs1;
	  rhs1 = NULL_वृक्ष;
	  gcc_assert (वृक्ष_CODE (cmp_व्यंजक.मूल्य) == EQ_व्यंजक);
	}
      अगर (वृक्ष_CODE (cmp_व्यंजक.मूल्य) == EQ_व्यंजक)
	;
      अन्यथा अगर (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (व्यंजक_LOC_OR_LOC (cmp_व्यंजक.मूल्य, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  जाओ saw_error;
	}
      अन्यथा अगर (वृक्ष_CODE (cmp_व्यंजक.मूल्य) != GT_व्यंजक
	       && वृक्ष_CODE (cmp_व्यंजक.मूल्य) != LT_व्यंजक)
	{
	  error_at (व्यंजक_LOC_OR_LOC (cmp_व्यंजक.मूल्य, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  जाओ saw_error;
	}
      अगर (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	जाओ saw_error;

      extra_scope = true;
      eloc = c_parser_peek_token (parser)->location;
      व्यंजक = c_parser_cast_expression (parser, शून्य);
      lhs = व्यंजक.मूल्य;
      व्यंजक = default_function_array_conversion (eloc, व्यंजक);
      unfolded_lhs = व्यंजक.मूल्य;
      lhs = c_fully_fold (lhs, false, शून्य, true);
      orig_lhs = lhs;
      अगर (lhs == error_mark_गाँठ)
	जाओ saw_error;
      अगर (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      अगर (!c_parser_अग्र_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  जाओ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
      rhs1 = व्यंजक.मूल्य;

      अगर (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	जाओ saw_error;

      अगर (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	जाओ saw_error;

      extra_scope = false;
      no_semicolon = true;

      अगर (c_वृक्ष_equal (वृक्ष_OPERAND (cmp_व्यंजक.मूल्य, 0), unfolded_lhs))
	{
	  अगर (वृक्ष_CODE (cmp_व्यंजक.मूल्य) == EQ_व्यंजक)
	    {
	      opcode = COND_व्यंजक;
	      rhs = c_fully_fold (वृक्ष_OPERAND (cmp_व्यंजक.मूल्य, 1),
				  false, शून्य, true);
	      rhs1 = c_fully_fold (rhs1, false, शून्य, true);
	    }
	  अन्यथा अगर (c_वृक्ष_equal (वृक्ष_OPERAND (cmp_व्यंजक.मूल्य, 1), rhs1))
	    {
	      opcode = (वृक्ष_CODE (cmp_व्यंजक.मूल्य) == GT_व्यंजक
			? MIN_व्यंजक : MAX_व्यंजक);
	      rhs = c_fully_fold (rhs1, false, शून्य, true);
	      rhs1 = c_fully_fold (वृक्ष_OPERAND (cmp_व्यंजक.मूल्य, 0),
				   false, शून्य, true);
	    }
	  अन्यथा
	    जाओ bad_if;
	}
      अन्यथा अगर (वृक्ष_CODE (cmp_व्यंजक.मूल्य) == EQ_व्यंजक)
	जाओ bad_if;
      अन्यथा अगर (c_वृक्ष_equal (वृक्ष_OPERAND (cmp_व्यंजक.मूल्य, 1), unfolded_lhs)
	       && c_वृक्ष_equal (वृक्ष_OPERAND (cmp_व्यंजक.मूल्य, 0), rhs1))
	{
	  opcode = (वृक्ष_CODE (cmp_व्यंजक.मूल्य) == GT_व्यंजक
		    ? MAX_व्यंजक : MIN_व्यंजक);
	  rhs = c_fully_fold (rhs1, false, शून्य, true);
	  rhs1 = c_fully_fold (वृक्ष_OPERAND (cmp_व्यंजक.मूल्य, 1),
			       false, शून्य, true);
	}
      अन्यथा
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  जाओ saw_error;
	}

      अगर (c_parser_अग्र_token_is_keyword (parser, RID_ELSE))
	{
	  अगर (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_वृक्ष)
	      || वृक्ष_CODE (cmp_व्यंजक.मूल्य) != EQ_व्यंजक)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      जाओ saw_error;
	    }

	  c_parser_consume_token (parser);

	  अगर (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    जाओ saw_error;

	  extra_scope = true;
	  v = c_parser_cast_expression (parser, शून्य).मूल्य;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, false, शून्य, true);
	  अगर (v == error_mark_गाँठ)
	    जाओ saw_error;
	  अगर (non_lvalue_p)
	    v = non_lvalue (v);
	  अगर (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    जाओ saw_error;

	  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);

	  अगर (!c_वृक्ष_equal (व्यंजक.मूल्य, unfolded_lhs))
	    जाओ bad_if;

	  अगर (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    जाओ saw_error;

	  अगर (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    जाओ saw_error;

	  extra_scope = false;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  अगर (r == NULL_वृक्ष)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_गाँठ;
	}
      अन्यथा अगर (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  जाओ saw_error;
	}
      अन्यथा अगर (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_वृक्ष
	       && v == NULL_वृक्ष)
	code = OMP_ATOMIC;
      जाओ stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  व्यंजक = c_parser_cast_expression (parser, शून्य);
  lhs = व्यंजक.मूल्य;
  व्यंजक = default_function_array_conversion (eloc, व्यंजक);
  unfolded_lhs = व्यंजक.मूल्य;
  lhs = c_fully_fold (lhs, false, शून्य, true);
  orig_lhs = lhs;
  चयन (वृक्ष_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    हाल ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      अगर (extra_scope && c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      अगर (structured_block)
	{
	  अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  अन्यथा अगर (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      वापस;

    हाल POSTINCREMENT_व्यंजक:
      अगर (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    हाल PREINCREMENT_व्यंजक:
      lhs = वृक्ष_OPERAND (lhs, 0);
      unfolded_lhs = NULL_वृक्ष;
      opcode = PLUS_व्यंजक;
      rhs = integer_one_गाँठ;
      अगर (compare)
	जाओ invalid_compare;
      अवरोध;

    हाल POSTDECREMENT_व्यंजक:
      अगर (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    हाल PREDECREMENT_व्यंजक:
      lhs = वृक्ष_OPERAND (lhs, 0);
      unfolded_lhs = NULL_वृक्ष;
      opcode = MINUS_व्यंजक;
      rhs = integer_one_गाँठ;
      अगर (compare)
	जाओ invalid_compare;
      अवरोध;

    हाल COMPOUND_व्यंजक:
      अगर (वृक्ष_CODE (वृक्ष_OPERAND (lhs, 0)) == SAVE_व्यंजक
	  && वृक्ष_CODE (वृक्ष_OPERAND (lhs, 1)) == COMPOUND_व्यंजक
	  && वृक्ष_CODE (वृक्ष_OPERAND (वृक्ष_OPERAND (lhs, 1), 0)) == MODIFY_व्यंजक
	  && वृक्ष_OPERAND (वृक्ष_OPERAND (lhs, 1), 1) == वृक्ष_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (वृक्ष_TYPE (वृक्ष_OPERAND (वृक्ष_OPERAND
					      (वृक्ष_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = वृक्ष_OPERAND (वृक्ष_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    हाल MODIFY_व्यंजक:
      अगर (वृक्ष_CODE (lhs) == MODIFY_व्यंजक
	  && C_BOOLEAN_TYPE_P (वृक्ष_TYPE (वृक्ष_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  अगर (integer_onep (वृक्ष_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = वृक्ष_OPERAND (lhs, 1);
	      lhs = वृक्ष_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_वृक्ष;
	      opcode = NOP_व्यंजक;
	      अगर (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && वृक्ष_CODE (orig_lhs) == COMPOUND_व्यंजक)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      अगर (compare)
		जाओ invalid_compare;
	      अवरोध;
	    }
	  अगर (वृक्ष_CODE (वृक्ष_OPERAND (lhs, 1)) == TRUTH_NOT_व्यंजक
	      && वृक्ष_OPERAND (lhs, 0)
		 == वृक्ष_OPERAND (वृक्ष_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = वृक्ष_OPERAND (lhs, 1);
	      lhs = वृक्ष_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_वृक्ष;
	      opcode = NOP_व्यंजक;
	      अगर (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && वृक्ष_CODE (orig_lhs) == COMPOUND_व्यंजक)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      अगर (compare)
		जाओ invalid_compare;
	      अवरोध;
	    }
	}
      /* FALLTHRU */
    शेष:
      अगर (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      अगर (compare && !c_parser_अग्र_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  जाओ saw_error;
	}
      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_MULT_EQ:
	  opcode = MULT_व्यंजक;
	  अवरोध;
	हाल CPP_DIV_EQ:
	  opcode = TRUNC_DIV_व्यंजक;
	  अवरोध;
	हाल CPP_PLUS_EQ:
	  opcode = PLUS_व्यंजक;
	  अवरोध;
	हाल CPP_MINUS_EQ:
	  opcode = MINUS_व्यंजक;
	  अवरोध;
	हाल CPP_LSHIFT_EQ:
	  opcode = LSHIFT_व्यंजक;
	  अवरोध;
	हाल CPP_RSHIFT_EQ:
	  opcode = RSHIFT_व्यंजक;
	  अवरोध;
	हाल CPP_AND_EQ:
	  opcode = BIT_AND_व्यंजक;
	  अवरोध;
	हाल CPP_OR_EQ:
	  opcode = BIT_IOR_व्यंजक;
	  अवरोध;
	हाल CPP_XOR_EQ:
	  opcode = BIT_XOR_व्यंजक;
	  अवरोध;
	हाल CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य, unfolded_lhs);
	  rhs1 = व्यंजक.मूल्य;
	  चयन (वृक्ष_CODE (rhs1))
	    {
	    हाल MULT_व्यंजक:
	    हाल TRUNC_DIV_व्यंजक:
	    हाल RDIV_व्यंजक:
	    हाल PLUS_व्यंजक:
	    हाल MINUS_व्यंजक:
	    हाल LSHIFT_व्यंजक:
	    हाल RSHIFT_व्यंजक:
	    हाल BIT_AND_व्यंजक:
	    हाल BIT_IOR_व्यंजक:
	    हाल BIT_XOR_व्यंजक:
	      अगर (compare)
		अवरोध;
	      अगर (c_वृक्ष_equal (वृक्ष_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = वृक्ष_CODE (rhs1);
		  rhs = c_fully_fold (वृक्ष_OPERAND (rhs1, 1), false, शून्य,
				      true);
		  rhs1 = c_fully_fold (वृक्ष_OPERAND (rhs1, 0), false, शून्य,
				       true);
		  जाओ stmt_done;
		}
	      अगर (c_वृक्ष_equal (वृक्ष_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = वृक्ष_CODE (rhs1);
		  rhs = c_fully_fold (वृक्ष_OPERAND (rhs1, 0), false, शून्य,
				      true);
		  rhs1 = c_fully_fold (वृक्ष_OPERAND (rhs1, 1), false, शून्य,
				       true);
		  swapped = !commutative_वृक्ष_code (opcode);
		  जाओ stmt_done;
		}
	      अवरोध;
	    हाल COND_व्यंजक:
	      अगर (!compare)
		अवरोध;
	      अगर (वृक्ष_CODE (वृक्ष_OPERAND (rhs1, 0)) != GT_व्यंजक
		  && वृक्ष_CODE (वृक्ष_OPERAND (rhs1, 0)) != LT_व्यंजक
		  && वृक्ष_CODE (वृक्ष_OPERAND (rhs1, 0)) != EQ_व्यंजक)
		अवरोध;
	      अगर (!वृक्ष_OPERAND (rhs1, 1))
		अवरोध;
	      अगर (!c_वृक्ष_equal (वृक्ष_OPERAND (rhs1, 2), unfolded_lhs))
		अवरोध;
	      अगर (c_वृक्ष_equal (वृक्ष_OPERAND (वृक्ष_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  अगर (वृक्ष_CODE (वृक्ष_OPERAND (rhs1, 0)) == EQ_व्यंजक)
		    {
		      opcode = COND_व्यंजक;
		      rhs = c_fully_fold (वृक्ष_OPERAND (वृक्ष_OPERAND (rhs1,
								      0), 1),
					  false, शून्य, true);
		      rhs1 = c_fully_fold (वृक्ष_OPERAND (rhs1, 1), false,
					   शून्य, true);
		      जाओ stmt_done;
		    }
		  अगर (c_वृक्ष_equal (वृक्ष_OPERAND (वृक्ष_OPERAND (rhs1, 0), 1),
				    वृक्ष_OPERAND (rhs1, 1)))
		    {
		      opcode = (वृक्ष_CODE (वृक्ष_OPERAND (rhs1, 0)) == GT_व्यंजक
				? MIN_व्यंजक : MAX_व्यंजक);
		      rhs = c_fully_fold (वृक्ष_OPERAND (rhs1, 1), false, शून्य,
					  true);
		      rhs1 = c_fully_fold (वृक्ष_OPERAND (वृक्ष_OPERAND (rhs1,
								       0), 0),
					   false, शून्य, true);
		      जाओ stmt_done;
		    }
		}
	      अन्यथा अगर (वृक्ष_CODE (वृक्ष_OPERAND (rhs1, 0)) == EQ_व्यंजक)
		अवरोध;
	      अन्यथा अगर (c_वृक्ष_equal (वृक्ष_OPERAND (वृक्ष_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  अगर (c_वृक्ष_equal (वृक्ष_OPERAND (वृक्ष_OPERAND (rhs1, 0), 0),
				    वृक्ष_OPERAND (rhs1, 1)))
		    {
		      opcode = (वृक्ष_CODE (वृक्ष_OPERAND (rhs1, 0)) == GT_व्यंजक
				? MAX_व्यंजक : MIN_व्यंजक);
		      rhs = c_fully_fold (वृक्ष_OPERAND (rhs1, 1), false, शून्य,
					  true);
		      rhs1 = c_fully_fold (वृक्ष_OPERAND (वृक्ष_OPERAND (rhs1,
								       0), 1),
					   false, शून्य, true);
		      जाओ stmt_done;
		    }
		}
	      अवरोध;
	    हाल EQ_व्यंजक:
	      अगर (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		अवरोध;
	      अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_वृक्ष;
		  c_parser_consume_token (parser);
		  जाओ restart;
		}
	      अवरोध;
	    हाल ERROR_MARK:
	      जाओ saw_error;
	    शेष:
	      अवरोध;
	    }
	  अगर (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      अगर (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_वृक्ष;
		  व्यंजक = default_function_array_read_conversion (eloc, व्यंजक);
		  unfolded_lhs1 = व्यंजक.मूल्य;
		  lhs1 = c_fully_fold (unfolded_lhs1, false, शून्य, true);
		  rhs1 = NULL_वृक्ष;
		  c_parser_consume_token (parser);
		  जाओ restart;
		}
	      अगर (structured_block && !compare)
		{
		  opcode = NOP_व्यंजक;
		  व्यंजक = default_function_array_read_conversion (eloc, व्यंजक);
		  rhs = c_fully_fold (व्यंजक.मूल्य, false, शून्य, true);
		  rhs1 = NULL_वृक्ष;
		  जाओ stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  जाओ saw_error;
	शेष:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  जाओ saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      व्यंजक = c_parser_expression (parser);
      व्यंजक = default_function_array_read_conversion (eloc, व्यंजक);
      rhs = व्यंजक.मूल्य;
      rhs = c_fully_fold (rhs, false, शून्य, true);
      अवरोध;
    }
stmt_done:
  अगर (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_वृक्ष)
    {
      अगर (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	जाओ saw_error;
      no_semicolon = false;
      v = c_parser_cast_expression (parser, शून्य).मूल्य;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, false, शून्य, true);
      अगर (v == error_mark_गाँठ)
	जाओ saw_error;
      अगर (non_lvalue_p)
	v = non_lvalue (v);
      अगर (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	जाओ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      व्यंजक = c_parser_cast_expression (parser, शून्य);
      lhs1 = व्यंजक.मूल्य;
      व्यंजक = default_function_array_read_conversion (eloc, व्यंजक);
      unfolded_lhs1 = व्यंजक.मूल्य;
      lhs1 = c_fully_fold (lhs1, false, शून्य, true);
      अगर (lhs1 == error_mark_गाँठ)
	जाओ saw_error;
      अगर (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  अगर (structured_block)
    {
      अगर (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  अगर (weak && opcode != COND_व्यंजक)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = false;
    }
  अगर (unfolded_lhs && unfolded_lhs1
      && !c_वृक्ष_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_गाँठ;
    }
  अन्यथा
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  अगर (stmt != error_mark_गाँठ)
    add_stmt (stmt);

  अगर (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

अटल व्योम
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

#घोषणा OMP_CRITICAL_CLAUSE_MASK		\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_HINT) )

अटल वृक्ष
c_parser_omp_critical (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष stmt, name = NULL_वृक्ष, clauses = NULL_वृक्ष;

  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->मूल्य;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      अन्यथा
	c_parser_error (parser, "expected identifier");

      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  वापस c_finish_omp_critical (loc, stmt, name, clauses);
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

अटल व्योम
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  अगर (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      वापस;
    }

  वृक्ष depobj = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
  अगर (depobj != error_mark_गाँठ)
    {
      अगर (!lvalue_p (depobj))
	{
	  error_at (व्यंजक_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_गाँठ;
	}
      अन्यथा
	{
	  वृक्ष addr = build_unary_op (व्यंजक_LOC_OR_LOC (depobj, loc), ADDR_व्यंजक,
				      depobj, false);
	  अगर (addr == error_mark_गाँठ)
	    depobj = error_mark_गाँठ;
	  अन्यथा
	    depobj = build_indirect_ref (व्यंजक_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  वृक्ष clause = NULL_वृक्ष;
  क्रमागत omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      c_parser_consume_token (parser);
      अगर (!म_भेद ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_वृक्ष, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  अगर (!clause)
	    clause = error_mark_गाँठ;
	}
      अन्यथा अगर (!म_भेद ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      वृक्ष destobj = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
	      अगर (!lvalue_p (destobj))
		error_at (व्यंजक_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      अन्यथा अगर (depobj != error_mark_गाँठ
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (व्यंजक_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      अन्यथा अगर (!म_भेद ("update", p))
	{
	  matching_parens c_parens;
	  अगर (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		{
		  स्थिर अक्षर *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

		  c_parser_consume_token (parser);
		  अगर (!म_भेद ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  अन्यथा अगर (!म_भेद ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  अन्यथा अगर (!म_भेद ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  अन्यथा अगर (!म_भेद ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  अन्यथा अगर (!म_भेद ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      अगर (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_गाँठ;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  अन्यथा
	    clause = error_mark_गाँठ;
	}
    }
  अगर (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_गाँठ;
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

अटल व्योम
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  क्रमागत memmodel mo = MEMMODEL_LAST;
  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      अगर (!म_भेद (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      अन्यथा अगर (!म_भेद (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      अन्यथा अगर (!म_भेद (p, "release"))
	mo = MEMMODEL_RELEASE;
      अन्यथा अगर (!म_भेद (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      अन्यथा
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      अगर (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, शून्य);
    }
  अन्यथा अगर (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

अटल bool
c_parser_omp_section_scan (c_parser *parser, स्थिर अक्षर *directive,
			   bool tentative)
{
  अगर (!c_parser_nth_token_starts_std_attributes (parser, 1))
    वापस false;
  अचिन्हित पूर्णांक n = 3;
  अगर (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    वापस false;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  अगर (token->type != CPP_CLOSE_SQUARE)
    वापस false;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  अगर (token->type != CPP_CLOSE_SQUARE)
    वापस false;
  अगर (n < 9)
    वापस false;
  अगर (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      वृक्ष first = c_parser_peek_nth_token_raw (parser, 3)->मूल्य;
      वृक्ष second = c_parser_peek_nth_token_raw (parser, 5)->मूल्य;
      अगर (म_भेद (IDENTIFIER_POINTER (first), "directive")
	  && म_भेद (IDENTIFIER_POINTER (first), "__directive__"))
	वापस false;
      अगर (म_भेद (IDENTIFIER_POINTER (second), directive))
	वापस false;
    }
  अगर (tentative)
    वापस true;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t मध्य_loc = UNKNOWN_LOCATION;
  वृक्ष std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  bool seen = false;
  पूर्णांक cnt = 0;
  क्रम (वृक्ष attr = std_attrs; attr; attr = वृक्ष_CHAIN (attr))
    अगर (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	क्रम (वृक्ष a = वृक्ष_मूल्य (attr); a; a = वृक्ष_CHAIN (a))
	  {
	    वृक्ष d = वृक्ष_मूल्य (a);
	    gcc_assert (वृक्ष_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    अगर (first->type == CPP_NAME
		&& म_भेद (IDENTIFIER_POINTER (first->मूल्य),
			   directive) == 0)
	      {
		seen = true;
		अगर (मध्य_loc == UNKNOWN_LOCATION)
		  मध्य_loc = first->location;
	      }
	  }
      }
  अगर (!seen)
    वापस false;
  अगर (cnt != 1 || वृक्ष_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, मध्य_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      वापस false;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, शून्य);
  वापस true;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

अटल वृक्ष
c_parser_omp_structured_block_sequence (c_parser *parser,
					क्रमागत pragma_kind kind)
{
  वृक्ष stmt = धकेलो_stmt_list ();
  c_parser_statement (parser, शून्य);
  करो
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	अवरोध;
      अगर (c_parser_अग्र_token_is (parser, CPP_EOF))
	अवरोध;

      अगर (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	अवरोध;

      अगर (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", false))
	अवरोध;

      c_parser_statement (parser, शून्य);
    }
  जबतक (1);
  वापस निकालो_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

अटल व्योम
c_parser_omp_scan_loop_body (c_parser *parser, bool open_brace_parsed)
{
  वृक्ष substmt;
  location_t loc;
  वृक्ष clauses = NULL_वृक्ष;
  bool found_scan = false;

  loc = c_parser_peek_token (parser)->location;
  अगर (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = false;
      वापस;
    }

  अगर (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  अन्यथा
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_गाँठ, substmt, NULL_वृक्ष);
  SET_व्यंजक_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  अगर (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      क्रमागत omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = true;

      c_parser_consume_pragma (parser);

      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  स्थिर अक्षर *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	  अगर (म_भेद (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  अन्यथा अगर (म_भेद (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      अगर (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_वृक्ष);
	}
      अन्यथा
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  अन्यथा
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  अगर (!c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  अन्यथा
    {
      अगर (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_गाँठ, substmt, clauses);
  SET_व्यंजक_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
अटल bool
c_parser_omp_अग्र_tokens_can_be_canon_loop (c_parser *parser,
					    क्रमागत वृक्ष_code code,
					    bool error_p)
{
  अगर (code == OACC_LOOP)
    {
      अगर (c_parser_अग्र_token_is_keyword (parser, RID_FOR))
	वापस true;
      अगर (error_p)
	c_parser_error (parser, "for statement expected");
    }
  अन्यथा
    {
      अगर (c_parser_अग्र_token_is_keyword (parser, RID_FOR))
	वापस true;

      अगर (c_parser_अग्र_token_is (parser, CPP_PRAGMA))
	चयन (c_parser_peek_token (parser)->pragma_kind)
	  {
	  हाल PRAGMA_OMP_UNROLL:
	  हाल PRAGMA_OMP_TILE:
	    वापस true;
	  शेष:
	    अवरोध;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      माप_प्रकार n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      अगर (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->मूल्य)
	  && C_RID_CODE (token->मूल्य) == RID_FOR)
	वापस true;
      अगर (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  वापस false;
}

अटल वृक्ष c_parser_omp_tile (location_t, c_parser *, bool *);
अटल वृक्ष c_parser_omp_unroll (location_t, c_parser *, bool *);

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

अटल वृक्ष
c_parser_omp_loop_nest (c_parser *parser, bool *if_p)
{
  वृक्ष decl = NULL_वृक्ष, cond = NULL_वृक्ष, incr = NULL_वृक्ष, init = NULL_वृक्ष;
  वृक्ष body = NULL_वृक्ष;
  matching_parens parens;
  bool moreloops;
  अचिन्हित अक्षर save_in_statement;
  वृक्ष loop_scope;
  location_t loc;
  काष्ठा omp_for_parse_तथ्य *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  पूर्णांक depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  अगर (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      वृक्ष std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, शून्य);
      अगर (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_PRAGMA))
    {
      वृक्ष transform = NULL_वृक्ष, sizes, body = NULL_वृक्ष;
      पूर्णांक गिनती = 0;
      चयन (c_parser_peek_token (parser)->pragma_kind)
	{
	हाल PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = धकेलो_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = निकालो_stmt_list (body);
	  अगर (transform == NULL_वृक्ष || transform == error_mark_गाँठ)
	    {
	      transform = error_mark_गाँठ;
	      अवरोध;
	    }
	  gcc_assert (वृक्ष_CODE (transform) == OMP_UNROLL);
	  अगर (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      अगर (omp_for_parse_state->गिनती - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->गिनती - depth);
		  transform = error_mark_गाँठ;
		}
	      अन्यथा
		गिनती = 1;
	    }
	  अन्यथा
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_गाँठ;
	    }
	  अवरोध;
	हाल PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = धकेलो_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = निकालो_stmt_list (body);
	  अगर (transform == NULL_वृक्ष || transform == error_mark_गाँठ)
	    {
	      transform = error_mark_गाँठ;
	      अवरोध;
	    }
	  gcc_assert (वृक्ष_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  गिनती = list_लंबाई (OMP_CLAUSE_SIZES_LIST (sizes));
	  अगर (depth + गिनती < omp_for_parse_state->गिनती)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			गिनती, omp_for_parse_state->गिनती - depth);
	      transform = error_mark_गाँठ;
	    }
	  अवरोध;
	शेष:
	  c_parser_pragma (parser, pragma_stmt, शून्य, void_list_गाँठ);
	  अवरोध;
	}
      अगर (transform == NULL_वृक्ष)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      अगर (transform == NULL_वृक्ष || transform == error_mark_गाँठ)
	{
	  omp_for_parse_state->हार = true;
	  वापस NULL_वृक्ष;
	}
      क्रम (गिनती = omp_for_parse_state->गिनती; depth < गिनती; ++depth)
	{
	  वृक्ष_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_वृक्ष;
	  वृक्ष_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_वृक्ष;
	  वृक्ष_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_वृक्ष;
	  वृक्ष_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_वृक्ष;
	}
      omp_for_parse_state->want_nested_loop = false;
      वापस body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = false;

  अगर (!parens.require_open (parser))
    {
      omp_for_parse_state->हार = true;
      वापस NULL_वृक्ष;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (true);

  /* Parse the initialization declaration or expression.  */
  अगर (c_parser_अग्र_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      वृक्ष this_pre_body = धकेलो_stmt_list ();
      c_in_omp_for = true;
      c_parser_declaration_or_fndef (parser, true, true, true, true, true,
				     false);
      c_in_omp_for = false;
      this_pre_body = निकालो_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      अगर (decl == शून्य)
	जाओ error_init;
      अगर (DECL_INITIAL (decl) == error_mark_गाँठ)
	decl = error_mark_गाँठ;
      init = decl;
    }
  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      काष्ठा c_व्यंजक decl_exp;
      काष्ठा c_व्यंजक init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.मूल्य;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_व्यंजक_no_commas (parser, शून्य);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = true;
      init = build_modify_व्यंजक (init_loc, decl, decl_exp.original_type,
				NOP_व्यंजक, init_loc, init_exp.मूल्य,
				init_exp.original_type);
      c_in_omp_for = false;
      init = c_process_व्यंजक_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  अन्यथा
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->हार = true;
      जाओ parse_अग्र;
    }

  /* Parse the loop condition.  */
  अगर (c_parser_अग्र_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = true;
      काष्ठा c_व्यंजक cond_व्यंजक
	= c_parser_द्विआधारी_expression (parser, शून्य, NULL_वृक्ष);
      c_in_omp_for = false;

      cond = cond_व्यंजक.मूल्य;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      चयन (cond_व्यंजक.original_code)
	{
	हाल GT_व्यंजक:
	हाल GE_व्यंजक:
	हाल LT_व्यंजक:
	हाल LE_व्यंजक:
	  अवरोध;
	हाल NE_व्यंजक:
	  अगर (omp_for_parse_state->code != OACC_LOOP)
	    अवरोध;
	  /* FALLTHRU.  */
	शेष:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_व्यंजक, boolean_type_गाँठ, error_mark_गाँठ);
	  अवरोध;
	}
      protected_set_व्यंजक_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  अगर (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_व्यंजक_stmt (incr_loc,
				  c_parser_expression (parser).मूल्य);
    }
  parens.skip_until_found_close (parser);

  अगर (decl == शून्य || decl == error_mark_गाँठ || init == error_mark_गाँठ)
    omp_for_parse_state->हार = true;
  अन्यथा
    {
      वृक्ष_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      वृक्ष_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      वृक्ष_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      वृक्ष_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_अग्र:
  moreloops = depth < omp_for_parse_state->गिनती - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  अगर (moreloops
      && c_parser_omp_अग्र_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     false))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  अन्यथा अगर (moreloops && c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = true;
      body = c_parser_compound_statement (parser, शून्य);
      omp_for_parse_state->in_intervening_code = false;
      अगर (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->हार = true;
	}
      if_p = शून्य;
    }
  अन्यथा
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      अगर (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->हार = true;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = शून्य;
      body = धकेलो_stmt_list ();
      अगर (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, false);
      अन्यथा
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = निकालो_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = false;
  omp_for_parse_state->in_intervening_code = true;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  अगर (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, true);
  अगर (decl && वृक्ष_CODE (body) == BIND_व्यंजक)
    {
      वृक्ष t = BIND_व्यंजक_VARS (body);
      वृक्ष पूर्व = NULL_वृक्ष, अग्र = NULL_वृक्ष;
      जबतक (t)
	{
	  अग्र = DECL_CHAIN (t);
	  अगर (t == decl)
	    {
	      अगर (पूर्व)
		DECL_CHAIN (पूर्व) = अग्र;
	      अन्यथा
		{
		  BIND_व्यंजक_VARS (body) = अग्र;
		  BLOCK_VARS (BIND_व्यंजक_BLOCK (body)) = अग्र;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      अवरोध;
	    }
	  अन्यथा
	    {
	      पूर्व = t;
	      t = अग्र;
	    }
	}
      अगर (BIND_व्यंजक_VARS (body) == NULL_वृक्ष)
	body = BIND_व्यंजक_BODY (body);
    }

  वापस body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

अटल वृक्ष
c_parser_omp_for_loop (location_t loc, c_parser *parser, क्रमागत वृक्ष_code code,
		       वृक्ष clauses, वृक्ष *cclauses, bool *if_p)
{
  वृक्ष body, stmt, cl;
  वृक्ष ret = NULL_वृक्ष;
  वृक्ष ordered_cl = NULL_वृक्ष;
  पूर्णांक i, collapse = 1, ordered = 0, गिनती;
  bool oacc_tiling = false;
  bool inscan = false;
  काष्ठा omp_for_parse_तथ्य तथ्य;
  काष्ठा omp_for_parse_तथ्य *save_तथ्य = parser->omp_for_parse_state;

  क्रम (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    अगर (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = वृक्ष_to_shwi (OMP_CLAUSE_COLLAPSE_व्यंजक (cl));
    अन्यथा अगर (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = true;
	collapse = list_लंबाई (OMP_CLAUSE_TILE_LIST (cl));
      }
    अन्यथा अगर (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_लंबाई (OMP_CLAUSE_SIZES_LIST (cl));
    अन्यथा अगर (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_व्यंजक (cl))
      {
	ordered_cl = cl;
	ordered = वृक्ष_to_shwi (OMP_CLAUSE_ORDERED_व्यंजक (cl));
      }
    अन्यथा अगर (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = true;

  अगर (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_व्यंजक (ordered_cl)
	= build_int_cst (integer_type_गाँठ, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  गिनती = ordered ? ordered : collapse;

  अगर (!c_parser_omp_अग्र_tokens_can_be_canon_loop (parser, code, true))
    वापस शून्य;

  /* Initialize parse state for recursive descent.  */
  तथ्य.declv = make_वृक्ष_vec (गिनती);
  तथ्य.initv = make_वृक्ष_vec (गिनती);
  तथ्य.condv = make_वृक्ष_vec (गिनती);
  तथ्य.incrv = make_वृक्ष_vec (गिनती);
  तथ्य.pre_body = NULL_वृक्ष;
  तथ्य.bindings = NULL_वृक्ष;
  तथ्य.for_loc = c_parser_peek_token (parser)->location;
  तथ्य.गिनती = गिनती;
  तथ्य.depth = 0;
  तथ्य.want_nested_loop = true;
  तथ्य.ordered = ordered > 0;
  तथ्य.in_intervening_code = false;
  तथ्य.perfect_nesting_fail = false;
  तथ्य.हार = false;
  तथ्य.inscan = inscan;
  तथ्य.saw_intervening_code = false;
  तथ्य.code = code;
  parser->omp_for_parse_state = &तथ्य;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  क्रम (वृक्ष t = तथ्य.bindings; t; )
    {
      वृक्ष n = वृक्ष_CHAIN (t);
      वृक्ष_CHAIN (t) = NULL_वृक्ष;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  अगर (!तथ्य.हार)
    {
      c_in_omp_for = true;
      stmt = c_finish_omp_for (loc, code, तथ्य.declv, शून्य, तथ्य.initv,
			       तथ्य.condv, तथ्य.incrv,
			       body, तथ्य.pre_body, true);
      c_in_omp_for = false;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      अगर (stmt && !c_omp_check_loop_iv (stmt, तथ्य.declv, शून्य))
	stmt = NULL_वृक्ष;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      अगर (तथ्य.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, शून्य))
	stmt = NULL_वृक्ष;

      अगर (stmt)
	{
	  add_stmt (stmt);

	  क्रम (i = 0; i < वृक्ष_VEC_लंबाई (OMP_FOR_INIT (stmt)); i++)
	    {
	      वृक्ष init = वृक्ष_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      अगर (init == NULL_वृक्ष)
		अवरोध;
	      gcc_assert (वृक्ष_CODE (init) == MODIFY_व्यंजक);
	      वृक्ष decl = वृक्ष_OPERAND (init, 0);
	      वृक्ष cond = वृक्ष_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (वृक्ष_OPERAND (cond, 0) == decl);

	      वृक्ष op0 = वृक्ष_OPERAND (init, 1);
	      अगर (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || वृक्ष_CODE (op0) != वृक्ष_VEC)
		वृक्ष_OPERAND (init, 1) = c_fully_fold (op0, false, शून्य);
	      अन्यथा
		{
		  वृक्ष_VEC_ELT (op0, 1)
		    = c_fully_fold (वृक्ष_VEC_ELT (op0, 1), false, शून्य);
		  वृक्ष_VEC_ELT (op0, 2)
		    = c_fully_fold (वृक्ष_VEC_ELT (op0, 2), false, शून्य);
		}

	      वृक्ष op1 = वृक्ष_OPERAND (cond, 1);
	      अगर (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || वृक्ष_CODE (op1) != वृक्ष_VEC)
		वृक्ष_OPERAND (cond, 1) = c_fully_fold (op1, false, शून्य);
	      अन्यथा
		{
		  वृक्ष_VEC_ELT (op1, 1)
		    = c_fully_fold (वृक्ष_VEC_ELT (op1, 1), false, शून्य);
		  वृक्ष_VEC_ELT (op1, 2)
		    = c_fully_fold (वृक्ष_VEC_ELT (op1, 2), false, शून्य);
		}
	    }

	  अगर (cclauses != शून्य
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != शून्य)
	    {
	      वृक्ष *c;
	      क्रम (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		अगर (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		अन्यथा
		  {
		    क्रम (i = 0; i < गिनती; i++)
		      अगर (वृक्ष_VEC_ELT (तथ्य.declv, i) == OMP_CLAUSE_DECL (*c))
			अवरोध;
		    अगर (i == गिनती)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    अन्यथा अगर (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
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
			वृक्ष l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			अगर (code == OMP_SIMD)
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

  parser->omp_for_parse_state = save_तथ्य;
  वापस ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

अटल व्योम
omp_split_clauses (location_t loc, क्रमागत वृक्ष_code code,
		   omp_clause_mask mask, वृक्ष clauses, वृक्ष *cclauses)
{
  पूर्णांक i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  क्रम (i = 0; i < C_OMP_CLAUSE_SPLIT_गिनती; i++)
    अगर (cclauses[i])
      cclauses[i] = c_finish_omp_clauses (cclauses[i],
					  i == C_OMP_CLAUSE_SPLIT_TARGET
					  ? C_ORT_OMP_TARGET : C_ORT_OMP);
}

/* OpenMP 5.0:
   #pragma omp loop loop-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#घोषणा OMP_LOOP_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_BIND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDER))

अटल वृक्ष
c_parser_omp_loop (location_t loc, c_parser *parser,
		   अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
		   bool *if_p)
{
  वृक्ष block, clauses, ret;

  म_जोड़ो (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस ret;
}

/* OpenMP 4.0:
   #pragma omp simd simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#घोषणा OMP_SIMD_CLAUSE_MASK					\
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

अटल वृक्ष
c_parser_omp_simd (location_t loc, c_parser *parser,
		   अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
		   bool *if_p)
{
  वृक्ष block, clauses, ret;

  म_जोड़ो (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस ret;
}

/* OpenMP 2.5:
   #pragma omp for for-clause[optseq] new-line
     for-loop

   OpenMP 4.0:
   #pragma omp for simd for-simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#घोषणा OMP_FOR_CLAUSE_MASK					\
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

अटल वृक्ष
c_parser_omp_for (location_t loc, c_parser *parser,
		  अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
		  bool *if_p)
{
  वृक्ष block, clauses, ret;

  म_जोड़ो (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  अगर (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  अगर ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      अगर (म_भेद (p, "simd") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  अगर (cclauses == शून्य)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (true);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  अगर (ret == NULL_वृक्ष)
	    वापस ret;
	  ret = make_गाँठ (OMP_FOR);
	  वृक्ष_TYPE (ret) = void_type_गाँठ;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_व्यंजक_LOCATION (ret, loc);
	  add_stmt (ret);
	  वापस ret;
	}
    }
  अगर (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, false);
      वापस NULL_वृक्ष;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  अगर ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस ret;
}

अटल वृक्ष c_parser_omp_taskloop (location_t, c_parser *, अक्षर *,
				   omp_clause_mask, वृक्ष *, bool *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

अटल वृक्ष
c_parser_omp_master (location_t loc, c_parser *parser,
		     अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
		     bool *if_p, location_t master_loc)
{
  वृक्ष block, clauses, ret;
  gcc_rich_location richloc (loc);
  अगर (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  म_जोड़ो (p_name, " master");

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      अगर (म_भेद (p, "taskloop") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  अगर (cclauses == शून्य)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (true);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  अगर (ret == NULL_वृक्ष)
	    वापस ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  वापस ret;
	}
    }
  अगर (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, false);
      वापस NULL_वृक्ष;
    }

  अगर (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, false);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  अन्यथा
    c_parser_skip_to_pragma_eol (parser);

  वापस c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#घोषणा OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

अटल वृक्ष
c_parser_omp_masked (location_t loc, c_parser *parser,
		     अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
		     bool *if_p)
{
  वृक्ष block, clauses, ret;

  म_जोड़ो (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      अगर (म_भेद (p, "taskloop") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  अगर (cclauses == शून्य)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (true);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  अगर (ret == NULL_वृक्ष)
	    वापस ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  वापस ret;
	}
    }
  अगर (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, false);
      वापस NULL_वृक्ष;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  वापस c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
								  if_p),
			      clauses);
}

/* OpenMP 5.1:
   # pragma omp interop clauses[opt] new-line */

#घोषणा OMP_INTEROP_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DESTROY)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INIT)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE))

अटल व्योम
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  वृक्ष clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  वृक्ष stmt = make_गाँठ (OMP_INTEROP);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, loc);
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

#घोषणा OMP_ORDERED_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SIMD))

#घोषणा OMP_ORDERED_DEPEND_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DOACROSS))

अटल bool
c_parser_omp_ordered (c_parser *parser, क्रमागत pragma_context context,
		      bool *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  अगर (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, false);
      वापस false;
    }

  पूर्णांक n = 1;
  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
    n = 2;

  अगर (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      स्थिर अक्षर *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->मूल्य);

      अगर (!म_भेद ("depend", p) || !म_भेद ("doacross", p))
	{
	  अगर (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, false);
	      वापस false;
	    }
	  अगर (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, false);
	      वापस true;
	    }

	  वृक्ष clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_वृक्ष);
	  वापस false;
	}
    }

  वृक्ष clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  अगर (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_वृक्ष)
    वापस false;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  वापस true;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

अटल वृक्ष
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  वृक्ष stmt, substmt;
  bool error_suppress = false;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  अगर (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = false;
      वापस NULL_वृक्ष;
    }

  stmt = धकेलो_stmt_list ();

  अगर (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", true))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_गाँठ, substmt);
      SET_व्यंजक_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  जबतक (1)
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
	अवरोध;
      अगर (c_parser_अग्र_token_is (parser, CPP_EOF))
	अवरोध;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", false);
      अगर (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = false;
	}
      अन्यथा अगर (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = true;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_गाँठ, substmt);
      SET_व्यंजक_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = निकालो_stmt_list (stmt);

  stmt = make_गाँठ (OMP_SECTIONS);
  SET_व्यंजक_LOCATION (stmt, sections_loc);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_SECTIONS_BODY (stmt) = substmt;

  वापस add_stmt (stmt);
}

/* OpenMP 2.5:
   # pragma omp sections sections-clause[optseq] newline
     sections-scope

   LOC is the location of the #pragma token.
*/

#घोषणा OMP_SECTIONS_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

अटल वृक्ष
c_parser_omp_sections (location_t loc, c_parser *parser,
		       अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses)
{
  वृक्ष block, clauses, ret;

  म_जोड़ो (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  अगर (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_sections_scope (loc, parser);
  अगर (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस ret;
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

#घोषणा OMP_PARALLEL_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अंक_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

अटल वृक्ष
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
		       bool *if_p)
{
  वृक्ष stmt, clauses, block;

  म_जोड़ो (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  अगर ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  अगर (c_parser_अग्र_token_is_keyword (parser, RID_FOR))
    {
      वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
      अगर (cclauses == शून्य)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      अगर (!flag_openmp)  /* flag_openmp_simd  */
	वापस c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      वृक्ष ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      अगर (ret == NULL_वृक्ष)
	वापस ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      वापस stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  अन्यथा अगर (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      वापस NULL_वृक्ष;
    }
  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      location_t ploc = c_parser_peek_token (parser)->location;
      अगर (cclauses == शून्य && म_भेद (p, "masked") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  वृक्ष ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  अगर (ret == शून्य)
	    वापस ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  अगर (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  वापस stmt;
	}
      अन्यथा अगर (cclauses == शून्य && म_भेद (p, "master") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  वृक्ष ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  अगर (ret == शून्य)
	    वापस ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  अगर (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  वापस stmt;
	}
      अन्यथा अगर (म_भेद (p, "loop") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  अगर (cclauses == शून्य)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  वृक्ष ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  अगर (ret == NULL_वृक्ष)
	    वापस ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  वापस stmt;
	}
      अन्यथा अगर (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, false);
	  वापस NULL_वृक्ष;
	}
      अन्यथा अगर (cclauses == शून्य && म_भेद (p, "sections") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  वापस stmt;
	}
    }
  अन्यथा अगर (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, false);
      वापस NULL_वृक्ष;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = true;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  वापस stmt;
}

/* OpenMP 2.5:
   # pragma omp single single-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#घोषणा OMP_SINGLE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

अटल वृक्ष
c_parser_omp_single (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष stmt = make_गाँठ (OMP_SINGLE);
  SET_व्यंजक_LOCATION (stmt, loc);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  वापस add_stmt (stmt);
}

/* OpenMP 5.1:
   # pragma omp scope scope-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#घोषणा OMP_SCOPE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

अटल वृक्ष
c_parser_omp_scope (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष stmt = make_गाँठ (OMP_SCOPE);
  SET_व्यंजक_LOCATION (stmt, loc);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  वापस add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
अटल वृक्ष
c_parser_omp_dispatch_body (c_parser *parser)
{
  काष्ठा c_व्यंजक lhs, rhs, ret;
  location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, शून्य, शून्य);
  अगर (वृक्ष_CODE (lhs.मूल्य) == CALL_व्यंजक)
    वापस lhs.मूल्य;

  location_t op_location = c_parser_peek_token (parser)->location;
  अगर (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    वापस error_mark_गाँठ;

  /* Parse function name.  */
  अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      वापस error_mark_गाँठ;
    }
  व्यंजक_loc = c_parser_peek_token (parser)->location;
  वृक्ष id = c_parser_peek_token (parser)->मूल्य;
  c_parser_consume_token (parser);
  अगर (!c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      वापस error_mark_गाँठ;
    }

  rhs.मूल्य = build_external_ref (व्यंजक_loc, id, true, &rhs.original_type);
  set_c_व्यंजक_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, व्यंजक_LOC_OR_LOC (rhs.मूल्य, व्यंजक_loc), rhs);
  अगर (वृक्ष_CODE (rhs.मूल्य) != CALL_व्यंजक)
    {
      error_at (व्यंजक_LOC_OR_LOC (rhs.मूल्य, व्यंजक_loc),
		"expected target-function call");
      वापस error_mark_गाँठ;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (व्यंजक_loc, rhs, true, true);
  ret.मूल्य
    = build_modify_व्यंजक (op_location, lhs.मूल्य, lhs.original_type, NOP_व्यंजक,
			 व्यंजक_loc, rhs.मूल्य, rhs.original_type);
  ret.m_decimal = 0;
  set_c_व्यंजक_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_व्यंजक;
  ret.original_type = शून्य;
  वापस ret.मूल्य;
}

/* OpenMP 5.1:
   # pragma omp dispatch dispatch-clause[optseq] new-line
     expression-stmt

   LOC is the location of the #pragma.
*/

#घोषणा OMP_DISPATCH_CLAUSE_MASK                                               \
  ((OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)                             \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)                           \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOVARIANTS)                       \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOCONTEXT)                        \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR)                  \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INTEROP)                          \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)                    \
   | (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

अटल वृक्ष
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  वृक्ष stmt = make_गाँठ (OMP_DISPATCH);
  SET_व्यंजक_LOCATION (stmt, loc);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  वृक्ष depend_clauses = NULL_वृक्ष;
  वृक्ष *depend_clauses_ptr = &depend_clauses;
  क्रम (वृक्ष c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  अगर (depend_clauses != NULL_वृक्ष)
    {
      वृक्ष stmt = make_गाँठ (OMP_TASK);
      वृक्ष_TYPE (stmt) = void_गाँठ;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_वृक्ष;
      SET_व्यंजक_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  वृक्ष dispatch_body = c_parser_omp_dispatch_body (parser);
  अगर (dispatch_body == error_mark_गाँठ)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      वापस NULL_वृक्ष;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (वृक्ष_CODE (dispatch_body) == CALL_व्यंजक
	      || वृक्ष_CODE (dispatch_body) == MODIFY_व्यंजक);
  वृक्ष *dispatch_call = वृक्ष_CODE (dispatch_body) == MODIFY_व्यंजक
			  ? &वृक्ष_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  जबतक (वृक्ष_CODE (*dispatch_call) == FLOAT_व्यंजक
	 || वृक्ष_CODE (*dispatch_call) == CONVERT_व्यंजक
	 || वृक्ष_CODE (*dispatch_call) == NOP_व्यंजक)
    dispatch_call = &वृक्ष_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_व्यंजक_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    वृक्ष_TYPE (वृक्ष_TYPE (CALL_व्यंजक_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  वापस add_stmt (stmt);
}

/* OpenMP 3.0:
   # pragma omp task task-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#घोषणा OMP_TASK_CLAUSE_MASK					\
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

अटल वृक्ष
c_parser_omp_task (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = true;
  c_parser_statement (parser, if_p);
  वापस c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#घोषणा OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

अटल व्योम
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  वृक्ष clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  अगर (clauses)
    {
      वृक्ष stmt = make_गाँठ (OMP_TASK);
      वृक्ष_TYPE (stmt) = void_गाँठ;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_वृक्ष;
      SET_व्यंजक_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  अन्यथा
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

अटल व्योम
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

#घोषणा OMP_TASKGROUP_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TASK_REDUCTION))

अटल वृक्ष
c_parser_omp_taskgroup (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  वृक्ष body = c_parser_omp_structured_block (parser, if_p);
  वापस c_finish_omp_taskgroup (loc, body, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancel cancel-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#घोषणा OMP_CANCEL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TASKGROUP)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF))

अटल व्योम
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  वृक्ष clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
					   "#pragma omp cancel");

  c_finish_omp_cancel (loc, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancellation point cancelpt-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#घोषणा OMP_CANCELLATION_POINT_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TASKGROUP))

अटल bool
c_parser_omp_cancellation_point (c_parser *parser, क्रमागत pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष clauses;
  bool point_seen = false;

  c_parser_consume_pragma (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = true;
	}
    }
  अगर (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      वापस false;
    }

  अगर (context != pragma_compound)
    {
      अगर (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      अन्यथा
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, false);
      वापस true;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  वापस true;
}

/* OpenMP 4.0:
   #pragma omp distribute distribute-clause[optseq] new-line
     for-loop  */

#घोषणा OMP_DISTRIBUTE_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDER))

अटल वृक्ष
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
			 bool *if_p)
{
  वृक्ष clauses, block, ret;

  म_जोड़ो (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      bool simd = false;
      bool parallel = false;

      अगर (म_भेद (p, "simd") == 0)
	simd = true;
      अन्यथा
	parallel = म_भेद (p, "parallel") == 0;
      अगर (parallel || simd)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  अगर (cclauses == शून्य)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      अगर (simd)
		वापस c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      अन्यथा
		वापस c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (true);
	  अगर (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  अन्यथा
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  अगर (ret == शून्य)
	    वापस ret;
	  ret = make_गाँठ (OMP_DISTRIBUTE);
	  वृक्ष_TYPE (ret) = void_type_गाँठ;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_व्यंजक_LOCATION (ret, loc);
	  add_stmt (ret);
	  वापस ret;
	}
    }
  अगर (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, false);
      वापस NULL_वृक्ष;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, शून्य,
			       if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#घोषणा OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अंक_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

अटल वृक्ष
c_parser_omp_teams (location_t loc, c_parser *parser,
		    अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
		    bool *if_p)
{
  वृक्ष clauses, block, ret;

  म_जोड़ो (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "distribute") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  अगर (cclauses == शून्य)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  अगर (ret == शून्य)
	    वापस ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_गाँठ (OMP_TEAMS);
	  वृक्ष_TYPE (ret) = void_type_गाँठ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_व्यंजक_LOCATION (ret, loc);
	  वापस add_stmt (ret);
	}
      अन्यथा अगर (म_भेद (p, "loop") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  अगर (cclauses == शून्य)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  अगर (ret == शून्य)
	    वापस ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_गाँठ (OMP_TEAMS);
	  वृक्ष_TYPE (ret) = void_type_गाँठ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_व्यंजक_LOCATION (ret, loc);
	  वापस add_stmt (ret);
	}
    }
  अगर (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, false);
      वापस NULL_वृक्ष;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  वृक्ष stmt = make_गाँठ (OMP_TEAMS);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, true);
  SET_व्यंजक_LOCATION (stmt, loc);

  वापस add_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target data target-data-clause[optseq] new-line
     structured-block  */

#घोषणा OMP_TARGET_तथ्य_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR) \
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR))

अटल वृक्ष
c_parser_omp_target_तथ्य (location_t loc, c_parser *parser, bool *if_p)
{
  अगर (flag_openmp)
    omp_requires_mask
      = (क्रमागत omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  वृक्ष clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_तथ्य_CLAUSE_MASK,
				"#pragma omp target data", false);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, false);
  पूर्णांक map_seen = 0;
  क्रम (वृक्ष *pc = &clauses; *pc;)
    {
      अगर (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	चयन (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  हाल GOMP_MAP_TO:
	  हाल GOMP_MAP_ALWAYS_TO:
	  हाल GOMP_MAP_PRESENT_TO:
	  हाल GOMP_MAP_ALWAYS_PRESENT_TO:
	  हाल GOMP_MAP_FROM:
	  हाल GOMP_MAP_ALWAYS_FROM:
	  हाल GOMP_MAP_PRESENT_FROM:
	  हाल GOMP_MAP_ALWAYS_PRESENT_FROM:
	  हाल GOMP_MAP_TOFROM:
	  हाल GOMP_MAP_ALWAYS_TOFROM:
	  हाल GOMP_MAP_PRESENT_TOFROM:
	  हाल GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  हाल GOMP_MAP_ALLOC:
	  हाल GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_FIRSTPRIVATE_POINTER:
	  हाल GOMP_MAP_ALWAYS_POINTER:
	  हाल GOMP_MAP_ATTACH_DETACH:
	  हाल GOMP_MAP_ATTACH:
	    अवरोध;
	  शेष:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    जारी;
	  }
      अन्यथा अगर (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  अगर (map_seen != 3)
    {
      अगर (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      वापस NULL_वृक्ष;
    }

  वृक्ष stmt = make_गाँठ (OMP_TARGET_तथ्य);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_TARGET_तथ्य_CLAUSES (stmt) = clauses;
  keep_अग्र_level ();
  वृक्ष block = c_begin_compound_stmt (true);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_तथ्य_BODY (stmt) = c_end_compound_stmt (loc, block, true);

  SET_व्यंजक_LOCATION (stmt, loc);
  वापस add_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target update target-update-clause[optseq] new-line */

#घोषणा OMP_TARGET_UPDATE_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FROM)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TO)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

अटल bool
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    क्रमागत pragma_context context)
{
  अगर (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, false);
      वापस true;
    }

  वृक्ष clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ false);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  अगर (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_वृक्ष
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_वृक्ष)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      वापस false;
    }

  अगर (flag_openmp)
    omp_requires_mask
      = (क्रमागत omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  वृक्ष stmt = make_गाँठ (OMP_TARGET_UPDATE);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);
  वापस false;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#घोषणा OMP_TARGET_ENTER_तथ्य_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

अटल bool
c_parser_omp_target_enter_तथ्य (location_t loc, c_parser *parser,
				क्रमागत pragma_context context)
{
  bool तथ्य_seen = false;
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  तथ्य_seen = true;
	}
    }
  अगर (!तथ्य_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      वापस false;
    }

  अगर (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, false);
      वापस true;
    }

  अगर (flag_openmp)
    omp_requires_mask
      = (क्रमागत omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  वृक्ष clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_तथ्य_CLAUSE_MASK,
				"#pragma omp target enter data", false);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, false);
  पूर्णांक map_seen = 0;
  क्रम (वृक्ष *pc = &clauses; *pc;)
    {
      अगर (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	चयन (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  हाल GOMP_MAP_TO:
	  हाल GOMP_MAP_ALWAYS_TO:
	  हाल GOMP_MAP_PRESENT_TO:
	  हाल GOMP_MAP_ALWAYS_PRESENT_TO:
	  हाल GOMP_MAP_ALLOC:
	  हाल GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_FIRSTPRIVATE_POINTER:
	  हाल GOMP_MAP_ALWAYS_POINTER:
	  हाल GOMP_MAP_ATTACH_DETACH:
	  हाल GOMP_MAP_ATTACH:
	    अवरोध;
	  शेष:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    जारी;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  अगर (map_seen != 3)
    {
      अगर (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      वापस true;
    }

  वृक्ष stmt = make_गाँठ (OMP_TARGET_ENTER_तथ्य);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_TARGET_ENTER_तथ्य_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);
  वापस true;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#घोषणा OMP_TARGET_EXIT_तथ्य_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

अटल bool
c_parser_omp_target_exit_तथ्य (location_t loc, c_parser *parser,
			       क्रमागत pragma_context context)
{
  bool तथ्य_seen = false;
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  तथ्य_seen = true;
	}
    }
  अगर (!तथ्य_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      वापस false;
    }

  अगर (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, false);
      वापस true;
    }

  अगर (flag_openmp)
    omp_requires_mask
      = (क्रमागत omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  वृक्ष clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_तथ्य_CLAUSE_MASK,
				"#pragma omp target exit data", false);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_तथ्य);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_तथ्य);
  c_omp_adjust_map_clauses (clauses, false);
  पूर्णांक map_seen = 0;
  क्रम (वृक्ष *pc = &clauses; *pc;)
    {
      अगर (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	चयन (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  हाल GOMP_MAP_FROM:
	  हाल GOMP_MAP_ALWAYS_FROM:
	  हाल GOMP_MAP_PRESENT_FROM:
	  हाल GOMP_MAP_ALWAYS_PRESENT_FROM:
	  हाल GOMP_MAP_RELEASE:
	  हाल GOMP_MAP_DELETE:
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    अवरोध;
	  हाल GOMP_MAP_FIRSTPRIVATE_POINTER:
	  हाल GOMP_MAP_ALWAYS_POINTER:
	  हाल GOMP_MAP_ATTACH_DETACH:
	  हाल GOMP_MAP_DETACH:
	    अवरोध;
	  शेष:
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

  अगर (map_seen != 3)
    {
      अगर (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      वापस true;
    }

  वृक्ष stmt = make_गाँठ (OMP_TARGET_EXIT_तथ्य);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_TARGET_EXIT_तथ्य_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);
  वापस true;
}

/* OpenMP 4.0:
   # pragma omp target target-clause[optseq] new-line
     structured-block  */

#घोषणा OMP_TARGET_CLAUSE_MASK					\
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

अटल bool
c_parser_omp_target (c_parser *parser, क्रमागत pragma_context context, bool *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  वृक्ष *pc = शून्य, stmt, block, body, clauses;

  अगर (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      वापस false;
    }

  अगर (flag_openmp)
    omp_requires_mask
      = (क्रमागत omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      क्रमागत वृक्ष_code ccode = ERROR_MARK;

      अगर (म_भेद (p, "teams") == 0)
	ccode = OMP_TEAMS;
      अन्यथा अगर (म_भेद (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      अन्यथा अगर (म_भेद (p, "simd") == 0)
	ccode = OMP_SIMD;
      अगर (ccode != ERROR_MARK)
	{
	  वृक्ष cclauses[C_OMP_CLAUSE_SPLIT_गिनती];
	  अक्षर p_name[माप ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  म_नकल (p_name, "#pragma omp target");
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      वृक्ष stmt;
	      चयन (ccode)
		{
		हाल OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  अवरोध;
		हाल OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  अवरोध;
		हाल OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  अवरोध;
		शेष:
		  gcc_unreachable ();
		}
	      वापस stmt != NULL_वृक्ष;
	    }
	  keep_अग्र_level ();
	  वृक्ष block = c_begin_compound_stmt (true), ret;
	  चयन (ccode)
	    {
	    हाल OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      अवरोध;
	    हाल OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      अवरोध;
	    हाल OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      अवरोध;
	    शेष:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, true);
	  अगर (ret == NULL_वृक्ष)
	    वापस false;
	  अगर (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    क्रम (वृक्ष c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_अंक_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		क्रम (पूर्णांक i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_अंक_TEAMS); ++i)
		  अगर (OMP_CLAUSE_OPERAND (c, i)
		      && वृक्ष_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      वृक्ष व्यंजक = OMP_CLAUSE_OPERAND (c, i);
		      वृक्ष tmp = create_tmp_var_raw (वृक्ष_TYPE (व्यंजक));
		      व्यंजक = build4 (TARGET_व्यंजक, वृक्ष_TYPE (व्यंजक), tmp,
				     व्यंजक, NULL_वृक्ष, NULL_वृक्ष);
		      add_stmt (व्यंजक);
		      OMP_CLAUSE_OPERAND (c, i) = व्यंजक;
		      वृक्ष tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  वृक्ष stmt = make_गाँठ (OMP_TARGET);
	  वृक्ष_TYPE (stmt) = void_type_गाँठ;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), true);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_व्यंजक_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  जाओ check_clauses;
	}
      अन्यथा अगर (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, false);
	  वापस false;
	}
      अन्यथा अगर (म_भेद (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_तथ्य (loc, parser, if_p);
	  वापस true;
	}
      अन्यथा अगर (म_भेद (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  वापस c_parser_omp_target_enter_तथ्य (loc, parser, context);
	}
      अन्यथा अगर (म_भेद (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  वापस c_parser_omp_target_exit_तथ्य (loc, parser, context);
	}
      अन्यथा अगर (म_भेद (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  वापस c_parser_omp_target_update (loc, parser, context);
	}
    }
  अगर (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, false);
      वापस false;
    }

  stmt = make_गाँठ (OMP_TARGET);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", false);
  क्रम (वृक्ष c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	वृक्ष nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, true);

  keep_अग्र_level ();
  block = c_begin_compound_stmt (true);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, true);

  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  जबतक (*pc)
    {
      अगर (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	चयन (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  हाल GOMP_MAP_TO:
	  हाल GOMP_MAP_ALWAYS_TO:
	  हाल GOMP_MAP_PRESENT_TO:
	  हाल GOMP_MAP_ALWAYS_PRESENT_TO:
	  हाल GOMP_MAP_FROM:
	  हाल GOMP_MAP_ALWAYS_FROM:
	  हाल GOMP_MAP_PRESENT_FROM:
	  हाल GOMP_MAP_ALWAYS_PRESENT_FROM:
	  हाल GOMP_MAP_TOFROM:
	  हाल GOMP_MAP_ALWAYS_TOFROM:
	  हाल GOMP_MAP_PRESENT_TOFROM:
	  हाल GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  हाल GOMP_MAP_ALLOC:
	  हाल GOMP_MAP_PRESENT_ALLOC:
	  हाल GOMP_MAP_FIRSTPRIVATE_POINTER:
	  हाल GOMP_MAP_ALWAYS_POINTER:
	  हाल GOMP_MAP_POINTER:
	  हाल GOMP_MAP_ATTACH_DETACH:
	  हाल GOMP_MAP_ATTACH:
	    अवरोध;
	  शेष:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    जारी;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = true;
  वापस true;
}

/* OpenMP 4.0:
   # pragma omp declare simd declare-simd-clauses[optseq] new-line

   OpenMP 5.0:
   # pragma omp declare variant (identifier) match(context-selector) new-line

   OpenMP 5.1
   # pragma omp declare variant (identifier) match(context-selector) \
      adjust_args(adjust-op:argument-list) append_args(interop-list) new-line
   */

#घोषणा OMP_DECLARE_SIMD_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INBRANCH)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOTINBRANCH))

अटल व्योम
c_parser_omp_declare_simd (c_parser *parser, क्रमागत pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  वृक्ष kind = token->मूल्य;
  gcc_assert (म_भेद (IDENTIFIER_POINTER (kind), "simd") == 0
	      || म_भेद (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      अगर (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  वापस;
	}
      clauses.safe_धकेलो (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_धकेलो (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  जबतक (c_parser_अग्र_token_is (parser, CPP_PRAGMA))
    {
      अगर (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->मूल्य != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  वापस;
	}
      c_parser_consume_pragma (parser);
      जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  अगर (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      वापस;
	    }
	  clauses.safe_धकेलो (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_धकेलो (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  स_रखो (&eof_token, 0, माप (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_धकेलो (eof_token);
  clauses.safe_धकेलो (eof_token);

  चयन (context)
    {
    हाल pragma_external:
      अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णांक ext = disable_extension_diagnostics ();
	  करो
	    c_parser_consume_token (parser);
	  जबतक (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, true, true, true, false, true,
					 false, शून्य, &clauses);
	  restore_extension_diagnostics (ext);
	}
      अन्यथा
	c_parser_declaration_or_fndef (parser, true, true, true, false, true,
				       false, शून्य, &clauses);
      अवरोध;
    हाल pragma_struct:
    हाल pragma_param:
    हाल pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      अवरोध;
    हाल pragma_compound:
      bool have_std_attrs;
      वृक्ष std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      अगर (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      अन्यथा
	std_attrs = NULL_वृक्ष;
      अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  पूर्णांक ext = disable_extension_diagnostics ();
	  करो
	    c_parser_consume_token (parser);
	  जबतक (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  अगर (c_parser_अग्र_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, true, true, true, true,
					     true, false, शून्य, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      अवरोध;
	    }
	  restore_extension_diagnostics (ext);
	}
      अन्यथा अगर (c_parser_अग्र_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, true, true, true, true, true,
					 false, शून्य, &clauses, have_std_attrs,
					 std_attrs);
	  अवरोध;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      अवरोध;
    शेष:
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

अटल वृक्ष
c_parser_omp_context_selector (c_parser *parser, क्रमागत omp_tss_code set,
			       वृक्ष parms)
{
  वृक्ष ret = NULL_वृक्ष;
  करो
    {
      वृक्ष selector;
      अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
	  || c_parser_अग्र_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->मूल्य;
      अन्यथा
	{
	  c_parser_error (parser, "expected trait selector name");
	  वापस error_mark_गाँठ;
	}
      क्रमागत omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      अगर (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_वृक्ष, NULL_वृक्ष, ret);
	  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  अन्यथा
	    अवरोध;
	}

      c_parser_consume_token (parser);

      वृक्ष properties = NULL_वृक्ष;
      वृक्ष scoreval = NULL_वृक्ष;
      क्रमागत omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      bool allow_score = omp_ts_map[sel].allow_score;
      वृक्ष t;

      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
	{
	  अगर (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      वापस error_mark_गाँठ;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && म_भेद (IDENTIFIER_POINTER (token->मूल्य), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      वृक्ष score = c_parser_व्यंजक_no_commas (parser, शून्य).मूल्य;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      अगर (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      अन्यथा अगर (score != error_mark_गाँठ)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, false, शून्य);
		  अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (score))
		      || वृक्ष_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  अन्यथा अगर (वृक्ष_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  अन्यथा
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  चयन (property_kind)
	    {
	    हाल OMP_TRAIT_PROPERTY_ID:
	      अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
		  || c_parser_अग्र_token_is (parser, CPP_NAME))
		{
		  वृक्ष prop = c_parser_peek_token (parser)->मूल्य;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_वृक्ष,
						    properties);
		}
	      अन्यथा
		{
		  c_parser_error (parser, "expected identifier");
		  वापस error_mark_गाँठ;
		}
	      अवरोध;
	    हाल OMP_TRAIT_PROPERTY_NAME_LIST:
	      करो
		{
		  वृक्ष prop = OMP_TP_NAMELIST_गाँठ;
		  वृक्ष मूल्य = NULL_वृक्ष;
		  अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
		      || c_parser_अग्र_token_is (parser, CPP_NAME))
		    {
		      मूल्य = c_parser_peek_token (parser)->मूल्य;
		      c_parser_consume_token (parser);
		    }
		  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_STRING))
		    मूल्य = c_parser_string_literal (parser, false,
						     false).मूल्य;
		  अन्यथा
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      वापस error_mark_गाँठ;
		    }

		  properties = make_trait_property (prop, मूल्य, properties);

		  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  अन्यथा
		    अवरोध;
		}
	      जबतक (1);
	      अवरोध;
	    हाल OMP_TRAIT_PROPERTY_DEV_अंक_व्यंजक:
	    हाल OMP_TRAIT_PROPERTY_BOOL_व्यंजक:
	      {
		c_व्यंजक texpr = c_parser_व्यंजक_no_commas (parser, शून्य);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  true, true);
		t = texpr.मूल्य;
	      }
	      अगर (t == error_mark_गाँठ)
		वापस error_mark_गाँठ;
	      mark_exp_read (t);
	      अगर (property_kind == OMP_TRAIT_PROPERTY_BOOL_व्यंजक)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_गाँठ);
		  अगर (t == error_mark_गाँठ)
		    वापस error_mark_गाँठ;
		}
	      अन्यथा अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  वापस error_mark_गाँठ;
		}
	      t = c_fully_fold (t, false, शून्य);
	      properties = make_trait_property (NULL_वृक्ष, t, properties);
	      अवरोध;
	    हाल OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      अगर (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  अगर (parms == NULL_वृक्ष)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      वापस error_mark_गाँठ;
		    }
		  वृक्ष c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", true, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_गाँठ
							     ? NULL_वृक्ष : parms,
							     c);
		  properties = c;
		}
	      अन्यथा अगर (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  वापस error_mark_गाँठ;
		}
	      अन्यथा
		gcc_unreachable ();
	      अवरोध;
	    शेष:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      अन्यथा अगर (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  वापस error_mark_गाँठ;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
    }
  जबतक (1);

  वापस nreverse (ret);
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

अटल वृक्ष
c_parser_omp_context_selector_specification (c_parser *parser, वृक्ष parms)
{
  वृक्ष ret = NULL_वृक्ष;
  करो
    {
      स्थिर अक्षर *setp = "";
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      क्रमागत omp_tss_code set = omp_lookup_tss_code (setp);

      अगर (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  वापस error_mark_गाँठ;
	}

      c_parser_consume_token (parser);

      अगर (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	वापस error_mark_गाँठ;

      matching_braces braces;
      अगर (!braces.require_open (parser))
	वापस error_mark_गाँठ;

      वृक्ष selectors = c_parser_omp_context_selector (parser, set, parms);
      अगर (selectors == error_mark_गाँठ)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_गाँठ;
	}
      अन्यथा अगर (ret != error_mark_गाँठ)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अन्यथा
	अवरोध;
    }
  जबतक (1);

  अगर (ret == error_mark_गाँठ)
    वापस ret;
  वापस nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

अटल व्योम
c_finish_omp_declare_variant (c_parser *parser, वृक्ष fndecl, वृक्ष parms)
{
  matching_parens parens;
  अगर (!parens.require_open (parser))
    {
     हार:
      c_parser_skip_to_pragma_eol (parser, false);
      वापस;
    }

  अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      जाओ हार;
    }

  c_token *token = c_parser_peek_token (parser);
  वृक्ष variant = lookup_name (token->मूल्य);

  अगर (variant == NULL_वृक्ष)
    {
      undeclared_variable (token->location, token->मूल्य);
      variant = error_mark_गाँठ;
    }
  अन्यथा अगर (वृक्ष_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_गाँठ;
    }
  अन्यथा अगर (fndecl_built_in_p (variant)
	   && (म_भेदन (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", म_माप ("__builtin_")) == 0
	       || म_भेदन (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", म_माप ("__sync_")) == 0
	       || म_भेदन (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", म_माप ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_गाँठ;
    }
  अन्यथा अगर (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_गाँठ;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  वृक्ष append_args_वृक्ष = NULL_वृक्ष;
  वृक्ष append_args_last;
  vec<वृक्ष> adjust_args_list = vNULL;
  bool has_match = false, has_adjust_args = false;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  वृक्ष need_device_ptr_list = NULL_वृक्ष;
  वृक्ष ctx = error_mark_गाँठ;

  करो
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      स्थिर अक्षर *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      क्रमागत clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      अगर (म_भेद (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      अन्यथा अगर (म_भेद (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      अन्यथा अगर (म_भेद (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  जाओ हार;
	}

      c_parser_consume_token (parser);

      अगर (!parens.require_open (parser))
	जाओ हार;

      अगर (parms == NULL_वृक्ष)
	parms = error_mark_गाँठ;

      अगर (ccode == match)
	{
	  अगर (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = true;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  अगर (ctx == error_mark_गाँठ)
	    जाओ हार;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  अगर (ctx != error_mark_गाँठ
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      वृक्ष outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      अन्यथा अगर (ccode == adjust_args)
	{
	  has_adjust_args = true;
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      स्थिर अक्षर *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	      अगर (म_भेद (p, "need_device_ptr") == 0
		  || म_भेद (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  वृक्ष list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_वृक्ष);

		  वृक्ष arg;
		  अगर (variant != error_mark_गाँठ)
		    क्रम (वृक्ष c = list; c != NULL_वृक्ष; c = वृक्ष_CHAIN (c))
		      {
			वृक्ष decl = वृक्ष_PURPOSE (c);
			location_t arg_loc = व्यंजक_LOCATION (वृक्ष_मूल्य (c));
			पूर्णांक idx;
			क्रम (arg = parms, idx = 0; arg != शून्य;
			     arg = वृक्ष_CHAIN (arg), idx++)
			  अगर (arg == decl)
			    अवरोध;
			अगर (arg == NULL_वृक्ष)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    जाओ हार;
			  }
			अगर (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    जाओ हार;
			  }
			अगर (म_भेद (p, "need_device_ptr") == 0
			    && वृक्ष_CODE (वृक्ष_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    जाओ हार;
			  }
			adjust_args_list.safe_धकेलो (arg);
			अगर (म_भेद (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_वृक्ष_list (
				NULL_वृक्ष,
				build_int_cst (
				  integer_type_गाँठ,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      अन्यथा
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  अगर (म_भेद (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  जाओ हार;
		}
	    }
	  अन्यथा
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      जाओ हार;
	    }
	}
      अन्यथा अगर (ccode == append_args)
	{
	  अगर (append_args_वृक्ष)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_वृक्ष = NULL_वृक्ष;
	    }
	  करो
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      अगर (!c_parser_अग्र_token_is (parser, CPP_NAME)
		  || म_भेद ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->मूल्य)))
		{
		  error_at (loc, "expected %<interop%>");
		  जाओ हार;
		}
	      c_parser_consume_token (parser);

	      अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		जाओ हार;
	      bool target = false;
	      bool targetsync = false;
	      वृक्ष prefer_type_वृक्ष = NULL_वृक्ष;
	      अगर (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_वृक्ष)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		जाओ हार;
	      अगर (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      वृक्ष t = build_वृक्ष_list (target ? boolean_true_गाँठ
					       : boolean_false_गाँठ,
					targetsync ? boolean_true_गाँठ
						   : boolean_false_गाँठ);
	      t = build1_loc (loc, NOP_व्यंजक, void_type_गाँठ, t);
	      t = build_वृक्ष_list (t, prefer_type_वृक्ष);
	      अगर (append_args_वृक्ष)
		{
		  वृक्ष_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      अन्यथा
		append_args_वृक्ष = append_args_last = t;
	      अगर (c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
		अवरोध;
	      अगर (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		जाओ हार;
	    }
	  जबतक (true);
	}

      parens.require_close (parser);
  } जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL));
  अगर (variant != error_mark_गाँठ && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_गाँठ;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  अगर (variant == error_mark_गाँठ || ctx == error_mark_गाँठ)
    /* Previously diagnosed error.  */
    वापस;

  अगर ((has_adjust_args || append_args_वृक्ष)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      वापस;
    }

  अगर (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      वृक्ष base_type = वृक्ष_TYPE (fndecl);
      वृक्ष variant_type = वृक्ष_TYPE (variant);
      bool unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_वृक्ष
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      अगर (append_args_वृक्ष
	  && TYPE_ARG_TYPES (base_type) == NULL_वृक्ष
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
	  वापस;
	}
      अन्यथा अगर (append_args_वृक्ष)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  पूर्णांक nappend_args = 0;
	  पूर्णांक nbase_args = 0;
	  क्रम (वृक्ष t = TYPE_ARG_TYPES (base_type);
	       t && वृक्ष_मूल्य (t) != void_type_गाँठ; t = वृक्ष_CHAIN (t))
	    nbase_args++;
	  क्रम (वृक्ष t = append_args_वृक्ष; t; t = वृक्ष_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_वृक्ष = build_वृक्ष_list (build_int_cst (integer_type_गाँठ,
							     nbase_args),
					      append_args_वृक्ष);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  अगर (!unprototyped_variant)
	    {
	      वृक्ष args = TYPE_ARG_TYPES (variant_type);
	      क्रम (पूर्णांक i = 0; args && i < nbase_args;
		   i++, args = वृक्ष_CHAIN (args))
		;
	      क्रम (पूर्णांक i = 0; i < nappend_args; i++, args = वृक्ष_CHAIN (args))
		अगर (!args || !c_omp_interop_t_p (वृक्ष_मूल्य (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    वापस;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  वृक्ष args = TYPE_ARG_TYPES (base_type);
	  वृक्ष newargs = NULL_वृक्ष;
	  वृक्ष lastarg = NULL_वृक्ष;
	  क्रम (पूर्णांक j = 0; j < nbase_args; j++, args = वृक्ष_CHAIN (args))
	    {
	      वृक्ष t = वृक्ष_cons (वृक्ष_PURPOSE (args),
				  वृक्ष_मूल्य (args), NULL_वृक्ष);
	      अगर (lastarg)
		वृक्ष_CHAIN (lastarg) = t;
	      अन्यथा
		newargs = t;
	      lastarg = t;
	    }
	  वृक्ष type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? वृक्ष_TYPE (type) : pointer_sized_int_गाँठ;
	  क्रम (पूर्णांक j = 0; j < nappend_args; j++)
	    {
	      वृक्ष t = वृक्ष_cons (NULL_वृक्ष, type, NULL_वृक्ष);
	      अगर (lastarg)
		वृक्ष_CHAIN (lastarg) = t;
	      अन्यथा
		newargs = t;
	      lastarg = t;
	    }
	  वृक्ष_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  वृक्ष saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  bool हार = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  अगर (हार)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      वापस;
	    }
	  अन्यथा अगर (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      अन्यथा  /* No append_args present.  */
	{
	  अगर (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      वापस;
	    }
	  अन्यथा अगर (TYPE_ARG_TYPES (variant_type) == NULL_वृक्ष
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_वृक्ष)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  वृक्ष construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  अगर (omp_context_selector_matches (ctx, NULL_वृक्ष, false))
    {
      वृक्ष attr = वृक्ष_cons (get_identifier ("omp declare variant base"),
			     build_वृक्ष_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  अगर (need_device_ptr_list || append_args_वृक्ष)
    {
      वृक्ष variant_decl = वृक्ष_strip_nop_conversions (variant);
      वृक्ष t = build_वृक्ष_list (need_device_ptr_list,
				NULL_वृक्ष /* need_device_addr */);
      वृक्ष_CHAIN (t) = append_args_वृक्ष;
      DECL_ATTRIBUTES (variant_decl)
	= वृक्ष_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

अटल व्योम
c_finish_omp_declare_simd (c_parser *parser, वृक्ष fndecl, वृक्ष parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  अगर (clauses.exists () && clauses[0].type == CPP_EOF)
    वापस;
  स्थिर अक्षर *kind = "simd";
  अगर (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].मूल्य);
  gcc_assert (म_भेद (kind, "simd") == 0 || म_भेद (kind, "variant") == 0);
  अगर (fndecl == NULL_वृक्ष || वृक्ष_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      वापस;
    }
  अगर (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      वापस;
    }
  अगर (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      वापस;
    }

  अगर (parms == NULL_वृक्ष)
    parms = DECL_ARGUMENTS (fndecl);

  अचिन्हित पूर्णांक tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.लंबाई ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  जबतक (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->मूल्य);
      c_parser_consume_token (parser);
      parser->in_pragma = true;

      अगर (म_भेद (kind, "simd") == 0)
	{
	  वृक्ष c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  अगर (c != NULL_वृक्ष)
	    c = वृक्ष_cons (NULL_वृक्ष, c, NULL_वृक्ष);
	  c = build_वृक्ष_list (get_identifier ("omp declare simd"), c);
	  वृक्ष_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
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
  अगर (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#अगर !defined (NO_DOT_IN_LABEL)
#घोषणा JOIN_STR "."
#या_अगर !defined (NO_DOLLAR_IN_LABEL)
#घोषणा JOIN_STR "$"
#अन्यथा
#घोषणा JOIN_STR "_"
#पूर्ण_अगर

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
अटल वृक्ष
omp_start_variant_function (c_declarator *declarator, वृक्ष ctx)
{
  c_declarator *id = declarator;
  जबतक (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  वृक्ष name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  वापस name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
अटल व्योम
omp_finish_variant_function (वृक्ष decl, वृक्ष base_name, वृक्ष ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  वृक्ष base_decl = lookup_name (base_name);
  अगर (base_decl == error_mark_गाँठ)
    base_decl = NULL_वृक्ष;
  अगर (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      वापस;
    }

  अगर (!comptypes (वृक्ष_TYPE (decl), वृक्ष_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      वापस;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  वृक्ष construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  वृक्ष attrs = DECL_ATTRIBUTES (base_decl);
  वृक्ष match_loc_गाँठ
    = maybe_wrap_with_location (integer_zero_गाँठ,
				DECL_SOURCE_LOCATION (base_decl));
  वृक्ष loc_गाँठ = वृक्ष_cons (match_loc_गाँठ, integer_zero_गाँठ,
			     build_वृक्ष_list (match_loc_गाँठ,
					      integer_zero_गाँठ));
  attrs = वृक्ष_cons (get_identifier ("omp declare variant base"),
		     वृक्ष_cons (decl, ctx, loc_गाँठ), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  वृक्ष_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

bool
c_maybe_parse_omp_decl (वृक्ष decl, वृक्ष d)
{
  gcc_assert (वृक्ष_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->लंबाई ();
  स्थिर अक्षर *directive[3] = {};
  क्रम (पूर्णांक j = 0; j < 3; j++)
    {
      वृक्ष id = NULL_वृक्ष;
      अगर (first + j == last)
	अवरोध;
      अगर (first[j].type == CPP_NAME)
	id = first[j].मूल्य;
      अन्यथा अगर (first[j].type == CPP_KEYWORD)
	id = ridpointers[(पूर्णांक) first[j].keyword];
      अन्यथा
	अवरोध;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  स्थिर c_omp_directive *dir = शून्य;
  अगर (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  अगर (dir == शून्य)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      वापस false;
    }
  अगर (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || म_भेद (directive[1], "target") != 0))
    वापस false;

  अगर (!flag_openmp && !dir->simd)
    वापस true;

  c_parser *parser = the_parser;
  अचिन्हित पूर्णांक tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = शून्य;
  vec_safe_reserve (toks, last - first + 2, true);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_धकेलो (tok);
  जबतक (++first < last)
    toks->quick_धकेलो (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_धकेलो (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_धकेलो (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->लंबाई ();
  c_parser_pragma (parser, pragma_external, शून्य, NULL_वृक्ष);
  parser->in_omp_decl_attribute = NULL_वृक्ष;
  वापस true;
}

/* OpenMP 4.0:
   # pragma omp declare target new-line
   declarations and definitions
   # pragma omp end declare target new-line

   OpenMP 4.5:
   # pragma omp declare target ( extended-list ) new-line

   # pragma omp declare target declare-target-clauses[seq] new-line  */

#घोषणा OMP_DECLARE_TARGET_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_TO)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ENTER)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LOCAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INDIRECT))

अटल व्योम
c_parser_omp_declare_target (c_parser *parser)
{
  वृक्ष clauses = NULL_वृक्ष;
  पूर्णांक device_type = 0;
  bool indirect = false;
  bool only_device_type_or_indirect = true;
  अगर (flag_openmp)
    omp_requires_mask
      = (क्रमागत omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
      || (c_parser_अग्र_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  अन्यथा अगर (parser->in_omp_decl_attribute
	   || c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
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
      bool attr_syntax = parser->in_omp_attribute_pragma != शून्य;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_धकेलो (current_omp_declare_target_attribute, attr);
      वापस;
    }
  क्रम (वृक्ष c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_व्यंजक (c));
    }
  क्रम (वृक्ष c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	जारी;
      वृक्ष t = OMP_CLAUSE_DECL (c), id;
      वृक्ष at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      वृक्ष at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = false;
      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      अन्यथा
	id = get_identifier ("omp declare target");
      अगर (at2)
	{
	  अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  अन्यथा अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || मूल्य_member (get_identifier ("local"), वृक्ष_मूल्य (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  अन्यथा
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  जारी;
	}
      अगर (!at1)
	{
	  DECL_ATTRIBUTES (t) = वृक्ष_cons (id, NULL_वृक्ष, DECL_ATTRIBUTES (t));
	  अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    वृक्ष_मूल्य (DECL_ATTRIBUTES (t))
	      = वृक्ष_cons (NULL_वृक्ष, get_identifier ("local"),
			   वृक्ष_मूल्य (DECL_ATTRIBUTES (t)));

	  अगर (वृक्ष_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    जारी;

	  symtab_गाँठ *गाँठ = symtab_गाँठ::लो (t);
	  अगर (गाँठ != शून्य)
	    {
	      गाँठ->offloadable = 1;
	      अगर (ENABLE_OFFLOADING)
		{
		  g->have_offload = true;
		  अगर (is_a <varpool_गाँठ *> (गाँठ)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_धकेलो (offload_vars, t);
		}
	    }
	}
      अन्यथा
	{
	  bool saw_local = मूल्य_member (get_identifier ("local"),
					 वृक्ष_मूल्य (at1));
	  अगर (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      जारी;
	    }
	  अन्यथा अगर (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      जारी;
	    }
	}
      अगर (वृक्ष_CODE (t) != FUNCTION_DECL)
	जारी;
      अगर ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  वृक्ष at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  अगर (at3 == NULL_वृक्ष)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= वृक्ष_cons (id, NULL_वृक्ष, DECL_ATTRIBUTES (t));
	    }
	}
      अगर ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  वृक्ष at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  अगर (at3 == NULL_वृक्ष)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= वृक्ष_cons (id, NULL_वृक्ष, DECL_ATTRIBUTES (t));
	    }
	}
      अगर (indirect)
	{
	  वृक्ष at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  अगर (at4 == NULL_वृक्ष)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= वृक्ष_cons (id, NULL_वृक्ष, DECL_ATTRIBUTES (t));
	    }
	}
    }
  अगर ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  अगर (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "%<device_type%> clause must specify 'any' when used with "
	      "an %<indirect%> clause");
}

/* OpenMP 5.1
   #pragma omp begin assumes clauses[optseq] new-line

   #pragma omp begin declare target clauses[optseq] new-line

   #pragma omp begin declare variant match (context-selector) new-line  */

#घोषणा OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_INDIRECT))

अटल व्योम
c_parser_omp_begin (c_parser *parser)
{
  स्थिर अक्षर *p = "";
  c_parser_consume_pragma (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
  अगर (म_भेद (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  bool attr_syntax = parser->in_omp_attribute_pragma != शून्य;
	  वृक्ष clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  पूर्णांक device_type = 0;
	  पूर्णांक indirect = 0;
	  क्रम (वृक्ष c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_व्यंजक (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_धकेलो (current_omp_declare_target_attribute, attr);
	}
      अन्यथा अगर (म_भेद (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  स्थिर अक्षर *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  अगर (म_भेद (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      वापस;
	    }

	  c_parser_consume_token (parser);

	  अगर (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, false);
	      वापस;
	    }

	  वृक्ष ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_वृक्ष);
	  अगर (ctx != error_mark_गाँठ)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  अगर (ctx != error_mark_गाँठ
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      वृक्ष outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  अगर (ctx == error_mark_गाँठ
	      || !omp_context_selector_matches (ctx, NULL_वृक्ष, false, true))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, false);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      वापस;
	    }
	  अन्यथा
	    {
	      bool attr_syntax = parser->in_omp_attribute_pragma != शून्य;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_धकेलो (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      अन्यथा
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, false);
	}
    }
  अन्यथा अगर (म_भेद (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      bool attr_syntax = parser->in_omp_attribute_pragma != शून्य;
      c_parser_omp_assumption_clauses (parser, false);
      काष्ठा c_omp_begin_assumes_तथ्य a = { attr_syntax };
      vec_safe_धकेलो (current_omp_begin_assumes, a);
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

अटल व्योम
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  स्थिर अक्षर *p = "";
  c_parser_consume_pragma (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
  अगर (म_भेद (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  bool attr_syntax = parser->in_omp_attribute_pragma != शून्य;
	  c_parser_skip_to_pragma_eol (parser);
	  अगर (!vec_safe_लंबाई (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  अन्यथा
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->निकालो ();
	      अगर (a.attr_syntax != attr_syntax)
		{
		  अगर (a.attr_syntax)
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
      अन्यथा अगर (म_भेद (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  bool attr_syntax = parser->in_omp_attribute_pragma != शून्य;
	  c_parser_skip_to_pragma_eol (parser);
	  अगर (!vec_safe_लंबाई (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  अन्यथा
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->निकालो ();
	      अगर (a.attr_syntax != attr_syntax)
		{
		  अगर (a.attr_syntax)
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
	  वापस;
	}
    }
  अन्यथा अगर (म_भेद (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      bool attr_syntax = parser->in_omp_attribute_pragma != शून्य;
      c_parser_skip_to_pragma_eol (parser);
      अगर (!vec_safe_लंबाई (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      अन्यथा
	{
	  c_omp_begin_assumes_तथ्य
	    a = current_omp_begin_assumes->निकालो ();
	  अगर (a.attr_syntax != attr_syntax)
	    {
	      अगर (a.attr_syntax)
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

अटल व्योम
c_parser_omp_declare_mapper (c_parser *parser, क्रमागत pragma_context context)
{
  वृक्ष type, mapper_name = NULL_वृक्ष, var = NULL_वृक्ष, stmt, stmtlist;
  वृक्ष maplist = NULL_वृक्ष, mapper_id, mapper_decl, t;
  c_token *token;

  अगर (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      जाओ हार;
    }

  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    जाओ हार;

  token = c_parser_peek_token (parser);

  अगर (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      चयन (token->type)
	{
	हाल CPP_NAME:
	  mapper_name = token->मूल्य;
	  c_parser_consume_token (parser);
	  अवरोध;
	हाल CPP_KEYWORD:
	  अगर (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_वृक्ष;
	      c_parser_consume_token (parser);
	      अवरोध;
	    }
	  /* Fallthrough.  */
	शेष:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, false);
	  वापस;
	}

      अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	जाओ हार;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    काष्ठा c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, शून्य, शून्य);
    अगर (type == error_mark_गाँठ)
      जाओ हार;
    अगर (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, false);
	वापस;
      }
    क्रम (वृक्ष t = DECL_INITIAL (mapper_decl); t; t = वृक्ष_CHAIN (t))
      अगर (comptypes (वृक्ष_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + माप ("omp declare mapper ") - 1,
		    type);
	  वृक्ष prevmapper = वृक्ष_मूल्य (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, false);
	  वापस;
	}
  }

  token = c_parser_peek_token (parser);
  अगर (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->मूल्य, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  अन्यथा
    {
      error_at (token->location, "expected identifier");
      जाओ हार;
    }

  अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    जाओ हार;

  धकेलो_scope ();
  stmtlist = धकेलो_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      अगर (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  जाओ हार;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, true);
    }

  अगर (maplist == NULL_वृक्ष)
    {
      error_at (निवेश_location, "missing %<map%> clause");
      जाओ हार;
    }
  वृक्ष list;
  क्रम (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      वृक्ष dvar = OMP_CLAUSE_DECL (list);
      जबतक (!DECL_P (dvar) && वृक्ष_OPERAND_लंबाई (dvar))
	dvar = वृक्ष_OPERAND (dvar, 0);
      अगर (dvar == var)
	अवरोध;
    }
  अगर (!list)
    error_at (निवेश_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_गाँठ (OMP_DECLARE_MAPPER);
  वृक्ष_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  निकालो_stmt_list (stmtlist);
  निकालो_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = वृक्ष_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  वापस;

 हार:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

अटल व्योम
c_parser_omp_declare_reduction (c_parser *parser, क्रमागत pragma_context context)
{
  अचिन्हित पूर्णांक tokens_avail = 0, i;
  c_token *saved_tokens = शून्य;
  vec<वृक्ष> types = vNULL;
  vec<c_token> clauses = vNULL;
  क्रमागत वृक्ष_code reduc_code = ERROR_MARK;
  वृक्ष reduc_id = NULL_वृक्ष;
  वृक्ष type;
  location_t rloc = c_parser_peek_token (parser)->location;

  अगर (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      जाओ हार;
    }

  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    जाओ हार;

  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_PLUS:
      reduc_code = PLUS_व्यंजक;
      अवरोध;
    हाल CPP_MULT:
      reduc_code = MULT_व्यंजक;
      अवरोध;
    हाल CPP_MINUS:
      reduc_code = MINUS_व्यंजक;
      अवरोध;
    हाल CPP_AND:
      reduc_code = BIT_AND_व्यंजक;
      अवरोध;
    हाल CPP_XOR:
      reduc_code = BIT_XOR_व्यंजक;
      अवरोध;
    हाल CPP_OR:
      reduc_code = BIT_IOR_व्यंजक;
      अवरोध;
    हाल CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_व्यंजक;
      अवरोध;
    हाल CPP_OR_OR:
      reduc_code = TRUTH_ORIF_व्यंजक;
      अवरोध;
    हाल CPP_NAME:
      स्थिर अक्षर *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "min") == 0)
	{
	  reduc_code = MIN_व्यंजक;
	  अवरोध;
	}
      अगर (म_भेद (p, "max") == 0)
	{
	  reduc_code = MAX_व्यंजक;
	  अवरोध;
	}
      reduc_id = c_parser_peek_token (parser)->मूल्य;
      अवरोध;
    शेष:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      जाओ हार;
    }

  वृक्ष orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    जाओ हार;

  जबतक (true)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      काष्ठा c_type_name *ctype = c_parser_type_name (parser);
      अगर (ctype != शून्य)
	{
	  type = groktypename (ctype, शून्य, शून्य);
	  अगर (type == error_mark_गाँठ)
	    ;
	  अन्यथा अगर ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || वृक्ष_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_वृक्ष)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  अन्यथा अगर (वृक्ष_CODE (type) == FUNCTION_TYPE
		   || वृक्ष_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  अन्यथा अगर (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  अन्यथा अगर (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  अन्यथा
	    {
	      वृक्ष t;
	      क्रम (t = DECL_INITIAL (reduc_decl); t; t = वृक्ष_CHAIN (t))
		अगर (comptypes (वृक्ष_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + माप ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (वृक्ष_VEC_ELT (वृक्ष_मूल्य (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    अवरोध;
		  }
	      अगर (t == NULL_वृक्ष)
		types.safe_धकेलो (type);
	    }
	  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    अवरोध;
	}
      अन्यथा
	अवरोध;
    }

  अगर (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     हार:
      clauses.release ();
      types.release ();
      जबतक (true)
	{
	  c_token *token = c_parser_peek_token (parser);
	  अगर (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    अवरोध;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      वापस;
    }

  अगर (types.लंबाई () > 1)
    {
      जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  अगर (token->type == CPP_EOF)
	    जाओ हार;
	  clauses.safe_धकेलो (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_धकेलो (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      स_रखो (&eof_token, 0, माप (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_धकेलो (eof_token);
      clauses.safe_धकेलो (eof_token);
    }

  पूर्णांक errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      अगर (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.लंबाई ();
	  parser->in_pragma = true;
	}

      bool nested = current_function_decl != NULL_वृक्ष;
      अगर (nested)
	c_धकेलो_function_context ();
      वृक्ष fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, true);
      धकेलो_scope ();
      वृक्ष stmt = धकेलो_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      वृक्ष omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      वृक्ष omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      काष्ठा c_व्यंजक combiner = c_parser_expression (parser);
      काष्ठा c_व्यंजक initializer;
      वृक्ष omp_priv = NULL_वृक्ष, omp_orig = NULL_वृक्ष;
      bool बुरा = false;
      initializer.set_error ();
      अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	बुरा = true;
      अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      अगर (!बुरा
	  && (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && म_भेद (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->मूल्य),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  निकालो_scope ();
	  धकेलो_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_गाँठ;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    बुरा = true;
	  अन्यथा अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      बुरा = true;
	    }
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->मूल्य),
			   "omp_priv") != 0)
	    {
	      अगर (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  बुरा = true;
		}
	      अन्यथा
		initializer = c_parser_postfix_expression (parser);
	      अगर (initializer.मूल्य
		  && वृक्ष_CODE (initializer.मूल्य) == CALL_व्यंजक)
		{
		  पूर्णांक j;
		  वृक्ष c = initializer.मूल्य;
		  क्रम (j = 0; j < call_व्यंजक_nargs (c); j++)
		    {
		      वृक्ष a = CALL_व्यंजक_ARG (c, j);
		      STRIP_NOPS (a);
		      अगर (वृक्ष_CODE (a) == ADDR_व्यंजक
			  && वृक्ष_OPERAND (a, 0) == omp_priv)
			अवरोध;
		    }
		  अगर (j == call_व्यंजक_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  अन्यथा
	    {
	      c_parser_consume_token (parser);
	      अगर (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		बुरा = true;
	      अन्यथा
		{
		  वृक्ष st = धकेलो_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (पंक्ति_table, loc);
		  start_init (omp_priv, NULL_वृक्ष, false, false, &richloc);
		  काष्ठा c_व्यंजक init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.मूल्य,
		      	       init.original_type, NULL_वृक्ष);
		  निकालो_stmt_list (st);
		}
	    }
	  अगर (!बुरा
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    बुरा = true;
	}

      अगर (!बुरा)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  वृक्ष t = वृक्ष_cons (type, make_वृक्ष_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 0) = omp_out;
	  वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 1) = omp_in;
	  वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 2) = combiner.मूल्य;
	  walk_वृक्ष (&combiner.मूल्य, c_check_omp_declare_reduction_r,
		     &वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 0), शून्य);
	  अगर (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 3) = omp_priv;
	      वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 4) = omp_orig;
	      वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 5) = initializer.मूल्य;
	      walk_वृक्ष (&initializer.मूल्य, c_check_omp_declare_reduction_r,
			 &वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 3), शून्य);
	      walk_वृक्ष (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &वृक्ष_VEC_ELT (वृक्ष_मूल्य (t), 3), शून्य);
	    }
	}

      निकालो_stmt_list (stmt);
      निकालो_scope ();
      अगर (cfun->language != शून्य)
	{
	  ggc_free (cfun->language);
	  cfun->language = शून्य;
	}
      set_cfun (शून्य);
      current_function_decl = NULL_वृक्ष;
      अगर (nested)
	c_निकालो_function_context ();

      अगर (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      अगर (बुरा)
	जाओ हार;
      अगर (errs != errorcount)
	अवरोध;
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

अटल bool
c_parser_omp_declare (c_parser *parser, क्रमागत pragma_context context)
{
  c_parser_consume_pragma (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  वापस true;
	}
      अगर (म_भेद (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  वापस false;
	}
      अगर (म_भेद (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  वापस false;
	}
      अगर (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, false);
	  वापस false;
	}
      अगर (म_भेद (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  वापस false;
	}
      अगर (म_भेद (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  वापस true;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  वापस false;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

अटल व्योम
c_parser_omp_requires (c_parser *parser)
{
  क्रमागत omp_requires new_req = (क्रमागत omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  स्थिर अक्षर *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  क्रमागत omp_requires this_req = (क्रमागत omp_requires) 0;

	  अगर (!म_भेद (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  अन्यथा अगर (!म_भेद (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  अन्यथा अगर (!म_भेद (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  अन्यथा अगर (!म_भेद (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  अन्यथा अगर (!म_भेद (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  अन्यथा अगर (!म_भेद (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      अगर (parens.require_open (parser))
		{
		  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		    {
		      वृक्ष v = c_parser_peek_token (parser)->मूल्य;
		      p = IDENTIFIER_POINTER (v);

		      अगर (!म_भेद (p, "seq_cst"))
			this_req
			  = (क्रमागत omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      अन्यथा अगर (!म_भेद (p, "relaxed"))
			this_req
			  = (क्रमागत omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      अन्यथा अगर (!म_भेद (p, "release"))
			this_req
			  = (क्रमागत omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      अन्यथा अगर (!म_भेद (p, "acq_rel"))
			this_req
			  = (क्रमागत omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      अन्यथा अगर (!म_भेद (p, "acquire"))
			this_req
			  = (क्रमागत omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  अगर (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      चयन (c_parser_peek_token (parser)->type)
			{
			हाल CPP_EOF:
			हाल CPP_PRAGMA_EOL:
			हाल CPP_CLOSE_PAREN:
			  अवरोध;
			शेष:
			  अगर (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  अवरोध;
			}
		    }
		  अन्यथा
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  अगर (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, false);
		      वापस;
		    }
		}
	      p = शून्य;
	    }
	  अन्यथा
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, false);
	      वापस;
	    }
	  अगर (p)
	    c_parser_consume_token (parser);
	  अगर (this_req)
	    {
	      अगर ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  अगर ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  अगर (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      अन्यथा अगर ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (क्रमागत omp_requires) 0;
		}
	      अन्यथा अगर ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (क्रमागत omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      अन्यथा अगर ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (क्रमागत omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (क्रमागत omp_requires) (omp_requires_mask | this_req);
	      जारी;
	    }
	}
      अवरोध;
    }
  c_parser_skip_to_pragma_eol (parser);

  अगर (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

अटल वृक्ष
c_finish_taskloop_clauses (वृक्ष clauses)
{
  वृक्ष *pc = &clauses;
  क्रम (वृक्ष c = clauses; c; c = *pc)
    {
      bool हटाओ = false;
      अगर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  वृक्ष type = strip_array_types (वृक्ष_TYPE (OMP_CLAUSE_DECL (c)));
	  अगर (integer_zerop (TYPE_आकार_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      हटाओ = true;
	    }
	  अन्यथा अगर (वृक्ष_CODE (TYPE_आकार_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      हटाओ = true;
	    }
	}
      अगर (हटाओ)
	*pc = OMP_CLAUSE_CHAIN (c);
      अन्यथा
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  वापस clauses;
}

/* OpenMP 4.5:
   #pragma omp taskloop taskloop-clause[optseq] new-line
     for-loop

   #pragma omp taskloop simd taskloop-simd-clause[optseq] new-line
     for-loop  */

#घोषणा OMP_TASKLOOP_CLAUSE_MASK				\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_GRAINSIZE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अंक_TASKS)	\
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

अटल वृक्ष
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       अक्षर *p_name, omp_clause_mask mask, वृक्ष *cclauses,
		       bool *if_p)
{
  वृक्ष clauses, block, ret;

  म_जोड़ो (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  अगर ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_अंक_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);

      अगर (म_भेद (p, "simd") == 0)
	{
	  वृक्ष cclauses_buf[C_OMP_CLAUSE_SPLIT_गिनती];
	  अगर (cclauses == शून्य)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  अगर (!flag_openmp)  /* flag_openmp_simd  */
	    वापस c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (true);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, true);
	  अगर (ret == शून्य)
	    वापस ret;
	  ret = make_गाँठ (OMP_TASKLOOP);
	  वृक्ष_TYPE (ret) = void_type_गाँठ;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_व्यंजक_LOCATION (ret, loc);
	  add_stmt (ret);
	  वापस ret;
	}
    }
  अगर (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, false);
      वापस NULL_वृक्ष;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == शून्य);
  अगर (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (true);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, शून्य, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
अटल वृक्ष
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  वृक्ष sizes = NULL_वृक्ष;

  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  अगर (tok->type != CPP_NAME
      || म_भेद ("sizes", IDENTIFIER_POINTER (tok->मूल्य)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      वापस error_mark_गाँठ;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  अगर (!parens.require_open (parser))
    वापस error_mark_गाँठ;

  vec<वृक्ष, va_gc> *sizes_vec
    = c_parser_व्यंजक_list (parser, true, true, शून्य, शून्य, शून्य, शून्य);
  sizes = build_वृक्ष_list_vec (sizes_vec);
  release_वृक्ष_vector (sizes_vec);

  क्रम (वृक्ष s = sizes; s; s = वृक्ष_CHAIN (s))
    {
      वृक्ष व्यंजक = वृक्ष_मूल्य (s);
      अगर (व्यंजक == error_mark_गाँठ)
	{
	  parens.skip_until_found_close (parser);
	  वापस error_mark_गाँठ;
	}

      HOST_WIDE_INT n;
      अगर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (व्यंजक))
	  || !वृक्ष_fits_shwi_p (व्यंजक)
	  || (n = वृक्ष_to_shwi (व्यंजक)) <= 0
	  || (पूर्णांक) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  वृक्ष_मूल्य (s) = integer_one_गाँठ;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  वृक्ष c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  वापस c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

अटल वृक्ष
c_parser_omp_tile (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  अगर (!clauses || clauses == error_mark_गाँठ)
    वापस error_mark_गाँठ;

  वृक्ष block = c_begin_compound_stmt (true);
  वृक्ष ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    शून्य, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस ret;
}

#घोषणा OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

अटल वृक्ष
c_parser_omp_unroll (location_t loc, c_parser *parser, bool *if_p)
{
  वृक्ष clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", true);

  वृक्ष block = c_begin_compound_stmt (true);
  वृक्ष ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    शून्य, if_p);
  block = c_end_compound_stmt (loc, block, true);
  add_stmt (block);

  वापस ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

अटल व्योम
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

अटल bool
c_parser_omp_error (c_parser *parser, क्रमागत pragma_context context)
{
  पूर्णांक at_compilation = -1;
  पूर्णांक severity_fatal = -1;
  वृक्ष message = NULL_वृक्ष;
  bool बुरा = false;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
	अवरोध;

      स्थिर अक्षर *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      location_t cloc = c_parser_peek_token (parser)->location;
      अटल स्थिर अक्षर *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      पूर्णांक *v = शून्य;
      पूर्णांक idx = 0, n = -1;
      वृक्ष m = NULL_वृक्ष;

      अगर (!म_भेद (p, "at"))
	v = &at_compilation;
      अन्यथा अगर (!म_भेद (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      अन्यथा अगर (म_भेद (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, false);
	  वापस false;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      अगर (parens.require_open (parser))
	{
	  अगर (v == शून्य)
	    {
	      location_t व्यंजक_loc = c_parser_peek_token (parser)->location;
	      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	      व्यंजक = convert_lvalue_to_rvalue (व्यंजक_loc, व्यंजक, true, true);
	      m = convert (const_string_type_गाँठ, व्यंजक.मूल्य);
	      m = c_fully_fold (m, false, शून्य);
	    }
	  अन्यथा
	    {
	      अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		{
		  वृक्ष val = c_parser_peek_token (parser)->मूल्य;
		  स्थिर अक्षर *q = IDENTIFIER_POINTER (val);

		  अगर (!म_भेद (q, args[idx]))
		    n = 0;
		  अन्यथा अगर (!म_भेद (q, args[idx + 1]))
		    n = 1;
		}
	      अगर (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  बुरा = true;
		  चयन (c_parser_peek_token (parser)->type)
		    {
		    हाल CPP_EOF:
		    हाल CPP_PRAGMA_EOL:
		    हाल CPP_CLOSE_PAREN:
		      अवरोध;
		    शेष:
		      अगर (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      अवरोध;
		    }
		}
	      अन्यथा
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  अगर (v == शून्य)
	    {
	      अगर (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  बुरा = true;
		}
	      अन्यथा
		message = m;
	    }
	  अन्यथा अगर (n != -1)
	    {
	      अगर (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  बुरा = true;
		}
	      अन्यथा
		*v = n;
	    }
	}
      अन्यथा
	बुरा = true;
    }
  c_parser_skip_to_pragma_eol (parser);
  अगर (बुरा)
    वापस true;

  अगर (at_compilation == -1)
    at_compilation = 1;
  अगर (severity_fatal == -1)
    severity_fatal = 1;
  अगर (!at_compilation)
    {
      अगर (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  वापस true;
	}
      अगर (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->हार = true;
	  वापस true;
	}
      वृक्ष fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      अगर (!message)
	message = build_zero_cst (const_string_type_गाँठ);
      वृक्ष stmt = build_call_व्यंजक_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (आकार_type_गाँठ));
      add_stmt (stmt);
      वापस true;
    }
  स्थिर अक्षर *संदेश = शून्य;
  अगर (message)
    {
      संदेश = c_getstr (message);
      अगर (संदेश == शून्य)
	संदेश = _("<message unknown at compile time>");
    }
  स्थिर क्रमागत diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  अगर (संदेश)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", संदेश);
  अन्यथा
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  वापस false;
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

अटल व्योम
c_parser_omp_assumption_clauses (c_parser *parser, bool is_assume)
{
  bool no_openmp = false;
  bool no_openmp_constructs = false;
  bool no_openmp_routines = false;
  bool no_parallelism = false;
  bitmap_शीर्ष absent_शीर्ष, contains_शीर्ष;

  bitmap_obstack_initialize (शून्य);
  bitmap_initialize (&absent_शीर्ष, &bitmap_default_obstack);
  bitmap_initialize (&contains_शीर्ष, &bitmap_default_obstack);

  अगर (c_parser_अग्र_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
	अवरोध;

      स्थिर अक्षर *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      location_t cloc = c_parser_peek_token (parser)->location;

      अगर (!म_भेद (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  अगर (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = true;
	}
      अन्यथा अगर (!म_भेद (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  अगर (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = true;
	}
      अन्यथा अगर (!म_भेद (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  अगर (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = true;
	}
      अन्यथा अगर (!म_भेद (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  अगर (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = true;
	}
      अन्यथा अगर (!म_भेद (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  अगर (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_व्यंजक व्यंजक = c_parser_व्यंजक_no_commas (parser, शून्य);
	      वृक्ष t = convert_lvalue_to_rvalue (eloc, व्यंजक, true, true).मूल्य;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, false, शून्य);
	      अगर (is_assume && t != error_mark_गाँठ)
		{
		  वृक्ष fn = build_call_व्यंजक_internal_loc (eloc, IFN_ASSUME,
							  void_type_गाँठ, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      अन्यथा अगर (!म_भेद (p, "absent") || !म_भेद (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  अगर (parens.require_open (parser))
	    {
	      करो
		{
		  स्थिर अक्षर *directive[3] = {};
		  पूर्णांक i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  क्रम (i = 0; i < 3; i++)
		    {
		      वृक्ष id;
		      अगर (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->मूल्य;
		      अन्यथा अगर (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  क्रमागत rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      अन्यथा
			अवरोध;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  अगर (i == 0)
		    error_at (dloc, "expected directive name");
		  अन्यथा
		    {
		      स्थिर काष्ठा c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      अगर (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      अन्यथा अगर (dir == शून्य
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      अन्यथा
			{
			  पूर्णांक id = dir - c_omp_directives;
			  अगर (bitmap_bit_p (p[0] == 'a' ? &contains_शीर्ष
							: &absent_शीर्ष, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  अन्यथा अगर (!bitmap_set_bit (p[0] == 'a'
						    ? &absent_शीर्ष
						    : &contains_शीर्ष, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned multiple times in %qs "
					    "clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "", p);
			}
		      क्रम (; i; --i)
			c_parser_consume_token (parser);
		    }
		  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  अन्यथा
		    अवरोध;
		}
	      जबतक (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      अन्यथा अगर (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
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
	  अवरोध;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

अटल व्योम
c_parser_omp_assume (c_parser *parser, bool *if_p)
{
  c_parser_omp_assumption_clauses (parser, true);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

अटल व्योम
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, false);
}

/* Helper function for c_parser_omp_metadirective.  */

अटल व्योम
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<वृक्ष> &labels)
{
  पूर्णांक nesting_depth = 0;
  पूर्णांक bracket_depth = 0;
  bool ignore_label = false;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  जबतक (1)
    {
      c_token *token = c_parser_peek_token (parser);
      bool stop = false;

      अगर (c_parser_अग्र_token_is_keyword (parser, RID_CASE))
	ignore_label = true;

      चयन (token->type)
	{
	हाल CPP_EOF:
	  अवरोध;
	हाल CPP_NAME:
	  अगर (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_धकेलो (token->मूल्य);
	  जाओ add;
	हाल CPP_OPEN_BRACE:
	  ++nesting_depth;
	  जाओ add;
	हाल CPP_CLOSE_BRACE:
	  अगर (--nesting_depth == 0 && bracket_depth == 0)
	    stop = true;
	  जाओ add;
	हाल CPP_OPEN_PAREN:
	  ++bracket_depth;
	  जाओ add;
	हाल CPP_CLOSE_PAREN:
	  --bracket_depth;
	  जाओ add;
	हाल CPP_COLON:
	  ignore_label = false;
	  जाओ add;
	हाल CPP_SEMICOLON:
	  अगर (nesting_depth == 0 && bracket_depth == 0)
	    stop = true;
	  जाओ add;
	शेष:
	add:
	  tokens.safe_धकेलो (*token);
	  अगर (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  अन्यथा अगर (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  अन्यथा
	    c_parser_consume_token (parser);
	  अगर (stop)
	    अवरोध;
	  जारी;
	}
      अवरोध;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

अटल व्योम
c_parser_omp_metadirective (c_parser *parser, bool *if_p)
{
  अटल अचिन्हित पूर्णांक metadirective_region_गिनती = 0;

  वृक्ष ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<वृक्ष> body_labels;
  auto_vec<स्थिर काष्ठा c_omp_directive *> directives;
  auto_vec<वृक्ष> ctxs;
  vec<काष्ठा omp_variant> candidates;
  bool default_seen = false;
  पूर्णांक directive_token_idx = 0;
  वृक्ष standalone_body = NULL_वृक्ष;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  bool requires_body = false;

  ret = make_गाँठ (OMP_METADIRECTIVE);
  SET_व्यंजक_LOCATION (ret, pragma_loc);
  वृक्ष_TYPE (ret) = void_type_गाँठ;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_वृक्ष;

  c_parser_consume_pragma (parser);
  जबतक (c_parser_अग्र_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      अगर (c_parser_अग्र_token_is_not (parser, CPP_NAME)
	  && c_parser_अग्र_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  जाओ error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      स्थिर अक्षर *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      अगर (म_भेद (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      bool default_p
	= म_भेद (p, "default") == 0 || म_भेद (p, "otherwise") == 0;
      अगर (default_p)
	{
	  अगर (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      जाओ error;
	    }
	  default_seen = true;
	}
      अन्यथा अगर (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  जाओ error;
	}
      अगर (!default_p && म_भेद (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  जाओ error;
	}

      matching_parens parens;
      वृक्ष ctx = NULL_वृक्ष;
      bool skip = false;

      अगर (!parens.require_open (parser))
	जाओ error;

      अगर (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_वृक्ष);
	  अगर (ctx == error_mark_गाँठ)
	    जाओ error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  अगर (ctx == error_mark_गाँठ)
	    जाओ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_वृक्ष, false) == 0);

	  अगर (c_parser_अग्र_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      जाओ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      स्थिर अक्षर *directive[3] = {};
      पूर्णांक i;
      क्रम (i = 0; i < 3; i++)
	{
	  वृक्ष id;
	  अगर (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      अगर (i == 0)
		directive[i++] = "nothing";
	      अवरोध;
	    }
	  अन्यथा अगर (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->मूल्य;
	  अन्यथा अगर (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      क्रमागत rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  अन्यथा
	    अवरोध;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      अगर (i == 0)
	{
	  error_at (loc, "expected directive name");
	  जाओ error;
	}

      स्थिर काष्ठा c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      अगर (omp_directive == शून्य)
	{
	  क्रम (पूर्णांक j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  जाओ error;
	}
      अन्यथा
	{
	  पूर्णांक token_गिनती = 0;
	  अगर (omp_directive->first) token_गिनती++;
	  अगर (omp_directive->second) token_गिनती++;
	  अगर (omp_directive->third) token_गिनती++;
	  क्रम (पूर्णांक j = 0; j < token_गिनती; j++)
	    c_parser_consume_token (parser);
	}
      अगर (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  जाओ error;
	}
      अगर (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  जाओ error;
	}
      अगर (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = true;

      अगर (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (क्रमागत pragma_kind) omp_directive->id;

	  directives.safe_धकेलो (omp_directive);
	  directive_tokens.safe_धकेलो (pragma_token);
	  ctxs.safe_धकेलो (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      पूर्णांक nesting_depth = 0;
      जबतक (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  चयन (token->type)
	    {
	    हाल CPP_EOF:
	    हाल CPP_PRAGMA_EOL:
	      अवरोध;
	    हाल CPP_OPEN_PAREN:
	      ++nesting_depth;
	      जाओ add;
	    हाल CPP_CLOSE_PAREN:
	      अगर (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  अवरोध;
		}
	      जाओ add;
	    शेष:
	    add:
	      अगर (!skip)
		directive_tokens.safe_धकेलो (*token);
	      c_parser_consume_token (parser);
	      जारी;
	    }
	  अवरोध;
	}

      अगर (!skip)
	{
	  c_token eol_token;
	  स_रखो (&eol_token, 0, माप (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_धकेलो (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  अगर (ctxs.लंबाई () == 1)
    {
      वृक्ष ctx = ctxs[0];
      अगर (ctx == NULL_वृक्ष
	  || (omp_context_selector_matches (ctx, NULL_वृक्ष, false) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	वापस;
    }

  अगर (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      स्थिर काष्ठा c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", शून्य, शून्य);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_धकेलो (omp_directive);
      directive_tokens.safe_धकेलो (pragma_token);
      ctxs.safe_धकेलो (NULL_वृक्ष);

      c_token eol_token;
      स_रखो (&eol_token, 0, माप (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_धकेलो (eol_token);
    }

  अगर (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  अचिन्हित i;
  वृक्ष ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      करो
	tokens.safe_धकेलो (directive_tokens [directive_token_idx++]);
      जबतक (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      क्रम (अचिन्हित j = 0; j < body_tokens.लंबाई (); j++)
	tokens.safe_धकेलो (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      स_रखो (&eof_token, 0, माप (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_धकेलो (eof_token);
      tokens.safe_धकेलो (eof_token);

      अचिन्हित पूर्णांक old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      काष्ठा omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      काष्ठा omp_metadirective_parse_तथ्य *old_state
	= parser->omp_metadirective_state;

      काष्ठा omp_metadirective_parse_तथ्य new_state;
      new_state.body_labels = &body_labels;
      new_state.region_अंक = ++metadirective_region_गिनती;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.लंबाई ();
      parser->in_omp_attribute_pragma = शून्य;
      parser->omp_metadirective_state = &new_state;

      पूर्णांक पूर्व_errorcount = errorcount;
      वृक्ष directive = c_begin_compound_stmt (true);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_वृक्ष);
      directive = c_end_compound_stmt (pragma_loc, directive, true);
      bool standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      अगर (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  अगर (standalone_body == NULL_वृक्ष)
	    {
	      standalone_body = धकेलो_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = निकालो_stmt_list (standalone_body);
	    }
	  अन्यथा
	    c_parser_skip_to_end_of_block_or_statement (parser, true);
	}

      वृक्ष body = standalone_p ? standalone_body : NULL_वृक्ष;
      वृक्ष variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      अगर (errorcount == पूर्व_errorcount)
	{
	  gcc_assert (parser->tokens_avail == 2);
	  gcc_assert (c_parser_अग्र_token_is (parser, CPP_EOF));
	  gcc_assert (c_parser_peek_2nd_token (parser)->type == CPP_EOF);
	}

      parser->tokens = old_tokens;
      parser->tokens_avail = old_tokens_avail;
      parser->in_omp_attribute_pragma = old_in_omp_attribute_pragma;
      parser->omp_metadirective_state = old_state;
    }

  /* Try to resolve the metadirective early.  */
  candidates = omp_early_resolve_metadirective (ret);
  अगर (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  वापस;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  अगर (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, false);
}

/* Main entry point to parsing most OpenMP pragmas.  */

अटल व्योम
c_parser_omp_construct (c_parser *parser, bool *if_p)
{
  क्रमागत pragma_kind p_kind;
  location_t loc;
  वृक्ष stmt;
  अक्षर p_name[माप "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  चयन (p_kind)
    {
    हाल PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, true);
      वापस;
    हाल PRAGMA_OACC_CACHE:
      म_नकल (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      अवरोध;
    हाल PRAGMA_OACC_तथ्य:
      stmt = c_parser_oacc_तथ्य (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OACC_HOST_तथ्य:
      stmt = c_parser_oacc_host_तथ्य (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OACC_KERNELS:
    हाल PRAGMA_OACC_PARALLEL:
    हाल PRAGMA_OACC_SERIAL:
      म_नकल (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      अवरोध;
    हाल PRAGMA_OACC_LOOP:
      म_नकल (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OACC_WAIT:
      म_नकल (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      अवरोध;
    हाल PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, false);
      वापस;
    हाल PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OMP_DISTRIBUTE:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OMP_FOR:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OMP_LOOP:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OMP_MASKED:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OMP_MASTER:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, शून्य, if_p,
				  UNKNOWN_LOCATION);
      अवरोध;
    हाल PRAGMA_OMP_PARALLEL:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OMP_SECTIONS:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, शून्य);
      अवरोध;
    हाल PRAGMA_OMP_SIMD:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OMP_TASKLOOP:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OMP_TEAMS:
      म_नकल (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, शून्य, if_p);
      अवरोध;
    हाल PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      वापस;
    हाल PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      अवरोध;
    हाल PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      अवरोध;
    शेष:
      gcc_unreachable ();
    }

  अगर (stmt && stmt != error_mark_गाँठ)
    gcc_assert (व्यंजक_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#घोषणा OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

अटल व्योम
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  वृक्ष vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, शून्य);
  वृक्ष clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (व्योम) vars;
  (व्योम) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

अटल व्योम
c_parser_omp_threadprivate (c_parser *parser)
{
  वृक्ष vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, शून्य);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  क्रम (t = vars; t; t = वृक्ष_CHAIN (t))
    {
      वृक्ष v = वृक्ष_PURPOSE (t);
      loc = व्यंजक_LOCATION (वृक्ष_मूल्य (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      अगर (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      अन्यथा अगर (वृक्ष_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      अन्यथा अगर (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      अन्यथा अगर (वृक्ष_TYPE (v) == error_mark_गाँठ)
	;
      अन्यथा अगर (! COMPLETE_TYPE_P (वृक्ष_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      अन्यथा
	{
	  अगर (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      अगर (DECL_RTL_SET_P (v))
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

अटल वृक्ष
c_parser_transaction_attributes (c_parser *parser)
{
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ATTRIBUTE))
    वापस c_parser_gnu_attributes (parser);

  अगर (!c_parser_अग्र_token_is (parser, CPP_OPEN_SQUARE))
    वापस NULL_वृक्ष;
  वापस c_parser_std_attribute_specifier (parser, true);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

अटल वृक्ष
c_parser_transaction (c_parser *parser, क्रमागत rid keyword)
{
  अचिन्हित पूर्णांक old_in = parser->in_transaction;
  अचिन्हित पूर्णांक this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_अग्र_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  अगर (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  अन्यथा
    {
      attrs = c_parser_transaction_attributes (parser);
      अगर (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  अगर (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  अन्यथा
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  वापस stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

अटल काष्ठा c_व्यंजक
c_parser_transaction_expression (c_parser *parser, क्रमागत rid keyword)
{
  काष्ठा c_व्यंजक ret;
  अचिन्हित पूर्णांक old_in = parser->in_transaction;
  अचिन्हित पूर्णांक this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_अग्र_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  अगर (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  अन्यथा
    {
      attrs = c_parser_transaction_attributes (parser);
      अगर (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  अगर (parens.require_open (parser))
    {
      वृक्ष व्यंजक = c_parser_expression (parser).मूल्य;
      ret.original_type = वृक्ष_TYPE (व्यंजक);
      ret.मूल्य = build1 (TRANSACTION_व्यंजक, ret.original_type, व्यंजक);
      अगर (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_व्यंजक_RELAXED (ret.मूल्य) = 1;
      SET_व्यंजक_LOCATION (ret.मूल्य, loc);
      ret.original_code = TRANSACTION_व्यंजक;
      ret.m_decimal = 0;
      अगर (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, शून्य);
	  जाओ error;
	}
    }
  अन्यथा
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = शून्य;
    }
  parser->in_transaction = old_in;

  अगर (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_व्यंजक_source_range (&ret, loc, loc);

  वापस ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

अटल वृक्ष
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  वृक्ष attrs;
  bool is_outer = false;

  gcc_assert (c_parser_अग्र_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  अगर (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  अगर (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      जाओ ret_error;
    }
  अन्यथा अगर (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      जाओ ret_error;
    }
  अन्यथा अगर (is_outer)
    {
      अगर ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  जाओ ret_error;
	}
    }
  अन्यथा अगर (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      जाओ ret_error;
    }

  वापस add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  वापस build1 (NOP_व्यंजक, void_type_गाँठ, error_mark_गाँठ);
}

/* Parse a single source file.  */

व्योम
c_parse_file (व्योम)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  स_रखो (&tparser, 0, माप tparser);
  tparser.translate_strings_p = true;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  अगर (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  अन्यथा
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  अगर (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  अगर (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = शून्य;
}

व्योम
c_init_preprocess (व्योम)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  स_रखो (the_parser, 0, माप (c_parser));
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
c_parser_parse_rtl_body (c_parser *parser, अक्षर *start_with_pass)
{
  अगर (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      मुक्त (start_with_pass);
      वापस c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  पूर्णांक अंक_open_braces = 1;
  जबतक (1)
    {
      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_OPEN_BRACE:
	  अंक_open_braces++;
	  अवरोध;
	हाल CPP_CLOSE_BRACE:
	  अगर (--अंक_open_braces == 0)
	    जाओ found_closing_brace;
	  अवरोध;
	हाल CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  मुक्त (start_with_pass);
	  वापस c_parser_peek_token (parser)->location;
	शेष:
	  अवरोध;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  अगर (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      मुक्त (start_with_pass);
      वापस end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  वापस end_loc;
}

#समावेश "gt-c-c-parser.h"
