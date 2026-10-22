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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INCLUDE_STRING
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "target.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "function.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timevar.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stringpool.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cgraph.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attribs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stor-layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "varasm.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "trans-mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-pragma.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-lang.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-objc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plugin.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "omp-general.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "omp-offload.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "builtins.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gomp-constants.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-indentation.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple-expr.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "context.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gcc-rich-location.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-parser.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple-parser.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "read-rtl-function.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "run-rtl-passes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/name-hint.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-iterator.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-pretty-print.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "memmodel.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/known-headers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bitmap.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "analyzer/analyzer-language.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "toplev.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "asan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-ubsan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gcc-urlifier.h"

/* We need to walk over decls with incomplete struct/union/enum types
   after parsing the whole translation unit.
   In finish_decl(), if the decl is static, has incomplete
   struct/union/enum type, it is appended to incomplete_record_decls.
   In c_parser_translation_unit(), we iterate over incomplete_record_decls
   and report error if any of the decls are still incomplete.  */

vec<ਰੁੱਖ> incomplete_ਰਿਕਾਰਡ_decls;

ਖਾਲੀ
ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (c_ਵਿਅੰਜਕ *ਵਿਅੰਜਕ,
			 location_t ਸ਼ੁਰੂ, location_t ਅੰਤ)
{
  ਵਿਅੰਜਕ->src_range.m_ਸ਼ੁਰੂ = ਸ਼ੁਰੂ;
  ਵਿਅੰਜਕ->src_range.m_ਅੰਤ = ਅੰਤ;
  ਜੇ (ਵਿਅੰਜਕ->ਮੁੱਲ)
    ਸੈੱਟ_ਸਰੋਤ_range (ਵਿਅੰਜਕ->ਮੁੱਲ, ਸ਼ੁਰੂ, ਅੰਤ);
}

ਖਾਲੀ
ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (c_ਵਿਅੰਜਕ *ਵਿਅੰਜਕ,
			 ਸਰੋਤ_range src_range)
{
  ਵਿਅੰਜਕ->src_range = src_range;
  ਜੇ (ਵਿਅੰਜਕ->ਮੁੱਲ)
    ਸੈੱਟ_ਸਰੋਤ_range (ਵਿਅੰਜਕ->ਮੁੱਲ, src_range);
}


/* Initialization routine for this file.  */

ਖਾਲੀ
c_parse_init (ਖਾਲੀ)
{
  /* The only initialization required is of the reserved word
     identifiers.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
  ਰੁੱਖ id;
  ਪੂਰਨ ਨਕਾਬ = 0;

  /* Make sure RID_MAX hasn't grown past the 8 bits used to hold the keyword in
     the c_token structure.  */
  gcc_assert (RID_MAX <= 255);

  ਨਕਾਬ |= D_CXXONLY;
  ਜੇ (!flag_isoc99)
    ਨਕਾਬ |= D_C99;
  ਜੇ (!flag_isoc23)
    ਨਕਾਬ |= D_C23;
  ਜੇ (flag_no_asm)
    {
      ਨਕਾਬ |= D_ASM | D_EXT;
      ਜੇ (!flag_isoc99)
	ਨਕਾਬ |= D_EXT89;
      ਜੇ (!flag_isoc23)
	ਨਕਾਬ |= D_EXT11;
    }
  ਜੇ (!c_dialect_objc ())
    ਨਕਾਬ |= D_OBJC | D_CXX_OBJC;

  ridpointers = ggc_cleared_vec_alloc<ਰੁੱਖ> ((ਪੂਰਨ) RID_MAX);
  ਲਈ (i = 0; i < ਅੰਕ_c_common_reswords; i++)
    {
      /* If a keyword is disabled, do not enter it into the table
	 and so create a canonical spelling that isn't a keyword.  */
      ਜੇ (c_common_reswords[i].disable & ਨਕਾਬ)
	{
	  ਜੇ (warn_cxx_compat
	      && (c_common_reswords[i].disable & D_CXXWARN))
	    {
	      id = get_identifier (c_common_reswords[i].ਸ਼ਬਦ);
	      C_ਸੈੱਟ_RID_ਕੋਡ (id, RID_CXX_COMPAT_WARN);
	      C_IS_RESERVED_ਸ਼ਬਦ (id) = 1;
	    }
	  ਜਾਰੀ;
	}

      id = get_identifier (c_common_reswords[i].ਸ਼ਬਦ);
      C_ਸੈੱਟ_RID_ਕੋਡ (id, c_common_reswords[i].rid);
      C_IS_RESERVED_ਸ਼ਬਦ (id) = 1;
      ridpointers [(ਪੂਰਨ) c_common_reswords[i].rid] = id;
    }

  ਲਈ (i = 0; i < ਅੰਕ_INT_N_ENTS; i++)
    {
      /* We always create the symbols but they aren't always supported.  */
      ਅੱਖਰ name[50];
      sprintf (name, "__int%d", int_n_ਅੰਕੜੇ[i].bitsize);
      id = get_identifier (name);
      C_ਸੈੱਟ_RID_ਕੋਡ (id, RID_ਪਹਿਲਾ_INT_N + i);
      C_IS_RESERVED_ਸ਼ਬਦ (id) = 1;

      sprintf (name, "__int%d__", int_n_ਅੰਕੜੇ[i].bitsize);
      id = get_identifier (name);
      C_ਸੈੱਟ_RID_ਕੋਡ (id, RID_ਪਹਿਲਾ_INT_N + i);
      C_IS_RESERVED_ਸ਼ਬਦ (id) = 1;
    }

  ਜੇ (flag_openmp)
    {
      id = get_identifier ("omp_all_memory");
      C_ਸੈੱਟ_RID_ਕੋਡ (id, RID_OMP_ALL_ਸਮ੍ਰਿਤੀ);
      C_IS_RESERVED_ਸ਼ਬਦ (id) = 1;
      ridpointers [RID_OMP_ALL_ਸਮ੍ਰਿਤੀ] = id;
    }
}

/* A parser structure recording information about the state and
   context of parsing.  Includes lexer information with up to two
   tokens of look-ahead; more are not needed for C.  */
ਬਣਤਰ GTY(()) c_parser {
  /* The look-ahead tokens.  */
  c_token * GTY((skip)) ਟੋਕਨ;
  /* Buffer for look-ahead tokens.  */
  c_token ਟੋਕਨ_buf[4];
  /* How many look-ahead tokens are available (0 - 4, or
     more if parsing from pre-lexed tokens).  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਟੋਕਨ_avail;
  /* Raw look-ahead tokens, used only for checking in Objective-C
     whether '[[' starts attributes.  */
  vec<c_token, va_gc> *raw_ਟੋਕਨ;
  /* The number of raw look-ahead tokens that have since been fully
     lexed.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ raw_ਟੋਕਨ_ਵਰਤਿਆ;
  /* True if a syntax error is being recovered from; false otherwise.
     c_parser_error sets this flag.  It should clear this flag when
     enough tokens have been consumed to recover from the error.  */
  ਤਾਰਕਿਕ error : 1;
  /* True if we're processing a pragma, and shouldn't automatically
     consume CPP_PRAGMA_EOL.  */
  ਤਾਰਕਿਕ ਵਿੱਚ_pragma : 1;
  /* True if we're parsing the outermost block of an if statement.  */
  ਤਾਰਕਿਕ ਵਿੱਚ_if_ਖੰਡ : 1;
  /* True if we want to lex a translated, joined string (for an
     initial #pragma pch_preprocess).  Otherwise the parser is
     responsible for concatenating strings and translating to the
     execution character set as needed.  */
  ਤਾਰਕਿਕ lex_joined_string : 1;
  /* True if, when the parser is concatenating string literals, it
     should translate them to the execution character set (false
     inside attributes).  */
  ਤਾਰਕਿਕ translate_ਲੜੀਆਂ_p : 1;

  /* Objective-C specific parser/lexer information.  */

  /* True if we are in a context where the Objective-C "PQ" keywords
     are considered keywords.  */
  ਤਾਰਕਿਕ objc_pq_context : 1;
  /* True if we are parsing a (potential) Objective-C foreach
     statement.  This is set to true after we parsed 'for (' and while
     we wait for 'in' or ';' to decide if it's a standard C for loop or an
     Objective-C foreach loop.  */
  ਤਾਰਕਿਕ objc_could_be_foreach_context : 1;
  /* The following flag is needed to contextualize Objective-C lexical
     analysis.  In some cases (e.g., 'int NSObject;'), it is
     undesirable to bind an identifier to an Objective-C class, even
     if a class with that name exists.  */
  ਤਾਰਕਿਕ objc_need_raw_identifier : 1;
  /* Nonzero if we're processing a __transaction statement.  The value
     is 1 | TM_STMT_ATTR_*.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਵਿੱਚ_transaction : 4;
  /* True if we are in a context where the Objective-C "Property attribute"
     keywords are valid.  */
  ਤਾਰਕਿਕ objc_property_attr_context : 1;

  /* Whether we have just seen/constructed a string-literal.  Set when
     returning a string-literal from c_parser_string_literal.  Reset
     in consume_token.  Useful when we get a parse error and see an
     unknown token, which could have been a string-literal constant
     macro.  */
  ਤਾਰਕਿਕ ਵੇਖਿਆ_string_literal : 1;

  /* TRUE if omp::directive, omp::decl or omp::sequence attributes may not
     appear.  */
  ਤਾਰਕਿਕ omp_attrs_forbidden_p : 1;

  /* Location of the last consumed token.  */
  location_t ਆਖਰੀ_token_location;

  /* Holds state for parsing collapsed OMP_FOR loops.  Managed by
     c_parser_omp_for_loop.  */
  ਬਣਤਰ omp_for_parse_ਅੰਕੜੇ * GTY((skip)) omp_for_parse_state;

  /* If we're in the context of OpenMP directives written as C23
     attributes turned into pragma, the tokens field is temporarily
     redirected.  This holds data needed to restore state afterwards.
     It's NULL otherwise.  */
  ਬਣਤਰ omp_attribute_pragma_state *ਵਿੱਚ_omp_attribute_pragma;

  /* Set for omp::decl attribute parsing to the decl to which it
     appertains.  */
  ਰੁੱਖ ਵਿੱਚ_omp_decl_attribute;

  /* Non-null only when parsing the body of an OpenMP metadirective.
     Managed by c_parser_omp_metadirective.  */
  ਬਣਤਰ omp_metadirective_parse_ਅੰਕੜੇ * GTY((skip))
    omp_metadirective_state;
};

/* Holds data needed to restore the token stream to its previous state
   after parsing an OpenMP attribute-syntax pragma.  */
ਬਣਤਰ GTY(()) omp_attribute_pragma_state
{
  vec<c_token, va_gc> *token_vec;
  c_token * GTY((skip)) save_ਟੋਕਨ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ save_ਟੋਕਨ_avail;
};

/* Holds data for deferred lookup of base functions for OpenMP
   "begin declare variant", which are permitted to be declared after
   the variant.  */
ਬਣਤਰ GTY(()) omp_begin_declare_variant_map_ਇੰਦਰਾਜ {
  ਰੁੱਖ variant;		/* The variant decl.  */
  ਰੁੱਖ id;		/* Name of base function.  */
  ਰੁੱਖ ctx;		/* The context selector associated with the variant.  */
};
vec<omp_begin_declare_variant_map_ਇੰਦਰਾਜ, va_gc> *omp_begin_declare_variant_map;

ਸਥਿਰ ਰੁੱਖ omp_ਸ਼ੁਰੂ_variant_function (c_declarator *, ਰੁੱਖ);
ਸਥਿਰ ਖਾਲੀ omp_ਅੰਤ_variant_function (ਰੁੱਖ, ਰੁੱਖ, ਰੁੱਖ);

/* Return a pointer to the Nth token in PARSERs tokens_buf.  */

c_token *
c_parser_ਟੋਕਨ_buf (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ n)
{
  ਵਾਪਸ &parser->ਟੋਕਨ_buf[n];
}

/* Return the error state of PARSER.  */

ਤਾਰਕਿਕ
c_parser_error (c_parser *parser)
{
  ਵਾਪਸ parser->error;
}

/* Set the error state of PARSER to ERR.  */

ਖਾਲੀ
c_parser_ਸੈੱਟ_error (c_parser *parser, ਤਾਰਕਿਕ err)
{
  parser->error = err;
}


/* The actual parser and external interface.  ??? Does this need to be
   garbage-collected?  */

ਸਥਿਰ GTY (()) c_parser *the_parser;

/* Read in and lex a single token, storing it in *TOKEN.  If RAW,
   context-sensitive postprocessing of the token is not done.  */

ਸਥਿਰ ਖਾਲੀ
c_lex_one_token (c_parser *parser, c_token *token, ਤਾਰਕਿਕ raw = ਝੂਠ)
{
  timevar_ਧੱਕੋ (TV_LEX);

  ਜੇ (raw || vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (parser->raw_ਟੋਕਨ) == 0)
    {
      token->type = c_lex_with_flags (&token->ਮੁੱਲ, &token->location,
				      &token->flags,
				      (parser->lex_joined_string
				       ? 0 : C_LEX_STRING_NO_JOIN));
      token->id_ਕਿਸਮ = C_ID_NONE;
      token->keyword = RID_MAX;
      token->pragma_ਕਿਸਮ = PRAGMA_NONE;
    }
  ਨਹੀਂਤਾਂ
    {
      /* Use a token previously lexed as a raw look-ahead token, and
	 complete the processing on it.  */
      *token = (*parser->raw_ਟੋਕਨ)[parser->raw_ਟੋਕਨ_ਵਰਤਿਆ];
      ++parser->raw_ਟੋਕਨ_ਵਰਤਿਆ;
      ਜੇ (parser->raw_ਟੋਕਨ_ਵਰਤਿਆ == vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (parser->raw_ਟੋਕਨ))
	{
	  vec_free (parser->raw_ਟੋਕਨ);
	  parser->raw_ਟੋਕਨ_ਵਰਤਿਆ = 0;
	}
    }

  ਜੇ (raw)
    ਜਾਓ ਬਾਹਰਲਾ;

  ਚੋਣ (token->type)
    {
    ਹਾਲਤ CPP_NAME:
      {
	ਰੁੱਖ decl;

	ਤਾਰਕਿਕ objc_force_identifier = parser->objc_need_raw_identifier;
	ਜੇ (c_dialect_objc ())
	  parser->objc_need_raw_identifier = ਝੂਠ;

	ਜੇ (C_IS_RESERVED_ਸ਼ਬਦ (token->ਮੁੱਲ))
	  {
	    ਗਿਣਤੀ rid rid_ਕੋਡ = C_RID_ਕੋਡ (token->ਮੁੱਲ);

	    ਜੇ (rid_ਕੋਡ == RID_CXX_COMPAT_WARN)
	      {
		warning_at (token->location,
			    OPT_Wc___compat,
			    "identifier %qE conflicts with C++ keyword",
			    token->ਮੁੱਲ);
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (rid_ਕੋਡ >= RID_ਪਹਿਲਾ_ADDR_SPACE
		     && rid_ਕੋਡ <= RID_ਆਖਰੀ_ADDR_SPACE)
	      {
		addr_space_t as;
		as = (addr_space_t) (rid_ਕੋਡ - RID_ਪਹਿਲਾ_ADDR_SPACE);
		targetm.addr_space.diagnose_usage (as, token->location);
		token->id_ਕਿਸਮ = C_ID_ADDRSPACE;
		token->keyword = rid_ਕੋਡ;
		ਰੋਕੋ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (c_dialect_objc () && OBJC_IS_PQ_KEYWORD (rid_ਕੋਡ))
	      {
		/* We found an Objective-C "pq" keyword (in, out,
		   inout, bycopy, byref, oneway).  They need special
		   care because the interpretation depends on the
		   context.  */
		ਜੇ (parser->objc_pq_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_ਕੋਡ;
		    ਰੋਕੋ;
		  }
		ਨਹੀਂਤਾਂ ਜੇ (parser->objc_could_be_foreach_context
			 && rid_ਕੋਡ == RID_ਵਿੱਚ)
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
		    token->keyword = rid_ਕੋਡ;
		    ਰੋਕੋ;
		  }
		/* Else, "pq" keywords outside of the "pq" context are
		   not keywords, and we fall through to the code for
		   normal tokens.  */
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (c_dialect_objc () && OBJC_IS_PATTR_KEYWORD (rid_ਕੋਡ))
	      {
		/* We found an Objective-C "property attribute"
		   keyword (getter, setter, readonly, etc). These are
		   only valid in the property context.  */
		ਜੇ (parser->objc_property_attr_context)
		  {
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_ਕੋਡ;
		    ਰੋਕੋ;
		  }
		/* Else they are not special keywords.
		*/
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (c_dialect_objc ()
		     && (OBJC_IS_AT_KEYWORD (rid_ਕੋਡ)
			 || OBJC_IS_CXX_KEYWORD (rid_ਕੋਡ)))
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
	    ਨਹੀਂਤਾਂ
	      {
		token->type = CPP_KEYWORD;
		token->keyword = rid_ਕੋਡ;
		ਰੋਕੋ;
	      }
	  }

	decl = lookup_name (token->ਮੁੱਲ);
	ਜੇ (decl)
	  {
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == TYPE_DECL)
	      {
		token->id_ਕਿਸਮ = C_ID_TYPENAME;
		ਰੋਕੋ;
	      }
	  }
	ਨਹੀਂਤਾਂ ਜੇ (c_dialect_objc ())
	  {
	    ਰੁੱਖ objc_interface_decl = objc_is_class_name (token->ਮੁੱਲ);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    ਜੇ (objc_interface_decl
                && (!objc_force_identifier || global_bindings_p ()))
	      {
		token->ਮੁੱਲ = objc_interface_decl;
		token->id_ਕਿਸਮ = C_ID_CLASSNAME;
		ਰੋਕੋ;
	      }
	  }
        token->id_ਕਿਸਮ = C_ID_ID;
      }
      ਰੋਕੋ;
    ਹਾਲਤ CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      ਚੋਣ (C_RID_ਕੋਡ (token->ਮੁੱਲ))
	{
	  /* Replace 'class' with '@class', 'private' with '@private',
	     etc.  This prevents confusion with the C++ keyword
	     'class', and makes the tokens consistent with other
	     Objective-C 'AT' keywords.  For example '@class' is
	     reported as RID_AT_CLASS which is consistent with
	     '@synchronized', which is reported as
	     RID_AT_SYNCHRONIZED.
	  */
	ਹਾਲਤ RID_CLASS:     token->keyword = RID_AT_CLASS; ਰੋਕੋ;
	ਹਾਲਤ RID_ਨਿੱਜੀ:   token->keyword = RID_AT_ਨਿੱਜੀ; ਰੋਕੋ;
	ਹਾਲਤ RID_PROTECTED: token->keyword = RID_AT_PROTECTED; ਰੋਕੋ;
	ਹਾਲਤ RID_ਜਨਤਕ:    token->keyword = RID_AT_ਜਨਤਕ; ਰੋਕੋ;
	ਹਾਲਤ RID_THROW:     token->keyword = RID_AT_THROW; ਰੋਕੋ;
	ਹਾਲਤ RID_TRY:       token->keyword = RID_AT_TRY; ਰੋਕੋ;
	ਹਾਲਤ RID_CATCH:     token->keyword = RID_AT_CATCH; ਰੋਕੋ;
	ਹਾਲਤ RID_SYNCHRONIZED: token->keyword = RID_AT_SYNCHRONIZED; ਰੋਕੋ;
	ਮੂਲ:            token->keyword = C_RID_ਕੋਡ (token->ਮੁੱਲ);
	}
      ਰੋਕੋ;
    ਹਾਲਤ CPP_COLON:
    ਹਾਲਤ CPP_COMMA:
    ਹਾਲਤ CPP_CLOSE_PAREN:
    ਹਾਲਤ CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      ਜੇ (c_dialect_objc ())
	parser->objc_need_raw_identifier = ਝੂਠ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_ਕਿਸਮ = (ਗਿਣਤੀ pragma_ਕਿਸਮ) ਰੁੱਖ_INT_CST_ਨੀਵਾਂ (token->ਮੁੱਲ);
      token->ਮੁੱਲ = ਨਿਰਾ;
      ਰੋਕੋ;
    ਮੂਲ:
      ਰੋਕੋ;
    }
 ਬਾਹਰਲਾ:
  timevar_ਕੱਢੋ (TV_LEX);
}

/* Return a pointer to the next token from PARSER, reading it in if
   necessary.  */

c_token *
c_parser_peek_token (c_parser *parser)
{
  ਜੇ (parser->ਟੋਕਨ_avail == 0)
    {
      c_lex_one_token (parser, &parser->ਟੋਕਨ[0]);
      parser->ਟੋਕਨ_avail = 1;
    }
  ਵਾਪਸ &parser->ਟੋਕਨ[0];
}

/* Return a pointer to the next-but-one token from PARSER, reading it
   in if necessary.  The next token is already read in.  */

c_token *
c_parser_peek_2nd_token (c_parser *parser)
{
  ਜੇ (parser->ਟੋਕਨ_avail >= 2)
    ਵਾਪਸ &parser->ਟੋਕਨ[1];
  gcc_assert (parser->ਟੋਕਨ_avail == 1);
  gcc_assert (parser->ਟੋਕਨ[0].type != CPP_EOF);
  gcc_assert (parser->ਟੋਕਨ[0].type != CPP_PRAGMA_EOL);
  c_lex_one_token (parser, &parser->ਟੋਕਨ[1]);
  parser->ਟੋਕਨ_avail = 2;
  ਵਾਪਸ &parser->ਟੋਕਨ[1];
}

/* Return a pointer to the Nth token from PARSER, reading it
   in if necessary.  The N-1th token is already read in.  */

c_token *
c_parser_peek_nth_token (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  ਜੇ (parser->ਟੋਕਨ_avail >= n)
    ਵਾਪਸ &parser->ਟੋਕਨ[n - 1];
  gcc_assert (parser->ਟੋਕਨ_avail == n - 1);
  c_lex_one_token (parser, &parser->ਟੋਕਨ[n - 1]);
  parser->ਟੋਕਨ_avail = n;
  ਵਾਪਸ &parser->ਟੋਕਨ[n - 1];
}

/* Return a pointer to the Nth token from PARSER, reading it in as a
   raw look-ahead token if necessary.  The N-1th token is already read
   in.  Raw look-ahead tokens remain available for when the non-raw
   functions above are called.  */

c_token *
c_parser_peek_nth_token_raw (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n)
{
  /* N is 1-based, not zero-based.  */
  gcc_assert (n > 0);

  ਜੇ (parser->ਟੋਕਨ_avail >= n)
    ਵਾਪਸ &parser->ਟੋਕਨ[n - 1];
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ raw_len = vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (parser->raw_ਟੋਕਨ);
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ raw_avail
    = parser->ਟੋਕਨ_avail + raw_len - parser->raw_ਟੋਕਨ_ਵਰਤਿਆ;
  gcc_assert (raw_avail >= n - 1);
  ਜੇ (raw_avail >= n)
    ਵਾਪਸ &(*parser->raw_ਟੋਕਨ)[parser->raw_ਟੋਕਨ_ਵਰਤਿਆ
				  + n - 1 - parser->ਟੋਕਨ_avail];
  vec_ਸੁਰੱਖਿਅਤ_reserve (parser->raw_ਟੋਕਨ, 1);
  parser->raw_ਟੋਕਨ->ਤੇਜ਼_grow (raw_len + 1);
  c_lex_one_token (parser, &(*parser->raw_ਟੋਕਨ)[raw_len], ਸੱਚ);
  ਵਾਪਸ &(*parser->raw_ਟੋਕਨ)[raw_len];
}

ਤਾਰਕਿਕ
c_keyword_starts_typename (ਗਿਣਤੀ rid keyword)
{
  ਚੋਣ (keyword)
    {
    ਹਾਲਤ RID_UNSIGNED:
    ਹਾਲਤ RID_LONG:
    ਹਾਲਤ RID_SHORT:
    ਹਾਲਤ RID_SIGNED:
    ਹਾਲਤ RID_COMPLEX:
    ਹਾਲਤ RID_INT:
    ਹਾਲਤ RID_CHAR:
    ਹਾਲਤ RID_FLOAT:
    ਹਾਲਤ RID_DOUBLE:
    ਹਾਲਤ RID_VOID:
    ਹਾਲਤ RID_DFLOAT32:
    ਹਾਲਤ RID_DFLOAT64:
    ਹਾਲਤ RID_DFLOAT128:
    ਹਾਲਤ RID_DFLOAT64X:
    CASE_RID_FLOATN_NX:
    ਹਾਲਤ RID_BOOL:
    ਹਾਲਤ RID_BITINT:
    ਹਾਲਤ RID_ENUM:
    ਹਾਲਤ RID_STRUCT:
    ਹਾਲਤ RID_UNION:
    ਹਾਲਤ RID_TYPEOF:
    ਹਾਲਤ RID_TYPEOF_UNQUAL:
    ਹਾਲਤ RID_CONST:
    ਹਾਲਤ RID_ATOMIC:
    ਹਾਲਤ RID_VOLATILE:
    ਹਾਲਤ RID_RESTRICT:
    ਹਾਲਤ RID_ATTRIBUTE:
    ਹਾਲਤ RID_FRACT:
    ਹਾਲਤ RID_ACCUM:
    ਹਾਲਤ RID_SAT:
    ਹਾਲਤ RID_AUTO_TYPE:
    ਹਾਲਤ RID_ALIGNAS:
      ਵਾਪਸ ਸੱਚ;
    ਮੂਲ:
      ਜੇ (keyword >= RID_ਪਹਿਲਾ_INT_N
	  && keyword < RID_ਪਹਿਲਾ_INT_N + ਅੰਕ_INT_N_ENTS
	  && int_n_enabled_p[keyword - RID_ਪਹਿਲਾ_INT_N])
	ਵਾਪਸ ਸੱਚ;
      ਵਾਪਸ ਝੂਠ;
    }
}

/* Return true if TOKEN can start a type name,
   false otherwise.  */
ਤਾਰਕਿਕ
c_token_starts_typename (c_token *token)
{
  ਚੋਣ (token->type)
    {
    ਹਾਲਤ CPP_NAME:
      ਚੋਣ (token->id_ਕਿਸਮ)
	{
	ਹਾਲਤ C_ID_ID:
	  ਵਾਪਸ ਝੂਠ;
	ਹਾਲਤ C_ID_ADDRSPACE:
	  ਵਾਪਸ ਸੱਚ;
	ਹਾਲਤ C_ID_TYPENAME:
	  ਵਾਪਸ ਸੱਚ;
	ਹਾਲਤ C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  ਵਾਪਸ ਸੱਚ;
	ਮੂਲ:
	  gcc_unreachable ();
	}
    ਹਾਲਤ CPP_KEYWORD:
      ਵਾਪਸ c_keyword_starts_typename (token->keyword);
    ਹਾਲਤ CPP_LESS:
      ਜੇ (c_dialect_objc ())
	ਵਾਪਸ ਸੱਚ;
      ਵਾਪਸ ਝੂਠ;
    ਮੂਲ:
      ਵਾਪਸ ਝੂਠ;
    }
}

/* Return true if the next token from PARSER, starting from token N, can start
   a type name, false otherwise.  LA specifies how to do lookahead in order to
   detect unknown type names.  If unsure, pick CLA_PREFER_ID.  */

ਸਥਿਰ ਸਤਰਅੰਦਰ ਤਾਰਕਿਕ
c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (c_parser *parser, ਗਿਣਤੀ c_lookahead_ਕਿਸਮ la,
				     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n = 1)
{
  c_token *token = c_parser_peek_nth_token (parser, n);
  ਜੇ (c_token_starts_typename (token))
    ਵਾਪਸ ਸੱਚ;

  /* Try a bit harder to detect an unknown typename.  */
  ਜੇ (la != cla_prefer_id
      && token->type == CPP_NAME
      && token->id_ਕਿਸਮ == C_ID_ID

      /* Do not try too hard when we could have "object in array".  */
      && !parser->objc_could_be_foreach_context

      && (la == cla_prefer_type
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_NAME
	  || c_parser_peek_nth_token (parser, n + 1)->type == CPP_MULT)

      /* Only unknown identifiers.  */
      && !lookup_name (token->ਮੁੱਲ))
    ਵਾਪਸ ਸੱਚ;

  ਵਾਪਸ ਝੂਠ;
}

/* Return true if TOKEN, after an open parenthesis, can start a
   compound literal (either a storage class specifier allowed in that
   context, or a type name), false otherwise.  */
ਸਥਿਰ ਤਾਰਕਿਕ
c_token_starts_compound_literal (c_token *token)
{
  ਚੋਣ (token->type)
    {
    ਹਾਲਤ CPP_KEYWORD:
      ਚੋਣ (token->keyword)
	{
	ਹਾਲਤ RID_CONSTEXPR:
	ਹਾਲਤ RID_ਰਜਿਸਟਰ:
	ਹਾਲਤ RID_STATIC:
	ਹਾਲਤ RID_THREAD:
	  ਵਾਪਸ ਸੱਚ;
	ਮੂਲ:
	  ਰੋਕੋ;
	}
      /* Fall through.  */
    ਮੂਲ:
      ਵਾਪਸ c_token_starts_typename (token);
    }
}

/* Return true if TOKEN is a type qualifier, false otherwise.  */
ਸਥਿਰ ਤਾਰਕਿਕ
c_token_is_qualifier (c_token *token)
{
  ਚੋਣ (token->type)
    {
    ਹਾਲਤ CPP_NAME:
      ਚੋਣ (token->id_ਕਿਸਮ)
	{
	ਹਾਲਤ C_ID_ADDRSPACE:
	  ਵਾਪਸ ਸੱਚ;
	ਮੂਲ:
	  ਵਾਪਸ ਝੂਠ;
	}
    ਹਾਲਤ CPP_KEYWORD:
      ਚੋਣ (token->keyword)
	{
	ਹਾਲਤ RID_CONST:
	ਹਾਲਤ RID_VOLATILE:
	ਹਾਲਤ RID_RESTRICT:
	ਹਾਲਤ RID_ATTRIBUTE:
	ਹਾਲਤ RID_ATOMIC:
	  ਵਾਪਸ ਸੱਚ;
	ਮੂਲ:
	  ਵਾਪਸ ਝੂਠ;
	}
    ਹਾਲਤ CPP_LESS:
      ਵਾਪਸ ਝੂਠ;
    ਮੂਲ:
      gcc_unreachable ();
    }
}

/* Return true if the next token from PARSER is a type qualifier,
   false otherwise.  */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਤਾਰਕਿਕ
c_parser_ਅਗਲਾ_token_is_qualifier (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  ਵਾਪਸ c_token_is_qualifier (token);
}

/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes), false otherwise.  */
ਸਥਿਰ ਤਾਰਕਿਕ
c_token_starts_declspecs (c_token *token)
{
  ਚੋਣ (token->type)
    {
    ਹਾਲਤ CPP_NAME:
      ਚੋਣ (token->id_ਕਿਸਮ)
	{
	ਹਾਲਤ C_ID_ID:
	  ਵਾਪਸ ਝੂਠ;
	ਹਾਲਤ C_ID_ADDRSPACE:
	  ਵਾਪਸ ਸੱਚ;
	ਹਾਲਤ C_ID_TYPENAME:
	  ਵਾਪਸ ਸੱਚ;
	ਹਾਲਤ C_ID_CLASSNAME:
	  gcc_assert (c_dialect_objc ());
	  ਵਾਪਸ ਸੱਚ;
	ਮੂਲ:
	  gcc_unreachable ();
	}
    ਹਾਲਤ CPP_KEYWORD:
      ਚੋਣ (token->keyword)
	{
	ਹਾਲਤ RID_STATIC:
	ਹਾਲਤ RID_EXTERN:
	ਹਾਲਤ RID_ਰਜਿਸਟਰ:
	ਹਾਲਤ RID_TYPEDEF:
	ਹਾਲਤ RID_INLINE:
	ਹਾਲਤ RID_NORETURN:
	ਹਾਲਤ RID_AUTO:
	ਹਾਲਤ RID_THREAD:
	ਹਾਲਤ RID_UNSIGNED:
	ਹਾਲਤ RID_LONG:
	ਹਾਲਤ RID_SHORT:
	ਹਾਲਤ RID_SIGNED:
	ਹਾਲਤ RID_COMPLEX:
	ਹਾਲਤ RID_INT:
	ਹਾਲਤ RID_CHAR:
	ਹਾਲਤ RID_FLOAT:
	ਹਾਲਤ RID_DOUBLE:
	ਹਾਲਤ RID_VOID:
	ਹਾਲਤ RID_DFLOAT32:
	ਹਾਲਤ RID_DFLOAT64:
	ਹਾਲਤ RID_DFLOAT128:
	ਹਾਲਤ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ਹਾਲਤ RID_BOOL:
	ਹਾਲਤ RID_BITINT:
	ਹਾਲਤ RID_ENUM:
	ਹਾਲਤ RID_STRUCT:
	ਹਾਲਤ RID_UNION:
	ਹਾਲਤ RID_TYPEOF:
	ਹਾਲਤ RID_TYPEOF_UNQUAL:
	ਹਾਲਤ RID_CONST:
	ਹਾਲਤ RID_VOLATILE:
	ਹਾਲਤ RID_RESTRICT:
	ਹਾਲਤ RID_ATTRIBUTE:
	ਹਾਲਤ RID_FRACT:
	ਹਾਲਤ RID_ACCUM:
	ਹਾਲਤ RID_SAT:
	ਹਾਲਤ RID_ALIGNAS:
	ਹਾਲਤ RID_ATOMIC:
	ਹਾਲਤ RID_AUTO_TYPE:
	ਹਾਲਤ RID_CONSTEXPR:
	  ਵਾਪਸ ਸੱਚ;
	ਮੂਲ:
	  ਜੇ (token->keyword >= RID_ਪਹਿਲਾ_INT_N
	      && token->keyword < RID_ਪਹਿਲਾ_INT_N + ਅੰਕ_INT_N_ENTS
	      && int_n_enabled_p[token->keyword - RID_ਪਹਿਲਾ_INT_N])
	    ਵਾਪਸ ਸੱਚ;
	  ਵਾਪਸ ਝੂਠ;
	}
    ਹਾਲਤ CPP_LESS:
      ਜੇ (c_dialect_objc ())
	ਵਾਪਸ ਸੱਚ;
      ਵਾਪਸ ਝੂਠ;
    ਮੂਲ:
      ਵਾਪਸ ਝੂਠ;
    }
}


/* Return true if TOKEN can start declaration specifiers (not
   including standard attributes) or a static assertion, false
   otherwise.  */
ਸਥਿਰ ਤਾਰਕਿਕ
c_token_starts_declaration (c_token *token)
{
  ਜੇ (c_token_starts_declspecs (token)
      || token->keyword == RID_STATIC_ASSERT)
    ਵਾਪਸ ਸੱਚ;
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ ਝੂਠ;
}

/* Return true if the next token from PARSER can start declaration
   specifiers (not including standard attributes), false
   otherwise.  */
ਤਾਰਕਿਕ
c_parser_ਅਗਲਾ_token_starts_declspecs (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);

  /* In Objective-C, a classname normally starts a declspecs unless it
     is immediately followed by a dot.  In that case, it is the
     Objective-C 2.0 "dot-syntax" for class objects, ie, calls the
     setter/getter on the class.  c_token_starts_declspecs() can't
     differentiate between the two cases because it only checks the
     current token, so we have a special check here.  */
  ਜੇ (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_ਕਿਸਮ == C_ID_CLASSNAME
      && c_parser_peek_2nd_token (parser)->type == CPP_DOT)
    ਵਾਪਸ ਝੂਠ;

  ਵਾਪਸ c_token_starts_declspecs (token);
}

ਸਥਿਰ ਤਾਰਕਿਕ c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (c_parser *,
							ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *);

/* Return true if the next tokens from PARSER (starting with token N, 1-based)
   can start declaration specifiers (not including standard attributes) or a
   static assertion, false otherwise.  */
ਤਾਰਕਿਕ
c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n)
{
  c_token *token = c_parser_peek_nth_token (parser, n);

  /* Same as above.  */
  ਜੇ (c_dialect_objc ()
      && token->type == CPP_NAME
      && token->id_ਕਿਸਮ == C_ID_CLASSNAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_DOT)
    ਵਾਪਸ ਝੂਠ;

  /* Labels do not start declarations.  */
  ਜੇ (token->type == CPP_NAME
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_COLON)
    ਵਾਪਸ ਝੂਠ;

  /* A static assertion is only a declaration if followed by a semicolon;
     otherwise, it may be an expression in C2Y.  */
  ਜੇ (token->keyword == RID_STATIC_ASSERT
      && c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_PAREN)
    {
      n += 2;
      ਜੇ (!c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n)
	  || c_parser_peek_nth_token_raw (parser, n)->type != CPP_CLOSE_PAREN)
	/* Invalid static assertion syntax; treat as a declaration and report a
	   syntax error there.  */
	ਵਾਪਸ ਸੱਚ;
      ਵਾਪਸ c_parser_peek_nth_token_raw (parser, n + 1)->type == CPP_SEMICOLON;
    }

  ਜੇ (c_token_starts_declaration (token))
    ਵਾਪਸ ਸੱਚ;

  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, cla_nonabstract_decl, n))
    ਵਾਪਸ ਸੱਚ;

  ਵਾਪਸ ਝੂਠ;
}

/* Consume the next token from PARSER.  */

ਖਾਲੀ
c_parser_consume_token (c_parser *parser)
{
  gcc_assert (parser->ਟੋਕਨ_avail >= 1);
  gcc_assert (parser->ਟੋਕਨ[0].type != CPP_EOF);
  gcc_assert (!parser->ਵਿੱਚ_pragma || parser->ਟੋਕਨ[0].type != CPP_PRAGMA_EOL);
  /* CPP_PRAGMA should not show up here except if there was an error or inside
     another pragma.  */
  gcc_assert (parser->ਵਿੱਚ_pragma
	      || parser->error
	      || parser->ਟੋਕਨ[0].type != CPP_PRAGMA);
  parser->ਆਖਰੀ_token_location = parser->ਟੋਕਨ[0].location;
  ਜੇ (parser->ਟੋਕਨ != &parser->ਟੋਕਨ_buf[0])
    parser->ਟੋਕਨ++;
  ਨਹੀਂਤਾਂ ਜੇ (parser->ਟੋਕਨ_avail >= 2)
    {
      parser->ਟੋਕਨ[0] = parser->ਟੋਕਨ[1];
      ਜੇ (parser->ਟੋਕਨ_avail >= 3)
        {
          parser->ਟੋਕਨ[1] = parser->ਟੋਕਨ[2];
          ਜੇ (parser->ਟੋਕਨ_avail >= 4)
            parser->ਟੋਕਨ[2] = parser->ਟੋਕਨ[3];
        }
    }
  parser->ਟੋਕਨ_avail--;
  parser->ਵੇਖਿਆ_string_literal = ਝੂਠ;
}

/* Expect the current token to be a #pragma.  Consume it and remember
   that we've begun parsing a pragma.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_consume_pragma (c_parser *parser)
{
  gcc_assert (!parser->ਵਿੱਚ_pragma);
  gcc_assert (parser->ਟੋਕਨ_avail >= 1);
  gcc_assert (parser->ਟੋਕਨ[0].type == CPP_PRAGMA);
  ਜੇ (parser->ਟੋਕਨ != &parser->ਟੋਕਨ_buf[0])
    parser->ਟੋਕਨ++;
  ਨਹੀਂਤਾਂ ਜੇ (parser->ਟੋਕਨ_avail >= 2)
    {
      parser->ਟੋਕਨ[0] = parser->ਟੋਕਨ[1];
      ਜੇ (parser->ਟੋਕਨ_avail >= 3)
	parser->ਟੋਕਨ[1] = parser->ਟੋਕਨ[2];
    }
  parser->ਟੋਕਨ_avail--;
  parser->ਵਿੱਚ_pragma = ਸੱਚ;
}

/* Update the global input_location from TOKEN.  */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ
c_parser_ਸੈੱਟ_ਸਰੋਤ_position_from_token (c_token *token)
{
  ਜੇ (token->type != CPP_EOF)
    {
      ਨਿਵੇਸ਼_location = token->location;
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

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_peek_conflict_marker (c_parser *parser, ਗਿਣਤੀ cpp_ttype tok1_ਕਿਸਮ,
			       location_t *ਬਾਹਰਲਾ_loc)
{
  c_token *token2 = c_parser_peek_2nd_token (parser);
  ਜੇ (token2->type != tok1_ਕਿਸਮ)
    ਵਾਪਸ ਝੂਠ;
  c_token *token3 = c_parser_peek_nth_token (parser, 3);
  ਜੇ (token3->type != tok1_ਕਿਸਮ)
    ਵਾਪਸ ਝੂਠ;
  c_token *token4 = c_parser_peek_nth_token (parser, 4);
  ਜੇ (token4->type != conflict_marker_get_final_tok_ਕਿਸਮ (tok1_ਕਿਸਮ))
    ਵਾਪਸ ਝੂਠ;

  /* It must be at the start of the line.  */
  location_t ਸ਼ੁਰੂ_loc = c_parser_peek_token (parser)->location;
  ਜੇ (LOCATION_ਕਾਲਮ (ਸ਼ੁਰੂ_loc) != 1)
    ਵਾਪਸ ਝੂਠ;

  /* We have a conflict marker.  Construct a location of the form:
       <<<<<<<
       ^~~~~~~
     with start == caret, finishing at the end of the marker.  */
  location_t ਅੰਤ_loc = get_ਅੰਤ (token4->location);
  *ਬਾਹਰਲਾ_loc = make_location (ਸ਼ੁਰੂ_loc, ਸ਼ੁਰੂ_loc, ਅੰਤ_loc);

  ਵਾਪਸ ਸੱਚ;
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

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_error_richloc (c_parser *parser, ਅਚਲ ਅੱਖਰ *gmsgid,
			rich_location *richloc)
{
  c_token *token = c_parser_peek_token (parser);
  ਜੇ (parser->error)
    ਵਾਪਸ ਝੂਠ;
  parser->error = ਸੱਚ;
  ਜੇ (!gmsgid)
    ਵਾਪਸ ਝੂਠ;

  /* If this is actually a conflict marker, report it as such.  */
  ਜੇ (token->type == CPP_LSHIFT
      || token->type == CPP_RSHIFT
      || token->type == CPP_EQ_EQ)
    {
      location_t loc;
      ਜੇ (c_parser_peek_conflict_marker (parser, token->type, &loc))
	{
	  error_at (loc, "version control conflict marker in file");
	  ਵਾਪਸ ਸੱਚ;
	}
    }

  /* If we were parsing a string-literal and there is an unknown name
     token right after, then check to see if that could also have been
     a literal string by checking the name against a list of known
     standard string literal constants defined in header files. If
     there is one, then add that as an hint to the error message. */
  auto_diagnostic_ਸਮੂਹ d;
  name_hint h;
  ਜੇ (parser->ਵੇਖਿਆ_string_literal && token->type == CPP_NAME)
    {
      ਰੁੱਖ name = token->ਮੁੱਲ;
      ਅਚਲ ਅੱਖਰ *token_name = IDENTIFIER_ਸੂਚਕ (name);
      ਅਚਲ ਅੱਖਰ *ਸਿਰਲੇਖ_hint
	= get_c_stdlib_ਸਿਰਲੇਖ_for_string_macro_name (token_name);
      ਜੇ (ਸਿਰਲੇਖ_hint != ਨਿਰਾ)
	h = name_hint (ਖਾਲੀ_ਸੂਚਕ,
		       std::make_unique<suggest_missing_ਸਿਰਲੇਖ>
			 (token->location,
			  token_name,
			  ਸਿਰਲੇਖ_hint));
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
		 token->ਮੁੱਲ, /*flags=*/0, richloc);
  ਵਾਪਸ ਸੱਚ;
}

/* As c_parser_error_richloc, but issue the message at the
   location of PARSER's next token, or at input_location
   if the next token is EOF.  */

ਤਾਰਕਿਕ
c_parser_error (c_parser *parser, ਅਚਲ ਅੱਖਰ *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  c_parser_ਸੈੱਟ_ਸਰੋਤ_position_from_token (token);
  rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, ਨਿਵੇਸ਼_location);
  ਵਾਪਸ c_parser_error_richloc (parser, gmsgid, &richloc);
}

/* Some tokens naturally come in pairs e.g.'(' and ')'.
   This class is for tracking such a matching pair of symbols.
   In particular, it tracks the location of the first token,
   so that if the second token is missing, we can highlight the
   location of the first token when notifying the user about the
   problem.  */

ਸਾਂਚਾ <ਕਿਸਮ_ਨਾਂ traits_t>
ਵਰਗ token_pair
{
 ਜਨਤਕ:
  /* token_pair's ctor.  */
  token_pair () : m_open_loc (UNKNOWN_LOCATION) {}

  /* If the next token is the opening symbol for this pair, consume it and
     return true.
     Otherwise, issue an error and return false.
     In either case, record the location of the opening token.  */

  ਤਾਰਕਿਕ require_open (c_parser *parser)
  {
    c_token *token = c_parser_peek_token (parser);
    ਜੇ (token)
      m_open_loc = token->location;

    ਵਾਪਸ c_parser_require (parser, traits_t::open_token_type,
			     traits_t::open_gmsgid);
  }

  /* Consume the next token from PARSER, recording its location as
     that of the opening token within the pair.  */

  ਖਾਲੀ consume_open (c_parser *parser)
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

  ਤਾਰਕਿਕ require_close (c_parser *parser) ਅਚਲ
  {
    ਵਾਪਸ c_parser_require (parser, traits_t::close_token_type,
			     traits_t::close_gmsgid, m_open_loc);
  }

  /* Like token_pair::require_close, except that tokens will be skipped
     until the desired token is found.  An error message is still produced
     if the next token is not as expected.  */

  ਖਾਲੀ skip_until_ਮਿਲਿਆ_close (c_parser *parser) ਅਚਲ
  {
    c_parser_skip_until_ਮਿਲਿਆ (parser, traits_t::close_token_type,
			       traits_t::close_gmsgid, m_open_loc);
  }

 ਨਿਜੀ:
  location_t m_open_loc;
};

/* Traits for token_pair<T> for tracking matching pairs of parentheses.  */

ਬਣਤਰ matching_paren_traits
{
  ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ cpp_ttype open_token_type = CPP_OPEN_PAREN;
  ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ open_gmsgid;
  ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ cpp_ttype close_token_type = CPP_CLOSE_PAREN;
  ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ close_gmsgid;
};

ਅਚਲ ਅੱਖਰ * ਅਚਲ matching_paren_traits::open_gmsgid = "expected %<(%>";
ਅਚਲ ਅੱਖਰ * ਅਚਲ matching_paren_traits::close_gmsgid = "expected %<)%>";

/* "matching_parens" is a token_pair<T> class for tracking matching
   pairs of parentheses.  */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ token_pair<matching_paren_traits> matching_parens;

/* Traits for token_pair<T> for tracking matching pairs of braces.  */

ਬਣਤਰ matching_brace_traits
{
  ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ cpp_ttype open_token_type = CPP_OPEN_BRACE;
  ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ open_gmsgid;
  ਸਥਿਰ ਅਚਲ ਗਿਣਤੀ cpp_ttype close_token_type = CPP_CLOSE_BRACE;
  ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ close_gmsgid;
};

ਅਚਲ ਅੱਖਰ * ਅਚਲ matching_brace_traits::open_gmsgid = "expected %<{%>";
ਅਚਲ ਅੱਖਰ * ਅਚਲ matching_brace_traits::close_gmsgid = "expected %<}%>";

/* "matching_braces" is a token_pair<T> class for tracking matching
   pairs of braces.  */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ token_pair<matching_brace_traits> matching_braces;

/* Get a description of the matching symbol to TYPE e.g. "(" for
   CPP_CLOSE_PAREN.  */

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *
get_matching_ਚਿੰਨ੍ਹ (ਗਿਣਤੀ cpp_ttype type)
{
  ਚੋਣ (type)
    {
    ਮੂਲ:
      gcc_unreachable ();
    ਹਾਲਤ CPP_CLOSE_PAREN:
      ਵਾਪਸ "(";
    ਹਾਲਤ CPP_CLOSE_BRACE:
      ਵਾਪਸ "{";
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

ਤਾਰਕਿਕ
c_parser_require (c_parser *parser,
		  ਗਿਣਤੀ cpp_ttype type,
		  ਅਚਲ ਅੱਖਰ *msgid,
		  location_t matching_location,
		  ਤਾਰਕਿਕ type_is_unique)
{
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, type))
    {
      c_parser_consume_token (parser);
      ਵਾਪਸ ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ
    {
      location_t ਅਗਲਾ_token_loc = c_parser_peek_token (parser)->location;
      gcc_rich_location richloc (ਅਗਲਾ_token_loc);

      /* Potentially supply a fix-it hint, suggesting to add the
	 missing token immediately after the *previous* token.
	 This may move the primary location within richloc.  */
      ਜੇ (!parser->error && type_is_unique)
	maybe_suggest_missing_token_insertion (&richloc, type,
					       parser->ਆਖਰੀ_token_location);

      /* If matching_location != UNKNOWN_LOCATION, highlight it.
	 Attempt to consolidate diagnostics by printing it as a
	 secondary range within the main diagnostic.  */
      ਤਾਰਕਿਕ added_matching_location = ਝੂਠ;
      ਜੇ (matching_location != UNKNOWN_LOCATION)
	added_matching_location
	  = richloc.ਜੋੜੋ_location_if_nearby (*global_dc, matching_location);

      ਜੇ (c_parser_error_richloc (parser, msgid, &richloc))
	/* If we weren't able to consolidate matching_location, then
	   print it as a secondary diagnostic.  */
	ਜੇ (matching_location != UNKNOWN_LOCATION && !added_matching_location)
	  inform (matching_location, "to match this %qs",
		  get_matching_ਚਿੰਨ੍ਹ (type));

      ਵਾਪਸ ਝੂਠ;
    }
}

/* If the next token is the indicated keyword, consume it.  Otherwise,
   issue the error MSGID.  Returns true if found, false otherwise.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_require_keyword (c_parser *parser,
			  ਗਿਣਤੀ rid keyword,
			  ਅਚਲ ਅੱਖਰ *msgid)
{
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, keyword))
    {
      c_parser_consume_token (parser);
      ਵਾਪਸ ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ
    {
      c_parser_error (parser, msgid);
      ਵਾਪਸ ਝੂਠ;
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

ਖਾਲੀ
c_parser_skip_until_ਮਿਲਿਆ (c_parser *parser,
			   ਗਿਣਤੀ cpp_ttype type,
			   ਅਚਲ ਅੱਖਰ *msgid,
			   location_t matching_location)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ nesting_ਡੂੰਘਾਈ = 0;

  ਜੇ (c_parser_require (parser, type, msgid, matching_location))
    {
      ਜੇ (UNLIKELY (type == CPP_PRAGMA_EOL) && parser->ਵਿੱਚ_omp_attribute_pragma)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ਜੇ (token->type == CPP_EOF)
	    {
	      parser->ਟੋਕਨ = parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ;
	      parser->ਟੋਕਨ_avail
		= parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ_avail;
	      parser->ਵਿੱਚ_omp_attribute_pragma = ਨਿਰਾ;
	    }
	}
      ਵਾਪਸ;
    }

  /* Skip tokens until the desired token is found.  */
  ਜਦੋਂ (ਸੱਚ)
    {
      /* Peek at the next token.  */
      c_token *token = c_parser_peek_token (parser);
      /* If we've reached the token we want, consume it and stop.  */
      ਜੇ (token->type == type && !nesting_ਡੂੰਘਾਈ)
	{
	  c_parser_consume_token (parser);
	  ਜੇ (UNLIKELY (type == CPP_PRAGMA_EOL)
	      && parser->ਵਿੱਚ_omp_attribute_pragma)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      ਜੇ (token->type == CPP_EOF)
		{
		  parser->ਟੋਕਨ = parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ;
		  parser->ਟੋਕਨ_avail
		    = parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ_avail;
		  parser->ਵਿੱਚ_omp_attribute_pragma = ਨਿਰਾ;
		}
	    }
	  ਰੋਕੋ;
	}

      /* If we've run out of tokens, stop.  */
      ਜੇ (token->type == CPP_EOF)
	ਵਾਪਸ;
      ਜੇ (token->type == CPP_PRAGMA_EOL && parser->ਵਿੱਚ_pragma)
	ਵਾਪਸ;
      ਜੇ (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_ਵਰਗਫਲ)
	++nesting_ਡੂੰਘਾਈ;
      ਨਹੀਂਤਾਂ ਜੇ (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_ਵਰਗਫਲ)
	{
	  ਜੇ (nesting_ਡੂੰਘਾਈ-- == 0)
	    ਰੋਕੋ;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = ਝੂਠ;
}

/* Skip tokens until the end of a parameter is found, but do not
   consume the comma, semicolon or closing delimiter.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_parameter (c_parser *parser)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ nesting_ਡੂੰਘਾਈ = 0;

  ਜਦੋਂ (ਸੱਚ)
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ ((token->type == CPP_COMMA || token->type == CPP_SEMICOLON)
	  && !nesting_ਡੂੰਘਾਈ)
	ਰੋਕੋ;
      /* If we've run out of tokens, stop.  */
      ਜੇ (token->type == CPP_EOF)
	ਵਾਪਸ;
      ਜੇ (token->type == CPP_PRAGMA_EOL && parser->ਵਿੱਚ_pragma)
	ਵਾਪਸ;
      ਜੇ (token->type == CPP_OPEN_BRACE
	  || token->type == CPP_OPEN_PAREN
	  || token->type == CPP_OPEN_ਵਰਗਫਲ)
	++nesting_ਡੂੰਘਾਈ;
      ਨਹੀਂਤਾਂ ਜੇ (token->type == CPP_CLOSE_BRACE
	       || token->type == CPP_CLOSE_PAREN
	       || token->type == CPP_CLOSE_ਵਰਗਫਲ)
	{
	  ਜੇ (nesting_ਡੂੰਘਾਈ-- == 0)
	    ਰੋਕੋ;
	}
      /* Consume this token.  */
      c_parser_consume_token (parser);
    }
  parser->error = ਝੂਠ;
}

/* Skip tokens until a non-nested closing curly brace is the next
   token, or there are no more tokens. Return true in the first case,
   false otherwise.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_skip_ਮੰਜ਼ਿਲ_closing_brace (c_parser *parser)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ nesting_ਡੂੰਘਾਈ = 0;

  ਜਦੋਂ (ਸੱਚ)
    {
      c_token *token = c_parser_peek_token (parser);

      ਚੋਣ (token->type)
	{
	ਹਾਲਤ CPP_PRAGMA_EOL:
	  ਜੇ (!parser->ਵਿੱਚ_pragma)
	    ਰੋਕੋ;
	  /* FALLTHRU */
	ਹਾਲਤ CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  ਵਾਪਸ ਝੂਠ;

	ਹਾਲਤ CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested `}', then we have reached
	     the end of the current block.  */
	  ਜੇ (nesting_ਡੂੰਘਾਈ-- == 0)
	    ਵਾਪਸ ਸੱਚ;
	  ਰੋਕੋ;

	ਹਾਲਤ CPP_OPEN_BRACE:
	  /* If it the next token is a `{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_ਡੂੰਘਾਈ;
	  ਰੋਕੋ;

	ਮੂਲ:
	  ਰੋਕੋ;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Expect to be at the end of the pragma directive and consume an
   end of line marker.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (c_parser *parser, ਤਾਰਕਿਕ error_if_not_eol = ਸੱਚ)
{
  gcc_assert (parser->ਵਿੱਚ_pragma);
  parser->ਵਿੱਚ_pragma = ਝੂਠ;

  ਜੇ (error_if_not_eol && c_parser_peek_token (parser)->type != CPP_PRAGMA_EOL)
    c_parser_error (parser, "expected end of line");

  cpp_ttype token_type;
  ਕਰੋ
    {
      c_token *token = c_parser_peek_token (parser);
      token_type = token->type;
      ਜੇ (token_type == CPP_EOF)
	ਰੋਕੋ;
      c_parser_consume_token (parser);
    }
  ਜਦੋਂ (token_type != CPP_PRAGMA_EOL);

  ਜੇ (parser->ਵਿੱਚ_omp_attribute_pragma)
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ (token->type == CPP_EOF)
	{
	  parser->ਟੋਕਨ = parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ;
	  parser->ਟੋਕਨ_avail
	    = parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ_avail;
	  parser->ਵਿੱਚ_omp_attribute_pragma = ਨਿਰਾ;
	}
    }

  parser->error = ਝੂਠ;
}

/* Skip tokens up to and including "#pragma omp end declare variant".
   Properly handle nested "#pragma omp begin declare variant" pragmas.  */
ਸਥਿਰ ਖਾਲੀ
c_parser_skip_ਮੰਜ਼ਿਲ_pragma_omp_ਸਿਰਾ_declare_variant (c_parser *parser)
{
  ਲਈ (ਪੂਰਨ ਡੂੰਘਾਈ = 0; ਡੂੰਘਾਈ >= 0; )
    {
      c_token *token = c_parser_peek_token (parser);

      ਚੋਣ (token->type)
	{
	ਹਾਲਤ CPP_PRAGMA_EOL:
	  ਜੇ (!parser->ਵਿੱਚ_pragma)
	    ਰੋਕੋ;
	  /* FALLTHRU */
	ਹਾਲਤ CPP_EOF:
	  /* If we've run out of tokens, stop.  */
	  ਵਾਪਸ;

	ਹਾਲਤ CPP_PRAGMA:
	  ਜੇ ((token->pragma_ਕਿਸਮ == PRAGMA_OMP_BEGIN
	       || token->pragma_ਕਿਸਮ == PRAGMA_OMP_ਸਿਰਾ)
	      && c_parser_peek_nth_token (parser, 2)->type == CPP_NAME
	      && c_parser_peek_nth_token (parser, 3)->type == CPP_NAME)
	    {
	      ਰੁੱਖ id1 = c_parser_peek_nth_token (parser, 2)->ਮੁੱਲ;
	      ਰੁੱਖ id2 = c_parser_peek_nth_token (parser, 3)->ਮੁੱਲ;
	      ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id1), "declare") == 0
		  && strcmp (IDENTIFIER_ਸੂਚਕ (id2), "variant") == 0)
		{
		  ਜੇ (token->pragma_ਕਿਸਮ == PRAGMA_OMP_BEGIN)
		    ਡੂੰਘਾਈ++;
		  ਨਹੀਂਤਾਂ
		    ਡੂੰਘਾਈ--;
		}
	    }
	  c_parser_consume_pragma (parser);
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਜਾਰੀ;

	ਮੂਲ:
	  ਰੋਕੋ;
	}

      /* Consume the token.  */
      c_parser_consume_token (parser);
    }
}

/* Skip tokens until we have consumed an entire block, or until we
   have consumed a non-nested ';'.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (c_parser *parser,
					    ਤਾਰਕਿਕ metadirective_p = ਝੂਠ)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ nesting_ਡੂੰਘਾਈ = 0;
  ਪੂਰਨ bracket_ਡੂੰਘਾਈ = 0;
  ਤਾਰਕਿਕ save_error = parser->error;

  ਜਦੋਂ (ਸੱਚ)
    {
      c_token *token;

      /* Peek at the next token.  */
      token = c_parser_peek_token (parser);

      ਚੋਣ (token->type)
	{
	ਹਾਲਤ CPP_EOF:
	  ਵਾਪਸ;

	ਹਾਲਤ CPP_PRAGMA_EOL:
	  ਜੇ (parser->ਵਿੱਚ_pragma)
	    ਵਾਪਸ;
	  ਰੋਕੋ;

	ਹਾਲਤ CPP_SEMICOLON:
	  /* If the next token is a ';', we have reached the
	     end of the statement.  */
	  ਜੇ (!nesting_ਡੂੰਘਾਈ && (!metadirective_p || bracket_ਡੂੰਘਾਈ <= 0))
	    {
	      /* Consume the ';'.  */
	      c_parser_consume_token (parser);
	      ਜਾਓ ਮੁਕੰਮਲ;
	    }
	  ਰੋਕੋ;

	ਹਾਲਤ CPP_CLOSE_BRACE:
	  /* If the next token is a non-nested '}', then we have
	     reached the end of the current block.  */
	  ਜੇ ((nesting_ਡੂੰਘਾਈ == 0 || --nesting_ਡੂੰਘਾਈ == 0)
	      && (!metadirective_p || bracket_ਡੂੰਘਾਈ <= 0))
	    {
	      c_parser_consume_token (parser);
	      ਜਾਓ ਮੁਕੰਮਲ;
	    }
	  ਰੋਕੋ;

	ਹਾਲਤ CPP_OPEN_BRACE:
	  /* If it the next token is a '{', then we are entering a new
	     block.  Consume the entire block.  */
	  ++nesting_ਡੂੰਘਾਈ;
	  ਰੋਕੋ;

	ਹਾਲਤ CPP_OPEN_PAREN:
	  /* Track parentheses in case the statement is a standalone 'for'
	     statement - we want to skip over the semicolons separating the
	     operands.  */
	  ਜੇ (metadirective_p && nesting_ਡੂੰਘਾਈ == 0)
	    ++bracket_ਡੂੰਘਾਈ;
	  ਰੋਕੋ;

	ਹਾਲਤ CPP_CLOSE_PAREN:
	  ਜੇ (metadirective_p && nesting_ਡੂੰਘਾਈ == 0)
	    --bracket_ਡੂੰਘਾਈ;
	  ਰੋਕੋ;

	ਹਾਲਤ CPP_PRAGMA:
	  /* If we see a pragma, consume the whole thing at once.  We
	     have some safeguards against consuming pragmas willy-nilly.
	     Normally, we'd expect to be here with parser->error set,
	     which disables these safeguards.  But it's possible to get
	     here for secondary error recovery, after parser->error has
	     been cleared.  */
	  c_parser_consume_pragma (parser);
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  parser->error = save_error;
	  ਜਾਰੀ;

	ਮੂਲ:
	  ਰੋਕੋ;
	}

      c_parser_consume_token (parser);
    }

 ਮੁਕੰਮਲ:
  parser->error = ਝੂਠ;
}

/* CPP's options (initialized by c-opts.cc).  */
ਬਾਹਰੀ cpp_options *cpp_opts;

/* Save the warning flags which are controlled by __extension__.  */

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ
disable_extension_diagnostics (ਖਾਲੀ)
{
  ਪੂਰਨ ret = (pedantic
	     | (warn_ਸੂਚਕ_arith << 1)
	     | (warn_traditional << 2)
	     | (flag_iso << 3)
	     | (warn_long_long << 4)
	     | (warn_cxx_compat << 5)
	     | (warn_overlength_ਲੜੀਆਂ << 6)
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
  warn_ਸੂਚਕ_arith = 0;
  cpp_opts->cpp_warn_traditional = warn_traditional = 0;
  flag_iso = 0;
  cpp_opts->cpp_warn_long_long = warn_long_long = 0;
  warn_cxx_compat = 0;
  warn_overlength_ਲੜੀਆਂ = 0;
  warn_c90_c99_compat = 0;
  warn_c99_c11_compat = 0;
  warn_c11_c23_compat = 0;
  warn_c23_c2y_compat = 0;
  ਵਾਪਸ ret;
}

/* Restore the warning flags which are controlled by __extension__.
   FLAGS is the return value from disable_extension_diagnostics.  */

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ
restore_extension_diagnostics (ਪੂਰਨ flags)
{
  cpp_opts->cpp_pedantic = pedantic = flags & 1;
  warn_ਸੂਚਕ_arith = (flags >> 1) & 1;
  cpp_opts->cpp_warn_traditional = warn_traditional = (flags >> 2) & 1;
  flag_iso = (flags >> 3) & 1;
  cpp_opts->cpp_warn_long_long = warn_long_long = (flags >> 4) & 1;
  warn_cxx_compat = (flags >> 5) & 1;
  warn_overlength_ਲੜੀਆਂ = (flags >> 6) & 1;
  /* See above for why is this needed.  */
  warn_c90_c99_compat = (flags >> 7) & 1 ? 1 : ((flags >> 8) & 1 ? -1 : 0);
  warn_c99_c11_compat = (flags >> 9) & 1 ? 1 : ((flags >> 10) & 1 ? -1 : 0);
  warn_c11_c23_compat = (flags >> 11) & 1 ? 1 : ((flags >> 12) & 1 ? -1 : 0);
  warn_c23_c2y_compat = (flags >> 13) & 1 ? 1 : ((flags >> 14) & 1 ? -1 : 0);
}

/* Helper data structure for parsing #pragma acc routine.  */
ਬਣਤਰ oacc_routine_ਅੰਕੜੇ {
  ਤਾਰਕਿਕ error_ਵੇਖਿਆ; /* Set if error has been reported.  */
  ਤਾਰਕਿਕ fndecl_ਵੇਖਿਆ; /* Set if one fn decl/definition has been seen already.  */
  ਰੁੱਖ clauses;
  location_t loc;
};

/* Used for parsing objc foreach statements.  */
ਸਥਿਰ ਰੁੱਖ objc_foreach_break_label, objc_foreach_continue_label;

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
ਬਣਤਰ omp_for_parse_ਅੰਕੜੇ {
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ;
  ਰੁੱਖ declv, condv, incrv, initv;
  ਰੁੱਖ pre_body;
  ਰੁੱਖ bindings;
  ਪੂਰਨ ਗਿਣਤੀ_2;	/* Expected nesting depth.  */
  ਪੂਰਨ ਡੂੰਘਾਈ;	/* Current nesting depth.  */
  location_t for_loc;
  ਤਾਰਕਿਕ ordered : 1;
  ਤਾਰਕਿਕ inscan : 1;
  ਤਾਰਕਿਕ want_nested_loop : 1;
  ਤਾਰਕਿਕ ਵਿੱਚ_intervening_ਕੋਡ : 1;
  ਤਾਰਕਿਕ saw_intervening_ਕੋਡ: 1;
  ਤਾਰਕਿਕ perfect_nesting_fail : 1;
  ਤਾਰਕਿਕ fail : 1;
};

ਬਣਤਰ attr_state
{
  /* True if we parsed a musttail attribute for return.  */
  ਤਾਰਕਿਕ musttail_p;

  ਖਾਲੀ reset () { musttail_p = ਝੂਠ; }
};

ਸਥਿਰ ਤਾਰਕਿਕ c_parser_nth_token_starts_std_ਗੁਣ (c_parser *,
						      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ);
ਸਥਿਰ ਰੁੱਖ c_parser_std_attribute_specifier_sequence (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_external_declaration (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_asm_definition (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_declaration_or_fndef (c_parser *, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ,
					   ਤਾਰਕਿਕ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ, ਰੁੱਖ * = ਨਿਰਾ,
					   vec<c_token> * = ਨਿਰਾ,
					   ਤਾਰਕਿਕ have_attrs = ਝੂਠ,
					   ਰੁੱਖ attrs = ਨਿਰਾ,
					   ਬਣਤਰ oacc_routine_ਅੰਕੜੇ * = ਨਿਰਾ,
					   ਤਾਰਕਿਕ * = ਨਿਰਾ);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_handle_statement_omp_ਗੁਣ (c_parser *, ਰੁੱਖ &,
						      ਤਾਰਕਿਕ *);
ਸਥਿਰ ਖਾਲੀ c_parser_static_assert_declaration_no_semi (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_static_assert_declaration (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_typespec c_parser_enum_specifier (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_typespec c_parser_struct_or_union_specifier (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_struct_declaration (c_parser *, ਰੁੱਖ *);
ਸਥਿਰ ਬਣਤਰ c_typespec c_parser_typeof_specifier (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_alignas_specifier (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_declarator *c_parser_ਸਿੱਧਾ_declarator (c_parser *, ਤਾਰਕਿਕ,
							c_dtr_syn, ਤਾਰਕਿਕ *);
ਸਥਿਰ ਬਣਤਰ c_declarator *c_parser_ਸਿੱਧਾ_declarator_inner (c_parser *,
							      ਤਾਰਕਿਕ,
							      ਬਣਤਰ c_declarator *);
ਸਥਿਰ ਬਣਤਰ c_arg_info *c_parser_parms_declarator (c_parser *, ਤਾਰਕਿਕ, ਰੁੱਖ,
						     ਤਾਰਕਿਕ);
ਸਥਿਰ ਬਣਤਰ c_arg_info *c_parser_parms_list_declarator (c_parser *, ਰੁੱਖ,
							  ਰੁੱਖ, ਤਾਰਕਿਕ);
ਸਥਿਰ ਬਣਤਰ c_parm *c_parser_parameter_declaration (c_parser *, ਰੁੱਖ, ਤਾਰਕਿਕ);
ਸਥਿਰ ਰੁੱਖ c_parser_asm_string_literal (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_simple_asm_ਵਿਅੰਜਕ (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_gnu_ਗੁਣ (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_initializer (c_parser *, ਰੁੱਖ);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_braced_init (c_parser *, ਰੁੱਖ, ਤਾਰਕਿਕ,
					   ਬਣਤਰ obstack *, ਤਾਰਕਿਕ);
ਸਥਿਰ ਖਾਲੀ c_parser_initelt (c_parser *, ਬਣਤਰ obstack *);
ਸਥਿਰ ਖਾਲੀ c_parser_initval (c_parser *, ਬਣਤਰ c_ਵਿਅੰਜਕ *,
			      ਬਣਤਰ obstack *);
ਸਥਿਰ ਰੁੱਖ c_parser_compound_statement (c_parser *, location_t * = ਨਿਰਾ);
ਸਥਿਰ location_t c_parser_compound_statement_nostart (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_label (c_parser *, ਰੁੱਖ);
ਸਥਿਰ ਖਾਲੀ c_parser_statement (c_parser *, ਤਾਰਕਿਕ *, location_t * = ਨਿਰਾ);
ਸਥਿਰ ਖਾਲੀ c_parser_statement_after_labels (c_parser *, ਤਾਰਕਿਕ *, ਰੁੱਖ,
					     vec<ਰੁੱਖ> * = ਨਿਰਾ,
					     attr_state = {});
ਸਥਿਰ ਰੁੱਖ c_parser_c99_ਖੰਡ_statement (c_parser *, ਤਾਰਕਿਕ *,
					  location_t * = ਨਿਰਾ);
ਸਥਿਰ ਖਾਲੀ c_parser_if_statement (c_parser *, ਤਾਰਕਿਕ *, vec<ਰੁੱਖ> *);
ਸਥਿਰ ਖਾਲੀ c_parser_switch_statement (c_parser *, ਤਾਰਕਿਕ *, ਰੁੱਖ);
ਸਥਿਰ ਖਾਲੀ c_parser_while_statement (c_parser *, ਤਾਰਕਿਕ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ, ਤਾਰਕਿਕ,
				      ਤਾਰਕਿਕ *, ਰੁੱਖ);
ਸਥਿਰ ਖਾਲੀ c_parser_do_statement (c_parser *, ਤਾਰਕਿਕ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ, ਤਾਰਕਿਕ,
				   ਰੁੱਖ);
ਸਥਿਰ ਖਾਲੀ c_parser_for_statement (c_parser *, ਤਾਰਕਿਕ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ, ਤਾਰਕਿਕ,
				    ਤਾਰਕਿਕ *, ਰੁੱਖ);
ਸਥਿਰ ਰੁੱਖ c_parser_asm_statement (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_asm_operands (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_asm_goto_operands (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_asm_clobbers (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_ਵਿਅੰਜਕ_no_commas (c_parser *, ਬਣਤਰ c_ਵਿਅੰਜਕ *,
					      ਰੁੱਖ = NULL_ਰੁੱਖ);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_conditional_ਵਿਅੰਜਕ (c_parser *,
						      ਬਣਤਰ c_ਵਿਅੰਜਕ *, ਰੁੱਖ);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (c_parser *, ਬਣਤਰ c_ਵਿਅੰਜਕ *,
						 ਰੁੱਖ);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_cast_ਵਿਅੰਜਕ (c_parser *, ਬਣਤਰ c_ਵਿਅੰਜਕ *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_unary_ਵਿਅੰਜਕ (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_sizeof_or_countof_ਵਿਅੰਜਕ (c_parser *,
							    ਗਿਣਤੀ rid);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_alignof_ਵਿਅੰਜਕ (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_maxof_or_minof_ਵਿਅੰਜਕ (c_parser *, ਗਿਣਤੀ rid);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_postfix_ਵਿਅੰਜਕ (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_postfix_ਵਿਅੰਜਕ_after_paren_type (c_parser *,
								   ਬਣਤਰ c_declspecs *,
								   ਬਣਤਰ c_type_name *,
								   location_t);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_postfix_ਵਿਅੰਜਕ_after_primary (c_parser *,
								location_t loc,
								ਬਣਤਰ c_ਵਿਅੰਜਕ);
ਸਥਿਰ ਰੁੱਖ c_parser_transaction (c_parser *, ਗਿਣਤੀ rid);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_transaction_ਵਿਅੰਜਕ (c_parser *, ਗਿਣਤੀ rid);
ਸਥਿਰ ਰੁੱਖ c_parser_transaction_cancel (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_ਵਿਅੰਜਕ (c_parser *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_ਵਿਅੰਜਕ_conv (c_parser *);
ਸਥਿਰ vec<ਰੁੱਖ, va_gc> *c_parser_ਵਿਅੰਜਕ_list (c_parser *, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ,
					     vec<ਰੁੱਖ, va_gc> **, location_t *,
					     ਰੁੱਖ *, vec<location_t> *,
					     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ * = ਨਿਰਾ);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_has_attribute_ਵਿਅੰਜਕ (c_parser *);

ਸਥਿਰ ਖਾਲੀ c_parser_oacc_declare (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_oacc_enter_exit_ਅੰਕੜੇ (c_parser *, ਤਾਰਕਿਕ);
ਸਥਿਰ ਖਾਲੀ c_parser_oacc_update (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_construct (c_parser *, ਤਾਰਕਿਕ *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_groupprivate (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_threadprivate (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_barrier (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_depobj (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_flush (c_parser *);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_omp_ਅਗਲਾ_ਟੋਕਨ_can_be_canon_loop (c_parser *,
							ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2, ਤਾਰਕਿਕ);
ਸਥਿਰ ਰੁੱਖ c_parser_omp_loop_nest (c_parser *, ਤਾਰਕਿਕ *);
ਸਥਿਰ ਰੁੱਖ c_parser_omp_for_loop (location_t, c_parser *, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2,
				   ਰੁੱਖ, ਰੁੱਖ *, ਤਾਰਕਿਕ *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_taskwait (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_taskyield (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_cancel (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_nothing (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_metadirective (c_parser *, ਤਾਰਕਿਕ *);

ਗਿਣਤੀ pragma_context { pragma_external, pragma_struct, pragma_param,
		      pragma_stmt, pragma_compound };
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_pragma (c_parser *, ਗਿਣਤੀ pragma_context, ਤਾਰਕਿਕ *, ਰੁੱਖ);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_omp_cancellation_ਬਿੰਦੂ (c_parser *, ਗਿਣਤੀ pragma_context);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_omp_ਨਿਸ਼ਾਨਾ (c_parser *, ਗਿਣਤੀ pragma_context, ਤਾਰਕਿਕ *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_begin (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_ਸਿਰਾ (c_parser *);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_omp_declare (c_parser *, ਗਿਣਤੀ pragma_context);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_requires (c_parser *);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_omp_error (c_parser *, ਗਿਣਤੀ pragma_context);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_assumption_clauses (c_parser *, ਤਾਰਕਿਕ);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_allocate (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_assumes (c_parser *);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_omp_ordered (c_parser *, ਗਿਣਤੀ pragma_context, ਤਾਰਕਿਕ *);
ਸਥਿਰ ਰੁੱਖ c_parser_omp_dispatch (location_t, c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_omp_interop (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_oacc_routine (c_parser *, ਗਿਣਤੀ pragma_context);

/* These Objective-C parser functions are only ever called when
   compiling Objective-C.  */
ਸਥਿਰ ਖਾਲੀ c_parser_objc_class_definition (c_parser *, ਰੁੱਖ);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_class_instance_variables (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_class_declaration (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_alias_declaration (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_protocol_definition (c_parser *, ਰੁੱਖ);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_objc_ਵਿਧੀ_type (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_ਵਿਧੀ_definition (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_methodprotolist (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_methodproto (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_objc_ਵਿਧੀ_decl (c_parser *, ਤਾਰਕਿਕ, ਰੁੱਖ *, ਰੁੱਖ *);
ਸਥਿਰ ਰੁੱਖ c_parser_objc_type_name (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_objc_protocol_refs (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_try_catch_finally_statement (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_synchronized_statement (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_objc_selector (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_objc_selector_arg (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_objc_receiver (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_objc_ਸੁਨੇਹਾ_ਦਲੀਲਾਂ (c_parser *);
ਸਥਿਰ ਰੁੱਖ c_parser_objc_keywordexpr (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_at_property_declaration (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_at_synthesize_declaration (c_parser *);
ਸਥਿਰ ਖਾਲੀ c_parser_objc_at_dynamic_declaration (c_parser *);
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_objc_diagnose_bad_element_ਅਗੇਤਰ
  (c_parser *, ਬਣਤਰ c_declspecs *);
ਸਥਿਰ location_t c_parser_parse_rtl_body (c_parser *, ਅੱਖਰ *);
ਸਥਿਰ ਰੁੱਖ c_parser_handle_musttail (c_parser *, ਰੁੱਖ, attr_state &);

#ਜੇ ENABLE_ANALYZER

ਨਾਮਾਕਾਸ਼ ana {

/* Concrete implementation of ana::translation_unit for the C frontend.  */

ਵਰਗ c_translation_unit : ਜਨਤਕ translation_unit
{
ਜਨਤਕ:
  /* Implementation of translation_unit::lookup_constant_by_id for use by the
     analyzer to look up named constants in the user's source code.  */
  ਰੁੱਖ lookup_constant_by_id (ਰੁੱਖ id) ਅਚਲ final override
  {
    /* Consider decls.  */
    ਜੇ (ਰੁੱਖ decl = lookup_name (id))
      ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == CONST_DECL)
	ਜੇ (ਰੁੱਖ ਮੁੱਲ = DECL_INITIAL (decl))
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == INTEGER_CST)
	    ਵਾਪਸ ਮੁੱਲ;

    /* Consider macros.  */
    cpp_hashnode *hashnode = C_CPP_HASHNODE (id);
    ਜੇ (cpp_macro_p (hashnode))
      ਜੇ (ਰੁੱਖ ਮੁੱਲ = consider_macro (hashnode->ਮੁੱਲ.macro))
	ਵਾਪਸ ਮੁੱਲ;

    ਵਾਪਸ NULL_ਰੁੱਖ;
  }

  ਰੁੱਖ
  lookup_type_by_id (ਰੁੱਖ id) ਅਚਲ final override
  {
    ਜੇ (ਰੁੱਖ type_decl = lookup_name (id))
	ਜੇ (ਰੁੱਖ_ਕੋਡ (type_decl) == TYPE_DECL)
	  {
	    ਰੁੱਖ ਰਿਕਾਰਡ_type = ਰੁੱਖ_TYPE (type_decl);
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰਿਕਾਰਡ_type) == ਰਿਕਾਰਡ_TYPE)
	      ਵਾਪਸ ਰਿਕਾਰਡ_type;
	  }

    ਵਾਪਸ NULL_ਰੁੱਖ;
  }

  ਰੁੱਖ
  lookup_global_var_by_id (ਰੁੱਖ id) ਅਚਲ final override
  {
    ਜੇ (ਰੁੱਖ var_decl = lookup_name (id))
      ਜੇ (ਰੁੱਖ_ਕੋਡ (var_decl) == VAR_DECL)
				ਵਾਪਸ var_decl;

    ਵਾਪਸ NULL_ਰੁੱਖ;
  }

ਨਿਜੀ:
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
  ਰੁੱਖ consider_macro (cpp_macro *macro, ਪੂਰਨ ਡੂੰਘਾਈ = 0) ਅਚਲ
  {
    /* UInteger option variables are stored as int, so "depth" must be signed
       to avoid a signed/unsigned comparison here. */
    gcc_assert (ਡੂੰਘਾਈ >= 0);

    ਜੇ (macro->paramc > 0)
      ਵਾਪਸ NULL_ਰੁੱਖ;
    ਜੇ (macro->ਕਿਸਮ != cmk_macro)
      ਵਾਪਸ NULL_ਰੁੱਖ;
    ਜੇ (macro->ਗਿਣਤੀ_2 != 1)
      ਵਾਪਸ NULL_ਰੁੱਖ;
    ਅਚਲ cpp_token &tok = macro->ਘਾਤਾਂਕ.ਟੋਕਨ[0];
    ਜੇ (tok.type == CPP_NAME)
      {
	/* Limit recursion.  */
	ਜੇ (ਡੂੰਘਾਈ >= param_analyzer_max_macro_alias_ਡੂੰਘਾਈ)
	  ਵਾਪਸ NULL_ਰੁੱਖ;

	cpp_hashnode *alias = tok.val.ਗੰਢ.ਗੰਢ;
	ਜੇ (cpp_macro_p (alias))
	  ਵਾਪਸ consider_macro (alias->ਮੁੱਲ.macro, ਡੂੰਘਾਈ + 1);

	/* Not a simple alias.  */
	ਵਾਪਸ NULL_ਰੁੱਖ;
      }
    ਨਹੀਂਤਾਂ ਜੇ (tok.type != CPP_ਸੰਖਿਆ)
      ਵਾਪਸ NULL_ਰੁੱਖ;

    cpp_reader *old_parse_ਵਿੱਚ = parse_ਵਿੱਚ;
    parse_ਵਿੱਚ = cpp_create_reader (CLK_GNUC89, ਨਿਰਾ, ਸਤਰ_ਸਾਰਣੀ);

    pretty_printer pp;
    pp_string (&pp, (ਅਚਲ ਅੱਖਰ *) tok.val.str.ਪਾਠ);
    pp_newline (&pp);
    cpp_ਧੱਕੋ_ਬਫਰ (parse_ਵਿੱਚ,
		     (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) pp_formatted_ਪਾਠ (&pp),
		     ਲੜੀ_ਲੰਬਾਈ (pp_formatted_ਪਾਠ (&pp)),
		     0);

    ਰੁੱਖ ਮੁੱਲ;
    location_t loc;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ cpp_flags;
    c_lex_with_flags (&ਮੁੱਲ, &loc, &cpp_flags, 0);

    cpp_destroy (parse_ਵਿੱਚ);
    parse_ਵਿੱਚ = old_parse_ਵਿੱਚ;

    ਜੇ (ਮੁੱਲ && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == INTEGER_CST)
      ਵਾਪਸ ਮੁੱਲ;

    ਵਾਪਸ NULL_ਰੁੱਖ;
  }
};

} // namespace ana

#ਜੇ_ਅੰਤ /* #if ENABLE_ANALYZER */

/* Parse a translation unit (C90 6.7, C99 6.9, C11 6.9).

   translation-unit:
     external-declarations

   external-declarations:
     external-declaration
     external-declarations external-declaration

   GNU extensions:

   translation-unit:
ਖਾਲੀ_ਥਾਵਾਂ
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_translation_unit (c_parser *parser)
{
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EOF))
    {
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C forbids an empty translation unit");
    }
  ਨਹੀਂਤਾਂ
    {
      ਖਾਲੀ *obstack_position = obstack_alloc (&parser_obstack, 0);
      mark_valid_location_for_stdc_pragma (ਝੂਠ);
      ਕਰੋ
	{
	  ggc_collect ();
	  c_parser_external_declaration (parser);
	  obstack_free (&parser_obstack, obstack_position);
	}
      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_EOF));
    }

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
  ਰੁੱਖ decl;
  FOR_EACH_VEC_ELT (incomplete_ਰਿਕਾਰਡ_decls, i, decl)
    ਜੇ (DECL_ਮਾਪ (decl) == NULL_ਰੁੱਖ && ਰੁੱਖ_TYPE (decl) != error_mark_ਗੰਢ)
      error ("storage size of %q+D isn%'t known", decl);

  ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute))
    {
      c_omp_declare_ਨਿਸ਼ਾਨਾ_attr
	a = current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute->ਕੱਢੋ ();
      ਜੇ (!errorcount)
	error ("%qs without corresponding %qs",
	       a.device_type >= 0 ? "#pragma omp begin declare target"
				  : "#pragma omp declare target",
	       "#pragma omp end declare target");
      vec_ਸੁਰੱਖਿਅਤ_truncate (current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute, 0);
    }
  ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (current_omp_begin_assumes))
    {
      ਜੇ (!errorcount)
	error ("%qs without corresponding %qs",
	       "#pragma omp begin assumes", "#pragma omp end assumes");
      vec_ਸੁਰੱਖਿਅਤ_truncate (current_omp_begin_assumes, 0);
    }
  ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (current_omp_declare_variant_attribute))
    {
      ਜੇ (!errorcount)
	error ("%<omp begin declare variant%> without corresponding "
	       "%<omp end declare variant%>");
      vec_ਸੁਰੱਖਿਅਤ_truncate (current_omp_declare_variant_attribute, 0);
    }
  ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (omp_begin_declare_variant_map))
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
      omp_begin_declare_variant_map_ਇੰਦਰਾਜ *e;
      FOR_EACH_VEC_ELT (*omp_begin_declare_variant_map, i, e)
	omp_ਅੰਤ_variant_function (e->variant, e->id, e->ctx);
      vec_ਸੁਰੱਖਿਅਤ_truncate (omp_begin_declare_variant_map, 0);
    }

#ਜੇ ENABLE_ANALYZER
  ਜੇ (flag_analyzer)
    {
      ana::c_translation_unit tu;
      ana::on_ਅੰਤ_translation_unit (tu);
    }
#ਜੇ_ਅੰਤ
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

ਸਥਿਰ ਖਾਲੀ
c_parser_external_declaration (c_parser *parser)
{
  ਪੂਰਨ ext;
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_KEYWORD:
      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_ASM:
	  c_parser_asm_definition (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_INTERFACE:
	ਹਾਲਤ RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_definition (parser, NULL_ਰੁੱਖ);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_protocol_definition (parser, NULL_ਰੁੱਖ);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_PROPERTY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_property_declaration (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_SYNTHESIZE:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_synthesize_declaration (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_DYNAMIC:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_at_dynamic_declaration (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_ਸਿਰਾ:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_ਅੰਤ_implementation ();
	  ਰੋਕੋ;
	ਮੂਲ:
	  ਜਾਓ decl_or_fndef;
	}
      ਰੋਕੋ;
    ਹਾਲਤ CPP_SEMICOLON:
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_PRAGMA:
      mark_valid_location_for_stdc_pragma (ਸੱਚ);
      c_parser_pragma (parser, pragma_external, ਨਿਰਾ, NULL_ਰੁੱਖ);
      mark_valid_location_for_stdc_pragma (ਝੂਠ);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_PLUS:
    ਹਾਲਤ CPP_MINUS:
      ਜੇ (c_dialect_objc ())
	{
	  c_parser_objc_ਵਿਧੀ_definition (parser);
	  ਰੋਕੋ;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
      /* FALLTHRU */
    ਮੂਲ:
    decl_or_fndef:
      /* A declaration or a function definition (or, in Objective-C,
	 an @interface or @protocol with prefix attributes).  We can
	 only tell which after parsing the declaration specifiers, if
	 any, and the first declarator.  */
      c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਝੂਠ, ਸੱਚ,
				     ਝੂਠ);
      ਰੋਕੋ;
    }
}

ਸਥਿਰ ਖਾਲੀ c_parser_handle_directive_omp_ਗੁਣ (ਰੁੱਖ &, vec<c_token> *&,
						      vec<c_token> *);
ਸਥਿਰ ਖਾਲੀ c_ਅੰਤ_omp_declare_simd (c_parser *, ਰੁੱਖ, ਰੁੱਖ, vec<c_token> *);
ਸਥਿਰ ਖਾਲੀ c_ਅੰਤ_oacc_routine (ਬਣਤਰ oacc_routine_ਅੰਕੜੇ *, ਰੁੱਖ, ਤਾਰਕਿਕ);

/* Build and add a DEBUG_BEGIN_STMT statement with location LOC.  */

ਸਥਿਰ ਖਾਲੀ
ਜੋੜੋ_debug_begin_stmt (location_t loc)
{
  /* Don't add DEBUG_BEGIN_STMTs outside of functions, see PR84721.  */
  ਜੇ (!MAY_HAVE_DEBUG_MARKER_STMTS || !building_stmt_list_p ())
    ਵਾਪਸ;

  ਰੁੱਖ stmt = build0 (DEBUG_BEGIN_STMT, void_type_ਗੰਢ);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);
}

/* Helper function for c_parser_declaration_or_fndef and
   Handle assume attribute(s).  */

ਸਥਿਰ ਰੁੱਖ
handle_assume_attribute (location_t ਇੱਥੇ, ਰੁੱਖ attrs, ਤਾਰਕਿਕ nested)
{
  ਜੇ (nested)
    ਲਈ (ਰੁੱਖ attr = lookup_attribute ("gnu", "assume", attrs); attr;
	 attr = lookup_attribute ("gnu", "assume", ਰੁੱਖ_CHAIN (attr)))
      {
	ਰੁੱਖ ਦਲੀਲਾਂ = ਰੁੱਖ_ਮੁੱਲ (attr);
	ਪੂਰਨ nargs = list_ਲੰਮਾਈ (ਦਲੀਲਾਂ);
	ਜੇ (nargs != 1)
	  {
	    error_at (ਇੱਥੇ, "wrong number of arguments specified "
			    "for %qE attribute",
		      get_attribute_name (attr));
	    inform (ਇੱਥੇ, "expected %i, found %i", 1, nargs);
	  }
	ਨਹੀਂਤਾਂ
	  {
	    ਰੁੱਖ arg = ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ);
	    arg = c_objc_common_truthvalue_conversion (ਇੱਥੇ, arg);
	    arg = c_fully_fold (arg, ਝੂਠ, ਨਿਰਾ);
	    ਜੇ (arg != error_mark_ਗੰਢ)
	      {
		ਰੁੱਖ fn = build_call_ਵਿਅੰਜਕ_ਅੰਦਰੂਨੀ_loc (ਇੱਥੇ, IFN_ASSUME,
							void_type_ਗੰਢ, 1,
							arg);
		ਜੋੜੋ_stmt (fn);
	      }
	  }
      }
  ਨਹੀਂਤਾਂ
    pedwarn (ਇੱਥੇ, OPT_Wattributes,
	     "%<assume%> attribute at top level");

  ਵਾਪਸ remove_attribute ("gnu", "assume", attrs);
}

/* We might need to reclassify any previously-lexed identifier, e.g.
   when we've left a for loop with an if-statement without else in the
   body - we might have used a wrong scope for the token.  See PR67784.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_maybe_reclassify_token (c_parser *parser)
{
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      c_token *token = c_parser_peek_token (parser);

      ਜੇ (token->id_ਕਿਸਮ == C_ID_ID || token->id_ਕਿਸਮ == C_ID_TYPENAME)
	{
	  ਰੁੱਖ decl = lookup_name (token->ਮੁੱਲ);

	  token->id_ਕਿਸਮ = C_ID_ID;
	  ਜੇ (decl)
	    {
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == TYPE_DECL)
		token->id_ਕਿਸਮ = C_ID_TYPENAME;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_dialect_objc ())
	    {
	      ਰੁੱਖ objc_interface_decl = objc_is_class_name (token->ਮੁੱਲ);
	      /* Objective-C class names are in the same namespace as
		 variables and typedefs, and hence are shadowed by local
		 declarations.  */
	      ਜੇ (objc_interface_decl)
		{
		  token->ਮੁੱਲ = objc_interface_decl;
		  token->id_ਕਿਸਮ = C_ID_CLASSNAME;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_declaration_or_fndef (c_parser *parser, ਤਾਰਕਿਕ fndef_ok,
			       ਤਾਰਕਿਕ static_assert_ok, ਤਾਰਕਿਕ ਖਾਲੀ_ਥਾਵਾਂ_ok,
			       ਤਾਰਕਿਕ nested, ਤਾਰਕਿਕ ਸ਼ੁਰੂ_attr_ok,
			       ਤਾਰਕਿਕ simple_ok,
			       ਰੁੱਖ *objc_foreach_object_declaration
			       /* = NULL */,
			       vec<c_token> *omp_declare_simd_clauses
			       /* = NULL */,
			       ਤਾਰਕਿਕ have_attrs /* = false */,
			       ਰੁੱਖ attrs /* = NULL_TREE */,
			       ਬਣਤਰ oacc_routine_ਅੰਕੜੇ *oacc_routine_ਅੰਕੜੇ
			       /* = NULL */,
			       ਤਾਰਕਿਕ *fallthru_attr_p /* = NULL */)
{
  ਬਣਤਰ c_declspecs *specs;
  ਰੁੱਖ ਅਗੇਤਰ_attrs;
  ਰੁੱਖ all_ਅਗੇਤਰ_attrs;
  ਤਾਰਕਿਕ diagnosed_no_specs = ਝੂਠ;
  location_t ਇੱਥੇ = c_parser_peek_token (parser)->location;
  ਰੁੱਖ ਨਤੀਜਾ = NULL_ਰੁੱਖ;

  ਜੋੜੋ_debug_begin_stmt (c_parser_peek_token (parser)->location);

  ਜੇ (static_assert_ok
      && c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration (parser);
      ਵਾਪਸ ਨਤੀਜਾ;
    }
  specs = build_null_declspecs ();

  /* Handle any standard attributes parsed in the caller.  */
  ਜੇ (have_attrs)
    {
      declspecs_ਜੋੜੋ_attrs (ਇੱਥੇ, specs, attrs);
      specs->non_std_attrs_ਵੇਖਿਆ_p = ਝੂਠ;
    }

  /* Try to detect an unknown type name when we have "A B" or "A *B".  */
  ਜੇ (c_parser_peek_token (parser)->type == CPP_NAME
      && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID
      && (c_parser_peek_2nd_token (parser)->type == CPP_NAME
          || c_parser_peek_2nd_token (parser)->type == CPP_MULT)
      && (!nested || !lookup_name (c_parser_peek_token (parser)->ਮੁੱਲ)))
    {
      ਰੁੱਖ name = c_parser_peek_token (parser)->ਮੁੱਲ;

      /* Issue a warning about NAME being an unknown type name, perhaps
	 with some kind of hint.
	 If the user forgot a "struct" etc, suggest inserting
	 it.  Otherwise, attempt to look for misspellings.  */
      gcc_rich_location richloc (ਇੱਥੇ);
      ਜੇ (ਟੈਗ_exists_p (ਰਿਕਾਰਡ_TYPE, name))
	{
	  /* This is not C++ with its implicit typedef.  */
	  richloc.ਜੋੜੋ_fixit_ਪਾਓ_before ("struct ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<struct%> keyword to refer to the type",
		    name);
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਟੈਗ_exists_p (UNION_TYPE, name))
	{
	  richloc.ਜੋੜੋ_fixit_ਪਾਓ_before ("union ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<union%> keyword to refer to the type",
		    name);
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਟੈਗ_exists_p (ENUMERAL_TYPE, name))
	{
	  richloc.ਜੋੜੋ_fixit_ਪਾਓ_before ("enum ");
	  error_at (&richloc,
		    "unknown type name %qE;"
		    " use %<enum%> keyword to refer to the type",
		    name);
	}
      ਨਹੀਂਤਾਂ
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  name_hint hint = lookup_name_fuzzy (name, FUZZY_LOOKUP_TYPENAME,
					      ਇੱਥੇ);
	  ਜੇ (ਅਚਲ ਅੱਖਰ *suggestion = hint.suggestion ())
	    {
	      richloc.ਜੋੜੋ_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			name, suggestion);
	    }
	  ਨਹੀਂਤਾਂ
	    error_at (ਇੱਥੇ, "unknown type name %qE", name);
	}

      /* Parse declspecs normally to get a correct pointer type, but avoid
         a further "fails to be a type name" error.  Refuse nested functions
         since it is not how the user likely wants us to recover.  */
      c_parser_peek_token (parser)->type = CPP_KEYWORD;
      c_parser_peek_token (parser)->keyword = RID_VOID;
      c_parser_peek_token (parser)->ਮੁੱਲ = error_mark_ਗੰਢ;
      fndef_ok = !nested;
    }

  /* When there are standard attributes at the start of the
     declaration (to apply to the entity being declared), an
     init-declarator-list or function definition must be present.  */
  ਜੇ (c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
    have_attrs = ਸੱਚ;

  c_parser_declspecs (parser, specs, ਸੱਚ, ਸੱਚ, ਸ਼ੁਰੂ_attr_ok,
		      ਸੱਚ, ਸੱਚ, ਸ਼ੁਰੂ_attr_ok, ਸੱਚ, cla_nonabstract_decl);
  ਜੇ (parser->error)
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
      ਵਾਪਸ ਨਤੀਜਾ;
    }
  ਜੇ (nested && !specs->declspecs_ਵੇਖਿਆ_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
      ਵਾਪਸ ਨਤੀਜਾ;
    }

  ਅੰਤ_declspecs (specs);
  /* When the decl is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ਜੇ (specs->typespec_ਕਿਸਮ == ctsk_tagdef)
    verify_counted_by_for_ਸਿਖਰ_anonymous_type (specs->type);

  ਤਾਰਕਿਕ gnu_auto_type_p = specs->typespec_ਸ਼ਬਦ == cts_auto_type;
  ਤਾਰਕਿਕ std_auto_type_p = specs->c23_auto_p;
  ਤਾਰਕਿਕ any_auto_type_p = gnu_auto_type_p || std_auto_type_p;
  gcc_assert (!(gnu_auto_type_p && std_auto_type_p));
  ਅਚਲ ਅੱਖਰ *auto_type_keyword = gnu_auto_type_p ? "__auto_type" : "auto";
  ਜੇ (specs->constexpr_p)
    {
      /* An underspecified declaration may not declare tags or members
	 or structures or unions; it is undefined behavior to declare
	 the members of an enumeration.  Where the structure, union or
	 enumeration type is declared within an initializer, this is
	 diagnosed elsewhere.  Diagnose here the case of declaring
	 such a type in the type specifiers of a constexpr
	 declaration.  */
      ਚੋਣ (specs->typespec_ਕਿਸਮ)
	{
	ਹਾਲਤ ctsk_tagfirstref:
	ਹਾਲਤ ctsk_tagfirstref_attrs:
	  error_at (ਇੱਥੇ, "%qT declared in underspecified object declaration",
		    specs->type);
	  ਰੋਕੋ;

	ਹਾਲਤ ctsk_tagdef:
	  error_at (ਇੱਥੇ, "%qT defined in underspecified object declaration",
		    specs->type);
	  ਰੋਕੋ;

	ਮੂਲ:
	  ਰੋਕੋ;
	}
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      ਤਾਰਕਿਕ handled_assume = ਝੂਠ;
      ਜੇ (specs->attrs
	  && !nested
	  && specs->typespec_ਕਿਸਮ == ctsk_none
	  && c_parser_handle_statement_omp_ਗੁਣ (parser, specs->attrs,
						       ਨਿਰਾ))
	{
	  ਜੇ (specs->attrs)
	    c_warn_ਅਣਵਰਤਿਆ_ਗੁਣ (specs->attrs);
	  ਜਦੋਂ (parser->ਵਿੱਚ_omp_attribute_pragma)
	    {
	      gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA));
	      c_parser_pragma (parser, pragma_external, ਨਿਰਾ, NULL_ਰੁੱਖ);
	    }
	  c_parser_consume_token (parser);
	  ਵਾਪਸ ਨਤੀਜਾ;
	}
      ਜੇ (specs->typespec_ਕਿਸਮ == ctsk_none
	  && lookup_attribute ("gnu", "assume", specs->attrs))
	{
	  handled_assume = ਸੱਚ;
	  specs->attrs
	    = handle_assume_attribute (ਇੱਥੇ, specs->attrs, nested);
	}
      ਜੇ (any_auto_type_p)
	error_at (ਇੱਥੇ, "%qs in empty declaration", auto_type_keyword);
      ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਕਿਸਮ == ctsk_none
	       && attribute_fallthrough_p (specs->attrs))
	{
	  ਜੇ (fallthru_attr_p != ਨਿਰਾ)
	    *fallthru_attr_p = ਸੱਚ;
	  ਜੇ (nested)
	    {
	      ਰੁੱਖ fn = build_call_ਵਿਅੰਜਕ_ਅੰਦਰੂਨੀ_loc (ਇੱਥੇ, IFN_FALLTHROUGH,
						      void_type_ਗੰਢ, 0);
	      ਜੋੜੋ_stmt (fn);
	    }
	  ਨਹੀਂਤਾਂ
	    pedwarn (ਇੱਥੇ, OPT_Wattributes,
		     "%<fallthrough%> attribute at top level");
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਖਾਲੀ_ਥਾਵਾਂ_ok
	       && !(have_attrs && specs->non_std_attrs_ਵੇਖਿਆ_p)
	       && !handled_assume)
	shadow_ਟੈਗ (specs);
      ਨਹੀਂਤਾਂ
	{
	  shadow_ਟੈਗ_warned (specs, 1);
	  ਜੇ (!handled_assume)
	    pedwarn (ਇੱਥੇ, 0, "empty declaration");
	}
      /* We still have to evaluate size expressions.  */
      ਜੇ (specs->ਵਿਅੰਜਕ)
	ਜੋੜੋ_stmt (fold_convert (void_type_ਗੰਢ, specs->ਵਿਅੰਜਕ));
      c_parser_consume_token (parser);
      ਜੇ (oacc_routine_ਅੰਕੜੇ)
	c_ਅੰਤ_oacc_routine (oacc_routine_ਅੰਕੜੇ, NULL_ਰੁੱਖ, ਝੂਠ);
      ਵਾਪਸ ਨਤੀਜਾ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (specs->typespec_ਕਿਸਮ == ctsk_none
	   && nested
	   /* Only parse __attribute__((musttail)) when called from
	      c_parser_compound_statement_nostart.  This certainly isn't
	      a declaration in that case, but we don't do tentative parsing
	      of GNU attributes right now.  */
	   && fallthru_attr_p
	   && c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_RETURN))
    {
      attr_state astate = {};
      specs->attrs = c_parser_handle_musttail (parser, specs->attrs, astate);
      ਜੇ (astate.musttail_p)
	{
	  ਜੇ (specs->attrs)
	    {
	      auto_urlify_ਗੁਣ sentinel;
	      warning_at (c_parser_peek_token (parser)->location,
			  OPT_Wattributes,
			  "attribute %<musttail%> mixed with other attributes "
			  "on %<return%> statement");
	    }
	  c_parser_statement_after_labels (parser, ਨਿਰਾ, NULL_ਰੁੱਖ, ਨਿਰਾ,
					   astate);
	  ਵਾਪਸ ਨਤੀਜਾ;
	}
    }

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ਜੇ (ਖਾਲੀ_ਥਾਵਾਂ_ok
      && specs->typespec_ਕਿਸਮ == ctsk_tagdef
      && c_parser_ਅਗਲਾ_token_starts_declspecs (parser)
      && !c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = ਝੂਠ;
      shadow_ਟੈਗ_warned (specs, 1);
      ਵਾਪਸ ਨਤੀਜਾ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_dialect_objc () && !any_auto_type_p)
    {
      /* Prefix attributes are an error on method decls.  */
      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	  ਹਾਲਤ CPP_PLUS:
	  ਹਾਲਤ CPP_MINUS:
	    ਜੇ (c_parser_objc_diagnose_bad_element_ਅਗੇਤਰ (parser, specs))
	      ਵਾਪਸ ਨਤੀਜਾ;
	    ਜੇ (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			    OPT_Wattributes,
	       		    "prefix attributes are ignored for methods");
		specs->attrs = NULL_ਰੁੱਖ;
	      }
	    ਜੇ (fndef_ok)
	      c_parser_objc_ਵਿਧੀ_definition (parser);
	    ਨਹੀਂਤਾਂ
	      c_parser_objc_methodproto (parser);
	    ਵਾਪਸ ਨਤੀਜਾ;
	    ਰੋਕੋ;
	  ਮੂਲ:
	    ਰੋਕੋ;
	}
      /* This is where we parse 'attributes @interface ...',
	 'attributes @implementation ...', 'attributes @protocol ...'
	 (where attributes could be, for example, __attribute__
	 ((deprecated)).
      */
      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_AT_INTERFACE:
	  {
	    ਜੇ (c_parser_objc_diagnose_bad_element_ਅਗੇਤਰ (parser, specs))
	      ਵਾਪਸ ਨਤੀਜਾ;
	    c_parser_objc_class_definition (parser, specs->attrs);
	    ਵਾਪਸ ਨਤੀਜਾ;
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_IMPLEMENTATION:
	  {
	    ਜੇ (c_parser_objc_diagnose_bad_element_ਅਗੇਤਰ (parser, specs))
	      ਵਾਪਸ ਨਤੀਜਾ;
	    ਜੇ (specs->attrs)
	      {
		warning_at (c_parser_peek_token (parser)->location,
			OPT_Wattributes,
			"prefix attributes are ignored for implementations");
		specs->attrs = NULL_ਰੁੱਖ;
	      }
	    c_parser_objc_class_definition (parser, NULL_ਰੁੱਖ);
	    ਵਾਪਸ ਨਤੀਜਾ;
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_PROTOCOL:
	  {
	    ਜੇ (c_parser_objc_diagnose_bad_element_ਅਗੇਤਰ (parser, specs))
	      ਵਾਪਸ ਨਤੀਜਾ;
	    c_parser_objc_protocol_definition (parser, specs->attrs);
	    ਵਾਪਸ ਨਤੀਜਾ;
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_ALIAS:
	ਹਾਲਤ RID_AT_CLASS:
	ਹਾਲਤ RID_AT_ਸਿਰਾ:
	ਹਾਲਤ RID_AT_PROPERTY:
	  ਜੇ (specs->attrs)
	    {
	      c_parser_error (parser, "unexpected attribute");
	      specs->attrs = ਨਿਰਾ;
	    }
	  ਰੋਕੋ;
	ਮੂਲ:
	  ਰੋਕੋ;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (attribute_fallthrough_p (specs->attrs))
    warning_at (ਇੱਥੇ, OPT_Wattributes,
		"%<fallthrough%> attribute not followed by %<;%>");
  ਨਹੀਂਤਾਂ ਜੇ (lookup_attribute ("gnu", "assume", specs->attrs))
    warning_at (ਇੱਥੇ, OPT_Wattributes,
		"%<assume%> attribute not followed by %<;%>");

  auto_vec<c_token> omp_declare_simd_attr_clauses;
  c_parser_handle_directive_omp_ਗੁਣ (specs->attrs,
					    omp_declare_simd_clauses,
					    &omp_declare_simd_attr_clauses);
  pending_xref_error ();
  ਅਗੇਤਰ_attrs = specs->attrs;
  all_ਅਗੇਤਰ_attrs = ਅਗੇਤਰ_attrs;
  specs->attrs = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ ਹੋਰ_than_one_decl = ਝੂਠ;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਬਣਤਰ c_declarator *declarator;
      ਤਾਰਕਿਕ dummy = ਝੂਠ;
      timevar_id_t tv;
      ਰੁੱਖ fnbody = NULL_ਰੁੱਖ;
      ਰੁੱਖ underspec_name = NULL_ਰੁੱਖ;
      auto_vec<c_token> omp_dsimd_idattr_clauses;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser,
					specs->typespec_ਕਿਸਮ != ctsk_none,
					C_DTR_ਸਾਧਾਰਨ, &dummy);
      ਜੇ (declarator == ਨਿਰਾ)
	{
	  ਜੇ (omp_declare_simd_clauses)
	    c_ਅੰਤ_omp_declare_simd (parser, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ,
				       omp_declare_simd_clauses);
	  ਜੇ (oacc_routine_ਅੰਕੜੇ)
	    c_ਅੰਤ_oacc_routine (oacc_routine_ਅੰਕੜੇ, NULL_ਰੁੱਖ, ਝੂਠ);
	  /* This check is here purely to improve the diagnostic.  */
	  ਜੇ (!simple_ok)
	    c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
	  ਵਾਪਸ ਨਤੀਜਾ;
	}
      ਜੇ (flag_openmp || flag_openmp_simd)
	{
	  ਬਣਤਰ c_declarator *d = declarator;
	  ਜਦੋਂ (d->ਕਿਸਮ != cdk_id)
	    d = d->declarator;
	  vec<c_token> *dummy = ਨਿਰਾ;
	  c_parser_handle_directive_omp_ਗੁਣ (d->u.id.attrs, dummy,
						    &omp_dsimd_idattr_clauses);
	}
      ਜੇ (gnu_auto_type_p && declarator->ਕਿਸਮ != cdk_id)
	{
	  error_at (ਇੱਥੇ,
		    "%<__auto_type%> requires a plain identifier"
		    " as declarator");
	  c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
	  ਵਾਪਸ ਨਤੀਜਾ;
	}
      ਜੇ (std_auto_type_p)
	{
	  ਬਣਤਰ c_declarator *d = declarator;
	  ਜਦੋਂ (d->ਕਿਸਮ == cdk_attrs)
	    d = d->declarator;
	  ਜੇ (d->ਕਿਸਮ != cdk_id)
	    {
	      error_at (ਇੱਥੇ,
			"%<auto%> requires a plain identifier, possibly with"
			" attributes, as declarator");
	      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
	      ਵਾਪਸ ਨਤੀਜਾ;
	    }
	  underspec_name = d->u.id.id;
	}
      ਨਹੀਂਤਾਂ ਜੇ (specs->constexpr_p)
	{
	  ਬਣਤਰ c_declarator *d = declarator;
	  ਜਦੋਂ (d->ਕਿਸਮ != cdk_id)
	    d = d->declarator;
	  underspec_name = d->u.id.id;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EQ)
	  || c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  || c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)
	  || c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ASM)
	  || c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE)
	  || c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ਵਿੱਚ))
	{
	  ਰੁੱਖ asm_name = NULL_ਰੁੱਖ;
	  ਰੁੱਖ postfix_attrs = NULL_ਰੁੱਖ;
	  ਜੇ (!diagnosed_no_specs && !specs->declspecs_ਵੇਖਿਆ_p)
	    {
	      diagnosed_no_specs = ਸੱਚ;
	      pedwarn (ਇੱਥੇ, 0, "data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = ਝੂਠ;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_ਵਿਅੰਜਕ (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
	    {
	      postfix_attrs = c_parser_gnu_ਗੁਣ (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
		{
		  /* This means there is an attribute specifier after
		     the declarator in a function definition.  Provide
		     some more information for the user.  */
		  error_at (ਇੱਥੇ, "attributes should be specified before the "
			    "declarator in a function definition");
		  c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
		  ਵਾਪਸ ਨਤੀਜਾ;
		}
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EQ))
	    {
	      ਰੁੱਖ d;
	      ਬਣਤਰ c_ਵਿਅੰਜਕ init;
	      location_t init_loc;
	      c_parser_consume_token (parser);
	      ਜੇ (any_auto_type_p)
		{
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, init_loc);
		  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ underspec_state = 0;
		  ਜੇ (std_auto_type_p)
		    underspec_state =
		      ਸ਼ੁਰੂ_underspecified_init (init_loc, underspec_name);
		  ਸ਼ੁਰੂ_init (NULL_ਰੁੱਖ, asm_name,
			      (global_bindings_p ()
			       || specs->storage_class == csc_static
			       || specs->constexpr_p),
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_ਕੋਡ_type flag_sanitize_save = flag_sanitize;
		  ਜੇ (nested && !ਖਾਲੀ_ਥਾਵਾਂ_ok)
		    flag_sanitize = 0;
		  init = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
		  ਜੇ (std_auto_type_p)
		    ਅੰਤ_underspecified_init (underspec_name,
						underspec_state);
		  flag_sanitize = flag_sanitize_save;
		  ਜੇ (gnu_auto_type_p
		      && ਰੁੱਖ_ਕੋਡ (init.ਮੁੱਲ) == COMPONENT_REF
		      && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (init.ਮੁੱਲ, 1)))
		    error_at (ਇੱਥੇ,
			      "%<__auto_type%> used with a bit-field"
			      " initializer");
		  init = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (init_loc, init, ਸੱਚ, ਸੱਚ,
						   ਸੱਚ);
		  ਰੁੱਖ init_type = ਰੁੱਖ_TYPE (init.ਮੁੱਲ);
		  ਤਾਰਕਿਕ vm_type = c_type_variably_modified_p (init_type);
		  ਜੇ (vm_type)
		    init.ਮੁੱਲ = save_ਵਿਅੰਜਕ (init.ਮੁੱਲ);
		  ਅੰਤ_init ();
		  specs->typespec_ਕਿਸਮ = ctsk_typeof;
		  specs->locations[cdw_typedef] = init_loc;
		  specs->typedef_p = ਸੱਚ;
		  specs->type = init_type;
		  ਜੇ (specs->postfix_attrs)
		    {
		      /* Postfix [[]] attributes are valid with C23
			 auto, although not with __auto_type, and
			 modify the type given by the initializer.  */
		      specs->postfix_attrs
			= c_warn_type_ਗੁਣ (specs->type,
						  specs->postfix_attrs);
		      decl_ਗੁਣ (&specs->type, specs->postfix_attrs, 0);
		      specs->postfix_attrs = NULL_ਰੁੱਖ;
		    }
		  ਜੇ (vm_type)
		    {
		      ਤਾਰਕਿਕ maybe_const = ਸੱਚ;
		      ਰੁੱਖ type_ਵਿਅੰਜਕ = c_fully_fold (init.ਮੁੱਲ, ਝੂਠ,
						     &maybe_const);
		      specs->ਵਿਅੰਜਕ_const_operands &= maybe_const;
		      ਜੇ (specs->ਵਿਅੰਜਕ)
			specs->ਵਿਅੰਜਕ = build2 (COMPOUND_ਵਿਅੰਜਕ,
					      ਰੁੱਖ_TYPE (type_ਵਿਅੰਜਕ),
					      specs->ਵਿਅੰਜਕ, type_ਵਿਅੰਜਕ);
		      ਨਹੀਂਤਾਂ
			specs->ਵਿਅੰਜਕ = type_ਵਿਅੰਜਕ;
		    }
		  d = ਸ਼ੁਰੂ_decl (declarator, specs, ਸੱਚ,
				  chainon (postfix_attrs, all_ਅਗੇਤਰ_attrs));
		  ਜੇ (!d)
		    d = error_mark_ਗੰਢ;
		  ਜੇ (omp_declare_simd_clauses)
		    c_ਅੰਤ_omp_declare_simd (parser, d, NULL_ਰੁੱਖ,
					       omp_declare_simd_clauses);
		  ਜੇ (!omp_dsimd_idattr_clauses.is_ਖਾਲੀ_ਥਾਵਾਂ ())
		    c_ਅੰਤ_omp_declare_simd (parser, d, NULL_ਰੁੱਖ,
					       &omp_dsimd_idattr_clauses);
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* The declaration of the variable is in effect while
		     its initializer is parsed, except for a constexpr
		     variable.  */
		  init_loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, init_loc);
		  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ underspec_state = 0;
		  ਜੇ (specs->constexpr_p)
		    underspec_state =
		      ਸ਼ੁਰੂ_underspecified_init (init_loc, underspec_name);
		  d = ਸ਼ੁਰੂ_decl (declarator, specs, ਸੱਚ,
				  chainon (postfix_attrs,
					   all_ਅਗੇਤਰ_attrs),
				  !specs->constexpr_p);
		  ਜੇ (!d)
		    d = error_mark_ਗੰਢ;
		  ਜੇ (!specs->constexpr_p && omp_declare_simd_clauses)
		    c_ਅੰਤ_omp_declare_simd (parser, d, NULL_ਰੁੱਖ,
					       omp_declare_simd_clauses);
		  ਜੇ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_ਖਾਲੀ_ਥਾਵਾਂ ())
		    c_ਅੰਤ_omp_declare_simd (parser, d, NULL_ਰੁੱਖ,
					       &omp_dsimd_idattr_clauses);
		  ਸ਼ੁਰੂ_init (d, asm_name,
			      ਰੁੱਖ_STATIC (d) || specs->constexpr_p,
			      specs->constexpr_p, &richloc);
		  /* A parameter is initialized, which is invalid.  Don't
		     attempt to instrument the initializer.  */
		  sanitize_ਕੋਡ_type flag_sanitize_save = flag_sanitize;
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (d) == PARM_DECL)
		    flag_sanitize = 0;
		  init = c_parser_initializer (parser, d);
		  flag_sanitize = flag_sanitize_save;
		  ਜੇ (specs->constexpr_p)
		    {
		      ਅੰਤ_underspecified_init (underspec_name,
						  underspec_state);
		      d = pushdecl (d);
		      ਜੇ (omp_declare_simd_clauses)
			c_ਅੰਤ_omp_declare_simd (parser, d, NULL_ਰੁੱਖ,
						   omp_declare_simd_clauses);
		  ਜੇ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_ਖਾਲੀ_ਥਾਵਾਂ ())
		    c_ਅੰਤ_omp_declare_simd (parser, d, NULL_ਰੁੱਖ,
					       &omp_dsimd_idattr_clauses);
		    }
		  ਅੰਤ_init ();
		}
	      ਜੇ (oacc_routine_ਅੰਕੜੇ)
		c_ਅੰਤ_oacc_routine (oacc_routine_ਅੰਕੜੇ, d, ਝੂਠ);
	      ਜੇ (d != error_mark_ਗੰਢ)
		{
		  maybe_warn_string_init (init_loc, ਰੁੱਖ_TYPE (d), init);
		  ਅੰਤ_decl (d, init_loc, init.ਮੁੱਲ,
			       init.original_type, asm_name);
		  ਨਤੀਜਾ = d;
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (ਇੱਥੇ,
			    "%qs requires an initialized data declaration",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
		  ਵਾਪਸ ਨਤੀਜਾ;
		}

	      location_t lastloc = UNKNOWN_LOCATION;
	      ਰੁੱਖ attrs = chainon (postfix_attrs, all_ਅਗੇਤਰ_attrs);
	      ਰੁੱਖ d = ਸ਼ੁਰੂ_decl (declarator, specs, ਝੂਠ, attrs, ਸੱਚ,
				   &lastloc);
	      ਜੇ (d && ਰੁੱਖ_ਕੋਡ (d) == FUNCTION_DECL)
		{
		  /* Find the innermost declarator that is neither cdk_id
		     nor cdk_attrs.  */
		  ਅਚਲ ਬਣਤਰ c_declarator *decl = declarator;
		  ਅਚਲ ਬਣਤਰ c_declarator *ਆਖਰੀ_non_id_attrs = ਨਿਰਾ;

		  ਜਦੋਂ (decl)
		    ਚੋਣ (decl->ਕਿਸਮ)
		      {
		      ਹਾਲਤ cdk_array:
		      ਹਾਲਤ cdk_function:
		      ਹਾਲਤ cdk_ਸੂਚਕ:
			ਆਖਰੀ_non_id_attrs = decl;
			decl = decl->declarator;
			ਰੋਕੋ;

		      ਹਾਲਤ cdk_attrs:
			decl = decl->declarator;
			ਰੋਕੋ;

		      ਹਾਲਤ cdk_id:
			decl = 0;
			ਰੋਕੋ;

		      ਮੂਲ:
			gcc_unreachable ();
		      }

		  /* If it exists and is cdk_function declaration whose
		     arguments have not been set yet, use its arguments.  */
		  ਜੇ (ਆਖਰੀ_non_id_attrs
		      && ਆਖਰੀ_non_id_attrs->ਕਿਸਮ == cdk_function)
		    {
		      ਰੁੱਖ parms = ਆਖਰੀ_non_id_attrs->u.arg_info->parms;
		      ਜੇ (DECL_ARGUMENTS (d) == NULL_ਰੁੱਖ
			  && DECL_INITIAL (d) == NULL_ਰੁੱਖ)
			DECL_ARGUMENTS (d) = parms;

		      warn_parms_array_mismatch (lastloc, d, parms);
		    }
		}
	      ਜੇ (omp_declare_simd_clauses
		  || !omp_dsimd_idattr_clauses.is_ਖਾਲੀ_ਥਾਵਾਂ ())
		{
		  ਰੁੱਖ parms = NULL_ਰੁੱਖ;
		  ਜੇ (d && ਰੁੱਖ_ਕੋਡ (d) == FUNCTION_DECL)
		    {
		      ਬਣਤਰ c_declarator *ce = declarator;
		      ਜਦੋਂ (ce != ਨਿਰਾ)
			ਜੇ (ce->ਕਿਸਮ == cdk_function)
			  {
			    parms = ce->u.arg_info->parms;
			    ਰੋਕੋ;
			  }
			ਨਹੀਂਤਾਂ
			  ce = ce->declarator;
		    }
		  ਜੇ (parms)
		    ਆਰਜ਼ੀ_store_parm_decls (d, parms);
		  ਜੇ (omp_declare_simd_clauses)
		    c_ਅੰਤ_omp_declare_simd (parser, d, parms,
					       omp_declare_simd_clauses);
		  ਜੇ (!specs->constexpr_p
		      && !omp_dsimd_idattr_clauses.is_ਖਾਲੀ_ਥਾਵਾਂ ())
		    c_ਅੰਤ_omp_declare_simd (parser, d, parms,
					       &omp_dsimd_idattr_clauses);
		  ਜੇ (parms)
		    ਆਰਜ਼ੀ_ਕੱਢੋ_parm_decls ();
		}
	      ਜੇ (oacc_routine_ਅੰਕੜੇ)
		c_ਅੰਤ_oacc_routine (oacc_routine_ਅੰਕੜੇ, d, ਝੂਠ);
	      ਜੇ (d)
		ਅੰਤ_decl (d, UNKNOWN_LOCATION, NULL_ਰੁੱਖ,
			     NULL_ਰੁੱਖ, asm_name);

	      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ਵਿੱਚ))
		{
		  ਜੇ (d)
		    *objc_foreach_object_declaration = d;
		  ਨਹੀਂਤਾਂ
		    *objc_foreach_object_declaration = error_mark_ਗੰਢ;
		}
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    {
	      ਹੋਰ_than_one_decl = ਸੱਚ;
	      ਜੇ (any_auto_type_p || specs->constexpr_p)
		{
		  error_at (ਇੱਥੇ,
			    "%qs may only be used with a single declarator",
			    any_auto_type_p ? auto_type_keyword : "constexpr");
		  c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
		  ਵਾਪਸ ਨਤੀਜਾ;
		}
	      c_parser_consume_token (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
		all_ਅਗੇਤਰ_attrs = chainon (c_parser_gnu_ਗੁਣ (parser),
					    ਅਗੇਤਰ_attrs);
	      ਨਹੀਂਤਾਂ
		all_ਅਗੇਤਰ_attrs = ਅਗੇਤਰ_attrs;
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	    {
	      ਜੇ (!simple_ok)
		c_parser_consume_token (parser);
	      ਵਾਪਸ ਨਤੀਜਾ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ਵਿੱਚ))
	    {
	      /* This can only happen in Objective-C: we found the
		 'in' that terminates the declaration inside an
		 Objective-C foreach statement.  Do not consume the
		 token, so that the caller can use it to determine
		 that this indeed is a foreach context.  */
	      ਵਾਪਸ ਨਤੀਜਾ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (!simple_ok)
		{
		  c_parser_error (parser, "expected %<,%> or %<;%>");
		  c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
		}
	      /* It's not valid to use if (int i = 2, j = 3).  */
	      ਨਹੀਂਤਾਂ ਜੇ (ਹੋਰ_than_one_decl)
		error_at (ਇੱਥੇ, "declaration in condition can only declare "
			  "a single object");
	      ਵਾਪਸ ਨਤੀਜਾ;
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (any_auto_type_p || specs->constexpr_p)
	{
	  error_at (ਇੱਥੇ,
		    "%qs requires an initialized data declaration",
		    any_auto_type_p ? auto_type_keyword : "constexpr");
	  c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
	  ਵਾਪਸ ਨਤੀਜਾ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!fndef_ok)
	{
	  ਜੇ (simple_ok && c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	    /* Let c_parser_selection_header emit the error.  */;
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			      "%<asm%> or %<__attribute__%>");
	      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
	    }
	  ਵਾਪਸ ਨਤੀਜਾ;
	}
      /* Function definition (nested or otherwise).  */
      ਜੇ (nested)
	{
	  pedwarn (ਇੱਥੇ, OPT_Wpedantic, "ISO C forbids nested functions");
	  c_ਧੱਕੋ_function_context ();
	}

      /* If we're in an OpenMP "begin declare variant" block, the
	 name in the declarator refers to the base function.  We need
	 to save that and modify the declarator to have the mangled
	 name for the variant function instead.  */
      ਰੁੱਖ dv_ਅਧਾਰ = NULL_ਰੁੱਖ;
      ਰੁੱਖ dv_ctx = NULL_ਰੁੱਖ;
      ਜੇ (!vec_ਸੁਰੱਖਿਅਤ_is_ਖਾਲੀ_ਥਾਵਾਂ (current_omp_declare_variant_attribute))
	{
	  c_omp_declare_variant_attr a
	    = current_omp_declare_variant_attribute->ਆਖਰੀ ();
	  dv_ctx = copy_list (a.selector);
	  dv_ਅਧਾਰ = omp_ਸ਼ੁਰੂ_variant_function (declarator, dv_ctx);
	}

      ਜੇ (!ਸ਼ੁਰੂ_function (specs, declarator, all_ਅਗੇਤਰ_attrs))
	{
	  /* At this point we've consumed:
	       declaration-specifiers declarator
	     and the next token isn't CPP_EQ, CPP_COMMA, CPP_SEMICOLON,
	     RID_ASM, RID_ATTRIBUTE, or RID_IN,
	     but the
	       declaration-specifiers declarator
	     aren't grokkable as a function definition, so we have
	     an error.  */
	  gcc_assert (!c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON));
	  ਜੇ (c_parser_ਅਗਲਾ_token_starts_declspecs (parser))
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
	      parser->error = ਝੂਠ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      /* This can appear in many cases looking nothing like a
		 function definition, so we don't give a more specific
		 error suggesting there was one.  */
	      c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			      "or %<__attribute__%>");
	    }
	  ਜੇ (nested)
	    c_ਕੱਢੋ_function_context ();
	  ਰੋਕੋ;
	}

      ਜੇ (DECL_DECLARED_INLINE_P (current_function_decl))
        tv = TV_PARSE_INLINE;
      ਨਹੀਂਤਾਂ
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
      ਪੂਰਨ save_debug_nonbind_markers_p = debug_nonbind_markers_p;
      debug_nonbind_markers_p = 0;
      c_parser_maybe_reclassify_token (parser);
      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_EOF)
	     && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_OPEN_BRACE))
	c_parser_declaration_or_fndef (parser, ਝੂਠ, ਝੂਠ, ਝੂਠ,
				       ਸੱਚ, ਝੂਠ, ਝੂਠ);
      debug_nonbind_markers_p = save_debug_nonbind_markers_p;
      store_parm_decls ();
      ਜੇ (omp_declare_simd_clauses)
	c_ਅੰਤ_omp_declare_simd (parser, current_function_decl, NULL_ਰੁੱਖ,
				   omp_declare_simd_clauses);
      ਜੇ (!omp_dsimd_idattr_clauses.is_ਖਾਲੀ_ਥਾਵਾਂ ())
	c_ਅੰਤ_omp_declare_simd (parser, current_function_decl, NULL_ਰੁੱਖ,
				   &omp_dsimd_idattr_clauses);
      ਜੇ (oacc_routine_ਅੰਕੜੇ)
	c_ਅੰਤ_oacc_routine (oacc_routine_ਅੰਕੜੇ, current_function_decl, ਸੱਚ);
      location_t startloc = c_parser_peek_token (parser)->location;
      DECL_STRUCT_FUNCTION (current_function_decl)->function_ਸ਼ੁਰੂ_locus
	= startloc;
      location_t endloc = startloc;
      /* If this function was in a "begin declare variant" block,
	 remember it.  We will associate it with the base function at
	 the end of processing the translation unit, since it is permitted
	 for the variant definition to appear before the base declaration.  */
      ਜੇ (dv_ਅਧਾਰ && current_function_decl != error_mark_ਗੰਢ)
	{
	  omp_begin_declare_variant_map_ਇੰਦਰਾਜ e
	    = { current_function_decl, dv_ਅਧਾਰ, dv_ctx };
	  vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (omp_begin_declare_variant_map, e);
	}

      /* If the definition was marked with __RTL, use the RTL parser now,
	 consuming the function body.  */
      ਜੇ (specs->declspec_il == cdil_rtl)
	{
	  endloc = c_parser_parse_rtl_body (parser, specs->gimple_or_rtl_pass);

	  /* Normally, store_parm_decls sets next_is_function_body,
	     anticipating a function body.  We need a push_scope/pop_scope
	     pair to flush out this state, or subsequent function parsing
	     will go wrong.  */
	  ਧੱਕੋ_scope ();
	  ਕੱਢੋ_scope ();

	  ਅੰਤ_function (endloc);
	  ਵਾਪਸ ਨਤੀਜਾ;
	}
      /* If the definition was marked with __GIMPLE then parse the
         function body as GIMPLE.  */
      ਨਹੀਂਤਾਂ ਜੇ (specs->declspec_il != cdil_none)
	{
	  ਤਾਰਕਿਕ saved = ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op;
	  ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = ਸੱਚ;
	  c_parser_parse_gimple_body (parser, specs->gimple_or_rtl_pass,
				      specs->declspec_il,
				      specs->ਇੰਦਰਾਜ_bb_ਗਿਣਤੀ);
	  ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = saved;
	}
      ਨਹੀਂਤਾਂ
	fnbody = c_parser_compound_statement (parser, &endloc);
      ਰੁੱਖ fndecl = current_function_decl;
      ਜੇ (nested && specs->declspec_il == cdil_none)
	{
	  ਰੁੱਖ decl = current_function_decl;
	  /* Mark nested functions as needing static-chain initially.
	     lower_nested_functions will recompute it but the
	     DECL_STATIC_CHAIN flag is also used before that happens,
	     by initializer_constant_valid_p.  See gcc.dg/nested-fn-2.c.  */
	  DECL_STATIC_CHAIN (decl) = 1;
	  ਜੋੜੋ_stmt (fnbody);
	  ਅੰਤ_function (endloc);
	  c_ਕੱਢੋ_function_context ();
	  ਜੋੜੋ_stmt (build_stmt (DECL_ਸਰੋਤ_LOCATION (decl), DECL_ਵਿਅੰਜਕ, decl));
	}
      ਨਹੀਂਤਾਂ ਜੇ (nested)
	{
	  ਜੇ (specs->declspec_il == cdil_rtl)
	    error ("%<__RTL%> function cannot be a nested function");
	  ਨਹੀਂਤਾਂ
	    error ("%<__GIMPLE%> function cannot be a nested function");
	  ਅੰਤ_function (endloc);
	  c_ਕੱਢੋ_function_context ();
	}
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (fnbody)
	    ਜੋੜੋ_stmt (fnbody);
	  ਅੰਤ_function (endloc);
	}
      /* Get rid of the empty stmt list for GIMPLE/RTL.  */
      ਜੇ (specs->declspec_il != cdil_none)
	DECL_SAVED_ਰੁੱਖ (fndecl) = NULL_ਰੁੱਖ;

      ਰੋਕੋ;
    }

  ਵਾਪਸ ਨਤੀਜਾ;
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

ਸਥਿਰ ਖਾਲੀ
c_parser_asm_definition (c_parser *parser)
{
  location_t asm_loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  ਰੁੱਖ asm_str = NULL_ਰੁੱਖ;
  ਰੁੱਖ outputs = NULL_ਰੁੱਖ, inputs = NULL_ਰੁੱਖ;
  ਜੇ (!parens.require_open (parser))
    ਜਾਓ ਪੂਰਾ;
  asm_str = c_parser_asm_string_literal (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
    {
      parens.require_close (parser);
      ਜਾਓ ਪੂਰਾ;
    }
  ਲਈ (ਪੂਰਨ section = 0; section < 2; ++section)
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  ਜੇ (section == 2)
	    {
	      c_parser_error (parser, "expected %<)%>");
	    error_close_paren:
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	      asm_str = NULL_ਰੁੱਖ;
	      ਜਾਓ ਪੂਰਾ;
	    }
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (!c_parser_require (parser, CPP_COLON,
				  "expected %<:%> or %<)%>",
				  UNKNOWN_LOCATION, ਝੂਠ))
	ਜਾਓ error_close_paren;
      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON)
	  && !c_parser_ਅਗਲਾ_token_is (parser, CPP_SCOPE)
	  && !c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ਜੇ (section)
	    inputs = c_parser_asm_operands (parser);
	  ਨਹੀਂਤਾਂ
	    outputs = c_parser_asm_operands (parser);
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	ਰੋਕੋ;
    }

  ਜੇ (!parens.require_close (parser))
    {
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
      asm_str = NULL_ਰੁੱਖ;
    }

  ਜੇ (asm_str)
    asm_str = build_asm_ਵਿਅੰਜਕ (asm_loc, asm_str, outputs, inputs,
			      NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, ਝੂਠ, ਝੂਠ);
ਪੂਰਾ:
  ਜੇ (asm_str)
    symtab->finalize_toplevel_asm (asm_str);
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse a static assertion (C11 6.7.10).

   static_assert-declaration:
     static_assert-declaration-no-semi ;
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_static_assert_declaration (c_parser *parser)
{
  c_parser_static_assert_declaration_no_semi (parser);
  ਜੇ (parser->error
      || !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
}

/* Parse a static assertion (C11 6.7.10), without the trailing
   semicolon.

   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression , string-literal )

   C23:
   static_assert-declaration-no-semi:
     _Static_assert ( constant-expression )
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_static_assert_declaration_no_semi (c_parser *parser)
{
  location_t assert_loc, ਮੁੱਲ_loc;
  ਰੁੱਖ ਮੁੱਲ;
  ਰੁੱਖ string = NULL_ਰੁੱਖ;

  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_STATIC_ASSERT));
  ਰੁੱਖ spelling = c_parser_peek_token (parser)->ਮੁੱਲ;
  assert_loc = c_parser_peek_token (parser)->location;
  ਜੇ (flag_isoc99)
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  ਨਹੀਂਤਾਂ
    pedwarn_c99 (assert_loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  c_parser_consume_token (parser);
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ;
  location_t ਮੁੱਲ_tok_loc = c_parser_peek_token (parser)->location;
  ਮੁੱਲ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਮੁੱਲ_tok_loc,
				    c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ),
				    ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
  ਮੁੱਲ_loc = ਵਿਅੰਜਕ_LOC_OR_LOC (ਮੁੱਲ, ਮੁੱਲ_tok_loc);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_STRING:
	ਹਾਲਤ CPP_STRING16:
	ਹਾਲਤ CPP_STRING32:
	ਹਾਲਤ CPP_WSTRING:
	ਹਾਲਤ CPP_UTF8STRING:
	  string = c_parser_string_literal (parser, ਝੂਠ, ਸੱਚ).ਮੁੱਲ;
	  ਰੋਕੋ;
	ਮੂਲ:
	  c_parser_error (parser, "expected string literal");
	  ਵਾਪਸ;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (flag_isoc11)
    /* If pedantic for pre-C11, the use of _Static_assert itself will
       have been diagnosed, so do not also diagnose the use of this
       new C23 feature of _Static_assert.  */
    pedwarn_c11 (assert_loc, OPT_Wpedantic,
		 "ISO C11 does not support omitting the string in "
		 "%qE", spelling);
  parens.require_close (parser);

  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਮੁੱਲ)))
    {
      error_at (ਮੁੱਲ_loc, "expression in static assertion is not an integer");
      ਵਾਪਸ;
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST)
    {
      ਮੁੱਲ = c_fully_fold (ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
      /* Strip no-op conversions.  */
      STRIP_TYPE_NOPS (ਮੁੱਲ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) == INTEGER_CST)
	pedwarn (ਮੁੱਲ_loc, OPT_Wpedantic, "expression in static assertion "
		 "is not an integer constant expression");
    }
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST)
    {
      error_at (ਮੁੱਲ_loc, "expression in static assertion is not constant");
      ਵਾਪਸ;
    }
  constant_ਵਿਅੰਜਕ_warning (ਮੁੱਲ);
  ਜੇ (integer_zerop (ਮੁੱਲ))
    {
      ਜੇ (string)
	error_at (assert_loc, "static assertion failed: %E", string);
      ਨਹੀਂਤਾਂ
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
ਰਜਿਸਟਰ
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

ਖਾਲੀ
c_parser_declspecs (c_parser *parser, ਬਣਤਰ c_declspecs *specs,
		    ਤਾਰਕਿਕ scspec_ok, ਤਾਰਕਿਕ typespec_ok, ਤਾਰਕਿਕ ਸ਼ੁਰੂ_attr_ok,
		    ਤਾਰਕਿਕ alignspec_ok, ਤਾਰਕਿਕ auto_type_ok,
		    ਤਾਰਕਿਕ ਸ਼ੁਰੂ_std_attr_ok, ਤਾਰਕਿਕ ਸਿਰਾ_std_attr_ok,
		    ਗਿਣਤੀ c_lookahead_ਕਿਸਮ la)
{
  ਤਾਰਕਿਕ attrs_ok = ਸ਼ੁਰੂ_attr_ok;
  ਤਾਰਕਿਕ ਵੇਖਿਆ_type = specs->typespec_ਕਿਸਮ != ctsk_none;

  ਜੇ (!typespec_ok)
    gcc_assert (la == cla_prefer_id);

  ਜੇ (ਸ਼ੁਰੂ_std_attr_ok
      && c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
    {
      gcc_assert (!specs->non_std_attrs_ਵੇਖਿਆ_p);
      location_t loc = c_parser_peek_token (parser)->location;
      ਰੁੱਖ attrs = c_parser_std_attribute_specifier_sequence (parser);
      declspecs_ਜੋੜੋ_attrs (loc, specs, attrs);
      specs->non_std_attrs_ਵੇਖਿਆ_p = ਝੂਠ;
    }

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	 || c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
	 || (c_dialect_objc () && c_parser_ਅਗਲਾ_token_is (parser, CPP_LESS)))
    {
      ਬਣਤਰ c_typespec t;
      ਰੁੱਖ attrs;
      ਰੁੱਖ align;
      location_t loc = c_parser_peek_token (parser)->location;

      /* If we cannot accept a type, exit if the next token must start
	 one.  Also, if we already have seen a tagged definition,
	 a typename would be an error anyway and likely the user
	 has simply forgotten a semicolon, so we exit.  */
      ਜੇ ((!typespec_ok || specs->typespec_ਕਿਸਮ == ctsk_tagdef)
	  && c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, la)
	  && !c_parser_ਅਗਲਾ_token_is_qualifier (parser)
	  && !c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ALIGNAS))
	ਰੋਕੋ;

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  c_token *name_token = c_parser_peek_token (parser);
	  ਰੁੱਖ ਮੁੱਲ = name_token->ਮੁੱਲ;
	  c_id_ਕਿਸਮ ਕਿਸਮ = name_token->id_ਕਿਸਮ;

	  ਜੇ (ਕਿਸਮ == C_ID_ADDRSPACE)
	    {
	      addr_space_t as
		= name_token->keyword - RID_ਪਹਿਲਾ_ADDR_SPACE;
	      declspecs_ਜੋੜੋ_addrspace (name_token->location, specs, as);
	      c_parser_consume_token (parser);
	      attrs_ok = ਸੱਚ;
	      ਜਾਰੀ;
	    }

	  gcc_assert (!c_parser_ਅਗਲਾ_token_is_qualifier (parser));

	  /* If we cannot accept a type, and the next token must start one,
	     exit.  Do the same if we already have seen a tagged definition,
	     since it would be an error anyway and likely the user has simply
	     forgotten a semicolon.  */
	  ਜੇ (ਵੇਖਿਆ_type || !c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, la))
	    ਰੋਕੋ;

	  /* Now at an unknown typename (C_ID_ID), a C_ID_TYPENAME or
	     a C_ID_CLASSNAME.  */
	  c_parser_consume_token (parser);
	  ਵੇਖਿਆ_type = ਸੱਚ;
	  attrs_ok = ਸੱਚ;
	  ਜੇ (ਕਿਸਮ == C_ID_ID)
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      name_hint hint = lookup_name_fuzzy (ਮੁੱਲ, FUZZY_LOOKUP_TYPENAME,
						  loc);
	      ਜੇ (ਅਚਲ ਅੱਖਰ *suggestion = hint.suggestion ())
		{
		  gcc_rich_location richloc (loc);
		  richloc.ਜੋੜੋ_fixit_replace (suggestion);
		  error_at (&richloc,
			    "unknown type name %qE; did you mean %qs?",
			    ਮੁੱਲ, suggestion);
		}
	      ਨਹੀਂਤਾਂ
		error_at (loc, "unknown type name %qE", ਮੁੱਲ);
	      t.ਕਿਸਮ = ctsk_typedef;
	      t.spec = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਕਿਸਮ == C_ID_TYPENAME
	           && (!c_dialect_objc ()
	               || c_parser_ਅਗਲਾ_token_is_not (parser, CPP_LESS)))
	    {
	      t.ਕਿਸਮ = ctsk_typedef;
	      /* For a typedef name, record the meaning, not the name.
		 In case of 'foo foo, bar;'.  */
	      t.spec = lookup_name (ਮੁੱਲ);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ proto = NULL_ਰੁੱਖ;
	      gcc_assert (c_dialect_objc ());
	      t.ਕਿਸਮ = ctsk_objc;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_LESS))
		proto = c_parser_objc_protocol_refs (parser);
	      t.spec = objc_get_protocol_qualified_type (ਮੁੱਲ, proto);
	    }
	  t.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
	  t.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
	  t.has_enum_type_specifier = ਝੂਠ;
	  declspecs_ਜੋੜੋ_type (name_token->location, specs, t);
	  ਜਾਰੀ;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_LESS))
	{
	  /* Make "<SomeProtocol>" equivalent to "id <SomeProtocol>" -
	     nisse@lysator.liu.se.  */
	  ਰੁੱਖ proto;
	  gcc_assert (c_dialect_objc ());
	  ਜੇ (!typespec_ok || ਵੇਖਿਆ_type)
	    ਰੋਕੋ;
	  proto = c_parser_objc_protocol_refs (parser);
	  t.ਕਿਸਮ = ctsk_objc;
	  t.spec = objc_get_protocol_qualified_type (NULL_ਰੁੱਖ, proto);
	  t.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
	  t.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
	  t.has_enum_type_specifier = ਝੂਠ;
	  declspecs_ਜੋੜੋ_type (loc, specs, t);
	  ਜਾਰੀ;
	}
      gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD));
      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_STATIC:
	ਹਾਲਤ RID_EXTERN:
	ਹਾਲਤ RID_ਰਜਿਸਟਰ:
	ਹਾਲਤ RID_TYPEDEF:
	ਹਾਲਤ RID_INLINE:
	ਹਾਲਤ RID_NORETURN:
	ਹਾਲਤ RID_AUTO:
	ਹਾਲਤ RID_THREAD:
	ਹਾਲਤ RID_CONSTEXPR:
	  ਜੇ (!scspec_ok)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  attrs_ok = ਸੱਚ;
	  /* TODO: Distinguish between function specifiers (inline, noreturn)
	     and storage class specifiers, either here or in
	     declspecs_add_scspec.  */
	  declspecs_ਜੋੜੋ_scspec (loc, specs,
				c_parser_peek_token (parser)->ਮੁੱਲ);
	  c_parser_consume_token (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AUTO_TYPE:
	  ਜੇ (!auto_type_ok)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  /* Fall through.  */
	ਹਾਲਤ RID_UNSIGNED:
	ਹਾਲਤ RID_LONG:
	ਹਾਲਤ RID_SHORT:
	ਹਾਲਤ RID_SIGNED:
	ਹਾਲਤ RID_COMPLEX:
	ਹਾਲਤ RID_INT:
	ਹਾਲਤ RID_CHAR:
	ਹਾਲਤ RID_FLOAT:
	ਹਾਲਤ RID_DOUBLE:
	ਹਾਲਤ RID_VOID:
	ਹਾਲਤ RID_DFLOAT32:
	ਹਾਲਤ RID_DFLOAT64:
	ਹਾਲਤ RID_DFLOAT128:
	ਹਾਲਤ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ਹਾਲਤ RID_BOOL:
	ਹਾਲਤ RID_FRACT:
	ਹਾਲਤ RID_ACCUM:
	ਹਾਲਤ RID_SAT:
	ਹਾਲਤ RID_INT_N_0:
	ਹਾਲਤ RID_INT_N_1:
	ਹਾਲਤ RID_INT_N_2:
	ਹਾਲਤ RID_INT_N_3:
	  ਜੇ (!typespec_ok)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  attrs_ok = ਸੱਚ;
	  ਵੇਖਿਆ_type = ਸੱਚ;
	  ਜੇ (c_dialect_objc ())
	    parser->objc_need_raw_identifier = ਸੱਚ;
	  t.ਕਿਸਮ = ctsk_resword;
	  t.spec = c_parser_peek_token (parser)->ਮੁੱਲ;
	  t.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
	  t.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
	  t.has_enum_type_specifier = ਝੂਠ;
	  declspecs_ਜੋੜੋ_type (loc, specs, t);
	  c_parser_consume_token (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_ENUM:
	  ਜੇ (!typespec_ok)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  attrs_ok = ਸੱਚ;
	  ਵੇਖਿਆ_type = ਸੱਚ;
	  t = c_parser_enum_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_ਅੰਤ_TYPE, t.spec);
	  declspecs_ਜੋੜੋ_type (loc, specs, t);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_STRUCT:
	ਹਾਲਤ RID_UNION:
	  ਜੇ (!typespec_ok)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  attrs_ok = ਸੱਚ;
	  ਵੇਖਿਆ_type = ਸੱਚ;
	  t = c_parser_struct_or_union_specifier (parser);
          invoke_plugin_callbacks (PLUGIN_ਅੰਤ_TYPE, t.spec);
	  declspecs_ਜੋੜੋ_type (loc, specs, t);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_TYPEOF:
	ਹਾਲਤ RID_TYPEOF_UNQUAL:
	  /* ??? The old parser rejected typeof after other type
	     specifiers, but is a syntax error the best way of
	     handling this?  */
	  ਜੇ (!typespec_ok || ਵੇਖਿਆ_type)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  attrs_ok = ਸੱਚ;
	  ਵੇਖਿਆ_type = ਸੱਚ;
	  t = c_parser_typeof_specifier (parser);
	  declspecs_ਜੋੜੋ_type (loc, specs, t);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_BITINT:
	  ਜੇ (!typespec_ok)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  ਨਹੀਂਤਾਂ
	    {
	      attrs_ok = ਸੱਚ;
	      ਵੇਖਿਆ_type = ਸੱਚ;
	      t.ਕਿਸਮ = ctsk_resword;
	      t.spec = c_parser_peek_token (parser)->ਮੁੱਲ;
	      t.ਵਿਅੰਜਕ = error_mark_ਗੰਢ;
	      t.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
	      t.has_enum_type_specifier = ਝੂਠ;
	      c_parser_consume_token (parser);
	      matching_parens parens;
	      ਜੇ (parens.require_open (parser))
		{
		  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
		  t.ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਸੱਚ,
						     ਸੱਚ).ਮੁੱਲ;
		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		}
	      declspecs_ਜੋੜੋ_type (loc, specs, t);
	    }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_ATOMIC:
	  /* C parser handling of Objective-C constructs needs
	     checking for correct lvalue-to-rvalue conversions, and
	     the code in build_modify_expr handling various
	     Objective-C cases, and that in build_unary_op handling
	     Objective-C cases for increment / decrement, also needs
	     updating; uses of TYPE_MAIN_VARIANT in objc_compare_types
	     and objc_types_are_equivalent may also need updates.  */
	  ਜੇ (c_dialect_objc ())
	    sorry ("%<_Atomic%> in Objective-C");
	  ਜੇ (flag_isoc99)
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C99 does not support the %<_Atomic%> qualifier");
	  ਨਹੀਂਤਾਂ
	    pedwarn_c99 (loc, OPT_Wpedantic,
			 "ISO C90 does not support the %<_Atomic%> qualifier");
	  attrs_ok = ਸੱਚ;
	  ਰੁੱਖ ਮੁੱਲ;
	  ਮੁੱਲ = c_parser_peek_token (parser)->ਮੁੱਲ;
	  c_parser_consume_token (parser);
	  ਜੇ (typespec_ok && c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
	    {
	      /* _Atomic ( type-name ).  */
	      ਵੇਖਿਆ_type = ਸੱਚ;
	      c_parser_consume_token (parser);
	      ਬਣਤਰ c_type_name *type = c_parser_type_name (parser);
	      t.ਕਿਸਮ = ctsk_typeof;
	      t.spec = error_mark_ਗੰਢ;
	      t.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
	      t.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
	      t.has_enum_type_specifier = ਝੂਠ;
	      ਜੇ (type != ਨਿਰਾ)
		t.spec = groktypename (type, &t.ਵਿਅੰਜਕ,
				       &t.ਵਿਅੰਜਕ_const_operands);
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ਜੇ (t.spec != error_mark_ਗੰਢ)
		{
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (t.spec) == ARRAY_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified array type");
		  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (t.spec) == FUNCTION_TYPE)
		    error_at (loc, "%<_Atomic%>-qualified function type");
		  ਨਹੀਂਤਾਂ ਜੇ (TYPE_QUALS (t.spec) != TYPE_UNQUALIFIED)
		    error_at (loc, "%<_Atomic%> applied to a qualified type");
		  ਨਹੀਂਤਾਂ
		    t.spec = c_build_qualified_type (t.spec, TYPE_QUAL_ATOMIC);
		}
	      declspecs_ਜੋੜੋ_type (loc, specs, t);
	    }
	  ਨਹੀਂਤਾਂ
	    declspecs_ਜੋੜੋ_qual (loc, specs, ਮੁੱਲ);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_CONST:
	ਹਾਲਤ RID_VOLATILE:
	ਹਾਲਤ RID_RESTRICT:
	  attrs_ok = ਸੱਚ;
	  declspecs_ਜੋੜੋ_qual (loc, specs, c_parser_peek_token (parser)->ਮੁੱਲ);
	  c_parser_consume_token (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_ATTRIBUTE:
	  ਜੇ (!attrs_ok)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  attrs = c_parser_gnu_ਗੁਣ (parser);
	  declspecs_ਜੋੜੋ_attrs (loc, specs, attrs);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_ALIGNAS:
	  ਜੇ (!alignspec_ok)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  align = c_parser_alignas_specifier (parser);
	  declspecs_ਜੋੜੋ_alignas (loc, specs, align);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_GIMPLE:
	  ਜੇ (! flag_gimple)
	    error_at (loc, "%<__GIMPLE%> only valid with %<-fgimple%>");
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_gimple;
	  specs->locations[cdw_gimple] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_RTL:
	  c_parser_consume_token (parser);
	  specs->declspec_il = cdil_rtl;
	  specs->locations[cdw_rtl] = loc;
	  c_parser_gimple_or_rtl_pass_list (parser, specs);
	  ਰੋਕੋ;
	ਮੂਲ:
	  ਜਾਓ ਬਾਹਰਲਾ;
	}
    }
 ਬਾਹਰਲਾ:
  ਜੇ (ਸਿਰਾ_std_attr_ok
      && c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
    specs->postfix_attrs = c_parser_std_attribute_specifier_sequence (parser);
}

/* Complain about a non-CPP_NAME within an enumerator list.  */

ਸਥਿਰ ਖਾਲੀ
report_bad_enum_name (c_parser *parser)
{
  ਜੇ (!parser->error)
    {
      c_token *token = c_parser_peek_token (parser);
      ਚੋਣ (token->type)
	{
	ਮੂਲ:
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_CLOSE_BRACE:
	  /* Give a nicer error for "enum {}".  */
	  error_at (token->location,
		    "empty enum is invalid");
	  parser->error = ਸੱਚ;
	  ਵਾਪਸ;
	ਹਾਲਤ CPP_KEYWORD:
	  /* Give a nicer error for attempts to use "true" and "false"
	     in enums with C23 onwards.  */
	  ਜੇ (token->keyword == RID_FALSE
	      || token->keyword == RID_TRUE)
	    {
	      auto_diagnostic_ਸਮੂਹ d;
	      error_at (token->location,
			"cannot use keyword %qs as enumeration constant",
			IDENTIFIER_ਸੂਚਕ (token->ਮੁੱਲ));
	      ਜੋੜੋ_note_about_new_keyword (token->location,
					  token->ਮੁੱਲ);
	      parser->error = ਸੱਚ;
	      ਵਾਪਸ;
	    }
	  ਰੋਕੋ;
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

ਸਥਿਰ ਬਣਤਰ c_typespec
c_parser_enum_specifier (c_parser *parser)
{
  ਬਣਤਰ c_typespec ret;
  ਤਾਰਕਿਕ have_std_attrs;
  ਤਾਰਕਿਕ potential_nesting_p = ਝੂਠ;
  ਰੁੱਖ std_attrs = NULL_ਰੁੱਖ;
  ਰੁੱਖ attrs;
  ਰੁੱਖ ident = NULL_ਰੁੱਖ;
  ਰੁੱਖ fixed_underlying_type = NULL_ਰੁੱਖ;
  location_t enum_loc;
  location_t ident_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ENUM));
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_ਗੁਣ (parser, 1);
  ਜੇ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_ਗੁਣ (parser);
  enum_loc = c_parser_peek_token (parser)->location;
  /* Set the location in case we create a decl now.  */
  c_parser_ਸੈੱਟ_ਸਰੋਤ_position_from_token (c_parser_peek_token (parser));
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->ਮੁੱਲ;
      ident_loc = c_parser_peek_token (parser)->location;
      enum_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON)
      /* Distinguish an enum-type-specifier from a bit-field
	 declaration of the form "enum e : constant-expression;".  */
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      pedwarn_c11 (enum_loc, OPT_Wpedantic,
		   "ISO C does not support specifying %<enum%> underlying "
		   "types before C23");
      ਜੇ (ident)
	{
	  /* The tag is in scope during the enum-type-specifier (which
	     may refer to the tag inside typeof).  */
	  ret = parser_xref_ਟੈਗ (ident_loc, ENUMERAL_TYPE, ident,
				 have_std_attrs, std_attrs, ਸੱਚ);
	  ਜੇ (!ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec))
	    error_at (enum_loc, "%<enum%> declared both with and without "
		      "fixed underlying type");
	  potential_nesting_p = NULL_ਰੁੱਖ == TYPE_ਮੁੱਲਾਂ (ret.spec);
	}
      ਨਹੀਂਤਾਂ
	{
	  /* There must be an enum definition, so this initialization
	     (to avoid possible warnings about uninitialized data)
	     will be replaced later (either with the results of that
	     definition, or with the results of error handling for the
	     case of no tag and no definition).  */
	  ret.spec = NULL_ਰੁੱਖ;
	  ret.ਕਿਸਮ = ctsk_tagdef;
	  ret.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
	  ret.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
	  ret.has_enum_type_specifier = ਸੱਚ;
	}
      c_parser_consume_token (parser);
      ਬਣਤਰ c_declspecs *specs = build_null_declspecs ();
      c_parser_declspecs (parser, specs, ਝੂਠ, ਸੱਚ, ਝੂਠ, ਝੂਠ, ਝੂਠ,
			  ਝੂਠ, ਸੱਚ, cla_prefer_id);
      ਅੰਤ_declspecs (specs);
      ਜੇ (specs->default_int_p)
	error_at (enum_loc, "no %<enum%> underlying type specified");
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (specs->type) != INTEGER_TYPE
	       && ਰੁੱਖ_ਕੋਡ (specs->type) != BOOLEAN_TYPE
	       && (!flag_isoc2y || ਰੁੱਖ_ਕੋਡ (specs->type) != BITINT_TYPE))
	{
	  error_at (enum_loc, "invalid %<enum%> underlying type");
	  specs->type = integer_type_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (specs->restrict_p)
	error_at (enum_loc, "invalid use of %<restrict%>");
      fixed_underlying_type = TYPE_MAIN_VARIANT (specs->type);
      ਜੇ (ident)
	{
	  /* The type specified must be consistent with any previously
	     specified underlying type.  If this is a newly declared
	     type, it is now a complete type.  */
	  ਜੇ (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
	      && ENUM_UNDERLYING_TYPE (ret.spec) == NULL_ਰੁੱਖ)
	    {
	      TYPE_MIN_ਮੁੱਲ (ret.spec) =
		TYPE_MIN_ਮੁੱਲ (fixed_underlying_type);
	      TYPE_MAX_ਮੁੱਲ (ret.spec) =
		TYPE_MAX_ਮੁੱਲ (fixed_underlying_type);
	      TYPE_UNSIGNED (ret.spec) = TYPE_UNSIGNED (fixed_underlying_type);
	      ਸੈੱਟ_TYPE_ALIGN (ret.spec, TYPE_ALIGN (fixed_underlying_type));
	      TYPE_ਮਾਪ (ret.spec) = NULL_ਰੁੱਖ;
	      TYPE_PRECISION (ret.spec) =
		TYPE_PRECISION (fixed_underlying_type);
	      ENUM_UNDERLYING_TYPE (ret.spec) = fixed_underlying_type;
	      layout_type (ret.spec);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ENUM_FIXED_UNDERLYING_TYPE_P (ret.spec)
		   && !comptypes (fixed_underlying_type,
				  ENUM_UNDERLYING_TYPE (ret.spec)))
	    {
	      error_at (enum_loc, "%<enum%> underlying type incompatible with "
			"previous declaration");
	      fixed_underlying_type = ENUM_UNDERLYING_TYPE (ret.spec);
	    }
	}
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse an enum definition.  */
      ਬਣਤਰ c_enum_contents the_enum;
      ਰੁੱਖ type;
      ਰੁੱਖ postfix_attrs;
      /* We chain the enumerators in reverse order, then put them in
	 forward order at the end.  */
      ਰੁੱਖ ਮੁੱਲਾਂ;
      timevar_ਧੱਕੋ (TV_PARSE_ENUM);
      type = ਸ਼ੁਰੂ_enum (enum_loc, &the_enum, ident, fixed_underlying_type,
			 potential_nesting_p);
      ਮੁੱਲਾਂ = NULL_ਰੁੱਖ;
      c_parser_consume_token (parser);
      ਜਦੋਂ (ਸੱਚ)
	{
	  ਰੁੱਖ enum_id;
	  ਰੁੱਖ enum_ਮੁੱਲ;
	  ਰੁੱਖ enum_decl;
	  ਤਾਰਕਿਕ ਵੇਖਿਆ_comma;
	  c_token *token;
	  location_t comma_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	  location_t decl_loc, ਮੁੱਲ_loc;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	    {
	      report_bad_enum_name (parser);
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE, ਨਿਰਾ);
	      ਮੁੱਲਾਂ = error_mark_ਗੰਢ;
	      ਰੋਕੋ;
	    }
	  token = c_parser_peek_token (parser);
	  enum_id = token->ਮੁੱਲ;
	  /* Set the location in case we create a decl now.  */
	  c_parser_ਸੈੱਟ_ਸਰੋਤ_position_from_token (token);
	  decl_loc = ਮੁੱਲ_loc = token->location;
	  c_parser_consume_token (parser);
	  /* Parse any specified attributes.  */
	  ਰੁੱਖ std_attrs = NULL_ਰੁੱਖ;
	  ਜੇ (c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
	    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  ਰੁੱਖ enum_attrs = chainon (std_attrs,
				     c_parser_gnu_ਗੁਣ (parser));
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EQ))
	    {
	      c_parser_consume_token (parser);
	      ਮੁੱਲ_loc = c_parser_peek_token (parser)->location;
	      enum_ਮੁੱਲ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਮੁੱਲ_loc,
						     (c_parser_ਵਿਅੰਜਕ_no_commas
						      (parser, ਨਿਰਾ)),
						     ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
	    }
	  ਨਹੀਂਤਾਂ
	    enum_ਮੁੱਲ = NULL_ਰੁੱਖ;
	  enum_decl = build_enumerator (decl_loc, ਮੁੱਲ_loc,
					&the_enum, enum_id, enum_ਮੁੱਲ);
	  ਜੇ (enum_attrs)
	    decl_ਗੁਣ (&ਰੁੱਖ_PURPOSE (enum_decl), enum_attrs, 0);
	  ਰੁੱਖ_CHAIN (enum_decl) = ਮੁੱਲਾਂ;
	  ਮੁੱਲਾਂ = enum_decl;
	  ਵੇਖਿਆ_comma = ਝੂਠ;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    {
	      comma_loc = c_parser_peek_token (parser)->location;
	      ਵੇਖਿਆ_comma = ਸੱਚ;
	      c_parser_consume_token (parser);
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      ਜੇ (ਵੇਖਿਆ_comma)
		pedwarn_c90 (comma_loc, OPT_Wpedantic,
			     "comma at end of enumerator list");
	      c_parser_consume_token (parser);
	      ਰੋਕੋ;
	    }
	  ਜੇ (!ਵੇਖਿਆ_comma)
	    {
	      c_parser_error (parser, "expected %<,%> or %<}%>");
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE, ਨਿਰਾ);
	      ਮੁੱਲਾਂ = error_mark_ਗੰਢ;
	      ਰੋਕੋ;
	    }
	}
      postfix_attrs = c_parser_gnu_ਗੁਣ (parser);
      ret.spec = ਅੰਤ_enum (type, nreverse (ਮੁੱਲਾਂ),
			      chainon (std_attrs,
				       chainon (attrs, postfix_attrs)));
      ret.ਕਿਸਮ = ctsk_tagdef;
      ret.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
      ret.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
      ret.has_enum_type_specifier = fixed_underlying_type != NULL_ਰੁੱਖ;
      timevar_ਕੱਢੋ (TV_PARSE_ENUM);
      ਵਾਪਸ ret;
    }
  ਨਹੀਂਤਾਂ ਜੇ (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ਗੰਢ;
      ret.ਕਿਸਮ = ctsk_tagref;
      ret.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
      ret.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
      ret.has_enum_type_specifier = ਝੂਠ;
      ਵਾਪਸ ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations (treat enum forward declarations in
     GNU C analogously to struct and union forward declarations in
     standard C).  */
  ਜੇ (have_std_attrs && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  ਜੇ (fixed_underlying_type == NULL_ਰੁੱਖ)
    {
      ret = parser_xref_ਟੈਗ (ident_loc, ENUMERAL_TYPE, ident, have_std_attrs,
			     std_attrs, ਝੂਠ);
      /* In ISO C, enumerated types without a fixed underlying type
	 can be referred to only if already defined.  */
      ਜੇ (pedantic && !COMPLETE_TYPE_P (ret.spec))
	{
	  gcc_assert (ident);
	  pedwarn (enum_loc, OPT_Wpedantic,
		   "ISO C forbids forward references to %<enum%> types");
	}
    }
  ਵਾਪਸ ret;
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
ਖਾਲੀ_ਥਾਵਾਂ
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

ਸਥਿਰ ਬਣਤਰ c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  ਬਣਤਰ c_typespec ret;
  ਤਾਰਕਿਕ have_std_attrs;
  ਰੁੱਖ std_attrs = NULL_ਰੁੱਖ;
  ਰੁੱਖ attrs;
  ਰੁੱਖ ident = NULL_ਰੁੱਖ;
  location_t struct_loc;
  location_t ident_loc = UNKNOWN_LOCATION;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ;
  ਚੋਣ (c_parser_peek_token (parser)->keyword)
    {
    ਹਾਲਤ RID_STRUCT:
      ਕੋਡ = ਰਿਕਾਰਡ_TYPE;
      ਰੋਕੋ;
    ਹਾਲਤ RID_UNION:
      ਕੋਡ = UNION_TYPE;
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }
  struct_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  have_std_attrs = c_parser_nth_token_starts_std_ਗੁਣ (parser, 1);
  ਜੇ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  attrs = c_parser_gnu_ਗੁਣ (parser);

  /* Set the location in case we create a decl now.  */
  c_parser_ਸੈੱਟ_ਸਰੋਤ_position_from_token (c_parser_peek_token (parser));

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->ਮੁੱਲ;
      ident_loc = c_parser_peek_token (parser)->location;
      struct_loc = ident_loc;
      c_parser_consume_token (parser);
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      ਵਰਗ c_struct_parse_info *struct_info;
      ਰੁੱਖ type = ਸ਼ੁਰੂ_struct (struct_loc, ਕੋਡ, ident, &struct_info);
      ਰੁੱਖ postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      ਰੁੱਖ contents;
      ਰੁੱਖ ਵਿਅੰਜਕ = ਨਿਰਾ;
      timevar_ਧੱਕੋ (TV_PARSE_STRUCT);
      contents = NULL_ਰੁੱਖ;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_DEFS))
	{
	  ਰੁੱਖ name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ਜੇ (!parens.require_open (parser))
	    ਜਾਓ ਸਿਰਾ_at_defs;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->ਮੁੱਲ;
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	      ਜਾਓ ਸਿਰਾ_at_defs;
	    }
	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	  contents = nreverse (objc_get_class_ivars (name));
	}
    ਸਿਰਾ_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      ਜਦੋਂ (ਸੱਚ)
	{
	  ਰੁੱਖ decls;
	  /* Parse any stray semicolon.  */
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	    {
	      location_t semicolon_loc
		= c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (semicolon_loc);
	      richloc.ਜੋੜੋ_fixit_remove ();
	      pedwarn (&richloc, OPT_Wpedantic,
		       "extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      ਜਾਰੀ;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      ਰੋਕੋ;
	    }
	  /* Accept #pragmas at struct scope.  */
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_struct, ਨਿਰਾ, NULL_ਰੁੱਖ);
	      ਜਾਰੀ;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser, &ਵਿਅੰਜਕ);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn (c_parser_peek_token (parser)->location, 0,
			 "no semicolon at end of struct or union");
	      ਨਹੀਂਤਾਂ ਜੇ (parser->error
		       || !c_parser_ਅਗਲਾ_token_starts_declspecs (parser))
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE, ਨਿਰਾ);
		  ਰੋਕੋ;
		}

	      /* If we come here, we have already emitted an error
		 for an expected `;', identifier or `(', and we also
	         recovered already.  Go on with the next field. */
	    }
	}
      postfix_attrs = c_parser_gnu_ਗੁਣ (parser);
      ret.spec = ਅੰਤ_struct (struct_loc, type, nreverse (contents),
				chainon (std_attrs,
					 chainon (attrs, postfix_attrs)),
				struct_info, &ਵਿਅੰਜਕ);
      ret.ਕਿਸਮ = ctsk_tagdef;
      ret.ਵਿਅੰਜਕ = ਵਿਅੰਜਕ;
      ret.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
      ret.has_enum_type_specifier = ਝੂਠ;
      timevar_ਕੱਢੋ (TV_PARSE_STRUCT);
      ਵਾਪਸ ret;
    }
  ਨਹੀਂਤਾਂ ਜੇ (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_ਗੰਢ;
      ret.ਕਿਸਮ = ctsk_tagref;
      ret.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
      ret.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
      ret.has_enum_type_specifier = ਝੂਠ;
      ਵਾਪਸ ret;
    }
  /* Attributes may only appear when the members are defined or in
     certain forward declarations.  */
  ਜੇ (have_std_attrs && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected %<;%>");
  /* ??? Existing practice is that GNU attributes are ignored after
     the struct or union keyword when not defining the members.  */
  ret = parser_xref_ਟੈਗ (ident_loc, ਕੋਡ, ident, have_std_attrs, std_attrs,
			 ਝੂਠ);
  ਵਾਪਸ ret;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_struct_declaration (c_parser *parser, ਰੁੱਖ *ਵਿਅੰਜਕ)
{
  ਬਣਤਰ c_declspecs *specs;
  ਰੁੱਖ ਅਗੇਤਰ_attrs;
  ਰੁੱਖ all_ਅਗੇਤਰ_attrs;
  ਰੁੱਖ decls;
  location_t decl_loc;
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_EXTENSION))
    {
      ਪੂਰਨ ext;
      ਰੁੱਖ decl;
      ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      decl = c_parser_struct_declaration (parser, ਵਿਅੰਜਕ);
      restore_extension_diagnostics (ext);
      ਵਾਪਸ decl;
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_STATIC_ASSERT))
    {
      c_parser_static_assert_declaration_no_semi (parser);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  specs = build_null_declspecs ();
  decl_loc = c_parser_peek_token (parser)->location;
  /* Strictly by the standard, we shouldn't allow _Alignas here,
     but it appears to have been intended to allow it there, so
     we're keeping it as it is until WG14 reaches a conclusion
     of N1731.
     <http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1731.pdf>  */
  c_parser_declspecs (parser, specs, ਝੂਠ, ਸੱਚ, ਸੱਚ,
		      ਸੱਚ, ਝੂਠ, ਸੱਚ, ਸੱਚ, cla_nonabstract_decl);
  ਜੇ (parser->error)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਜੇ (!specs->declspecs_ਵੇਖਿਆ_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਅੰਤ_declspecs (specs);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)
      || c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
    {
      ਰੁੱਖ ret;
      ਜੇ (specs->typespec_ਕਿਸਮ == ctsk_none)
	{
	  pedwarn (decl_loc, OPT_Wpedantic,
		   "ISO C forbids member declarations with no members");
	  shadow_ਟੈਗ_warned (specs, pedantic);
	  ret = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ
	{
	  /* Support for unnamed structs or unions as members of
	     structs or unions (which is [a] useful and [b] supports
	     MS P-SDK).  */
	  ਰੁੱਖ attrs = ਨਿਰਾ;

	  ret = grokfield (c_parser_peek_token (parser)->location,
			   build_id_declarator (NULL_ਰੁੱਖ), specs,
			   NULL_ਰੁੱਖ, &attrs, ਵਿਅੰਜਕ);
	  ਜੇ (ret)
	    decl_ਗੁਣ (&ret, attrs, 0);
	}
      ਵਾਪਸ ret;
    }

  /* Provide better error recovery.  Note that a type name here is valid,
     and will be treated as a field name.  */
  ਜੇ (specs->typespec_ਕਿਸਮ == ctsk_tagdef
      && ਰੁੱਖ_ਕੋਡ (specs->type) != ENUMERAL_TYPE
      && c_parser_ਅਗਲਾ_token_starts_declspecs (parser)
      && !c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>, identifier or %<(%>");
      parser->error = ਝੂਠ;
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  pending_xref_error ();
  ਅਗੇਤਰ_attrs = specs->attrs;
  all_ਅਗੇਤਰ_attrs = ਅਗੇਤਰ_attrs;
  specs->attrs = NULL_ਰੁੱਖ;
  decls = NULL_ਰੁੱਖ;
  ਜਦੋਂ (ਸੱਚ)
    {
      /* Declaring one or more declarators or un-named bit-fields.  */
      ਬਣਤਰ c_declarator *declarator;
      ਤਾਰਕਿਕ dummy = ਝੂਠ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	declarator = build_id_declarator (NULL_ਰੁੱਖ);
      ਨਹੀਂਤਾਂ
	declarator = c_parser_declarator (parser,
					  specs->typespec_ਕਿਸਮ != ctsk_none,
					  C_DTR_ਸਾਧਾਰਨ, &dummy);
      ਜੇ (declarator == ਨਿਰਾ)
	{
	  c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
	  ਰੋਕੋ;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON)
	  || c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  || c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)
	  || c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE)
	  || c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  ਰੁੱਖ postfix_attrs = NULL_ਰੁੱਖ;
	  ਰੁੱਖ ਚੌੜਾਈ = NULL_ਰੁੱਖ;
	  ਰੁੱਖ d;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      location_t loc = c_parser_peek_token (parser)->location;
	      ਚੌੜਾਈ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc,
						(c_parser_ਵਿਅੰਜਕ_no_commas
						 (parser, ਨਿਰਾ)),
						ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_gnu_ਗੁਣ (parser);
	  d = grokfield (c_parser_peek_token (parser)->location,
			 declarator, specs, ਚੌੜਾਈ, &all_ਅਗੇਤਰ_attrs, ਵਿਅੰਜਕ);
	  decl_ਗੁਣ (&d, chainon (postfix_attrs,
					all_ਅਗੇਤਰ_attrs), 0);
	  DECL_CHAIN (d) = decls;
	  decls = d;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
	    all_ਅਗੇਤਰ_attrs = chainon (c_parser_gnu_ਗੁਣ (parser),
					ਅਗੇਤਰ_attrs);
	  ਨਹੀਂਤਾਂ
	    all_ਅਗੇਤਰ_attrs = ਅਗੇਤਰ_attrs;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)
		   || c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      /* Semicolon consumed in caller.  */
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_error (parser, "expected %<,%>, %<;%> or %<}%>");
	      ਰੋਕੋ;
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser,
			  "expected %<:%>, %<,%>, %<;%>, %<}%> or "
			  "%<__attribute__%>");
	  ਰੋਕੋ;
	}
    }
  ਵਾਪਸ decls;
}

/* Parse a typeof specifier (a GNU extension adopted in C23).

   typeof-specifier:
     typeof ( expression )
     typeof ( type-name )
     typeof_unqual ( expression )
     typeof_unqual ( type-name )
*/

ਸਥਿਰ ਬਣਤਰ c_typespec
c_parser_typeof_specifier (c_parser *parser)
{
  ਤਾਰਕਿਕ is_unqual;
  ਤਾਰਕਿਕ is_std;
  ਬਣਤਰ c_typespec ret;
  ret.ਕਿਸਮ = ctsk_typeof;
  ret.spec = error_mark_ਗੰਢ;
  ret.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ret.ਵਿਅੰਜਕ_const_operands = ਸੱਚ;
  ret.has_enum_type_specifier = ਝੂਠ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_TYPEOF))
    {
      is_unqual = ਝੂਠ;
      ਰੁੱਖ spelling = c_parser_peek_token (parser)->ਮੁੱਲ;
      is_std = (flag_isoc23
		&& strcmp (IDENTIFIER_ਸੂਚਕ (spelling), "typeof") == 0);
    }
  ਨਹੀਂਤਾਂ
    {
      gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_TYPEOF_UNQUAL));
      is_unqual = ਸੱਚ;
      ਰੁੱਖ spelling = c_parser_peek_token (parser)->ਮੁੱਲ;
      is_std = strcmp (IDENTIFIER_ਸੂਚਕ (spelling), "typeof_unqual") == 0;
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ਵਿੱਚ_typeof++;
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_typeof--;
      ਵਾਪਸ ret;
    }
  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, cla_prefer_id))
    {
      ਬਣਤਰ c_type_name *type = c_parser_type_name (parser);
      c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_typeof--;
      ਜੇ (type != ਨਿਰਾ)
	{
	  ret.spec = groktypename (type, &ret.ਵਿਅੰਜਕ, &ret.ਵਿਅੰਜਕ_const_operands);
	  ਕੱਢੋ_maybe_ਵਰਤਿਆ (c_type_variably_modified_p (ret.spec));
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਤਾਰਕਿਕ was_vm;
      location_t ਇੱਥੇ = c_parser_peek_token (parser)->location;
      ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
      c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_typeof--;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == COMPONENT_REF
	  && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ.ਮੁੱਲ, 1)))
	error_at (ਇੱਥੇ, "%<typeof%> applied to a bit-field");
      mark_exp_read (ਵਿਅੰਜਕ.ਮੁੱਲ);
      ret.spec = ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ.ਮੁੱਲ);
      was_vm = c_type_variably_modified_p (ret.spec);
      /* This is returned with the type so that when the type is
	 evaluated, this can be evaluated.  */
      ਜੇ (was_vm)
	ret.ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, &ret.ਵਿਅੰਜਕ_const_operands);
      ਕੱਢੋ_maybe_ਵਰਤਿਆ (was_vm);
    }
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਜੇ (ret.spec != error_mark_ਗੰਢ)
    {
      ਜੇ (is_unqual)
	{
	  ਤਾਰਕਿਕ is_array = ਰੁੱਖ_ਕੋਡ (ret.spec) == ARRAY_TYPE;
	  ਪੂਰਨ quals = TYPE_QUALS (strip_array_types (ret.spec));
	  ਜੇ ((is_array ? quals & ~TYPE_QUAL_ATOMIC : quals)
	      != TYPE_UNQUALIFIED)
	    {
	      ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	      ਜੇ (quals & TYPE_QUAL_ATOMIC && is_array)
		ret.spec = c_build_qualified_type (ret.spec,
						   TYPE_QUAL_ATOMIC);
	    }
	}
      ਜੇ (is_std)
	{
	  /* In ISO C terms, _Noreturn is not part of the type of
	     expressions such as &abort, but in GCC it is represented
	     internally as a type qualifier.  */
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ret.spec) == FUNCTION_TYPE
	      && TYPE_QUALS (ret.spec) != TYPE_UNQUALIFIED)
	    ret.spec = TYPE_MAIN_VARIANT (ret.spec);
	  ਨਹੀਂਤਾਂ ਜੇ (FUNCTION_ਸੂਚਕ_TYPE_P (ret.spec)
		   && TYPE_QUALS (ਰੁੱਖ_TYPE (ret.spec)) != TYPE_UNQUALIFIED)
	    ret.spec
	      = c_build_ਸੂਚਕ_type (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ret.spec)));
	}
    }
  ਵਾਪਸ ret;
}

/* Parse an alignment-specifier.

   C11 6.7.5:

   alignment-specifier:
     _Alignas ( type-name )
     _Alignas ( constant-expression )
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_alignas_specifier (c_parser * parser)
{
  ਰੁੱਖ ret = error_mark_ਗੰਢ;
  location_t loc = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ALIGNAS));
  ਰੁੱਖ spelling = c_parser_peek_token (parser)->ਮੁੱਲ;
  c_parser_consume_token (parser);
  ਜੇ (flag_isoc99)
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C99 does not support %qE", spelling);
  ਨਹੀਂਤਾਂ
    pedwarn_c99 (loc, OPT_Wpedantic,
		 "ISO C90 does not support %qE", spelling);
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ ret;
  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, cla_prefer_id))
    {
      ਬਣਤਰ c_type_name *type = c_parser_type_name (parser);
      ਜੇ (type != ਨਿਰਾ)
	ret = c_sizeof_or_alignof_type (loc, groktypename (type, ਨਿਰਾ, ਨਿਰਾ),
					ਝੂਠ, ਸੱਚ, 1);
    }
  ਨਹੀਂਤਾਂ
    ret = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc,
				    c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ),
				    ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ ret;
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
ਸੂਚਕ
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

ਬਣਤਰ c_declarator *
c_parser_declarator (c_parser *parser, ਤਾਰਕਿਕ type_ਵੇਖਿਆ_p, c_dtr_syn ਕਿਸਮ,
		     ਤਾਰਕਿਕ *ਵੇਖਿਆ_id)
{
  /* Parse any initial pointer part.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_MULT))
    {
      ਬਣਤਰ c_declspecs *quals_attrs = build_null_declspecs ();
      ਬਣਤਰ c_declarator *inner;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, ਝੂਠ, ਝੂਠ, ਸੱਚ,
			  ਝੂਠ, ਝੂਠ, ਸੱਚ, ਝੂਠ, cla_prefer_id);
      inner = c_parser_declarator (parser, type_ਵੇਖਿਆ_p, ਕਿਸਮ, ਵੇਖਿਆ_id);
      ਜੇ (inner == ਨਿਰਾ)
	ਵਾਪਸ ਨਿਰਾ;
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ make_ਸੂਚਕ_declarator (quals_attrs, inner);
    }
  /* Now we have a direct declarator, direct abstract declarator or
     nothing (which counts as a direct abstract declarator here).  */
  ਵਾਪਸ c_parser_ਸਿੱਧਾ_declarator (parser, type_ਵੇਖਿਆ_p, ਕਿਸਮ, ਵੇਖਿਆ_id);
}

/* Parse a direct declarator or direct abstract declarator; arguments
   as c_parser_declarator.  */

ਸਥਿਰ ਬਣਤਰ c_declarator *
c_parser_ਸਿੱਧਾ_declarator (c_parser *parser, ਤਾਰਕਿਕ type_ਵੇਖਿਆ_p, c_dtr_syn ਕਿਸਮ,
			    ਤਾਰਕਿਕ *ਵੇਖਿਆ_id)
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

  ਜੇ (ਕਿਸਮ != C_DTR_ABSTRACT
      && c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && ((type_ਵੇਖਿਆ_p
	   && (c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_TYPENAME
	       || c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_CLASSNAME))
	  || c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID))
    {
      ਬਣਤਰ c_declarator *inner
	= build_id_declarator (c_parser_peek_token (parser)->ਮੁੱਲ);
      *ਵੇਖਿਆ_id = ਸੱਚ;
      inner->id_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ਜੇ (c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
	inner->u.id.attrs = c_parser_std_attribute_specifier_sequence (parser);
      ਵਾਪਸ c_parser_ਸਿੱਧਾ_declarator_inner (parser, *ਵੇਖਿਆ_id, inner);
    }

  ਜੇ (ਕਿਸਮ != C_DTR_ਸਾਧਾਰਨ
      && c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_ਵਰਗਫਲ)
      && !c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
    {
      ਬਣਤਰ c_declarator *inner = build_id_declarator (NULL_ਰੁੱਖ);
      inner->id_loc = c_parser_peek_token (parser)->location;
      ਵਾਪਸ c_parser_ਸਿੱਧਾ_declarator_inner (parser, *ਵੇਖਿਆ_id, inner);
    }

  /* Either we are at the end of an abstract declarator, or we have
     parentheses.  */

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      ਰੁੱਖ attrs;
      ਬਣਤਰ c_declarator *inner;
      c_parser_consume_token (parser);
      ਤਾਰਕਿਕ have_gnu_attrs = c_parser_ਅਗਲਾ_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_ਗੁਣ (parser);
      ਜੇ (ਕਿਸਮ != C_DTR_ਸਾਧਾਰਨ
	  && (c_parser_ਅਗਲਾ_token_starts_declspecs (parser)
	      || (!have_gnu_attrs
		  && (c_parser_nth_token_starts_std_ਗੁਣ (parser, 1)
		      || c_parser_ਅਗਲਾ_token_is (parser, CPP_ELLIPSIS)))
	      || c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN)))
	{
	  ਬਣਤਰ c_arg_info *ਦਲੀਲਾਂ
	    = c_parser_parms_declarator (parser, ਕਿਸਮ == C_DTR_ਸਾਧਾਰਨ,
					 attrs, have_gnu_attrs);
	  ਜੇ (ਦਲੀਲਾਂ == ਨਿਰਾ)
	    ਵਾਪਸ ਨਿਰਾ;
	  ਨਹੀਂਤਾਂ
	    {
	      inner = build_id_declarator (NULL_ਰੁੱਖ);
	      ਜੇ (!(ਦਲੀਲਾਂ->types
		    && ਦਲੀਲਾਂ->types != error_mark_ਗੰਢ
		    && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ->types)) == IDENTIFIER_ਗੰਢ)
		  && c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
		{
		  ਰੁੱਖ std_attrs
		    = c_parser_std_attribute_specifier_sequence (parser);
		  ਜੇ (std_attrs)
		    inner = build_attrs_declarator (std_attrs, inner);
		}
	      inner = build_function_declarator (ਦਲੀਲਾਂ, inner);
	      ਵਾਪਸ c_parser_ਸਿੱਧਾ_declarator_inner (parser, *ਵੇਖਿਆ_id,
						       inner);
	    }
	}
      /* A parenthesized declarator.  */
      inner = c_parser_declarator (parser, type_ਵੇਖਿਆ_p, ਕਿਸਮ, ਵੇਖਿਆ_id);
      ਜੇ (inner != ਨਿਰਾ && attrs != ਨਿਰਾ)
	inner = build_attrs_declarator (attrs, inner);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (inner == ਨਿਰਾ)
	    ਵਾਪਸ ਨਿਰਾ;
	  ਨਹੀਂਤਾਂ
	    ਵਾਪਸ c_parser_ਸਿੱਧਾ_declarator_inner (parser, *ਵੇਖਿਆ_id, inner);
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ਵਾਪਸ ਨਿਰਾ;
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (ਕਿਸਮ == C_DTR_ਸਾਧਾਰਨ)
	{
	  c_parser_error (parser, "expected identifier or %<(%>");
	  ਵਾਪਸ ਨਿਰਾ;
	}
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ build_id_declarator (NULL_ਰੁੱਖ);
    }
}

/* Parse part of a direct declarator or direct abstract declarator,
   given that some (in INNER) has already been parsed; ID_PRESENT is
   true if an identifier is present, false for an abstract
   declarator.  */

ਸਥਿਰ ਬਣਤਰ c_declarator *
c_parser_ਸਿੱਧਾ_declarator_inner (c_parser *parser, ਤਾਰਕਿਕ id_present,
				  ਬਣਤਰ c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_ਵਰਗਫਲ)
      && !c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
    {
      location_t brace_loc = c_parser_peek_token (parser)->location;
      ਬਣਤਰ c_declarator *declarator;
      ਬਣਤਰ c_declspecs *quals_attrs = build_null_declspecs ();
      ਬਣਤਰ c_ਵਿਅੰਜਕ dimen;
      dimen.ਮੁੱਲ = NULL_ਰੁੱਖ;
      dimen.original_ਕੋਡ = ERROR_MARK;
      dimen.original_type = NULL_ਰੁੱਖ;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, ਝੂਠ, ਝੂਠ, ਸੱਚ,
			  ਝੂਠ, ਝੂਠ, ਝੂਠ, ਝੂਠ, cla_prefer_id);

      location_t static_loc = UNKNOWN_LOCATION;
      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_STATIC))
	{
	  static_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  ਜੇ (!quals_attrs->declspecs_ਵੇਖਿਆ_p)
	    c_parser_declspecs (parser, quals_attrs, ਝੂਠ, ਝੂਠ, ਸੱਚ,
				ਝੂਠ, ਝੂਠ, ਝੂਠ, ਝੂਠ, cla_prefer_id);
	}
      ਜੇ (!quals_attrs->declspecs_ਵੇਖਿਆ_p)
	quals_attrs = ਨਿਰਾ;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      ਅਚਲ ਤਾਰਕਿਕ static_ਵੇਖਿਆ = (static_loc != UNKNOWN_LOCATION);
      ਤਾਰਕਿਕ ਤਾਰਾ_ਵੇਖਿਆ = ਝੂਠ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_MULT)
	  && c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_ਵਰਗਫਲ)
	{
	  ਤਾਰਾ_ਵੇਖਿਆ = ਸੱਚ;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_ਵਰਗਫਲ))
	dimen = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);

      ਜੇ (static_ਵੇਖਿਆ)
	{
	  ਜੇ (ਤਾਰਾ_ਵੇਖਿਆ)
	    {
	      error_at (static_loc,
			"%<static%> may not be used with an unspecified "
			"variable length array size");
	      /* Prevent further errors.  */
	      ਤਾਰਾ_ਵੇਖਿਆ = ਝੂਠ;
	      dimen.ਮੁੱਲ = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!dimen.ਮੁੱਲ)
	    error_at (static_loc,
		      "%<static%> may not be used without an array size");
	}

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_ਵਰਗਫਲ))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ,
				     "expected %<]%>");
	  ਵਾਪਸ ਨਿਰਾ;
	}
      ਜੇ (dimen.ਮੁੱਲ)
	dimen = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (brace_loc, dimen, ਸੱਚ, ਸੱਚ);
      declarator = build_array_declarator (brace_loc, dimen.ਮੁੱਲ, quals_attrs,
					   static_ਵੇਖਿਆ, ਤਾਰਾ_ਵੇਖਿਆ);
      ਜੇ (declarator == ਨਿਰਾ)
	ਵਾਪਸ ਨਿਰਾ;
      ਜੇ (c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
	{
	  ਰੁੱਖ std_attrs
	    = c_parser_std_attribute_specifier_sequence (parser);
	  ਜੇ (std_attrs)
	    inner = build_attrs_declarator (std_attrs, inner);
	}
      inner = ਸੈੱਟ_array_declarator_inner (declarator, inner);
      ਵਾਪਸ c_parser_ਸਿੱਧਾ_declarator_inner (parser, id_present, inner);
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      ਰੁੱਖ attrs;
      ਬਣਤਰ c_arg_info *ਦਲੀਲਾਂ;
      c_parser_consume_token (parser);
      ਤਾਰਕਿਕ have_gnu_attrs = c_parser_ਅਗਲਾ_token_is_keyword (parser,
							    RID_ATTRIBUTE);
      attrs = c_parser_gnu_ਗੁਣ (parser);
      ਦਲੀਲਾਂ = c_parser_parms_declarator (parser, id_present, attrs,
					have_gnu_attrs);
      ਜੇ (ਦਲੀਲਾਂ == ਨਿਰਾ)
	ਵਾਪਸ ਨਿਰਾ;
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (!(ਦਲੀਲਾਂ->types
		&& ਦਲੀਲਾਂ->types != error_mark_ਗੰਢ
		&& ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ->types)) == IDENTIFIER_ਗੰਢ)
	      && c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
	    {
	      ਰੁੱਖ std_attrs
		= c_parser_std_attribute_specifier_sequence (parser);
	      ਜੇ (std_attrs)
		inner = build_attrs_declarator (std_attrs, inner);
	    }
	  inner = build_function_declarator (ਦਲੀਲਾਂ, inner);
	  ਵਾਪਸ c_parser_ਸਿੱਧਾ_declarator_inner (parser, id_present, inner);
	}
    }
  ਵਾਪਸ inner;
}

/* Parse a parameter list or identifier list, including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list.  ID_LIST_OK is true if an identifier list
   is acceptable; such a list must not have attributes at the start.
   HAVE_GNU_ATTRS says whether any gnu-attributes (including empty
   attributes) were present (in which case standard attributes cannot
   occur).  */

ਸਥਿਰ ਬਣਤਰ c_arg_info *
c_parser_parms_declarator (c_parser *parser, ਤਾਰਕਿਕ id_list_ok, ਰੁੱਖ attrs,
			   ਤਾਰਕਿਕ have_gnu_attrs)
{
  ਧੱਕੋ_scope ();
  declare_parm_level ();
  /* If the list starts with an identifier, it is an identifier list.
     Otherwise, it is either a prototype list or an empty list.  */
  ਜੇ (id_list_ok
      && !attrs
      && c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID

      /* Look ahead to detect typos in type names.  */
      && c_parser_peek_2nd_token (parser)->type != CPP_NAME
      && c_parser_peek_2nd_token (parser)->type != CPP_MULT
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
      && c_parser_peek_2nd_token (parser)->type != CPP_OPEN_ਵਰਗਫਲ
      && c_parser_peek_2nd_token (parser)->type != CPP_KEYWORD)
    {
      ਰੁੱਖ list = NULL_ਰੁੱਖ, *nextp = &list;
      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	     && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID)
	{
	  *nextp = build_ਰੁੱਖ_list (NULL_ਰੁੱਖ,
				    c_parser_peek_token (parser)->ਮੁੱਲ);
	  nextp = & ਰੁੱਖ_CHAIN (*nextp);
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COMMA))
	    ਰੋਕੋ;
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_error (parser, "expected identifier");
	      ਰੋਕੋ;
	    }
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ਬਣਤਰ c_arg_info *ret = build_arg_info ();
	  ret->types = list;
	  c_parser_consume_token (parser);
	  ਕੱਢੋ_scope ();
	  ਵਾਪਸ ret;
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ਕੱਢੋ_scope ();
	  ਵਾਪਸ ਨਿਰਾ;
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਬਣਤਰ c_arg_info *ret
	= c_parser_parms_list_declarator (parser, attrs, ਨਿਰਾ, have_gnu_attrs);
      ਕੱਢੋ_scope ();
      ਵਾਪਸ ret;
    }
}

/* Parse a parameter list (possibly empty), including the closing
   parenthesis but not the opening one.  ATTRS are the gnu-attributes
   at the start of the list; if HAVE_GNU_ATTRS, there were some such
   attributes (possibly empty, in which case ATTRS is NULL_TREE),
   which means standard attributes cannot start the list.  EXPR is
   NULL or an expression that needs to be evaluated for the side
   effects of array size expressions in the parameters.  */

ਸਥਿਰ ਬਣਤਰ c_arg_info *
c_parser_parms_list_declarator (c_parser *parser, ਰੁੱਖ attrs, ਰੁੱਖ ਵਿਅੰਜਕ,
				ਤਾਰਕਿਕ have_gnu_attrs)
{
  ਤਾਰਕਿਕ bad_parm = ਝੂਠ;

  /* ??? Following the old parser, forward parameter declarations may
     use abstract declarators, and if no real parameter declarations
     follow the forward declarations then this is not diagnosed.  Also
     note as above that gnu-attributes are ignored as the only contents of
     the parentheses, or as the only contents after forward
     declarations.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
    {
      ਬਣਤਰ c_arg_info *ret = build_arg_info ();
      c_parser_consume_token (parser);
      ਵਾਪਸ ret;
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_ELLIPSIS) && !have_gnu_attrs)
    {
      ਬਣਤਰ c_arg_info *ret = build_arg_info ();

      ret->types = NULL_ਰੁੱਖ;
      pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C requires a named argument before %<...%> "
		   "before C23");
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ret->no_named_ਦਲੀਲਾਂ_stdarg_p = ਸੱਚ;
	  c_parser_consume_token (parser);
	  ਵਾਪਸ ret;
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ਵਾਪਸ ਨਿਰਾ;
	}
    }
  /* Nonempty list of parameters, either terminated with semicolon
     (forward declarations; recurse) or with close parenthesis (normal
     function) or with ", ... )" (variadic function).  */
  ਜਦੋਂ (ਸੱਚ)
    {
      /* Parse a parameter.  */
      ਬਣਤਰ c_parm *parm = c_parser_parameter_declaration (parser, attrs,
							    have_gnu_attrs);
      attrs = NULL_ਰੁੱਖ;
      have_gnu_attrs = ਝੂਠ;
      ਜੇ (parm == ਨਿਰਾ)
	bad_parm = ਸੱਚ;
      ਨਹੀਂਤਾਂ
	ਧੱਕੋ_parm_decl (parm, &ਵਿਅੰਜਕ);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	{
	  ਰੁੱਖ new_attrs;
	  c_parser_consume_token (parser);
	  mark_forward_parm_decls ();
	  ਤਾਰਕਿਕ new_have_gnu_attrs
	    = c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE);
	  new_attrs = c_parser_gnu_ਗੁਣ (parser);
	  ਵਾਪਸ c_parser_parms_list_declarator (parser, new_attrs, ਵਿਅੰਜਕ,
						 new_have_gnu_attrs);
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (bad_parm)
	    ਵਾਪਸ ਨਿਰਾ;
	  ਨਹੀਂਤਾਂ
	    ਵਾਪਸ get_parm_info (ਝੂਠ, ਵਿਅੰਜਕ);
	}
      ਜੇ (!c_parser_require (parser, CPP_COMMA,
			     "expected %<;%>, %<,%> or %<)%>",
			     UNKNOWN_LOCATION, ਝੂਠ))
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	  ਵਾਪਸ ਨਿਰਾ;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      c_parser_consume_token (parser);
	      ਜੇ (bad_parm)
		ਵਾਪਸ ਨਿਰਾ;
	      ਨਹੀਂਤਾਂ
		ਵਾਪਸ get_parm_info (ਸੱਚ, ਵਿਅੰਜਕ);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ਵਾਪਸ ਨਿਰਾ;
	    }
	}
    }
}

/* Parse a parameter declaration.  ATTRS are the gnu-attributes at the
   start of the declaration if it is the first parameter;
   HAVE_GNU_ATTRS is true if there were any gnu-attributes there (even
   empty) there.  */

ਸਥਿਰ ਬਣਤਰ c_parm *
c_parser_parameter_declaration (c_parser *parser, ਰੁੱਖ attrs,
				ਤਾਰਕਿਕ have_gnu_attrs)
{
  ਬਣਤਰ c_declspecs *specs;
  ਬਣਤਰ c_declarator *declarator;
  ਰੁੱਖ ਅਗੇਤਰ_attrs;
  ਰੁੱਖ postfix_attrs = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ dummy = ਝੂਠ;

  /* Accept #pragmas between parameter declarations.  */
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA))
    c_parser_pragma (parser, pragma_param, ਨਿਰਾ, NULL_ਰੁੱਖ);

  ਜੇ (!c_parser_ਅਗਲਾ_token_starts_declspecs (parser)
      && !c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ (parser->error)
	ਵਾਪਸ ਨਿਰਾ;
      c_parser_ਸੈੱਟ_ਸਰੋਤ_position_from_token (token);
      ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, cla_prefer_type))
	{
	  auto_diagnostic_ਸਮੂਹ d;
	  name_hint hint = lookup_name_fuzzy (token->ਮੁੱਲ,
					      FUZZY_LOOKUP_TYPENAME,
					      token->location);
	  ਜੇ (ਅਚਲ ਅੱਖਰ *suggestion = hint.suggestion ())
	    {
	      gcc_rich_location richloc (token->location);
	      richloc.ਜੋੜੋ_fixit_replace (suggestion);
	      error_at (&richloc,
			"unknown type name %qE; did you mean %qs?",
			token->ਮੁੱਲ, suggestion);
	    }
	  ਨਹੀਂਤਾਂ
	    error_at (token->location, "unknown type name %qE", token->ਮੁੱਲ);
	  parser->error = ਸੱਚ;
	}
      /* ??? In some Objective-C cases '...' isn't applicable so there
	 should be a different message.  */
      ਨਹੀਂਤਾਂ
	c_parser_error (parser,
			"expected declaration specifiers or %<...%>");
      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_parameter (parser);
      ਵਾਪਸ ਨਿਰਾ;
    }

  location_t ਸ਼ੁਰੂ_loc = c_parser_peek_token (parser)->location;

  specs = build_null_declspecs ();
  ਜੇ (attrs)
    {
      declspecs_ਜੋੜੋ_attrs (ਨਿਵੇਸ਼_location, specs, attrs);
      attrs = NULL_ਰੁੱਖ;
    }
  c_parser_declspecs (parser, specs, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਝੂਠ,
		      !have_gnu_attrs, ਸੱਚ, cla_nonabstract_decl);
  ਅੰਤ_declspecs (specs);
  /* When the param is declared, its type is a top level type, we should
     call verify_counted_by_for_top_anonymous_type.  */
  ਜੇ (specs->typespec_ਕਿਸਮ == ctsk_tagdef)
    verify_counted_by_for_ਸਿਖਰ_anonymous_type (specs->type);

  pending_xref_error ();
  ਅਗੇਤਰ_attrs = specs->attrs;
  specs->attrs = NULL_ਰੁੱਖ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_ਕਿਸਮ != ctsk_none,
				    C_DTR_PARM, &dummy);
  ਜੇ (declarator == ਨਿਰਾ)
    {
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_COMMA, ਨਿਰਾ);
      ਵਾਪਸ ਨਿਰਾ;
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
    postfix_attrs = c_parser_gnu_ਗੁਣ (parser);

  /* Generate a location for the parameter, ranging from the start of the
     initial token to the end of the final token.

     If we have a identifier, then use it for the caret location, e.g.

       extern int callee (int one, int (*two)(int, int), float three);
                                   ~~~~~~^~~~~~~~~~~~~~

     otherwise, reuse the start location for the caret location e.g.:

       extern int callee (int one, int (*)(int, int), float three);
                                   ^~~~~~~~~~~~~~~~~
  */
  location_t ਸਿਰਾ_loc = parser->ਆਖਰੀ_token_location;

  /* Find any cdk_id declarator; determine if we have an identifier.  */
  c_declarator *id_declarator = declarator;
  ਜਦੋਂ (id_declarator && id_declarator->ਕਿਸਮ != cdk_id)
    id_declarator = id_declarator->declarator;
  location_t caret_loc = (id_declarator->u.id.id
			  ? id_declarator->id_loc
			  : ਸ਼ੁਰੂ_loc);
  location_t param_loc = make_location (caret_loc, ਸ਼ੁਰੂ_loc, ਸਿਰਾ_loc);

  ਵਾਪਸ build_c_parm (specs, chainon (postfix_attrs, ਅਗੇਤਰ_attrs),
		       declarator, param_loc);
}

/* Parse a string literal in an asm expression.  It should not be
   translated, and wide string literals are an error although
   permitted by the syntax.  This is a GNU extension.

   asm-string-literal:
     string-literal
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_asm_string_literal (c_parser *parser)
{
  ਰੁੱਖ str;
  ਪੂਰਨ save_flag = warn_overlength_ਲੜੀਆਂ;
  warn_overlength_ਲੜੀਆਂ = 0;
  str = c_parser_string_literal (parser, ਝੂਠ, ਝੂਠ).ਮੁੱਲ;
  warn_overlength_ਲੜੀਆਂ = save_flag;
  ਵਾਪਸ str;
}

/* Parse a simple asm expression.  This is used in restricted
   contexts, where a full expression with inputs and outputs does not
   make sense.  This is a GNU extension.

   simple-asm-expr:
     asm ( asm-string-literal )
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_simple_asm_ਵਿਅੰਜਕ (c_parser *parser)
{
  ਰੁੱਖ str;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ NULL_ਰੁੱਖ;
  str = c_parser_asm_string_literal (parser);
  ਜੇ (!parens.require_close (parser))
    {
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਵਾਪਸ str;
}

ਸਥਿਰ ਰੁੱਖ
c_parser_gnu_attribute_any_ਸ਼ਬਦ (c_parser *parser)
{
  ਰੁੱਖ attr_name = NULL_ਰੁੱਖ;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD))
    {
      /* ??? See comment above about what keywords are accepted here.  */
      ਤਾਰਕਿਕ ok;
      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_STATIC:
	ਹਾਲਤ RID_UNSIGNED:
	ਹਾਲਤ RID_LONG:
	ਹਾਲਤ RID_CONST:
	ਹਾਲਤ RID_EXTERN:
	ਹਾਲਤ RID_ਰਜਿਸਟਰ:
	ਹਾਲਤ RID_TYPEDEF:
	ਹਾਲਤ RID_SHORT:
	ਹਾਲਤ RID_INLINE:
	ਹਾਲਤ RID_NORETURN:
	ਹਾਲਤ RID_VOLATILE:
	ਹਾਲਤ RID_SIGNED:
	ਹਾਲਤ RID_AUTO:
	ਹਾਲਤ RID_RESTRICT:
	ਹਾਲਤ RID_COMPLEX:
	ਹਾਲਤ RID_THREAD:
	ਹਾਲਤ RID_INT:
	ਹਾਲਤ RID_CHAR:
	ਹਾਲਤ RID_FLOAT:
	ਹਾਲਤ RID_DOUBLE:
	ਹਾਲਤ RID_VOID:
	ਹਾਲਤ RID_DFLOAT32:
	ਹਾਲਤ RID_DFLOAT64:
	ਹਾਲਤ RID_DFLOAT128:
	ਹਾਲਤ RID_DFLOAT64X:
	CASE_RID_FLOATN_NX:
	ਹਾਲਤ RID_BOOL:
	ਹਾਲਤ RID_BITINT:
	ਹਾਲਤ RID_FRACT:
	ਹਾਲਤ RID_ACCUM:
	ਹਾਲਤ RID_SAT:
	ਹਾਲਤ RID_TRANSACTION_ATOMIC:
	ਹਾਲਤ RID_TRANSACTION_CANCEL:
	ਹਾਲਤ RID_ATOMIC:
	ਹਾਲਤ RID_AUTO_TYPE:
	ਹਾਲਤ RID_CONSTEXPR:
	ਹਾਲਤ RID_INT_N_0:
	ਹਾਲਤ RID_INT_N_1:
	ਹਾਲਤ RID_INT_N_2:
	ਹਾਲਤ RID_INT_N_3:
	  ok = ਸੱਚ;
	  ਰੋਕੋ;
	ਮੂਲ:
	  ok = ਝੂਠ;
	  ਰੋਕੋ;
	}
      ਜੇ (!ok)
	ਵਾਪਸ NULL_ਰੁੱਖ;

      /* Accept __attribute__((__const)) as __attribute__((const)) etc.  */
      attr_name = ridpointers[(ਪੂਰਨ) c_parser_peek_token (parser)->keyword];
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    attr_name = c_parser_peek_token (parser)->ਮੁੱਲ;

  ਵਾਪਸ attr_name;
}

/* Parse attribute arguments.  This is a common form of syntax
   covering all currently valid GNU and standard attributes.

   gnu-attribute-arguments:
     identifier
     identifier , nonempty-expr-list
     expr-list

   where the "identifier" must not be declared as a type.  ??? Why not
   allow identifiers declared as types to start the arguments?  */

ਸਥਿਰ ਰੁੱਖ
c_parser_attribute_arguments (c_parser *parser, ਤਾਰਕਿਕ takes_identifier,
			      ਤਾਰਕਿਕ require_string, ਤਾਰਕਿਕ assume_attr,
			      ਤਾਰਕਿਕ allow_ਖਾਲੀ_ਥਾਵਾਂ_ਦਲੀਲਾਂ)
{
  vec<ਰੁੱਖ, va_gc> *ਵਿਅੰਜਕ_list;
  ਰੁੱਖ attr_ਦਲੀਲਾਂ;
  /* Parse the attribute contents.  If they start with an
     identifier which is followed by a comma or close
     parenthesis, then the arguments start with that
     identifier; otherwise they are an expression list.
     In objective-c the identifier may be a classname.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && (c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID
	  || (c_dialect_objc ()
	      && c_parser_peek_token (parser)->id_ਕਿਸਮ
	      == C_ID_CLASSNAME))
      && ((c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	  || (c_parser_peek_2nd_token (parser)->type
	      == CPP_CLOSE_PAREN))
      && (takes_identifier
	  || (c_dialect_objc ()
	      && !assume_attr
	      && c_parser_peek_token (parser)->id_ਕਿਸਮ
	      == C_ID_CLASSNAME)))
    {
      ਰੁੱਖ arg1 = c_parser_peek_token (parser)->ਮੁੱਲ;
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	attr_ਦਲੀਲਾਂ = build_ਰੁੱਖ_list (NULL_ਰੁੱਖ, arg1);
      ਨਹੀਂਤਾਂ
	{
	  ਰੁੱਖ ਰੁੱਖ_list;
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ_list = c_parser_ਵਿਅੰਜਕ_list (parser, ਝੂਠ, ਸੱਚ,
					  ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
	  ਰੁੱਖ_list = build_ਰੁੱਖ_list_vec (ਵਿਅੰਜਕ_list);
	  attr_ਦਲੀਲਾਂ = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, arg1, ਰੁੱਖ_list);
	  release_ਰੁੱਖ_ਸਦਿਸ਼ (ਵਿਅੰਜਕ_list);
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ਜੇ (!allow_ਖਾਲੀ_ਥਾਵਾਂ_ਦਲੀਲਾਂ)
	    error_at (c_parser_peek_token (parser)->location,
		      "parentheses must be omitted if "
		      "attribute argument list is empty");
	  attr_ਦਲੀਲਾਂ = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (require_string)
	{
	  /* The only valid argument for this attribute is a string
	     literal.  Handle this specially here to avoid accepting
	     string literals with excess parentheses.  */
	  ਰੁੱਖ string = c_parser_string_literal (parser, ਝੂਠ, ਸੱਚ).ਮੁੱਲ;
	  attr_ਦਲੀਲਾਂ = build_ਰੁੱਖ_list (NULL_ਰੁੱਖ, string);
	}
      ਨਹੀਂਤਾਂ ਜੇ (assume_attr)
	{
	  ਰੁੱਖ cond
	    = c_parser_conditional_ਵਿਅੰਜਕ (parser, ਨਿਰਾ, NULL_ਰੁੱਖ).ਮੁੱਲ;
	  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    attr_ਦਲੀਲਾਂ = build_ਰੁੱਖ_list (NULL_ਰੁੱਖ, cond);
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ ਰੁੱਖ_list;
	      c_parser_consume_token (parser);
	      ਵਿਅੰਜਕ_list = c_parser_ਵਿਅੰਜਕ_list (parser, ਝੂਠ, ਸੱਚ,
					      ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
	      ਰੁੱਖ_list = build_ਰੁੱਖ_list_vec (ਵਿਅੰਜਕ_list);
	      attr_ਦਲੀਲਾਂ = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, cond, ਰੁੱਖ_list);
	      release_ਰੁੱਖ_ਸਦਿਸ਼ (ਵਿਅੰਜਕ_list);
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  ਵਿਅੰਜਕ_list = c_parser_ਵਿਅੰਜਕ_list (parser, ਝੂਠ, ਸੱਚ,
					  ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
	  attr_ਦਲੀਲਾਂ = build_ਰੁੱਖ_list_vec (ਵਿਅੰਜਕ_list);
	  release_ਰੁੱਖ_ਸਦਿਸ਼ (ਵਿਅੰਜਕ_list);
	}
    }
  ਵਾਪਸ attr_ਦਲੀਲਾਂ;
}

/* Parse (possibly empty) gnu-attributes.  This is a GNU extension.

   gnu-attributes:
ਖਾਲੀ_ਥਾਵਾਂ
     gnu-attributes gnu-attribute

   gnu-attribute:
     __attribute__ ( ( gnu-attribute-list ) )

   gnu-attribute-list:
     gnu-attrib
     gnu-attribute_list , gnu-attrib

   gnu-attrib:
ਖਾਲੀ_ਥਾਵਾਂ
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

ਸਥਿਰ ਰੁੱਖ
c_parser_gnu_attribute (c_parser *parser, ਰੁੱਖ attrs,
			ਤਾਰਕਿਕ expect_comma = ਝੂਠ, ਤਾਰਕਿਕ ਖਾਲੀ_ਥਾਵਾਂ_ok = ਸੱਚ)
{
  ਤਾਰਕਿਕ comma_ਪਹਿਲਾ = c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA);
  ਜੇ (!comma_ਪਹਿਲਾ
      && !c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && !c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD))
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ਜੇ (!ਖਾਲੀ_ਥਾਵਾਂ_ok)
	ਵਾਪਸ attrs;
    }

  ਰੁੱਖ attr_name = c_parser_gnu_attribute_any_ਸ਼ਬਦ (parser);
  ਜੇ (attr_name == NULL_ਰੁੱਖ)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  attr_name = canonicalize_attr_name (attr_name);
  c_parser_consume_token (parser);

  ਰੁੱਖ attr;
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_OPEN_PAREN))
    {
      ਜੇ (expect_comma && !comma_ਪਹਿਲਾ)
	{
	  /* A comma is missing between the last attribute on the chain
	     and this one.  */
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      attr = build_ਰੁੱਖ_list (attr_name, NULL_ਰੁੱਖ);
      /* Add this attribute to the list.  */
      attrs = chainon (attrs, attr);
      ਵਾਪਸ attrs;
    }
  c_parser_consume_token (parser);

  ਰੁੱਖ attr_ਦਲੀਲਾਂ
    = c_parser_attribute_arguments (parser,
				    attribute_takes_identifier_p (attr_name),
				    ਝੂਠ,
				    is_attribute_p ("assume", attr_name),
				    ਸੱਚ);

  attr = build_ਰੁੱਖ_list (attr_name, attr_ਦਲੀਲਾਂ);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  ਨਹੀਂਤਾਂ
    {
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (expect_comma && !comma_ਪਹਿਲਾ)
    {
      /* A comma is missing between the last attribute on the chain
	 and this one.  */
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  /* Add this attribute to the list.  */
  attrs = chainon (attrs, attr);
  ਵਾਪਸ attrs;
}

ਸਥਿਰ ਰੁੱਖ
c_parser_gnu_ਗੁਣ (c_parser *parser)
{
  ਰੁੱਖ attrs = NULL_ਰੁੱਖ;
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      ਤਾਰਕਿਕ save_translate_ਲੜੀਆਂ_p = parser->translate_ਲੜੀਆਂ_p;
      parser->translate_ਲੜੀਆਂ_p = ਝੂਠ;
      /* Consume the `__attribute__' keyword.  */
      c_parser_consume_token (parser);
      /* Look for the two `(' tokens.  */
      ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_ਲੜੀਆਂ_p = save_translate_ਲੜੀਆਂ_p;
	  ਵਾਪਸ attrs;
	}
      ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  parser->translate_ਲੜੀਆਂ_p = save_translate_ਲੜੀਆਂ_p;
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	  ਵਾਪਸ attrs;
	}
      /* Parse the attribute list.  Require a comma between successive
	 (possibly empty) attributes.  */
      ਲਈ (ਤਾਰਕਿਕ expect_comma = ਝੂਠ; ; expect_comma = ਸੱਚ)
	{
	  /* Parse a single attribute.  */
	  ਰੁੱਖ attr = c_parser_gnu_attribute (parser, attrs, expect_comma);
	  ਜੇ (attr == error_mark_ਗੰਢ)
	    ਵਾਪਸ attrs;
	  ਜੇ (!attr)
	    ਰੋਕੋ;
	  attrs = attr;
      }

      /* Look for the two `)' tokens.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	{
	  parser->translate_ਲੜੀਆਂ_p = save_translate_ਲੜੀਆਂ_p;
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ਵਾਪਸ attrs;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	{
	  parser->translate_ਲੜੀਆਂ_p = save_translate_ਲੜੀਆਂ_p;
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ਵਾਪਸ attrs;
	}
      parser->translate_ਲੜੀਆਂ_p = save_translate_ਲੜੀਆਂ_p;
    }

  ਵਾਪਸ attrs;
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

ਸਥਿਰ ਖਾਲੀ
c_parser_ਸੰਤੁਲਿਤ_token_sequence (c_parser *parser)
{
  ਜਦੋਂ (ਸੱਚ)
    {
      c_token *token = c_parser_peek_token (parser);
      ਚੋਣ (token->type)
	{
	ਹਾਲਤ CPP_OPEN_BRACE:
	  {
	    matching_braces braces;
	    braces.consume_open (parser);
	    c_parser_ਸੰਤੁਲਿਤ_token_sequence (parser);
	    braces.require_close (parser);
	    ਰੋਕੋ;
	  }

	ਹਾਲਤ CPP_OPEN_PAREN:
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    c_parser_ਸੰਤੁਲਿਤ_token_sequence (parser);
	    parens.require_close (parser);
	    ਰੋਕੋ;
	  }

	ਹਾਲਤ CPP_OPEN_ਵਰਗਫਲ:
	  c_parser_consume_token (parser);
	  c_parser_ਸੰਤੁਲਿਤ_token_sequence (parser);
	  c_parser_require (parser, CPP_CLOSE_ਵਰਗਫਲ, "expected %<]%>");
	  ਰੋਕੋ;

	ਹਾਲਤ CPP_CLOSE_BRACE:
	ਹਾਲਤ CPP_CLOSE_PAREN:
	ਹਾਲਤ CPP_CLOSE_ਵਰਗਫਲ:
	ਹਾਲਤ CPP_EOF:
	  ਵਾਪਸ;

	ਹਾਲਤ CPP_PRAGMA:
	  c_parser_consume_pragma (parser);
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਰੋਕੋ;

	ਮੂਲ:
	  c_parser_consume_token (parser);
	  ਰੋਕੋ;
	}
    }
}

/* Parse arguments of omp::directive or omp::decl attribute.

   directive-name ,[opt] clause-list[opt]

   For directive just remember the tokens in a vector for subsequent
   parsing.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_directive_ਦਲੀਲਾਂ (c_parser *parser, ਰੁੱਖ attribute, ਤਾਰਕਿਕ decl_p)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n = 1;
  c_token *ਪਹਿਲਾ = c_parser_peek_token (parser);
  ਜੇ (!c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n)
      || (c_parser_peek_nth_token_raw (parser, n)->type
	  != CPP_CLOSE_PAREN))
    {
      c_parser_ਸੰਤੁਲਿਤ_token_sequence (parser);
      ਰੁੱਖ_ਮੁੱਲ (attribute) = NULL_ਰੁੱਖ;
      ਵਾਪਸ;
    }
  ਜੇ (n == 1)
    {
      error_at (ਪਹਿਲਾ->location, "expected OpenMP directive name");
      ਰੁੱਖ_ਮੁੱਲ (attribute) = NULL_ਰੁੱਖ;
      ਵਾਪਸ;
    }
  vec<c_token, va_gc> *v;
  vec_alloc (v, n - 1);
  ਲਈ (--n; n; --n)
    {
      c_token *tok = c_parser_peek_token (parser);
      v->ਤੇਜ਼_ਧੱਕੋ (*tok);
      c_parser_consume_token (parser);
    }
  ਰੁੱਖ arg = make_ਗੰਢ (C_TOKEN_VEC);
  C_TOKEN_VEC_ਟੋਕਨ (arg) = v;
  ਜੇ (decl_p)
    ਰੁੱਖ_ਜਨਤਕ (arg) = 1;
  ਰੁੱਖ_ਮੁੱਲ (attribute) = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, arg, ਰੁੱਖ_ਮੁੱਲ (attribute));
}

/* Parse arguments of omp::sequence attribute.

   omp::[opt] directive-attr [ , omp::[opt] directive-attr ]...  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_sequence_ਦਲੀਲਾਂ (c_parser *parser, ਰੁੱਖ attribute)
{
  ਕਰੋ
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ (token->type == CPP_NAME
	  && strcmp (IDENTIFIER_ਸੂਚਕ (token->ਮੁੱਲ), "omp") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_SCOPE)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  token = c_parser_peek_token (parser);
	}
      ਤਾਰਕਿਕ directive = ਝੂਠ;
      ਅਚਲ ਅੱਖਰ *p;
      ਜੇ (token->type != CPP_NAME)
	p = "";
      ਨਹੀਂਤਾਂ
	p = IDENTIFIER_ਸੂਚਕ (token->ਮੁੱਲ);
      ਜੇ (strcmp (p, "directive") == 0)
	directive = ਸੱਚ;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "sequence") != 0)
	{
	  error_at (token->location, "expected %<directive%> or %<sequence%>");
	  ਬਿਨਾਨਿਸ਼ਾਨੀ nesting_ਡੂੰਘਾਈ = 0;

	  ਜਦੋਂ (ਸੱਚ)
	    {
	      /* Peek at the next token.  */
	      token = c_parser_peek_token (parser);
	      /* If we've reached the token we want, consume it and stop.  */
	      ਜੇ ((token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
		  && !nesting_ਡੂੰਘਾਈ)
		ਰੋਕੋ;
	      /* If we've run out of tokens, stop.  */
	      ਜੇ (token->type == CPP_EOF)
		ਰੋਕੋ;
	      ਜੇ (token->type == CPP_PRAGMA_EOL && parser->ਵਿੱਚ_pragma)
		ਰੋਕੋ;
	      ਜੇ (token->type == CPP_OPEN_BRACE
		  || token->type == CPP_OPEN_PAREN
		  || token->type == CPP_OPEN_ਵਰਗਫਲ)
		++nesting_ਡੂੰਘਾਈ;
	      ਨਹੀਂਤਾਂ ਜੇ (token->type == CPP_CLOSE_BRACE
		       || token->type == CPP_CLOSE_PAREN
		       || token->type == CPP_CLOSE_ਵਰਗਫਲ)
		{
		  ਜੇ (nesting_ਡੂੰਘਾਈ-- == 0)
		    ਰੋਕੋ;
		}
	      /* Consume this token.  */
	      c_parser_consume_token (parser);
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COMMA))
	    ਰੋਕੋ;
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}
      c_parser_consume_token (parser);
      matching_parens parens;
      ਜੇ (parens.require_open (parser))
	{
	  ਜੇ (directive)
	    c_parser_omp_directive_ਦਲੀਲਾਂ (parser, attribute, ਝੂਠ);
	  ਨਹੀਂਤਾਂ
	    c_parser_omp_sequence_ਦਲੀਲਾਂ (parser, attribute);
	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COMMA))
	    ਰੋਕੋ;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COMMA))
	ਰੋਕੋ;
      ਨਹੀਂਤਾਂ
	c_parser_consume_token (parser);
    }
  ਜਦੋਂ (1);
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

ਸਥਿਰ ਰੁੱਖ
c_parser_std_attribute (c_parser *parser, ਤਾਰਕਿਕ for_tm)
{
  c_token *token = c_parser_peek_token (parser);
  ਰੁੱਖ ns, name, attribute;

  /* Parse the attribute-token.  */
  ਜੇ (token->type != CPP_NAME && token->type != CPP_KEYWORD)
    {
      c_parser_error (parser, "expected identifier");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  name = canonicalize_attr_name (token->ਮੁੱਲ);
  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SCOPE)
      || (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON)
	  && (c_parser_peek_token (parser)->flags & COLON_SCOPE) != 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      ns = name;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      token = c_parser_peek_token (parser);
      ਜੇ (token->type != CPP_NAME && token->type != CPP_KEYWORD)
	{
	  c_parser_error (parser, "expected identifier");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      name = canonicalize_attr_name (token->ਮੁੱਲ);
      c_parser_consume_token (parser);
    }
  ਨਹੀਂਤਾਂ
    ns = NULL_ਰੁੱਖ;
  attribute = build_ਰੁੱਖ_list (build_ਰੁੱਖ_list (ns, name), NULL_ਰੁੱਖ);

  /* Parse the arguments, if any.  */
  ਅਚਲ attribute_spec *as = lookup_attribute_spec (ਰੁੱਖ_PURPOSE (attribute));
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_OPEN_PAREN))
    {
      ਜੇ ((flag_openmp || flag_openmp_simd)
	  && ns
	  && is_attribute_p ("omp", ns)
	  && (is_attribute_p ("directive", name)
	      || is_attribute_p ("sequence", name)
	      || is_attribute_p ("decl", name)))
	{
	  error ("%<omp::%E%> attribute requires argument", name);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਜਾਓ ਬਾਹਰਲਾ;
    }
  {
    location_t open_loc = c_parser_peek_token (parser)->location;
    matching_parens parens;
    parens.consume_open (parser);
    ਜੇ ((as && as->max_ਲੰਮਾਈ == 0)
	/* Special-case the transactional-memory attribute "outer",
	   which is specially handled but not registered as an
	   attribute, to avoid allowing arbitrary balanced token
	   sequences as arguments.  */
	|| is_attribute_p ("outer", name))
      {
	error_at (open_loc, "%qE attribute does not take any arguments", name);
	parens.skip_until_ਮਿਲਿਆ_close (parser);
	ਵਾਪਸ error_mark_ਗੰਢ;
      }
    /* If this is a fake attribute created to handle -Wno-attributes,
       we must skip parsing the arguments.  */
    ਜੇ (as && !attribute_ignored_p (as))
      {
	ਤਾਰਕਿਕ takes_identifier
	  = (ns != NULL_ਰੁੱਖ
	     && strcmp (IDENTIFIER_ਸੂਚਕ (ns), "gnu") == 0
	     && attribute_takes_identifier_p (name));
	ਤਾਰਕਿਕ require_string
	  = (ns == NULL_ਰੁੱਖ
	     && (strcmp (IDENTIFIER_ਸੂਚਕ (name), "deprecated") == 0
		 || strcmp (IDENTIFIER_ਸੂਚਕ (name), "nodiscard") == 0));
	ਤਾਰਕਿਕ assume_attr
	  = (ns != NULL_ਰੁੱਖ
	     && strcmp (IDENTIFIER_ਸੂਚਕ (ns), "gnu") == 0
	     && strcmp (IDENTIFIER_ਸੂਚਕ (name), "assume") == 0);
	ਰੁੱਖ_ਮੁੱਲ (attribute)
	  = c_parser_attribute_arguments (parser, takes_identifier,
					  require_string, assume_attr, ਝੂਠ);
      }
    ਨਹੀਂਤਾਂ
      {
	ਜੇ ((flag_openmp || flag_openmp_simd)
	    && ns
	    && is_attribute_p ("omp", ns))
	  {
	    ਜੇ (is_attribute_p ("directive", name))
	      {
		c_parser_omp_directive_ਦਲੀਲਾਂ (parser, attribute, ਝੂਠ);
		parens.skip_until_ਮਿਲਿਆ_close (parser);
		ਵਾਪਸ attribute;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (is_attribute_p ("decl", name))
	      {
		ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_directive_ਦਲੀਲਾਂ (parser, attribute, ਸੱਚ);
		parens.skip_until_ਮਿਲਿਆ_close (parser);
		ਵਾਪਸ attribute;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (is_attribute_p ("sequence", name))
	      {
		ਰੁੱਖ_ਮੁੱਲ (ਰੁੱਖ_PURPOSE (attribute))
		  = get_identifier ("directive");
		c_parser_omp_sequence_ਦਲੀਲਾਂ (parser, attribute);
		parens.skip_until_ਮਿਲਿਆ_close (parser);
		ਰੁੱਖ_ਮੁੱਲ (attribute) = nreverse (ਰੁੱਖ_ਮੁੱਲ (attribute));
		ਵਾਪਸ attribute;
	      }
	  }
	c_parser_ਸੰਤੁਲਿਤ_token_sequence (parser);
      }
    parens.require_close (parser);
  }
 ਬਾਹਰਲਾ:
  ਜੇ (ns == NULL_ਰੁੱਖ && !for_tm && !as)
    {
      /* An attribute with standard syntax and no namespace specified
	 is a constraint violation if it is not one of the known
	 standard attributes.  Diagnose it here with a pedwarn and
	 then discard it to prevent a duplicate warning later.  */
      pedwarn (ਨਿਵੇਸ਼_location, OPT_Wattributes, "%qE attribute ignored",
	       name);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਵਾਪਸ attribute;
}

ਸਥਿਰ ਰੁੱਖ
c_parser_std_attribute_list (c_parser *parser, ਤਾਰਕਿਕ for_tm)
{
  ਰੁੱਖ ਗੁਣ = NULL_ਰੁੱਖ;
  ਜਦੋਂ (ਸੱਚ)
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ (token->type == CPP_CLOSE_ਵਰਗਫਲ)
	ਰੋਕੋ;
      ਜੇ (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}
      ਰੁੱਖ attribute = c_parser_std_attribute (parser, for_tm);
      ਜੇ (attribute != error_mark_ਗੰਢ)
	{
	  ਰੁੱਖ_CHAIN (attribute) = ਗੁਣ;
	  ਗੁਣ = attribute;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COMMA))
	ਰੋਕੋ;
    }
  ਵਾਪਸ ਗੁਣ;
}

ਸਥਿਰ ਰੁੱਖ
c_parser_std_attribute_specifier (c_parser *parser, ਤਾਰਕਿਕ for_tm)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਜੇ (!c_parser_require (parser, CPP_OPEN_ਵਰਗਫਲ, "expected %<[%>"))
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਜੇ (!c_parser_require (parser, CPP_OPEN_ਵਰਗਫਲ, "expected %<[%>"))
    {
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ, "expected %<]%>");
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਰੁੱਖ ਗੁਣ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_EXTENSION))
    {
      ਸਵੈਚਾਲਿਤ ext = disable_extension_diagnostics ();
      c_parser_consume_token (parser);
      ਗੁਣ = c_parser_std_attribute_list (parser, for_tm);
      restore_extension_diagnostics (ext);
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (!for_tm)
	pedwarn_c11 (loc, OPT_Wpedantic,
		     "ISO C does not support %<[[]]%> attributes before C23");
      ਗੁਣ = c_parser_std_attribute_list (parser, for_tm);
    }
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ, "expected %<]%>");
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ, "expected %<]%>");
  ਵਾਪਸ nreverse (ਗੁਣ);
}

/* Look past an optional balanced token sequence of raw look-ahead
   tokens starting with the *Nth token.  *N is updated to point to the
   following token.  Return true if such a sequence was found, false
   if the tokens parsed were not balanced.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *n)
{
  ਜਦੋਂ (ਸੱਚ)
    {
      c_token *token = c_parser_peek_nth_token_raw (parser, *n);
      ਚੋਣ (token->type)
	{
	ਹਾਲਤ CPP_OPEN_BRACE:
	  {
	    ++*n;
	    ਜੇ (c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ਜੇ (token->type == CPP_CLOSE_BRACE)
		  ++*n;
		ਨਹੀਂਤਾਂ
		  ਵਾਪਸ ਝੂਠ;
	      }
	    ਨਹੀਂਤਾਂ
	      ਵਾਪਸ ਝੂਠ;
	    ਰੋਕੋ;
	  }

	ਹਾਲਤ CPP_OPEN_PAREN:
	  {
	    ++*n;
	    ਜੇ (c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ਜੇ (token->type == CPP_CLOSE_PAREN)
		  ++*n;
		ਨਹੀਂਤਾਂ
		  ਵਾਪਸ ਝੂਠ;
	      }
	    ਨਹੀਂਤਾਂ
	      ਵਾਪਸ ਝੂਠ;
	    ਰੋਕੋ;
	  }

	ਹਾਲਤ CPP_OPEN_ਵਰਗਫਲ:
	  {
	    ++*n;
	    ਜੇ (c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, n))
	      {
		token = c_parser_peek_nth_token_raw (parser, *n);
		ਜੇ (token->type == CPP_CLOSE_ਵਰਗਫਲ)
		  ++*n;
		ਨਹੀਂਤਾਂ
		  ਵਾਪਸ ਝੂਠ;
	      }
	    ਨਹੀਂਤਾਂ
	      ਵਾਪਸ ਝੂਠ;
	    ਰੋਕੋ;
	  }

	ਹਾਲਤ CPP_CLOSE_BRACE:
	ਹਾਲਤ CPP_CLOSE_PAREN:
	ਹਾਲਤ CPP_CLOSE_ਵਰਗਫਲ:
	ਹਾਲਤ CPP_EOF:
	  ਵਾਪਸ ਸੱਚ;

	ਮੂਲ:
	  ++*n;
	  ਰੋਕੋ;
	}
    }
}

/* Return whether standard attributes start with the Nth token.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_nth_token_starts_std_ਗੁਣ (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n)
{
  ਜੇ (!(c_parser_peek_nth_token (parser, n)->type == CPP_OPEN_ਵਰਗਫਲ
	&& c_parser_peek_nth_token (parser, n + 1)->type == CPP_OPEN_ਵਰਗਫਲ))
    ਵਾਪਸ ਝੂਠ;
  /* In C, '[[' must start attributes.  In Objective-C, we need to
     check whether '[[' is matched by ']]'.  */
  ਜੇ (!c_dialect_objc ())
    ਵਾਪਸ ਸੱਚ;
  n += 2;
  ਜੇ (!c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n))
    ਵਾਪਸ ਝੂਠ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  ਜੇ (token->type != CPP_CLOSE_ਵਰਗਫਲ)
    ਵਾਪਸ ਝੂਠ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  ਵਾਪਸ token->type == CPP_CLOSE_ਵਰਗਫਲ;
}

/* Skip standard attribute tokens starting at Nth token (with 1 as the
   next token), return index of the first token after the standard
   attribute tokens, or N on failure.  */

ਸਥਿਰ ਮਾਪ_t
c_parser_skip_std_attribute_spec_seq (c_parser *parser, ਮਾਪ_t n)
{
  ਮਾਪ_t orig_n = n;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਜੇ (c_parser_peek_nth_token_raw (parser, n)->type == CPP_OPEN_ਵਰਗਫਲ
	  && (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_OPEN_ਵਰਗਫਲ))
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ m = n + 2;
	  ਜੇ (!c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &m))
	    ਵਾਪਸ orig_n;
	  c_token *token = c_parser_peek_nth_token_raw (parser, m);
	  ਜੇ (token->type != CPP_CLOSE_ਵਰਗਫਲ)
	    ਵਾਪਸ orig_n;
	  token = c_parser_peek_nth_token_raw (parser, m + 1);
	  ਜੇ (token->type != CPP_CLOSE_ਵਰਗਫਲ)
	    ਵਾਪਸ orig_n;
	  n = m + 2;
	}
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  ਵਾਪਸ n;
}

ਸਥਿਰ ਰੁੱਖ
c_parser_std_attribute_specifier_sequence (c_parser *parser)
{
  ਰੁੱਖ ਗੁਣ = NULL_ਰੁੱਖ;
  ਕਰੋ
    {
      ਰੁੱਖ attrs = c_parser_std_attribute_specifier (parser, ਝੂਠ);
      ਗੁਣ = chainon (ਗੁਣ, attrs);
    }
  ਜਦੋਂ (c_parser_nth_token_starts_std_ਗੁਣ (parser, 1));
  ਵਾਪਸ ਗੁਣ;
}

/* Parse a type name (C90 6.5.5, C99 6.7.6, C11 6.7.7).  ALIGNAS_OK
   says whether alignment specifiers are OK (only in cases that might
   be the type name of a compound literal).

   type-name:
     specifier-qualifier-list abstract-declarator[opt]
*/

ਬਣਤਰ c_type_name *
c_parser_type_name (c_parser *parser, ਤਾਰਕਿਕ alignas_ok)
{
  ਬਣਤਰ c_declspecs *specs = build_null_declspecs ();
  ਬਣਤਰ c_declarator *declarator;
  ਬਣਤਰ c_type_name *ret;
  ਤਾਰਕਿਕ dummy = ਝੂਠ;
  c_parser_declspecs (parser, specs, ਝੂਠ, ਸੱਚ, ਸੱਚ, alignas_ok, ਝੂਠ,
		      ਝੂਠ, ਸੱਚ, cla_prefer_type);
  ਜੇ (!specs->declspecs_ਵੇਖਿਆ_p)
    {
      c_parser_error (parser, "expected specifier-qualifier-list");
      ਵਾਪਸ ਨਿਰਾ;
    }
  ਜੇ (specs->type != error_mark_ਗੰਢ)
    {
      pending_xref_error ();
      ਅੰਤ_declspecs (specs);
      /* When the typename is declared, its type is a top level type, we should
	 call verify_counted_by_for_top_anonymous_type.  */
      ਜੇ (specs->typespec_ਕਿਸਮ == ctsk_tagdef)
	verify_counted_by_for_ਸਿਖਰ_anonymous_type (specs->type);
    }
  declarator = c_parser_declarator (parser,
				    specs->typespec_ਕਿਸਮ != ctsk_none,
				    C_DTR_ABSTRACT, &dummy);
  ਜੇ (declarator == ਨਿਰਾ)
    ਵਾਪਸ ਨਿਰਾ;
  ret = XOBNEW (&parser_obstack, ਬਣਤਰ c_type_name);
  ret->specs = specs;
  ret->declarator = declarator;
  ਵਾਪਸ ret;
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_initializer (c_parser *parser, ਰੁੱਖ decl)
{
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    ਵਾਪਸ c_parser_braced_init (parser, NULL_ਰੁੱਖ, ਝੂਠ, ਨਿਰਾ,
				 decl != error_mark_ਗੰਢ
				 && C_DECL_VARIABLE_ਮਾਪ (decl));
  ਨਹੀਂਤਾਂ
    {
      ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
      location_t loc = c_parser_peek_token (parser)->location;
      ret = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਜੇ (decl != error_mark_ਗੰਢ && C_DECL_VARIABLE_ਮਾਪ (decl))
	{
	  error_at (loc,
		    "variable-sized object may not be initialized except "
		    "with an empty initializer");
	  ret.ਸੈੱਟ_error ();
	}
      /* This is handled mostly by gimplify.cc, but we have to deal with
	 not warning about int x = x; as it is a GCC extension to turn off
	 this warning but only if warn_init_self is zero.  */
      ਜੇ (VAR_P (decl)
	  && !DECL_EXTERNAL (decl)
	  && !ਰੁੱਖ_STATIC (decl)
	  && ret.ਮੁੱਲ == decl
	  && !warning_enabled_at (DECL_ਸਰੋਤ_LOCATION (decl), OPT_Winit_self))
	suppress_warning (decl, OPT_Winit_self);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ret.ਮੁੱਲ) != STRING_CST
	  && (ਰੁੱਖ_ਕੋਡ (ret.ਮੁੱਲ) != COMPOUND_LITERAL_ਵਿਅੰਜਕ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL
					    (ret.ਮੁੱਲ))))
	ret = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ret, ਸੱਚ, ਸੱਚ, ਸੱਚ);
      ਵਾਪਸ ret;
    }
}

/* The location of the last comma within the current initializer list,
   or UNKNOWN_LOCATION if not within one.  */

location_t ਆਖਰੀ_init_list_comma;

/* Parse a braced initializer list.  TYPE is the type specified for a
   compound literal, and NULL_TREE for other initializers and for
   nested braced lists.  NESTED_P is true for nested braced lists,
   false for the list of a compound literal or the list that is the
   top-level initializer in a declaration.  VARSIZE_P indicates
   whether the object to be initialized has a variable size.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_braced_init (c_parser *parser, ਰੁੱਖ type, ਤਾਰਕਿਕ nested_p,
		      ਬਣਤਰ obstack *outer_obstack, ਤਾਰਕਿਕ varsize_p)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਬਣਤਰ obstack braced_init_obstack;
  location_t brace_loc = c_parser_peek_token (parser)->location;
  gcc_obstack_init (&braced_init_obstack);
  gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE));
  ਤਾਰਕਿਕ save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = ਝੂਠ;
  ਤਾਰਕਿਕ zero_init_padding_ਬਿੱਟ = ਝੂਠ;
  matching_braces braces;
  braces.consume_open (parser);
  ਜੇ (nested_p)
    {
      ਅੰਤ_implicit_inits (brace_loc, outer_obstack);
      ਧੱਕੋ_init_level (brace_loc, 0, &braced_init_obstack);
    }
  ਨਹੀਂਤਾਂ
    really_ਸ਼ੁਰੂ_incremental_init (type);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
    {
      pedwarn_c11 (brace_loc, OPT_Wpedantic,
		   "ISO C forbids empty initializer braces before C23");
      ਜੇ (flag_isoc23)
	zero_init_padding_ਬਿੱਟ = ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (varsize_p)
	error_at (brace_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      ਜਦੋਂ (ਸੱਚ)
	{
	  c_parser_initelt (parser, &braced_init_obstack);
	  ਜੇ (parser->error)
	    ਰੋਕੋ;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    {
	      ਆਖਰੀ_init_list_comma = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      /* CPP_EMBED should be always in between two CPP_COMMA
		 tokens.  */
	      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EMBED))
		{
		  c_token *embed = c_parser_peek_token (parser);
		  c_parser_consume_token (parser);
		  c_ਵਿਅੰਜਕ embed_val;
		  embed_val.ਮੁੱਲ = embed->ਮੁੱਲ;
		  embed_val.original_ਕੋਡ = RAW_ਅੰਕੜੇ_CST;
		  embed_val.original_type = integer_type_ਗੰਢ;
		  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&embed_val, embed->get_range ());
		  embed_val.m_decimal = 0;
		  process_init_element (embed->location, embed_val, ਝੂਠ,
					&braced_init_obstack);
		  gcc_checking_assert (c_parser_ਅਗਲਾ_token_is (parser,
							       CPP_COMMA));
		  ਆਖਰੀ_init_list_comma = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		}
	    }
	  ਨਹੀਂਤਾਂ
	    ਰੋਕੋ;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	    ਰੋਕੋ;
	}
    }
  c_omp_array_section_p = save_c_omp_array_section_p;
  c_token *ਅਗਲਾ_tok = c_parser_peek_token (parser);
  ਜੇ (ਅਗਲਾ_tok->type != CPP_CLOSE_BRACE)
    {
      ret.ਸੈੱਟ_error ();
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = ਨਿਰਾ;
      braces.skip_until_ਮਿਲਿਆ_close (parser);
      ਕੱਢੋ_init_level (brace_loc, 0, &braced_init_obstack, ਆਖਰੀ_init_list_comma);
      obstack_free (&braced_init_obstack, ਨਿਰਾ);
      ਵਾਪਸ ret;
    }
  location_t close_loc = ਅਗਲਾ_tok->location;
  c_parser_consume_token (parser);
  ret = ਕੱਢੋ_init_level (brace_loc, 0, &braced_init_obstack, close_loc);
  ਜੇ (zero_init_padding_ਬਿੱਟ
      && ret.ਮੁੱਲ
      && ਰੁੱਖ_ਕੋਡ (ret.ਮੁੱਲ) == CONSTRUCTOR)
    CONSTRUCTOR_ZERO_PADDING_ਬਿੱਟ (ret.ਮੁੱਲ) = 1;
  obstack_free (&braced_init_obstack, ਨਿਰਾ);
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, brace_loc, close_loc);
  ਵਾਪਸ ret;
}

/* Parse a nested initializer, including designators.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_initelt (c_parser *parser, ਬਣਤਰ obstack * braced_init_obstack)
{
  /* Parse any designator or designator list.  A single array
     designator may have the subsequent "=" omitted in GNU C, but a
     longer list or a structure member designator may not.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      /* Old-style structure member designator.  */
      ਸੈੱਟ_init_label (c_parser_peek_token (parser)->location,
		      c_parser_peek_token (parser)->ਮੁੱਲ,
		      c_parser_peek_token (parser)->location,
		      braced_init_obstack);
      /* Use the colon as the error location.  */
      pedwarn (c_parser_peek_2nd_token (parser)->location, OPT_Wpedantic,
	       "obsolete use of designated initializer with %<:%>");
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  ਨਹੀਂਤਾਂ
    {
      /* des_seen is 0 if there have been no designators, 1 if there
	 has been a single array designator and 2 otherwise.  */
      ਪੂਰਨ des_ਵੇਖਿਆ = 0;
      /* Location of a designator.  */
      location_t des_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_ਵਰਗਫਲ)
	     || c_parser_ਅਗਲਾ_token_is (parser, CPP_DOT))
	{
	  ਪੂਰਨ des_prev = des_ਵੇਖਿਆ;
	  ਜੇ (!des_ਵੇਖਿਆ)
	    des_loc = c_parser_peek_token (parser)->location;
	  ਜੇ (des_ਵੇਖਿਆ < 2)
	    des_ਵੇਖਿਆ++;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_DOT))
	    {
	      des_ਵੇਖਿਆ = 2;
	      c_parser_consume_token (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		{
		  ਸੈੱਟ_init_label (des_loc, c_parser_peek_token (parser)->ਮੁੱਲ,
				  c_parser_peek_token (parser)->location,
				  braced_init_obstack);
		  c_parser_consume_token (parser);
		}
	      ਨਹੀਂਤਾਂ
		{
		  ਬਣਤਰ c_ਵਿਅੰਜਕ init;
		  init.ਸੈੱਟ_error ();
		  init.original_ਕੋਡ = ERROR_MARK;
		  init.original_type = ਨਿਰਾ;
		  c_parser_error (parser, "expected identifier");
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_COMMA, ਨਿਰਾ);
		  process_init_element (ਨਿਵੇਸ਼_location, init, ਝੂਠ,
					braced_init_obstack);
		  ਵਾਪਸ;
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਬਣਤਰ c_ਵਿਅੰਜਕ ਪਹਿਲਾ_ਵਿਅੰਜਕ;
	      ਰੁੱਖ ਪਹਿਲਾ, ਦੂਜਾ;
	      location_t ellipsis_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
	      location_t array_ਸੂਚਕਾਂਕ_loc = UNKNOWN_LOCATION;
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
	      ਜੇ (des_prev == 1 && c_dialect_objc ())
		{
		  des_ਵੇਖਿਆ = des_prev;
		  ਰੋਕੋ;
		}
	      ਜੇ (des_prev == 0 && c_dialect_objc ())
		{
		  /* This might be an array designator or an
		     Objective-C message expression.  If the former,
		     continue parsing here; if the latter, parse the
		     remainder of the initializer given the starting
		     primary-expression.  ??? It might make sense to
		     distinguish when des_prev == 1 as well; see
		     previous comment.  */
		  ਰੁੱਖ rec, ਦਲੀਲਾਂ;
		  ਬਣਤਰ c_ਵਿਅੰਜਕ mexpr;
		  c_parser_consume_token (parser);
		  ਜੇ (c_parser_peek_token (parser)->type == CPP_NAME
		      && ((c_parser_peek_token (parser)->id_ਕਿਸਮ
			   == C_ID_TYPENAME)
			  || (c_parser_peek_token (parser)->id_ਕਿਸਮ
			      == C_ID_CLASSNAME)))
		    {
		      /* Type name receiver.  */
		      ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
		      c_parser_consume_token (parser);
		      rec = objc_get_class_reference (id);
		      ਜਾਓ parse_ਸੁਨੇਹਾ_ਦਲੀਲਾਂ;
		    }
		  array_ਸੂਚਕਾਂਕ_loc = c_parser_peek_token (parser)->location;
		  ਪਹਿਲਾ_ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
		  mark_exp_read (ਪਹਿਲਾ_ਵਿਅੰਜਕ.ਮੁੱਲ);
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_ELLIPSIS)
		      || c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_ਵਰਗਫਲ))
		    ਜਾਓ array_desig_after_ਪਹਿਲਾ;
		  ਪਹਿਲਾ = ਪਹਿਲਾ_ਵਿਅੰਜਕ.ਮੁੱਲ;
		  /* Expression receiver.  So far only one part
		     without commas has been parsed; there might be
		     more of the expression.  */
		  rec = ਪਹਿਲਾ;
		  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		    {
		      ਬਣਤਰ c_ਵਿਅੰਜਕ ਅਗਲਾ;
		      location_t comma_loc, exp_loc;
		      comma_loc = c_parser_peek_token (parser)->location;
		      c_parser_consume_token (parser);
		      exp_loc = c_parser_peek_token (parser)->location;
		      ਅਗਲਾ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
		      ਅਗਲਾ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (exp_loc, ਅਗਲਾ,
						       ਸੱਚ, ਸੱਚ);
		      rec = build_compound_ਵਿਅੰਜਕ (comma_loc, rec, ਅਗਲਾ.ਮੁੱਲ);
		    }
		parse_ਸੁਨੇਹਾ_ਦਲੀਲਾਂ:
		  /* Now parse the objc-message-args.  */
		  ਦਲੀਲਾਂ = c_parser_objc_ਸੁਨੇਹਾ_ਦਲੀਲਾਂ (parser);
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ,
					     "expected %<]%>");
		  mexpr.ਮੁੱਲ
		    = objc_build_ਸੁਨੇਹਾ_ਵਿਅੰਜਕ (rec, ਦਲੀਲਾਂ);
		  mexpr.original_ਕੋਡ = ERROR_MARK;
		  mexpr.original_type = ਨਿਰਾ;
		  mexpr.m_decimal = 0;
		  /* Now parse and process the remainder of the
		     initializer, starting with this message
		     expression as a primary-expression.  */
		  c_parser_initval (parser, &mexpr, braced_init_obstack);
		  ਵਾਪਸ;
		}
	      c_parser_consume_token (parser);
	      array_ਸੂਚਕਾਂਕ_loc = c_parser_peek_token (parser)->location;
	      ਪਹਿਲਾ_ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	      mark_exp_read (ਪਹਿਲਾ_ਵਿਅੰਜਕ.ਮੁੱਲ);
	    array_desig_after_ਪਹਿਲਾ:
	      ਪਹਿਲਾ_ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (array_ਸੂਚਕਾਂਕ_loc,
						     ਪਹਿਲਾ_ਵਿਅੰਜਕ,
						     ਸੱਚ, ਸੱਚ);
	      ਪਹਿਲਾ = ਪਹਿਲਾ_ਵਿਅੰਜਕ.ਮੁੱਲ;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_ELLIPSIS))
		{
		  ellipsis_loc = c_parser_peek_token (parser)->location;
		  c_parser_consume_token (parser);
		  ਦੂਜਾ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ellipsis_loc,
						     (c_parser_ਵਿਅੰਜਕ_no_commas
						      (parser, ਨਿਰਾ)),
						     ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
		  mark_exp_read (ਦੂਜਾ);
		}
	      ਨਹੀਂਤਾਂ
		ਦੂਜਾ = NULL_ਰੁੱਖ;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_ਵਰਗਫਲ))
		{
		  c_parser_consume_token (parser);
		  ਸੈੱਟ_init_ਸੂਚਕਾਂਕ (array_ਸੂਚਕਾਂਕ_loc, ਪਹਿਲਾ, ਦੂਜਾ,
				  braced_init_obstack);
		  ਜੇ (ਦੂਜਾ)
		    pedwarn (ellipsis_loc, OPT_Wpedantic,
			     "ISO C forbids specifying range of elements to initialize");
		}
	      ਨਹੀਂਤਾਂ
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ,
					   "expected %<]%>");
	    }
	}
      ਜੇ (des_ਵੇਖਿਆ >= 1)
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EQ))
	    {
	      pedwarn_c90 (des_loc, OPT_Wpedantic,
			   "ISO C90 forbids specifying subobject "
			   "to initialize");
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (des_ਵੇਖਿਆ == 1)
		pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
			 "obsolete use of designated initializer without %<=%>");
	      ਨਹੀਂਤਾਂ
		{
		  ਬਣਤਰ c_ਵਿਅੰਜਕ init;
		  init.ਸੈੱਟ_error ();
		  init.original_ਕੋਡ = ERROR_MARK;
		  init.original_type = ਨਿਰਾ;
		  c_parser_error (parser, "expected %<=%>");
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_COMMA, ਨਿਰਾ);
		  process_init_element (ਨਿਵੇਸ਼_location, init, ਝੂਠ,
					braced_init_obstack);
		  ਵਾਪਸ;
		}
	    }
	}
    }
  c_parser_initval (parser, ਨਿਰਾ, braced_init_obstack);
}

/* Parse a nested initializer; as c_parser_initializer but parses
   initializers within braced lists, after any designators have been
   applied.  If AFTER is not NULL then it is an Objective-C message
   expression which is the primary-expression starting the
   initializer.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_initval (c_parser *parser, ਬਣਤਰ c_ਵਿਅੰਜਕ *after,
		  ਬਣਤਰ obstack * braced_init_obstack)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ init;
  gcc_assert (!after || c_dialect_objc ());
  location_t loc = c_parser_peek_token (parser)->location;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE) && !after)
    init = c_parser_braced_init (parser, NULL_ਰੁੱਖ, ਸੱਚ,
				 braced_init_obstack, ਝੂਠ);
  ਨਹੀਂਤਾਂ
    {
      init = c_parser_ਵਿਅੰਜਕ_no_commas (parser, after);
      ਜੇ (init.ਮੁੱਲ != NULL_ਰੁੱਖ
	  && ਰੁੱਖ_ਕੋਡ (init.ਮੁੱਲ) != STRING_CST
	  && (ਰੁੱਖ_ਕੋਡ (init.ਮੁੱਲ) != COMPOUND_LITERAL_ਵਿਅੰਜਕ
	      || C_DECL_DECLARED_CONSTEXPR (COMPOUND_LITERAL_ਵਿਅੰਜਕ_DECL
					    (init.ਮੁੱਲ))))
	init = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, init, ਸੱਚ, ਸੱਚ, ਸੱਚ);
    }
  ਰੁੱਖ val = init.ਮੁੱਲ;
  process_init_element (loc, init, ਝੂਠ, braced_init_obstack);

  /* Attempt to optimize large char array initializers into RAW_DATA_CST
     to save compile time and memory even when not using #embed.  */
  ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ vals_ਮੰਜ਼ਿਲ_ignore;
  ਜੇ (vals_ਮੰਜ਼ਿਲ_ignore)
    /* If earlier call determined there is certain number of CPP_COMMA
       CPP_NUMBER tokens with 0-255 int values, but not enough for
       RAW_DATA_CST to be beneficial, don't try to check it again until
       they are all parsed.  */
    --vals_ਮੰਜ਼ਿਲ_ignore;
  ਨਹੀਂਤਾਂ ਜੇ (val
	   && ਰੁੱਖ_ਕੋਡ (val) == INTEGER_CST
	   && ਰੁੱਖ_TYPE (val) == integer_type_ਗੰਢ
	   && c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    ਜੇ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ len = c_maybe_optimize_large_byte_initializer ())
      {
	ਅੱਖਰ buf1[64];
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
	gcc_checking_assert (len >= 64);
	location_t ਆਖਰੀ_loc = UNKNOWN_LOCATION;
	ਲਈ (i = 0; i < 64; ++i)
	  {
	    c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	    ਜੇ (tok->type != CPP_COMMA)
	      ਰੋਕੋ;
	    tok = c_parser_peek_nth_token_raw (parser, 2 + 2 * i);
	    ਜੇ (tok->type != CPP_ਸੰਖਿਆ
		|| ਰੁੱਖ_ਕੋਡ (tok->ਮੁੱਲ) != INTEGER_CST
		|| ਰੁੱਖ_TYPE (tok->ਮੁੱਲ) != integer_type_ਗੰਢ
		|| wi::neg_p (wi::ਮੰਜ਼ਿਲ_wide (tok->ਮੁੱਲ))
		|| wi::ਮੰਜ਼ਿਲ_widest (tok->ਮੁੱਲ) > UCHAR_MAX)
	      ਰੋਕੋ;
	    buf1[i] = (ਅੱਖਰ) ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (tok->ਮੁੱਲ);
	    ਜੇ (i == 0)
	      loc = tok->location;
	    ਆਖਰੀ_loc = tok->location;
	  }
	ਜੇ (i < 64)
	  {
	    vals_ਮੰਜ਼ਿਲ_ignore = i;
	    ਵਾਪਸ;
	  }
	c_token *tok = c_parser_peek_nth_token_raw (parser, 1 + 2 * i);
	/* If 64 CPP_COMMA CPP_NUMBER pairs are followed by CPP_CLOSE_BRACE,
	   punt if len is INT_MAX as that can mean this is a flexible array
	   member and in that case we need one CPP_NUMBER afterwards
	   (as guaranteed for CPP_EMBED).  */
	ਜੇ (tok->type == CPP_CLOSE_BRACE && len != ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
	  len = i;
	ਨਹੀਂਤਾਂ ਜੇ (tok->type != CPP_COMMA
		 || (c_parser_peek_nth_token_raw (parser, 2 + 2 * i)->type
		     != CPP_ਸੰਖਿਆ))
	  {
	    vals_ਮੰਜ਼ਿਲ_ignore = i;
	    ਵਾਪਸ;
	  }
	/* Ensure the STRING_CST fits into 128K.  */
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ max_len = 131072 - offsetof (ਬਣਤਰ ਰੁੱਖ_string, str) - 1;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ orig_len = len;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ off = 0, ਆਖਰੀ = 0;
	ਜੇ (!wi::neg_p (wi::ਮੰਜ਼ਿਲ_wide (val)) && wi::ਮੰਜ਼ਿਲ_widest (val) <= UCHAR_MAX)
	  off = 1;
	len = MIN (len, max_len - off);
	ਅੱਖਰ *buf2 = XNEWVEC (ਅੱਖਰ, len + off);
	ਜੇ (off)
	  buf2[0] = (ਅੱਖਰ) ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (val);
	ਸਮ੍ਰਿਤੀ_ਨਕਲ (buf2 + off, buf1, i);
	ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j < i; ++j)
	  {
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	    c_parser_peek_token (parser);
	    c_parser_consume_token (parser);
	  }
	ਲਈ (; i < len; ++i)
	  {
	    ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	      ਰੋਕੋ;
	    tok = c_parser_peek_2nd_token (parser);
	    ਜੇ (tok->type != CPP_ਸੰਖਿਆ
		|| ਰੁੱਖ_ਕੋਡ (tok->ਮੁੱਲ) != INTEGER_CST
		|| ਰੁੱਖ_TYPE (tok->ਮੁੱਲ) != integer_type_ਗੰਢ
		|| wi::neg_p (wi::ਮੰਜ਼ਿਲ_wide (tok->ਮੁੱਲ))
		|| wi::ਮੰਜ਼ਿਲ_widest (tok->ਮੁੱਲ) > UCHAR_MAX)
	      ਰੋਕੋ;
	    c_token *tok2 = c_parser_peek_nth_token (parser, 3);
	    ਜੇ (tok2->type != CPP_COMMA && tok2->type != CPP_CLOSE_BRACE)
	      ਰੋਕੋ;
	    buf2[i + off] = (ਅੱਖਰ) ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (tok->ਮੁੱਲ);
	    /* If orig_len is INT_MAX, this can be flexible array member and
	       in that case we need to ensure another element which
	       for CPP_EMBED is normally guaranteed after it.  Include
	       that byte in the RAW_DATA_OWNER though, so it can be optimized
	       later.  */
	    ਜੇ (orig_len == ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ
		&& (tok2->type == CPP_CLOSE_BRACE
		    || (c_parser_peek_nth_token (parser, 4)->type
			!= CPP_ਸੰਖਿਆ)))
	      {
		ਆਖਰੀ = 1;
		ਰੋਕੋ;
	      }
	    ਆਖਰੀ_loc = tok->location;
	    c_parser_consume_token (parser);
	    c_parser_consume_token (parser);
	  }
	val = make_ਗੰਢ (RAW_ਅੰਕੜੇ_CST);
	ਰੁੱਖ_TYPE (val) = integer_type_ਗੰਢ;
	RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (val) = i;
	ਰੁੱਖ owner = build_string (i + off + ਆਖਰੀ, buf2);
	XDELETEVEC (buf2);
	ਰੁੱਖ_TYPE (owner) = build_array_type_nelts (unsigned_char_type_ਗੰਢ,
						    i + off + ਆਖਰੀ);
	RAW_ਅੰਕੜੇ_OWNER (val) = owner;
	RAW_ਅੰਕੜੇ_ਸੂਚਕ (val) = ਰੁੱਖ_STRING_ਸੂਚਕ (owner) + off;
	init.ਮੁੱਲ = val;
	ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&init, loc, ਆਖਰੀ_loc);
	init.original_ਕੋਡ = RAW_ਅੰਕੜੇ_CST;
	init.original_type = integer_type_ਗੰਢ;
	init.m_decimal = 0;
	process_init_element (loc, init, ਝੂਠ, braced_init_obstack);
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

ਸਥਿਰ ਰੁੱਖ
c_parser_compound_statement (c_parser *parser, location_t *endlocp)
{
  ਰੁੱਖ stmt;
  location_t brace_loc;
  brace_loc = c_parser_peek_token (parser)->location;
  ਜੇ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Ensure a scope is entered and left anyway to avoid confusion
	 if we have just prepared to enter a function body.  */
      stmt = c_begin_compound_stmt (ਸੱਚ);
      c_ਸਿਰਾ_compound_stmt (brace_loc, stmt, ਸੱਚ);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  stmt = c_begin_compound_stmt (ਸੱਚ);
  location_t ਸਿਰਾ_loc = c_parser_compound_statement_nostart (parser);
  ਜੇ (endlocp)
    *endlocp = ਸਿਰਾ_loc;

  ਵਾਪਸ c_ਸਿਰਾ_compound_stmt (brace_loc, stmt, ਸੱਚ);
}

/* Diagnose errors related to imperfectly nested loops in an OMP
   loop construct.  This function is called when such code is seen.
   Only issue one such diagnostic no matter how much invalid
   intervening code there is in the loop.
   FIXME: maybe the location associated with the diagnostic should
   be the current parser token instead of the location of the outer loop
   nest.  */

ਸਥਿਰ ਖਾਲੀ
check_omp_intervening_ਕੋਡ (c_parser *parser)
{
  ਬਣਤਰ omp_for_parse_ਅੰਕੜੇ *omp_for_parse_state = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);

  ਜੇ (!omp_for_parse_state->ਵਿੱਚ_intervening_ਕੋਡ)
    ਵਾਪਸ;
  omp_for_parse_state->saw_intervening_ਕੋਡ = ਸੱਚ;

  /* Only diagnose errors related to perfect nesting once.  */
  ਜੇ (!omp_for_parse_state->perfect_nesting_fail)
    {

      /* OpenACC does not (yet) permit intervening code, in
	 addition to situations forbidden by the OpenMP spec.  */
      ਜੇ (omp_for_parse_state->ਕੋਡ == OACC_LOOP)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		    "%<#pragma acc loop%>");
	  omp_for_parse_state->perfect_nesting_fail = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (omp_for_parse_state->ordered)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<ordered%> clause");
	  omp_for_parse_state->perfect_nesting_fail = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (omp_for_parse_state->inscan)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested with "
		    "%<reduction%> %<inscan%> clause");
	  omp_for_parse_state->perfect_nesting_fail = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (omp_for_parse_state->ਕੋਡ == OMP_TILE)
	{
	  error_at (omp_for_parse_state->for_loc,
		    "inner loops must be perfectly nested in "
		     "%<pragma omp tile%>");
	  omp_for_parse_state->perfect_nesting_fail = ਸੱਚ;
	}
      ਜੇ (omp_for_parse_state->perfect_nesting_fail)
	omp_for_parse_state->fail = ਸੱਚ;
    }
}

/* Helper function for below:  wrap an OMP_STRUCTURED_BLOCK around SL
   and add the statement to the current list.  If SL is an empty statement
   list, do nothing.  */
ਸਥਿਰ ਖਾਲੀ
ਜੋੜੋ_structured_ਖੰਡ_stmt (ਰੁੱਖ sl)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (sl) != STATEMENT_LIST
      || !tsi_ਸਿਰਾ_p (tsi_ਸ਼ੁਰੂ (sl)))
    ਜੋੜੋ_stmt (build1 (OMP_STRUCTURED_ਖੰਡ, void_type_ਗੰਢ, sl));
}

ਬਣਤਰ c_omp_attribute_ਅੰਕੜੇ
{
  vec<c_token, va_gc> *ਟੋਕਨ;
  ਅਚਲ c_omp_directive *dir;
  c_omp_directive_ਕਿਸਮ ਕਿਸਮ;
};

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start of a statement or in attribute-declaration.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_handle_statement_omp_ਗੁਣ (c_parser *parser, ਰੁੱਖ &attrs,
					  ਤਾਰਕਿਕ *have_std_attrs)
{
  ਜੇ (!flag_openmp && !flag_openmp_simd)
    ਵਾਪਸ ਝੂਠ;

  auto_vec<c_omp_attribute_ਅੰਕੜੇ, 16> vd;
  ਪੂਰਨ cnt = 0;
  ਪੂਰਨ ਟੋਕਨ = 0;
  ਤਾਰਕਿਕ bad = ਝੂਠ;
  ਲਈ (ਰੁੱਖ *pa = &attrs; *pa; )
    ਜੇ (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	cnt++;
	ਲਈ (ਰੁੱਖ a = ਰੁੱਖ_ਮੁੱਲ (*pa); a; a = ਰੁੱਖ_CHAIN (a))
	  {
	    ਰੁੱਖ d = ਰੁੱਖ_ਮੁੱਲ (a);
	    gcc_assert (ਰੁੱਖ_ਕੋਡ (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_ਟੋਕਨ (d);
	    c_token *ਪਹਿਲਾ = toks->ਪਤਾ ();
	    c_token *ਆਖਰੀ = ਪਹਿਲਾ + toks->ਲੰਮਾਈ ();
	    ਜੇ (parser->omp_attrs_forbidden_p)
	      {
		error_at (ਪਹਿਲਾ->location,
			  "mixing OpenMP directives with attribute and pragma "
			  "syntax on the same statement");
		parser->omp_attrs_forbidden_p = ਝੂਠ;
		bad = ਸੱਚ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਜਨਤਕ (d))
	      {
		error_at (ਪਹਿਲਾ->location,
			  "OpenMP %<omp::decl%> attribute on a statement");
		bad = ਸੱਚ;
	      }
	    ਅਚਲ ਅੱਖਰ *directive[3] = {};
	    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
	      {
		ਰੁੱਖ id = NULL_ਰੁੱਖ;
		ਜੇ (ਪਹਿਲਾ + i == ਆਖਰੀ)
		  ਰੋਕੋ;
		ਜੇ (ਪਹਿਲਾ[i].type == CPP_NAME)
		  id = ਪਹਿਲਾ[i].ਮੁੱਲ;
		ਨਹੀਂਤਾਂ ਜੇ (ਪਹਿਲਾ[i].type == CPP_KEYWORD)
		  id = ridpointers[(ਪੂਰਨ) ਪਹਿਲਾ[i].keyword];
		ਨਹੀਂਤਾਂ
		  ਰੋਕੋ;
		directive[i] = IDENTIFIER_ਸੂਚਕ (id);
	      }
	    ਅਚਲ c_omp_directive *dir = ਨਿਰਾ;
	    ਜੇ (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    ਜੇ (dir == ਨਿਰਾ)
	      {
		error_at (ਪਹਿਲਾ->location,
			  "unknown OpenMP directive name in %qs attribute "
			  "argument",
			  ਰੁੱਖ_ਜਨਤਕ (d) ? "omp::decl" : "omp::directive");
		ਜਾਰੀ;
	      }
	    c_omp_directive_ਕਿਸਮ ਕਿਸਮ = dir->ਕਿਸਮ;
	    ਜੇ (dir->id == PRAGMA_OMP_ORDERED)
	      {
		/* ordered is C_OMP_DIR_CONSTRUCT only if it doesn't contain
		   depend/doacross clause.  */
		ਜੇ (directive[1]
		    && (strcmp (directive[1], "depend") == 0
			|| strcmp (directive[1], "doacross") == 0))
		  ਕਿਸਮ = C_OMP_DIR_STANDALONE;
		ਨਹੀਂਤਾਂ ਜੇ (ਪਹਿਲਾ + 2 < ਆਖਰੀ
			 && ਪਹਿਲਾ[1].type == CPP_COMMA
			 && ਪਹਿਲਾ[2].type == CPP_NAME
			 && (strcmp (IDENTIFIER_ਸੂਚਕ (ਪਹਿਲਾ[2].ਮੁੱਲ),
				     "depend") == 0
			     || strcmp (IDENTIFIER_ਸੂਚਕ (ਪਹਿਲਾ[2].ਮੁੱਲ),
					"doacross") == 0))
		  ਕਿਸਮ = C_OMP_DIR_STANDALONE;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (dir->id == PRAGMA_OMP_ERROR)
	      {
		/* error with at(execution) clause is C_OMP_DIR_STANDALONE.  */
		ਪੂਰਨ paren_ਡੂੰਘਾਈ = 0;
		ਲਈ (ਪੂਰਨ i = 1; ਪਹਿਲਾ + i < ਆਖਰੀ; i++)
		  ਜੇ (ਪਹਿਲਾ[i].type == CPP_OPEN_PAREN)
		    paren_ਡੂੰਘਾਈ++;
		  ਨਹੀਂਤਾਂ ਜੇ (ਪਹਿਲਾ[i].type == CPP_CLOSE_PAREN)
		    paren_ਡੂੰਘਾਈ--;
		  ਨਹੀਂਤਾਂ ਜੇ (paren_ਡੂੰਘਾਈ == 0
			   && ਪਹਿਲਾ + i + 2 < ਆਖਰੀ
			   && ਪਹਿਲਾ[i].type == CPP_NAME
			   && ਪਹਿਲਾ[i + 1].type == CPP_OPEN_PAREN
			   && ਪਹਿਲਾ[i + 2].type == CPP_NAME
			   && !strcmp (IDENTIFIER_ਸੂਚਕ (ਪਹਿਲਾ[i].ਮੁੱਲ),
				       "at")
			   && !strcmp (IDENTIFIER_ਸੂਚਕ (ਪਹਿਲਾ[i
								 + 2].ਮੁੱਲ),
				       "execution"))
		    {
		      ਕਿਸਮ = C_OMP_DIR_STANDALONE;
		      ਰੋਕੋ;
		    }
	      }
	    c_omp_attribute_ਅੰਕੜੇ v = { toks, dir, ਕਿਸਮ };
	    vd.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (v);
	    ਜੇ (flag_openmp || dir->simd)
	      ਟੋਕਨ += (ਆਖਰੀ - ਪਹਿਲਾ) + 1;
	  }
	c_omp_attribute_ਅੰਕੜੇ v = {};
	vd.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (v);
	*pa = ਰੁੱਖ_CHAIN (*pa);
      }
    ਨਹੀਂਤਾਂ
      pa = &ਰੁੱਖ_CHAIN (*pa);

  ਜੇ (bad)
    {
    fail:
      ਜੇ (have_std_attrs && attrs == ਨਿਰਾ)
	*have_std_attrs = ਝੂਠ;
      ਵਾਪਸ ਝੂਠ;
    }

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
  c_omp_attribute_ਅੰਕੜੇ *v;
  c_omp_attribute_ਅੰਕੜੇ *construct_ਵੇਖਿਆ = ਖਾਲੀ_ਸੂਚਕ;
  c_omp_attribute_ਅੰਕੜੇ *standalone_ਵੇਖਿਆ = ਖਾਲੀ_ਸੂਚਕ;
  c_omp_attribute_ਅੰਕੜੇ *prev_standalone_ਵੇਖਿਆ = ਖਾਲੀ_ਸੂਚਕ;
  FOR_EACH_VEC_ELT (vd, i, v)
    ਜੇ (v->ਟੋਕਨ)
      {
	ਜੇ (v->ਕਿਸਮ == C_OMP_DIR_CONSTRUCT && !construct_ਵੇਖਿਆ)
	  construct_ਵੇਖਿਆ = v;
	ਨਹੀਂਤਾਂ ਜੇ (v->ਕਿਸਮ == C_OMP_DIR_STANDALONE && !standalone_ਵੇਖਿਆ)
	  standalone_ਵੇਖਿਆ = v;
      }
    ਨਹੀਂਤਾਂ
      {
	ਜੇ (standalone_ਵੇਖਿਆ && !prev_standalone_ਵੇਖਿਆ)
	  {
	    prev_standalone_ਵੇਖਿਆ = standalone_ਵੇਖਿਆ;
	    standalone_ਵੇਖਿਆ = ਖਾਲੀ_ਸੂਚਕ;
	  }
      }

  ਜੇ (cnt > 1 && construct_ਵੇਖਿਆ)
    {
      error_at ((*construct_ਵੇਖਿਆ->ਟੋਕਨ)[0].location,
		"OpenMP construct among %<omp::directive%> attributes"
		" requires all %<omp::directive%> attributes on the"
		" same statement to be in the same %<omp::sequence%>");
      ਜਾਓ fail;
    }
  ਜੇ (cnt > 1 && standalone_ਵੇਖਿਆ && prev_standalone_ਵੇਖਿਆ)
    {
      error_at ((*standalone_ਵੇਖਿਆ->ਟੋਕਨ)[0].location,
		"multiple OpenMP standalone directives among"
		" %<omp::directive%> attributes must be all within the"
		" same %<omp::sequence%>");
      ਜਾਓ fail;
    }

  ਜੇ (prev_standalone_ਵੇਖਿਆ)
    standalone_ਵੇਖਿਆ = prev_standalone_ਵੇਖਿਆ;
  ਜੇ (standalone_ਵੇਖਿਆ
      && !c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      error_at (standalone_ਵੇਖਿਆ->ਟੋਕਨ->ਪਤਾ ()->location,
		"standalone OpenMP directives in %<omp::directive%> attribute"
		" can only appear on an empty statement");
      ਜਾਓ fail;
    }
  ਜੇ (cnt && c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA))
    {
      c_token *token = c_parser_peek_token (parser);
      ਗਿਣਤੀ pragma_ਕਿਸਮ ਕਿਸਮ = token->pragma_ਕਿਸਮ;
      ਜੇ (ਕਿਸਮ >= PRAGMA_OMP_ਸ਼ੁਰੂ && ਕਿਸਮ <= PRAGMA_OMP_ਆਖਰੀ)
	{
	  error_at (token->location,
		    "mixing OpenMP directives with attribute and pragma "
		    "syntax on the same statement");
	  ਜਾਓ fail;
	}
    }

  ਜੇ (!ਟੋਕਨ)
    ਵਾਪਸ ਝੂਠ;

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਟੋਕਨ_avail = parser->ਟੋਕਨ_avail;

  ਟੋਕਨ++;
  vec<c_token, va_gc> *toks = ਨਿਰਾ;
  vec_ਸੁਰੱਖਿਅਤ_reserve (toks, ਟੋਕਨ, ਸੱਚ);
  FOR_EACH_VEC_ELT (vd, i, v)
    {
      ਜੇ (!v->ਟੋਕਨ)
	ਜਾਰੀ;
      ਜੇ (!flag_openmp && !v->dir->simd)
	ਜਾਰੀ;
      c_token *ਪਹਿਲਾ = v->ਟੋਕਨ->ਪਤਾ ();
      c_token *ਆਖਰੀ = ਪਹਿਲਾ + v->ਟੋਕਨ->ਲੰਮਾਈ ();
      c_token tok = {};
      tok.type = CPP_PRAGMA;
      tok.keyword = RID_MAX;
      tok.pragma_ਕਿਸਮ = pragma_ਕਿਸਮ (v->dir->id);
      tok.location = ਪਹਿਲਾ->location;
      toks->ਤੇਜ਼_ਧੱਕੋ (tok);
      ਜਦੋਂ (++ਪਹਿਲਾ < ਆਖਰੀ)
	toks->ਤੇਜ਼_ਧੱਕੋ (*ਪਹਿਲਾ);
      tok = {};
      tok.type = CPP_PRAGMA_EOL;
      tok.keyword = RID_MAX;
      tok.location = ਆਖਰੀ[-1].location;
      toks->ਤੇਜ਼_ਧੱਕੋ (tok);
    }

  c_token tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = toks->ਆਖਰੀ ().location;
  toks->ਤੇਜ਼_ਧੱਕੋ (tok);

  gcc_assert (!parser->ਵਿੱਚ_omp_attribute_pragma);
  parser->ਵਿੱਚ_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->ਵਿੱਚ_omp_attribute_pragma->token_vec = toks;
  parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ = parser->ਟੋਕਨ;
  parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ_avail = ਟੋਕਨ_avail;
  parser->ਟੋਕਨ = toks->ਪਤਾ ();
  parser->ਟੋਕਨ_avail = ਟੋਕਨ;
  ਵਾਪਸ ਸੱਚ;
}

/* Handle omp::directive and omp::sequence attributes in ATTRS
   (if any) at the start or after declaration-id of a declaration.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_handle_directive_omp_ਗੁਣ (ਰੁੱਖ &attrs,
					  vec<c_token> *&pragma_clauses,
					  vec<c_token> *attr_clauses)
{
  ਜੇ (!flag_openmp && !flag_openmp_simd)
    ਵਾਪਸ;

  ਲਈ (ਰੁੱਖ *pa = &attrs; *pa; )
    ਜੇ (is_attribute_namespace_p ("omp", *pa)
	&& is_attribute_p ("directive", get_attribute_name (*pa)))
      {
	ਪੂਰਨ cnt = 0;
	ਲਈ (ਰੁੱਖ *pa2 = &ਰੁੱਖ_ਮੁੱਲ (*pa); *pa2; )
	  {
	    ਰੁੱਖ a = *pa2;
	    ਰੁੱਖ d = ਰੁੱਖ_ਮੁੱਲ (a);
	    gcc_assert (ਰੁੱਖ_ਕੋਡ (d) == C_TOKEN_VEC);
	    vec<c_token, va_gc> *toks = C_TOKEN_VEC_ਟੋਕਨ (d);
	    c_token *ਪਹਿਲਾ = toks->ਪਤਾ ();
	    c_token *ਆਖਰੀ = ਪਹਿਲਾ + toks->ਲੰਮਾਈ ();
	    ਅਚਲ ਅੱਖਰ *directive[3] = {};
	    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
	      {
		ਰੁੱਖ id = NULL_ਰੁੱਖ;
		ਜੇ (ਪਹਿਲਾ + i == ਆਖਰੀ)
		  ਰੋਕੋ;
		ਜੇ (ਪਹਿਲਾ[i].type == CPP_NAME)
		  id = ਪਹਿਲਾ[i].ਮੁੱਲ;
		ਨਹੀਂਤਾਂ ਜੇ (ਪਹਿਲਾ[i].type == CPP_KEYWORD)
		  id = ridpointers[(ਪੂਰਨ) ਪਹਿਲਾ[i].keyword];
		ਨਹੀਂਤਾਂ
		  ਰੋਕੋ;
		directive[i] = IDENTIFIER_ਸੂਚਕ (id);
	      }
	    ਅਚਲ c_omp_directive *dir = ਨਿਰਾ;
	    ਜੇ (directive[0])
	      dir = c_omp_categorize_directive (directive[0], directive[1],
						directive[2]);
	    ਜੇ (dir == ਨਿਰਾ)
	      {
		error_at (ਪਹਿਲਾ->location,
			  "unknown OpenMP directive name in "
			  "%qs attribute argument",
			  ਰੁੱਖ_ਜਨਤਕ (d) ? "omp::decl" : "omp::directive");
		*pa2 = ਰੁੱਖ_CHAIN (a);
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (dir->id == PRAGMA_OMP_DECLARE
		     && (strcmp (directive[1], "simd") == 0
			 || strcmp (directive[1], "variant") == 0))
	      {
		ਜੇ (pragma_clauses)
		  {
		    error_at (ਪਹਿਲਾ->location,
			      "mixing OpenMP directives with attribute and "
			      "pragma syntax on the same declaration");
		    ਲਈ (pa = &attrs; *pa; )
		      ਜੇ (is_attribute_namespace_p ("omp", *pa)
			  && is_attribute_p ("directive",
					     get_attribute_name (*pa)))
			*pa = ਰੁੱਖ_CHAIN (*pa);
		      ਨਹੀਂਤਾਂ
			pa = &ਰੁੱਖ_CHAIN (*pa);
		    ਵਾਪਸ;
		  }
		++cnt;
		attr_clauses->reserve (attr_clauses->ਲੰਮਾਈ ()
				       + toks->ਲੰਮਾਈ () + 2);
		ਲਈ (++ਪਹਿਲਾ; ਪਹਿਲਾ < ਆਖਰੀ; ++ਪਹਿਲਾ)
		  attr_clauses->ਤੇਜ਼_ਧੱਕੋ (*ਪਹਿਲਾ);
		c_token tok = {};
		tok.type = CPP_PRAGMA_EOL;
		tok.keyword = RID_MAX;
		tok.location = ਆਖਰੀ[-1].location;
		attr_clauses->ਤੇਜ਼_ਧੱਕੋ (tok);
		*pa2 = ਰੁੱਖ_CHAIN (a);
	      }
	    ਨਹੀਂਤਾਂ
	      pa2 = &ਰੁੱਖ_CHAIN (a);
	  }
	ਜੇ (cnt && ਰੁੱਖ_ਮੁੱਲ (*pa) == NULL_ਰੁੱਖ)
	  *pa = ਰੁੱਖ_CHAIN (*pa);
	ਨਹੀਂਤਾਂ
	  pa = &ਰੁੱਖ_CHAIN (*pa);
      }
    ਨਹੀਂਤਾਂ
      pa = &ਰੁੱਖ_CHAIN (*pa);
  ਜੇ (attr_clauses->ਲੰਮਾਈ ())
    {
      c_token tok = {};
      tok.type = CPP_EOF;
      tok.keyword = RID_MAX;
      tok.location = attr_clauses->ਆਖਰੀ ().location;
      attr_clauses->ਤੇਜ਼_ਧੱਕੋ (tok);
      attr_clauses->ਤੇਜ਼_ਧੱਕੋ (tok);
      pragma_clauses = attr_clauses;
    }
}

/* Check if STD_ATTR contains a musttail attribute and remove if it
   precedes a return.  PARSER is the parser and ATTR is the output
   attr_state.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_handle_musttail (c_parser *parser, ਰੁੱਖ std_attrs, attr_state &attr)
{
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_RETURN))
    {
      ਜੇ (ਰੁੱਖ a = lookup_attribute ("gnu", "musttail", std_attrs))
	{
	  ਲਈ (; a; a = lookup_attribute ("gnu", "musttail", ਰੁੱਖ_CHAIN (a)))
	    ਜੇ (ਰੁੱਖ_ਮੁੱਲ (a))
	      error ("%qs attribute does not take any arguments",
		     "musttail");
	  std_attrs = remove_attribute ("gnu", "musttail", std_attrs);
	  attr.musttail_p = ਸੱਚ;
	}
      ਜੇ (lookup_attribute ("clang", "musttail", std_attrs))
	{
	  std_attrs = remove_attribute ("clang", "musttail", std_attrs);
	  attr.musttail_p = ਸੱਚ;
	}
    }
  ਵਾਪਸ std_attrs;
}

/* Return a statement before optional series of LABEL_EXPR/CASE_LABEL_EXPRs.
   Instead of collecting vectors of labels before each stmt just in case
   the statement would be iteration or switch statement for named loops,
   we just remember last emitted statement and let the iteration/switch
   statement search backwards in cur_stmt_list until that stmt for loop
   names if any.  */

ਸਥਿਰ ਰੁੱਖ
get_before_labels ()
{
  ਜੇ (!building_stmt_list_p ())
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਰੁੱਖ_stmt_iterator tsi = tsi_ਆਖਰੀ (cur_stmt_list);
  ਜੇ (tsi_ਸਿਰਾ_p (tsi))
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਵਾਪਸ tsi_stmt (tsi);
}

/* Parse a compound statement except for the opening brace.  This is
   used for parsing both compound statements and statement expressions
   (which follow different paths to handling the opening).  */

ਸਥਿਰ location_t
c_parser_compound_statement_nostart (c_parser *parser)
{
  ਤਾਰਕਿਕ ਆਖਰੀ_stmt = ਝੂਠ;
  ਤਾਰਕਿਕ ਆਖਰੀ_label = ਝੂਠ;
  ਤਾਰਕਿਕ save_valid_for_pragma = valid_location_for_stdc_pragma_p ();
  location_t label_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
  ਬਣਤਰ omp_for_parse_ਅੰਕੜੇ *omp_for_parse_state
    = parser->omp_for_parse_state;
  ਤਾਰਕਿਕ ਵਿੱਚ_omp_loop_ਖੰਡ
    = omp_for_parse_state ? omp_for_parse_state->want_nested_loop : ਝੂਠ;
  ਰੁੱਖ sl = NULL_ਰੁੱਖ;
  attr_state astate = {};

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
    {
      location_t endloc = c_parser_peek_token (parser)->location;
      ਜੋੜੋ_debug_begin_stmt (endloc);
      c_parser_consume_token (parser);
      ਵਾਪਸ endloc;
    }

  /* If we're parsing a {} sequence in an OMP_FOR body, start a
     statement list for intervening code.  */
  ਜੇ (ਵਿੱਚ_omp_loop_ਖੰਡ)
    sl = ਧੱਕੋ_stmt_list ();

  mark_valid_location_for_stdc_pragma (ਸੱਚ);
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_LABEL))
    {
      /* Read zero or more forward-declarations for labels that nested
	 functions can jump to.  */
      mark_valid_location_for_stdc_pragma (ਝੂਠ);
      ਜੇ (ਵਿੱਚ_omp_loop_ਖੰਡ)
	check_omp_intervening_ਕੋਡ (parser);
      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_LABEL))
	{
	  label_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* Any identifiers, including those declared as type names,
	     are OK here.  */
	  ਜਦੋਂ (ਸੱਚ)
	    {
	      ਰੁੱਖ label;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
		{
		  c_parser_error (parser, "expected identifier");
		  ਰੋਕੋ;
		}
	      label
		= declare_label (c_parser_peek_token (parser)->ਮੁੱਲ);
	      C_DECLARED_LABEL_FLAG (label) = 1;
	      ਜੋੜੋ_stmt (build_stmt (label_loc, DECL_ਵਿਅੰਜਕ, label));
	      c_parser_consume_token (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		c_parser_consume_token (parser);
	      ਨਹੀਂਤਾਂ
		ਰੋਕੋ;
	    }
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
	}
      pedwarn (label_loc, OPT_Wpedantic, "ISO C forbids label declarations");
    }
  /* We must now have at least one statement, label or declaration.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
    {
      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
      c_parser_error (parser, "expected declaration or statement");
      location_t endloc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ਵਾਪਸ endloc;
    }
  ਰੁੱਖ before_labels = get_before_labels ();
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      loc = expansion_ਬਿੰਦੂ_location_if_ਵਿੱਚ_system_ਸਿਰਲੇਖ (loc);

      ਤਾਰਕਿਕ want_nested_loop = (omp_for_parse_state
			       ? omp_for_parse_state->want_nested_loop
			       : ਝੂਠ);

      /* First take care of special cases for OpenMP "canonical loop
	 nest form", that do not allow standard attributes, labels, or
	 __extension__ before the nested statement.  */
      ਜੇ (ਵਿੱਚ_omp_loop_ਖੰਡ && !ਆਖਰੀ_label)
	{
	  ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = omp_for_parse_state->ਕੋਡ;
	  ਜੇ (want_nested_loop
	      && c_parser_omp_ਅਗਲਾ_ਟੋਕਨ_can_be_canon_loop (parser, ਕੋਡ,
							     ਝੂਠ))
	    {
	      /* Found the next nested loop.  If there were intervening
		 code statements collected before now, wrap them in an
		 OMP_STRUCTURED_BLOCK node, and start a new structured
		 block to hold statements that may come after the FOR.  */
	      gcc_assert (sl);
	      ਜੋੜੋ_structured_ਖੰਡ_stmt (ਕੱਢੋ_stmt_list (sl));
	      omp_for_parse_state->ਡੂੰਘਾਈ++;
	      ਜੋੜੋ_stmt (c_parser_omp_loop_nest (parser, ਨਿਰਾ));
	      omp_for_parse_state->ਡੂੰਘਾਈ--;
	      sl = ਧੱਕੋ_stmt_list ();
	      parser->error = ਝੂਠ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (want_nested_loop
		   && c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
	    {
	      /* If this nested compound statement contains the nested loop,
		 we need to separate the other statements in the current
		 statement into separate blocks of intervening code.  If
		 there's no nested loop, it's all part of the same
		 chunk of intervening code.  */
	      ਰੁੱਖ pre_sl = ਕੱਢੋ_stmt_list (sl);
	      ਰੁੱਖ nested_sl = ਧੱਕੋ_stmt_list ();
	      mark_valid_location_for_stdc_pragma (ਝੂਠ);
	      c_parser_statement_after_labels (parser, ਨਿਰਾ, NULL_ਰੁੱਖ);
	      nested_sl = ਕੱਢੋ_stmt_list (nested_sl);
	      ਜੇ (omp_for_parse_state->want_nested_loop)
		{
		  /* This block didn't contain a loop-nest, so it's
		     all part of the same chunk of intervening code.  */
		  check_omp_intervening_ਕੋਡ (parser);
		  sl = ਧੱਕੋ_stmt_list ();
		  ਜੋੜੋ_stmt (pre_sl);
		  ਜੋੜੋ_stmt (nested_sl);
		}
	      ਨਹੀਂਤਾਂ
		{
		  /* It contains the nested loop.  */
		  ਜੋੜੋ_structured_ਖੰਡ_stmt (pre_sl);
		  ਜੋੜੋ_stmt (nested_sl);
		  sl = ਧੱਕੋ_stmt_list ();
		}
	      parser->error = ਝੂਠ;
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	    {
	      /* Prior to implementing the OpenMP 5.1 syntax for canonical
		 loop form, GCC used to accept an empty statements that
		 would now be flagged as intervening code.  Continue to
		 do that, as an extension.  */
	      /* FIXME:  Maybe issue a warning or something here?  */
	      c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
	      ਜਾਰੀ;
	    }
	}

      /* Standard attributes may start a label, statement or declaration.  */
      ਤਾਰਕਿਕ have_std_attrs
	= c_parser_nth_token_starts_std_ਗੁਣ (parser, 1);
      ਰੁੱਖ std_attrs = NULL_ਰੁੱਖ;
      ਜੇ (have_std_attrs)
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, astate);
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_CASE)
	  || c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_DEFAULT)
	  || (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_CASE))
	    label_loc = c_parser_peek_2nd_token (parser)->location;
	  ਨਹੀਂਤਾਂ
	    label_loc = c_parser_peek_token (parser)->location;
	  ਆਖਰੀ_label = ਸੱਚ;
	  ਆਖਰੀ_stmt = ਝੂਠ;
	  mark_valid_location_for_stdc_pragma (ਝੂਠ);
	  ਜੇ (ਵਿੱਚ_omp_loop_ਖੰਡ)
	    check_omp_intervening_ਕੋਡ (parser);
	  c_parser_label (parser, std_attrs);
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser)
	       || (have_std_attrs
		   && !c_parser_handle_statement_omp_ਗੁਣ
				(parser, std_attrs, &have_std_attrs)
		   && c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)
		   && (have_std_attrs = ਸੱਚ)))
	{
	  ਜੇ (ਆਖਰੀ_label)
	    pedwarn_c11 (c_parser_peek_token (parser)->location, OPT_Wfree_labels,
			 "a label can only be part of a statement and "
			 "a declaration is not a statement");
	  /* It's unlikely we'll see a nested loop in a declaration in
	     intervening code in an OMP loop, but disallow it anyway.  */
	  ਜੇ (ਵਿੱਚ_omp_loop_ਖੰਡ)
	    {
	      check_omp_intervening_ਕੋਡ (parser);
	      omp_for_parse_state->want_nested_loop = ਝੂਠ;
	    }
	  mark_valid_location_for_stdc_pragma (ਝੂਠ);
	  ਤਾਰਕਿਕ fallthru_attr_p = ਝੂਠ;
	  c_parser_declaration_or_fndef (parser, ਸੱਚ, !have_std_attrs,
					 ਸੱਚ, ਸੱਚ, ਸੱਚ, ਝੂਠ, ਨਿਰਾ,
					 ਨਿਰਾ, have_std_attrs, std_attrs,
					 ਨਿਰਾ, &fallthru_attr_p);

	  ਜੇ (ਵਿੱਚ_omp_loop_ਖੰਡ)
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	  ਜੇ (ਆਖਰੀ_stmt && !fallthru_attr_p)
	    pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			 "ISO C90 forbids mixed declarations and code");
	  ਆਖਰੀ_stmt = fallthru_attr_p;
	  ਆਖਰੀ_label = ਝੂਠ;
	  before_labels = get_before_labels ();
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  If standard attributes have already
	     been seen, it must start a statement, not a declaration,
	     but standard attributes starting a declaration may appear
	     after __extension__.  */
	  ਜਦੋਂ (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  ਜੇ (!have_std_attrs
	      && (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser, 2)
		  || c_parser_nth_token_starts_std_ਗੁਣ (parser, 2)))
	    {
	      ਪੂਰਨ ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      ਆਖਰੀ_label = ਝੂਠ;
	      /* It's unlikely we'll see a nested loop in a declaration in
		 intervening code in an OMP loop, but disallow it anyway.  */
	      ਜੇ (ਵਿੱਚ_omp_loop_ਖੰਡ)
		{
		  check_omp_intervening_ਕੋਡ (parser);
		  omp_for_parse_state->want_nested_loop = ਝੂਠ;
		}
	      mark_valid_location_for_stdc_pragma (ਝੂਠ);
	      c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ,
					     ਸੱਚ, ਝੂਠ);
	      ਜੇ (ਵਿੱਚ_omp_loop_ਖੰਡ)
		omp_for_parse_state->want_nested_loop = want_nested_loop;
	      /* Following the old parser, __extension__ does not
		 disable this diagnostic.  */
	      restore_extension_diagnostics (ext);
	      ਜੇ (ਆਖਰੀ_stmt)
		pedwarn_c90 (loc, OPT_Wdeclaration_after_statement,
			     "ISO C90 forbids mixed declarations and code");
	      ਆਖਰੀ_stmt = ਝੂਠ;
	      before_labels = get_before_labels ();
	    }
	  ਨਹੀਂਤਾਂ
	    ਜਾਓ statement;
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA))
	{
	  ਜੇ (have_std_attrs && !parser->ਵਿੱਚ_omp_attribute_pragma)
	    c_parser_error (parser, "expected declaration or statement");
	  ਨਹੀਂਤਾਂ ਜੇ (std_attrs)
	    c_warn_ਅਣਵਰਤਿਆ_ਗੁਣ (std_attrs);
	  /* External pragmas, and some omp pragmas, are not associated
	     with regular c code, and so are not to be considered statements
	     syntactically.  This ensures that the user doesn't put them
	     places that would turn into syntax errors if the directive
	     were ignored.  */
	  ਜੇ (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = ਝੂਠ;
	  ਜੇ (c_parser_pragma (parser,
			       ਆਖਰੀ_label ? pragma_stmt : pragma_compound,
			       ਨਿਰਾ, before_labels))
	    {
	      ਆਖਰੀ_label = ਝੂਠ;
	      ਆਖਰੀ_stmt = ਸੱਚ;
	      ਜੇ (omp_for_parse_state)
		check_omp_intervening_ਕੋਡ (parser);
	    }
	  ਜੇ (omp_for_parse_state)
	    omp_for_parse_state->want_nested_loop = want_nested_loop;
	  before_labels = get_before_labels ();
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EOF))
	{
	  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	  c_parser_error (parser, "expected declaration or statement");
	  ਵਾਪਸ c_parser_peek_token (parser)->location;
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ELSE))
        {
          ਜੇ (parser->ਵਿੱਚ_if_ਖੰਡ)
            {
	      mark_valid_location_for_stdc_pragma (save_valid_for_pragma);
	      error_at (loc, "expected %<}%> before %<else%>");
	      ਵਾਪਸ c_parser_peek_token (parser)->location;
            }
          ਨਹੀਂਤਾਂ
            {
              error_at (loc, "%<else%> without a previous %<if%>");
              c_parser_consume_token (parser);
	      before_labels = get_before_labels ();
	      astate.reset ();
              ਜਾਰੀ;
            }
        }
      ਨਹੀਂਤਾਂ
	{
	statement:
	  c_warn_ਅਣਵਰਤਿਆ_ਗੁਣ (std_attrs);
	  ਆਖਰੀ_label = ਝੂਠ;
	  ਆਖਰੀ_stmt = ਸੱਚ;
	  mark_valid_location_for_stdc_pragma (ਝੂਠ);
	  ਜੇ (!omp_for_parse_state)
	    c_parser_statement_after_labels (parser, ਨਿਰਾ, before_labels,
					     ਨਿਰਾ, astate);
	  ਨਹੀਂਤਾਂ
	    {
	      /* In canonical loop nest form, nested loops can only appear
		 directly, or in a directly nested compound statement.  We
		 already took care of those cases above, so now we have
		 something else.  This statement and everything inside
		 it must be intervening code.  */
	      omp_for_parse_state->want_nested_loop = ਝੂਠ;
	      check_omp_intervening_ਕੋਡ (parser);
	      c_parser_statement_after_labels (parser, ਨਿਰਾ, before_labels);
	      omp_for_parse_state->want_nested_loop = want_nested_loop;
	    }
	  before_labels = get_before_labels ();
	}

      parser->error = ਝੂਠ;
      astate.reset ();
    }
  ਜੇ (ਆਖਰੀ_label)
    pedwarn_c11 (label_loc, OPT_Wfree_labels,
		 "label at end of compound statement");
  location_t endloc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  /* Restore the value we started with.  */
  mark_valid_location_for_stdc_pragma (save_valid_for_pragma);

  /* Package leftover intervening code, or the whole contents of the
     compound statement if we were looking for a nested loop in an OMP_FOR
     construct and didn't find one.  */
  ਜੇ (sl)
    {
      sl = ਕੱਢੋ_stmt_list (sl);
      ਜੇ (omp_for_parse_state->want_nested_loop)
	ਜੋੜੋ_stmt (sl);
      ਨਹੀਂਤਾਂ
	ਜੋੜੋ_structured_ਖੰਡ_stmt (sl);
    }
  ਵਾਪਸ endloc;
}

/* Parse all consecutive labels, possibly preceded by standard
   attributes.  In this context, a statement is required, not a
   declaration, so attributes must be followed by a statement that is
   not just a semicolon.  Returns an attr_state.  */

ਸਥਿਰ attr_state
c_parser_all_labels (c_parser *parser)
{
  attr_state attr = {};
  ਤਾਰਕਿਕ have_std_attrs;
  ਰੁੱਖ std_attrs = ਨਿਰਾ;
  ਜੇ ((have_std_attrs = c_parser_nth_token_starts_std_ਗੁਣ (parser, 1)))
    {
      std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
    }

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_CASE)
	 || c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_DEFAULT)
	 || (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	     && c_parser_peek_2nd_token (parser)->type == CPP_COLON))
    {
      c_parser_label (parser, std_attrs);
      std_attrs = ਨਿਰਾ;
      ਜੇ ((have_std_attrs = c_parser_nth_token_starts_std_ਗੁਣ (parser,
								      1)))
	{
	  std_attrs = c_parser_std_attribute_specifier_sequence (parser);
	  std_attrs = c_parser_handle_musttail (parser, std_attrs, attr);
	}
    }
  ਜੇ (std_attrs
      && (!c_parser_handle_statement_omp_ਗੁਣ (parser, std_attrs, &have_std_attrs)
	  || std_attrs))
    {
      ਜੇ (have_std_attrs && c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	c_parser_error (parser, "expected statement");
      c_warn_ਅਣਵਰਤਿਆ_ਗੁਣ (std_attrs);
    }
  ਨਹੀਂਤਾਂ ਜੇ (have_std_attrs && c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    c_parser_error (parser, "expected statement");
  ਵਾਪਸ attr;
}


/* Information used while parsing an OpenMP metadirective.  */
ਬਣਤਰ omp_metadirective_parse_ਅੰਕੜੇ {
  /* These fields are used to unique-ify labels when reparsing the
     code in a metadirective alternative.  */
  vec<ਰੁੱਖ> * GTY((skip)) body_labels;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ region_ਅੰਕ;
};

/* Helper function for c_parser_label: mangle a metadirective region
   label NAME.  */
ਸਥਿਰ ਰੁੱਖ
mangle_metadirective_region_label (c_parser *parser, ਰੁੱਖ name)
{
  ਜੇ (parser->omp_metadirective_state->body_labels->ਸ਼ਾਮਲ_ਹੈ (name))
    {
      ਅਚਲ ਅੱਖਰ *old_name = IDENTIFIER_ਸੂਚਕ (name);
      ਅੱਖਰ *new_name = (ਅੱਖਰ *) XALLOCAVEC (ਅੱਖਰ, ਲੜੀ_ਲੰਬਾਈ (old_name) + 32);
      sprintf (new_name, "%s_MDR%u", old_name,
	       parser->omp_metadirective_state->region_ਅੰਕ);
      ਵਾਪਸ get_identifier (new_name);
    }
  ਵਾਪਸ name;
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
ਸਥਿਰ ਖਾਲੀ
c_parser_label (c_parser *parser, ਰੁੱਖ std_attrs)
{
  location_t loc1 = c_parser_peek_token (parser)->location;
  ਰੁੱਖ label = NULL_ਰੁੱਖ;

  /* Remember whether this case or a user-defined label is allowed to fall
     through to.  */
  ਤਾਰਕਿਕ fallthrough_p = c_parser_peek_token (parser)->flags & PREV_FALLTHROUGH;

  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_CASE))
    {
      ਰੁੱਖ exp1, exp2;
      c_parser_consume_token (parser);
      exp1 = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc1,
				       c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ),
				       ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  label = do_case (loc1, exp1, NULL_ਰੁੱਖ, std_attrs);
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_ELLIPSIS))
	{
	  c_parser_consume_token (parser);
	  exp2 = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc1,
					   c_parser_ਵਿਅੰਜਕ_no_commas (parser,
								    ਨਿਰਾ),
					   ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
	  ਜੇ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    label = do_case (loc1, exp1, exp2, std_attrs);
	}
      ਨਹੀਂਤਾਂ
	c_parser_error (parser, "expected %<:%> or %<...%>");
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_DEFAULT))
    {
      c_parser_consume_token (parser);
      ਜੇ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	label = do_case (loc1, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, std_attrs);
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ name = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਰੁੱਖ tlab;
      ਰੁੱਖ attrs;
      location_t loc2 = c_parser_peek_token (parser)->location;
      gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME));
      c_parser_consume_token (parser);
      gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON));
      c_parser_consume_token (parser);
      attrs = c_parser_gnu_ਗੁਣ (parser);
      ਜੇ (parser->omp_metadirective_state)
	name = mangle_metadirective_region_label (parser, name);
      tlab = define_label (loc2, name);
      ਜੇ (tlab)
	{
	  decl_ਗੁਣ (&tlab, attrs, 0);
	  decl_ਗੁਣ (&tlab, std_attrs, 0);
	  label = ਜੋੜੋ_stmt (build_stmt (loc1, LABEL_ਵਿਅੰਜਕ, tlab));
	}
      ਜੇ (attrs
	  && c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser))
	  warning_at (loc2, OPT_Wattributes, "GNU-style attribute between"
		      " label and declaration appertains to the label");
    }
  ਜੇ (label)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (label) == LABEL_ਵਿਅੰਜਕ)
	FALLTHROUGH_LABEL_P (LABEL_ਵਿਅੰਜਕ_LABEL (label)) = fallthrough_p;
      ਨਹੀਂਤਾਂ
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

ਸਥਿਰ ਖਾਲੀ
c_parser_statement (c_parser *parser, ਤਾਰਕਿਕ *if_p, location_t *loc_after_labels)
{
  ਰੁੱਖ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);
  ਜੇ (loc_after_labels)
    *loc_after_labels = c_parser_peek_token (parser)->location;
  parser->omp_attrs_forbidden_p = ਝੂਠ;
  c_parser_statement_after_labels (parser, if_p, before_labels, ਨਿਰਾ, a);
}

/* Parse and handle optional identifier after break or continue keywords.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_bc_name (c_parser *parser, ਤਾਰਕਿਕ is_break)
{
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    ਵਾਪਸ NULL_ਰੁੱਖ;

  c_token *tok = c_parser_peek_token (parser);
  ਰੁੱਖ label = c_ਅੰਤ_bc_name (tok->location, tok->ਮੁੱਲ, is_break);
  c_parser_consume_token (parser);
  ਵਾਪਸ label;
}

/* Parse a statement, other than a labeled statement.  CHAIN is a vector
   of if-else-if conditions.  All labels and standard attributes have
   been parsed in the caller.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  ASTATE is an earlier parsed attribute state.

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_statement_after_labels (c_parser *parser, ਤਾਰਕਿਕ *if_p,
				 ਰੁੱਖ before_labels,
				 vec<ਰੁੱਖ> *chain, attr_state astate)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ stmt = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ ਵਿੱਚ_if_ਖੰਡ = parser->ਵਿੱਚ_if_ਖੰਡ;
  parser->ਵਿੱਚ_if_ਖੰਡ = ਝੂਠ;
  ਜੇ (if_p != ਨਿਰਾ)
    *if_p = ਝੂਠ;

  ਜੇ (c_parser_peek_token (parser)->type != CPP_OPEN_BRACE)
    ਜੋੜੋ_debug_begin_stmt (loc);

 restart:
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_OPEN_BRACE:
      ਜੋੜੋ_stmt (c_parser_compound_statement (parser));
      ਰੋਕੋ;
    ਹਾਲਤ CPP_KEYWORD:
      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_IF:
	  c_parser_if_statement (parser, if_p, chain);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_SWITCH:
	  c_parser_switch_statement (parser, if_p, before_labels);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_WHILE:
	  c_parser_while_statement (parser, ਝੂਠ, 0, ਝੂਠ, if_p, before_labels);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_DO:
	  c_parser_do_statement (parser, ਝੂਠ, 0, ਝੂਠ, before_labels);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_FOR:
	  c_parser_for_statement (parser, ਝੂਠ, 0, ਝੂਠ, if_p, before_labels);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_GOTO:
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	    {
	      ਰੁੱਖ name = c_parser_peek_token (parser)->ਮੁੱਲ;
	      ਜੇ (parser->omp_metadirective_state)
		name = mangle_metadirective_region_label (parser, name);
	      stmt = c_ਅੰਤ_goto_label (loc, name);
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_MULT))
	    {
	      ਬਣਤਰ c_ਵਿਅੰਜਕ val;

	      c_parser_consume_token (parser);
	      val = c_parser_ਵਿਅੰਜਕ (parser);
	      val = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, val, ਝੂਠ, ਸੱਚ);
	      stmt = c_ਅੰਤ_goto_ptr (loc, val);
	    }
	  ਨਹੀਂਤਾਂ
	    c_parser_error (parser, "expected identifier or %<*%>");
	  ਜਾਓ expect_semicolon;
	ਹਾਲਤ RID_CONTINUE:
	  c_parser_consume_token (parser);
	  stmt = c_ਅੰਤ_bc_stmt (loc, objc_foreach_continue_label, ਝੂਠ,
				   c_parser_bc_name (parser, ਝੂਠ));
	  ਜਾਓ expect_semicolon;
	ਹਾਲਤ RID_BREAK:
	  c_parser_consume_token (parser);
	  stmt = c_ਅੰਤ_bc_stmt (loc, objc_foreach_break_label, ਸੱਚ,
				   c_parser_bc_name (parser, ਸੱਚ));
	  ਜਾਓ expect_semicolon;
	ਹਾਲਤ RID_RETURN:
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = c_ਅੰਤ_return (loc, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ,
				      astate.musttail_p);
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      location_t xloc = c_parser_peek_token (parser)->location;
	      ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_conv (parser);
	      mark_exp_read (ਵਿਅੰਜਕ.ਮੁੱਲ);
	      stmt = c_ਅੰਤ_return (ਵਿਅੰਜਕ_LOC_OR_LOC (ਵਿਅੰਜਕ.ਮੁੱਲ, xloc),
				      ਵਿਅੰਜਕ.ਮੁੱਲ, ਵਿਅੰਜਕ.original_type,
				      astate.musttail_p);
	      ਜਾਓ expect_semicolon;
	    }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_ASM:
	  stmt = c_parser_asm_statement (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_TRANSACTION_ATOMIC:
	ਹਾਲਤ RID_TRANSACTION_RELAXED:
	  stmt = c_parser_transaction (parser,
	      c_parser_peek_token (parser)->keyword);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_TRANSACTION_CANCEL:
	  stmt = c_parser_transaction_cancel (parser);
	  ਜਾਓ expect_semicolon;
	ਹਾਲਤ RID_AT_THROW:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	    {
	      stmt = objc_build_throw_stmt (loc, NULL_ਰੁੱਖ);
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
	      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਝੂਠ, ਝੂਠ);
	      ਵਿਅੰਜਕ.ਮੁੱਲ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	      stmt = objc_build_throw_stmt (loc, ਵਿਅੰਜਕ.ਮੁੱਲ);
	      ਜਾਓ expect_semicolon;
	    }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_TRY:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_try_catch_finally_statement (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_SYNCHRONIZED:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_synchronized_statement (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_ATTRIBUTE:
	  {
	    /* Allow '__attribute__((fallthrough));' or
	       '__attribute__((assume(cond)));' or
	       '__attribute__((musttail))) return'.  */
	    ਰੁੱਖ attrs = c_parser_gnu_ਗੁਣ (parser);
	    ਤਾਰਕਿਕ has_assume = lookup_attribute ("assume", attrs);
	    ਜੇ (has_assume)
	      {
		ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
		  attrs = handle_assume_attribute (loc, attrs, ਸੱਚ);
		ਨਹੀਂਤਾਂ
		  {
		    auto_urlify_ਗੁਣ sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<assume%> attribute not followed by %<;%>");
		    has_assume = ਝੂਠ;
		  }
	      }
	    gcc_assert (!astate.musttail_p);
	    attrs = c_parser_handle_musttail (parser, attrs, astate);
	    ਜੇ (astate.musttail_p)
	      {
		ਜੇ (attrs)
		  {
		    auto_urlify_ਗੁਣ sentinel;
		    warning_at (c_parser_peek_token (parser)->location,
				OPT_Wattributes,
				"attribute %<musttail%> mixed with other "
				"attributes on %<return%> statement");
		  }
		ਜਾਓ restart;
	      }
	    ਜੇ (attribute_fallthrough_p (attrs))
	      {
		ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
		  {
		    ਰੁੱਖ fn = build_call_ਵਿਅੰਜਕ_ਅੰਦਰੂਨੀ_loc (loc,
							    IFN_FALLTHROUGH,
							    void_type_ਗੰਢ, 0);
		    ਜੋੜੋ_stmt (fn);
		    /* Eat the ';'.  */
		    c_parser_consume_token (parser);
		  }
		ਨਹੀਂਤਾਂ
		  {
		    auto_urlify_ਗੁਣ sentinel;
		    warning_at (loc, OPT_Wattributes,
				"%<fallthrough%> attribute not followed "
				"by %<;%>");
		  }
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (has_assume)
	      /* Eat the ';'.  */
	      c_parser_consume_token (parser);
	    ਨਹੀਂਤਾਂ ਜੇ (attrs != NULL_ਰੁੱਖ)
	      {
		auto_urlify_ਗੁਣ sentinel;
		warning_at (loc, OPT_Wattributes,
			    "only attribute %<fallthrough%> or %<assume%> can "
			    "be applied to a null statement");
	      }
	    ਰੋਕੋ;
	  }
	ਮੂਲ:
	  ਜਾਓ ਵਿਅੰਜਕ_stmt;
	}
      ਰੋਕੋ;
    ਹਾਲਤ CPP_SEMICOLON:
      c_parser_consume_token (parser);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_CLOSE_PAREN:
    ਹਾਲਤ CPP_CLOSE_ਵਰਗਫਲ:
      /* Avoid infinite loop in error recovery:
	 c_parser_skip_until_found stops at a closing nesting
	 delimiter without consuming it, but here we need to consume
	 it to proceed further.  */
      c_parser_error (parser, "expected statement");
      c_parser_consume_token (parser);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_PRAGMA:
      ਜੇ (!c_parser_pragma (parser, pragma_stmt, if_p, before_labels))
        ਜਾਓ restart;
      ਰੋਕੋ;
    ਮੂਲ:
    ਵਿਅੰਜਕ_stmt:
      stmt = c_ਅੰਤ_ਵਿਅੰਜਕ_stmt (loc, c_parser_ਵਿਅੰਜਕ_conv (parser).ਮੁੱਲ);
    expect_semicolon:
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
      ਰੋਕੋ;
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
  ਜੇ (ਵਿਅੰਜਕ_LOCATION (stmt) == UNKNOWN_LOCATION)
    protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (stmt, loc);

  parser->ਵਿੱਚ_if_ਖੰਡ = ਵਿੱਚ_if_ਖੰਡ;
}

/* Parse the condition from an if, do, while or for statements.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_condition (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ cond;
  cond = c_parser_ਵਿਅੰਜਕ_conv (parser).ਮੁੱਲ;
  cond = c_objc_common_truthvalue_conversion (loc, cond);
  cond = c_fully_fold (cond, ਝੂਠ, ਨਿਰਾ);
  ਜੇ (warn_sequence_ਬਿੰਦੂ)
    verify_sequence_points (cond);
  ਵਾਪਸ cond;
}

/* Parse a parenthesized condition from a do or while statement.

   condition:
     ( expression )
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_paren_condition (c_parser *parser)
{
  ਰੁੱਖ cond;
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ error_mark_ਗੰਢ;
  cond = c_parser_condition (parser);
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ cond;
}

/* Parse a selection-header:

   selection-header:
ਵਿਅੰਜਕ
     declaration expression
     simple-declaration

   simple-declaration:
     attribute-specifier-sequence[opt] declaration-specifiers declarator
       = initializer

  SWITCH_P is true if we are called from c_parser_switch_statement; in
  that case, don't perform the truthvalue conversion.  */

ਸਥਿਰ c_ਵਿਅੰਜਕ
c_parser_selection_ਸਿਰਲੇਖ (c_parser *parser, ਤਾਰਕਿਕ switch_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  ਤਾਰਕਿਕ parse_ਵਿਅੰਜਕ = ਸੱਚ;
  ਰੁੱਖ std_attrs;
  ਤਾਰਕਿਕ have_std_attrs = c_parser_nth_token_starts_std_ਗੁਣ (parser, 1);
  ਜੇ (have_std_attrs)
    std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  ਨਹੀਂਤਾਂ
    std_attrs = NULL_ਰੁੱਖ;
  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser))
    {
      pedwarn_c23 (loc, OPT_Wpedantic,
		   "ISO C does not support if declarations before C2Y");
      ਵਿਅੰਜਕ.ਮੁੱਲ
	= c_parser_declaration_or_fndef (parser,
					 /*fndef_ok=*/ਝੂਠ,
					 /*static_assert_ok=*/ਝੂਠ,
					 /*empty_ok=*/ਝੂਠ,
					 /*nested=*/ਸੱਚ,
					 /*start_attr_ok=*/ਸੱਚ,
					 /*simple_ok=*/ਸੱਚ,
					 /*objc_foreach_object_decl=*/ਖਾਲੀ_ਸੂਚਕ,
					 /*omp_declare_simd_clauses=*/ਖਾਲੀ_ਸੂਚਕ,
					 have_std_attrs,
					 std_attrs);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	{
	  /* A simple-declaration is a declaration that can appear in
	     place of the controlling expression of a selection statement.
	     In that case, there shall be an initializer.  */
	  ਜੇ (!ਵਿਅੰਜਕ.ਮੁੱਲ)
	    {
	      error_at (loc, "declaration in the controlling expression must "
			"have an initializer");
	      ਵਿਅੰਜਕ.original_type = error_mark_ਗੰਢ;
	      ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	      ਵਾਪਸ ਵਿਅੰਜਕ;
	    }
	  parse_ਵਿਅੰਜਕ = ਝੂਠ;
	}
      ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ)
	{
	  ਵਿਅੰਜਕ.original_type = ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ.ਮੁੱਲ);
	  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, /*convert_p=*/ਸੱਚ,
					   /*read_p=*/ਸੱਚ);
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (have_std_attrs)
    {
      c_parser_error (parser, "expected declaration");
      ਵਿਅੰਜਕ.original_type = error_mark_ਗੰਢ;
      ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
      ਵਾਪਸ ਵਿਅੰਜਕ;
    }

  ਜੇ (parse_ਵਿਅੰਜਕ)
    ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_conv (parser);
  ਜੇ (!switch_p)
    {
      ਵਿਅੰਜਕ.ਮੁੱਲ = c_objc_common_truthvalue_conversion (loc, ਵਿਅੰਜਕ.ਮੁੱਲ);
      ਵਿਅੰਜਕ.ਮੁੱਲ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (warn_sequence_ਬਿੰਦੂ)
	verify_sequence_points (ਵਿਅੰਜਕ.ਮੁੱਲ);
    }
  ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* Parse a selection-header enclosed in parentheses:

   ( selection-header )
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_paren_selection_ਸਿਰਲੇਖ (c_parser *parser)
{
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ error_mark_ਗੰਢ;
  ਰੁੱਖ cond = c_parser_selection_ਸਿਰਲੇਖ (parser, /*switch_p=*/ਝੂਠ).ਮੁੱਲ;
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ cond;
}

/* Parse a statement which is a block in C99.

   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_c99_ਖੰਡ_statement (c_parser *parser, ਤਾਰਕਿਕ *if_p,
			      location_t *loc_after_labels)
{
  ਰੁੱਖ ਖੰਡ = c_begin_compound_stmt (flag_isoc99);
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_statement (parser, if_p, loc_after_labels);
  ਵਾਪਸ c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, flag_isoc99);
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

ਸਥਿਰ ਰੁੱਖ
c_parser_if_body (c_parser *parser, ਤਾਰਕਿਕ *if_p,
		  ਅਚਲ token_indent_info &if_tinfo)
{
  ਰੁੱਖ ਖੰਡ = c_begin_compound_stmt (flag_isoc99);
  location_t body_loc = c_parser_peek_token (parser)->location;
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ਰੁੱਖ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      ਜੋੜੋ_stmt (build_ਖਾਲੀ_ਥਾਵਾਂ_stmt (loc));
      c_parser_consume_token (parser);
      ਜੇ (!c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ELSE))
	warning_at (loc, OPT_Wempty_body,
		    "suggest braces around empty body in an %<if%> statement");
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    ਜੋੜੋ_stmt (c_parser_compound_statement (parser));
  ਨਹੀਂਤਾਂ
    {
      body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, if_p, before_labels, ਨਿਰਾ, a);
    }

  token_indent_info ਅਗਲਾ_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (if_tinfo, body_tinfo, ਅਗਲਾ_tinfo);
  ਜੇ (body_loc_after_labels != UNKNOWN_LOCATION
      && ਅਗਲਾ_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, ਅਗਲਾ_tinfo.location,
				    if_tinfo.location, RID_IF);

  ਵਾਪਸ c_ਸਿਰਾ_compound_stmt (body_loc, ਖੰਡ, flag_isoc99);
}

/* Parse the else body of an if statement.  This is just parsing a
   statement but (a) it is a block in C99, (b) we handle an empty body
   specially for the sake of -Wempty-body warnings.  CHAIN is a vector
   of if-else-if conditions.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_else_body (c_parser *parser, ਅਚਲ token_indent_info &else_tinfo,
		    vec<ਰੁੱਖ> *chain)
{
  location_t body_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ ਖੰਡ = c_begin_compound_stmt (flag_isoc99);
  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  location_t body_loc_after_labels = UNKNOWN_LOCATION;
  ਰੁੱਖ before_labels = get_before_labels ();
  attr_state a = c_parser_all_labels (parser);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      location_t loc = c_parser_peek_token (parser)->location;
      warning_at (loc,
		  OPT_Wempty_body,
	         "suggest braces around empty body in an %<else%> statement");
      ਜੋੜੋ_stmt (build_ਖਾਲੀ_ਥਾਵਾਂ_stmt (loc));
      c_parser_consume_token (parser);
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
	body_loc_after_labels = c_parser_peek_token (parser)->location;
      c_parser_statement_after_labels (parser, ਨਿਰਾ, before_labels, chain, a);
    }

  token_indent_info ਅਗਲਾ_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (else_tinfo, body_tinfo, ਅਗਲਾ_tinfo);
  ਜੇ (body_loc_after_labels != UNKNOWN_LOCATION
      && ਅਗਲਾ_tinfo.type != CPP_SEMICOLON)
    warn_for_multistatement_macros (body_loc_after_labels, ਅਗਲਾ_tinfo.location,
				    else_tinfo.location, RID_ELSE);

  ਵਾਪਸ c_ਸਿਰਾ_compound_stmt (body_loc, ਖੰਡ, flag_isoc99);
}

/* Parse an if statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   if-statement:
     if ( selection-header ) statement
     if ( selection-header ) statement else statement

   CHAIN is a vector of if-else-if conditions.
   IF_P is used to track whether there's a (possibly labeled) if statement
   which is not enclosed in braces and has an else clause.  This is used to
   implement -Wparentheses.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_if_statement (c_parser *parser, ਤਾਰਕਿਕ *if_p, vec<ਰੁੱਖ> *chain)
{
  ਰੁੱਖ ਖੰਡ;
  location_t loc;
  ਰੁੱਖ cond;
  ਤਾਰਕਿਕ nested_if = ਝੂਠ;
  ਰੁੱਖ ਪਹਿਲਾ_body, ਦੂਜਾ_body;
  ਤਾਰਕਿਕ ਵਿੱਚ_if_ਖੰਡ;

  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_IF));
  token_indent_info if_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  c_parser_consume_token (parser);
  ਖੰਡ = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_selection_ਸਿਰਲੇਖ (parser);
  ਵਿੱਚ_if_ਖੰਡ = parser->ਵਿੱਚ_if_ਖੰਡ;
  parser->ਵਿੱਚ_if_ਖੰਡ = ਸੱਚ;
  ਪਹਿਲਾ_body = c_parser_if_body (parser, &nested_if, if_tinfo);
  parser->ਵਿੱਚ_if_ਖੰਡ = ਵਿੱਚ_if_ਖੰਡ;

  ਜੇ (warn_duplicated_cond)
    warn_duplicated_cond_ਜੋੜੋ_or_warn (ਵਿਅੰਜਕ_LOCATION (cond), cond, &chain);

  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ELSE))
    {
      token_indent_info else_tinfo
	= get_token_indent_info (c_parser_peek_token (parser));
      c_parser_consume_token (parser);
      ਜੇ (warn_duplicated_cond)
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_IF)
	      && chain == ਨਿਰਾ)
	    {
	      /* We've got "if (COND) else if (COND2)".  Start the
		 condition chain and add COND as the first element.  */
	      chain = ਨਵਾਂ vec<ਰੁੱਖ> ();
	      ਜੇ (!CONSTANT_CLASS_P (cond) && !ਰੁੱਖ_SIDE_EFFECTS (cond))
		chain->ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (cond);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_IF))
	    /* This is if-else without subsequent if.  Zap the condition
	       chain; we would have already warned at this point.  */
	    vec_free (chain);
	}
      ਦੂਜਾ_body = c_parser_else_body (parser, else_tinfo, chain);
      /* Set IF_P to true to indicate that this if statement has an
	 else clause.  This may trigger the Wparentheses warning
	 below when we get back up to the parent if statement.  */
      ਜੇ (if_p != ਨਿਰਾ)
	*if_p = ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਦੂਜਾ_body = NULL_ਰੁੱਖ;

      /* Diagnose an ambiguous else if if-then-else is nested inside
	 if-then.  */
      ਜੇ (nested_if)
	warning_at (loc, OPT_Wdangling_else,
		    "suggest explicit braces to avoid ambiguous %<else%>");

      ਜੇ (warn_duplicated_cond)
	/* This if statement does not have an else clause.  We don't
	   need the condition chain anymore.  */
	vec_free (chain);
    }
  c_ਅੰਤ_if_stmt (loc, cond, ਪਹਿਲਾ_body, ਦੂਜਾ_body);
  ਜੋੜੋ_stmt (c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, flag_isoc99));

  c_parser_maybe_reclassify_token (parser);
}

/* Parse a switch statement (C90 6.6.4, C99 6.8.4, C11 6.8.4).

   switch-statement:
     switch (expression) statement

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_switch_statement (c_parser *parser, ਤਾਰਕਿਕ *if_p, ਰੁੱਖ before_labels)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ce;
  ਰੁੱਖ ਖੰਡ, ਵਿਅੰਜਕ, body;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ save_ਵਿੱਚ_statement;
  location_t switch_loc = c_parser_peek_token (parser)->location;
  location_t switch_cond_loc;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_SWITCH));
  c_parser_consume_token (parser);
  ਰੁੱਖ switch_name;
  ਪੂਰਨ ਅੰਕ_ਨਾਂ = c_get_loop_ਨਾਂ (before_labels, ਸੱਚ, &switch_name);
  ਖੰਡ = c_begin_compound_stmt (flag_isoc99);
  ਤਾਰਕਿਕ explicit_cast_p = ਝੂਠ;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      switch_cond_loc = c_parser_peek_token (parser)->location;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN)
	  && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
	explicit_cast_p = ਸੱਚ;
      ce = c_parser_selection_ਸਿਰਲੇਖ (parser, /*switch_p=*/ਸੱਚ);
      /* The call above already performed convert_lvalue_to_rvalue, but
	 if it parsed an expression, read_p was false.  Make sure we mark
	 the expression as read.  */
      ce = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (switch_cond_loc, ce, ਸੱਚ, ਸੱਚ);
      ਵਿਅੰਜਕ = ce.ਮੁੱਲ;
      /* ??? expr has no valid location?  */
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਨਹੀਂਤਾਂ
    {
      switch_cond_loc = UNKNOWN_LOCATION;
      ਵਿਅੰਜਕ = error_mark_ਗੰਢ;
      ce.original_type = error_mark_ਗੰਢ;
    }
  ਰੁੱਖ stmt
    = c_ਸ਼ੁਰੂ_switch (switch_loc, switch_cond_loc, ਵਿਅੰਜਕ, explicit_cast_p,
		      switch_name);
  save_ਵਿੱਚ_statement = ਵਿੱਚ_statement;
  ਵਿੱਚ_statement |= ਵਿੱਚ_SWITCH_STMT;
  ਜੇ (switch_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (switch_name) = 1;
      ਵਿੱਚ_statement |= ਵਿੱਚ_NAMED_STMT;
    }
  ਨਹੀਂਤਾਂ
    ਵਿੱਚ_statement &= ~ਵਿੱਚ_NAMED_STMT;
  location_t loc_after_labels;
  ਤਾਰਕਿਕ open_brace_p = c_parser_peek_token (parser)->type == CPP_OPEN_BRACE;
  body = c_parser_c99_ਖੰਡ_statement (parser, if_p, &loc_after_labels);
  location_t ਅਗਲਾ_loc = c_parser_peek_token (parser)->location;
  ਜੇ (!open_brace_p && c_parser_peek_token (parser)->type != CPP_SEMICOLON)
    warn_for_multistatement_macros (loc_after_labels, ਅਗਲਾ_loc, switch_loc,
				    RID_SWITCH);
  c_ਅੰਤ_switch (body, ce.original_type);
  ਵਿੱਚ_statement = save_ਵਿੱਚ_statement;
  ਜੇ (ਅੰਕ_ਨਾਂ)
    {
      ਜੇ (!C_DECL_LOOP_SWITCH_NAME_ਵਰਤਿਆ (switch_name))
	SWITCH_STMT_NAME (stmt) = NULL_ਰੁੱਖ;
      ਨਹੀਂਤਾਂ
	SWITCH_STMT_NO_BREAK_P (stmt) = 0;
      c_release_loop_ਨਾਂ (ਅੰਕ_ਨਾਂ);
    }
  ਜੋੜੋ_stmt (c_ਸਿਰਾ_compound_stmt (switch_loc, ਖੰਡ, flag_isoc99));
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

ਸਥਿਰ ਖਾਲੀ
c_parser_while_statement (c_parser *parser, ਤਾਰਕਿਕ ivdep, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ unroll,
			  ਤਾਰਕਿਕ novector, ਤਾਰਕਿਕ *if_p, ਰੁੱਖ before_labels)
{
  ਰੁੱਖ ਖੰਡ, cond, body;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ save_ਵਿੱਚ_statement;
  location_t loc;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_WHILE));
  token_indent_info while_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ਰੁੱਖ loop_name;
  ਪੂਰਨ ਅੰਕ_ਨਾਂ = c_get_loop_ਨਾਂ (before_labels, ਝੂਠ, &loop_name);

  ਜੇ (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ਸੱਚ;
    }

  c_parser_consume_token (parser);
  ਖੰਡ = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  cond = c_parser_paren_condition (parser);
  ਜੇ (ivdep && cond != error_mark_ਗੰਢ)
    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
		   build_int_cst (integer_type_ਗੰਢ,
				  annot_ਵਿਅੰਜਕ_ivdep_ਕਿਸਮ),
		   integer_zero_ਗੰਢ);
  ਜੇ (unroll && cond != error_mark_ਗੰਢ)
    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
		   build_int_cst (integer_type_ਗੰਢ,
				  annot_ਵਿਅੰਜਕ_unroll_ਕਿਸਮ),
		   build_int_cst (integer_type_ਗੰਢ, unroll));
  ਜੇ (novector && cond != error_mark_ਗੰਢ)
    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
		   build_int_cst (integer_type_ਗੰਢ,
				  annot_ਵਿਅੰਜਕ_no_ਸਦਿਸ਼_ਕਿਸਮ),
		   integer_zero_ਗੰਢ);
  save_ਵਿੱਚ_statement = ਵਿੱਚ_statement;
  ਵਿੱਚ_statement = ਵਿੱਚ_ITERATION_STMT;
  ਜੇ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      ਵਿੱਚ_statement |= ਵਿੱਚ_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  ਤਾਰਕਿਕ open_brace = c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_ਖੰਡ_statement (parser, if_p, &loc_after_labels);
  ਜੇ (loop_name && !C_DECL_LOOP_SWITCH_NAME_ਵਰਤਿਆ (loop_name))
    loop_name = NULL_ਰੁੱਖ;
  ਜੋੜੋ_stmt (build_stmt (loc, WHILE_STMT, cond, body, loop_name, NULL_ਰੁੱਖ,
			NULL_ਰੁੱਖ));
  ਜੋੜੋ_stmt (c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, flag_isoc99));
  c_parser_maybe_reclassify_token (parser);
  ਜੇ (ਅੰਕ_ਨਾਂ)
    c_release_loop_ਨਾਂ (ਅੰਕ_ਨਾਂ);

  token_indent_info ਅਗਲਾ_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (while_tinfo, body_tinfo, ਅਗਲਾ_tinfo);

  ਜੇ (ਅਗਲਾ_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, ਅਗਲਾ_tinfo.location,
				    while_tinfo.location, RID_WHILE);

  ਵਿੱਚ_statement = save_ਵਿੱਚ_statement;
}

/* Parse a do statement (C90 6.6.5, C99 6.8.5, C11 6.8.5).

   do-statement:
     do statement while ( expression ) ;

   BEFORE_LABELS is last statement before possible labels, see
   get_before_labels description for details.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_do_statement (c_parser *parser, ਤਾਰਕਿਕ ivdep, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ unroll,
		       ਤਾਰਕਿਕ novector, ਰੁੱਖ before_labels)
{
  ਰੁੱਖ ਖੰਡ, cond, body;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ save_ਵਿੱਚ_statement;
  location_t loc;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_DO));
  ਰੁੱਖ loop_name;
  ਪੂਰਨ ਅੰਕ_ਨਾਂ = c_get_loop_ਨਾਂ (before_labels, ਝੂਠ, &loop_name);

  ਜੇ (parser->omp_for_parse_state)
    {
      error_at (c_parser_peek_token (parser)->location,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ਸੱਚ;
    }

  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    warning_at (c_parser_peek_token (parser)->location,
		OPT_Wempty_body,
		"suggest braces around empty body in %<do%> statement");
  ਖੰਡ = c_begin_compound_stmt (flag_isoc99);
  loc = c_parser_peek_token (parser)->location;
  save_ਵਿੱਚ_statement = ਵਿੱਚ_statement;
  ਵਿੱਚ_statement = ਵਿੱਚ_ITERATION_STMT;
  ਜੇ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      ਵਿੱਚ_statement |= ਵਿੱਚ_NAMED_STMT;
    }
  body = c_parser_c99_ਖੰਡ_statement (parser, ਨਿਰਾ);
  c_parser_require_keyword (parser, RID_WHILE, "expected %<while%>");
  ਵਿੱਚ_statement = save_ਵਿੱਚ_statement;
  ਜੇ (ਅੰਕ_ਨਾਂ)
    {
      ਜੇ (!C_DECL_LOOP_SWITCH_NAME_ਵਰਤਿਆ (loop_name))
	loop_name = NULL_ਰੁੱਖ;
      c_release_loop_ਨਾਂ (ਅੰਕ_ਨਾਂ);
    }
  cond = c_parser_paren_condition (parser);
  ਜੇ (ivdep && cond != error_mark_ਗੰਢ)
    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
		   build_int_cst (integer_type_ਗੰਢ,
				  annot_ਵਿਅੰਜਕ_ivdep_ਕਿਸਮ),
		   integer_zero_ਗੰਢ);
  ਜੇ (unroll && cond != error_mark_ਗੰਢ)
    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
		   build_int_cst (integer_type_ਗੰਢ,
				  annot_ਵਿਅੰਜਕ_unroll_ਕਿਸਮ),
 		   build_int_cst (integer_type_ਗੰਢ, unroll));
  ਜੇ (novector && cond != error_mark_ਗੰਢ)
    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
		   build_int_cst (integer_type_ਗੰਢ,
				  annot_ਵਿਅੰਜਕ_no_ਸਦਿਸ਼_ਕਿਸਮ),
		   integer_zero_ਗੰਢ);
  ਜੇ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);

  ਜੋੜੋ_stmt (build_stmt (loc, DO_STMT, cond, body, loop_name));
  ਜੋੜੋ_stmt (c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, flag_isoc99));
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

ਸਥਿਰ ਖਾਲੀ
c_parser_for_statement (c_parser *parser, ਤਾਰਕਿਕ ivdep, ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ unroll,
			ਤਾਰਕਿਕ novector, ਤਾਰਕਿਕ *if_p, ਰੁੱਖ before_labels)
{
  ਰੁੱਖ ਖੰਡ, cond, incr, body;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ save_ਵਿੱਚ_statement;
  ਰੁੱਖ save_objc_foreach_break_label, save_objc_foreach_continue_label;
  /* The following are only used when parsing an ObjC foreach statement.  */
  ਰੁੱਖ object_ਵਿਅੰਜਕ;
  /* Silence the bogus uninitialized warning.  */
  ਰੁੱਖ collection_ਵਿਅੰਜਕ = ਨਿਰਾ;
  location_t loc = c_parser_peek_token (parser)->location;
  location_t for_loc = loc;
  ਤਾਰਕਿਕ is_foreach_statement = ਝੂਠ;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_FOR));
  token_indent_info for_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  ਰੁੱਖ loop_name;
  ਪੂਰਨ ਅੰਕ_ਨਾਂ = c_get_loop_ਨਾਂ (before_labels, ਝੂਠ, &loop_name);

  ਜੇ (parser->omp_for_parse_state)
    {
      error_at (for_loc,
		"loop not permitted in intervening code in OpenMP loop body");
      parser->omp_for_parse_state->fail = ਸੱਚ;
    }

  c_parser_consume_token (parser);
  /* Open a compound statement in Objective-C as well, just in case this is
     as foreach expression.  */
  ਖੰਡ = c_begin_compound_stmt (flag_isoc99 || c_dialect_objc ());
  cond = error_mark_ਗੰਢ;
  incr = error_mark_ਗੰਢ;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      /* Parse the initialization declaration or expression.  */
      object_ਵਿਅੰਜਕ = error_mark_ਗੰਢ;
      parser->objc_could_be_foreach_context = c_dialect_objc ();
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	{
	  parser->objc_could_be_foreach_context = ਝੂਠ;
	  c_parser_consume_token (parser);
	  c_ਅੰਤ_ਵਿਅੰਜਕ_stmt (loc, NULL_ਰੁੱਖ);
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser)
	       || c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
	{
	  c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ,
					 ਝੂਠ, &object_ਵਿਅੰਜਕ);
	  parser->objc_could_be_foreach_context = ਝੂਠ;

	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ਵਿੱਚ))
	    {
	      c_parser_consume_token (parser);
	      is_foreach_statement = ਸੱਚ;
	      ਜੇ (check_for_loop_decls (for_loc, ਸੱਚ) == NULL_ਰੁੱਖ)
		c_parser_error (parser, "multiple iterating variables in "
					"fast enumeration");
	    }
	  ਨਹੀਂਤਾਂ
	    check_for_loop_decls (for_loc, flag_isoc99);
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_EXTENSION))
	{
	  /* __extension__ can start a declaration, but is also an
	     unary operator that can start an expression.  Consume all
	     but the last of a possible series of __extension__ to
	     determine which.  */
	  ਜਦੋਂ (c_parser_peek_2nd_token (parser)->type == CPP_KEYWORD
		 && (c_parser_peek_2nd_token (parser)->keyword
		     == RID_EXTENSION))
	    c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser, 2)
	      || c_parser_nth_token_starts_std_ਗੁਣ (parser, 2))
	    {
	      ਪੂਰਨ ext;
	      ext = disable_extension_diagnostics ();
	      c_parser_consume_token (parser);
	      c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ,
					     ਸੱਚ, ਝੂਠ, &object_ਵਿਅੰਜਕ);
	      parser->objc_could_be_foreach_context = ਝੂਠ;

	      restore_extension_diagnostics (ext);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ਵਿੱਚ))
		{
		  c_parser_consume_token (parser);
		  is_foreach_statement = ਸੱਚ;
		  ਜੇ (check_for_loop_decls (for_loc, ਸੱਚ) == NULL_ਰੁੱਖ)
		    c_parser_error (parser, "multiple iterating variables in "
					    "fast enumeration");
		}
	      ਨਹੀਂਤਾਂ
		check_for_loop_decls (for_loc, flag_isoc99);
	    }
	  ਨਹੀਂਤਾਂ
	    ਜਾਓ init_ਵਿਅੰਜਕ;
	}
      ਨਹੀਂਤਾਂ
	{
	init_ਵਿਅੰਜਕ:
	  {
	    ਬਣਤਰ c_ਵਿਅੰਜਕ ce;
	    ਰੁੱਖ init_ਵਿਅੰਜਕ_2;
	    ce = c_parser_ਵਿਅੰਜਕ (parser);
	    init_ਵਿਅੰਜਕ_2 = ce.ਮੁੱਲ;
	    parser->objc_could_be_foreach_context = ਝੂਠ;
	    ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ਵਿੱਚ))
	      {
		c_parser_consume_token (parser);
		is_foreach_statement = ਸੱਚ;
		ਜੇ (! lvalue_p (init_ਵਿਅੰਜਕ_2))
		  c_parser_error (parser, "invalid iterating variable in "
					  "fast enumeration");
		object_ਵਿਅੰਜਕ
		  = c_fully_fold (init_ਵਿਅੰਜਕ_2, ਝੂਠ, ਨਿਰਾ);
	      }
	    ਨਹੀਂਤਾਂ
	      {
		ce = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ce, ਸੱਚ, ਝੂਠ);
		init_ਵਿਅੰਜਕ_2 = ce.ਮੁੱਲ;
		c_ਅੰਤ_ਵਿਅੰਜਕ_stmt (loc, init_ਵਿਅੰਜਕ_2);
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON,
					   "expected %<;%>");
	      }
	  }
	}
      /* Parse the loop condition.  In the case of a foreach
	 statement, there is no loop condition.  */
      gcc_assert (!parser->objc_could_be_foreach_context);
      ਜੇ (!is_foreach_statement)
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	    {
	      ਜੇ (ivdep)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC ivdep%> pragma");
		  cond = error_mark_ਗੰਢ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (unroll)
		{
		  c_parser_error (parser, "missing loop condition in loop "
					  "with %<GCC unroll%> pragma");
		  cond = error_mark_ਗੰਢ;
		}
	      ਨਹੀਂਤਾਂ
		{
		  c_parser_consume_token (parser);
		  cond = NULL_ਰੁੱਖ;
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      cond = c_parser_condition (parser);
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON,
					 "expected %<;%>");
	    }
	  ਜੇ (ivdep && cond != error_mark_ਗੰਢ)
	    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
			   build_int_cst (integer_type_ਗੰਢ,
					  annot_ਵਿਅੰਜਕ_ivdep_ਕਿਸਮ),
			   integer_zero_ਗੰਢ);
	  ਜੇ (unroll && cond != error_mark_ਗੰਢ)
	    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
 			   build_int_cst (integer_type_ਗੰਢ,
					  annot_ਵਿਅੰਜਕ_unroll_ਕਿਸਮ),
			   build_int_cst (integer_type_ਗੰਢ, unroll));
	  ਜੇ (novector && cond && cond != error_mark_ਗੰਢ)
	    cond = build3 (ANNOTATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (cond), cond,
			   build_int_cst (integer_type_ਗੰਢ,
					  annot_ਵਿਅੰਜਕ_no_ਸਦਿਸ਼_ਕਿਸਮ),
			   integer_zero_ਗੰਢ);
	}
      /* Parse the increment expression (the third expression in a
	 for-statement).  In the case of a foreach-statement, this is
	 the expression that follows the 'in'.  */
      loc = c_parser_peek_token (parser)->location;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  ਜੇ (is_foreach_statement)
	    {
	      c_parser_error (parser,
			      "missing collection in fast enumeration");
	      collection_ਵਿਅੰਜਕ = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ
	    incr = c_process_ਵਿਅੰਜਕ_stmt (loc, NULL_ਰੁੱਖ);
	}
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (is_foreach_statement)
	    collection_ਵਿਅੰਜਕ
	      = c_fully_fold (c_parser_ਵਿਅੰਜਕ (parser).ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	  ਨਹੀਂਤਾਂ
	    {
	      ਬਣਤਰ c_ਵਿਅੰਜਕ ce = c_parser_ਵਿਅੰਜਕ (parser);
	      ce = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ce, ਸੱਚ, ਝੂਠ);
	      incr = c_process_ਵਿਅੰਜਕ_stmt (loc, ce.ਮੁੱਲ);
	    }
	}
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  save_ਵਿੱਚ_statement = ਵਿੱਚ_statement;
  ਜੇ (is_foreach_statement)
    {
      ਵਿੱਚ_statement = ਵਿੱਚ_OBJC_FOREACH;
      save_objc_foreach_break_label = objc_foreach_break_label;
      save_objc_foreach_continue_label = objc_foreach_continue_label;
      objc_foreach_break_label = create_artificial_label (loc);
      objc_foreach_continue_label = create_artificial_label (loc);
      ਜੇ (loop_name)
	{
	  gcc_checking_assert (!DECL_CHAIN (loop_name)
			       && !DECL_CHAIN (objc_foreach_break_label));
	  C_DECL_SWITCH_NAME (loop_name) = 1;
	  DECL_CHAIN (loop_name) = objc_foreach_break_label;
	  DECL_CHAIN (objc_foreach_break_label) = objc_foreach_continue_label;
	}
    }
  ਨਹੀਂਤਾਂ
    ਵਿੱਚ_statement = ਵਿੱਚ_ITERATION_STMT;
  ਜੇ (loop_name)
    {
      C_DECL_LOOP_SWITCH_NAME_VALID (loop_name) = 1;
      ਵਿੱਚ_statement |= ਵਿੱਚ_NAMED_STMT;
    }

  token_indent_info body_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));

  location_t loc_after_labels;
  ਤਾਰਕਿਕ open_brace = c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE);
  body = c_parser_c99_ਖੰਡ_statement (parser, if_p, &loc_after_labels);

  ਜੇ (loop_name && is_foreach_statement)
    {
      gcc_checking_assert (DECL_CHAIN (loop_name) == objc_foreach_break_label
			   && (DECL_CHAIN (objc_foreach_break_label)
			       == objc_foreach_continue_label));
      C_DECL_SWITCH_NAME (loop_name) = 0;
      DECL_CHAIN (loop_name) = NULL_ਰੁੱਖ;
      DECL_CHAIN (objc_foreach_break_label) = NULL_ਰੁੱਖ;
    }

  ਜੇ (is_foreach_statement)
    objc_ਅੰਤ_foreach_loop (for_loc, object_ਵਿਅੰਜਕ,
			      collection_ਵਿਅੰਜਕ, body,
			      objc_foreach_break_label,
			      objc_foreach_continue_label);
  ਨਹੀਂਤਾਂ
    ਜੋੜੋ_stmt (build_stmt (for_loc, FOR_STMT, NULL_ਰੁੱਖ, cond, incr,
			  body, NULL_ਰੁੱਖ,
			  loop_name && C_DECL_LOOP_SWITCH_NAME_ਵਰਤਿਆ (loop_name)
			  ? loop_name : NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ));
  ਜੋੜੋ_stmt (c_ਸਿਰਾ_compound_stmt (for_loc, ਖੰਡ,
				 flag_isoc99 || c_dialect_objc ()));
  c_parser_maybe_reclassify_token (parser);

  token_indent_info ਅਗਲਾ_tinfo
    = get_token_indent_info (c_parser_peek_token (parser));
  warn_for_misleading_indentation (for_tinfo, body_tinfo, ਅਗਲਾ_tinfo);

  ਜੇ (ਅਗਲਾ_tinfo.type != CPP_SEMICOLON && !open_brace)
    warn_for_multistatement_macros (loc_after_labels, ਅਗਲਾ_tinfo.location,
				    for_tinfo.location, RID_FOR);

  ਵਿੱਚ_statement = save_ਵਿੱਚ_statement;
  ਜੇ (ਅੰਕ_ਨਾਂ)
    c_release_loop_ਨਾਂ (ਅੰਕ_ਨਾਂ);
  ਜੇ (is_foreach_statement)
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

ਸਥਿਰ ਰੁੱਖ
c_parser_asm_statement (c_parser *parser)
{
  ਰੁੱਖ str, outputs, inputs, clobbers, labels, ret;
  ਤਾਰਕਿਕ simple;
  location_t asm_loc = c_parser_peek_token (parser)->location;
  ਪੂਰਨ section, nsections;

  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ASM));
  c_parser_consume_token (parser);

  /* Handle the asm-qualifier-list.  */
  location_t volatile_loc = UNKNOWN_LOCATION;
  location_t inline_loc = UNKNOWN_LOCATION;
  location_t goto_loc = UNKNOWN_LOCATION;
  ਲਈ (;;)
    {
      c_token *token = c_parser_peek_token (parser);
      location_t loc = token->location;
      ਚੋਣ (token->keyword)
	{
	ਹਾਲਤ RID_VOLATILE:
	  ਜੇ (volatile_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ਮੁੱਲ);
	      inform (volatile_loc, "first seen here");
	    }
	  ਨਹੀਂਤਾਂ
	    volatile_loc = loc;
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;

	ਹਾਲਤ RID_INLINE:
	  ਜੇ (inline_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ਮੁੱਲ);
	      inform (inline_loc, "first seen here");
	    }
	  ਨਹੀਂਤਾਂ
	    inline_loc = loc;
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;

	ਹਾਲਤ RID_GOTO:
	  ਜੇ (goto_loc)
	    {
	      error_at (loc, "duplicate %<asm%> qualifier %qE", token->ਮੁੱਲ);
	      inform (goto_loc, "first seen here");
	    }
	  ਨਹੀਂਤਾਂ
	    goto_loc = loc;
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;

	ਹਾਲਤ RID_CONST:
	ਹਾਲਤ RID_RESTRICT:
	  error_at (loc, "%qE is not a valid %<asm%> qualifier", token->ਮੁੱਲ);
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;

	ਮੂਲ:
	  ਰੋਕੋ;
	}
      ਰੋਕੋ;
    }

  ਤਾਰਕਿਕ is_volatile = (volatile_loc != UNKNOWN_LOCATION);
  ਤਾਰਕਿਕ is_inline = (inline_loc != UNKNOWN_LOCATION);
  ਤਾਰਕਿਕ is_goto = (goto_loc != UNKNOWN_LOCATION);

  ret = ਨਿਰਾ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਜਾਓ error;

  str = c_parser_asm_string_literal (parser);
  ਜੇ (str == NULL_ਰੁੱਖ)
    ਜਾਓ error_close_paren;

  simple = ਸੱਚ;
  outputs = NULL_ਰੁੱਖ;
  inputs = NULL_ਰੁੱਖ;
  clobbers = NULL_ਰੁੱਖ;
  labels = NULL_ਰੁੱਖ;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
    ਜਾਓ ਪੂਰਾ_asm;

  /* Parse each colon-delimited section of operands.  */
  nsections = 3 + is_goto;
  ਲਈ (section = 0; section < nsections; ++section)
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SCOPE))
	{
	  ++section;
	  ਜੇ (section == nsections)
	    {
	      c_parser_error (parser, "expected %<)%>");
	      ਜਾਓ error_close_paren;
	    }
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (!c_parser_require (parser, CPP_COLON,
				  is_goto
				  ? G_("expected %<:%>")
				  : G_("expected %<:%> or %<)%>"),
				  UNKNOWN_LOCATION, is_goto))
	ਜਾਓ error_close_paren;

      /* Once past any colon, we're no longer a simple asm.  */
      simple = ਝੂਠ;

      ਜੇ ((!c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON)
	   && !c_parser_ਅਗਲਾ_token_is (parser, CPP_SCOPE)
	   && !c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	  || section == 3)
	ਚੋਣ (section)
	  {
	  ਹਾਲਤ 0:
	    outputs = c_parser_asm_operands (parser);
	    ਰੋਕੋ;
	  ਹਾਲਤ 1:
	    inputs = c_parser_asm_operands (parser);
	    ਰੋਕੋ;
	  ਹਾਲਤ 2:
	    clobbers = c_parser_asm_clobbers (parser);
	    ਰੋਕੋ;
	  ਹਾਲਤ 3:
	    labels = c_parser_asm_goto_operands (parser);
	    ਰੋਕੋ;
	  ਮੂਲ:
	    gcc_unreachable ();
	  }

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN) && !is_goto)
	ਜਾਓ ਪੂਰਾ_asm;
    }

 ਪੂਰਾ_asm:
  ਜੇ (!parens.require_close (parser))
    {
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
      ਜਾਓ error;
    }

  ਜੇ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
    c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);

  ret = build_asm_stmt (is_volatile,
			build_asm_ਵਿਅੰਜਕ (asm_loc, str, outputs, inputs,
					clobbers, labels, simple, is_inline));

 error:
  ਵਾਪਸ ret;

 error_close_paren:
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
  ਜਾਓ error;
}

/* Parse asm operands, a GNU extension.

   asm-operands:
     asm-operand
     asm-operands , asm-operand

   asm-operand:
     asm-string-literal ( expression )
     [ identifier ] asm-string-literal ( expression )
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_asm_operands (c_parser *parser)
{
  ਰੁੱਖ list = NULL_ਰੁੱਖ;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਰੁੱਖ name, str;
      ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_ਵਰਗਫਲ))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	    {
	      ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
	      c_parser_consume_token (parser);
	      name = build_string (IDENTIFIER_ਲੰਮਾਈ (id),
				   IDENTIFIER_ਸੂਚਕ (id));
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ, ਨਿਰਾ);
	      ਵਾਪਸ NULL_ਰੁੱਖ;
	    }
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ,
				     "expected %<]%>");
	}
      ਨਹੀਂਤਾਂ
	name = NULL_ਰੁੱਖ;
      str = c_parser_asm_string_literal (parser);
      ਜੇ (str == NULL_ਰੁੱਖ)
	ਵਾਪਸ NULL_ਰੁੱਖ;
      matching_parens parens;
      ਜੇ (!parens.require_open (parser))
	ਵਾਪਸ NULL_ਰੁੱਖ;
      ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
      mark_exp_read (ਵਿਅੰਜਕ.ਮੁੱਲ);
      ਜੇ (!parens.require_close (parser))
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	  ਵਾਪਸ NULL_ਰੁੱਖ;
	}
      list = chainon (list, build_ਰੁੱਖ_list (build_ਰੁੱਖ_list (name, str),
					     ਵਿਅੰਜਕ.ਮੁੱਲ));
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  ਵਾਪਸ list;
}

/* Parse asm clobbers, a GNU extension.

   asm-clobbers:
     asm-string-literal
     asm-clobbers , asm-string-literal
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_asm_clobbers (c_parser *parser)
{
  ਰੁੱਖ list = NULL_ਰੁੱਖ;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਰੁੱਖ str = c_parser_asm_string_literal (parser);
      ਜੇ (str)
	list = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, str, list);
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ NULL_ਰੁੱਖ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  ਵਾਪਸ list;
}

/* Parse asm goto labels, a GNU extension.

   asm-goto-operands:
     identifier
     asm-goto-operands , identifier
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_asm_goto_operands (c_parser *parser)
{
  ਰੁੱਖ list = NULL_ਰੁੱਖ;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਰੁੱਖ name, label;

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  name = tok->ਮੁੱਲ;
	  label = lookup_label_for_goto (tok->location, name);
	  c_parser_consume_token (parser);
	  ਰੁੱਖ_ਵਰਤਿਆ (label) = 1;
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected identifier");
	  ਵਾਪਸ NULL_ਰੁੱਖ;
	}

      name = build_string (IDENTIFIER_ਲੰਮਾਈ (name),
			   IDENTIFIER_ਸੂਚਕ (name));
      list = ਰੁੱਖ_cons (name, label, list);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ nreverse (list);
    }
}

/* Parse a possibly concatenated sequence of string literals.
   TRANSLATE says whether to translate them to the execution character
   set; WIDE_OK says whether any kind of prefixed string literal is
   permitted in this context.  This code is based on that in
   lex_string.  */

ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_string_literal (c_parser *parser, ਤਾਰਕਿਕ translate, ਤਾਰਕਿਕ wide_ok)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਮਾਪ_t ਗਿਣਤੀ_2;
  ਬਣਤਰ obstack str_ob;
  ਬਣਤਰ obstack loc_ob;
  cpp_string str, istr, *strs;
  c_token *tok;
  location_t loc, ਆਖਰੀ_tok_loc;
  ਗਿਣਤੀ cpp_ttype type;
  ਰੁੱਖ ਮੁੱਲ, string_ਰੁੱਖ;

  tok = c_parser_peek_token (parser);
  loc = tok->location;
  ਆਖਰੀ_tok_loc = linemap_resolve_location (ਸਤਰ_ਸਾਰਣੀ, loc,
					   LRK_MACRO_DEFINITION_LOCATION,
					   ਨਿਰਾ);
  type = tok->type;
  ਚੋਣ (type)
    {
    ਹਾਲਤ CPP_STRING:
    ਹਾਲਤ CPP_WSTRING:
    ਹਾਲਤ CPP_STRING16:
    ਹਾਲਤ CPP_STRING32:
    ਹਾਲਤ CPP_UTF8STRING:
      string_ਰੁੱਖ = tok->ਮੁੱਲ;
      ਰੋਕੋ;

    ਮੂਲ:
      c_parser_error (parser, "expected string literal");
      ret.ਸੈੱਟ_error ();
      ret.ਮੁੱਲ = NULL_ਰੁੱਖ;
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = NULL_ਰੁੱਖ;
      ਵਾਪਸ ret;
    }

  /* Try to avoid the overhead of creating and destroying an obstack
     for the common case of just one string.  */
  ਚੋਣ (c_parser_peek_2nd_token (parser)->type)
    {
    ਮੂਲ:
      c_parser_consume_token (parser);
      str.ਪਾਠ = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) ਰੁੱਖ_STRING_ਸੂਚਕ (string_ਰੁੱਖ);
      str.len = ਰੁੱਖ_STRING_ਲੰਮਾਈ (string_ਰੁੱਖ);
      ਗਿਣਤੀ_2 = 1;
      strs = &str;
      ਰੋਕੋ;

    ਹਾਲਤ CPP_STRING:
    ਹਾਲਤ CPP_WSTRING:
    ਹਾਲਤ CPP_STRING16:
    ਹਾਲਤ CPP_STRING32:
    ਹਾਲਤ CPP_UTF8STRING:
      gcc_obstack_init (&str_ob);
      gcc_obstack_init (&loc_ob);
      ਗਿਣਤੀ_2 = 0;
      ਕਰੋ
	{
	  c_parser_consume_token (parser);
	  ਗਿਣਤੀ_2++;
	  str.ਪਾਠ = (ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *) ਰੁੱਖ_STRING_ਸੂਚਕ (string_ਰੁੱਖ);
	  str.len = ਰੁੱਖ_STRING_ਲੰਮਾਈ (string_ਰੁੱਖ);
	  ਜੇ (type != tok->type)
	    {
	      ਜੇ (type == CPP_STRING)
		type = tok->type;
	      ਨਹੀਂਤਾਂ ਜੇ (tok->type != CPP_STRING)
		error ("unsupported non-standard concatenation "
		       "of string literals");
	    }
	  obstack_grow (&str_ob, &str, ਆਕਾਰ (cpp_string));
	  obstack_grow (&loc_ob, &ਆਖਰੀ_tok_loc, ਆਕਾਰ (location_t));
	  tok = c_parser_peek_token (parser);
	  string_ਰੁੱਖ = tok->ਮੁੱਲ;
	  ਆਖਰੀ_tok_loc
	    = linemap_resolve_location (ਸਤਰ_ਸਾਰਣੀ, tok->location,
					LRK_MACRO_DEFINITION_LOCATION, ਨਿਰਾ);
	}
      ਜਦੋਂ (tok->type == CPP_STRING
	     || tok->type == CPP_WSTRING
	     || tok->type == CPP_STRING16
	     || tok->type == CPP_STRING32
	     || tok->type == CPP_UTF8STRING);
      strs = (cpp_string *) obstack_ਅੰਤ (&str_ob);
    }

  ਜੇ (ਗਿਣਤੀ_2 > 1 && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location))
    warning (OPT_Wtraditional,
	     "traditional C rejects string constant concatenation");

  ਜੇ ((type == CPP_STRING || wide_ok)
      && ((translate
	  ? cpp_interpret_string : cpp_interpret_string_notranslate)
	  (parse_ਵਿੱਚ, strs, ਗਿਣਤੀ_2, &istr, type)))
    {
      ਮੁੱਲ = build_string (istr.len, (ਅਚਲ ਅੱਖਰ *) istr.ਪਾਠ);
      ਮੁਕਤ (const_cast<ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *> (istr.ਪਾਠ));
      ਜੇ (ਗਿਣਤੀ_2 > 1)
	{
	  location_t *locs = (location_t *) obstack_ਅੰਤ (&loc_ob);
	  gcc_assert (g_string_concat_db);
	  g_string_concat_db->ਰਿਕਾਰਡ_string_concatenation (ਗਿਣਤੀ_2, locs);
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (type != CPP_STRING && !wide_ok)
	{
	  error_at (loc, "a wide string is invalid in this context");
	  type = CPP_STRING;
	}
      /* Callers cannot generally handle error_mark_node in this
	 context, so return the empty string instead.  An error has
	 been issued, either above or from cpp_interpret_string.  */
      ਚੋਣ (type)
	{
	ਮੂਲ:
	ਹਾਲਤ CPP_STRING:
	ਹਾਲਤ CPP_UTF8STRING:
	  ਜੇ (type == CPP_UTF8STRING && flag_char8_t)
	    {
	      ਮੁੱਲ = build_string (TYPE_PRECISION (char8_type_ਗੰਢ)
				    / TYPE_PRECISION (char_type_ਗੰਢ),
				    "");  /* char8_t is 8 bits */
	    }
	  ਨਹੀਂਤਾਂ
	    ਮੁੱਲ = build_string (1, "");
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_STRING16:
	  ਮੁੱਲ = build_string (TYPE_PRECISION (char16_type_ਗੰਢ)
				/ TYPE_PRECISION (char_type_ਗੰਢ),
				"\0");  /* char16_t is 16 bits */
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_STRING32:
	  ਮੁੱਲ = build_string (TYPE_PRECISION (char32_type_ਗੰਢ)
				/ TYPE_PRECISION (char_type_ਗੰਢ),
				"\0\0\0");  /* char32_t is 32 bits */
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_WSTRING:
	  ਮੁੱਲ = build_string (TYPE_PRECISION (wchar_type_ਗੰਢ)
				/ TYPE_PRECISION (char_type_ਗੰਢ),
				"\0\0\0");  /* widest supported wchar_t
					       is 32 bits */
	  ਰੋਕੋ;
        }
    }

  ਚੋਣ (type)
    {
    ਮੂਲ:
    ਹਾਲਤ CPP_STRING:
      ਰੁੱਖ_TYPE (ਮੁੱਲ) = char_array_type_ਗੰਢ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_UTF8STRING:
      ਜੇ (flag_char8_t)
	ਰੁੱਖ_TYPE (ਮੁੱਲ) = char8_array_type_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	ਰੁੱਖ_TYPE (ਮੁੱਲ) = char_array_type_ਗੰਢ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_STRING16:
      ਰੁੱਖ_TYPE (ਮੁੱਲ) = char16_array_type_ਗੰਢ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_STRING32:
      ਰੁੱਖ_TYPE (ਮੁੱਲ) = char32_array_type_ਗੰਢ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_WSTRING:
      ਰੁੱਖ_TYPE (ਮੁੱਲ) = wchar_array_type_ਗੰਢ;
    }
  ਮੁੱਲ = fix_string_type (ਮੁੱਲ);

  ਜੇ (ਗਿਣਤੀ_2 > 1)
    {
      obstack_free (&str_ob, 0);
      obstack_free (&loc_ob, 0);
    }

  ret.ਮੁੱਲ = ਮੁੱਲ;
  ret.original_ਕੋਡ = STRING_CST;
  ret.original_type = NULL_ਰੁੱਖ;
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, get_range_from_loc (ਸਤਰ_ਸਾਰਣੀ, loc));
  ret.m_decimal = 0;
  parser->ਵੇਖਿਆ_string_literal = ਸੱਚ;
  ਵਾਪਸ ret;
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_ਵਿਅੰਜਕ_no_commas (c_parser *parser, ਬਣਤਰ c_ਵਿਅੰਜਕ *after,
			 ਰੁੱਖ omp_atomic_lhs)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ lhs, rhs, ret;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ;
  location_t op_location, exp_location;
  ਤਾਰਕਿਕ save_ਵਿੱਚ_omp_for = c_ਵਿੱਚ_omp_for;
  c_ਵਿੱਚ_omp_for = ਝੂਠ;
  gcc_assert (!after || c_dialect_objc ());
  lhs = c_parser_conditional_ਵਿਅੰਜਕ (parser, after, omp_atomic_lhs);
  op_location = c_parser_peek_token (parser)->location;
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_EQ:
      ਕੋਡ = NOP_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_MULT_EQ:
      ਕੋਡ = MULT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_DIV_EQ:
      ਕੋਡ = TRUNC_DIV_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_MOD_EQ:
      ਕੋਡ = TRUNC_MOD_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_PLUS_EQ:
      ਕੋਡ = PLUS_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_MINUS_EQ:
      ਕੋਡ = MINUS_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_LSHIFT_EQ:
      ਕੋਡ = LSHIFT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_RSHIFT_EQ:
      ਕੋਡ = RSHIFT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_AND_EQ:
      ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_XOR_EQ:
      ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_OR_EQ:
      ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਮੂਲ:
      c_ਵਿੱਚ_omp_for = save_ਵਿੱਚ_omp_for;
      ਵਾਪਸ lhs;
    }
  c_parser_consume_token (parser);
  exp_location = c_parser_peek_token (parser)->location;
  rhs = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  rhs = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (exp_location, rhs, ਸੱਚ, ਸੱਚ);

  ret.ਮੁੱਲ = build_modify_ਵਿਅੰਜਕ (op_location, lhs.ਮੁੱਲ, lhs.original_type,
				 ਕੋਡ, exp_location, rhs.ਮੁੱਲ,
				 rhs.original_type);
  ret.m_decimal = 0;
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, lhs.get_ਸ਼ੁਰੂ (), rhs.get_ਅੰਤ ());
  ਜੇ (ਕੋਡ == NOP_ਵਿਅੰਜਕ)
    ret.original_ਕੋਡ = MODIFY_ਵਿਅੰਜਕ;
  ਨਹੀਂਤਾਂ
    {
      suppress_warning (ret.ਮੁੱਲ, OPT_Wparentheses);
      ret.original_ਕੋਡ = ERROR_MARK;
    }
  ret.original_type = ਨਿਰਾ;
  c_ਵਿੱਚ_omp_for = save_ਵਿੱਚ_omp_for;
  ਵਾਪਸ ret;
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_conditional_ਵਿਅੰਜਕ (c_parser *parser, ਬਣਤਰ c_ਵਿਅੰਜਕ *after,
				 ਰੁੱਖ omp_atomic_lhs)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ cond, exp1, exp2, ret;
  location_t ਸ਼ੁਰੂ, cond_loc, colon_loc;
  ਤਾਰਕਿਕ save_c_omp_array_section_p = c_omp_array_section_p;

  gcc_assert (!after || c_dialect_objc ());

  cond = c_parser_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (parser, after, omp_atomic_lhs);

  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_QUERY))
    ਵਾਪਸ cond;
  c_omp_array_section_p = ਝੂਠ;
  ਜੇ (cond.ਮੁੱਲ != error_mark_ਗੰਢ)
    ਸ਼ੁਰੂ = cond.get_ਸ਼ੁਰੂ ();
  ਨਹੀਂਤਾਂ
    ਸ਼ੁਰੂ = UNKNOWN_LOCATION;
  cond_loc = c_parser_peek_token (parser)->location;
  cond = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (cond_loc, cond, ਸੱਚ, ਸੱਚ);
  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
    {
      ਰੁੱਖ eptype = NULL_ਰੁੱਖ;

      location_t ਵਿਚਕਾਰ_loc = c_parser_peek_token (parser)->location;
      pedwarn (ਵਿਚਕਾਰ_loc, OPT_Wpedantic,
	       "ISO C forbids omitting the middle term of a %<?:%> expression");
      ਜੇ (ਰੁੱਖ_ਕੋਡ (cond.ਮੁੱਲ) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	{
	  eptype = ਰੁੱਖ_TYPE (cond.ਮੁੱਲ);
	  cond.ਮੁੱਲ = ਰੁੱਖ_ਸੰਕਾਰਜ (cond.ਮੁੱਲ, 0);
	}
      ਰੁੱਖ e = cond.ਮੁੱਲ;
      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (e) == COMPOUND_ਵਿਅੰਜਕ)
	e = ਰੁੱਖ_ਸੰਕਾਰਜ (e, 1);
      warn_for_omitted_condop (ਵਿਚਕਾਰ_loc, e);
      /* Make sure first operand is calculated only once.  */
      exp1.ਮੁੱਲ = save_ਵਿਅੰਜਕ (default_conversion (cond.ਮੁੱਲ));
      ਜੇ (eptype)
	exp1.ਮੁੱਲ = build1 (EXCESS_PRECISION_ਵਿਅੰਜਕ, eptype, exp1.ਮੁੱਲ);
      exp1.original_type = ਨਿਰਾ;
      exp1.src_range = cond.src_range;
      cond.ਮੁੱਲ = c_objc_common_truthvalue_conversion (cond_loc, exp1.ਮੁੱਲ);
      c_inhibit_evaluation_warnings += cond.ਮੁੱਲ == truthvalue_true_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ
    {
      cond.ਮੁੱਲ
	= c_objc_common_truthvalue_conversion
	(cond_loc, default_conversion (cond.ਮੁੱਲ));
      c_inhibit_evaluation_warnings += cond.ਮੁੱਲ == truthvalue_false_ਗੰਢ;
      exp1 = c_parser_ਵਿਅੰਜਕ_conv (parser);
      mark_exp_read (exp1.ਮੁੱਲ);
      c_inhibit_evaluation_warnings +=
	((cond.ਮੁੱਲ == truthvalue_true_ਗੰਢ)
	 - (cond.ਮੁੱਲ == truthvalue_false_ਗੰਢ));
    }

  colon_loc = c_parser_peek_token (parser)->location;
  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      c_inhibit_evaluation_warnings -= cond.ਮੁੱਲ == truthvalue_true_ਗੰਢ;
      ret.ਸੈੱਟ_error ();
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = ਨਿਰਾ;
      c_omp_array_section_p = save_c_omp_array_section_p;
      ਵਾਪਸ ret;
    }
  {
    location_t exp2_loc = c_parser_peek_token (parser)->location;
    exp2 = c_parser_conditional_ਵਿਅੰਜਕ (parser, ਨਿਰਾ, NULL_ਰੁੱਖ);
    exp2 = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (exp2_loc, exp2, ਸੱਚ, ਸੱਚ);
  }
  c_inhibit_evaluation_warnings -= cond.ਮੁੱਲ == truthvalue_true_ਗੰਢ;
  location_t loc1 = make_location (exp1.get_ਸ਼ੁਰੂ (), exp1.src_range);
  location_t loc2 = make_location (exp2.get_ਸ਼ੁਰੂ (), exp2.src_range);
  ਜੇ (UNLIKELY (omp_atomic_lhs != ਨਿਰਾ)
      && (ਰੁੱਖ_ਕੋਡ (cond.ਮੁੱਲ) == GT_ਵਿਅੰਜਕ
	  || ਰੁੱਖ_ਕੋਡ (cond.ਮੁੱਲ) == LT_ਵਿਅੰਜਕ
	  || ਰੁੱਖ_ਕੋਡ (cond.ਮੁੱਲ) == EQ_ਵਿਅੰਜਕ)
      && c_ਰੁੱਖ_equal (exp2.ਮੁੱਲ, omp_atomic_lhs)
      && (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (cond.ਮੁੱਲ, 0), omp_atomic_lhs)
	  || c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (cond.ਮੁੱਲ, 1), omp_atomic_lhs)))
    ret.ਮੁੱਲ = build3_loc (colon_loc, COND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (omp_atomic_lhs),
			    cond.ਮੁੱਲ, exp1.ਮੁੱਲ, exp2.ਮੁੱਲ);
  ਨਹੀਂਤਾਂ
    ret.ਮੁੱਲ
      = build_conditional_ਵਿਅੰਜਕ (colon_loc, cond.ਮੁੱਲ,
				cond.original_ਕੋਡ == C_MAYBE_CONST_ਵਿਅੰਜਕ,
				exp1.ਮੁੱਲ, exp1.original_type, loc1,
				exp2.ਮੁੱਲ, exp2.original_type, loc2);
  ret.original_ਕੋਡ = ERROR_MARK;
  ਜੇ (exp1.ਮੁੱਲ == error_mark_ਗੰਢ || exp2.ਮੁੱਲ == error_mark_ਗੰਢ)
    ret.original_type = ਨਿਰਾ;
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ t1, t2;

      /* If both sides are enum type, the default conversion will have
	 made the type of the result be an integer type.  We want to
	 remember the enum types we started with.  */
      t1 = exp1.original_type ? exp1.original_type : ਰੁੱਖ_TYPE (exp1.ਮੁੱਲ);
      t2 = exp2.original_type ? exp2.original_type : ਰੁੱਖ_TYPE (exp2.ਮੁੱਲ);
      ret.original_type = ((t1 != error_mark_ਗੰਢ
			    && t2 != error_mark_ਗੰਢ
			    && (TYPE_MAIN_VARIANT (t1)
				== TYPE_MAIN_VARIANT (t2)))
			   ? t1
			   : ਨਿਰਾ);
    }
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, ਸ਼ੁਰੂ, exp2.get_ਅੰਤ ());
  ret.m_decimal = 0;
  c_omp_array_section_p = save_c_omp_array_section_p;
  ਵਾਪਸ ret;
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (c_parser *parser, ਬਣਤਰ c_ਵਿਅੰਜਕ *after,
			    ਰੁੱਖ omp_atomic_lhs)
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

  ਬਣਤਰ {
    /* The expression at this stack level.  */
    ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
    /* The precedence of the operator on its left, PREC_NONE at the
       bottom of the stack.  */
    ਗਿਣਤੀ c_parser_prec prec;
    /* The operation on its left.  */
    ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 op;
    /* The source location of this operation.  */
    location_t loc;
    /* The sizeof argument if expr.original_code == {PAREN_,}SIZEOF_EXPR.  */
    ਰੁੱਖ sizeof_arg;
    /* The original expr.value before c_objc_common_truthvalue_conversion
       for TRUTH_{AND,OR}*_EXPR lhs operands.  */
    ਰੁੱਖ orig_ਵਿਅੰਜਕ;
  } ਢੇਰ[ਅੰਕ_PRECS];
  ਪੂਰਨ sp;
  /* Location of the binary operator.  */
  location_t ਦੁਆਧਾਰੀ_loc = UNKNOWN_LOCATION;  /* Quiet warning.  */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਕੱਢੋ_2								      \
  ਕਰੋ {									      \
    ਚੋਣ (ਢੇਰ[sp].op)						      \
      {									      \
      ਹਾਲਤ TRUTH_ANDIF_ਵਿਅੰਜਕ:						      \
	c_inhibit_evaluation_warnings -= (ਢੇਰ[sp - 1].ਵਿਅੰਜਕ.ਮੁੱਲ	      \
					  == truthvalue_false_ਗੰਢ);	      \
	ਰੋਕੋ;								      \
      ਹਾਲਤ TRUTH_ORIF_ਵਿਅੰਜਕ:						      \
	c_inhibit_evaluation_warnings -= (ਢੇਰ[sp - 1].ਵਿਅੰਜਕ.ਮੁੱਲ	      \
					  == truthvalue_true_ਗੰਢ);	      \
	ਰੋਕੋ;								      \
      ਹਾਲਤ TRUNC_DIV_ਵਿਅੰਜਕ:						      \
	ਜੇ ((ਢੇਰ[sp - 1].ਵਿਅੰਜਕ.original_ਕੋਡ == SIZEOF_ਵਿਅੰਜਕ		      \
	     || ਢੇਰ[sp - 1].ਵਿਅੰਜਕ.original_ਕੋਡ == PAREN_SIZEOF_ਵਿਅੰਜਕ)	      \
	    && (ਢੇਰ[sp].ਵਿਅੰਜਕ.original_ਕੋਡ == SIZEOF_ਵਿਅੰਜਕ		      \
		|| ਢੇਰ[sp].ਵਿਅੰਜਕ.original_ਕੋਡ == PAREN_SIZEOF_ਵਿਅੰਜਕ))	      \
	  {								      \
	    ਰੁੱਖ type0 = ਢੇਰ[sp - 1].sizeof_arg;			      \
	    ਰੁੱਖ type1 = ਢੇਰ[sp].sizeof_arg;				      \
	    ਰੁੱਖ ਪਹਿਲਾ_arg = type0;					      \
	    ਜੇ (!TYPE_P (type0))					      \
	      type0 = ਰੁੱਖ_TYPE (type0);				      \
	    ਜੇ (!TYPE_P (type1))					      \
	      type1 = ਰੁੱਖ_TYPE (type1);				      \
	    ਜੇ (ਸੂਚਕ_TYPE_P (type0)					      \
		&& comptypes (ਰੁੱਖ_TYPE (type0), type1)			      \
		&& !(ਰੁੱਖ_ਕੋਡ (ਪਹਿਲਾ_arg) == PARM_DECL			      \
		     && C_ARRAY_PARAMETER (ਪਹਿਲਾ_arg)			      \
		     && warn_sizeof_array_ਦਲੀਲ))			      \
	      {								      \
		auto_diagnostic_ਸਮੂਹ d;				      \
		ਜੇ (warning_at (ਢੇਰ[sp].loc, OPT_Wsizeof_ਸੂਚਕ_div,	      \
				  "division %<sizeof (%T) / sizeof (%T)%> "   \
				  "does not compute the number of array "     \
				  "elements",				      \
				  type0, type1))			      \
		  ਜੇ (DECL_P (ਪਹਿਲਾ_arg))				      \
		    inform (DECL_ਸਰੋਤ_LOCATION (ਪਹਿਲਾ_arg),		      \
			      "first %<sizeof%> operand was declared here");  \
	      }								      \
	    ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type0) == ARRAY_TYPE			      \
		     && !char_type_p (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (type0)))  \
		     && ਢੇਰ[sp].ਵਿਅੰਜਕ.original_ਕੋਡ != PAREN_SIZEOF_ਵਿਅੰਜਕ)    \
	      maybe_warn_sizeof_array_div (ਢੇਰ[sp].loc, ਪਹਿਲਾ_arg, type0,   \
					   ਢੇਰ[sp].sizeof_arg, type1);      \
	  }								      \
	ਰੋਕੋ;								      \
      ਮੂਲ:								      \
	ਰੋਕੋ;								      \
      }									      \
    ਢੇਰ[sp - 1].ਵਿਅੰਜਕ							      \
      = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਢੇਰ[sp - 1].loc,			      \
				  ਢੇਰ[sp - 1].ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);	      \
    ਢੇਰ[sp].ਵਿਅੰਜਕ							      \
      = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਢੇਰ[sp].loc,			      \
				  ਢੇਰ[sp].ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);		      \
    ਜੇ (UNLIKELY (omp_atomic_lhs != NULL_ਰੁੱਖ) && sp == 1		      \
	&& ((c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)		      \
	     && ((1 << ਢੇਰ[sp].prec)					      \
		 & ((1 << PREC_BITOR) | (1 << PREC_BITXOR)		      \
		     | (1 << PREC_BITAND) | (1 << PREC_ਖਿਸਕਾਓ)		      \
		     | (1 << PREC_ਜੋੜੋ) | (1 << PREC_MULT)		      \
		     | (1 << PREC_EQ))))				      \
	    || ((c_parser_ਅਗਲਾ_token_is (parser, CPP_QUERY)		      \
		 || (omp_atomic_lhs == void_list_ਗੰਢ			      \
		     && c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN)))    \
		&& (ਢੇਰ[sp].prec == PREC_REL || ਢੇਰ[sp].prec == PREC_EQ)))\
	&& ਢੇਰ[sp].op != TRUNC_MOD_ਵਿਅੰਜਕ				      \
	&& ਢੇਰ[sp].op != GE_ਵਿਅੰਜਕ					      \
	&& ਢੇਰ[sp].op != LE_ਵਿਅੰਜਕ					      \
	&& ਢੇਰ[sp].op != NE_ਵਿਅੰਜਕ					      \
	&& ਢੇਰ[0].ਵਿਅੰਜਕ.ਮੁੱਲ != error_mark_ਗੰਢ			      \
	&& ਢੇਰ[1].ਵਿਅੰਜਕ.ਮੁੱਲ != error_mark_ਗੰਢ			      \
	&& (omp_atomic_lhs == void_list_ਗੰਢ				      \
	    || c_ਰੁੱਖ_equal (ਢੇਰ[0].ਵਿਅੰਜਕ.ਮੁੱਲ, omp_atomic_lhs)	      \
	    || c_ਰੁੱਖ_equal (ਢੇਰ[1].ਵਿਅੰਜਕ.ਮੁੱਲ, omp_atomic_lhs)	      \
	    || (ਢੇਰ[sp].op == EQ_ਵਿਅੰਜਕ					      \
		&& c_parser_peek_2nd_token (parser)->keyword == RID_IF)))     \
      {									      \
	ਰੁੱਖ t = make_ਗੰਢ (ਢੇਰ[1].op);				      \
	ਰੁੱਖ_TYPE (t) = ਰੁੱਖ_TYPE (ਢੇਰ[0].ਵਿਅੰਜਕ.ਮੁੱਲ);		      \
	ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0) = ਢੇਰ[0].ਵਿਅੰਜਕ.ਮੁੱਲ;			      \
	ਰੁੱਖ_ਸੰਕਾਰਜ (t, 1) = ਢੇਰ[1].ਵਿਅੰਜਕ.ਮੁੱਲ;			      \
	ਢੇਰ[0].ਵਿਅੰਜਕ.ਮੁੱਲ = t;					      \
	ਢੇਰ[0].ਵਿਅੰਜਕ.m_decimal = 0;					      \
      }									      \
    ਨਹੀਂਤਾਂ								      \
      ਢੇਰ[sp - 1].ਵਿਅੰਜਕ = parser_build_ਦੁਆਧਾਰੀ_op (ਢੇਰ[sp].loc,	      \
						   ਢੇਰ[sp].op,	      \
						   ਢੇਰ[sp - 1].ਵਿਅੰਜਕ,	      \
						   ਢੇਰ[sp].ਵਿਅੰਜਕ,	      \
						   ਢੇਰ[sp - 1].orig_ਵਿਅੰਜਕ);  \
    ਢੇਰ[sp - 1].orig_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;				      \
    sp--;								      \
  } ਜਦੋਂ (0)
  gcc_assert (!after || c_dialect_objc ());
  ਢੇਰ[0].loc = c_parser_peek_token (parser)->location;
  ਢੇਰ[0].ਵਿਅੰਜਕ = c_parser_cast_ਵਿਅੰਜਕ (parser, after);
  ਢੇਰ[0].prec = PREC_NONE;
  ਢੇਰ[0].sizeof_arg = c_ਆਖਰੀ_sizeof_arg;
  ਢੇਰ[0].orig_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  sp = 0;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਗਿਣਤੀ c_parser_prec oprec;
      ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ocode;
      ਸਰੋਤ_range src_range;
      ਜੇ (parser->error)
	ਜਾਓ ਬਾਹਰਲਾ;
      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_MULT:
	  oprec = PREC_MULT;
	  ocode = MULT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_DIV:
	  oprec = PREC_MULT;
	  ocode = TRUNC_DIV_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_MOD:
	  oprec = PREC_MULT;
	  ocode = TRUNC_MOD_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_PLUS:
	  oprec = PREC_ਜੋੜੋ;
	  ocode = PLUS_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_MINUS:
	  oprec = PREC_ਜੋੜੋ;
	  ocode = MINUS_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_LSHIFT:
	  oprec = PREC_ਖਿਸਕਾਓ;
	  ocode = LSHIFT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_RSHIFT:
	  oprec = PREC_ਖਿਸਕਾਓ;
	  ocode = RSHIFT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_LESS:
	  oprec = PREC_REL;
	  ocode = LT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_GREATER:
	  oprec = PREC_REL;
	  ocode = GT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_LESS_EQ:
	  oprec = PREC_REL;
	  ocode = LE_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_GREATER_EQ:
	  oprec = PREC_REL;
	  ocode = GE_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_EQ_EQ:
	  oprec = PREC_EQ;
	  ocode = EQ_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_NOT_EQ:
	  oprec = PREC_EQ;
	  ocode = NE_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_AND:
	  oprec = PREC_BITAND;
	  ocode = ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_XOR:
	  oprec = PREC_BITXOR;
	  ocode = ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_OR:
	  oprec = PREC_BITOR;
	  ocode = ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_AND_AND:
	  oprec = PREC_LOGAND;
	  ocode = TRUTH_ANDIF_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_OR_OR:
	  oprec = PREC_LOGOR;
	  ocode = TRUTH_ORIF_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਮੂਲ:
	  /* Not a binary operator, so end of the binary
	     expression.  */
	  ਜਾਓ ਬਾਹਰਲਾ;
	}
      ਦੁਆਧਾਰੀ_loc = c_parser_peek_token (parser)->location;
      ਜਦੋਂ (oprec <= ਢੇਰ[sp].prec)
	ਕੱਢੋ_2;
      c_parser_consume_token (parser);
      ਚੋਣ (ocode)
	{
	ਹਾਲਤ TRUTH_ANDIF_ਵਿਅੰਜਕ:
	  src_range = ਢੇਰ[sp].ਵਿਅੰਜਕ.src_range;
	  ਢੇਰ[sp].ਵਿਅੰਜਕ
	    = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਢੇਰ[sp].loc,
					ਢੇਰ[sp].ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);
	  ਢੇਰ[sp].orig_ਵਿਅੰਜਕ = ਢੇਰ[sp].ਵਿਅੰਜਕ.ਮੁੱਲ;
	  ਢੇਰ[sp].ਵਿਅੰਜਕ.ਮੁੱਲ = c_objc_common_truthvalue_conversion
	    (ਢੇਰ[sp].loc, default_conversion (ਢੇਰ[sp].ਵਿਅੰਜਕ.ਮੁੱਲ));
	  c_inhibit_evaluation_warnings += (ਢੇਰ[sp].ਵਿਅੰਜਕ.ਮੁੱਲ
					    == truthvalue_false_ਗੰਢ);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਢੇਰ[sp].ਵਿਅੰਜਕ, src_range);
	  ਰੋਕੋ;
	ਹਾਲਤ TRUTH_ORIF_ਵਿਅੰਜਕ:
	  src_range = ਢੇਰ[sp].ਵਿਅੰਜਕ.src_range;
	  ਢੇਰ[sp].ਵਿਅੰਜਕ
	    = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਢੇਰ[sp].loc,
					ਢੇਰ[sp].ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);
	  ਢੇਰ[sp].orig_ਵਿਅੰਜਕ = ਢੇਰ[sp].ਵਿਅੰਜਕ.ਮੁੱਲ;
	  ਢੇਰ[sp].ਵਿਅੰਜਕ.ਮੁੱਲ = c_objc_common_truthvalue_conversion
	    (ਢੇਰ[sp].loc, default_conversion (ਢੇਰ[sp].ਵਿਅੰਜਕ.ਮੁੱਲ));
	  c_inhibit_evaluation_warnings += (ਢੇਰ[sp].ਵਿਅੰਜਕ.ਮੁੱਲ
					    == truthvalue_true_ਗੰਢ);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਢੇਰ[sp].ਵਿਅੰਜਕ, src_range);
	  ਰੋਕੋ;
	ਮੂਲ:
	  ਰੋਕੋ;
	}
      sp++;
      ਢੇਰ[sp].loc = ਦੁਆਧਾਰੀ_loc;
      ਢੇਰ[sp].ਵਿਅੰਜਕ = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      ਢੇਰ[sp].prec = oprec;
      ਢੇਰ[sp].op = ocode;
      ਢੇਰ[sp].sizeof_arg = c_ਆਖਰੀ_sizeof_arg;
      ਢੇਰ[sp].orig_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
    }
 ਬਾਹਰਲਾ:
  ਜਦੋਂ (sp > 0)
    ਕੱਢੋ_2;
  ਵਾਪਸ ਢੇਰ[0].ਵਿਅੰਜਕ;
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਕੱਢੋ_2
}

/* Parse any storage class specifiers after an open parenthesis in a
   context where a compound literal is permitted.  */

ਸਥਿਰ ਬਣਤਰ c_declspecs *
c_parser_compound_literal_scspecs (c_parser *parser)
{
  ਤਾਰਕਿਕ ਵੇਖਿਆ_scspec = ਝੂਠ;
  ਬਣਤਰ c_declspecs *specs = build_null_declspecs ();
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD))
    {
      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_CONSTEXPR:
	ਹਾਲਤ RID_ਰਜਿਸਟਰ:
	ਹਾਲਤ RID_STATIC:
	ਹਾਲਤ RID_THREAD:
	  ਵੇਖਿਆ_scspec = ਸੱਚ;
	  declspecs_ਜੋੜੋ_scspec (c_parser_peek_token (parser)->location,
				specs, c_parser_peek_token (parser)->ਮੁੱਲ);
	  c_parser_consume_token (parser);
	  ਰੋਕੋ;
	ਮੂਲ:
	  ਜਾਓ ਬਾਹਰਲਾ;
	}
    }
 ਬਾਹਰਲਾ:
  ਵਾਪਸ ਵੇਖਿਆ_scspec ? specs : ਨਿਰਾ;
}

/* Parse a cast expression (C90 6.3.4, C99 6.5.4, C11 6.5.4).  If AFTER
   is not NULL then it is an Objective-C message expression which is the
   primary-expression starting the expression as an initializer.

   cast-expression:
     unary-expression
     ( type-name ) unary-expression
*/

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_cast_ਵਿਅੰਜਕ (c_parser *parser, ਬਣਤਰ c_ਵਿਅੰਜਕ *after)
{
  location_t cast_loc = c_parser_peek_token (parser)->location;
  gcc_assert (!after || c_dialect_objc ());
  ਜੇ (after)
    ਵਾਪਸ c_parser_postfix_ਵਿਅੰਜਕ_after_primary (parser,
						      cast_loc, *after);
  /* If the expression begins with a parenthesized type name, it may
     be either a cast or a compound literal; we need to see whether
     the next character is '{' to tell the difference.  If not, it is
     an unary expression.  Full detection of unknown typenames here
     would require a 3-token lookahead.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      ਬਣਤਰ c_declspecs *scspecs;
      ਬਣਤਰ c_type_name *type_name;
      ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
      ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
      matching_parens parens;
      parens.consume_open (parser);
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ਸੱਚ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਜੇ (type_name == ਨਿਰਾ)
	{
	  ret.ਸੈੱਟ_error ();
	  ret.original_ਕੋਡ = ERROR_MARK;
	  ret.original_type = ਨਿਰਾ;
	  ਵਾਪਸ ret;
	}

      /* Save casted types in the function's used types hash table.  */
      ਵਰਤਿਆ_types_ਪਾਓ (type_name->specs->type);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
	ਵਾਪਸ c_parser_postfix_ਵਿਅੰਜਕ_after_paren_type (parser, scspecs,
							     type_name,
							     cast_loc);
      ਜੇ (scspecs)
	error_at (cast_loc, "storage class specifier in cast");
      ਜੇ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in cast");
      {
	location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
	ਵਿਅੰਜਕ = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
	ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);
      }
      ret.ਮੁੱਲ = c_cast_ਵਿਅੰਜਕ (cast_loc, type_name, ਵਿਅੰਜਕ.ਮੁੱਲ);
      ਜੇ (ret.ਮੁੱਲ && ਵਿਅੰਜਕ.ਮੁੱਲ)
	ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, cast_loc, ਵਿਅੰਜਕ.get_ਅੰਤ ());
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = ਨਿਰਾ;
      ret.m_decimal = 0;
      ਵਾਪਸ ret;
    }
  ਨਹੀਂਤਾਂ
    ਵਾਪਸ c_parser_unary_ਵਿਅੰਜਕ (parser);
}


/* Like mark_exp_read but skip marking VAR_DECLs and PARM_DECLs
   depending on the warning mode.  This helper function is
   used in c_parser_unary_expression and
   and c_parser_postfix_expression_after_primary for
   pre/post-increment/decrement operations.
 */

ਸਥਿਰ ਖਾਲੀ
mark_exp_read_cond (ਰੁੱਖ ਘਾਤਾਂਕ)
{
  ਜੇ ((VAR_P (ਘਾਤਾਂਕ) || ਰੁੱਖ_ਕੋਡ (ਘਾਤਾਂਕ) == PARM_DECL)
      && (VAR_P (ਘਾਤਾਂਕ) ? warn_ਅਣਵਰਤਿਆ_but_ਸੈੱਟ_variable
		      : warn_ਅਣਵਰਤਿਆ_but_ਸੈੱਟ_parameter) > 1)
    ਵਾਪਸ;

  mark_exp_read (ਘਾਤਾਂਕ);
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_unary_ਵਿਅੰਜਕ (c_parser *parser)
{
  ਪੂਰਨ ext;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t exp_loc;
  location_t ਅੰਤ;
  ret.original_ਕੋਡ = ERROR_MARK;
  ret.original_type = ਨਿਰਾ;
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_PLUS_PLUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      mark_exp_read_cond (op.ਮੁੱਲ);
      op = default_function_array_conversion (exp_loc, op);
      ਵਾਪਸ parser_build_unary_op (op_loc, PREINCREMENT_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_MINUS_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      mark_exp_read_cond (op.ਮੁੱਲ);
      op = default_function_array_conversion (exp_loc, op);
      ਵਾਪਸ parser_build_unary_op (op_loc, PREDECREMENT_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      mark_exp_read (op.ਮੁੱਲ);
      ਵਾਪਸ parser_build_unary_op (op_loc, ADDR_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_MULT:
      {
	c_parser_consume_token (parser);
	exp_loc = c_parser_peek_token (parser)->location;
	op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
	ਅੰਤ = op.get_ਅੰਤ ();
	op = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (exp_loc, op, ਸੱਚ, ਸੱਚ);
	location_t combined_loc = make_location (op_loc, op_loc, ਅੰਤ);
	ret.ਮੁੱਲ = build_ਅਸਿੱਧਾ_ref (combined_loc, op.ਮੁੱਲ, RO_UNARY_ਤਾਰਾ);
	ret.src_range.m_ਸ਼ੁਰੂ = op_loc;
	ret.src_range.m_ਅੰਤ = ਅੰਤ;
	ret.m_decimal = 0;
	ਵਾਪਸ ret;
      }
    ਹਾਲਤ CPP_PLUS:
      ਜੇ (!c_dialect_objc () && !ਵਿੱਚ_system_ਸਿਰਲੇਖ_at (ਨਿਵੇਸ਼_location))
	warning_at (op_loc,
		    OPT_Wtraditional,
		    "traditional C rejects the unary plus operator");
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      op = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (exp_loc, op, ਸੱਚ, ਸੱਚ);
      ਵਾਪਸ parser_build_unary_op (op_loc, CONVERT_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_MINUS:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      op = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (exp_loc, op, ਸੱਚ, ਸੱਚ);
      ਵਾਪਸ parser_build_unary_op (op_loc, NEGATE_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_COMPL:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      op = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (exp_loc, op, ਸੱਚ, ਸੱਚ);
      ਵਾਪਸ parser_build_unary_op (op_loc, ਦੋਆਧਾਰੀ_ਅੰਕ_NOT_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_NOT:
      c_parser_consume_token (parser);
      exp_loc = c_parser_peek_token (parser)->location;
      op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      op = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (exp_loc, op, ਸੱਚ, ਸੱਚ);
      ਵਾਪਸ parser_build_unary_op (op_loc, TRUTH_NOT_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_AND_AND:
      /* Refer to the address of a label as a pointer.  */
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  ret.ਮੁੱਲ = ਅੰਤ_label_ਪਤਾ_ਵਿਅੰਜਕ
	    (c_parser_peek_token (parser)->ਮੁੱਲ, op_loc);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, op_loc,
				   c_parser_peek_token (parser)->get_ਅੰਤ ());
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected identifier");
	  ret.ਸੈੱਟ_error ();
	}
      ਵਾਪਸ ret;
    ਹਾਲਤ CPP_KEYWORD:
      {
	ਗਿਣਤੀ rid rid = c_parser_peek_token (parser)->keyword;
	ਚੋਣ (rid)
	  {
	  ਹਾਲਤ RID_COUNTOF:
	  ਹਾਲਤ RID_SIZEOF:
	    ਵਾਪਸ c_parser_sizeof_or_countof_ਵਿਅੰਜਕ (parser, rid);
	  ਹਾਲਤ RID_ALIGNOF:
	    ਵਾਪਸ c_parser_alignof_ਵਿਅੰਜਕ (parser);
	  ਹਾਲਤ RID_MAXOF:
	  ਹਾਲਤ RID_MINOF:
	    ਵਾਪਸ c_parser_maxof_or_minof_ਵਿਅੰਜਕ (parser, rid);
	  ਹਾਲਤ RID_BUILTIN_HAS_ATTRIBUTE:
	    ਵਾਪਸ c_parser_has_attribute_ਵਿਅੰਜਕ (parser);
	  ਹਾਲਤ RID_EXTENSION:
	    c_parser_consume_token (parser);
	    ext = disable_extension_diagnostics ();
	    ret = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
	    restore_extension_diagnostics (ext);
	    ਵਾਪਸ ret;
	  ਹਾਲਤ RID_REALPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
	    op = default_function_array_conversion (exp_loc, op);
	    ਵਾਪਸ parser_build_unary_op (op_loc, REALPART_ਵਿਅੰਜਕ, op);
	  ਹਾਲਤ RID_IMAGPART:
	    c_parser_consume_token (parser);
	    exp_loc = c_parser_peek_token (parser)->location;
	    op = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
	    op = default_function_array_conversion (exp_loc, op);
	    ਵਾਪਸ parser_build_unary_op (op_loc, IMAGPART_ਵਿਅੰਜਕ, op);
	  ਹਾਲਤ RID_TRANSACTION_ATOMIC:
	  ਹਾਲਤ RID_TRANSACTION_RELAXED:
	    ਵਾਪਸ c_parser_transaction_ਵਿਅੰਜਕ (parser, rid);
	  ਹਾਲਤ RID_STATIC_ASSERT:
	    c_parser_static_assert_declaration_no_semi (parser);
	    pedwarn_c23 (op_loc, OPT_Wpedantic,
			 "ISO C does not support static assertions in "
			 "expressions before C2Y");
	    ret.ਮੁੱਲ = void_ਗੰਢ;
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, op_loc, op_loc);
	    ret.m_decimal = 0;
	    ਵਾਪਸ ret;
	  ਮੂਲ:
	    ਵਾਪਸ c_parser_postfix_ਵਿਅੰਜਕ (parser);
	  }
      }
    ਮੂਲ:
      ਵਾਪਸ c_parser_postfix_ਵਿਅੰਜਕ (parser);
    }
}

/* Parse a sizeof or _Countof expression.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_sizeof_or_countof_ਵਿਅੰਜਕ (c_parser *parser, ਗਿਣਤੀ rid rid)
{
  ਅਚਲ ਅੱਖਰ *op_name = (rid == RID_COUNTOF) ? "_Countof" : "sizeof";
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਨਤੀਜਾ;
  location_t ਵਿਅੰਜਕ_loc;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, rid));

  location_t ਸ਼ੁਰੂ;
  location_t ਅੰਤ = UNKNOWN_LOCATION;

  ਸ਼ੁਰੂ = c_parser_peek_token (parser)->location;

  ਜੇ (rid == RID_COUNTOF)
    pedwarn_c23 (ਸ਼ੁਰੂ, OPT_Wpedantic,
		 "ISO C does not support %qs before C2Y", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ਜੇ (rid == RID_COUNTOF)
    ਵਿੱਚ_countof++;
  ਨਹੀਂਤਾਂ
    ਵਿੱਚ_sizeof++;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either sizeof ( type-name ) or sizeof unary-expression
	 starting with a compound literal.  */
      ਬਣਤਰ c_declspecs *scspecs;
      ਬਣਤਰ c_type_name *type_name;
      matching_parens parens;
      parens.consume_open (parser);
      ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ਸੱਚ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਅੰਤ = parser->ਟੋਕਨ_buf[0].location;
      ਜੇ (type_name == ਨਿਰਾ)
	{
	  /* Let c_expr_sizeof_expr call pop_maybe_used and fill in c_expr
	     for parsing error; the parsing of the expression could have
	     called record_maybe_used_decl.  */
	  ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	  ਜਾਓ Xof_ਵਿਅੰਜਕ;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
	{
	  ਵਿਅੰਜਕ = c_parser_postfix_ਵਿਅੰਜਕ_after_paren_type (parser, scspecs,
							       type_name,
							       ਵਿਅੰਜਕ_loc);
	  ਅੰਤ = ਵਿਅੰਜਕ.get_ਅੰਤ ();
	  ਜਾਓ Xof_ਵਿਅੰਜਕ;
	}
      /* sizeof ( type-name ).  */
      ਜੇ (scspecs)
	error_at (ਵਿਅੰਜਕ_loc, "storage class specifier in %qs", op_name);
      ਜੇ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qs", op_name);
      c_inhibit_evaluation_warnings--;
      ਜੇ (rid == RID_COUNTOF)
	{
	  ਵਿੱਚ_countof--;
	  ਨਤੀਜਾ = c_ਵਿਅੰਜਕ_countof_type (ਵਿਅੰਜਕ_loc, type_name);
	}
      ਨਹੀਂਤਾਂ
	{
	  ਵਿੱਚ_sizeof--;
	  ਨਤੀਜਾ = c_ਵਿਅੰਜਕ_sizeof_type (ਵਿਅੰਜਕ_loc, type_name);
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      ਵਿਅੰਜਕ = c_parser_unary_ਵਿਅੰਜਕ (parser);
      ਅੰਤ = ਵਿਅੰਜਕ.get_ਅੰਤ ();
    Xof_ਵਿਅੰਜਕ:
      c_inhibit_evaluation_warnings--;
      ਜੇ (rid == RID_COUNTOF)
	ਵਿੱਚ_countof--;
      ਨਹੀਂਤਾਂ
	ਵਿੱਚ_sizeof--;
      mark_exp_read (ਵਿਅੰਜਕ.ਮੁੱਲ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == COMPONENT_REF
	  && DECL_C_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ.ਮੁੱਲ, 1)))
	error_at (ਵਿਅੰਜਕ_loc, "%qs applied to a bit-field", op_name);
      ਜੇ (rid == RID_COUNTOF)
	ਨਤੀਜਾ = c_ਵਿਅੰਜਕ_countof_ਵਿਅੰਜਕ (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ);
      ਨਹੀਂਤਾਂ
	ਨਤੀਜਾ = c_ਵਿਅੰਜਕ_sizeof_ਵਿਅੰਜਕ (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ);
    }
  ਜੇ (ਅੰਤ == UNKNOWN_LOCATION)
    ਅੰਤ = ਸ਼ੁਰੂ;
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਨਤੀਜਾ, ਸ਼ੁਰੂ, ਅੰਤ);
  ਵਾਪਸ ਨਤੀਜਾ;
}

/* Parse an alignof expression.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_alignof_ਵਿਅੰਜਕ (c_parser *parser)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  location_t ਸ਼ੁਰੂ_loc = c_parser_peek_token (parser)->location;
  location_t ਸਿਰਾ_loc;
  ਰੁੱਖ alignof_spelling = c_parser_peek_token (parser)->ਮੁੱਲ;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ALIGNOF));
  ਤਾਰਕਿਕ is_c11_alignof = (strcmp (IDENTIFIER_ਸੂਚਕ (alignof_spelling),
				"_Alignof") == 0
			 || strcmp (IDENTIFIER_ਸੂਚਕ (alignof_spelling),
				    "alignof") == 0);
  /* A diagnostic is not required for the use of this identifier in
     the implementation namespace; only diagnose it for the C11 or C23
     spelling because of existing code using the other spellings.  */
  ਜੇ (is_c11_alignof)
    {
      ਜੇ (flag_isoc99)
	pedwarn_c99 (ਸ਼ੁਰੂ_loc, OPT_Wpedantic, "ISO C99 does not support %qE",
		     alignof_spelling);
      ਨਹੀਂਤਾਂ
	pedwarn_c99 (ਸ਼ੁਰੂ_loc, OPT_Wpedantic, "ISO C90 does not support %qE",
		     alignof_spelling);
    }
  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ਵਿੱਚ_alignof++;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_compound_literal (c_parser_peek_2nd_token (parser)))
    {
      /* Either __alignof__ ( type-name ) or __alignof__
	 unary-expression starting with a compound literal.  */
      location_t loc;
      ਬਣਤਰ c_declspecs *scspecs;
      ਬਣਤਰ c_type_name *type_name;
      ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
      matching_parens parens;
      parens.consume_open (parser);
      loc = c_parser_peek_token (parser)->location;
      scspecs = c_parser_compound_literal_scspecs (parser);
      type_name = c_parser_type_name (parser, ਸੱਚ);
      ਸਿਰਾ_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਜੇ (type_name == ਨਿਰਾ)
	{
	  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
	  c_inhibit_evaluation_warnings--;
	  ਵਿੱਚ_alignof--;
	  ret.ਸੈੱਟ_error ();
	  ret.original_ਕੋਡ = ERROR_MARK;
	  ret.original_type = ਨਿਰਾ;
	  ਵਾਪਸ ret;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
	{
	  ਵਿਅੰਜਕ = c_parser_postfix_ਵਿਅੰਜਕ_after_paren_type (parser, scspecs,
							       type_name,
							       loc);
	  ਜਾਓ alignof_ਵਿਅੰਜਕ;
	}
      /* alignof ( type-name ).  */
      ਜੇ (scspecs)
	error_at (loc, "storage class specifier in %qE", alignof_spelling);
      ਜੇ (type_name->specs->alignas_p)
	error_at (type_name->specs->locations[cdw_alignas],
		  "alignment specified for type name in %qE",
		  alignof_spelling);
      c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_alignof--;
      ret.ਮੁੱਲ = c_sizeof_or_alignof_type (loc, groktypename (type_name,
							       ਨਿਰਾ, ਨਿਰਾ),
					    ਝੂਠ, is_c11_alignof, 1);
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = ਨਿਰਾ;
      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, ਸ਼ੁਰੂ_loc, ਸਿਰਾ_loc);
      ret.m_decimal = 0;
      ਵਾਪਸ ret;
    }
  ਨਹੀਂਤਾਂ
    {
      ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
      ਵਿਅੰਜਕ = c_parser_unary_ਵਿਅੰਜਕ (parser);
      ਸਿਰਾ_loc = ਵਿਅੰਜਕ.src_range.m_ਅੰਤ;
    alignof_ਵਿਅੰਜਕ:
      mark_exp_read (ਵਿਅੰਜਕ.ਮੁੱਲ);
      c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_alignof--;
      ਜੇ (is_c11_alignof)
	pedwarn (ਸ਼ੁਰੂ_loc,
		 OPT_Wpedantic, "ISO C does not allow %<%E (expression)%>",
		 alignof_spelling);
      ret.ਮੁੱਲ = c_alignof_ਵਿਅੰਜਕ (ਸ਼ੁਰੂ_loc, ਵਿਅੰਜਕ.ਮੁੱਲ);
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = ਨਿਰਾ;
      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, ਸ਼ੁਰੂ_loc, ਸਿਰਾ_loc);
      ret.m_decimal = 0;
      ਵਾਪਸ ret;
    }
}

/* Parse a _Maxof or _Minof expression.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_maxof_or_minof_ਵਿਅੰਜਕ (c_parser *parser, ਗਿਣਤੀ rid rid)
{
  ਅਚਲ ਅੱਖਰ *op_name = (rid == RID_MAXOF) ? "_Maxof" : "_Minof";
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਨਤੀਜਾ;
  location_t ਵਿਅੰਜਕ_loc;
  ਬਣਤਰ c_type_name *type_name;
  matching_parens parens;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, rid));

  location_t ਸ਼ੁਰੂ;
  location_t ਅੰਤ = UNKNOWN_LOCATION;

  ਸ਼ੁਰੂ = c_parser_peek_token (parser)->location;

  pedwarn (ਸ਼ੁਰੂ, OPT_Wpedantic, "ISO C does not support %qs", op_name);

  c_parser_consume_token (parser);
  c_inhibit_evaluation_warnings++;
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected %<(%>");
      ਜਾਓ fail;
    }
  parens.consume_open (parser);
  ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
  ਜੇ (!c_token_starts_typename (c_parser_peek_token (parser)))
    {
      error_at (ਵਿਅੰਜਕ_loc, "invalid application of %qs to something not a type", op_name);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਜਾਓ fail;
    }
  type_name = c_parser_type_name (parser, ਸੱਚ);
  ਜੇ (type_name == ਨਿਰਾ)
    {
      // c_parser_type_name() has already diagnosed the error.
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਜਾਓ fail;
    }
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਅੰਤ = parser->ਟੋਕਨ_buf[0].location;
  ਜੇ (type_name->specs->alignas_p)
    error_at (type_name->specs->locations[cdw_alignas],
	      "alignment specified for type name in %qs", op_name);
  c_inhibit_evaluation_warnings--;
  ਜੇ (rid == RID_MAXOF)
    ਨਤੀਜਾ = c_ਵਿਅੰਜਕ_maxof_type (ਵਿਅੰਜਕ_loc, type_name);
  ਨਹੀਂਤਾਂ
    ਨਤੀਜਾ = c_ਵਿਅੰਜਕ_minof_type (ਵਿਅੰਜਕ_loc, type_name);
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਨਤੀਜਾ, ਸ਼ੁਰੂ, ਅੰਤ);
  ਵਾਪਸ ਨਤੀਜਾ;
fail:
  c_inhibit_evaluation_warnings--;
  ਨਤੀਜਾ.ਸੈੱਟ_error ();
  ਨਤੀਜਾ.original_ਕੋਡ = ERROR_MARK;
  ਨਤੀਜਾ.original_type = ਨਿਰਾ;
  ਵਾਪਸ ਨਤੀਜਾ;
}

/* Parse the __builtin_has_attribute ([expr|type], attribute-spec)
   expression.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_has_attribute_ਵਿਅੰਜਕ (c_parser *parser)
{
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser,
					      RID_BUILTIN_HAS_ATTRIBUTE));
  location_t ਸ਼ੁਰੂ = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);

  c_inhibit_evaluation_warnings++;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    {
      c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_typeof--;

      ਬਣਤਰ c_ਵਿਅੰਜਕ ਨਤੀਜਾ;
      ਨਤੀਜਾ.ਸੈੱਟ_error ();
      ਨਤੀਜਾ.original_ਕੋਡ = ERROR_MARK;
      ਨਤੀਜਾ.original_type = ਨਿਰਾ;
      ਵਾਪਸ ਨਤੀਜਾ;
    }

  /* Treat the type argument the same way as in typeof for the purposes
     of warnings.  FIXME: Generalize this so the warning refers to
     __builtin_has_attribute rather than typeof.  */
  ਵਿੱਚ_typeof++;

  /* The first operand: one of DECL, EXPR, or TYPE.  */
  ਰੁੱਖ oper = NULL_ਰੁੱਖ;
  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, cla_prefer_id))
    {
      ਬਣਤਰ c_type_name *tname = c_parser_type_name (parser);
      ਵਿੱਚ_typeof--;
      ਜੇ (tname)
	{
	  oper = groktypename (tname, ਨਿਰਾ, ਨਿਰਾ);
	  ਕੱਢੋ_maybe_ਵਰਤਿਆ (c_type_variably_modified_p (oper));
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਬਣਤਰ c_ਵਿਅੰਜਕ cexpr = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_typeof--;
      ਜੇ (cexpr.ਮੁੱਲ != error_mark_ਗੰਢ)
	{
	  mark_exp_read (cexpr.ਮੁੱਲ);
	  oper = cexpr.ਮੁੱਲ;
	  ਰੁੱਖ etype = ਰੁੱਖ_TYPE (oper);
	  ਤਾਰਕਿਕ was_vm = c_type_variably_modified_p (etype);
	  /* This is returned with the type so that when the type is
	     evaluated, this can be evaluated.  */
	  ਜੇ (was_vm)
	    oper = c_fully_fold (oper, ਝੂਠ, ਨਿਰਾ);
	  ਕੱਢੋ_maybe_ਵਰਤਿਆ (was_vm);
	}
    }

  ਬਣਤਰ c_ਵਿਅੰਜਕ ਨਤੀਜਾ;
  ਨਤੀਜਾ.original_ਕੋਡ = ERROR_MARK;
  ਨਤੀਜਾ.original_type = ਨਿਰਾ;

  ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      /* Consume the closing parenthesis if that's the next token
	 in the likely case the built-in was invoked with fewer
	 than two arguments.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      c_inhibit_evaluation_warnings--;
      ਨਤੀਜਾ.ਸੈੱਟ_error ();
      ਵਾਪਸ ਨਤੀਜਾ;
    }

  ਤਾਰਕਿਕ save_translate_ਲੜੀਆਂ_p = parser->translate_ਲੜੀਆਂ_p;

  location_t atloc = c_parser_peek_token (parser)->location;
  /* Parse a single attribute.  Require no leading comma and do not
     allow empty attributes.  */
  ਰੁੱਖ attr = c_parser_gnu_attribute (parser, NULL_ਰੁੱਖ, ਝੂਠ, ਝੂਠ);

  parser->translate_ਲੜੀਆਂ_p = save_translate_ਲੜੀਆਂ_p;

  location_t ਅੰਤ = c_parser_peek_token (parser)->location;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
    c_parser_consume_token (parser);
  ਨਹੀਂਤਾਂ
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);

      ਨਤੀਜਾ.ਸੈੱਟ_error ();
      ਵਾਪਸ ਨਤੀਜਾ;
    }

  ਜੇ (!attr)
    {
      error_at (atloc, "expected identifier");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ਨਤੀਜਾ.ਸੈੱਟ_error ();
      ਵਾਪਸ ਨਤੀਜਾ;
    }

  ਨਤੀਜਾ.original_ਕੋਡ = INTEGER_CST;
  ਨਤੀਜਾ.original_type = boolean_type_ਗੰਢ;

  ਜੇ (has_attribute (atloc, oper, attr, default_conversion))
    ਨਤੀਜਾ.ਮੁੱਲ = boolean_true_ਗੰਢ;
  ਨਹੀਂਤਾਂ
    ਨਤੀਜਾ.ਮੁੱਲ =  boolean_false_ਗੰਢ;

  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਨਤੀਜਾ, ਸ਼ੁਰੂ, ਅੰਤ);
  ਨਤੀਜਾ.m_decimal = 0;
  ਵਾਪਸ ਨਤੀਜਾ;
}

/* Helper function to read arguments of builtins which are interfaces
   for the middle-end nodes like COMPLEX_EXPR, VEC_PERM_EXPR and
   others.  The name of the builtin is passed using BNAME parameter.
   Function returns true if there were no errors while parsing and
   stores the arguments in CEXPR_LIST.  If it returns true,
   *OUT_CLOSE_PAREN_LOC is written to with the location of the closing
   parenthesis.  */
ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_get_builtin_ਦਲੀਲਾਂ (c_parser *parser, ਅਚਲ ਅੱਖਰ *bname,
			   vec<c_ਵਿਅੰਜਕ_t, va_gc> **ret_cexpr_list,
			   ਤਾਰਕਿਕ ਚੁਣੋ_ਵਿਅੰਜਕ_p,
			   location_t *ਬਾਹਰਲਾ_close_paren_loc)
{
  location_t loc = c_parser_peek_token (parser)->location;
  vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
  c_ਵਿਅੰਜਕ_t ਵਿਅੰਜਕ;
  ਤਾਰਕਿਕ saved_force_folding_builtin_constant_p;

  *ret_cexpr_list = ਨਿਰਾ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_OPEN_PAREN))
    {
      error_at (loc, "cannot take address of %qs", bname);
      ਵਾਪਸ ਝੂਠ;
    }

  c_parser_consume_token (parser);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
    {
      *ਬਾਹਰਲਾ_close_paren_loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ਵਾਪਸ ਸੱਚ;
    }

  saved_force_folding_builtin_constant_p
    = force_folding_builtin_constant_p;
  force_folding_builtin_constant_p |= ਚੁਣੋ_ਵਿਅੰਜਕ_p;
  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  force_folding_builtin_constant_p
    = saved_force_folding_builtin_constant_p;
  vec_alloc (cexpr_list, 1);
  vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (cexpr_list, ਵਿਅੰਜਕ);
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  ਰੁੱਖ ਮੁੱਲ = embed->ਮੁੱਲ;
	  ਵਿਅੰਜਕ.original_ਕੋਡ = INTEGER_CST;
	  ਵਿਅੰਜਕ.original_type = integer_type_ਗੰਢ;
	  ਵਿਅੰਜਕ.ਮੁੱਲ = NULL_ਰੁੱਖ;
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, embed->get_range ());
	  ਵਿਅੰਜਕ.m_decimal = 0;
	  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < (ਬਿਨਾਨਿਸ਼ਾਨੀ) RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ); i++)
	    {
	      ਵਿਅੰਜਕ.ਮੁੱਲ = build_int_cst (integer_type_ਗੰਢ,
					  RAW_ਅੰਕੜੇ_UCHAR_ELT (ਮੁੱਲ, i));
	      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (cexpr_list, ਵਿਅੰਜਕ);
	    }
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}
      ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (cexpr_list, ਵਿਅੰਜਕ);
    }

  *ਬਾਹਰਲਾ_close_paren_loc = c_parser_peek_token (parser)->location;
  ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ਵਾਪਸ ਝੂਠ;

  *ret_cexpr_list = cexpr_list;
  ਵਾਪਸ ਸੱਚ;
}

/* This represents a single generic-association.  */

ਬਣਤਰ c_generic_association
{
  /* The location of the starting token of the type.  */
  location_t type_location;
  /* The association's type, or NULL_TREE for 'default'.  */
  ਰੁੱਖ type;
  /* The association's expression.  */
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ_2;
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_generic_selection (c_parser *parser)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ selector, error_ਵਿਅੰਜਕ;
  ਰੁੱਖ selector_type;
  ਬਣਤਰ c_generic_association matched_assoc;
  ਪੂਰਨ ਮੇਲ_ਮਿਲਿਆ = -1;
  location_t generic_loc, selector_loc;

  error_ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
  error_ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
  error_ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
  matched_assoc.type_location = UNKNOWN_LOCATION;
  matched_assoc.type = NULL_ਰੁੱਖ;
  matched_assoc.ਵਿਅੰਜਕ_2 = error_ਵਿਅੰਜਕ;

  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_GENERIC));
  generic_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  ਜੇ (flag_isoc99)
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C99 does not support %<_Generic%>");
  ਨਹੀਂਤਾਂ
    pedwarn_c99 (generic_loc, OPT_Wpedantic,
		 "ISO C90 does not support %<_Generic%>");

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ error_ਵਿਅੰਜਕ;

  selector_loc = c_parser_peek_token (parser)->location;
  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, cla_prefer_id))
    {
      c_inhibit_evaluation_warnings++;
      pedwarn_c23 (selector_loc, OPT_Wpedantic,
		   "ISO C does not support use of type name as %<_Generic%> "
		   "controlling operand before C2Y");
      ਬਣਤਰ c_type_name *type = c_parser_type_name (parser);
      ਜੇ (type)
	selector_type = groktypename (type, ਨਿਰਾ, ਨਿਰਾ);
      c_inhibit_evaluation_warnings--;
      ਜੇ (!type)
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	  ਵਾਪਸ error_ਵਿਅੰਜਕ;
	}
    }
  ਨਹੀਂਤਾਂ
    {
      c_inhibit_evaluation_warnings++;
      ਵਿੱਚ_generic++;
      selector = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      selector = default_function_array_conversion (selector_loc, selector);
      c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_generic--;
      ਕੱਢੋ_maybe_ਵਰਤਿਆ (!flag_isoc23);

      ਜੇ (selector.ਮੁੱਲ == error_mark_ਗੰਢ)
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	  ਵਾਪਸ selector;
	}
      mark_exp_read (selector.ਮੁੱਲ);
      selector_type = ਰੁੱਖ_TYPE (selector.ਮੁੱਲ);
      /* In ISO C terms, rvalues (including the controlling expression
	 of _Generic) do not have qualified types.  */
      ਜੇ (ਰੁੱਖ_ਕੋਡ (selector_type) != ARRAY_TYPE)
	selector_type = TYPE_MAIN_VARIANT (selector_type);
      /* In ISO C terms, _Noreturn is not part of the type of expressions
	 such as &abort, but in GCC it is represented internally as a type
	 qualifier.  */
      ਜੇ (FUNCTION_ਸੂਚਕ_TYPE_P (selector_type)
	  && TYPE_QUALS (ਰੁੱਖ_TYPE (selector_type)) != TYPE_UNQUALIFIED)
	selector_type
	  = c_build_ਸੂਚਕ_type (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (selector_type)));
    }

  ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    {
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
      ਵਾਪਸ error_ਵਿਅੰਜਕ;
    }

  auto_vec<c_generic_association> associations;
  ਬਣਤਰ maybe_ਵਰਤਿਆ_decl *maybe_ਵਰਤਿਆ_default = ਨਿਰਾ;
  ਜਦੋਂ (1)
    {
      ਬਣਤਰ c_generic_association assoc, *iter;
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ix;
      c_token *token = c_parser_peek_token (parser);

      assoc.type_location = token->location;
      ਜੇ (token->type == CPP_KEYWORD && token->keyword == RID_DEFAULT)
	{
	  c_parser_consume_token (parser);
	  assoc.type = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਬਣਤਰ c_type_name *type_name;

	  type_name = c_parser_type_name (parser);
	  ਜੇ (type_name == ਨਿਰਾ)
	    {
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	      ਵਾਪਸ error_ਵਿਅੰਜਕ;
	    }
	  assoc.type = grokgenassoc (type_name);
	  ਜੇ (assoc.type == error_mark_ਗੰਢ)
	    {
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	      ਵਾਪਸ error_ਵਿਅੰਜਕ;
	    }

	  ਜੇ (ਰੁੱਖ_ਕੋਡ (assoc.type) == FUNCTION_TYPE)
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "function type before C2Y");
	  ਨਹੀਂਤਾਂ ਜੇ (!COMPLETE_TYPE_P (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "incomplete type before C2Y");

	  ਜੇ (c_type_variably_modified_p (assoc.type))
	    pedwarn_c23 (assoc.type_location, OPT_Wpedantic,
			 "ISO C does not support %<_Generic%> association with "
			 "variably-modified type before C2Y");
	}

      ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	  ਵਾਪਸ error_ਵਿਅੰਜਕ;
	}

      ਤਾਰਕਿਕ ਮੇਲ = assoc.type == NULL_ਰੁੱਖ
		   || comptypes (assoc.type, selector_type);

      ਜੇ (!ਮੇਲ || matched_assoc.type != NULL_ਰੁੱਖ)
	c_inhibit_evaluation_warnings++;
      ਵਿੱਚ_generic++;

      assoc.ਵਿਅੰਜਕ_2 = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);

      ਜੇ (!ਮੇਲ || matched_assoc.type != NULL_ਰੁੱਖ)
	c_inhibit_evaluation_warnings--;
      ਵਿੱਚ_generic--;
      ਜੇ (!ਮੇਲ)
	ਕੱਢੋ_maybe_ਵਰਤਿਆ (!flag_isoc23);
      ਨਹੀਂਤਾਂ ਜੇ (assoc.type == NULL_ਰੁੱਖ)
	maybe_ਵਰਤਿਆ_default = save_maybe_ਵਰਤਿਆ ();
      ਨਹੀਂਤਾਂ
	ਕੱਢੋ_maybe_ਵਰਤਿਆ (ਸੱਚ);

      ਜੇ (assoc.ਵਿਅੰਜਕ_2.ਮੁੱਲ == error_mark_ਗੰਢ)
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	  ਵਾਪਸ error_ਵਿਅੰਜਕ;
	}

      ਲਈ (ix = 0; associations.iterate (ix, &iter); ++ix)
	{
	  ਜੇ (assoc.type == NULL_ਰੁੱਖ)
	    {
	      ਜੇ (iter->type == NULL_ਰੁੱਖ)
		{
		  error_at (assoc.type_location,
			    "duplicate %<default%> case in %<_Generic%>");
		  inform (iter->type_location, "original %<default%> is here");
		}
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (iter->type != NULL_ਰੁੱਖ)
	    {
	      ਜੇ (comptypes (assoc.type, iter->type))
		{
		  error_at (assoc.type_location,
			    "%<_Generic%> specifies two compatible types");
		  inform (iter->type_location, "compatible type is here");
		}
	    }
	}

      ਜੇ (assoc.type == NULL_ਰੁੱਖ)
	{
	  ਜੇ (ਮੇਲ_ਮਿਲਿਆ < 0)
	    {
	      matched_assoc = assoc;
	      ਮੇਲ_ਮਿਲਿਆ = associations.ਲੰਮਾਈ ();
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਮੇਲ)
	{
	  ਜੇ (ਮੇਲ_ਮਿਲਿਆ < 0 || matched_assoc.type == NULL_ਰੁੱਖ)
	    {
	      matched_assoc = assoc;
	      ਮੇਲ_ਮਿਲਿਆ = associations.ਲੰਮਾਈ ();
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      error_at (assoc.type_location,
			"%<_Generic%> selector matches multiple associations");
	      inform (matched_assoc.type_location,
		      "other match is here");
	    }
	}

      associations.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (assoc);

      ਜੇ (c_parser_peek_token (parser)->type != CPP_COMMA)
	ਰੋਕੋ;
      c_parser_consume_token (parser);
    }

  ਜੇ (ਮੇਲ_ਮਿਲਿਆ >= 0 && matched_assoc.type == NULL_ਰੁੱਖ)
    {
      /* Declarations referenced in the default association are used.  */
      restore_maybe_ਵਰਤਿਆ (maybe_ਵਰਤਿਆ_default);
      ਕੱਢੋ_maybe_ਵਰਤਿਆ (ਸੱਚ);
    }
  ਨਹੀਂਤਾਂ ਜੇ (maybe_ਵਰਤਿਆ_default)
    {
      /* Declarations referenced in the default association are not used, but
	 are treated as used before C23.  */
      restore_maybe_ਵਰਤਿਆ (maybe_ਵਰਤਿਆ_default);
      ਕੱਢੋ_maybe_ਵਰਤਿਆ (!flag_isoc23);
    }

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ix;
  ਬਣਤਰ c_generic_association *iter;
  FOR_EACH_VEC_ELT (associations, ix, iter)
    ਜੇ (ix != (ਬਿਨਾਨਿਸ਼ਾਨੀ) ਮੇਲ_ਮਿਲਿਆ)
      mark_exp_read (iter->ਵਿਅੰਜਕ_2.ਮੁੱਲ);

  ਜੇ (!parens.require_close (parser))
    {
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
      ਵਾਪਸ error_ਵਿਅੰਜਕ;
    }

  ਜੇ (ਮੇਲ_ਮਿਲਿਆ < 0)
    {
      error_at (selector_loc, "%<_Generic%> selector of type %qT is not "
		"compatible with any association",
		selector_type);
      ਵਾਪਸ error_ਵਿਅੰਜਕ;
    }

  ਵਾਪਸ matched_assoc.ਵਿਅੰਜਕ_2;
}

/* Check the validity of a function pointer argument *EXPR (argument
   position POS) to __builtin_tgmath.  Return the number of function
   arguments if possibly valid; return 0 having reported an error if
   not valid.  */

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ
check_tgmath_function (c_ਵਿਅੰਜਕ *ਵਿਅੰਜਕ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ pos)
{
  ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ->ਮੁੱਲ);
  ਜੇ (!FUNCTION_ਸੂਚਕ_TYPE_P (type))
    {
      error_at (ਵਿਅੰਜਕ->get_location (),
		"argument %u of %<__builtin_tgmath%> is not a function pointer",
		pos);
      ਵਾਪਸ 0;
    }
  type = ਰੁੱਖ_TYPE (type);
  ਜੇ (!prototype_p (type))
    {
      error_at (ਵਿਅੰਜਕ->get_location (),
		"argument %u of %<__builtin_tgmath%> is unprototyped", pos);
      ਵਾਪਸ 0;
    }
  ਜੇ (stdarg_p (type))
    {
      error_at (ਵਿਅੰਜਕ->get_location (),
		"argument %u of %<__builtin_tgmath%> has variable arguments",
		pos);
      ਵਾਪਸ 0;
    }
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nargs = 0;
  function_ਦਲੀਲਾਂ_iterator iter;
  ਰੁੱਖ t;
  FOREACH_FUNCTION_ਦਲੀਲਾਂ (type, t, iter)
    {
      ਜੇ (t == void_type_ਗੰਢ)
	ਰੋਕੋ;
      nargs++;
    }
  ਜੇ (nargs == 0)
    {
      error_at (ਵਿਅੰਜਕ->get_location (),
		"argument %u of %<__builtin_tgmath%> has no arguments", pos);
      ਵਾਪਸ 0;
    }
  ਵਾਪਸ nargs;
}

/* Ways in which a parameter or return value of a type-generic macro
   may vary between the different functions the macro may call.  */
ਗਿਣਤੀ tgmath_parm_ਕਿਸਮ
  {
    tgmath_fixed, tgmath_real, tgmath_complex
  };

/* Helper function for c_parser_postfix_expression.  Parse predefined
   identifiers.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_predefined_identifier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਚੋਣ (c_parser_peek_token (parser)->keyword)
    {
    ਹਾਲਤ RID_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__FUNCTION__");
      ਰੋਕੋ;
    ਹਾਲਤ RID_PRETTY_FUNCTION_NAME:
      pedwarn (loc, OPT_Wpedantic, "ISO C does not support %qs predefined "
	       "identifier", "__PRETTY_FUNCTION__");
      ਰੋਕੋ;
    ਹਾਲਤ RID_C99_FUNCTION_NAME:
      pedwarn_c90 (loc, OPT_Wpedantic, "ISO C90 does not support "
		   "%<__func__%> predefined identifier");
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }

  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
  ਵਿਅੰਜਕ.ਮੁੱਲ = fname_decl (loc, c_parser_peek_token (parser)->keyword,
			   c_parser_peek_token (parser)->ਮੁੱਲ);
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, loc);
  ਵਿਅੰਜਕ.m_decimal = 0;
  c_parser_consume_token (parser);
  ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* Check whether the REF has an counted-by object associated with it
   through the "counted_by" attribute.  */

ਸਥਿਰ ਤਾਰਕਿਕ
has_counted_by_object (ਰੁੱਖ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  ਜੇ ((ਰੁੱਖ_ਕੋਡ (ref) == ਅਸਿੱਧਾ_REF
       && is_access_with_ਮਾਪ_p (ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 0)))
      || is_access_with_ਮਾਪ_p (ref))
    ਵਾਪਸ ਸੱਚ;
  ਵਾਪਸ ਝੂਠ;
}

/* Get the reference to the counted-by object associated with the REF.  */

ਸਥਿਰ ਰੁੱਖ
get_counted_by_ref (ਰੁੱਖ ref)
{
  /* Currently, there are two cases are valid:
     A. when the ref is an indirect_ref to a call to the
	.ACCESS_WITH_SIZE, return true. (this is for FAM)
     B. when the ref is a call to .ACCESS_WITH_SIZE, return true.
	(this is for pointer field inside a structure)
     More cases can be included later when the counted_by attribute is
     extended to other situations.  */
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ref) == ਅਸਿੱਧਾ_REF
      && is_access_with_ਮਾਪ_p (ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 0)))
    ਵਾਪਸ CALL_ਵਿਅੰਜਕ_ARG (ਰੁੱਖ_ਸੰਕਾਰਜ (ref, 0), 1);
  ਨਹੀਂਤਾਂ ਜੇ (is_access_with_ਮਾਪ_p (ref))
    ਵਾਪਸ CALL_ਵਿਅੰਜਕ_ARG (ref, 1);

  ਵਾਪਸ NULL_ਰੁੱਖ;
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_postfix_ਵਿਅੰਜਕ (c_parser *parser)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ, e1;
  ਬਣਤਰ c_type_name *t1, *t2;
  location_t loc = c_parser_peek_token (parser)->location;
  ਸਰੋਤ_range tok_range = c_parser_peek_token (parser)->get_range ();
  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
  ਵਿਅੰਜਕ.m_decimal = 0;
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_ਸੰਖਿਆ:
      ਵਿਅੰਜਕ.ਮੁੱਲ = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      ਵਿਅੰਜਕ.m_decimal = c_parser_peek_token (parser)->flags & DECIMAL_INT;
      c_parser_consume_token (parser);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == FIXED_CST
	  && !targetm.fixed_ਬਿੰਦੂ_supported_p ())
	{
	  error_at (loc, "fixed-point types not supported for this target");
	  ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	}
      ਰੋਕੋ;
    ਹਾਲਤ CPP_CHAR:
    ਹਾਲਤ CPP_CHAR16:
    ਹਾਲਤ CPP_CHAR32:
    ਹਾਲਤ CPP_UTF8CHAR:
    ਹਾਲਤ CPP_WCHAR:
      ਵਿਅੰਜਕ.ਮੁੱਲ = c_parser_peek_token (parser)->ਮੁੱਲ;
      /* For the purpose of warning when a pointer is compared with
	 a zero character constant.  */
      ਵਿਅੰਜਕ.original_type = char_type_ਗੰਢ;
      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
      c_parser_consume_token (parser);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_STRING:
    ਹਾਲਤ CPP_STRING16:
    ਹਾਲਤ CPP_STRING32:
    ਹਾਲਤ CPP_WSTRING:
    ਹਾਲਤ CPP_UTF8STRING:
      ਵਿਅੰਜਕ = c_parser_string_literal (parser, parser->translate_ਲੜੀਆਂ_p,
				      ਸੱਚ);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_OBJC_STRING:
      gcc_assert (c_dialect_objc ());
      ਵਿਅੰਜਕ.ਮੁੱਲ
	= objc_build_string_object (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
      c_parser_consume_token (parser);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_NAME:
      ਚੋਣ (c_parser_peek_token (parser)->id_ਕਿਸਮ)
	{
	ਹਾਲਤ C_ID_ID:
	  {
	    ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
	    c_parser_consume_token (parser);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = build_external_ref (loc, id,
					     (c_parser_peek_token (parser)->type
					      == CPP_OPEN_PAREN),
					     &ਵਿਅੰਜਕ.original_type);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ C_ID_CLASSNAME:
	  {
	    /* Here we parse the Objective-C 2.0 Class.name dot
	       syntax.  */
	    ਰੁੱਖ class_name = c_parser_peek_token (parser)->ਮੁੱਲ;
	    ਰੁੱਖ component;
	    c_parser_consume_token (parser);
	    gcc_assert (c_dialect_objc ());
	    ਜੇ (!c_parser_require (parser, CPP_DOT, "expected %<.%>"))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    c_token *component_tok = c_parser_peek_token (parser);
	    component = component_tok->ਮੁੱਲ;
	    location_t ਸਿਰਾ_loc = component_tok->get_ਅੰਤ ();
	    c_parser_consume_token (parser);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = objc_build_class_component_ref (class_name,
							 component);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, ਸਿਰਾ_loc);
	    ਰੋਕੋ;
	  }
	ਮੂਲ:
	  c_parser_error (parser, "expected expression");
	  ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	  ਰੋਕੋ;
	}
      ਰੋਕੋ;
    ਹਾਲਤ CPP_OPEN_PAREN:
      /* A parenthesized expression, statement expression or compound
	 literal.  */
      ਜੇ (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_BRACE)
	{
	  /* A statement expression.  */
	  ਰੁੱਖ stmt;
	  location_t brace_loc;
	  ਤਾਰਕਿਕ save_c_omp_array_section_p = c_omp_array_section_p;
	  c_parser_consume_token (parser);
	  brace_loc = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  /* If we've not yet started the current function's statement list,
	     or we're in the parameter scope of an old-style function
	     declaration, statement expressions are not allowed.  */
	  ਜੇ (!building_stmt_list_p () || old_style_parameter_scope ())
	    {
	      error_at (loc, "braced-group within expression allowed "
			"only inside a function");
	      parser->error = ਸੱਚ;
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE, ਨਿਰਾ);
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	      ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	      ਰੋਕੋ;
	    }
	  c_omp_array_section_p = ਝੂਠ;
	  stmt = c_begin_stmt_ਵਿਅੰਜਕ ();
	  c_parser_compound_statement_nostart (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  pedwarn (loc, OPT_Wpedantic,
		   "ISO C forbids braced-groups within expressions");
	  ਵਿਅੰਜਕ.ਮੁੱਲ = c_ਅੰਤ_stmt_ਵਿਅੰਜਕ (brace_loc, stmt);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_loc);
	  mark_exp_read (ਵਿਅੰਜਕ.ਮੁੱਲ);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	}
      ਨਹੀਂਤਾਂ
	{
	  /* A parenthesized expression.  */
	  location_t loc_open_paren = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == MODIFY_ਵਿਅੰਜਕ)
	    suppress_warning (ਵਿਅੰਜਕ.ਮੁੱਲ, OPT_Wparentheses);
	  ਜੇ (ਵਿਅੰਜਕ.original_ਕੋਡ != C_MAYBE_CONST_ਵਿਅੰਜਕ
	      && ਵਿਅੰਜਕ.original_ਕੋਡ != SIZEOF_ਵਿਅੰਜਕ)
	    ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	  /* Remember that we saw ( ) around the sizeof.  */
	  ਜੇ (ਵਿਅੰਜਕ.original_ਕੋਡ == SIZEOF_ਵਿਅੰਜਕ)
	    ਵਿਅੰਜਕ.original_ਕੋਡ = PAREN_SIZEOF_ਵਿਅੰਜਕ;
	  /* Don't change EXPR.ORIGINAL_TYPE.  */
	  location_t loc_close_paren = c_parser_peek_token (parser)->location;
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc_open_paren, loc_close_paren);
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>", loc_open_paren);
	}
      ਰੋਕੋ;
    ਹਾਲਤ CPP_KEYWORD:
      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_FUNCTION_NAME:
	ਹਾਲਤ RID_PRETTY_FUNCTION_NAME:
	ਹਾਲਤ RID_C99_FUNCTION_NAME:
	  ਵਿਅੰਜਕ = c_parser_predefined_identifier (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_VA_ARG:
	  {
	    location_t ਸ਼ੁਰੂ_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    e1 = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	    mark_exp_read (e1.ਮੁੱਲ);
	    e1.ਮੁੱਲ = c_fully_fold (e1.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	    ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t ਸਿਰਾ_loc = c_parser_peek_token (parser)->get_ਅੰਤ ();
	    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ਜੇ (t1 == ਨਿਰਾ)
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	      }
	    ਨਹੀਂਤਾਂ
	      {
		ਰੁੱਖ type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
		ਰੁੱਖ type = groktypename (t1, &type_ਵਿਅੰਜਕ, ਨਿਰਾ);
		ਵਿਅੰਜਕ.ਮੁੱਲ = c_build_va_arg (ਸ਼ੁਰੂ_loc, e1.ਮੁੱਲ, loc,
					     type, type_ਵਿਅੰਜਕ);
		ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ_loc, ਸਿਰਾ_loc);
	      }
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_C23_VA_ਸ਼ੁਰੂ:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    e1 = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	    e1 = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (e1.get_location (), e1, ਸੱਚ, ਸੱਚ);
	    ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	      {
		location_t cloc = c_parser_peek_token (parser)->location;
		ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
		  {
		    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਰੋਕੋ;
		  }
		ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
		    && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID
		    && (c_parser_peek_2nd_token (parser)->type
			== CPP_CLOSE_PAREN))
		  {
		    ਰੁੱਖ name = c_parser_peek_token (parser)->ਮੁੱਲ;
		    location_t nloc = c_parser_peek_token (parser)->location;
		    ਰੁੱਖ decl = lookup_name (name);
		    ਰੁੱਖ ਆਖਰੀ_parm
		      = ਰੁੱਖ_ਆਖਰੀ (DECL_ARGUMENTS (current_function_decl));
		    ਜੇ (!ਆਖਰੀ_parm || decl != ਆਖਰੀ_parm)
		      warning_at (nloc, OPT_Wvarargs,
				  "optional second parameter of %<va_start%> "
				  "not last named argument");
		    ਨਹੀਂਤਾਂ ਜੇ (DECL_ਰਜਿਸਟਰ (decl))
		      warning_at (nloc, OPT_Wvarargs,
				  "undefined behavior when second parameter "
				  "of %<va_start%> is declared with "
				  "%<register%> storage");
		    c_parser_consume_token (parser);
		  }
		ਨਹੀਂਤਾਂ
		  {
		    ਬਿਨਾਨਿਸ਼ਾਨੀ nesting_ਡੂੰਘਾਈ = 0;
		    location_t sloc = c_parser_peek_token (parser)->location;
		    location_t eloc = sloc;

		    /* For va_start (ap,) the ) comes from stdarg.h.
		       Use location of , in that case, otherwise without
		       -Wsystem-headers nothing is reported.  After all,
		       the problematic token is the comma in that case.  */
		    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
		      sloc = eloc = cloc;
		    ਜਦੋਂ (ਸੱਚ)
		      {
			c_token *token = c_parser_peek_token (parser);
			ਜੇ (token->type == CPP_CLOSE_PAREN && !nesting_ਡੂੰਘਾਈ)
			  ਰੋਕੋ;

			ਜੇ (token->type == CPP_EOF)
			  ਰੋਕੋ;
			ਜੇ (token->type == CPP_OPEN_PAREN)
			  ++nesting_ਡੂੰਘਾਈ;
			ਨਹੀਂਤਾਂ ਜੇ (token->type == CPP_CLOSE_PAREN)
			  --nesting_ਡੂੰਘਾਈ;
			eloc = token->location;
			c_parser_consume_token (parser);
		      }
		    ਜੇ (sloc != eloc)
		      sloc = make_location (sloc, sloc, eloc);
		    warning_at (sloc, OPT_Wvarargs,
				"%<va_start%> macro used with additional "
				"arguments other than identifier of the "
				"last named argument");
		  }
	      }
	    parens.skip_until_ਮਿਲਿਆ_close (parser);
	    ਰੁੱਖ fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_VA_ਸ਼ੁਰੂ);
	    vec<ਰੁੱਖ, va_gc> *params;
	    vec_alloc (params, 2);
	    params->ਤੇਜ਼_ਧੱਕੋ (e1.ਮੁੱਲ);
	    params->ਤੇਜ਼_ਧੱਕੋ (integer_zero_ਗੰਢ);
	    auto_vec<location_t> arg_loc (2);
	    arg_loc.ਤੇਜ਼_ਧੱਕੋ (e1.get_location ());
	    arg_loc.ਤੇਜ਼_ਧੱਕੋ (UNKNOWN_LOCATION);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = c_build_function_call_vec (loc, arg_loc, fndecl,
						    params, ਨਿਰਾ);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc,
				     parser->ਟੋਕਨ_buf[0].get_ਅੰਤ ());
	    ਵਿਅੰਜਕ.m_decimal = 0;
	    ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	    ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	    release_ਰੁੱਖ_ਸਦਿਸ਼ (params);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_OFFSETOF:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    t1 = c_parser_type_name (parser);
	    ਜੇ (t1 == ਨਿਰਾ)
	      parser->error = ਸੱਚ;
	    ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      gcc_assert (parser->error);
	    ਜੇ (parser->error)
	      {
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ type = groktypename (t1, ਨਿਰਾ, ਨਿਰਾ);
	    ਰੁੱਖ offsetof_ref;
	    ਜੇ (type == error_mark_ਗੰਢ)
	      offsetof_ref = error_mark_ਗੰਢ;
	    ਨਹੀਂਤਾਂ
	      {
		offsetof_ref = build1 (ਅਸਿੱਧਾ_REF, type, null_ਸੂਚਕ_ਗੰਢ);
		ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (offsetof_ref, loc);
	      }
	    /* Parse the second argument to __builtin_offsetof.  We
	       must have one identifier, and beyond that we want to
	       accept sub structure and sub array references.  */
	    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		offsetof_ref
		  = build_component_ref (loc, offsetof_ref, comp_tok->ਮੁੱਲ,
					 comp_tok->location, UNKNOWN_LOCATION);
		c_parser_consume_token (parser);
		ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_DOT)
		       || c_parser_ਅਗਲਾ_token_is (parser,
						  CPP_OPEN_ਵਰਗਫਲ)
		       || c_parser_ਅਗਲਾ_token_is (parser,
						  CPP_DEREF))
		  {
		    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_DEREF))
		      {
			loc = c_parser_peek_token (parser)->location;
			offsetof_ref = build_array_ref (loc,
							offsetof_ref,
							integer_zero_ਗੰਢ);
			ਜਾਓ do_dot;
		      }
		    ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_DOT))
		      {
		      do_dot:
			c_parser_consume_token (parser);
			ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser,
							CPP_NAME))
			  {
			    c_parser_error (parser, "expected identifier");
			    ਰੋਕੋ;
			  }
			c_token *comp_tok = c_parser_peek_token (parser);
			offsetof_ref
			  = build_component_ref (loc, offsetof_ref,
						 comp_tok->ਮੁੱਲ,
						 comp_tok->location,
						 UNKNOWN_LOCATION);
			c_parser_consume_token (parser);
		      }
		    ਨਹੀਂਤਾਂ
		      {
			ਬਣਤਰ c_ਵਿਅੰਜਕ ce;
			ਰੁੱਖ idx;
			loc = c_parser_peek_token (parser)->location;
			c_parser_consume_token (parser);
			ce = c_parser_ਵਿਅੰਜਕ (parser);
			ce = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ce, ਝੂਠ, ਝੂਠ);
			idx = ce.ਮੁੱਲ;
			idx = c_fully_fold (idx, ਝੂਠ, ਨਿਰਾ);
			c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ,
						   "expected %<]%>");
			offsetof_ref = build_array_ref (loc, offsetof_ref, idx);
		      }
		  }
	      }
	    ਨਹੀਂਤਾਂ
	      c_parser_error (parser, "expected identifier");
	    location_t ਸਿਰਾ_loc = c_parser_peek_token (parser)->get_ਅੰਤ ();
	    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ਵਿਅੰਜਕ.ਮੁੱਲ = fold_offsetof (offsetof_ref);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, ਸਿਰਾ_loc);
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_ਚੁਣੋ_ਵਿਅੰਜਕ:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    c_ਵਿਅੰਜਕ_t *e1_p, *e2_p, *e3_p;
	    ਰੁੱਖ c;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser,
					    "__builtin_choose_expr",
					    &cexpr_list, ਸੱਚ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) != 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_choose_expr%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    e3_p = &(*cexpr_list)[2];

	    c = e1_p->ਮੁੱਲ;
	    mark_exp_read (e2_p->ਮੁੱਲ);
	    mark_exp_read (e3_p->ਮੁੱਲ);
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (c) != INTEGER_CST
		|| !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (c)))
	      error_at (loc,
			"first argument to %<__builtin_choose_expr%> not"
			" a constant");
	    constant_ਵਿਅੰਜਕ_warning (c);
	    ਵਿਅੰਜਕ = integer_zerop (c) ? *e3_p : *e2_p;
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_TYPES_COMPATIBLE_P:
	  {
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    t1 = c_parser_type_name (parser);
	    ਜੇ (t1 == ਨਿਰਾ)
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    t2 = c_parser_type_name (parser);
	    ਜੇ (t2 == ਨਿਰਾ)
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    location_t close_paren_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_ਮਿਲਿਆ_close (parser);
	    ਰੁੱਖ e1, e2;
	    e1 = groktypename (t1, ਨਿਰਾ, ਨਿਰਾ);
	    e2 = groktypename (t2, ਨਿਰਾ, ਨਿਰਾ);
	    ਜੇ (e1 == error_mark_ਗੰਢ || e2 == error_mark_ਗੰਢ)
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    e1 = TYPE_MAIN_VARIANT (e1);
	    e2 = TYPE_MAIN_VARIANT (e2);

	    ਵਿਅੰਜਕ.ਮੁੱਲ
	      = comptypes (e1, e2) ? integer_one_ਗੰਢ : integer_zero_ਗੰਢ;
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_BUILTIN_TGMATH:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser,
					    "__builtin_tgmath",
					    &cexpr_list, ਝੂਠ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) < 3)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
	    c_ਵਿਅੰਜਕ_t *p;
	    FOR_EACH_VEC_ELT (*cexpr_list, i, p)
	      *p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *p, ਸੱਚ, ਸੱਚ);
	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nargs = check_tgmath_function (&(*cexpr_list)[0], 1);
	    ਜੇ (nargs == 0)
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) < nargs)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਅੰਕ_functions = vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) - nargs;
	    ਜੇ (ਅੰਕ_functions < 2)
	      {
		error_at (loc, "too few arguments to %<__builtin_tgmath%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    /* The first NUM_FUNCTIONS expressions are the function
	       pointers.  The remaining NARGS expressions are the
	       arguments that are to be passed to one of those
	       functions, chosen following <tgmath.h> rules.  */
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 1; j < ਅੰਕ_functions; j++)
	      {
		ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ this_nargs
		  = check_tgmath_function (&(*cexpr_list)[j], j + 1);
		ਜੇ (this_nargs == 0)
		  {
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਜਾਓ ਬਾਹਰਲਾ;
		  }
		ਜੇ (this_nargs != nargs)
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "argument %u of %<__builtin_tgmath%> has "
			      "wrong number of arguments", j + 1);
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਜਾਓ ਬਾਹਰਲਾ;
		  }
	      }

	    /* The functions all have the same number of arguments.
	       Determine whether arguments and return types vary in
	       ways permitted for <tgmath.h> functions.  */
	    /* The first entry in each of these vectors is for the
	       return type, subsequent entries for parameter
	       types.  */
	    auto_vec<ਗਿਣਤੀ tgmath_parm_ਕਿਸਮ> parm_ਕਿਸਮ (nargs + 1);
	    auto_vec<ਰੁੱਖ> parm_ਪਹਿਲਾ (nargs + 1);
	    auto_vec<ਤਾਰਕਿਕ> parm_complex (nargs + 1);
	    auto_vec<ਤਾਰਕਿਕ> parm_varies (nargs + 1);
	    ਰੁੱਖ ਪਹਿਲਾ_type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE ((*cexpr_list)[0].ਮੁੱਲ));
	    ਰੁੱਖ ਪਹਿਲਾ_ret = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਪਹਿਲਾ_type));
	    parm_ਪਹਿਲਾ.ਤੇਜ਼_ਧੱਕੋ (ਪਹਿਲਾ_ret);
	    parm_complex.ਤੇਜ਼_ਧੱਕੋ (ਰੁੱਖ_ਕੋਡ (ਪਹਿਲਾ_ret) == COMPLEX_TYPE);
	    parm_varies.ਤੇਜ਼_ਧੱਕੋ (ਝੂਠ);
	    function_ਦਲੀਲਾਂ_iterator iter;
	    ਰੁੱਖ t;
	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ argpos;
	    FOREACH_FUNCTION_ਦਲੀਲਾਂ (ਪਹਿਲਾ_type, t, iter)
	      {
		ਜੇ (t == void_type_ਗੰਢ)
		  ਰੋਕੋ;
		parm_ਪਹਿਲਾ.ਤੇਜ਼_ਧੱਕੋ (TYPE_MAIN_VARIANT (t));
		parm_complex.ਤੇਜ਼_ਧੱਕੋ (ਰੁੱਖ_ਕੋਡ (t) == COMPLEX_TYPE);
		parm_varies.ਤੇਜ਼_ਧੱਕੋ (ਝੂਠ);
	      }
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 1; j < ਅੰਕ_functions; j++)
	      {
		ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE ((*cexpr_list)[j].ਮੁੱਲ));
		ਰੁੱਖ ret = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (type));
		ਜੇ (ret != parm_ਪਹਿਲਾ[0])
		  {
		    parm_varies[0] = ਸੱਚ;
		    ਜੇ (!SCALAR_FLOAT_TYPE_P (parm_ਪਹਿਲਾ[0])
			&& !COMPLEX_FLOAT_TYPE_P (parm_ਪਹਿਲਾ[0]))
		      {
			error_at ((*cexpr_list)[0].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  1);
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		    ਜੇ (!SCALAR_FLOAT_TYPE_P (ret)
			&& !COMPLEX_FLOAT_TYPE_P (ret))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "invalid type-generic return type for "
				  "argument %u of %<__builtin_tgmath%>",
				  j + 1);
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		  }
		ਜੇ (ਰੁੱਖ_ਕੋਡ (ret) == COMPLEX_TYPE)
		  parm_complex[0] = ਸੱਚ;
		argpos = 1;
		FOREACH_FUNCTION_ਦਲੀਲਾਂ (type, t, iter)
		  {
		    ਜੇ (t == void_type_ਗੰਢ)
		      ਰੋਕੋ;
		    t = TYPE_MAIN_VARIANT (t);
		    ਜੇ (t != parm_ਪਹਿਲਾ[argpos])
		      {
			parm_varies[argpos] = ਸੱਚ;
			ਜੇ (!SCALAR_FLOAT_TYPE_P (parm_ਪਹਿਲਾ[argpos])
			    && !COMPLEX_FLOAT_TYPE_P (parm_ਪਹਿਲਾ[argpos]))
			  {
			    error_at ((*cexpr_list)[0].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, 1);
			    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			    ਜਾਓ ਬਾਹਰਲਾ;
			  }
			ਜੇ (!SCALAR_FLOAT_TYPE_P (t)
			    && !COMPLEX_FLOAT_TYPE_P (t))
			  {
			    error_at ((*cexpr_list)[j].get_location (),
				      "invalid type-generic type for "
				      "argument %u of argument %u of "
				      "%<__builtin_tgmath%>", argpos, j + 1);
			    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			    ਜਾਓ ਬਾਹਰਲਾ;
			  }
		      }
		    ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == COMPLEX_TYPE)
		      parm_complex[argpos] = ਸੱਚ;
		    argpos++;
		  }
	      }
	    ਗਿਣਤੀ tgmath_parm_ਕਿਸਮ max_variation = tgmath_fixed;
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j <= nargs; j++)
	      {
		ਗਿਣਤੀ tgmath_parm_ਕਿਸਮ this_ਕਿਸਮ;
		ਜੇ (parm_varies[j])
		  {
		    ਜੇ (parm_complex[j])
		      max_variation = this_ਕਿਸਮ = tgmath_complex;
		    ਨਹੀਂਤਾਂ
		      {
			this_ਕਿਸਮ = tgmath_real;
			ਜੇ (max_variation != tgmath_complex)
			  max_variation = tgmath_real;
		      }
		  }
		ਨਹੀਂਤਾਂ
		  this_ਕਿਸਮ = tgmath_fixed;
		parm_ਕਿਸਮ.ਤੇਜ਼_ਧੱਕੋ (this_ਕਿਸਮ);
	      }
	    ਜੇ (max_variation == tgmath_fixed)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "all have the same type");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    /* Identify a parameter (not the return type) that varies,
	       including with complex types if any variation includes
	       complex types; there must be at least one such
	       parameter.  */
	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ tgarg = 0;
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 1; j <= nargs; j++)
	      ਜੇ (parm_ਕਿਸਮ[j] == max_variation)
		{
		  tgarg = j;
		  ਰੋਕੋ;
		}
	    ਜੇ (tgarg == 0)
	      {
		error_at (loc, "function arguments of %<__builtin_tgmath%> "
			  "lack type-generic parameter");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    /* Determine the type of the relevant parameter for each
	       function.  */
	    auto_vec<ਰੁੱਖ> tg_type (ਅੰਕ_functions);
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j < ਅੰਕ_functions; j++)
	      {
		ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE ((*cexpr_list)[j].ਮੁੱਲ));
		argpos = 1;
		FOREACH_FUNCTION_ਦਲੀਲਾਂ (type, t, iter)
		  {
		    ਜੇ (argpos == tgarg)
		      {
			tg_type.ਤੇਜ਼_ਧੱਕੋ (TYPE_MAIN_VARIANT (t));
			ਰੋਕੋ;
		      }
		    argpos++;
		  }
	      }

	    /* Verify that the corresponding types are different for
	       all the listed functions.  Also determine whether all
	       the types are complex, whether all the types are
	       standard or binary, and whether all the types are
	       decimal.  */
	    ਤਾਰਕਿਕ all_complex = ਸੱਚ;
	    ਤਾਰਕਿਕ all_ਦੁਆਧਾਰੀ = ਸੱਚ;
	    ਤਾਰਕਿਕ all_decimal = ਸੱਚ;
	    hash_ਸੈੱਟ<ਰੁੱਖ> tg_types;
	    FOR_EACH_VEC_ELT (tg_type, i, t)
	      {
		ਜੇ (ਰੁੱਖ_ਕੋਡ (t) == COMPLEX_TYPE)
		  all_decimal = ਝੂਠ;
		ਨਹੀਂਤਾਂ
		  {
		    all_complex = ਝੂਠ;
		    ਜੇ (DECIMAL_FLOAT_TYPE_P (t))
		      all_ਦੁਆਧਾਰੀ = ਝੂਠ;
		    ਨਹੀਂਤਾਂ
		      all_decimal = ਝੂਠ;
		  }
		ਜੇ (tg_types.ਜੋੜੋ (t))
		  {
		    error_at ((*cexpr_list)[i].get_location (),
			      "duplicate type-generic parameter type for "
			      "function argument %u of %<__builtin_tgmath%>",
			      i + 1);
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਜਾਓ ਬਾਹਰਲਾ;
		  }
	      }

	    /* Verify that other parameters and the return type whose
	       types vary have their types varying in the correct
	       way.  */
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j < ਅੰਕ_functions; j++)
	      {
		ਰੁੱਖ exp_type = tg_type[j];
		ਰੁੱਖ exp_real_type = exp_type;
		ਜੇ (ਰੁੱਖ_ਕੋਡ (exp_type) == COMPLEX_TYPE)
		  exp_real_type = ਰੁੱਖ_TYPE (exp_type);
		ਰੁੱਖ type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE ((*cexpr_list)[j].ਮੁੱਲ));
		ਰੁੱਖ ret = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (type));
		ਜੇ ((parm_ਕਿਸਮ[0] == tgmath_complex && ret != exp_type)
		    || (parm_ਕਿਸਮ[0] == tgmath_real && ret != exp_real_type))
		  {
		    error_at ((*cexpr_list)[j].get_location (),
			      "bad return type for function argument %u "
			      "of %<__builtin_tgmath%>", j + 1);
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਜਾਓ ਬਾਹਰਲਾ;
		  }
		argpos = 1;
		FOREACH_FUNCTION_ਦਲੀਲਾਂ (type, t, iter)
		  {
		    ਜੇ (t == void_type_ਗੰਢ)
		      ਰੋਕੋ;
		    t = TYPE_MAIN_VARIANT (t);
		    ਜੇ ((parm_ਕਿਸਮ[argpos] == tgmath_complex
			 && t != exp_type)
			|| (parm_ਕਿਸਮ[argpos] == tgmath_real
			    && t != exp_real_type))
		      {
			error_at ((*cexpr_list)[j].get_location (),
				  "bad type for argument %u of "
				  "function argument %u of "
				  "%<__builtin_tgmath%>", argpos, j + 1);
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
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
	    ਤਾਰਕਿਕ arg_complex = all_complex;
	    ਤਾਰਕਿਕ arg_ਦੁਆਧਾਰੀ = all_ਦੁਆਧਾਰੀ;
	    ਤਾਰਕਿਕ arg_int_decimal = all_decimal;
	    ਤਾਰਕਿਕ arg_int_floatnx = ਝੂਠ;
	    ਤਾਰਕਿਕ arg_int_decimalx = ਝੂਠ;
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 1; j <= nargs; j++)
	      {
		ਜੇ (parm_ਕਿਸਮ[j] == tgmath_fixed)
		  ਜਾਰੀ;
		c_ਵਿਅੰਜਕ_t *ce = &(*cexpr_list)[ਅੰਕ_functions + j - 1];
		ਰੁੱਖ type = ਰੁੱਖ_TYPE (ce->ਮੁੱਲ);
		ਜੇ (!INTEGRAL_TYPE_P (type)
		    && !SCALAR_FLOAT_TYPE_P (type)
		    && ਰੁੱਖ_ਕੋਡ (type) != COMPLEX_TYPE)
		  {
		    error_at (ce->get_location (),
			      "invalid type of argument %u of type-generic "
			      "function", j);
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਜਾਓ ਬਾਹਰਲਾ;
		  }
		ਜੇ (DECIMAL_FLOAT_TYPE_P (type))
		  {
		    arg_int_decimal = ਸੱਚ;
		    ਜੇ (all_complex)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "complex-only type-generic function", j);
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		    ਨਹੀਂਤਾਂ ਜੇ (all_ਦੁਆਧਾਰੀ)
		      {
			error_at (ce->get_location (),
				  "decimal floating-point argument %u to "
				  "binary-only type-generic function", j);
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		    ਨਹੀਂਤਾਂ ਜੇ (arg_complex)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		    ਨਹੀਂਤਾਂ ਜੇ (arg_ਦੁਆਧਾਰੀ)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		  }
		ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE)
		  {
		    arg_complex = ਸੱਚ;
		    ਜੇ (COMPLEX_FLOAT_TYPE_P (type))
		      arg_ਦੁਆਧਾਰੀ = ਸੱਚ;
		    ਜੇ (all_decimal)
		      {
			error_at (ce->get_location (),
				  "complex argument %u to "
				  "decimal-only type-generic function", j);
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		    ਨਹੀਂਤਾਂ ਜੇ (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both complex and decimal floating-point "
				  "arguments to type-generic function");
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		  }
		ਨਹੀਂਤਾਂ ਜੇ (SCALAR_FLOAT_TYPE_P (type))
		  {
		    arg_ਦੁਆਧਾਰੀ = ਸੱਚ;
		    ਜੇ (all_decimal)
		      {
			error_at (ce->get_location (),
				  "binary argument %u to "
				  "decimal-only type-generic function", j);
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		    ਨਹੀਂਤਾਂ ਜੇ (arg_int_decimal)
		      {
			error_at (ce->get_location (),
				  "both binary and decimal floating-point "
				  "arguments to type-generic function");
			ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
			ਜਾਓ ਬਾਹਰਲਾ;
		      }
		  }
		ਰੁੱਖ rtype = TYPE_MAIN_VARIANT (type);
		ਜੇ (ਰੁੱਖ_ਕੋਡ (rtype) == COMPLEX_TYPE)
		  rtype = ਰੁੱਖ_TYPE (rtype);
		ਜੇ (SCALAR_FLOAT_TYPE_P (rtype))
		  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j < ਅੰਕ_FLOATNX_TYPES; j++)
		    ਜੇ (rtype == FLOATNX_TYPE_ਗੰਢ (j))
		      {
			arg_int_floatnx = ਸੱਚ;
			ਰੋਕੋ;
		      }
		ਜੇ (rtype == dfloat64x_type_ਗੰਢ)
		  arg_int_decimalx = ਸੱਚ;
	      }
	    ਰੁੱਖ arg_real = NULL_ਰੁੱਖ;
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 1; j <= nargs; j++)
	      {
		ਜੇ (parm_ਕਿਸਮ[j] == tgmath_fixed)
		  ਜਾਰੀ;
		c_ਵਿਅੰਜਕ_t *ce = &(*cexpr_list)[ਅੰਕ_functions + j - 1];
		ਰੁੱਖ type = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ce->ਮੁੱਲ));
		ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE)
		  type = ਰੁੱਖ_TYPE (type);
		ਜੇ (INTEGRAL_TYPE_P (type))
		  type = (arg_int_decimalx
			  ? dfloat64x_type_ਗੰਢ
			  : arg_int_floatnx
			  ? float32x_type_ਗੰਢ
			  : arg_int_decimal
			  ? dfloat64_type_ਗੰਢ
			  : double_type_ਗੰਢ);
		ਜੇ (arg_real == NULL_ਰੁੱਖ)
		  arg_real = type;
		ਨਹੀਂਤਾਂ
		  arg_real = common_type (arg_real, type);
		ਜੇ (arg_real == error_mark_ਗੰਢ)
		  {
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਜਾਓ ਬਾਹਰਲਾ;
		  }
	      }
	    ਰੁੱਖ arg_type = (arg_complex
			     ? build_complex_type (arg_real)
			     : arg_real);

	    /* Look for a function to call with type-generic parameter
	       type ARG_TYPE.  */
	    c_ਵਿਅੰਜਕ_t *fn = ਨਿਰਾ;
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j < ਅੰਕ_functions; j++)
	      {
		ਜੇ (tg_type[j] == arg_type)
		  {
		    fn = &(*cexpr_list)[j];
		    ਰੋਕੋ;
		  }
	      }
	    ਜੇ (fn == ਨਿਰਾ
		&& parm_ਕਿਸਮ[0] == tgmath_fixed
		&& SCALAR_FLOAT_TYPE_P (parm_ਪਹਿਲਾ[0]))
	      {
		/* Presume this is a macro that rounds its result to a
		   narrower type, and look for the first function with
		   at least the range and precision of the argument
		   type.  */
		ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j < ਅੰਕ_functions; j++)
		  {
		    ਜੇ (arg_complex
			!= (ਰੁੱਖ_ਕੋਡ (tg_type[j]) == COMPLEX_TYPE))
		      ਜਾਰੀ;
		    ਰੁੱਖ real_tg_type = (arg_complex
					 ? ਰੁੱਖ_TYPE (tg_type[j])
					 : tg_type[j]);
		    ਜੇ (DECIMAL_FLOAT_TYPE_P (arg_real)
			!= DECIMAL_FLOAT_TYPE_P (real_tg_type))
		      ਜਾਰੀ;
		    scalar_float_ਬਹੁਲਕ arg_ਬਹੁਲਕ
		      = SCALAR_FLOAT_TYPE_ਬਹੁਲਕ (arg_real);
		    scalar_float_ਬਹੁਲਕ tg_ਬਹੁਲਕ
		      = SCALAR_FLOAT_TYPE_ਬਹੁਲਕ (real_tg_type);
		    ਅਚਲ real_format *arg_fmt = REAL_ਬਹੁਲਕ_FORMAT (arg_ਬਹੁਲਕ);
		    ਅਚਲ real_format *tg_fmt = REAL_ਬਹੁਲਕ_FORMAT (tg_ਬਹੁਲਕ);
		    ਜੇ (arg_fmt->b == tg_fmt->b
			&& arg_fmt->p <= tg_fmt->p
			&& arg_fmt->emax <= tg_fmt->emax
			&& (arg_fmt->emin - arg_fmt->p
			    >= tg_fmt->emin - tg_fmt->p))
		      {
			fn = &(*cexpr_list)[j];
			ਰੋਕੋ;
		      }
		  }
	      }
	    ਜੇ (fn == ਨਿਰਾ)
	      {
		error_at (loc, "no matching function for type-generic call");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    /* Construct a call to FN.  */
	    vec<ਰੁੱਖ, va_gc> *ਦਲੀਲਾਂ;
	    vec_alloc (ਦਲੀਲਾਂ, nargs);
	    vec<ਰੁੱਖ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j = 0; j < nargs; j++)
	      {
		c_ਵਿਅੰਜਕ_t *ce = &(*cexpr_list)[ਅੰਕ_functions + j];
		ਦਲੀਲਾਂ->ਤੇਜ਼_ਧੱਕੋ (ce->ਮੁੱਲ);
		arg_loc.ਤੇਜ਼_ਧੱਕੋ (ce->get_location ());
		origtypes->ਤੇਜ਼_ਧੱਕੋ (ce->original_type);
	      }
	    ਵਿਅੰਜਕ.ਮੁੱਲ = c_build_function_call_vec (loc, arg_loc, fn->ਮੁੱਲ,
						    ਦਲੀਲਾਂ, origtypes);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_BUILTIN_CALL_WITH_STATIC_CHAIN:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    c_ਵਿਅੰਜਕ_t *e2_p;
	    ਰੁੱਖ chain_ਮੁੱਲ;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser,
					    "__builtin_call_with_static_chain",
					    &cexpr_list, ਝੂਠ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_call_with_static_chain%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    ਵਿਅੰਜਕ = (*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];
	    *e2_p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *e2_p, ਸੱਚ, ਸੱਚ);
	    chain_ਮੁੱਲ = e2_p->ਮੁੱਲ;
	    mark_exp_read (chain_ਮੁੱਲ);

	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) != CALL_ਵਿਅੰਜਕ)
	      error_at (loc, "first argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a call expression");
	    ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (chain_ਮੁੱਲ)) != ਸੂਚਕ_TYPE)
	      error_at (loc, "second argument to "
			"%<__builtin_call_with_static_chain%> "
			"must be a pointer type");
	    ਨਹੀਂਤਾਂ
	      CALL_ਵਿਅੰਜਕ_STATIC_CHAIN (ਵਿਅੰਜਕ.ਮੁੱਲ) = chain_ਮੁੱਲ;
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_BUILTIN_COMPLEX:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    c_ਵਿਅੰਜਕ_t *e1_p, *e2_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser,
					    "__builtin_complex",
					    &cexpr_list, ਝੂਠ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) != 2)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_complex%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    e1_p = &(*cexpr_list)[0];
	    e2_p = &(*cexpr_list)[1];

	    *e1_p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *e1_p, ਸੱਚ, ਸੱਚ);
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (e1_p->ਮੁੱਲ) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	      e1_p->ਮੁੱਲ = convert (ਰੁੱਖ_TYPE (e1_p->ਮੁੱਲ),
				     ਰੁੱਖ_ਸੰਕਾਰਜ (e1_p->ਮੁੱਲ, 0));
	    *e2_p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *e2_p, ਸੱਚ, ਸੱਚ);
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (e2_p->ਮੁੱਲ) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
	      e2_p->ਮੁੱਲ = convert (ਰੁੱਖ_TYPE (e2_p->ਮੁੱਲ),
				     ਰੁੱਖ_ਸੰਕਾਰਜ (e2_p->ਮੁੱਲ, 0));
	    ਜੇ (!SCALAR_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (e1_p->ਮੁੱਲ))
		|| DECIMAL_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (e1_p->ਮੁੱਲ))
		|| !SCALAR_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (e2_p->ਮੁੱਲ))
		|| DECIMAL_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (e2_p->ਮੁੱਲ)))
	      {
		error_at (loc, "%<__builtin_complex%> operand "
			  "not of real binary floating-point type");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (e1_p->ਮੁੱਲ))
		!= TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (e2_p->ਮੁੱਲ)))
	      {
		error_at (loc,
			  "%<__builtin_complex%> operands of different types");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 does not support complex types");
	    ਵਿਅੰਜਕ.ਮੁੱਲ = build2_loc (loc, COMPLEX_ਵਿਅੰਜਕ,
				     build_complex_type
				     (TYPE_MAIN_VARIANT
				      (ਰੁੱਖ_TYPE (e1_p->ਮੁੱਲ))),
				     e1_p->ਮੁੱਲ, e2_p->ਮੁੱਲ);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_BUILTIN_COUNTED_BY_REF:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    c_ਵਿਅੰਜਕ_t *e_p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser,
					    "__builtin_counted_by_ref",
					    &cexpr_list, ਝੂਠ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_counted_by_ref%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    e_p = &(*cexpr_list)[0];
	    ਰੁੱਖ ref = e_p->ਮੁੱਲ;

	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ref)) != ARRAY_TYPE
		 && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ref)) != ਸੂਚਕ_TYPE)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be an array or pointer");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ref) != COMPONENT_REF)
	      {
		error_at (loc, "the argument to %<__builtin_counted_by_ref%>"
				" must be a field of a structure");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    /* If the ref is inside TYPEOF or ALIGNOF, the call to
	       .ACCESS_WITH_SIZE was not generated by the routine
	       build_component_ref by default, we should generate it here.  */
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ref) == COMPONENT_REF)
	      ref = handle_counted_by_for_component_ref (loc, ref);

	    ਜੇ (has_counted_by_object (ref))
	      ਵਿਅੰਜਕ.ਮੁੱਲ = get_counted_by_ref (ref);
	    ਨਹੀਂਤਾਂ
	      ਵਿਅੰਜਕ.ਮੁੱਲ = null_ਸੂਚਕ_ਗੰਢ;

	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_BUILTIN_SHUFFLE:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
	    c_ਵਿਅੰਜਕ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser,
					    "__builtin_shuffle",
					    &cexpr_list, ਝੂਠ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *p, ਸੱਚ, ਸੱਚ);

	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) == 2)
	      ਵਿਅੰਜਕ.ਮੁੱਲ = c_build_vec_perm_ਵਿਅੰਜਕ (loc, (*cexpr_list)[0].ਮੁੱਲ,
						  NULL_ਰੁੱਖ,
						  (*cexpr_list)[1].ਮੁੱਲ);

	    ਨਹੀਂਤਾਂ ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) == 3)
	      ਵਿਅੰਜਕ.ਮੁੱਲ = c_build_vec_perm_ਵਿਅੰਜਕ (loc, (*cexpr_list)[0].ਮੁੱਲ,
						  (*cexpr_list)[1].ਮੁੱਲ,
						  (*cexpr_list)[2].ਮੁੱਲ);
	    ਨਹੀਂਤਾਂ
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	      }
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_BUILTIN_SHUFFLEVECTOR:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
	    c_ਵਿਅੰਜਕ_t *p;
	    location_t close_paren_loc;

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser,
					    "__builtin_shufflevector",
					    &cexpr_list, ਝੂਠ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    FOR_EACH_VEC_ਸੁਰੱਖਿਅਤ_ELT (cexpr_list, i, p)
	      *p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *p, ਸੱਚ, ਸੱਚ);

	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) < 3)
	      {
		error_at (loc, "wrong number of arguments to "
			       "%<__builtin_shuffle%>");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	      }
	    ਨਹੀਂਤਾਂ
	      {
		auto_vec<ਰੁੱਖ, 16> ਨਕਾਬ;
		ਲਈ (i = 2; i < cexpr_list->ਲੰਮਾਈ (); ++i)
		  ਨਕਾਬ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ ((*cexpr_list)[i].ਮੁੱਲ);
		ਵਿਅੰਜਕ.ਮੁੱਲ = c_build_shufflevector (loc, (*cexpr_list)[0].ਮੁੱਲ,
						    (*cexpr_list)[1].ਮੁੱਲ,
						    ਨਕਾਬ);
	      }
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_BUILTIN_CONVERTVECTOR:
	  {
	    location_t ਸ਼ੁਰੂ_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    e1 = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	    mark_exp_read (e1.ਮੁੱਲ);
	    ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	      {
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    loc = c_parser_peek_token (parser)->location;
	    t1 = c_parser_type_name (parser);
	    location_t ਸਿਰਾ_loc = c_parser_peek_token (parser)->get_ਅੰਤ ();
	    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ਜੇ (t1 == ਨਿਰਾ)
	      ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	    ਨਹੀਂਤਾਂ
	      {
		ਰੁੱਖ type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
		ਵਿਅੰਜਕ.ਮੁੱਲ = c_build_vec_convert (ਸ਼ੁਰੂ_loc, e1.ਮੁੱਲ, loc,
						  groktypename (t1, &type_ਵਿਅੰਜਕ,
								ਨਿਰਾ));
		ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ_loc, ਸਿਰਾ_loc);
	      }
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_BUILTIN_ASSOC_BARRIER:
	  {
	    location_t ਸ਼ੁਰੂ_loc = loc;
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    e1 = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	    mark_exp_read (e1.ਮੁੱਲ);
	    location_t ਸਿਰਾ_loc = c_parser_peek_token (parser)->get_ਅੰਤ ();
	    parens.skip_until_ਮਿਲਿਆ_close (parser);
	    ਵਿਅੰਜਕ = parser_build_unary_op (loc, PAREN_ਵਿਅੰਜਕ, e1);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ_loc, ਸਿਰਾ_loc);
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_BUILTIN_STDC:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    c_ਵਿਅੰਜਕ_t *arg_p;
	    location_t close_paren_loc;
	    ਗਿਣਤੀ c_builtin_stdc {
	      C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL,
	      C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_FLOOR,
	      C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_ਚੌੜਾਈ,
	      C_BUILTIN_STDC_ਗਿਣਤੀ_ONES,
	      C_BUILTIN_STDC_ਗਿਣਤੀ_ZEROS,
	      C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ONE,
	      C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ZERO,
	      C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ONE,
	      C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ZERO,
	      C_BUILTIN_STDC_HAS_SINGLE_ਦੋਆਧਾਰੀ_ਅੰਕ,
	      C_BUILTIN_STDC_LEADING_ONES,
	      C_BUILTIN_STDC_LEADING_ZEROS,
	      C_BUILTIN_STDC_ROTATE_ਖੱਬਾ,
	      C_BUILTIN_STDC_ROTATE_ਸੱਜਾ,
	      C_BUILTIN_STDC_TRAILING_ONES,
	      C_BUILTIN_STDC_TRAILING_ZEROS,
	      C_BUILTIN_STDC_MAX
	    } stdc_rid = C_BUILTIN_STDC_MAX;
	    ਅਚਲ ਅੱਖਰ *name
	      = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੰਕ_ਦਲੀਲਾਂ = 1;
	    ਚੋਣ (name[ਆਕਾਰ ("__builtin_stdc_") - 1])
	      {
	      ਹਾਲਤ 'b':
		ਚੋਣ (name[ਆਕਾਰ ("__builtin_stdc_bit_") - 1])
		  {
		  ਹਾਲਤ 'c':
		    stdc_rid = C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL;
		    ਰੋਕੋ;
		  ਹਾਲਤ 'f':
		    stdc_rid = C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_FLOOR;
		    ਰੋਕੋ;
		  ਮੂਲ:
		    stdc_rid = C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_ਚੌੜਾਈ;
		    ਰੋਕੋ;
		  }
		ਰੋਕੋ;
	      ਹਾਲਤ 'c':
		ਜੇ (name[ਆਕਾਰ ("__builtin_stdc_count_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_ਗਿਣਤੀ_ONES;
		ਨਹੀਂਤਾਂ
		  stdc_rid = C_BUILTIN_STDC_ਗਿਣਤੀ_ZEROS;
		ਰੋਕੋ;
	      ਹਾਲਤ 'f':
		ਚੋਣ (name[ਆਕਾਰ ("__builtin_stdc_first_trailing_") - 1])
		  {
		  ਹਾਲਤ 'n':
		    stdc_rid = C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ONE;
		    ਰੋਕੋ;
		  ਹਾਲਤ 'e':
		    stdc_rid = C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ZERO;
		    ਰੋਕੋ;
		  ਹਾਲਤ 'o':
		    stdc_rid = C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ONE;
		    ਰੋਕੋ;
		  ਮੂਲ:
		    stdc_rid = C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ZERO;
		    ਰੋਕੋ;
		  }
		ਰੋਕੋ;
	      ਹਾਲਤ 'h':
		stdc_rid = C_BUILTIN_STDC_HAS_SINGLE_ਦੋਆਧਾਰੀ_ਅੰਕ;
		ਰੋਕੋ;
	      ਹਾਲਤ 'l':
		ਜੇ (name[ਆਕਾਰ ("__builtin_stdc_leading_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_LEADING_ONES;
		ਨਹੀਂਤਾਂ
		  stdc_rid = C_BUILTIN_STDC_LEADING_ZEROS;
		ਰੋਕੋ;
	      ਹਾਲਤ 'r':
		ਜੇ (name[ਆਕਾਰ ("__builtin_stdc_rotate_") - 1] == 'l')
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ਖੱਬਾ;
		ਨਹੀਂਤਾਂ
		  stdc_rid = C_BUILTIN_STDC_ROTATE_ਸੱਜਾ;
		ਅੰਕ_ਦਲੀਲਾਂ = 2;
		ਰੋਕੋ;
	      ਹਾਲਤ 't':
		ਜੇ (name[ਆਕਾਰ ("__builtin_stdc_trailing_") - 1] == 'o')
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ONES;
		ਨਹੀਂਤਾਂ
		  stdc_rid = C_BUILTIN_STDC_TRAILING_ZEROS;
		ਰੋਕੋ;
	      }
	    gcc_checking_assert (stdc_rid != C_BUILTIN_STDC_MAX);

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser, name,
					    &cexpr_list, ਝੂਠ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) != ਅੰਕ_ਦਲੀਲਾਂ)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *arg_p, ਸੱਚ, ਸੱਚ);
	    ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (arg_p->ਮੁੱਲ)))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (arg_p->ਮੁੱਲ)) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (arg_p->ਮੁੱਲ)) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (!TYPE_UNSIGNED (ਰੁੱਖ_TYPE (arg_p->ਮੁੱਲ)))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (arg_p->ਮੁੱਲ))
		== char_type_ਗੰਢ)
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has %<char%> type", name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ arg = arg_p->ਮੁੱਲ;
	    ਰੁੱਖ type = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (arg));
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
	    ਪੂਰਨ prec = TYPE_PRECISION (type);
	    ਜੇ (ਅੰਕ_ਦਲੀਲਾਂ == 2)
	      {
		/* Expand:
		   __builtin_stdc_rotate_left (arg1, arg2) as
		   arg1 r<< (arg2 % prec)
		   __builtin_stdc_rotate_right (arg1, arg2) as
		   arg1 r>> (arg2 % prec).  */
		arg_p = &(*cexpr_list)[1];
		*arg_p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *arg_p, ਸੱਚ, ਸੱਚ);
		ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (arg_p->ਮੁੱਲ)))
		  {
		    error_at (loc, "%qs operand not an integral type", name);
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਰੋਕੋ;
		  }
		ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (arg_p->ਮੁੱਲ)) == ENUMERAL_TYPE)
		  {
		    error_at (loc, "argument %u in call to function "
				   "%qs has enumerated type", 2, name);
		    ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		    ਰੋਕੋ;
		  }
		ਰੁੱਖ arg1 = save_ਵਿਅੰਜਕ (arg);
		ਰੁੱਖ arg2 = save_ਵਿਅੰਜਕ (arg_p->ਮੁੱਲ);
		ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ;
		ਜੇ (stdc_rid == C_BUILTIN_STDC_ROTATE_ਖੱਬਾ)
		  ਕੋਡ = LROTATE_ਵਿਅੰਜਕ;
		ਨਹੀਂਤਾਂ
		  ਕੋਡ = RROTATE_ਵਿਅੰਜਕ;

		ਜੇ (ਰੁੱਖ_ਕੋਡ (arg2) == INTEGER_CST
		    && ਰੁੱਖ_int_cst_sgn (arg2) < 0)
		  warning_at (loc, OPT_Wshift_ਗਿਣਤੀ_negative,
			      "rotate count is negative");

		ਰੁੱਖ instrument_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
		ਜੇ (sanitize_flags_p (SANITIZE_ਖਿਸਕਾਓ))
		  instrument_ਵਿਅੰਜਕ = ubsan_instrument_ਖਿਸਕਾਓ (loc, ਕੋਡ,
							    arg1, arg2);

		/* Promote arg2 to unsigned just so that we don't
		   need to deal with arg2 type not being able to represent
		   prec.  In the end gimplification uses unsigned int
		   for all shifts/rotates anyway.  */
		ਜੇ (TYPE_PRECISION (ਰੁੱਖ_TYPE (arg2))
		    < TYPE_PRECISION (integer_type_ਗੰਢ))
		  arg2 = fold_convert (unsigned_type_ਗੰਢ, arg2);

		ਜੇ (TYPE_UNSIGNED (ਰੁੱਖ_TYPE (arg2)))
		  arg2 = build2_loc (loc, TRUNC_MOD_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (arg2),
				     arg2, build_int_cst (ਰੁੱਖ_TYPE (arg2),
							  prec));
		ਨਹੀਂਤਾਂ
		  {
		    /* When second argument is signed, just do the modulo in
		       unsigned type, that results in better generated code
		       (for power of 2 precisions bitwise AND).  */
		    ਰੁੱਖ utype = c_common_unsigned_type (ਰੁੱਖ_TYPE (arg2));
		    arg2 = build2_loc (loc, TRUNC_MOD_ਵਿਅੰਜਕ, utype,
				       fold_convert (utype, arg2),
				       build_int_cst (utype, prec));
		  }

		/* The middle-end isn't prepared to handle {L,R}ROTATE_EXPR
		   on types without mode precision, except for large/huge
		   _BitInt types.  */
		ਜੇ (type_has_ਬਹੁਲਕ_precision_p (ਰੁੱਖ_TYPE (arg1))
		    || (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (arg1)) == BITINT_TYPE
			&& prec > MAX_FIXED_ਬਹੁਲਕ_ਮਾਪ))
		  ਵਿਅੰਜਕ.ਮੁੱਲ = build2_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (arg1), arg1,
					   arg2);
		ਨਹੀਂਤਾਂ
		  {
		    arg2 = save_ਵਿਅੰਜਕ (arg2);
		    ਰੁੱਖ t1 = build2_loc (loc, (ਕੋਡ == LROTATE_ਵਿਅੰਜਕ
						? LSHIFT_ਵਿਅੰਜਕ : RSHIFT_ਵਿਅੰਜਕ),
					  ਰੁੱਖ_TYPE (arg1), arg1, arg2);
		    ਰੁੱਖ t2 = build2_loc (loc, MINUS_ਵਿਅੰਜਕ,
					  ਰੁੱਖ_TYPE (arg2),
					  build_int_cst (ਰੁੱਖ_TYPE (arg2),
							 prec), arg2);
		    t2 = build2_loc (loc, (ਕੋਡ == LROTATE_ਵਿਅੰਜਕ
					   ? RSHIFT_ਵਿਅੰਜਕ : LSHIFT_ਵਿਅੰਜਕ),
				     ਰੁੱਖ_TYPE (arg1), arg1, t2);
		    suppress_warning (t2, OPT_Wshift_ਗਿਣਤੀ_ਉਛਾਲ);
		    ਰੁੱਖ t3 = build2_loc (loc, ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ,
					  ਰੁੱਖ_TYPE (arg1), t1, t2);
		    ਰੁੱਖ t4 = build2_loc (loc, NE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ,
					  arg2,
					  build_zero_cst (ਰੁੱਖ_TYPE (arg2)));
		    t4 = build2_loc (loc, COMPOUND_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ,
				     arg1, t4);
		    ਵਿਅੰਜਕ.ਮੁੱਲ = build3_loc (loc, COND_ਵਿਅੰਜਕ,
					     ਰੁੱਖ_TYPE (arg1), t4, t3, arg1);
		  }
		ਜੇ (instrument_ਵਿਅੰਜਕ)
		  ਵਿਅੰਜਕ.ਮੁੱਲ = build2_loc (loc, COMPOUND_ਵਿਅੰਜਕ,
					   ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ.ਮੁੱਲ),
					   instrument_ਵਿਅੰਜਕ, ਵਿਅੰਜਕ.ਮੁੱਲ);
		ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ barg1 = arg;
	    ਚੋਣ (stdc_rid)
	      {
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL:
		arg = save_ਵਿਅੰਜਕ (arg);
		barg1 = build2_loc (loc, PLUS_ਵਿਅੰਜਕ, type, arg,
				    build_int_cst (type, -1));
		ਰੋਕੋ;
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_FLOOR:
		barg1 = arg = save_ਵਿਅੰਜਕ (arg);
		ਰੋਕੋ;
	      ਹਾਲਤ C_BUILTIN_STDC_ਗਿਣਤੀ_ZEROS:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ZERO:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ZERO:
	      ਹਾਲਤ C_BUILTIN_STDC_LEADING_ONES:
	      ਹਾਲਤ C_BUILTIN_STDC_TRAILING_ONES:
		barg1 = build1_loc (loc, ਦੋਆਧਾਰੀ_ਅੰਕ_NOT_ਵਿਅੰਜਕ, type, arg);
		ਰੋਕੋ;
	      ਮੂਲ:
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ barg2 = NULL_ਰੁੱਖ;
	    ਚੋਣ (stdc_rid)
	      {
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_ਚੌੜਾਈ:
	      ਹਾਲਤ C_BUILTIN_STDC_LEADING_ONES:
	      ਹਾਲਤ C_BUILTIN_STDC_LEADING_ZEROS:
	      ਹਾਲਤ C_BUILTIN_STDC_TRAILING_ONES:
	      ਹਾਲਤ C_BUILTIN_STDC_TRAILING_ZEROS:
		barg2 = build_int_cst (integer_type_ਗੰਢ, prec);
		ਰੋਕੋ;
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ONE:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ZERO:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ONE:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ZERO:
		barg2 = integer_minus_one_ਗੰਢ;
		ਰੋਕੋ;
	      ਮੂਲ:
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ fndecl = NULL_ਰੁੱਖ;
	    ਚੋਣ (stdc_rid)
	      {
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL:
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_FLOOR:
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_ਚੌੜਾਈ:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ONE:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ZERO:
	      ਹਾਲਤ C_BUILTIN_STDC_LEADING_ONES:
	      ਹਾਲਤ C_BUILTIN_STDC_LEADING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_CLZG);
		ਰੋਕੋ;
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ONE:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ZERO:
	      ਹਾਲਤ C_BUILTIN_STDC_TRAILING_ONES:
	      ਹਾਲਤ C_BUILTIN_STDC_TRAILING_ZEROS:
		fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_CTZG);
		ਰੋਕੋ;
	      ਹਾਲਤ C_BUILTIN_STDC_ਗਿਣਤੀ_ONES:
	      ਹਾਲਤ C_BUILTIN_STDC_ਗਿਣਤੀ_ZEROS:
	      ਹਾਲਤ C_BUILTIN_STDC_HAS_SINGLE_ਦੋਆਧਾਰੀ_ਅੰਕ:
		fndecl = builtin_decl_explicit (BUILT_ਵਿੱਚ_POPCOUNTG);
		ਰੋਕੋ;
	      ਮੂਲ:
		gcc_unreachable ();
	      }
	    /* Construct a call to __builtin_{clz,ctz,popcount}g.  */
	    ਪੂਰਨ nargs = barg2 != NULL_ਰੁੱਖ ? 2 : 1;
	    vec<ਰੁੱਖ, va_gc> *ਦਲੀਲਾਂ;
	    vec_alloc (ਦਲੀਲਾਂ, nargs);
	    vec<ਰੁੱਖ, va_gc> *origtypes;
	    vec_alloc (origtypes, nargs);
	    auto_vec<location_t> arg_loc (nargs);
	    ਦਲੀਲਾਂ->ਤੇਜ਼_ਧੱਕੋ (barg1);
	    arg_loc.ਤੇਜ਼_ਧੱਕੋ (arg_p->get_location ());
	    origtypes->ਤੇਜ਼_ਧੱਕੋ (arg_p->original_type);
	    ਜੇ (nargs == 2)
	      {
		ਦਲੀਲਾਂ->ਤੇਜ਼_ਧੱਕੋ (barg2);
		arg_loc.ਤੇਜ਼_ਧੱਕੋ (loc);
		origtypes->ਤੇਜ਼_ਧੱਕੋ (integer_type_ਗੰਢ);
	      }
	    ਵਿਅੰਜਕ.ਮੁੱਲ = c_build_function_call_vec (loc, arg_loc, fndecl,
						    ਦਲੀਲਾਂ, origtypes);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
	      ਰੋਕੋ;
	    ਚੋਣ (stdc_rid)
	      {
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL:
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_FLOOR:
		--prec;
		/* FALLTHRU */
	      ਹਾਲਤ C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_ਚੌੜਾਈ:
		ਵਿਅੰਜਕ.ਮੁੱਲ = build2_loc (loc, MINUS_ਵਿਅੰਜਕ, integer_type_ਗੰਢ,
					 build_int_cst (integer_type_ਗੰਢ,
							prec), ਵਿਅੰਜਕ.ਮੁੱਲ);
		ਰੋਕੋ;
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ONE:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_LEADING_ZERO:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ONE:
	      ਹਾਲਤ C_BUILTIN_STDC_ਪਹਿਲਾ_TRAILING_ZERO:
		ਵਿਅੰਜਕ.ਮੁੱਲ = build2_loc (loc, PLUS_ਵਿਅੰਜਕ, integer_type_ਗੰਢ,
					 ਵਿਅੰਜਕ.ਮੁੱਲ, integer_one_ਗੰਢ);
		ਰੋਕੋ;
	      ਹਾਲਤ C_BUILTIN_STDC_HAS_SINGLE_ਦੋਆਧਾਰੀ_ਅੰਕ:
		ਵਿਅੰਜਕ.ਮੁੱਲ = build2_loc (loc, EQ_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ,
					 ਵਿਅੰਜਕ.ਮੁੱਲ, integer_one_ਗੰਢ);
		ਰੋਕੋ;
	      ਮੂਲ:
		ਰੋਕੋ;
	      }

	    ਜੇ (stdc_rid != C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL
		&& stdc_rid != C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_FLOOR)
	      {
		ਜੇ (stdc_rid != C_BUILTIN_STDC_HAS_SINGLE_ਦੋਆਧਾਰੀ_ਅੰਕ)
		  ਵਿਅੰਜਕ.ਮੁੱਲ = fold_convert_loc (loc, unsigned_type_ਗੰਢ,
						 ਵਿਅੰਜਕ.ਮੁੱਲ);
		ਰੋਕੋ;
	      }
	    /* For __builtin_stdc_bit_ceil (0U) or __builtin_stdc_bit_ceil (1U)
	       or __builtin_stdc_bit_floor (0U) avoid bogus -Wshift-count-*
	       warnings.  The LSHIFT_EXPR is in dead code in that case.  */
	    ਜੇ (integer_zerop (arg)
		|| (stdc_rid == C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL && integer_onep (arg)))
	      ਵਿਅੰਜਕ.ਮੁੱਲ = build_int_cst (type, 0);
	    ਨਹੀਂਤਾਂ
	      ਵਿਅੰਜਕ.ਮੁੱਲ
		= build2_loc (loc, LSHIFT_ਵਿਅੰਜਕ, type,
			      build_int_cst (type,
					     (stdc_rid
					      == C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL
					      ? 2 : 1)), ਵਿਅੰਜਕ.ਮੁੱਲ);
	    ਜੇ (stdc_rid == C_BUILTIN_STDC_ਦੋਆਧਾਰੀ_ਅੰਕ_CEIL)
	      ਵਿਅੰਜਕ.ਮੁੱਲ = build3_loc (loc, COND_ਵਿਅੰਜਕ, type,
				       build2_loc (loc, LE_ਵਿਅੰਜਕ,
						   boolean_type_ਗੰਢ, arg,
						   build_int_cst (type, 1)),
				       build_int_cst (type, 1),
				       ਵਿਅੰਜਕ.ਮੁੱਲ);
	    ਨਹੀਂਤਾਂ
	      ਵਿਅੰਜਕ.ਮੁੱਲ = build3_loc (loc, COND_ਵਿਅੰਜਕ, type,
				       build2_loc (loc, EQ_ਵਿਅੰਜਕ,
						   boolean_type_ਗੰਢ, arg,
						   build_int_cst (type, 0)),
				       build_int_cst (type, 0),
				       ਵਿਅੰਜਕ.ਮੁੱਲ);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_BUILTIN_BSWAPG:
	ਹਾਲਤ RID_BUILTIN_BITREVERSEG:
	  {
	    vec<c_ਵਿਅੰਜਕ_t, va_gc> *cexpr_list;
	    location_t close_paren_loc;
	    ਅੰਦਰੂਨੀ_fn ifn
	      = (c_parser_peek_token (parser)->keyword == RID_BUILTIN_BSWAPG
		 ? IFN_BSWAP : IFN_BITREVERSE);
	    ਅਚਲ ਅੱਖਰ *name
	      = (ifn == IFN_BSWAP ? "__builtin_bswapg"
		 : "__builtin_bitreverseg");

	    c_parser_consume_token (parser);
	    ਜੇ (!c_parser_get_builtin_ਦਲੀਲਾਂ (parser, name, &cexpr_list, ਝੂਠ,
					    &close_paren_loc))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (cexpr_list) != 1)
	      {
		error_at (loc, "wrong number of arguments to %qs", name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }

	    c_ਵਿਅੰਜਕ_t *arg_p = &(*cexpr_list)[0];
	    *arg_p = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, *arg_p, ਸੱਚ, ਸੱਚ);
	    ਰੁੱਖ arg = arg_p->ਮੁੱਲ;
	    ਜੇ (error_ਸੰਕਾਰਜ_p (arg))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ type = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (arg));
	    ਜੇ (!INTEGRAL_TYPE_P (type))
	      {
		error_at (loc, "%qs operand not an integral type", name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == ENUMERAL_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has enumerated type", 1, name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == BOOLEAN_TYPE)
	      {
		error_at (loc, "argument %u in call to function "
			  "%qs has boolean type", 1, name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (!TYPE_UNSIGNED (type))
	      {
		error_at (loc, "argument 1 in call to function "
			  "%qs has signed type", name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (ifn == IFN_BSWAP && (TYPE_PRECISION (type) % 8) != 0)
	      {
		error_at (loc, "precision %d of argument 1 to function "
			  "%qs is not a multiple of 8",
			  TYPE_PRECISION (type), name);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    arg = c_fully_fold (arg, ਝੂਠ, ਨਿਰਾ);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = fold_build_builtin_bswapg_bitreverseg (loc, ifn, arg);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_paren_loc);
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_AT_SELECTOR:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ sel = c_parser_objc_selector_arg (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_ਮਿਲਿਆ_close (parser);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = objc_build_selector_ਵਿਅੰਜਕ (loc, sel);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_loc);
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_PROTOCOL:
	  {
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	      {
		c_parser_error (parser, "expected identifier");
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
	    c_parser_consume_token (parser);
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_ਮਿਲਿਆ_close (parser);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = objc_build_protocol_ਵਿਅੰਜਕ (id);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_loc);
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_AT_ENCODE:
	  {
	    /* Extension to support C-structures in the archiver.  */
	    gcc_assert (c_dialect_objc ());
	    c_parser_consume_token (parser);
	    matching_parens parens;
	    ਜੇ (!parens.require_open (parser))
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    t1 = c_parser_type_name (parser);
	    ਜੇ (t1 == ਨਿਰਾ)
	      {
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
		ਰੋਕੋ;
	      }
	    location_t close_loc = c_parser_peek_token (parser)->location;
	    parens.skip_until_ਮਿਲਿਆ_close (parser);
	    ਰੁੱਖ type = groktypename (t1, ਨਿਰਾ, ਨਿਰਾ);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = objc_build_encode_ਵਿਅੰਜਕ (type);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_loc);
	  }
	  ਰੋਕੋ;
	ਹਾਲਤ RID_GENERIC:
	  ਵਿਅੰਜਕ = c_parser_generic_selection (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_OMP_ALL_ਸਮ੍ਰਿਤੀ:
	  gcc_assert (flag_openmp);
	  c_parser_consume_token (parser);
	  error_at (loc, "%<omp_all_memory%> may only be used in OpenMP "
			 "%<depend%> clause");
	  ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	  ਰੋਕੋ;
	/* C23 'nullptr' literal.  */
	ਹਾਲਤ RID_NULLPTR:
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ.ਮੁੱਲ = nullptr_ਗੰਢ;
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
	  pedwarn_c11 (loc, OPT_Wpedantic,
		       "ISO C does not support %qs before C23", "nullptr");
	  ਰੋਕੋ;
	ਹਾਲਤ RID_TRUE:
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ.ਮੁੱਲ = boolean_true_ਗੰਢ;
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
	  ਰੋਕੋ;
	ਹਾਲਤ RID_FALSE:
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ.ਮੁੱਲ = boolean_false_ਗੰਢ;
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
	  ਰੋਕੋ;
	ਮੂਲ:
	  c_parser_error (parser, "expected expression");
	  ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	  ਰੋਕੋ;
	}
      ਰੋਕੋ;
    ਹਾਲਤ CPP_OPEN_ਵਰਗਫਲ:
      ਜੇ (c_dialect_objc ())
	{
	  ਰੁੱਖ receiver, ਦਲੀਲਾਂ;
	  c_parser_consume_token (parser);
	  receiver = c_parser_objc_receiver (parser);
	  ਦਲੀਲਾਂ = c_parser_objc_ਸੁਨੇਹਾ_ਦਲੀਲਾਂ (parser);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ,
				     "expected %<]%>");
	  ਵਿਅੰਜਕ.ਮੁੱਲ = objc_build_ਸੁਨੇਹਾ_ਵਿਅੰਜਕ (receiver, ਦਲੀਲਾਂ);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, loc, close_loc);
	  ਰੋਕੋ;
	}
      /* Else fall through to report error.  */
      /* FALLTHRU */
    ਮੂਲ:
      c_parser_error (parser, "expected expression");
      ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
      ਰੋਕੋ;
    }
 ਬਾਹਰਲਾ:
  ਵਾਪਸ c_parser_postfix_ਵਿਅੰਜਕ_after_primary
    (parser, ਵਿਅੰਜਕ_LOC_OR_LOC (ਵਿਅੰਜਕ.ਮੁੱਲ, loc), ਵਿਅੰਜਕ);
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_postfix_ਵਿਅੰਜਕ_after_paren_type (c_parser *parser,
					      ਬਣਤਰ c_declspecs *scspecs,
					      ਬਣਤਰ c_type_name *type_name,
					      location_t type_loc)
{
  ਰੁੱਖ type;
  ਬਣਤਰ c_ਵਿਅੰਜਕ init;
  ਤਾਰਕਿਕ non_const;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  location_t ਸ਼ੁਰੂ_loc;
  ਰੁੱਖ type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ type_ਵਿਅੰਜਕ_const = ਸੱਚ;
  ਤਾਰਕਿਕ constexpr_p = scspecs ? scspecs->constexpr_p : ਝੂਠ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ underspec_state = 0;
  check_compound_literal_type (type_loc, type_name);
  rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, type_loc);
  ਸ਼ੁਰੂ_loc = c_parser_peek_token (parser)->location;
  ਜੇ (constexpr_p)
    {
      underspec_state = ਸ਼ੁਰੂ_underspecified_init (ਸ਼ੁਰੂ_loc, NULL_ਰੁੱਖ);
      /* A constexpr compound literal is subject to the constraints on
	 underspecified declarations, which may not declare tags or
	 members or structures or unions; it is undefined behavior to
	 declare the members of an enumeration.  Where the structure,
	 union or enumeration type is declared within the compound
	 literal initializer, this is diagnosed elsewhere as a result
	 of the above call to start_underspecified_init.  Diagnose
	 here the case of declaring such a type in the type specifiers
	 of the compound literal.  */
      ਚੋਣ (type_name->specs->typespec_ਕਿਸਮ)
	{
	ਹਾਲਤ ctsk_tagfirstref:
	ਹਾਲਤ ctsk_tagfirstref_attrs:
	  error_at (type_loc, "%qT declared in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ਰੋਕੋ;

	ਹਾਲਤ ctsk_tagdef:
	  error_at (type_loc, "%qT defined in %<constexpr%> compound literal",
		    type_name->specs->type);
	  ਰੋਕੋ;

	ਮੂਲ:
	  ਰੋਕੋ;
	}
    }
  ਸ਼ੁਰੂ_init (NULL_ਰੁੱਖ, ਨਿਰਾ,
	      (global_bindings_p ()
	       || (scspecs && scspecs->storage_class == csc_static)
	       || constexpr_p), constexpr_p, &richloc);
  type = groktypename (type_name, &type_ਵਿਅੰਜਕ, &type_ਵਿਅੰਜਕ_const);
  ਤਾਰਕਿਕ varsize_p = ਝੂਠ;
  ਜੇ (type != error_mark_ਗੰਢ && C_TYPE_VARIABLE_ਮਾਪ (type))
    {
      pedwarn (type_loc, OPT_Wpedantic, "compound literal has variable size");
      varsize_p = ਸੱਚ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE)
    {
      error_at (type_loc, "compound literal has function type");
      type = error_mark_ਗੰਢ;
    }
  ਜੇ (constexpr_p && type != error_mark_ਗੰਢ)
    {
      ਰੁੱਖ type_no_array = strip_array_types (type);
      /* The type of a constexpr object must not be variably modified
	 (which applies to all compound literals), volatile, atomic or
	 restrict qualified or have a member with such a qualifier.
	 const qualification is implicitly added.  */
      ਜੇ (TYPE_QUALS (type_no_array)
	  & (TYPE_QUAL_VOLATILE | TYPE_QUAL_RESTRICT | TYPE_QUAL_ATOMIC))
	error_at (type_loc, "invalid qualifiers for %<constexpr%> object");
      ਨਹੀਂਤਾਂ ਜੇ (ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type_no_array)
	       && C_TYPE_FIELDS_NON_CONSTEXPR (type_no_array))
	error_at (type_loc, "invalid qualifiers for field of "
		  "%<constexpr%> object");
      type = c_build_qualified_type (type,
				     (TYPE_QUALS (type_no_array)
				      | TYPE_QUAL_CONST));
    }
  init = c_parser_braced_init (parser, type, ਝੂਠ, ਨਿਰਾ, varsize_p);
  ਜੇ (constexpr_p)
    ਅੰਤ_underspecified_init (NULL_ਰੁੱਖ, underspec_state);
  ਅੰਤ_init ();
  maybe_warn_string_init (type_loc, type, init);

  ਜੇ (type != error_mark_ਗੰਢ
      && !ADDR_SPACE_GENERIC_P (TYPE_ADDR_SPACE (type))
      && current_function_decl)
    {
      error ("compound literal qualified by address-space qualifier");
      type = error_mark_ਗੰਢ;
    }

  ਜੇ (!pedwarn_c90 (ਸ਼ੁਰੂ_loc, OPT_Wpedantic,
		    "ISO C90 forbids compound literals") && scspecs)
    pedwarn_c11 (ਸ਼ੁਰੂ_loc, OPT_Wpedantic,
		 "ISO C forbids storage class specifiers in compound literals "
		 "before C23");
  non_const = ((init.ਮੁੱਲ && ਰੁੱਖ_ਕੋਡ (init.ਮੁੱਲ) == CONSTRUCTOR)
	       ? CONSTRUCTOR_NON_CONST (init.ਮੁੱਲ)
	       : init.original_ਕੋਡ == C_MAYBE_CONST_ਵਿਅੰਜਕ);
  non_const |= !type_ਵਿਅੰਜਕ_const;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ alignas_align = 0;
  ਜੇ (type != error_mark_ਗੰਢ
      && type_name->specs->align_log != -1)
    {
      alignas_align = 1U << type_name->specs->align_log;
      ਜੇ (alignas_align < min_align_ਦਾ_type (type))
	{
	  error_at (type_name->specs->locations[cdw_alignas],
		    "%<_Alignas%> specifiers cannot reduce "
		    "alignment of compound literal");
	  alignas_align = 0;
	}
    }
  ਵਿਅੰਜਕ.ਮੁੱਲ = build_compound_literal (ਸ਼ੁਰੂ_loc, type, init.ਮੁੱਲ, non_const,
				       alignas_align, scspecs);
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, init.src_range);
  ਵਿਅੰਜਕ.m_decimal = 0;
  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
  ਜੇ (type != error_mark_ਗੰਢ
      && ਵਿਅੰਜਕ.ਮੁੱਲ != error_mark_ਗੰਢ
      && type_ਵਿਅੰਜਕ)
    {
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == C_MAYBE_CONST_ਵਿਅੰਜਕ)
	{
	  gcc_assert (C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (ਵਿਅੰਜਕ.ਮੁੱਲ) == NULL_ਰੁੱਖ);
	  C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (ਵਿਅੰਜਕ.ਮੁੱਲ) = type_ਵਿਅੰਜਕ;
	}
      ਨਹੀਂਤਾਂ
	{
	  gcc_assert (!non_const);
	  ਵਿਅੰਜਕ.ਮੁੱਲ = build2 (C_MAYBE_CONST_ਵਿਅੰਜਕ, type,
			       type_ਵਿਅੰਜਕ, ਵਿਅੰਜਕ.ਮੁੱਲ);
	}
    }
  ਵਾਪਸ c_parser_postfix_ਵਿਅੰਜਕ_after_primary (parser, ਸ਼ੁਰੂ_loc, ਵਿਅੰਜਕ);
}

/* Callback function for sizeof_pointer_memaccess_warning to compare
   types.  */

ਸਥਿਰ ਤਾਰਕਿਕ
sizeof_ptr_memacc_comptypes (ਰੁੱਖ type1, ਰੁੱਖ type2)
{
  ਵਾਪਸ comptypes (type1, type2) == 1;
}

/* Warn for patterns where abs-like function appears to be used incorrectly,
   gracefully ignore any non-abs-like function.  The warning location should
   be LOC.  FNDECL is the declaration of called function, it must be a
   BUILT_IN_NORMAL function.  ARG is the first and only argument of the
   call.  */

ਸਥਿਰ ਖਾਲੀ
warn_for_abs (location_t loc, ਰੁੱਖ fndecl, ਰੁੱਖ arg)
{
  /* Avoid warning in unreachable subexpressions.  */
  ਜੇ (c_inhibit_evaluation_warnings)
    ਵਾਪਸ;

  ਰੁੱਖ atype = ਰੁੱਖ_TYPE (arg);

  /* Casts from pointers (and thus arrays and fndecls) will generate
     -Wint-conversion warnings.  Most other wrong types hopefully lead to type
     mismatch errors.  TODO: Think about what to do with FIXED_POINT_TYPE_P
     types and possibly other exotic types.  */
  ਜੇ (!INTEGRAL_TYPE_P (atype)
      && !SCALAR_FLOAT_TYPE_P (atype)
      && ਰੁੱਖ_ਕੋਡ (atype) != COMPLEX_TYPE)
    ਵਾਪਸ;

  ਗਿਣਤੀ built_ਵਿੱਚ_function fcode = DECL_FUNCTION_ਕੋਡ (fndecl);

  ਚੋਣ (fcode)
    {
    ਹਾਲਤ BUILT_ਵਿੱਚ_ABS:
    ਹਾਲਤ BUILT_ਵਿੱਚ_LABS:
    ਹਾਲਤ BUILT_ਵਿੱਚ_LLABS:
    ਹਾਲਤ BUILT_ਵਿੱਚ_IMAXABS:
      ਜੇ (!INTEGRAL_TYPE_P (atype))
	{
	  ਜੇ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using integer absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using integer absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  ਨਹੀਂਤਾਂ
	    gcc_unreachable ();
	  ਵਾਪਸ;
	}
      ਜੇ (TYPE_UNSIGNED (atype))
	warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
		    "taking the absolute value of unsigned type %qT "
		    "has no effect", atype);
      ਰੋਕੋ;

    CASE_FLT_FN (BUILT_ਵਿੱਚ_FABS):
    CASE_FLT_FN_FLOATN_NX (BUILT_ਵਿੱਚ_FABS):
      ਜੇ (!SCALAR_FLOAT_TYPE_P (atype)
	  || DECIMAL_FLOAT_ਬਹੁਲਕ_P (TYPE_ਬਹੁਲਕ (atype)))
	{
	  ਜੇ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using floating-point absolute value function %qD "
			"when argument is of integer type %qT", fndecl, atype);
	  ਨਹੀਂਤਾਂ ਜੇ (DECIMAL_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using floating-point absolute value function %qD "
			"when argument is of decimal floating-point type %qT",
			fndecl, atype);
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using floating-point absolute value function %qD when "
			"argument is of complex type %qT", fndecl, atype);
	  ਨਹੀਂਤਾਂ
	    gcc_unreachable ();
	  ਵਾਪਸ;
	}
      ਰੋਕੋ;

    CASE_FLT_FN (BUILT_ਵਿੱਚ_CABS):
      ਜੇ (ਰੁੱਖ_ਕੋਡ (atype) != COMPLEX_TYPE)
	{
	  ਜੇ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using complex absolute value function %qD when "
			"argument is of integer type %qT", fndecl, atype);
	  ਨਹੀਂਤਾਂ ਜੇ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using complex absolute value function %qD when "
			"argument is of floating-point type %qT",
			fndecl, atype);
	  ਨਹੀਂਤਾਂ
	    gcc_unreachable ();

	  ਵਾਪਸ;
	}
      ਰੋਕੋ;

    ਹਾਲਤ BUILT_ਵਿੱਚ_FABSD32:
    ਹਾਲਤ BUILT_ਵਿੱਚ_FABSD64:
    ਹਾਲਤ BUILT_ਵਿੱਚ_FABSD128:
    ਹਾਲਤ BUILT_ਵਿੱਚ_FABSD64_X:
      ਜੇ (!DECIMAL_FLOAT_TYPE_P (atype))
	{
	  ਜੇ (INTEGRAL_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of integer type %qT",
			fndecl, atype);
	  ਨਹੀਂਤਾਂ ਜੇ (SCALAR_FLOAT_TYPE_P (atype))
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of floating-point "
			"type %qT", fndecl, atype);
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (atype) == COMPLEX_TYPE)
	    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
			"using decimal floating-point absolute value "
			"function %qD when argument is of complex type %qT",
			fndecl, atype);
	  ਨਹੀਂਤਾਂ
	    gcc_unreachable ();
	  ਵਾਪਸ;
	}
      ਰੋਕੋ;

    ਮੂਲ:
      ਵਾਪਸ;
    }

  ਜੇ (!TYPE_ARG_TYPES (ਰੁੱਖ_TYPE (fndecl)))
    ਵਾਪਸ;

  ਰੁੱਖ ftype = ਰੁੱਖ_ਮੁੱਲ (TYPE_ARG_TYPES (ਰੁੱਖ_TYPE (fndecl)));
  ਜੇ (ਰੁੱਖ_ਕੋਡ (atype) == COMPLEX_TYPE)
    {
      gcc_assert (ਰੁੱਖ_ਕੋਡ (ftype) == COMPLEX_TYPE);
      atype = ਰੁੱਖ_TYPE (atype);
      ftype = ਰੁੱਖ_TYPE (ftype);
    }

  ਜੇ (TYPE_PRECISION (ftype) < TYPE_PRECISION (atype))
    warning_at (loc, OPT_Wabsolute_ਮੁੱਲ,
		"absolute value function %qD given an argument of type %qT "
		"but has parameter of type %qT which may cause truncation "
		"of value", fndecl, atype, ftype);
}


/* Parse a postfix expression after the initial primary or compound
   literal; that is, parse a series of postfix operators.

   EXPR_LOC is the location of the primary expression.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_postfix_ਵਿਅੰਜਕ_after_primary (c_parser *parser,
					   location_t ਵਿਅੰਜਕ_loc,
					   ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ orig_ਵਿਅੰਜਕ;
  ਰੁੱਖ ident, idx, len;
  location_t sizeof_arg_loc[6], comp_loc;
  ਰੁੱਖ sizeof_arg[6];
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ literal_zero_ਨਕਾਬ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i;
  vec<ਰੁੱਖ, va_gc> *exprlist;
  vec<ਰੁੱਖ, va_gc> *origtypes = ਨਿਰਾ;
  vec<location_t> arg_loc = vNULL;
  location_t ਸ਼ੁਰੂ;
  location_t ਅੰਤ;

  ਜਦੋਂ (ਸੱਚ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_OPEN_ਵਰਗਫਲ:
	  /* Array reference.  */
	  c_parser_consume_token (parser);
	  idx = len = NULL_ਰੁੱਖ;
	  ਜੇ (!c_omp_array_section_p
	      || c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COLON))
	    idx = c_parser_ਵਿਅੰਜਕ (parser).ਮੁੱਲ;

	  ਜੇ (c_omp_array_section_p
	      && c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	    {
	      c_parser_consume_token (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_CLOSE_ਵਰਗਫਲ))
		len = c_parser_ਵਿਅੰਜਕ (parser).ਮੁੱਲ;

	      ਵਿਅੰਜਕ.ਮੁੱਲ = build_omp_array_section (op_loc, ਵਿਅੰਜਕ.ਮੁੱਲ, idx,
						    len);
	    }
	  ਨਹੀਂਤਾਂ
	    ਵਿਅੰਜਕ.ਮੁੱਲ = build_array_ref (op_loc, ਵਿਅੰਜਕ.ਮੁੱਲ, idx);

	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ,
				     "expected %<]%>");

	  ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	  ਅੰਤ = parser->ਟੋਕਨ_buf[0].location;
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	  ਵਿਅੰਜਕ.m_decimal = 0;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_OPEN_PAREN:
	  /* Function call.  */
	  {
	    matching_parens parens;
	    parens.consume_open (parser);
	    ਲਈ (i = 0; i < 6; i++)
	      {
		sizeof_arg[i] = NULL_ਰੁੱਖ;
		sizeof_arg_loc[i] = UNKNOWN_LOCATION;
	      }
	    literal_zero_ਨਕਾਬ = 0;
	    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	      exprlist = ਨਿਰਾ;
	    ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == FUNCTION_DECL
		     && fndecl_built_ਵਿੱਚ_p (ਵਿਅੰਜਕ.ਮੁੱਲ, BUILT_ਵਿੱਚ_CLASSIFY_TYPE)
		     && c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser,
							     cla_prefer_id))
	      {
		/* __builtin_classify_type (type)  */
		c_inhibit_evaluation_warnings++;
		ਵਿੱਚ_alignof++;
		ਬਣਤਰ c_type_name *type = c_parser_type_name (parser);
		c_inhibit_evaluation_warnings--;
		ਵਿੱਚ_alignof--;
		ਬਣਤਰ c_typespec ret;
		ret.ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
		ret.spec = error_mark_ਗੰਢ;
		ret.ਵਿਅੰਜਕ_const_operands = ਝੂਠ;
		ਜੇ (type != ਨਿਰਾ)
		  ret.spec = groktypename (type, &ret.ਵਿਅੰਜਕ,
					   &ret.ਵਿਅੰਜਕ_const_operands);
		parens.skip_until_ਮਿਲਿਆ_close (parser);
		ਵਿਅੰਜਕ.ਮੁੱਲ = build_int_cst (integer_type_ਗੰਢ,
					    type_ਮੰਜ਼ਿਲ_class (ret.spec));
		ਰੋਕੋ;
	      }
	    ਨਹੀਂਤਾਂ
	      exprlist = c_parser_ਵਿਅੰਜਕ_list (parser, ਸੱਚ, ਝੂਠ, &origtypes,
					     sizeof_arg_loc, sizeof_arg,
					     &arg_loc, &literal_zero_ਨਕਾਬ);
	    parens.skip_until_ਮਿਲਿਆ_close (parser);
	  }
	  orig_ਵਿਅੰਜਕ = ਵਿਅੰਜਕ;
	  mark_exp_read (ਵਿਅੰਜਕ.ਮੁੱਲ);
	  ਜੇ (warn_sizeof_ਸੂਚਕ_memaccess)
	    sizeof_ਸੂਚਕ_memaccess_warning (sizeof_arg_loc,
					      ਵਿਅੰਜਕ.ਮੁੱਲ, exprlist,
					      sizeof_arg,
					      sizeof_ptr_memacc_comptypes);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == FUNCTION_DECL)
	    {
	      ਜੇ (fndecl_built_ਵਿੱਚ_p (ਵਿਅੰਜਕ.ਮੁੱਲ, BUILT_ਵਿੱਚ_MEMSET)
		  && vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (exprlist) == 3)
		{
		  ਰੁੱਖ arg0 = (*exprlist)[0];
		  ਰੁੱਖ arg2 = (*exprlist)[2];
		  warn_for_memset (ਵਿਅੰਜਕ_loc, arg0, arg2, literal_zero_ਨਕਾਬ);
		}
	      ਜੇ (warn_absolute_ਮੁੱਲ
		  && fndecl_built_ਵਿੱਚ_p (ਵਿਅੰਜਕ.ਮੁੱਲ, BUILT_ਵਿੱਚ_ਸਾਧਾਰਨ)
		  && vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (exprlist) == 1)
		warn_for_abs (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ.ਮੁੱਲ, (*exprlist)[0]);
	      ਜੇ (parser->omp_for_parse_state
		  && parser->omp_for_parse_state->ਵਿੱਚ_intervening_ਕੋਡ
		  && omp_runtime_api_call (ਵਿਅੰਜਕ.ਮੁੱਲ))
		{
		  error_at (ਵਿਅੰਜਕ_loc, "calls to the OpenMP runtime API are "
				      "not permitted in intervening code");
		  parser->omp_for_parse_state->fail = ਸੱਚ;
		}
	      ਜੇ (warn_calloc_transposed_ਦਲੀਲਾਂ)
		ਜੇ (ਰੁੱਖ attr = lookup_attribute ("alloc_size",
						  TYPE_ਗੁਣ
						    (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ.ਮੁੱਲ))))
		  ਜੇ (ਰੁੱਖ_ਮੁੱਲ (attr) && ਰੁੱਖ_CHAIN (ਰੁੱਖ_ਮੁੱਲ (attr)))
		    warn_for_calloc (sizeof_arg_loc, ਵਿਅੰਜਕ.ਮੁੱਲ, exprlist,
				     sizeof_arg, attr);
	    }

	  ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	  ਅੰਤ = parser->ਟੋਕਨ_buf[0].get_ਅੰਤ ();
	  ਵਿਅੰਜਕ.ਮੁੱਲ
	    = c_build_function_call_vec (ਵਿਅੰਜਕ_loc, arg_loc, ਵਿਅੰਜਕ.ਮੁੱਲ,
					 exprlist, origtypes);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	  ਵਿਅੰਜਕ.m_decimal = 0;

	  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == INTEGER_CST
	      && ਰੁੱਖ_ਕੋਡ (orig_ਵਿਅੰਜਕ.ਮੁੱਲ) == FUNCTION_DECL
	      && fndecl_built_ਵਿੱਚ_p (orig_ਵਿਅੰਜਕ.ਮੁੱਲ, BUILT_ਵਿੱਚ_CONSTANT_P))
	    ਵਿਅੰਜਕ.original_ਕੋਡ = C_MAYBE_CONST_ਵਿਅੰਜਕ;
	  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	  ਜੇ (exprlist)
	    {
	      release_ਰੁੱਖ_ਸਦਿਸ਼ (exprlist);
	      release_ਰੁੱਖ_ਸਦਿਸ਼ (origtypes);
	    }
	  arg_loc.release ();
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_DOT:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ = default_function_array_conversion (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->ਮੁੱਲ;
	      comp_loc = comp_tok->location;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_error (parser, "expected identifier");
	      ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	      ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
              ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	      ਵਾਪਸ ਵਿਅੰਜਕ;
	    }
	  ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	  ਅੰਤ = c_parser_peek_token (parser)->get_ਅੰਤ ();
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ.ਮੁੱਲ = build_component_ref (op_loc, ਵਿਅੰਜਕ.ਮੁੱਲ, ident,
					    comp_loc, UNKNOWN_LOCATION);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) != COMPONENT_REF)
	    ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	  ਨਹੀਂਤਾਂ
	    {
	      /* Remember the original type of a bitfield.  */
	      ਰੁੱਖ ਖੇਤਰ_2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ.ਮੁੱਲ, 1);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) != ਖੇਤਰ_DECL)
		ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	      ਨਹੀਂਤਾਂ
		ਵਿਅੰਜਕ.original_type = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਖੇਤਰ_2);
	    }
	  ਵਿਅੰਜਕ.m_decimal = 0;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_DEREF:
	  /* Structure element reference.  */
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਸੱਚ, ਝੂਠ);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	    {
	      c_token *comp_tok = c_parser_peek_token (parser);
	      ident = comp_tok->ਮੁੱਲ;
	      comp_loc = comp_tok->location;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_error (parser, "expected identifier");
	      ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
	      ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	      ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	      ਵਾਪਸ ਵਿਅੰਜਕ;
	    }
	  ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	  ਅੰਤ = c_parser_peek_token (parser)->get_ਅੰਤ ();
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ.ਮੁੱਲ = build_component_ref (op_loc,
					    build_ਅਸਿੱਧਾ_ref (op_loc,
								ਵਿਅੰਜਕ.ਮੁੱਲ,
								RO_ARROW),
					    ident, comp_loc,
					    ਵਿਅੰਜਕ.get_location ());
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) != COMPONENT_REF)
	    ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	  ਨਹੀਂਤਾਂ
	    {
	      /* Remember the original type of a bitfield.  */
	      ਰੁੱਖ ਖੇਤਰ_2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ.ਮੁੱਲ, 1);
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) != ਖੇਤਰ_DECL)
		ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	      ਨਹੀਂਤਾਂ
		ਵਿਅੰਜਕ.original_type = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਖੇਤਰ_2);
	    }
	  ਵਿਅੰਜਕ.m_decimal = 0;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_PLUS_PLUS:
	  /* Postincrement.  */
	  ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	  ਅੰਤ = c_parser_peek_token (parser)->get_ਅੰਤ ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (ਵਿਅੰਜਕ.ਮੁੱਲ);
	  ਵਿਅੰਜਕ = default_function_array_conversion (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ);
	  ਵਿਅੰਜਕ.ਮੁੱਲ = build_unary_op (op_loc, POSTINCREMENT_ਵਿਅੰਜਕ,
				       ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_MINUS_MINUS:
	  /* Postdecrement.  */
	  ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	  ਅੰਤ = c_parser_peek_token (parser)->get_ਅੰਤ ();
	  c_parser_consume_token (parser);
	  mark_exp_read_cond (ਵਿਅੰਜਕ.ਮੁੱਲ);
	  ਵਿਅੰਜਕ = default_function_array_conversion (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ);
	  ਵਿਅੰਜਕ.ਮੁੱਲ = build_unary_op (op_loc, POSTDECREMENT_ਵਿਅੰਜਕ,
				       ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ);
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	  ਰੋਕੋ;
	ਮੂਲ:
	  ਵਾਪਸ ਵਿਅੰਜਕ;
	}
    }
}

/* Parse an expression (C90 6.3.17, C99 6.5.17, C11 6.5.17).

   expression:
     assignment-expression
     expression , assignment-expression
*/

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_ਵਿਅੰਜਕ (c_parser *parser)
{
  location_t tloc = c_parser_peek_token (parser)->location;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (tloc, ਵਿਅੰਜਕ, ਸੱਚ, ਝੂਠ);
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    {
      ਬਣਤਰ c_ਵਿਅੰਜਕ ਅਗਲਾ;
      ਰੁੱਖ lhsval;
      location_t loc = c_parser_peek_token (parser)->location;
      location_t ਵਿਅੰਜਕ_loc;
      c_parser_consume_token (parser);
      ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      lhsval = ਵਿਅੰਜਕ.ਮੁੱਲ;
      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (lhsval) == COMPOUND_ਵਿਅੰਜਕ
	     || ਰੁੱਖ_ਕੋਡ (lhsval) == NOP_ਵਿਅੰਜਕ)
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (lhsval) == COMPOUND_ਵਿਅੰਜਕ)
	    lhsval = ਰੁੱਖ_ਸੰਕਾਰਜ (lhsval, 1);
	  ਨਹੀਂਤਾਂ
	    lhsval = ਰੁੱਖ_ਸੰਕਾਰਜ (lhsval, 0);
	}
      ਜੇ (DECL_P (lhsval) || handled_component_p (lhsval))
	mark_exp_read (lhsval);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EMBED))
	{
	  /* Users aren't interested in millions of -Wunused-value
	     warnings when using #embed inside of a comma expression,
	     and one CPP_NUMBER plus CPP_COMMA before it and one
	     CPP_COMMA plus CPP_NUMBER after it is guaranteed by
	     the preprocessor.  Thus, parse the whole CPP_EMBED just
	     as a single INTEGER_CST, the last byte in it.  */
	  c_token *embed = c_parser_peek_token (parser);
	  ਰੁੱਖ val = embed->ਮੁੱਲ;
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਆਖਰੀ = RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (val) - 1;
	  ਅਗਲਾ.ਮੁੱਲ = build_int_cst (ਰੁੱਖ_TYPE (val),
				      RAW_ਅੰਕੜੇ_UCHAR_ELT (val, ਆਖਰੀ));
	  ਅਗਲਾ.original_type = integer_type_ਗੰਢ;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ
	{
	  ਅਗਲਾ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  ਅਗਲਾ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਅਗਲਾ, ਸੱਚ, ਝੂਠ);
	}
      ਵਿਅੰਜਕ.ਮੁੱਲ = build_compound_ਵਿਅੰਜਕ (loc, ਵਿਅੰਜਕ.ਮੁੱਲ, ਅਗਲਾ.ਮੁੱਲ);
      ਵਿਅੰਜਕ.original_ਕੋਡ = COMPOUND_ਵਿਅੰਜਕ;
      ਵਿਅੰਜਕ.original_type = ਅਗਲਾ.original_type;
      ਵਿਅੰਜਕ.m_decimal = 0;
    }
  ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* Parse an expression and convert functions or arrays to pointers and
   lvalues to rvalues.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_ਵਿਅੰਜਕ_conv (c_parser *parser)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  location_t loc = c_parser_peek_token (parser)->location;
  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਸੱਚ, ਝੂਠ);
  ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* Helper function of c_parser_expr_list.  Check if IDXth (0 based)
   argument is a literal zero alone and if so, set it in literal_zero_mask.  */

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ
c_parser_check_literal_zero (c_parser *parser, ਬਿਨਾਨਿਸ਼ਾਨੀ *literal_zero_ਨਕਾਬ,
			     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ idx)
{
  ਜੇ (idx >= HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_INT)
    ਵਾਪਸ;

  c_token *tok = c_parser_peek_token (parser);
  ਚੋਣ (tok->type)
    {
    ਹਾਲਤ CPP_ਸੰਖਿਆ:
    ਹਾਲਤ CPP_CHAR:
    ਹਾਲਤ CPP_WCHAR:
    ਹਾਲਤ CPP_CHAR16:
    ਹਾਲਤ CPP_CHAR32:
    ਹਾਲਤ CPP_UTF8CHAR:
      /* If a parameter is literal zero alone, remember it
	 for -Wmemset-transposed-args warning.  */
      ਜੇ (integer_zerop (tok->ਮੁੱਲ)
	  && !ਰੁੱਖ_ਉਛਾਲ (tok->ਮੁੱਲ)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	*literal_zero_ਨਕਾਬ |= 1U << idx;
    ਮੂਲ:
      ਰੋਕੋ;
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

ਸਥਿਰ vec<ਰੁੱਖ, va_gc> *
c_parser_ਵਿਅੰਜਕ_list (c_parser *parser, ਤਾਰਕਿਕ convert_p, ਤਾਰਕਿਕ fold_p,
		    vec<ਰੁੱਖ, va_gc> **p_orig_types,
		    location_t *sizeof_arg_loc, ਰੁੱਖ *sizeof_arg,
		    vec<location_t> *locations,
		    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *literal_zero_ਨਕਾਬ)
{
  vec<ਰੁੱਖ, va_gc> *ret;
  vec<ਰੁੱਖ, va_gc> *orig_types;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ idx = 0;
  ਤਾਰਕਿਕ save_c_omp_array_section_p = c_omp_array_section_p;
  c_omp_array_section_p = ਝੂਠ;

  ret = make_ਰੁੱਖ_ਸਦਿਸ਼ ();
  ਜੇ (p_orig_types == ਨਿਰਾ)
    orig_types = ਨਿਰਾ;
  ਨਹੀਂਤਾਂ
    orig_types = make_ਰੁੱਖ_ਸਦਿਸ਼ ();

  ਜੇ (literal_zero_ਨਕਾਬ)
    c_parser_check_literal_zero (parser, literal_zero_ਨਕਾਬ, 0);
  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  ਜੇ (convert_p)
    ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ.get_location (), ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);
  ਜੇ (fold_p)
    ਵਿਅੰਜਕ.ਮੁੱਲ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
  ret->ਤੇਜ਼_ਧੱਕੋ (ਵਿਅੰਜਕ.ਮੁੱਲ);
  ਜੇ (orig_types)
    orig_types->ਤੇਜ਼_ਧੱਕੋ (ਵਿਅੰਜਕ.original_type);
  ਜੇ (locations)
    locations->ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਵਿਅੰਜਕ.get_location ());
  ਜੇ (sizeof_arg != ਨਿਰਾ
      && (ਵਿਅੰਜਕ.original_ਕੋਡ == SIZEOF_ਵਿਅੰਜਕ
	  || ਵਿਅੰਜਕ.original_ਕੋਡ == PAREN_SIZEOF_ਵਿਅੰਜਕ))
    {
      sizeof_arg[0] = c_ਆਖਰੀ_sizeof_arg;
      sizeof_arg_loc[0] = c_ਆਖਰੀ_sizeof_loc;
    }
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EMBED))
	{
	  c_token *embed = c_parser_peek_token (parser);
	  ਰੁੱਖ ਮੁੱਲ = embed->ਮੁੱਲ;
	  ਵਿਅੰਜਕ.original_ਕੋਡ = INTEGER_CST;
	  ਵਿਅੰਜਕ.original_type = integer_type_ਗੰਢ;
	  ਵਿਅੰਜਕ.ਮੁੱਲ = NULL_ਰੁੱਖ;
	  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, embed->get_range ());
	  ਵਿਅੰਜਕ.m_decimal = 0;
	  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ i = 0; i < (ਬਿਨਾਨਿਸ਼ਾਨੀ) RAW_ਅੰਕੜੇ_ਲੰਮਾਈ (ਮੁੱਲ); i++)
	    {
	      ਜੇ (literal_zero_ਨਕਾਬ
		  && idx + 1 < HOST_ਬਿੱਟ_ਪ੍ਰਤੀ_INT
		  && RAW_ਅੰਕੜੇ_ਸੂਚਕ (ਮੁੱਲ)[i] == 0)
		*literal_zero_ਨਕਾਬ |= 1U << (idx + 1);
	      ਵਿਅੰਜਕ.ਮੁੱਲ = build_int_cst (integer_type_ਗੰਢ,
					  RAW_ਅੰਕੜੇ_UCHAR_ELT (ਮੁੱਲ, i));
	      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ret, ਵਿਅੰਜਕ.ਮੁੱਲ);
	      ਜੇ (orig_types)
		vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (orig_types, ਵਿਅੰਜਕ.original_type);
	      ਜੇ (locations)
		locations->ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਵਿਅੰਜਕ.get_location ());
	      ++idx;
	    }
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}
      ਜੇ (literal_zero_ਨਕਾਬ)
	c_parser_check_literal_zero (parser, literal_zero_ਨਕਾਬ, idx + 1);
      ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਜੇ (convert_p)
	ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ.get_location (), ਵਿਅੰਜਕ, ਸੱਚ,
					 ਸੱਚ);
      ਜੇ (fold_p)
	ਵਿਅੰਜਕ.ਮੁੱਲ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ret, ਵਿਅੰਜਕ.ਮੁੱਲ);
      ਜੇ (orig_types)
	vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (orig_types, ਵਿਅੰਜਕ.original_type);
      ਜੇ (locations)
	locations->ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਵਿਅੰਜਕ.get_location ());
      ਜੇ (++idx < 6
	  && sizeof_arg != ਨਿਰਾ
	  && (ਵਿਅੰਜਕ.original_ਕੋਡ == SIZEOF_ਵਿਅੰਜਕ
	      || ਵਿਅੰਜਕ.original_ਕੋਡ == PAREN_SIZEOF_ਵਿਅੰਜਕ))
	{
	  sizeof_arg[idx] = c_ਆਖਰੀ_sizeof_arg;
	  sizeof_arg_loc[idx] = c_ਆਖਰੀ_sizeof_loc;
	}
    }
  ਜੇ (orig_types)
    *p_orig_types = orig_types;
  c_omp_array_section_p = save_c_omp_array_section_p;
  ਵਾਪਸ ret;
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

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_class_definition (c_parser *parser, ਰੁੱਖ ਗੁਣ)
{
  ਤਾਰਕਿਕ iface_p;
  ਰੁੱਖ id1;
  ਰੁੱਖ superclass;
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_INTERFACE))
    iface_p = ਸੱਚ;
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    iface_p = ਝੂਠ;
  ਨਹੀਂਤਾਂ
    gcc_unreachable ();

  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      ਵਾਪਸ;
    }
  id1 = c_parser_peek_token (parser)->ਮੁੱਲ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      /* We have a category or class extension.  */
      ਰੁੱਖ id2;
      ਰੁੱਖ proto = NULL_ਰੁੱਖ;
      matching_parens parens;
      parens.consume_open (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	{
	  ਜੇ (iface_p && c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	    {
	      /* We have a class extension.  */
	      id2 = NULL_ਰੁੱਖ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_error (parser, "expected identifier or %<)%>");
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	      ਵਾਪਸ;
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  id2 = c_parser_peek_token (parser)->ਮੁੱਲ;
	  c_parser_consume_token (parser);
	}
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਜੇ (!iface_p)
	{
	  objc_ਸ਼ੁਰੂ_category_implementation (id1, id2);
	  ਵਾਪਸ;
	}
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_ਸ਼ੁਰੂ_category_interface (id1, id2, proto, ਗੁਣ);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_ਸਿਰਾ, "expected %<@end%>");
      objc_ਅੰਤ_interface ();
      ਵਾਪਸ;
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ਵਾਪਸ;
	}
      superclass = c_parser_peek_token (parser)->ਮੁੱਲ;
      c_parser_consume_token (parser);
    }
  ਨਹੀਂਤਾਂ
    superclass = NULL_ਰੁੱਖ;
  ਜੇ (iface_p)
    {
      ਰੁੱਖ proto = NULL_ਰੁੱਖ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      objc_ਸ਼ੁਰੂ_class_interface (id1, loc1, superclass, proto, ਗੁਣ);
    }
  ਨਹੀਂਤਾਂ
    objc_ਸ਼ੁਰੂ_class_implementation (id1, superclass);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    c_parser_objc_class_instance_variables (parser);
  ਜੇ (iface_p)
    {
      objc_continue_interface ();
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_ਸਿਰਾ, "expected %<@end%>");
      objc_ਅੰਤ_interface ();
    }
  ਨਹੀਂਤਾਂ
    {
      objc_continue_implementation ();
      ਵਾਪਸ;
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

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_class_instance_variables (c_parser *parser)
{
  gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_EOF))
    {
      ਰੁੱਖ decls;
      /* Parse any stray semicolon.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
	{
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "extra semicolon");
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}
      /* Stop if at the end of the instance variables.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	{
	  c_parser_consume_token (parser);
	  ਰੋਕੋ;
	}
      /* Parse any objc-visibility-spec.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_ਨਿੱਜੀ))
	{
	  c_parser_consume_token (parser);
	  objc_ਸੈੱਟ_visibility (OBJC_IVAR_VIS_ਨਿੱਜੀ);
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_PROTECTED))
	{
	  c_parser_consume_token (parser);
	  objc_ਸੈੱਟ_visibility (OBJC_IVAR_VIS_PROTECTED);
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_ਜਨਤਕ))
	{
	  c_parser_consume_token (parser);
	  objc_ਸੈੱਟ_visibility (OBJC_IVAR_VIS_ਜਨਤਕ);
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_PACKAGE))
	{
	  c_parser_consume_token (parser);
	  objc_ਸੈੱਟ_visibility (OBJC_IVAR_VIS_PACKAGE);
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA))
	{
	  c_parser_pragma (parser, pragma_external, ਨਿਰਾ, NULL_ਰੁੱਖ);
	  ਜਾਰੀ;
	}

      /* Parse some comma-separated declarations.  */
      decls = c_parser_struct_declaration (parser, ਨਿਰਾ);
      ਜੇ (decls == ਨਿਰਾ)
	{
	  /* There is a syntax error.  We want to skip the offending
	     tokens up to the next ';' (included) or '}'
	     (excluded).  */

	  /* First, skip manually a ')' or ']'.  This is because they
	     reduce the nesting level, so c_parser_skip_until_found()
	     wouldn't be able to skip past them.  */
	  c_token *token = c_parser_peek_token (parser);
	  ਜੇ (token->type == CPP_CLOSE_PAREN || token->type == CPP_CLOSE_ਵਰਗਫਲ)
	    c_parser_consume_token (parser);

	  /* Then, do the standard skipping.  */
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);

	  /* We hopefully recovered.  Start normal parsing again.  */
	  parser->error = ਝੂਠ;
	  ਜਾਰੀ;
	}
      ਨਹੀਂਤਾਂ
	{
	  /* Comma-separated instance variables are chained together
	     in reverse order; add them one by one.  */
	  ਰੁੱਖ ivar = nreverse (decls);
	  ਲਈ (; ivar; ivar = DECL_CHAIN (ivar))
	    objc_ਜੋੜੋ_instance_variable (copy_ਗੰਢ (ivar));
	}
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
    }
}

/* Parse an objc-class-declaration.

   objc-class-declaration:
     @class identifier-list ;
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_class_declaration (c_parser *parser)
{
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_CLASS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  ਜਦੋਂ (ਸੱਚ)
    {
      ਰੁੱਖ id;
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);
	  parser->error = ਝੂਠ;
	  ਵਾਪਸ;
	}
      id = c_parser_peek_token (parser)->ਮੁੱਲ;
      objc_declare_class (id);
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* Parse an objc-alias-declaration.

   objc-alias-declaration:
     @compatibility_alias identifier identifier ;
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_alias_declaration (c_parser *parser)
{
  ਰੁੱਖ id1, id2;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_ALIAS));
  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);
      ਵਾਪਸ;
    }
  id1 = c_parser_peek_token (parser)->ਮੁੱਲ;
  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);
      ਵਾਪਸ;
    }
  id2 = c_parser_peek_token (parser)->ਮੁੱਲ;
  c_parser_consume_token (parser);
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
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

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_protocol_definition (c_parser *parser, ਰੁੱਖ ਗੁਣ)
{
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_PROTOCOL));

  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected identifier");
      ਵਾਪਸ;
    }
  ਜੇ (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
      || c_parser_peek_2nd_token (parser)->type == CPP_SEMICOLON)
    {
      /* Any identifiers, including those declared as type names, are
	 OK here.  */
      ਜਦੋਂ (ਸੱਚ)
	{
	  ਰੁੱਖ id;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      ਰੋਕੋ;
	    }
	  id = c_parser_peek_token (parser)->ਮੁੱਲ;
	  objc_declare_protocol (id, ਗੁਣ);
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ਨਹੀਂਤਾਂ
	    ਰੋਕੋ;
	}
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਰੁੱਖ proto = NULL_ਰੁੱਖ;
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_LESS))
	proto = c_parser_objc_protocol_refs (parser);
      parser->objc_pq_context = ਸੱਚ;
      objc_ਸ਼ੁਰੂ_protocol (id, proto, ਗੁਣ);
      c_parser_objc_methodprotolist (parser);
      c_parser_require_keyword (parser, RID_AT_ਸਿਰਾ, "expected %<@end%>");
      parser->objc_pq_context = ਝੂਠ;
      objc_ਅੰਤ_interface ();
    }
}

/* Parse an objc-method-type.

   objc-method-type:
     +
     -

   Return true if it is a class method (+) and false if it is
   an instance method (-).
*/
ਸਥਿਰ ਸਤਰਅੰਦਰ ਤਾਰਕਿਕ
c_parser_objc_ਵਿਧੀ_type (c_parser *parser)
{
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_PLUS:
      c_parser_consume_token (parser);
      ਵਾਪਸ ਸੱਚ;
    ਹਾਲਤ CPP_MINUS:
      c_parser_consume_token (parser);
      ਵਾਪਸ ਝੂਠ;
    ਮੂਲ:
      gcc_unreachable ();
    }
}

/* Parse an objc-method-definition.

   objc-method-definition:
     objc-method-type objc-method-decl ;[opt] compound-statement
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_ਵਿਧੀ_definition (c_parser *parser)
{
  ਤਾਰਕਿਕ is_class_ਵਿਧੀ = c_parser_objc_ਵਿਧੀ_type (parser);
  ਰੁੱਖ decl, ਗੁਣ = NULL_ਰੁੱਖ, ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  parser->objc_pq_context = ਸੱਚ;
  decl = c_parser_objc_ਵਿਧੀ_decl (parser, is_class_ਵਿਧੀ, &ਗੁਣ,
				    &ਵਿਅੰਜਕ);
  ਜੇ (decl == error_mark_ਗੰਢ)
    ਵਾਪਸ;  /* Bail here. */

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
	       "extra semicolon in method definition specified");
    }

  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    {
      c_parser_error (parser, "expected %<{%>");
      ਵਾਪਸ;
    }

  parser->objc_pq_context = ਝੂਠ;
  ਜੇ (objc_ਸ਼ੁਰੂ_ਵਿਧੀ_definition (is_class_ਵਿਧੀ, decl, ਗੁਣ, ਵਿਅੰਜਕ))
    {
      ਜੋੜੋ_stmt (c_parser_compound_statement (parser));
      objc_ਅੰਤ_ਵਿਧੀ_definition (current_function_decl);
    }
  ਨਹੀਂਤਾਂ
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
ਖਾਲੀ_ਥਾਵਾਂ
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

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_methodprotolist (c_parser *parser)
{
  ਜਦੋਂ (ਸੱਚ)
    {
      /* The list is terminated by @end.  */
      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_SEMICOLON:
	  pedwarn (c_parser_peek_token (parser)->location, OPT_Wpedantic,
		   "ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_PLUS:
	ਹਾਲਤ CPP_MINUS:
	  c_parser_objc_methodproto (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external, ਨਿਰਾ, NULL_ਰੁੱਖ);
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_EOF:
	  ਵਾਪਸ;
	ਮੂਲ:
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_ਸਿਰਾ))
	    ਵਾਪਸ;
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_PROPERTY))
	    c_parser_objc_at_property_declaration (parser);
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_OPTIONAL))
	    {
	      objc_ਸੈੱਟ_ਵਿਧੀ_opt (ਸੱਚ);
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_REQUIRED))
	    {
	      objc_ਸੈੱਟ_ਵਿਧੀ_opt (ਝੂਠ);
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ
	    c_parser_declaration_or_fndef (parser, ਝੂਠ, ਝੂਠ, ਸੱਚ,
					   ਝੂਠ, ਸੱਚ, ਝੂਠ);
	  ਰੋਕੋ;
	}
    }
}

/* Parse an objc-methodproto.

   objc-methodproto:
     objc-method-type objc-method-decl ;
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_methodproto (c_parser *parser)
{
  ਤਾਰਕਿਕ is_class_ਵਿਧੀ = c_parser_objc_ਵਿਧੀ_type (parser);
  ਰੁੱਖ decl, ਗੁਣ = NULL_ਰੁੱਖ;

  /* Remember protocol qualifiers in prototypes.  */
  parser->objc_pq_context = ਸੱਚ;
  decl = c_parser_objc_ਵਿਧੀ_decl (parser, is_class_ਵਿਧੀ, &ਗੁਣ,
				    ਨਿਰਾ);
  /* Forget protocol qualifiers now.  */
  parser->objc_pq_context = ਝੂਠ;

  /* Do not allow the presence of attributes to hide an erroneous
     method implementation in the interface section.  */
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ਵਾਪਸ;
    }

  ਜੇ (decl != error_mark_ਗੰਢ)
    objc_ਜੋੜੋ_ਵਿਧੀ_declaration (is_class_ਵਿਧੀ, decl, ਗੁਣ);

  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
}

/* If we are at a position that method attributes may be present, check that
   there are not any parsed already (a syntax error) and then collect any
   specified at the current location.  Finally, if new attributes were present,
   check that the next token is legal ( ';' for decls and '{' for defs).  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_objc_maybe_ਵਿਧੀ_ਗੁਣ (c_parser* parser, ਰੁੱਖ* ਗੁਣ)
{
  ਤਾਰਕਿਕ bad = ਝੂਠ;
  ਜੇ (*ਗੁਣ)
    {
      c_parser_error (parser,
		    "method attributes must be specified at the end only");
      *ਗੁਣ = NULL_ਰੁੱਖ;
      bad = ਸੱਚ;
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
    *ਗੁਣ = c_parser_gnu_ਗੁਣ (parser);

  /* If there were no attributes here, just report any earlier error.  */
  ਜੇ (*ਗੁਣ == NULL_ਰੁੱਖ || bad)
    ਵਾਪਸ bad;

  /* If the attributes are followed by a ; or {, then just report any earlier
     error.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)
      || c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    ਵਾਪਸ bad;

  /* We've got attributes, but not at the end.  */
  c_parser_error (parser,
		  "expected %<;%> or %<{%> after method attribute definition");
  ਵਾਪਸ ਸੱਚ;
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
ਖਾਲੀ_ਥਾਵਾਂ
     objc-opt-parms , parameter-declaration

   objc-optellipsis:
ਖਾਲੀ_ਥਾਵਾਂ
     , ...
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_objc_ਵਿਧੀ_decl (c_parser *parser, ਤਾਰਕਿਕ is_class_ਵਿਧੀ,
			   ਰੁੱਖ *ਗੁਣ, ਰੁੱਖ *ਵਿਅੰਜਕ)
{
  ਰੁੱਖ type = NULL_ਰੁੱਖ;
  ਰੁੱਖ sel;
  ਰੁੱਖ parms = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ ellipsis = ਝੂਠ;
  ਤਾਰਕਿਕ attr_err = ਝੂਠ;

  *ਗੁਣ = NULL_ਰੁੱਖ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      type = c_parser_objc_type_name (parser);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  sel = c_parser_objc_selector (parser);
  /* If there is no selector, or a colon follows, we have an
     objc-keyword-selector.  If there is a selector, and a colon does
     not follow, that selector ends the objc-method-decl.  */
  ਜੇ (!sel || c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
    {
      ਰੁੱਖ tsel = sel;
      ਰੁੱਖ list = NULL_ਰੁੱਖ;
      ਜਦੋਂ (ਸੱਚ)
	{
	  ਰੁੱਖ atype = NULL_ਰੁੱਖ, id, keyworddecl;
	  ਰੁੱਖ param_attr = NULL_ਰੁੱਖ;
	  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ਰੋਕੋ;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* New ObjC allows attributes on method parameters.  */
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
	    param_attr = c_parser_gnu_ਗੁਣ (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
	  id = c_parser_peek_token (parser)->ਮੁੱਲ;
	  c_parser_consume_token (parser);
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, param_attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  ਜੇ (!tsel && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COLON))
	    ਰੋਕੋ;
	}

      attr_err |= c_parser_objc_maybe_ਵਿਧੀ_ਗੁਣ (parser, ਗੁਣ) ;

      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_ਗੰਢ (ਰੁੱਖ_LIST);
      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	{
	  ਬਣਤਰ c_parm *parm;
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = ਸੱਚ;
	      c_parser_consume_token (parser);
	      attr_err |= c_parser_objc_maybe_ਵਿਧੀ_ਗੁਣ
						(parser, ਗੁਣ) ;
	      ਰੋਕੋ;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_ਰੁੱਖ, ਝੂਠ);
	  ਜੇ (parm == ਨਿਰਾ)
	    ਰੋਕੋ;
	  parms = chainon (parms,
			   build_ਰੁੱਖ_list (NULL_ਰੁੱਖ, grokparm (parm, ਵਿਅੰਜਕ)));
	}
      sel = list;
    }
  ਨਹੀਂਤਾਂ
    attr_err |= c_parser_objc_maybe_ਵਿਧੀ_ਗੁਣ (parser, ਗੁਣ) ;

  ਜੇ (sel == ਨਿਰਾ)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (attr_err)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਵਾਪਸ objc_build_ਵਿਧੀ_signature (is_class_ਵਿਧੀ, type, sel, parms, ellipsis);
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

ਸਥਿਰ ਰੁੱਖ
c_parser_objc_type_name (c_parser *parser)
{
  ਰੁੱਖ quals = NULL_ਰੁੱਖ;
  ਬਣਤਰ c_type_name *type_name = ਨਿਰਾ;
  ਰੁੱਖ type = NULL_ਰੁੱਖ;
  ਜਦੋਂ (ਸੱਚ)
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ (token->type == CPP_KEYWORD
	  && (token->keyword == RID_ਵਿੱਚ
	      || token->keyword == RID_ਬਾਹਰਲਾ
	      || token->keyword == RID_INOUT
	      || token->keyword == RID_BYCOPY
	      || token->keyword == RID_BYREF
	      || token->keyword == RID_ONEWAY))
	{
	  quals = chainon (build_ਰੁੱਖ_list (NULL_ਰੁੱਖ, token->ਮੁੱਲ), quals);
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, cla_prefer_type))
    type_name = c_parser_type_name (parser);
  ਜੇ (type_name)
    type = groktypename (type_name, ਨਿਰਾ, ਨਿਰਾ);

  /* If the type is unknown, and error has already been produced and
     we need to recover from the error.  In that case, use NULL_TREE
     for the type, as if no type had been specified; this will use the
     default type ('id') which is good for error recovery.  */
  ਜੇ (type == error_mark_ਗੰਢ)
    type = NULL_ਰੁੱਖ;

  ਵਾਪਸ build_ਰੁੱਖ_list (quals, type);
}

/* Parse objc-protocol-refs.

   objc-protocol-refs:
     < identifier-list >
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_objc_protocol_refs (c_parser *parser)
{
  ਰੁੱਖ list = NULL_ਰੁੱਖ;
  gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_LESS));
  c_parser_consume_token (parser);
  /* Any identifiers, including those declared as type names, are OK
     here.  */
  ਜਦੋਂ (ਸੱਚ)
    {
      ਰੁੱਖ id;
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ਰੋਕੋ;
	}
      id = c_parser_peek_token (parser)->ਮੁੱਲ;
      list = chainon (list, build_ਰੁੱਖ_list (NULL_ਰੁੱਖ, id));
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  c_parser_require (parser, CPP_GREATER, "expected %<>%>");
  ਵਾਪਸ list;
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

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_try_catch_finally_statement (c_parser *parser)
{
  location_t location;
  ਰੁੱਖ stmt;

  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  location = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (location);
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (location, stmt);

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_CATCH))
    {
      ਬਣਤਰ c_parm *parm;
      ਰੁੱਖ parameter_declaration = error_mark_ਗੰਢ;
      ਤਾਰਕਿਕ ਵੇਖਿਆ_open_paren = ਝੂਠ;

      c_parser_consume_token (parser);
      matching_parens parens;
      ਜੇ (!parens.require_open (parser))
	ਵੇਖਿਆ_open_paren = ਸੱਚ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_ELLIPSIS))
	{
	  /* We have "@catch (...)" (where the '...' are literally
	     what is in the code).  Skip the '...'.
	     parameter_declaration is set to NULL_TREE, and
	     objc_being_catch_clauses() knows that that means
	     '...'.  */
	  c_parser_consume_token (parser);
	  parameter_declaration = NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ
	{
	  /* We have "@catch (NSException *exception)" or something
	     like that.  Parse the parameter declaration.  */
	  parm = c_parser_parameter_declaration (parser, NULL_ਰੁੱਖ, ਝੂਠ);
	  ਜੇ (parm == ਨਿਰਾ)
	    parameter_declaration = error_mark_ਗੰਢ;
	  ਨਹੀਂਤਾਂ
	    parameter_declaration = grokparm (parm, ਨਿਰਾ);
	}
      ਜੇ (ਵੇਖਿਆ_open_paren)
	parens.require_close (parser);
      ਨਹੀਂਤਾਂ
	{
	  /* If there was no open parenthesis, we are recovering from
	     an error, and we are trying to figure out what mistake
	     the user has made.  */

	  /* If there is an immediate closing parenthesis, the user
	     probably forgot the opening one (ie, they typed "@catch
	     NSException *e)".  Parse the closing parenthesis and keep
	     going.  */
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);

	  /* If these is no immediate closing parenthesis, the user
	     probably doesn't know that parenthesis are required at
	     all (ie, they typed "@catch NSException *e").  So, just
	     forget about the closing parenthesis and keep going.  */
	}
      objc_begin_catch_clause (parameter_declaration);
      ਜੇ (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_ਅੰਤ_catch_clause ();
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_FINALLY))
    {
      c_parser_consume_token (parser);
      location = c_parser_peek_token (parser)->location;
      stmt = c_parser_compound_statement (parser);
      objc_build_finally_clause (location, stmt);
    }
  objc_ਅੰਤ_try_stmt ();
}

/* Parse an objc-synchronized-statement.

   objc-synchronized-statement:
     @synchronized ( expression ) compound-statement
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_objc_synchronized_statement (c_parser *parser)
{
  location_t loc;
  ਰੁੱਖ ਵਿਅੰਜਕ, stmt;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_SYNCHRONIZED));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  objc_maybe_warn_exceptions (loc);
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      ਬਣਤਰ c_ਵਿਅੰਜਕ ce = c_parser_ਵਿਅੰਜਕ (parser);
      ce = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ce, ਝੂਠ, ਝੂਠ);
      ਵਿਅੰਜਕ = ce.ਮੁੱਲ;
      ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ, ਝੂਠ, ਨਿਰਾ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਨਹੀਂਤਾਂ
    ਵਿਅੰਜਕ = error_mark_ਗੰਢ;
  stmt = c_parser_compound_statement (parser);
  objc_build_synchronized (loc, ਵਿਅੰਜਕ, stmt);
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

ਸਥਿਰ ਰੁੱਖ
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  ਰੁੱਖ ਮੁੱਲ = token->ਮੁੱਲ;
  ਜੇ (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      ਵਾਪਸ ਮੁੱਲ;
    }
  ਜੇ (token->type != CPP_KEYWORD)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਚੋਣ (token->keyword)
    {
    ਹਾਲਤ RID_ENUM:
    ਹਾਲਤ RID_STRUCT:
    ਹਾਲਤ RID_UNION:
    ਹਾਲਤ RID_IF:
    ਹਾਲਤ RID_ELSE:
    ਹਾਲਤ RID_WHILE:
    ਹਾਲਤ RID_DO:
    ਹਾਲਤ RID_FOR:
    ਹਾਲਤ RID_SWITCH:
    ਹਾਲਤ RID_CASE:
    ਹਾਲਤ RID_DEFAULT:
    ਹਾਲਤ RID_BREAK:
    ਹਾਲਤ RID_CONTINUE:
    ਹਾਲਤ RID_RETURN:
    ਹਾਲਤ RID_GOTO:
    ਹਾਲਤ RID_ASM:
    ਹਾਲਤ RID_SIZEOF:
    ਹਾਲਤ RID_TYPEOF:
    ਹਾਲਤ RID_TYPEOF_UNQUAL:
    ਹਾਲਤ RID_ALIGNOF:
    ਹਾਲਤ RID_UNSIGNED:
    ਹਾਲਤ RID_LONG:
    ਹਾਲਤ RID_CONST:
    ਹਾਲਤ RID_SHORT:
    ਹਾਲਤ RID_VOLATILE:
    ਹਾਲਤ RID_SIGNED:
    ਹਾਲਤ RID_RESTRICT:
    ਹਾਲਤ RID_COMPLEX:
    ਹਾਲਤ RID_ਵਿੱਚ:
    ਹਾਲਤ RID_ਬਾਹਰਲਾ:
    ਹਾਲਤ RID_INOUT:
    ਹਾਲਤ RID_BYCOPY:
    ਹਾਲਤ RID_BYREF:
    ਹਾਲਤ RID_ONEWAY:
    ਹਾਲਤ RID_INT:
    ਹਾਲਤ RID_CHAR:
    ਹਾਲਤ RID_FLOAT:
    ਹਾਲਤ RID_DOUBLE:
    CASE_RID_FLOATN_NX:
    ਹਾਲਤ RID_VOID:
    ਹਾਲਤ RID_BOOL:
    ਹਾਲਤ RID_ATOMIC:
    ਹਾਲਤ RID_AUTO_TYPE:
    ਹਾਲਤ RID_INT_N_0:
    ਹਾਲਤ RID_INT_N_1:
    ਹਾਲਤ RID_INT_N_2:
    ਹਾਲਤ RID_INT_N_3:
      c_parser_consume_token (parser);
      ਵਾਪਸ ਮੁੱਲ;
    ਮੂਲ:
      ਵਾਪਸ NULL_ਰੁੱਖ;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_objc_selector_arg (c_parser *parser)
{
  ਰੁੱਖ sel = c_parser_objc_selector (parser);
  ਰੁੱਖ list = NULL_ਰੁੱਖ;
  ਜੇ (sel
      && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COLON)
      && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_SCOPE))
    ਵਾਪਸ sel;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SCOPE))
	{
	  c_parser_consume_token (parser);
	  list = chainon (list, build_ਰੁੱਖ_list (sel, NULL_ਰੁੱਖ));
	  list = chainon (list, build_ਰੁੱਖ_list (NULL_ਰੁੱਖ, NULL_ਰੁੱਖ));
	}
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ਵਾਪਸ list;
	  list = chainon (list, build_ਰੁੱਖ_list (sel, NULL_ਰੁੱਖ));
	}
      sel = c_parser_objc_selector (parser);
      ਜੇ (!sel
	  && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COLON)
	  && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_SCOPE))
	ਰੋਕੋ;
    }
  ਵਾਪਸ list;
}

/* Parse an objc-receiver.

   objc-receiver:
ਵਿਅੰਜਕ
     class-name
     type-name
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_objc_receiver (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  ਜੇ (c_parser_peek_token (parser)->type == CPP_NAME
      && (c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_TYPENAME
	  || c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_CLASSNAME))
    {
      ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
      c_parser_consume_token (parser);
      ਵਾਪਸ objc_get_class_reference (id);
    }
  ਬਣਤਰ c_ਵਿਅੰਜਕ ce = c_parser_ਵਿਅੰਜਕ (parser);
  ce = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ce, ਝੂਠ, ਝੂਠ);
  ਵਾਪਸ c_fully_fold (ce.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
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

ਸਥਿਰ ਰੁੱਖ
c_parser_objc_ਸੁਨੇਹਾ_ਦਲੀਲਾਂ (c_parser *parser)
{
  ਰੁੱਖ sel = c_parser_objc_selector (parser);
  ਰੁੱਖ list = NULL_ਰੁੱਖ;
  ਜੇ (sel && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COLON))
    ਵਾਪਸ sel;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਰੁੱਖ keywordexpr;
      ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ਵਾਪਸ error_mark_ਗੰਢ;
      keywordexpr = c_parser_objc_keywordexpr (parser);
      list = chainon (list, build_ਰੁੱਖ_list (sel, keywordexpr));
      sel = c_parser_objc_selector (parser);
      ਜੇ (!sel && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COLON))
	ਰੋਕੋ;
    }
  ਵਾਪਸ list;
}

/* Parse an objc-keywordexpr.

   objc-keywordexpr:
     nonempty-expr-list
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_objc_keywordexpr (c_parser *parser)
{
  ਰੁੱਖ ret;
  vec<ਰੁੱਖ, va_gc> *ਵਿਅੰਜਕ_list = c_parser_ਵਿਅੰਜਕ_list (parser, ਸੱਚ, ਸੱਚ,
						ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
  ਜੇ (vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (ਵਿਅੰਜਕ_list) == 1)
    {
      /* Just return the expression, remove a level of
	 indirection.  */
      ret = (*ਵਿਅੰਜਕ_list)[0];
    }
  ਨਹੀਂਤਾਂ
    {
      /* We have a comma expression, we will collapse later.  */
      ret = build_ਰੁੱਖ_list_vec (ਵਿਅੰਜਕ_list);
    }
  release_ਰੁੱਖ_ਸਦਿਸ਼ (ਵਿਅੰਜਕ_list);
  ਵਾਪਸ ret;
}

/* A check, needed in several places, that ObjC interface, implementation or
   method definitions are not prefixed by incorrect items.  */
ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_objc_diagnose_bad_element_ਅਗੇਤਰ (c_parser *parser,
					   ਬਣਤਰ c_declspecs *specs)
{
  ਜੇ (!specs->declspecs_ਵੇਖਿਆ_p || specs->non_sc_ਵੇਖਿਆ_p
      || specs->typespec_ਕਿਸਮ != ctsk_none)
    {
      c_parser_error (parser,
      		      "no type or storage class may be specified here,");
      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
      ਵਾਪਸ ਸੱਚ;
    }
  ਵਾਪਸ ਝੂਠ;
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
ਸਥਿਰ ਖਾਲੀ
c_parser_objc_at_property_declaration (c_parser *parser)
{
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_PROPERTY));
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);  /* Eat '@property'.  */

  /* Parse the optional attribute list.

     A list of parsed, but not verified, attributes.  */
  vec<property_attribute_info *> prop_attr_list = vNULL;

  ਤਾਰਕਿਕ syntax_error = ਝੂਠ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;

      location_t attr_ਸ਼ੁਰੂ = c_parser_peek_token (parser)->location;
      /* Eat the '(' */
      parens.consume_open (parser);

      /* Property attribute keywords are valid now.  */
      parser->objc_property_attr_context = ਸੱਚ;

      /* Allow @property (), with a warning.  */
      location_t attr_ਸਿਰਾ = c_parser_peek_token (parser)->location;

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	{
	  location_t attr_comb = make_location (attr_ਸਿਰਾ, attr_ਸ਼ੁਰੂ, attr_ਸਿਰਾ);
	  warning_at (attr_comb, OPT_Wattributes,
		      "empty property attribute list");
	}
      ਨਹੀਂਤਾਂ
	ਜਦੋਂ (ਸੱਚ)
	  {
	    c_token *token = c_parser_peek_token (parser);
	    attr_ਸ਼ੁਰੂ = token->location;
	    attr_ਸਿਰਾ = get_ਅੰਤ (token->location);
	    location_t attr_comb = make_location (attr_ਸ਼ੁਰੂ, attr_ਸ਼ੁਰੂ,
						  attr_ਸਿਰਾ);

	    ਜੇ (token->type == CPP_CLOSE_PAREN || token->type == CPP_COMMA)
	      {
		warning_at (attr_comb, OPT_Wattributes,
			    "missing property attribute");
		ਜੇ (token->type == CPP_CLOSE_PAREN)
		  ਰੋਕੋ;
		c_parser_consume_token (parser);
		ਜਾਰੀ;
	      }

	    ਰੁੱਖ attr_name = NULL_ਰੁੱਖ;
	    ਗਿਣਤੀ rid keyword = RID_MAX; /* Not a valid property attribute.  */
	    ਤਾਰਕਿਕ ਜੋੜੋ_at = ਝੂਠ;
	    ਜੇ (token->type == CPP_KEYWORD)
	      {
		keyword = token->keyword;
		ਜੇ (OBJC_IS_AT_KEYWORD (keyword))
		  {
		    /* For '@' keywords the token value has the keyword,
		       prepend the '@' for diagnostics.  */
		    attr_name = token->ਮੁੱਲ;
		    ਜੋੜੋ_at = ਸੱਚ;
		  }
		ਨਹੀਂਤਾਂ
		  attr_name = ridpointers[(ਪੂਰਨ)keyword];
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (token->type == CPP_NAME)
	      attr_name = token->ਮੁੱਲ;
	    c_parser_consume_token (parser);

	    ਗਿਣਤੀ objc_property_attribute_ਕਿਸਮ prop_ਕਿਸਮ
	      = objc_prop_attr_ਕਿਸਮ_for_rid (keyword);
	    property_attribute_info *prop
	      = ਨਵਾਂ property_attribute_info (attr_name, attr_comb, prop_ਕਿਸਮ);
	    prop_attr_list.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (prop);

	    ਰੁੱਖ meth_name;
	    ਚੋਣ (prop->prop_ਕਿਸਮ)
	      {
	      ਮੂਲ: ਰੋਕੋ;
	      ਹਾਲਤ OBJC_PROPERTY_ATTR_UNKNOWN:
		ਜੇ (attr_name)
		  error_at (attr_comb, "unknown property attribute %<%s%s%>",
			    ਜੋੜੋ_at ? "@" : "", IDENTIFIER_ਸੂਚਕ (attr_name));
		ਨਹੀਂਤਾਂ
		  error_at (attr_comb, "unknown property attribute");
		prop->parse_error = syntax_error = ਸੱਚ;
		ਰੋਕੋ;

	      ਹਾਲਤ OBJC_PROPERTY_ATTR_GETTER:
	      ਹਾਲਤ OBJC_PROPERTY_ATTR_SETTER:
		ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_EQ))
		  {
		    attr_comb = make_location (attr_ਸਿਰਾ, attr_ਸ਼ੁਰੂ, attr_ਸਿਰਾ);
		    error_at (attr_comb, "expected %<=%> after Objective-C %qE",
			      attr_name);
		    prop->parse_error = syntax_error = ਸੱਚ;
		    ਰੋਕੋ;
		  }
		token = c_parser_peek_token (parser);
		attr_ਸਿਰਾ = token->location;
		c_parser_consume_token (parser); /* eat the = */
		ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
		  {
		    attr_comb = make_location (attr_ਸਿਰਾ, attr_ਸ਼ੁਰੂ, attr_ਸਿਰਾ);
		    error_at (attr_comb, "expected %qE selector name",
			      attr_name);
		    prop->parse_error = syntax_error = ਸੱਚ;
		    ਰੋਕੋ;
		  }
		/* Get the end of the method name, and consume the name.  */
		token = c_parser_peek_token (parser);
		attr_ਸਿਰਾ = get_ਅੰਤ (token->location);
		meth_name = token->ਮੁੱਲ;
		c_parser_consume_token (parser);
		ਜੇ (prop->prop_ਕਿਸਮ == OBJC_PROPERTY_ATTR_SETTER)
		  {
		    ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COLON))
		      {
			attr_comb = make_location (attr_ਸਿਰਾ, attr_ਸ਼ੁਰੂ,
						   attr_ਸਿਰਾ);
			error_at (attr_comb, "setter method names must"
				  " terminate with %<:%>");
			prop->parse_error = syntax_error = ਸੱਚ;
		      }
		    ਨਹੀਂਤਾਂ
		      {
			attr_ਸਿਰਾ = get_ਅੰਤ (c_parser_peek_token
					       (parser)->location);
			c_parser_consume_token (parser);
		      }
		    attr_comb = make_location (attr_ਸ਼ੁਰੂ, attr_ਸ਼ੁਰੂ,
					       attr_ਸਿਰਾ);
		  }
		ਨਹੀਂਤਾਂ
		  attr_comb = make_location (attr_ਸ਼ੁਰੂ, attr_ਸ਼ੁਰੂ,
					       attr_ਸਿਰਾ);
		prop->ident = meth_name;
		/* Updated location including all that was successfully
		   parsed.  */
		prop->prop_loc = attr_comb;
		ਰੋਕੋ;
	    }

	  /* If we see a comma here, then keep going - even if we already
	     saw a syntax error.  For simple mistakes e.g. (assign, getter=x)
	     this makes a more useful output and avoid spurious warnings about
	     missing attributes that are, in fact, specified after the one with
	     the syntax error.  */
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ਨਹੀਂਤਾਂ
	    ਰੋਕੋ;
	}
      parser->objc_property_attr_context = ਝੂਠ;

      ਜੇ (syntax_error && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_CLOSE_PAREN))
	/* We don't really want to chew the whole of the file looking for a
	   matching closing parenthesis, so we will try to read the decl and
	   let the error handling for that close out the statement.  */
	;
      ਨਹੀਂਤਾਂ
	syntax_error = ਝੂਠ, parens.skip_until_ਮਿਲਿਆ_close (parser);
    }

  /* 'properties' is the list of properties that we read.  Usually a
     single one, but maybe more (eg, in "@property int a, b, c;" there
     are three).  */
  ਰੁੱਖ properties = c_parser_struct_declaration (parser, ਨਿਰਾ);

  ਜੇ (properties == error_mark_ਗੰਢ)
    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (properties == NULL_ਰੁੱਖ)
	c_parser_error (parser, "expected identifier");
      ਨਹੀਂਤਾਂ
	{
	  /* Comma-separated properties are chained together in reverse order;
	     add them one by one.  */
	  properties = nreverse (properties);
	  ਲਈ (; properties; properties = ਰੁੱਖ_CHAIN (properties))
	    objc_ਜੋੜੋ_property_declaration (loc, copy_ਗੰਢ (properties),
					    prop_attr_list);
	}
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
    }

  ਜਦੋਂ (!prop_attr_list.is_ਖਾਲੀ_ਥਾਵਾਂ())
    ਮਿਟਾਓ prop_attr_list.ਕੱਢੋ ();
  prop_attr_list.release ();
  parser->error = ਝੂਠ;
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
ਸਥਿਰ ਖਾਲੀ
c_parser_objc_at_synthesize_declaration (c_parser *parser)
{
  ਰੁੱਖ list = NULL_ਰੁੱਖ;
  location_t loc;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_SYNTHESIZE));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  ਜਦੋਂ (ਸੱਚ)
    {
      ਰੁੱਖ property, ivar;
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);
	  /* Once we find the semicolon, we can resume normal parsing.
	     We have to reset parser->error manually because
	     c_parser_skip_until_found() won't reset it for us if the
	     next token is precisely a semicolon.  */
	  parser->error = ਝੂਠ;
	  ਵਾਪਸ;
	}
      property = c_parser_peek_token (parser)->ਮੁੱਲ;
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EQ))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);
	      parser->error = ਝੂਠ;
	      ਵਾਪਸ;
	    }
	  ivar = c_parser_peek_token (parser)->ਮੁੱਲ;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ
	ivar = NULL_ਰੁੱਖ;
      list = chainon (list, build_ਰੁੱਖ_list (ivar, property));
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_ਜੋੜੋ_synthesize_declaration (loc, list);
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
ਸਥਿਰ ਖਾਲੀ
c_parser_objc_at_dynamic_declaration (c_parser *parser)
{
  ਰੁੱਖ list = NULL_ਰੁੱਖ;
  location_t loc;
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AT_DYNAMIC));
  loc = c_parser_peek_token (parser)->location;

  c_parser_consume_token (parser);
  ਜਦੋਂ (ਸੱਚ)
    {
      ਰੁੱਖ property;
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);
	  parser->error = ਝੂਠ;
	  ਵਾਪਸ;
	}
      property = c_parser_peek_token (parser)->ਮੁੱਲ;
      list = chainon (list, build_ਰੁੱਖ_list (NULL_ਰੁੱਖ, property));
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
  objc_ਜੋੜੋ_dynamic_declaration (loc, list);
}


/* Parse a pragma GCC ivdep.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parse_pragma_ivdep (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
  ਵਾਪਸ ਸੱਚ;
}

/* Parse a pragma GCC novector.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parse_pragma_novector (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
  ਵਾਪਸ ਸੱਚ;
}

/* Parse a pragma GCC unroll.  */

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ
c_parser_pragma_unroll (c_parser *parser)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ unroll;
  c_parser_consume_pragma (parser);
  location_t location = c_parser_peek_token (parser)->location;
  ਰੁੱਖ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
  mark_exp_read (ਵਿਅੰਜਕ);
  ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ, ਝੂਠ, ਨਿਰਾ);
  HOST_WIDE_INT lunroll = 0;
  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
      || ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) != INTEGER_CST
      || (lunroll = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (ਵਿਅੰਜਕ)) < 0
      || lunroll >= USHRT_MAX)
    {
      error_at (location, "%<#pragma GCC unroll%> requires an"
		" assignment-expression that evaluates to a non-negative"
		" integral constant less than %u", USHRT_MAX);
      unroll = 0;
    }
  ਨਹੀਂਤਾਂ
    {
      unroll = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ)lunroll;
      ਜੇ (unroll == 0)
	unroll = 1;
    }

  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
  ਵਾਪਸ unroll;
}

/* Handle pragmas.  Some OpenMP pragmas are associated with, and therefore
   should be considered, statements.  ALLOW_STMT is true if we're within
   the context of a function and such pragmas are to be allowed.  Returns
   true if we actually parsed such a pragma.  BEFORE_LABELS is last statement
   before possible labels, see get_before_labels description for details.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_pragma (c_parser *parser, ਗਿਣਤੀ pragma_context context, ਤਾਰਕਿਕ *if_p,
		 ਰੁੱਖ before_labels)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ id;
  ਅਚਲ ਅੱਖਰ *construct = ਨਿਰਾ;

  ਨਿਵੇਸ਼_location = c_parser_peek_token (parser)->location;
  id = c_parser_peek_token (parser)->pragma_ਕਿਸਮ;
  gcc_assert (id != PRAGMA_NONE);
  ਜੇ (parser->omp_for_parse_state
      && parser->omp_for_parse_state->ਵਿੱਚ_intervening_ਕੋਡ
      && id >= PRAGMA_OMP_ਸ਼ੁਰੂ && id <= PRAGMA_OMP_ਆਖਰੀ
      /* Allow a safe subset of non-executable directives. See classification in
	 array c_omp_directives.  */
      && id != PRAGMA_OMP_METADIRECTIVE && id != PRAGMA_OMP_NOTHING
      && id != PRAGMA_OMP_ASSUME && id != PRAGMA_OMP_ERROR)
    {
      error_at (
	ਨਿਵੇਸ਼_location,
	"intervening code must not contain executable OpenMP directives");
      parser->omp_for_parse_state->fail = ਸੱਚ;
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
      ਵਾਪਸ ਝੂਠ;
    }

  ਚੋਣ (id)
    {
    ਹਾਲਤ PRAGMA_OACC_DECLARE:
      c_parser_oacc_declare (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OACC_ENTER_ਅੰਕੜੇ:
      ਜੇ (context != pragma_compound)
	{
	  construct = "acc enter data";
	ਵਿੱਚ_compound:
	  ਜੇ (context == pragma_stmt)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"%<#pragma %s%> may only be used in compound "
			"statements", construct);
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
	      ਵਾਪਸ ਸੱਚ;
	    }
	  ਜਾਓ bad_stmt;
	}
      c_parser_oacc_enter_exit_ਅੰਕੜੇ (parser, ਸੱਚ);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OACC_EXIT_ਅੰਕੜੇ:
      ਜੇ (context != pragma_compound)
	{
	  construct = "acc exit data";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_oacc_enter_exit_ਅੰਕੜੇ (parser, ਝੂਠ);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OACC_ROUTINE:
      ਜੇ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma acc routine%> must be at file scope");
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
	  ਵਾਪਸ ਝੂਠ;
	}
      c_parser_oacc_routine (parser, context);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OACC_UPDATE:
      ਜੇ (context != pragma_compound)
	{
	  construct = "acc update";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_oacc_update (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_BARRIER:
      ਜੇ (context != pragma_compound)
	{
	  construct = "omp barrier";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_omp_barrier (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_DEPOBJ:
      ਜੇ (context != pragma_compound)
	{
	  construct = "omp depobj";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_omp_depobj (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_FLUSH:
      ਜੇ (context != pragma_compound)
	{
	  construct = "omp flush";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_omp_flush (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_INTEROP:
      ਜੇ (context != pragma_compound)
	{
	  construct = "omp interop";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_omp_interop (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_TASKWAIT:
      ਜੇ (context != pragma_compound)
	{
	  construct = "omp taskwait";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_omp_taskwait (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_TASKYIELD:
      ਜੇ (context != pragma_compound)
	{
	  construct = "omp taskyield";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_omp_taskyield (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_CANCEL:
      ਜੇ (context != pragma_compound)
	{
	  construct = "omp cancel";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
      c_parser_omp_cancel (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_CANCELLATION_ਬਿੰਦੂ:
      ਵਾਪਸ c_parser_omp_cancellation_ਬਿੰਦੂ (parser, context);

    ਹਾਲਤ PRAGMA_OMP_GROUPPRIVATE:
      c_parser_omp_groupprivate (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_THREADPRIVATE:
      c_parser_omp_threadprivate (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_ਨਿਸ਼ਾਨਾ:
      ਵਾਪਸ c_parser_omp_ਨਿਸ਼ਾਨਾ (parser, context, if_p);

    ਹਾਲਤ PRAGMA_OMP_BEGIN:
      c_parser_omp_begin (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_ਸਿਰਾ:
      c_parser_omp_ਸਿਰਾ (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_ਜਾਂਚ:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp scan%> may only be used in "
		"a loop construct with %<inscan%> %<reduction%> clause");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_SECTION:
      error_at (c_parser_peek_token (parser)->location,
		"%<#pragma omp section%> may only be used in "
		"%<#pragma omp sections%> construct");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_DECLARE:
      ਵਾਪਸ c_parser_omp_declare (parser, context);

    ਹਾਲਤ PRAGMA_OMP_REQUIRES:
      ਜੇ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp requires");
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
	  ਵਾਪਸ ਝੂਠ;
	}
      c_parser_omp_requires (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_ALLOCATE:
      c_parser_omp_allocate (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_ASSUMES:
      ਜੇ (context != pragma_external)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<#pragma %s%> may only be used at file scope",
		    "omp assumes");
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
	  ਵਾਪਸ ਝੂਠ;
	}
      c_parser_omp_assumes (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_NOTHING:
      c_parser_omp_nothing (parser);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OMP_METADIRECTIVE:
      c_parser_omp_metadirective (parser, if_p);
      ਵਾਪਸ ਸੱਚ;

    ਹਾਲਤ PRAGMA_OMP_ERROR:
      ਵਾਪਸ c_parser_omp_error (parser, context);

    ਹਾਲਤ PRAGMA_OMP_ORDERED:
      ਵਾਪਸ c_parser_omp_ordered (parser, context, if_p);

    ਹਾਲਤ PRAGMA_NOVECTOR:
    ਹਾਲਤ PRAGMA_UNROLL:
    ਹਾਲਤ PRAGMA_IVDEP:
      {
	ਤਾਰਕਿਕ novector = ਝੂਠ;
	ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ unroll = 0;
	ਤਾਰਕਿਕ ivdep = ਝੂਠ;

	ਚੋਣ (id)
	  {
	  ਹਾਲਤ PRAGMA_NOVECTOR:
	    novector = c_parse_pragma_novector (parser);
	    ਰੋਕੋ;
	  ਹਾਲਤ PRAGMA_UNROLL:
	    unroll = c_parser_pragma_unroll (parser);
	    ਰੋਕੋ;
	  ਹਾਲਤ PRAGMA_IVDEP:
	    ivdep = c_parse_pragma_ivdep (parser);
	    ਰੋਕੋ;
	  ਮੂਲ:
	    gcc_unreachable ();
	  }

	c_token *tok = c_parser_peek_token (parser);
	ਤਾਰਕਿਕ has_ਹੋਰ = tok->type == CPP_PRAGMA;
	ਜਦੋਂ (has_ਹੋਰ)
	  {
	    ਚੋਣ (tok->pragma_ਕਿਸਮ)
	      {
	      ਹਾਲਤ PRAGMA_IVDEP:
		ivdep = c_parse_pragma_ivdep (parser);
		ਰੋਕੋ;
	      ਹਾਲਤ PRAGMA_UNROLL:
		unroll = c_parser_pragma_unroll (parser);
		ਰੋਕੋ;
	      ਹਾਲਤ PRAGMA_NOVECTOR:
		novector = c_parse_pragma_novector (parser);
		ਰੋਕੋ;
	      ਮੂਲ:
		has_ਹੋਰ = ਝੂਠ;
		ਰੋਕੋ;
	      }
	    tok = c_parser_peek_token (parser);
	    has_ਹੋਰ = has_ਹੋਰ && tok->type == CPP_PRAGMA;
	  }
	ਜੇ (!c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_FOR)
	    && !c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_WHILE)
	    && !c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_DO))
	  {
	    c_parser_error (parser, "for, while or do statement expected");
	    ਵਾਪਸ ਝੂਠ;
	  }
	ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_FOR))
	  c_parser_for_statement (parser, ivdep, unroll, novector, if_p,
				  before_labels);
	ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_WHILE))
	  c_parser_while_statement (parser, ivdep, unroll, novector, if_p,
				    before_labels);
	ਨਹੀਂਤਾਂ
	  c_parser_do_statement (parser, ivdep, unroll, novector,
				 before_labels);
      }
      ਵਾਪਸ ਸੱਚ;

    ਹਾਲਤ PRAGMA_GCC_PCH_PREPROCESS:
      c_parser_error (parser, "%<#pragma GCC pch_preprocess%> must be first");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
      ਵਾਪਸ ਝੂਠ;

    ਹਾਲਤ PRAGMA_OACC_WAIT:
      ਜੇ (context != pragma_compound)
	{
	  construct = "acc wait";
	  ਜਾਓ ਵਿੱਚ_compound;
	}
	/* FALL THROUGH.  */

    ਮੂਲ:
      ਜੇ (id < PRAGMA_ਪਹਿਲਾ_EXTERNAL)
	{
	  ਜੇ (context != pragma_stmt && context != pragma_compound)
	    {
	    bad_stmt:
	      c_parser_error (parser, "expected declaration specifiers");
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_PRAGMA_EOL, ਨਿਰਾ);
	      ਵਾਪਸ ਝੂਠ;
	    }
	  c_parser_omp_construct (parser, if_p);
	  ਵਾਪਸ ਸੱਚ;
	}
      ਰੋਕੋ;
    }

  c_parser_consume_pragma (parser);
  c_invoke_pragma_handler (id);

  /* Skip to EOL, but suppress any error message.  Those will have been
     generated by the handler routine through calling error, as opposed
     to calling c_parser_error.  */
  parser->error = ਸੱਚ;
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  ਵਾਪਸ ਝੂਠ;
}

/* The interface the pragma parsers have to the lexer.  */

ਗਿਣਤੀ cpp_ttype
pragma_lex (ਰੁੱਖ *ਮੁੱਲ, location_t *loc)
{
  c_token *tok = c_parser_peek_token (the_parser);
  ਗਿਣਤੀ cpp_ttype ret = tok->type;

  *ਮੁੱਲ = tok->ਮੁੱਲ;
  ਜੇ (loc)
    *loc = tok->location;

  ਜੇ (ret == CPP_PRAGMA_EOL || ret == CPP_EOF)
    ret = CPP_EOF;
  ਨਹੀਂਤਾਂ ਜੇ (ret == CPP_STRING)
    *ਮੁੱਲ = c_parser_string_literal (the_parser, ਝੂਠ, ਝੂਠ).ਮੁੱਲ;
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (ret == CPP_KEYWORD)
	ret = CPP_NAME;
      c_parser_consume_token (the_parser);
    }

  ਵਾਪਸ ret;
}

ਖਾਲੀ
pragma_lex_discard_ਮੰਜ਼ਿਲ_eol ()
{
  cpp_ttype type;
  ਕਰੋ
    {
      type = c_parser_peek_token (the_parser)->type;
      gcc_assert (type != CPP_EOF);
      c_parser_consume_token (the_parser);
    } ਜਦੋਂ (type != CPP_PRAGMA_EOL);
}

ਸਥਿਰ ਖਾਲੀ
c_parser_pragma_pch_preprocess (c_parser *parser)
{
  ਰੁੱਖ name = ਨਿਰਾ;

  parser->lex_joined_string = ਸੱਚ;
  c_parser_consume_pragma (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_STRING))
    {
      name = c_parser_peek_token (parser)->ਮੁੱਲ;
      c_parser_consume_token (parser);
    }
  ਨਹੀਂਤਾਂ
    c_parser_error (parser, "expected string literal");
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
  parser->lex_joined_string = ਝੂਠ;

  ਜੇ (name)
    c_common_pch_pragma (parse_ਵਿੱਚ, ਰੁੱਖ_STRING_ਸੂਚਕ (name));
}

/* OpenACC and OpenMP parsing routines.  */

/* Returns name of the next clause.
   If the clause is not recognized PRAGMA_OMP_CLAUSE_NONE is returned and
   the token is not consumed.  Otherwise appropriate pragma_omp_clause is
   returned and the token is consumed.  */

ਸਥਿਰ pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_NONE;

  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AUTO))
    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_AUTO;
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_IF))
    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_IF;
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_DEFAULT))
    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DEFAULT;
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_FOR))
    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_FOR;
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      ਚੋਣ (p[0])
	{
	ਹਾਲਤ 'a':
	  ਜੇ (!strcmp ("affinity", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_AFFINITY;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("aligned", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ALIGNED;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("allocate", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ALLOCATE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("async", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_ASYNC;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("attach", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_ATTACH;
	  ਰੋਕੋ;
	ਹਾਲਤ 'b':
	  ਜੇ (!strcmp ("bind", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_BIND;
	  ਰੋਕੋ;
	ਹਾਲਤ 'c':
	  ਜੇ (!strcmp ("collapse", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_COLLAPSE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("copy", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_COPY;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("copyin", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_COPYIN;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("copyout", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_COPYOUT;
          ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("copyprivate", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("create", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_CREATE;
	  ਰੋਕੋ;
	ਹਾਲਤ 'd':
	  ਜੇ (!strcmp ("defaultmap", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DEFAULTMAP;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("delete", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_DELETE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("depend", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DEPEND;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("destroy", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DESTROY;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("detach", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_DETACH;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("device", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DEVICE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("deviceptr", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_DEVICEPTR;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("device_resident", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("device_type", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DEVICE_TYPE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("dist_schedule", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("doacross", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DOACROSS;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("dyn_groupprivate", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE;
	  ਰੋਕੋ;
	ਹਾਲਤ 'e':
	  ਜੇ (!strcmp ("enter", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ENTER;
	  ਰੋਕੋ;
	ਹਾਲਤ 'f':
	  ਜੇ (!strcmp ("filter", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_FILTER;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("final", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_FINAL;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("finalize", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_FINALIZE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("firstprivate", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("from", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_FROM;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("full", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਭਰਿਆ;
	  ਰੋਕੋ;
	ਹਾਲਤ 'g':
	  ਜੇ (!strcmp ("gang", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_GANG;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("grainsize", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_GRAINSIZE;
	  ਰੋਕੋ;
	ਹਾਲਤ 'h':
	  ਜੇ (!strcmp ("has_device_addr", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("hint", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_HINT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("host", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_HOST;
	  ਰੋਕੋ;
	ਹਾਲਤ 'i':
	  ਜੇ (!strcmp ("if_present", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_IF_PRESENT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("in_reduction", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਵਿੱਚ_REDUCTION;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("inbranch", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_INBRANCH;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("independent", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_INDEPENDENT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("indirect", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਅਸਿੱਧਾ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("init", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_INIT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("is_device_ptr", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("interop", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_INTEROP;
	  ਰੋਕੋ;
	ਹਾਲਤ 'l':
	  ਜੇ (!strcmp ("lastprivate", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("linear", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਰੇਖਿਕ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("link", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_LINK;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("local", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_LOCAL;
	  ਰੋਕੋ;
	ਹਾਲਤ 'm':
	  ਜੇ (!strcmp ("map", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_MAP;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("mergeable", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_MERGEABLE;
	  ਰੋਕੋ;
	ਹਾਲਤ 'n':
	  ਜੇ (!strcmp ("no_create", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_NO_CREATE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("nocontext", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_NOCONTEXT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("nogroup", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_NOGROUP;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("nohost", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_NOHOST;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("nontemporal", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_NONTEMPORAL;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("notinbranch", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_NOTINBRANCH;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("novariants", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_NOVARIANTS;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("nowait", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_NOWAIT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("num_gangs", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_ਅੰਕ_GANGS;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("num_tasks", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਅੰਕ_TASKS;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("num_teams", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਅੰਕ_TEAMS;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("num_threads", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਅੰਕ_ਧਾਗੇ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("num_workers", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_ਅੰਕ_WORKERS;
	  ਰੋਕੋ;
	ਹਾਲਤ 'o':
	  ਜੇ (!strcmp ("ordered", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ORDERED;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("order", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਕ੍ਰਮ;
	  ਰੋਕੋ;
	ਹਾਲਤ 'p':
	  ਜੇ (!strcmp ("parallel", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_PARALLEL;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("partial", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_PARTIAL;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("present", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_PRESENT;
	  /* As of OpenACC 2.5, these are now aliases of the non-present_or
	     clauses.  */
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("present_or_copy", p)
		   || !strcmp ("pcopy", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_COPY;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("present_or_copyin", p)
		   || !strcmp ("pcopyin", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_COPYIN;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("present_or_copyout", p)
		   || !strcmp ("pcopyout", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_COPYOUT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("present_or_create", p)
		   || !strcmp ("pcreate", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_CREATE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("priority", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਤਰਜੀਹ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("private", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("proc_bind", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_PROC_BIND;
	  ਰੋਕੋ;
	ਹਾਲਤ 'r':
	  ਜੇ (!strcmp ("reduction", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_REDUCTION;
	  ਰੋਕੋ;
	ਹਾਲਤ 's':
	  ਜੇ (!strcmp ("safelen", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_SAFELEN;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("schedule", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("sections", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_SECTIONS;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("self", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_SELF;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("seq", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_SEQ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("shared", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_SHARED;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("simd", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_SIMD;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("simdlen", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_SIMDLEN;
	  ਰੋਕੋ;
	ਹਾਲਤ 't':
	  ਜੇ (!strcmp ("task_reduction", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_TASK_REDUCTION;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("taskgroup", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_TASKGROUP;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("thread_limit", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("threads", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਧਾਗੇ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("tile", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_TILE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("to", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਮੰਜ਼ਿਲ;
	  ਰੋਕੋ;
	ਹਾਲਤ 'u':
	  ਜੇ (!strcmp ("uniform", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਇਕਸਾਰ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("untied", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_UNTIED;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("use", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_USE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("use_device", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_USE_DEVICE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("use_device_addr", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("use_device_ptr", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("uses_allocators", p))
	    ਨਤੀਜਾ = PRAGMA_OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS;
	  ਰੋਕੋ;
	ਹਾਲਤ 'v':
	  ਜੇ (!strcmp ("vector", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_ਸਦਿਸ਼;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("vector_length", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_ਸਦਿਸ਼_ਲੰਮਾਈ;
	  ਰੋਕੋ;
	ਹਾਲਤ 'w':
	  ਜੇ (!strcmp ("wait", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_WAIT;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("worker", p))
	    ਨਤੀਜਾ = PRAGMA_OACC_CLAUSE_ਕਾਮਾ;
	  ਰੋਕੋ;
	}
    }

  ਜੇ (ਨਤੀਜਾ != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  ਵਾਪਸ ਨਤੀਜਾ;
}

/* Validate that a clause of the given type does not already exist.  */

ਸਥਿਰ ਖਾਲੀ
check_no_duplicate_clause (ਰੁੱਖ clauses, ਗਿਣਤੀ omp_clause_ਕੋਡ ਕੋਡ,
			   ਅਚਲ ਅੱਖਰ *name)
{
  ਜੇ (ਰੁੱਖ c = omp_ਲੱਭੋ_clause (clauses, ਕੋਡ))
    error_at (OMP_CLAUSE_LOCATION (c), "too many %qs clauses", name);
}

/* OpenACC 2.0
   Parse wait clause or wait directive parameters.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_wait_list (c_parser *parser, location_t clause_loc, ਰੁੱਖ list)
{
  vec<ਰੁੱਖ, va_gc> *ਦਲੀਲਾਂ;
  ਰੁੱਖ t, ਦਲੀਲਾਂ_ਰੁੱਖ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਦਲੀਲਾਂ = c_parser_ਵਿਅੰਜਕ_list (parser, ਝੂਠ, ਸੱਚ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
  ਦਲੀਲਾਂ_ਰੁੱਖ = build_ਰੁੱਖ_list_vec (ਦਲੀਲਾਂ);

  ਲਈ (t = ਦਲੀਲਾਂ_ਰੁੱਖ; t; t = ਰੁੱਖ_CHAIN (t))
    {
      ਰੁੱਖ targ = ਰੁੱਖ_ਮੁੱਲ (t);

      ਜੇ (targ != error_mark_ਗੰਢ)
	{
	  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (targ)))
	    {
	      c_parser_error (parser, "expression must be integral");
	      targ = error_mark_ਗੰਢ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

	      OMP_CLAUSE_DECL (c) = targ;
	      OMP_CLAUSE_CHAIN (c) = list;
	      list = c;
	    }
	}
    }

  release_ਰੁੱਖ_ਸਦਿਸ਼ (ਦਲੀਲਾਂ);
  parens.require_close (parser);
  ਵਾਪਸ list;
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

ਬਣਤਰ omp_dim
{
  ਰੁੱਖ ਨੀਵਾਂ_bound, ਲੰਮਾਈ;
  location_t loc;
  ਤਾਰਕਿਕ no_colon;
  omp_dim (ਰੁੱਖ lb, ਰੁੱਖ len, location_t lo, ਤਾਰਕਿਕ nc)
  : ਨੀਵਾਂ_bound (lb), ਲੰਮਾਈ (len), loc (lo), no_colon (nc) {}
};

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_variable_list (c_parser *parser,
			    location_t clause_loc,
			    ਗਿਣਤੀ omp_clause_ਕੋਡ ਕਿਸਮ, ਰੁੱਖ list,
			    ਤਾਰਕਿਕ map_lvalue = ਝੂਠ)
{
  auto_vec<omp_dim> dims;
  ਤਾਰਕਿਕ array_section_p;
  auto_vec<c_token> ਟੋਕਨ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਟੋਕਨ_avail = 0;
  c_token *saved_ਟੋਕਨ = ਨਿਰਾ;

  ਜਦੋਂ (1)
    {
      ਰੁੱਖ t = NULL_ਰੁੱਖ;
      location_t tloc = c_parser_peek_token (parser)->location;

      ਜੇ (ਕਿਸਮ == OMP_CLAUSE_DEPEND || ਕਿਸਮ == OMP_CLAUSE_AFFINITY)
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME)
	      || c_parser_peek_token (parser)->id_ਕਿਸਮ != C_ID_ID)
	    {
	      ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
	      ਜੇ (ਕਿਸਮ == OMP_CLAUSE_DEPEND
		  && c_parser_ਅਗਲਾ_token_is_keyword (parser,
						     RID_OMP_ALL_ਸਮ੍ਰਿਤੀ)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)))
		{
		  ਵਿਅੰਜਕ.ਮੁੱਲ = ridpointers[RID_OMP_ALL_ਸਮ੍ਰਿਤੀ];
		  c_parser_consume_token (parser);
		}
	      ਨਹੀਂਤਾਂ
		ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	      ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ != error_mark_ਗੰਢ)
		{
		  ਰੁੱਖ u = build_omp_clause (clause_loc, ਕਿਸਮ);
		  OMP_CLAUSE_DECL (u) = ਵਿਅੰਜਕ.ਮੁੱਲ;
		  OMP_CLAUSE_CHAIN (u) = list;
		  list = u;
		}

	      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COMMA))
		ਰੋਕੋ;

	      c_parser_consume_token (parser);
	      ਜਾਰੀ;
	    }

	  ਟੋਕਨ.truncate (0);
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nesting_ਡੂੰਘਾਈ = 0;
	  ਜਦੋਂ (1)
	    {
	      c_token *token = c_parser_peek_token (parser);
	      ਚੋਣ (token->type)
		{
		ਹਾਲਤ CPP_EOF:
		ਹਾਲਤ CPP_PRAGMA_EOL:
		  ਰੋਕੋ;
		ਹਾਲਤ CPP_OPEN_BRACE:
		ਹਾਲਤ CPP_OPEN_PAREN:
		ਹਾਲਤ CPP_OPEN_ਵਰਗਫਲ:
		  ++nesting_ਡੂੰਘਾਈ;
		  ਜਾਓ ਜੋੜੋ;
		ਹਾਲਤ CPP_CLOSE_BRACE:
		ਹਾਲਤ CPP_CLOSE_PAREN:
		ਹਾਲਤ CPP_CLOSE_ਵਰਗਫਲ:
		  ਜੇ (nesting_ਡੂੰਘਾਈ-- == 0)
		    ਰੋਕੋ;
		  ਜਾਓ ਜੋੜੋ;
		ਹਾਲਤ CPP_COMMA:
		  ਜੇ (nesting_ਡੂੰਘਾਈ == 0)
		    ਰੋਕੋ;
		  ਜਾਓ ਜੋੜੋ;
		ਮੂਲ:
		ਜੋੜੋ:
		  ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*token);
		  c_parser_consume_token (parser);
		  ਜਾਰੀ;
		}
	      ਰੋਕੋ;
	    }

	  /* Make sure nothing tries to read past the end of the tokens.  */
	  c_token eof_token;
	  memset (&eof_token, 0, ਆਕਾਰ (eof_token));
	  eof_token.type = CPP_EOF;
	  ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eof_token);
	  ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eof_token);

	  saved_ਟੋਕਨ = parser->ਟੋਕਨ;
	  ਟੋਕਨ_avail = parser->ਟੋਕਨ_avail;
	  parser->ਟੋਕਨ = ਟੋਕਨ.ਪਤਾ ();
	  parser->ਟੋਕਨ_avail = ਟੋਕਨ.ਲੰਮਾਈ ();
	}
      ਨਹੀਂਤਾਂ ਜੇ (map_lvalue
	       && (ਕਿਸਮ == OMP_CLAUSE_MAP
		   || ਕਿਸਮ == OMP_CLAUSE_ਮੰਜ਼ਿਲ
		   || ਕਿਸਮ == OMP_CLAUSE_FROM))
	{
	  location_t loc = c_parser_peek_token (parser)->location;
	  ਤਾਰਕਿਕ save_c_omp_array_section_p = c_omp_array_section_p;
	  c_omp_array_section_p = ਸੱਚ;
	  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ != error_mark_ਗੰਢ)
	    mark_exp_read (ਵਿਅੰਜਕ.ਮੁੱਲ);
	  c_omp_array_section_p = save_c_omp_array_section_p;
	  ਰੁੱਖ decl = ਵਿਅੰਜਕ.ਮੁੱਲ;

	 /* This code rewrites a parsed expression containing various tree
	    codes used to represent array accesses into a more uniform nest of
	    OMP_ARRAY_SECTION nodes before it is processed by
	    c-typeck.cc:handle_omp_array_sections_1.  It might be more
	    efficient to move this logic to that function instead, analysing
	    the parsed expression directly rather than this preprocessed
	    form.  (See also equivalent code in cp/parser.cc,
	    cp/semantics.cc).  */
	  dims.truncate (0);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == OMP_ARRAY_SECTION)
	    {
	      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (decl) == OMP_ARRAY_SECTION)
		{
		  ਰੁੱਖ ਨੀਵਾਂ_bound = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 1);
		  ਰੁੱਖ ਲੰਮਾਈ = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 2);
		  dims.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (omp_dim (ਨੀਵਾਂ_bound, ਲੰਮਾਈ, loc, ਝੂਠ));
		  decl = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 0);
		}

	      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (decl) == ARRAY_REF
		     || ਰੁੱਖ_ਕੋਡ (decl) == ਅਸਿੱਧਾ_REF
		     || ਰੁੱਖ_ਕੋਡ (decl) == COMPOUND_ਵਿਅੰਜਕ)
		{
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == COMPOUND_ਵਿਅੰਜਕ)
		    {
		      decl = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 1);
		      STRIP_NOPS (decl);
		    }
		  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == ਅਸਿੱਧਾ_REF)
		    {
		      dims.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (omp_dim (integer_zero_ਗੰਢ,
					       integer_one_ਗੰਢ, loc, ਸੱਚ));
		      decl = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 0);
		    }
		  ਨਹੀਂਤਾਂ  /* ARRAY_REF. */
		    {
		      ਰੁੱਖ ਸੂਚਕਾਂਕ = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 1);
		      dims.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (omp_dim (ਸੂਚਕਾਂਕ, integer_one_ਗੰਢ, loc,
					       ਸੱਚ));
		      decl = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 0);
		    }
		}

	      ਲਈ (ਪੂਰਨ i = dims.ਲੰਮਾਈ () - 1; i >= 0; i--)
		decl = build_omp_array_section (loc,  decl, dims[i].ਨੀਵਾਂ_bound,
						dims[i].ਲੰਮਾਈ);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == ਅਸਿੱਧਾ_REF)
	    {
	      /* Turn indirection of a pointer "*foo" into "foo[0:1]".  */
	      decl = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, integer_zero_ਗੰਢ,
					      integer_one_ਗੰਢ);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == ARRAY_REF)
	    {
	      ਰੁੱਖ idx = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 1);

	      decl = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 0);
	      STRIP_NOPS (decl);

	      decl = build_omp_array_section (loc, decl, idx, integer_one_ਗੰਢ);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) == NON_LVALUE_ਵਿਅੰਜਕ
		   || CONVERT_ਵਿਅੰਜਕ_P (decl))
	    decl = ਰੁੱਖ_ਸੰਕਾਰਜ (decl, 0);

	  ਰੁੱਖ u = build_omp_clause (loc, ਕਿਸਮ);
	  OMP_CLAUSE_DECL (u) = decl;
	  OMP_CLAUSE_CHAIN (u) = list;
	  list = u;

	  ਜਾਓ ਅਗਲਾ_ਵਸਤੂ;
	}

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID)
	{
	  t = lookup_name (c_parser_peek_token (parser)->ਮੁੱਲ);

	  ਜੇ (t == NULL_ਰੁੱਖ)
	    {
	      undeclared_variable (c_parser_peek_token (parser)->location,
	      c_parser_peek_token (parser)->ਮੁੱਲ);
	      t = error_mark_ਗੰਢ;
	    }

	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
	       && (c_parser_peek_token (parser)->keyword == RID_FUNCTION_NAME
		   || (c_parser_peek_token (parser)->keyword
		       == RID_PRETTY_FUNCTION_NAME)
		   || (c_parser_peek_token (parser)->keyword
		       == RID_C99_FUNCTION_NAME)))
	t = c_parser_predefined_identifier (parser).ਮੁੱਲ;
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected identifier");
	  ਰੋਕੋ;
	}

      ਜੇ (t == error_mark_ਗੰਢ)
	;
      ਨਹੀਂਤਾਂ ਜੇ (ਕਿਸਮ != 0)  /* kind != OMP_CLAUSE_ERROR */
	{
	  ਚੋਣ (ਕਿਸਮ)
	    {
	    ਹਾਲਤ OMP_CLAUSE__CACHE_:
	      /* The OpenACC cache directive explicitly only allows "array
		 elements or subarrays".  */
	      ਜੇ (c_parser_peek_token (parser)->type != CPP_OPEN_ਵਰਗਫਲ)
		{
		  c_parser_error (parser, "expected %<[%>");
		  t = error_mark_ਗੰਢ;
		  ਰੋਕੋ;
		}
	      /* FALLTHROUGH  */
	    ਹਾਲਤ OMP_CLAUSE_MAP:
	    ਹਾਲਤ OMP_CLAUSE_FROM:
	    ਹਾਲਤ OMP_CLAUSE_ਮੰਜ਼ਿਲ:
	    ਸ਼ੁਰੂ_component_ref:
	      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_DOT)
		     || c_parser_ਅਗਲਾ_token_is (parser, CPP_DEREF))
		{
		  location_t op_loc = c_parser_peek_token (parser)->location;
		  location_t arrow_loc = UNKNOWN_LOCATION;
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_DEREF))
		    {
		      c_ਵਿਅੰਜਕ t_ਵਿਅੰਜਕ;
		      t_ਵਿਅੰਜਕ.ਮੁੱਲ = t;
		      t_ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
		      t_ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
		      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&t_ਵਿਅੰਜਕ, op_loc, op_loc);
		      t_ਵਿਅੰਜਕ.m_decimal = 0;
		      t_ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (op_loc, t_ਵਿਅੰਜਕ,
							 ਸੱਚ, ਝੂਠ);
		      t = build_ਅਸਿੱਧਾ_ref (op_loc, t_ਵਿਅੰਜਕ.ਮੁੱਲ, RO_ARROW);
		      arrow_loc = t_ਵਿਅੰਜਕ.get_location ();
		    }
		  c_parser_consume_token (parser);
		  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected identifier");
		      t = error_mark_ਗੰਢ;
		      ਰੋਕੋ;
		    }

		  c_token *comp_tok = c_parser_peek_token (parser);
		  ਰੁੱਖ ident = comp_tok->ਮੁੱਲ;
		  location_t comp_loc = comp_tok->location;
		  c_parser_consume_token (parser);
		  t = build_component_ref (op_loc, t, ident, comp_loc,
					   arrow_loc);
		}
	      /* FALLTHROUGH  */
	    ਹਾਲਤ OMP_CLAUSE_AFFINITY:
	    ਹਾਲਤ OMP_CLAUSE_DEPEND:
	    ਹਾਲਤ OMP_CLAUSE_REDUCTION:
	    ਹਾਲਤ OMP_CLAUSE_ਵਿੱਚ_REDUCTION:
	    ਹਾਲਤ OMP_CLAUSE_TASK_REDUCTION:
	    ਹਾਲਤ OMP_CLAUSE_HAS_DEVICE_ADDR:
	      array_section_p = ਝੂਠ;
	      dims.truncate (0);
	      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_ਵਰਗਫਲ))
		{
		  location_t loc = UNKNOWN_LOCATION;
		  ਰੁੱਖ ਨੀਵਾਂ_bound = NULL_ਰੁੱਖ, ਲੰਮਾਈ = NULL_ਰੁੱਖ;
		  ਤਾਰਕਿਕ no_colon = ਝੂਠ;

		  c_parser_consume_token (parser);
		  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
		    {
		      location_t ਵਿਅੰਜਕ_loc
			= c_parser_peek_token (parser)->location;
		      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
		      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ,
						       ਝੂਠ, ਸੱਚ);
		      ਨੀਵਾਂ_bound = ਵਿਅੰਜਕ.ਮੁੱਲ;
		      loc = ਵਿਅੰਜਕ_loc;
		    }
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_ਵਰਗਫਲ))
		    {
		      ਲੰਮਾਈ = integer_one_ਗੰਢ;
		      no_colon = ਸੱਚ;
		    }
		  ਨਹੀਂਤਾਂ
		    {
		      /* Look for `:'.  */
		      ਜੇ (!c_parser_require (parser, CPP_COLON,
					     "expected %<:%>"))
			{
			  t = error_mark_ਗੰਢ;
			  ਰੋਕੋ;
			}
		      array_section_p = ਸੱਚ;
		      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_ਵਰਗਫਲ))
			{
			  location_t ਵਿਅੰਜਕ_loc
			    = c_parser_peek_token (parser)->location;
			  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
			  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ,
							   ਝੂਠ, ਸੱਚ);
			  ਲੰਮਾਈ = ਵਿਅੰਜਕ.ਮੁੱਲ;
			}
		    }
		  /* Look for the closing `]'.  */
		  ਜੇ (!c_parser_require (parser, CPP_CLOSE_ਵਰਗਫਲ,
					 "expected %<]%>"))
		    {
		      t = error_mark_ਗੰਢ;
		      ਰੋਕੋ;
		    }

		  dims.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (omp_dim (ਨੀਵਾਂ_bound, ਲੰਮਾਈ, loc, no_colon));
		}

	      ਜੇ (t != error_mark_ਗੰਢ)
		{
		  ਜੇ ((ਕਿਸਮ == OMP_CLAUSE_MAP
		       || ਕਿਸਮ == OMP_CLAUSE_FROM
		       || ਕਿਸਮ == OMP_CLAUSE_ਮੰਜ਼ਿਲ)
		      && !array_section_p
		      && (c_parser_ਅਗਲਾ_token_is (parser, CPP_DOT)
			  || c_parser_ਅਗਲਾ_token_is (parser, CPP_DEREF)))
		    {
		      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < dims.ਲੰਮਾਈ (); i++)
			{
			  gcc_assert (dims[i].ਲੰਮਾਈ == integer_one_ਗੰਢ);
			  t = build_array_ref (dims[i].loc,
					       t, dims[i].ਨੀਵਾਂ_bound);
			}
		      ਜਾਓ ਸ਼ੁਰੂ_component_ref;
		    }
		  ਨਹੀਂਤਾਂ
		    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < dims.ਲੰਮਾਈ (); i++)
		      t = build_omp_array_section (clause_loc, t,
						   dims[i].ਨੀਵਾਂ_bound,
						   dims[i].ਲੰਮਾਈ);
		}

	      ਜੇ ((ਕਿਸਮ == OMP_CLAUSE_DEPEND || ਕਿਸਮ == OMP_CLAUSE_AFFINITY)
		  && t != error_mark_ਗੰਢ
		  && parser->ਟੋਕਨ_avail != 2)
		{
		  ਜੇ (array_section_p)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<)%> or %<,%>");
		      t = error_mark_ਗੰਢ;
		    }
		  ਨਹੀਂਤਾਂ
		    {
		      parser->ਟੋਕਨ = ਟੋਕਨ.ਪਤਾ ();
		      parser->ਟੋਕਨ_avail = ਟੋਕਨ.ਲੰਮਾਈ ();

		      t = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
		      ਜੇ (t != error_mark_ਗੰਢ && parser->ਟੋਕਨ_avail != 2)
			{
			  error_at (c_parser_peek_token (parser)->location,
				    "expected %<)%> or %<,%>");
			  t = error_mark_ਗੰਢ;
			}
		    }
		}
	      ਰੋਕੋ;
	    ਮੂਲ:
	      ਰੋਕੋ;
	    }

	  ਜੇ (t != error_mark_ਗੰਢ)
	    {
	      ਰੁੱਖ u = build_omp_clause (clause_loc, ਕਿਸਮ);
	      OMP_CLAUSE_DECL (u) = t;
	      OMP_CLAUSE_CHAIN (u) = list;
	      list = u;
	    }
	}
      ਨਹੀਂਤਾਂ  /* kind == OMP_CLAUSE_ERROR */
	list = ਰੁੱਖ_cons (t, build_ਖਾਲੀ_ਥਾਵਾਂ_stmt (tloc), list);

      ਜੇ (ਕਿਸਮ == OMP_CLAUSE_DEPEND || ਕਿਸਮ == OMP_CLAUSE_AFFINITY)
	{
	  parser->ਟੋਕਨ = saved_ਟੋਕਨ;
	  parser->ਟੋਕਨ_avail = ਟੋਕਨ_avail;
	}

    ਅਗਲਾ_ਵਸਤੂ:
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COMMA))
	ਰੋਕੋ;

      c_parser_consume_token (parser);
    }

  ਵਾਪਸ list;
}

/* Similarly, but expect leading and trailing parenthesis.  This is a very
   common case for OpenACC and OpenMP clauses.  The optional ALLOW_DEREF
   argument is true if list items can use the deref (->) operator.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_var_list_parens (c_parser *parser, ਗਿਣਤੀ omp_clause_ਕੋਡ ਕਿਸਮ,
			      ਰੁੱਖ list, ਤਾਰਕਿਕ map_lvalue = ਝੂਠ)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  ਜੇ (parser->ਵਿੱਚ_omp_decl_attribute)
    {
      ਜੇ (ਕਿਸਮ)
	{
	  ਰੁੱਖ u = build_omp_clause (loc, ਕਿਸਮ);
	  OMP_CLAUSE_DECL (u) = parser->ਵਿੱਚ_omp_decl_attribute;
	  OMP_CLAUSE_CHAIN (u) = list;
	  ਵਾਪਸ u;
	}
      ਨਹੀਂਤਾਂ
	ਵਾਪਸ ਰੁੱਖ_cons (parser->ਵਿੱਚ_omp_decl_attribute, NULL_ਰੁੱਖ, list);
    }

  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, ਕਿਸਮ, list, map_lvalue);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਵਾਪਸ list;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_ਅੰਕੜੇ_clause (c_parser *parser, pragma_omp_clause c_ਕਿਸਮ,
			   ਰੁੱਖ list)
{
  ਗਿਣਤੀ gomp_map_ਕਿਸਮ ਕਿਸਮ;
  ਚੋਣ (c_ਕਿਸਮ)
    {
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_ATTACH:
      ਕਿਸਮ = GOMP_MAP_ATTACH;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_COPY:
      ਕਿਸਮ = GOMP_MAP_TOFROM;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_COPYIN:
      ਕਿਸਮ = GOMP_MAP_ਮੰਜ਼ਿਲ;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_COPYOUT:
      ਕਿਸਮ = GOMP_MAP_FROM;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_CREATE:
      ਕਿਸਮ = GOMP_MAP_ALLOC;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_DELETE:
      ਕਿਸਮ = GOMP_MAP_RELEASE;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_DETACH:
      ਕਿਸਮ = GOMP_MAP_DETACH;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_DEVICE:
      ਕਿਸਮ = GOMP_MAP_FORCE_ਮੰਜ਼ਿਲ;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
      ਕਿਸਮ = GOMP_MAP_DEVICE_RESIDENT;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_LINK:
      ਕਿਸਮ = GOMP_MAP_LINK;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_NO_CREATE:
      ਕਿਸਮ = GOMP_MAP_IF_PRESENT;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_PRESENT:
      ਕਿਸਮ = GOMP_MAP_FORCE_PRESENT;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_SELF:
      /* "The 'host' clause is a synonym for the 'self' clause."  */
    ਹਾਲਤ PRAGMA_OACC_CLAUSE_HOST:
      ਕਿਸਮ = GOMP_MAP_FORCE_FROM;
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }

  ਰੁੱਖ nl = list;
  ਤਾਰਕਿਕ readonly = ਝੂਠ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      /* Turn on readonly modifier parsing for copyin clause.  */
      ਜੇ (c_ਕਿਸਮ == PRAGMA_OACC_CLAUSE_COPYIN)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ਜੇ (token->type == CPP_NAME
	      && !strcmp (IDENTIFIER_ਸੂਚਕ (token->ਮੁੱਲ), "readonly")
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      readonly = ਸੱਚ;
	    }
	}
      nl = c_parser_omp_variable_list (parser, open_loc, OMP_CLAUSE_MAP, list,
				       ਝੂਠ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }

  ਲਈ (ਰੁੱਖ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (c, ਕਿਸਮ);
      ਜੇ (readonly)
	OMP_CLAUSE_MAP_READONLY (c) = 1;
    }

  ਵਾਪਸ nl;
}

/* OpenACC 2.0:
   deviceptr ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_ਅੰਕੜੇ_clause_deviceptr (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ vars, t;

  /* Can't use OMP_CLAUSE_MAP here (that is, can't use the generic
     c_parser_oacc_data_clause), as for PRAGMA_OACC_CLAUSE_DEVICEPTR,
     variable-list must only allow for pointer variables.  */
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ਨਿਰਾ);
  ਲਈ (t = vars; t && t; t = ਰੁੱਖ_CHAIN (t))
    {
      ਰੁੱਖ v = ਰੁੱਖ_PURPOSE (t);
      location_t loc = ਵਿਅੰਜਕ_LOCATION (ਰੁੱਖ_ਮੁੱਲ (t));

      ਜੇ (!VAR_P (v) && ਰੁੱਖ_ਕੋਡ (v) != PARM_DECL)
	error_at (loc, "%qD is not a variable", v);
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_TYPE (v) == error_mark_ਗੰਢ)
	;
      ਨਹੀਂਤਾਂ ਜੇ (!ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (v)))
	error_at (loc, "%qD is not a pointer variable", v);

      ਰੁੱਖ u = build_omp_clause (loc, OMP_CLAUSE_MAP);
      OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (u, GOMP_MAP_FORCE_DEVICEPTR);
      OMP_CLAUSE_DECL (u) = v;
      OMP_CLAUSE_CHAIN (u) = list;
      list = u;
    }

  ਵਾਪਸ list;
}

/* OpenACC 2.0, OpenMP 3.0:
   collapse ( constant-expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_collapse (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ c, ਅੰਕ = error_mark_ਗੰਢ;
  HOST_WIDE_INT n;
  location_t loc;

  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");
  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");

  loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      ਅੰਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਜੇ (ਅੰਕ == error_mark_ਗੰਢ)
    ਵਾਪਸ list;
  mark_exp_read (ਅੰਕ);
  ਅੰਕ = c_fully_fold (ਅੰਕ, ਝੂਠ, ਨਿਰਾ);
  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਅੰਕ))
      || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_shwi_p (ਅੰਕ)
      || (n = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (ਅੰਕ)) <= 0
      || (ਪੂਰਨ) n != n)
    {
      error_at (loc,
		"collapse argument needs positive constant integer expression");
      ਵਾਪਸ list;
    }
  c = build_omp_clause (loc, OMP_CLAUSE_COLLAPSE);
  OMP_CLAUSE_COLLAPSE_ਵਿਅੰਜਕ (c) = ਅੰਕ;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 2.5:
   copyin ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_copyin (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYIN, list);
}

/* OpenMP 2.5:
   copyprivate ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_copyprivate (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_COPYPRIVATE, list);
}

/* OpenMP 2.5:
   default ( none | shared )

   OpenMP 5.1:
   default ( private | firstprivate )

   OpenACC:
   default ( none | present ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_default (c_parser *parser, ਰੁੱਖ list, ਤਾਰਕਿਕ is_oacc)
{
  ਗਿਣਤੀ omp_clause_default_ਕਿਸਮ ਕਿਸਮ = OMP_CLAUSE_DEFAULT_UNSPECIFIED;
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ c;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      ਚੋਣ (p[0])
	{
	ਹਾਲਤ 'n':
	  ਜੇ (strcmp ("none", p) != 0)
	    ਜਾਓ invalid_ਕਿਸਮ;
	  ਕਿਸਮ = OMP_CLAUSE_DEFAULT_NONE;
	  ਰੋਕੋ;

	ਹਾਲਤ 'p':
	  ਜੇ (is_oacc)
	    {
	      ਜੇ (strcmp ("present", p) != 0)
		ਜਾਓ invalid_ਕਿਸਮ;
	      ਕਿਸਮ = OMP_CLAUSE_DEFAULT_PRESENT;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (strcmp ("private", p) != 0)
		ਜਾਓ invalid_ਕਿਸਮ;
	      ਕਿਸਮ = OMP_CLAUSE_DEFAULT_ਨਿੱਜੀ;
	    }
	  ਰੋਕੋ;

	ਹਾਲਤ 'f':
	  ਜੇ (strcmp ("firstprivate", p) != 0 || is_oacc)
	    ਜਾਓ invalid_ਕਿਸਮ;
	  ਕਿਸਮ = OMP_CLAUSE_DEFAULT_FIRSTPRIVATE;
	  ਰੋਕੋ;

	ਹਾਲਤ 's':
	  ਜੇ (strcmp ("shared", p) != 0 || is_oacc)
	    ਜਾਓ invalid_ਕਿਸਮ;
	  ਕਿਸਮ = OMP_CLAUSE_DEFAULT_SHARED;
	  ਰੋਕੋ;

	ਮੂਲ:
	  ਜਾਓ invalid_ਕਿਸਮ;
	}

      c_parser_consume_token (parser);
    }
  ਨਹੀਂਤਾਂ
    {
    invalid_ਕਿਸਮ:
      ਜੇ (is_oacc)
	c_parser_error (parser, "expected %<none%> or %<present%>");
      ਨਹੀਂਤਾਂ
	c_parser_error (parser, "expected %<none%>, %<shared%>, "
				"%<private%> or %<firstprivate%>");
    }
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਜੇ (ਕਿਸਮ == OMP_CLAUSE_DEFAULT_UNSPECIFIED)
    ਵਾਪਸ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEFAULT, "default");
  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULT);
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEFAULT_ਕਿਸਮ (c) = ਕਿਸਮ;

  ਵਾਪਸ c;
}

/* OpenMP 2.5:
   firstprivate ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_firstprivate (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_FIRSTPRIVATE, list);
}

/* OpenMP 3.1:
   final ( expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_final (c_parser *parser, ਰੁੱਖ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      ਰੁੱਖ t, c;
      ਜੇ (!parens.require_open (parser))
	t = error_mark_ਗੰਢ;
      ਨਹੀਂਤਾਂ
	{
	  location_t eloc = c_parser_peek_token (parser)->location;
	  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  t = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (eloc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
	  t = c_objc_common_truthvalue_conversion (eloc, t);
	  t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_FINAL, "final");

      c = build_omp_clause (loc, OMP_CLAUSE_FINAL);
      OMP_CLAUSE_FINAL_ਵਿਅੰਜਕ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }
  ਨਹੀਂਤਾਂ
    c_parser_error (parser, "expected %<(%>");

  ਵਾਪਸ list;
}

/* OpenMP 5.1:
   indirect [( expression )]
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਅਸਿੱਧਾ (c_parser *parser, ਰੁੱਖ list)
{
  location_t location = c_parser_peek_token (parser)->location;
  ਰੁੱਖ t;

  ਜੇ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      ਜੇ (!parens.require_open (parser))
	ਵਾਪਸ list;

      location_t loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);
      t = c_objc_common_truthvalue_conversion (loc, ਵਿਅੰਜਕ.ਮੁੱਲ);
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t))
	  || ਰੁੱਖ_ਕੋਡ (t) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected constant logical expression");
	  ਵਾਪਸ list;
	}
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਨਹੀਂਤਾਂ
    t = integer_one_ਗੰਢ;

  check_no_duplicate_clause (list, OMP_CLAUSE_ਅਸਿੱਧਾ, "indirect");

  ਰੁੱਖ c = build_omp_clause (location, OMP_CLAUSE_ਅਸਿੱਧਾ);
  OMP_CLAUSE_ਅਸਿੱਧਾ_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;

  ਵਾਪਸ c;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_if (c_parser *parser, ਰੁੱਖ list, ਤਾਰਕਿਕ is_omp)
{
  location_t location = c_parser_peek_token (parser)->location;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 if_modifier = ERROR_MARK;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (is_omp && c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਪੂਰਨ n = 2;
      ਜੇ (strcmp (p, "cancel") == 0)
	if_modifier = VOID_CST;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "parallel") == 0)
	if_modifier = OMP_PARALLEL;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "simd") == 0)
	if_modifier = OMP_SIMD;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "task") == 0)
	if_modifier = OMP_TASK;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "taskloop") == 0)
	if_modifier = OMP_TASKLOOP;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "target") == 0)
	{
	  if_modifier = OMP_ਨਿਸ਼ਾਨਾ;
	  ਜੇ (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	    {
	      p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_2nd_token (parser)->ਮੁੱਲ);
	      ਜੇ (strcmp ("data", p) == 0)
		if_modifier = OMP_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ;
	      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("update", p) == 0)
		if_modifier = OMP_ਨਿਸ਼ਾਨਾ_UPDATE;
	      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("enter", p) == 0)
		if_modifier = OMP_ਨਿਸ਼ਾਨਾ_ENTER_ਅੰਕੜੇ;
	      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("exit", p) == 0)
		if_modifier = OMP_ਨਿਸ਼ਾਨਾ_EXIT_ਅੰਕੜੇ;
	      ਜੇ (if_modifier != OMP_ਨਿਸ਼ਾਨਾ)
		{
		  n = 3;
		  c_parser_consume_token (parser);
		}
	      ਨਹੀਂਤਾਂ
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<data%>, %<update%>, %<enter%> "
				 "or %<exit%>");
		  if_modifier = ERROR_MARK;
		}
	      ਜੇ (if_modifier == OMP_ਨਿਸ਼ਾਨਾ_ENTER_ਅੰਕੜੇ
		  || if_modifier == OMP_ਨਿਸ਼ਾਨਾ_EXIT_ਅੰਕੜੇ)
		{
		  ਜੇ (c_parser_peek_2nd_token (parser)->type == CPP_NAME)
		    {
		      p = IDENTIFIER_ਸੂਚਕ
				(c_parser_peek_2nd_token (parser)->ਮੁੱਲ);
		      ਜੇ (strcmp ("data", p) == 0)
			n = 4;
		    }
		  ਜੇ (n == 4)
		    c_parser_consume_token (parser);
		  ਨਹੀਂਤਾਂ
		    {
		      location_t loc
			= c_parser_peek_2nd_token (parser)->location;
		      error_at (loc, "expected %<data%>");
		      if_modifier = ERROR_MARK;
		    }
		}
	    }
	}
      ਜੇ (if_modifier != ERROR_MARK)
	{
	  ਜੇ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (n > 2)
		{
		  location_t loc = c_parser_peek_2nd_token (parser)->location;
		  error_at (loc, "expected %<:%>");
		}
	      if_modifier = ERROR_MARK;
	    }
	}
    }

  location_t loc = c_parser_peek_token (parser)->location;
  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);
  ਰੁੱਖ t = c_objc_common_truthvalue_conversion (loc, ਵਿਅੰਜਕ.ਮੁੱਲ), c;
  t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਲਈ (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_IF)
      {
	ਜੇ (if_modifier != ERROR_MARK
	    && OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ਅਚਲ ਅੱਖਰ *p = ਨਿਰਾ;
	    ਚੋਣ (if_modifier)
	      {
	      ਹਾਲਤ VOID_CST: p = "cancel"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_PARALLEL: p = "parallel"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_SIMD: p = "simd"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_TASK: p = "task"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_TASKLOOP: p = "taskloop"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ: p = "target data"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_ਨਿਸ਼ਾਨਾ: p = "target"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_ਨਿਸ਼ਾਨਾ_UPDATE: p = "target update"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_ਨਿਸ਼ਾਨਾ_ENTER_ਅੰਕੜੇ: p = "target enter data"; ਰੋਕੋ;
	      ਹਾਲਤ OMP_ਨਿਸ਼ਾਨਾ_EXIT_ਅੰਕੜੇ: p = "target exit data"; ਰੋਕੋ;
	      ਮੂਲ: gcc_unreachable ();
	      }
	    error_at (location, "too many %<if%> clauses with %qs modifier",
		      p);
	    ਵਾਪਸ list;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_IF_MODIFIER (c) == if_modifier)
	  {
	    ਜੇ (!is_omp)
	      error_at (location, "too many %<if%> clauses");
	    ਨਹੀਂਤਾਂ
	      error_at (location, "too many %<if%> clauses without modifier");
	    ਵਾਪਸ list;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (if_modifier == ERROR_MARK
		 || OMP_CLAUSE_IF_MODIFIER (c) == ERROR_MARK)
	  {
	    error_at (location, "if any %<if%> clause has modifier, then all "
				"%<if%> clauses have to use modifier");
	    ਵਾਪਸ list;
	  }
      }

  c = build_omp_clause (location, OMP_CLAUSE_IF);
  OMP_CLAUSE_IF_MODIFIER (c) = if_modifier;
  OMP_CLAUSE_IF_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 2.5:
   lastprivate ( variable-list )

   OpenMP 5.0:
   lastprivate ( [ lastprivate-modifier : ] variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_lastprivate (c_parser *parser, ਰੁੱਖ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  ਜੇ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      ਤਾਰਕਿਕ conditional = ਝੂਠ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  ਅਚਲ ਅੱਖਰ *p
	    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	  ਜੇ (strcmp (p, "conditional") == 0)
	    {
	      conditional = ਸੱਚ;
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	}
      ਰੁੱਖ nlist = c_parser_omp_variable_list (parser, loc,
					       OMP_CLAUSE_LASTPRIVATE, list);
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ਜੇ (conditional)
	ਲਈ (ਰੁੱਖ c = nlist; c != list; c = OMP_CLAUSE_CHAIN (c))
	  OMP_CLAUSE_LASTPRIVATE_CONDITIONAL (c) = 1;
      ਵਾਪਸ nlist;
    }
  ਵਾਪਸ list;
}

/* OpenMP 3.1:
   mergeable */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_mergeable (c_parser *parser ATTRIBUTE_ਅਣਵਰਤਿਆ, ਰੁੱਖ list)
{
  ਰੁੱਖ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_MERGEABLE, "mergeable");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_MERGEABLE);
  OMP_CLAUSE_CHAIN (c) = list;

  ਵਾਪਸ c;
}

/* OpenMP 2.5:
   nowait */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_nowait (c_parser *parser ATTRIBUTE_ਅਣਵਰਤਿਆ, ਰੁੱਖ list)
{
  ਰੁੱਖ c;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_NOWAIT, "nowait");

  c = build_omp_clause (loc, OMP_CLAUSE_NOWAIT);
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 2.5:
   num_threads ( expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਅੰਕ_ਧਾਗੇ (c_parser *parser, ਰੁੱਖ list)
{
  location_t ਅੰਕ_ਧਾਗੇ_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ c, t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

      parens.skip_until_ਮਿਲਿਆ_close (parser);

      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ਵਾਪਸ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ਵਿਅੰਜਕ_loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, t,
		       build_int_cst (ਰੁੱਖ_TYPE (t), 0));
      protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (c, ਵਿਅੰਜਕ_loc);
      ਜੇ (c == boolean_true_ਗੰਢ)
	{
	  warning_at (ਵਿਅੰਜਕ_loc, OPT_Wopenmp,
		      "%<num_threads%> value must be positive");
	  t = integer_one_ਗੰਢ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ਅੰਕ_ਧਾਗੇ, "num_threads");

      c = build_omp_clause (ਅੰਕ_ਧਾਗੇ_loc, OMP_CLAUSE_ਅੰਕ_ਧਾਗੇ);
      OMP_CLAUSE_ਅੰਕ_ਧਾਗੇ_ਵਿਅੰਜਕ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenMP 4.5:
   num_tasks ( expression )

   OpenMP 5.1:
   num_tasks ( strict : expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਅੰਕ_tasks (c_parser *parser, ਰੁੱਖ list)
{
  location_t ਅੰਕ_tasks_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      ਤਾਰਕਿਕ strict = ਝੂਠ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ),
		     "strict") == 0)
	{
	  strict = ਸੱਚ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ c, t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

      parens.skip_until_ਮਿਲਿਆ_close (parser);

      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ਵਾਪਸ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ਵਿਅੰਜਕ_loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, t,
			   build_int_cst (ਰੁੱਖ_TYPE (t), 0));
      ਜੇ (CAN_HAVE_LOCATION_P (c))
	ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (c, ਵਿਅੰਜਕ_loc);
      ਜੇ (c == boolean_true_ਗੰਢ)
	{
	  warning_at (ਵਿਅੰਜਕ_loc, OPT_Wopenmp,
		      "%<num_tasks%> value must be positive");
	  t = integer_one_ਗੰਢ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ਅੰਕ_TASKS, "num_tasks");

      c = build_omp_clause (ਅੰਕ_tasks_loc, OMP_CLAUSE_ਅੰਕ_TASKS);
      OMP_CLAUSE_ਅੰਕ_TASKS_ਵਿਅੰਜਕ (c) = t;
      OMP_CLAUSE_ਅੰਕ_TASKS_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenMP 4.5:
   grainsize ( expression )

   OpenMP 5.1:
   grainsize ( strict : expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_grainsize (c_parser *parser, ਰੁੱਖ list)
{
  location_t grainsize_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      ਤਾਰਕਿਕ strict = ਝੂਠ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  && strcmp (IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ),
		     "strict") == 0)
	{
	  strict = ਸੱਚ;
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}

      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ c, t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

      parens.skip_until_ਮਿਲਿਆ_close (parser);

      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ਵਾਪਸ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ਵਿਅੰਜਕ_loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, t,
			   build_int_cst (ਰੁੱਖ_TYPE (t), 0));
      ਜੇ (CAN_HAVE_LOCATION_P (c))
	ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (c, ਵਿਅੰਜਕ_loc);
      ਜੇ (c == boolean_true_ਗੰਢ)
	{
	  warning_at (ਵਿਅੰਜਕ_loc, OPT_Wopenmp,
		      "%<grainsize%> value must be positive");
	  t = integer_one_ਗੰਢ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_GRAINSIZE, "grainsize");

      c = build_omp_clause (grainsize_loc, OMP_CLAUSE_GRAINSIZE);
      OMP_CLAUSE_GRAINSIZE_ਵਿਅੰਜਕ (c) = t;
      OMP_CLAUSE_GRAINSIZE_STRICT (c) = strict;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenMP 4.5:
   priority ( expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਤਰਜੀਹ (c_parser *parser, ਰੁੱਖ list)
{
  location_t ਤਰਜੀਹ_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ c, t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

      parens.skip_until_ਮਿਲਿਆ_close (parser);

      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ਵਾਪਸ list;
	}

      /* Attempt to statically determine when the number isn't
	 non-negative.  */
      c = fold_build2_loc (ਵਿਅੰਜਕ_loc, LT_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, t,
			   build_int_cst (ਰੁੱਖ_TYPE (t), 0));
      ਜੇ (CAN_HAVE_LOCATION_P (c))
	ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (c, ਵਿਅੰਜਕ_loc);
      ਜੇ (c == boolean_true_ਗੰਢ)
	{
	  warning_at (ਵਿਅੰਜਕ_loc, OPT_Wopenmp,
		      "%<priority%> value must be non-negative");
	  t = integer_one_ਗੰਢ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ਤਰਜੀਹ, "priority");

      c = build_omp_clause (ਤਰਜੀਹ_loc, OMP_CLAUSE_ਤਰਜੀਹ);
      OMP_CLAUSE_ਤਰਜੀਹ_ਵਿਅੰਜਕ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenMP 4.5:
   hint ( expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_hint (c_parser *parser, ਰੁੱਖ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ c, t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t))
	  || ਰੁੱਖ_ਕੋਡ (t) != INTEGER_CST
	  || ਰੁੱਖ_int_cst_sgn (t) == -1)
	{
	  c_parser_error (parser, "expected constant integer expression "
				  "with valid sync-hint value");
	  ਵਾਪਸ list;
	}
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_HINT, "hint");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_HINT);
      OMP_CLAUSE_HINT_ਵਿਅੰਜਕ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenMP 5.1:
   filter ( integer-expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_filter (c_parser *parser, ਰੁੱਖ list)
{
  location_t hint_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ c, t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ਵਾਪਸ list;
	}
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      check_no_duplicate_clause (list, OMP_CLAUSE_FILTER, "filter");

      c = build_omp_clause (hint_loc, OMP_CLAUSE_FILTER);
      OMP_CLAUSE_FILTER_ਵਿਅੰਜਕ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenMP 4.5:
   defaultmap ( tofrom : scalar )

   OpenMP 5.0:
   defaultmap ( implicit-behavior [ : variable-category ] ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_defaultmap (c_parser *parser, ਰੁੱਖ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ c;
  ਅਚਲ ਅੱਖਰ *p;
  ਗਿਣਤੀ omp_clause_defaultmap_ਕਿਸਮ behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
  ਗਿਣਤੀ omp_clause_defaultmap_ਕਿਸਮ category
    = OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_DEFAULT))
    p = "default";
  ਨਹੀਂਤਾਂ ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
    invalid_behavior:
      c_parser_error (parser, "expected %<alloc%>, %<to%>, %<from%>, "
			      "%<tofrom%>, %<firstprivate%>, %<none%> "
			      "or %<default%>");
      ਜਾਓ ਬਾਹਰਲਾ_err;
    }
  ਨਹੀਂਤਾਂ
    p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

  ਚੋਣ (p[0])
    {
    ਹਾਲਤ 'a':
      ਜੇ (strcmp ("alloc", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ALLOC;
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_behavior;
      ਰੋਕੋ;

    ਹਾਲਤ 'd':
      ਜੇ (strcmp ("default", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_DEFAULT;
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_behavior;
      ਰੋਕੋ;

    ਹਾਲਤ 'f':
      ਜੇ (strcmp ("firstprivate", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FIRSTPRIVATE;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("from", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_FROM;
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_behavior;
      ਰੋਕੋ;

    ਹਾਲਤ 'n':
      ਜੇ (strcmp ("none", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_NONE;
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_behavior;
      ਰੋਕੋ;

    ਹਾਲਤ 'p':
      ਜੇ (strcmp ("present", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_PRESENT;
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_behavior;
      ਰੋਕੋ;

    ਹਾਲਤ 't':
      ਜੇ (strcmp ("tofrom", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_TOFROM;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("to", p) == 0)
	behavior = OMP_CLAUSE_DEFAULTMAP_ਮੰਜ਼ਿਲ;
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_behavior;
      ਰੋਕੋ;

    ਮੂਲ:
      ਜਾਓ invalid_behavior;
    }
  c_parser_consume_token (parser);

  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
    {
      ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ਜਾਓ ਬਾਹਰਲਾ_err;
      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	invalid_category:
	  c_parser_error (parser, "expected %<scalar%>, %<aggregate%>, "
				  "%<pointer%> or %<all%>");
	  ਜਾਓ ਬਾਹਰਲਾ_err;
	}
      p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਚੋਣ (p[0])
	{
	ਹਾਲਤ 'a':
	  ਜੇ (strcmp ("aggregate", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE;
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp ("all", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL;
	  ਨਹੀਂਤਾਂ
	    ਜਾਓ invalid_category;
	  ਰੋਕੋ;

	ਹਾਲਤ 'p':
	  ਜੇ (strcmp ("pointer", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_ਸੂਚਕ;
	  ਨਹੀਂਤਾਂ
	    ਜਾਓ invalid_category;
	  ਰੋਕੋ;

	ਹਾਲਤ 's':
	  ਜੇ (strcmp ("scalar", p) == 0)
	    category = OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR;
	  ਨਹੀਂਤਾਂ
	    ਜਾਓ invalid_category;
	  ਰੋਕੋ;

	ਮੂਲ:
	  ਜਾਓ invalid_category;
	}

      c_parser_consume_token (parser);
    }
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਲਈ (c = list; c ; c = OMP_CLAUSE_CHAIN (c))
    ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEFAULTMAP
	&& (category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || category == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
	    || OMP_CLAUSE_DEFAULTMAP_CATEGORY (c) == category
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)
	    || (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		== OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL)))
      {
	ਗਿਣਤੀ omp_clause_defaultmap_ਕਿਸਮ cat = category;
	location_t loc = OMP_CLAUSE_LOCATION (c);
	ਜੇ (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED
	    || (cat == OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL
		&& (OMP_CLAUSE_DEFAULTMAP_CATEGORY (c)
		    != OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED)))
	  cat = OMP_CLAUSE_DEFAULTMAP_CATEGORY (c);
	p = ਨਿਰਾ;
	ਚੋਣ (cat)
	  {
	  ਹਾਲਤ OMP_CLAUSE_DEFAULTMAP_CATEGORY_UNSPECIFIED:
	    p = ਨਿਰਾ;
	    ਰੋਕੋ;
	  ਹਾਲਤ OMP_CLAUSE_DEFAULTMAP_CATEGORY_ALL:
	    p = "all";
	    ਰੋਕੋ;
	  ਹਾਲਤ OMP_CLAUSE_DEFAULTMAP_CATEGORY_AGGREGATE:
	    p = "aggregate";
	    ਰੋਕੋ;
	  ਹਾਲਤ OMP_CLAUSE_DEFAULTMAP_CATEGORY_ਸੂਚਕ:
	    p = "pointer";
	    ਰੋਕੋ;
	  ਹਾਲਤ OMP_CLAUSE_DEFAULTMAP_CATEGORY_SCALAR:
	    p = "scalar";
	    ਰੋਕੋ;
	  ਮੂਲ:
	    gcc_unreachable ();
	  }
	ਜੇ (p)
	  error_at (loc, "too many %<defaultmap%> clauses with %qs category",
		    p);
	ਨਹੀਂਤਾਂ
	  error_at (loc, "too many %<defaultmap%> clauses with unspecified "
			 "category");
	ਰੋਕੋ;
      }

  c = build_omp_clause (loc, OMP_CLAUSE_DEFAULTMAP);
  OMP_CLAUSE_DEFAULTMAP_ਸੈੱਟ_ਕਿਸਮ (c, behavior, category);
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;

 ਬਾਹਰਲਾ_err:
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ list;
}

/* OpenACC 2.0:
   use_device ( variable-list )

   OpenMP 4.5:
   use_device_ptr ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_use_device_ptr (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_PTR,
				       list);
}

/* OpenMP 5.0:
   use_device_addr ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_use_device_addr (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE_DEVICE_ADDR,
				       list);
}

/* OpenMP 5.1:
   has_device_addr ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_has_device_addr (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_HAS_DEVICE_ADDR,
				       list);
}

/* OpenMP 4.5:
   is_device_ptr ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_is_device_ptr (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_IS_DEVICE_PTR, list);
}

/* OpenACC:
   num_gangs ( expression )
   num_workers ( expression )
   vector_length ( expression )  */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_single_int_clause (c_parser *parser, omp_clause_ਕੋਡ ਕੋਡ,
				 ਰੁੱਖ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
  ਰੁੱਖ c, t = ਵਿਅੰਜਕ.ਮੁੱਲ;
  t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਜੇ (t == error_mark_ਗੰਢ)
    ਵਾਪਸ list;
  ਨਹੀਂਤਾਂ ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
    {
      error_at (ਵਿਅੰਜਕ_loc, "%qs expression must be integral",
		omp_clause_ਕੋਡ_name[ਕੋਡ]);
      ਵਾਪਸ list;
    }

  /* Attempt to statically determine when the number isn't positive.  */
  c = fold_build2_loc (ਵਿਅੰਜਕ_loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, t,
		       build_int_cst (ਰੁੱਖ_TYPE (t), 0));
  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (c, ਵਿਅੰਜਕ_loc);
  ਜੇ (c == boolean_true_ਗੰਢ)
    {
      warning_at (ਵਿਅੰਜਕ_loc, 0,
		  "%qs value must be positive",
		  omp_clause_ਕੋਡ_name[ਕੋਡ]);
      t = integer_one_ਗੰਢ;
    }

  check_no_duplicate_clause (list, ਕੋਡ, omp_clause_ਕੋਡ_name[ਕੋਡ]);

  c = build_omp_clause (loc, ਕੋਡ);
  OMP_CLAUSE_ਸੰਕਾਰਜ (c, 0) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_shape_clause (c_parser *parser, location_t loc,
			    omp_clause_ਕੋਡ ਕਿਸਮ,
			    ਅਚਲ ਅੱਖਰ *str, ਰੁੱਖ list)
{
  ਅਚਲ ਅੱਖਰ *id = "num";
  ਰੁੱਖ ops[2] = { NULL_ਰੁੱਖ, NULL_ਰੁੱਖ }, c;

  ਜੇ (ਕਿਸਮ == OMP_CLAUSE_ਸਦਿਸ਼)
    id = "length";

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);

      ਕਰੋ
	{
	  c_token *ਅਗਲਾ = c_parser_peek_token (parser);
	  ਪੂਰਨ idx = 0;

	  /* Gang static argument.  */
	  ਜੇ (ਕਿਸਮ == OMP_CLAUSE_GANG
	      && c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_STATIC))
	    {
	      c_parser_consume_token (parser);

	      ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
		ਜਾਓ cleanup_error;

	      idx = 1;
	      ਜੇ (ops[idx] != NULL_ਰੁੱਖ)
		{
		  c_parser_error (parser, "too many %<static%> arguments");
		  ਜਾਓ cleanup_error;
		}

	      /* Check for the '*' argument.  */
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_MULT)
		  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
		      || c_parser_peek_2nd_token (parser)->type
		         == CPP_CLOSE_PAREN))
		{
		  c_parser_consume_token (parser);
		  ops[idx] = integer_minus_one_ਗੰਢ;

		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		    {
		      c_parser_consume_token (parser);
		      ਜਾਰੀ;
		    }
		  ਨਹੀਂਤਾਂ
		    ਰੋਕੋ;
		}
	    }
	  /* Worker num: argument and vector length: arguments.  */
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
		   && strcmp (id, IDENTIFIER_ਸੂਚਕ (ਅਗਲਾ->ਮੁੱਲ)) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_consume_token (parser);  /* id  */
	      c_parser_consume_token (parser);  /* ':'  */
	    }

	  /* Now collect the actual argument.  */
	  ਜੇ (ops[idx] != NULL_ਰੁੱਖ)
	    {
	      c_parser_error (parser, "unexpected argument");
	      ਜਾਓ cleanup_error;
	    }

	  location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
	  c_ਵਿਅੰਜਕ cexpr = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  cexpr = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, cexpr, ਝੂਠ, ਸੱਚ);
	  ਰੁੱਖ ਵਿਅੰਜਕ = cexpr.ਮੁੱਲ;
	  ਜੇ (ਵਿਅੰਜਕ == error_mark_ਗੰਢ)
	    ਜਾਓ cleanup_error;

	  ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ, ਝੂਠ, ਨਿਰਾ);

	  /* Attempt to statically determine when the number isn't a
	     positive integer.  */

	  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
	    {
	      c_parser_error (parser, "expected integer expression");
	      ਵਾਪਸ list;
	    }

	  ਰੁੱਖ c = fold_build2_loc (ਵਿਅੰਜਕ_loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, ਵਿਅੰਜਕ,
				    build_int_cst (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), 0));
	  ਜੇ (c == boolean_true_ਗੰਢ)
	    {
	      warning_at (loc, 0,
			  "%qs value must be positive", str);
	      ਵਿਅੰਜਕ = integer_one_ਗੰਢ;
	    }

	  ops[idx] = ਵਿਅੰਜਕ;

	  ਜੇ (ਕਿਸਮ == OMP_CLAUSE_GANG
	      && c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ਜਾਰੀ;
	    }
	  ਰੋਕੋ;
	}
      ਜਦੋਂ (1);

      ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ਜਾਓ cleanup_error;
    }

  check_no_duplicate_clause (list, ਕਿਸਮ, str);

  c = build_omp_clause (loc, ਕਿਸਮ);

  ਜੇ (ops[1])
    OMP_CLAUSE_ਸੰਕਾਰਜ (c, 1) = ops[1];

  OMP_CLAUSE_ਸੰਕਾਰਜ (c, 0) = ops[0];
  OMP_CLAUSE_CHAIN (c) = list;

  ਵਾਪਸ c;

 cleanup_error:
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, 0);
  ਵਾਪਸ list;
}

/* OpenACC 2.5:
   auto
   finalize
   independent
   nohost
   seq */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_simple_clause (location_t loc, ਗਿਣਤੀ omp_clause_ਕੋਡ ਕੋਡ,
			     ਰੁੱਖ list)
{
  check_no_duplicate_clause (list, ਕੋਡ, omp_clause_ਕੋਡ_name[ਕੋਡ]);

  ਰੁੱਖ c = build_omp_clause (loc, ਕੋਡ);
  OMP_CLAUSE_CHAIN (c) = list;

  ਵਾਪਸ c;
}

/* OpenACC:
   async [( int-expr )] */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_clause_async (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ c, t;
  location_t loc = c_parser_peek_token (parser)->location;

  t = build_int_cst (integer_type_ਗੰਢ, GOMP_ASYNC_NOVAL);

  ਜੇ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      c_parser_consume_token (parser);

      t = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
	c_parser_error (parser, "expected integer expression");
      ਨਹੀਂਤਾਂ ਜੇ (t == error_mark_ਗੰਢ
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ਵਾਪਸ list;
    }
  ਨਹੀਂਤਾਂ
    t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

  check_no_duplicate_clause (list, OMP_CLAUSE_ASYNC, "async");

  c = build_omp_clause (loc, OMP_CLAUSE_ASYNC);
  OMP_CLAUSE_ASYNC_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ਵਾਪਸ list;
}

/* OpenACC 2.0:
   tile ( size-expr-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_clause_tile (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ c, ਵਿਅੰਜਕ = error_mark_ਗੰਢ;
  location_t loc;
  ਰੁੱਖ tile = NULL_ਰੁੱਖ;

  check_no_duplicate_clause (list, OMP_CLAUSE_TILE, "tile");
  check_no_duplicate_clause (list, OMP_CLAUSE_COLLAPSE, "collapse");

  loc = c_parser_peek_token (parser)->location;
  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ਵਾਪਸ list;

  ਕਰੋ
    {
      ਜੇ (tile && !c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
	ਵਾਪਸ list;

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_MULT)
	  && (c_parser_peek_2nd_token (parser)->type == CPP_COMMA
	      || c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_PAREN))
	{
	  c_parser_consume_token (parser);
	  ਵਿਅੰਜਕ = integer_zero_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ
	{
	  location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
	  c_ਵਿਅੰਜਕ cexpr = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  cexpr = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, cexpr, ਝੂਠ, ਸੱਚ);
	  ਵਿਅੰਜਕ = cexpr.ਮੁੱਲ;

	  ਜੇ (ਵਿਅੰਜਕ == error_mark_ਗੰਢ)
	    {
	      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      ਵਾਪਸ list;
	    }

	  ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ, ਝੂਠ, ਨਿਰਾ);

	  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
	      || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_shwi_p (ਵਿਅੰਜਕ)
	      || ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (ਵਿਅੰਜਕ) <= 0)
	    {
	      error_at (ਵਿਅੰਜਕ_loc, "%<tile%> argument needs positive"
			" integral constant");
	      ਵਿਅੰਜਕ = integer_zero_ਗੰਢ;
	    }
	}

      tile = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, ਵਿਅੰਜਕ, tile);
    }
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_CLOSE_PAREN));

  /* Consume the trailing ')'.  */
  c_parser_consume_token (parser);

  c = build_omp_clause (loc, OMP_CLAUSE_TILE);
  tile = nreverse (tile);
  OMP_CLAUSE_TILE_LIST (c) = tile;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenACC:
   wait [( int-expr-list )] */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_clause_wait (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;

  ਜੇ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, clause_loc, list);
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ c = build_omp_clause (clause_loc, OMP_CLAUSE_WAIT);

      OMP_CLAUSE_DECL (c) = build_int_cst (integer_type_ਗੰਢ, GOMP_ASYNC_NOVAL);
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenACC 2.7:
   self [( expression )] */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_compute_clause_self (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ t;
  location_t location = c_parser_peek_token (parser)->location;
  ਜੇ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    {
      matching_parens parens;
      parens.consume_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);
      t = c_objc_common_truthvalue_conversion (loc, ਵਿਅੰਜਕ.ਮੁੱਲ);
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਨਹੀਂਤਾਂ
    t = truthvalue_true_ਗੰਢ;

  ਲਈ (ਰੁੱਖ c = list; c; c = OMP_CLAUSE_CHAIN (c))
    ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_SELF)
      {
	error_at (location, "too many %<self%> clauses");
	ਵਾਪਸ list;
      }

  ਰੁੱਖ c = build_omp_clause (location, OMP_CLAUSE_SELF);
  OMP_CLAUSE_SELF_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 5.0:
   order ( concurrent )

   OpenMP 5.1:
   order ( order-modifier : concurrent )

   order-modifier:
     reproducible
     unconstrained  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਕ੍ਰਮ (c_parser *parser, ਰੁੱਖ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ c;
  ਅਚਲ ਅੱਖਰ *p;
  ਤਾਰਕਿਕ unconstrained = ਝੂਠ;
  ਤਾਰਕਿਕ reproducible = ਝੂਠ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "unconstrained") == 0)
	unconstrained = ਸੱਚ;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "reproducible") == 0)
	reproducible = ਸੱਚ;
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected %<reproducible%> or "
				  "%<unconstrained%>");
	  ਜਾਓ ਬਾਹਰਲਾ_err;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<concurrent%>");
      ਜਾਓ ਬਾਹਰਲਾ_err;
    }
  p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
  ਜੇ (strcmp (p, "concurrent") != 0)
    {
      c_parser_error (parser, "expected %<concurrent%>");
      ਜਾਓ ਬਾਹਰਲਾ_err;
    }
  c_parser_consume_token (parser);
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  check_no_duplicate_clause (list, OMP_CLAUSE_ਕ੍ਰਮ, "order");
  c = build_omp_clause (loc, OMP_CLAUSE_ਕ੍ਰਮ);
  OMP_CLAUSE_ਕ੍ਰਮ_UNCONSTRAINED (c) = unconstrained;
  OMP_CLAUSE_ਕ੍ਰਮ_REPRODUCIBLE (c) = reproducible;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;

 ਬਾਹਰਲਾ_err:
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ list;
}


/* OpenMP 5.0:
   bind ( teams | parallel | thread ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_bind (c_parser *parser, ਰੁੱਖ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ c;
  ਅਚਲ ਅੱਖਰ *p;
  ਗਿਣਤੀ omp_clause_bind_ਕਿਸਮ ਕਿਸਮ = OMP_CLAUSE_BIND_THREAD;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
     invalid:
      c_parser_error (parser,
		      "expected %<teams%>, %<parallel%> or %<thread%>");
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਵਾਪਸ list;
    }
  p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
  ਜੇ (strcmp (p, "teams") == 0)
    ਕਿਸਮ = OMP_CLAUSE_BIND_TEAMS;
  ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "parallel") == 0)
    ਕਿਸਮ = OMP_CLAUSE_BIND_PARALLEL;
  ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "thread") != 0)
    ਜਾਓ invalid;
  c_parser_consume_token (parser);
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  /* check_no_duplicate_clause (list, OMP_CLAUSE_BIND, "bind"); */
  c = build_omp_clause (loc, OMP_CLAUSE_BIND);
  OMP_CLAUSE_BIND_ਕਿਸਮ (c) = ਕਿਸਮ;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}


/* OpenMP 2.5:
   ordered

   OpenMP 4.5:
   ordered ( constant-expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ordered (c_parser *parser, ਰੁੱਖ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ORDERED, "ordered");

  ਰੁੱਖ c, ਅੰਕ = NULL_ਰੁੱਖ;
  HOST_WIDE_INT n;
  location_t loc = c_parser_peek_token (parser)->location;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      ਅੰਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਜੇ (ਅੰਕ == error_mark_ਗੰਢ)
    ਵਾਪਸ list;
  ਜੇ (ਅੰਕ)
    {
      mark_exp_read (ਅੰਕ);
      ਅੰਕ = c_fully_fold (ਅੰਕ, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਅੰਕ))
	  || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_shwi_p (ਅੰਕ)
	  || (n = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (ਅੰਕ)) <= 0
	  || (ਪੂਰਨ) n != n)
	{
	  error_at (loc, "ordered argument needs positive "
			 "constant integer expression");
	  ਵਾਪਸ list;
	}
    }
  c = build_omp_clause (loc, OMP_CLAUSE_ORDERED);
  OMP_CLAUSE_ORDERED_ਵਿਅੰਜਕ (c) = ਅੰਕ;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 2.5:
   private ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਨਿੱਜੀ (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ਨਿੱਜੀ, list);
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_reduction (c_parser *parser, ਗਿਣਤੀ omp_clause_ਕੋਡ ਕਿਸਮ,
			       ਤਾਰਕਿਕ is_omp, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      ਤਾਰਕਿਕ task = ਝੂਠ;
      ਤਾਰਕਿਕ inscan = ਝੂਠ;
      ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ERROR_MARK;
      ਰੁੱਖ reduc_id = NULL_ਰੁੱਖ;

      ਜੇ (ਕਿਸਮ == OMP_CLAUSE_REDUCTION && is_omp)
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_DEFAULT)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
		   && c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
	    {
	      ਅਚਲ ਅੱਖਰ *p
		= IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	      ਜੇ (strcmp (p, "task") == 0)
		task = ਸੱਚ;
	      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "inscan") == 0)
		inscan = ਸੱਚ;
	      ਜੇ (task || inscan)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		}
	    }
	}

      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_PLUS:
	  ਕੋਡ = PLUS_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_MULT:
	  ਕੋਡ = MULT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_MINUS:
	  ਜੇ (is_omp)
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      gcc_rich_location richloc (loc);
	      richloc.ਜੋੜੋ_fixit_replace ("+");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<-%> operator for reductions deprecated in "
			  "OpenMP 5.2");
	    }
	  ਕੋਡ = MINUS_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_AND:
	  ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_XOR:
	  ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_OR:
	  ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_AND_AND:
	  ਕੋਡ = TRUTH_ANDIF_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_OR_OR:
	  ਕੋਡ = TRUTH_ORIF_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
        ਹਾਲਤ CPP_NAME:
	  {
	    ਅਚਲ ਅੱਖਰ *p
	      = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	    ਜੇ (strcmp (p, "min") == 0)
	      {
		ਕੋਡ = MIN_ਵਿਅੰਜਕ;
		ਰੋਕੋ;
	      }
	    ਜੇ (strcmp (p, "max") == 0)
	      {
		ਕੋਡ = MAX_ਵਿਅੰਜਕ;
		ਰੋਕੋ;
	      }
	    reduc_id = c_parser_peek_token (parser)->ਮੁੱਲ;
	    ਰੋਕੋ;
	  }
	ਮੂਲ:
	  c_parser_error (parser,
			  "expected %<+%>, %<*%>, %<-%>, %<&%>, "
			  "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, 0);
	  ਵਾਪਸ list;
	}
      c_parser_consume_token (parser);
      reduc_id = c_omp_reduction_id (ਕੋਡ, reduc_id);
      ਜੇ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  ਰੁੱਖ nl, c;

	  nl = c_parser_omp_variable_list (parser, clause_loc, ਕਿਸਮ, list);
	  ਲਈ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    {
	      ਰੁੱਖ d = OMP_CLAUSE_DECL (c), type;
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (d) != OMP_ARRAY_SECTION)
		type = ਰੁੱਖ_TYPE (d);
	      ਨਹੀਂਤਾਂ
		{
		  ਪੂਰਨ cnt = 0;
		  ਰੁੱਖ t;
		  ਲਈ (t = d;
		      ਰੁੱਖ_ਕੋਡ (t) == OMP_ARRAY_SECTION;
		      t = ਰੁੱਖ_ਸੰਕਾਰਜ (t, 0))
		    cnt++;
		  type = ਰੁੱਖ_TYPE (t);
		  ਜਦੋਂ (cnt > 0)
		    {
		      ਜੇ (ਰੁੱਖ_ਕੋਡ (type) != ਸੂਚਕ_TYPE
			  && ਰੁੱਖ_ਕੋਡ (type) != ARRAY_TYPE)
			ਰੋਕੋ;
		      type = ਰੁੱਖ_TYPE (type);
		      cnt--;
		    }
		}
	      ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
		type = ਰੁੱਖ_TYPE (type);
	      OMP_CLAUSE_REDUCTION_ਕੋਡ (c) = ਕੋਡ;
	      ਜੇ (task)
		OMP_CLAUSE_REDUCTION_TASK (c) = 1;
	      ਨਹੀਂਤਾਂ ਜੇ (inscan)
		OMP_CLAUSE_REDUCTION_INSCAN (c) = 1;
	      ਜੇ (ਕੋਡ == ERROR_MARK
		  || !(INTEGRAL_TYPE_P (type)
		       || SCALAR_FLOAT_TYPE_P (type)
		       || ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE))
		OMP_CLAUSE_REDUCTION_PLACEHOLDER (c)
		  = c_omp_reduction_lookup (reduc_id,
					    TYPE_MAIN_VARIANT (type));
	    }

	  list = nl;
	}
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਵਾਪਸ list;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਸਮਾਂ_ਸਾਰਣੀ (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ c, t;
  location_t loc = c_parser_peek_token (parser)->location;
  ਪੂਰਨ modifiers = 0, nmodifiers = 0;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  c = build_omp_clause (loc, OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ);

  location_t comma = UNKNOWN_LOCATION;
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਰੁੱਖ ਕਿਸਮ = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (ਕਿਸਮ);
      ਜੇ (strcmp ("simd", p) == 0)
	OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_SIMD (c) = 1;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("monotonic", p) == 0)
	modifiers |= OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_MONOTONIC;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("nonmonotonic", p) == 0)
	modifiers |= OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_NONMONOTONIC;
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
      comma = UNKNOWN_LOCATION;
      c_parser_consume_token (parser);
      ਜੇ (nmodifiers++ == 0
	  && c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	{
	  comma = c_parser_peek_token (parser)->location;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_require (parser, CPP_COLON, "expected %<:%>");
	  ਰੋਕੋ;
	}
    }
  ਜੇ (comma != UNKNOWN_LOCATION)
    error_at (comma, "expected %<:%>");

  ਜੇ ((modifiers & (OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_MONOTONIC
		    | OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_NONMONOTONIC))
      == (OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_MONOTONIC
	  | OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_NONMONOTONIC))
    {
      error_at (loc, "both %<monotonic%> and %<nonmonotonic%> modifiers "
		     "specified");
      modifiers = 0;
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਰੁੱਖ ਕਿਸਮ = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (ਕਿਸਮ);

      ਚੋਣ (p[0])
	{
	ਹਾਲਤ 'd':
	  ਜੇ (strcmp ("dynamic", p) != 0)
	    ਜਾਓ invalid_ਕਿਸਮ;
	  OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c) = OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_DYNAMIC;
	  ਰੋਕੋ;

        ਹਾਲਤ 'g':
	  ਜੇ (strcmp ("guided", p) != 0)
	    ਜਾਓ invalid_ਕਿਸਮ;
	  OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c) = OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_GUIDED;
	  ਰੋਕੋ;

	ਹਾਲਤ 'r':
	  ਜੇ (strcmp ("runtime", p) != 0)
	    ਜਾਓ invalid_ਕਿਸਮ;
	  OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c) = OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_RUNTIME;
	  ਰੋਕੋ;

	ਮੂਲ:
	  ਜਾਓ invalid_ਕਿਸਮ;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_STATIC))
    OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c) = OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_STATIC;
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_AUTO))
    OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c) = OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_AUTO;
  ਨਹੀਂਤਾਂ
    ਜਾਓ invalid_ਕਿਸਮ;

  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    {
      location_t ਇੱਥੇ;
      c_parser_consume_token (parser);

      ਇੱਥੇ = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਇੱਥੇ, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

      ਜੇ (OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c) == OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_RUNTIME)
	error_at (ਇੱਥੇ, "schedule %<runtime%> does not take "
		  "a %<chunk_size%> parameter");
      ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c) == OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_AUTO)
	error_at (ਇੱਥੇ,
		  "schedule %<auto%> does not take "
		  "a %<chunk_size%> parameter");
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) == INTEGER_TYPE
	       || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (t)) == BITINT_TYPE)
	{
	  /* Attempt to statically determine when the number isn't
	     positive.  */
	  ਰੁੱਖ s = fold_build2_loc (loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, t,
				    build_int_cst (ਰੁੱਖ_TYPE (t), 0));
	  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (s, loc);
	  ਜੇ (s == boolean_true_ਗੰਢ)
	    {
	      warning_at (loc, OPT_Wopenmp,
			  "chunk size value must be positive");
	      t = integer_one_ਗੰਢ;
	    }
	  OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_CHUNK_ਵਿਅੰਜਕ (c) = t;
	}
      ਨਹੀਂਤਾਂ
	c_parser_error (parser, "expected integer expression");

      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਨਹੀਂਤਾਂ
    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c)
    = (ਗਿਣਤੀ omp_clause_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ)
      (OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ_ਕਿਸਮ (c) | modifiers);

  check_no_duplicate_clause (list, OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ, "schedule");
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;

 invalid_ਕਿਸਮ:
  c_parser_error (parser, "invalid schedule kind");
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, 0);
  ਵਾਪਸ list;
}

/* OpenMP 2.5:
   shared ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_shared (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_SHARED, list);
}

/* OpenMP 3.0:
   untied */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_untied (c_parser *parser ATTRIBUTE_ਅਣਵਰਤਿਆ, ਰੁੱਖ list)
{
  ਰੁੱਖ c;

  /* FIXME: Should we allow duplicates?  */
  check_no_duplicate_clause (list, OMP_CLAUSE_UNTIED, "untied");

  c = build_omp_clause (c_parser_peek_token (parser)->location,
			OMP_CLAUSE_UNTIED);
  OMP_CLAUSE_CHAIN (c) = list;

  ਵਾਪਸ c;
}

/* OpenMP 4.0:
   inbranch
   notinbranch */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_branch (c_parser *parser ATTRIBUTE_ਅਣਵਰਤਿਆ,
			    ਗਿਣਤੀ omp_clause_ਕੋਡ ਕੋਡ, ਰੁੱਖ list)
{
  check_no_duplicate_clause (list, ਕੋਡ, omp_clause_ਕੋਡ_name[ਕੋਡ]);

  ਰੁੱਖ c = build_omp_clause (c_parser_peek_token (parser)->location, ਕੋਡ);
  OMP_CLAUSE_CHAIN (c) = list;

  ਵਾਪਸ c;
}

/* OpenMP 4.0:
   parallel
   for
   sections
   taskgroup */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_cancelkind (c_parser *parser ATTRIBUTE_ਅਣਵਰਤਿਆ,
				ਗਿਣਤੀ omp_clause_ਕੋਡ ਕੋਡ, ਰੁੱਖ list)
{
  ਰੁੱਖ c = build_omp_clause (c_parser_peek_token (parser)->location, ਕੋਡ);
  OMP_CLAUSE_CHAIN (c) = list;

  ਵਾਪਸ c;
}

/* OpenMP 4.5:
   nogroup */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_nogroup (c_parser *parser ATTRIBUTE_ਅਣਵਰਤਿਆ, ਰੁੱਖ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_NOGROUP, "nogroup");
  ਰੁੱਖ c = build_omp_clause (c_parser_peek_token (parser)->location,
			     OMP_CLAUSE_NOGROUP);
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 4.5:
   simd
ਧਾਗੇ*/

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_orderedkind (c_parser *parser ATTRIBUTE_ਅਣਵਰਤਿਆ,
				 ਗਿਣਤੀ omp_clause_ਕੋਡ ਕੋਡ, ਰੁੱਖ list)
{
  check_no_duplicate_clause (list, ਕੋਡ, omp_clause_ਕੋਡ_name[ਕੋਡ]);
  ਰੁੱਖ c = build_omp_clause (c_parser_peek_token (parser)->location, ਕੋਡ);
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 4.0:
   num_teams ( expression )

   OpenMP 5.1:
   num_teams ( expression : expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਅੰਕ_teams (c_parser *parser, ਰੁੱਖ list)
{
  location_t ਅੰਕ_teams_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      location_t ਉੱਤਲਾ_loc = c_parser_peek_token (parser)->location;
      location_t ਹੇਠਲਾ_loc = UNKNOWN_LOCATION;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਉੱਤਲਾ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ c, ਉੱਤਲਾ = ਵਿਅੰਜਕ.ਮੁੱਲ, ਹੇਠਲਾ = NULL_ਰੁੱਖ;
      ਉੱਤਲਾ = c_fully_fold (ਉੱਤਲਾ, ਝੂਠ, ਨਿਰਾ);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  ਹੇਠਲਾ_loc = ਉੱਤਲਾ_loc;
	  ਹੇਠਲਾ = ਉੱਤਲਾ;
	  ਉੱਤਲਾ_loc = c_parser_peek_token (parser)->location;
	  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਉੱਤਲਾ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
	  ਉੱਤਲਾ = ਵਿਅੰਜਕ.ਮੁੱਲ;
	  ਉੱਤਲਾ = c_fully_fold (ਉੱਤਲਾ, ਝੂਠ, ਨਿਰਾ);
	}

      parens.skip_until_ਮਿਲਿਆ_close (parser);

      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਉੱਤਲਾ))
	  || (ਹੇਠਲਾ && !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਹੇਠਲਾ))))
	{
	  c_parser_error (parser, "expected integer expression");
	  ਵਾਪਸ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ਉੱਤਲਾ_loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, ਉੱਤਲਾ,
			   build_int_cst (ਰੁੱਖ_TYPE (ਉੱਤਲਾ), 0));
      protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (c, ਉੱਤਲਾ_loc);
      ਜੇ (c == boolean_true_ਗੰਢ)
	{
	  warning_at (ਉੱਤਲਾ_loc, OPT_Wopenmp,
		      "%<num_teams%> value must be positive");
	  ਉੱਤਲਾ = integer_one_ਗੰਢ;
	}
      ਜੇ (ਹੇਠਲਾ)
	{
	  c = fold_build2_loc (ਹੇਠਲਾ_loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, ਹੇਠਲਾ,
			       build_int_cst (ਰੁੱਖ_TYPE (ਹੇਠਲਾ), 0));
	  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (c, ਹੇਠਲਾ_loc);
	  ਜੇ (c == boolean_true_ਗੰਢ)
	    {
	      warning_at (ਹੇਠਲਾ_loc, OPT_Wopenmp,
			  "%<num_teams%> value must be positive");
	      ਹੇਠਲਾ = NULL_ਰੁੱਖ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਹੇਠਲਾ) == INTEGER_CST
		   && ਰੁੱਖ_ਕੋਡ (ਉੱਤਲਾ) == INTEGER_CST
		   && ਰੁੱਖ_int_cst_lt (ਉੱਤਲਾ, ਹੇਠਲਾ))
	    {
	      warning_at (ਹੇਠਲਾ_loc, OPT_Wopenmp,
			  "%<num_teams%> lower bound %qE bigger than upper "
			  "bound %qE", ਹੇਠਲਾ, ਉੱਤਲਾ);
	      ਹੇਠਲਾ = NULL_ਰੁੱਖ;
	    }
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_ਅੰਕ_TEAMS, "num_teams");

      c = build_omp_clause (ਅੰਕ_teams_loc, OMP_CLAUSE_ਅੰਕ_TEAMS);
      OMP_CLAUSE_ਅੰਕ_TEAMS_ਉੱਤਲਾ_ਵਿਅੰਜਕ (c) = ਉੱਤਲਾ;
      OMP_CLAUSE_ਅੰਕ_TEAMS_ਹੇਠਲਾ_ਵਿਅੰਜਕ (c) = ਹੇਠਲਾ;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenMP 4.0:
   thread_limit ( expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_thread_ਹੱਦਬੰਦੀ (c_parser *parser, ਰੁੱਖ list)
{
  location_t ਅੰਕ_thread_ਹੱਦਬੰਦੀ_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ c, t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

      parens.skip_until_ਮਿਲਿਆ_close (parser);

      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
	{
	  c_parser_error (parser, "expected integer expression");
	  ਵਾਪਸ list;
	}

      /* Attempt to statically determine when the number isn't positive.  */
      c = fold_build2_loc (ਵਿਅੰਜਕ_loc, LE_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, t,
			   build_int_cst (ਰੁੱਖ_TYPE (t), 0));
      protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (c, ਵਿਅੰਜਕ_loc);
      ਜੇ (c == boolean_true_ਗੰਢ)
	{
	  warning_at (ਵਿਅੰਜਕ_loc, OPT_Wopenmp,
		      "%<thread_limit%> value must be positive");
	  t = integer_one_ਗੰਢ;
	}

      check_no_duplicate_clause (list, OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ,
				 "thread_limit");

      c = build_omp_clause (ਅੰਕ_thread_ਹੱਦਬੰਦੀ_loc, OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ);
      OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ_ਵਿਅੰਜਕ (c) = t;
      OMP_CLAUSE_CHAIN (c) = list;
      list = c;
    }

  ਵਾਪਸ list;
}

/* OpenMP 4.0:
   aligned ( variable-list )
   aligned ( variable-list : constant-expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_aligned (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ nl, c;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALIGNED, list);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਰੁੱਖ alignment = ਵਿਅੰਜਕ.ਮੁੱਲ;
      alignment = c_fully_fold (alignment, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (alignment) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (alignment))
	  || ਰੁੱਖ_int_cst_sgn (alignment) != 1)
	{
	  error_at (clause_loc, "%<aligned%> clause alignment expression must "
				"be positive constant integer expression");
	  alignment = NULL_ਰੁੱਖ;
	}

      ਲਈ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	OMP_CLAUSE_ALIGNED_ALIGNMENT (c) = alignment;
    }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ nl;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_allocate (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ nl, c;
  ਰੁੱਖ allocator = NULL_ਰੁੱਖ;
  ਰੁੱਖ align = NULL_ਰੁੱਖ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ ((c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME)
       && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_KEYWORD))
      || (c_parser_peek_2nd_token (parser)->type != CPP_COMMA
	  && c_parser_peek_2nd_token (parser)->type != CPP_CLOSE_PAREN))
    {
      ਤਾਰਕਿਕ has_modifiers = ਝੂਠ;
      ਰੁੱਖ orig_type = NULL_ਰੁੱਖ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n = 3;
	  ਅਚਲ ਅੱਖਰ *p
	    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	  ਜੇ ((strcmp (p, "allocator") == 0 || strcmp (p, "align") == 0)
	      && c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN))
	    {
	      ਜੇ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON)
		has_modifiers = ਸੱਚ;
	      ਨਹੀਂਤਾਂ ਜੇ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA
		       && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			   == CPP_NAME)
		       && (c_parser_peek_nth_token_raw (parser, n + 3)->type
			   == CPP_OPEN_PAREN))
		{
		  c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
		  ਅਚਲ ਅੱਖਰ *q = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
		  n += 4;
		  ਜੇ ((strcmp (q, "allocator") == 0
		       || strcmp (q, "align") == 0)
		      && c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser,
								     &n)
		      && (c_parser_peek_nth_token_raw (parser, n)->type
			  == CPP_CLOSE_PAREN)
		      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
			  == CPP_COLON))
		    has_modifiers = ਸੱਚ;
		}
	    }
	  ਜੇ (has_modifiers)
	    {
	      c_parser_consume_token (parser);
	      matching_parens parens2;
	      parens2.require_open (parser);
	      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
	      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
	      ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
		;
	      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "allocator") == 0)
		{
		  allocator = ਵਿਅੰਜਕ.ਮੁੱਲ;
		  allocator = c_fully_fold (allocator, ਝੂਠ, ਨਿਰਾ);
		  orig_type = ਵਿਅੰਜਕ.original_type
			      ? ਵਿਅੰਜਕ.original_type : ਰੁੱਖ_TYPE (allocator);
		  orig_type = TYPE_MAIN_VARIANT (orig_type);
		}
	      ਨਹੀਂਤਾਂ
		{
		  align = ਵਿਅੰਜਕ.ਮੁੱਲ;
		  align = c_fully_fold (align, ਝੂਠ, ਨਿਰਾ);
		}
	      parens2.skip_until_ਮਿਲਿਆ_close (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  c_token *tok = c_parser_peek_token (parser);
		  ਅਚਲ ਅੱਖਰ *q = "";
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		    q = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
		  ਜੇ (strcmp (q, "allocator") != 0 && strcmp (q, "align") != 0)
		    {
		      c_parser_error (parser, "expected %<allocator%> or "
					      "%<align%>");
		      parens.skip_until_ਮਿਲਿਆ_close (parser);
		      ਵਾਪਸ list;
		    }
		  ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, q) == 0)
		    {
		      error_at (tok->location, "duplicate %qs modifier", p);
		      parens.skip_until_ਮਿਲਿਆ_close (parser);
		      ਵਾਪਸ list;
		    }
		  c_parser_consume_token (parser);
		  ਜੇ (!parens2.require_open (parser))
		    {
		      parens.skip_until_ਮਿਲਿਆ_close (parser);
		      ਵਾਪਸ list;
		    }
		  ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
		  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
		  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ,
						   ਸੱਚ);
		  ਜੇ (strcmp (q, "allocator") == 0)
		    {
		      allocator = ਵਿਅੰਜਕ.ਮੁੱਲ;
		      allocator = c_fully_fold (allocator, ਝੂਠ, ਨਿਰਾ);
		      orig_type = ਵਿਅੰਜਕ.original_type
				  ? ਵਿਅੰਜਕ.original_type : ਰੁੱਖ_TYPE (allocator);
		      orig_type = TYPE_MAIN_VARIANT (orig_type);
		    }
		  ਨਹੀਂਤਾਂ
		    {
		      align = ਵਿਅੰਜਕ.ਮੁੱਲ;
		      align = c_fully_fold (align, ਝੂਠ, ਨਿਰਾ);
		    }
		  parens2.skip_until_ਮਿਲਿਆ_close (parser);
		}
	    }
	}
      ਜੇ (!has_modifiers)
	{
	  location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
	  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
	  ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ != error_mark_ਗੰਢ)
	    {
	      allocator = ਵਿਅੰਜਕ.ਮੁੱਲ;
	      allocator = c_fully_fold (allocator, ਝੂਠ, ਨਿਰਾ);
	      orig_type = ਵਿਅੰਜਕ.original_type
			  ? ਵਿਅੰਜਕ.original_type : ਰੁੱਖ_TYPE (allocator);
	      orig_type = TYPE_MAIN_VARIANT (orig_type);
	    }
	}
      ਜੇ (allocator
	  && (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (allocator))
	      || ਰੁੱਖ_ਕੋਡ (orig_type) != ENUMERAL_TYPE
	      || (TYPE_NAME (orig_type)
		  != get_identifier ("omp_allocator_handle_t"))))
        {
          error_at (clause_loc, "%<allocate%> clause allocator expression "
				"has type %qT rather than "
				"%<omp_allocator_handle_t%>",
				ਰੁੱਖ_TYPE (allocator));
          allocator = NULL_ਰੁੱਖ;
        }
      ਜੇ (align
	  && (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (align))
	      || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_uhwi_p (align)
	      || !integer_pow2p (align)))
	{
	  error_at (clause_loc, "%<allocate%> clause %<align%> modifier "
				"argument needs to be positive constant "
				"power of two integer expression");
	  align = NULL_ਰੁੱਖ;
	}
      ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	{
	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	  ਵਾਪਸ list;
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ALLOCATE, list);

  ਜੇ (allocator || align)
    ਲਈ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      {
	OMP_CLAUSE_ALLOCATE_ALLOCATOR (c) = allocator;
	OMP_CLAUSE_ALLOCATE_ALIGN (c) = align;
      }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ nl;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਵਰਤਦਾ_allocators (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ nl = list;
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

parse_ਅਗਲਾ:

  ਤਾਰਕਿਕ has_modifiers = ਝੂਠ;
  ਤਾਰਕਿਕ ਵੇਖਿਆ_allocators = ਝੂਠ;
  ਰੁੱਖ memspace_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
  ਰੁੱਖ traits_var = NULL_ਰੁੱਖ;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
    {
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n = 3;
      ਅਚਲ ਅੱਖਰ *p
	= IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ ((strcmp (p, "traits") == 0 || strcmp (p, "memspace") == 0)
	  && c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n)
	  && (c_parser_peek_nth_token_raw (parser, n)->type
	      == CPP_CLOSE_PAREN))
	{
	  ਜੇ (c_parser_peek_nth_token_raw (parser, n + 1)->type
	      == CPP_COLON)
	    has_modifiers = ਸੱਚ;
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		   == CPP_COMMA
		   && (c_parser_peek_nth_token_raw (parser, n + 2)->type
		       == CPP_NAME)
		   && (c_parser_peek_nth_token_raw (parser, n + 3)->type
		       == CPP_OPEN_PAREN))
	    {
	      c_token *tok = c_parser_peek_nth_token_raw (parser, n + 2);
	      ਅਚਲ ਅੱਖਰ *q = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
	      n += 4;
	      ਜੇ ((strcmp (q, "traits") == 0
		   || strcmp (q, "memspace") == 0)
		  && c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n)
		  && (c_parser_peek_nth_token_raw (parser, n)->type
		      == CPP_CLOSE_PAREN))
		{
		  ਜੇ (c_parser_peek_nth_token_raw (parser, n + 1)->type
		      == CPP_COLON)
		    has_modifiers = ਸੱਚ;
		  ਜੇ ((c_parser_peek_nth_token_raw (parser, n + 1)->type
		       == CPP_COMMA)
		      && (c_parser_peek_nth_token_raw (parser, n + 2)->type
			  == CPP_NAME))
		    {
		      c_token *tok
			= c_parser_peek_nth_token_raw (parser, n + 2);
		      ਅਚਲ ਅੱਖਰ *m = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
		      ਜੇ (strcmp (p, m) == 0 || strcmp (q, m) == 0)
			{
			  error_at (tok->location, "duplicate %qs modifier", m);
			  ਜਾਓ ਸਿਰਾ;
			}
		    }
		}
	    }
	}
      ਜੇ (has_modifiers)
	{
	  c_parser_consume_token (parser);
	  matching_parens parens2;
	  parens2.require_open (parser);
	  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
	    ;
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "traits") == 0)
	    {
	      traits_var = ਵਿਅੰਜਕ.ਮੁੱਲ;
	      traits_var = c_fully_fold (traits_var, ਝੂਠ, ਨਿਰਾ);
	      mark_exp_read (traits_var);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      memspace_ਵਿਅੰਜਕ = ਵਿਅੰਜਕ.ਮੁੱਲ;
	      memspace_ਵਿਅੰਜਕ = c_fully_fold (memspace_ਵਿਅੰਜਕ, ਝੂਠ, ਨਿਰਾ);
	    }
	  parens2.skip_until_ਮਿਲਿਆ_close (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      c_token *tok = c_parser_peek_token (parser);
	      ਅਚਲ ਅੱਖਰ *q = "";
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		q = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
	      ਜੇ (strcmp (q, "traits") != 0 && strcmp (q, "memspace") != 0)
		{
		  c_parser_error (parser, "expected %<traits%> or "
				  "%<memspace%>");
		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		  ਵਾਪਸ list;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, q) == 0)
		{
		  error_at (tok->location, "duplicate %qs modifier", p);
		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		  ਵਾਪਸ list;
		}
	      c_parser_consume_token (parser);
	      ਜੇ (!parens2.require_open (parser))
		{
		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		  ਵਾਪਸ list;
		}
	      ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	      ਜੇ (strcmp (q, "traits") == 0)
		{
		  traits_var = ਵਿਅੰਜਕ.ਮੁੱਲ;
		  traits_var = c_fully_fold (traits_var, ਝੂਠ, ਨਿਰਾ);
		  mark_exp_read (traits_var);
		}
	      ਨਹੀਂਤਾਂ
		{
		  memspace_ਵਿਅੰਜਕ = ਵਿਅੰਜਕ.ਮੁੱਲ;
		  memspace_ਵਿਅੰਜਕ = c_fully_fold (memspace_ਵਿਅੰਜਕ, ਝੂਠ, ਨਿਰਾ);
		}
	      parens2.skip_until_ਮਿਲਿਆ_close (parser);
	    }
	  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    ਜਾਓ ਸਿਰਾ;
	}
    }

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      location_t alloc_loc = c_parser_peek_token (parser)->location;
      c_token *tok = c_parser_peek_token (parser);
      ਅਚਲ ਅੱਖਰ *tok_s = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
      ਰੁੱਖ t = lookup_name (tok->ਮੁੱਲ);
      ਜੇ (t == NULL_ਰੁੱਖ)
	{
	  undeclared_variable (tok->location, tok->ਮੁੱਲ);
	  t = error_mark_ਗੰਢ;
	}
      c_parser_consume_token (parser);

      /* Legacy traits syntax.  */
      ਰੁੱਖ legacy_traits = NULL_ਰੁੱਖ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
	  && c_parser_peek_nth_token_raw (parser, 3)->type == CPP_CLOSE_PAREN)
	{
	  matching_parens parens2;
	  parens2.require_open (parser);
	  ਅਚਲ ਅੱਖਰ *tok_a
	    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  location_t close_loc = c_parser_peek_token (parser)->location;
	  parens2.skip_until_ਮਿਲਿਆ_close (parser);

	  ਜੇ (has_modifiers)
	    {
	      error_at (make_location (alloc_loc, alloc_loc, close_loc),
			"legacy %<%s(%s)%> traits syntax not allowed in "
			"%<uses_allocators%> clause when using modifiers",
			tok_s, tok_a);
	      ਜਾਓ ਸਿਰਾ;
	    }
	  legacy_traits = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	  ਜੇ (legacy_traits == error_mark_ਗੰਢ)
	    ਜਾਓ ਸਿਰਾ;
	  mark_exp_read (legacy_traits);

	  gcc_rich_location richloc (make_location (alloc_loc, alloc_loc, close_loc));
	  ਜੇ (nl == list)
	    {
	      /* Fixit only works well if it is the only first item.  */
	      richloc.ਜੋੜੋ_fixit_replace (alloc_loc, "traits");
	      richloc.ਜੋੜੋ_fixit_ਪਾਓ_after (close_loc, ": ");
	      richloc.ਜੋੜੋ_fixit_ਪਾਓ_after (close_loc, tok_s);
	    }
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "the specification of arguments to %<uses_allocators%> "
		      "where each item is of the form %<allocator(traits)%> is "
		      "deprecated since OpenMP 5.2");
	}

      ਜੇ (ਵੇਖਿਆ_allocators && has_modifiers)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "%<uses_allocators%> clause only accepts a single "
		    "allocator when using modifiers");
	  ਜਾਓ ਸਿਰਾ;
	}
      ਵੇਖਿਆ_allocators = ਸੱਚ;

      ਰੁੱਖ c = build_omp_clause (clause_loc,
				 OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS);
      OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS_ALLOCATOR (c) = t;
      OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS_MEMSPACE (c) = memspace_ਵਿਅੰਜਕ;
      OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS_TRAITS (c) = (legacy_traits
					       ? legacy_traits : traits_var);
      OMP_CLAUSE_CHAIN (c) = nl;
      nl = c;

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_consume_token (parser);
      ਜਾਓ parse_ਅਗਲਾ;
    }

 ਸਿਰਾ:
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ nl;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਰੇਖਿਕ (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t rm1_loc = UNKNOWN_LOCATION, rm2_loc = UNKNOWN_LOCATION;
  location_t after_colon_loc = UNKNOWN_LOCATION;
  ਰੁੱਖ nl, c, ਕਦਮ;
  ਗਿਣਤੀ omp_clause_ਰੇਖਿਕ_ਕਿਸਮ ਕਿਸਮ = OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT;
  ਤਾਰਕਿਕ old_ਰੇਖਿਕ_modifier = ਝੂਠ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      c_token *tok = c_parser_peek_token (parser);
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
      ਜੇ (strcmp ("val", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_ਰੇਖਿਕ_VAL;
      ਜੇ (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN)
	ਕਿਸਮ = OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT;
      ਜੇ (ਕਿਸਮ != OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT)
	{
	  old_ਰੇਖਿਕ_modifier = ਸੱਚ;
	  rm1_loc = make_location (tok->location, tok->location,
				   c_parser_peek_2nd_token (parser)->location);
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	}
    }

  nl = c_parser_omp_variable_list (parser, clause_loc,
				   OMP_CLAUSE_ਰੇਖਿਕ, list);

  ਜੇ (ਕਿਸਮ != OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT)
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	rm2_loc = c_parser_peek_token (parser)->location;
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
    {
      c_parser_consume_token (parser);
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      after_colon_loc = ਵਿਅੰਜਕ_loc;
      ਤਾਰਕਿਕ has_modifiers = ਝੂਠ;
      ਜੇ (ਕਿਸਮ == OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT
	  && c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ pos = 0;
	  ਜੇ (strcmp ("val", p) == 0)
	    pos = 2;
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp ("step", p) == 0
		   && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      pos = 3;
	      ਜੇ (c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &pos)
		  && (c_parser_peek_nth_token_raw (parser, pos)->type
		      == CPP_CLOSE_PAREN))
		++pos;
	      ਨਹੀਂਤਾਂ
		pos = 0;
	    }
	  ਜੇ (pos)
	    {
	      tok = c_parser_peek_nth_token_raw (parser, pos);
	      ਜੇ (tok->type == CPP_COMMA || tok->type == CPP_CLOSE_PAREN)
		has_modifiers = ਸੱਚ;
	    }
	}
      ਜੇ (has_modifiers)
	{
	  ਕਦਮ = NULL_ਰੁੱਖ;
	  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	    {
	      c_token *tok = c_parser_peek_token (parser);
	      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
	      ਜੇ (strcmp ("val", p) == 0)
		{
		  ਜੇ (ਕਿਸਮ != OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT)
		    error_at (tok->location, "multiple linear modifiers");
		  ਕਿਸਮ = OMP_CLAUSE_ਰੇਖਿਕ_DEFAULT;
		  c_parser_consume_token (parser);
		}
	      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("step", p) == 0)
		{
		  c_parser_consume_token (parser);
		  matching_parens parens2;
		  ਜੇ (parens2.require_open (parser))
		    {
		      ਜੇ (ਕਦਮ)
			error_at (tok->location,
				  "multiple %<step%> modifiers");
		      ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
		      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
		      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ,
						       ਸੱਚ);
		      ਕਦਮ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
		      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਕਦਮ)))
			{
			  error_at (clause_loc, "%<linear%> clause step "
						"expression must be integral");
			  ਕਦਮ = integer_one_ਗੰਢ;
			}
		      parens2.skip_until_ਮਿਲਿਆ_close (parser);
		    }
		  ਨਹੀਂਤਾਂ
		    ਰੋਕੋ;
		}
	      ਨਹੀਂਤਾਂ
		ਰੋਕੋ;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ਜਾਰੀ;
		}
	      ਰੋਕੋ;
	    }
	  ਜੇ (!ਕਦਮ)
	    ਕਦਮ = integer_one_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ
	{
	  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
	  ਕਦਮ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਕਦਮ)))
	    {
	      error_at (clause_loc, "%<linear%> clause step expression must "
				    "be integral");
	      ਕਦਮ = integer_one_ਗੰਢ;
	    }
	}

    }
  ਨਹੀਂਤਾਂ
    ਕਦਮ = integer_one_ਗੰਢ;

  ਲਈ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_ਰੇਖਿਕ_ਕਦਮ (c) = ਕਦਮ;
      OMP_CLAUSE_ਰੇਖਿਕ_ਕਿਸਮ (c) = ਕਿਸਮ;
      OMP_CLAUSE_ਰੇਖਿਕ_OLD_ਰੇਖਿਕ_MODIFIER (c) = old_ਰੇਖਿਕ_modifier;
    }

  ਜੇ (old_ਰੇਖਿਕ_modifier)
    {
      gcc_rich_location richloc (clause_loc);
      ਜੇ (rm2_loc != UNKNOWN_LOCATION)
	{
	  richloc.ਜੋੜੋ_fixit_remove (rm1_loc);
	  ਜੇ (after_colon_loc != UNKNOWN_LOCATION)
	    {
	      richloc.ਜੋੜੋ_fixit_remove (rm2_loc);
	      richloc.ਜੋੜੋ_fixit_ਪਾਓ_before (after_colon_loc, "val, step (");
	      location_t close_loc = c_parser_peek_token (parser)->location;
	      richloc.ਜੋੜੋ_fixit_ਪਾਓ_before (close_loc, ")");
	    }
	  ਨਹੀਂਤਾਂ
	    richloc.ਜੋੜੋ_fixit_replace (rm2_loc, " : val");
	}
      warning_at (&richloc, OPT_Wdeprecated_openmp,
		  "specifying the list items as arguments to the "
		  "modifiers is deprecated since OpenMP 5.2");
    }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ nl;
}

/* OpenMP 5.0:
   nontemporal ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_nontemporal (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_NONTEMPORAL, list);
}

/* OpenMP 4.0:
   safelen ( constant-expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_safelen (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ c, t;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
  t = ਵਿਅੰਜਕ.ਮੁੱਲ;
  t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) != INTEGER_CST
      || !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t))
      || ਰੁੱਖ_int_cst_sgn (t) != 1)
    {
      error_at (clause_loc, "%<safelen%> clause expression must "
			    "be positive constant integer expression");
      t = NULL_ਰੁੱਖ;
    }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਜੇ (t == NULL_ਰੁੱਖ || t == error_mark_ਗੰਢ)
    ਵਾਪਸ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SAFELEN, "safelen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SAFELEN);
  OMP_CLAUSE_SAFELEN_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 4.0:
   simdlen ( constant-expression )

   OpenMP 6.1:
   simdlen ([scaled(type[, constant-expression]):] constant-expression )  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_simdlen (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ c, t = NULL_ਰੁੱਖ, type = NULL_ਰੁੱਖ, ਭਾਜਕ = NULL_ਰੁੱਖ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਬਿਨਾਨਿਸ਼ਾਨੀ pos = 3;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
      && strcmp (IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ),
		 "scaled") == 0
      && c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &pos)
      && c_parser_peek_nth_token_raw (parser, ++pos)->type == CPP_COLON)
    {
      c_parser_consume_token (parser);
      matching_parens parens2;
      parens2.require_open (parser);

      location_t loc = c_parser_peek_token (parser)->location;
      ਬਣਤਰ c_type_name *ctype = c_parser_type_name (parser);
      ਜੇ (ctype == ਨਿਰਾ
	  || (type = groktypename (ctype, ਨਿਰਾ, ਨਿਰਾ)) == ਨਿਰਾ
	  || (!INTEGRAL_TYPE_P (type)
	      && !SCALAR_FLOAT_TYPE_P (type)
	      && ਰੁੱਖ_ਕੋਡ (type) != COMPLEX_TYPE))
	{
	  error_at (loc, "expected arithmetic type name as argument to the "
			 "%<scaled%> modifier");
	  type = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  loc = c_parser_peek_token (parser)->location;
	  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
	  ਭਾਜਕ = ਵਿਅੰਜਕ.ਮੁੱਲ;
	  ਭਾਜਕ = c_fully_fold (ਭਾਜਕ, ਝੂਠ, ਨਿਰਾ);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਭਾਜਕ) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਭਾਜਕ))
	      || ਰੁੱਖ_int_cst_sgn (ਭਾਜਕ) != 1)
	    {
	      error_at (loc, "divisor expression of the %<scaled%> modifier "
			     "must a be positive constant integer expression");
	      type = error_mark_ਗੰਢ;
	    }
	}
      parens2.skip_until_ਮਿਲਿਆ_close (parser);
      c_parser_require (parser, CPP_COLON, "expected %<:%>");
    }

  ਜੇ (type != error_mark_ਗੰਢ)
    {
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) != INTEGER_CST
	  || !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t))
	  || ਰੁੱਖ_int_cst_sgn (t) != 1)
	{
	  error_at (clause_loc, "%<simdlen%> clause expression must "
				"be positive constant integer expression");
	  t = NULL_ਰੁੱਖ;
	}
    }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਜੇ (type == error_mark_ਗੰਢ || t == NULL_ਰੁੱਖ || t == error_mark_ਗੰਢ)
    ਵਾਪਸ list;

  check_no_duplicate_clause (list, OMP_CLAUSE_SIMDLEN, "simdlen");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_SIMDLEN);
  OMP_CLAUSE_SIMDLEN_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_SIMDLEN_TYPE (c) = type;
  OMP_CLAUSE_SIMDLEN_ਭਾਜਕ (c) = ਭਾਜਕ;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 4.5:
   vec:
     identifier [+/- integer]
     vec , identifier [+/- integer]
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_doacross_sink (c_parser *parser, location_t clause_loc,
				   ਰੁੱਖ list, ਤਾਰਕਿਕ depend_p)
{
  ਰੁੱਖ vec = ਨਿਰਾ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_ਕਿਸਮ != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      ਵਾਪਸ list;
    }

  ਜੇ (!depend_p)
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "omp_cur_iteration") == 0
	  && c_parser_peek_2nd_token (parser)->type == CPP_MINUS
	  && c_parser_peek_nth_token (parser, 3)->type == CPP_ਸੰਖਿਆ
	  && c_parser_peek_nth_token (parser, 4)->type == CPP_CLOSE_PAREN)
	{
	  ਰੁੱਖ val = c_parser_peek_nth_token (parser, 3)->ਮੁੱਲ;
	  ਜੇ (integer_onep (val))
	    {
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      c_parser_consume_token (parser);
	      ਰੁੱਖ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
	      OMP_CLAUSE_DOACROSS_ਕਿਸਮ (u) = OMP_CLAUSE_DOACROSS_SINK;
	      OMP_CLAUSE_CHAIN (u) = list;
	      ਵਾਪਸ u;
	    }
	}
    }



  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	 && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID)
    {
      ਰੁੱਖ t = lookup_name (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਰੁੱਖ addend = ਨਿਰਾ;

      ਜੇ (t == NULL_ਰੁੱਖ)
	{
	  undeclared_variable (c_parser_peek_token (parser)->location,
			       c_parser_peek_token (parser)->ਮੁੱਲ);
	  t = error_mark_ਗੰਢ;
	}

      c_parser_consume_token (parser);

      ਤਾਰਕਿਕ neg = ਝੂਠ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_MINUS))
	neg = ਸੱਚ;
      ਨਹੀਂਤਾਂ ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_PLUS))
	{
	  addend = integer_zero_ਗੰਢ;
	  neg = ਝੂਠ;
	  ਜਾਓ ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸਦਿਸ਼;
	}
      c_parser_consume_token (parser);

      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_ਸੰਖਿਆ))
	{
	  c_parser_error (parser, "expected integer");
	  ਵਾਪਸ list;
	}

      addend = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (addend) != INTEGER_CST)
	{
	  c_parser_error (parser, "expected integer");
	  ਵਾਪਸ list;
	}
      c_parser_consume_token (parser);

    ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸਦਿਸ਼:
      ਜੇ (t != error_mark_ਗੰਢ)
	{
	  vec = ਰੁੱਖ_cons (addend, t, vec);
	  ਜੇ (neg)
	    OMP_CLAUSE_DOACROSS_SINK_NEGATIVE (vec) = 1;
	}

      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COMMA)
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->id_ਕਿਸਮ != C_ID_ID)
	ਰੋਕੋ;

      c_parser_consume_token (parser);
    }

  ਜੇ (vec == NULL_ਰੁੱਖ)
    ਵਾਪਸ list;

  ਰੁੱਖ u = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
  OMP_CLAUSE_DOACROSS_ਕਿਸਮ (u) = OMP_CLAUSE_DOACROSS_SINK;
  OMP_CLAUSE_DOACROSS_DEPEND (u) = depend_p;
  OMP_CLAUSE_DECL (u) = nreverse (vec);
  OMP_CLAUSE_CHAIN (u) = list;
  ਵਾਪਸ u;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_iterators (c_parser *parser)
{
  ਰੁੱਖ ret = NULL_ਰੁੱਖ, *ਆਖਰੀ = &ret;
  c_parser_consume_token (parser);

  ਧੱਕੋ_scope ();

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਕਰੋ
    {
      ਰੁੱਖ iter_type = NULL_ਰੁੱਖ, type_ਵਿਅੰਜਕ = NULL_ਰੁੱਖ;
      ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_typename (parser, cla_prefer_id))
	{
	  ਬਣਤਰ c_type_name *type = c_parser_type_name (parser);
	  ਜੇ (type != ਨਿਰਾ)
	    iter_type = groktypename (type, &type_ਵਿਅੰਜਕ, ਨਿਰਾ);
	}
      ਜੇ (iter_type == NULL_ਰੁੱਖ)
	iter_type = integer_type_ਗੰਢ;

      location_t loc = c_parser_peek_token (parser)->location;
      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected identifier");
	  ਰੋਕੋ;
	}

      ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
      c_parser_consume_token (parser);

      ਜੇ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ਰੋਕੋ;

      location_t eloc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (eloc, ਵਿਅੰਜਕ, ਸੱਚ, ਝੂਠ);
      ਰੁੱਖ begin = ਵਿਅੰਜਕ.ਮੁੱਲ;

      ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ਰੋਕੋ;

      eloc = c_parser_peek_token (parser)->location;
      ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (eloc, ਵਿਅੰਜਕ, ਸੱਚ, ਝੂਠ);
      ਰੁੱਖ ਸਿਰਾ = ਵਿਅੰਜਕ.ਮੁੱਲ;

      ਰੁੱਖ ਕਦਮ = integer_one_ਗੰਢ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	{
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (eloc, ਵਿਅੰਜਕ, ਸੱਚ, ਝੂਠ);
	  ਕਦਮ = ਵਿਅੰਜਕ.ਮੁੱਲ;
	}

      ਰੁੱਖ iter_var = build_decl (loc, VAR_DECL, id, iter_type);
      DECL_ARTIFICIAL (iter_var) = 1;
      DECL_CONTEXT (iter_var) = current_function_decl;
      pushdecl (iter_var);

      *ਆਖਰੀ = make_omp_iterator ();
      OMP_ITERATOR_VAR (*ਆਖਰੀ) = iter_var;
      OMP_ITERATOR_BEGIN (*ਆਖਰੀ) = begin;
      OMP_ITERATOR_ਸਿਰਾ (*ਆਖਰੀ) = ਸਿਰਾ;
      OMP_ITERATOR_ਕਦਮ (*ਆਖਰੀ) = ਕਦਮ;
      ਆਖਰੀ = &ਰੁੱਖ_CHAIN (*ਆਖਰੀ);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}
      ਰੋਕੋ;
    }
  ਜਦੋਂ (1);

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ ret ? ret : error_mark_ਗੰਢ;
}

/* OpenMP 5.0:
   affinity ( [aff-modifier :] variable-list )
   aff-modifier:
     iterator ( iterators-definition )  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_affinity (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ nl, iterators = NULL_ਰੁੱਖ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਤਾਰਕਿਕ parse_iter = ((strcmp ("iterator", p) == 0)
			 && (c_parser_peek_2nd_token (parser)->type
			     == CPP_OPEN_PAREN));
      ਜੇ (parse_iter)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ n = 3;
	  parse_iter = (c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n)
			&& (c_parser_peek_nth_token_raw (parser, n)->type
			    == CPP_CLOSE_PAREN)
			&& (c_parser_peek_nth_token_raw (parser, n + 1)->type
			    == CPP_COLON));
	}
      ਜੇ (parse_iter)
	{
	  iterators = c_parser_omp_iterators (parser);
	  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    {
	      ਜੇ (iterators)
		ਕੱਢੋ_scope ();
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਵਾਪਸ list;
	    }
	}
    }
  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_AFFINITY,
				   list);
  ਜੇ (iterators)
    {
      ਰੁੱਖ ਖੰਡ = ਕੱਢੋ_scope ();
      ਜੇ (iterators != error_mark_ਗੰਢ)
	{
	  OMP_ITERATOR_ਖੰਡ (iterators) = ਖੰਡ;
	  ਲਈ (ਰੁੱਖ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	    OMP_CLAUSE_DECL (c) = build_ਰੁੱਖ_list (iterators,
						   OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ nl;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_depend (c_parser *parser, ਰੁੱਖ list, location_t ਇੱਥੇ)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਗਿਣਤੀ omp_clause_depend_ਕਿਸਮ ਕਿਸਮ = OMP_CLAUSE_DEPEND_ਆਖਰੀ;
  ਗਿਣਤੀ omp_clause_doacross_ਕਿਸਮ dkind = OMP_CLAUSE_DOACROSS_ਆਖਰੀ;
  ਰੁੱਖ nl, c, iterators = NULL_ਰੁੱਖ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਕਰੋ
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
	ਜਾਓ invalid_ਕਿਸਮ;

      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp ("iterator", p) == 0 && iterators == NULL_ਰੁੱਖ)
	{
	  iterators = c_parser_omp_iterators (parser);
	  c_parser_require (parser, CPP_COMMA, "expected %<,%>");
	  ਜਾਰੀ;
	}
      ਜੇ (strcmp ("in", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEPEND_ਵਿੱਚ;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("inout", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEPEND_INOUT;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("inoutset", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEPEND_INOUTSET;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("mutexinoutset", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("out", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEPEND_ਬਾਹਰਲਾ;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("depobj", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEPEND_DEPOBJ;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("sink", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.ਜੋੜੋ_fixit_replace (ਇੱਥੇ, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<sink%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_SINK;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("source", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.ਜੋੜੋ_fixit_replace (ਇੱਥੇ, "doacross");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<source%> modifier with %<depend%> clause deprecated "
		      "since OpenMP 5.2, use with %<doacross%>");
	  dkind = OMP_CLAUSE_DOACROSS_ਸਰੋਤ;
	}
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_ਕਿਸਮ;
      ਰੋਕੋ;
    }
  ਜਦੋਂ (1);

  c_parser_consume_token (parser);

  ਜੇ (iterators
      && (dkind == OMP_CLAUSE_DOACROSS_ਸਰੋਤ
	  || dkind == OMP_CLAUSE_DOACROSS_SINK))
    {
      ਕੱਢੋ_scope ();
      error_at (clause_loc, "%<iterator%> modifier incompatible with %qs",
		dkind == OMP_CLAUSE_DOACROSS_ਸਰੋਤ ? "source" : "sink");
      iterators = NULL_ਰੁੱਖ;
    }

  ਜੇ (dkind == OMP_CLAUSE_DOACROSS_ਸਰੋਤ)
    {
      c = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_ਕਿਸਮ (c) = dkind;
      OMP_CLAUSE_DOACROSS_DEPEND (c) = 1;
      OMP_CLAUSE_DECL (c) = NULL_ਰੁੱਖ;
      OMP_CLAUSE_CHAIN (c) = list;
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਵਾਪਸ c;
    }

  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ਜਾਓ resync_fail;

  ਜੇ (dkind == OMP_CLAUSE_DOACROSS_SINK)
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, ਸੱਚ);
  ਨਹੀਂਤਾਂ
    {
      nl = c_parser_omp_variable_list (parser, clause_loc,
				       OMP_CLAUSE_DEPEND, list);

      ਜੇ (iterators)
	{
	  ਰੁੱਖ ਖੰਡ = ਕੱਢੋ_scope ();
	  ਜੇ (iterators == error_mark_ਗੰਢ)
	    iterators = NULL_ਰੁੱਖ;
	  ਨਹੀਂਤਾਂ
	    OMP_ITERATOR_ਖੰਡ (iterators) = ਖੰਡ;
	}

      ਲਈ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	{
	  OMP_CLAUSE_DEPEND_ਕਿਸਮ (c) = ਕਿਸਮ;
	  ਜੇ (iterators)
	    OMP_CLAUSE_DECL (c)
	      = build_ਰੁੱਖ_list (iterators, OMP_CLAUSE_DECL (c));
	}
    }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ nl;

 invalid_ਕਿਸਮ:
  c_parser_error (parser, "invalid depend kind");
 resync_fail:
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਜੇ (iterators)
    ਕੱਢੋ_scope ();
  ਵਾਪਸ list;
}

/* OpenMP 5.2:
   doacross ( source : )
   doacross ( source : omp_cur_iteration )

   doacross ( sink : vec )
   doacross ( sink : omp_cur_iteration - logical_iteration )  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_doacross (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਗਿਣਤੀ omp_clause_doacross_ਕਿਸਮ ਕਿਸਮ = OMP_CLAUSE_DOACROSS_ਆਖਰੀ;
  ਰੁੱਖ nl;
  ਅਚਲ ਅੱਖਰ *p;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME))
    ਜਾਓ invalid_ਕਿਸਮ;

  p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
  ਜੇ (strcmp ("sink", p) == 0)
    ਕਿਸਮ = OMP_CLAUSE_DOACROSS_SINK;
  ਨਹੀਂਤਾਂ ਜੇ (strcmp ("source", p) == 0)
    ਕਿਸਮ = OMP_CLAUSE_DOACROSS_ਸਰੋਤ;
  ਨਹੀਂਤਾਂ
    ਜਾਓ invalid_ਕਿਸਮ;

  c_parser_consume_token (parser);

  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ਜਾਓ resync_fail;

  ਜੇ (ਕਿਸਮ == OMP_CLAUSE_DOACROSS_ਸਰੋਤ)
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	  && strcmp (IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ),
		     "omp_cur_iteration") == 0)
	c_parser_consume_token (parser);
      nl = build_omp_clause (clause_loc, OMP_CLAUSE_DOACROSS);
      OMP_CLAUSE_DOACROSS_ਕਿਸਮ (nl) = OMP_CLAUSE_DOACROSS_ਸਰੋਤ;
      OMP_CLAUSE_DECL (nl) = NULL_ਰੁੱਖ;
      OMP_CLAUSE_CHAIN (nl) = list;
    }
  ਨਹੀਂਤਾਂ
    nl = c_parser_omp_clause_doacross_sink (parser, clause_loc, list, ਝੂਠ);

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ nl;

 invalid_ਕਿਸਮ:
  c_parser_error (parser, "invalid doacross kind");
 resync_fail:
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ list;
}

/* OpenMP 6.1:
   dyn_groupprivate ( [fallback-modifier : ] integer-expression )

   fallback-modifier
      fallback( abort | default_mem | null )  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_dyn_groupprivate (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਗਿਣਤੀ omp_clause_fallback_ਕਿਸਮ ਕਿਸਮ = OMP_CLAUSE_FALLBACK_UNSPECIFIED;

  ਬਿਨਾਨਿਸ਼ਾਨੀ n = 3;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && (c_parser_peek_2nd_token (parser)->type == CPP_COLON
	  || (c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	      && c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n)
	      && (c_parser_peek_nth_token_raw (parser, n)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, n + 1)->type
		  == CPP_COLON))))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "fallback") != 0)
	{
	  c_parser_error (parser, "expected %<fallback%> modifier");
	  ਵਾਪਸ list;
	}
      c_parser_consume_token (parser);
      ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ਵਾਪਸ list;
      p = "";
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "abort") == 0)
	ਕਿਸਮ = OMP_CLAUSE_FALLBACK_ABORT;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "default_mem") == 0)
	ਕਿਸਮ = OMP_CLAUSE_FALLBACK_DEFAULT_MEM;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "null") == 0)
	ਕਿਸਮ = OMP_CLAUSE_FALLBACK_NULL;
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected %<abort%>, %<default_mem%>, or "
				  "%<null%> as fallback mode");
	  ਵਾਪਸ list;
	}
      c_parser_consume_token (parser);
      ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	ਵਾਪਸ list;
      ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ਵਾਪਸ list;
    }
  location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
  ਰੁੱਖ ਮਾਪ = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਮਾਪ)))
    {
      error_at (ਵਿਅੰਜਕ_loc, "expected integer expression");
      ਵਾਪਸ list;
    }

  /* Attempt to statically determine when the number is negative.  */
  ਰੁੱਖ c = fold_build2_loc (ਵਿਅੰਜਕ_loc, LT_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, ਮਾਪ,
			    build_int_cst (ਰੁੱਖ_TYPE (ਮਾਪ), 0));
  protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (c, ਵਿਅੰਜਕ_loc);
  ਜੇ (c == boolean_true_ਗੰਢ)
    {
      warning_at (ਵਿਅੰਜਕ_loc, OPT_Wopenmp,
		  "%<dyn_groupprivate%> value must be non-negative");
      ਮਾਪ = integer_zero_ਗੰਢ;
    }
  check_no_duplicate_clause (list, OMP_CLAUSE_DYN_GROUPPRIVATE,
			     "dyn_groupprivate");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DYN_GROUPPRIVATE);
  OMP_CLAUSE_DYN_GROUPPRIVATE_ਕਿਸਮ (c) = ਕਿਸਮ;
  OMP_CLAUSE_DYN_GROUPPRIVATE_ਵਿਅੰਜਕ (c) = ਮਾਪ;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ਵਾਪਸ list;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_map (c_parser *parser, ਰੁੱਖ list, ਤਾਰਕਿਕ declare_mapper_p)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ nl, c;
  ਗਿਣਤੀ gomp_map_ਕਿਸਮ ਕਿਸਮ = declare_mapper_p ? GOMP_MAP_UNSET : GOMP_MAP_TOFROM;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਪੂਰਨ pos = 1;
  ਪੂਰਨ map_ਕਿਸਮ_pos = 0;
  ਪੂਰਨ iterator_ਲੰਮਾਈ = 0;
  ਲਈ (;;)
    {
      c_token *tok = c_parser_peek_nth_token_raw (parser, pos);
      ਜੇ (tok->type != CPP_NAME)
	ਰੋਕੋ;

      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
      c_token *ਅਗਲਾ_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
      ਜੇ (strcmp (p, "iterator") == 0 && ਅਗਲਾ_tok->type == CPP_OPEN_PAREN)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ n = pos + 2;
	  ਜੇ (c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n)
	      && c_parser_peek_nth_token_raw (parser, n)->type
		 == CPP_CLOSE_PAREN)
	    {
	      iterator_ਲੰਮਾਈ = n - pos + 1;
	      pos = n;
	      ਅਗਲਾ_tok = c_parser_peek_nth_token_raw (parser, pos + 1);
	    }
	}

      ਜੇ (ਅਗਲਾ_tok->type == CPP_COLON)
	{
	  map_ਕਿਸਮ_pos = pos;
	  ਰੋਕੋ;
	}

      ਜੇ (ਅਗਲਾ_tok->type == CPP_COMMA)
	pos++;
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	       == CPP_OPEN_PAREN)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ npos = pos + 2;
	  ਜੇ (c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN)
	      && (c_parser_peek_nth_token_raw (parser, npos + 1)->type
		  == CPP_COMMA))
	    pos = npos + 1;
	}

      pos++;
    }

  ਪੂਰਨ always_modifier = 0;
  ਪੂਰਨ close_modifier = 0;
  ਪੂਰਨ present_modifier = 0;
  ਪੂਰਨ mapper_modifier = 0;
  ਪੂਰਨ ਅੰਕ_commas = 0;
  ਪੂਰਨ ਅੰਕ_identifiers = 0;
  ਰੁੱਖ mapper_name = NULL_ਰੁੱਖ;
  ਰੁੱਖ iterators = NULL_ਰੁੱਖ;
  ਲਈ (ਪੂਰਨ pos = 1; pos < map_ਕਿਸਮ_pos; ++pos)
    {
      c_token *tok = c_parser_peek_token (parser);

      ਜੇ (tok->type == CPP_COMMA)
	{
	  ++ਅੰਕ_commas;
	  ਜੇ (ਅੰਕ_commas > ਅੰਕ_identifiers)
	    c_parser_error (parser, "illegal comma");
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}

      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
      ਜੇ (strcmp ("always", p) == 0)
	{
	  ਜੇ (always_modifier)
	    {
	      c_parser_error (parser, "too many %<always%> modifiers");
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਵਾਪਸ list;
	    }
	  always_modifier++;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("close", p) == 0)
	{
	  ਜੇ (close_modifier)
	    {
	      c_parser_error (parser, "too many %<close%> modifiers");
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਵਾਪਸ list;
	    }
	  close_modifier++;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("iterator", p) == 0)
	{
	  ਜੇ (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਵਾਪਸ list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_ਲੰਮਾਈ - 1;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  ਜੇ (mparens.require_open (parser))
	    {
	      ਜੇ (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		  ਵਾਪਸ list;
		}

	      tok = c_parser_peek_token (parser);

	      ਚੋਣ (tok->type)
		{
		ਹਾਲਤ CPP_NAME:
		  {
		    mapper_name = tok->ਮੁੱਲ;
		    c_parser_consume_token (parser);
		    ਜੇ (declare_mapper_p)
		      {
			error_at (tok->location,
				  "in %<declare mapper%> directives, parameter "
				  "to %<mapper%> modifier must be %<default%>");
		      }
		  }
		  ਰੋਕੋ;

		ਹਾਲਤ CPP_KEYWORD:
		  ਜੇ (tok->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ਰੋਕੋ;
		    }
		  /* Fallthrough.  */

		ਮੂਲ:
		  error_at (tok->location,
			    "expected identifier or %<default%>");
		  ਵਾਪਸ list;
		}

	      ਜੇ (!mparens.require_close (parser))
		{
		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		  ਵਾਪਸ list;
		}

	      mapper_modifier++;
	      pos += 3;
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("present", p) == 0)
	{
	  ਜੇ (present_modifier)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਵਾਪਸ list;
	    }
	  present_modifier++;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "%<map%> clause with map-type modifier other "
				  "than %<always%>, %<close%>, %<iterator%>, "
				  "%<mapper%> or %<present%>");
	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	  ਵਾਪਸ list;
	}
      ++ਅੰਕ_identifiers;
      ਜੇ (ਅੰਕ_identifiers - 1 > ਅੰਕ_commas)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.ਜੋੜੋ_fixit_ਪਾਓ_before (tok->location, ",");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<map%> clause modifiers without comma separation is "
		      "deprecated since OpenMP 5.2");
	}
      ਅੰਕ_commas = ਅੰਕ_identifiers - 1;
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਪੂਰਨ always_present_modifier = always_modifier && present_modifier;

      ਜੇ (strcmp ("alloc", p) == 0)
	ਕਿਸਮ = present_modifier ? GOMP_MAP_PRESENT_ALLOC : GOMP_MAP_ALLOC;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("to", p) == 0)
	ਕਿਸਮ = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_ਮੰਜ਼ਿਲ
		: present_modifier ? GOMP_MAP_PRESENT_ਮੰਜ਼ਿਲ
		: always_modifier ? GOMP_MAP_ALWAYS_ਮੰਜ਼ਿਲ
		: GOMP_MAP_ਮੰਜ਼ਿਲ);
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("from", p) == 0)
	ਕਿਸਮ = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_FROM
		: present_modifier ? GOMP_MAP_PRESENT_FROM
		: always_modifier ? GOMP_MAP_ALWAYS_FROM
		: GOMP_MAP_FROM);
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("tofrom", p) == 0)
	ਕਿਸਮ = (always_present_modifier ? GOMP_MAP_ALWAYS_PRESENT_TOFROM
		: present_modifier ? GOMP_MAP_PRESENT_TOFROM
		: always_modifier ? GOMP_MAP_ALWAYS_TOFROM
		: GOMP_MAP_TOFROM);
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("release", p) == 0)
	ਕਿਸਮ = GOMP_MAP_RELEASE;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("delete", p) == 0)
	ਕਿਸਮ = GOMP_MAP_DELETE;
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "invalid map kind");
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  ਵਾਪਸ list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  nl = c_parser_omp_variable_list (parser, clause_loc, OMP_CLAUSE_MAP, list,
				   ਸੱਚ);

  ਰੁੱਖ ਆਖਰੀ_new = NULL_ਰੁੱਖ;

  ਜੇ (iterators)
    {
      ਰੁੱਖ ਖੰਡ = ਕੱਢੋ_scope ();
      ਜੇ (iterators == error_mark_ਗੰਢ)
	iterators = NULL_ਰੁੱਖ;
      ਨਹੀਂਤਾਂ
	OMP_ITERATOR_ਖੰਡ (iterators) = ਖੰਡ;
    }

  ਲਈ (c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (c, ਕਿਸਮ);
      OMP_CLAUSE_ITERATORS (c) = iterators;
      ਆਖਰੀ_new = c;
    }

  ਜੇ (mapper_name)
    {
      ਰੁੱਖ name = build_omp_clause (ਨਿਵੇਸ਼_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (name, GOMP_MAP_ਧੱਕੋ_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (ਆਖਰੀ_new);

      name = build_omp_clause (ਨਿਵੇਸ਼_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (name, GOMP_MAP_ਕੱਢੋ_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_ਸੂਚਕ_ਗੰਢ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (ਆਖਰੀ_new);
      OMP_CLAUSE_CHAIN (ਆਖਰੀ_new) = name;
    }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ nl;
}

/* OpenMP 4.0:
   device ( expression )

   OpenMP 5.0:
   device ( [device-modifier :] integer-expression )

   device-modifier:
     ancestor | device_num */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_device (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  location_t ਵਿਅੰਜਕ_loc;
  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  ਰੁੱਖ c, t;
  ਤਾਰਕਿਕ ancestor = ਝੂਠ;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      c_token *tok = c_parser_peek_token (parser);
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
      ਜੇ (strcmp ("ancestor", p) == 0)
	{
	  /* A requires directive with the reverse_offload clause must be
	  specified.  */
	  ਜੇ ((omp_requires_ਨਕਾਬ & OMP_REQUIRES_ਉਲਟ_OFFLOAD) == 0)
	    {
	      error_at (tok->location, "%<ancestor%> device modifier not "
				       "preceded by %<requires%> directive "
				       "with %<reverse_offload%> clause");
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਵਾਪਸ list;
	    }
	  ancestor = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("device_num", p) == 0)
	;
      ਨਹੀਂਤਾਂ
	{
	  error_at (tok->location, "expected %<ancestor%> or %<device_num%>");
	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	  ਵਾਪਸ list;
	}
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
  t = ਵਿਅੰਜਕ.ਮੁੱਲ;
  t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);

  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
    {
      c_parser_error (parser, "expected integer expression");
      ਵਾਪਸ list;
    }
  ਜੇ (ancestor && ਰੁੱਖ_ਕੋਡ (t) == INTEGER_CST && !integer_onep (t))
    {
      error_at (ਵਿਅੰਜਕ_loc, "the %<device%> clause expression must evaluate to "
			  "%<1%>");
      ਵਾਪਸ list;
    }

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE, "device");

  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE);

  OMP_CLAUSE_DEVICE_ID (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  OMP_CLAUSE_DEVICE_ANCESTOR (c) = ancestor;

  list = c;
  ਵਾਪਸ list;
}

/* OpenMP 4.0:
   dist_schedule ( static )
   dist_schedule ( static , expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_dist_ਸਮਾਂ_ਸਾਰਣੀ (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ c, t = NULL_ਰੁੱਖ;
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (!c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_STATIC))
    {
      c_parser_error (parser, "invalid dist_schedule kind");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      ਵਾਪਸ list;
    }

  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);

      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      t = ਵਿਅੰਜਕ.ਮੁੱਲ;
      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਨਹੀਂਤਾਂ
    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>");

  /* check_no_duplicate_clause (list, OMP_CLAUSE_DIST_SCHEDULE,
				"dist_schedule"); */
  ਜੇ (omp_ਲੱਭੋ_clause (list, OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ))
    warning_at (loc, OPT_Wopenmp, "too many %qs clauses", "dist_schedule");
  ਜੇ (t == error_mark_ਗੰਢ)
    ਵਾਪਸ list;

  c = build_omp_clause (loc, OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ);
  OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ_CHUNK_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 4.0:
   proc_bind ( proc-bind-kind )

   proc-bind-kind:
     primary | master | close | spread
   where OpenMP 5.1 added 'primary' and deprecated the alias 'master'.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_proc_bind (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਗਿਣਤੀ omp_clause_proc_bind_ਕਿਸਮ ਕਿਸਮ;
  ਰੁੱਖ c;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp ("primary", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_PROC_BIND_PRIMARY;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("master", p) == 0)
	{
	  gcc_rich_location richloc (clause_loc);
	  richloc.ਜੋੜੋ_fixit_replace (c_parser_peek_token (parser)->location,
				     "primary");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<master%> affinity deprecated since OpenMP 5.1, "
		      "use %<primary%>");
	  ਕਿਸਮ = OMP_CLAUSE_PROC_BIND_MASTER;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("close", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_PROC_BIND_CLOSE;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("spread", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_PROC_BIND_ਫੈਲਾਅ;
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_ਕਿਸਮ;
    }
  ਨਹੀਂਤਾਂ
    ਜਾਓ invalid_ਕਿਸਮ;

  check_no_duplicate_clause (list, OMP_CLAUSE_PROC_BIND, "proc_bind");
  c_parser_consume_token (parser);
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_PROC_BIND);
  OMP_CLAUSE_PROC_BIND_ਕਿਸਮ (c) = ਕਿਸਮ;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;

 invalid_ਕਿਸਮ:
  c_parser_error (parser, "invalid proc_bind kind");
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ list;
}

/* OpenMP 5.0:
   device_type ( host | nohost | any )  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_device_type (c_parser *parser, ਰੁੱਖ list)
{
  location_t clause_loc = c_parser_peek_token (parser)->location;
  ਗਿਣਤੀ omp_clause_device_type_ਕਿਸਮ ਕਿਸਮ;
  ਰੁੱਖ c;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp ("host", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEVICE_TYPE_HOST;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("nohost", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEVICE_TYPE_NOHOST;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("any", p) == 0)
	ਕਿਸਮ = OMP_CLAUSE_DEVICE_TYPE_ANY;
      ਨਹੀਂਤਾਂ
	ਜਾਓ invalid_ਕਿਸਮ;
    }
  ਨਹੀਂਤਾਂ
    ਜਾਓ invalid_ਕਿਸਮ;

  check_no_duplicate_clause (list, OMP_CLAUSE_DEVICE_TYPE,
			     "device_type");
  c_parser_consume_token (parser);
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  c = build_omp_clause (clause_loc, OMP_CLAUSE_DEVICE_TYPE);
  OMP_CLAUSE_DEVICE_TYPE_ਕਿਸਮ (c) = ਕਿਸਮ;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;

 invalid_ਕਿਸਮ:
  c_parser_error (parser, "expected %<host%>, %<nohost%> or %<any%>");
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ list;
}

/* OpenMP 4.0:
   from ( variable-list )
   to ( variable-list )

   OpenMP 5.1:
   from ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )
   to ( [motion-modifier[,] [motion-modifier[,]...]:] variable-list )

   motion-modifier:
     present | iterator (iterators-definition) | mapper (id)  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_from_ਮੰਜ਼ਿਲ (c_parser *parser, ਗਿਣਤੀ omp_clause_ਕੋਡ ਕਿਸਮ,
			     ਰੁੱਖ list)
{
  location_t loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਪੂਰਨ pos = 1, colon_pos = 0;
  ਪੂਰਨ iterator_ਲੰਮਾਈ = 0;

  ਜਦੋਂ (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_NAME)
    {
      ਅਚਲ ਅੱਖਰ *identifier =
	IDENTIFIER_ਸੂਚਕ (c_parser_peek_nth_token_raw (parser, pos)->ਮੁੱਲ);
      ਜੇ (c_parser_peek_nth_token_raw (parser, pos + 1)->type
	  == CPP_OPEN_PAREN)
	{
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ npos = pos + 2;
	  ਜੇ (c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &npos)
	      && (c_parser_peek_nth_token_raw (parser, npos)->type
		  == CPP_CLOSE_PAREN))
	    {
	      ਜੇ (strcmp (identifier, "iterator") == 0)
		iterator_ਲੰਮਾਈ = npos - pos + 1;
	      pos = npos;
	    }
	}
      ਜੇ (c_parser_peek_nth_token_raw (parser, pos + 1)->type == CPP_COMMA)
	pos += 2;
      ਨਹੀਂਤਾਂ
	pos++;
      ਜੇ (c_parser_peek_nth_token_raw (parser, pos)->type == CPP_COLON)
	{
	  colon_pos = pos;
	  ਰੋਕੋ;
	}
    }

  ਤਾਰਕਿਕ present = ਝੂਠ, mapper_modifier = ਝੂਠ;
  ਰੁੱਖ iterators = NULL_ਰੁੱਖ;
  ਰੁੱਖ mapper_name = NULL_ਰੁੱਖ;

  ਲਈ (ਪੂਰਨ pos = 1; pos < colon_pos; ++pos)
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ (token->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (token->ਮੁੱਲ);
      ਜੇ (strcmp ("present", p) == 0)
	{
	  ਜੇ (present)
	    {
	      c_parser_error (parser, "too many %<present%> modifiers");
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਵਾਪਸ list;
	    }
	  present = ਸੱਚ;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("iterator", p) == 0)
	{
	  ਜੇ (iterators)
	    {
	      c_parser_error (parser, "too many %<iterator%> modifiers");
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਵਾਪਸ list;
	    }
	  iterators = c_parser_omp_iterators (parser);
	  pos += iterator_ਲੰਮਾਈ - 1;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("mapper", p) == 0)
	{
	  c_parser_consume_token (parser);

	  matching_parens mparens;
	  ਜੇ (mparens.require_open (parser))
	    {
	      ਜੇ (mapper_modifier)
		{
		  c_parser_error (parser, "too many %<mapper%> modifiers");
		  /* Assume it's a well-formed mapper modifier, even if it
		     seems to be in the wrong place.  */
		  c_parser_consume_token (parser);
		  mparens.require_close (parser);
		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		  ਵਾਪਸ list;
		}

	      token = c_parser_peek_token (parser);
	      ਚੋਣ (token->type)
		{
		ਹਾਲਤ CPP_NAME:
		  {
		    mapper_name = token->ਮੁੱਲ;
		    c_parser_consume_token (parser);
		  }
		  ਰੋਕੋ;
		ਹਾਲਤ CPP_KEYWORD:
		  ਜੇ (token->keyword == RID_DEFAULT)
		    {
		      c_parser_consume_token (parser);
		      ਰੋਕੋ;
		    }
		  /* FALLTHROUGH  */
		ਮੂਲ:
		  error_at (token->location,
			    "expected identifier or %<default%>");
		  ਵਾਪਸ list;
		}
	      ਜੇ (!mparens.require_close (parser))
		{
		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		  ਵਾਪਸ list;
		}
	      mapper_modifier = ਸੱਚ;
	      pos += 3;
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  error_at (token->location,
		    "%qs clause with modifier other than %<iterator%>, "
		    "%<mapper%>, or %<present%>",
		    ਕਿਸਮ == OMP_CLAUSE_ਮੰਜ਼ਿਲ ? "to" : "from");
	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	  ਵਾਪਸ list;
	}
    }

  ਜੇ (colon_pos)
    c_parser_require (parser, CPP_COLON, "expected %<:%>");

  ਰੁੱਖ nl = c_parser_omp_variable_list (parser, loc, ਕਿਸਮ, list);
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਜੇ (present)
    ਲਈ (ਰੁੱਖ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_MOTION_PRESENT (c) = 1;

  ਜੇ (iterators)
    {
      ਰੁੱਖ ਖੰਡ = ਕੱਢੋ_scope ();
      ਜੇ (iterators == error_mark_ਗੰਢ)
	iterators = NULL_ਰੁੱਖ;
      ਨਹੀਂਤਾਂ
	OMP_ITERATOR_ਖੰਡ (iterators) = ਖੰਡ;
    }

  ਜੇ (iterators)
    ਲਈ (ਰੁੱਖ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE_ITERATORS (c) = iterators;

  ਜੇ (mapper_name)
    {
      ਰੁੱਖ ਆਖਰੀ_new = NULL_ਰੁੱਖ;
      ਲਈ (ਰੁੱਖ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
	ਆਖਰੀ_new = c;

      ਰੁੱਖ name = build_omp_clause (ਨਿਵੇਸ਼_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (name, GOMP_MAP_ਧੱਕੋ_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = mapper_name;
      OMP_CLAUSE_CHAIN (name) = nl;
      nl = name;

      gcc_assert (ਆਖਰੀ_new);

      name = build_omp_clause (ਨਿਵੇਸ਼_location, OMP_CLAUSE_MAP);
      OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (name, GOMP_MAP_ਕੱਢੋ_MAPPER_NAME);
      OMP_CLAUSE_DECL (name) = null_ਸੂਚਕ_ਗੰਢ;
      OMP_CLAUSE_CHAIN (name) = OMP_CLAUSE_CHAIN (ਆਖਰੀ_new);
      OMP_CLAUSE_CHAIN (ਆਖਰੀ_new) = name;
    }

  ਵਾਪਸ nl;
}

/* OpenMP 4.0:
   uniform ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਇਕਸਾਰ (c_parser *parser, ਰੁੱਖ list)
{
  /* The clauses location.  */
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      list = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ਇਕਸਾਰ,
					 list);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }
  ਵਾਪਸ list;
}

/* OpenMP 5.1
ਭਰਿਆ*/

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_ਭਰਿਆ (c_parser *parser, ਰੁੱਖ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_ਭਰਿਆ, "full");

  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ c = build_omp_clause (loc, OMP_CLAUSE_ਭਰਿਆ);
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 5.1
   partial ( constant-expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_partial (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ ਅੰਕ = NULL_ਰੁੱਖ;
  location_t loc = c_parser_peek_token (parser)->location;

  check_no_duplicate_clause (list, OMP_CLAUSE_PARTIAL, "partial");

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      matching_parens parens;
      parens.consume_open (parser);
      ਅੰਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
      parens.skip_until_ਮਿਲਿਆ_close (parser);

      ਜੇ (ਅੰਕ == error_mark_ਗੰਢ)
	ਵਾਪਸ list;

      mark_exp_read (ਅੰਕ);
      ਅੰਕ = c_fully_fold (ਅੰਕ, ਝੂਠ, ਨਿਰਾ);
      HOST_WIDE_INT n;
      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਅੰਕ))
	  || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_shwi_p (ਅੰਕ)
	  || (n = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (ਅੰਕ)) <= 0
	  || (ਪੂਰਨ) n != n)
	{
	  error_at (loc, "%<partial%> argument needs positive constant "
			 "integer expression");
	  ਵਾਪਸ list;
	}
    }

  ਰੁੱਖ c = build_omp_clause (loc, OMP_CLAUSE_PARTIAL);
  OMP_CLAUSE_PARTIAL_ਵਿਅੰਜਕ (c) = ਅੰਕ;
  OMP_CLAUSE_CHAIN (c) = list;
  ਵਾਪਸ c;
}

/* OpenMP 5.1
   novariants ( scalar-expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_novariants (c_parser *parser, ਰੁੱਖ list)
{
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  ਰੁੱਖ t = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOVARIANTS, "novariants");

  ਰੁੱਖ c = build_omp_clause (loc, OMP_CLAUSE_NOVARIANTS);
  OMP_CLAUSE_NOVARIANTS_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ਵਾਪਸ list;
}

/* OpenMP 5.1
   nocontext ( scalar-expression ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_nocontext (c_parser *parser, ਰੁੱਖ list)
{
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  location_t loc = c_parser_peek_token (parser)->location;
  c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
  ਰੁੱਖ t = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (loc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
  t = c_objc_common_truthvalue_conversion (loc, t);
  t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  check_no_duplicate_clause (list, OMP_CLAUSE_NOCONTEXT, "nocontext");

  ਰੁੱਖ c = build_omp_clause (loc, OMP_CLAUSE_NOCONTEXT);
  OMP_CLAUSE_NOCONTEXT_ਵਿਅੰਜਕ (c) = t;
  OMP_CLAUSE_CHAIN (c) = list;
  list = c;

  ਵਾਪਸ list;
}

/* OpenMP 5.0:
   detach ( event-handle ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_detach (c_parser *parser, ਰੁੱਖ list)
{
  matching_parens parens;
  location_t clause_loc = c_parser_peek_token (parser)->location;

  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_ਕਿਸਮ != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਵਾਪਸ list;
    }

  ਰੁੱਖ t = lookup_name (c_parser_peek_token (parser)->ਮੁੱਲ);
  ਜੇ (t == NULL_ਰੁੱਖ)
    {
      undeclared_variable (c_parser_peek_token (parser)->location,
			   c_parser_peek_token (parser)->ਮੁੱਲ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਵਾਪਸ list;
    }
  c_parser_consume_token (parser);

  ਰੁੱਖ type = TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (t));
  ਜੇ (!INTEGRAL_TYPE_P (type)
      || ਰੁੱਖ_ਕੋਡ (type) != ENUMERAL_TYPE
      || TYPE_NAME (type) != get_identifier ("omp_event_handle_t"))
    {
      error_at (clause_loc, "%<detach%> clause event handle "
			    "has type %qT rather than "
			    "%<omp_event_handle_t%>",
			    type);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਵਾਪਸ list;
    }

  ਰੁੱਖ u = build_omp_clause (clause_loc, OMP_CLAUSE_DETACH);
  OMP_CLAUSE_DECL (u) = t;
  OMP_CLAUSE_CHAIN (u) = list;
  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਵਾਪਸ u;
}

/* OpenMP 5.0:
   destroy ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_destroy (c_parser *parser, ਰੁੱਖ list)
{
  ਰੁੱਖ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_DESTROY, list);
  ਲਈ (ਰੁੱਖ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    ਰੁੱਖ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
  ਵਾਪਸ nl;
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_modifier_prefer_type (c_parser *parser)
{
  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ਵਾਪਸ error_mark_ਗੰਢ;

  std::string str;

  /* Old Format: const-int-expr-or-string-literal-list */
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    ਜਦੋਂ (ਸੱਚ)
      {
	str += (ਅੱਖਰ) GOMP_INTEROP_IFR_SEPARATOR;
	ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_STRING))
	  {
	    c_ਵਿਅੰਜਕ cval = c_parser_string_literal (parser, ਝੂਠ, ਝੂਠ);
	    ਜੇ (cval.ਮੁੱਲ == error_mark_ਗੰਢ)
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    ਜੇ ((ਮਾਪ_t) ਰੁੱਖ_STRING_ਲੰਮਾਈ (cval.ਮੁੱਲ)
		!= ਲੜੀ_ਲੰਬਾਈ (ਰੁੱਖ_STRING_ਸੂਚਕ (cval.ਮੁੱਲ)) + 1)
	      {
		error_at (cval.get_location (), "string literal must "
						"not contain %<\\0%>");
		parser->error = ਸੱਚ;
		ਵਾਪਸ error_mark_ਗੰਢ;
	      }

	    ਅੱਖਰ c = omp_get_fr_id_from_name (ਰੁੱਖ_STRING_ਸੂਚਕ (cval.ਮੁੱਲ));
	    ਜੇ (c == GOMP_INTEROP_IFR_UNKNOWN)
	      warning_at (cval.get_location (), OPT_Wopenmp,
			  "unknown foreign runtime identifier %qs",
			  ਰੁੱਖ_STRING_ਸੂਚਕ (cval.ਮੁੱਲ));
	    str += c;
	  }
	ਨਹੀਂਤਾਂ
	  {
	    c_ਵਿਅੰਜਕ cval = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	    ਰੁੱਖ ਮੁੱਲ = c_fully_fold (cval.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	    ਜੇ (INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਮੁੱਲ))
		&& ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST)
	      ਮੁੱਲ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (cval.get_ਸ਼ੁਰੂ (), cval,
						ਝੂਠ, ਸੱਚ).ਮੁੱਲ;
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST
		|| !ਰੁੱਖ_ਸਮਾਉਂਦਾ_shwi_p (ਮੁੱਲ))
	      {
		c_parser_error (parser, "expected string literal or constant "
					"integer expression");
		ਵਾਪਸ error_mark_ਗੰਢ;
	      }
	    HOST_WIDE_INT n = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (ਮੁੱਲ);
	    ਜੇ (n < 1 || n > GOMP_INTEROP_IFR_ਆਖਰੀ)
	      {
		warning_at (cval.get_location (), OPT_Wopenmp,
			    "unknown foreign runtime identifier %qwd", n);
		n = GOMP_INTEROP_IFR_UNKNOWN;
	      }
	    str += (ਅੱਖਰ) n;
	  }
	str += (ਅੱਖਰ) GOMP_INTEROP_IFR_SEPARATOR;
	str += '\0';
	ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	  {
	    c_parser_consume_token (parser);
	    ਜਾਰੀ;
	  }
	ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN,
			       "expected %<,%> or %<)%>"))
	  ਵਾਪਸ error_mark_ਗੰਢ;
	str += '\0';
	ਰੁੱਖ res = build_string (str.ਲੰਮਾਈ (), str.ਅੰਕੜੇ ());
	ਰੁੱਖ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ਗੰਢ,
						  str.ਲੰਮਾਈ ());
	ਵਾਪਸ res;
      }

  /* New format. */
  std::string str2;
  ਜਦੋਂ (ਸੱਚ)
    {
      ਜੇ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	ਵਾਪਸ error_mark_ਗੰਢ;
      str += (ਅੱਖਰ) GOMP_INTEROP_IFR_SEPARATOR;
      str2.clear ();
      ਤਾਰਕਿਕ has_fr = ਝੂਠ;
      ਜਦੋਂ (ਸੱਚ)
	{
	  c_token *tok = c_parser_peek_token (parser);
	  ਜੇ (tok->type != CPP_NAME
	      || (strcmp("fr", IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ)) != 0
		  && strcmp("attr", IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ)) != 0))
	    {
	      c_parser_error (parser, "expected %<fr%> or %<attr%> preference "
				      "selector");
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
	  c_parser_consume_token (parser);
	  ਤਾਰਕਿਕ is_fr = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ)[0] == 'f';
	  ਜੇ (is_fr && has_fr)
	    {
	      c_parser_error (parser, "duplicated %<fr%> preference selector");
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
	  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ਵਾਪਸ error_mark_ਗੰਢ;
	  ਜਦੋਂ (ਸੱਚ)
	    {
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_STRING))
		{
		  c_ਵਿਅੰਜਕ cval = c_parser_string_literal (parser, ਝੂਠ, ਝੂਠ);
		  ਰੁੱਖ ਮੁੱਲ = cval.ਮੁੱਲ;
		  ਜੇ (ਮੁੱਲ == error_mark_ਗੰਢ)
		    ਵਾਪਸ error_mark_ਗੰਢ;
		  ਜੇ ((ਮਾਪ_t) ਰੁੱਖ_STRING_ਲੰਮਾਈ (ਮੁੱਲ)
		      != ਲੜੀ_ਲੰਬਾਈ (ਰੁੱਖ_STRING_ਸੂਚਕ (ਮੁੱਲ)) + 1)
		    {
		      error_at (cval.get_location (), "string literal must "
						      "not contain %<\\0%>");
		      parser->error = ਸੱਚ;
		      ਵਾਪਸ error_mark_ਗੰਢ;
		    }
		  ਜੇ (!is_fr)
		    {
		      ਜੇ (!startswith (ਰੁੱਖ_STRING_ਸੂਚਕ (ਮੁੱਲ), "ompx_"))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must start with "
				    "%<ompx_%>");
			  parser->error = ਸੱਚ;
			  ਵਾਪਸ error_mark_ਗੰਢ;
			}
		      ਜੇ (strchr (ਰੁੱਖ_STRING_ਸੂਚਕ (ਮੁੱਲ), ','))
			{
			  error_at (cval.get_location (),
				    "%<attr%> string literal must not contain "
				    "a comma");
			  parser->error = ਸੱਚ;
			  ਵਾਪਸ error_mark_ਗੰਢ;
			}
		      str2 += ਰੁੱਖ_STRING_ਸੂਚਕ (ਮੁੱਲ);
		      str2 += '\0';
		    }
		  ਨਹੀਂਤਾਂ
		    {
		      ਜੇ (*ਰੁੱਖ_STRING_ਸੂਚਕ (ਮੁੱਲ) == '\0')
			{
			  c_parser_error (parser, "non-empty string literal expected");
			  ਵਾਪਸ error_mark_ਗੰਢ;
			}
		      ਅੱਖਰ c = omp_get_fr_id_from_name (ਰੁੱਖ_STRING_ਸੂਚਕ (ਮੁੱਲ));
		      ਜੇ (c == GOMP_INTEROP_IFR_UNKNOWN)
			warning_at (cval.get_location (), OPT_Wopenmp,
				    "unknown foreign runtime identifier %qs",
				    ਰੁੱਖ_STRING_ਸੂਚਕ (ਮੁੱਲ));
		     str += c;
		     has_fr = ਸੱਚ;
		    }
		}
	      ਨਹੀਂਤਾਂ ਜੇ (!is_fr)
		{
		  c_parser_error (parser, "expected string literal");
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	      ਨਹੀਂਤਾਂ
		{
		  c_ਵਿਅੰਜਕ cval = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
		  ਰੁੱਖ ਮੁੱਲ = c_fully_fold (cval.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
		  ਜੇ (INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਮੁੱਲ))
		      && ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST)
		    ਮੁੱਲ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (cval.get_ਸ਼ੁਰੂ (), cval,
						      ਝੂਠ, ਸੱਚ).ਮੁੱਲ;

		  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਮੁੱਲ) != INTEGER_CST
		      || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_shwi_p (ਮੁੱਲ))
		    {
		      c_parser_error (parser, "expected string literal or "
					      "constant integer expression");
		      ਵਾਪਸ error_mark_ਗੰਢ;
		    }
		  HOST_WIDE_INT n = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (ਮੁੱਲ);
		  ਜੇ (n < 1 || n > GOMP_INTEROP_IFR_ਆਖਰੀ)
		    {
		      warning_at (cval.get_location (), OPT_Wopenmp,
				  "unknown foreign runtime identifier %qwd", n);
		      n = GOMP_INTEROP_IFR_UNKNOWN;
		    }
		  str += (ਅੱਖਰ) n;
		  has_fr = ਸੱਚ;
		}
	      ਜੇ (!is_fr
		  && c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ਜਾਰੀ;
		}
	      ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN,
				     is_fr ? G_("expected %<)%>")
					   : G_("expected %<)%> or %<,%>")))
		ਵਾਪਸ error_mark_ਗੰਢ;
	      ਰੋਕੋ;
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ਜਾਰੀ;
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	    ਰੋਕੋ;
	  c_parser_error (parser, "expected %<,%> or %<}%>");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      str += (ਅੱਖਰ) GOMP_INTEROP_IFR_SEPARATOR;
      str += str2;
      str += '\0';
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	ਰੋਕੋ;
      ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
	ਵਾਪਸ error_mark_ਗੰਢ;
    }
  c_parser_consume_token (parser);
  str += '\0';
  ਰੁੱਖ res = build_string (str.ਲੰਮਾਈ (), str.ਅੰਕੜੇ ());
  ਰੁੱਖ_TYPE (res) = build_array_type_nelts (unsigned_char_type_ਗੰਢ,
						  str.ਲੰਮਾਈ ());
  ਵਾਪਸ res;
}

/* OpenMP 5.1
     modifiers of the 'init' clause, used by the 'init' and the
     'append_args' clauses.

   Modifiers:
ਨਿਸ਼ਾਨਾ
     targetsync
     prefer_type (preference-specification)

  Returns 'false' if an error has been issued.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_clause_init_modifiers (c_parser *parser, ਤਾਰਕਿਕ *ਨਿਸ਼ਾਨਾ,
				    ਤਾਰਕਿਕ *targetsync, ਰੁੱਖ *prefer_type_ਰੁੱਖ)
{
  *ਨਿਸ਼ਾਨਾ = ਝੂਠ;
  *targetsync = ਝੂਠ;
  *prefer_type_ਰੁੱਖ = NULL_ਰੁੱਖ;

  ਕਰੋ
    {
      c_token *tok = c_parser_peek_token (parser);
      ਜੇ (tok->type != CPP_NAME)
	ਜਾਓ fail;
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
      ਜੇ (strcmp ("targetsync", p) == 0)
	{
	  ਜੇ (*targetsync)
	    error_at (tok->location, "duplicate %<targetsync%> modifier");
	  *targetsync = ਸੱਚ;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("target", p) == 0)
	{
	  ਜੇ (*ਨਿਸ਼ਾਨਾ)
	    error_at (tok->location, "duplicate %<target%> modifier");
	  *ਨਿਸ਼ਾਨਾ = ਸੱਚ;
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp ("prefer_type", p) == 0)
	{
	  ਜੇ (*prefer_type_ਰੁੱਖ != NULL_ਰੁੱਖ)
	    error_at (tok->location, "duplicate %<prefer_type%> modifier");
	  c_parser_consume_token (parser);
	  *prefer_type_ਰੁੱਖ = c_parser_omp_modifier_prefer_type (parser);
	  ਜੇ (*prefer_type_ਰੁੱਖ == error_mark_ਗੰਢ)
	    ਵਾਪਸ ਝੂਠ;
	}
      ਨਹੀਂਤਾਂ
	ਜਾਓ fail;
      tok = c_parser_peek_token (parser);
      ਜੇ (tok->type == CPP_COMMA)
	{
	  c_parser_consume_token (parser);
	  ਜਾਰੀ;
	}
      /* Unknown token - either done or an error; handle it in the caller.  */
      ਵਾਪਸ ਸੱਚ;
    }
  ਜਦੋਂ (ਸੱਚ);

fail:
  c_parser_error (parser,
		  "expected %<prefer_type%>, %<target%>, or %<targetsync%>");
  ਵਾਪਸ ਝੂਠ;
}

/* OpenMP 5.1:
   init ( [init-modifier-list : ] variable-list )

   Modifiers:
ਨਿਸ਼ਾਨਾ
     targetsync
     prefer_type (preference-specification) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_init (c_parser *parser, ਰੁੱਖ list)
{
  location_t loc = c_parser_peek_token (parser)->location;

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ list;

  ਤਾਰਕਿਕ ਨਿਸ਼ਾਨਾ = ਝੂਠ;
  ਤਾਰਕਿਕ targetsync = ਝੂਠ;
  ਰੁੱਖ prefer_type_ਰੁੱਖ = NULL_ਰੁੱਖ;

  ਜੇ (!c_parser_omp_clause_init_modifiers (parser, &ਨਿਸ਼ਾਨਾ, &targetsync,
					   &prefer_type_ਰੁੱਖ)
      || !c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    {
      ਜੇ (prefer_type_ਰੁੱਖ != error_mark_ਗੰਢ)
	parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਵਾਪਸ list;
    }

  ਜੇ (!ਨਿਸ਼ਾਨਾ && !targetsync)
    error_at (loc,
	      "missing required %<target%> and/or %<targetsync%> modifier");

  ਰੁੱਖ nl = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_INIT, list,
					ਝੂਠ);
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਲਈ (ਰੁੱਖ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      ਰੁੱਖ_ADDRESSABLE (OMP_CLAUSE_DECL (c)) = 1;
      ਜੇ (ਨਿਸ਼ਾਨਾ)
	OMP_CLAUSE_INIT_ਨਿਸ਼ਾਨਾ (c) = 1;
      ਜੇ (targetsync)
	OMP_CLAUSE_INIT_TARGETSYNC (c) = 1;
      ਜੇ (prefer_type_ਰੁੱਖ)
	OMP_CLAUSE_INIT_PREFER_TYPE (c) = prefer_type_ਰੁੱਖ;
    }
  ਵਾਪਸ nl;
}

/* OpenMP 5.0:
   use ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_use (c_parser *parser, ਰੁੱਖ list)
{
  ਵਾਪਸ c_parser_omp_var_list_parens (parser, OMP_CLAUSE_USE, list);
}

/* OpenMP 6.0:
   interop ( variable-list ) */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_clause_interop (c_parser *parser, ਰੁੱਖ list)
{
  check_no_duplicate_clause (list, OMP_CLAUSE_INTEROP, "interop");
  ਰੁੱਖ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_INTEROP, list);
  ਲਈ (ਰੁੱਖ c = nl; c != list; c = OMP_CLAUSE_CHAIN (c))
    {
      ਰੁੱਖ_ਵਰਤਿਆ (OMP_CLAUSE_DECL (c)) = 1;
      DECL_READ_P (OMP_CLAUSE_DECL (c)) = 1;
    }
  ਵਾਪਸ nl;
}

/* Parse all OpenACC clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_all_clauses (c_parser *parser, omp_clause_ਨਕਾਬ ਨਕਾਬ,
			   ਅਚਲ ਅੱਖਰ *where, ਤਾਰਕਿਕ ਅੰਤ_p = ਸੱਚ,
			   ਤਾਰਕਿਕ ਨਿਸ਼ਾਨਾ_p = ਝੂਠ)
{
  ਰੁੱਖ clauses = ਨਿਰਾ;
  ਤਾਰਕਿਕ ਪਹਿਲਾ = ਸੱਚ;

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t ਇੱਥੇ;
      pragma_omp_clause c_ਕਿਸਮ;
      ਅਚਲ ਅੱਖਰ *c_name;
      ਰੁੱਖ prev = clauses;

      ਜੇ (!ਪਹਿਲਾ && c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      ਇੱਥੇ = c_parser_peek_token (parser)->location;
      c_ਕਿਸਮ = c_parser_omp_clause_name (parser);

      ਚੋਣ (c_ਕਿਸਮ)
	{
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_ASYNC:
	  clauses = c_parser_oacc_clause_async (parser, clauses);
	  c_name = "async";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_AUTO:
	  clauses = c_parser_oacc_simple_clause (ਇੱਥੇ, OMP_CLAUSE_AUTO,
						 clauses);
	  c_name = "auto";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_ATTACH:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "attach";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_COPY:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "copy";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_COPYIN:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "copyin";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_COPYOUT:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "copyout";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_CREATE:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "create";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_DELETE:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "delete";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, ਸੱਚ);
	  c_name = "default";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_DETACH:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "detach";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_DEVICE:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "device";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_DEVICEPTR:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause_deviceptr (parser, clauses);
	  c_name = "deviceptr";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "device_resident";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_FINALIZE:
	  clauses = c_parser_oacc_simple_clause (ਇੱਥੇ, OMP_CLAUSE_FINALIZE,
						 clauses);
	  c_name = "finalize";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_GANG:
	  c_name = "gang";
	  clauses = c_parser_oacc_shape_clause (parser, ਇੱਥੇ, OMP_CLAUSE_GANG,
						c_name, clauses);
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_HOST:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "host";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, ਝੂਠ);
	  c_name = "if";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_IF_PRESENT:
	  clauses = c_parser_oacc_simple_clause (ਇੱਥੇ, OMP_CLAUSE_IF_PRESENT,
						 clauses);
	  c_name = "if_present";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_INDEPENDENT:
	  clauses = c_parser_oacc_simple_clause (ਇੱਥੇ, OMP_CLAUSE_INDEPENDENT,
						 clauses);
	  c_name = "independent";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_LINK:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "link";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_NO_CREATE:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "no_create";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_NOHOST:
	  clauses = c_parser_oacc_simple_clause (ਇੱਥੇ, OMP_CLAUSE_NOHOST,
						 clauses);
	  c_name = "nohost";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_ਅੰਕ_GANGS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_ਅੰਕ_GANGS,
						     clauses);
	  c_name = "num_gangs";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_ਅੰਕ_WORKERS:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_ਅੰਕ_WORKERS,
						     clauses);
	  c_name = "num_workers";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_PRESENT:
	  clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "present";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_ਨਿੱਜੀ:
	  clauses = c_parser_omp_clause_ਨਿੱਜੀ (parser, clauses);
	  c_name = "private";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     ਝੂਠ, clauses);
	  c_name = "reduction";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_SELF:
	  ਜੇ ((ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_HOST)) == 0)
	    /* OpenACC compute construct */
	    clauses = c_parser_oacc_compute_clause_self (parser, clauses);
	  ਨਹੀਂਤਾਂ
	    /* OpenACC 'update' directive */
	    clauses = c_parser_oacc_ਅੰਕੜੇ_clause (parser, c_ਕਿਸਮ, clauses);
	  c_name = "self";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_SEQ:
	  clauses = c_parser_oacc_simple_clause (ਇੱਥੇ, OMP_CLAUSE_SEQ,
						 clauses);
	  c_name = "seq";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_TILE:
	  clauses = c_parser_oacc_clause_tile (parser, clauses);
	  c_name = "tile";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_USE_DEVICE:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_ਸਦਿਸ਼:
	  c_name = "vector";
	  clauses = c_parser_oacc_shape_clause (parser, ਇੱਥੇ, OMP_CLAUSE_ਸਦਿਸ਼,
						c_name,	clauses);
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_ਸਦਿਸ਼_ਲੰਮਾਈ:
	  clauses = c_parser_oacc_single_int_clause (parser,
						     OMP_CLAUSE_ਸਦਿਸ਼_ਲੰਮਾਈ,
						     clauses);
	  c_name = "vector_length";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_WAIT:
	  clauses = c_parser_oacc_clause_wait (parser, clauses);
	  c_name = "wait";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OACC_CLAUSE_ਕਾਮਾ:
	  c_name = "worker";
	  clauses = c_parser_oacc_shape_clause (parser, ਇੱਥੇ, OMP_CLAUSE_ਕਾਮਾ,
						c_name, clauses);
	  ਰੋਕੋ;
	ਮੂਲ:
	  c_parser_error (parser, "expected an OpenACC clause");
	  ਜਾਓ saw_error;
	}

      ਪਹਿਲਾ = ਝੂਠ;

      ਜੇ (((ਨਕਾਬ >> c_ਕਿਸਮ) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (ਇੱਥੇ, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  ਜੇ (ਅੰਤ_p)
    ਵਾਪਸ c_ਅੰਤ_omp_clauses (clauses, ਨਿਸ਼ਾਨਾ_p ? C_ORT_ACC_ਨਿਸ਼ਾਨਾ
						   : C_ORT_ACC);

  ਵਾਪਸ clauses;
}

/* Parse all OpenMP clauses.  The set clauses allowed by the directive
   is a bitmask in MASK.  Return the list of clauses found.
   FINISH_P set if c_finish_omp_clauses should be called.
   NESTED non-zero if clauses should be terminated by closing paren instead
   of end of pragma.  If it is 2, additionally commas are required in between
   the clauses.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_all_clauses (c_parser *parser, omp_clause_ਨਕਾਬ ਨਕਾਬ,
			  ਅਚਲ ਅੱਖਰ *where, ਤਾਰਕਿਕ ਅੰਤ_p = ਸੱਚ,
			  ਪੂਰਨ nested = 0)
{
  ਰੁੱਖ clauses = ਨਿਰਾ;
  ਤਾਰਕਿਕ ਪਹਿਲਾ = ਸੱਚ;

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t ਇੱਥੇ;
      pragma_omp_clause c_ਕਿਸਮ;
      ਅਚਲ ਅੱਖਰ *c_name;
      ਰੁੱਖ prev = clauses;

      ਜੇ (nested && c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	ਰੋਕੋ;

      ਜੇ (!ਪਹਿਲਾ || nested != 2)
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ਨਹੀਂਤਾਂ ਜੇ (nested == 2)
	    error_at (c_parser_peek_token (parser)->location,
		      "clauses in %<simd%> trait should be separated "
		      "by %<,%>");
	}

      ਇੱਥੇ = c_parser_peek_token (parser)->location;
      c_ਕਿਸਮ = c_parser_omp_clause_name (parser);

      ਚੋਣ (c_ਕਿਸਮ)
	{
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_BIND:
	  clauses = c_parser_omp_clause_bind (parser, clauses);
	  c_name = "bind";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_COLLAPSE:
	  clauses = c_parser_omp_clause_collapse (parser, clauses);
	  c_name = "collapse";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses, ਝੂਠ);
	  c_name = "default";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DETACH:
	  clauses = c_parser_omp_clause_detach (parser, clauses);
	  c_name = "detach";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_FILTER:
	  clauses = c_parser_omp_clause_filter (parser, clauses);
	  c_name = "filter";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_FINAL:
	  clauses = c_parser_omp_clause_final (parser, clauses);
	  c_name = "final";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_GRAINSIZE:
	  clauses = c_parser_omp_clause_grainsize (parser, clauses);
	  c_name = "grainsize";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_HINT:
	  clauses = c_parser_omp_clause_hint (parser, clauses);
	  c_name = "hint";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DEFAULTMAP:
	  clauses = c_parser_omp_clause_defaultmap (parser, clauses);
	  c_name = "defaultmap";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses, ਸੱਚ);
	  c_name = "if";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਵਿੱਚ_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_ਵਿੱਚ_REDUCTION,
					     ਸੱਚ, clauses);
	  c_name = "in_reduction";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਅਸਿੱਧਾ:
	  clauses = c_parser_omp_clause_ਅਸਿੱਧਾ (parser, clauses);
	  c_name = "indirect";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_MERGEABLE:
	  clauses = c_parser_omp_clause_mergeable (parser, clauses);
	  c_name = "mergeable";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਅੰਕ_TASKS:
	  clauses = c_parser_omp_clause_ਅੰਕ_tasks (parser, clauses);
	  c_name = "num_tasks";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਅੰਕ_ਧਾਗੇ:
	  clauses = c_parser_omp_clause_ਅੰਕ_ਧਾਗੇ (parser, clauses);
	  c_name = "num_threads";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਕ੍ਰਮ:
	  clauses = c_parser_omp_clause_ਕ੍ਰਮ (parser, clauses);
	  c_name = "order";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਤਰਜੀਹ:
	  clauses = c_parser_omp_clause_ਤਰਜੀਹ (parser, clauses);
	  c_name = "priority";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ:
	  clauses = c_parser_omp_clause_ਨਿੱਜੀ (parser, clauses);
	  c_name = "private";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_REDUCTION,
					     ਸੱਚ, clauses);
	  c_name = "reduction";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ:
	  clauses = c_parser_omp_clause_ਸਮਾਂ_ਸਾਰਣੀ (parser, clauses);
	  c_name = "schedule";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_TASK_REDUCTION:
	  clauses
	    = c_parser_omp_clause_reduction (parser, OMP_CLAUSE_TASK_REDUCTION,
					     ਸੱਚ, clauses);
	  c_name = "task_reduction";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_UNTIED:
	  clauses = c_parser_omp_clause_untied (parser, clauses);
	  c_name = "untied";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_INBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_INBRANCH,
						clauses);
	  c_name = "inbranch";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_NONTEMPORAL:
	  clauses = c_parser_omp_clause_nontemporal (parser, clauses);
	  c_name = "nontemporal";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_NOTINBRANCH:
	  clauses = c_parser_omp_clause_branch (parser, OMP_CLAUSE_NOTINBRANCH,
						clauses);
	  c_name = "notinbranch";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_PARALLEL:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_PARALLEL,
					      clauses);
	  c_name = "parallel";
	  ਜੇ (!ਪਹਿਲਾ)
	    {
	     clause_not_ਪਹਿਲਾ:
	      error_at (ਇੱਥੇ, "%qs must be the first clause of %qs",
			c_name, where);
	      clauses = prev;
	    }
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_FOR:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_FOR,
					      clauses);
	  c_name = "for";
	  ਜੇ (!ਪਹਿਲਾ)
	    ਜਾਓ clause_not_ਪਹਿਲਾ;
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_SECTIONS:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_SECTIONS,
					      clauses);
	  c_name = "sections";
	  ਜੇ (!ਪਹਿਲਾ)
	    ਜਾਓ clause_not_ਪਹਿਲਾ;
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_TASKGROUP:
	  clauses
	    = c_parser_omp_clause_cancelkind (parser, OMP_CLAUSE_TASKGROUP,
					      clauses);
	  c_name = "taskgroup";
	  ਜੇ (!ਪਹਿਲਾ)
	    ਜਾਓ clause_not_ਪਹਿਲਾ;
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_LINK:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LINK, clauses);
	  c_name = "link";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_LOCAL:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LOCAL, clauses);
	  c_name = "local";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਮੰਜ਼ਿਲ:
	  ਜੇ ((ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LINK)) != 0)
	    {
	      gcc_rich_location richloc (ਇੱਥੇ);
	      richloc.ਜੋੜੋ_fixit_replace ("enter");
	      warning_at (&richloc, OPT_Wdeprecated_openmp,
			  "%<to%> clause with %<declare target%> deprecated "
			  "since OpenMP 5.2, use %<enter%>");
	      ਰੁੱਖ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
						      clauses);
	      ਲਈ (ਰੁੱਖ c = nl; c != clauses; c = OMP_CLAUSE_CHAIN (c))
		OMP_CLAUSE_ENTER_ਮੰਜ਼ਿਲ (c) = 1;
	      clauses = nl;
	    }
	  ਨਹੀਂਤਾਂ
	    clauses = c_parser_omp_clause_from_ਮੰਜ਼ਿਲ (parser, OMP_CLAUSE_ਮੰਜ਼ਿਲ,
						   clauses);
	  c_name = "to";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_FROM:
	  clauses = c_parser_omp_clause_from_ਮੰਜ਼ਿਲ (parser, OMP_CLAUSE_FROM,
						 clauses);
	  c_name = "from";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਇਕਸਾਰ:
	  clauses = c_parser_omp_clause_ਇਕਸਾਰ (parser, clauses);
	  c_name = "uniform";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਅੰਕ_TEAMS:
	  clauses = c_parser_omp_clause_ਅੰਕ_teams (parser, clauses);
	  c_name = "num_teams";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ:
	  clauses = c_parser_omp_clause_thread_ਹੱਦਬੰਦੀ (parser, clauses);
	  c_name = "thread_limit";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ALIGNED:
	  clauses = c_parser_omp_clause_aligned (parser, clauses);
	  c_name = "aligned";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ALLOCATE:
	  clauses = c_parser_omp_clause_allocate (parser, clauses);
	  c_name = "allocate";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਰੇਖਿਕ:
	  clauses = c_parser_omp_clause_ਰੇਖਿਕ (parser, clauses);
	  c_name = "linear";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS:
	  clauses = c_parser_omp_clause_ਵਰਤਦਾ_allocators (parser, clauses);
	  c_name = "uses_allocators";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_AFFINITY:
	  clauses = c_parser_omp_clause_affinity (parser, clauses);
	  c_name = "affinity";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DEPEND:
	  clauses = c_parser_omp_clause_depend (parser, clauses, ਇੱਥੇ);
	  c_name = "depend";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DOACROSS:
	  clauses = c_parser_omp_clause_doacross (parser, clauses);
	  c_name = "doacross";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DESTROY:
	  clauses = c_parser_omp_clause_destroy (parser, clauses);
	  c_name = "destroy";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE:
	  clauses = c_parser_omp_clause_dyn_groupprivate (parser, clauses);
	  c_name = "dyn_groupprivate";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_INIT:
	  clauses = c_parser_omp_clause_init (parser, clauses);
	  c_name = "init";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_USE:
	  clauses = c_parser_omp_clause_use (parser, clauses);
	  c_name = "use";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_INTEROP:
	  clauses = c_parser_omp_clause_interop (parser, clauses);
	  c_name = "interop";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_MAP:
	  clauses = c_parser_omp_clause_map (parser, clauses, ਝੂਠ);
	  c_name = "map";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR:
	  clauses = c_parser_omp_clause_use_device_ptr (parser, clauses);
	  c_name = "use_device_ptr";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_use_device_addr (parser, clauses);
	  c_name = "use_device_addr";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR:
	  clauses = c_parser_omp_clause_has_device_addr (parser, clauses);
	  c_name = "has_device_addr";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR:
	  clauses = c_parser_omp_clause_is_device_ptr (parser, clauses);
	  c_name = "is_device_ptr";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DEVICE:
	  clauses = c_parser_omp_clause_device (parser, clauses);
	  c_name = "device";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ:
	  clauses = c_parser_omp_clause_dist_ਸਮਾਂ_ਸਾਰਣੀ (parser, clauses);
	  c_name = "dist_schedule";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_PROC_BIND:
	  clauses = c_parser_omp_clause_proc_bind (parser, clauses);
	  c_name = "proc_bind";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_DEVICE_TYPE:
	  clauses = c_parser_omp_clause_device_type (parser, clauses);
	  c_name = "device_type";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_SAFELEN:
	  clauses = c_parser_omp_clause_safelen (parser, clauses);
	  c_name = "safelen";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_SIMDLEN:
	  clauses = c_parser_omp_clause_simdlen (parser, clauses);
	  c_name = "simdlen";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_NOGROUP:
	  clauses = c_parser_omp_clause_nogroup (parser, clauses);
	  c_name = "nogroup";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਧਾਗੇ:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_ਧਾਗੇ,
					       clauses);
	  c_name = "threads";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_SIMD:
	  clauses
	    = c_parser_omp_clause_orderedkind (parser, OMP_CLAUSE_SIMD,
					       clauses);
	  c_name = "simd";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ENTER:
	  clauses
	    = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					    clauses);
	  c_name = "enter";
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_ਭਰਿਆ:
	  c_name = "full";
	  clauses = c_parser_omp_clause_ਭਰਿਆ (parser, clauses);
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_PARTIAL:
	  c_name = "partial";
	  clauses = c_parser_omp_clause_partial (parser, clauses);
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_NOVARIANTS:
	  c_name = "novariants";
	  clauses = c_parser_omp_clause_novariants (parser, clauses);
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_CLAUSE_NOCONTEXT:
	  c_name = "nocontext";
	  clauses = c_parser_omp_clause_nocontext (parser, clauses);
	  ਰੋਕੋ;
	ਮੂਲ:
	  c_parser_error (parser, "expected an OpenMP clause");
	  ਜਾਓ saw_error;
	}

      ਪਹਿਲਾ = ਝੂਠ;

      ਜੇ (((ਨਕਾਬ >> c_ਕਿਸਮ) & 1) == 0)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error_at (ਇੱਥੇ, "%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  ਜੇ (!nested)
    c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  ਜੇ (ਅੰਤ_p)
    {
      ਜੇ ((ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਇਕਸਾਰ)) != 0)
	ਵਾਪਸ c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP_DECLARE_SIMD);
      ਜੇ ((ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_USE)) != 0)
	ਵਾਪਸ c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP_INTEROP);
      ਵਾਪਸ c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP);
    }

  ਵਾਪਸ clauses;
}

/* OpenACC 2.0, OpenMP 2.5:
   structured-block:
     statement

   In practice, we're also interested in adding the statement to an
   outer node.  So it is convenient if we work around the fact that
   c_parser_statement calls add_stmt.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_structured_ਖੰਡ (c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ stmt = ਧੱਕੋ_stmt_list ();
  parser->omp_attrs_forbidden_p = ਸੱਚ;
  c_parser_statement (parser, if_p);
  ਵਾਪਸ ਕੱਢੋ_stmt_list (stmt);
}

/* OpenACC 2.0:
   # pragma acc cache (variable-list) new-line

   OpenACC 2.7:
   # pragma acc cache (readonly: variable-list) new-line

   LOC is the location of the #pragma token.
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_cache (location_t loc, c_parser *parser)
{
  ਰੁੱਖ stmt, clauses = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ readonly = ਝੂਠ;
  location_t open_loc = c_parser_peek_token (parser)->location;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ (token->type == CPP_NAME
	  && !strcmp (IDENTIFIER_ਸੂਚਕ (token->ਮੁੱਲ), "readonly")
	  && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	{
	  c_parser_consume_token (parser);
	  c_parser_consume_token (parser);
	  readonly = ਸੱਚ;
	}
      clauses = c_parser_omp_variable_list (parser, open_loc,
					    OMP_CLAUSE__CACHE_, NULL_ਰੁੱਖ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    }

  ਜੇ (readonly)
    ਲਈ (ਰੁੱਖ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      OMP_CLAUSE__CACHE__READONLY (c) = 1;

  clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_ACC);

  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  stmt = make_ਗੰਢ (OACC_CACHE);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OACC_CACHE_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);

  ਵਾਪਸ stmt;
}

/* OpenACC 2.0:
   # pragma acc data oacc-data-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ						\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_PRESENT))

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_ਅੰਕੜੇ (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ stmt, clauses, ਖੰਡ;

  clauses = c_parser_oacc_all_clauses (parser, OACC_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ,
				       "#pragma acc data");

  ਖੰਡ = c_begin_omp_parallel ();
  ਜੋੜੋ_stmt (c_parser_omp_structured_ਖੰਡ (parser, if_p));

  stmt = c_ਅੰਤ_oacc_ਅੰਕੜੇ (loc, clauses, ਖੰਡ);

  ਵਾਪਸ stmt;
}

/* OpenACC 2.0:
   # pragma acc declare oacc-data-clause[optseq] new-line
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_DECLARE_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEVICE_RESIDENT)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_LINK)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_PRESENT))

ਸਥਿਰ ਖਾਲੀ
c_parser_oacc_declare (c_parser *parser)
{
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ clauses, stmt, t, decl;

  ਤਾਰਕਿਕ error = ਝੂਠ;

  c_parser_consume_pragma (parser);

  clauses = c_parser_oacc_all_clauses (parser, OACC_DECLARE_CLAUSE_ਨਕਾਬ,
				       "#pragma acc declare");
  ਜੇ (!clauses)
    {
      error_at (pragma_loc,
		"no valid clauses specified in %<#pragma acc declare%>");
      ਵਾਪਸ;
    }

  ਲਈ (t = clauses; t; t = OMP_CLAUSE_CHAIN (t))
    {
      location_t loc = OMP_CLAUSE_LOCATION (t);
      decl = OMP_CLAUSE_DECL (t);
      ਜੇ (!DECL_P (decl))
	{
	  error_at (loc, "array section in %<#pragma acc declare%>");
	  error = ਸੱਚ;
	  ਜਾਰੀ;
	}

      ਚੋਣ (OMP_CLAUSE_MAP_ਕਿਸਮ (t))
	{
	ਹਾਲਤ GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ:
	ਹਾਲਤ GOMP_MAP_ALLOC:
	ਹਾਲਤ GOMP_MAP_ਮੰਜ਼ਿਲ:
	ਹਾਲਤ GOMP_MAP_FORCE_DEVICEPTR:
	ਹਾਲਤ GOMP_MAP_DEVICE_RESIDENT:
	  ਰੋਕੋ;

	ਹਾਲਤ GOMP_MAP_LINK:
	  ਜੇ (!global_bindings_p ()
	      && (ਰੁੱਖ_STATIC (decl)
	       || !DECL_EXTERNAL (decl)))
	    {
	      error_at (loc,
			"%qD must be a global variable in "
			"%<#pragma acc declare link%>",
			decl);
	      error = ਸੱਚ;
	      ਜਾਰੀ;
	    }
	  ਰੋਕੋ;

	ਮੂਲ:
	  ਜੇ (global_bindings_p ())
	    {
	      error_at (loc, "invalid OpenACC clause at file scope");
	      error = ਸੱਚ;
	      ਜਾਰੀ;
	    }
	  ਜੇ (DECL_EXTERNAL (decl))
	    {
	      error_at (loc,
			"invalid use of %<extern%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = ਸੱਚ;
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਜਨਤਕ (decl))
	    {
	      error_at (loc,
			"invalid use of %<global%> variable %qD "
			"in %<#pragma acc declare%>", decl);
	      error = ਸੱਚ;
	      ਜਾਰੀ;
	    }
	  ਰੋਕੋ;
	}

      ਜੇ (!c_check_ਵਿੱਚ_current_scope (decl))
	{
	  error_at (loc,
		    "%qD must be a variable declared in the same scope as "
		    "%<#pragma acc declare%>", decl);
	  error = ਸੱਚ;
	  ਜਾਰੀ;
	}

      ਜੇ (lookup_attribute ("omp declare target", DECL_ਗੁਣ (decl))
	  || lookup_attribute ("omp declare target link",
			       DECL_ਗੁਣ (decl)))
	{
	  error_at (loc, "variable %qD used more than once with "
		    "%<#pragma acc declare%>", decl);
	  error = ਸੱਚ;
	  ਜਾਰੀ;
	}

      ਜੇ (!error)
	{
	  ਰੁੱਖ id;

	  ਜੇ (OMP_CLAUSE_MAP_ਕਿਸਮ (t) == GOMP_MAP_LINK)
	    id = get_identifier ("omp declare target link");
	  ਨਹੀਂਤਾਂ
	    id = get_identifier ("omp declare target");

	  DECL_ਗੁਣ (decl)
			   = ਰੁੱਖ_cons (id, NULL_ਰੁੱਖ, DECL_ਗੁਣ (decl));

	  ਜੇ (global_bindings_p ())
	    {
	      symtab_ਗੰਢ *ਗੰਢ = symtab_ਗੰਢ::get (decl);
	      ਜੇ (ਗੰਢ != ਨਿਰਾ)
		{
		  ਗੰਢ->offloadable = 1;
		  ਜੇ (ENABLE_OFFLOADING)
		    {
		      g->have_offload = ਸੱਚ;
		      ਜੇ (is_a <varpool_ਗੰਢ *> (ਗੰਢ))
			vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (offload_vars, decl);
		    }
		}
	    }
	}
    }

  ਜੇ (error || global_bindings_p ())
    ਵਾਪਸ;

  stmt = make_ਗੰਢ (OACC_DECLARE);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OACC_DECLARE_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, pragma_loc);

  ਜੋੜੋ_stmt (stmt);

  ਵਾਪਸ;
}

/* OpenACC 2.0:
   # pragma acc enter data oacc-enter-data-clause[optseq] new-line

   or

   # pragma acc exit data oacc-exit-data-clause[optseq] new-line


   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_ENTER_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_EXIT_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DELETE) 		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DETACH) 		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_FINALIZE) 		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ਸਥਿਰ ਖਾਲੀ
c_parser_oacc_enter_exit_ਅੰਕੜੇ (c_parser *parser, ਤਾਰਕਿਕ enter)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ clauses, stmt;
  ਅਚਲ ਅੱਖਰ *p = "";

  c_parser_consume_pragma (parser);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      c_parser_consume_token (parser);
    }

  ਜੇ (strcmp (p, "data") != 0)
    {
      error_at (loc, "expected %<data%> after %<#pragma acc %s%>",
		enter ? "enter" : "exit");
      parser->error = ਸੱਚ;
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਵਾਪਸ;
    }

  ਜੇ (enter)
    clauses = c_parser_oacc_all_clauses (parser, OACC_ENTER_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ,
					 "#pragma acc enter data");
  ਨਹੀਂਤਾਂ
    clauses = c_parser_oacc_all_clauses (parser, OACC_EXIT_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ,
					 "#pragma acc exit data");

  ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_MAP) == NULL_ਰੁੱਖ)
    {
      error_at (loc, "%<#pragma acc %s data%> has no data movement clause",
		enter ? "enter" : "exit");
      ਵਾਪਸ;
    }

  stmt = enter ? make_ਗੰਢ (OACC_ENTER_ਅੰਕੜੇ) : make_ਗੰਢ (OACC_EXIT_ਅੰਕੜੇ);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_STANDALONE_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);
}


/* OpenACC 2.0:
   # pragma acc host_data oacc-data-clause[optseq] new-line
     structured-block
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_HOST_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_USE_DEVICE)          \
	 | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF)                  \
	 | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT) )

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_host_ਅੰਕੜੇ (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ stmt, clauses, ਖੰਡ;

  clauses = c_parser_oacc_all_clauses (parser, OACC_HOST_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ,
				       "#pragma acc host_data", ਝੂਠ);
  ਜੇ (!omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_USE_DEVICE_PTR))
    {
      error_at (loc, "%<host_data%> construct requires %<use_device%> clause");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_ACC);
  ਖੰਡ = c_begin_omp_parallel ();
  ਜੋੜੋ_stmt (c_parser_omp_structured_ਖੰਡ (parser, if_p));
  stmt = c_ਅੰਤ_oacc_host_ਅੰਕੜੇ (loc, clauses, ਖੰਡ);
  ਵਾਪਸ stmt;
}


/* OpenACC 2.0:

   # pragma acc loop oacc-loop-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_LOOP_CLAUSE_ਨਕਾਬ						\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COLLAPSE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਨਿੱਜੀ)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਕਾਮਾ)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਸਦਿਸ਼)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_AUTO)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_INDEPENDENT) 	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_TILE) )
ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_loop (location_t loc, c_parser *parser, ਅੱਖਰ *p_name,
		    omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses, ਤਾਰਕਿਕ *if_p)
{
  ਤਾਰਕਿਕ is_parallel = ((ਨਕਾਬ >> PRAGMA_OACC_CLAUSE_REDUCTION) & 1) == 1;

  strcat (p_name, " loop");
  ਨਕਾਬ |= OACC_LOOP_CLAUSE_ਨਕਾਬ;

  ਰੁੱਖ clauses = c_parser_oacc_all_clauses (parser, ਨਕਾਬ, p_name,
					    /*finish_p=*/cclauses == ਨਿਰਾ,
					    /*target=*/is_parallel);
  ਜੇ (cclauses)
    {
      clauses = c_oacc_ਵੰਡੋ_loop_clauses (clauses, cclauses, is_parallel);
      ਜੇ (*cclauses)
	*cclauses = c_ਅੰਤ_omp_clauses (*cclauses, C_ORT_ACC_ਨਿਸ਼ਾਨਾ);
      ਜੇ (clauses)
	clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_ACC);
    }

  ਰੁੱਖ ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ਰੁੱਖ stmt = c_parser_omp_for_loop (loc, parser, OACC_LOOP, clauses, ਨਿਰਾ,
				     if_p);
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ stmt;
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_KERNELS_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਅੰਕ_GANGS)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਅੰਕ_WORKERS)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਸਦਿਸ਼_ਲੰਮਾਈ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_PARALLEL_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਨਿੱਜੀ)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਅੰਕ_GANGS)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਅੰਕ_WORKERS)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਸਦਿਸ਼_ਲੰਮਾਈ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_WAIT) )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_SERIAL_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ATTACH)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPY)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYIN)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_COPYOUT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEFAULT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEVICEPTR)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_NO_CREATE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਨਿੱਜੀ)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_PRESENT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_REDUCTION)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_compute (location_t loc, c_parser *parser,
		       ਗਿਣਤੀ pragma_ਕਿਸਮ p_ਕਿਸਮ, ਅੱਖਰ *p_name, ਤਾਰਕਿਕ *if_p)
{
  omp_clause_ਨਕਾਬ ਨਕਾਬ;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ;
  ਚੋਣ (p_ਕਿਸਮ)
    {
    ਹਾਲਤ PRAGMA_OACC_KERNELS:
      strcat (p_name, " kernels");
      ਨਕਾਬ = OACC_KERNELS_CLAUSE_ਨਕਾਬ;
      ਕੋਡ = OACC_KERNELS;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_PARALLEL:
      strcat (p_name, " parallel");
      ਨਕਾਬ = OACC_PARALLEL_CLAUSE_ਨਕਾਬ;
      ਕੋਡ = OACC_PARALLEL;
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_SERIAL:
      strcat (p_name, " serial");
      ਨਕਾਬ = OACC_SERIAL_CLAUSE_ਨਕਾਬ;
      ਕੋਡ = OACC_SERIAL;
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "loop") == 0)
	{
	  c_parser_consume_token (parser);
	  ਰੁੱਖ ਖੰਡ = c_begin_omp_parallel ();
	  ਰੁੱਖ clauses;
	  c_parser_oacc_loop (loc, parser, p_name, ਨਕਾਬ, &clauses, if_p);
	  ਵਾਪਸ c_ਅੰਤ_omp_construct (loc, ਕੋਡ, ਖੰਡ, clauses);
	}
    }

  ਰੁੱਖ clauses = c_parser_oacc_all_clauses (parser, ਨਕਾਬ, p_name,
					    /*finish_p=*/ਸੱਚ,
					    /*target=*/ਸੱਚ);

  ਰੁੱਖ ਖੰਡ = c_begin_omp_parallel ();
  ਜੋੜੋ_stmt (c_parser_omp_structured_ਖੰਡ (parser, if_p));

  ਵਾਪਸ c_ਅੰਤ_omp_construct (loc, ਕੋਡ, ਖੰਡ, clauses);
}

/* OpenACC 2.0:
   # pragma acc routine oacc-routine-clause[optseq] new-line
     function-definition

   # pragma acc routine ( name ) oacc-routine-clause[optseq] new-line
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_ROUTINE_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_GANG)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਕਾਮਾ)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ਸਦਿਸ਼)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_SEQ)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_NOHOST) )

/* Parse an OpenACC routine directive.  For named directives, we apply
   immediately to the named function.  For unnamed ones we then parse
   a declaration or definition, which must be for a function.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_oacc_routine (c_parser *parser, ਗਿਣਤੀ pragma_context context)
{
  gcc_checking_assert (context == pragma_external);

  oacc_routine_ਅੰਕੜੇ ਅੰਕੜੇ;
  ਅੰਕੜੇ.error_ਵੇਖਿਆ = ਝੂਠ;
  ਅੰਕੜੇ.fndecl_ਵੇਖਿਆ = ਝੂਠ;
  ਅੰਕੜੇ.loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  /* Look for optional '( name )'.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser); /* '(' */

      ਰੁੱਖ decl = NULL_ਰੁੱਖ;
      c_token *name_token = c_parser_peek_token (parser);
      location_t name_loc = name_token->location;
      ਜੇ (name_token->type == CPP_NAME
	  && (name_token->id_ਕਿਸਮ == C_ID_ID
	      || name_token->id_ਕਿਸਮ == C_ID_TYPENAME))
	{
	  decl = lookup_name (name_token->ਮੁੱਲ);
	  ਜੇ (!decl)
	    error_at (name_loc,
		      "%qE has not been declared", name_token->ਮੁੱਲ);
	  c_parser_consume_token (parser);
	}
      ਨਹੀਂਤਾਂ
	c_parser_error (parser, "expected function name");

      ਜੇ (!decl
	  || !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	{
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਵਾਪਸ;
	}

      ਅੰਕੜੇ.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_ਨਕਾਬ,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      ਅੰਕੜੇ.clauses = nreverse (ਅੰਕੜੇ.clauses);

      ਜੇ (ਰੁੱਖ_ਕੋਡ (decl) != FUNCTION_DECL)
	{
	  error_at (name_loc, "%qD does not refer to a function", decl);
	  ਵਾਪਸ;
	}

      c_ਅੰਤ_oacc_routine (&ਅੰਕੜੇ, decl, ਝੂਠ);
    }
  ਨਹੀਂਤਾਂ /* No optional '( name )'.  */
    {
      ਅੰਕੜੇ.clauses
	= c_parser_oacc_all_clauses (parser, OACC_ROUTINE_CLAUSE_ਨਕਾਬ,
				     "#pragma acc routine");
      /* The clauses are in reverse order; fix that to make later diagnostic
	 emission easier.  */
      ਅੰਕੜੇ.clauses = nreverse (ਅੰਕੜੇ.clauses);

      /* Emit a helpful diagnostic if there's another pragma following this
	 one.  Also don't allow a static assertion declaration, as in the
	 following we'll just parse a *single* "declaration or function
	 definition", and the static assertion counts an one.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA)
	  || c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_STATIC_ASSERT))
	{
	  error_at (ਅੰਕੜੇ.loc,
		    "%<#pragma acc routine%> not immediately followed by"
		    " function declaration or definition");
	  /* ..., and then just keep going.  */
	  ਵਾਪਸ;
	}

      /* We only have to consider the pragma_external case here.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ਪੂਰਨ ext = disable_extension_diagnostics ();
	  ਕਰੋ
	    c_parser_consume_token (parser);
	  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਝੂਠ, ਸੱਚ,
					 ਝੂਠ, ਨਿਰਾ, ਨਿਰਾ, ਝੂਠ, ਨਿਰਾ, &ਅੰਕੜੇ);
	  restore_extension_diagnostics (ext);
	}
      ਨਹੀਂਤਾਂ
	c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਝੂਠ, ਸੱਚ,
				       ਝੂਠ, ਨਿਰਾ, ਨਿਰਾ, ਝੂਠ, ਨਿਰਾ, &ਅੰਕੜੇ);
    }
}

/* Finalize an OpenACC routine pragma, applying it to FNDECL.
   IS_DEFN is true if we're applying it to the definition.  */

ਸਥਿਰ ਖਾਲੀ
c_ਅੰਤ_oacc_routine (ਬਣਤਰ oacc_routine_ਅੰਕੜੇ *ਅੰਕੜੇ, ਰੁੱਖ fndecl,
		       ਤਾਰਕਿਕ is_defn)
{
  /* Keep going if we're in error reporting mode.  */
  ਜੇ (ਅੰਕੜੇ->error_ਵੇਖਿਆ
      || fndecl == error_mark_ਗੰਢ)
    ਵਾਪਸ;

  ਜੇ (ਅੰਕੜੇ->fndecl_ਵੇਖਿਆ)
    {
      error_at (ਅੰਕੜੇ->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" a single function declaration or definition");
      ਅੰਕੜੇ->error_ਵੇਖਿਆ = ਸੱਚ;
      ਵਾਪਸ;
    }
  ਜੇ (fndecl == NULL_ਰੁੱਖ || ਰੁੱਖ_ਕੋਡ (fndecl) != FUNCTION_DECL)
    {
      error_at (ਅੰਕੜੇ->loc,
		"%<#pragma acc routine%> not immediately followed by"
		" function declaration or definition");
      ਅੰਕੜੇ->error_ਵੇਖਿਆ = ਸੱਚ;
      ਵਾਪਸ;
    }

  ਪੂਰਨ compatible
    = oacc_verify_routine_clauses (fndecl, &ਅੰਕੜੇ->clauses, ਅੰਕੜੇ->loc,
				   "#pragma acc routine");
  ਜੇ (compatible < 0)
    {
      ਅੰਕੜੇ->error_ਵੇਖਿਆ = ਸੱਚ;
      ਵਾਪਸ;
    }
  ਜੇ (compatible > 0)
    {
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (ਰੁੱਖ_ਵਰਤਿਆ (fndecl) || (!is_defn && DECL_SAVED_ਰੁੱਖ (fndecl)))
	{
	  error_at (ਅੰਕੜੇ->loc,
		    ਰੁੱਖ_ਵਰਤਿਆ (fndecl)
		    ? G_("%<#pragma acc routine%> must be applied before use")
		    : G_("%<#pragma acc routine%> must be applied before"
			 " definition"));
	  ਅੰਕੜੇ->error_ਵੇਖਿਆ = ਸੱਚ;
	  ਵਾਪਸ;
	}

      /* Set the routine's level of parallelism.  */
      ਰੁੱਖ dims = oacc_build_routine_dims (ਅੰਕੜੇ->clauses);
      oacc_replace_fn_attrib (fndecl, dims);

      /* Add an "omp declare target" attribute.  */
      DECL_ਗੁਣ (fndecl)
	= ਰੁੱਖ_cons (get_identifier ("omp declare target"),
		     ਅੰਕੜੇ->clauses, DECL_ਗੁਣ (fndecl));
    }

  /* Remember that we've used this "#pragma acc routine".  */
  ਅੰਕੜੇ->fndecl_ਵੇਖਿਆ = ਸੱਚ;
}

/* OpenACC 2.0:
   # pragma acc update oacc-update-clause[optseq] new-line
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_UPDATE_CLAUSE_ਨਕਾਬ						\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_DEVICE)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_HOST)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF)			\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF_PRESENT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_SELF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_WAIT) )

ਸਥਿਰ ਖਾਲੀ
c_parser_oacc_update (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  ਰੁੱਖ clauses = c_parser_oacc_all_clauses (parser, OACC_UPDATE_CLAUSE_ਨਕਾਬ,
					    "#pragma acc update");
  ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_MAP) == NULL_ਰੁੱਖ)
    {
      error_at (loc,
		"%<#pragma acc update%> must contain at least one "
		"%<device%> or %<host%> or %<self%> clause");
      ਵਾਪਸ;
    }

  ਜੇ (parser->error)
    ਵਾਪਸ;

  ਰੁੱਖ stmt = make_ਗੰਢ (OACC_UPDATE);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OACC_UPDATE_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);
}

/* OpenACC 2.0:
   # pragma acc wait [(intseq)] oacc-wait-clause[optseq] new-line

   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OACC_WAIT_CLAUSE_ਨਕਾਬ						\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_ASYNC)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OACC_CLAUSE_IF) )

ਸਥਿਰ ਰੁੱਖ
c_parser_oacc_wait (location_t loc, c_parser *parser, ਅੱਖਰ *p_name)
{
  ਰੁੱਖ clauses, list = NULL_ਰੁੱਖ, stmt = NULL_ਰੁੱਖ;

  ਜੇ (c_parser_peek_token (parser)->type == CPP_OPEN_PAREN)
    list = c_parser_oacc_wait_list (parser, loc, list);

  strcpy (p_name, " wait");
  clauses = c_parser_oacc_all_clauses (parser, OACC_WAIT_CLAUSE_ਨਕਾਬ, p_name);
  stmt = c_ਅੰਤ_oacc_wait (loc, list, clauses);
  ਜੋੜੋ_stmt (stmt);

  ਵਾਪਸ stmt;
}

ਬਣਤਰ c_omp_loc_ਰੁੱਖ
{
  location_t loc;
  ਰੁੱਖ var;
};

/* Check whether the expression used in the allocator clause is declared or
   modified between the variable declaration and its allocate directive.  */
ਸਥਿਰ ਰੁੱਖ
c_check_omp_allocate_allocator_r (ਰੁੱਖ *tp, ਪੂਰਨ *, ਖਾਲੀ *ਅੰਕੜੇ)
{
  ਰੁੱਖ var = ((ਬਣਤਰ c_omp_loc_ਰੁੱਖ *) ਅੰਕੜੇ)->var;
  location_t loc = ((ਬਣਤਰ c_omp_loc_ਰੁੱਖ *) ਅੰਕੜੇ)->loc;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (*tp) == VAR_DECL && c_check_ਵਿੱਚ_current_scope (*tp))
    {
      ਜੇ (linemap_location_before_p (ਸਤਰ_ਸਾਰਣੀ, DECL_ਸਰੋਤ_LOCATION (var),
				     DECL_ਸਰੋਤ_LOCATION (*tp)))
	{
	  error_at (loc, "variable %qD used in the %<allocator%> clause must "
			 "be declared before %qD", *tp, var);
	  inform (DECL_ਸਰੋਤ_LOCATION (*tp), "declared here");
	  inform (DECL_ਸਰੋਤ_LOCATION (var),
		  "to be allocated variable declared here");
	  ਵਾਪਸ *tp;
	}
      ਨਹੀਂਤਾਂ
	{
	  gcc_assert (cur_stmt_list
		      && ਰੁੱਖ_ਕੋਡ (cur_stmt_list) == STATEMENT_LIST);

	  ਰੁੱਖ_stmt_iterator l = tsi_ਆਖਰੀ (cur_stmt_list);
	  ਜਦੋਂ (!tsi_ਸਿਰਾ_p (l))
	    {
	      ਜੇ (linemap_location_before_p (ਸਤਰ_ਸਾਰਣੀ, ਵਿਅੰਜਕ_LOCATION (*l),
					     DECL_ਸਰੋਤ_LOCATION (var)))
		  ਰੋਕੋ;
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (*l) == MODIFY_ਵਿਅੰਜਕ
		  && ਰੁੱਖ_ਸੰਕਾਰਜ (*l, 0) == *tp)
		{
		  error_at (loc,
			    "variable %qD used in the %<allocator%> clause "
			    "must not be modified between declaration of %qD "
			    "and its %<allocate%> directive", *tp, var);
		  inform (ਵਿਅੰਜਕ_LOCATION (*l), "modified here");
		  inform (DECL_ਸਰੋਤ_LOCATION (var),
			  "to be allocated variable declared here");
		  ਵਾਪਸ *tp;
		}
	      --l;
	    }
	}
    }
  ਵਾਪਸ NULL_ਰੁੱਖ;
}

/* OpenMP 5.x:
   # pragma omp allocate (list)  clauses

   OpenMP 5.0 clause:
   allocator (omp_allocator_handle_t expression)

   OpenMP 5.1 additional clause:
   align (constant-expression)]  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_allocate (c_parser *parser)
{
  ਰੁੱਖ alignment = NULL_ਰੁੱਖ;
  ਰੁੱਖ allocator = NULL_ਰੁੱਖ;
  c_parser_consume_pragma (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  location_t allocator_loc = UNKNOWN_LOCATION;
  ਰੁੱਖ nl = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ALLOCATE, NULL_ਰੁੱਖ);
  ਕਰੋ
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	ਰੋਕੋ;
      matching_parens parens;
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      c_parser_consume_token (parser);
      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      ਜੇ (strcmp ("align", p) != 0 && strcmp ("allocator", p) != 0)
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "expected %<allocator%> or %<align%>");
	  ਰੋਕੋ;
	}
      ਜੇ (!parens.require_open (parser))
	ਰੋਕੋ;

      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਝੂਠ, ਸੱਚ);
      ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
      ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
	;
      ਨਹੀਂਤਾਂ ਜੇ (p[2] == 'i' && alignment)
	{
	  error_at (ਵਿਅੰਜਕ_loc, "too many %qs clauses", "align");
	  ਰੋਕੋ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (p[2] == 'i')
	{
	  alignment = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (alignment) != INTEGER_CST
	      || !INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (alignment))
	      || ਰੁੱਖ_int_cst_sgn (alignment) != 1
	      || !integer_pow2p (alignment))
	    {
	      error_at (ਵਿਅੰਜਕ_loc, "%<align%> clause argument needs to be "
				  "positive constant power of two integer "
				  "expression");
	      alignment = NULL_ਰੁੱਖ;
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (allocator)
	{
	  error_at (ਵਿਅੰਜਕ_loc, "too many %qs clauses", "allocator");
	  ਰੋਕੋ;
	}
      ਨਹੀਂਤਾਂ
	{
	  allocator = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	  allocator_loc = ਵਿਅੰਜਕ_loc;
	  ਰੁੱਖ orig_type
	    = ਵਿਅੰਜਕ.original_type ? ਵਿਅੰਜਕ.original_type : ਰੁੱਖ_TYPE (allocator);
	  orig_type = TYPE_MAIN_VARIANT (orig_type);
	  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (allocator))
	      || ਰੁੱਖ_ਕੋਡ (orig_type) != ENUMERAL_TYPE
	      || TYPE_NAME (orig_type)
		 != get_identifier ("omp_allocator_handle_t"))
	    {
	      error_at (ਵਿਅੰਜਕ_loc,
			"%<allocator%> clause allocator expression has type "
			"%qT rather than %<omp_allocator_handle_t%>",
			ਰੁੱਖ_TYPE (allocator));
	      allocator = NULL_ਰੁੱਖ;
	    }
	}
      parens.skip_until_ਮਿਲਿਆ_close (parser);
    } ਜਦੋਂ (ਸੱਚ);
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  c_mark_decl_jump_unsafe_ਵਿੱਚ_current_scope ();
  ਲਈ (ਰੁੱਖ c = nl; c != NULL_ਰੁੱਖ; c = OMP_CLAUSE_CHAIN (c))
    {
      ਰੁੱਖ var = OMP_CLAUSE_DECL (c);
      ਜੇ (ਰੁੱਖ_ਕੋਡ (var) == PARM_DECL)
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "function parameter %qD may not appear as list item in an "
		    "%<allocate%> directive", var);
	  ਜਾਰੀ;
	}
      ਜੇ (!parser->ਵਿੱਚ_omp_decl_attribute && !c_check_ਵਿੱਚ_current_scope (var))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%<allocate%> directive must be in the same scope as %qD",
		    var);
	  inform (DECL_ਸਰੋਤ_LOCATION (var), "declared here");
	  ਜਾਰੀ;
	}
      ਜੇ (lookup_attribute ("omp allocate", DECL_ਗੁਣ (var)))
	{
	  error_at (OMP_CLAUSE_LOCATION (nl),
		    "%qD already appeared as list item in an "
		    "%<allocate%> directive", var);
	  ਜਾਰੀ;
	}
      ਜੇ (ਰੁੱਖ_STATIC (var))
	{
	  ਜੇ (allocator == NULL_ਰੁੱਖ && allocator_loc == UNKNOWN_LOCATION)
	    {
	      error_at (loc,
			"%<allocator%> clause required for "
			"static variable %qD", var);
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (allocator
		   && (wi::ਮੰਜ਼ਿਲ_widest (allocator) < 1
		       || wi::ਮੰਜ਼ਿਲ_widest (allocator) > GOMP_OMP_PREDEF_ALLOC_MAX)
		   && (wi::ਮੰਜ਼ਿਲ_widest (allocator) < GOMP_OMPX_PREDEF_ALLOC_MIN
		       || wi::ਮੰਜ਼ਿਲ_widest (allocator) > GOMP_OMPX_PREDEF_ALLOC_MAX))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause requires a predefined allocator as "
			"%qD is static", var);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (allocator
		   && (wi::eq_p (wi::ਮੰਜ਼ਿਲ_widest (allocator),
				 GOMP_OMP_PREDEF_ALLOC_CGROUP)
		       || wi::eq_p (wi::ਮੰਜ਼ਿਲ_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_PTEAM)
		       || wi::eq_p (wi::ਮੰਜ਼ਿਲ_widest (allocator),
				    GOMP_OMP_PREDEF_ALLOC_THREAD)))
	    {
	      error_at (allocator_loc,
			"%<allocator%> clause for static variable %qD must not "
			"be %<omp_cgroup_mem_alloc%>, %<omp_pteam_mem_alloc%>, "
			"or %<omp_thread_mem_alloc%>", var);
	    }
	}
      ਜੇ (allocator)
	{
	  ਬਣਤਰ c_omp_loc_ਰੁੱਖ ਅੰਕੜੇ
	    = {ਵਿਅੰਜਕ_LOC_OR_LOC (allocator, OMP_CLAUSE_LOCATION (nl)), var};
	  walk_ਰੁੱਖ (&allocator, c_check_omp_allocate_allocator_r, &ਅੰਕੜੇ, ਨਿਰਾ);
	}
      DECL_ਗੁਣ (var) = ਰੁੱਖ_cons (get_identifier ("omp allocate"),
					 build_ਰੁੱਖ_list (allocator, alignment),
					 DECL_ਗੁਣ (var));
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

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_atomic (location_t loc, c_parser *parser, ਤਾਰਕਿਕ openacc)
{
  ਰੁੱਖ lhs = NULL_ਰੁੱਖ, rhs = NULL_ਰੁੱਖ, v = NULL_ਰੁੱਖ, r = NULL_ਰੁੱਖ;
  ਰੁੱਖ lhs1 = NULL_ਰੁੱਖ, rhs1 = NULL_ਰੁੱਖ;
  ਰੁੱਖ stmt, orig_lhs, unfolded_lhs = NULL_ਰੁੱਖ, unfolded_lhs1 = NULL_ਰੁੱਖ;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ERROR_MARK, opcode = NOP_ਵਿਅੰਜਕ;
  ਗਿਣਤੀ omp_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED;
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  location_t eloc;
  ਤਾਰਕਿਕ structured_ਖੰਡ = ਝੂਠ;
  ਤਾਰਕਿਕ swapped = ਝੂਠ;
  ਤਾਰਕਿਕ non_lvalue_p;
  ਰੁੱਖ clauses = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ capture = ਝੂਠ;
  ਤਾਰਕਿਕ compare = ਝੂਠ;
  ਤਾਰਕਿਕ weak = ਝੂਠ;
  ਗਿਣਤੀ omp_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ fail = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED;
  ਤਾਰਕਿਕ no_semicolon = ਝੂਠ;
  ਤਾਰਕਿਕ extra_scope = ਝੂਠ;

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  ਅਚਲ ਅੱਖਰ *p
	    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 new_ਕੋਡ = ERROR_MARK;
	  ਗਿਣਤੀ omp_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ new_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ
	    = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED;
	  ਤਾਰਕਿਕ new_capture = ਝੂਠ;
	  ਤਾਰਕਿਕ new_compare = ਝੂਠ;
	  ਤਾਰਕਿਕ new_weak = ਝੂਠ;
	  ਗਿਣਤੀ omp_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ new_fail = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED;

	  ਜੇ (!strcmp (p, "read"))
	    new_ਕੋਡ = OMP_ATOMIC_READ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "write"))
	    new_ਕੋਡ = NOP_ਵਿਅੰਜਕ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "update"))
	    new_ਕੋਡ = OMP_ATOMIC;
	  ਨਹੀਂਤਾਂ ਜੇ (openacc && !strcmp (p, "capture"))
	    new_ਕੋਡ = OMP_ATOMIC_CAPTURE_NEW;
	  ਨਹੀਂਤਾਂ ਜੇ (openacc)
	    {
	      p = ਨਿਰਾ;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "or %<capture%> clause");
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "capture"))
	    new_capture = ਸੱਚ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "compare"))
	    new_compare = ਸੱਚ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "weak"))
	    new_weak = ਸੱਚ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "fail"))
	    {
	      matching_parens parens;

	      c_parser_consume_token (parser);
	      ਜੇ (!parens.require_open (parser))
		ਜਾਰੀ;

	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		{
		  ਅਚਲ ਅੱਖਰ *q
		    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

		  ਜੇ (!strcmp (q, "seq_cst"))
		    new_fail = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST;
		  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (q, "acquire"))
		    new_fail = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQUIRE;
		  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (q, "relaxed"))
		    new_fail = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELAXED;
		}

	      ਜੇ (new_fail != OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED)
		{
		  c_parser_consume_token (parser);
		  ਜੇ (fail != OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED)
		    error_at (cloc, "too many %qs clauses", "fail");
		  ਨਹੀਂਤਾਂ
		    fail = new_fail;
		}
	      ਨਹੀਂਤਾਂ
		c_parser_error (parser, "expected %<seq_cst%>, %<acquire%> "
					"or %<relaxed%>");
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "seq_cst"))
	    new_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "acq_rel"))
	    new_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQ_REL;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "release"))
	    new_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELEASE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "acquire"))
	    new_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQUIRE;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "relaxed"))
	    new_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELAXED;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "hint"))
	    {
	      c_parser_consume_token (parser);
	      clauses = c_parser_omp_clause_hint (parser, clauses);
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      p = ਨਿਰਾ;
	      error_at (cloc, "expected %<read%>, %<write%>, %<update%>, "
			      "%<capture%>, %<compare%>, %<weak%>, %<fail%>, "
			      "%<seq_cst%>, %<acq_rel%>, %<release%>, "
			      "%<relaxed%> or %<hint%> clause");
	    }
	  ਜੇ (p)
	    {
	      ਜੇ (new_ਕੋਡ != ERROR_MARK)
		{
		  /* OpenACC permits 'update capture'.  */
		  ਜੇ (openacc
		      && ਕੋਡ == OMP_ATOMIC
		      && new_ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW)
		    ਕੋਡ = new_ਕੋਡ;
		  ਨਹੀਂਤਾਂ ਜੇ (ਕੋਡ != ERROR_MARK)
		    error_at (cloc, "too many atomic clauses");
		  ਨਹੀਂਤਾਂ
		    ਕੋਡ = new_ਕੋਡ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (new_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ != OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED)
		{
		  ਜੇ (ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ != OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED)
		    error_at (cloc, "too many memory order clauses");
		  ਨਹੀਂਤਾਂ
		    ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = new_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (new_capture)
		{
		  ਜੇ (capture)
		    error_at (cloc, "too many %qs clauses", "capture");
		  ਨਹੀਂਤਾਂ
		    capture = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (new_compare)
		{
		  ਜੇ (compare)
		    error_at (cloc, "too many %qs clauses", "compare");
		  ਨਹੀਂਤਾਂ
		    compare = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (new_weak)
		{
		  ਜੇ (weak)
		    error_at (cloc, "too many %qs clauses", "weak");
		  ਨਹੀਂਤਾਂ
		    weak = ਸੱਚ;
		}
	      c_parser_consume_token (parser);
	      ਜਾਰੀ;
	    }
	}
      ਰੋਕੋ;
    }
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  ਜੇ (ਕੋਡ == ERROR_MARK)
    ਕੋਡ = OMP_ATOMIC;
  ਜੇ (capture)
    {
      ਜੇ (ਕੋਡ != OMP_ATOMIC)
	error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		       "clauses", "capture");
      ਨਹੀਂਤਾਂ
	ਕੋਡ = OMP_ATOMIC_CAPTURE_NEW;
    }
  ਜੇ (compare && ਕੋਡ != OMP_ATOMIC && ਕੋਡ != OMP_ATOMIC_CAPTURE_NEW)
    {
      error_at (loc, "%qs clause is incompatible with %<read%> or %<write%> "
		      "clauses", "compare");
      compare = ਝੂਠ;
    }
  ਜੇ (fail != OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "fail", "compare");
      fail = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED;
    }
  ਜੇ (weak && !compare)
    {
      error_at (loc, "%qs clause requires %qs clause", "weak", "compare");
      weak = ਝੂਠ;
    }
  ਜੇ (openacc)
    ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELAXED;
  ਨਹੀਂਤਾਂ ਜੇ (ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ == OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED)
    {
      omp_requires_ਨਕਾਬ
	= (ਗਿਣਤੀ omp_requires) (omp_requires_ਨਕਾਬ
			       | OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ਕ੍ਰਮ_ਵਰਤਿਆ);
      ਚੋਣ ((ਗਿਣਤੀ omp_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ)
	      (omp_requires_ਨਕਾਬ & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ਕ੍ਰਮ))
	{
	ਹਾਲਤ OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED:
	ਹਾਲਤ OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELAXED:
	  ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELAXED;
	  ਰੋਕੋ;
	ਹਾਲਤ OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST:
	  ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST;
	  ਰੋਕੋ;
	ਹਾਲਤ OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQUIRE:
	  ਜੇ (ਕੋਡ == NOP_ਵਿਅੰਜਕ)  /* atomic write */
	    {
	      error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			     "%<acquire%> clause implicitly provided by a "
			     "%<requires%> directive");
	      ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST;
	    }
	  ਨਹੀਂਤਾਂ
	    ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQUIRE;
	  ਰੋਕੋ;
	ਹਾਲਤ OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELEASE:
	  ਜੇ (ਕੋਡ == OMP_ATOMIC_READ)
	    {
	      error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			     "%<release%> clause implicitly provided by a "
			     "%<requires%> directive");
	      ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST;
	    }
	  ਨਹੀਂਤਾਂ
	    ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELEASE;
	  ਰੋਕੋ;
	ਹਾਲਤ OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQ_REL:
	  ਚੋਣ (ਕੋਡ)
	    {
	    ਹਾਲਤ OMP_ATOMIC_READ:
	      ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQUIRE;
	      ਰੋਕੋ;
	    ਹਾਲਤ NOP_ਵਿਅੰਜਕ: /* atomic write */
	      ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELEASE;
	      ਰੋਕੋ;
	    ਮੂਲ:
	      ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQ_REL;
	      ਰੋਕੋ;
	    }
	  ਰੋਕੋ;
	ਮੂਲ:
	  gcc_unreachable ();
	}
    }
  ਨਹੀਂਤਾਂ
    ਚੋਣ (ਕੋਡ)
      {
      ਹਾਲਤ OMP_ATOMIC_READ:
	ਜੇ (ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ == OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELEASE)
	  {
	    error_at (loc, "%<#pragma omp atomic read%> incompatible with "
			   "%<release%> clause");
	    ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ == OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQ_REL)
	  ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQUIRE;
	ਰੋਕੋ;
      ਹਾਲਤ NOP_ਵਿਅੰਜਕ: /* atomic write */
	ਜੇ (ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ == OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQUIRE)
	  {
	    error_at (loc, "%<#pragma omp atomic write%> incompatible with "
			   "%<acquire%> clause");
	    ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST;
	  }
	ਨਹੀਂਤਾਂ ਜੇ (ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ == OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQ_REL)
	  ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ = OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELEASE;
	ਰੋਕੋ;
      ਮੂਲ:
	ਰੋਕੋ;
      }
  ਜੇ (fail != OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_UNSPECIFIED)
    ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ
      = (ਗਿਣਤੀ omp_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ) (ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ
				 | (fail << OMP_FAIL_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ਖਿਸਕਾਓ));

  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ OMP_ATOMIC_READ:
    ਹਾਲਤ NOP_ਵਿਅੰਜਕ: /* atomic write */
      v = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ).ਮੁੱਲ;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
      ਜੇ (v == error_mark_ਗੰਢ)
	ਜਾਓ saw_error;
      ਜੇ (non_lvalue_p)
	v = non_lvalue (v);
      loc = c_parser_peek_token (parser)->location;
      ਜੇ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ਜਾਓ saw_error;
      ਜੇ (ਕੋਡ == NOP_ਵਿਅੰਜਕ)
	{
	  eloc = c_parser_peek_token (parser)->location;
	  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
	  ਵਿਅੰਜਕ = default_function_array_read_conversion (eloc, ਵਿਅੰਜਕ);
	  /* atomic write is represented by OMP_ATOMIC with NOP_EXPR
	     opcode.  */
	  ਕੋਡ = OMP_ATOMIC;
	  lhs = v;
	  v = NULL_ਰੁੱਖ;
	  rhs = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ);
	  ਜੇ (rhs == error_mark_ਗੰਢ)
	    ਜਾਓ saw_error;
	}
      ਨਹੀਂਤਾਂ
	{
	  lhs = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ).ਮੁੱਲ;
	  non_lvalue_p = !lvalue_p (lhs);
	  lhs = c_fully_fold (lhs, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	  ਜੇ (lhs == error_mark_ਗੰਢ)
	    ਜਾਓ saw_error;
	  ਜੇ (non_lvalue_p)
	    lhs = non_lvalue (lhs);
	}
      ਜਾਓ ਪੂਰਾ;
    ਹਾਲਤ OMP_ATOMIC_CAPTURE_NEW:
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
	{
	  c_parser_consume_token (parser);
	  structured_ਖੰਡ = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (compare
	       && c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_IF))
	ਰੋਕੋ;
      ਨਹੀਂਤਾਂ
	{
	  v = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ).ਮੁੱਲ;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	  ਜੇ (v == error_mark_ਗੰਢ)
	    ਜਾਓ saw_error;
	  ਜੇ (non_lvalue_p)
	    v = non_lvalue (v);
	  ਜੇ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    ਜਾਓ saw_error;
	  ਜੇ (compare && c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_IF))
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "expected expression");
	      ਜਾਓ saw_error;
	    }
	}
      ਰੋਕੋ;
    ਮੂਲ:
      ਰੋਕੋ;
    }

  /* For structured_block case we don't know yet whether
     old or new x should be captured.  */
restart:
  ਜੇ (compare && c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_IF))
    {
      c_parser_consume_token (parser);

      matching_parens parens;
      ਜੇ (!parens.require_open (parser))
	ਜਾਓ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ cmp_ਵਿਅੰਜਕ;
      ਜੇ (r)
	{
	  cmp_ਵਿਅੰਜਕ = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
	  cmp_ਵਿਅੰਜਕ = default_function_array_conversion (eloc, cmp_ਵਿਅੰਜਕ);
	}
      ਨਹੀਂਤਾਂ
	cmp_ਵਿਅੰਜਕ = c_parser_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (parser, ਨਿਰਾ, void_list_ਗੰਢ);
      parens.skip_until_ਮਿਲਿਆ_close (parser);
      ਜੇ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
	ਜਾਓ saw_error;
      ਜੇ (r)
	{
	  ਜੇ (!c_ਰੁੱਖ_equal (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, unfolded_lhs))
	    ਜਾਓ bad_if;
	  cmp_ਵਿਅੰਜਕ.ਮੁੱਲ = rhs1;
	  rhs1 = NULL_ਰੁੱਖ;
	  gcc_assert (ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) == EQ_ਵਿਅੰਜਕ);
	}
      ਜੇ (ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) == EQ_ਵਿਅੰਜਕ)
	;
      ਨਹੀਂਤਾਂ ਜੇ (!structured_ਖੰਡ && ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW)
	{
	  error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, eloc),
		    "expected %<==%> comparison in %<if%> condition");
	  ਜਾਓ saw_error;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) != GT_ਵਿਅੰਜਕ
	       && ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) != LT_ਵਿਅੰਜਕ)
	{
	  error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, eloc),
		    "expected %<==%>, %<<%> or %<>%> comparison in %<if%> "
		    "condition");
	  ਜਾਓ saw_error;
	}
      ਜੇ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	ਜਾਓ saw_error;

      extra_scope = ਸੱਚ;
      eloc = c_parser_peek_token (parser)->location;
      ਵਿਅੰਜਕ = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      lhs = ਵਿਅੰਜਕ.ਮੁੱਲ;
      ਵਿਅੰਜਕ = default_function_array_conversion (eloc, ਵਿਅੰਜਕ);
      unfolded_lhs = ਵਿਅੰਜਕ.ਮੁੱਲ;
      lhs = c_fully_fold (lhs, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
      orig_lhs = lhs;
      ਜੇ (lhs == error_mark_ਗੰਢ)
	ਜਾਓ saw_error;
      ਜੇ (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  ਜਾਓ saw_error;
	}
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      rhs1 = ਵਿਅੰਜਕ.ਮੁੱਲ;

      ਜੇ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ਜਾਓ saw_error;

      ਜੇ (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	ਜਾਓ saw_error;

      extra_scope = ਝੂਠ;
      no_semicolon = ਸੱਚ;

      ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, 0), unfolded_lhs))
	{
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) == EQ_ਵਿਅੰਜਕ)
	    {
	      opcode = COND_ਵਿਅੰਜਕ;
	      rhs = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, 1),
				  ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	      rhs1 = c_fully_fold (rhs1, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, 1), rhs1))
	    {
	      opcode = (ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) == GT_ਵਿਅੰਜਕ
			? MIN_ਵਿਅੰਜਕ : MAX_ਵਿਅੰਜਕ);
	      rhs = c_fully_fold (rhs1, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	      rhs1 = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, 0),
				   ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	    }
	  ਨਹੀਂਤਾਂ
	    ਜਾਓ bad_if;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) == EQ_ਵਿਅੰਜਕ)
	ਜਾਓ bad_if;
      ਨਹੀਂਤਾਂ ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, 1), unfolded_lhs)
	       && c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, 0), rhs1))
	{
	  opcode = (ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) == GT_ਵਿਅੰਜਕ
		    ? MAX_ਵਿਅੰਜਕ : MIN_ਵਿਅੰਜਕ);
	  rhs = c_fully_fold (rhs1, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	  rhs1 = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ, 1),
			       ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	}
      ਨਹੀਂਤਾਂ
	{
	bad_if:
	  c_parser_error (parser,
			  "invalid form of %<#pragma omp atomic compare%>");
	  ਜਾਓ saw_error;
	}

      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ELSE))
	{
	  ਜੇ (ਕੋਡ != OMP_ATOMIC_CAPTURE_NEW
	      || (structured_ਖੰਡ && r == NULL_ਰੁੱਖ)
	      || ਰੁੱਖ_ਕੋਡ (cmp_ਵਿਅੰਜਕ.ਮੁੱਲ) != EQ_ਵਿਅੰਜਕ)
	    {
	      eloc = c_parser_peek_token (parser)->location;
	      error_at (eloc, "unexpected %<else%>");
	      ਜਾਓ saw_error;
	    }

	  c_parser_consume_token (parser);

	  ਜੇ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	    ਜਾਓ saw_error;

	  extra_scope = ਸੱਚ;
	  v = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ).ਮੁੱਲ;
	  non_lvalue_p = !lvalue_p (v);
	  v = c_fully_fold (v, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
	  ਜੇ (v == error_mark_ਗੰਢ)
	    ਜਾਓ saw_error;
	  ਜੇ (non_lvalue_p)
	    v = non_lvalue (v);
	  ਜੇ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	    ਜਾਓ saw_error;

	  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);

	  ਜੇ (!c_ਰੁੱਖ_equal (ਵਿਅੰਜਕ.ਮੁੱਲ, unfolded_lhs))
	    ਜਾਓ bad_if;

	  ਜੇ (!c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    ਜਾਓ saw_error;

	  ਜੇ (!c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
	    ਜਾਓ saw_error;

	  extra_scope = ਝੂਠ;
	  ਕੋਡ = OMP_ATOMIC_CAPTURE_OLD;
	  ਜੇ (r == NULL_ਰੁੱਖ)
	    /* Signal to c_finish_omp_atomic that in
	       if (x == e) { x = d; } else { v = x; }
	       case the store to v should be conditional.  */
	    r = void_list_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW && !structured_ਖੰਡ)
	{
	  c_parser_require_keyword (parser, RID_ELSE, "expected %<else%>");
	  ਜਾਓ saw_error;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW
	       && r != NULL_ਰੁੱਖ
	       && v == NULL_ਰੁੱਖ)
	ਕੋਡ = OMP_ATOMIC;
      ਜਾਓ stmt_ਪੂਰਾ;
    }
  eloc = c_parser_peek_token (parser)->location;
  ਵਿਅੰਜਕ = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
  lhs = ਵਿਅੰਜਕ.ਮੁੱਲ;
  ਵਿਅੰਜਕ = default_function_array_conversion (eloc, ਵਿਅੰਜਕ);
  unfolded_lhs = ਵਿਅੰਜਕ.ਮੁੱਲ;
  lhs = c_fully_fold (lhs, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
  orig_lhs = lhs;
  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (lhs))
    {
    invalid_compare:
      error_at (eloc, "invalid form of %<pragma omp atomic compare%>");
      /* FALLTHRU */
    ਹਾਲਤ ERROR_MARK:
    saw_error:
      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
      ਜੇ (extra_scope && c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	c_parser_consume_token (parser);
      ਜੇ (structured_ਖੰਡ)
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	    c_parser_consume_token (parser);
	  ਨਹੀਂਤਾਂ ਜੇ (ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW)
	    {
	      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
		c_parser_consume_token (parser);
	    }
	}
      ਵਾਪਸ;

    ਹਾਲਤ POSTINCREMENT_ਵਿਅੰਜਕ:
      ਜੇ (ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW && !structured_ਖੰਡ)
	ਕੋਡ = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    ਹਾਲਤ PREINCREMENT_ਵਿਅੰਜਕ:
      lhs = ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 0);
      unfolded_lhs = NULL_ਰੁੱਖ;
      opcode = PLUS_ਵਿਅੰਜਕ;
      rhs = integer_one_ਗੰਢ;
      ਜੇ (compare)
	ਜਾਓ invalid_compare;
      ਰੋਕੋ;

    ਹਾਲਤ POSTDECREMENT_ਵਿਅੰਜਕ:
      ਜੇ (ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW && !structured_ਖੰਡ)
	ਕੋਡ = OMP_ATOMIC_CAPTURE_OLD;
      /* FALLTHROUGH */
    ਹਾਲਤ PREDECREMENT_ਵਿਅੰਜਕ:
      lhs = ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 0);
      unfolded_lhs = NULL_ਰੁੱਖ;
      opcode = MINUS_ਵਿਅੰਜਕ;
      rhs = integer_one_ਗੰਢ;
      ਜੇ (compare)
	ਜਾਓ invalid_compare;
      ਰੋਕੋ;

    ਹਾਲਤ COMPOUND_ਵਿਅੰਜਕ:
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 0)) == SAVE_ਵਿਅੰਜਕ
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1)) == COMPOUND_ਵਿਅੰਜਕ
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1), 0)) == MODIFY_ਵਿਅੰਜਕ
	  && ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1), 1) == ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 0)
	  && C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ
					      (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1), 0), 0))))
	/* Undo effects of boolean_increment for post {in,de}crement.  */
	lhs = ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1), 0);
      /* FALLTHRU */
    ਹਾਲਤ MODIFY_ਵਿਅੰਜਕ:
      ਜੇ (ਰੁੱਖ_ਕੋਡ (lhs) == MODIFY_ਵਿਅੰਜਕ
	  && C_BOOLEAN_TYPE_P (ਰੁੱਖ_TYPE (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 0))))
	{
	  /* Undo effects of boolean_increment.  */
	  ਜੇ (integer_onep (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1)))
	    {
	      /* This is pre or post increment.  */
	      rhs = ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1);
	      lhs = ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 0);
	      unfolded_lhs = NULL_ਰੁੱਖ;
	      opcode = NOP_ਵਿਅੰਜਕ;
	      ਜੇ (ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_ਖੰਡ
		  && ਰੁੱਖ_ਕੋਡ (orig_lhs) == COMPOUND_ਵਿਅੰਜਕ)
		ਕੋਡ = OMP_ATOMIC_CAPTURE_OLD;
	      ਜੇ (compare)
		ਜਾਓ invalid_compare;
	      ਰੋਕੋ;
	    }
	  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1)) == TRUTH_NOT_ਵਿਅੰਜਕ
	      && ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 0)
		 == ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1), 0))
	    {
	      /* This is pre or post decrement.  */
	      rhs = ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 1);
	      lhs = ਰੁੱਖ_ਸੰਕਾਰਜ (lhs, 0);
	      unfolded_lhs = NULL_ਰੁੱਖ;
	      opcode = NOP_ਵਿਅੰਜਕ;
	      ਜੇ (ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW
		  && !structured_ਖੰਡ
		  && ਰੁੱਖ_ਕੋਡ (orig_lhs) == COMPOUND_ਵਿਅੰਜਕ)
		ਕੋਡ = OMP_ATOMIC_CAPTURE_OLD;
	      ਜੇ (compare)
		ਜਾਓ invalid_compare;
	      ਰੋਕੋ;
	    }
	}
      /* FALLTHRU */
    ਮੂਲ:
      ਜੇ (!lvalue_p (unfolded_lhs))
	lhs = non_lvalue (lhs);
      ਜੇ (compare && !c_parser_ਅਗਲਾ_token_is (parser, CPP_EQ))
	{
	  c_parser_error (parser, "expected %<=%>");
	  ਜਾਓ saw_error;
	}
      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_MULT_EQ:
	  opcode = MULT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_DIV_EQ:
	  opcode = TRUNC_DIV_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_PLUS_EQ:
	  opcode = PLUS_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_MINUS_EQ:
	  opcode = MINUS_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_LSHIFT_EQ:
	  opcode = LSHIFT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_RSHIFT_EQ:
	  opcode = RSHIFT_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_AND_EQ:
	  opcode = ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_OR_EQ:
	  opcode = ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_XOR_EQ:
	  opcode = ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_EQ:
	  c_parser_consume_token (parser);
	  eloc = c_parser_peek_token (parser)->location;
	  ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ, unfolded_lhs);
	  rhs1 = ਵਿਅੰਜਕ.ਮੁੱਲ;
	  ਚੋਣ (ਰੁੱਖ_ਕੋਡ (rhs1))
	    {
	    ਹਾਲਤ MULT_ਵਿਅੰਜਕ:
	    ਹਾਲਤ TRUNC_DIV_ਵਿਅੰਜਕ:
	    ਹਾਲਤ RDIV_ਵਿਅੰਜਕ:
	    ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
	    ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
	    ਹਾਲਤ LSHIFT_ਵਿਅੰਜਕ:
	    ਹਾਲਤ RSHIFT_ਵਿਅੰਜਕ:
	    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ:
	    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ:
	    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ:
	      ਜੇ (compare)
		ਰੋਕੋ;
	      ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0), unfolded_lhs))
		{
		  opcode = ਰੁੱਖ_ਕੋਡ (rhs1);
		  rhs = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1), ਝੂਠ, ਨਿਰਾ,
				      ਸੱਚ);
		  rhs1 = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0), ਝੂਠ, ਨਿਰਾ,
				       ਸੱਚ);
		  ਜਾਓ stmt_ਪੂਰਾ;
		}
	      ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1), unfolded_lhs))
		{
		  opcode = ਰੁੱਖ_ਕੋਡ (rhs1);
		  rhs = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0), ਝੂਠ, ਨਿਰਾ,
				      ਸੱਚ);
		  rhs1 = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1), ਝੂਠ, ਨਿਰਾ,
				       ਸੱਚ);
		  swapped = !commutative_ਰੁੱਖ_ਕੋਡ (opcode);
		  ਜਾਓ stmt_ਪੂਰਾ;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ COND_ਵਿਅੰਜਕ:
	      ਜੇ (!compare)
		ਰੋਕੋ;
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0)) != GT_ਵਿਅੰਜਕ
		  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0)) != LT_ਵਿਅੰਜਕ
		  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0)) != EQ_ਵਿਅੰਜਕ)
		ਰੋਕੋ;
	      ਜੇ (!ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1))
		ਰੋਕੋ;
	      ਜੇ (!c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 2), unfolded_lhs))
		ਰੋਕੋ;
	      ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0), 0),
				unfolded_lhs))
		{
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0)) == EQ_ਵਿਅੰਜਕ)
		    {
		      opcode = COND_ਵਿਅੰਜਕ;
		      rhs = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1,
								      0), 1),
					  ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
		      rhs1 = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1), ਝੂਠ,
					   ਨਿਰਾ, ਸੱਚ);
		      ਜਾਓ stmt_ਪੂਰਾ;
		    }
		  ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0), 1),
				    ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1)))
		    {
		      opcode = (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0)) == GT_ਵਿਅੰਜਕ
				? MIN_ਵਿਅੰਜਕ : MAX_ਵਿਅੰਜਕ);
		      rhs = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1), ਝੂਠ, ਨਿਰਾ,
					  ਸੱਚ);
		      rhs1 = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1,
								       0), 0),
					   ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
		      ਜਾਓ stmt_ਪੂਰਾ;
		    }
		}
	      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0)) == EQ_ਵਿਅੰਜਕ)
		ਰੋਕੋ;
	      ਨਹੀਂਤਾਂ ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0), 1),
				     unfolded_lhs))
		{
		  ਜੇ (c_ਰੁੱਖ_equal (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0), 0),
				    ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1)))
		    {
		      opcode = (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 0)) == GT_ਵਿਅੰਜਕ
				? MAX_ਵਿਅੰਜਕ : MIN_ਵਿਅੰਜਕ);
		      rhs = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1, 1), ਝੂਠ, ਨਿਰਾ,
					  ਸੱਚ);
		      rhs1 = c_fully_fold (ਰੁੱਖ_ਸੰਕਾਰਜ (ਰੁੱਖ_ਸੰਕਾਰਜ (rhs1,
								       0), 1),
					   ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
		      ਜਾਓ stmt_ਪੂਰਾ;
		    }
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ EQ_ਵਿਅੰਜਕ:
	      ਜੇ (!compare
		  || ਕੋਡ != OMP_ATOMIC_CAPTURE_NEW
		  || !structured_ਖੰਡ
		  || v
		  || r)
		ਰੋਕੋ;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)
		  && c_parser_peek_2nd_token (parser)->keyword == RID_IF)
		{
		  r = lhs;
		  lhs = NULL_ਰੁੱਖ;
		  c_parser_consume_token (parser);
		  ਜਾਓ restart;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ ERROR_MARK:
	      ਜਾਓ saw_error;
	    ਮੂਲ:
	      ਰੋਕੋ;
	    }
	  ਜੇ (c_parser_peek_token (parser)->type == CPP_SEMICOLON)
	    {
	      ਜੇ (structured_ਖੰਡ && ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW)
		{
		  ਕੋਡ = OMP_ATOMIC_CAPTURE_OLD;
		  v = lhs;
		  lhs = NULL_ਰੁੱਖ;
		  ਵਿਅੰਜਕ = default_function_array_read_conversion (eloc, ਵਿਅੰਜਕ);
		  unfolded_lhs1 = ਵਿਅੰਜਕ.ਮੁੱਲ;
		  lhs1 = c_fully_fold (unfolded_lhs1, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
		  rhs1 = NULL_ਰੁੱਖ;
		  c_parser_consume_token (parser);
		  ਜਾਓ restart;
		}
	      ਜੇ (structured_ਖੰਡ && !compare)
		{
		  opcode = NOP_ਵਿਅੰਜਕ;
		  ਵਿਅੰਜਕ = default_function_array_read_conversion (eloc, ਵਿਅੰਜਕ);
		  rhs = c_fully_fold (ਵਿਅੰਜਕ.ਮੁੱਲ, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
		  rhs1 = NULL_ਰੁੱਖ;
		  ਜਾਓ stmt_ਪੂਰਾ;
		}
	    }
	  c_parser_error (parser, "invalid form of %<#pragma omp atomic%>");
	  ਜਾਓ saw_error;
	ਮੂਲ:
	  c_parser_error (parser,
			  "invalid operator for %<#pragma omp atomic%>");
	  ਜਾਓ saw_error;
	}

      /* Arrange to pass the location of the assignment operator to
	 c_finish_omp_atomic.  */
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      eloc = c_parser_peek_token (parser)->location;
      ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser);
      ਵਿਅੰਜਕ = default_function_array_read_conversion (eloc, ਵਿਅੰਜਕ);
      rhs = ਵਿਅੰਜਕ.ਮੁੱਲ;
      rhs = c_fully_fold (rhs, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
      ਰੋਕੋ;
    }
stmt_ਪੂਰਾ:
  ਜੇ (structured_ਖੰਡ && ਕੋਡ == OMP_ATOMIC_CAPTURE_NEW && r == NULL_ਰੁੱਖ)
    {
      ਜੇ (!no_semicolon
	  && !c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ਜਾਓ saw_error;
      no_semicolon = ਝੂਠ;
      v = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ).ਮੁੱਲ;
      non_lvalue_p = !lvalue_p (v);
      v = c_fully_fold (v, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
      ਜੇ (v == error_mark_ਗੰਢ)
	ਜਾਓ saw_error;
      ਜੇ (non_lvalue_p)
	v = non_lvalue (v);
      ਜੇ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ਜਾਓ saw_error;
      eloc = c_parser_peek_token (parser)->location;
      ਵਿਅੰਜਕ = c_parser_cast_ਵਿਅੰਜਕ (parser, ਨਿਰਾ);
      lhs1 = ਵਿਅੰਜਕ.ਮੁੱਲ;
      ਵਿਅੰਜਕ = default_function_array_read_conversion (eloc, ਵਿਅੰਜਕ);
      unfolded_lhs1 = ਵਿਅੰਜਕ.ਮੁੱਲ;
      lhs1 = c_fully_fold (lhs1, ਝੂਠ, ਨਿਰਾ, ਸੱਚ);
      ਜੇ (lhs1 == error_mark_ਗੰਢ)
	ਜਾਓ saw_error;
      ਜੇ (!lvalue_p (unfolded_lhs1))
	lhs1 = non_lvalue (lhs1);
    }
  ਜੇ (structured_ਖੰਡ)
    {
      ਜੇ (!no_semicolon)
	c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
      c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>");
    }
ਪੂਰਾ:
  ਜੇ (weak && opcode != COND_ਵਿਅੰਜਕ)
    {
      error_at (loc, "%<weak%> clause requires atomic equality comparison");
      weak = ਝੂਠ;
    }
  ਜੇ (unfolded_lhs && unfolded_lhs1
      && !c_ਰੁੱਖ_equal (unfolded_lhs, unfolded_lhs1))
    {
      error ("%<#pragma omp atomic capture%> uses two different "
	     "expressions for memory");
      stmt = error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ
    stmt = c_ਅੰਤ_omp_atomic (loc, ਕੋਡ, opcode, lhs, rhs, v, lhs1, rhs1, r,
				swapped, ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ, weak);
  ਜੇ (stmt != error_mark_ਗੰਢ)
    ਜੋੜੋ_stmt (stmt);

  ਜੇ (!structured_ਖੰਡ && !no_semicolon)
    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
}


/* OpenMP 2.5:
   # pragma omp barrier new-line
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_barrier (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  c_ਅੰਤ_omp_barrier (loc);
}

/* OpenMP 2.5:
   # pragma omp critical [(name)] new-line
     structured-block

   OpenMP 4.5:
   # pragma omp critical [(name) [hint(expression)]] new-line

  LOC is the location of the #pragma itself.  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_CRITICAL_CLAUSE_ਨਕਾਬ		\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_HINT) )

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_critical (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ stmt, name = NULL_ਰੁੱਖ, clauses = NULL_ਰੁੱਖ;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  name = c_parser_peek_token (parser)->ਮੁੱਲ;
	  c_parser_consume_token (parser);
	  c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	}
      ਨਹੀਂਤਾਂ
	c_parser_error (parser, "expected identifier");

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
    }
  clauses = c_parser_omp_all_clauses (parser, OMP_CRITICAL_CLAUSE_ਨਕਾਬ,
				      "#pragma omp critical");
  stmt = c_parser_omp_structured_ਖੰਡ (parser, if_p);
  ਵਾਪਸ c_ਅੰਤ_omp_critical (loc, stmt, name, clauses);
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
ਵਿੱਚ
ਬਾਹਰਲਾ
     inout
     mutexinout  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_depobj (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਵਾਪਸ;
    }

  ਰੁੱਖ depobj = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
  ਜੇ (depobj != error_mark_ਗੰਢ)
    {
      ਜੇ (!lvalue_p (depobj))
	{
	  error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (depobj, loc),
		    "%<depobj%> expression is not lvalue expression");
	  depobj = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਰੁੱਖ addr = build_unary_op (ਵਿਅੰਜਕ_LOC_OR_LOC (depobj, loc), ADDR_ਵਿਅੰਜਕ,
				      depobj, ਝੂਠ);
	  ਜੇ (addr == error_mark_ਗੰਢ)
	    depobj = error_mark_ਗੰਢ;
	  ਨਹੀਂਤਾਂ
	    depobj = build_ਅਸਿੱਧਾ_ref (ਵਿਅੰਜਕ_LOC_OR_LOC (depobj, loc),
					 addr, RO_UNARY_ਤਾਰਾ);
	}
    }

  parens.skip_until_ਮਿਲਿਆ_close (parser);
  ਰੁੱਖ clause = NULL_ਰੁੱਖ;
  ਗਿਣਤੀ omp_clause_depend_ਕਿਸਮ ਕਿਸਮ = OMP_CLAUSE_DEPEND_INVALID;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);
  location_t c_loc = c_parser_peek_token (parser)->location;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      c_parser_consume_token (parser);
      ਜੇ (!strcmp ("depend", p))
	{
	  clause = c_parser_omp_clause_depend (parser, NULL_ਰੁੱਖ, c_loc);
	  clause = c_ਅੰਤ_omp_clauses (clause, C_ORT_OMP);
	  ਜੇ (!clause)
	    clause = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("destroy", p))
	{
	  matching_parens c_parens;
	  ਕਿਸਮ = OMP_CLAUSE_DEPEND_ਆਖਰੀ;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN)
	      && c_parens.require_open (parser))
	    {
	      ਰੁੱਖ destobj = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
	      ਜੇ (!lvalue_p (destobj))
		error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (destobj, c_loc),
			  "%<destroy%> expression is not lvalue expression");
	      ਨਹੀਂਤਾਂ ਜੇ (depobj != error_mark_ਗੰਢ
		       && !ਸੰਕਾਰਜ_equal_p (destobj, depobj,
					    OEP_ਮੇਲ_SIDE_EFFECTS
					    | OEP_LEXICOGRAPHIC))
		warning_at (ਵਿਅੰਜਕ_LOC_OR_LOC (destobj, c_loc), OPT_Wopenmp,
			    "the %<destroy%> expression %qE should be the same "
			    "as the %<depobj%> argument %qE", destobj, depobj);
	      c_parens.skip_until_ਮਿਲਿਆ_close (parser);
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("update", p))
	{
	  matching_parens c_parens;
	  ਜੇ (c_parens.require_open (parser))
	    {
	      location_t c2_loc = c_parser_peek_token (parser)->location;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		{
		  ਅਚਲ ਅੱਖਰ *p2
		    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

		  c_parser_consume_token (parser);
		  ਜੇ (!strcmp ("in", p2))
		    ਕਿਸਮ = OMP_CLAUSE_DEPEND_ਵਿੱਚ;
		  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("out", p2))
		    ਕਿਸਮ = OMP_CLAUSE_DEPEND_ਬਾਹਰਲਾ;
		  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("inout", p2))
		    ਕਿਸਮ = OMP_CLAUSE_DEPEND_INOUT;
		  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("mutexinoutset", p2))
		    ਕਿਸਮ = OMP_CLAUSE_DEPEND_MUTEXINOUTSET;
		  ਨਹੀਂਤਾਂ ਜੇ (!strcmp ("inoutset", p2))
		    ਕਿਸਮ = OMP_CLAUSE_DEPEND_INOUTSET;
		}
	      ਜੇ (ਕਿਸਮ == OMP_CLAUSE_DEPEND_INVALID)
		{
		  clause = error_mark_ਗੰਢ;
		  error_at (c2_loc, "expected %<in%>, %<out%>, %<inout%>, "
				    "%<mutexinoutset%> or %<inoutset%>");
		}
	      c_parens.skip_until_ਮਿਲਿਆ_close (parser);
	    }
	  ਨਹੀਂਤਾਂ
	    clause = error_mark_ਗੰਢ;
	}
    }
  ਜੇ (!clause && ਕਿਸਮ == OMP_CLAUSE_DEPEND_INVALID)
    {
      clause = error_mark_ਗੰਢ;
      error_at (c_loc, "expected %<depend%>, %<destroy%> or %<update%> clause");
    }
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  c_ਅੰਤ_omp_depobj (loc, depobj, ਕਿਸਮ, clause);
}


/* OpenMP 2.5:
   # pragma omp flush flush-vars[opt] new-line

   flush-vars:
     ( variable-list )

   OpenMP 5.0:
   # pragma omp flush memory-order-clause new-line  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_flush (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ਗਿਣਤੀ memmodel mo = MEMMODEL_ਆਖਰੀ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
    c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p
	= IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      ਜੇ (!strcmp (p, "seq_cst"))
	mo = MEMMODEL_SEQ_CST;
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "acq_rel"))
	mo = MEMMODEL_ACQ_REL;
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "release"))
	mo = MEMMODEL_RELEASE;
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "acquire"))
	mo = MEMMODEL_ACQUIRE;
      ਨਹੀਂਤਾਂ
	error_at (c_parser_peek_token (parser)->location,
		  "expected %<seq_cst%>, %<acq_rel%>, %<release%> or "
		  "%<acquire%>");
      c_parser_consume_token (parser);
    }
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      ਜੇ (mo != MEMMODEL_ਆਖਰੀ)
	error_at (c_parser_peek_token (parser)->location,
		  "%<flush%> list specified together with memory order "
		  "clause");
      c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ਨਿਰਾ);
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    c_parser_error (parser, "expected %<(%> or end of line");
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  c_ਅੰਤ_omp_flush (loc, mo);
}

/* Return true if next tokens contain a standard attribute that contains
   omp::directive (DIRECTIVE).  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_section_ਜਾਂਚ (c_parser *parser, ਅਚਲ ਅੱਖਰ *directive,
			   ਤਾਰਕਿਕ tentative)
{
  ਜੇ (!c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
    ਵਾਪਸ ਝੂਠ;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ n = 3;
  ਜੇ (!c_parser_check_ਸੰਤੁਲਿਤ_raw_token_sequence (parser, &n))
    ਵਾਪਸ ਝੂਠ;
  c_token *token = c_parser_peek_nth_token_raw (parser, n);
  ਜੇ (token->type != CPP_CLOSE_ਵਰਗਫਲ)
    ਵਾਪਸ ਝੂਠ;
  token = c_parser_peek_nth_token_raw (parser, n + 1);
  ਜੇ (token->type != CPP_CLOSE_ਵਰਗਫਲ)
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (n < 9)
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (c_parser_peek_nth_token_raw (parser, 3)->type == CPP_NAME
      && c_parser_peek_nth_token_raw (parser, 4)->type == CPP_OPEN_PAREN
      && c_parser_peek_nth_token_raw (parser, 5)->type == CPP_NAME)
    {
      ਰੁੱਖ ਪਹਿਲਾ = c_parser_peek_nth_token_raw (parser, 3)->ਮੁੱਲ;
      ਰੁੱਖ ਦੂਜਾ = c_parser_peek_nth_token_raw (parser, 5)->ਮੁੱਲ;
      ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (ਪਹਿਲਾ), "directive")
	  && strcmp (IDENTIFIER_ਸੂਚਕ (ਪਹਿਲਾ), "__directive__"))
	ਵਾਪਸ ਝੂਠ;
      ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (ਦੂਜਾ), directive))
	ਵਾਪਸ ਝੂਠ;
    }
  ਜੇ (tentative)
    ਵਾਪਸ ਸੱਚ;
  location_t ਪਹਿਲਾ_loc = c_parser_peek_token (parser)->location;
  location_t ਆਖਰੀ_loc = c_parser_peek_nth_token_raw (parser, n + 1)->location;
  location_t ਵਿਚਕਾਰ_loc = UNKNOWN_LOCATION;
  ਰੁੱਖ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
  ਤਾਰਕਿਕ ਵੇਖਿਆ = ਝੂਠ;
  ਪੂਰਨ cnt = 0;
  ਲਈ (ਰੁੱਖ attr = std_attrs; attr; attr = ਰੁੱਖ_CHAIN (attr))
    ਜੇ (is_attribute_namespace_p ("omp", attr)
	&& is_attribute_p ("directive", get_attribute_name (attr)))
      {
	ਲਈ (ਰੁੱਖ a = ਰੁੱਖ_ਮੁੱਲ (attr); a; a = ਰੁੱਖ_CHAIN (a))
	  {
	    ਰੁੱਖ d = ਰੁੱਖ_ਮੁੱਲ (a);
	    gcc_assert (ਰੁੱਖ_ਕੋਡ (d) == C_TOKEN_VEC);
	    c_token *ਪਹਿਲਾ = C_TOKEN_VEC_ਟੋਕਨ (d)->ਪਤਾ ();
	    cnt++;
	    ਜੇ (ਪਹਿਲਾ->type == CPP_NAME
		&& strcmp (IDENTIFIER_ਸੂਚਕ (ਪਹਿਲਾ->ਮੁੱਲ),
			   directive) == 0)
	      {
		ਵੇਖਿਆ = ਸੱਚ;
		ਜੇ (ਵਿਚਕਾਰ_loc == UNKNOWN_LOCATION)
		  ਵਿਚਕਾਰ_loc = ਪਹਿਲਾ->location;
	      }
	  }
      }
  ਜੇ (!ਵੇਖਿਆ)
    ਵਾਪਸ ਝੂਠ;
  ਜੇ (cnt != 1 || ਰੁੱਖ_CHAIN (std_attrs))
    {
      error_at (make_location (ਪਹਿਲਾ_loc, ਆਖਰੀ_loc, ਵਿਚਕਾਰ_loc),
		"%<[[omp::directive(%s)]]%> must be the only specified "
		"attribute on a statement", directive);
      ਵਾਪਸ ਝੂਠ;
    }
  c_parser_handle_statement_omp_ਗੁਣ (parser, std_attrs, ਨਿਰਾ);
  ਵਾਪਸ ਸੱਚ;
}

/* Parse an OpenMP structured block sequence.  KIND is the corresponding
   separating directive.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_structured_ਖੰਡ_sequence (c_parser *parser,
					ਗਿਣਤੀ pragma_ਕਿਸਮ ਕਿਸਮ)
{
  ਰੁੱਖ stmt = ਧੱਕੋ_stmt_list ();
  c_parser_statement (parser, ਨਿਰਾ);
  ਕਰੋ
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	ਰੋਕੋ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EOF))
	ਰੋਕੋ;

      ਜੇ (ਕਿਸਮ != PRAGMA_NONE
	  && c_parser_peek_token (parser)->pragma_ਕਿਸਮ == ਕਿਸਮ)
	ਰੋਕੋ;

      ਜੇ (ਕਿਸਮ != PRAGMA_NONE
	  && c_parser_omp_section_ਜਾਂਚ (parser,
					ਕਿਸਮ == PRAGMA_OMP_ਜਾਂਚ
					? "scan" : "section", ਝੂਠ))
	ਰੋਕੋ;

      c_parser_statement (parser, ਨਿਰਾ);
    }
  ਜਦੋਂ (1);
  ਵਾਪਸ ਕੱਢੋ_stmt_list (stmt);
}

/* OpenMP 5.0:

   scan-loop-body:
     { structured-block scan-directive structured-block }  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_ਜਾਂਚ_loop_body (c_parser *parser, ਤਾਰਕਿਕ open_brace_parsed)
{
  ਰੁੱਖ substmt;
  location_t loc;
  ਰੁੱਖ clauses = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ ਮਿਲਿਆ_ਜਾਂਚ = ਝੂਠ;

  loc = c_parser_peek_token (parser)->location;
  ਜੇ (!open_brace_parsed
      && !c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = ਝੂਠ;
      ਵਾਪਸ;
    }

  ਜੇ (c_parser_peek_token (parser)->pragma_ਕਿਸਮ != PRAGMA_OMP_ਜਾਂਚ)
    substmt = c_parser_omp_structured_ਖੰਡ_sequence (parser, PRAGMA_OMP_ਜਾਂਚ);
  ਨਹੀਂਤਾਂ
    {
      warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		  "%<#pragma omp scan%> with zero preceding executable "
		  "statements");
      substmt = build_ਖਾਲੀ_ਥਾਵਾਂ_stmt (loc);
    }
  substmt = build2 (OMP_ਜਾਂਚ, void_type_ਗੰਢ, substmt, NULL_ਰੁੱਖ);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (substmt, loc);
  ਜੋੜੋ_stmt (substmt);

  loc = c_parser_peek_token (parser)->location;
  ਜੇ (c_parser_peek_token (parser)->pragma_ਕਿਸਮ == PRAGMA_OMP_ਜਾਂਚ)
    {
      ਗਿਣਤੀ omp_clause_ਕੋਡ clause = OMP_CLAUSE_ERROR;
      ਮਿਲਿਆ_ਜਾਂਚ = ਸੱਚ;

      c_parser_consume_pragma (parser);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  ਅਚਲ ਅੱਖਰ *p
	    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	  ਜੇ (strcmp (p, "inclusive") == 0)
	    clause = OMP_CLAUSE_INCLUSIVE;
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "exclusive") == 0)
	    clause = OMP_CLAUSE_EXCLUSIVE;
	}
      ਜੇ (clause != OMP_CLAUSE_ERROR)
	{
	  c_parser_consume_token (parser);
	  clauses = c_parser_omp_var_list_parens (parser, clause, NULL_ਰੁੱਖ);
	}
      ਨਹੀਂਤਾਂ
	c_parser_error (parser, "expected %<inclusive%> or "
				"%<exclusive%> clause");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
    }
  ਨਹੀਂਤਾਂ
    error ("expected %<#pragma omp scan%>");

  clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP);
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
    substmt = c_parser_omp_structured_ਖੰਡ_sequence (parser, PRAGMA_NONE);
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (ਮਿਲਿਆ_ਜਾਂਚ)
	warning_at (loc, OPT_Wopenmp,
		    "%<#pragma omp scan%> with zero succeeding executable "
		    "statements");
      substmt = build_ਖਾਲੀ_ਥਾਵਾਂ_stmt (loc);
    }
  substmt = build2 (OMP_ਜਾਂਚ, void_type_ਗੰਢ, substmt, clauses);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (substmt, loc);
  ਜੋੜੋ_stmt (substmt);

  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE,
			     "expected %<}%>");
}


/* Check if the next tokens can start a canonical loop.  Return true if yes,
   otherwise diagnose an error if ERROR_P is true, and return false.  */
ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_ਅਗਲਾ_ਟੋਕਨ_can_be_canon_loop (c_parser *parser,
					    ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ,
					    ਤਾਰਕਿਕ error_p)
{
  ਜੇ (ਕੋਡ == OACC_LOOP)
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_FOR))
	ਵਾਪਸ ਸੱਚ;
      ਜੇ (error_p)
	c_parser_error (parser, "for statement expected");
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_FOR))
	ਵਾਪਸ ਸੱਚ;

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA))
	ਚੋਣ (c_parser_peek_token (parser)->pragma_ਕਿਸਮ)
	  {
	  ਹਾਲਤ PRAGMA_OMP_UNROLL:
	  ਹਾਲਤ PRAGMA_OMP_TILE:
	    ਵਾਪਸ ਸੱਚ;
	  ਮੂਲ:
	    ਰੋਕੋ;
	  }

      /* Skip standard attributes on next for in case they are
	 [[omp::directive (unroll partial (4))]] or
	 [[omp::directive (tile sizes (1, 2, 3))]] etc.  */
      ਮਾਪ_t n = c_parser_skip_std_attribute_spec_seq (parser, 1);
      c_token *token = c_parser_peek_nth_token_raw (parser, n);
      /* TOKEN is a raw token that hasn't been converted to a keyword yet,
	 we have to do the lookup explicitly.  */
      ਜੇ (token->type == CPP_NAME
	  && C_IS_RESERVED_ਸ਼ਬਦ (token->ਮੁੱਲ)
	  && C_RID_ਕੋਡ (token->ਮੁੱਲ) == RID_FOR)
	ਵਾਪਸ ਸੱਚ;
      ਜੇ (error_p)
	c_parser_error (parser,	"loop nest expected");
    }

  ਵਾਪਸ ਝੂਠ;
}

ਸਥਿਰ ਰੁੱਖ c_parser_omp_tile (location_t, c_parser *, ਤਾਰਕਿਕ *);
ਸਥਿਰ ਰੁੱਖ c_parser_omp_unroll (location_t, c_parser *, ਤਾਰਕਿਕ *);

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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_loop_nest (c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ decl = NULL_ਰੁੱਖ, cond = NULL_ਰੁੱਖ, incr = NULL_ਰੁੱਖ, init = NULL_ਰੁੱਖ;
  ਰੁੱਖ body = NULL_ਰੁੱਖ;
  matching_parens parens;
  ਤਾਰਕਿਕ moreloops;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ save_ਵਿੱਚ_statement;
  ਰੁੱਖ loop_scope;
  location_t loc;
  ਬਣਤਰ omp_for_parse_ਅੰਕੜੇ *omp_for_parse_state
    = parser->omp_for_parse_state;
  gcc_assert (omp_for_parse_state);
  ਪੂਰਨ ਡੂੰਘਾਈ = omp_for_parse_state->ਡੂੰਘਾਈ;

  /* Arrange for C23 standard attribute syntax to be parsed as regular
     pragmas.  */
  ਜੇ (c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
    {
      ਰੁੱਖ std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      c_parser_handle_statement_omp_ਗੁਣ (parser, std_attrs, ਨਿਰਾ);
      ਜੇ (std_attrs)
	error_at (c_parser_peek_token (parser)->location,
		  "attributes other than OpenMP directives "
		  "are not allowed on %<for%> in loop nest");
    }

  loc = c_parser_peek_token (parser)->location;

  /* Handle loop transformations first.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA))
    {
      ਰੁੱਖ transform = NULL_ਰੁੱਖ, sizes, body = NULL_ਰੁੱਖ;
      ਪੂਰਨ ਗਿਣਤੀ_2 = 0;
      ਚੋਣ (c_parser_peek_token (parser)->pragma_ਕਿਸਮ)
	{
	ਹਾਲਤ PRAGMA_OMP_UNROLL:
	  c_parser_consume_pragma (parser);
	  body = ਧੱਕੋ_stmt_list ();
	  transform = c_parser_omp_unroll (loc, parser, if_p);
	  body = ਕੱਢੋ_stmt_list (body);
	  ਜੇ (transform == NULL_ਰੁੱਖ || transform == error_mark_ਗੰਢ)
	    {
	      transform = error_mark_ਗੰਢ;
	      ਰੋਕੋ;
	    }
	  gcc_assert (ਰੁੱਖ_ਕੋਡ (transform) == OMP_UNROLL);
	  ਜੇ (omp_ਲੱਭੋ_clause (OMP_FOR_CLAUSES (transform),
			       OMP_CLAUSE_PARTIAL))
	    {
	      ਜੇ (omp_for_parse_state->ਗਿਣਤੀ_2 - ਡੂੰਘਾਈ > 1)
		{
		  error_at (loc, "%<unroll%> construct with %<partial%> "
				 "clause generates just one loop with "
				 "canonical form but %d loops are needed",
			    omp_for_parse_state->ਗਿਣਤੀ_2 - ਡੂੰਘਾਈ);
		  transform = error_mark_ਗੰਢ;
		}
	      ਨਹੀਂਤਾਂ
		ਗਿਣਤੀ_2 = 1;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      error_at (loc, "generated loop of %<unroll%> construct "
			     "without %<partial%> clause does not have "
			     "canonical form");
	      transform = error_mark_ਗੰਢ;
	    }
	  ਰੋਕੋ;
	ਹਾਲਤ PRAGMA_OMP_TILE:
	  c_parser_consume_pragma (parser);
	  body = ਧੱਕੋ_stmt_list ();
	  transform = c_parser_omp_tile (loc, parser, if_p);
	  body = ਕੱਢੋ_stmt_list (body);
	  ਜੇ (transform == NULL_ਰੁੱਖ || transform == error_mark_ਗੰਢ)
	    {
	      transform = error_mark_ਗੰਢ;
	      ਰੋਕੋ;
	    }
	  gcc_assert (ਰੁੱਖ_ਕੋਡ (transform) == OMP_TILE);
	  sizes = omp_ਲੱਭੋ_clause (OMP_FOR_CLAUSES (transform),
				   OMP_CLAUSE_SIZES);
	  gcc_assert (sizes);
	  ਗਿਣਤੀ_2 = list_ਲੰਮਾਈ (OMP_CLAUSE_SIZES_LIST (sizes));
	  ਜੇ (ਡੂੰਘਾਈ + ਗਿਣਤੀ_2 < omp_for_parse_state->ਗਿਣਤੀ_2)
	    {
	      error_at (loc, "%<tile%> construct generates %d loops "
			     "with canonical form but %d loops are needed",
			ਗਿਣਤੀ_2, omp_for_parse_state->ਗਿਣਤੀ_2 - ਡੂੰਘਾਈ);
	      transform = error_mark_ਗੰਢ;
	    }
	  ਰੋਕੋ;
	ਮੂਲ:
	  c_parser_pragma (parser, pragma_stmt, ਨਿਰਾ, void_list_ਗੰਢ);
	  ਰੋਕੋ;
	}
      ਜੇ (transform == NULL_ਰੁੱਖ)
	error_at (loc, "expected %<for%> loop or OpenMP loop "
		       "transformation construct");
      ਜੇ (transform == NULL_ਰੁੱਖ || transform == error_mark_ਗੰਢ)
	{
	  omp_for_parse_state->fail = ਸੱਚ;
	  ਵਾਪਸ NULL_ਰੁੱਖ;
	}
      ਲਈ (ਗਿਣਤੀ_2 = omp_for_parse_state->ਗਿਣਤੀ_2; ਡੂੰਘਾਈ < ਗਿਣਤੀ_2; ++ਡੂੰਘਾਈ)
	{
	  ਰੁੱਖ_VEC_ELT (omp_for_parse_state->declv, ਡੂੰਘਾਈ) = NULL_ਰੁੱਖ;
	  ਰੁੱਖ_VEC_ELT (omp_for_parse_state->initv, ਡੂੰਘਾਈ) = NULL_ਰੁੱਖ;
	  ਰੁੱਖ_VEC_ELT (omp_for_parse_state->condv, ਡੂੰਘਾਈ) = NULL_ਰੁੱਖ;
	  ਰੁੱਖ_VEC_ELT (omp_for_parse_state->incrv, ਡੂੰਘਾਈ) = NULL_ਰੁੱਖ;
	}
      omp_for_parse_state->want_nested_loop = ਝੂਠ;
      ਵਾਪਸ body;
    }

  /* We have already matched the FOR token but not consumed it yet.  */
  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_FOR));
  c_parser_consume_token (parser);

  /* Forbid break/continue in the loop initializer, condition, and
     increment expressions.  */
  save_ਵਿੱਚ_statement = ਵਿੱਚ_statement;
  ਵਿੱਚ_statement = ਵਿੱਚ_OMP_ਖੰਡ;

  /* We are not in intervening code now.  */
  omp_for_parse_state->ਵਿੱਚ_intervening_ਕੋਡ = ਝੂਠ;

  ਜੇ (!parens.require_open (parser))
    {
      omp_for_parse_state->fail = ਸੱਚ;
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  /* An implicit scope block surrounds each level of FOR loop, for
     declarations of iteration variables at this loop depth.  */
  loop_scope = c_begin_compound_stmt (ਸੱਚ);

  /* Parse the initialization declaration or expression.  */
  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser))
    {
      /* This is a declaration, which must be added to the pre_body code.  */
      ਰੁੱਖ this_pre_body = ਧੱਕੋ_stmt_list ();
      c_ਵਿੱਚ_omp_for = ਸੱਚ;
      c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ,
				     ਝੂਠ);
      c_ਵਿੱਚ_omp_for = ਝੂਠ;
      this_pre_body = ਕੱਢੋ_stmt_list (this_pre_body);
      append_ਮੰਜ਼ਿਲ_statement_list_force (this_pre_body,
				      &(omp_for_parse_state->pre_body));
      decl = check_for_loop_decls (omp_for_parse_state->for_loc, flag_isoc99);
      ਜੇ (decl == ਨਿਰਾ)
	ਜਾਓ error_init;
      ਜੇ (DECL_INITIAL (decl) == error_mark_ਗੰਢ)
	decl = error_mark_ਗੰਢ;
      init = decl;
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	   && c_parser_peek_2nd_token (parser)->type == CPP_EQ)
    {
      ਬਣਤਰ c_ਵਿਅੰਜਕ decl_exp;
      ਬਣਤਰ c_ਵਿਅੰਜਕ init_exp;
      location_t init_loc;

      decl_exp = c_parser_postfix_ਵਿਅੰਜਕ (parser);
      decl = decl_exp.ਮੁੱਲ;

      c_parser_require (parser, CPP_EQ, "expected %<=%>");

      init_loc = c_parser_peek_token (parser)->location;
      init_exp = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
      init_exp = default_function_array_read_conversion (init_loc,
							 init_exp);
      c_ਵਿੱਚ_omp_for = ਸੱਚ;
      init = build_modify_ਵਿਅੰਜਕ (init_loc, decl, decl_exp.original_type,
				NOP_ਵਿਅੰਜਕ, init_loc, init_exp.ਮੁੱਲ,
				init_exp.original_type);
      c_ਵਿੱਚ_omp_for = ਝੂਠ;
      init = c_process_ਵਿਅੰਜਕ_stmt (init_loc, init);

      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
    }
  ਨਹੀਂਤਾਂ
    {
    error_init:
      c_parser_error (parser,
		      "expected iteration declaration or initialization");
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");
      omp_for_parse_state->fail = ਸੱਚ;
      ਜਾਓ parse_ਅਗਲਾ;
    }

  /* Parse the loop condition.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_SEMICOLON))
    {
      location_t cond_loc = c_parser_peek_token (parser)->location;
      c_ਵਿੱਚ_omp_for = ਸੱਚ;
      ਬਣਤਰ c_ਵਿਅੰਜਕ cond_ਵਿਅੰਜਕ
	= c_parser_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (parser, ਨਿਰਾ, NULL_ਰੁੱਖ);
      c_ਵਿੱਚ_omp_for = ਝੂਠ;

      cond = cond_ਵਿਅੰਜਕ.ਮੁੱਲ;
      cond = c_objc_common_truthvalue_conversion (cond_loc, cond);
      ਚੋਣ (cond_ਵਿਅੰਜਕ.original_ਕੋਡ)
	{
	ਹਾਲਤ GT_ਵਿਅੰਜਕ:
	ਹਾਲਤ GE_ਵਿਅੰਜਕ:
	ਹਾਲਤ LT_ਵਿਅੰਜਕ:
	ਹਾਲਤ LE_ਵਿਅੰਜਕ:
	  ਰੋਕੋ;
	ਹਾਲਤ NE_ਵਿਅੰਜਕ:
	  ਜੇ (omp_for_parse_state->ਕੋਡ != OACC_LOOP)
	    ਰੋਕੋ;
	  /* FALLTHRU.  */
	ਮੂਲ:
	  /* Can't be cond = error_mark_node, because we want to preserve
	     the location until c_finish_omp_for.  */
	  cond = build1 (NOP_ਵਿਅੰਜਕ, boolean_type_ਗੰਢ, error_mark_ਗੰਢ);
	  ਰੋਕੋ;
	}
      protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (cond, cond_loc);
    }
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");

  /* Parse the increment expression.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_CLOSE_PAREN))
    {
      location_t incr_loc = c_parser_peek_token (parser)->location;

      incr = c_process_ਵਿਅੰਜਕ_stmt (incr_loc,
				  c_parser_ਵਿਅੰਜਕ (parser).ਮੁੱਲ);
    }
  parens.skip_until_ਮਿਲਿਆ_close (parser);

  ਜੇ (decl == ਨਿਰਾ || decl == error_mark_ਗੰਢ || init == error_mark_ਗੰਢ)
    omp_for_parse_state->fail = ਸੱਚ;
  ਨਹੀਂਤਾਂ
    {
      ਰੁੱਖ_VEC_ELT (omp_for_parse_state->declv, ਡੂੰਘਾਈ) = decl;
      ਰੁੱਖ_VEC_ELT (omp_for_parse_state->initv, ਡੂੰਘਾਈ) = init;
      ਰੁੱਖ_VEC_ELT (omp_for_parse_state->condv, ਡੂੰਘਾਈ) = cond;
      ਰੁੱਖ_VEC_ELT (omp_for_parse_state->incrv, ਡੂੰਘਾਈ) = incr;
    }

parse_ਅਗਲਾ:
  moreloops = ਡੂੰਘਾਈ < omp_for_parse_state->ਗਿਣਤੀ_2 - 1;
  omp_for_parse_state->want_nested_loop = moreloops;
  ਜੇ (moreloops
      && c_parser_omp_ਅਗਲਾ_ਟੋਕਨ_can_be_canon_loop (parser,
						     omp_for_parse_state->ਕੋਡ,
						     ਝੂਠ))
    {
      omp_for_parse_state->ਡੂੰਘਾਈ++;
      body = c_parser_omp_loop_nest (parser, if_p);
      omp_for_parse_state->ਡੂੰਘਾਈ--;
    }
  ਨਹੀਂਤਾਂ ਜੇ (moreloops && c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
    {
      /* This is the open brace in the loop-body grammar production.  Rather
	 than trying to special-case braces, just parse it as a compound
	 statement and handle the nested loop-body case there.  Note that
	 when we see a further open brace inside the compound statement
	 loop-body, we don't know whether it is the start of intervening
	 code that is a compound statement, or a level of braces
	 surrounding a nested loop-body.  Use the WANT_NESTED_LOOP state
	 bit to ensure we have only one nested loop at each level.  */
      omp_for_parse_state->ਵਿੱਚ_intervening_ਕੋਡ = ਸੱਚ;
      body = c_parser_compound_statement (parser, ਨਿਰਾ);
      omp_for_parse_state->ਵਿੱਚ_intervening_ਕੋਡ = ਝੂਠ;
      ਜੇ (omp_for_parse_state->want_nested_loop)
	{
	  /* We have already parsed the whole loop body and not found a
	     nested loop.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = ਸੱਚ;
	}
      if_p = ਨਿਰਾ;
    }
  ਨਹੀਂਤਾਂ
    {
      /* This is the final-loop-body case in the grammar: we have
	 something that is not a FOR and not an open brace.  */
      ਜੇ (moreloops)
	{
	  /* If we were expecting a nested loop, give an error and mark
	     that parsing has failed, and try to recover by parsing the
	     body as regular code without further collapsing.  */
	  error_at (omp_for_parse_state->for_loc,
		    "not enough nested loops");
	  omp_for_parse_state->fail = ਸੱਚ;
	}
      ਵਿੱਚ_statement = ਵਿੱਚ_OMP_FOR;
      parser->omp_for_parse_state = ਨਿਰਾ;
      body = ਧੱਕੋ_stmt_list ();
      ਜੇ (omp_for_parse_state->inscan)
	c_parser_omp_ਜਾਂਚ_loop_body (parser, ਝੂਠ);
      ਨਹੀਂਤਾਂ
	ਜੋੜੋ_stmt (c_parser_c99_ਖੰਡ_statement (parser, if_p));
      body = ਕੱਢੋ_stmt_list (body);
      parser->omp_for_parse_state = omp_for_parse_state;
    }
  ਵਿੱਚ_statement = save_ਵਿੱਚ_statement;
  omp_for_parse_state->want_nested_loop = ਝੂਠ;
  omp_for_parse_state->ਵਿੱਚ_intervening_ਕੋਡ = ਸੱਚ;

  /* Pop and return the implicit scope surrounding this level of loop.
     If the iteration variable at this depth was bound in the for loop,
     pull out and save the binding.  Later in c_parser_omp_for_loop,
     these bindings will be moved to the scope surrounding the entire
     OMP_FOR.  That keeps the gimplifier happy later on, and meanwhile
     we have already resolved all references to the iteration variable
     in its true scope.  */
  ਜੇ (body)
    ਜੋੜੋ_stmt (body);
  body = c_ਸਿਰਾ_compound_stmt (loc, loop_scope, ਸੱਚ);
  ਜੇ (decl && ਰੁੱਖ_ਕੋਡ (body) == BIND_ਵਿਅੰਜਕ)
    {
      ਰੁੱਖ t = BIND_ਵਿਅੰਜਕ_VARS (body);
      ਰੁੱਖ prev = NULL_ਰੁੱਖ, ਅਗਲਾ = NULL_ਰੁੱਖ;
      ਜਦੋਂ (t)
	{
	  ਅਗਲਾ = DECL_CHAIN (t);
	  ਜੇ (t == decl)
	    {
	      ਜੇ (prev)
		DECL_CHAIN (prev) = ਅਗਲਾ;
	      ਨਹੀਂਤਾਂ
		{
		  BIND_ਵਿਅੰਜਕ_VARS (body) = ਅਗਲਾ;
		  ਖੰਡ_VARS (BIND_ਵਿਅੰਜਕ_ਖੰਡ (body)) = ਅਗਲਾ;
		}
	      DECL_CHAIN (t) = omp_for_parse_state->bindings;
	      omp_for_parse_state->bindings = t;
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      prev = t;
	      t = ਅਗਲਾ;
	    }
	}
      ਜੇ (BIND_ਵਿਅੰਜਕ_VARS (body) == NULL_ਰੁੱਖ)
	body = BIND_ਵਿਅੰਜਕ_BODY (body);
    }

  ਵਾਪਸ body;
}

/* Parse the restricted form of loop statements allowed by OpenACC and OpenMP.
   The real trick here is to determine the loop control variable early
   so that we can push a new decl if necessary to make it private.
   LOC is the location of the "acc" or "omp" in "#pragma acc" or "#pragma omp",
   respectively.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_for_loop (location_t loc, c_parser *parser, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ,
		       ਰੁੱਖ clauses, ਰੁੱਖ *cclauses, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ body, stmt, cl;
  ਰੁੱਖ ret = NULL_ਰੁੱਖ;
  ਰੁੱਖ ordered_cl = NULL_ਰੁੱਖ;
  ਪੂਰਨ i, collapse = 1, ordered = 0, ਗਿਣਤੀ_2;
  ਤਾਰਕਿਕ oacc_tiling = ਝੂਠ;
  ਤਾਰਕਿਕ inscan = ਝੂਠ;
  ਬਣਤਰ omp_for_parse_ਅੰਕੜੇ ਅੰਕੜੇ;
  ਬਣਤਰ omp_for_parse_ਅੰਕੜੇ *save_ਅੰਕੜੇ = parser->omp_for_parse_state;

  ਲਈ (cl = clauses; cl; cl = OMP_CLAUSE_CHAIN (cl))
    ਜੇ (OMP_CLAUSE_ਕੋਡ (cl) == OMP_CLAUSE_COLLAPSE)
      collapse = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (OMP_CLAUSE_COLLAPSE_ਵਿਅੰਜਕ (cl));
    ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (cl) == OMP_CLAUSE_TILE)
      {
	oacc_tiling = ਸੱਚ;
	collapse = list_ਲੰਮਾਈ (OMP_CLAUSE_TILE_LIST (cl));
      }
    ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (cl) == OMP_CLAUSE_SIZES)
      collapse = list_ਲੰਮਾਈ (OMP_CLAUSE_SIZES_LIST (cl));
    ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (cl) == OMP_CLAUSE_ORDERED
	     && OMP_CLAUSE_ORDERED_ਵਿਅੰਜਕ (cl))
      {
	ordered_cl = cl;
	ordered = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (OMP_CLAUSE_ORDERED_ਵਿਅੰਜਕ (cl));
      }
    ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (cl) == OMP_CLAUSE_REDUCTION
	     && OMP_CLAUSE_REDUCTION_INSCAN (cl)
	     && (ਕੋਡ == OMP_SIMD || ਕੋਡ == OMP_FOR))
      inscan = ਸੱਚ;

  ਜੇ (ordered && ordered < collapse)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_cl),
		"%<ordered%> clause parameter is less than %<collapse%>");
      OMP_CLAUSE_ORDERED_ਵਿਅੰਜਕ (ordered_cl)
	= build_int_cst (integer_type_ਗੰਢ, collapse);
      ordered = collapse;
    }

  gcc_assert (oacc_tiling || (collapse >= 1 && ordered >= 0));
  ਗਿਣਤੀ_2 = ordered ? ordered : collapse;

  ਜੇ (!c_parser_omp_ਅਗਲਾ_ਟੋਕਨ_can_be_canon_loop (parser, ਕੋਡ, ਸੱਚ))
    ਵਾਪਸ ਨਿਰਾ;

  /* Initialize parse state for recursive descent.  */
  ਅੰਕੜੇ.declv = make_ਰੁੱਖ_vec (ਗਿਣਤੀ_2);
  ਅੰਕੜੇ.initv = make_ਰੁੱਖ_vec (ਗਿਣਤੀ_2);
  ਅੰਕੜੇ.condv = make_ਰੁੱਖ_vec (ਗਿਣਤੀ_2);
  ਅੰਕੜੇ.incrv = make_ਰੁੱਖ_vec (ਗਿਣਤੀ_2);
  ਅੰਕੜੇ.pre_body = NULL_ਰੁੱਖ;
  ਅੰਕੜੇ.bindings = NULL_ਰੁੱਖ;
  ਅੰਕੜੇ.for_loc = c_parser_peek_token (parser)->location;
  ਅੰਕੜੇ.ਗਿਣਤੀ_2 = ਗਿਣਤੀ_2;
  ਅੰਕੜੇ.ਡੂੰਘਾਈ = 0;
  ਅੰਕੜੇ.want_nested_loop = ਸੱਚ;
  ਅੰਕੜੇ.ordered = ordered > 0;
  ਅੰਕੜੇ.ਵਿੱਚ_intervening_ਕੋਡ = ਝੂਠ;
  ਅੰਕੜੇ.perfect_nesting_fail = ਝੂਠ;
  ਅੰਕੜੇ.fail = ਝੂਠ;
  ਅੰਕੜੇ.inscan = inscan;
  ਅੰਕੜੇ.saw_intervening_ਕੋਡ = ਝੂਠ;
  ਅੰਕੜੇ.ਕੋਡ = ਕੋਡ;
  parser->omp_for_parse_state = &ਅੰਕੜੇ;

  body = c_parser_omp_loop_nest (parser, if_p);

  /* Add saved bindings for iteration variables that were declared in
     the nested for loop to the scope surrounding the entire loop.  */
  ਲਈ (ਰੁੱਖ t = ਅੰਕੜੇ.bindings; t; )
    {
      ਰੁੱਖ n = ਰੁੱਖ_CHAIN (t);
      ਰੁੱਖ_CHAIN (t) = NULL_ਰੁੱਖ;
      pushdecl (t);
      t = n;
    }

  /* Only bother calling c_finish_omp_for if we haven't already generated
     an error from the initialization parsing.  */
  ਜੇ (!ਅੰਕੜੇ.fail)
    {
      c_ਵਿੱਚ_omp_for = ਸੱਚ;
      stmt = c_ਅੰਤ_omp_for (loc, ਕੋਡ, ਅੰਕੜੇ.declv, ਨਿਰਾ, ਅੰਕੜੇ.initv,
			       ਅੰਕੜੇ.condv, ਅੰਕੜੇ.incrv,
			       body, ਅੰਕੜੇ.pre_body, ਸੱਚ);
      c_ਵਿੱਚ_omp_for = ਝੂਠ;

      /* Check for iterators appearing in lb, b or incr expressions.  */
      ਜੇ (stmt && !c_omp_check_loop_iv (stmt, ਅੰਕੜੇ.declv, ਨਿਰਾ))
	stmt = NULL_ਰੁੱਖ;

      /* Check for errors involving lb/ub/incr expressions referencing
	 variables declared in intervening code.  */
      ਜੇ (ਅੰਕੜੇ.saw_intervening_ਕੋਡ
	  && stmt
	  && !c_omp_check_loop_binding_exprs (stmt, ਨਿਰਾ))
	stmt = NULL_ਰੁੱਖ;

      ਜੇ (stmt)
	{
	  ਜੋੜੋ_stmt (stmt);

	  ਲਈ (i = 0; i < ਰੁੱਖ_VEC_ਲੰਮਾਈ (OMP_FOR_INIT (stmt)); i++)
	    {
	      ਰੁੱਖ init = ਰੁੱਖ_VEC_ELT (OMP_FOR_INIT (stmt), i);
	      ਜੇ (init == NULL_ਰੁੱਖ)
		ਰੋਕੋ;
	      gcc_assert (ਰੁੱਖ_ਕੋਡ (init) == MODIFY_ਵਿਅੰਜਕ);
	      ਰੁੱਖ decl = ਰੁੱਖ_ਸੰਕਾਰਜ (init, 0);
	      ਰੁੱਖ cond = ਰੁੱਖ_VEC_ELT (OMP_FOR_COND (stmt), i);
	      gcc_assert (COMPARISON_CLASS_P (cond));
	      gcc_assert (ਰੁੱਖ_ਸੰਕਾਰਜ (cond, 0) == decl);

	      ਰੁੱਖ op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (init, 1);
	      ਜੇ (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || ਰੁੱਖ_ਕੋਡ (op0) != ਰੁੱਖ_VEC)
		ਰੁੱਖ_ਸੰਕਾਰਜ (init, 1) = c_fully_fold (op0, ਝੂਠ, ਨਿਰਾ);
	      ਨਹੀਂਤਾਂ
		{
		  ਰੁੱਖ_VEC_ELT (op0, 1)
		    = c_fully_fold (ਰੁੱਖ_VEC_ELT (op0, 1), ਝੂਠ, ਨਿਰਾ);
		  ਰੁੱਖ_VEC_ELT (op0, 2)
		    = c_fully_fold (ਰੁੱਖ_VEC_ELT (op0, 2), ਝੂਠ, ਨਿਰਾ);
		}

	      ਰੁੱਖ op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (cond, 1);
	      ਜੇ (!OMP_FOR_NON_RECTANGULAR (stmt)
		  || ਰੁੱਖ_ਕੋਡ (op1) != ਰੁੱਖ_VEC)
		ਰੁੱਖ_ਸੰਕਾਰਜ (cond, 1) = c_fully_fold (op1, ਝੂਠ, ਨਿਰਾ);
	      ਨਹੀਂਤਾਂ
		{
		  ਰੁੱਖ_VEC_ELT (op1, 1)
		    = c_fully_fold (ਰੁੱਖ_VEC_ELT (op1, 1), ਝੂਠ, ਨਿਰਾ);
		  ਰੁੱਖ_VEC_ELT (op1, 2)
		    = c_fully_fold (ਰੁੱਖ_VEC_ELT (op1, 2), ਝੂਠ, ਨਿਰਾ);
		}
	    }

	  ਜੇ (cclauses != ਨਿਰਾ
	      && cclauses[C_OMP_CLAUSE_ਵੰਡੋ_PARALLEL] != ਨਿਰਾ)
	    {
	      ਰੁੱਖ *c;
	      ਲਈ (c = &cclauses[C_OMP_CLAUSE_ਵੰਡੋ_PARALLEL]; *c ; )
		ਜੇ (OMP_CLAUSE_ਕੋਡ (*c) != OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_ਕੋਡ (*c) != OMP_CLAUSE_LASTPRIVATE)
		  c = &OMP_CLAUSE_CHAIN (*c);
		ਨਹੀਂਤਾਂ
		  {
		    ਲਈ (i = 0; i < ਗਿਣਤੀ_2; i++)
		      ਜੇ (ਰੁੱਖ_VEC_ELT (ਅੰਕੜੇ.declv, i) == OMP_CLAUSE_DECL (*c))
			ਰੋਕੋ;
		    ਜੇ (i == ਗਿਣਤੀ_2)
		      c = &OMP_CLAUSE_CHAIN (*c);
		    ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (*c) == OMP_CLAUSE_FIRSTPRIVATE)
		      {
			error_at (loc,
				  "iteration variable %qD should not be firstprivate",
				  OMP_CLAUSE_DECL (*c));
			*c = OMP_CLAUSE_CHAIN (*c);
		      }
		    ਨਹੀਂਤਾਂ
		      {
			/* Move lastprivate (decl) clause to
			   OMP_FOR_CLAUSES.  */
			ਰੁੱਖ l = *c;
			*c = OMP_CLAUSE_CHAIN (*c);
			ਜੇ (ਕੋਡ == OMP_SIMD)
			  {
			    OMP_CLAUSE_CHAIN (l)
			      = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_FOR];
			    cclauses[C_OMP_CLAUSE_ਵੰਡੋ_FOR] = l;
			  }
			ਨਹੀਂਤਾਂ
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

  parser->omp_for_parse_state = save_ਅੰਕੜੇ;
  ਵਾਪਸ ret;
}

/* Helper function for OpenMP parsing, split clauses and call
   finish_omp_clauses on each of the set of clauses afterwards.  */

ਸਥਿਰ ਖਾਲੀ
omp_ਵੰਡੋ_clauses (location_t loc, ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ,
		   omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ clauses, ਰੁੱਖ *cclauses)
{
  ਪੂਰਨ i;
  c_omp_ਵੰਡੋ_clauses (loc, ਕੋਡ, ਨਕਾਬ, clauses, cclauses);
  ਲਈ (i = 0; i < C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ; i++)
    ਜੇ (cclauses[i])
      cclauses[i] = c_ਅੰਤ_omp_clauses (cclauses[i],
					  i == C_OMP_CLAUSE_ਵੰਡੋ_ਨਿਸ਼ਾਨਾ
					  ? C_ORT_OMP_ਨਿਸ਼ਾਨਾ : C_ORT_OMP);
}

/* OpenMP 5.0:
   #pragma omp loop loop-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_LOOP_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_BIND)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਕ੍ਰਮ))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_loop (location_t loc, c_parser *parser,
		   ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
		   ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ ਖੰਡ, clauses, ret;

  strcat (p_name, " loop");
  ਨਕਾਬ |= OMP_LOOP_CLAUSE_ਨਕਾਬ;

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_LOOP, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_LOOP];
    }

  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_LOOP, clauses, cclauses, if_p);
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ ret;
}

/* OpenMP 4.0:
   #pragma omp simd simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_SIMD_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SAFELEN)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਰੇਖਿਕ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NONTEMPORAL)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਕ੍ਰਮ))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_simd (location_t loc, c_parser *parser,
		   ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
		   ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ ਖੰਡ, clauses, ret;

  strcat (p_name, " simd");
  ਨਕਾਬ |= OMP_SIMD_CLAUSE_ਨਕਾਬ;

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_SIMD, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_SIMD];
    }

  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_SIMD, clauses, cclauses, if_p);
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ ret;
}

/* OpenMP 2.5:
   #pragma omp for for-clause[optseq] new-line
     for-loop

   OpenMP 4.0:
   #pragma omp for simd for-simd-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_FOR_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਰੇਖਿਕ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ORDERED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਸਮਾਂ_ਸਾਰਣੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਕ੍ਰਮ))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_for (location_t loc, c_parser *parser,
		  ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
		  ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ ਖੰਡ, clauses, ret;

  strcat (p_name, " for");
  ਨਕਾਬ |= OMP_FOR_CLAUSE_ਨਕਾਬ;
  /* parallel for{, simd} disallows nowait clause, but for
     target {teams distribute ,}parallel for{, simd} it should be accepted.  */
  ਜੇ (cclauses && (ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_MAP)) == 0)
    ਨਕਾਬ &= ~(OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT);
  /* Composite distribute parallel for{, simd} disallows ordered clause.  */
  ਜੇ ((ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ)) != 0)
    ਨਕਾਬ &= ~(OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ORDERED);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      ਜੇ (strcmp (p, "simd") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਜੇ (cclauses == ਨਿਰਾ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_simd (loc, parser, p_name, ਨਕਾਬ, cclauses,
				      if_p);
	  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
	  ret = c_parser_omp_simd (loc, parser, p_name, ਨਕਾਬ, cclauses, if_p);
	  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
	  ਜੇ (ret == NULL_ਰੁੱਖ)
	    ਵਾਪਸ ret;
	  ret = make_ਗੰਢ (OMP_FOR);
	  ਰੁੱਖ_TYPE (ret) = void_type_ਗੰਢ;
	  OMP_FOR_BODY (ret) = ਖੰਡ;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_FOR];
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret, loc);
	  ਜੋੜੋ_stmt (ret);
	  ਵਾਪਸ ret;
	}
    }
  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  /* Composite distribute parallel for disallows linear clause.  */
  ਜੇ ((ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ)) != 0)
    ਨਕਾਬ &= ~(OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਰੇਖਿਕ);

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_FOR, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_FOR];
    }

  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_FOR, clauses, cclauses, if_p);
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ ret;
}

ਸਥਿਰ ਰੁੱਖ c_parser_omp_taskloop (location_t, c_parser *, ਅੱਖਰ *,
				   omp_clause_ਨਕਾਬ, ਰੁੱਖ *, ਤਾਰਕਿਕ *);

/* OpenMP 2.5:
   # pragma omp master new-line
     structured-block

   LOC is the location of the #pragma token.
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_master (location_t loc, c_parser *parser,
		     ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
		     ਤਾਰਕਿਕ *if_p, location_t master_loc)
{
  ਰੁੱਖ ਖੰਡ, clauses, ret;
  gcc_rich_location richloc (loc);
  ਜੇ (master_loc != UNKNOWN_LOCATION)
    richloc.ਜੋੜੋ_fixit_replace (master_loc, "masked");
  warning_at (&richloc, OPT_Wdeprecated_openmp,
	      "%<master%> construct deprecated since OpenMP 5.1, use "
	      "%<masked%>");

  strcat (p_name, " master");

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      ਜੇ (strcmp (p, "taskloop") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਜੇ (cclauses == ਨਿਰਾ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_taskloop (loc, parser, p_name, ਨਕਾਬ, cclauses,
					  if_p);
	  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, ਨਕਾਬ, cclauses,
				       if_p);
	  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
	  ਜੇ (ret == NULL_ਰੁੱਖ)
	    ਵਾਪਸ ret;
	  ret = c_ਅੰਤ_omp_master (loc, ਖੰਡ);
	  OMP_MASTER_COMBINED (ret) = 1;
	  ਵਾਪਸ ret;
	}
    }
  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  ਜੇ (cclauses)
    {
      clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, ਝੂਠ);
      omp_ਵੰਡੋ_clauses (loc, OMP_MASTER, ਨਕਾਬ, clauses, cclauses);
    }
  ਨਹੀਂਤਾਂ
    c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  ਵਾਪਸ c_ਅੰਤ_omp_master (loc, c_parser_omp_structured_ਖੰਡ (parser,
								  if_p));
}

/* OpenMP 5.1:
   # pragma omp masked masked-clauses new-line
     structured-block

   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_MASKED_CLAUSE_ਨਕਾਬ					\
	(OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FILTER)

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_masked (location_t loc, c_parser *parser,
		     ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
		     ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ ਖੰਡ, clauses, ret;

  strcat (p_name, " masked");
  ਨਕਾਬ |= OMP_MASKED_CLAUSE_ਨਕਾਬ;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      ਜੇ (strcmp (p, "taskloop") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਜੇ (cclauses == ਨਿਰਾ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_taskloop (loc, parser, p_name, ਨਕਾਬ, cclauses,
					  if_p);
	  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
	  ret = c_parser_omp_taskloop (loc, parser, p_name, ਨਕਾਬ, cclauses,
				       if_p);
	  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
	  ਜੇ (ret == NULL_ਰੁੱਖ)
	    ਵਾਪਸ ret;
	  ret = c_ਅੰਤ_omp_masked (loc, ਖੰਡ,
				     cclauses[C_OMP_CLAUSE_ਵੰਡੋ_MASKED]);
	  OMP_MASKED_COMBINED (ret) = 1;
	  ਵਾਪਸ ret;
	}
    }
  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_MASKED, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_MASKED];
    }

  ਵਾਪਸ c_ਅੰਤ_omp_masked (loc, c_parser_omp_structured_ਖੰਡ (parser,
								  if_p),
			      clauses);
}

/* OpenMP 5.1:
   # pragma omp interop clauses[opt] new-line */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_INTEROP_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DESTROY)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_INIT)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_USE))

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_interop (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ਰੁੱਖ clauses = c_parser_omp_all_clauses (parser,
					   OMP_INTEROP_CLAUSE_ਨਕਾਬ,
					   "#pragma omp interop");
  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_INTEROP);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_INTEROP_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_ORDERED_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਧਾਗੇ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SIMD))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_ORDERED_DEPEND_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DOACROSS))

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_ordered (c_parser *parser, ਗਿਣਤੀ pragma_context context,
		      ਤਾਰਕਿਕ *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  ਜੇ (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ ਝੂਠ;
    }

  ਪੂਰਨ n = 1;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    n = 2;

  ਜੇ (c_parser_peek_nth_token (parser, n)->type == CPP_NAME)
    {
      ਅਚਲ ਅੱਖਰ *p
	= IDENTIFIER_ਸੂਚਕ (c_parser_peek_nth_token (parser, n)->ਮੁੱਲ);

      ਜੇ (!strcmp ("depend", p) || !strcmp ("doacross", p))
	{
	  ਜੇ (!flag_openmp)	/* flag_openmp_simd  */
	    {
	      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	      ਵਾਪਸ ਝੂਠ;
	    }
	  ਜੇ (context == pragma_stmt)
	    {
	      error_at (loc,
			"%<#pragma omp ordered%> with %qs clause may "
			"only be used in compound statements", p);
	      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	      ਵਾਪਸ ਸੱਚ;
	    }

	  ਰੁੱਖ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_ORDERED_DEPEND_CLAUSE_ਨਕਾਬ,
					"#pragma omp ordered");
	  c_ਅੰਤ_omp_ordered (loc, clauses, NULL_ਰੁੱਖ);
	  ਵਾਪਸ ਝੂਠ;
	}
    }

  ਰੁੱਖ clauses = c_parser_omp_all_clauses (parser, OMP_ORDERED_CLAUSE_ਨਕਾਬ,
					   "#pragma omp ordered");

  ਜੇ (!flag_openmp	/* flag_openmp_simd  */
      && omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_SIMD) == NULL_ਰੁੱਖ)
    ਵਾਪਸ ਝੂਠ;

  c_ਅੰਤ_omp_ordered (loc, clauses,
			c_parser_omp_structured_ਖੰਡ (parser, if_p));
  ਵਾਪਸ ਸੱਚ;
}

/* OpenMP 2.5:

   section-scope:
     { section-sequence }

   section-sequence:
     section-directive[opt] structured-block
     section-sequence section-directive structured-block

   OpenMP 5.1 allows structured-block-sequence instead of structured-block.

    SECTIONS_LOC is the location of the #pragma omp sections.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_sections_scope (location_t sections_loc, c_parser *parser)
{
  ਰੁੱਖ stmt, substmt;
  ਤਾਰਕਿਕ error_suppress = ਝੂਠ;
  location_t loc;

  loc = c_parser_peek_token (parser)->location;
  ਜੇ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      /* Avoid skipping until the end of the block.  */
      parser->error = ਝੂਠ;
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  stmt = ਧੱਕੋ_stmt_list ();

  ਜੇ (c_parser_peek_token (parser)->pragma_ਕਿਸਮ != PRAGMA_OMP_SECTION
      && !c_parser_omp_section_ਜਾਂਚ (parser, "section", ਸੱਚ))
    {
      substmt = c_parser_omp_structured_ਖੰਡ_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ਗੰਢ, substmt);
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (substmt, loc);
      ਜੋੜੋ_stmt (substmt);
    }

  ਜਦੋਂ (1)
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
	ਰੋਕੋ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EOF))
	ਰੋਕੋ;

      loc = c_parser_peek_token (parser)->location;
      c_parser_omp_section_ਜਾਂਚ (parser, "section", ਝੂਠ);
      ਜੇ (c_parser_peek_token (parser)->pragma_ਕਿਸਮ == PRAGMA_OMP_SECTION)
	{
	  c_parser_consume_pragma (parser);
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	  error_suppress = ਝੂਠ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!error_suppress)
	{
	  error_at (loc, "expected %<#pragma omp section%> or %<}%>");
	  error_suppress = ਸੱਚ;
	}

      substmt = c_parser_omp_structured_ਖੰਡ_sequence (parser,
							PRAGMA_OMP_SECTION);
      substmt = build1 (OMP_SECTION, void_type_ਗੰਢ, substmt);
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (substmt, loc);
      ਜੋੜੋ_stmt (substmt);
    }
  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE,
			     "expected %<#pragma omp section%> or %<}%>");

  substmt = ਕੱਢੋ_stmt_list (stmt);

  stmt = make_ਗੰਢ (OMP_SECTIONS);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, sections_loc);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_SECTIONS_BODY (stmt) = substmt;

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* OpenMP 2.5:
   # pragma omp sections sections-clause[optseq] newline
     sections-scope

   LOC is the location of the #pragma token.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_SECTIONS_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_sections (location_t loc, c_parser *parser,
		       ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses)
{
  ਰੁੱਖ ਖੰਡ, clauses, ret;

  strcat (p_name, " sections");
  ਨਕਾਬ |= OMP_SECTIONS_CLAUSE_ਨਕਾਬ;
  ਜੇ (cclauses)
    ਨਕਾਬ &= ~(OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT);

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_SECTIONS, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_SECTIONS];
    }

  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ret = c_parser_omp_sections_scope (loc, parser);
  ਜੇ (ret)
    OMP_SECTIONS_CLAUSES (ret) = clauses;
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ ret;
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_PARALLEL_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_COPYIN)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਅੰਕ_ਧਾਗੇ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_PROC_BIND))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_parallel (location_t loc, c_parser *parser,
		       ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
		       ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ stmt, clauses, ਖੰਡ;

  strcat (p_name, " parallel");
  ਨਕਾਬ |= OMP_PARALLEL_CLAUSE_ਨਕਾਬ;
  /* #pragma omp target parallel{, for, for simd} disallow copyin clause.  */
  ਜੇ ((ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_MAP)) != 0
      && (ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ)) == 0)
    ਨਕਾਬ &= ~(OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_COPYIN);

  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_FOR))
    {
      ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
      ਜੇ (cclauses == ਨਿਰਾ)
	cclauses = cclauses_buf;

      c_parser_consume_token (parser);
      ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	ਵਾਪਸ c_parser_omp_for (loc, parser, p_name, ਨਕਾਬ, cclauses, if_p);
      ਖੰਡ = c_begin_omp_parallel ();
      ਰੁੱਖ ret = c_parser_omp_for (loc, parser, p_name, ਨਕਾਬ, cclauses, if_p);
      stmt
	= c_ਅੰਤ_omp_parallel (loc, cclauses[C_OMP_CLAUSE_ਵੰਡੋ_PARALLEL],
				 ਖੰਡ);
      ਜੇ (ret == NULL_ਰੁੱਖ)
	ਵਾਪਸ ret;
      OMP_PARALLEL_COMBINED (stmt) = 1;
      ਵਾਪਸ stmt;
    }
  /* When combined with distribute, parallel has to be followed by for.
     #pragma omp target parallel is allowed though.  */
  ਨਹੀਂਤਾਂ ਜੇ (cclauses
	   && (ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1
		       << PRAGMA_OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ)) != 0)
    {
      error_at (loc, "expected %<for%> after %qs", p_name);
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      location_t ploc = c_parser_peek_token (parser)->location;
      ਜੇ (cclauses == ਨਿਰਾ && strcmp (p, "masked") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_masked (loc, parser, p_name, ਨਕਾਬ, cclauses,
					if_p);
	  ਖੰਡ = c_begin_omp_parallel ();
	  ਰੁੱਖ ret = c_parser_omp_masked (loc, parser, p_name, ਨਕਾਬ, cclauses,
					  if_p);
	  stmt = c_ਅੰਤ_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_ਵੰਡੋ_PARALLEL],
					ਖੰਡ);
	  ਜੇ (ret == ਨਿਰਾ)
	    ਵਾਪਸ ret;
	  /* masked does have just filter clause, but during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel masked don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel masked
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel masked taskloop simd lastprivate (x)  */
	  ਜੇ (OMP_MASKED_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  ਵਾਪਸ stmt;
	}
      ਨਹੀਂਤਾਂ ਜੇ (cclauses == ਨਿਰਾ && strcmp (p, "master") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_master (loc, parser, p_name, ਨਕਾਬ, cclauses,
					if_p, ploc);
	  ਖੰਡ = c_begin_omp_parallel ();
	  ਰੁੱਖ ret = c_parser_omp_master (loc, parser, p_name, ਨਕਾਬ, cclauses,
					  if_p, ploc);
	  stmt = c_ਅੰਤ_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_ਵੰਡੋ_PARALLEL],
					ਖੰਡ);
	  ਜੇ (ret == ਨਿਰਾ)
	    ਵਾਪਸ ret;
	  /* master doesn't have any clauses and during gimplification
	     isn't represented by a gimplification omp context, so for
	     #pragma omp parallel master don't set OMP_PARALLEL_COMBINED,
	     so that
	     #pragma omp parallel master
	     #pragma omp taskloop simd lastprivate (x)
	     isn't confused with
	     #pragma omp parallel master taskloop simd lastprivate (x)  */
	  ਜੇ (OMP_MASTER_COMBINED (ret))
	    OMP_PARALLEL_COMBINED (stmt) = 1;
	  ਵਾਪਸ stmt;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "loop") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਜੇ (cclauses == ਨਿਰਾ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_loop (loc, parser, p_name, ਨਕਾਬ, cclauses,
				      if_p);
	  ਖੰਡ = c_begin_omp_parallel ();
	  ਰੁੱਖ ret = c_parser_omp_loop (loc, parser, p_name, ਨਕਾਬ, cclauses,
					if_p);
	  stmt
	    = c_ਅੰਤ_omp_parallel (loc,
				     cclauses[C_OMP_CLAUSE_ਵੰਡੋ_PARALLEL],
				     ਖੰਡ);
	  ਜੇ (ret == NULL_ਰੁੱਖ)
	    ਵਾਪਸ ret;
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  ਵਾਪਸ stmt;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਵਾਪਸ NULL_ਰੁੱਖ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (cclauses == ਨਿਰਾ && strcmp (p, "sections") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਖੰਡ = c_begin_omp_parallel ();
	  c_parser_omp_sections (loc, parser, p_name, ਨਕਾਬ, cclauses);
	  stmt = c_ਅੰਤ_omp_parallel (loc,
					cclauses[C_OMP_CLAUSE_ਵੰਡੋ_PARALLEL],
					ਖੰਡ);
	  OMP_PARALLEL_COMBINED (stmt) = 1;
	  ਵਾਪਸ stmt;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_PARALLEL, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_PARALLEL];
    }

  ਖੰਡ = c_begin_omp_parallel ();
  parser->omp_attrs_forbidden_p = ਸੱਚ;
  c_parser_statement (parser, if_p);
  stmt = c_ਅੰਤ_omp_parallel (loc, clauses, ਖੰਡ);

  ਵਾਪਸ stmt;
}

/* OpenMP 2.5:
   # pragma omp single single-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_SINGLE_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_COPYPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_single (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_SINGLE);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;

  OMP_SINGLE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SINGLE_CLAUSE_ਨਕਾਬ,
				"#pragma omp single");
  OMP_SINGLE_BODY (stmt) = c_parser_omp_structured_ਖੰਡ (parser, if_p);

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* OpenMP 5.1:
   # pragma omp scope scope-clause[optseq] new-line
     structured-block

   LOC is the location of the #pragma.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_SCOPE_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_scope (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_SCOPE);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;

  OMP_SCOPE_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_SCOPE_CLAUSE_ਨਕਾਬ,
				"#pragma omp scope");
  OMP_SCOPE_BODY (stmt) = c_parser_omp_structured_ਖੰਡ (parser, if_p);

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* Parse a function dispatch structured block:

    lvalue-expression = target-call ( [expression-list] );
    or
    target-call ( [expression-list] );

   Adapted from c_parser_expr_no_commas and c_parser_postfix_expression
   (CPP_NAME/C_ID_ID) for the function name.
*/
ਸਥਿਰ ਰੁੱਖ
c_parser_omp_dispatch_body (c_parser *parser)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ lhs, rhs, ret;
  location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
  ਸਰੋਤ_range tok_range = c_parser_peek_token (parser)->get_range ();

  lhs = c_parser_conditional_ਵਿਅੰਜਕ (parser, ਨਿਰਾ, ਨਿਰਾ);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (lhs.ਮੁੱਲ) == CALL_ਵਿਅੰਜਕ)
    ਵਾਪਸ lhs.ਮੁੱਲ;

  location_t op_location = c_parser_peek_token (parser)->location;
  ਜੇ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ਵਾਪਸ error_mark_ਗੰਢ;

  /* Parse function name.  */
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected a function name");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
  c_parser_consume_token (parser);
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_error (parser, "expected a function name");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  rhs.ਮੁੱਲ = build_external_ref (ਵਿਅੰਜਕ_loc, id, ਸੱਚ, &rhs.original_type);
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&rhs, tok_range);

  /* Parse argument list.  */
  rhs = c_parser_postfix_ਵਿਅੰਜਕ_after_primary (
    parser, ਵਿਅੰਜਕ_LOC_OR_LOC (rhs.ਮੁੱਲ, ਵਿਅੰਜਕ_loc), rhs);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (rhs.ਮੁੱਲ) != CALL_ਵਿਅੰਜਕ)
    {
      error_at (ਵਿਅੰਜਕ_LOC_OR_LOC (rhs.ਮੁੱਲ, ਵਿਅੰਜਕ_loc),
		"expected target-function call");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  /* Build assignment. */
  rhs = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, rhs, ਸੱਚ, ਸੱਚ);
  ret.ਮੁੱਲ
    = build_modify_ਵਿਅੰਜਕ (op_location, lhs.ਮੁੱਲ, lhs.original_type, NOP_ਵਿਅੰਜਕ,
			 ਵਿਅੰਜਕ_loc, rhs.ਮੁੱਲ, rhs.original_type);
  ret.m_decimal = 0;
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, lhs.get_ਸ਼ੁਰੂ (), rhs.get_ਅੰਤ ());
  ret.original_ਕੋਡ = MODIFY_ਵਿਅੰਜਕ;
  ret.original_type = ਨਿਰਾ;
  ਵਾਪਸ ret.ਮੁੱਲ;
}

/* OpenMP 5.1:
   # pragma omp dispatch dispatch-clause[optseq] new-line
     expression-stmt

   LOC is the location of the #pragma.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_DISPATCH_CLAUSE_ਨਕਾਬ                                               \
  ((OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE)                             \
   | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)                           \
   | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOVARIANTS)                       \
   | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOCONTEXT)                        \
   | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR)                  \
   | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_INTEROP)                          \
   | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)                    \
   | (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_dispatch (location_t loc, c_parser *parser)
{
  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_DISPATCH);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;

  OMP_DISPATCH_CLAUSES (stmt)
    = c_parser_omp_all_clauses (parser, OMP_DISPATCH_CLAUSE_ਨਕਾਬ,
				"#pragma omp dispatch");

  // Extract depend clauses and create taskwait
  ਰੁੱਖ depend_clauses = NULL_ਰੁੱਖ;
  ਰੁੱਖ *depend_clauses_ptr = &depend_clauses;
  ਲਈ (ਰੁੱਖ c = OMP_DISPATCH_CLAUSES (stmt); c; c = OMP_CLAUSE_CHAIN (c))
    {
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEPEND)
	{
	  *depend_clauses_ptr = c;
	  depend_clauses_ptr = &OMP_CLAUSE_CHAIN (c);
	}
    }
  ਜੇ (depend_clauses != NULL_ਰੁੱਖ)
    {
      ਰੁੱਖ stmt = make_ਗੰਢ (OMP_TASK);
      ਰੁੱਖ_TYPE (stmt) = void_ਗੰਢ;
      OMP_TASK_CLAUSES (stmt) = depend_clauses;
      OMP_TASK_BODY (stmt) = NULL_ਰੁੱਖ;
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
      ਜੋੜੋ_stmt (stmt);
    }

  // Parse body as expression statement
  loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ dispatch_body = c_parser_omp_dispatch_body (parser);
  ਜੇ (dispatch_body == error_mark_ਗੰਢ)
    {
      inform (loc, "%<#pragma omp dispatch%> must be followed by a function "
		   "call with optional assignment");
      c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  // Walk the tree to find the dispatch function call and wrap it into an IFN
  gcc_assert (ਰੁੱਖ_ਕੋਡ (dispatch_body) == CALL_ਵਿਅੰਜਕ
	      || ਰੁੱਖ_ਕੋਡ (dispatch_body) == MODIFY_ਵਿਅੰਜਕ);
  ਰੁੱਖ *dispatch_call = ਰੁੱਖ_ਕੋਡ (dispatch_body) == MODIFY_ਵਿਅੰਜਕ
			  ? &ਰੁੱਖ_ਸੰਕਾਰਜ (dispatch_body, 1)
			  : &dispatch_body;
  ਜਦੋਂ (ਰੁੱਖ_ਕੋਡ (*dispatch_call) == FLOAT_ਵਿਅੰਜਕ
	 || ਰੁੱਖ_ਕੋਡ (*dispatch_call) == CONVERT_ਵਿਅੰਜਕ
	 || ਰੁੱਖ_ਕੋਡ (*dispatch_call) == NOP_ਵਿਅੰਜਕ)
    dispatch_call = &ਰੁੱਖ_ਸੰਕਾਰਜ (*dispatch_call, 0);
  *dispatch_call = build_call_ਵਿਅੰਜਕ_ਅੰਦਰੂਨੀ_loc (
    loc, IFN_GOMP_DISPATCH,
    ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (CALL_ਵਿਅੰਜਕ_FN (*dispatch_call))), 1, *dispatch_call);

  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, "expected %<;%>");
  OMP_DISPATCH_BODY (stmt) = dispatch_body;

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* OpenMP 3.0:
   # pragma omp task task-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_TASK_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਤਰਜੀਹ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਵਿੱਚ_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DETACH)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_AFFINITY))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_task (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ clauses, ਖੰਡ;

  clauses = c_parser_omp_all_clauses (parser, OMP_TASK_CLAUSE_ਨਕਾਬ,
				      "#pragma omp task");

  ਖੰਡ = c_begin_omp_task ();
  parser->omp_attrs_forbidden_p = ਸੱਚ;
  c_parser_statement (parser, if_p);
  ਵਾਪਸ c_ਅੰਤ_omp_task (loc, clauses, ਖੰਡ);
}

/* OpenMP 3.0:
   # pragma omp taskwait new-line

   OpenMP 5.0:
   # pragma omp taskwait taskwait-clause[optseq] new-line
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_TASKWAIT_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_taskwait (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);

  ਰੁੱਖ clauses
    = c_parser_omp_all_clauses (parser, OMP_TASKWAIT_CLAUSE_ਨਕਾਬ,
				"#pragma omp taskwait");

  ਜੇ (clauses)
    {
      ਰੁੱਖ stmt = make_ਗੰਢ (OMP_TASK);
      ਰੁੱਖ_TYPE (stmt) = void_ਗੰਢ;
      OMP_TASK_CLAUSES (stmt) = clauses;
      OMP_TASK_BODY (stmt) = NULL_ਰੁੱਖ;
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
      ਜੋੜੋ_stmt (stmt);
    }
  ਨਹੀਂਤਾਂ
    c_ਅੰਤ_omp_taskwait (loc);
}

/* OpenMP 3.1:
   # pragma omp taskyield new-line
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_taskyield (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  c_ਅੰਤ_omp_taskyield (loc);
}

/* OpenMP 4.0:
   # pragma omp taskgroup new-line

   OpenMP 5.0:
   # pragma omp taskgroup taskgroup-clause[optseq] new-line
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_TASKGROUP_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_TASK_REDUCTION))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_taskgroup (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ clauses = c_parser_omp_all_clauses (parser, OMP_TASKGROUP_CLAUSE_ਨਕਾਬ,
					   "#pragma omp taskgroup");

  ਰੁੱਖ body = c_parser_omp_structured_ਖੰਡ (parser, if_p);
  ਵਾਪਸ c_ਅੰਤ_omp_taskgroup (loc, body, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancel cancel-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_CANCEL_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_TASKGROUP)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF))

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);
  ਰੁੱਖ clauses = c_parser_omp_all_clauses (parser, OMP_CANCEL_CLAUSE_ਨਕਾਬ,
					   "#pragma omp cancel");

  c_ਅੰਤ_omp_cancel (loc, clauses);
}

/* OpenMP 4.0:
   # pragma omp cancellation point cancelpt-clause[optseq] new-line

   LOC is the location of the #pragma.
*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_CANCELLATION_ਬਿੰਦੂ_CLAUSE_ਨਕਾਬ			\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_PARALLEL)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FOR)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SECTIONS)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_TASKGROUP))

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_cancellation_ਬਿੰਦੂ (c_parser *parser, ਗਿਣਤੀ pragma_context context)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ clauses;
  ਤਾਰਕਿਕ ਬਿੰਦੂ_ਵੇਖਿਆ = ਝੂਠ;

  c_parser_consume_pragma (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "point") == 0)
	{
	  c_parser_consume_token (parser);
	  ਬਿੰਦੂ_ਵੇਖਿਆ = ਸੱਚ;
	}
    }
  ਜੇ (!ਬਿੰਦੂ_ਵੇਖਿਆ)
    {
      c_parser_error (parser, "expected %<point%>");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਵਾਪਸ ਝੂਠ;
    }

  ਜੇ (context != pragma_compound)
    {
      ਜੇ (context == pragma_stmt)
	error_at (loc,
		  "%<#pragma %s%> may only be used in compound statements",
		  "omp cancellation point");
      ਨਹੀਂਤਾਂ
	c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ ਸੱਚ;
    }

  clauses
    = c_parser_omp_all_clauses (parser, OMP_CANCELLATION_ਬਿੰਦੂ_CLAUSE_ਨਕਾਬ,
				"#pragma omp cancellation point");

  c_ਅੰਤ_omp_cancellation_ਬਿੰਦੂ (loc, clauses);
  ਵਾਪਸ ਸੱਚ;
}

/* OpenMP 4.0:
   #pragma omp distribute distribute-clause[optseq] new-line
     for-loop  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_DISTRIBUTE_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DIST_ਸਮਾਂ_ਸਾਰਣੀ)\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਕ੍ਰਮ))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_distribute (location_t loc, c_parser *parser,
			 ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
			 ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ clauses, ਖੰਡ, ret;

  strcat (p_name, " distribute");
  ਨਕਾਬ |= OMP_DISTRIBUTE_CLAUSE_ਨਕਾਬ;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਤਾਰਕਿਕ simd = ਝੂਠ;
      ਤਾਰਕਿਕ parallel = ਝੂਠ;

      ਜੇ (strcmp (p, "simd") == 0)
	simd = ਸੱਚ;
      ਨਹੀਂਤਾਂ
	parallel = strcmp (p, "parallel") == 0;
      ਜੇ (parallel || simd)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਜੇ (cclauses == ਨਿਰਾ)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      ਜੇ (simd)
		ਵਾਪਸ c_parser_omp_simd (loc, parser, p_name, ਨਕਾਬ, cclauses,
					  if_p);
	      ਨਹੀਂਤਾਂ
		ਵਾਪਸ c_parser_omp_parallel (loc, parser, p_name, ਨਕਾਬ,
					      cclauses, if_p);
	    }
	  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
	  ਜੇ (simd)
	    ret = c_parser_omp_simd (loc, parser, p_name, ਨਕਾਬ, cclauses,
				     if_p);
	  ਨਹੀਂਤਾਂ
	    ret = c_parser_omp_parallel (loc, parser, p_name, ਨਕਾਬ, cclauses,
					 if_p);
	  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
	  ਜੇ (ret == ਨਿਰਾ)
	    ਵਾਪਸ ret;
	  ret = make_ਗੰਢ (OMP_DISTRIBUTE);
	  ਰੁੱਖ_TYPE (ret) = void_type_ਗੰਢ;
	  OMP_FOR_BODY (ret) = ਖੰਡ;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_DISTRIBUTE];
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret, loc);
	  ਜੋੜੋ_stmt (ret);
	  ਵਾਪਸ ret;
	}
    }
  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_DISTRIBUTE, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_DISTRIBUTE];
    }

  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_DISTRIBUTE, clauses, ਨਿਰਾ,
			       if_p);
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ ret;
}

/* OpenMP 4.0:
   # pragma omp teams teams-clause[optseq] new-line
     structured-block  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_TEAMS_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਅੰਕ_TEAMS)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEFAULT))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_teams (location_t loc, c_parser *parser,
		    ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
		    ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ clauses, ਖੰਡ, ret;

  strcat (p_name, " teams");
  ਨਕਾਬ |= OMP_TEAMS_CLAUSE_ਨਕਾਬ;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "distribute") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਜੇ (cclauses == ਨਿਰਾ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_distribute (loc, parser, p_name, ਨਕਾਬ,
					    cclauses, if_p);
	  ਖੰਡ = c_begin_omp_parallel ();
	  ret = c_parser_omp_distribute (loc, parser, p_name, ਨਕਾਬ, cclauses,
					 if_p);
	  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
	  ਜੇ (ret == ਨਿਰਾ)
	    ਵਾਪਸ ret;
	  clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_TEAMS];
	  ret = make_ਗੰਢ (OMP_TEAMS);
	  ਰੁੱਖ_TYPE (ret) = void_type_ਗੰਢ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = ਖੰਡ;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret, loc);
	  ਵਾਪਸ ਜੋੜੋ_stmt (ret);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "loop") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਜੇ (cclauses == ਨਿਰਾ)
	    cclauses = cclauses_buf;

	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_loop (loc, parser, p_name, ਨਕਾਬ, cclauses,
				      if_p);
	  ਖੰਡ = c_begin_omp_parallel ();
	  ret = c_parser_omp_loop (loc, parser, p_name, ਨਕਾਬ, cclauses, if_p);
	  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
	  ਜੇ (ret == ਨਿਰਾ)
	    ਵਾਪਸ ret;
	  clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_TEAMS];
	  ret = make_ਗੰਢ (OMP_TEAMS);
	  ਰੁੱਖ_TYPE (ret) = void_type_ਗੰਢ;
	  OMP_TEAMS_CLAUSES (ret) = clauses;
	  OMP_TEAMS_BODY (ret) = ਖੰਡ;
	  OMP_TEAMS_COMBINED (ret) = 1;
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret, loc);
	  ਵਾਪਸ ਜੋੜੋ_stmt (ret);
	}
    }
  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_TEAMS, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_TEAMS];
    }

  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_TEAMS);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_TEAMS_CLAUSES (stmt) = clauses;
  ਖੰਡ = c_begin_omp_parallel ();
  ਜੋੜੋ_stmt (c_parser_omp_structured_ਖੰਡ (parser, if_p));
  OMP_TEAMS_BODY (stmt) = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);

  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target data target-data-clause[optseq] new-line
     structured-block  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_PTR) \
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_USE_DEVICE_ADDR))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਜੇ (flag_openmp)
    omp_requires_ਨਕਾਬ
      = (ਗਿਣਤੀ omp_requires) (omp_requires_ਨਕਾਬ | OMP_REQUIRES_ਨਿਸ਼ਾਨਾ_ਵਰਤਿਆ);

  ਰੁੱਖ clauses
    = c_parser_omp_all_clauses (parser, OMP_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ,
				"#pragma omp target data", ਝੂਠ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, ਝੂਠ);
  ਪੂਰਨ map_ਵੇਖਿਆ = 0;
  ਲਈ (ਰੁੱਖ *pc = &clauses; *pc;)
    {
      ਜੇ (OMP_CLAUSE_ਕੋਡ (*pc) == OMP_CLAUSE_MAP)
	ਚੋਣ (OMP_CLAUSE_MAP_ਕਿਸਮ (*pc))
	  {
	  ਹਾਲਤ GOMP_MAP_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_PRESENT_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_FROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_FROM:
	  ਹਾਲਤ GOMP_MAP_PRESENT_FROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ਹਾਲਤ GOMP_MAP_TOFROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_TOFROM:
	  ਹਾਲਤ GOMP_MAP_PRESENT_TOFROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  ਹਾਲਤ GOMP_MAP_ALLOC:
	  ਹਾਲਤ GOMP_MAP_PRESENT_ALLOC:
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ATTACH_DETACH:
	  ਹਾਲਤ GOMP_MAP_ATTACH:
	    ਰੋਕੋ;
	  ਮੂਲ:
	    map_ਵੇਖਿਆ |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target data%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ਜਾਰੀ;
	  }
      ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (*pc) == OMP_CLAUSE_USE_DEVICE_PTR
	       || OMP_CLAUSE_ਕੋਡ (*pc) == OMP_CLAUSE_USE_DEVICE_ADDR)
	map_ਵੇਖਿਆ = 3;
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ਜੇ (map_ਵੇਖਿਆ != 3)
    {
      ਜੇ (map_ਵੇਖਿਆ == 0)
	error_at (loc,
		  "%<#pragma omp target data%> must contain at least "
		  "one %<map%>, %<use_device_ptr%> or %<use_device_addr%> "
		  "clause");
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ_CLAUSES (stmt) = clauses;
  keep_ਅਗਲਾ_level ();
  ਰੁੱਖ ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ਜੋੜੋ_stmt (c_parser_omp_structured_ਖੰਡ (parser, if_p));
  OMP_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ_BODY (stmt) = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);

  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਵਾਪਸ ਜੋੜੋ_stmt (stmt);
}

/* OpenMP 4.0:
   # pragma omp target update target-update-clause[optseq] new-line */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_ਨਿਸ਼ਾਨਾ_UPDATE_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FROM)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਮੰਜ਼ਿਲ)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_ਨਿਸ਼ਾਨਾ_update (location_t loc, c_parser *parser,
			    ਗਿਣਤੀ pragma_context context)
{
  ਜੇ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target update");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ ਸੱਚ;
    }

  ਰੁੱਖ clauses
    = c_parser_omp_all_clauses (parser, OMP_ਨਿਸ਼ਾਨਾ_UPDATE_CLAUSE_ਨਕਾਬ,
				"#pragma omp target update",
				/* finish_p = */ ਝੂਠ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_UPDATE);
  clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP_UPDATE);

  ਜੇ (omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_ਮੰਜ਼ਿਲ) == NULL_ਰੁੱਖ
      && omp_ਲੱਭੋ_clause (clauses, OMP_CLAUSE_FROM) == NULL_ਰੁੱਖ)
    {
      error_at (loc,
		"%<#pragma omp target update%> must contain at least one "
		"%<from%> or %<to%> clauses");
      ਵਾਪਸ ਝੂਠ;
    }

  ਜੇ (flag_openmp)
    omp_requires_ਨਕਾਬ
      = (ਗਿਣਤੀ omp_requires) (omp_requires_ਨਕਾਬ | OMP_REQUIRES_ਨਿਸ਼ਾਨਾ_ਵਰਤਿਆ);

  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_ਨਿਸ਼ਾਨਾ_UPDATE);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_ਨਿਸ਼ਾਨਾ_UPDATE_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);
  ਵਾਪਸ ਝੂਠ;
}

/* OpenMP 4.5:
   # pragma omp target enter data target-data-clause[optseq] new-line  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_ਨਿਸ਼ਾਨਾ_ENTER_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ			\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_ਨਿਸ਼ਾਨਾ_enter_ਅੰਕੜੇ (location_t loc, c_parser *parser,
				ਗਿਣਤੀ pragma_context context)
{
  ਤਾਰਕਿਕ ਅੰਕੜੇ_ਵੇਖਿਆ = ਝੂਠ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  ਅੰਕੜੇ_ਵੇਖਿਆ = ਸੱਚ;
	}
    }
  ਜੇ (!ਅੰਕੜੇ_ਵੇਖਿਆ)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਵਾਪਸ ਝੂਠ;
    }

  ਜੇ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target enter data");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ ਸੱਚ;
    }

  ਜੇ (flag_openmp)
    omp_requires_ਨਕਾਬ
      = (ਗਿਣਤੀ omp_requires) (omp_requires_ਨਕਾਬ | OMP_REQUIRES_ਨਿਸ਼ਾਨਾ_ਵਰਤਿਆ);

  ਰੁੱਖ clauses
    = c_parser_omp_all_clauses (parser, OMP_ਨਿਸ਼ਾਨਾ_ENTER_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ,
				"#pragma omp target enter data", ਝੂਠ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP);
  clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP);
  c_omp_adjust_map_clauses (clauses, ਝੂਠ);
  ਪੂਰਨ map_ਵੇਖਿਆ = 0;
  ਲਈ (ਰੁੱਖ *pc = &clauses; *pc;)
    {
      ਜੇ (OMP_CLAUSE_ਕੋਡ (*pc) == OMP_CLAUSE_MAP)
	ਚੋਣ (OMP_CLAUSE_MAP_ਕਿਸਮ (*pc))
	  {
	  ਹਾਲਤ GOMP_MAP_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_PRESENT_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_ALLOC:
	  ਹਾਲਤ GOMP_MAP_PRESENT_ALLOC:
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_TOFROM:
	    OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (*pc, GOMP_MAP_ਮੰਜ਼ਿਲ);
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (*pc, GOMP_MAP_ALWAYS_ਮੰਜ਼ਿਲ);
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (*pc, GOMP_MAP_PRESENT_ਮੰਜ਼ਿਲ);
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (*pc, GOMP_MAP_ALWAYS_PRESENT_ਮੰਜ਼ਿਲ);
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ATTACH_DETACH:
	  ਹਾਲਤ GOMP_MAP_ATTACH:
	    ਰੋਕੋ;
	  ਮੂਲ:
	    map_ਵੇਖਿਆ |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target enter data%> with map-type other "
		      "than %<to%>, %<tofrom%> or %<alloc%> on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ਜਾਰੀ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ਜੇ (map_ਵੇਖਿਆ != 3)
    {
      ਜੇ (map_ਵੇਖਿਆ == 0)
	error_at (loc,
		  "%<#pragma omp target enter data%> must contain at least "
		  "one %<map%> clause");
      ਵਾਪਸ ਸੱਚ;
    }

  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_ਨਿਸ਼ਾਨਾ_ENTER_ਅੰਕੜੇ);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_ਨਿਸ਼ਾਨਾ_ENTER_ਅੰਕੜੇ_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);
  ਵਾਪਸ ਸੱਚ;
}

/* OpenMP 4.5:
   # pragma omp target exit data target-data-clause[optseq] new-line  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_ਨਿਸ਼ਾਨਾ_EXIT_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ			\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT))

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_ਨਿਸ਼ਾਨਾ_exit_ਅੰਕੜੇ (location_t loc, c_parser *parser,
			       ਗਿਣਤੀ pragma_context context)
{
  ਤਾਰਕਿਕ ਅੰਕੜੇ_ਵੇਖਿਆ = ਝੂਠ;
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  ਅੰਕੜੇ_ਵੇਖਿਆ = ਸੱਚ;
	}
    }
  ਜੇ (!ਅੰਕੜੇ_ਵੇਖਿਆ)
    {
      c_parser_error (parser, "expected %<data%>");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਵਾਪਸ ਝੂਠ;
    }

  ਜੇ (context == pragma_stmt)
    {
      error_at (loc, "%<#pragma %s%> may only be used in compound statements",
		"omp target exit data");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ ਸੱਚ;
    }

  ਜੇ (flag_openmp)
    omp_requires_ਨਕਾਬ
      = (ਗਿਣਤੀ omp_requires) (omp_requires_ਨਕਾਬ | OMP_REQUIRES_ਨਿਸ਼ਾਨਾ_ਵਰਤਿਆ);

  ਰੁੱਖ clauses
    = c_parser_omp_all_clauses (parser, OMP_ਨਿਸ਼ਾਨਾ_EXIT_ਅੰਕੜੇ_CLAUSE_ਨਕਾਬ,
				"#pragma omp target exit data", ਝੂਠ);
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_EXIT_ਅੰਕੜੇ);
  clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP_EXIT_ਅੰਕੜੇ);
  c_omp_adjust_map_clauses (clauses, ਝੂਠ);
  ਪੂਰਨ map_ਵੇਖਿਆ = 0;
  ਲਈ (ਰੁੱਖ *pc = &clauses; *pc;)
    {
      ਜੇ (OMP_CLAUSE_ਕੋਡ (*pc) == OMP_CLAUSE_MAP)
	ਚੋਣ (OMP_CLAUSE_MAP_ਕਿਸਮ (*pc))
	  {
	  ਹਾਲਤ GOMP_MAP_FROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_FROM:
	  ਹਾਲਤ GOMP_MAP_PRESENT_FROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ਹਾਲਤ GOMP_MAP_RELEASE:
	  ਹਾਲਤ GOMP_MAP_DELETE:
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_TOFROM:
	    OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (*pc, GOMP_MAP_FROM);
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_ALWAYS_TOFROM:
	    OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (*pc, GOMP_MAP_ALWAYS_FROM);
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_PRESENT_TOFROM:
	    OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (*pc, GOMP_MAP_PRESENT_FROM);
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	    OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (*pc, GOMP_MAP_ALWAYS_PRESENT_FROM);
	    map_ਵੇਖਿਆ = 3;
	    ਰੋਕੋ;
	  ਹਾਲਤ GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ATTACH_DETACH:
	  ਹਾਲਤ GOMP_MAP_DETACH:
	    ਰੋਕੋ;
	  ਮੂਲ:
	    map_ਵੇਖਿਆ |= 1;
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target exit data%> with map-type other "
		      "than %<from%>, %<tofrom%>, %<release%> or %<delete%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ਜਾਰੀ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }

  ਜੇ (map_ਵੇਖਿਆ != 3)
    {
      ਜੇ (map_ਵੇਖਿਆ == 0)
	error_at (loc,
		  "%<#pragma omp target exit data%> must contain at least one "
		  "%<map%> clause");
      ਵਾਪਸ ਸੱਚ;
    }

  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_ਨਿਸ਼ਾਨਾ_EXIT_ਅੰਕੜੇ);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
  OMP_ਨਿਸ਼ਾਨਾ_EXIT_ਅੰਕੜੇ_CLAUSES (stmt) = clauses;
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);
  ਵਾਪਸ ਸੱਚ;
}

/* OpenMP 4.0:
   # pragma omp target target-clause[optseq] new-line
     structured-block  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEFAULTMAP)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEPEND)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DYN_GROUPPRIVATE) \
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_HAS_DEVICE_ADDR) \
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਵਿੱਚ_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IS_DEVICE_PTR)\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_MAP)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOWAIT)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਵਰਤਦਾ_ALLOCATORS))

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_ਨਿਸ਼ਾਨਾ (c_parser *parser, ਗਿਣਤੀ pragma_context context, ਤਾਰਕਿਕ *if_p)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ਰੁੱਖ *pc = ਨਿਰਾ, stmt, ਖੰਡ, body, clauses;

  ਜੇ (context != pragma_stmt && context != pragma_compound)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਵਾਪਸ ਝੂਠ;
    }

  ਜੇ (flag_openmp)
    omp_requires_ਨਕਾਬ
      = (ਗਿਣਤੀ omp_requires) (omp_requires_ਨਕਾਬ | OMP_REQUIRES_ਨਿਸ਼ਾਨਾ_ਵਰਤਿਆ);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ccode = ERROR_MARK;

      ਜੇ (strcmp (p, "teams") == 0)
	ccode = OMP_TEAMS;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "parallel") == 0)
	ccode = OMP_PARALLEL;
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "simd") == 0)
	ccode = OMP_SIMD;
      ਜੇ (ccode != ERROR_MARK)
	{
	  ਰੁੱਖ cclauses[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਅੱਖਰ p_name[ਆਕਾਰ ("#pragma omp target teams distribute "
			      "parallel for simd")];

	  c_parser_consume_token (parser);
	  strcpy (p_name, "#pragma omp target");
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    {
	      ਰੁੱਖ stmt;
	      ਚੋਣ (ccode)
		{
		ਹਾਲਤ OMP_TEAMS:
		  stmt = c_parser_omp_teams (loc, parser, p_name,
					     OMP_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ,
					     cclauses, if_p);
		  ਰੋਕੋ;
		ਹਾਲਤ OMP_PARALLEL:
		  stmt = c_parser_omp_parallel (loc, parser, p_name,
						OMP_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ,
						cclauses, if_p);
		  ਰੋਕੋ;
		ਹਾਲਤ OMP_SIMD:
		  stmt = c_parser_omp_simd (loc, parser, p_name,
					    OMP_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ,
					    cclauses, if_p);
		  ਰੋਕੋ;
		ਮੂਲ:
		  gcc_unreachable ();
		}
	      ਵਾਪਸ stmt != NULL_ਰੁੱਖ;
	    }
	  keep_ਅਗਲਾ_level ();
	  ਰੁੱਖ ਖੰਡ = c_begin_compound_stmt (ਸੱਚ), ret;
	  ਚੋਣ (ccode)
	    {
	    ਹਾਲਤ OMP_TEAMS:
	      ret = c_parser_omp_teams (loc, parser, p_name,
					OMP_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ, cclauses,
					if_p);
	      ਰੋਕੋ;
	    ਹਾਲਤ OMP_PARALLEL:
	      ret = c_parser_omp_parallel (loc, parser, p_name,
					   OMP_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ, cclauses,
					   if_p);
	      ਰੋਕੋ;
	    ਹਾਲਤ OMP_SIMD:
	      ret = c_parser_omp_simd (loc, parser, p_name,
				       OMP_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ, cclauses,
				       if_p);
	      ਰੋਕੋ;
	    ਮੂਲ:
	      gcc_unreachable ();
	    }
	  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
	  ਜੇ (ret == NULL_ਰੁੱਖ)
	    ਵਾਪਸ ਝੂਠ;
	  ਜੇ (ccode == OMP_TEAMS)
	    /* For combined target teams, ensure the num_teams and
	       thread_limit clause expressions are evaluated on the host,
	       before entering the target construct.  */
	    ਲਈ (ਰੁੱਖ c = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_TEAMS];
		 c; c = OMP_CLAUSE_CHAIN (c))
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਅੰਕ_TEAMS
		  || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_THREAD_ਹੱਦਬੰਦੀ)
		ਲਈ (ਪੂਰਨ i = 0;
		     i <= (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਅੰਕ_TEAMS); ++i)
		  ਜੇ (OMP_CLAUSE_ਸੰਕਾਰਜ (c, i)
		      && ਰੁੱਖ_ਕੋਡ (OMP_CLAUSE_ਸੰਕਾਰਜ (c, i)) != INTEGER_CST)
		    {
		      ਰੁੱਖ ਵਿਅੰਜਕ = OMP_CLAUSE_ਸੰਕਾਰਜ (c, i);
		      ਰੁੱਖ tmp = create_tmp_var_raw (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ));
		      ਵਿਅੰਜਕ = build4 (ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), tmp,
				     ਵਿਅੰਜਕ, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ);
		      ਜੋੜੋ_stmt (ਵਿਅੰਜਕ);
		      OMP_CLAUSE_ਸੰਕਾਰਜ (c, i) = ਵਿਅੰਜਕ;
		      ਰੁੱਖ tc = build_omp_clause (OMP_CLAUSE_LOCATION (c),
						  OMP_CLAUSE_FIRSTPRIVATE);
		      OMP_CLAUSE_DECL (tc) = tmp;
		      OMP_CLAUSE_CHAIN (tc)
			= cclauses[C_OMP_CLAUSE_ਵੰਡੋ_ਨਿਸ਼ਾਨਾ];
		      cclauses[C_OMP_CLAUSE_ਵੰਡੋ_ਨਿਸ਼ਾਨਾ] = tc;
		    }
	  ਰੁੱਖ stmt = make_ਗੰਢ (OMP_ਨਿਸ਼ਾਨਾ);
	  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;
	  OMP_ਨਿਸ਼ਾਨਾ_CLAUSES (stmt) = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_ਨਿਸ਼ਾਨਾ];
	  c_omp_adjust_map_clauses (OMP_ਨਿਸ਼ਾਨਾ_CLAUSES (stmt), ਸੱਚ);
	  OMP_ਨਿਸ਼ਾਨਾ_BODY (stmt) = ਖੰਡ;
	  OMP_ਨਿਸ਼ਾਨਾ_COMBINED (stmt) = 1;
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
	  ਜੋੜੋ_stmt (stmt);
	  pc = &OMP_ਨਿਸ਼ਾਨਾ_CLAUSES (stmt);
	  ਜਾਓ check_clauses;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਵਾਪਸ ਝੂਠ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "data") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_ਨਿਸ਼ਾਨਾ_ਅੰਕੜੇ (loc, parser, if_p);
	  ਵਾਪਸ ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "enter") == 0)
	{
	  c_parser_consume_token (parser);
	  ਵਾਪਸ c_parser_omp_ਨਿਸ਼ਾਨਾ_enter_ਅੰਕੜੇ (loc, parser, context);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "exit") == 0)
	{
	  c_parser_consume_token (parser);
	  ਵਾਪਸ c_parser_omp_ਨਿਸ਼ਾਨਾ_exit_ਅੰਕੜੇ (loc, parser, context);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "update") == 0)
	{
	  c_parser_consume_token (parser);
	  ਵਾਪਸ c_parser_omp_ਨਿਸ਼ਾਨਾ_update (loc, parser, context);
	}
    }
  ਜੇ (!flag_openmp) /* flag_openmp_simd  */
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ ਝੂਠ;
    }

  stmt = make_ਗੰਢ (OMP_ਨਿਸ਼ਾਨਾ);
  ਰੁੱਖ_TYPE (stmt) = void_type_ਗੰਢ;

  clauses = c_parser_omp_all_clauses (parser, OMP_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ,
				      "#pragma omp target", ਝੂਠ);
  ਲਈ (ਰੁੱਖ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਵਿੱਚ_REDUCTION)
      {
	ਰੁੱਖ nc = build_omp_clause (OMP_CLAUSE_LOCATION (c), OMP_CLAUSE_MAP);
	OMP_CLAUSE_DECL (nc) = OMP_CLAUSE_DECL (c);
	OMP_CLAUSE_ਸੈੱਟ_MAP_ਕਿਸਮ (nc, GOMP_MAP_ALWAYS_TOFROM);
	OMP_CLAUSE_CHAIN (nc) = OMP_CLAUSE_CHAIN (c);
	OMP_CLAUSE_CHAIN (c) = nc;
      }
  clauses = c_omp_instantiate_mappers (clauses, C_ORT_OMP_ਨਿਸ਼ਾਨਾ);
  clauses  = c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP_ਨਿਸ਼ਾਨਾ);
  c_omp_adjust_map_clauses (clauses, ਸੱਚ);

  keep_ਅਗਲਾ_level ();
  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  body = c_parser_omp_structured_ਖੰਡ (parser, if_p);

  c_omp_ਜਾਂਚ_mapper_bindings (loc, &clauses, body);

  ਜੋੜੋ_stmt (body);
  OMP_ਨਿਸ਼ਾਨਾ_CLAUSES (stmt) = clauses;
  pc = &OMP_ਨਿਸ਼ਾਨਾ_CLAUSES (stmt);
  OMP_ਨਿਸ਼ਾਨਾ_BODY (stmt) = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);

  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (stmt, loc);
  ਜੋੜੋ_stmt (stmt);

check_clauses:
  ਜਦੋਂ (*pc)
    {
      ਜੇ (OMP_CLAUSE_ਕੋਡ (*pc) == OMP_CLAUSE_MAP)
	ਚੋਣ (OMP_CLAUSE_MAP_ਕਿਸਮ (*pc))
	  {
	  ਹਾਲਤ GOMP_MAP_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_PRESENT_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_ਮੰਜ਼ਿਲ:
	  ਹਾਲਤ GOMP_MAP_FROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_FROM:
	  ਹਾਲਤ GOMP_MAP_PRESENT_FROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_FROM:
	  ਹਾਲਤ GOMP_MAP_TOFROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_TOFROM:
	  ਹਾਲਤ GOMP_MAP_PRESENT_TOFROM:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_PRESENT_TOFROM:
	  ਹਾਲਤ GOMP_MAP_ALLOC:
	  ਹਾਲਤ GOMP_MAP_PRESENT_ALLOC:
	  ਹਾਲਤ GOMP_MAP_FIRSTPRIVATE_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ALWAYS_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ਸੂਚਕ:
	  ਹਾਲਤ GOMP_MAP_ATTACH_DETACH:
	  ਹਾਲਤ GOMP_MAP_ATTACH:
	    ਰੋਕੋ;
	  ਮੂਲ:
	    error_at (OMP_CLAUSE_LOCATION (*pc),
		      "%<#pragma omp target%> with map-type other "
		      "than %<to%>, %<from%>, %<tofrom%> or %<alloc%> "
		      "on %<map%> clause");
	    *pc = OMP_CLAUSE_CHAIN (*pc);
	    ਜਾਰੀ;
	  }
      pc = &OMP_CLAUSE_CHAIN (*pc);
    }
  cfun->has_omp_ਨਿਸ਼ਾਨਾ = ਸੱਚ;
  ਵਾਪਸ ਸੱਚ;
}

/* OpenMP 4.0:
   # pragma omp declare simd declare-simd-clauses[optseq] new-line

   OpenMP 5.0:
   # pragma omp declare variant (identifier) match(context-selector) new-line

   OpenMP 5.1
   # pragma omp declare variant (identifier) match(context-selector) \
      adjust_args(adjust-op:argument-list) append_args(interop-list) new-line
   */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_DECLARE_SIMD_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SIMDLEN)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਰੇਖਿਕ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALIGNED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਇਕਸਾਰ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_INBRANCH)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOTINBRANCH))

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_declare_simd (c_parser *parser, ਗਿਣਤੀ pragma_context context)
{
  c_token *token = c_parser_peek_token (parser);
  gcc_assert (token->type == CPP_NAME);
  ਰੁੱਖ ਕਿਸਮ = token->ਮੁੱਲ;
  gcc_assert (strcmp (IDENTIFIER_ਸੂਚਕ (ਕਿਸਮ), "simd") == 0
	      || strcmp (IDENTIFIER_ਸੂਚਕ (ਕਿਸਮ), "variant") == 0);

  auto_vec<c_token> clauses;
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      c_token *token = c_parser_peek_token (parser);
      ਜੇ (token->type == CPP_EOF)
	{
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	  ਵਾਪਸ;
	}
      clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*token);
      c_parser_consume_token (parser);
    }
  clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*c_parser_peek_token (parser));
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA))
    {
      ਜੇ (c_parser_peek_token (parser)->pragma_ਕਿਸਮ != PRAGMA_OMP_DECLARE
	  || c_parser_peek_2nd_token (parser)->type != CPP_NAME
	  || c_parser_peek_2nd_token (parser)->ਮੁੱਲ != ਕਿਸਮ)
	{
	  error ("%<#pragma omp declare %s%> must be followed by "
		 "function declaration or definition or another "
		 "%<#pragma omp declare %s%>",
		 IDENTIFIER_ਸੂਚਕ (ਕਿਸਮ), IDENTIFIER_ਸੂਚਕ (ਕਿਸਮ));
	  ਵਾਪਸ;
	}
      c_parser_consume_pragma (parser);
      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  ਜੇ (token->type == CPP_EOF)
	    {
	      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	      ਵਾਪਸ;
	    }
	  clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*token);
	  c_parser_consume_token (parser);
	}
      clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*c_parser_peek_token (parser));
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
    }

  /* Make sure nothing tries to read past the end of the tokens.  */
  c_token eof_token;
  memset (&eof_token, 0, ਆਕਾਰ (eof_token));
  eof_token.type = CPP_EOF;
  clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eof_token);
  clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eof_token);

  ਚੋਣ (context)
    {
    ਹਾਲਤ pragma_external:
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ਪੂਰਨ ext = disable_extension_diagnostics ();
	  ਕਰੋ
	    c_parser_consume_token (parser);
	  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਝੂਠ, ਸੱਚ,
					 ਝੂਠ, ਨਿਰਾ, &clauses);
	  restore_extension_diagnostics (ext);
	}
      ਨਹੀਂਤਾਂ
	c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਝੂਠ, ਸੱਚ,
				       ਝੂਠ, ਨਿਰਾ, &clauses);
      ਰੋਕੋ;
    ਹਾਲਤ pragma_struct:
    ਹਾਲਤ pragma_param:
    ਹਾਲਤ pragma_stmt:
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_ਸੂਚਕ (ਕਿਸਮ));
      ਰੋਕੋ;
    ਹਾਲਤ pragma_compound:
      ਤਾਰਕਿਕ have_std_attrs;
      ਰੁੱਖ std_attrs;
      have_std_attrs = c_parser_nth_token_starts_std_ਗੁਣ (parser, 1);
      ਜੇ (have_std_attrs)
	std_attrs = c_parser_std_attribute_specifier_sequence (parser);
      ਨਹੀਂਤਾਂ
	std_attrs = NULL_ਰੁੱਖ;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_EXTENSION)
	{
	  ਪੂਰਨ ext = disable_extension_diagnostics ();
	  ਕਰੋ
	    c_parser_consume_token (parser);
	  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
		 && c_parser_peek_token (parser)->keyword == RID_EXTENSION);
	  ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser)
	      || c_parser_nth_token_starts_std_ਗੁਣ (parser, 1))
	    {
	      c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ,
					     ਸੱਚ, ਝੂਠ, ਨਿਰਾ, &clauses,
					     have_std_attrs, std_attrs);
	      restore_extension_diagnostics (ext);
	      ਰੋਕੋ;
	    }
	  restore_extension_diagnostics (ext);
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser))
	{
	  c_parser_declaration_or_fndef (parser, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ,
					 ਝੂਠ, ਨਿਰਾ, &clauses, have_std_attrs,
					 std_attrs);
	  ਰੋਕੋ;
	}
      error ("%<#pragma omp declare %s%> must be followed by "
	     "function declaration or definition",
	     IDENTIFIER_ਸੂਚਕ (ਕਿਸਮ));
      ਰੋਕੋ;
    ਮੂਲ:
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_context_selector (c_parser *parser, ਗਿਣਤੀ omp_tss_ਕੋਡ ਸੈੱਟ,
			       ਰੁੱਖ parms)
{
  ਰੁੱਖ ret = NULL_ਰੁੱਖ;
  ਕਰੋ
    {
      ਰੁੱਖ selector;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
	  || c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	selector = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected trait selector name");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}
      ਗਿਣਤੀ omp_ts_ਕੋਡ sel
	= omp_lookup_ts_ਕੋਡ (ਸੈੱਟ, IDENTIFIER_ਸੂਚਕ (selector));

      ਜੇ (sel == OMP_TRAIT_INVALID)
	{
	  /* Per the spec, "Implementations can ignore specified selectors
	     that are not those described in this section"; however, we
	     must record such selectors because they cause match failures.  */
	  warning_at (c_parser_peek_token (parser)->location, OPT_Wopenmp,
		      "unknown selector %qs for context selector set %qs",
		      IDENTIFIER_ਸੂਚਕ (selector),  omp_tss_map[ਸੈੱਟ]);
	  c_parser_consume_token (parser);
	  ret = make_trait_selector (sel, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ, ret);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
	    c_parser_ਸੰਤੁਲਿਤ_token_sequence (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ
	    ਰੋਕੋ;
	}

      c_parser_consume_token (parser);

      ਰੁੱਖ properties = NULL_ਰੁੱਖ;
      ਰੁੱਖ scoreval = NULL_ਰੁੱਖ;
      ਗਿਣਤੀ omp_tp_type property_ਕਿਸਮ = omp_ts_map[sel].tp_type;
      ਤਾਰਕਿਕ allow_score = omp_ts_map[sel].allow_score;
      ਰੁੱਖ t;

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
	{
	  ਜੇ (property_ਕਿਸਮ == OMP_TRAIT_PROPERTY_NONE)
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"selector %qs does not accept any properties",
			IDENTIFIER_ਸੂਚਕ (selector));
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }

	  matching_parens parens;
	  parens.require_open (parser);

	  c_token *token = c_parser_peek_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_ਸੂਚਕ (token->ਮੁੱਲ), "score") == 0
	      && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN)
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens2;
	      parens2.require_open (parser);
	      ਰੁੱਖ score = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ).ਮੁੱਲ;
	      parens2.skip_until_ਮਿਲਿਆ_close (parser);
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      ਜੇ (!allow_score)
		error_at (token->location,
			  "%<score%> cannot be specified in traits "
			  "in the %qs trait-selector-set",
			  omp_tss_map[ਸੈੱਟ]);
	      ਨਹੀਂਤਾਂ ਜੇ (score != error_mark_ਗੰਢ)
		{
		  mark_exp_read (score);
		  score = c_fully_fold (score, ਝੂਠ, ਨਿਰਾ);
		  ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (score))
		      || ਰੁੱਖ_ਕੋਡ (score) != INTEGER_CST)
		    error_at (token->location, "%<score%> argument must "
			      "be constant integer expression");
		  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_int_cst_sgn (score) < 0)
		    error_at (token->location, "%<score%> argument must "
			      "be non-negative");
		  ਨਹੀਂਤਾਂ
		    scoreval = score;
		}
	      token = c_parser_peek_token (parser);
	    }

	  ਚੋਣ (property_ਕਿਸਮ)
	    {
	    ਹਾਲਤ OMP_TRAIT_PROPERTY_ID:
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
		  || c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		{
		  ਰੁੱਖ prop = c_parser_peek_token (parser)->ਮੁੱਲ;
		  c_parser_consume_token (parser);
		  properties = make_trait_property (prop, NULL_ਰੁੱਖ,
						    properties);
		}
	      ਨਹੀਂਤਾਂ
		{
		  c_parser_error (parser, "expected identifier");
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ OMP_TRAIT_PROPERTY_NAME_LIST:
	      ਕਰੋ
		{
		  ਰੁੱਖ prop = OMP_TP_NAMELIST_ਗੰਢ;
		  ਰੁੱਖ ਮੁੱਲ = NULL_ਰੁੱਖ;
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
		      || c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		    {
		      ਮੁੱਲ = c_parser_peek_token (parser)->ਮੁੱਲ;
		      c_parser_consume_token (parser);
		    }
		  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_STRING))
		    ਮੁੱਲ = c_parser_string_literal (parser, ਝੂਠ,
						     ਝੂਠ).ਮੁੱਲ;
		  ਨਹੀਂਤਾਂ
		    {
		      c_parser_error (parser, "expected identifier or "
					      "string literal");
		      ਵਾਪਸ error_mark_ਗੰਢ;
		    }

		  properties = make_trait_property (prop, ਮੁੱਲ, properties);

		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  ਨਹੀਂਤਾਂ
		    ਰੋਕੋ;
		}
	      ਜਦੋਂ (1);
	      ਰੋਕੋ;
	    ਹਾਲਤ OMP_TRAIT_PROPERTY_DEV_ਅੰਕ_ਵਿਅੰਜਕ:
	    ਹਾਲਤ OMP_TRAIT_PROPERTY_BOOL_ਵਿਅੰਜਕ:
	      {
		c_ਵਿਅੰਜਕ texpr = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
		texpr = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (token->location, texpr,
						  ਸੱਚ, ਸੱਚ);
		t = texpr.ਮੁੱਲ;
	      }
	      ਜੇ (t == error_mark_ਗੰਢ)
		ਵਾਪਸ error_mark_ਗੰਢ;
	      mark_exp_read (t);
	      ਜੇ (property_ਕਿਸਮ == OMP_TRAIT_PROPERTY_BOOL_ਵਿਅੰਜਕ)
		{
		  t = c_objc_common_truthvalue_conversion (token->location,
							   t,
							   boolean_type_ਗੰਢ);
		  ਜੇ (t == error_mark_ਗੰਢ)
		    ਵਾਪਸ error_mark_ਗੰਢ;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (t)))
		{
		  error_at (token->location,
			    "property must be integer expression");
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
	      properties = make_trait_property (NULL_ਰੁੱਖ, t, properties);
	      ਰੋਕੋ;
	    ਹਾਲਤ OMP_TRAIT_PROPERTY_CLAUSE_LIST:
	      ਜੇ (sel == OMP_TRAIT_CONSTRUCT_SIMD)
		{
		  ਜੇ (parms == NULL_ਰੁੱਖ)
		    {
		      error_at (token->location, "properties for %<simd%> "
				"selector may not be specified in "
				"%<metadirective%>");
		      ਵਾਪਸ error_mark_ਗੰਢ;
		    }
		  ਰੁੱਖ c;
		  c = c_parser_omp_all_clauses (parser,
						OMP_DECLARE_SIMD_CLAUSE_ਨਕਾਬ,
						"simd", ਸੱਚ, 2);
		  c = c_omp_declare_simd_clauses_ਮੰਜ਼ਿਲ_numbers (parms
							     == error_mark_ਗੰਢ
							     ? NULL_ਰੁੱਖ : parms,
							     c);
		  properties = c;
		}
	      ਨਹੀਂਤਾਂ ਜੇ (sel == OMP_TRAIT_IMPLEMENTATION_REQUIRES)
		{
		  /* FIXME: The "requires" selector was added in OpenMP 5.1.
		     Currently only the now-deprecated syntax
		     from OpenMP 5.0 is supported.  */
		  sorry_at (token->location,
			    "%<requires%> selector is not supported yet");
		  ਵਾਪਸ error_mark_ਗੰਢ;
		}
	      ਨਹੀਂਤਾਂ
		gcc_unreachable ();
	      ਰੋਕੋ;
	    ਮੂਲ:
	      gcc_unreachable ();
	    }

	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	  properties = nreverse (properties);
	}
      ਨਹੀਂਤਾਂ ਜੇ (property_ਕਿਸਮ != OMP_TRAIT_PROPERTY_NONE
	       && property_ਕਿਸਮ != OMP_TRAIT_PROPERTY_CLAUSE_LIST
	       && property_ਕਿਸਮ != OMP_TRAIT_PROPERTY_EXTENSION)
	{
	  c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      ret = make_trait_selector (sel, scoreval, properties, ret);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  ਜਦੋਂ (1);

  ਵਾਪਸ nreverse (ret);
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

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_context_selector_specification (c_parser *parser, ਰੁੱਖ parms)
{
  ਰੁੱਖ ret = NULL_ਰੁੱਖ;
  ਕਰੋ
    {
      ਅਚਲ ਅੱਖਰ *setp = "";
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	setp = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਗਿਣਤੀ omp_tss_ਕੋਡ ਸੈੱਟ = omp_lookup_tss_ਕੋਡ (setp);

      ਜੇ (ਸੈੱਟ == OMP_TRAIT_ਸੈੱਟ_INVALID)
	{
	  c_parser_error (parser, "expected context selector set name");
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      c_parser_consume_token (parser);

      ਜੇ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
	ਵਾਪਸ error_mark_ਗੰਢ;

      matching_braces braces;
      ਜੇ (!braces.require_open (parser))
	ਵਾਪਸ error_mark_ਗੰਢ;

      ਰੁੱਖ selectors = c_parser_omp_context_selector (parser, ਸੈੱਟ, parms);
      ਜੇ (selectors == error_mark_ਗੰਢ)
	{
	  c_parser_skip_ਮੰਜ਼ਿਲ_closing_brace (parser);
	  ret = error_mark_ਗੰਢ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (ret != error_mark_ਗੰਢ)
	ret = make_trait_ਸੈੱਟ_selector (ਸੈੱਟ, selectors, ret);

      braces.require_close (parser);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }
  ਜਦੋਂ (1);

  ਜੇ (ret == error_mark_ਗੰਢ)
    ਵਾਪਸ ret;
  ਵਾਪਸ nreverse (ret);
}

/* Finalize #pragma omp declare variant after FNDECL has been parsed, and put
   that into "omp declare variant base" attribute.  */

ਸਥਿਰ ਖਾਲੀ
c_ਅੰਤ_omp_declare_variant (c_parser *parser, ਰੁੱਖ fndecl, ਰੁੱਖ parms)
{
  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    {
     fail:
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ;
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_ਕਿਸਮ != C_ID_ID)
    {
      c_parser_error (parser, "expected identifier");
      ਜਾਓ fail;
    }

  c_token *token = c_parser_peek_token (parser);
  ਰੁੱਖ variant = lookup_name (token->ਮੁੱਲ);

  ਜੇ (variant == NULL_ਰੁੱਖ)
    {
      undeclared_variable (token->location, token->ਮੁੱਲ);
      variant = error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (variant) != FUNCTION_DECL)
    {
      error_at (token->location, "variant %qD is not a function",
		variant);
      variant = error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (fndecl_built_ਵਿੱਚ_p (variant)
	   && (ਲੜੀ_ਤੁਲਨਾ (IDENTIFIER_ਸੂਚਕ (DECL_NAME (variant)),
			"__builtin_", ਲੜੀ_ਲੰਬਾਈ ("__builtin_")) == 0
	       || ਲੜੀ_ਤੁਲਨਾ (IDENTIFIER_ਸੂਚਕ (DECL_NAME (variant)),
			   "__sync_", ਲੜੀ_ਲੰਬਾਈ ("__sync_")) == 0
	       || ਲੜੀ_ਤੁਲਨਾ (IDENTIFIER_ਸੂਚਕ (DECL_NAME (variant)),
			   "__atomic_", ਲੜੀ_ਲੰਬਾਈ ("__atomic_")) == 0))
    {
      error_at (token->location, "variant %qD is a built-in",
		variant);
      variant = error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ ਜੇ (variant == fndecl)
    {
      error_at (token->location, "variant %qD is the same as base function",
		variant);
      variant = error_mark_ਗੰਢ;
    }

  c_parser_consume_token (parser);

  parens.require_close (parser);

  ਰੁੱਖ append_ਦਲੀਲਾਂ_ਰੁੱਖ = NULL_ਰੁੱਖ;
  ਰੁੱਖ append_ਦਲੀਲਾਂ_ਆਖਰੀ;
  vec<ਰੁੱਖ> adjust_ਦਲੀਲਾਂ_list = vNULL;
  ਤਾਰਕਿਕ has_ਮੇਲ = ਝੂਠ, has_adjust_ਦਲੀਲਾਂ = ਝੂਠ;
  location_t adjust_ਦਲੀਲਾਂ_loc = UNKNOWN_LOCATION;
  location_t append_ਦਲੀਲਾਂ_loc = UNKNOWN_LOCATION;
  location_t ਮੇਲ_loc = UNKNOWN_LOCATION;
  ਰੁੱਖ need_device_ptr_list = NULL_ਰੁੱਖ;
  ਰੁੱਖ ctx = error_mark_ਗੰਢ;

  ਕਰੋ
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ਅਚਲ ਅੱਖਰ *clause = "";
      location_t loc = c_parser_peek_token (parser)->location;
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	clause = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      ਗਿਣਤੀ clause
      {
	ਮੇਲ,
	adjust_ਦਲੀਲਾਂ,
	append_ਦਲੀਲਾਂ
      } ccode;

      ਜੇ (strcmp (clause, "match") == 0)
	{
	  ccode = ਮੇਲ;
	  ਮੇਲ_loc = loc;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (clause, "adjust_args") == 0)
	{
	  ccode = adjust_ਦਲੀਲਾਂ;
	  adjust_ਦਲੀਲਾਂ_loc = loc;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (clause, "append_args") == 0)
	{
	  ccode = append_ਦਲੀਲਾਂ;
	  append_ਦਲੀਲਾਂ_loc = loc;
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected %<match%>, %<adjust_args%> or "
				  "%<append_args%> clause");
	  ਜਾਓ fail;
	}

      c_parser_consume_token (parser);

      ਜੇ (!parens.require_open (parser))
	ਜਾਓ fail;

      ਜੇ (parms == NULL_ਰੁੱਖ)
	parms = error_mark_ਗੰਢ;

      ਜੇ (ccode == ਮੇਲ)
	{
	  ਜੇ (has_ਮੇਲ)
	    error_at (ਮੇਲ_loc, "too many %<match%> clauses");
	  has_ਮੇਲ = ਸੱਚ;
	  ctx  = c_parser_omp_context_selector_specification (parser, parms);
	  ਜੇ (ctx == error_mark_ਗੰਢ)
	    ਜਾਓ fail;
	  ctx = omp_check_context_selector (ਮੇਲ_loc, ctx,
					    OMP_CTX_DECLARE_VARIANT);

	  /* The OpenMP spec says the merging rules for enclosing
	     "begin declare variant" contexts apply to "declare variant
	     directives" -- the term it uses to refer to both directive
	     forms.  */
	  ਜੇ (ctx != error_mark_ਗੰਢ
	      && !vec_ਸੁਰੱਖਿਅਤ_is_ਖਾਲੀ_ਥਾਵਾਂ (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->ਆਖਰੀ ();
	      ਰੁੱਖ outer_ctx = a.selector;
	      ctx = omp_ਮਿਲਾਓ_context_selectors (ਮੇਲ_loc, outer_ctx, ctx,
						 OMP_CTX_DECLARE_VARIANT);
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ccode == adjust_ਦਲੀਲਾਂ)
	{
	  has_adjust_ਦਲੀਲਾਂ = ਸੱਚ;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      ਅਚਲ ਅੱਖਰ *p
		= IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	      ਜੇ (strcmp (p, "need_device_ptr") == 0
		  || strcmp (p, "nothing") == 0)
		{
		  c_parser_consume_token (parser); // need_device_ptr
		  c_parser_consume_token (parser); // :

		  loc = c_parser_peek_token (parser)->location;
		  ਰੁੱਖ list
		    = c_parser_omp_variable_list (parser, loc, OMP_CLAUSE_ERROR,
						  NULL_ਰੁੱਖ);

		  ਰੁੱਖ arg;
		  ਜੇ (variant != error_mark_ਗੰਢ)
		    ਲਈ (ਰੁੱਖ c = list; c != NULL_ਰੁੱਖ; c = ਰੁੱਖ_CHAIN (c))
		      {
			ਰੁੱਖ decl = ਰੁੱਖ_PURPOSE (c);
			location_t arg_loc = ਵਿਅੰਜਕ_LOCATION (ਰੁੱਖ_ਮੁੱਲ (c));
			ਪੂਰਨ idx;
			ਲਈ (arg = parms, idx = 0; arg != ਨਿਰਾ;
			     arg = ਰੁੱਖ_CHAIN (arg), idx++)
			  ਜੇ (arg == decl)
			    ਰੋਕੋ;
			ਜੇ (arg == NULL_ਰੁੱਖ)
			  {
			    error_at (arg_loc,
				      "%qD is not a function argument",
				      decl);
			    ਜਾਓ fail;
			  }
			ਜੇ (adjust_ਦਲੀਲਾਂ_list.ਸ਼ਾਮਲ_ਹੈ (arg))
			  {
			    error_at (arg_loc,
				      "%qD is specified more than once",
				      decl);
			    ਜਾਓ fail;
			  }
			ਜੇ (strcmp (p, "need_device_ptr") == 0
			    && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (arg)) != ਸੂਚਕ_TYPE)
			  {
			    error_at (loc, "%qD is not of pointer type", decl);
			    ਜਾਓ fail;
			  }
			adjust_ਦਲੀਲਾਂ_list.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (arg);
			ਜੇ (strcmp (p, "need_device_ptr") == 0)
			  {
			    need_device_ptr_list = chainon (
			      need_device_ptr_list,
			      build_ਰੁੱਖ_list (
				NULL_ਰੁੱਖ,
				build_int_cst (
				  integer_type_ਗੰਢ,
				  idx))); // Store 0-based argument index,
					  // as in gimplify_call_expr
			  }
		      }
		}
	      ਨਹੀਂਤਾਂ
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %<nothing%> or %<need_device_ptr%>");
		  ਜੇ (strcmp (p, "need_device_addr") == 0)
		    inform (c_parser_peek_token (parser)->location,
			    "%<need_device_addr%> is not valid for C");
		  ਜਾਓ fail;
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected %<nothing%> or %<need_device_ptr%> "
			"followed by %<:%>");
	      ਜਾਓ fail;
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (ccode == append_ਦਲੀਲਾਂ)
	{
	  ਜੇ (append_ਦਲੀਲਾਂ_ਰੁੱਖ)
	    {
	      error_at (append_ਦਲੀਲਾਂ_loc, "too many %qs clauses", "append_args");
	      append_ਦਲੀਲਾਂ_ਰੁੱਖ = NULL_ਰੁੱਖ;
	    }
	  ਕਰੋ
	    {
	      location_t loc = c_parser_peek_token (parser)->location;
	      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
		  || strcmp ("interop",
			     IDENTIFIER_ਸੂਚਕ (
			       c_parser_peek_token (parser)->ਮੁੱਲ)))
		{
		  error_at (loc, "expected %<interop%>");
		  ਜਾਓ fail;
		}
	      c_parser_consume_token (parser);

	      ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		ਜਾਓ fail;
	      ਤਾਰਕਿਕ ਨਿਸ਼ਾਨਾ = ਝੂਠ;
	      ਤਾਰਕਿਕ targetsync = ਝੂਠ;
	      ਰੁੱਖ prefer_type_ਰੁੱਖ = NULL_ਰੁੱਖ;
	      ਜੇ (!c_parser_omp_clause_init_modifiers (parser, &ਨਿਸ਼ਾਨਾ,
						       &targetsync,
						       &prefer_type_ਰੁੱਖ)
		  || !c_parser_require (parser, CPP_CLOSE_PAREN,
					"expected %<)%> or %<,%>"))
		ਜਾਓ fail;
	      ਜੇ (!ਨਿਸ਼ਾਨਾ && !targetsync)
		error_at (loc,
			  "missing required %<target%> and/or "
			  "%<targetsync%> modifier");
	      ਰੁੱਖ t = build_ਰੁੱਖ_list (ਨਿਸ਼ਾਨਾ ? boolean_true_ਗੰਢ
					       : boolean_false_ਗੰਢ,
					targetsync ? boolean_true_ਗੰਢ
						   : boolean_false_ਗੰਢ);
	      t = build1_loc (loc, NOP_ਵਿਅੰਜਕ, void_type_ਗੰਢ, t);
	      t = build_ਰੁੱਖ_list (t, prefer_type_ਰੁੱਖ);
	      ਜੇ (append_ਦਲੀਲਾਂ_ਰੁੱਖ)
		{
		  ਰੁੱਖ_CHAIN (append_ਦਲੀਲਾਂ_ਆਖਰੀ) = t;
		  append_ਦਲੀਲਾਂ_ਆਖਰੀ = t;
		}
	      ਨਹੀਂਤਾਂ
		append_ਦਲੀਲਾਂ_ਰੁੱਖ = append_ਦਲੀਲਾਂ_ਆਖਰੀ = t;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
		ਰੋਕੋ;
	      ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<)%> or %<,%>"))
		ਜਾਓ fail;
	    }
	  ਜਦੋਂ (ਸੱਚ);
	}

      parens.require_close (parser);
  } ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL));
  ਜੇ (variant != error_mark_ਗੰਢ && !has_ਮੇਲ)
    {
      c_parser_error (parser, "expected %<match%> clause");
      variant = error_mark_ਗੰਢ;
    }
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  /* At this point, we have completed parsing of the pragma, now it's
     on to error checking.  */
  ਜੇ (variant == error_mark_ਗੰਢ || ctx == error_mark_ਗੰਢ)
    /* Previously diagnosed error.  */
    ਵਾਪਸ;

  ਜੇ ((has_adjust_ਦਲੀਲਾਂ || append_ਦਲੀਲਾਂ_ਰੁੱਖ)
      && !omp_get_context_selector (ctx, OMP_TRAIT_ਸੈੱਟ_CONSTRUCT,
				    OMP_TRAIT_CONSTRUCT_DISPATCH))
    {
      error_at (has_adjust_ਦਲੀਲਾਂ ? adjust_ਦਲੀਲਾਂ_loc : append_ਦਲੀਲਾਂ_loc,
		"an %qs clause can only be specified if the "
		"%<dispatch%> selector of the %<construct%> selector "
		"set appears in the %<match%> clause",
		has_adjust_ਦਲੀਲਾਂ ? "adjust_args" : "append_args");
      ਵਾਪਸ;
    }

  ਜੇ (!omp_get_context_selector (ctx, OMP_TRAIT_ਸੈੱਟ_CONSTRUCT,
				 OMP_TRAIT_CONSTRUCT_SIMD))
    /* Check that the base and variant have compatible types.  */
    {
      ਰੁੱਖ ਅਧਾਰ_type = ਰੁੱਖ_TYPE (fndecl);
      ਰੁੱਖ variant_type = ਰੁੱਖ_TYPE (variant);
      ਤਾਰਕਿਕ unprototyped_variant
	= (TYPE_ARG_TYPES (variant_type) == NULL_ਰੁੱਖ
	   && !TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (variant_type));

      ਜੇ (append_ਦਲੀਲਾਂ_ਰੁੱਖ
	  && TYPE_ARG_TYPES (ਅਧਾਰ_type) == NULL_ਰੁੱਖ
	  && !TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (ਅਧਾਰ_type))
	{
	  /* The base function is a pre-C23 unprototyped function.  Without
	     a prototype, we don't know the offset where the append_args go.
	     That offset needs to be stored with the append_args in the
	     variant function attributes, so we cannot presently handle
	     this case.  */
	  sorry_at (append_ਦਲੀਲਾਂ_loc,
		    "%<append_args%> with unprototyped base function "
		    "is not supported yet");
	  inform (DECL_ਸਰੋਤ_LOCATION (fndecl),
		  "base function %qD declared here", fndecl);
	  ਵਾਪਸ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (append_ਦਲੀਲਾਂ_ਰੁੱਖ)
	{
	  /* Find nbase_args, the number of fixed arguments in the base
	     function.  */
	  ਪੂਰਨ nappend_ਦਲੀਲਾਂ = 0;
	  ਪੂਰਨ nbase_ਦਲੀਲਾਂ = 0;
	  ਲਈ (ਰੁੱਖ t = TYPE_ARG_TYPES (ਅਧਾਰ_type);
	       t && ਰੁੱਖ_ਮੁੱਲ (t) != void_type_ਗੰਢ; t = ਰੁੱਖ_CHAIN (t))
	    nbase_ਦਲੀਲਾਂ++;
	  ਲਈ (ਰੁੱਖ t = append_ਦਲੀਲਾਂ_ਰੁੱਖ; t; t = ਰੁੱਖ_CHAIN (t))
	    nappend_ਦਲੀਲਾਂ++;

	  /* Store as purpose = arg number after which to append
	     and value = list of interop items.  */
	  append_ਦਲੀਲਾਂ_ਰੁੱਖ = build_ਰੁੱਖ_list (build_int_cst (integer_type_ਗੰਢ,
							     nbase_ਦਲੀਲਾਂ),
					      append_ਦਲੀਲਾਂ_ਰੁੱਖ);

	  /* Give a specific diagnostic if the append_args parameters
	     of the variant are of the wrong type, or missing.  The
	     compatible types test below could fail to detect this if
	     the variant is a varargs function.  */
	  ਜੇ (!unprototyped_variant)
	    {
	      ਰੁੱਖ ਦਲੀਲਾਂ = TYPE_ARG_TYPES (variant_type);
	      ਲਈ (ਪੂਰਨ i = 0; ਦਲੀਲਾਂ && i < nbase_ਦਲੀਲਾਂ;
		   i++, ਦਲੀਲਾਂ = ਰੁੱਖ_CHAIN (ਦਲੀਲਾਂ))
		;
	      ਲਈ (ਪੂਰਨ i = 0; i < nappend_ਦਲੀਲਾਂ; i++, ਦਲੀਲਾਂ = ਰੁੱਖ_CHAIN (ਦਲੀਲਾਂ))
		ਜੇ (!ਦਲੀਲਾਂ || !c_omp_interop_t_p (ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ)))
		  {
		    error_at (DECL_ਸਰੋਤ_LOCATION (variant),
			      "argument %d of %qD must be of "
			      "%<omp_interop_t%>",
			      nbase_ਦਲੀਲਾਂ + i + 1, variant);
		    inform (append_ਦਲੀਲਾਂ_loc,
			    "%<append_args%> specified here");
		    ਵਾਪਸ;
		  }
	    }

	  /* Perform the "implementation defined transformation" on the type
	     of the base function to add the append_args before checking it
	     for compatibility with the function variant's type.  */
	  ਰੁੱਖ ਦਲੀਲਾਂ = TYPE_ARG_TYPES (ਅਧਾਰ_type);
	  ਰੁੱਖ newargs = NULL_ਰੁੱਖ;
	  ਰੁੱਖ lastarg = NULL_ਰੁੱਖ;
	  ਲਈ (ਪੂਰਨ j = 0; j < nbase_ਦਲੀਲਾਂ; j++, ਦਲੀਲਾਂ = ਰੁੱਖ_CHAIN (ਦਲੀਲਾਂ))
	    {
	      ਰੁੱਖ t = ਰੁੱਖ_cons (ਰੁੱਖ_PURPOSE (ਦਲੀਲਾਂ),
				  ਰੁੱਖ_ਮੁੱਲ (ਦਲੀਲਾਂ), NULL_ਰੁੱਖ);
	      ਜੇ (lastarg)
		ਰੁੱਖ_CHAIN (lastarg) = t;
	      ਨਹੀਂਤਾਂ
		newargs = t;
	      lastarg = t;
	    }
	  ਰੁੱਖ type = lookup_name (get_identifier ("omp_interop_t"));
	  type = type ? ਰੁੱਖ_TYPE (type) : ਸੂਚਕ_sized_int_ਗੰਢ;
	  ਲਈ (ਪੂਰਨ j = 0; j < nappend_ਦਲੀਲਾਂ; j++)
	    {
	      ਰੁੱਖ t = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, type, NULL_ਰੁੱਖ);
	      ਜੇ (lastarg)
		ਰੁੱਖ_CHAIN (lastarg) = t;
	      ਨਹੀਂਤਾਂ
		newargs = t;
	      lastarg = t;
	    }
	  ਰੁੱਖ_CHAIN (lastarg) = ਦਲੀਲਾਂ;

	  /* Temporarily stuff newargs into the original base_type.  */
	  ਰੁੱਖ saveargs = TYPE_ARG_TYPES (ਅਧਾਰ_type);
	  TYPE_ARG_TYPES (ਅਧਾਰ_type) = newargs;
	  ਤਾਰਕਿਕ fail = !comptypes (ਅਧਾਰ_type, variant_type);
	  TYPE_ARG_TYPES (ਅਧਾਰ_type) = saveargs;

	  ਜੇ (fail)
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types "
			"after %<append_args%> adjustment",
			variant, fndecl);
	      inform (DECL_ਸਰੋਤ_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      ਵਾਪਸ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (unprototyped_variant)
	    /* If we've got an unprototyped variant, copy the transformed
	       base arg types to the variant.  This is needed later by
	       modify_call_for_omp_dispatch.  */
	    TYPE_ARG_TYPES (variant_type) = newargs;
	}
      ਨਹੀਂਤਾਂ  /* No append_args present.  */
	{
	  ਜੇ (!comptypes (ਅਧਾਰ_type, variant_type))
	    {
	      error_at (token->location,
			"variant %qD and base %qD have incompatible types",
			variant, fndecl);
	      inform (DECL_ਸਰੋਤ_LOCATION (variant),
		      "%<declare variant%> candidate %qD declared here",
		      variant);
	      ਵਾਪਸ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (TYPE_ARG_TYPES (variant_type) == NULL_ਰੁੱਖ
		   && !TYPE_NO_NAMED_ਦਲੀਲਾਂ_STDARG_P (variant_type)
		   && TYPE_ARG_TYPES (ਅਧਾਰ_type) != NULL_ਰੁੱਖ)
	    /* If we've got an unprototyped variant but the base has
	       a prototype, copy the base arg types to the variant.  */
	    TYPE_ARG_TYPES (variant_type) = TYPE_ARG_TYPES (ਅਧਾਰ_type);
	}
    }

  /* If we made it here, store the parsed information.  */
  C_DECL_ਵਰਤਿਆ (variant) = 1;
  ਰੁੱਖ construct = omp_get_context_selector_list (ctx,
						  OMP_TRAIT_ਸੈੱਟ_CONSTRUCT);
  omp_mark_declare_variant (ਮੇਲ_loc, variant, construct);
  ਜੇ (omp_context_selector_matches (ctx, NULL_ਰੁੱਖ, ਝੂਠ))
    {
      ਰੁੱਖ attr = ਰੁੱਖ_cons (get_identifier ("omp declare variant base"),
			     build_ਰੁੱਖ_list (variant, ctx),
			     DECL_ਗੁਣ (fndecl));
      DECL_ਗੁਣ (fndecl) = attr;
    }

  ਜੇ (need_device_ptr_list || append_ਦਲੀਲਾਂ_ਰੁੱਖ)
    {
      ਰੁੱਖ variant_decl = ਰੁੱਖ_strip_nop_conversions (variant);
      ਰੁੱਖ t = build_ਰੁੱਖ_list (need_device_ptr_list,
				NULL_ਰੁੱਖ /* need_device_addr */);
      ਰੁੱਖ_CHAIN (t) = append_ਦਲੀਲਾਂ_ਰੁੱਖ;
      DECL_ਗੁਣ (variant_decl)
	= ਰੁੱਖ_cons (get_identifier ("omp declare variant variant args"), t,
		     DECL_ਗੁਣ (variant_decl));
    }
}

/* Finalize #pragma omp declare simd or #pragma omp declare variant
   clauses after FNDECL has been parsed, and put that into "omp declare simd"
   or "omp declare variant base" attribute.  */

ਸਥਿਰ ਖਾਲੀ
c_ਅੰਤ_omp_declare_simd (c_parser *parser, ਰੁੱਖ fndecl, ਰੁੱਖ parms,
			   vec<c_token> *pclauses)
{
  vec<c_token> &clauses = *pclauses;

  /* Normally first token is CPP_NAME "simd" or "variant".  CPP_EOF there
     indicates error has been reported and CPP_PRAGMA that
     c_finish_omp_declare_simd has already processed the tokens.  */
  ਜੇ (clauses.exists () && clauses[0].type == CPP_EOF)
    ਵਾਪਸ;
  ਅਚਲ ਅੱਖਰ *ਕਿਸਮ = "simd";
  ਜੇ (clauses.exists ()
      && (clauses[0].type == CPP_NAME || clauses[0].type == CPP_PRAGMA))
    ਕਿਸਮ = IDENTIFIER_ਸੂਚਕ (clauses[0].ਮੁੱਲ);
  gcc_assert (strcmp (ਕਿਸਮ, "simd") == 0 || strcmp (ਕਿਸਮ, "variant") == 0);
  ਜੇ (fndecl == NULL_ਰੁੱਖ || ਰੁੱਖ_ਕੋਡ (fndecl) != FUNCTION_DECL)
    {
      error ("%<#pragma omp declare %s%> not immediately followed by "
	     "a function declaration or definition", ਕਿਸਮ);
      clauses[0].type = CPP_EOF;
      ਵਾਪਸ;
    }
  ਜੇ (clauses.exists () && clauses[0].type != CPP_NAME)
    {
      error_at (DECL_ਸਰੋਤ_LOCATION (fndecl),
		"%<#pragma omp declare %s%> not immediately followed by "
		"a single function declaration or definition", ਕਿਸਮ);
      clauses[0].type = CPP_EOF;
      ਵਾਪਸ;
    }
  ਜੇ (DECL_FUNCTION_VERSIONED (fndecl))
    {
      error_at (DECL_ਸਰੋਤ_LOCATION (fndecl),
		"%<#pragma omp declare %s%> cannot be used with function "
		"multi-versioning", ਕਿਸਮ);
      ਵਾਪਸ;
    }

  ਜੇ (parms == NULL_ਰੁੱਖ)
    parms = DECL_ARGUMENTS (fndecl);

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਟੋਕਨ_avail = parser->ਟੋਕਨ_avail;
  gcc_assert (parser->ਟੋਕਨ == &parser->ਟੋਕਨ_buf[0]);

  parser->ਟੋਕਨ = clauses.ਪਤਾ ();
  parser->ਟੋਕਨ_avail = clauses.ਲੰਮਾਈ ();

  /* c_parser_omp_declare_simd pushed 2 extra CPP_EOF tokens at the end.  */
  ਜਦੋਂ (parser->ਟੋਕਨ_avail > 3)
    {
      c_token *token = c_parser_peek_token (parser);
      gcc_assert (token->type == CPP_NAME);
      ਕਿਸਮ = IDENTIFIER_ਸੂਚਕ (token->ਮੁੱਲ);
      c_parser_consume_token (parser);
      parser->ਵਿੱਚ_pragma = ਸੱਚ;

      ਜੇ (strcmp (ਕਿਸਮ, "simd") == 0)
	{
	  ਰੁੱਖ c;
	  c = c_parser_omp_all_clauses (parser, OMP_DECLARE_SIMD_CLAUSE_ਨਕਾਬ,
					"#pragma omp declare simd");
	  c = c_omp_declare_simd_clauses_ਮੰਜ਼ਿਲ_numbers (parms, c);
	  ਜੇ (c != NULL_ਰੁੱਖ)
	    c = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, c, NULL_ਰੁੱਖ);
	  c = build_ਰੁੱਖ_list (get_identifier ("omp declare simd"), c);
	  ਰੁੱਖ_CHAIN (c) = DECL_ਗੁਣ (fndecl);
	  DECL_ਗੁਣ (fndecl) = c;
	}
      ਨਹੀਂਤਾਂ
	{
	  gcc_assert (strcmp (ਕਿਸਮ, "variant") == 0);
	  c_ਅੰਤ_omp_declare_variant (parser, fndecl, parms);
	}
    }

  parser->ਟੋਕਨ = &parser->ਟੋਕਨ_buf[0];
  parser->ਟੋਕਨ_avail = ਟੋਕਨ_avail;
  ਜੇ (clauses.exists ())
    clauses[0].type = CPP_PRAGMA;
}

/* This is consistent with the C++ front end.  */

#ਜੇ !defined (NO_DOT_ਵਿੱਚ_LABEL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ JOIN_STR "."
#ਜਾਂਜੇ !defined (NO_DOLLAR_ਵਿੱਚ_LABEL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ JOIN_STR "$"
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ JOIN_STR "_"
#ਜੇ_ਅੰਤ

/* Helper function for OpenMP "begin declare variant" directives.
   Function definitions inside the construct need to have their names
   mangled according to the context selector CTX.  The DECLARATOR is
   modified in place to point to a new identifier; the original name of
   the function is returned.  */
ਸਥਿਰ ਰੁੱਖ
omp_ਸ਼ੁਰੂ_variant_function (c_declarator *declarator, ਰੁੱਖ ctx)
{
  c_declarator *id = declarator;
  ਜਦੋਂ (id->ਕਿਸਮ != cdk_id)
    {
      id = id->declarator;
      gcc_assert (id);
    }
  ਰੁੱਖ name = id->u.id.id;
  id->u.id.id = omp_mangle_variant_name (name, ctx, JOIN_STR);
  ਵਾਪਸ name;
}

/* Helper function for OpenMP "begin declare variant" directives.  Now
   that we have a DECL for the variant function, and BASE_NAME for the
   base function, add an "omp declare variant base" attribute pointing
   at CTX to the base decl, and an "omp declare variant variant"
   attribute to the variant DECL.  */
ਸਥਿਰ ਖਾਲੀ
omp_ਅੰਤ_variant_function (ਰੁੱਖ decl, ਰੁੱਖ ਅਧਾਰ_name, ਰੁੱਖ ctx)
{
  /* First look up BASE_NAME and ensure it matches DECL.  */
  ਰੁੱਖ ਅਧਾਰ_decl = lookup_name (ਅਧਾਰ_name);
  ਜੇ (ਅਧਾਰ_decl == error_mark_ਗੰਢ)
    ਅਧਾਰ_decl = NULL_ਰੁੱਖ;
  ਜੇ (!ਅਧਾਰ_decl)
    {
      error_at (DECL_ਸਰੋਤ_LOCATION (decl),
		"no declaration of base function %qs",
		IDENTIFIER_ਸੂਚਕ (ਅਧਾਰ_name));
      ਵਾਪਸ;
    }

  ਜੇ (!comptypes (ਰੁੱਖ_TYPE (decl), ਰੁੱਖ_TYPE (ਅਧਾਰ_decl)))
    {
      error_at (DECL_ਸਰੋਤ_LOCATION (decl),
		"variant function definition does not match "
		"declaration of %qE", ਅਧਾਰ_decl);
      inform (DECL_ਸਰੋਤ_LOCATION (ਅਧਾਰ_decl),
	      "%qE declared here", ਅਧਾਰ_decl);
      ਵਾਪਸ;
    }

  /* Now set the attributes on the base and variant decls for the middle
     end.  */
  omp_check_for_duplicate_variant (DECL_ਸਰੋਤ_LOCATION (decl),
				   ਅਧਾਰ_decl, ctx);
  ਰੁੱਖ construct
    = omp_get_context_selector_list (ctx, OMP_TRAIT_ਸੈੱਟ_CONSTRUCT);
  omp_mark_declare_variant (DECL_ਸਰੋਤ_LOCATION (decl), decl, construct);
  ਰੁੱਖ attrs = DECL_ਗੁਣ (ਅਧਾਰ_decl);
  ਰੁੱਖ ਮੇਲ_loc_ਗੰਢ
    = maybe_wrap_with_location (integer_zero_ਗੰਢ,
				DECL_ਸਰੋਤ_LOCATION (ਅਧਾਰ_decl));
  ਰੁੱਖ loc_ਗੰਢ = ਰੁੱਖ_cons (ਮੇਲ_loc_ਗੰਢ, integer_zero_ਗੰਢ,
			     build_ਰੁੱਖ_list (ਮੇਲ_loc_ਗੰਢ,
					      integer_zero_ਗੰਢ));
  attrs = ਰੁੱਖ_cons (get_identifier ("omp declare variant base"),
		     ਰੁੱਖ_cons (decl, ctx, loc_ਗੰਢ), attrs);
  DECL_ਗੁਣ (ਅਧਾਰ_decl) = attrs;

  /* Variant functions are essentially anonymous and cannot be referenced
     outside the compilation unit.  */
  ਰੁੱਖ_ਜਨਤਕ (decl) = 0;
  DECL_COMDAT (decl) = 0;
}


/* D should be C_TOKEN_VEC from omp::decl attribute.  If it contains
   a threadprivate, groupprivate, allocate or declare target directive,
   return true and parse it for DECL.  */

ਤਾਰਕਿਕ
c_maybe_parse_omp_decl (ਰੁੱਖ decl, ਰੁੱਖ d)
{
  gcc_assert (ਰੁੱਖ_ਕੋਡ (d) == C_TOKEN_VEC);
  vec<c_token, va_gc> *toks = C_TOKEN_VEC_ਟੋਕਨ (d);
  c_token *ਪਹਿਲਾ = toks->ਪਤਾ ();
  c_token *ਆਖਰੀ = ਪਹਿਲਾ + toks->ਲੰਮਾਈ ();
  ਅਚਲ ਅੱਖਰ *directive[3] = {};
  ਲਈ (ਪੂਰਨ j = 0; j < 3; j++)
    {
      ਰੁੱਖ id = NULL_ਰੁੱਖ;
      ਜੇ (ਪਹਿਲਾ + j == ਆਖਰੀ)
	ਰੋਕੋ;
      ਜੇ (ਪਹਿਲਾ[j].type == CPP_NAME)
	id = ਪਹਿਲਾ[j].ਮੁੱਲ;
      ਨਹੀਂਤਾਂ ਜੇ (ਪਹਿਲਾ[j].type == CPP_KEYWORD)
	id = ridpointers[(ਪੂਰਨ) ਪਹਿਲਾ[j].keyword];
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
      directive[j] = IDENTIFIER_ਸੂਚਕ (id);
    }
  ਅਚਲ c_omp_directive *dir = ਨਿਰਾ;
  ਜੇ (directive[0])
    dir = c_omp_categorize_directive (directive[0], directive[1],
				      directive[2]);
  ਜੇ (dir == ਨਿਰਾ)
    {
      error_at (ਪਹਿਲਾ->location,
		"unknown OpenMP directive name in "
		"%qs attribute argument", "omp::decl");
      ਵਾਪਸ ਝੂਠ;
    }
  ਜੇ (dir->id != PRAGMA_OMP_THREADPRIVATE
      && dir->id != PRAGMA_OMP_GROUPPRIVATE
      && dir->id != PRAGMA_OMP_ALLOCATE
      && (dir->id != PRAGMA_OMP_DECLARE
	  || strcmp (directive[1], "target") != 0))
    ਵਾਪਸ ਝੂਠ;

  ਜੇ (!flag_openmp && !dir->simd)
    ਵਾਪਸ ਸੱਚ;

  c_parser *parser = the_parser;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਟੋਕਨ_avail = parser->ਟੋਕਨ_avail;
  gcc_assert (parser->ਟੋਕਨ == &parser->ਟੋਕਨ_buf[0]);
  toks = ਨਿਰਾ;
  vec_ਸੁਰੱਖਿਅਤ_reserve (toks, ਆਖਰੀ - ਪਹਿਲਾ + 2, ਸੱਚ);
  c_token tok = {};
  tok.type = CPP_PRAGMA;
  tok.keyword = RID_MAX;
  tok.pragma_ਕਿਸਮ = pragma_ਕਿਸਮ (dir->id);
  tok.location = ਪਹਿਲਾ->location;
  toks->ਤੇਜ਼_ਧੱਕੋ (tok);
  ਜਦੋਂ (++ਪਹਿਲਾ < ਆਖਰੀ)
    toks->ਤੇਜ਼_ਧੱਕੋ (*ਪਹਿਲਾ);
  tok = {};
  tok.type = CPP_PRAGMA_EOL;
  tok.keyword = RID_MAX;
  tok.location = ਆਖਰੀ[-1].location;
  toks->ਤੇਜ਼_ਧੱਕੋ (tok);
  tok = {};
  tok.type = CPP_EOF;
  tok.keyword = RID_MAX;
  tok.location = ਆਖਰੀ[-1].location;
  toks->ਤੇਜ਼_ਧੱਕੋ (tok);
  parser->ਵਿੱਚ_omp_decl_attribute = decl;
  gcc_assert (!parser->ਵਿੱਚ_omp_attribute_pragma);
  parser->ਵਿੱਚ_omp_attribute_pragma = ggc_alloc<omp_attribute_pragma_state> ();
  parser->ਵਿੱਚ_omp_attribute_pragma->token_vec = toks;
  parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ = parser->ਟੋਕਨ;
  parser->ਵਿੱਚ_omp_attribute_pragma->save_ਟੋਕਨ_avail = ਟੋਕਨ_avail;
  parser->ਟੋਕਨ = toks->ਪਤਾ ();
  parser->ਟੋਕਨ_avail = toks->ਲੰਮਾਈ ();
  c_parser_pragma (parser, pragma_external, ਨਿਰਾ, NULL_ਰੁੱਖ);
  parser->ਵਿੱਚ_omp_decl_attribute = NULL_ਰੁੱਖ;
  ਵਾਪਸ ਸੱਚ;
}

/* OpenMP 4.0:
   # pragma omp declare target new-line
   declarations and definitions
   # pragma omp end declare target new-line

   OpenMP 4.5:
   # pragma omp declare target ( extended-list ) new-line

   # pragma omp declare target declare-target-clauses[seq] new-line  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_DECLARE_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਮੰਜ਼ਿਲ)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ENTER)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LINK)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LOCAL)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਅਸਿੱਧਾ))

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_declare_ਨਿਸ਼ਾਨਾ (c_parser *parser)
{
  ਰੁੱਖ clauses = NULL_ਰੁੱਖ;
  ਪੂਰਨ device_type = 0;
  ਤਾਰਕਿਕ ਅਸਿੱਧਾ = ਝੂਠ;
  ਤਾਰਕਿਕ only_device_type_or_ਅਸਿੱਧਾ = ਸੱਚ;
  ਜੇ (flag_openmp)
    omp_requires_ਨਕਾਬ
      = (ਗਿਣਤੀ omp_requires) (omp_requires_ਨਕਾਬ | OMP_REQUIRES_ਨਿਸ਼ਾਨਾ_ਵਰਤਿਆ);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      || (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME))
    clauses = c_parser_omp_all_clauses (parser, OMP_DECLARE_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ,
					"#pragma omp declare target");
  ਨਹੀਂਤਾਂ ਜੇ (parser->ਵਿੱਚ_omp_decl_attribute
	   || c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
    {
      clauses = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ENTER,
					      clauses);
      clauses = c_ਅੰਤ_omp_clauses (clauses, C_ORT_OMP);
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
    }
  ਨਹੀਂਤਾਂ
    {
      warning_at (c_parser_peek_token (parser)->location,
		  OPT_Wdeprecated_openmp,
		  "use of %<omp declare target%> as a synonym for "
		  "%<omp begin declare target%> has been deprecated since "
		  "OpenMP 5.2");
      ਤਾਰਕਿਕ attr_syntax = parser->ਵਿੱਚ_omp_attribute_pragma != ਨਿਰਾ;
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      c_omp_declare_ਨਿਸ਼ਾਨਾ_attr attr = { attr_syntax, -1, 0 };
      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute, attr);
      ਵਾਪਸ;
    }
  ਲਈ (ਰੁੱਖ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEVICE_TYPE)
	device_type |= OMP_CLAUSE_DEVICE_TYPE_ਕਿਸਮ (c);
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਅਸਿੱਧਾ)
	ਅਸਿੱਧਾ |= !integer_zerop (OMP_CLAUSE_ਅਸਿੱਧਾ_ਵਿਅੰਜਕ (c));
    }
  ਲਈ (ਰੁੱਖ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
    {
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEVICE_TYPE
	  || OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਅਸਿੱਧਾ)
	ਜਾਰੀ;
      ਰੁੱਖ t = OMP_CLAUSE_DECL (c), id;
      ਰੁੱਖ at1 = lookup_attribute ("omp declare target", DECL_ਗੁਣ (t));
      ਰੁੱਖ at2 = lookup_attribute ("omp declare target link",
				   DECL_ਗੁਣ (t));
      only_device_type_or_ਅਸਿੱਧਾ = ਝੂਠ;
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_LINK)
	{
	  id = get_identifier ("omp declare target link");
	  std::ਅਦਲਾ_ਬਦਲੀ (at1, at2);
	}
      ਨਹੀਂਤਾਂ
	id = get_identifier ("omp declare target");
      ਜੇ (at2)
	{
	  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ENTER)
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and %qs"
		      " clauses", t, OMP_CLAUSE_ENTER_ਮੰਜ਼ਿਲ (c) ? "to" : "enter");
	  ਨਹੀਂਤਾਂ ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_LOCAL
		   || ਮੁੱਲ_member (get_identifier ("local"), ਰੁੱਖ_ਮੁੱਲ (at2)))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<local%> clauses", t);
	  ਨਹੀਂਤਾਂ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified both in declare target %<link%> and "
		      "%<to%> or %<enter%> clauses", t);
	  ਜਾਰੀ;
	}
      ਜੇ (!at1)
	{
	  DECL_ਗੁਣ (t) = ਰੁੱਖ_cons (id, NULL_ਰੁੱਖ, DECL_ਗੁਣ (t));
	  ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_LOCAL)
	    ਰੁੱਖ_ਮੁੱਲ (DECL_ਗੁਣ (t))
	      = ਰੁੱਖ_cons (NULL_ਰੁੱਖ, get_identifier ("local"),
			   ਰੁੱਖ_ਮੁੱਲ (DECL_ਗੁਣ (t)));

	  ਜੇ (ਰੁੱਖ_ਕੋਡ (t) != FUNCTION_DECL && !is_global_var (t))
	    ਜਾਰੀ;

	  symtab_ਗੰਢ *ਗੰਢ = symtab_ਗੰਢ::get (t);
	  ਜੇ (ਗੰਢ != ਨਿਰਾ)
	    {
	      ਗੰਢ->offloadable = 1;
	      ਜੇ (ENABLE_OFFLOADING)
		{
		  g->have_offload = ਸੱਚ;
		  ਜੇ (is_a <varpool_ਗੰਢ *> (ਗੰਢ)
		      && OMP_CLAUSE_ਕੋਡ (c) != OMP_CLAUSE_LOCAL)
		    vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (offload_vars, t);
		}
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  ਤਾਰਕਿਕ saw_local = ਮੁੱਲ_member (get_identifier ("local"),
					 ਰੁੱਖ_ਮੁੱਲ (at1));
	  ਜੇ (saw_local && OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ENTER)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%qs clauses", t,
			OMP_CLAUSE_ENTER_ਮੰਜ਼ਿਲ (c) ? "to" : "enter");
	      ਜਾਰੀ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (!saw_local && OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_LOCAL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD specified both in declare target %<local%> and "
			"%<to%> or %<enter%> clauses", t);
	      ਜਾਰੀ;
	    }
	}
      ਜੇ (ਰੁੱਖ_ਕੋਡ (t) != FUNCTION_DECL)
	ਜਾਰੀ;
      ਜੇ ((device_type & OMP_CLAUSE_DEVICE_TYPE_HOST) != 0)
	{
	  ਰੁੱਖ at3 = lookup_attribute ("omp declare target host",
				       DECL_ਗੁਣ (t));
	  ਜੇ (at3 == NULL_ਰੁੱਖ)
	    {
	      id = get_identifier ("omp declare target host");
	      DECL_ਗੁਣ (t)
		= ਰੁੱਖ_cons (id, NULL_ਰੁੱਖ, DECL_ਗੁਣ (t));
	    }
	}
      ਜੇ ((device_type & OMP_CLAUSE_DEVICE_TYPE_NOHOST) != 0)
	{
	  ਰੁੱਖ at3 = lookup_attribute ("omp declare target nohost",
				       DECL_ਗੁਣ (t));
	  ਜੇ (at3 == NULL_ਰੁੱਖ)
	    {
	      id = get_identifier ("omp declare target nohost");
	      DECL_ਗੁਣ (t)
		= ਰੁੱਖ_cons (id, NULL_ਰੁੱਖ, DECL_ਗੁਣ (t));
	    }
	}
      ਜੇ (ਅਸਿੱਧਾ)
	{
	  ਰੁੱਖ at4 = lookup_attribute ("omp declare target indirect",
				       DECL_ਗੁਣ (t));
	  ਜੇ (at4 == NULL_ਰੁੱਖ)
	    {
	      id = get_identifier ("omp declare target indirect");
	      DECL_ਗੁਣ (t)
		= ਰੁੱਖ_cons (id, NULL_ਰੁੱਖ, DECL_ਗੁਣ (t));
	    }
	}
    }
  ਜੇ ((device_type || ਅਸਿੱਧਾ) && only_device_type_or_ਅਸਿੱਧਾ)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "directive with only %<device_type%> or %<indirect%> clauses");
  ਜੇ (ਅਸਿੱਧਾ && device_type && device_type != OMP_CLAUSE_DEVICE_TYPE_ANY)
    error_at (OMP_CLAUSE_LOCATION (clauses),
	      "%<device_type%> clause must specify 'any' when used with "
	      "an %<indirect%> clause");
}

/* OpenMP 5.1
   #pragma omp begin assumes clauses[optseq] new-line

   #pragma omp begin declare target clauses[optseq] new-line

   #pragma omp begin declare variant match (context-selector) new-line  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_BEGIN_DECLARE_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ			\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਅਸਿੱਧਾ))

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_begin (c_parser *parser)
{
  ਅਚਲ ਅੱਖਰ *p = "";
  c_parser_consume_pragma (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
  ਜੇ (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  ਤਾਰਕਿਕ attr_syntax = parser->ਵਿੱਚ_omp_attribute_pragma != ਨਿਰਾ;
	  ਰੁੱਖ clauses
	    = c_parser_omp_all_clauses (parser,
					OMP_BEGIN_DECLARE_ਨਿਸ਼ਾਨਾ_CLAUSE_ਨਕਾਬ,
					"#pragma omp begin declare target");
	  ਪੂਰਨ device_type = 0;
	  ਪੂਰਨ ਅਸਿੱਧਾ = 0;
	  ਲਈ (ਰੁੱਖ c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
	    {
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_DEVICE_TYPE)
		device_type |= OMP_CLAUSE_DEVICE_TYPE_ਕਿਸਮ (c);
	      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_ਅਸਿੱਧਾ)
		ਅਸਿੱਧਾ |= !integer_zerop (OMP_CLAUSE_ਅਸਿੱਧਾ_ਵਿਅੰਜਕ (c));
	    }
	  c_omp_declare_ਨਿਸ਼ਾਨਾ_attr attr = { attr_syntax, device_type,
					     ਅਸਿੱਧਾ };
	  vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute, attr);
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ਅਚਲ ਅੱਖਰ *clause = "";
	  matching_parens parens;
	  location_t ਮੇਲ_loc = c_parser_peek_token (parser)->location;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	    {
	      ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
	      clause = IDENTIFIER_ਸੂਚਕ (id);
	    }
	  ਜੇ (strcmp (clause, "match") != 0)
	    {
	      c_parser_error (parser, "expected %<match%>");
	      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	      ਵਾਪਸ;
	    }

	  c_parser_consume_token (parser);

	  ਜੇ (!parens.require_open (parser))
	    {
	      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	      ਵਾਪਸ;
	    }

	  ਰੁੱਖ ctx =
	    c_parser_omp_context_selector_specification (parser, NULL_ਰੁੱਖ);
	  ਜੇ (ctx != error_mark_ਗੰਢ)
	    ctx = omp_check_context_selector (ਮੇਲ_loc, ctx,
					      OMP_CTX_BEGIN_DECLARE_VARIANT);

	  ਜੇ (ctx != error_mark_ਗੰਢ
	      && !vec_ਸੁਰੱਖਿਅਤ_is_ਖਾਲੀ_ਥਾਵਾਂ (current_omp_declare_variant_attribute))
	    {
	      c_omp_declare_variant_attr a
		= current_omp_declare_variant_attribute->ਆਖਰੀ ();
	      ਰੁੱਖ outer_ctx = a.selector;
	      ctx = omp_ਮਿਲਾਓ_context_selectors (ਮੇਲ_loc, outer_ctx, ctx,
						 OMP_CTX_BEGIN_DECLARE_VARIANT);
	    }

	  ਜੇ (ctx == error_mark_ਗੰਢ
	      || !omp_context_selector_matches (ctx, NULL_ਰੁੱਖ, ਝੂਠ, ਸੱਚ))
	    {
	      /* The context is either invalid or cannot possibly match.
		 In the latter case the spec says all code in the begin/end
		 sequence will be elided.  In the former case we'll get bogus
		 errors from trying to parse it without a valid context to
		 use for name-mangling, so elide that too.  */
	      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_omp_ਸਿਰਾ_declare_variant (parser);
	      ਵਾਪਸ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਤਾਰਕਿਕ attr_syntax = parser->ਵਿੱਚ_omp_attribute_pragma != ਨਿਰਾ;
	      c_omp_declare_variant_attr a = { attr_syntax, ctx };
	      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (current_omp_declare_variant_attribute, a);
	    }

	  parens.require_close (parser);
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      ਤਾਰਕਿਕ attr_syntax = parser->ਵਿੱਚ_omp_attribute_pragma != ਨਿਰਾ;
      c_parser_omp_assumption_clauses (parser, ਝੂਠ);
      ਬਣਤਰ c_omp_begin_assumes_ਅੰਕੜੇ a = { attr_syntax };
      vec_ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (current_omp_begin_assumes, a);
    }
  ਨਹੀਂਤਾਂ
    {
      c_parser_error (parser, "expected %<declare target%>, "
		      "%<declare variant%>, or %<assumes%>");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
    }
}

/* OpenMP 4.0
   #pragma omp end declare target

   OpenMP 5.1
   #pragma omp end assumes
   #pragma omp end declare variant  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_ਸਿਰਾ (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਅਚਲ ਅੱਖਰ *p = "";
  c_parser_consume_pragma (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
  ਜੇ (strcmp (p, "declare") == 0)
    {
      c_parser_consume_token (parser);
      p = "";
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  ਤਾਰਕਿਕ attr_syntax = parser->ਵਿੱਚ_omp_attribute_pragma != ਨਿਰਾ;
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	  ਜੇ (!vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute))
	    error_at (loc, "%<#pragma omp end declare target%> without "
		      "corresponding %<#pragma omp declare target%> or "
		      "%<#pragma omp begin declare target%>");
	  ਨਹੀਂਤਾਂ
	    {
	      c_omp_declare_ਨਿਸ਼ਾਨਾ_attr
		a = current_omp_declare_ਨਿਸ਼ਾਨਾ_attribute->ਕੱਢੋ ();
	      ਜੇ (a.attr_syntax != attr_syntax)
		{
		  ਜੇ (a.attr_syntax)
		    error_at (loc,
			      "%qs in attribute syntax terminated "
			      "with %qs in pragma syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		  ਨਹੀਂਤਾਂ
		    error_at (loc,
			      "%qs in pragma syntax terminated "
			      "with %qs in attribute syntax",
			      a.device_type >= 0 ? "begin declare target"
						 : "declare target",
			      "end declare target");
		}
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "variant") == 0)
	{
	  c_parser_consume_token (parser);
	  ਤਾਰਕਿਕ attr_syntax = parser->ਵਿੱਚ_omp_attribute_pragma != ਨਿਰਾ;
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	  ਜੇ (!vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (current_omp_declare_variant_attribute))
	    error_at (loc, "%<#pragma omp end declare variant%> without "
		      "corresponding %<#pragma omp begin declare variant%>");
	  ਨਹੀਂਤਾਂ
	    {
	      c_omp_declare_variant_attr
		a = current_omp_declare_variant_attribute->ਕੱਢੋ ();
	      ਜੇ (a.attr_syntax != attr_syntax)
		{
		  ਜੇ (a.attr_syntax)
		    error_at (loc,
			      "%<begin declare variant%> in attribute syntax "
			      "terminated with "
			      "%<end declare variant%> in pragma syntax");
		  ਨਹੀਂਤਾਂ
		    error_at (loc,
			      "%<begin declare variant%> in pragma syntax "
			      "terminated with "
			      "%<end declare variant%> in attribute syntax");
		}
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_error (parser, "expected %<target%> or %<variant%>");
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	  ਵਾਪਸ;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "assumes") == 0)
    {
      c_parser_consume_token (parser);
      ਤਾਰਕਿਕ attr_syntax = parser->ਵਿੱਚ_omp_attribute_pragma != ਨਿਰਾ;
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਜੇ (!vec_ਸੁਰੱਖਿਅਤ_ਲੰਮਾਈ (current_omp_begin_assumes))
	error_at (loc, "%qs without corresponding %qs",
		  "#pragma omp end assumes", "#pragma omp begin assumes");
      ਨਹੀਂਤਾਂ
	{
	  c_omp_begin_assumes_ਅੰਕੜੇ
	    a = current_omp_begin_assumes->ਕੱਢੋ ();
	  ਜੇ (a.attr_syntax != attr_syntax)
	    {
	      ਜੇ (a.attr_syntax)
		error_at (loc,
			  "%qs in attribute syntax terminated "
			  "with %qs in pragma syntax",
			  "begin assumes", "end assumes");
	      ਨਹੀਂਤਾਂ
		error_at (loc,
			  "%qs in pragma syntax terminated "
			  "with %qs in attribute syntax",
			  "begin assumes", "end assumes");
	    }
	}
    }
  ਨਹੀਂਤਾਂ
    {
      c_parser_error (parser, "expected %<declare%> or %<assumes%>");
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
    }
}

/* OpenMP 5.0
   #pragma omp declare mapper ([mapper-identifier :] type var) \
			      [clause [ [,] clause ] ... ] new-line  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_declare_mapper (c_parser *parser, ਗਿਣਤੀ pragma_context context)
{
  ਰੁੱਖ type, mapper_name = NULL_ਰੁੱਖ, var = NULL_ਰੁੱਖ, stmt, stmtlist;
  ਰੁੱਖ maplist = NULL_ਰੁੱਖ, mapper_id, mapper_decl, t;
  c_token *token;

  ਜੇ (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare mapper%> not at file or block scope");
      ਜਾਓ fail;
    }

  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ਜਾਓ fail;

  token = c_parser_peek_token (parser);

  ਜੇ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
    {
      ਚੋਣ (token->type)
	{
	ਹਾਲਤ CPP_NAME:
	  mapper_name = token->ਮੁੱਲ;
	  c_parser_consume_token (parser);
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_KEYWORD:
	  ਜੇ (token->keyword == RID_DEFAULT)
	    {
	      mapper_name = NULL_ਰੁੱਖ;
	      c_parser_consume_token (parser);
	      ਰੋਕੋ;
	    }
	  /* Fallthrough.  */
	ਮੂਲ:
	  error_at (token->location, "expected identifier or %<default%>");
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਵਾਪਸ;
	}

      ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	ਜਾਓ fail;
    }

  mapper_id = c_omp_mapper_id (mapper_name);
  mapper_decl = c_omp_mapper_decl (mapper_id);

  {
    location_t loc = c_parser_peek_token (parser)->location;
    ਬਣਤਰ c_type_name *ctype = c_parser_type_name (parser);
    type = groktypename (ctype, ਨਿਰਾ, ਨਿਰਾ);
    ਜੇ (type == error_mark_ਗੰਢ)
      ਜਾਓ fail;
    ਜੇ (!ਰਿਕਾਰਡ_OR_UNION_TYPE_P (type))
      {
	error_at (loc, "%qT is not a struct or union type in "
		  "%<#pragma omp declare mapper%>", type);
	c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	ਵਾਪਸ;
      }
    ਲਈ (ਰੁੱਖ t = DECL_INITIAL (mapper_decl); t; t = ਰੁੱਖ_CHAIN (t))
      ਜੇ (comptypes (ਰੁੱਖ_PURPOSE (t), type))
	{
	  error_at (loc, "redeclaration of %qs %<#pragma omp declare "
		    "mapper%> for type %qT", IDENTIFIER_ਸੂਚਕ (mapper_id)
		      + ਆਕਾਰ ("omp declare mapper ") - 1,
		    type);
	  ਰੁੱਖ prevmapper = ਰੁੱਖ_ਮੁੱਲ (t);
	  /* Hmm, this location might not be very accurate.  */
	  location_t ploc
	    = DECL_ਸਰੋਤ_LOCATION (OMP_DECLARE_MAPPER_DECL (prevmapper));
	  inform (ploc, "%<#pragma omp declare mapper%> "
			"previously declared here");
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਵਾਪਸ;
	}
  }

  token = c_parser_peek_token (parser);
  ਜੇ (token->type == CPP_NAME)
    {
      var = build_decl (token->location, VAR_DECL, token->ਮੁੱਲ, type);
      c_parser_consume_token (parser);
      DECL_ARTIFICIAL (var) = 1;
    }
  ਨਹੀਂਤਾਂ
    {
      error_at (token->location, "expected identifier");
      ਜਾਓ fail;
    }

  ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ਜਾਓ fail;

  ਧੱਕੋ_scope ();
  stmtlist = ਧੱਕੋ_stmt_list ();
  pushdecl (var);
  DECL_CONTEXT (var) = current_function_decl;

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      location_t ਇੱਥੇ;
      pragma_omp_clause c_ਕਿਸਮ;
      ਇੱਥੇ = c_parser_peek_token (parser)->location;
      c_ਕਿਸਮ = c_parser_omp_clause_name (parser);
      ਜੇ (c_ਕਿਸਮ != PRAGMA_OMP_CLAUSE_MAP)
	{
	  error_at (ਇੱਥੇ, "unexpected clause");
	  ਜਾਓ fail;
	}
      maplist = c_parser_omp_clause_map (parser, maplist, ਸੱਚ);
    }

  ਜੇ (maplist == NULL_ਰੁੱਖ)
    {
      error_at (ਨਿਵੇਸ਼_location, "missing %<map%> clause");
      ਜਾਓ fail;
    }
  ਰੁੱਖ list;
  ਲਈ (list = maplist; list; list = OMP_CLAUSE_CHAIN (list))
    {
      ਰੁੱਖ dvar = OMP_CLAUSE_DECL (list);
      ਜਦੋਂ (!DECL_P (dvar) && ਰੁੱਖ_ਸੰਕਾਰਜ_ਲੰਮਾਈ (dvar))
	dvar = ਰੁੱਖ_ਸੰਕਾਰਜ (dvar, 0);
      ਜੇ (dvar == var)
	ਰੋਕੋ;
    }
  ਜੇ (!list)
    error_at (ਨਿਵੇਸ਼_location, "at least one %<map%> clause must map %qD or an "
			      "element of it", var);

  stmt = make_ਗੰਢ (OMP_DECLARE_MAPPER);
  ਰੁੱਖ_TYPE (stmt) = type;
  OMP_DECLARE_MAPPER_ID (stmt) = mapper_name;
  OMP_DECLARE_MAPPER_DECL (stmt) = var;
  OMP_DECLARE_MAPPER_CLAUSES (stmt) = maplist;

  ਜੋੜੋ_stmt (stmt);

  ਕੱਢੋ_stmt_list (stmtlist);
  ਕੱਢੋ_scope ();

  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  t = ਰੁੱਖ_cons (type, stmt, DECL_INITIAL (mapper_decl));
  DECL_INITIAL (mapper_decl) = t;

  ਵਾਪਸ;

 fail:
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
}

/* OpenMP 4.0
   #pragma omp declare reduction (reduction-id : typename-list : expression) \
      initializer-clause[opt] new-line

   initializer-clause:
      initializer (omp_priv = initializer)
      initializer (function-name (argument-list))  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_declare_reduction (c_parser *parser, ਗਿਣਤੀ pragma_context context)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਟੋਕਨ_avail = 0, i;
  c_token *saved_ਟੋਕਨ = ਨਿਰਾ;
  vec<ਰੁੱਖ> types = vNULL;
  vec<c_token> clauses = vNULL;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 reduc_ਕੋਡ = ERROR_MARK;
  ਰੁੱਖ reduc_id = NULL_ਰੁੱਖ;
  ਰੁੱਖ type;
  location_t rloc = c_parser_peek_token (parser)->location;

  ਜੇ (context == pragma_struct || context == pragma_param)
    {
      error ("%<#pragma omp declare reduction%> not at file or block scope");
      ਜਾਓ fail;
    }

  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ਜਾਓ fail;

  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_PLUS:
      reduc_ਕੋਡ = PLUS_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_MULT:
      reduc_ਕੋਡ = MULT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_MINUS:
      reduc_ਕੋਡ = MINUS_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_AND:
      reduc_ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_XOR:
      reduc_ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_OR:
      reduc_ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_AND_AND:
      reduc_ਕੋਡ = TRUTH_ANDIF_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_OR_OR:
      reduc_ਕੋਡ = TRUTH_ORIF_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_NAME:
      ਅਚਲ ਅੱਖਰ *p;
      p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "min") == 0)
	{
	  reduc_ਕੋਡ = MIN_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	}
      ਜੇ (strcmp (p, "max") == 0)
	{
	  reduc_ਕੋਡ = MAX_ਵਿਅੰਜਕ;
	  ਰੋਕੋ;
	}
      reduc_id = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਰੋਕੋ;
    ਮੂਲ:
      c_parser_error (parser,
		      "expected %<+%>, %<*%>, %<-%>, %<&%>, "
		      "%<^%>, %<|%>, %<&&%>, %<||%> or identifier");
      ਜਾਓ fail;
    }

  ਰੁੱਖ orig_reduc_id, reduc_decl;
  orig_reduc_id = reduc_id;
  reduc_id = c_omp_reduction_id (reduc_ਕੋਡ, reduc_id);
  reduc_decl = c_omp_reduction_decl (reduc_id);
  c_parser_consume_token (parser);

  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
    ਜਾਓ fail;

  ਜਦੋਂ (ਸੱਚ)
    {
      location_t loc = c_parser_peek_token (parser)->location;
      ਬਣਤਰ c_type_name *ctype = c_parser_type_name (parser);
      ਜੇ (ctype != ਨਿਰਾ)
	{
	  type = groktypename (ctype, ਨਿਰਾ, ਨਿਰਾ);
	  ਜੇ (type == error_mark_ਗੰਢ)
	    ;
	  ਨਹੀਂਤਾਂ ਜੇ ((INTEGRAL_TYPE_P (type)
		    || SCALAR_FLOAT_TYPE_P (type)
		    || ਰੁੱਖ_ਕੋਡ (type) == COMPLEX_TYPE)
		   && orig_reduc_id == NULL_ਰੁੱਖ)
	    error_at (loc, "predeclared arithmetic type in "
			   "%<#pragma omp declare reduction%>");
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (type) == FUNCTION_TYPE
		   || ਰੁੱਖ_ਕੋਡ (type) == ARRAY_TYPE)
	    error_at (loc, "function or array type in "
		      "%<#pragma omp declare reduction%>");
	  ਨਹੀਂਤਾਂ ਜੇ (TYPE_ATOMIC (type))
	    error_at (loc, "%<_Atomic%> qualified type in "
			   "%<#pragma omp declare reduction%>");
	  ਨਹੀਂਤਾਂ ਜੇ (TYPE_QUALS_NO_ADDR_SPACE (type))
	    error_at (loc, "const, volatile or restrict qualified type in "
			   "%<#pragma omp declare reduction%>");
	  ਨਹੀਂਤਾਂ
	    {
	      ਰੁੱਖ t;
	      ਲਈ (t = DECL_INITIAL (reduc_decl); t; t = ਰੁੱਖ_CHAIN (t))
		ਜੇ (comptypes (ਰੁੱਖ_PURPOSE (t), type))
		  {
		    error_at (loc, "redeclaration of %qs "
				   "%<#pragma omp declare reduction%> for "
				   "type %qT",
				   IDENTIFIER_ਸੂਚਕ (reduc_id)
				   + ਆਕਾਰ ("omp declare reduction ") - 1,
				   type);
		    location_t ploc
		      = DECL_ਸਰੋਤ_LOCATION (ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t),
							    0));
		    inform (ploc, "%<#pragma omp declare reduction%> "
				  "previously declared here");
		    ਰੋਕੋ;
		  }
	      ਜੇ (t == NULL_ਰੁੱਖ)
		types.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (type);
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ਨਹੀਂਤਾਂ
	    ਰੋਕੋ;
	}
      ਨਹੀਂਤਾਂ
	ਰੋਕੋ;
    }

  ਜੇ (!c_parser_require (parser, CPP_COLON, "expected %<:%>")
      || types.is_ਖਾਲੀ_ਥਾਵਾਂ ())
    {
     fail:
      clauses.release ();
      types.release ();
      ਜਦੋਂ (ਸੱਚ)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ਜੇ (token->type == CPP_EOF || token->type == CPP_PRAGMA_EOL)
	    ਰੋਕੋ;
	  c_parser_consume_token (parser);
	}
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
      ਵਾਪਸ;
    }

  ਜੇ (types.ਲੰਮਾਈ () > 1)
    {
      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
	{
	  c_token *token = c_parser_peek_token (parser);
	  ਜੇ (token->type == CPP_EOF)
	    ਜਾਓ fail;
	  clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*token);
	  c_parser_consume_token (parser);
	}
      clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*c_parser_peek_token (parser));
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, ਆਕਾਰ (eof_token));
      eof_token.type = CPP_EOF;
      clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eof_token);
      clauses.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eof_token);
    }

  ਪੂਰਨ errs = errorcount;
  FOR_EACH_VEC_ELT (types, i, type)
    {
      saved_ਟੋਕਨ = parser->ਟੋਕਨ;
      ਟੋਕਨ_avail = parser->ਟੋਕਨ_avail;
      ਜੇ (!clauses.is_ਖਾਲੀ_ਥਾਵਾਂ ())
	{
	  parser->ਟੋਕਨ = clauses.ਪਤਾ ();
	  parser->ਟੋਕਨ_avail = clauses.ਲੰਮਾਈ ();
	  parser->ਵਿੱਚ_pragma = ਸੱਚ;
	}

      ਤਾਰਕਿਕ nested = current_function_decl != NULL_ਰੁੱਖ;
      ਜੇ (nested)
	c_ਧੱਕੋ_function_context ();
      ਰੁੱਖ fndecl = build_decl (BUILTINS_LOCATION, FUNCTION_DECL,
				reduc_id, default_function_type);
      current_function_decl = fndecl;
      allocate_struct_function (fndecl, ਸੱਚ);
      ਧੱਕੋ_scope ();
      ਰੁੱਖ stmt = ਧੱਕੋ_stmt_list ();
      /* Intentionally BUILTINS_LOCATION, so that -Wshadow doesn't
	 warn about these.  */
      ਰੁੱਖ omp_ਬਾਹਰਲਾ = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_out"), type);
      DECL_ARTIFICIAL (omp_ਬਾਹਰਲਾ) = 1;
      DECL_CONTEXT (omp_ਬਾਹਰਲਾ) = fndecl;
      pushdecl (omp_ਬਾਹਰਲਾ);
      ਰੁੱਖ omp_ਵਿੱਚ = build_decl (BUILTINS_LOCATION, VAR_DECL,
				get_identifier ("omp_in"), type);
      DECL_ARTIFICIAL (omp_ਵਿੱਚ) = 1;
      DECL_CONTEXT (omp_ਵਿੱਚ) = fndecl;
      pushdecl (omp_ਵਿੱਚ);
      ਬਣਤਰ c_ਵਿਅੰਜਕ combiner = c_parser_ਵਿਅੰਜਕ (parser);
      ਬਣਤਰ c_ਵਿਅੰਜਕ initializer;
      ਰੁੱਖ omp_priv = NULL_ਰੁੱਖ, omp_orig = NULL_ਰੁੱਖ;
      ਤਾਰਕਿਕ bad = ਝੂਠ;
      initializer.ਸੈੱਟ_error ();
      ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	bad = ਸੱਚ;
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	       && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);
      ਜੇ (!bad
	  && (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	      && strcmp (IDENTIFIER_ਸੂਚਕ
				(c_parser_peek_token (parser)->ਮੁੱਲ),
			  "initializer") == 0))
	{
	  c_parser_consume_token (parser);
	  ਕੱਢੋ_scope ();
	  ਧੱਕੋ_scope ();
	  omp_priv = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_priv"), type);
	  DECL_ARTIFICIAL (omp_priv) = 1;
	  DECL_INITIAL (omp_priv) = error_mark_ਗੰਢ;
	  DECL_CONTEXT (omp_priv) = fndecl;
	  pushdecl (omp_priv);
	  omp_orig = build_decl (BUILTINS_LOCATION, VAR_DECL,
				 get_identifier ("omp_orig"), type);
	  DECL_ARTIFICIAL (omp_orig) = 1;
	  DECL_CONTEXT (omp_orig) = fndecl;
	  pushdecl (omp_orig);
	  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    bad = ਸੱਚ;
	  ਨਹੀਂਤਾਂ ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected %<omp_priv%> or "
				      "function-name");
	      bad = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ
				(c_parser_peek_token (parser)->ਮੁੱਲ),
			   "omp_priv") != 0)
	    {
	      ਜੇ (c_parser_peek_2nd_token (parser)->type != CPP_OPEN_PAREN
		  || c_parser_peek_token (parser)->id_ਕਿਸਮ != C_ID_ID)
		{
		  c_parser_error (parser, "expected function-name %<(%>");
		  bad = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ
		initializer = c_parser_postfix_ਵਿਅੰਜਕ (parser);
	      ਜੇ (initializer.ਮੁੱਲ
		  && ਰੁੱਖ_ਕੋਡ (initializer.ਮੁੱਲ) == CALL_ਵਿਅੰਜਕ)
		{
		  ਪੂਰਨ j;
		  ਰੁੱਖ c = initializer.ਮੁੱਲ;
		  ਲਈ (j = 0; j < call_ਵਿਅੰਜਕ_nargs (c); j++)
		    {
		      ਰੁੱਖ a = CALL_ਵਿਅੰਜਕ_ARG (c, j);
		      STRIP_NOPS (a);
		      ਜੇ (ਰੁੱਖ_ਕੋਡ (a) == ADDR_ਵਿਅੰਜਕ
			  && ਰੁੱਖ_ਸੰਕਾਰਜ (a, 0) == omp_priv)
			ਰੋਕੋ;
		    }
		  ਜੇ (j == call_ਵਿਅੰਜਕ_nargs (c))
		    error ("one of the initializer call arguments should be "
			   "%<&omp_priv%>");
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_consume_token (parser);
	      ਜੇ (!c_parser_require (parser, CPP_EQ, "expected %<=%>"))
		bad = ਸੱਚ;
	      ਨਹੀਂਤਾਂ
		{
		  ਰੁੱਖ st = ਧੱਕੋ_stmt_list ();
		  location_t loc = c_parser_peek_token (parser)->location;
		  rich_location richloc (ਸਤਰ_ਸਾਰਣੀ, loc);
		  ਸ਼ੁਰੂ_init (omp_priv, NULL_ਰੁੱਖ, ਝੂਠ, ਝੂਠ, &richloc);
		  ਬਣਤਰ c_ਵਿਅੰਜਕ init = c_parser_initializer (parser, omp_priv);
		  ਅੰਤ_init ();
		  ਅੰਤ_decl (omp_priv, loc, init.ਮੁੱਲ,
		      	       init.original_type, NULL_ਰੁੱਖ);
		  ਕੱਢੋ_stmt_list (st);
		}
	    }
	  ਜੇ (!bad
	      && !c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    bad = ਸੱਚ;
	}

      ਜੇ (!bad)
	{
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

	  ਰੁੱਖ t = ਰੁੱਖ_cons (type, make_ਰੁੱਖ_vec (omp_priv ? 6 : 3),
			      DECL_INITIAL (reduc_decl));
	  DECL_INITIAL (reduc_decl) = t;
	  DECL_ਸਰੋਤ_LOCATION (omp_ਬਾਹਰਲਾ) = rloc;
	  ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 0) = omp_ਬਾਹਰਲਾ;
	  ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 1) = omp_ਵਿੱਚ;
	  ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 2) = combiner.ਮੁੱਲ;
	  walk_ਰੁੱਖ (&combiner.ਮੁੱਲ, c_check_omp_declare_reduction_r,
		     &ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 0), ਨਿਰਾ);
	  ਜੇ (omp_priv)
	    {
	      DECL_ਸਰੋਤ_LOCATION (omp_priv) = rloc;
	      ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 3) = omp_priv;
	      ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 4) = omp_orig;
	      ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 5) = initializer.ਮੁੱਲ;
	      walk_ਰੁੱਖ (&initializer.ਮੁੱਲ, c_check_omp_declare_reduction_r,
			 &ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 3), ਨਿਰਾ);
	      walk_ਰੁੱਖ (&DECL_INITIAL (omp_priv),
			 c_check_omp_declare_reduction_r,
			 &ਰੁੱਖ_VEC_ELT (ਰੁੱਖ_ਮੁੱਲ (t), 3), ਨਿਰਾ);
	    }
	}

      ਕੱਢੋ_stmt_list (stmt);
      ਕੱਢੋ_scope ();
      ਜੇ (cfun->language != ਨਿਰਾ)
	{
	  ggc_free (cfun->language);
	  cfun->language = ਨਿਰਾ;
	}
      ਸੈੱਟ_cfun (ਨਿਰਾ);
      current_function_decl = NULL_ਰੁੱਖ;
      ਜੇ (nested)
	c_ਕੱਢੋ_function_context ();

      ਜੇ (!clauses.is_ਖਾਲੀ_ਥਾਵਾਂ ())
	{
	  parser->ਟੋਕਨ = saved_ਟੋਕਨ;
	  parser->ਟੋਕਨ_avail = ਟੋਕਨ_avail;
	}
      ਜੇ (bad)
	ਜਾਓ fail;
      ਜੇ (errs != errorcount)
	ਰੋਕੋ;
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

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_declare (c_parser *parser, ਗਿਣਤੀ pragma_context context)
{
  c_parser_consume_pragma (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "simd") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  ਵਾਪਸ ਸੱਚ;
	}
      ਜੇ (strcmp (p, "reduction") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_reduction (parser, context);
	  ਵਾਪਸ ਝੂਠ;
	}
      ਜੇ (strcmp (p, "mapper") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_mapper (parser, context);
	  ਵਾਪਸ ਝੂਠ;
	}
      ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	{
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਵਾਪਸ ਝੂਠ;
	}
      ਜੇ (strcmp (p, "target") == 0)
	{
	  c_parser_consume_token (parser);
	  c_parser_omp_declare_ਨਿਸ਼ਾਨਾ (parser);
	  ਵਾਪਸ ਝੂਠ;
	}
      ਜੇ (strcmp (p, "variant") == 0)
	{
	  /* c_parser_consume_token (parser); done in
	     c_parser_omp_declare_simd.  */
	  c_parser_omp_declare_simd (parser, context);
	  ਵਾਪਸ ਸੱਚ;
	}
    }

  c_parser_error (parser, "expected %<simd%>, %<reduction%>, "
			  "%<target%> or %<variant%>");
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
  ਵਾਪਸ ਝੂਠ;
}

/* OpenMP 5.0
   #pragma omp requires clauses[optseq] new-line  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_requires (c_parser *parser)
{
  ਗਿਣਤੀ omp_requires new_req = (ਗਿਣਤੀ omp_requires) 0;

  c_parser_consume_pragma (parser);

  location_t loc = c_parser_peek_token (parser)->location;
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  ਅਚਲ ਅੱਖਰ *p
	    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	  location_t cloc = c_parser_peek_token (parser)->location;
	  ਗਿਣਤੀ omp_requires this_req = (ਗਿਣਤੀ omp_requires) 0;

	  ਜੇ (!strcmp (p, "unified_address"))
	    this_req = OMP_REQUIRES_UNIFIED_ਪਤਾ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "unified_shared_memory"))
	    this_req = OMP_REQUIRES_UNIFIED_SHARED_ਸਮ੍ਰਿਤੀ;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "self_maps"))
	    this_req = OMP_REQUIRES_SELF_MAPS;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "dynamic_allocators"))
	    this_req = OMP_REQUIRES_DYNAMIC_ALLOCATORS;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "reverse_offload"))
	    this_req = OMP_REQUIRES_ਉਲਟ_OFFLOAD;
	  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "atomic_default_mem_order"))
	    {
	      c_parser_consume_token (parser);

	      matching_parens parens;
	      ਜੇ (parens.require_open (parser))
		{
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		    {
		      ਰੁੱਖ v = c_parser_peek_token (parser)->ਮੁੱਲ;
		      p = IDENTIFIER_ਸੂਚਕ (v);

		      ਜੇ (!strcmp (p, "seq_cst"))
			this_req
			  = (ਗਿਣਤੀ omp_requires) OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_SEQ_CST;
		      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "relaxed"))
			this_req
			  = (ਗਿਣਤੀ omp_requires) OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELAXED;
		      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "release"))
			this_req
			  = (ਗਿਣਤੀ omp_requires) OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_RELEASE;
		      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "acq_rel"))
			this_req
			  = (ਗਿਣਤੀ omp_requires) OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQ_REL;
		      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "acquire"))
			this_req
			  = (ਗਿਣਤੀ omp_requires) OMP_ਸਮ੍ਰਿਤੀ_ਕ੍ਰਮ_ACQUIRE;
		    }
		  ਜੇ (this_req == 0)
		    {
		      error_at (c_parser_peek_token (parser)->location,
				"expected %<acq_rel%>, %<acquire%>, "
				"%<relaxed%>, %<release%> or %<seq_cst%>");
		      ਚੋਣ (c_parser_peek_token (parser)->type)
			{
			ਹਾਲਤ CPP_EOF:
			ਹਾਲਤ CPP_PRAGMA_EOL:
			ਹਾਲਤ CPP_CLOSE_PAREN:
			  ਰੋਕੋ;
			ਮੂਲ:
			  ਜੇ (c_parser_peek_2nd_token (parser)->type
			      == CPP_CLOSE_PAREN)
			    c_parser_consume_token (parser);
			  ਰੋਕੋ;
			}
		    }
		  ਨਹੀਂਤਾਂ
		    c_parser_consume_token (parser);

		  parens.skip_until_ਮਿਲਿਆ_close (parser);
		  ਜੇ (this_req == 0)
		    {
		      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
		      ਵਾਪਸ;
		    }
		}
	      p = ਨਿਰਾ;
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      error_at (cloc, "expected %<unified_address%>, "
			      "%<unified_shared_memory%>, "
			      "%<self_maps%>, "
			      "%<dynamic_allocators%>, "
			       "%<reverse_offload%> "
			       "or %<atomic_default_mem_order%> clause");
	      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	      ਵਾਪਸ;
	    }
	  ਜੇ (p)
	    c_parser_consume_token (parser);
	  ਜੇ (this_req)
	    {
	      ਜੇ ((this_req & ~OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ਕ੍ਰਮ) != 0)
		{
		  ਜੇ ((this_req & new_req) != 0)
		    error_at (cloc, "too many %qs clauses", p);
		  ਜੇ (this_req != OMP_REQUIRES_DYNAMIC_ALLOCATORS
		      && (omp_requires_ਨਕਾਬ & OMP_REQUIRES_ਨਿਸ਼ਾਨਾ_ਵਰਤਿਆ) != 0)
		    error_at (cloc, "%qs clause used lexically after first "
				    "target construct or offloading API", p);
		}
	      ਨਹੀਂਤਾਂ ਜੇ ((new_req & OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ਕ੍ਰਮ) != 0)
		{
		  error_at (cloc, "too many %qs clauses",
			    "atomic_default_mem_order");
		  this_req = (ਗਿਣਤੀ omp_requires) 0;
		}
	      ਨਹੀਂਤਾਂ ਜੇ ((omp_requires_ਨਕਾਬ
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ਕ੍ਰਮ) != 0)
		{
		  error_at (cloc, "more than one %<atomic_default_mem_order%>"
				  " clause in a single compilation unit");
		  this_req
		    = (ਗਿਣਤੀ omp_requires)
		       (omp_requires_ਨਕਾਬ
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ਕ੍ਰਮ);
		}
	      ਨਹੀਂਤਾਂ ਜੇ ((omp_requires_ਨਕਾਬ
			& OMP_REQUIRES_ATOMIC_DEFAULT_MEM_ਕ੍ਰਮ_ਵਰਤਿਆ) != 0)
		error_at (cloc, "%<atomic_default_mem_order%> clause used "
				"lexically after first %<atomic%> construct "
				"without memory order clause");
	      new_req = (ਗਿਣਤੀ omp_requires) (new_req | this_req);
	      omp_requires_ਨਕਾਬ
		= (ਗਿਣਤੀ omp_requires) (omp_requires_ਨਕਾਬ | this_req);
	      ਜਾਰੀ;
	    }
	}
      ਰੋਕੋ;
    }
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  ਜੇ (new_req == 0)
    error_at (loc, "%<pragma omp requires%> requires at least one clause");
}

/* Helper function for c_parser_omp_taskloop.
   Disallow zero sized or potentially zero sized task reductions.  */

ਸਥਿਰ ਰੁੱਖ
c_ਅੰਤ_taskloop_clauses (ਰੁੱਖ clauses)
{
  ਰੁੱਖ *pc = &clauses;
  ਲਈ (ਰੁੱਖ c = clauses; c; c = *pc)
    {
      ਤਾਰਕਿਕ remove = ਝੂਠ;
      ਜੇ (OMP_CLAUSE_ਕੋਡ (c) == OMP_CLAUSE_REDUCTION)
	{
	  ਰੁੱਖ type = strip_array_types (ਰੁੱਖ_TYPE (OMP_CLAUSE_DECL (c)));
	  ਜੇ (integer_zerop (TYPE_ਮਾਪ_UNIT (type)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"zero sized type %qT in %<reduction%> clause", type);
	      remove = ਸੱਚ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (TYPE_ਮਾਪ_UNIT (type)) != INTEGER_CST)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"variable sized type %qT in %<reduction%> clause",
			type);
	      remove = ਸੱਚ;
	    }
	}
      ਜੇ (remove)
	*pc = OMP_CLAUSE_CHAIN (c);
      ਨਹੀਂਤਾਂ
	pc = &OMP_CLAUSE_CHAIN (c);
    }
  ਵਾਪਸ clauses;
}

/* OpenMP 4.5:
   #pragma omp taskloop taskloop-clause[optseq] new-line
     for-loop

   #pragma omp taskloop simd taskloop-simd-clause[optseq] new-line
     for-loop  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_TASKLOOP_CLAUSE_ਨਕਾਬ				\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_SHARED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਨਿੱਜੀ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FIRSTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_LASTPRIVATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEFAULT)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_GRAINSIZE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਅੰਕ_TASKS)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_COLLAPSE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_UNTIED)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_IF)		\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_FINAL)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_MERGEABLE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_NOGROUP)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਤਰਜੀਹ)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ALLOCATE)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_REDUCTION)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਵਿੱਚ_REDUCTION))

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_taskloop (location_t loc, c_parser *parser,
		       ਅੱਖਰ *p_name, omp_clause_ਨਕਾਬ ਨਕਾਬ, ਰੁੱਖ *cclauses,
		       ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ clauses, ਖੰਡ, ret;

  strcat (p_name, " taskloop");
  ਨਕਾਬ |= OMP_TASKLOOP_CLAUSE_ਨਕਾਬ;
  /* #pragma omp parallel master taskloop{, simd} disallow in_reduction
     clause.  */
  ਜੇ ((ਨਕਾਬ & (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਅੰਕ_ਧਾਗੇ)) != 0)
    ਨਕਾਬ &= ~(OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਵਿੱਚ_REDUCTION);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);

      ਜੇ (strcmp (p, "simd") == 0)
	{
	  ਰੁੱਖ cclauses_buf[C_OMP_CLAUSE_ਵੰਡੋ_ਗਿਣਤੀ];
	  ਜੇ (cclauses == ਨਿਰਾ)
	    cclauses = cclauses_buf;
	  c_parser_consume_token (parser);
	  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
	    ਵਾਪਸ c_parser_omp_simd (loc, parser, p_name, ਨਕਾਬ, cclauses,
				      if_p);
	  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
	  ret = c_parser_omp_simd (loc, parser, p_name, ਨਕਾਬ, cclauses, if_p);
	  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
	  ਜੇ (ret == ਨਿਰਾ)
	    ਵਾਪਸ ret;
	  ret = make_ਗੰਢ (OMP_TASKLOOP);
	  ਰੁੱਖ_TYPE (ret) = void_type_ਗੰਢ;
	  OMP_FOR_BODY (ret) = ਖੰਡ;
	  OMP_FOR_CLAUSES (ret) = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_TASKLOOP];
	  OMP_FOR_CLAUSES (ret)
	    = c_ਅੰਤ_taskloop_clauses (OMP_FOR_CLAUSES (ret));
	  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret, loc);
	  ਜੋੜੋ_stmt (ret);
	  ਵਾਪਸ ret;
	}
    }
  ਜੇ (!flag_openmp)  /* flag_openmp_simd  */
    {
      c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
      ਵਾਪਸ NULL_ਰੁੱਖ;
    }

  clauses = c_parser_omp_all_clauses (parser, ਨਕਾਬ, p_name, cclauses == ਨਿਰਾ);
  ਜੇ (cclauses)
    {
      omp_ਵੰਡੋ_clauses (loc, OMP_TASKLOOP, ਨਕਾਬ, clauses, cclauses);
      clauses = cclauses[C_OMP_CLAUSE_ਵੰਡੋ_TASKLOOP];
    }

  clauses = c_ਅੰਤ_taskloop_clauses (clauses);
  ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ret = c_parser_omp_for_loop (loc, parser, OMP_TASKLOOP, clauses, ਨਿਰਾ, if_p);
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ ret;
}

/* OpenMP 5.1: Parse sizes list for "omp tile sizes"
   sizes ( size-expr-list ) */
ਸਥਿਰ ਰੁੱਖ
c_parser_omp_tile_sizes (c_parser *parser, location_t loc)
{
  ਰੁੱਖ sizes = NULL_ਰੁੱਖ;

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    c_parser_consume_token (parser);

  c_token *tok = c_parser_peek_token (parser);
  ਜੇ (tok->type != CPP_NAME
      || strcmp ("sizes", IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ)))
    {
      c_parser_error (parser, "expected %<sizes%>");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }
  c_parser_consume_token (parser);

  matching_parens parens;
  ਜੇ (!parens.require_open (parser))
    ਵਾਪਸ error_mark_ਗੰਢ;

  vec<ਰੁੱਖ, va_gc> *sizes_vec
    = c_parser_ਵਿਅੰਜਕ_list (parser, ਸੱਚ, ਸੱਚ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
  sizes = build_ਰੁੱਖ_list_vec (sizes_vec);
  release_ਰੁੱਖ_ਸਦਿਸ਼ (sizes_vec);

  ਲਈ (ਰੁੱਖ s = sizes; s; s = ਰੁੱਖ_CHAIN (s))
    {
      ਰੁੱਖ ਵਿਅੰਜਕ = ਰੁੱਖ_ਮੁੱਲ (s);
      ਜੇ (ਵਿਅੰਜਕ == error_mark_ਗੰਢ)
	{
	  parens.skip_until_ਮਿਲਿਆ_close (parser);
	  ਵਾਪਸ error_mark_ਗੰਢ;
	}

      HOST_WIDE_INT n;
      ਜੇ (!INTEGRAL_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
	  || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_shwi_p (ਵਿਅੰਜਕ)
	  || (n = ਰੁੱਖ_ਮੰਜ਼ਿਲ_shwi (ਵਿਅੰਜਕ)) <= 0
	  || (ਪੂਰਨ) n != n)
	{
	  c_parser_error (parser, "%<sizes%> argument needs positive"
				  " integral constant");
	  ਰੁੱਖ_ਮੁੱਲ (s) = integer_one_ਗੰਢ;
	}
    }
  parens.require_close (parser);

  gcc_assert (sizes);
  ਰੁੱਖ c = build_omp_clause (loc, OMP_CLAUSE_SIZES);
  OMP_CLAUSE_SIZES_LIST (c) = sizes;

  ਵਾਪਸ c;
}

/* OpenMP 5.1:
   #pragma omp tile sizes ( size-expr-list ) new-line
     for-loop

   LOC is the location of the #pragma token.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_tile (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ clauses = c_parser_omp_tile_sizes (parser, loc);
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  ਜੇ (!clauses || clauses == error_mark_ਗੰਢ)
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਰੁੱਖ ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ਰੁੱਖ ret = c_parser_omp_for_loop (loc, parser, OMP_TILE, clauses,
				    ਨਿਰਾ, if_p);
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ ret;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_UNROLL_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_PARTIAL)	\
	| (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_ਭਰਿਆ))

/* OpenMP 5.1
   #pragma omp unroll unroll-clause[optseq] new-line
     for-loop

   LOC is the location of the #pragma token.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_omp_unroll (location_t loc, c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਰੁੱਖ clauses = c_parser_omp_all_clauses (parser, OMP_UNROLL_CLAUSE_ਨਕਾਬ,
					   "#pragma omp unroll", ਸੱਚ);

  ਰੁੱਖ ਖੰਡ = c_begin_compound_stmt (ਸੱਚ);
  ਰੁੱਖ ret = c_parser_omp_for_loop (loc, parser, OMP_UNROLL, clauses,
				    ਨਿਰਾ, if_p);
  ਖੰਡ = c_ਸਿਰਾ_compound_stmt (loc, ਖੰਡ, ਸੱਚ);
  ਜੋੜੋ_stmt (ਖੰਡ);

  ਵਾਪਸ ret;
}

/* OpenMP 5.1
   #pragma omp nothing new-line  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_nothing (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp error clauses[optseq] new-line  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_omp_error (c_parser *parser, ਗਿਣਤੀ pragma_context context)
{
  ਪੂਰਨ at_compilation = -1;
  ਪੂਰਨ severity_fatal = -1;
  ਰੁੱਖ ਸੁਨੇਹਾ = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ bad = ਝੂਠ;
  location_t loc = c_parser_peek_token (parser)->location;

  c_parser_consume_pragma (parser);

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	ਰੋਕੋ;

      ਅਚਲ ਅੱਖਰ *p
	= IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      location_t cloc = c_parser_peek_token (parser)->location;
      ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਦਲੀਲਾਂ[] = {
	"execution", "compilation", "warning", "fatal"
      };
      ਪੂਰਨ *v = ਨਿਰਾ;
      ਪੂਰਨ idx = 0, n = -1;
      ਰੁੱਖ m = NULL_ਰੁੱਖ;

      ਜੇ (!strcmp (p, "at"))
	v = &at_compilation;
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "severity"))
	{
	  v = &severity_fatal;
	  idx += 2;
	}
      ਨਹੀਂਤਾਂ ਜੇ (strcmp (p, "message"))
	{
	  error_at (cloc,
		    "expected %<at%>, %<severity%> or %<message%> clause");
	  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
	  ਵਾਪਸ ਝੂਠ;
	}

      c_parser_consume_token (parser);

      matching_parens parens;
      ਜੇ (parens.require_open (parser))
	{
	  ਜੇ (v == ਨਿਰਾ)
	    {
	      location_t ਵਿਅੰਜਕ_loc = c_parser_peek_token (parser)->location;
	      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	      ਵਿਅੰਜਕ = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (ਵਿਅੰਜਕ_loc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ);
	      m = convert (const_string_type_ਗੰਢ, ਵਿਅੰਜਕ.ਮੁੱਲ);
	      m = c_fully_fold (m, ਝੂਠ, ਨਿਰਾ);
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		{
		  ਰੁੱਖ val = c_parser_peek_token (parser)->ਮੁੱਲ;
		  ਅਚਲ ਅੱਖਰ *q = IDENTIFIER_ਸੂਚਕ (val);

		  ਜੇ (!strcmp (q, ਦਲੀਲਾਂ[idx]))
		    n = 0;
		  ਨਹੀਂਤਾਂ ਜੇ (!strcmp (q, ਦਲੀਲਾਂ[idx + 1]))
		    n = 1;
		}
	      ਜੇ (n == -1)
		{
		  error_at (c_parser_peek_token (parser)->location,
			    "expected %qs or %qs", ਦਲੀਲਾਂ[idx], ਦਲੀਲਾਂ[idx + 1]);
		  bad = ਸੱਚ;
		  ਚੋਣ (c_parser_peek_token (parser)->type)
		    {
		    ਹਾਲਤ CPP_EOF:
		    ਹਾਲਤ CPP_PRAGMA_EOL:
		    ਹਾਲਤ CPP_CLOSE_PAREN:
		      ਰੋਕੋ;
		    ਮੂਲ:
		      ਜੇ (c_parser_peek_2nd_token (parser)->type
			  == CPP_CLOSE_PAREN)
			c_parser_consume_token (parser);
		      ਰੋਕੋ;
		    }
		}
	      ਨਹੀਂਤਾਂ
		c_parser_consume_token (parser);
	    }

	  parens.skip_until_ਮਿਲਿਆ_close (parser);

	  ਜੇ (v == ਨਿਰਾ)
	    {
	      ਜੇ (ਸੁਨੇਹਾ)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ
		ਸੁਨੇਹਾ = m;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (n != -1)
	    {
	      ਜੇ (*v != -1)
		{
		  error_at (cloc, "too many %qs clauses", p);
		  bad = ਸੱਚ;
		}
	      ਨਹੀਂਤਾਂ
		*v = n;
	    }
	}
      ਨਹੀਂਤਾਂ
	bad = ਸੱਚ;
    }
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
  ਜੇ (bad)
    ਵਾਪਸ ਸੱਚ;

  ਜੇ (at_compilation == -1)
    at_compilation = 1;
  ਜੇ (severity_fatal == -1)
    severity_fatal = 1;
  ਜੇ (!at_compilation)
    {
      ਜੇ (context != pragma_compound)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may only be used in compound statements");
	  ਵਾਪਸ ਸੱਚ;
	}
      ਜੇ (parser->omp_for_parse_state
	  && parser->omp_for_parse_state->ਵਿੱਚ_intervening_ਕੋਡ)
	{
	  error_at (loc, "%<#pragma omp error%> with %<at(execution)%> clause "
			 "may not be used in intervening code");
	  parser->omp_for_parse_state->fail = ਸੱਚ;
	  ਵਾਪਸ ਸੱਚ;
	}
      ਰੁੱਖ fndecl
	= builtin_decl_explicit (severity_fatal ? BUILT_ਵਿੱਚ_GOMP_ERROR
						: BUILT_ਵਿੱਚ_GOMP_WARNING);
      ਜੇ (!ਸੁਨੇਹਾ)
	ਸੁਨੇਹਾ = build_zero_cst (const_string_type_ਗੰਢ);
      ਰੁੱਖ stmt = build_call_ਵਿਅੰਜਕ_loc (loc, fndecl, 2, ਸੁਨੇਹਾ,
				       build_all_ones_cst (ਮਾਪ_type_ਗੰਢ));
      ਜੋੜੋ_stmt (stmt);
      ਵਾਪਸ ਸੱਚ;
    }
  ਅਚਲ ਅੱਖਰ *ਸੁਨੇਹਾ_2 = ਨਿਰਾ;
  ਜੇ (ਸੁਨੇਹਾ)
    {
      ਸੁਨੇਹਾ_2 = c_getstr (ਸੁਨੇਹਾ);
      ਜੇ (ਸੁਨੇਹਾ_2 == ਨਿਰਾ)
	ਸੁਨੇਹਾ_2 = _("<message unknown at compile time>");
    }
  ਅਚਲ ਗਿਣਤੀ diagnostics::ਕਿਸਮ diag_ਕਿਸਮ = (severity_fatal
					    ? diagnostics::ਕਿਸਮ::error
					    : diagnostics::ਕਿਸਮ::warning);
  ਜੇ (ਸੁਨੇਹਾ_2)
    emit_diagnostic (diag_ਕਿਸਮ, loc, 0,
		     "%<pragma omp error%> encountered: %s", ਸੁਨੇਹਾ_2);
  ਨਹੀਂਤਾਂ
    emit_diagnostic (diag_ਕਿਸਮ, loc, 0,
		     "%<pragma omp error%> encountered");
  ਵਾਪਸ ਝੂਠ;
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

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_assumption_clauses (c_parser *parser, ਤਾਰਕਿਕ is_assume)
{
  ਤਾਰਕਿਕ no_openmp = ਝੂਠ;
  ਤਾਰਕਿਕ no_openmp_constructs = ਝੂਠ;
  ਤਾਰਕਿਕ no_openmp_routines = ਝੂਠ;
  ਤਾਰਕਿਕ no_parallelism = ਝੂਠ;
  bitmap_ਸਿਰ absent_ਸਿਰ, ਸ਼ਾਮਲ_ਹੈ_ਸਿਰ;

  bitmap_obstack_initialize (ਨਿਰਾ);
  bitmap_initialize (&absent_ਸਿਰ, &bitmap_default_obstack);
  bitmap_initialize (&ਸ਼ਾਮਲ_ਹੈ_ਸਿਰ, &bitmap_default_obstack);

  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PRAGMA_EOL))
    error_at (c_parser_peek_token (parser)->location,
	      "expected at least one assumption clause");

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA)
	  && c_parser_peek_2nd_token (parser)->type == CPP_NAME)
	c_parser_consume_token (parser);

      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	ਰੋਕੋ;

      ਅਚਲ ਅੱਖਰ *p
	= IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      location_t cloc = c_parser_peek_token (parser)->location;

      ਜੇ (!strcmp (p, "no_openmp"))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (no_openmp)
	    error_at (cloc, "too many %qs clauses", "no_openmp");
	  no_openmp = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "no_openmp_constructs"))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (no_openmp_constructs)
	    error_at (cloc, "too many %qs clauses", "no_openmp_constructs");
	  no_openmp_constructs = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "no_openmp_routines"))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (no_openmp_routines)
	    error_at (cloc, "too many %qs clauses", "no_openmp_routines");
	  no_openmp_routines = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "no_parallelism"))
	{
	  c_parser_consume_token (parser);
	  ਜੇ (no_parallelism)
	    error_at (cloc, "too many %qs clauses", "no_parallelism");
	  no_parallelism = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "holds"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ਜੇ (parens.require_open (parser))
	    {
	      location_t eloc = c_parser_peek_token (parser)->location;
	      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ_no_commas (parser, ਨਿਰਾ);
	      ਰੁੱਖ t = convert_lvalue_ਮੰਜ਼ਿਲ_rvalue (eloc, ਵਿਅੰਜਕ, ਸੱਚ, ਸੱਚ).ਮੁੱਲ;
	      t = c_objc_common_truthvalue_conversion (eloc, t);
	      t = c_fully_fold (t, ਝੂਠ, ਨਿਰਾ);
	      ਜੇ (is_assume && t != error_mark_ਗੰਢ)
		{
		  ਰੁੱਖ fn = build_call_ਵਿਅੰਜਕ_ਅੰਦਰੂਨੀ_loc (eloc, IFN_ASSUME,
							  void_type_ਗੰਢ, 1,
							  t);
		  ਜੋੜੋ_stmt (fn);
		}
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (!strcmp (p, "absent") || !strcmp (p, "contains"))
	{
	  c_parser_consume_token (parser);
	  matching_parens parens;
	  ਜੇ (parens.require_open (parser))
	    {
	      ਕਰੋ
		{
		  ਅਚਲ ਅੱਖਰ *directive[3] = {};
		  ਪੂਰਨ i;
		  location_t dloc = c_parser_peek_token (parser)->location;
		  ਲਈ (i = 0; i < 3; i++)
		    {
		      ਰੁੱਖ id;
		      ਜੇ (c_parser_peek_nth_token (parser, i + 1)->type
			  == CPP_NAME)
			id = c_parser_peek_nth_token (parser, i + 1)->ਮੁੱਲ;
		      ਨਹੀਂਤਾਂ ਜੇ (c_parser_peek_nth_token (parser, i + 1)->keyword
			       != RID_MAX)
			{
			  ਗਿਣਤੀ rid rid
			    = c_parser_peek_nth_token (parser, i + 1)->keyword;
			  id = ridpointers[rid];
			}
		      ਨਹੀਂਤਾਂ
			ਰੋਕੋ;
		      directive[i] = IDENTIFIER_ਸੂਚਕ (id);
		    }
		  ਜੇ (i == 0)
		    error_at (dloc, "expected directive name");
		  ਨਹੀਂਤਾਂ
		    {
		      ਅਚਲ ਬਣਤਰ c_omp_directive *dir
			= c_omp_categorize_directive (directive[0],
						      directive[1],
						      directive[2]);
		      ਜੇ (dir
			  && dir->id != PRAGMA_OMP_ਸਿਰਾ
			  && (dir->ਕਿਸਮ == C_OMP_DIR_DECLARATIVE
			      || dir->ਕਿਸਮ == C_OMP_DIR_INFORMATIONAL
			      || dir->ਕਿਸਮ == C_OMP_DIR_META))
			error_at (dloc, "invalid OpenMP directive name in "
					"%qs clause argument: declarative, "
					"informational, and meta directives "
					"not permitted", p);
		      ਨਹੀਂਤਾਂ ਜੇ (dir == ਨਿਰਾ
			       || dir->id == PRAGMA_OMP_ਸਿਰਾ
			       || (!dir->ਦੂਜਾ && directive[1])
			       || (!dir->ਤੀਜਾ && directive[2]))
			error_at (dloc, "unknown OpenMP directive name in "
					"%qs clause argument", p);
		      ਨਹੀਂਤਾਂ
			{
			  ਪੂਰਨ id = dir - c_omp_directives;
			  ਜੇ (bitmap_ਦੋਆਧਾਰੀ_ਅੰਕ_p (p[0] == 'a' ? &ਸ਼ਾਮਲ_ਹੈ_ਸਿਰ
							: &absent_ਸਿਰ, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned in both %<absent%> and "
					    "%<contains%> clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "");
			  ਨਹੀਂਤਾਂ ਜੇ (!bitmap_ਸੈੱਟ_ਦੋਆਧਾਰੀ_ਅੰਕ (p[0] == 'a'
						    ? &absent_ਸਿਰ
						    : &ਸ਼ਾਮਲ_ਹੈ_ਸਿਰ, id))
			    error_at (dloc, "%<%s%s%s%s%s%> directive "
					    "mentioned multiple times in %qs "
					    "clauses",
				      directive[0],
				      directive[1] ? " " : "",
				      directive[1] ? directive[1] : "",
				      directive[2] ? " " : "",
				      directive[2] ? directive[2] : "", p);
			}
		      ਲਈ (; i; --i)
			c_parser_consume_token (parser);
		    }
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		    c_parser_consume_token (parser);
		  ਨਹੀਂਤਾਂ
		    ਰੋਕੋ;
		}
	      ਜਦੋਂ (1);
	      parens.skip_until_ਮਿਲਿਆ_close (parser);
	    }
	}
      ਨਹੀਂਤਾਂ ਜੇ (startswith (p, "ext_"))
	{
	  warning_at (cloc, OPT_Wopenmp, "unknown assumption clause %qs", p);
	  c_parser_consume_token (parser);
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
	    {
	      matching_parens parens;
	      parens.consume_open (parser);
	      c_parser_ਸੰਤੁਲਿਤ_token_sequence (parser);
	      parens.require_close (parser);
	    }
	}
      ਨਹੀਂਤਾਂ
	{
	  c_parser_consume_token (parser);
	  error_at (cloc, "expected assumption clause");
	  ਰੋਕੋ;
	}
    }
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
}

/* OpenMP 5.1
   #pragma omp assume clauses[optseq] new-line  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_assume (c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  c_parser_omp_assumption_clauses (parser, ਸੱਚ);
  ਜੋੜੋ_stmt (c_parser_omp_structured_ਖੰਡ (parser, if_p));
}

/* OpenMP 5.1
   #pragma omp assumes clauses[optseq] new-line  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_assumes (c_parser *parser)
{
  c_parser_consume_pragma (parser);
  c_parser_omp_assumption_clauses (parser, ਝੂਠ);
}

/* Helper function for c_parser_omp_metadirective.  */

ਸਥਿਰ ਖਾਲੀ
analyze_metadirective_body (c_parser *parser,
			    vec<c_token> &ਟੋਕਨ,
			    vec<ਰੁੱਖ> &labels)
{
  ਪੂਰਨ nesting_ਡੂੰਘਾਈ = 0;
  ਪੂਰਨ bracket_ਡੂੰਘਾਈ = 0;
  ਤਾਰਕਿਕ ignore_label = ਝੂਠ;

  /* Read in the body tokens to the tokens for each candidate directive.  */
  ਜਦੋਂ (1)
    {
      c_token *token = c_parser_peek_token (parser);
      ਤਾਰਕਿਕ stop = ਝੂਠ;

      ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_CASE))
	ignore_label = ਸੱਚ;

      ਚੋਣ (token->type)
	{
	ਹਾਲਤ CPP_EOF:
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_NAME:
	  ਜੇ (!ignore_label
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    labels.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (token->ਮੁੱਲ);
	  ਜਾਓ ਜੋੜੋ;
	ਹਾਲਤ CPP_OPEN_BRACE:
	  ++nesting_ਡੂੰਘਾਈ;
	  ਜਾਓ ਜੋੜੋ;
	ਹਾਲਤ CPP_CLOSE_BRACE:
	  ਜੇ (--nesting_ਡੂੰਘਾਈ == 0 && bracket_ਡੂੰਘਾਈ == 0)
	    stop = ਸੱਚ;
	  ਜਾਓ ਜੋੜੋ;
	ਹਾਲਤ CPP_OPEN_PAREN:
	  ++bracket_ਡੂੰਘਾਈ;
	  ਜਾਓ ਜੋੜੋ;
	ਹਾਲਤ CPP_CLOSE_PAREN:
	  --bracket_ਡੂੰਘਾਈ;
	  ਜਾਓ ਜੋੜੋ;
	ਹਾਲਤ CPP_COLON:
	  ignore_label = ਝੂਠ;
	  ਜਾਓ ਜੋੜੋ;
	ਹਾਲਤ CPP_SEMICOLON:
	  ਜੇ (nesting_ਡੂੰਘਾਈ == 0 && bracket_ਡੂੰਘਾਈ == 0)
	    stop = ਸੱਚ;
	  ਜਾਓ ਜੋੜੋ;
	ਮੂਲ:
	ਜੋੜੋ:
	  ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*token);
	  ਜੇ (token->type == CPP_PRAGMA)
	    c_parser_consume_pragma (parser);
	  ਨਹੀਂਤਾਂ ਜੇ (token->type == CPP_PRAGMA_EOL)
	    c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
	  ਨਹੀਂਤਾਂ
	    c_parser_consume_token (parser);
	  ਜੇ (stop)
	    ਰੋਕੋ;
	  ਜਾਰੀ;
	}
      ਰੋਕੋ;
    }
}

/* OpenMP 5.0:

  # pragma omp metadirective [clause[, clause]]
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_metadirective (c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ metadirective_region_ਗਿਣਤੀ = 0;

  ਰੁੱਖ ret;
  auto_vec<c_token> directive_ਟੋਕਨ;
  auto_vec<c_token> body_ਟੋਕਨ;
  auto_vec<ਰੁੱਖ> body_labels;
  auto_vec<ਅਚਲ ਬਣਤਰ c_omp_directive *> directives;
  auto_vec<ਰੁੱਖ> ctxs;
  vec<ਬਣਤਰ omp_variant> candidates;
  ਤਾਰਕਿਕ default_ਵੇਖਿਆ = ਝੂਠ;
  ਪੂਰਨ directive_token_idx = 0;
  ਰੁੱਖ standalone_body = NULL_ਰੁੱਖ;
  location_t pragma_loc = c_parser_peek_token (parser)->location;
  ਤਾਰਕਿਕ requires_body = ਝੂਠ;

  ret = make_ਗੰਢ (OMP_METADIRECTIVE);
  ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret, pragma_loc);
  ਰੁੱਖ_TYPE (ret) = void_type_ਗੰਢ;
  OMP_METADIRECTIVE_VARIANTS (ret) = NULL_ਰੁੱਖ;

  c_parser_consume_pragma (parser);
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	c_parser_consume_token (parser);
      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_NAME)
	  && c_parser_ਅਗਲਾ_token_is_not (parser, CPP_KEYWORD))
	{
	  c_parser_error (parser, "expected %<when%>, "
			  "%<otherwise%>, or %<default%> clause");
	  ਜਾਓ error;
	}

      location_t ਮੇਲ_loc = c_parser_peek_token (parser)->location;
      ਅਚਲ ਅੱਖਰ *p = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      ਜੇ (strcmp (p, "default") == 0)
	{
	  gcc_rich_location richloc (pragma_loc);
	  richloc.ਜੋੜੋ_fixit_replace (ਮੇਲ_loc, "otherwise");
	  warning_at (&richloc, OPT_Wdeprecated_openmp,
		      "%<default%> clause on metadirectives deprecated since "
		      "OpenMP 5.2, use %<otherwise%>");
	}
      c_parser_consume_token (parser);
      ਤਾਰਕਿਕ default_p
	= strcmp (p, "default") == 0 || strcmp (p, "otherwise") == 0;
      ਜੇ (default_p)
	{
	  ਜੇ (default_ਵੇਖਿਆ)
	    {
	      error_at (ਮੇਲ_loc, "too many %<otherwise%> or %<default%> "
			"clauses in %<metadirective%>");
	      ਜਾਓ error;
	    }
	  default_ਵੇਖਿਆ = ਸੱਚ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (default_ਵੇਖਿਆ)
	{
	  error_at (ਮੇਲ_loc, "%<otherwise%> or %<default%> clause "
		    "must appear last in %<metadirective%>");
	  ਜਾਓ error;
	}
      ਜੇ (!default_p && strcmp (p, "when") != 0)
	{
	  error_at (ਮੇਲ_loc, "%qs is not valid for %qs",
		    p, "metadirective");
	  ਜਾਓ error;
	}

      matching_parens parens;
      ਰੁੱਖ ctx = NULL_ਰੁੱਖ;
      ਤਾਰਕਿਕ skip = ਝੂਠ;

      ਜੇ (!parens.require_open (parser))
	ਜਾਓ error;

      ਜੇ (!default_p)
	{
	  ctx = c_parser_omp_context_selector_specification (parser,
							     NULL_ਰੁੱਖ);
	  ਜੇ (ctx == error_mark_ਗੰਢ)
	    ਜਾਓ error;
	  ctx = omp_check_context_selector (ਮੇਲ_loc, ctx,
					    OMP_CTX_METADIRECTIVE);
	  ਜੇ (ctx == error_mark_ਗੰਢ)
	    ਜਾਓ error;

	  /* Remove the selector from further consideration if it can be
	     evaluated as a non-match at this point.  */
	  skip = (omp_context_selector_matches (ctx, NULL_ਰੁੱਖ, ਝੂਠ) == 0);

	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_COLON))
	    {
	      c_parser_require (parser, CPP_COLON, "expected %<:%>");
	      ਜਾਓ error;
	    }
	  c_parser_consume_token (parser);
	}

      /* Read in the directive type and create a dummy pragma token for
	 it.  */
      location_t loc = c_parser_peek_token (parser)->location;

      ਅਚਲ ਅੱਖਰ *directive[3] = {};
      ਪੂਰਨ i;
      ਲਈ (i = 0; i < 3; i++)
	{
	  ਰੁੱਖ id;
	  ਜੇ (c_parser_peek_nth_token (parser, i + 1)->type
	      == CPP_CLOSE_PAREN)
	    {
	      ਜੇ (i == 0)
		directive[i++] = "nothing";
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_peek_nth_token (parser, i + 1)->type
		   == CPP_NAME)
	    id = c_parser_peek_nth_token (parser, i + 1)->ਮੁੱਲ;
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_peek_nth_token (parser, i + 1)->keyword
		   != RID_MAX)
	    {
	      ਗਿਣਤੀ rid rid
		= c_parser_peek_nth_token (parser, i + 1)->keyword;
	      id = ridpointers[rid];
	    }
	  ਨਹੀਂਤਾਂ
	    ਰੋਕੋ;

	  directive[i] = IDENTIFIER_ਸੂਚਕ (id);
	}
      ਜੇ (i == 0)
	{
	  error_at (loc, "expected directive name");
	  ਜਾਓ error;
	}

      ਅਚਲ ਬਣਤਰ c_omp_directive *omp_directive
	= c_omp_categorize_directive (directive[0],
				      directive[1],
				      directive[2]);

      ਜੇ (omp_directive == ਨਿਰਾ)
	{
	  ਲਈ (ਪੂਰਨ j = 0; j < i; j++)
	    c_parser_consume_token (parser);
	  c_parser_error (parser, "unknown directive name");
	  ਜਾਓ error;
	}
      ਨਹੀਂਤਾਂ
	{
	  ਪੂਰਨ token_ਗਿਣਤੀ = 0;
	  ਜੇ (omp_directive->ਪਹਿਲਾ) token_ਗਿਣਤੀ++;
	  ਜੇ (omp_directive->ਦੂਜਾ) token_ਗਿਣਤੀ++;
	  ਜੇ (omp_directive->ਤੀਜਾ) token_ਗਿਣਤੀ++;
	  ਲਈ (ਪੂਰਨ j = 0; j < token_ਗਿਣਤੀ; j++)
	    c_parser_consume_token (parser);
	}
      ਜੇ (omp_directive->id == PRAGMA_OMP_METADIRECTIVE)
	{
	  c_parser_error (parser,
			  "metadirectives cannot be used as variants of a "
			  "%<metadirective%>");
	  ਜਾਓ error;
	}
      ਜੇ (omp_directive->ਕਿਸਮ == C_OMP_DIR_DECLARATIVE)
	{
	  sorry_at (loc, "declarative directive variants of a "
			 "%<metadirective%> are not supported");
	  ਜਾਓ error;
	}
      ਜੇ (omp_directive->ਕਿਸਮ == C_OMP_DIR_CONSTRUCT)
	requires_body = ਸੱਚ;

      ਜੇ (!skip)
	{
	  c_token pragma_token;
	  pragma_token.type = CPP_PRAGMA;
	  pragma_token.location = loc;
	  pragma_token.pragma_ਕਿਸਮ = (ਗਿਣਤੀ pragma_ਕਿਸਮ) omp_directive->id;

	  directives.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (omp_directive);
	  directive_ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (pragma_token);
	  ctxs.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ctx);
	}

      /* Read in tokens for the directive clauses.  */
      ਪੂਰਨ nesting_ਡੂੰਘਾਈ = 0;
      ਜਦੋਂ (1)
	{
	  c_token *token = c_parser_peek_token (parser);
	  ਚੋਣ (token->type)
	    {
	    ਹਾਲਤ CPP_EOF:
	    ਹਾਲਤ CPP_PRAGMA_EOL:
	      ਰੋਕੋ;
	    ਹਾਲਤ CPP_OPEN_PAREN:
	      ++nesting_ਡੂੰਘਾਈ;
	      ਜਾਓ ਜੋੜੋ;
	    ਹਾਲਤ CPP_CLOSE_PAREN:
	      ਜੇ (nesting_ਡੂੰਘਾਈ-- == 0)
		{
		  c_parser_consume_token (parser);
		  ਰੋਕੋ;
		}
	      ਜਾਓ ਜੋੜੋ;
	    ਮੂਲ:
	    ਜੋੜੋ:
	      ਜੇ (!skip)
		directive_ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (*token);
	      c_parser_consume_token (parser);
	      ਜਾਰੀ;
	    }
	  ਰੋਕੋ;
	}

      ਜੇ (!skip)
	{
	  c_token eol_token;
	  memset (&eol_token, 0, ਆਕਾਰ (eol_token));
	  eol_token.type = CPP_PRAGMA_EOL;
	  directive_ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eol_token);
	}
    }
  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);

  /* If only one selector matches and it evaluates to 'omp nothing', no need to
     proceed.  */
  ਜੇ (ctxs.ਲੰਮਾਈ () == 1)
    {
      ਰੁੱਖ ctx = ctxs[0];
      ਜੇ (ctx == NULL_ਰੁੱਖ
	  || (omp_context_selector_matches (ctx, NULL_ਰੁੱਖ, ਝੂਠ) == 1
	      && directive_ਟੋਕਨ[0].pragma_ਕਿਸਮ == PRAGMA_OMP_NOTHING))
	ਵਾਪਸ;
    }

  ਜੇ (!default_ਵੇਖਿਆ)
    {
      /* Add a default clause that evaluates to 'omp nothing'.  */
      ਅਚਲ ਬਣਤਰ c_omp_directive *omp_directive
	= c_omp_categorize_directive ("nothing", ਨਿਰਾ, ਨਿਰਾ);

      c_token pragma_token;
      pragma_token.type = CPP_PRAGMA;
      pragma_token.location = UNKNOWN_LOCATION;
      pragma_token.pragma_ਕਿਸਮ = PRAGMA_OMP_NOTHING;

      directives.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (omp_directive);
      directive_ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (pragma_token);
      ctxs.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (NULL_ਰੁੱਖ);

      c_token eol_token;
      memset (&eol_token, 0, ਆਕਾਰ (eol_token));
      eol_token.type = CPP_PRAGMA_EOL;
      directive_ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eol_token);
    }

  ਜੇ (requires_body)
    analyze_metadirective_body (parser, body_ਟੋਕਨ, body_labels);

  /* Process each candidate directive.  */
  ਬਿਨਾਨਿਸ਼ਾਨੀ i;
  ਰੁੱਖ ctx;

  FOR_EACH_VEC_ELT (ctxs, i, ctx)
    {
      auto_vec<c_token> ਟੋਕਨ;

      /* Add the directive tokens.  */
      ਕਰੋ
	ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (directive_ਟੋਕਨ [directive_token_idx++]);
      ਜਦੋਂ (ਟੋਕਨ.ਆਖਰੀ ().type != CPP_PRAGMA_EOL);

      /* Add the body tokens.  */
      gcc_assert (requires_body || body_ਟੋਕਨ.is_ਖਾਲੀ_ਥਾਵਾਂ ());
      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ j = 0; j < body_ਟੋਕਨ.ਲੰਮਾਈ (); j++)
	ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (body_ਟੋਕਨ[j]);

      /* Make sure nothing tries to read past the end of the tokens.  */
      c_token eof_token;
      memset (&eof_token, 0, ਆਕਾਰ (eof_token));
      eof_token.type = CPP_EOF;
      ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eof_token);
      ਟੋਕਨ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (eof_token);

      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ old_ਟੋਕਨ_avail = parser->ਟੋਕਨ_avail;
      c_token *old_ਟੋਕਨ = parser->ਟੋਕਨ;
      ਬਣਤਰ omp_attribute_pragma_state *old_ਵਿੱਚ_omp_attribute_pragma
	= parser->ਵਿੱਚ_omp_attribute_pragma;
      ਬਣਤਰ omp_metadirective_parse_ਅੰਕੜੇ *old_state
	= parser->omp_metadirective_state;

      ਬਣਤਰ omp_metadirective_parse_ਅੰਕੜੇ new_state;
      new_state.body_labels = &body_labels;
      new_state.region_ਅੰਕ = ++metadirective_region_ਗਿਣਤੀ;

      parser->ਟੋਕਨ = ਟੋਕਨ.ਪਤਾ ();
      parser->ਟੋਕਨ_avail = ਟੋਕਨ.ਲੰਮਾਈ ();
      parser->ਵਿੱਚ_omp_attribute_pragma = ਨਿਰਾ;
      parser->omp_metadirective_state = &new_state;

      ਪੂਰਨ prev_errorcount = errorcount;
      ਰੁੱਖ directive = c_begin_compound_stmt (ਸੱਚ);

      c_parser_pragma (parser, pragma_compound, if_p, NULL_ਰੁੱਖ);
      directive = c_ਸਿਰਾ_compound_stmt (pragma_loc, directive, ਸੱਚ);
      ਤਾਰਕਿਕ standalone_p
	= directives[i]->ਕਿਸਮ == C_OMP_DIR_STANDALONE
	  || directives[i]->ਕਿਸਮ == C_OMP_DIR_UTILITY;
      ਜੇ (standalone_p && requires_body)
	{
	  /* Parsing standalone directives will not consume the body
	     tokens, so do that here.  */
	  ਜੇ (standalone_body == NULL_ਰੁੱਖ)
	    {
	      standalone_body = ਧੱਕੋ_stmt_list ();
	      c_parser_statement (parser, if_p); // TODO skip this
	      standalone_body = ਕੱਢੋ_stmt_list (standalone_body);
	    }
	  ਨਹੀਂਤਾਂ
	    c_parser_skip_ਮੰਜ਼ਿਲ_ਸਿਰਾ_ਦਾ_ਖੰਡ_or_statement (parser, ਸੱਚ);
	}

      ਰੁੱਖ body = standalone_p ? standalone_body : NULL_ਰੁੱਖ;
      ਰੁੱਖ variant = make_omp_metadirective_variant (ctx, directive, body);
      OMP_METADIRECTIVE_VARIANTS (ret)
	= chainon (OMP_METADIRECTIVE_VARIANTS (ret), variant);

      /* Check that all valid tokens have been consumed if no parse errors
	 encountered.  */
      ਜੇ (errorcount == prev_errorcount)
	{
	  gcc_assert (parser->ਟੋਕਨ_avail == 2);
	  gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_EOF));
	  gcc_assert (c_parser_peek_2nd_token (parser)->type == CPP_EOF);
	}

      parser->ਟੋਕਨ = old_ਟੋਕਨ;
      parser->ਟੋਕਨ_avail = old_ਟੋਕਨ_avail;
      parser->ਵਿੱਚ_omp_attribute_pragma = old_ਵਿੱਚ_omp_attribute_pragma;
      parser->omp_metadirective_state = old_state;
    }

  /* Try to resolve the metadirective early.  */
  candidates = omp_early_resolve_metadirective (ret);
  ਜੇ (!candidates.is_ਖਾਲੀ_ਥਾਵਾਂ ())
    ret = c_omp_expand_variant_construct (candidates);

  ਜੋੜੋ_stmt (ret);
  ਵਾਪਸ;

error:
  /* Skip the metadirective pragma.  Do not skip the metadirective body.  */
  ਜੇ (parser->ਵਿੱਚ_pragma)
    c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser, ਝੂਠ);
}

/* Main entry point to parsing most OpenMP pragmas.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_construct (c_parser *parser, ਤਾਰਕਿਕ *if_p)
{
  ਗਿਣਤੀ pragma_ਕਿਸਮ p_ਕਿਸਮ;
  location_t loc;
  ਰੁੱਖ stmt;
  ਅੱਖਰ p_name[ਆਕਾਰ "#pragma omp teams distribute parallel for simd"];
  omp_clause_ਨਕਾਬ ਨਕਾਬ (0);

  loc = c_parser_peek_token (parser)->location;
  p_ਕਿਸਮ = c_parser_peek_token (parser)->pragma_ਕਿਸਮ;
  c_parser_consume_pragma (parser);

  ਚੋਣ (p_ਕਿਸਮ)
    {
    ਹਾਲਤ PRAGMA_OACC_ATOMIC:
      c_parser_omp_atomic (loc, parser, ਸੱਚ);
      ਵਾਪਸ;
    ਹਾਲਤ PRAGMA_OACC_CACHE:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_cache (loc, parser);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_ਅੰਕੜੇ:
      stmt = c_parser_oacc_ਅੰਕੜੇ (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_HOST_ਅੰਕੜੇ:
      stmt = c_parser_oacc_host_ਅੰਕੜੇ (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_KERNELS:
    ਹਾਲਤ PRAGMA_OACC_PARALLEL:
    ਹਾਲਤ PRAGMA_OACC_SERIAL:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_compute (loc, parser, p_ਕਿਸਮ, p_name, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_LOOP:
      strcpy (p_name, "#pragma acc");
      stmt = c_parser_oacc_loop (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OACC_WAIT:
      strcpy (p_name, "#pragma wait");
      stmt = c_parser_oacc_wait (loc, parser, p_name);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (loc, parser, ਝੂਠ);
      ਵਾਪਸ;
    ਹਾਲਤ PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_DISTRIBUTE:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_distribute (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_FOR:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_for (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_LOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_loop (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_MASKED:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_masked (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_MASTER:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_master (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p,
				  UNKNOWN_LOCATION);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_PARALLEL:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_parallel (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_SCOPE:
      stmt = c_parser_omp_scope (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_SECTIONS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_sections (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_SIMD:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_simd (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_TASK:
      stmt = c_parser_omp_task (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_TASKGROUP:
      stmt = c_parser_omp_taskgroup (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_TASKLOOP:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_taskloop (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_TEAMS:
      strcpy (p_name, "#pragma omp");
      stmt = c_parser_omp_teams (loc, parser, p_name, ਨਕਾਬ, ਨਿਰਾ, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_ASSUME:
      c_parser_omp_assume (parser, if_p);
      ਵਾਪਸ;
    ਹਾਲਤ PRAGMA_OMP_TILE:
      stmt = c_parser_omp_tile (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_UNROLL:
      stmt = c_parser_omp_unroll (loc, parser, if_p);
      ਰੋਕੋ;
    ਹਾਲਤ PRAGMA_OMP_DISPATCH:
      stmt = c_parser_omp_dispatch (loc, parser);
      ਰੋਕੋ;
    ਮੂਲ:
      gcc_unreachable ();
    }

  ਜੇ (stmt && stmt != error_mark_ਗੰਢ)
    gcc_assert (ਵਿਅੰਜਕ_LOCATION (stmt) != UNKNOWN_LOCATION);
}

/* OpenMP 6.0:
   # pragma omp groupprivate (variable-list) [device_type(...)]  */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OMP_GROUPPRIVATE_CLAUSE_ਨਕਾਬ					\
	( (OMP_CLAUSE_ਨਕਾਬ_1 << PRAGMA_OMP_CLAUSE_DEVICE_TYPE) )

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_groupprivate (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  c_parser_consume_pragma (parser);
  ਰੁੱਖ vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ਨਿਰਾ);
  ਰੁੱਖ clauses = c_parser_omp_all_clauses (parser, OMP_GROUPPRIVATE_CLAUSE_ਨਕਾਬ,
					   "#pragma omp groupprivate");
  /* TODO: Implies 'declare target local' with specified device_type, check for
     conflicts.  Check for other restrictions.  */
  (ਖਾਲੀ) vars;
  (ਖਾਲੀ) clauses;
  sorry_at (loc, "%<omp groupprivate%>");
}

/* OpenMP 2.5:
   # pragma omp threadprivate (variable-list) */

ਸਥਿਰ ਖਾਲੀ
c_parser_omp_threadprivate (c_parser *parser)
{
  ਰੁੱਖ vars, t;
  location_t loc;

  c_parser_consume_pragma (parser);
  vars = c_parser_omp_var_list_parens (parser, OMP_CLAUSE_ERROR, ਨਿਰਾ);

  /* Mark every variable in VARS to be assigned thread local storage.  */
  ਲਈ (t = vars; t; t = ਰੁੱਖ_CHAIN (t))
    {
      ਰੁੱਖ v = ਰੁੱਖ_PURPOSE (t);
      loc = ਵਿਅੰਜਕ_LOCATION (ਰੁੱਖ_ਮੁੱਲ (t));

      /* If V had already been marked threadprivate, it doesn't matter
	 whether it had been used prior to this point.  */
      ਜੇ (!VAR_P (v))
	error_at (loc, "%qD is not a variable", v);
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਵਰਤਿਆ (v) && !C_DECL_THREADPRIVATE_P (v))
	error_at (loc, "%qE declared %<threadprivate%> after first use", v);
      ਨਹੀਂਤਾਂ ਜੇ (! is_global_var (v))
	error_at (loc, "automatic variable %qE cannot be %<threadprivate%>", v);
      ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_TYPE (v) == error_mark_ਗੰਢ)
	;
      ਨਹੀਂਤਾਂ ਜੇ (! COMPLETE_TYPE_P (ਰੁੱਖ_TYPE (v)))
	error_at (loc, "%<threadprivate%> %qE has incomplete type", v);
      ਨਹੀਂਤਾਂ
	{
	  ਜੇ (! DECL_THREAD_LOCAL_P (v))
	    {
	      ਸੈੱਟ_decl_tls_model (v, decl_default_tls_model (v));
	      /* If rtl has been already set for this var, call
		 make_decl_rtl once again, so that encode_section_info
		 has a chance to look at the new decl flags.  */
	      ਜੇ (DECL_RTL_ਸੈੱਟ_P (v))
		make_decl_rtl (v);
	    }
	  C_DECL_THREADPRIVATE_P (v) = 1;
	}
    }

  c_parser_skip_ਮੰਜ਼ਿਲ_pragma_eol (parser);
}

/* Parse a transaction attribute (GCC Extension).

   transaction-attribute:
     gnu-attributes
     attribute-specifier
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_transaction_ਗੁਣ (c_parser *parser)
{
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ATTRIBUTE))
    ਵਾਪਸ c_parser_gnu_ਗੁਣ (parser);

  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_ਵਰਗਫਲ))
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਵਾਪਸ c_parser_std_attribute_specifier (parser, ਸੱਚ);
}

/* Parse a __transaction_atomic or __transaction_relaxed statement
   (GCC Extension).

   transaction-statement:
     __transaction_atomic transaction-attribute[opt] compound-statement
     __transaction_relaxed compound-statement

   Note that the only valid attribute is: "outer".
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_transaction (c_parser *parser, ਗਿਣਤੀ rid keyword)
{
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ old_ਵਿੱਚ = parser->ਵਿੱਚ_transaction;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ this_ਵਿੱਚ = 1, new_ਵਿੱਚ;
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ stmt, attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_ਅਗਲਾ_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  ਜੇ (keyword == RID_TRANSACTION_RELAXED)
    this_ਵਿੱਚ |= TM_STMT_ATTR_RELAXED;
  ਨਹੀਂਤਾਂ
    {
      attrs = c_parser_transaction_ਗੁਣ (parser);
      ਜੇ (attrs)
	this_ਵਿੱਚ |= parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER);
    }

  /* Keep track if we're in the lexical scope of an outer transaction.  */
  new_ਵਿੱਚ = this_ਵਿੱਚ | (old_ਵਿੱਚ & TM_STMT_ATTR_OUTER);

  parser->ਵਿੱਚ_transaction = new_ਵਿੱਚ;
  stmt = c_parser_compound_statement (parser);
  parser->ਵਿੱਚ_transaction = old_ਵਿੱਚ;

  ਜੇ (flag_tm)
    stmt = c_ਅੰਤ_transaction (loc, stmt, this_ਵਿੱਚ);
  ਨਹੀਂਤਾਂ
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  ਵਾਪਸ stmt;
}

/* Parse a __transaction_atomic or __transaction_relaxed expression
   (GCC Extension).

   transaction-expression:
     __transaction_atomic ( expression )
     __transaction_relaxed ( expression )
*/

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_transaction_ਵਿਅੰਜਕ (c_parser *parser, ਗਿਣਤੀ rid keyword)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ old_ਵਿੱਚ = parser->ਵਿੱਚ_transaction;
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ this_ਵਿੱਚ = 1;
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ attrs;

  gcc_assert ((keyword == RID_TRANSACTION_ATOMIC
      || keyword == RID_TRANSACTION_RELAXED)
      && c_parser_ਅਗਲਾ_token_is_keyword (parser, keyword));
  c_parser_consume_token (parser);

  ਜੇ (keyword == RID_TRANSACTION_RELAXED)
    this_ਵਿੱਚ |= TM_STMT_ATTR_RELAXED;
  ਨਹੀਂਤਾਂ
    {
      attrs = c_parser_transaction_ਗੁਣ (parser);
      ਜੇ (attrs)
	this_ਵਿੱਚ |= parse_tm_stmt_attr (attrs, 0);
    }

  parser->ਵਿੱਚ_transaction = this_ਵਿੱਚ;
  matching_parens parens;
  ਜੇ (parens.require_open (parser))
    {
      ਰੁੱਖ ਵਿਅੰਜਕ = c_parser_ਵਿਅੰਜਕ (parser).ਮੁੱਲ;
      ret.original_type = ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ);
      ret.ਮੁੱਲ = build1 (TRANSACTION_ਵਿਅੰਜਕ, ret.original_type, ਵਿਅੰਜਕ);
      ਜੇ (this_ਵਿੱਚ & TM_STMT_ATTR_RELAXED)
	TRANSACTION_ਵਿਅੰਜਕ_RELAXED (ret.ਮੁੱਲ) = 1;
      ਸੈੱਟ_ਵਿਅੰਜਕ_LOCATION (ret.ਮੁੱਲ, loc);
      ret.original_ਕੋਡ = TRANSACTION_ਵਿਅੰਜਕ;
      ret.m_decimal = 0;
      ਜੇ (!parens.require_close (parser))
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, ਨਿਰਾ);
	  ਜਾਓ error;
	}
    }
  ਨਹੀਂਤਾਂ
    {
     error:
      ret.ਸੈੱਟ_error ();
      ret.original_ਕੋਡ = ERROR_MARK;
      ret.original_type = ਨਿਰਾ;
    }
  parser->ਵਿੱਚ_transaction = old_ਵਿੱਚ;

  ਜੇ (!flag_tm)
    error_at (loc,
	      keyword == RID_TRANSACTION_ATOMIC
	      ? G_("%<__transaction_atomic%> without transactional memory "
		   "support enabled")
	      : G_("%<__transaction_relaxed%> without transactional memory "
		   "support enabled"));

  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ret, loc, loc);

  ਵਾਪਸ ret;
}

/* Parse a __transaction_cancel statement (GCC Extension).

   transaction-cancel-statement:
     __transaction_cancel transaction-attribute[opt] ;

   Note that the only valid attribute is "outer".
*/

ਸਥਿਰ ਰੁੱਖ
c_parser_transaction_cancel (c_parser *parser)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਰੁੱਖ attrs;
  ਤਾਰਕਿਕ is_outer = ਝੂਠ;

  gcc_assert (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_TRANSACTION_CANCEL));
  c_parser_consume_token (parser);

  attrs = c_parser_transaction_ਗੁਣ (parser);
  ਜੇ (attrs)
    is_outer = (parse_tm_stmt_attr (attrs, TM_STMT_ATTR_OUTER) != 0);

  ਜੇ (!flag_tm)
    {
      error_at (loc, "%<__transaction_cancel%> without "
		"transactional memory support enabled");
      ਜਾਓ ret_error;
    }
  ਨਹੀਂਤਾਂ ਜੇ (parser->ਵਿੱਚ_transaction & TM_STMT_ATTR_RELAXED)
    {
      error_at (loc, "%<__transaction_cancel%> within a "
		"%<__transaction_relaxed%>");
      ਜਾਓ ret_error;
    }
  ਨਹੀਂਤਾਂ ਜੇ (is_outer)
    {
      ਜੇ ((parser->ਵਿੱਚ_transaction & TM_STMT_ATTR_OUTER) == 0
	  && !is_tm_may_cancel_outer (current_function_decl))
	{
	  error_at (loc, "outer %<__transaction_cancel%> not "
		    "within outer %<__transaction_atomic%> or "
		    "a %<transaction_may_cancel_outer%> function");
	  ਜਾਓ ret_error;
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (parser->ਵਿੱਚ_transaction == 0)
    {
      error_at (loc, "%<__transaction_cancel%> not within "
		"%<__transaction_atomic%>");
      ਜਾਓ ret_error;
    }

  ਵਾਪਸ ਜੋੜੋ_stmt (build_tm_abort_call (loc, is_outer));

 ret_error:
  ਵਾਪਸ build1 (NOP_ਵਿਅੰਜਕ, void_type_ਗੰਢ, error_mark_ਗੰਢ);
}

/* Parse a single source file.  */

ਖਾਲੀ
c_parse_file (ਖਾਲੀ)
{
  /* Use local storage to begin.  If the first token is a pragma, parse it.
     If it is #pragma GCC pch_preprocess, then this will load a PCH file
     which will cause garbage collection.  */
  c_parser tparser;

  memset (&tparser, 0, ਆਕਾਰ tparser);
  tparser.translate_ਲੜੀਆਂ_p = ਸੱਚ;
  tparser.ਟੋਕਨ = &tparser.ਟੋਕਨ_buf[0];
  the_parser = &tparser;

  ਜੇ (c_parser_peek_token (&tparser)->pragma_ਕਿਸਮ == PRAGMA_GCC_PCH_PREPROCESS)
    c_parser_pragma_pch_preprocess (&tparser);
  ਨਹੀਂਤਾਂ
    c_common_no_ਹੋਰ_pch ();

  the_parser = ggc_alloc<c_parser> ();
  *the_parser = tparser;
  ਜੇ (tparser.ਟੋਕਨ == &tparser.ਟੋਕਨ_buf[0])
    the_parser->ਟੋਕਨ = &the_parser->ਟੋਕਨ_buf[0];

  /* Initialize EH, if we've been told to do so.  */
  ਜੇ (flag_exceptions)
    using_eh_for_cleanups ();

  c_parser_translation_unit (the_parser);
  the_parser = ਨਿਰਾ;
}

ਖਾਲੀ
c_init_preprocess (ਖਾਲੀ)
{
  /* Create a parser for use by pragma_lex during preprocessing.  */
  the_parser = ggc_alloc<c_parser> ();
  memset (the_parser, 0, ਆਕਾਰ (c_parser));
  the_parser->ਟੋਕਨ = &the_parser->ਟੋਕਨ_buf[0];
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
c_parser_parse_rtl_body (c_parser *parser, ਅੱਖਰ *ਸ਼ੁਰੂ_with_pass)
{
  ਜੇ (!c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    {
      ਮੁਕਤ (ਸ਼ੁਰੂ_with_pass);
      ਵਾਪਸ c_parser_peek_token (parser)->location;
    }

  location_t ਸ਼ੁਰੂ_loc = c_parser_peek_token (parser)->location;

  /* Consume all tokens, up to the closing brace, handling
     matching pairs of braces in the rtl dump.  */
  ਪੂਰਨ ਅੰਕ_open_braces = 1;
  ਜਦੋਂ (1)
    {
      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_OPEN_BRACE:
	  ਅੰਕ_open_braces++;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_CLOSE_BRACE:
	  ਜੇ (--ਅੰਕ_open_braces == 0)
	    ਜਾਓ ਮਿਲਿਆ_closing_brace;
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_EOF:
	  error_at (ਸ਼ੁਰੂ_loc, "no closing brace");
	  ਮੁਕਤ (ਸ਼ੁਰੂ_with_pass);
	  ਵਾਪਸ c_parser_peek_token (parser)->location;
	ਮੂਲ:
	  ਰੋਕੋ;
	}
      c_parser_consume_token (parser);
    }

 ਮਿਲਿਆ_closing_brace:
  /* At the closing brace; record its location.  */
  location_t ਸਿਰਾ_loc = c_parser_peek_token (parser)->location;

  /* Consume the closing brace.  */
  c_parser_consume_token (parser);

  /* Invoke the RTL parser.  */
  ਜੇ (!read_rtl_function_body_from_file_range (ਸ਼ੁਰੂ_loc, ਸਿਰਾ_loc))
    {
      ਮੁਕਤ (ਸ਼ੁਰੂ_with_pass);
      ਵਾਪਸ ਸਿਰਾ_loc;
    }

 /*  Run the backend on the cfun created above, transferring ownership of
     START_WITH_PASS.  */
  ਲੜੀਵਾਰ_rtl_passes (ਸ਼ੁਰੂ_with_pass);
  ਵਾਪਸ ਸਿਰਾ_loc;
}

#ਅਨ੍ਤਰ੍ਭਾਵ "gt-c-c-parser.h"
