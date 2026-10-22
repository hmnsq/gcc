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

#અન્તર્ભાવ "config.h"
#define INCLUDE_STRING
#અન્તર્ભાવ "system.h"
#અન્તર્ભાવ "coretypes.h"
#અન્તર્ભાવ "target.h"
#અન્તર્ભાવ "function.h"
#અન્તર્ભાવ "c-tree.h"
#અન્તર્ભાવ "timevar.h"
#અન્તર્ભાવ "stringpool.h"
#અન્તર્ભાવ "cgraph.h"
#અન્તર્ભાવ "attribs.h"
#અન્તર્ભાવ "stor-layout.h"
#અન્તર્ભાવ "varasm.h"
#અન્તર્ભાવ "trans-mem.h"
#અન્તર્ભાવ "c-family/c-pragma.h"
#અન્તર્ભાવ "c-lang.h"
#અન્તર્ભાવ "c-family/c-objc.h"
#અન્તર્ભાવ "plugin.h"
#અન્તર્ભાવ "omp-general.h"
#અન્તર્ભાવ "omp-offload.h"
#અન્તર્ભાવ "builtins.h"
#અન્તર્ભાવ "gomp-constants.h"
#અન્તર્ભાવ "c-family/c-indentation.h"
#અન્તર્ભાવ "gimple-expr.h"
#અન્તર્ભાવ "context.h"
#અન્તર્ભાવ "gcc-rich-location.h"
#અન્તર્ભાવ "c-parser.h"
#અન્તર્ભાવ "gimple-parser.h"
#અન્તર્ભાવ "read-rtl-function.h"
#અન્તર્ભાવ "run-rtl-passes.h"
#અન્તર્ભાવ "intl.h"
#અન્તર્ભાવ "c-family/name-hint.h"
#અન્તર્ભાવ "tree-iterator.h"
#અન્તર્ભાવ "tree-pretty-print.h"
#અન્તર્ભાવ "memmodel.h"
#અન્તર્ભાવ "c-family/known-headers.h"
#અન્તર્ભાવ "bitmap.h"
#અન્તર્ભાવ "analyzer/analyzer-language.h"
#અન્તર્ભાવ "toplev.h"
#અન્તર્ભાવ "asan.h"
#અન્તર્ભાવ "c-family/c-ubsan.h"
#અન્તર્ભાવ "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<વૃક્ષ> incomplete_record_decls;

શૂન્ય
set_c_પદાવલિ_source_range (c_પદાવલિ *પદાવલિ,
			 location_t start, location_t finish)
{
  પદાવલિ->src_range.m_start = start;
  પદાવલિ->src_range.m_finish = finish;
  જો (પદાવલિ->કિંમત)
    set_source_range (પદાવલિ->કિંમત, start, finish);
}

શૂન્ય
set_c_પદાવલિ_source_range (c_પદાવલિ *પદાવલિ,
			 source_range src_range)
{
  પદાવલિ->src_range = src_range;
  જો (પદાવલિ->કિંમત)
    set_source_range (પદાવલિ->કિંમત, src_range);
}


/* Initialization routine for this file.  */

શૂન્ય
c_parse_init (શૂન્ય)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  unsigned પૂર્ણાંક i;
  વૃક્ષ id;
  પૂર્ણાંક mask = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  mask |= D_CXXONLY;
  જો (!flag_isoc99)
    mask |= D_C99;
  જો (!flag_isoc23)
    mask |= D_C23;
  જો (flag_no_asm)
    {
      mask |= D_ASM | D_EXT;
      જો (!flag_isoc99)
	mask |= D_EXT89;
      જો (!flag_isoc23)
	mask |= D_EXT11;
    }
  જો (!c_dialect_objc ())
    mask |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<વૃક્ષ> ((પૂર્ણાંક) RID_MAX);
  માટે (i = 0; i < અંક_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      જો (c_common_reswords[i].disable & mask)
	{
	  જો (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].word);
	      C_SET_RID_CODE (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_WORD (id) = 1;
	    }
	  ચાલુ;
	}

      id = get_identifier (c_common_reswords[i].word);
      C_SET_RID_CODE (id, c_common_reswords[i].rid);
      C_IS_RESERVED_WORD (id) = 1;
      ridpointers [(પૂર્ણાંક) c_common_reswords[i].rid] = id;
    }

  માટે (i = 0; i < અંક_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      અક્ષર name[50];
      sprintf (name, "__int%d", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;

      sprintf (name, "__int%d__", int_n_data[i].bitsize);
      id = get_identifier (name);
      C_SET_RID_CODE (id, RID_FIRST_INT_N + i);
      C_IS_RESERVED_WORD (id) = 1;
    }

  જો (flag_openmp)
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
સંરચના GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) tokens;
  /* Buffer for look-ahead tokens.  */
  c_token tokens_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  unsigned પૂર્ણાંક tokens_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_tokens;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  unsigned પૂર્ણાંક raw_tokens_used;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  તાર્કિક error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  તાર્કિક in_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  તાર્કિક in_if_block : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  તાર્કિક lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  તાર્કિક translate_strings_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  તાર્કિક objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  તાર્કિક objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  તાર્કિક objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  unsigned પૂર્ણાંક in_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  તાર્કિક objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  તાર્કિક seen_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  તાર્કિક omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t last_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  સંરચના omp_for_parse_data * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  સંરચના omp_attribute_pragma_state *in_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  વૃક્ષ in_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  સંરચના omp_metadirective_parse_data * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
સંરચના GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_tokens;
  unsigned પૂર્ણાંક save_tokens_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
સંરચના GTY(()) omp_begin_declare_variant_map_entry {
  વૃક્ષ variant;		/* The variant decl.  */
  વૃક્ષ id;		/* Name of base function.  */
  વૃક્ષ ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_entry, va_gc> *omp_begin_declare_variant_map;

સ્થિર વૃક્ષ omp_start_variant_function (c_declarator *, વૃક્ષ);
સ્થિર શૂન્ય omp_finish_variant_function (વૃક્ષ, વૃક્ષ, વૃક્ષ);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_tokens_buf (c_parser *parser, unsigned n)
{
  પાછા &parser->tokens_buf[n];
}

/* Return the error state of PARSER.  */

તાર્કિક
c_parser_error (c_parser *parser)
{
  પાછા parser->error;
}

/* Set the error state of PARSER to ERR.  */

શૂન્ય
c_parser_set_error (c_parser *parser, તાર્કિક err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

સ્થિર GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

સ્થિર શૂન્ય
c_lex_one_token (c_parser *parser, c_token *token, તાર્કિક raw = ખોટું)
{
  timevar_ધકેલો (TV_LEX);

  જો (raw || vec_safe_length (parser->raw_tokens) == 0)
    {
      token->type = c_lex_with_flags (&token->કિંમત, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_kind = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_kind = PRAGMA_NONE;
    }
  નહીંતર
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_tokens)[parser->raw_tokens_used];
      ++parser->raw_tokens_used;
      જો (parser->raw_tokens_used == vec_safe_length (parser->raw_tokens))
	{
	  vec_free (parser->raw_tokens);
	  parser->raw_tokens_used = 0;
	}
    }

  જો (raw)
    જાઓ out;

  પસંદગી (token->type)
    {
    સ્થિતિ CPP_NAME:
      {
	વૃક્ષ decl;

	તાર્કિક objc_force_identifier = parser->objc_need_raw_identifier;
	જો (c_dialect_objc ())
	  parser->objc_need_raw_identifier = ખોટું;

	જો (C_IS_RESERVED_WORD (token->કિંમત))
	  {
	    ગણના rid rid_code = C_RID_CODE (token->કિંમત);

	    જો (rid_code == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->કિંમત);
	      }
	    નહીંતર જો (rid_code >= RID_FIRST_ADDR_SPACE
		     && rid_code <= RID_LAST_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_code - RID_FIRST_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_kind = C_ID_ADDRSPACE;
		token->keyword = rid_code;
		તોડો;
	      }
	    નહીંતર જો (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		જો (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    તોડો;
		  }
		નહીંતર જો (parser->objc_could_be_foreach_context
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
		    તોડો;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    નહીંતર જો (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_code))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		જો (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    તોડો;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    નહીંતર જો (c_dialect_objc ()
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
	    નહીંતર
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		તોડો;
	      }
	  }

	decl = lookup_name (token->કિંમત);
	જો (decl)
	  {
	    જો (વૃક્ષ_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		તોડો;
	      }
	  }
	નહીંતર જો (c_dialect_objc ())
	  {
	    વૃક્ષ objc_interface_decl = objc_is_class_name (token->કિંમત);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    જો (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->કિંમત = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		તોડો;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      તોડો;
    સ્થિતિ CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      પસંદગી (C_RID_CODE (token->કિંમત))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	સ્થિતિ RID_CLASS:     token->keyword = RID_AT_CLASS; તોડો;
	સ્થિતિ RID_PRIVATE:   token->keyword = RID_AT_PRIVATE; તોડો;
	સ્થિતિ RID_PROTECTED: token->keyword = RID_AT_PROTECTED; તોડો;
	સ્થિતિ RID_PUBLIC:    token->keyword = RID_AT_PUBLIC; તોડો;
	સ્થિતિ RID_THROW:     token->keyword = RID_AT_THROW; તોડો;
	સ્થિતિ RID_TRY:       token->keyword = RID_AT_TRY; તોડો;
	સ્થિતિ RID_CATCH:     token->keyword = RID_AT_CATCH; તોડો;
	સ્થિતિ RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; તોડો;
	મૂળભૂત:            token->keyword = C_RID_CODE (token->કિંમત);
	}
      તોડો;
    સ્થિતિ CPP_COLON:
    સ્થિતિ CPP_COMMA:
    સ્થિતિ CPP_CLOSE_PAREN:
    સ્થિતિ CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      જો (c_dialect_objc ())
	parser->objc_need_raw_identifier = ખોટું;
      તોડો;
    સ્થિતિ CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = (ગણના pragma_kind) વૃક્ષ_INT_CST_નીચલું (token->કિંમત);
      token->કિંમત = ખાલી;
      તોડો;
    મૂળભૂત:
      તોડો;
    }
 out:
  timevar_કાઢો (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  જો (parser->tokens_avail == 0)
    {
      c_lex_one_token (parser, &parser->tokens[0]);
      parser->tokens_avail = 1;
    }
  પાછા &parser->tokens[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  જો (parser->tokens_avail >= 2)
    પાછા &parser->tokens[1];
  gcc_assert (parser->tokens_avail == 1);
  gcc_assert (parser->tokens[0].type != CPP_EOF);
  gcc_assert (parser->tokens[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->tokens[1]);
  parser->tokens_avail = 2;
  પાછા &parser->tokens[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, unsigned પૂર્ણાંક n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  જો (parser->tokens_avail >= n)
    પાછા &parser->tokens[n - 1];
  gcc_assert (parser->tokens_avail == n - 1);
  c_lex_one_token (parser, &parser->tokens[n - 1]);
  parser->tokens_avail = n;
  પાછા &parser->tokens[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, unsigned પૂર્ણાંક n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  જો (parser->tokens_avail >= n)
    પાછા &parser->tokens[n - 1];
  unsigned પૂર્ણાંક raw_len = vec_safe_length (parser->raw_tokens);
  unsigned પૂર્ણાંક raw_avail
    = parser->tokens_avail + raw_len - parser->raw_tokens_used;
  gcc_assert (raw_avail >= n - 1);
  જો (raw_avail >= n)
    પાછા &(*parser->raw_tokens)[parser->raw_tokens_used
				  + n - 1 - parser->tokens_avail];
  vec_safe_reserve (parser->raw_tokens, 1);
  parser->raw_tokens->quick_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_tokens)[raw_len], સાચું);
  પાછા &(*parser->raw_tokens)[raw_len];
}

તાર્કિક
c_keyword_starts_typename (ગણના rid keyword)
{
  પસંદગી (keyword)
    {
    સ્થિતિ RID_UNSIGNED:
    સ્થિતિ RID_LONG:
    સ્થિતિ RID_SHORT:
    સ્થિતિ RID_SIGNED:
    સ્થિતિ RID_COMPLEX:
    સ્થિતિ RID_INT:
    સ્થિતિ RID_CHAR:
    સ્થિતિ RID_FLOAT:
    સ્થિતિ RID_DOUBLE:
    સ્થિતિ RID_VOID:
    સ્થિતિ RID_DFLOAT32:
    સ્થિતિ RID_DFLOAT64:
    સ્થિતિ RID_DFLOAT128:
    સ્થિતિ RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    સ્થિતિ RID_BOOL:
    સ્થિતિ RID_BITINT:
    સ્થિતિ RID_ENUM:
    સ્થિતિ RID_STRUCT:
    સ્થિતિ RID_UNION:
    સ્થિતિ RID_TYPEOF:
    સ્થિતિ RID_TYPEOF_UNQUAL:
    સ્થિતિ RID_CONST:
    સ્થિતિ RID_ATOMIC:
    સ્થિતિ RID_VOLATILE:
    સ્થિતિ RID_RESTRICT:
    સ્થિતિ RID_ATTRIBUTE:
    સ્થિતિ RID_FRACT:
    સ્થિતિ RID_ACCUM:
    સ્થિતિ RID_SAT:
    સ્થિતિ RID_AUTO_TYPE:
    સ્થિતિ RID_ALIGNAS:
      પાછા સાચું;
    મૂળભૂત:
      જો (keyword >= RID_FIRST_INT_N
	  && keyword < RID_FIRST_INT_N + અંક_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_FIRST_INT_N])
	પાછા સાચું;
      પાછા ખોટું;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
તાર્કિક
c_token_starts_typename (c_token *token)
{
  પસંદગી (token->type)
    {
    સ્થિતિ CPP_NAME:
      પસંદગી (token->id_kind)
	{
	સ્થિતિ C_ID_ID:
	  પાછા ખોટું;
	સ્થિતિ C_ID_ADDRSPACE:
	  પાછા સાચું;
	સ્થિતિ C_ID_TYPENAME:
	  પાછા સાચું;
	સ્થિતિ C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  પાછા સાચું;
	મૂળભૂત:
	  gcc_unreachable ();
	}
    સ્થિતિ CPP_KEYWORD:
      પાછા c_keyword_starts_typename (token->keyword);
    સ્થિતિ CPP_LESS:
      જો (c_dialect_objc ())
	પાછા સાચું;
      પાછા ખોટું;
    મૂળભૂત:
      પાછા ખોટું;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

સ્થિર અંતઃરેખ તાર્કિક
c_parser_next_tokens_start_typename (c_parser *parser, ગણના c_lookahead_kind la,
				     unsigned પૂર્ણાંક n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  જો (c_token_starts_typename (token))
    પાછા સાચું;

  /* Try a bit harder to detect an unknown typename.  */
  જો (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_kind == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->કિંમત))
    પાછા સાચું;

  પાછા ખોટું;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
સ્થિર તાર્કિક
c_token_starts_compound_literal (c_token *token)
{
  પસંદગી (token->type)
    {
    સ્થિતિ CPP_KEYWORD:
      પસંદગી (token->keyword)
	{
	સ્થિતિ RID_CONSTEXPR:
	સ્થિતિ RID_REGISTER:
	સ્થિતિ RID_STATIC:
	સ્થિતિ RID_THREAD:
	  પાછા સાચું;
	મૂળભૂત:
	  તોડો;
	}
      /* Fall through.  */
    મૂળભૂત:
      પાછા c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
સ્થિર તાર્કિક
c_token_is_qualifier (c_token *token)
{
  પસંદગી (token->type)
    {
    સ્થિતિ CPP_NAME:
      પસંદગી (token->id_kind)
	{
	સ્થિતિ C_ID_ADDRSPACE:
	  પાછા સાચું;
	મૂળભૂત:
	  પાછા ખોટું;
	}
    સ્થિતિ CPP_KEYWORD:
      પસંદગી (token->keyword)
	{
	સ્થિતિ RID_CONST:
	સ્થિતિ RID_VOLATILE:
	સ્થિતિ RID_RESTRICT:
	સ્થિતિ RID_ATTRIBUTE:
	સ્થિતિ RID_ATOMIC:
	  પાછા સાચું;
	મૂળભૂત:
	  પાછા ખોટું;
	}
    સ્થિતિ CPP_LESS:
      પાછા ખોટું;
    મૂળભૂત:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
સ્થિર અંતઃરેખ તાર્કિક
c_parser_next_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  પાછા c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
સ્થિર તાર્કિક
c_token_starts_declspecs (c_token *token)
{
  પસંદગી (token->type)
    {
    સ્થિતિ CPP_NAME:
      પસંદગી (token->id_kind)
	{
	સ્થિતિ C_ID_ID:
	  પાછા ખોટું;
	સ્થિતિ C_ID_ADDRSPACE:
	  પાછા સાચું;
	સ્થિતિ C_ID_TYPENAME:
	  પાછા સાચું;
	સ્થિતિ C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  પાછા સાચું;
	મૂળભૂત:
	  gcc_unreachable ();
	}
    સ્થિતિ CPP_KEYWORD:
      પસંદગી (token->keyword)
	{
	સ્થિતિ RID_STATIC:
	સ્થિતિ RID_EXTERN:
	સ્થિતિ RID_REGISTER:
	સ્થિતિ RID_TYPEDEF:
	સ્થિતિ RID_INLINE:
	સ્થિતિ RID_NORETURN:
	સ્થિતિ RID_AUTO:
	સ્થિતિ RID_THREAD:
	સ્થિતિ RID_UNSIGNED:
	સ્થિતિ RID_LONG:
	સ્થિતિ RID_SHORT:
	સ્થિતિ RID_SIGNED:
	સ્થિતિ RID_COMPLEX:
	સ્થિતિ RID_INT:
	સ્થિતિ RID_CHAR:
	સ્થિતિ RID_FLOAT:
	સ્થિતિ RID_DOUBLE:
	સ્થિતિ RID_VOID:
	સ્થિતિ RID_DFLOAT32:
	સ્થિતિ RID_DFLOAT64:
	સ્થિતિ RID_DFLOAT128:
	સ્થિતિ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	સ્થિતિ RID_BOOL:
	સ્થિતિ RID_BITINT:
	સ્થિતિ RID_ENUM:
	સ્થિતિ RID_STRUCT:
	સ્થિતિ RID_UNION:
	સ્થિતિ RID_TYPEOF:
	સ્થિતિ RID_TYPEOF_UNQUAL:
	સ્થિતિ RID_CONST:
	સ્થિતિ RID_VOLATILE:
	સ્થિતિ RID_RESTRICT:
	સ્થિતિ RID_ATTRIBUTE:
	સ્થિતિ RID_FRACT:
	સ્થિતિ RID_ACCUM:
	સ્થિતિ RID_SAT:
	સ્થિતિ RID_ALIGNAS:
	સ્થિતિ RID_ATOMIC:
	સ્થિતિ RID_AUTO_TYPE:
	સ્થિતિ RID_CONSTEXPR:
	  પાછા સાચું;
	મૂળભૂત:
	  જો (token->keyword >= RID_FIRST_INT_N
	      && token->keyword < RID_FIRST_INT_N + અંક_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_FIRST_INT_N])
	    પાછા સાચું;
	  પાછા ખોટું;
	}
    સ્થિતિ CPP_LESS:
      જો (c_dialect_objc ())
	પાછા સાચું;
      પાછા ખોટું;
    મૂળભૂત:
      પાછા ખોટું;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
સ્થિર તાર્કિક
c_token_starts_declaration (c_token *token)
{
  જો (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    પાછા સાચું;
  નહીંતર
    પાછા ખોટું;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
તાર્કિક
c_parser_next_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  જો (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    પાછા ખોટું;

  પાછા c_token_starts_declspecs (token);
}

સ્થિર તાર્કિક c_parser_check_balanced_raw_token_sequence (c_parser *,
							unsigned પૂર્ણાંક *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
તાર્કિક
c_parser_next_tokens_start_declaration (c_parser *parser, unsigned પૂર્ણાંક n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  જો (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_kind == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    પાછા ખોટું;

  /* Labels do not start declarations.  */
  જો (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    પાછા ખોટું;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  જો (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      જો (!c_parser_check_balanced_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	પાછા સાચું;
      પાછા c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  જો (c_token_starts_declaration (token))
    પાછા સાચું;

  જો (c_parser_next_tokens_start_typename (parser, cla_nonabstract_decl, n))
    પાછા સાચું;

  પાછા ખોટું;
}

/* Consume the next token from PARSER.  */

શૂન્ય
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
  જો (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  નહીંતર જો (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      જો (parser->tokens_avail >= 3)
        {
          parser->tokens[1] = parser->tokens[2];
          જો (parser->tokens_avail >= 4)
            parser->tokens[2] = parser->tokens[3];
        }
    }
  parser->tokens_avail--;
  parser->seen_string_literal = ખોટું;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

સ્થિર શૂન્ય
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->in_pragma);
  gcc_assert (parser->tokens_avail >= 1);
  gcc_assert (parser->tokens[0].type == CPP_PRAGMA);
  જો (parser->tokens != &parser->tokens_buf[0])
    parser->tokens++;
  નહીંતર જો (parser->tokens_avail >= 2)
    {
      parser->tokens[0] = parser->tokens[1];
      જો (parser->tokens_avail >= 3)
	parser->tokens[1] = parser->tokens[2];
    }
  parser->tokens_avail--;
  parser->in_pragma = સાચું;
}

/* Update the global input_location from TOKEN.  */
સ્થિર અંતઃરેખ શૂન્ય
c_parser_set_source_position_from_token (c_token *token)
{
  જો (token->type != CPP_EOF)
    {
      આગત_location = token->location;
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

સ્થિર તાર્કિક
c_parser_peek_conflict_marker (c_parser *parser, ગણના cpp_ttype tok1_kind,
			       location_t *out_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  જો (token2->type != tok1_kind)
    પાછા ખોટું;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  જો (token3->type != tok1_kind)
    પાછા ખોટું;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  જો (token4->type != conflict_marker_get_final_tok_kind (tok1_kind))
    પાછા ખોટું;

  /* It must be at the start of the line.  */
  location_t start_loc = c_parser_peek_token (parser)->location;
  જો (LOCATION_COLUMN (start_loc) != 1)
    પાછા ખોટું;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t finish_loc = get_finish (token4->location);
  *out_loc = make_location (start_loc, start_loc, finish_loc);

  પાછા સાચું;
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

સ્થિર તાર્કિક
c_parser_error_richloc (c_parser *parser, અચલ અક્ષર *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  જો (parser->error)
    પાછા ખોટું;
  parser->error = સાચું;
  જો (!gmsgid)
    પાછા ખોટું;

  /* If this is actually a conflict marker, report it as such.  */
  જો (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      જો (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  પાછા સાચું;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_group d;
  name_hint h;
  જો (parser->seen_string_literal && token->type == CPP_NAME)
    {
      વૃક્ષ name = token->કિંમત;
      અચલ અક્ષર *token_name = IDENTIFIER_POINTER (name);
      અચલ અક્ષર *header_hint
	= get_c_stdlib_header_for_string_macro_name (token_name);
      જો (header_hint != ખાલી)
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
		 token->કિંમત, /*flags=*/0, richloc);
  પાછા સાચું;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

તાર્કિક
c_parser_error (c_parser *parser, અચલ અક્ષર *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_set_source_position_from_token (token);
  rich_location richloc (લીટી_table, આગત_location);
  પાછા c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

template <typename traits_t>
વર્ગ token_pair
{
 જાહેર:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  તાર્કિક require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    જો (token)
      m_open_loc = token->location;

    પાછા c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  શૂન્ય consume_open (c_parser *parser)
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

  તાર્કિક require_close (c_parser *parser) અચલ
  {
    પાછા c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  શૂન્ય skip_until_found_close (c_parser *parser) અચલ
  {
    c_parser_skip_until_found (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 ખાનગી:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

સંરચના matching_paren_traits
{
  સ્થિર અચલ ગણના cpp_ttype open_token_type = CPP_OPEN_PAREN;
  સ્થિર અચલ અક્ષર * અચલ open_gmsgid;
  સ્થિર અચલ ગણના cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  સ્થિર અચલ અક્ષર * અચલ close_gmsgid;
};

અચલ અક્ષર * અચલ matching_paren_traits::open_gmsgid = "expected %<(%>";
અચલ અક્ષર * અચલ matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

પ્રકારવ્યાખ્યા token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

સંરચના matching_brace_traits
{
  સ્થિર અચલ ગણના cpp_ttype open_token_type = CPP_OPEN_BRACE;
  સ્થિર અચલ અક્ષર * અચલ open_gmsgid;
  સ્થિર અચલ ગણના cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  સ્થિર અચલ અક્ષર * અચલ close_gmsgid;
};

અચલ અક્ષર * અચલ matching_brace_traits::open_gmsgid = "expected %<{%>";
અચલ અક્ષર * અચલ matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

પ્રકારવ્યાખ્યા token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

સ્થિર અચલ અક્ષર *
get_matching_પ્રતીક (ગણના cpp_ttype type)
{
  પસંદગી (type)
    {
    મૂળભૂત:
      gcc_unreachable ();
    સ્થિતિ CPP_CLOSE_PAREN:
      પાછા "(";
    સ્થિતિ CPP_CLOSE_BRACE:
      પાછા "{";
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

તાર્કિક
c_parser_require (c_parser *parser,
		  ગણના cpp_ttype type,
		  અચલ અક્ષર *msgid,
		  location_t matching_location,
		  તાર્કિક type_is_unique)
{
  જો (c_parser_next_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      પાછા સાચું;
    }
  નહીંતર
    {
      location_t next_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (next_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      જો (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->last_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      તાર્કિક added_matching_location = ખોટું;
      જો (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.add_location_if_nearby (*global_dc, matching_location);

      જો (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	જો (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_પ્રતીક (type));

      પાછા ખોટું;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

સ્થિર તાર્કિક
c_parser_require_keyword (c_parser *parser,
			  ગણના rid keyword,
			  અચલ અક્ષર *msgid)
{
  જો (c_parser_next_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      પાછા સાચું;
    }
  નહીંતર
    {
      c_parser_error (parser, msgid);
      પાછા ખોટું;
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

શૂન્ય
c_parser_skip_until_found (c_parser *parser,
			   ગણના cpp_ttype type,
			   અચલ અક્ષર *msgid,
			   location_t matching_location)
{
  unsigned nesting_depth = 0;

  જો (c_parser_require (parser, type, msgid, matching_location))
    {
      જો (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->in_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  જો (token->type == CPP_EOF)
	    {
	      parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	      parser->tokens_avail
		= parser->in_omp_attribute_pragma->save_tokens_avail;
	      parser->in_omp_attribute_pragma = ખાલી;
	    }
	}
      પાછા;
    }

  /* Skip tokens until the desired token is found.  */
  જ્યારે (સાચું)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      જો (token->type == type && !nesting_depth)
	{
	  c_parser_consume_token (parser);
	  જો (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->in_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      જો (token->type == CPP_EOF)
		{
		  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
		  parser->tokens_avail
		    = parser->in_omp_attribute_pragma->save_tokens_avail;
		  parser->in_omp_attribute_pragma = ખાલી;
		}
	    }
	  તોડો;
	}

      /* If we've run out of tokens, stop.  */
      જો (token->type == CPP_EOF)
	પાછા;
      જો (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	પાછા;
      જો (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      નહીંતર જો (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  જો (nesting_depth-- == 0)
	    તોડો;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = ખોટું;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

સ્થિર શૂન્ય
c_parser_skip_to_end_of_parameter (c_parser *parser)
{
  unsigned nesting_depth = 0;

  જ્યારે (સાચું)
    {
      c_token *token = c_parser_peek_token (parser);
      જો ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_depth)
	તોડો;
      /* If we've run out of tokens, stop.  */
      જો (token->type == CPP_EOF)
	પાછા;
      જો (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
	પાછા;
      જો (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_SQUARE)
	++nesting_depth;
      નહીંતર જો (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_SQUARE)
	{
	  જો (nesting_depth-- == 0)
	    તોડો;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = ખોટું;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

સ્થિર તાર્કિક
c_parser_skip_to_closing_brace (c_parser *parser)
{
  unsigned nesting_depth = 0;

  જ્યારે (સાચું)
    {
      c_token *token = c_parser_peek_token (parser);

      પસંદગી (token->type)
	{
	સ્થિતિ CPP_PRAGMA_EOL:
	  જો (!parser->in_pragma)
	    તોડો;
	  /* FALLTHRU */
	સ્થિતિ CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  પાછા ખોટું;

	સ્થિતિ CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  જો (nesting_depth-- == 0)
	    પાછા સાચું;
	  તોડો;

	સ્થિતિ CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  તોડો;

	મૂળભૂત:
	  તોડો;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

સ્થિર શૂન્ય
c_parser_skip_to_pragma_eol (c_parser *parser, તાર્કિક error_if_not_eol = સાચું)
{
  gcc_assert (parser->in_pragma);
  parser->in_pragma = ખોટું;

  જો (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  કરો
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      જો (token_type == CPP_EOF)
	તોડો;
      c_parser_consume_token (parser);
    }
  જ્યારે (token_type != CPP_PRAGMA_EOL);

  જો (parser->in_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      જો (token->type == CPP_EOF)
	{
	  parser->tokens = parser->in_omp_attribute_pragma->save_tokens;
	  parser->tokens_avail
	    = parser->in_omp_attribute_pragma->save_tokens_avail;
	  parser->in_omp_attribute_pragma = ખાલી;
	}
    }

  parser->error = ખોટું;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
સ્થિર શૂન્ય
c_parser_skip_to_pragma_omp_end_declare_variant (c_parser *parser)
{
  માટે (પૂર્ણાંક depth = 0; depth >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      પસંદગી (token->type)
	{
	સ્થિતિ CPP_PRAGMA_EOL:
	  જો (!parser->in_pragma)
	    તોડો;
	  /* FALLTHRU */
	સ્થિતિ CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  પાછા;

	સ્થિતિ CPP_PRAGMA:
	  જો ((token->pragma_kind == PRAGMA_OMP_BEGIN
	       || token->pragma_kind == PRAGMA_OMP_END)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      વૃક્ષ id1 = c_parser_peek_nth_token (parser, 2)->કિંમત;
	      વૃક્ષ id2 = c_parser_peek_nth_token (parser, 3)->કિંમત;
	      જો (strcmp (IDENTIFIER_POINTER (id1), "declare") == 0
		  && strcmp (IDENTIFIER_POINTER (id2), "variant") == 0)
		{
		  જો (token->pragma_kind == PRAGMA_OMP_BEGIN)
		    depth++;
		  નહીંતર
		    depth--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  ચાલુ;

	મૂળભૂત:
	  તોડો;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

સ્થિર શૂન્ય
c_parser_skip_to_end_of_block_or_statement (c_parser *parser,
					    તાર્કિક metadirective_p = ખોટું)
{
  unsigned nesting_depth = 0;
  પૂર્ણાંક bracket_depth = 0;
  તાર્કિક save_error = parser->error;

  જ્યારે (સાચું)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      પસંદગી (token->type)
	{
	સ્થિતિ CPP_EOF:
	  પાછા;

	સ્થિતિ CPP_PRAGMA_EOL:
	  જો (parser->in_pragma)
	    પાછા;
	  તોડો;

	સ્થિતિ CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  જો (!nesting_depth && (!metadirective_p || bracket_depth <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      જાઓ finished;
	    }
	  તોડો;

	સ્થિતિ CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  જો ((nesting_depth == 0 || --nesting_depth == 0)
	      && (!metadirective_p || bracket_depth <= 0))
	    {
	      c_parser_consume_token (parser);
	      જાઓ finished;
	    }
	  તોડો;

	સ્થિતિ CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_depth;
	  તોડો;

	સ્થિતિ CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  જો (metadirective_p && nesting_depth == 0)
	    ++bracket_depth;
	  તોડો;

	સ્થિતિ CPP_CLOSE_PAREN:
	  જો (metadirective_p && nesting_depth == 0)
	    --bracket_depth;
	  તોડો;

	સ્થિતિ CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  parser->error = save_error;
	  ચાલુ;

	મૂળભૂત:
	  તોડો;
	}

      c_parser_consume_token (parser);
    }

 finished:
  parser->error = ખોટું;
}

/* CPP's options (initialized by c-opts.cc).  */
બાહ્ય cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

સ્થિર અંતઃરેખ પૂર્ણાંક
disable_extension_diagnostics (શૂન્ય)
{
  પૂર્ણાંક ret = (pedantic
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
  પાછા ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

સ્થિર અંતઃરેખ શૂન્ય
restore_extension_diagnostics (પૂર્ણાંક flags)
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
સંરચના oacc_routine_data {
  તાર્કિક error_seen; /* Set if error has been reported.  */
  તાર્કિક fndecl_seen; /* Set if one fn decl/definition has been seen already.  */
  વૃક્ષ clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
સ્થિર વૃક્ષ objc_foreach_break_label, objc_foreach_continue_label;

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
સંરચના omp_for_parse_data {
  ગણના વૃક્ષ_code code;
  વૃક્ષ declv, condv, incrv, initv;
  વૃક્ષ pre_body;
  વૃક્ષ bindings;
  પૂર્ણાંક ગણતરી;	/* Expected nesting depth.  */
  પૂર્ણાંક depth;	/* Current nesting depth.  */
  location_t for_loc;
  તાર્કિક ordered : 1;
  તાર્કિક inscan : 1;
  તાર્કિક want_nested_loop : 1;
  તાર્કિક in_intervening_code : 1;
  તાર્કિક saw_intervening_code: 1;
  તાર્કિક perfect_nesting_fail : 1;
  તાર્કિક fail : 1;
};

સંરચના attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  તાર્કિક musttail_p;

  શૂન્ય reset () { musttail_p = ખોટું; }
};

સ્થિર તાર્કિક c_parser_nth_token_starts_std_attributes (c_parser *,
						      unsigned પૂર્ણાંક);
સ્થિર વૃક્ષ c_parser_std_attribute_specifier_sequence (c_parser *);
સ્થિર શૂન્ય c_parser_external_declaration (c_parser *);
સ્થિર શૂન્ય c_parser_asm_definition (c_parser *);
સ્થિર વૃક્ષ c_parser_declaration_or_fndef (c_parser *, તાર્કિક, તાર્કિક, તાર્કિક,
					   તાર્કિક, તાર્કિક, તાર્કિક, વૃક્ષ * = ખાલી,
					   vec<c_token> * = ખાલી,
					   તાર્કિક have_attrs = ખોટું,
					   વૃક્ષ attrs = ખાલી,
					   સંરચના oacc_routine_data * = ખાલી,
					   તાર્કિક * = ખાલી);
સ્થિર તાર્કિક c_parser_handle_statement_omp_attributes (c_parser *, વૃક્ષ &,
						      તાર્કિક *);
સ્થિર શૂન્ય c_parser_static_assert_declaration_no_semi (c_parser *);
સ્થિર શૂન્ય c_parser_static_assert_declaration (c_parser *);
સ્થિર સંરચના c_typespec c_parser_enum_specifier (c_parser *);
સ્થિર સંરચના c_typespec c_parser_struct_or_union_specifier (c_parser *);
સ્થિર વૃક્ષ c_parser_struct_declaration (c_parser *, વૃક્ષ *);
સ્થિર સંરચના c_typespec c_parser_typeof_specifier (c_parser *);
સ્થિર વૃક્ષ c_parser_alignas_specifier (c_parser *);
સ્થિર સંરચના c_declarator *c_parser_direct_declarator (c_parser *, તાર્કિક,
							c_dtr_syn, તાર્કિક *);
સ્થિર સંરચના c_declarator *c_parser_direct_declarator_inner (c_parser *,
							      તાર્કિક,
							      સંરચના c_declarator *);
સ્થિર સંરચના c_arg_info *c_parser_parms_declarator (c_parser *, તાર્કિક, વૃક્ષ,
						     તાર્કિક);
સ્થિર સંરચના c_arg_info *c_parser_parms_list_declarator (c_parser *, વૃક્ષ,
							  વૃક્ષ, તાર્કિક);
સ્થિર સંરચના c_parm *c_parser_parameter_declaration (c_parser *, વૃક્ષ, તાર્કિક);
સ્થિર વૃક્ષ c_parser_asm_string_literal (c_parser *);
સ્થિર વૃક્ષ c_parser_simple_asm_પદાવલિ (c_parser *);
સ્થિર વૃક્ષ c_parser_gnu_attributes (c_parser *);
સ્થિર સંરચના c_પદાવલિ c_parser_initializer (c_parser *, વૃક્ષ);
સ્થિર સંરચના c_પદાવલિ c_parser_braced_init (c_parser *, વૃક્ષ, તાર્કિક,
					   સંરચના obstack *, તાર્કિક);
સ્થિર શૂન્ય c_parser_initelt (c_parser *, સંરચના obstack *);
સ્થિર શૂન્ય c_parser_initval (c_parser *, સંરચના c_પદાવલિ *,
			      સંરચના obstack *);
સ્થિર વૃક્ષ c_parser_compound_statement (c_parser *, location_t * = ખાલી);
સ્થિર location_t c_parser_compound_statement_nostart (c_parser *);
સ્થિર શૂન્ય c_parser_label (c_parser *, વૃક્ષ);
સ્થિર શૂન્ય c_parser_statement (c_parser *, તાર્કિક *, location_t * = ખાલી);
સ્થિર શૂન્ય c_parser_statement_after_labels (c_parser *, તાર્કિક *, વૃક્ષ,
					     vec<વૃક્ષ> * = ખાલી,
					     attr_state = {});
સ્થિર વૃક્ષ c_parser_c99_block_statement (c_parser *, તાર્કિક *,
					  location_t * = ખાલી);
સ્થિર શૂન્ય c_parser_if_statement (c_parser *, તાર્કિક *, vec<વૃક્ષ> *);
સ્થિર શૂન્ય c_parser_switch_statement (c_parser *, તાર્કિક *, વૃક્ષ);
સ્થિર શૂન્ય c_parser_while_statement (c_parser *, તાર્કિક, unsigned short, તાર્કિક,
				      તાર્કિક *, વૃક્ષ);
સ્થિર શૂન્ય c_parser_do_statement (c_parser *, તાર્કિક, unsigned short, તાર્કિક,
				   વૃક્ષ);
સ્થિર શૂન્ય c_parser_for_statement (c_parser *, તાર્કિક, unsigned short, તાર્કિક,
				    તાર્કિક *, વૃક્ષ);
સ્થિર વૃક્ષ c_parser_asm_statement (c_parser *);
સ્થિર વૃક્ષ c_parser_asm_operands (c_parser *);
સ્થિર વૃક્ષ c_parser_asm_goto_operands (c_parser *);
સ્થિર વૃક્ષ c_parser_asm_clobbers (c_parser *);
સ્થિર સંરચના c_પદાવલિ c_parser_પદાવલિ_no_commas (c_parser *, સંરચના c_પદાવલિ *,
					      વૃક્ષ = NULL_વૃક્ષ);
સ્થિર સંરચના c_પદાવલિ c_parser_conditional_expression (c_parser *,
						      સંરચના c_પદાવલિ *, વૃક્ષ);
સ્થિર સંરચના c_પદાવલિ c_parser_દ્વિઅંકી_expression (c_parser *, સંરચના c_પદાવલિ *,
						 વૃક્ષ);
સ્થિર સંરચના c_પદાવલિ c_parser_cast_expression (c_parser *, સંરચના c_પદાવલિ *);
સ્થિર સંરચના c_પદાવલિ c_parser_unary_expression (c_parser *);
સ્થિર સંરચના c_પદાવલિ c_parser_sizeof_or_countof_expression (c_parser *,
							    ગણના rid);
સ્થિર સંરચના c_પદાવલિ c_parser_alignof_expression (c_parser *);
સ્થિર સંરચના c_પદાવલિ c_parser_maxof_or_minof_expression (c_parser *, ગણના rid);
સ્થિર સંરચના c_પદાવલિ c_parser_postfix_expression (c_parser *);
સ્થિર સંરચના c_પદાવલિ c_parser_postfix_expression_after_paren_type (c_parser *,
								   સંરચના c_declspecs *,
								   સંરચના c_type_name *,
								   location_t);
સ્થિર સંરચના c_પદાવલિ c_parser_postfix_expression_after_primary (c_parser *,
								location_t loc,
								સંરચના c_પદાવલિ);
સ્થિર વૃક્ષ c_parser_transaction (c_parser *, ગણના rid);
સ્થિર સંરચના c_પદાવલિ c_parser_transaction_expression (c_parser *, ગણના rid);
સ્થિર વૃક્ષ c_parser_transaction_cancel (c_parser *);
સ્થિર સંરચના c_પદાવલિ c_parser_expression (c_parser *);
સ્થિર સંરચના c_પદાવલિ c_parser_expression_conv (c_parser *);
સ્થિર vec<વૃક્ષ, va_gc> *c_parser_પદાવલિ_list (c_parser *, તાર્કિક, તાર્કિક,
					     vec<વૃક્ષ, va_gc> **, location_t *,
					     વૃક્ષ *, vec<location_t> *,
					     unsigned પૂર્ણાંક * = ખાલી);
સ્થિર સંરચના c_પદાવલિ c_parser_has_attribute_expression (c_parser *);

સ્થિર શૂન્ય c_parser_oacc_declare (c_parser *);
સ્થિર શૂન્ય c_parser_oacc_enter_exit_data (c_parser *, તાર્કિક);
સ્થિર શૂન્ય c_parser_oacc_update (c_parser *);
સ્થિર શૂન્ય c_parser_omp_construct (c_parser *, તાર્કિક *);
સ્થિર શૂન્ય c_parser_omp_groupprivate (c_parser *);
સ્થિર શૂન્ય c_parser_omp_threadprivate (c_parser *);
સ્થિર શૂન્ય c_parser_omp_barrier (c_parser *);
સ્થિર શૂન્ય c_parser_omp_depobj (c_parser *);
સ્થિર શૂન્ય c_parser_omp_flush (c_parser *);
સ્થિર તાર્કિક c_parser_omp_next_tokens_can_be_canon_loop (c_parser *,
							ગણના વૃક્ષ_code, તાર્કિક);
સ્થિર વૃક્ષ c_parser_omp_loop_nest (c_parser *, તાર્કિક *);
સ્થિર વૃક્ષ c_parser_omp_for_loop (location_t, c_parser *, ગણના વૃક્ષ_code,
				   વૃક્ષ, વૃક્ષ *, તાર્કિક *);
સ્થિર શૂન્ય c_parser_omp_taskwait (c_parser *);
સ્થિર શૂન્ય c_parser_omp_taskyield (c_parser *);
સ્થિર શૂન્ય c_parser_omp_cancel (c_parser *);
સ્થિર શૂન્ય c_parser_omp_nothing (c_parser *);
સ્થિર શૂન્ય c_parser_omp_metadirective (c_parser *, તાર્કિક *);

ગણના pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
સ્થિર તાર્કિક c_parser_pragma (c_parser *, ગણના pragma_context, તાર્કિક *, વૃક્ષ);
સ્થિર તાર્કિક c_parser_omp_cancellation_point (c_parser *, ગણના pragma_context);
સ્થિર તાર્કિક c_parser_omp_target (c_parser *, ગણના pragma_context, તાર્કિક *);
સ્થિર શૂન્ય c_parser_omp_begin (c_parser *);
સ્થિર શૂન્ય c_parser_omp_end (c_parser *);
સ્થિર તાર્કિક c_parser_omp_declare (c_parser *, ગણના pragma_context);
સ્થિર શૂન્ય c_parser_omp_requires (c_parser *);
સ્થિર તાર્કિક c_parser_omp_error (c_parser *, ગણના pragma_context);
સ્થિર શૂન્ય c_parser_omp_assumption_clauses (c_parser *, તાર્કિક);
સ્થિર શૂન્ય c_parser_omp_allocate (c_parser *);
સ્થિર શૂન્ય c_parser_omp_assumes (c_parser *);
સ્થિર તાર્કિક c_parser_omp_ordered (c_parser *, ગણના pragma_context, તાર્કિક *);
સ્થિર વૃક્ષ c_parser_omp_dispatch (location_t, c_parser *);
સ્થિર શૂન્ય c_parser_omp_interop (c_parser *);
સ્થિર શૂન્ય c_parser_oacc_routine (c_parser *, ગણના pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
સ્થિર શૂન્ય c_parser_objc_class_definition (c_parser *, વૃક્ષ);
સ્થિર શૂન્ય c_parser_objc_class_instance_variables (c_parser *);
સ્થિર શૂન્ય c_parser_objc_class_declaration (c_parser *);
સ્થિર શૂન્ય c_parser_objc_alias_declaration (c_parser *);
સ્થિર શૂન્ય c_parser_objc_protocol_definition (c_parser *, વૃક્ષ);
સ્થિર તાર્કિક c_parser_objc_method_type (c_parser *);
સ્થિર શૂન્ય c_parser_objc_method_definition (c_parser *);
સ્થિર શૂન્ય c_parser_objc_methodprotolist (c_parser *);
સ્થિર શૂન્ય c_parser_objc_methodproto (c_parser *);
સ્થિર વૃક્ષ c_parser_objc_method_decl (c_parser *, તાર્કિક, વૃક્ષ *, વૃક્ષ *);
સ્થિર વૃક્ષ c_parser_objc_type_name (c_parser *);
સ્થિર વૃક્ષ c_parser_objc_protocol_refs (c_parser *);
સ્થિર શૂન્ય c_parser_objc_try_catch_finally_statement (c_parser *);
સ્થિર શૂન્ય c_parser_objc_synchronized_statement (c_parser *);
સ્થિર વૃક્ષ c_parser_objc_selector (c_parser *);
સ્થિર વૃક્ષ c_parser_objc_selector_arg (c_parser *);
સ્થિર વૃક્ષ c_parser_objc_receiver (c_parser *);
સ્થિર વૃક્ષ c_parser_objc_message_args (c_parser *);
સ્થિર વૃક્ષ c_parser_objc_keywordexpr (c_parser *);
સ્થિર શૂન્ય c_parser_objc_at_property_declaration (c_parser *);
સ્થિર શૂન્ય c_parser_objc_at_synthesize_declaration (c_parser *);
સ્થિર શૂન્ય c_parser_objc_at_dynamic_declaration (c_parser *);
સ્થિર તાર્કિક c_parser_objc_diagnose_bad_element_prefix
  (c_parser *, સંરચના c_declspecs *);
સ્થિર location_t c_parser_parse_rtl_body (c_parser *, અક્ષર *);
સ્થિર વૃક્ષ c_parser_handle_musttail (c_parser *, વૃક્ષ, attr_state &);

#જો ENABLE_ANALYZER

નામાકાશ ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

વર્ગ c_translation_unit : જાહેર translation_unit
{
જાહેર:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  વૃક્ષ lookup_constant_by_id (વૃક્ષ id) અચલ final override
  {
    /* Consider decls.  */
    જો (વૃક્ષ decl = lookup_name (id))
      જો (વૃક્ષ_CODE (decl) == CONST_DECL)
	જો (વૃક્ષ કિંમત = DECL_INITIAL (decl))
	  જો (વૃક્ષ_CODE (કિંમત) == INTEGER_CST)
	    પાછા કિંમત;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    જો (cpp_macro_p (hashnode))
      જો (વૃક્ષ કિંમત = consider_macro (hashnode->કિંમત.macro))
	પાછા કિંમત;

    પાછા NULL_વૃક્ષ;
  }

  વૃક્ષ
  lookup_type_by_id (વૃક્ષ id) અચલ final override
  {
    જો (વૃક્ષ type_decl = lookup_name (id))
	જો (વૃક્ષ_CODE (type_decl) == TYPE_DECL)
	  {
	    વૃક્ષ record_type = વૃક્ષ_TYPE (type_decl);
	    જો (વૃક્ષ_CODE (record_type) == RECORD_TYPE)
	      પાછા record_type;
	  }

    પાછા NULL_વૃક્ષ;
  }

  વૃક્ષ
  lookup_global_var_by_id (વૃક્ષ id) અચલ final override
  {
    જો (વૃક્ષ var_decl = lookup_name (id))
      જો (વૃક્ષ_CODE (var_decl) == VAR_DECL)
				પાછા var_decl;

    પાછા NULL_વૃક્ષ;
  }

ખાનગી:
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
  વૃક્ષ consider_macro (cpp_macro *macro, પૂર્ણાંક depth = 0) અચલ
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (depth >= 0);

    જો (macro->paramc > 0)
      પાછા NULL_વૃક્ષ;
    જો (macro->kind != cmk_macro)
      પાછા NULL_વૃક્ષ;
    જો (macro->ગણતરી != 1)
      પાછા NULL_વૃક્ષ;
    અચલ cpp_token &tok = macro->exp.tokens[0];
    જો (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	જો (depth >= param_analyzer_max_macro_alias_depth)
	  પાછા NULL_વૃક્ષ;

	cpp_hashnode *alias = tok.val.ગાંઠ.ગાંઠ;
	જો (cpp_macro_p (alias))
	  પાછા consider_macro (alias->કિંમત.macro, depth + 1);

	/* Not a simple alias.  */
	પાછા NULL_વૃક્ષ;
      }
    નહીંતર જો (tok.type != CPP_સંખ્યા)
      પાછા NULL_વૃક્ષ;

    cpp_reader *old_parse_in = parse_in;
    parse_in = cpp_create_reader (CLK_GNUC89, ખાલી, લીટી_table);

    pretty_printer pp;
    pp_string (&pp, (અચલ અક્ષર *) tok.val.str.text);
    pp_newline (&pp);
    cpp_ધકેલો_buffer (parse_in,
		     (અચલ unsigned અક્ષર *) pp_formatted_text (&pp),
		     strlen (pp_formatted_text (&pp)),
		     0);

    વૃક્ષ કિંમત;
    location_t loc;
    unsigned અક્ષર cpp_flags;
    c_lex_with_flags (&કિંમત, &loc, &cpp_flags, 0);

    cpp_destroy (parse_in);
    parse_in = old_parse_in;

    જો (કિંમત && વૃક્ષ_CODE (કિંમત) == INTEGER_CST)
      પાછા કિંમત;

    પાછા NULL_વૃક્ષ;
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

સ્થિર શૂન્ય
c_parser_translation_unit (c_parser *parser)
{
  જો (c_parser_next_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  નહીંતર
    {
      શૂન્ય *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (ખોટું);
      કરો
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      જ્યારે (c_parser_next_token_is_not (parser, CPP_EOF));
    }

  unsigned પૂર્ણાંક i;
  વૃક્ષ decl;
  FOR_EACH_VEC_ELT (incomplete_record_decls, i, decl)
    જો (DECL_SIZE (decl) == NULL_વૃક્ષ && વૃક્ષ_TYPE (decl) != error_mark_ગાંઠ)
      error ("storage size of %q+D isn%'t known", decl);

  જો (vec_safe_length (current_omp_declare_target_attribute))
    {
      c_omp_declare_target_attr
	a = current_omp_declare_target_attribute->કાઢો ();
      જો (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_safe_truncate (current_omp_declare_target_attribute, 0);
    }
  જો (vec_safe_length (current_omp_begin_assumes))
    {
      જો (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_safe_truncate (current_omp_begin_assumes, 0);
    }
  જો (vec_safe_length (current_omp_declare_variant_attribute))
    {
      જો (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_safe_truncate (current_omp_declare_variant_attribute, 0);
    }
  જો (vec_safe_length (omp_begin_declare_variant_map))
    {
      unsigned પૂર્ણાંક i;
      omp_begin_declare_variant_map_entry *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_finish_variant_function (e->variant, e->id, e->ctx);
      vec_safe_truncate (omp_begin_declare_variant_map, 0);
    }

#જો ENABLE_ANALYZER
  જો (flag_analyzer)
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

સ્થિર શૂન્ય
c_parser_external_declaration (c_parser *parser)
{
  પૂર્ણાંક ext;
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_KEYWORD:
      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  તોડો;
	સ્થિતિ RID_ASM:
	  c_parser_asm_definition (parser);
	  તોડો;
	સ્થિતિ RID_AT_INTERFACE:
	સ્થિતિ RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_વૃક્ષ);
	  તોડો;
	સ્થિતિ RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  તોડો;
	સ્થિતિ RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  તોડો;
	સ્થિતિ RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_વૃક્ષ);
	  તોડો;
	સ્થિતિ RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  તોડો;
	સ્થિતિ RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  તોડો;
	સ્થિતિ RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  તોડો;
	સ્થિતિ RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  તોડો;
	મૂળભૂત:
	  જાઓ decl_or_fndef;
	}
      તોડો;
    સ્થિતિ CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      તોડો;
    સ્થિતિ CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (સાચું);
      c_parser_pragma (parser, pragma_external, ખાલી, NULL_વૃક્ષ);
      mark_valid_location_for_stdc_pragma (ખોટું);
      તોડો;
    સ્થિતિ CPP_PLUS:
    સ્થિતિ CPP_MINUS:
      જો (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  તોડો;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    મૂળભૂત:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, ખોટું, સાચું,
				     ખોટું);
      તોડો;
    }
}

સ્થિર શૂન્ય c_parser_handle_directive_omp_attributes (વૃક્ષ &, vec<c_token> *&,
						      vec<c_token> *);
સ્થિર શૂન્ય c_finish_omp_declare_simd (c_parser *, વૃક્ષ, વૃક્ષ, vec<c_token> *);
સ્થિર શૂન્ય c_finish_oacc_routine (સંરચના oacc_routine_data *, વૃક્ષ, તાર્કિક);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

સ્થિર શૂન્ય
add_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  જો (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    પાછા;

  વૃક્ષ stmt = build0 (DEBUG_BEGIN_STMT, void_type_ગાંઠ);
  SET_પદાવલિ_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

સ્થિર વૃક્ષ
handle_assume_attribute (location_t here, વૃક્ષ attrs, તાર્કિક nested)
{
  જો (nested)
    માટે (વૃક્ષ attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", વૃક્ષ_CHAIN (attr)))
      {
	વૃક્ષ args = વૃક્ષ_કિંમત (attr);
	પૂર્ણાંક nargs = list_length (args);
	જો (nargs != 1)
	  {
	    error_at (here, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (here, "expected %i, found %i", 1, nargs);
	  }
	નહીંતર
	  {
	    વૃક્ષ arg = વૃક્ષ_કિંમત (args);
	    arg = c_objc_common_truthvalue_conversion (here, arg);
	    arg = c_fully_fold (arg, ખોટું, ખાલી);
	    જો (arg != error_mark_ગાંઠ)
	      {
		વૃક્ષ fn = build_call_પદાવલિ_internal_loc (here, IFN_ASSUME,
							void_type_ગાંઠ, 1,
							arg);
		add_stmt (fn);
	      }
	  }
      }
  નહીંતર
    pedwarn (here, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  પાછા remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

સ્થિર શૂન્ય
c_parser_maybe_reclassify_token (c_parser *parser)
{
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      જો (token->id_kind == C_ID_ID || token->id_kind == C_ID_TYPENAME)
	{
	  વૃક્ષ decl = lookup_name (token->કિંમત);

	  token->id_kind = C_ID_ID;
	  જો (decl)
	    {
	      જો (વૃક્ષ_CODE (decl) == TYPE_DECL)
		token->id_kind = C_ID_TYPENAME;
	    }
	  નહીંતર જો (c_dialect_objc ())
	    {
	      વૃક્ષ objc_interface_decl = objc_is_class_name (token->કિંમત);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      જો (objc_interface_decl)
		{
		  token->કિંમત = objc_interface_decl;
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

સ્થિર વૃક્ષ
c_parser_declaration_or_fndef (c_parser *parser, તાર્કિક fndef_ok,
			       તાર્કિક static_assert_ok, તાર્કિક empty_ok,
			       તાર્કિક nested, તાર્કિક start_attr_ok,
			       તાર્કિક simple_ok,
			       વૃક્ષ *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       તાર્કિક have_attrs /* = false */,
			       વૃક્ષ attrs /* = NULL_TREE */,
			       સંરચના oacc_routine_data *oacc_routine_data
			       /* = NULL */,
			       તાર્કિક *fallthru_attr_p /* = NULL */)
{
  સંરચના c_declspecs *specs;
  વૃક્ષ prefix_attrs;
  વૃક્ષ all_prefix_attrs;
  તાર્કિક diagnosed_no_specs = ખોટું;
  location_t here = c_parser_peek_token (parser)->location;
  વૃક્ષ result = NULL_વૃક્ષ;

  add_debug_begin_stmt (c_parser_peek_token (parser)->location);

  જો (static_assert_ok
      && c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      પાછા result;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  જો (have_attrs)
    {
      declspecs_add_attrs (here, specs, attrs);
      specs->non_std_attrs_seen_p = ખોટું;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  જો (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_kind == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->કિંમત)))
    {
      વૃક્ષ name = c_parser_peek_token (parser)->કિંમત;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (here);
      જો (tag_exists_p (RECORD_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.add_fixit_ઉમેરો_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      નહીંતર જો (tag_exists_p (UNION_TYPE, name))
	{
	  richloc.add_fixit_ઉમેરો_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      નહીંતર જો (tag_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.add_fixit_ઉમેરો_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      નહીંતર
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      here);
	  જો (અચલ અક્ષર *suggestion = hint.suggestion ())
	    {
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  નહીંતર
	    error_at (here, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->કિંમત = error_mark_ગાંઠ;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  જો (c_parser_nth_token_starts_std_attributes (parser, 1))
    have_attrs = સાચું;

  c_parser_declspecs (parser, specs, સાચું, સાચું, start_attr_ok,
		      સાચું, સાચું, start_attr_ok, સાચું, cla_nonabstract_decl);
  જો (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      પાછા result;
    }
  જો (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      પાછા result;
    }

  finish_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  જો (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_ટોચ_anonymous_type (specs->type);

  તાર્કિક gnu_auto_type_p = specs->typespec_word == cts_auto_type;
  તાર્કિક std_auto_type_p = specs->c23_auto_p;
  તાર્કિક any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  અચલ અક્ષર *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  જો (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      પસંદગી (specs->typespec_kind)
	{
	સ્થિતિ ctsk_tagfirstref:
	સ્થિતિ ctsk_tagfirstref_attrs:
	  error_at (here, "%qT declared in underspecified object declaration",
		    specs->type);
	  તોડો;

	સ્થિતિ ctsk_tagdef:
	  error_at (here, "%qT defined in underspecified object declaration",
		    specs->type);
	  તોડો;

	મૂળભૂત:
	  તોડો;
	}
    }

  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      તાર્કિક handled_assume = ખોટું;
      જો (specs->attrs
	  && !nested
	  && specs->typespec_kind == ctsk_none
	  && c_parser_handle_statement_omp_attributes (parser, specs->attrs,
						       ખાલી))
	{
	  જો (specs->attrs)
	    c_warn_unused_attributes (specs->attrs);
	  જ્યારે (parser->in_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_next_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, ખાલી, NULL_વૃક્ષ);
	    }
	  c_parser_consume_token (parser);
	  પાછા result;
	}
      જો (specs->typespec_kind == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = સાચું;
	  specs->attrs
	    = handle_assume_attribute (here, specs->attrs, nested);
	}
      જો (any_auto_type_p)
	error_at (here, "%qs in empty declaration", auto_type_keyword);
      નહીંતર જો (specs->typespec_kind == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  જો (fallthru_attr_p != ખાલી)
	    *fallthru_attr_p = સાચું;
	  જો (nested)
	    {
	      વૃક્ષ fn = build_call_પદાવલિ_internal_loc (here, IFN_FALLTHROUGH,
						      void_type_ગાંઠ, 0);
	      add_stmt (fn);
	    }
	  નહીંતર
	    pedwarn (here, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      નહીંતર જો (empty_ok
	       && !(have_attrs && specs->non_std_attrs_seen_p)
	       && !handled_assume)
	shadow_tag (specs);
      નહીંતર
	{
	  shadow_tag_warned (specs, 1);
	  જો (!handled_assume)
	    pedwarn (here, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      જો (specs->પદાવલિ)
	add_stmt (fold_convert (void_type_ગાંઠ, specs->પદાવલિ));
      c_parser_consume_token (parser);
      જો (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, NULL_વૃક્ષ, ખોટું);
      પાછા result;
    }
  નહીંતર જો (specs->typespec_kind == ctsk_none
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
      જો (astate.musttail_p)
	{
	  જો (specs->attrs)
	    {
	      auto_urlify_attributes sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, ખાલી, NULL_વૃક્ષ, ખાલી,
					   astate);
	  પાછા result;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  જો (empty_ok
      && specs->typespec_kind == ctsk_tagdef
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = ખોટું;
      shadow_tag_warned (specs, 1);
      પાછા result;
    }
  નહીંતર જો (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      પસંદગી (c_parser_peek_token (parser)->type)
	{
	  સ્થિતિ CPP_PLUS:
	  સ્થિતિ CPP_MINUS:
	    જો (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      પાછા result;
	    જો (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_વૃક્ષ;
	      }
	    જો (fndef_ok)
	      c_parser_objc_method_definition (parser);
	    નહીંતર
	      c_parser_objc_methodproto (parser);
	    પાછા result;
	    તોડો;
	  મૂળભૂત:
	    તોડો;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_AT_INTERFACE:
	  {
	    જો (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      પાછા result;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    પાછા result;
	  }
	  તોડો;
	સ્થિતિ RID_AT_IMPLEMENTATION:
	  {
	    જો (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      પાછા result;
	    જો (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_વૃક્ષ;
	      }
	    c_parser_objc_class_definition (parser, NULL_વૃક્ષ);
	    પાછા result;
	  }
	  તોડો;
	સ્થિતિ RID_AT_PROTOCOL:
	  {
	    જો (c_parser_objc_diagnose_bad_element_prefix (parser, specs))
	      પાછા result;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    પાછા result;
	  }
	  તોડો;
	સ્થિતિ RID_AT_ALIAS:
	સ્થિતિ RID_AT_CLASS:
	સ્થિતિ RID_AT_END:
	સ્થિતિ RID_AT_PROPERTY:
	  જો (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = ખાલી;
	    }
	  તોડો;
	મૂળભૂત:
	  તોડો;
	}
    }
  નહીંતર જો (attribute_fallthrough_p (specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  નહીંતર જો (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (here, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_attributes (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_વૃક્ષ;
  તાર્કિક more_than_one_decl = ખોટું;
  જ્યારે (સાચું)
    {
      સંરચના c_declarator *declarator;
      તાર્કિક dummy = ખોટું;
      timevar_id_t tv;
      વૃક્ષ fnbody = NULL_વૃક્ષ;
      વૃક્ષ underspec_name = NULL_વૃક્ષ;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_kind != ctsk_none,
					C_DTR_NORMAL, &dummy);
      જો (declarator == ખાલી)
	{
	  જો (omp_declare_simd_clauses)
	    c_finish_omp_declare_simd (parser, NULL_વૃક્ષ, NULL_વૃક્ષ,
				       omp_declare_simd_clauses);
	  જો (oacc_routine_data)
	    c_finish_oacc_routine (oacc_routine_data, NULL_વૃક્ષ, ખોટું);
	  /* This check is here purely to improve the diagnostic.  */
	  જો (!simple_ok)
	    c_parser_skip_to_end_of_block_or_statement (parser);
	  પાછા result;
	}
      જો (flag_openmp || flag_openmp_simd)
	{
	  સંરચના c_declarator *d = declarator;
	  જ્યારે (d->kind != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = ખાલી;
	  c_parser_handle_directive_omp_attributes (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      જો (gnu_auto_type_p && declarator->kind != cdk_id)
	{
	  error_at (here,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  પાછા result;
	}
      જો (std_auto_type_p)
	{
	  સંરચના c_declarator *d = declarator;
	  જ્યારે (d->kind == cdk_attrs)
	    d = d->declarator;
	  જો (d->kind != cdk_id)
	    {
	      error_at (here,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      પાછા result;
	    }
	  underspec_name = d->u.id.id;
	}
      નહીંતર જો (specs->constexpr_p)
	{
	  સંરચના c_declarator *d = declarator;
	  જ્યારે (d->kind != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      જો (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_next_token_is_keyword (parser, RID_IN))
	{
	  વૃક્ષ asm_name = NULL_વૃક્ષ;
	  વૃક્ષ postfix_attrs = NULL_વૃક્ષ;
	  જો (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = સાચું;
	      pedwarn (here, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = ખોટું;
	  જો (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_પદાવલિ (parser);
	  જો (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_attributes (parser);
	      જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (here, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  પાછા result;
		}
	    }
	  જો (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      વૃક્ષ d;
	      સંરચના c_પદાવલિ init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      જો (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (લીટી_table, init_loc);
		  unsigned પૂર્ણાંક underspec_state = 0;
		  જો (std_auto_type_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  start_init (NULL_વૃક્ષ, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  જો (nested && !empty_ok)
		    flag_sanitize = 0;
		  init = c_parser_પદાવલિ_no_commas (parser, ખાલી);
		  જો (std_auto_type_p)
		    finish_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  જો (gnu_auto_type_p
		      && વૃક્ષ_CODE (init.કિંમત) == COMPONENT_REF
		      && DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (init.કિંમત, 1)))
		    error_at (here,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_to_rvalue (init_loc, init, સાચું, સાચું,
						   સાચું);
		  વૃક્ષ init_type = વૃક્ષ_TYPE (init.કિંમત);
		  તાર્કિક vm_type = c_type_variably_modified_p (init_type);
		  જો (vm_type)
		    init.કિંમત = save_પદાવલિ (init.કિંમત);
		  finish_init ();
		  specs->typespec_kind = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = સાચું;
		  specs->type = init_type;
		  જો (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_attributes (specs->type,
						  specs->postfix_attrs);
		      decl_attributes (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_વૃક્ષ;
		    }
		  જો (vm_type)
		    {
		      તાર્કિક maybe_const = સાચું;
		      વૃક્ષ type_પદાવલિ = c_fully_fold (init.કિંમત, ખોટું,
						     &maybe_const);
		      specs->પદાવલિ_const_operands &= maybe_const;
		      જો (specs->પદાવલિ)
			specs->પદાવલિ = build2 (COMPOUND_પદાવલિ,
					      વૃક્ષ_TYPE (type_પદાવલિ),
					      specs->પદાવલિ, type_પદાવલિ);
		      નહીંતર
			specs->પદાવલિ = type_પદાવલિ;
		    }
		  d = start_decl (declarator, specs, સાચું,
				  chainon (postfix_attrs, all_prefix_attrs));
		  જો (!d)
		    d = error_mark_ગાંઠ;
		  જો (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_વૃક્ષ,
					       omp_declare_simd_clauses);
		  જો (!omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_વૃક્ષ,
					       &omp_dsimd_idattr_clauses);
		}
	      નહીંતર
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (લીટી_table, init_loc);
		  unsigned પૂર્ણાંક underspec_state = 0;
		  જો (specs->constexpr_p)
		    underspec_state =
		      start_underspecified_init (init_loc, underspec_name);
		  d = start_decl (declarator, specs, સાચું,
				  chainon (postfix_attrs,
					   all_prefix_attrs),
				  !specs->constexpr_p);
		  જો (!d)
		    d = error_mark_ગાંઠ;
		  જો (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, NULL_વૃક્ષ,
					       omp_declare_simd_clauses);
		  જો (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_વૃક્ષ,
					       &omp_dsimd_idattr_clauses);
		  start_init (d, asm_name,
			      વૃક્ષ_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_code_type flag_sanitize_save = flag_sanitize;
		  જો (વૃક્ષ_CODE (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  જો (specs->constexpr_p)
		    {
		      finish_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      જો (omp_declare_simd_clauses)
			c_finish_omp_declare_simd (parser, d, NULL_વૃક્ષ,
						   omp_declare_simd_clauses);
		  જો (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, NULL_વૃક્ષ,
					       &omp_dsimd_idattr_clauses);
		    }
		  finish_init ();
		}
	      જો (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, ખોટું);
	      જો (d != error_mark_ગાંઠ)
		{
		  maybe_warn_string_init (init_loc, વૃક્ષ_TYPE (d), init);
		  finish_decl (d, init_loc, init.કિંમત,
			       init.original_type, asm_name);
		  result = d;
		}
	    }
	  નહીંતર
	    {
	      જો (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  પાછા result;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      વૃક્ષ attrs = chainon (postfix_attrs, all_prefix_attrs);
	      વૃક્ષ d = start_decl (declarator, specs, ખોટું, attrs, સાચું,
				   &lastloc);
	      જો (d && વૃક્ષ_CODE (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  અચલ સંરચના c_declarator *decl = declarator;
		  અચલ સંરચના c_declarator *last_non_id_attrs = ખાલી;

		  જ્યારે (decl)
		    પસંદગી (decl->kind)
		      {
		      સ્થિતિ cdk_array:
		      સ્થિતિ cdk_function:
		      સ્થિતિ cdk_pointer:
			last_non_id_attrs = decl;
			decl = decl->declarator;
			તોડો;

		      સ્થિતિ cdk_attrs:
			decl = decl->declarator;
			તોડો;

		      સ્થિતિ cdk_id:
			decl = 0;
			તોડો;

		      મૂળભૂત:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  જો (last_non_id_attrs
		      && last_non_id_attrs->kind == cdk_function)
		    {
		      વૃક્ષ parms = last_non_id_attrs->u.arg_info->parms;
		      જો (DECL_ARGUMENTS (d) == NULL_વૃક્ષ
			  && DECL_INITIAL (d) == NULL_વૃક્ષ)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      જો (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_empty ())
		{
		  વૃક્ષ parms = NULL_વૃક્ષ;
		  જો (d && વૃક્ષ_CODE (d) == FUNCTION_DECL)
		    {
		      સંરચના c_declarator *ce = declarator;
		      જ્યારે (ce != ખાલી)
			જો (ce->kind == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    તોડો;
			  }
			નહીંતર
			  ce = ce->declarator;
		    }
		  જો (parms)
		    temp_store_parm_decls (d, parms);
		  જો (omp_declare_simd_clauses)
		    c_finish_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  જો (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_empty ())
		    c_finish_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  જો (parms)
		    temp_કાઢો_parm_decls ();
		}
	      જો (oacc_routine_data)
		c_finish_oacc_routine (oacc_routine_data, d, ખોટું);
	      જો (d)
		finish_decl (d, UNKNOWN_LOCATION, NULL_વૃક્ષ,
			     NULL_વૃક્ષ, asm_name);

	      જો (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  જો (d)
		    *objc_foreach_object_declaration = d;
		  નહીંતર
		    *objc_foreach_object_declaration = error_mark_ગાંઠ;
		}
	    }
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      more_than_one_decl = સાચું;
	      જો (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (here,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		  પાછા result;
		}
	      c_parser_consume_token (parser);
	      જો (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					    prefix_attrs);
	      નહીંતર
		all_prefix_attrs = prefix_attrs;
	      ચાલુ;
	    }
	  નહીંતર જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      જો (!simple_ok)
		c_parser_consume_token (parser);
	      પાછા result;
	    }
	  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      પાછા result;
	    }
	  નહીંતર
	    {
	      જો (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_to_end_of_block_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      નહીંતર જો (more_than_one_decl)
		error_at (here, "declaration in condition can only declare "
			  "a single object");
	      પાછા result;
	    }
	}
      નહીંતર જો (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (here,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  પાછા result;
	}
      નહીંતર જો (!fndef_ok)
	{
	  જો (simple_ok && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  નહીંતર
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	    }
	  પાછા result;
	}
      /* Function definition (nested or otherwise).  */
      જો (nested)
	{
	  pedwarn (here, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_ધકેલો_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      વૃક્ષ dv_base = NULL_વૃક્ષ;
      વૃક્ષ dv_ctx = NULL_વૃક્ષ;
      જો (!vec_safe_is_empty (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->last ();
	  dv_ctx = copy_list (a.selector);
	  dv_base = omp_start_variant_function (declarator, dv_ctx);
	}

      જો (!start_function (specs, declarator, all_prefix_attrs))
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
	  જો (c_parser_next_token_starts_declspecs (parser))
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
	      parser->error = ખોટું;
	    }
	  નહીંતર
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  જો (nested)
	    c_કાઢો_function_context ();
	  તોડો;
	}

      જો (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      નહીંતર
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
      પૂર્ણાંક save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      જ્યારે (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, ખોટું, ખોટું, ખોટું,
				       સાચું, ખોટું, ખોટું);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      જો (omp_declare_simd_clauses)
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_વૃક્ષ,
				   omp_declare_simd_clauses);
      જો (!omp_dsimd_idattr_clauses.is_empty ())
	c_finish_omp_declare_simd (parser, current_function_decl, NULL_વૃક્ષ,
				   &omp_dsimd_idattr_clauses);
      જો (oacc_routine_data)
	c_finish_oacc_routine (oacc_routine_data, current_function_decl, સાચું);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_start_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      જો (dv_base && current_function_decl != error_mark_ગાંઠ)
	{
	  omp_begin_declare_variant_map_entry e
	    = { current_function_decl, dv_base, dv_ctx };
	  vec_safe_ધકેલો (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      જો (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  ધકેલો_scope ();
	  કાઢો_scope ();

	  finish_function (endloc);
	  પાછા result;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      નહીંતર જો (specs->declspec_il != cdil_none)
	{
	  તાર્કિક saved = in_late_દ્વિઅંકી_op;
	  in_late_દ્વિઅંકી_op = સાચું;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->entry_bb_ગણતરી);
	  in_late_દ્વિઅંકી_op = saved;
	}
      નહીંતર
	fnbody = c_parser_compound_statement (parser, &endloc);
      વૃક્ષ fndecl = current_function_decl;
      જો (nested && specs->declspec_il == cdil_none)
	{
	  વૃક્ષ decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  add_stmt (fnbody);
	  finish_function (endloc);
	  c_કાઢો_function_context ();
	  add_stmt (build_stmt (DECL_SOURCE_LOCATION (decl), DECL_પદાવલિ, decl));
	}
      નહીંતર જો (nested)
	{
	  જો (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  નહીંતર
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  finish_function (endloc);
	  c_કાઢો_function_context ();
	}
      નહીંતર
	{
	  જો (fnbody)
	    add_stmt (fnbody);
	  finish_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      જો (specs->declspec_il != cdil_none)
	DECL_SAVED_વૃક્ષ (fndecl) = NULL_વૃક્ષ;

      તોડો;
    }

  પાછા result;
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

સ્થિર શૂન્ય
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  વૃક્ષ asm_str = NULL_વૃક્ષ;
  વૃક્ષ outputs = NULL_વૃક્ષ, inputs = NULL_વૃક્ષ;
  જો (!parens.require_open (parser))
    જાઓ done;
  asm_str = c_parser_asm_string_literal (parser);
  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      જાઓ done;
    }
  માટે (પૂર્ણાંક section = 0; section < 2; ++section)
    {
      જો (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  જો (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	      asm_str = NULL_વૃક્ષ;
	      જાઓ done;
	    }
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, ખોટું))
	જાઓ error_close_paren;
      જો (!c_parser_next_token_is (parser, CPP_COLON)
	  && !c_parser_next_token_is (parser, CPP_SCOPE)
	  && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  જો (section)
	    inputs = c_parser_asm_operands (parser);
	  નહીંતર
	    outputs = c_parser_asm_operands (parser);
	}
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	તોડો;
    }

  જો (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
      asm_str = NULL_વૃક્ષ;
    }

  જો (asm_str)
    asm_str = build_asm_પદાવલિ (asm_loc, asm_str, outputs, inputs,
			      NULL_વૃક્ષ, NULL_વૃક્ષ, ખોટું, ખોટું);
done:
  જો (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

સ્થિર શૂન્ય
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  જો (parser->error
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

સ્થિર શૂન્ય
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, કિંમત_loc;
  વૃક્ષ કિંમત;
  વૃક્ષ string = NULL_વૃક્ષ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT));
  વૃક્ષ spelling = c_parser_peek_token (parser)->કિંમત;
  assert_loc = c_parser_peek_token (parser)->location;
  જો (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  નહીંતર
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા;
  location_t કિંમત_tok_loc = c_parser_peek_token (parser)->location;
  કિંમત = convert_lvalue_to_rvalue (કિંમત_tok_loc,
				    c_parser_પદાવલિ_no_commas (parser, ખાલી),
				    સાચું, સાચું).કિંમત;
  કિંમત_loc = પદાવલિ_LOC_OR_LOC (કિંમત, કિંમત_tok_loc);
  જો (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_STRING:
	સ્થિતિ CPP_STRING16:
	સ્થિતિ CPP_STRING32:
	સ્થિતિ CPP_WSTRING:
	સ્થિતિ CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, ખોટું, સાચું).કિંમત;
	  તોડો;
	મૂળભૂત:
	  c_parser_error (parser, "expected string literal");
	  પાછા;
	}
    }
  નહીંતર જો (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (કિંમત)))
    {
      error_at (કિંમત_loc, "expression in static assertion is not an integer");
      પાછા;
    }
  જો (વૃક્ષ_CODE (કિંમત) != INTEGER_CST)
    {
      કિંમત = c_fully_fold (કિંમત, ખોટું, ખાલી);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (કિંમત);
      જો (વૃક્ષ_CODE (કિંમત) == INTEGER_CST)
	pedwarn (કિંમત_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  જો (વૃક્ષ_CODE (કિંમત) != INTEGER_CST)
    {
      error_at (કિંમત_loc, "expression in static assertion is not constant");
      પાછા;
    }
  constant_expression_warning (કિંમત);
  જો (integer_zerop (કિંમત))
    {
      જો (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      નહીંતર
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

શૂન્ય
c_parser_declspecs (c_parser *parser, સંરચના c_declspecs *specs,
		    તાર્કિક scspec_ok, તાર્કિક typespec_ok, તાર્કિક start_attr_ok,
		    તાર્કિક alignspec_ok, તાર્કિક auto_type_ok,
		    તાર્કિક start_std_attr_ok, તાર્કિક end_std_attr_ok,
		    ગણના c_lookahead_kind la)
{
  તાર્કિક attrs_ok = start_attr_ok;
  તાર્કિક seen_type = specs->typespec_kind != ctsk_none;

  જો (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  જો (start_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_seen_p);
      location_t loc = c_parser_peek_token (parser)->location;
      વૃક્ષ attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_add_attrs (loc, specs, attrs);
      specs->non_std_attrs_seen_p = ખોટું;
    }

  જ્યારે (c_parser_next_token_is (parser, CPP_NAME)
	 || c_parser_next_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_next_token_is (parser, CPP_LESS)))
    {
      સંરચના c_typespec t;
      વૃક્ષ attrs;
      વૃક્ષ align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      જો ((!typespec_ok || specs->typespec_kind == ctsk_tagdef)
	  && c_parser_next_tokens_start_typename (parser, la)
	  && !c_parser_next_token_is_qualifier (parser)
	  && !c_parser_next_token_is_keyword (parser, RID_ALIGNAS))
	તોડો;

      જો (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  વૃક્ષ કિંમત = name_token->કિંમત;
	  c_id_kind kind = name_token->id_kind;

	  જો (kind == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_FIRST_ADDR_SPACE;
	      declspecs_add_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = સાચું;
	      ચાલુ;
	    }

	  gcc_assert (!c_parser_next_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  જો (seen_type || !c_parser_next_tokens_start_typename (parser, la))
	    તોડો;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  seen_type = સાચું;
	  attrs_ok = સાચું;
	  જો (kind == C_ID_ID)
	    {
	      auto_diagnostic_group d;
	      name_hint hint = lookup_name_fuzzy (કિંમત, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      જો (અચલ અક્ષર *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.add_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    કિંમત, suggestion);
		}
	      નહીંતર
		error_at (loc, "unknown type name %qE", કિંમત);
	      t.kind = ctsk_typedef;
	      t.spec = error_mark_ગાંઠ;
	    }
	  નહીંતર જો (kind == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_next_token_is_not (parser, CPP_LESS)))
	    {
	      t.kind = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (કિંમત);
	    }
	  નહીંતર
	    {
	      વૃક્ષ proto = NULL_વૃક્ષ;
	      gcc_assert (c_dialect_objc ());
	      t.kind = ctsk_objc;
	      જો (c_parser_next_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (કિંમત, proto);
	    }
	  t.પદાવલિ = NULL_વૃક્ષ;
	  t.પદાવલિ_const_operands = સાચું;
	  t.has_enum_type_specifier = ખોટું;
	  declspecs_add_type (name_token->location, specs, t);
	  ચાલુ;
	}
      જો (c_parser_next_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  વૃક્ષ proto;
	  gcc_assert (c_dialect_objc ());
	  જો (!typespec_ok || seen_type)
	    તોડો;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.kind = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_વૃક્ષ, proto);
	  t.પદાવલિ = NULL_વૃક્ષ;
	  t.પદાવલિ_const_operands = સાચું;
	  t.has_enum_type_specifier = ખોટું;
	  declspecs_add_type (loc, specs, t);
	  ચાલુ;
	}
      gcc_assert (c_parser_next_token_is (parser, CPP_KEYWORD));
      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_STATIC:
	સ્થિતિ RID_EXTERN:
	સ્થિતિ RID_REGISTER:
	સ્થિતિ RID_TYPEDEF:
	સ્થિતિ RID_INLINE:
	સ્થિતિ RID_NORETURN:
	સ્થિતિ RID_AUTO:
	સ્થિતિ RID_THREAD:
	સ્થિતિ RID_CONSTEXPR:
	  જો (!scspec_ok)
	    જાઓ out;
	  attrs_ok = સાચું;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_add_scspec (loc, specs,
				c_parser_peek_token (parser)->કિંમત);
	  c_parser_consume_token (parser);
	  તોડો;
	સ્થિતિ RID_AUTO_TYPE:
	  જો (!auto_type_ok)
	    જાઓ out;
	  /* Fall through.  */
	સ્થિતિ RID_UNSIGNED:
	સ્થિતિ RID_LONG:
	સ્થિતિ RID_SHORT:
	સ્થિતિ RID_SIGNED:
	સ્થિતિ RID_COMPLEX:
	સ્થિતિ RID_INT:
	સ્થિતિ RID_CHAR:
	સ્થિતિ RID_FLOAT:
	સ્થિતિ RID_DOUBLE:
	સ્થિતિ RID_VOID:
	સ્થિતિ RID_DFLOAT32:
	સ્થિતિ RID_DFLOAT64:
	સ્થિતિ RID_DFLOAT128:
	સ્થિતિ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	સ્થિતિ RID_BOOL:
	સ્થિતિ RID_FRACT:
	સ્થિતિ RID_ACCUM:
	સ્થિતિ RID_SAT:
	સ્થિતિ RID_INT_N_0:
	સ્થિતિ RID_INT_N_1:
	સ્થિતિ RID_INT_N_2:
	સ્થિતિ RID_INT_N_3:
	  જો (!typespec_ok)
	    જાઓ out;
	  attrs_ok = સાચું;
	  seen_type = સાચું;
	  જો (c_dialect_objc ())
	    parser->objc_need_raw_identifier = સાચું;
	  t.kind = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->કિંમત;
	  t.પદાવલિ = NULL_વૃક્ષ;
	  t.પદાવલિ_const_operands = સાચું;
	  t.has_enum_type_specifier = ખોટું;
	  declspecs_add_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  તોડો;
	સ્થિતિ RID_ENUM:
	  જો (!typespec_ok)
	    જાઓ out;
	  attrs_ok = સાચું;
	  seen_type = સાચું;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  તોડો;
	સ્થિતિ RID_STRUCT:
	સ્થિતિ RID_UNION:
	  જો (!typespec_ok)
	    જાઓ out;
	  attrs_ok = સાચું;
	  seen_type = સાચું;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_FINISH_TYPE, t.spec);
	  declspecs_add_type (loc, specs, t);
	  તોડો;
	સ્થિતિ RID_TYPEOF:
	સ્થિતિ RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  જો (!typespec_ok || seen_type)
	    જાઓ out;
	  attrs_ok = સાચું;
	  seen_type = સાચું;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_add_type (loc, specs, t);
	  તોડો;
	સ્થિતિ RID_BITINT:
	  જો (!typespec_ok)
	    જાઓ out;
	  નહીંતર
	    {
	      attrs_ok = સાચું;
	      seen_type = સાચું;
	      t.kind = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->કિંમત;
	      t.પદાવલિ = error_mark_ગાંઠ;
	      t.પદાવલિ_const_operands = સાચું;
	      t.has_enum_type_specifier = ખોટું;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      જો (parens.require_open (parser))
		{
		  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
		  t.પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, સાચું,
						     સાચું).કિંમત;
		  parens.skip_until_found_close (parser);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  તોડો;
	સ્થિતિ RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  જો (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  જો (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  નહીંતર
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = સાચું;
	  વૃક્ષ કિંમત;
	  કિંમત = c_parser_peek_token (parser)->કિંમત;
	  c_parser_consume_token (parser);
	  જો (typespec_ok && c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      seen_type = સાચું;
	      c_parser_consume_token (parser);
	      સંરચના c_type_name *type = c_parser_type_name (parser);
	      t.kind = ctsk_typeof;
	      t.spec = error_mark_ગાંઠ;
	      t.પદાવલિ = NULL_વૃક્ષ;
	      t.પદાવલિ_const_operands = સાચું;
	      t.has_enum_type_specifier = ખોટું;
	      જો (type != ખાલી)
		t.spec = groktypename (type, &t.પદાવલિ,
				       &t.પદાવલિ_const_operands);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      જો (t.spec != error_mark_ગાંઠ)
		{
		  જો (વૃક્ષ_CODE (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  નહીંતર જો (વૃક્ષ_CODE (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  નહીંતર જો (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  નહીંતર
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_add_type (loc, specs, t);
	    }
	  નહીંતર
	    declspecs_add_qual (loc, specs, કિંમત);
	  તોડો;
	સ્થિતિ RID_CONST:
	સ્થિતિ RID_VOLATILE:
	સ્થિતિ RID_RESTRICT:
	  attrs_ok = સાચું;
	  declspecs_add_qual (loc, specs, c_parser_peek_token (parser)->કિંમત);
	  c_parser_consume_token (parser);
	  તોડો;
	સ્થિતિ RID_ATTRIBUTE:
	  જો (!attrs_ok)
	    જાઓ out;
	  attrs = c_parser_gnu_attributes (parser);
	  declspecs_add_attrs (loc, specs, attrs);
	  તોડો;
	સ્થિતિ RID_ALIGNAS:
	  જો (!alignspec_ok)
	    જાઓ out;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_add_alignas (loc, specs, align);
	  તોડો;
	સ્થિતિ RID_GIMPLE:
	  જો (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  તોડો;
	સ્થિતિ RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  તોડો;
	મૂળભૂત:
	  જાઓ out;
	}
    }
 out:
  જો (end_std_attr_ok
      && c_parser_nth_token_starts_std_attributes (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

સ્થિર શૂન્ય
report_bad_enum_name (c_parser *parser)
{
  જો (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      પસંદગી (token->type)
	{
	મૂળભૂત:
	  તોડો;
	સ્થિતિ CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = સાચું;
	  પાછા;
	સ્થિતિ CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  જો (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_group d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_POINTER (token->કિંમત));
	      add_note_about_new_keyword (token->location,
					  token->કિંમત);
	      parser->error = સાચું;
	      પાછા;
	    }
	  તોડો;
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

સ્થિર સંરચના c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  સંરચના c_typespec ret;
  તાર્કિક have_std_attrs;
  તાર્કિક potential_nesting_p = ખોટું;
  વૃક્ષ std_attrs = NULL_વૃક્ષ;
  વૃક્ષ attrs;
  વૃક્ષ ident = NULL_વૃક્ષ;
  વૃક્ષ fixed_underlying_type = NULL_વૃક્ષ;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  જો (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->કિંમત;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  જો (c_parser_next_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      જો (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, સાચું);
	  જો (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_વૃક્ષ == TYPE_કિંમતો (ret.spec);
	}
      નહીંતર
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_વૃક્ષ;
	  ret.kind = ctsk_tagdef;
	  ret.પદાવલિ = NULL_વૃક્ષ;
	  ret.પદાવલિ_const_operands = સાચું;
	  ret.has_enum_type_specifier = સાચું;
	}
      c_parser_consume_token (parser);
      સંરચના c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, ખોટું, સાચું, ખોટું, ખોટું, ખોટું,
			  ખોટું, સાચું, cla_prefer_id);
      finish_declspecs (specs);
      જો (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      નહીંતર જો (વૃક્ષ_CODE (specs->type) != INTEGER_TYPE
	       && વૃક્ષ_CODE (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || વૃક્ષ_CODE (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_ગાંઠ;
	}
      નહીંતર જો (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      જો (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  જો (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_વૃક્ષ)
	    {
	      TYPE_MIN_કિંમત (ret.spec) =
		TYPE_MIN_કિંમત (fixed_underlying_type);
	      TYPE_MAX_કિંમત (ret.spec) =
		TYPE_MAX_કિંમત (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      SET_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_SIZE (ret.spec) = NULL_વૃક્ષ;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  નહીંતર જો (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      સંરચના c_enum_contents the_enum;
      વૃક્ષ type;
      વૃક્ષ postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      વૃક્ષ કિંમતો;
      timevar_ધકેલો (TV_PARSE_ENUM);
      type = start_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      કિંમતો = NULL_વૃક્ષ;
      c_parser_consume_token (parser);
      જ્યારે (સાચું)
	{
	  વૃક્ષ enum_id;
	  વૃક્ષ enum_કિંમત;
	  વૃક્ષ enum_decl;
	  તાર્કિક seen_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, કિંમત_loc;
	  જો (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ખાલી);
	      કિંમતો = error_mark_ગાંઠ;
	      તોડો;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->કિંમત;
	  /* Set the location in case we create a decl now.  */
	  c_parser_set_source_position_from_token (token);
	  decl_loc = કિંમત_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  વૃક્ષ std_attrs = NULL_વૃક્ષ;
	  જો (c_parser_nth_token_starts_std_attributes (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  વૃક્ષ enum_attrs = chainon (std_attrs,
				     c_parser_gnu_attributes (parser));
	  જો (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      કિંમત_loc = c_parser_peek_token (parser)->location;
	      enum_કિંમત = convert_lvalue_to_rvalue (કિંમત_loc,
						     (c_parser_પદાવલિ_no_commas
						      (parser, ખાલી)),
						     સાચું, સાચું).કિંમત;
	    }
	  નહીંતર
	    enum_કિંમત = NULL_વૃક્ષ;
	  enum_decl = build_enumerator (decl_loc, કિંમત_loc,
					&the_enum, enum_id, enum_કિંમત);
	  જો (enum_attrs)
	    decl_attributes (&વૃક્ષ_PURPOSE (enum_decl), enum_attrs, 0);
	  વૃક્ષ_CHAIN (enum_decl) = કિંમતો;
	  કિંમતો = enum_decl;
	  seen_comma = ખોટું;
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      seen_comma = સાચું;
	      c_parser_consume_token (parser);
	    }
	  જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      જો (seen_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      તોડો;
	    }
	  જો (!seen_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ખાલી);
	      કિંમતો = error_mark_ગાંઠ;
	      તોડો;
	    }
	}
      postfix_attrs = c_parser_gnu_attributes (parser);
      ret.spec = finish_enum (type, nreverse (કિંમતો),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.kind = ctsk_tagdef;
      ret.પદાવલિ = NULL_વૃક્ષ;
      ret.પદાવલિ_const_operands = સાચું;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_વૃક્ષ;
      timevar_કાઢો (TV_PARSE_ENUM);
      પાછા ret;
    }
  નહીંતર જો (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ગાંઠ;
      ret.kind = ctsk_tagref;
      ret.પદાવલિ = NULL_વૃક્ષ;
      ret.પદાવલિ_const_operands = સાચું;
      ret.has_enum_type_specifier = ખોટું;
      પાછા ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  જો (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  જો (fixed_underlying_type == NULL_વૃક્ષ)
    {
      ret = parser_xref_tag (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, ખોટું);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      જો (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  પાછા ret;
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

સ્થિર સંરચના c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  સંરચના c_typespec ret;
  તાર્કિક have_std_attrs;
  વૃક્ષ std_attrs = NULL_વૃક્ષ;
  વૃક્ષ attrs;
  વૃક્ષ ident = NULL_વૃક્ષ;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  ગણના વૃક્ષ_code code;
  પસંદગી (c_parser_peek_token (parser)->keyword)
    {
    સ્થિતિ RID_STRUCT:
      code = RECORD_TYPE;
      તોડો;
    સ્થિતિ RID_UNION:
      code = UNION_TYPE;
      તોડો;
    મૂળભૂત:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  જો (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_attributes (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_set_source_position_from_token (c_parser_peek_token (parser));

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->કિંમત;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      વર્ગ c_struct_parse_info *struct_info;
      વૃક્ષ type = start_struct (struct_loc, code, ident, &struct_info);
      વૃક્ષ postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      વૃક્ષ contents;
      વૃક્ષ પદાવલિ = ખાલી;
      timevar_ધકેલો (TV_PARSE_STRUCT);
      contents = NULL_વૃક્ષ;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      જો (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  વૃક્ષ name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  જો (!parens.require_open (parser))
	    જાઓ end_at_defs;
	  જો (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->કિંમત;
	      c_parser_consume_token (parser);
	    }
	  નહીંતર
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	      જાઓ end_at_defs;
	    }
	  parens.skip_until_found_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      જ્યારે (સાચું)
	{
	  વૃક્ષ decls;
	  /* Parse any stray semicolon.  */
	  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.add_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      ચાલુ;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      તોડો;
	    }
	  /* Accept #pragmas at struct scope.  */
	  જો (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, ખાલી, NULL_વૃક્ષ);
	      ચાલુ;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &પદાવલિ);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  નહીંતર
	    {
	      જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      નહીંતર જો (parser->error
		       || !c_parser_next_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ખાલી);
		  તોડો;
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
				struct_info, &પદાવલિ);
      ret.kind = ctsk_tagdef;
      ret.પદાવલિ = પદાવલિ;
      ret.પદાવલિ_const_operands = સાચું;
      ret.has_enum_type_specifier = ખોટું;
      timevar_કાઢો (TV_PARSE_STRUCT);
      પાછા ret;
    }
  નહીંતર જો (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ગાંઠ;
      ret.kind = ctsk_tagref;
      ret.પદાવલિ = NULL_વૃક્ષ;
      ret.પદાવલિ_const_operands = સાચું;
      ret.has_enum_type_specifier = ખોટું;
      પાછા ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  જો (have_std_attrs && c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_tag (ident_loc, code, ident, have_std_attrs, std_attrs,
			 ખોટું);
  પાછા ret;
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

સ્થિર વૃક્ષ
c_parser_struct_declaration (c_parser *parser, વૃક્ષ *પદાવલિ)
{
  સંરચના c_declspecs *specs;
  વૃક્ષ prefix_attrs;
  વૃક્ષ all_prefix_attrs;
  વૃક્ષ decls;
  location_t decl_loc;
  જો (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      પૂર્ણાંક ext;
      વૃક્ષ decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, પદાવલિ);
      restore_extension_diagnostics (ext);
      પાછા decl;
    }
  જો (c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      પાછા NULL_વૃક્ષ;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, ખોટું, સાચું, સાચું,
		      સાચું, ખોટું, સાચું, સાચું, cla_nonabstract_decl);
  જો (parser->error)
    પાછા NULL_વૃક્ષ;
  જો (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      પાછા NULL_વૃક્ષ;
    }
  finish_declspecs (specs);
  જો (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      વૃક્ષ ret;
      જો (specs->typespec_kind == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_tag_warned (specs, pedantic);
	  ret = NULL_વૃક્ષ;
	}
      નહીંતર
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  વૃક્ષ attrs = ખાલી;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_વૃક્ષ), specs,
			   NULL_વૃક્ષ, &attrs, પદાવલિ);
	  જો (ret)
	    decl_attributes (&ret, attrs, 0);
	}
      પાછા ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  જો (specs->typespec_kind == ctsk_tagdef
      && વૃક્ષ_CODE (specs->type) != ENUMERAL_TYPE
      && c_parser_next_token_starts_declspecs (parser)
      && !c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = ખોટું;
      પાછા NULL_વૃક્ષ;
    }

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_વૃક્ષ;
  decls = NULL_વૃક્ષ;
  જ્યારે (સાચું)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      સંરચના c_declarator *declarator;
      તાર્કિક dummy = ખોટું;
      જો (c_parser_next_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_વૃક્ષ);
      નહીંતર
	declarator = c_parser_declarator (parser,
					  specs->typespec_kind != ctsk_none,
					  C_DTR_NORMAL, &dummy);
      જો (declarator == ખાલી)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  તોડો;
	}
      જો (c_parser_next_token_is (parser, CPP_COLON)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  વૃક્ષ postfix_attrs = NULL_વૃક્ષ;
	  વૃક્ષ width = NULL_વૃક્ષ;
	  વૃક્ષ d;
	  જો (c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      width = convert_lvalue_to_rvalue (loc,
						(c_parser_પદાવલિ_no_commas
						 (parser, ખાલી)),
						સાચું, સાચું).કિંમત;
	    }
	  જો (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_attributes (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, width, &all_prefix_attrs, પદાવલિ);
	  decl_attributes (&d, chainon (postfix_attrs,
					all_prefix_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  જો (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_prefix_attrs = chainon (c_parser_gnu_attributes (parser),
					prefix_attrs);
	  નહીંતર
	    all_prefix_attrs = prefix_attrs;
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  નહીંતર જો (c_parser_next_token_is (parser, CPP_SEMICOLON)
		   || c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      તોડો;
	    }
	  નહીંતર
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      તોડો;
	    }
	}
      નહીંતર
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  તોડો;
	}
    }
  પાછા decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

સ્થિર સંરચના c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  તાર્કિક is_unqual;
  તાર્કિક is_std;
  સંરચના c_typespec ret;
  ret.kind = ctsk_typeof;
  ret.spec = error_mark_ગાંઠ;
  ret.પદાવલિ = NULL_વૃક્ષ;
  ret.પદાવલિ_const_operands = સાચું;
  ret.has_enum_type_specifier = ખોટું;
  જો (c_parser_next_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = ખોટું;
      વૃક્ષ spelling = c_parser_peek_token (parser)->કિંમત;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_POINTER (spelling), "typeof") == 0);
    }
  નહીંતર
    {
      gcc_assert (c_parser_next_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = સાચું;
      વૃક્ષ spelling = c_parser_peek_token (parser)->કિંમત;
      is_std = strcmp (IDENTIFIER_POINTER (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_typeof++;
  matching_parens parens;
  જો (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      પાછા ret;
    }
  જો (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      સંરચના c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      જો (type != ખાલી)
	{
	  ret.spec = groktypename (type, &ret.પદાવલિ, &ret.પદાવલિ_const_operands);
	  કાઢો_maybe_used (c_type_variably_modified_p (ret.spec));
	}
    }
  નહીંતર
    {
      તાર્કિક was_vm;
      location_t here = c_parser_peek_token (parser)->location;
      સંરચના c_પદાવલિ પદાવલિ = c_parser_expression (parser);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (પદાવલિ.કિંમત, 1)))
	error_at (here, "%<typeof%> applied to a bit-field");
      mark_exp_read (પદાવલિ.કિંમત);
      ret.spec = વૃક્ષ_TYPE (પદાવલિ.કિંમત);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      જો (was_vm)
	ret.પદાવલિ = c_fully_fold (પદાવલિ.કિંમત, ખોટું, &ret.પદાવલિ_const_operands);
      કાઢો_maybe_used (was_vm);
    }
  parens.skip_until_found_close (parser);
  જો (ret.spec != error_mark_ગાંઠ)
    {
      જો (is_unqual)
	{
	  તાર્કિક is_array = વૃક્ષ_CODE (ret.spec) == ARRAY_TYPE;
	  પૂર્ણાંક quals = TYPE_QUALS (strip_array_types (ret.spec));
	  જો ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      જો (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      જો (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  જો (વૃક્ષ_CODE (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  નહીંતર જો (FUNCTION_POINTER_TYPE_P (ret.spec)
		   && TYPE_QUALS (વૃક્ષ_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_pointer_type (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (ret.spec)));
	}
    }
  પાછા ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

સ્થિર વૃક્ષ
c_parser_alignas_specifier (c_parser * parser)
{
  વૃક્ષ ret = error_mark_ગાંઠ;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNAS));
  વૃક્ષ spelling = c_parser_peek_token (parser)->કિંમત;
  c_parser_consume_token (parser);
  જો (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  નહીંતર
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા ret;
  જો (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      સંરચના c_type_name *type = c_parser_type_name (parser);
      જો (type != ખાલી)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, ખાલી, ખાલી),
					ખોટું, સાચું, 1);
    }
  નહીંતર
    ret = convert_lvalue_to_rvalue (loc,
				    c_parser_પદાવલિ_no_commas (parser, ખાલી),
				    સાચું, સાચું).કિંમત;
  parens.skip_until_found_close (parser);
  પાછા ret;
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

સંરચના c_declarator *
c_parser_declarator (c_parser *parser, તાર્કિક type_seen_p, c_dtr_syn kind,
		     તાર્કિક *seen_id)
{
  /* Parse any initial pointer part.  */
  જો (c_parser_next_token_is (parser, CPP_MULT))
    {
      સંરચના c_declspecs *quals_attrs = build_null_declspecs ();
      સંરચના c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, ખોટું, ખોટું, સાચું,
			  ખોટું, ખોટું, સાચું, ખોટું, cla_prefer_id);
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      જો (inner == ખાલી)
	પાછા ખાલી;
      નહીંતર
	પાછા make_pointer_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  પાછા c_parser_direct_declarator (parser, type_seen_p, kind, seen_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

સ્થિર સંરચના c_declarator *
c_parser_direct_declarator (c_parser *parser, તાર્કિક type_seen_p, c_dtr_syn kind,
			    તાર્કિક *seen_id)
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

  જો (kind != C_DTR_ABSTRACT
      && c_parser_next_token_is (parser, CPP_NAME)
      && ((type_seen_p
	   && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_kind == C_ID_ID))
    {
      સંરચના c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->કિંમત);
      *seen_id = સાચું;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      જો (c_parser_nth_token_starts_std_attributes (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      પાછા c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  જો (kind != C_DTR_NORMAL
      && c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      સંરચના c_declarator *inner = build_id_declarator (NULL_વૃક્ષ);
      inner->id_loc = c_parser_peek_token (parser)->location;
      પાછા c_parser_direct_declarator_inner (parser, *seen_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      વૃક્ષ attrs;
      સંરચના c_declarator *inner;
      c_parser_consume_token (parser);
      તાર્કિક have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      જો (kind != C_DTR_NORMAL
	  && (c_parser_next_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_attributes (parser, 1)
		      || c_parser_next_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  સંરચના c_arg_info *args
	    = c_parser_parms_declarator (parser, kind == C_DTR_NORMAL,
					 attrs, have_gnu_attrs);
	  જો (args == ખાલી)
	    પાછા ખાલી;
	  નહીંતર
	    {
	      inner = build_id_declarator (NULL_વૃક્ષ);
	      જો (!(args->types
		    && args->types != error_mark_ગાંઠ
		    && વૃક્ષ_CODE (વૃક્ષ_કિંમત (args->types)) == IDENTIFIER_ગાંઠ)
		  && c_parser_nth_token_starts_std_attributes (parser, 1))
		{
		  વૃક્ષ std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  જો (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (args, inner);
	      પાછા c_parser_direct_declarator_inner (parser, *seen_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_seen_p, kind, seen_id);
      જો (inner != ખાલી && attrs != ખાલી)
	inner = build_attrs_declarator (attrs, inner);
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  જો (inner == ખાલી)
	    પાછા ખાલી;
	  નહીંતર
	    પાછા c_parser_direct_declarator_inner (parser, *seen_id, inner);
	}
      નહીંતર
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  પાછા ખાલી;
	}
    }
  નહીંતર
    {
      જો (kind == C_DTR_NORMAL)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  પાછા ખાલી;
	}
      નહીંતર
	પાછા build_id_declarator (NULL_વૃક્ષ);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

સ્થિર સંરચના c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, તાર્કિક id_present,
				  સંરચના c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  જો (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      સંરચના c_declarator *declarator;
      સંરચના c_declspecs *quals_attrs = build_null_declspecs ();
      સંરચના c_પદાવલિ dimen;
      dimen.કિંમત = NULL_વૃક્ષ;
      dimen.original_code = ERROR_MARK;
      dimen.original_type = NULL_વૃક્ષ;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, ખોટું, ખોટું, સાચું,
			  ખોટું, ખોટું, ખોટું, ખોટું, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      જો (c_parser_next_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  જો (!quals_attrs->declspecs_seen_p)
	    c_parser_declspecs (parser, quals_attrs, ખોટું, ખોટું, સાચું,
				ખોટું, ખોટું, ખોટું, ખોટું, cla_prefer_id);
	}
      જો (!quals_attrs->declspecs_seen_p)
	quals_attrs = ખાલી;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      અચલ તાર્કિક static_seen = (static_loc != UNKNOWN_LOCATION);
      તાર્કિક star_seen = ખોટું;
      જો (c_parser_next_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
	{
	  star_seen = સાચું;
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	dimen = c_parser_પદાવલિ_no_commas (parser, ખાલી);

      જો (static_seen)
	{
	  જો (star_seen)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      star_seen = ખોટું;
	      dimen.કિંમત = error_mark_ગાંઠ;
	    }
	  નહીંતર જો (!dimen.કિંમત)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      જો (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      નહીંતર
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  પાછા ખાલી;
	}
      જો (dimen.કિંમત)
	dimen = convert_lvalue_to_rvalue (brace_loc, dimen, સાચું, સાચું);
      declarator = build_array_declarator (brace_loc, dimen.કિંમત, quals_attrs,
					   static_seen, star_seen);
      જો (declarator == ખાલી)
	પાછા ખાલી;
      જો (c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  વૃક્ષ std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  જો (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = set_array_declarator_inner (declarator, inner);
      પાછા c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  નહીંતર જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      વૃક્ષ attrs;
      સંરચના c_arg_info *args;
      c_parser_consume_token (parser);
      તાર્કિક have_gnu_attrs = c_parser_next_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      જો (args == ખાલી)
	પાછા ખાલી;
      નહીંતર
	{
	  જો (!(args->types
		&& args->types != error_mark_ગાંઠ
		&& વૃક્ષ_CODE (વૃક્ષ_કિંમત (args->types)) == IDENTIFIER_ગાંઠ)
	      && c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      વૃક્ષ std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      જો (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (args, inner);
	  પાછા c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  પાછા inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

સ્થિર સંરચના c_arg_info *
c_parser_parms_declarator (c_parser *parser, તાર્કિક id_list_ok, વૃક્ષ attrs,
			   તાર્કિક have_gnu_attrs)
{
  ધકેલો_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  જો (id_list_ok
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
      વૃક્ષ list = NULL_વૃક્ષ, *nextp = &list;
      જ્યારે (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  *nextp = build_વૃક્ષ_list (NULL_વૃક્ષ,
				    c_parser_peek_token (parser)->કિંમત);
	  nextp = & વૃક્ષ_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is_not (parser, CPP_COMMA))
	    તોડો;
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      તોડો;
	    }
	}
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  સંરચના c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  કાઢો_scope ();
	  પાછા ret;
	}
      નહીંતર
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  કાઢો_scope ();
	  પાછા ખાલી;
	}
    }
  નહીંતર
    {
      સંરચના c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, ખાલી, have_gnu_attrs);
      કાઢો_scope ();
      પાછા ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

સ્થિર સંરચના c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, વૃક્ષ attrs, વૃક્ષ પદાવલિ,
				તાર્કિક have_gnu_attrs)
{
  તાર્કિક bad_parm = ખોટું;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      સંરચના c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      પાછા ret;
    }
  જો (c_parser_next_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      સંરચના c_arg_info *ret = build_arg_info ();

      ret->types = NULL_વૃક્ષ;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_args_stdarg_p = સાચું;
	  c_parser_consume_token (parser);
	  પાછા ret;
	}
      નહીંતર
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  પાછા ખાલી;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  જ્યારે (સાચું)
    {
      /* Parse a parameter.  */
      સંરચના c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_વૃક્ષ;
      have_gnu_attrs = ખોટું;
      જો (parm == ખાલી)
	bad_parm = સાચું;
      નહીંતર
	ધકેલો_parm_decl (parm, &પદાવલિ);
      જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  વૃક્ષ new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  તાર્કિક new_have_gnu_attrs
	    = c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_attributes (parser);
	  પાછા c_parser_parms_list_declarator (parser, new_attrs, પદાવલિ,
						 new_have_gnu_attrs);
	}
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  જો (bad_parm)
	    પાછા ખાલી;
	  નહીંતર
	    પાછા get_parm_info (ખોટું, પદાવલિ);
	}
      જો (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, ખોટું))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	  પાછા ખાલી;
	}
      જો (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      જો (bad_parm)
		પાછા ખાલી;
	      નહીંતર
		પાછા get_parm_info (સાચું, પદાવલિ);
	    }
	  નહીંતર
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      પાછા ખાલી;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

સ્થિર સંરચના c_parm *
c_parser_parameter_declaration (c_parser *parser, વૃક્ષ attrs,
				તાર્કિક have_gnu_attrs)
{
  સંરચના c_declspecs *specs;
  સંરચના c_declarator *declarator;
  વૃક્ષ prefix_attrs;
  વૃક્ષ postfix_attrs = NULL_વૃક્ષ;
  તાર્કિક dummy = ખોટું;

  /* Accept #pragmas between parameter declarations.  */
  જ્યારે (c_parser_next_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, ખાલી, NULL_વૃક્ષ);

  જો (!c_parser_next_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      જો (parser->error)
	પાછા ખાલી;
      c_parser_set_source_position_from_token (token);
      જો (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_group d;
	  name_hint hint = lookup_name_fuzzy (token->કિંમત,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  જો (અચલ અક્ષર *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.add_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->કિંમત, suggestion);
	    }
	  નહીંતર
	    error_at (token->location, "unknown type name %qE", token->કિંમત);
	  parser->error = સાચું;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      નહીંતર
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_to_end_of_parameter (parser);
      પાછા ખાલી;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  જો (attrs)
    {
      declspecs_add_attrs (આગત_location, specs, attrs);
      attrs = NULL_વૃક્ષ;
    }
  c_parser_declspecs (parser, specs, સાચું, સાચું, સાચું, સાચું, ખોટું,
		      !have_gnu_attrs, સાચું, cla_nonabstract_decl);
  finish_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  જો (specs->typespec_kind == ctsk_tagdef)
    verify_counted_by_for_ટોચ_anonymous_type (specs->type);

  pending_xref_error ();
  prefix_attrs = specs->attrs;
  specs->attrs = NULL_વૃક્ષ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_PARM, &dummy);
  જો (declarator == ખાલી)
    {
      c_parser_skip_until_found (parser, CPP_COMMA, ખાલી);
      પાછા ખાલી;
    }
  જો (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
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
  જ્યારે (id_declarator && id_declarator->kind != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : start_loc);
  location_t param_loc = make_location (caret_loc, start_loc, end_loc);

  પાછા build_c_parm (specs, chainon (postfix_attrs, prefix_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

સ્થિર વૃક્ષ
c_parser_asm_string_literal (c_parser *parser)
{
  વૃક્ષ str;
  પૂર્ણાંક save_flag = warn_overlength_strings;
  warn_overlength_strings = 0;
  str = c_parser_string_literal (parser, ખોટું, ખોટું).કિંમત;
  warn_overlength_strings = save_flag;
  પાછા str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

સ્થિર વૃક્ષ
c_parser_simple_asm_પદાવલિ (c_parser *parser)
{
  વૃક્ષ str;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા NULL_વૃક્ષ;
  str = c_parser_asm_string_literal (parser);
  જો (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
      પાછા NULL_વૃક્ષ;
    }
  પાછા str;
}

સ્થિર વૃક્ષ
c_parser_gnu_attribute_any_word (c_parser *parser)
{
  વૃક્ષ attr_name = NULL_વૃક્ષ;

  જો (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      તાર્કિક ok;
      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_STATIC:
	સ્થિતિ RID_UNSIGNED:
	સ્થિતિ RID_LONG:
	સ્થિતિ RID_CONST:
	સ્થિતિ RID_EXTERN:
	સ્થિતિ RID_REGISTER:
	સ્થિતિ RID_TYPEDEF:
	સ્થિતિ RID_SHORT:
	સ્થિતિ RID_INLINE:
	સ્થિતિ RID_NORETURN:
	સ્થિતિ RID_VOLATILE:
	સ્થિતિ RID_SIGNED:
	સ્થિતિ RID_AUTO:
	સ્થિતિ RID_RESTRICT:
	સ્થિતિ RID_COMPLEX:
	સ્થિતિ RID_THREAD:
	સ્થિતિ RID_INT:
	સ્થિતિ RID_CHAR:
	સ્થિતિ RID_FLOAT:
	સ્થિતિ RID_DOUBLE:
	સ્થિતિ RID_VOID:
	સ્થિતિ RID_DFLOAT32:
	સ્થિતિ RID_DFLOAT64:
	સ્થિતિ RID_DFLOAT128:
	સ્થિતિ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	સ્થિતિ RID_BOOL:
	સ્થિતિ RID_BITINT:
	સ્થિતિ RID_FRACT:
	સ્થિતિ RID_ACCUM:
	સ્થિતિ RID_SAT:
	સ્થિતિ RID_TRANSACTION_ATOMIC:
	સ્થિતિ RID_TRANSACTION_CANCEL:
	સ્થિતિ RID_ATOMIC:
	સ્થિતિ RID_AUTO_TYPE:
	સ્થિતિ RID_CONSTEXPR:
	સ્થિતિ RID_INT_N_0:
	સ્થિતિ RID_INT_N_1:
	સ્થિતિ RID_INT_N_2:
	સ્થિતિ RID_INT_N_3:
	  ok = સાચું;
	  તોડો;
	મૂળભૂત:
	  ok = ખોટું;
	  તોડો;
	}
      જો (!ok)
	પાછા NULL_વૃક્ષ;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(પૂર્ણાંક) c_parser_peek_token (parser)->keyword];
    }
  નહીંતર જો (c_parser_next_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->કિંમત;

  પાછા attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

સ્થિર વૃક્ષ
c_parser_attribute_arguments (c_parser *parser, તાર્કિક takes_identifier,
			      તાર્કિક require_string, તાર્કિક assume_attr,
			      તાર્કિક allow_empty_args)
{
  vec<વૃક્ષ, va_gc> *પદાવલિ_list;
  વૃક્ષ attr_args;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  જો (c_parser_next_token_is (parser, CPP_NAME)
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
      વૃક્ષ arg1 = c_parser_peek_token (parser)->કિંમત;
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	attr_args = build_વૃક્ષ_list (NULL_વૃક્ષ, arg1);
      નહીંતર
	{
	  વૃક્ષ વૃક્ષ_list;
	  c_parser_consume_token (parser);
	  પદાવલિ_list = c_parser_પદાવલિ_list (parser, ખોટું, સાચું,
					  ખાલી, ખાલી, ખાલી, ખાલી);
	  વૃક્ષ_list = build_વૃક્ષ_list_vec (પદાવલિ_list);
	  attr_args = વૃક્ષ_cons (NULL_વૃક્ષ, arg1, વૃક્ષ_list);
	  release_વૃક્ષ_vector (પદાવલિ_list);
	}
    }
  નહીંતર
    {
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  જો (!allow_empty_args)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_args = NULL_વૃક્ષ;
	}
      નહીંતર જો (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  વૃક્ષ string = c_parser_string_literal (parser, ખોટું, સાચું).કિંમત;
	  attr_args = build_વૃક્ષ_list (NULL_વૃક્ષ, string);
	}
      નહીંતર જો (assume_attr)
	{
	  વૃક્ષ cond
	    = c_parser_conditional_expression (parser, ખાલી, NULL_વૃક્ષ).કિંમત;
	  જો (!c_parser_next_token_is (parser, CPP_COMMA))
	    attr_args = build_વૃક્ષ_list (NULL_વૃક્ષ, cond);
	  નહીંતર
	    {
	      વૃક્ષ વૃક્ષ_list;
	      c_parser_consume_token (parser);
	      પદાવલિ_list = c_parser_પદાવલિ_list (parser, ખોટું, સાચું,
					      ખાલી, ખાલી, ખાલી, ખાલી);
	      વૃક્ષ_list = build_વૃક્ષ_list_vec (પદાવલિ_list);
	      attr_args = વૃક્ષ_cons (NULL_વૃક્ષ, cond, વૃક્ષ_list);
	      release_વૃક્ષ_vector (પદાવલિ_list);
	    }
	}
      નહીંતર
	{
	  પદાવલિ_list = c_parser_પદાવલિ_list (parser, ખોટું, સાચું,
					  ખાલી, ખાલી, ખાલી, ખાલી);
	  attr_args = build_વૃક્ષ_list_vec (પદાવલિ_list);
	  release_વૃક્ષ_vector (પદાવલિ_list);
	}
    }
  પાછા attr_args;
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

સ્થિર વૃક્ષ
c_parser_gnu_attribute (c_parser *parser, વૃક્ષ attrs,
			તાર્કિક expect_comma = ખોટું, તાર્કિક empty_ok = સાચું)
{
  તાર્કિક comma_first = c_parser_next_token_is (parser, CPP_COMMA);
  જો (!comma_first
      && !c_parser_next_token_is (parser, CPP_NAME)
      && !c_parser_next_token_is (parser, CPP_KEYWORD))
    પાછા NULL_વૃક્ષ;

  જ્યારે (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      જો (!empty_ok)
	પાછા attrs;
    }

  વૃક્ષ attr_name = c_parser_gnu_attribute_any_word (parser);
  જો (attr_name == NULL_વૃક્ષ)
    પાછા NULL_વૃક્ષ;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  વૃક્ષ attr;
  જો (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      જો (expect_comma && !comma_first)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  પાછા error_mark_ગાંઠ;
	}
      attr = build_વૃક્ષ_list (attr_name, NULL_વૃક્ષ);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      પાછા attrs;
    }
  c_parser_consume_token (parser);

  વૃક્ષ attr_args
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    ખોટું,
				    is_attribute_p ("assume", attr_name),
				    સાચું);

  attr = build_વૃક્ષ_list (attr_name, attr_args);
  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  નહીંતર
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      પાછા error_mark_ગાંઠ;
    }

  જો (expect_comma && !comma_first)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      પાછા error_mark_ગાંઠ;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  પાછા attrs;
}

સ્થિર વૃક્ષ
c_parser_gnu_attributes (c_parser *parser)
{
  વૃક્ષ attrs = NULL_વૃક્ષ;
  જ્યારે (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      તાર્કિક save_translate_strings_p = parser->translate_strings_p;
      parser->translate_strings_p = ખોટું;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  પાછા attrs;
	}
      જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	  પાછા attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      માટે (તાર્કિક expect_comma = ખોટું; ; expect_comma = સાચું)
	{
	  /* Parse a single attribute.  */
	  વૃક્ષ attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  જો (attr == error_mark_ગાંઠ)
	    પાછા attrs;
	  જો (!attr)
	    તોડો;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      નહીંતર
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  પાછા attrs;
	}
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      નહીંતર
	{
	  parser->translate_strings_p = save_translate_strings_p;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  પાછા attrs;
	}
      parser->translate_strings_p = save_translate_strings_p;
    }

  પાછા attrs;
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

સ્થિર શૂન્ય
c_parser_balanced_token_sequence (c_parser *parser)
{
  જ્યારે (સાચું)
    {
      c_token *token = c_parser_peek_token (parser);
      પસંદગી (token->type)
	{
	સ્થિતિ CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    braces.require_close (parser);
	    તોડો;
	  }

	સ્થિતિ CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_balanced_token_sequence (parser);
	    parens.require_close (parser);
	    તોડો;
	  }

	સ્થિતિ CPP_OPEN_SQUARE:
	  c_parser_consume_token (parser);
	  c_parser_balanced_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
	  તોડો;

	સ્થિતિ CPP_CLOSE_BRACE:
	સ્થિતિ CPP_CLOSE_PAREN:
	સ્થિતિ CPP_CLOSE_SQUARE:
	સ્થિતિ CPP_EOF:
	  પાછા;

	સ્થિતિ CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  તોડો;

	મૂળભૂત:
	  c_parser_consume_token (parser);
	  તોડો;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

સ્થિર શૂન્ય
c_parser_omp_directive_args (c_parser *parser, વૃક્ષ attribute, તાર્કિક decl_p)
{
  unsigned પૂર્ણાંક n = 1;
  c_token *first = c_parser_peek_token (parser);
  જો (!c_parser_check_balanced_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_balanced_token_sequence (parser);
      વૃક્ષ_કિંમત (attribute) = NULL_વૃક્ષ;
      પાછા;
    }
  જો (n == 1)
    {
      error_at (first->location, "expected OpenMP directive name");
      વૃક્ષ_કિંમત (attribute) = NULL_વૃક્ષ;
      પાછા;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  માટે (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->quick_ધકેલો (*tok);
      c_parser_consume_token (parser);
    }
  વૃક્ષ arg = make_ગાંઠ (C_TOKEN_VEC);
  C_TOKEN_VEC_TOKENS (arg) = v;
  જો (decl_p)
    વૃક્ષ_PUBLIC (arg) = 1;
  વૃક્ષ_કિંમત (attribute) = વૃક્ષ_cons (NULL_વૃક્ષ, arg, વૃક્ષ_કિંમત (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

સ્થિર શૂન્ય
c_parser_omp_sequence_args (c_parser *parser, વૃક્ષ attribute)
{
  કરો
    {
      c_token *token = c_parser_peek_token (parser);
      જો (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_POINTER (token->કિંમત), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      તાર્કિક directive = ખોટું;
      અચલ અક્ષર *p;
      જો (token->type != CPP_NAME)
	p = "";
      નહીંતર
	p = IDENTIFIER_POINTER (token->કિંમત);
      જો (strcmp (p, "directive") == 0)
	directive = સાચું;
      નહીંતર જો (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  unsigned nesting_depth = 0;

	  જ્યારે (સાચું)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      જો ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_depth)
		તોડો;
	      /* If we've run out of tokens, stop.  */
	      જો (token->type == CPP_EOF)
		તોડો;
	      જો (token->type == CPP_PRAGMA_EOL && parser->in_pragma)
		તોડો;
	      જો (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_SQUARE)
		++nesting_depth;
	      નહીંતર જો (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_SQUARE)
		{
		  જો (nesting_depth-- == 0)
		    તોડો;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  જો (c_parser_next_token_is_not (parser, CPP_COMMA))
	    તોડો;
	  c_parser_consume_token (parser);
	  ચાલુ;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      જો (parens.require_open (parser))
	{
	  જો (directive)
	    c_parser_omp_directive_args (parser, attribute, ખોટું);
	  નહીંતર
	    c_parser_omp_sequence_args (parser, attribute);
	  parens.skip_until_found_close (parser);
	  જો (c_parser_next_token_is_not (parser, CPP_COMMA))
	    તોડો;
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (c_parser_next_token_is_not (parser, CPP_COMMA))
	તોડો;
      નહીંતર
	c_parser_consume_token (parser);
    }
  જ્યારે (1);
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

સ્થિર વૃક્ષ
c_parser_std_attribute (c_parser *parser, તાર્કિક for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  વૃક્ષ ns, name, attribute;

  /* Parse the attribute-token.  */
  જો (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      પાછા error_mark_ગાંઠ;
    }
  name = canonicalize_attr_name (token->કિંમત);
  c_parser_consume_token (parser);
  જો (c_parser_next_token_is (parser, CPP_SCOPE)
      || (c_parser_next_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      જો (c_parser_next_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      જો (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  પાછા error_mark_ગાંઠ;
	}
      name = canonicalize_attr_name (token->કિંમત);
      c_parser_consume_token (parser);
    }
  નહીંતર
    ns = NULL_વૃક્ષ;
  attribute = build_વૃક્ષ_list (build_વૃક્ષ_list (ns, name), NULL_વૃક્ષ);

  /* Parse the arguments, if any.  */
  અચલ attribute_spec *as = lookup_attribute_spec (વૃક્ષ_PURPOSE (attribute));
  જો (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      જો ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  પાછા error_mark_ગાંઠ;
	}
      જાઓ out;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    જો ((as && as->max_length == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_found_close (parser);
	પાછા error_mark_ગાંઠ;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    જો (as && !attribute_ignored_p (as))
      {
	તાર્કિક takes_identifier
	  = (ns != NULL_વૃક્ષ
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	તાર્કિક require_string
	  = (ns == NULL_વૃક્ષ
	     && (strcmp (IDENTIFIER_POINTER (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_POINTER (name), "nodiscard") == 0));
	તાર્કિક assume_attr
	  = (ns != NULL_વૃક્ષ
	     && strcmp (IDENTIFIER_POINTER (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_POINTER (name), "assume") == 0);
	વૃક્ષ_કિંમત (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, ખોટું);
      }
    નહીંતર
      {
	જો ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    જો (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_args (parser, attribute, ખોટું);
		parens.skip_until_found_close (parser);
		પાછા attribute;
	      }
	    નહીંતર જો (is_attribute_p ("decl", name))
	      {
		વૃક્ષ_કિંમત (વૃક્ષ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_args (parser, attribute, સાચું);
		parens.skip_until_found_close (parser);
		પાછા attribute;
	      }
	    નહીંતર જો (is_attribute_p ("sequence", name))
	      {
		વૃક્ષ_કિંમત (વૃક્ષ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_args (parser, attribute);
		parens.skip_until_found_close (parser);
		વૃક્ષ_કિંમત (attribute) = nreverse (વૃક્ષ_કિંમત (attribute));
		પાછા attribute;
	      }
	  }
	c_parser_balanced_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 out:
  જો (ns == NULL_વૃક્ષ && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (આગત_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      પાછા error_mark_ગાંઠ;
    }
  પાછા attribute;
}

સ્થિર વૃક્ષ
c_parser_std_attribute_list (c_parser *parser, તાર્કિક for_tm)
{
  વૃક્ષ attributes = NULL_વૃક્ષ;
  જ્યારે (સાચું)
    {
      c_token *token = c_parser_peek_token (parser);
      જો (token->type == CPP_CLOSE_SQUARE)
	તોડો;
      જો (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ચાલુ;
	}
      વૃક્ષ attribute = c_parser_std_attribute (parser, for_tm);
      જો (attribute != error_mark_ગાંઠ)
	{
	  વૃક્ષ_CHAIN (attribute) = attributes;
	  attributes = attribute;
	}
      જો (c_parser_next_token_is_not (parser, CPP_COMMA))
	તોડો;
    }
  પાછા attributes;
}

સ્થિર વૃક્ષ
c_parser_std_attribute_specifier (c_parser *parser, તાર્કિક for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  જો (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    પાછા NULL_વૃક્ષ;
  જો (!c_parser_require (parser, CPP_OPEN_SQUARE, "expected %<[%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
      પાછા NULL_વૃક્ષ;
    }
  વૃક્ષ attributes;
  જો (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
    {
      auto ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      attributes = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  નહીંતર
    {
      જો (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      attributes = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, "expected %<]%>");
  પાછા nreverse (attributes);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

સ્થિર તાર્કિક
c_parser_check_balanced_raw_token_sequence (c_parser *parser, unsigned પૂર્ણાંક *n)
{
  જ્યારે (સાચું)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      પસંદગી (token->type)
	{
	સ્થિતિ CPP_OPEN_BRACE:
	  {
	    ++*n;
	    જો (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		જો (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		નહીંતર
		  પાછા ખોટું;
	      }
	    નહીંતર
	      પાછા ખોટું;
	    તોડો;
	  }

	સ્થિતિ CPP_OPEN_PAREN:
	  {
	    ++*n;
	    જો (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		જો (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		નહીંતર
		  પાછા ખોટું;
	      }
	    નહીંતર
	      પાછા ખોટું;
	    તોડો;
	  }

	સ્થિતિ CPP_OPEN_SQUARE:
	  {
	    ++*n;
	    જો (c_parser_check_balanced_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		જો (token->type == CPP_CLOSE_SQUARE)
		  ++*n;
		નહીંતર
		  પાછા ખોટું;
	      }
	    નહીંતર
	      પાછા ખોટું;
	    તોડો;
	  }

	સ્થિતિ CPP_CLOSE_BRACE:
	સ્થિતિ CPP_CLOSE_PAREN:
	સ્થિતિ CPP_CLOSE_SQUARE:
	સ્થિતિ CPP_EOF:
	  પાછા સાચું;

	મૂળભૂત:
	  ++*n;
	  તોડો;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

સ્થિર તાર્કિક
c_parser_nth_token_starts_std_attributes (c_parser *parser, unsigned પૂર્ણાંક n)
{
  જો (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_SQUARE
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_SQUARE))
    પાછા ખોટું;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  જો (!c_dialect_objc ())
    પાછા સાચું;
  n += 2;
  જો (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    પાછા ખોટું;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  જો (token->type != CPP_CLOSE_SQUARE)
    પાછા ખોટું;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  પાછા token->type == CPP_CLOSE_SQUARE;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

સ્થિર size_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, size_t n)
{
  size_t orig_n = n;
  જ્યારે (સાચું)
    {
      જો (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_SQUARE
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_SQUARE))
	{
	  unsigned પૂર્ણાંક m = n + 2;
	  જો (!c_parser_check_balanced_raw_token_sequence (parser, &m))
	    પાછા orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  જો (token->type != CPP_CLOSE_SQUARE)
	    પાછા orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  જો (token->type != CPP_CLOSE_SQUARE)
	    પાછા orig_n;
	  n = m + 2;
	}
      નહીંતર
	તોડો;
    }
  પાછા n;
}

સ્થિર વૃક્ષ
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  વૃક્ષ attributes = NULL_વૃક્ષ;
  કરો
    {
      વૃક્ષ attrs = c_parser_std_attribute_specifier (parser, ખોટું);
      attributes = chainon (attributes, attrs);
    }
  જ્યારે (c_parser_nth_token_starts_std_attributes (parser, 1));
  પાછા attributes;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

સંરચના c_type_name *
c_parser_type_name (c_parser *parser, તાર્કિક alignas_ok)
{
  સંરચના c_declspecs *specs = build_null_declspecs ();
  સંરચના c_declarator *declarator;
  સંરચના c_type_name *ret;
  તાર્કિક dummy = ખોટું;
  c_parser_declspecs (parser, specs, ખોટું, સાચું, સાચું, alignas_ok, ખોટું,
		      ખોટું, સાચું, cla_prefer_type);
  જો (!specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      પાછા ખાલી;
    }
  જો (specs->type != error_mark_ગાંઠ)
    {
      pending_xref_error ();
      finish_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      જો (specs->typespec_kind == ctsk_tagdef)
	verify_counted_by_for_ટોચ_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  જો (declarator == ખાલી)
    પાછા ખાલી;
  ret = XOBNEW (&parser_obstack, સંરચના c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  પાછા ret;
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

સ્થિર સંરચના c_પદાવલિ
c_parser_initializer (c_parser *parser, વૃક્ષ decl)
{
  જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    પાછા c_parser_braced_init (parser, NULL_વૃક્ષ, ખોટું, ખાલી,
				 decl != error_mark_ગાંઠ
				 && C_DECL_VARIABLE_SIZE (decl));
  નહીંતર
    {
      સંરચના c_પદાવલિ ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      જો (decl != error_mark_ગાંઠ && C_DECL_VARIABLE_SIZE (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.set_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      જો (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !વૃક્ષ_STATIC (decl)
	  && ret.કિંમત == decl
	  && !warning_enabled_at (DECL_SOURCE_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      જો (વૃક્ષ_CODE (ret.કિંમત) != STRING_CST
	  && (વૃક્ષ_CODE (ret.કિંમત) != COMPOUND_LITERAL_પદાવલિ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_પદાવલિ_DECL
					    (ret.કિંમત))))
	ret = convert_lvalue_to_rvalue (loc, ret, સાચું, સાચું, સાચું);
      પાછા ret;
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

સ્થિર સંરચના c_પદાવલિ
c_parser_braced_init (c_parser *parser, વૃક્ષ type, તાર્કિક nested_p,
		      સંરચના obstack *outer_obstack, તાર્કિક varsize_p)
{
  સંરચના c_પદાવલિ ret;
  સંરચના obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  તાર્કિક save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = ખોટું;
  તાર્કિક zero_init_padding_bits = ખોટું;
  matching_braces braces;
  braces.consume_open (parser);
  જો (nested_p)
    {
      finish_implicit_inits (brace_loc, outer_obstack);
      ધકેલો_init_level (brace_loc, 0, &braced_init_obstack);
    }
  નહીંતર
    really_start_incremental_init (type);
  જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      જો (flag_isoc23)
	zero_init_padding_bits = સાચું;
    }
  નહીંતર
    {
      જો (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      જ્યારે (સાચું)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  જો (parser->error)
	    તોડો;
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      last_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      જ્યારે (c_parser_next_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_પદાવલિ embed_val;
		  embed_val.કિંમત = embed->કિંમત;
		  embed_val.original_code = RAW_DATA_CST;
		  embed_val.original_type = integer_type_ગાંઠ;
		  set_c_પદાવલિ_source_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, ખોટું,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_next_token_is (parser,
							       CPP_COMMA));
		  last_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  નહીંતર
	    તોડો;
	  જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    તોડો;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *next_tok = c_parser_peek_token (parser);
  જો (next_tok->type != CPP_CLOSE_BRACE)
    {
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ખાલી;
      braces.skip_until_found_close (parser);
      કાઢો_init_level (brace_loc, 0, &braced_init_obstack, last_init_list_comma);
      obstack_free (&braced_init_obstack, ખાલી);
      પાછા ret;
    }
  location_t close_loc = next_tok->location;
  c_parser_consume_token (parser);
  ret = કાઢો_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  જો (zero_init_padding_bits
      && ret.કિંમત
      && વૃક્ષ_CODE (ret.કિંમત) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_BITS (ret.કિંમત) = 1;
  obstack_free (&braced_init_obstack, ખાલી);
  set_c_પદાવલિ_source_range (&ret, brace_loc, close_loc);
  પાછા ret;
}

/* Parse a nested initializer, including designators.  */

સ્થિર શૂન્ય
c_parser_initelt (c_parser *parser, સંરચના obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  જો (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      set_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->કિંમત,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  નહીંતર
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      પૂર્ણાંક des_seen = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      જ્યારે (c_parser_next_token_is (parser, CPP_OPEN_SQUARE)
	     || c_parser_next_token_is (parser, CPP_DOT))
	{
	  પૂર્ણાંક des_prev = des_seen;
	  જો (!des_seen)
	    des_loc = c_parser_peek_token (parser)->location;
	  જો (des_seen < 2)
	    des_seen++;
	  જો (c_parser_next_token_is (parser, CPP_DOT))
	    {
	      des_seen = 2;
	      c_parser_consume_token (parser);
	      જો (c_parser_next_token_is (parser, CPP_NAME))
		{
		  set_init_label (des_loc, c_parser_peek_token (parser)->કિંમત,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      નહીંતર
		{
		  સંરચના c_પદાવલિ init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = ખાલી;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_found (parser, CPP_COMMA, ખાલી);
		  process_init_element (આગત_location, init, ખોટું,
					braced_init_obstack);
		  પાછા;
		}
	    }
	  નહીંતર
	    {
	      સંરચના c_પદાવલિ first_પદાવલિ;
	      વૃક્ષ first, second;
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
	      જો (des_prev == 1 && c_dialect_objc ())
		{
		  des_seen = des_prev;
		  તોડો;
		}
	      જો (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  વૃક્ષ rec, args;
		  સંરચના c_પદાવલિ mexpr;
		  c_parser_consume_token (parser);
		  જો (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_kind
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_kind
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      જાઓ parse_message_args;
		    }
		  array_index_loc = c_parser_peek_token (parser)->location;
		  first_પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
		  mark_exp_read (first_પદાવલિ.કિંમત);
		  જો (c_parser_next_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    જાઓ array_desig_after_first;
		  first = first_પદાવલિ.કિંમત;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = first;
		  જ્યારે (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      સંરચના c_પદાવલિ next;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      next = c_parser_પદાવલિ_no_commas (parser, ખાલી);
		      next = convert_lvalue_to_rvalue (exp_loc, next,
						       સાચું, સાચું);
		      rec = build_compound_પદાવલિ (comma_loc, rec, next.કિંમત);
		    }
		parse_message_args:
		  /* Now parse the objc-message-args.  */
		  args = c_parser_objc_message_args (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					     "expected %<]%>");
		  mexpr.કિંમત
		    = objc_build_message_પદાવલિ (rec, args);
		  mexpr.original_code = ERROR_MARK;
		  mexpr.original_type = ખાલી;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  પાછા;
		}
	      c_parser_consume_token (parser);
	      array_index_loc = c_parser_peek_token (parser)->location;
	      first_પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	      mark_exp_read (first_પદાવલિ.કિંમત);
	    array_desig_after_first:
	      first_પદાવલિ = convert_lvalue_to_rvalue (array_index_loc,
						     first_પદાવલિ,
						     સાચું, સાચું);
	      first = first_પદાવલિ.કિંમત;
	      જો (c_parser_next_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  second = convert_lvalue_to_rvalue (ellipsis_loc,
						     (c_parser_પદાવલિ_no_commas
						      (parser, ખાલી)),
						     સાચું, સાચું).કિંમત;
		  mark_exp_read (second);
		}
	      નહીંતર
		second = NULL_વૃક્ષ;
	      જો (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		{
		  c_parser_consume_token (parser);
		  set_init_index (array_index_loc, first, second,
				  braced_init_obstack);
		  જો (second)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      નહીંતર
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
					   "expected %<]%>");
	    }
	}
      જો (des_seen >= 1)
	{
	  જો (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  નહીંતર
	    {
	      જો (des_seen == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      નહીંતર
		{
		  સંરચના c_પદાવલિ init;
		  init.set_error ();
		  init.original_code = ERROR_MARK;
		  init.original_type = ખાલી;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_found (parser, CPP_COMMA, ખાલી);
		  process_init_element (આગત_location, init, ખોટું,
					braced_init_obstack);
		  પાછા;
		}
	    }
	}
    }
  c_parser_initval (parser, ખાલી, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

સ્થિર શૂન્ય
c_parser_initval (c_parser *parser, સંરચના c_પદાવલિ *after,
		  સંરચના obstack * braced_init_obstack)
{
  સંરચના c_પદાવલિ init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_વૃક્ષ, સાચું,
				 braced_init_obstack, ખોટું);
  નહીંતર
    {
      init = c_parser_પદાવલિ_no_commas (parser, after);
      જો (init.કિંમત != NULL_વૃક્ષ
	  && વૃક્ષ_CODE (init.કિંમત) != STRING_CST
	  && (વૃક્ષ_CODE (init.કિંમત) != COMPOUND_LITERAL_પદાવલિ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_પદાવલિ_DECL
					    (init.કિંમત))))
	init = convert_lvalue_to_rvalue (loc, init, સાચું, સાચું, સાચું);
    }
  વૃક્ષ val = init.કિંમત;
  process_init_element (loc, init, ખોટું, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  સ્થિર unsigned vals_to_ignore;
  જો (vals_to_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_to_ignore;
  નહીંતર જો (val
	   && વૃક્ષ_CODE (val) == INTEGER_CST
	   && વૃક્ષ_TYPE (val) == integer_type_ગાંઠ
	   && c_parser_next_token_is (parser, CPP_COMMA))
    જો (unsigned પૂર્ણાંક len = c_maybe_optimize_large_byte_initializer ())
      {
	અક્ષર buf1[64];
	unsigned પૂર્ણાંક i;
	gcc_checking_assert (len >= 64);
	location_t last_loc = UNKNOWN_LOCATION;
	માટે (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    જો (tok->type != CPP_COMMA)
	      તોડો;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    જો (tok->type != CPP_સંખ્યા
		|| વૃક્ષ_CODE (tok->કિંમત) != INTEGER_CST
		|| વૃક્ષ_TYPE (tok->કિંમત) != integer_type_ગાંઠ
		|| wi::neg_p (wi::to_wide (tok->કિંમત))
		|| wi::to_widest (tok->કિંમત) > UCHAR_MAX)
	      તોડો;
	    buf1[i] = (અક્ષર) વૃક્ષ_to_uhwi (tok->કિંમત);
	    જો (i == 0)
	      loc = tok->location;
	    last_loc = tok->location;
	  }
	જો (i < 64)
	  {
	    vals_to_ignore = i;
	    પાછા;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	જો (tok->type == CPP_CLOSE_BRACE && len != INT_MAX)
	  len = i;
	નહીંતર જો (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_સંખ્યા))
	  {
	    vals_to_ignore = i;
	    પાછા;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	unsigned પૂર્ણાંક max_len = 131072 - offsetof (સંરચના વૃક્ષ_string, str) - 1;
	unsigned પૂર્ણાંક orig_len = len;
	unsigned પૂર્ણાંક off = 0, last = 0;
	જો (!wi::neg_p (wi::to_wide (val)) && wi::to_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	અક્ષર *buf2 = XNEWVEC (અક્ષર, len + off);
	જો (off)
	  buf2[0] = (અક્ષર) વૃક્ષ_to_uhwi (val);
	memcpy (buf2 + off, buf1, i);
	માટે (unsigned પૂર્ણાંક j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	માટે (; i < len; ++i)
	  {
	    જો (!c_parser_next_token_is (parser, CPP_COMMA))
	      તોડો;
	    tok = c_parser_peek_2nd_token (parser);
	    જો (tok->type != CPP_સંખ્યા
		|| વૃક્ષ_CODE (tok->કિંમત) != INTEGER_CST
		|| વૃક્ષ_TYPE (tok->કિંમત) != integer_type_ગાંઠ
		|| wi::neg_p (wi::to_wide (tok->કિંમત))
		|| wi::to_widest (tok->કિંમત) > UCHAR_MAX)
	      તોડો;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    જો (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      તોડો;
	    buf2[i + off] = (અક્ષર) વૃક્ષ_to_uhwi (tok->કિંમત);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    જો (orig_len == INT_MAX
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_સંખ્યા)))
	      {
		last = 1;
		તોડો;
	      }
	    last_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_ગાંઠ (RAW_DATA_CST);
	વૃક્ષ_TYPE (val) = integer_type_ગાંઠ;
	RAW_DATA_LENGTH (val) = i;
	વૃક્ષ owner = build_string (i + off + last, buf2);
	XDELETEVEC (buf2);
	વૃક્ષ_TYPE (owner) = build_array_type_nelts (unsigned_char_type_ગાંઠ,
						    i + off + last);
	RAW_DATA_OWNER (val) = owner;
	RAW_DATA_POINTER (val) = વૃક્ષ_STRING_POINTER (owner) + off;
	init.કિંમત = val;
	set_c_પદાવલિ_source_range (&init, loc, last_loc);
	init.original_code = RAW_DATA_CST;
	init.original_type = integer_type_ગાંઠ;
	init.m_decimal = 0;
	process_init_element (loc, init, ખોટું, braced_init_obstack);
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

સ્થિર વૃક્ષ
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  વૃક્ષ stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  જો (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (સાચું);
      c_end_compound_stmt (brace_loc, stmt, સાચું);
      પાછા error_mark_ગાંઠ;
    }
  stmt = c_begin_compound_stmt (સાચું);
  location_t end_loc = c_parser_compound_statement_nostart (parser);
  જો (endlocp)
    *endlocp = end_loc;

  પાછા c_end_compound_stmt (brace_loc, stmt, સાચું);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

સ્થિર શૂન્ય
check_omp_intervening_code (c_parser *parser)
{
  સંરચના omp_for_parse_data *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  જો (!omp_for_parse_state->in_intervening_code)
    પાછા;
  omp_for_parse_state->saw_intervening_code = સાચું;

  /* Only diagnose errors related to perfect nesting once.  */
  જો (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      જો (omp_for_parse_state->code == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = સાચું;
	}
      નહીંતર જો (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = સાચું;
	}
      નહીંતર જો (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = સાચું;
	}
      નહીંતર જો (omp_for_parse_state->code == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = સાચું;
	}
      જો (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = સાચું;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
સ્થિર શૂન્ય
add_structured_block_stmt (વૃક્ષ sl)
{
  જો (વૃક્ષ_CODE (sl) != STATEMENT_LIST
      || !tsi_end_p (tsi_start (sl)))
    add_stmt (build1 (OMP_STRUCTURED_BLOCK, void_type_ગાંઠ, sl));
}

સંરચના c_omp_attribute_data
{
  vec<c_token, va_gc> *tokens;
  અચલ c_omp_directive *dir;
  c_omp_directive_kind kind;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

સ્થિર તાર્કિક
c_parser_handle_statement_omp_attributes (c_parser *parser, વૃક્ષ &attrs,
					  તાર્કિક *have_std_attrs)
{
  જો (!flag_openmp && !flag_openmp_simd)
    પાછા ખોટું;

  auto_vec<c_omp_attribute_data, 16> vd;
  પૂર્ણાંક cnt = 0;
  પૂર્ણાંક tokens = 0;
  તાર્કિક bad = ખોટું;
  માટે (વૃક્ષ *pa = &attrs; *pa; )
    જો (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	માટે (વૃક્ષ a = વૃક્ષ_કિંમત (*pa); a; a = વૃક્ષ_CHAIN (a))
	  {
	    વૃક્ષ d = વૃક્ષ_કિંમત (a);
	    gcc_assert (વૃક્ષ_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    જો (parser->omp_attrs_forbidden_p)
	      {
		error_at (first->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = ખોટું;
		bad = સાચું;
	      }
	    નહીંતર જો (વૃક્ષ_PUBLIC (d))
	      {
		error_at (first->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = સાચું;
	      }
	    અચલ અક્ષર *directive[3] = {};
	    માટે (પૂર્ણાંક i = 0; i < 3; i++)
	      {
		વૃક્ષ id = NULL_વૃક્ષ;
		જો (first + i == last)
		  તોડો;
		જો (first[i].type == CPP_NAME)
		  id = first[i].કિંમત;
		નહીંતર જો (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(પૂર્ણાંક) first[i].keyword];
		નહીંતર
		  તોડો;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    અચલ c_omp_directive *dir = ખાલી;
	    જો (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    જો (dir == ખાલી)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  વૃક્ષ_PUBLIC (d) ? "omp::decl" : "omp::directive");
		ચાલુ;
	      }
	    c_omp_directive_kind kind = dir->kind;
	    જો (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		જો (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
		નહીંતર જો (first + 2 < last
			 && first[1].type == CPP_COMMA
			 && first[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_POINTER (first[2].કિંમત),
				     "depend") == 0
			     || strcmp (IDENTIFIER_POINTER (first[2].કિંમત),
					"doacross") == 0))
		  kind = C_OMP_DIR_STANDALONE;
	      }
	    નહીંતર જો (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		પૂર્ણાંક paren_depth = 0;
		માટે (પૂર્ણાંક i = 1; first + i < last; i++)
		  જો (first[i].type == CPP_OPEN_PAREN)
		    paren_depth++;
		  નહીંતર જો (first[i].type == CPP_CLOSE_PAREN)
		    paren_depth--;
		  નહીંતર જો (paren_depth == 0
			   && first + i + 2 < last
			   && first[i].type == CPP_NAME
			   && first[i + 1].type == CPP_OPEN_PAREN
			   && first[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_POINTER (first[i].કિંમત),
				       "at")
			   && !strcmp (IDENTIFIER_POINTER (first[i
								 + 2].કિંમત),
				       "execution"))
		    {
		      kind = C_OMP_DIR_STANDALONE;
		      તોડો;
		    }
	      }
	    c_omp_attribute_data v = { toks, dir, kind };
	    vd.safe_ધકેલો (v);
	    જો (flag_openmp || dir->simd)
	      tokens += (last - first) + 1;
	  }
	c_omp_attribute_data v = {};
	vd.safe_ધકેલો (v);
	*pa = વૃક્ષ_CHAIN (*pa);
      }
    નહીંતર
      pa = &વૃક્ષ_CHAIN (*pa);

  જો (bad)
    {
    fail:
      જો (have_std_attrs && attrs == ખાલી)
	*have_std_attrs = ખોટું;
      પાછા ખોટું;
    }

  unsigned પૂર્ણાંક i;
  c_omp_attribute_data *v;
  c_omp_attribute_data *construct_seen = nullptr;
  c_omp_attribute_data *standalone_seen = nullptr;
  c_omp_attribute_data *prev_standalone_seen = nullptr;
  FOR_EACH_VEC_ELT (vd, i, v)
    જો (v->tokens)
      {
	જો (v->kind == C_OMP_DIR_CONSTRUCT && !construct_seen)
	  construct_seen = v;
	નહીંતર જો (v->kind == C_OMP_DIR_STANDALONE && !standalone_seen)
	  standalone_seen = v;
      }
    નહીંતર
      {
	જો (standalone_seen && !prev_standalone_seen)
	  {
	    prev_standalone_seen = standalone_seen;
	    standalone_seen = nullptr;
	  }
      }

  જો (cnt > 1 && construct_seen)
    {
      error_at ((*construct_seen->tokens)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      જાઓ fail;
    }
  જો (cnt > 1 && standalone_seen && prev_standalone_seen)
    {
      error_at ((*standalone_seen->tokens)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      જાઓ fail;
    }

  જો (prev_standalone_seen)
    standalone_seen = prev_standalone_seen;
  જો (standalone_seen
      && !c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_seen->tokens->address ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      જાઓ fail;
    }
  જો (cnt && c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      ગણના pragma_kind kind = token->pragma_kind;
      જો (kind >= PRAGMA_OMP__START_ && kind <= PRAGMA_OMP__LAST_)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  જાઓ fail;
	}
    }

  જો (!tokens)
    પાછા ખોટું;

  unsigned પૂર્ણાંક tokens_avail = parser->tokens_avail;

  tokens++;
  vec<c_token, va_gc> *toks = ખાલી;
  vec_safe_reserve (toks, tokens, સાચું);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      જો (!v->tokens)
	ચાલુ;
      જો (!flag_openmp && !v->dir->simd)
	ચાલુ;
      c_token *first = v->tokens->address ();
      c_token *last = first + v->tokens->length ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_kind = pragma_kind (v->dir->id);
      tok.location = first->location;
      toks->quick_ધકેલો (tok);
      જ્યારે (++first < last)
	toks->quick_ધકેલો (*first);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = last[-1].location;
      toks->quick_ધકેલો (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->last ().location;
  toks->quick_ધકેલો (tok);

  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = tokens;
  પાછા સાચું;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

સ્થિર શૂન્ય
c_parser_handle_directive_omp_attributes (વૃક્ષ &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  જો (!flag_openmp && !flag_openmp_simd)
    પાછા;

  માટે (વૃક્ષ *pa = &attrs; *pa; )
    જો (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	પૂર્ણાંક cnt = 0;
	માટે (વૃક્ષ *pa2 = &વૃક્ષ_કિંમત (*pa); *pa2; )
	  {
	    વૃક્ષ a = *pa2;
	    વૃક્ષ d = વૃક્ષ_કિંમત (a);
	    gcc_assert (વૃક્ષ_CODE (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
	    c_token *first = toks->address ();
	    c_token *last = first + toks->length ();
	    અચલ અક્ષર *directive[3] = {};
	    માટે (પૂર્ણાંક i = 0; i < 3; i++)
	      {
		વૃક્ષ id = NULL_વૃક્ષ;
		જો (first + i == last)
		  તોડો;
		જો (first[i].type == CPP_NAME)
		  id = first[i].કિંમત;
		નહીંતર જો (first[i].type == CPP_KEYWORD)
		  id = ridpointers[(પૂર્ણાંક) first[i].keyword];
		નહીંતર
		  તોડો;
		directive[i] = IDENTIFIER_POINTER (id);
	      }
	    અચલ c_omp_directive *dir = ખાલી;
	    જો (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    જો (dir == ખાલી)
	      {
		error_at (first->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  વૃક્ષ_PUBLIC (d) ? "omp::decl" : "omp::directive");
		*pa2 = વૃક્ષ_CHAIN (a);
	      }
	    નહીંતર જો (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		જો (pragma_clauses)
		  {
		    error_at (first->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    માટે (pa = &attrs; *pa; )
		      જો (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = વૃક્ષ_CHAIN (*pa);
		      નહીંતર
			pa = &વૃક્ષ_CHAIN (*pa);
		    પાછા;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->length ()
				       + toks->length () + 2);
		માટે (++first; first < last; ++first)
		  attr_clauses->quick_ધકેલો (*first);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = last[-1].location;
		attr_clauses->quick_ધકેલો (tok);
		*pa2 = વૃક્ષ_CHAIN (a);
	      }
	    નહીંતર
	      pa2 = &વૃક્ષ_CHAIN (a);
	  }
	જો (cnt && વૃક્ષ_કિંમત (*pa) == NULL_વૃક્ષ)
	  *pa = વૃક્ષ_CHAIN (*pa);
	નહીંતર
	  pa = &વૃક્ષ_CHAIN (*pa);
      }
    નહીંતર
      pa = &વૃક્ષ_CHAIN (*pa);
  જો (attr_clauses->length ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->last ().location;
      attr_clauses->quick_ધકેલો (tok);
      attr_clauses->quick_ધકેલો (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

સ્થિર વૃક્ષ
c_parser_handle_musttail (c_parser *parser, વૃક્ષ std_attrs, attr_state &attr)
{
  જો (c_parser_next_token_is_keyword (parser, RID_RETURN))
    {
      જો (વૃક્ષ a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  માટે (; a; a = lookup_attribute ("gnu", "musttail", વૃક્ષ_CHAIN (a)))
	    જો (વૃક્ષ_કિંમત (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = સાચું;
	}
      જો (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = સાચું;
	}
    }
  પાછા std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

સ્થિર વૃક્ષ
get_before_labels ()
{
  જો (!building_stmt_list_p ())
    પાછા NULL_વૃક્ષ;
  વૃક્ષ_stmt_iterator tsi = tsi_last (cur_stmt_list);
  જો (tsi_end_p (tsi))
    પાછા NULL_વૃક્ષ;
  પાછા tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

સ્થિર location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  તાર્કિક last_stmt = ખોટું;
  તાર્કિક last_label = ખોટું;
  તાર્કિક save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  સંરચના omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  તાર્કિક in_omp_loop_block
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : ખોટું;
  વૃક્ષ sl = NULL_વૃક્ષ;
  attr_state astate = {};

  જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      add_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      પાછા endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  જો (in_omp_loop_block)
    sl = ધકેલો_stmt_list ();

  mark_valid_location_for_stdc_pragma (સાચું);
  જો (c_parser_next_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (ખોટું);
      જો (in_omp_loop_block)
	check_omp_intervening_code (parser);
      જ્યારે (c_parser_next_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  જ્યારે (સાચું)
	    {
	      વૃક્ષ label;
	      જો (c_parser_next_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  તોડો;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->કિંમત);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      add_stmt (build_stmt (label_loc, DECL_પદાવલિ, label));
	      c_parser_consume_token (parser);
	      જો (c_parser_next_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      નહીંતર
		તોડો;
	    }
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      પાછા endloc;
    }
  વૃક્ષ before_labels = get_before_labels ();
  જ્યારે (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_point_location_if_in_system_header (loc);

      તાર્કિક want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : ખોટું);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      જો (in_omp_loop_block && !last_label)
	{
	  વૃક્ષ_code code = omp_for_parse_state->code;
	  જો (want_nested_loop
	      && c_parser_omp_next_tokens_can_be_canon_loop (parser, code,
							     ખોટું))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      add_structured_block_stmt (કાઢો_stmt_list (sl));
	      omp_for_parse_state->depth++;
	      add_stmt (c_parser_omp_loop_nest (parser, ખાલી));
	      omp_for_parse_state->depth--;
	      sl = ધકેલો_stmt_list ();
	      parser->error = ખોટું;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ચાલુ;
	    }
	  નહીંતર જો (want_nested_loop
		   && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      વૃક્ષ pre_sl = કાઢો_stmt_list (sl);
	      વૃક્ષ nested_sl = ધકેલો_stmt_list ();
	      mark_valid_location_for_stdc_pragma (ખોટું);
	      c_parser_statement_after_labels (parser, ખાલી, NULL_વૃક્ષ);
	      nested_sl = કાઢો_stmt_list (nested_sl);
	      જો (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_code (parser);
		  sl = ધકેલો_stmt_list ();
		  add_stmt (pre_sl);
		  add_stmt (nested_sl);
		}
	      નહીંતર
		{
		  /* It contains the nested loop.  */
		  add_structured_block_stmt (pre_sl);
		  add_stmt (nested_sl);
		  sl = ધકેલો_stmt_list ();
		}
	      parser->error = ખોટું;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ચાલુ;
	    }
	  નહીંતર જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ચાલુ;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      તાર્કિક have_std_attrs
	= c_parser_nth_token_starts_std_attributes (parser, 1);
      વૃક્ષ std_attrs = NULL_વૃક્ષ;
      જો (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      જો (c_parser_next_token_is_keyword (parser, RID_CASE)
	  || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  જો (c_parser_next_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  નહીંતર
	    label_loc = c_parser_peek_token (parser)->location;
	  last_label = સાચું;
	  last_stmt = ખોટું;
	  mark_valid_location_for_stdc_pragma (ખોટું);
	  જો (in_omp_loop_block)
	    check_omp_intervening_code (parser);
	  c_parser_label (parser, std_attrs);
	}
      નહીંતર જો (c_parser_next_tokens_start_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_attributes
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_next_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = સાચું)))
	{
	  જો (last_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  જો (in_omp_loop_block)
	    {
	      check_omp_intervening_code (parser);
	      omp_for_parse_state->want_nested_loop = ખોટું;
	    }
	  mark_valid_location_for_stdc_pragma (ખોટું);
	  તાર્કિક fallthru_attr_p = ખોટું;
	  c_parser_declaration_or_fndef (parser, સાચું, !have_std_attrs,
					 સાચું, સાચું, સાચું, ખોટું, ખાલી,
					 ખાલી, have_std_attrs, std_attrs,
					 ખાલી, &fallthru_attr_p);

	  જો (in_omp_loop_block)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  જો (last_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  last_stmt = fallthru_attr_p;
	  last_label = ખોટું;
	  before_labels = get_before_labels ();
	}
      નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  જ્યારે (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  જો (!have_std_attrs
	      && (c_parser_next_tokens_start_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_attributes (parser, 2)))
	    {
	      પૂર્ણાંક ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      last_label = ખોટું;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      જો (in_omp_loop_block)
		{
		  check_omp_intervening_code (parser);
		  omp_for_parse_state->want_nested_loop = ખોટું;
		}
	      mark_valid_location_for_stdc_pragma (ખોટું);
	      c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, સાચું,
					     સાચું, ખોટું);
	      જો (in_omp_loop_block)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      જો (last_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      last_stmt = ખોટું;
	      before_labels = get_before_labels ();
	    }
	  નહીંતર
	    જાઓ statement;
	}
      નહીંતર જો (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  જો (have_std_attrs && !parser->in_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  નહીંતર જો (std_attrs)
	    c_warn_unused_attributes (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  જો (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = ખોટું;
	  જો (c_parser_pragma (parser,
			       last_label ? pragma_stmt : pragma_compound,
			       ખાલી, before_labels))
	    {
	      last_label = ખોટું;
	      last_stmt = સાચું;
	      જો (omp_for_parse_state)
		check_omp_intervening_code (parser);
	    }
	  જો (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      નહીંતર જો (c_parser_next_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  પાછા c_parser_peek_token (parser)->location;
	}
      નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_ELSE))
        {
          જો (parser->in_if_block)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      પાછા c_parser_peek_token (parser)->location;
            }
          નહીંતર
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              ચાલુ;
            }
        }
      નહીંતર
	{
	statement:
	  c_warn_unused_attributes (std_attrs);
	  last_label = ખોટું;
	  last_stmt = સાચું;
	  mark_valid_location_for_stdc_pragma (ખોટું);
	  જો (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, ખાલી, before_labels,
					     ખાલી, astate);
	  નહીંતર
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = ખોટું;
	      check_omp_intervening_code (parser);
	      c_parser_statement_after_labels (parser, ખાલી, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = ખોટું;
      astate.reset ();
    }
  જો (last_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  જો (sl)
    {
      sl = કાઢો_stmt_list (sl);
      જો (omp_for_parse_state->want_nested_loop)
	add_stmt (sl);
      નહીંતર
	add_structured_block_stmt (sl);
    }
  પાછા endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

સ્થિર attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  તાર્કિક have_std_attrs;
  વૃક્ષ std_attrs = ખાલી;
  જો ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  જ્યારે (c_parser_next_token_is_keyword (parser, RID_CASE)
	 || c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_next_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = ખાલી;
      જો ((have_std_attrs = c_parser_nth_token_starts_std_attributes (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  જો (std_attrs
      && (!c_parser_handle_statement_omp_attributes (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      જો (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_unused_attributes (std_attrs);
    }
  નહીંતર જો (have_std_attrs && c_parser_next_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  પાછા attr;
}


/* Information used while parsing an OpenMP metadirective.  */
સંરચના omp_metadirective_parse_data {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<વૃક્ષ> * GTY((skip)) body_labels;
  unsigned પૂર્ણાંક region_અંક;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
સ્થિર વૃક્ષ
mangle_metadirective_region_label (c_parser *parser, વૃક્ષ name)
{
  જો (parser->omp_metadirective_state->body_labels->contains (name))
    {
      અચલ અક્ષર *old_name = IDENTIFIER_POINTER (name);
      અક્ષર *new_name = (અક્ષર *) XALLOCAVEC (અક્ષર, strlen (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_અંક);
      પાછા get_identifier (new_name);
    }
  પાછા name;
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
સ્થિર શૂન્ય
c_parser_label (c_parser *parser, વૃક્ષ std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  વૃક્ષ label = NULL_વૃક્ષ;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  તાર્કિક fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  જો (c_parser_next_token_is_keyword (parser, RID_CASE))
    {
      વૃક્ષ exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_to_rvalue (loc1,
				       c_parser_પદાવલિ_no_commas (parser, ખાલી),
				       સાચું, સાચું).કિંમત;
      જો (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_વૃક્ષ, std_attrs);
	}
      નહીંતર જો (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_to_rvalue (loc1,
					   c_parser_પદાવલિ_no_commas (parser,
								    ખાલી),
					   સાચું, સાચું).કિંમત;
	  જો (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      નહીંતર
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      જો (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_વૃક્ષ, NULL_વૃક્ષ, std_attrs);
    }
  નહીંતર
    {
      વૃક્ષ name = c_parser_peek_token (parser)->કિંમત;
      વૃક્ષ tlab;
      વૃક્ષ attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_attributes (parser);
      જો (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      જો (tlab)
	{
	  decl_attributes (&tlab, attrs, 0);
	  decl_attributes (&tlab, std_attrs, 0);
	  label = add_stmt (build_stmt (loc1, LABEL_પદાવલિ, tlab));
	}
      જો (attrs
	  && c_parser_next_tokens_start_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  જો (label)
    {
      જો (વૃક્ષ_CODE (label) == LABEL_પદાવલિ)
	FALLTHROUGH_LABEL_P (LABEL_પદાવલિ_LABEL (label)) = fallthrough_p;
      નહીંતર
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

સ્થિર શૂન્ય
c_parser_statement (c_parser *parser, તાર્કિક *if_p, location_t *loc_after_labels)
{
  વૃક્ષ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  જો (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = ખોટું;
  c_parser_statement_after_labels (parser, if_p, before_labels, ખાલી, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

સ્થિર વૃક્ષ
c_parser_bc_name (c_parser *parser, તાર્કિક is_break)
{
  જો (!c_parser_next_token_is (parser, CPP_NAME))
    પાછા NULL_વૃક્ષ;

  c_token *tok = c_parser_peek_token (parser);
  વૃક્ષ label = c_finish_bc_name (tok->location, tok->કિંમત, is_break);
  c_parser_consume_token (parser);
  પાછા label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

સ્થિર શૂન્ય
c_parser_statement_after_labels (c_parser *parser, તાર્કિક *if_p,
				 વૃક્ષ before_labels,
				 vec<વૃક્ષ> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ stmt = NULL_વૃક્ષ;
  તાર્કિક in_if_block = parser->in_if_block;
  parser->in_if_block = ખોટું;
  જો (if_p != ખાલી)
    *if_p = ખોટું;

  જો (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    add_debug_begin_stmt (loc);

 restart:
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_OPEN_BRACE:
      add_stmt (c_parser_compound_statement (parser));
      તોડો;
    સ્થિતિ CPP_KEYWORD:
      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  તોડો;
	સ્થિતિ RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  તોડો;
	સ્થિતિ RID_WHILE:
	  c_parser_while_statement (parser, ખોટું, 0, ખોટું, if_p, before_labels);
	  તોડો;
	સ્થિતિ RID_DO:
	  c_parser_do_statement (parser, ખોટું, 0, ખોટું, before_labels);
	  તોડો;
	સ્થિતિ RID_FOR:
	  c_parser_for_statement (parser, ખોટું, 0, ખોટું, if_p, before_labels);
	  તોડો;
	સ્થિતિ RID_GOTO:
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      વૃક્ષ name = c_parser_peek_token (parser)->કિંમત;
	      જો (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_finish_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  નહીંતર જો (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      સંરચના c_પદાવલિ val;

	      c_parser_consume_token (parser);
	      val = c_parser_expression (parser);
	      val = convert_lvalue_to_rvalue (loc, val, ખોટું, સાચું);
	      stmt = c_finish_goto_ptr (loc, val);
	    }
	  નહીંતર
	    c_parser_error (parser, "expected identifier or %<*%>");
	  જાઓ expect_semicolon;
	સ્થિતિ RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_continue_label, ખોટું,
				   c_parser_bc_name (parser, ખોટું));
	  જાઓ expect_semicolon;
	સ્થિતિ RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_finish_bc_stmt (loc, objc_foreach_break_label, સાચું,
				   c_parser_bc_name (parser, સાચું));
	  જાઓ expect_semicolon;
	સ્થિતિ RID_RETURN:
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_finish_return (loc, NULL_વૃક્ષ, NULL_વૃક્ષ,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  નહીંતર
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      સંરચના c_પદાવલિ પદાવલિ = c_parser_expression_conv (parser);
	      mark_exp_read (પદાવલિ.કિંમત);
	      stmt = c_finish_return (પદાવલિ_LOC_OR_LOC (પદાવલિ.કિંમત, xloc),
				      પદાવલિ.કિંમત, પદાવલિ.original_type,
				      astate.musttail_p);
	      જાઓ expect_semicolon;
	    }
	  તોડો;
	સ્થિતિ RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  તોડો;
	સ્થિતિ RID_TRANSACTION_ATOMIC:
	સ્થિતિ RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  તોડો;
	સ્થિતિ RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  જાઓ expect_semicolon;
	સ્થિતિ RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_વૃક્ષ);
	      c_parser_consume_token (parser);
	    }
	  નહીંતર
	    {
	      સંરચના c_પદાવલિ પદાવલિ = c_parser_expression (parser);
	      પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, ખોટું, ખોટું);
	      પદાવલિ.કિંમત = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
	      stmt = objc_build_throw_stmt (loc, પદાવલિ.કિંમત);
	      જાઓ expect_semicolon;
	    }
	  તોડો;
	સ્થિતિ RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  તોડો;
	સ્થિતિ RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  તોડો;
	સ્થિતિ RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    વૃક્ષ attrs = c_parser_gnu_attributes (parser);
	    તાર્કિક has_assume = lookup_attribute ("assume", attrs);
	    જો (has_assume)
	      {
		જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, સાચું);
		નહીંતર
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = ખોટું;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    જો (astate.musttail_p)
	      {
		જો (attrs)
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		જાઓ restart;
	      }
	    જો (attribute_fallthrough_p (attrs))
	      {
		જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
		  {
		    વૃક્ષ fn = build_call_પદાવલિ_internal_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_ગાંઠ, 0);
		    add_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		નહીંતર
		  {
		    auto_urlify_attributes sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    નહીંતર જો (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    નહીંતર જો (attrs != NULL_વૃક્ષ)
	      {
		auto_urlify_attributes sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    તોડો;
	  }
	મૂળભૂત:
	  જાઓ પદાવલિ_stmt;
	}
      તોડો;
    સ્થિતિ CPP_SEMICOLON:
      c_parser_consume_token (parser);
      તોડો;
    સ્થિતિ CPP_CLOSE_PAREN:
    સ્થિતિ CPP_CLOSE_SQUARE:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      તોડો;
    સ્થિતિ CPP_PRAGMA:
      જો (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        જાઓ restart;
      તોડો;
    મૂળભૂત:
    પદાવલિ_stmt:
      stmt = c_finish_પદાવલિ_stmt (loc, c_parser_expression_conv (parser).કિંમત);
    expect_semicolon:
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      તોડો;
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
  જો (પદાવલિ_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_set_પદાવલિ_location (stmt, loc);

  parser->in_if_block = in_if_block;
}

/* Parse the condition from an if, do, while or for statements.  */

સ્થિર વૃક્ષ
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ cond;
  cond = c_parser_expression_conv (parser).કિંમત;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, ખોટું, ખાલી);
  જો (warn_sequence_point)
    verify_sequence_points (cond);
  પાછા cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

સ્થિર વૃક્ષ
c_parser_paren_condition (c_parser *parser)
{
  વૃક્ષ cond;
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા error_mark_ગાંઠ;
  cond = c_parser_condition (parser);
  parens.skip_until_found_close (parser);
  પાછા cond;
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

સ્થિર c_પદાવલિ
c_parser_selection_header (c_parser *parser, તાર્કિક switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_પદાવલિ પદાવલિ;
  તાર્કિક parse_પદાવલિ = સાચું;
  વૃક્ષ std_attrs;
  તાર્કિક have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
  જો (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  નહીંતર
    std_attrs = NULL_વૃક્ષ;
  જો (c_parser_next_tokens_start_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      પદાવલિ.કિંમત
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/ખોટું,
					 /*static_assert_ok=*/ખોટું,
					 /*empty_ok=*/ખોટું,
					 /*nested=*/સાચું,
					 /*start_attr_ok=*/સાચું,
					 /*simple_ok=*/સાચું,
					 /*objc_foreach_object_decl=*/nullptr,
					 /*omp_declare_simd_clauses=*/nullptr,
					 have_std_attrs,
					 std_attrs);
      જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      નહીંતર
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  જો (!પદાવલિ.કિંમત)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      પદાવલિ.original_type = error_mark_ગાંઠ;
	      પદાવલિ.set_error ();
	      પાછા પદાવલિ;
	    }
	  parse_પદાવલિ = ખોટું;
	}
      જો (પદાવલિ.કિંમત)
	{
	  પદાવલિ.original_type = વૃક્ષ_TYPE (પદાવલિ.કિંમત);
	  પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, /*convert_p=*/સાચું,
					   /*read_p=*/સાચું);
	}
    }
  નહીંતર જો (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      પદાવલિ.original_type = error_mark_ગાંઠ;
      પદાવલિ.set_error ();
      પાછા પદાવલિ;
    }

  જો (parse_પદાવલિ)
    પદાવલિ = c_parser_expression_conv (parser);
  જો (!switch_p)
    {
      પદાવલિ.કિંમત = c_objc_common_truthvalue_conversion (loc, પદાવલિ.કિંમત);
      પદાવલિ.કિંમત = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
      જો (warn_sequence_point)
	verify_sequence_points (પદાવલિ.કિંમત);
    }
  પાછા પદાવલિ;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

સ્થિર વૃક્ષ
c_parser_paren_selection_header (c_parser *parser)
{
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા error_mark_ગાંઠ;
  વૃક્ષ cond = c_parser_selection_header (parser, /*switch_p=*/ખોટું).કિંમત;
  parens.skip_until_found_close (parser);
  પાછા cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

સ્થિર વૃક્ષ
c_parser_c99_block_statement (c_parser *parser, તાર્કિક *if_p,
			      location_t *loc_after_labels)
{
  વૃક્ષ block = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  પાછા c_end_compound_stmt (loc, block, flag_isoc99);
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

સ્થિર વૃક્ષ
c_parser_if_body (c_parser *parser, તાર્કિક *if_p,
		  અચલ token_indent_info &if_tinfo)
{
  વૃક્ષ block = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  વૃક્ષ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
      જો (!c_parser_next_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  નહીંતર જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    add_stmt (c_parser_compound_statement (parser));
  નહીંતર
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, ખાલી, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, next_tinfo);
  જો (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    if_tinfo.location, RID_IF);

  પાછા c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

સ્થિર વૃક્ષ
c_parser_else_body (c_parser *parser, અચલ token_indent_info &else_tinfo,
		    vec<વૃક્ષ> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ block = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  વૃક્ષ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      add_stmt (build_empty_stmt (loc));
      c_parser_consume_token (parser);
    }
  નહીંતર
    {
      જો (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, ખાલી, before_labels, chain, a);
    }

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, next_tinfo);
  જો (body_loc_after_labels != UNKNOWN_LOCATION
      && next_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, next_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  પાછા c_end_compound_stmt (body_loc, block, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

સ્થિર શૂન્ય
c_parser_if_statement (c_parser *parser, તાર્કિક *if_p, vec<વૃક્ષ> *chain)
{
  વૃક્ષ block;
  location_t loc;
  વૃક્ષ cond;
  તાર્કિક nested_if = ખોટું;
  વૃક્ષ first_body, second_body;
  તાર્કિક in_if_block;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_header (parser);
  in_if_block = parser->in_if_block;
  parser->in_if_block = સાચું;
  first_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->in_if_block = in_if_block;

  જો (warn_duplicated_cond)
    warn_duplicated_cond_add_or_warn (પદાવલિ_LOCATION (cond), cond, &chain);

  જો (c_parser_next_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      જો (warn_duplicated_cond)
	{
	  જો (c_parser_next_token_is_keyword (parser, RID_IF)
	      && chain == ખાલી)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = નવું vec<વૃક્ષ> ();
	      જો (!CONSTANT_CLASS_P (cond) && !વૃક્ષ_SIDE_EFFECTS (cond))
		chain->safe_ધકેલો (cond);
	    }
	  નહીંતર જો (!c_parser_next_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      second_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      જો (if_p != ખાલી)
	*if_p = સાચું;
    }
  નહીંતર
    {
      second_body = NULL_વૃક્ષ;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      જો (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      જો (warn_duplicated_cond)
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

સ્થિર શૂન્ય
c_parser_switch_statement (c_parser *parser, તાર્કિક *if_p, વૃક્ષ before_labels)
{
  સંરચના c_પદાવલિ ce;
  વૃક્ષ block, પદાવલિ, body;
  unsigned અક્ષર save_in_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  વૃક્ષ switch_name;
  પૂર્ણાંક અંક_names = c_get_loop_names (before_labels, સાચું, &switch_name);
  block = c_begin_compound_stmt (flag_isoc99);
  તાર્કિક explicit_cast_p = ખોટું;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = સાચું;
      ce = c_parser_selection_header (parser, /*switch_p=*/સાચું);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_to_rvalue (switch_cond_loc, ce, સાચું, સાચું);
      પદાવલિ = ce.કિંમત;
      /* ??? expr has no valid location?  */
      parens.skip_until_found_close (parser);
    }
  નહીંતર
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      પદાવલિ = error_mark_ગાંઠ;
      ce.original_type = error_mark_ગાંઠ;
    }
  વૃક્ષ stmt
    = c_start_switch (switch_loc, switch_cond_loc, પદાવલિ, explicit_cast_p,
		      switch_name);
  save_in_statement = in_statement;
  in_statement |= IN_SWITCH_STMT;
  જો (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  નહીંતર
    in_statement &= ~IN_NAMED_STMT;
  location_t loc_after_labels;
  તાર્કિક open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  location_t next_loc = c_parser_peek_token (parser)->location;
  જો (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, next_loc, switch_loc,
				    RID_SWITCH);
  c_finish_switch (body, ce.original_type);
  in_statement = save_in_statement;
  જો (અંક_names)
    {
      જો (!C_DECL_LOOP_SWITCH_NAME_USED (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_વૃક્ષ;
      નહીંતર
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_names (અંક_names);
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

સ્થિર શૂન્ય
c_parser_while_statement (c_parser *parser, તાર્કિક ivdep, unsigned short unroll,
			  તાર્કિક novector, તાર્કિક *if_p, વૃક્ષ before_labels)
{
  વૃક્ષ block, cond, body;
  unsigned અક્ષર save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  વૃક્ષ loop_name;
  પૂર્ણાંક અંક_names = c_get_loop_names (before_labels, ખોટું, &loop_name);

  જો (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = સાચું;
    }

  c_parser_consume_token (parser);
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  જો (ivdep && cond != error_mark_ગાંઠ)
    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
		   build_int_cst (integer_type_ગાંઠ,
				  annot_પદાવલિ_ivdep_kind),
		   integer_zero_ગાંઠ);
  જો (unroll && cond != error_mark_ગાંઠ)
    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
		   build_int_cst (integer_type_ગાંઠ,
				  annot_પદાવલિ_unroll_kind),
		   build_int_cst (integer_type_ગાંઠ, unroll));
  જો (novector && cond != error_mark_ગાંઠ)
    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
		   build_int_cst (integer_type_ગાંઠ,
				  annot_પદાવલિ_no_vector_kind),
		   integer_zero_ગાંઠ);
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  જો (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  તાર્કિક open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);
  જો (loop_name && !C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
    loop_name = NULL_વૃક્ષ;
  add_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_વૃક્ષ,
			NULL_વૃક્ષ));
  add_stmt (c_end_compound_stmt (loc, block, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  જો (અંક_names)
    c_release_loop_names (અંક_names);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, next_tinfo);

  જો (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  in_statement = save_in_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

સ્થિર શૂન્ય
c_parser_do_statement (c_parser *parser, તાર્કિક ivdep, unsigned short unroll,
		       તાર્કિક novector, વૃક્ષ before_labels)
{
  વૃક્ષ block, cond, body;
  unsigned અક્ષર save_in_statement;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_DO));
  વૃક્ષ loop_name;
  પૂર્ણાંક અંક_names = c_get_loop_names (before_labels, ખોટું, &loop_name);

  જો (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = સાચું;
    }

  c_parser_consume_token (parser);
  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  block = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_in_statement = in_statement;
  in_statement = IN_ITERATION_STMT;
  જો (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }
  body = c_parser_c99_block_statement (parser, ખાલી);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  in_statement = save_in_statement;
  જો (અંક_names)
    {
      જો (!C_DECL_LOOP_SWITCH_NAME_USED (loop_name))
	loop_name = NULL_વૃક્ષ;
      c_release_loop_names (અંક_names);
    }
  cond = c_parser_paren_condition (parser);
  જો (ivdep && cond != error_mark_ગાંઠ)
    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
		   build_int_cst (integer_type_ગાંઠ,
				  annot_પદાવલિ_ivdep_kind),
		   integer_zero_ગાંઠ);
  જો (unroll && cond != error_mark_ગાંઠ)
    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
		   build_int_cst (integer_type_ગાંઠ,
				  annot_પદાવલિ_unroll_kind),
 		   build_int_cst (integer_type_ગાંઠ, unroll));
  જો (novector && cond != error_mark_ગાંઠ)
    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
		   build_int_cst (integer_type_ગાંઠ,
				  annot_પદાવલિ_no_vector_kind),
		   integer_zero_ગાંઠ);
  જો (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
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

સ્થિર શૂન્ય
c_parser_for_statement (c_parser *parser, તાર્કિક ivdep, unsigned short unroll,
			તાર્કિક novector, તાર્કિક *if_p, વૃક્ષ before_labels)
{
  વૃક્ષ block, cond, incr, body;
  unsigned અક્ષર save_in_statement;
  વૃક્ષ save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  વૃક્ષ object_expression;
  /* Silence the bogus uninitialized warning.  */
  વૃક્ષ collection_expression = ખાલી;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  તાર્કિક is_foreach_statement = ખોટું;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  વૃક્ષ loop_name;
  પૂર્ણાંક અંક_names = c_get_loop_names (before_labels, ખોટું, &loop_name);

  જો (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = સાચું;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  block = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_ગાંઠ;
  incr = error_mark_ગાંઠ;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_expression = error_mark_ગાંઠ;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = ખોટું;
	  c_parser_consume_token (parser);
	  c_finish_પદાવલિ_stmt (loc, NULL_વૃક્ષ);
	}
      નહીંતર જો (c_parser_next_tokens_start_declaration (parser)
	       || c_parser_nth_token_starts_std_attributes (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, સાચું, સાચું,
					 ખોટું, &object_expression);
	  parser->objc_could_be_foreach_context = ખોટું;

	  જો (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = સાચું;
	      જો (check_for_loop_decls (for_loc, સાચું) == NULL_વૃક્ષ)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  નહીંતર
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  જ્યારે (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  જો (c_parser_next_tokens_start_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_attributes (parser, 2))
	    {
	      પૂર્ણાંક ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, સાચું,
					     સાચું, ખોટું, &object_expression);
	      parser->objc_could_be_foreach_context = ખોટું;

	      restore_extension_diagnostics (ext);
	      જો (c_parser_next_token_is_keyword (parser, RID_IN))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = સાચું;
		  જો (check_for_loop_decls (for_loc, સાચું) == NULL_વૃક્ષ)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      નહીંતર
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  નહીંતર
	    જાઓ init_પદાવલિ;
	}
      નહીંતર
	{
	init_પદાવલિ:
	  {
	    સંરચના c_પદાવલિ ce;
	    વૃક્ષ init_expression;
	    ce = c_parser_expression (parser);
	    init_expression = ce.કિંમત;
	    parser->objc_could_be_foreach_context = ખોટું;
	    જો (c_parser_next_token_is_keyword (parser, RID_IN))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = સાચું;
		જો (! lvalue_p (init_expression))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_expression
		  = c_fully_fold (init_expression, ખોટું, ખાલી);
	      }
	    નહીંતર
	      {
		ce = convert_lvalue_to_rvalue (loc, ce, સાચું, ખોટું);
		init_expression = ce.કિંમત;
		c_finish_પદાવલિ_stmt (loc, init_expression);
		c_parser_skip_until_found (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      જો (!is_foreach_statement)
	{
	  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      જો (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_ગાંઠ;
		}
	      નહીંતર જો (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_ગાંઠ;
		}
	      નહીંતર
		{
		  c_parser_consume_token (parser);
		  cond = NULL_વૃક્ષ;
		}
	    }
	  નહીંતર
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_found (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  જો (ivdep && cond != error_mark_ગાંઠ)
	    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
			   build_int_cst (integer_type_ગાંઠ,
					  annot_પદાવલિ_ivdep_kind),
			   integer_zero_ગાંઠ);
	  જો (unroll && cond != error_mark_ગાંઠ)
	    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
 			   build_int_cst (integer_type_ગાંઠ,
					  annot_પદાવલિ_unroll_kind),
			   build_int_cst (integer_type_ગાંઠ, unroll));
	  જો (novector && cond && cond != error_mark_ગાંઠ)
	    cond = build3 (ANNOTATE_પદાવલિ, વૃક્ષ_TYPE (cond), cond,
			   build_int_cst (integer_type_ગાંઠ,
					  annot_પદાવલિ_no_vector_kind),
			   integer_zero_ગાંઠ);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  જો (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_expression = error_mark_ગાંઠ;
	    }
	  નહીંતર
	    incr = c_process_પદાવલિ_stmt (loc, NULL_વૃક્ષ);
	}
      નહીંતર
	{
	  જો (is_foreach_statement)
	    collection_expression
	      = c_fully_fold (c_parser_expression (parser).કિંમત, ખોટું, ખાલી);
	  નહીંતર
	    {
	      સંરચના c_પદાવલિ ce = c_parser_expression (parser);
	      ce = convert_lvalue_to_rvalue (loc, ce, સાચું, ખોટું);
	      incr = c_process_પદાવલિ_stmt (loc, ce.કિંમત);
	    }
	}
      parens.skip_until_found_close (parser);
    }
  save_in_statement = in_statement;
  જો (is_foreach_statement)
    {
      in_statement = IN_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      જો (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  નહીંતર
    in_statement = IN_ITERATION_STMT;
  જો (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      in_statement |= IN_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  તાર્કિક open_brace = c_parser_next_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_block_statement (parser, if_p, &loc_after_labels);

  જો (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_વૃક્ષ;
      DECL_CHAIN (objc_foreach_break_label) = NULL_વૃક્ષ;
    }

  જો (is_foreach_statement)
    objc_finish_foreach_loop (for_loc, object_expression,
			      collection_expression, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  નહીંતર
    add_stmt (build_stmt (for_loc, FOR_STMT, NULL_વૃક્ષ, cond, incr,
			  body, NULL_વૃક્ષ,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_USED (loop_name)
			  ? loop_name : NULL_વૃક્ષ, NULL_વૃક્ષ, NULL_વૃક્ષ));
  add_stmt (c_end_compound_stmt (for_loc, block,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info next_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, next_tinfo);

  જો (next_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, next_tinfo.location,
				    for_tinfo.location, RID_FOR);

  in_statement = save_in_statement;
  જો (અંક_names)
    c_release_loop_names (અંક_names);
  જો (is_foreach_statement)
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

સ્થિર વૃક્ષ
c_parser_asm_statement (c_parser *parser)
{
  વૃક્ષ str, outputs, inputs, clobbers, labels, ret;
  તાર્કિક simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  પૂર્ણાંક section, nsections;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  માટે (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      પસંદગી (token->keyword)
	{
	સ્થિતિ RID_VOLATILE:
	  જો (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->કિંમત);
	      inform (volatile_loc, "first seen here");
	    }
	  નહીંતર
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  ચાલુ;

	સ્થિતિ RID_INLINE:
	  જો (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->કિંમત);
	      inform (inline_loc, "first seen here");
	    }
	  નહીંતર
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  ચાલુ;

	સ્થિતિ RID_GOTO:
	  જો (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->કિંમત);
	      inform (goto_loc, "first seen here");
	    }
	  નહીંતર
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  ચાલુ;

	સ્થિતિ RID_CONST:
	સ્થિતિ RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->કિંમત);
	  c_parser_consume_token (parser);
	  ચાલુ;

	મૂળભૂત:
	  તોડો;
	}
      તોડો;
    }

  તાર્કિક is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  તાર્કિક is_inline = (inline_loc != UNKNOWN_LOCATION);
  તાર્કિક is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = ખાલી;

  matching_parens parens;
  જો (!parens.require_open (parser))
    જાઓ error;

  str = c_parser_asm_string_literal (parser);
  જો (str == NULL_વૃક્ષ)
    જાઓ error_close_paren;

  simple = સાચું;
  outputs = NULL_વૃક્ષ;
  inputs = NULL_વૃક્ષ;
  clobbers = NULL_વૃક્ષ;
  labels = NULL_વૃક્ષ;

  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    જાઓ done_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  માટે (section = 0; section < nsections; ++section)
    {
      જો (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  જો (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      જાઓ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	જાઓ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = ખોટું;

      જો ((!c_parser_next_token_is (parser, CPP_COLON)
	   && !c_parser_next_token_is (parser, CPP_SCOPE)
	   && !c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	પસંદગી (section)
	  {
	  સ્થિતિ 0:
	    outputs = c_parser_asm_operands (parser);
	    તોડો;
	  સ્થિતિ 1:
	    inputs = c_parser_asm_operands (parser);
	    તોડો;
	  સ્થિતિ 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    તોડો;
	  સ્થિતિ 3:
	    labels = c_parser_asm_goto_operands (parser);
	    તોડો;
	  મૂળભૂત:
	    gcc_unreachable ();
	  }

      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	જાઓ done_asm;
    }

 done_asm:
  જો (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
      જાઓ error;
    }

  જો (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_to_end_of_block_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_પદાવલિ (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  પાછા ret;

 error_close_paren:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
  જાઓ error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

સ્થિર વૃક્ષ
c_parser_asm_operands (c_parser *parser)
{
  વૃક્ષ list = NULL_વૃક્ષ;
  જ્યારે (સાચું)
    {
      વૃક્ષ name, str;
      સંરચના c_પદાવલિ પદાવલિ;
      જો (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
	{
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_LENGTH (id),
				   IDENTIFIER_POINTER (id));
	    }
	  નહીંતર
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, ખાલી);
	      પાછા NULL_વૃક્ષ;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	}
      નહીંતર
	name = NULL_વૃક્ષ;
      str = c_parser_asm_string_literal (parser);
      જો (str == NULL_વૃક્ષ)
	પાછા NULL_વૃક્ષ;
      matching_parens parens;
      જો (!parens.require_open (parser))
	પાછા NULL_વૃક્ષ;
      પદાવલિ = c_parser_expression (parser);
      mark_exp_read (પદાવલિ.કિંમત);
      જો (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	  પાછા NULL_વૃક્ષ;
	}
      list = chainon (list, build_વૃક્ષ_list (build_વૃક્ષ_list (name, str),
					     પદાવલિ.કિંમત));
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
    }
  પાછા list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

સ્થિર વૃક્ષ
c_parser_asm_clobbers (c_parser *parser)
{
  વૃક્ષ list = NULL_વૃક્ષ;
  જ્યારે (સાચું)
    {
      વૃક્ષ str = c_parser_asm_string_literal (parser);
      જો (str)
	list = વૃક્ષ_cons (NULL_વૃક્ષ, str, list);
      નહીંતર
	પાછા NULL_વૃક્ષ;
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
    }
  પાછા list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

સ્થિર વૃક્ષ
c_parser_asm_goto_operands (c_parser *parser)
{
  વૃક્ષ list = NULL_વૃક્ષ;
  જ્યારે (સાચું)
    {
      વૃક્ષ name, label;

      જો (c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->કિંમત;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  વૃક્ષ_USED (label) = 1;
	}
      નહીંતર
	{
	  c_parser_error (parser, "expected identifier");
	  પાછા NULL_વૃક્ષ;
	}

      name = build_string (IDENTIFIER_LENGTH (name),
			   IDENTIFIER_POINTER (name));
      list = વૃક્ષ_cons (name, label, list);
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	પાછા nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

સંરચના c_પદાવલિ
c_parser_string_literal (c_parser *parser, તાર્કિક translate, તાર્કિક wide_ok)
{
  સંરચના c_પદાવલિ ret;
  size_t ગણતરી;
  સંરચના obstack str_ob;
  સંરચના obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, last_tok_loc;
  ગણના cpp_ttype type;
  વૃક્ષ કિંમત, string_વૃક્ષ;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  last_tok_loc = linemap_resolve_location (લીટી_table, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   ખાલી);
  type = tok->type;
  પસંદગી (type)
    {
    સ્થિતિ CPP_STRING:
    સ્થિતિ CPP_WSTRING:
    સ્થિતિ CPP_STRING16:
    સ્થિતિ CPP_STRING32:
    સ્થિતિ CPP_UTF8STRING:
      string_વૃક્ષ = tok->કિંમત;
      તોડો;

    મૂળભૂત:
      c_parser_error (parser, "expected string literal");
      ret.set_error ();
      ret.કિંમત = NULL_વૃક્ષ;
      ret.original_code = ERROR_MARK;
      ret.original_type = NULL_વૃક્ષ;
      પાછા ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  પસંદગી (c_parser_peek_2nd_token (parser)->type)
    {
    મૂળભૂત:
      c_parser_consume_token (parser);
      str.text = (અચલ unsigned અક્ષર *) વૃક્ષ_STRING_POINTER (string_વૃક્ષ);
      str.len = વૃક્ષ_STRING_LENGTH (string_વૃક્ષ);
      ગણતરી = 1;
      strs = &str;
      તોડો;

    સ્થિતિ CPP_STRING:
    સ્થિતિ CPP_WSTRING:
    સ્થિતિ CPP_STRING16:
    સ્થિતિ CPP_STRING32:
    સ્થિતિ CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      ગણતરી = 0;
      કરો
	{
	  c_parser_consume_token (parser);
	  ગણતરી++;
	  str.text = (અચલ unsigned અક્ષર *) વૃક્ષ_STRING_POINTER (string_વૃક્ષ);
	  str.len = વૃક્ષ_STRING_LENGTH (string_વૃક્ષ);
	  જો (type != tok->type)
	    {
	      જો (type == CPP_STRING)
		type = tok->type;
	      નહીંતર જો (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, કદ (cpp_string));
	  obstack_grow (&loc_ob, &last_tok_loc, કદ (location_t));
	  tok = c_parser_peek_token (parser);
	  string_વૃક્ષ = tok->કિંમત;
	  last_tok_loc
	    = linemap_resolve_location (લીટી_table, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, ખાલી);
	}
      જ્યારે (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_finish (&str_ob);
    }

  જો (ગણતરી > 1 && !in_system_header_at (આગત_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  જો ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_in, strs, ગણતરી, &istr, type)))
    {
      કિંમત = build_string (istr.len, (અચલ અક્ષર *) istr.text);
      મુક્ત (const_cast<unsigned અક્ષર *> (istr.text));
      જો (ગણતરી > 1)
	{
	  location_t *locs = (location_t *) obstack_finish (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->record_string_concatenation (ગણતરી, locs);
	}
    }
  નહીંતર
    {
      જો (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      પસંદગી (type)
	{
	મૂળભૂત:
	સ્થિતિ CPP_STRING:
	સ્થિતિ CPP_UTF8STRING:
	  જો (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      કિંમત = build_string (TYPE_PRECISION (char8_type_ગાંઠ)
				    / TYPE_PRECISION (char_type_ગાંઠ),
				    "");  /* char8_t is 8 bits */
	    }
	  નહીંતર
	    કિંમત = build_string (1, "");
	  તોડો;
	સ્થિતિ CPP_STRING16:
	  કિંમત = build_string (TYPE_PRECISION (char16_type_ગાંઠ)
				/ TYPE_PRECISION (char_type_ગાંઠ),
				"\0");  /* char16_t is 16 bits */
	  તોડો;
	સ્થિતિ CPP_STRING32:
	  કિંમત = build_string (TYPE_PRECISION (char32_type_ગાંઠ)
				/ TYPE_PRECISION (char_type_ગાંઠ),
				"\0\0\0");  /* char32_t is 32 bits */
	  તોડો;
	સ્થિતિ CPP_WSTRING:
	  કિંમત = build_string (TYPE_PRECISION (wchar_type_ગાંઠ)
				/ TYPE_PRECISION (char_type_ગાંઠ),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  તોડો;
        }
    }

  પસંદગી (type)
    {
    મૂળભૂત:
    સ્થિતિ CPP_STRING:
      વૃક્ષ_TYPE (કિંમત) = char_array_type_ગાંઠ;
      તોડો;
    સ્થિતિ CPP_UTF8STRING:
      જો (flag_char8_t)
	વૃક્ષ_TYPE (કિંમત) = char8_array_type_ગાંઠ;
      નહીંતર
	વૃક્ષ_TYPE (કિંમત) = char_array_type_ગાંઠ;
      તોડો;
    સ્થિતિ CPP_STRING16:
      વૃક્ષ_TYPE (કિંમત) = char16_array_type_ગાંઠ;
      તોડો;
    સ્થિતિ CPP_STRING32:
      વૃક્ષ_TYPE (કિંમત) = char32_array_type_ગાંઠ;
      તોડો;
    સ્થિતિ CPP_WSTRING:
      વૃક્ષ_TYPE (કિંમત) = wchar_array_type_ગાંઠ;
    }
  કિંમત = fix_string_type (કિંમત);

  જો (ગણતરી > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.કિંમત = કિંમત;
  ret.original_code = STRING_CST;
  ret.original_type = NULL_વૃક્ષ;
  set_c_પદાવલિ_source_range (&ret, get_range_from_loc (લીટી_table, loc));
  ret.m_decimal = 0;
  parser->seen_string_literal = સાચું;
  પાછા ret;
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

સ્થિર સંરચના c_પદાવલિ
c_parser_પદાવલિ_no_commas (c_parser *parser, સંરચના c_પદાવલિ *after,
			 વૃક્ષ omp_atomic_lhs)
{
  સંરચના c_પદાવલિ lhs, rhs, ret;
  ગણના વૃક્ષ_code code;
  location_t op_location, exp_location;
  તાર્કિક save_in_omp_for = c_in_omp_for;
  c_in_omp_for = ખોટું;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_expression (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_EQ:
      code = NOP_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_MULT_EQ:
      code = MULT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_DIV_EQ:
      code = TRUNC_DIV_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_MOD_EQ:
      code = TRUNC_MOD_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_PLUS_EQ:
      code = PLUS_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_MINUS_EQ:
      code = MINUS_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_LSHIFT_EQ:
      code = LSHIFT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_RSHIFT_EQ:
      code = RSHIFT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_AND_EQ:
      code = BIT_AND_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_XOR_EQ:
      code = BIT_XOR_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_OR_EQ:
      code = BIT_IOR_પદાવલિ;
      તોડો;
    મૂળભૂત:
      c_in_omp_for = save_in_omp_for;
      પાછા lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  rhs = convert_lvalue_to_rvalue (exp_location, rhs, સાચું, સાચું);

  ret.કિંમત = build_modify_પદાવલિ (op_location, lhs.કિંમત, lhs.original_type,
				 code, exp_location, rhs.કિંમત,
				 rhs.original_type);
  ret.m_decimal = 0;
  set_c_પદાવલિ_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  જો (code == NOP_પદાવલિ)
    ret.original_code = MODIFY_પદાવલિ;
  નહીંતર
    {
      suppress_warning (ret.કિંમત, OPT_Wparentheses);
      ret.original_code = ERROR_MARK;
    }
  ret.original_type = ખાલી;
  c_in_omp_for = save_in_omp_for;
  પાછા ret;
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

સ્થિર સંરચના c_પદાવલિ
c_parser_conditional_expression (c_parser *parser, સંરચના c_પદાવલિ *after,
				 વૃક્ષ omp_atomic_lhs)
{
  સંરચના c_પદાવલિ cond, exp1, exp2, ret;
  location_t start, cond_loc, colon_loc;
  તાર્કિક save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_દ્વિઅંકી_expression (parser, after, omp_atomic_lhs);

  જો (c_parser_next_token_is_not (parser, CPP_QUERY))
    પાછા cond;
  c_omp_array_section_p = ખોટું;
  જો (cond.કિંમત != error_mark_ગાંઠ)
    start = cond.get_start ();
  નહીંતર
    start = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_to_rvalue (cond_loc, cond, સાચું, સાચું);
  c_parser_consume_token (parser);
  જો (c_parser_next_token_is (parser, CPP_COLON))
    {
      વૃક્ષ eptype = NULL_વૃક્ષ;

      location_t મધ્ય_loc = c_parser_peek_token (parser)->location;
      pedwarn (મધ્ય_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      જો (વૃક્ષ_CODE (cond.કિંમત) == EXCESS_PRECISION_પદાવલિ)
	{
	  eptype = વૃક્ષ_TYPE (cond.કિંમત);
	  cond.કિંમત = વૃક્ષ_OPERAND (cond.કિંમત, 0);
	}
      વૃક્ષ e = cond.કિંમત;
      જ્યારે (વૃક્ષ_CODE (e) == COMPOUND_પદાવલિ)
	e = વૃક્ષ_OPERAND (e, 1);
      warn_for_omitted_condop (મધ્ય_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.કિંમત = save_પદાવલિ (default_conversion (cond.કિંમત));
      જો (eptype)
	exp1.કિંમત = build1 (EXCESS_PRECISION_પદાવલિ, eptype, exp1.કિંમત);
      exp1.original_type = ખાલી;
      exp1.src_range = cond.src_range;
      cond.કિંમત = c_objc_common_truthvalue_conversion (cond_loc, exp1.કિંમત);
      c_inhibit_evaluation_warnings += cond.કિંમત == truthvalue_true_ગાંઠ;
    }
  નહીંતર
    {
      cond.કિંમત
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.કિંમત));
      c_inhibit_evaluation_warnings += cond.કિંમત == truthvalue_false_ગાંઠ;
      exp1 = c_parser_expression_conv (parser);
      mark_exp_read (exp1.કિંમત);
      c_inhibit_evaluation_warnings +=
	((cond.કિંમત == truthvalue_true_ગાંઠ)
	 - (cond.કિંમત == truthvalue_false_ગાંઠ));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.કિંમત == truthvalue_true_ગાંઠ;
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ખાલી;
      c_omp_array_section_p = save_c_omp_array_section_p;
      પાછા ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_expression (parser, ખાલી, NULL_વૃક્ષ);
    exp2 = convert_lvalue_to_rvalue (exp2_loc, exp2, સાચું, સાચું);
  }
  c_inhibit_evaluation_warnings -= cond.કિંમત == truthvalue_true_ગાંઠ;
  location_t loc1 = make_location (exp1.get_start (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_start (), exp2.src_range);
  જો (UNLIKELY (omp_atomic_lhs != ખાલી)
      && (વૃક્ષ_CODE (cond.કિંમત) == GT_પદાવલિ
	  || વૃક્ષ_CODE (cond.કિંમત) == LT_પદાવલિ
	  || વૃક્ષ_CODE (cond.કિંમત) == EQ_પદાવલિ)
      && c_વૃક્ષ_equal (exp2.કિંમત, omp_atomic_lhs)
      && (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (cond.કિંમત, 0), omp_atomic_lhs)
	  || c_વૃક્ષ_equal (વૃક્ષ_OPERAND (cond.કિંમત, 1), omp_atomic_lhs)))
    ret.કિંમત = build3_loc (colon_loc, COND_પદાવલિ, વૃક્ષ_TYPE (omp_atomic_lhs),
			    cond.કિંમત, exp1.કિંમત, exp2.કિંમત);
  નહીંતર
    ret.કિંમત
      = build_conditional_પદાવલિ (colon_loc, cond.કિંમત,
				cond.original_code == C_MAYBE_CONST_પદાવલિ,
				exp1.કિંમત, exp1.original_type, loc1,
				exp2.કિંમત, exp2.original_type, loc2);
  ret.original_code = ERROR_MARK;
  જો (exp1.કિંમત == error_mark_ગાંઠ || exp2.કિંમત == error_mark_ગાંઠ)
    ret.original_type = ખાલી;
  નહીંતર
    {
      વૃક્ષ t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : વૃક્ષ_TYPE (exp1.કિંમત);
      t2 = exp2.original_type ? exp2.original_type : વૃક્ષ_TYPE (exp2.કિંમત);
      ret.original_type = ((t1 != error_mark_ગાંઠ
			    && t2 != error_mark_ગાંઠ
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : ખાલી);
    }
  set_c_પદાવલિ_source_range (&ret, start, exp2.get_finish ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  પાછા ret;
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

સ્થિર સંરચના c_પદાવલિ
c_parser_દ્વિઅંકી_expression (c_parser *parser, સંરચના c_પદાવલિ *after,
			    વૃક્ષ omp_atomic_lhs)
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

  સંરચના {
    /* The expression at this stack level.  */
    સંરચના c_પદાવલિ પદાવલિ;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    ગણના c_parser_prec prec;
    /* The operation on its left.  */
    ગણના વૃક્ષ_code op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    વૃક્ષ sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    વૃક્ષ orig_પદાવલિ;
  } ઢગલો[અંક_PRECS];
  પૂર્ણાંક sp;
  /* Location of the binary operator.  */
  location_t દ્વિઅંકી_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#define કાઢો_2								      \
  કરો {									      \
    પસંદગી (ઢગલો[sp].op)						      \
      {									      \
      સ્થિતિ TRUTH_ANDIF_પદાવલિ:						      \
	c_inhibit_evaluation_warnings -= (ઢગલો[sp - 1].પદાવલિ.કિંમત	      \
					  == truthvalue_false_ગાંઠ);	      \
	તોડો;								      \
      સ્થિતિ TRUTH_ORIF_પદાવલિ:						      \
	c_inhibit_evaluation_warnings -= (ઢગલો[sp - 1].પદાવલિ.કિંમત	      \
					  == truthvalue_true_ગાંઠ);	      \
	તોડો;								      \
      સ્થિતિ TRUNC_DIV_પદાવલિ:						      \
	જો ((ઢગલો[sp - 1].પદાવલિ.original_code == SIZEOF_પદાવલિ		      \
	     || ઢગલો[sp - 1].પદાવલિ.original_code == PAREN_SIZEOF_પદાવલિ)	      \
	    && (ઢગલો[sp].પદાવલિ.original_code == SIZEOF_પદાવલિ		      \
		|| ઢગલો[sp].પદાવલિ.original_code == PAREN_SIZEOF_પદાવલિ))	      \
	  {								      \
	    વૃક્ષ type0 = ઢગલો[sp - 1].sizeof_arg;			      \
	    વૃક્ષ type1 = ઢગલો[sp].sizeof_arg;				      \
	    વૃક્ષ first_arg = type0;					      \
	    જો (!TYPE_P (type0))					      \
	      type0 = વૃક્ષ_TYPE (type0);				      \
	    જો (!TYPE_P (type1))					      \
	      type1 = વૃક્ષ_TYPE (type1);				      \
	    જો (POINTER_TYPE_P (type0)					      \
		&& comptypes (વૃક્ષ_TYPE (type0), type1)			      \
		&& !(વૃક્ષ_CODE (first_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (first_arg)			      \
		     && warn_sizeof_array_argument))			      \
	      {								      \
		auto_diagnostic_group d;				      \
		જો (warning_at (ઢગલો[sp].loc, OPT_Wsizeof_pointer_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  જો (DECL_P (first_arg))				      \
		    inform (DECL_SOURCE_LOCATION (first_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    નહીંતર જો (વૃક્ષ_CODE (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (type0)))  \
		     && ઢગલો[sp].પદાવલિ.original_code != PAREN_SIZEOF_પદાવલિ)    \
	      maybe_warn_sizeof_array_div (ઢગલો[sp].loc, first_arg, type0,   \
					   ઢગલો[sp].sizeof_arg, type1);      \
	  }								      \
	તોડો;								      \
      મૂળભૂત:								      \
	તોડો;								      \
      }									      \
    ઢગલો[sp - 1].પદાવલિ							      \
      = convert_lvalue_to_rvalue (ઢગલો[sp - 1].loc,			      \
				  ઢગલો[sp - 1].પદાવલિ, સાચું, સાચું);	      \
    ઢગલો[sp].પદાવલિ							      \
      = convert_lvalue_to_rvalue (ઢગલો[sp].loc,			      \
				  ઢગલો[sp].પદાવલિ, સાચું, સાચું);		      \
    જો (UNLIKELY (omp_atomic_lhs != NULL_વૃક્ષ) && sp == 1		      \
	&& ((c_parser_next_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << ઢગલો[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_SHIFT)		      \
		     | (1 << PREC_ADD) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_next_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_ગાંઠ			      \
		     && c_parser_next_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (ઢગલો[sp].prec == PREC_REL || ઢગલો[sp].prec == PREC_EQ)))\
	&& ઢગલો[sp].op != TRUNC_MOD_પદાવલિ				      \
	&& ઢગલો[sp].op != GE_પદાવલિ					      \
	&& ઢગલો[sp].op != LE_પદાવલિ					      \
	&& ઢગલો[sp].op != NE_પદાવલિ					      \
	&& ઢગલો[0].પદાવલિ.કિંમત != error_mark_ગાંઠ			      \
	&& ઢગલો[1].પદાવલિ.કિંમત != error_mark_ગાંઠ			      \
	&& (omp_atomic_lhs == void_list_ગાંઠ				      \
	    || c_વૃક્ષ_equal (ઢગલો[0].પદાવલિ.કિંમત, omp_atomic_lhs)	      \
	    || c_વૃક્ષ_equal (ઢગલો[1].પદાવલિ.કિંમત, omp_atomic_lhs)	      \
	    || (ઢગલો[sp].op == EQ_પદાવલિ					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	વૃક્ષ t = make_ગાંઠ (ઢગલો[1].op);				      \
	વૃક્ષ_TYPE (t) = વૃક્ષ_TYPE (ઢગલો[0].પદાવલિ.કિંમત);		      \
	વૃક્ષ_OPERAND (t, 0) = ઢગલો[0].પદાવલિ.કિંમત;			      \
	વૃક્ષ_OPERAND (t, 1) = ઢગલો[1].પદાવલિ.કિંમત;			      \
	ઢગલો[0].પદાવલિ.કિંમત = t;					      \
	ઢગલો[0].પદાવલિ.m_decimal = 0;					      \
      }									      \
    નહીંતર								      \
      ઢગલો[sp - 1].પદાવલિ = parser_build_દ્વિઅંકી_op (ઢગલો[sp].loc,	      \
						   ઢગલો[sp].op,	      \
						   ઢગલો[sp - 1].પદાવલિ,	      \
						   ઢગલો[sp].પદાવલિ,	      \
						   ઢગલો[sp - 1].orig_પદાવલિ);  \
    ઢગલો[sp - 1].orig_પદાવલિ = NULL_વૃક્ષ;				      \
    sp--;								      \
  } જ્યારે (0)
  gcc_assert (!after || c_dialect_objc ());
  ઢગલો[0].loc = c_parser_peek_token (parser)->location;
  ઢગલો[0].પદાવલિ = c_parser_cast_expression (parser, after);
  ઢગલો[0].prec = PREC_NONE;
  ઢગલો[0].sizeof_arg = c_last_sizeof_arg;
  ઢગલો[0].orig_પદાવલિ = NULL_વૃક્ષ;
  sp = 0;
  જ્યારે (સાચું)
    {
      ગણના c_parser_prec oprec;
      ગણના વૃક્ષ_code ocode;
      source_range src_range;
      જો (parser->error)
	જાઓ out;
      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_PLUS:
	  oprec = PREC_ADD;
	  ocode = PLUS_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_MINUS:
	  oprec = PREC_ADD;
	  ocode = MINUS_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_LSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = LSHIFT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_RSHIFT:
	  oprec = PREC_SHIFT;
	  ocode = RSHIFT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = BIT_AND_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = BIT_XOR_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = BIT_IOR_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_પદાવલિ;
	  તોડો;
	મૂળભૂત:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  જાઓ out;
	}
      દ્વિઅંકી_loc = c_parser_peek_token (parser)->location;
      જ્યારે (oprec <= ઢગલો[sp].prec)
	કાઢો_2;
      c_parser_consume_token (parser);
      પસંદગી (ocode)
	{
	સ્થિતિ TRUTH_ANDIF_પદાવલિ:
	  src_range = ઢગલો[sp].પદાવલિ.src_range;
	  ઢગલો[sp].પદાવલિ
	    = convert_lvalue_to_rvalue (ઢગલો[sp].loc,
					ઢગલો[sp].પદાવલિ, સાચું, સાચું);
	  ઢગલો[sp].orig_પદાવલિ = ઢગલો[sp].પદાવલિ.કિંમત;
	  ઢગલો[sp].પદાવલિ.કિંમત = c_objc_common_truthvalue_conversion
	    (ઢગલો[sp].loc, default_conversion (ઢગલો[sp].પદાવલિ.કિંમત));
	  c_inhibit_evaluation_warnings += (ઢગલો[sp].પદાવલિ.કિંમત
					    == truthvalue_false_ગાંઠ);
	  set_c_પદાવલિ_source_range (&ઢગલો[sp].પદાવલિ, src_range);
	  તોડો;
	સ્થિતિ TRUTH_ORIF_પદાવલિ:
	  src_range = ઢગલો[sp].પદાવલિ.src_range;
	  ઢગલો[sp].પદાવલિ
	    = convert_lvalue_to_rvalue (ઢગલો[sp].loc,
					ઢગલો[sp].પદાવલિ, સાચું, સાચું);
	  ઢગલો[sp].orig_પદાવલિ = ઢગલો[sp].પદાવલિ.કિંમત;
	  ઢગલો[sp].પદાવલિ.કિંમત = c_objc_common_truthvalue_conversion
	    (ઢગલો[sp].loc, default_conversion (ઢગલો[sp].પદાવલિ.કિંમત));
	  c_inhibit_evaluation_warnings += (ઢગલો[sp].પદાવલિ.કિંમત
					    == truthvalue_true_ગાંઠ);
	  set_c_પદાવલિ_source_range (&ઢગલો[sp].પદાવલિ, src_range);
	  તોડો;
	મૂળભૂત:
	  તોડો;
	}
      sp++;
      ઢગલો[sp].loc = દ્વિઅંકી_loc;
      ઢગલો[sp].પદાવલિ = c_parser_cast_expression (parser, ખાલી);
      ઢગલો[sp].prec = oprec;
      ઢગલો[sp].op = ocode;
      ઢગલો[sp].sizeof_arg = c_last_sizeof_arg;
      ઢગલો[sp].orig_પદાવલિ = NULL_વૃક્ષ;
    }
 out:
  જ્યારે (sp > 0)
    કાઢો_2;
  પાછા ઢગલો[0].પદાવલિ;
#undef કાઢો_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

સ્થિર સંરચના c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  તાર્કિક seen_scspec = ખોટું;
  સંરચના c_declspecs *specs = build_null_declspecs ();
  જ્યારે (c_parser_next_token_is (parser, CPP_KEYWORD))
    {
      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_CONSTEXPR:
	સ્થિતિ RID_REGISTER:
	સ્થિતિ RID_STATIC:
	સ્થિતિ RID_THREAD:
	  seen_scspec = સાચું;
	  declspecs_add_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->કિંમત);
	  c_parser_consume_token (parser);
	  તોડો;
	મૂળભૂત:
	  જાઓ out;
	}
    }
 out:
  પાછા seen_scspec ? specs : ખાલી;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

સ્થિર સંરચના c_પદાવલિ
c_parser_cast_expression (c_parser *parser, સંરચના c_પદાવલિ *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  જો (after)
    પાછા c_parser_postfix_expression_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      સંરચના c_declspecs *scspecs;
      સંરચના c_type_name *type_name;
      સંરચના c_પદાવલિ ret;
      સંરચના c_પદાવલિ પદાવલિ;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, સાચું);
      parens.skip_until_found_close (parser);
      જો (type_name == ખાલી)
	{
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = ખાલી;
	  પાછા ret;
	}

      /* Save casted types in the function's used types hash table.  */
      used_types_ઉમેરો (type_name->specs->type);

      જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	પાછા c_parser_postfix_expression_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      જો (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      જો (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
	પદાવલિ = c_parser_cast_expression (parser, ખાલી);
	પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, સાચું, સાચું);
      }
      ret.કિંમત = c_cast_પદાવલિ (cast_loc, type_name, પદાવલિ.કિંમત);
      જો (ret.કિંમત && પદાવલિ.કિંમત)
	set_c_પદાવલિ_source_range (&ret, cast_loc, પદાવલિ.get_finish ());
      ret.original_code = ERROR_MARK;
      ret.original_type = ખાલી;
      ret.m_decimal = 0;
      પાછા ret;
    }
  નહીંતર
    પાછા c_parser_unary_expression (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

સ્થિર શૂન્ય
mark_exp_read_cond (વૃક્ષ exp)
{
  જો ((VAR_P (exp) || વૃક્ષ_CODE (exp) == PARM_DECL)
      && (VAR_P (exp) ? warn_unused_but_set_variable
		      : warn_unused_but_set_parameter) > 1)
    પાછા;

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

સ્થિર સંરચના c_પદાવલિ
c_parser_unary_expression (c_parser *parser)
{
  પૂર્ણાંક ext;
  સંરચના c_પદાવલિ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t finish;
  ret.original_code = ERROR_MARK;
  ret.original_type = ખાલી;
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ખાલી);
      mark_exp_read_cond (op.કિંમત);
      op = default_function_array_conversion (exp_loc, op);
      પાછા parser_build_unary_op (op_loc, PREINCREMENT_પદાવલિ, op);
    સ્થિતિ CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ખાલી);
      mark_exp_read_cond (op.કિંમત);
      op = default_function_array_conversion (exp_loc, op);
      પાછા parser_build_unary_op (op_loc, PREDECREMENT_પદાવલિ, op);
    સ્થિતિ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_expression (parser, ખાલી);
      mark_exp_read (op.કિંમત);
      પાછા parser_build_unary_op (op_loc, ADDR_પદાવલિ, op);
    સ્થિતિ CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_expression (parser, ખાલી);
	finish = op.get_finish ();
	op = convert_lvalue_to_rvalue (exp_loc, op, સાચું, સાચું);
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.કિંમત = build_indirect_ref (combined_loc, op.કિંમત, RO_UNARY_STAR);
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ret.m_decimal = 0;
	પાછા ret;
      }
    સ્થિતિ CPP_PLUS:
      જો (!c_dialect_objc () && !in_system_header_at (આગત_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ખાલી);
      op = convert_lvalue_to_rvalue (exp_loc, op, સાચું, સાચું);
      પાછા parser_build_unary_op (op_loc, CONVERT_પદાવલિ, op);
    સ્થિતિ CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ખાલી);
      op = convert_lvalue_to_rvalue (exp_loc, op, સાચું, સાચું);
      પાછા parser_build_unary_op (op_loc, NEGATE_પદાવલિ, op);
    સ્થિતિ CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ખાલી);
      op = convert_lvalue_to_rvalue (exp_loc, op, સાચું, સાચું);
      પાછા parser_build_unary_op (op_loc, BIT_NOT_પદાવલિ, op);
    સ્થિતિ CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_expression (parser, ખાલી);
      op = convert_lvalue_to_rvalue (exp_loc, op, સાચું, સાચું);
      પાછા parser_build_unary_op (op_loc, TRUTH_NOT_પદાવલિ, op);
    સ્થિતિ CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_NAME))
	{
	  ret.કિંમત = finish_label_address_પદાવલિ
	    (c_parser_peek_token (parser)->કિંમત, op_loc);
	  set_c_પદાવલિ_source_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_finish ());
	  c_parser_consume_token (parser);
	}
      નહીંતર
	{
	  c_parser_error (parser, "expected identifier");
	  ret.set_error ();
	}
      પાછા ret;
    સ્થિતિ CPP_KEYWORD:
      {
	ગણના rid rid = c_parser_peek_token (parser)->keyword;
	પસંદગી (rid)
	  {
	  સ્થિતિ RID_COUNTOF:
	  સ્થિતિ RID_SIZEOF:
	    પાછા c_parser_sizeof_or_countof_expression (parser, rid);
	  સ્થિતિ RID_ALIGNOF:
	    પાછા c_parser_alignof_expression (parser);
	  સ્થિતિ RID_MAXOF:
	  સ્થિતિ RID_MINOF:
	    પાછા c_parser_maxof_or_minof_expression (parser, rid);
	  સ્થિતિ RID_BUILTIN_HAS_ATTRIBUTE:
	    પાછા c_parser_has_attribute_expression (parser);
	  સ્થિતિ RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_expression (parser, ખાલી);
	    restore_extension_diagnostics (ext);
	    પાછા ret;
	  સ્થિતિ RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, ખાલી);
	    op = default_function_array_conversion (exp_loc, op);
	    પાછા parser_build_unary_op (op_loc, REALPART_પદાવલિ, op);
	  સ્થિતિ RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_expression (parser, ખાલી);
	    op = default_function_array_conversion (exp_loc, op);
	    પાછા parser_build_unary_op (op_loc, IMAGPART_પદાવલિ, op);
	  સ્થિતિ RID_TRANSACTION_ATOMIC:
	  સ્થિતિ RID_TRANSACTION_RELAXED:
	    પાછા c_parser_transaction_expression (parser, rid);
	  સ્થિતિ RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.કિંમત = void_ગાંઠ;
	    set_c_પદાવલિ_source_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    પાછા ret;
	  મૂળભૂત:
	    પાછા c_parser_postfix_expression (parser);
	  }
      }
    મૂળભૂત:
      પાછા c_parser_postfix_expression (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

સ્થિર સંરચના c_પદાવલિ
c_parser_sizeof_or_countof_expression (c_parser *parser, ગણના rid rid)
{
  અચલ અક્ષર *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  સંરચના c_પદાવલિ પદાવલિ;
  સંરચના c_પદાવલિ result;
  location_t પદાવલિ_loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  જો (rid == RID_COUNTOF)
    pedwarn_c23 (start, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  જો (rid == RID_COUNTOF)
    in_countof++;
  નહીંતર
    in_sizeof++;
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      સંરચના c_declspecs *scspecs;
      સંરચના c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      પદાવલિ_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, સાચું);
      parens.skip_until_found_close (parser);
      finish = parser->tokens_buf[0].location;
      જો (type_name == ખાલી)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  પદાવલિ.set_error ();
	  જાઓ Xof_પદાવલિ;
	}
      જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  પદાવલિ = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       પદાવલિ_loc);
	  finish = પદાવલિ.get_finish ();
	  જાઓ Xof_પદાવલિ;
	}
      /* sizeof ( type-name ).  */
      જો (scspecs)
	error_at (પદાવલિ_loc, "storage class specifier in %qs", op_name);
      જો (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      જો (rid == RID_COUNTOF)
	{
	  in_countof--;
	  result = c_પદાવલિ_countof_type (પદાવલિ_loc, type_name);
	}
      નહીંતર
	{
	  in_sizeof--;
	  result = c_પદાવલિ_sizeof_type (પદાવલિ_loc, type_name);
	}
    }
  નહીંતર
    {
      પદાવલિ_loc = c_parser_peek_token (parser)->location;
      પદાવલિ = c_parser_unary_expression (parser);
      finish = પદાવલિ.get_finish ();
    Xof_પદાવલિ:
      c_inhibit_evaluation_warnings--;
      જો (rid == RID_COUNTOF)
	in_countof--;
      નહીંતર
	in_sizeof--;
      mark_exp_read (પદાવલિ.કિંમત);
      જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (વૃક્ષ_OPERAND (પદાવલિ.કિંમત, 1)))
	error_at (પદાવલિ_loc, "%qs applied to a bit-field", op_name);
      જો (rid == RID_COUNTOF)
	result = c_પદાવલિ_countof_પદાવલિ (પદાવલિ_loc, પદાવલિ);
      નહીંતર
	result = c_પદાવલિ_sizeof_પદાવલિ (પદાવલિ_loc, પદાવલિ);
    }
  જો (finish == UNKNOWN_LOCATION)
    finish = start;
  set_c_પદાવલિ_source_range (&result, start, finish);
  પાછા result;
}

/* Parse an alignof expression.  */

સ્થિર સંરચના c_પદાવલિ
c_parser_alignof_expression (c_parser *parser)
{
  સંરચના c_પદાવલિ પદાવલિ;
  location_t start_loc = c_parser_peek_token (parser)->location;
  location_t end_loc;
  વૃક્ષ alignof_spelling = c_parser_peek_token (parser)->કિંમત;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_ALIGNOF));
  તાર્કિક is_c11_alignof = (strcmp (IDENTIFIER_POINTER (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_POINTER (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  જો (is_c11_alignof)
    {
      જો (flag_isoc99)
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      નહીંતર
	pedwarn_c99 (start_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  in_alignof++;
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      સંરચના c_declspecs *scspecs;
      સંરચના c_type_name *type_name;
      સંરચના c_પદાવલિ ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, સાચું);
      end_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
      જો (type_name == ખાલી)
	{
	  સંરચના c_પદાવલિ ret;
	  c_inhibit_evaluation_warnings--;
	  in_alignof--;
	  ret.set_error ();
	  ret.original_code = ERROR_MARK;
	  ret.original_type = ખાલી;
	  પાછા ret;
	}
      જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  પદાવલિ = c_parser_postfix_expression_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  જાઓ alignof_પદાવલિ;
	}
      /* alignof ( type-name ).  */
      જો (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      જો (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      ret.કિંમત = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       ખાલી, ખાલી),
					    ખોટું, is_c11_alignof, 1);
      ret.original_code = ERROR_MARK;
      ret.original_type = ખાલી;
      set_c_પદાવલિ_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      પાછા ret;
    }
  નહીંતર
    {
      સંરચના c_પદાવલિ ret;
      પદાવલિ = c_parser_unary_expression (parser);
      end_loc = પદાવલિ.src_range.m_finish;
    alignof_પદાવલિ:
      mark_exp_read (પદાવલિ.કિંમત);
      c_inhibit_evaluation_warnings--;
      in_alignof--;
      જો (is_c11_alignof)
	pedwarn (start_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.કિંમત = c_alignof_પદાવલિ (start_loc, પદાવલિ.કિંમત);
      ret.original_code = ERROR_MARK;
      ret.original_type = ખાલી;
      set_c_પદાવલિ_source_range (&ret, start_loc, end_loc);
      ret.m_decimal = 0;
      પાછા ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

સ્થિર સંરચના c_પદાવલિ
c_parser_maxof_or_minof_expression (c_parser *parser, ગણના rid rid)
{
  અચલ અક્ષર *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  સંરચના c_પદાવલિ result;
  location_t પદાવલિ_loc;
  સંરચના c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_next_token_is_keyword (parser, rid));

  location_t start;
  location_t finish = UNKNOWN_LOCATION;

  start = c_parser_peek_token (parser)->location;

  pedwarn (start, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  જો (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      જાઓ fail;
    }
  parens.consume_open (parser);
  પદાવલિ_loc = c_parser_peek_token (parser)->location;
  જો (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (પદાવલિ_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_found_close (parser);
      જાઓ fail;
    }
  type_name = c_parser_type_name (parser, સાચું);
  જો (type_name == ખાલી)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_found_close (parser);
      જાઓ fail;
    }
  parens.skip_until_found_close (parser);
  finish = parser->tokens_buf[0].location;
  જો (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  જો (rid == RID_MAXOF)
    result = c_પદાવલિ_maxof_type (પદાવલિ_loc, type_name);
  નહીંતર
    result = c_પદાવલિ_minof_type (પદાવલિ_loc, type_name);
  set_c_પદાવલિ_source_range (&result, start, finish);
  પાછા result;
fail:
  c_inhibit_evaluation_warnings--;
  result.set_error ();
  result.original_code = ERROR_MARK;
  result.original_type = ખાલી;
  પાછા result;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

સ્થિર સંરચના c_પદાવલિ
c_parser_has_attribute_expression (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t start = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  જો (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      in_typeof--;

      સંરચના c_પદાવલિ result;
      result.set_error ();
      result.original_code = ERROR_MARK;
      result.original_type = ખાલી;
      પાછા result;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  in_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  વૃક્ષ oper = NULL_વૃક્ષ;
  જો (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      સંરચના c_type_name *tname = c_parser_type_name (parser);
      in_typeof--;
      જો (tname)
	{
	  oper = groktypename (tname, ખાલી, ખાલી);
	  કાઢો_maybe_used (c_type_variably_modified_p (oper));
	}
    }
  નહીંતર
    {
      સંરચના c_પદાવલિ cexpr = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      c_inhibit_evaluation_warnings--;
      in_typeof--;
      જો (cexpr.કિંમત != error_mark_ગાંઠ)
	{
	  mark_exp_read (cexpr.કિંમત);
	  oper = cexpr.કિંમત;
	  વૃક્ષ etype = વૃક્ષ_TYPE (oper);
	  તાર્કિક was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  જો (was_vm)
	    oper = c_fully_fold (oper, ખોટું, ખાલી);
	  કાઢો_maybe_used (was_vm);
	}
    }

  સંરચના c_પદાવલિ result;
  result.original_code = ERROR_MARK;
  result.original_type = ખાલી;

  જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      result.set_error ();
      પાછા result;
    }

  તાર્કિક save_translate_strings_p = parser->translate_strings_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  વૃક્ષ attr = c_parser_gnu_attribute (parser, NULL_વૃક્ષ, ખોટું, ખોટું);

  parser->translate_strings_p = save_translate_strings_p;

  location_t finish = c_parser_peek_token (parser)->location;
  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  નહીંતર
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);

      result.set_error ();
      પાછા result;
    }

  જો (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      result.set_error ();
      પાછા result;
    }

  result.original_code = INTEGER_CST;
  result.original_type = boolean_type_ગાંઠ;

  જો (has_attribute (atloc, oper, attr, default_conversion))
    result.કિંમત = boolean_true_ગાંઠ;
  નહીંતર
    result.કિંમત =  boolean_false_ગાંઠ;

  set_c_પદાવલિ_source_range (&result, start, finish);
  result.m_decimal = 0;
  પાછા result;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
સ્થિર તાર્કિક
c_parser_get_builtin_args (c_parser *parser, અચલ અક્ષર *bname,
			   vec<c_પદાવલિ_t, va_gc> **ret_cexpr_list,
			   તાર્કિક choose_પદાવલિ_p,
			   location_t *out_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_પદાવલિ_t, va_gc> *cexpr_list;
  c_પદાવલિ_t પદાવલિ;
  તાર્કિક saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = ખાલી;
  જો (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      પાછા ખોટું;
    }

  c_parser_consume_token (parser);

  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      *out_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      પાછા સાચું;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= choose_પદાવલિ_p;
  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_safe_ધકેલો (cexpr_list, પદાવલિ);
  જ્યારે (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  વૃક્ષ કિંમત = embed->કિંમત;
	  પદાવલિ.original_code = INTEGER_CST;
	  પદાવલિ.original_type = integer_type_ગાંઠ;
	  પદાવલિ.કિંમત = NULL_વૃક્ષ;
	  set_c_પદાવલિ_source_range (&પદાવલિ, embed->get_range ());
	  પદાવલિ.m_decimal = 0;
	  માટે (unsigned પૂર્ણાંક i = 0; i < (unsigned) RAW_DATA_LENGTH (કિંમત); i++)
	    {
	      પદાવલિ.કિંમત = build_int_cst (integer_type_ગાંઠ,
					  RAW_DATA_UCHAR_ELT (કિંમત, i));
	      vec_safe_ધકેલો (cexpr_list, પદાવલિ);
	    }
	  c_parser_consume_token (parser);
	  ચાલુ;
	}
      પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      vec_safe_ધકેલો (cexpr_list, પદાવલિ);
    }

  *out_close_paren_loc = c_parser_peek_token (parser)->location;
  જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    પાછા ખોટું;

  *ret_cexpr_list = cexpr_list;
  પાછા સાચું;
}

/* This represents a single generic-association.  */

સંરચના c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  વૃક્ષ type;
  /* The association's expression.  */
  સંરચના c_પદાવલિ expression;
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

સ્થિર સંરચના c_પદાવલિ
c_parser_generic_selection (c_parser *parser)
{
  સંરચના c_પદાવલિ selector, error_પદાવલિ;
  વૃક્ષ selector_type;
  સંરચના c_generic_association matched_assoc;
  પૂર્ણાંક match_found = -1;
  location_t generic_loc, selector_loc;

  error_પદાવલિ.original_code = ERROR_MARK;
  error_પદાવલિ.original_type = ખાલી;
  error_પદાવલિ.set_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_વૃક્ષ;
  matched_assoc.expression = error_પદાવલિ;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  જો (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  નહીંતર
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા error_પદાવલિ;

  selector_loc = c_parser_peek_token (parser)->location;
  જો (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      સંરચના c_type_name *type = c_parser_type_name (parser);
      જો (type)
	selector_type = groktypename (type, ખાલી, ખાલી);
      c_inhibit_evaluation_warnings--;
      જો (!type)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	  પાછા error_પદાવલિ;
	}
    }
  નહીંતર
    {
      c_inhibit_evaluation_warnings++;
      in_generic++;
      selector = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      in_generic--;
      કાઢો_maybe_used (!flag_isoc23);

      જો (selector.કિંમત == error_mark_ગાંઠ)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	  પાછા selector;
	}
      mark_exp_read (selector.કિંમત);
      selector_type = વૃક્ષ_TYPE (selector.કિંમત);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      જો (વૃક્ષ_CODE (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      જો (FUNCTION_POINTER_TYPE_P (selector_type)
	  && TYPE_QUALS (વૃક્ષ_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_pointer_type (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (selector_type)));
    }

  જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
      પાછા error_પદાવલિ;
    }

  auto_vec<c_generic_association> associations;
  સંરચના maybe_used_decl *maybe_used_default = ખાલી;
  જ્યારે (1)
    {
      સંરચના c_generic_association assoc, *iter;
      unsigned પૂર્ણાંક ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      જો (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_વૃક્ષ;
	}
      નહીંતર
	{
	  સંરચના c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  જો (type_name == ખાલી)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	      પાછા error_પદાવલિ;
	    }
	  assoc.type = grokgenassoc (type_name);
	  જો (assoc.type == error_mark_ગાંઠ)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	      પાછા error_પદાવલિ;
	    }

	  જો (વૃક્ષ_CODE (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  નહીંતર જો (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  જો (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	  પાછા error_પદાવલિ;
	}

      તાર્કિક match = assoc.type == NULL_વૃક્ષ
		   || comptypes (assoc.type, selector_type);

      જો (!match || matched_assoc.type != NULL_વૃક્ષ)
	c_inhibit_evaluation_warnings++;
      in_generic++;

      assoc.expression = c_parser_પદાવલિ_no_commas (parser, ખાલી);

      જો (!match || matched_assoc.type != NULL_વૃક્ષ)
	c_inhibit_evaluation_warnings--;
      in_generic--;
      જો (!match)
	કાઢો_maybe_used (!flag_isoc23);
      નહીંતર જો (assoc.type == NULL_વૃક્ષ)
	maybe_used_default = save_maybe_used ();
      નહીંતર
	કાઢો_maybe_used (સાચું);

      જો (assoc.expression.કિંમત == error_mark_ગાંઠ)
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	  પાછા error_પદાવલિ;
	}

      માટે (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  જો (assoc.type == NULL_વૃક્ષ)
	    {
	      જો (iter->type == NULL_વૃક્ષ)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  નહીંતર જો (iter->type != NULL_વૃક્ષ)
	    {
	      જો (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      જો (assoc.type == NULL_વૃક્ષ)
	{
	  જો (match_found < 0)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	}
      નહીંતર જો (match)
	{
	  જો (match_found < 0 || matched_assoc.type == NULL_વૃક્ષ)
	    {
	      matched_assoc = assoc;
	      match_found = associations.length ();
	    }
	  નહીંતર
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.safe_ધકેલો (assoc);

      જો (c_parser_peek_token (parser)->type != CPP_COMMA)
	તોડો;
      c_parser_consume_token (parser);
    }

  જો (match_found >= 0 && matched_assoc.type == NULL_વૃક્ષ)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_used (maybe_used_default);
      કાઢો_maybe_used (સાચું);
    }
  નહીંતર જો (maybe_used_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_used (maybe_used_default);
      કાઢો_maybe_used (!flag_isoc23);
    }

  unsigned પૂર્ણાંક ix;
  સંરચના c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    જો (ix != (unsigned) match_found)
      mark_exp_read (iter->expression.કિંમત);

  જો (!parens.require_close (parser))
    {
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
      પાછા error_પદાવલિ;
    }

  જો (match_found < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      પાછા error_પદાવલિ;
    }

  પાછા matched_assoc.expression;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

સ્થિર unsigned પૂર્ણાંક
check_tgmath_function (c_પદાવલિ *પદાવલિ, unsigned પૂર્ણાંક pos)
{
  વૃક્ષ type = વૃક્ષ_TYPE (પદાવલિ->કિંમત);
  જો (!FUNCTION_POINTER_TYPE_P (type))
    {
      error_at (પદાવલિ->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      પાછા 0;
    }
  type = વૃક્ષ_TYPE (type);
  જો (!prototype_p (type))
    {
      error_at (પદાવલિ->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      પાછા 0;
    }
  જો (stdarg_p (type))
    {
      error_at (પદાવલિ->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      પાછા 0;
    }
  unsigned પૂર્ણાંક nargs = 0;
  function_args_iterator iter;
  વૃક્ષ t;
  FOREACH_FUNCTION_ARGS (type, t, iter)
    {
      જો (t == void_type_ગાંઠ)
	તોડો;
      nargs++;
    }
  જો (nargs == 0)
    {
      error_at (પદાવલિ->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      પાછા 0;
    }
  પાછા nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
ગણના tgmath_parm_kind
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

સ્થિર સંરચના c_પદાવલિ
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  પસંદગી (c_parser_peek_token (parser)->keyword)
    {
    સ્થિતિ RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      તોડો;
    સ્થિતિ RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      તોડો;
    સ્થિતિ RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      તોડો;
    મૂળભૂત:
      gcc_unreachable ();
    }

  સંરચના c_પદાવલિ પદાવલિ;
  પદાવલિ.original_code = ERROR_MARK;
  પદાવલિ.original_type = ખાલી;
  પદાવલિ.કિંમત = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->કિંમત);
  set_c_પદાવલિ_source_range (&પદાવલિ, loc, loc);
  પદાવલિ.m_decimal = 0;
  c_parser_consume_token (parser);
  પાછા પદાવલિ;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

સ્થિર તાર્કિક
has_counted_by_object (વૃક્ષ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  જો ((વૃક્ષ_CODE (ref) == INDIRECT_REF
       && is_access_with_size_p (વૃક્ષ_OPERAND (ref, 0)))
      || is_access_with_size_p (ref))
    પાછા સાચું;
  પાછા ખોટું;
}

/* Get the reference to the counted-by object associated with the REF.  */

સ્થિર વૃક્ષ
get_counted_by_ref (વૃક્ષ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  જો (વૃક્ષ_CODE (ref) == INDIRECT_REF
      && is_access_with_size_p (વૃક્ષ_OPERAND (ref, 0)))
    પાછા CALL_પદાવલિ_ARG (વૃક્ષ_OPERAND (ref, 0), 1);
  નહીંતર જો (is_access_with_size_p (ref))
    પાછા CALL_પદાવલિ_ARG (ref, 1);

  પાછા NULL_વૃક્ષ;
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

સ્થિર સંરચના c_પદાવલિ
c_parser_postfix_expression (c_parser *parser)
{
  સંરચના c_પદાવલિ પદાવલિ, e1;
  સંરચના c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  પદાવલિ.original_code = ERROR_MARK;
  પદાવલિ.original_type = ખાલી;
  પદાવલિ.m_decimal = 0;
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_સંખ્યા:
      પદાવલિ.કિંમત = c_parser_peek_token (parser)->કિંમત;
      set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      પદાવલિ.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == FIXED_CST
	  && !targetm.fixed_point_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  પદાવલિ.set_error ();
	}
      તોડો;
    સ્થિતિ CPP_CHAR:
    સ્થિતિ CPP_CHAR16:
    સ્થિતિ CPP_CHAR32:
    સ્થિતિ CPP_UTF8CHAR:
    સ્થિતિ CPP_WCHAR:
      પદાવલિ.કિંમત = c_parser_peek_token (parser)->કિંમત;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      પદાવલિ.original_type = char_type_ગાંઠ;
      set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
      c_parser_consume_token (parser);
      તોડો;
    સ્થિતિ CPP_STRING:
    સ્થિતિ CPP_STRING16:
    સ્થિતિ CPP_STRING32:
    સ્થિતિ CPP_WSTRING:
    સ્થિતિ CPP_UTF8STRING:
      પદાવલિ = c_parser_string_literal (parser, parser->translate_strings_p,
				      સાચું);
      તોડો;
    સ્થિતિ CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      પદાવલિ.કિંમત
	= objc_build_string_object (c_parser_peek_token (parser)->કિંમત);
      set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
      c_parser_consume_token (parser);
      તોડો;
    સ્થિતિ CPP_NAME:
      પસંદગી (c_parser_peek_token (parser)->id_kind)
	{
	સ્થિતિ C_ID_ID:
	  {
	    વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
	    c_parser_consume_token (parser);
	    પદાવલિ.કિંમત = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &પદાવલિ.original_type);
	    set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
	    તોડો;
	  }
	સ્થિતિ C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    વૃક્ષ class_name = c_parser_peek_token (parser)->કિંમત;
	    વૃક્ષ component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    જો (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		પદાવલિ.set_error ();
		તોડો;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->કિંમત;
	    location_t end_loc = component_tok->get_finish ();
	    c_parser_consume_token (parser);
	    પદાવલિ.કિંમત = objc_build_class_component_ref (class_name,
							 component);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, end_loc);
	    તોડો;
	  }
	મૂળભૂત:
	  c_parser_error (parser, "expected expression");
	  પદાવલિ.set_error ();
	  તોડો;
	}
      તોડો;
    સ્થિતિ CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      જો (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  વૃક્ષ stmt;
	  location_t brace_loc;
	  તાર્કિક save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  જો (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = સાચું;
	      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ખાલી);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	      પદાવલિ.set_error ();
	      તોડો;
	    }
	  c_omp_array_section_p = ખોટું;
	  stmt = c_begin_stmt_પદાવલિ ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  પદાવલિ.કિંમત = c_finish_stmt_પદાવલિ (brace_loc, stmt);
	  set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_loc);
	  mark_exp_read (પદાવલિ.કિંમત);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      નહીંતર
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  પદાવલિ = c_parser_expression (parser);
	  જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == MODIFY_પદાવલિ)
	    suppress_warning (પદાવલિ.કિંમત, OPT_Wparentheses);
	  જો (પદાવલિ.original_code != C_MAYBE_CONST_પદાવલિ
	      && પદાવલિ.original_code != SIZEOF_પદાવલિ)
	    પદાવલિ.original_code = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  જો (પદાવલિ.original_code == SIZEOF_પદાવલિ)
	    પદાવલિ.original_code = PAREN_SIZEOF_પદાવલિ;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  set_c_પદાવલિ_source_range (&પદાવલિ, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      તોડો;
    સ્થિતિ CPP_KEYWORD:
      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_FUNCTION_NAME:
	સ્થિતિ RID_PRETTY_FUNCTION_NAME:
	સ્થિતિ RID_C99_FUNCTION_NAME:
	  પદાવલિ = c_parser_predefined_identifier (parser);
	  તોડો;
	સ્થિતિ RID_VA_ARG:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    e1 = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	    mark_exp_read (e1.કિંમત);
	    e1.કિંમત = c_fully_fold (e1.કિંમત, ખોટું, ખાલી);
	    જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    જો (t1 == ખાલી)
	      {
		પદાવલિ.set_error ();
	      }
	    નહીંતર
	      {
		વૃક્ષ type_પદાવલિ = NULL_વૃક્ષ;
		વૃક્ષ type = groktypename (t1, &type_પદાવલિ, ખાલી);
		પદાવલિ.કિંમત = c_build_va_arg (start_loc, e1.કિંમત, loc,
					     type, type_પદાવલિ);
		set_c_પદાવલિ_source_range (&પદાવલિ, start_loc, end_loc);
	      }
	  }
	  તોડો;
	સ્થિતિ RID_C23_VA_START:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    e1 = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	    e1 = convert_lvalue_to_rvalue (e1.get_location (), e1, સાચું, સાચું);
	    જો (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
		    પદાવલિ.set_error ();
		    તોડો;
		  }
		જો (c_parser_next_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_kind == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    વૃક્ષ name = c_parser_peek_token (parser)->કિંમત;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    વૃક્ષ decl = lookup_name (name);
		    વૃક્ષ last_parm
		      = વૃક્ષ_last (DECL_ARGUMENTS (current_function_decl));
		    જો (!last_parm || decl != last_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    નહીંતર જો (DECL_REGISTER (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		નહીંતર
		  {
		    unsigned nesting_depth = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    જ્યારે (સાચું)
		      {
			c_token *token = c_parser_peek_token (parser);
			જો (token->type == CPP_CLOSE_PAREN && !nesting_depth)
			  તોડો;

			જો (token->type == CPP_EOF)
			  તોડો;
			જો (token->type == CPP_OPEN_PAREN)
			  ++nesting_depth;
			નહીંતર જો (token->type == CPP_CLOSE_PAREN)
			  --nesting_depth;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    જો (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_found_close (parser);
	    વૃક્ષ fndecl = builtin_decl_explicit (BUILT_IN_VA_START);
	    vec<વૃક્ષ, va_gc> *params;
	    vec_alloc (params, 2);
	    params->quick_ધકેલો (e1.કિંમત);
	    params->quick_ધકેલો (integer_zero_ગાંઠ);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.quick_ધકેલો (e1.get_location ());
	    arg_loc.quick_ધકેલો (UNKNOWN_LOCATION);
	    પદાવલિ.કિંમત = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, ખાલી);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc,
				     parser->tokens_buf[0].get_finish ());
	    પદાવલિ.m_decimal = 0;
	    પદાવલિ.original_code = ERROR_MARK;
	    પદાવલિ.original_type = ખાલી;
	    release_વૃક્ષ_vector (params);
	    તોડો;
	  }
	સ્થિતિ RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    t1 = c_parser_type_name (parser);
	    જો (t1 == ખાલી)
	      parser->error = સાચું;
	    જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    જો (parser->error)
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    વૃક્ષ type = groktypename (t1, ખાલી, ખાલી);
	    વૃક્ષ offsetof_ref;
	    જો (type == error_mark_ગાંઠ)
	      offsetof_ref = error_mark_ગાંઠ;
	    નહીંતર
	      {
		offsetof_ref = build1 (INDIRECT_REF, type, null_pointer_ગાંઠ);
		SET_પદાવલિ_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    જો (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->કિંમત,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		જ્યારે (c_parser_next_token_is (parser, CPP_DOT)
		       || c_parser_next_token_is (parser,
						  CPP_OPEN_SQUARE)
		       || c_parser_next_token_is (parser,
						  CPP_DEREF))
		  {
		    જો (c_parser_next_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_ગાંઠ);
			જાઓ do_dot;
		      }
		    નહીંતર જો (c_parser_next_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			જો (c_parser_next_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    તોડો;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->કિંમત,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    નહીંતર
		      {
			સંરચના c_પદાવલિ ce;
			વૃક્ષ idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_expression (parser);
			ce = convert_lvalue_to_rvalue (loc, ce, ખોટું, ખોટું);
			idx = ce.કિંમત;
			idx = c_fully_fold (idx, ખોટું, ખાલી);
			c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    નહીંતર
	      c_parser_error (parser, "expected identifier");
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    પદાવલિ.કિંમત = fold_offsetof (offsetof_ref);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, end_loc);
	  }
	  તોડો;
	સ્થિતિ RID_CHOOSE_પદાવલિ:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    c_પદાવલિ_t *e1_p, *e2_p, *e3_p;
	    વૃક્ષ c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, સાચું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }

	    જો (vec_safe_length (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->કિંમત;
	    mark_exp_read (e2_p->કિંમત);
	    mark_exp_read (e3_p->કિંમત);
	    જો (વૃક્ષ_CODE (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_expression_warning (c);
	    પદાવલિ = integer_zerop (c) ? *e3_p : *e2_p;
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    તોડો;
	  }
	સ્થિતિ RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    t1 = c_parser_type_name (parser);
	    જો (t1 == ખાલી)
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    t2 = c_parser_type_name (parser);
	    જો (t2 == ખાલી)
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    વૃક્ષ e1, e2;
	    e1 = groktypename (t1, ખાલી, ખાલી);
	    e2 = groktypename (t2, ખાલી, ખાલી);
	    જો (e1 == error_mark_ગાંઠ || e2 == error_mark_ગાંઠ)
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    પદાવલિ.કિંમત
	      = comptypes (e1, e2) ? integer_one_ગાંઠ : integer_zero_ગાંઠ;
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	  }
	  તોડો;
	સ્થિતિ RID_BUILTIN_TGMATH:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser,
					    "__builtin_tgmath",
					    &cexpr_list, ખોટું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }

	    જો (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    unsigned પૂર્ણાંક i;
	    c_પદાવલિ_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, સાચું, સાચું);
	    unsigned પૂર્ણાંક nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    જો (nargs == 0)
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (vec_safe_length (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		પદાવલિ.set_error ();
		તોડો;
	      }
	    unsigned પૂર્ણાંક અંક_functions = vec_safe_length (cexpr_list) - nargs;
	    જો (અંક_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    માટે (unsigned પૂર્ણાંક j = 1; j < અંક_functions; j++)
	      {
		unsigned પૂર્ણાંક this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		જો (this_nargs == 0)
		  {
		    પદાવલિ.set_error ();
		    જાઓ out;
		  }
		જો (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    પદાવલિ.set_error ();
		    જાઓ out;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<ગણના tgmath_parm_kind> parm_kind (nargs + 1);
	    auto_vec<વૃક્ષ> parm_first (nargs + 1);
	    auto_vec<તાર્કિક> parm_complex (nargs + 1);
	    auto_vec<તાર્કિક> parm_varies (nargs + 1);
	    વૃક્ષ first_type = વૃક્ષ_TYPE (વૃક્ષ_TYPE ((*cexpr_list)[0].કિંમત));
	    વૃક્ષ first_ret = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (first_type));
	    parm_first.quick_ધકેલો (first_ret);
	    parm_complex.quick_ધકેલો (વૃક્ષ_CODE (first_ret) == COMPLEX_TYPE);
	    parm_varies.quick_ધકેલો (ખોટું);
	    function_args_iterator iter;
	    વૃક્ષ t;
	    unsigned પૂર્ણાંક argpos;
	    FOREACH_FUNCTION_ARGS (first_type, t, iter)
	      {
		જો (t == void_type_ગાંઠ)
		  તોડો;
		parm_first.quick_ધકેલો (TYPE_MAIN_VARIANT (t));
		parm_complex.quick_ધકેલો (વૃક્ષ_CODE (t) == COMPLEX_TYPE);
		parm_varies.quick_ધકેલો (ખોટું);
	      }
	    માટે (unsigned પૂર્ણાંક j = 1; j < અંક_functions; j++)
	      {
		વૃક્ષ type = વૃક્ષ_TYPE (વૃક્ષ_TYPE ((*cexpr_list)[j].કિંમત));
		વૃક્ષ ret = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (type));
		જો (ret != parm_first[0])
		  {
		    parm_varies[0] = સાચું;
		    જો (!SCALAR_FLOAT_TYPE_P (parm_first[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_first[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		    જો (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		  }
		જો (વૃક્ષ_CODE (ret) == COMPLEX_TYPE)
		  parm_complex[0] = સાચું;
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    જો (t == void_type_ગાંઠ)
		      તોડો;
		    t = TYPE_MAIN_VARIANT (t);
		    જો (t != parm_first[argpos])
		      {
			parm_varies[argpos] = સાચું;
			જો (!SCALAR_FLOAT_TYPE_P (parm_first[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_first[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    પદાવલિ.set_error ();
			    જાઓ out;
			  }
			જો (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    પદાવલિ.set_error ();
			    જાઓ out;
			  }
		      }
		    જો (વૃક્ષ_CODE (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = સાચું;
		    argpos++;
		  }
	      }
	    ગણના tgmath_parm_kind max_variation = tgmath_fixed;
	    માટે (unsigned પૂર્ણાંક j = 0; j <= nargs; j++)
	      {
		ગણના tgmath_parm_kind this_kind;
		જો (parm_varies[j])
		  {
		    જો (parm_complex[j])
		      max_variation = this_kind = tgmath_complex;
		    નહીંતર
		      {
			this_kind = tgmath_real;
			જો (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		નહીંતર
		  this_kind = tgmath_fixed;
		parm_kind.quick_ધકેલો (this_kind);
	      }
	    જો (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    unsigned પૂર્ણાંક tgarg = 0;
	    માટે (unsigned પૂર્ણાંક j = 1; j <= nargs; j++)
	      જો (parm_kind[j] == max_variation)
		{
		  tgarg = j;
		  તોડો;
		}
	    જો (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<વૃક્ષ> tg_type (અંક_functions);
	    માટે (unsigned પૂર્ણાંક j = 0; j < અંક_functions; j++)
	      {
		વૃક્ષ type = વૃક્ષ_TYPE (વૃક્ષ_TYPE ((*cexpr_list)[j].કિંમત));
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    જો (argpos == tgarg)
		      {
			tg_type.quick_ધકેલો (TYPE_MAIN_VARIANT (t));
			તોડો;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    તાર્કિક all_complex = સાચું;
	    તાર્કિક all_દ્વિઅંકી = સાચું;
	    તાર્કિક all_decimal = સાચું;
	    hash_set<વૃક્ષ> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		જો (વૃક્ષ_CODE (t) == COMPLEX_TYPE)
		  all_decimal = ખોટું;
		નહીંતર
		  {
		    all_complex = ખોટું;
		    જો (DECIMAL_FLOAT_TYPE_P (t))
		      all_દ્વિઅંકી = ખોટું;
		    નહીંતર
		      all_decimal = ખોટું;
		  }
		જો (tg_types.add (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    પદાવલિ.set_error ();
		    જાઓ out;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    માટે (unsigned પૂર્ણાંક j = 0; j < અંક_functions; j++)
	      {
		વૃક્ષ exp_type = tg_type[j];
		વૃક્ષ exp_real_type = exp_type;
		જો (વૃક્ષ_CODE (exp_type) == COMPLEX_TYPE)
		  exp_real_type = વૃક્ષ_TYPE (exp_type);
		વૃક્ષ type = વૃક્ષ_TYPE (વૃક્ષ_TYPE ((*cexpr_list)[j].કિંમત));
		વૃક્ષ ret = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (type));
		જો ((parm_kind[0] == tgmath_complex && ret != exp_type)
		    || (parm_kind[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    પદાવલિ.set_error ();
		    જાઓ out;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ARGS (type, t, iter)
		  {
		    જો (t == void_type_ગાંઠ)
		      તોડો;
		    t = TYPE_MAIN_VARIANT (t);
		    જો ((parm_kind[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_kind[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			પદાવલિ.set_error ();
			જાઓ out;
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
	    તાર્કિક arg_complex = all_complex;
	    તાર્કિક arg_દ્વિઅંકી = all_દ્વિઅંકી;
	    તાર્કિક arg_int_decimal = all_decimal;
	    તાર્કિક arg_int_floatnx = ખોટું;
	    તાર્કિક arg_int_decimalx = ખોટું;
	    માટે (unsigned પૂર્ણાંક j = 1; j <= nargs; j++)
	      {
		જો (parm_kind[j] == tgmath_fixed)
		  ચાલુ;
		c_પદાવલિ_t *ce = &(*cexpr_list)[અંક_functions + j - 1];
		વૃક્ષ type = વૃક્ષ_TYPE (ce->કિંમત);
		જો (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && વૃક્ષ_CODE (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    પદાવલિ.set_error ();
		    જાઓ out;
		  }
		જો (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = સાચું;
		    જો (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		    નહીંતર જો (all_દ્વિઅંકી)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		    નહીંતર જો (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		    નહીંતર જો (arg_દ્વિઅંકી)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		  }
		નહીંતર જો (વૃક્ષ_CODE (type) == COMPLEX_TYPE)
		  {
		    arg_complex = સાચું;
		    જો (COMPLEX_FLOAT_TYPE_P (type))
		      arg_દ્વિઅંકી = સાચું;
		    જો (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		    નહીંતર જો (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		  }
		નહીંતર જો (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_દ્વિઅંકી = સાચું;
		    જો (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		    નહીંતર જો (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			પદાવલિ.set_error ();
			જાઓ out;
		      }
		  }
		વૃક્ષ rtype = TYPE_MAIN_VARIANT (type);
		જો (વૃક્ષ_CODE (rtype) == COMPLEX_TYPE)
		  rtype = વૃક્ષ_TYPE (rtype);
		જો (SCALAR_FLOAT_TYPE_P (rtype))
		  માટે (unsigned પૂર્ણાંક j = 0; j < અંક_FLOATNX_TYPES; j++)
		    જો (rtype == FLOATNX_TYPE_ગાંઠ (j))
		      {
			arg_int_floatnx = સાચું;
			તોડો;
		      }
		જો (rtype == dfloat64x_type_ગાંઠ)
		  arg_int_decimalx = સાચું;
	      }
	    વૃક્ષ arg_real = NULL_વૃક્ષ;
	    માટે (unsigned પૂર્ણાંક j = 1; j <= nargs; j++)
	      {
		જો (parm_kind[j] == tgmath_fixed)
		  ચાલુ;
		c_પદાવલિ_t *ce = &(*cexpr_list)[અંક_functions + j - 1];
		વૃક્ષ type = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (ce->કિંમત));
		જો (વૃક્ષ_CODE (type) == COMPLEX_TYPE)
		  type = વૃક્ષ_TYPE (type);
		જો (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_ગાંઠ
			  : arg_int_floatnx
			  ? float32x_type_ગાંઠ
			  : arg_int_decimal
			  ? dfloat64_type_ગાંઠ
			  : double_type_ગાંઠ);
		જો (arg_real == NULL_વૃક્ષ)
		  arg_real = type;
		નહીંતર
		  arg_real = common_type (arg_real, type);
		જો (arg_real == error_mark_ગાંઠ)
		  {
		    પદાવલિ.set_error ();
		    જાઓ out;
		  }
	      }
	    વૃક્ષ arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_પદાવલિ_t *fn = ખાલી;
	    માટે (unsigned પૂર્ણાંક j = 0; j < અંક_functions; j++)
	      {
		જો (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    તોડો;
		  }
	      }
	    જો (fn == ખાલી
		&& parm_kind[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_first[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		માટે (unsigned પૂર્ણાંક j = 0; j < અંક_functions; j++)
		  {
		    જો (arg_complex
			!= (વૃક્ષ_CODE (tg_type[j]) == COMPLEX_TYPE))
		      ચાલુ;
		    વૃક્ષ real_tg_type = (arg_complex
					 ? વૃક્ષ_TYPE (tg_type[j])
					 : tg_type[j]);
		    જો (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      ચાલુ;
		    scalar_float_mode arg_mode
		      = SCALAR_FLOAT_TYPE_MODE (arg_real);
		    scalar_float_mode tg_mode
		      = SCALAR_FLOAT_TYPE_MODE (real_tg_type);
		    અચલ real_format *arg_fmt = REAL_MODE_FORMAT (arg_mode);
		    અચલ real_format *tg_fmt = REAL_MODE_FORMAT (tg_mode);
		    જો (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			તોડો;
		      }
		  }
	      }
	    જો (fn == ખાલી)
	      {
		error_at (loc, "no matching function for type-generic call");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    /* Construct a call to FN.  */
	    vec<વૃક્ષ, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<વૃક્ષ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    માટે (unsigned પૂર્ણાંક j = 0; j < nargs; j++)
	      {
		c_પદાવલિ_t *ce = &(*cexpr_list)[અંક_functions + j];
		args->quick_ધકેલો (ce->કિંમત);
		arg_loc.quick_ધકેલો (ce->get_location ());
		origtypes->quick_ધકેલો (ce->original_type);
	      }
	    પદાવલિ.કિંમત = c_build_function_call_vec (loc, arg_loc, fn->કિંમત,
						    args, origtypes);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    તોડો;
	  }
	સ્થિતિ RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    c_પદાવલિ_t *e2_p;
	    વૃક્ષ chain_કિંમત;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, ખોટું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    પદાવલિ = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, સાચું, સાચું);
	    chain_કિંમત = e2_p->કિંમત;
	    mark_exp_read (chain_કિંમત);

	    જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) != CALL_પદાવલિ)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (chain_કિંમત)) != POINTER_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    નહીંતર
	      CALL_પદાવલિ_STATIC_CHAIN (પદાવલિ.કિંમત) = chain_કિંમત;
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    તોડો;
	  }
	સ્થિતિ RID_BUILTIN_COMPLEX:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    c_પદાવલિ_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser,
					    "__builtin_complex",
					    &cexpr_list, ખોટું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }

	    જો (vec_safe_length (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_to_rvalue (loc, *e1_p, સાચું, સાચું);
	    જો (વૃક્ષ_CODE (e1_p->કિંમત) == EXCESS_PRECISION_પદાવલિ)
	      e1_p->કિંમત = convert (વૃક્ષ_TYPE (e1_p->કિંમત),
				     વૃક્ષ_OPERAND (e1_p->કિંમત, 0));
	    *e2_p = convert_lvalue_to_rvalue (loc, *e2_p, સાચું, સાચું);
	    જો (વૃક્ષ_CODE (e2_p->કિંમત) == EXCESS_PRECISION_પદાવલિ)
	      e2_p->કિંમત = convert (વૃક્ષ_TYPE (e2_p->કિંમત),
				     વૃક્ષ_OPERAND (e2_p->કિંમત, 0));
	    જો (!SCALAR_FLOAT_TYPE_P (વૃક્ષ_TYPE (e1_p->કિંમત))
		|| DECIMAL_FLOAT_TYPE_P (વૃક્ષ_TYPE (e1_p->કિંમત))
		|| !SCALAR_FLOAT_TYPE_P (વૃક્ષ_TYPE (e2_p->કિંમત))
		|| DECIMAL_FLOAT_TYPE_P (વૃક્ષ_TYPE (e2_p->કિંમત)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (e1_p->કિંમત))
		!= TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (e2_p->કિંમત)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		પદાવલિ.set_error ();
		તોડો;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    પદાવલિ.કિંમત = build2_loc (loc, COMPLEX_પદાવલિ,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (વૃક્ષ_TYPE (e1_p->કિંમત))),
				     e1_p->કિંમત, e2_p->કિંમત);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    તોડો;
	  }
	સ્થિતિ RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    c_પદાવલિ_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, ખોટું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    e_p = &(*cexpr_list)[0];
	    વૃક્ષ ref = e_p->કિંમત;

	    જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (ref)) != ARRAY_TYPE
		 && વૃક્ષ_CODE (વૃક્ષ_TYPE (ref)) != POINTER_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    જો (વૃક્ષ_CODE (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		પદાવલિ.set_error ();
		તોડો;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    જો (વૃક્ષ_CODE (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    જો (has_counted_by_object (ref))
	      પદાવલિ.કિંમત = get_counted_by_ref (ref);
	    નહીંતર
	      પદાવલિ.કિંમત = null_pointer_ગાંઠ;

	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    તોડો;
	  }
	સ્થિતિ RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    unsigned પૂર્ણાંક i;
	    c_પદાવલિ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser,
					    "__builtin_shuffle",
					    &cexpr_list, ખોટું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, સાચું, સાચું);

	    જો (vec_safe_length (cexpr_list) == 2)
	      પદાવલિ.કિંમત = c_build_vec_perm_પદાવલિ (loc, (*cexpr_list)[0].કિંમત,
						  NULL_વૃક્ષ,
						  (*cexpr_list)[1].કિંમત);

	    નહીંતર જો (vec_safe_length (cexpr_list) == 3)
	      પદાવલિ.કિંમત = c_build_vec_perm_પદાવલિ (loc, (*cexpr_list)[0].કિંમત,
						  (*cexpr_list)[1].કિંમત,
						  (*cexpr_list)[2].કિંમત);
	    નહીંતર
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		પદાવલિ.set_error ();
	      }
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    તોડો;
	  }
	સ્થિતિ RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    unsigned પૂર્ણાંક i;
	    c_પદાવલિ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, ખોટું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }

	    FOR_EACH_VEC_SAFE_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_to_rvalue (loc, *p, સાચું, સાચું);

	    જો (vec_safe_length (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		પદાવલિ.set_error ();
	      }
	    નહીંતર
	      {
		auto_vec<વૃક્ષ, 16> mask;
		માટે (i = 2; i < cexpr_list->length (); ++i)
		  mask.safe_ધકેલો ((*cexpr_list)[i].કિંમત);
		પદાવલિ.કિંમત = c_build_shufflevector (loc, (*cexpr_list)[0].કિંમત,
						    (*cexpr_list)[1].કિંમત,
						    mask);
	      }
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    તોડો;
	  }
	સ્થિતિ RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    e1 = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	    mark_exp_read (e1.કિંમત);
	    જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    જો (t1 == ખાલી)
	      પદાવલિ.set_error ();
	    નહીંતર
	      {
		વૃક્ષ type_પદાવલિ = NULL_વૃક્ષ;
		પદાવલિ.કિંમત = c_build_vec_convert (start_loc, e1.કિંમત, loc,
						  groktypename (t1, &type_પદાવલિ,
								ખાલી));
		set_c_પદાવલિ_source_range (&પદાવલિ, start_loc, end_loc);
	      }
	  }
	  તોડો;
	સ્થિતિ RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t start_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    e1 = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	    mark_exp_read (e1.કિંમત);
	    location_t end_loc = c_parser_peek_token (parser)->get_finish ();
	    parens.skip_until_found_close (parser);
	    પદાવલિ = parser_build_unary_op (loc, PAREN_પદાવલિ, e1);
	    set_c_પદાવલિ_source_range (&પદાવલિ, start_loc, end_loc);
	  }
	  તોડો;
	સ્થિતિ RID_BUILTIN_STDC:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    c_પદાવલિ_t *arg_p;
	    location_t close_paren_loc;
	    ગણના c_builtin_stdc {
	      C_BUILTIN_STDC_BIT_CEIL,
	      C_BUILTIN_STDC_BIT_FLOOR,
	      C_BUILTIN_STDC_BIT_WIDTH,
	      C_BUILTIN_STDC_ગણતરી_ONES,
	      C_BUILTIN_STDC_ગણતરી_ZEROS,
	      C_BUILTIN_STDC_FIRST_LEADING_ONE,
	      C_BUILTIN_STDC_FIRST_LEADING_ZERO,
	      C_BUILTIN_STDC_FIRST_TRAILING_ONE,
	      C_BUILTIN_STDC_FIRST_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_BIT,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_ડાબું,
	      C_BUILTIN_STDC_ROTATE_જમણું,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    અચલ અક્ષર *name
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	    unsigned અંક_args = 1;
	    પસંદગી (name[કદ ("__builtin_stdc_") - 1])
	      {
	      સ્થિતિ 'b':
		પસંદગી (name[કદ ("__builtin_stdc_bit_") - 1])
		  {
		  સ્થિતિ 'c':
		    stdc_rid = C_BUILTIN_STDC_BIT_CEIL;
		    તોડો;
		  સ્થિતિ 'f':
		    stdc_rid = C_BUILTIN_STDC_BIT_FLOOR;
		    તોડો;
		  મૂળભૂત:
		    stdc_rid = C_BUILTIN_STDC_BIT_WIDTH;
		    તોડો;
		  }
		તોડો;
	      સ્થિતિ 'c':
		જો (name[કદ ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_ગણતરી_ONES;
		નહીંતર
		  stdc_rid = C_BUILTIN_STDC_ગણતરી_ZEROS;
		તોડો;
	      સ્થિતિ 'f':
		પસંદગી (name[કદ ("__builtin_stdc_first_trailing_") - 1])
		  {
		  સ્થિતિ 'n':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ONE;
		    તોડો;
		  સ્થિતિ 'e':
		    stdc_rid = C_BUILTIN_STDC_FIRST_LEADING_ZERO;
		    તોડો;
		  સ્થિતિ 'o':
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ONE;
		    તોડો;
		  મૂળભૂત:
		    stdc_rid = C_BUILTIN_STDC_FIRST_TRAILING_ZERO;
		    તોડો;
		  }
		તોડો;
	      સ્થિતિ 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_BIT;
		તોડો;
	      સ્થિતિ 'l':
		જો (name[કદ ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		નહીંતર
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		તોડો;
	      સ્થિતિ 'r':
		જો (name[કદ ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ડાબું;
		નહીંતર
		  stdc_rid = C_BUILTIN_STDC_ROTATE_જમણું;
		અંક_args = 2;
		તોડો;
	      સ્થિતિ 't':
		જો (name[કદ ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		નહીંતર
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		તોડો;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser, name,
					    &cexpr_list, ખોટું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }

	    જો (vec_safe_length (cexpr_list) != અંક_args)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		પદાવલિ.set_error ();
		તોડો;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, સાચું, સાચું);
	    જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (arg_p->કિંમત)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (arg_p->કિંમત)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (arg_p->કિંમત)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (!TYPE_UNSIGNED (વૃક્ષ_TYPE (arg_p->કિંમત)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (arg_p->કિંમત))
		== char_type_ગાંઠ)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    વૃક્ષ arg = arg_p->કિંમત;
	    વૃક્ષ type = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (arg));
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
	    પૂર્ણાંક prec = TYPE_PRECISION (type);
	    જો (અંક_args == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_to_rvalue (loc, *arg_p, સાચું, સાચું);
		જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (arg_p->કિંમત)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    પદાવલિ.set_error ();
		    તોડો;
		  }
		જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (arg_p->કિંમત)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    પદાવલિ.set_error ();
		    તોડો;
		  }
		વૃક્ષ arg1 = save_પદાવલિ (arg);
		વૃક્ષ arg2 = save_પદાવલિ (arg_p->કિંમત);
		વૃક્ષ_code code;
		જો (stdc_rid == C_BUILTIN_STDC_ROTATE_ડાબું)
		  code = LROTATE_પદાવલિ;
		નહીંતર
		  code = RROTATE_પદાવલિ;

		જો (વૃક્ષ_CODE (arg2) == INTEGER_CST
		    && વૃક્ષ_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_ગણતરી_negative,
			      "rotate count is negative");

		વૃક્ષ instrument_પદાવલિ = NULL_વૃક્ષ;
		જો (sanitize_flags_p (SANITIZE_SHIFT))
		  instrument_પદાવલિ = ubsan_instrument_shift (loc, code,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		જો (TYPE_PRECISION (વૃક્ષ_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_ગાંઠ))
		  arg2 = fold_convert (unsigned_type_ગાંઠ, arg2);

		જો (TYPE_UNSIGNED (વૃક્ષ_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_પદાવલિ, વૃક્ષ_TYPE (arg2),
				     arg2, build_int_cst (વૃક્ષ_TYPE (arg2),
							  prec));
		નહીંતર
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    વૃક્ષ utype = c_common_unsigned_type (વૃક્ષ_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_પદાવલિ, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		જો (type_has_mode_precision_p (વૃક્ષ_TYPE (arg1))
		    || (વૃક્ષ_CODE (વૃક્ષ_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_MODE_SIZE))
		  પદાવલિ.કિંમત = build2_loc (loc, code, વૃક્ષ_TYPE (arg1), arg1,
					   arg2);
		નહીંતર
		  {
		    arg2 = save_પદાવલિ (arg2);
		    વૃક્ષ t1 = build2_loc (loc, (code == LROTATE_પદાવલિ
						? LSHIFT_પદાવલિ : RSHIFT_પદાવલિ),
					  વૃક્ષ_TYPE (arg1), arg1, arg2);
		    વૃક્ષ t2 = build2_loc (loc, MINUS_પદાવલિ,
					  વૃક્ષ_TYPE (arg2),
					  build_int_cst (વૃક્ષ_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (code == LROTATE_પદાવલિ
					   ? RSHIFT_પદાવલિ : LSHIFT_પદાવલિ),
				     વૃક્ષ_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_ગણતરી_overflow);
		    વૃક્ષ t3 = build2_loc (loc, BIT_IOR_પદાવલિ,
					  વૃક્ષ_TYPE (arg1), t1, t2);
		    વૃક્ષ t4 = build2_loc (loc, NE_પદાવલિ, boolean_type_ગાંઠ,
					  arg2,
					  build_zero_cst (વૃક્ષ_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_પદાવલિ, boolean_type_ગાંઠ,
				     arg1, t4);
		    પદાવલિ.કિંમત = build3_loc (loc, COND_પદાવલિ,
					     વૃક્ષ_TYPE (arg1), t4, t3, arg1);
		  }
		જો (instrument_પદાવલિ)
		  પદાવલિ.કિંમત = build2_loc (loc, COMPOUND_પદાવલિ,
					   વૃક્ષ_TYPE (પદાવલિ.કિંમત),
					   instrument_પદાવલિ, પદાવલિ.કિંમત);
		set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
		તોડો;
	      }
	    વૃક્ષ barg1 = arg;
	    પસંદગી (stdc_rid)
	      {
	      સ્થિતિ C_BUILTIN_STDC_BIT_CEIL:
		arg = save_પદાવલિ (arg);
		barg1 = build2_loc (loc, PLUS_પદાવલિ, type, arg,
				    build_int_cst (type, -1));
		તોડો;
	      સ્થિતિ C_BUILTIN_STDC_BIT_FLOOR:
		barg1 = arg = save_પદાવલિ (arg);
		તોડો;
	      સ્થિતિ C_BUILTIN_STDC_ગણતરી_ZEROS:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      સ્થિતિ C_BUILTIN_STDC_LEADING_ONES:
	      સ્થિતિ C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, BIT_NOT_પદાવલિ, type, arg);
		તોડો;
	      મૂળભૂત:
		તોડો;
	      }
	    વૃક્ષ barg2 = NULL_વૃક્ષ;
	    પસંદગી (stdc_rid)
	      {
	      સ્થિતિ C_BUILTIN_STDC_BIT_WIDTH:
	      સ્થિતિ C_BUILTIN_STDC_LEADING_ONES:
	      સ્થિતિ C_BUILTIN_STDC_LEADING_ZEROS:
	      સ્થિતિ C_BUILTIN_STDC_TRAILING_ONES:
	      સ્થિતિ C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_ગાંઠ, prec);
		તોડો;
	      સ્થિતિ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		barg2 = integer_minus_one_ગાંઠ;
		તોડો;
	      મૂળભૂત:
		તોડો;
	      }
	    વૃક્ષ fndecl = NULL_વૃક્ષ;
	    પસંદગી (stdc_rid)
	      {
	      સ્થિતિ C_BUILTIN_STDC_BIT_CEIL:
	      સ્થિતિ C_BUILTIN_STDC_BIT_FLOOR:
	      સ્થિતિ C_BUILTIN_STDC_BIT_WIDTH:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      સ્થિતિ C_BUILTIN_STDC_LEADING_ONES:
	      સ્થિતિ C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CLZG);
		તોડો;
	      સ્થિતિ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
	      સ્થિતિ C_BUILTIN_STDC_TRAILING_ONES:
	      સ્થિતિ C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_IN_CTZG);
		તોડો;
	      સ્થિતિ C_BUILTIN_STDC_ગણતરી_ONES:
	      સ્થિતિ C_BUILTIN_STDC_ગણતરી_ZEROS:
	      સ્થિતિ C_BUILTIN_STDC_HAS_SINGLE_BIT:
		fndecl = builtin_decl_explicit (BUILT_IN_POPCOUNTG);
		તોડો;
	      મૂળભૂત:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    પૂર્ણાંક nargs = barg2 != NULL_વૃક્ષ ? 2 : 1;
	    vec<વૃક્ષ, va_gc> *args;
	    vec_alloc (args, nargs);
	    vec<વૃક્ષ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    args->quick_ધકેલો (barg1);
	    arg_loc.quick_ધકેલો (arg_p->get_location ());
	    origtypes->quick_ધકેલો (arg_p->original_type);
	    જો (nargs == 2)
	      {
		args->quick_ધકેલો (barg2);
		arg_loc.quick_ધકેલો (loc);
		origtypes->quick_ધકેલો (integer_type_ગાંઠ);
	      }
	    પદાવલિ.કિંમત = c_build_function_call_vec (loc, arg_loc, fndecl,
						    args, origtypes);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    જો (પદાવલિ.કિંમત == error_mark_ગાંઠ)
	      તોડો;
	    પસંદગી (stdc_rid)
	      {
	      સ્થિતિ C_BUILTIN_STDC_BIT_CEIL:
	      સ્થિતિ C_BUILTIN_STDC_BIT_FLOOR:
		--prec;
		/* FALLTHRU */
	      સ્થિતિ C_BUILTIN_STDC_BIT_WIDTH:
		પદાવલિ.કિંમત = build2_loc (loc, MINUS_પદાવલિ, integer_type_ગાંઠ,
					 build_int_cst (integer_type_ગાંઠ,
							prec), પદાવલિ.કિંમત);
		તોડો;
	      સ્થિતિ C_BUILTIN_STDC_FIRST_LEADING_ONE:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_LEADING_ZERO:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_TRAILING_ONE:
	      સ્થિતિ C_BUILTIN_STDC_FIRST_TRAILING_ZERO:
		પદાવલિ.કિંમત = build2_loc (loc, PLUS_પદાવલિ, integer_type_ગાંઠ,
					 પદાવલિ.કિંમત, integer_one_ગાંઠ);
		તોડો;
	      સ્થિતિ C_BUILTIN_STDC_HAS_SINGLE_BIT:
		પદાવલિ.કિંમત = build2_loc (loc, EQ_પદાવલિ, boolean_type_ગાંઠ,
					 પદાવલિ.કિંમત, integer_one_ગાંઠ);
		તોડો;
	      મૂળભૂત:
		તોડો;
	      }

	    જો (stdc_rid != C_BUILTIN_STDC_BIT_CEIL
		&& stdc_rid != C_BUILTIN_STDC_BIT_FLOOR)
	      {
		જો (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_BIT)
		  પદાવલિ.કિંમત = fold_convert_loc (loc, unsigned_type_ગાંઠ,
						 પદાવલિ.કિંમત);
		તોડો;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    જો (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_BIT_CEIL && integer_onep (arg)))
	      પદાવલિ.કિંમત = build_int_cst (type, 0);
	    નહીંતર
	      પદાવલિ.કિંમત
		= build2_loc (loc, LSHIFT_પદાવલિ, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_BIT_CEIL
					      ? 2 : 1)), પદાવલિ.કિંમત);
	    જો (stdc_rid == C_BUILTIN_STDC_BIT_CEIL)
	      પદાવલિ.કિંમત = build3_loc (loc, COND_પદાવલિ, type,
				       build2_loc (loc, LE_પદાવલિ,
						   boolean_type_ગાંઠ, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       પદાવલિ.કિંમત);
	    નહીંતર
	      પદાવલિ.કિંમત = build3_loc (loc, COND_પદાવલિ, type,
				       build2_loc (loc, EQ_પદાવલિ,
						   boolean_type_ગાંઠ, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       પદાવલિ.કિંમત);
	    તોડો;
	  }
	સ્થિતિ RID_BUILTIN_BSWAPG:
	સ્થિતિ RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_પદાવલિ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    internal_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    અચલ અક્ષર *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    જો (!c_parser_get_builtin_args (parser, name, &cexpr_list, ખોટું,
					    &close_paren_loc))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }

	    જો (vec_safe_length (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		પદાવલિ.set_error ();
		તોડો;
	      }

	    c_પદાવલિ_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_to_rvalue (loc, *arg_p, સાચું, સાચું);
	    વૃક્ષ arg = arg_p->કિંમત;
	    જો (error_operand_p (arg))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    વૃક્ષ type = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (arg));
	    જો (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (વૃક્ષ_CODE (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (વૃક્ષ_CODE (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    arg = c_fully_fold (arg, ખોટું, ખાલી);
	    પદાવલિ.કિંમત = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_paren_loc);
	    તોડો;
	  }
	સ્થિતિ RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    વૃક્ષ sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    પદાવલિ.કિંમત = objc_build_selector_પદાવલિ (loc, sel);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_loc);
	  }
	  તોડો;
	સ્થિતિ RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    જો (c_parser_next_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
		પદાવલિ.set_error ();
		તોડો;
	      }
	    વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    પદાવલિ.કિંમત = objc_build_protocol_પદાવલિ (id);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_loc);
	  }
	  તોડો;
	સ્થિતિ RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    જો (!parens.require_open (parser))
	      {
		પદાવલિ.set_error ();
		તોડો;
	      }
	    t1 = c_parser_type_name (parser);
	    જો (t1 == ખાલી)
	      {
		પદાવલિ.set_error ();
		c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
		તોડો;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_found_close (parser);
	    વૃક્ષ type = groktypename (t1, ખાલી, ખાલી);
	    પદાવલિ.કિંમત = objc_build_encode_પદાવલિ (type);
	    set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_loc);
	  }
	  તોડો;
	સ્થિતિ RID_GENERIC:
	  પદાવલિ = c_parser_generic_selection (parser);
	  તોડો;
	સ્થિતિ RID_OMP_ALL_MEMORY:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  પદાવલિ.set_error ();
	  તોડો;
	/* C23 'nullptr' literal.  */
	સ્થિતિ RID_NULLPTR:
	  c_parser_consume_token (parser);
	  પદાવલિ.કિંમત = nullptr_ગાંઠ;
	  set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  તોડો;
	સ્થિતિ RID_TRUE:
	  c_parser_consume_token (parser);
	  પદાવલિ.કિંમત = boolean_true_ગાંઠ;
	  set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
	  તોડો;
	સ્થિતિ RID_FALSE:
	  c_parser_consume_token (parser);
	  પદાવલિ.કિંમત = boolean_false_ગાંઠ;
	  set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
	  તોડો;
	મૂળભૂત:
	  c_parser_error (parser, "expected expression");
	  પદાવલિ.set_error ();
	  તોડો;
	}
      તોડો;
    સ્થિતિ CPP_OPEN_SQUARE:
      જો (c_dialect_objc ())
	{
	  વૃક્ષ receiver, args;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  args = c_parser_objc_message_args (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  પદાવલિ.કિંમત = objc_build_message_પદાવલિ (receiver, args);
	  set_c_પદાવલિ_source_range (&પદાવલિ, loc, close_loc);
	  તોડો;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    મૂળભૂત:
      c_parser_error (parser, "expected expression");
      પદાવલિ.set_error ();
      તોડો;
    }
 out:
  પાછા c_parser_postfix_expression_after_primary
    (parser, પદાવલિ_LOC_OR_LOC (પદાવલિ.કિંમત, loc), પદાવલિ);
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

સ્થિર સંરચના c_પદાવલિ
c_parser_postfix_expression_after_paren_type (c_parser *parser,
					      સંરચના c_declspecs *scspecs,
					      સંરચના c_type_name *type_name,
					      location_t type_loc)
{
  વૃક્ષ type;
  સંરચના c_પદાવલિ init;
  તાર્કિક non_const;
  સંરચના c_પદાવલિ પદાવલિ;
  location_t start_loc;
  વૃક્ષ type_પદાવલિ = NULL_વૃક્ષ;
  તાર્કિક type_પદાવલિ_const = સાચું;
  તાર્કિક constexpr_p = scspecs ? scspecs->constexpr_p : ખોટું;
  unsigned પૂર્ણાંક underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (લીટી_table, type_loc);
  start_loc = c_parser_peek_token (parser)->location;
  જો (constexpr_p)
    {
      underspec_state = start_underspecified_init (start_loc, NULL_વૃક્ષ);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      પસંદગી (type_name->specs->typespec_kind)
	{
	સ્થિતિ ctsk_tagfirstref:
	સ્થિતિ ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  તોડો;

	સ્થિતિ ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  તોડો;

	મૂળભૂત:
	  તોડો;
	}
    }
  start_init (NULL_વૃક્ષ, ખાલી,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_પદાવલિ, &type_પદાવલિ_const);
  તાર્કિક varsize_p = ખોટું;
  જો (type != error_mark_ગાંઠ && C_TYPE_VARIABLE_SIZE (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = સાચું;
    }
  નહીંતર જો (વૃક્ષ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_ગાંઠ;
    }
  જો (constexpr_p && type != error_mark_ગાંઠ)
    {
      વૃક્ષ type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      જો (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      નહીંતર જો (RECORD_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, ખોટું, ખાલી, varsize_p);
  જો (constexpr_p)
    finish_underspecified_init (NULL_વૃક્ષ, underspec_state);
  finish_init ();
  maybe_warn_string_init (type_loc, type, init);

  જો (type != error_mark_ગાંઠ
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_ગાંઠ;
    }

  જો (!pedwarn_c90 (start_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (start_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.કિંમત && વૃક્ષ_CODE (init.કિંમત) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.કિંમત)
	       : init.original_code == C_MAYBE_CONST_પદાવલિ);
  non_const |= !type_પદાવલિ_const;
  unsigned પૂર્ણાંક alignas_align = 0;
  જો (type != error_mark_ગાંઠ
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      જો (alignas_align < min_align_of_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  પદાવલિ.કિંમત = build_compound_literal (start_loc, type, init.કિંમત, non_const,
				       alignas_align, scspecs);
  set_c_પદાવલિ_source_range (&પદાવલિ, init.src_range);
  પદાવલિ.m_decimal = 0;
  પદાવલિ.original_code = ERROR_MARK;
  પદાવલિ.original_type = ખાલી;
  જો (type != error_mark_ગાંઠ
      && પદાવલિ.કિંમત != error_mark_ગાંઠ
      && type_પદાવલિ)
    {
      જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == C_MAYBE_CONST_પદાવલિ)
	{
	  gcc_assert (C_MAYBE_CONST_પદાવલિ_PRE (પદાવલિ.કિંમત) == NULL_વૃક્ષ);
	  C_MAYBE_CONST_પદાવલિ_PRE (પદાવલિ.કિંમત) = type_પદાવલિ;
	}
      નહીંતર
	{
	  gcc_assert (!non_const);
	  પદાવલિ.કિંમત = build2 (C_MAYBE_CONST_પદાવલિ, type,
			       type_પદાવલિ, પદાવલિ.કિંમત);
	}
    }
  પાછા c_parser_postfix_expression_after_primary (parser, start_loc, પદાવલિ);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

સ્થિર તાર્કિક
sizeof_ptr_memacc_comptypes (વૃક્ષ type1, વૃક્ષ type2)
{
  પાછા comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

સ્થિર શૂન્ય
warn_for_abs (location_t loc, વૃક્ષ fndecl, વૃક્ષ arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  જો (c_inhibit_evaluation_warnings)
    પાછા;

  વૃક્ષ atype = વૃક્ષ_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  જો (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && વૃક્ષ_CODE (atype) != COMPLEX_TYPE)
    પાછા;

  ગણના built_in_function fcode = DECL_FUNCTION_CODE (fndecl);

  પસંદગી (fcode)
    {
    સ્થિતિ BUILT_IN_ABS:
    સ્થિતિ BUILT_IN_LABS:
    સ્થિતિ BUILT_IN_LLABS:
    સ્થિતિ BUILT_IN_IMAXABS:
      જો (!INTEGRAL_TYPE_P (atype))
	{
	  જો (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  નહીંતર જો (વૃક્ષ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  નહીંતર
	    gcc_unreachable ();
	  પાછા;
	}
      જો (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_કિંમત,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      તોડો;

    CASE_FLT_FN (BUILT_IN_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_IN_FABS):
      જો (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_MODE_P (TYPE_MODE (atype)))
	{
	  જો (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  નહીંતર જો (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  નહીંતર જો (વૃક્ષ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  નહીંતર
	    gcc_unreachable ();
	  પાછા;
	}
      તોડો;

    CASE_FLT_FN (BUILT_IN_CABS):
      જો (વૃક્ષ_CODE (atype) != COMPLEX_TYPE)
	{
	  જો (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  નહીંતર જો (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  નહીંતર
	    gcc_unreachable ();

	  પાછા;
	}
      તોડો;

    સ્થિતિ BUILT_IN_FABSD32:
    સ્થિતિ BUILT_IN_FABSD64:
    સ્થિતિ BUILT_IN_FABSD128:
    સ્થિતિ BUILT_IN_FABSD64X:
      જો (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  જો (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  નહીંતર જો (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  નહીંતર જો (વૃક્ષ_CODE (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_કિંમત,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  નહીંતર
	    gcc_unreachable ();
	  પાછા;
	}
      તોડો;

    મૂળભૂત:
      પાછા;
    }

  જો (!TYPE_ARG_TYPES (વૃક્ષ_TYPE (fndecl)))
    પાછા;

  વૃક્ષ ftype = વૃક્ષ_કિંમત (TYPE_ARG_TYPES (વૃક્ષ_TYPE (fndecl)));
  જો (વૃક્ષ_CODE (atype) == COMPLEX_TYPE)
    {
      gcc_assert (વૃક્ષ_CODE (ftype) == COMPLEX_TYPE);
      atype = વૃક્ષ_TYPE (atype);
      ftype = વૃક્ષ_TYPE (ftype);
    }

  જો (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_કિંમત,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

સ્થિર સંરચના c_પદાવલિ
c_parser_postfix_expression_after_primary (c_parser *parser,
					   location_t પદાવલિ_loc,
					   સંરચના c_પદાવલિ પદાવલિ)
{
  સંરચના c_પદાવલિ orig_પદાવલિ;
  વૃક્ષ ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  વૃક્ષ sizeof_arg[6];
  unsigned પૂર્ણાંક literal_zero_mask;
  unsigned પૂર્ણાંક i;
  vec<વૃક્ષ, va_gc> *exprlist;
  vec<વૃક્ષ, va_gc> *origtypes = ખાલી;
  vec<location_t> arg_loc = vNULL;
  location_t start;
  location_t finish;

  જ્યારે (સાચું)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_OPEN_SQUARE:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_વૃક્ષ;
	  જો (!c_omp_array_section_p
	      || c_parser_next_token_is_not (parser, CPP_COLON))
	    idx = c_parser_expression (parser).કિંમત;

	  જો (c_omp_array_section_p
	      && c_parser_next_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      જો (c_parser_next_token_is_not (parser, CPP_CLOSE_SQUARE))
		len = c_parser_expression (parser).કિંમત;

	      પદાવલિ.કિંમત = build_omp_array_section (op_loc, પદાવલિ.કિંમત, idx,
						    len);
	    }
	  નહીંતર
	    પદાવલિ.કિંમત = build_array_ref (op_loc, પદાવલિ.કિંમત, idx);

	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");

	  start = પદાવલિ.get_start ();
	  finish = parser->tokens_buf[0].location;
	  set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	  પદાવલિ.original_code = ERROR_MARK;
	  પદાવલિ.original_type = ખાલી;
	  પદાવલિ.m_decimal = 0;
	  તોડો;
	સ્થિતિ CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    માટે (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_વૃક્ષ;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_mask = 0;
	    જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = ખાલી;
	    નહીંતર જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == FUNCTION_DECL
		     && fndecl_built_in_p (પદાવલિ.કિંમત, BUILT_IN_CLASSIFY_TYPE)
		     && c_parser_next_tokens_start_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		in_alignof++;
		સંરચના c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		in_alignof--;
		સંરચના c_typespec ret;
		ret.પદાવલિ = NULL_વૃક્ષ;
		ret.spec = error_mark_ગાંઠ;
		ret.પદાવલિ_const_operands = ખોટું;
		જો (type != ખાલી)
		  ret.spec = groktypename (type, &ret.પદાવલિ,
					   &ret.પદાવલિ_const_operands);
		parens.skip_until_found_close (parser);
		પદાવલિ.કિંમત = build_int_cst (integer_type_ગાંઠ,
					    type_to_class (ret.spec));
		તોડો;
	      }
	    નહીંતર
	      exprlist = c_parser_પદાવલિ_list (parser, સાચું, ખોટું, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_mask);
	    parens.skip_until_found_close (parser);
	  }
	  orig_પદાવલિ = પદાવલિ;
	  mark_exp_read (પદાવલિ.કિંમત);
	  જો (warn_sizeof_pointer_memaccess)
	    sizeof_pointer_memaccess_warning (sizeof_arg_loc,
					      પદાવલિ.કિંમત, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == FUNCTION_DECL)
	    {
	      જો (fndecl_built_in_p (પદાવલિ.કિંમત, BUILT_IN_MEMSET)
		  && vec_safe_length (exprlist) == 3)
		{
		  વૃક્ષ arg0 = (*exprlist)[0];
		  વૃક્ષ arg2 = (*exprlist)[2];
		  warn_for_memset (પદાવલિ_loc, arg0, arg2, literal_zero_mask);
		}
	      જો (warn_absolute_કિંમત
		  && fndecl_built_in_p (પદાવલિ.કિંમત, BUILT_IN_NORMAL)
		  && vec_safe_length (exprlist) == 1)
		warn_for_abs (પદાવલિ_loc, પદાવલિ.કિંમત, (*exprlist)[0]);
	      જો (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->in_intervening_code
		  && omp_runtime_api_call (પદાવલિ.કિંમત))
		{
		  error_at (પદાવલિ_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = સાચું;
		}
	      જો (warn_calloc_transposed_args)
		જો (વૃક્ષ attr = lookup_attribute ("alloc_size",
						  TYPE_ATTRIBUTES
						    (વૃક્ષ_TYPE (પદાવલિ.કિંમત))))
		  જો (વૃક્ષ_કિંમત (attr) && વૃક્ષ_CHAIN (વૃક્ષ_કિંમત (attr)))
		    warn_for_calloc (sizeof_arg_loc, પદાવલિ.કિંમત, exprlist,
				     sizeof_arg, attr);
	    }

	  start = પદાવલિ.get_start ();
	  finish = parser->tokens_buf[0].get_finish ();
	  પદાવલિ.કિંમત
	    = c_build_function_call_vec (પદાવલિ_loc, arg_loc, પદાવલિ.કિંમત,
					 exprlist, origtypes);
	  set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	  પદાવલિ.m_decimal = 0;

	  પદાવલિ.original_code = ERROR_MARK;
	  જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == INTEGER_CST
	      && વૃક્ષ_CODE (orig_પદાવલિ.કિંમત) == FUNCTION_DECL
	      && fndecl_built_in_p (orig_પદાવલિ.કિંમત, BUILT_IN_CONSTANT_P))
	    પદાવલિ.original_code = C_MAYBE_CONST_પદાવલિ;
	  પદાવલિ.original_type = ખાલી;
	  જો (exprlist)
	    {
	      release_વૃક્ષ_vector (exprlist);
	      release_વૃક્ષ_vector (origtypes);
	    }
	  arg_loc.release ();
	  તોડો;
	સ્થિતિ CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  પદાવલિ = default_function_array_conversion (પદાવલિ_loc, પદાવલિ);
	  જો (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->કિંમત;
	      comp_loc = comp_tok->location;
	    }
	  નહીંતર
	    {
	      c_parser_error (parser, "expected identifier");
	      પદાવલિ.set_error ();
	      પદાવલિ.original_code = ERROR_MARK;
              પદાવલિ.original_type = ખાલી;
	      પાછા પદાવલિ;
	    }
	  start = પદાવલિ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  પદાવલિ.કિંમત = build_component_ref (op_loc, પદાવલિ.કિંમત, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	  પદાવલિ.original_code = ERROR_MARK;
	  જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) != COMPONENT_REF)
	    પદાવલિ.original_type = ખાલી;
	  નહીંતર
	    {
	      /* Remember the original type of a bitfield.  */
	      વૃક્ષ field = વૃક્ષ_OPERAND (પદાવલિ.કિંમત, 1);
	      જો (વૃક્ષ_CODE (field) != FIELD_DECL)
		પદાવલિ.original_type = ખાલી;
	      નહીંતર
		પદાવલિ.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  પદાવલિ.m_decimal = 0;
	  તોડો;
	સ્થિતિ CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, સાચું, ખોટું);
	  જો (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->કિંમત;
	      comp_loc = comp_tok->location;
	    }
	  નહીંતર
	    {
	      c_parser_error (parser, "expected identifier");
	      પદાવલિ.set_error ();
	      પદાવલિ.original_code = ERROR_MARK;
	      પદાવલિ.original_type = ખાલી;
	      પાછા પદાવલિ;
	    }
	  start = પદાવલિ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  પદાવલિ.કિંમત = build_component_ref (op_loc,
					    build_indirect_ref (op_loc,
								પદાવલિ.કિંમત,
								RO_ARROW),
					    ident, comp_loc,
					    પદાવલિ.get_location ());
	  set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	  પદાવલિ.original_code = ERROR_MARK;
	  જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) != COMPONENT_REF)
	    પદાવલિ.original_type = ખાલી;
	  નહીંતર
	    {
	      /* Remember the original type of a bitfield.  */
	      વૃક્ષ field = વૃક્ષ_OPERAND (પદાવલિ.કિંમત, 1);
	      જો (વૃક્ષ_CODE (field) != FIELD_DECL)
		પદાવલિ.original_type = ખાલી;
	      નહીંતર
		પદાવલિ.original_type = DECL_BIT_FIELD_TYPE (field);
	    }
	  પદાવલિ.m_decimal = 0;
	  તોડો;
	સ્થિતિ CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  start = પદાવલિ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (પદાવલિ.કિંમત);
	  પદાવલિ = default_function_array_conversion (પદાવલિ_loc, પદાવલિ);
	  પદાવલિ.કિંમત = build_unary_op (op_loc, POSTINCREMENT_પદાવલિ,
				       પદાવલિ.કિંમત, ખોટું);
	  set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	  પદાવલિ.original_code = ERROR_MARK;
	  પદાવલિ.original_type = ખાલી;
	  તોડો;
	સ્થિતિ CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  start = પદાવલિ.get_start ();
	  finish = c_parser_peek_token (parser)->get_finish ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (પદાવલિ.કિંમત);
	  પદાવલિ = default_function_array_conversion (પદાવલિ_loc, પદાવલિ);
	  પદાવલિ.કિંમત = build_unary_op (op_loc, POSTDECREMENT_પદાવલિ,
				       પદાવલિ.કિંમત, ખોટું);
	  set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	  પદાવલિ.original_code = ERROR_MARK;
	  પદાવલિ.original_type = ખાલી;
	  તોડો;
	મૂળભૂત:
	  પાછા પદાવલિ;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

સ્થિર સંરચના c_પદાવલિ
c_parser_expression (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  સંરચના c_પદાવલિ પદાવલિ;
  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  જો (c_parser_next_token_is (parser, CPP_COMMA))
    પદાવલિ = convert_lvalue_to_rvalue (tloc, પદાવલિ, સાચું, ખોટું);
  જ્યારે (c_parser_next_token_is (parser, CPP_COMMA))
    {
      સંરચના c_પદાવલિ next;
      વૃક્ષ lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t પદાવલિ_loc;
      c_parser_consume_token (parser);
      પદાવલિ_loc = c_parser_peek_token (parser)->location;
      lhsval = પદાવલિ.કિંમત;
      જ્યારે (વૃક્ષ_CODE (lhsval) == COMPOUND_પદાવલિ
	     || વૃક્ષ_CODE (lhsval) == NOP_પદાવલિ)
	{
	  જો (વૃક્ષ_CODE (lhsval) == COMPOUND_પદાવલિ)
	    lhsval = વૃક્ષ_OPERAND (lhsval, 1);
	  નહીંતર
	    lhsval = વૃક્ષ_OPERAND (lhsval, 0);
	}
      જો (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      જો (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  વૃક્ષ val = embed->કિંમત;
	  unsigned last = RAW_DATA_LENGTH (val) - 1;
	  next.કિંમત = build_int_cst (વૃક્ષ_TYPE (val),
				      RAW_DATA_UCHAR_ELT (val, last));
	  next.original_type = integer_type_ગાંઠ;
	  c_parser_consume_token (parser);
	}
      નહીંતર
	{
	  next = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  next = convert_lvalue_to_rvalue (પદાવલિ_loc, next, સાચું, ખોટું);
	}
      પદાવલિ.કિંમત = build_compound_પદાવલિ (loc, પદાવલિ.કિંમત, next.કિંમત);
      પદાવલિ.original_code = COMPOUND_પદાવલિ;
      પદાવલિ.original_type = next.original_type;
      પદાવલિ.m_decimal = 0;
    }
  પાછા પદાવલિ;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

સ્થિર સંરચના c_પદાવલિ
c_parser_expression_conv (c_parser *parser)
{
  સંરચના c_પદાવલિ પદાવલિ;
  location_t loc = c_parser_peek_token (parser)->location;
  પદાવલિ = c_parser_expression (parser);
  પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, સાચું, ખોટું);
  પાછા પદાવલિ;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

સ્થિર અંતઃરેખ શૂન્ય
c_parser_check_literal_zero (c_parser *parser, unsigned *literal_zero_mask,
			     unsigned પૂર્ણાંક idx)
{
  જો (idx >= HOST_BITS_PER_INT)
    પાછા;

  c_token *tok = c_parser_peek_token (parser);
  પસંદગી (tok->type)
    {
    સ્થિતિ CPP_સંખ્યા:
    સ્થિતિ CPP_CHAR:
    સ્થિતિ CPP_WCHAR:
    સ્થિતિ CPP_CHAR16:
    સ્થિતિ CPP_CHAR32:
    સ્થિતિ CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      જો (integer_zerop (tok->કિંમત)
	  && !વૃક્ષ_OVERFLOW (tok->કિંમત)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_mask |= 1U << idx;
    મૂળભૂત:
      તોડો;
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

સ્થિર vec<વૃક્ષ, va_gc> *
c_parser_પદાવલિ_list (c_parser *parser, તાર્કિક convert_p, તાર્કિક fold_p,
		    vec<વૃક્ષ, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, વૃક્ષ *sizeof_arg,
		    vec<location_t> *locations,
		    unsigned પૂર્ણાંક *literal_zero_mask)
{
  vec<વૃક્ષ, va_gc> *ret;
  vec<વૃક્ષ, va_gc> *orig_types;
  સંરચના c_પદાવલિ પદાવલિ;
  unsigned પૂર્ણાંક idx = 0;
  તાર્કિક save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = ખોટું;

  ret = make_વૃક્ષ_vector ();
  જો (p_orig_types == ખાલી)
    orig_types = ખાલી;
  નહીંતર
    orig_types = make_વૃક્ષ_vector ();

  જો (literal_zero_mask)
    c_parser_check_literal_zero (parser, literal_zero_mask, 0);
  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  જો (convert_p)
    પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ.get_location (), પદાવલિ, સાચું, સાચું);
  જો (fold_p)
    પદાવલિ.કિંમત = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
  ret->quick_ધકેલો (પદાવલિ.કિંમત);
  જો (orig_types)
    orig_types->quick_ધકેલો (પદાવલિ.original_type);
  જો (locations)
    locations->safe_ધકેલો (પદાવલિ.get_location ());
  જો (sizeof_arg != ખાલી
      && (પદાવલિ.original_code == SIZEOF_પદાવલિ
	  || પદાવલિ.original_code == PAREN_SIZEOF_પદાવલિ))
    {
      sizeof_arg[0] = c_last_sizeof_arg;
      sizeof_arg_loc[0] = c_last_sizeof_loc;
    }
  જ્યારે (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  વૃક્ષ કિંમત = embed->કિંમત;
	  પદાવલિ.original_code = INTEGER_CST;
	  પદાવલિ.original_type = integer_type_ગાંઠ;
	  પદાવલિ.કિંમત = NULL_વૃક્ષ;
	  set_c_પદાવલિ_source_range (&પદાવલિ, embed->get_range ());
	  પદાવલિ.m_decimal = 0;
	  માટે (unsigned પૂર્ણાંક i = 0; i < (unsigned) RAW_DATA_LENGTH (કિંમત); i++)
	    {
	      જો (literal_zero_mask
		  && idx + 1 < HOST_BITS_PER_INT
		  && RAW_DATA_POINTER (કિંમત)[i] == 0)
		*literal_zero_mask |= 1U << (idx + 1);
	      પદાવલિ.કિંમત = build_int_cst (integer_type_ગાંઠ,
					  RAW_DATA_UCHAR_ELT (કિંમત, i));
	      vec_safe_ધકેલો (ret, પદાવલિ.કિંમત);
	      જો (orig_types)
		vec_safe_ધકેલો (orig_types, પદાવલિ.original_type);
	      જો (locations)
		locations->safe_ધકેલો (પદાવલિ.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  ચાલુ;
	}
      જો (literal_zero_mask)
	c_parser_check_literal_zero (parser, literal_zero_mask, idx + 1);
      પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      જો (convert_p)
	પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ.get_location (), પદાવલિ, સાચું,
					 સાચું);
      જો (fold_p)
	પદાવલિ.કિંમત = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
      vec_safe_ધકેલો (ret, પદાવલિ.કિંમત);
      જો (orig_types)
	vec_safe_ધકેલો (orig_types, પદાવલિ.original_type);
      જો (locations)
	locations->safe_ધકેલો (પદાવલિ.get_location ());
      જો (++idx < 6
	  && sizeof_arg != ખાલી
	  && (પદાવલિ.original_code == SIZEOF_પદાવલિ
	      || પદાવલિ.original_code == PAREN_SIZEOF_પદાવલિ))
	{
	  sizeof_arg[idx] = c_last_sizeof_arg;
	  sizeof_arg_loc[idx] = c_last_sizeof_loc;
	}
    }
  જો (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  પાછા ret;
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

સ્થિર શૂન્ય
c_parser_objc_class_definition (c_parser *parser, વૃક્ષ attributes)
{
  તાર્કિક iface_p;
  વૃક્ષ id1;
  વૃક્ષ superclass;
  જો (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = સાચું;
  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = ખોટું;
  નહીંતર
    gcc_unreachable ();

  c_parser_consume_token (parser);
  જો (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      પાછા;
    }
  id1 = c_parser_peek_token (parser)->કિંમત;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      વૃક્ષ id2;
      વૃક્ષ proto = NULL_વૃક્ષ;
      matching_parens parens;
      parens.consume_open (parser);
      જો (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  જો (iface_p && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_વૃક્ષ;
	    }
	  નહીંતર
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	      પાછા;
	    }
	}
      નહીંતર
	{
	  id2 = c_parser_peek_token (parser)->કિંમત;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_found_close (parser);
      જો (!iface_p)
	{
	  objc_start_category_implementation (id1, id2);
	  પાછા;
	}
      જો (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_category_interface (id1, id2, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
      પાછા;
    }
  જો (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  પાછા;
	}
      superclass = c_parser_peek_token (parser)->કિંમત;
      c_parser_consume_token (parser);
    }
  નહીંતર
    superclass = NULL_વૃક્ષ;
  જો (iface_p)
    {
      વૃક્ષ proto = NULL_વૃક્ષ;
      જો (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_start_class_interface (id1, loc1, superclass, proto, attributes);
    }
  નહીંતર
    objc_start_class_implementation (id1, superclass);
  જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  જો (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      objc_finish_interface ();
    }
  નહીંતર
    {
      objc_continue_implementation ();
      પાછા;
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

સ્થિર શૂન્ય
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  જ્યારે (c_parser_next_token_is_not (parser, CPP_EOF))
    {
      વૃક્ષ decls;
      /* Parse any stray semicolon.  */
      જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  ચાલુ;
	}
      /* Stop if at the end of the instance variables.  */
      જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  તોડો;
	}
      /* Parse any objc-visibility-spec.  */
      જો (c_parser_next_token_is_keyword (parser, RID_AT_PRIVATE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PRIVATE);
	  ચાલુ;
	}
      નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PROTECTED);
	  ચાલુ;
	}
      નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_AT_PUBLIC))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PUBLIC);
	  ચાલુ;
	}
      નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_set_visibility (OBJC_IVAR_VIS_PACKAGE);
	  ચાલુ;
	}
      નહીંતર જો (c_parser_next_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, ખાલી, NULL_વૃક્ષ);
	  ચાલુ;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, ખાલી);
      જો (decls == ખાલી)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  જો (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_SQUARE)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = ખોટું;
	  ચાલુ;
	}
      નહીંતર
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  વૃક્ષ ivar = nreverse (decls);
	  માટે (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_add_instance_variable (copy_ગાંઠ (ivar));
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

સ્થિર શૂન્ય
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  જ્યારે (સાચું)
    {
      વૃક્ષ id;
      જો (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);
	  parser->error = ખોટું;
	  પાછા;
	}
      id = c_parser_peek_token (parser)->કિંમત;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

સ્થિર શૂન્ય
c_parser_objc_alias_declaration (c_parser *parser)
{
  વૃક્ષ id1, id2;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  જો (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);
      પાછા;
    }
  id1 = c_parser_peek_token (parser)->કિંમત;
  c_parser_consume_token (parser);
  જો (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);
      પાછા;
    }
  id2 = c_parser_peek_token (parser)->કિંમત;
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

સ્થિર શૂન્ય
c_parser_objc_protocol_definition (c_parser *parser, વૃક્ષ attributes)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  જો (c_parser_next_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      પાછા;
    }
  જો (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      જ્યારે (સાચું)
	{
	  વૃક્ષ id;
	  જો (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      તોડો;
	    }
	  id = c_parser_peek_token (parser)->કિંમત;
	  objc_declare_protocol (id, attributes);
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  નહીંતર
	    તોડો;
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  નહીંતર
    {
      વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
      વૃક્ષ proto = NULL_વૃક્ષ;
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = સાચું;
      objc_start_protocol (id, proto, attributes);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_END, "expected %<@end%>");
      parser->objc_pq_context = ખોટું;
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
સ્થિર અંતઃરેખ તાર્કિક
c_parser_objc_method_type (c_parser *parser)
{
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_PLUS:
      c_parser_consume_token (parser);
      પાછા સાચું;
    સ્થિતિ CPP_MINUS:
      c_parser_consume_token (parser);
      પાછા ખોટું;
    મૂળભૂત:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

સ્થિર શૂન્ય
c_parser_objc_method_definition (c_parser *parser)
{
  તાર્કિક is_class_method = c_parser_objc_method_type (parser);
  વૃક્ષ decl, attributes = NULL_વૃક્ષ, પદાવલિ = NULL_વૃક્ષ;
  parser->objc_pq_context = સાચું;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    &પદાવલિ);
  જો (decl == error_mark_ગાંઠ)
    પાછા;  /* Bail here. */

  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  જો (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      પાછા;
    }

  parser->objc_pq_context = ખોટું;
  જો (objc_start_method_definition (is_class_method, decl, attributes, પદાવલિ))
    {
      add_stmt (c_parser_compound_statement (parser));
      objc_finish_method_definition (current_function_decl);
    }
  નહીંતર
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

સ્થિર શૂન્ય
c_parser_objc_methodprotolist (c_parser *parser)
{
  જ્યારે (સાચું)
    {
      /* The list is terminated by @end.  */
      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  તોડો;
	સ્થિતિ CPP_PLUS:
	સ્થિતિ CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  તોડો;
	સ્થિતિ CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, ખાલી, NULL_વૃક્ષ);
	  તોડો;
	સ્થિતિ CPP_EOF:
	  પાછા;
	મૂળભૂત:
	  જો (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    પાછા;
	  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_set_method_opt (સાચું);
	      c_parser_consume_token (parser);
	    }
	  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_set_method_opt (ખોટું);
	      c_parser_consume_token (parser);
	    }
	  નહીંતર
	    c_parser_declaration_or_fndef (parser, ખોટું, ખોટું, સાચું,
					   ખોટું, સાચું, ખોટું);
	  તોડો;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

સ્થિર શૂન્ય
c_parser_objc_methodproto (c_parser *parser)
{
  તાર્કિક is_class_method = c_parser_objc_method_type (parser);
  વૃક્ષ decl, attributes = NULL_વૃક્ષ;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = સાચું;
  decl = c_parser_objc_method_decl (parser, is_class_method, &attributes,
				    ખાલી);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = ખોટું;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  જો (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      પાછા;
    }

  જો (decl != error_mark_ગાંઠ)
    objc_add_method_declaration (is_class_method, decl, attributes);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

સ્થિર તાર્કિક
c_parser_objc_maybe_method_attributes (c_parser* parser, વૃક્ષ* attributes)
{
  તાર્કિક bad = ખોટું;
  જો (*attributes)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *attributes = NULL_વૃક્ષ;
      bad = સાચું;
    }

  જો (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    *attributes = c_parser_gnu_attributes (parser);

  /* If there were no attributes here, just report any earlier error.  */
  જો (*attributes == NULL_વૃક્ષ || bad)
    પાછા bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  જો (c_parser_next_token_is (parser, CPP_SEMICOLON)
      || c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    પાછા bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  પાછા સાચું;
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

સ્થિર વૃક્ષ
c_parser_objc_method_decl (c_parser *parser, તાર્કિક is_class_method,
			   વૃક્ષ *attributes, વૃક્ષ *પદાવલિ)
{
  વૃક્ષ type = NULL_વૃક્ષ;
  વૃક્ષ sel;
  વૃક્ષ parms = NULL_વૃક્ષ;
  તાર્કિક ellipsis = ખોટું;
  તાર્કિક attr_err = ખોટું;

  *attributes = NULL_વૃક્ષ;
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
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
  જો (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      વૃક્ષ tsel = sel;
      વૃક્ષ list = NULL_વૃક્ષ;
      જ્યારે (સાચું)
	{
	  વૃક્ષ atype = NULL_વૃક્ષ, id, keyworddecl;
	  વૃક્ષ param_attr = NULL_વૃક્ષ;
	  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    તોડો;
	  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  જો (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_attributes (parser);
	  જો (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      પાછા error_mark_ગાંઠ;
	    }
	  id = c_parser_peek_token (parser)->કિંમત;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  જો (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    તોડો;
	}

      attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_ગાંઠ (વૃક્ષ_LIST);
      જ્યારે (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  સંરચના c_parm *parm;
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = સાચું;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_method_attributes
						(parser, attributes) ;
	      તોડો;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_વૃક્ષ, ખોટું);
	  જો (parm == ખાલી)
	    તોડો;
	  parms = chainon (parms,
			   build_વૃક્ષ_list (NULL_વૃક્ષ, grokparm (parm, પદાવલિ)));
	}
      sel = list;
    }
  નહીંતર
    attr_err |= c_parser_objc_maybe_method_attributes (parser, attributes) ;

  જો (sel == ખાલી)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      પાછા error_mark_ગાંઠ;
    }

  જો (attr_err)
    પાછા error_mark_ગાંઠ;

  પાછા objc_build_method_signature (is_class_method, type, sel, parms, ellipsis);
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

સ્થિર વૃક્ષ
c_parser_objc_type_name (c_parser *parser)
{
  વૃક્ષ quals = NULL_વૃક્ષ;
  સંરચના c_type_name *type_name = ખાલી;
  વૃક્ષ type = NULL_વૃક્ષ;
  જ્યારે (સાચું)
    {
      c_token *token = c_parser_peek_token (parser);
      જો (token->type == CPP_KEYWORD
	  && (token->keyword == RID_IN
	      || token->keyword == RID_OUT
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_વૃક્ષ_list (NULL_વૃક્ષ, token->કિંમત), quals);
	  c_parser_consume_token (parser);
	}
      નહીંતર
	તોડો;
    }
  જો (c_parser_next_tokens_start_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  જો (type_name)
    type = groktypename (type_name, ખાલી, ખાલી);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  જો (type == error_mark_ગાંઠ)
    type = NULL_વૃક્ષ;

  પાછા build_વૃક્ષ_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

સ્થિર વૃક્ષ
c_parser_objc_protocol_refs (c_parser *parser)
{
  વૃક્ષ list = NULL_વૃક્ષ;
  gcc_assert (c_parser_next_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  જ્યારે (સાચું)
    {
      વૃક્ષ id;
      જો (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  તોડો;
	}
      id = c_parser_peek_token (parser)->કિંમત;
      list = chainon (list, build_વૃક્ષ_list (NULL_વૃક્ષ, id));
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  પાછા list;
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

સ્થિર શૂન્ય
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  વૃક્ષ stmt;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  જ્યારે (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      સંરચના c_parm *parm;
      વૃક્ષ parameter_declaration = error_mark_ગાંઠ;
      તાર્કિક seen_open_paren = ખોટું;

      c_parser_consume_token (parser);
      matching_parens parens;
      જો (!parens.require_open (parser))
	seen_open_paren = સાચું;
      જો (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_વૃક્ષ;
	}
      નહીંતર
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_વૃક્ષ, ખોટું);
	  જો (parm == ખાલી)
	    parameter_declaration = error_mark_ગાંઠ;
	  નહીંતર
	    parameter_declaration = grokparm (parm, ખાલી);
	}
      જો (seen_open_paren)
	parens.require_close (parser);
      નહીંતર
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      જો (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  જો (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
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

સ્થિર શૂન્ય
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  વૃક્ષ પદાવલિ, stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      સંરચના c_પદાવલિ ce = c_parser_expression (parser);
      ce = convert_lvalue_to_rvalue (loc, ce, ખોટું, ખોટું);
      પદાવલિ = ce.કિંમત;
      પદાવલિ = c_fully_fold (પદાવલિ, ખોટું, ખાલી);
      parens.skip_until_found_close (parser);
    }
  નહીંતર
    પદાવલિ = error_mark_ગાંઠ;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, પદાવલિ, stmt);
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

સ્થિર વૃક્ષ
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  વૃક્ષ કિંમત = token->કિંમત;
  જો (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      પાછા કિંમત;
    }
  જો (token->type != CPP_KEYWORD)
    પાછા NULL_વૃક્ષ;
  પસંદગી (token->keyword)
    {
    સ્થિતિ RID_ENUM:
    સ્થિતિ RID_STRUCT:
    સ્થિતિ RID_UNION:
    સ્થિતિ RID_IF:
    સ્થિતિ RID_ELSE:
    સ્થિતિ RID_WHILE:
    સ્થિતિ RID_DO:
    સ્થિતિ RID_FOR:
    સ્થિતિ RID_SWITCH:
    સ્થિતિ RID_CASE:
    સ્થિતિ RID_DEFAULT:
    સ્થિતિ RID_BREAK:
    સ્થિતિ RID_CONTINUE:
    સ્થિતિ RID_RETURN:
    સ્થિતિ RID_GOTO:
    સ્થિતિ RID_ASM:
    સ્થિતિ RID_SIZEOF:
    સ્થિતિ RID_TYPEOF:
    સ્થિતિ RID_TYPEOF_UNQUAL:
    સ્થિતિ RID_ALIGNOF:
    સ્થિતિ RID_UNSIGNED:
    સ્થિતિ RID_LONG:
    સ્થિતિ RID_CONST:
    સ્થિતિ RID_SHORT:
    સ્થિતિ RID_VOLATILE:
    સ્થિતિ RID_SIGNED:
    સ્થિતિ RID_RESTRICT:
    સ્થિતિ RID_COMPLEX:
    સ્થિતિ RID_IN:
    સ્થિતિ RID_OUT:
    સ્થિતિ RID_INOUT:
    સ્થિતિ RID_BYCOPY:
    સ્થિતિ RID_BYREF:
    સ્થિતિ RID_ONEWAY:
    સ્થિતિ RID_INT:
    સ્થિતિ RID_CHAR:
    સ્થિતિ RID_FLOAT:
    સ્થિતિ RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    સ્થિતિ RID_VOID:
    સ્થિતિ RID_BOOL:
    સ્થિતિ RID_ATOMIC:
    સ્થિતિ RID_AUTO_TYPE:
    સ્થિતિ RID_INT_N_0:
    સ્થિતિ RID_INT_N_1:
    સ્થિતિ RID_INT_N_2:
    સ્થિતિ RID_INT_N_3:
      c_parser_consume_token (parser);
      પાછા કિંમત;
    મૂળભૂત:
      પાછા NULL_વૃક્ષ;
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

સ્થિર વૃક્ષ
c_parser_objc_selector_arg (c_parser *parser)
{
  વૃક્ષ sel = c_parser_objc_selector (parser);
  વૃક્ષ list = NULL_વૃક્ષ;
  જો (sel
      && c_parser_next_token_is_not (parser, CPP_COLON)
      && c_parser_next_token_is_not (parser, CPP_SCOPE))
    પાછા sel;
  જ્યારે (સાચું)
    {
      જો (c_parser_next_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_વૃક્ષ_list (sel, NULL_વૃક્ષ));
	  list = chainon (list, build_વૃક્ષ_list (NULL_વૃક્ષ, NULL_વૃક્ષ));
	}
      નહીંતર
	{
	  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    પાછા list;
	  list = chainon (list, build_વૃક્ષ_list (sel, NULL_વૃક્ષ));
	}
      sel = c_parser_objc_selector (parser);
      જો (!sel
	  && c_parser_next_token_is_not (parser, CPP_COLON)
	  && c_parser_next_token_is_not (parser, CPP_SCOPE))
	તોડો;
    }
  પાછા list;
}

/* Parse an objc-receiver.

   objc-receiver:
     expression
     class-name
     type-name
*/

સ્થિર વૃક્ષ
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  જો (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_kind == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME))
    {
      વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
      c_parser_consume_token (parser);
      પાછા objc_get_class_reference (id);
    }
  સંરચના c_પદાવલિ ce = c_parser_expression (parser);
  ce = convert_lvalue_to_rvalue (loc, ce, ખોટું, ખોટું);
  પાછા c_fully_fold (ce.કિંમત, ખોટું, ખાલી);
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

સ્થિર વૃક્ષ
c_parser_objc_message_args (c_parser *parser)
{
  વૃક્ષ sel = c_parser_objc_selector (parser);
  વૃક્ષ list = NULL_વૃક્ષ;
  જો (sel && c_parser_next_token_is_not (parser, CPP_COLON))
    પાછા sel;
  જ્યારે (સાચું)
    {
      વૃક્ષ keywordexpr;
      જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	પાછા error_mark_ગાંઠ;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_વૃક્ષ_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      જો (!sel && c_parser_next_token_is_not (parser, CPP_COLON))
	તોડો;
    }
  પાછા list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

સ્થિર વૃક્ષ
c_parser_objc_keywordexpr (c_parser *parser)
{
  વૃક્ષ ret;
  vec<વૃક્ષ, va_gc> *પદાવલિ_list = c_parser_પદાવલિ_list (parser, સાચું, સાચું,
						ખાલી, ખાલી, ખાલી, ખાલી);
  જો (vec_safe_length (પદાવલિ_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*પદાવલિ_list)[0];
    }
  નહીંતર
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_વૃક્ષ_list_vec (પદાવલિ_list);
    }
  release_વૃક્ષ_vector (પદાવલિ_list);
  પાછા ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
સ્થિર તાર્કિક
c_parser_objc_diagnose_bad_element_prefix (c_parser *parser,
					   સંરચના c_declspecs *specs)
{
  જો (!specs->declspecs_seen_p || specs->non_sc_seen_p
      || specs->typespec_kind != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_to_end_of_block_or_statement (parser);
      પાછા સાચું;
    }
  પાછા ખોટું;
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
સ્થિર શૂન્ય
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  તાર્કિક syntax_error = ખોટું;
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_start = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = સાચું;

      /* Allow @property (), with a warning.  */
      location_t attr_end = c_parser_peek_token (parser)->location;

      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_end, attr_start, attr_end);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      નહીંતર
	જ્યારે (સાચું)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_start = token->location;
	    attr_end = get_finish (token->location);
	    location_t attr_comb = make_location (attr_start, attr_start,
						  attr_end);

	    જો (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		જો (token->type == CPP_CLOSE_PAREN)
		  તોડો;
		c_parser_consume_token (parser);
		ચાલુ;
	      }

	    વૃક્ષ attr_name = NULL_વૃક્ષ;
	    ગણના rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    તાર્કિક add_at = ખોટું;
	    જો (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		જો (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->કિંમત;
		    add_at = સાચું;
		  }
		નહીંતર
		  attr_name = ridpointers[(પૂર્ણાંક)keyword];
	      }
	    નહીંતર જો (token->type == CPP_NAME)
	      attr_name = token->કિંમત;
	    c_parser_consume_token (parser);

	    ગણના objc_property_attribute_kind prop_kind
	      = objc_prop_attr_kind_for_rid (keyword);
	    property_attribute_info *prop
	      = નવું property_attribute_info (attr_name, attr_comb, prop_kind);
	    prop_attr_list.safe_ધકેલો (prop);

	    વૃક્ષ meth_name;
	    પસંદગી (prop->prop_kind)
	      {
	      મૂળભૂત: તોડો;
	      સ્થિતિ OBJC_PROPERTY_ATTR_UNKNOWN:
		જો (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    add_at ? "@" : "", IDENTIFIER_POINTER (attr_name));
		નહીંતર
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = સાચું;
		તોડો;

	      સ્થિતિ OBJC_PROPERTY_ATTR_GETTER:
	      સ્થિતિ OBJC_PROPERTY_ATTR_SETTER:
		જો (c_parser_next_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = સાચું;
		    તોડો;
		  }
		token = c_parser_peek_token (parser);
		attr_end = token->location;
		c_parser_consume_token (parser); /* eat the = */
		જો (c_parser_next_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_end, attr_start, attr_end);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = સાચું;
		    તોડો;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_end = get_finish (token->location);
		meth_name = token->કિંમત;
		c_parser_consume_token (parser);
		જો (prop->prop_kind == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    જો (c_parser_next_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_end, attr_start,
						   attr_end);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = સાચું;
		      }
		    નહીંતર
		      {
			attr_end = get_finish (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		  }
		નહીંતર
		  attr_comb = make_location (attr_start, attr_start,
					       attr_end);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		તોડો;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  નહીંતર
	    તોડો;
	}
      parser->objc_property_attr_context = ખોટું;

      જો (syntax_error && c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      નહીંતર
	syntax_error = ખોટું, parens.skip_until_found_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  વૃક્ષ properties = c_parser_struct_declaration (parser, ખાલી);

  જો (properties == error_mark_ગાંઠ)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);
  નહીંતર
    {
      જો (properties == NULL_વૃક્ષ)
	c_parser_error (parser, "expected identifier");
      નહીંતર
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  માટે (; properties; properties = વૃક્ષ_CHAIN (properties))
	    objc_add_property_declaration (loc, copy_ગાંઠ (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  જ્યારે (!prop_attr_list.is_empty())
    delete prop_attr_list.કાઢો ();
  prop_attr_list.release ();
  parser->error = ખોટું;
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
સ્થિર શૂન્ય
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  વૃક્ષ list = NULL_વૃક્ષ;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  જ્યારે (સાચું)
    {
      વૃક્ષ property, ivar;
      જો (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = ખોટું;
	  પાછા;
	}
      property = c_parser_peek_token (parser)->કિંમત;
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);
	      parser->error = ખોટું;
	      પાછા;
	    }
	  ivar = c_parser_peek_token (parser)->કિંમત;
	  c_parser_consume_token (parser);
	}
      નહીંતર
	ivar = NULL_વૃક્ષ;
      list = chainon (list, build_વૃક્ષ_list (ivar, property));
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
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
સ્થિર શૂન્ય
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  વૃક્ષ list = NULL_વૃક્ષ;
  location_t loc;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  જ્યારે (સાચું)
    {
      વૃક્ષ property;
      જો (c_parser_next_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);
	  parser->error = ખોટું;
	  પાછા;
	}
      property = c_parser_peek_token (parser)->કિંમત;
      list = chainon (list, build_વૃક્ષ_list (NULL_વૃક્ષ, property));
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_add_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

સ્થિર તાર્કિક
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  પાછા સાચું;
}

/* Parse a pragma GCC novector.  */

સ્થિર તાર્કિક
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
  પાછા સાચું;
}

/* Parse a pragma GCC unroll.  */

સ્થિર unsigned short
c_parser_pragma_unroll (c_parser *parser)
{
  unsigned short unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  વૃક્ષ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
  mark_exp_read (પદાવલિ);
  પદાવલિ = c_fully_fold (પદાવલિ, ખોટું, ખાલી);
  HOST_WIDE_INT lunroll = 0;
  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (પદાવલિ))
      || વૃક્ષ_CODE (પદાવલિ) != INTEGER_CST
      || (lunroll = વૃક્ષ_to_shwi (પદાવલિ)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  નહીંતર
    {
      unroll = (unsigned short)lunroll;
      જો (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_to_pragma_eol (parser);
  પાછા unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

સ્થિર તાર્કિક
c_parser_pragma (c_parser *parser, ગણના pragma_context context, તાર્કિક *if_p,
		 વૃક્ષ before_labels)
{
  unsigned પૂર્ણાંક id;
  અચલ અક્ષર *construct = ખાલી;

  આગત_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_kind;
  gcc_assert (id != PRAGMA_NONE);
  જો (parser->omp_for_parse_state
      && parser->omp_for_parse_state->in_intervening_code
      && id >= PRAGMA_OMP__START_ && id <= PRAGMA_OMP__LAST_
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	આગત_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = સાચું;
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
      પાછા ખોટું;
    }

  પસંદગી (id)
    {
    સ્થિતિ PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OACC_ENTER_DATA:
      જો (context != pragma_compound)
	{
	  construct = "acc enter data";
	in_compound:
	  જો (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
	      પાછા સાચું;
	    }
	  જાઓ bad_stmt;
	}
      c_parser_oacc_enter_exit_data (parser, સાચું);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OACC_EXIT_DATA:
      જો (context != pragma_compound)
	{
	  construct = "acc exit data";
	  જાઓ in_compound;
	}
      c_parser_oacc_enter_exit_data (parser, ખોટું);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OACC_ROUTINE:
      જો (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
	  પાછા ખોટું;
	}
      c_parser_oacc_routine (parser, context);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OACC_UPDATE:
      જો (context != pragma_compound)
	{
	  construct = "acc update";
	  જાઓ in_compound;
	}
      c_parser_oacc_update (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_BARRIER:
      જો (context != pragma_compound)
	{
	  construct = "omp barrier";
	  જાઓ in_compound;
	}
      c_parser_omp_barrier (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_DEPOBJ:
      જો (context != pragma_compound)
	{
	  construct = "omp depobj";
	  જાઓ in_compound;
	}
      c_parser_omp_depobj (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_FLUSH:
      જો (context != pragma_compound)
	{
	  construct = "omp flush";
	  જાઓ in_compound;
	}
      c_parser_omp_flush (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_INTEROP:
      જો (context != pragma_compound)
	{
	  construct = "omp interop";
	  જાઓ in_compound;
	}
      c_parser_omp_interop (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_TASKWAIT:
      જો (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  જાઓ in_compound;
	}
      c_parser_omp_taskwait (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_TASKYIELD:
      જો (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  જાઓ in_compound;
	}
      c_parser_omp_taskyield (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_CANCEL:
      જો (context != pragma_compound)
	{
	  construct = "omp cancel";
	  જાઓ in_compound;
	}
      c_parser_omp_cancel (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_CANCELLATION_POINT:
      પાછા c_parser_omp_cancellation_point (parser, context);

    સ્થિતિ PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_TARGET:
      પાછા c_parser_omp_target (parser, context, if_p);

    સ્થિતિ PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_END:
      c_parser_omp_end (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_SCAN:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_DECLARE:
      પાછા c_parser_omp_declare (parser, context);

    સ્થિતિ PRAGMA_OMP_REQUIRES:
      જો (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
	  પાછા ખોટું;
	}
      c_parser_omp_requires (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_ASSUMES:
      જો (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
	  પાછા ખોટું;
	}
      c_parser_omp_assumes (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      પાછા સાચું;

    સ્થિતિ PRAGMA_OMP_ERROR:
      પાછા c_parser_omp_error (parser, context);

    સ્થિતિ PRAGMA_OMP_ORDERED:
      પાછા c_parser_omp_ordered (parser, context, if_p);

    સ્થિતિ PRAGMA_NOVECTOR:
    સ્થિતિ PRAGMA_UNROLL:
    સ્થિતિ PRAGMA_IVDEP:
      {
	તાર્કિક novector = ખોટું;
	unsigned short unroll = 0;
	તાર્કિક ivdep = ખોટું;

	પસંદગી (id)
	  {
	  સ્થિતિ PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    તોડો;
	  સ્થિતિ PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    તોડો;
	  સ્થિતિ PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    તોડો;
	  મૂળભૂત:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	તાર્કિક has_more = tok->type == CPP_PRAGMA;
	જ્યારે (has_more)
	  {
	    પસંદગી (tok->pragma_kind)
	      {
	      સ્થિતિ PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		તોડો;
	      સ્થિતિ PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		તોડો;
	      સ્થિતિ PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		તોડો;
	      મૂળભૂત:
		has_more = ખોટું;
		તોડો;
	      }
	    tok = c_parser_peek_token (parser);
	    has_more = has_more && tok->type == CPP_PRAGMA;
	  }
	જો (!c_parser_next_token_is_keyword (parser, RID_FOR)
	    && !c_parser_next_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_next_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    પાછા ખોટું;
	  }
	જો (c_parser_next_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	નહીંતર
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      પાછા સાચું;

    સ્થિતિ PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
      પાછા ખોટું;

    સ્થિતિ PRAGMA_OACC_WAIT:
      જો (context != pragma_compound)
	{
	  construct = "acc wait";
	  જાઓ in_compound;
	}
	/* FALL THROUGH.  */

    મૂળભૂત:
      જો (id < PRAGMA_FIRST_EXTERNAL)
	{
	  જો (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_found (parser, CPP_PRAGMA_EOL, ખાલી);
	      પાછા ખોટું;
	    }
	  c_parser_omp_construct (parser, if_p);
	  પાછા સાચું;
	}
      તોડો;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = સાચું;
  c_parser_skip_to_pragma_eol (parser);

  પાછા ખોટું;
}

/* The interface the pragma parsers have to the lexer.  */

ગણના cpp_ttype
pragma_lex (વૃક્ષ *કિંમત, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  ગણના cpp_ttype ret = tok->type;

  *કિંમત = tok->કિંમત;
  જો (loc)
    *loc = tok->location;

  જો (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  નહીંતર જો (ret == CPP_STRING)
    *કિંમત = c_parser_string_literal (the_parser, ખોટું, ખોટું).કિંમત;
  નહીંતર
    {
      જો (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  પાછા ret;
}

શૂન્ય
pragma_lex_discard_to_eol ()
{
  cpp_ttype type;
  કરો
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } જ્યારે (type != CPP_PRAGMA_EOL);
}

સ્થિર શૂન્ય
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  વૃક્ષ name = ખાલી;

  parser->lex_joined_string = સાચું;
  c_parser_consume_pragma (parser);
  જો (c_parser_next_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->કિંમત;
      c_parser_consume_token (parser);
    }
  નહીંતર
    c_parser_error (parser, "expected string literal");
  c_parser_skip_to_pragma_eol (parser);
  parser->lex_joined_string = ખોટું;

  જો (name)
    c_common_pch_pragma (parse_in, વૃક્ષ_STRING_POINTER (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

સ્થિર pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  જો (c_parser_next_token_is_keyword (parser, RID_AUTO))
    result = PRAGMA_OACC_CLAUSE_AUTO;
  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_FOR))
    result = PRAGMA_OMP_CLAUSE_FOR;
  નહીંતર જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      પસંદગી (p[0])
	{
	સ્થિતિ 'a':
	  જો (!strcmp ("affinity", p))
	    result = PRAGMA_OMP_CLAUSE_AFFINITY;
	  નહીંતર જો (!strcmp ("aligned", p))
	    result = PRAGMA_OMP_CLAUSE_ALIGNED;
	  નહીંતર જો (!strcmp ("allocate", p))
	    result = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  નહીંતર જો (!strcmp ("async", p))
	    result = PRAGMA_OACC_CLAUSE_ASYNC;
	  નહીંતર જો (!strcmp ("attach", p))
	    result = PRAGMA_OACC_CLAUSE_ATTACH;
	  તોડો;
	સ્થિતિ 'b':
	  જો (!strcmp ("bind", p))
	    result = PRAGMA_OMP_CLAUSE_BIND;
	  તોડો;
	સ્થિતિ 'c':
	  જો (!strcmp ("collapse", p))
	    result = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  નહીંતર જો (!strcmp ("copy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  નહીંતર જો (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
	  નહીંતર જો (!strcmp ("copyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
          નહીંતર જો (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  નહીંતર જો (!strcmp ("create", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  તોડો;
	સ્થિતિ 'd':
	  જો (!strcmp ("defaultmap", p))
	    result = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  નહીંતર જો (!strcmp ("delete", p))
	    result = PRAGMA_OACC_CLAUSE_DELETE;
	  નહીંતર જો (!strcmp ("depend", p))
	    result = PRAGMA_OMP_CLAUSE_DEPEND;
	  નહીંતર જો (!strcmp ("destroy", p))
	    result = PRAGMA_OMP_CLAUSE_DESTROY;
	  નહીંતર જો (!strcmp ("detach", p))
	    result = PRAGMA_OACC_CLAUSE_DETACH;
	  નહીંતર જો (!strcmp ("device", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE;
	  નહીંતર જો (!strcmp ("deviceptr", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  નહીંતર જો (!strcmp ("device_resident", p))
	    result = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  નહીંતર જો (!strcmp ("device_type", p))
	    result = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  નહીંતર જો (!strcmp ("dist_schedule", p))
	    result = PRAGMA_OMP_CLAUSE_DIST_SCHEDULE;
	  નહીંતર જો (!strcmp ("doacross", p))
	    result = PRAGMA_OMP_CLAUSE_DOACROSS;
	  નહીંતર જો (!strcmp ("dyn_groupprivate", p))
	    result = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  તોડો;
	સ્થિતિ 'e':
	  જો (!strcmp ("enter", p))
	    result = PRAGMA_OMP_CLAUSE_ENTER;
	  તોડો;
	સ્થિતિ 'f':
	  જો (!strcmp ("filter", p))
	    result = PRAGMA_OMP_CLAUSE_FILTER;
	  નહીંતર જો (!strcmp ("final", p))
	    result = PRAGMA_OMP_CLAUSE_FINAL;
	  નહીંતર જો (!strcmp ("finalize", p))
	    result = PRAGMA_OACC_CLAUSE_FINALIZE;
	  નહીંતર જો (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  નહીંતર જો (!strcmp ("from", p))
	    result = PRAGMA_OMP_CLAUSE_FROM;
	  નહીંતર જો (!strcmp ("full", p))
	    result = PRAGMA_OMP_CLAUSE_FULL;
	  તોડો;
	સ્થિતિ 'g':
	  જો (!strcmp ("gang", p))
	    result = PRAGMA_OACC_CLAUSE_GANG;
	  નહીંતર જો (!strcmp ("grainsize", p))
	    result = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  તોડો;
	સ્થિતિ 'h':
	  જો (!strcmp ("has_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  નહીંતર જો (!strcmp ("hint", p))
	    result = PRAGMA_OMP_CLAUSE_HINT;
	  નહીંતર જો (!strcmp ("host", p))
	    result = PRAGMA_OACC_CLAUSE_HOST;
	  તોડો;
	સ્થિતિ 'i':
	  જો (!strcmp ("if_present", p))
	    result = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  નહીંતર જો (!strcmp ("in_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_IN_REDUCTION;
	  નહીંતર જો (!strcmp ("inbranch", p))
	    result = PRAGMA_OMP_CLAUSE_INBRANCH;
	  નહીંતર જો (!strcmp ("independent", p))
	    result = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  નહીંતર જો (!strcmp ("indirect", p))
	    result = PRAGMA_OMP_CLAUSE_INDIRECT;
	  નહીંતર જો (!strcmp ("init", p))
	    result = PRAGMA_OMP_CLAUSE_INIT;
	  નહીંતર જો (!strcmp ("is_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  નહીંતર જો (!strcmp ("interop", p))
	    result = PRAGMA_OMP_CLAUSE_INTEROP;
	  તોડો;
	સ્થિતિ 'l':
	  જો (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  નહીંતર જો (!strcmp ("linear", p))
	    result = PRAGMA_OMP_CLAUSE_LINEAR;
	  નહીંતર જો (!strcmp ("link", p))
	    result = PRAGMA_OMP_CLAUSE_LINK;
	  નહીંતર જો (!strcmp ("local", p))
	    result = PRAGMA_OMP_CLAUSE_LOCAL;
	  તોડો;
	સ્થિતિ 'm':
	  જો (!strcmp ("map", p))
	    result = PRAGMA_OMP_CLAUSE_MAP;
	  નહીંતર જો (!strcmp ("mergeable", p))
	    result = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  તોડો;
	સ્થિતિ 'n':
	  જો (!strcmp ("no_create", p))
	    result = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  નહીંતર જો (!strcmp ("nocontext", p))
	    result = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  નહીંતર જો (!strcmp ("nogroup", p))
	    result = PRAGMA_OMP_CLAUSE_NOGROUP;
	  નહીંતર જો (!strcmp ("nohost", p))
	    result = PRAGMA_OACC_CLAUSE_NOHOST;
	  નહીંતર જો (!strcmp ("nontemporal", p))
	    result = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  નહીંતર જો (!strcmp ("notinbranch", p))
	    result = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  નહીંતર જો (!strcmp ("novariants", p))
	    result = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  નહીંતર જો (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  નહીંતર જો (!strcmp ("num_gangs", p))
	    result = PRAGMA_OACC_CLAUSE_અંક_GANGS;
	  નહીંતર જો (!strcmp ("num_tasks", p))
	    result = PRAGMA_OMP_CLAUSE_અંક_TASKS;
	  નહીંતર જો (!strcmp ("num_teams", p))
	    result = PRAGMA_OMP_CLAUSE_અંક_TEAMS;
	  નહીંતર જો (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_અંક_THREADS;
	  નહીંતર જો (!strcmp ("num_workers", p))
	    result = PRAGMA_OACC_CLAUSE_અંક_WORKERS;
	  તોડો;
	સ્થિતિ 'o':
	  જો (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  નહીંતર જો (!strcmp ("order", p))
	    result = PRAGMA_OMP_CLAUSE_ORDER;
	  તોડો;
	સ્થિતિ 'p':
	  જો (!strcmp ("parallel", p))
	    result = PRAGMA_OMP_CLAUSE_PARALLEL;
	  નહીંતર જો (!strcmp ("partial", p))
	    result = PRAGMA_OMP_CLAUSE_PARTIAL;
	  નહીંતર જો (!strcmp ("present", p))
	    result = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  નહીંતર જો (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    result = PRAGMA_OACC_CLAUSE_COPY;
	  નહીંતર જો (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    result = PRAGMA_OACC_CLAUSE_COPYIN;
	  નહીંતર જો (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    result = PRAGMA_OACC_CLAUSE_COPYOUT;
	  નહીંતર જો (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    result = PRAGMA_OACC_CLAUSE_CREATE;
	  નહીંતર જો (!strcmp ("priority", p))
	    result = PRAGMA_OMP_CLAUSE_PRIORITY;
	  નહીંતર જો (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  નહીંતર જો (!strcmp ("proc_bind", p))
	    result = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  તોડો;
	સ્થિતિ 'r':
	  જો (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  તોડો;
	સ્થિતિ 's':
	  જો (!strcmp ("safelen", p))
	    result = PRAGMA_OMP_CLAUSE_SAFELEN;
	  નહીંતર જો (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  નહીંતર જો (!strcmp ("sections", p))
	    result = PRAGMA_OMP_CLAUSE_SECTIONS;
	  નહીંતર જો (!strcmp ("self", p))
	    result = PRAGMA_OACC_CLAUSE_SELF;
	  નહીંતર જો (!strcmp ("seq", p))
	    result = PRAGMA_OACC_CLAUSE_SEQ;
	  નહીંતર જો (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  નહીંતર જો (!strcmp ("simd", p))
	    result = PRAGMA_OMP_CLAUSE_SIMD;
	  નહીંતર જો (!strcmp ("simdlen", p))
	    result = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  તોડો;
	સ્થિતિ 't':
	  જો (!strcmp ("task_reduction", p))
	    result = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  નહીંતર જો (!strcmp ("taskgroup", p))
	    result = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  નહીંતર જો (!strcmp ("thread_limit", p))
	    result = PRAGMA_OMP_CLAUSE_THREAD_LIMIT;
	  નહીંતર જો (!strcmp ("threads", p))
	    result = PRAGMA_OMP_CLAUSE_THREADS;
	  નહીંતર જો (!strcmp ("tile", p))
	    result = PRAGMA_OACC_CLAUSE_TILE;
	  નહીંતર જો (!strcmp ("to", p))
	    result = PRAGMA_OMP_CLAUSE_TO;
	  તોડો;
	સ્થિતિ 'u':
	  જો (!strcmp ("uniform", p))
	    result = PRAGMA_OMP_CLAUSE_UNIFORM;
	  નહીંતર જો (!strcmp ("untied", p))
	    result = PRAGMA_OMP_CLAUSE_UNTIED;
	  નહીંતર જો (!strcmp ("use", p))
	    result = PRAGMA_OMP_CLAUSE_USE;
	  નહીંતર જો (!strcmp ("use_device", p))
	    result = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  નહીંતર જો (!strcmp ("use_device_addr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  નહીંતર જો (!strcmp ("use_device_ptr", p))
	    result = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  નહીંતર જો (!strcmp ("uses_allocators", p))
	    result = PRAGMA_OMP_CLAUSE_USES_ALLOCATORS;
	  તોડો;
	સ્થિતિ 'v':
	  જો (!strcmp ("vector", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR;
	  નહીંતર જો (!strcmp ("vector_length", p))
	    result = PRAGMA_OACC_CLAUSE_VECTOR_LENGTH;
	  તોડો;
	સ્થિતિ 'w':
	  જો (!strcmp ("wait", p))
	    result = PRAGMA_OACC_CLAUSE_WAIT;
	  નહીંતર જો (!strcmp ("worker", p))
	    result = PRAGMA_OACC_CLAUSE_WORKER;
	  તોડો;
	}
    }

  જો (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  પાછા result;
}

/* Validate that a clause of the given type does not already exist.  */

સ્થિર શૂન્ય
check_no_duplicate_clause (વૃક્ષ clauses, ગણના omp_clause_code code,
			   અચલ અક્ષર *name)
{
  જો (વૃક્ષ c = omp_find_clause (clauses, code))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

સ્થિર વૃક્ષ
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, વૃક્ષ list)
{
  vec<વૃક્ષ, va_gc> *args;
  વૃક્ષ t, args_વૃક્ષ;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  args = c_parser_પદાવલિ_list (parser, ખોટું, સાચું, ખાલી, ખાલી, ખાલી, ખાલી);
  args_વૃક્ષ = build_વૃક્ષ_list_vec (args);

  માટે (t = args_વૃક્ષ; t; t = વૃક્ષ_CHAIN (t))
    {
      વૃક્ષ targ = વૃક્ષ_કિંમત (t);

      જો (targ != error_mark_ગાંઠ)
	{
	  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_ગાંઠ;
	    }
	  નહીંતર
	    {
	      વૃક્ષ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_વૃક્ષ_vector (args);
  parens.require_close (parser);
  પાછા list;
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

સંરચના omp_dim
{
  વૃક્ષ નીચલું_bound, length;
  location_t loc;
  તાર્કિક no_colon;
  omp_dim (વૃક્ષ lb, વૃક્ષ len, location_t lo, તાર્કિક nc)
  : નીચલું_bound (lb), length (len), loc (lo), no_colon (nc) {}
};

સ્થિર વૃક્ષ
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    ગણના omp_clause_code kind, વૃક્ષ list,
			    તાર્કિક map_lvalue = ખોટું)
{
  auto_vec<omp_dim> dims;
  તાર્કિક array_section_p;
  auto_vec<c_token> tokens;
  unsigned પૂર્ણાંક tokens_avail = 0;
  c_token *saved_tokens = ખાલી;

  જ્યારે (1)
    {
      વૃક્ષ t = NULL_વૃક્ષ;
      location_t tloc = c_parser_peek_token (parser)->location;

      જો (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  જો (c_parser_next_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
	    {
	      સંરચના c_પદાવલિ પદાવલિ;
	      જો (kind == OMP_CLAUSE_DEPEND
		  && c_parser_next_token_is_keyword (parser,
						     RID_OMP_ALL_MEMORY)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  પદાવલિ.કિંમત = ridpointers[RID_OMP_ALL_MEMORY];
		  c_parser_consume_token (parser);
		}
	      નહીંતર
		પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	      જો (પદાવલિ.કિંમત != error_mark_ગાંઠ)
		{
		  વૃક્ષ u = build_omp_clause (clause_loc, kind);
		  OMP_CLAUSE_DECL (u) = પદાવલિ.કિંમત;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      જો (c_parser_next_token_is_not (parser, CPP_COMMA))
		તોડો;

	      c_parser_consume_token (parser);
	      ચાલુ;
	    }

	  tokens.truncate (0);
	  unsigned પૂર્ણાંક nesting_depth = 0;
	  જ્યારે (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      પસંદગી (token->type)
		{
		સ્થિતિ CPP_EOF:
		સ્થિતિ CPP_PRAGMA_EOL:
		  તોડો;
		સ્થિતિ CPP_OPEN_BRACE:
		સ્થિતિ CPP_OPEN_PAREN:
		સ્થિતિ CPP_OPEN_SQUARE:
		  ++nesting_depth;
		  જાઓ add;
		સ્થિતિ CPP_CLOSE_BRACE:
		સ્થિતિ CPP_CLOSE_PAREN:
		સ્થિતિ CPP_CLOSE_SQUARE:
		  જો (nesting_depth-- == 0)
		    તોડો;
		  જાઓ add;
		સ્થિતિ CPP_COMMA:
		  જો (nesting_depth == 0)
		    તોડો;
		  જાઓ add;
		મૂળભૂત:
		add:
		  tokens.safe_ધકેલો (*token);
		  c_parser_consume_token (parser);
		  ચાલુ;
		}
	      તોડો;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, કદ (eof_token));
	  eof_token.type = CPP_EOF;
	  tokens.safe_ધકેલો (eof_token);
	  tokens.safe_ધકેલો (eof_token);

	  saved_tokens = parser->tokens;
	  tokens_avail = parser->tokens_avail;
	  parser->tokens = tokens.address ();
	  parser->tokens_avail = tokens.length ();
	}
      નહીંતર જો (map_lvalue
	       && (kind == OMP_CLAUSE_MAP
		   || kind == OMP_CLAUSE_TO
		   || kind == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  તાર્કિક save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = સાચું;
	  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  જો (પદાવલિ.કિંમત != error_mark_ગાંઠ)
	    mark_exp_read (પદાવલિ.કિંમત);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  વૃક્ષ decl = પદાવલિ.કિંમત;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  જો (વૃક્ષ_CODE (decl) == OMP_ARRAY_SECTION)
	    {
	      જ્યારે (વૃક્ષ_CODE (decl) == OMP_ARRAY_SECTION)
		{
		  વૃક્ષ નીચલું_bound = વૃક્ષ_OPERAND (decl, 1);
		  વૃક્ષ length = વૃક્ષ_OPERAND (decl, 2);
		  dims.safe_ધકેલો (omp_dim (નીચલું_bound, length, loc, ખોટું));
		  decl = વૃક્ષ_OPERAND (decl, 0);
		}

	      જ્યારે (વૃક્ષ_CODE (decl) == ARRAY_REF
		     || વૃક્ષ_CODE (decl) == INDIRECT_REF
		     || વૃક્ષ_CODE (decl) == COMPOUND_પદાવલિ)
		{
		  જો (વૃક્ષ_CODE (decl) == COMPOUND_પદાવલિ)
		    {
		      decl = વૃક્ષ_OPERAND (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  નહીંતર જો (વૃક્ષ_CODE (decl) == INDIRECT_REF)
		    {
		      dims.safe_ધકેલો (omp_dim (integer_zero_ગાંઠ,
					       integer_one_ગાંઠ, loc, સાચું));
		      decl = વૃક્ષ_OPERAND (decl, 0);
		    }
		  નહીંતર  /* ARRAY_REF. */
		    {
		      વૃક્ષ index = વૃક્ષ_OPERAND (decl, 1);
		      dims.safe_ધકેલો (omp_dim (index, integer_one_ગાંઠ, loc,
					       સાચું));
		      decl = વૃક્ષ_OPERAND (decl, 0);
		    }
		}

	      માટે (પૂર્ણાંક i = dims.length () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].નીચલું_bound,
						dims[i].length);
	    }
	  નહીંતર જો (વૃક્ષ_CODE (decl) == INDIRECT_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = વૃક્ષ_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_ગાંઠ,
					      integer_one_ગાંઠ);
	    }
	  નહીંતર જો (વૃક્ષ_CODE (decl) == ARRAY_REF)
	    {
	      વૃક્ષ idx = વૃક્ષ_OPERAND (decl, 1);

	      decl = વૃક્ષ_OPERAND (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_ગાંઠ);
	    }
	  નહીંતર જો (વૃક્ષ_CODE (decl) == NON_LVALUE_પદાવલિ
		   || CONVERT_પદાવલિ_P (decl))
	    decl = વૃક્ષ_OPERAND (decl, 0);

	  વૃક્ષ u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  જાઓ next_item;
	}

      જો (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->કિંમત);

	  જો (t == NULL_વૃક્ષ)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->કિંમત);
	      t = error_mark_ગાંઠ;
	    }

	  c_parser_consume_token (parser);
	}
      નહીંતર જો (c_parser_next_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).કિંમત;
      નહીંતર
	{
	  c_parser_error (parser, "expected identifier");
	  તોડો;
	}

      જો (t == error_mark_ગાંઠ)
	;
      નહીંતર જો (kind != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  પસંદગી (kind)
	    {
	    સ્થિતિ OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      જો (c_parser_peek_token (parser)->type != CPP_OPEN_SQUARE)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_ગાંઠ;
		  તોડો;
		}
	      /* FALLTHROUGH  */
	    સ્થિતિ OMP_CLAUSE_MAP:
	    સ્થિતિ OMP_CLAUSE_FROM:
	    સ્થિતિ OMP_CLAUSE_TO:
	    start_component_ref:
	      જ્યારે (c_parser_next_token_is (parser, CPP_DOT)
		     || c_parser_next_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  જો (c_parser_next_token_is (parser, CPP_DEREF))
		    {
		      c_પદાવલિ t_પદાવલિ;
		      t_પદાવલિ.કિંમત = t;
		      t_પદાવલિ.original_code = ERROR_MARK;
		      t_પદાવલિ.original_type = ખાલી;
		      set_c_પદાવલિ_source_range (&t_પદાવલિ, op_loc, op_loc);
		      t_પદાવલિ.m_decimal = 0;
		      t_પદાવલિ = convert_lvalue_to_rvalue (op_loc, t_પદાવલિ,
							 સાચું, ખોટું);
		      t = build_indirect_ref (op_loc, t_પદાવલિ.કિંમત, RO_ARROW);
		      arrow_loc = t_પદાવલિ.get_location ();
		    }
		  c_parser_consume_token (parser);
		  જો (!c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_ગાંઠ;
		      તોડો;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  વૃક્ષ ident = comp_tok->કિંમત;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    સ્થિતિ OMP_CLAUSE_AFFINITY:
	    સ્થિતિ OMP_CLAUSE_DEPEND:
	    સ્થિતિ OMP_CLAUSE_REDUCTION:
	    સ્થિતિ OMP_CLAUSE_IN_REDUCTION:
	    સ્થિતિ OMP_CLAUSE_TASK_REDUCTION:
	    સ્થિતિ OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = ખોટું;
	      dims.truncate (0);
	      જ્યારે (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  વૃક્ષ નીચલું_bound = NULL_વૃક્ષ, length = NULL_વૃક્ષ;
		  તાર્કિક no_colon = ખોટું;

		  c_parser_consume_token (parser);
		  જો (!c_parser_next_token_is (parser, CPP_COLON))
		    {
		      location_t પદાવલિ_loc
			= c_parser_peek_token (parser)->location;
		      c_પદાવલિ પદાવલિ = c_parser_expression (parser);
		      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ,
						       ખોટું, સાચું);
		      નીચલું_bound = પદાવલિ.કિંમત;
		      loc = પદાવલિ_loc;
		    }
		  જો (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
		    {
		      length = integer_one_ગાંઠ;
		      no_colon = સાચું;
		    }
		  નહીંતર
		    {
		      /* Look for `:'.  */
		      જો (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_ગાંઠ;
			  તોડો;
			}
		      array_section_p = સાચું;
		      જો (!c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
			{
			  location_t પદાવલિ_loc
			    = c_parser_peek_token (parser)->location;
			  c_પદાવલિ પદાવલિ = c_parser_expression (parser);
			  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ,
							   ખોટું, સાચું);
			  length = પદાવલિ.કિંમત;
			}
		    }
		  /* Look for the closing `]'.  */
		  જો (!c_parser_require (parser, CPP_CLOSE_SQUARE,
					 "expected %<]%>"))
		    {
		      t = error_mark_ગાંઠ;
		      તોડો;
		    }

		  dims.safe_ધકેલો (omp_dim (નીચલું_bound, length, loc, no_colon));
		}

	      જો (t != error_mark_ગાંઠ)
		{
		  જો ((kind == OMP_CLAUSE_MAP
		       || kind == OMP_CLAUSE_FROM
		       || kind == OMP_CLAUSE_TO)
		      && !array_section_p
		      && (c_parser_next_token_is (parser, CPP_DOT)
			  || c_parser_next_token_is (parser, CPP_DEREF)))
		    {
		      માટે (unsigned i = 0; i < dims.length (); i++)
			{
			  gcc_assert (dims[i].length == integer_one_ગાંઠ);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].નીચલું_bound);
			}
		      જાઓ start_component_ref;
		    }
		  નહીંતર
		    માટે (unsigned i = 0; i < dims.length (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].નીચલું_bound,
						   dims[i].length);
		}

	      જો ((kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_ગાંઠ
		  && parser->tokens_avail != 2)
		{
		  જો (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_ગાંઠ;
		    }
		  નહીંતર
		    {
		      parser->tokens = tokens.address ();
		      parser->tokens_avail = tokens.length ();

		      t = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
		      જો (t != error_mark_ગાંઠ && parser->tokens_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_ગાંઠ;
			}
		    }
		}
	      તોડો;
	    મૂળભૂત:
	      તોડો;
	    }

	  જો (t != error_mark_ગાંઠ)
	    {
	      વૃક્ષ u = build_omp_clause (clause_loc, kind);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      નહીંતર  /* kind == OMP_CLAUSE_ERROR */
	list = વૃક્ષ_cons (t, build_empty_stmt (tloc), list);

      જો (kind == OMP_CLAUSE_DEPEND || kind == OMP_CLAUSE_AFFINITY)
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}

    next_item:
      જો (c_parser_next_token_is_not (parser, CPP_COMMA))
	તોડો;

      c_parser_consume_token (parser);
    }

  પાછા list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

સ્થિર વૃક્ષ
c_parser_omp_var_list_parens (c_parser *parser, ગણના omp_clause_code kind,
			      વૃક્ષ list, તાર્કિક map_lvalue = ખોટું)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  જો (parser->in_omp_decl_attribute)
    {
      જો (kind)
	{
	  વૃક્ષ u = build_omp_clause (loc, kind);
	  OMP_CLAUSE_DECL (u) = parser->in_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  પાછા u;
	}
      નહીંતર
	પાછા વૃક્ષ_cons (parser->in_omp_decl_attribute, NULL_વૃક્ષ, list);
    }

  matching_parens parens;
  જો (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, kind, list, map_lvalue);
      parens.skip_until_found_close (parser);
    }
  પાછા list;
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

સ્થિર વૃક્ષ
c_parser_oacc_data_clause (c_parser *parser, pragma_omp_clause c_kind,
			   વૃક્ષ list)
{
  ગણના gomp_map_kind kind;
  પસંદગી (c_kind)
    {
    સ્થિતિ PRAGMA_OACC_CLAUSE_ATTACH:
      kind = GOMP_MAP_ATTACH;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_COPY:
      kind = GOMP_MAP_TOFROM;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_COPYIN:
      kind = GOMP_MAP_TO;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_COPYOUT:
      kind = GOMP_MAP_FROM;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_CREATE:
      kind = GOMP_MAP_ALLOC;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_DELETE:
      kind = GOMP_MAP_RELEASE;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_DETACH:
      kind = GOMP_MAP_DETACH;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_DEVICE:
      kind = GOMP_MAP_FORCE_TO;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      kind = GOMP_MAP_DEVICE_RESIDENT;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_LINK:
      kind = GOMP_MAP_LINK;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_NO_CREATE:
      kind = GOMP_MAP_IF_PRESENT;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_PRESENT:
      kind = GOMP_MAP_FORCE_PRESENT;
      તોડો;
    સ્થિતિ PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    સ્થિતિ PRAGMA_OACC_CLAUSE_HOST:
      kind = GOMP_MAP_FORCE_FROM;
      તોડો;
    મૂળભૂત:
      gcc_unreachable ();
    }

  વૃક્ષ nl = list;
  તાર્કિક readonly = ખોટું;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      જો (c_kind == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  જો (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_POINTER (token->કિંમત), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = સાચું;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       ખોટું);
      parens.skip_until_found_close (parser);
    }

  માટે (વૃક્ષ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      જો (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  પાછા nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_oacc_data_clause_deviceptr (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ખાલી);
  માટે (t = vars; t && t; t = વૃક્ષ_CHAIN (t))
    {
      વૃક્ષ v = વૃક્ષ_PURPOSE (t);
      location_t loc = પદાવલિ_LOCATION (વૃક્ષ_કિંમત (t));

      જો (!VAR_P (v) && વૃક્ષ_CODE (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      નહીંતર જો (વૃક્ષ_TYPE (v) == error_mark_ગાંઠ)
	;
      નહીંતર જો (!POINTER_TYPE_P (વૃક્ષ_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      વૃક્ષ u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  પાછા list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_collapse (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ c, અંક = error_mark_ગાંઠ;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      અંક = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
      parens.skip_until_found_close (parser);
    }
  જો (અંક == error_mark_ગાંઠ)
    પાછા list;
  mark_exp_read (અંક);
  અંક = c_fully_fold (અંક, ખોટું, ખાલી);
  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (અંક))
      || !વૃક્ષ_fits_shwi_p (અંક)
      || (n = વૃક્ષ_to_shwi (અંક)) <= 0
      || (પૂર્ણાંક) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      પાછા list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_પદાવલિ (c) = અંક;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_copyin (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_copyprivate (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_default (c_parser *parser, વૃક્ષ list, તાર્કિક is_oacc)
{
  ગણના omp_clause_default_kind kind = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ c;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      પસંદગી (p[0])
	{
	સ્થિતિ 'n':
	  જો (strcmp ("none", p) != 0)
	    જાઓ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_NONE;
	  તોડો;

	સ્થિતિ 'p':
	  જો (is_oacc)
	    {
	      જો (strcmp ("present", p) != 0)
		જાઓ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  નહીંતર
	    {
	      જો (strcmp ("private", p) != 0)
		જાઓ invalid_kind;
	      kind = OMP_CLAUSE_DEFAULT_PRIVATE;
	    }
	  તોડો;

	સ્થિતિ 'f':
	  જો (strcmp ("firstprivate", p) != 0 || is_oacc)
	    જાઓ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  તોડો;

	સ્થિતિ 's':
	  જો (strcmp ("shared", p) != 0 || is_oacc)
	    જાઓ invalid_kind;
	  kind = OMP_CLAUSE_DEFAULT_SHARED;
	  તોડો;

	મૂળભૂત:
	  જાઓ invalid_kind;
	}

      c_parser_consume_token (parser);
    }
  નહીંતર
    {
    invalid_kind:
      જો (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      નહીંતર
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_found_close (parser);

  જો (kind == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    પાછા list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_KIND (c) = kind;

  પાછા c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_firstprivate (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_final (c_parser *parser, વૃક્ષ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      વૃક્ષ t, c;
      જો (!parens.require_open (parser))
	t = error_mark_ગાંઠ;
      નહીંતર
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  t = convert_lvalue_to_rvalue (eloc, પદાવલિ, સાચું, સાચું).કિંમત;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, ખોટું, ખાલી);
	  parens.skip_until_found_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_પદાવલિ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  નહીંતર
    c_parser_error (parser, "expected %<(%>");

  પાછા list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

સ્થિર વૃક્ષ
c_parser_omp_clause_indirect (c_parser *parser, વૃક્ષ list)
{
  location_t location = c_parser_peek_token (parser)->location;
  વૃક્ષ t;

  જો (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      જો (!parens.require_open (parser))
	પાછા list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, સાચું, સાચું);
      t = c_objc_common_truthvalue_conversion (loc, પદાવલિ.કિંમત);
      t = c_fully_fold (t, ખોટું, ખાલી);
      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t))
	  || વૃક્ષ_CODE (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  પાછા list;
	}
      parens.skip_until_found_close (parser);
    }
  નહીંતર
    t = integer_one_ગાંઠ;

  check_no_duplicate_clause (list, OMP_CLAUSE_INDIRECT, "indirect");

  વૃક્ષ c = build_omp_clause (location, OMP_CLAUSE_INDIRECT);
  OMP_CLAUSE_INDIRECT_પદાવલિ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  પાછા c;
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

સ્થિર વૃક્ષ
c_parser_omp_clause_if (c_parser *parser, વૃક્ષ list, તાર્કિક is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  ગણના વૃક્ષ_code if_modifier = ERROR_MARK;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો (is_omp && c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      પૂર્ણાંક n = 2;
      જો (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      નહીંતર જો (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      નહીંતર જો (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      નહીંતર જો (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      નહીંતર જો (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      નહીંતર જો (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_TARGET;
	  જો (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_POINTER (c_parser_peek_2nd_token (parser)->કિંમત);
	      જો (strcmp ("data", p) == 0)
		if_modifier = OMP_TARGET_DATA;
	      નહીંતર જો (strcmp ("update", p) == 0)
		if_modifier = OMP_TARGET_UPDATE;
	      નહીંતર જો (strcmp ("enter", p) == 0)
		if_modifier = OMP_TARGET_ENTER_DATA;
	      નહીંતર જો (strcmp ("exit", p) == 0)
		if_modifier = OMP_TARGET_EXIT_DATA;
	      જો (if_modifier != OMP_TARGET)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      નહીંતર
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      જો (if_modifier == OMP_TARGET_ENTER_DATA
		  || if_modifier == OMP_TARGET_EXIT_DATA)
		{
		  જો (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_POINTER
				(c_parser_peek_2nd_token (parser)->કિંમત);
		      જો (strcmp ("data", p) == 0)
			n = 4;
		    }
		  જો (n == 4)
		    c_parser_consume_token (parser);
		  નહીંતર
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      જો (if_modifier != ERROR_MARK)
	{
	  જો (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  નહીંતર
	    {
	      જો (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, સાચું, સાચું);
  વૃક્ષ t = c_objc_common_truthvalue_conversion (loc, પદાવલિ.કિંમત), c;
  t = c_fully_fold (t, ખોટું, ખાલી);
  parens.skip_until_found_close (parser);

  માટે (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IF)
      {
	જો (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    અચલ અક્ષર *p = ખાલી;
	    પસંદગી (if_modifier)
	      {
	      સ્થિતિ VOID_CST: p = "cancel"; તોડો;
	      સ્થિતિ OMP_PARALLEL: p = "parallel"; તોડો;
	      સ્થિતિ OMP_SIMD: p = "simd"; તોડો;
	      સ્થિતિ OMP_TASK: p = "task"; તોડો;
	      સ્થિતિ OMP_TASKLOOP: p = "taskloop"; તોડો;
	      સ્થિતિ OMP_TARGET_DATA: p = "target data"; તોડો;
	      સ્થિતિ OMP_TARGET: p = "target"; તોડો;
	      સ્થિતિ OMP_TARGET_UPDATE: p = "target update"; તોડો;
	      સ્થિતિ OMP_TARGET_ENTER_DATA: p = "target enter data"; તોડો;
	      સ્થિતિ OMP_TARGET_EXIT_DATA: p = "target exit data"; તોડો;
	      મૂળભૂત: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    પાછા list;
	  }
	નહીંતર જો (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    જો (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    નહીંતર
	      error_at (location, "too many %<if%> clauses without modifier");
	    પાછા list;
	  }
	નહીંતર જો (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    પાછા list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_પદાવલિ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_lastprivate (c_parser *parser, વૃક્ષ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  જો (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      તાર્કિક conditional = ખોટું;
      જો (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  અચલ અક્ષર *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	  જો (strcmp (p, "conditional") == 0)
	    {
	      conditional = સાચું;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      વૃક્ષ nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      જો (conditional)
	માટે (વૃક્ષ c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      પાછા nlist;
    }
  પાછા list;
}

/* OpenMP 3.1:
   mergeable */

સ્થિર વૃક્ષ
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_UNUSED, વૃક્ષ list)
{
  વૃક્ષ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  પાછા c;
}

/* OpenMP 2.5:
   nowait */

સ્થિર વૃક્ષ
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_UNUSED, વૃક્ષ list)
{
  વૃક્ષ c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_અંક_threads (c_parser *parser, વૃક્ષ list)
{
  location_t અંક_threads_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ c, t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);

      parens.skip_until_found_close (parser);

      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  પાછા list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (પદાવલિ_loc, LE_પદાવલિ, boolean_type_ગાંઠ, t,
		       build_int_cst (વૃક્ષ_TYPE (t), 0));
      protected_set_પદાવલિ_location (c, પદાવલિ_loc);
      જો (c == boolean_true_ગાંઠ)
	{
	  warning_at (પદાવલિ_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_ગાંઠ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_અંક_THREADS, "num_threads");

      c = build_omp_clause (અંક_threads_loc, OMP_CLAUSE_અંક_THREADS);
      OMP_CLAUSE_અંક_THREADS_પદાવલિ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_અંક_tasks (c_parser *parser, વૃક્ષ list)
{
  location_t અંક_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      તાર્કિક strict = ખોટું;
      જો (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત),
		     "strict") == 0)
	{
	  strict = સાચું;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ c, t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);

      parens.skip_until_found_close (parser);

      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  પાછા list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (પદાવલિ_loc, LE_પદાવલિ, boolean_type_ગાંઠ, t,
			   build_int_cst (વૃક્ષ_TYPE (t), 0));
      જો (CAN_HAVE_LOCATION_P (c))
	SET_પદાવલિ_LOCATION (c, પદાવલિ_loc);
      જો (c == boolean_true_ગાંઠ)
	{
	  warning_at (પદાવલિ_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_ગાંઠ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_અંક_TASKS, "num_tasks");

      c = build_omp_clause (અંક_tasks_loc, OMP_CLAUSE_અંક_TASKS);
      OMP_CLAUSE_અંક_TASKS_પદાવલિ (c) = t;
      OMP_CLAUSE_અંક_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_grainsize (c_parser *parser, વૃક્ષ list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      તાર્કિક strict = ખોટું;
      જો (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત),
		     "strict") == 0)
	{
	  strict = સાચું;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ c, t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);

      parens.skip_until_found_close (parser);

      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  પાછા list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (પદાવલિ_loc, LE_પદાવલિ, boolean_type_ગાંઠ, t,
			   build_int_cst (વૃક્ષ_TYPE (t), 0));
      જો (CAN_HAVE_LOCATION_P (c))
	SET_પદાવલિ_LOCATION (c, પદાવલિ_loc);
      જો (c == boolean_true_ગાંઠ)
	{
	  warning_at (પદાવલિ_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_ગાંઠ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_પદાવલિ (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenMP 4.5:
   priority ( expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_priority (c_parser *parser, વૃક્ષ list)
{
  location_t priority_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ c, t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);

      parens.skip_until_found_close (parser);

      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  પાછા list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (પદાવલિ_loc, LT_પદાવલિ, boolean_type_ગાંઠ, t,
			   build_int_cst (વૃક્ષ_TYPE (t), 0));
      જો (CAN_HAVE_LOCATION_P (c))
	SET_પદાવલિ_LOCATION (c, પદાવલિ_loc);
      જો (c == boolean_true_ગાંઠ)
	{
	  warning_at (પદાવલિ_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_ગાંઠ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_PRIORITY, "priority");

      c = build_omp_clause (priority_loc, OMP_CLAUSE_PRIORITY);
      OMP_CLAUSE_PRIORITY_પદાવલિ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenMP 4.5:
   hint ( expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_hint (c_parser *parser, વૃક્ષ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ c, t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);
      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t))
	  || વૃક્ષ_CODE (t) != INTEGER_CST
	  || વૃક્ષ_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  પાછા list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_પદાવલિ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_filter (c_parser *parser, વૃક્ષ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ c, t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);
      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  પાછા list;
	}
      parens.skip_until_found_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_પદાવલિ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_defaultmap (c_parser *parser, વૃક્ષ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ c;
  અચલ અક્ષર *p;
  ગણના omp_clause_defaultmap_kind behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  ગણના omp_clause_defaultmap_kind category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;
  જો (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  નહીંતર જો (!c_parser_next_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      જાઓ out_err;
    }
  નહીંતર
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

  પસંદગી (p[0])
    {
    સ્થિતિ 'a':
      જો (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      નહીંતર
	જાઓ invalid_behavior;
      તોડો;

    સ્થિતિ 'd':
      જો (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      નહીંતર
	જાઓ invalid_behavior;
      તોડો;

    સ્થિતિ 'f':
      જો (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      નહીંતર જો (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      નહીંતર
	જાઓ invalid_behavior;
      તોડો;

    સ્થિતિ 'n':
      જો (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      નહીંતર
	જાઓ invalid_behavior;
      તોડો;

    સ્થિતિ 'p':
      જો (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      નહીંતર
	જાઓ invalid_behavior;
      તોડો;

    સ્થિતિ 't':
      જો (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      નહીંતર જો (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TO;
      નહીંતર
	જાઓ invalid_behavior;
      તોડો;

    મૂળભૂત:
      જાઓ invalid_behavior;
    }
  c_parser_consume_token (parser);

  જો (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
    {
      જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	જાઓ out_err;
      જો (!c_parser_next_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  જાઓ out_err;
	}
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      પસંદગી (p[0])
	{
	સ્થિતિ 'a':
	  જો (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  નહીંતર જો (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  નહીંતર
	    જાઓ invalid_category;
	  તોડો;

	સ્થિતિ 'p':
	  જો (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER;
	  નહીંતર
	    જાઓ invalid_category;
	  તોડો;

	સ્થિતિ 's':
	  જો (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  નહીંતર
	    જાઓ invalid_category;
	  તોડો;

	મૂળભૂત:
	  જાઓ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_found_close (parser);

  માટે (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	ગણના omp_clause_defaultmap_kind cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	જો (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = ખાલી;
	પસંદગી (cat)
	  {
	  સ્થિતિ OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = ખાલી;
	    તોડો;
	  સ્થિતિ OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    તોડો;
	  સ્થિતિ OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    તોડો;
	  સ્થિતિ OMP_CLAUSE_DEFAULTMAP_CATEGORY_POINTER:
	    p = "pointer";
	    તોડો;
	  સ્થિતિ OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    તોડો;
	  મૂળભૂત:
	    gcc_unreachable ();
	  }
	જો (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	નહીંતર
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	તોડો;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_SET_KIND (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;

 out_err:
  parens.skip_until_found_close (parser);
  પાછા list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_use_device_ptr (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_use_device_addr (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_has_device_addr (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_is_device_ptr (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

સ્થિર વૃક્ષ
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_code code,
				 વૃક્ષ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
  c_પદાવલિ પદાવલિ = c_parser_expression (parser);
  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
  વૃક્ષ c, t = પદાવલિ.કિંમત;
  t = c_fully_fold (t, ખોટું, ખાલી);

  parens.skip_until_found_close (parser);

  જો (t == error_mark_ગાંઠ)
    પાછા list;
  નહીંતર જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
    {
      error_at (પદાવલિ_loc, "%qs expression must be integral",
		omp_clause_code_name[code]);
      પાછા list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (પદાવલિ_loc, LE_પદાવલિ, boolean_type_ગાંઠ, t,
		       build_int_cst (વૃક્ષ_TYPE (t), 0));
  protected_set_પદાવલિ_location (c, પદાવલિ_loc);
  જો (c == boolean_true_ગાંઠ)
    {
      warning_at (પદાવલિ_loc, 0,
		  "%qs value must be positive",
		  omp_clause_code_name[code]);
      t = integer_one_ગાંઠ;
    }

  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  c = build_omp_clause (loc, code);
  OMP_CLAUSE_OPERAND (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
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

સ્થિર વૃક્ષ
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_code kind,
			    અચલ અક્ષર *str, વૃક્ષ list)
{
  અચલ અક્ષર *id = "num";
  વૃક્ષ ops[2] = { NULL_વૃક્ષ, NULL_વૃક્ષ }, c;

  જો (kind == OMP_CLAUSE_VECTOR)
    id = "length";

  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      કરો
	{
	  c_token *next = c_parser_peek_token (parser);
	  પૂર્ણાંક idx = 0;

	  /* Gang static argument.  */
	  જો (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		જાઓ cleanup_error;

	      idx = 1;
	      જો (ops[idx] != NULL_વૃક્ષ)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  જાઓ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      જો (c_parser_next_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_ગાંઠ;

		  જો (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      ચાલુ;
		    }
		  નહીંતર
		    તોડો;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  નહીંતર જો (c_parser_next_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_POINTER (next->કિંમત)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  જો (ops[idx] != NULL_વૃક્ષ)
	    {
	      c_parser_error (parser, "unexpected argument");
	      જાઓ cleanup_error;
	    }

	  location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
	  c_પદાવલિ cexpr = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  cexpr = convert_lvalue_to_rvalue (પદાવલિ_loc, cexpr, ખોટું, સાચું);
	  વૃક્ષ પદાવલિ = cexpr.કિંમત;
	  જો (પદાવલિ == error_mark_ગાંઠ)
	    જાઓ cleanup_error;

	  પદાવલિ = c_fully_fold (પદાવલિ, ખોટું, ખાલી);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (પદાવલિ)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      પાછા list;
	    }

	  વૃક્ષ c = fold_build2_loc (પદાવલિ_loc, LE_પદાવલિ, boolean_type_ગાંઠ, પદાવલિ,
				    build_int_cst (વૃક્ષ_TYPE (પદાવલિ), 0));
	  જો (c == boolean_true_ગાંઠ)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      પદાવલિ = integer_one_ગાંઠ;
	    }

	  ops[idx] = પદાવલિ;

	  જો (kind == OMP_CLAUSE_GANG
	      && c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ચાલુ;
	    }
	  તોડો;
	}
      જ્યારે (1);

      જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	જાઓ cleanup_error;
    }

  check_no_duplicate_clause (list, kind, str);

  c = build_omp_clause (loc, kind);

  જો (ops[1])
    OMP_CLAUSE_OPERAND (c, 1) = ops[1];

  OMP_CLAUSE_OPERAND (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  પાછા c;

 cleanup_error:
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  પાછા list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

સ્થિર વૃક્ષ
c_parser_oacc_simple_clause (location_t loc, ગણના omp_clause_code code,
			     વૃક્ષ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  વૃક્ષ c = build_omp_clause (loc, code);
  OMP_CLAUSE_CHAIN (c) = list;

  પાછા c;
}

/* OpenACC:
   async [( int-expr )] */

સ્થિર વૃક્ષ
c_parser_oacc_clause_async (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_ગાંઠ, GOMP_ASYNC_NOVAL);

  જો (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      નહીંતર જો (t == error_mark_ગાંઠ
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	પાછા list;
    }
  નહીંતર
    t = c_fully_fold (t, ખોટું, ખાલી);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_પદાવલિ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  પાછા list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

સ્થિર વૃક્ષ
c_parser_oacc_clause_tile (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ c, પદાવલિ = error_mark_ગાંઠ;
  location_t loc;
  વૃક્ષ tile = NULL_વૃક્ષ;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    પાછા list;

  કરો
    {
      જો (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	પાછા list;

      જો (c_parser_next_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  પદાવલિ = integer_zero_ગાંઠ;
	}
      નહીંતર
	{
	  location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
	  c_પદાવલિ cexpr = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  cexpr = convert_lvalue_to_rvalue (પદાવલિ_loc, cexpr, ખોટું, સાચું);
	  પદાવલિ = cexpr.કિંમત;

	  જો (પદાવલિ == error_mark_ગાંઠ)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      પાછા list;
	    }

	  પદાવલિ = c_fully_fold (પદાવલિ, ખોટું, ખાલી);

	  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (પદાવલિ))
	      || !વૃક્ષ_fits_shwi_p (પદાવલિ)
	      || વૃક્ષ_to_shwi (પદાવલિ) <= 0)
	    {
	      error_at (પદાવલિ_loc, "%<tile%> argument needs positive"
			" integral constant");
	      પદાવલિ = integer_zero_ગાંઠ;
	    }
	}

      tile = વૃક્ષ_cons (NULL_વૃક્ષ, પદાવલિ, tile);
    }
  જ્યારે (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenACC:
   wait [( int-expr-list )] */

સ્થિર વૃક્ષ
c_parser_oacc_clause_wait (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  જો (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  નહીંતર
    {
      વૃક્ષ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_ગાંઠ, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenACC 2.7:
   self [( expression )] */

સ્થિર વૃક્ષ
c_parser_oacc_compute_clause_self (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ t;
  location_t location = c_parser_peek_token (parser)->location;
  જો (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, સાચું, સાચું);
      t = c_objc_common_truthvalue_conversion (loc, પદાવલિ.કિંમત);
      t = c_fully_fold (t, ખોટું, ખાલી);
      parens.skip_until_found_close (parser);
    }
  નહીંતર
    t = truthvalue_true_ગાંઠ;

  માટે (વૃક્ષ c = list; c; c = OMP_CLAUSE_CHAIN (c))
    જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	પાછા list;
      }

  વૃક્ષ c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_પદાવલિ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

સ્થિર વૃક્ષ
c_parser_omp_clause_order (c_parser *parser, વૃક્ષ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ c;
  અચલ અક્ષર *p;
  તાર્કિક unconstrained = ખોટું;
  તાર્કિક reproducible = ખોટું;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;
  જો (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "unconstrained") == 0)
	unconstrained = સાચું;
      નહીંતર જો (strcmp (p, "reproducible") == 0)
	reproducible = સાચું;
      નહીંતર
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  જાઓ out_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  જો (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      જાઓ out_err;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
  જો (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      જાઓ out_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDER, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ORDER);
  OMP_CLAUSE_ORDER_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ORDER_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;

 out_err:
  parens.skip_until_found_close (parser);
  પાછા list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_bind (c_parser *parser, વૃક્ષ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ c;
  અચલ અક્ષર *p;
  ગણના omp_clause_bind_kind kind = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;
  જો (!c_parser_next_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_found_close (parser);
      પાછા list;
    }
  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
  જો (strcmp (p, "teams") == 0)
    kind = OMP_CLAUSE_BIND_TEAMS;
  નહીંતર જો (strcmp (p, "parallel") == 0)
    kind = OMP_CLAUSE_BIND_PARALLEL;
  નહીંતર જો (strcmp (p, "thread") != 0)
    જાઓ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_ordered (c_parser *parser, વૃક્ષ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  વૃક્ષ c, અંક = NULL_વૃક્ષ;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      અંક = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
      parens.skip_until_found_close (parser);
    }
  જો (અંક == error_mark_ગાંઠ)
    પાછા list;
  જો (અંક)
    {
      mark_exp_read (અંક);
      અંક = c_fully_fold (અંક, ખોટું, ખાલી);
      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (અંક))
	  || !વૃક્ષ_fits_shwi_p (અંક)
	  || (n = વૃક્ષ_to_shwi (અંક)) <= 0
	  || (પૂર્ણાંક) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  પાછા list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_પદાવલિ (c) = અંક;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_private (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_PRIVATE, list);
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

સ્થિર વૃક્ષ
c_parser_omp_clause_reduction (c_parser *parser, ગણના omp_clause_code kind,
			       તાર્કિક is_omp, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      તાર્કિક task = ખોટું;
      તાર્કિક inscan = ખોટું;
      ગણના વૃક્ષ_code code = ERROR_MARK;
      વૃક્ષ reduc_id = NULL_વૃક્ષ;

      જો (kind == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  જો (c_parser_next_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  નહીંતર જો (c_parser_next_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      અચલ અક્ષર *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	      જો (strcmp (p, "task") == 0)
		task = સાચું;
	      નહીંતર જો (strcmp (p, "inscan") == 0)
		inscan = સાચું;
	      જો (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_PLUS:
	  code = PLUS_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_MULT:
	  code = MULT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_MINUS:
	  જો (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.add_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  code = MINUS_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_AND:
	  code = BIT_AND_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_XOR:
	  code = BIT_XOR_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_OR:
	  code = BIT_IOR_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_AND_AND:
	  code = TRUTH_ANDIF_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_OR_OR:
	  code = TRUTH_ORIF_પદાવલિ;
	  તોડો;
        સ્થિતિ CPP_NAME:
	  {
	    અચલ અક્ષર *p
	      = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	    જો (strcmp (p, "min") == 0)
	      {
		code = MIN_પદાવલિ;
		તોડો;
	      }
	    જો (strcmp (p, "max") == 0)
	      {
		code = MAX_પદાવલિ;
		તોડો;
	      }
	    reduc_id = c_parser_peek_token (parser)->કિંમત;
	    તોડો;
	  }
	મૂળભૂત:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
	  પાછા list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (code, reduc_id);
      જો (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  વૃક્ષ nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, kind, list);
	  માટે (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      વૃક્ષ d = OMP_CLAUSE_DECL (c), type;
	      જો (વૃક્ષ_CODE (d) != OMP_ARRAY_SECTION)
		type = વૃક્ષ_TYPE (d);
	      નહીંતર
		{
		  પૂર્ણાંક cnt = 0;
		  વૃક્ષ t;
		  માટે (t = d;
		      વૃક્ષ_CODE (t) == OMP_ARRAY_SECTION;
		      t = વૃક્ષ_OPERAND (t, 0))
		    cnt++;
		  type = વૃક્ષ_TYPE (t);
		  જ્યારે (cnt > 0)
		    {
		      જો (વૃક્ષ_CODE (type) != POINTER_TYPE
			  && વૃક્ષ_CODE (type) != ARRAY_TYPE)
			તોડો;
		      type = વૃક્ષ_TYPE (type);
		      cnt--;
		    }
		}
	      જ્યારે (વૃક્ષ_CODE (type) == ARRAY_TYPE)
		type = વૃક્ષ_TYPE (type);
	      OMP_CLAUSE_REDUCTION_CODE (c) = code;
	      જો (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      નહીંતર જો (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      જો (code == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || વૃક્ષ_CODE (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_found_close (parser);
    }
  પાછા list;
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

સ્થિર વૃક્ષ
c_parser_omp_clause_schedule (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  પૂર્ણાંક modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  c = build_omp_clause (loc, OMP_CLAUSE_SCHEDULE);

  location_t comma = UNKNOWN_LOCATION;
  જ્યારે (c_parser_next_token_is (parser, CPP_NAME))
    {
      વૃક્ષ kind = c_parser_peek_token (parser)->કિંમત;
      અચલ અક્ષર *p = IDENTIFIER_POINTER (kind);
      જો (strcmp ("simd", p) == 0)
	OMP_CLAUSE_SCHEDULE_SIMD (c) = 1;
      નહીંતર જો (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_MONOTONIC;
      નહીંતર જો (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_SCHEDULE_NONMONOTONIC;
      નહીંતર
	તોડો;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      જો (nmodifiers++ == 0
	  && c_parser_next_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      નહીંતર
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  તોડો;
	}
    }
  જો (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  જો ((modifiers & (OMP_CLAUSE_SCHEDULE_MONOTONIC
		    | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
      == (OMP_CLAUSE_SCHEDULE_MONOTONIC
	  | OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      વૃક્ષ kind = c_parser_peek_token (parser)->કિંમત;
      અચલ અક્ષર *p = IDENTIFIER_POINTER (kind);

      પસંદગી (p[0])
	{
	સ્થિતિ 'd':
	  જો (strcmp ("dynamic", p) != 0)
	    જાઓ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_DYNAMIC;
	  તોડો;

        સ્થિતિ 'g':
	  જો (strcmp ("guided", p) != 0)
	    જાઓ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_GUIDED;
	  તોડો;

	સ્થિતિ 'r':
	  જો (strcmp ("runtime", p) != 0)
	    જાઓ invalid_kind;
	  OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_RUNTIME;
	  તોડો;

	મૂળભૂત:
	  જાઓ invalid_kind;
	}
    }
  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_STATIC;
  નહીંતર જો (c_parser_next_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_SCHEDULE_KIND (c) = OMP_CLAUSE_SCHEDULE_AUTO;
  નહીંતર
    જાઓ invalid_kind;

  c_parser_consume_token (parser);
  જો (c_parser_next_token_is (parser, CPP_COMMA))
    {
      location_t here;
      c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (here, પદાવલિ, ખોટું, સાચું);
      t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);

      જો (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_RUNTIME)
	error_at (here, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      નહીંતર જો (OMP_CLAUSE_SCHEDULE_KIND (c) == OMP_CLAUSE_SCHEDULE_AUTO)
	error_at (here,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) == INTEGER_TYPE
	       || વૃક્ષ_CODE (વૃક્ષ_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  વૃક્ષ s = fold_build2_loc (loc, LE_પદાવલિ, boolean_type_ગાંઠ, t,
				    build_int_cst (વૃક્ષ_TYPE (t), 0));
	  protected_set_પદાવલિ_location (s, loc);
	  જો (s == boolean_true_ગાંઠ)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_ગાંઠ;
	    }
	  OMP_CLAUSE_SCHEDULE_CHUNK_પદાવલિ (c) = t;
	}
      નહીંતર
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_found_close (parser);
    }
  નહીંતર
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_SCHEDULE_KIND (c)
    = (ગણના omp_clause_schedule_kind)
      (OMP_CLAUSE_SCHEDULE_KIND (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_SCHEDULE, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;

 invalid_kind:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, 0);
  પાછા list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_shared (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

સ્થિર વૃક્ષ
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_UNUSED, વૃક્ષ list)
{
  વૃક્ષ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  પાછા c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

સ્થિર વૃક્ષ
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_UNUSED,
			    ગણના omp_clause_code code, વૃક્ષ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);

  વૃક્ષ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  પાછા c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

સ્થિર વૃક્ષ
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_UNUSED,
				ગણના omp_clause_code code, વૃક્ષ list)
{
  વૃક્ષ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;

  પાછા c;
}

/* OpenMP 4.5:
   nogroup */

સ્થિર વૃક્ષ
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_UNUSED, વૃક્ષ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  વૃક્ષ c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 4.5:
   simd
   threads */

સ્થિર વૃક્ષ
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_UNUSED,
				 ગણના omp_clause_code code, વૃક્ષ list)
{
  check_no_duplicate_clause (list, code, omp_clause_code_name[code]);
  વૃક્ષ c = build_omp_clause (c_parser_peek_token (parser)->location, code);
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_અંક_teams (c_parser *parser, વૃક્ષ list)
{
  location_t અંક_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      location_t upper_loc = c_parser_peek_token (parser)->location;
      location_t lower_loc = UNKNOWN_LOCATION;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (upper_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ c, upper = પદાવલિ.કિંમત, lower = NULL_વૃક્ષ;
      upper = c_fully_fold (upper, ખોટું, ખાલી);

      જો (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  lower_loc = upper_loc;
	  lower = upper;
	  upper_loc = c_parser_peek_token (parser)->location;
	  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  પદાવલિ = convert_lvalue_to_rvalue (upper_loc, પદાવલિ, ખોટું, સાચું);
	  upper = પદાવલિ.કિંમત;
	  upper = c_fully_fold (upper, ખોટું, ખાલી);
	}

      parens.skip_until_found_close (parser);

      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (upper))
	  || (lower && !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (lower))))
	{
	  c_parser_error (parser, "expected integer expression");
	  પાછા list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (upper_loc, LE_પદાવલિ, boolean_type_ગાંઠ, upper,
			   build_int_cst (વૃક્ષ_TYPE (upper), 0));
      protected_set_પદાવલિ_location (c, upper_loc);
      જો (c == boolean_true_ગાંઠ)
	{
	  warning_at (upper_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  upper = integer_one_ગાંઠ;
	}
      જો (lower)
	{
	  c = fold_build2_loc (lower_loc, LE_પદાવલિ, boolean_type_ગાંઠ, lower,
			       build_int_cst (વૃક્ષ_TYPE (lower), 0));
	  protected_set_પદાવલિ_location (c, lower_loc);
	  જો (c == boolean_true_ગાંઠ)
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      lower = NULL_વૃક્ષ;
	    }
	  નહીંતર જો (વૃક્ષ_CODE (lower) == INTEGER_CST
		   && વૃક્ષ_CODE (upper) == INTEGER_CST
		   && વૃક્ષ_int_cst_lt (upper, lower))
	    {
	      warning_at (lower_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", lower, upper);
	      lower = NULL_વૃક્ષ;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_અંક_TEAMS, "num_teams");

      c = build_omp_clause (અંક_teams_loc, OMP_CLAUSE_અંક_TEAMS);
      OMP_CLAUSE_અંક_TEAMS_UPPER_પદાવલિ (c) = upper;
      OMP_CLAUSE_અંક_TEAMS_LOWER_પદાવલિ (c) = lower;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_thread_limit (c_parser *parser, વૃક્ષ list)
{
  location_t અંક_thread_limit_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ c, t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);

      parens.skip_until_found_close (parser);

      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  પાછા list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (પદાવલિ_loc, LE_પદાવલિ, boolean_type_ગાંઠ, t,
			   build_int_cst (વૃક્ષ_TYPE (t), 0));
      protected_set_પદાવલિ_location (c, પદાવલિ_loc);
      જો (c == boolean_true_ગાંઠ)
	{
	  warning_at (પદાવલિ_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_ગાંઠ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_LIMIT,
				 "thread_limit");

      c = build_omp_clause (અંક_thread_limit_loc, OMP_CLAUSE_THREAD_LIMIT);
      OMP_CLAUSE_THREAD_LIMIT_પદાવલિ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  પાછા list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_aligned (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ nl, c;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  જો (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      વૃક્ષ alignment = પદાવલિ.કિંમત;
      alignment = c_fully_fold (alignment, ખોટું, ખાલી);
      જો (વૃક્ષ_CODE (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (alignment))
	  || વૃક્ષ_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_વૃક્ષ;
	}

      માટે (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_found_close (parser);
  પાછા nl;
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

સ્થિર વૃક્ષ
c_parser_omp_clause_allocate (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ nl, c;
  વૃક્ષ allocator = NULL_વૃક્ષ;
  વૃક્ષ align = NULL_વૃક્ષ;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો ((c_parser_next_token_is_not (parser, CPP_NAME)
       && c_parser_next_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      તાર્કિક has_modifiers = ખોટું;
      વૃક્ષ orig_type = NULL_વૃક્ષ;
      જો (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  unsigned પૂર્ણાંક n = 3;
	  અચલ અક્ષર *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	  જો ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      જો (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = સાચું;
	      નહીંતર જો (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  અચલ અક્ષર *q = IDENTIFIER_POINTER (tok->કિંમત);
		  n += 4;
		  જો ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_balanced_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = સાચું;
		}
	    }
	  જો (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
	      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
	      જો (પદાવલિ.કિંમત == error_mark_ગાંઠ)
		;
	      નહીંતર જો (strcmp (p, "allocator") == 0)
		{
		  allocator = પદાવલિ.કિંમત;
		  allocator = c_fully_fold (allocator, ખોટું, ખાલી);
		  orig_type = પદાવલિ.original_type
			      ? પદાવલિ.original_type : વૃક્ષ_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      નહીંતર
		{
		  align = પદાવલિ.કિંમત;
		  align = c_fully_fold (align, ખોટું, ખાલી);
		}
	      parens2.skip_until_found_close (parser);
	      જો (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  અચલ અક્ષર *q = "";
		  જો (c_parser_next_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_POINTER (tok->કિંમત);
		  જો (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_found_close (parser);
		      પાછા list;
		    }
		  નહીંતર જો (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_found_close (parser);
		      પાછા list;
		    }
		  c_parser_consume_token (parser);
		  જો (!parens2.require_open (parser))
		    {
		      parens.skip_until_found_close (parser);
		      પાછા list;
		    }
		  પદાવલિ_loc = c_parser_peek_token (parser)->location;
		  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
		  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું,
						   સાચું);
		  જો (strcmp (q, "allocator") == 0)
		    {
		      allocator = પદાવલિ.કિંમત;
		      allocator = c_fully_fold (allocator, ખોટું, ખાલી);
		      orig_type = પદાવલિ.original_type
				  ? પદાવલિ.original_type : વૃક્ષ_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  નહીંતર
		    {
		      align = પદાવલિ.કિંમત;
		      align = c_fully_fold (align, ખોટું, ખાલી);
		    }
		  parens2.skip_until_found_close (parser);
		}
	    }
	}
      જો (!has_modifiers)
	{
	  location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
	  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
	  જો (પદાવલિ.કિંમત != error_mark_ગાંઠ)
	    {
	      allocator = પદાવલિ.કિંમત;
	      allocator = c_fully_fold (allocator, ખોટું, ખાલી);
	      orig_type = પદાવલિ.original_type
			  ? પદાવલિ.original_type : વૃક્ષ_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      જો (allocator
	  && (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (allocator))
	      || વૃક્ષ_CODE (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				વૃક્ષ_TYPE (allocator));
          allocator = NULL_વૃક્ષ;
        }
      જો (align
	  && (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (align))
	      || !વૃક્ષ_fits_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_વૃક્ષ;
	}
      જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_found_close (parser);
	  પાછા list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  જો (allocator || align)
    માટે (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_found_close (parser);
  પાછા nl;
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

સ્થિર વૃક્ષ
c_parser_omp_clause_uses_allocators (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ nl = list;
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

parse_next:

  તાર્કિક has_modifiers = ખોટું;
  તાર્કિક seen_allocators = ખોટું;
  વૃક્ષ memspace_પદાવલિ = NULL_વૃક્ષ;
  વૃક્ષ traits_var = NULL_વૃક્ષ;

  જો (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      unsigned પૂર્ણાંક n = 3;
      અચલ અક્ષર *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_balanced_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  જો (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = સાચું;
	  નહીંતર જો (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      અચલ અક્ષર *q = IDENTIFIER_POINTER (tok->કિંમત);
	      n += 4;
	      જો ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_balanced_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  જો (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = સાચું;
		  જો ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      અચલ અક્ષર *m = IDENTIFIER_POINTER (tok->કિંમત);
		      જો (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  જાઓ end;
			}
		    }
		}
	    }
	}
      જો (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  જો (પદાવલિ.કિંમત == error_mark_ગાંઠ)
	    ;
	  નહીંતર જો (strcmp (p, "traits") == 0)
	    {
	      traits_var = પદાવલિ.કિંમત;
	      traits_var = c_fully_fold (traits_var, ખોટું, ખાલી);
	      mark_exp_read (traits_var);
	    }
	  નહીંતર
	    {
	      memspace_પદાવલિ = પદાવલિ.કિંમત;
	      memspace_પદાવલિ = c_fully_fold (memspace_પદાવલિ, ખોટું, ખાલી);
	    }
	  parens2.skip_until_found_close (parser);
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      અચલ અક્ષર *q = "";
	      જો (c_parser_next_token_is (parser, CPP_NAME))
		q = IDENTIFIER_POINTER (tok->કિંમત);
	      જો (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_found_close (parser);
		  પાછા list;
		}
	      નહીંતર જો (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_found_close (parser);
		  પાછા list;
		}
	      c_parser_consume_token (parser);
	      જો (!parens2.require_open (parser))
		{
		  parens.skip_until_found_close (parser);
		  પાછા list;
		}
	      પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	      જો (strcmp (q, "traits") == 0)
		{
		  traits_var = પદાવલિ.કિંમત;
		  traits_var = c_fully_fold (traits_var, ખોટું, ખાલી);
		  mark_exp_read (traits_var);
		}
	      નહીંતર
		{
		  memspace_પદાવલિ = પદાવલિ.કિંમત;
		  memspace_પદાવલિ = c_fully_fold (memspace_પદાવલિ, ખોટું, ખાલી);
		}
	      parens2.skip_until_found_close (parser);
	    }
	  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    જાઓ end;
	}
    }

  જ્યારે (c_parser_next_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      અચલ અક્ષર *tok_s = IDENTIFIER_POINTER (tok->કિંમત);
      વૃક્ષ t = lookup_name (tok->કિંમત);
      જો (t == NULL_વૃક્ષ)
	{
	  undeclared_variable (tok->location, tok->કિંમત);
	  t = error_mark_ગાંઠ;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      વૃક્ષ legacy_traits = NULL_વૃક્ષ;
      જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  અચલ અક્ષર *tok_a
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_found_close (parser);

	  જો (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      જાઓ end;
	    }
	  legacy_traits = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
	  જો (legacy_traits == error_mark_ગાંઠ)
	    જાઓ end;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  જો (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.add_fixit_replace (alloc_loc, "traits");
	      richloc.add_fixit_ઉમેરો_after (close_loc, ": ");
	      richloc.add_fixit_ઉમેરો_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      જો (seen_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  જાઓ end;
	}
      seen_allocators = સાચું;

      વૃક્ષ c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_USES_ALLOCATORS);
      OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c) = memspace_પદાવલિ;
      OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
    }

  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      જાઓ parse_next;
    }

 end:
  parens.skip_until_found_close (parser);
  પાછા nl;
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

સ્થિર વૃક્ષ
c_parser_omp_clause_linear (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  વૃક્ષ nl, c, step;
  ગણના omp_clause_linear_kind kind = OMP_CLAUSE_LINEAR_DEFAULT;
  તાર્કિક old_linear_modifier = ખોટું;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      અચલ અક્ષર *p = IDENTIFIER_POINTER (tok->કિંમત);
      જો (strcmp ("val", p) == 0)
	kind = OMP_CLAUSE_LINEAR_VAL;
      જો (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	kind = OMP_CLAUSE_LINEAR_DEFAULT;
      જો (kind != OMP_CLAUSE_LINEAR_DEFAULT)
	{
	  old_linear_modifier = સાચું;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_LINEAR, list);

  જો (kind != OMP_CLAUSE_LINEAR_DEFAULT)
    {
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_found_close (parser);
    }

  જો (c_parser_next_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = પદાવલિ_loc;
      તાર્કિક has_modifiers = ખોટું;
      જો (kind == OMP_CLAUSE_LINEAR_DEFAULT
	  && c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  અચલ અક્ષર *p = IDENTIFIER_POINTER (tok->કિંમત);
	  unsigned પૂર્ણાંક pos = 0;
	  જો (strcmp ("val", p) == 0)
	    pos = 2;
	  નહીંતર જો (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      જો (c_parser_check_balanced_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      નહીંતર
		pos = 0;
	    }
	  જો (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      જો (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = સાચું;
	    }
	}
      જો (has_modifiers)
	{
	  step = NULL_વૃક્ષ;
	  જ્યારે (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      અચલ અક્ષર *p = IDENTIFIER_POINTER (tok->કિંમત);
	      જો (strcmp ("val", p) == 0)
		{
		  જો (kind != OMP_CLAUSE_LINEAR_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  kind = OMP_CLAUSE_LINEAR_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      નહીંતર જો (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  જો (parens2.require_open (parser))
		    {
		      જો (step)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      પદાવલિ_loc = c_parser_peek_token (parser)->location;
		      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
		      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું,
						       સાચું);
		      step = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
		      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (step)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  step = integer_one_ગાંઠ;
			}
		      parens2.skip_until_found_close (parser);
		    }
		  નહીંતર
		    તોડો;
		}
	      નહીંતર
		તોડો;
	      જો (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ચાલુ;
		}
	      તોડો;
	    }
	  જો (!step)
	    step = integer_one_ગાંઠ;
	}
      નહીંતર
	{
	  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
	  step = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
	  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (step)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      step = integer_one_ગાંઠ;
	    }
	}

    }
  નહીંતર
    step = integer_one_ગાંઠ;

  માટે (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_LINEAR_STEP (c) = step;
      OMP_CLAUSE_LINEAR_KIND (c) = kind;
      OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c) = old_linear_modifier;
    }

  જો (old_linear_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      જો (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_remove (rm1_loc);
	  જો (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.add_fixit_remove (rm2_loc);
	      richloc.add_fixit_ઉમેરો_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.add_fixit_ઉમેરો_before (close_loc, ")");
	    }
	  નહીંતર
	    richloc.add_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_found_close (parser);
  પાછા nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_nontemporal (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_safelen (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ c, t;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
  t = પદાવલિ.કિંમત;
  t = c_fully_fold (t, ખોટું, ખાલી);
  જો (વૃક્ષ_CODE (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t))
      || વૃક્ષ_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_વૃક્ષ;
    }

  parens.skip_until_found_close (parser);
  જો (t == NULL_વૃક્ષ || t == error_mark_ગાંઠ)
    પાછા list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_પદાવલિ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

સ્થિર વૃક્ષ
c_parser_omp_clause_simdlen (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ c, t = NULL_વૃક્ષ, type = NULL_વૃક્ષ, ભાજક = NULL_વૃક્ષ;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  unsigned pos = 3;
  જો (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત),
		 "scaled") == 0
      && c_parser_check_balanced_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      સંરચના c_type_name *ctype = c_parser_type_name (parser);
      જો (ctype == ખાલી
	  || (type = groktypename (ctype, ખાલી, ખાલી)) == ખાલી
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && વૃક્ષ_CODE (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_ગાંઠ;
	}
      નહીંતર જો (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  પદાવલિ = convert_lvalue_to_rvalue (loc, પદાવલિ, ખોટું, સાચું);
	  ભાજક = પદાવલિ.કિંમત;
	  ભાજક = c_fully_fold (ભાજક, ખોટું, ખાલી);
	  જો (વૃક્ષ_CODE (ભાજક) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (ભાજક))
	      || વૃક્ષ_int_cst_sgn (ભાજક) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_ગાંઠ;
	    }
	}
      parens2.skip_until_found_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  જો (type != error_mark_ગાંઠ)
    {
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);
      જો (વૃક્ષ_CODE (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t))
	  || વૃક્ષ_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_વૃક્ષ;
	}
    }

  parens.skip_until_found_close (parser);
  જો (type == error_mark_ગાંઠ || t == NULL_વૃક્ષ || t == error_mark_ગાંઠ)
    પાછા list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_પદાવલિ (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_ભાજક (c) = ભાજક;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

સ્થિર વૃક્ષ
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   વૃક્ષ list, તાર્કિક depend_p)
{
  વૃક્ષ vec = ખાલી;
  જો (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      પાછા list;
    }

  જો (!depend_p)
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_સંખ્યા
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  વૃક્ષ val = c_parser_peek_nth_token (parser, 3)->કિંમત;
	  જો (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      વૃક્ષ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      પાછા u;
	    }
	}
    }



  જ્યારે (c_parser_next_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_kind == C_ID_ID)
    {
      વૃક્ષ t = lookup_name (c_parser_peek_token (parser)->કિંમત);
      વૃક્ષ addend = ખાલી;

      જો (t == NULL_વૃક્ષ)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->કિંમત);
	  t = error_mark_ગાંઠ;
	}

      c_parser_consume_token (parser);

      તાર્કિક neg = ખોટું;
      જો (c_parser_next_token_is (parser, CPP_MINUS))
	neg = સાચું;
      નહીંતર જો (!c_parser_next_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_ગાંઠ;
	  neg = ખોટું;
	  જાઓ add_to_vector;
	}
      c_parser_consume_token (parser);

      જો (c_parser_next_token_is_not (parser, CPP_સંખ્યા))
	{
	  c_parser_error (parser, "expected integer");
	  પાછા list;
	}

      addend = c_parser_peek_token (parser)->કિંમત;
      જો (વૃક્ષ_CODE (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  પાછા list;
	}
      c_parser_consume_token (parser);

    add_to_vector:
      જો (t != error_mark_ગાંઠ)
	{
	  vec = વૃક્ષ_cons (addend, t, vec);
	  જો (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      જો (c_parser_next_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_kind != C_ID_ID)
	તોડો;

      c_parser_consume_token (parser);
    }

  જો (vec == NULL_વૃક્ષ)
    પાછા list;

  વૃક્ષ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_KIND (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  પાછા u;
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

સ્થિર વૃક્ષ
c_parser_omp_iterators (c_parser *parser)
{
  વૃક્ષ ret = NULL_વૃક્ષ, *last = &ret;
  c_parser_consume_token (parser);

  ધકેલો_scope ();

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા error_mark_ગાંઠ;

  કરો
    {
      વૃક્ષ iter_type = NULL_વૃક્ષ, type_પદાવલિ = NULL_વૃક્ષ;
      જો (c_parser_next_tokens_start_typename (parser, cla_prefer_id))
	{
	  સંરચના c_type_name *type = c_parser_type_name (parser);
	  જો (type != ખાલી)
	    iter_type = groktypename (type, &type_પદાવલિ, ખાલી);
	}
      જો (iter_type == NULL_વૃક્ષ)
	iter_type = integer_type_ગાંઠ;

      location_t loc = c_parser_peek_token (parser)->location;
      જો (!c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  તોડો;
	}

      વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
      c_parser_consume_token (parser);

      જો (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	તોડો;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (eloc, પદાવલિ, સાચું, ખોટું);
      વૃક્ષ begin = પદાવલિ.કિંમત;

      જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	તોડો;

      eloc = c_parser_peek_token (parser)->location;
      પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (eloc, પદાવલિ, સાચું, ખોટું);
      વૃક્ષ end = પદાવલિ.કિંમત;

      વૃક્ષ step = integer_one_ગાંઠ;
      જો (c_parser_next_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	  પદાવલિ = convert_lvalue_to_rvalue (eloc, પદાવલિ, સાચું, ખોટું);
	  step = પદાવલિ.કિંમત;
	}

      વૃક્ષ iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *last = make_omp_iterator ();
      OMP_ITERATOR_VAR (*last) = iter_var;
      OMP_ITERATOR_BEGIN (*last) = begin;
      OMP_ITERATOR_END (*last) = end;
      OMP_ITERATOR_STEP (*last) = step;
      last = &વૃક્ષ_CHAIN (*last);

      જો (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  ચાલુ;
	}
      તોડો;
    }
  જ્યારે (1);

  parens.skip_until_found_close (parser);
  પાછા ret ? ret : error_mark_ગાંઠ;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

સ્થિર વૃક્ષ
c_parser_omp_clause_affinity (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ nl, iterators = NULL_વૃક્ષ;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      તાર્કિક parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      જો (parse_iter)
	{
	  unsigned n = 3;
	  parse_iter = (c_parser_check_balanced_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      જો (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      જો (iterators)
		કાઢો_scope ();
	      parens.skip_until_found_close (parser);
	      પાછા list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  જો (iterators)
    {
      વૃક્ષ block = કાઢો_scope ();
      જો (iterators != error_mark_ગાંઠ)
	{
	  OMP_ITERATOR_BLOCK (iterators) = block;
	  માટે (વૃક્ષ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_વૃક્ષ_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  પાછા nl;
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

સ્થિર વૃક્ષ
c_parser_omp_clause_depend (c_parser *parser, વૃક્ષ list, location_t here)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ગણના omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_LAST;
  ગણના omp_clause_doacross_kind dkind = OMP_CLAUSE_DOACROSS_LAST;
  વૃક્ષ nl, c, iterators = NULL_વૃક્ષ;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  કરો
    {
      જો (c_parser_next_token_is_not (parser, CPP_NAME))
	જાઓ invalid_kind;

      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp ("iterator", p) == 0 && iterators == NULL_વૃક્ષ)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  ચાલુ;
	}
      જો (strcmp ("in", p) == 0)
	kind = OMP_CLAUSE_DEPEND_IN;
      નહીંતર જો (strcmp ("inout", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUT;
      નહીંતર જો (strcmp ("inoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_INOUTSET;
      નહીંતર જો (strcmp ("mutexinoutset", p) == 0)
	kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      નહીંતર જો (strcmp ("out", p) == 0)
	kind = OMP_CLAUSE_DEPEND_OUT;
      નહીંતર જો (strcmp ("depobj", p) == 0)
	kind = OMP_CLAUSE_DEPEND_DEPOBJ;
      નહીંતર જો (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      નહીંતર જો (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (here, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SOURCE;
	}
      નહીંતર
	જાઓ invalid_kind;
      તોડો;
    }
  જ્યારે (1);

  c_parser_consume_token (parser);

  જો (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_SOURCE
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      કાઢો_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_SOURCE ? "source" : "sink");
      iterators = NULL_વૃક્ષ;
    }

  જો (dkind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_વૃક્ષ;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_found_close (parser);
      પાછા c;
    }

  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    જાઓ resync_fail;

  જો (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, સાચું);
  નહીંતર
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      જો (iterators)
	{
	  વૃક્ષ block = કાઢો_scope ();
	  જો (iterators == error_mark_ગાંઠ)
	    iterators = NULL_વૃક્ષ;
	  નહીંતર
	    OMP_ITERATOR_BLOCK (iterators) = block;
	}

      માટે (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_KIND (c) = kind;
	  જો (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_વૃક્ષ_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_found_close (parser);
  પાછા nl;

 invalid_kind:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  જો (iterators)
    કાઢો_scope ();
  પાછા list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

સ્થિર વૃક્ષ
c_parser_omp_clause_doacross (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ગણના omp_clause_doacross_kind kind = OMP_CLAUSE_DOACROSS_LAST;
  વૃક્ષ nl;
  અચલ અક્ષર *p;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો (c_parser_next_token_is_not (parser, CPP_NAME))
    જાઓ invalid_kind;

  p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
  જો (strcmp ("sink", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SINK;
  નહીંતર જો (strcmp ("source", p) == 0)
    kind = OMP_CLAUSE_DOACROSS_SOURCE;
  નહીંતર
    જાઓ invalid_kind;

  c_parser_consume_token (parser);

  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    જાઓ resync_fail;

  જો (kind == OMP_CLAUSE_DOACROSS_SOURCE)
    {
      જો (c_parser_next_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_KIND (nl) = OMP_CLAUSE_DOACROSS_SOURCE;
      OMP_CLAUSE_DECL (nl) = NULL_વૃક્ષ;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  નહીંતર
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, ખોટું);

  parens.skip_until_found_close (parser);
  પાછા nl;

 invalid_kind:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_found_close (parser);
  પાછા list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

સ્થિર વૃક્ષ
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  ગણના omp_clause_fallback_kind kind = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  unsigned n = 3;
  જો (c_parser_next_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  પાછા list;
	}
      c_parser_consume_token (parser);
      જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	પાછા list;
      p = "";
      જો (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "abort") == 0)
	kind = OMP_CLAUSE_FALLBACK_ABORT;
      નહીંતર જો (strcmp (p, "default_mem") == 0)
	kind = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      નહીંતર જો (strcmp (p, "null") == 0)
	kind = OMP_CLAUSE_FALLBACK_NULL;
      નહીંતર
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  પાછા list;
	}
      c_parser_consume_token (parser);
      જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	પાછા list;
      જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	પાછા list;
    }
  location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
  વૃક્ષ size = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
  parens.skip_until_found_close (parser);

  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (size)))
    {
      error_at (પદાવલિ_loc, "expected integer expression");
      પાછા list;
    }

  /* Attempt to statically determine when the number is negative.  */
  વૃક્ષ c = fold_build2_loc (પદાવલિ_loc, LT_પદાવલિ, boolean_type_ગાંઠ, size,
			    build_int_cst (વૃક્ષ_TYPE (size), 0));
  protected_set_પદાવલિ_location (c, પદાવલિ_loc);
  જો (c == boolean_true_ગાંઠ)
    {
      warning_at (પદાવલિ_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      size = integer_zero_ગાંઠ;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_KIND (c) = kind;
  OMP_CLAUSE_DYN_GROUPPRIVATE_પદાવલિ (c) = size;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  પાછા list;
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

સ્થિર વૃક્ષ
c_parser_omp_clause_map (c_parser *parser, વૃક્ષ list, તાર્કિક declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ nl, c;
  ગણના gomp_map_kind kind = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  પૂર્ણાંક pos = 1;
  પૂર્ણાંક map_kind_pos = 0;
  પૂર્ણાંક iterator_length = 0;
  માટે (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      જો (tok->type != CPP_NAME)
	તોડો;

      અચલ અક્ષર *p = IDENTIFIER_POINTER (tok->કિંમત);
      c_token *next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      જો (strcmp (p, "iterator") == 0 && next_tok->type == CPP_OPEN_PAREN)
	{
	  unsigned n = pos + 2;
	  જો (c_parser_check_balanced_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_length = n - pos + 1;
	      pos = n;
	      next_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      જો (next_tok->type == CPP_COLON)
	{
	  map_kind_pos = pos;
	  તોડો;
	}

      જો (next_tok->type == CPP_COMMA)
	pos++;
      નહીંતર જો (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  unsigned પૂર્ણાંક npos = pos + 2;
	  જો (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  પૂર્ણાંક always_modifier = 0;
  પૂર્ણાંક close_modifier = 0;
  પૂર્ણાંક present_modifier = 0;
  પૂર્ણાંક mapper_modifier = 0;
  પૂર્ણાંક અંક_commas = 0;
  પૂર્ણાંક અંક_identifiers = 0;
  વૃક્ષ mapper_name = NULL_વૃક્ષ;
  વૃક્ષ iterators = NULL_વૃક્ષ;
  માટે (પૂર્ણાંક pos = 1; pos < map_kind_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      જો (tok->type == CPP_COMMA)
	{
	  ++અંક_commas;
	  જો (અંક_commas > અંક_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  ચાલુ;
	}

      અચલ અક્ષર *p = IDENTIFIER_POINTER (tok->કિંમત);
      જો (strcmp ("always", p) == 0)
	{
	  જો (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_found_close (parser);
	      પાછા list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (strcmp ("close", p) == 0)
	{
	  જો (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_found_close (parser);
	      પાછા list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (strcmp ("iterator", p) == 0)
	{
	  જો (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      પાછા list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      નહીંતર જો (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  જો (mparens.require_open (parser))
	    {
	      જો (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  પાછા list;
		}

	      tok = c_parser_peek_token (parser);

	      પસંદગી (tok->type)
		{
		સ્થિતિ CPP_NAME:
		  {
		    mapper_name = tok->કિંમત;
		    c_parser_consume_token (parser);
		    જો (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  તોડો;

		સ્થિતિ CPP_KEYWORD:
		  જો (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      તોડો;
		    }
		  /* Fallthrough.  */

		મૂળભૂત:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  પાછા list;
		}

	      જો (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  પાછા list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      નહીંતર જો (strcmp ("present", p) == 0)
	{
	  જો (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      પાછા list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      નહીંતર
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_found_close (parser);
	  પાછા list;
	}
      ++અંક_identifiers;
      જો (અંક_identifiers - 1 > અંક_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_ઉમેરો_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      અંક_commas = અંક_identifiers - 1;
    }

  જો (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      પૂર્ણાંક always_present_modifier = always_modifier && present_modifier;

      જો (strcmp ("alloc", p) == 0)
	kind = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      નહીંતર જો (strcmp ("to", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TO
		: present_modifier ? GOMP_MAP_PRESENT_TO
		: always_modifier ? GOMP_MAP_ALWAYS_TO
		: GOMP_MAP_TO);
      નહીંતર જો (strcmp ("from", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      નહીંતર જો (strcmp ("tofrom", p) == 0)
	kind = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      નહીંતર જો (strcmp ("release", p) == 0)
	kind = GOMP_MAP_RELEASE;
      નહીંતર જો (strcmp ("delete", p) == 0)
	kind = GOMP_MAP_DELETE;
      નહીંતર
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  પાછા list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   સાચું);

  વૃક્ષ last_new = NULL_વૃક્ષ;

  જો (iterators)
    {
      વૃક્ષ block = કાઢો_scope ();
      જો (iterators == error_mark_ગાંઠ)
	iterators = NULL_વૃક્ષ;
      નહીંતર
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  માટે (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_SET_MAP_KIND (c, kind);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      last_new = c;
    }

  જો (mapper_name)
    {
      વૃક્ષ name = build_omp_clause (આગત_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ધકેલો_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (આગત_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_કાઢો_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_ગાંઠ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  parens.skip_until_found_close (parser);
  પાછા nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

સ્થિર વૃક્ષ
c_parser_omp_clause_device (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t પદાવલિ_loc;
  c_પદાવલિ પદાવલિ;
  વૃક્ષ c, t;
  તાર્કિક ancestor = ખોટું;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો (c_parser_next_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      અચલ અક્ષર *p = IDENTIFIER_POINTER (tok->કિંમત);
      જો (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  જો ((omp_requires_mask & OMP_REQUIRES_REVERSE_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_found_close (parser);
	      પાછા list;
	    }
	  ancestor = સાચું;
	}
      નહીંતર જો (strcmp ("device_num", p) == 0)
	;
      નહીંતર
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_found_close (parser);
	  પાછા list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  પદાવલિ_loc = c_parser_peek_token (parser)->location;
  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
  t = પદાવલિ.કિંમત;
  t = c_fully_fold (t, ખોટું, ખાલી);

  parens.skip_until_found_close (parser);

  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      પાછા list;
    }
  જો (ancestor && વૃક્ષ_CODE (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (પદાવલિ_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      પાછા list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  પાછા list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_dist_schedule (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ c, t = NULL_વૃક્ષ;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો (!c_parser_next_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      પાછા list;
    }

  c_parser_consume_token (parser);
  જો (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      t = પદાવલિ.કિંમત;
      t = c_fully_fold (t, ખોટું, ખાલી);
      parens.skip_until_found_close (parser);
    }
  નહીંતર
    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  જો (omp_find_clause (list, OMP_CLAUSE_DIST_SCHEDULE))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  જો (t == error_mark_ગાંઠ)
    પાછા list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_SCHEDULE);
  OMP_CLAUSE_DIST_SCHEDULE_CHUNK_પદાવલિ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

સ્થિર વૃક્ષ
c_parser_omp_clause_proc_bind (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ગણના omp_clause_proc_bind_kind kind;
  વૃક્ષ c;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp ("primary", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_PRIMARY;
      નહીંતર જો (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.add_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  kind = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      નહીંતર જો (strcmp ("close", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_CLOSE;
      નહીંતર જો (strcmp ("spread", p) == 0)
	kind = OMP_CLAUSE_PROC_BIND_SPREAD;
      નહીંતર
	જાઓ invalid_kind;
    }
  નહીંતર
    જાઓ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;

 invalid_kind:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_found_close (parser);
  પાછા list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

સ્થિર વૃક્ષ
c_parser_omp_clause_device_type (c_parser *parser, વૃક્ષ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ગણના omp_clause_device_type_kind kind;
  વૃક્ષ c;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp ("host", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_HOST;
      નહીંતર જો (strcmp ("nohost", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      નહીંતર જો (strcmp ("any", p) == 0)
	kind = OMP_CLAUSE_DEVICE_TYPE_ANY;
      નહીંતર
	જાઓ invalid_kind;
    }
  નહીંતર
    જાઓ invalid_kind;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_found_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_KIND (c) = kind;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;

 invalid_kind:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_found_close (parser);
  પાછા list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

સ્થિર વૃક્ષ
c_parser_omp_clause_from_to (c_parser *parser, ગણના omp_clause_code kind,
			     વૃક્ષ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  પૂર્ણાંક pos = 1, colon_pos = 0;
  પૂર્ણાંક iterator_length = 0;

  જ્યારે (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      અચલ અક્ષર *identifier =
	IDENTIFIER_POINTER (c_parser_peek_nth_token_raw (parser, pos)->કિંમત);
      જો (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  unsigned પૂર્ણાંક npos = pos + 2;
	  જો (c_parser_check_balanced_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      જો (strcmp (identifier, "iterator") == 0)
		iterator_length = npos - pos + 1;
	      pos = npos;
	    }
	}
      જો (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      નહીંતર
	pos++;
      જો (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  તોડો;
	}
    }

  તાર્કિક present = ખોટું, mapper_modifier = ખોટું;
  વૃક્ષ iterators = NULL_વૃક્ષ;
  વૃક્ષ mapper_name = NULL_વૃક્ષ;

  માટે (પૂર્ણાંક pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      જો (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ચાલુ;
	}
      અચલ અક્ષર *p = IDENTIFIER_POINTER (token->કિંમત);
      જો (strcmp ("present", p) == 0)
	{
	  જો (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_found_close (parser);
	      પાછા list;
	    }
	  present = સાચું;
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (strcmp ("iterator", p) == 0)
	{
	  જો (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_found_close (parser);
	      પાછા list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_length - 1;
	}
      નહીંતર જો (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  જો (mparens.require_open (parser))
	    {
	      જો (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_found_close (parser);
		  પાછા list;
		}

	      token = c_parser_peek_token (parser);
	      પસંદગી (token->type)
		{
		સ્થિતિ CPP_NAME:
		  {
		    mapper_name = token->કિંમત;
		    c_parser_consume_token (parser);
		  }
		  તોડો;
		સ્થિતિ CPP_KEYWORD:
		  જો (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      તોડો;
		    }
		  /* FALLTHROUGH  */
		મૂળભૂત:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  પાછા list;
		}
	      જો (!mparens.require_close (parser))
		{
		  parens.skip_until_found_close (parser);
		  પાછા list;
		}
	      mapper_modifier = સાચું;
	      pos += 3;
	    }
	}
      નહીંતર
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    kind == OMP_CLAUSE_TO ? "to" : "from");
	  parens.skip_until_found_close (parser);
	  પાછા list;
	}
    }

  જો (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  વૃક્ષ nl = c_parser_omp_variable_list (parser, loc, kind, list);
  parens.skip_until_found_close (parser);

  જો (present)
    માટે (વૃક્ષ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  જો (iterators)
    {
      વૃક્ષ block = કાઢો_scope ();
      જો (iterators == error_mark_ગાંઠ)
	iterators = NULL_વૃક્ષ;
      નહીંતર
	OMP_ITERATOR_BLOCK (iterators) = block;
    }

  જો (iterators)
    માટે (વૃક્ષ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  જો (mapper_name)
    {
      વૃક્ષ last_new = NULL_વૃક્ષ;
      માટે (વૃક્ષ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	last_new = c;

      વૃક્ષ name = build_omp_clause (આગત_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_ધકેલો_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (last_new);

      name = build_omp_clause (આગત_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_SET_MAP_KIND (name, GOMP_MAP_કાઢો_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_pointer_ગાંઠ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (last_new);
      OMP_CLAUSE_CHAIN (last_new) = name;
    }

  પાછા nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_uniform (c_parser *parser, વૃક્ષ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  જો (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_UNIFORM,
					 list);
      parens.skip_until_found_close (parser);
    }
  પાછા list;
}

/* OpenMP 5.1
   full */

સ્થિર વૃક્ષ
c_parser_omp_clause_full (c_parser *parser, વૃક્ષ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_FULL, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ c = build_omp_clause (loc, OMP_CLAUSE_FULL);
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_partial (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ અંક = NULL_વૃક્ષ;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      અંક = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
      parens.skip_until_found_close (parser);

      જો (અંક == error_mark_ગાંઠ)
	પાછા list;

      mark_exp_read (અંક);
      અંક = c_fully_fold (અંક, ખોટું, ખાલી);
      HOST_WIDE_INT n;
      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (અંક))
	  || !વૃક્ષ_fits_shwi_p (અંક)
	  || (n = વૃક્ષ_to_shwi (અંક)) <= 0
	  || (પૂર્ણાંક) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  પાછા list;
	}
    }

  વૃક્ષ c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_પદાવલિ (c) = અંક;
  OMP_CLAUSE_CHAIN (c) = list;
  પાછા c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_novariants (c_parser *parser, વૃક્ષ list)
{
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  વૃક્ષ t = convert_lvalue_to_rvalue (loc, પદાવલિ, સાચું, સાચું).કિંમત;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, ખોટું, ખાલી);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  વૃક્ષ c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_પદાવલિ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  પાછા list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_nocontext (c_parser *parser, વૃક્ષ list)
{
  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
  વૃક્ષ t = convert_lvalue_to_rvalue (loc, પદાવલિ, સાચું, સાચું).કિંમત;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, ખોટું, ખાલી);
  parens.skip_until_found_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  વૃક્ષ c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_પદાવલિ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  પાછા list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_detach (c_parser *parser, વૃક્ષ list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  જો (!parens.require_open (parser))
    પાછા list;

  જો (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_found_close (parser);
      પાછા list;
    }

  વૃક્ષ t = lookup_name (c_parser_peek_token (parser)->કિંમત);
  જો (t == NULL_વૃક્ષ)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->કિંમત);
      parens.skip_until_found_close (parser);
      પાછા list;
    }
  c_parser_consume_token (parser);

  વૃક્ષ type = TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (t));
  જો (!INTEGRAL_TYPE_P (type)
      || વૃક્ષ_CODE (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_found_close (parser);
      પાછા list;
    }

  વૃક્ષ u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_found_close (parser);
  પાછા u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_destroy (c_parser *parser, વૃક્ષ list)
{
  વૃક્ષ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  માટે (વૃક્ષ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    વૃક્ષ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  પાછા nl;
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

સ્થિર વૃક્ષ
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    પાછા error_mark_ગાંઠ;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  જો (!c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    જ્યારે (સાચું)
      {
	str += (અક્ષર) GOMP_INTEROP_IFR_SEPARATOR;
	જો (c_parser_next_token_is (parser, CPP_STRING))
	  {
	    c_પદાવલિ cval = c_parser_string_literal (parser, ખોટું, ખોટું);
	    જો (cval.કિંમત == error_mark_ગાંઠ)
	      પાછા error_mark_ગાંઠ;
	    જો ((size_t) વૃક્ષ_STRING_LENGTH (cval.કિંમત)
		!= strlen (વૃક્ષ_STRING_POINTER (cval.કિંમત)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = સાચું;
		પાછા error_mark_ગાંઠ;
	      }

	    અક્ષર c = omp_get_fr_id_from_name (વૃક્ષ_STRING_POINTER (cval.કિંમત));
	    જો (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  વૃક્ષ_STRING_POINTER (cval.કિંમત));
	    str += c;
	  }
	નહીંતર
	  {
	    c_પદાવલિ cval = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	    વૃક્ષ કિંમત = c_fully_fold (cval.કિંમત, ખોટું, ખાલી);
	    જો (INTEGRAL_TYPE_P (વૃક્ષ_TYPE (કિંમત))
		&& વૃક્ષ_CODE (કિંમત) != INTEGER_CST)
	      કિંમત = convert_lvalue_to_rvalue (cval.get_start (), cval,
						ખોટું, સાચું).કિંમત;
	    જો (વૃક્ષ_CODE (કિંમત) != INTEGER_CST
		|| !વૃક્ષ_fits_shwi_p (કિંમત))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		પાછા error_mark_ગાંઠ;
	      }
	    HOST_WIDE_INT n = વૃક્ષ_to_shwi (કિંમત);
	    જો (n < 1 || n > GOMP_INTEROP_IFR_LAST)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (અક્ષર) n;
	  }
	str += (અક્ષર) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	જો (c_parser_next_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    ચાલુ;
	  }
	જો (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  પાછા error_mark_ગાંઠ;
	str += '\0';
	વૃક્ષ res = build_string (str.length (), str.data ());
	વૃક્ષ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ગાંઠ,
						  str.length ());
	પાછા res;
      }

  /* New format. */
  std::string str2;
  જ્યારે (સાચું)
    {
      જો (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	પાછા error_mark_ગાંઠ;
      str += (અક્ષર) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      તાર્કિક has_fr = ખોટું;
      જ્યારે (સાચું)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  જો (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_POINTER (tok->કિંમત)) != 0
		  && strcmp("attr", IDENTIFIER_POINTER (tok->કિંમત)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      પાછા error_mark_ગાંઠ;
	    }
	  c_parser_consume_token (parser);
	  તાર્કિક is_fr = IDENTIFIER_POINTER (tok->કિંમત)[0] == 'f';
	  જો (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      પાછા error_mark_ગાંઠ;
	    }
	  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    પાછા error_mark_ગાંઠ;
	  જ્યારે (સાચું)
	    {
	      જો (c_parser_next_token_is (parser, CPP_STRING))
		{
		  c_પદાવલિ cval = c_parser_string_literal (parser, ખોટું, ખોટું);
		  વૃક્ષ કિંમત = cval.કિંમત;
		  જો (કિંમત == error_mark_ગાંઠ)
		    પાછા error_mark_ગાંઠ;
		  જો ((size_t) વૃક્ષ_STRING_LENGTH (કિંમત)
		      != strlen (વૃક્ષ_STRING_POINTER (કિંમત)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = સાચું;
		      પાછા error_mark_ગાંઠ;
		    }
		  જો (!is_fr)
		    {
		      જો (!startswith (વૃક્ષ_STRING_POINTER (કિંમત), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = સાચું;
			  પાછા error_mark_ગાંઠ;
			}
		      જો (strchr (વૃક્ષ_STRING_POINTER (કિંમત), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = સાચું;
			  પાછા error_mark_ગાંઠ;
			}
		      str2 += વૃક્ષ_STRING_POINTER (કિંમત);
		      str2 += '\0';
		    }
		  નહીંતર
		    {
		      જો (*વૃક્ષ_STRING_POINTER (કિંમત) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  પાછા error_mark_ગાંઠ;
			}
		      અક્ષર c = omp_get_fr_id_from_name (વૃક્ષ_STRING_POINTER (કિંમત));
		      જો (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    વૃક્ષ_STRING_POINTER (કિંમત));
		     str += c;
		     has_fr = સાચું;
		    }
		}
	      નહીંતર જો (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  પાછા error_mark_ગાંઠ;
		}
	      નહીંતર
		{
		  c_પદાવલિ cval = c_parser_પદાવલિ_no_commas (parser, ખાલી);
		  વૃક્ષ કિંમત = c_fully_fold (cval.કિંમત, ખોટું, ખાલી);
		  જો (INTEGRAL_TYPE_P (વૃક્ષ_TYPE (કિંમત))
		      && વૃક્ષ_CODE (કિંમત) != INTEGER_CST)
		    કિંમત = convert_lvalue_to_rvalue (cval.get_start (), cval,
						      ખોટું, સાચું).કિંમત;

		  જો (વૃક્ષ_CODE (કિંમત) != INTEGER_CST
		      || !વૃક્ષ_fits_shwi_p (કિંમત))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      પાછા error_mark_ગાંઠ;
		    }
		  HOST_WIDE_INT n = વૃક્ષ_to_shwi (કિંમત);
		  જો (n < 1 || n > GOMP_INTEROP_IFR_LAST)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (અક્ષર) n;
		  has_fr = સાચું;
		}
	      જો (!is_fr
		  && c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ચાલુ;
		}
	      જો (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		પાછા error_mark_ગાંઠ;
	      તોડો;
	    }
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ચાલુ;
	    }
	  જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    તોડો;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  પાછા error_mark_ગાંઠ;
	}
      str += (અક્ષર) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	તોડો;
      જો (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	પાછા error_mark_ગાંઠ;
    }
  c_parser_consume_token (parser);
  str += '\0';
  વૃક્ષ res = build_string (str.length (), str.data ());
  વૃક્ષ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ગાંઠ,
						  str.length ());
  પાછા res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

સ્થિર તાર્કિક
c_parser_omp_clause_init_modifiers (c_parser *parser, તાર્કિક *target,
				    તાર્કિક *targetsync, વૃક્ષ *prefer_type_વૃક્ષ)
{
  *target = ખોટું;
  *targetsync = ખોટું;
  *prefer_type_વૃક્ષ = NULL_વૃક્ષ;

  કરો
    {
      c_token *tok = c_parser_peek_token (parser);
      જો (tok->type != CPP_NAME)
	જાઓ fail;
      અચલ અક્ષર *p = IDENTIFIER_POINTER (tok->કિંમત);
      જો (strcmp ("targetsync", p) == 0)
	{
	  જો (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = સાચું;
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (strcmp ("target", p) == 0)
	{
	  જો (*target)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *target = સાચું;
	  c_parser_consume_token (parser);
	}
      નહીંતર જો (strcmp ("prefer_type", p) == 0)
	{
	  જો (*prefer_type_વૃક્ષ != NULL_વૃક્ષ)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_વૃક્ષ = c_parser_omp_modifier_prefer_type (parser);
	  જો (*prefer_type_વૃક્ષ == error_mark_ગાંઠ)
	    પાછા ખોટું;
	}
      નહીંતર
	જાઓ fail;
      tok = c_parser_peek_token (parser);
      જો (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ચાલુ;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      પાછા સાચું;
    }
  જ્યારે (સાચું);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  પાછા ખોટું;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
     target
     targetsync
     prefer_type (preference-specification) */

સ્થિર વૃક્ષ
c_parser_omp_clause_init (c_parser *parser, વૃક્ષ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા list;

  તાર્કિક target = ખોટું;
  તાર્કિક targetsync = ખોટું;
  વૃક્ષ prefer_type_વૃક્ષ = NULL_વૃક્ષ;

  જો (!c_parser_omp_clause_init_modifiers (parser, &target, &targetsync,
					   &prefer_type_વૃક્ષ)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      જો (prefer_type_વૃક્ષ != error_mark_ગાંઠ)
	parens.skip_until_found_close (parser);
      પાછા list;
    }

  જો (!target && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  વૃક્ષ nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					ખોટું);
  parens.skip_until_found_close (parser);

  માટે (વૃક્ષ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      વૃક્ષ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      જો (target)
	OMP_CLAUSE_INIT_TARGET (c) = 1;
      જો (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      જો (prefer_type_વૃક્ષ)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_વૃક્ષ;
    }
  પાછા nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_use (c_parser *parser, વૃક્ષ list)
{
  પાછા c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

સ્થિર વૃક્ષ
c_parser_omp_clause_interop (c_parser *parser, વૃક્ષ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  વૃક્ષ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  માટે (વૃક્ષ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      વૃક્ષ_USED (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  પાછા nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

સ્થિર વૃક્ષ
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_mask mask,
			   અચલ અક્ષર *where, તાર્કિક finish_p = સાચું,
			   તાર્કિક target_p = ખોટું)
{
  વૃક્ષ clauses = ખાલી;
  તાર્કિક first = સાચું;

  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      અચલ અક્ષર *c_name;
      વૃક્ષ prev = clauses;

      જો (!first && c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      પસંદગી (c_kind)
	{
	સ્થિતિ PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "attach";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copy";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyin";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "copyout";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "create";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "delete";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, સાચું);
	  c_name = "default";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "detach";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_data_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "device_resident";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_GANG,
						c_name, clauses);
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "host";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, ખોટું);
	  c_name = "if";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "link";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "no_create";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_અંક_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_અંક_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_અંક_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_અંક_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "present";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     ખોટું, clauses);
	  c_name = "reduction";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_SELF:
	  જો ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  નહીંતર
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_data_clause (parser, c_kind, clauses);
	  c_name = "self";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (here, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_VECTOR:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_VECTOR,
						c_name,	clauses);
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_VECTOR_LENGTH:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_VECTOR_LENGTH,
						     clauses);
	  c_name = "vector_length";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  તોડો;
	સ્થિતિ PRAGMA_OACC_CLAUSE_WORKER:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, here, OMP_CLAUSE_WORKER,
						c_name, clauses);
	  તોડો;
	મૂળભૂત:
	  c_parser_error (parser, "expected an OpenACC clause");
	  જાઓ saw_error;
	}

      first = ખોટું;

      જો (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  જો (finish_p)
    પાછા c_finish_omp_clauses (clauses, target_p ? C_ORT_ACC_TARGET
						   : C_ORT_ACC);

  પાછા clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

સ્થિર વૃક્ષ
c_parser_omp_all_clauses (c_parser *parser, omp_clause_mask mask,
			  અચલ અક્ષર *where, તાર્કિક finish_p = સાચું,
			  પૂર્ણાંક nested = 0)
{
  વૃક્ષ clauses = ખાલી;
  તાર્કિક first = સાચું;

  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      અચલ અક્ષર *c_name;
      વૃક્ષ prev = clauses;

      જો (nested && c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	તોડો;

      જો (!first || nested != 2)
	{
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  નહીંતર જો (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);

      પસંદગી (c_kind)
	{
	સ્થિતિ PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, ખોટું);
	  c_name = "default";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, સાચું);
	  c_name = "if";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_IN_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_IN_REDUCTION,
					     સાચું, clauses);
	  c_name = "in_reduction";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_INDIRECT:
	  clauses = c_parser_omp_clause_indirect (parser, clauses);
	  c_name = "indirect";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_અંક_TASKS:
	  clauses = c_parser_omp_clause_અંક_tasks (parser, clauses);
	  c_name = "num_tasks";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_અંક_THREADS:
	  clauses = c_parser_omp_clause_અંક_threads (parser, clauses);
	  c_name = "num_threads";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_ORDER:
	  clauses = c_parser_omp_clause_order (parser, clauses);
	  c_name = "order";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_PRIORITY:
	  clauses = c_parser_omp_clause_priority (parser, clauses);
	  c_name = "priority";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     સાચું, clauses);
	  c_name = "reduction";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     સાચું, clauses);
	  c_name = "task_reduction";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  જો (!first)
	    {
	     clause_not_first:
	      error_at (here, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  જો (!first)
	    જાઓ clause_not_first;
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  જો (!first)
	    જાઓ clause_not_first;
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  જો (!first)
	    જાઓ clause_not_first;
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_TO:
	  જો ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (here);
	      richloc.add_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      વૃક્ષ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      માટે (વૃક્ષ c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_TO (c) = 1;
	      clauses = nl;
	    }
	  નહીંતર
	    clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_TO,
						   clauses);
	  c_name = "to";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_to (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_UNIFORM:
	  clauses = c_parser_omp_clause_uniform (parser, clauses);
	  c_name = "uniform";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_અંક_TEAMS:
	  clauses = c_parser_omp_clause_અંક_teams (parser, clauses);
	  c_name = "num_teams";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_THREAD_LIMIT:
	  clauses = c_parser_omp_clause_thread_limit (parser, clauses);
	  c_name = "thread_limit";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_LINEAR:
	  clauses = c_parser_omp_clause_linear (parser, clauses);
	  c_name = "linear";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_USES_ALLOCATORS:
	  clauses = c_parser_omp_clause_uses_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, here);
	  c_name = "depend";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, ખોટું);
	  c_name = "map";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DIST_SCHEDULE:
	  clauses = c_parser_omp_clause_dist_schedule (parser, clauses);
	  c_name = "dist_schedule";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_THREADS:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_THREADS,
					       clauses);
	  c_name = "threads";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_FULL:
	  c_name = "full";
	  clauses = c_parser_omp_clause_full (parser, clauses);
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  તોડો;
	સ્થિતિ PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  તોડો;
	મૂળભૂત:
	  c_parser_error (parser, "expected an OpenMP clause");
	  જાઓ saw_error;
	}

      first = ખોટું;

      જો (((mask >> c_kind) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (here, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  જો (!nested)
    c_parser_skip_to_pragma_eol (parser);

  જો (finish_p)
    {
      જો ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_UNIFORM)) != 0)
	પાછા c_finish_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      જો ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	પાછા c_finish_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      પાછા c_finish_omp_clauses (clauses, C_ORT_OMP);
    }

  પાછા clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

સ્થિર વૃક્ષ
c_parser_omp_structured_block (c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ stmt = ધકેલો_stmt_list ();
  parser->omp_attrs_forbidden_p = સાચું;
  c_parser_statement (parser, if_p);
  પાછા કાઢો_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

સ્થિર વૃક્ષ
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  વૃક્ષ stmt, clauses = NULL_વૃક્ષ;
  તાર્કિક readonly = ખોટું;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      જો (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_POINTER (token->કિંમત), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = સાચું;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_વૃક્ષ);
      parens.skip_until_found_close (parser);
    }

  જો (readonly)
    માટે (વૃક્ષ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_to_pragma_eol (parser);

  stmt = make_ગાંઠ (OACC_CACHE);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, loc);
  add_stmt (stmt);

  પાછા stmt;
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

સ્થિર વૃક્ષ
c_parser_oacc_data (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_DATA_CLAUSE_MASK,
				       "#pragma acc data");

  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  stmt = c_finish_oacc_data (loc, clauses, block);

  પાછા stmt;
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

સ્થિર શૂન્ય
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ clauses, stmt, t, decl;

  તાર્કિક error = ખોટું;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_MASK,
				       "#pragma acc declare");
  જો (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      પાછા;
    }

  માટે (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      જો (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = સાચું;
	  ચાલુ;
	}

      પસંદગી (OMP_CLAUSE_MAP_KIND (t))
	{
	સ્થિતિ GOMP_MAP_FIRSTPRIVATE_POINTER:
	સ્થિતિ GOMP_MAP_ALLOC:
	સ્થિતિ GOMP_MAP_TO:
	સ્થિતિ GOMP_MAP_FORCE_DEVICEPTR:
	સ્થિતિ GOMP_MAP_DEVICE_RESIDENT:
	  તોડો;

	સ્થિતિ GOMP_MAP_LINK:
	  જો (!global_bindings_p ()
	      && (વૃક્ષ_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = સાચું;
	      ચાલુ;
	    }
	  તોડો;

	મૂળભૂત:
	  જો (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = સાચું;
	      ચાલુ;
	    }
	  જો (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = સાચું;
	      ચાલુ;
	    }
	  નહીંતર જો (વૃક્ષ_PUBLIC (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = સાચું;
	      ચાલુ;
	    }
	  તોડો;
	}

      જો (!c_check_in_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = સાચું;
	  ચાલુ;
	}

      જો (lookup_attribute ("omp declare target", DECL_ATTRIBUTES (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ATTRIBUTES (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = સાચું;
	  ચાલુ;
	}

      જો (!error)
	{
	  વૃક્ષ id;

	  જો (OMP_CLAUSE_MAP_KIND (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  નહીંતર
	    id = get_identifier ("omp declare target");

	  DECL_ATTRIBUTES (decl)
			   = વૃક્ષ_cons (id, NULL_વૃક્ષ, DECL_ATTRIBUTES (decl));

	  જો (global_bindings_p ())
	    {
	      symtab_ગાંઠ *ગાંઠ = symtab_ગાંઠ::get (decl);
	      જો (ગાંઠ != ખાલી)
		{
		  ગાંઠ->offloadable = 1;
		  જો (ENABLE_OFFLOADING)
		    {
		      g->have_offload = સાચું;
		      જો (is_a <varpool_ગાંઠ *> (ગાંઠ))
			vec_safe_ધકેલો (offload_vars, decl);
		    }
		}
	    }
	}
    }

  જો (error || global_bindings_p ())
    પાછા;

  stmt = make_ગાંઠ (OACC_DECLARE);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, pragma_loc);

  add_stmt (stmt);

  પાછા;
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

સ્થિર શૂન્ય
c_parser_oacc_enter_exit_data (c_parser *parser, તાર્કિક enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ clauses, stmt;
  અચલ અક્ષર *p = "";

  c_parser_consume_pragma (parser);

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      c_parser_consume_token (parser);
    }

  જો (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = સાચું;
      c_parser_skip_to_pragma_eol (parser);
      પાછા;
    }

  જો (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_DATA_CLAUSE_MASK,
					 "#pragma acc enter data");
  નહીંતર
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_DATA_CLAUSE_MASK,
					 "#pragma acc exit data");

  જો (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_વૃક્ષ)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      પાછા;
    }

  stmt = enter ? make_ગાંઠ (OACC_ENTER_DATA) : make_ગાંઠ (OACC_EXIT_DATA);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, loc);
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

સ્થિર વૃક્ષ
c_parser_oacc_host_data (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ stmt, clauses, block;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_DATA_CLAUSE_MASK,
				       "#pragma acc host_data", ખોટું);
  જો (!omp_find_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      પાછા error_mark_ગાંઠ;
    }
  clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  stmt = c_finish_oacc_host_data (loc, clauses, block);
  પાછા stmt;
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
સ્થિર વૃક્ષ
c_parser_oacc_loop (location_t loc, c_parser *parser, અક્ષર *p_name,
		    omp_clause_mask mask, વૃક્ષ *cclauses, તાર્કિક *if_p)
{
  તાર્કિક is_parallel = ((mask >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  mask |= OACC_LOOP_CLAUSE_MASK;

  વૃક્ષ clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/cclauses == ખાલી,
					    /*target=*/is_parallel);
  જો (cclauses)
    {
      clauses = c_oacc_split_loop_clauses (clauses, cclauses, is_parallel);
      જો (*cclauses)
	*cclauses = c_finish_omp_clauses (*cclauses, C_ORT_ACC_TARGET);
      જો (clauses)
	clauses = c_finish_omp_clauses (clauses, C_ORT_ACC);
    }

  વૃક્ષ block = c_begin_compound_stmt (સાચું);
  વૃક્ષ stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, ખાલી,
				     if_p);
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા stmt;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_અંક_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_અંક_WORKERS)		\
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_અંક_GANGS)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_અંક_WORKERS)		\
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

સ્થિર વૃક્ષ
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       ગણના pragma_kind p_kind, અક્ષર *p_name, તાર્કિક *if_p)
{
  omp_clause_mask mask;
  ગણના વૃક્ષ_code code;
  પસંદગી (p_kind)
    {
    સ્થિતિ PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      mask = OACC_KERNELS_CLAUSE_MASK;
      code = OACC_KERNELS;
      તોડો;
    સ્થિતિ PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      mask = OACC_PARALLEL_CLAUSE_MASK;
      code = OACC_PARALLEL;
      તોડો;
    સ્થિતિ PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      mask = OACC_SERIAL_CLAUSE_MASK;
      code = OACC_SERIAL;
      તોડો;
    મૂળભૂત:
      gcc_unreachable ();
    }

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  વૃક્ષ block = c_begin_omp_parallel ();
	  વૃક્ષ clauses;
	  c_parser_oacc_loop (loc, parser, p_name, mask, &clauses, if_p);
	  પાછા c_finish_omp_construct (loc, code, block, clauses);
	}
    }

  વૃક્ષ clauses = c_parser_oacc_all_clauses (parser, mask, p_name,
					    /*finish_p=*/સાચું,
					    /*target=*/સાચું);

  વૃક્ષ block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));

  પાછા c_finish_omp_construct (loc, code, block, clauses);
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

સ્થિર શૂન્ય
c_parser_oacc_routine (c_parser *parser, ગણના pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_data data;
  data.error_seen = ખોટું;
  data.fndecl_seen = ખોટું;
  data.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      વૃક્ષ decl = NULL_વૃક્ષ;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      જો (name_token->type == CPP_NAME
	  && (name_token->id_kind == C_ID_ID
	      || name_token->id_kind == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->કિંમત);
	  જો (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->કિંમત);
	  c_parser_consume_token (parser);
	}
      નહીંતર
	c_parser_error (parser, "expected function name");

      જો (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  પાછા;
	}

      data.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_MASK,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      data.clauses = nreverse (data.clauses);

      જો (વૃક્ષ_CODE (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  પાછા;
	}

      c_finish_oacc_routine (&data, decl, ખોટું);
    }
  નહીંતર /* No optional '( name )'.  */
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
      જો (c_parser_next_token_is (parser, CPP_PRAGMA)
	  || c_parser_next_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (data.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  પાછા;
	}

      /* We only have to consider the pragma_external case here.  */
      જો (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  પૂર્ણાંક ext = disable_extension_diagnostics ();
	  કરો
	    c_parser_consume_token (parser);
	  જ્યારે (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, ખોટું, સાચું,
					 ખોટું, ખાલી, ખાલી, ખોટું, ખાલી, &data);
	  restore_extension_diagnostics (ext);
	}
      નહીંતર
	c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, ખોટું, સાચું,
				       ખોટું, ખાલી, ખાલી, ખોટું, ખાલી, &data);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

સ્થિર શૂન્ય
c_finish_oacc_routine (સંરચના oacc_routine_data *data, વૃક્ષ fndecl,
		       તાર્કિક is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  જો (data->error_seen
      || fndecl == error_mark_ગાંઠ)
    પાછા;

  જો (data->fndecl_seen)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      data->error_seen = સાચું;
      પાછા;
    }
  જો (fndecl == NULL_વૃક્ષ || વૃક્ષ_CODE (fndecl) != FUNCTION_DECL)
    {
      error_at (data->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      data->error_seen = સાચું;
      પાછા;
    }

  પૂર્ણાંક compatible
    = oacc_verify_routine_clauses (fndecl, &data->clauses, data->loc,
				   "#pragma acc routine");
  જો (compatible < 0)
    {
      data->error_seen = સાચું;
      પાછા;
    }
  જો (compatible > 0)
    {
    }
  નહીંતર
    {
      જો (વૃક્ષ_USED (fndecl) || (!is_defn && DECL_SAVED_વૃક્ષ (fndecl)))
	{
	  error_at (data->loc,
		    વૃક્ષ_USED (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  data->error_seen = સાચું;
	  પાછા;
	}

      /* Set the routine's level of parallelism.  */
      વૃક્ષ dims = oacc_build_routine_dims (data->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ATTRIBUTES (fndecl)
	= વૃક્ષ_cons (get_identifier ("omp declare target"),
		     data->clauses, DECL_ATTRIBUTES (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  data->fndecl_seen = સાચું;
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

સ્થિર શૂન્ય
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  વૃક્ષ clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_MASK,
					    "#pragma acc update");
  જો (omp_find_clause (clauses, OMP_CLAUSE_MAP) == NULL_વૃક્ષ)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      પાછા;
    }

  જો (parser->error)
    પાછા;

  વૃક્ષ stmt = make_ગાંઠ (OACC_UPDATE);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, loc);
  add_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#define OACC_WAIT_CLAUSE_MASK						\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OACC_CLAUSE_IF) )

સ્થિર વૃક્ષ
c_parser_oacc_wait (location_t loc, c_parser *parser, અક્ષર *p_name)
{
  વૃક્ષ clauses, list = NULL_વૃક્ષ, stmt = NULL_વૃક્ષ;

  જો (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_MASK, p_name);
  stmt = c_finish_oacc_wait (loc, list, clauses);
  add_stmt (stmt);

  પાછા stmt;
}

સંરચના c_omp_loc_વૃક્ષ
{
  location_t loc;
  વૃક્ષ var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
સ્થિર વૃક્ષ
c_check_omp_allocate_allocator_r (વૃક્ષ *tp, પૂર્ણાંક *, શૂન્ય *data)
{
  વૃક્ષ var = ((સંરચના c_omp_loc_વૃક્ષ *) data)->var;
  location_t loc = ((સંરચના c_omp_loc_વૃક્ષ *) data)->loc;
  જો (વૃક્ષ_CODE (*tp) == VAR_DECL && c_check_in_current_scope (*tp))
    {
      જો (linemap_location_before_p (લીટી_table, DECL_SOURCE_LOCATION (var),
				     DECL_SOURCE_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_SOURCE_LOCATION (*tp), "declared here");
	  inform (DECL_SOURCE_LOCATION (var),
		  "to be allocated variable declared here");
	  પાછા *tp;
	}
      નહીંતર
	{
	  gcc_assert (cur_stmt_list
		      && વૃક્ષ_CODE (cur_stmt_list) == STATEMENT_LIST);

	  વૃક્ષ_stmt_iterator l = tsi_last (cur_stmt_list);
	  જ્યારે (!tsi_end_p (l))
	    {
	      જો (linemap_location_before_p (લીટી_table, પદાવલિ_LOCATION (*l),
					     DECL_SOURCE_LOCATION (var)))
		  તોડો;
	      જો (વૃક્ષ_CODE (*l) == MODIFY_પદાવલિ
		  && વૃક્ષ_OPERAND (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (પદાવલિ_LOCATION (*l), "modified here");
		  inform (DECL_SOURCE_LOCATION (var),
			  "to be allocated variable declared here");
		  પાછા *tp;
		}
	      --l;
	    }
	}
    }
  પાછા NULL_વૃક્ષ;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

સ્થિર શૂન્ય
c_parser_omp_allocate (c_parser *parser)
{
  વૃક્ષ alignment = NULL_વૃક્ષ;
  વૃક્ષ allocator = NULL_વૃક્ષ;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  વૃક્ષ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_વૃક્ષ);
  કરો
    {
      જો (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      જો (!c_parser_next_token_is (parser, CPP_NAME))
	તોડો;
      matching_parens parens;
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      c_parser_consume_token (parser);
      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
      જો (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  તોડો;
	}
      જો (!parens.require_open (parser))
	તોડો;

      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, ખોટું, સાચું);
      પદાવલિ_loc = c_parser_peek_token (parser)->location;
      જો (પદાવલિ.કિંમત == error_mark_ગાંઠ)
	;
      નહીંતર જો (p[2] == 'i' && alignment)
	{
	  error_at (પદાવલિ_loc, "too many %qs clauses", "align");
	  તોડો;
	}
      નહીંતર જો (p[2] == 'i')
	{
	  alignment = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
	  જો (વૃક્ષ_CODE (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (વૃક્ષ_TYPE (alignment))
	      || વૃક્ષ_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (પદાવલિ_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_વૃક્ષ;
	    }
	}
      નહીંતર જો (allocator)
	{
	  error_at (પદાવલિ_loc, "too many %qs clauses", "allocator");
	  તોડો;
	}
      નહીંતર
	{
	  allocator = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
	  allocator_loc = પદાવલિ_loc;
	  વૃક્ષ orig_type
	    = પદાવલિ.original_type ? પદાવલિ.original_type : વૃક્ષ_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (allocator))
	      || વૃક્ષ_CODE (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (પદાવલિ_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			વૃક્ષ_TYPE (allocator));
	      allocator = NULL_વૃક્ષ;
	    }
	}
      parens.skip_until_found_close (parser);
    } જ્યારે (સાચું);
  c_parser_skip_to_pragma_eol (parser);

  c_mark_decl_jump_unsafe_in_current_scope ();
  માટે (વૃક્ષ c = nl; c != NULL_વૃક્ષ; c = OMP_CLAUSE_CHAIN (c))
    {
      વૃક્ષ var = OMP_CLAUSE_DECL (c);
      જો (વૃક્ષ_CODE (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  ચાલુ;
	}
      જો (!parser->in_omp_decl_attribute && !c_check_in_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_SOURCE_LOCATION (var), "declared here");
	  ચાલુ;
	}
      જો (lookup_attribute ("omp allocate", DECL_ATTRIBUTES (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  ચાલુ;
	}
      જો (વૃક્ષ_STATIC (var))
	{
	  જો (allocator == NULL_વૃક્ષ && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      ચાલુ;
	    }
	  નહીંતર જો (allocator
		   && (wi::to_widest (allocator) < 1
		       || wi::to_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::to_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::to_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  નહીંતર જો (allocator
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
      જો (allocator)
	{
	  સંરચના c_omp_loc_વૃક્ષ data
	    = {પદાવલિ_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_વૃક્ષ (&allocator, c_check_omp_allocate_allocator_r, &data, ખાલી);
	}
      DECL_ATTRIBUTES (var) = વૃક્ષ_cons (get_identifier ("omp allocate"),
					 build_વૃક્ષ_list (allocator, alignment),
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

સ્થિર શૂન્ય
c_parser_omp_atomic (location_t loc, c_parser *parser, તાર્કિક openacc)
{
  વૃક્ષ lhs = NULL_વૃક્ષ, rhs = NULL_વૃક્ષ, v = NULL_વૃક્ષ, r = NULL_વૃક્ષ;
  વૃક્ષ lhs1 = NULL_વૃક્ષ, rhs1 = NULL_વૃક્ષ;
  વૃક્ષ stmt, orig_lhs, unfolded_lhs = NULL_વૃક્ષ, unfolded_lhs1 = NULL_વૃક્ષ;
  ગણના વૃક્ષ_code code = ERROR_MARK, opcode = NOP_પદાવલિ;
  ગણના omp_memory_order memory_order = OMP_MEMORY_ORDER_UNSPECIFIED;
  સંરચના c_પદાવલિ પદાવલિ;
  location_t eloc;
  તાર્કિક structured_block = ખોટું;
  તાર્કિક swapped = ખોટું;
  તાર્કિક non_lvalue_p;
  વૃક્ષ clauses = NULL_વૃક્ષ;
  તાર્કિક capture = ખોટું;
  તાર્કિક compare = ખોટું;
  તાર્કિક weak = ખોટું;
  ગણના omp_memory_order fail = OMP_MEMORY_ORDER_UNSPECIFIED;
  તાર્કિક no_semicolon = ખોટું;
  તાર્કિક extra_scope = ખોટું;

  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      જો (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      જો (c_parser_next_token_is (parser, CPP_NAME))
	{
	  અચલ અક્ષર *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  ગણના વૃક્ષ_code new_code = ERROR_MARK;
	  ગણના omp_memory_order new_memory_order
	    = OMP_MEMORY_ORDER_UNSPECIFIED;
	  તાર્કિક new_capture = ખોટું;
	  તાર્કિક new_compare = ખોટું;
	  તાર્કિક new_weak = ખોટું;
	  ગણના omp_memory_order new_fail = OMP_MEMORY_ORDER_UNSPECIFIED;

	  જો (!strcmp (p, "read"))
	    new_code = OMP_ATOMIC_READ;
	  નહીંતર જો (!strcmp (p, "write"))
	    new_code = NOP_પદાવલિ;
	  નહીંતર જો (!strcmp (p, "update"))
	    new_code = OMP_ATOMIC;
	  નહીંતર જો (openacc && !strcmp (p, "capture"))
	    new_code = OMP_ATOMIC_CAPTURE_NEW;
	  નહીંતર જો (openacc)
	    {
	      p = ખાલી;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  નહીંતર જો (!strcmp (p, "capture"))
	    new_capture = સાચું;
	  નહીંતર જો (!strcmp (p, "compare"))
	    new_compare = સાચું;
	  નહીંતર જો (!strcmp (p, "weak"))
	    new_weak = સાચું;
	  નહીંતર જો (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      જો (!parens.require_open (parser))
		ચાલુ;

	      જો (c_parser_next_token_is (parser, CPP_NAME))
		{
		  અચલ અક્ષર *q
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

		  જો (!strcmp (q, "seq_cst"))
		    new_fail = OMP_MEMORY_ORDER_SEQ_CST;
		  નહીંતર જો (!strcmp (q, "acquire"))
		    new_fail = OMP_MEMORY_ORDER_ACQUIRE;
		  નહીંતર જો (!strcmp (q, "relaxed"))
		    new_fail = OMP_MEMORY_ORDER_RELAXED;
		}

	      જો (new_fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  જો (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  નહીંતર
		    fail = new_fail;
		}
	      નહીંતર
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_found_close (parser);
	      ચાલુ;
	    }
	  નહીંતર જો (!strcmp (p, "seq_cst"))
	    new_memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  નહીંતર જો (!strcmp (p, "acq_rel"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	  નહીંતર જો (!strcmp (p, "release"))
	    new_memory_order = OMP_MEMORY_ORDER_RELEASE;
	  નહીંતર જો (!strcmp (p, "acquire"))
	    new_memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  નહીંતર જો (!strcmp (p, "relaxed"))
	    new_memory_order = OMP_MEMORY_ORDER_RELAXED;
	  નહીંતર જો (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      ચાલુ;
	    }
	  નહીંતર
	    {
	      p = ખાલી;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  જો (p)
	    {
	      જો (new_code != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  જો (openacc
		      && code == OMP_ATOMIC
		      && new_code == OMP_ATOMIC_CAPTURE_NEW)
		    code = new_code;
		  નહીંતર જો (code != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  નહીંતર
		    code = new_code;
		}
	      નહીંતર જો (new_memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		{
		  જો (memory_order != OMP_MEMORY_ORDER_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  નહીંતર
		    memory_order = new_memory_order;
		}
	      નહીંતર જો (new_capture)
		{
		  જો (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  નહીંતર
		    capture = સાચું;
		}
	      નહીંતર જો (new_compare)
		{
		  જો (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  નહીંતર
		    compare = સાચું;
		}
	      નહીંતર જો (new_weak)
		{
		  જો (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  નહીંતર
		    weak = સાચું;
		}
	      c_parser_consume_token (parser);
	      ચાલુ;
	    }
	}
      તોડો;
    }
  c_parser_skip_to_pragma_eol (parser);

  જો (code == ERROR_MARK)
    code = OMP_ATOMIC;
  જો (capture)
    {
      જો (code != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      નહીંતર
	code = OMP_ATOMIC_CAPTURE_NEW;
    }
  જો (compare && code != OMP_ATOMIC && code != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = ખોટું;
    }
  જો (fail != OMP_MEMORY_ORDER_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_MEMORY_ORDER_UNSPECIFIED;
    }
  જો (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = ખોટું;
    }
  જો (openacc)
    memory_order = OMP_MEMORY_ORDER_RELAXED;
  નહીંતર જો (memory_order == OMP_MEMORY_ORDER_UNSPECIFIED)
    {
      omp_requires_mask
	= (ગણના omp_requires) (omp_requires_mask
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED);
      પસંદગી ((ગણના omp_memory_order)
	      (omp_requires_mask & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER))
	{
	સ્થિતિ OMP_MEMORY_ORDER_UNSPECIFIED:
	સ્થિતિ OMP_MEMORY_ORDER_RELAXED:
	  memory_order = OMP_MEMORY_ORDER_RELAXED;
	  તોડો;
	સ્થિતિ OMP_MEMORY_ORDER_SEQ_CST:
	  memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  તોડો;
	સ્થિતિ OMP_MEMORY_ORDER_ACQUIRE:
	  જો (code == NOP_પદાવલિ)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  નહીંતર
	    memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	  તોડો;
	સ્થિતિ OMP_MEMORY_ORDER_RELEASE:
	  જો (code == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	    }
	  નહીંતર
	    memory_order = OMP_MEMORY_ORDER_RELEASE;
	  તોડો;
	સ્થિતિ OMP_MEMORY_ORDER_ACQ_REL:
	  પસંદગી (code)
	    {
	    સ્થિતિ OMP_ATOMIC_READ:
	      memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	      તોડો;
	    સ્થિતિ NOP_પદાવલિ: /* atomic write */
	      memory_order = OMP_MEMORY_ORDER_RELEASE;
	      તોડો;
	    મૂળભૂત:
	      memory_order = OMP_MEMORY_ORDER_ACQ_REL;
	      તોડો;
	    }
	  તોડો;
	મૂળભૂત:
	  gcc_unreachable ();
	}
    }
  નહીંતર
    પસંદગી (code)
      {
      સ્થિતિ OMP_ATOMIC_READ:
	જો (memory_order == OMP_MEMORY_ORDER_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	નહીંતર જો (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_ACQUIRE;
	તોડો;
      સ્થિતિ NOP_પદાવલિ: /* atomic write */
	જો (memory_order == OMP_MEMORY_ORDER_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    memory_order = OMP_MEMORY_ORDER_SEQ_CST;
	  }
	નહીંતર જો (memory_order == OMP_MEMORY_ORDER_ACQ_REL)
	  memory_order = OMP_MEMORY_ORDER_RELEASE;
	તોડો;
      મૂળભૂત:
	તોડો;
      }
  જો (fail != OMP_MEMORY_ORDER_UNSPECIFIED)
    memory_order
      = (ગણના omp_memory_order) (memory_order
				 | (fail << OMP_FAIL_MEMORY_ORDER_SHIFT));

  પસંદગી (code)
    {
    સ્થિતિ OMP_ATOMIC_READ:
    સ્થિતિ NOP_પદાવલિ: /* atomic write */
      v = c_parser_cast_expression (parser, ખાલી).કિંમત;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, ખોટું, ખાલી, સાચું);
      જો (v == error_mark_ગાંઠ)
	જાઓ saw_error;
      જો (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      જો (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	જાઓ saw_error;
      જો (code == NOP_પદાવલિ)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  પદાવલિ = c_parser_expression (parser);
	  પદાવલિ = default_function_array_read_conversion (eloc, પદાવલિ);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  code = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_વૃક્ષ;
	  rhs = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી);
	  જો (rhs == error_mark_ગાંઠ)
	    જાઓ saw_error;
	}
      નહીંતર
	{
	  lhs = c_parser_cast_expression (parser, ખાલી).કિંમત;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, ખોટું, ખાલી, સાચું);
	  જો (lhs == error_mark_ગાંઠ)
	    જાઓ saw_error;
	  જો (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      જાઓ done;
    સ્થિતિ OMP_ATOMIC_CAPTURE_NEW:
      જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_block = સાચું;
	}
      નહીંતર જો (compare
	       && c_parser_next_token_is_keyword (parser, RID_IF))
	તોડો;
      નહીંતર
	{
	  v = c_parser_cast_expression (parser, ખાલી).કિંમત;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, ખોટું, ખાલી, સાચું);
	  જો (v == error_mark_ગાંઠ)
	    જાઓ saw_error;
	  જો (non_lvalue_p)
	    v = non_lvalue (v);
	  જો (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    જાઓ saw_error;
	  જો (compare && c_parser_next_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      જાઓ saw_error;
	    }
	}
      તોડો;
    મૂળભૂત:
      તોડો;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  જો (compare && c_parser_next_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      જો (!parens.require_open (parser))
	જાઓ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_પદાવલિ cmp_પદાવલિ;
      જો (r)
	{
	  cmp_પદાવલિ = c_parser_cast_expression (parser, ખાલી);
	  cmp_પદાવલિ = default_function_array_conversion (eloc, cmp_પદાવલિ);
	}
      નહીંતર
	cmp_પદાવલિ = c_parser_દ્વિઅંકી_expression (parser, ખાલી, void_list_ગાંઠ);
      parens.skip_until_found_close (parser);
      જો (cmp_પદાવલિ.કિંમત == error_mark_ગાંઠ)
	જાઓ saw_error;
      જો (r)
	{
	  જો (!c_વૃક્ષ_equal (cmp_પદાવલિ.કિંમત, unfolded_lhs))
	    જાઓ bad_if;
	  cmp_પદાવલિ.કિંમત = rhs1;
	  rhs1 = NULL_વૃક્ષ;
	  gcc_assert (વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) == EQ_પદાવલિ);
	}
      જો (વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) == EQ_પદાવલિ)
	;
      નહીંતર જો (!structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (પદાવલિ_LOC_OR_LOC (cmp_પદાવલિ.કિંમત, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  જાઓ saw_error;
	}
      નહીંતર જો (વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) != GT_પદાવલિ
	       && વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) != LT_પદાવલિ)
	{
	  error_at (પદાવલિ_LOC_OR_LOC (cmp_પદાવલિ.કિંમત, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  જાઓ saw_error;
	}
      જો (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	જાઓ saw_error;

      extra_scope = સાચું;
      eloc = c_parser_peek_token (parser)->location;
      પદાવલિ = c_parser_cast_expression (parser, ખાલી);
      lhs = પદાવલિ.કિંમત;
      પદાવલિ = default_function_array_conversion (eloc, પદાવલિ);
      unfolded_lhs = પદાવલિ.કિંમત;
      lhs = c_fully_fold (lhs, ખોટું, ખાલી, સાચું);
      orig_lhs = lhs;
      જો (lhs == error_mark_ગાંઠ)
	જાઓ saw_error;
      જો (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      જો (!c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  જાઓ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      rhs1 = પદાવલિ.કિંમત;

      જો (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	જાઓ saw_error;

      જો (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	જાઓ saw_error;

      extra_scope = ખોટું;
      no_semicolon = સાચું;

      જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (cmp_પદાવલિ.કિંમત, 0), unfolded_lhs))
	{
	  જો (વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) == EQ_પદાવલિ)
	    {
	      opcode = COND_પદાવલિ;
	      rhs = c_fully_fold (વૃક્ષ_OPERAND (cmp_પદાવલિ.કિંમત, 1),
				  ખોટું, ખાલી, સાચું);
	      rhs1 = c_fully_fold (rhs1, ખોટું, ખાલી, સાચું);
	    }
	  નહીંતર જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (cmp_પદાવલિ.કિંમત, 1), rhs1))
	    {
	      opcode = (વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) == GT_પદાવલિ
			? MIN_પદાવલિ : MAX_પદાવલિ);
	      rhs = c_fully_fold (rhs1, ખોટું, ખાલી, સાચું);
	      rhs1 = c_fully_fold (વૃક્ષ_OPERAND (cmp_પદાવલિ.કિંમત, 0),
				   ખોટું, ખાલી, સાચું);
	    }
	  નહીંતર
	    જાઓ bad_if;
	}
      નહીંતર જો (વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) == EQ_પદાવલિ)
	જાઓ bad_if;
      નહીંતર જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (cmp_પદાવલિ.કિંમત, 1), unfolded_lhs)
	       && c_વૃક્ષ_equal (વૃક્ષ_OPERAND (cmp_પદાવલિ.કિંમત, 0), rhs1))
	{
	  opcode = (વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) == GT_પદાવલિ
		    ? MAX_પદાવલિ : MIN_પદાવલિ);
	  rhs = c_fully_fold (rhs1, ખોટું, ખાલી, સાચું);
	  rhs1 = c_fully_fold (વૃક્ષ_OPERAND (cmp_પદાવલિ.કિંમત, 1),
			       ખોટું, ખાલી, સાચું);
	}
      નહીંતર
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  જાઓ saw_error;
	}

      જો (c_parser_next_token_is_keyword (parser, RID_ELSE))
	{
	  જો (code != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_block && r == NULL_વૃક્ષ)
	      || વૃક્ષ_CODE (cmp_પદાવલિ.કિંમત) != EQ_પદાવલિ)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      જાઓ saw_error;
	    }

	  c_parser_consume_token (parser);

	  જો (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    જાઓ saw_error;

	  extra_scope = સાચું;
	  v = c_parser_cast_expression (parser, ખાલી).કિંમત;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, ખોટું, ખાલી, સાચું);
	  જો (v == error_mark_ગાંઠ)
	    જાઓ saw_error;
	  જો (non_lvalue_p)
	    v = non_lvalue (v);
	  જો (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    જાઓ saw_error;

	  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);

	  જો (!c_વૃક્ષ_equal (પદાવલિ.કિંમત, unfolded_lhs))
	    જાઓ bad_if;

	  જો (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    જાઓ saw_error;

	  જો (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    જાઓ saw_error;

	  extra_scope = ખોટું;
	  code = OMP_ATOMIC_CAPTURE_OLD;
	  જો (r == NULL_વૃક્ષ)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_ગાંઠ;
	}
      નહીંતર જો (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  જાઓ saw_error;
	}
      નહીંતર જો (code == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_વૃક્ષ
	       && v == NULL_વૃક્ષ)
	code = OMP_ATOMIC;
      જાઓ stmt_done;
    }
  eloc = c_parser_peek_token (parser)->location;
  પદાવલિ = c_parser_cast_expression (parser, ખાલી);
  lhs = પદાવલિ.કિંમત;
  પદાવલિ = default_function_array_conversion (eloc, પદાવલિ);
  unfolded_lhs = પદાવલિ.કિંમત;
  lhs = c_fully_fold (lhs, ખોટું, ખાલી, સાચું);
  orig_lhs = lhs;
  પસંદગી (વૃક્ષ_CODE (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    સ્થિતિ ERROR_MARK:
    saw_error:
      c_parser_skip_to_end_of_block_or_statement (parser);
      જો (extra_scope && c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      જો (structured_block)
	{
	  જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  નહીંતર જો (code == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      પાછા;

    સ્થિતિ POSTINCREMENT_પદાવલિ:
      જો (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    સ્થિતિ PREINCREMENT_પદાવલિ:
      lhs = વૃક્ષ_OPERAND (lhs, 0);
      unfolded_lhs = NULL_વૃક્ષ;
      opcode = PLUS_પદાવલિ;
      rhs = integer_one_ગાંઠ;
      જો (compare)
	જાઓ invalid_compare;
      તોડો;

    સ્થિતિ POSTDECREMENT_પદાવલિ:
      જો (code == OMP_ATOMIC_CAPTURE_NEW && !structured_block)
	code = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    સ્થિતિ PREDECREMENT_પદાવલિ:
      lhs = વૃક્ષ_OPERAND (lhs, 0);
      unfolded_lhs = NULL_વૃક્ષ;
      opcode = MINUS_પદાવલિ;
      rhs = integer_one_ગાંઠ;
      જો (compare)
	જાઓ invalid_compare;
      તોડો;

    સ્થિતિ COMPOUND_પદાવલિ:
      જો (વૃક્ષ_CODE (વૃક્ષ_OPERAND (lhs, 0)) == SAVE_પદાવલિ
	  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (lhs, 1)) == COMPOUND_પદાવલિ
	  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (lhs, 1), 0)) == MODIFY_પદાવલિ
	  && વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (lhs, 1), 1) == વૃક્ષ_OPERAND (lhs, 0)
	  && C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND
					      (વૃક્ષ_OPERAND (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (lhs, 1), 0);
      /* FALLTHRU */
    સ્થિતિ MODIFY_પદાવલિ:
      જો (વૃક્ષ_CODE (lhs) == MODIFY_પદાવલિ
	  && C_BOOLEAN_TYPE_P (વૃક્ષ_TYPE (વૃક્ષ_OPERAND (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  જો (integer_onep (વૃક્ષ_OPERAND (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = વૃક્ષ_OPERAND (lhs, 1);
	      lhs = વૃક્ષ_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_વૃક્ષ;
	      opcode = NOP_પદાવલિ;
	      જો (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && વૃક્ષ_CODE (orig_lhs) == COMPOUND_પદાવલિ)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      જો (compare)
		જાઓ invalid_compare;
	      તોડો;
	    }
	  જો (વૃક્ષ_CODE (વૃક્ષ_OPERAND (lhs, 1)) == TRUTH_NOT_પદાવલિ
	      && વૃક્ષ_OPERAND (lhs, 0)
		 == વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = વૃક્ષ_OPERAND (lhs, 1);
	      lhs = વૃક્ષ_OPERAND (lhs, 0);
	      unfolded_lhs = NULL_વૃક્ષ;
	      opcode = NOP_પદાવલિ;
	      જો (code == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_block
		  && વૃક્ષ_CODE (orig_lhs) == COMPOUND_પદાવલિ)
		code = OMP_ATOMIC_CAPTURE_OLD;
	      જો (compare)
		જાઓ invalid_compare;
	      તોડો;
	    }
	}
      /* FALLTHRU */
    મૂળભૂત:
      જો (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      જો (compare && !c_parser_next_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  જાઓ saw_error;
	}
      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_MULT_EQ:
	  opcode = MULT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_DIV_EQ:
	  opcode = TRUNC_DIV_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_PLUS_EQ:
	  opcode = PLUS_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_MINUS_EQ:
	  opcode = MINUS_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_LSHIFT_EQ:
	  opcode = LSHIFT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_RSHIFT_EQ:
	  opcode = RSHIFT_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_AND_EQ:
	  opcode = BIT_AND_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_OR_EQ:
	  opcode = BIT_IOR_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_XOR_EQ:
	  opcode = BIT_XOR_પદાવલિ;
	  તોડો;
	સ્થિતિ CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી, unfolded_lhs);
	  rhs1 = પદાવલિ.કિંમત;
	  પસંદગી (વૃક્ષ_CODE (rhs1))
	    {
	    સ્થિતિ MULT_પદાવલિ:
	    સ્થિતિ TRUNC_DIV_પદાવલિ:
	    સ્થિતિ RDIV_પદાવલિ:
	    સ્થિતિ PLUS_પદાવલિ:
	    સ્થિતિ MINUS_પદાવલિ:
	    સ્થિતિ LSHIFT_પદાવલિ:
	    સ્થિતિ RSHIFT_પદાવલિ:
	    સ્થિતિ BIT_AND_પદાવલિ:
	    સ્થિતિ BIT_IOR_પદાવલિ:
	    સ્થિતિ BIT_XOR_પદાવલિ:
	      જો (compare)
		તોડો;
	      જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (rhs1, 0), unfolded_lhs))
		{
		  opcode = વૃક્ષ_CODE (rhs1);
		  rhs = c_fully_fold (વૃક્ષ_OPERAND (rhs1, 1), ખોટું, ખાલી,
				      સાચું);
		  rhs1 = c_fully_fold (વૃક્ષ_OPERAND (rhs1, 0), ખોટું, ખાલી,
				       સાચું);
		  જાઓ stmt_done;
		}
	      જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (rhs1, 1), unfolded_lhs))
		{
		  opcode = વૃક્ષ_CODE (rhs1);
		  rhs = c_fully_fold (વૃક્ષ_OPERAND (rhs1, 0), ખોટું, ખાલી,
				      સાચું);
		  rhs1 = c_fully_fold (વૃક્ષ_OPERAND (rhs1, 1), ખોટું, ખાલી,
				       સાચું);
		  swapped = !commutative_વૃક્ષ_code (opcode);
		  જાઓ stmt_done;
		}
	      તોડો;
	    સ્થિતિ COND_પદાવલિ:
	      જો (!compare)
		તોડો;
	      જો (વૃક્ષ_CODE (વૃક્ષ_OPERAND (rhs1, 0)) != GT_પદાવલિ
		  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (rhs1, 0)) != LT_પદાવલિ
		  && વૃક્ષ_CODE (વૃક્ષ_OPERAND (rhs1, 0)) != EQ_પદાવલિ)
		તોડો;
	      જો (!વૃક્ષ_OPERAND (rhs1, 1))
		તોડો;
	      જો (!c_વૃક્ષ_equal (વૃક્ષ_OPERAND (rhs1, 2), unfolded_lhs))
		તોડો;
	      જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (rhs1, 0), 0),
				unfolded_lhs))
		{
		  જો (વૃક્ષ_CODE (વૃક્ષ_OPERAND (rhs1, 0)) == EQ_પદાવલિ)
		    {
		      opcode = COND_પદાવલિ;
		      rhs = c_fully_fold (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (rhs1,
								      0), 1),
					  ખોટું, ખાલી, સાચું);
		      rhs1 = c_fully_fold (વૃક્ષ_OPERAND (rhs1, 1), ખોટું,
					   ખાલી, સાચું);
		      જાઓ stmt_done;
		    }
		  જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (rhs1, 0), 1),
				    વૃક્ષ_OPERAND (rhs1, 1)))
		    {
		      opcode = (વૃક્ષ_CODE (વૃક્ષ_OPERAND (rhs1, 0)) == GT_પદાવલિ
				? MIN_પદાવલિ : MAX_પદાવલિ);
		      rhs = c_fully_fold (વૃક્ષ_OPERAND (rhs1, 1), ખોટું, ખાલી,
					  સાચું);
		      rhs1 = c_fully_fold (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (rhs1,
								       0), 0),
					   ખોટું, ખાલી, સાચું);
		      જાઓ stmt_done;
		    }
		}
	      નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_OPERAND (rhs1, 0)) == EQ_પદાવલિ)
		તોડો;
	      નહીંતર જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  જો (c_વૃક્ષ_equal (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (rhs1, 0), 0),
				    વૃક્ષ_OPERAND (rhs1, 1)))
		    {
		      opcode = (વૃક્ષ_CODE (વૃક્ષ_OPERAND (rhs1, 0)) == GT_પદાવલિ
				? MAX_પદાવલિ : MIN_પદાવલિ);
		      rhs = c_fully_fold (વૃક્ષ_OPERAND (rhs1, 1), ખોટું, ખાલી,
					  સાચું);
		      rhs1 = c_fully_fold (વૃક્ષ_OPERAND (વૃક્ષ_OPERAND (rhs1,
								       0), 1),
					   ખોટું, ખાલી, સાચું);
		      જાઓ stmt_done;
		    }
		}
	      તોડો;
	    સ્થિતિ EQ_પદાવલિ:
	      જો (!compare
		  || code != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_block
		  || v
		  || r)
		તોડો;
	      જો (c_parser_next_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_વૃક્ષ;
		  c_parser_consume_token (parser);
		  જાઓ restart;
		}
	      તોડો;
	    સ્થિતિ ERROR_MARK:
	      જાઓ saw_error;
	    મૂળભૂત:
	      તોડો;
	    }
	  જો (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      જો (structured_block && code == OMP_ATOMIC_CAPTURE_NEW)
		{
		  code = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_વૃક્ષ;
		  પદાવલિ = default_function_array_read_conversion (eloc, પદાવલિ);
		  unfolded_lhs1 = પદાવલિ.કિંમત;
		  lhs1 = c_fully_fold (unfolded_lhs1, ખોટું, ખાલી, સાચું);
		  rhs1 = NULL_વૃક્ષ;
		  c_parser_consume_token (parser);
		  જાઓ restart;
		}
	      જો (structured_block && !compare)
		{
		  opcode = NOP_પદાવલિ;
		  પદાવલિ = default_function_array_read_conversion (eloc, પદાવલિ);
		  rhs = c_fully_fold (પદાવલિ.કિંમત, ખોટું, ખાલી, સાચું);
		  rhs1 = NULL_વૃક્ષ;
		  જાઓ stmt_done;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  જાઓ saw_error;
	મૂળભૂત:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  જાઓ saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      પદાવલિ = c_parser_expression (parser);
      પદાવલિ = default_function_array_read_conversion (eloc, પદાવલિ);
      rhs = પદાવલિ.કિંમત;
      rhs = c_fully_fold (rhs, ખોટું, ખાલી, સાચું);
      તોડો;
    }
stmt_done:
  જો (structured_block && code == OMP_ATOMIC_CAPTURE_NEW && r == NULL_વૃક્ષ)
    {
      જો (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	જાઓ saw_error;
      no_semicolon = ખોટું;
      v = c_parser_cast_expression (parser, ખાલી).કિંમત;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, ખોટું, ખાલી, સાચું);
      જો (v == error_mark_ગાંઠ)
	જાઓ saw_error;
      જો (non_lvalue_p)
	v = non_lvalue (v);
      જો (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	જાઓ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      પદાવલિ = c_parser_cast_expression (parser, ખાલી);
      lhs1 = પદાવલિ.કિંમત;
      પદાવલિ = default_function_array_read_conversion (eloc, પદાવલિ);
      unfolded_lhs1 = પદાવલિ.કિંમત;
      lhs1 = c_fully_fold (lhs1, ખોટું, ખાલી, સાચું);
      જો (lhs1 == error_mark_ગાંઠ)
	જાઓ saw_error;
      જો (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  જો (structured_block)
    {
      જો (!no_semicolon)
	c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
done:
  જો (weak && opcode != COND_પદાવલિ)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = ખોટું;
    }
  જો (unfolded_lhs && unfolded_lhs1
      && !c_વૃક્ષ_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_ગાંઠ;
    }
  નહીંતર
    stmt = c_finish_omp_atomic (loc, code, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, memory_order, weak);
  જો (stmt != error_mark_ગાંઠ)
    add_stmt (stmt);

  જો (!structured_block && !no_semicolon)
    c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

સ્થિર શૂન્ય
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

સ્થિર વૃક્ષ
c_parser_omp_critical (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ stmt, name = NULL_વૃક્ષ, clauses = NULL_વૃક્ષ;

  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      જો (c_parser_next_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->કિંમત;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      નહીંતર
	c_parser_error (parser, "expected identifier");

      જો (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_MASK,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_block (parser, if_p);
  પાછા c_finish_omp_critical (loc, stmt, name, clauses);
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

સ્થિર શૂન્ય
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  જો (!parens.require_open (parser))
    {
      c_parser_skip_to_pragma_eol (parser);
      પાછા;
    }

  વૃક્ષ depobj = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
  જો (depobj != error_mark_ગાંઠ)
    {
      જો (!lvalue_p (depobj))
	{
	  error_at (પદાવલિ_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_ગાંઠ;
	}
      નહીંતર
	{
	  વૃક્ષ addr = build_unary_op (પદાવલિ_LOC_OR_LOC (depobj, loc), ADDR_પદાવલિ,
				      depobj, ખોટું);
	  જો (addr == error_mark_ગાંઠ)
	    depobj = error_mark_ગાંઠ;
	  નહીંતર
	    depobj = build_indirect_ref (પદાવલિ_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_STAR);
	}
    }

  parens.skip_until_found_close (parser);
  વૃક્ષ clause = NULL_વૃક્ષ;
  ગણના omp_clause_depend_kind kind = OMP_CLAUSE_DEPEND_INVALID;
  જો (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      c_parser_consume_token (parser);
      જો (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_વૃક્ષ, c_loc);
	  clause = c_finish_omp_clauses (clause, C_ORT_OMP);
	  જો (!clause)
	    clause = error_mark_ગાંઠ;
	}
      નહીંતર જો (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  kind = OMP_CLAUSE_DEPEND_LAST;
	  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      વૃક્ષ destobj = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
	      જો (!lvalue_p (destobj))
		error_at (પદાવલિ_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      નહીંતર જો (depobj != error_mark_ગાંઠ
		       && !operand_equal_p (destobj, depobj,
					    OEP_MATCH_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (પદાવલિ_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_found_close (parser);
	    }
	}
      નહીંતર જો (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  જો (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      જો (c_parser_next_token_is (parser, CPP_NAME))
		{
		  અચલ અક્ષર *p2
		    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

		  c_parser_consume_token (parser);
		  જો (!strcmp ("in", p2))
		    kind = OMP_CLAUSE_DEPEND_IN;
		  નહીંતર જો (!strcmp ("out", p2))
		    kind = OMP_CLAUSE_DEPEND_OUT;
		  નહીંતર જો (!strcmp ("inout", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUT;
		  નહીંતર જો (!strcmp ("mutexinoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  નહીંતર જો (!strcmp ("inoutset", p2))
		    kind = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      જો (kind == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_ગાંઠ;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_found_close (parser);
	    }
	  નહીંતર
	    clause = error_mark_ગાંઠ;
	}
    }
  જો (!clause && kind == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_ગાંઠ;
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

સ્થિર શૂન્ય
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ગણના memmodel mo = MEMMODEL_LAST;
  જો (c_parser_next_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      જો (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      નહીંતર જો (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      નહીંતર જો (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      નહીંતર જો (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      નહીંતર
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      જો (mo != MEMMODEL_LAST)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ખાલી);
    }
  નહીંતર જો (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_to_pragma_eol (parser);

  c_finish_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

સ્થિર તાર્કિક
c_parser_omp_section_scan (c_parser *parser, અચલ અક્ષર *directive,
			   તાર્કિક tentative)
{
  જો (!c_parser_nth_token_starts_std_attributes (parser, 1))
    પાછા ખોટું;
  unsigned પૂર્ણાંક n = 3;
  જો (!c_parser_check_balanced_raw_token_sequence (parser, &n))
    પાછા ખોટું;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  જો (token->type != CPP_CLOSE_SQUARE)
    પાછા ખોટું;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  જો (token->type != CPP_CLOSE_SQUARE)
    પાછા ખોટું;
  જો (n < 9)
    પાછા ખોટું;
  જો (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      વૃક્ષ first = c_parser_peek_nth_token_raw (parser, 3)->કિંમત;
      વૃક્ષ second = c_parser_peek_nth_token_raw (parser, 5)->કિંમત;
      જો (strcmp (IDENTIFIER_POINTER (first), "directive")
	  && strcmp (IDENTIFIER_POINTER (first), "__directive__"))
	પાછા ખોટું;
      જો (strcmp (IDENTIFIER_POINTER (second), directive))
	પાછા ખોટું;
    }
  જો (tentative)
    પાછા સાચું;
  location_t first_loc = c_parser_peek_token (parser)->location;
  location_t last_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t મધ્ય_loc = UNKNOWN_LOCATION;
  વૃક્ષ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  તાર્કિક seen = ખોટું;
  પૂર્ણાંક cnt = 0;
  માટે (વૃક્ષ attr = std_attrs; attr; attr = વૃક્ષ_CHAIN (attr))
    જો (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	માટે (વૃક્ષ a = વૃક્ષ_કિંમત (attr); a; a = વૃક્ષ_CHAIN (a))
	  {
	    વૃક્ષ d = વૃક્ષ_કિંમત (a);
	    gcc_assert (વૃક્ષ_CODE (d) == C_TOKEN_VEC);
	    c_token *first = C_TOKEN_VEC_TOKENS (d)->address ();
	    cnt++;
	    જો (first->type == CPP_NAME
		&& strcmp (IDENTIFIER_POINTER (first->કિંમત),
			   directive) == 0)
	      {
		seen = સાચું;
		જો (મધ્ય_loc == UNKNOWN_LOCATION)
		  મધ્ય_loc = first->location;
	      }
	  }
      }
  જો (!seen)
    પાછા ખોટું;
  જો (cnt != 1 || વૃક્ષ_CHAIN (std_attrs))
    {
      error_at (make_location (first_loc, last_loc, મધ્ય_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      પાછા ખોટું;
    }
  c_parser_handle_statement_omp_attributes (parser, std_attrs, ખાલી);
  પાછા સાચું;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

સ્થિર વૃક્ષ
c_parser_omp_structured_block_sequence (c_parser *parser,
					ગણના pragma_kind kind)
{
  વૃક્ષ stmt = ધકેલો_stmt_list ();
  c_parser_statement (parser, ખાલી);
  કરો
    {
      જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	તોડો;
      જો (c_parser_next_token_is (parser, CPP_EOF))
	તોડો;

      જો (kind != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_kind == kind)
	તોડો;

      જો (kind != PRAGMA_NONE
	  && c_parser_omp_section_scan (parser,
					kind == PRAGMA_OMP_SCAN
					? "scan" : "section", ખોટું))
	તોડો;

      c_parser_statement (parser, ખાલી);
    }
  જ્યારે (1);
  પાછા કાઢો_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

સ્થિર શૂન્ય
c_parser_omp_scan_loop_body (c_parser *parser, તાર્કિક open_brace_parsed)
{
  વૃક્ષ substmt;
  location_t loc;
  વૃક્ષ clauses = NULL_વૃક્ષ;
  તાર્કિક found_scan = ખોટું;

  loc = c_parser_peek_token (parser)->location;
  જો (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = ખોટું;
      પાછા;
    }

  જો (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SCAN)
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_OMP_SCAN);
  નહીંતર
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_ગાંઠ, substmt, NULL_વૃક્ષ);
  SET_પદાવલિ_LOCATION (substmt, loc);
  add_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  જો (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SCAN)
    {
      ગણના omp_clause_code clause = OMP_CLAUSE_ERROR;
      found_scan = સાચું;

      c_parser_consume_pragma (parser);

      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      જો (c_parser_next_token_is (parser, CPP_NAME))
	{
	  અચલ અક્ષર *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	  જો (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  નહીંતર જો (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      જો (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_વૃક્ષ);
	}
      નહીંતર
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_to_pragma_eol (parser);
    }
  નહીંતર
    error ("expected %<#pragma omp scan%>");

  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  જો (!c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_block_sequence (parser, PRAGMA_NONE);
  નહીંતર
    {
      જો (found_scan)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_empty_stmt (loc);
    }
  substmt = build2 (OMP_SCAN, void_type_ગાંઠ, substmt, clauses);
  SET_પદાવલિ_LOCATION (substmt, loc);
  add_stmt (substmt);

  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
સ્થિર તાર્કિક
c_parser_omp_next_tokens_can_be_canon_loop (c_parser *parser,
					    ગણના વૃક્ષ_code code,
					    તાર્કિક error_p)
{
  જો (code == OACC_LOOP)
    {
      જો (c_parser_next_token_is_keyword (parser, RID_FOR))
	પાછા સાચું;
      જો (error_p)
	c_parser_error (parser, "for statement expected");
    }
  નહીંતર
    {
      જો (c_parser_next_token_is_keyword (parser, RID_FOR))
	પાછા સાચું;

      જો (c_parser_next_token_is (parser, CPP_PRAGMA))
	પસંદગી (c_parser_peek_token (parser)->pragma_kind)
	  {
	  સ્થિતિ PRAGMA_OMP_UNROLL:
	  સ્થિતિ PRAGMA_OMP_TILE:
	    પાછા સાચું;
	  મૂળભૂત:
	    તોડો;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      size_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      જો (token->type == CPP_NAME
	  && C_IS_RESERVED_WORD (token->કિંમત)
	  && C_RID_CODE (token->કિંમત) == RID_FOR)
	પાછા સાચું;
      જો (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  પાછા ખોટું;
}

સ્થિર વૃક્ષ c_parser_omp_tile (location_t, c_parser *, તાર્કિક *);
સ્થિર વૃક્ષ c_parser_omp_unroll (location_t, c_parser *, તાર્કિક *);

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

સ્થિર વૃક્ષ
c_parser_omp_loop_nest (c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ decl = NULL_વૃક્ષ, cond = NULL_વૃક્ષ, incr = NULL_વૃક્ષ, init = NULL_વૃક્ષ;
  વૃક્ષ body = NULL_વૃક્ષ;
  matching_parens parens;
  તાર્કિક moreloops;
  unsigned અક્ષર save_in_statement;
  વૃક્ષ loop_scope;
  location_t loc;
  સંરચના omp_for_parse_data *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  પૂર્ણાંક depth = omp_for_parse_state->depth;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  જો (c_parser_nth_token_starts_std_attributes (parser, 1))
    {
      વૃક્ષ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_attributes (parser, std_attrs, ખાલી);
      જો (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  જો (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      વૃક્ષ transform = NULL_વૃક્ષ, sizes, body = NULL_વૃક્ષ;
      પૂર્ણાંક ગણતરી = 0;
      પસંદગી (c_parser_peek_token (parser)->pragma_kind)
	{
	સ્થિતિ PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = ધકેલો_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = કાઢો_stmt_list (body);
	  જો (transform == NULL_વૃક્ષ || transform == error_mark_ગાંઠ)
	    {
	      transform = error_mark_ગાંઠ;
	      તોડો;
	    }
	  gcc_assert (વૃક્ષ_CODE (transform) == OMP_UNROLL);
	  જો (omp_find_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      જો (omp_for_parse_state->ગણતરી - depth > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->ગણતરી - depth);
		  transform = error_mark_ગાંઠ;
		}
	      નહીંતર
		ગણતરી = 1;
	    }
	  નહીંતર
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_ગાંઠ;
	    }
	  તોડો;
	સ્થિતિ PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = ધકેલો_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = કાઢો_stmt_list (body);
	  જો (transform == NULL_વૃક્ષ || transform == error_mark_ગાંઠ)
	    {
	      transform = error_mark_ગાંઠ;
	      તોડો;
	    }
	  gcc_assert (વૃક્ષ_CODE (transform) == OMP_TILE);
	  sizes = omp_find_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  ગણતરી = list_length (OMP_CLAUSE_SIZES_LIST (sizes));
	  જો (depth + ગણતરી < omp_for_parse_state->ગણતરી)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			ગણતરી, omp_for_parse_state->ગણતરી - depth);
	      transform = error_mark_ગાંઠ;
	    }
	  તોડો;
	મૂળભૂત:
	  c_parser_pragma (parser, pragma_stmt, ખાલી, void_list_ગાંઠ);
	  તોડો;
	}
      જો (transform == NULL_વૃક્ષ)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      જો (transform == NULL_વૃક્ષ || transform == error_mark_ગાંઠ)
	{
	  omp_for_parse_state->fail = સાચું;
	  પાછા NULL_વૃક્ષ;
	}
      માટે (ગણતરી = omp_for_parse_state->ગણતરી; depth < ગણતરી; ++depth)
	{
	  વૃક્ષ_VEC_ELT (omp_for_parse_state->declv, depth) = NULL_વૃક્ષ;
	  વૃક્ષ_VEC_ELT (omp_for_parse_state->initv, depth) = NULL_વૃક્ષ;
	  વૃક્ષ_VEC_ELT (omp_for_parse_state->condv, depth) = NULL_વૃક્ષ;
	  વૃક્ષ_VEC_ELT (omp_for_parse_state->incrv, depth) = NULL_વૃક્ષ;
	}
      omp_for_parse_state->want_nested_loop = ખોટું;
      પાછા body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_in_statement = in_statement;
  in_statement = IN_OMP_BLOCK;

  /* We are not in intervening code now.  */
  omp_for_parse_state->in_intervening_code = ખોટું;

  જો (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = સાચું;
      પાછા NULL_વૃક્ષ;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (સાચું);

  /* Parse the initialization declaration or expression.  */
  જો (c_parser_next_tokens_start_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      વૃક્ષ this_pre_body = ધકેલો_stmt_list ();
      c_in_omp_for = સાચું;
      c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, સાચું, સાચું,
				     ખોટું);
      c_in_omp_for = ખોટું;
      this_pre_body = કાઢો_stmt_list (this_pre_body);
      append_to_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      જો (decl == ખાલી)
	જાઓ error_init;
      જો (DECL_INITIAL (decl) == error_mark_ગાંઠ)
	decl = error_mark_ગાંઠ;
      init = decl;
    }
  નહીંતર જો (c_parser_next_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      સંરચના c_પદાવલિ decl_exp;
      સંરચના c_પદાવલિ init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_expression (parser);
      decl = decl_exp.કિંમત;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_પદાવલિ_no_commas (parser, ખાલી);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_in_omp_for = સાચું;
      init = build_modify_પદાવલિ (init_loc, decl, decl_exp.original_type,
				NOP_પદાવલિ, init_loc, init_exp.કિંમત,
				init_exp.original_type);
      c_in_omp_for = ખોટું;
      init = c_process_પદાવલિ_stmt (init_loc, init);

      c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  નહીંતર
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = સાચું;
      જાઓ parse_next;
    }

  /* Parse the loop condition.  */
  જો (c_parser_next_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_in_omp_for = સાચું;
      સંરચના c_પદાવલિ cond_પદાવલિ
	= c_parser_દ્વિઅંકી_expression (parser, ખાલી, NULL_વૃક્ષ);
      c_in_omp_for = ખોટું;

      cond = cond_પદાવલિ.કિંમત;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      પસંદગી (cond_પદાવલિ.original_code)
	{
	સ્થિતિ GT_પદાવલિ:
	સ્થિતિ GE_પદાવલિ:
	સ્થિતિ LT_પદાવલિ:
	સ્થિતિ LE_પદાવલિ:
	  તોડો;
	સ્થિતિ NE_પદાવલિ:
	  જો (omp_for_parse_state->code != OACC_LOOP)
	    તોડો;
	  /* FALLTHRU.  */
	મૂળભૂત:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_પદાવલિ, boolean_type_ગાંઠ, error_mark_ગાંઠ);
	  તોડો;
	}
      protected_set_પદાવલિ_location (cond, cond_loc);
    }
  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  જો (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_પદાવલિ_stmt (incr_loc,
				  c_parser_expression (parser).કિંમત);
    }
  parens.skip_until_found_close (parser);

  જો (decl == ખાલી || decl == error_mark_ગાંઠ || init == error_mark_ગાંઠ)
    omp_for_parse_state->fail = સાચું;
  નહીંતર
    {
      વૃક્ષ_VEC_ELT (omp_for_parse_state->declv, depth) = decl;
      વૃક્ષ_VEC_ELT (omp_for_parse_state->initv, depth) = init;
      વૃક્ષ_VEC_ELT (omp_for_parse_state->condv, depth) = cond;
      વૃક્ષ_VEC_ELT (omp_for_parse_state->incrv, depth) = incr;
    }

parse_next:
  moreloops = depth < omp_for_parse_state->ગણતરી - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  જો (moreloops
      && c_parser_omp_next_tokens_can_be_canon_loop (parser,
						     omp_for_parse_state->code,
						     ખોટું))
    {
      omp_for_parse_state->depth++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->depth--;
    }
  નહીંતર જો (moreloops && c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->in_intervening_code = સાચું;
      body = c_parser_compound_statement (parser, ખાલી);
      omp_for_parse_state->in_intervening_code = ખોટું;
      જો (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = સાચું;
	}
      if_p = ખાલી;
    }
  નહીંતર
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      જો (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = સાચું;
	}
      in_statement = IN_OMP_FOR;
      parser->omp_for_parse_state = ખાલી;
      body = ધકેલો_stmt_list ();
      જો (omp_for_parse_state->inscan)
	c_parser_omp_scan_loop_body (parser, ખોટું);
      નહીંતર
	add_stmt (c_parser_c99_block_statement (parser, if_p));
      body = કાઢો_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  in_statement = save_in_statement;
  omp_for_parse_state->want_nested_loop = ખોટું;
  omp_for_parse_state->in_intervening_code = સાચું;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  જો (body)
    add_stmt (body);
  body = c_end_compound_stmt (loc, loop_scope, સાચું);
  જો (decl && વૃક્ષ_CODE (body) == BIND_પદાવલિ)
    {
      વૃક્ષ t = BIND_પદાવલિ_VARS (body);
      વૃક્ષ prev = NULL_વૃક્ષ, next = NULL_વૃક્ષ;
      જ્યારે (t)
	{
	  next = DECL_CHAIN (t);
	  જો (t == decl)
	    {
	      જો (prev)
		DECL_CHAIN (prev) = next;
	      નહીંતર
		{
		  BIND_પદાવલિ_VARS (body) = next;
		  BLOCK_VARS (BIND_પદાવલિ_BLOCK (body)) = next;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      તોડો;
	    }
	  નહીંતર
	    {
	      prev = t;
	      t = next;
	    }
	}
      જો (BIND_પદાવલિ_VARS (body) == NULL_વૃક્ષ)
	body = BIND_પદાવલિ_BODY (body);
    }

  પાછા body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

સ્થિર વૃક્ષ
c_parser_omp_for_loop (location_t loc, c_parser *parser, ગણના વૃક્ષ_code code,
		       વૃક્ષ clauses, વૃક્ષ *cclauses, તાર્કિક *if_p)
{
  વૃક્ષ body, stmt, cl;
  વૃક્ષ ret = NULL_વૃક્ષ;
  વૃક્ષ ordered_cl = NULL_વૃક્ષ;
  પૂર્ણાંક i, collapse = 1, ordered = 0, ગણતરી;
  તાર્કિક oacc_tiling = ખોટું;
  તાર્કિક inscan = ખોટું;
  સંરચના omp_for_parse_data data;
  સંરચના omp_for_parse_data *save_data = parser->omp_for_parse_state;

  માટે (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    જો (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = વૃક્ષ_to_shwi (OMP_CLAUSE_COLLAPSE_પદાવલિ (cl));
    નહીંતર જો (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = સાચું;
	collapse = list_length (OMP_CLAUSE_TILE_LIST (cl));
      }
    નહીંતર જો (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_SIZES)
      collapse = list_length (OMP_CLAUSE_SIZES_LIST (cl));
    નહીંતર જો (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_પદાવલિ (cl))
      {
	ordered_cl = cl;
	ordered = વૃક્ષ_to_shwi (OMP_CLAUSE_ORDERED_પદાવલિ (cl));
      }
    નહીંતર જો (OMP_CLAUSE_CODE (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (code == OMP_SIMD || code == OMP_FOR))
      inscan = સાચું;

  જો (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_પદાવલિ (ordered_cl)
	= build_int_cst (integer_type_ગાંઠ, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  ગણતરી = ordered ? ordered : collapse;

  જો (!c_parser_omp_next_tokens_can_be_canon_loop (parser, code, સાચું))
    પાછા ખાલી;

  /* Initialize parse state for recursive descent.  */
  data.declv = make_વૃક્ષ_vec (ગણતરી);
  data.initv = make_વૃક્ષ_vec (ગણતરી);
  data.condv = make_વૃક્ષ_vec (ગણતરી);
  data.incrv = make_વૃક્ષ_vec (ગણતરી);
  data.pre_body = NULL_વૃક્ષ;
  data.bindings = NULL_વૃક્ષ;
  data.for_loc = c_parser_peek_token (parser)->location;
  data.ગણતરી = ગણતરી;
  data.depth = 0;
  data.want_nested_loop = સાચું;
  data.ordered = ordered > 0;
  data.in_intervening_code = ખોટું;
  data.perfect_nesting_fail = ખોટું;
  data.fail = ખોટું;
  data.inscan = inscan;
  data.saw_intervening_code = ખોટું;
  data.code = code;
  parser->omp_for_parse_state = &data;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  માટે (વૃક્ષ t = data.bindings; t; )
    {
      વૃક્ષ n = વૃક્ષ_CHAIN (t);
      વૃક્ષ_CHAIN (t) = NULL_વૃક્ષ;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  જો (!data.fail)
    {
      c_in_omp_for = સાચું;
      stmt = c_finish_omp_for (loc, code, data.declv, ખાલી, data.initv,
			       data.condv, data.incrv,
			       body, data.pre_body, સાચું);
      c_in_omp_for = ખોટું;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      જો (stmt && !c_omp_check_loop_iv (stmt, data.declv, ખાલી))
	stmt = NULL_વૃક્ષ;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      જો (data.saw_intervening_code
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, ખાલી))
	stmt = NULL_વૃક્ષ;

      જો (stmt)
	{
	  add_stmt (stmt);

	  માટે (i = 0; i < વૃક્ષ_VEC_LENGTH (OMP_FOR_INIT (stmt)); i++)
	    {
	      વૃક્ષ init = વૃક્ષ_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      જો (init == NULL_વૃક્ષ)
		તોડો;
	      gcc_assert (વૃક્ષ_CODE (init) == MODIFY_પદાવલિ);
	      વૃક્ષ decl = વૃક્ષ_OPERAND (init, 0);
	      વૃક્ષ cond = વૃક્ષ_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (વૃક્ષ_OPERAND (cond, 0) == decl);

	      વૃક્ષ op0 = વૃક્ષ_OPERAND (init, 1);
	      જો (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || વૃક્ષ_CODE (op0) != વૃક્ષ_VEC)
		વૃક્ષ_OPERAND (init, 1) = c_fully_fold (op0, ખોટું, ખાલી);
	      નહીંતર
		{
		  વૃક્ષ_VEC_ELT (op0, 1)
		    = c_fully_fold (વૃક્ષ_VEC_ELT (op0, 1), ખોટું, ખાલી);
		  વૃક્ષ_VEC_ELT (op0, 2)
		    = c_fully_fold (વૃક્ષ_VEC_ELT (op0, 2), ખોટું, ખાલી);
		}

	      વૃક્ષ op1 = વૃક્ષ_OPERAND (cond, 1);
	      જો (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || વૃક્ષ_CODE (op1) != વૃક્ષ_VEC)
		વૃક્ષ_OPERAND (cond, 1) = c_fully_fold (op1, ખોટું, ખાલી);
	      નહીંતર
		{
		  વૃક્ષ_VEC_ELT (op1, 1)
		    = c_fully_fold (વૃક્ષ_VEC_ELT (op1, 1), ખોટું, ખાલી);
		  વૃક્ષ_VEC_ELT (op1, 2)
		    = c_fully_fold (વૃક્ષ_VEC_ELT (op1, 2), ખોટું, ખાલી);
		}
	    }

	  જો (cclauses != ખાલી
	      && cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL] != ખાલી)
	    {
	      વૃક્ષ *c;
	      માટે (c = &cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL]; *c ; )
		જો (OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_CODE (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		નહીંતર
		  {
		    માટે (i = 0; i < ગણતરી; i++)
		      જો (વૃક્ષ_VEC_ELT (data.declv, i) == OMP_CLAUSE_DECL (*c))
			તોડો;
		    જો (i == ગણતરી)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    નહીંતર જો (OMP_CLAUSE_CODE (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    નહીંતર
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			વૃક્ષ l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			જો (code == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
			    cclauses[C_OMP_CLAUSE_SPLIT_FOR] = l;
			  }
			નહીંતર
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
  પાછા ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

સ્થિર શૂન્ય
omp_split_clauses (location_t loc, ગણના વૃક્ષ_code code,
		   omp_clause_mask mask, વૃક્ષ clauses, વૃક્ષ *cclauses)
{
  પૂર્ણાંક i;
  c_omp_split_clauses (loc, code, mask, clauses, cclauses);
  માટે (i = 0; i < C_OMP_CLAUSE_SPLIT_ગણતરી; i++)
    જો (cclauses[i])
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

સ્થિર વૃક્ષ
c_parser_omp_loop (location_t loc, c_parser *parser,
		   અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
		   તાર્કિક *if_p)
{
  વૃક્ષ block, clauses, ret;

  strcat (p_name, " loop");
  mask |= OMP_LOOP_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_LOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_LOOP];
    }

  block = c_begin_compound_stmt (સાચું);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા ret;
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

સ્થિર વૃક્ષ
c_parser_omp_simd (location_t loc, c_parser *parser,
		   અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
		   તાર્કિક *if_p)
{
  વૃક્ષ block, clauses, ret;

  strcat (p_name, " simd");
  mask |= OMP_SIMD_CLAUSE_MASK;

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_SIMD, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SIMD];
    }

  block = c_begin_compound_stmt (સાચું);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા ret;
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

સ્થિર વૃક્ષ
c_parser_omp_for (location_t loc, c_parser *parser,
		  અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
		  તાર્કિક *if_p)
{
  વૃક્ષ block, clauses, ret;

  strcat (p_name, " for");
  mask |= OMP_FOR_CLAUSE_MASK;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  જો (cclauses && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  જો ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      જો (strcmp (p, "simd") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  જો (cclauses == ખાલી)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (સાચું);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, સાચું);
	  જો (ret == NULL_વૃક્ષ)
	    પાછા ret;
	  ret = make_ગાંઠ (OMP_FOR);
	  વૃક્ષ_TYPE (ret) = void_type_ગાંઠ;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
	  SET_પદાવલિ_LOCATION (ret, loc);
	  add_stmt (ret);
	  પાછા ret;
	}
    }
  જો (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા NULL_વૃક્ષ;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  જો ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_LINEAR);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_FOR, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_FOR];
    }

  block = c_begin_compound_stmt (સાચું);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા ret;
}

સ્થિર વૃક્ષ c_parser_omp_taskloop (location_t, c_parser *, અક્ષર *,
				   omp_clause_mask, વૃક્ષ *, તાર્કિક *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

સ્થિર વૃક્ષ
c_parser_omp_master (location_t loc, c_parser *parser,
		     અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
		     તાર્કિક *if_p, location_t master_loc)
{
  વૃક્ષ block, clauses, ret;
  gcc_rich_location richloc (loc);
  જો (master_loc != UNKNOWN_LOCATION)
    richloc.add_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      જો (strcmp (p, "taskloop") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  જો (cclauses == ખાલી)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (સાચું);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, સાચું);
	  જો (ret == NULL_વૃક્ષ)
	    પાછા ret;
	  ret = c_finish_omp_master (loc, block);
	  OMP_MASTER_COMBINED (ret) = 1;
	  પાછા ret;
	}
    }
  જો (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા NULL_વૃક્ષ;
    }

  જો (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, mask, p_name, ખોટું);
      omp_split_clauses (loc, OMP_MASTER, mask, clauses, cclauses);
    }
  નહીંતર
    c_parser_skip_to_pragma_eol (parser);

  પાછા c_finish_omp_master (loc, c_parser_omp_structured_block (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#define OMP_MASKED_CLAUSE_MASK					\
	(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FILTER)

સ્થિર વૃક્ષ
c_parser_omp_masked (location_t loc, c_parser *parser,
		     અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
		     તાર્કિક *if_p)
{
  વૃક્ષ block, clauses, ret;

  strcat (p_name, " masked");
  mask |= OMP_MASKED_CLAUSE_MASK;

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      જો (strcmp (p, "taskloop") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  જો (cclauses == ખાલી)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
					  if_p);
	  block = c_begin_compound_stmt (સાચું);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, mask, cclauses,
				       if_p);
	  block = c_end_compound_stmt (loc, block, સાચું);
	  જો (ret == NULL_વૃક્ષ)
	    પાછા ret;
	  ret = c_finish_omp_masked (loc, block,
				     cclauses[C_OMP_CLAUSE_SPLIT_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  પાછા ret;
	}
    }
  જો (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા NULL_વૃક્ષ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_MASKED, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_MASKED];
    }

  પાછા c_finish_omp_masked (loc, c_parser_omp_structured_block (parser,
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

સ્થિર શૂન્ય
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  વૃક્ષ clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_MASK,
					   "#pragma omp interop");
  વૃક્ષ stmt = make_ગાંઠ (OMP_INTEROP);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, loc);
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

સ્થિર તાર્કિક
c_parser_omp_ordered (c_parser *parser, ગણના pragma_context context,
		      તાર્કિક *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  જો (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા ખોટું;
    }

  પૂર્ણાંક n = 1;
  જો (c_parser_next_token_is (parser, CPP_COMMA))
    n = 2;

  જો (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      અચલ અક્ષર *p
	= IDENTIFIER_POINTER (c_parser_peek_nth_token (parser, n)->કિંમત);

      જો (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  જો (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_to_pragma_eol (parser, ખોટું);
	      પાછા ખોટું;
	    }
	  જો (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_to_pragma_eol (parser, ખોટું);
	      પાછા સાચું;
	    }

	  વૃક્ષ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_MASK,
					"#pragma omp ordered");
	  c_finish_omp_ordered (loc, clauses, NULL_વૃક્ષ);
	  પાછા ખોટું;
	}
    }

  વૃક્ષ clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_MASK,
					   "#pragma omp ordered");

  જો (!flag_openmp	/* flag_openmp_simd  */
      && omp_find_clause (clauses, OMP_CLAUSE_SIMD) == NULL_વૃક્ષ)
    પાછા ખોટું;

  c_finish_omp_ordered (loc, clauses,
			c_parser_omp_structured_block (parser, if_p));
  પાછા સાચું;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

સ્થિર વૃક્ષ
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  વૃક્ષ stmt, substmt;
  તાર્કિક error_suppress = ખોટું;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  જો (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = ખોટું;
      પાછા NULL_વૃક્ષ;
    }

  stmt = ધકેલો_stmt_list ();

  જો (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_scan (parser, "section", સાચું))
    {
      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ગાંઠ, substmt);
      SET_પદાવલિ_LOCATION (substmt, loc);
      add_stmt (substmt);
    }

  જ્યારે (1)
    {
      જો (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	તોડો;
      જો (c_parser_next_token_is (parser, CPP_EOF))
	તોડો;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_scan (parser, "section", ખોટું);
      જો (c_parser_peek_token (parser)->pragma_kind == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_to_pragma_eol (parser);
	  error_suppress = ખોટું;
	}
      નહીંતર જો (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = સાચું;
	}

      substmt = c_parser_omp_structured_block_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ગાંઠ, substmt);
      SET_પદાવલિ_LOCATION (substmt, loc);
      add_stmt (substmt);
    }
  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = કાઢો_stmt_list (stmt);

  stmt = make_ગાંઠ (OMP_SECTIONS);
  SET_પદાવલિ_LOCATION (stmt, sections_loc);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_SECTIONS_BODY (stmt) = substmt;

  પાછા add_stmt (stmt);
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

સ્થિર વૃક્ષ
c_parser_omp_sections (location_t loc, c_parser *parser,
		       અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses)
{
  વૃક્ષ block, clauses, ret;

  strcat (p_name, " sections");
  mask |= OMP_SECTIONS_CLAUSE_MASK;
  જો (cclauses)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_SECTIONS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_SECTIONS];
    }

  block = c_begin_compound_stmt (સાચું);
  ret = c_parser_omp_sections_scope (loc, parser);
  જો (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા ret;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_અંક_THREADS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

સ્થિર વૃક્ષ
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
		       તાર્કિક *if_p)
{
  વૃક્ષ stmt, clauses, block;

  strcat (p_name, " parallel");
  mask |= OMP_PARALLEL_CLAUSE_MASK;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  જો ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) == 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  જો (c_parser_next_token_is_keyword (parser, RID_FOR))
    {
      વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
      જો (cclauses == ખાલી)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      જો (!flag_openmp)  /* flag_openmp_simd  */
	પાછા c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      block = c_begin_omp_parallel ();
      વૃક્ષ ret = c_parser_omp_for (loc, parser, p_name, mask, cclauses, if_p);
      stmt
	= c_finish_omp_parallel (loc, cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				 block);
      જો (ret == NULL_વૃક્ષ)
	પાછા ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      પાછા stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  નહીંતર જો (cclauses
	   && (mask & (OMP_CLAUSE_MASK_1
		       << PRAGMA_OMP_CLAUSE_DIST_SCHEDULE)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_to_pragma_eol (parser);
      પાછા NULL_વૃક્ષ;
    }
  નહીંતર જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      location_t ploc = c_parser_peek_token (parser)->location;
      જો (cclauses == ખાલી && strcmp (p, "masked") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					if_p);
	  block = c_begin_omp_parallel ();
	  વૃક્ષ ret = c_parser_omp_masked (loc, parser, p_name, mask, cclauses,
					  if_p);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  જો (ret == ખાલી)
	    પાછા ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  જો (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  પાછા stmt;
	}
      નહીંતર જો (cclauses == ખાલી && strcmp (p, "master") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					if_p, ploc);
	  block = c_begin_omp_parallel ();
	  વૃક્ષ ret = c_parser_omp_master (loc, parser, p_name, mask, cclauses,
					  if_p, ploc);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  જો (ret == ખાલી)
	    પાછા ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  જો (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  પાછા stmt;
	}
      નહીંતર જો (strcmp (p, "loop") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  જો (cclauses == ખાલી)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  વૃક્ષ ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
					if_p);
	  stmt
	    = c_finish_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
				     block);
	  જો (ret == NULL_વૃક્ષ)
	    પાછા ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  પાછા stmt;
	}
      નહીંતર જો (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  પાછા NULL_વૃક્ષ;
	}
      નહીંતર જો (cclauses == ખાલી && strcmp (p, "sections") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  block = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, mask, cclauses);
	  stmt = c_finish_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL],
					block);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  પાછા stmt;
	}
    }
  નહીંતર જો (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા NULL_વૃક્ષ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_PARALLEL, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_PARALLEL];
    }

  block = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = સાચું;
  c_parser_statement (parser, if_p);
  stmt = c_finish_omp_parallel (loc, clauses, block);

  પાછા stmt;
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

સ્થિર વૃક્ષ
c_parser_omp_single (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ stmt = make_ગાંઠ (OMP_SINGLE);
  SET_પદાવલિ_LOCATION (stmt, loc);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_MASK,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  પાછા add_stmt (stmt);
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

સ્થિર વૃક્ષ
c_parser_omp_scope (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ stmt = make_ગાંઠ (OMP_SCOPE);
  SET_પદાવલિ_LOCATION (stmt, loc);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_MASK,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_block (parser, if_p);

  પાછા add_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
સ્થિર વૃક્ષ
c_parser_omp_dispatch_body (c_parser *parser)
{
  સંરચના c_પદાવલિ lhs, rhs, ret;
  location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_expression (parser, ખાલી, ખાલી);
  જો (વૃક્ષ_CODE (lhs.કિંમત) == CALL_પદાવલિ)
    પાછા lhs.કિંમત;

  location_t op_location = c_parser_peek_token (parser)->location;
  જો (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    પાછા error_mark_ગાંઠ;

  /* Parse function name.  */
  જો (!c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      પાછા error_mark_ગાંઠ;
    }
  પદાવલિ_loc = c_parser_peek_token (parser)->location;
  વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
  c_parser_consume_token (parser);
  જો (!c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      પાછા error_mark_ગાંઠ;
    }

  rhs.કિંમત = build_external_ref (પદાવલિ_loc, id, સાચું, &rhs.original_type);
  set_c_પદાવલિ_source_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_expression_after_primary (
    parser, પદાવલિ_LOC_OR_LOC (rhs.કિંમત, પદાવલિ_loc), rhs);
  જો (વૃક્ષ_CODE (rhs.કિંમત) != CALL_પદાવલિ)
    {
      error_at (પદાવલિ_LOC_OR_LOC (rhs.કિંમત, પદાવલિ_loc),
		"expected target-function call");
      પાછા error_mark_ગાંઠ;
    }

  /* Build assignment. */
  rhs = convert_lvalue_to_rvalue (પદાવલિ_loc, rhs, સાચું, સાચું);
  ret.કિંમત
    = build_modify_પદાવલિ (op_location, lhs.કિંમત, lhs.original_type, NOP_પદાવલિ,
			 પદાવલિ_loc, rhs.કિંમત, rhs.original_type);
  ret.m_decimal = 0;
  set_c_પદાવલિ_source_range (&ret, lhs.get_start (), rhs.get_finish ());
  ret.original_code = MODIFY_પદાવલિ;
  ret.original_type = ખાલી;
  પાછા ret.કિંમત;
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

સ્થિર વૃક્ષ
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  વૃક્ષ stmt = make_ગાંઠ (OMP_DISPATCH);
  SET_પદાવલિ_LOCATION (stmt, loc);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_MASK,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  વૃક્ષ depend_clauses = NULL_વૃક્ષ;
  વૃક્ષ *depend_clauses_ptr = &depend_clauses;
  માટે (વૃક્ષ c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  જો (depend_clauses != NULL_વૃક્ષ)
    {
      વૃક્ષ stmt = make_ગાંઠ (OMP_TASK);
      વૃક્ષ_TYPE (stmt) = void_ગાંઠ;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_વૃક્ષ;
      SET_પદાવલિ_LOCATION (stmt, loc);
      add_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  વૃક્ષ dispatch_body = c_parser_omp_dispatch_body (parser);
  જો (dispatch_body == error_mark_ગાંઠ)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_to_end_of_block_or_statement (parser);
      પાછા NULL_વૃક્ષ;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (વૃક્ષ_CODE (dispatch_body) == CALL_પદાવલિ
	      || વૃક્ષ_CODE (dispatch_body) == MODIFY_પદાવલિ);
  વૃક્ષ *dispatch_call = વૃક્ષ_CODE (dispatch_body) == MODIFY_પદાવલિ
			  ? &વૃક્ષ_OPERAND (dispatch_body, 1)
			  : &dispatch_body;
  જ્યારે (વૃક્ષ_CODE (*dispatch_call) == FLOAT_પદાવલિ
	 || વૃક્ષ_CODE (*dispatch_call) == CONVERT_પદાવલિ
	 || વૃક્ષ_CODE (*dispatch_call) == NOP_પદાવલિ)
    dispatch_call = &વૃક્ષ_OPERAND (*dispatch_call, 0);
  *dispatch_call = build_call_પદાવલિ_internal_loc (
    loc, IFN_GOMP_DISPATCH,
    વૃક્ષ_TYPE (વૃક્ષ_TYPE (CALL_પદાવલિ_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_found (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  પાછા add_stmt (stmt);
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

સ્થિર વૃક્ષ
c_parser_omp_task (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ clauses, block;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_MASK,
				      "#pragma omp task");

  block = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = સાચું;
  c_parser_statement (parser, if_p);
  પાછા c_finish_omp_task (loc, clauses, block);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#define OMP_TASKWAIT_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

સ્થિર શૂન્ય
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  વૃક્ષ clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_MASK,
				"#pragma omp taskwait");

  જો (clauses)
    {
      વૃક્ષ stmt = make_ગાંઠ (OMP_TASK);
      વૃક્ષ_TYPE (stmt) = void_ગાંઠ;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_વૃક્ષ;
      SET_પદાવલિ_LOCATION (stmt, loc);
      add_stmt (stmt);
    }
  નહીંતર
    c_finish_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

સ્થિર શૂન્ય
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

સ્થિર વૃક્ષ
c_parser_omp_taskgroup (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_MASK,
					   "#pragma omp taskgroup");

  વૃક્ષ body = c_parser_omp_structured_block (parser, if_p);
  પાછા c_finish_omp_taskgroup (loc, body, clauses);
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

સ્થિર શૂન્ય
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  વૃક્ષ clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_MASK,
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

સ્થિર તાર્કિક
c_parser_omp_cancellation_point (c_parser *parser, ગણના pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ clauses;
  તાર્કિક point_seen = ખોટું;

  c_parser_consume_pragma (parser);
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  point_seen = સાચું;
	}
    }
  જો (!point_seen)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_to_pragma_eol (parser);
      પાછા ખોટું;
    }

  જો (context != pragma_compound)
    {
      જો (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      નહીંતર
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા સાચું;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_POINT_CLAUSE_MASK,
				"#pragma omp cancellation point");

  c_finish_omp_cancellation_point (loc, clauses);
  પાછા સાચું;
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

સ્થિર વૃક્ષ
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
			 તાર્કિક *if_p)
{
  વૃક્ષ clauses, block, ret;

  strcat (p_name, " distribute");
  mask |= OMP_DISTRIBUTE_CLAUSE_MASK;

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      તાર્કિક simd = ખોટું;
      તાર્કિક parallel = ખોટું;

      જો (strcmp (p, "simd") == 0)
	simd = સાચું;
      નહીંતર
	parallel = strcmp (p, "parallel") == 0;
      જો (parallel || simd)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  જો (cclauses == ખાલી)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      જો (simd)
		પાછા c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
					  if_p);
	      નહીંતર
		પાછા c_parser_omp_parallel (loc, parser, p_name, mask,
					      cclauses, if_p);
	    }
	  block = c_begin_compound_stmt (સાચું);
	  જો (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				     if_p);
	  નહીંતર
	    ret = c_parser_omp_parallel (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, સાચું);
	  જો (ret == ખાલી)
	    પાછા ret;
	  ret = make_ગાંઠ (OMP_DISTRIBUTE);
	  વૃક્ષ_TYPE (ret) = void_type_ગાંઠ;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
	  SET_પદાવલિ_LOCATION (ret, loc);
	  add_stmt (ret);
	  પાછા ret;
	}
    }
  જો (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા NULL_વૃક્ષ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_DISTRIBUTE, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_DISTRIBUTE];
    }

  block = c_begin_compound_stmt (સાચું);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, ખાલી,
			       if_p);
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#define OMP_TEAMS_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_અંક_TEAMS)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_THREAD_LIMIT)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

સ્થિર વૃક્ષ
c_parser_omp_teams (location_t loc, c_parser *parser,
		    અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
		    તાર્કિક *if_p)
{
  વૃક્ષ clauses, block, ret;

  strcat (p_name, " teams");
  mask |= OMP_TEAMS_CLAUSE_MASK;

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "distribute") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  જો (cclauses == ખાલી)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_distribute (loc, parser, p_name, mask,
					    cclauses, if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, mask, cclauses,
					 if_p);
	  block = c_end_compound_stmt (loc, block, સાચું);
	  જો (ret == ખાલી)
	    પાછા ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_ગાંઠ (OMP_TEAMS);
	  વૃક્ષ_TYPE (ret) = void_type_ગાંઠ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_પદાવલિ_LOCATION (ret, loc);
	  પાછા add_stmt (ret);
	}
      નહીંતર જો (strcmp (p, "loop") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  જો (cclauses == ખાલી)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_loop (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, સાચું);
	  જો (ret == ખાલી)
	    પાછા ret;
	  clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
	  ret = make_ગાંઠ (OMP_TEAMS);
	  વૃક્ષ_TYPE (ret) = void_type_ગાંઠ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = block;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  SET_પદાવલિ_LOCATION (ret, loc);
	  પાછા add_stmt (ret);
	}
    }
  જો (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા NULL_વૃક્ષ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_TEAMS, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
    }

  વૃક્ષ stmt = make_ગાંઠ (OMP_TEAMS);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  block = c_begin_omp_parallel ();
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_end_compound_stmt (loc, block, સાચું);
  SET_પદાવલિ_LOCATION (stmt, loc);

  પાછા add_stmt (stmt);
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

સ્થિર વૃક્ષ
c_parser_omp_target_data (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  જો (flag_openmp)
    omp_requires_mask
      = (ગણના omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  વૃક્ષ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_DATA_CLAUSE_MASK,
				"#pragma omp target data", ખોટું);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, ખોટું);
  પૂર્ણાંક map_seen = 0;
  માટે (વૃક્ષ *pc = &clauses; *pc;)
    {
      જો (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	પસંદગી (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  સ્થિતિ GOMP_MAP_TO:
	  સ્થિતિ GOMP_MAP_ALWAYS_TO:
	  સ્થિતિ GOMP_MAP_PRESENT_TO:
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_TO:
	  સ્થિતિ GOMP_MAP_FROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_FROM:
	  સ્થિતિ GOMP_MAP_PRESENT_FROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  સ્થિતિ GOMP_MAP_TOFROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_TOFROM:
	  સ્થિતિ GOMP_MAP_PRESENT_TOFROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  સ્થિતિ GOMP_MAP_ALLOC:
	  સ્થિતિ GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  સ્થિતિ GOMP_MAP_ALWAYS_POINTER:
	  સ્થિતિ GOMP_MAP_ATTACH_DETACH:
	  સ્થિતિ GOMP_MAP_ATTACH:
	    તોડો;
	  મૂળભૂત:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ચાલુ;
	  }
      નહીંતર જો (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_seen = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  જો (map_seen != 3)
    {
      જો (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      પાછા NULL_વૃક્ષ;
    }

  વૃક્ષ stmt = make_ગાંઠ (OMP_TARGET_DATA);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_TARGET_DATA_CLAUSES (stmt) = clauses;
  keep_next_level ();
  વૃક્ષ block = c_begin_compound_stmt (સાચું);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
  OMP_TARGET_DATA_BODY (stmt) = c_end_compound_stmt (loc, block, સાચું);

  SET_પદાવલિ_LOCATION (stmt, loc);
  પાછા add_stmt (stmt);
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

સ્થિર તાર્કિક
c_parser_omp_target_update (location_t loc, c_parser *parser,
			    ગણના pragma_context context)
{
  જો (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા સાચું;
    }

  વૃક્ષ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_UPDATE_CLAUSE_MASK,
				"#pragma omp target update",
				/* finish_p = */ ખોટું);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  જો (omp_find_clause (clauses, OMP_CLAUSE_TO) == NULL_વૃક્ષ
      && omp_find_clause (clauses, OMP_CLAUSE_FROM) == NULL_વૃક્ષ)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      પાછા ખોટું;
    }

  જો (flag_openmp)
    omp_requires_mask
      = (ગણના omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  વૃક્ષ stmt = make_ગાંઠ (OMP_TARGET_UPDATE);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_TARGET_UPDATE_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, loc);
  add_stmt (stmt);
  પાછા ખોટું;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#define OMP_TARGET_ENTER_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

સ્થિર તાર્કિક
c_parser_omp_target_enter_data (location_t loc, c_parser *parser,
				ગણના pragma_context context)
{
  તાર્કિક data_seen = ખોટું;
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = સાચું;
	}
    }
  જો (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      પાછા ખોટું;
    }

  જો (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા સાચું;
    }

  જો (flag_openmp)
    omp_requires_mask
      = (ગણના omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  વૃક્ષ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_ENTER_DATA_CLAUSE_MASK,
				"#pragma omp target enter data", ખોટું);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, ખોટું);
  પૂર્ણાંક map_seen = 0;
  માટે (વૃક્ષ *pc = &clauses; *pc;)
    {
      જો (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	પસંદગી (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  સ્થિતિ GOMP_MAP_TO:
	  સ્થિતિ GOMP_MAP_ALWAYS_TO:
	  સ્થિતિ GOMP_MAP_PRESENT_TO:
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_TO:
	  સ્થિતિ GOMP_MAP_ALLOC:
	  સ્થિતિ GOMP_MAP_PRESENT_ALLOC:
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_TO);
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_TO);
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_TO);
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_TO);
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  સ્થિતિ GOMP_MAP_ALWAYS_POINTER:
	  સ્થિતિ GOMP_MAP_ATTACH_DETACH:
	  સ્થિતિ GOMP_MAP_ATTACH:
	    તોડો;
	  મૂળભૂત:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ચાલુ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  જો (map_seen != 3)
    {
      જો (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      પાછા સાચું;
    }

  વૃક્ષ stmt = make_ગાંઠ (OMP_TARGET_ENTER_DATA);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_TARGET_ENTER_DATA_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, loc);
  add_stmt (stmt);
  પાછા સાચું;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#define OMP_TARGET_EXIT_DATA_CLAUSE_MASK			\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

સ્થિર તાર્કિક
c_parser_omp_target_exit_data (location_t loc, c_parser *parser,
			       ગણના pragma_context context)
{
  તાર્કિક data_seen = ખોટું;
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  data_seen = સાચું;
	}
    }
  જો (!data_seen)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_to_pragma_eol (parser);
      પાછા ખોટું;
    }

  જો (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા સાચું;
    }

  જો (flag_openmp)
    omp_requires_mask
      = (ગણના omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  વૃક્ષ clauses
    = c_parser_omp_all_clauses (parser, OMP_TARGET_EXIT_DATA_CLAUSE_MASK,
				"#pragma omp target exit data", ખોટું);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_DATA);
  clauses = c_finish_omp_clauses (clauses, C_ORT_OMP_EXIT_DATA);
  c_omp_adjust_map_clauses (clauses, ખોટું);
  પૂર્ણાંક map_seen = 0;
  માટે (વૃક્ષ *pc = &clauses; *pc;)
    {
      જો (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	પસંદગી (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  સ્થિતિ GOMP_MAP_FROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_FROM:
	  સ્થિતિ GOMP_MAP_PRESENT_FROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  સ્થિતિ GOMP_MAP_RELEASE:
	  સ્થિતિ GOMP_MAP_DELETE:
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_FROM);
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_PRESENT_FROM);
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_SET_MAP_KIND (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_seen = 3;
	    તોડો;
	  સ્થિતિ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  સ્થિતિ GOMP_MAP_ALWAYS_POINTER:
	  સ્થિતિ GOMP_MAP_ATTACH_DETACH:
	  સ્થિતિ GOMP_MAP_DETACH:
	    તોડો;
	  મૂળભૂત:
	    map_seen |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ચાલુ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  જો (map_seen != 3)
    {
      જો (map_seen == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      પાછા સાચું;
    }

  વૃક્ષ stmt = make_ગાંઠ (OMP_TARGET_EXIT_DATA);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
  OMP_TARGET_EXIT_DATA_CLAUSES (stmt) = clauses;
  SET_પદાવલિ_LOCATION (stmt, loc);
  add_stmt (stmt);
  પાછા સાચું;
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

સ્થિર તાર્કિક
c_parser_omp_target (c_parser *parser, ગણના pragma_context context, તાર્કિક *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  વૃક્ષ *pc = ખાલી, stmt, block, body, clauses;

  જો (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_pragma_eol (parser);
      પાછા ખોટું;
    }

  જો (flag_openmp)
    omp_requires_mask
      = (ગણના omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      ગણના વૃક્ષ_code ccode = ERROR_MARK;

      જો (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      નહીંતર જો (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      નહીંતર જો (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      જો (ccode != ERROR_MARK)
	{
	  વૃક્ષ cclauses[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  અક્ષર p_name[કદ ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      વૃક્ષ stmt;
	      પસંદગી (ccode)
		{
		સ્થિતિ OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_TARGET_CLAUSE_MASK,
					     cclauses, if_p);
		  તોડો;
		સ્થિતિ OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_TARGET_CLAUSE_MASK,
						cclauses, if_p);
		  તોડો;
		સ્થિતિ OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_TARGET_CLAUSE_MASK,
					    cclauses, if_p);
		  તોડો;
		મૂળભૂત:
		  gcc_unreachable ();
		}
	      પાછા stmt != NULL_વૃક્ષ;
	    }
	  keep_next_level ();
	  વૃક્ષ block = c_begin_compound_stmt (સાચું), ret;
	  પસંદગી (ccode)
	    {
	    સ્થિતિ OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_TARGET_CLAUSE_MASK, cclauses,
					if_p);
	      તોડો;
	    સ્થિતિ OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_TARGET_CLAUSE_MASK, cclauses,
					   if_p);
	      તોડો;
	    સ્થિતિ OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_TARGET_CLAUSE_MASK, cclauses,
				       if_p);
	      તોડો;
	    મૂળભૂત:
	      gcc_unreachable ();
	    }
	  block = c_end_compound_stmt (loc, block, સાચું);
	  જો (ret == NULL_વૃક્ષ)
	    પાછા ખોટું;
	  જો (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    માટે (વૃક્ષ c = cclauses[C_OMP_CLAUSE_SPLIT_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_અંક_TEAMS
		  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_THREAD_LIMIT)
		માટે (પૂર્ણાંક i = 0;
		     i <= (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_અંક_TEAMS); ++i)
		  જો (OMP_CLAUSE_OPERAND (c, i)
		      && વૃક્ષ_CODE (OMP_CLAUSE_OPERAND (c, i)) != INTEGER_CST)
		    {
		      વૃક્ષ પદાવલિ = OMP_CLAUSE_OPERAND (c, i);
		      વૃક્ષ tmp = create_tmp_var_raw (વૃક્ષ_TYPE (પદાવલિ));
		      પદાવલિ = build4 (TARGET_પદાવલિ, વૃક્ષ_TYPE (પદાવલિ), tmp,
				     પદાવલિ, NULL_વૃક્ષ, NULL_વૃક્ષ);
		      add_stmt (પદાવલિ);
		      OMP_CLAUSE_OPERAND (c, i) = પદાવલિ;
		      વૃક્ષ tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
		      cclauses[C_OMP_CLAUSE_SPLIT_TARGET] = tc;
		    }
	  વૃક્ષ stmt = make_ગાંઠ (OMP_TARGET);
	  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;
	  OMP_TARGET_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_SPLIT_TARGET];
	  c_omp_adjust_map_clauses (OMP_TARGET_CLAUSES (stmt), સાચું);
	  OMP_TARGET_BODY (stmt) = block;
	  OMP_TARGET_COMBINED (stmt) = 1;
	  SET_પદાવલિ_LOCATION (stmt, loc);
	  add_stmt (stmt);
	  pc = &OMP_TARGET_CLAUSES (stmt);
	  જાઓ check_clauses;
	}
      નહીંતર જો (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  પાછા ખોટું;
	}
      નહીંતર જો (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_target_data (loc, parser, if_p);
	  પાછા સાચું;
	}
      નહીંતર જો (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  પાછા c_parser_omp_target_enter_data (loc, parser, context);
	}
      નહીંતર જો (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  પાછા c_parser_omp_target_exit_data (loc, parser, context);
	}
      નહીંતર જો (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  પાછા c_parser_omp_target_update (loc, parser, context);
	}
    }
  જો (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા ખોટું;
    }

  stmt = make_ગાંઠ (OMP_TARGET);
  વૃક્ષ_TYPE (stmt) = void_type_ગાંઠ;

  clauses = c_parser_omp_all_clauses (parser, OMP_TARGET_CLAUSE_MASK,
				      "#pragma omp target", ખોટું);
  માટે (વૃક્ષ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
      {
	વૃક્ષ nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_SET_MAP_KIND (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_TARGET);
  clauses  = c_finish_omp_clauses (clauses, C_ORT_OMP_TARGET);
  c_omp_adjust_map_clauses (clauses, સાચું);

  keep_next_level ();
  block = c_begin_compound_stmt (સાચું);
  body = c_parser_omp_structured_block (parser, if_p);

  c_omp_scan_mapper_bindings (loc, &clauses, body);

  add_stmt (body);
  OMP_TARGET_CLAUSES (stmt) = clauses;
  pc = &OMP_TARGET_CLAUSES (stmt);
  OMP_TARGET_BODY (stmt) = c_end_compound_stmt (loc, block, સાચું);

  SET_પદાવલિ_LOCATION (stmt, loc);
  add_stmt (stmt);

check_clauses:
  જ્યારે (*pc)
    {
      જો (OMP_CLAUSE_CODE (*pc) == OMP_CLAUSE_MAP)
	પસંદગી (OMP_CLAUSE_MAP_KIND (*pc))
	  {
	  સ્થિતિ GOMP_MAP_TO:
	  સ્થિતિ GOMP_MAP_ALWAYS_TO:
	  સ્થિતિ GOMP_MAP_PRESENT_TO:
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_TO:
	  સ્થિતિ GOMP_MAP_FROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_FROM:
	  સ્થિતિ GOMP_MAP_PRESENT_FROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  સ્થિતિ GOMP_MAP_TOFROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_TOFROM:
	  સ્થિતિ GOMP_MAP_PRESENT_TOFROM:
	  સ્થિતિ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  સ્થિતિ GOMP_MAP_ALLOC:
	  સ્થિતિ GOMP_MAP_PRESENT_ALLOC:
	  સ્થિતિ GOMP_MAP_FIRSTPRIVATE_POINTER:
	  સ્થિતિ GOMP_MAP_ALWAYS_POINTER:
	  સ્થિતિ GOMP_MAP_POINTER:
	  સ્થિતિ GOMP_MAP_ATTACH_DETACH:
	  સ્થિતિ GOMP_MAP_ATTACH:
	    તોડો;
	  મૂળભૂત:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ચાલુ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_target = સાચું;
  પાછા સાચું;
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

સ્થિર શૂન્ય
c_parser_omp_declare_simd (c_parser *parser, ગણના pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  વૃક્ષ kind = token->કિંમત;
  gcc_assert (strcmp (IDENTIFIER_POINTER (kind), "simd") == 0
	      || strcmp (IDENTIFIER_POINTER (kind), "variant") == 0);

  auto_vec<c_token> clauses;
  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      જો (token->type == CPP_EOF)
	{
	  c_parser_skip_to_pragma_eol (parser);
	  પાછા;
	}
      clauses.safe_ધકેલો (*token);
      c_parser_consume_token (parser);
    }
  clauses.safe_ધકેલો (*c_parser_peek_token (parser));
  c_parser_skip_to_pragma_eol (parser);

  જ્યારે (c_parser_next_token_is (parser, CPP_PRAGMA))
    {
      જો (c_parser_peek_token (parser)->pragma_kind != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->કિંમત != kind)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_POINTER (kind), IDENTIFIER_POINTER (kind));
	  પાછા;
	}
      c_parser_consume_pragma (parser);
      જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  જો (token->type == CPP_EOF)
	    {
	      c_parser_skip_to_pragma_eol (parser);
	      પાછા;
	    }
	  clauses.safe_ધકેલો (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_ધકેલો (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, કદ (eof_token));
  eof_token.type = CPP_EOF;
  clauses.safe_ધકેલો (eof_token);
  clauses.safe_ધકેલો (eof_token);

  પસંદગી (context)
    {
    સ્થિતિ pragma_external:
      જો (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  પૂર્ણાંક ext = disable_extension_diagnostics ();
	  કરો
	    c_parser_consume_token (parser);
	  જ્યારે (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, ખોટું, સાચું,
					 ખોટું, ખાલી, &clauses);
	  restore_extension_diagnostics (ext);
	}
      નહીંતર
	c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, ખોટું, સાચું,
				       ખોટું, ખાલી, &clauses);
      તોડો;
    સ્થિતિ pragma_struct:
    સ્થિતિ pragma_param:
    સ્થિતિ pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      તોડો;
    સ્થિતિ pragma_compound:
      તાર્કિક have_std_attrs;
      વૃક્ષ std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_attributes (parser, 1);
      જો (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      નહીંતર
	std_attrs = NULL_વૃક્ષ;
      જો (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  પૂર્ણાંક ext = disable_extension_diagnostics ();
	  કરો
	    c_parser_consume_token (parser);
	  જ્યારે (c_parser_next_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  જો (c_parser_next_tokens_start_declaration (parser)
	      || c_parser_nth_token_starts_std_attributes (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, સાચું,
					     સાચું, ખોટું, ખાલી, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      તોડો;
	    }
	  restore_extension_diagnostics (ext);
	}
      નહીંતર જો (c_parser_next_tokens_start_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, સાચું, સાચું, સાચું, સાચું, સાચું,
					 ખોટું, ખાલી, &clauses, have_std_attrs,
					 std_attrs);
	  તોડો;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_POINTER (kind));
      તોડો;
    મૂળભૂત:
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

સ્થિર વૃક્ષ
c_parser_omp_context_selector (c_parser *parser, ગણના omp_tss_code set,
			       વૃક્ષ parms)
{
  વૃક્ષ ret = NULL_વૃક્ષ;
  કરો
    {
      વૃક્ષ selector;
      જો (c_parser_next_token_is (parser, CPP_KEYWORD)
	  || c_parser_next_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->કિંમત;
      નહીંતર
	{
	  c_parser_error (parser, "expected trait selector name");
	  પાછા error_mark_ગાંઠ;
	}
      ગણના omp_ts_code sel
	= omp_lookup_ts_code (set, IDENTIFIER_POINTER (selector));

      જો (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_POINTER (selector),  omp_tss_map[set]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_વૃક્ષ, NULL_વૃક્ષ, ret);
	  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_balanced_token_sequence (parser);
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ચાલુ;
	    }
	  નહીંતર
	    તોડો;
	}

      c_parser_consume_token (parser);

      વૃક્ષ properties = NULL_વૃક્ષ;
      વૃક્ષ scoreval = NULL_વૃક્ષ;
      ગણના omp_tp_type property_kind = omp_ts_map[sel].tp_type;
      તાર્કિક allow_score = omp_ts_map[sel].allow_score;
      વૃક્ષ t;

      જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  જો (property_kind == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_POINTER (selector));
	      પાછા error_mark_ગાંઠ;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER (token->કિંમત), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      વૃક્ષ score = c_parser_પદાવલિ_no_commas (parser, ખાલી).કિંમત;
	      parens2.skip_until_found_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      જો (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[set]);
	      નહીંતર જો (score != error_mark_ગાંઠ)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, ખોટું, ખાલી);
		  જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (score))
		      || વૃક્ષ_CODE (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  નહીંતર જો (વૃક્ષ_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  નહીંતર
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  પસંદગી (property_kind)
	    {
	    સ્થિતિ OMP_TRAIT_PROPERTY_ID:
	      જો (c_parser_next_token_is (parser, CPP_KEYWORD)
		  || c_parser_next_token_is (parser, CPP_NAME))
		{
		  વૃક્ષ prop = c_parser_peek_token (parser)->કિંમત;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_વૃક્ષ,
						    properties);
		}
	      નહીંતર
		{
		  c_parser_error (parser, "expected identifier");
		  પાછા error_mark_ગાંઠ;
		}
	      તોડો;
	    સ્થિતિ OMP_TRAIT_PROPERTY_NAME_LIST:
	      કરો
		{
		  વૃક્ષ prop = OMP_TP_NAMELIST_ગાંઠ;
		  વૃક્ષ કિંમત = NULL_વૃક્ષ;
		  જો (c_parser_next_token_is (parser, CPP_KEYWORD)
		      || c_parser_next_token_is (parser, CPP_NAME))
		    {
		      કિંમત = c_parser_peek_token (parser)->કિંમત;
		      c_parser_consume_token (parser);
		    }
		  નહીંતર જો (c_parser_next_token_is (parser, CPP_STRING))
		    કિંમત = c_parser_string_literal (parser, ખોટું,
						     ખોટું).કિંમત;
		  નહીંતર
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      પાછા error_mark_ગાંઠ;
		    }

		  properties = make_trait_property (prop, કિંમત, properties);

		  જો (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  નહીંતર
		    તોડો;
		}
	      જ્યારે (1);
	      તોડો;
	    સ્થિતિ OMP_TRAIT_PROPERTY_DEV_અંક_પદાવલિ:
	    સ્થિતિ OMP_TRAIT_PROPERTY_BOOL_પદાવલિ:
	      {
		c_પદાવલિ texpr = c_parser_પદાવલિ_no_commas (parser, ખાલી);
		texpr = convert_lvalue_to_rvalue (token->location, texpr,
						  સાચું, સાચું);
		t = texpr.કિંમત;
	      }
	      જો (t == error_mark_ગાંઠ)
		પાછા error_mark_ગાંઠ;
	      mark_exp_read (t);
	      જો (property_kind == OMP_TRAIT_PROPERTY_BOOL_પદાવલિ)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_ગાંઠ);
		  જો (t == error_mark_ગાંઠ)
		    પાછા error_mark_ગાંઠ;
		}
	      નહીંતર જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  પાછા error_mark_ગાંઠ;
		}
	      t = c_fully_fold (t, ખોટું, ખાલી);
	      properties = make_trait_property (NULL_વૃક્ષ, t, properties);
	      તોડો;
	    સ્થિતિ OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      જો (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  જો (parms == NULL_વૃક્ષ)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      પાછા error_mark_ગાંઠ;
		    }
		  વૃક્ષ c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_MASK,
						"simd", સાચું, 2);
		  c = c_omp_declare_simd_clauses_to_numbers (parms
							     == error_mark_ગાંઠ
							     ? NULL_વૃક્ષ : parms,
							     c);
		  properties = c;
		}
	      નહીંતર જો (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  પાછા error_mark_ગાંઠ;
		}
	      નહીંતર
		gcc_unreachable ();
	      તોડો;
	    મૂળભૂત:
	      gcc_unreachable ();
	    }

	  parens.skip_until_found_close (parser);
	  properties = nreverse (properties);
	}
      નહીંતર જો (property_kind != OMP_TRAIT_PROPERTY_NONE
	       && property_kind != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_kind != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  પાછા error_mark_ગાંઠ;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
    }
  જ્યારે (1);

  પાછા nreverse (ret);
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

સ્થિર વૃક્ષ
c_parser_omp_context_selector_specification (c_parser *parser, વૃક્ષ parms)
{
  વૃક્ષ ret = NULL_વૃક્ષ;
  કરો
    {
      અચલ અક્ષર *setp = "";
      જો (c_parser_next_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      ગણના omp_tss_code set = omp_lookup_tss_code (setp);

      જો (set == OMP_TRAIT_SET_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  પાછા error_mark_ગાંઠ;
	}

      c_parser_consume_token (parser);

      જો (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	પાછા error_mark_ગાંઠ;

      matching_braces braces;
      જો (!braces.require_open (parser))
	પાછા error_mark_ગાંઠ;

      વૃક્ષ selectors = c_parser_omp_context_selector (parser, set, parms);
      જો (selectors == error_mark_ગાંઠ)
	{
	  c_parser_skip_to_closing_brace (parser);
	  ret = error_mark_ગાંઠ;
	}
      નહીંતર જો (ret != error_mark_ગાંઠ)
	ret = make_trait_set_selector (set, selectors, ret);

      braces.require_close (parser);

      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      નહીંતર
	તોડો;
    }
  જ્યારે (1);

  જો (ret == error_mark_ગાંઠ)
    પાછા ret;
  પાછા nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

સ્થિર શૂન્ય
c_finish_omp_declare_variant (c_parser *parser, વૃક્ષ fndecl, વૃક્ષ parms)
{
  matching_parens parens;
  જો (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા;
    }

  જો (c_parser_next_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      જાઓ fail;
    }

  c_token *token = c_parser_peek_token (parser);
  વૃક્ષ variant = lookup_name (token->કિંમત);

  જો (variant == NULL_વૃક્ષ)
    {
      undeclared_variable (token->location, token->કિંમત);
      variant = error_mark_ગાંઠ;
    }
  નહીંતર જો (વૃક્ષ_CODE (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_ગાંઠ;
    }
  નહીંતર જો (fndecl_built_in_p (variant)
	   && (strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			"__builtin_", strlen ("__builtin_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__sync_", strlen ("__sync_")) == 0
	       || strncmp (IDENTIFIER_POINTER (DECL_NAME (variant)),
			   "__atomic_", strlen ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_ગાંઠ;
    }
  નહીંતર જો (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_ગાંઠ;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  વૃક્ષ append_args_વૃક્ષ = NULL_વૃક્ષ;
  વૃક્ષ append_args_last;
  vec<વૃક્ષ> adjust_args_list = vNULL;
  તાર્કિક has_match = ખોટું, has_adjust_args = ખોટું;
  location_t adjust_args_loc = UNKNOWN_LOCATION;
  location_t append_args_loc = UNKNOWN_LOCATION;
  location_t match_loc = UNKNOWN_LOCATION;
  વૃક્ષ need_device_ptr_list = NULL_વૃક્ષ;
  વૃક્ષ ctx = error_mark_ગાંઠ;

  કરો
    {
      જો (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      અચલ અક્ષર *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      જો (c_parser_next_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      ગણના clause
      {
	match,
	adjust_args,
	append_args
      } ccode;

      જો (strcmp (clause, "match") == 0)
	{
	  ccode = match;
	  match_loc = loc;
	}
      નહીંતર જો (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_args;
	  adjust_args_loc = loc;
	}
      નહીંતર જો (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_args;
	  append_args_loc = loc;
	}
      નહીંતર
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  જાઓ fail;
	}

      c_parser_consume_token (parser);

      જો (!parens.require_open (parser))
	જાઓ fail;

      જો (parms == NULL_વૃક્ષ)
	parms = error_mark_ગાંઠ;

      જો (ccode == match)
	{
	  જો (has_match)
	    error_at (match_loc, "too many %<match%> clauses");
	  has_match = સાચું;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  જો (ctx == error_mark_ગાંઠ)
	    જાઓ fail;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  જો (ctx != error_mark_ગાંઠ
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      વૃક્ષ outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      નહીંતર જો (ccode == adjust_args)
	{
	  has_adjust_args = સાચું;
	  જો (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      અચલ અક્ષર *p
		= IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	      જો (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  વૃક્ષ list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_વૃક્ષ);

		  વૃક્ષ arg;
		  જો (variant != error_mark_ગાંઠ)
		    માટે (વૃક્ષ c = list; c != NULL_વૃક્ષ; c = વૃક્ષ_CHAIN (c))
		      {
			વૃક્ષ decl = વૃક્ષ_PURPOSE (c);
			location_t arg_loc = પદાવલિ_LOCATION (વૃક્ષ_કિંમત (c));
			પૂર્ણાંક idx;
			માટે (arg = parms, idx = 0; arg != ખાલી;
			     arg = વૃક્ષ_CHAIN (arg), idx++)
			  જો (arg == decl)
			    તોડો;
			જો (arg == NULL_વૃક્ષ)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    જાઓ fail;
			  }
			જો (adjust_args_list.contains (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    જાઓ fail;
			  }
			જો (strcmp (p, "need_device_ptr") == 0
			    && વૃક્ષ_CODE (વૃક્ષ_TYPE (arg)) != POINTER_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    જાઓ fail;
			  }
			adjust_args_list.safe_ધકેલો (arg);
			જો (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_વૃક્ષ_list (
				NULL_વૃક્ષ,
				build_int_cst (
				  integer_type_ગાંઠ,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      નહીંતર
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  જો (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  જાઓ fail;
		}
	    }
	  નહીંતર
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      જાઓ fail;
	    }
	}
      નહીંતર જો (ccode == append_args)
	{
	  જો (append_args_વૃક્ષ)
	    {
	      error_at (append_args_loc, "too many %qs clauses", "append_args");
	      append_args_વૃક્ષ = NULL_વૃક્ષ;
	    }
	  કરો
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      જો (!c_parser_next_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_POINTER (
			       c_parser_peek_token (parser)->કિંમત)))
		{
		  error_at (loc, "expected %<interop%>");
		  જાઓ fail;
		}
	      c_parser_consume_token (parser);

	      જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		જાઓ fail;
	      તાર્કિક target = ખોટું;
	      તાર્કિક targetsync = ખોટું;
	      વૃક્ષ prefer_type_વૃક્ષ = NULL_વૃક્ષ;
	      જો (!c_parser_omp_clause_init_modifiers (parser, &target,
						       &targetsync,
						       &prefer_type_વૃક્ષ)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		જાઓ fail;
	      જો (!target && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      વૃક્ષ t = build_વૃક્ષ_list (target ? boolean_true_ગાંઠ
					       : boolean_false_ગાંઠ,
					targetsync ? boolean_true_ગાંઠ
						   : boolean_false_ગાંઠ);
	      t = build1_loc (loc, NOP_પદાવલિ, void_type_ગાંઠ, t);
	      t = build_વૃક્ષ_list (t, prefer_type_વૃક્ષ);
	      જો (append_args_વૃક્ષ)
		{
		  વૃક્ષ_CHAIN (append_args_last) = t;
		  append_args_last = t;
		}
	      નહીંતર
		append_args_વૃક્ષ = append_args_last = t;
	      જો (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		તોડો;
	      જો (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		જાઓ fail;
	    }
	  જ્યારે (સાચું);
	}

      parens.require_close (parser);
  } જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL));
  જો (variant != error_mark_ગાંઠ && !has_match)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_ગાંઠ;
    }
  c_parser_skip_to_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  જો (variant == error_mark_ગાંઠ || ctx == error_mark_ગાંઠ)
    /* Previously diagnosed error.  */
    પાછા;

  જો ((has_adjust_args || append_args_વૃક્ષ)
      && !omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_args ? adjust_args_loc : append_args_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_args ? "adjust_args" : "append_args");
      પાછા;
    }

  જો (!omp_get_context_selector (ctx, OMP_TRAIT_SET_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      વૃક્ષ base_type = વૃક્ષ_TYPE (fndecl);
      વૃક્ષ variant_type = વૃક્ષ_TYPE (variant);
      તાર્કિક unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_વૃક્ષ
	   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type));

      જો (append_args_વૃક્ષ
	  && TYPE_ARG_TYPES (base_type) == NULL_વૃક્ષ
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
	  પાછા;
	}
      નહીંતર જો (append_args_વૃક્ષ)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  પૂર્ણાંક nappend_args = 0;
	  પૂર્ણાંક nbase_args = 0;
	  માટે (વૃક્ષ t = TYPE_ARG_TYPES (base_type);
	       t && વૃક્ષ_કિંમત (t) != void_type_ગાંઠ; t = વૃક્ષ_CHAIN (t))
	    nbase_args++;
	  માટે (વૃક્ષ t = append_args_વૃક્ષ; t; t = વૃક્ષ_CHAIN (t))
	    nappend_args++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_args_વૃક્ષ = build_વૃક્ષ_list (build_int_cst (integer_type_ગાંઠ,
							     nbase_args),
					      append_args_વૃક્ષ);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  જો (!unprototyped_variant)
	    {
	      વૃક્ષ args = TYPE_ARG_TYPES (variant_type);
	      માટે (પૂર્ણાંક i = 0; args && i < nbase_args;
		   i++, args = વૃક્ષ_CHAIN (args))
		;
	      માટે (પૂર્ણાંક i = 0; i < nappend_args; i++, args = વૃક્ષ_CHAIN (args))
		જો (!args || !c_omp_interop_t_p (વૃક્ષ_કિંમત (args)))
		  {
		    error_at (DECL_SOURCE_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_args + i + 1, variant);
		    inform (append_args_loc,
			    "%<append_args%> specified here");
		    પાછા;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  વૃક્ષ args = TYPE_ARG_TYPES (base_type);
	  વૃક્ષ newargs = NULL_વૃક્ષ;
	  વૃક્ષ lastarg = NULL_વૃક્ષ;
	  માટે (પૂર્ણાંક j = 0; j < nbase_args; j++, args = વૃક્ષ_CHAIN (args))
	    {
	      વૃક્ષ t = વૃક્ષ_cons (વૃક્ષ_PURPOSE (args),
				  વૃક્ષ_કિંમત (args), NULL_વૃક્ષ);
	      જો (lastarg)
		વૃક્ષ_CHAIN (lastarg) = t;
	      નહીંતર
		newargs = t;
	      lastarg = t;
	    }
	  વૃક્ષ type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? વૃક્ષ_TYPE (type) : pointer_sized_int_ગાંઠ;
	  માટે (પૂર્ણાંક j = 0; j < nappend_args; j++)
	    {
	      વૃક્ષ t = વૃક્ષ_cons (NULL_વૃક્ષ, type, NULL_વૃક્ષ);
	      જો (lastarg)
		વૃક્ષ_CHAIN (lastarg) = t;
	      નહીંતર
		newargs = t;
	      lastarg = t;
	    }
	  વૃક્ષ_CHAIN (lastarg) = args;

	  /* Temporarily stuff newargs into the original base_type.  */
	  વૃક્ષ saveargs = TYPE_ARG_TYPES (base_type);
	  TYPE_ARG_TYPES (base_type) = newargs;
	  તાર્કિક fail = !comptypes (base_type, variant_type);
	  TYPE_ARG_TYPES (base_type) = saveargs;

	  જો (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      પાછા;
	    }
	  નહીંતર જો (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      નહીંતર  /* No append_args present.  */
	{
	  જો (!comptypes (base_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_SOURCE_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      પાછા;
	    }
	  નહીંતર જો (TYPE_ARG_TYPES (variant_type) == NULL_વૃક્ષ
		   && !TYPE_NO_NAMED_ARGS_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (base_type) != NULL_વૃક્ષ)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (base_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_USED (variant) = 1;
  વૃક્ષ construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (match_loc, variant, construct);
  જો (omp_context_selector_matches (ctx, NULL_વૃક્ષ, ખોટું))
    {
      વૃક્ષ attr = વૃક્ષ_cons (get_identifier ("omp declare variant base"),
			     build_વૃક્ષ_list (variant, ctx),
			     DECL_ATTRIBUTES (fndecl));
      DECL_ATTRIBUTES (fndecl) = attr;
    }

  જો (need_device_ptr_list || append_args_વૃક્ષ)
    {
      વૃક્ષ variant_decl = વૃક્ષ_strip_nop_conversions (variant);
      વૃક્ષ t = build_વૃક્ષ_list (need_device_ptr_list,
				NULL_વૃક્ષ /* need_device_addr */);
      વૃક્ષ_CHAIN (t) = append_args_વૃક્ષ;
      DECL_ATTRIBUTES (variant_decl)
	= વૃક્ષ_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ATTRIBUTES (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

સ્થિર શૂન્ય
c_finish_omp_declare_simd (c_parser *parser, વૃક્ષ fndecl, વૃક્ષ parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  જો (clauses.exists () && clauses[0].type == CPP_EOF)
    પાછા;
  અચલ અક્ષર *kind = "simd";
  જો (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    kind = IDENTIFIER_POINTER (clauses[0].કિંમત);
  gcc_assert (strcmp (kind, "simd") == 0 || strcmp (kind, "variant") == 0);
  જો (fndecl == NULL_વૃક્ષ || વૃક્ષ_CODE (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      પાછા;
    }
  જો (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", kind);
      clauses[0].type = CPP_EOF;
      પાછા;
    }
  જો (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_SOURCE_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", kind);
      પાછા;
    }

  જો (parms == NULL_વૃક્ષ)
    parms = DECL_ARGUMENTS (fndecl);

  unsigned પૂર્ણાંક tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);

  parser->tokens = clauses.address ();
  parser->tokens_avail = clauses.length ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  જ્યારે (parser->tokens_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      kind = IDENTIFIER_POINTER (token->કિંમત);
      c_parser_consume_token (parser);
      parser->in_pragma = સાચું;

      જો (strcmp (kind, "simd") == 0)
	{
	  વૃક્ષ c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_MASK,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_to_numbers (parms, c);
	  જો (c != NULL_વૃક્ષ)
	    c = વૃક્ષ_cons (NULL_વૃક્ષ, c, NULL_વૃક્ષ);
	  c = build_વૃક્ષ_list (get_identifier ("omp declare simd"), c);
	  વૃક્ષ_CHAIN (c) = DECL_ATTRIBUTES (fndecl);
	  DECL_ATTRIBUTES (fndecl) = c;
	}
      નહીંતર
	{
	  gcc_assert (strcmp (kind, "variant") == 0);
	  c_finish_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->tokens = &parser->tokens_buf[0];
  parser->tokens_avail = tokens_avail;
  જો (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#જો !defined (NO_DOT_IN_LABEL)
#define JOIN_STR "."
#અથવાજો !defined (NO_DOLLAR_IN_LABEL)
#define JOIN_STR "$"
#નહીંતર
#define JOIN_STR "_"
#endif

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
સ્થિર વૃક્ષ
omp_start_variant_function (c_declarator *declarator, વૃક્ષ ctx)
{
  c_declarator *id = declarator;
  જ્યારે (id->kind != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  વૃક્ષ name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  પાછા name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
સ્થિર શૂન્ય
omp_finish_variant_function (વૃક્ષ decl, વૃક્ષ base_name, વૃક્ષ ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  વૃક્ષ base_decl = lookup_name (base_name);
  જો (base_decl == error_mark_ગાંઠ)
    base_decl = NULL_વૃક્ષ;
  જો (!base_decl)
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_POINTER (base_name));
      પાછા;
    }

  જો (!comptypes (વૃક્ષ_TYPE (decl), વૃક્ષ_TYPE (base_decl)))
    {
      error_at (DECL_SOURCE_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", base_decl);
      inform (DECL_SOURCE_LOCATION (base_decl),
	      "%qE declared here", base_decl);
      પાછા;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_SOURCE_LOCATION (decl),
				   base_decl, ctx);
  વૃક્ષ construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_SET_CONSTRUCT);
  omp_mark_declare_variant (DECL_SOURCE_LOCATION (decl), decl, construct);
  વૃક્ષ attrs = DECL_ATTRIBUTES (base_decl);
  વૃક્ષ match_loc_ગાંઠ
    = maybe_wrap_with_location (integer_zero_ગાંઠ,
				DECL_SOURCE_LOCATION (base_decl));
  વૃક્ષ loc_ગાંઠ = વૃક્ષ_cons (match_loc_ગાંઠ, integer_zero_ગાંઠ,
			     build_વૃક્ષ_list (match_loc_ગાંઠ,
					      integer_zero_ગાંઠ));
  attrs = વૃક્ષ_cons (get_identifier ("omp declare variant base"),
		     વૃક્ષ_cons (decl, ctx, loc_ગાંઠ), attrs);
  DECL_ATTRIBUTES (base_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  વૃક્ષ_PUBLIC (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

તાર્કિક
c_maybe_parse_omp_decl (વૃક્ષ decl, વૃક્ષ d)
{
  gcc_assert (વૃક્ષ_CODE (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_TOKENS (d);
  c_token *first = toks->address ();
  c_token *last = first + toks->length ();
  અચલ અક્ષર *directive[3] = {};
  માટે (પૂર્ણાંક j = 0; j < 3; j++)
    {
      વૃક્ષ id = NULL_વૃક્ષ;
      જો (first + j == last)
	તોડો;
      જો (first[j].type == CPP_NAME)
	id = first[j].કિંમત;
      નહીંતર જો (first[j].type == CPP_KEYWORD)
	id = ridpointers[(પૂર્ણાંક) first[j].keyword];
      નહીંતર
	તોડો;
      directive[j] = IDENTIFIER_POINTER (id);
    }
  અચલ c_omp_directive *dir = ખાલી;
  જો (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  જો (dir == ખાલી)
    {
      error_at (first->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      પાછા ખોટું;
    }
  જો (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    પાછા ખોટું;

  જો (!flag_openmp && !dir->simd)
    પાછા સાચું;

  c_parser *parser = the_parser;
  unsigned પૂર્ણાંક tokens_avail = parser->tokens_avail;
  gcc_assert (parser->tokens == &parser->tokens_buf[0]);
  toks = ખાલી;
  vec_safe_reserve (toks, last - first + 2, સાચું);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_kind = pragma_kind (dir->id);
  tok.location = first->location;
  toks->quick_ધકેલો (tok);
  જ્યારે (++first < last)
    toks->quick_ધકેલો (*first);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_ધકેલો (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = last[-1].location;
  toks->quick_ધકેલો (tok);
  parser->in_omp_decl_attribute = decl;
  gcc_assert (!parser->in_omp_attribute_pragma);
  parser->in_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->in_omp_attribute_pragma->token_vec = toks;
  parser->in_omp_attribute_pragma->save_tokens = parser->tokens;
  parser->in_omp_attribute_pragma->save_tokens_avail = tokens_avail;
  parser->tokens = toks->address ();
  parser->tokens_avail = toks->length ();
  c_parser_pragma (parser, pragma_external, ખાલી, NULL_વૃક્ષ);
  parser->in_omp_decl_attribute = NULL_વૃક્ષ;
  પાછા સાચું;
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

સ્થિર શૂન્ય
c_parser_omp_declare_target (c_parser *parser)
{
  વૃક્ષ clauses = NULL_વૃક્ષ;
  પૂર્ણાંક device_type = 0;
  તાર્કિક indirect = ખોટું;
  તાર્કિક only_device_type_or_indirect = સાચું;
  જો (flag_openmp)
    omp_requires_mask
      = (ગણના omp_requires) (omp_requires_mask | OMP_REQUIRES_TARGET_USED);
  જો (c_parser_next_token_is (parser, CPP_NAME)
      || (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp declare target");
  નહીંતર જો (parser->in_omp_decl_attribute
	   || c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_finish_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_to_pragma_eol (parser);
    }
  નહીંતર
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      તાર્કિક attr_syntax = parser->in_omp_attribute_pragma != ખાલી;
      c_parser_skip_to_pragma_eol (parser);
      c_omp_declare_target_attr attr = { attr_syntax, -1, 0 };
      vec_safe_ધકેલો (current_omp_declare_target_attribute, attr);
      પાછા;
    }
  માટે (વૃક્ષ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_પદાવલિ (c));
    }
  માટે (વૃક્ષ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
	ચાલુ;
      વૃક્ષ t = OMP_CLAUSE_DECL (c), id;
      વૃક્ષ at1 = lookup_attribute ("omp declare target", DECL_ATTRIBUTES (t));
      વૃક્ષ at2 = lookup_attribute ("omp declare target link",
				   DECL_ATTRIBUTES (t));
      only_device_type_or_indirect = ખોટું;
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::swap (at1, at2);
	}
      નહીંતર
	id = get_identifier ("omp declare target");
      જો (at2)
	{
	  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	  નહીંતર જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL
		   || કિંમત_member (get_identifier ("local"), વૃક્ષ_કિંમત (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  નહીંતર
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  ચાલુ;
	}
      જો (!at1)
	{
	  DECL_ATTRIBUTES (t) = વૃક્ષ_cons (id, NULL_વૃક્ષ, DECL_ATTRIBUTES (t));
	  જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    વૃક્ષ_કિંમત (DECL_ATTRIBUTES (t))
	      = વૃક્ષ_cons (NULL_વૃક્ષ, get_identifier ("local"),
			   વૃક્ષ_કિંમત (DECL_ATTRIBUTES (t)));

	  જો (વૃક્ષ_CODE (t) != FUNCTION_DECL && !is_global_var (t))
	    ચાલુ;

	  symtab_ગાંઠ *ગાંઠ = symtab_ગાંઠ::get (t);
	  જો (ગાંઠ != ખાલી)
	    {
	      ગાંઠ->offloadable = 1;
	      જો (ENABLE_OFFLOADING)
		{
		  g->have_offload = સાચું;
		  જો (is_a <varpool_ગાંઠ *> (ગાંઠ)
		      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_LOCAL)
		    vec_safe_ધકેલો (offload_vars, t);
		}
	    }
	}
      નહીંતર
	{
	  તાર્કિક saw_local = કિંમત_member (get_identifier ("local"),
					 વૃક્ષ_કિંમત (at1));
	  જો (saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_TO (c) ? "to" : "enter");
	      ચાલુ;
	    }
	  નહીંતર જો (!saw_local && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      ચાલુ;
	    }
	}
      જો (વૃક્ષ_CODE (t) != FUNCTION_DECL)
	ચાલુ;
      જો ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  વૃક્ષ at3 = lookup_attribute ("omp declare target host",
				       DECL_ATTRIBUTES (t));
	  જો (at3 == NULL_વૃક્ષ)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ATTRIBUTES (t)
		= વૃક્ષ_cons (id, NULL_વૃક્ષ, DECL_ATTRIBUTES (t));
	    }
	}
      જો ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  વૃક્ષ at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ATTRIBUTES (t));
	  જો (at3 == NULL_વૃક્ષ)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ATTRIBUTES (t)
		= વૃક્ષ_cons (id, NULL_વૃક્ષ, DECL_ATTRIBUTES (t));
	    }
	}
      જો (indirect)
	{
	  વૃક્ષ at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ATTRIBUTES (t));
	  જો (at4 == NULL_વૃક્ષ)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ATTRIBUTES (t)
		= વૃક્ષ_cons (id, NULL_વૃક્ષ, DECL_ATTRIBUTES (t));
	    }
	}
    }
  જો ((device_type || indirect) && only_device_type_or_indirect)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  જો (indirect && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
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

સ્થિર શૂન્ય
c_parser_omp_begin (c_parser *parser)
{
  અચલ અક્ષર *p = "";
  c_parser_consume_pragma (parser);
  જો (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
  જો (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      જો (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  તાર્કિક attr_syntax = parser->in_omp_attribute_pragma != ખાલી;
	  વૃક્ષ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_TARGET_CLAUSE_MASK,
					"#pragma omp begin declare target");
	  પૂર્ણાંક device_type = 0;
	  પૂર્ણાંક indirect = 0;
	  માટે (વૃક્ષ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_KIND (c);
	      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INDIRECT)
		indirect |= !integer_zerop (OMP_CLAUSE_INDIRECT_પદાવલિ (c));
	    }
	  c_omp_declare_target_attr attr = { attr_syntax, device_type,
					     indirect };
	  vec_safe_ધકેલો (current_omp_declare_target_attribute, attr);
	}
      નહીંતર જો (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  અચલ અક્ષર *clause = "";
	  matching_parens parens;
	  location_t match_loc = c_parser_peek_token (parser)->location;
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_NAME))
	    {
	      વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
	      clause = IDENTIFIER_POINTER (id);
	    }
	  જો (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_to_pragma_eol (parser);
	      પાછા;
	    }

	  c_parser_consume_token (parser);

	  જો (!parens.require_open (parser))
	    {
	      c_parser_skip_to_pragma_eol (parser, ખોટું);
	      પાછા;
	    }

	  વૃક્ષ ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_વૃક્ષ);
	  જો (ctx != error_mark_ગાંઠ)
	    ctx = omp_check_context_selector (match_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  જો (ctx != error_mark_ગાંઠ
	      && !vec_safe_is_empty (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->last ();
	      વૃક્ષ outer_ctx = a.selector;
	      ctx = omp_merge_context_selectors (match_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  જો (ctx == error_mark_ગાંઠ
	      || !omp_context_selector_matches (ctx, NULL_વૃક્ષ, ખોટું, સાચું))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_to_pragma_eol (parser, ખોટું);
	      c_parser_skip_to_pragma_omp_end_declare_variant (parser);
	      પાછા;
	    }
	  નહીંતર
	    {
	      તાર્કિક attr_syntax = parser->in_omp_attribute_pragma != ખાલી;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_safe_ધકેલો (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_to_pragma_eol (parser);
	}
      નહીંતર
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	}
    }
  નહીંતર જો (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      તાર્કિક attr_syntax = parser->in_omp_attribute_pragma != ખાલી;
      c_parser_omp_assumption_clauses (parser, ખોટું);
      સંરચના c_omp_begin_assumes_data a = { attr_syntax };
      vec_safe_ધકેલો (current_omp_begin_assumes, a);
    }
  નહીંતર
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

સ્થિર શૂન્ય
c_parser_omp_end (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  અચલ અક્ષર *p = "";
  c_parser_consume_pragma (parser);
  જો (c_parser_next_token_is (parser, CPP_NAME))
    p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
  જો (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      જો (c_parser_next_token_is (parser, CPP_NAME))
	p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  તાર્કિક attr_syntax = parser->in_omp_attribute_pragma != ખાલી;
	  c_parser_skip_to_pragma_eol (parser);
	  જો (!vec_safe_length (current_omp_declare_target_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  નહીંતર
	    {
	      c_omp_declare_target_attr
		a = current_omp_declare_target_attribute->કાઢો ();
	      જો (a.attr_syntax != attr_syntax)
		{
		  જો (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  નહીંતર
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      નહીંતર જો (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  તાર્કિક attr_syntax = parser->in_omp_attribute_pragma != ખાલી;
	  c_parser_skip_to_pragma_eol (parser);
	  જો (!vec_safe_length (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  નહીંતર
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->કાઢો ();
	      જો (a.attr_syntax != attr_syntax)
		{
		  જો (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  નહીંતર
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      નહીંતર
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_to_pragma_eol (parser);
	  પાછા;
	}
    }
  નહીંતર જો (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      તાર્કિક attr_syntax = parser->in_omp_attribute_pragma != ખાલી;
      c_parser_skip_to_pragma_eol (parser);
      જો (!vec_safe_length (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      નહીંતર
	{
	  c_omp_begin_assumes_data
	    a = current_omp_begin_assumes->કાઢો ();
	  જો (a.attr_syntax != attr_syntax)
	    {
	      જો (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      નહીંતર
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  નહીંતર
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_to_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

સ્થિર શૂન્ય
c_parser_omp_declare_mapper (c_parser *parser, ગણના pragma_context context)
{
  વૃક્ષ type, mapper_name = NULL_વૃક્ષ, var = NULL_વૃક્ષ, stmt, stmtlist;
  વૃક્ષ maplist = NULL_વૃક્ષ, mapper_id, mapper_decl, t;
  c_token *token;

  જો (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      જાઓ fail;
    }

  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    જાઓ fail;

  token = c_parser_peek_token (parser);

  જો (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      પસંદગી (token->type)
	{
	સ્થિતિ CPP_NAME:
	  mapper_name = token->કિંમત;
	  c_parser_consume_token (parser);
	  તોડો;
	સ્થિતિ CPP_KEYWORD:
	  જો (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_વૃક્ષ;
	      c_parser_consume_token (parser);
	      તોડો;
	    }
	  /* Fallthrough.  */
	મૂળભૂત:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  પાછા;
	}

      જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	જાઓ fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    સંરચના c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, ખાલી, ખાલી);
    જો (type == error_mark_ગાંઠ)
      જાઓ fail;
    જો (!RECORD_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_to_pragma_eol (parser, ખોટું);
	પાછા;
      }
    માટે (વૃક્ષ t = DECL_INITIAL (mapper_decl); t; t = વૃક્ષ_CHAIN (t))
      જો (comptypes (વૃક્ષ_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_POINTER (mapper_id)
		      + કદ ("omp declare mapper ") - 1,
		    type);
	  વૃક્ષ prevmapper = વૃક્ષ_કિંમત (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_SOURCE_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  પાછા;
	}
  }

  token = c_parser_peek_token (parser);
  જો (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->કિંમત, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  નહીંતર
    {
      error_at (token->location, "expected identifier");
      જાઓ fail;
    }

  જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    જાઓ fail;

  ધકેલો_scope ();
  stmtlist = ધકેલો_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t here;
      pragma_omp_clause c_kind;
      here = c_parser_peek_token (parser)->location;
      c_kind = c_parser_omp_clause_name (parser);
      જો (c_kind != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (here, "unexpected clause");
	  જાઓ fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, સાચું);
    }

  જો (maplist == NULL_વૃક્ષ)
    {
      error_at (આગત_location, "missing %<map%> clause");
      જાઓ fail;
    }
  વૃક્ષ list;
  માટે (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      વૃક્ષ dvar = OMP_CLAUSE_DECL (list);
      જ્યારે (!DECL_P (dvar) && વૃક્ષ_OPERAND_LENGTH (dvar))
	dvar = વૃક્ષ_OPERAND (dvar, 0);
      જો (dvar == var)
	તોડો;
    }
  જો (!list)
    error_at (આગત_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_ગાંઠ (OMP_DECLARE_MAPPER);
  વૃક્ષ_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  add_stmt (stmt);

  કાઢો_stmt_list (stmtlist);
  કાઢો_scope ();

  c_parser_skip_to_pragma_eol (parser);

  t = વૃક્ષ_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  પાછા;

 fail:
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

સ્થિર શૂન્ય
c_parser_omp_declare_reduction (c_parser *parser, ગણના pragma_context context)
{
  unsigned પૂર્ણાંક tokens_avail = 0, i;
  c_token *saved_tokens = ખાલી;
  vec<વૃક્ષ> types = vNULL;
  vec<c_token> clauses = vNULL;
  ગણના વૃક્ષ_code reduc_code = ERROR_MARK;
  વૃક્ષ reduc_id = NULL_વૃક્ષ;
  વૃક્ષ type;
  location_t rloc = c_parser_peek_token (parser)->location;

  જો (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      જાઓ fail;
    }

  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    જાઓ fail;

  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_PLUS:
      reduc_code = PLUS_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_MULT:
      reduc_code = MULT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_MINUS:
      reduc_code = MINUS_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_AND:
      reduc_code = BIT_AND_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_XOR:
      reduc_code = BIT_XOR_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_OR:
      reduc_code = BIT_IOR_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_AND_AND:
      reduc_code = TRUTH_ANDIF_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_OR_OR:
      reduc_code = TRUTH_ORIF_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_NAME:
      અચલ અક્ષર *p;
      p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "min") == 0)
	{
	  reduc_code = MIN_પદાવલિ;
	  તોડો;
	}
      જો (strcmp (p, "max") == 0)
	{
	  reduc_code = MAX_પદાવલિ;
	  તોડો;
	}
      reduc_id = c_parser_peek_token (parser)->કિંમત;
      તોડો;
    મૂળભૂત:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      જાઓ fail;
    }

  વૃક્ષ orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_code, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    જાઓ fail;

  જ્યારે (સાચું)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      સંરચના c_type_name *ctype = c_parser_type_name (parser);
      જો (ctype != ખાલી)
	{
	  type = groktypename (ctype, ખાલી, ખાલી);
	  જો (type == error_mark_ગાંઠ)
	    ;
	  નહીંતર જો ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || વૃક્ષ_CODE (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_વૃક્ષ)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  નહીંતર જો (વૃક્ષ_CODE (type) == FUNCTION_TYPE
		   || વૃક્ષ_CODE (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  નહીંતર જો (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  નહીંતર જો (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  નહીંતર
	    {
	      વૃક્ષ t;
	      માટે (t = DECL_INITIAL (reduc_decl); t; t = વૃક્ષ_CHAIN (t))
		જો (comptypes (વૃક્ષ_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_POINTER (reduc_id)
				   + કદ ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_SOURCE_LOCATION (વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    તોડો;
		  }
	      જો (t == NULL_વૃક્ષ)
		types.safe_ધકેલો (type);
	    }
	  જો (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  નહીંતર
	    તોડો;
	}
      નહીંતર
	તોડો;
    }

  જો (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_empty ())
    {
     fail:
      clauses.release ();
      types.release ();
      જ્યારે (સાચું)
	{
	  c_token *token = c_parser_peek_token (parser);
	  જો (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    તોડો;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_to_pragma_eol (parser);
      પાછા;
    }

  જો (types.length () > 1)
    {
      જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  જો (token->type == CPP_EOF)
	    જાઓ fail;
	  clauses.safe_ધકેલો (*token);
	  c_parser_consume_token (parser);
	}
      clauses.safe_ધકેલો (*c_parser_peek_token (parser));
      c_parser_skip_to_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, કદ (eof_token));
      eof_token.type = CPP_EOF;
      clauses.safe_ધકેલો (eof_token);
      clauses.safe_ધકેલો (eof_token);
    }

  પૂર્ણાંક errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_tokens = parser->tokens;
      tokens_avail = parser->tokens_avail;
      જો (!clauses.is_empty ())
	{
	  parser->tokens = clauses.address ();
	  parser->tokens_avail = clauses.length ();
	  parser->in_pragma = સાચું;
	}

      તાર્કિક nested = current_function_decl != NULL_વૃક્ષ;
      જો (nested)
	c_ધકેલો_function_context ();
      વૃક્ષ fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, સાચું);
      ધકેલો_scope ();
      વૃક્ષ stmt = ધકેલો_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      વૃક્ષ omp_out = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_out) = 1;
      DECL_CONTEXT (omp_out) = fndecl;
      pushdecl (omp_out);
      વૃક્ષ omp_in = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_in) = 1;
      DECL_CONTEXT (omp_in) = fndecl;
      pushdecl (omp_in);
      સંરચના c_પદાવલિ combiner = c_parser_expression (parser);
      સંરચના c_પદાવલિ initializer;
      વૃક્ષ omp_priv = NULL_વૃક્ષ, omp_orig = NULL_વૃક્ષ;
      તાર્કિક bad = ખોટું;
      initializer.set_error ();
      જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = સાચું;
      નહીંતર જો (c_parser_next_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      જો (!bad
	  && (c_parser_next_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->કિંમત),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  કાઢો_scope ();
	  ધકેલો_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_ગાંઠ;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = સાચું;
	  નહીંતર જો (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = સાચું;
	    }
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER
				(c_parser_peek_token (parser)->કિંમત),
			   "omp_priv") != 0)
	    {
	      જો (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_kind != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = સાચું;
		}
	      નહીંતર
		initializer = c_parser_postfix_expression (parser);
	      જો (initializer.કિંમત
		  && વૃક્ષ_CODE (initializer.કિંમત) == CALL_પદાવલિ)
		{
		  પૂર્ણાંક j;
		  વૃક્ષ c = initializer.કિંમત;
		  માટે (j = 0; j < call_પદાવલિ_nargs (c); j++)
		    {
		      વૃક્ષ a = CALL_પદાવલિ_ARG (c, j);
		      STRIP_NOPS (a);
		      જો (વૃક્ષ_CODE (a) == ADDR_પદાવલિ
			  && વૃક્ષ_OPERAND (a, 0) == omp_priv)
			તોડો;
		    }
		  જો (j == call_પદાવલિ_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  નહીંતર
	    {
	      c_parser_consume_token (parser);
	      જો (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = સાચું;
	      નહીંતર
		{
		  વૃક્ષ st = ધકેલો_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (લીટી_table, loc);
		  start_init (omp_priv, NULL_વૃક્ષ, ખોટું, ખોટું, &richloc);
		  સંરચના c_પદાવલિ init = c_parser_initializer (parser, omp_priv);
		  finish_init ();
		  finish_decl (omp_priv, loc, init.કિંમત,
		      	       init.original_type, NULL_વૃક્ષ);
		  કાઢો_stmt_list (st);
		}
	    }
	  જો (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = સાચું;
	}

      જો (!bad)
	{
	  c_parser_skip_to_pragma_eol (parser);

	  વૃક્ષ t = વૃક્ષ_cons (type, make_વૃક્ષ_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_SOURCE_LOCATION (omp_out) = rloc;
	  વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 0) = omp_out;
	  વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 1) = omp_in;
	  વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 2) = combiner.કિંમત;
	  walk_વૃક્ષ (&combiner.કિંમત, c_check_omp_declare_reduction_r,
		     &વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 0), ખાલી);
	  જો (omp_priv)
	    {
	      DECL_SOURCE_LOCATION (omp_priv) = rloc;
	      વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 3) = omp_priv;
	      વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 4) = omp_orig;
	      વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 5) = initializer.કિંમત;
	      walk_વૃક્ષ (&initializer.કિંમત, c_check_omp_declare_reduction_r,
			 &વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 3), ખાલી);
	      walk_વૃક્ષ (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &વૃક્ષ_VEC_ELT (વૃક્ષ_કિંમત (t), 3), ખાલી);
	    }
	}

      કાઢો_stmt_list (stmt);
      કાઢો_scope ();
      જો (cfun->language != ખાલી)
	{
	  ggc_free (cfun->language);
	  cfun->language = ખાલી;
	}
      set_cfun (ખાલી);
      current_function_decl = NULL_વૃક્ષ;
      જો (nested)
	c_કાઢો_function_context ();

      જો (!clauses.is_empty ())
	{
	  parser->tokens = saved_tokens;
	  parser->tokens_avail = tokens_avail;
	}
      જો (bad)
	જાઓ fail;
      જો (errs != errorcount)
	તોડો;
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

સ્થિર તાર્કિક
c_parser_omp_declare (c_parser *parser, ગણના pragma_context context)
{
  c_parser_consume_pragma (parser);
  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  પાછા સાચું;
	}
      જો (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  પાછા ખોટું;
	}
      જો (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  પાછા ખોટું;
	}
      જો (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  પાછા ખોટું;
	}
      જો (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_target (parser);
	  પાછા ખોટું;
	}
      જો (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  પાછા સાચું;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_to_pragma_eol (parser);
  પાછા ખોટું;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

સ્થિર શૂન્ય
c_parser_omp_requires (c_parser *parser)
{
  ગણના omp_requires new_req = (ગણના omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      જો (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      જો (c_parser_next_token_is (parser, CPP_NAME))
	{
	  અચલ અક્ષર *p
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  ગણના omp_requires this_req = (ગણના omp_requires) 0;

	  જો (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ADDRESS;
	  નહીંતર જો (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_MEMORY;
	  નહીંતર જો (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  નહીંતર જો (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  નહીંતર જો (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_REVERSE_OFFLOAD;
	  નહીંતર જો (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      જો (parens.require_open (parser))
		{
		  જો (c_parser_next_token_is (parser, CPP_NAME))
		    {
		      વૃક્ષ v = c_parser_peek_token (parser)->કિંમત;
		      p = IDENTIFIER_POINTER (v);

		      જો (!strcmp (p, "seq_cst"))
			this_req
			  = (ગણના omp_requires) OMP_MEMORY_ORDER_SEQ_CST;
		      નહીંતર જો (!strcmp (p, "relaxed"))
			this_req
			  = (ગણના omp_requires) OMP_MEMORY_ORDER_RELAXED;
		      નહીંતર જો (!strcmp (p, "release"))
			this_req
			  = (ગણના omp_requires) OMP_MEMORY_ORDER_RELEASE;
		      નહીંતર જો (!strcmp (p, "acq_rel"))
			this_req
			  = (ગણના omp_requires) OMP_MEMORY_ORDER_ACQ_REL;
		      નહીંતર જો (!strcmp (p, "acquire"))
			this_req
			  = (ગણના omp_requires) OMP_MEMORY_ORDER_ACQUIRE;
		    }
		  જો (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      પસંદગી (c_parser_peek_token (parser)->type)
			{
			સ્થિતિ CPP_EOF:
			સ્થિતિ CPP_PRAGMA_EOL:
			સ્થિતિ CPP_CLOSE_PAREN:
			  તોડો;
			મૂળભૂત:
			  જો (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  તોડો;
			}
		    }
		  નહીંતર
		    c_parser_consume_token (parser);

		  parens.skip_until_found_close (parser);
		  જો (this_req == 0)
		    {
		      c_parser_skip_to_pragma_eol (parser, ખોટું);
		      પાછા;
		    }
		}
	      p = ખાલી;
	    }
	  નહીંતર
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_to_pragma_eol (parser, ખોટું);
	      પાછા;
	    }
	  જો (p)
	    c_parser_consume_token (parser);
	  જો (this_req)
	    {
	      જો ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  જો ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  જો (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_mask & OMP_REQUIRES_TARGET_USED) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      નહીંતર જો ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (ગણના omp_requires) 0;
		}
	      નહીંતર જો ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (ગણના omp_requires)
		       (omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER);
		}
	      નહીંતર જો ((omp_requires_mask
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ORDER_USED) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (ગણના omp_requires) (new_req | this_req);
	      omp_requires_mask
		= (ગણના omp_requires) (omp_requires_mask | this_req);
	      ચાલુ;
	    }
	}
      તોડો;
    }
  c_parser_skip_to_pragma_eol (parser);

  જો (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

સ્થિર વૃક્ષ
c_finish_taskloop_clauses (વૃક્ષ clauses)
{
  વૃક્ષ *pc = &clauses;
  માટે (વૃક્ષ c = clauses; c; c = *pc)
    {
      તાર્કિક remove = ખોટું;
      જો (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
	{
	  વૃક્ષ type = strip_array_types (વૃક્ષ_TYPE (OMP_CLAUSE_DECL (c)));
	  જો (integer_zerop (TYPE_SIZE_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = સાચું;
	    }
	  નહીંતર જો (વૃક્ષ_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = સાચું;
	    }
	}
      જો (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      નહીંતર
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  પાછા clauses;
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
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_અંક_TASKS)	\
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

સ્થિર વૃક્ષ
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       અક્ષર *p_name, omp_clause_mask mask, વૃક્ષ *cclauses,
		       તાર્કિક *if_p)
{
  વૃક્ષ clauses, block, ret;

  strcat (p_name, " taskloop");
  mask |= OMP_TASKLOOP_CLAUSE_MASK;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  જો ((mask & (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_અંક_THREADS)) != 0)
    mask &= ~(OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_IN_REDUCTION);

  જો (c_parser_next_token_is (parser, CPP_NAME))
    {
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);

      જો (strcmp (p, "simd") == 0)
	{
	  વૃક્ષ cclauses_buf[C_OMP_CLAUSE_SPLIT_ગણતરી];
	  જો (cclauses == ખાલી)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  જો (!flag_openmp)  /* flag_openmp_simd  */
	    પાછા c_parser_omp_simd (loc, parser, p_name, mask, cclauses,
				      if_p);
	  block = c_begin_compound_stmt (સાચું);
	  ret = c_parser_omp_simd (loc, parser, p_name, mask, cclauses, if_p);
	  block = c_end_compound_stmt (loc, block, સાચું);
	  જો (ret == ખાલી)
	    પાછા ret;
	  ret = make_ગાંઠ (OMP_TASKLOOP);
	  વૃક્ષ_TYPE (ret) = void_type_ગાંઠ;
	  OMP_FOR_BODY (ret) = block;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_finish_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  SET_પદાવલિ_LOCATION (ret, loc);
	  add_stmt (ret);
	  પાછા ret;
	}
    }
  જો (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_to_pragma_eol (parser, ખોટું);
      પાછા NULL_વૃક્ષ;
    }

  clauses = c_parser_omp_all_clauses (parser, mask, p_name, cclauses == ખાલી);
  જો (cclauses)
    {
      omp_split_clauses (loc, OMP_TASKLOOP, mask, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_SPLIT_TASKLOOP];
    }

  clauses = c_finish_taskloop_clauses (clauses);
  block = c_begin_compound_stmt (સાચું);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, ખાલી, if_p);
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
સ્થિર વૃક્ષ
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  વૃક્ષ sizes = NULL_વૃક્ષ;

  જો (c_parser_next_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  જો (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_POINTER (tok->કિંમત)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      પાછા error_mark_ગાંઠ;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  જો (!parens.require_open (parser))
    પાછા error_mark_ગાંઠ;

  vec<વૃક્ષ, va_gc> *sizes_vec
    = c_parser_પદાવલિ_list (parser, સાચું, સાચું, ખાલી, ખાલી, ખાલી, ખાલી);
  sizes = build_વૃક્ષ_list_vec (sizes_vec);
  release_વૃક્ષ_vector (sizes_vec);

  માટે (વૃક્ષ s = sizes; s; s = વૃક્ષ_CHAIN (s))
    {
      વૃક્ષ પદાવલિ = વૃક્ષ_કિંમત (s);
      જો (પદાવલિ == error_mark_ગાંઠ)
	{
	  parens.skip_until_found_close (parser);
	  પાછા error_mark_ગાંઠ;
	}

      HOST_WIDE_INT n;
      જો (!INTEGRAL_TYPE_P (વૃક્ષ_TYPE (પદાવલિ))
	  || !વૃક્ષ_fits_shwi_p (પદાવલિ)
	  || (n = વૃક્ષ_to_shwi (પદાવલિ)) <= 0
	  || (પૂર્ણાંક) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  વૃક્ષ_કિંમત (s) = integer_one_ગાંઠ;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  વૃક્ષ c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  પાછા c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

સ્થિર વૃક્ષ
c_parser_omp_tile (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_to_pragma_eol (parser);

  જો (!clauses || clauses == error_mark_ગાંઠ)
    પાછા error_mark_ગાંઠ;

  વૃક્ષ block = c_begin_compound_stmt (સાચું);
  વૃક્ષ ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    ખાલી, if_p);
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા ret;
}

#define OMP_UNROLL_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_FULL))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

સ્થિર વૃક્ષ
c_parser_omp_unroll (location_t loc, c_parser *parser, તાર્કિક *if_p)
{
  વૃક્ષ clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_MASK,
					   "#pragma omp unroll", સાચું);

  વૃક્ષ block = c_begin_compound_stmt (સાચું);
  વૃક્ષ ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    ખાલી, if_p);
  block = c_end_compound_stmt (loc, block, સાચું);
  add_stmt (block);

  પાછા ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

સ્થિર શૂન્ય
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

સ્થિર તાર્કિક
c_parser_omp_error (c_parser *parser, ગણના pragma_context context)
{
  પૂર્ણાંક at_compilation = -1;
  પૂર્ણાંક severity_fatal = -1;
  વૃક્ષ message = NULL_વૃક્ષ;
  તાર્કિક bad = ખોટું;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      જો (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      જો (!c_parser_next_token_is (parser, CPP_NAME))
	તોડો;

      અચલ અક્ષર *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      location_t cloc = c_parser_peek_token (parser)->location;
      સ્થિર અચલ અક્ષર *args[] = {
	"execution", "compilation", "warning", "fatal"
      };
      પૂર્ણાંક *v = ખાલી;
      પૂર્ણાંક idx = 0, n = -1;
      વૃક્ષ m = NULL_વૃક્ષ;

      જો (!strcmp (p, "at"))
	v = &at_compilation;
      નહીંતર જો (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      નહીંતર જો (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_to_pragma_eol (parser, ખોટું);
	  પાછા ખોટું;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      જો (parens.require_open (parser))
	{
	  જો (v == ખાલી)
	    {
	      location_t પદાવલિ_loc = c_parser_peek_token (parser)->location;
	      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	      પદાવલિ = convert_lvalue_to_rvalue (પદાવલિ_loc, પદાવલિ, સાચું, સાચું);
	      m = convert (const_string_type_ગાંઠ, પદાવલિ.કિંમત);
	      m = c_fully_fold (m, ખોટું, ખાલી);
	    }
	  નહીંતર
	    {
	      જો (c_parser_next_token_is (parser, CPP_NAME))
		{
		  વૃક્ષ val = c_parser_peek_token (parser)->કિંમત;
		  અચલ અક્ષર *q = IDENTIFIER_POINTER (val);

		  જો (!strcmp (q, args[idx]))
		    n = 0;
		  નહીંતર જો (!strcmp (q, args[idx + 1]))
		    n = 1;
		}
	      જો (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", args[idx], args[idx + 1]);
		  bad = સાચું;
		  પસંદગી (c_parser_peek_token (parser)->type)
		    {
		    સ્થિતિ CPP_EOF:
		    સ્થિતિ CPP_PRAGMA_EOL:
		    સ્થિતિ CPP_CLOSE_PAREN:
		      તોડો;
		    મૂળભૂત:
		      જો (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      તોડો;
		    }
		}
	      નહીંતર
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_found_close (parser);

	  જો (v == ખાલી)
	    {
	      જો (message)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = સાચું;
		}
	      નહીંતર
		message = m;
	    }
	  નહીંતર જો (n != -1)
	    {
	      જો (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = સાચું;
		}
	      નહીંતર
		*v = n;
	    }
	}
      નહીંતર
	bad = સાચું;
    }
  c_parser_skip_to_pragma_eol (parser);
  જો (bad)
    પાછા સાચું;

  જો (at_compilation == -1)
    at_compilation = 1;
  જો (severity_fatal == -1)
    severity_fatal = 1;
  જો (!at_compilation)
    {
      જો (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  પાછા સાચું;
	}
      જો (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->in_intervening_code)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = સાચું;
	  પાછા સાચું;
	}
      વૃક્ષ fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_IN_GOMP_ERROR
						: BUILT_IN_GOMP_WARNING);
      જો (!message)
	message = build_zero_cst (const_string_type_ગાંઠ);
      વૃક્ષ stmt = build_call_પદાવલિ_loc (loc, fndecl, 2, message,
				       build_all_ones_cst (size_type_ગાંઠ));
      add_stmt (stmt);
      પાછા સાચું;
    }
  અચલ અક્ષર *સંદેશ = ખાલી;
  જો (message)
    {
      સંદેશ = c_getstr (message);
      જો (સંદેશ == ખાલી)
	સંદેશ = _("<message unknown at compile time>");
    }
  અચલ ગણના diagnostics::kind diag_kind = (severity_fatal
					    ? diagnostics::kind::error
					    : diagnostics::kind::warning);
  જો (સંદેશ)
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered: %s", સંદેશ);
  નહીંતર
    emit_diagnostic (diag_kind, loc, 0,
		     "%<pragma omp error%> encountered");
  પાછા ખોટું;
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

સ્થિર શૂન્ય
c_parser_omp_assumption_clauses (c_parser *parser, તાર્કિક is_assume)
{
  તાર્કિક no_openmp = ખોટું;
  તાર્કિક no_openmp_constructs = ખોટું;
  તાર્કિક no_openmp_routines = ખોટું;
  તાર્કિક no_parallelism = ખોટું;
  bitmap_head absent_head, contains_head;

  bitmap_obstack_initialize (ખાલી);
  bitmap_initialize (&absent_head, &bitmap_default_obstack);
  bitmap_initialize (&contains_head, &bitmap_default_obstack);

  જો (c_parser_next_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      જો (c_parser_next_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      જો (!c_parser_next_token_is (parser, CPP_NAME))
	તોડો;

      અચલ અક્ષર *p
	= IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      location_t cloc = c_parser_peek_token (parser)->location;

      જો (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  જો (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = સાચું;
	}
      નહીંતર જો (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  જો (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = સાચું;
	}
      નહીંતર જો (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  જો (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = સાચું;
	}
      નહીંતર જો (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  જો (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = સાચું;
	}
      નહીંતર જો (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  જો (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_પદાવલિ પદાવલિ = c_parser_પદાવલિ_no_commas (parser, ખાલી);
	      વૃક્ષ t = convert_lvalue_to_rvalue (eloc, પદાવલિ, સાચું, સાચું).કિંમત;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, ખોટું, ખાલી);
	      જો (is_assume && t != error_mark_ગાંઠ)
		{
		  વૃક્ષ fn = build_call_પદાવલિ_internal_loc (eloc, IFN_ASSUME,
							  void_type_ગાંઠ, 1,
							  t);
		  add_stmt (fn);
		}
	      parens.skip_until_found_close (parser);
	    }
	}
      નહીંતર જો (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  જો (parens.require_open (parser))
	    {
	      કરો
		{
		  અચલ અક્ષર *directive[3] = {};
		  પૂર્ણાંક i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  માટે (i = 0; i < 3; i++)
		    {
		      વૃક્ષ id;
		      જો (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->કિંમત;
		      નહીંતર જો (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  ગણના rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      નહીંતર
			તોડો;
		      directive[i] = IDENTIFIER_POINTER (id);
		    }
		  જો (i == 0)
		    error_at (dloc, "expected directive name");
		  નહીંતર
		    {
		      અચલ સંરચના c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      જો (dir
			  && dir->id != PRAGMA_OMP_END
			  && (dir->kind == C_OMP_DIR_DECLARATIVE
			      || dir->kind == C_OMP_DIR_INFORMATIONAL
			      || dir->kind == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      નહીંતર જો (dir == ખાલી
			       || dir->id == PRAGMA_OMP_END
			       || (!dir->second && directive[1])
			       || (!dir->third && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      નહીંતર
			{
			  પૂર્ણાંક id = dir - c_omp_directives;
			  જો (bitmap_bit_p (p[0] == 'a' ? &contains_head
							: &absent_head, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  નહીંતર જો (!bitmap_set_bit (p[0] == 'a'
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
		      માટે (; i; --i)
			c_parser_consume_token (parser);
		    }
		  જો (c_parser_next_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  નહીંતર
		    તોડો;
		}
	      જ્યારે (1);
	      parens.skip_until_found_close (parser);
	    }
	}
      નહીંતર જો (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_balanced_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      નહીંતર
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  તોડો;
	}
    }
  c_parser_skip_to_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

સ્થિર શૂન્ય
c_parser_omp_assume (c_parser *parser, તાર્કિક *if_p)
{
  c_parser_omp_assumption_clauses (parser, સાચું);
  add_stmt (c_parser_omp_structured_block (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

સ્થિર શૂન્ય
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, ખોટું);
}

/* Helper function for c_parser_omp_metadirective.  */

સ્થિર શૂન્ય
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &tokens,
			    vec<વૃક્ષ> &labels)
{
  પૂર્ણાંક nesting_depth = 0;
  પૂર્ણાંક bracket_depth = 0;
  તાર્કિક ignore_label = ખોટું;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  જ્યારે (1)
    {
      c_token *token = c_parser_peek_token (parser);
      તાર્કિક stop = ખોટું;

      જો (c_parser_next_token_is_keyword (parser, RID_CASE))
	ignore_label = સાચું;

      પસંદગી (token->type)
	{
	સ્થિતિ CPP_EOF:
	  તોડો;
	સ્થિતિ CPP_NAME:
	  જો (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.safe_ધકેલો (token->કિંમત);
	  જાઓ add;
	સ્થિતિ CPP_OPEN_BRACE:
	  ++nesting_depth;
	  જાઓ add;
	સ્થિતિ CPP_CLOSE_BRACE:
	  જો (--nesting_depth == 0 && bracket_depth == 0)
	    stop = સાચું;
	  જાઓ add;
	સ્થિતિ CPP_OPEN_PAREN:
	  ++bracket_depth;
	  જાઓ add;
	સ્થિતિ CPP_CLOSE_PAREN:
	  --bracket_depth;
	  જાઓ add;
	સ્થિતિ CPP_COLON:
	  ignore_label = ખોટું;
	  જાઓ add;
	સ્થિતિ CPP_SEMICOLON:
	  જો (nesting_depth == 0 && bracket_depth == 0)
	    stop = સાચું;
	  જાઓ add;
	મૂળભૂત:
	add:
	  tokens.safe_ધકેલો (*token);
	  જો (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  નહીંતર જો (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_to_pragma_eol (parser);
	  નહીંતર
	    c_parser_consume_token (parser);
	  જો (stop)
	    તોડો;
	  ચાલુ;
	}
      તોડો;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

સ્થિર શૂન્ય
c_parser_omp_metadirective (c_parser *parser, તાર્કિક *if_p)
{
  સ્થિર unsigned પૂર્ણાંક metadirective_region_ગણતરી = 0;

  વૃક્ષ ret;
  auto_vec<c_token> directive_tokens;
  auto_vec<c_token> body_tokens;
  auto_vec<વૃક્ષ> body_labels;
  auto_vec<અચલ સંરચના c_omp_directive *> directives;
  auto_vec<વૃક્ષ> ctxs;
  vec<સંરચના omp_variant> candidates;
  તાર્કિક default_seen = ખોટું;
  પૂર્ણાંક directive_token_idx = 0;
  વૃક્ષ standalone_body = NULL_વૃક્ષ;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  તાર્કિક requires_body = ખોટું;

  ret = make_ગાંઠ (OMP_METADIRECTIVE);
  SET_પદાવલિ_LOCATION (ret, pragma_loc);
  વૃક્ષ_TYPE (ret) = void_type_ગાંઠ;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_વૃક્ષ;

  c_parser_consume_pragma (parser);
  જ્યારે (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      જો (c_parser_next_token_is_not (parser, CPP_NAME)
	  && c_parser_next_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  જાઓ error;
	}

      location_t match_loc = c_parser_peek_token (parser)->location;
      અચલ અક્ષર *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      જો (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.add_fixit_replace (match_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      તાર્કિક default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      જો (default_p)
	{
	  જો (default_seen)
	    {
	      error_at (match_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      જાઓ error;
	    }
	  default_seen = સાચું;
	}
      નહીંતર જો (default_seen)
	{
	  error_at (match_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  જાઓ error;
	}
      જો (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (match_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  જાઓ error;
	}

      matching_parens parens;
      વૃક્ષ ctx = NULL_વૃક્ષ;
      તાર્કિક skip = ખોટું;

      જો (!parens.require_open (parser))
	જાઓ error;

      જો (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_વૃક્ષ);
	  જો (ctx == error_mark_ગાંઠ)
	    જાઓ error;
	  ctx = omp_check_context_selector (match_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  જો (ctx == error_mark_ગાંઠ)
	    જાઓ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_વૃક્ષ, ખોટું) == 0);

	  જો (c_parser_next_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      જાઓ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      અચલ અક્ષર *directive[3] = {};
      પૂર્ણાંક i;
      માટે (i = 0; i < 3; i++)
	{
	  વૃક્ષ id;
	  જો (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      જો (i == 0)
		directive[i++] = "nothing";
	      તોડો;
	    }
	  નહીંતર જો (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->કિંમત;
	  નહીંતર જો (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      ગણના rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  નહીંતર
	    તોડો;

	  directive[i] = IDENTIFIER_POINTER (id);
	}
      જો (i == 0)
	{
	  error_at (loc, "expected directive name");
	  જાઓ error;
	}

      અચલ સંરચના c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      જો (omp_directive == ખાલી)
	{
	  માટે (પૂર્ણાંક j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  જાઓ error;
	}
      નહીંતર
	{
	  પૂર્ણાંક token_ગણતરી = 0;
	  જો (omp_directive->first) token_ગણતરી++;
	  જો (omp_directive->second) token_ગણતરી++;
	  જો (omp_directive->third) token_ગણતરી++;
	  માટે (પૂર્ણાંક j = 0; j < token_ગણતરી; j++)
	    c_parser_consume_token (parser);
	}
      જો (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  જાઓ error;
	}
      જો (omp_directive->kind == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  જાઓ error;
	}
      જો (omp_directive->kind == C_OMP_DIR_CONSTRUCT)
	requires_body = સાચું;

      જો (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_kind = (ગણના pragma_kind) omp_directive->id;

	  directives.safe_ધકેલો (omp_directive);
	  directive_tokens.safe_ધકેલો (pragma_token);
	  ctxs.safe_ધકેલો (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      પૂર્ણાંક nesting_depth = 0;
      જ્યારે (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  પસંદગી (token->type)
	    {
	    સ્થિતિ CPP_EOF:
	    સ્થિતિ CPP_PRAGMA_EOL:
	      તોડો;
	    સ્થિતિ CPP_OPEN_PAREN:
	      ++nesting_depth;
	      જાઓ add;
	    સ્થિતિ CPP_CLOSE_PAREN:
	      જો (nesting_depth-- == 0)
		{
		  c_parser_consume_token (parser);
		  તોડો;
		}
	      જાઓ add;
	    મૂળભૂત:
	    add:
	      જો (!skip)
		directive_tokens.safe_ધકેલો (*token);
	      c_parser_consume_token (parser);
	      ચાલુ;
	    }
	  તોડો;
	}

      જો (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, કદ (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_tokens.safe_ધકેલો (eol_token);
	}
    }
  c_parser_skip_to_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  જો (ctxs.length () == 1)
    {
      વૃક્ષ ctx = ctxs[0];
      જો (ctx == NULL_વૃક્ષ
	  || (omp_context_selector_matches (ctx, NULL_વૃક્ષ, ખોટું) == 1
	      && directive_tokens[0].pragma_kind == PRAGMA_OMP_NOTHING))
	પાછા;
    }

  જો (!default_seen)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      અચલ સંરચના c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", ખાલી, ખાલી);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_kind = PRAGMA_OMP_NOTHING;

      directives.safe_ધકેલો (omp_directive);
      directive_tokens.safe_ધકેલો (pragma_token);
      ctxs.safe_ધકેલો (NULL_વૃક્ષ);

      c_token eol_token;
      memset (&eol_token, 0, કદ (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_tokens.safe_ધકેલો (eol_token);
    }

  જો (requires_body)
    analyze_metadirective_body (parser, body_tokens, body_labels);

  /* Process each candidate directive.  */
  unsigned i;
  વૃક્ષ ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> tokens;

      /* Add the directive tokens.  */
      કરો
	tokens.safe_ધકેલો (directive_tokens [directive_token_idx++]);
      જ્યારે (tokens.last ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_tokens.is_empty ());
      માટે (unsigned j = 0; j < body_tokens.length (); j++)
	tokens.safe_ધકેલો (body_tokens[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, કદ (eof_token));
      eof_token.type = CPP_EOF;
      tokens.safe_ધકેલો (eof_token);
      tokens.safe_ધકેલો (eof_token);

      unsigned પૂર્ણાંક old_tokens_avail = parser->tokens_avail;
      c_token *old_tokens = parser->tokens;
      સંરચના omp_attribute_pragma_state *old_in_omp_attribute_pragma
	= parser->in_omp_attribute_pragma;
      સંરચના omp_metadirective_parse_data *old_state
	= parser->omp_metadirective_state;

      સંરચના omp_metadirective_parse_data new_state;
      new_state.body_labels = &body_labels;
      new_state.region_અંક = ++metadirective_region_ગણતરી;

      parser->tokens = tokens.address ();
      parser->tokens_avail = tokens.length ();
      parser->in_omp_attribute_pragma = ખાલી;
      parser->omp_metadirective_state = &new_state;

      પૂર્ણાંક prev_errorcount = errorcount;
      વૃક્ષ directive = c_begin_compound_stmt (સાચું);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_વૃક્ષ);
      directive = c_end_compound_stmt (pragma_loc, directive, સાચું);
      તાર્કિક standalone_p
	= directives[i]->kind == C_OMP_DIR_STANDALONE
	  || directives[i]->kind == C_OMP_DIR_UTILITY;
      જો (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  જો (standalone_body == NULL_વૃક્ષ)
	    {
	      standalone_body = ધકેલો_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = કાઢો_stmt_list (standalone_body);
	    }
	  નહીંતર
	    c_parser_skip_to_end_of_block_or_statement (parser, સાચું);
	}

      વૃક્ષ body = standalone_p ? standalone_body : NULL_વૃક્ષ;
      વૃક્ષ variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      જો (errorcount == prev_errorcount)
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
  જો (!candidates.is_empty ())
    ret = c_omp_expand_variant_construct (candidates);

  add_stmt (ret);
  પાછા;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  જો (parser->in_pragma)
    c_parser_skip_to_pragma_eol (parser, ખોટું);
}

/* Main entry point to parsing most OpenMP pragmas.  */

સ્થિર શૂન્ય
c_parser_omp_construct (c_parser *parser, તાર્કિક *if_p)
{
  ગણના pragma_kind p_kind;
  location_t loc;
  વૃક્ષ stmt;
  અક્ષર p_name[કદ "#pragma omp teams distribute parallel for simd"];
  omp_clause_mask mask (0);

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  પસંદગી (p_kind)
    {
    સ્થિતિ PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, સાચું);
      પાછા;
    સ્થિતિ PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      તોડો;
    સ્થિતિ PRAGMA_OACC_DATA:
      stmt = c_parser_oacc_data (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OACC_HOST_DATA:
      stmt = c_parser_oacc_host_data (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OACC_KERNELS:
    સ્થિતિ PRAGMA_OACC_PARALLEL:
    સ્થિતિ PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_kind, p_name, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      તોડો;
    સ્થિતિ PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, ખોટું);
      પાછા;
    સ્થિતિ PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, mask, ખાલી, if_p,
				  UNKNOWN_LOCATION);
      તોડો;
    સ્થિતિ PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, mask, ખાલી);
      તોડો;
    સ્થિતિ PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, mask, ખાલી, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      પાછા;
    સ્થિતિ PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      તોડો;
    સ્થિતિ PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      તોડો;
    મૂળભૂત:
      gcc_unreachable ();
    }

  જો (stmt && stmt != error_mark_ગાંઠ)
    gcc_assert (પદાવલિ_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#define OMP_GROUPPRIVATE_CLAUSE_MASK					\
	( (OMP_CLAUSE_MASK_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

સ્થિર શૂન્ય
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  વૃક્ષ vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ખાલી);
  વૃક્ષ clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_MASK,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (શૂન્ય) vars;
  (શૂન્ય) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

સ્થિર શૂન્ય
c_parser_omp_threadprivate (c_parser *parser)
{
  વૃક્ષ vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ખાલી);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  માટે (t = vars; t; t = વૃક્ષ_CHAIN (t))
    {
      વૃક્ષ v = વૃક્ષ_PURPOSE (t);
      loc = પદાવલિ_LOCATION (વૃક્ષ_કિંમત (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      જો (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      નહીંતર જો (વૃક્ષ_USED (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      નહીંતર જો (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      નહીંતર જો (વૃક્ષ_TYPE (v) == error_mark_ગાંઠ)
	;
      નહીંતર જો (! COMPLETE_TYPE_P (વૃક્ષ_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      નહીંતર
	{
	  જો (! DECL_THREAD_LOCAL_P (v))
	    {
	      set_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      જો (DECL_RTL_SET_P (v))
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

સ્થિર વૃક્ષ
c_parser_transaction_attributes (c_parser *parser)
{
  જો (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    પાછા c_parser_gnu_attributes (parser);

  જો (!c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    પાછા NULL_વૃક્ષ;
  પાછા c_parser_std_attribute_specifier (parser, સાચું);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

સ્થિર વૃક્ષ
c_parser_transaction (c_parser *parser, ગણના rid keyword)
{
  unsigned પૂર્ણાંક old_in = parser->in_transaction;
  unsigned પૂર્ણાંક this_in = 1, new_in;
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  જો (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  નહીંતર
    {
      attrs = c_parser_transaction_attributes (parser);
      જો (attrs)
	this_in |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_in = this_in | (old_in & TM_STMT_ATTR_OUTER);

  parser->in_transaction = new_in;
  stmt = c_parser_compound_statement (parser);
  parser->in_transaction = old_in;

  જો (flag_tm)
    stmt = c_finish_transaction (loc, stmt, this_in);
  નહીંતર
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  પાછા stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

સ્થિર સંરચના c_પદાવલિ
c_parser_transaction_expression (c_parser *parser, ગણના rid keyword)
{
  સંરચના c_પદાવલિ ret;
  unsigned પૂર્ણાંક old_in = parser->in_transaction;
  unsigned પૂર્ણાંક this_in = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_next_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  જો (keyword == RID_TRANSACTION_RELAXED)
    this_in |= TM_STMT_ATTR_RELAXED;
  નહીંતર
    {
      attrs = c_parser_transaction_attributes (parser);
      જો (attrs)
	this_in |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->in_transaction = this_in;
  matching_parens parens;
  જો (parens.require_open (parser))
    {
      વૃક્ષ પદાવલિ = c_parser_expression (parser).કિંમત;
      ret.original_type = વૃક્ષ_TYPE (પદાવલિ);
      ret.કિંમત = build1 (TRANSACTION_પદાવલિ, ret.original_type, પદાવલિ);
      જો (this_in & TM_STMT_ATTR_RELAXED)
	TRANSACTION_પદાવલિ_RELAXED (ret.કિંમત) = 1;
      SET_પદાવલિ_LOCATION (ret.કિંમત, loc);
      ret.original_code = TRANSACTION_પદાવલિ;
      ret.m_decimal = 0;
      જો (!parens.require_close (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, ખાલી);
	  જાઓ error;
	}
    }
  નહીંતર
    {
     error:
      ret.set_error ();
      ret.original_code = ERROR_MARK;
      ret.original_type = ખાલી;
    }
  parser->in_transaction = old_in;

  જો (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  set_c_પદાવલિ_source_range (&ret, loc, loc);

  પાછા ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

સ્થિર વૃક્ષ
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  વૃક્ષ attrs;
  તાર્કિક is_outer = ખોટું;

  gcc_assert (c_parser_next_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_attributes (parser);
  જો (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  જો (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      જાઓ ret_error;
    }
  નહીંતર જો (parser->in_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      જાઓ ret_error;
    }
  નહીંતર જો (is_outer)
    {
      જો ((parser->in_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  જાઓ ret_error;
	}
    }
  નહીંતર જો (parser->in_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      જાઓ ret_error;
    }

  પાછા add_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  પાછા build1 (NOP_પદાવલિ, void_type_ગાંઠ, error_mark_ગાંઠ);
}

/* Parse a single source file.  */

શૂન્ય
c_parse_file (શૂન્ય)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, કદ tparser);
  tparser.translate_strings_p = સાચું;
  tparser.tokens = &tparser.tokens_buf[0];
  the_parser = &tparser;

  જો (c_parser_peek_token (&tparser)->pragma_kind == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  નહીંતર
    c_common_no_more_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  જો (tparser.tokens == &tparser.tokens_buf[0])
    the_parser->tokens = &the_parser->tokens_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  જો (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = ખાલી;
}

શૂન્ય
c_init_preprocess (શૂન્ય)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, કદ (c_parser));
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
c_parser_parse_rtl_body (c_parser *parser, અક્ષર *start_with_pass)
{
  જો (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      મુક્ત (start_with_pass);
      પાછા c_parser_peek_token (parser)->location;
    }

  location_t start_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  પૂર્ણાંક અંક_open_braces = 1;
  જ્યારે (1)
    {
      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_OPEN_BRACE:
	  અંક_open_braces++;
	  તોડો;
	સ્થિતિ CPP_CLOSE_BRACE:
	  જો (--અંક_open_braces == 0)
	    જાઓ found_closing_brace;
	  તોડો;
	સ્થિતિ CPP_EOF:
	  error_at (start_loc, "no closing brace");
	  મુક્ત (start_with_pass);
	  પાછા c_parser_peek_token (parser)->location;
	મૂળભૂત:
	  તોડો;
	}
      c_parser_consume_token (parser);
    }

 found_closing_brace:
  /* At the closing brace; record its location.  */
  location_t end_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  જો (!read_rtl_function_body_from_file_range (start_loc, end_loc))
    {
      મુક્ત (start_with_pass);
      પાછા end_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  run_rtl_passes (start_with_pass);
  પાછા end_loc;
}

#અન્તર્ભાવ "gt-c-c-parser.h"
